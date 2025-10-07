use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::Increment';



# Start objects count
my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Pre dec
{
  ok(SPVM::TestCase::Operator::Increment->pre_dec_var);
  ok(SPVM::TestCase::Operator::Increment->pre_dec_element_access_constant_index);
  ok(SPVM::TestCase::Operator::Increment->pre_dec_element_access_var_index);
  ok(SPVM::TestCase::Operator::Increment->pre_dec_field_access);
  ok(SPVM::TestCase::Operator::Increment->pre_dec_deref);
  ok(SPVM::TestCase::Operator::Increment->pre_dec_class_var_access);
  ok(SPVM::TestCase::Operator::Increment->pre_dec_array_field_access_constant_index);
  
  ok(SPVM::TestCase::Operator::Increment->pre_dec_element_access_invocant_not_var);
  ok(SPVM::TestCase::Operator::Increment->pre_dec_array_field_access_invocant_not_var);
  ok(SPVM::TestCase::Operator::Increment->pre_dec_field_access_invocant_not_var);
}

# Post dec
{
  ok(SPVM::TestCase::Operator::Increment->post_dec_var);
  ok(SPVM::TestCase::Operator::Increment->post_dec_element_access_constant_index);
  ok(SPVM::TestCase::Operator::Increment->post_dec_element_access_var_index);
  ok(SPVM::TestCase::Operator::Increment->post_dec_field_access);
  ok(SPVM::TestCase::Operator::Increment->post_dec_deref);
  ok(SPVM::TestCase::Operator::Increment->post_dec_class_var_access);
  ok(SPVM::TestCase::Operator::Increment->post_dec_array_field_access_constant_index);
  
  ok(SPVM::TestCase::Operator::Increment->post_dec_element_access_invocant_not_var);
  ok(SPVM::TestCase::Operator::Increment->post_dec_array_field_access_invocant_not_var);
  ok(SPVM::TestCase::Operator::Increment->post_dec_field_access_invocant_not_var);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);


done_testing;
