use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;
use POSIX();
use Encode 'encode';

use Test::More 'no_plan';

my $file = basename $0;

use FindBin;
use Encode 'decode', 'encode';

use SPVM 'TestCase'; my $use_test_line = __LINE__;

use SPVM 'TestCase::ExchangeAPI';
use SPVM 'TestCase::Point_3i';

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
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Any object array
{
  # String - UTF-8 string, new_str, new_str_from_bin, to_str, to_bin
  {
    my $bytes = SPVM::new_oarray("SPVM::Byte[]", [SPVM::Byte->new(1), SPVM::Byte->new(2), SPVM::Byte->new(3)]);
    my $ret = TestCase::ExchangeAPI->any_object_array($bytes);
    
    isa_ok($ret, 'SPVM::Data::Array');
    is_deeply([$ret->to_elems->[0]->val, $ret->to_elems->[1]->val, $ret->to_elems->[2]->val], [1, 2, 5]);
  }
}

# String argument
{
  # String argument - ascii
  {
    my $string = TestCase::ExchangeAPI->string_argments_and_return_value("ABC", "DE");
    is("$string", "ABCDE");
  }

  # String argument - UTF-8
  {
    my $string = TestCase::ExchangeAPI->string_argments_and_return_value("あいう", "えお");
    is("$string", "あいうえお");
  }

  # String argument - ascii and utf8
  {
    my $string = TestCase::ExchangeAPI->string_argments_and_return_value("あいう", "DE");
    is("$string", "あいうDE");
  }
}

# Stringfy
{
  # Stringfy - stringify overload
  {
    my $string1 = SPVM::new_str("あいう");
    my $string2 = SPVM::new_str("");
    my $string3 = TestCase::ExchangeAPI->string_argments_and_return_value($string1, $string2);
    isa_ok($string3, 'SPVM::Data::Array');
    is("$string3", "あいう");
  }
  
  # Stringify - 0 is true
  {
    my $string1 = SPVM::new_str("0");
    ok($string1);
    is("$string1", "0");
  }
}

# String arguments and return value
{
  # String - UTF-8 string, new_str, new_str_from_bin, to_str, to_bin
  {
    my $string1 = SPVM::new_str("あいう");
    my $string2 = SPVM::new_str_from_bin(encode('UTF-8', "えお"));
    my $string3 = TestCase::ExchangeAPI->string_argments_and_return_value($string1, $string2);
    isa_ok($string3, 'SPVM::Data::Array');
    is($string3->to_str, "あいうえお");
    is($string3->to_bin, encode('UTF-8', "あいうえお"));
  }

  # String - ascii string, new_str, new_str_from_bin, to_str, to_bin, to_element
  {
    my $string1 = SPVM::new_str_from_bin("abc");
    my $string2 = SPVM::new_str("de");
    my $string3 = TestCase::ExchangeAPI->string_argments_and_return_value($string1, $string2);
    isa_ok($string3, 'SPVM::Data::Array');
    is($string3->to_str, "abcde");
    is($string3->to_bin, "abcde");
    is_deeply($string3->to_elems, [ord('a'), ord('b'), ord('c'), ord('d'), ord('e')]);
  }
}

# Argument is value reference and numeric reference mixed
{
  {
    my $point1 = {x => $BYTE_MIN, y => 1, z => 2};
    my $value1 = 6;
    my $point2 = {x => 3, y => 4, z => 5};
    my $value2 = 7;
    TestCase::ExchangeAPI->call_sub_value_ref_numeric_ref_mixed_arg(\$point1, \$value1, \$point2, \$value2);
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
    TestCase::ExchangeAPI->call_sub_value_ref_arg_byte(\$point);
    is_deeply($point, {x => $BYTE_MIN + 1, y => 2, z => 3});
  }
  {
    my $point = {x => $SHORT_MIN, y => 1, z => 2};
    TestCase::ExchangeAPI->call_sub_value_ref_arg_short(\$point);
    is_deeply($point, {x => $SHORT_MIN + 1, y => 2, z => 3});
  }
  {
    my $point = {x => $INT_MIN, y => 1, z => 2};
    TestCase::ExchangeAPI->call_sub_value_ref_arg_int(\$point);
    is_deeply($point, {x => $INT_MIN + 1, y => 2, z => 3});
  }
  {
    my $point = {x => $LONG_MIN, y => 1, z => 2};
    TestCase::ExchangeAPI->call_sub_value_ref_arg_long(\$point);
    is_deeply($point, {x => $LONG_MIN + 1, y => 2, z => 3});
  }
  {
    my $point = {x => $FLT_MIN, y => 1, z => 2};
    TestCase::ExchangeAPI->call_sub_value_ref_arg_float(\$point);
    is_deeply($point, {x => $FLT_MIN + 1, y => 2, z => 3});
  }
  {
    my $point = {x => $DBL_MIN, y => 1, z => 2};
    TestCase::ExchangeAPI->call_sub_value_ref_arg_double(\$point);
    is_deeply($point, {x => $DBL_MIN + 1, y => 2, z => 3});
  }
}

