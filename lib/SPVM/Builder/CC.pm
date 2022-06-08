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

use SPVM::Builder;
use SPVM::Builder::Util;
use SPVM::Builder::Config;
use SPVM::Builder::ObjectFileInfo;
use SPVM::Builder::LinkInfo;
use SPVM::Builder::Resource;

sub category {
  my $self = shift;
  if (@_) {
    $self->{category} = $_[0];
    return $self;
  }
  else {
    return $self->{category};
  }
}

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

sub global_cc_each {
  my $self = shift;
  if (@_) {
    $self->{global_cc_each} = $_[0];
    return $self;
  }
  else {
    return $self->{global_cc_each};
  }
}

sub global_ccflags_each {
  my $self = shift;
  if (@_) {
    $self->{global_ccflags_each} = $_[0];
    return $self;
  }
  else {
    return $self->{global_ccflags_each};
  }
}

sub global_optimize_each {
  my $self = shift;
  if (@_) {
    $self->{global_optimize_each} = $_[0];
    return $self;
  }
  else {
    return $self->{global_optimize_each};
  }
}

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  if ($ENV{SPVM_CC_DEBUG}) {
    $self->{debug} = 1;
  }
  
  if ($ENV{SPVM_CC_FORCE}) {
    $self->{force} = 1;
  }
  
  return bless $self, $class;
}

sub build_dynamic_lib_runtime {
  my ($self, $class_name) = @_;

  my $category = $self->category;
  
  # Build directory
  my $build_dir = $self->builder->build_dir;
  if (defined $build_dir) {
    mkpath $build_dir;
  }
  else {
    confess "SPVM_BUILD_DIR environment variable must be set for build $category method in runtime";
  }
  
  # Source directory
  my $build_src_dir;
  if ($category eq 'precompile') {
    $build_src_dir = $self->builder->create_build_src_path;
    mkpath $build_src_dir;
    
    $self->create_precompile_source_file(
      $class_name,
      {
        output_dir => $build_src_dir,
      }
    );
  }
  elsif ($category eq 'native') {
    my $module_file = $self->builder->get_module_file($class_name);
    $build_src_dir = SPVM::Builder::Util::remove_class_part_from_file($module_file, $class_name);
  }
  
  # Object directory
  my $build_object_dir = $self->builder->create_build_object_path;
  mkpath $build_object_dir;
  
  # Lib directory
  my $build_lib_dir = $self->builder->create_build_lib_path;
  mkpath $build_lib_dir;
  
  my $build_dynamic_lib_file = $self->build_dynamic_lib(
    $class_name,
    {
      compile_input_dir => $build_src_dir,
      compile_output_dir => $build_object_dir,
      link_output_dir => $build_lib_dir,
    }
  );
  
  return $build_dynamic_lib_file;
}

sub build_dynamic_lib_dist {
  my ($self, $class_name) = @_;
  
  my $category = $self->category;
  
  my $build_src_dir;
  if ($category eq 'precompile') {
    $build_src_dir = $self->builder->create_build_src_path;
    mkpath $build_src_dir;

    $self->create_precompile_source_file(
      $class_name,
      {
        output_dir => $build_src_dir,
      }
    );
  }
  elsif ($category eq 'native') {
    $build_src_dir = 'lib';
  }

  my $build_object_dir = $self->builder->create_build_object_path;
  mkpath $build_object_dir;
  
  my $build_lib_dir = 'blib/lib';
  
  
  $self->build_dynamic_lib(
    $class_name,
    {
      compile_input_dir => $build_src_dir,
      compile_output_dir => $build_object_dir,
      link_output_dir => $build_lib_dir,
    }
  );
}

sub build_dynamic_lib {
  my ($self, $class_name, $opt) = @_;
  
  # Compile source file and create object files
  my $compile_options = {};
  $compile_options->{input_dir} = $opt->{compile_input_dir};
  $compile_options->{output_dir} = $opt->{compile_output_dir};
  my $object_files = $self->compile($class_name, $compile_options);
  
  # Link object files and create shared library
  my $link_options = {};
  $link_options->{output_dir} = $opt->{link_output_dir};
  my $build_dynamic_lib_file = $self->link(
    $class_name,
    $object_files,
    $link_options
  );
  
  return $build_dynamic_lib_file;
}

