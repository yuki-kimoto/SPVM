use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::LongList';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::LongList
{
  ok(TestCase::Lib::SPVM::LongList->push);
  ok(TestCase::Lib::SPVM::LongList->pop);
  ok(TestCase::Lib::SPVM::LongList->new);
  ok(TestCase::Lib::SPVM::LongList->new_len);
  ok(TestCase::Lib::SPVM::LongList->unshift);
  ok(TestCase::Lib::SPVM::LongList->shift);
  ok(TestCase::Lib::SPVM::LongList->length);
  ok(TestCase::Lib::SPVM::LongList->get);
  ok(TestCase::Lib::SPVM::LongList->set);
  ok(TestCase::Lib::SPVM::LongList->set_array);
  ok(TestCase::Lib::SPVM::LongList->to_array);
  ok(TestCase::Lib::SPVM::LongList->insert);
  ok(TestCase::Lib::SPVM::LongList->remove);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
