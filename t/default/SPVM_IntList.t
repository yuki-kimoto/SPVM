use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::Lib::SPVM::IntList';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::IntList
{
  ok(SPVM::TestCase::Lib::SPVM::IntList->push);
  ok(SPVM::TestCase::Lib::SPVM::IntList->pop);
  ok(SPVM::TestCase::Lib::SPVM::IntList->new);
  ok(SPVM::TestCase::Lib::SPVM::IntList->new_len);
  ok(SPVM::TestCase::Lib::SPVM::IntList->unshift);
  ok(SPVM::TestCase::Lib::SPVM::IntList->shift);
  ok(SPVM::TestCase::Lib::SPVM::IntList->length);
  ok(SPVM::TestCase::Lib::SPVM::IntList->get);
  ok(SPVM::TestCase::Lib::SPVM::IntList->set);
  ok(SPVM::TestCase::Lib::SPVM::IntList->set_array);
  ok(SPVM::TestCase::Lib::SPVM::IntList->to_array);
  ok(SPVM::TestCase::Lib::SPVM::IntList->insert);
  ok(SPVM::TestCase::Lib::SPVM::IntList->remove);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
