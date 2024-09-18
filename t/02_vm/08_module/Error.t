use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Error';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count();

# SPVM::Error
{
  ok(SPVM::TestCase::Module::Error->basic_type_id);
}

# All object is freed
my $end_memory_blocks_count = $api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
