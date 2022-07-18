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
  ok(SPVM::TestCase::Lib::StringBuffer->new);
  ok(SPVM::TestCase::Lib::StringBuffer->length);
  ok(SPVM::TestCase::Lib::StringBuffer->push);
  ok(SPVM::TestCase::Lib::StringBuffer->push_char);
  ok(SPVM::TestCase::Lib::StringBuffer->to_string);
  ok(SPVM::TestCase::Lib::StringBuffer->read_write_value);
  ok(SPVM::TestCase::Lib::StringBuffer->replace);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
