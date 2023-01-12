package SPVM;

our $VERSION = '0.9680';

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
use SPVM::Builder::Env;
use SPVM::Builder::Stack;
use SPVM::ExchangeAPI;
use SPVM::Builder::Runtime;

use Carp 'confess';

# INIT and CHECK block can't be used because SPVM supports dynamic module loading.
# For the reason, this variable is needed.
my $SPVM_INITED;

our $BUILDER;
our $INTERPRETER;

require XSLoader;
XSLoader::load('SPVM', $VERSION);

my $loaded_spvm_modules = {};

sub import {
  my ($class, $class_name) = @_;
  
  unless (defined $class_name) {
    return;
  }
  
  my ($file, $line) = (caller)[1, 2];

  unless ($BUILDER) {
    my $build_dir = $ENV{SPVM_BUILD_DIR};
    $BUILDER = SPVM::Builder->new(build_dir => $build_dir, include_dirs => [@INC]);
  }

  # Add class informations
  my $build_success;
  if (defined $class_name) {

    my $start_classes_length = $BUILDER->get_classes_length;

    # Compile SPVM source code and create runtime env
    my $compile_success = $BUILDER->compile($class_name, $file, $line);

    unless ($compile_success) {
      $BUILDER->print_error_messages(*STDERR);
      exit(255);
    }

    # Class names added at this compilation
    my $added_class_names = [];
    my $class_names = $BUILDER->get_class_names;
    for (my $i = $start_classes_length; $i < @$class_names; $i++) {
      my $added_class_name =  $class_names->[$i];
      push @$added_class_names, $added_class_name;
    }
    
    # Bind SPVM method to Perl
    bind_to_perl($BUILDER, $added_class_names);

    # Set addresses of native methods and precompile methods
    for my $added_class_name (@$added_class_names) {
      next if $added_class_name =~ /::anon/;
      
      for my $category ('precompile', 'native') {
        my $cc = SPVM::Builder::CC->new(
          build_dir => $BUILDER->{build_dir},
          builder => $BUILDER,
          runtime => 1,
        );
        
        my $method_names = $BUILDER->get_method_names($added_class_name, $category);
        
        if (@$method_names) {
          # Build classs - Compile C source codes and link them to SPVM precompile method
          # Shared library which is already installed in distribution directory
          my $dynamic_lib_file = $BUILDER->get_dynamic_lib_file_dist($added_class_name, $category);
          
          # Try runtime compile if shared library is not found
          unless (-f $dynamic_lib_file) {
            $dynamic_lib_file = $cc->build_runtime($added_class_name, {category => $category});
          }
          
          if (-f $dynamic_lib_file) {
            $BUILDER->dynamic_lib_files->{$category}{$added_class_name} = $dynamic_lib_file;
          }
        }
      }
    }
  }
}

sub init {
  unless ($SPVM_INITED) {
    unless ($BUILDER) {
      # If any SPVM module are not yet loaded, $BUILDER is not set.
      my $build_dir = $ENV{SPVM_BUILD_DIR};
      $BUILDER = SPVM::Builder->new(build_dir => $build_dir, include_dirs => [@INC]);
      my $compile_success = $BUILDER->compile('Int', __FILE__, __LINE__);
      unless ($compile_success) {
        confess "Unexpcted Error:the compiliation must be always successful";
      }
    }
    
    my $runtime = $BUILDER->runtime;

    # Set function addresses of native and precompile methods
    for my $category ('precompile', 'native') {
      for my $class_name (keys %{$BUILDER->dynamic_lib_files->{$category}}) {
        my $dynamic_lib_file = $BUILDER->dynamic_lib_files->{$category}{$class_name};
        $BUILDER->bind_methods($dynamic_lib_file, $class_name, $category);
      }
    }
    
    # Build an environment
    my $native_env = SPVM::Builder::Runtime->build_native_env($BUILDER->runtime);
    $BUILDER->native_env($native_env);

    # Set command line info
    SPVM::Builder::Runtime->set_command_info($native_env, $0, \@ARGV);
    
    # Call INIT blocks
    SPVM::Builder::Runtime->call_init_blocks($native_env);
    
    # Build an stack
    my $native_stack = $BUILDER->build_native_stack;
    $BUILDER->native_stack($native_stack);
    
    my $obj_runtime = bless ({runtime => $runtime}, "SPVM::Builder::Runtime");
    my $env = bless ({runtime => $runtime, native_env => $native_env}, "SPVM::Builder::Env");
    my $stack = bless ({native_stack => $native_stack, env => $env}, "SPVM::Builder::Stack");
    
    $SPVM::RUNTIME_ENV_STACK = {
      runtime => $runtime,
      stack => $stack,
    };
    
    $SPVM_INITED = 1;
  }
}