sub resource_src_dir_from_class_name {
  my ($self, $class_name) = @_;

  my $config_file_base = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'config');
  my $config_file;
  for my $inc (@INC) {
    my $config_file_tmp = "$inc/$config_file_base";
    if (-f $config_file_tmp) {
      $config_file = $config_file_tmp;
      last;
    }
  }
  unless (defined $config_file) {
    confess "Can't find resource config file $config_file_base in @INC";
  }
  
  my $config_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'config');
  
  my $input_dir = $config_file;
  $input_dir =~ s|/\Q$config_rel_file\E$||;
  
  return $input_dir;
}

sub get_resource_object_dir_from_class_name {
  my ($self, $class_name) = @_;

  my $class_rel_dir = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name);
  
  my $resource_object_dir = $self->builder->create_build_object_path("$class_rel_dir.resource");
  
  return $resource_object_dir;
}

sub get_config_file_from_class_name {
  my ($self, $class_name) = @_;
  
  my $config_file_base = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'config');
  my $config_file;
  for my $inc (@INC) {
    my $config_file_tmp = "$inc/$config_file_base";
    if (-f $config_file_tmp) {
      $config_file = $config_file_tmp;
      last;
    }
  }
  unless (defined $config_file) {
    confess "Can't find resource config file $config_file_base in @INC";
  }
  
  return $config_file;
}

