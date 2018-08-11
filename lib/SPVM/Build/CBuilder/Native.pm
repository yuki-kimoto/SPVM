package SPVM::Build::CBuilder::Native;

# SPVM::Build::PPtUtil is used from Makefile.PL
# so this module must be wrote as pure per script, not contain XS and don't use any other SPVM modules.

use strict;
use warnings;
use base 'SPVM::Build::CBuilder';

use Carp 'croak', 'confess';

use ExtUtils::CBuilder;
use Config;
use File::Copy 'move';
use File::Path 'mkpath';
use DynaLoader;

use File::Basename 'dirname', 'basename';

use SPVM::Build;
use SPVM::Build::Util;

sub new {
  my $self = shift->SUPER::new(@_);

  $self->{category} = 'native';
  
  return $self;
}

sub build_shared_lib_dist {
  my ($self, $package_name, $sub_names) = @_;
  
  my $input_dir = 'lib';

  my $work_dir = "spvm_build/work";
  mkpath $work_dir;

  my $output_dir = 'blib/lib';

  my $category = $self->category;
  
  # Build shared library
  $self->build_shared_lib(
    $package_name,
    $sub_names,
    {
      input_dir => $input_dir,
      work_dir => $work_dir,
      output_dir => $output_dir,
    }
  );
}

sub build_shared_lib_runtime {
  my ($self, $package_name, $sub_names) = @_;
  
  my $package_load_path = $self->info->get_package_load_path($package_name);
  my $input_dir = SPVM::Build::Util::remove_package_part_from_path($package_load_path, $package_name);

  # Build directory
  my $build_dir = $self->{build_dir};
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for runtime " . $self->category . " build";
  }
  
  my $work_dir = "$build_dir/work";
  mkpath $work_dir;
  
  my $output_dir = "$build_dir/lib";
  mkpath $output_dir;
  
  $self->build_shared_lib(
    $package_name,
    $sub_names,
    {
      input_dir => $input_dir,
      work_dir => $work_dir,
      output_dir => $output_dir,
      quiet => 1,
    }
  );
}

1;
