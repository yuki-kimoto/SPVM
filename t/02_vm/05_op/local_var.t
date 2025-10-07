use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::LocalVar';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Local variable
{
  ok(SPVM::TestCase::LocalVar->name);
  ok(SPVM::TestCase::LocalVar->var_brace);
  ok(SPVM::TestCase::LocalVar->upper_case);
  ok(SPVM::TestCase::LocalVar->high_precidence_than_class_var);
  ok(SPVM::TestCase::LocalVar->with_logical_operator);
  ok(SPVM::TestCase::LocalVar->temporary_local_var);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
