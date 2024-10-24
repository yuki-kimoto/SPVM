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
  # Condition evaluation
  {
    ok(SPVM::TestCase::Operator::ComparisonOperator->condition_evaluation);
    
    ok(SPVM::TestCase::Operator::ComparisonOperator->bool_else);
    ok(SPVM::TestCase::Operator::ComparisonOperator->bool_elsif);
    ok(SPVM::TestCase::Operator::ComparisonOperator->bool_elsbool_2);
    ok(SPVM::TestCase::Operator::ComparisonOperator->bool_duplicate);
  }
}

# All object is freed
$api->set_exception(undef);
my $end_memory_blocks_count = $api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
