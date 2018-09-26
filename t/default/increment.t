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
  ok(TestCase::Increment->pre_inc_var);
  ok(TestCase::Increment->pre_inc_array_access_constant_index);
  ok(TestCase::Increment->pre_inc_array_access_var_index);
  ok(TestCase::Increment->pre_inc_field_access);
  ok(TestCase::Increment->pre_inc_deref);
  ok(TestCase::Increment->pre_inc_package_var_access);
  ok(TestCase::Increment->pre_inc_array_field_access_constant_index);
}

# Pre dec
{
  ok(TestCase::Increment->pre_dec_var);
  ok(TestCase::Increment->pre_dec_array_access_constant_index);
  ok(TestCase::Increment->pre_dec_array_access_var_index);
  ok(TestCase::Increment->pre_dec_field_access);
  ok(TestCase::Increment->pre_dec_deref);
  ok(TestCase::Increment->pre_dec_package_var_access);
  ok(TestCase::Increment->pre_dec_array_field_access_constant_index);
}

# Post inc
{
  ok(TestCase::Increment->post_inc_var());
}

# Post dec
{
  ok(TestCase::Increment->post_dec());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

