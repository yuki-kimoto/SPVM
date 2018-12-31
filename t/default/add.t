use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Add';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Add
{
  ok(TestCase::Add->add());
  is(TestCase::Add->add_int_max(), 2147483647);
  is(TestCase::Add->add_int_min(), -2147483647);
  is(TestCase::Add->add_int_overflow(), -2147483648);
  is(TestCase::Add->add_long_max(), 9223372036854775807);
  is(TestCase::Add->add_long_min(), -9223372036854775807);
  is(TestCase::Add->add_long_overflow(), -9223372036854775808);
}
# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

