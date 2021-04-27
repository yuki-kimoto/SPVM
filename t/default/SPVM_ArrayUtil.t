use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::ArrayUtil';
use SPVM 'SPVM::ArrayUtil';
use POSIX();
use TestFile;

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

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

# Positive infinity(unix like system : inf, Windows : 1.#INF)
my $POSITIVE_INFINITY = 9**9**9;

my $NaN = 9**9**9 / 9**9**9;

my $nan_re = qr/(nan|ind)/i;

use SPVM 'TestCase::Lib::SPVM::ArrayUtil';
use SPVM 'SPVM::ArrayUtil';


# Copy
{
  # copy_array_byte
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_array_byte);

  # copy_array_short
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_array_short);

  # copy_array_int
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_array_int);

  # copy_array_long
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_array_long);

  # copy_array_float
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_array_float);

  # copy_array_double
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_array_double);

  # copy_array_string
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_array_string);
  
  # copy_array_object
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_array_object);
}

# copy_array_range
{
  # copy_array_range_byte
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_array_range_byte);

  # copy_array_range_short
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_array_range_short);

  # copy_array_range_int
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_array_range_int);

  # copy_array_range_long
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_array_range_long);

  # copy_array_range_float
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_array_range_float);

  # copy_array_range_double
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_array_range_double);

  # copy_array_range_double
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_array_range_string);

  # copy_array_range_double
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_array_range_object);
}

# dump array
{
  # dump_array_object
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_array_byte);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_array_short);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_array_int);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_array_long);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_array_float);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_array_double);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_unsigned_array_byte);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_unsigned_array_short);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_unsigned_array_int);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_unsigned_array_long);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_array_string);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_array_object);
}

# equals
{
  # equals_array_byte
  ok(TestCase::Lib::SPVM::ArrayUtil->test_equals_array_byte);

  # equals_array_short
  ok(TestCase::Lib::SPVM::ArrayUtil->test_equals_array_short);

  # equals_array_int
  ok(TestCase::Lib::SPVM::ArrayUtil->test_equals_array_int);

  # equeals_array_long
  ok(TestCase::Lib::SPVM::ArrayUtil->test_equals_array_long);

  # equals_array_float
  ok(TestCase::Lib::SPVM::ArrayUtil->test_equals_array_float);

  # equals_array_double
  ok(TestCase::Lib::SPVM::ArrayUtil->test_equals_array_double);

  # equals_array_string
  ok(TestCase::Lib::SPVM::ArrayUtil->test_equals_array_string);

  # equals_array_object
  ok(TestCase::Lib::SPVM::ArrayUtil->test_equals_array_object);
}

# memcpy
{
  ok(TestCase::Lib::SPVM::ArrayUtil->test_memcpy_byte);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_memcpy_short);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_memcpy_int);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_memcpy_long);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_memcpy_float);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_memcpy_double);
}

# memmove
{
  ok(TestCase::Lib::SPVM::ArrayUtil->test_memmove_byte);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_memmove_short);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_memmove_int);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_memmove_long);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_memmove_float);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_memmove_double);
}

# new_array_proto
{
  # copy_array_range_byte
  ok(TestCase::Lib::SPVM::ArrayUtil->test_new_array_proto);
}

# sort
{
  ok(TestCase::Lib::SPVM::ArrayUtil->sort_byte);
  ok(TestCase::Lib::SPVM::ArrayUtil->sort_short);
  ok(TestCase::Lib::SPVM::ArrayUtil->sort_int);
  ok(TestCase::Lib::SPVM::ArrayUtil->sort_long);
  ok(TestCase::Lib::SPVM::ArrayUtil->sort_float);
  ok(TestCase::Lib::SPVM::ArrayUtil->sort_double);
  ok(TestCase::Lib::SPVM::ArrayUtil->sort_string);
  ok(TestCase::Lib::SPVM::ArrayUtil->sort_object);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
