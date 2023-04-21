use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM;

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

my $api = SPVM::api();

# Default loaded classes
$api->class('Byte')->new(1);
$api->class('Short')->new(1);
$api->class('Int')->new(1);
$api->class('Long')->new(1);
$api->class('Float')->new(1);
$api->class('Double')->new(1);
$api->class('Bool')->new_true;
$api->class('Address')->new;

ok(1);

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
