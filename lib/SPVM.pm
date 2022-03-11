package SPVM;

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
use SPVM::ExchangeAPI;

use Carp 'confess';

our $VERSION = '0.9508_01';

my $SPVM_INITED;
my $BUILDER;

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
    my $compile_success = $BUILDER->compile_spvm($class_name, $file, $line);

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
    
    my $address_info = {};
    for my $added_class_name (@$added_class_names) {
      next if $added_class_name =~ /::anon/;
      
      # Build Precompile classs - Compile C source codes and link them to SPVM precompile method
      $BUILDER->build_and_bind_shared_lib($added_class_name, 'precompile');
      
      # Build native classs - Compile C source codes and link them to SPVM native method
      $BUILDER->build_and_bind_shared_lib($added_class_name, 'native');
    }

    # Bind SPVM method to Perl
    bind_to_perl($BUILDER, $added_class_names);
  }
}

sub init {
  unless ($SPVM_INITED) {
    if (my $builder = $BUILDER) {
      
      # Build runtime information
      $builder->build_runtime;
      
      # Prepare runtime environment
      $builder->prepare_env;

      # Call INIT blocks
      $builder->call_init_blocks;
    }
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
    
      my $code = "package $perl_class_name; our \@ISA = ('SPVM::BlessedObject::Class');";
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
        eval { $return_value = SPVM::call_spvm_method($class_name, $method_name, @_) };
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
  SPVM::ExchangeAPI::new_byte_array($BUILDER->{env}, @_);
}

sub new_byte_array_unsigned {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_byte_array_unsigned($BUILDER->{env}, @_);
}

sub new_byte_array_len {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_byte_array_len($BUILDER->{env}, @_);
}

sub new_byte_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_byte_array_from_bin($BUILDER->{env}, @_);
}
sub new_byte_array_from_string {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_byte_array_from_string($BUILDER->{env}, @_);
}

sub new_short_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_short_array($BUILDER->{env}, @_);
}

sub new_short_array_unsigned {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_short_array_unsigned($BUILDER->{env}, @_);
}

sub new_short_array_len {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_short_array_len($BUILDER->{env}, @_);
}

sub new_short_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_short_array_from_bin($BUILDER->{env}, @_);
}
sub new_int_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_int_array($BUILDER->{env}, @_);
}

sub new_int_array_unsigned {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_int_array_unsigned($BUILDER->{env}, @_);
}

sub new_int_array_len {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_int_array_len($BUILDER->{env}, @_);
}

sub new_int_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_int_array_from_bin($BUILDER->{env}, @_);
}
sub new_long_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_long_array($BUILDER->{env}, @_);
}

sub new_long_array_unsigned {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_long_array_unsigned($BUILDER->{env}, @_);
}

sub new_long_array_len {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_long_array_len($BUILDER->{env}, @_);
}

sub new_long_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_long_array_from_bin($BUILDER->{env}, @_);
}
sub new_float_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_float_array($BUILDER->{env}, @_);
}
sub new_float_array_len {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_float_array_len($BUILDER->{env}, @_);
}

sub new_float_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_float_array_from_bin($BUILDER->{env}, @_);
}
sub new_double_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_double_array($BUILDER->{env}, @_);
}

sub new_double_array_len {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_double_array_len($BUILDER->{env}, @_);
}

sub new_double_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_double_array_from_bin($BUILDER->{env}, @_);
}
sub new_string {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_string($BUILDER->{env}, @_);
}

sub new_string_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_string_from_bin($BUILDER->{env}, @_);
}

sub new_object_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_object_array($BUILDER->{env}, @_);
}

sub new_mulnum_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_mulnum_array($BUILDER->{env}, @_);
}

sub new_mulnum_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_mulnum_array_from_bin($BUILDER->{env}, @_);
}

sub new_string_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_string_array($BUILDER->{env}, @_);
}

sub get_exception {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::get_exception($BUILDER->{env}, @_);
}

sub set_exception {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::set_exception($BUILDER->{env}, @_);
}

sub get_memory_blocks_count {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::get_memory_blocks_count($BUILDER->{env}, @_);
}

sub call_spvm_method {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::call_spvm_method($BUILDER->{env}, @_);
}

1;

=encoding utf8

=head1 NAME

SPVM - Static Perl Virtual Machine. Fast Calculation, Fast Array Operation, and Easy C/C++ Binding.

=head1 CAUTHION

B<L<SPVM> is not yet 1.0. Please note L<SPVM> can change without warnings. There can be a lot of changes until I feel good enough.>

=head1 SYNOPSIS

SPVM Module:

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

