use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use utf8;

use Test::More;

use SPVM 'TestCase::Operator::ComparisonOperator';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count();

# Spec tests
{
  # a > b
  {
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt);
  }

  # a >= b
  {
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge);
  }

  # a < b
  {
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt);
  }

  # a <= b
  {
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le);
  }

  # a == b
  {
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_eq);
  }

  # a != b
  {
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ne);
  }

  # a <=> b
  {
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_cmp);
  }

  # String comparison operator
  {
    {
      ok(SPVM::TestCase::Operator::ComparisonOperator->string_eq);
      ok(SPVM::TestCase::Operator::ComparisonOperator->string_ne);
      ok(SPVM::TestCase::Operator::ComparisonOperator->string_gt);
      ok(SPVM::TestCase::Operator::ComparisonOperator->string_ge);
      ok(SPVM::TestCase::Operator::ComparisonOperator->string_lt);
      ok(SPVM::TestCase::Operator::ComparisonOperator->string_le);
      ok(SPVM::TestCase::Operator::ComparisonOperator->string_cmp);
    }
  }
}

# All object is freed
$api->set_exception(undef);
my $end_memory_blocks_count = $api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
