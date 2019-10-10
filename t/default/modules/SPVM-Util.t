use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::Util';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# join
{
  ok(TestCase::Lib::SPVM::Util->test_joino);
}

# split
{
  ok(TestCase::Lib::SPVM::Util->test_split);
}

# copy_oarray
{
  ok(TestCase::Lib::SPVM::Util->test_copy_oarray);
}

# equals_oarray
{
  ok(TestCase::Lib::SPVM::Util->test_equals_oarray);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
