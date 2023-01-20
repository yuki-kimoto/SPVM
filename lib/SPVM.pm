package SPVM;

our $VERSION = $SPVM::Builder::VERSION;

use 5.008007;
use strict;
use warnings;

use DynaLoader;
use File::Basename 'basename', 'dirname';

use SPVM::BlessedObject;
use SPVM::BlessedObject::Array;
use SPVM::BlessedObject::Class;
use SPVM::BlessedObject::String;
use FindBin;

use SPVM::Builder;
use SPVM::Builder::Runtime;
use SPVM::ExchangeAPI;

use Carp 'confess';

my $BUILDER;
my $BUILDER_ENV;
my $BUILDER_STACK;
my $COMPILER;
my $RUNTIME;
my $DYNAMIC_LIB_FILES = {};
my $ENV;
my $STACK;

sub GET_ENV { $ENV }
sub GET_STACK { $STACK }

sub load_dynamic_libs {
  my ($runtime, $dynamic_lib_files) = @_;

  my $class_names = [map { "$_" } @{$runtime->get_class_names}];

  # Set addresses of native methods and precompile methods
  for my $class_name (@$class_names) {
    next if $class_name =~ /::anon/;
    
    for my $category ('precompile', 'native') {

      my $cc = SPVM::Builder::CC->new(
        build_dir => $BUILDER->build_dir,
        at_runtime => 1,
      );

      my $get_method_names_options = SPVM::ExchangeAPI::new_any_object_array(
        $runtime->env,
        $runtime->stack,
        [
          SPVM::ExchangeAPI::new_string($runtime->env, $runtime->stack, $category)
          =>
          SPVM::ExchangeAPI::call_method($runtime->env, $runtime->stack, 'Int', 'new', 1)
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
      $runtime->env,
      $runtime->stack,
      [
        SPVM::ExchangeAPI::new_string($runtime->env, $runtime->stack, $category)
        =>
        SPVM::ExchangeAPI::call_method($runtime->env, $runtime->stack, 'Int', 'new', 1)
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
          $runtime->set_native_method_address($class_name, $method_name, SPVM::ExchangeAPI::new_address_object($runtime->env, $runtime->stack, $cfunc_address));
        }
        elsif ($category eq 'precompile') {
          $runtime->set_precompile_method_address($class_name, $method_name, SPVM::ExchangeAPI::new_address_object($runtime->env, $runtime->stack, $cfunc_address));
        }
      }
    }
  }
}

sub init_runtime {
  unless ($RUNTIME) {
    unless ($BUILDER) {
      my $build_dir = $ENV{SPVM_BUILD_DIR};
      $BUILDER = SPVM::Builder->new(build_dir => $build_dir);
    }
    
    my $builder_compiler = SPVM::Builder::Compiler->new(
      module_dirs => $BUILDER->module_dirs
    );
    # Load SPVM Compilers
    $builder_compiler->use("Compiler", __FILE__, __LINE__);
    $builder_compiler->use("Runtime", __FILE__, __LINE__);
    $builder_compiler->use("Env", __FILE__, __LINE__);
    $builder_compiler->use("Stack", __FILE__, __LINE__);
    
    my $builder_runtime = $builder_compiler->build_runtime;

    $builder_runtime->load_dynamic_libs;

    # Build an environment
    $BUILDER_ENV = SPVM::Builder::Runtime->build_env($builder_runtime);
    
    # Set command line info
    SPVM::Builder::Runtime->set_command_info($BUILDER_ENV, $0, \@ARGV);
    
    # Call INIT blocks
    SPVM::Builder::Runtime->call_init_blocks($BUILDER_ENV);
    
    $BUILDER_STACK = SPVM::Builder::Runtime->build_stack($BUILDER_ENV);
    
    $COMPILER = SPVM::ExchangeAPI::call_method($BUILDER_ENV, $BUILDER_STACK, "Compiler", "new");
    for my $module_dir (@{$BUILDER->module_dirs}) {
      $COMPILER->add_module_dir($module_dir);
    }
    $COMPILER->set_start_file(__FILE__);
    $COMPILER->set_start_line(__LINE__ + 1);
    my $success = $COMPILER->compile('Int');
    unless ($success) {
      confess "Unexpcted Error:the compiliation must be always successful";
    }
    $RUNTIME = $COMPILER->build_runtime;

    &load_dynamic_libs($RUNTIME, $DYNAMIC_LIB_FILES);
  }
}

sub import {
  my ($class, $class_name) = @_;
  
  unless ($BUILDER) {
    my $build_dir = $ENV{SPVM_BUILD_DIR};
    $BUILDER = SPVM::Builder->new(build_dir => $build_dir);
  }

  {
    my $start_classes_length = 0;
    if ($RUNTIME) {
      $start_classes_length = $RUNTIME->get_classes_length;
    }
    
    &init_runtime();
    
    my ($file, $line) = (caller)[1, 2];
    
    # Add class informations
    my $build_success;
    if (defined $class_name) {
      
      $COMPILER->set_start_file(__FILE__);
      $COMPILER->set_start_line(__LINE__ + 1);
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
}

INIT {
  &init_runtime();
  
  my $class_names = $RUNTIME->get_class_names;
  &bind_to_perl($RUNTIME, $class_names);
  
  $ENV = SPVM::ExchangeAPI::call_method($BUILDER_ENV, $BUILDER_STACK, "Env", "new", $RUNTIME);
  
  SPVM::ExchangeAPI::call_method($BUILDER_ENV, $BUILDER_STACK, 'Runtime', 'set_command_info', $ENV, $0, \@ARGV);
  
  SPVM::ExchangeAPI::call_method($BUILDER_ENV, $BUILDER_STACK, 'Runtime', 'call_init_blocks', $ENV);
  
  $STACK = SPVM::ExchangeAPI::call_method($BUILDER_ENV, $BUILDER_STACK, 'Stack', 'new', $ENV);
  
  $BUILDER = undef;
  $COMPILER = undef;
}

END {
  $STACK = undef;
  $ENV = undef;
  $RUNTIME = undef;
  $DYNAMIC_LIB_FILES = undef;
  $BUILDER_STACK = undef;
  $BUILDER_ENV = undef;
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
          
          eval { $return_value = SPVM::ExchangeAPI::call_method($ENV, $STACK, $class_name_string, $method_name_string, @_) };
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

sub new_byte_array {
  SPVM::ExchangeAPI::new_byte_array($ENV, $STACK, @_);
}

sub new_byte_array_unsigned {
  SPVM::ExchangeAPI::new_byte_array_unsigned($ENV, $STACK, @_);
}

sub new_byte_array_len {
  SPVM::ExchangeAPI::new_byte_array_len($ENV, $STACK, @_);
}

sub new_byte_array_from_bin {
  SPVM::ExchangeAPI::new_byte_array_from_bin($ENV, $STACK, @_);
}
sub new_byte_array_from_string {
  SPVM::ExchangeAPI::new_byte_array_from_string($ENV, $STACK, @_);
}

sub new_short_array {
  SPVM::ExchangeAPI::new_short_array($ENV, $STACK, @_);
}

sub new_short_array_unsigned {
  SPVM::ExchangeAPI::new_short_array_unsigned($ENV, $STACK, @_);
}

sub new_short_array_len {
  SPVM::ExchangeAPI::new_short_array_len($ENV, $STACK, @_);
}

sub new_short_array_from_bin {
  SPVM::ExchangeAPI::new_short_array_from_bin($ENV, $STACK, @_);
}
sub new_int_array {
  SPVM::ExchangeAPI::new_int_array($ENV, $STACK, @_);
}

sub new_int_array_unsigned {
  SPVM::ExchangeAPI::new_int_array_unsigned($ENV, $STACK, @_);
}

sub new_int_array_len {
  SPVM::ExchangeAPI::new_int_array_len($ENV, $STACK, @_);
}

sub new_int_array_from_bin {
  SPVM::ExchangeAPI::new_int_array_from_bin($ENV, $STACK, @_);
}
sub new_long_array {
  SPVM::ExchangeAPI::new_long_array($ENV, $STACK, @_);
}

sub new_long_array_unsigned {
  SPVM::ExchangeAPI::new_long_array_unsigned($ENV, $STACK, @_);
}

sub new_long_array_len {
  SPVM::ExchangeAPI::new_long_array_len($ENV, $STACK, @_);
}

sub new_long_array_from_bin {
  SPVM::ExchangeAPI::new_long_array_from_bin($ENV, $STACK, @_);
}
sub new_float_array {
  SPVM::ExchangeAPI::new_float_array($ENV, $STACK, @_);
}
sub new_float_array_len {
  SPVM::ExchangeAPI::new_float_array_len($ENV, $STACK, @_);
}

sub new_float_array_from_bin {
  SPVM::ExchangeAPI::new_float_array_from_bin($ENV, $STACK, @_);
}
sub new_double_array {
  SPVM::ExchangeAPI::new_double_array($ENV, $STACK, @_);
}

sub new_double_array_len {
  SPVM::ExchangeAPI::new_double_array_len($ENV, $STACK, @_);
}

sub new_double_array_from_bin {
  SPVM::ExchangeAPI::new_double_array_from_bin($ENV, $STACK, @_);
}
sub new_string {
  SPVM::ExchangeAPI::new_string($ENV, $STACK, @_);
}

sub new_string_from_bin {
  SPVM::ExchangeAPI::new_string_from_bin($ENV, $STACK, @_);
}

sub new_object_array {
  SPVM::ExchangeAPI::new_object_array($ENV, $STACK, @_);
}

sub new_any_object_array {
  SPVM::ExchangeAPI::new_any_object_array($ENV, $STACK, @_);
}

sub new_mulnum_array {
  SPVM::ExchangeAPI::new_mulnum_array($ENV, $STACK, @_);
}

sub new_mulnum_array_from_bin {
  SPVM::ExchangeAPI::new_mulnum_array_from_bin($ENV, $STACK, @_);
}

sub new_string_array {
  SPVM::ExchangeAPI::new_string_array($ENV, $STACK, @_);
}

sub get_exception {
  SPVM::ExchangeAPI::get_exception($ENV, $STACK, @_);
}

sub set_exception {
  SPVM::ExchangeAPI::set_exception($ENV, $STACK, @_);
}

sub get_memory_blocks_count {
  SPVM::ExchangeAPI::get_memory_blocks_count($ENV, $STACK, @_);
}

sub call_method {
  SPVM::ExchangeAPI::call_method($ENV, $STACK, @_);
}

sub new_address_object {
  SPVM::ExchangeAPI::new_address_object($ENV, $STACK, @_);
}

1;

=encoding utf8

=head1 Name

SPVM - SPVM Language

=head1 Caution

C<SPVM> is not yet 1.0 release. It is quite often changed without warnings until I feel that the implementation is good enough.

=head1 Usage

Write a SPVM Module:

  # lib/SPVM/MyMath.spvm
  class MyMath {
    static method sum : int ($nums : int[]) {

      my $total = 0;
      for (my $i = 0; $i < @$nums; $i++) {
        $total += $nums->[$i];
      }

      return $total;
    }
  }

Call the SPVM method from Perl:

  # sum.pl
  use strict;
  use warnings;
  use FindBin;
  use lib "$FindBin::Bin/lib";

  use SPVM 'MyMath';

  # Call method
  my $total = SPVM::MyMath->sum([3, 6, 8, 9]);

  print "$total\n";

=head1 Description

B<SPVM> (Static Perl Virtual Machine) is a perl-ish static typed programing language. SPVM provides fast calculation, fast array operations, easy C/C++ binding, and creating executable files.

=head1 Document

SPVM documents.

=head2 Tutorial

SPVM Tutorial.

=over 2

=item * L<Tutorial|SPVM::Document::Tutorial>

=back

=head2 Language Specification

SPVM Language Specification.

=over 2

=item * L<Language Specification|SPVM::Document::Language>

=back

=head2 Standard Modules

SPVM Standard Modules.

=over 2

=item * L<Standard Modules|SPVM::Document::Modules>

=back

=head2 Exchange APIs

SPVM Exchange APIs is functions to convert between Perl data structures and SPVM data structures.

=over 2

=item * L<ExchangeAPI|SPVM::Document::ExchangeAPI>

=back

=head2 Native Module

The native module is the module that is implemented by native language such as C<C language> or C<C++>.

=over 2

=item * L<Native Method|SPVM::Document::NativeModule>

=back

=head2 Native APIs

SPVM native APIs are public APIs that are used in native language sources such as C<C language> or C<C++>.

=over 2

=item * L<Native APIs|SPVM::Document::NativeAPI>

=back

=head2 Resource

A resource is a L<native module|SPVM::Document::NativeModule> that contains a set of sources and headers of native language such as C<C language> or C<C++>.

=over 2

=item * L<Resource|SPVM::Document::Resource>

=back

=head2 Creating Executable File

C<spvmcc> is the compiler and linker to create the executable file from SPVM source codes.

=over 2

=item * L<spvmcc>

=back

=head2 Creating SPVM Distribution

C<spvmdist> is the command to create SPVM distribution.

=over 2

=item * L<spvmdist>

=back

=head2 Benchmark

SPVM performance benchmarks.

=over 2

=item * L<Benchmark|SPVM::Document::Benchmark>

=back

=head1 Environment Variables

=head2 SPVM_BUILD_DIR

SPVM building directory to build C<precompile> and C<native> methods. If the C<SPVM_BUILD_DIR> environment variable is not set, the building of C<precompile> and C<native> methods fails.

B<bash:>

  export SPVM_BUILD_DIR=~/.spvm_build

B<csh:>

  setenv SPVM_BUILD_DIR ~/.spvm_build

=head2 SPVM_CC_DEBUG

Print debug messages of L<SPVM::Builder::CC> to stderr.

=head2 SPVM_CC_FORCE

Force the compilation and the link of L<SPVM::Builder::CC>.

=head1 Repository

L<Github|https://github.com/yuki-kimoto/SPVM>

=head1 Bug Report

L<GitHub Issue|https://github.com/yuki-kimoto/SPVM/issues>

=head1 Support

L<Github Discussions|https://github.com/yuki-kimoto/SPVM/discussions>

=head1 Author

Yuki Kimoto E<lt>kimoto.yuki@gmail.comE<gt>

=head1 Core Developers

motiE<lt>motohiko.ave@gmail.comE<gt>

=head1 Contributors

=over 2

=item * Mohammad S Anwar

=item * akinomyoga

=item * NAGAYASU Shinya

=item * Reini Urban

=item * chromatic

=item * Kazutake Hiramatsu

=item * Yasuaki Omokawa

=item * Suman Khanal

=item * L<Ryunosuke Murakami|https://github.com/ryun0suke22>

=item * L<Yoshiyuki Itoh|https://github.com/YoshiyukiItoh>

=item * L<Tore Aursand|https://github.com/toreau>

=back

=head1 Copyright & LICENSE

Copyright 2018-2022 Yuki Kimoto, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.

=cut
