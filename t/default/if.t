use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::If';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# while
{
  ok(SPVM::TestCase::If->if_bool());
  ok(SPVM::TestCase::If->if_true());
  ok(SPVM::TestCase::If->if_false());
  ok(SPVM::TestCase::If->elsif_match());
  ok(SPVM::TestCase::If->else_match());
  ok(SPVM::TestCase::If->condition_my());
}


# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
