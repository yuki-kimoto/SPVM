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
use SPVM 'SPVM::ByteList';
use SPVM 'SPVM::ShortList';
use SPVM 'SPVM::IntList';
use SPVM 'SPVM::LongList';
use SPVM 'SPVM::FloatList';
use SPVM 'SPVM::DoubleList';
use SPVM 'SPVM::StringList';

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
my $UBYTE_MAX = 255;
my $USHORT_MAX = 65535;
my $UINT_MAX = 4294967295;
my $ULONG_MAX = 18446744073709551615;

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Argument Type
{
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
      is($values, "");
    }
  }
}

# Argument string
{
  # Argument string - ascii
  {
    my $string = TestCase::ExchangeAPI->string_argments_and_return_value("ABC", "DE");
    is("$string", "ABCDE");
  }

  # Argument string - UTF-8
  {
    my $string = TestCase::ExchangeAPI->string_argments_and_return_value("あいう", "えお");
    is("$string", "あいうえお");
  }

  # Argument string - ascii and utf8
  {
    my $string = TestCase::ExchangeAPI->string_argments_and_return_value("あいう", "DE");
    is("$string", "あいうDE");
  }

  # Argument string - numerci
  {
    my $string = TestCase::ExchangeAPI->string_argments_and_return_value(3, 4.12);
    is("$string", "34.12");
  }

  # Argument string - SPVM::BlessedObject::String
  {
    my $string = TestCase::ExchangeAPI->string_argments_and_return_value(SPVM::new_string("あいう"), SPVM::new_string_from_bin("abc"));
    is(ref $string, 'SPVM::BlessedObject::String');
    is("$string", "あいうabc");
  }
}

# Stringfy
{
  # Stringfy - stringify overload
  {
    my $string1 = "あいう";
    my $string2 = "";
    my $string3 = TestCase::ExchangeAPI->string_argments_and_return_value($string1, $string2);
    is(ref $string3, 'SPVM::BlessedObject::String');
    is("$string3", "あいう");
  }
}

# Argument string and return value
{
  # String - UTF-8 string
  {
    my $string1 = "あいう";
    my $string2 = "えお";
    my $string3 = TestCase::ExchangeAPI->string_argments_and_return_value($string1, $string2);
    is($string3, "あいうえお");
  }

  # String - ascii string
  {
    my $string1 = "abc";
    my $string2 = "de";
    my $string3 = TestCase::ExchangeAPI->string_argments_and_return_value($string1, $string2);
    is($string3, "abcde");
  }
}

# Argument Exception
{
  # Argument Exception - too few arguments
  {
    eval {
      SPVM::Int->new;
    };
    like($@, qr/too few arguments/i);
  }
  
  # Argument Exception - too many arguments
  {
    eval {
      SPVM::Int->new(1, 2);
    };
    like($@, qr/too many arguments/i);
  }
}

