use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::Time::Moment';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# SPVM::Time::Moment
{
  ok(TestCase::Lib::SPVM::Time::Moment->test_basic());
  ok(TestCase::Lib::SPVM::Time::Moment->test_leap_year());
  ok(TestCase::Lib::SPVM::Time::Moment->test_now());
}


# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
