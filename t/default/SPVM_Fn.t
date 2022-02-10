use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

# SPVM::Fn tests is separated multiple files(smaller than 50KB)
# The reason is gcc can't compile the precompile code for the insufficient memory
# in some environment of CPAN testers.
use SPVM 'TestCase::Lib::Fn1';
use SPVM 'TestCase::Lib::Fn2';
use SPVM 'TestCase::Lib::Fn3';

use SPVM 'Fn';

use POSIX();
use TestFile;

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

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

# crand
{
  ok(SPVM::TestCase::Lib::Fn3->test_crand);
}

# rand
{
  ok(SPVM::TestCase::Lib::Fn3->test_rand);
}

# srand
SKIP: {
  if ($^O eq 'openbsd') {
    skip "openbsd srand don't fllow POSIX", 6;
  }
  
  {
    ok(SPVM::TestCase::Lib::Fn3->test_srand);
  }
}

# RAND_MAX
{
  ok(SPVM::TestCase::Lib::Fn3->test_RAND_MAX);
}

# Copy
{
  # copy_string
  ok(SPVM::TestCase::Lib::Fn3->test_copy_str);
}

# Constant integral functions
{
  is(SPVM::Fn->INT8_MAX, 127);
  is(SPVM::Fn->INT8_MIN, -128);
  is(SPVM::Fn->INT16_MAX, 32767);
  is(SPVM::Fn->INT16_MIN, -32768);
  is(SPVM::Fn->INT32_MAX, 2147483647);
  is(SPVM::Fn->INT32_MIN, -2147483648);
  is(SPVM::Fn->INT64_MAX, 9223372036854775807);
  is(SPVM::Fn->INT64_MIN, -9223372036854775808);
  is(SPVM::Fn->UINT8_MAX, -1);
  is(SPVM::Fn->UINT16_MAX, -1);
  is(SPVM::Fn->UINT32_MAX, -1);
  is(SPVM::Fn->UINT64_MAX, -1);
}

# Constant floating point number functions
{
  is(SPVM::Fn->FLT_MAX, POSIX::FLT_MAX);
  is(SPVM::Fn->FLT_MIN, POSIX::FLT_MIN);
  is(SPVM::Fn->DBL_MAX, POSIX::DBL_MAX);
  is(SPVM::Fn->DBL_MIN, POSIX::DBL_MIN);
}

{
  ok(SPVM::TestCase::Lib::Fn3->test_byte_constant);
  ok(SPVM::TestCase::Lib::Fn3->test_short_constant);
  ok(SPVM::TestCase::Lib::Fn3->test_int_constant);
}

{
  is(SPVM::Fn->INT8_MAX, $BYTE_MAX);
  is(SPVM::Fn->INT8_MIN, $BYTE_MIN);
  is(SPVM::Fn->INT16_MAX, $SHORT_MAX);
  is(SPVM::Fn->INT16_MIN, $SHORT_MIN);
  is(SPVM::Fn->INT32_MAX, $INT_MAX);
  is(SPVM::Fn->INT32_MIN, $INT_MIN);
  is(SPVM::Fn->INT64_MAX, $LONG_MAX);
  is(SPVM::Fn->INT64_MIN, $LONG_MIN);
}
{
  # Check not Inf or NaN in Perl value
  like(SPVM::Fn->FLT_MAX(), qr/[0-9]/);
  like(SPVM::Fn->FLT_MIN(), qr/[0-9]/);
}

# hex
{
  ok(SPVM::TestCase::Lib::Fn3->test_hex);
}

# trim_ascii_space
{
  ok(SPVM::TestCase::Lib::Fn3->test_trim_ascii_space);
}

# split
{
  ok(SPVM::TestCase::Lib::Fn3->test_split);
}

# abs
{
  ok(SPVM::TestCase::Lib::Fn3->test_abs);
}

# labs
{
  ok(SPVM::TestCase::Lib::Fn3->test_labs);
}

# sprintf
{
  ok(SPVM::TestCase::Lib::Fn1->test_sprintf_d);
  ok(SPVM::TestCase::Lib::Fn1->test_sprintf_u);
  ok(SPVM::TestCase::Lib::Fn1->test_sprintf_ld);
  ok(SPVM::TestCase::Lib::Fn1->test_sprintf_lu);
  ok(SPVM::TestCase::Lib::Fn1->test_sprintf_f);
  ok(SPVM::TestCase::Lib::Fn1->test_sprintf_c);
  ok(SPVM::TestCase::Lib::Fn1->test_sprintf_s);
  ok(SPVM::TestCase::Lib::Fn1->test_sprintf_U);
  ok(SPVM::TestCase::Lib::Fn1->test_sprintf_percent);
  ok(SPVM::TestCase::Lib::Fn1->test_sprintf_all);
}

