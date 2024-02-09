package SPVM::Builder::Util;

use strict;
use warnings;
use Carp 'confess';
use Config;
use File::Path 'mkpath';
use Pod::Usage 'pod2usage';
use Getopt::Long 'GetOptionsFromArray';
use List::Util 'min';
use File::Basename 'dirname';
use File::Spec;
use SPVM::Builder::Config;
use Encode 'decode';
use File::Find 'find';

# SPVM::Builder::Util is used from Makefile.PL
# so this class must be wrote as pure perl script, not contain XS functions.

sub get_spvm_core_perl_class_file_names {
  my @spvm_builder_class_file_names = qw(
    SPVM/BlessedObject/Array.pm
    SPVM/BlessedObject/Class.pm
    SPVM/BlessedObject.pm
    SPVM/BlessedObject/String.pm
    SPVM/Builder/API.pm
    SPVM/Builder/CC.pm
    SPVM/Builder/CompileInfo.pm
    SPVM/Builder/Compiler.pm
    SPVM/Builder/Config/Exe.pm
    SPVM/Builder/Config.pm
    SPVM/Builder/Env.pm
    SPVM/Builder/Exe.pm
    SPVM/Builder/LibInfo.pm
    SPVM/Builder/LinkInfo.pm
    SPVM/Builder/ObjectFileInfo.pm
    SPVM/Builder.pm
    SPVM/Builder/Resource.pm
    SPVM/Builder/Runtime.pm
    SPVM/Builder/Stack.pm
    SPVM/Builder/Util/API.pm
    SPVM/Builder/Util.pm
    SPVM/Document/ExchangeAPI.pm
    SPVM/ExchangeAPI/Class.pm
    SPVM/ExchangeAPI/Error.pm
    SPVM/ExchangeAPI.pm
    SPVM/Global.pm
    SPVM.pm
  );
  
  return \@spvm_builder_class_file_names;
}

sub get_spvm_version_header_file_name {
  
  my $spvm_version_header_file_name = 'spvm_version.h';
  
  return $spvm_version_header_file_name;
}

sub get_spvm_version_header_file {
  
  my $builder_dir = &get_builder_dir;
  
  my $spvm_version_header_file = "/include/spvm_version.h";
  
  unless (-f $spvm_version_header_file) {
    confess "The SPVM version header file \"$spvm_version_header_file\" is not found.";
  }
  
  return $spvm_version_header_file;
}

sub get_spvm_core_header_file_names {
  
  my @spvm_core_header_file_names = qw(
    spvm_allocator.h
    spvm_allow.h
    spvm_api_allocator.h
    spvm_api_arg.h
    spvm_api_basic_type.h
    spvm_api_class_var.h
    spvm_api_compiler.h
    spvm_api_field.h
    spvm_api.h
    spvm_api_method.h
    spvm_api_mutex.h
    spvm_api_class_file.h
    spvm_api_runtime.h
    spvm_api_string_buffer.h
    spvm_api_type.h
    spvm_api_internal.h
    spvm_array_field_access.h
    spvm_attribute.h
    spvm_basic_type.h
    spvm_block.h
    spvm_call_method.h
    spvm_case_info.h
    spvm_check.h
    spvm_class_var_access.h
    spvm_class_var.h
    spvm_compiler.h
    spvm_constant.h
    spvm_dumper.h
    spvm_field_access.h
    spvm_field.h
    spvm_hash.h
    spvm_implement.h
    spvm_interface.h
    spvm_list.h
    spvm_method.h
    spvm_mutex.h
    spvm_class_file.h
    spvm_native.h
    spvm_object.h
    spvm_opcode_builder.h
    spvm_opcode.h
    spvm_opcode_list.h
    spvm_op.h
    spvm_precompile.h
    spvm_public_api.h
    spvm_runtime_arg.h
    spvm_runtime_basic_type.h
    spvm_runtime_class_var.h
    spvm_runtime_field.h
    spvm_runtime.h
    spvm_runtime_method.h
    spvm_runtime_string.h
    spvm_strerror.h
    spvm_string_buffer.h
    spvm_string.h
    spvm_switch_info.h
    spvm_toke.h
    spvm_typedecl.h
    spvm_type.h
    spvm_use.h
    spvm_var_decl.h
    spvm_var.h
    spvm_version.h
    spvm_vm.h
    spvm_weaken_backref.h
    spvm_yacc.h
    spvm_yacc_util.h
  );
  
  return \@spvm_core_header_file_names;
}

