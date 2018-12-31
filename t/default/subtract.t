use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Subtract';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Subtract
{
  ok(TestCase::Subtract->subtract());

  is(TestCase::Subtract->subtract_int_max(), 2147483646);
  is(TestCase::Subtract->subtract_int_min(), -2147483648);
  is(TestCase::Subtract->subtract_int_underflow(), 2147483647);
  is(TestCase::Subtract->subtract_long_max(), 9223372036854775806);
  is(TestCase::Subtract->subtract_long_min(), -9223372036854775808);
  is(TestCase::Subtract->subtract_long_underflow(), 9223372036854775807);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

