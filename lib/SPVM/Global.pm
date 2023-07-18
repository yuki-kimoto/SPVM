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

our $BUILDER;
our $BUILDER_COMPILER;
our $BUILDER_ENV;
our $BUILDER_STACK;
our $BUILDER_API;
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
  $BUILDER_API = undef;
  if ($BUILDER_ENV) {
    $BUILDER_ENV->destroy_class_vars($BUILDER_STACK);
  }
  $BUILDER_STACK = undef;
  $BUILDER_ENV = undef;
  $BUILDER_COMPILER = undef;
  $BUILDER = undef;
}

sub build_module {
  my ($module_name, $file, $line) = @_;
  
  &init_global();
  
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
    
    my $runtime = $COMPILER->get_runtime;
    
    &load_dynamic_libs($runtime);
    
    &bind_to_perl($module_name);
  }
}

sub init_global {
  unless ($COMPILER) {
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
    
    my $builder_runtime = $BUILDER_COMPILER->get_runtime;
    
    $builder_runtime->load_dynamic_libs;
    
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
    my $runtime = $COMPILER->get_runtime;
    
    &load_dynamic_libs($runtime);
  }
}

sub init_api {
  
  &init_global();
  
  $ENV = $BUILDER_API->class("Native::Env")->new($COMPILER);
  
  $STACK = $ENV->new_stack;
  
  $ENV->set_command_info_program_name($STACK, $0);
  
  $ENV->set_command_info_argv($STACK, \@ARGV);
  my $base_time = $^T + 0; # For Perl 5.8.9
  $ENV->set_command_info_base_time($STACK, $base_time);
  
  $ENV->call_init_methods($STACK);
  
  $API = SPVM::ExchangeAPI->new(env => $ENV, stack => $STACK);
}

sub load_dynamic_libs {
  my ($runtime) = @_;
  
  my $basic_types_length = $runtime->get_basic_types_length;
  
  # Set addresses of native methods and precompile methods
  for (my $basic_type_id = 0; $basic_type_id < $basic_types_length; $basic_type_id++) {
    my $basic_type = $runtime->get_basic_type_by_id($basic_type_id);
    
    my $basic_type_name = $basic_type->get_name->to_string;
    
    my $spvm_module_dir = $basic_type->get_module_dir;
    my $spvm_module_rel_file = $basic_type->get_module_rel_file;
    
    for my $category ('precompile', 'native') {
      
      my $get_method_names_options = $runtime->__api->new_options({
        $category => $runtime->__api->class('Int')->new(1)
      });
      
      my $category_method_names;
      
      if ($category eq 'native') {
        $category_method_names = &get_native_method_names($basic_type);
      }
      elsif ($category eq 'precompile') {
        $category_method_names = &get_precompile_method_names($basic_type);
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
}

sub get_native_method_names {
  my ($basic_type) = @_;
  
  my $methods_length = $basic_type->get_methods_length;
  
  my $native_method_names = [];
  for (my $index = 0; $index < $methods_length; $index++) {
    my $method = $basic_type->get_method_by_index($index);
    
    if ($method->is_native) {
      push @$native_method_names, $method->get_name->to_string;
    }
  }
  
  return $native_method_names;
}

sub get_precompile_method_names {
  my ($basic_type) = @_;
  
  my $methods_length = $basic_type->get_methods_length;
  
  my $precompile_method_names = [];
  for (my $index = 0; $index < $methods_length; $index++) {
    my $method = $basic_type->get_method_by_index($index);
    
    if ($method->is_precompile) {
      push @$precompile_method_names, $method->get_name->to_string;
    }
  }
  
  return $precompile_method_names;
}

my $BIND_TO_PERL_MODULE_NAME_H = {};
sub bind_to_perl {
  my ($basic_type_name) = @_;
  
  my $runtime = $COMPILER->get_runtime;
    
  my $basic_type = $runtime->get_basic_type_by_name($basic_type_name);
  
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
      my $is_class_method = $method->is_class_method;
      
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

=head1 Name

SPVM::Global - SPVM Global Instance for Perl Interpreter

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
