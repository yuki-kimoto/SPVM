use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use utf8;

use Test::More 'no_plan';

use SPVM 'TestCase::Undef';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

{
  ok(TestCase::Undef->test_undef);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
