use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::UnaryPlus';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# Spec tests
{
  # Unary plus - Operation
  {
    ok(SPVM::TestCase::Operator::UnaryPlus->unary_plus_byte);
    ok(SPVM::TestCase::Operator::UnaryPlus->unary_plus_short);
    ok(SPVM::TestCase::Operator::UnaryPlus->unary_plus_int);
    ok(SPVM::TestCase::Operator::UnaryPlus->unary_plus_long);
    ok(SPVM::TestCase::Operator::UnaryPlus->unary_plus_float);
    ok(SPVM::TestCase::Operator::UnaryPlus->unary_plus_double);
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
