use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;
use POSIX();

use Test::More 'no_plan';

my $file = basename $0;

use FindBin;

use SPVM 'TestCase'; my $use_test_line = __LINE__;

use SPVM 'TestCase::PerlAPI';
use SPVM 'TestCase::Point_i3';

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
my $FLT_MIN = POSIX::FLT_MIN();
my $DBL_MIN = POSIX::DBL_MIN();

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Argument is value reference and numeric reference mixed
{
  {
    my $point1 = {x => $BYTE_MIN, y => 1, z => 2};
    my $value1 = 6;
    my $point2 = {x => 3, y => 4, z => 5};
    my $value2 = 7;
    TestCase::PerlAPI->call_sub_value_ref_numeric_ref_mixed_arg(\$point1, \$value1, \$point2, \$value2);
    is_deeply($point1, {x => $BYTE_MIN + 1, y => 2, z => 3});
    is($value1, 7);
    is_deeply($point2, {x => 4, y => 5, z => 6});
    is($value2, 8);
  }
}

# Argument is value reference
{
  {
    my $point = {x => $BYTE_MIN, y => 1, z => 2};
    TestCase::PerlAPI->call_sub_value_ref_arg_byte(\$point);
    is_deeply($point, {x => $BYTE_MIN + 1, y => 2, z => 3});
  }
  {
    my $point = {x => $SHORT_MIN, y => 1, z => 2};
    TestCase::PerlAPI->call_sub_value_ref_arg_short(\$point);
    is_deeply($point, {x => $SHORT_MIN + 1, y => 2, z => 3});
  }
  {
    my $point = {x => $INT_MIN, y => 1, z => 2};
    TestCase::PerlAPI->call_sub_value_ref_arg_int(\$point);
    is_deeply($point, {x => $INT_MIN + 1, y => 2, z => 3});
  }
  {
    my $point = {x => $LONG_MIN, y => 1, z => 2};
    TestCase::PerlAPI->call_sub_value_ref_arg_long(\$point);
    is_deeply($point, {x => $LONG_MIN + 1, y => 2, z => 3});
  }
  {
    my $point = {x => $FLT_MIN, y => 1, z => 2};
    TestCase::PerlAPI->call_sub_value_ref_arg_float(\$point);
    is_deeply($point, {x => $FLT_MIN + 1, y => 2, z => 3});
  }
  {
    my $point = {x => $DBL_MIN, y => 1, z => 2};
    TestCase::PerlAPI->call_sub_value_ref_arg_double(\$point);
    is_deeply($point, {x => $DBL_MIN + 1, y => 2, z => 3});
  }
}

# Argument is numeric reference
{
  {
    my $num_byte = $BYTE_MIN;
    TestCase::PerlAPI->call_sub_numeric_ref_arg_byte(\$num_byte);
    is($num_byte, $BYTE_MIN + 1);
  }
  {
    my $num_short = $SHORT_MIN;
    TestCase::PerlAPI->call_sub_numeric_ref_arg_short(\$num_short);
    is($num_short, $SHORT_MIN + 1);
  }
  {
    my $num_int = $INT_MIN;
    TestCase::PerlAPI->call_sub_numeric_ref_arg_int(\$num_int);
    is($num_int, $INT_MIN + 1);
  }
  {
    my $num_long = $LONG_MIN;
    TestCase::PerlAPI->call_sub_numeric_ref_arg_long(\$num_long);
    is($num_long, $LONG_MIN + 1);
  }
  {
    my $num_float = POSIX::FLT_MIN();
    TestCase::PerlAPI->call_sub_numeric_ref_arg_float(\$num_float);
    is($num_float, POSIX::FLT_MIN() + 1);
  }
  {
    my $num_double = POSIX::DBL_MIN();
    TestCase::PerlAPI->call_sub_numeric_ref_arg_double(\$num_double);
    is($num_double, POSIX::DBL_MIN() + 1);
  }
}

