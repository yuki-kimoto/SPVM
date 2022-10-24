use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::LogicalOperator';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Spec tests
{
  # logical operator - combination
  {
    ok(SPVM::TestCase::LogicalOperator->logical_operator_combination);
  }

  # logical not
  {
    ok(SPVM::TestCase::LogicalOperator->logical_not_operator);
    ok(SPVM::TestCase::LogicalOperator->logical_not_false());
  }

  # logical or
  {
    ok(SPVM::TestCase::LogicalOperator->logical_or_operator);
    ok(SPVM::TestCase::LogicalOperator->logical_or_both_true());
    ok(SPVM::TestCase::LogicalOperator->logical_or_left_true());
    ok(SPVM::TestCase::LogicalOperator->logical_or_right_true());
    ok(SPVM::TestCase::LogicalOperator->logical_or_both_false());
  }

  # logical and
  {
    ok(SPVM::TestCase::LogicalOperator->logical_and_operator);
    ok(SPVM::TestCase::LogicalOperator->logical_and_both_true());
    ok(SPVM::TestCase::LogicalOperator->logical_and_left_true());
    ok(SPVM::TestCase::LogicalOperator->logical_and_right_true());
    ok(SPVM::TestCase::LogicalOperator->logical_and_both_false());
    ok(SPVM::TestCase::LogicalOperator->logical_and_push_mortal_leave_scope);
    ok(SPVM::TestCase::LogicalOperator->logical_and_nagate);
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
