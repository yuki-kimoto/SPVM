use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM;
use POSIX();
use TestFile;

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

# Copy test_files to test_files_tmp with replacing os newline
TestFile::copy_test_files_tmp_replace_newline();

# Positive infinity(unix like system : inf, Windows : 1.#INF)
my $POSITIVE_INFINITY = 9**9**9;

my $NaN = 9**9**9 / 9**9**9;

my $nan_re = qr/(nan|ind)/i;

use SPVM 'TestCase::Lib::SPVM::CORE';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Complex
{
  ok(TestCase::Lib::SPVM::CORE->test_complexf());
  ok(TestCase::Lib::SPVM::CORE->test_complexd());
  ok(TestCase::Lib::SPVM::CORE->test_complex_farray());
  ok(TestCase::Lib::SPVM::CORE->test_complex_darray());
}

# strtoi
{
  ok(TestCase::Lib::SPVM::CORE->test_strtoi);
  ok(TestCase::Lib::SPVM::CORE->test_strtol);
  ok(TestCase::Lib::SPVM::CORE->test_strtof);
  ok(TestCase::Lib::SPVM::CORE->test_strtod);
}

# isdigit
{
  ok(TestCase::Lib::SPVM::CORE->test_isdigit);
}

# rand
{
  ok(TestCase::Lib::SPVM::CORE->test_rand);
}

# uc
{
  ok(TestCase::Lib::SPVM::CORE->test_uc);
}

# lcfirst
{
  ok(TestCase::Lib::SPVM::CORE->test_lcfirst);
}

# lc
{
  ok(TestCase::Lib::SPVM::CORE->test_lc);
}

# replace
{
  ok(TestCase::Lib::SPVM::CORE->test_replace_all);
}

# replace
{
  ok(TestCase::Lib::SPVM::CORE->test_replace);
}

# memmoveb
{
  ok(TestCase::Lib::SPVM::CORE->test_memmoveb);
}

# memcpyb
{
  ok(TestCase::Lib::SPVM::CORE->test_memcpyb);
}

# index
{
  ok(TestCase::Lib::SPVM::CORE->test_index);
}

# rindex
{
  ok(TestCase::Lib::SPVM::CORE->test_rindex);
}

# starts_with
{
  ok(TestCase::Lib::SPVM::CORE->test_starts_with);
}

# strerror
{
  ok(TestCase::Lib::SPVM::CORE->test_strerror);
}

# contains
{
  ok(TestCase::Lib::SPVM::CORE->test_contains);
}

# new_oarray_proto
{
  # sliceb
  ok(TestCase::Lib::SPVM::CORE->test_new_oarray_proto);
}

# slice
{
  # sliceb
  ok(TestCase::Lib::SPVM::CORE->test_sliceb);

  # slices
  ok(TestCase::Lib::SPVM::CORE->test_slices);

  # slicei
  ok(TestCase::Lib::SPVM::CORE->test_slicei);

  # slicel
  ok(TestCase::Lib::SPVM::CORE->test_slicel);

  # slicef
  ok(TestCase::Lib::SPVM::CORE->test_slicef);

  # sliced
  ok(TestCase::Lib::SPVM::CORE->test_sliced);

  # sliced
  ok(TestCase::Lib::SPVM::CORE->test_sliceo);
}

# reverse
{
  # reverseb
  ok(TestCase::Lib::SPVM::CORE->test_reverseb);

  # reverses
  ok(TestCase::Lib::SPVM::CORE->test_reverses);

  # reversei
  ok(TestCase::Lib::SPVM::CORE->test_reversei);

  # reversel
  ok(TestCase::Lib::SPVM::CORE->test_reversel);

  # reversef
  ok(TestCase::Lib::SPVM::CORE->test_reversef);

  # reversed
  ok(TestCase::Lib::SPVM::CORE->test_reversed);

  # reversed
  ok(TestCase::Lib::SPVM::CORE->test_reverseo);
}

# join
{
  ok(TestCase::Lib::SPVM::CORE->test_join);
  ok(TestCase::Lib::SPVM::CORE->test_joinb);
  ok(TestCase::Lib::SPVM::CORE->test_joins);
  ok(TestCase::Lib::SPVM::CORE->test_joini);
  ok(TestCase::Lib::SPVM::CORE->test_joinl);
  ok(TestCase::Lib::SPVM::CORE->test_joinf);
  ok(TestCase::Lib::SPVM::CORE->test_joind);
}

# get_type_name
{
  ok(TestCase::Lib::SPVM::CORE->test_get_type_name);
}

# equals
{
  # equals_barray
  ok(TestCase::Lib::SPVM::CORE->test_equals_barray);
  
  # equals_sarray
  ok(TestCase::Lib::SPVM::CORE->test_equals_sarray);
  
  # equals_iarray
  ok(TestCase::Lib::SPVM::CORE->test_equals_iarray);
  
  # equeals_larray
  ok(TestCase::Lib::SPVM::CORE->test_equals_larray);
  
  # equals_farray
  ok(TestCase::Lib::SPVM::CORE->test_equals_farray);
  
  # equals_darray
  ok(TestCase::Lib::SPVM::CORE->test_equals_darray);

  # equals_oarray
  ok(TestCase::Lib::SPVM::CORE->test_equals_darray);

  # equals_strarray
  ok(TestCase::Lib::SPVM::CORE->test_equals_strarray);
}

# Copy
{
  # copy_str
  ok(TestCase::Lib::SPVM::CORE->test_copy_str);
  
  # copy_barray
  ok(TestCase::Lib::SPVM::CORE->test_copy_barray);
  
  # copy_sarray
  ok(TestCase::Lib::SPVM::CORE->test_copy_sarray);
  
  # copy_iarray
  ok(TestCase::Lib::SPVM::CORE->test_copy_iarray);
  
  # copy_larray
  ok(TestCase::Lib::SPVM::CORE->test_copy_larray);
  
  # copy_farray
  ok(TestCase::Lib::SPVM::CORE->test_copy_farray);
  
  # copy_darray
  ok(TestCase::Lib::SPVM::CORE->test_copy_darray);
  
  # copy_strarray
  ok(TestCase::Lib::SPVM::CORE->test_copy_strarray);
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

{
  ok(TestCase::Lib::SPVM::CORE->test_byte_constant);
  ok(TestCase::Lib::SPVM::CORE->test_short_constant);
  ok(TestCase::Lib::SPVM::CORE->test_int_constant);
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

# getenv
=pod
{
  # TODO: Windows compatibility
  $ENV{SPVM_ENV_NAME} = "SPVM_ENV_VALUE";
  ok(TestCase::Lib::SPVM::CORE->test_getenv);
}
=cut

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
