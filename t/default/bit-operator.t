use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::BitOperator';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Complement
{
  ok(TestCase::BitOperator->complement());
}

# Bit shift left
{
  ok(TestCase::BitOperator->bit_shift_left_int());
  ok(TestCase::BitOperator->bit_shift_left_int_max());
  ok(TestCase::BitOperator->bit_shift_left_int_overflow());
  ok(TestCase::BitOperator->bit_shift_left_long());
  ok(TestCase::BitOperator->bit_shift_left_long_max());
  ok(TestCase::BitOperator->bit_shift_left_long_overflow());
}

# Bit shift right logical
{
  ok(TestCase::BitOperator->bit_shift_right_logical_int());
  ok(TestCase::BitOperator->bit_shift_right_logical_long());
}

# Bit shift right
{
  ok(TestCase::BitOperator->bit_shift_right_int());
  ok(TestCase::BitOperator->bit_shift_right_long());
}

# Bit and
{
  ok(TestCase::BitOperator->bit_and());
}

# Bit or
{
  ok(TestCase::BitOperator->bit_or());
}

# Bit xor
{
  ok(TestCase::BitOperator->bit_xor());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

