package SPVM::Builder::Exe;

use strict;
use warnings;
use Carp 'croak', 'confess';
use Pod::Usage 'pod2usage';
use Config;

use SPVM::Builder;
use SPVM::Builder::C;
use SPVM::Builder::Util;
use File::Find 'find';

use Getopt::Long 'GetOptions';

use ExtUtils::CBuilder;
use File::Copy 'copy', 'move';
use File::Path 'mkpath';
use DynaLoader;
use Scalar::Util 'weaken';
use File::Path 'mkpath';

use File::Basename 'dirname', 'basename';

sub new {
  my $class = shift;
  
  my $self = {@_};

  # Package name
  my $package_name = $self->{package_name};
  unless (defined $package_name) {
    croak "Package name not specified";
  }
  
  # Excutable file name
  my $exe_name = $self->{exe_name};
  unless (defined $exe_name) {
    $exe_name = $package_name;
    $exe_name =~ s/::/__/g;
    $self->{exe_name} = $exe_name;
  }
  
  # Build directory
  my $build_dir = $self->{build_dir};
  unless (defined $build_dir) {
    $self->{build_dir} = 'spvm_build/exe';
  }
  
  return bless $self, $class;
}

sub build_exe_file {
  my ($self) = @_;
  
  # Package name
  my $package_name = $self->{package_name};
  
  # Excutable file name
  my $exe_name = $self->{exe_name};
  
  # Build directory
  my $build_dir = $self->{build_dir};
  mkpath $build_dir;
  
  # New SPVM::Builder object
  my $builder = SPVM::Builder->new(build_dir => $build_dir);
  
  $self->{builder} = $builder;
  
  # Add package informations
  my $package_info = {
    name => $package_name,
  };
  push @{$builder->{package_infos}}, $package_info;
  
  # Compile
  my $compile_success = $builder->compile_spvm();
  unless ($compile_success) {
    croak "Compile error";
  }
  
  # Build native packages - Compile C source codes and link them to SPVM native subroutine
  my $builder_c_native = SPVM::Builder::C->new(
    build_dir => $builder->{build_dir},
    info => $builder->{info},
    category => 'native',
    builder => $builder,
    quiet => 0,
    copy_dist => 1,
  );
  $builder_c_native->build;

  # Build precompile packages - Compile C source codes and link them to SPVM precompile subroutine
  my $builder_c_precompile = SPVM::Builder::C->new(
    build_dir => $builder->{build_dir},
    info => $builder->{info},
    category => 'precompile',
    builder => $builder,
    quiet => 0,
    copy_dist => 1,
  );
  $builder_c_precompile->build;

  # Compile SPVM csource
  $self->compile_spvm_csources;

  # Copy and rename shared libraray "libxxx.$Config{dlext"
  $self->copy_rename_spvm_shared_lib;

  # Create main csouce
  $self->create_main_csource($package_name);

  # compile main
  $self->compile_main;

  # Link and create exe file
  $self->link_main($package_name);
  
  $self->create_exe_file;
}

sub create_exe_file {

  my ($self) = @_;
  
  my $exe_name = $self->{exe_name};
  
  my $dlext = $Config{dlext};

  my $build_dir = $self->{build_dir};
  
  my $object_files = [];
  push @$object_files, glob "$build_dir/*.$dlext";
  
  my $build_config = SPVM::Builder::Util::new_default_build_config();
  
  # CBuilder configs
  my $lddlflags = $build_config->get_lddlflags;
  
  # ExeUtils::CBuilder config
  my $config = $build_config->to_hash;
  
  my $exe_file = "$build_dir/$exe_name";
  my $cbuilder = ExtUtils::CBuilder->new(quiet => 0, config => $config);
  my $tmp_shared_lib_file = $cbuilder->link_executable(
    objects => $object_files,
    exe_file => $exe_file,
  );
}

