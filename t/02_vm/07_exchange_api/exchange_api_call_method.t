use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use POSIX();
use Encode 'encode';

use Test::More;

my $file = basename $0;

use Encode 'decode', 'encode';

use SPVM 'TestCase'; my $use_test_line = __LINE__;

use SPVM 'TestCase::ExchangeAPI';
use SPVM 'TestCase::Point_3i';
use SPVM 'Point';

use SPVM 'Hash';
use SPVM 'List';
use SPVM 'ByteList';
use SPVM 'ShortList';
use SPVM 'IntList';
use SPVM 'LongList';
use SPVM 'FloatList';
use SPVM 'DoubleList';
use SPVM 'StringList';
use SPVM 'Point3D';
use SPVM 'Byte';
use SPVM 'Short';
use SPVM 'Int';
use SPVM 'Long';
use SPVM 'Float';
use SPVM 'Double';
use SPVM 'Bool';

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

my $api = SPVM::api();

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# call_method
{
  {
    my $obj_int = $api->call_method("Int", "new", 1);
    isa_ok($obj_int, "SPVM::BlessedObject");
    my $value = $obj_int->value;
    is($value, 1);
  }
  
  # Static instance method call
  {
    {
      my $list = SPVM::FloatList->new([]);
      $list->SPVM::FloatList::push(1);
      is_deeply($list->length, 1);
    }
  }

  # Invalid argument type
  {
    {
      my $list = SPVM::IntList->new([]);
      eval { $list->push(undef) };
      ok($@);
    }
    {
      eval { SPVM::IntList->new(1) };
      ok($@);
    }
  }

  # Error id
  {
    {
      my $error = $api->new_error;
      is($error->id, 0);
      my $message = "Error Message";
      eval { SPVM::TestCase::ExchangeAPI->die($message, $error); };
      # Error
      is($error->id, 18);
    }
    {
      my $error = $api->new_error;
      is($error->id, 0);
      my $message = "Error Message";
      eval { SPVM::TestCase::ExchangeAPI->die_with_die_error_id($message, $error); };
      # Error::System
      is($error->id, 19);
    }
  }
  
  # Binding SPVM class to Perl class
  {
    # Calls a non-defined method
    {
      eval { SPVM::Int->not_defined_method };
      like($@, qr|Int#not_defined_method method is not found|);
    }
  }
}

# Argument conversion
{
  # Argument conversion - Exceptions
  {
    # Argument conversiongeneral exception - too few arguments
    {
      eval {
        SPVM::Int->new;
      };
      like($@, qr/Too few arguments are passed to Int#new method/);
    }
    
    # Argument conversiongeneral exception - too many arguments. This is OK.
    {
      SPVM::Int->new(1, 2);
    }
  }

  # Argument conversion - Numeric type
  {
    # Argument conversion - byte
    {
      {
        my $total = SPVM::TestCase->sum_byte(8, 3);
        is($total, 11);
      }
      {
        my $total = SPVM::TestCase->sum_byte("8", "3");
        is($total, 11);
      }
      {
        my $total = SPVM::TestCase->sum_byte("8ab", "3");
        is($total, 11);
      }
    }

    # Argument conversion - short
    {
      {
        my $total = SPVM::TestCase->sum_short(8, 3);
        is($total, 11);
      }
      {
        my $total = SPVM::TestCase->sum_short("8", "3");
        is($total, 11);
      }
    }
    
    # Argument conversion - int
    {
      {
        my $total = SPVM::TestCase->sum_int(8, 3);
        is($total, 11);
      }
      {
        my $total = SPVM::TestCase->sum_int("8", "3");
        is($total, 11);
      }
    }
    
    # Argument conversion - long
    {
      {
        my $total = SPVM::TestCase->sum_long(8, 3);
        is($total, 11);
      }
      {
        my $total = SPVM::TestCase->sum_long("8", "3");
        is($total, 11);
      }
      {
        my $total = SPVM::TestCase->sum_long(9223372036854775806, 1);
        is($total, 9223372036854775807);
      }
    }

    # Argument conversion - float
    {
      {
        my $total = SPVM::TestCase->sum_float(0.25, 0.25);
        cmp_ok($total, '==', 0.5);
      }
      {
        my $total = SPVM::TestCase->sum_float("0.25", "0.25");
        cmp_ok($total, '==', 0.5);
      }
    }
    
    # Argument conversion - double
    {
      {
        my $total = SPVM::TestCase->sum_double(0.25, 0.25);
        cmp_ok($total, '==', 0.5);
      }
      {
        my $total = SPVM::TestCase->sum_double("0.25", "0.25");
        cmp_ok($total, '==', 0.5);
      }
    }
  }

  # Argument conversion - string
  {
    # Argument conversion - string
    {
      # Argument conversion - string - ascii
      {
        my $ok = SPVM::TestCase::ExchangeAPI->argument_non_ref_scalar_to_string_ascii("ABC");
        ok($ok);
      }

      # Argument conversion - string - UTF-8
      {
        my $ok = SPVM::TestCase::ExchangeAPI->argument_non_ref_scalar_to_string_decoded_string("あいう");
        ok($ok);
      }

      # Argument conversion - string - numeric
      {
        my $ok = SPVM::TestCase::ExchangeAPI->argument_non_ref_scalar_to_string_number(4.12);
        ok($ok);
      }

      # Argument conversion - string - undef
      {
        my $ok = SPVM::TestCase::ExchangeAPI->argument_non_ref_scalar_to_string_undef(undef);
        ok($ok);
      }
    }
    
    # Argument conversion - string
    {
      # Argument conversion - string
      {
        my $ok = SPVM::TestCase::ExchangeAPI->argument_blessed_object_string_to_string($api->new_string("あいう"));
        ok($ok);
      }

      # Argument conversion - undef
      {
        my $ok = SPVM::TestCase::ExchangeAPI->argument_blessed_object_string_to_string_undef(undef);
        ok($ok);
      }
      
      # Argument conversion - exception invalid type
      {
        eval { SPVM::TestCase::ExchangeAPI->argument_non_ref_scalar_to_string_ascii({}) };
        ok($@);
      }
    }
  }

  # Argument conversion - numeric reference
  {
    {
      # Argument conversion - byte reference
      {
        my $num_byte = $BYTE_MIN;
        SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_byte(\$num_byte);
        is($num_byte, $BYTE_MIN + 1);
      }
      {
        my $num_byte = "" . $BYTE_MIN;
        SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_byte(\$num_byte);
        is($num_byte, $BYTE_MIN + 1);
      }
      {
        my $num_byte = "" . $BYTE_MIN . "ab";
        SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_byte(\$num_byte);
        is($num_byte, $BYTE_MIN + 1);
      }
      # Argument conversion - short reference
      {
        my $num_short = $SHORT_MIN;
        SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_short(\$num_short);
        is($num_short, $SHORT_MIN + 1);
      }
      {
        my $num_short = "" . $SHORT_MIN;
        SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_short(\$num_short);
        is($num_short, $SHORT_MIN + 1);
      }
      # Argument conversion - int reference
      {
        my $num_int = $INT_MIN;
        SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_int(\$num_int);
        is($num_int, $INT_MIN + 1);
      }
      {
        my $num_int = "" . $INT_MIN;
        SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_int(\$num_int);
        is($num_int, $INT_MIN + 1);
      }
      # Argument conversion - long reference
      {
        my $num_long = $LONG_MIN;
        SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_long(\$num_long);
        is($num_long, $LONG_MIN + 1);
      }
      {
        my $num_long = "" . $LONG_MIN;
        SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_long(\$num_long);
        is($num_long, $LONG_MIN + 1);
      }
      # Argument conversion - float reference
      {
        my $num_float = POSIX::FLT_MIN();
        SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_float(\$num_float);
        is($num_float, POSIX::FLT_MIN() + 1);
      }
      {
        my $num_float = "" . POSIX::FLT_MIN();
        SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_float(\$num_float);
        is($num_float, POSIX::FLT_MIN() + 1);
      }
      # Argument conversion - double reference
      {
        my $num_double = POSIX::DBL_MIN();
        SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_double(\$num_double);
        is($num_double, POSIX::DBL_MIN() + 1);
      }
      {
        my $num_double = "" . POSIX::DBL_MIN();
        SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_double(\$num_double);
        is($num_double, POSIX::DBL_MIN() + 1);
      }
    }

    # Argument conversion - numeric reference exception
    {
      # Argument conversion - byte reference exception
      {
        my $num_byte = $BYTE_MIN;
        eval { SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_byte($num_byte) };
        ok($@);

        eval { SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_byte({}) };
        ok($@);
      }
      # Argument conversion - short reference exception
      {
        my $num_short = $SHORT_MIN;
        eval { SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_short($num_short) };
        ok($@);

        eval { SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_short({}) };
        ok($@);
      }
      # Argument conversion - int reference exception
      {
        my $num_int = $INT_MIN;
        eval { SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_int($num_int) };
        ok($@);

        eval { SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_int({}) };
        ok($@);
      }
      # Argument conversion - long reference exception
      {
        my $num_long = $LONG_MIN;
        eval { SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_long($num_long) };
        ok($@);

        eval { SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_long({}) };
        ok($@);
      }
      # Argument conversion - float reference exception
      {
        my $num_float = POSIX::FLT_MIN();
        eval { SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_float($num_float) };
        ok($@);

        eval { SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_float({}) };
        ok($@);
      }
      # Argument conversion - double reference exception
      {
        my $num_double = POSIX::DBL_MIN();
        eval { SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_double($num_double) };
        ok($@);

        eval { SPVM::TestCase::ExchangeAPI->call_method_numeric_ref_arg_double({}) };
        ok($@);
      }
    }
  }

  # Argument conversion - any object
  {
    # Argument conversion - any object - array
    {
      my $spvm_array = $api->new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
      my $spvm_array_ret = SPVM::TestCase::ExchangeAPI->return_any_object_only($spvm_array);
      ok(ref $spvm_array_ret, "SPVM::BlessedObject::Array");
      is($spvm_array_ret->__get_type_name, "byte[]");
      is_deeply($spvm_array_ret->to_elems, [1, $BYTE_MAX, $BYTE_MIN]);
    }
    
    # Argument conversion - any object - string
    {
      {
        my $spvm_string = $api->new_string("abc");
        my $spvm_string_ret = SPVM::TestCase::ExchangeAPI->return_any_object_only($spvm_string);
        ok(ref $spvm_string_ret, "SPVM::BlessedObject::String");
        is($spvm_string_ret->__get_type_name, "string");
        is("$spvm_string", "$spvm_string_ret");
      }
      
      {
        my $string = "abc";
        my $spvm_string_ret = SPVM::TestCase::ExchangeAPI->return_any_object_only($string);
        ok(ref $spvm_string_ret, "SPVM::BlessedObject::String");
        is($spvm_string_ret->__get_type_name, "string");
        is($string, "$spvm_string_ret");
      }
    }

    # Argument conversion - any object - class
    {
      my $spvm_object = SPVM::Point->new(1, 2);
      my $spvm_object_ret = SPVM::TestCase::ExchangeAPI->return_any_object_only($spvm_object);
      ok(ref $spvm_object_ret, "SPVM::BlessedObject::Class");
      is($spvm_object_ret->__get_type_name, "Point");
      is($spvm_object->x, $spvm_object_ret->x);
      is($spvm_object->y, $spvm_object_ret->y);
    }
    
    # Exceptions
    {
      my $spvm_value = 1;
      eval { SPVM::TestCase::ExchangeAPI->return_any_object_only($spvm_value) };
      like($@, qr|The 1th argument of TestCase::ExchangeAPI#return_any_object_only method must be an SPVM::BlessedObject object or a string or undef|);
    }
  }
  
  # Argument conversion - numeric array
  {
    # Argument conversion - byte array
    {
      my $spvm_array = $api->new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
      my $ok = SPVM::TestCase::ExchangeAPI->argument_spvm_array_to_spvm_byte_array($spvm_array, undef);
      ok($ok);
    }
    # Argument conversion - short array
    {
      my $spvm_array = $api->new_short_array([1, $SHORT_MAX, $SHORT_MIN]);
      my $ok = SPVM::TestCase::ExchangeAPI->argument_spvm_array_to_spvm_short_array($spvm_array, undef);
      ok($ok);
    }
    # Argument conversion - int array
    {
      my $spvm_array = $api->new_int_array([1, $INT_MAX, $INT_MIN]);
      my $ok = SPVM::TestCase::ExchangeAPI->argument_spvm_array_to_spvm_int_array($spvm_array, undef);
      ok($ok);
    }
    # Argument conversion - long array
    {
      my $spvm_array = $api->new_long_array([1, $LONG_MAX, $LONG_MIN]);
      my $ok = SPVM::TestCase::ExchangeAPI->argument_spvm_array_to_spvm_long_array($spvm_array, undef);
      ok($ok);
    }
    # Argument conversion - float array
    {
      my $spvm_array = $api->new_float_array([0.5, $FLT_MAX, $FLT_MIN]);
      my $ok = SPVM::TestCase::ExchangeAPI->argument_spvm_array_to_spvm_float_array($spvm_array, undef);
      ok($ok);
    }
    # Argument conversion - double array
    {
      my $spvm_array = $api->new_double_array([0.5, $DBL_MAX, $DBL_MIN]);
      my $ok = SPVM::TestCase::ExchangeAPI->argument_spvm_array_to_spvm_double_array($spvm_array, undef);
      ok($ok);
    }
    # Argument conversion - string array
    {
      my $spvm_string_array = $api->new_string_array(["あいう", "えお", "ab", undef]);
      my $ok = SPVM::TestCase::ExchangeAPI->argument_spvm_string_array_to_spvm_string_array($spvm_string_array, undef);
      ok($ok);
    }
    
    # Argument conversion - numeric array - Extra
    {
      # Argument conversion - byte array
      {
        my $perl_array_ref = [1, $BYTE_MAX, $BYTE_MIN];
        my $ok = SPVM::TestCase::ExchangeAPI->argument_perl_array_ref_to_spvm_byte_array($perl_array_ref, undef);
        ok($ok);
      }
      # Argument conversion - short array
      {
        my $perl_array_ref = [1, $SHORT_MAX, $SHORT_MIN];
        my $ok = SPVM::TestCase::ExchangeAPI->argument_perl_array_ref_to_spvm_short_array($perl_array_ref, undef);
        ok($ok);
      }
      # Argument conversion - int array
      {
        my $perl_array_ref = [1, $INT_MAX, $INT_MIN];
        my $ok = SPVM::TestCase::ExchangeAPI->argument_perl_array_ref_to_spvm_int_array($perl_array_ref, undef);
        ok($ok);
      }
      # Argument conversion - long array
      {
        my $perl_array_ref = [1, $LONG_MAX, $LONG_MIN];
        my $ok = SPVM::TestCase::ExchangeAPI->argument_perl_array_ref_to_spvm_long_array($perl_array_ref, undef);
        ok($ok);
      }
      # Argument conversion - float array
      {
        my $perl_array_ref = [0.5, $FLT_MAX, $FLT_MIN];
        my $ok = SPVM::TestCase::ExchangeAPI->argument_perl_array_ref_to_spvm_float_array($perl_array_ref, undef);
        ok($ok);
      }
      # Argument conversion - double array
      {
        my $perl_array_ref = [0.5, $DBL_MAX, $DBL_MIN];
        my $ok = SPVM::TestCase::ExchangeAPI->argument_perl_array_ref_to_spvm_double_array($perl_array_ref, undef);
        ok($ok);
      }

      # Argument conversion - string array
      {
        my $perl_array_ref = ["あいう", "えお", "ab", undef];
        my $ok = SPVM::TestCase::ExchangeAPI->argument_perl_array_ref_to_spvm_string_array($perl_array_ref, undef);
        ok($ok);
      }
    }
  }

  # Argument conversion - multi numeric array
  {
    
    # Argument conversion - multi numeric array - byte
    {
      my $values = [
        {x => $BYTE_MIN, y => 1, z => 2},
        {x => 3, y => 4, z => 5},
        {x => 6, y => 7, z => 8},
      ];
      my $spvm_values = $api->new_mulnum_array("TestCase::Point_3b[]", $values);
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_byte($values));
      my $out_values = $spvm_values->to_elems;
      is_deeply($out_values, $values);
    }

    # Argument conversion - multi numeric array - short
    {
      my $values = [
        {x => $SHORT_MIN, y => 1, z => 2},
        {x => 3, y => 4, z => 5},
        {x => 6, y => 7, z => 8},
      ];
      my $spvm_values = $api->new_mulnum_array("TestCase::Point_3s[]", $values);
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_short($values));
      my $out_values = $spvm_values->to_elems;
      is_deeply($out_values, $values);
    }

    # Argument conversion - multi numeric array - int
    {
      my $values = [
        {x => $INT_MIN, y => 1, z => 2},
        {x => 3, y => 4, z => 5},
        {x => 6, y => 7, z => 8},
      ];
      my $spvm_values = $api->new_mulnum_array("TestCase::Point_3i[]", $values);
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_int($values));
      my $out_values = $spvm_values->to_elems;
      is_deeply($out_values, $values);
    }

    # Argument conversion - multi numeric array - long
    {
      my $values = [
        {x => $LONG_MIN, y => 1, z => 2},
        {x => 3, y => 4, z => 5},
        {x => 6, y => 7, z => 8},
      ];
      my $spvm_values = $api->new_mulnum_array("TestCase::Point_3l[]", $values);
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_long($values));
      my $out_values = $spvm_values->to_elems;
      is_deeply($out_values, $values);
    }

    # Argument conversion - multi numeric array - float
    {
      my $values = [
        {x => $FLT_MIN, y => 1, z => 2},
        {x => 3, y => 4, z => 5},
        {x => 6, y => 7, z => 8},
      ];
      my $spvm_values = $api->new_mulnum_array("TestCase::Point_3f[]", $values);
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_float($values));
      my $out_values = $spvm_values->to_elems;
      is_deeply($out_values, $values);
    }

    # Argument conversion - multi numeric array - double
    {
      my $values = [
        {x => $DBL_MIN, y => 1, z => 2},
        {x => 3, y => 4, z => 5},
        {x => 6, y => 7, z => 8},
      ];
      my $spvm_values = $api->new_mulnum_array("TestCase::Point_3d[]", $values);
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_double($values));
      my $out_values = $spvm_values->to_elems;
      is_deeply($out_values, $values);
    }

    # Argument conversion - multi numeric type - Exceptions
    {
      {
        # Argument conversion - multi-numeric byte
        {
          my $input = {x => 1, y => 3, z => $BYTE_MAX};
          my $output = SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_arg_byte($input);
          is_deeply($output, $input);
        }

        # Argument conversion - multi-numeric short
        {
          my $input = {x => 1, y => 3, z => $SHORT_MAX};
          my $output = SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_arg_short($input);
          is_deeply($output, $input);
        }

        # Argument conversion - multi-numeric int
        {
          my $input = {x => 1, y => 3, z => $INT_MAX};
          my $output = SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_arg_int($input);
          is_deeply($output, $input);
        }

        # Argument conversion - multi-numeric long
        {
          my $input = {x => 1, y => 3, z => $LONG_MAX};
          my $output = SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_arg_long($input);
          is_deeply($output, $input);
        }

        # Argument conversion - multi-numeric float
        {
          my $input = {x => 1, y => 3, z => $FLT_MAX};
          my $output = SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_arg_float($input);
          is_deeply($output, $input);
        }

        # Argument conversion - multi-numeric double
        {
          my $input = {x => 1, y => 3, z => $DBL_MAX};
          my $output = SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_arg_double($input);
          is_deeply($output, $input);
        }
      }

      # Argument conversion - multi numeric exception
      {
        # Argument conversion - multi numeric exception - byte, field not found
        {
          my $input = {x => 1, y => 3};
          eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_arg_byte($input) };
          ok($@);
        }

        # Argument conversion - multi-numeric short, field not found
        {
          my $input = {x => 1, y => 3};
          eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_arg_short($input) };
          ok($@);
        }

        # Argument conversion - multi-numeric int, field not found
        {
          my $input = {x => 1, y => 3};
          eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_arg_int($input) };
          ok($@);
        }

        # Argument conversion - multi-numeric long, field not found
        {
          my $input = {x => 1, y => 3};
          eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_arg_long($input) };
          ok($@);
        }

        # Argument conversion - multi-numeric float, field not found
        {
          my $input = {x => 1, y => 3};
          eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_arg_float($input) };
          ok($@);
        }

        # Argument conversion - multi-numeric double, field not found
        {
          my $input = {x => 1, y => 3};
          eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_arg_double($input) };
          ok($@);
        }

        # Argument conversion - multi numeric exception - byte, not hash reference
        {
          my $input = 1;
          eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_arg_byte($input) };
          ok($@);
        }

        # Argument conversion - multi-numeric short, not hash reference
        {
          my $input = 1;
          eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_arg_short($input) };
          ok($@);
        }

        # Argument conversion - multi-numeric int, not hash reference
        {
          my $input = 1;
          eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_arg_int($input) };
          ok($@);
        }

        # Argument conversion - multi-numeric long, not hash reference
        {
          my $input = 1;
          eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_arg_long($input) };
          ok($@);
        }

        # Argument conversion - multi-numeric float, not hash reference
        {
          my $input = 1;
          eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_arg_float($input) };
          ok($@);
        }

        # Argument conversion - multi-numeric double, not hash reference
        {
          my $input = 1;
          eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_arg_double($input) };
          ok($@);
        }
      }
    }
  }

  # Argument conversion - multi numeric reference
  {
    {
      # Argument conversion - multi numeric reference - byte
      {
        my $point = {x => $BYTE_MIN, y => 1, z => 2};
        SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_ref_arg_byte(\$point);
        is_deeply($point, {x => $BYTE_MIN + 1, y => 2, z => 3});
      }
      # Argument conversion - multi numeric reference - short
      {
        my $point = {x => $SHORT_MIN, y => 1, z => 2};
        SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_ref_arg_short(\$point);
        is_deeply($point, {x => $SHORT_MIN + 1, y => 2, z => 3});
      }
      # Argument conversion - multi numeric reference - int
      {
        my $point = {x => $INT_MIN, y => 1, z => 2};
        SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_ref_arg_int(\$point);
        is_deeply($point, {x => $INT_MIN + 1, y => 2, z => 3});
      }
      # Argument conversion - multi numeric reference - long
      {
        my $point = {x => $LONG_MIN, y => 1, z => 2};
        SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_ref_arg_long(\$point);
        is_deeply($point, {x => $LONG_MIN + 1, y => 2, z => 3});
      }
      # Argument conversion - multi numeric reference - float
      {
        my $point = {x => $FLT_MIN, y => 1, z => 2};
        SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_ref_arg_float(\$point);
        is_deeply($point, {x => $FLT_MIN + 1, y => 2, z => 3});
      }
      # Argument conversion - multi numeric reference - double
      {
        my $point = {x => $DBL_MIN, y => 1, z => 2};
        SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_ref_arg_double(\$point);
        is_deeply($point, {x => $DBL_MIN + 1, y => 2, z => 3});
      }
    }
    
    # Argument conversion - multi numeric reference exception
    {
      # Argument conversion - multi numeric reference exception - byte, key not found
      {
        my $point = {x => $BYTE_MIN, y => 1};
        eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_ref_arg_byte(\$point) };
        ok($@);
      }
      # Argument conversion - multi numeric reference exception - short, key not found
      {
        my $point = {x => $SHORT_MIN, y => 1};
        eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_ref_arg_short(\$point) };
        ok($@);
      }
      # Argument conversion - multi numeric reference exception - int, key not found
      {
        my $point = {x => $INT_MIN, y => 1};
        eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_ref_arg_int(\$point) };
        ok($@);
      }
      # Argument conversion - multi numeric reference exception - long, key not found
      {
        my $point = {x => $LONG_MIN, y => 1};
        eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_ref_arg_long(\$point) };
        ok($@);
      }
      # Argument conversion - multi numeric reference exception - float, key not found
      {
        my $point = {x => $FLT_MIN, y => 1};
        eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_ref_arg_float(\$point) };
        ok($@);
      }
      # Argument conversion - multi numeric reference exception - double, key not found
      {
        my $point = {x => $DBL_MIN, y => 1};
        eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_ref_arg_double(\$point) };
        ok($@);
      }

      # Argument conversion - multi numeric reference exception - byte, not reference of hash reference
      {
        my $point = {x => $BYTE_MIN, y => 1, z => 2};
        eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_ref_arg_byte($point) };
        ok($@);
      }
      # Argument conversion - multi numeric reference exception - short, not reference of hash reference
      {
        my $point = {x => $SHORT_MIN, y => 1, z => 2};
        eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_ref_arg_short($point) };
        ok($@);
      }
      # Argument conversion - multi numeric reference exception - int, not reference of hash reference
      {
        my $point = {x => $INT_MIN, y => 1, z => 2};
        eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_ref_arg_int($point) };
        ok($@);
      }
      # Argument conversion - multi numeric reference exception - long, not reference of hash reference
      {
        my $point = {x => $LONG_MIN, y => 1, z => 2};
        eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_ref_arg_long($point) };
        ok($@);
      }
      # Argument conversion - multi numeric reference exception - float, not reference of hash reference
      {
        my $point = {x => $FLT_MIN, y => 1, z => 2};
        eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_ref_arg_float($point) };
        ok($@);
      }
      # Argument conversion - multi numeric reference exception - double, not reference of hash reference
      {
        my $point = {x => $DBL_MIN, y => 1, z => 2};
        eval { SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_ref_arg_double($point) };
        ok($@);
      }

    }

    # Argument conversion - multi numeric reference and numeric reference mixed
    {
      {
        my $point1 = {x => $BYTE_MIN, y => 1, z => 2};
        my $value1 = 6;
        my $point2 = {x => 3, y => 4, z => 5};
        my $value2 = 7;
        SPVM::TestCase::ExchangeAPI->call_method_multi_numeric_ref_numeric_ref_mixed_arg(\$point1, \$value1, \$point2, \$value2);
        is_deeply($point1, {x => $BYTE_MIN + 1, y => 2, z => 3});
        is($value1, 7);
        is_deeply($point2, {x => 4, y => 5, z => 6});
        is($value2, 8);
      }
    }
  }
  
  # Argument conversion - Extra
  {
    # Argument conversion - Empty List push
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
        my $list = SPVM::StringList->new([]);
        $list->push("abc");
        is_deeply($list->length, 1);
      }
      {
        my $list = SPVM::List->new($api->new_object_array("Int[]", []));
        $list->push(SPVM::Int->new(1));
        is_deeply($list->length, 1);
      }
    }

    # Argument conversion - Empty List new
    {
      {
        my $list = SPVM::IntList->new([]);
        is_deeply($list->length, 0);
      }
      {
        my $list = SPVM::List->new($api->new_object_array("Int[]", []));
        is_deeply($list->length, 0);
      }
    }

    # Argument conversion - Pass list
    {
      # Pass list
      {
        my $list = SPVM::List->new($api->new_object_array("Int[]", [SPVM::Int->new(1), SPVM::Int->new(5), undef]));
        my $x = $list->get(0);
        
        is($list->get(0)->value, 1);
        is($list->get(1)->value, 5);
        ok(!defined $list->get(2));
      }
    }

    # Argument conversion - Pass list
    {
      SPVM::List->new($api->new_object_array("object[]", []));
      ok(1);
    }
    
    # Argument conversion - object[] array of any object
    {
      my $args = $api->new_object_array('object[]', [SPVM::Int->new(1), SPVM::Double->new(3)]);
      ok(SPVM::TestCase::ExchangeAPI->arg_array_of_any_object($args));
    }
  }
}

