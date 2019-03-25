use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::Time::Format';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# SPVM::Time::Format
{
  ok(TestCase::Lib::SPVM::Time::Format->test_parse());
  ok(TestCase::Lib::SPVM::Time::Format->test_timezone_JST());
}


# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