sub compile {
  my ($self, $class_name, $opt) = @_;

  # Category
  my $category = $self->category;

  # Build directory
  my $build_dir = $self->builder->build_dir;
  if (defined $build_dir) {
    mkpath $build_dir;
  }
  else {
    confess "Build directory is not specified. Maybe forget to set \"SPVM_BUILD_DIR\" environment variable?";
  }
  
  # Source directory
  my $input_dir = $opt->{input_dir};
  
  # Object directory
  my $output_dir = $opt->{output_dir};
  unless (defined $output_dir && -d $output_dir) {
    confess "Temporary directory must exists for " . $self->category . " build";
  }
  
  # Module file
  my $module_file = $self->builder->get_module_file($class_name);
  unless (defined $module_file) {
    my $config_file = $self->get_config_file_from_class_name($class_name);
    if ($config_file) {
      $module_file = $config_file;
      $module_file =~ s/\.config$/\.spvm/;
    }
    else {
      confess "\"$module_file\" module is not loaded";
    }
  }
  
  # Config
  my $config = $opt->{config};
  unless ($config) {
    my $config_file = $module_file;
    $config_file =~ s/\.spvm$/.config/;
    if ($category eq 'native') {
      # Config file
      if (-f $config_file) {
        $config = SPVM::Builder::Util::load_config($config_file);
        $config->file($config_file);
      }
      else {
        my $error = $self->_error_message_find_config($config_file);
        confess $error;
      }
    }
    elsif ($category eq 'precompile') {
      $config = SPVM::Builder::Config->new_gnu99;
    }
    else { confess 'Unexpected Error' }
  }
  
  # Resource directory
  my $resource_dir = $module_file;
  $resource_dir =~ s/\.spvm$//;
  $resource_dir .= '.native';
  
  # Runtime include directries
  my @runtime_include_dirs;

  # Include directory
  my $resource_include_dir = "$resource_dir/include";
  
  # Add native include dir
  push @runtime_include_dirs, $resource_include_dir;
  
  if ($category eq 'native') {
    
    my $resources = $config->resources;
    for my $resource (@$resources) {
      my $config_file = $self->get_config_file_from_class_name($resource);
      
      my $include_dir = $config_file;
      $include_dir =~ s|\.config$|\.native/include|;
      
      push @runtime_include_dirs, $include_dir;
    }
  }
  unshift @{$config->include_dirs}, @runtime_include_dirs;

  # Source directory
  my $resource_src_dir = "$resource_dir/src";
  
  # Quiet output
  my $quiet = $config->quiet;

  # Debug mode
  if ($self->debug) {
    $quiet = 0;
  }
  else {
    if (defined $self->quiet) {
      $quiet = $self->quiet;
    }
  }
  
  my $is_resource = $opt->{is_resource};
  my $native_module_file;
  unless ($is_resource) {
    # Native module file
    my $native_module_ext = $config->ext;
    unless (defined $native_module_ext) {
      confess "Source extension is not specified";
    }
    my $native_module_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, $native_module_ext);
    $native_module_file = "$input_dir/$native_module_rel_file";
    
    unless (-f $native_module_file) {
      confess "Can't find source file $native_module_file";
    }
  }
  
  # Resource source files
  my $source_files = $config->source_files;

  # Native source files
  my $resource_src_files = [map { "$resource_src_dir/$_" } @$source_files ];

  # Native header files
  my @include_file_names;
  if (-d $resource_include_dir) {
    find(
      {
        wanted => sub {
          my $include_file_name = $File::Find::name;
          if (-f $include_file_name) {
            push @include_file_names, $include_file_name;
          }
        },
        no_chdir => 1,
      },
      $resource_include_dir,
    );
  }
  
  my $mod_time_config_file;
  if (defined $config->file && -f $config->file) {
     $mod_time_config_file = (stat($config->file))[9];
  }
  else {
    $mod_time_config_file = 0;
  }
  my $mod_time_header_files_max = 0;
  for my $header_file (@include_file_names) {
    my $mod_time_header_file = (stat($header_file))[9];
    if ($mod_time_header_file > $mod_time_header_files_max) {
      $mod_time_header_files_max = $mod_time_header_file;
    }
  }

  # Compile source files
  my $object_file_infos = [];
  my $is_native_module = 1;
  for my $source_file ($native_module_file, @$resource_src_files) {
    my $cur_is_native_module = $is_native_module;
    $is_native_module = 0;
    
    next unless defined $source_file;
    
    my $object_file;
    # Native object file name
    if ($cur_is_native_module) {
      my $object_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, 'o');
      $object_file = "$output_dir/$object_rel_file";
    }
    # SPVM method object file name
    else {
      my $object_rel_file = SPVM::Builder::Util::convert_class_name_to_category_rel_file($class_name, $category, 'native');
      
      my $object_file_base = $source_file;
      $object_file_base =~ s/^\Q$resource_src_dir//;
      $object_file_base =~ s/^[\\\/]//;
      
      $object_file_base =~ s/\.[^\.]+$/.o/;
      $object_file = "$output_dir/$object_rel_file/$object_file_base";
      
      my $output_dir = dirname $object_file;
      mkpath $output_dir;
    }
    
    # Do compile. This is same as make command
    my $need_generate;
    my $input_files = [$source_file, @include_file_names];
    if (defined $config->file) {
      push @$input_files, $config->file;
    };
    if ($cur_is_native_module) {
      my $module_file = $source_file;
      $module_file =~ s/\.[^\/\\]+$//;
      $module_file .= '.spvm';
      
      push @$input_files, $module_file;
    }
    $need_generate = SPVM::Builder::Util::need_generate({
      force => $self->force || $config->force,
      output_file => $object_file,
      input_files => $input_files,
    });

    my $compile_info = $self->create_compile_command_info({class_name => $class_name, config => $config, output_file => $object_file, source_file => $source_file});

    my $cc_cmd = $self->create_compile_command($compile_info);
    
    my $compile_info_cc = $compile_info->{cc};
    my $compile_info_ccflags = $compile_info->{ccflags};
    
    if ($need_generate) {
      my $class_rel_dir = SPVM::Builder::Util::convert_class_name_to_rel_dir($class_name);
      my $work_output_dir = "$output_dir/$class_rel_dir";
      mkpath dirname $object_file;
      
      # Execute compile command
      my $cbuilder = ExtUtils::CBuilder->new(quiet => 1);
      $cbuilder->do_system(@$cc_cmd)
        or confess "Can't compile $source_file: @$cc_cmd";
      unless ($quiet) {
        print "@$cc_cmd\n";
      }
    }
    
    my $object_file_info = SPVM::Builder::ObjectFileInfo->new(
      object_file => $object_file,
      class_name => $class_name,
      source_file => $source_file,
      cc => $compile_info_cc,
      ccflags => $compile_info_ccflags,
      config => $config,
      source_type => $cur_is_native_module ? 'native_module' : 'resource',
    );
    
    push @$object_file_infos, $object_file_info;
  }
  
  return $object_file_infos;
}

