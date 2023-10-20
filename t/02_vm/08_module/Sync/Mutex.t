use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Sync::Mutex';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# SPVM::Byte
{
  ok(SPVM::TestCase::Module::Sync::Mutex->basic);
  
  ok(SPVM::TestCase::Module::Sync::Mutex->thread);
  
  ok(SPVM::TestCase::Module::Sync::Mutex->increment);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
