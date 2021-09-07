use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::For';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# for
{
  ok(SPVM::TestCase::For->basic);
  ok(SPVM::TestCase::For->next_statement);
  ok(SPVM::TestCase::For->nested_last);
  ok(SPVM::TestCase::For->nested_next);
  ok(SPVM::TestCase::For->nested_last_with_switch);
  ok(SPVM::TestCase::For->omit_init_inc);
  ok(SPVM::TestCase::For->condition_my);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
