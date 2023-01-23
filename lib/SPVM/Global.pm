package SPVM::Global;
use strict;
use warnings;
use Carp 'confess';

use SPVM::BlessedObject;
use SPVM::BlessedObject::Array;
use SPVM::BlessedObject::Class;
use SPVM::BlessedObject::String;

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

  my $class_names = [map { "$_" } @{$runtime->get_class_names}];

  # Set addresses of native methods and precompile methods
  for my $class_name (@$class_names) {
    next if $class_name =~ /::anon/;
    
    for my $category ('precompile', 'native') {

      my $cc = SPVM::Builder::CC->new(
        build_dir => $SPVM::Global::BUILDER->build_dir,
        at_runtime => 1,
      );
      
      my $get_method_names_options = SPVM::ExchangeAPI::new_any_object_array(
        $runtime->api,
        [
          SPVM::ExchangeAPI::new_string($runtime->api, $category)
          =>
          SPVM::ExchangeAPI::call_method($runtime->api, 'Int', 'new', 1)
        ]
      );
      
      my $method_names = [map { "$_" } @{$runtime->get_method_names($class_name, $get_method_names_options)}];
      
      if (@$method_names) {
        # Build classs - Compile C source codes and link them to SPVM precompile method
        # Shared library which is already installed in distribution directory
        my $module_file = $runtime->get_module_file($class_name);
        my $dynamic_lib_file = SPVM::Builder::Util::get_dynamic_lib_file_dist($module_file, $category);
        
        # Try to build the shared library at runtime if shared library is not found
        unless (-f $dynamic_lib_file) {
          my $module_file = $runtime->get_module_file($class_name);
          my $method_names = $runtime->get_method_names($class_name, $get_method_names_options);
          my $anon_class_names = $runtime->get_anon_class_names($class_name);
          my $dl_func_list = SPVM::Builder::Util::create_dl_func_list($class_name, $method_names, $anon_class_names, {category => $category});
          my $precompile_source = $runtime->build_precompile_class_source($class_name);
          $dynamic_lib_file = $cc->build_at_runtime($class_name, {module_file => $module_file, category => $category, dl_func_list => $dl_func_list, precompile_source => $precompile_source});
        }
        
        if (-f $dynamic_lib_file) {
          $dynamic_lib_files->{$category}{$class_name} = $dynamic_lib_file;
        }
      }
    }
  }

  # Set function addresses of native and precompile methods
  for my $category ('precompile', 'native') {
    my $get_method_names_options = SPVM::ExchangeAPI::new_any_object_array(
      $runtime->api,
      [
        SPVM::ExchangeAPI::new_string($runtime->api, $category)
        =>
        SPVM::ExchangeAPI::call_method($runtime->api, 'Int', 'new', 1)
      ]
    );
    
    for my $class_name (keys %{$dynamic_lib_files->{$category}}) {
      next unless grep { "$_" eq $class_name } @$class_names;
      
      my $dynamic_lib_file = $dynamic_lib_files->{$category}{$class_name};
      my $method_names = $runtime->get_method_names($class_name, $get_method_names_options);
      my $anon_class_names = $runtime->get_anon_class_names($class_name);
      my $method_addresses = SPVM::Builder::Util::get_method_addresses($dynamic_lib_file, $class_name, $method_names, $anon_class_names, $category);
      
      for my $method_name (sort keys %$method_addresses) {
        my $cfunc_address = $method_addresses->{$method_name};
        if ($category eq 'native') {
          $runtime->set_native_method_address($class_name, $method_name, SPVM::ExchangeAPI::new_address_object($runtime->api, $cfunc_address));
        }
        elsif ($category eq 'precompile') {
          $runtime->set_precompile_method_address($class_name, $method_name, SPVM::ExchangeAPI::new_address_object($runtime->api, $cfunc_address));
        }
      }
    }
  }
}

