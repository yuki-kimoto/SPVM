use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::BreakPoint';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# If you want to test the break_point manually, run the following command:
# make && perl -Mblib blib/script/spvm t/02_vm/05_op/break_point.spvm

my $output = `$^X -e "print chr(10)" | $^X -Mblib blib/script/spvm t/02_vm/05_op/break_point_continue.spvm 2>&1`;

like($output, qr|\Q[Break Point]eval::anon_class::0#main at t/02_vm/05_op/break_point_continue.spvm line 1|);

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
