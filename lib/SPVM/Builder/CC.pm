package SPVM::Builder::CC;

use strict;
use warnings;
use Carp 'confess';
use Config;

use ExtUtils::CBuilder;
use File::Copy 'copy', 'move';
use File::Path 'mkpath';
use File::Find 'find';
use File::Basename 'dirname', 'basename';

use SPVM::Builder::Util;
use SPVM::Builder::Util::API;
use SPVM::Builder::Config;
use SPVM::Builder::CompileInfo;
use SPVM::Builder::ObjectFileInfo;
use SPVM::Builder::LinkInfo;
use SPVM::Builder::Resource;

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

sub force {
  my $self = shift;
  if (@_) {
    $self->{force} = $_[0];
    return $self;
  }
  else {
    return $self->{force};
  }
}

sub quiet {
  my $self = shift;
  if (@_) {
    $self->{quiet} = $_[0];
    return $self;
  }
  else {
    return $self->{quiet};
  }
}

sub debug {
  my $self = shift;
  if (@_) {
    $self->{debug} = $_[0];
    return $self;
  }
  else {
    return $self->{debug};
  }
}

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, $class;
  
  my $env_spvm_cc_debug = SPVM::Builder::Util::get_normalized_env('SPVM_CC_DEBUG');
  if (defined $env_spvm_cc_debug) {
    $self->debug(1);
  }
  
  my $env_spvm_cc_quiet = SPVM::Builder::Util::get_normalized_env('SPVM_CC_QUIET');
  if (defined $env_spvm_cc_quiet) {
    $self->quiet(!!$env_spvm_cc_quiet);
  }
  
  my $env_spvm_cc_force = SPVM::Builder::Util::get_normalized_env('SPVM_CC_FORCE');
  if (defined $env_spvm_cc_force) {
    $self->force(1);
  }
  
  return $self;
}

# Instance Methods
sub detect_force {
  my ($self, $config) = @_;
  
  my $force;
  
  if (defined $self->force) {
    $force = $self->force;
  }
  elsif (defined $config && defined $config->force) {
    $force = $config->force;
  }
  else {
    $force = 0;
  }
  
  return $force;
}

sub detect_quiet {
  my ($self, $config) = @_;
  
  my $quiet;
  
  if (defined $self->debug) {
    $quiet = 0;
  }
  elsif (defined $self->quiet) {
    $quiet = $self->quiet;
  }
  elsif (defined $config && defined $config->quiet) {
    $quiet = $config->quiet;
  }
  elsif (defined $config && $config->is_jit) {
    $quiet = 1;
  }
  else {
    $quiet = 0;
  }
  
  return $quiet;
}

sub build_precompile_class_source_file {
  my ($self, $class_name, $options) = @_;
  
  my $config = $options->{config};
  
  my $runtime = $options->{runtime};
  
  my $class_file = &_runtime_get_class_file($runtime, $class_name);
  my $precompile_source = &_runtime_build_precompile_class_source($runtime, $class_name);
  
  # Force
  my $force = $self->detect_force;
  
  # Output - Precompile C source file
  my $cc_output_dir = $config->cc_output_dir;
  my $source_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'precompile.c');
  my $source_file = "$cc_output_dir/$source_rel_file";
  
  # Check if generating is needed
  my $spvm_include_dir = $INC{'SPVM/Builder.pm'};
  $spvm_include_dir =~ s/\.pm$//;
  $spvm_include_dir .= '/src';
  my $spvm_precompile_soruce_file = "$spvm_include_dir/spvm_precompile.c";
  unless (-f $spvm_precompile_soruce_file) {
    confess "Can't find $spvm_precompile_soruce_file";
  }
  my $need_generate = SPVM::Builder::Util::need_generate({
    force => $force,
    output_file => $source_file,
    input_files => [$class_file, $spvm_precompile_soruce_file],
  });
  
  # Generate precompile C source file
  if ($need_generate) {
    mkpath dirname $source_file;
    open my $fh, '>', $source_file
      or die "Can't create $source_file";
    print $fh $precompile_source;
    close $fh;
  }
}

