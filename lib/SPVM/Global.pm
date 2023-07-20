package SPVM::Global;
use strict;
use warnings;
use Carp 'confess';

use SPVM::BlessedObject;
use SPVM::BlessedObject::Array;
use SPVM::BlessedObject::Class;
use SPVM::BlessedObject::String;
use SPVM::ExchangeAPI;

use SPVM ();
use SPVM::Builder;
use SPVM::ExchangeAPI;

use SPVM 'Native::Compiler';
use SPVM 'Native::Runtime';
use SPVM 'Native::Env';
use SPVM 'Native::Stack';

our $BUILDER;
our $BUILDER_COMPILER;
our $BUILDER_ENV;
our $BUILDER_STACK;
our $COMPILER;
our $ENV;
our $STACK;
our $API;

END {
  $API = undef;
  if ($ENV) {
    $ENV->destroy_class_vars($STACK);
  }
  $STACK = undef;
  $ENV = undef;
  $COMPILER = undef;
  # if ($BUILDER_ENV) {
  #   $BUILDER_ENV->destroy_class_vars($BUILDER_STACK);
  #}
  $BUILDER_STACK = undef;
  $BUILDER_ENV = undef;
  $BUILDER_COMPILER = undef;
  $BUILDER = undef;
}

sub build_module {
  my ($basic_type_name, $file, $line) = @_;
  
  &init_global();
  
  if (defined $basic_type_name) {
    
    my $start_runtime = $COMPILER->get_runtime;
    my $start_basic_types_length = $start_runtime->get_basic_types_length;
    
    $COMPILER->set_start_file($file);
    $COMPILER->set_start_line($line);
    my $success = $COMPILER->compile($basic_type_name);
    unless ($success) {
      my $error_messages = $COMPILER->get_error_messages;
      for my $error_message (@$error_messages) {
        printf STDERR "[CompileError]$error_message\n";
      }
      $COMPILER = undef;
      exit(255);
    }
    
    my $runtime = $COMPILER->get_runtime;
    
    my $basic_types_length = $runtime->get_basic_types_length;
    
    my $api = SPVM::ExchangeAPI->new(env => $runtime->{env}, stack => $runtime->{stack});
    for (my $basic_type_id = $start_basic_types_length; $basic_type_id < $basic_types_length; $basic_type_id++) {
      my $basic_type = $runtime->get_basic_type_by_id($basic_type_id);
      &load_dynamic_lib($runtime, $basic_type, $api);
    }
    
    &bind_to_perl($basic_type_name);
  }
}

my $INIT_GLOBAL;
sub init_global {
  unless ($INIT_GLOBAL) {
    unless ($BUILDER) {
      my $build_dir = SPVM::Builder::Util::get_normalized_env('SPVM_BUILD_DIR');
      $BUILDER = SPVM::Builder->new(build_dir => $build_dir);
    }
    
    $BUILDER_COMPILER = SPVM::Builder::Compiler->new(
      include_dirs => $BUILDER->include_dirs
    );
    
    my @native_compiler_modules = qw(
      Native::Compiler
      Native::Method
      Native::Runtime
      Native::BasicType
      Native::Stack
      Native::Env
    );
    
    for my $native_compiler_module (@native_compiler_modules) {
      $BUILDER_COMPILER->compile_with_exit($native_compiler_module, __FILE__, __LINE__);
      my $builder_runtime = $BUILDER_COMPILER->get_runtime;
      my $native_method_addresses = &get_native_method_addresses($builder_runtime, $native_compiler_module);
      for my $method_name (keys %$native_method_addresses) {
        my $native_method_address = $native_method_addresses->{$method_name};
        $builder_runtime->set_native_method_address($native_compiler_module, $method_name, $native_method_address);
      }
    }
    
    # Build an environment
    $BUILDER_ENV = SPVM::Builder->new_env($BUILDER_COMPILER);
    
    # Set command line info
    $BUILDER_STACK = SPVM::Builder->new_stack($BUILDER_ENV);
    
    $COMPILER = SPVM::Builder->new_native_compiler($BUILDER_ENV, $BUILDER_STACK);
    for my $include_dir (@{$BUILDER->include_dirs}) {
      $COMPILER->add_include_dir($include_dir);
    }
    $COMPILER->compile(undef);
    my $runtime = $COMPILER->get_runtime;
    
    $INIT_GLOBAL = 1;
  }
}

