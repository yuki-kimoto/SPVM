use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::BitOperator';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Bit not
{
  # Bit not - Operation
  {
    ok(SPVM::TestCase::Operator::BitOperator->bit_not_byte);
    ok(SPVM::TestCase::Operator::BitOperator->bit_not_short);
    ok(SPVM::TestCase::Operator::BitOperator->bit_not_int);
    ok(SPVM::TestCase::Operator::BitOperator->bit_not_int_theory);
    ok(SPVM::TestCase::Operator::BitOperator->bit_not_long);
  }

  # Extra
  {
    ok(SPVM::TestCase::Operator::BitOperator->complement());
  }
}

# Bit and
{
  ok(SPVM::TestCase::Operator::BitOperator->bit_and());
}

# Bit or
{
  ok(SPVM::TestCase::Operator::BitOperator->bit_or());
}

# Bit xor
{
  ok(SPVM::TestCase::Operator::BitOperator->bit_xor());
}

# Complement
{
  ok(SPVM::TestCase::Operator::BitOperator->complement());
}

# Bit shift left
{
  ok(SPVM::TestCase::Operator::BitOperator->bit_shift_left_int());
  ok(SPVM::TestCase::Operator::BitOperator->bit_shift_left_int_max());
  ok(SPVM::TestCase::Operator::BitOperator->bit_shift_left_int_overflow());
  ok(SPVM::TestCase::Operator::BitOperator->bit_shift_left_long());
  ok(SPVM::TestCase::Operator::BitOperator->bit_shift_left_long_max());
  ok(SPVM::TestCase::Operator::BitOperator->bit_shift_left_long_overflow());
}

# Bit shift right logical
{
  ok(SPVM::TestCase::Operator::BitOperator->bit_shift_right_logical_int());
  ok(SPVM::TestCase::Operator::BitOperator->bit_shift_right_logical_long());
}

# Bit shift right
{
  ok(SPVM::TestCase::Operator::BitOperator->bit_shift_right_int());
  ok(SPVM::TestCase::Operator::BitOperator->bit_shift_right_long());
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
