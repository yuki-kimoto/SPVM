use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Point';

use SPVM 'TestCase::ModuleContainsMultiClass';

use Devel::Peek;

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Point
{
  ok(SPVM::TestCase::Point->basic);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