sub get_spvm_core_source_file_names {
  
  my @spvm_core_source_file_names = qw(
    spvm_allocator.c
    spvm_allow.c
    spvm_api_allocator.c
    spvm_api_arg.c
    spvm_api_basic_type.c
    spvm_api.c
    spvm_api_class_var.c
    spvm_api_compiler.c
    spvm_api_field.c
    spvm_api_method.c
    spvm_api_mutex.c
    spvm_api_class_file.c
    spvm_api_runtime.c
    spvm_api_string_buffer.c
    spvm_api_type.c
    spvm_api_internal.c
    spvm_array_field_access.c
    spvm_attribute.c
    spvm_basic_type.c
    spvm_block.c
    spvm_call_method.c
    spvm_case_info.c
    spvm_check.c
    spvm_class_var_access.c
    spvm_class_var.c
    spvm_compiler.c
    spvm_constant.c
    spvm_dumper.c
    spvm_field_access.c
    spvm_field.c
    spvm_hash.c
    spvm_interface.c
    spvm_list.c
    spvm_method.c
    spvm_mutex.c
    spvm_class_file.c
    spvm_op.c
    spvm_opcode_builder.c
    spvm_opcode.c
    spvm_opcode_list.c
    spvm_precompile.c
    spvm_runtime.c
    spvm_strerror.c
    spvm_string_buffer.c
    spvm_string.c
    spvm_switch_info.c
    spvm_toke.c
    spvm_type.c
    spvm_use.c
    spvm_var.c
    spvm_var_decl.c
    spvm_vm.c
    spvm_yacc.c
    spvm_yacc_util.c
  );

  return \@spvm_core_source_file_names;
}

sub get_spvm_compiler_required_file_names {
  my @get_spvm_compiler_required_file_names = qw(
    SPVM/Native/Arg.c
    SPVM/Native/Arg.spvm
    SPVM/Native/BasicType.c
    SPVM/Native/BasicType.spvm
    SPVM/Native.c
    SPVM/Native/ClassVar.c
    SPVM/Native/ClassVar.spvm
    SPVM/Native/Compiler.c
    SPVM/Native/Compiler.spvm
    SPVM/Native/Env.c
    SPVM/Native/Env.spvm
    SPVM/Native/Field.c
    SPVM/Native/Field.spvm
    SPVM/Native/Method.c
    SPVM/Native/MethodCall.c
    SPVM/Native/MethodCall.spvm
    SPVM/Native/Method.spvm
    SPVM/Native/ClassFile.c
    SPVM/Native/ClassFile.spvm
    SPVM/Native/Runtime.c
    SPVM/Native/Runtime.spvm
    SPVM/Native.spvm
    SPVM/Native/Stack.c
    SPVM/Native/Stack.spvm
  );
  
  return \@get_spvm_compiler_required_file_names;
}

sub need_generate {
  my ($opt) = @_;
  
  my $force = $opt->{force};
  my $input_files = $opt->{input_files};
  my $output_file = $opt->{output_file};
  
  # SPVM::Builder classes
  my $spvm_dependent_files = &get_spvm_dependent_files;
  
  my $spvm_dependent_files_mtime_max;
  $spvm_dependent_files_mtime_max = 0;
  for my $spvm_core_file (@$spvm_dependent_files) {
    my $spvm_core_file_mtime = (stat($spvm_core_file))[9];
    if ($spvm_core_file_mtime > $spvm_dependent_files_mtime_max) {
      $spvm_dependent_files_mtime_max = $spvm_core_file_mtime;
    }
  }

  my $need_generate;
  if ($force) {
    $need_generate = 1;
  }
  else {
    if (!-f $output_file) {
      $need_generate = 1;
    }
    else {
      my $input_files_mtime_max = 0;
      my $exists_input_file_at_least_one;
      for my $input_file (@$input_files) {
        if (-f $input_file) {
          $exists_input_file_at_least_one = 1;
          my $input_file_mtime = (stat($input_file))[9];
          if ($input_file_mtime > $input_files_mtime_max) {
            $input_files_mtime_max = $input_file_mtime;
          }
        }
      }
      if ($exists_input_file_at_least_one) {
        my $output_file_mtime = (stat($output_file))[9];
        
        if (defined $spvm_dependent_files_mtime_max) {
          if ($spvm_dependent_files_mtime_max > $input_files_mtime_max) {
            $input_files_mtime_max = $spvm_dependent_files_mtime_max;
          }
        }
        
        if ($input_files_mtime_max > $output_file_mtime) {
          $need_generate = 1;
        }
      }
    }
  }
  
  return $need_generate;
}

