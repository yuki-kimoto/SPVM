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

  # Compile SPVM csource
  $self->compile_spvm_csources;
  
  # Create main csouce
  $self->create_main_csource($package_name);
  
  # compile main
  $self->compile_main;

  # Link and create exe file
  $self->link_main($package_name);
}

sub compile_spvm_csources {
  my ($self, $package_name, $sub_names, $opt) = @_;
  
  # Correct source files
  my $src_files = [glob "blib/lib/SPVM/Build/src/*.c"];
  
  # Config
  my $build_config = SPVM::Build::Util::new_default_build_config;
  
  # CBuilder configs
  my $ccflags = $build_config->get_ccflags;
  
  # Default include path
  $build_config->add_ccflags("-Iblib/lib/SPVM/Build/include");

  # Use all of default %Config not to use %Config directory by ExtUtils::CBuilder
  # and overwrite user configs
  my $config = $build_config->to_hash;
  
  # Compile source files
  my $cbuilder = ExtUtils::CBuilder->new(quiet => 0, config => $config);
  my $object_files = [];
  for my $src_file (@$src_files) {
    # Object file
    my $object_file = "spvmcc_build/" . basename($src_file);
    $object_file =~ s/\.c$//;
    $object_file .= '.o';
    
    # Compile source file
    $cbuilder->compile(
      source => $src_file,
      object_file => $object_file,
    );
    push @$object_files, $object_file;
  }
}

sub create_main_csource {
  my ($self) = @_;
  
  my $main_csource_file = "spvmcc_build/my_runtime.c";

  # Create c source file
  my $main_csource = $self->build_main_csource;

  open my $fh, '>', $main_csource_file
    or die "Can't create $main_csource_file";
  print $fh $main_csource;
  close $fh;
}

sub compile_main {
  my ($self) = @_;
  
  my $build_config = SPVM::Build::Util::new_default_build_config();
  my $config = $build_config->to_hash;
  
  # Compile source files
  my $cbuilder = ExtUtils::CBuilder->new(quiet => 0, config => $config);
  my $object_file = "spvmcc_build/my_runtime.o";
  my $src_file = "spvmcc_build/my_runtime.c";
  
  # Compile source file
  $cbuilder->compile(
    source => $src_file,
    object_file => $object_file,
  );
  
  return $object_file;
}

sub link_main {
  my ($self, $package_name) = @_;
  
  my $object_files = [glob 'spvmcc_build/*.o'];
  
  my $build_config = SPVM::Build::Util::new_default_build_config();
  my $config = $build_config->to_hash;
  
  # CBuilder configs
  my $lddlflags = $build_config->get_lddlflags;

  # Use all of default %Config not to use %Config directory by ExtUtils::CBuilder
  # and overwrite user configs
  my $config = $build_config->to_hash;
  
  my $sub_names = [];
  
  my $cfunc_names = [];
  for my $sub_name (@$sub_names) {
    my $category = $self->category;
    my $category_uc = uc $category;
    my $cfunc_name = "SPVM_${category_uc}_${package_name}::$sub_name";
    $cfunc_name =~ s/:/_/g;
    push @$cfunc_names, $cfunc_name;
  }
  
  # This is dummy to suppress boot strap function
  # This is bad hack
  unless (@$cfunc_names) {
    push @$cfunc_names, '';
  }
  
  my $cbuilder = ExtUtils::CBuilder->new(quiet => 0, config => $config);
  my $tmp_shared_lib_file = $cbuilder->link(
    objects => $object_files,
    package_name => $package_name,
    dl_func_list => $cfunc_names,
  );
}

1;
