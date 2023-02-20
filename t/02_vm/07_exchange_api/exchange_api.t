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

# to_elems
{
  # to_elems
  {
    # to_elems - byte[]
    {
      my $sp_values = $api->new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
      my $values = $sp_values->to_elems;
      is_deeply($values, [1, $BYTE_MAX, $BYTE_MIN]);
    }
    # to_elems - short[]
    {
      my $sp_values = $api->new_short_array([1, $SHORT_MAX, $SHORT_MIN]);
      my $values = $sp_values->to_elems;
      is_deeply($values, [1, $SHORT_MAX, $SHORT_MIN]);
    }
    
    # to_elems - int[]
    {
      my $sp_values = $api->new_int_array([1, $INT_MAX, $INT_MIN]);
      my $values = $sp_values->to_elems;
      is_deeply($values, [1, $INT_MAX, $INT_MIN]);
    }
    # to_elems - long[]
    {
      my $sp_values = $api->new_long_array([1, $LONG_MAX, $LONG_MIN]);
      my $values = $sp_values->to_elems;
      is_deeply($values, [1, $LONG_MAX, $LONG_MIN]);
    }
    # to_elems - float[]
    {
      my $sp_values = $api->new_float_array([0.5, $FLT_MAX, $FLT_MIN]);
      my $values = $sp_values->to_elems;
      is_deeply($values, [0.5, $FLT_MAX, $FLT_MIN]);
    }
    # to_elems - double[]
    {
      my $sp_values = $api->new_double_array([0.5, $DBL_MAX, $DBL_MIN]);
      my $values = $sp_values->to_elems;
      is_deeply($values, [0.5, $DBL_MAX, $DBL_MIN]);
    }
    # to_elems - string[]
    {
      my $sp_values = $api->new_string_array(["あ", "い"]);
      my $values = $sp_values->to_elems;
      is(ref $values->[0], "SPVM::BlessedObject::String");
      is($values->[0], "あ");
      is($values->[1], "い");
      is(scalar @$values, 2);
    }
    # to_strings - string[]
    {
      my $sp_values = $api->new_object_array('Point[]', [SPVM::Point->new(1, 2), SPVM::Point->new(3, 4)]);
      my $values = $sp_values->to_strings;
      is($values->[0], "(1,2)");
      is($values->[1], "(3,4)");
      is(scalar @$values, 2);
    }
    # to_strings - string[]
    {
      my $sp_values = $api->new_string_array(["あ", "い"]);
      my $values = $sp_values->to_strings;
      ok(!ref $values->[0]);
      ok(utf8::is_utf8($values->[0]));
      is($values->[0], "あ");
      is($values->[1], "い");
      is(scalar @$values, 2);
    }
    # to_bins - string[]
    {
      my $sp_values = $api->new_string_array(["あ", "い"]);
      my $values = $sp_values->to_bins;
      ok(!ref $values->[0]);
      ok(!utf8::is_utf8($values->[0]));
      is($values->[0], Encode::encode('UTF-8', "あ"));
      is($values->[1], Encode::encode('UTF-8', "い"));
      is(scalar @$values, 2);
    }
  }
}
# Convert a scalar value to SPVM numeric object
{

  # SPVM::Byte->new
  {
    {
      my $sp_value = SPVM::Byte->new(-128);
      is($sp_value->get_class_name, 'Byte');
      is(ref $sp_value, 'SPVM::BlessedObject::Class');
      ok($sp_value->isa('SPVM::BlessedObject::Class'));
      is($sp_value->value, -128);
    }
  }
  
  # SPVM::Short->new
  {
    {
      my $sp_value = SPVM::Short->new(-32768);
      is($sp_value->get_class_name, 'Short');
      ok($sp_value->isa('SPVM::BlessedObject::Class'));
      is($sp_value->value, -32768);
    }
  }

  # SPVM::Int->new
  {
    {
      my $sp_value = SPVM::Int->new(-2147483648);
      is($sp_value->get_class_name, 'Int');
      ok($sp_value->isa('SPVM::BlessedObject::Class'));
      is($sp_value->value, -2147483648);
    }
  }
  # SPVM::Long->new
  {
    {
      my $sp_value = SPVM::Long->new(-9223372036854775808);
      is($sp_value->get_class_name, 'Long');
      ok($sp_value->isa('SPVM::BlessedObject::Class'));
      is($sp_value->value, -9223372036854775808);
    }
  }

  # SPVM::Float->new
  {
    {
      my $sp_value = SPVM::Float->new($FLT_MAX);
      is($sp_value->get_class_name, 'Float');
      ok($sp_value->isa('SPVM::BlessedObject::Class'));
      is($sp_value->value, $FLT_MAX);
    }
  }

  # SPVM::Double->new
  {
    {
      my $sp_value = SPVM::Double->new($DBL_MAX);
      is($sp_value->get_class_name, 'Double');
      ok($sp_value->isa('SPVM::BlessedObject::Class'));
      is($sp_value->value, $DBL_MAX);
    }
  }
}

