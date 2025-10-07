use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM;

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Default loaded classes
$api->class('Byte')->new(1);
$api->class('Short')->new(1);
$api->class('Int')->new(1);
$api->class('Long')->new(1);
$api->class('Float')->new(1);
$api->class('Double')->new(1);
$api->class('Bool')->TRUE;
$api->class('Address')->new;

ok(1);

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
