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
use Time::HiRes ();

use SPVM::Builder::Util;
use SPVM::Builder::CompileInfo;
use SPVM::Builder::ObjectFileInfo;
use SPVM::Builder::LinkInfo;
use SPVM::Builder::Native::BasicType;

# Fields
sub builder {
  my $self = shift;
  if (@_) {
    $self->{builder} = $_[0];
    return $self;
  }
  else {
    return $self->{builder};
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
  
  return $self;
}

# Instance Methods
sub detect_force {
  my ($self, $config) = @_;
  
  unless ($config) {
    confess("The config \$config must be define.");
  }
  my $force;
  
  if (defined $self->force) {
    $force = $self->force;
  }
  elsif (defined $config->force) {
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

sub compile_source_file {
  my ($self, $compile_info, $options) = @_;
  
  my $config = $compile_info->config;
  
  my $quiet = $self->detect_quiet($config);
  
  my $cbuilder = ExtUtils::CBuilder->new(quiet => 1);
  
  my $source_rel_file = $compile_info->source_rel_file;
  
  unless (defined $source_rel_file) {
    confess("\$source_rel_file must be defined.");
  }
  
  my $cc_input_dir = $config->cc_input_dir // $config->get_base_dir;
  
  my $source_file = $compile_info->source_file;
  my $source_file_from_rel_file = "$cc_input_dir/$source_rel_file";
  unless ($source_file eq $source_file_from_rel_file) {
    confess("\$source_file '$source_file' does not equel \$source_file_from_rel_file '$cc_input_dir    /    $source_rel_file'.");
  }
  
  my $object_rel_file = $source_rel_file;
  $object_rel_file =~ s/\.[^\.]+$/.o/;
  my $cc_output_dir = $self->builder->create_build_object_path;
  
  my $output_file = "$cc_output_dir/$object_rel_file";
  
  mkpath dirname $output_file;
  
  $compile_info->output_file($output_file);
  
  my $before_compile_cbs = $config->before_compile_cbs;
  for my $before_compile_cb (@$before_compile_cbs) {
    $before_compile_cb->($compile_info->config, $compile_info);
  }
  
  my $config_global = $config->config_global;
  
  if ($config_global) {
    for my $before_compile_cb (@{$config_global->before_compile_cbs}) {
      $before_compile_cb->($compile_info->config, $compile_info);
    }
  }
  
  my $cc_cmd = $compile_info->create_command;
  my $cc_cmd_string = "@$cc_cmd";
  
  my $cc_version = $config->cc_version;
  
  my $force = $self->detect_force($config);
  
  my $dependent_files = $options->{dependent_files};
  my $ninja = $self->builder->ninja;
  my $ninja_entry = {
    command => $cc_cmd_string,
    command_version => $cc_version,
    dependent_files => $dependent_files,
    output_file => $output_file,
  };
  my $need_generate = $force || $ninja->need_generate($ninja_entry);
  
  if ($need_generate) {
    mkpath dirname $output_file;
    
    unless ($quiet) {
      my $compile_info_category = $compile_info->category;
      my $message;
      if ($config->is_resource) {
        my $resource_class_name = $config->class_name;
        $message = "[Compile a source file in $resource_class_name resource.";
      }
      else {
        my $config_class_name = $config->class_name;
        my $config_file = $config->file;
        
        if ($compile_info_category eq 'bootstrap') {
          $message = "[Compile Bootstrap File]";
        }
        elsif ($compile_info_category eq 'spvm_core') {
          $message = "[Compile SPVM Source File]";
        }
        elsif ($compile_info_category eq 'native_source') {
          $message = "[Compile Native Source File for $config_class_name class using the config file \"$config_file\"]";
        }
        elsif ($compile_info_category eq 'native_class') {
          $message = "[Compile Native Class File for $config_class_name class using the config file \"$config_file\"]";
        }
        elsif ($compile_info_category eq 'precompile_class') {
          $message = "[Compile Precompile Class File for $config_class_name class]";
        }
        else {
          confess("[Unexpected Error]Invalid compile info category \"$compile_info_category\".");
        }
      }
      
      print "$message\n";
      print "$cc_cmd_string\n";
    }
    
    my $start_time = int(Time::HiRes::time() * 1000);
    $cbuilder->do_system(@$cc_cmd)
      or confess("$source_file file cannnot be compiled by the following command:\n$cc_cmd_string\n");
    my $end_time = int(Time::HiRes::time() * 1000);
    
    my $command_hash = $ninja->create_command_hash($ninja_entry);
    
    unless (-f $output_file) {
      confess("The output file '$output_file' does not exist.");
    }
    
    my $mtime = int((Time::HiRes::stat $output_file)[9] * 1000);
    
    my $log_entry = {
      output_file  => $output_file,
      command_hash => $command_hash,
      start_time   => $start_time,
      end_time     => $end_time,
      mtime => $mtime,
    };
    $ninja->add_log($log_entry);
  }
}

sub compile_class {
  my ($self, $class_name, $options) = @_;
  
  unless (defined $class_name) {
    confess("A class name must be defined.");
  }
  
  if (ref $class_name) {
    confess("[Unexpected Error]A class name must be non-reference.");
  }
  
  my $build_dir = $self->builder->build_dir;
  
  unless (defined $build_dir) {
    confess("[Unexpected Error]A build directory must be defined.");
  }
  
  unless (-d $build_dir) {
    confess("[Unexpected Error]A build directory must exists.");
  }
  
  $options ||= {};
  
  my $config = $options->{config};
  
  $config->class_name($class_name);
  
  my $object_files = [];
  
  my $resource_object_files = $self->compile_resources($class_name, $options);
  push @$object_files, @$resource_object_files;
  
  my $native_object_files = $self->compile_native_class($class_name, $options);
  push @$object_files, @$native_object_files;
  
  return $object_files;
}

sub compile_resources {
  my ($self, $class_name, $options) = @_;
  
  my $config = $options->{config};
  
  my $runtime = $options->{runtime};
  
  my $object_files = [];
  
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
  
  my $need_compile_resources;
  if ($config->config_global) {
    if ($class_name eq $config->config_global->class_name) {
      $need_compile_resources = 1;
    }
    else {
      $need_compile_resources = 0;
    }
  }
  else {
    if ($config->is_resource) {
      $need_compile_resources = 0;
    }
    else {
      $need_compile_resources = 1;
    }
  }
  
  if ($need_compile_resources) {
    for my $resource_name (@$resource_names) {
      my $resource = $config->get_resource($resource_name);
      
      my $resource_class_name = $resource->class_name;
      my $resource_config = $resource->config;
      
      $resource_config->add_include_dir(@$resource_include_dirs);
      
      my $compile_options = {
        runtime => $runtime,
        config => $resource_config,
      };
      
      my $builder_cc_resource = SPVM::Builder::CC->new(
        builder => $self->builder,
        quiet => $self->detect_quiet($config),
        force => $self->detect_force($config),
      );
      
      my $resource_object_files = $builder_cc_resource->compile_class($resource_class_name, $compile_options);
      push @$object_files, @$resource_object_files;
    }
  }
  
  return $object_files;
}

sub compile_native_class {
  my ($self, $class_name, $options) = @_;
  
  my $config = $options->{config};
  
  my $is_cc_config = $config->isa('SPVM::Builder::Config') ? 1 : 0;
  unless ($is_cc_config) {
    return [];
  }
  
  my $runtime = $options->{runtime};
  my $native_class_ext = $config->ext;
  
  my $basic_type = $runtime->get_basic_type_by_name($class_name);
  
  # Check if a config file and an loaded SPVM class file are in the same directory.
  my $class_file = $basic_type->get_class_file;
  if (defined $config->file) {
    my $config_file_abs = File::Spec->rel2abs($config->file);
    my $class_file_abs  = File::Spec->rel2abs($class_file);
    
    my $config_dir  = dirname($config_file_abs);
    my $config_base = basename($config_file_abs);
    $config_base =~ s/\..*$//;
    
    my $class_dir  = dirname($class_file_abs);
    my $class_base = basename($class_file_abs);
    $class_base =~ s/\..*$//;
    
    unless ($config_dir eq $class_dir && $config_base eq $class_base) {
      confess("The config file \"$config_file_abs\" is not compatible with the SPVM file \"$class_file_abs\".");
    }
  }
  
  my $category = $config->category;
  
  if ($category eq 'precompile') {
    my $precompile_method_names = $basic_type->get_method_names_by_category($category);
    
    unless (@$precompile_method_names) {
      return [];
    }
  }
  
  my $object_files = [];
  
  my $cc_input_dir;
  if ($category eq 'precompile') {
    
    $cc_input_dir = $self->builder->create_build_src_path;
    
    my $config_precompile_class_source = $config->clone;
    
    $config_precompile_class_source->cc_input_dir($cc_input_dir);
    
    $self->build_precompile_class_source_file(
      $class_name,
      {
        config => $config_precompile_class_source,
        runtime => $runtime,
      }
    );
  }
  elsif ($category eq 'native') {
    if ($is_cc_config) {
      $cc_input_dir = SPVM::Builder::Util::get_class_base_dir($class_file, $class_name);
    }
  }
  $config->cc_input_dir($cc_input_dir);
  
  # Native class source file
  my $native_class_source_file;
  my $native_class_rel_file;
  if (defined $cc_input_dir && defined $native_class_ext) {
    $native_class_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, $native_class_ext);
    $native_class_source_file = "$cc_input_dir/$native_class_rel_file";
  }
  
  my $need_native_class_file;
  if ($native_class_source_file) {
    if (defined $config->is_resource) {
      if ($config->is_resource) {
        $need_native_class_file = 0;
      }
      else {
        if ($config->config_global && $class_name eq $config->config_global->class_name) {
          $need_native_class_file = 0;
        }
        else {
          $need_native_class_file = 1;
        }
      }
    }
    else {
      $need_native_class_file = 1;
    }
  }
  else {
    $need_native_class_file = 0;
  }
  
  if ($need_native_class_file) {
    unless (-f $native_class_source_file) {
      Carp::cluck("[Warning]Can't find native class source file $native_class_source_file. If this class is a resource class, set is_resource field to 1 to suppress this warning.");
    }
  }
  
  my $is_resource;
  if (defined $config->is_resource) {
    $is_resource = $config->is_resource;
  }
  else {
    $is_resource = !(defined $native_class_source_file && -f $native_class_source_file);
  }
  
  # For executable files, the resources are compiled in the executable's configuration file, so we don't compile them here.
  my $is_compile_native_source_files;
  if ($is_resource) {
    if ($config->config_global) {
      if ($class_name eq $config->config_global->class_name) {
        $is_compile_native_source_files = 1;
      }
      else {
        $is_compile_native_source_files = 0;
      }
    }
    else {
      $is_compile_native_source_files = 1;
    }
  }
  else {
    $is_compile_native_source_files = 1;
  }
  
  # Native source files
  my $native_source_rel_dir = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, 'native');
  $native_source_rel_dir .= '/src';

  my $native_src_dir = $config->native_src_dir;
  my $native_source_files = [];
    my $native_source_files_base = $config->source_files;
  if ($is_compile_native_source_files) {
    $native_source_files = [map { "$native_src_dir/$_" } @$native_source_files_base ];
  }
  
  # Compile source files
  my $is_native_class_source_file = 1;
  my @source_file_infos;
  if ($native_class_source_file) {
    push @source_file_infos, {is_native_class_source_file => 1, source_rel_file => $native_class_rel_file};
  }
  if ($is_compile_native_source_files) {
    push @source_file_infos, map { {source_rel_file => SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, "native/src/$_")} } @$native_source_files_base;
  }
  
  for my $source_file_info (@source_file_infos) {
    
    my $current_is_native_class_source_file = $source_file_info->{is_native_class_source_file};
    my $source_rel_file = $source_file_info->{source_rel_file};
    my $source_file = "$cc_input_dir/$source_rel_file";
    
    next unless defined $source_file && -f $source_file;
    
    # Check if object file need to be generated
    my $native_include_dir = $config->native_include_dir;
    
    # Resource include directories
    my @resource_naitve_include_dirs;
    my $resource_names = $config->get_resource_names;
    for my $resource_name (@$resource_names) {
      my $resource = $config->get_resource($resource_name);
      my $resource_config = $resource->config;
      
      my $resource_native_include_dir = $resource_config->native_include_dir;
      push @resource_naitve_include_dirs, $resource_native_include_dir;
    }
    
    my $compile_source_file_options = {
      dependent_files => [$source_file, $native_include_dir, @resource_naitve_include_dirs],
    };
    
    my $compile_info_category;
    if ($category eq 'precompile') {
      $compile_info_category = 'precompile_class';
    }
    elsif ($category eq 'native') {
      if ($current_is_native_class_source_file) {
        $compile_info_category = 'native_class';
      }
      else {
        $compile_info_category = 'native_source';
      }
    }
    
    my $compile_info = SPVM::Builder::CompileInfo->new(
      source_file => $source_file,
      source_rel_file => $source_rel_file,
      config => $config,
      category => $compile_info_category,
    );
    
    # Compile a source file
    $self->compile_source_file($compile_info, $compile_source_file_options);
    
    # Object file information
    my $compile_info_cc = $compile_info->{cc};
    my $compile_info_ccflags = $compile_info->{ccflags};
    my $object_file = SPVM::Builder::ObjectFileInfo->new(
      file => $compile_info->output_file,
      compile_info => $compile_info,
    );
    
    # Add object file information
    push @$object_files, $object_file;
  }
  
  return $object_files;
}

