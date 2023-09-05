use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use Config;
use Errno;

use SPVM 'TestCase::NativeAPI2';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# src and include directory
{
  warn "AAA";
  ok(SPVM::TestCase::NativeAPI2->src_foo);
  warn "BBB";
  ok(SPVM::TestCase::NativeAPI2->src_bar);
  warn "CCC";
  ok(SPVM::TestCase::NativeAPI2->src_baz);
  warn "DDD";
}

# Clear exception
SPVM::api->set_exception(undef);

warn "EEE";

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
