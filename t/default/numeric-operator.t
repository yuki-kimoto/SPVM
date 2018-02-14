use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Special assign
{
  ok(SPVM::TestCase::special_assign());
}

# Add
{
  ok(SPVM::TestCase::add());

  is(SPVM::TestCase::add_byte_max(), 127);
  is(SPVM::TestCase::add_byte_min(), -127);
  is(SPVM::TestCase::add_byte_overflow(), -128);
  is(SPVM::TestCase::add_short_max(), 32767);
  is(SPVM::TestCase::add_short_min(), -32767);
  is(SPVM::TestCase::add_short_overflow(), -32768);
  is(SPVM::TestCase::add_int_max(), 2147483647);
  is(SPVM::TestCase::add_int_min(), -2147483647);
  is(SPVM::TestCase::add_int_overflow(), -2147483648);
  is(SPVM::TestCase::add_long_max(), 9223372036854775807);
  is(SPVM::TestCase::add_long_min(), -9223372036854775807);
  is(SPVM::TestCase::add_long_overflow(), -9223372036854775808);
}

# Subtract
{
  ok(SPVM::TestCase::subtract());

  is(SPVM::TestCase::subtract_byte_max(), 126);
  is(SPVM::TestCase::subtract_byte_min(), -128);
  is(SPVM::TestCase::subtract_byte_underflow(), 127);
  is(SPVM::TestCase::subtract_short_max(), 32766);
  is(SPVM::TestCase::subtract_short_min(), -32768);
  is(SPVM::TestCase::subtract_short_underflow(), 32767);
  is(SPVM::TestCase::subtract_int_max(), 2147483646);
  is(SPVM::TestCase::subtract_int_min(), -2147483648);
  is(SPVM::TestCase::subtract_int_underflow(), 2147483647);
  is(SPVM::TestCase::subtract_long_max(), 9223372036854775806);
  is(SPVM::TestCase::subtract_long_min(), -9223372036854775808);
  is(SPVM::TestCase::subtract_long_underflow(), 9223372036854775807);
}

# Multiply
{
  is(SPVM::TestCase::multiply_byte_plus(), 64);
  is(SPVM::TestCase::multiply_byte_minus(), -64);
  is(SPVM::TestCase::multiply_byte_overflow(), -128);
  is(SPVM::TestCase::multiply_short_plus(), 16384);
  is(SPVM::TestCase::multiply_short_minus(), -16384);
  is(SPVM::TestCase::multiply_short_overflow(), -32768);
  is(SPVM::TestCase::multiply_int_plus(), 1073741824);
  is(SPVM::TestCase::multiply_int_minus(), -1073741824);
  is(SPVM::TestCase::multiply_int_overflow(), -2147483648);
  is(SPVM::TestCase::multiply_long_plus(), 4611686018427387904);
  is(SPVM::TestCase::multiply_long_minus(), -4611686018427387904);
  is(SPVM::TestCase::multiply_long_overflow(), -9223372036854775808);
}

# Divide
{
  ok(SPVM::TestCase::divide());
}

# Remainder
{
  ok(SPVM::TestCase::remainder());
}

# Negate
{
  ok(SPVM::TestCase::negate());
}

# Complement
{
  ok(SPVM::TestCase::complement());
}

# Bit shift left
{
  ok(SPVM::TestCase::bit_shift_left_int());
  ok(SPVM::TestCase::bit_shift_left_int_max());
  ok(SPVM::TestCase::bit_shift_left_int_overflow());
  ok(SPVM::TestCase::bit_shift_left_long());
  ok(SPVM::TestCase::bit_shift_left_long_max());
  ok(SPVM::TestCase::bit_shift_left_long_overflow());
}

# Bit shift right logical
{
  ok(SPVM::TestCase::bit_shift_right_logical_int());
  ok(SPVM::TestCase::bit_shift_right_logical_long());
}

# Bit shift right
{
  ok(SPVM::TestCase::bit_shift_right_int());
  ok(SPVM::TestCase::bit_shift_right_long());
}

# Bit and
{
  ok(SPVM::TestCase::bit_and());
}

# Bit or
{
  ok(SPVM::TestCase::bit_or());
}

# Bit xor
{
  ok(SPVM::TestCase::bit_xor());
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);

