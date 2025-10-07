use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Statement::For';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# for
{
  ok(SPVM::TestCase::Statement::For->basic);
  ok(SPVM::TestCase::Statement::For->next_statement);
  ok(SPVM::TestCase::Statement::For->nested_last);
  ok(SPVM::TestCase::Statement::For->nested_next);
  ok(SPVM::TestCase::Statement::For->nested_last_with_switch);
  ok(SPVM::TestCase::Statement::For->omit_init_inc);
  ok(SPVM::TestCase::Statement::For->condition_my);
  ok(SPVM::TestCase::Statement::For->foreach);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
