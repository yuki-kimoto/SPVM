use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::Assign';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Assign ref
{
  ok(SPVM::TestCase::Assign->assign_ref());
}

# Assign return value
{
  ok(SPVM::TestCase::Assign->assign_return_value_ref);
  ok(SPVM::TestCase::Assign->assign_return_value_value_field);
  ok(SPVM::TestCase::Assign->assign_return_value_multi_numeric_type);

  ok(SPVM::TestCase::Assign->assign_return_value_byte);
  ok(SPVM::TestCase::Assign->assign_return_value_short);
  ok(SPVM::TestCase::Assign->assign_return_value_int);
  ok(SPVM::TestCase::Assign->assign_return_value_long);
  ok(SPVM::TestCase::Assign->assign_return_value_float);
  ok(SPVM::TestCase::Assign->assign_return_value_double);
  ok(SPVM::TestCase::Assign->assign_return_value_object);

  ok(SPVM::TestCase::Assign->assign_return_value_var);
  ok(SPVM::TestCase::Assign->assign_return_value_constant);

  ok(SPVM::TestCase::Assign->assign_return_value_array_access_right_var);
  ok(SPVM::TestCase::Assign->assign_return_value_array_access_right_not_var);
  ok(SPVM::TestCase::Assign->assign_return_value_array_access_left_var);
  ok(SPVM::TestCase::Assign->assign_return_value_array_access_chain);
  
  ok(SPVM::TestCase::Assign->assign_return_value_field_access);

  ok(SPVM::TestCase::Assign->assign_return_value_my_var);
}
{
  ok(SPVM::TestCase::Assign->assign);

  ok(SPVM::TestCase::Assign->assign_numeric_to_string);

  ok(SPVM::TestCase::Assign->assign_byte_to_byte_object);
  ok(SPVM::TestCase::Assign->assign_short_to_short_object);
  ok(SPVM::TestCase::Assign->assign_int_to_int_object);
  ok(SPVM::TestCase::Assign->assign_long_to_long_object);
  ok(SPVM::TestCase::Assign->assign_float_to_float_object);
  ok(SPVM::TestCase::Assign->assign_double_to_double_object);

  ok(SPVM::TestCase::Assign->assign_byte_to_any_object);
  ok(SPVM::TestCase::Assign->assign_short_to_any_object);
  ok(SPVM::TestCase::Assign->assign_int_to_any_object);
  ok(SPVM::TestCase::Assign->assign_long_to_any_object);
  ok(SPVM::TestCase::Assign->assign_float_to_any_object);
  ok(SPVM::TestCase::Assign->assign_double_to_any_object);

  ok(SPVM::TestCase::Assign->assign_byte_object_to_byte);
  ok(SPVM::TestCase::Assign->assign_short_object_to_short);
  ok(SPVM::TestCase::Assign->assign_int_object_to_int);
  ok(SPVM::TestCase::Assign->assign_long_object_to_long);
  ok(SPVM::TestCase::Assign->assign_float_object_to_float);
  ok(SPVM::TestCase::Assign->assign_double_object_to_double);

  ok(SPVM::TestCase::Assign->assign_any_object_to_byte);
  ok(SPVM::TestCase::Assign->assign_any_object_to_short);
  ok(SPVM::TestCase::Assign->assign_any_object_to_int);
  ok(SPVM::TestCase::Assign->assign_any_object_to_long);
  ok(SPVM::TestCase::Assign->assign_any_object_to_float);
  ok(SPVM::TestCase::Assign->assign_any_object_to_double);
  
  ok(SPVM::TestCase::Assign->assign_undef_to_numeric_object);

}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
