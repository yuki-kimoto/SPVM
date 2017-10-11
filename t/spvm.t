use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;

use Test::More 'no_plan';

my $file = 't/' . basename $0;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase'; my $use_test_line = __LINE__;
use SPVM 'std'; my $use_std_line = __LINE__;

use SPVM 'TestCase::Extension';
use SPVM 'TestCase::Extension2';
use SPVM 'TestCase::Arrays';

use POSIX ();

use SPVM::Object::Package;

my $BYTE_MAX = 127;
my $BYTE_MIN = -128;
my $SHORT_MAX = 32767;
my $SHORT_MIN = -32768;
my $INT_MAX = 2147483647;
my $INT_MIN = -2147483648;
my $LONG_MAX = 9223372036854775807;
my $LONG_MIN = -9223372036854775808;
my $FLOAT_MAX = POSIX::FLT_MAX();
my $FLOAT_MIN = POSIX::FLT_MIN();
my $DOUBLE_MAX = POSIX::DBL_MAX();
my $DOUBLE_MIN = POSIX::DBL_MIN();
my $FLOAT_PRECICE = 16384.5;
my $DOUBLE_PRECICE = 65536.5;

# Positive infinity(unix like system : inf, Windows : 1.#INF)
my $POSITIVE_INFINITY = SPVM::POSITIVE_INFINITY();

# Negative infinity(unix like system : -inf, Windows : -1.#INF)
my $NEGATIVE_INFINITY = SPVM::NEGATIVE_INFINITY();

my $NaN = SPVM::NaN();

use SPVM 'Double';
use SPVM 'Float';
use SPVM 'std';

# time
{
  cmp_ok(abs(time - SPVM::std::time()), '<', 2);
}

# Native Exception
{
  ok(SPVM::TestCase::Extension::call_void_sub_exception());
  ok(SPVM::TestCase::Extension::call_byte_sub_exception());
  ok(SPVM::TestCase::Extension::call_short_sub_exception());
  ok(SPVM::TestCase::Extension::call_int_sub_exception());
  ok(SPVM::TestCase::Extension::call_long_sub_exception());
  ok(SPVM::TestCase::Extension::call_float_sub_exception());
  ok(SPVM::TestCase::Extension::call_double_sub_exception());
  ok(SPVM::TestCase::Extension::call_object_sub_exception());
}

# SPVM::Arrays;
{
  ok(SPVM::TestCase::Arrays::equals_byte());

  ok(SPVM::TestCase::Arrays::copy_of_byte());
  ok(SPVM::TestCase::Arrays::copy_of_byte_over());
  ok(SPVM::TestCase::Arrays::copy_of_byte_less());
  ok(SPVM::TestCase::Arrays::copy_of_byte_undef());
  ok(SPVM::TestCase::Arrays::copy_of_byte_negative());

  ok(SPVM::TestCase::Arrays::copy_of_short());
  ok(SPVM::TestCase::Arrays::copy_of_short_over());
  ok(SPVM::TestCase::Arrays::copy_of_short_less());
  ok(SPVM::TestCase::Arrays::copy_of_short_undef());
  ok(SPVM::TestCase::Arrays::copy_of_short_negative());

  ok(SPVM::TestCase::Arrays::copy_of_int());
  ok(SPVM::TestCase::Arrays::copy_of_int_over());
  ok(SPVM::TestCase::Arrays::copy_of_int_less());
  ok(SPVM::TestCase::Arrays::copy_of_int_undef());
  ok(SPVM::TestCase::Arrays::copy_of_int_negative());

  ok(SPVM::TestCase::Arrays::copy_of_long());
  ok(SPVM::TestCase::Arrays::copy_of_long_over());
  ok(SPVM::TestCase::Arrays::copy_of_long_less());
  ok(SPVM::TestCase::Arrays::copy_of_long_undef());
  ok(SPVM::TestCase::Arrays::copy_of_long_negative());

  ok(SPVM::TestCase::Arrays::copy_of_float());
  ok(SPVM::TestCase::Arrays::copy_of_float_over());
  ok(SPVM::TestCase::Arrays::copy_of_float_less());
  ok(SPVM::TestCase::Arrays::copy_of_float_undef());
  ok(SPVM::TestCase::Arrays::copy_of_float_negative());

  ok(SPVM::TestCase::Arrays::copy_of_double());
  ok(SPVM::TestCase::Arrays::copy_of_double_over());
  ok(SPVM::TestCase::Arrays::copy_of_double_less());
  ok(SPVM::TestCase::Arrays::copy_of_double_undef());
  ok(SPVM::TestCase::Arrays::copy_of_double_negative());
  1;
}

{
  like($POSITIVE_INFINITY, qr/inf/i);
  cmp_ok($POSITIVE_INFINITY, '>', 0);
  
  like($NEGATIVE_INFINITY, qr/inf/i);
  cmp_ok($NEGATIVE_INFINITY, '<', 0);
  
  like($NaN, qr/(nan|ind)/i);
}

# Template
{
  ok(SPVM::TestCase::template());
}

# SPVM::Byte
{
  ok(SPVM::TestCase::Byte::constant());
}

# SPVM::Short
{
  ok(SPVM::TestCase::Short::constant());
}

# SPVM::Integer
{
  ok(SPVM::TestCase::Integer::constant());
}

# SPVM::Long
{
  ok(SPVM::TestCase::Long::constant());
}

# SPVM::Float
{
  ok(SPVM::TestCase::Float::pass_positive_infinity($POSITIVE_INFINITY));
  ok(SPVM::TestCase::Float::pass_negative_infinity($NEGATIVE_INFINITY));
  ok(SPVM::TestCase::Float::pass_nan($NaN));
  
  ok(SPVM::TestCase::Float::constant());
  ok(SPVM::TestCase::Float::is_infinite());
  ok(SPVM::TestCase::Float::is_finite());
  ok(SPVM::TestCase::Float::is_nan());
  ok(SPVM::TestCase::Float::int_bits_to_float());
  ok(SPVM::TestCase::Float::int_bits_to_float_nan_first_condition());
  ok(SPVM::TestCase::Float::int_bits_to_float_nan_first_condition_is_nan());
  ok(SPVM::TestCase::Float::int_bits_to_float_nan_second_condition());
  ok(SPVM::TestCase::Float::int_bits_to_float_nan_second_condition_is_nan());

  ok(SPVM::TestCase::Float::float_to_raw_int_bits());
  ok(SPVM::TestCase::Float::float_to_raw_int_bits_nan());
  ok(SPVM::TestCase::Float::float_to_int_bits());
  ok(SPVM::TestCase::Float::float_to_int_bits_nan());
  
  is(SPVM::Float::POSITIVE_INFINITY(), $POSITIVE_INFINITY);
  is(SPVM::Float::NEGATIVE_INFINITY(), $NEGATIVE_INFINITY);
  
  cmp_ok(SPVM::Float::NaN(), 'eq', $NaN);
  
  # Check not Inf or NaN in Perl value
  like(SPVM::Float::MAX_VALUE(), qr/[0-9]/);
  like(SPVM::Float::MIN_VALUE(), qr/[0-9]/);
  like(SPVM::Float::MIN_NORMAL(), qr/[0-9]/);
}

