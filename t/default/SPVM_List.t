use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::List';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::List
{
  ok(SPVM::TestCase::Lib::List->length);
  ok(SPVM::TestCase::Lib::List->push);
  ok(SPVM::TestCase::Lib::List->pop);
  ok(SPVM::TestCase::Lib::List->unshift);
  ok(SPVM::TestCase::Lib::List->shift);
  ok(SPVM::TestCase::Lib::List->offset_by_alternate_push_and_shift);
  ok(SPVM::TestCase::Lib::List->offset_by_alternate_unshift_and_pop);
  ok(SPVM::TestCase::Lib::List->set);
  ok(SPVM::TestCase::Lib::List->set_array);
  ok(SPVM::TestCase::Lib::List->get);
  ok(SPVM::TestCase::Lib::List->insert);
  ok(SPVM::TestCase::Lib::List->remove);
  ok(SPVM::TestCase::Lib::List->resize);
  ok(SPVM::TestCase::Lib::List->to_array);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
