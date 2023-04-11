use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use Config;

use Test::More;

use SPVM 'TestCase::Method';

my $build_dir = $ENV{SPVM_BUILD_DIR};

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
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

{
  ok(SPVM::TestCase::Method->call_keyword_name_method);
}

# Import method
{
  ok(SPVM::TestCase::Method->test_import_method);
}

# Retrun value automatical numeric convertion
{
  ok(SPVM::TestCase::Method->return_mulnum_automatical_numeric_convertion);
}
# variable length arguments
{
  ok(SPVM::TestCase::Method->vaarg_objects_pass_each_values);
  ok(SPVM::TestCase::Method->vaarg_objects_pass_array);
  ok(SPVM::TestCase::Method->vaarg_pass_each_values);
  ok(SPVM::TestCase::Method->vaarg_pass_array);
  ok(SPVM::TestCase::Method->vaarg_objects_pass_empty);
}

# Anon method
{
  ok(SPVM::TestCase::Method->cb_obj_capture);
  ok(SPVM::TestCase::Method->cb_obj_call_cb_obj);
  ok(SPVM::TestCase::Method->cb_obj_call_cb_obj_from_callback);
}

# Argument multi-numeric type
{
  ok(SPVM::TestCase::Method->test_arg_byte);
  ok(SPVM::TestCase::Method->test_arg_short);
  ok(SPVM::TestCase::Method->test_arg_int);
  ok(SPVM::TestCase::Method->test_arg_long);
  ok(SPVM::TestCase::Method->test_arg_float);
  ok(SPVM::TestCase::Method->test_arg_double);
  ok(SPVM::TestCase::Method->test_arg_object);
  ok(SPVM::TestCase::Method->test_arg_ref);
}

# Argument multi-numeric type
{
  ok(SPVM::TestCase::Method->test_arg_mulnum_byte);
  ok(SPVM::TestCase::Method->test_arg_mulnum_short);
  ok(SPVM::TestCase::Method->test_arg_mulnum_int);
  ok(SPVM::TestCase::Method->test_arg_mulnum_long);
  ok(SPVM::TestCase::Method->test_arg_mulnum_float);
  ok(SPVM::TestCase::Method->test_arg_mulnum_double);
  ok(SPVM::TestCase::Method->test_arg_mulnum_ref);
}

# Return value
{
  ok(SPVM::TestCase::Method->return_mulnum_byte);
  ok(SPVM::TestCase::Method->return_mulnum_short);
  ok(SPVM::TestCase::Method->return_mulnum_int);
  ok(SPVM::TestCase::Method->return_mulnum_long);
  ok(SPVM::TestCase::Method->return_mulnum_float);
  ok(SPVM::TestCase::Method->return_mulnum_double);
}

{
  ok(SPVM::TestCase::Method->push_arg_undef);
}

# Call method
{
  ok(SPVM::TestCase::Method->call_method_last_camma);
  ok(SPVM::TestCase::Method->call_method_undef(undef));
}

# Call void method
{
  ok(SPVM::TestCase::Method->call_void);
}

# Default return value
{
  ok(SPVM::TestCase::Method->default_return_mulnum_byte);
  ok(SPVM::TestCase::Method->default_return_mulnum_short);
  ok(SPVM::TestCase::Method->default_return_mulnum_int);
  ok(SPVM::TestCase::Method->default_return_mulnum_long);
  ok(SPVM::TestCase::Method->default_return_mulnum_float);
  ok(SPVM::TestCase::Method->default_return_mulnum_double);
  ok(SPVM::TestCase::Method->default_return_mulnum_object);
}

{
  ok(SPVM::TestCase::Method->call_method_nest);
}

# Argument convetion
{
  ok(SPVM::TestCase::Method->call_method_args_convertion);
}