# SPVM::Double
{
  ok(SPVM::TestCase::Double::pass_positive_infinity($POSITIVE_INFINITY));
  ok(SPVM::TestCase::Double::pass_negative_infinity($NEGATIVE_INFINITY));
  ok(SPVM::TestCase::Double::pass_nan($NaN));
  
  ok(SPVM::TestCase::Double::constant());
  ok(SPVM::TestCase::Double::is_infinite());
  ok(SPVM::TestCase::Double::is_finite());
  ok(SPVM::TestCase::Double::is_nan());
  ok(SPVM::TestCase::Double::long_bits_to_double());
  ok(SPVM::TestCase::Double::long_bits_to_double_nan_first_condition());
  ok(SPVM::TestCase::Double::long_bits_to_double_nan_first_condition_is_nan());
  ok(SPVM::TestCase::Double::long_bits_to_double_nan_second_condition());
  ok(SPVM::TestCase::Double::long_bits_to_double_nan_second_condition_is_nan());
  
  ok(SPVM::TestCase::Double::double_to_raw_long_bits());
  ok(SPVM::TestCase::Double::double_to_raw_long_bits_nan());
  ok(SPVM::TestCase::Double::double_to_long_bits());
  ok(SPVM::TestCase::Double::double_to_long_bits_nan());
  
  is(SPVM::Double::POSITIVE_INFINITY(), $POSITIVE_INFINITY);
  is(SPVM::Double::NEGATIVE_INFINITY(), $NEGATIVE_INFINITY);
  
  cmp_ok(SPVM::Double::NaN(), 'eq', $NaN);
  
  # Check not Inf or NaN in Perl value
  like(SPVM::Double::MAX_VALUE(), qr/[0-9]/);
  like(SPVM::Double::MIN_VALUE(), qr/[0-9]/);
  like(SPVM::Double::MIN_NORMAL(), qr/[0-9]/);
}

# .
{
  {
    is("ab", SPVM::TestCase::concat_string_special_assign()->to_data);
    is("ab", SPVM::TestCase::concat_string_string()->to_data);
    is("a3", SPVM::TestCase::concat_string_byte()->to_data);
    is("a3", SPVM::TestCase::concat_string_short()->to_data);
    is("a3", SPVM::TestCase::concat_string_int()->to_data);
    is("a3", SPVM::TestCase::concat_string_long()->to_data);
    is("a3.000000", SPVM::TestCase::concat_string_float()->to_data);
    is("a3.000000", SPVM::TestCase::concat_string_double()->to_data);
  }
}

# String
{
  {
    my $values = SPVM::TestCase::string_empty();
    is($values->to_data, "");
  }
  
  {
    my $values = SPVM::TestCase::string_utf8();
    is($values->to_string, "あいうえお");
  }
}

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Call subroutine
{
  ok(SPVM::TestCase::sin());
  ok(SPVM::TestCase::cos());
  ok(SPVM::TestCase::tan());
}

# Native subroutine
{
  my $sp_values = SPVM::new_int_array([1, 2, 3]);
  my $total = SPVM::std::sum_int($sp_values);
  is($total, 6);
}

# Call subroutine
{
  ok(SPVM::TestCase::call_sub_last_camma());
  ok(SPVM::TestCase::call_sub_undef(undef));
}

# Destructor
{
  ok(SPVM::TestCase::destructor());
}

# Weaken
{
  {
    my $start_objects_count = SPVM::get_objects_count();
    {
      ok(SPVM::TestCase::weaken_target4_weaken_object_assign());
    }
    my $end_objects_count = SPVM::get_objects_count();
    is($end_objects_count, $start_objects_count);
  }
  {
    my $start_objects_count = SPVM::get_objects_count();
    {
      ok(SPVM::TestCase::weaken_target4());
    }
    my $end_objects_count = SPVM::get_objects_count();
    is($end_objects_count, $start_objects_count);
  }
  {
    my $start_objects_count = SPVM::get_objects_count();
    {
      ok(SPVM::TestCase::weaken_weaken_object_undef());
    }
    my $end_objects_count = SPVM::get_objects_count();
    is($end_objects_count, $start_objects_count);
  }
  {
    my $start_objects_count = SPVM::get_objects_count();
    {
      ok(SPVM::TestCase::weaken_target_object_undef());
    }
    my $end_objects_count = SPVM::get_objects_count();
    is($end_objects_count, $start_objects_count);
  }
  {
    my $start_objects_count = SPVM::get_objects_count();
    {
      SPVM::TestCase::weaken_recursive3();
    }
    my $end_objects_count = SPVM::get_objects_count();
    is($end_objects_count, $start_objects_count);
  }
  {
    my $start_objects_count = SPVM::get_objects_count();
    {
      SPVM::TestCase::weaken_recursive_again();
    }
    my $end_objects_count = SPVM::get_objects_count();
    is($end_objects_count, $start_objects_count);
  }
  {
    my $start_objects_count = SPVM::get_objects_count();
    {
      ok(SPVM::TestCase::weaken_recursive());
    }
    my $end_objects_count = SPVM::get_objects_count();
    is($end_objects_count, $start_objects_count);
  }
  {
    my $start_objects_count = SPVM::get_objects_count();
    {
      ok(SPVM::TestCase::weaken_reference_count1_object());
    }
    my $end_objects_count = SPVM::get_objects_count();
    is($end_objects_count, $start_objects_count);
  }
  {
    my $start_objects_count = SPVM::get_objects_count();
    {
      ok(SPVM::TestCase::weaken_self_recuresive());
    }
    my $end_objects_count = SPVM::get_objects_count();
    is($end_objects_count, $start_objects_count);
  }
}

# Exception
{
  {
    ok(SPVM::TestCase::exception_eval_call_sub());
  }
  
  {
    eval { SPVM::TestCase::exception_call_stack() };
    like($@, qr/Error/);
    like($@, qr/exception_croak_return_int/);
    like($@, qr/exception_call_stack/);
  }

  {
    eval { SPVM::TestCase::exception_croak_return_byte() };
    like($@, qr/Error/);
    like($@, qr/exception_croak_return_byte/);
  }
  {
    eval { SPVM::TestCase::exception_croak_return_short() };
    like($@, qr/Error/);
  }
  {
    eval { SPVM::TestCase::exception_croak_return_int() };
    like($@, qr/Error/);
    like($@, qr/exception_croak_return_int/);
    like($@, qr/TestCase\.spvm/);
  }
  {
    eval { SPVM::TestCase::exception_croak_return_long() };
    like($@, qr/Error/);
  }
  {
    eval { SPVM::TestCase::exception_croak_return_float() };
    like($@, qr/Error/);
  }
  {
    eval { SPVM::TestCase::exception_croak_return_double() };
    like($@, qr/Error/);
  }
  {
    eval { SPVM::TestCase::exception_croak_return_object() };
    like($@, qr/Error/);
  }
  {
    eval { SPVM::TestCase::exception_croak_return_void() };
    like($@, qr/Error/);
  }
  
  {
    ok(SPVM::TestCase::exception_croak_return_int_eval_catch());
  }
}

# Call void subroutine
{
  ok(SPVM::TestCase::call_void());
}

# Array default
{
  ok(SPVM::TestCase::array_default_zero_memory_pool());
  ok(SPVM::TestCase::array_default_zero_not_memory_pool());
}

# Array initialization
{
  ok(SPVM::TestCase::array_init_byte());
  ok(SPVM::TestCase::array_init_short());
  ok(SPVM::TestCase::array_init_int());
  ok(SPVM::TestCase::array_init_long());
  ok(SPVM::TestCase::array_init_float());
  ok(SPVM::TestCase::array_init_double());
}

# Exception
{
  eval { SPVM::TestCase::exception_zero_divide_int() }; my $line = __LINE__;
  like($@, qr|\Q0 division (int / int)|);
  like($@, qr/\Q$file/);
  like($@, qr/$line/);
}

# Default return value
{
  ok(SPVM::TestCase::default_return_value_byte());
  ok(SPVM::TestCase::default_return_value_short());
  ok(SPVM::TestCase::default_return_value_int());
  ok(SPVM::TestCase::default_return_value_long());
  ok(SPVM::TestCase::default_return_value_float());
  ok(SPVM::TestCase::default_return_value_double());
  ok(SPVM::TestCase::default_return_value_object());
}

# Switch
{
  ok(SPVM::TestCase::switch_nest());
  ok(SPVM::TestCase::switch_lookup_switch());
  ok(SPVM::TestCase::switch_table_switch());
}

{
  ok(SPVM::TestCase::my_var_initialized_zero());
}

# Field
{
  ok(SPVM::TestCase::object_field_set_and_get());
  ok(SPVM::TestCase::object_field_set_and_get_again());
}

{
  ok(SPVM::TestCase::object_field_initialized_zero());
}

{
  ok(SPVM::TestCase::new_near_small_base_object_max_byte_size_use_memory_pool());
}

# Get object from freelist
{
  ok(SPVM::TestCase::get_object_from_freelist());
}

