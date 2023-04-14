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

  my $class_names = $runtime->get_class_names->to_strings;

  # Set addresses of native methods and precompile methods
  for my $class_name (@$class_names) {
    next if $class_name =~ /::anon/;
    
    for my $category ('precompile', 'native') {

      my $get_method_names_options = $runtime->__api->new_options({
        $category => $runtime->__api->class('Int')->new(1)
      });
      
      my $method_names = $runtime->get_method_names($class_name, $get_method_names_options)->to_strings;
      
      if (@$method_names) {
        # Build classs - Compile C source codes and link them to SPVM precompile method
        # Shared library which is already installed in distribution directory
        my $class_file = $runtime->get_class_file($class_name)->to_string;
        my $dynamic_lib_file = SPVM::Builder::Util::get_dynamic_lib_file_dist($class_file, $category);
        
        # Try to build the shared library at runtime if shared library is not found
        unless (-f $dynamic_lib_file) {
          my $class_file = $runtime->get_class_file($class_name)->to_string;
          my $method_names = $runtime->get_method_names($class_name, $get_method_names_options)->to_strings;
          my $anon_class_names = $runtime->get_anon_class_names($class_name)->to_strings;
          my $dl_func_list = SPVM::Builder::Util::create_dl_func_list($class_name, $method_names, $anon_class_names, {category => $category});
          my $precompile_source = $runtime->build_precompile_class_source($class_name)->to_string;
          
          $dynamic_lib_file = $BUILDER->build_at_runtime($class_name, {class_file => $class_file, category => $category, dl_func_list => $dl_func_list, precompile_source => $precompile_source});
        }
        
        if (-f $dynamic_lib_file) {
          $dynamic_lib_files->{$category}{$class_name} = $dynamic_lib_file;
        }
      }
    }
  }

  # Set function addresses of native and precompile methods
  for my $category ('precompile', 'native') {
    my $get_method_names_options = $runtime->__api->new_options({
      $category => $runtime->__api->class('Int')->new(1)
    });
    
    for my $class_name (keys %{$dynamic_lib_files->{$category}}) {
      next unless grep { "$_" eq $class_name } @$class_names;
      
      my $dynamic_lib_file = $dynamic_lib_files->{$category}{$class_name};
      my $method_names = $runtime->get_method_names($class_name, $get_method_names_options)->to_strings;
      my $anon_class_names = $runtime->get_anon_class_names($class_name)->to_strings;
      my $method_addresses = SPVM::Builder::Util::get_method_addresses($dynamic_lib_file, $class_name, $method_names, $anon_class_names, $category);
      
      for my $method_name (sort keys %$method_addresses) {
        my $cfunc_address = $method_addresses->{$method_name};
        if ($category eq 'native') {
          $runtime->set_native_method_address($class_name, $method_name, $runtime->__api->new_address_object($cfunc_address));
        }
        elsif ($category eq 'precompile') {
          $runtime->set_precompile_method_address($class_name, $method_name, $runtime->__api->new_address_object($cfunc_address));
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
    
    my $builder_compiler = SPVM::Builder::Compiler->new(
      class_paths => $BUILDER->class_paths
    );
    # Load SPVM Compilers
    $builder_compiler->use("Compiler", __FILE__, __LINE__);
    $builder_compiler->use("Runtime", __FILE__, __LINE__);
    $builder_compiler->use("Env", __FILE__, __LINE__);
    $builder_compiler->use("Stack", __FILE__, __LINE__);
    
    my $builder_runtime = $builder_compiler->build_runtime;

    $builder_runtime->load_dynamic_libs;

    # Build an environment
    $BUILDER_ENV = $builder_runtime->build_env;
    
    # Set command line info
    $BUILDER_ENV->set_command_info_program_name($0);
    $BUILDER_ENV->set_command_info_argv(\@ARGV);
    my $base_time = $^T + 0; # For Perl 5.8.9
    $BUILDER_ENV->set_command_info_base_time($base_time);
    
    # Call INIT blocks
    $BUILDER_ENV->call_init_blocks;
    
    $BUILDER_STACK = $BUILDER_ENV->build_stack;
    
    $BUILDER_API = SPVM::ExchangeAPI->new(env => $BUILDER_ENV, stack => $BUILDER_STACK);
    
    $COMPILER = $BUILDER_API->class("Compiler")->new;
    for my $class_path (@{$BUILDER->class_paths}) {
      $COMPILER->add_class_path($class_path);
    }
    $RUNTIME = $COMPILER->build_runtime;

    &load_dynamic_libs($RUNTIME, $DYNAMIC_LIB_FILES);
  }
}

my $BIND_TO_PERL_CLASS_NAME_H = {};
sub bind_to_perl {
  my ($class_name) = @_;
  
  my $perl_class_name_base = "SPVM::";
  my $perl_class_name = "$perl_class_name_base$class_name";
  
  unless ($BIND_TO_PERL_CLASS_NAME_H->{$perl_class_name}) {
    
    my $parent_class_name = $RUNTIME->get_parent_class_name($class_name);
    my $parent_class_name_str = defined $parent_class_name ? "($parent_class_name)" : "()";
    
    # The inheritance
    my @isa;
    if (defined $parent_class_name) {
      push @isa, "$perl_class_name_base$parent_class_name";
    }
    push @isa, 'SPVM::BlessedObject::Class';
    my $isa = "our \@ISA = (" . join(',', map { "'$_'" } @isa) . ");";
    
    my $code = "package $perl_class_name; $isa";
    eval $code;
    
    if (my $error = $@) {
      confess $error;
    }
    $BIND_TO_PERL_CLASS_NAME_H->{$perl_class_name_base}{$perl_class_name} = 1;
  }

  my $method_names = $RUNTIME->get_method_names($class_name);

  for my $method_name (@$method_names) {
    
    # Destrutor is skip
    if ($method_name eq 'DESTROY') {
      next;
    }
    # Anon method is skip
    elsif (length $method_name == 0) {
      next;
    }
    
    my $perl_method_abs_name = "${perl_class_name}::$method_name";
    my $is_class_method = $RUNTIME->get_method_is_class_method($class_name, $method_name);
    
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
          confess $error;
        }
        $return_value;
      };
    }
  }
}


