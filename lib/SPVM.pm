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

Use SPVM Module from Perl

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

Precompiled SPVM Subroutine. This means SPVM code is converted to Machine Code:

  # lib/MyMath.spvm
  package MyMath : precompile {
    sub sum_precompile : int ($nums : int[]) {

      my $total = 0;
      for (my $i = 0; $i < @$nums; $i++) {
        $total += $nums->[$i];
      }

      return $total;
    }
  }

Call SPVM Precompile Subroutine from Perl

  # spvm.pl
  use strict;
  use warnings;
  use FindBin;
  use lib "$FindBin::Bin/lib";

  use SPVM 'MyMath';

  # Call precompile subroutine
  my $total_precompile = MyMath->sum_precompile([3, 6, 8, 9]);

  print "Total Precompile: $total_precompile\n";

SPVM Native Subroutine. This means SPVM subroutine call C/C++ native subroutine:

  # lib/MyMath.spvm
  package MyMath {
    native sub sum_native : int ($nums : int[]);
  }

  // lib/MyMath.c
  #include "spvm_native.h"

  int32_t SPNATIVE__MyMath__sum_native(SPVM_ENV* env, SPVM_VALUE* stack) {

    void* sv_nums = stack[0].oval;

    int32_t length = env->length(env, sv_nums);

    int32_t* nums = env->get_elems_int(env, sv_nums);

    int32_t total = 0;
    for (int32_t i = 0; i < length; i++) {
      total += nums[i];
    }

    stack[0].ival = total;

    return SPVM_SUCCESS;
  }

  # lib/MyMath.config

  use strict;
  use warnings;

  use SPVM::Builder::Config;
  my $bconf = SPVM::Builder::Config->new_c99;

  $bconf;

Use SPVM Native Subroutine from Perl

  # spvm.pl
  use strict;
  use warnings;
  use FindBin;
  use lib "$FindBin::Bin/lib";

  use SPVM 'MyMath';

  # Call native subroutine
  my $total_native = MyMath->sum_native([3, 6, 8, 9]);

  print "Total Native: $total_native\n";

Environment Variable "SPVM_BUILD_DIR" must be set for precompile and native subroutine

  # bash example
  export SPVM_BUILD_DIR=~/.spvm_build

=head1 DESCRIPTION

SPVM is Static Perl Virtual Machine. Provide fast calculation & easy C/C++ Binding.

B<Features:>

=over 4

=item * B<Fast culcuration>, B<Fast array operation>, B<Small memory>

=item * B<Perl syntax>, B<Static typing>, B<Switch syntax>, B<Have language specification>

=item * B<Enum>, B<Type inference>, B<Anon subroutine>, B<Variable captures>

=item * B<Array initialization>,

=item * B<Reference count GC>, B<Weaken reference>, B<Module system>

=item * B<Exception>, B<Package variable>

=item * B<Object oriented>, B<Inteface>, B<Value type>, B<Value array type>, B<Reference type>

=item * B<Easy way to C/C++ binding>, B<Automatically Perl binding>, B<C99 math functions>

=item * B<Shared Library>, B<Precompile Subroutine into Machine code>

=item * B<Native API(C level api)>, B<C99 standard>

=back

=head1 DOCUMENT

Currently some ports of document are use Automatic translation, so not accurate and maybe difficult to read.

=over 2

=item * L<SPVM Document|https://yuki-kimoto.github.io/spvmdoc-public>

=item * L<SPVM Tutorial|https://yuki-kimoto.github.io/spvmdoc-public/tutorial.html>

=item * L<SPVM Language Specification|https://yuki-kimoto.github.io/spvmdoc-public/language.html>

=item * L<SPVM Exchange API|https://yuki-kimoto.github.io/spvmdoc-public/exchange-api.html>

=item * L<SPVM Native API|https://yuki-kimoto.github.io/spvmdoc-public/native-api.html>

