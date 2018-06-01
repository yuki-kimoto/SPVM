package SPVM::Build::Precompile;

use strict;
use warnings;
use base 'SPVM::Build::Base';

use Carp 'croak', 'confess';
use File::Spec;

use SPVM::Build::Util;

use ExtUtils::CBuilder;
use Config;
use File::Copy 'move';
use File::Path 'mkpath', 'rmtree';

use File::Basename 'dirname', 'basename';

use SPVM::Build::SPVMInfo;
use SPVM::Build::Util;

sub new {
  my $self = shift->SUPER::new(@_);

  $self->{category} = 'precompile';
  
  return $self;
}

sub get_sub_names_from_module_file {
  my ($self, $module_file) = @_;
  
  return SPVM::Build::Util::get_precompile_sub_names_from_module_file($module_file);
}

sub get_subs_from_package_id {
  my ($self, $package_id) = @_;
  
  return SPVM::Build::SPVMInfo::get_precompile_subs_from_package_id($package_id);;
}

sub create_cfunc_name {
  my ($self, $sub_name) = @_;

  # Precompile Subroutine names
  my $cfunc_name = $sub_name;
  $cfunc_name =~ s/:/_/g;
  $cfunc_name = "SPVM_BUILD_PRECOMPILE_$cfunc_name";
  
  return $cfunc_name;
}

sub create_shared_lib_file_name {
  my ($self, $package_name) = @_;
  
  # Build Precompile code
  my $output_dir = $SPVM::BUILD_DIR;
  unless (defined $output_dir && -d $output_dir) {
    confess "SPVM build directory must be specified for precompile";
  }
  
  my $package_file_name = $package_name;
  $package_file_name =~ s/::/__/g;
  
  my $shared_lib_file_name = "$output_dir/$package_file_name.$Config{dlext}";
  
  return $shared_lib_file_name;
}

sub build_shared_lib_runtime {
  my ($self, $package) = @_;
  
  my $package_id = $package->{id};
  my $package_name = $package->{name};
  
  my $subs = SPVM::Build::SPVMInfo::get_precompile_subs_from_package_id($package->{id});

  my $csource_source = '';
  for my $sub (@$subs) {
    my $sub_name = $sub->{name};
    my $sub_id = $sub->{id};
    
    my $sub_csource_source = $self->build_csource($sub_id);
    $csource_source .= "$sub_csource_source\n";
  }

  # Build Precompile code
  my $output_dir = $SPVM::BUILD_DIR;
  unless (defined $output_dir && -d $output_dir) {
    confess "SPVM build directory must be specified for precompile";
  }
  
  my $package_file_name = $package_name;
  $package_file_name =~ s/::/__/g;
  
  my $source_file = "$output_dir/$package_file_name.c";
  my $shared_lib_file = $self->create_shared_lib_file_name($package_name);

  # Get old csource source
  my $old_csource_source;
  if (-f $source_file) {
    open my $fh, '<', $source_file
      or die "Can't open $source_file";
    $old_csource_source = do { local $/; <$fh> };
  }
  else {
    $old_csource_source = '';
  }
  
  # Only compile when source is different
  if ($csource_source ne $old_csource_source) {
  
    # Compile Precompile code
    open my $fh, '>', $source_file
      or die "Can't create $source_file";
    print $fh $csource_source;
    close $fh;
    
    {
      my $source_file = $source_file;
      
      # Source directory
      my $source_dir = dirname $source_file;
      
      # Object created directory
      my $object_dir = $source_dir;
      
      # Include directory
      my $include_dirs = [];
      
      # Default include path
      my $env_header_include_dir = $INC{"SPVM/Build/Native.pm"};
      $env_header_include_dir =~ s/\/Build\/Native\.pm$//;
      push @$include_dirs, $env_header_include_dir;
      
      my $cbuilder_config = {};
      
      # OPTIMIZE
      $cbuilder_config->{optimize} ||= $self->optimize;
      
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
        include_dirs => $include_dirs,
        extra_compiler_flags => $self->extra_compiler_flags
      );
      push @$object_files, $object_file;
      
      my $cfunc_names = [map { $self->create_cfunc_name($_->{name}) } @$subs];
      my $lib_file = $cbuilder->link(
        objects => $object_files,
        module_name => $package_file_name,
        dl_func_list => $cfunc_names,
      );
    }
  }
  
  return $self->create_shared_lib_file_name($package_name);
}

1;
