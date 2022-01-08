use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Literal::FloatingPoint';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# decimal
{
  ok(SPVM::TestCase::Literal::FloatingPoint->decimal_all_numbers);
  ok(SPVM::TestCase::Literal::FloatingPoint->decimal_minus);
  ok(SPVM::TestCase::Literal::FloatingPoint->decimal_plus);
  ok(SPVM::TestCase::Literal::FloatingPoint->decimal_prefix_f);
  ok(SPVM::TestCase::Literal::FloatingPoint->decimal_prefix_F);
  ok(SPVM::TestCase::Literal::FloatingPoint->decimal_prefix_d);
  ok(SPVM::TestCase::Literal::FloatingPoint->decimal_prefix_D);
  ok(SPVM::TestCase::Literal::FloatingPoint->decimal_under_line);
  ok(SPVM::TestCase::Literal::FloatingPoint->decimal_exponant_e_plus);
  ok(SPVM::TestCase::Literal::FloatingPoint->decimal_exponant_E_minus);
  ok(SPVM::TestCase::Literal::FloatingPoint->decimal_exponant_e_nosign);
  ok(SPVM::TestCase::Literal::FloatingPoint->decimal_exponant_no_point);
}

# Hex Literal
{
  ok(SPVM::TestCase::Literal::FloatingPoint->hex_all_numbers);
  ok(SPVM::TestCase::Literal::FloatingPoint->hex_suffix);
  ok(SPVM::TestCase::Literal::FloatingPoint->hex_equals_decimal);
  ok(SPVM::TestCase::Literal::FloatingPoint->hex_exponent);
  ok(SPVM::TestCase::Literal::FloatingPoint->hex_underline);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
