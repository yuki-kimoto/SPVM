use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::StringList';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::StringList
{
  ok(TestCase::Lib::SPVM::StringList->push);
  ok(TestCase::Lib::SPVM::StringList->pop);
  ok(TestCase::Lib::SPVM::StringList->new);
  ok(TestCase::Lib::SPVM::StringList->new_len);
  ok(TestCase::Lib::SPVM::StringList->new_capacity);
  ok(TestCase::Lib::SPVM::StringList->unshift);
  ok(TestCase::Lib::SPVM::StringList->shift);
  ok(TestCase::Lib::SPVM::StringList->length);
  ok(TestCase::Lib::SPVM::StringList->get);
  ok(TestCase::Lib::SPVM::StringList->set);
  ok(TestCase::Lib::SPVM::StringList->to_array);
  ok(TestCase::Lib::SPVM::StringList->insert);
  ok(TestCase::Lib::SPVM::StringList->remove);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
