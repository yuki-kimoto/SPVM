use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;

use Test::More 'no_plan';

my $file = basename $0;

use FindBin;

use SPVM 'TestCase'; my $use_test_line = __LINE__;
use SPVM 'CORE'; my $use_core_line = __LINE__;

use POSIX ();

use SPVM::Core::Object::Package;

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

# TODO
# remainder float double
# bit_and
# bit_or
# last
# while
# eval repeat
# print

# Positive infinity(unix like system : inf, Windows : 1.#INF)
my $POSITIVE_INFINITY = SPVM::POSITIVE_INFINITY();

# Negative infinity(unix like system : -inf, Windows : -1.#INF)
my $NEGATIVE_INFINITY = SPVM::NEGATIVE_INFINITY();

my $NaN = SPVM::NaN();

use SPVM 'Double';
use SPVM 'Float';
use SPVM 'CORE';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# time
{
  cmp_ok(abs(time - SPVM::CORE::time()), '<', 2);
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

# Switch
{
  ok(SPVM::TestCase::switch_nest());
  ok(SPVM::TestCase::switch_lookup_switch());
  ok(SPVM::TestCase::switch_table_switch());
}

# my variable
{
  ok(SPVM::TestCase::my_var_initialized_zero());
  ok(SPVM::TestCase::my_var_initialized_zero());
}

{
  ok(SPVM::TestCase::new_near_small_base_object_max_byte_size_use_memory_pool());
}

=pod
is_deeply(
  \@SPVM::PACKAGE_INFOS,
  [
    {name => 'TestCase', file => $file, line => $use_test_line},
    {name => 'CORE', file => $file, line => $use_core_line}
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
    my $object1 = SPVM::TestCase::new();
    
    $object1->set_x_int(1);
    $object_array->set(0, $object1);
    my $object2 = SPVM::TestCase::new();
    $object2->set_x_int(2);
    $object_array->set(1, $object2);
    ok(SPVM::TestCase::spvm_new_object_array_len_element_object_array($object_array));
    
    my $object1_get = $object_array->get(0);
    my $object2_get = $object_array->get(1);
    
    is_deeply($object1_get->get_x_int, 1);
    is_deeply($object2_get->get_x_int, 2);
  }
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


# SPVM::Core::Object::Array
{
  my $sp_values = SPVM::Core::Object::Array::Int->new_len(3);
  $sp_values->set_elements([1, 2, 3]);
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

