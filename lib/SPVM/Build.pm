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
  
  my $native_dir = $module_name;
  $native_dir =~ s/::/\//g;
  $native_dir .= '.native';
  $native_dir = "$source_dir/$native_dir";
  
  # Correct source files
  my $src_files = [];
  my @valid_exts = ('c', 'C', 'cpp', 'i', 's', 'cxx', 'cc');
  for my $src_file (glob "$native_dir/*") {
    if (grep { $src_file =~ /\.$_$/ } @valid_exts) {
      push @$src_files, $src_file;
    }
  }
  
  # Config
  my $config_file = "$native_dir/$module_base_name.config";
  my $config;
  if (-f $config_file) {
    $config = do $config_file
      or confess "Can't parser $config_file: $!$@";
  }
  
  # Include directory
  my $include_dirs = [];
  
  # Default include path
  my $api_header_include_dir = $INC{"SPVM/Build.pm"};
  $api_header_include_dir =~ s/\/Build\.pm$//;
  push @$include_dirs, $api_header_include_dir;
  
  push @$include_dirs, $native_dir;
  
  # CBuilder config
  my $cbuilder_config = {};
  
  # Convert ExtUitls::MakeMaker config to ExtUtils::CBuilder config
  if ($config) {
    # CBuilder config name which compatible with ExtUtils::MakeMaker
    my @cbuilder_config_names_compatible = qw(
      optimize
      cc
      ccflags
      ld
      lddlflags
    );
    for my $cbuilder_name (@cbuilder_config_names_compatible) {
      my $makemaker_name = uc $cbuilder_name;
      
      if (defined $config->{$makemaker_name}) {
        $cbuilder_config->{$cbuilder_name} = delete $config->{$makemaker_name};
      }
    }
  }
  
  # Include directory
  if (defined $config->{INC}) {
    my $inc = delete $config->{INC};
    
    my @include_dirs_tmp = split /\s+/, $inc;
    for my $include_dir_tmp (reverse @include_dirs_tmp) {
      if ($include_dir_tmp =~ s/^-I//) {
        unshift @$include_dirs, $include_dir_tmp;
      }
      else {
        confess "Invalid include option \"$inc\"";
      }
    }
  }
  
  # Shared library
  my $extra_linker_flags = '';
  if (defined $config->{LIBS}) {
    my $libs = delete $config->{LIBS};
    
    if (ref $libs eq 'ARRAY') {
      $libs = join(' ', @$libs);
    }
    
    $extra_linker_flags .= $libs;
  }
  
  my @keys = keys %$config;
  if (@keys) {
    confess "$keys[0] is not supported option";
  }
  
  # OPTIMIZE default is -O3
  $cbuilder_config->{optimize} ||= '-O3';
  
  # Compile source files
  my $quiet = 1;
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $cbuilder_config);
  my $object_files = [];
  unless (defined $object_dir) {
    $object_dir = tempdir(CLEANUP => 1);
  }
  for my $src_file (@$src_files) {
    # Object file
    my $object_file = $module_name;
    $object_file =~ s/:/_/g;
    my $src_file_under_score = $src_file;
    $src_file_under_score =~ s/^.+\///;
    $src_file_under_score =~ s/[^a-zA-Z0-9]/_/g;
    $object_file = "$object_dir/${object_file}____$src_file_under_score.o";
    
    # Compile source file
    $cbuilder->compile(
      source => $src_file,
      object_file => $object_file,
      include_dirs => $include_dirs
    );
    push @$object_files, $object_file;
  }
  
  
  my $dlext = $Config{dlext};
  my $native_func_names = SPVM::Build::get_native_func_names($module_dir, $module_name);

  # This is dummy to suppress boot strap function
  # This is bad hack
  unless (@$native_func_names) {
    push @$native_func_names, '';
  }

  my $lib_file = $cbuilder->link(
    objects => $object_files,
    module_name => $module_name,
    dl_func_list => $native_func_names,
    extra_linker_flags => ''
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

sub compile_jitcode {
  my $source_file = shift;
  
  # Source directory
  my $source_dir = dirname $source_file;
  
  # Object created directory
  my $object_dir = $source_dir;
  
  # Include directory
  my $include_dirs = [];
  
  # Default include path
  my $api_header_include_dir = $INC{"SPVM/Build.pm"};
  $api_header_include_dir =~ s/\/Build\.pm$//;
  push @$include_dirs, $api_header_include_dir;
  
  my $cbuilder_config = {};
  
  # OPTIMIZE default is -O3
  $cbuilder_config->{optimize} ||= '-O0';
  
  # Compile source files
  my $quiet = 1;
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $cbuilder_config);
  my $object_files = [];
  
  # Object file
  my $object_file = $source_file;
  $object_file =~ s/\.c$//;
  $object_file .= '.o';
  
  # Compile source file
  $cbuilder->compile(
    source => $source_file,
    object_file => $object_file,
    include_dirs => $include_dirs
  );
  push @$object_files, $object_file;
  
  my $lib_file = $cbuilder->link(
    objects => $object_files,
    module_name => 'SPVM::JITCode',
    dl_func_list => ['SPVM_JITCODE_call_sub'],
    extra_linker_flags => ''
  );
  
  return $lib_file;
}

1;
