use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Literal::FloatingPoint';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Integer literal
{
  ok(TestCase::Literal::FloatingPoint->underline());
  ok(TestCase::Literal::FloatingPoint->underline_hex());
}

# Hex Literal
{
  ok(TestCase::Literal::FloatingPoint->hex_specifier());
  ok(TestCase::Literal::FloatingPoint->hex_all_number());
  ok(TestCase::Literal::FloatingPoint->hex_int());
  ok(TestCase::Literal::FloatingPoint->hex_int_max());
  ok(TestCase::Literal::FloatingPoint->hex_long_max());
}

# Octal Literal
{
  ok(TestCase::Literal::FloatingPoint->octal_specifier());
  ok(TestCase::Literal::FloatingPoint->octal_all_number());
  ok(TestCase::Literal::FloatingPoint->octal_int());
  ok(TestCase::Literal::FloatingPoint->octal_int_max());
  ok(TestCase::Literal::FloatingPoint->octal_long_max());
}

# Binary Literal
{
  ok(TestCase::Literal::FloatingPoint->binary_specifier());
  ok(TestCase::Literal::FloatingPoint->binary_all_number());
  ok(TestCase::Literal::FloatingPoint->binary_int());
  ok(TestCase::Literal::FloatingPoint->binary_int_max());
  ok(TestCase::Literal::FloatingPoint->binary_long_max());
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
