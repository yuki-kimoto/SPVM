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
use SPVM::ExchangeAPI;

my $API;

END {
  if ($API) {
    # Remove circular reference
    my $env = delete $API->{env};
    my $stack = delete $API->{stack};
    
    $env->destroy_class_vars($stack);
  }
}

sub api {
  unless ($API) {
    &init_api();
  }
  return $API;
}

sub build_module {
  my ($basic_type_name, $file, $line) = @_;
  
  &init_api();
  
  # Add module informations
  my $build_success;
  if (defined $basic_type_name) {
    
    my $env = $API->env;
    
    my $compiler = $env->compiler;
    
    my $start_runtime = $compiler->get_runtime;
    my $start_basic_types_length = $start_runtime->get_basic_types_length;
    
    $compiler->set_start_file($file);
    $compiler->set_start_line($line);
    my $success = $compiler->compile($basic_type_name);
    unless ($success) {
      my $error_messages = $compiler->get_error_messages;
      for my $error_message (@$error_messages) {
        printf STDERR "[CompileError]$error_message\n";
      }
      $compiler = undef;
      exit(255);
    }
    
    my $runtime = $compiler->get_runtime;
    
    my $basic_types_length = $runtime->get_basic_types_length;
    
    for (my $basic_type_id = $start_basic_types_length; $basic_type_id < $basic_types_length; $basic_type_id++) {
      my $basic_type = $runtime->get_basic_type_by_id($basic_type_id);
      &load_dynamic_lib($runtime, $basic_type->get_name->to_string);
    }
    
    &bind_to_perl($basic_type_name);
    
    my $stack = $API->stack;
    
    $env->call_init_methods($stack);
  }
}

sub init_api {
  unless ($API) {
    my $build_dir = SPVM::Builder::Util::get_normalized_env('SPVM_BUILD_DIR');
    my $builder = SPVM::Builder->new(build_dir => $build_dir);
    
    my $builder_compiler = SPVM::Builder::Compiler->new(
      include_dirs => $builder->include_dirs
    );
    
    my @native_compiler_basic_type_names = qw(
      Native::Compiler
      Native::Method
      Native::Runtime
      Native::BasicType
      Native::Stack
      Native::Env
    );
    
    for my $native_compiler_basic_type_name (@native_compiler_basic_type_names) {
      $builder_compiler->compile_with_exit($native_compiler_basic_type_name, __FILE__, __LINE__);
      my $builder_runtime = $builder_compiler->get_runtime;
      
      # Load dinamic libnaray - native only
      {
        my $basic_type_name = $native_compiler_basic_type_name;
        my $category = 'native';
        my $method_names = $builder_runtime->get_method_names($basic_type_name, $category);
        
        if (@$method_names) {
          # Build classes - Compile C source codes and link them to SPVM precompile method
          # Shared library which is already installed in distribution directory
          my $class_file = $builder_runtime->get_class_file($basic_type_name);
          my $dynamic_lib_file = SPVM::Builder::Util::get_dynamic_lib_file_dist($class_file, $category);
          
          if (-f $dynamic_lib_file) {
            my $method_addresses = SPVM::Builder::Util::get_method_addresses($dynamic_lib_file, $basic_type_name, $method_names, $category);
            
            for my $method_name (sort keys %$method_addresses) {
              my $cfunc_address = $method_addresses->{$method_name};
              $builder_runtime->set_native_method_address($basic_type_name, $method_name, $cfunc_address);
            }
          }
        }
      }
    }
    
    my $builder_env = SPVM::Builder::Env->new($builder_compiler);
    
    my $builder_stack = $builder_env->new_stack;
    
    my $builder_api = SPVM::ExchangeAPI->new(env => $builder_env, stack => $builder_stack);
    
    my $compiler = $builder_api->class("Native::Compiler")->new;
    for my $include_dir (@{$builder->include_dirs}) {
      $compiler->add_include_dir($include_dir);
    }
    $compiler->compile(undef);
    
    my $env = $builder_api->class("Native::Env")->new($compiler);
    
    my $stack = $env->new_stack;
    
    $API = SPVM::ExchangeAPI->new(env => $env, stack => $stack);
    
    $env->set_command_info_program_name($stack, $0);
    
    $env->set_command_info_argv($stack, \@ARGV);
    my $base_time = $^T + 0; # For Perl 5.8.9
    $env->set_command_info_base_time($stack, $base_time);
  }
}

