use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::Assign';

use SPVM 'TestCase::Operator::Move';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Simple assign
{
  {
    ok(SPVM::TestCase::Operator::Move->move_constant_byte);
    ok(SPVM::TestCase::Operator::Move->move_constant_int);
    ok(SPVM::TestCase::Operator::Move->move_constant_long);
    ok(SPVM::TestCase::Operator::Move->move_constant_float);
    ok(SPVM::TestCase::Operator::Move->move_constant_double);
    ok(SPVM::TestCase::Operator::Move->move_byte);
    ok(SPVM::TestCase::Operator::Move->move_short);
    ok(SPVM::TestCase::Operator::Move->move_int);
    ok(SPVM::TestCase::Operator::Move->move_long);
    ok(SPVM::TestCase::Operator::Move->move_float);
    ok(SPVM::TestCase::Operator::Move->move_double);
    ok(SPVM::TestCase::Operator::Move->move_object);
    ok(SPVM::TestCase::Operator::Move->move_ref);
  }
}

# Assign ref
{
  ok(SPVM::TestCase::Operator::Assign->assign_ref());
}

# Assign return value
{
  ok(SPVM::TestCase::Operator::Assign->assign_return_value_ref);
  ok(SPVM::TestCase::Operator::Assign->assign_return_value_value_field);
  ok(SPVM::TestCase::Operator::Assign->assign_return_value_multi_numeric_type);

  ok(SPVM::TestCase::Operator::Assign->assign_return_value_byte);
  ok(SPVM::TestCase::Operator::Assign->assign_return_value_short);
  ok(SPVM::TestCase::Operator::Assign->assign_return_value_int);
  ok(SPVM::TestCase::Operator::Assign->assign_return_value_long);
  ok(SPVM::TestCase::Operator::Assign->assign_return_value_float);
  ok(SPVM::TestCase::Operator::Assign->assign_return_value_double);
  ok(SPVM::TestCase::Operator::Assign->assign_return_value_object);

  ok(SPVM::TestCase::Operator::Assign->assign_return_value_var);
  ok(SPVM::TestCase::Operator::Assign->assign_return_value_constant);

  ok(SPVM::TestCase::Operator::Assign->assign_return_value_element_access_right_var);
  ok(SPVM::TestCase::Operator::Assign->assign_return_value_element_access_right_not_var);
  ok(SPVM::TestCase::Operator::Assign->assign_return_value_element_access_left_var);
  ok(SPVM::TestCase::Operator::Assign->assign_return_value_element_access_chain);
  
  ok(SPVM::TestCase::Operator::Assign->assign_return_value_field_access);

  ok(SPVM::TestCase::Operator::Assign->assign_return_value_my_var);
}
{
  ok(SPVM::TestCase::Operator::Assign->assign);

  ok(SPVM::TestCase::Operator::Assign->assign_numeric_to_string);

  ok(SPVM::TestCase::Operator::Assign->assign_byte_to_byte_object);
  ok(SPVM::TestCase::Operator::Assign->assign_short_to_short_object);
  ok(SPVM::TestCase::Operator::Assign->assign_int_to_int_object);
  ok(SPVM::TestCase::Operator::Assign->assign_long_to_long_object);
  ok(SPVM::TestCase::Operator::Assign->assign_float_to_float_object);
  ok(SPVM::TestCase::Operator::Assign->assign_double_to_double_object);

  ok(SPVM::TestCase::Operator::Assign->assign_byte_to_any_object);
  ok(SPVM::TestCase::Operator::Assign->assign_short_to_any_object);
  ok(SPVM::TestCase::Operator::Assign->assign_int_to_any_object);
  ok(SPVM::TestCase::Operator::Assign->assign_long_to_any_object);
  ok(SPVM::TestCase::Operator::Assign->assign_float_to_any_object);
  ok(SPVM::TestCase::Operator::Assign->assign_double_to_any_object);

  ok(SPVM::TestCase::Operator::Assign->assign_byte_object_to_byte);
  ok(SPVM::TestCase::Operator::Assign->assign_short_object_to_short);
  ok(SPVM::TestCase::Operator::Assign->assign_int_object_to_int);
  ok(SPVM::TestCase::Operator::Assign->assign_long_object_to_long);
  ok(SPVM::TestCase::Operator::Assign->assign_float_object_to_float);
  ok(SPVM::TestCase::Operator::Assign->assign_double_object_to_double);

  ok(SPVM::TestCase::Operator::Assign->assign_any_object_to_byte);
  ok(SPVM::TestCase::Operator::Assign->assign_any_object_to_short);
  ok(SPVM::TestCase::Operator::Assign->assign_any_object_to_int);
  ok(SPVM::TestCase::Operator::Assign->assign_any_object_to_long);
  ok(SPVM::TestCase::Operator::Assign->assign_any_object_to_float);
  ok(SPVM::TestCase::Operator::Assign->assign_any_object_to_double);
  
  ok(SPVM::TestCase::Operator::Assign->assign_undef_to_numeric_object);
  ok(SPVM::TestCase::Operator::Assign->assign_undef_to_ref);
  ok(SPVM::TestCase::Operator::Assign->assign_cannot_assign);
  ok(SPVM::TestCase::Operator::Assign->to_mulnum);

}

# Spec tests
{
  ok(SPVM::TestCase::Operator::Assign->evaluate_left_to_right);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
