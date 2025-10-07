use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

BEGIN { @ARGV = ('arg1', 'arg2', 'arg3') };

use SPVM 'CommandInfo';
use SPVM 'TestCase::Module::CommandInfo';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

is(SPVM::CommandInfo->PROGRAM_NAME, $0);
is_deeply(SPVM::CommandInfo->ARGV->to_elems, \@ARGV);


is(SPVM::CommandInfo->BASETIME, $^T);

is(SPVM::CommandInfo->WARNING, $^W);

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
