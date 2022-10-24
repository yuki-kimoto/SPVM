use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::NumericOperator';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Remainder
{
  ok(SPVM::TestCase::NumericOperator->remainder());
}

# Plus
{
  ok(SPVM::TestCase::NumericOperator->plus());
}

# Negate
{
  ok(SPVM::TestCase::NumericOperator->negate());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);


done_testing;