sub compile_source_file {
  my ($self, $compile_info) = @_;
  
  my $config = $compile_info->config;
  
  # Quiet output
  my $quiet = $self->detect_quiet($config);
  
  my $source_file = $compile_info->source_file;
  
  # Execute compile command
  my $cbuilder = ExtUtils::CBuilder->new(quiet => 1);
  my $cc_cmd = $compile_info->create_command;
  
  unless ($quiet) {
    
    my $resource_loader_config = $compile_info->config->resource_loader_config;
    
    my $compile_info_category = $compile_info->category;
    
    my $message;
    if ($resource_loader_config) {
      
      my $resource_loader_config_class_name = $resource_loader_config->class_name;
      
      my $resource_loader_config_file = $config->file;
      
      my $resource_class_name = $config->class_name;
      
      my $resource_config_file = $config->file;
      
      $message = "[Compile a resource source file for the \"$resource_class_name\" resource using the config file \"$resource_config_file\", which is used as a resource for the class \"$resource_loader_config_class_name\" using the config file \"$resource_loader_config_file\"]";
    }
    else {
      my $config_class_name = $config->class_name;
      
      my $config_file = $config->file;
      
      if ($compile_info_category eq 'spvm_core') {
        $message = "[Compile a SPVM core source file]";
      }
      elsif ($compile_info_category eq 'bootstrap') {
        $message = "[Compile a bootstrap source file for an excutable file]";
      }
      elsif ($compile_info_category eq 'precompile_class') {
        $message = "[Compile a precompile source file for the \"$config_class_name\" class]";
      }
      elsif ($compile_info_category eq 'native_class') {
        $message = "[Compile a native class source file for the \"$config_class_name\" class using the config file \"$config_file\"]";
      }
      elsif ($compile_info_category eq 'native_source') {
        $message = "[Compile a native source file for the \"$config_class_name\" class using the config file \"$config_file\"]";
      }
      else {
        confess "[Unexpected Error]Invalid compile info category.";
      }
    }
    
    warn "$message\n";
    
    warn "@$cc_cmd\n";
  }
  
  $cbuilder->do_system(@$cc_cmd)
    or confess "$source_file file cannnot be compiled by the following command:\n@$cc_cmd\n";
}

