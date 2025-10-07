use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use utf8;

use Test::More;

use SPVM 'TestCase::Operator::ConditionEvaluation';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Spec tests
{
  # Condition evaluation
  {
    ok(SPVM::TestCase::Operator::ConditionEvaluation->basic);
    
    ok(SPVM::TestCase::Operator::ConditionEvaluation->else);
    ok(SPVM::TestCase::Operator::ConditionEvaluation->elsif);
    ok(SPVM::TestCase::Operator::ConditionEvaluation->elsif2);
    ok(SPVM::TestCase::Operator::ConditionEvaluation->duplicate);
  }
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
