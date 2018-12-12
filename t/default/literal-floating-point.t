use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Literal::FloatingPoint';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

{
  ok(TestCase::Literal::FloatingPoint->decimal());
}

# Hex Literal
{
  ok(TestCase::Literal::FloatingPoint->hex_specifier());
  ok(TestCase::Literal::FloatingPoint->hex_all_number());
  ok(TestCase::Literal::FloatingPoint->hex_int());
  ok(TestCase::Literal::FloatingPoint->hex_int_max());
  ok(TestCase::Literal::FloatingPoint->hex_long_max());
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
