use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::LINEN';
use SPVM 'TestCase::LINER';
use SPVM 'TestCase::LINERN';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

ok(TestCase::LINEN->line);
ok(TestCase::LINER->line);
ok(TestCase::LINERN->line);

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