sub slurp_binary {
  my ($file) = @_;
  
  open my $fh, '<', $file
    or confess "Can't open file \"$file\":$!";
    
  my $content = do { local $/; <$fh> };
  
  return $content;
}

sub slurp_utf8 {
  my ($file) = @_;
  
  my $content = &slurp_binary($file);
  
  $content = decode('UTF-8', $content);
  
  return $content;
}

sub file_contains {
  my ($file, $string) = @_;
  
  my $content = &slurp_utf8($file);
  
  my $contains;
  if (index($content, $string) >= 0) {
    $contains = 1;
  }
  
  return $contains;
}

sub spurt_binary {
  my ($file, $content) = @_;
  
  open my $fh, '>:raw', $file
    or confess "Can't open file \"$file\":$!";
    
  print $fh $content;
}

sub unindent {
  my $str = shift;
  my $min = min map { m/^([ \t]*)/; length $1 || () } split "\n", $str;
  $str =~ s/^[ \t]{0,$min}//gm if $min;
  return $str;
}

sub extract_usage {
  my $file = @_ ? "$_[0]" : (caller)[1];
  
  open my $handle, '>', \my $output;
  
  pod2usage -exitval => 'noexit', -input => $file, -output => $handle, -verbose => 99, -sections => "Usage";
  $output =~ s/^.*\n|\n$//;
  $output =~ s/\n$//;

  return SPVM::Builder::Util::unindent($output);
}

sub getopt {
  my ($array, $opts) = map { ref $_[0] eq 'ARRAY' ? shift : $_ } \@ARGV, [];
  my $save = Getopt::Long::Configure(qw(default no_auto_abbrev no_ignore_case),
    @$opts);
  GetOptionsFromArray $array, @_;
  Getopt::Long::Configure($save);
}

sub convert_class_file_to_dynamic_lib_file {
  my ($class_file, $category) = @_;
  
  my $dlext = $Config{dlext};
  $class_file =~ s/\.[^.]+$//;
  my $dynamic_lib_category_file = $class_file;
  $dynamic_lib_category_file .= $category eq 'native' ? ".$dlext" : ".$category.$dlext";
  
  return $dynamic_lib_category_file;
}

sub convert_class_name_to_dynamic_lib_rel_file {
  my ($class_name, $category) = @_;
  
  my $dlext = $Config{dlext};
  my $dynamic_lib_category_rel_file = &convert_class_name_to_rel_file($class_name);
  $dynamic_lib_category_rel_file .= $category eq 'native' ? ".$dlext" : ".$category.$dlext";
  
  return $dynamic_lib_category_rel_file;
}

sub convert_class_name_to_category_rel_file {
  my ($class_name, $category, $ext) = @_;
  
  $class_name =~ s/^SPVM:://;
  
  my $rel_file_with_ext = "SPVM::$class_name";
  $rel_file_with_ext =~ s/::/\//g;
  $rel_file_with_ext .= $category eq 'native' ? "" : ".$category";
  if (defined $ext) {
    $rel_file_with_ext .= ".$ext";
  }
  
  return $rel_file_with_ext;
}

sub convert_class_name_to_rel_dir {
  my ($class_name) = @_;
  
  $class_name =~ s/^SPVM:://;
  
  my $rel_dir;
  my $rel_file = "SPVM::$class_name";
  $rel_file =~ s/::/\//g;
  $rel_dir = dirname $rel_file;
  
  return $rel_dir;
}

sub convert_class_name_to_rel_file {
  my ($class_name, $ext) = @_;

  $class_name =~ s/^SPVM:://;
  
  my $rel_file_with_ext = "SPVM::$class_name";
  $rel_file_with_ext =~ s/::/\//g;
  
  if (defined $ext) {
    $rel_file_with_ext .= ".$ext";
  }
  
  return $rel_file_with_ext;
}

sub get_class_base_dir {
  my ($file, $class_name) = @_;
  
  $file =~ s/\.spvm$//;
  my $class_file = "SPVM::$class_name";
  $class_file =~ s/::/\//g;
  $file =~ s/$class_file$//;
  $file =~ s/[\\\/]$//;
  
  return $file;
}

sub create_make_rule_native {
  my $class_name = shift;
  
  create_make_rule($class_name, 'native', @_);
}

sub create_make_rule_precompile {
  my $class_name = shift;
  
  create_make_rule($class_name, 'precompile', @_);
}

