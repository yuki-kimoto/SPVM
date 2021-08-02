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
my $FLT_MAX = POSIX::FLT_MAX();
my $DBL_MAX = POSIX::DBL_MAX();
my $UBYTE_MAX = 255;
my $USHORT_MAX = 65535;
my $UINT_MAX = 4294967295;
my $ULONG_MAX = 18446744073709551615;

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Convert a scalar value to SPVM numeric object
{
  # SPVM::Byte->new
  {
    {
      my $spvm_value = SPVM::Byte->new(-128);
      is(ref $spvm_value, 'SPVM::Byte');
      ok($spvm_value->isa('SPVM::BlessedObject::Package'));
      is($spvm_value->value, -128);
    }
  }
  
  # SPVM::Short->new
  {
    {
      my $spvm_value = SPVM::Short->new(-32768);
      is(ref $spvm_value, 'SPVM::Short');
      ok($spvm_value->isa('SPVM::BlessedObject::Package'));
      is($spvm_value->value, -32768);
    }
  }

  # SPVM::Int->new
  {
    {
      my $spvm_value = SPVM::Int->new(-2147483648);
      is(ref $spvm_value, 'SPVM::Int');
      ok($spvm_value->isa('SPVM::BlessedObject::Package'));
      is($spvm_value->value, -2147483648);
    }
  }
  # SPVM::Long->new
  {
    {
      my $spvm_value = SPVM::Long->new(-9223372036854775808);
      is(ref $spvm_value, 'SPVM::Long');
      ok($spvm_value->isa('SPVM::BlessedObject::Package'));
      is($spvm_value->value, -9223372036854775808);
    }
  }

  # SPVM::Float->new
  {
    {
      my $spvm_value = SPVM::Float->new($FLT_MAX);
      is(ref $spvm_value, 'SPVM::Float');
      ok($spvm_value->isa('SPVM::BlessedObject::Package'));
      is($spvm_value->value, $FLT_MAX);
    }
  }

  # SPVM::Double->new
  {
    {
      my $spvm_value = SPVM::Double->new($DBL_MAX);
      is(ref $spvm_value, 'SPVM::Double');
      ok($spvm_value->isa('SPVM::BlessedObject::Package'));
      is($spvm_value->value, $DBL_MAX);
    }
  }
}

