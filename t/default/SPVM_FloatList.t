use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::Lib::SPVM::FloatList';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::FloatList
{
  ok(SPVM::TestCase::Lib::SPVM::FloatList->push);
  ok(SPVM::TestCase::Lib::SPVM::FloatList->pop);
  ok(SPVM::TestCase::Lib::SPVM::FloatList->new);
  ok(SPVM::TestCase::Lib::SPVM::FloatList->new_len);
  ok(SPVM::TestCase::Lib::SPVM::FloatList->unshift);
  ok(SPVM::TestCase::Lib::SPVM::FloatList->shift);
  ok(SPVM::TestCase::Lib::SPVM::FloatList->length);
  ok(SPVM::TestCase::Lib::SPVM::FloatList->get);
  ok(SPVM::TestCase::Lib::SPVM::FloatList->set);
  ok(SPVM::TestCase::Lib::SPVM::FloatList->set_array);
  ok(SPVM::TestCase::Lib::SPVM::FloatList->to_array);
  ok(SPVM::TestCase::Lib::SPVM::FloatList->insert);
  ok(SPVM::TestCase::Lib::SPVM::FloatList->remove);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
