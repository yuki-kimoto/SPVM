use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::Text';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# SPVM::Text
{
  ok(TestCase::Lib::SPVM::Text->test_ctor_default);
  ok(TestCase::Lib::SPVM::Text->test_ctor_with_capacity);
  ok(TestCase::Lib::SPVM::Text->test_ctor_with_string);
  ok(TestCase::Lib::SPVM::Text->test_length);
  ok(TestCase::Lib::SPVM::Text->test_push);
  ok(TestCase::Lib::SPVM::Text->test_pop);
  ok(TestCase::Lib::SPVM::Text->test_unshift);
  ok(TestCase::Lib::SPVM::Text->test_shift);
  ok(TestCase::Lib::SPVM::Text->test_set);
  ok(TestCase::Lib::SPVM::Text->test_get);
  ok(TestCase::Lib::SPVM::Text->test_append_string);
  ok(TestCase::Lib::SPVM::Text->test_append_text);
  ok(TestCase::Lib::SPVM::Text->test_splice);
  ok(TestCase::Lib::SPVM::Text->test_splice_no_reallocation);
  ok(TestCase::Lib::SPVM::Text->test_to_string);
  ok(TestCase::Lib::SPVM::Text->test_equals);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
