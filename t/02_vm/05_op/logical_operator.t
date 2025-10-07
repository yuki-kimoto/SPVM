use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::LogicalOperator';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Spec tests
{
  # logical and
  {
    ok(SPVM::TestCase::Operator::LogicalOperator->logical_and);
    ok(SPVM::TestCase::Operator::LogicalOperator->logical_and_both_true);
    ok(SPVM::TestCase::Operator::LogicalOperator->logical_and_left_true);
    ok(SPVM::TestCase::Operator::LogicalOperator->logical_and_right_true);
    ok(SPVM::TestCase::Operator::LogicalOperator->logical_and_both_false);
    ok(SPVM::TestCase::Operator::LogicalOperator->logical_and_push_mortal_leave_scope);
    ok(SPVM::TestCase::Operator::LogicalOperator->logical_and_nagate);
    ok(SPVM::TestCase::Operator::LogicalOperator->logical_and_assign);
    ok(SPVM::TestCase::Operator::LogicalOperator->logical_and_type);
  }
  
  # logical or
  {
    ok(SPVM::TestCase::Operator::LogicalOperator->logical_or);
    ok(SPVM::TestCase::Operator::LogicalOperator->logical_or_both_true);
    ok(SPVM::TestCase::Operator::LogicalOperator->logical_or_left_true);
    ok(SPVM::TestCase::Operator::LogicalOperator->logical_or_right_true);
    ok(SPVM::TestCase::Operator::LogicalOperator->logical_or_both_false);
    ok(SPVM::TestCase::Operator::LogicalOperator->logical_or_assign);
    ok(SPVM::TestCase::Operator::LogicalOperator->logical_or_type);
  }
  
  # logical not
  {
    ok(SPVM::TestCase::Operator::LogicalOperator->logical_not_operator);
    ok(SPVM::TestCase::Operator::LogicalOperator->logical_not_false);
    ok(SPVM::TestCase::Operator::LogicalOperator->logical_not_assign);
  }
  
  # logical operator - combination
  {
    ok(SPVM::TestCase::Operator::LogicalOperator->combination);
  }
  
  # Extra
  {
    ok(SPVM::TestCase::Operator::LogicalOperator->extra);
  }
  
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