# to_int_with_base
{
  ok(SPVM::TestCase::Lib::Fn3->test_to_int);
  ok(SPVM::TestCase::Lib::Fn3->test_to_int_with_base);
  ok(SPVM::TestCase::Lib::Fn3->test_to_long);
  ok(SPVM::TestCase::Lib::Fn3->test_to_long_with_base);
  ok(SPVM::TestCase::Lib::Fn3->test_to_float);
  ok(SPVM::TestCase::Lib::Fn3->test_to_double);
}
# chompr
{
  ok(SPVM::TestCase::Lib::Fn3->test_chompr);
}
# is_alnum
{
  ok(SPVM::TestCase::Lib::Fn3->test_is_alnum);
}

# is_alpha
{
  ok(SPVM::TestCase::Lib::Fn3->test_is_alpha);
}

# is_alpha
{
  ok(SPVM::TestCase::Lib::Fn3->test_is_blank);
}

# is_cntrl
{
  ok(SPVM::TestCase::Lib::Fn3->test_is_cntrl);
}

# is_digit
{
  ok(SPVM::TestCase::Lib::Fn3->test_is_digit);
}

# is_graph
{
  ok(SPVM::TestCase::Lib::Fn3->test_is_graph);
}

# is_lower
{
  ok(SPVM::TestCase::Lib::Fn3->test_is_lower);
}

# is_print
{
  ok(SPVM::TestCase::Lib::Fn3->test_is_print);
}

# is_print
{
  ok(SPVM::TestCase::Lib::Fn3->test_is_print);
}

# is_punct
{
  ok(SPVM::TestCase::Lib::Fn3->test_is_punct);
}

# is_space
{
  ok(SPVM::TestCase::Lib::Fn3->test_is_space);
}

# is_upper
{
  ok(SPVM::TestCase::Lib::Fn3->test_is_upper);
}

# is_xdigit
{
  ok(SPVM::TestCase::Lib::Fn3->test_is_xdigit);
}

# to_lower
{
  ok(SPVM::TestCase::Lib::Fn3->test_to_lower);
}

# to_upper
{
  ok(SPVM::TestCase::Lib::Fn3->test_to_upper);
}

# is_perl_space
{
  ok(SPVM::TestCase::Lib::Fn3->test_is_perl_space);
}

# is_perl_word
{
  ok(SPVM::TestCase::Lib::Fn3->test_is_perl_word);
}
# uc
{
  ok(SPVM::TestCase::Lib::Fn3->test_uc);
}

# lcfirst
{
  ok(SPVM::TestCase::Lib::Fn3->test_lcfirst);
}

# lc
{
  ok(SPVM::TestCase::Lib::Fn3->test_lc);
}

# index
{
  ok(SPVM::TestCase::Lib::Fn3->test_index);
}

# rindex
{
  ok(SPVM::TestCase::Lib::Fn3->test_rindex);
}

# join
{
  ok(SPVM::TestCase::Lib::Fn3->test_join);
}

# copy_string
{
  # copy_string
  ok(SPVM::TestCase::Lib::Fn3->test_copy_string);
}


# Copy
{
  # copy_array_byte
  ok(SPVM::TestCase::Lib::Fn2->test_copy_array_byte);

  # copy_array_short
  ok(SPVM::TestCase::Lib::Fn2->test_copy_array_short);

  # copy_array_int
  ok(SPVM::TestCase::Lib::Fn2->test_copy_array_int);

  # copy_array_long
  ok(SPVM::TestCase::Lib::Fn2->test_copy_array_long);

  # copy_array_float
  ok(SPVM::TestCase::Lib::Fn2->test_copy_array_float);

  # copy_array_double
  ok(SPVM::TestCase::Lib::Fn2->test_copy_array_double);

  # copy_array_string
  ok(SPVM::TestCase::Lib::Fn2->test_copy_array_string);
  
  # copy_array_object
  ok(SPVM::TestCase::Lib::Fn2->test_copy_array_object);
}

# copy_array_range
{
  # copy_array_range_byte
  ok(SPVM::TestCase::Lib::Fn2->test_copy_array_range_byte);

  # copy_array_range_short
  ok(SPVM::TestCase::Lib::Fn2->test_copy_array_range_short);

  # copy_array_range_int
  ok(SPVM::TestCase::Lib::Fn2->test_copy_array_range_int);

  # copy_array_range_long
  ok(SPVM::TestCase::Lib::Fn2->test_copy_array_range_long);

  # copy_array_range_float
  ok(SPVM::TestCase::Lib::Fn2->test_copy_array_range_float);

  # copy_array_range_double
  ok(SPVM::TestCase::Lib::Fn2->test_copy_array_range_double);

  # copy_array_range_double
  ok(SPVM::TestCase::Lib::Fn2->test_copy_array_range_string);

  # copy_array_range_double
  ok(SPVM::TestCase::Lib::Fn2->test_copy_array_range_object);
}

