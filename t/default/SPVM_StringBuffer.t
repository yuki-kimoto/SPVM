use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::StringBuffer';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::StringBuffer
{
  ok(TestCase::Lib::SPVM::StringBuffer->test_new_opt);
  ok(TestCase::Lib::SPVM::StringBuffer->test_length);
  ok(TestCase::Lib::SPVM::StringBuffer->test_push);
  ok(TestCase::Lib::SPVM::StringBuffer->test_push_char);
  ok(TestCase::Lib::SPVM::StringBuffer->test_push_range);
  ok(TestCase::Lib::SPVM::StringBuffer->test_to_string);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
