use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::LongList';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::LongList
{
  ok(SPVM::TestCase::Lib::LongList->push);
  ok(SPVM::TestCase::Lib::LongList->pop);
  ok(SPVM::TestCase::Lib::LongList->new);
  ok(SPVM::TestCase::Lib::LongList->new_len);
  ok(SPVM::TestCase::Lib::LongList->unshift);
  ok(SPVM::TestCase::Lib::LongList->shift);
  ok(SPVM::TestCase::Lib::LongList->length);
  ok(SPVM::TestCase::Lib::LongList->get);
  ok(SPVM::TestCase::Lib::LongList->set);
  ok(SPVM::TestCase::Lib::LongList->set_array);
  ok(SPVM::TestCase::Lib::LongList->to_array);
  ok(SPVM::TestCase::Lib::LongList->insert);
  ok(SPVM::TestCase::Lib::LongList->remove);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
