use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use Config;
use Errno;

use SPVM 'TestCase::NativeAPISrc';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# src and include directory
{
  ok(SPVM::TestCase::NativeAPISrc->src_foo);
  ok(SPVM::TestCase::NativeAPISrc->src_bar);
  ok(SPVM::TestCase::NativeAPISrc->src_baz);
}

# Clear exception
SPVM::api->set_exception(undef);

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