# Argument is numeric reference
{
  {
    my $num_byte = $BYTE_MIN;
    TestCase::ExchangeAPI->call_sub_numeric_ref_arg_byte(\$num_byte);
    is($num_byte, $BYTE_MIN + 1);
  }
  {
    my $num_short = $SHORT_MIN;
    TestCase::ExchangeAPI->call_sub_numeric_ref_arg_short(\$num_short);
    is($num_short, $SHORT_MIN + 1);
  }
  {
    my $num_int = $INT_MIN;
    TestCase::ExchangeAPI->call_sub_numeric_ref_arg_int(\$num_int);
    is($num_int, $INT_MIN + 1);
  }
  {
    my $num_long = $LONG_MIN;
    TestCase::ExchangeAPI->call_sub_numeric_ref_arg_long(\$num_long);
    is($num_long, $LONG_MIN + 1);
  }
  {
    my $num_float = POSIX::FLT_MIN();
    TestCase::ExchangeAPI->call_sub_numeric_ref_arg_float(\$num_float);
    is($num_float, POSIX::FLT_MIN() + 1);
  }
  {
    my $num_double = POSIX::DBL_MIN();
    TestCase::ExchangeAPI->call_sub_numeric_ref_arg_double(\$num_double);
    is($num_double, POSIX::DBL_MIN() + 1);
  }
}