=pod
is_deeply(
  \@SPVM::PACKAGE_INFOS,
  [
    {name => 'TestCase', file => $file, line => $use_test_line},
    {name => 'std', file => $file, line => $use_std_line}
  ]
);
=cut

# Extension 
{
  ok(SPVM::TestCase::spvm_extension());
  ok(SPVM::TestCase::spvm_extension_add_int_array());
  ok(SPVM::TestCase::spvm_extension2());
  ok(SPVM::TestCase::spvm_extension2_binding());
}

# Get object from freelist
{
  ok(SPVM::TestCase::get_object_from_freelist());
}

# Enumeration
{
  ok(SPVM::TestCase::enum_byte());
  ok(SPVM::TestCase::enum_short());
  ok(SPVM::TestCase::enum_int());
  ok(SPVM::TestCase::enum_long());
  ok(SPVM::TestCase::enum_float());
  ok(SPVM::TestCase::enum_double());

  is(SPVM::TestCase::INT_VALUE(), 127);

=pod
  is(SPVM::TestCase::BYTE_MIN(), -128);
  is(SPVM::TestCase::SHORT_MAX(), 32767);
  is(SPVM::TestCase::SHORT_MIN(), -32768);
  is(SPVM::TestCase::INT_MAX(), 2147483647);
  is(SPVM::TestCase::INT_MIN(), -2147483648);
  is(SPVM::TestCase::LONG_MAX(), 9223372036854775807);
  is(SPVM::TestCase::LONG_MIN(), -9223372036854775808);
=cut

}

# Convert type - floating point narrowing convertion
{
  ok(SPVM::TestCase::convert_float_to_byte());
  ok(SPVM::TestCase::convert_float_to_short());
  ok(SPVM::TestCase::convert_float_to_int());
  ok(SPVM::TestCase::convert_float_to_long());
  ok(SPVM::TestCase::convert_double_to_byte());
  ok(SPVM::TestCase::convert_double_to_short());
  ok(SPVM::TestCase::convert_double_to_int());
  ok(SPVM::TestCase::convert_double_to_long());
  ok(SPVM::TestCase::convert_double_to_float());
}

# Convert type - floating point widening convertion
{
  ok(SPVM::TestCase::convert_byte_to_float());
  ok(SPVM::TestCase::convert_short_to_float());
  ok(SPVM::TestCase::convert_int_to_float());
  ok(SPVM::TestCase::convert_long_to_float());
  ok(SPVM::TestCase::convert_byte_to_double());
  ok(SPVM::TestCase::convert_short_to_double());
  ok(SPVM::TestCase::convert_int_to_double());
  ok(SPVM::TestCase::convert_long_to_double());
  ok(SPVM::TestCase::convert_float_to_double());
}

# Convert type - integral number widning convertion
{
  ok(SPVM::TestCase::convert_byte_to_short_plus());
  ok(SPVM::TestCase::convert_byte_to_short_minus());
  ok(SPVM::TestCase::convert_byte_to_int_plus());
  ok(SPVM::TestCase::convert_byte_to_int_minus());
  ok(SPVM::TestCase::convert_byte_to_long_plus());
  ok(SPVM::TestCase::convert_byte_to_long_minus());
  ok(SPVM::TestCase::convert_short_to_int_plus());
  ok(SPVM::TestCase::convert_short_to_int_minus());
  ok(SPVM::TestCase::convert_short_to_long_plus());
  ok(SPVM::TestCase::convert_short_to_long_minus());
  ok(SPVM::TestCase::convert_int_to_long_plus());
  ok(SPVM::TestCase::convert_int_to_long_minus());
}

# Convert type - same type
{
  ok(SPVM::TestCase::convert_long_to_long());
  ok(SPVM::TestCase::convert_int_to_int());
  ok(SPVM::TestCase::convert_short_to_short());
  ok(SPVM::TestCase::convert_byte_to_byte());
}

# Convert type - integral number narrowing convertion
{
  ok(SPVM::TestCase::convert_long_to_int());
  ok(SPVM::TestCase::convert_long_to_short());
  ok(SPVM::TestCase::convert_long_to_byte());
  ok(SPVM::TestCase::convert_int_to_short());
  ok(SPVM::TestCase::convert_int_to_byte());
  ok(SPVM::TestCase::convert_short_to_byte());
}

# SPVM new_object_array_len
{
  # element byte array
  {
    my $object_array = SPVM::new_object_array_len("byte[]", 3);
    
    my $object1 = SPVM::new_byte_array([1, 2, 3]);
    $object_array->set(0, $object1);
    my $object2 = SPVM::new_byte_array([4, 5, 6]);
    $object_array->set(1, $object2);
    ok(SPVM::TestCase::spvm_new_object_array_len_element_byte_array($object_array));
    
    my $object1_get = $object_array->get(0);
    my $object2_get = $object_array->get(1);
    
    is_deeply($object1_get->get_elements, [1, 2, 3]);
    is_deeply($object2_get->get_elements, [4, 5, 6]);
  }

  # element short array
  {
    my $object_array = SPVM::new_object_array_len("short[]", 3);
    my $object1 = SPVM::new_short_array([1, 2, 3]);
    $object_array->set(0, $object1);
    my $object2 = SPVM::new_short_array([4, 5, 6]);
    $object_array->set(1, $object2);
    ok(SPVM::TestCase::spvm_new_object_array_len_element_short_array($object_array));
    
    my $object1_get = $object_array->get(0);
    my $object2_get = $object_array->get(1);
    
    is_deeply($object1_get->get_elements, [1, 2, 3]);
    is_deeply($object2_get->get_elements, [4, 5, 6]);
  }

  # element int array
  {
    my $object_array = SPVM::new_object_array_len("int[]", 3);
    my $object1 = SPVM::new_int_array([1, 2, 3]);
    $object_array->set(0, $object1);
    my $object2 = SPVM::new_int_array([4, 5, 6]);
    $object_array->set(1, $object2);
    ok(SPVM::TestCase::spvm_new_object_array_len_element_int_array($object_array));
    
    my $object1_get = $object_array->get(0);
    my $object2_get = $object_array->get(1);
    
    is_deeply($object1_get->get_elements, [1, 2, 3]);
    is_deeply($object2_get->get_elements, [4, 5, 6]);
  }

  # element long array
  {
    my $object_array = SPVM::new_object_array_len("long[]", 3);
    my $object1 = SPVM::new_long_array([1, 2, 3]);
    $object_array->set(0, $object1);
    my $object2 = SPVM::new_long_array([4, 5, 6]);
    $object_array->set(1, $object2);
    ok(SPVM::TestCase::spvm_new_object_array_len_element_long_array($object_array));
    
    my $object1_get = $object_array->get(0);
    my $object2_get = $object_array->get(1);
    
    is_deeply($object1_get->get_elements, [1, 2, 3]);
    is_deeply($object2_get->get_elements, [4, 5, 6]);
  }

  # element float array
  {
    my $object_array = SPVM::new_object_array_len("float[]", 3);
    my $object1 = SPVM::new_float_array([1, 2, 3]);
    $object_array->set(0, $object1);
    my $object2 = SPVM::new_float_array([4, 5, 6]);
    $object_array->set(1, $object2);
    ok(SPVM::TestCase::spvm_new_object_array_len_element_float_array($object_array));
    
    my $object1_get = $object_array->get(0);
    my $object2_get = $object_array->get(1);
    
    is_deeply($object1_get->get_elements, [1, 2, 3]);
    is_deeply($object2_get->get_elements, [4, 5, 6]);
  }

  # element double array
  {
    my $object_array = SPVM::new_object_array_len("double[]", 3);
    my $object1 = SPVM::new_double_array([1, 2, 3]);
    $object_array->set(0, $object1);
    my $object2 = SPVM::new_double_array([4, 5, 6]);
    $object_array->set(1, $object2);
    ok(SPVM::TestCase::spvm_new_object_array_len_element_double_array($object_array));
    
    my $object1_get = $object_array->get(0);
    my $object2_get = $object_array->get(1);
    
    is_deeply($object1_get->get_elements, [1, 2, 3]);
    is_deeply($object2_get->get_elements, [4, 5, 6]);
  }

  # element object array
  {
    my $object_array = SPVM::new_object_array_len("TestCase", 3);
    my $object1 = SPVM::new_object("TestCase");
    $object1->set('x_int', 1);
    $object_array->set(0, $object1);
    my $object2 = SPVM::new_object("TestCase");
    $object2->set('x_int', 2);
    $object_array->set(1, $object2);
    ok(SPVM::TestCase::spvm_new_object_array_len_element_object_array($object_array));
    
    my $object1_get = $object_array->get(0);
    my $object2_get = $object_array->get(1);
    
    is_deeply($object1_get->get('x_int'), 1);
    is_deeply($object2_get->get('x_int'), 2);
  }
}

