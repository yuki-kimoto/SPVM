use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Alias';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count();

# Alias 
{
  ok(SPVM::TestCase::Alias->alias);
}

# All object is freed
$api->set_exception(undef);
my $end_memory_blocks_count = $api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);



done_testing;
