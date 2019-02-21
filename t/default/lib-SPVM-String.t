use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::String';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# SPVM::String
{
  ok(TestCase::Lib::SPVM::String->test_ctor_default);
  ok(TestCase::Lib::SPVM::String->test_ctor_with_capacity);
  ok(TestCase::Lib::SPVM::String->test_ctor_with_string);
  ok(TestCase::Lib::SPVM::String->test_length);
  ok(TestCase::Lib::SPVM::String->test_substr);
  #ok(TestCase::Lib::SPVM::String->test_substr_copy_on_write);
  #ok(TestCase::Lib::SPVM::String->test_copy);
  ok(TestCase::Lib::SPVM::String->test_prepend);
  #ok(TestCase::Lib::SPVM::String->test_prepend_copy_on_write);
  ok(TestCase::Lib::SPVM::String->test_append);
  #ok(TestCase::Lib::SPVM::String->test_append_copy_on_write);
  ok(TestCase::Lib::SPVM::String->test_replace);
  #ok(TestCase::Lib::SPVM::String->test_replace_copy_on_write);
  ok(TestCase::Lib::SPVM::String->test_to_barray);
  ok(TestCase::Lib::SPVM::String->test_equals);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
