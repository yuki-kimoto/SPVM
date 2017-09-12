package SPVM::Build;

use strict;
use warnings;
use Carp 'croak', 'confess';

use ExtUtils::CBuilder;
use Config;

use File::Basename 'dirname', 'basename';
use File::Temp 'tempdir';

my $compiled = {};

sub create_postamble {
  my %opt = @_;
  
  my $module_names = $opt{module_names};
  
  my $postamble;
  
  # dynamic section
  $postamble
    = "dynamic :: ";
  for my $module_name (@$module_names) {
    my $module_name_under_score = $module_name;
    $module_name_under_score =~ s/:/_/g;
    
    $postamble
      .= "shared_lib_$module_name_under_score ";
  }
  $postamble .= "\n\n";
  
  # shared_lib sections
  my $dlext = $Config{dlext};
  for my $module_name (@$module_names) {
    my $module_name_under_score = $module_name;
    $module_name_under_score =~ s/:/_/g;
    
    my $module_base_name = $module_name;
    $module_base_name =~ s/^.+:://;
    
    my $src_dir = $module_name;
    $src_dir =~ s/::/\//g;
    $src_dir = "native/$src_dir.native";
    
    # Dependency
    my @deps = grep { $_ ne '.' && $_ ne '..' } glob "$src_dir/*";
    
    # Shared library file
    my $shared_lib_file = $module_name;
    $shared_lib_file =~ s/::/\//g;
    $shared_lib_file = "blib/arch/auto/$shared_lib_file.native/$module_base_name.$dlext";
    
    # Get native source files
    $postamble
      .= "shared_lib_$module_name_under_score :: $shared_lib_file\n\n";
    $postamble
      .= "$shared_lib_file :: @deps\n\n";
    $postamble
      .= "\tperl build_shared_lib.pl --object_dir=. $module_name\n\n";
  }
  
  return $postamble;
}

sub build_shared_lib {
  my %opt = @_;
  
  # Module name
  my $module_name = $opt{module_name};
  
  # Module directory
  my $module_dir = $opt{module_dir};

  # Source directory
  my $source_dir = $opt{source_dir};
  unless (defined $source_dir) {
    $source_dir = $module_dir;
  }
  
  # Object created directory
  my $object_dir = $opt{object_dir};
  
  if ($compiled->{$module_name}) {
    return $compiled->{$module_name};
  }
  
  my $module_base_name = $module_name;
  $module_base_name =~ s/^.+:://;
  
  my $src_dir = $module_name;
  $src_dir =~ s/::/\//g;
  $src_dir .= '.native';
  
  # Correct source files
  my $src_files = [];
  my @valid_exts = ('c', 'C', 'cpp', 'i', 's', 'cxx', 'cc');
  for my $src_file (glob "$source_dir/$src_dir/*") {
    if (grep { $src_file =~ /\.$_$/ } @valid_exts) {
      push @$src_files, $src_file;
    }
  }
  
  # Config
  my $config_file = "$src_dir/$module_base_name.config";
  my $config;
  if (-f $config_file) {
  
    $config = do $config_file
      or confess "Can't parser $config_file: $!$@";
  }
  
  # Header inlucde directory
  my $include_dirs = [];
  my $api_header_include_dir = $INC{"SPVM/Build.pm"};
  $api_header_include_dir =~ s/\/Build\.pm$//;
  push @$include_dirs, $api_header_include_dir;
  
  # Convert ExtUitls::MakeMaker config to ExtUtils::CBuilder config
  my $cbuilder_new_config = {};
  if ($config) {
    # OPTIMIZE
    if (defined $config->{OPTIMIZE}) {
      $cbuilder_new_config->{optimize} = delete $config->{OPTIMIZE};
    }
    
    # CC
    if (defined $config->{CC}) {
      $cbuilder_new_config->{cc} = delete $config->{CC};
    }
    
    # CCFLAGS
    if (defined $config->{CCFLAGS}) {
      $cbuilder_new_config->{ccflags} = delete $config->{CCFLAGS};
    }
    
    # LD
    if (defined $config->{LD}) {
      $cbuilder_new_config->{ld} = delete $config->{LD};
    }
    
    # LDDLFLAGS
    if (defined $config->{LDDLFLAGS}) {
      $cbuilder_new_config->{lddlflags} = delete $config->{LDDLFLAGS};
    }
    
    my @keys = keys %$config;
    if (@keys) {
      confess "$keys[0] is not supported option";
    }
  }
  
  # OPTIMIZE default is -O3
  $cbuilder_new_config->{optimize} ||= '-O3';
  
  # Compile source files
  my $quiet = 1;
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $config);
  my $object_files = [];
  unless (defined $object_dir) {
    $object_dir = tempdir(CLEANUP => 1);
  }
  for my $src_file (@$src_files) {
    # Object file
    my $object_file = $module_name;
    $object_file =~ s/:/_/g;
    $object_file = "$object_dir/$object_file.o";
    
    # Compile source file
    $cbuilder->compile(
      source => $src_file,
      object_file => $object_file,
      include_dirs => $include_dirs
    );
    push @$object_files, $object_file;
  }
  
  # Link
  my $dlext = $Config{dlext};
  my $native_func_names = SPVM::Build::get_native_func_names($module_dir, $module_name);
  my $lib_file = $cbuilder->link(
    objects => $object_files,
    module_name => $module_name,
    dl_func_list => $native_func_names,
  );
  
  $compiled->{$module_name} = $lib_file;
  
  return $lib_file;
}

sub get_native_func_names {
  my ($module_dir, $module_name) = @_;
  
  my $module_file = $module_name;
  $module_file =~ s/:/\//g;
  $module_file = "$module_dir/$module_file.spvm";
  
  open my $module_fh, '<', $module_file
    or croak "Can't open $module_file: $!";
  
  my $native_func_names = [];
  
  my $src = do { local $/; <$module_fh> };
  
  while ($src =~ /sub\s+([^\s]+)\s*\((?:[^\)]*?)\)\s*\:\s*([^\{;]+);/g) {
    my $sub_name = $1;
    my $descripter_type = $2;
    if ($descripter_type =~ /\bnative\b/) {
      my $native_func_name = "${module_name}::$sub_name";
      $native_func_name =~ s/:/_/g;
      
      push @$native_func_names, $native_func_name;
    }
  }
  
  return $native_func_names;
}

1;
