use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::StringBuffer';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# SPVM::StringBuffer
{
  ok(TestCase::Lib::SPVM::StringBuffer->test_ctor_default);
  ok(TestCase::Lib::SPVM::StringBuffer->test_ctor_with_capacity);
  ok(TestCase::Lib::SPVM::StringBuffer->test_ctor_with_string);
  ok(TestCase::Lib::SPVM::StringBuffer->test_length);
  ok(TestCase::Lib::SPVM::StringBuffer->test_substr);
  ok(TestCase::Lib::SPVM::StringBuffer->test_prepend);
  ok(TestCase::Lib::SPVM::StringBuffer->test_append);
  ok(TestCase::Lib::SPVM::StringBuffer->test_append_string);
  ok(TestCase::Lib::SPVM::StringBuffer->test_append_bytes);
  ok(TestCase::Lib::SPVM::StringBuffer->test_replace);
  ok(TestCase::Lib::SPVM::StringBuffer->test_to_barray);
  ok(TestCase::Lib::SPVM::StringBuffer->test_equals);
  ok(TestCase::Lib::SPVM::StringBuffer->test_to_str);
  ok(TestCase::Lib::SPVM::StringBuffer->test_index_with_string);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
