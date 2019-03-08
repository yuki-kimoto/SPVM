use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Socket';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Socket
{
  ok(TestCase::Socket->basic);
}


# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