sub compile_class {
  my ($self, $class_name, $options) = @_;
  
  unless (defined $class_name) {
    confess "A class name must be defined.";
  }
  
  $options ||= {};
  
  # Build directory
  my $build_dir = $self->build_dir;
  if (defined $build_dir) {
    mkpath $build_dir;
  }
  else {
    confess "Build directory is not specified. Maybe forget to set \"SPVM_BUILD_DIR\" environment variable?";
  }
  
  # Config
  my $config = $options->{config};
  
  my $runtime = $options->{runtime};
  
  my $used_as_resource = $config->used_as_resource;
  
  my $is_jit = $config->is_jit;
  
  my $category = $config->category;
  
  my $config_exe = $config->config_exe;
  
  # Native class file
  my $native_class_ext = $config->ext;
  
  if ($category eq 'precompile') {
    my $precompile_method_names = &_runtime_get_method_names($runtime, $class_name, $category);
    
    unless (@$precompile_method_names) {
      return [];
    }
  }
  
  my $cc_output_dir = $config->cc_output_dir;
  unless ($cc_output_dir) {
    $cc_output_dir = SPVM::Builder::Util::create_build_object_path($build_dir);
  }
  
  mkpath $cc_output_dir;
  
  if ($is_jit) {
    if (defined $build_dir) {
      mkpath $build_dir;
    }
    else {
      confess "The \"build_dir\" field must be defined to build a $category method at runtime. Perhaps the setting of the SPVM_BUILD_DIR environment variable is forgotten";
    }
  }
  
  my $class_file;
  if ($used_as_resource) {
    my $config_file = $config->file;
    
    my $config_file_basename = basename $config_file;
    
    my $config_file_dirname = dirname $config_file;
    
    $config_file_basename =~ s/\..+$//;
    
    $class_file = "$config_file_dirname/$config_file_basename.spvm";
    
    unless (-f $class_file) {
      confess "The resource \"$class_name\" must have its SPVM class file \"$class_file\".";
    }
  }
  else {
    $class_file = &_runtime_get_class_file($runtime, $class_name);
  }
  
  my $build_src_dir;
  if ($category eq 'precompile') {
    
    $build_src_dir = SPVM::Builder::Util::create_build_src_path($build_dir);
    mkpath $build_src_dir;
    
    my $config_precompile_class_source = $config->clone;
    
    $config_precompile_class_source->cc_output_dir($build_src_dir);
    
    $self->build_precompile_class_source_file(
      $class_name,
      {
        config => $config_precompile_class_source,
        runtime => $runtime,
      }
    );
  }
  elsif ($category eq 'native') {
    $build_src_dir = SPVM::Builder::Util::get_class_base_dir($class_file, $class_name);
  }
  
  my $build_object_dir = SPVM::Builder::Util::create_build_object_path($build_dir);
  mkpath $build_object_dir;
  
  my $input_dir = $build_src_dir;
  
  # Class file
  unless (defined $class_file) {
    confess "[Unexpected Error]The class file is not defined.";
  }
  
  if (defined $config->file) {
    my $config_file = $config->file;
    
    my $config_file_abs = File::Spec->rel2abs($config_file);
    
    my $class_file_cannonpath = File::Spec->rel2abs($class_file);
    
    my $class_file_cannonpath_without_ext = $class_file_cannonpath;
    $class_file_cannonpath_without_ext =~ s/\.spvm$//;
    my $class_file_cannonpath_without_ext_quotemeta = quotemeta $class_file_cannonpath_without_ext;
    
    unless ($config_file_abs =~ /^$class_file_cannonpath_without_ext_quotemeta\./) {
      confess "The config file \"$config_file_abs\" is not compatible with the SPVM file \"$class_file_cannonpath\".";
    }
  }
  
  $config->class_name("$class_name");
  
  if ($config_exe) {
    my $before_each_compile_cbs = $config_exe->before_each_compile_cbs;
    $config->add_before_compile_cb(@$before_each_compile_cbs);
  }
  
  # Force compile
  my $force = $self->detect_force($config);
  
  # Add resource include directories
  my $resource_names = $config->get_resource_names;
  my $resource_include_dirs = [];
  for my $resource_name (@$resource_names) {
    my $resource = $config->get_resource($resource_name);
    my $resource_config = $resource->config;
    my $resource_include_dir = $resource_config->native_include_dir;
    if (defined $resource_include_dir) {
      push @$resource_include_dirs, $resource_include_dir;
    }
  }
  
  my $object_files = [];
  
  unless ($config->no_compile_resource) {
    for my $resource_name (@$resource_names) {
      my $resource = $config->get_resource($resource_name);
      
      # Build native classes
      my $builder_cc_resource = SPVM::Builder::CC->new(
        build_dir => $self->build_dir,
      );
      
      my $resource_class_name;
      my $resource_config;
      if (ref $resource) {
        $resource_class_name = $resource->class_name;
        $resource_config = $resource->config;
      }
      else {
        $resource_class_name = $resource;
      }
      
      $resource_config->add_include_dir(@$resource_include_dirs);
      
      $resource_config->class_name($resource_class_name);
      
      $resource_config->resource_loader_config($config),
      
      $resource_config->used_as_resource(1),
      
      my $resource_object_dir = $self->get_resource_object_dir_from_basic_type_name($class_name);
      mkpath $resource_object_dir;
      
      $resource_config->cc_output_dir($resource_object_dir),
      
      my $compile_options = {
        runtime => $runtime,
        config => $resource_config,
      };
      
      my $resouce_object_files = $builder_cc_resource->compile_class($resource_class_name, $compile_options);
      push @$object_files, @$resouce_object_files;
    }
  }
  
  # Native class file
  my $native_class_file;
  unless ($used_as_resource) {
    if (defined $native_class_ext) {
      my $native_class_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, $native_class_ext);
      $native_class_file = "$input_dir/$native_class_rel_file";
      
      unless (-f $native_class_file) {
        unless ($config->isa('SPVM::Builder::Config::Exe')) {
          confess "Can't find source file $native_class_file";
        }
      }
    }
  }
  
  # Native source files
  my $native_source_files_base = $config->source_files;
  my $native_src_dir = $config->native_src_dir;
  my $native_source_files;
  if (defined $native_src_dir) {
    $native_source_files = [map { "$native_src_dir/$_" } @$native_source_files_base ];
  }
  
  # Compile source files
  my $is_native_class = 1;
  for my $source_file ($native_class_file, @$native_source_files) {
    my $current_is_native_class = $is_native_class;
    $is_native_class = 0;
    
    next unless defined $source_file && -f $source_file;;
    
    my $object_file_name;
    
    # Object file of native class
    if ($current_is_native_class) {
      my $object_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, 'o');
      $object_file_name = "$cc_output_dir/$object_rel_file";
    }
    # Object file of resource source file
    else {
      my $object_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, 'native');
      
      my $object_file_base = $source_file;
      $object_file_base =~ s/^\Q$native_src_dir//;
      $object_file_base =~ s/^[\\\/]//;
      
      $object_file_base =~ s/\.[^\.]+$/.o/;
      $object_file_name = "$cc_output_dir/$object_rel_file/$object_file_base";
      
      my $output_dir = dirname $object_file_name;
      mkpath $output_dir;
    }
    
    # Check if object file need to be generated
    my $need_generate;
    {
      # Own resource header files
      my @own_header_files;
      my $native_include_dir = $config->native_include_dir;
      if (defined $native_include_dir && -d $native_include_dir) {
        find(
          {
            wanted => sub {
              my $include_file_name = $File::Find::name;
              if (-f $include_file_name) {
                push @own_header_files, $include_file_name;
              }
            },
            no_chdir => 1,
          },
          $native_include_dir,
        );
      }
      my $input_files = [$source_file, @own_header_files];
      if (defined $config->file) {
        push @$input_files, $config->file;
      };
      if ($current_is_native_class) {
        my $class_file = $source_file;
        $class_file =~ s/\.[^\/\\]+$//;
        $class_file .= '.spvm';
        
        push @$input_files, $class_file;
      }
      $need_generate = SPVM::Builder::Util::need_generate({
        force => $force,
        output_file => $object_file_name,
        input_files => $input_files,
      });
    }
    
    my $compile_info_category;
    if ($category eq 'precompile') {
      $compile_info_category = 'precompile_class';
    }
    elsif ($category eq 'native') {
      if ($current_is_native_class) {
        $compile_info_category = 'native_class';
      }
      else {
        $compile_info_category = 'native_source';
      }
    }
    
    # Compile-information
    my $compile_info = SPVM::Builder::CompileInfo->new(
      output_file => $object_file_name,
      source_file => $source_file,
      config => $config,
      category => $compile_info_category,
    );
    
    my $before_compile_cbs = $config->before_compile_cbs;
    for my $before_compile_cb (@$before_compile_cbs) {
      $before_compile_cb->($config, $compile_info);
    }
    
    # Compile a source file
    if ($need_generate) {
      my $module_rel_dir = SPVM::Builder::Util::convert_class_name_to_rel_dir($class_name);
      my $work_output_dir = "$cc_output_dir/$module_rel_dir";
      mkpath dirname $object_file_name;
      
      $self->compile_source_file($compile_info);
    }
    
    # Object file information
    my $compile_info_cc = $compile_info->{cc};
    my $compile_info_ccflags = $compile_info->{ccflags};
    my $object_file = SPVM::Builder::ObjectFileInfo->new(
      file => $object_file_name,
      compile_info => $compile_info,
    );
    
    # Add object file information
    push @$object_files, $object_file;
  }
  
  return $object_files;
}

