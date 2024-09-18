use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::Subtract';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count();

# Spec tests
{
  # Subtract - Operation
  {
    ok(SPVM::TestCase::Operator::Subtract->subtract_byte_byte);
    ok(SPVM::TestCase::Operator::Subtract->subtract_short_short);
    ok(SPVM::TestCase::Operator::Subtract->subtract_int_byte);
    ok(SPVM::TestCase::Operator::Subtract->subtract_int_short);
    ok(SPVM::TestCase::Operator::Subtract->subtract_byte_int);
    ok(SPVM::TestCase::Operator::Subtract->subtract_short_int);
    ok(SPVM::TestCase::Operator::Subtract->subtract_int_int);
    ok(SPVM::TestCase::Operator::Subtract->subtract_long_long);
    ok(SPVM::TestCase::Operator::Subtract->subtract_int_float);
    ok(SPVM::TestCase::Operator::Subtract->subtract_int_double);
    ok(SPVM::TestCase::Operator::Subtract->subtract_minus);
    ok(SPVM::TestCase::Operator::Subtract->subtract_zero_minus);
    ok(SPVM::TestCase::Operator::Subtract->subtract_float_float);
    ok(SPVM::TestCase::Operator::Subtract->subtract_double_double);
    ok(SPVM::TestCase::Operator::Subtract->subtract_double_double_big);
  }
}

# Optional tests
{
  ok(SPVM::TestCase::Operator::Subtract->subtract());

  is(SPVM::TestCase::Operator::Subtract->subtract_int_max(), 2147483646);
  is(SPVM::TestCase::Operator::Subtract->subtract_int_min(), -2147483648);
  is(SPVM::TestCase::Operator::Subtract->subtract_int_underflow(), 2147483647);
  is(SPVM::TestCase::Operator::Subtract->subtract_long_max(), 9223372036854775806);
  is(SPVM::TestCase::Operator::Subtract->subtract_long_min(), -9223372036854775808);
}

# All object is freed
$api->set_exception(undef);
my $end_memory_blocks_count = $api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);


done_testing;
