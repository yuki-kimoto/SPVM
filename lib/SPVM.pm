package SPVM;

our $VERSION = '0.9682';

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
my $BOOT_COMPILER;
my $BOOT_RUNTIME;
my $BOOT_DYNAMIC_LIB_FILES = {};
my $BOOT_ENV;
my $BOOT_STACK;
my $COMPILER;
my $RUNTIME;
my $DYNAMIC_LIB_FILES = {};
my $ENV;
my $STACK;
my $SPVM_COMPILER;
my $SPVM_RUNTIME;
my $SPVM_DYNAMIC_LIB_FILES = {};
my $SPVM_ENV;
my $SPVM_STACK;

sub GET_ENV { $ENV }
sub GET_STACK { $STACK }

require XSLoader;
XSLoader::load('SPVM', $VERSION);

my $loaded_spvm_modules = {};

sub use_spvm_module {
  my ($compiler, $class_name, $file, $line) = @_;
  
  my $success = $compiler->compile($class_name, __FILE__, __LINE__);
  unless ($success) {
    $compiler->print_error_messages(*STDERR);
    exit(255);
  }
}

sub load_dynamic_libs {
  my ($runtime, $dynamic_lib_files) = @_;

  my $class_names = SPVM::Builder::Runtime->get_class_names($runtime);

  # Set addresses of native methods and precompile methods
  for my $class_name (@$class_names) {
    next if $class_name =~ /::anon/;
    
    for my $category ('precompile', 'native') {
      my $cc = SPVM::Builder::CC->new(
        build_dir => $BUILDER->build_dir,
        at_runtime => 1,
      );
      
      my $method_names = SPVM::Builder::Runtime->get_method_names($runtime, $class_name, $category);
      
      if (@$method_names) {
        # Build classs - Compile C source codes and link them to SPVM precompile method
        # Shared library which is already installed in distribution directory
        my $module_file = SPVM::Builder::Runtime->get_module_file($runtime, $class_name);
        my $dynamic_lib_file = SPVM::Builder::Util::get_dynamic_lib_file_dist($module_file, $category);
        
        # Try to build the shared library at runtime if shared library is not found
        unless (-f $dynamic_lib_file) {
          my $module_file = SPVM::Builder::Runtime->get_module_file($runtime, $class_name);
          my $method_names = SPVM::Builder::Runtime->get_method_names($runtime, $class_name, $category);
          my $anon_class_names = SPVM::Builder::Runtime->get_anon_class_names($runtime, $class_name);
          my $dl_func_list = SPVM::Builder::Util::create_dl_func_list($class_name, $method_names, $anon_class_names, {category => $category});
          my $precompile_source = SPVM::Builder::Runtime->build_precompile_class_source($runtime, $class_name);
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
    for my $class_name (keys %{$dynamic_lib_files->{$category}}) {
      my $dynamic_lib_file = $dynamic_lib_files->{$category}{$class_name};
      my $method_names = SPVM::Builder::Runtime->get_method_names($runtime, $class_name, $category);
      my $anon_class_names = SPVM::Builder::Runtime->get_anon_class_names($runtime, $class_name);
      my $method_addresses = SPVM::Builder::Util::get_method_addresses($dynamic_lib_file, $class_name, $method_names, $anon_class_names, $category);
      
      for my $method_name (sort keys %$method_addresses) {
        my $cfunc_address = $method_addresses->{$method_name};
        if ($category eq 'native') {
          SPVM::Builder::Runtime->set_native_method_address($runtime, $class_name, $method_name, $cfunc_address);
        }
        elsif ($category eq 'precompile') {
          SPVM::Builder::Runtime->set_precompile_method_address($runtime, $class_name, $method_name, $cfunc_address);
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
    $COMPILER = SPVM::Builder::Compiler->new(
      module_dirs => $BUILDER->module_dirs
    );
    my $success = $COMPILER->compile('Int', __FILE__, __LINE__);
    unless ($success) {
      confess "Unexpcted Error:the compiliation must be always successful";
    }
    $RUNTIME = $COMPILER->build_runtime;
    
    &load_dynamic_libs($RUNTIME, $DYNAMIC_LIB_FILES);
  }
}

sub spvm_init_runtime {
  unless ($SPVM_RUNTIME) {
    $SPVM_COMPILER = SPVM::ExchangeAPI::call_method($BOOT_ENV, $BOOT_STACK, "Compiler", "new");
    for my $module_dir (@{$BUILDER->module_dirs}) {
      $SPVM_COMPILER->add_module_dir($module_dir);
    }
    $SPVM_COMPILER->set_start_file(__FILE__);
    $SPVM_COMPILER->set_start_line(__LINE__ + 1);
    my $success = $SPVM_COMPILER->compile('Int');
    unless ($success) {
      confess "Unexpcted Error:the compiliation must be always successful";
    }
    $SPVM_RUNTIME = $SPVM_COMPILER->build_runtime;
  }
}

sub import {
  my ($class, $class_name) = @_;
  
  unless ($BUILDER) {
    my $build_dir = $ENV{SPVM_BUILD_DIR};
    $BUILDER = SPVM::Builder->new(build_dir => $build_dir);
  }

  unless ($BOOT_RUNTIME) {
    $BOOT_COMPILER = SPVM::Builder::Compiler->new(
      module_dirs => $BUILDER->module_dirs
    );
    # Load SPVM Compilers
    use_spvm_module($BOOT_COMPILER, "Compiler", __FILE__, __LINE__);
    use_spvm_module($BOOT_COMPILER, "Runtime", __FILE__, __LINE__);
    use_spvm_module($BOOT_COMPILER, "Native::Compiler", __FILE__, __LINE__);
    use_spvm_module($BOOT_COMPILER, "Native::Runtime", __FILE__, __LINE__);
    use_spvm_module($BOOT_COMPILER, "Native::Precompile", __FILE__, __LINE__);
    use_spvm_module($BOOT_COMPILER, "Native::Env", __FILE__, __LINE__);
    use_spvm_module($BOOT_COMPILER, "Native::Stack", __FILE__, __LINE__);
    use_spvm_module($BOOT_COMPILER, "Native::Address", __FILE__, __LINE__);
    use_spvm_module($BOOT_COMPILER, "Fn", __FILE__, __LINE__);
    
    $BOOT_RUNTIME = $BOOT_COMPILER->build_runtime;

    &load_dynamic_libs($BOOT_RUNTIME, $BOOT_DYNAMIC_LIB_FILES);

    # Build an environment
    $BOOT_ENV = SPVM::Builder::Runtime->build_env($BOOT_RUNTIME);
    
    # Set command line info
    SPVM::Builder::Runtime->set_command_info($BOOT_ENV, $0, \@ARGV);
    
    # Call INIT blocks
    SPVM::Builder::Runtime->call_init_blocks($BOOT_ENV);
    
    $BOOT_STACK = SPVM::Builder::Runtime->build_stack($BOOT_ENV);

    my $class_names = SPVM::Builder::Runtime->get_class_names($BOOT_RUNTIME);
    
    # Test codes
    my $int_max = SPVM::ExchangeAPI::call_method($BOOT_ENV, $BOOT_STACK, "Fn", "abs", -3);
    unless ($int_max == 3) {
      confess("Unexpected");
    }
    my $int_obj = SPVM::ExchangeAPI::call_method($BOOT_ENV, $BOOT_STACK, "Int", "new", 1);
    unless (ref $int_obj eq 'SPVM::BlessedObject::Class') {
      confess("Unexpected");
    }
    my $value = SPVM::ExchangeAPI::call_method($BOOT_ENV, $BOOT_STACK, $int_obj, "value");
    unless ($value == 1) {
      confess("Unexpected");
    }
    my $value2 = $int_obj->value;
    unless ($value2 == 1) {
      confess("Unexpected");
    }
  }
  
  {
    my $start_classes_length = 0;
    if ($SPVM_RUNTIME) {
      $start_classes_length = $SPVM_RUNTIME->get_classes_length;
    }
    
    &spvm_init_runtime();
  }
  
  my $start_classes_length = SPVM::Builder::Runtime->get_classes_length($RUNTIME);
  
  # This is needed in the case that INIT block is not called in "perl -c script.pl"
  &init_runtime();
  
  my ($file, $line) = (caller)[1, 2];

  # Add class informations
  my $build_success;
  if (defined $class_name) {

    # Compile SPVM source code and create runtime env
    my $success = $COMPILER->compile($class_name, $file, $line);
    unless ($success) {
      $COMPILER->print_error_messages(*STDERR);
      exit(255);
    }
    $RUNTIME = $COMPILER->build_runtime;

    &load_dynamic_libs($RUNTIME, $DYNAMIC_LIB_FILES);
  }
}

INIT {
  # This is needed in the case that SPVM->import is not called.
  &init_runtime();
  
  # Class names added at this compilation
  my $class_names = SPVM::Builder::Runtime->get_class_names($RUNTIME);
  bind_to_perl($RUNTIME, $class_names);
  
  # Build an environment
  $ENV = SPVM::Builder::Runtime->build_env($RUNTIME);
  
  # Set command line info
  SPVM::Builder::Runtime->set_command_info($ENV, $0, \@ARGV);
  
  # Call INIT blocks
  SPVM::Builder::Runtime->call_init_blocks($ENV);
  
  $STACK = SPVM::Builder::Runtime->build_stack($ENV);

  $BUILDER = undef;
  $BOOT_COMPILER = undef;
  $COMPILER = undef;
  $SPVM_COMPILER = undef;
}

END {
  $SPVM_STACK = undef;
  $SPVM_ENV = undef;
  $SPVM_RUNTIME = undef;
  $BOOT_STACK = undef;
  $BOOT_ENV = undef;
  $BOOT_RUNTIME = undef;
  $STACK = undef;
  $ENV = undef;
  $RUNTIME = undef;
}

my $BIND_TO_PERL_CLASS_NAME_H = {};
sub bind_to_perl {
  my ($runtime, $class_names) = @_;

  for my $class_name (@$class_names) {
    next if $class_name =~ /::anon/;

    my $perl_class_name_base = "SPVM::";
    my $perl_class_name = "$perl_class_name_base$class_name";
    
    unless ($BIND_TO_PERL_CLASS_NAME_H->{$perl_class_name_base}{$perl_class_name}) {
      
      my $parent_class_name = SPVM::Builder::Runtime->get_parent_class_name($runtime, $class_name);
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

    my $method_names = SPVM::Builder::Runtime->get_method_names($runtime, $class_name);

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
      my $is_class_method = SPVM::Builder::Runtime->get_method_is_class_method($runtime, $class_name, $method_name);
      
      if ($is_class_method) {
        # Define Perl method
        no strict 'refs';
        *{"$perl_method_abs_name"} = sub {
          my $perl_class_name = shift;
          
          my $return_value;
          
          eval { $return_value = SPVM::ExchangeAPI::call_method($ENV, $STACK, $class_name, $method_name, @_) };
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
