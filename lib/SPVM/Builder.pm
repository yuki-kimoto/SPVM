package SPVM::Builder;

use strict;
use warnings;

use Carp 'confess';
use Scalar::Util 'weaken';
use File::Path 'mkpath';
use File::Basename 'dirname', 'basename';

use SPVM ();

use SPVM::Builder::CC;
use SPVM::Builder::Compiler;
use SPVM::Builder::Runtime;
use SPVM::Builder::Env;
use SPVM::Builder::Stack;

# Fields
sub build_dir {
  my $self = shift;
  if (@_) {
    $self->{build_dir} = $_[0];
    return $self;
  }
  else {
    return $self->{build_dir};
  }
}

sub include_dirs {
  my $self = shift;
  if (@_) {
    $self->{include_dirs} = $_[0];
    return $self;
  }
  else {
    return $self->{include_dirs};
  }
}

sub new {
  my $class = shift;
  
  my $self = {
    include_dirs => [map { "$_/SPVM" } @INC],
    @_
  };
  
  bless $self, ref $class || $class;
  
  return $self;
}

sub build_dynamic_lib_dist {
  my ($self, $basic_type_name, $category) = @_;
  
  # Create the compiler
  my $compiler = SPVM::Builder::Compiler->new(
    include_dirs => $self->include_dirs
  );
  
  my $success = $compiler->compile($basic_type_name, __FILE__, __LINE__);
  unless ($success) {
    $compiler->print_error_messages(*STDERR);
    exit(255);
  }
  my $runtime = $compiler->build_runtime;
  my $module_file = $runtime->get_file($basic_type_name);
  my $method_names = $runtime->get_method_names($basic_type_name, $category);
  my $anon_basic_type_names = $runtime->get_basic_type_anon_basic_type_names($basic_type_name);
  my $precompile_source = $runtime->build_precompile_source($basic_type_name);
  my $dl_func_list = SPVM::Builder::Util::create_dl_func_list($basic_type_name, $method_names, $anon_basic_type_names, {category => $category});
  
  $self->build_dist($basic_type_name, {category => $category, module_file => $module_file, dl_func_list => $dl_func_list, precompile_source => $precompile_source});
}

sub build_dist {
  my ($self, $basic_type_name, $options) = @_;
  
  $options ||= {};
  
  my $build_dir = $self->build_dir;
  
  my $dl_func_list = $options->{dl_func_list};
  my $module_file = $options->{module_file};
  my $precompile_source = $options->{precompile_source};
  
  my $category = $options->{category};
  
  my $build_src_dir;
  if ($category eq 'precompile') {
    $build_src_dir = SPVM::Builder::Util::create_build_src_path($build_dir);
    mkpath $build_src_dir;
    
    my $cc = SPVM::Builder::CC->new(
      build_dir => $build_dir,
    );
    
    $cc->build_precompile_source_file(
      $basic_type_name,
      {
        output_dir => $build_src_dir,
        precompile_source => $precompile_source,
        module_file => $module_file,
      }
    );
  }
  elsif ($category eq 'native') {
    $build_src_dir = 'lib';
  }

  my $build_object_dir = SPVM::Builder::Util::create_build_object_path($build_dir);
  mkpath $build_object_dir;
  
  my $build_lib_dir = 'blib/lib';
  
  $self->build(
    $basic_type_name,
    {
      compile_input_dir => $build_src_dir,
      compile_output_dir => $build_object_dir,
      link_output_dir => $build_lib_dir,
      category => $category,
      module_file => $module_file,
      dl_func_list => $dl_func_list,
    }
  );
}

sub build_dynamic_lib_dist_precompile {
  my ($self, $basic_type_name) = @_;
  
  $self->build_dynamic_lib_dist($basic_type_name, 'precompile');
}

sub build_dynamic_lib_dist_native {
  my ($self, $basic_type_name) = @_;
  
  $self->build_dynamic_lib_dist($basic_type_name, 'native');
}

