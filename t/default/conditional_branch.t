use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::ConditionalBranch';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Conditinal Branch - if, elsif, else, unless
{
  ok(SPVM::TestCase::ConditionalBranch->if_bool());
  ok(SPVM::TestCase::ConditionalBranch->if_true());
  ok(SPVM::TestCase::ConditionalBranch->if_false());
  ok(SPVM::TestCase::ConditionalBranch->elsif_match());
  ok(SPVM::TestCase::ConditionalBranch->else_match());
  ok(SPVM::TestCase::ConditionalBranch->condition_my());
  ok(SPVM::TestCase::ConditionalBranch->unless_ok);
  ok(SPVM::TestCase::ConditionalBranch->unless_not_ok);
  ok(SPVM::TestCase::ConditionalBranch->unless_else);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
