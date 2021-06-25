use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Method';



my $BYTE_MAX = 127;
my $BYTE_MIN = -128;
my $SHORT_MAX = 32767;
my $SHORT_MIN = -32768;
my $INT_MAX = 2147483647;
my $INT_MIN = -2147483648;
my $LONG_MAX = 9223372036854775807;
my $LONG_MIN = -9223372036854775808;
my $FLOAT_PRECICE = 16384.5;
my $DOUBLE_PRECICE = 65536.5;

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Import sub
{
  ok(TestCase::Method->test_import_method);
}

# Retrun value automatical numeric convertion
{
  ok(TestCase::Method->return_value_automatical_numeric_convertion);
}
# variable length arguments
{
  ok(TestCase::Method->vaarg_objects_pass_each_values);
  ok(TestCase::Method->vaarg_objects_pass_array);
  ok(TestCase::Method->vaarg_pass_each_values);
  ok(TestCase::Method->vaarg_pass_array);
  ok(TestCase::Method->vaarg_objects_pass_empty);
}

# Anon sub
{
  ok(TestCase::Method->cb_obj_capture);
  ok(TestCase::Method->cb_obj_call_cb_obj);
  ok(TestCase::Method->cb_obj_call_cb_obj_from_callback);
}

# Return value
{
  ok(TestCase::Method->return_value_byte);
  ok(TestCase::Method->return_value_short);
  ok(TestCase::Method->return_value_int);
  ok(TestCase::Method->return_value_long);
  ok(TestCase::Method->return_value_float);
  ok(TestCase::Method->return_value_double);
}

{
  ok(TestCase::Method->push_arg_undef());
}

# Call method
{
  ok(TestCase::Method->call_spvm_method_last_camma());
  ok(TestCase::Method->call_spvm_method_undef(undef));
}

# Call void method
{
  ok(TestCase::Method->call_void());
}

# Default return value
{
  ok(TestCase::Method->default_return_value_byte());
  ok(TestCase::Method->default_return_value_short());
  ok(TestCase::Method->default_return_value_int());
  ok(TestCase::Method->default_return_value_long());
  ok(TestCase::Method->default_return_value_float());
  ok(TestCase::Method->default_return_value_double());
  ok(TestCase::Method->default_return_value_object());
}

{
  ok(TestCase::Method->call_spvm_method_nest());
}

# Argument convetion
{
  ok(TestCase::Method->call_spvm_method_args_convertion());
}


# call_spvm_method array
{
  # call_spvm_method
  {
    ok(TestCase::Method->call_spvm_method_args_byte(0, $BYTE_MAX, $BYTE_MIN));
    ok(TestCase::Method->call_spvm_method_args_short(0, $SHORT_MAX, $SHORT_MIN));
    ok(TestCase::Method->call_spvm_method_args_int(0, $INT_MAX, $INT_MIN));
    ok(TestCase::Method->call_spvm_method_args_long(0, $LONG_MAX, $LONG_MIN));
  }
}

{
  # call_spvm_method barray
  {
    my $sp_values = SPVM::new_byte_array([1, 2, 3]);
    is(TestCase::Method->call_spvm_method_byte_array($sp_values), 6);
  }

  # call_spvm_method sarray
  {
    my $sp_values = SPVM::new_short_array([1, 2, 3]);
    is(TestCase::Method->call_spvm_method_short_array($sp_values), 6);
  }

  # call_spvm_method iarray
  {
    my $sp_values = SPVM::new_int_array([1, 2, 3]);
    is(TestCase::Method->call_spvm_method_int_array($sp_values), 6);
  }

  # call_spvm_method larray
  {
    my $sp_values = SPVM::new_long_array([1, 2, 3]);
    is(TestCase::Method->call_spvm_method_long_array($sp_values), 6);
  }

  # call_spvm_method farray
  {
    my $sp_values = SPVM::new_float_array([0.5, 0.5, 1.0]);
    is(TestCase::Method->call_spvm_method_float_array($sp_values), 2.0);
  }

  # call_spvm_method darray
  {
    my $sp_values = SPVM::new_double_array([0.5, 0.5, 1.0]);
    is(TestCase::Method->call_spvm_method_double_array($sp_values), 2.0);
  }
}

{
  {
    my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
    TestCase::Method->call_spvm_method_assign();
    my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
    is($start_memory_blocks_count, $end_memory_blocks_count);
  }
}

# call_spvm_method return array
{
  {
    my $sp_values = TestCase::Method->call_spvm_method_return_byte_array();
    TestCase::Method->call_spvm_method_return_byte_array_check($sp_values);
  }
  {
    my $sp_values = TestCase::Method->call_spvm_method_return_short_array();
    TestCase::Method->call_spvm_method_return_short_array_check($sp_values);
  }
  {
    my $sp_values = TestCase::Method->call_spvm_method_return_int_array();
    TestCase::Method->call_spvm_method_return_int_array_check($sp_values);
  }
  {
    my $sp_values = TestCase::Method->call_spvm_method_return_long_array();
    TestCase::Method->call_spvm_method_return_long_array_check($sp_values);
  }
  {
    my $sp_values = TestCase::Method->call_spvm_method_return_float_array();
    TestCase::Method->call_spvm_method_return_float_array_check($sp_values);
  }
  {
    my $sp_values = TestCase::Method->call_spvm_method_return_double_array();
    TestCase::Method->call_spvm_method_return_double_array_check($sp_values);
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