sub _runtime_build_precompile_class_source {
  my ($runtime, $class_name, $category) = @_;
  
  my $precompile_source;
  if ($runtime->isa('SPVM::Builder::Runtime')) {
    $precompile_source = $runtime->build_precompile_class_source($class_name);
  }
  elsif ($runtime->isa('SPVM::BlessedObject::Class')) {
    my $basic_type = $runtime->get_basic_type_by_name($class_name);
    
    $precompile_source = $runtime->build_precompile_class_source($basic_type)->to_string;
  }
  else {
    confess "[Unexpected Error]Invalid object type.";
  }
  
  return $precompile_source;
}

sub _runtime_get_class_file {
  my ($runtime, $class_name, $category) = @_;
  
  my $class_file;
  if ($runtime->isa('SPVM::Builder::Runtime')) {
    $class_file = $runtime->get_class_file($class_name, $category);
  }
  elsif ($runtime->isa('SPVM::BlessedObject::Class')) {
    my $basic_type = $runtime->get_basic_type_by_name($class_name);
    
    my $spvm_class_dir = $basic_type->get_class_dir;
    
    my $spvm_class_rel_file = $basic_type->get_class_rel_file;
    
    $class_file = "$spvm_class_dir/$spvm_class_rel_file";
  }
  else {
    confess "[Unexpected Error]Invalid object type.";
  }
  
  return $class_file;
}

