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
use SPVM 'TestCase::Minimal';
use SPVM 'Point';
use SPVM 'Point3D';
use SPVM 'Byte';
use SPVM 'Short';
use SPVM 'Int';
use SPVM 'Long';
use SPVM 'Float';
use SPVM 'Double';
use SPVM 'Bool';

use SPVM 'TestCase::Simple';

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
my $start_memory_blocks_count = $api->get_memory_blocks_count();

# Convert a scalar value to SPVM numeric object
{

  # SPVM::Byte->new
  {
    {
      my $spvm_value = SPVM::Byte->new(-128);
      is($spvm_value->get_class_name, 'Byte');
      is(ref $spvm_value, 'SPVM::BlessedObject::Class');
      ok($spvm_value->isa('SPVM::BlessedObject::Class'));
      is($spvm_value->value, -128);
    }
  }
  
  # SPVM::Short->new
  {
    {
      my $spvm_value = SPVM::Short->new(-32768);
      is($spvm_value->get_class_name, 'Short');
      ok($spvm_value->isa('SPVM::BlessedObject::Class'));
      is($spvm_value->value, -32768);
    }
  }

  # SPVM::Int->new
  {
    {
      my $spvm_value = SPVM::Int->new(-2147483648);
      is($spvm_value->get_class_name, 'Int');
      ok($spvm_value->isa('SPVM::BlessedObject::Class'));
      is($spvm_value->value, -2147483648);
    }
  }
  # SPVM::Long->new
  {
    {
      my $spvm_value = SPVM::Long->new(-9223372036854775808);
      is($spvm_value->get_class_name, 'Long');
      ok($spvm_value->isa('SPVM::BlessedObject::Class'));
      is($spvm_value->value, -9223372036854775808);
    }
  }

  # SPVM::Float->new
  {
    {
      my $spvm_value = SPVM::Float->new($FLT_MAX);
      is($spvm_value->get_class_name, 'Float');
      ok($spvm_value->isa('SPVM::BlessedObject::Class'));
      is($spvm_value->value, $FLT_MAX);
    }
  }

  # SPVM::Double->new
  {
    {
      my $spvm_value = SPVM::Double->new($DBL_MAX);
      is($spvm_value->get_class_name, 'Double');
      ok($spvm_value->isa('SPVM::BlessedObject::Class'));
      is($spvm_value->value, $DBL_MAX);
    }
  }
}

# Convert an array reference to to SPVM numeric array
{
  # new_byte_array
  {
    my $spvm_values = $api->new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
    is(ref $spvm_values, 'SPVM::BlessedObject::Array');
    my $values = $spvm_values->to_elems;
    is_deeply($values, [1, $BYTE_MAX, $BYTE_MIN]);
  }
  # new_short_array
  {
    my $spvm_values = $api->new_short_array([1, $SHORT_MAX, $SHORT_MIN]);
    is(ref $spvm_values, 'SPVM::BlessedObject::Array');
    my $values = $spvm_values->to_elems;
    is_deeply($values, [1, $SHORT_MAX, $SHORT_MIN]);
  }
  # new_int_array
  {
    my $spvm_values = $api->new_int_array([1, $INT_MAX, $INT_MIN]);
    is(ref $spvm_values, 'SPVM::BlessedObject::Array');
    my $values = $spvm_values->to_elems;
    is_deeply($values, [1, $INT_MAX, $INT_MIN]);
  }
  # new_long_array
  {
    my $spvm_values = $api->new_long_array([1, $LONG_MAX, $LONG_MIN]);
    is(ref $spvm_values, 'SPVM::BlessedObject::Array');
    my $values = $spvm_values->to_elems;
    is_deeply($values, [1, $LONG_MAX, $LONG_MIN]);
  }
  # new_float_array
  {
    my $spvm_values = $api->new_float_array([0.5, $FLT_MAX, $FLT_MIN]);
    is(ref $spvm_values, 'SPVM::BlessedObject::Array');
    my $values = $spvm_values->to_elems;
    is_deeply($values, [0.5, $FLT_MAX, $FLT_MIN]);
  }
  # new_double_array
  {
    my $spvm_values = $api->new_double_array([0.5, $DBL_MAX, $DBL_MIN]);
    is(ref $spvm_values, 'SPVM::BlessedObject::Array');
    my $values = $spvm_values->to_elems;
    is_deeply($values, [0.5, $DBL_MAX, $DBL_MIN]);
  }
}

