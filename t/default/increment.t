use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::Increment';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Pre inc
{
  ok(SPVM::TestCase::Increment->pre_inc_var);
  ok(SPVM::TestCase::Increment->pre_inc_array_access_constant_index);
  ok(SPVM::TestCase::Increment->pre_inc_array_access_var_index);
  ok(SPVM::TestCase::Increment->pre_inc_field_access);
  ok(SPVM::TestCase::Increment->pre_inc_deref);
  ok(SPVM::TestCase::Increment->pre_inc_package_var_access);
  ok(SPVM::TestCase::Increment->pre_inc_array_field_access_constant_index);
  
  ok(SPVM::TestCase::Increment->pre_inc_array_access_invocant_not_var);
  ok(SPVM::TestCase::Increment->pre_inc_array_field_access_invocant_not_var);
  ok(SPVM::TestCase::Increment->pre_inc_field_access_invocant_not_var);
}

# Pre dec
{
  ok(SPVM::TestCase::Increment->pre_dec_var);
  ok(SPVM::TestCase::Increment->pre_dec_array_access_constant_index);
  ok(SPVM::TestCase::Increment->pre_dec_array_access_var_index);
  ok(SPVM::TestCase::Increment->pre_dec_field_access);
  ok(SPVM::TestCase::Increment->pre_dec_deref);
  ok(SPVM::TestCase::Increment->pre_dec_package_var_access);
  ok(SPVM::TestCase::Increment->pre_dec_array_field_access_constant_index);

  ok(SPVM::TestCase::Increment->pre_dec_array_access_invocant_not_var);
  ok(SPVM::TestCase::Increment->pre_dec_array_field_access_invocant_not_var);
  ok(SPVM::TestCase::Increment->pre_dec_field_access_invocant_not_var);
}

# Post inc
{
  ok(SPVM::TestCase::Increment->post_inc_var);
  ok(SPVM::TestCase::Increment->post_inc_array_access_constant_index);
  ok(SPVM::TestCase::Increment->post_inc_array_access_var_index);
  ok(SPVM::TestCase::Increment->post_inc_field_access);
  ok(SPVM::TestCase::Increment->post_inc_deref);
  ok(SPVM::TestCase::Increment->post_inc_package_var_access);
  ok(SPVM::TestCase::Increment->post_inc_array_field_access_constant_index);

  ok(SPVM::TestCase::Increment->post_inc_array_access_invocant_not_var);
  ok(SPVM::TestCase::Increment->post_inc_array_field_access_invocant_not_var);
  ok(SPVM::TestCase::Increment->post_inc_field_access_invocant_not_var);
}

# Post dec
{
  ok(SPVM::TestCase::Increment->post_dec_var);
  ok(SPVM::TestCase::Increment->post_dec_array_access_constant_index);
  ok(SPVM::TestCase::Increment->post_dec_array_access_var_index);
  ok(SPVM::TestCase::Increment->post_dec_field_access);
  ok(SPVM::TestCase::Increment->post_dec_deref);
  ok(SPVM::TestCase::Increment->post_dec_package_var_access);
  ok(SPVM::TestCase::Increment->post_dec_array_field_access_constant_index);

  ok(SPVM::TestCase::Increment->post_dec_array_access_invocant_not_var);
  ok(SPVM::TestCase::Increment->post_dec_array_field_access_invocant_not_var);
  ok(SPVM::TestCase::Increment->post_dec_field_access_invocant_not_var);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

