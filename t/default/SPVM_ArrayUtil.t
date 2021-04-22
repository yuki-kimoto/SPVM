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

# copy_object_array
{
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_object_array);
}

# equals_object_array
{
  ok(TestCase::Lib::SPVM::ArrayUtil->test_equals_object_array);
}

# memmove_byte
{
  ok(TestCase::Lib::SPVM::ArrayUtil->test_memmove_byte);
}

# memcpy_byte
{
  ok(TestCase::Lib::SPVM::ArrayUtil->test_memcpy_byte);
}

# new_object_array_proto
{
  # slice_byte
  ok(TestCase::Lib::SPVM::ArrayUtil->test_new_object_array_proto);
}

# slice
{
  # slice_byte
  ok(TestCase::Lib::SPVM::ArrayUtil->test_slice_byte);

  # slice_short
  ok(TestCase::Lib::SPVM::ArrayUtil->test_slice_short);

  # slice_int
  ok(TestCase::Lib::SPVM::ArrayUtil->test_slice_int);

  # slice_long
  ok(TestCase::Lib::SPVM::ArrayUtil->test_slice_long);

  # slice_float
  ok(TestCase::Lib::SPVM::ArrayUtil->test_slice_float);

  # slice_double
  ok(TestCase::Lib::SPVM::ArrayUtil->test_slice_double);

  # slice_double
  ok(TestCase::Lib::SPVM::ArrayUtil->test_slice_object);
}

# dump array
{
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_byte_array);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_short_array);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_int_array);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_long_array);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_float_array);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_double_array);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_unsigned_byte_array);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_unsigned_short_array);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_unsigned_int_array);
  ok(TestCase::Lib::SPVM::ArrayUtil->test_dump_unsigned_long_array);
}

# equals
{
  # equals_byte_array
  ok(TestCase::Lib::SPVM::ArrayUtil->test_equals_byte_array);

  # equals_short_array
  ok(TestCase::Lib::SPVM::ArrayUtil->test_equals_short_array);

  # equals_int_array
  ok(TestCase::Lib::SPVM::ArrayUtil->test_equals_int_array);

  # equeals_long_array
  ok(TestCase::Lib::SPVM::ArrayUtil->test_equals_long_array);

  # equals_float_array
  ok(TestCase::Lib::SPVM::ArrayUtil->test_equals_float_array);

  # equals_double_array
  ok(TestCase::Lib::SPVM::ArrayUtil->test_equals_double_array);

  # equals_string_array
  ok(TestCase::Lib::SPVM::ArrayUtil->test_equals_string_array);
}

# Copy
{
  # copy_byte_array
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_byte_array);

  # copy_short_array
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_short_array);

  # copy_int_array
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_int_array);

  # copy_long_array
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_long_array);

  # copy_float_array
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_float_array);

  # copy_double_array
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_double_array);

  # copy_string_array
  ok(TestCase::Lib::SPVM::ArrayUtil->test_copy_string_array);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