# Create SPVM numeric array with the length
{
  # new_byte_array_len
  {
    {
      my $spvm_values = $api->new_byte_array_len(3);
      my $values = $spvm_values->to_elems;
      is_deeply($values, [0, 0, 0]);
    }
    {
      my $spvm_values = $api->new_byte_array_len(0);
      my $values = $spvm_values->to_elems;
      is_deeply($values, []);
    }
    {
      eval {
        my $spvm_values = $api->new_byte_array_len(-1);
      };
      ok($@);
    }
  }
  # new_short_array_len
  {
    {
      my $spvm_values = $api->new_short_array_len(3);
      my $values = $spvm_values->to_elems;
      is_deeply($values, [0, 0, 0]);
    }
    {
      my $spvm_values = $api->new_short_array_len(0);
      my $values = $spvm_values->to_elems;
      is_deeply($values, []);
    }
    {
      eval {
        my $spvm_values = $api->new_short_array_len(-1);
      };
      ok($@);
    }
  }
  
  # new_int_array_len
  {
    {
      my $spvm_values = $api->new_int_array_len(3);
      my $values = $spvm_values->to_elems;
      is_deeply($values, [0, 0, 0]);
    }
    {
      my $spvm_values = $api->new_int_array_len(0);
      my $values = $spvm_values->to_elems;
      is_deeply($values, []);
    }
    {
      eval {
        my $spvm_values = $api->new_int_array_len(-1);
      };
      ok($@);
    }
  }
  
  # new_long_array_len
  {
    {
      my $spvm_values = $api->new_long_array_len(3);
      my $values = $spvm_values->to_elems;
      is_deeply($values, [0, 0, 0]);
    }
    {
      my $spvm_values = $api->new_long_array_len(0);
      my $values = $spvm_values->to_elems;
      is_deeply($values, []);
    }
    {
      eval {
        my $spvm_values = $api->new_long_array_len(-1);
      };
      ok($@);
    }
  }
  
  # new_float_array_len
  {
    {
      my $spvm_values = $api->new_float_array_len(3);
      my $values = $spvm_values->to_elems;
      is_deeply($values, [0, 0, 0]);
    }
    {
      my $spvm_values = $api->new_float_array_len(0);
      my $values = $spvm_values->to_elems;
      is_deeply($values, []);
    }
    {
      eval {
        my $spvm_values = $api->new_float_array_len(-1);
      };
      ok($@);
    }
  }
  
  # new_double_array_len
  {
    {
      my $spvm_values = $api->new_double_array_len(3);
      my $values = $spvm_values->to_elems;
      is_deeply($values, [0, 0, 0]);
    }
    {
      my $spvm_values = $api->new_double_array_len(0);
      my $values = $spvm_values->to_elems;
      is_deeply($values, []);
    }
    {
      eval {
        my $spvm_values = $api->new_double_array_len(-1);
      };
      ok($@);
    }
  }
}

# Convert a Perl binary data to a SPVM array
{
  # new_byte_array_from_bin
  {
    {
      my $spvm_values = $api->new_byte_array_from_bin("abc");
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_byte_array_bin($spvm_values));
    }
    {
      my $binary = pack('c*', 97, 98, $BYTE_MAX);
      my $spvm_values = $api->new_byte_array_from_bin($binary);
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_byte_array_binary_pack($spvm_values));
    }
    {
      my $binary = pack('c*', 97, 98, $BYTE_MAX);
      my $spvm_values = $api->new_byte_array_from_bin($binary);
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_byte_array_binary_pack($spvm_values));
    }
    {
      my $spvm_values = $api->new_byte_array_from_bin(encode('UTF-8', "あ"));
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_byte_array_from_bin($spvm_values));
    }
    
    {
      eval { my $spvm_values = $api->new_byte_array_from_bin(undef); };
      ok($@);
    }
    {
      my $spvm_values = $api->new_byte_array_from_bin("\xFF\xFE");
      is($spvm_values->[0], -1);
      is($spvm_values->[1], -2);
    }
  }
  
  # new_short_array_from_bin
  {
    my $binary = pack('s*', 97, 98, $SHORT_MAX);
    my $spvm_values = $api->new_short_array_from_bin($binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_short_array_binary_pack($spvm_values));
  }

  # new_int_array_from_bin
  {
    my $binary = pack('l*', 97, 98, $INT_MAX);
    my $spvm_values = $api->new_int_array_from_bin($binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_int_array_binary_pack($spvm_values));
  }

  # new_long_array_from_bin
  {
    my $binary = pack('q*', 97, 98, $LONG_MAX);
    my $spvm_values = $api->new_long_array_from_bin($binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_long_array_binary_pack($spvm_values));
  }

  # new_float_array_from_bin
  {
    my $binary = pack('f*', 97, 98, $FLOAT_PRECICE);
    my $spvm_values = $api->new_float_array_from_bin($binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_float_array_binary_pack($spvm_values));
  }

  # new_double_array_from_bin
  {
    my $binary = pack('d*', 97, 98, $DOUBLE_PRECICE);
    my $spvm_values = $api->new_double_array_from_bin($binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_double_array_binary_pack($spvm_values));
  }
}