=item * L<SPVM Performance Benchmark|https://yuki-kimoto.github.io/spvmdoc-public/benchmark.html>

=head1 CORE MODULES

SPVM Core Modules.

L<SPVM::Document::Modules>

=back

=head1 FUNCTIONS

Function names and examples is only listed.

See SPVM Exchange API about the details.

L<SPVM Exchange API|https://yuki-kimoto.github.io/spvmdoc-public/exchange-api.html>

=head2 new_string

  my $spvm_string = SPVM::new_string("あいう");

New SPVM string from decoded string.

Return value is L<SPVM::BlessedObject::String> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::String>.

=head2 new_string_from_bin

  my $spvm_string = SPVM::new_string_from_bin("abc");

New SPVM string from binary data.

Return value is L<SPVM::BlessedObject::String> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::String>.

=head2 new_byte_array

  my $spvm_nums = SPVM::new_byte_array([ 1, -5, 100]);

New SPVM byte array from Perl array reference.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_byte_array_unsigned

  my $spvm_nums = SPVM::new_byte_array_unsigned([1, 2, 255]);

New SPVM byte array from Perl array reference. Each element in Perl array reference is interpreted an unsigned 8-bit integer.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_byte_array_len

  my $spvm_nums = SPVM::new_byte_array_len(3)

New SPVM byte array with array length.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_byte_array_from_bin

  # Pack singed 8-bit integers
  my $bin = pack('c*', 1, -5, 100);
  my $spvm_nums = SPVM::new_byte_array_from_bin($bin);

  # Pack unsigned 8-bit integers
  my $bin = pack('C*', 1, 2, 255);
  my $spvm_nums = SPVM::new_byte_array_from_bin($bin);

New SPVM byte array with packed binary data. The packed binary data is interpreted a sequence of signed singed 8-bit integers or unsigned 8-bit intergers.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_byte_array_from_string

  use utf8;
  my $string = "あいう";
  my $spvm_nums = new_byte_array_from_string($string);

New SPVM byte array from decoded Perl string. The decoded Perl string is encoded to UTF-8.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_short_array

  my $spvm_nums = SPVM::new_short_array([1, 2, 3]);

New SPVM short array from Perl array reference.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_short_array_unsigned

  my $spvm_nums = SPVM::new_short_array_unsigned([1, 2, 65535]);

New SPVM short array from Perl array reference. Each element in Perl array reference is interpreted an unsigned 16-bit integer.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_short_array_len

  my $spvm_nums = SPVM::new_short_array_len(3)

New SPVM short array with array length.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_short_array_from_bin

  # Pack signed 16-bit intergers
  my $bin = pack('s*', 1, -5, 100);
  my $spvm_nums = SPVM::new_short_array_from_bin($bin);

  # Pack unsigned 16-bit intergers
  my $bin = pack('S*', 1, 2, 65535);
  my $spvm_nums = SPVM::new_short_array_from_bin($bin);

New SPVM short array with packed binary data. The packed binary data is interpreted a sequence of signed 16-bit interger or unsinged 16-bit integer.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_int_array

  my $spvm_nums = SPVM::new_int_array([1, 2, 3]);

New SPVM int array from Perl array reference.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_int_array_unsigned

  my $spvm_nums = SPVM::new_int_array_unsigned([1, 2, 4294967295]);

New SPVM int array from Perl array reference. Each element in Perl array reference is interpreted an unsigned 32-bit integer.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_int_array_len

  my $spvm_nums = SPVM::new_int_array_len(3)

New SPVM int array with array length.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_int_array_from_bin

  # Pack signed 32-bit intergers
  my $bin = pack('l*', 1, -5, 100);
  my $spvm_nums = SPVM::new_int_array_from_bin($bin);

  # Pack unsigned 32-bit intergers
  my $bin = pack('L*', 1, 2, 65535);
  my $spvm_nums = SPVM::new_int_array_from_bin($bin);

