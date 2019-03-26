use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::HTTP::Cookies';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# SPVM::HTTP::Cookies
{
  ok(TestCase::Lib::SPVM::HTTP::Cookies->test_all_through);
  ok(TestCase::Lib::SPVM::HTTP::Cookies->test_extend_capacity);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
