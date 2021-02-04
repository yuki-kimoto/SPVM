use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Literal::FloatingPoint';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# decimal
{
  ok(TestCase::Literal::FloatingPoint->decimal_all_numbers);
  ok(TestCase::Literal::FloatingPoint->decimal_minus);
  ok(TestCase::Literal::FloatingPoint->decimal_plus);
  ok(TestCase::Literal::FloatingPoint->decimal_prefix_f);
  ok(TestCase::Literal::FloatingPoint->decimal_prefix_F);
  ok(TestCase::Literal::FloatingPoint->decimal_prefix_d);
  ok(TestCase::Literal::FloatingPoint->decimal_prefix_D);
  ok(TestCase::Literal::FloatingPoint->decimal_under_line);
  ok(TestCase::Literal::FloatingPoint->decimal_exponant_e_plus);
  ok(TestCase::Literal::FloatingPoint->decimal_exponant_E_minus);
  ok(TestCase::Literal::FloatingPoint->decimal_exponant_e_nosign);
  ok(TestCase::Literal::FloatingPoint->decimal_exponant_no_point);
}

# Hex Literal
{
  ok(TestCase::Literal::FloatingPoint->hex_all_numbers);
  ok(TestCase::Literal::FloatingPoint->hex_suffix);
  ok(TestCase::Literal::FloatingPoint->hex_equals_decimal);
  ok(TestCase::Literal::FloatingPoint->hex_exponent);
  ok(TestCase::Literal::FloatingPoint->hex_underline);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