Call SPVM method from Perl:

  # spvm.pl
  use strict;
  use warnings;
  use FindBin;
  use lib "$FindBin::Bin/lib";

  use SPVM 'MyMath';

  # Call method
  my $total = SPVM::MyMath->sum([3, 6, 8, 9]);

  print "Total: $total\n";

  # Call method with packed data
  my $nums_packed = pack('l*', 3, 6, 8, 9);
  my $sv_nums = SPVM::new_int_array_from_bin($nums_packed);
  my $total_packed = SPVM::MyMath->sum($sv_nums);

  print "Total Packed: $total_packed\n";

Precompiled SPVM Method. This code is converted to C language and then converted to a shared library.

  # lib/SPVM/MyMath.spvm
  class MyMath : precompile {
    static method sum : int ($nums : int[]) {

      my $total = 0;
      for (my $i = 0; $i < @$nums; $i++) {
        $total += $nums->[$i];
      }

      return $total;
    }
  }

=head1 DESCRIPTION

SPVM is a Static Perl Virtual Machine. SPVM is a programming language which has Perlish syntax. SPVM provides fast Calculation & easy C/C++ Binding.

=head1 FEATURES

=over 4

=item * Fast calculation, Fast array operation

=item * Precompile Method, Easy way to C/C++ binding, C99 math functions

=item * Perlish syntax, Static typing, Type inference

=item * Reference count GC, Weaken reference, Exception, Module

=item * Object oriented programming

=back

=head1 DOCUMENT

SPVM documents.

=head2 Tutorial

SPVM Tutorial.

=over 2

=item * L<Tutorial|SPVM::Document::Tutorial>

=back

=head2 Language Specification

SPVM Language Specification.

=over 2

=item * L<Language Specification|SPVM::Document::LanguageSpecification>

=back

=head2 Standard Functions

SPVM Standard Functions

=over 2

=item * L<Standard Functions|SPVM::Fn>

=back

=head2 Standard Modules

SPVM Standard Modules.

=over 2

=item * L<Standard Modules|SPVM::Document::Modules>

=back

=head2 Performance Benchmark

SPVM Performance Benchmark.

=over 2

=item * L<Benchmark|SPVM::Document::Benchmark>

=back

=head2 Exchange API

SPVM Exchange API converts Perl data structures to SPVM data structures, and vice versa.

=over 2

=item * L<ExchangeAPI|SPVM::Document::ExchangeAPI>

=back

=head2 Native API

SPVM Native API is C API used in SPVM native method.

=over 2

=item * L<NativeAPI|SPVM::Document::NativeAPI>

=back

=head2 Generate Execution File

B<spvmcc> is a compiler to compile SPVM source codes to a execution file. The execution file can be run by itself.

=over 2

=item * L<spvmcc>

=back

=head2 Generate SPVM Native Modules

B<spvmgenlib> is the command to generate SPVM native modules.

=over 2

=item * L<spvmgenlib>

=back

=head1 ENVIRONMENT VARIABLE

=head2 SPVM_BUILD_DIR

SPVM build directory for precompile and native method.

If SPVM_BUILD_DIR environment variable is not set, SPVM can't compile precompile method and native method, and a exception occur. You see error message "SPVM_BUILD_DIR environment variable must be set ...".

In bash, you can set SPVM_BUILD_DIR to the following.

  export SPVM_BUILD_DIR=~/.spvm_build

=head2 SPVM_CC_DEBUG

Print L<SVPM::Builder::CC> compile and link outputs to stderr.

=head2 SPVM_CC_FORCE

Force L<SVPM::Builder::CC> compile and link.

=head1 CAUTION

This release is a beta release before SPVM 1.0. The features can change without notice. Use at your own risk.

=head1 REPOSITORY

L<SPVM - Github|https://github.com/yuki-kimoto/SPVM>

=head1 BUG REPORT

L<GitHub Issue|https://github.com/yuki-kimoto/SPVM/issues>

=head1 SUPPORT

L<Github Discussions|https://github.com/yuki-kimoto/SPVM/discussions>

=head1 AUTHOR

Yuki Kimoto E<lt>kimoto.yuki@gmail.comE<gt>

=head1 CORE DEVELOPERS

motiE<lt>motohiko.ave@gmail.comE<gt>

=head1 CONTRIBUTORS

=over 2

=item * Mohammad S Anwar

=item * akinomyoga

=item * NAGAYASU Shinya

=item * Reini Urban

=item * chromatic

=item * Kazutake Hiramatsu

=item * Yasuaki Omokawa

=back

=head1 COPYRIGHT & LICENSE

Copyright 2018-2021 Yuki Kimoto, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.

=cut
