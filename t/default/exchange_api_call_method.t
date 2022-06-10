use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use utf8;
use Data::Dumper;
use File::Basename 'basename';
use FindBin;
use POSIX();
use Encode 'encode';

use Test::More;

my $file = basename $0;

use FindBin;
use Encode 'decode', 'encode';

use SPVM 'TestCase'; my $use_test_line = __LINE__;

use SPVM 'TestCase::ExchangeAPI';
use SPVM 'TestCase::Point_3i';

use SPVM 'Hash';
use SPVM 'List';
use SPVM 'ByteList';
use SPVM 'ShortList';
use SPVM 'IntList';
use SPVM 'LongList';
use SPVM 'FloatList';
use SPVM 'DoubleList';
use SPVM 'StringList';

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

# Argument general exception
{
  # Argument general exception - too few arguments
  {
    eval {
      SPVM::Int->new;
    };
    like($@, qr/too few arguments/i);
  }
  
  # Argument general exception - too many arguments
  {
    eval {
      SPVM::Int->new(1, 2);
    };
    like($@, qr/too many arguments/i);
  }
}

# Argument conversion
{
  # Argument Perl scalar to SPVM number
  {
    # Perl scalar to SPVM byte
    {
      my $total = SPVM::TestCase->sum_byte(8, 3);
      is($total, 11);
    }

    # Perl scalar to SPVM short
    {
      my $total = SPVM::TestCase->sum_short(8, 3);
      is($total, 11);
    }

    # Perl scalar to SPVM int
    {
      my $total = SPVM::TestCase->sum_int(8, 3);
      is($total, 11);
    }

    # Perl scalar to SPVM long
    {
      {
        my $total = SPVM::TestCase->sum_long(8, 3);
        is($total, 11);
      }
      {
        my $total = SPVM::TestCase->sum_long(9223372036854775806, 1);
        is($total, 9223372036854775807);
      }
    }

    # Perl scalar to SPVM float
    {
      my $total = SPVM::TestCase->sum_float(0.25, 0.25);
      cmp_ok($total, '==', 0.5);
    }

    # Perl scalar to SPVM double
    {
      my $total = SPVM::TestCase->sum_double(0.25, 0.25);
      cmp_ok($total, '==', 0.5);
    }
  }

  # Argument Perl scalar to SPVM string
  {
    # Argument Perl non-ref scalar to SPVM string
    {
      # Argument Perl non-ref scalar to SPVM string - ascii
      {
        my $ok = SPVM::TestCase::ExchangeAPI->argument_non_ref_scalar_to_string_ascii("ABC");
        ok($ok);
      }

      # Argument Perl non-ref scalar to SPVM string - UTF-8
      {
        my $ok = SPVM::TestCase::ExchangeAPI->argument_non_ref_scalar_to_string_decoded_string("あいう");
        ok($ok);
      }

      # Argument Perl non-ref scalar to SPVM string - numeric
      {
        my $ok = SPVM::TestCase::ExchangeAPI->argument_non_ref_scalar_to_string_number(4.12);
        ok($ok);
      }

      # Argument Perl non-ref scalar to SPVM string - undef
      {
        my $ok = SPVM::TestCase::ExchangeAPI->argument_non_ref_scalar_to_string_undef(undef);
        ok($ok);
      }
    }
    
    # Argument Perl SPVM::BlessedObject::String to SPVM string
    {
      # Argument Perl SPVM::BlessedObject::String to SPVM string
      {
        my $ok = SPVM::TestCase::ExchangeAPI->argument_blessed_object_string_to_string(SPVM::new_string("あいう"));
        ok($ok);
      }

      # Argument Perl SPVM::BlessedObject::String to SPVM string - undef
      {
        my $ok = SPVM::TestCase::ExchangeAPI->argument_blessed_object_string_to_string_undef(undef);
        ok($ok);
      }
      
      # Argument Perl SPVM::BlessedObject::String to SPVM string - exception invalid type
      {
        eval { SPVM::TestCase::ExchangeAPI->argument_non_ref_scalar_to_string_ascii({}) };
        ok($@);
      }
    }
  }

  # Argument Perl reference to SPVM numeric reference
  {
    {
      # Argument Perl reference to SPVM byte reference
      {
        my $num_byte = $BYTE_MIN;
        SPVM::TestCase::ExchangeAPI->call_spvm_method_numeric_ref_arg_byte(\$num_byte);
        is($num_byte, $BYTE_MIN + 1);
      }
      # Argument Perl reference to SPVM short reference
      {
        my $num_short = $SHORT_MIN;
        SPVM::TestCase::ExchangeAPI->call_spvm_method_numeric_ref_arg_short(\$num_short);
        is($num_short, $SHORT_MIN + 1);
      }
      # Argument Perl reference to SPVM int reference
      {
        my $num_int = $INT_MIN;
        SPVM::TestCase::ExchangeAPI->call_spvm_method_numeric_ref_arg_int(\$num_int);
        is($num_int, $INT_MIN + 1);
      }
      # Argument Perl reference to SPVM long reference
      {
        my $num_long = $LONG_MIN;
        SPVM::TestCase::ExchangeAPI->call_spvm_method_numeric_ref_arg_long(\$num_long);
        is($num_long, $LONG_MIN + 1);
      }
      # Argument Perl reference to SPVM float reference
      {
        my $num_float = POSIX::FLT_MIN();
        SPVM::TestCase::ExchangeAPI->call_spvm_method_numeric_ref_arg_float(\$num_float);
        is($num_float, POSIX::FLT_MIN() + 1);
      }
      # Argument Perl reference to SPVM double reference
      {
        my $num_double = POSIX::DBL_MIN();
        SPVM::TestCase::ExchangeAPI->call_spvm_method_numeric_ref_arg_double(\$num_double);
        is($num_double, POSIX::DBL_MIN() + 1);
      }
    }

    # Argument Perl reference to SPVM numeric reference exception
    {
      # Argument Perl reference to SPVM byte reference exception
      {
        my $num_byte = $BYTE_MIN;
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_numeric_ref_arg_byte($num_byte) };
        ok($@);

        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_numeric_ref_arg_byte({}) };
        ok($@);
      }
      # Argument Perl reference to SPVM short reference exception
      {
        my $num_short = $SHORT_MIN;
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_numeric_ref_arg_short($num_short) };
        ok($@);

        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_numeric_ref_arg_short({}) };
        ok($@);
      }
      # Argument Perl reference to SPVM int reference exception
      {
        my $num_int = $INT_MIN;
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_numeric_ref_arg_int($num_int) };
        ok($@);

        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_numeric_ref_arg_int({}) };
        ok($@);
      }
      # Argument Perl reference to SPVM long reference exception
      {
        my $num_long = $LONG_MIN;
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_numeric_ref_arg_long($num_long) };
        ok($@);

        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_numeric_ref_arg_long({}) };
        ok($@);
      }
      # Argument Perl reference to SPVM float reference exception
      {
        my $num_float = POSIX::FLT_MIN();
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_numeric_ref_arg_float($num_float) };
        ok($@);

        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_numeric_ref_arg_float({}) };
        ok($@);
      }
      # Argument Perl reference to SPVM double reference exception
      {
        my $num_double = POSIX::DBL_MIN();
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_numeric_ref_arg_double($num_double) };
        ok($@);

        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_numeric_ref_arg_double({}) };
        ok($@);
      }
    }
  }

  # Argument Perl array reference to SPVM array
  {
    # Argument Perl array reference to SPVM byte array
    {
      my $perl_array_ref = [1, $BYTE_MAX, $BYTE_MIN];
      my $ok = SPVM::TestCase::ExchangeAPI->argument_perl_array_ref_to_spvm_byte_array($perl_array_ref, undef);
      ok($ok);
    }
    # Argument Perl array reference to SPVM short array
    {
      my $perl_array_ref = [1, $SHORT_MAX, $SHORT_MIN];
      my $ok = SPVM::TestCase::ExchangeAPI->argument_perl_array_ref_to_spvm_short_array($perl_array_ref, undef);
      ok($ok);
    }
    # Argument Perl array reference to SPVM int array
    {
      my $perl_array_ref = [1, $INT_MAX, $INT_MIN];
      my $ok = SPVM::TestCase::ExchangeAPI->argument_perl_array_ref_to_spvm_int_array($perl_array_ref, undef);
      ok($ok);
    }
    # Argument Perl array reference to SPVM long array
    {
      my $perl_array_ref = [1, $LONG_MAX, $LONG_MIN];
      my $ok = SPVM::TestCase::ExchangeAPI->argument_perl_array_ref_to_spvm_long_array($perl_array_ref, undef);
      ok($ok);
    }
    # Argument Perl array reference to SPVM float array
    {
      my $perl_array_ref = [0.5, $FLT_MAX, $FLT_MIN];
      my $ok = SPVM::TestCase::ExchangeAPI->argument_perl_array_ref_to_spvm_float_array($perl_array_ref, undef);
      ok($ok);
    }
    # Argument Perl array reference to SPVM double array
    {
      my $perl_array_ref = [0.5, $DBL_MAX, $DBL_MIN];
      my $ok = SPVM::TestCase::ExchangeAPI->argument_perl_array_ref_to_spvm_double_array($perl_array_ref, undef);
      ok($ok);
    }

    # Argument Perl array reference to SPVM string array
    {
      my $perl_array_ref = ["あいう", "えお", "ab", undef];
      my $ok = SPVM::TestCase::ExchangeAPI->argument_perl_array_ref_to_spvm_string_array($perl_array_ref, undef);
      ok($ok);
    }
  }

  # Argument SPVM::BlessedObject::Array
  {
    # Argument SPVM array to SPVM byte array
    {
      my $spvm_array = SPVM::new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
      my $ok = SPVM::TestCase::ExchangeAPI->argument_spvm_array_to_spvm_byte_array($spvm_array, undef);
      ok($ok);
    }
    # Argument SPVM array to SPVM short array
    {
      my $spvm_array = SPVM::new_short_array([1, $SHORT_MAX, $SHORT_MIN]);
      my $ok = SPVM::TestCase::ExchangeAPI->argument_spvm_array_to_spvm_short_array($spvm_array, undef);
      ok($ok);
    }
    # Argument SPVM array to SPVM int array
    {
      my $spvm_array = SPVM::new_int_array([1, $INT_MAX, $INT_MIN]);
      my $ok = SPVM::TestCase::ExchangeAPI->argument_spvm_array_to_spvm_int_array($spvm_array, undef);
      ok($ok);
    }
    # Argument SPVM array to SPVM long array
    {
      my $spvm_array = SPVM::new_long_array([1, $LONG_MAX, $LONG_MIN]);
      my $ok = SPVM::TestCase::ExchangeAPI->argument_spvm_array_to_spvm_long_array($spvm_array, undef);
      ok($ok);
    }
    # Argument SPVM array to SPVM float array
    {
      my $spvm_array = SPVM::new_float_array([0.5, $FLT_MAX, $FLT_MIN]);
      my $ok = SPVM::TestCase::ExchangeAPI->argument_spvm_array_to_spvm_float_array($spvm_array, undef);
      ok($ok);
    }
    # Argument SPVM array to SPVM double array
    {
      my $spvm_array = SPVM::new_double_array([0.5, $DBL_MAX, $DBL_MIN]);
      my $ok = SPVM::TestCase::ExchangeAPI->argument_spvm_array_to_spvm_double_array($spvm_array, undef);
      ok($ok);
    }
    # Argument SPVM array to SPVM string array
    {
      my $spvm_string_array = SPVM::new_string_array(["あいう", "えお", "ab", undef]);
      my $ok = SPVM::TestCase::ExchangeAPI->argument_spvm_string_array_to_spvm_string_array($spvm_string_array, undef);
      ok($ok);
    }
  }

  # Argument multi numeric
  {
    {
      # Argument multi numeric - byte
      {
        my $input = {x => 1, y => 3, z => $BYTE_MAX};
        my $output = SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_arg_byte($input);
        is_deeply($output, $input);
      }

      # Argument multi numeric - short
      {
        my $input = {x => 1, y => 3, z => $SHORT_MAX};
        my $output = SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_arg_short($input);
        is_deeply($output, $input);
      }

      # Argument multi numeric - int
      {
        my $input = {x => 1, y => 3, z => $INT_MAX};
        my $output = SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_arg_int($input);
        is_deeply($output, $input);
      }

      # Argument multi numeric - long
      {
        my $input = {x => 1, y => 3, z => $LONG_MAX};
        my $output = SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_arg_long($input);
        is_deeply($output, $input);
      }

      # Argument multi numeric - float
      {
        my $input = {x => 1, y => 3, z => $FLT_MAX};
        my $output = SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_arg_float($input);
        is_deeply($output, $input);
      }

      # Argument multi numeric - double
      {
        my $input = {x => 1, y => 3, z => $DBL_MAX};
        my $output = SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_arg_double($input);
        is_deeply($output, $input);
      }
    }

    # Argument multi numeric exception
    {
      # Argument multi numeric exception - byte, field not found
      {
        my $input = {x => 1, y => 3};
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_arg_byte($input) };
        ok($@);
      }

      # Argument multi numeric - short, field not found
      {
        my $input = {x => 1, y => 3};
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_arg_short($input) };
        ok($@);
      }

      # Argument multi numeric - int, field not found
      {
        my $input = {x => 1, y => 3};
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_arg_int($input) };
        ok($@);
      }

      # Argument multi numeric - long, field not found
      {
        my $input = {x => 1, y => 3};
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_arg_long($input) };
        ok($@);
      }

      # Argument multi numeric - float, field not found
      {
        my $input = {x => 1, y => 3};
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_arg_float($input) };
        ok($@);
      }

      # Argument multi numeric - double, field not found
      {
        my $input = {x => 1, y => 3};
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_arg_double($input) };
        ok($@);
      }

      # Argument multi numeric exception - byte, not hash reference
      {
        my $input = 1;
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_arg_byte($input) };
        ok($@);
      }

      # Argument multi numeric - short, not hash reference
      {
        my $input = 1;
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_arg_short($input) };
        ok($@);
      }

      # Argument multi numeric - int, not hash reference
      {
        my $input = 1;
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_arg_int($input) };
        ok($@);
      }

      # Argument multi numeric - long, not hash reference
      {
        my $input = 1;
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_arg_long($input) };
        ok($@);
      }

      # Argument multi numeric - float, not hash reference
      {
        my $input = 1;
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_arg_float($input) };
        ok($@);
      }

      # Argument multi numeric - double, not hash reference
      {
        my $input = 1;
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_arg_double($input) };
        ok($@);
      }
    }
  }

  # Argument multi numeric array
  {
    
    # Argument multi numeric array - byte
    {
      my $values = [
        {x => $BYTE_MIN, y => 1, z => 2},
        {x => 3, y => 4, z => 5},
        {x => 6, y => 7, z => 8},
      ];
      my $spvm_values = SPVM::new_mulnum_array("TestCase::Point_3b[]", $values);
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_byte($values));
      my $out_values = $spvm_values->to_elems;
      is_deeply($out_values, $values);
    }

    # Argument multi numeric array - short
    {
      my $values = [
        {x => $SHORT_MIN, y => 1, z => 2},
        {x => 3, y => 4, z => 5},
        {x => 6, y => 7, z => 8},
      ];
      my $spvm_values = SPVM::new_mulnum_array("TestCase::Point_3s[]", $values);
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_short($values));
      my $out_values = $spvm_values->to_elems;
      is_deeply($out_values, $values);
    }

    # Argument multi numeric array - int
    {
      my $values = [
        {x => $INT_MIN, y => 1, z => 2},
        {x => 3, y => 4, z => 5},
        {x => 6, y => 7, z => 8},
      ];
      my $spvm_values = SPVM::new_mulnum_array("TestCase::Point_3i[]", $values);
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_int($values));
      my $out_values = $spvm_values->to_elems;
      is_deeply($out_values, $values);
    }

    # Argument multi numeric array - long
    {
      my $values = [
        {x => $LONG_MIN, y => 1, z => 2},
        {x => 3, y => 4, z => 5},
        {x => 6, y => 7, z => 8},
      ];
      my $spvm_values = SPVM::new_mulnum_array("TestCase::Point_3l[]", $values);
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_long($values));
      my $out_values = $spvm_values->to_elems;
      is_deeply($out_values, $values);
    }

    # Argument multi numeric array - float
    {
      my $values = [
        {x => $FLT_MIN, y => 1, z => 2},
        {x => 3, y => 4, z => 5},
        {x => 6, y => 7, z => 8},
      ];
      my $spvm_values = SPVM::new_mulnum_array("TestCase::Point_3f[]", $values);
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_float($values));
      my $out_values = $spvm_values->to_elems;
      is_deeply($out_values, $values);
    }

    # Argument multi numeric array - double
    {
      my $values = [
        {x => $DBL_MIN, y => 1, z => 2},
        {x => 3, y => 4, z => 5},
        {x => 6, y => 7, z => 8},
      ];
      my $spvm_values = SPVM::new_mulnum_array("TestCase::Point_3d[]", $values);
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_double($values));
      my $out_values = $spvm_values->to_elems;
      is_deeply($out_values, $values);
    }
  }

  # Argument multi numeric reference
  {
    {
      # Argument multi numeric reference - byte
      {
        my $point = {x => $BYTE_MIN, y => 1, z => 2};
        SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_ref_arg_byte(\$point);
        is_deeply($point, {x => $BYTE_MIN + 1, y => 2, z => 3});
      }
      # Argument multi numeric reference - short
      {
        my $point = {x => $SHORT_MIN, y => 1, z => 2};
        SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_ref_arg_short(\$point);
        is_deeply($point, {x => $SHORT_MIN + 1, y => 2, z => 3});
      }
      # Argument multi numeric reference - int
      {
        my $point = {x => $INT_MIN, y => 1, z => 2};
        SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_ref_arg_int(\$point);
        is_deeply($point, {x => $INT_MIN + 1, y => 2, z => 3});
      }
      # Argument multi numeric reference - long
      {
        my $point = {x => $LONG_MIN, y => 1, z => 2};
        SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_ref_arg_long(\$point);
        is_deeply($point, {x => $LONG_MIN + 1, y => 2, z => 3});
      }
      # Argument multi numeric reference - float
      {
        my $point = {x => $FLT_MIN, y => 1, z => 2};
        SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_ref_arg_float(\$point);
        is_deeply($point, {x => $FLT_MIN + 1, y => 2, z => 3});
      }
      # Argument multi numeric reference - double
      {
        my $point = {x => $DBL_MIN, y => 1, z => 2};
        SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_ref_arg_double(\$point);
        is_deeply($point, {x => $DBL_MIN + 1, y => 2, z => 3});
      }
    }
    
    # Argument multi numeric reference exception
    {
      # Argument multi numeric reference exception - byte, key not found
      {
        my $point = {x => $BYTE_MIN, y => 1};
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_ref_arg_byte(\$point) };
        ok($@);
      }
      # Argument multi numeric reference exception - short, key not found
      {
        my $point = {x => $SHORT_MIN, y => 1};
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_ref_arg_short(\$point) };
        ok($@);
      }
      # Argument multi numeric reference exception - int, key not found
      {
        my $point = {x => $INT_MIN, y => 1};
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_ref_arg_int(\$point) };
        ok($@);
      }
      # Argument multi numeric reference exception - long, key not found
      {
        my $point = {x => $LONG_MIN, y => 1};
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_ref_arg_long(\$point) };
        ok($@);
      }
      # Argument multi numeric reference exception - float, key not found
      {
        my $point = {x => $FLT_MIN, y => 1};
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_ref_arg_float(\$point) };
        ok($@);
      }
      # Argument multi numeric reference exception - double, key not found
      {
        my $point = {x => $DBL_MIN, y => 1};
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_ref_arg_double(\$point) };
        ok($@);
      }

      # Argument multi numeric reference exception - byte, not reference of hash reference
      {
        my $point = {x => $BYTE_MIN, y => 1, z => 2};
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_ref_arg_byte($point) };
        ok($@);
      }
      # Argument multi numeric reference exception - short, not reference of hash reference
      {
        my $point = {x => $SHORT_MIN, y => 1, z => 2};
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_ref_arg_short($point) };
        ok($@);
      }
      # Argument multi numeric reference exception - int, not reference of hash reference
      {
        my $point = {x => $INT_MIN, y => 1, z => 2};
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_ref_arg_int($point) };
        ok($@);
      }
      # Argument multi numeric reference exception - long, not reference of hash reference
      {
        my $point = {x => $LONG_MIN, y => 1, z => 2};
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_ref_arg_long($point) };
        ok($@);
      }
      # Argument multi numeric reference exception - float, not reference of hash reference
      {
        my $point = {x => $FLT_MIN, y => 1, z => 2};
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_ref_arg_float($point) };
        ok($@);
      }
      # Argument multi numeric reference exception - double, not reference of hash reference
      {
        my $point = {x => $DBL_MIN, y => 1, z => 2};
        eval { SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_ref_arg_double($point) };
        ok($@);
      }

    }

    # Argument multi numeric reference and numeric reference mixed
    {
      {
        my $point1 = {x => $BYTE_MIN, y => 1, z => 2};
        my $value1 = 6;
        my $point2 = {x => 3, y => 4, z => 5};
        my $value2 = 7;
        SPVM::TestCase::ExchangeAPI->call_spvm_method_multi_numeric_ref_numeric_ref_mixed_arg(\$point1, \$value1, \$point2, \$value2);
        is_deeply($point1, {x => $BYTE_MIN + 1, y => 2, z => 3});
        is($value1, 7);
        is_deeply($point2, {x => 4, y => 5, z => 6});
        is($value2, 8);
      }
    }
  }
  
  # Argument various patterns
  {
    # Argument - Empty List push
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
        my $list = SPVM::List->new(SPVM::new_object_array("Int[]", []));
        $list->push(SPVM::Int->new(1));
        is_deeply($list->length, 1);
      }
    }

    # Argument - Empty List new
    {
      {
        my $list = SPVM::IntList->new([]);
        is_deeply($list->length, 0);
      }
      {
        my $list = SPVM::List->new(SPVM::new_object_array("Int[]", []));
        is_deeply($list->length, 0);
      }
    }

    # Argument - Pass list
    {
      # Pass list
      {
        my $list = SPVM::List->new(SPVM::new_object_array("Int[]", [SPVM::Int->new(1), SPVM::Int->new(5), undef]));
        my $x = $list->get(0);
        
        is($list->get(0)->value, 1);
        is($list->get(1)->value, 5);
        ok(!defined $list->get(2));
      }
    }

    # Argument - Pass list
    {
      SPVM::List->new(SPVM::new_object_array("object[]", []));
      ok(1);
    }
    
    # Argument - object[] array of any object
    {
      my $args = SPVM::new_object_array('object[]', [SPVM::Int->new(1), SPVM::Double->new(3)]);
      ok(SPVM::TestCase::ExchangeAPI->arg_array_of_any_object($args));
    }
  }
}