# Convert an array reference to to SPVM numeric array
{
  # new_byte_array
  {
    my $sp_values = $api->new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
    is(ref $sp_values, 'SPVM::BlessedObject::Array');
    my $values = $sp_values->to_elems;
    is_deeply($values, [1, $BYTE_MAX, $BYTE_MIN]);
  }
  # new_short_array
  {
    my $sp_values = $api->new_short_array([1, $SHORT_MAX, $SHORT_MIN]);
    is(ref $sp_values, 'SPVM::BlessedObject::Array');
    my $values = $sp_values->to_elems;
    is_deeply($values, [1, $SHORT_MAX, $SHORT_MIN]);
  }
  # new_int_array
  {
    my $sp_values = $api->new_int_array([1, $INT_MAX, $INT_MIN]);
    is(ref $sp_values, 'SPVM::BlessedObject::Array');
    my $values = $sp_values->to_elems;
    is_deeply($values, [1, $INT_MAX, $INT_MIN]);
  }
  # new_long_array
  {
    my $sp_values = $api->new_long_array([1, $LONG_MAX, $LONG_MIN]);
    is(ref $sp_values, 'SPVM::BlessedObject::Array');
    my $values = $sp_values->to_elems;
    is_deeply($values, [1, $LONG_MAX, $LONG_MIN]);
  }
  # new_float_array
  {
    my $sp_values = $api->new_float_array([0.5, $FLT_MAX, $FLT_MIN]);
    is(ref $sp_values, 'SPVM::BlessedObject::Array');
    my $values = $sp_values->to_elems;
    is_deeply($values, [0.5, $FLT_MAX, $FLT_MIN]);
  }
  # new_double_array
  {
    my $sp_values = $api->new_double_array([0.5, $DBL_MAX, $DBL_MIN]);
    is(ref $sp_values, 'SPVM::BlessedObject::Array');
    my $values = $sp_values->to_elems;
    is_deeply($values, [0.5, $DBL_MAX, $DBL_MIN]);
  }
}

