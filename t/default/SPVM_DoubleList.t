use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::DoubleList';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::DoubleList
{
  ok(SPVM::TestCase::Lib::DoubleList->push);
  ok(SPVM::TestCase::Lib::DoubleList->pop);
  ok(SPVM::TestCase::Lib::DoubleList->new);
  ok(SPVM::TestCase::Lib::DoubleList->new_len);
  ok(SPVM::TestCase::Lib::DoubleList->unshift);
  ok(SPVM::TestCase::Lib::DoubleList->shift);
  ok(SPVM::TestCase::Lib::DoubleList->length);
  ok(SPVM::TestCase::Lib::DoubleList->get);
  ok(SPVM::TestCase::Lib::DoubleList->set);
  ok(SPVM::TestCase::Lib::DoubleList->set_array);
  ok(SPVM::TestCase::Lib::DoubleList->to_array);
  ok(SPVM::TestCase::Lib::DoubleList->insert);
  ok(SPVM::TestCase::Lib::DoubleList->remove);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
