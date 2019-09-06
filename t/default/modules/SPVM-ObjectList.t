use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::ObjectList';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# SPVM::ObjectList
{
  ok(TestCase::Lib::SPVM::ObjectList->test_ctor_default);
  ok(TestCase::Lib::SPVM::ObjectList->test_ctor_with_capacity);
  ok(TestCase::Lib::SPVM::ObjectList->test_ctor_with_array);
  ok(TestCase::Lib::SPVM::ObjectList->test_length);
  ok(TestCase::Lib::SPVM::ObjectList->test_push);
  ok(TestCase::Lib::SPVM::ObjectList->test_pop);
  ok(TestCase::Lib::SPVM::ObjectList->test_unshift);
  ok(TestCase::Lib::SPVM::ObjectList->test_shift);
  ok(TestCase::Lib::SPVM::ObjectList->test_offset_by_alternate_push_and_shift);
  ok(TestCase::Lib::SPVM::ObjectList->test_offset_by_alternate_unshift_and_pop);
  ok(TestCase::Lib::SPVM::ObjectList->test_set);
  ok(TestCase::Lib::SPVM::ObjectList->test_get);
  ok(TestCase::Lib::SPVM::ObjectList->test_splice);
  ok(TestCase::Lib::SPVM::ObjectList->test_splice_no_reallocation);
  ok(TestCase::Lib::SPVM::ObjectList->test_splice_offset_is_valid_when_removed);
  ok(TestCase::Lib::SPVM::ObjectList->test_splice_offset_is_valid_when_appended);
  ok(TestCase::Lib::SPVM::ObjectList->test_to_array);
  ok(TestCase::Lib::SPVM::ObjectList->insert);
  ok(TestCase::Lib::SPVM::ObjectList->remove);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
