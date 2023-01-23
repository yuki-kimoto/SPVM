use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::BitOperator';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# Bit not
{
  # Bit not - Operation
  {
    ok(SPVM::TestCase::BitOperator->bit_not_byte);
    ok(SPVM::TestCase::BitOperator->bit_not_short);
    ok(SPVM::TestCase::BitOperator->bit_not_int);
    ok(SPVM::TestCase::BitOperator->bit_not_int_theory);
    ok(SPVM::TestCase::BitOperator->bit_not_long);
  }

  # Extra
  {
    ok(SPVM::TestCase::BitOperator->complement());
  }
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
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
