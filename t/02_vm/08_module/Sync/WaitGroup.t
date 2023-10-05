use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Sync::WaitGroup';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# Sync::WaitGroup
{
  ok(SPVM::TestCase::Module::Sync::WaitGroup->basic);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
