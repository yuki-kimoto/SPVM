use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::TernaryOperator';

my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

{
  {
    ok(SPVM::TestCase::Operator::TernaryOperator->ternary_op);
  }
  
}

$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
