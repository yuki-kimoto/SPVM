use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::BitOperator';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Complement
{
  ok(SPVM::TestCase::BitOperator->complement());
}

# Bit shift left
{
  ok(SPVM::TestCase::BitOperator->bit_shift_left_int());
  ok(SPVM::TestCase::BitOperator->bit_shift_left_int_max());
  ok(SPVM::TestCase::BitOperator->bit_shift_left_int_overflow());
  ok(SPVM::TestCase::BitOperator->bit_shift_left_long());
  ok(SPVM::TestCase::BitOperator->bit_shift_left_long_max());
  ok(SPVM::TestCase::BitOperator->bit_shift_left_long_overflow());
}

# Bit shift right logical
{
  ok(SPVM::TestCase::BitOperator->bit_shift_right_logical_int());
  ok(SPVM::TestCase::BitOperator->bit_shift_right_logical_long());
}

# Bit shift right
{
  ok(SPVM::TestCase::BitOperator->bit_shift_right_int());
  ok(SPVM::TestCase::BitOperator->bit_shift_right_long());
}

# Bit and
{
  ok(SPVM::TestCase::BitOperator->bit_and());
}

# Bit or
{
  ok(SPVM::TestCase::BitOperator->bit_or());
}

# Bit xor
{
  ok(SPVM::TestCase::BitOperator->bit_xor());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