# call_method array
{
  # call_method
  {
    ok(SPVM::TestCase::Method->call_method_args_byte(0, $BYTE_MAX, $BYTE_MIN));
    ok(SPVM::TestCase::Method->call_method_args_short(0, $SHORT_MAX, $SHORT_MIN));
    ok(SPVM::TestCase::Method->call_method_args_int(0, $INT_MAX, $INT_MIN));
    ok(SPVM::TestCase::Method->call_method_args_long(0, $LONG_MAX, $LONG_MIN));
  }
}

{
  # call_method barray
  {
    my $sp_values = SPVM::api->new_byte_array([1, 2, 3]);
    is(SPVM::TestCase::Method->call_method_byte_array($sp_values), 6);
  }

  # call_method sarray
  {
    my $sp_values = SPVM::api->new_short_array([1, 2, 3]);
    is(SPVM::TestCase::Method->call_method_short_array($sp_values), 6);
  }

  # call_method iarray
  {
    my $sp_values = SPVM::api->new_int_array([1, 2, 3]);
    is(SPVM::TestCase::Method->call_method_int_array($sp_values), 6);
  }

  # call_method larray
  {
    my $sp_values = SPVM::api->new_long_array([1, 2, 3]);
    is(SPVM::TestCase::Method->call_method_long_array($sp_values), 6);
  }

  # call_method farray
  {
    my $sp_values = SPVM::api->new_float_array([0.5, 0.5, 1.0]);
    is(SPVM::TestCase::Method->call_method_float_array($sp_values), 2.0);
  }

  # call_method darray
  {
    my $sp_values = SPVM::api->new_double_array([0.5, 0.5, 1.0]);
    is(SPVM::TestCase::Method->call_method_double_array($sp_values), 2.0);
  }
}

{
  {
    my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();
    SPVM::TestCase::Method->call_method_assign();
    my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
    is($start_memory_blocks_count, $end_memory_blocks_count);
  }
}

# call_method return array
{
  {
    my $sp_values = SPVM::TestCase::Method->call_method_return_byte_array();
    SPVM::TestCase::Method->call_method_return_byte_array_check($sp_values);
  }
  {
    my $sp_values = SPVM::TestCase::Method->call_method_return_short_array();
    SPVM::TestCase::Method->call_method_return_short_array_check($sp_values);
  }
  {
    my $sp_values = SPVM::TestCase::Method->call_method_return_int_array();
    SPVM::TestCase::Method->call_method_return_int_array_check($sp_values);
  }
  {
    my $sp_values = SPVM::TestCase::Method->call_method_return_long_array();
    SPVM::TestCase::Method->call_method_return_long_array_check($sp_values);
  }
  {
    my $sp_values = SPVM::TestCase::Method->call_method_return_float_array();
    SPVM::TestCase::Method->call_method_return_float_array_check($sp_values);
  }
  {
    my $sp_values = SPVM::TestCase::Method->call_method_return_double_array();
    SPVM::TestCase::Method->call_method_return_double_array_check($sp_values);
  }
}

# The max length of arguments
{
  {
    my $ret = SPVM::TestCase::Method->args_max_count((1) x 254, 2);
    is($ret, 2);
  }
  {
    my $ret = SPVM::TestCase::Method->args_max_count_mulnum((1) x 253, {re => 2, im => 3});
    is_deeply($ret, {re => 2, im => 3});
  }
}

# precompile method
{
  # Check precompile class file
  {
    my $precompile_class_file = "$build_dir/work/lib/SPVM/TestCase/Method.precompile.$Config{dlext}";
    ok(-f $precompile_class_file);
  }
  
  # Call precompile method
  {
    my $ret = SPVM::TestCase::Method->precompile_sum(2, 3);
    is($ret, 5);
  }
}

# Deep recursion
{
  # ok(SPVM::TestCase::Method->deep_recursion);
  1;
}

# Optional arguments
{
  ok(SPVM::TestCase::Method->optional_args);
}

# items
{
  ok(SPVM::TestCase::Method->items);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
