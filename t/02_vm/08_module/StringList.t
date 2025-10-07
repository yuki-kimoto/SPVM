use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::StringList';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# StringList
{
  ok(SPVM::TestCase::Module::StringList->fields);
  ok(SPVM::TestCase::Module::StringList->new);
  ok(SPVM::TestCase::Module::StringList->new_len);
  ok(SPVM::TestCase::Module::StringList->get);
  ok(SPVM::TestCase::Module::StringList->insert);
  ok(SPVM::TestCase::Module::StringList->pop);
  ok(SPVM::TestCase::Module::StringList->push);
  ok(SPVM::TestCase::Module::StringList->remove);
  ok(SPVM::TestCase::Module::StringList->replace);
  ok(SPVM::TestCase::Module::StringList->splice);
  ok(SPVM::TestCase::Module::StringList->reserve);
  ok(SPVM::TestCase::Module::StringList->resize);
  ok(SPVM::TestCase::Module::StringList->set);
  ok(SPVM::TestCase::Module::StringList->shift);
  ok(SPVM::TestCase::Module::StringList->to_array);
  ok(SPVM::TestCase::Module::StringList->unshift);
  ok(SPVM::TestCase::Module::StringList->clone);
  ok(SPVM::TestCase::Module::StringList->push_);
  ok(SPVM::TestCase::Module::StringList->unshift_);
  ok(SPVM::TestCase::Module::StringList->get_array_unsafe);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
