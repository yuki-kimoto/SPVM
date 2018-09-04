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
use Scalar::Util 'weaken';

use File::Basename 'dirname', 'basename';

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  return bless $self, $class;
}

sub build_dir {
  my $self = shift;
  
  return $self->{build_dir};
}

sub output_file {
  my $self = shift;
  
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
  my $compile_success = $build->compile_spvm();
  unless ($compile_success) {
    croak "Compile error";
  }
  

=pod
  # Build precompile all subs - Compile C source codes and link them to SPVM precompile subroutine
  my $cbuilder_native = SPVM::Build::CBuilder::Native->new(
    build_dir => $build_dir,
    info => $build->info,
  );
  $cbuilder_native->{build} = $build;
  weaken $cbuilder_native->{build};
  $cbuilder_native->build({all_subs => 1, quiet => 0});
  
  # Build native packages - Compile C source codes and link them to SPVM native subroutine
  my $cbuilder_precompile = SPVM::Build::CBuilder::Precompile->new(
    build_dir => $build_dir,
    info => $build->info,
  );
  $cbuilder_precompile->{build} = $build;
  weaken $cbuilder_precompile->{build};
  $cbuilder_precompile->build({quiet => 0});

=cut
  
  $self->{build} = $build;

  # Create main csouce
  $self->create_main_csource;
  
=pod
  # compile main
  $self->compile_main;
  
  # Link and create exe file
  $self->link_main;
=cut

}

sub create_main_csource {
  my ($self) = @_;
  
  my $main_csource_file = "spvmcc_build/main.c";

  # Create c source file
  my $main_csource = $self->build_main_csource;

  open my $fh, '>', $main_csource_file
    or die "Can't create $main_csource_file";
  print $fh $main_csource;
  close $fh;
}

sub compile_main {

=pod
  my ($self, $build) = @_;
  
  my $build_dir = $build->build_dir;
  
  my $spvm_core_dir = "$build_dir/spvm_core";
  
  # SPVM source directory
  my $spvm_src_dir = $INC{"SPVM/Build/Util.pm"};
  $spvm_src_dir =~ s/\/Util\.pm$//;
  $spvm_src_dir .= '/src';
  
  my @src_files = glob "$spvm_src_dir/*.c";
  
  my $build_config = SPVM::Build::Util::new_default_build_config();
  my $config = $build_config->to_hash;
  
  # Compile source files
  my $cbuilder = ExtUtils::CBuilder->new(config => $config);
  my $object_files = [];
  for my $src_file (@src_files) {
    # Object file
    my $object_file = "$spvm_core_dir/" . basename($src_file);
    $object_file =~ s/\.c$//;
    $object_file .= '.o';
    
    # Compile source file
    $cbuilder->compile(
      source => $src_file,
      object_file => $object_file,
    );
    push @$object_files, $object_file;
  }
  
  return $object_files;
=cut

}


1;
