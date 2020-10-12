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

use SPVM 'SPVM::Hash';
use SPVM 'SPVM::List';

use SPVM 'TestCase::Minimal';


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
my $FLT_MAX = POSIX::FLT_MAX();
my $DBL_MAX = POSIX::DBL_MAX();

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# ref SPVM array
{
  my $nums = SPVM::new_float_array([1, 2, 3]);
  is(ref $nums, 'SPVM::BlessedObject::Array');
}

# ref SPVM object
{
  my $minimal = TestCase::Minimal->new;
  
  is(ref $minimal, 'TestCase::Minimal');
}

# stringify SPVM object
{
  my $minimal = TestCase::Minimal->new;
  
  like("$minimal", qr/TestCase::Minimal/);
}

# set_exception
{
  # set_exception - string
  {
    SPVM::set_exception("あいう");
    ok(TestCase::ExchangeAPI->set_exception);
  }
  
  # set_exception - undef
  {
    SPVM::set_exception(undef);
    ok(TestCase::ExchangeAPI->set_exception_undef);
  }
}

# exception
{
  # exception - string
  {
    SPVM::set_exception("あいう");
    is(SPVM::get_exception, "あいう");
  }

  # exception - undef
  {
    SPVM::set_exception(undef);
    ok(!SPVM::get_exception);
  }
}

# Retrun numeric
{
  # Retrun numeric - byte
  {
    my $val = TestCase::ExchangeAPI->return_byte;
    is($val, $BYTE_MIN);
  }
  
  # Retrun numeric - short
  {
    my $val = TestCase::ExchangeAPI->return_short;
    is($val, $SHORT_MIN);
  }
  
  # Retrun numeric - int
  {
    my $val = TestCase::ExchangeAPI->return_int;
    is($val, $INT_MIN);
  }
  
  # Retrun numeric - long
  {
    my $val = TestCase::ExchangeAPI->return_long;
    is($val, $LONG_MIN);
  }
  
  # Retrun numeric - float
  {
    my $val = TestCase::ExchangeAPI->return_float;
    is($val, $FLT_MIN);
  }
  
  # Retrun numeric - double
  {
    my $val = TestCase::ExchangeAPI->return_double;
    is($val, $DBL_MIN);
  }
}

# Retrun value
{
  # Retrun value - byte
  {
    my $val = TestCase::ExchangeAPI->return_byte_value;
    is_deeply($val, {x => 1, y => 2, z => $BYTE_MIN});
  }
  
  # Retrun value - short
  {
    my $val = TestCase::ExchangeAPI->return_short_value;
    is_deeply($val, {x => 1, y => 2, z => $SHORT_MIN});
  }
  
  # Retrun value - int
  {
    my $val = TestCase::ExchangeAPI->return_int_value;
    is_deeply($val, {x => 1, y => 2, z => $INT_MIN});
  }
  
  # Retrun value - long
  {
    my $val = TestCase::ExchangeAPI->return_long_value;
    is_deeply($val, {x => 1, y => 2, z => $LONG_MIN});
  }
  
  # Retrun value - float
  {
    my $val = TestCase::ExchangeAPI->return_float_value;
    is_deeply($val, {x => 1, y => 2, z => $FLT_MIN});
  }
  
  # Retrun value - double
  {
    my $val = TestCase::ExchangeAPI->return_double_value;
    is_deeply($val, {x => 1, y => 2, z => $DBL_MIN});
  }
}

# Retrun undef
{
  # Retrun undef
  {
    my $val = TestCase::ExchangeAPI->return_undef;
    ok(!defined $val);
  }
}

# Retrun array
{
  # Retrun array
  {
    my $vals = TestCase::ExchangeAPI->return_array->to_elems;
    is($vals->[0]->x, 1);
    is($vals->[0]->y, 2);
    is($vals->[1]->x, 3);
    is($vals->[1]->y, 4);
  }
}

# Retrun oarray
{
  # Retrun oarray
  {
    my $vals = TestCase::ExchangeAPI->return_oarray->to_elems;
    is($vals->[0]->x, 1);
    is($vals->[0]->y, 2);
    is($vals->[1]->x, 3);
    is($vals->[1]->y, 4);
  }
}

# Pass hash
{
  # Pass hash
  {
    my $hash = SPVM::Hash->newa([x => SPVM::Int->new(1), y => SPVM::Double->new(2.5)]);
    is($hash->get("x")->val, 1);
    is($hash->get("y")->val, 2.5);
  }
}

# Pass list
{
  # Pass list
  {
    my $list = SPVM::List->newa([SPVM::Int->new(1), SPVM::Double->new(2.5), undef]);
    my $x = $list->get(0);
    
    is($list->get(0)->val, 1);
    is($list->get(1)->val, 2.5);
    ok(!defined $list->get(2));
  }
}

