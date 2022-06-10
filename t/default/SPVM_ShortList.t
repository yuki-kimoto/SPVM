use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Lib::ShortList';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::ShortList
{
  ok(SPVM::TestCase::Lib::ShortList->length);
  ok(SPVM::TestCase::Lib::ShortList->new);
  ok(SPVM::TestCase::Lib::ShortList->new_len);
  ok(SPVM::TestCase::Lib::ShortList->get);
  ok(SPVM::TestCase::Lib::ShortList->pop);
  ok(SPVM::TestCase::Lib::ShortList->push);
  ok(SPVM::TestCase::Lib::ShortList->insert);
  ok(SPVM::TestCase::Lib::ShortList->remove);
  ok(SPVM::TestCase::Lib::ShortList->set);
  ok(SPVM::TestCase::Lib::ShortList->set_array);
  ok(SPVM::TestCase::Lib::ShortList->shift);
  ok(SPVM::TestCase::Lib::ShortList->to_array);
  ok(SPVM::TestCase::Lib::ShortList->unshift);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
