use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Increment';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Pre inc
{
  ok(TestCase::Increment->pre_inc());
  ok(TestCase::Increment->pre_inc_array_access());
  ok(TestCase::Increment->pre_inc_field_access());
}

# Pre dec
{
  ok(TestCase::Increment->pre_dec());
}

# Post inc
{
  ok(TestCase::Increment->post_inc());
}

# Post dec
{
  ok(TestCase::Increment->post_dec());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