# Return value conversion - value conversion
{
  # Return value conversion - void
  {
    # Return value conversion - void
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_void;
      ok(!defined $value);
    }
  }

  # Return value conversion - numeric
  {
    # Return value conversion - numeric - byte
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_byte;
      is($value, $BYTE_MIN);
    }
    
    # Return value conversion - numeric - short
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_short;
      is($value, $SHORT_MIN);
    }
    
    # Return value conversion - numeric - int
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_int;
      is($value, $INT_MIN);
    }
    
    # Return value conversion - numeric - long
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_long;
      is($value, $LONG_MIN);
    }
    
    # Return value conversion - numeric - float
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_float;
      is($value, $FLT_MIN);
    }
    
    # Return value conversion - numeric - double
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_double;
      is($value, $DBL_MIN);
    }
  }

  # Return value conversion - string
  {
    # Return value conversion - string
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_string;
      is(ref $value, 'SPVM::BlessedObject::String');
      ok($value eq "あいう");
    }

    # Return value conversion - string undef
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_string_undef;
      ok(!defined $value);
    }

    # Return value conversion - string empty
    {
      my $values = SPVM::TestCase->string_empty();
      is($values, "");
    }
  }

  # Return value conversion - object
  {
    # Return value conversion - object
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_object;
      is($value->get_basic_type_name, 'TestCase::Minimal');
      isa_ok($value, 'SPVM::BlessedObject::Class');
      is($value->x, 1);
      is($value->y, 2);
    }

    # Return value conversion - object undef
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_object_undef;
      ok(!defined $value);
    }
  }

  # Return value conversion - any object
  {
    # Return value conversion - any object - class
    {
      my $spvm_object = SPVM::Point->new(1, 2);
      my $spvm_object_ret = SPVM::TestCase::ExchangeAPI->return_any_object_only($spvm_object);
      ok(ref $spvm_object_ret, "SPVM::BlessedObject::Class");
      is($spvm_object_ret->__get_type_name, "Point");
      is($spvm_object->x, $spvm_object_ret->x);
      is($spvm_object->y, $spvm_object_ret->y);
    }

    # Return value conversion - any object - array
    {
      my $spvm_array = $api->new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
      my $spvm_array_ret = SPVM::TestCase::ExchangeAPI->return_any_object_only($spvm_array);
      ok(ref $spvm_array_ret, "SPVM::BlessedObject::Array");
      is($spvm_array_ret->__get_type_name, "byte[]");
      is_deeply($spvm_array_ret->to_elems, [1, $BYTE_MAX, $BYTE_MIN]);
    }
    
    # Return value conversion - any object - string
    {
      my $spvm_string = $api->new_string("abc");
      my $spvm_string_ret = SPVM::TestCase::ExchangeAPI->return_any_object_only($spvm_string);
      ok(ref $spvm_string_ret, "SPVM::BlessedObject::String");
      is($spvm_string_ret->__get_type_name, "string");
      is("$spvm_string", "$spvm_string_ret");
    }

    # Return value conversion - any object undef
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_any_object_undef;
      ok(!defined $value);
    }
    
    # Extra
    {
      # Return value conversion - any object - class
      {
        my $value = SPVM::TestCase::ExchangeAPI->return_any_object;
        is($value->get_basic_type_name, 'TestCase::Minimal');
        isa_ok($value, 'SPVM::BlessedObject::Class');
        is($value->x, 1);
        is($value->y, 2);
      }
    }
  }

  # Return value conversion - multi numeric
  {
    # Return value conversion - multi numeric - byte
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_byte_multi_numeric;
      is_deeply($value, {x => 1, y => 2, z => $BYTE_MIN});
    }
    
    # Return value conversion - multi numeric - short
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_short_multi_numeric;
      is_deeply($value, {x => 1, y => 2, z => $SHORT_MIN});
    }
    
    # Return value conversion - multi numeric - int
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_int_multi_numeric;
      is_deeply($value, {x => 1, y => 2, z => $INT_MIN});
    }
    
    # Return value conversion - multi numeric - long
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_long_multi_numeric;
      is_deeply($value, {x => 1, y => 2, z => $LONG_MIN});
    }
    
    # Return value conversion - multi numeric - float
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_float_multi_numeric;
      is_deeply($value, {x => 1, y => 2, z => $FLT_MIN});
    }
    
    # Return value conversion - multi numeric - double
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_double_multi_numeric;
      is_deeply($value, {x => 1, y => 2, z => $DBL_MIN});
    }
  }

  # Return value conversion - array
  {
    # Return value conversion - numeric array
    {
      {
        my $blessed_array = SPVM::TestCase::ExchangeAPI->return_numeric_array;
        my $values = $blessed_array->to_elems;
        is_deeply($values, [1, 2, 3]);
      }

      # Return value conversion - array undef
      {
        my $blessed_array = SPVM::TestCase::ExchangeAPI->return_numeric_array_undef;
        ok(!defined $blessed_array);
      }
    }
      
    # Return value conversion - object array
    {
      # Return value conversion - object array
      {
        {
          my $blessed_array = SPVM::TestCase::ExchangeAPI->return_object_array;
          my $values = $blessed_array->to_elems;
          is($values->[0]->x, 1);
          is($values->[0]->y, 2);
          is($values->[1]->x, 3);
          is($values->[1]->y, 4);
        }

        # Return value conversion - array undef
        {
          my $blessed_array = SPVM::TestCase::ExchangeAPI->return_object_array_undef;
          ok(!defined $blessed_array);
        }
      }

      # Return value conversion - any object array
      {
        {
          my $blessed_array = SPVM::TestCase::ExchangeAPI->return_any_object_array;
          my $values = $blessed_array->to_elems;
          is($values->[0]->x, 1);
          is($values->[0]->y, 2);
          is($values->[1]->x, 3);
          is($values->[1]->y, 4);
        }

        # Return value conversion - array undef
        {
          my $blessed_array = SPVM::TestCase::ExchangeAPI->return_any_object_array_undef;
          ok(!defined $blessed_array);
        }
        
        # Return value conversion - any object array
        {
          my $values = SPVM::TestCase::ExchangeAPI->return_any_object_array->to_elems;
          is($values->[0]->x, 1);
          is($values->[0]->y, 2);
          is($values->[1]->x, 3);
          is($values->[1]->y, 4);
        }
      }

      # Return value conversion - mutil numeric array
      {
        {
          my $blessed_array = SPVM::TestCase::ExchangeAPI->return_multi_numeric_array;
          my $values = $blessed_array->to_elems;
          is_deeply($values, [{x => 1, y => 0, z => 0}, {x => 0, y => 0, z => 5}]);
        }

        # Return value conversion - array undef
        {
          my $blessed_array = SPVM::TestCase::ExchangeAPI->return_multi_numeric_array_undef;
          ok(!defined $blessed_array);
        }
      }

      # Return value conversion - mutil dimensional array
      {
        my $spvm_array = $api->new_muldim_array_len("byte[][]", 3);
        my $spvm_array_ret = SPVM::TestCase::ExchangeAPI->return_muldim_array_only($spvm_array);
        is(ref $spvm_array_ret, "SPVM::BlessedObject::Array");
        is($spvm_array_ret->__get_type_name, "byte[][]");
        is($spvm_array_ret->length, 3);
      }
    }
  }
}

