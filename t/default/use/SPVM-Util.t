use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM::Util;

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

{
  my $strs = SPVM::Util->split(",", "aaa,bbb,ccc")->to_elems;
  is_deeply($strs, ['aaa', 'bbb', 'ccc']);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