sub init_runtime {
  unless ($SPVM::Global::RUNTIME) {
    unless ($SPVM::Global::BUILDER) {
      my $build_dir = $ENV{SPVM_BUILD_DIR};
      $SPVM::Global::BUILDER = SPVM::Builder->new(build_dir => $build_dir);
    }
    
    my $builder_compiler = SPVM::Builder::Compiler->new(
      module_dirs => $SPVM::Global::BUILDER->module_dirs
    );
    # Load SPVM Compilers
    $builder_compiler->use("Compiler", __FILE__, __LINE__);
    $builder_compiler->use("Runtime", __FILE__, __LINE__);
    $builder_compiler->use("Env", __FILE__, __LINE__);
    $builder_compiler->use("Stack", __FILE__, __LINE__);
    
    my $builder_runtime = $builder_compiler->build_runtime;

    $builder_runtime->load_dynamic_libs;

    # Build an environment
    $SPVM::Global::BUILDER_ENV = $builder_runtime->build_env;
    
    # Set command line info
    $SPVM::Global::BUILDER_ENV->set_command_info($0, \@ARGV);
    
    # Call INIT blocks
    $SPVM::Global::BUILDER_ENV->call_init_blocks;
    
    $SPVM::Global::BUILDER_STACK = $SPVM::Global::BUILDER_ENV->build_stack;
    
    $SPVM::Global::BUILDER_API = SPVM::ExchangeAPI->new(env => $SPVM::Global::BUILDER_ENV, stack => $SPVM::Global::BUILDER_STACK);
    
    $SPVM::Global::COMPILER = SPVM::ExchangeAPI::call_method($SPVM::Global::BUILDER_API, "Compiler", "new");
    for my $module_dir (@{$SPVM::Global::BUILDER->module_dirs}) {
      $SPVM::Global::COMPILER->add_module_dir($module_dir);
    }
    $SPVM::Global::COMPILER->set_start_file(__FILE__);
    $SPVM::Global::COMPILER->set_start_line(__LINE__ + 1);
    my $success = $SPVM::Global::COMPILER->compile('Int');
    unless ($success) {
      confess "Unexpcted Error:the compiliation must be always successful";
    }
    $SPVM::Global::RUNTIME = $SPVM::Global::COMPILER->build_runtime;

    &load_dynamic_libs($SPVM::Global::RUNTIME, $SPVM::Global::DYNAMIC_LIB_FILES);
  }
}

my $BIND_TO_PERL_CLASS_NAME_H = {};
sub bind_to_perl {
  my ($runtime, $class_names) = @_;

  for my $class_name (@$class_names) {
    next if $class_name =~ /::anon/;

    my $perl_class_name_base = "SPVM::";
    my $perl_class_name = "$perl_class_name_base$class_name";
    
    unless ($BIND_TO_PERL_CLASS_NAME_H->{$perl_class_name}) {
      
      my $parent_class_name = $runtime->get_parent_class_name($class_name);
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

    my $method_names = $runtime->get_method_names($class_name);

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
      my $is_class_method = $runtime->get_method_is_class_method($class_name, $method_name);
      
      if ($is_class_method) {
        # Define Perl method
        no strict 'refs';
        
        # Suppress refer to objects
        my $class_name_string = "$class_name";
        my $method_name_string = "$method_name";
        
        *{"$perl_method_abs_name"} = sub {
          my $perl_class_name = shift;
          
          my $return_value;
          
          eval { $return_value = SPVM::ExchangeAPI::call_method($SPVM::Global::API, $class_name_string, $method_name_string, @_) };
          my $error = $@;
          if ($error) {
            confess $error;
          }
          $return_value;
        };
      }
    }
  }
}


sub build_class {
  my ($class_name, $file, $line) = @_;
  
  unless ($SPVM::Global::BUILDER) {
    my $build_dir = $ENV{SPVM_BUILD_DIR};
    $SPVM::Global::BUILDER = SPVM::Builder->new(build_dir => $build_dir);
  }
  
  my $start_classes_length = 0;
  if ($SPVM::Global::RUNTIME) {
    $start_classes_length = $SPVM::Global::RUNTIME->get_classes_length;
  }
  
  &init_runtime();
  
  # Add class informations
  my $build_success;
  if (defined $class_name) {
    
    $SPVM::Global::COMPILER->set_start_file($file);
    $SPVM::Global::COMPILER->set_start_line($line);
    my $success = $SPVM::Global::COMPILER->compile($class_name);
    unless ($success) {
      my $error_messages = $SPVM::Global::COMPILER->get_error_messages;
      for my $error_message (@$error_messages) {
        printf STDERR "[CompileError]$error_message\n";
      }
      $SPVM::Global::COMPILER = undef;
      exit(255);
    }
    $SPVM::Global::RUNTIME = $SPVM::Global::COMPILER->build_runtime;

    &load_dynamic_libs($SPVM::Global::RUNTIME, $SPVM::Global::DYNAMIC_LIB_FILES);
  }
}

INIT {
  &init_runtime();
  
  my $class_names = $SPVM::Global::RUNTIME->get_class_names;
  &bind_to_perl($SPVM::Global::RUNTIME, $class_names);
  
  $SPVM::Global::ENV = $SPVM::Global::RUNTIME->build_env;
  
  $SPVM::Global::ENV->set_command_info($0, \@ARGV);
  
  $SPVM::Global::ENV->call_init_blocks;
  
  $SPVM::Global::STACK = $SPVM::Global::ENV->build_stack;
  
  $SPVM::Global::API = SPVM::ExchangeAPI->new(env => $SPVM::Global::ENV, stack => $SPVM::Global::STACK);
    
  $SPVM::Global::BUILDER = undef;
  $SPVM::Global::COMPILER = undef;
}

END {
  $SPVM::Global::API = undef;
  $SPVM::Global::STACK = undef;
  $SPVM::Global::ENV = undef;
  $SPVM::Global::RUNTIME = undef;
  $SPVM::Global::DYNAMIC_LIB_FILES = undef;
  $SPVM::Global::BUILDER_API = undef;
  $SPVM::Global::BUILDER_STACK = undef;
  $SPVM::Global::BUILDER_ENV = undef;
}

