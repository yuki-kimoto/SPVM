use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::Multiply';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Spec tests
{
  # Multiply - Operation
  {
    ok(SPVM::TestCase::Operator::Multiply->multiply_byte_byte);
    ok(SPVM::TestCase::Operator::Multiply->multiply_short_short);
    ok(SPVM::TestCase::Operator::Multiply->multiply_int_byte);
    ok(SPVM::TestCase::Operator::Multiply->multiply_int_short);
    ok(SPVM::TestCase::Operator::Multiply->multiply_byte_int);
    ok(SPVM::TestCase::Operator::Multiply->multiply_short_int);
    ok(SPVM::TestCase::Operator::Multiply->multiply_int_int);
    ok(SPVM::TestCase::Operator::Multiply->multiply_long_long);
    ok(SPVM::TestCase::Operator::Multiply->multiply_int_float);
    ok(SPVM::TestCase::Operator::Multiply->multiply_int_double);
    ok(SPVM::TestCase::Operator::Multiply->multiply_float_float);
    ok(SPVM::TestCase::Operator::Multiply->multiply_double_double);
    ok(SPVM::TestCase::Operator::Multiply->multiply_double_double_big);
  }
}

# Optional tests
{
  ok(SPVM::TestCase::Operator::Multiply->multiply());

  is(SPVM::TestCase::Operator::Multiply->multiply_int_plus(), 1073741824);
  is(SPVM::TestCase::Operator::Multiply->multiply_int_minus(), -1073741824);
  is(SPVM::TestCase::Operator::Multiply->multiply_int_overflow(), -2147483648);
  is(SPVM::TestCase::Operator::Multiply->multiply_long_plus(), 4611686018427387904);
  is(SPVM::TestCase::Operator::Multiply->multiply_long_minus(), -4611686018427387904);
  is(SPVM::TestCase::Operator::Multiply->multiply_long_overflow(), -9223372036854775808);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);



done_testing;
