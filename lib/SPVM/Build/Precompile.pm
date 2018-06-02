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
  
  my $shared_lib_file_name = "$output_dir/$package_file_name.precompile/$package_file_name.$Config{dlext}";
  
  return $shared_lib_file_name;
}

sub build_shared_lib_runtime {
  my ($self, $package) = @_;

  my $package_id = $package->{id};
  my $package_name = $package->{name};

  # Output directory
  my $build_dir = $SPVM::BUILD_DIR;
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for runtime " . $self->category . " build";
  }

  my $package_file_name = $package_name;
  $package_file_name =~ s/::/__/g;
  my $output_dir = "$build_dir/$package_file_name." . $self->category;
  mkpath $output_dir;

  my $input_dir = $output_dir;
  
  my $subs = $self->get_subs_from_package_id($package->{id});
  my $sub_names = [map { $_->{name} } @$subs];

  my $csource_source = '';
  for my $sub_name (@$sub_names) {
    my $sub_csource_source = $self->build_csource($sub_name);
    $csource_source .= "$sub_csource_source\n";
  }
  my $source_file = "$input_dir/$package_file_name.c";

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

  # Compile Precompile code
  open my $fh, '>', $source_file
    or die "Can't create $source_file";
  print $fh $csource_source;
  close $fh;
  
  if ($csource_source ne $old_csource_source) {
    $self->build_shared_lib(
      package_name => $package_name,
      input_dir => $input_dir,
      output_dir => $output_dir,
      quiet => 1,
      sub_names => $sub_names,
    );
  }
  
  return $self->create_shared_lib_file_name($package_name);
}


1;
