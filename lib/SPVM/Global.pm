package SPVM::Global;
use strict;
use warnings;
use Carp 'confess';

use SPVM::BlessedObject;
use SPVM::BlessedObject::Array;
use SPVM::BlessedObject::Class;
use SPVM::BlessedObject::String;

use SPVM ();
use SPVM::Builder;
use SPVM::Builder::Runtime;
use SPVM::ExchangeAPI;

our $BUILDER;
our $BUILDER_COMPILER;
our $BUILDER_RUNTIME;
our $BUILDER_ENV;
our $BUILDER_STACK;
our $BUILDER_API;
our $COMPILER;
our $RUNTIME;
our $DYNAMIC_LIB_FILES = {};
our $ENV;
our $STACK;
our $API;

sub load_dynamic_libs {
  my ($runtime, $dynamic_lib_files) = @_;
  
  my $basic_types_length = $runtime->get_basic_types_length;
  
  # Set addresses of native methods and precompile methods
  for (my $basic_type_id = 0; $basic_type_id < $basic_types_length; $basic_type_id++) {
    my $basic_type = $runtime->get_basic_type_by_id($basic_type_id);
    
    my $spvm_basic_type_name = $basic_type->get_name;
    my $basic_type_name = $spvm_basic_type_name->to_string;
    
    for my $category ('precompile', 'native') {
      
      my $get_method_names_options = $runtime->__api->new_options({
        $category => $runtime->__api->class('Int')->new(1)
      });
      
      my $method_names = $runtime->get_method_names($basic_type_name, $get_method_names_options)->to_strings;
      
      if (@$method_names) {
        # Build modules - Compile C source codes and link them to SPVM precompile method
        # Shared library which is already installed in distribution directory
        my $module_file = $runtime->get_module_file($basic_type_name)->to_string;
        my $dynamic_lib_file = SPVM::Builder::Util::get_dynamic_lib_file_dist($module_file, $category);
        
        # Try to build the shared library at runtime if shared library is not found
        unless (-f $dynamic_lib_file) {
          my $module_file = $runtime->get_module_file($basic_type_name)->to_string;
          my $method_names = $runtime->get_method_names($basic_type_name, $get_method_names_options)->to_strings;
          my $anon_basic_type_names = &get_anon_basic_type_names_v2($runtime, $basic_type);
          
          my $dl_func_list = SPVM::Builder::Util::create_dl_func_list($basic_type_name, $method_names, $anon_basic_type_names, {category => $category});
          
          my $precompile_source = $runtime->build_precompile_module_source($basic_type)->to_string;
          
          $dynamic_lib_file = $BUILDER->build_at_runtime($basic_type_name, {module_file => $module_file, category => $category, dl_func_list => $dl_func_list, precompile_source => $precompile_source});
        }
        
        if (-f $dynamic_lib_file) {
          $dynamic_lib_files->{$category}{$basic_type_name} = $dynamic_lib_file;
        }
      }
    }
  }
  
  # Set function addresses of native and precompile methods
  for my $category ('precompile', 'native') {
    my $get_method_names_options = $runtime->__api->new_options({
      $category => $runtime->__api->class('Int')->new(1)
    });
    
    for my $module_name (keys %{$dynamic_lib_files->{$category}}) {
      
      my $basic_type = $runtime->get_basic_type_by_name($module_name);
      
      my $basic_type_name = $basic_type->get_name;
      
      my $dynamic_lib_file = $dynamic_lib_files->{$category}{$module_name};
      my $method_names = $runtime->get_method_names($module_name, $get_method_names_options)->to_strings;
      
      my $anon_basic_type_names = &get_anon_basic_type_names_v2($runtime, $basic_type);
      
      my $method_addresses = SPVM::Builder::Util::get_method_addresses($dynamic_lib_file, $module_name, $method_names, $anon_basic_type_names, $category);
      
      for my $method_name (sort keys %$method_addresses) {
        my $cfunc_address = $method_addresses->{$method_name};
        if ($category eq 'native') {
          $runtime->set_native_method_address($module_name, $method_name, $runtime->__api->new_address_object($cfunc_address));
        }
        elsif ($category eq 'precompile') {
          $runtime->set_precompile_method_address($module_name, $method_name, $runtime->__api->new_address_object($cfunc_address));
        }
      }
    }
  }
}

