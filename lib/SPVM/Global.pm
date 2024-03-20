package SPVM::Global;
use strict;
use warnings;
use Carp 'confess';

use SPVM::Builder;
use SPVM::Builder::Native::Env;
use SPVM::ExchangeAPI;

my $COMPILER;
my $API;

END {
  
  if ($API) {
    {
      # Remove circular reference
      my $env = delete $API->{env};
      my $stack = delete $API->{stack};
      
      $env->destroy_class_vars($stack);
    }
    
    $API = undef;
    
    $COMPILER = undef;
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
    
    my $api = $API;
    my $compiler = $COMPILER;
    
    my $env = $api->env;
    
    my $runtime = $compiler->get_runtime;
    my $start_basic_types_length = $runtime->get_basic_types_length;
    
    $compiler->compile_with_exit($class_name, __FILE__, __LINE__);
    
    my $basic_types_length = $runtime->get_basic_types_length;
    
    for (my $basic_type_id = $start_basic_types_length; $basic_type_id < $basic_types_length; $basic_type_id++) {
      my $basic_type = $runtime->get_basic_type_by_id($basic_type_id);
      my $class_name = $basic_type->get_name;
      
      &load_dynamic_lib($runtime, $class_name);
    }
    
    my $stack = $api->stack;
    
    $env->call_init_methods($stack);
    
    &bind_to_perl($class_name);
  }
}

sub init_api {
  unless ($API) {
    my $build_dir = SPVM::Builder::Util::get_normalized_env('SPVM_BUILD_DIR');
    my $builder = SPVM::Builder->new(build_dir => $build_dir);
    
    my $compiler = SPVM::Builder::Native::Compiler->new;
    
    for my $include_dir (@{$builder->include_dirs}) {
      $compiler->add_include_dir($include_dir);
    }
    
    my $runtime = $compiler->get_runtime;
    
    my $start_basic_types_length = $runtime->get_basic_types_length;
    
    $compiler->compile_with_exit(undef, __FILE__, __LINE__);
    
    my $basic_types_length = $runtime->get_basic_types_length;
    
    for (my $basic_type_id = $start_basic_types_length; $basic_type_id < $basic_types_length; $basic_type_id++) {
      my $basic_type = $runtime->get_basic_type_by_id($basic_type_id);
      my $class_name = $basic_type->get_name;
      
      &load_dynamic_lib($runtime, $class_name);
    }
    
    my $env = $runtime->new_env;
    
    my $stack = $env->new_stack;
    
    my $api = SPVM::ExchangeAPI->new(env => $env, stack => $stack);
    
    $COMPILER = $compiler;
    $API = $api;
    
    $env->set_command_info_program_name($stack, $0);
    
    $env->set_command_info_argv($stack, \@ARGV);
    my $base_time = $^T + 0; # For Perl 5.8.9
    $env->set_command_info_base_time($stack, $base_time);
  }
}

sub load_dynamic_lib {
  my ($runtime, $class_name) = @_;
  
  for my $category ('precompile', 'native') {
    my $method_names = $runtime->get_method_names($class_name, $category);
    
    if (@$method_names) {
      # Build classes - Compile C source codes and link them generating a dynamic link library
      my $class_file = $runtime->get_class_file($class_name);
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
        my $method_addresses = SPVM::Builder::Util::get_method_addresses($dynamic_lib_file, $class_name, $method_names, $category);
        
        for my $method_name (sort keys %$method_addresses) {
          my $cfunc_address = $method_addresses->{$method_name};
          if ($category eq 'precompile') {
            $runtime->set_precompile_method_address($class_name, $method_name, $cfunc_address);
          }
          elsif ($category eq 'native') {
            $runtime->set_native_method_address($class_name, $method_name, $cfunc_address);
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
  
  my $runtime = $env->runtime;
  
  my $basic_type = $runtime->get_basic_type_by_name($class_name);
  
  my $perl_class_name_base = "SPVM::";
  my $perl_class_name = "$perl_class_name_base$class_name";
  
  unless ($BIND_TO_PERL_CLASS_NAME_H->{$perl_class_name}) {
    
    my $parent_basic_type = $basic_type->get_parent;
    
    # The inheritance
    my @isa;
    if (defined $parent_basic_type) {
      my $parent_basic_type_name = $parent_basic_type->get_name;
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
      
      my $method_name = $method->get_name;
      
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