# Create SPVM numeric array with the length
{
  # new_byte_array_len
  {
    {
      my $sp_values = $api->new_byte_array_len(3);
      my $values = $sp_values->to_elems;
      is_deeply($values, [0, 0, 0]);
    }
    {
      my $sp_values = $api->new_byte_array_len(0);
      my $values = $sp_values->to_elems;
      is_deeply($values, []);
    }
    {
      eval {
        my $sp_values = $api->new_byte_array_len(-1);
      };
      ok($@);
    }
  }
  # new_short_array_len
  {
    {
      my $sp_values = $api->new_short_array_len(3);
      my $values = $sp_values->to_elems;
      is_deeply($values, [0, 0, 0]);
    }
    {
      my $sp_values = $api->new_short_array_len(0);
      my $values = $sp_values->to_elems;
      is_deeply($values, []);
    }
    {
      eval {
        my $sp_values = $api->new_short_array_len(-1);
      };
      ok($@);
    }
  }
  
  # new_int_array_len
  {
    {
      my $sp_values = $api->new_int_array_len(3);
      my $values = $sp_values->to_elems;
      is_deeply($values, [0, 0, 0]);
    }
    {
      my $sp_values = $api->new_int_array_len(0);
      my $values = $sp_values->to_elems;
      is_deeply($values, []);
    }
    {
      eval {
        my $sp_values = $api->new_int_array_len(-1);
      };
      ok($@);
    }
  }
  
  # new_long_array_len
  {
    {
      my $sp_values = $api->new_long_array_len(3);
      my $values = $sp_values->to_elems;
      is_deeply($values, [0, 0, 0]);
    }
    {
      my $sp_values = $api->new_long_array_len(0);
      my $values = $sp_values->to_elems;
      is_deeply($values, []);
    }
    {
      eval {
        my $sp_values = $api->new_long_array_len(-1);
      };
      ok($@);
    }
  }
  
  # new_float_array_len
  {
    {
      my $sp_values = $api->new_float_array_len(3);
      my $values = $sp_values->to_elems;
      is_deeply($values, [0, 0, 0]);
    }
    {
      my $sp_values = $api->new_float_array_len(0);
      my $values = $sp_values->to_elems;
      is_deeply($values, []);
    }
    {
      eval {
        my $sp_values = $api->new_float_array_len(-1);
      };
      ok($@);
    }
  }
  
  # new_double_array_len
  {
    {
      my $sp_values = $api->new_double_array_len(3);
      my $values = $sp_values->to_elems;
      is_deeply($values, [0, 0, 0]);
    }
    {
      my $sp_values = $api->new_double_array_len(0);
      my $values = $sp_values->to_elems;
      is_deeply($values, []);
    }
    {
      eval {
        my $sp_values = $api->new_double_array_len(-1);
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
      my $sp_values = $api->new_byte_array_from_bin("abc");
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_byte_array_bin($sp_values));
    }
    {
      my $binary = pack('c*', 97, 98, $BYTE_MAX);
      my $sp_values = $api->new_byte_array_from_bin($binary);
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_byte_array_binary_pack($sp_values));
    }
    {
      my $binary = pack('c*', 97, 98, $BYTE_MAX);
      my $sp_values = $api->new_byte_array_from_bin($binary);
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_byte_array_binary_pack($sp_values));
    }
    {
      my $sp_values = $api->new_byte_array_from_bin(encode('UTF-8', "あ"));
      ok(SPVM::TestCase::ExchangeAPI->spvm_new_byte_array_from_bin($sp_values));
    }
  }
  
  # new_short_array_from_bin
  {
    my $binary = pack('s*', 97, 98, $SHORT_MAX);
    my $sp_values = $api->new_short_array_from_bin($binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_short_array_binary_pack($sp_values));
  }

  # new_int_array_from_bin
  {
    my $binary = pack('l*', 97, 98, $INT_MAX);
    my $sp_values = $api->new_int_array_from_bin($binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_int_array_binary_pack($sp_values));
  }

  # new_long_array_from_bin
  {
    my $binary = pack('q*', 97, 98, $LONG_MAX);
    my $sp_values = $api->new_long_array_from_bin($binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_long_array_binary_pack($sp_values));
  }

  # new_float_array_from_bin
  {
    my $binary = pack('f*', 97, 98, $FLOAT_PRECICE);
    my $sp_values = $api->new_float_array_from_bin($binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_float_array_binary_pack($sp_values));
  }

  # new_double_array_from_bin
  {
    my $binary = pack('d*', 97, 98, $DOUBLE_PRECICE);
    my $sp_values = $api->new_double_array_from_bin($binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_double_array_binary_pack($sp_values));
  }
}

# Convert a Perl string to a SPVM array
{
  # new_byte_array_from_string
  {
    {
      my $sp_values = $api->new_byte_array_from_string("あいう");
      ok(SPVM::TestCase::ExchangeAPI->new_byte_array_from_string($sp_values));
    }
    {
      my $sp_values = $api->new_byte_array_from_string("\xFF\xFE");
      is($sp_values->[0], -1);
      is($sp_values->[1], -2);
    }
  }
}

