use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::IntList';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# IntList
{
  ok(SPVM::TestCase::Module::IntList->fields);
  ok(SPVM::TestCase::Module::IntList->new);
  ok(SPVM::TestCase::Module::IntList->new_len);
  ok(SPVM::TestCase::Module::IntList->get);
  ok(SPVM::TestCase::Module::IntList->insert);
  ok(SPVM::TestCase::Module::IntList->pop);
  ok(SPVM::TestCase::Module::IntList->push);
  ok(SPVM::TestCase::Module::IntList->remove);
  ok(SPVM::TestCase::Module::IntList->replace);
  ok(SPVM::TestCase::Module::IntList->reserve);
  ok(SPVM::TestCase::Module::IntList->resize);
  ok(SPVM::TestCase::Module::IntList->set);
  ok(SPVM::TestCase::Module::IntList->set_array);
  ok(SPVM::TestCase::Module::IntList->shift);
  ok(SPVM::TestCase::Module::IntList->to_array);
  ok(SPVM::TestCase::Module::IntList->unshift);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
