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

sub get_sub_names_dist {
  my ($self, $package_name) = @_;
  
  my $package_load_path = SPVM::Build::Util::create_package_load_path('lib', $package_name);
  
  open my $module_fh, '<', $package_load_path
    or croak "Can't open $package_load_path: $!";
  
  my $src = do { local $/; <$module_fh> };
  
  my $precompile_sub_names = [];
  while ($src =~ /compile\b(.*?)\bsub\s+([^\s]+)\s/g) {
    my $sub_name = $1;
    push @$precompile_sub_names, $sub_name;
  }
  
  return $precompile_sub_names;
}

sub get_subs_from_package_name {
  my ($self, $package_name) = @_;
  
  return SPVM::Build::SPVMInfo::get_precompile_subs_from_package_name($self->{compiler}, $package_name);
}

sub create_cfunc_name {
  my ($self, $sub_name) = @_;

  # Precompile Subroutine names
  my $cfunc_name = $sub_name;
  $cfunc_name =~ s/:/_/g;
  $cfunc_name = "SPVM_BUILD_PRECOMPILE_$cfunc_name";
  
  return $cfunc_name;
}

sub create_shared_lib_runtime {
  my ($self, $package_name) = @_;

  # Output directory
  my $build_dir = $self->{build_dir};
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for runtime " . $self->category . " build";
  }
  
  my $work_dir = "$build_dir/work";
  mkpath $work_dir;
  
  my $input_dir = "$build_dir/src";
  my $package_path = SPVM::Build::Util::convert_package_name_to_path($package_name, $self->category);
  my $input_src_dir = "$input_dir/$package_path";
  mkpath $input_src_dir;
  
  my $output_dir = "$build_dir/lib";
  mkpath $output_dir;
  
  my $subs = $self->get_subs_from_package_name($package_name);
  my $sub_names = [map { $_->{name} } @$subs];

  my $module_base_name = $package_name;
  $module_base_name =~ s/^.+:://;
  
  my $source_file = "$input_src_dir/$module_base_name.c";

  # Get old csource source
  my $old_package_csource;
  if (-f $source_file) {
    open my $fh, '<', $source_file
      or die "Can't open $source_file";
    $old_package_csource = do { local $/; <$fh> };
  }
  else {
    $old_package_csource = '';
  }
  
  # Create c source file
  my $package_csource = $self->build_package_csource($package_name);
  open my $fh, '>', $source_file
    or die "Can't create $source_file";
  print $fh $package_csource;
  close $fh;
  
  if ($package_csource ne $old_package_csource) {
    $self->create_shared_lib(
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
