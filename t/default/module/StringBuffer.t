use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::StringBuffer';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::StringBuffer
{
  ok(SPVM::TestCase::Module::StringBuffer->new);
  ok(SPVM::TestCase::Module::StringBuffer->length);
  ok(SPVM::TestCase::Module::StringBuffer->push);
  ok(SPVM::TestCase::Module::StringBuffer->push_char);
  ok(SPVM::TestCase::Module::StringBuffer->to_string);
  ok(SPVM::TestCase::Module::StringBuffer->read_write_value);
  ok(SPVM::TestCase::Module::StringBuffer->replace == 1);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
