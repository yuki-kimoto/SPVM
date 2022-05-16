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
  ok(SPVM::TestCase::Lib::Fn3->crand);
}

# rand
{
  ok(SPVM::TestCase::Lib::Fn3->rand);
}

# RAND_MAX
{
  ok(SPVM::TestCase::Lib::Fn3->RAND_MAX);
}

# Copy
{
  # copy_string
  ok(SPVM::TestCase::Lib::Fn3->copy_str);
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
  ok(SPVM::TestCase::Lib::Fn3->byte_constant);
  ok(SPVM::TestCase::Lib::Fn3->short_constant);
  ok(SPVM::TestCase::Lib::Fn3->int_constant);
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
  ok(SPVM::TestCase::Lib::Fn3->hex);
}

# trim_ascii_space
{
  ok(SPVM::TestCase::Lib::Fn3->trim_ascii_space);
}

# split
{
  ok(SPVM::TestCase::Lib::Fn3->split);
}

# abs
{
  ok(SPVM::TestCase::Lib::Fn3->abs);
}

# labs
{
  ok(SPVM::TestCase::Lib::Fn3->labs);
}

# sprintf
{
  ok(SPVM::TestCase::Lib::Fn1->sprintf_d);
  ok(SPVM::TestCase::Lib::Fn1->sprintf_u);
  ok(SPVM::TestCase::Lib::Fn1->sprintf_ld);
  ok(SPVM::TestCase::Lib::Fn1->sprintf_lu);
  ok(SPVM::TestCase::Lib::Fn1->sprintf_f);
  ok(SPVM::TestCase::Lib::Fn1->sprintf_c);
  ok(SPVM::TestCase::Lib::Fn1->sprintf_s);
  ok(SPVM::TestCase::Lib::Fn1->sprintf_U);
  ok(SPVM::TestCase::Lib::Fn1->sprintf_percent);
  ok(SPVM::TestCase::Lib::Fn1->sprintf_x);
  ok(SPVM::TestCase::Lib::Fn1->sprintf_X);
  ok(SPVM::TestCase::Lib::Fn1->sprintf_all);
}

# to_int_with_base
{
  ok(SPVM::TestCase::Lib::Fn3->to_int);
  ok(SPVM::TestCase::Lib::Fn3->to_int_with_base);
  ok(SPVM::TestCase::Lib::Fn3->to_long);
  ok(SPVM::TestCase::Lib::Fn3->to_long_with_base);
  ok(SPVM::TestCase::Lib::Fn3->to_float);
  ok(SPVM::TestCase::Lib::Fn3->to_double);
}
# chompr
{
  ok(SPVM::TestCase::Lib::Fn3->chompr);
}
# is_alnum
{
  ok(SPVM::TestCase::Lib::Fn3->is_alnum);
}

# is_alpha
{
  ok(SPVM::TestCase::Lib::Fn3->is_alpha);
}

# is_alpha
{
  ok(SPVM::TestCase::Lib::Fn3->is_blank);
}

# is_cntrl
{
  ok(SPVM::TestCase::Lib::Fn3->is_cntrl);
}

# is_digit
{
  ok(SPVM::TestCase::Lib::Fn3->is_digit);
}

# is_graph
{
  ok(SPVM::TestCase::Lib::Fn3->is_graph);
}

# is_lower
{
  ok(SPVM::TestCase::Lib::Fn3->is_lower);
}

# is_print
{
  ok(SPVM::TestCase::Lib::Fn3->is_print);
}

# is_print
{
  ok(SPVM::TestCase::Lib::Fn3->is_print);
}

# is_punct
{
  ok(SPVM::TestCase::Lib::Fn3->is_punct);
}

# is_space
{
  ok(SPVM::TestCase::Lib::Fn3->is_space);
}

# is_upper
{
  ok(SPVM::TestCase::Lib::Fn3->is_upper);
}

# is_xdigit
{
  ok(SPVM::TestCase::Lib::Fn3->is_xdigit);
}

# to_lower
{
  ok(SPVM::TestCase::Lib::Fn3->to_lower);
}

# to_upper
{
  ok(SPVM::TestCase::Lib::Fn3->to_upper);
}

# is_perl_space
{
  ok(SPVM::TestCase::Lib::Fn3->is_perl_space);
}

# is_perl_word
{
  ok(SPVM::TestCase::Lib::Fn3->is_perl_word);
}
# uc
{
  ok(SPVM::TestCase::Lib::Fn3->uc);
}

# lcfirst
{
  ok(SPVM::TestCase::Lib::Fn3->lcfirst);
}

# lc
{
  ok(SPVM::TestCase::Lib::Fn3->lc);
}

# index
{
  ok(SPVM::TestCase::Lib::Fn3->index);
}

# rindex
{
  ok(SPVM::TestCase::Lib::Fn3->rindex);
}

# join
{
  ok(SPVM::TestCase::Lib::Fn3->join);
}

# copy_string
{
  # copy_string
  ok(SPVM::TestCase::Lib::Fn3->copy_string);
}


