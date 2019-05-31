use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Switch';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Switch
{
  ok(TestCase::Switch->switch_nest());
  ok(TestCase::Switch->switch_lookup_switch());
  ok(TestCase::Switch->switch_table_switch());
  ok(TestCase::Switch->switch_constant_byte());
}


# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