my $class_name_h = {};
my $binded_class_name_h = {};
sub bind_to_perl {
  my ($builder, $added_class_names) = @_;

  for my $class_name (@$added_class_names) {
    next if $class_name =~ /::anon/;

    my $perl_class_name = "SPVM::$class_name";
    
    unless ($class_name_h->{$class_name}) {
      
      my $parent_class_name = $builder->get_parent_class_name($class_name);
      my $parent_class_name_str = defined $parent_class_name ? "($parent_class_name)" : "()";
      
      # The inheritance
      my @isa;
      if (defined $parent_class_name) {
        push @isa, "SPVM::$parent_class_name";
      }
      push @isa, 'SPVM::BlessedObject::Class';
      my $isa = "our \@ISA = (" . join(',', map { "'$_'" } @isa) . ");";
      
      my $code = "package $perl_class_name; $isa";
      eval $code;
      
      if (my $error = $@) {
        confess $error;
      }
      $class_name_h->{$class_name} = 1;
    }

    my $method_names = $builder->get_method_names($class_name);

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

      # Define Perl method
      no strict 'refs';
      *{"$perl_method_abs_name"} = sub {
        SPVM::init() unless $SPVM_INITED;

        my $return_value;
        eval { $return_value = SPVM::call_method($class_name, $method_name, @_) };
        my $error = $@;
        if ($error) {
          confess $error;
        }
        $return_value;
      };
    }
  }
}

sub new_byte_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_byte_array($BUILDER, @_);
}

sub new_byte_array_unsigned {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_byte_array_unsigned($BUILDER, @_);
}

sub new_byte_array_len {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_byte_array_len($BUILDER, @_);
}

sub new_byte_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_byte_array_from_bin($BUILDER, @_);
}
sub new_byte_array_from_string {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_byte_array_from_string($BUILDER, @_);
}

sub new_short_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_short_array($BUILDER, @_);
}

sub new_short_array_unsigned {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_short_array_unsigned($BUILDER, @_);
}

sub new_short_array_len {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_short_array_len($BUILDER, @_);
}

sub new_short_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_short_array_from_bin($BUILDER, @_);
}
sub new_int_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_int_array($BUILDER, @_);
}

sub new_int_array_unsigned {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_int_array_unsigned($BUILDER, @_);
}

sub new_int_array_len {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_int_array_len($BUILDER, @_);
}

sub new_int_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_int_array_from_bin($BUILDER, @_);
}
sub new_long_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_long_array($BUILDER, @_);
}

sub new_long_array_unsigned {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_long_array_unsigned($BUILDER, @_);
}

sub new_long_array_len {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_long_array_len($BUILDER, @_);
}

sub new_long_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_long_array_from_bin($BUILDER, @_);
}
sub new_float_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_float_array($BUILDER, @_);
}
sub new_float_array_len {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_float_array_len($BUILDER, @_);
}

sub new_float_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_float_array_from_bin($BUILDER, @_);
}
sub new_double_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_double_array($BUILDER, @_);
}

sub new_double_array_len {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_double_array_len($BUILDER, @_);
}

sub new_double_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_double_array_from_bin($BUILDER, @_);
}
sub new_string {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_string($BUILDER, @_);
}

sub new_string_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_string_from_bin($BUILDER, @_);
}

sub new_object_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_object_array($BUILDER, @_);
}

sub new_any_object_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_any_object_array($BUILDER, @_);
}

sub new_mulnum_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_mulnum_array($BUILDER, @_);
}

sub new_mulnum_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_mulnum_array_from_bin($BUILDER, @_);
}

sub new_string_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_string_array($BUILDER, @_);
}

sub get_exception {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::get_exception($BUILDER, @_);
}

sub set_exception {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::set_exception($BUILDER, @_);
}

sub get_memory_blocks_count {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::get_memory_blocks_count($BUILDER, @_);
}

sub call_method {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::call_method($BUILDER, @_);
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