sub load_dynamic_lib {
  my ($runtime, $basic_type_name) = @_;
  
  my $basic_type = $runtime->get_basic_type_by_name($basic_type_name);
  
  my $spvm_class_dir = $basic_type->get_class_dir;
  my $spvm_class_rel_file = $basic_type->get_class_rel_file;
  
  for my $category ('precompile', 'native') {
    
    my $get_method_names_options = $runtime->__api->new_options({
      $category => $runtime->__api->class('Int')->new(1)
    });
    
    my $category_method_names;
    
    if ($category eq 'native') {
      $category_method_names = $basic_type->_get_native_method_names;
    }
    elsif ($category eq 'precompile') {
      $category_method_names = $basic_type->_get_precompile_method_names;
    }
    
    if (@$category_method_names) {
      # Build modules - Compile C source codes and link them to SPVM precompile method
      # Shared library which is already installed in distribution directory
      
      if ($spvm_class_dir) {
        
        my $class_file = "$spvm_class_dir/$spvm_class_rel_file";
        my $dynamic_lib_file = SPVM::Builder::Util::get_dynamic_lib_file_dist($class_file, $category);
        
        # Try to build the shared library at runtime if shared library is not found
        unless (-f $dynamic_lib_file) {
          my $dl_func_list = SPVM::Builder::Util::create_dl_func_list(
            $basic_type_name,
            $category_method_names,
            {category => $category}
          );
          
          my $precompile_source = $runtime->build_precompile_module_source($basic_type)->to_string;
          
          my $build_dir = SPVM::Builder::Util::get_normalized_env('SPVM_BUILD_DIR');
          my $builder = SPVM::Builder->new(build_dir => $build_dir);
          $dynamic_lib_file = $builder->build_at_runtime(
            $basic_type_name,
            {
              class_file => $class_file,
              category => $category,
              dl_func_list => $dl_func_list,
              precompile_source => $precompile_source
            }
          );
        }
        
        if (-f $dynamic_lib_file) {
          my $method_addresses = SPVM::Builder::Util::get_method_addresses(
            $dynamic_lib_file,
            $basic_type_name,
            $category_method_names,
            $category
          );
          
          for my $method_name (sort keys %$method_addresses) {
            my $method = $basic_type->get_method_by_name($method_name);
            
            my $cfunc_address = $method_addresses->{$method_name};
            if ($category eq 'native') {
              $method->set_native_address(
                $runtime->__api->new_address_object($cfunc_address)
              );
            }
            elsif ($category eq 'precompile') {
              $method->set_precompile_address(
                $runtime->__api->new_address_object($cfunc_address)
              );
            }
          }
        }
      }
    }
  }
}

my $BIND_TO_PERL_BASIC_TYPE_NAME_H = {};
sub bind_to_perl {
  my ($basic_type_name) = @_;
  
  my $env = $API->env;
  
  my $compiler = $env->compiler;
  
  my $runtime = $compiler->get_runtime;
    
  my $basic_type = $runtime->get_basic_type_by_name($basic_type_name);
  
  my $perl_basic_type_name_base = "SPVM::";
  my $perl_basic_type_name = "$perl_basic_type_name_base$basic_type_name";
  
  unless ($BIND_TO_PERL_BASIC_TYPE_NAME_H->{$perl_basic_type_name}) {
    
    my $parent_basic_type = $basic_type->get_parent;
    
    # The inheritance
    my @isa;
    if (defined $parent_basic_type) {
      my $parent_basic_type_name = $parent_basic_type->get_name->to_string;
      push @isa, "$perl_basic_type_name_base$parent_basic_type_name";
    }
    push @isa, 'SPVM::BlessedObject::Class';
    my $isa = "our \@ISA = (" . join(',', map { "'$_'" } @isa) . ");";
    
    my $code = "package $perl_basic_type_name; $isa";
    eval $code;
    
    if (my $error = $@) {
      confess $error;
    }
    
    my $methods_length = $basic_type->get_methods_length;
    for (my $method_index = 0; $method_index < $methods_length; $method_index++) {
      my $method = $basic_type->get_method_by_index($method_index);
      
      my $method_name = $method->get_name->to_string;
      
      # Destrutor is skip
      if ($method_name eq 'DESTROY') {
        next;
      }
      # Anon method is skip
      elsif (length $method_name == 0) {
        next;
      }
      
      my $perl_method_abs_name = "${perl_basic_type_name}::$method_name";
      my $is_class_method = $method->is_class_method;
      
      if ($is_class_method) {
        # Define Perl method
        no strict 'refs';
        
        # Suppress refer to objects
        my $basic_type_name_string = "$basic_type_name";
        my $method_name_string = "$method_name";
        
        *{"$perl_method_abs_name"} = sub {
          my $perl_basic_type_name = shift;
          
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
    
    $BIND_TO_PERL_BASIC_TYPE_NAME_H->{$perl_basic_type_name} = 1;
  }
}

=head1 Name

SPVM::Global - SPVM Global Instance for Perl Interpreter

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
