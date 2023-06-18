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

sub at_runtime {
  my $self = shift;
  if (@_) {
    $self->{at_runtime} = $_[0];
    return $self;
  }
  else {
    return $self->{at_runtime};
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
sub resource_src_dir_from_basic_type_name {
  my ($self, $basic_type_name) = @_;

  my $config_file = SPVM::Builder::Util::get_config_file_from_basic_type_name($basic_type_name);
  my $config_rel_file = SPVM::Builder::Util::convert_basic_type_name_to_rel_file($basic_type_name, 'config');
  
  my $resource_src_dir = $config_file;
  $resource_src_dir =~ s|/\Q$config_rel_file\E$||;
  
  return $resource_src_dir;
}

sub get_resource_object_dir_from_basic_type_name {
  my ($self, $basic_type_name) = @_;

  my $class_rel_dir = SPVM::Builder::Util::convert_basic_type_name_to_rel_file($basic_type_name);
  
  my $resource_object_dir = SPVM::Builder::Util::create_build_object_path($self->build_dir, "$class_rel_dir.resource");
  
  return $resource_object_dir;
}

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
  elsif ($self->at_runtime) {
    $quiet = 1;
  }
  else {
    $quiet = 0;
  }
  
  return $quiet;
}

sub build_precompile_source_file {
  my ($self, $basic_type_name, $options) = @_;

  my $precompile_source = $options->{precompile_source};
  my $module_file = $options->{module_file};
  
  # Force
  my $force = $self->detect_force;

  # Output - Precompile C source file
  my $output_dir = $options->{output_dir};
  my $source_rel_file = SPVM::Builder::Util::convert_basic_type_name_to_rel_file($basic_type_name, 'precompile.c');
  my $source_file = "$output_dir/$source_rel_file";
  
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
    input_files => [$module_file, $spvm_precompile_soruce_file],
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
  my $cc_cmd = $compile_info->create_compile_command;
  
  unless ($quiet) {
    warn "@$cc_cmd\n";
  }
  
  $cbuilder->do_system(@$cc_cmd)
    or confess "The $source_file file cannnot be compiled by the following command:\n@$cc_cmd\n";
}

sub compile_source_files {
  my ($self, $basic_type_name, $options) = @_;
  
  $options ||= {};
  
  # Category
  my $category = $options->{category};

  # Build directory
  my $build_dir = $self->build_dir;
  if (defined $build_dir) {
    mkpath $build_dir;
  }
  else {
    confess "Build directory is not specified. Maybe forget to set \"SPVM_BUILD_DIR\" environment variable?";
  }
  
  # Input directory
  my $input_dir = $options->{input_dir};
  
  # Object directory
  my $output_dir = $options->{output_dir};
  unless (defined $output_dir && -d $output_dir) {
    confess "Output directory must exists for " . $options->{category} . " build";
  }
  
  # Config
  my $config = $options->{config};
  
  # Force compile
  my $force = $self->detect_force($config);

  my $ignore_native_module = $options->{ignore_native_module};
  
  # Native class file
  my $native_module_file;
  unless ($ignore_native_module) {
    # Native class file
    my $native_module_ext = $config->ext;
    unless (defined $native_module_ext) {
      confess "Source extension is not specified";
    }
    my $native_module_rel_file = SPVM::Builder::Util::convert_basic_type_name_to_category_rel_file($basic_type_name, $category, $native_module_ext);
    $native_module_file = "$input_dir/$native_module_rel_file";
    
    unless (-f $native_module_file) {
      confess "Can't find source file $native_module_file";
    }
  }
  
  # Own resource source files
  my $own_source_files = $config->source_files;
  my $native_src_dir = $config->native_src_dir;
  my $resource_src_files;
  if (defined $native_src_dir) {
    $resource_src_files = [map { "$native_src_dir/$_" } @$own_source_files ];
  }
  
  # Compile source files
  my $object_files = [];
  my $is_native_module = 1;
  for my $source_file ($native_module_file, @$resource_src_files) {
    my $cur_is_native_module = $is_native_module;
    $is_native_module = 0;
    
    next unless defined $source_file;
    
    my $object_file_name;
    
    # Object file of native class
    if ($cur_is_native_module) {
      my $object_rel_file = SPVM::Builder::Util::convert_basic_type_name_to_category_rel_file($basic_type_name, $category, 'o');
      $object_file_name = "$output_dir/$object_rel_file";
    }
    # Object file of resource source file
    else {
      my $object_rel_file = SPVM::Builder::Util::convert_basic_type_name_to_category_rel_file($basic_type_name, $category, 'native');
      
      my $object_file_base = $source_file;
      $object_file_base =~ s/^\Q$native_src_dir//;
      $object_file_base =~ s/^[\\\/]//;
      
      $object_file_base =~ s/\.[^\.]+$/.o/;
      $object_file_name = "$output_dir/$object_rel_file/$object_file_base";
      
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
      if ($cur_is_native_module) {
        my $module_file = $source_file;
        $module_file =~ s/\.[^\/\\]+$//;
        $module_file .= '.spvm';
        
        push @$input_files, $module_file;
      }
      $need_generate = SPVM::Builder::Util::need_generate({
        force => $force,
        output_file => $object_file_name,
        input_files => $input_files,
      });
    }
    
    # Compile-information
    my $compile_info = SPVM::Builder::CompileInfo->new(
      output_file => $object_file_name,
      source_file => $source_file,
      config => $config,
    );
    
    my $before_compile_cbs = $config->before_compile_cbs;
    for my $before_compile_cb (@$before_compile_cbs) {
      $before_compile_cb->($config, $compile_info);
    }
    
    # Compile a source file
    if ($need_generate) {
      my $class_rel_dir = SPVM::Builder::Util::convert_basic_type_name_to_rel_dir($basic_type_name);
      my $work_output_dir = "$output_dir/$class_rel_dir";
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

sub create_link_info {
  my ($self, $basic_type_name, $object_files, $config, $options) = @_;
  
  my $category = $options->{category};

  my $all_object_files = [@$object_files];
  
  $options ||= {};
  
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
      $lib_info = SPVM::Builder::LibInfo->new;
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
  
  # Use resources
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
  
  for my $resource_name (@$resource_names) {
    my $resource = $config->get_resource($resource_name);
    
    # Build native classes
    my $builder_cc_resource = SPVM::Builder::CC->new(
      build_dir => $self->build_dir,
    );
    
    my $resource_src_dir = $self->resource_src_dir_from_basic_type_name($resource);
    my $resource_object_dir = $self->get_resource_object_dir_from_basic_type_name($basic_type_name);
    mkpath $resource_object_dir;
    
    my $resource_basic_type_name;
    my $resource_config;
    if (ref $resource) {
      $resource_basic_type_name = $resource->basic_type_name;
      $resource_config = $resource->config;
    }
    else {
      $resource_basic_type_name = $resource;
    }
    
    $resource_config->add_include_dir(@$resource_include_dirs);
    
    $resource_config->disable_resource(1);
    my $compile_options = {
      input_dir => $resource_src_dir,
      output_dir => $resource_object_dir,
      ignore_native_module => 1,
      config => $resource_config,
      category => $category,
    };
    
    my $object_files = $builder_cc_resource->compile_source_files($resource_basic_type_name, $compile_options);
    
    push @$all_object_files, @$object_files;
  }

  # Output file
  my $output_file = $options->{output_file};
  unless (defined $output_file) {
    # Dynamic library directory
    my $output_dir = $options->{output_dir};
    unless (defined $output_dir && -d $output_dir) {
      confess "Shared lib directory must be specified for link";
    }
    
    # Dynamic library file
    my $output_rel_file = SPVM::Builder::Util::convert_basic_type_name_to_category_rel_file($basic_type_name, $options->{category});
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

  # Optimize
  my $ld_optimize = $config->ld_optimize;
  
  my $link_info = SPVM::Builder::LinkInfo->new(
    basic_type_name => $basic_type_name,
    config => $config,
    object_files => $all_object_files,
    output_file => $output_file,
  );
  
  return $link_info;
}

sub link {
  my ($self, $basic_type_name, $object_files, $options) = @_;
  
  my $dl_func_list = $options->{dl_func_list};
  
  my $category = $options->{category};
  
  # Build directory
  my $build_dir = $self->build_dir;
  if (defined $build_dir) {
    mkpath $build_dir;
  }
  else {
    confess "The \"build_dir\" field must be defined to build the native class for the $category methods. Perhaps the setting of the SPVM_BUILD_DIR environment variable is forgotten";
  }
  
  # Config
  my $config = $options->{config};
  unless ($config) {
    confess "Need config option";
  }

  # Force link
  my $force = $self->detect_force($config);
  
  # Link information
  my $link_info = $self->create_link_info($basic_type_name, $object_files, $config, $options);
  
  # Output file
  my $output_file = $link_info->output_file;
  
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
    
    my $link_info_output_file = $link_info->output_file;
    my $link_info_object_files = $link_info->object_files;
    
    my $link_command_args = $link_info->create_link_command_args;
    
    my $link_info_object_file_names = [map { $_->to_string; } @$link_info_object_files];

    my @tmp_files;
    
    my $output_type = $config->output_type;
    
    # Create a dynamic library
    if ($output_type eq 'dynamic_lib') {
      (undef, @tmp_files) = $cbuilder->link(
        objects => $link_info_object_file_names,
        module_name => $basic_type_name,
        lib_file => $link_info_output_file,
        extra_linker_flags => "@$link_command_args",
        dl_func_list => $dl_func_list,
      );
      unless ($quiet) {
        my $link_command = $link_info->to_cmd;
        warn "$link_command\n";
      }
    }
    # Create a static library
    elsif ($output_type eq 'static_lib') {
      my @object_files = map { "$_" } @$link_info_object_file_names;
      my @ar_cmd = ('ar', 'rc', $link_info_output_file, @object_files);
      $cbuilder->do_system(@ar_cmd)
        or confess "Can't execute command @ar_cmd";
      unless ($quiet) {
        warn "@ar_cmd\n";
      }
    }
    # Create an executable file
    elsif ($output_type eq 'exe') {
      (undef, @tmp_files) = $cbuilder->link_executable(
        objects => $link_info_object_file_names,
        module_name => $basic_type_name,
        exe_file => $link_info_output_file,
        extra_linker_flags => "@$link_command_args",
      );
      unless ($quiet) {
        my $link_command = $link_info->to_cmd;
        warn "$link_command\n";
      }
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

1;

=head1 Name

SPVM::Builder::CC - Compilation and Link of Native Class

=head1 Description

The SPVM::Builder::CC class has methods to compile and link a SPVM native class.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
