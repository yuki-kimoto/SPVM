package SPVM::Global;
use strict;
use warnings;
use Carp 'confess';

use SPVM::Builder;
use SPVM::Builder::Native::Runtime::Info;
use SPVM::ExchangeAPI;

my $COMPILER;
my $API;

my $BUILDER_COMPILER;
my $BUILDER_API;

END {
  
  if ($API) {
    # TODO - this compilation is removed in the near feature
    #        because the SPVM language must be compile by C and Perl only.
    
    {
      # Remove circular reference
      my $env = delete $API->{env};
      my $stack = delete $API->{stack};
      
      my $native_api = $BUILDER_API->class("Native::API")->new($env, $stack);
      
      $native_api->destroy_class_vars;
    }
    
    $API = undef;
    
    $COMPILER = undef;
    
    {
      # Remove circular reference
      my $env = delete $BUILDER_API->{env};
      my $stack = delete $BUILDER_API->{stack};
      
      $env->destroy_class_vars($stack);
    }
    
    $BUILDER_API = undef;
    
    $BUILDER_COMPILER = undef;
  }
}

sub api {
  
  unless ($API) {
    &init_api();
  }
  return $API;
}

sub build_class {
  my ($class_name, $file, $line) = @_;
  
  &init_api();
  
  # Add module informations
  my $build_success;
  if (defined $class_name) {
    
    # TODO - this compilation is removed in the near feature
    #        because the SPVM language must be compile by C and Perl only.
    {
      my $api = $API;
      my $compiler = $COMPILER;
      
      my $env = $api->env;
      
      my $runtime = $compiler->get_runtime;
      my $start_basic_types_length = $runtime->get_basic_types_length;
      
      $compiler->set_start_file($file);
      $compiler->set_start_line($line);
      eval { $compiler->compile($class_name) };
      if ($@) {
        my $error_messages = $compiler->get_error_messages;
        for my $error_message (@$error_messages) {
          printf STDERR "[CompileError]$error_message\n";
        }
        $compiler = undef;
        exit(255);
      }
      my $basic_types_length = $runtime->get_basic_types_length;
      
      for (my $basic_type_id = $start_basic_types_length; $basic_type_id < $basic_types_length; $basic_type_id++) {
        my $basic_type = $runtime->get_basic_type_by_id($basic_type_id);
        &load_dynamic_lib($runtime, $basic_type->get_name->to_string);
      }
      
      &bind_to_perl($class_name);
      
      my $stack = $api->stack;
      
      my $native_api = $BUILDER_API->class("Native::API")->new($env, $stack);
      
      $native_api->call_init_methods;
    }
    
    {
      my $api = $BUILDER_API;
      my $compiler = $BUILDER_COMPILER;
      
      my $env = $api->env;
      
      my $runtime = $compiler->get_runtime;
      my $start_basic_types_length = $runtime->get_basic_types_length;
      
      $compiler->compile_with_exit($class_name, __FILE__, __LINE__);
      
      my $basic_types_length = $runtime->get_basic_types_length;
      
      # Load dynamic library
      for my $category ('precompile', 'native') {
        my $method_names = $runtime->get_method_names($class_name, $category);
        
        if (@$method_names) {
          # Build classes - Compile C source codes and link them generating a dynamic link library
          my $class_file = $runtime->get_class_file($class_name);
          my $dynamic_lib_file = SPVM::Builder::Util::get_dynamic_lib_file_dist($class_file, $category);
          
          if (-f $dynamic_lib_file) {
            my $method_addresses = SPVM::Builder::Util::get_method_addresses($dynamic_lib_file, $class_name, $method_names, $category);
            
            for my $method_name (sort keys %$method_addresses) {
              my $cfunc_address = $method_addresses->{$method_name};
              $runtime->set_native_method_address($class_name, $method_name, $cfunc_address);
            }
          }
        }
      }
    }
  }
}

