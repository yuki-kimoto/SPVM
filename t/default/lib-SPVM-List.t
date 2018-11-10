use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::List';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::List
{
  ok(TestCase::List->test_ctor_default);
  ok(TestCase::List->test_ctor_with_capacity);
  ok(TestCase::List->test_ctor_with_array);
  ok(TestCase::List->test_length);
  ok(TestCase::List->test_push);
  ok(TestCase::List->test_pop);
  ok(TestCase::List->test_unshift);
  ok(TestCase::List->test_shift);
  ok(TestCase::List->test_offset_by_alternate_push_and_shift);
  ok(TestCase::List->test_offset_by_alternate_unshift_and_pop);
  ok(TestCase::List->test_set);
  ok(TestCase::List->test_get);
  ok(TestCase::List->test_splice);
  ok(TestCase::List->test_splice_no_reallocation);
  ok(TestCase::List->test_splice_offset_is_valid_when_removed);
  ok(TestCase::List->test_splice_offset_is_valid_when_appended);
  ok(TestCase::List->test_splice_deallocation);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
