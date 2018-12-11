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
  ok(TestCase::Literal::Integer->decimal());
}

# Hex Literal
{
  ok(TestCase::Literal::Integer->hex());
}

# Octal Literal
{
  ok(TestCase::Literal::Integer->octal_expression());
  ok(TestCase::Literal::Integer->octal_all_number());
  ok(TestCase::Literal::Integer->octal_int());
  ok(TestCase::Literal::Integer->octal_int_max());
  ok(TestCase::Literal::Integer->octal_long_max());
}

# Binary Literal
{
  ok(TestCase::Literal::Integer->binary_expression());
  ok(TestCase::Literal::Integer->binary_all_number());
  ok(TestCase::Literal::Integer->binary_int());
  ok(TestCase::Literal::Integer->binary_int_max());
  ok(TestCase::Literal::Integer->binary_long_max());
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