# Numeric value to numeric object
{
  # Numeric value to numeric object - number to SPVM::Byte
  {
    my $val = TestCase::ExchangeAPI->return_byte_object_only(SPVM::Byte->new($BYTE_MAX))->val;
    is($val, $BYTE_MAX);
  }

  # Numeric value to numeric object - number to SPVM::Short
  {
    my $val = TestCase::ExchangeAPI->return_short_object_only(SPVM::Short->new($SHORT_MAX))->val;
    is($val, $SHORT_MAX);
  }

  # Numeric value to numeric object - number to SPVM::Int
  {
    my $val = TestCase::ExchangeAPI->return_int_object_only(SPVM::Int->new($INT_MAX))->val;
    is($val, $INT_MAX);
  }

  # Numeric value to numeric object - number to SPVM::Long
  {
    my $val = TestCase::ExchangeAPI->return_long_object_only(SPVM::Long->new($LONG_MAX))->val;
    is($val, $LONG_MAX);
  }

  # Numeric value to numeric object - number to SPVM::Float
  {
    my $val = TestCase::ExchangeAPI->return_float_object_only(SPVM::Float->new($FLT_MAX))->val;
    is($val, $FLT_MAX);
  }

  # Numeric value to numeric object - number to SPVM::Double
  {
    my $val = TestCase::ExchangeAPI->return_double_object_only(SPVM::Double->new($DBL_MAX))->val;
    is($val, $DBL_MAX);
  }
}

