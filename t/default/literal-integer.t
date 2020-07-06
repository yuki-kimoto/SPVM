use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Literal::Integer';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

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
  ok(TestCase::Literal::Integer->hex_all_numbers());
  ok(TestCase::Literal::Integer->hex_all_f());
  ok(TestCase::Literal::Integer->hex_max_int());
  ok(TestCase::Literal::Integer->hex_min_int());
  ok(TestCase::Literal::Integer->hex_combination());
  ok(TestCase::Literal::Integer->hex_long_all_f());
}

# Octal Literal
{
  ok(TestCase::Literal::Integer->octal_all_numbers());
  ok(TestCase::Literal::Integer->octal_combination());
}

# Binary Literal
{
  ok(TestCase::Literal::Integer->binary_all_numbers());
  ok(TestCase::Literal::Integer->binary_combination());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
