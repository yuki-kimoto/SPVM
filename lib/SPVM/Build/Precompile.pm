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

sub get_subs_from_package_name {
  my ($self, $package_name) = @_;
  
  return SPVM::Build::SPVMInfo::get_precompile_subs_from_package_name($package_name);
}

sub create_cfunc_name {
  my ($self, $sub_name) = @_;

  # Precompile Subroutine names
  my $cfunc_name = $sub_name;
  $cfunc_name =~ s/:/_/g;
  $cfunc_name = "SPVM_BUILD_PRECOMPILE_$cfunc_name";
  
  return $cfunc_name;
}

sub build_shared_lib_runtime {
  my ($self, $package_name) = @_;

  # Output directory
  my $build_dir = $SPVM::BUILD_DIR;
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for runtime " . $self->category . " build";
  }
  
  my $work_dir = "$build_dir/work/" . $self->category;
  mkpath $work_dir;
  
  my $package_file_name = $package_name;
  $package_file_name =~ s/::/__/g;
  my $input_dir = "$build_dir/$package_file_name." . $self->category;
  mkpath $input_dir;

  my $output_dir = "$build_dir/lib";
  mkpath $output_dir;
  
  my $subs = $self->get_subs_from_package_name($package_name);
  my $sub_names = [map { $_->{name} } @$subs];

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
  
  # Create c source file
  my $csource_source = '';
  for my $sub_name (@$sub_names) {
    my $sub_csource_source = $self->build_csource($sub_name);
    $csource_source .= "$sub_csource_source\n";
  }
  open my $fh, '>', $source_file
    or die "Can't create $source_file";
  print $fh $csource_source;
  close $fh;
  
  if ($csource_source ne $old_csource_source) {
    $self->build_shared_lib(
      package_name => $package_name,
      input_dir => $input_dir,
      work_dir => $work_dir,
      output_dir => $output_dir,
      quiet => 1,
      sub_names => $sub_names,
    );
  }
  
  my $shared_lib_rel_file = SPVM::Build::Util::convert_package_name_to_shared_lib_rel_file($package_name, $self->category);
  my $shared_lib_file = "$output_dir/$shared_lib_rel_file";
  
  return $shared_lib_file;
}

1;