# dump array
{
  # dump_array_object
  ok(SPVM::TestCase::Lib::Fn3->test_dump_array_byte);
  ok(SPVM::TestCase::Lib::Fn3->test_dump_array_short);
  ok(SPVM::TestCase::Lib::Fn3->test_dump_array_int);
  ok(SPVM::TestCase::Lib::Fn3->test_dump_array_long);
  ok(SPVM::TestCase::Lib::Fn3->test_dump_array_float);
  ok(SPVM::TestCase::Lib::Fn3->test_dump_array_double);
  ok(SPVM::TestCase::Lib::Fn3->test_dump_unsigned_array_byte);
  ok(SPVM::TestCase::Lib::Fn3->test_dump_unsigned_array_short);
  ok(SPVM::TestCase::Lib::Fn3->test_dump_unsigned_array_int);
  ok(SPVM::TestCase::Lib::Fn3->test_dump_unsigned_array_long);
  ok(SPVM::TestCase::Lib::Fn3->test_dump_array_string);
  ok(SPVM::TestCase::Lib::Fn3->test_dump_array_object);
}

# equals
{
  # equals_array_byte
  ok(SPVM::TestCase::Lib::Fn2->test_equals_array_byte);

  # equals_array_short
  ok(SPVM::TestCase::Lib::Fn2->test_equals_array_short);

  # equals_array_int
  ok(SPVM::TestCase::Lib::Fn2->test_equals_array_int);

  # equeals_array_long
  ok(SPVM::TestCase::Lib::Fn2->test_equals_array_long);

  # equals_array_float
  ok(SPVM::TestCase::Lib::Fn2->test_equals_array_float);

  # equals_array_double
  ok(SPVM::TestCase::Lib::Fn2->test_equals_array_double);

  # equals_array_string
  ok(SPVM::TestCase::Lib::Fn2->test_equals_array_string);

  # equals_array_object
  ok(SPVM::TestCase::Lib::Fn2->test_equals_array_object);
}

# memcpy
{
  ok(SPVM::TestCase::Lib::Fn2->test_memcpy_byte);
  ok(SPVM::TestCase::Lib::Fn2->test_memcpy_short);
  ok(SPVM::TestCase::Lib::Fn2->test_memcpy_int);
  ok(SPVM::TestCase::Lib::Fn2->test_memcpy_long);
  ok(SPVM::TestCase::Lib::Fn2->test_memcpy_float);
  ok(SPVM::TestCase::Lib::Fn2->test_memcpy_double);
}

# memmove
{
  ok(SPVM::TestCase::Lib::Fn2->test_memmove_byte);
  ok(SPVM::TestCase::Lib::Fn2->test_memmove_short);
  ok(SPVM::TestCase::Lib::Fn2->test_memmove_int);
  ok(SPVM::TestCase::Lib::Fn2->test_memmove_long);
  ok(SPVM::TestCase::Lib::Fn2->test_memmove_float);
  ok(SPVM::TestCase::Lib::Fn2->test_memmove_double);
}

# new_array_proto
{
  # copy_array_range_byte
  ok(SPVM::TestCase::Lib::Fn2->test_new_array_proto);
}

# sort
{
  ok(SPVM::TestCase::Lib::Fn1->sort_byte);
  ok(SPVM::TestCase::Lib::Fn1->sort_short);
  ok(SPVM::TestCase::Lib::Fn1->sort_int);
  ok(SPVM::TestCase::Lib::Fn1->sort_long);
  ok(SPVM::TestCase::Lib::Fn1->sort_float);
  ok(SPVM::TestCase::Lib::Fn1->sort_double);
  ok(SPVM::TestCase::Lib::Fn1->sort_string);
  ok(SPVM::TestCase::Lib::Fn1->sort_object);
}

# is_array
{
  ok(SPVM::TestCase::Lib::Fn3->is_array);
}

# is_numeric_array
{
  ok(SPVM::TestCase::Lib::Fn3->is_numeric_array);
}

# is_mulnum_array
{
  ok(SPVM::TestCase::Lib::Fn3->is_mulnum_array);
}

# chomp
{
  ok(SPVM::TestCase::Lib::Fn3->chomp);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