sub create_make_rule {
  my ($class_name, $category, $options) = @_;
  
  $options ||= {};
  
  # Deprecated
  if ($class_name =~ s/^SPVM:://) {
    warn "The SPVM:: prefix is no more required in the class name given to the create_make_rule function.";
  }
  
  my $lib_dir = defined $options->{lib_dir} ? $options->{lib_dir} : 'lib';
  
  my $config_file = "$lib_dir/" . &convert_class_name_to_rel_file($class_name, 'config');
  
  my $config_file_without_ext = $config_file;
  $config_file_without_ext =~ s/\.[^\.]+$//;
  
  # Dependency files
  my @dependent_files;
  
  my $spvm_class_file = "$config_file_without_ext.spvm";
  push @dependent_files, $spvm_class_file;
  
  # Dependency native class file
  if ($category eq 'native') {
    # Config
    my $config = SPVM::Builder::Config->load_config($config_file);
    push @dependent_files, $config_file;
    
    # Native class
    my $native_class_file_ext = $config->ext;
    my $native_class_file = "$config_file_without_ext.$native_class_file_ext";
    push @dependent_files, $native_class_file;
    
    # Native include
    my $native_include_dir = "$config_file_without_ext.native/include";
    my @native_include_files;
    if (-d $native_include_dir) {
      find({wanted => sub { if (-f $_) { push @native_include_files, $_ } }, no_chdir => 1}, $native_include_dir);
    }
    push @dependent_files, @native_include_files;
    
    # Native source
    my $native_src_dir = "$config_file_without_ext.native/src";
    my @native_src_files;
    if (-d $native_src_dir) {
      find({wanted => sub { if (-f $_) { push @native_src_files, $_ } }, no_chdir => 1}, $native_src_dir);
    }
    push @dependent_files, @native_src_files;
    
    # Dependency resources
    {
      my $resource_class_names = $config->get_resource_names;
      for my $resource_class_name (@$resource_class_names) {
        my $resource = $config->get_resource($resource_class_name);
        
        my $resource_config = $resource->config;
        
        my $resource_config_file = $resource_config->file;
        
        my $resource_config_file_without_ext = $resource_config_file;
        $resource_config_file_without_ext =~ s/\.[^\.]+$//;
        
        # Resource class file
        my $resource_spvm_class_file = "$resource_config_file_without_ext.spvm";
        push @dependent_files, $resource_spvm_class_file;
        
        # Config
        push @dependent_files, $resource_config_file;
        
        # Native include
        my $resource_native_include_dir = "$resource_config_file_without_ext.native/include";
        my @resource_native_include_files;
        if (-d $resource_native_include_dir) {
          find({wanted => sub { if (-f $_) { push @resource_native_include_files, $_ } }, no_chdir => 1}, $resource_native_include_dir);
        }
        push @dependent_files, @resource_native_include_files;
        
        # Native source
        my $resource_native_src_dir = "$resource_config_file_without_ext.native/src";
        my @resource_native_src_files;
        if (-d $resource_native_src_dir) {
          find({wanted => sub { if (-f $_) { push @resource_native_src_files, $_ } }, no_chdir => 1}, $resource_native_src_dir);
        }
        push @dependent_files, @resource_native_src_files;
      }
    }
  }
  
  # Shared library file
  my $dynamic_lib_rel_file = &convert_class_name_to_dynamic_lib_rel_file($class_name, $category);
  my $dynamic_lib_file = "blib/lib/$dynamic_lib_rel_file";
  
  my $make_rule = '';
  
  # dynamic section
  $make_rule .= "dynamic :: $dynamic_lib_file\n";
  $make_rule .= "\t\$(NOECHO) \$(NOOP)\n\n";
  
  # Get source files
  $make_rule .= "$dynamic_lib_file :: @dependent_files\n";
  $make_rule .= "\t$^X -Mblib -MSPVM::Builder::API -e \"SPVM::Builder::API->new(build_dir => '.spvm_build')->build_dynamic_lib_dist_$category('$class_name')\"\n\n";
  
  return $make_rule;
}

