use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Lib::FloatList';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::FloatList
{
  ok(SPVM::TestCase::Lib::FloatList->push);
  ok(SPVM::TestCase::Lib::FloatList->pop);
  ok(SPVM::TestCase::Lib::FloatList->new);
  ok(SPVM::TestCase::Lib::FloatList->new_len);
  ok(SPVM::TestCase::Lib::FloatList->unshift);
  ok(SPVM::TestCase::Lib::FloatList->shift);
  ok(SPVM::TestCase::Lib::FloatList->length);
  ok(SPVM::TestCase::Lib::FloatList->get);
  ok(SPVM::TestCase::Lib::FloatList->set);
  ok(SPVM::TestCase::Lib::FloatList->set_array);
  ok(SPVM::TestCase::Lib::FloatList->to_array);
  ok(SPVM::TestCase::Lib::FloatList->insert);
  ok(SPVM::TestCase::Lib::FloatList->remove);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
