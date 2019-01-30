use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::For';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# for
{
  ok(TestCase::For->basic);
  ok(TestCase::For->next_statement);
  ok(TestCase::For->nested_last);
  ok(TestCase::For->nested_next);
  ok(TestCase::For->nested_last_with_switch);
  ok(TestCase::For->omit_init_inc);
  ok(TestCase::For->condition_my);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
