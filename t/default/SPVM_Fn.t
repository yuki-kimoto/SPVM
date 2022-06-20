use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

# SPVM::Fn tests is separated multiple files(smaller than 50KB)
# The reason is gcc can't compile the precompile code for the insufficient memory
# in some environment of CPAN testers.
use SPVM 'TestCase::Lib::Fn';

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
  ok(SPVM::TestCase::Lib::Fn->crand);
}

# rand
{
  ok(SPVM::TestCase::Lib::Fn->rand);
}

# RAND_MAX
{
  ok(SPVM::TestCase::Lib::Fn->RAND_MAX);
}

# Copy
{
  # copy_string
  ok(SPVM::TestCase::Lib::Fn->copy_str);
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
  ok(SPVM::TestCase::Lib::Fn->byte_constant);
  ok(SPVM::TestCase::Lib::Fn->short_constant);
  ok(SPVM::TestCase::Lib::Fn->int_constant);
  ok(SPVM::TestCase::Lib::Fn->spvm_like_constants);
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
  ok(SPVM::TestCase::Lib::Fn->hex);
}

# trim_ascii_space
{
  ok(SPVM::TestCase::Lib::Fn->trim_ascii_space);
}

# split
{
  ok(SPVM::TestCase::Lib::Fn->split);
}

# abs
{
  ok(SPVM::TestCase::Lib::Fn->abs);
}

# labs
{
  ok(SPVM::TestCase::Lib::Fn->labs);
}

# to_int_with_base
{
  ok(SPVM::TestCase::Lib::Fn->to_int);
  ok(SPVM::TestCase::Lib::Fn->to_int_with_base);
  ok(SPVM::TestCase::Lib::Fn->to_long);
  ok(SPVM::TestCase::Lib::Fn->to_long_with_base);
  ok(SPVM::TestCase::Lib::Fn->to_float);
  ok(SPVM::TestCase::Lib::Fn->to_double);
}
# chompr
{
  ok(SPVM::TestCase::Lib::Fn->chompr);
}
# is_alnum
{
  ok(SPVM::TestCase::Lib::Fn->is_alnum);
}

# is_alpha
{
  ok(SPVM::TestCase::Lib::Fn->is_alpha);
}

# is_alpha
{
  ok(SPVM::TestCase::Lib::Fn->is_blank);
}

# is_cntrl
{
  ok(SPVM::TestCase::Lib::Fn->is_cntrl);
}

# is_digit
{
  ok(SPVM::TestCase::Lib::Fn->is_digit);
}

# is_graph
{
  ok(SPVM::TestCase::Lib::Fn->is_graph);
}

# is_lower
{
  ok(SPVM::TestCase::Lib::Fn->is_lower);
}

# is_print
{
  ok(SPVM::TestCase::Lib::Fn->is_print);
}

# is_print
{
  ok(SPVM::TestCase::Lib::Fn->is_print);
}

# is_punct
{
  ok(SPVM::TestCase::Lib::Fn->is_punct);
}

# is_space
{
  ok(SPVM::TestCase::Lib::Fn->is_space);
}

# is_upper
{
  ok(SPVM::TestCase::Lib::Fn->is_upper);
}

# is_xdigit
{
  ok(SPVM::TestCase::Lib::Fn->is_xdigit);
}

# to_lower
{
  ok(SPVM::TestCase::Lib::Fn->to_lower);
}

# to_upper
{
  ok(SPVM::TestCase::Lib::Fn->to_upper);
}

# is_perl_space
{
  ok(SPVM::TestCase::Lib::Fn->is_perl_space);
}

# is_perl_word
{
  ok(SPVM::TestCase::Lib::Fn->is_perl_word);
}
# uc
{
  ok(SPVM::TestCase::Lib::Fn->uc);
}

# lcfirst
{
  ok(SPVM::TestCase::Lib::Fn->lcfirst);
}

# lc
{
  ok(SPVM::TestCase::Lib::Fn->lc);
}

# index
{
  ok(SPVM::TestCase::Lib::Fn->index);
}

# contains
{
  ok(SPVM::TestCase::Lib::Fn->contains);
}

# rindex
{
  ok(SPVM::TestCase::Lib::Fn->rindex);
}

# join
{
  ok(SPVM::TestCase::Lib::Fn->join);
}

# copy_string
{
  # copy_string
  ok(SPVM::TestCase::Lib::Fn->copy_string);
}

# is_array
{
  ok(SPVM::TestCase::Lib::Fn->is_array);
}

# is_numeric_array
{
  ok(SPVM::TestCase::Lib::Fn->is_numeric_array);
}

# is_mulnum_array
{
  ok(SPVM::TestCase::Lib::Fn->is_mulnum_array);
}

# is_object_array
{
  ok(SPVM::TestCase::Lib::Fn->is_object_array);
}

# chomp
{
  ok(SPVM::TestCase::Lib::Fn->chomp);
}

# memcpy
{
  ok(SPVM::TestCase::Lib::Fn->memcpy);
}

# memmove
{
  ok(SPVM::TestCase::Lib::Fn->memmove);
}

# index_len
{
  ok(SPVM::TestCase::Lib::Fn->index_len);
}

# rindex_len
{
  ok(SPVM::TestCase::Lib::Fn->rindex_len);
}

# chr
{
  ok(SPVM::TestCase::Lib::Fn->chr);
}

# ord
{
  ok(SPVM::TestCase::Lib::Fn->ord);
}

# repeat
{
  ok(SPVM::TestCase::Lib::Fn->repeat);
}

# is_hex_digit
{
  ok(SPVM::TestCase::Lib::Fn->is_hex_digit);
}

# get_next_code_point
{
  ok(SPVM::TestCase::Lib::Fn->get_next_code_point);
}

# look_next_code_point
{
  ok(SPVM::TestCase::Lib::Fn->get_next_code_point);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
