use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::ShortList';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::ShortList
{
  ok(TestCase::Lib::SPVM::ShortList->length);
  ok(TestCase::Lib::SPVM::ShortList->new);
  ok(TestCase::Lib::SPVM::ShortList->new_len);
  ok(TestCase::Lib::SPVM::ShortList->get);
  ok(TestCase::Lib::SPVM::ShortList->pop);
  ok(TestCase::Lib::SPVM::ShortList->push);
  ok(TestCase::Lib::SPVM::ShortList->insert);
  ok(TestCase::Lib::SPVM::ShortList->remove);
  ok(TestCase::Lib::SPVM::ShortList->set);
  ok(TestCase::Lib::SPVM::ShortList->set_array);
  ok(TestCase::Lib::SPVM::ShortList->shift);
  ok(TestCase::Lib::SPVM::ShortList->to_array);
  ok(TestCase::Lib::SPVM::ShortList->unshift);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