# Create object
{
  # Create object
  {
    my $object = SPVM::new_object("TestCase");
    $object->set(x_int_array => SPVM::new_int_array([$INT_MAX, $INT_MAX]));
    $object->set(x_string => SPVM::new_byte_array_data("abc"));
    ok(SPVM::TestCase::spvm_object_set_object($object));
  }
  # Create object
  {
    my $object = SPVM::new_object("TestCase");
    $object->set(x_byte => $BYTE_MAX);
    $object->set(x_short => $SHORT_MAX);
    $object->set(x_int => $INT_MAX);
    $object->set(x_long => $LONG_MAX);
    $object->set(x_float => $FLOAT_PRECICE);
    $object->set(x_double => $DOUBLE_PRECICE);
    $object->set(x_int_array => SPVM::new_int_array([1, 2, 3, 4]));
    $object->set(x_string => SPVM::new_byte_array_string("Hello"));
    my $minimal = SPVM::new_object("TestCase::Minimal");
    $minimal->set(x => 3);
    $object->set(minimal => $minimal);
    
    ok(SPVM::TestCase::spvm_object_set($object));
    
    is($object->get('x_byte'), $BYTE_MAX);
    is($object->get('x_short'), $SHORT_MAX);
    is($object->get('x_int'), $INT_MAX);
    is($object->get('x_long'), $LONG_MAX);
    is($object->get('x_float'), $FLOAT_PRECICE);
    is($object->get('x_double'), $DOUBLE_PRECICE);
    is($object->get('minimal')->get('x'), 3);
  }
  
}

# call_sub return array
{
  {
    my $sp_values = SPVM::TestCase::call_sub_return_byte_array();
    is(ref $sp_values, 'SPVM::Object::Array::Byte');
    SPVM::TestCase::call_sub_return_byte_array_check($sp_values);
  }
  {
    my $sp_values = SPVM::TestCase::call_sub_return_short_array();
    is(ref $sp_values, 'SPVM::Object::Array::Short');
    SPVM::TestCase::call_sub_return_short_array_check($sp_values);
  }
  {
    my $sp_values = SPVM::TestCase::call_sub_return_int_array();
    is(ref $sp_values, 'SPVM::Object::Array::Int');
    SPVM::TestCase::call_sub_return_int_array_check($sp_values);
  }
  {
    my $sp_values = SPVM::TestCase::call_sub_return_long_array();
    is(ref $sp_values, 'SPVM::Object::Array::Long');
    SPVM::TestCase::call_sub_return_long_array_check($sp_values);
  }
  {
    my $sp_values = SPVM::TestCase::call_sub_return_float_array();
    is(ref $sp_values, 'SPVM::Object::Array::Float');
    SPVM::TestCase::call_sub_return_float_array_check($sp_values);
  }
  {
    my $sp_values = SPVM::TestCase::call_sub_return_double_array();
    is(ref $sp_values, 'SPVM::Object::Array::Double');
    SPVM::TestCase::call_sub_return_double_array_check($sp_values);
  }
}


# logical not
{
  ok(SPVM::TestCase::logical_not_true());
  ok(SPVM::TestCase::logical_not_false());
}

# logical or
{
  ok(SPVM::TestCase::logical_or_both_true());
  ok(SPVM::TestCase::logical_or_left_true());
  ok(SPVM::TestCase::logical_or_right_true());
  ok(SPVM::TestCase::logical_or_both_false());
}

# logical and
{
  ok(SPVM::TestCase::logical_and_both_true());
  ok(SPVM::TestCase::logical_and_left_true());
  ok(SPVM::TestCase::logical_and_right_true());
  ok(SPVM::TestCase::logical_and_both_false());
}

# Special assign
{
  ok(SPVM::TestCase::special_assign());
}
# Add
{
  is(SPVM::TestCase::add_byte_max(), 127);
  is(SPVM::TestCase::add_byte_min(), -127);
  is(SPVM::TestCase::add_byte_overflow(), -128);
  is(SPVM::TestCase::add_short_max(), 32767);
  is(SPVM::TestCase::add_short_min(), -32767);
  is(SPVM::TestCase::add_short_overflow(), -32768);
  is(SPVM::TestCase::add_int_max(), 2147483647);
  is(SPVM::TestCase::add_int_min(), -2147483647);
  is(SPVM::TestCase::add_int_overflow(), -2147483648);
  is(SPVM::TestCase::add_long_max(), 9223372036854775807);
  is(SPVM::TestCase::add_long_min(), -9223372036854775807);
  is(SPVM::TestCase::add_long_overflow(), -9223372036854775808);
}

# Subtract
{
  is(SPVM::TestCase::subtract_byte_max(), 126);
  is(SPVM::TestCase::subtract_byte_min(), -128);
  is(SPVM::TestCase::subtract_byte_underflow(), 127);
  is(SPVM::TestCase::subtract_short_max(), 32766);
  is(SPVM::TestCase::subtract_short_min(), -32768);
  is(SPVM::TestCase::subtract_short_underflow(), 32767);
  is(SPVM::TestCase::subtract_int_max(), 2147483646);
  is(SPVM::TestCase::subtract_int_min(), -2147483648);
  is(SPVM::TestCase::subtract_int_underflow(), 2147483647);
  is(SPVM::TestCase::subtract_long_max(), 9223372036854775806);
  is(SPVM::TestCase::subtract_long_min(), -9223372036854775808);
  is(SPVM::TestCase::subtract_long_underflow(), 9223372036854775807);
}

# Multiply
{
  is(SPVM::TestCase::multiply_byte_plus(), 64);
  is(SPVM::TestCase::multiply_byte_minus(), -64);
  is(SPVM::TestCase::multiply_byte_overflow(), -128);
  is(SPVM::TestCase::multiply_short_plus(), 16384);
  is(SPVM::TestCase::multiply_short_minus(), -16384);
  is(SPVM::TestCase::multiply_short_overflow(), -32768);
  is(SPVM::TestCase::multiply_int_plus(), 1073741824);
  is(SPVM::TestCase::multiply_int_minus(), -1073741824);
  is(SPVM::TestCase::multiply_int_overflow(), -2147483648);
  is(SPVM::TestCase::multiply_long_plus(), 4611686018427387904);
  is(SPVM::TestCase::multiply_long_minus(), -4611686018427387904);
  is(SPVM::TestCase::multiply_long_overflow(), -9223372036854775808);
}



# get and set
{
  {
    my $sp_values = SPVM::new_byte_array([0, 0]);
    $sp_values->set(1, $BYTE_MAX);
    ok(SPVM::TestCase::spvm_set_and_get_byte($sp_values));
    my $value = $sp_values->get(1);
    is($value, $BYTE_MAX);
  }
  {
    my $sp_values = SPVM::new_short_array([0, 0]);
    $sp_values->set(1, $SHORT_MAX);
    ok(SPVM::TestCase::spvm_set_and_get_short($sp_values));
    my $value = $sp_values->get(1);
    is($value, $SHORT_MAX);
  }
  {
    my $sp_values = SPVM::new_int_array([0, 0]);
    $sp_values->set(1, $INT_MAX);
    ok(SPVM::TestCase::spvm_set_and_get_int($sp_values));
    my $value = $sp_values->get(1);
    is($value, $INT_MAX);
  }
  {
    my $sp_values = SPVM::new_long_array([0, 0]);
    $sp_values->set(1, $LONG_MAX);
    ok(SPVM::TestCase::spvm_set_and_get_long($sp_values));
    my $value = $sp_values->get(1);
    is($value, $LONG_MAX);
  }
  {
    my $sp_values = SPVM::new_float_array([0, 0]);
    $sp_values->set(1, $FLOAT_PRECICE);
    ok(SPVM::TestCase::spvm_set_and_get_float($sp_values));
    my $value = $sp_values->get(1);
    is($value, $FLOAT_PRECICE);
  }
  {
    my $sp_values = SPVM::new_double_array([0, 0]);
    $sp_values->set(1, $DOUBLE_PRECICE);
    ok(SPVM::TestCase::spvm_set_and_get_double($sp_values));
    my $value = $sp_values->get(1);
    is($value, $DOUBLE_PRECICE);
  }
}

