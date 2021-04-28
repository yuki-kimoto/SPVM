use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::ByteList';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::ByteList
{
  ok(TestCase::Lib::SPVM::ByteList->push);
  ok(TestCase::Lib::SPVM::ByteList->pop);
  ok(TestCase::Lib::SPVM::ByteList->new);
  ok(TestCase::Lib::SPVM::ByteList->new_len);
  ok(TestCase::Lib::SPVM::ByteList->unshift);
  ok(TestCase::Lib::SPVM::ByteList->shift);
  ok(TestCase::Lib::SPVM::ByteList->length);
  ok(TestCase::Lib::SPVM::ByteList->get);
  ok(TestCase::Lib::SPVM::ByteList->set);
  ok(TestCase::Lib::SPVM::ByteList->set_array);
  ok(TestCase::Lib::SPVM::ByteList->to_array);
  ok(TestCase::Lib::SPVM::ByteList->insert);
  ok(TestCase::Lib::SPVM::ByteList->remove);
  ok(TestCase::Lib::SPVM::ByteList->resize);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
