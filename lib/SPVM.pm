package SPVM;

use 5.008007;
use strict;
use warnings;

use DynaLoader;
use File::Basename 'basename', 'dirname';

use SPVM::BlessedObject;
use SPVM::BlessedObject::Array;
use SPVM::BlessedObject::Package;
use SPVM::BlessedObject::String;
use FindBin;

use SPVM::Builder;
use SPVM::ExchangeAPI;

use Encode 'encode', 'decode';

use Carp 'confess';

our $VERSION = '0.0952';

my $SPVM_INITED;
my $BUILDER;

require XSLoader;
XSLoader::load('SPVM', $VERSION);

my $loaded_spvm_modules = {};

sub import {
  my ($class, $package_name) = @_;

  unless ($BUILDER) {
    my $build_dir = $ENV{SPVM_BUILD_DIR};
    $BUILDER = SPVM::Builder->new(build_dir => $build_dir, include_dirs => [@INC]);
  }

  # Add package informations
  if (defined $package_name) {
    my ($file, $line) = (caller)[1, 2];

    # Compile SPVM source code and create runtime env
    my $compile_success = $BUILDER->compile_spvm($package_name, $file, $line);
    unless ($compile_success) {
      exit(255);
    }
    if ($compile_success) {
      my $added_package_names = $BUILDER->get_added_package_names;

      for my $added_package_name (@$added_package_names) {
        # Build Precompile packages - Compile C source codes and link them to SPVM precompile subroutine
        $BUILDER->build_and_bind_shared_lib($added_package_name, 'precompile');

        # Build native packages - Compile C source codes and link them to SPVM native subroutine
        $BUILDER->build_and_bind_shared_lib($added_package_name, 'native');
      }

      # Bind SPVM subroutine to Perl
      bind_to_perl($BUILDER, $added_package_names);
    }
  }
}

sub init {
  unless ($SPVM_INITED) {
    if (my $builder = $BUILDER) {
      # Call begin blocks
      $builder->_init;
    }
    $SPVM_INITED = 1;
  }
}

my $package_name_h = {};
my $binded_package_name_h = {};
sub bind_to_perl {
  my ($builder, $added_package_names) = @_;

  for my $package_name (@$added_package_names) {

    unless ($package_name_h->{$package_name}) {

      my $code = "package $package_name; our \@ISA = ('SPVM::BlessedObject::Package');";
      eval $code;

      if (my $error = $@) {
        confess $error;
      }
      $package_name_h->{$package_name} = 1;
    }

    my $sub_names = $builder->get_sub_names($package_name);

    for my $sub_name (@$sub_names) {
      # Destrutor is skip
      if ($sub_name eq 'DESTROY') {
        next;
      }
      # Anon subroutine is skip
      elsif (length $sub_name == 0) {
        next;
      }

      my $sub_abs_name = "${package_name}::$sub_name";

      # Define SPVM subroutine
      no strict 'refs';

      my ($package_name, $sub_name) = $sub_abs_name =~ /^(?:(.+)::)(.*)/;

      # Declare subroutine
      *{"$sub_abs_name"} = sub {
        SPVM::init() unless $SPVM_INITED;

        my $return_value;
        eval { $return_value = SPVM::call_sub($package_name, $sub_name, @_) };
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

sub call_sub {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::call_sub($BUILDER->{env}, @_);
}

1;

=encoding UTF-8

=head1 NAME

SPVM - Static Perl Virtual Machine. Fast Calculation, Fast Array Operation, and Easy C/C++ Binding.

=head1 SYNOPSIS

SPVM Module:

  # lib/MyMath.spvm
  package MyMath {
    sub sum : int ($nums : int[]) {

      my $total = 0;
      for (my $i = 0; $i < @$nums; $i++) {
        $total += $nums->[$i];
      }

      return $total;
    }
  }

Call SPVM subroutine from Perl

  # spvm.pl
  use strict;
  use warnings;
  use FindBin;
  use lib "$FindBin::Bin/lib";

  use SPVM 'MyMath';

  # Call subroutine
  my $total = MyMath->sum([3, 6, 8, 9]);

  print "Total: $total\n";

  # Call subroutine with packed data
  my $nums_packed = pack('l*', 3, 6, 8, 9);
  my $sv_nums = SPVM::new_int_array_from_bin($nums_packed);
  my $total_packed = MyMath->sum($sv_nums);

  print "Total Packed: $total_packed\n";

Precompiled SPVM Subroutine. This code is converted to C language and then converted to a shared library.

  # lib/MyMath.spvm
  package MyMath : precompile {
    sub sum : int ($nums : int[]) {

      my $total = 0;
      for (my $i = 0; $i < @$nums; $i++) {
        $total += $nums->[$i];
      }

      return $total;
    }
  }

=head1 DESCRIPTION

SPVM is Static Perl Virtual Machine. SPVM is a programming language which has Perlish syntax. SPVM provides fast Calculation & easy C/C++ Binding.

See L<SPVM Tutorial|SPVM::Document::Tutorial> at first.
If you want to convert Perl Data structres to SPVM data structures, See L<SPVM Exchange API|SPVM::Document::ExchangeAPI>. 
If you check SPVM performance, see L<SPVM Performance Benchmark|SPVM::Document::Benchmark>.

B<SPVM Features:>

=over 4

=item * B<Fast culcuration>, B<Fast array operation>, B<Small memory>

=item * B<Perl syntax>, B<Static typing>, B<Switch syntax>, B<Have language specification>

=item * B<Enum>, B<Type inference>, B<Anon subroutine>, B<Variable captures>

=item * B<Array initialization>,

=item * B<Reference count GC>, B<Weaken reference>, B<Module system>

=item * B<Exception>, B<Package variable>

=item * B<Object oriented programming>, B<Callback type>, B<Multi numeric type>, B<Multi numeric array type>, B<Reference type>

=item * B<Easy way to C/C++ binding>, B<Automatically Perl binding>, B<C99 math functions>

=item * B<Shared Library>, B<Precompile Subroutine into Machine code>

=item * B<Native API(C level api)>, B<C99 standard>

=back

=head1 DOCUMENT

=over 2

=item * L<SPVM::Document::Tutorial>

=item * L<SPVM::Document::Benchmark>

=item * L<SPVM::Document::ExchangeAPI>

=item * L<SPVM Document|https://yuki-kimoto.github.io/spvmdoc-public>

=item * L<SPVM Language Specification|https://yuki-kimoto.github.io/spvmdoc-public/language.html>

=item * L<SPVM Native API|https://yuki-kimoto.github.io/spvmdoc-public/native-api.html>

=back

=head1 CORE MODULES

=over 2

=item * L<SPVM::Document::Modules>

=back

=head1 ENVIRONMENT VARIABLE

=head2 SPVM_BUILD_DIR

SPVM build directory for precompile and native subroutine.

If SPVM_BUILD_DIR environment variable is not set, SPVM can't compile precompile subroutine and native subroutine, and a exception occur. You see error message "SPVM_BUILD_DIR environment variable must be set ...".

In bash, you can set SPVM_BUILD_DIR to the following.

  export SPVM_BUILD_DIR=~/.spvm_build

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
