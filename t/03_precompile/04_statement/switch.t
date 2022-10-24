use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Switch';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Switch
{
  ok(SPVM::TestCase::Switch->switch);
  ok(SPVM::TestCase::Switch->switch_extra);
}


# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