# new_mulnum_array_from_bin
{
  # new_mulnum_array_from_bin - byte
  {
    my $binary = pack('c9', ($BYTE_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_values = $api->new_mulnum_array_from_bin("TestCase::Point_3b[]", $binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_byte($spvm_values));
    my $out_bin = $spvm_values->to_bin;
    is_deeply($out_bin, $binary);
  }

  # new_mulnum_array_from_bin - short
  {
    my $binary = pack('s9', ($SHORT_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_values = $api->new_mulnum_array_from_bin("TestCase::Point_3s[]", $binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_short($spvm_values));
    my $out_bin = $spvm_values->to_bin;
    is_deeply($out_bin, $binary);
  }
  
  # new_mulnum_array_from_bin - int
  {
    my $binary = pack('l9', ($INT_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_values = $api->new_mulnum_array_from_bin("TestCase::Point_3i[]", $binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_int($spvm_values));
    my $out_bin = $spvm_values->to_bin;
    is_deeply($out_bin, $binary);
  }
  # new_mulnum_array_from_bin - long
  {
    my $binary = pack('q9', ($LONG_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_values = $api->new_mulnum_array_from_bin("TestCase::Point_3l[]", $binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_long($spvm_values));
    my $out_bin = $spvm_values->to_bin;
    is_deeply($out_bin, $binary);
  }
  # new_mulnum_array_from_bin - float
  {
    my $binary = pack('f9', ($FLT_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_values = $api->new_mulnum_array_from_bin("TestCase::Point_3f[]", $binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_float($spvm_values));
    my $out_bin = $spvm_values->to_bin;
    is_deeply($out_bin, $binary);
  }
  # new_mulnum_array_from_bin - double
  {
    my $binary = pack('d9', ($DBL_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_values = $api->new_mulnum_array_from_bin("TestCase::Point_3d[]", $binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_double($spvm_values));
    my $out_bin = $spvm_values->to_bin;
    is_deeply($out_bin, $binary);
  }

  # new_mulnum_array_from_bin - double
  {
    my $binary = pack('d8', ($DBL_MIN, 1, 2), (3, 4, 5), (6, 7));
    eval {
      $api->new_mulnum_array_from_bin("TestCase::Point_3d[]", $binary);
    };
    ok($@);
  }
}

# ref SPVM array
{
  my $nums = $api->new_float_array([1, 2, 3]);
  is(ref $nums, 'SPVM::BlessedObject::Array');
}

# set_exception
{
  # set_exception - string
  {
    $api->set_exception("あいう");
    ok(SPVM::TestCase::ExchangeAPI->set_exception);
  }
  
  # set_exception - undef
  {
    $api->set_exception(undef);
    ok(SPVM::TestCase::ExchangeAPI->set_exception_undef);
  }
}

# exception
{
  # exception - string
  {
    $api->set_exception("あいう");
    my $exception = $api->get_exception;
    is(ref $exception, 'SPVM::BlessedObject::String');
    is($exception, "あいう");
  }
  
  # exception - SPVM::BlessedObject::String
  {
    $api->set_exception($api->new_string("あいう"));
    my $exception = $api->get_exception;
    is($exception, "あいう");
  }

  # exception - Invalid type
  {
    eval { $api->set_exception([]) };
    ok($@);
  }

  # exception - undef
  {
    $api->set_exception(undef);
    ok(!$api->get_exception);
  }
}


# my variable
{
  ok(SPVM::TestCase->my_var_initialized_zero());
  ok(SPVM::TestCase->my_var_initialized_zero());
}

{
  ok(SPVM::TestCase->new_near_small_base_object_max_size_use_memory_pool());
}

# SPVM new_object_array
{

  # element object array
  {
    my $object1 = SPVM::TestCase->new();
    $object1->set_x_int(1);
    my $object2 = SPVM::TestCase->new();
    $object2->set_x_int(2);
    my $spvm_oarray = $api->new_object_array("TestCase[]", [$object1, $object2]);
    
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_object_array_len_element_any_object_array($spvm_oarray));
    
    my $oarray_out = $spvm_oarray->to_elems;
    is($oarray_out->[0]->get_x_int, 1);
    is($oarray_out->[1]->get_x_int, 2);
  }
  # element byte array
  {
    my $object1 = $api->new_byte_array([1, 2, 3]);
    my $object2 = $api->new_byte_array([4, 5, 6]);
    my $oarray = $api->new_object_array("byte[][]", [$object1, $object2]);

    ok(SPVM::TestCase::ExchangeAPI->spvm_new_object_array_len_element_byte_array($oarray));
    
    my $oarray_out = $oarray->to_elems;
    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element short array
  {
    my $object1 = $api->new_short_array([1, 2, 3]);
    my $object2 = $api->new_short_array([4, 5, 6]);
    my $oarray = $api->new_object_array("short[][]", [$object1, $object2]);

    ok(SPVM::TestCase::ExchangeAPI->spvm_new_object_array_len_element_short_array($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element int array
  {
    my $object1 = $api->new_int_array([1, 2, 3]);
    my $object2 = $api->new_int_array([4, 5, 6]);
    my $oarray = $api->new_object_array("int[][]", [$object1, $object2]);

    ok(SPVM::TestCase::ExchangeAPI->spvm_new_object_array_len_element_int_array($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element long array
  {
    my $object1 = $api->new_long_array([1, 2, 3]);
    my $object2 = $api->new_long_array([4, 5, 6]);
    my $oarray = $api->new_object_array("long[][]", [$object1, $object2]);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_object_array_len_element_long_array($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element float array
  {
    my $object1 = $api->new_float_array([1, 2, 3]);
    my $object2 = $api->new_float_array([4, 5, 6]);
    my $oarray = $api->new_object_array("float[][]", [$object1, $object2]);

    ok(SPVM::TestCase::ExchangeAPI->spvm_new_object_array_len_element_float_array($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element double array
  {
    my $object1 = $api->new_double_array([1, 2, 3]);
    my $object2 = $api->new_double_array([4, 5, 6]);
    my $oarray = $api->new_object_array("double[][]", [$object1, $object2]);
    
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_object_array_len_element_double_array($oarray));
    
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
    my $spvm_values = $api->new_mulnum_array("TestCase::Point_3b[]", $values);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_byte($spvm_values));
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
    my $spvm_values = $api->new_mulnum_array("TestCase::Point_3s[]", $values);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_short($spvm_values));
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
    my $spvm_values = $api->new_mulnum_array("TestCase::Point_3i[]", $values);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_int($spvm_values));
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
    my $spvm_values = $api->new_mulnum_array("TestCase::Point_3l[]", $values);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_long($spvm_values));
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
    my $spvm_values = $api->new_mulnum_array("TestCase::Point_3f[]", $values);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_float($spvm_values));
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
    my $spvm_values = $api->new_mulnum_array("TestCase::Point_3d[]", $values);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_double($spvm_values));
    my $out_values = $spvm_values->to_elems;
    is_deeply($out_values, $values);
  }
}

# new_string
{
  # new_string - Argument decoded string, to_string, "" overload
  {
    my $spvm_string = $api->new_string("あいう");
    is($spvm_string->to_string, "あいう");
    is("$spvm_string", "あいう");
  }

  # new_string - Number
  {
    my $spvm_string = $api->new_string(23);
    is($spvm_string->to_string, 23);
  }

  # new_string - Empty
  {
    my $spvm_string = $api->new_string("");
    is($spvm_string->to_string, "");
  }

  # new_string - undef
  {
    my $spvm_string = $api->new_string(undef);
    ok(!defined $spvm_string);
  }

  # new_string - reference
  {
    eval { $api->new_string([]) };
    like($@, qr/The \$string must be a non-reference scalar or a SPVM::BlessedObject::String object or undef/);
    like($@, qr|XS_SPVM__ExchangeAPI__xs_new_string at SPVM\.xs line \d+|);
  }
  
  # Extra
  {
    # new_string - Argument decoded string, to_string, "" overload
    {
      my $spvm_string = $api->new_string("abc");
      is($spvm_string->to_string, "abc");
      is("$spvm_string", "abc");
    }

    # new_string - Empty
    {
      my $spvm_string = $api->new_string("");
      is($spvm_string->to_string, "");
    }

    # new_string - undef
    {
      my $spvm_string = $api->new_string(undef);
      ok(!defined $spvm_string);
    }

    # new_string - reference
    {
      eval { $api->new_string([]) };
      like($@, qr/The \$string must be a non-reference scalar or a SPVM::BlessedObject::String object or undef/);
    }
  }
}

# new array unsigned
{
  # new_byte_array_unsigned
  {
    my $spvm_values = $api->new_byte_array_unsigned([0, $UBYTE_MAX]);
    my $bin = $spvm_values->to_bin;
    is_deeply([unpack 'C*', $bin], [0, $UBYTE_MAX]);
  }
  # new_short_array_unsigned
  {
    my $spvm_values = $api->new_short_array_unsigned([0, $USHORT_MAX]);
    my $bin = $spvm_values->to_bin;
    is_deeply([unpack 'S*', $bin], [0, $USHORT_MAX]);
  }
  # new_int_array_unsigned
  {
    my $spvm_values = $api->new_int_array_unsigned([0, $UINT_MAX]);
    my $bin = $spvm_values->to_bin;
    is_deeply([unpack 'L*', $bin], [0, $UINT_MAX]);
  }
  # new_long_array_unsigned
  {
    my $spvm_values = $api->new_long_array_unsigned([0, $ULONG_MAX]);
    my $bin = $spvm_values->to_bin;
    is_deeply([unpack 'Q*', $bin], [0, $ULONG_MAX]);
  }
}

# length
{
  {
    my $spvm_values = $api->new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
    my $length = $spvm_values->length;
    is($length, 3);
  }
  {
    my $spvm_values = $api->new_short_array([1, $SHORT_MAX, $SHORT_MIN]);
    my $length = $spvm_values->length;
    is($length, 3);
  }
  {
    my $spvm_values = $api->new_int_array([1, $INT_MAX, $INT_MIN]);
    my $length = $spvm_values->length;
    is($length, 3);
  }
  {
    my $spvm_values = $api->new_long_array([1, $LONG_MAX, $LONG_MIN]);
    my $length = $spvm_values->length;
    is($length, 3);
  }
}

# to_bin
{
  # to_bin 0 length
  {
    {
      my $spvm_values = $api->new_byte_array([]);
      my $binary = $spvm_values->to_bin;
      is($binary, "");
    }
    {
      my $spvm_values = $api->new_short_array([]);
      my $binary = $spvm_values->to_bin;
      is($binary, "");
    }
    {
      my $spvm_values = $api->new_int_array([]);
      my $binary = $spvm_values->to_bin;
      is($binary, "");
    }
    {
      my $spvm_values = $api->new_long_array([]);
      my $binary = $spvm_values->to_bin;
      is($binary, "");
    }
    {
      my $spvm_values = $api->new_float_array([]);
      my $binary = $spvm_values->to_bin;
      is($binary, "");
    }
    {
      my $spvm_values = $api->new_double_array([]);
      my $binary = $spvm_values->to_bin;
      is($binary, "");
    }
  }
    
  # middle size array
  {
    my $length = 1_000_000;
    {
      my $binary = pack('l*', 1 .. $length);
      my $spvm_values = $api->new_int_array_from_bin($binary);
      is($spvm_values->length, $length);
    }
    {
      my $binary = pack('q*', 1 .. $length);
      my $spvm_values = $api->new_long_array_from_bin($binary);
      is($spvm_values->length, $length);
    }
    {
      my $binary = pack('f*', 1 .. $length);
      my $spvm_values = $api->new_float_array_from_bin($binary);
      is($spvm_values->length, $length);
    }
    {
      my $binary = pack('d*', 1 .. $length);
      my $spvm_values = $api->new_double_array_from_bin($binary);
      is($spvm_values->length, $length);
    }
    {
      my $binary = pack('f*', 1 .. $length);
      my $spvm_values = $api->new_float_array_from_bin($binary);
      is($spvm_values->length, $length);
    }
  }
}

# ref SPVM object
{
  my $minimal = SPVM::TestCase::Minimal->new;
  
  is(ref $minimal, 'SPVM::BlessedObject::Class');
}

# stringify SPVM object
{
  my $minimal = SPVM::TestCase::Minimal->new;
  
  like("$minimal", qr/SPVM::BlessedObject::Class/);
}

# Array dereference overload
{
  # list context
  {
    my $values = $api->new_int_array([1, 2, 3]);
    my $copy_values = [];
    for my $value (@$values) {
      push @$copy_values, $value;
    }
    is_deeply($copy_values, [1, 2, 3]);
  }
  
  # Scalar contenxt
  {
    my $values = $api->new_int_array([1, 2, 3]);
    my $length = @$values;
    is($length, 3);
  }
}

{
  {
    my $options = $api->new_options({
      x => SPVM::Int->new(1),
      y => SPVM::Int->new(2)
    });
    my $simple = SPVM::TestCase::Simple->new_options($options);
    is($simple->x, 1);
    is($simple->y, 2);
  }
  {
    my $options = $api->new_options({
    });
    my $simple = SPVM::TestCase::Simple->new_options($options);
    is($simple->x, 0);
    is($simple->y, 0);
  }
  {
    my $options = undef;
    my $simple = SPVM::TestCase::Simple->new_options($options);
    is($simple->x, 0);
    is($simple->y, 0);
  }
}

# dump
{
  # Object
  {
    my $point = SPVM::Point->new(100, 200);
    
    my $dump = $api->dump($point);
    
    is(ref $dump, "SPVM::BlessedObject::String");
    
    like($dump, qr|x|);
    like($dump, qr|y|);
    like($dump, qr|100|);
    like($dump, qr|200|);
  }
  
  # undef
  {
    my $dump = $api->dump(undef);
    
    like($dump, qr|undef|);
  }
  
  # Exceptions
  {
    eval { $api->dump("string"); };
    
    like($@, qr|The \$object must be a SPVM::BlessedObject object|);
  }
}

# Binding SPVM class to Perl class
{
  # Calls a non-defined method
  {
    eval { SPVM::Int->not_defined_method };
    like($@, qr|The "not_defined_method" method in the "Int" class is not found|);
  }
}

# SPVM::BlessedObject::String
{
  # Creates a SPVM::BlessedObject::String object
  {
    my $blessed_object_string = $api->new_string("abc");
    is(ref $blessed_object_string, "SPVM::BlessedObject::String");
  }
  
  # Instance Methods
  {
    # to_bin
    {
      {
        my $blessed_object_string = $api->new_string("abc");
        my $binary = $blessed_object_string->to_bin;
        is($binary, "abc");
      }
      {
        my $blessed_object_string = $api->new_string("あいう");
        my $binary = $blessed_object_string->to_bin;
        ok(!utf8::is_utf8($binary));
        
        {
          my $expected = "あいう";
          utf8::encode($expected);
          is($binary, $expected);
        }
      }
      {
        my $blessed_object_string = $api->new_string("\xFF\xFE");
        my $binary = $blessed_object_string->to_bin;
        is($binary, "\xFF\xFE");
      }
    }
    # to_string
    {
      {
        my $blessed_object_string = $api->new_string("abc");
        my $string = $blessed_object_string->to_string;
        is($string, "abc");
      }
      {
        my $blessed_object_string = $api->new_string("あいう");
        my $string = $blessed_object_string->to_string;
        ok(utf8::is_utf8($string));
        
        {
          is($string, "あいう");
        }
      }
      {
        my $blessed_object_string = $api->new_string("\xFF\xFE");
        eval { $blessed_object_string->to_string; };
        like($@, qr|The SPVM::BlessedObject::String object can't be decoded to Perl string|);
      }
    }
  }
  
  # Operators
  {
    # overload bool
    {
      my $blessed_object_string = $api->new_string("0");
      ok(!!$blessed_object_string);
    }
    # overload "" (stringify)
    {
      {
        my $blessed_object_string = $api->new_string("0");
        is("$blessed_object_string", "0");
      }
      
      {
        my $blessed_object_string = $api->new_string("あいう");
        is("$blessed_object_string", "あいう");
      }
    }
  }
}

# SPVM::BlessedObject::Class
{
  # AUTOLOAD
  {
    # Creates a SPVM::BlessedObject::Class object
    {
      my $blessed_object_class = SPVM::Point->new(1, 2);
      is(ref $blessed_object_class, "SPVM::BlessedObject::Class");
    }
    
    # Calls an instance method - Point
    {
      {
        my $point = SPVM::Point->new(1, 2);
        my $x = $point->x;
        my $y = $point->y;
        
        is($x, 1);
        is($y, 2);
      }
      
      {
        my $point = SPVM::Point->new(1, 2);
        $point->set_x(4);
        my $x = $point->x;
        is($x, 4);
      }
      
      {
        my $point = SPVM::Point->new(1, 2);
        $point->clear;
        my $x = $point->x;
        my $y = $point->y;
        is($x, 0);
        is($y, 0);
      }
    }
    
    # Calls an instance method - Point3D
    {
      {
        my $point = SPVM::Point3D->new(1, 2, 3);
        my $x = $point->x;
        my $y = $point->y;
        my $z = $point->z;
        
        is($x, 1);
        is($y, 2);
        is($z, 3);
      }
      
      {
        my $point = SPVM::Point3D->new(1, 2, 3);
        $point->clear;
        my $x = $point->x;
        my $y = $point->y;
        my $z = $point->z;
        is($x, 0);
        is($y, 0);
        is($z, 0);
      }
    }
    
    # Calls an instance method statically - Point3D
    {
      {
        my $point = SPVM::Point3D->new(1, 2, 3);
        $point->SPVM::Point::clear;
        my $x = $point->x;
        my $y = $point->y;
        my $z = $point->z;
        is($x, 0);
        is($y, 0);
        is($z, 3);
      }
    }
    
    # Exceptions
    {
      # Invocant assinable
      {
        my $point = SPVM::Point3D->new(1, 2, 3);
        eval { $point->SPVM::Int::value; };
        like($@, qr|The invocant must be assinged to the "Int" class|);
      }
      
      # Method not found
      {
        my $point = SPVM::Point->new(1, 2);
        eval { $point->not_found; };
        like($@, qr|The "not_found" method in the "Point" class is not found|);
      }
    }
  }
}

# SPVM::BlessedObject::Array
{
  # Creates a SPVM::BlessedObject::Array object
  {
    my $blessed_object_array = my $spvm_values = $api->new_int_array([0, 0]);
    is(ref $blessed_object_array, "SPVM::BlessedObject::Array");
  }
  
  # get and set
  {
    {
      my $spvm_values = $api->new_byte_array([0, 0]);
      $spvm_values->set(1, $BYTE_MAX);
      is_deeply($spvm_values->to_elems, [0, $BYTE_MAX]);
      my $value = $spvm_values->get(1);
      is($value, $BYTE_MAX);
    }
    {
      my $spvm_values = $api->new_short_array([0, 0]);
      $spvm_values->set(1, $SHORT_MAX);
      is_deeply($spvm_values->to_elems, [0, $SHORT_MAX]);
      my $value = $spvm_values->get(1);
      is($value, $SHORT_MAX);
    }
    {
      my $spvm_values = $api->new_int_array([0, 0]);
      $spvm_values->set(1, $INT_MAX);
      is_deeply($spvm_values->to_elems, [0, $INT_MAX]);
      my $value = $spvm_values->get(1);
      is($value, $INT_MAX);
    }
    {
      my $spvm_values = $api->new_long_array([0, 0]);
      $spvm_values->set(1, $LONG_MAX);
      is_deeply($spvm_values->to_elems, [0, $LONG_MAX]);
      my $value = $spvm_values->get(1);
      is($value, $LONG_MAX);
    }
    {
      my $spvm_values = $api->new_float_array([0, 0]);
      $spvm_values->set(1, $FLOAT_PRECICE);
      is_deeply($spvm_values->to_elems, [0, $FLOAT_PRECICE]);
      my $value = $spvm_values->get(1);
      is($value, $FLOAT_PRECICE);
    }
    {
      my $spvm_values = $api->new_double_array([0, 0]);
      $spvm_values->set(1, $DOUBLE_PRECICE);
      is_deeply($spvm_values->to_elems, [0, $DOUBLE_PRECICE]);
      my $value = $spvm_values->get(1);
      is($value, $DOUBLE_PRECICE);
    }
  }
  
  # overload fallback
  {
    my $spvm_values = $api->new_double_array([0, 0]);
    like("$spvm_values", qr/SPVM::BlessedObject::Array/);
  }
  
  # to_elems
  {
    # to_elems - byte[]
    {
      my $spvm_values = $api->new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
      my $values = $spvm_values->to_elems;
      is_deeply($values, [1, $BYTE_MAX, $BYTE_MIN]);
    }
    # to_elems - short[]
    {
      my $spvm_values = $api->new_short_array([1, $SHORT_MAX, $SHORT_MIN]);
      my $values = $spvm_values->to_elems;
      is_deeply($values, [1, $SHORT_MAX, $SHORT_MIN]);
    }
    
    # to_elems - int[]
    {
      my $spvm_values = $api->new_int_array([1, $INT_MAX, $INT_MIN]);
      my $values = $spvm_values->to_elems;
      is_deeply($values, [1, $INT_MAX, $INT_MIN]);
    }
    # to_elems - long[]
    {
      my $spvm_values = $api->new_long_array([1, $LONG_MAX, $LONG_MIN]);
      my $values = $spvm_values->to_elems;
      is_deeply($values, [1, $LONG_MAX, $LONG_MIN]);
    }
    # to_elems - float[]
    {
      my $spvm_values = $api->new_float_array([0.5, $FLT_MAX, $FLT_MIN]);
      my $values = $spvm_values->to_elems;
      is_deeply($values, [0.5, $FLT_MAX, $FLT_MIN]);
    }
    # to_elems - double[]
    {
      my $spvm_values = $api->new_double_array([0.5, $DBL_MAX, $DBL_MIN]);
      my $values = $spvm_values->to_elems;
      is_deeply($values, [0.5, $DBL_MAX, $DBL_MIN]);
    }
    # to_elems - string[]
    {
      my $spvm_values = $api->new_string_array(["あ", "い"]);
      my $values = $spvm_values->to_elems;
      is(ref $values->[0], "SPVM::BlessedObject::String");
      is($values->[0], "あ");
      is($values->[1], "い");
      is(scalar @$values, 2);
    }
  }
  
  # to_bin
  {
    {
      my $spvm_values = $api->new_byte_array([1, 2, $BYTE_MAX]);
      my $binary = $spvm_values->to_bin;
      
      my @values = unpack('c3', $binary);
      is_deeply(\@values, [1, 2, $BYTE_MAX]);
    }
    {
      my $spvm_values = $api->new_short_array([1, 2, $SHORT_MAX]);
      my $binary = $spvm_values->to_bin;
      
      my @values = unpack('s3', $binary);
      is_deeply(\@values, [1, 2, $SHORT_MAX]);
    }
    {
      my $spvm_values = $api->new_int_array([1, 2, $INT_MAX]);
      my $binary = $spvm_values->to_bin;
      
      my @values = unpack('l3', $binary);
      is_deeply(\@values, [1, 2, $INT_MAX]);
    }
    {
      my $spvm_values = $api->new_long_array([1, 2, $LONG_MAX]);
      my $binary = $spvm_values->to_bin;
      
      my @values = unpack('q3', $binary);
      is_deeply(\@values, [1, 2, $LONG_MAX]);
    }
    {
      my $spvm_values = $api->new_float_array([1, 2, $FLOAT_PRECICE]);
      my $binary = $spvm_values->to_bin;
      
      my @values = unpack('f3', $binary);
      is_deeply(\@values, [1, 2, $FLOAT_PRECICE]);
    }
    {
      my $spvm_values = $api->new_double_array([1, 2, $DOUBLE_PRECICE]);
      my $binary = $spvm_values->to_bin;
      
      my @values = unpack('d3', $binary);
      is_deeply(\@values, [1, 2, $DOUBLE_PRECICE]);
    }
  }
  
  # to_strings
  {
    # to_strings - string[]
    {
      my $spvm_values = $api->new_object_array('Point[]', [SPVM::Point->new(1, 2), SPVM::Point->new(3, 4)]);
      my $values = $spvm_values->to_strings;
      is($values->[0], "(1,2)");
      is($values->[1], "(3,4)");
      is(scalar @$values, 2);
    }
    # to_strings - string[]
    {
      my $spvm_values = $api->new_string_array(["あ", "い"]);
      my $values = $spvm_values->to_strings;
      ok(!ref $values->[0]);
      ok(utf8::is_utf8($values->[0]));
      is($values->[0], "あ");
      is($values->[1], "い");
      is(scalar @$values, 2);
    }
  }
  
  # to_bins
  {
    # to_bins - string[]
    {
      my $spvm_values = $api->new_string_array(["あ", "い"]);
      my $values = $spvm_values->to_bins;
      ok(!ref $values->[0]);
      ok(!utf8::is_utf8($values->[0]));
      {
        my $expected = "あ";
        utf8::encode($expected);
        is($values->[0], $expected);
      }
      {
        my $expected = "い";
        utf8::encode($expected);
        is($values->[1], $expected);
      }
      is(scalar @$values, 2);
    }
  }
}

# TODO

=pod

new_object_array_len
new_string_array_len

=cut

# All object is freed
my $end_memory_blocks_count = $api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);


done_testing;
