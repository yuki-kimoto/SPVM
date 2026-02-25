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
  
  my $basic_type = $runtime->get_basic_type_by_name($class_name);
  
  my $class_file = $basic_type->get_class_file;
  
  my $precompile_source = $basic_type->build_precompile_class_source($basic_type);
  
  # Force
  my $force = $self->detect_force;
  
  # Output - Precompile C source file
  my $cc_input_dir = $config->cc_input_dir;
  my $source_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'precompile.c');
  my $source_file = "$cc_input_dir/$source_rel_file";
  
  # Check if generating is needed
  my $need_generate = SPVM::Builder::Util::need_generate({
    force => $force,
    output_file => $source_file,
    input_files => [$class_file],
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
  
  my $no_generate = $compile_info->no_generate;
  
  my $config = $compile_info->config;
  
  # Quiet output
  my $quiet = $self->detect_quiet($config);
  
  my $source_file = $compile_info->source_file;
  
  # Execute compile command
  my $cbuilder = ExtUtils::CBuilder->new(quiet => 1);
  
  my $output_file = $compile_info->output_file;
  
  my $before_compile_cbs = $config->before_compile_cbs;
  for my $before_compile_cb (@$before_compile_cbs) {
    $before_compile_cb->($compile_info->config, $compile_info);
  }
  
  my $config_exe = $config->config_exe;
  
  if ($config_exe) {
    my $before_compile_cbs_global = $config_exe->before_compile_cbs_global;
    for my $before_compile_cb_global (@$before_compile_cbs_global) {
      $before_compile_cb_global->($compile_info->config, $compile_info);
    }
  }
  
  my $cc_cmd = $compile_info->create_command;
  
  unless ($no_generate) {
    mkpath dirname $output_file;
    
    unless ($quiet) {
      
      my $resource_loader_config = $compile_info->config->resource_loader_config;
      
      my $compile_info_category = $compile_info->category;
      
      my $message;
      if ($resource_loader_config) {
        
        my $resource_loader_config_class_name = $resource_loader_config->class_name;
        
        my $resource_loader_config_file = $resource_loader_config->file;
        
        my $resource_class_name = $config->class_name;
        
        my $resource_config_file = $config->file;
        
        $message = "[Compile a source file in $resource_class_name resource. The resource is used from $resource_loader_config_class_name class]";
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
      
      print "@$cc_cmd\n";
    }
    
    $cbuilder->do_system(@$cc_cmd)
      or confess("$source_file file cannnot be compiled by the following command:\n@$cc_cmd\n");
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
  
  $options ||= {};
  
  my $build_dir = $self->builder->build_dir;
  
  unless (defined $build_dir) {
    confess("[Unexpected Error]A build directory must be defined.");
  }
  
  unless (-d $build_dir) {
    confess("[Unexpected Error]A build directory must exists.");
  }
  
  my $is_anon;
  if ($class_name =~ /::anon_/) {
    $is_anon = 1;
  }
  
  # Config
  my $config = $options->{config};
  
  my $runtime = $options->{runtime};
  
  my $is_jit = $config->is_jit;
  
  my $category = $config->category;
  
  my $config_exe = $config->config_exe;
  
  # Native class file
  my $native_class_ext = $config->ext;
  
  if ($category eq 'precompile') {
    my $basic_type = $runtime->get_basic_type_by_name($class_name);
    my $precompile_method_names = $basic_type->get_method_names_by_category($category);
    
    unless (@$precompile_method_names) {
      return [];
    }
  }
  
  my $cc_output_dir = $config->cc_output_dir;
  unless ($cc_output_dir) {
    $cc_output_dir = $self->builder->create_build_object_path;
  }
  
  my $class_file;
  my $basic_type;
  
  eval { $basic_type = $runtime->get_basic_type_by_name($class_name) };
  
  if ($basic_type) {
    $class_file = $basic_type->get_class_file;
  }
  else {
    Carp::confess("$class_name class must be loaded.");
  }
  
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
    unless ($is_anon) {
      $cc_input_dir = SPVM::Builder::Util::get_class_base_dir($class_file, $class_name);
    }
  }
  
  # Check if a config file and an SPVM class file are in the same directory.
  if (defined $config->file) {
    my $config_file = $config->file;
    
    my $config_file_abs = File::Spec->rel2abs($config_file);
    
    my $class_file_cannonpath = File::Spec->rel2abs($class_file);
    
    my $class_file_cannonpath_without_ext = $class_file_cannonpath;
    $class_file_cannonpath_without_ext =~ s/\.spvm$//;
    my $class_file_cannonpath_without_ext_quotemeta = quotemeta $class_file_cannonpath_without_ext;
    
    if (!$config->isa('SPVM::Builder::Config::Exe') && $config_file_abs !~ /^$class_file_cannonpath_without_ext_quotemeta\./) {
      confess("The config file \"$config_file_abs\" is not compatible with the SPVM file \"$class_file_cannonpath\".");
    }
  }
  
  $config->class_name($class_name);
  
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
  
  my $need_compile_resources;
  if ($config->config_exe) {
    if ($class_name eq $config->config_exe->class_name) {
      $need_compile_resources = 1;
    }
    else {
      $need_compile_resources = 0;
    }
  }
  else {
    $need_compile_resources = 1;
  }
  
  if ($need_compile_resources) {
    for my $resource_name (@$resource_names) {
      my $resource = $config->get_resource($resource_name);
      
      # Build native classes
      my $builder_cc_resource = SPVM::Builder::CC->new(
        builder => $self->builder,
        quiet => $self->detect_quiet($config),
        force => $self->detect_force($config),
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
      
      my $resource_object_dir;
      if ($config->config_exe) {
        $resource_object_dir = $self->builder->create_build_object_path;
      }
      else {
        $resource_object_dir = $self->get_resource_object_dir_from_class_name($class_name);
      }
      
      $resource_config->cc_output_dir($resource_object_dir);
      
      my $compile_options = {
        runtime => $runtime,
        config => $resource_config,
      };
      
      my $resource_object_files = $builder_cc_resource->compile_class($resource_class_name, $compile_options);
      push @$object_files, @$resource_object_files;
    }
  }
  
  # Native class source file
  my $native_class_source_file;
  if (defined $cc_input_dir && defined $native_class_ext) {
    my $native_class_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, $native_class_ext);
    $native_class_source_file = "$cc_input_dir/$native_class_rel_file";
  }
  
  my $need_native_class_file;
  if ($native_class_source_file) {
    if (defined $config->is_resource) {
      if ($config->is_resource) {
        $need_native_class_file = 0;
      }
      else {
        if ($config->config_exe && $class_name eq $config->config_exe->class_name) {
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
    if ($config->config_exe) {
      if ($class_name eq $config->config_exe->class_name) {
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
  my $native_src_dir = $config->native_src_dir;
  my $native_source_files = [];
  if ($is_compile_native_source_files) {
    my $native_source_files_base = $config->source_files;
    if (defined $native_src_dir) {
      $native_source_files = [map { "$native_src_dir/$_" } @$native_source_files_base ];
    }
  }
  
  # Compile source files
  my $is_native_class_source_file = 1;
  for my $source_file ($native_class_source_file, @$native_source_files) {
    
    my $current_is_native_class_source_file = $is_native_class_source_file;
    $is_native_class_source_file = 0;
    
    next unless defined $source_file && -f $source_file;
    
    my $object_file_name;
    
    if ($current_is_native_class_source_file) {
      my $object_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, 'o');
      $object_file_name = "$cc_output_dir/$object_rel_file";
    }
    else {
      my $object_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, 'native');
      
      my $object_file_base = $source_file;
      $object_file_base =~ s/^\Q$native_src_dir//;
      $object_file_base =~ s/^[\\\/]//;
      
      $object_file_base =~ s/\.[^\.]+$/.o/;
      $object_file_name = "$cc_output_dir/$object_rel_file/$object_file_base";
      
      mkpath dirname $object_file_name;
    }
    
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
      output_file => $object_file_name,
      source_file => $source_file,
      config => $config,
      category => $compile_info_category,
    );
    
    # Check if object file need to be generated
    my $need_generate;
    {
      my @native_header_files;
      my $native_include_dir = $config->native_include_dir;
      if (defined $native_include_dir && -d $native_include_dir) {
        find(
          {
            wanted => sub {
              my $include_file_name = $File::Find::name;
              if (-f $include_file_name) {
                push @native_header_files, $include_file_name;
              }
            },
            no_chdir => 1,
          },
          $native_include_dir,
        );
      }
      
      # Resource include directories
      my @resource_native_header_files;
      my @resource_config_files;
      my $resource_names = $config->get_resource_names;
      for my $resource_name (@$resource_names) {
        my $resource = $config->get_resource($resource_name);
        my $resource_config = $resource->config;
        
        push @resource_config_files, $resource_config->file;
        
        my $resource_native_include_dir = $resource_config->native_include_dir;
        if (defined $resource_native_include_dir && -d $resource_native_include_dir) {
          find(
            {
              wanted => sub {
                my $resource_native_include_file_name = $File::Find::name;
                if (-f $resource_native_include_file_name) {
                  push @resource_native_header_files, $resource_native_include_file_name;
                }
              },
              no_chdir => 1,
            },
            $resource_native_include_dir,
          );
        }
      }
      
      my $input_files = [$source_file, @native_header_files, @resource_native_header_files, @resource_config_files];
      
      if (defined $config->file) {
        push @$input_files, $config->file;
      };
      
      $need_generate = SPVM::Builder::Util::need_generate({
        force => $force,
        output_file => $object_file_name,
        input_files => $input_files,
      });
    }
    
    # Compile a source file
    $compile_info->no_generate(!$need_generate);
    $self->compile_source_file($compile_info);
    
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

sub get_resource_object_dir_from_class_name {
  my ($self, $class_name) = @_;
  
  my $module_rel_dir = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name);
  
  my $resource_object_dir = $self->builder->create_build_object_path("$module_rel_dir.resource");
  
  return $resource_object_dir;
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
  
  my $force = $self->detect_force($config);
  
  my $link_info = $self->create_link_info($class_name, $object_files, $config);
  
  my $output_file = $config->output_file;
  
  my @object_files = map { "$_" } @{$link_info->object_files};
  
  my $input_files = [@object_files];
  
  my $need_generate = SPVM::Builder::Util::need_generate({
    force => $force,
    output_file => $output_file,
    input_files => $input_files,
  });
  
  $link_info->no_generate(!$need_generate);
  
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
  
  if ($need_generate) {
    
    mkpath dirname $link_info_output_file;
    
    # Create a dynamic library
    if ($output_type eq 'dynamic_lib') {
      my $basic_type = $runtime->get_basic_type_by_name($class_name);
      my $method_names = $basic_type->get_method_names_by_category($category);
      
      unless ($quiet) {
        my $for_precompile = $category eq 'precompile' ? ' for precompile' : '';
        my $message = "[Generate Dynamic Link Library for $class_name class$for_precompile]";
        print "$message\n";
        
        my $link_command = $link_info->to_command;
        print "$link_command\n";
      }
      
      my $dl_func_list = SPVM::Builder::Util::create_dl_func_list($class_name, $method_names, {category => $category});
      
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
        
        my $link_command = $link_info->to_command;
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
    elsif ($output_type eq 'static_lib') {
      $exe_ext = '.a';
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
