use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::Lib::StringList';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::StringList
{
  ok(SPVM::TestCase::Lib::StringList->push);
  ok(SPVM::TestCase::Lib::StringList->pop);
  ok(SPVM::TestCase::Lib::StringList->new);
  ok(SPVM::TestCase::Lib::StringList->new_len);
  ok(SPVM::TestCase::Lib::StringList->unshift);
  ok(SPVM::TestCase::Lib::StringList->shift);
  ok(SPVM::TestCase::Lib::StringList->length);
  ok(SPVM::TestCase::Lib::StringList->get);
  ok(SPVM::TestCase::Lib::StringList->set);
  ok(SPVM::TestCase::Lib::StringList->set_array);
  ok(SPVM::TestCase::Lib::StringList->to_array);
  ok(SPVM::TestCase::Lib::StringList->insert);
  ok(SPVM::TestCase::Lib::StringList->remove);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
