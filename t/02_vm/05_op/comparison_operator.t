use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use utf8;

use Test::More;

use SPVM 'TestCase::Operator::ComparisonOperator';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Numeric Comparison Operator
{
  ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_eq);
  ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ne);
  ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt);
  ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge);
  ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt);
  ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le);
  ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_cmp);
}

# String comparison operator
{
  ok(SPVM::TestCase::Operator::ComparisonOperator->string_eq);
  ok(SPVM::TestCase::Operator::ComparisonOperator->string_ne);
  ok(SPVM::TestCase::Operator::ComparisonOperator->string_gt);
  ok(SPVM::TestCase::Operator::ComparisonOperator->string_ge);
  ok(SPVM::TestCase::Operator::ComparisonOperator->string_lt);
  ok(SPVM::TestCase::Operator::ComparisonOperator->string_le);
  ok(SPVM::TestCase::Operator::ComparisonOperator->string_cmp);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
