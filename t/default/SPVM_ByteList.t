use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::ByteList';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::ByteList
{
  ok(SPVM::TestCase::Lib::ByteList->push);
  ok(SPVM::TestCase::Lib::ByteList->pop);
  ok(SPVM::TestCase::Lib::ByteList->new);
  ok(SPVM::TestCase::Lib::ByteList->new_len);
  ok(SPVM::TestCase::Lib::ByteList->unshift);
  ok(SPVM::TestCase::Lib::ByteList->shift);
  ok(SPVM::TestCase::Lib::ByteList->length);
  ok(SPVM::TestCase::Lib::ByteList->get);
  ok(SPVM::TestCase::Lib::ByteList->set);
  ok(SPVM::TestCase::Lib::ByteList->set_array);
  ok(SPVM::TestCase::Lib::ByteList->to_array);
  ok(SPVM::TestCase::Lib::ByteList->insert);
  ok(SPVM::TestCase::Lib::ByteList->remove);
  ok(SPVM::TestCase::Lib::ByteList->resize);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
