use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Statement::If';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Conditional Branch
#   if Statement
#   elsif Statement
#   else Statement
#   unless Statement
{
  ok(SPVM::TestCase::Statement::If->condition_types());
  ok(SPVM::TestCase::Statement::If->condition_true());
  ok(SPVM::TestCase::Statement::If->condition_false());
  ok(SPVM::TestCase::Statement::If->elsif_condition_true());
  ok(SPVM::TestCase::Statement::If->elsif_condition_false());
  ok(SPVM::TestCase::Statement::If->elsif_only());
  ok(SPVM::TestCase::Statement::If->else_only());
  ok(SPVM::TestCase::Statement::If->condition_my());
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