# SPVM Functions
{
  # get_elements
  {
    {
      my $sp_values = SPVM::new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
      my $values = $sp_values->get_elements;
      is_deeply($values, [1, $BYTE_MAX, $BYTE_MIN]);
    }
    {
      my $sp_values = SPVM::new_short_array([1, $SHORT_MAX, $SHORT_MIN]);
      my $values = $sp_values->get_elements;
      is_deeply($values, [1, $SHORT_MAX, $SHORT_MIN]);
    }
    {
      my $sp_values = SPVM::new_int_array([1, $INT_MAX, $INT_MIN]);
      my $values = $sp_values->get_elements;
      is_deeply($values, [1, $INT_MAX, $INT_MIN]);
    }
    {
      my $sp_values = SPVM::new_long_array([1, $LONG_MAX, $LONG_MIN]);
      my $values = $sp_values->get_elements;
      is_deeply($values, [1, $LONG_MAX, $LONG_MIN]);
    }
    {
      my $sp_values = SPVM::new_float_array([1, $FLOAT_MAX, $FLOAT_MIN]);
      my $values = $sp_values->get_elements;
      is_deeply($values, [1, $FLOAT_MAX, $FLOAT_MIN]);
    }
    {
      my $sp_values = SPVM::new_double_array([1, $DOUBLE_MAX, $DOUBLE_MIN]);
      my $values = $sp_values->get_elements;
      is_deeply($values, [1, $DOUBLE_MAX, $DOUBLE_MIN]);
    }
  }

  # get_elements_range
  {
    {
      my $sp_values = SPVM::new_byte_array([1, 2, $BYTE_MAX, 4]);
      my $values = $sp_values->get_elements_range(1, 2);
      is_deeply($values, [2, $BYTE_MAX]);
    }
    {
      my $sp_values = SPVM::new_short_array([1, 2, $SHORT_MAX, 4]);
      my $values = $sp_values->get_elements_range(1, 2);
      is_deeply($values, [2, $SHORT_MAX]);
    }
    {
      my $sp_values = SPVM::new_int_array([1, 2, $INT_MAX, 4]);
      my $values = $sp_values->get_elements_range(1, 2);
      is_deeply($values, [2, $INT_MAX]);
    }
    {
      my $sp_values = SPVM::new_long_array([1, 2, $LONG_MAX, 4]);
      my $values = $sp_values->get_elements_range(1, 2);
      is_deeply($values, [2, $LONG_MAX]);
    }
    {
      my $sp_values = SPVM::new_float_array([1, 2, $FLOAT_PRECICE, 4]);
      my $values = $sp_values->get_elements_range(1, 2);
      is_deeply($values, [2, $FLOAT_PRECICE]);
    }
    {
      my $sp_values = SPVM::new_double_array([1, 2, $DOUBLE_PRECICE, 4]);
      my $values = $sp_values->get_elements_range(1, 2);
      is_deeply($values, [2, $DOUBLE_PRECICE]);
    }
  }

  # set_elements_range
  {
    {
      my $sp_values = SPVM::new_byte_array([1, 2, 3, 4]);
      $sp_values->set_elements_range(1, 2, [5, $BYTE_MAX]);
      my $data = $sp_values->to_data;
      
      my @values = unpack('c4', $data);
      is_deeply(\@values, [1, 5, $BYTE_MAX, 4]);
    }
    {
      my $sp_values = SPVM::new_short_array([1, 2, 3, 4]);
      $sp_values->set_elements_range(1, 2, [5, $SHORT_MAX]);
      my $data = $sp_values->to_data;
      
      my @values = unpack('s4', $data);
      is_deeply(\@values, [1, 5, $SHORT_MAX, 4]);
    }
    {
      my $sp_values = SPVM::new_int_array([1, 2, 3, 4]);
      $sp_values->set_elements_range(1, 2, [5, $INT_MAX]);
      my $data = $sp_values->to_data;
      
      my @values = unpack('l4', $data);
      is_deeply(\@values, [1, 5, $INT_MAX, 4]);
    }
    {
      my $sp_values = SPVM::new_long_array([1, 2, 3, 4]);
      $sp_values->set_elements_range(1, 2, [5, $LONG_MAX]);
      my $data = $sp_values->to_data;
      
      my @values = unpack('q4', $data);
      is_deeply(\@values, [1, 5, $LONG_MAX, 4]);
    }
    {
      my $sp_values = SPVM::new_float_array([1, 2, 3, 4]);
      $sp_values->set_elements_range(1, 2, [5, $FLOAT_PRECICE]);
      my $data = $sp_values->to_data;
      
      my @values = unpack('f4', $data);
      is_deeply(\@values, [1, 5, $FLOAT_PRECICE, 4]);
    }
    {
      my $sp_values = SPVM::new_double_array([1, 2, 3, 4]);
      $sp_values->set_elements_range(1, 2, [5, $DOUBLE_PRECICE]);
      my $data = $sp_values->to_data;
      
      my @values = unpack('d4', $data);
      is_deeply(\@values, [1, 5, $DOUBLE_PRECICE, 4]);
    }
  }

  # to_data 0 length
  {
    {
      my $sp_values = SPVM::new_byte_array([]);
      my $data = $sp_values->to_data;
      is($data, "");
    }
    {
      my $sp_values = SPVM::new_short_array([]);
      my $data = $sp_values->to_data;
      is($data, "");
    }
    {
      my $sp_values = SPVM::new_int_array([]);
      my $data = $sp_values->to_data;
      is($data, "");
    }
    {
      my $sp_values = SPVM::new_long_array([]);
      my $data = $sp_values->to_data;
      is($data, "");
    }
    {
      my $sp_values = SPVM::new_float_array([]);
      my $data = $sp_values->to_data;
      is($data, "");
    }
    {
      my $sp_values = SPVM::new_double_array([]);
      my $data = $sp_values->to_data;
      is($data, "");
    }
  }
    
  # to_data
  {
    {
      my $sp_values = SPVM::new_byte_array([1, 2, $BYTE_MAX]);
      my $data = $sp_values->to_data;
      
      my @values = unpack('c3', $data);
      is_deeply(\@values, [1, 2, $BYTE_MAX]);
    }
    {
      my $sp_values = SPVM::new_short_array([1, 2, $SHORT_MAX]);
      my $data = $sp_values->to_data;
      
      my @values = unpack('s3', $data);
      is_deeply(\@values, [1, 2, $SHORT_MAX]);
    }
    {
      my $sp_values = SPVM::new_int_array([1, 2, $INT_MAX]);
      my $data = $sp_values->to_data;
      
      my @values = unpack('l3', $data);
      is_deeply(\@values, [1, 2, $INT_MAX]);
    }
    {
      my $sp_values = SPVM::new_long_array([1, 2, $LONG_MAX]);
      my $data = $sp_values->to_data;
      
      my @values = unpack('q3', $data);
      is_deeply(\@values, [1, 2, $LONG_MAX]);
    }
    {
      my $sp_values = SPVM::new_float_array([1, 2, $FLOAT_PRECICE]);
      my $data = $sp_values->to_data;
      
      my @values = unpack('f3', $data);
      is_deeply(\@values, [1, 2, $FLOAT_PRECICE]);
    }
    {
      my $sp_values = SPVM::new_double_array([1, 2, $DOUBLE_PRECICE]);
      my $data = $sp_values->to_data;
      
      my @values = unpack('d3', $data);
      is_deeply(\@values, [1, 2, $DOUBLE_PRECICE]);
    }
  }

  # to_data_range 0 length
  {
    {
      my $sp_values = SPVM::new_byte_array([1, 2, $BYTE_MAX, 4]);
      my $data = $sp_values->to_data_range(1, 0);
      is($data, "");
    }
    {
      my $sp_values = SPVM::new_short_array([1, 2, $SHORT_MAX, 4]);
      my $data = $sp_values->to_data_range(1, 0);
      is($data, "");
    }
    {
      my $sp_values = SPVM::new_int_array([1, 2, $INT_MAX, 4]);
      my $data = $sp_values->to_data_range(1, 0);
      is($data, "");
    }
    {
      my $sp_values = SPVM::new_long_array([1, 2, $LONG_MAX, 4]);
      my $data = $sp_values->to_data_range(1, 0);
      is($data, "");
    }
    {
      my $sp_values = SPVM::new_float_array([1, 2, $FLOAT_PRECICE, 4]);
      my $data = $sp_values->to_data_range(1, 0);
      is($data, "");
    }
    {
      my $sp_values = SPVM::new_double_array([1, 2, $DOUBLE_PRECICE, 4]);
      my $data = $sp_values->to_data_range(1, 0);
      is($data, "");
    }
  }

  # to_data_range
  {
    {
      my $sp_values = SPVM::new_byte_array([1, 2, $BYTE_MAX, 4]);
      my $data = $sp_values->to_data_range(1, 2);
      my @values = unpack('c2', $data);
      is_deeply(\@values, [2, $BYTE_MAX]);
    }
    {
      my $sp_values = SPVM::new_short_array([1, 2, $SHORT_MAX, 4]);
      my $data = $sp_values->to_data_range(1, 2);
      my @values = unpack('s2', $data);
      is_deeply(\@values, [2, $SHORT_MAX]);
    }
    {
      my $sp_values = SPVM::new_int_array([1, 2, $INT_MAX, 4]);
      my $data = $sp_values->to_data_range(1, 2);
      my @values = unpack('l2', $data);
      is_deeply(\@values, [2, $INT_MAX]);
    }
    {
      my $sp_values = SPVM::new_long_array([1, 2, $LONG_MAX, 4]);
      my $data = $sp_values->to_data_range(1, 2);
      my @values = unpack('q2', $data);
      is_deeply(\@values, [2, $LONG_MAX]);
    }
    {
      my $sp_values = SPVM::new_float_array([1, 2, $FLOAT_PRECICE, 4]);
      my $data = $sp_values->to_data_range(1, 2);
      my @values = unpack('f2', $data);
      is_deeply(\@values, [2, $FLOAT_PRECICE]);
    }
    {
      my $sp_values = SPVM::new_double_array([1, 2, $DOUBLE_PRECICE, 4]);
      my $data = $sp_values->to_data_range(1, 2);
      my @values = unpack('d2', $data);
      is_deeply(\@values, [2, $DOUBLE_PRECICE]);
    }
  }
  
  # new_xxx_array_string
  {
    {
      my $sp_values = SPVM::new_byte_array_string("あ");
      ok(SPVM::TestCase::spvm_new_byte_array_string($sp_values));
    }
  }
  
  # set_data_range
  {
    {
      my $data = pack('c2', 5, $BYTE_MAX);
      my $sp_values = SPVM::new_byte_array([1, 2, 3, 4]);
      $sp_values->set_data_range(1, 2, $data);
      
      my $values = $sp_values->get_elements;
      is_deeply($values, [1, 5, $BYTE_MAX, 4]);
    }
    {
      my $data = pack('s2', 5, $SHORT_MAX);
      my $sp_values = SPVM::new_short_array([1, 2, 3, 4]);
      $sp_values->set_data_range(1, 2, $data);
      
      my $values = $sp_values->get_elements;
      is_deeply($values, [1, 5, $SHORT_MAX, 4]);
    }
    {
      my $data = pack('l2', 5, $INT_MAX);
      my $sp_values = SPVM::new_int_array([1, 2, 3, 4]);
      $sp_values->set_data_range(1, 2, $data);
      
      my $values = $sp_values->get_elements;
      is_deeply($values, [1, 5, $INT_MAX, 4]);
    }
    {
      my $data = pack('q2', 5, $LONG_MAX);
      my $sp_values = SPVM::new_long_array([1, 2, 3, 4]);
      $sp_values->set_data_range(1, 2, $data);
      
      my $values = $sp_values->get_elements;
      is_deeply($values, [1, 5, $LONG_MAX, 4]);
    }
    {
      my $data = pack('f2', 5, $FLOAT_PRECICE);
      my $sp_values = SPVM::new_float_array([1, 2, 3, 4]);
      $sp_values->set_data_range(1, 2, $data);
      
      my $values = $sp_values->get_elements;
      is_deeply($values, [1, 5, $FLOAT_PRECICE, 4]);
    }
    {
      my $data = pack('d2', 5, $DOUBLE_PRECICE);
      my $sp_values = SPVM::new_double_array([1, 2, 3, 4]);
      $sp_values->set_data_range(1, 2, $data);
      
      my $values = $sp_values->get_elements;
      is_deeply($values, [1, 5, $DOUBLE_PRECICE, 4]);
    }
  }
  
  # new_xxx_array_data
  {
    {
      my $sp_values = SPVM::new_byte_array_data("abc");
      ok(SPVM::TestCase::spvm_new_byte_array_data($sp_values));
    }
    {
      my $data = pack('c3', 97, 98, $BYTE_MAX);
      
      my $sp_values = SPVM::new_byte_array_data($data);
      ok(SPVM::TestCase::spvm_new_byte_array_data_pack($sp_values));
    }
    {
      my $data = pack('c3', 97, 98, $BYTE_MAX);
      
      my $sp_values = SPVM::new_byte_array_data($data);
      ok(SPVM::TestCase::spvm_new_byte_array_data_pack($sp_values));
    }
    {
      my $data = pack('s3', 97, 98, $SHORT_MAX);
      
      my $sp_values = SPVM::new_short_array_data($data);
      ok(SPVM::TestCase::spvm_new_short_array_data_pack($sp_values));
    }
    {
      my $data = pack('l3', 97, 98, $INT_MAX);
      
      my $sp_values = SPVM::new_int_array_data($data);
      ok(SPVM::TestCase::spvm_new_int_array_data_pack($sp_values));
    }
    {
      my $data = pack('q3', 97, 98, $LONG_MAX);
      
      my $sp_values = SPVM::new_long_array_data($data);
      ok(SPVM::TestCase::spvm_new_long_array_data_pack($sp_values));
    }
    {
      my $data = pack('f3', 97, 98, $FLOAT_PRECICE);
      
      my $sp_values = SPVM::new_float_array_data($data);
      ok(SPVM::TestCase::spvm_new_float_array_data_pack($sp_values));
    }
    {
      my $data = pack('d3', 97, 98, $DOUBLE_PRECICE);
      
      my $sp_values = SPVM::new_double_array_data($data);
      ok(SPVM::TestCase::spvm_new_double_array_data_pack($sp_values));
    }
  }
}

