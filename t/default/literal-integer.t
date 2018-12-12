use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Literal::Integer';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Decimal Literal
{
  ok(TestCase::Literal::Integer->decimal_all_numbers());
  ok(TestCase::Literal::Integer->decimal_plus_max());
  ok(TestCase::Literal::Integer->decimal_minus_max());
  ok(TestCase::Literal::Integer->decimal_underline());
  ok(TestCase::Literal::Integer->decimal_long_minus_max());
  ok(TestCase::Literal::Integer->decimal_long_lower_case());
  ok(TestCase::Literal::Integer->decimal_long_underline());
  ok(TestCase::Literal::Integer->decimal_byte_norrowing_convertion());
  ok(TestCase::Literal::Integer->decimal_short_norrowing_convertion());
}

# Hex Literal
{
  ok(TestCase::Literal::Integer->hex());
}

# Octal Literal
{
  ok(TestCase::Literal::Integer->octal());
}

# Binary Literal
{
  ok(TestCase::Literal::Integer->binary());
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
