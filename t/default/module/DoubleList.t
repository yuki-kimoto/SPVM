use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::DoubleList';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# DoubleList
{
  ok(SPVM::TestCase::Module::DoubleList->fields);
  ok(SPVM::TestCase::Module::DoubleList->new);
  ok(SPVM::TestCase::Module::DoubleList->new_len);
  ok(SPVM::TestCase::Module::DoubleList->get);
  ok(SPVM::TestCase::Module::DoubleList->insert);
  ok(SPVM::TestCase::Module::DoubleList->pop);
  ok(SPVM::TestCase::Module::DoubleList->push);
  ok(SPVM::TestCase::Module::DoubleList->remove);
  ok(SPVM::TestCase::Module::DoubleList->replace);
  ok(SPVM::TestCase::Module::DoubleList->resize);
  ok(SPVM::TestCase::Module::DoubleList->set);
  ok(SPVM::TestCase::Module::DoubleList->set_array);
  ok(SPVM::TestCase::Module::DoubleList->shift);
  ok(SPVM::TestCase::Module::DoubleList->to_array);
  ok(SPVM::TestCase::Module::DoubleList->unshift);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
