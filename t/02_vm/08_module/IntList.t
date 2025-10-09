use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::IntList';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# IntList
{
  ok(SPVM::TestCase::Module::IntList->fields);
  ok(SPVM::TestCase::Module::IntList->new);
  ok(SPVM::TestCase::Module::IntList->new_len);
  ok(SPVM::TestCase::Module::IntList->new_ref);
  ok(SPVM::TestCase::Module::IntList->get);
  ok(SPVM::TestCase::Module::IntList->insert);
  ok(SPVM::TestCase::Module::IntList->pop);
  ok(SPVM::TestCase::Module::IntList->push);
  ok(SPVM::TestCase::Module::IntList->remove);
  ok(SPVM::TestCase::Module::IntList->replace);
  ok(SPVM::TestCase::Module::IntList->splice);
  ok(SPVM::TestCase::Module::IntList->reserve);
  ok(SPVM::TestCase::Module::IntList->resize);
  ok(SPVM::TestCase::Module::IntList->set);
  ok(SPVM::TestCase::Module::IntList->shift);
  ok(SPVM::TestCase::Module::IntList->to_array);
  ok(SPVM::TestCase::Module::IntList->get_array_unsafe);
  ok(SPVM::TestCase::Module::IntList->get_array);
  ok(SPVM::TestCase::Module::IntList->unshift);
  ok(SPVM::TestCase::Module::IntList->clone);
  ok(SPVM::TestCase::Module::IntList->push_);
  ok(SPVM::TestCase::Module::IntList->unshift_);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
