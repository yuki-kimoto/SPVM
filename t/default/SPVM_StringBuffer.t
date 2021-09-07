use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::Lib::SPVM::StringBuffer';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::StringBuffer
{
  ok(SPVM::TestCase::Lib::SPVM::StringBuffer->test_new);
  ok(SPVM::TestCase::Lib::SPVM::StringBuffer->test_length);
  ok(SPVM::TestCase::Lib::SPVM::StringBuffer->test_push);
  ok(SPVM::TestCase::Lib::SPVM::StringBuffer->test_push_char);
  ok(SPVM::TestCase::Lib::SPVM::StringBuffer->test_to_string);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
