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

use SPVM 'TestCase::CoreFunc::Basic';
use SPVM 'TestCase::CoreFunc::Math';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# new_oarray_proto
{
  # sliceb
  ok(TestCase::CoreFunc::Basic->test_new_oarray_proto);
}

# slice
{
  # sliceb
  ok(TestCase::CoreFunc::Basic->test_sliceb);

  # slices
  ok(TestCase::CoreFunc::Basic->test_slices);

  # slicei
  ok(TestCase::CoreFunc::Basic->test_slicei);

  # slicel
  ok(TestCase::CoreFunc::Basic->test_slicel);

  # slicef
  ok(TestCase::CoreFunc::Basic->test_slicef);

  # sliced
  ok(TestCase::CoreFunc::Basic->test_sliced);

  # sliced
  ok(TestCase::CoreFunc::Basic->test_sliceo);
}

# reverse
{
  # reverseb
  ok(TestCase::CoreFunc::Basic->test_reverseb);

  # reverses
  ok(TestCase::CoreFunc::Basic->test_reverses);

  # reversei
  ok(TestCase::CoreFunc::Basic->test_reversei);

  # reversel
  ok(TestCase::CoreFunc::Basic->test_reversel);

  # reversef
  ok(TestCase::CoreFunc::Basic->test_reversef);

  # reversed
  ok(TestCase::CoreFunc::Basic->test_reversed);

  # reversed
  ok(TestCase::CoreFunc::Basic->test_reverseo);
}

# sort
{
  # sortb
  ok(TestCase::CoreFunc::Basic->test_sortb);

  # sorts
  ok(TestCase::CoreFunc::Basic->test_sorts);

  # sorti
  ok(TestCase::CoreFunc::Basic->test_sorti);

  # sortl
  ok(TestCase::CoreFunc::Basic->test_sortl);

  # sortf
  ok(TestCase::CoreFunc::Basic->test_sortf);

  # sortd
  ok(TestCase::CoreFunc::Basic->test_sortd);

  # sortd
  ok(TestCase::CoreFunc::Basic->test_sorto);
}


ok(TestCase::CoreFunc::Math->test_join);

# type_name
{
  ok(TestCase::CoreFunc::Basic->test_type_name);
}

# equals
{
  # equals_barray
  ok(TestCase::CoreFunc::Basic->test_equals_barray);
  
  # equals_sarray
  ok(TestCase::CoreFunc::Basic->test_equals_sarray);
  
  # equals_iarray
  ok(TestCase::CoreFunc::Basic->test_equals_iarray);
  
  # equeals_larray
  ok(TestCase::CoreFunc::Basic->test_equals_larray);
  
  # equals_farray
  ok(TestCase::CoreFunc::Basic->test_equals_farray);
  
  # equals_darray
  ok(TestCase::CoreFunc::Basic->test_equals_darray);

  # equals_oarray
  ok(TestCase::CoreFunc::Basic->test_equals_darray);
}

# Copy
{
  ok(TestCase::CoreFunc::Basic->test_copy_str);
  ok(TestCase::CoreFunc::Basic->test_copy_barray);
  ok(TestCase::CoreFunc::Basic->test_copy_sarray);
  ok(TestCase::CoreFunc::Basic->test_copy_iarray);
  ok(TestCase::CoreFunc::Basic->test_copy_larray);
  ok(TestCase::CoreFunc::Basic->test_copy_farray);
  ok(TestCase::CoreFunc::Basic->test_copy_farray);
  ok(TestCase::CoreFunc::Basic->test_copy_oarray);
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
  ok(TestCase::CoreFunc::Math->test_sin);
  ok(TestCase::CoreFunc::Math->test_cos);
  ok(TestCase::CoreFunc::Math->test_tan);
}

# float
{
  ok(TestCase::CoreFunc::Math->test_float_pass_positive_infinity($POSITIVE_INFINITY));
  ok(TestCase::CoreFunc::Math->test_float_pass_nan($NaN));
  
  ok(TestCase::CoreFunc::Math->test_isinff);
  ok(TestCase::CoreFunc::Math->test_isfinitef);
  ok(TestCase::CoreFunc::Math->test_isnanf);
  
  is(SPVM::CORE->INFINITYF(), $POSITIVE_INFINITY);
  
  like(SPVM::CORE->NANF(), $nan_re);
}

# SPVM::Double
{
  ok(TestCase::CoreFunc::Math->test_double_pass_positive_infinity($POSITIVE_INFINITY));
  ok(TestCase::CoreFunc::Math->test_double_pass_nan($NaN));
  
  ok(TestCase::CoreFunc::Math->test_isinf);
  ok(TestCase::CoreFunc::Math->test_isfinite);
  ok(TestCase::CoreFunc::Math->test_isnan);
  
  is(SPVM::CORE->INFINITY(), $POSITIVE_INFINITY);
  
  like(SPVM::CORE->NAN(), $nan_re);
}

{
  ok(TestCase::CoreFunc::Math->test_byte_constant);
  ok(TestCase::CoreFunc::Math->test_short_constant);
  ok(TestCase::CoreFunc::Math->test_int_constant);
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
