use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::FloatList';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::FloatList
{
  ok(SPVM::TestCase::Module::FloatList->push);
  ok(SPVM::TestCase::Module::FloatList->pop);
  ok(SPVM::TestCase::Module::FloatList->new);
  ok(SPVM::TestCase::Module::FloatList->new_len);
  ok(SPVM::TestCase::Module::FloatList->unshift);
  ok(SPVM::TestCase::Module::FloatList->shift);
  ok(SPVM::TestCase::Module::FloatList->length);
  ok(SPVM::TestCase::Module::FloatList->get);
  ok(SPVM::TestCase::Module::FloatList->set);
  ok(SPVM::TestCase::Module::FloatList->set_array);
  ok(SPVM::TestCase::Module::FloatList->to_array);
  ok(SPVM::TestCase::Module::FloatList->insert);
  ok(SPVM::TestCase::Module::FloatList->remove);
  ok(SPVM::TestCase::Module::FloatList->replace);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
