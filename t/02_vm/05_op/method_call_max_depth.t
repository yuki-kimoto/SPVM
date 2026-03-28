use lib "t/lib";
use TestAuto;
use TestUtil::MyLib;

use strict;
use warnings;
use Config;

use Test::More;

use SPVM 'TestCase::Operator::MethodCall';

my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

{
  ok(SPVM::TestCase::Operator::MethodCall->call_recursive);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
