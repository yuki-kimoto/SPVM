use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::FloatList';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::FloatList
{
  ok(TestCase::Lib::SPVM::FloatList->push);
  ok(TestCase::Lib::SPVM::FloatList->pop);
  ok(TestCase::Lib::SPVM::FloatList->new);
  ok(TestCase::Lib::SPVM::FloatList->new_len);
  ok(TestCase::Lib::SPVM::FloatList->unshift);
  ok(TestCase::Lib::SPVM::FloatList->shift);
  ok(TestCase::Lib::SPVM::FloatList->length);
  ok(TestCase::Lib::SPVM::FloatList->get);
  ok(TestCase::Lib::SPVM::FloatList->set);
  ok(TestCase::Lib::SPVM::FloatList->to_array);
  ok(TestCase::Lib::SPVM::FloatList->insert);
  ok(TestCase::Lib::SPVM::FloatList->remove);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
