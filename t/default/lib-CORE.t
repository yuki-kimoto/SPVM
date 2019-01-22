use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM;

my $BYTE_MAX = 127;
my $BYTE_MIN = -128;
my $SHORT_MAX = 32767;
my $SHORT_MIN = -32768;
my $INT_MAX = 2147483647;
my $INT_MIN = -2147483648;
my $LONG_MAX = 9223372036854775807;
my $LONG_MIN = -9223372036854775808;
my $FLOAT_PRECICE = 16384.5;
my $DOUBLE_PRECICE = 65536.5;

# Positive infinity(unix like system : inf, Windows : 1.#INF)
my $POSITIVE_INFINITY = 9**9**9;

my $NaN = 9**9**9 / 9**9**9;

my $nan_re = qr/(nan|ind)/i;

use SPVM 'TestCase::Lib::CORE';
use SPVM 'TestCase::Lib::CORE';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# new_oarray_proto
{
  # sliceb
  ok(TestCase::Lib::CORE->test_new_oarray_proto);
}

# slice
{
  # sliceb
  ok(TestCase::Lib::CORE->test_sliceb);

  # slices
  ok(TestCase::Lib::CORE->test_slices);

  # slicei
  ok(TestCase::Lib::CORE->test_slicei);

  # slicel
  ok(TestCase::Lib::CORE->test_slicel);

  # slicef
  ok(TestCase::Lib::CORE->test_slicef);

  # sliced
  ok(TestCase::Lib::CORE->test_sliced);

  # sliced
  ok(TestCase::Lib::CORE->test_sliceo);
}

# reverse
{
  # reverseb
  ok(TestCase::Lib::CORE->test_reverseb);

  # reverses
  ok(TestCase::Lib::CORE->test_reverses);

  # reversei
  ok(TestCase::Lib::CORE->test_reversei);

  # reversel
  ok(TestCase::Lib::CORE->test_reversel);

  # reversef
  ok(TestCase::Lib::CORE->test_reversef);

  # reversed
  ok(TestCase::Lib::CORE->test_reversed);

  # reversed
  ok(TestCase::Lib::CORE->test_reverseo);
}

# sort
{
  # sortb
  ok(TestCase::Lib::CORE->test_sortb);

  # sorts
  ok(TestCase::Lib::CORE->test_sorts);

  # sorti
  ok(TestCase::Lib::CORE->test_sorti);

  # sortl
  ok(TestCase::Lib::CORE->test_sortl);

  # sortf
  ok(TestCase::Lib::CORE->test_sortf);

  # sortd
  ok(TestCase::Lib::CORE->test_sortd);

  # sortd
  ok(TestCase::Lib::CORE->test_sorto);
}


ok(TestCase::Lib::CORE->test_join);

# type_name
{
  ok(TestCase::Lib::CORE->test_type_name);
}

# equals
{
  # equals_barray
  ok(TestCase::Lib::CORE->test_equals_barray);
  
  # equals_sarray
  ok(TestCase::Lib::CORE->test_equals_sarray);
  
  # equals_iarray
  ok(TestCase::Lib::CORE->test_equals_iarray);
  
  # equeals_larray
  ok(TestCase::Lib::CORE->test_equals_larray);
  
  # equals_farray
  ok(TestCase::Lib::CORE->test_equals_farray);
  
  # equals_darray
  ok(TestCase::Lib::CORE->test_equals_darray);

  # equals_oarray
  ok(TestCase::Lib::CORE->test_equals_darray);

  # equals_strarray
  ok(TestCase::Lib::CORE->test_equals_strarray);
}