sub init_api {
  unless ($API) {
    my $build_dir = SPVM::Builder::Util::get_normalized_env('SPVM_BUILD_DIR');
    my $builder = SPVM::Builder->new(build_dir => $build_dir);
    
    my $builder_compiler = SPVM::Builder::Native::Compiler->new(
      include_dirs => $builder->include_dirs
    );
    
    my @native_compiler_class_name_names = qw(
      Native::Compiler
      Native::Method
      Native::Runtime
      Native::BasicType
      Native::Stack
      Native::Env
      Native::API
    );
    
    my $builder_runtime = $builder_compiler->get_runtime;
    
    my $builder_runtime_info = SPVM::Builder::Native::Runtime::Info->new(boot_env => $builder_runtime->boot_env, runtime => $builder_runtime);
    
    for my $native_compiler_class_name_name (@native_compiler_class_name_names) {
      $builder_compiler->compile_with_exit($native_compiler_class_name_name, __FILE__, __LINE__);
      
      # Load dinamic libnaray - native only
      {
        my $class_name = $native_compiler_class_name_name;
        my $category = 'native';
        my $method_names = $builder_runtime_info->get_method_names($class_name, $category);
        
        if (@$method_names) {
          # Build classes - Compile C source codes and link them generating a dynamic link library
          my $class_file = $builder_runtime->get_class_file($class_name);
          my $dynamic_lib_file = SPVM::Builder::Util::get_dynamic_lib_file_dist($class_file, $category);
          
          if (-f $dynamic_lib_file) {
            my $method_addresses = SPVM::Builder::Util::get_method_addresses($dynamic_lib_file, $class_name, $method_names, $category);
            
            for my $method_name (sort keys %$method_addresses) {
              my $cfunc_address = $method_addresses->{$method_name};
              $builder_runtime->set_native_method_address($class_name, $method_name, $cfunc_address);
            }
          }
        }
      }
    }
    
    my $builder_env = SPVM::Builder::Native::Env->new($builder_compiler);
    
    my $builder_stack = $builder_env->new_stack;
    
    my $builder_api = SPVM::ExchangeAPI->new(env => $builder_env, stack => $builder_stack);
    
    $BUILDER_COMPILER = $builder_compiler;
    $BUILDER_API = $builder_api;
    
    {
      $builder_env->set_command_info_program_name($builder_stack, $0);
      
      $builder_env->set_command_info_argv($builder_stack, \@ARGV);
      my $base_time = $^T + 0; # For Perl 5.8.9
      $builder_env->set_command_info_base_time($builder_stack, $base_time);
    }
    
    my $compiler = $builder_api->class("Native::Compiler")->new;
    for my $include_dir (@{$builder->include_dirs}) {
      $compiler->add_include_dir($include_dir);
    }
    
    $compiler->compile(undef);
    
    my $runtime = $compiler->get_runtime;
    
    my $env = $runtime->new_env;
    
    my $stack = $env->new_stack;
    
    $COMPILER = $compiler;
    $API = SPVM::ExchangeAPI->new(env => $env, stack => $stack);
    
    my $native_api = $builder_api->class("Native::API")->new($env, $stack);
    
    $native_api->set_command_info_program_name($0);
    
    $native_api->set_command_info_argv(\@ARGV);
    
    my $base_time = $^T + 0; # +0 is for Perl 5.8.9
    $native_api->set_command_info_base_time($base_time);
  }
}

sub load_dynamic_lib {
  my ($runtime, $class_name) = @_;
  
  my $basic_type = $runtime->get_basic_type_by_name($class_name);
  
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
      
      my $spvm_class_dir = $basic_type->get_class_dir;
      if ($spvm_class_dir) {
        
        my $spvm_class_rel_file = $basic_type->get_class_rel_file;
        
        my $class_file = "$spvm_class_dir/$spvm_class_rel_file";
        my $dynamic_lib_file = SPVM::Builder::Util::get_dynamic_lib_file_dist($class_file, $category);
        
        # Try to build the shared library at runtime if shared library is not found
        unless (-f $dynamic_lib_file) {
          my $build_dir = SPVM::Builder::Util::get_normalized_env('SPVM_BUILD_DIR');
          my $builder = SPVM::Builder->new(build_dir => $build_dir);
          $dynamic_lib_file = $builder->build_jit(
            $class_name,
            {
              runtime => $runtime,
              class_file => $class_file,
              category => $category,
            }
          );
        }
        
        if (-f $dynamic_lib_file) {
          my $method_addresses = SPVM::Builder::Util::get_method_addresses(
            $dynamic_lib_file,
            $class_name,
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

my $BIND_TO_PERL_CLASS_NAME_H = {};
sub bind_to_perl {
  my ($class_name) = @_;
  
  my $env = $API->env;
  
  my $compiler = $env->runtime->get_compiler;
  
  my $runtime = $compiler->get_runtime;
  
  my $basic_type = $runtime->get_basic_type_by_name($class_name);
  
  my $perl_class_name_base = "SPVM::";
  my $perl_class_name = "$perl_class_name_base$class_name";
  
  unless ($BIND_TO_PERL_CLASS_NAME_H->{$perl_class_name}) {
    
    my $parent_basic_type = $basic_type->get_parent;
    
    # The inheritance
    my @isa;
    if (defined $parent_basic_type) {
      my $parent_basic_type_name = $parent_basic_type->get_name->to_string;
      push @isa, "$perl_class_name_base$parent_basic_type_name";
    }
    push @isa, 'SPVM::BlessedObject::Class';
    my $isa = "our \@ISA = (" . join(',', map { "'$_'" } @isa) . ");";
    
    my $code = "package $perl_class_name; $isa";
    eval $code;
    
    if (my $error = $@) {
      confess($error);
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
      
      my $perl_method_abs_name = "${perl_class_name}::$method_name";
      my $is_class_method = $method->is_class_method;
      
      if ($is_class_method) {
        # Define Perl method
        no strict 'refs';
        
        # Suppress refer to objects
        my $class_name_string = "$class_name";
        my $method_name_string = "$method_name";
        
        *{"$perl_method_abs_name"} = sub {
          my $perl_class_name = shift;
          
          my $return_value;
          
          eval { $return_value = SPVM::api()->call_method($class_name_string, $method_name_string, @_) };
          my $error = $@;
          if ($error) {
            confess($error);
          }
          $return_value;
        };
      }
    }
    
    $BIND_TO_PERL_CLASS_NAME_H->{$perl_class_name} = 1;
  }
}

=head1 Name

SPVM::Global - SPVM Global Instance

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
