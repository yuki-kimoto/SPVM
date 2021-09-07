use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::Lib::SPVM::LongList';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::LongList
{
  ok(SPVM::TestCase::Lib::SPVM::LongList->push);
  ok(SPVM::TestCase::Lib::SPVM::LongList->pop);
  ok(SPVM::TestCase::Lib::SPVM::LongList->new);
  ok(SPVM::TestCase::Lib::SPVM::LongList->new_len);
  ok(SPVM::TestCase::Lib::SPVM::LongList->unshift);
  ok(SPVM::TestCase::Lib::SPVM::LongList->shift);
  ok(SPVM::TestCase::Lib::SPVM::LongList->length);
  ok(SPVM::TestCase::Lib::SPVM::LongList->get);
  ok(SPVM::TestCase::Lib::SPVM::LongList->set);
  ok(SPVM::TestCase::Lib::SPVM::LongList->set_array);
  ok(SPVM::TestCase::Lib::SPVM::LongList->to_array);
  ok(SPVM::TestCase::Lib::SPVM::LongList->insert);
  ok(SPVM::TestCase::Lib::SPVM::LongList->remove);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
