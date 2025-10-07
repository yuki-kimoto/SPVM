use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Immutable::FloatList';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# FloatList
{
  ok(SPVM::TestCase::Module::Immutable::FloatList->fields);
  ok(SPVM::TestCase::Module::Immutable::FloatList->new);
  ok(SPVM::TestCase::Module::Immutable::FloatList->new_len);
  ok(SPVM::TestCase::Module::Immutable::FloatList->get);
  ok(SPVM::TestCase::Module::Immutable::FloatList->to_array);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
