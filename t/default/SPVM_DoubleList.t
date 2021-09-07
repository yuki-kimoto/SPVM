use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::Lib::SPVM::DoubleList';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::DoubleList
{
  ok(SPVM::TestCase::Lib::SPVM::DoubleList->push);
  ok(SPVM::TestCase::Lib::SPVM::DoubleList->pop);
  ok(SPVM::TestCase::Lib::SPVM::DoubleList->new);
  ok(SPVM::TestCase::Lib::SPVM::DoubleList->new_len);
  ok(SPVM::TestCase::Lib::SPVM::DoubleList->unshift);
  ok(SPVM::TestCase::Lib::SPVM::DoubleList->shift);
  ok(SPVM::TestCase::Lib::SPVM::DoubleList->length);
  ok(SPVM::TestCase::Lib::SPVM::DoubleList->get);
  ok(SPVM::TestCase::Lib::SPVM::DoubleList->set);
  ok(SPVM::TestCase::Lib::SPVM::DoubleList->set_array);
  ok(SPVM::TestCase::Lib::SPVM::DoubleList->to_array);
  ok(SPVM::TestCase::Lib::SPVM::DoubleList->insert);
  ok(SPVM::TestCase::Lib::SPVM::DoubleList->remove);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
