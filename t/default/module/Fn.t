use lib "t/testlib";
use TestAuto;
use TestFile;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Fn';

use SPVM 'Fn';

use POSIX();

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

# Note: Positive infinity(unix like system : inf, Windows : 1.#INF)
my $POSITIVE_INFINITY = 9**9**9;
my $NaN = 9**9**9 / 9**9**9;
my $nan_re = qr/(nan|ind)/i;

# Fn
{
  ok(SPVM::TestCase::Module::Fn->byte_constant);
  ok(SPVM::TestCase::Module::Fn->short_constant);
  ok(SPVM::TestCase::Module::Fn->int_constant);
  ok(SPVM::TestCase::Module::Fn->spvm_like_constants);
  is(SPVM::Fn->DBL_MAX, POSIX::DBL_MAX);
  is(SPVM::Fn->DBL_MIN, POSIX::DBL_MIN);
  is(SPVM::Fn->FLT_MAX, POSIX::FLT_MAX);
  like(SPVM::Fn->FLT_MAX(), qr/[0-9]/);
  is(SPVM::Fn->FLT_MIN, POSIX::FLT_MIN);
  like(SPVM::Fn->FLT_MIN(), qr/[0-9]/);
  is(SPVM::Fn->INT16_MAX, $SHORT_MAX);
  is(SPVM::Fn->INT16_MAX, 32767);
  is(SPVM::Fn->INT16_MIN, $SHORT_MIN);
  is(SPVM::Fn->INT16_MIN, -32768);
  is(SPVM::Fn->INT32_MAX, $INT_MAX);
  is(SPVM::Fn->INT32_MAX, 2147483647);
  is(SPVM::Fn->INT32_MIN, $INT_MIN);
  is(SPVM::Fn->INT32_MIN, -2147483648);
  is(SPVM::Fn->INT64_MAX, $LONG_MAX);
  is(SPVM::Fn->INT64_MAX, 9223372036854775807);
  is(SPVM::Fn->INT64_MIN, $LONG_MIN);
  is(SPVM::Fn->INT64_MIN, -9223372036854775808);
  is(SPVM::Fn->INT8_MAX, $BYTE_MAX);
  is(SPVM::Fn->INT8_MAX, 127);
  is(SPVM::Fn->INT8_MIN, $BYTE_MIN);
  is(SPVM::Fn->INT8_MIN, -128);
  ok(SPVM::TestCase::Module::Fn->RAND_MAX);
  is(SPVM::Fn->UINT16_MAX, -1);
  is(SPVM::Fn->UINT32_MAX, -1);
  is(SPVM::Fn->UINT64_MAX, -1);
  is(SPVM::Fn->UINT8_MAX, -1);
  ok(SPVM::TestCase::Module::Fn->abs);
  ok(SPVM::TestCase::Module::Fn->chomp);
  ok(SPVM::TestCase::Module::Fn->chompr);
  ok(SPVM::TestCase::Module::Fn->chr);
  ok(SPVM::TestCase::Module::Fn->contains);
  ok(SPVM::TestCase::Module::Fn->copy_str);
  ok(SPVM::TestCase::Module::Fn->copy_string);
  ok(SPVM::TestCase::Module::Fn->crand);
  ok(SPVM::TestCase::Module::Fn->get_next_code_point);
  ok(SPVM::TestCase::Module::Fn->hex);
  ok(SPVM::TestCase::Module::Fn->index);
  ok(SPVM::TestCase::Module::Fn->index_len);
  ok(SPVM::TestCase::Module::Fn->is_alnum);
  ok(SPVM::TestCase::Module::Fn->is_alpha);
  ok(SPVM::TestCase::Module::Fn->is_array);
  ok(SPVM::TestCase::Module::Fn->is_blank);
  ok(SPVM::TestCase::Module::Fn->is_cntrl);
  ok(SPVM::TestCase::Module::Fn->is_digit);
  ok(SPVM::TestCase::Module::Fn->is_graph);
  ok(SPVM::TestCase::Module::Fn->is_hex_digit);
  ok(SPVM::TestCase::Module::Fn->is_lower);
  ok(SPVM::TestCase::Module::Fn->is_mulnum_array);
  ok(SPVM::TestCase::Module::Fn->is_numeric_array);
  ok(SPVM::TestCase::Module::Fn->is_object_array);
  ok(SPVM::TestCase::Module::Fn->is_perl_space);
  ok(SPVM::TestCase::Module::Fn->is_perl_word);
  ok(SPVM::TestCase::Module::Fn->is_print);
  ok(SPVM::TestCase::Module::Fn->is_print);
  ok(SPVM::TestCase::Module::Fn->is_punct);
  ok(SPVM::TestCase::Module::Fn->is_space);
  ok(SPVM::TestCase::Module::Fn->is_upper);
  ok(SPVM::TestCase::Module::Fn->is_xdigit);
  ok(SPVM::TestCase::Module::Fn->join);
  ok(SPVM::TestCase::Module::Fn->labs);
  ok(SPVM::TestCase::Module::Fn->lc);
  ok(SPVM::TestCase::Module::Fn->lcfirst);
  ok(SPVM::TestCase::Module::Fn->memcpy);
  ok(SPVM::TestCase::Module::Fn->memmove);
  ok(SPVM::TestCase::Module::Fn->ord);
  ok(SPVM::TestCase::Module::Fn->rand);
  ok(SPVM::TestCase::Module::Fn->repeat);
  ok(SPVM::TestCase::Module::Fn->rindex);
  ok(SPVM::TestCase::Module::Fn->rindex_len);
  ok(SPVM::TestCase::Module::Fn->split);
  ok(SPVM::TestCase::Module::Fn->to_double);
  ok(SPVM::TestCase::Module::Fn->to_float);
  ok(SPVM::TestCase::Module::Fn->to_int);
  ok(SPVM::TestCase::Module::Fn->to_int_with_base);
  ok(SPVM::TestCase::Module::Fn->to_long);
  ok(SPVM::TestCase::Module::Fn->to_long_with_base);
  ok(SPVM::TestCase::Module::Fn->to_lower);
  ok(SPVM::TestCase::Module::Fn->to_upper);
  ok(SPVM::TestCase::Module::Fn->trim_ascii_space);
  ok(SPVM::TestCase::Module::Fn->uc);}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