# Copy
{
  # copy_str
  ok(TestCase::Lib::CORE->test_copy_str);
  
  # copy_barray
  ok(TestCase::Lib::CORE->test_copy_barray);
  
  # copy_sarray
  ok(TestCase::Lib::CORE->test_copy_sarray);
  
  # copy_iarray
  ok(TestCase::Lib::CORE->test_copy_iarray);
  
  # copy_larray
  ok(TestCase::Lib::CORE->test_copy_larray);
  
  # copy_farray
  ok(TestCase::Lib::CORE->test_copy_farray);
  
  # copy_darray
  ok(TestCase::Lib::CORE->test_copy_darray);
  
  # copy_oarray
  ok(TestCase::Lib::CORE->test_copy_oarray);
  
  # copy_strarray
  ok(TestCase::Lib::CORE->test_copy_strarray);
}

# Constant integral functions
{
  is(SPVM::CORE->INT8_MAX, 127);
  is(SPVM::CORE->INT8_MIN, -128);
  is(SPVM::CORE->INT16_MAX, 32767);
  is(SPVM::CORE->INT16_MIN, -32768);
  is(SPVM::CORE->INT32_MAX, 2147483647);
  is(SPVM::CORE->INT32_MIN, -2147483648);
  is(SPVM::CORE->INT64_MAX, 9223372036854775807);
  is(SPVM::CORE->INT64_MIN, -9223372036854775808);
}

# Constant floating point number functions
{
  is(SPVM::CORE->FLT_MAX, POSIX::FLT_MAX);
  is(SPVM::CORE->FLT_MIN, POSIX::FLT_MIN);
  is(SPVM::CORE->DBL_MAX, POSIX::DBL_MAX);
  is(SPVM::CORE->DBL_MIN, POSIX::DBL_MIN);
}

# Call subroutine
{
  ok(TestCase::Lib::CORE->test_sin);
  ok(TestCase::Lib::CORE->test_cos);
  ok(TestCase::Lib::CORE->test_tan);
}

# float
{
  ok(TestCase::Lib::CORE->test_float_pass_positive_infinity($POSITIVE_INFINITY));
  ok(TestCase::Lib::CORE->test_float_pass_nan($NaN));
  
  ok(TestCase::Lib::CORE->test_isinff);
  ok(TestCase::Lib::CORE->test_isfinitef);
  ok(TestCase::Lib::CORE->test_isnanf);
  
  is(SPVM::CORE->INFINITYF(), $POSITIVE_INFINITY);
  
  like(SPVM::CORE->NANF(), $nan_re);
}

# SPVM::Double
{
  ok(TestCase::Lib::CORE->test_double_pass_positive_infinity($POSITIVE_INFINITY));
  ok(TestCase::Lib::CORE->test_double_pass_nan($NaN));
  
  ok(TestCase::Lib::CORE->test_isinf);
  ok(TestCase::Lib::CORE->test_isfinite);
  ok(TestCase::Lib::CORE->test_isnan);
  
  is(SPVM::CORE->INFINITY(), $POSITIVE_INFINITY);
  
  like(SPVM::CORE->NAN(), $nan_re);
}

{
  ok(TestCase::Lib::CORE->test_byte_constant);
  ok(TestCase::Lib::CORE->test_short_constant);
  ok(TestCase::Lib::CORE->test_int_constant);
}

{
  is(SPVM::CORE->INT8_MAX, $BYTE_MAX);
  is(SPVM::CORE->INT8_MIN, $BYTE_MIN);
  is(SPVM::CORE->INT16_MAX, $SHORT_MAX);
  is(SPVM::CORE->INT16_MIN, $SHORT_MIN);
  is(SPVM::CORE->INT32_MAX, $INT_MAX);
  is(SPVM::CORE->INT32_MIN, $INT_MIN);
  is(SPVM::CORE->INT64_MAX, $LONG_MAX);
  is(SPVM::CORE->INT64_MIN, $LONG_MIN);
}
{
  # Check not Inf or NaN in Perl value
  like(SPVM::CORE->FLT_MAX(), qr/[0-9]/);
  like(SPVM::CORE->FLT_MIN(), qr/[0-9]/);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