# Argument array reference
{
  # Argument array reference - new_byte_array
  {
    my $spvm_values = [1, $BYTE_MAX, $BYTE_MIN];
    my $values = TestCase::ExchangeAPI->return_byte_array_only($spvm_values)->to_elems;
    is_deeply($values, [1, $BYTE_MAX, $BYTE_MIN]);
  }
  # Argument array reference - new_short_array
  {
    my $spvm_values = [1, $SHORT_MAX, $SHORT_MIN];
    my $values = TestCase::ExchangeAPI->return_short_array_only($spvm_values)->to_elems;
    is_deeply($values, [1, $SHORT_MAX, $SHORT_MIN]);
  }
  # Argument array reference - new_int_array
  {
    my $spvm_values = [1, $INT_MAX, $INT_MIN];
    my $values = TestCase::ExchangeAPI->return_int_array_only($spvm_values)->to_elems;
    is_deeply($values, [1, $INT_MAX, $INT_MIN]);
  }
  # Argument array reference - new_long_array
  {
    my $spvm_values = [1, $LONG_MAX, $LONG_MIN];
    my $values = TestCase::ExchangeAPI->return_long_array_only($spvm_values)->to_elems;
    is_deeply($values, [1, $LONG_MAX, $LONG_MIN]);
  }
  # Argument array reference - new_float_array
  {
    my $spvm_values = [0.5, $FLT_MAX, $FLT_MIN];
    my $values = TestCase::ExchangeAPI->return_float_array_only($spvm_values)->to_elems;
    is_deeply($values, [0.5, $FLT_MAX, $FLT_MIN]);
  }
  # Argument array reference - new_double_array
  {
    my $spvm_values = [0.5, $DBL_MAX, $DBL_MIN];
    my $values = TestCase::ExchangeAPI->return_double_array_only($spvm_values)->to_elems;
    is_deeply($values, [0.5, $DBL_MAX, $DBL_MIN]);
  }

  # Argument array reference - new string array and to_strings
  {
    my $spvm_values = SPVM::new_string_array(["あいう", "えお", "ab", undef]);
    my $values = TestCase::ExchangeAPI->return_string_array_only($spvm_values)->to_elems;
    is_deeply($values, ["あいう", "えお", "ab", undef]);
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

# Return numeric
{
  # Return numeric - byte
  {
    my $val = TestCase::ExchangeAPI->return_byte;
    is($val, $BYTE_MIN);
  }
  
  # Return numeric - short
  {
    my $val = TestCase::ExchangeAPI->return_short;
    is($val, $SHORT_MIN);
  }
  
  # Return numeric - int
  {
    my $val = TestCase::ExchangeAPI->return_int;
    is($val, $INT_MIN);
  }
  
  # Return numeric - long
  {
    my $val = TestCase::ExchangeAPI->return_long;
    is($val, $LONG_MIN);
  }
  
  # Return numeric - float
  {
    my $val = TestCase::ExchangeAPI->return_float;
    is($val, $FLT_MIN);
  }
  
  # Return numeric - double
  {
    my $val = TestCase::ExchangeAPI->return_double;
    is($val, $DBL_MIN);
  }
}

# Return value
{
  # Return value - byte
  {
    my $val = TestCase::ExchangeAPI->return_byte_value;
    is_deeply($val, {x => 1, y => 2, z => $BYTE_MIN});
  }
  
  # Return value - short
  {
    my $val = TestCase::ExchangeAPI->return_short_value;
    is_deeply($val, {x => 1, y => 2, z => $SHORT_MIN});
  }
  
  # Return value - int
  {
    my $val = TestCase::ExchangeAPI->return_int_value;
    is_deeply($val, {x => 1, y => 2, z => $INT_MIN});
  }
  
  # Return value - long
  {
    my $val = TestCase::ExchangeAPI->return_long_value;
    is_deeply($val, {x => 1, y => 2, z => $LONG_MIN});
  }
  
  # Return value - float
  {
    my $val = TestCase::ExchangeAPI->return_float_value;
    is_deeply($val, {x => 1, y => 2, z => $FLT_MIN});
  }
  
  # Return value - double
  {
    my $val = TestCase::ExchangeAPI->return_double_value;
    is_deeply($val, {x => 1, y => 2, z => $DBL_MIN});
  }
}

# Return undef
{
  # Return undef
  {
    my $val = TestCase::ExchangeAPI->return_undef;
    ok(!defined $val);
  }
}

# Return array
{
  # Return array
  {
    my $vals = TestCase::ExchangeAPI->return_array->to_elems;
    is($vals->[0]->x, 1);
    is($vals->[0]->y, 2);
    is($vals->[1]->x, 3);
    is($vals->[1]->y, 4);
  }
}

# Return oarray
{
  # Return oarray
  {
    my $vals = TestCase::ExchangeAPI->return_oarray->to_elems;
    is($vals->[0]->x, 1);
    is($vals->[0]->y, 2);
    is($vals->[1]->x, 3);
    is($vals->[1]->y, 4);
  }
}

# Object
{
  # Create object
  {
    my $object = TestCase->new();
    $object->set_x_int_array(SPVM::new_int_array([$INT_MAX, $INT_MAX]));
    my $spvm_values = SPVM::new_byte_array_from_bin("abc");
    $object->set_x_byte_array($spvm_values);
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
    $object->set_x_int_array(SPVM::new_int_array([1, 2, 3, 4]));
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

# Pass list
{
  # Pass list
  {
    my $list = SPVM::List->new([SPVM::Int->new(1), SPVM::Double->new(2.5), undef]);
    my $x = $list->get(0);
    
    is($list->get(0)->value, 1);
    is($list->get(1)->value, 2.5);
    ok(!defined $list->get(2));
  }
}

# Numeric value to numeric object
{
  # Numeric value to numeric object - number to SPVM::Byte
  {
    my $val = TestCase::ExchangeAPI->return_byte_object_only(SPVM::Byte->new($BYTE_MAX))->value;
    is($val, $BYTE_MAX);
  }

  # Numeric value to numeric object - number to SPVM::Short
  {
    my $val = TestCase::ExchangeAPI->return_short_object_only(SPVM::Short->new($SHORT_MAX))->value;
    is($val, $SHORT_MAX);
  }

  # Numeric value to numeric object - number to SPVM::Int
  {
    my $val = TestCase::ExchangeAPI->return_int_object_only(SPVM::Int->new($INT_MAX))->value;
    is($val, $INT_MAX);
  }

  # Numeric value to numeric object - number to SPVM::Long
  {
    my $val = TestCase::ExchangeAPI->return_long_object_only(SPVM::Long->new($LONG_MAX))->value;
    is($val, $LONG_MAX);
  }

  # Numeric value to numeric object - number to SPVM::Float
  {
    my $val = TestCase::ExchangeAPI->return_float_object_only(SPVM::Float->new($FLT_MAX))->value;
    is($val, $FLT_MAX);
  }

  # Numeric value to numeric object - number to SPVM::Double
  {
    my $val = TestCase::ExchangeAPI->return_double_object_only(SPVM::Double->new($DBL_MAX))->value;
    is($val, $DBL_MAX);
  }
}

# Any object array
{
  {
    my $bytes = SPVM::new_object_array("SPVM::Byte[]", [SPVM::Byte->new(1), SPVM::Byte->new(2), SPVM::Byte->new(3)]);
    my $ret = TestCase::ExchangeAPI->any_object_array($bytes);
    
    isa_ok($ret, 'SPVM::BlessedObject::Array');
    is_deeply([$ret->to_elems->[0]->value, $ret->to_elems->[1]->value, $ret->to_elems->[2]->value], [1, 2, 5]);
  }
}

# SPVM::Hash
{
  {
    # SPVM::Hash
    my $opt = SPVM::Hash->new([]);
    $opt->set_int(count => 5);
    my $count = $opt->get_int("count");
    
    is($count, 5);
  }

  # Empty Hash new
  {
    {
      my $hash = SPVM::Hash->new([]);
      is_deeply($hash->count, 0);
    }
  }

  # Pass hash
  {
    my $hash = SPVM::Hash->new([]);
    $hash->set_int(x => 1);
    $hash->set_double(y => 2.5);
    is($hash->get("x")->value, 1);
    is($hash->get("y")->value, 2.5);
  }
}

# Empty List push
{
  {
    my $list = SPVM::ByteList->new([]);
    $list->push(1);
    is_deeply($list->length, 1);
  }
  {
    my $list = SPVM::ShortList->new([]);
    $list->push(1);
    is_deeply($list->length, 1);
  }
  {
    my $list = SPVM::IntList->new([]);
    $list->push(1);
    is_deeply($list->length, 1);
  }
  {
    my $list = SPVM::LongList->new([]);
    $list->push(1);
    is_deeply($list->length, 1);
  }
  {
    my $list = SPVM::FloatList->new([]);
    $list->push(1);
    is_deeply($list->length, 1);
  }
  {
    my $list = SPVM::DoubleList->new([]);
    $list->push(1);
    is_deeply($list->length, 1);
  }
  {
    my $list = SPVM::List->new([]);
    $list->push(SPVM::Int->new(1));
    is_deeply($list->length, 1);
  }
  {
    my $list = SPVM::StringList->new([]);
    $list->push("abc");
    is_deeply($list->length, 1);
  }
}

# Empty List new
{
  {
    my $list = SPVM::IntList->new([]);
    is_deeply($list->length, 0);
  }
  {
    my $list = SPVM::List->new([]);
    is_deeply($list->length, 0);
  }
}

# SPVM::BlessedObject::Array get and set
{
  {
    my $sp_values = SPVM::new_byte_array([0, 0]);
    $sp_values->set(1, $BYTE_MAX);
    is_deeply($sp_values->to_elems, [0, $BYTE_MAX]);
    my $value = $sp_values->get(1);
    is($value, $BYTE_MAX);
  }
  {
    my $sp_values = SPVM::new_short_array([0, 0]);
    $sp_values->set(1, $SHORT_MAX);
    is_deeply($sp_values->to_elems, [0, $SHORT_MAX]);
    my $value = $sp_values->get(1);
    is($value, $SHORT_MAX);
  }
  {
    my $sp_values = SPVM::new_int_array([0, 0]);
    $sp_values->set(1, $INT_MAX);
    is_deeply($sp_values->to_elems, [0, $INT_MAX]);
    my $value = $sp_values->get(1);
    is($value, $INT_MAX);
  }
  {
    my $sp_values = SPVM::new_long_array([0, 0]);
    $sp_values->set(1, $LONG_MAX);
    is_deeply($sp_values->to_elems, [0, $LONG_MAX]);
    my $value = $sp_values->get(1);
    is($value, $LONG_MAX);
  }
  {
    my $sp_values = SPVM::new_float_array([0, 0]);
    $sp_values->set(1, $FLOAT_PRECICE);
    is_deeply($sp_values->to_elems, [0, $FLOAT_PRECICE]);
    my $value = $sp_values->get(1);
    is($value, $FLOAT_PRECICE);
  }
  {
    my $sp_values = SPVM::new_double_array([0, 0]);
    $sp_values->set(1, $DOUBLE_PRECICE);
    is_deeply($sp_values->to_elems, [0, $DOUBLE_PRECICE]);
    my $value = $sp_values->get(1);
    is($value, $DOUBLE_PRECICE);
  }
}

# Get hash key - any object
{
  my $biases = SPVM::new_float_array([1, 2, 3]);
  my $hash = SPVM::Hash->new([]);
  $hash->set(biases => $biases);
  $hash->set("int" => SPVM::Int->new(4));
  my $get_biases = $hash->get("biases");
  my $get_int = $hash->get("int");
  
  is(ref $get_biases, 'SPVM::BlessedObject::Array');
  is(ref $get_int, 'SPVM::Int');
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

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

