package SPVM::Builder::ExeOld;

use strict;
use warnings;
use Carp 'confess';
use Pod::Usage 'pod2usage';
use Config;

use SPVM::Builder;
use SPVM::Builder::CC;
use SPVM::Builder::Util;
use File::Find 'find';

use Getopt::Long 'GetOptions';

use ExtUtils::CBuilder;
use File::Copy 'copy', 'move';
use File::Path 'mkpath';
use DynaLoader;
use Scalar::Util 'weaken';

use File::Basename 'dirname', 'basename';

sub builder { shift->{builder} }

sub new {
  my $class = shift;
  
  my $self = {@_};

  # Package name
  my $package_name = $self->{package_name};
  unless (defined $package_name) {
    confess "Package name not specified";
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
    $self->{build_dir} = 'spvm_build/work/exe';
  }
  
  # Quiet output
  unless (exists $self->{quiet}) {
    $self->{quiet} = 0;
  }
  
  # Library paths
  unless (exists $self->{library_path}) {
    $self->{library_path} = [];
  }

  # Library
  unless (exists $self->{library}) {
    $self->{library} = [];
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
    file => 'internal',
    line => 0,
  };
  push @{$builder->{package_infos}}, $package_info;
  
  # Compile
  my $compile_success = $builder->compile_spvm();
  unless ($compile_success) {
    confess "Compile error";
  }
  
  my $quiet = $self->{quiet};
  
  # Object directry
  my $object_dir = "$build_dir/work/exe/object";
  mkpath $object_dir;
  
  my $all_libs = [];
  
  # Build native packages
  my $builder_c_native = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    category => 'native',
    builder => $builder,
    quiet => $quiet,
  );
  my $native_package_names = $builder->get_native_package_names;
  for my $native_package_name (@$native_package_names) {
    my $native_module_file = $builder->get_module_file($native_package_name);
    my $native_dir = $native_module_file;
    
    my $native_config_file = $builder->get_config_file($native_package_name);
    my $bconf = SPVM::Builder::Util::load_config($native_config_file);
    my $dll_infos = $bconf->parse_dll_infos;
    for my $dll_info (@$dll_infos) {
      if ($dll_info->{type} eq 'l') {
        push @$all_libs, "-l$dll_info->{name}";
      }
    }
    
    $native_dir =~ s/\.spvm$//;
    $native_dir .= 'native';
    my $src_dir = SPVM::Builder::Util::remove_package_part_from_file($native_module_file, $native_package_name);
    $builder_c_native->compile(
      $native_package_name,
      {
        src_dir => $src_dir,
        object_dir => $object_dir,
      }
    );
  }

  # Build precompile packages
  my $builder_c_precompile = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    category => 'precompile',
    builder => $builder,
    quiet => $quiet,
  );
  my $precompile_package_names = $builder->get_precompile_package_names;
  for my $precompile_package_name (@$precompile_package_names) {
    my $precompile_module_file = $builder->get_module_file($precompile_package_name);
    my $precompile_dir = $precompile_module_file;
    $precompile_dir =~ s/\.spvm$//;
    $precompile_dir .= 'precompile';
    my $src_dir;
    if (-f $precompile_dir) {
      $src_dir = SPVM::Builder::Util::remove_package_part_from_file($precompile_module_file, $precompile_package_name);
    }
    else {
      $src_dir = "$build_dir/work/exe/src";
      $builder_c_precompile->create_source_precompile(
        $precompile_package_name,
        [],
        {
          src_dir => $src_dir,
        }
      );
    }
    $builder_c_precompile->compile(
      $precompile_package_name,
      {
        src_dir => $src_dir,
        object_dir => $object_dir,
      }
    );
  }

  # Compile SPVM csource
  $self->compile_spvm_csources;

  # Create main csouce
  $self->create_main_csource($package_name);

  # compile main
  $self->compile_main;

  # Link executable
  $self->link_executable($package_name, $all_libs);
}