sub build_class {
  my ($class_name, $file, $line) = @_;
  
  unless ($BUILDER) {
    my $build_dir = SPVM::Builder::Util::get_normalized_env('SPVM_BUILD_DIR');
    $BUILDER = SPVM::Builder->new(build_dir => $build_dir);
  }
  
  my $start_classes_length = 0;
  if ($RUNTIME) {
    $start_classes_length = $RUNTIME->get_classes_length;
  }
  
  &init_runtime();
  
  # Add class informations
  my $build_success;
  if (defined $class_name) {
    
    $COMPILER->set_start_file($file);
    $COMPILER->set_start_line($line);
    my $success = $COMPILER->compile($class_name);
    unless ($success) {
      my $error_messages = $COMPILER->get_error_messages;
      for my $error_message (@$error_messages) {
        printf STDERR "[CompileError]$error_message\n";
      }
      $COMPILER = undef;
      exit(255);
    }
    $RUNTIME = $COMPILER->build_runtime;

    &load_dynamic_libs($RUNTIME, $DYNAMIC_LIB_FILES);
  }
}

sub init_api {
  &init_runtime();
  
  $ENV = $RUNTIME->build_env;
  
  $ENV->set_command_info_program_name($0);
  $ENV->set_command_info_argv(\@ARGV);
  my $base_time = $^T + 0; # For Perl 5.8.9
  $ENV->set_command_info_base_time($base_time);
  
  $ENV->call_init_blocks;
  
  $STACK = $ENV->build_stack;
  
  $API = SPVM::ExchangeAPI->new(env => $ENV, stack => $STACK);
}

END {
  $BUILDER = undef;
  $COMPILER = undef;
  $API = undef;
  $STACK = undef;
  $ENV = undef;
  $RUNTIME = undef;
  $DYNAMIC_LIB_FILES = undef;
  $BUILDER_API = undef;
  $BUILDER_STACK = undef;
  $BUILDER_ENV = undef;
}

=head1 Name

SPVM::Global - SPVM Global Instance for Perl Interpreter

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
