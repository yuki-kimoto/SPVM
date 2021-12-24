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

use Encode 'encode', 'decode';

use Carp 'confess';

our $VERSION = '0.9021';

my $SPVM_INITED;
my $BUILDER;

require XSLoader;
XSLoader::load('SPVM', $VERSION);

my $loaded_spvm_modules = {};

sub import {
  my ($class, $class_name) = @_;

  unless ($BUILDER) {
    my $build_dir = $ENV{SPVM_BUILD_DIR};
    $BUILDER = SPVM::Builder->new(build_dir => $build_dir, include_dirs => [@INC]);
  }

  # Add class informations
  if (defined $class_name) {
    $class_name =~ s/^SPVM:://;
    
    my ($file, $line) = (caller)[1, 2];

    # Compile SPVM source code and create runtime env
    my $compile_success = $BUILDER->compile_spvm($class_name, $file, $line);
    
    unless ($compile_success) {
      exit(255);
    }
    if ($compile_success) {
      my $added_class_names = $BUILDER->get_added_class_names;
      for my $added_class_name (@$added_class_names) {
        
        # Build Precompile classs - Compile C source codes and link them to SPVM precompile method
        $BUILDER->build_and_bind_shared_lib($added_class_name, 'precompile');

        # Build native classs - Compile C source codes and link them to SPVM native method
        $BUILDER->build_and_bind_shared_lib($added_class_name, 'native');
      }

      # Bind SPVM method to Perl
      bind_to_perl($BUILDER, $added_class_names);
    }
  }
}

sub init {
  unless ($SPVM_INITED) {
    if (my $builder = $BUILDER) {
      # Call init blocks
      $builder->_init;
    }
    $SPVM_INITED = 1;
  }
}

my $class_name_h = {};
my $binded_class_name_h = {};
sub bind_to_perl {
  my ($builder, $added_class_names) = @_;

  for my $class_name (@$added_class_names) {
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

=encoding UTF-8

=head1 NAME

SPVM - Static Perl Virtual Machine. Fast Calculation, Fast Array Operation, and Easy C/C++ Binding.

=head1 CAUTHION

B<L<SPVM> is yet before 1.0 released. L<SPVM> is changed without warnings. There will be quite a lot of changes until I feel enough good.>

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

Call SPVM method from Perl

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

SPVM is Static Perl Virtual Machine. SPVM is a programming language which has Perlish syntax. SPVM provides fast Calculation & easy C/C++ Binding.

=head1 FEATURES

=over 4

=item * Fast culcuration, Fast array operation

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

SPVM Starndard Modules.

=over 2

=item * L<Standard Modules|SPVM::Document::Modules>

=back

=head2 Performance Benchmark

SPVM Performance Benchmark.

=over 2

=item * L<Benchmark|SPVM::Document::Benchmark>

=back

=head2 Exchagne API

SPVM Exchange API is APIs which convert Perl data structures to SPVM data structures, and the reverse.

=over 2

=item * L<ExchangeAPI|SPVM::Document::ExchangeAPI>

=back

=head2 Native API

SPVM Native APIs is C APIs used in SPVM native method.

=over 2

=item * L<NativeAPI|SPVM::Document::NativeAPI>

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

This release is beta release before SPVM 1.0. The features is changed without warnings.

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

=head1 CONTRIBUTERS

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