sub init_runtime {
  unless ($RUNTIME) {
    unless ($BUILDER) {
      my $build_dir = SPVM::Builder::Util::get_normalized_env('SPVM_BUILD_DIR');
      $BUILDER = SPVM::Builder->new(build_dir => $build_dir);
    }
    
    $BUILDER_COMPILER = SPVM::Builder::Compiler->new(
      include_dirs => $BUILDER->include_dirs
    );
    # Load SPVM Compilers
    $BUILDER_COMPILER->compile_with_exit("Native::Compiler", __FILE__, __LINE__);
    $BUILDER_COMPILER->compile_with_exit("Native::Runtime", __FILE__, __LINE__);
    $BUILDER_COMPILER->compile_with_exit("Native::Env", __FILE__, __LINE__);
    $BUILDER_COMPILER->compile_with_exit("Native::Stack", __FILE__, __LINE__);
    
    $BUILDER_RUNTIME = $BUILDER_COMPILER->get_runtime;

    $BUILDER_RUNTIME->load_dynamic_libs;

    # Build an environment
    $BUILDER_ENV = SPVM::Builder::Env->new($BUILDER_COMPILER);
    
    # Set command line info
    $BUILDER_STACK = $BUILDER_ENV->new_stack;
    
    $BUILDER_ENV->set_command_info_program_name($BUILDER_STACK, $0);
    $BUILDER_ENV->set_command_info_argv($BUILDER_STACK, \@ARGV);
    my $base_time = $^T + 0; # For Perl 5.8.9
    $BUILDER_ENV->set_command_info_base_time($BUILDER_STACK, $base_time);
    
    # Call INIT blocks
    $BUILDER_ENV->call_init_methods($BUILDER_STACK);
    
    $BUILDER_API = SPVM::ExchangeAPI->new(env => $BUILDER_ENV, stack => $BUILDER_STACK);
    
    $COMPILER = $BUILDER_API->class("Native::Compiler")->new;
    for my $include_dir (@{$BUILDER->include_dirs}) {
      $COMPILER->add_include_dir($include_dir);
    }
    $COMPILER->compile(undef);
    $RUNTIME = $COMPILER->get_runtime;
    
    &load_dynamic_libs($RUNTIME, $DYNAMIC_LIB_FILES);
  }
}

my $BIND_TO_PERL_MODULE_NAME_H = {};
sub bind_to_perl {
  my ($basic_type_name) = @_;
  
  my $basic_type = $RUNTIME->get_basic_type_by_name($basic_type_name);
  
  my $perl_module_name_base = "SPVM::";
  my $perl_module_name = "$perl_module_name_base$basic_type_name";
  
  unless ($BIND_TO_PERL_MODULE_NAME_H->{$perl_module_name}) {
    
    my $parent_basic_type = $basic_type->get_parent;
    
    # The inheritance
    my @isa;
    if (defined $parent_basic_type) {
      my $parent_basic_type_name = $parent_basic_type->get_name;
      push @isa, "$perl_module_name_base$parent_basic_type_name";
    }
    push @isa, 'SPVM::BlessedObject::Class';
    my $isa = "our \@ISA = (" . join(',', map { "'$_'" } @isa) . ");";
    
    my $code = "package $perl_module_name; $isa";
    eval $code;
    
    if (my $error = $@) {
      confess $error;
    }
    
    my $methods_length = $basic_type->get_methods_length;
    for (my $method_index = 0; $method_index < $methods_length; $method_index++) {
      my $method = $basic_type->get_method_by_index($method_index);
      
      my $method_name = $method->get_name;
      
      # Destrutor is skip
      if ($method_name eq 'DESTROY') {
        next;
      }
      # Anon method is skip
      elsif (length $method_name == 0) {
        next;
      }
      
      my $perl_method_abs_name = "${perl_module_name}::$method_name";
      my $is_class_method = $RUNTIME->get_method_is_class_method($basic_type_name, $method_name);
      
      if ($is_class_method) {
        # Define Perl method
        no strict 'refs';
        
        # Suppress refer to objects
        my $basic_type_name_string = "$basic_type_name";
        my $method_name_string = "$method_name";
        
        *{"$perl_method_abs_name"} = sub {
          my $perl_module_name = shift;
          
          my $return_value;
          
          eval { $return_value = SPVM::api()->call_method($basic_type_name_string, $method_name_string, @_) };
          my $error = $@;
          if ($error) {
            confess $error;
          }
          $return_value;
        };
      }
    }
    
    $BIND_TO_PERL_MODULE_NAME_H->{$perl_module_name} = 1;
  }
}


