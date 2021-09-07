use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::Lib::SPVM::ByteList';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::ByteList
{
  ok(SPVM::TestCase::Lib::SPVM::ByteList->push);
  ok(SPVM::TestCase::Lib::SPVM::ByteList->pop);
  ok(SPVM::TestCase::Lib::SPVM::ByteList->new);
  ok(SPVM::TestCase::Lib::SPVM::ByteList->new_len);
  ok(SPVM::TestCase::Lib::SPVM::ByteList->unshift);
  ok(SPVM::TestCase::Lib::SPVM::ByteList->shift);
  ok(SPVM::TestCase::Lib::SPVM::ByteList->length);
  ok(SPVM::TestCase::Lib::SPVM::ByteList->get);
  ok(SPVM::TestCase::Lib::SPVM::ByteList->set);
  ok(SPVM::TestCase::Lib::SPVM::ByteList->set_array);
  ok(SPVM::TestCase::Lib::SPVM::ByteList->to_array);
  ok(SPVM::TestCase::Lib::SPVM::ByteList->insert);
  ok(SPVM::TestCase::Lib::SPVM::ByteList->remove);
  ok(SPVM::TestCase::Lib::SPVM::ByteList->resize);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
