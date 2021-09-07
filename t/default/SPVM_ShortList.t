use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::Lib::SPVM::ShortList';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::ShortList
{
  ok(SPVM::TestCase::Lib::SPVM::ShortList->length);
  ok(SPVM::TestCase::Lib::SPVM::ShortList->new);
  ok(SPVM::TestCase::Lib::SPVM::ShortList->new_len);
  ok(SPVM::TestCase::Lib::SPVM::ShortList->get);
  ok(SPVM::TestCase::Lib::SPVM::ShortList->pop);
  ok(SPVM::TestCase::Lib::SPVM::ShortList->push);
  ok(SPVM::TestCase::Lib::SPVM::ShortList->insert);
  ok(SPVM::TestCase::Lib::SPVM::ShortList->remove);
  ok(SPVM::TestCase::Lib::SPVM::ShortList->set);
  ok(SPVM::TestCase::Lib::SPVM::ShortList->set_array);
  ok(SPVM::TestCase::Lib::SPVM::ShortList->shift);
  ok(SPVM::TestCase::Lib::SPVM::ShortList->to_array);
  ok(SPVM::TestCase::Lib::SPVM::ShortList->unshift);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
