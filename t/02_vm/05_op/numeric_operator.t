use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::NumericOperator';



# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# Plus
{
  ok(SPVM::TestCase::Operator::NumericOperator->plus());
}

# Negate
{
  ok(SPVM::TestCase::Operator::NumericOperator->negate());
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);


done_testing;