sub _runtime_get_method_names {
  my ($runtime, $class_name, $category) = @_;
  
  my $method_names;
  if ($runtime->isa('SPVM::Builder::Runtime')) {
    $method_names = $runtime->get_method_names($class_name, $category);
  }
  elsif ($runtime->isa('SPVM::BlessedObject::Class')) {
    my $basic_type = $runtime->get_basic_type_by_name($class_name);
    
    if ($category eq 'native') {
      $method_names = $basic_type->_get_native_method_names;
    }
    elsif ($category eq 'precompile') {
      $method_names = $basic_type->_get_precompile_method_names;
    }
  }
  else {
    confess "[Unexpected Error]Invalid object type.";
  }
  
  return $method_names;
}

sub link {
  my ($self, $class_name, $object_files, $options) = @_;
  
  unless (@$object_files) {
    return;
  }
  
  my $runtime = $options->{runtime};
  
  # Build directory
  my $build_dir = $self->build_dir;
  if (defined $build_dir) {
    mkpath $build_dir;
  }
  else {
    confess "The \"build_dir\" field must be defined to link the object files for the \"$class_name\" class. Perhaps the setting of the SPVM_BUILD_DIR environment variable is forgotten";
  }
  
  # Config
  my $config = $options->{config};
  unless ($config) {
    confess "Need config option";
  }
  
  my $category = $config->category;
  
  # Force link
  my $force = $self->detect_force($config);
  
  # Link information
  my $link_info = $self->create_link_info($class_name, $object_files, $config, $options);
  
  # Output file
  my $output_file = $config->output_file;
  
  # Execute the callback before this link
  my $before_link_cbs = $config->before_link_cbs;
  for my $before_link_cb (@$before_link_cbs) {
    $before_link_cb->($config, $link_info);
  }
  
  my @object_files = map { "$_" } @{$link_info->object_files};
  my $input_files = [@object_files];
  if (defined $config->file) {
    push @$input_files, $config->file;
  }
  my $need_generate = SPVM::Builder::Util::need_generate({
    force => $force,
    output_file => $output_file,
    input_files => $input_files,
  });
  
  if ($need_generate) {
    # Move temporary dynamic library file to blib directory
    mkpath dirname $output_file;
    
    my $ld = $config->ld;
    
    my $cbuilder_config = {
      ld => $ld,
      lddlflags => '',
      shrpenv => '',
      libpth => '',
      libperl => '',
      
      # "perllibs" should be empty string, but ExtUtils::CBuiler outputs "INPUT()" into 
      # Linker Script File(.lds) when "perllibs" is empty string.
      # This is syntax error in Linker Script File(.lds)
      # For the reason, libm is linked which seems to have no effect.
      perllibs => '-lm',
    };
    
    # Quiet output
    my $quiet = $self->detect_quiet($config);
    
    # ExtUtils::CBuilder object
    my $cbuilder = ExtUtils::CBuilder->new(quiet => 1, config => $cbuilder_config);
    
    my $link_info_output_file = $config->output_file;
    my $link_info_object_files = $link_info->object_files;
    
    my $link_command_args = $link_info->create_ldflags;
    
    my $link_info_object_file_names = [map { $_->to_string; } @$link_info_object_files];
    
    my @tmp_files;
    
    my $output_type = $config->output_type;
    
    # Create a dynamic library
    if ($output_type eq 'dynamic_lib') {
      my $method_names = &_runtime_get_method_names($runtime, $class_name, $category);
      my $dl_func_list = SPVM::Builder::Util::create_dl_func_list($class_name, $method_names, {category => $category});
      
      unless ($quiet) {
        
        my $for_precompile = $category eq 'precompile' ? ' for precompile' : '';
        my $message = "[Generate a dynamic link library for the \"$class_name\" class$for_precompile]";
        warn "$message\n";
        
        my $link_command = $link_info->to_command;
        warn "$link_command\n";
      }
      
      (undef, @tmp_files) = $cbuilder->link(
        objects => $link_info_object_file_names,
        module_name => $class_name,
        lib_file => $link_info_output_file,
        extra_linker_flags => "@$link_command_args",
        dl_func_list => $dl_func_list,
      );
      
    }
    # Create a static library
    elsif ($output_type eq 'static_lib') {
      my @object_files = map { "$_" } @$link_info_object_file_names;
      my @ar_cmd = ('ar', 'rc', $link_info_output_file, @object_files);
      
      unless ($quiet) {
        warn "[Generate a static link library for the \"$class_name\" class]\n";
        
        warn "@ar_cmd\n";
      }
      
      $cbuilder->do_system(@ar_cmd)
        or confess "Can't execute command @ar_cmd";
    }
    # Create an executable file
    elsif ($output_type eq 'exe') {
      unless ($quiet) {
        warn "[Generate an executable file for the \"$class_name\" class]\n";
        
        my $link_command = $link_info->to_command;
        warn "$link_command\n";
      }
      
      (undef, @tmp_files) = $cbuilder->link_executable(
        objects => $link_info_object_file_names,
        module_name => $class_name,
        exe_file => $link_info_output_file,
        extra_linker_flags => "@$link_command_args",
      );
    }
    else {
      confess "Unknown output_type \"$output_type\"";
    }
    
    if ($self->debug) {
      if ($^O eq 'MSWin32') {
        my $def_file;
        my $lds_file;
        for my $tmp_file (@tmp_files) {
          # Remove double quote
          $tmp_file =~ s/^"//;
          $tmp_file =~ s/"$//;
          
          if ($tmp_file =~ /\.def$/) {
            $def_file = $tmp_file;
            $lds_file = $def_file;
            $lds_file =~ s/\.def$/.lds/;
            last;
          }
        }
        if (defined $def_file && -f $def_file) {
          my $def_content = SPVM::Builder::Util::slurp_binary($def_file);
          warn "[$def_file]\n$def_content\n";
        }
        if (defined $lds_file && -f $lds_file) {
          my $lds_content = SPVM::Builder::Util::slurp_binary($lds_file);
          warn "[$lds_file]\n$lds_content\n";
        }
      }
    }
  }
  
  return $output_file;
}

