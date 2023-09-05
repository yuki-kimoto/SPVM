use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use Config;
use Errno;

use SPVM 'TestCase::NativeAPI2';

my $build_dir = $ENV{SPVM_BUILD_DIR};

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();


# Native Exception
{
  is(SPVM::TestCase::NativeAPI2->mul(2, 3), 6);
  ok(SPVM::TestCase::NativeAPI2->spvm_extension2);
}

# src and include directory
{
  ok(SPVM::TestCase::NativeAPI2->src_foo);
  ok(SPVM::TestCase::NativeAPI2->src_bar);
}

# Clear exception
SPVM::api->set_exception(undef);

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
