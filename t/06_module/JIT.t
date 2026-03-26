use lib "t/lib";
use TestAuto;
use TestUtil::MyLib;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::JIT';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# SPVM::JIT
{
  ok(SPVM::TestCase::Module::JIT->basic);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