sub build_precompile_class_source_file {
  my ($self, $class_name, $options) = @_;
  
  my $config = $options->{config};
  
  my $runtime = $options->{runtime};
  
  my $basic_type = $runtime->get_basic_type_by_name($class_name);
  
  my $class_file = $basic_type->get_class_file;
  
  my $precompile_source = $basic_type->build_precompile_class_source($basic_type);
  
  # Force
  my $force = $self->detect_force($config);
  
  # Output - Precompile C source file
  my $cc_input_dir = $config->cc_input_dir;
  my $source_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'precompile.c');
  my $source_file = "$cc_input_dir/$source_rel_file";
  
  # Generate precompile C source file
  mkpath dirname $source_file;
  open my $fh, '>', $source_file
    or die "Can't create $source_file";
  
  binmode $fh;
  print $fh $precompile_source;
  close $fh;
}

sub link {
  my ($self, $class_name, $object_files, $options) = @_;
  
  unless (defined $class_name) {
    confess("A class name must be defined.");
  }
  
  if (ref $class_name) {
    confess("[Unexpected Error]A class name must be non-reference.");
  }
  
  unless (@$object_files) {
    return;
  }
  
  my $runtime = $options->{runtime};
  
  my $build_dir = $self->builder->build_dir;
  
  unless (defined $build_dir) {
    confess("[Unexpected Error]A build directory must be defined.");
  }
  
  unless (-d $build_dir) {
    confess("[Unexpected Error]A build directory must exists.");
  }
  
  my $config = $options->{config};
  
  unless ($config) {
    confess("[Unexpected Error]A config must be defined.");
  }
  
  my $category = $config->category;
  
  my $link_info = $self->create_link_info($class_name, $object_files, $config);
  
  my $output_file = $config->output_file;
  
  my @object_files = map { "$_" } @{$link_info->object_files};
  
  unless ($config->isa('SPVM::Builder::Config::Linker')) {
    confess("[Unexpected Error]The config must be an SPVM::Builder::Config object");
  }
  
  my $hint_cc = $config->hint_cc;
  my $ld = $config->ld;
  
  my $cbuilder_config = {
    cc => $hint_cc,
    ld => $ld,
    lddlflags => '',
    shrpenv => '',
    libpth => '',
    libperl => '',
    # On Windows/gcc(MinGW) "perllibs" should be empty string, but ExtUtils::CBuiler outputs "INPUT()" into 
    # Linker Script File(.lds) when "perllibs" is empty string.
    # This is syntax error in Linker Script File(.lds)
    # For the reason, libm is linked which seems to have no effect.
    perllibs => '-lm',
  };
  
  my $quiet = $self->detect_quiet($config);
  
  my $cbuilder = ExtUtils::CBuilder->new(quiet => 1, config => $cbuilder_config);
  
  my $link_info_output_file = $config->output_file;
  
  my $link_info_object_files = $link_info->object_files;
  
  my $link_info_object_file_names = [map { $_->to_string; } @$link_info_object_files];
  
  my $link_info_ldflags = $link_info->create_ldflags;
  
  my $output_type = $config->output_type;
  
  my @link_tmp_files;
  
  my $before_link_cbs = $config->before_link_cbs;
  for my $before_link_cb (@$before_link_cbs) {
    $before_link_cb->($link_info->config, $link_info);
  }
  
  my $ld_version = $config->ld_version;
  
  my $force = $self->detect_force($config);
  
  my $ninja_entry = {
    command => $link_info->to_command,
    command_version => $ld_version,
    force => $force,
    output_file => $output_file,
    dependent_files => [@object_files],
  };
  my $need_generate = $force || $self->builder->ninja->need_generate($ninja_entry);
  
  if ($need_generate) {
    mkpath dirname $link_info_output_file;
    
    # Create a dynamic library
    my $start_time = int(Time::HiRes::time() * 1000);
    my $link_command = $link_info->to_command;
    if ($output_type eq 'dynamic_lib') {
      my $basic_type = $runtime->get_basic_type_by_name($class_name);
      
      # Get normal methods
      my $method_names = $basic_type->get_method_names_by_category($category);
      
      # Create the dynamic link function list for the class
      my $dl_func_list = SPVM::Builder::Util::create_dl_func_list($class_name, $method_names, {category => $category});
      
      # Get anon methods from anon basic types
      my $anon_basic_type_names = $basic_type->get_anon_basic_type_names;
      for my $anon_basic_type_name (@$anon_basic_type_names) {
        my $anon_basic_type = $runtime->get_basic_type_by_name($anon_basic_type_name);
        my $anon_method_names = $anon_basic_type->get_method_names_by_category($category);
        
        # Create the dynamic link function list for each anon class and merge it
        my $anon_dl_func_list = SPVM::Builder::Util::create_dl_func_list($anon_basic_type_name, $anon_method_names, {category => $category});
        push @$dl_func_list, @$anon_dl_func_list;
      }
      
      unless ($quiet) {
        my $for_precompile = $category eq 'precompile' ? ' for precompile' : '';
        my $message = "[Generate Dynamic Link Library for $class_name class$for_precompile]";
        print "$message\n";
        
        print "$link_command\n";
      }
      
      (undef, @link_tmp_files) = $cbuilder->link(
        objects => $link_info_object_file_names,
        module_name => $class_name,
        lib_file => $link_info_output_file,
        extra_linker_flags => "@$link_info_ldflags",
        dl_func_list => $dl_func_list,
      );
    }
    # Create an executable file
    elsif ($output_type eq 'exe') {
      unless ($quiet) {
        print "[Generate Executable File \"$link_info_output_file\"]\n";
        
        print "$link_command\n";
      }
      
      (undef, @link_tmp_files) = $cbuilder->link_executable(
        objects => $link_info_object_file_names,
        module_name => $class_name,
        exe_file => $link_info_output_file,
        extra_linker_flags => "@$link_info_ldflags",
      );
    }
    else {
      confess("Unknown output_type \"$output_type\"");
    }
    
    my $end_time = int(Time::HiRes::time() * 1000);
    
    my $ninja = $self->builder->ninja;
    my $command_hash = $ninja->create_command_hash($ninja_entry);
    
    unless (-f $link_info_output_file) {
      confess("The output file '$link_info_output_file' does not exist.");
    }
    
    my $mtime = int((Time::HiRes::stat $link_info_output_file)[9] * 1000);
    
    my $log_entry = {
      output_file  => $link_info_output_file,
      command_hash => $command_hash,
      start_time   => $start_time,
      end_time     => $end_time,
      mtime => $mtime,
    };
    $ninja->add_log($log_entry);
    
    if ($self->debug) {
      if ($^O eq 'MSWin32') {
        my $def_file;
        my $lds_file;
        for my $tmp_file (@link_tmp_files) {
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
          print "[$def_file]\n$def_content\n";
        }
        if (defined $lds_file && -f $lds_file) {
          my $lds_content = SPVM::Builder::Util::slurp_binary($lds_file);
          print "[$lds_file]\n$lds_content\n";
        }
      }
    }
  }
  
  # after_link_cbs
  my $after_link_cbs = $config->after_link_cbs;
  for my $after_link_cb (@$after_link_cbs) {
    $after_link_cb->($link_info->config, $link_info);
  }
  
  return $output_file;
}

