use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Immutable::DoubleList';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# DoubleList
{
  ok(SPVM::TestCase::Module::Immutable::DoubleList->fields);
  ok(SPVM::TestCase::Module::Immutable::DoubleList->new);
  ok(SPVM::TestCase::Module::Immutable::DoubleList->new_len);
  ok(SPVM::TestCase::Module::Immutable::DoubleList->get);
  ok(SPVM::TestCase::Module::Immutable::DoubleList->to_array);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
