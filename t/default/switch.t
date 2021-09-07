use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::Switch';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Switch
{
  ok(SPVM::TestCase::Switch->switch_return);
  ok(SPVM::TestCase::Switch->switch_nest);
  ok(SPVM::TestCase::Switch->switch_lookup_switch);
  ok(SPVM::TestCase::Switch->switch_table_switch);
  ok(SPVM::TestCase::Switch->switch_constant_byte);
  ok(SPVM::TestCase::Switch->switch_no_default);
}


# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