sub build_at_runtime {
  my ($self, $basic_type_name, $options) = @_;
  
  $options ||= {};
  
  my $build_dir = $self->build_dir;
  
  my $dl_func_list = $options->{dl_func_list};
  my $module_file = $options->{module_file};
  my $precompile_source = $options->{precompile_source};

  my $category = $options->{category};
  
  # Build directory
  if (defined $build_dir) {
    mkpath $build_dir;
  }
  else {
    confess "The \"build_dir\" field must be defined to build a $category method at runtime. Perhaps the setting of the SPVM_BUILD_DIR environment variable is forgotten";
  }
  
  # Source directory
  my $build_src_dir;
  if ($category eq 'precompile') {
    $build_src_dir = SPVM::Builder::Util::create_build_src_path($build_dir);
    mkpath $build_src_dir;
    
    my $cc = SPVM::Builder::CC->new(
      build_dir => $build_dir,
      at_runtime => 1,
    );
    
    $cc->build_precompile_source_file(
      $basic_type_name,
      {
        output_dir => $build_src_dir,
        precompile_source => $precompile_source,
        module_file => $module_file,
      }
    );
  }
  elsif ($category eq 'native') {
    my $module_file = $options->{module_file};
    $build_src_dir = SPVM::Builder::Util::remove_basic_type_part_from_file($module_file, $basic_type_name);
  }
  
  # Object directory
  my $build_object_dir = SPVM::Builder::Util::create_build_object_path($build_dir);
  mkpath $build_object_dir;
  
  # Lib directory
  my $build_lib_dir = SPVM::Builder::Util::create_build_lib_path($build_dir);
  mkpath $build_lib_dir;
  
  my $build_file = $self->build(
    $basic_type_name,
    {
      compile_input_dir => $build_src_dir,
      compile_output_dir => $build_object_dir,
      link_output_dir => $build_lib_dir,
      category => $category,
      module_file => $module_file,
      dl_func_list => $dl_func_list,
      at_runtime => 1,
    }
  );
  
  return $build_file;
}

sub build {
  my ($self, $basic_type_name, $options) = @_;
  
  $options ||= {};
  
  my $build_dir = $self->build_dir;
  
  my $at_runtime = $options->{at_runtime};
  my $cc = SPVM::Builder::CC->new(
    build_dir => $build_dir,
    at_runtime => $at_runtime,
  );
  
  my $dl_func_list = $options->{dl_func_list};
  
  my $category = $options->{category};
  
  # Class file
  my $module_file = $options->{module_file};
  unless (defined $module_file) {
    my $config_file = SPVM::Builder::Util::get_config_file_from_basic_type_name($basic_type_name);
    if ($config_file) {
      $module_file = $config_file;
      $module_file =~ s/\.config$/\.spvm/;
    }
    else {
      confess "\"$module_file\" basic type is not loaded";
    }
  }
  
  my $config;
  if ($category eq 'native') {
    $config = $self->create_native_config_from_module_file($module_file);
  }
  elsif ($category eq 'precompile') {
    $config = SPVM::Builder::Util::API::create_default_config();
  }
  
  $config->module_name($basic_type_name);
  
  # Compile source file and create object files
  my $compile_options = {
    input_dir => $options->{compile_input_dir},
    output_dir => $options->{compile_output_dir},
    config => $config,
    category => $category,
  };

  my $object_files = $cc->compile_source_files($basic_type_name, $compile_options);
  
  # Link object files and create dynamic library
  my $link_options = {
    output_dir => $options->{link_output_dir},
    config => $config,
    category => $category,
    dl_func_list => $dl_func_list,
  };
  my $output_file = $cc->link(
    $basic_type_name,
    $object_files,
    $link_options
  );
  
  return $output_file;
}

sub create_native_config_from_module_file {
  my ($self, $module_file) = @_;
  
  my $config;
  my $config_file = $module_file;
  $config_file =~ s/\.spvm$/.config/;

  # Config file
  if (-f $config_file) {
    $config = SPVM::Builder::Config->load_config($config_file);
  }
  else {
    my $error = $self->_error_message_find_config($config_file);
    confess $error;
  }
  
  return $config;
}

sub _error_message_find_config {
  my ($self, $config_file) = @_;
  
  my $error = <<"EOS";
Can't find the native config file \"$config_file\".

The config file must contain at least the following code.
----------------------------------------------
use strict;
use warnings;

use SPVM::Builder::Config;
my \$config = SPVM::Builder::Config->new_c99(file => __FILE__);

\$config;
----------------------------------------------
EOS
  
}

1;

=encoding utf8

=head1 Name

SPVM::Builder - Build Dynamic Libraries for SPVM Distribution

=head1 Description

The SPVM::Builder class has methods to build dynamic librares for a SPVM distribution.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
