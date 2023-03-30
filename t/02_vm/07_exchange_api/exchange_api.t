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
my $FLOAT_MIN = POSIX::FLT_MIN();
my $DOUBLE_MIN = POSIX::DBL_MIN();
my $FLOAT_MAX = POSIX::FLT_MAX();
my $DOUBLE_MAX = POSIX::DBL_MAX();
my $UBYTE_MAX = 255;
my $USHORT_MAX = 65535;
my $UINT_MAX = 4294967295;
my $ULONG_MAX = 18446744073709551615;

my $api = SPVM::api();

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count();

# new_string
{
  # new_string - object type
  {
    my $spvm_string = $api->new_string("abc");
    is(ref $spvm_string, "SPVM::BlessedObject::String");
    is($spvm_string->__get_type_name, "string");
  }
  
  # new_string - scalar
  {
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
  }
  
  # new_string - undef
  {
    my $spvm_string = $api->new_string(undef);
    ok(!defined $spvm_string);
  }

  # new_string - SPVM::BlessedObject::String
  {
    my $spvm_string = $api->new_string("abc");
    my $spvm_string2 = $api->new_string($spvm_string);
    ok($spvm_string == $spvm_string);
  }
  
  # Excetpions
  {
    # new_string - reference
    {
      eval { $api->new_string([]) };
      like($@, qr/The \$string must be a non-reference scalar or a SPVM::BlessedObject::String object or undef/);
      like($@, qr|XS_SPVM__ExchangeAPI__xs_new_string at SPVM\.xs line \d+|);
    }
    # new_string - non-assignable
    {
      eval { $api->new_string($api->new_byte_array([1, 2, 3])) };
      like($@, qr/The \$string must be a non-reference scalar or a SPVM::BlessedObject::String object or undef/);
      like($@, qr|XS_SPVM__ExchangeAPI__xs_new_string at SPVM\.xs line \d+|);
    }
  }
  
  # Extra
  {
    # new_string - Argument decoded string, to_string, "" overload
    {
      my $spvm_string = $api->new_string("あいう");
      is($spvm_string->to_string, "あいう");
      is("$spvm_string", "あいう");
    }

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

# new_byte_array
{
  # new_byte_array - Return type
  {
    my $spvm_array = $api->new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
    is(ref $spvm_array, 'SPVM::BlessedObject::Array');
    is($spvm_array->__get_type_name, "byte[]");
  }
  
  # new_byte_array - array reference
  {
    my $spvm_array = $api->new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
    my $values = $spvm_array->to_elems;
    is_deeply($values, [1, $BYTE_MAX, $BYTE_MIN]);
  }
  
  # new_byte_array - undef
  {
    my $spvm_array = $api->new_byte_array(undef);
    ok(!defined $spvm_array);
  }

  # new_byte_array - SPVM::BlessedObject::Array
  {
    my $spvm_array1 = $api->new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
    my $spvm_array2 = $api->new_byte_array($spvm_array1);
    ok($spvm_array1 == $spvm_array2);
  }
  
  # new_byte_array - Exceptions
  {
    {
      eval { $api->new_byte_array({}); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the byte[] type or undef') >= 0);
    }
    {
      eval { $api->new_byte_array($api->new_string("abc")); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the byte[] type or undef') >= 0);
    }
  }
}

# new_byte_array_unsigned
{
  # new_byte_array_unsigned - Return type
  {
    my $spvm_array = $api->new_byte_array_unsigned([1, $UBYTE_MAX]);
    is(ref $spvm_array, 'SPVM::BlessedObject::Array');
    is($spvm_array->__get_type_name, "byte[]");
  }
  
  # new_byte_array_unsigned - array reference
  {
    my $spvm_array = $api->new_byte_array_unsigned([0, $UBYTE_MAX]);
    my $bin = $spvm_array->to_bin;
    is_deeply([unpack 'C*', $bin], [0, $UBYTE_MAX]);
  }
  
  # new_byte_array_unsigned - undef
  {
    my $spvm_array = $api->new_byte_array_unsigned(undef);
    ok(!defined $spvm_array);
  }

  # new_byte_array_unsigned - SPVM::BlessedObject::Array
  {
    my $spvm_array1 = $api->new_byte_array_unsigned([1, $UBYTE_MAX]);
    my $spvm_array2 = $api->new_byte_array_unsigned($spvm_array1);
    ok($spvm_array1 == $spvm_array2);
  }
  
  # new_byte_array_unsigned - Exceptions
  {
    {
      eval { $api->new_byte_array_unsigned({}); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the byte[] type or undef') >= 0);
    }
    {
      eval { $api->new_byte_array_unsigned($api->new_string("abc")); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the byte[] type or undef') >= 0);
    }
  }
}

# new_byte_array_len
{
  # new_byte_array_len - Return type
  {
    my $spvm_array = $api->new_byte_array_len(3);
    is(ref $spvm_array, 'SPVM::BlessedObject::Array');
    is($spvm_array->__get_type_name, "byte[]");
  }
  
  # new_byte_array_len - Length 3
  {
    my $spvm_array = $api->new_byte_array_len(3);
    my $values = $spvm_array->to_elems;
    is_deeply($values, [0, 0, 0]);
  }
  
  # new_byte_array_len - Length 0
  {
    my $spvm_array = $api->new_byte_array_len(0);
    my $values = $spvm_array->to_elems;
    is_deeply($values, []);
  }
  
  # Exceptions
  {
    eval { $api->new_byte_array_len(-1); };
    ok(index($@, 'The $length must be greater than or equal to 0') >= 0);
  }
}

# new_byte_array_from_bin
{
  # new_byte_array_from_bin - Return type
  {
    my $binary = pack('c*', 97, 98, $BYTE_MAX);
    my $spvm_array = $api->new_byte_array_from_bin($binary);
    is(ref $spvm_array, 'SPVM::BlessedObject::Array');
    is($spvm_array->__get_type_name, "byte[]");
  }
  
  # new_byte_array_from_bin - binary signed
  {
    my $binary = pack('c*', 97, 98, $BYTE_MAX);
    my $spvm_array = $api->new_byte_array_from_bin($binary);
    my $values = $spvm_array->to_elems;
    is_deeply($values, [97, 98, $BYTE_MAX]);
  }
  
  # new_byte_array_from_bin - binary unsigned
  {
    my $binary = pack('C*', 97, 98, $UBYTE_MAX);
    my $spvm_array = $api->new_byte_array_from_bin($binary);
    my $values = $spvm_array->to_elems;
    is_deeply($values, [97, 98, -1]);
  }
  
  # new_byte_array_from_bin - Exceptions
  {
    eval { my $spvm_array = $api->new_byte_array_from_bin(undef); };
    ok(index($@, 'The $binary must be defined') >= 0);
  }
  
  # Extra
  {
    {
      my $binary = "abc";
      my $spvm_array = $api->new_byte_array_from_bin("abc");
      my $values = $spvm_array->to_elems;
      is_deeply($values, [ord("a"), ord("b"), ord("c")]);
    }
    
    {
      my $binary = "あ";
      utf8::encode($binary);
      my $spvm_array = $api->new_byte_array_from_bin($binary);
      my $binary_ret = $spvm_array->to_bin;
      is($binary_ret, $binary);
    }
    
    {
      my $spvm_array = $api->new_byte_array_from_bin("\xFF\xFE");
      is($spvm_array->[0], -1);
      is($spvm_array->[1], -2);
    }
  }
}

# new_short_array
{
  # new_short_array - Return type
  {
    my $spvm_array = $api->new_short_array([1, $SHORT_MAX, $SHORT_MIN]);
    is(ref $spvm_array, 'SPVM::BlessedObject::Array');
    is($spvm_array->__get_type_name, "short[]");
  }
  
  # new_short_array - array reference
  {
    my $spvm_array = $api->new_short_array([1, $SHORT_MAX, $SHORT_MIN]);
    my $values = $spvm_array->to_elems;
    is_deeply($values, [1, $SHORT_MAX, $SHORT_MIN]);
  }
  
  # new_short_array - undef
  {
    my $spvm_array = $api->new_short_array(undef);
    ok(!defined $spvm_array);
  }

  # new_short_array - SPVM::BlessedObject::Array
  {
    my $spvm_array1 = $api->new_short_array([1, $SHORT_MAX, $SHORT_MIN]);
    my $spvm_array2 = $api->new_short_array($spvm_array1);
    ok($spvm_array1 == $spvm_array2);
  }
  
  # new_short_array - Exceptions
  {
    {
      eval { $api->new_short_array({}); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the short[] type or undef') >= 0);
    }
    {
      eval { $api->new_short_array($api->new_string("abc")); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the short[] type or undef') >= 0);
    }
  }
}

# new_short_array_unsigned
{
  # new_short_array_unsigned - Return type
  {
    my $spvm_array = $api->new_short_array_unsigned([1, $USHORT_MAX]);
    is(ref $spvm_array, 'SPVM::BlessedObject::Array');
    is($spvm_array->__get_type_name, "short[]");
  }
  
  # new_short_array_unsigned - array reference
  {
    my $spvm_array = $api->new_short_array_unsigned([0, $USHORT_MAX]);
    my $bin = $spvm_array->to_bin;
    is_deeply([unpack 'S*', $bin], [0, $USHORT_MAX]);
  }
  
  # new_short_array_unsigned - undef
  {
    my $spvm_array = $api->new_short_array_unsigned(undef);
    ok(!defined $spvm_array);
  }

  # new_short_array_unsigned - SPVM::BlessedObject::Array
  {
    my $spvm_array1 = $api->new_short_array_unsigned([1, $USHORT_MAX]);
    my $spvm_array2 = $api->new_short_array_unsigned($spvm_array1);
    ok($spvm_array1 == $spvm_array2);
  }
  
  # new_short_array_unsigned - Exceptions
  {
    {
      eval { $api->new_short_array_unsigned({}); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the short[] type or undef') >= 0);
    }
    {
      eval { $api->new_short_array_unsigned($api->new_string("abc")); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the short[] type or undef') >= 0);
    }
  }
}

# new_short_array_len
{
  # new_short_array_len - Return type
  {
    my $spvm_array = $api->new_short_array_len(3);
    is(ref $spvm_array, 'SPVM::BlessedObject::Array');
    is($spvm_array->__get_type_name, "short[]");
  }
  
  # new_short_array_len - Length 3
  {
    my $spvm_array = $api->new_short_array_len(3);
    my $values = $spvm_array->to_elems;
    is_deeply($values, [0, 0, 0]);
  }
  
  # new_short_array_len - Length 0
  {
    my $spvm_array = $api->new_short_array_len(0);
    my $values = $spvm_array->to_elems;
    is_deeply($values, []);
  }
  
  # Exceptions
  {
    eval { $api->new_short_array_len(-1); };
    ok(index($@, 'The $length must be greater than or equal to 0') >= 0);
  }
}

# new_short_array_from_bin
{
  # new_short_array_from_bin - Return type
  {
    my $binary = pack('s*', 97, 98, $SHORT_MAX);
    my $spvm_array = $api->new_short_array_from_bin($binary);
    is(ref $spvm_array, 'SPVM::BlessedObject::Array');
    is($spvm_array->__get_type_name, "short[]");
  }
  
  # new_short_array_from_bin - binary signed
  {
    my $binary = pack('s*', 97, 98, $SHORT_MAX);
    my $spvm_array = $api->new_short_array_from_bin($binary);
    my $values = $spvm_array->to_elems;
    is_deeply($values, [97, 98, $SHORT_MAX]);
  }
  
  # new_short_array_from_bin - binary unsigned
  {
    my $binary = pack('S*', 97, 98, $USHORT_MAX);
    my $spvm_array = $api->new_short_array_from_bin($binary);
    my $values = $spvm_array->to_elems;
    is_deeply($values, [97, 98, -1]);
  }
  
  # new_short_array_from_bin - Exceptions
  {
    # undef
    {
      eval { $api->new_short_array_from_bin(undef); };
      ok(index($@, 'The $binary must be defined') >= 0);
    }
    
    # Non-divisible
    {
      eval { $api->new_short_array_from_bin("abc"); };
      ok(index($@, 'The length of the $binary must be divisible by 2') >= 0);
    }
  }
}

# new_int_array
{
  # new_int_array - Return type
  {
    my $spvm_array = $api->new_int_array([1, $INT_MAX, $INT_MIN]);
    is(ref $spvm_array, 'SPVM::BlessedObject::Array');
    is($spvm_array->__get_type_name, "int[]");
  }
  
  # new_int_array - array reference
  {
    my $spvm_array = $api->new_int_array([1, $INT_MAX, $INT_MIN]);
    my $values = $spvm_array->to_elems;
    is_deeply($values, [1, $INT_MAX, $INT_MIN]);
  }
  
  # new_int_array - undef
  {
    my $spvm_array = $api->new_int_array(undef);
    ok(!defined $spvm_array);
  }

  # new_int_array - SPVM::BlessedObject::Array
  {
    my $spvm_array1 = $api->new_int_array([1, $INT_MAX, $INT_MIN]);
    my $spvm_array2 = $api->new_int_array($spvm_array1);
    ok($spvm_array1 == $spvm_array2);
  }
  
  # new_int_array - Exceptions
  {
    {
      eval { $api->new_int_array({}); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the int[] type or undef') >= 0);
    }
    {
      eval { $api->new_int_array($api->new_string("abc")); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the int[] type or undef') >= 0);
    }
  }
}

# new_int_array_unsigned
{
  # new_int_array_unsigned - Return type
  {
    my $spvm_array = $api->new_int_array_unsigned([1, $UINT_MAX]);
    is(ref $spvm_array, 'SPVM::BlessedObject::Array');
    is($spvm_array->__get_type_name, "int[]");
  }
  
  # new_int_array_unsigned - array reference
  {
    my $spvm_array = $api->new_int_array_unsigned([0, $UINT_MAX]);
    my $bin = $spvm_array->to_bin;
    is_deeply([unpack 'L*', $bin], [0, $UINT_MAX]);
  }
  
  # new_int_array_unsigned - undef
  {
    my $spvm_array = $api->new_int_array_unsigned(undef);
    ok(!defined $spvm_array);
  }

  # new_int_array_unsigned - SPVM::BlessedObject::Array
  {
    my $spvm_array1 = $api->new_int_array_unsigned([1, $UINT_MAX]);
    my $spvm_array2 = $api->new_int_array_unsigned($spvm_array1);
    ok($spvm_array1 == $spvm_array2);
  }
  
  # new_int_array_unsigned - Exceptions
  {
    {
      eval { $api->new_int_array_unsigned({}); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the int[] type or undef') >= 0);
    }
    {
      eval { $api->new_int_array_unsigned($api->new_string("abc")); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the int[] type or undef') >= 0);
    }
  }
}

# new_int_array_len
{
  # new_int_array_len - Return type
  {
    my $spvm_array = $api->new_int_array_len(3);
    is(ref $spvm_array, 'SPVM::BlessedObject::Array');
    is($spvm_array->__get_type_name, "int[]");
  }
  
  # new_int_array_len - Length 3
  {
    my $spvm_array = $api->new_int_array_len(3);
    my $values = $spvm_array->to_elems;
    is_deeply($values, [0, 0, 0]);
  }
  
  # new_int_array_len - Length 0
  {
    my $spvm_array = $api->new_int_array_len(0);
    my $values = $spvm_array->to_elems;
    is_deeply($values, []);
  }
  
  # Exceptions
  {
    eval { $api->new_int_array_len(-1); };
    ok(index($@, 'The $length must be greater than or equal to 0') >= 0);
  }
}

# new_int_array_from_bin
{
  # new_int_array_from_bin - Return type
  {
    my $binary = pack('l*', 97, 98, $INT_MAX);
    my $spvm_array = $api->new_int_array_from_bin($binary);
    is(ref $spvm_array, 'SPVM::BlessedObject::Array');
    is($spvm_array->__get_type_name, "int[]");
  }
  
  # new_int_array_from_bin - binary signed
  {
    my $binary = pack('l*', 97, 98, $INT_MAX);
    my $spvm_array = $api->new_int_array_from_bin($binary);
    my $values = $spvm_array->to_elems;
    is_deeply($values, [97, 98, $INT_MAX]);
  }
  
  # new_int_array_from_bin - binary unsigned
  {
    my $binary = pack('L*', 97, 98, $UINT_MAX);
    my $spvm_array = $api->new_int_array_from_bin($binary);
    my $values = $spvm_array->to_elems;
    is_deeply($values, [97, 98, -1]);
  }
  
  # new_int_array_from_bin - Exceptions
  {
    # undef
    {
      eval { $api->new_int_array_from_bin(undef); };
      ok(index($@, 'The $binary must be defined') >= 0);
    }
    
    # Non-divisible
    {
      eval { $api->new_int_array_from_bin("abcde"); };
      ok(index($@, 'The length of the $binary must be divisible by 4') >= 0);
    }
  }
}

# new_long_array
{
  # new_long_array - Return type
  {
    my $spvm_array = $api->new_long_array([1, $LONG_MAX, $LONG_MIN]);
    is(ref $spvm_array, 'SPVM::BlessedObject::Array');
    is($spvm_array->__get_type_name, "long[]");
  }
  
  # new_long_array - array reference
  {
    my $spvm_array = $api->new_long_array([1, $LONG_MAX, $LONG_MIN]);
    my $values = $spvm_array->to_elems;
    is_deeply($values, [1, $LONG_MAX, $LONG_MIN]);
  }
  
  # new_long_array - undef
  {
    my $spvm_array = $api->new_long_array(undef);
    ok(!defined $spvm_array);
  }

  # new_long_array - SPVM::BlessedObject::Array
  {
    my $spvm_array1 = $api->new_long_array([1, $LONG_MAX, $LONG_MIN]);
    my $spvm_array2 = $api->new_long_array($spvm_array1);
    ok($spvm_array1 == $spvm_array2);
  }
  
  # new_long_array - Exceptions
  {
    {
      eval { $api->new_long_array({}); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the long[] type or undef') >= 0);
    }
    {
      eval { $api->new_long_array($api->new_string("abc")); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the long[] type or undef') >= 0);
    }
  }
}

# new_long_array_unsigned
{
  # new_long_array_unsigned - Return type
  {
    my $spvm_array = $api->new_long_array_unsigned([1, $ULONG_MAX]);
    is(ref $spvm_array, 'SPVM::BlessedObject::Array');
    is($spvm_array->__get_type_name, "long[]");
  }
  
  # new_long_array_unsigned - array reference
  {
    my $spvm_array = $api->new_long_array_unsigned([0, $ULONG_MAX]);
    my $bin = $spvm_array->to_bin;
    is_deeply([unpack 'Q*', $bin], [0, $ULONG_MAX]);
  }
  
  # new_long_array_unsigned - undef
  {
    my $spvm_array = $api->new_long_array_unsigned(undef);
    ok(!defined $spvm_array);
  }

  # new_long_array_unsigned - SPVM::BlessedObject::Array
  {
    my $spvm_array1 = $api->new_long_array_unsigned([1, $ULONG_MAX]);
    my $spvm_array2 = $api->new_long_array_unsigned($spvm_array1);
    ok($spvm_array1 == $spvm_array2);
  }
  
  # new_long_array_unsigned - Exceptions
  {
    {
      eval { $api->new_long_array_unsigned({}); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the long[] type or undef') >= 0);
    }
    {
      eval { $api->new_long_array_unsigned($api->new_string("abc")); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the long[] type or undef') >= 0);
    }
  }
}

# new_long_array_len
{
  # new_long_array_len - Return type
  {
    my $spvm_array = $api->new_long_array_len(3);
    is(ref $spvm_array, 'SPVM::BlessedObject::Array');
    is($spvm_array->__get_type_name, "long[]");
  }
  
  # new_long_array_len - Length 3
  {
    my $spvm_array = $api->new_long_array_len(3);
    my $values = $spvm_array->to_elems;
    is_deeply($values, [0, 0, 0]);
  }
  
  # new_long_array_len - Length 0
  {
    my $spvm_array = $api->new_long_array_len(0);
    my $values = $spvm_array->to_elems;
    is_deeply($values, []);
  }
  
  # Exceptions
  {
    eval { $api->new_long_array_len(-1); };
    ok(index($@, 'The $length must be greater than or equal to 0') >= 0);
  }
}

# new_long_array_from_bin
{
  my $binary = pack('q*', 97, 98, $LONG_MAX);
  my $spvm_array = $api->new_long_array_from_bin($binary);
  ok(SPVM::TestCase::ExchangeAPI->spvm_new_long_array_binary_pack($spvm_array));
}

# new_float_array
{
  # new_float_array - Return type
  {
    my $spvm_array = $api->new_float_array([1, $FLOAT_MAX, $FLOAT_MIN]);
    is(ref $spvm_array, 'SPVM::BlessedObject::Array');
    is($spvm_array->__get_type_name, "float[]");
  }
  
  # new_float_array - array reference
  {
    my $spvm_array = $api->new_float_array([1, $FLOAT_MAX, $FLOAT_MIN]);
    my $values = $spvm_array->to_elems;
    is_deeply($values, [1, $FLOAT_MAX, $FLOAT_MIN]);
  }
  
  # new_float_array - undef
  {
    my $spvm_array = $api->new_float_array(undef);
    ok(!defined $spvm_array);
  }

  # new_float_array - SPVM::BlessedObject::Array
  {
    my $spvm_array1 = $api->new_float_array([1, $FLOAT_MAX, $FLOAT_MIN]);
    my $spvm_array2 = $api->new_float_array($spvm_array1);
    ok($spvm_array1 == $spvm_array2);
  }
  
  # new_float_array - Exceptions
  {
    {
      eval { $api->new_float_array({}); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the float[] type or undef') >= 0);
    }
    {
      eval { $api->new_float_array($api->new_string("abc")); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the float[] type or undef') >= 0);
    }
  }
}

# new_float_array_len
{
  # new_float_array_len - Return type
  {
    my $spvm_array = $api->new_float_array_len(3);
    is(ref $spvm_array, 'SPVM::BlessedObject::Array');
    is($spvm_array->__get_type_name, "float[]");
  }
  
  # new_float_array_len - Length 3
  {
    my $spvm_array = $api->new_float_array_len(3);
    my $values = $spvm_array->to_elems;
    is_deeply($values, [0, 0, 0]);
  }
  
  # new_float_array_len - Length 0
  {
    my $spvm_array = $api->new_float_array_len(0);
    my $values = $spvm_array->to_elems;
    is_deeply($values, []);
  }
  
  # Exceptions
  {
    eval { $api->new_float_array_len(-1); };
    ok(index($@, 'The $length must be greater than or equal to 0') >= 0);
  }
}

# new_float_array_from_bin
{
  my $binary = pack('f*', 97, 98, $FLOAT_PRECICE);
  my $spvm_array = $api->new_float_array_from_bin($binary);
  ok(SPVM::TestCase::ExchangeAPI->spvm_new_float_array_binary_pack($spvm_array));
}

# new_double_array
{
  # new_double_array - Return type
  {
    my $spvm_array = $api->new_double_array([1, $DOUBLE_MAX, $DOUBLE_MIN]);
    is(ref $spvm_array, 'SPVM::BlessedObject::Array');
    is($spvm_array->__get_type_name, "double[]");
  }
  
  # new_double_array - array reference
  {
    my $spvm_array = $api->new_double_array([1, $DOUBLE_MAX, $DOUBLE_MIN]);
    my $values = $spvm_array->to_elems;
    is_deeply($values, [1, $DOUBLE_MAX, $DOUBLE_MIN]);
  }
  
  # new_double_array - undef
  {
    my $spvm_array = $api->new_double_array(undef);
    ok(!defined $spvm_array);
  }

  # new_double_array - SPVM::BlessedObject::Array
  {
    my $spvm_array1 = $api->new_double_array([1, $DOUBLE_MAX, $DOUBLE_MIN]);
    my $spvm_array2 = $api->new_double_array($spvm_array1);
    ok($spvm_array1 == $spvm_array2);
  }
  
  # new_double_array - Exceptions
  {
    {
      eval { $api->new_double_array({}); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the double[] type or undef') >= 0);
    }
    {
      eval { $api->new_double_array($api->new_string("abc")); };
      ok(index($@, 'The $array must be an array reference or a SPVM::BlessedObject::Array object of the double[] type or undef') >= 0);
    }
  }
}

# new_double_array_len
{
  # new_double_array_len - Return type
  {
    my $spvm_array = $api->new_double_array_len(3);
    is(ref $spvm_array, 'SPVM::BlessedObject::Array');
    is($spvm_array->__get_type_name, "double[]");
  }
  
  # new_double_array_len - Length 3
  {
    my $spvm_array = $api->new_double_array_len(3);
    my $values = $spvm_array->to_elems;
    is_deeply($values, [0, 0, 0]);
  }
  
  # new_double_array_len - Length 0
  {
    my $spvm_array = $api->new_double_array_len(0);
    my $values = $spvm_array->to_elems;
    is_deeply($values, []);
  }
  
  # Exceptions
  {
    eval { $api->new_double_array_len(-1); };
    ok(index($@, 'The $length must be greater than or equal to 0') >= 0);
  }
}

# new_double_array_from_bin
{
  my $binary = pack('d*', 97, 98, $DOUBLE_PRECICE);
  my $spvm_array = $api->new_double_array_from_bin($binary);
  ok(SPVM::TestCase::ExchangeAPI->spvm_new_double_array_binary_pack($spvm_array));
}

# new_mulnum_array_from_bin
{
  # new_mulnum_array_from_bin - byte
  {
    my $binary = pack('c9', ($BYTE_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_array = $api->new_mulnum_array_from_bin("TestCase::Point_3b[]", $binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_byte($spvm_array));
    my $out_bin = $spvm_array->to_bin;
    is_deeply($out_bin, $binary);
  }

  # new_mulnum_array_from_bin - short
  {
    my $binary = pack('s9', ($SHORT_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_array = $api->new_mulnum_array_from_bin("TestCase::Point_3s[]", $binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_short($spvm_array));
    my $out_bin = $spvm_array->to_bin;
    is_deeply($out_bin, $binary);
  }
  
  # new_mulnum_array_from_bin - int
  {
    my $binary = pack('l9', ($INT_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_array = $api->new_mulnum_array_from_bin("TestCase::Point_3i[]", $binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_int($spvm_array));
    my $out_bin = $spvm_array->to_bin;
    is_deeply($out_bin, $binary);
  }
  # new_mulnum_array_from_bin - long
  {
    my $binary = pack('q9', ($LONG_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_array = $api->new_mulnum_array_from_bin("TestCase::Point_3l[]", $binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_long($spvm_array));
    my $out_bin = $spvm_array->to_bin;
    is_deeply($out_bin, $binary);
  }
  # new_mulnum_array_from_bin - float
  {
    my $binary = pack('f9', ($FLOAT_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_array = $api->new_mulnum_array_from_bin("TestCase::Point_3f[]", $binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_float($spvm_array));
    my $out_bin = $spvm_array->to_bin;
    is_deeply($out_bin, $binary);
  }
  # new_mulnum_array_from_bin - double
  {
    my $binary = pack('d9', ($DOUBLE_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_array = $api->new_mulnum_array_from_bin("TestCase::Point_3d[]", $binary);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_binary_double($spvm_array));
    my $out_bin = $spvm_array->to_bin;
    is_deeply($out_bin, $binary);
  }

  # new_mulnum_array_from_bin - double
  {
    my $binary = pack('d8', ($DOUBLE_MIN, 1, 2), (3, 4, 5), (6, 7));
    eval {
      $api->new_mulnum_array_from_bin("TestCase::Point_3d[]", $binary);
    };
    ok($@);
  }
}

# new_object_array
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
    my $spvm_array = $api->new_mulnum_array("TestCase::Point_3b[]", $values);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_byte($spvm_array));
    my $out_values = $spvm_array->to_elems;
    is_deeply($out_values, $values);
  }

  # new_mulnum_array - short
  {
    my $values = [
      {x => $SHORT_MIN, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_array = $api->new_mulnum_array("TestCase::Point_3s[]", $values);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_short($spvm_array));
    my $out_values = $spvm_array->to_elems;
    is_deeply($out_values, $values);
  }

  # new_mulnum_array - int
  {
    my $values = [
      {x => $INT_MIN, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_array = $api->new_mulnum_array("TestCase::Point_3i[]", $values);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_int($spvm_array));
    my $out_values = $spvm_array->to_elems;
    is_deeply($out_values, $values);
  }

  # new_mulnum_array - long
  {
    my $values = [
      {x => $LONG_MIN, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_array = $api->new_mulnum_array("TestCase::Point_3l[]", $values);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_long($spvm_array));
    my $out_values = $spvm_array->to_elems;
    is_deeply($out_values, $values);
  }

  # new_mulnum_array - float
  {
    my $values = [
      {x => $FLOAT_MIN, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_array = $api->new_mulnum_array("TestCase::Point_3f[]", $values);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_float($spvm_array));
    my $out_values = $spvm_array->to_elems;
    is_deeply($out_values, $values);
  }

  # new_mulnum_array - double
  {
    my $values = [
      {x => $DOUBLE_MIN, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_array = $api->new_mulnum_array("TestCase::Point_3d[]", $values);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_mulnum_array_double($spvm_array));
    my $out_values = $spvm_array->to_elems;
    is_deeply($out_values, $values);
  }
}

# new_muldim_array
{
  # element byte array
  {
    my $object1 = $api->new_byte_array([1, 2, 3]);
    my $object2 = $api->new_byte_array([4, 5, 6]);
    my $oarray = $api->new_muldim_array("byte[][]", [$object1, $object2]);

    ok(SPVM::TestCase::ExchangeAPI->spvm_new_object_array_len_element_byte_array($oarray));
    
    my $oarray_out = $oarray->to_elems;
    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element short array
  {
    my $object1 = $api->new_short_array([1, 2, 3]);
    my $object2 = $api->new_short_array([4, 5, 6]);
    my $oarray = $api->new_muldim_array("short[][]", [$object1, $object2]);

    ok(SPVM::TestCase::ExchangeAPI->spvm_new_object_array_len_element_short_array($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element int array
  {
    my $object1 = $api->new_int_array([1, 2, 3]);
    my $object2 = $api->new_int_array([4, 5, 6]);
    my $oarray = $api->new_muldim_array("int[][]", [$object1, $object2]);

    ok(SPVM::TestCase::ExchangeAPI->spvm_new_object_array_len_element_int_array($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element long array
  {
    my $object1 = $api->new_long_array([1, 2, 3]);
    my $object2 = $api->new_long_array([4, 5, 6]);
    my $oarray = $api->new_muldim_array("long[][]", [$object1, $object2]);
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_object_array_len_element_long_array($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element float array
  {
    my $object1 = $api->new_float_array([1, 2, 3]);
    my $object2 = $api->new_float_array([4, 5, 6]);
    my $oarray = $api->new_muldim_array("float[][]", [$object1, $object2]);

    ok(SPVM::TestCase::ExchangeAPI->spvm_new_object_array_len_element_float_array($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }

  # element double array
  {
    my $object1 = $api->new_double_array([1, 2, 3]);
    my $object2 = $api->new_double_array([4, 5, 6]);
    my $oarray = $api->new_muldim_array("double[][]", [$object1, $object2]);
    
    ok(SPVM::TestCase::ExchangeAPI->spvm_new_object_array_len_element_double_array($oarray));
    
    my $oarray_out = $oarray->to_elems;

    is_deeply($oarray_out->[0]->to_elems, [1, 2, 3]);
    is_deeply($oarray_out->[1]->to_elems, [4, 5, 6]);
  }
}

# get_exception
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

# new_options
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

# SPVM::BlessedObject
{
  # SPVM::BlessedObject - __get_type_name
  {
    # string
    {
      my $blessed_object = $api->new_string("abc");
      isa_ok($blessed_object, "SPVM::BlessedObject");
      my $type_name = $blessed_object->__get_type_name;
      is($type_name, "string");
    }

    # byte[]
    {
      my $blessed_object = $api->new_byte_array([1, 2, 3]);
      isa_ok($blessed_object, "SPVM::BlessedObject");
      my $type_name = $blessed_object->__get_type_name;
      is($type_name, "byte[]");
    }

    # Point
    {
      my $blessed_object = SPVM::Point->new;
      isa_ok($blessed_object, "SPVM::BlessedObject");
      my $type_name = $blessed_object->__get_type_name;
      is($type_name, "Point");
    }
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
    
    # stringify SPVM object
    {
      my $minimal = SPVM::TestCase::Minimal->new;
      
      like("$minimal", qr/SPVM::BlessedObject::Class/);
    }
    
    # ref SPVM object
    {
      my $minimal = SPVM::TestCase::Minimal->new;
      
      is(ref $minimal, 'SPVM::BlessedObject::Class');
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
    my $blessed_object_array = my $spvm_array = $api->new_int_array([0, 0]);
    is(ref $blessed_object_array, "SPVM::BlessedObject::Array");
  }
  
  # length
  {
    {
      my $spvm_array = $api->new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
      my $length = $spvm_array->length;
      is($length, 3);
    }
    {
      my $spvm_array = $api->new_short_array([1, $SHORT_MAX, $SHORT_MIN]);
      my $length = $spvm_array->length;
      is($length, 3);
    }
    {
      my $spvm_array = $api->new_int_array([1, $INT_MAX, $INT_MIN]);
      my $length = $spvm_array->length;
      is($length, 3);
    }
    {
      my $spvm_array = $api->new_long_array([1, $LONG_MAX, $LONG_MIN]);
      my $length = $spvm_array->length;
      is($length, 3);
    }
  }

  # get and set
  {
    {
      my $spvm_array = $api->new_byte_array([0, 0]);
      $spvm_array->set(1, $BYTE_MAX);
      is_deeply($spvm_array->to_elems, [0, $BYTE_MAX]);
      my $value = $spvm_array->get(1);
      is($value, $BYTE_MAX);
    }
    {
      my $spvm_array = $api->new_short_array([0, 0]);
      $spvm_array->set(1, $SHORT_MAX);
      is_deeply($spvm_array->to_elems, [0, $SHORT_MAX]);
      my $value = $spvm_array->get(1);
      is($value, $SHORT_MAX);
    }
    {
      my $spvm_array = $api->new_int_array([0, 0]);
      $spvm_array->set(1, $INT_MAX);
      is_deeply($spvm_array->to_elems, [0, $INT_MAX]);
      my $value = $spvm_array->get(1);
      is($value, $INT_MAX);
    }
    {
      my $spvm_array = $api->new_long_array([0, 0]);
      $spvm_array->set(1, $LONG_MAX);
      is_deeply($spvm_array->to_elems, [0, $LONG_MAX]);
      my $value = $spvm_array->get(1);
      is($value, $LONG_MAX);
    }
    {
      my $spvm_array = $api->new_float_array([0, 0]);
      $spvm_array->set(1, $FLOAT_PRECICE);
      is_deeply($spvm_array->to_elems, [0, $FLOAT_PRECICE]);
      my $value = $spvm_array->get(1);
      is($value, $FLOAT_PRECICE);
    }
    {
      my $spvm_array = $api->new_double_array([0, 0]);
      $spvm_array->set(1, $DOUBLE_PRECICE);
      is_deeply($spvm_array->to_elems, [0, $DOUBLE_PRECICE]);
      my $value = $spvm_array->get(1);
      is($value, $DOUBLE_PRECICE);
    }
  }
  
  # overload fallback
  {
    my $spvm_array = $api->new_double_array([0, 0]);
    like("$spvm_array", qr/SPVM::BlessedObject::Array/);
  }
  
  # to_elems
  {
    # to_elems - byte[]
    {
      my $spvm_array = $api->new_byte_array([1, $BYTE_MAX, $BYTE_MIN]);
      my $values = $spvm_array->to_elems;
      is_deeply($values, [1, $BYTE_MAX, $BYTE_MIN]);
    }
    # to_elems - short[]
    {
      my $spvm_array = $api->new_short_array([1, $SHORT_MAX, $SHORT_MIN]);
      my $values = $spvm_array->to_elems;
      is_deeply($values, [1, $SHORT_MAX, $SHORT_MIN]);
    }
    
    # to_elems - int[]
    {
      my $spvm_array = $api->new_int_array([1, $INT_MAX, $INT_MIN]);
      my $values = $spvm_array->to_elems;
      is_deeply($values, [1, $INT_MAX, $INT_MIN]);
    }
    # to_elems - long[]
    {
      my $spvm_array = $api->new_long_array([1, $LONG_MAX, $LONG_MIN]);
      my $values = $spvm_array->to_elems;
      is_deeply($values, [1, $LONG_MAX, $LONG_MIN]);
    }
    # to_elems - float[]
    {
      my $spvm_array = $api->new_float_array([0.5, $FLOAT_MAX, $FLOAT_MIN]);
      my $values = $spvm_array->to_elems;
      is_deeply($values, [0.5, $FLOAT_MAX, $FLOAT_MIN]);
    }
    # to_elems - double[]
    {
      my $spvm_array = $api->new_double_array([0.5, $DOUBLE_MAX, $DOUBLE_MIN]);
      my $values = $spvm_array->to_elems;
      is_deeply($values, [0.5, $DOUBLE_MAX, $DOUBLE_MIN]);
    }
    # to_elems - string[]
    {
      my $spvm_array = $api->new_string_array(["あ", "い"]);
      my $values = $spvm_array->to_elems;
      is(ref $values->[0], "SPVM::BlessedObject::String");
      is($values->[0], "あ");
      is($values->[1], "い");
      is(scalar @$values, 2);
    }
  }
  
  # to_bin
  {
    {
      my $spvm_array = $api->new_byte_array([1, 2, $BYTE_MAX]);
      my $binary = $spvm_array->to_bin;
      
      my @values = unpack('c3', $binary);
      is_deeply(\@values, [1, 2, $BYTE_MAX]);
    }
    {
      my $spvm_array = $api->new_short_array([1, 2, $SHORT_MAX]);
      my $binary = $spvm_array->to_bin;
      
      my @values = unpack('s3', $binary);
      is_deeply(\@values, [1, 2, $SHORT_MAX]);
    }
    {
      my $spvm_array = $api->new_int_array([1, 2, $INT_MAX]);
      my $binary = $spvm_array->to_bin;
      
      my @values = unpack('l3', $binary);
      is_deeply(\@values, [1, 2, $INT_MAX]);
    }
    {
      my $spvm_array = $api->new_long_array([1, 2, $LONG_MAX]);
      my $binary = $spvm_array->to_bin;
      
      my @values = unpack('q3', $binary);
      is_deeply(\@values, [1, 2, $LONG_MAX]);
    }
    {
      my $spvm_array = $api->new_float_array([1, 2, $FLOAT_PRECICE]);
      my $binary = $spvm_array->to_bin;
      
      my @values = unpack('f3', $binary);
      is_deeply(\@values, [1, 2, $FLOAT_PRECICE]);
    }
    {
      my $spvm_array = $api->new_double_array([1, 2, $DOUBLE_PRECICE]);
      my $binary = $spvm_array->to_bin;
      
      my @values = unpack('d3', $binary);
      is_deeply(\@values, [1, 2, $DOUBLE_PRECICE]);
    }
    
    # to_bin 0 length
    {
      {
        my $spvm_array = $api->new_byte_array([]);
        my $binary = $spvm_array->to_bin;
        is($binary, "");
      }
      {
        my $spvm_array = $api->new_short_array([]);
        my $binary = $spvm_array->to_bin;
        is($binary, "");
      }
      {
        my $spvm_array = $api->new_int_array([]);
        my $binary = $spvm_array->to_bin;
        is($binary, "");
      }
      {
        my $spvm_array = $api->new_long_array([]);
        my $binary = $spvm_array->to_bin;
        is($binary, "");
      }
      {
        my $spvm_array = $api->new_float_array([]);
        my $binary = $spvm_array->to_bin;
        is($binary, "");
      }
      {
        my $spvm_array = $api->new_double_array([]);
        my $binary = $spvm_array->to_bin;
        is($binary, "");
      }
    }
      
    # middle size array
    {
      my $length = 1_000_000;
      {
        my $binary = pack('l*', 1 .. $length);
        my $spvm_array = $api->new_int_array_from_bin($binary);
        is($spvm_array->length, $length);
      }
      {
        my $binary = pack('q*', 1 .. $length);
        my $spvm_array = $api->new_long_array_from_bin($binary);
        is($spvm_array->length, $length);
      }
      {
        my $binary = pack('f*', 1 .. $length);
        my $spvm_array = $api->new_float_array_from_bin($binary);
        is($spvm_array->length, $length);
      }
      {
        my $binary = pack('d*', 1 .. $length);
        my $spvm_array = $api->new_double_array_from_bin($binary);
        is($spvm_array->length, $length);
      }
      {
        my $binary = pack('f*', 1 .. $length);
        my $spvm_array = $api->new_float_array_from_bin($binary);
        is($spvm_array->length, $length);
      }
    }
  }

  
  # to_strings
  {
    # to_strings - string[]
    {
      my $spvm_array = $api->new_object_array('Point[]', [SPVM::Point->new(1, 2), SPVM::Point->new(3, 4)]);
      my $values = $spvm_array->to_strings;
      is($values->[0], "(1,2)");
      is($values->[1], "(3,4)");
      is(scalar @$values, 2);
    }
    # to_strings - string[]
    {
      my $spvm_array = $api->new_string_array(["あ", "い"]);
      my $values = $spvm_array->to_strings;
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
      my $spvm_array = $api->new_string_array(["あ", "い"]);
      my $values = $spvm_array->to_bins;
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

  # Operators - Array dereference overload
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
}

# class
{
  my $obj_int = $api->class("Int")->new(1);
  isa_ok($obj_int, "SPVM::BlessedObject");
  my $value = $obj_int->value;
  is($value, 1);
}

# error
{
  my $error = $api->new_error;
  ok(ref $error, "SPVM::ExchangeAPI::Error");
  
  # Default
  is($error->code, 0);
  
  # set
  $error->code(2);
  
  # get
  is($error->code, 2);
}

# Extra
{
  # ref SPVM array
  {
    my $nums = $api->new_float_array([1, 2, 3]);
    is(ref $nums, 'SPVM::BlessedObject::Array');
  }
  # my variable
  {
    ok(SPVM::TestCase->my_var_initialized_zero());
    ok(SPVM::TestCase->my_var_initialized_zero());
  }
  
  {
    ok(SPVM::TestCase->new_near_small_base_object_max_size_use_memory_pool());
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
