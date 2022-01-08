use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::While';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# while
{
  ok(SPVM::TestCase::While->basic);
  ok(SPVM::TestCase::While->next);
  ok(SPVM::TestCase::While->last);
  ok(SPVM::TestCase::While->condition_my);
  ok(SPVM::TestCase::While->condition_my_var_mem_id);
}


# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