# Any object array
{
  # String - UTF-8 string, new_string, new_string_from_bin, to_string, to_bin
  {
    my $bytes = SPVM::new_object_array("SPVM::Byte[]", [SPVM::Byte->new(1), SPVM::Byte->new(2), SPVM::Byte->new(3)]);
    my $ret = TestCase::ExchangeAPI->any_object_array($bytes);
    
    isa_ok($ret, 'SPVM::BlessedObject::Array');
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

  # String argument - numerci
  {
    my $string = TestCase::ExchangeAPI->string_argments_and_return_value(3, 4.12);
    is("$string", "34.12");
  }
}

# Stringfy
{
  # Stringfy - stringify overload
  {
    my $string1 = SPVM::new_string("あいう");
    my $string2 = SPVM::new_string("");
    my $string3 = TestCase::ExchangeAPI->string_argments_and_return_value($string1, $string2);
    isa_ok($string3, 'SPVM::BlessedObject::Array');
    is("$string3", "あいう");
  }
  
  # Stringify - 0 is true
  {
    my $string1 = SPVM::new_string("0");
    ok($string1);
    is("$string1", "0");
  }
}

# String arguments and return value
{
  # String - UTF-8 string, new_string, new_string_from_bin, to_string, to_bin
  {
    my $string1 = SPVM::new_string("あいう");
    my $string2 = SPVM::new_string_from_bin(encode('UTF-8', "えお"));
    my $string3 = TestCase::ExchangeAPI->string_argments_and_return_value($string1, $string2);
    isa_ok($string3, 'SPVM::BlessedObject::Array');
    is($string3->to_string, "あいうえお");
    is($string3->to_bin, encode('UTF-8', "あいうえお"));
  }

  # String - ascii string, new_string, new_string_from_bin, to_string, to_bin, to_element
  {
    my $string1 = SPVM::new_string_from_bin("abc");
    my $string2 = SPVM::new_string("de");
    my $string3 = TestCase::ExchangeAPI->string_argments_and_return_value($string1, $string2);
    isa_ok($string3, 'SPVM::BlessedObject::Array');
    is($string3->to_string, "abcde");
    is($string3->to_bin, "abcde");
    is_deeply($string3->to_elems, [ord('a'), ord('b'), ord('c'), ord('d'), ord('e')]);
  }
}

# Argument value
{
  # Argument value - byte
  {
    my $input = {x => 1, y => 3, z => $BYTE_MAX};
    my $output = TestCase::ExchangeAPI->call_sub_value_arg_byte($input);
    is_deeply($output, $input);
  }

  # Argument value - short
  {
    my $input = {x => 1, y => 3, z => $SHORT_MAX};
    my $output = TestCase::ExchangeAPI->call_sub_value_arg_short($input);
    is_deeply($output, $input);
  }

  # Argument value - int
  {
    my $input = {x => 1, y => 3, z => $INT_MAX};
    my $output = TestCase::ExchangeAPI->call_sub_value_arg_int($input);
    is_deeply($output, $input);
  }

  # Argument value - long
  {
    my $input = {x => 1, y => 3, z => $LONG_MAX};
    my $output = TestCase::ExchangeAPI->call_sub_value_arg_long($input);
    is_deeply($output, $input);
  }

  # Argument value - float
  {
    my $input = {x => 1, y => 3, z => $FLT_MAX};
    my $output = TestCase::ExchangeAPI->call_sub_value_arg_float($input);
    is_deeply($output, $input);
  }

  # Argument value - double
  {
    my $input = {x => 1, y => 3, z => $DBL_MAX};
    my $output = TestCase::ExchangeAPI->call_sub_value_arg_double($input);
    is_deeply($output, $input);
  }
}

# Argument value exception
{
  # Argument value exception - byte, field not found
  {
    my $input = {x => 1, y => 3};
    eval { TestCase::ExchangeAPI->call_sub_value_arg_byte($input) };
    ok($@);
  }

  # Argument value - short, field not found
  {
    my $input = {x => 1, y => 3};
    eval { TestCase::ExchangeAPI->call_sub_value_arg_short($input) };
    ok($@);
  }

  # Argument value - int, field not found
  {
    my $input = {x => 1, y => 3};
    eval { TestCase::ExchangeAPI->call_sub_value_arg_int($input) };
    ok($@);
  }

  # Argument value - long, field not found
  {
    my $input = {x => 1, y => 3};
    eval { TestCase::ExchangeAPI->call_sub_value_arg_long($input) };
    ok($@);
  }

  # Argument value - float, field not found
  {
    my $input = {x => 1, y => 3};
    eval { TestCase::ExchangeAPI->call_sub_value_arg_float($input) };
    ok($@);
  }

  # Argument value - double, field not found
  {
    my $input = {x => 1, y => 3};
    eval { TestCase::ExchangeAPI->call_sub_value_arg_double($input) };
    ok($@);
  }

  # Argument value exception - byte, not hash reference
  {
    my $input = 1;
    eval { TestCase::ExchangeAPI->call_sub_value_arg_byte($input) };
    ok($@);
  }

  # Argument value - short, not hash reference
  {
    my $input = 1;
    eval { TestCase::ExchangeAPI->call_sub_value_arg_short($input) };
    ok($@);
  }

  # Argument value - int, not hash reference
  {
    my $input = 1;
    eval { TestCase::ExchangeAPI->call_sub_value_arg_int($input) };
    ok($@);
  }

  # Argument value - long, not hash reference
  {
    my $input = 1;
    eval { TestCase::ExchangeAPI->call_sub_value_arg_long($input) };
    ok($@);
  }

  # Argument value - float, not hash reference
  {
    my $input = 1;
    eval { TestCase::ExchangeAPI->call_sub_value_arg_float($input) };
    ok($@);
  }

  # Argument value - double, not hash reference
  {
    my $input = 1;
    eval { TestCase::ExchangeAPI->call_sub_value_arg_double($input) };
    ok($@);
  }
}

# Argument numeric reference
{
  # Argument numeric reference - byte
  {
    my $num_byte = $BYTE_MIN;
    TestCase::ExchangeAPI->call_sub_numeric_ref_arg_byte(\$num_byte);
    is($num_byte, $BYTE_MIN + 1);
  }
  # Argument numeric reference - short
  {
    my $num_short = $SHORT_MIN;
    TestCase::ExchangeAPI->call_sub_numeric_ref_arg_short(\$num_short);
    is($num_short, $SHORT_MIN + 1);
  }
  # Argument numeric reference - int
  {
    my $num_int = $INT_MIN;
    TestCase::ExchangeAPI->call_sub_numeric_ref_arg_int(\$num_int);
    is($num_int, $INT_MIN + 1);
  }
  # Argument numeric reference - long
  {
    my $num_long = $LONG_MIN;
    TestCase::ExchangeAPI->call_sub_numeric_ref_arg_long(\$num_long);
    is($num_long, $LONG_MIN + 1);
  }
  # Argument numeric reference - float
  {
    my $num_float = POSIX::FLT_MIN();
    TestCase::ExchangeAPI->call_sub_numeric_ref_arg_float(\$num_float);
    is($num_float, POSIX::FLT_MIN() + 1);
  }
  # Argument numeric reference - double
  {
    my $num_double = POSIX::DBL_MIN();
    TestCase::ExchangeAPI->call_sub_numeric_ref_arg_double(\$num_double);
    is($num_double, POSIX::DBL_MIN() + 1);
  }
}

# Argument numeric reference exception
{
  # Argument numeric reference exception - byte
  {
    my $num_byte = $BYTE_MIN;
    eval { TestCase::ExchangeAPI->call_sub_numeric_ref_arg_byte($num_byte) };
    ok($@);
  }
  # Argument numeric reference exception - short
  {
    my $num_short = $SHORT_MIN;
    eval { TestCase::ExchangeAPI->call_sub_numeric_ref_arg_short($num_short) };
    ok($@);
  }
  # Argument numeric reference exception - int
  {
    my $num_int = $INT_MIN;
    eval { TestCase::ExchangeAPI->call_sub_numeric_ref_arg_int($num_int) };
    ok($@);
  }
  # Argument numeric reference exception - long
  {
    my $num_long = $LONG_MIN;
    eval { TestCase::ExchangeAPI->call_sub_numeric_ref_arg_long($num_long) };
    ok($@);
  }
  # Argument numeric reference exception - float
  {
    my $num_float = POSIX::FLT_MIN();
    eval { TestCase::ExchangeAPI->call_sub_numeric_ref_arg_float($num_float) };
    ok($@);
  }
  # Argument numeric reference exception - double
  {
    my $num_double = POSIX::DBL_MIN();
    eval { TestCase::ExchangeAPI->call_sub_numeric_ref_arg_double($num_double) };
    ok($@);
  }
}

# Argument value reference
{
  # Argument value reference - byte
  {
    my $point = {x => $BYTE_MIN, y => 1, z => 2};
    TestCase::ExchangeAPI->call_sub_value_ref_arg_byte(\$point);
    is_deeply($point, {x => $BYTE_MIN + 1, y => 2, z => 3});
  }
  # Argument value reference - short
  {
    my $point = {x => $SHORT_MIN, y => 1, z => 2};
    TestCase::ExchangeAPI->call_sub_value_ref_arg_short(\$point);
    is_deeply($point, {x => $SHORT_MIN + 1, y => 2, z => 3});
  }
  # Argument value reference - int
  {
    my $point = {x => $INT_MIN, y => 1, z => 2};
    TestCase::ExchangeAPI->call_sub_value_ref_arg_int(\$point);
    is_deeply($point, {x => $INT_MIN + 1, y => 2, z => 3});
  }
  # Argument value reference - long
  {
    my $point = {x => $LONG_MIN, y => 1, z => 2};
    TestCase::ExchangeAPI->call_sub_value_ref_arg_long(\$point);
    is_deeply($point, {x => $LONG_MIN + 1, y => 2, z => 3});
  }
  # Argument value reference - float
  {
    my $point = {x => $FLT_MIN, y => 1, z => 2};
    TestCase::ExchangeAPI->call_sub_value_ref_arg_float(\$point);
    is_deeply($point, {x => $FLT_MIN + 1, y => 2, z => 3});
  }
  # Argument value reference - double
  {
    my $point = {x => $DBL_MIN, y => 1, z => 2};
    TestCase::ExchangeAPI->call_sub_value_ref_arg_double(\$point);
    is_deeply($point, {x => $DBL_MIN + 1, y => 2, z => 3});
  }
}

# Argument value reference exception
{
  # Argument value reference exception - byte, key not found
  {
    my $point = {x => $BYTE_MIN, y => 1};
    eval { TestCase::ExchangeAPI->call_sub_value_ref_arg_byte(\$point) };
    ok($@);
  }
  # Argument value reference exception - short, key not found
  {
    my $point = {x => $SHORT_MIN, y => 1};
    eval { TestCase::ExchangeAPI->call_sub_value_ref_arg_short(\$point) };
    ok($@);
  }
  # Argument value reference exception - int, key not found
  {
    my $point = {x => $INT_MIN, y => 1};
    eval { TestCase::ExchangeAPI->call_sub_value_ref_arg_int(\$point) };
    ok($@);
  }
  # Argument value reference exception - long, key not found
  {
    my $point = {x => $LONG_MIN, y => 1};
    eval { TestCase::ExchangeAPI->call_sub_value_ref_arg_long(\$point) };
    ok($@);
  }
  # Argument value reference exception - float, key not found
  {
    my $point = {x => $FLT_MIN, y => 1};
    eval { TestCase::ExchangeAPI->call_sub_value_ref_arg_float(\$point) };
    ok($@);
  }
  # Argument value reference exception - double, key not found
  {
    my $point = {x => $DBL_MIN, y => 1};
    eval { TestCase::ExchangeAPI->call_sub_value_ref_arg_double(\$point) };
    ok($@);
  }

  # Argument value reference exception - byte, not reference of hash reference
  {
    my $point = {x => $BYTE_MIN, y => 1, z => 2};
    eval { TestCase::ExchangeAPI->call_sub_value_ref_arg_byte($point) };
    ok($@);
  }
  # Argument value reference exception - short, not reference of hash reference
  {
    my $point = {x => $SHORT_MIN, y => 1, z => 2};
    eval { TestCase::ExchangeAPI->call_sub_value_ref_arg_short($point) };
    ok($@);
  }
  # Argument value reference exception - int, not reference of hash reference
  {
    my $point = {x => $INT_MIN, y => 1, z => 2};
    eval { TestCase::ExchangeAPI->call_sub_value_ref_arg_int($point) };
    ok($@);
  }
  # Argument value reference exception - long, not reference of hash reference
  {
    my $point = {x => $LONG_MIN, y => 1, z => 2};
    eval { TestCase::ExchangeAPI->call_sub_value_ref_arg_long($point) };
    ok($@);
  }
  # Argument value reference exception - float, not reference of hash reference
  {
    my $point = {x => $FLT_MIN, y => 1, z => 2};
    eval { TestCase::ExchangeAPI->call_sub_value_ref_arg_float($point) };
    ok($@);
  }
  # Argument value reference exception - double, not reference of hash reference
  {
    my $point = {x => $DBL_MIN, y => 1, z => 2};
    eval { TestCase::ExchangeAPI->call_sub_value_ref_arg_double($point) };
    ok($@);
  }

}

# Argument value reference and numeric reference mixed
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


# Object
{
  # Create object
  {
    my $object = TestCase->new();
    $object->set_x_iarray(SPVM::new_int_array([$INT_MAX, $INT_MAX]));
    my $spvm_values = SPVM::new_byte_array_from_bin("abc");
    $object->set_x_barray($spvm_values);
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
    $object->set_x_iarray(SPVM::new_int_array([1, 2, 3, 4]));
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

# my variable
{
  ok(TestCase->my_var_initialized_zero());
  ok(TestCase->my_var_initialized_zero());
}

{
  ok(TestCase->new_near_small_base_object_max_byte_size_use_memory_pool());
}

# SPVM new_object_array
{

  # element object array
  {
    my $object1 = TestCase->new();
    $object1->set_x_int(1);
    my $object2 = TestCase->new();
    $object2->set_x_int(2);
    my $spvm_oarray = SPVM::new_object_array("TestCase[]", [$object1, $object2]);
    
    ok(TestCase::ExchangeAPI->spvm_new_object_array_len_element_oarray($spvm_oarray));
    
    my $oarray_out = $spvm_oarray->to_elems;
    is($oarray_out->[0]->get_x_int, 1);
    is($oarray_out->[1]->get_x_int, 2);
  }
  # element byte array
  {
    my $object1 = SPVM::new_byte_array([1, 2, 3]);
    my $object2 = SPVM::new_byte_array([4, 5, 6]);
    my $oarray = SPVM::new_object_array("byte[][]", [$object1, $object2]);

    ok(TestCase::ExchangeAPI->spvm_new_object_array_len_element_barray($oarray));
    
    my $oarray_out = $oarray->to_elems;
    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element short array
  {
    my $object1 = SPVM::new_short_array([1, 2, 3]);
    my $object2 = SPVM::new_short_array([4, 5, 6]);
    my $oarray = SPVM::new_object_array("short[][]", [$object1, $object2]);

    ok(TestCase::ExchangeAPI->spvm_new_object_array_len_element_sarray($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element int array
  {
    my $object1 = SPVM::new_int_array([1, 2, 3]);
    my $object2 = SPVM::new_int_array([4, 5, 6]);
    my $oarray = SPVM::new_object_array("int[][]", [$object1, $object2]);

    ok(TestCase::ExchangeAPI->spvm_new_object_array_len_element_iarray($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element long array
  {
    my $object1 = SPVM::new_long_array([1, 2, 3]);
    my $object2 = SPVM::new_long_array([4, 5, 6]);
    my $oarray = SPVM::new_object_array("long[][]", [$object1, $object2]);
    ok(TestCase::ExchangeAPI->spvm_new_object_array_len_element_larray($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element float array
  {
    my $object1 = SPVM::new_float_array([1, 2, 3]);
    my $object2 = SPVM::new_float_array([4, 5, 6]);
    my $oarray = SPVM::new_object_array("float[][]", [$object1, $object2]);

    ok(TestCase::ExchangeAPI->spvm_new_object_array_len_element_farray($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element double array
  {
    my $object1 = SPVM::new_double_array([1, 2, 3]);
    my $object2 = SPVM::new_double_array([4, 5, 6]);
    my $oarray = SPVM::new_object_array("double[][]", [$object1, $object2]);
    
    ok(TestCase::ExchangeAPI->spvm_new_object_array_len_element_darray($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }
}

# new_mulnum_array
{
  
  # new_mulnum_array - byte
  {
    my $values = [
      {x => $BYTE_MIN, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_values = SPVM::new_mulnum_array("TestCase::Point_3b[]", $values);
    ok(TestCase::ExchangeAPI->spvm_new_mulnum_array_byte($spvm_values));
    my $out_values = $spvm_values->to_elems;
    is_deeply($out_values, $values);
  }

  # new_mulnum_array - short
  {
    my $values = [
      {x => $SHORT_MIN, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_values = SPVM::new_mulnum_array("TestCase::Point_3s[]", $values);
    ok(TestCase::ExchangeAPI->spvm_new_mulnum_array_short($spvm_values));
    my $out_values = $spvm_values->to_elems;
    is_deeply($out_values, $values);
  }

  # new_mulnum_array - int
  {
    my $values = [
      {x => $INT_MIN, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_values = SPVM::new_mulnum_array("TestCase::Point_3i[]", $values);
    ok(TestCase::ExchangeAPI->spvm_new_mulnum_array_int($spvm_values));
    my $out_values = $spvm_values->to_elems;
    is_deeply($out_values, $values);
  }

  # new_mulnum_array - long
  {
    my $values = [
      {x => $LONG_MIN, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_values = SPVM::new_mulnum_array("TestCase::Point_3l[]", $values);
    ok(TestCase::ExchangeAPI->spvm_new_mulnum_array_long($spvm_values));
    my $out_values = $spvm_values->to_elems;
    is_deeply($out_values, $values);
  }

  # new_mulnum_array - float
  {
    my $values = [
      {x => $FLT_MIN, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_values = SPVM::new_mulnum_array("TestCase::Point_3f[]", $values);
    ok(TestCase::ExchangeAPI->spvm_new_mulnum_array_float($spvm_values));
    my $out_values = $spvm_values->to_elems;
    is_deeply($out_values, $values);
  }

  # new_mulnum_array - double
  {
    my $values = [
      {x => $DBL_MIN, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_values = SPVM::new_mulnum_array("TestCase::Point_3d[]", $values);
    ok(TestCase::ExchangeAPI->spvm_new_mulnum_array_double($spvm_values));
    my $out_values = $spvm_values->to_elems;
    is_deeply($out_values, $values);
  }
}

# new_mulnum_array_from_bin
{
  # new_mulnum_array_from_bin - byte
  {
    my $binary = pack('c9', ($BYTE_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_values = SPVM::new_mulnum_array_from_bin("TestCase::Point_3b[]", $binary);
    ok(TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_byte($spvm_values));
    my $out_bin = $spvm_values->to_bin;
    is_deeply($out_bin, $binary);
  }

  # new_mulnum_array_from_bin - short
  {
    my $binary = pack('s9', ($SHORT_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_values = SPVM::new_mulnum_array_from_bin("TestCase::Point_3s[]", $binary);
    ok(TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_short($spvm_values));
    my $out_bin = $spvm_values->to_bin;
    is_deeply($out_bin, $binary);
  }
  
  # new_mulnum_array_from_bin - int
  {
    my $binary = pack('l9', ($INT_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_values = SPVM::new_mulnum_array_from_bin("TestCase::Point_3i[]", $binary);
    ok(TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_int($spvm_values));
    my $out_bin = $spvm_values->to_bin;
    is_deeply($out_bin, $binary);
  }
  # new_mulnum_array_from_bin - long
  {
    my $binary = pack('q9', ($LONG_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_values = SPVM::new_mulnum_array_from_bin("TestCase::Point_3l[]", $binary);
    ok(TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_long($spvm_values));
    my $out_bin = $spvm_values->to_bin;
    is_deeply($out_bin, $binary);
  }
  # new_mulnum_array_from_bin - float
  {
    my $binary = pack('f9', ($FLT_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_values = SPVM::new_mulnum_array_from_bin("TestCase::Point_3f[]", $binary);
    ok(TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_float($spvm_values));
    my $out_bin = $spvm_values->to_bin;
    is_deeply($out_bin, $binary);
  }
  # new_mulnum_array_from_bin - double
  {
    my $binary = pack('d9', ($DBL_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_values = SPVM::new_mulnum_array_from_bin("TestCase::Point_3d[]", $binary);
    ok(TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_double($spvm_values));
    my $out_bin = $spvm_values->to_bin;
    is_deeply($out_bin, $binary);
  }

  # new_mulnum_array_from_bin - double
  {
    my $binary = pack('d8', ($DBL_MIN, 1, 2), (3, 4, 5), (6, 7));
    eval {
      SPVM::new_mulnum_array_from_bin("TestCase::Point_3d[]", $binary);
    };
    ok($@);
  }
}

# call_sub can receive array reference
{
  # call_sub can receive array reference - new_byte_array
  {
    my $spvm_values = [1, $BYTE_MAX, $BYTE_MIN];
    my $values = TestCase::ExchangeAPI->return_byte_array_only($spvm_values)->to_elems;
    is_deeply($values, [1, $BYTE_MAX, $BYTE_MIN]);
  }
  # call_sub can receive array reference - new_short_array
  {
    my $spvm_values = [1, $SHORT_MAX, $SHORT_MIN];
    my $values = TestCase::ExchangeAPI->return_short_array_only($spvm_values)->to_elems;
    is_deeply($values, [1, $SHORT_MAX, $SHORT_MIN]);
  }
  # call_sub can receive array reference - new_int_array
  {
    my $spvm_values = [1, $INT_MAX, $INT_MIN];
    my $values = TestCase::ExchangeAPI->return_int_array_only($spvm_values)->to_elems;
    is_deeply($values, [1, $INT_MAX, $INT_MIN]);
  }
  # call_sub can receive array reference - new_long_array
  {
    my $spvm_values = [1, $LONG_MAX, $LONG_MIN];
    my $values = TestCase::ExchangeAPI->return_long_array_only($spvm_values)->to_elems;
    is_deeply($values, [1, $LONG_MAX, $LONG_MIN]);
  }
  # call_sub can receive array reference - new_float_array
  {
    my $spvm_values = [0.5, $FLT_MAX, $FLT_MIN];
    my $values = TestCase::ExchangeAPI->return_float_array_only($spvm_values)->to_elems;
    is_deeply($values, [0.5, $FLT_MAX, $FLT_MIN]);
  }
  # call_sub can receive array reference - new_double_array
  {
    my $spvm_values = [0.5, $DBL_MAX, $DBL_MIN];
    my $values = TestCase::ExchangeAPI->return_double_array_only($spvm_values)->to_elems;
    is_deeply($values, [0.5, $DBL_MAX, $DBL_MIN]);
  }

  # call_sub can receive array reference - new string array and to_strings
  {
    my $spvm_values = ["あいう", "えお", "ab", undef];
    my $values = TestCase::ExchangeAPI->return_string_array_only($spvm_values)->to_strings;
    is_deeply($values, ["あいう", "えお", "ab", undef]);
  }
}

# new array
{
  # new_byte_array
  {
    my $spvm_values = SPVM::new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
    my $values = $spvm_values->to_elems;
    is_deeply($values, [1, $BYTE_MAX, $BYTE_MIN]);
  }
  # new_short_array
  {
    my $spvm_values = SPVM::new_short_array([1, $SHORT_MAX, $SHORT_MIN]);
    my $values = $spvm_values->to_elems;
    is_deeply($values, [1, $SHORT_MAX, $SHORT_MIN]);
  }
  # new_int_array
  {
    my $spvm_values = SPVM::new_int_array([1, $INT_MAX, $INT_MIN]);
    my $values = $spvm_values->to_elems;
    is_deeply($values, [1, $INT_MAX, $INT_MIN]);
  }
  # new_long_array
  {
    my $spvm_values = SPVM::new_long_array([1, $LONG_MAX, $LONG_MIN]);
    my $values = $spvm_values->to_elems;
    is_deeply($values, [1, $LONG_MAX, $LONG_MIN]);
  }
  # new_float_array
  {
    my $spvm_values = SPVM::new_float_array([0.5, $FLT_MAX, $FLT_MIN]);
    my $values = $spvm_values->to_elems;
    is_deeply($values, [0.5, $FLT_MAX, $FLT_MIN]);
  }
  # new_double_array
  {
    my $spvm_values = SPVM::new_double_array([0.5, $DBL_MAX, $DBL_MIN]);
    my $values = $spvm_values->to_elems;
    is_deeply($values, [0.5, $DBL_MAX, $DBL_MIN]);
  }
}

# get_length
{
  {
    my $spvm_values = SPVM::new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
    my $length = $spvm_values->get_length;
    is($length, 3);
  }
  {
    my $spvm_values = SPVM::new_short_array([1, $SHORT_MAX, $SHORT_MIN]);
    my $length = $spvm_values->get_length;
    is($length, 3);
  }
  {
    my $spvm_values = SPVM::new_int_array([1, $INT_MAX, $INT_MIN]);
    my $length = $spvm_values->get_length;
    is($length, 3);
  }
  {
    my $spvm_values = SPVM::new_long_array([1, $LONG_MAX, $LONG_MIN]);
    my $length = $spvm_values->get_length;
    is($length, 3);
  }
}

# to_elems
{
  # to_elems
  {
    {
      my $spvm_values = SPVM::new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
      my $values = $spvm_values->to_elems;
      is_deeply($values, [1, $BYTE_MAX, $BYTE_MIN]);
    }
    {
      my $spvm_values = SPVM::new_short_array([1, $SHORT_MAX, $SHORT_MIN]);
      my $values = $spvm_values->to_elems;
      is_deeply($values, [1, $SHORT_MAX, $SHORT_MIN]);
    }
    {
      my $spvm_values = SPVM::new_int_array([1, $INT_MAX, $INT_MIN]);
      my $values = $spvm_values->to_elems;
      is_deeply($values, [1, $INT_MAX, $INT_MIN]);
    }
    {
      my $spvm_values = SPVM::new_long_array([1, $LONG_MAX, $LONG_MIN]);
      my $values = $spvm_values->to_elems;
      is_deeply($values, [1, $LONG_MAX, $LONG_MIN]);
    }
  }
}

# to_bin
{
  # to_bin 0 length
  {
    {
      my $spvm_values = SPVM::new_byte_array([]);
      my $binary = $spvm_values->to_bin;
      is($binary, "");
    }
    {
      my $spvm_values = SPVM::new_short_array([]);
      my $binary = $spvm_values->to_bin;
      is($binary, "");
    }
    {
      my $spvm_values = SPVM::new_int_array([]);
      my $binary = $spvm_values->to_bin;
      is($binary, "");
    }
    {
      my $spvm_values = SPVM::new_long_array([]);
      my $binary = $spvm_values->to_bin;
      is($binary, "");
    }
    {
      my $spvm_values = SPVM::new_float_array([]);
      my $binary = $spvm_values->to_bin;
      is($binary, "");
    }
    {
      my $spvm_values = SPVM::new_double_array([]);
      my $binary = $spvm_values->to_bin;
      is($binary, "");
    }
  }
    
  # to_bin(
  {
    {
      my $spvm_values = SPVM::new_byte_array([1, 2, $BYTE_MAX]);
      my $binary = $spvm_values->to_bin;
      
      my @values = unpack('c3', $binary);
      is_deeply(\@values, [1, 2, $BYTE_MAX]);
    }
    {
      my $spvm_values = SPVM::new_short_array([1, 2, $SHORT_MAX]);
      my $binary = $spvm_values->to_bin;
      
      my @values = unpack('s3', $binary);
      is_deeply(\@values, [1, 2, $SHORT_MAX]);
    }
    {
      my $spvm_values = SPVM::new_int_array([1, 2, $INT_MAX]);
      my $binary = $spvm_values->to_bin;
      
      my @values = unpack('l3', $binary);
      is_deeply(\@values, [1, 2, $INT_MAX]);
    }
    {
      my $spvm_values = SPVM::new_long_array([1, 2, $LONG_MAX]);
      my $binary = $spvm_values->to_bin;
      
      my @values = unpack('q3', $binary);
      is_deeply(\@values, [1, 2, $LONG_MAX]);
    }
    {
      my $spvm_values = SPVM::new_float_array([1, 2, $FLOAT_PRECICE]);
      my $binary = $spvm_values->to_bin;
      
      my @values = unpack('f3', $binary);
      is_deeply(\@values, [1, 2, $FLOAT_PRECICE]);
    }
    {
      my $spvm_values = SPVM::new_double_array([1, 2, $DOUBLE_PRECICE]);
      my $binary = $spvm_values->to_bin;
      
      my @values = unpack('d3', $binary);
      is_deeply(\@values, [1, 2, $DOUBLE_PRECICE]);
    }
  }

  # new_xxx_array_string
  {
    {
      my $spvm_values = SPVM::new_byte_array_from_bin(encode('UTF-8', "あ"));
      ok(TestCase::ExchangeAPI->spvm_new_byte_array_from_bin($spvm_values));
    }
  }
  
  # new_xxx_array_bin
  {
    {
      my $spvm_values = SPVM::new_byte_array_from_bin("abc");
      ok(TestCase::ExchangeAPI->spvm_new_byte_array_bin($spvm_values));
    }
    {
      my $binary = pack('c*', 97, 98, $BYTE_MAX);
      my $spvm_values = SPVM::new_byte_array_from_bin($binary);
      ok(TestCase::ExchangeAPI->spvm_new_byte_array_binary_pack($spvm_values));
    }
    {
      my $binary = pack('c*', 97, 98, $BYTE_MAX);
      my $spvm_values = SPVM::new_byte_array_from_bin($binary);
      ok(TestCase::ExchangeAPI->spvm_new_byte_array_binary_pack($spvm_values));
    }
    {
      my $binary = pack('s*', 97, 98, $SHORT_MAX);
      my $spvm_values = SPVM::new_short_array_from_bin($binary);
      ok(TestCase::ExchangeAPI->spvm_new_short_array_binary_pack($spvm_values));
    }
    {
      my $binary = pack('l*', 97, 98, $INT_MAX);
      my $spvm_values = SPVM::new_int_array_from_bin($binary);
      ok(TestCase::ExchangeAPI->spvm_new_int_array_binary_pack($spvm_values));
    }
    {
      my $binary = pack('q*', 97, 98, $LONG_MAX);
      my $spvm_values = SPVM::new_long_array_from_bin($binary);
      ok(TestCase::ExchangeAPI->spvm_new_long_array_binary_pack($spvm_values));
    }
    {
      my $binary = pack('f*', 97, 98, $FLOAT_PRECICE);
      my $spvm_values = SPVM::new_float_array_from_bin($binary);
      ok(TestCase::ExchangeAPI->spvm_new_float_array_binary_pack($spvm_values));
    }
    {
      my $binary = pack('d*', 97, 98, $DOUBLE_PRECICE);
      my $spvm_values = SPVM::new_double_array_from_bin($binary);
      ok(TestCase::ExchangeAPI->spvm_new_double_array_binary_pack($spvm_values));
    }
  }
  
  # middle size array
  {
    my $length = 1_000_000;
    {
      my $binary = pack('l*', 1 .. $length);
      my $spvm_values = SPVM::new_int_array_from_bin($binary);
      is($spvm_values->get_length, $length);
    }
    {
      my $binary = pack('q*', 1 .. $length);
      my $spvm_values = SPVM::new_long_array_from_bin($binary);
      is($spvm_values->get_length, $length);
    }
    {
      my $binary = pack('f*', 1 .. $length);
      my $spvm_values = SPVM::new_float_array_from_bin($binary);
      is($spvm_values->get_length, $length);
    }
    {
      my $binary = pack('d*', 1 .. $length);
      my $spvm_values = SPVM::new_double_array_from_bin($binary);
      is($spvm_values->get_length, $length);
    }
    {
      my $binary = pack('f*', 1 .. $length);
      my $spvm_values = SPVM::new_float_array_from_bin($binary);
      is($spvm_values->get_length, $length);
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

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

