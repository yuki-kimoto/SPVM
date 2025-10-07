use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Statement::Unless';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# unless Statement
{
  ok(SPVM::TestCase::Statement::Unless->true_condition);
  ok(SPVM::TestCase::Statement::Unless->false_condition);
  ok(SPVM::TestCase::Statement::Unless->elsif);
  ok(SPVM::TestCase::Statement::Unless->else);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