# call_sub array
{
  # call_sub byte_array
  {
    my $sp_values = SPVM::new_byte_array([1, 2, 3]);
    is(SPVM::TestCase::call_sub_byte_array($sp_values), 6);
  }

  # call_sub short_array
  {
    my $sp_values = SPVM::new_short_array([1, 2, 3]);
    is(SPVM::TestCase::call_sub_short_array($sp_values), 6);
  }

  # call_sub int_array
  {
    my $sp_values = SPVM::new_int_array([1, 2, 3]);
    is(SPVM::TestCase::call_sub_int_array($sp_values), 6);
  }

  # call_sub long_array
  {
    my $sp_values = SPVM::new_long_array([1, 2, 3]);
    is(SPVM::TestCase::call_sub_long_array($sp_values), 6);
  }

  # call_sub float_array
  {
    my $sp_values = SPVM::new_float_array([0.5, 0.5, 1.0]);
    is(SPVM::TestCase::call_sub_float_array($sp_values), 2.0);
  }

  # call_sub double_array
  {
    my $sp_values = SPVM::new_double_array([0.5, 0.5, 1.0]);
    is(SPVM::TestCase::call_sub_double_array($sp_values), 2.0);
  }

  # call_sub
  {
    ok(SPVM::TestCase::call_sub_args_byte(0, $BYTE_MAX, $BYTE_MIN));
    ok(SPVM::TestCase::call_sub_args_short(0, $SHORT_MAX, $SHORT_MIN));
    ok(SPVM::TestCase::call_sub_args_int(0, $INT_MAX, $INT_MIN));
    ok(SPVM::TestCase::call_sub_args_long(0, $LONG_MAX, $LONG_MIN));
  }
}

