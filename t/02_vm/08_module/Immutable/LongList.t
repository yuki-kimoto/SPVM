use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Immutable::LongList';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# LongList
{
  ok(SPVM::TestCase::Module::Immutable::LongList->fields);
  ok(SPVM::TestCase::Module::Immutable::LongList->new);
  ok(SPVM::TestCase::Module::Immutable::LongList->new_len);
  ok(SPVM::TestCase::Module::Immutable::LongList->get);
  ok(SPVM::TestCase::Module::Immutable::LongList->to_array);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