# new_string_from_bin
{
  # new_string_from_bin - Argument decoded string, to_string, "" overload
  {
    my $sp_string = $api->new_string_from_bin("abc");
    is($sp_string->to_string, "abc");
    is("$sp_string", "abc");
  }

  # new_string_from_bin - Empty
  {
    my $sp_string = $api->new_string_from_bin("");
    is($sp_string->to_string, "");
  }

  # new_string_from_bin - undef
  {
    eval { $api->new_string_from_bin(undef) };
    like($@, qr/The binary must be defined/);
  }

  # new_string_from_bin - reference
  {
    eval { $api->new_string_from_bin([]) };
    like($@, qr/The binary can't be a reference/);
  }
}

# new_mulnum_array_from_bin
{
  # new_mulnum_array_from_bin - byte
  {
    my $binary = pack('c9', ($BYTE_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $sp_values = $api->new_mulnum_array_from_bin("TestCase::Point_3b[]", $binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_byte($sp_values));
    my $out_bin = $sp_values->to_bin;
    is_deeply($out_bin, $binary);
  }

  # new_mulnum_array_from_bin - short
  {
    my $binary = pack('s9', ($SHORT_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $sp_values = $api->new_mulnum_array_from_bin("TestCase::Point_3s[]", $binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_short($sp_values));
    my $out_bin = $sp_values->to_bin;
    is_deeply($out_bin, $binary);
  }
  
  # new_mulnum_array_from_bin - int
  {
    my $binary = pack('l9', ($INT_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $sp_values = $api->new_mulnum_array_from_bin("TestCase::Point_3i[]", $binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_int($sp_values));
    my $out_bin = $sp_values->to_bin;
    is_deeply($out_bin, $binary);
  }
  # new_mulnum_array_from_bin - long
  {
    my $binary = pack('q9', ($LONG_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $sp_values = $api->new_mulnum_array_from_bin("TestCase::Point_3l[]", $binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_long($sp_values));
    my $out_bin = $sp_values->to_bin;
    is_deeply($out_bin, $binary);
  }
  # new_mulnum_array_from_bin - float
  {
    my $binary = pack('f9', ($FLT_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $sp_values = $api->new_mulnum_array_from_bin("TestCase::Point_3f[]", $binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_float($sp_values));
    my $out_bin = $sp_values->to_bin;
    is_deeply($out_bin, $binary);
  }
  # new_mulnum_array_from_bin - double
  {
    my $binary = pack('d9', ($DBL_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $sp_values = $api->new_mulnum_array_from_bin("TestCase::Point_3d[]", $binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_double($sp_values));
    my $out_bin = $sp_values->to_bin;
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
    my $sp_oarray = $api->new_object_array("TestCase[]", [$object1, $object2]);
    
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_object_array_len_element_any_object_array($sp_oarray));
    
    my $oarray_out = $sp_oarray->to_elems;
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
    my $sp_values = $api->new_mulnum_array("TestCase::Point_3b[]", $values);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_byte($sp_values));
    my $out_values = $sp_values->to_elems;
    is_deeply($out_values, $values);
  }

  # new_mulnum_array - short
  {
    my $values = [
      {x => $SHORT_MIN, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $sp_values = $api->new_mulnum_array("TestCase::Point_3s[]", $values);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_short($sp_values));
    my $out_values = $sp_values->to_elems;
    is_deeply($out_values, $values);
  }

  # new_mulnum_array - int
  {
    my $values = [
      {x => $INT_MIN, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $sp_values = $api->new_mulnum_array("TestCase::Point_3i[]", $values);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_int($sp_values));
    my $out_values = $sp_values->to_elems;
    is_deeply($out_values, $values);
  }

  # new_mulnum_array - long
  {
    my $values = [
      {x => $LONG_MIN, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $sp_values = $api->new_mulnum_array("TestCase::Point_3l[]", $values);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_long($sp_values));
    my $out_values = $sp_values->to_elems;
    is_deeply($out_values, $values);
  }

  # new_mulnum_array - float
  {
    my $values = [
      {x => $FLT_MIN, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $sp_values = $api->new_mulnum_array("TestCase::Point_3f[]", $values);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_float($sp_values));
    my $out_values = $sp_values->to_elems;
    is_deeply($out_values, $values);
  }

  # new_mulnum_array - double
  {
    my $values = [
      {x => $DBL_MIN, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $sp_values = $api->new_mulnum_array("TestCase::Point_3d[]", $values);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_double($sp_values));
    my $out_values = $sp_values->to_elems;
    is_deeply($out_values, $values);
  }
}

# new_string
{
  # new_string - Argument decoded string, to_string, "" overload
  {
    my $sp_string = $api->new_string("あいう");
    is($sp_string->to_string, "あいう");
    is("$sp_string", "あいう");
  }

  # new_string - Number
  {
    my $sp_string = $api->new_string(23);
    is($sp_string->to_string, 23);
  }

  # new_string - Empty
  {
    my $sp_string = $api->new_string("");
    is($sp_string->to_string, "");
  }

  # new_string - undef
  {
    eval { $api->new_string(undef) };
    like($@, qr/The string must be defined/);
  }

  # new_string - reference
  {
    eval { $api->new_string([]) };
    like($@, qr/The string can't be a reference/);
    like($@, qr|XS_SPVM__ExchangeAPI_xs_new_string at SPVM\.xs line \d+|);
  }
}

# new array unsigned
{
  # new_byte_array_unsigned
  {
    my $sp_values = $api->new_byte_array_unsigned([0, $UBYTE_MAX]);
    my $bin = $sp_values->to_bin;
    is_deeply([unpack 'C*', $bin], [0, $UBYTE_MAX]);
  }
  # new_short_array_unsigned
  {
    my $sp_values = $api->new_short_array_unsigned([0, $USHORT_MAX]);
    my $bin = $sp_values->to_bin;
    is_deeply([unpack 'S*', $bin], [0, $USHORT_MAX]);
  }
  # new_int_array_unsigned
  {
    my $sp_values = $api->new_int_array_unsigned([0, $UINT_MAX]);
    my $bin = $sp_values->to_bin;
    is_deeply([unpack 'L*', $bin], [0, $UINT_MAX]);
  }
  # new_long_array_unsigned
  {
    my $sp_values = $api->new_long_array_unsigned([0, $ULONG_MAX]);
    my $bin = $sp_values->to_bin;
    is_deeply([unpack 'Q*', $bin], [0, $ULONG_MAX]);
  }
}

# length
{
  {
    my $sp_values = $api->new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
    my $length = $sp_values->length;
    is($length, 3);
  }
  {
    my $sp_values = $api->new_short_array([1, $SHORT_MAX, $SHORT_MIN]);
    my $length = $sp_values->length;
    is($length, 3);
  }
  {
    my $sp_values = $api->new_int_array([1, $INT_MAX, $INT_MIN]);
    my $length = $sp_values->length;
    is($length, 3);
  }
  {
    my $sp_values = $api->new_long_array([1, $LONG_MAX, $LONG_MIN]);
    my $length = $sp_values->length;
    is($length, 3);
  }
}

# to_bin
{
  # to_bin 0 length
  {
    {
      my $sp_values = $api->new_byte_array([]);
      my $binary = $sp_values->to_bin;
      is($binary, "");
    }
    {
      my $sp_values = $api->new_short_array([]);
      my $binary = $sp_values->to_bin;
      is($binary, "");
    }
    {
      my $sp_values = $api->new_int_array([]);
      my $binary = $sp_values->to_bin;
      is($binary, "");
    }
    {
      my $sp_values = $api->new_long_array([]);
      my $binary = $sp_values->to_bin;
      is($binary, "");
    }
    {
      my $sp_values = $api->new_float_array([]);
      my $binary = $sp_values->to_bin;
      is($binary, "");
    }
    {
      my $sp_values = $api->new_double_array([]);
      my $binary = $sp_values->to_bin;
      is($binary, "");
    }
  }
    
  # to_bin(
  {
    {
      my $sp_values = $api->new_byte_array([1, 2, $BYTE_MAX]);
      my $binary = $sp_values->to_bin;
      
      my @values = unpack('c3', $binary);
      is_deeply(\@values, [1, 2, $BYTE_MAX]);
    }
    {
      my $sp_values = $api->new_short_array([1, 2, $SHORT_MAX]);
      my $binary = $sp_values->to_bin;
      
      my @values = unpack('s3', $binary);
      is_deeply(\@values, [1, 2, $SHORT_MAX]);
    }
    {
      my $sp_values = $api->new_int_array([1, 2, $INT_MAX]);
      my $binary = $sp_values->to_bin;
      
      my @values = unpack('l3', $binary);
      is_deeply(\@values, [1, 2, $INT_MAX]);
    }
    {
      my $sp_values = $api->new_long_array([1, 2, $LONG_MAX]);
      my $binary = $sp_values->to_bin;
      
      my @values = unpack('q3', $binary);
      is_deeply(\@values, [1, 2, $LONG_MAX]);
    }
    {
      my $sp_values = $api->new_float_array([1, 2, $FLOAT_PRECICE]);
      my $binary = $sp_values->to_bin;
      
      my @values = unpack('f3', $binary);
      is_deeply(\@values, [1, 2, $FLOAT_PRECICE]);
    }
    {
      my $sp_values = $api->new_double_array([1, 2, $DOUBLE_PRECICE]);
      my $binary = $sp_values->to_bin;
      
      my @values = unpack('d3', $binary);
      is_deeply(\@values, [1, 2, $DOUBLE_PRECICE]);
    }
  }

  # middle size array
  {
    my $length = 1_000_000;
    {
      my $binary = pack('l*', 1 .. $length);
      my $sp_values = $api->new_int_array_from_bin($binary);
      is($sp_values->length, $length);
    }
    {
      my $binary = pack('q*', 1 .. $length);
      my $sp_values = $api->new_long_array_from_bin($binary);
      is($sp_values->length, $length);
    }
    {
      my $binary = pack('f*', 1 .. $length);
      my $sp_values = $api->new_float_array_from_bin($binary);
      is($sp_values->length, $length);
    }
    {
      my $binary = pack('d*', 1 .. $length);
      my $sp_values = $api->new_double_array_from_bin($binary);
      is($sp_values->length, $length);
    }
    {
      my $binary = pack('f*', 1 .. $length);
      my $sp_values = $api->new_float_array_from_bin($binary);
      is($sp_values->length, $length);
    }
  }
}

# SPVM::BlessedObject::Array
{
  # get and set
  {
    {
      my $sp_values = $api->new_byte_array([0, 0]);
      $sp_values->set(1, $BYTE_MAX);
      is_deeply($sp_values->to_elems, [0, $BYTE_MAX]);
      my $value = $sp_values->get(1);
      is($value, $BYTE_MAX);
    }
    {
      my $sp_values = $api->new_short_array([0, 0]);
      $sp_values->set(1, $SHORT_MAX);
      is_deeply($sp_values->to_elems, [0, $SHORT_MAX]);
      my $value = $sp_values->get(1);
      is($value, $SHORT_MAX);
    }
    {
      my $sp_values = $api->new_int_array([0, 0]);
      $sp_values->set(1, $INT_MAX);
      is_deeply($sp_values->to_elems, [0, $INT_MAX]);
      my $value = $sp_values->get(1);
      is($value, $INT_MAX);
    }
    {
      my $sp_values = $api->new_long_array([0, 0]);
      $sp_values->set(1, $LONG_MAX);
      is_deeply($sp_values->to_elems, [0, $LONG_MAX]);
      my $value = $sp_values->get(1);
      is($value, $LONG_MAX);
    }
    {
      my $sp_values = $api->new_float_array([0, 0]);
      $sp_values->set(1, $FLOAT_PRECICE);
      is_deeply($sp_values->to_elems, [0, $FLOAT_PRECICE]);
      my $value = $sp_values->get(1);
      is($value, $FLOAT_PRECICE);
    }
    {
      my $sp_values = $api->new_double_array([0, 0]);
      $sp_values->set(1, $DOUBLE_PRECICE);
      is_deeply($sp_values->to_elems, [0, $DOUBLE_PRECICE]);
      my $value = $sp_values->get(1);
      is($value, $DOUBLE_PRECICE);
    }
  }
  
  # overload fallback
  {
    my $sp_values = $api->new_double_array([0, 0]);
    like("$sp_values", qr/PVM::BlessedObject::Array/);
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

# Call not defined method
{
  eval { SPVM::Int->not_defined_method };
  like($@, qr|The "not_defined_method" method in the "Int" class is not defined|);
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

# TODO

=pod

new_object_array_len
new_string_array_len

=cut

# All object is freed
my $end_memory_blocks_count = $api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);


done_testing;
