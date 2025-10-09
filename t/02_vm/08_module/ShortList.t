use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::ShortList';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# ShortList
{
  ok(SPVM::TestCase::Module::ShortList->fields);
  ok(SPVM::TestCase::Module::ShortList->new);
  ok(SPVM::TestCase::Module::ShortList->new_len);
  ok(SPVM::TestCase::Module::ShortList->new_ref);
  ok(SPVM::TestCase::Module::ShortList->get);
  ok(SPVM::TestCase::Module::ShortList->insert);
  ok(SPVM::TestCase::Module::ShortList->pop);
  ok(SPVM::TestCase::Module::ShortList->push);
  ok(SPVM::TestCase::Module::ShortList->remove);
  ok(SPVM::TestCase::Module::ShortList->replace);
  ok(SPVM::TestCase::Module::ShortList->splice);
  ok(SPVM::TestCase::Module::ShortList->reserve);
  ok(SPVM::TestCase::Module::ShortList->resize);
  ok(SPVM::TestCase::Module::ShortList->set);
  ok(SPVM::TestCase::Module::ShortList->shift);
  ok(SPVM::TestCase::Module::ShortList->to_array);
  ok(SPVM::TestCase::Module::ShortList->get_array_unsafe);
  ok(SPVM::TestCase::Module::ShortList->unshift);
  ok(SPVM::TestCase::Module::ShortList->clone);
  ok(SPVM::TestCase::Module::ShortList->push_);
  ok(SPVM::TestCase::Module::ShortList->unshift_);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
