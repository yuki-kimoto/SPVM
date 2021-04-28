use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::List';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::List
{
  ok(TestCase::Lib::SPVM::List->length);
  ok(TestCase::Lib::SPVM::List->push);
  ok(TestCase::Lib::SPVM::List->pop);
  ok(TestCase::Lib::SPVM::List->unshift);
  ok(TestCase::Lib::SPVM::List->shift);
  ok(TestCase::Lib::SPVM::List->offset_by_alternate_push_and_shift);
  ok(TestCase::Lib::SPVM::List->offset_by_alternate_unshift_and_pop);
  ok(TestCase::Lib::SPVM::List->set);
  ok(TestCase::Lib::SPVM::List->set_array);
  ok(TestCase::Lib::SPVM::List->get);
  ok(TestCase::Lib::SPVM::List->insert);
  ok(TestCase::Lib::SPVM::List->remove);
  ok(TestCase::Lib::SPVM::List->resize);
  ok(TestCase::Lib::SPVM::List->to_array);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
