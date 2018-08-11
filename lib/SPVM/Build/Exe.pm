package SPVM::Build::Exe;

use strict;
use warnings;
use Carp 'croak', 'confess';
use Pod::Usage 'pod2usage';

use SPVM::Build;
use SPVM::Build::Util;

use Getopt::Long 'GetOptions';

use ExtUtils::CBuilder;
use File::Copy 'move';
use File::Path 'mkpath';
use DynaLoader;

use File::Basename 'dirname', 'basename';

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  return bless $self, $class;
}

sub build_dir {
  return $self->{build_dir};
}

sub output_file {
  return $self->{output_file};
}

sub create_exe_file {
  my ($self, $package_name) = @_;
  
  # New SPVM::Build object
  my $build = SPVM::Build->new;
  
  # Add package informations
  my $package_info = {
    name => $package_name,
  };
  push @{$build->{package_infos}}, $package_info;
  
  # Compile
  my $compile_success = $self->compile_spvm();
  unless ($compile_success) {
    croak "Compile error";
  }
  
  my $build_dir = $self->build_dir;
  
  my $cbuilder_native = SPVM::Build::CBuilder::Native->new(
    build_dir => $build_dir,
    compiler => $build->compiler,
    info => $build->info,
  );
  
  my $cbuilder_precompile = SPVM::Build::CBuilder::Precompile->new(
    build_dir => $build_dir,
    compiler => $build->compiler,
    info => $build->info,
  );
  
  # Build precompile all subs - Compile C source codes and link them to SPVM precompile subroutine
  $cbuilder_native->build({all_subs => 1});
  
  # Build native packages - Compile C source codes and link them to SPVM native subroutine
  $cbuilder_precompile->build;
  
  # Build exe file
  $self->build_exe;
}




1;
