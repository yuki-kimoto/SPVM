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

use SPVM::Global;

use Carp 'confess';

sub api { $SPVM::Global::API }

sub import {
  my ($class, $class_name) = @_;

  my ($file, $line) = (caller)[1, 2];
  
  SPVM::Global::build_class($class_name, $file, $line);
}

sub new_byte_array {
  SPVM::ExchangeAPI::new_byte_array($SPVM::Global::API, @_);
}

sub new_byte_array_unsigned {
  SPVM::ExchangeAPI::new_byte_array_unsigned($SPVM::Global::API, @_);
}

sub new_byte_array_len {
  SPVM::ExchangeAPI::new_byte_array_len($SPVM::Global::API, @_);
}

sub new_byte_array_from_bin {
  SPVM::ExchangeAPI::new_byte_array_from_bin($SPVM::Global::API, @_);
}
sub new_byte_array_from_string {
  SPVM::ExchangeAPI::new_byte_array_from_string($SPVM::Global::API, @_);
}

sub new_short_array {
  SPVM::ExchangeAPI::new_short_array($SPVM::Global::API, @_);
}

sub new_short_array_unsigned {
  SPVM::ExchangeAPI::new_short_array_unsigned($SPVM::Global::API, @_);
}

sub new_short_array_len {
  SPVM::ExchangeAPI::new_short_array_len($SPVM::Global::API, @_);
}

sub new_short_array_from_bin {
  SPVM::ExchangeAPI::new_short_array_from_bin($SPVM::Global::API, @_);
}
sub new_int_array {
  SPVM::ExchangeAPI::new_int_array($SPVM::Global::API, @_);
}

sub new_int_array_unsigned {
  SPVM::ExchangeAPI::new_int_array_unsigned($SPVM::Global::API, @_);
}

sub new_int_array_len {
  SPVM::ExchangeAPI::new_int_array_len($SPVM::Global::API, @_);
}

sub new_int_array_from_bin {
  SPVM::ExchangeAPI::new_int_array_from_bin($SPVM::Global::API, @_);
}
sub new_long_array {
  SPVM::ExchangeAPI::new_long_array($SPVM::Global::API, @_);
}

sub new_long_array_unsigned {
  SPVM::ExchangeAPI::new_long_array_unsigned($SPVM::Global::API, @_);
}

sub new_long_array_len {
  SPVM::ExchangeAPI::new_long_array_len($SPVM::Global::API, @_);
}

sub new_long_array_from_bin {
  SPVM::ExchangeAPI::new_long_array_from_bin($SPVM::Global::API, @_);
}
sub new_float_array {
  SPVM::ExchangeAPI::new_float_array($SPVM::Global::API, @_);
}
sub new_float_array_len {
  SPVM::ExchangeAPI::new_float_array_len($SPVM::Global::API, @_);
}

sub new_float_array_from_bin {
  SPVM::ExchangeAPI::new_float_array_from_bin($SPVM::Global::API, @_);
}
sub new_double_array {
  SPVM::ExchangeAPI::new_double_array($SPVM::Global::API, @_);
}

sub new_double_array_len {
  SPVM::ExchangeAPI::new_double_array_len($SPVM::Global::API, @_);
}

sub new_double_array_from_bin {
  SPVM::ExchangeAPI::new_double_array_from_bin($SPVM::Global::API, @_);
}
sub new_string {
  SPVM::ExchangeAPI::new_string($SPVM::Global::API, @_);
}

sub new_string_from_bin {
  SPVM::ExchangeAPI::new_string_from_bin($SPVM::Global::API, @_);
}

sub new_object_array {
  SPVM::ExchangeAPI::new_object_array($SPVM::Global::API, @_);
}

sub new_object_array_len {
  SPVM::ExchangeAPI::new_object_array_len($SPVM::Global::API, @_);
}

sub new_any_object_array {
  SPVM::ExchangeAPI::new_any_object_array($SPVM::Global::API, @_);
}

sub new_mulnum_array {
  SPVM::ExchangeAPI::new_mulnum_array($SPVM::Global::API, @_);
}

sub new_mulnum_array_from_bin {
  SPVM::ExchangeAPI::new_mulnum_array_from_bin($SPVM::Global::API, @_);
}

sub new_string_array {
  SPVM::ExchangeAPI::new_string_array($SPVM::Global::API, @_);
}

sub new_string_array_len {
  SPVM::ExchangeAPI::new_string_array_len($SPVM::Global::API, @_);
}

sub get_exception {
  SPVM::ExchangeAPI::get_exception($SPVM::Global::API, @_);
}

sub set_exception {
  SPVM::ExchangeAPI::set_exception($SPVM::Global::API, @_);
}

sub get_memory_blocks_count {
  SPVM::ExchangeAPI::get_memory_blocks_count($SPVM::Global::API, @_);
}

sub call_method {
  SPVM::ExchangeAPI::call_method($SPVM::Global::API, @_);
}

sub new_address_object {
  SPVM::ExchangeAPI::new_address_object($SPVM::Global::API, @_);
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