sub init_api {
  
  &init_global();
  
  $ENV = SPVM::Builder->new_native_env($COMPILER->{env}, $COMPILER->{stack}, $COMPILER);
  
  $STACK = $ENV->new_stack;
  
  $ENV->set_command_info_program_name($STACK, $0);
  
  $ENV->set_command_info_argv($STACK, \@ARGV);
  my $base_time = $^T + 0; # For Perl 5.8.9
  $ENV->set_command_info_base_time($STACK, $base_time);
  
  $ENV->call_init_methods($STACK);
  
  my $builder_env = SPVM::Builder->convert_native_env_to_builder_env($ENV);
  my $builder_stack = SPVM::Builder->convert_native_stack_to_builder_stack($STACK);
  
  $API = SPVM::ExchangeAPI->new(env => $builder_env, stack => $builder_stack);
}

sub get_native_method_addresses {
  my ($builder_runtime, $basic_type_name) = @_;
  
  my $category = 'native';
  my $method_names = $builder_runtime->get_method_names($basic_type_name, $category);
  
  my $native_method_addresses = {};
  if (@$method_names) {
    my $module_file = $builder_runtime->get_module_file($basic_type_name);
    my $dynamic_lib_file = SPVM::Builder::Util::get_dynamic_lib_file_dist($module_file, $category);
    
    if (-f $dynamic_lib_file) {
      my $method_addresses = SPVM::Builder::Util::get_method_addresses($dynamic_lib_file, $basic_type_name, $method_names, $category);
      
      for my $method_name (sort keys %$method_addresses) {
        my $cfunc_address = $method_addresses->{$method_name};
        $native_method_addresses->{$method_name} = $cfunc_address;
      }
    }
  }
  
  return $native_method_addresses;
}

sub load_dynamic_lib {
  my ($runtime, $basic_type, $api) = @_;
    
    my $basic_type_name = $basic_type->get_name->to_string;
    
    my $spvm_module_dir = $basic_type->get_module_dir;
    my $spvm_module_rel_file = $basic_type->get_module_rel_file;
    
    for my $category ('precompile', 'native') {
      
      my $get_method_names_options = $api->new_options({
        $category => $api->class('Int')->new(1)
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
        
        if ($spvm_module_dir) {
          
          my $module_file = "$spvm_module_dir/$spvm_module_rel_file";
          my $dynamic_lib_file = SPVM::Builder::Util::get_dynamic_lib_file_dist($module_file, $category);
          
          # Try to build the shared library at runtime if shared library is not found
          unless (-f $dynamic_lib_file) {
            my $dl_func_list = SPVM::Builder::Util::create_dl_func_list(
              $basic_type_name,
              $category_method_names,
              {category => $category}
            );
            
            my $precompile_source = $runtime->build_precompile_module_source($basic_type)->to_string;
            
            $dynamic_lib_file = $BUILDER->build_at_runtime(
              $basic_type_name,
              {
                module_file => $module_file,
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
                  $api->new_address_object($cfunc_address)
                );
              }
              elsif ($category eq 'precompile') {
                $method->set_precompile_address(
                  $api->new_address_object($cfunc_address)
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
  
  my $runtime = $COMPILER->get_runtime;
    
  my $basic_type = $runtime->get_basic_type_by_name($basic_type_name);
  
  my $perl_basic_type_name_base = "SPVM::";
  my $perl_basic_type_name = "$perl_basic_type_name_base$basic_type_name";
  
  unless ($BIND_TO_PERL_BASIC_TYPE_NAME_H->{$perl_basic_type_name}) {
    
    my $parent_basic_type = $basic_type->get_parent;
    
    # The inheritance
    my @isa;
    if (defined $parent_basic_type) {
      my $parent_basic_type_name = $parent_basic_type->get_name;
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
      
      my $method_name = $method->get_name;
      
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
