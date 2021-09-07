use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::OArray';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# isa
{
  ok(SPVM::TestCase::OArray->basic());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