sub create_link_info {
  my ($self, $class_name, $object_files, $config) = @_;
  
  my $category = $config->category;
  
  my $output_file = $config->output_file;
  
  my $output_dir = $config->output_dir;
  
  my $build_dir = $self->builder->build_dir;
  
  my $ld = $config->ld;
  
  my $output_type = $config->output_type;
  
  # Output file
  unless (defined $output_file) {
    unless (defined $output_dir) {
      my $is_jit = $config->is_jit;
      if ($is_jit) {
        $output_dir = $self->builder->create_build_lib_path;
      }
      else {
        confess("[Unexpected Error]A output directory must exists.");
      }
    }
    
    my $output_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category);
    $output_file = "$output_dir/$output_rel_file";
  }
  
  # Output file extension
  my $output_file_base = basename $output_file;
  if ($output_file_base =~ /\.precompile$/ || $output_file_base !~ /\./) {
    my $exe_ext;
    
    if ($output_type eq 'dynamic_lib') {
      $exe_ext = ".$Config{dlext}"
    }
    elsif ($output_type eq 'exe') {
      $exe_ext = $Config{exe_ext};
    }
    
    $output_file .= $exe_ext;
  }
  
  $config->output_file($output_file);
  
  my $link_info = SPVM::Builder::LinkInfo->new(
    class_name => $class_name,
    config => $config,
    object_files => $object_files,
  );
  
  return $link_info;
}

1;

=head1 Name

SPVM::Builder::CC - Compilation and Link of Native Class

=head1 Description

The SPVM::Builder::CC class has methods to compile and link an SPVM native class.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