sub create_compile_command {
  my ($self, $compile_info) = @_;

  my $cc = $compile_info->{cc};
  my $ccflags = $compile_info->{ccflags};
  my $object_file = $compile_info->{object_file};
  my $source_file = $compile_info->{source_file};
  
  my $cc_cmd = [$cc, '-c', @$ccflags, '-o', $object_file, $source_file];
  
  return $cc_cmd;
}

sub create_compile_command_info {
  my ($self, $options) = @_;

  unless ($options) {
    $options = {};
  }
  
  my $class_name = $options->{class_name};
  
  my $config = $options->{config};
  my $output_file = $options->{output_file};
  my $source_file = $options->{source_file};
  
  my $cc_each = $config->cc_each;
  my $cc;
  if ($cc_each) {
    $cc = $cc_each->($config, {class_name => $class_name, source_file => $source_file});
  }
  else {
    $cc = $config->cc;
  }
  my $global_cc_each = $self->global_cc_each;
  if ($global_cc_each) {
    $cc = $global_cc_each->($config, {class_name => $class_name, source_file => $source_file, cc => $cc});
  }
  
  my $cflags = '';
  
  my $include_dirs = $config->include_dirs;
  my $inc = join(' ', map { "-I$_" } @$include_dirs);
  $cflags .= " $inc";
  
  my $ccflags_each = $config->ccflags_each;
  my $ccflags;
  if ($ccflags_each) {
    $ccflags = $ccflags_each->($config, {cc => $cc, class_name => $class_name, source_file => $source_file});
  }
  else {
    $ccflags = $config->ccflags;
  }
  my $global_ccflags_each = $self->global_ccflags_each;
  if ($global_ccflags_each) {
    $ccflags = $global_ccflags_each->($config, {cc => $cc, class_name => $class_name, source_file => $source_file, ccflags => $ccflags});
  }
  $cflags .= " " . join(' ', @$ccflags);
  
  my $optimize_each = $config->optimize_each;
  my $optimize;
  if ($optimize_each) {
    $optimize = $optimize_each->($config, {cc => $cc, class_name => $class_name, source_file => $source_file});
  }
  else {
    $optimize = $config->optimize;
  }
  my $global_optimize_each = $self->global_optimize_each;
  if ($global_optimize_each) {
    $optimize = $global_optimize_each->($config, {cc => $cc, class_name => $class_name, source_file => $source_file, optimize => $optimize});
  }
  $cflags .= " $optimize";
  
  my @cflags = ExtUtils::CBuilder->new->split_like_shell($cflags);
  
  my $compile_info = {cc => $cc, ccflags => \@cflags, object_file => $output_file, source_file => $source_file};
  
  return $compile_info;
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
my \$config = SPVM::Builder::Config->new_gnu99;

\$config;
----------------------------------------------
EOS
  
}