sub create_link_info {
  my ($self, $class_name, $object_files, $config, $options) = @_;
  
  $options ||= {};
  
  my $runtime = $options->{runtime};
  
  my $category = $config->category;
  
  my $output_file = $config->output_file;
  
  my $all_object_files = [@$object_files];
  
  my $output_dir = $config->output_dir;
  
  # Linker
  my $ld = $config->ld;
  
  # Output type
  my $output_type = $config->output_type;
  
  # Libraries
  my $lib_infos = [];
  my $libs = $config->libs;
  my $lib_dirs = $config->lib_dirs;
  for my $lib (@$libs) {
    my $lib_info;
    
    # Library is linked by file path
    my $static;
    my $lib_name;
    my $is_abs;
    if (ref $lib) {
      $static = $lib->is_static;
      $lib_name = $lib->name;
      $is_abs = $lib->is_abs;
      $lib_info = $lib;
    }
    else {
      $lib_name = $lib;
      $lib_info = SPVM::Builder::LibInfo->new(config => $config);
      $lib_info->name($lib_name);
    }
    
    if ($is_abs) {
      my $found_lib_file;
      for my $lib_dir (@$lib_dirs) {
        $lib_dir =~ s|[\\/]$||;
        
        # Search dynamic library
        unless ($static) {
          my $dynamic_lib_file_base = "lib$lib_name.$Config{dlext}";
          my $dynamic_lib_file = "$lib_dir/$dynamic_lib_file_base";
          
          if (-f $dynamic_lib_file) {
            $found_lib_file = $dynamic_lib_file;
            last;
          }
        }
        
        # Search static library
        my $static_lib_file_base = "lib$lib_name.a";
        my $static_lib_file = "$lib_dir/$static_lib_file_base";
        if (-f $static_lib_file) {
          $found_lib_file = $static_lib_file;
          last;
        }
      }
      
      if (defined $found_lib_file) {
        $lib_info->file = $found_lib_file;
      }
    }
    
    push @$lib_infos, $lib_info;
  }
  $config->libs($lib_infos);
  
  # Output file
  unless (defined $output_file) {
    # Dynamic library directory
    unless (defined $output_dir && -d $output_dir) {
      confess "Shared lib directory must be specified for link";
    }
    
    # Dynamic library file
    my $output_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category);
    $output_file = "$output_dir/$output_rel_file";
  }
  
  # Add output file extension
  my $output_file_base = basename $output_file;
  if ($output_file_base =~ /\.precompile$/ || $output_file_base !~ /\./) {
    my $exe_ext;
    
    # Dynamic library
    if ($output_type eq 'dynamic_lib') {
      $exe_ext = ".$Config{dlext}"
    }
    # Static library
    elsif ($output_type eq 'static_lib') {
      $exe_ext = '.a';
    }
    # Executable file
    elsif ($output_type eq 'exe') {
      $exe_ext = $Config{exe_ext};
    }
    
    $output_file .= $exe_ext;
  }
  
  $config->output_file($output_file);
  
  # Optimize
  my $ld_optimize = $config->ld_optimize;
  
  my $link_info = SPVM::Builder::LinkInfo->new(
    class_name => $class_name,
    config => $config,
    object_files => $all_object_files,
  );
  
  return $link_info;
}