# SPVM::Object::Array
{
  my $sp_values = SPVM::Object::Array::Int->new_len(3);
  $sp_values->set_elements([1, 2, 3]);
}

# constant int
{
  is(SPVM::TestCase::load_constant_int_min(), -2147483647);
  is(SPVM::TestCase::load_constant_int_m32769(), -32769);
  is(SPVM::TestCase::load_constant_int_m32768(), -32768);
  is(SPVM::TestCase::load_constant_int_m129(), -129);
  is(SPVM::TestCase::load_constant_int_m128(), -128);
  is(SPVM::TestCase::load_constant_int_m2(), -2);
  is(SPVM::TestCase::load_constant_int_m1(), -1);
  is(SPVM::TestCase::load_constant_int_0(), 0);
  is(SPVM::TestCase::load_constant_int_1(), 1);
  is(SPVM::TestCase::load_constant_int_2(), 2);
  is(SPVM::TestCase::load_constant_int_3(), 3);
  is(SPVM::TestCase::load_constant_int_4(), 4);
  is(SPVM::TestCase::load_constant_int_5(), 5);
  is(SPVM::TestCase::load_constant_int_6(), 6);
  is(SPVM::TestCase::load_constant_int_max(), 2147483647);
}

# constant long
{
  is(SPVM::TestCase::load_constant_long_min(), -9223372036854775808);
  is(SPVM::TestCase::load_constant_long_m32769(), -32769);
  is(SPVM::TestCase::load_constant_long_m32768(), -32768);
  is(SPVM::TestCase::load_constant_long_m129(), -129);
  is(SPVM::TestCase::load_constant_long_m128(), -128);
  is(SPVM::TestCase::load_constant_long_m2(), -2);
  is(SPVM::TestCase::load_constant_long_m1(), -1);
  is(SPVM::TestCase::load_constant_long_0(), 0);
  is(SPVM::TestCase::load_constant_long_1(), 1);
  is(SPVM::TestCase::load_constant_long_2(), 2);
  is(SPVM::TestCase::load_constant_long_3(), 3);
  is(SPVM::TestCase::load_constant_long_4(), 4);
  is(SPVM::TestCase::load_constant_long_5(), 5);
  is(SPVM::TestCase::load_constant_long_6(), 6);
  is(SPVM::TestCase::load_constant_long_127(), 127);
  is(SPVM::TestCase::load_constant_long_128(), 128);
  is(SPVM::TestCase::load_constant_long_32767(), 32767);
  is(SPVM::TestCase::load_constant_long_32768(), 32768);
  is(SPVM::TestCase::load_constant_long_max(), 9223372036854775807);
}

# constant float
{
  is(SPVM::TestCase::load_constant_float_0(), 0.0);
  is(SPVM::TestCase::load_constant_float_1(), 1.0);
  is(SPVM::TestCase::load_constant_float_0_5(), 0.5);
  is(SPVM::TestCase::load_constant_float_exponent_E_plus(), 0.5E+3);
  is(SPVM::TestCase::load_constant_float_exponent_e_plus(), 0.5e+3);
  is(SPVM::TestCase::load_constant_float_exponent_E_minus(), 62.5E-3);
  is(SPVM::TestCase::load_constant_float_exponent_e_minus(), 62.5e-3);
  is(SPVM::TestCase::load_constant_double_exponent_E_plus(), 0.5E+3);
  is(SPVM::TestCase::load_constant_double_exponent_e_plus(), 0.5e+3);
  is(SPVM::TestCase::load_constant_double_exponent_E_minus(), 62.5E-3);
  is(SPVM::TestCase::load_constant_double_exponent_e_minus(), 62.5e-3);
}

# constant double
{
  is(SPVM::TestCase::load_constant_double_0(), 0.0);
  is(SPVM::TestCase::load_constant_double_1(), 1.0);
  is(SPVM::TestCase::load_constant_double_0_5(), 0.5);
}

# If
{
  ok(SPVM::TestCase::if_true_byte());
  ok(SPVM::TestCase::if_true_short());
  ok(SPVM::TestCase::if_true_int());
  ok(SPVM::TestCase::if_true_long());
  ok(SPVM::TestCase::if_true_float());
  ok(SPVM::TestCase::if_true_double());
  ok(SPVM::TestCase::if_true_object());

  ok(SPVM::TestCase::if_false_byte());
  ok(SPVM::TestCase::if_false_short());
  ok(SPVM::TestCase::if_false_int());
  ok(SPVM::TestCase::if_false_long());
  ok(SPVM::TestCase::if_false_float());
  ok(SPVM::TestCase::if_false_double());
  ok(SPVM::TestCase::if_false_object());

  ok(SPVM::TestCase::if_else());
  ok(SPVM::TestCase::if_elsif());
  ok(SPVM::TestCase::if_elsif_2());
  ok(SPVM::TestCase::if_duplicate());
  
}

# If a > b
{
  ok(SPVM::TestCase::if_gt_byte_left_big());
  ok(SPVM::TestCase::if_gt_byte_same());
  ok(SPVM::TestCase::if_gt_byte_right_big());
  ok(SPVM::TestCase::if_gt_short_left_big());
  ok(SPVM::TestCase::if_gt_short_same());
  ok(SPVM::TestCase::if_gt_short_right_big());
  ok(SPVM::TestCase::if_gt_int_left_big());
  ok(SPVM::TestCase::if_gt_int_same());
  ok(SPVM::TestCase::if_gt_int_right_big());
  ok(SPVM::TestCase::if_gt_long_left_big());
  ok(SPVM::TestCase::if_gt_long_same());
  ok(SPVM::TestCase::if_gt_long_right_big());
  ok(SPVM::TestCase::if_gt_float_left_big());
  ok(SPVM::TestCase::if_gt_float_same());
  ok(SPVM::TestCase::if_gt_float_right_big());
  ok(SPVM::TestCase::if_gt_double_left_big());
  ok(SPVM::TestCase::if_gt_double_same());
  ok(SPVM::TestCase::if_gt_double_right_big());
}

# If a >= b
{
  ok(SPVM::TestCase::if_ge_byte_left_big());
  ok(SPVM::TestCase::if_ge_byte_same());
  ok(SPVM::TestCase::if_ge_byte_right_big());
  ok(SPVM::TestCase::if_ge_short_left_big());
  ok(SPVM::TestCase::if_ge_short_same());
  ok(SPVM::TestCase::if_ge_short_right_big());
  ok(SPVM::TestCase::if_ge_int_left_big());
  ok(SPVM::TestCase::if_ge_int_same());
  ok(SPVM::TestCase::if_ge_int_right_big());
  ok(SPVM::TestCase::if_ge_long_left_big());
  ok(SPVM::TestCase::if_ge_long_same());
  ok(SPVM::TestCase::if_ge_long_right_big());
  ok(SPVM::TestCase::if_ge_float_left_big());
  ok(SPVM::TestCase::if_ge_float_same());
  ok(SPVM::TestCase::if_ge_float_right_big());
  ok(SPVM::TestCase::if_ge_double_left_big());
  ok(SPVM::TestCase::if_ge_double_same());
  ok(SPVM::TestCase::if_ge_double_right_big());
}