sub get_spvm_dependent_files {
  
  my @spvm_dependent_files;
  if (my $builder_loaded_file = $INC{'SPVM/Builder/Util.pm'}) {
    my $builder_loaded_dir = $builder_loaded_file;
    $builder_loaded_dir =~ s|[/\\]SPVM/Builder/Util\.pm$||;
    
    # SPVM::Builder class files
    my $spvm_core_perl_class_file_names = &get_spvm_core_perl_class_file_names();
    for my $spvm_core_perl_class_file_name (@$spvm_core_perl_class_file_names) {
      my $spvm_core_perl_class_file = "$builder_loaded_dir/$spvm_core_perl_class_file_name";
      unless (-f $spvm_core_perl_class_file) {
        confess "Can't find $spvm_core_perl_class_file";
      }
      push @spvm_dependent_files, $spvm_core_perl_class_file;
    }
    
    # SPVM core header files
    my $spvm_core_header_file_names = &get_spvm_core_header_file_names();
    for my $spvm_core_header_file_name (@$spvm_core_header_file_names) {
      my $spvm_core_header_file = "$builder_loaded_dir/SPVM/Builder/include/$spvm_core_header_file_name";
      unless (-f $spvm_core_header_file) {
        confess "Can't find $spvm_core_header_file";
      }
      push @spvm_dependent_files, $spvm_core_header_file;
    }
    
    # SPVM core source files
    my $spvm_core_source_file_names  = &get_spvm_core_source_file_names();
    for my $spvm_core_source_file_name (@$spvm_core_source_file_names) {
      my $spvm_core_source_file = "$builder_loaded_dir/SPVM/Builder/src/$spvm_core_source_file_name";
      unless (-f $spvm_core_source_file) {
        confess "Can't find $spvm_core_source_file";
      }
      push @spvm_dependent_files, $spvm_core_source_file;
    }
    
    # SPVM Compiler required file names
    my $get_spvm_compiler_required_file_names = &get_spvm_compiler_required_file_names();
    for my $get_spvm_compiler_required_file_name (@$get_spvm_compiler_required_file_names) {
      my $get_spvm_compiler_required_class_file = "$builder_loaded_dir/$get_spvm_compiler_required_file_name";
      unless (-f $get_spvm_compiler_required_class_file) {
        confess "Can't find $get_spvm_compiler_required_class_file";
      }
      push @spvm_dependent_files, $get_spvm_compiler_required_class_file;
    }
  }
  
  unless (@spvm_dependent_files) {
    confess "[Unexpected Error]SPVM dependent files are not found";
  }
  
  return \@spvm_dependent_files;
}

sub search_config_file {
  my ($class_name, $mode) = @_;
  
  my $ext = 'config';
  if (defined $mode) {
    $ext = "$mode.$ext";
  }
  
  my $config_file_base = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, $ext);
  my $config_file;
  for my $inc (@INC) {
    my $config_file_tmp = "$inc/$config_file_base";
    if (-f $config_file_tmp) {
      $config_file = $config_file_tmp;
      last;
    }
  }
  
  return $config_file;
}

sub get_builder_dir {
  my $builder_config_dir = $INC{"SPVM/Builder/Config.pm"};
  my $builder_dir = $builder_config_dir;
  $builder_dir =~ s/\/Config\.pm$//;
  return $builder_dir;
}

sub create_build_src_path {
  my ($build_dir, $rel_file) = @_;
  
  my $build_src_path = "$build_dir/work/src";
  if (defined $rel_file) {
    $build_src_path .= "/$rel_file";
  }
  
  return $build_src_path;
}

sub create_build_include_path {
  my ($build_dir, $rel_file) = @_;
  
  my $build_include_path = "$build_dir/work/include";
  if (defined $rel_file) {
    $build_include_path .= "/$rel_file";
  }
  
  return $build_include_path;
}

sub create_build_object_path {
  my ($build_dir, $rel_file) = @_;
  
  my $build_output_path = "$build_dir/work/object";
  if (defined $rel_file) {
    $build_output_path .= "/$rel_file";
  }
  
  return $build_output_path;
}

sub create_build_lib_path {
  my ($build_dir, $rel_file) = @_;
  
  my $build_lib_path = "$build_dir/work/lib";
  if (defined $rel_file) {
    $build_lib_path .= "/$rel_file";
  }
  
  return $build_lib_path;
}

sub get_dynamic_lib_file_dist {
  my ($class_file, $category) = @_;

  my $dynamic_lib_file = SPVM::Builder::Util::convert_class_file_to_dynamic_lib_file($class_file, $category);
  
  return $dynamic_lib_file;
}

sub create_default_config {
  
  my $config = SPVM::Builder::Config->new_gnu99(file_optional => 1);
  
  return $config;
}

sub get_normalized_env {
  my ($name) = @_;
  
  my $value = $ENV{$name};
  
  if (defined $value && !length $value) {
    $value = undef;
  }
  
  return $value;
}

