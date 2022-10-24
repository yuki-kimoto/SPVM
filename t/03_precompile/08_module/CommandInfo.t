use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

BEGIN { @ARGV = ('arg1', 'arg2', 'arg3') };

use SPVM 'CommandInfo';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

is(SPVM::CommandInfo->PROGRAM_NAME, $0);
is_deeply(SPVM::CommandInfo->ARGV->to_elems, \@ARGV);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
