use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Loop';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# for
{
  ok(TestCase::Loop->basic());
  ok(TestCase::Loop->next_statement());
  ok(TestCase::Loop->nested_last);
  ok(TestCase::Loop->nested_next);
  ok(TestCase::Loop->nested_last_with_switch);
}


# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