# Return value conversion
{
  # Return void
  {
    # Return void
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_void;
      ok(!defined $value);
    }
  }

  # Return numeric
  {
    # Return numeric - byte
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_byte;
      is($value, $BYTE_MIN);
    }
    
    # Return numeric - short
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_short;
      is($value, $SHORT_MIN);
    }
    
    # Return numeric - int
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_int;
      is($value, $INT_MIN);
    }
    
    # Return numeric - long
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_long;
      is($value, $LONG_MIN);
    }
    
    # Return numeric - float
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_float;
      is($value, $FLT_MIN);
    }
    
    # Return numeric - double
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_double;
      is($value, $DBL_MIN);
    }
  }

  # Return string
  {
    # Return string
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_string;
      is(ref $value, 'SPVM::BlessedObject::String');
      ok($value eq "あいう");
    }

    # Return string undef
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_string_undef;
      ok(!defined $value);
    }

    # Return string empty
    {
      my $values = SPVM::TestCase->string_empty();
      is($values, "");
    }
  }

  # Return object
  {
    # Return object
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_object;
      is(ref $value, 'SPVM::TestCase::Minimal');
      isa_ok($value, 'SPVM::BlessedObject::Class');
      is($value->x, 1);
      is($value->y, 2);
    }

    # Return object undef
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_object_undef;
      ok(!defined $value);
    }
  }

  # Return any object
  {
    # Return any object
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_any_object;
      is(ref $value, 'SPVM::TestCase::Minimal');
      isa_ok($value, 'SPVM::BlessedObject::Class');
      is($value->x, 1);
      is($value->y, 2);
    }

    # Return any object undef
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_any_object_undef;
      ok(!defined $value);
    }
  }

  # Return array
  {
    # Return numeric array
    {
      {
        my $blessed_array = SPVM::TestCase::ExchangeAPI->return_numeric_array;
        my $values = $blessed_array->to_elems;
        is_deeply($values, [1, 2, 3]);
      }

      # Return array undef
      {
        my $blessed_array = SPVM::TestCase::ExchangeAPI->return_numeric_array_undef;
        ok(!defined $blessed_array);
      }
    }
    
    # Return object array
    {
      {
        my $blessed_array = SPVM::TestCase::ExchangeAPI->return_object_array;
        my $values = $blessed_array->to_elems;
        is($values->[0]->x, 1);
        is($values->[0]->y, 2);
        is($values->[1]->x, 3);
        is($values->[1]->y, 4);
      }

      # Return array undef
      {
        my $blessed_array = SPVM::TestCase::ExchangeAPI->return_object_array_undef;
        ok(!defined $blessed_array);
      }
    }

    # Return oarray
    {
      {
        my $blessed_array = SPVM::TestCase::ExchangeAPI->return_any_object_array;
        my $values = $blessed_array->to_elems;
        is($values->[0]->x, 1);
        is($values->[0]->y, 2);
        is($values->[1]->x, 3);
        is($values->[1]->y, 4);
      }

      # Return array undef
      {
        my $blessed_array = SPVM::TestCase::ExchangeAPI->return_any_object_array_undef;
        ok(!defined $blessed_array);
      }
    }

    # Return mutil numeric array
    {
      {
        my $blessed_array = SPVM::TestCase::ExchangeAPI->return_multi_numeric_array;
        my $values = $blessed_array->to_elems;
        is_deeply($values, [{x => 1, y => 0, z => 0}, {x => 0, y => 0, z => 5}]);
      }

      # Return array undef
      {
        my $blessed_array = SPVM::TestCase::ExchangeAPI->return_multi_numeric_array_undef;
        ok(!defined $blessed_array);
      }
    }
  }

  # Return multi numeric
  {
    # Return multi numeric - byte
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_byte_multi_numeric;
      is_deeply($value, {x => 1, y => 2, z => $BYTE_MIN});
    }
    
    # Return multi numeric - short
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_short_multi_numeric;
      is_deeply($value, {x => 1, y => 2, z => $SHORT_MIN});
    }
    
    # Return multi numeric - int
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_int_multi_numeric;
      is_deeply($value, {x => 1, y => 2, z => $INT_MIN});
    }
    
    # Return multi numeric - long
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_long_multi_numeric;
      is_deeply($value, {x => 1, y => 2, z => $LONG_MIN});
    }
    
    # Return multi numeric - float
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_float_multi_numeric;
      is_deeply($value, {x => 1, y => 2, z => $FLT_MIN});
    }
    
    # Return multi numeric - double
    {
      my $value = SPVM::TestCase::ExchangeAPI->return_double_multi_numeric;
      is_deeply($value, {x => 1, y => 2, z => $DBL_MIN});
    }
  }

  # Return oarray
  {
    # Return oarray
    {
      my $values = SPVM::TestCase::ExchangeAPI->return_any_object_array->to_elems;
      is($values->[0]->x, 1);
      is($values->[0]->y, 2);
      is($values->[1]->x, 3);
      is($values->[1]->y, 4);
    }
  }
}

