use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Statement::While';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# while
{
  ok(SPVM::TestCase::Statement::While->basic);
  ok(SPVM::TestCase::Statement::While->next);
  ok(SPVM::TestCase::Statement::While->last);
  ok(SPVM::TestCase::Statement::While->condition_my);
  ok(SPVM::TestCase::Statement::While->condition_my_var_mem_id);
}


# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
