use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::DoubleList';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# DoubleList
{
  ok(SPVM::TestCase::Module::DoubleList->fields);
  ok(SPVM::TestCase::Module::DoubleList->new);
  ok(SPVM::TestCase::Module::DoubleList->new_len);
  ok(SPVM::TestCase::Module::DoubleList->new_ref);
  ok(SPVM::TestCase::Module::DoubleList->get);
  ok(SPVM::TestCase::Module::DoubleList->insert);
  ok(SPVM::TestCase::Module::DoubleList->pop);
  ok(SPVM::TestCase::Module::DoubleList->push);
  ok(SPVM::TestCase::Module::DoubleList->remove);
  ok(SPVM::TestCase::Module::DoubleList->replace);
  ok(SPVM::TestCase::Module::DoubleList->splice);
  ok(SPVM::TestCase::Module::DoubleList->reserve);
  ok(SPVM::TestCase::Module::DoubleList->resize);
  ok(SPVM::TestCase::Module::DoubleList->set);
  ok(SPVM::TestCase::Module::DoubleList->shift);
  ok(SPVM::TestCase::Module::DoubleList->to_array);
  ok(SPVM::TestCase::Module::DoubleList->get_array_unsafe);
  ok(SPVM::TestCase::Module::DoubleList->unshift);
  ok(SPVM::TestCase::Module::DoubleList->clone);
  ok(SPVM::TestCase::Module::DoubleList->push_);
  ok(SPVM::TestCase::Module::DoubleList->unshift_);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