sub compile_spvm_csources {
  my ($self, $package_name, $sub_names, $opt) = @_;
  
  # Correct source files
  my $src_files = [glob "blib/lib/SPVM/Builder/src/*.c"];
  
  # Config
  my $build_config = SPVM::Builder::Util::new_default_build_config;
  
  # CBuilder configs
  my $ccflags = $build_config->get_ccflags;
  
  # Default include path
  $build_config->add_ccflags("-Iblib/lib/SPVM/Builder/include");

  # Use all of default %Config not to use %Config directory by ExtUtils::CBuilder
  # and overwrite user configs
  my $config = $build_config->to_hash;
  
  # Build directory
  my $build_dir = $self->{build_dir};
  
  # SPVM dir
  my $build_spvm_dir = "$build_dir/spvm";
  mkpath $build_spvm_dir;
  
  # Compile source files
  my $cbuilder = ExtUtils::CBuilder->new(quiet => 0, config => $config);
  my $object_files = [];
  for my $src_file (@$src_files) {
    # Object file
    my $object_file = "$build_spvm_dir/" . basename($src_file);
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
  my ($self, $package_name) = @_;
  
  my $build_dir = $self->{build_dir};
  my $main_csource_file = "$build_dir/my_main.c";

  # Create c source file
  my $main_csource = $self->build_main_csource($package_name);

  open my $fh, '>', $main_csource_file
    or die "Can't create $main_csource_file";
  print $fh $main_csource;
  close $fh;
}

sub copy_rename_spvm_shared_lib {
  my ($self) = @_;

  my $dlext = $Config{dlext};
  
  my $build_dir = $self->{build_dir};
  my $build_lib_dir = "$build_dir/lib";
  
  find(
    {
      wanted => sub {
        my $file_name = $File::Find::name;
        if ($file_name =~ /\.$dlext$/) {
          my $build_lib_dir_escape = quotemeta($build_lib_dir);
          my $module_path = $file_name;
          $module_path =~ s/^$build_lib_dir_escape//;
          $module_path =~ s/^[\/\\]//;
          
          my $shared_lib_file = $module_path;
          $shared_lib_file =~ s/\.$dlext$//;
          $shared_lib_file =~ s/\./-/g;
          $shared_lib_file .= ".$dlext";
          $shared_lib_file =~ s/[\/\\]/__/g;
          $shared_lib_file = "$build_dir/lib$shared_lib_file";
          
          copy $file_name, $shared_lib_file
            or croak "Can't copy $file_name to $shared_lib_file: $!";
        }
      },
      no_chdir => 1,
    }
    , $build_lib_dir
  );
}

sub compile_main {
  my ($self) = @_;
  
  my $build_dir = $self->{build_dir};

  my $build_config = SPVM::Builder::Util::new_default_build_config();
  $build_config->set_optimize('-O0');
  my $config = $build_config->to_hash;
  
  # Compile source files
  my $cbuilder = ExtUtils::CBuilder->new(quiet => 0, config => $config);
  my $object_file = "$build_dir/my_main.o";
  my $src_file = "$build_dir/my_main.c";
  
  # Compile source file
  $cbuilder->compile(
    source => $src_file,
    object_file => $object_file,
  );
  
  return $object_file;
}

sub link_main {
  my ($self, $package_name) = @_;
  
  my $dlext = $Config{dlext};

  my $build_dir = $self->{build_dir};
  
  my $object_files = [];
  push @$object_files, glob "$build_dir/my_main.o";
  push @$object_files, glob "$build_dir/spvm/*.o";
  
  my $build_config = SPVM::Builder::Util::new_default_build_config();
  
  # CBuilder configs
  my $lddlflags = $build_config->get_lddlflags;
  
  # ExeUtils::CBuilder config
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
  my $lib_file = "$build_dir/libmy_main.$dlext";
  my $tmp_shared_lib_file = $cbuilder->link(
    objects => $object_files,
    package_name => $package_name,
    dl_func_list => $cfunc_names,
    lib_file => $lib_file,
  );
}

1;
