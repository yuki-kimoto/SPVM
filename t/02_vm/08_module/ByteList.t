use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::ByteList';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# ByteList
{
  ok(SPVM::TestCase::Module::ByteList->fields);
  ok(SPVM::TestCase::Module::ByteList->new);
  ok(SPVM::TestCase::Module::ByteList->new_len);
  ok(SPVM::TestCase::Module::ByteList->new_ref);
  ok(SPVM::TestCase::Module::ByteList->get);
  ok(SPVM::TestCase::Module::ByteList->insert);
  ok(SPVM::TestCase::Module::ByteList->pop);
  ok(SPVM::TestCase::Module::ByteList->push);
  ok(SPVM::TestCase::Module::ByteList->remove);
  ok(SPVM::TestCase::Module::ByteList->replace);
  ok(SPVM::TestCase::Module::ByteList->splice);
  ok(SPVM::TestCase::Module::ByteList->reserve);
  ok(SPVM::TestCase::Module::ByteList->resize);
  ok(SPVM::TestCase::Module::ByteList->set);
  ok(SPVM::TestCase::Module::ByteList->shift);
  ok(SPVM::TestCase::Module::ByteList->to_array);
  ok(SPVM::TestCase::Module::ByteList->get_array_unsafe);
  ok(SPVM::TestCase::Module::ByteList->get_array);
  ok(SPVM::TestCase::Module::ByteList->unshift);
  ok(SPVM::TestCase::Module::ByteList->clone);
  ok(SPVM::TestCase::Module::ByteList->push_);
  ok(SPVM::TestCase::Module::ByteList->unshift_);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
