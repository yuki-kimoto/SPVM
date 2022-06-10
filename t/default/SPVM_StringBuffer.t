use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Lib::StringBuffer';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::StringBuffer
{
  ok(SPVM::TestCase::Lib::StringBuffer->test_new);
  ok(SPVM::TestCase::Lib::StringBuffer->test_length);
  ok(SPVM::TestCase::Lib::StringBuffer->test_push);
  ok(SPVM::TestCase::Lib::StringBuffer->test_push_char);
  ok(SPVM::TestCase::Lib::StringBuffer->test_to_string);
  ok(SPVM::TestCase::Lib::StringBuffer->read_write_value);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