# Copy
{
  # copy_array_byte
  ok(SPVM::TestCase::Lib::Fn2->copy_array_byte);

  # copy_array_short
  ok(SPVM::TestCase::Lib::Fn2->copy_array_short);

  # copy_array_int
  ok(SPVM::TestCase::Lib::Fn2->copy_array_int);

  # copy_array_long
  ok(SPVM::TestCase::Lib::Fn2->copy_array_long);

  # copy_array_float
  ok(SPVM::TestCase::Lib::Fn2->copy_array_float);

  # copy_array_double
  ok(SPVM::TestCase::Lib::Fn2->copy_array_double);

  # copy_array_string
  ok(SPVM::TestCase::Lib::Fn2->copy_array_string);
  
  # copy_array_object
  ok(SPVM::TestCase::Lib::Fn2->copy_array_object);
}

# copy_array_range
{
  # copy_array_range_byte
  ok(SPVM::TestCase::Lib::Fn2->copy_array_range_byte);

  # copy_array_range_short
  ok(SPVM::TestCase::Lib::Fn2->copy_array_range_short);

  # copy_array_range_int
  ok(SPVM::TestCase::Lib::Fn2->copy_array_range_int);

  # copy_array_range_long
  ok(SPVM::TestCase::Lib::Fn2->copy_array_range_long);

  # copy_array_range_float
  ok(SPVM::TestCase::Lib::Fn2->copy_array_range_float);

  # copy_array_range_double
  ok(SPVM::TestCase::Lib::Fn2->copy_array_range_double);

  # copy_array_range_double
  ok(SPVM::TestCase::Lib::Fn2->copy_array_range_string);

  # copy_array_range_double
  ok(SPVM::TestCase::Lib::Fn2->copy_array_range_object);
}

# dump array
{
  # dump_array_object
  ok(SPVM::TestCase::Lib::Fn3->dump_array_byte);
  ok(SPVM::TestCase::Lib::Fn3->dump_array_short);
  ok(SPVM::TestCase::Lib::Fn3->dump_array_int);
  ok(SPVM::TestCase::Lib::Fn3->dump_array_long);
  ok(SPVM::TestCase::Lib::Fn3->dump_array_float);
  ok(SPVM::TestCase::Lib::Fn3->dump_array_double);
  ok(SPVM::TestCase::Lib::Fn3->dump_unsigned_array_byte);
  ok(SPVM::TestCase::Lib::Fn3->dump_unsigned_array_short);
  ok(SPVM::TestCase::Lib::Fn3->dump_unsigned_array_int);
  ok(SPVM::TestCase::Lib::Fn3->dump_unsigned_array_long);
  ok(SPVM::TestCase::Lib::Fn3->dump_array_string);
  ok(SPVM::TestCase::Lib::Fn3->dump_array_object);
}

# equals
{
  # equals_array_byte
  ok(SPVM::TestCase::Lib::Fn2->equals_array_byte);

  # equals_array_short
  ok(SPVM::TestCase::Lib::Fn2->equals_array_short);

  # equals_array_int
  ok(SPVM::TestCase::Lib::Fn2->equals_array_int);

  # equeals_array_long
  ok(SPVM::TestCase::Lib::Fn2->equals_array_long);

  # equals_array_float
  ok(SPVM::TestCase::Lib::Fn2->equals_array_float);

  # equals_array_double
  ok(SPVM::TestCase::Lib::Fn2->equals_array_double);

  # equals_array_string
  ok(SPVM::TestCase::Lib::Fn2->equals_array_string);

  # equals_array_object
  ok(SPVM::TestCase::Lib::Fn2->equals_array_object);
}

# memcpy_numeric
{
  ok(SPVM::TestCase::Lib::Fn2->memcpy_byte);
  ok(SPVM::TestCase::Lib::Fn2->memcpy_short);
  ok(SPVM::TestCase::Lib::Fn2->memcpy_int);
  ok(SPVM::TestCase::Lib::Fn2->memcpy_long);
  ok(SPVM::TestCase::Lib::Fn2->memcpy_float);
  ok(SPVM::TestCase::Lib::Fn2->memcpy_double);
}

# memmove_numeric
{
  ok(SPVM::TestCase::Lib::Fn2->memmove_byte);
  ok(SPVM::TestCase::Lib::Fn2->memmove_short);
  ok(SPVM::TestCase::Lib::Fn2->memmove_int);
  ok(SPVM::TestCase::Lib::Fn2->memmove_long);
  ok(SPVM::TestCase::Lib::Fn2->memmove_float);
  ok(SPVM::TestCase::Lib::Fn2->memmove_double);
}

# new_array_proto
{
  # copy_array_range_byte
  ok(SPVM::TestCase::Lib::Fn2->new_array_proto);
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

# is_object_array
{
  ok(SPVM::TestCase::Lib::Fn3->is_object_array);
}

# chomp
{
  ok(SPVM::TestCase::Lib::Fn3->chomp);
}

# memcpy
{
  ok(SPVM::TestCase::Lib::Fn3->memcpy);
}

# memmove
{
  ok(SPVM::TestCase::Lib::Fn3->memmove);
}

# index_len
{
  ok(SPVM::TestCase::Lib::Fn3->index_len);
}

# rindex_len
{
  ok(SPVM::TestCase::Lib::Fn3->rindex_len);
}

# chr
{
  ok(SPVM::TestCase::Lib::Fn1->chr);
}

# ord
{
  ok(SPVM::TestCase::Lib::Fn1->ord);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