sub link {
  my ($self, $class_name, $object_file_infos, $opt) = @_;
  
  # All object file infos
  my $all_object_file_infos = [@$object_file_infos];
  
  # Category
  my $category = $self->category;

  # Build directory
  my $build_dir = $self->builder->build_dir;
  if (defined $build_dir) {
    mkpath $build_dir;
  }
  else {
    confess "SPVM_BUILD_DIR environment variable must be set for link";
  }

  # Shared library directory
  my $output_dir = $opt->{output_dir};
  unless (defined $output_dir && -d $output_dir) {
    confess "Shared lib directory must be specified for link";
  }

  # Shared library file
  my $dynamic_lib_rel_file = SPVM::Builder::Util::convert_class_name_to_dynamic_lib_rel_file($class_name, $self->category);
  my $dynamic_lib_file = "$output_dir/$dynamic_lib_rel_file";

  # Module file
  my $module_file = $self->builder->get_module_file($class_name);
  unless (defined $module_file) {
    my $config_file = $self->get_config_file_from_class_name($class_name);
    if ($config_file) {
      $module_file = $config_file;
      $module_file =~ s/\.config$/\.spvm/;
    }
    else {
      confess "\"$module_file\" module is not loaded";
    }
  }
  
  # Config
  my $config = $opt->{config};
  unless ($config) {
    # Config file
    my $config_file = $module_file;
    $config_file =~ s/\.spvm$/.config/;
    if ($category eq 'native') {
      if (-f $config_file) {
        $config = SPVM::Builder::Util::load_config($config_file);
        $config->file($config_file);
      }
      else {
        my $error = $self->_error_message_find_config($config_file);
        confess $error;
      }
    }
    elsif ($category eq 'precompile') {
      $config = SPVM::Builder::Config->new_gnu99;
    }
    else { confess 'Unexpected Error' }
  }
  
  # Quiet output
  my $quiet = $config->quiet;

  # If quiet field exists, overwrite it
  if ($self->debug) {
    $quiet = 0;
  }
  else {
    if (defined $self->quiet) {
      $quiet = $self->quiet;
    }
  }
  
  # dl_func_list
  # This option is needed Windows DLL file
  my $dl_func_list = [];
  my $method_names = $self->builder->get_method_names($class_name, $category);
  for my $method_name (@$method_names) {
    my $cfunc_name = SPVM::Builder::Util::create_cfunc_name($class_name, $method_name, $category);
    push @$dl_func_list, $cfunc_name;
  }
  
  if ($category eq 'precompile') {
    # Add anon class sub names to dl_func_list
    my $anon_class_names = $self->builder->get_anon_class_names_by_parent_class_name($class_name);
    
    for my $anon_class_name (@$anon_class_names) {
      my $anon_method_cfunc_name = SPVM::Builder::Util::create_cfunc_name($anon_class_name, "", $category);
      push @$dl_func_list, $anon_method_cfunc_name;
    }
  }

  # This is bad hack to suppress boot strap function error.
  unless (@$dl_func_list) {
    push @$dl_func_list, '';
  }

  # Linker
  my $ld = $config->ld;

  # All linker flags
  my @all_ldflags;

  # Linker flags
  my $ldflags = $config->ldflags;
  push @all_ldflags, @{$config->ldflags};
  
  # Optimize
  my $ld_optimize = $config->ld_optimize;
  push @all_ldflags, $ld_optimize;

  # Add resource lib directories
  if ($category eq 'native') {
    my $symbol_names_h = {};
    my $resources = $config->resources;
    for my $resource (@$resources) {
      
      # Build native classes
      my $builder_cc_resource = SPVM::Builder::CC->new(
        build_dir => $self->builder->build_dir,
        category => 'native',
        builder => $self->builder,
        quiet => $self->quiet,
        force => $self->force,
      );
      
      my $resource_src_dir = $self->resource_src_dir_from_class_name($resource);
      my $resource_object_dir = $self->get_resource_object_dir_from_class_name($class_name);
      mkpath $resource_object_dir;
      
      my $resource_class_name;
      my $resource_config;
      if (ref $resource) {
        $resource_class_name = $resource->class_name;
        $resource_config = $resource->config;
      }
      else {
        $resource_class_name = $resource;
      }
      
      my $compile_options = {
        input_dir => $resource_src_dir,
        output_dir => $resource_object_dir,
        is_resource => 1,
      };
      if ($resource_config) {
        $compile_options->{config} = $resource_config;
      }
      
      my $object_file_infos = $builder_cc_resource->compile($resource_class_name, $compile_options);
      
      push @$all_object_file_infos, @$object_file_infos;
    }
  }

  # Libraries
  # Libraries is linked using absolute path because the linked libraries must be known at runtime.
  my $lib_dirs = $config->lib_dirs;
  my @lib_files;
  {
    my $libs = $config->libs;
    for my $lib (@$libs) {
      my $type;
      my $lib_name;
      if (ref $lib eq 'HASH') {
        $type = $lib->{type};
        $lib_name = $lib->{name};
      }
      else {
        $lib_name = $lib;
        $type = 'dynamic,static';
      }
      
      my $found_lib_file;
      my $lib_type;
      for my $lib_dir (@$lib_dirs) {
        $lib_dir =~ s|[\\/]$||;

        my $dynamic_lib_file_base = "lib$lib_name.$Config{dlext}";
        my $dynamic_lib_file = "$lib_dir/$dynamic_lib_file_base";

        my $static_lib_file_base = "lib$lib_name.a";
        my $static_lib_file = "$lib_dir/$static_lib_file_base";
        
        if ($type eq 'dynamic,static') {
          if (-f $dynamic_lib_file) {
            $found_lib_file = $dynamic_lib_file;
            $lib_type = 'dynamic';
            last;
          }
          elsif (-f $static_lib_file) {
            $found_lib_file = $static_lib_file;
            $lib_type = 'static';
            last;
          }
        }
        elsif ($type eq 'dynamic') {
          if (-f $dynamic_lib_file) {
            $found_lib_file = $dynamic_lib_file;
            $lib_type = 'dynamic';
            last;
          }
        }
        elsif ($type eq 'static') {
          if (-f $static_lib_file) {
            $found_lib_file = $static_lib_file;
            $lib_type = 'static';
            last;
          }
        }
      }
      
      if (defined $found_lib_file) {
        push @lib_files, $found_lib_file;
        
        my $object_file_info = SPVM::Builder::ObjectFileInfo->new(
          object_file => $found_lib_file,
          class_name => $class_name,
          config => $config,
          lib_type => $lib_type,
        );
        
        push @$all_object_file_infos, $object_file_info;
      }
    }
  }

  my $all_object_files = [map { $_->to_string } @$all_object_file_infos];

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

  # ExtUtils::CBuilder object
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $cbuilder_config);

  # Move temporary shared library file to blib directory
  mkpath dirname $dynamic_lib_file;
  
  my $input_files = [@$all_object_files];
  if (defined $config->file) {
    push @$input_files, $config->file;
  }
  my $need_generate = SPVM::Builder::Util::need_generate({
    force => $self->force || $config->force,
    output_file => $dynamic_lib_file,
    input_files => $input_files,
  });

  my $link_info = SPVM::Builder::LinkInfo->new(
    class_name => $class_name,
    object_file_infos => $all_object_file_infos,
    ld => $ld,
    ldflags => \@all_ldflags,
    output_file => $dynamic_lib_file,
  );

  # Execute the callback before this link
  my $before_link = $config->before_link;
  if ($before_link) {
    $before_link->($config, $link_info);
  }

  if ($need_generate) {
    my $link_info_ld = $link_info->ld;
    my $link_info_ldflags = $link_info->ldflags;
    my $link_info_class_name = $link_info->class_name;
    my $link_info_output_file = $link_info->output_file;
    my $link_info_object_file_infos = $link_info->object_file_infos;

    my $link_info_object_files = [map { my $tmp = $_->to_string; $tmp } @$link_info_object_file_infos];

    my $link_info_ldflags_str = join(' ', @$link_info_ldflags);
    
    # Create shared library
    my (undef, @tmp_files) = $cbuilder->link(
      lib_file => $link_info_output_file,
      objects => $link_info_object_files,
      module_name => $link_info_class_name,
      extra_linker_flags => $link_info_ldflags_str,
      dl_func_list => $dl_func_list,
    );

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
          print "[$def_file]\n$def_content\n";
        }
        if (defined $lds_file && -f $lds_file) {
          my $lds_content = SPVM::Builder::Util::slurp_binary($lds_file);
          print "[$lds_file]\n$lds_content\n";
        }
      }
    }
  }
  
  return $dynamic_lib_file;
}

