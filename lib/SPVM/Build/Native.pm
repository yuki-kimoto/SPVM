package SPVM::Build::Native;

# SPVM::Build::PPtUtil is used from Makefile.PL
# so this module must be wrote as pure per script, not contain XS and don't use any other SPVM modules.

use strict;
use warnings;
use base 'SPVM::Build::Base';

use Carp 'croak', 'confess';

use SPVM::Build::Util;
use SPVM::Build::SPVMInfo;

use ExtUtils::CBuilder;
use Config;
use File::Copy 'move';
use File::Path 'mkpath';
use DynaLoader;

use File::Basename 'dirname', 'basename';

sub new {
  my $self = shift->SUPER::new(@_);

  $self->{category} = 'native';
  
  return $self;
}

sub get_sub_names_from_module_file {
  my ($self, $module_file) = @_;
  
  return SPVM::Build::Util::get_native_sub_names_from_module_file($module_file);
}

sub get_subs_from_package_id {
  my ($self, $package_id) = @_;
  
  return SPVM::Build::SPVMInfo::get_native_subs_from_package_id($package_id);;
}

sub create_cfunc_name {
  my ($self, $sub_name) = @_;

  my $sub_name_spvm = "SPVM::$sub_name";

  my $cfunc_name = $sub_name_spvm;
  $cfunc_name =~ s/:/_/g;
  
  return $cfunc_name;
}

sub source_dir_dist {
  my ($self, $package_name) = @_;
  
  my $source_dir = SPVM::Build::Util::create_package_load_path('lib', $package_name);
  my $category = $self->category;
  $source_dir =~ s/\.spvm$/.$category/;
  
  return $source_dir;
}

sub build_shared_lib {
  my ($self, %opt) = @_;
  
  # Source directory
  my $source_dir_new = $opt{source_dir};
  
  # Module name
  my $package_name = $opt{package_name};
  
  # Module directory
  my $module_dir = $opt{module_dir};

  # Object created directory
  my $build_dir = $opt{build_dir};
  
  # Quiet output
  my $quiet = defined $opt{quiet} ? $opt{quiet} : 0;
 
  my $module_base_name = $package_name;
  $module_base_name =~ s/^.+:://;
  
  my $source_dir;
  if ($opt{source_dir}) {
    $source_dir = $opt{source_dir};
  }
  else {
    $source_dir = $package_name;
    $source_dir =~ s/::/\//g;
    $source_dir .= '.' . $self->category;
    $source_dir = "$module_dir/$source_dir";
  }

  # Get sub names from module file
  my $package_load_path = SPVM::Build::Util::create_package_load_path($module_dir, $package_name);
  my $sub_names = $self->get_sub_names_from_module_file($package_load_path);
  
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for " . $self->category . " build";
  }
  
  # Correct source files
  my $src_files = [];
  my @valid_exts = ('c', 'C', 'cpp', 'i', 's', 'cxx', 'cc');
  for my $src_file (glob "$source_dir/*") {
    if (grep { $src_file =~ /\.$_$/ } @valid_exts) {
      push @$src_files, $src_file;
    }
  }
  
  # Config
  my $config_file = "$source_dir/$module_base_name.config";
  my $config;
  if (-f $config_file) {
    $config = do $config_file
      or confess "Can't parser $config_file: $!$@";
  }
  
  # Include directory
  my $include_dirs = [];
  
  # Default include path
  my $env_header_include_dir = $INC{"SPVM/Build/Native.pm"};
  $env_header_include_dir =~ s/\/Build\/Native\.pm$//;
  push @$include_dirs, $env_header_include_dir;
  
  push @$include_dirs, $source_dir;
  
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
  
  # OPTIMIZE
  $cbuilder_config->{optimize} ||= $self->optimize;
  
  # Compile source files
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $cbuilder_config);
  my $object_files = [];
  for my $src_file (@$src_files) {
    # Object file
    my $object_file = $package_name;
    $object_file =~ s/:/_/g;
    my $src_file_under_score = $src_file;
    $src_file_under_score =~ s/^.+\///;
    $src_file_under_score =~ s/[^a-zA-Z0-9]/_/g;
    $object_file = "$build_dir/${object_file}____$src_file_under_score.o";
    
    # Compile source file
    $cbuilder->compile(
      source => $src_file,
      object_file => $object_file,
      include_dirs => $include_dirs,
      extra_compiler_flags => $self->extra_compiler_flags
    );
    push @$object_files, $object_file;
  }
  
  my $dlext = $Config{dlext};
  
  my $cfunc_names = [];
  for my $sub_name (@$sub_names) {
    my $cfunc_name = "${package_name}::$sub_name";
    $cfunc_name =~ s/:/_/g;
    push @$cfunc_names, $cfunc_name;
  }
  
  # This is dummy to suppress boot strap function
  # This is bad hack
  unless (@$cfunc_names) {
    push @$cfunc_names, '';
  }
  
  my $shared_lib_file = $cbuilder->link(
    objects => $object_files,
    package_name => $package_name,
    dl_func_list => $cfunc_names,
    extra_linker_flags => $extra_linker_flags
  );
  
  return $shared_lib_file;
}

1;
