use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::Divide';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Spec tests
{
  # Division operator
  {
    ok(SPVM::TestCase::Operator::Divide->divide_byte_byte);
    ok(SPVM::TestCase::Operator::Divide->divide_short_short);
    ok(SPVM::TestCase::Operator::Divide->divide_int_byte);
    ok(SPVM::TestCase::Operator::Divide->divide_int_short);
    ok(SPVM::TestCase::Operator::Divide->divide_byte_int);
    ok(SPVM::TestCase::Operator::Divide->divide_short_int);
    ok(SPVM::TestCase::Operator::Divide->divide_int_int);
    ok(SPVM::TestCase::Operator::Divide->divide_long_long);
    ok(SPVM::TestCase::Operator::Divide->divide_int_float);
    ok(SPVM::TestCase::Operator::Divide->divide_int_double);
    ok(SPVM::TestCase::Operator::Divide->divide_float_float);
    ok(SPVM::TestCase::Operator::Divide->divide_double_double);
    ok(SPVM::TestCase::Operator::Divide->divide_double_double_big);
  }

  # Divide Unsinged operator
  {
    ok(SPVM::TestCase::Operator::Divide->divide_unsigned_int);
    ok(SPVM::TestCase::Operator::Divide->divide_unsigned_long);
  }
}

# Optional tests
{
  ok(SPVM::TestCase::Operator::Divide->divide());
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