# Various tests
{
  # Any object array
  {
    {
      my $bytes = SPVM::new_object_array("Byte[]", [SPVM::Byte->new(1), SPVM::Byte->new(2), SPVM::Byte->new(3)]);
      my $ret = SPVM::TestCase::ExchangeAPI->any_object_array($bytes);
      
      isa_ok($ret, 'SPVM::BlessedObject::Array');
      is_deeply([$ret->to_elems->[0]->value, $ret->to_elems->[1]->value, $ret->to_elems->[2]->value], [1, 2, 5]);
    }
  }

  # SPVM::Hash
  {
    {
      # SPVM::Hash
      my $opt = SPVM::Hash->new(SPVM::new_object_array("object[]", []));
      $opt->set_int(count => 5);
      my $count = $opt->get_int("count");
      
      is($count, 5);
    }

    # Empty Hash new
    {
      {
        my $hash = SPVM::Hash->new(SPVM::new_object_array("object[]", []));
        is_deeply($hash->count, 0);
      }
    }

    # Pass hash
    {
      my $hash = SPVM::Hash->new(SPVM::new_object_array("object[]", []));
      $hash->set_int(x => 1);
      $hash->set_double(y => 2.5);
      is($hash->get("x")->value, 1);
      is($hash->get("y")->value, 2.5);
    }
  }

  # Get hash key - any object
  {
    my $biases = SPVM::new_float_array([1, 2, 3]);
    my $hash = SPVM::Hash->new(SPVM::new_object_array("object[]", []));
    $hash->set(biases => $biases);
    $hash->set("int" => SPVM::Int->new(4));
    my $get_biases = $hash->get("biases");
    my $get_int = $hash->get("int");
    
    is(ref $get_biases, 'SPVM::BlessedObject::Array');
    is(ref $get_int, 'SPVM::Int');
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
      $object->set_x_int_array(SPVM::new_int_array([$INT_MAX, $INT_MAX]));
      my $spvm_values = SPVM::new_byte_array_from_bin("abc");
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
      $object->set_x_int_array(SPVM::new_int_array([1, 2, 3, 4]));
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
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);


done_testing;