New SPVM int array with packed binary data. The packed binary data is interpreted a sequence of signed 32-bit interger or unsinged 32-bit integer.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_long_array

  my $spvm_nums = SPVM::new_long_array([1, 2, 3]);

New SPVM long array from Perl array reference.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_long_array_unsigned

  my $spvm_nums = SPVM::new_long_array_unsigned([1, 2, 18446744073709551615]);

New SPVM long array from Perl array reference. Each element in Perl array reference is interpreted an unsigned 64-bit integer.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_long_array_len

  my $spvm_nums = SPVM::new_long_array_len(3)

New SPVM long array with array length.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_long_array_from_bin

  # Pack signed 64-bit intergers
  my $bin = pack('l*', 1, -5, 100);
  my $spvm_nums = SPVM::new_long_array_from_bin($bin);

  # Pack unsigned 64-bit intergers
  my $bin = pack('L*', 1, 2, 65535);
  my $spvm_nums = SPVM::new_long_array_from_bin($bin);

New SPVM long array with packed binary data. The packed binary data is interpreted a sequence of signed 64-bit interger or unsinged 64-bit integer.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_float_array

  my $spvm_nums = SPVM::new_float_array([1.5, 2.5, 3.0]);

New SPVM float array from Perl array reference.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_float_array_len

  my $spvm_nums = SPVM::new_float_array_len(3)

New SPVM float array with array length.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_float_array_from_bin

  # Pack float value
  my $bin = pack('f*', 1, -5.5, 4.5);
  my $spvm_nums = SPVM::new_float_array_from_bin($bin);

New SPVM float array with packed binary data. The packed binary data is interpreted a sequence of 32-bit floating points.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_double_array

  my $spvm_nums = SPVM::new_double_array([1.5, 2.5, 3.0]);

New SPVM double array from Perl array reference.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_double_array_len

  my $spvm_nums = SPVM::new_double_array_len(3)

New SPVM double array with array length.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_double_array_from_bin

  # Pack double value
  my $bin = pack('d*', 1, -5.5, 4.5);
  my $spvm_nums = SPVM::new_double_array_from_bin($bin);

New SPVM double array with packed binary data. The packed binary data is interpreted a sequence of 64-bit floating points.

Return value is L<SPVM::BlessedObject::Array> object. If you want to convert SPVM array to Perl data structure, use the methods of L<SPVM::BlessedObject::Array>.

=head2 new_object_array

=head2 new_string_array

=head2 new_mulnum_array

=head2 new_mulnum_array_from_bin

=head2 get_exception

=head2 set_exception

=head2 array_to_bin

=head2 array_to_elems

=head2 get_memory_blocks_count

=head2 call_sub

=head1 ENVIRONMENT VARIABLE

=head2 SPVM_BUILD_DIR

SPVM build directory for precompile and native subroutine.

If SPVM_BUILD_DIR environment variable is not set, SPVM can't compile precompile subroutine and native subroutine, and a exception occur. You see error message "SPVM_BUILD_DIR environment variable must be set ...".

In bash, you can set SPVM_BUILD_DIR to the following.

  export SPVM_BUILD_DIR=~/.spvm_build

=head1 CAUTION

This release is beta release before SPVM 1.0. Features is changed without warnings.

SPVM 1.0 is First Major Release

But Full backward compatibility is not guaranteed because SPVM is not used much in corporate work yet.

If SPVM has fatal bugs in the specification or implementation, the backward compatibility is broken and the bug will be fixed after discussion.

=head1 SUPPORT

If you have problems or find bugs, comment to GitHub Issue.

L<SPVM(GitHub)|https://github.com/yuki-kimoto/SPVM>.

=head1 AUTHOR

Yuki Kimoto E<lt>kimoto.yuki@gmail.com<gt>

=head1 CORE DEVELOPERS

moti<lt>motohiko.ave@gmail.com<gt>

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

Copyright 2018-2020 Yuki Kimoto, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.

=cut