# Object
{
  # Create object
  {
    my $object = TestCase->new();
    $object->set_x_int_array(SPVM::new_int_array([$INT_MAX, $INT_MAX]));
    my $sp_values = SPVM::new_byte_array_len(3);
    $sp_values->set_bin("abc");
    $object->set_x_string($sp_values);
    ok(TestCase::PerlAPI->spvm_object_set_object($object));
  }
  # Create object
  {
    my $object = TestCase->new();
    $object->set_x_byte($BYTE_MAX);
    $object->set_x_short($SHORT_MAX);
    $object->set_x_int($INT_MAX);
    $object->set_x_long($LONG_MAX);
    $object->set_x_float($FLOAT_PRECICE);
    $object->set_x_double($DOUBLE_PRECICE);
    $object->set_x_int_array(SPVM::new_int_array([1, 2, 3, 4]));
    $object->set_x_string(SPVM::new_byte_array_string("Hello"));
    my $minimal = TestCase::Minimal->new;
    $minimal->set_x(3);
    $object->set_minimal($minimal);
    
    ok(TestCase::PerlAPI->spvm_object_set($object));
    
    is($object->get_x_byte,$BYTE_MAX);
    is($object->get_x_short, $SHORT_MAX);
    is($object->get_x_int, $INT_MAX);
    is($object->get_x_long, $LONG_MAX);
    is($object->get_x_float, $FLOAT_PRECICE);
    is($object->get_x_double, $DOUBLE_PRECICE);
    is($object->get_minimal->get_x, 3);
  }
}

# time
{
  cmp_ok(abs(time - SPVM::CORE->time()), '<', 2);
}

# my variable
{
  ok(TestCase->my_var_initialized_zero());
  ok(TestCase->my_var_initialized_zero());
}

{
  ok(TestCase->new_near_small_base_object_max_byte_size_use_memory_pool());
}

=pod
is_deeply(
  \@SPVM::PACKAGE_INFOS,
  [
    {name => 'TestCase', file => $file, line => $use_test_line},
    {name => 'SPVM::CORE', file => $file, line => $use_core_line}
  ]
);
=cut

# SPVM new_object_array_len
{

  # element object array
  {
    my $object_array = SPVM::new_object_array_len("TestCase", 3);
    my $object1 = TestCase->new();
    
    $object1->set_x_int(1);
    SPVM::set_array_element($object_array, 0, $object1);
    my $object2 = TestCase->new();
    $object2->set_x_int(2);
    SPVM::set_array_element($object_array, 1, $object2);
    ok(TestCase::PerlAPI->spvm_new_object_array_len_element_object_array($object_array));
    
    my $object1_get = SPVM::get_array_element($object_array, 0);
    my $object2_get = SPVM::get_array_element($object_array, 1);
    
    is_deeply($object1_get->get_x_int, 1);
    is_deeply($object2_get->get_x_int, 2);
  }

  # element byte array
  {
    my $object_array = SPVM::new_multi_array_len("byte", 1, 3);
    
    my $object1 = SPVM::new_byte_array([1, 2, 3]);
    SPVM::set_array_element($object_array, 0, $object1);
    my $object2 = SPVM::new_byte_array([4, 5, 6]);
    SPVM::set_array_element($object_array, 1, $object2);
    ok(TestCase::PerlAPI->spvm_new_object_array_len_element_byte_array($object_array));
    
    my $object1_get = SPVM::get_array_element($object_array, 0);
    my $object2_get = SPVM::get_array_element($object_array, 1);
    
    is_deeply(SPVM::get_array_elements($object1_get), [1, 2, 3]);
    is_deeply(SPVM::get_array_elements($object2_get), [4, 5, 6]);
  }

  # element short array
  {
    my $object_array = SPVM::new_multi_array_len("short", 1, 3);
    my $object1 = SPVM::new_short_array([1, 2, 3]);
    SPVM::set_array_element($object_array, 0, $object1);
    my $object2 = SPVM::new_short_array([4, 5, 6]);
    SPVM::set_array_element($object_array, 1, $object2);
    ok(TestCase::PerlAPI->spvm_new_object_array_len_element_short_array($object_array));
    
    my $object1_get = SPVM::get_array_element($object_array, 0);
    my $object2_get = SPVM::get_array_element($object_array, 1);
    
    is_deeply(SPVM::get_array_elements($object1_get), [1, 2, 3]);
    is_deeply(SPVM::get_array_elements($object2_get), [4, 5, 6]);
  }

  # element int array
  {
    my $object_array = SPVM::new_multi_array_len("int", 1, 3);
    my $object1 = SPVM::new_int_array([1, 2, 3]);
    SPVM::set_array_element($object_array, 0, $object1);
    my $object2 = SPVM::new_int_array([4, 5, 6]);
    SPVM::set_array_element($object_array, 1, $object2);
    ok(TestCase::PerlAPI->spvm_new_object_array_len_element_int_array($object_array));
    
    my $object1_get = SPVM::get_array_element($object_array, 0);
    my $object2_get = SPVM::get_array_element($object_array, 1);
    
    is_deeply(SPVM::get_array_elements($object1_get), [1, 2, 3]);
    is_deeply(SPVM::get_array_elements($object2_get), [4, 5, 6]);
  }

  # element long array
  {
    my $object_array = SPVM::new_multi_array_len("long", 1, 3);
    my $object1 = SPVM::new_long_array([1, 2, 3]);
    SPVM::set_array_element($object_array, 0, $object1);
    my $object2 = SPVM::new_long_array([4, 5, 6]);
    SPVM::set_array_element($object_array, 1, $object2);
    ok(TestCase::PerlAPI->spvm_new_object_array_len_element_long_array($object_array));
    
    my $object1_get = SPVM::get_array_element($object_array, 0);
    my $object2_get = SPVM::get_array_element($object_array, 1);
    
    is_deeply(SPVM::get_array_elements($object1_get), [1, 2, 3]);
    is_deeply(SPVM::get_array_elements($object2_get), [4, 5, 6]);
  }

  # element float array
  {
    my $object_array = SPVM::new_multi_array_len("float", 1, 3);
    my $object1 = SPVM::new_float_array([1, 2, 3]);
    SPVM::set_array_element($object_array, 0, $object1);
    my $object2 = SPVM::new_float_array([4, 5, 6]);
    SPVM::set_array_element($object_array, 1, $object2);
    ok(TestCase::PerlAPI->spvm_new_object_array_len_element_float_array($object_array));
    
    my $object1_get = SPVM::get_array_element($object_array, 0);
    my $object2_get = SPVM::get_array_element($object_array, 1);
    
    is_deeply(SPVM::get_array_elements($object1_get), [1, 2, 3]);
    is_deeply(SPVM::get_array_elements($object2_get), [4, 5, 6]);
  }

  # element double array
  {
    my $object_array = SPVM::new_multi_array_len("double", 1, 3);
    my $object1 = SPVM::new_double_array([1, 2, 3]);
    SPVM::set_array_element($object_array, 0, $object1);
    my $object2 = SPVM::new_double_array([4, 5, 6]);
    SPVM::set_array_element($object_array, 1, $object2);
    ok(TestCase::PerlAPI->spvm_new_object_array_len_element_double_array($object_array));
    
    my $object1_get = SPVM::get_array_element($object_array, 0);
    my $object2_get = SPVM::get_array_element($object_array, 1);
    
    is_deeply(SPVM::get_array_elements($object1_get), [1, 2, 3]);
    is_deeply(SPVM::get_array_elements($object2_get), [4, 5, 6]);
  }
}

