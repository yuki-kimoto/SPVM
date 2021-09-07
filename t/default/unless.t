use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::Unless';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Array
{
  ok(SPVM::TestCase::Unless->unless_ok);
  ok(SPVM::TestCase::Unless->unless_not_ok);
  ok(SPVM::TestCase::Unless->unless_else);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