sub build {
  my ($module_name, $file, $line) = @_;
  
  unless ($BUILDER) {
    my $build_dir = SPVM::Builder::Util::get_normalized_env('SPVM_BUILD_DIR');
    $BUILDER = SPVM::Builder->new(build_dir => $build_dir);
  }
  
  &init_runtime();
  
  # Add module informations
  my $build_success;
  if (defined $module_name) {
    
    $COMPILER->set_start_file($file);
    $COMPILER->set_start_line($line);
    my $success = $COMPILER->compile($module_name);
    unless ($success) {
      my $error_messages = $COMPILER->get_error_messages;
      for my $error_message (@$error_messages) {
        printf STDERR "[CompileError]$error_message\n";
      }
      $COMPILER = undef;
      exit(255);
    }
    
    $RUNTIME = $COMPILER->get_runtime;
    
    &load_dynamic_libs($RUNTIME, $DYNAMIC_LIB_FILES);
  }
}

sub init_api {
  
  &init_runtime();
  
  $ENV = $BUILDER_API->class("Native::Env")->new($COMPILER);
  
  $STACK = $ENV->new_stack;
  
  $ENV->set_command_info_program_name($STACK, $0);
  
  $ENV->set_command_info_argv($STACK, \@ARGV);
  my $base_time = $^T + 0; # For Perl 5.8.9
  $ENV->set_command_info_base_time($STACK, $base_time);
  
  $ENV->call_init_methods($STACK);
  
  $API = SPVM::ExchangeAPI->new(env => $ENV, stack => $STACK);
}

END {
  $API = undef;
  if ($ENV) {
    $ENV->destroy_class_vars($STACK);
  }
  $STACK = undef;
  $ENV = undef;
  $RUNTIME = undef;
  $DYNAMIC_LIB_FILES = undef;
  $COMPILER = undef;
  $BUILDER_API = undef;
  if ($BUILDER_ENV) {
    $BUILDER_ENV->destroy_class_vars($BUILDER_STACK);
  }
  $BUILDER_STACK = undef;
  $BUILDER_ENV = undef;
  $BUILDER_RUNTIME = undef;
  $BUILDER_COMPILER = undef;
  $BUILDER = undef;
}

sub get_anon_basic_type_names_v2 {
  my ($runtime, $basic_type) = @_;
  
  my $anon_basic_type_names_length = $basic_type->get_anon_basic_types_length;
  
  my $anon_basic_type_names = [];
  for (my $anon_basic_type_id = 0; $anon_basic_type_id < $anon_basic_type_names_length; $anon_basic_type_id++) {
    my $anon_basic_type = $basic_type->get_anon_basic_type_by_index($anon_basic_type_id);
    
    my $anon_method = $anon_basic_type->get_method_by_name("");
    
    if ($anon_method->is_precompile) {
      $anon_basic_type->get_name;
      push @$anon_basic_type_names, $anon_basic_type->get_name->to_string;
    }
  }
  
  return $anon_basic_type_names;
}

=head1 Name

SPVM::Global - SPVM Global Instance for Perl Interpreter

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
