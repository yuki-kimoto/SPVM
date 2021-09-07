use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::Lib::SPVM::StringList';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::StringList
{
  ok(SPVM::TestCase::Lib::SPVM::StringList->push);
  ok(SPVM::TestCase::Lib::SPVM::StringList->pop);
  ok(SPVM::TestCase::Lib::SPVM::StringList->new);
  ok(SPVM::TestCase::Lib::SPVM::StringList->new_len);
  ok(SPVM::TestCase::Lib::SPVM::StringList->unshift);
  ok(SPVM::TestCase::Lib::SPVM::StringList->shift);
  ok(SPVM::TestCase::Lib::SPVM::StringList->length);
  ok(SPVM::TestCase::Lib::SPVM::StringList->get);
  ok(SPVM::TestCase::Lib::SPVM::StringList->set);
  ok(SPVM::TestCase::Lib::SPVM::StringList->set_array);
  ok(SPVM::TestCase::Lib::SPVM::StringList->to_array);
  ok(SPVM::TestCase::Lib::SPVM::StringList->insert);
  ok(SPVM::TestCase::Lib::SPVM::StringList->remove);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