sub create_precompile_source_file {
  my ($self, $class_name, $opt) = @_;
  
  # Output - Precompile C source file
  my $output_dir = $opt->{output_dir};
  my $source_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'precompile.c');
  my $source_file = "$output_dir/$source_rel_file";
  
  # Check if generating is needed
  my $module_file = $self->builder->get_module_file($class_name);
  my $spvm_module_dir = $INC{'SPVM/Builder.pm'};
  $spvm_module_dir =~ s/\.pm$//;
  $spvm_module_dir .= '/src';
  my $spvm_precompile_soruce_file = "$spvm_module_dir/spvm_precompile.c";
  unless (-f $spvm_precompile_soruce_file) {
    confess "Can't find $spvm_precompile_soruce_file";
  }
  my $need_generate = SPVM::Builder::Util::need_generate({
    force => $self->force,
    output_file => $source_file,
    input_files => [$module_file, $spvm_precompile_soruce_file],
  });
  
  # Generate precompile C source file
  if ($need_generate) {
    my $precompile_source = $self->create_precompile_source($class_name);
    mkpath dirname $source_file;
    open my $fh, '>', $source_file
      or die "Can't create $source_file";
    print $fh $precompile_source;
    close $fh;
  }
}

1;

=head1 NAME

SPVM::Builder::CC - Compiler and Linker of Native Sources
