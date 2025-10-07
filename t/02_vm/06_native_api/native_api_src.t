use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use Config;
use Errno;

use SPVM 'TestCase::NativeAPISrc';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# src and include directory
{
  ok(SPVM::TestCase::NativeAPISrc->src_foo);
  ok(SPVM::TestCase::NativeAPISrc->src_bar);
  ok(SPVM::TestCase::NativeAPISrc->src_baz);
}

# Clear exception
$api->destroy_runtime_permanent_vars;

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