# get and set
{
  {
    my $sp_values = SPVM::new_byte_array([0, 0]);
    SPVM::set_array_element($sp_values, 1, $BYTE_MAX);
    ok(TestCase::PerlAPI->spvm_set_and_get_byte($sp_values));
    my $value = SPVM::get_array_element($sp_values, 1);
    is($value, $BYTE_MAX);
  }
  {
    my $sp_values = SPVM::new_short_array([0, 0]);
    SPVM::set_array_element($sp_values, 1, $SHORT_MAX);
    ok(TestCase::PerlAPI->spvm_set_and_get_short($sp_values));
    my $value = SPVM::get_array_element($sp_values, 1);
    is($value, $SHORT_MAX);
  }
  {
    my $sp_values = SPVM::new_int_array([0, 0]);
    SPVM::set_array_element($sp_values, 1, $INT_MAX);
    ok(TestCase::PerlAPI->spvm_set_and_get_int($sp_values));
    my $value = SPVM::get_array_element($sp_values, 1);
    is($value, $INT_MAX);
  }
  {
    my $sp_values = SPVM::new_long_array([0, 0]);
    SPVM::set_array_element($sp_values, 1, $LONG_MAX);
    ok(TestCase::PerlAPI->spvm_set_and_get_long($sp_values));
    my $value = SPVM::get_array_element($sp_values, 1);
    is($value, $LONG_MAX);
  }
  {
    my $sp_values = SPVM::new_float_array([0, 0]);
    SPVM::set_array_element($sp_values, 1, $FLOAT_PRECICE);
    ok(TestCase::PerlAPI->spvm_set_and_get_float($sp_values));
    my $value = SPVM::get_array_element($sp_values, 1);
    is($value, $FLOAT_PRECICE);
  }
  {
    my $sp_values = SPVM::new_double_array([0, 0]);
    SPVM::set_array_element($sp_values, 1, $DOUBLE_PRECICE);
    ok(TestCase::PerlAPI->spvm_set_and_get_double($sp_values));
    my $value = SPVM::get_array_element($sp_values, 1);
    is($value, $DOUBLE_PRECICE);
  }
}

