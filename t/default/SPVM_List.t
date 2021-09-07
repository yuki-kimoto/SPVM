use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::Lib::SPVM::List';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::List
{
  ok(SPVM::TestCase::Lib::SPVM::List->length);
  ok(SPVM::TestCase::Lib::SPVM::List->push);
  ok(SPVM::TestCase::Lib::SPVM::List->pop);
  ok(SPVM::TestCase::Lib::SPVM::List->unshift);
  ok(SPVM::TestCase::Lib::SPVM::List->shift);
  ok(SPVM::TestCase::Lib::SPVM::List->offset_by_alternate_push_and_shift);
  ok(SPVM::TestCase::Lib::SPVM::List->offset_by_alternate_unshift_and_pop);
  ok(SPVM::TestCase::Lib::SPVM::List->set);
  ok(SPVM::TestCase::Lib::SPVM::List->set_array);
  ok(SPVM::TestCase::Lib::SPVM::List->get);
  ok(SPVM::TestCase::Lib::SPVM::List->insert);
  ok(SPVM::TestCase::Lib::SPVM::List->remove);
  ok(SPVM::TestCase::Lib::SPVM::List->resize);
  ok(SPVM::TestCase::Lib::SPVM::List->to_array);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
