use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::Add';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Spec tests
{
  # Add - Operation
  {
    ok(SPVM::TestCase::Operator::Add->add_byte_byte);
    ok(SPVM::TestCase::Operator::Add->add_short_short);
    ok(SPVM::TestCase::Operator::Add->add_int_byte);
    ok(SPVM::TestCase::Operator::Add->add_int_short);
    ok(SPVM::TestCase::Operator::Add->add_byte_int);
    ok(SPVM::TestCase::Operator::Add->add_short_int);
    ok(SPVM::TestCase::Operator::Add->add_int_int);
    ok(SPVM::TestCase::Operator::Add->add_long_long);
    ok(SPVM::TestCase::Operator::Add->add_int_float);
    ok(SPVM::TestCase::Operator::Add->add_int_double);
    ok(SPVM::TestCase::Operator::Add->add_float_float);
    ok(SPVM::TestCase::Operator::Add->add_double_double);
    ok(SPVM::TestCase::Operator::Add->add_double_double_big);
    ok(SPVM::TestCase::Operator::Add->add_minus);
    ok(SPVM::TestCase::Operator::Add->add_zero_minus);
  }
}

# Optional tests
{
  ok(SPVM::TestCase::Operator::Add->add);
  is(SPVM::TestCase::Operator::Add->add_int_max(), 2147483647);
  is(SPVM::TestCase::Operator::Add->add_int_min(), -2147483647);
  is(SPVM::TestCase::Operator::Add->add_long_max(), 9223372036854775807);
  is(SPVM::TestCase::Operator::Add->add_long_min(), -9223372036854775807);
}

# 2's complement
{
  ok(SPVM::TestCase::Operator::Add->add_int_max_plus_one_2s_complement());
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);



done_testing;