# value_t array
{
  {
    my $sp_values = SPVM::new_value_t_array_len("TestCase::Point_i3", 3);
    SPVM::set_array_element($sp_values, 1, {x => $INT_MIN, y => 1, z => 2});
    ok(TestCase::PerlAPI->spvm_set_and_get_value_t_int($sp_values));
    my $value = SPVM::get_array_element($sp_values, 1);
    is_deeply($value, {x => $INT_MIN, y => 1, z => 2});
  }

  {
    my $values = [
      {x => $INT_MIN, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $sp_values = SPVM::new_value_t_array("TestCase::Point_i3", $values);
    $sp_values->set_elements($values);
    ok(TestCase::PerlAPI->spvm_new_value_t_array_int($sp_values));
    my $out_values = SPVM::get_array_elements($sp_values);
    is_deeply($out_values, $values);
  }

  {
    my $bin = pack('l9', ($INT_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $sp_values = SPVM::new_value_t_array_len("TestCase::Point_i3", 3);
    $sp_values->set_bin($bin);
    ok(TestCase::PerlAPI->spvm_new_value_t_array_bin_int($sp_values));
    my $out_bin = $sp_values->to_bin;
    is_deeply($out_bin, $bin);
  }

}

# SPVM Functions
{
  # SPVM::get_array_elements(
  {
    {
      my $sp_values = SPVM::new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
      my $values = SPVM::get_array_elements($sp_values);
      is_deeply($values, [1, $BYTE_MAX, $BYTE_MIN]);
    }
    {
      my $sp_values = SPVM::new_short_array([1, $SHORT_MAX, $SHORT_MIN]);
      my $values = SPVM::get_array_elements($sp_values);
      is_deeply($values, [1, $SHORT_MAX, $SHORT_MIN]);
    }
    {
      my $sp_values = SPVM::new_int_array([1, $INT_MAX, $INT_MIN]);
      my $values = SPVM::get_array_elements($sp_values);
      is_deeply($values, [1, $INT_MAX, $INT_MIN]);
    }
    {
      my $sp_values = SPVM::new_long_array([1, $LONG_MAX, $LONG_MIN]);
      my $values = SPVM::get_array_elements($sp_values);
      is_deeply($values, [1, $LONG_MAX, $LONG_MIN]);
    }
  }

  # to_bin 0 length
  {
    {
      my $sp_values = SPVM::new_byte_array([]);
      my $bin = $sp_values->to_bin;
      is($bin, "");
    }
    {
      my $sp_values = SPVM::new_short_array([]);
      my $bin = $sp_values->to_bin;
      is($bin, "");
    }
    {
      my $sp_values = SPVM::new_int_array([]);
      my $bin = $sp_values->to_bin;
      is($bin, "");
    }
    {
      my $sp_values = SPVM::new_long_array([]);
      my $bin = $sp_values->to_bin;
      is($bin, "");
    }
    {
      my $sp_values = SPVM::new_float_array([]);
      my $bin = $sp_values->to_bin;
      is($bin, "");
    }
    {
      my $sp_values = SPVM::new_double_array([]);
      my $bin = $sp_values->to_bin;
      is($bin, "");
    }
  }
    
  # to_bin
  {
    {
      my $sp_values = SPVM::new_byte_array([1, 2, $BYTE_MAX]);
      my $bin = $sp_values->to_bin;
      
      my @values = unpack('c3', $bin);
      is_deeply(\@values, [1, 2, $BYTE_MAX]);
    }
    {
      my $sp_values = SPVM::new_short_array([1, 2, $SHORT_MAX]);
      my $bin = $sp_values->to_bin;
      
      my @values = unpack('s3', $bin);
      is_deeply(\@values, [1, 2, $SHORT_MAX]);
    }
    {
      my $sp_values = SPVM::new_int_array([1, 2, $INT_MAX]);
      my $bin = $sp_values->to_bin;
      
      my @values = unpack('l3', $bin);
      is_deeply(\@values, [1, 2, $INT_MAX]);
    }
    {
      my $sp_values = SPVM::new_long_array([1, 2, $LONG_MAX]);
      my $bin = $sp_values->to_bin;
      
      my @values = unpack('q3', $bin);
      is_deeply(\@values, [1, 2, $LONG_MAX]);
    }
    {
      my $sp_values = SPVM::new_float_array([1, 2, $FLOAT_PRECICE]);
      my $bin = $sp_values->to_bin;
      
      my @values = unpack('f3', $bin);
      is_deeply(\@values, [1, 2, $FLOAT_PRECICE]);
    }
    {
      my $sp_values = SPVM::new_double_array([1, 2, $DOUBLE_PRECICE]);
      my $bin = $sp_values->to_bin;
      
      my @values = unpack('d3', $bin);
      is_deeply(\@values, [1, 2, $DOUBLE_PRECICE]);
    }
  }

  # new_xxx_array_string
  {
    {
      my $sp_values = SPVM::new_byte_array_string("あ");
      ok(TestCase::PerlAPI->spvm_new_byte_array_string($sp_values));
    }
  }
  
  # new_xxx_array_bin
  {
    {
      my $sp_values = SPVM::new_byte_array_len(3);
      $sp_values->set_bin("abc");
      ok(TestCase::PerlAPI->spvm_new_byte_array_bin($sp_values));
    }
    {
      my $bin = pack('c3', 97, 98, $BYTE_MAX);
      my $sp_values = SPVM::new_byte_array_len(3);
      $sp_values->set_bin($bin);
      ok(TestCase::PerlAPI->spvm_new_byte_array_bin_pack($sp_values));
    }
    {
      my $bin = pack('c3', 97, 98, $BYTE_MAX);
      my $sp_values = SPVM::new_byte_array_len(3);
      $sp_values->set_bin($bin);
      ok(TestCase::PerlAPI->spvm_new_byte_array_bin_pack($sp_values));
    }
    {
      my $bin = pack('s3', 97, 98, $SHORT_MAX);
      
      my $sp_values = SPVM::new_short_array_len(3);
      $sp_values->set_bin($bin);
      ok(TestCase::PerlAPI->spvm_new_short_array_bin_pack($sp_values));
    }
    {
      my $bin = pack('l3', 97, 98, $INT_MAX);
      
      my $sp_values = SPVM::new_int_array_len(3);
      $sp_values->set_bin($bin);
      ok(TestCase::PerlAPI->spvm_new_int_array_bin_pack($sp_values));
    }
    {
      my $bin = pack('q3', 97, 98, $LONG_MAX);
      my $sp_values = SPVM::new_long_array_len(3);
      $sp_values->set_bin($bin);
      ok(TestCase::PerlAPI->spvm_new_long_array_bin_pack($sp_values));
    }
    {
      my $bin = pack('f3', 97, 98, $FLOAT_PRECICE);
      my $sp_values = SPVM::new_float_array_len(3);
      $sp_values->set_bin($bin);
      ok(TestCase::PerlAPI->spvm_new_float_array_bin_pack($sp_values));
    }
    {
      my $bin = pack('d3', 97, 98, $DOUBLE_PRECICE);
      my $sp_values = SPVM::new_double_array_len(3);
      $sp_values->set_bin($bin);
      ok(TestCase::PerlAPI->spvm_new_double_array_bin_pack($sp_values));
    }
  }
}


# SPVM::Object::Array
{
  my $sp_values = SPVM::new_int_array_len(3);
  $sp_values->set_elements([1, 2, 3]);
}

# byte
{
  my $total = TestCase->sum_byte(8, 3);
  is($total, 11);
}

# short
{
  my $total = TestCase->sum_short(8, 3);
  is($total, 11);
}

# int
{
  my $total = TestCase->sum_int(8, 3);
  is($total, 11);
}

# long
{
  my $total = TestCase->sum_long(8, 3);
  is($total, 11);
}
{
  my $total = TestCase->sum_long(9223372036854775806, 1);
  is($total, 9223372036854775807);
}

# float
{
  my $total = TestCase->sum_float(0.25, 0.25);
  cmp_ok($total, '==', 0.5);
}

# double
{
  my $total = TestCase->sum_double(0.25, 0.25);
  cmp_ok($total, '==', 0.5);
}

# String
{
  {
    my $values = TestCase->string_empty();
    is($values->to_bin, "");
  }
  
  {
    my $values = TestCase->string_utf8();
    is($values->to_string, "あいうえお");
  }
}

# Complex
{
  my $z3 = SPVM::CORE->cadd({re => 0.25, im => 0.5}, {re => 0.5, im => 0.125});
  is_deeply($z3, {re => 0.75, im => 0.625});
}


# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