# If a < b
{
  ok(SPVM::TestCase::if_lt_byte_left_big());
  ok(SPVM::TestCase::if_lt_byte_same());
  ok(SPVM::TestCase::if_lt_byte_right_big());
  ok(SPVM::TestCase::if_lt_short_left_big());
  ok(SPVM::TestCase::if_lt_short_same());
  ok(SPVM::TestCase::if_lt_short_right_big());
  ok(SPVM::TestCase::if_lt_int_left_big());
  ok(SPVM::TestCase::if_lt_int_same());
  ok(SPVM::TestCase::if_lt_int_right_big());
  ok(SPVM::TestCase::if_lt_long_left_big());
  ok(SPVM::TestCase::if_lt_long_same());
  ok(SPVM::TestCase::if_lt_long_right_big());
  ok(SPVM::TestCase::if_lt_float_left_big());
  ok(SPVM::TestCase::if_lt_float_same());
  ok(SPVM::TestCase::if_lt_float_right_big());
  ok(SPVM::TestCase::if_lt_double_left_big());
  ok(SPVM::TestCase::if_lt_double_same());
  ok(SPVM::TestCase::if_lt_double_right_big());
}

# If a <= b
{
  ok(SPVM::TestCase::if_le_byte_left_big());
  ok(SPVM::TestCase::if_le_byte_same());
  ok(SPVM::TestCase::if_le_byte_right_big());
  ok(SPVM::TestCase::if_le_short_left_big());
  ok(SPVM::TestCase::if_le_short_same());
  ok(SPVM::TestCase::if_le_short_right_big());
  ok(SPVM::TestCase::if_le_int_left_big());
  ok(SPVM::TestCase::if_le_int_same());
  ok(SPVM::TestCase::if_le_int_right_big());
  ok(SPVM::TestCase::if_le_long_left_big());
  ok(SPVM::TestCase::if_le_long_same());
  ok(SPVM::TestCase::if_le_long_right_big());
  ok(SPVM::TestCase::if_le_float_left_big());
  ok(SPVM::TestCase::if_le_float_same());
  ok(SPVM::TestCase::if_le_float_right_big());
  ok(SPVM::TestCase::if_le_double_left_big());
  ok(SPVM::TestCase::if_le_double_same());
  ok(SPVM::TestCase::if_le_double_right_big());
}

# If a == b
{
  ok(SPVM::TestCase::if_eq_byte_same());
  ok(SPVM::TestCase::if_eq_byte_different());
  ok(SPVM::TestCase::if_eq_short_same());
  ok(SPVM::TestCase::if_eq_short_different());
  ok(SPVM::TestCase::if_eq_int_same());
  ok(SPVM::TestCase::if_eq_int_different());
  ok(SPVM::TestCase::if_eq_long_same());
  ok(SPVM::TestCase::if_eq_long_different());
  ok(SPVM::TestCase::if_eq_float_same());
  ok(SPVM::TestCase::if_eq_float_different());
  ok(SPVM::TestCase::if_eq_double_same());
  ok(SPVM::TestCase::if_eq_double_different());
  ok(SPVM::TestCase::if_eq_object_same());
  ok(SPVM::TestCase::if_eq_object_different());
}

# If a != b
{
  ok(SPVM::TestCase::if_ne_byte_same());
  ok(SPVM::TestCase::if_ne_byte_different());
  ok(SPVM::TestCase::if_ne_short_same());
  ok(SPVM::TestCase::if_ne_short_different());
  ok(SPVM::TestCase::if_ne_int_same());
  ok(SPVM::TestCase::if_ne_int_different());
  ok(SPVM::TestCase::if_ne_long_same());
  ok(SPVM::TestCase::if_ne_long_different());
  ok(SPVM::TestCase::if_ne_float_same());
  ok(SPVM::TestCase::if_ne_float_different());
  ok(SPVM::TestCase::if_ne_double_same());
  ok(SPVM::TestCase::if_ne_double_different());
  ok(SPVM::TestCase::if_ne_object_same());
  ok(SPVM::TestCase::if_ne_object_different());
}

# Number literal
{
  ok(SPVM::TestCase::number_literal_underline_hex());
  ok(SPVM::TestCase::number_literal_underline());
  ok(SPVM::TestCase::number_literal_hex_specifier());
  ok(SPVM::TestCase::number_literal_hex_all_number());
  ok(SPVM::TestCase::number_literal_hex_int());
  ok(SPVM::TestCase::number_literal_hex_int_max());
  ok(SPVM::TestCase::number_literal_hex_long_max());

  ok(SPVM::TestCase::number_literal_octal_specifier());
  ok(SPVM::TestCase::number_literal_octal_all_number());
  ok(SPVM::TestCase::number_literal_octal_int());
  ok(SPVM::TestCase::number_literal_octal_int_max());
  ok(SPVM::TestCase::number_literal_octal_long_max());

  ok(SPVM::TestCase::number_literal_binary_specifier());
  ok(SPVM::TestCase::number_literal_binary_all_number());
  ok(SPVM::TestCase::number_literal_binary_int());
  ok(SPVM::TestCase::number_literal_binary_int_max());
  ok(SPVM::TestCase::number_literal_binary_long_max());
}

# Bit shift left
{
  ok(SPVM::TestCase::bit_shift_left_byte());
  ok(SPVM::TestCase::bit_shift_left_byte_max());
  ok(SPVM::TestCase::bit_shift_left_byte_overflow());
  ok(SPVM::TestCase::bit_shift_left_short());
  ok(SPVM::TestCase::bit_shift_left_short_max());
  ok(SPVM::TestCase::bit_shift_left_short_overflow());
  ok(SPVM::TestCase::bit_shift_left_int());
  ok(SPVM::TestCase::bit_shift_left_int_max());
  ok(SPVM::TestCase::bit_shift_left_int_overflow());
  ok(SPVM::TestCase::bit_shift_left_long());
  ok(SPVM::TestCase::bit_shift_left_long_max());
  ok(SPVM::TestCase::bit_shift_left_long_overflow());
}

# Bit shift right logical
{
  ok(SPVM::TestCase::bit_shift_right_logical_byte());
  ok(SPVM::TestCase::bit_shift_right_logical_short());
  ok(SPVM::TestCase::bit_shift_right_logical_int());
  ok(SPVM::TestCase::bit_shift_right_logical_long());
}

# Bit shift right
{
  ok(SPVM::TestCase::bit_shift_right_byte());
  ok(SPVM::TestCase::bit_shift_right_short());
  ok(SPVM::TestCase::bit_shift_right_int());
  ok(SPVM::TestCase::bit_shift_right_long());
}


# Array
{
  # int array and get length
  {
    ok(SPVM::TestCase::get_array_length_at());
    ok(SPVM::TestCase::get_array_length_len());
    # ok(SPVM::TestCase::get_array_length_undef());
  }

  # array - set and get array element, first element
  {
    my $element = SPVM::TestCase::array_set_and_get_array_element_first();
    is($element, 345);
  }
  
  # array - set and get array element, last element
  {
    my $element = SPVM::TestCase::array_set_and_get_array_element_last();
    is($element, 298);
  }

  # array - culcurate sum by for
  {
    my $total = SPVM::TestCase::array_culcurate_sum_by_for();
    is($total, 6);
  }
}

# byte
{
  my $total = SPVM::TestCase::sum_byte(8, 3);
  is($total, 11);
}

# short
{
  my $total = SPVM::TestCase::sum_short(8, 3);
  is($total, 11);
}

# int
{
  my $total = SPVM::TestCase::sum_int(8, 3);
  is($total, 11);
}

# long
{
  my $total = SPVM::TestCase::sum_long(8, 3);
  is($total, 11);
}
{
  my $total = SPVM::TestCase::sum_long(9223372036854775806, 1);
  is($total, 9223372036854775807);
}

# float
{
  my $total = SPVM::TestCase::sum_float(0.25, 0.25);
  cmp_ok($total, '==', 0.5);
}

# double
{
  my $total = SPVM::TestCase::sum_double(0.25, 0.25);
  cmp_ok($total, '==', 0.5);
}

# for
{
  my $total = SPVM::TestCase::for_basic();
  cmp_ok($total, '==', 6);
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);

