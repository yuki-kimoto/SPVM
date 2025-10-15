use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::LongList';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# LongList
{
  ok(SPVM::TestCase::Module::LongList->fields);
  ok(SPVM::TestCase::Module::LongList->new);
  ok(SPVM::TestCase::Module::LongList->new_len);
  ok(SPVM::TestCase::Module::LongList->new_ref);
  ok(SPVM::TestCase::Module::LongList->get);
  ok(SPVM::TestCase::Module::LongList->insert);
  ok(SPVM::TestCase::Module::LongList->pop);
  ok(SPVM::TestCase::Module::LongList->push);
  ok(SPVM::TestCase::Module::LongList->remove);
  ok(SPVM::TestCase::Module::LongList->replace);
  ok(SPVM::TestCase::Module::LongList->splice);
  ok(SPVM::TestCase::Module::LongList->reserve);
  ok(SPVM::TestCase::Module::LongList->resize);
  ok(SPVM::TestCase::Module::LongList->set);
  ok(SPVM::TestCase::Module::LongList->shift);
  ok(SPVM::TestCase::Module::LongList->to_array);
  ok(SPVM::TestCase::Module::LongList->get_array);
  ok(SPVM::TestCase::Module::LongList->unshift);
  ok(SPVM::TestCase::Module::LongList->clone);
  ok(SPVM::TestCase::Module::LongList->push_);
  ok(SPVM::TestCase::Module::LongList->unshift_);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