# Extra
{
  # Pass 8-bit characters
  {
    my $chars_8bit = "\xff\xfe";
    my $string = SPVM::TestCase::ExchangeAPI->pass_and_return_string($chars_8bit);
    my $bytes = $string->to_bin;
    is($chars_8bit, $bytes);
  }
  
  # Optional argument
  {
    my $value = SPVM::TestCase::ExchangeAPI->optional_args_int(3);
    is($value, 8);
  }
  
  # Numeric type exception
  {
    is(SPVM::Byte->new(5)->value, 5);
    is(SPVM::Short->new(5)->value, 5);
    is(SPVM::Int->new(5)->value, 5);
    is(SPVM::Long->new(5)->value, 5);
    is(SPVM::Float->new(5)->value, 5);
    is(SPVM::Double->new(5)->value, 5);

    is(SPVM::Byte->new(1.5)->value, 1);
    is(SPVM::Short->new(1.5)->value, 1);
    is(SPVM::Int->new(1.5)->value, 1);
    is(SPVM::Long->new(1.5)->value, 1);
    is(SPVM::Float->new(1.5)->value, 1.5);
    is(SPVM::Double->new(1.5)->value, 1.5);

    eval { SPVM::Byte->new(undef) };
    ok($@);
    eval { SPVM::Short->new(undef) };
    ok($@);
    eval { SPVM::Int->new(undef) };
    ok($@);
    eval { SPVM::Long->new(undef) };
    ok($@);
    eval { SPVM::Float->new(undef) };
    ok($@);
    eval { SPVM::Double->new(undef) };
    ok($@);
    
    my $bool = SPVM::Bool->TRUE;
    
    eval { SPVM::Byte->new($bool) };
    ok($@);
    eval { SPVM::Short->new($bool) };
    ok($@);
    eval { SPVM::Int->new($bool) };
    ok($@);
    eval { SPVM::Long->new($bool) };
    ok($@);
    eval { SPVM::Float->new($bool) };
    ok($@);
    eval { SPVM::Double->new($bool) };
    ok($@);

    my $ref = {};
    
    eval { SPVM::Byte->new($ref) };
    ok($@);
    eval { SPVM::Short->new($ref) };
    ok($@);
    eval { SPVM::Int->new($ref) };
    ok($@);
    eval { SPVM::Long->new($ref) };
    ok($@);
    eval { SPVM::Float->new($ref) };
    ok($@);
    eval { SPVM::Double->new($ref) };
    ok($@);
  }

  # Inheritance
  {
    my $point = SPVM::Point3D->new(1, 2);
    
    is($point->x, 1);
    is($point->y, 2);
  }
  
  # Any object array
  {
    {
      my $bytes = $api->new_object_array("Byte[]", [SPVM::Byte->new(1), SPVM::Byte->new(2), SPVM::Byte->new(3)]);
      my $ret = SPVM::TestCase::ExchangeAPI->any_object_array($bytes);
      
      isa_ok($ret, 'SPVM::BlessedObject::Array');
      is_deeply([$ret->to_elems->[0]->value, $ret->to_elems->[1]->value, $ret->to_elems->[2]->value], [1, 2, 5]);
    }
  }

  # SPVM::Hash
  {
    {
      # SPVM::Hash
      my $opt = SPVM::Hash->new($api->new_object_array("object[]", []));
      $opt->set(count => SPVM::Int->new(5));
      my $count = $opt->get("count")->value;
      
      is($count, 5);
    }

    # Empty Hash new
    {
      {
        my $hash = SPVM::Hash->new($api->new_object_array("object[]", []));
        is_deeply($hash->keys_length, 0);
      }
    }

    # Pass hash
    {
      my $hash = SPVM::Hash->new($api->new_object_array("object[]", []));
      $hash->set(x => SPVM::Int->new(1));
      $hash->set(y => SPVM::Double->new(2.5));
      is($hash->get("x")->value, 1);
      is($hash->get("y")->value, 2.5);
    }
  }

  # Get hash key - any object
  {
    my $biases = $api->new_float_array([1, 2, 3]);
    my $hash = SPVM::Hash->new($api->new_object_array("object[]", []));
    $hash->set(biases => $biases);
    $hash->set("int" => SPVM::Int->new(4));
    my $get_biases = $hash->get("biases");
    my $get_int = $hash->get("int");
    
    is(ref $get_biases, 'SPVM::BlessedObject::Array');
    is($get_int->get_basic_type_name, 'Int');
  }

  # Numeric value to numeric object
  {
    # Numeric value to numeric object - number to SPVM::Byte
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_byte_object_only(SPVM::Byte->new($BYTE_MAX))->value;
      is($value, $BYTE_MAX);
    }

    # Numeric value to numeric object - number to SPVM::Short
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_short_object_only(SPVM::Short->new($SHORT_MAX))->value;
      is($value, $SHORT_MAX);
    }

    # Numeric value to numeric object - number to SPVM::Int
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_int_object_only(SPVM::Int->new($INT_MAX))->value;
      is($value, $INT_MAX);
    }

    # Numeric value to numeric object - number to SPVM::Long
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_long_object_only(SPVM::Long->new($LONG_MAX))->value;
      is($value, $LONG_MAX);
    }

    # Numeric value to numeric object - number to SPVM::Float
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_float_object_only(SPVM::Float->new($FLT_MAX))->value;
      is($value, $FLT_MAX);
    }

    # Numeric value to numeric object - number to SPVM::Double
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_double_object_only(SPVM::Double->new($DBL_MAX))->value;
      is($value, $DBL_MAX);
    }
  }
  
  # Object
  {
    # Create object
    {
      my $object = SPVM::TestCase->new();
      $object->set_x_int_array($api->new_int_array([$INT_MAX, $INT_MAX]));
      my $spvm_values = $api->new_byte_array_from_bin("abc");
      $object->set_x_byte_array($spvm_values);
      ok(SPVM::TestCase::ExchangeAPI->spvm_object_set_object($object));
    }
    # Create object
    {
      my $object = SPVM::TestCase->new();
      $object->set_x_byte($BYTE_MAX);
      $object->set_x_short($SHORT_MAX);
      $object->set_x_int($INT_MAX);
      $object->set_x_long($LONG_MAX);
      $object->set_x_float($FLOAT_PRECICE);
      $object->set_x_double($DOUBLE_PRECICE);
      $object->set_x_int_array($api->new_int_array([1, 2, 3, 4]));
      my $minimal = SPVM::TestCase::Minimal->new;
      $minimal->set_x(3);
      $object->set_minimal($minimal);
      
      ok(SPVM::TestCase::ExchangeAPI->spvm_object_set($object));
      
      is($object->get_x_byte,$BYTE_MAX);
      is($object->get_x_short, $SHORT_MAX);
      is($object->get_x_int, $INT_MAX);
      is($object->get_x_long, $LONG_MAX);
      is($object->get_x_float, $FLOAT_PRECICE);
      is($object->get_x_double, $DOUBLE_PRECICE);
      is($object->get_minimal->get_x, 3);
    }
  }
  
  # Convert a scalar value to SPVM numeric object
  {

    # SPVM::Byte->new
    {
      {
        my $spvm_value = SPVM::Byte->new(-128);
        is($spvm_value->get_basic_type_name, 'Byte');
        is(ref $spvm_value, 'SPVM::BlessedObject::Class');
        ok($spvm_value->isa('SPVM::BlessedObject::Class'));
        is($spvm_value->value, -128);
      }
    }
    
    # SPVM::Short->new
    {
      {
        my $spvm_value = SPVM::Short->new(-32768);
        is($spvm_value->get_basic_type_name, 'Short');
        ok($spvm_value->isa('SPVM::BlessedObject::Class'));
        is($spvm_value->value, -32768);
      }
    }

    # SPVM::Int->new
    {
      {
        my $spvm_value = SPVM::Int->new(-2147483648);
        is($spvm_value->get_basic_type_name, 'Int');
        ok($spvm_value->isa('SPVM::BlessedObject::Class'));
        is($spvm_value->value, -2147483648);
      }
    }
    # SPVM::Long->new
    {
      {
        my $spvm_value = SPVM::Long->new(-9223372036854775808);
        is($spvm_value->get_basic_type_name, 'Long');
        ok($spvm_value->isa('SPVM::BlessedObject::Class'));
        is($spvm_value->value, -9223372036854775808);
      }
    }

    # SPVM::Float->new
    {
      {
        my $spvm_value = SPVM::Float->new($FLT_MAX);
        is($spvm_value->get_basic_type_name, 'Float');
        ok($spvm_value->isa('SPVM::BlessedObject::Class'));
        is($spvm_value->value, $FLT_MAX);
      }
    }

    # SPVM::Double->new
    {
      {
        my $spvm_value = SPVM::Double->new($DBL_MAX);
        is($spvm_value->get_basic_type_name, 'Double');
        ok($spvm_value->isa('SPVM::BlessedObject::Class'));
        is($spvm_value->value, $DBL_MAX);
      }
    }
  }
}

$api->destroy_runtime_permanent_vars;

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);


done_testing;