sub resource_src_dir_from_class_name {
  my ($self, $class_name) = @_;
  
  my $config_file = SPVM::Builder::Util::search_config_file($class_name);
  
  unless (defined $config_file) {
    my $config_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'config');
    
    confess "A config file \"$config_rel_file\" is not found in (@INC)";
  }
  
  my $config_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'config');
  
  my $resource_src_dir = $config_file;
  $resource_src_dir =~ s|/\Q$config_rel_file\E$||;
  
  return $resource_src_dir;
}

sub get_resource_object_dir_from_class_name {
  my ($self, $class_name) = @_;
  
  my $module_rel_dir = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name);
  
  my $resource_object_dir = SPVM::Builder::Util::create_build_object_path($self->build_dir, "$module_rel_dir.resource");
  
  return $resource_object_dir;
}

sub get_resource_object_dir_from_basic_type_name {
  my ($self, $class_name) = @_;

  my $module_rel_dir = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name);
  
  my $resource_object_dir = SPVM::Builder::Util::create_build_object_path($self->build_dir, "$module_rel_dir.resource");
  
  return $resource_object_dir;
}

1;

=head1 Name

SPVM::Builder::CC - Compilation and Link of Native Class

=head1 Description

The SPVM::Builder::CC class has methods to compile and link a SPVM native class.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
