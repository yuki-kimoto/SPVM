use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Examples';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

{
  # OK if segfault don't occur
  TestCase::Examples->new_only_field_object;
  ok(1);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
