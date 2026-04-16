package SPVM::Global;
use strict;
use warnings;
use Carp 'confess';
use File::Temp;

use SPVM::Builder::Util;
use SPVM::Builder;
use SPVM::Builder::Native::Env;
use SPVM::ExchangeAPI;
use File::Path 'rmtree';
use Time::HiRes;
use Fcntl qw(O_RDONLY);

my $COMPILER;
my $API;
my $BUILDER;
my $DYNAMIC_LIB_LIBREFS_H = {};
my $DYNAMIC_LIB_FILES_H = {};
my $DYNAMIC_LIB_FILE_IS_JIT_H = {};

# Accessed from SPVM::Builder
our $BUILD_TMP_DIR;

END {
  
  if ($API) {
    {
      # Remove circular reference
      my $env = delete $API->{env};
      my $stack = delete $API->{stack};
      
      $env->call_end_methods($stack);
      
      $env->destroy_class_vars($stack);
    }
    
    $API = undef;
    
    $COMPILER = undef;
    
    for my $dynamic_lib_file (keys %$DYNAMIC_LIB_LIBREFS_H) {
      my $dynamic_lib_libref = $DYNAMIC_LIB_LIBREFS_H->{$dynamic_lib_file};
      DynaLoader::dl_unload_file($dynamic_lib_libref);
    }
    
    for my $dynamic_lib_file_for_jit (keys %$DYNAMIC_LIB_FILE_IS_JIT_H) {
      unlink $dynamic_lib_file_for_jit
        or confess("[Unexpected Error]Cannot unlink '$dynamic_lib_file_for_jit':$!");
    }
    
    $BUILDER = undef;
    
    if (defined $BUILD_TMP_DIR) {
      rmtree $BUILD_TMP_DIR;
    }
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
  
  my $options = {
    class_name => $class_name,
    file => $file,
    line => $line,
  };
  
  &build_class_common($options);
}

sub build_anon_class {
  my ($source, $file, $line) = @_;
  
  my $options = {
    source => $source,
    file => $file,
    line => $line,
  };
  
  my $anon_class_name = &build_class_common($options);
  
  return $anon_class_name;
}

sub build_class_common {
  my ($options) = @_;
  
  $options ||= {};
  
  my $class_name = $options->{class_name};
  
  my $source = $options->{source};
  
  my $file = $options->{file};
  
  my $line = $options->{line};
  
  &init_api();
  
  # Add module informations
  my $build_success;
  if (defined $class_name || defined $source) {
    
    my $api = $API;
    my $compiler = $COMPILER;
    
    my $env = $api->env;
    
    my $runtime = $compiler->get_runtime;
    my $start_basic_types_length = $runtime->get_basic_types_length;
    
    if (defined $source) {
      $class_name = $compiler->compile_anon_class_with_exit($source, $file, $line);
    }
    else {
      $compiler->compile_with_exit($class_name, $file, $line);
    }
    
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
  
  return $class_name;
}

sub init_api {
  unless ($API) {
    my $build_dir = SPVM::Builder::Util::get_normalized_env('SPVM_BUILD_DIR');
    $BUILDER //= SPVM::Builder->new(build_dir => $build_dir);
    
    my $compiler = SPVM::Builder::Native::Compiler->new;
    
    for my $include_dir (@{$BUILDER->include_dirs}) {
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
    
    my $env = $runtime->get_env;
    
    my $stack = $env->new_stack;
    
    my $api = SPVM::ExchangeAPI->new(env => $env, stack => $stack);
    
    $COMPILER = $compiler;
    $API = $api;
    
    $env->set_command_info_program_name($stack, $0);
    
    $env->set_command_info_argv($stack, \@ARGV);
    my $base_time = $^T + 0; # For Perl 5.8.9
    $env->set_command_info_basetime($stack, $base_time);
    
    $env->set_command_info_basetime($stack, $base_time);
    
    my $warning = $^W ? 1 : 0;
    $env->set_command_info_warning($stack, $warning);
  }
}

sub load_dynamic_lib {
  my ($runtime, $class_name) = @_;
  
  my $outmost_class_name;
  if ($class_name =~ /^(.*)::anon_method::/) {
    $outmost_class_name = $1;
  }
  else {
    $outmost_class_name = $class_name;
  }
  
  for my $category ('precompile', 'native') {
    my $basic_type = $runtime->get_basic_type_by_name($class_name);
    
    my $method_names = $basic_type->get_method_names_by_category($category);
    
    if (@$method_names) {
      
      # Use the outmost class to find the class file and the dynamic library
      unless ($DYNAMIC_LIB_FILES_H->{$outmost_class_name}{$category}) {
        my $outmost_basic_type = $runtime->get_basic_type_by_name($outmost_class_name);
        my $outmost_class_file = $outmost_basic_type->get_class_file;
        my $dynamic_lib_file_dist = SPVM::Builder::Util::get_dynamic_lib_file_dist($outmost_class_file, $category);
        
        # Try to build the shared library at runtime if shared library is not found
        if (-f $dynamic_lib_file_dist) {
          $DYNAMIC_LIB_FILES_H->{$outmost_class_name}{$category} = $dynamic_lib_file_dist;
        }
        else {
          my $build_options = {
            runtime => $runtime,
            class_file => $outmost_class_file,
            category => $category,
          };
          
          my $env_spvm_cc_quiet = SPVM::Builder::Util::get_normalized_env('SPVM_CC_QUIET');
          if (defined $env_spvm_cc_quiet) {
            $build_options->{quiet} = 1;
          }
          
          my $env_spvm_cc_optimize = SPVM::Builder::Util::get_normalized_env('SPVM_CC_OPTIMIZE');
          if (defined $env_spvm_cc_optimize) {
            $build_options->{optimize} = $env_spvm_cc_optimize;
          }
          
          my $build_dir = SPVM::Builder::Util::get_normalized_env('SPVM_BUILD_DIR');
          $BUILDER //= SPVM::Builder->new(build_dir => $build_dir);
          my $dynamic_lib_file_jit = $BUILDER->build_jit(
            $outmost_class_name,
            $build_options,
          );
          
          $DYNAMIC_LIB_FILES_H->{$outmost_class_name}{$category} = $dynamic_lib_file_jit;
          $DYNAMIC_LIB_FILE_IS_JIT_H->{$dynamic_lib_file_jit} = 1;
        }
      }
      
      if (-f $DYNAMIC_LIB_FILES_H->{$outmost_class_name}{$category}) {
        # Get addresses using the original class_name (containing the anon method name)
        my $method_addresses = &get_method_addresses($DYNAMIC_LIB_FILES_H->{$outmost_class_name}{$category}, $class_name, $method_names, $category);
        
        for my $method_name (sort keys %$method_addresses) {
          my $cfunc_address = $method_addresses->{$method_name};
          my $method = $basic_type->get_method_by_name($method_name);
          if ($category eq 'precompile') {
            $method->set_precompile_address($cfunc_address);
          }
          elsif ($category eq 'native') {
            $method->set_native_address($cfunc_address);
          }
        }
      }
    }
  }
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
        my $dynamic_lib_libref;
        if ($DYNAMIC_LIB_LIBREFS_H->{$dynamic_lib_file}) {
          $dynamic_lib_libref = $DYNAMIC_LIB_LIBREFS_H->{$dynamic_lib_file};
        }
        else {
          # Load dynamic library with a shared lock to prevent race conditions during parallel builds
          unless (defined $ENV{SPVM_BUILD_DIR}) {
            confess("[Unexpected Error]no build directory");
          }
          
          $BUILDER->global_file_lock(sub {
            unless (-f $dynamic_lib_file) {
              confess("\$dynamic_lib_file does not exist.");
            }
            
            unless (sysopen(my $dynamic_lib_fh, $dynamic_lib_file, O_RDONLY)) {
              confess("\$dynamic_lib_file cannot be opened O_RDONLY.");
            }
            
            $dynamic_lib_libref = DynaLoader::dl_load_file($dynamic_lib_file);
          });
          
          $DYNAMIC_LIB_LIBREFS_H->{$dynamic_lib_file} = $dynamic_lib_libref;
        }
        
        if ($dynamic_lib_libref) {

          my $cfunc_name = SPVM::Builder::Util::create_cfunc_name($class_name, $method_name, $category);
          $cfunc_address = DynaLoader::dl_find_symbol($dynamic_lib_libref, $cfunc_name);
          unless ($cfunc_address) {
            my $dl_error = DynaLoader::dl_error();
            my $error = <<"EOS";
Can't find native function '$cfunc_name' corresponding to ${class_name}->$method_name in '$dynamic_lib_file'

You must write the following definition.
--------------------------------------------------
#include <spvm_native.h>

int32_t $cfunc_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}
--------------------------------------------------

$dl_error
EOS
            confess($error);
          }
        }
        else {
          my $dl_error = DynaLoader::dl_error();
          confess("The DynaLoader::dl_load_file function failed:Can't load the '$dynamic_lib_file' file for $category methods in $class_name class: $dl_error");
        }
      }
      else {
        confess("DLL file is not specified");
      }
      
      $method_addresses->{$method_name} = $cfunc_address;
    }
  }
  
  return $method_addresses;
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
    
    # Suppress a warning in child class
    # While trying to resolve method call %s->%s() can not locate package "%s" yet it is mentioned in @%s::ISA (perhaps you forgot to load "%s"?)
    # https://perldoc.perl.org/perldiag
    my $suppress_warning_code = "sub import {} sub CLONE_SKIP { 1 } sub CLONE {}";
    
    my $code = "package $perl_class_name; $isa $suppress_warning_code";
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
