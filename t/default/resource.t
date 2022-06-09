use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::UseResource::Foo1';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

ok(SPVM::TestCase::UseResource::Foo1->test);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
