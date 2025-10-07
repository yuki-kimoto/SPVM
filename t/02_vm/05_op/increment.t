use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::Increment';



# Start objects count
my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Pre inc
{
  ok(SPVM::TestCase::Operator::Increment->pre_inc_var);
  ok(SPVM::TestCase::Operator::Increment->pre_inc_element_access_constant_index);
  ok(SPVM::TestCase::Operator::Increment->pre_inc_element_access_var_index);
  ok(SPVM::TestCase::Operator::Increment->pre_inc_field_access);
  ok(SPVM::TestCase::Operator::Increment->pre_inc_deref);
  ok(SPVM::TestCase::Operator::Increment->pre_inc_class_var_access);
  ok(SPVM::TestCase::Operator::Increment->pre_inc_array_field_access_constant_index);
  ok(SPVM::TestCase::Operator::Increment->pre_inc_element_access_invocant_not_var);
  ok(SPVM::TestCase::Operator::Increment->pre_inc_array_field_access_invocant_not_var);
  ok(SPVM::TestCase::Operator::Increment->pre_inc_field_access_invocant_not_var);
}

# Post inc
{
  ok(SPVM::TestCase::Operator::Increment->post_inc_var);
  ok(SPVM::TestCase::Operator::Increment->post_inc_element_access_constant_index);
  ok(SPVM::TestCase::Operator::Increment->post_inc_element_access_var_index);
  ok(SPVM::TestCase::Operator::Increment->post_inc_field_access);
  ok(SPVM::TestCase::Operator::Increment->post_inc_deref);
  ok(SPVM::TestCase::Operator::Increment->post_inc_class_var_access);
  ok(SPVM::TestCase::Operator::Increment->post_inc_array_field_access_constant_index);
  
  ok(SPVM::TestCase::Operator::Increment->post_inc_element_access_invocant_not_var);
  ok(SPVM::TestCase::Operator::Increment->post_inc_array_field_access_invocant_not_var);
  ok(SPVM::TestCase::Operator::Increment->post_inc_field_access_invocant_not_var);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);


done_testing;
