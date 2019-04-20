use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::HTTP::Client';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# SPVM::HTTP::Client
{
  ok(TestCase::Lib::SPVM::HTTP::Client->test_get());
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
