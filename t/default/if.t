use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::If';

UNITCHECK { SPVM::init() }

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# while
{
  ok(TestCase::If->if_bool());
  ok(TestCase::If->if_true());
  ok(TestCase::If->if_false());
  ok(TestCase::If->elsif_match());
  ok(TestCase::If->else_match());
  ok(TestCase::If->condition_my());
}


# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
