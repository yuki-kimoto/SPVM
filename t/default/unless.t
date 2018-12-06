use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Unless';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Array
{
  ok(TestCase::Unless->unless_ok);
  ok(TestCase::Unless->unless_not_ok);
  ok(TestCase::Unless->unless_else);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