sub get_version_string {
  my ($spvm_class_file) = @_;
  
  open my $spvm_module_fh, '<', $spvm_class_file or die "Can't open the file \"$spvm_class_file\": $!";
  local $/;
  my $content = <$spvm_module_fh>;
  my $version_string;
  if ($content =~ /\bversion\s*"([\d\._]+)"\s*;/) {
    $version_string = $1;
  }

  unless (defined $version_string) {
    confess "The version string can't be find in $spvm_class_file file";
  }
  
  return $version_string;
}

sub get_spvm_version_string {
  
  my $builder_dir = &get_builder_dir;
  my $spvm_version_header_file = "$builder_dir/include/spvm_version.h";
  
  open my $spvm_module_fh, '<', $spvm_version_header_file
    or die "Can't open the file \"$spvm_version_header_file\": $!";
  local $/;
  my $content = <$spvm_module_fh>;
  my $version_string;
  if ($content =~ /#define\s+SPVM_NATIVE_VERSION_NUMBER\s* ([\d\._]+)/) {
    $version_string = $1;
  }
  
  unless (defined $version_string) {
    confess "The version string can't be found in \"$spvm_version_header_file\"";
  }
  
  return $version_string;
}

sub create_dl_func_list {
  my ($class_name, $method_names, $options) = @_;
  
  $options ||= {};
  
  my $category = $options->{category} || '';
  
  # dl_func_list
  # This option is needed Windows DLL file
  my $dl_func_list = [];
  for my $method_name (@$method_names) {
    my $cfunc_name = SPVM::Builder::Util::create_cfunc_name($class_name, $method_name, $category);
    push @$dl_func_list, $cfunc_name;
  }
  
  # This is bad hack to suppress boot strap function error.
  unless (@$dl_func_list) {
    push @$dl_func_list, '';
  }
  
  return $dl_func_list;
}

sub create_cfunc_name {
  my ($class_name, $method_name, $category) = @_;
  
  my $prefix;
  if ($category eq 'native') {
    $prefix = 'SPVM__';
  }
  elsif ($category eq 'precompile') {
    $prefix = 'SPVMPRECOMPILE__'
  }
  
  # Precompile Method names
  my $method_abs_name_under_score = "${class_name}::$method_name";
  $method_abs_name_under_score =~ s/:/_/g;
  my $cfunc_name = "$prefix$method_abs_name_under_score";
  
  return $cfunc_name;
}

sub get_method_addresses {
  my ($dynamic_lib_file, $class_name, $method_names, $category) = @_;
  
  my $method_addresses = {};
  if (@$method_names) {
    my $method_infos = [];
    for my $method_name (@$method_names) {
      my $method_info = {};
      $method_info->{class_name} = $class_name;
      $method_info->{method_name} = $method_name;
      push @$method_infos, $method_info;
    }
    
    for my $method_info (@$method_infos) {
      my $class_name = $method_info->{class_name};
      my $method_name = $method_info->{method_name};

      my $cfunc_address;
      if ($dynamic_lib_file) {
        my $dynamic_lib_libref = DynaLoader::dl_load_file($dynamic_lib_file);
        
        if ($dynamic_lib_libref) {

          my $cfunc_name = SPVM::Builder::Util::create_cfunc_name($class_name, $method_name, $category);
          $cfunc_address = DynaLoader::dl_find_symbol($dynamic_lib_libref, $cfunc_name);
          unless ($cfunc_address) {
            my $dl_error = DynaLoader::dl_error();
            my $error = <<"EOS";
Can't find native function \"$cfunc_name\" corresponding to ${class_name}->$method_name in \"$dynamic_lib_file\"

You must write the following definition.
--------------------------------------------------
#include <spvm_native.h>

int32_t $cfunc_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}
--------------------------------------------------

$dl_error
EOS
            confess $error;
          }
        }
        else {
          my $dl_error = DynaLoader::dl_error();
          confess "The DynaLoader::dl_load_file function failed:Can't load the \"$dynamic_lib_file\" file for $category methods in $class_name class: $dl_error";
        }
      }
      else {
        confess "DLL file is not specified";
      }
      
      $method_addresses->{$method_name} = $cfunc_address;
    }
  }
  
  return $method_addresses;
}

1;

=head1 Name

SPVM::Builder::Util - Builder Utilities

=head1 Description

The SPVM::Builder::Util class has utility functions for the L<SPVM::Builder> class.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