# Object
{
  # Create object
  {
    my $object = TestCase->new();
    $object->set_x_iarray(SPVM::new_iarray([$INT_MAX, $INT_MAX]));
    my $sp_values = SPVM::new_barray_from_bin("abc");
    $object->set_x_barray($sp_values);
    ok(TestCase::ExchangeAPI->spvm_object_set_object($object));
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
    $object->set_x_iarray(SPVM::new_iarray([1, 2, 3, 4]));
    my $minimal = TestCase::Minimal->new;
    $minimal->set_x(3);
    $object->set_minimal($minimal);
    
    ok(TestCase::ExchangeAPI->spvm_object_set($object));
    
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

# SPVM new_oarray
{

  # element object array
  {
    my $object1 = TestCase->new();
    $object1->set_x_int(1);
    my $object2 = TestCase->new();
    $object2->set_x_int(2);
    my $sp_oarray = SPVM::new_oarray("TestCase[]", [$object1, $object2]);
    
    ok(TestCase::ExchangeAPI->spvm_new_oarray_len_element_oarray($sp_oarray));
    
    my $oarray_out = $sp_oarray->to_elems;
    is($oarray_out->[0]->get_x_int, 1);
    is($oarray_out->[1]->get_x_int, 2);
  }

  # element byte array
  {
    my $object1 = SPVM::new_barray([1, 2, 3]);
    my $object2 = SPVM::new_barray([4, 5, 6]);
    my $oarray = SPVM::new_oarray("byte[][]", [$object1, $object2]);

    ok(TestCase::ExchangeAPI->spvm_new_oarray_len_element_barray($oarray));
    
    my $oarray_out = $oarray->to_elems;
    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element short array
  {
    my $object1 = SPVM::new_sarray([1, 2, 3]);
    my $object2 = SPVM::new_sarray([4, 5, 6]);
    my $oarray = SPVM::new_oarray("short[][]", [$object1, $object2]);

    ok(TestCase::ExchangeAPI->spvm_new_oarray_len_element_sarray($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element int array
  {
    my $object1 = SPVM::new_iarray([1, 2, 3]);
    my $object2 = SPVM::new_iarray([4, 5, 6]);
    my $oarray = SPVM::new_oarray("int[][]", [$object1, $object2]);

    ok(TestCase::ExchangeAPI->spvm_new_oarray_len_element_iarray($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element long array
  {
    my $object1 = SPVM::new_larray([1, 2, 3]);
    my $object2 = SPVM::new_larray([4, 5, 6]);
    my $oarray = SPVM::new_oarray("long[][]", [$object1, $object2]);
    ok(TestCase::ExchangeAPI->spvm_new_oarray_len_element_larray($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element float array
  {
    my $object1 = SPVM::new_farray([1, 2, 3]);
    my $object2 = SPVM::new_farray([4, 5, 6]);
    my $oarray = SPVM::new_oarray("float[][]", [$object1, $object2]);

    ok(TestCase::ExchangeAPI->spvm_new_oarray_len_element_farray($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element double array
  {
    my $object1 = SPVM::new_darray([1, 2, 3]);
    my $object2 = SPVM::new_darray([4, 5, 6]);
    my $oarray = SPVM::new_oarray("double[][]", [$object1, $object2]);
    
    ok(TestCase::ExchangeAPI->spvm_new_oarray_len_element_darray($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }
}

# value array
{
  {
    my $values = [
      {x => $INT_MIN, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $sp_values = SPVM::new_varray("TestCase::Point_3i[]", $values);
    ok(TestCase::ExchangeAPI->spvm_new_varray_int($sp_values));
    my $out_values = $sp_values->to_elems;
    is_deeply($out_values, $values);
  }

  {
    my $binary = pack('l9', ($INT_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $sp_values = SPVM::new_varray_from_bin("TestCase::Point_3i[]", $binary);
    ok(TestCase::ExchangeAPI->spvm_new_varray_binary_int($sp_values));
    my $out_bin = $sp_values->to_bin;
    is_deeply($out_bin, $binary);
  }
}

# SPVM Functions
{
  # to_elems(
  {
    {
      my $sp_values = SPVM::new_barray([1, $BYTE_MAX, $BYTE_MIN]);
      my $values = $sp_values->to_elems;
      is_deeply($values, [1, $BYTE_MAX, $BYTE_MIN]);
    }
    {
      my $sp_values = SPVM::new_sarray([1, $SHORT_MAX, $SHORT_MIN]);
      my $values = $sp_values->to_elems;
      is_deeply($values, [1, $SHORT_MAX, $SHORT_MIN]);
    }
    {
      my $sp_values = SPVM::new_iarray([1, $INT_MAX, $INT_MIN]);
      my $values = $sp_values->to_elems;
      is_deeply($values, [1, $INT_MAX, $INT_MIN]);
    }
    {
      my $sp_values = SPVM::new_larray([1, $LONG_MAX, $LONG_MIN]);
      my $values = $sp_values->to_elems;
      is_deeply($values, [1, $LONG_MAX, $LONG_MIN]);
    }
  }

  # to_bin 0 length
  {
    {
      my $sp_values = SPVM::new_barray([]);
      my $binary = $sp_values->to_bin;
      is($binary, "");
    }
    {
      my $sp_values = SPVM::new_sarray([]);
      my $binary = $sp_values->to_bin;
      is($binary, "");
    }
    {
      my $sp_values = SPVM::new_iarray([]);
      my $binary = $sp_values->to_bin;
      is($binary, "");
    }
    {
      my $sp_values = SPVM::new_larray([]);
      my $binary = $sp_values->to_bin;
      is($binary, "");
    }
    {
      my $sp_values = SPVM::new_farray([]);
      my $binary = $sp_values->to_bin;
      is($binary, "");
    }
    {
      my $sp_values = SPVM::new_darray([]);
      my $binary = $sp_values->to_bin;
      is($binary, "");
    }
  }
    
  # to_bin(
  {
    {
      my $sp_values = SPVM::new_barray([1, 2, $BYTE_MAX]);
      my $binary = $sp_values->to_bin;
      
      my @values = unpack('c3', $binary);
      is_deeply(\@values, [1, 2, $BYTE_MAX]);
    }
    {
      my $sp_values = SPVM::new_sarray([1, 2, $SHORT_MAX]);
      my $binary = $sp_values->to_bin;
      
      my @values = unpack('s3', $binary);
      is_deeply(\@values, [1, 2, $SHORT_MAX]);
    }
    {
      my $sp_values = SPVM::new_iarray([1, 2, $INT_MAX]);
      my $binary = $sp_values->to_bin;
      
      my @values = unpack('l3', $binary);
      is_deeply(\@values, [1, 2, $INT_MAX]);
    }
    {
      my $sp_values = SPVM::new_larray([1, 2, $LONG_MAX]);
      my $binary = $sp_values->to_bin;
      
      my @values = unpack('q3', $binary);
      is_deeply(\@values, [1, 2, $LONG_MAX]);
    }
    {
      my $sp_values = SPVM::new_farray([1, 2, $FLOAT_PRECICE]);
      my $binary = $sp_values->to_bin;
      
      my @values = unpack('f3', $binary);
      is_deeply(\@values, [1, 2, $FLOAT_PRECICE]);
    }
    {
      my $sp_values = SPVM::new_darray([1, 2, $DOUBLE_PRECICE]);
      my $binary = $sp_values->to_bin;
      
      my @values = unpack('d3', $binary);
      is_deeply(\@values, [1, 2, $DOUBLE_PRECICE]);
    }
  }

  # new_xxx_array_string
  {
    {
      my $sp_values = SPVM::new_barray_from_bin(encode('UTF-8', "あ"));
      ok(TestCase::ExchangeAPI->spvm_new_barray_from_bin($sp_values));
    }
  }
  
  # new_xxx_array_bin
  {
    {
      my $sp_values = SPVM::new_barray_from_bin("abc");
      ok(TestCase::ExchangeAPI->spvm_new_barray_bin($sp_values));
    }
    {
      my $binary = pack('c3', 97, 98, $BYTE_MAX);
      my $sp_values = SPVM::new_barray_from_bin($binary);
      ok(TestCase::ExchangeAPI->spvm_new_barray_binary_pack($sp_values));
    }
    {
      my $binary = pack('c3', 97, 98, $BYTE_MAX);
      my $sp_values = SPVM::new_barray_from_bin($binary);
      ok(TestCase::ExchangeAPI->spvm_new_barray_binary_pack($sp_values));
    }
    {
      my $binary = pack('s3', 97, 98, $SHORT_MAX);
      my $sp_values = SPVM::new_sarray_from_bin($binary);
      ok(TestCase::ExchangeAPI->spvm_new_sarray_binary_pack($sp_values));
    }
    {
      my $binary = pack('l3', 97, 98, $INT_MAX);
      my $sp_values = SPVM::new_iarray_from_bin($binary);
      ok(TestCase::ExchangeAPI->spvm_new_iarray_binary_pack($sp_values));
    }
    {
      my $binary = pack('q3', 97, 98, $LONG_MAX);
      my $sp_values = SPVM::new_larray_from_bin($binary);
      ok(TestCase::ExchangeAPI->spvm_new_larray_binary_pack($sp_values));
    }
    {
      my $binary = pack('f3', 97, 98, $FLOAT_PRECICE);
      my $sp_values = SPVM::new_farray_from_bin($binary);
      ok(TestCase::ExchangeAPI->spvm_new_farray_binary_pack($sp_values));
    }
    {
      my $binary = pack('d3', 97, 98, $DOUBLE_PRECICE);
      my $sp_values = SPVM::new_darray_from_bin($binary);
      ok(TestCase::ExchangeAPI->spvm_new_darray_binary_pack($sp_values));
    }
  }
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
}

# Complex
{
  my $z3 = SPVM::CORE->cadd({re => 0.25, im => 0.5}, {re => 0.5, im => 0.125});
  is_deeply($z3, {re => 0.75, im => 0.625});
}


# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