# ref SPVM array
{
  my $nums = SPVM::new_float_array([1, 2, 3]);
  is(ref $nums, 'SPVM::BlessedObject::Array');
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

    ok(TestCase::ExchangeAPI->spvm_new_object_array_len_element_byte_array($oarray));
    
    my $oarray_out = $oarray->to_elems;
    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element short array
  {
    my $object1 = SPVM::new_short_array([1, 2, 3]);
    my $object2 = SPVM::new_short_array([4, 5, 6]);
    my $oarray = SPVM::new_object_array("short[][]", [$object1, $object2]);

    ok(TestCase::ExchangeAPI->spvm_new_object_array_len_element_short_array($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element int array
  {
    my $object1 = SPVM::new_int_array([1, 2, 3]);
    my $object2 = SPVM::new_int_array([4, 5, 6]);
    my $oarray = SPVM::new_object_array("int[][]", [$object1, $object2]);

    ok(TestCase::ExchangeAPI->spvm_new_object_array_len_element_int_array($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element long array
  {
    my $object1 = SPVM::new_long_array([1, 2, 3]);
    my $object2 = SPVM::new_long_array([4, 5, 6]);
    my $oarray = SPVM::new_object_array("long[][]", [$object1, $object2]);
    ok(TestCase::ExchangeAPI->spvm_new_object_array_len_element_long_array($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element float array
  {
    my $object1 = SPVM::new_float_array([1, 2, 3]);
    my $object2 = SPVM::new_float_array([4, 5, 6]);
    my $oarray = SPVM::new_object_array("float[][]", [$object1, $object2]);

    ok(TestCase::ExchangeAPI->spvm_new_object_array_len_element_float_array($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element double array
  {
    my $object1 = SPVM::new_double_array([1, 2, 3]);
    my $object2 = SPVM::new_double_array([4, 5, 6]);
    my $oarray = SPVM::new_object_array("double[][]", [$object1, $object2]);
    
    ok(TestCase::ExchangeAPI->spvm_new_object_array_len_element_double_array($oarray));
    
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

# new_string
{
  # new_string - Argument decoded string, to_string, "" overload
  {
    my $spvm_string = SPVM::new_string("あいう");
    is($spvm_string->to_string, "あいう");
    is("$spvm_string", "あいう");
  }

  # new_string - Number
  {
    my $spvm_string = SPVM::new_string(23);
    is($spvm_string->to_string, 23);
  }

  # new_string - Empty
  {
    my $spvm_string = SPVM::new_string("");
    is($spvm_string->to_string, "");
  }

  # new_string - undef
  {
    eval { SPVM::new_string(undef) };
    like($@, qr/Argument must be defined/);
  }

  # new_string - reference
  {
    eval { SPVM::new_string([]) };
    like($@, qr/Argument must not be reference/);
  }
}

# new_string_from_bin
{
  # new_string_from_bin - Argument decoded string, to_string, "" overload
  {
    my $spvm_string = SPVM::new_string_from_bin("abc");
    is($spvm_string->to_string, "abc");
    is("$spvm_string", "abc");
  }

  # new_string_from_bin - Empty
  {
    my $spvm_string = SPVM::new_string_from_bin("");
    is($spvm_string->to_string, "");
  }

  # new_string_from_bin - undef
  {
    eval { SPVM::new_string_from_bin(undef) };
    like($@, qr/Argument must be defined/);
  }

  # new_string_from_bin - reference
  {
    eval { SPVM::new_string_from_bin([]) };
    like($@, qr/Argument must not be reference/);
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

# new array unsigned
{
  # new_byte_array_unsigned
  {
    my $spvm_values = SPVM::new_byte_array_unsigned([0, $UBYTE_MAX]);
    my $bin = $spvm_values->to_bin;
    is_deeply([unpack 'C*', $bin], [0, $UBYTE_MAX]);
  }
  # new_short_array_unsigned
  {
    my $spvm_values = SPVM::new_short_array_unsigned([0, $USHORT_MAX]);
    my $bin = $spvm_values->to_bin;
    is_deeply([unpack 'S*', $bin], [0, $USHORT_MAX]);
  }
  # new_int_array_unsigned
  {
    my $spvm_values = SPVM::new_int_array_unsigned([0, $UINT_MAX]);
    my $bin = $spvm_values->to_bin;
    is_deeply([unpack 'L*', $bin], [0, $UINT_MAX]);
  }
  # new_long_array_unsigned
  {
    my $spvm_values = SPVM::new_long_array_unsigned([0, $ULONG_MAX]);
    my $bin = $spvm_values->to_bin;
    is_deeply([unpack 'Q*', $bin], [0, $ULONG_MAX]);
  }
}

# new array_len
{
  # new_byte_array_len
  {
    my $spvm_values = SPVM::new_byte_array_len(3);
    my $values = $spvm_values->to_elems;
    is_deeply($values, [0, 0, 0]);
  }
  {
    my $spvm_values = SPVM::new_byte_array_len(0);
    my $values = $spvm_values->to_elems;
    is_deeply($values, []);
  }
  # new_short_array_len
  {
    my $spvm_values = SPVM::new_short_array_len(3);
    my $values = $spvm_values->to_elems;
    is_deeply($values, [0, 0, 0]);
  }
  {
    my $spvm_values = SPVM::new_short_array_len(0);
    my $values = $spvm_values->to_elems;
    is_deeply($values, []);
  }
  # new_int_array_len
  {
    my $spvm_values = SPVM::new_int_array_len(3);
    my $values = $spvm_values->to_elems;
    is_deeply($values, [0, 0, 0]);
  }
  {
    my $spvm_values = SPVM::new_int_array_len(0);
    my $values = $spvm_values->to_elems;
    is_deeply($values, []);
  }
  # new_long_array_len
  {
    my $spvm_values = SPVM::new_long_array_len(3);
    my $values = $spvm_values->to_elems;
    is_deeply($values, [0, 0, 0]);
  }
  {
    my $spvm_values = SPVM::new_long_array_len(0);
    my $values = $spvm_values->to_elems;
    is_deeply($values, []);
  }
  # new_float_array_len
  {
    my $spvm_values = SPVM::new_float_array_len(3);
    my $values = $spvm_values->to_elems;
    is_deeply($values, [0, 0, 0]);
  }
  {
    my $spvm_values = SPVM::new_float_array_len(0);
    my $values = $spvm_values->to_elems;
    is_deeply($values, []);
  }
  # new_double_array_len
  {
    my $spvm_values = SPVM::new_double_array_len(3);
    my $values = $spvm_values->to_elems;
    is_deeply($values, [0, 0, 0]);
  }
  {
    my $spvm_values = SPVM::new_double_array_len(0);
    my $values = $spvm_values->to_elems;
    is_deeply($values, []);
  }
}

# length
{
  {
    my $spvm_values = SPVM::new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
    my $length = $spvm_values->length;
    is($length, 3);
  }
  {
    my $spvm_values = SPVM::new_short_array([1, $SHORT_MAX, $SHORT_MIN]);
    my $length = $spvm_values->length;
    is($length, 3);
  }
  {
    my $spvm_values = SPVM::new_int_array([1, $INT_MAX, $INT_MIN]);
    my $length = $spvm_values->length;
    is($length, 3);
  }
  {
    my $spvm_values = SPVM::new_long_array([1, $LONG_MAX, $LONG_MIN]);
    my $length = $spvm_values->length;
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
      is($spvm_values->length, $length);
    }
    {
      my $binary = pack('q*', 1 .. $length);
      my $spvm_values = SPVM::new_long_array_from_bin($binary);
      is($spvm_values->length, $length);
    }
    {
      my $binary = pack('f*', 1 .. $length);
      my $spvm_values = SPVM::new_float_array_from_bin($binary);
      is($spvm_values->length, $length);
    }
    {
      my $binary = pack('d*', 1 .. $length);
      my $spvm_values = SPVM::new_double_array_from_bin($binary);
      is($spvm_values->length, $length);
    }
    {
      my $binary = pack('f*', 1 .. $length);
      my $spvm_values = SPVM::new_float_array_from_bin($binary);
      is($spvm_values->length, $length);
    }
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