sub compile_spvm_csources {
  my ($self, $package_name, $sub_names, $opt) = @_;
  
  # Correct source files
  my $src_files = [glob "blib/lib/SPVM/Builder/src/*.c"];
  
  # Config
  my $bconf = SPVM::Builder::Config->new_c99;;
  
  # Default include path
  $bconf->add_extra_compiler_flags("-Iblib/lib/SPVM/Builder/include");
  
  $bconf->set_cache(0);
  $bconf->set_quiet(0);

  # Use all of default %Config not to use %Config directory by ExtUtils::CBuilder
  # and overwrite user configs
  my $config = $bconf->to_hash;
  
  # Build directory
  my $build_dir = $self->{build_dir};
  
  # Object dir
  my $object_dir = "$build_dir/work/exe/target/object";
  mkpath $object_dir;
  
  # Compile source files
  my $quiet = $self->{quiet};
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $config);
  my $object_files = [];
  for my $src_file (@$src_files) {
    # Object file
    my $object_file = "$object_dir/" . basename($src_file);
    $object_file =~ s/\.c$//;
    $object_file .= '.o';
    
    # Compile source file
    $cbuilder->compile(
      source => $src_file,
      object_file => $object_file,
      extra_compiler_flags => $bconf->get_extra_compiler_flags,
    );
    push @$object_files, $object_file;
  }
}

sub create_main_csource {
  my ($self, $package_name) = @_;
  
  my $build_dir = $self->{build_dir};
  
  my $src_dir = "$build_dir/work/exe/target/src";
  mkpath $src_dir;
  
  my $main_csource_file = "$build_dir/work/exe/target/src/my_main.c";

  # Create c source file
  my $main_csource = $self->build_main_csource($package_name);

  open my $fh, '>', $main_csource_file
    or die "Can't create $main_csource_file";
  print $fh $main_csource;
  close $fh;
}

sub compile_main {
  my ($self) = @_;
  
  my $build_dir = $self->{build_dir};

  my $bconf = SPVM::Builder::Config->new_c99;
  $bconf->set_optimize('-O0');
  my $config = $bconf->to_hash;
  
  # Compile source files
  my $quiet = $self->{quiet};
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $config);
  my $object_file = "$build_dir/work/exe/target/object/my_main.o";
  my $src_file = "$build_dir/work/exe/target/src/my_main.c";
  
  # Compile source file
  $cbuilder->compile(
    source => $src_file,
    object_file => $object_file,
    extra_compiler_flags => $bconf->get_extra_compiler_flags,
  );
  
  return $object_file;
}

sub link_executable {
  my ($self, $package_name, $all_libs) = @_;
  
  my $dlext = $Config{dlext};

  my $build_dir = $self->{build_dir};
  
  my $object_files = [];
  push @$object_files, glob "$build_dir/work/exe/target/object/*.o";
  
  my $builder = $self->builder;
  
  my $native_object_files = [];
  my $native_package_names = $builder->get_native_package_names;
  for my $native_package_name (@$native_package_names) {
    my $category = 'native';
    my $native_object_rel_file = SPVM::Builder::Util::convert_package_name_to_category_rel_file_with_ext($native_package_name, $category, 'o');
    my $native_object_file = "$build_dir/work/exe/object/$native_object_rel_file";
    push @$native_object_files, $native_object_file;
  }
  push @$object_files, @$native_object_files;
  
  my $precompile_object_files = [];
  my $precompile_package_names = $builder->get_precompile_package_names;
  for my $precompile_package_name (@$precompile_package_names) {
    my $category = 'precompile';
    my $precompile_object_rel_file = SPVM::Builder::Util::convert_package_name_to_category_rel_file_with_ext($precompile_package_name, $category, 'o');
    my $precompile_object_file = "$build_dir/work/exe/object/$precompile_object_rel_file";
    push @$precompile_object_files, $precompile_object_file;
  }
  push @$object_files, @$precompile_object_files;
  
  my $bconf = SPVM::Builder::Config->new_c99;
  
  # CBuilder configs
  my $lddlflags = $bconf->get_lddlflags;
  
  my $exe_name = $self->{exe_name};
  
  my $original_extra_linker_flag = $bconf->get_extra_linker_flags;
  my $extra_linker_flag = "$original_extra_linker_flag @$all_libs";
  
  # ExeUtils::CBuilder config
  my $config = $bconf->to_hash;
  
  my $quiet = $self->{quiet};
  
  my $exe_file = $exe_name;
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $config);
  my $tmp_dll_file = $cbuilder->link_executable(
    objects => $object_files,
    module_name => $package_name,
    exe_file => $exe_file,
    extra_linker_flags => $extra_linker_flag,
  );
}

1;
