use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Scope::Guard';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count();

# SPVM::Scope::Guard
{
  ok(SPVM::TestCase::Module::Scope::Guard->basic());
}

# All object is freed
$api->set_exception(undef);
my $end_memory_blocks_count = $api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
