use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Literal::Integer';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Integer Literal - decimal notation
{
  ok(SPVM::TestCase::Literal::Integer->integer_literal_decimal_notation);
  ok(SPVM::TestCase::Literal::Integer->integer_literal_decimal_notation_extra);
}

# Integer Literal - hex notation
{
  ok(SPVM::TestCase::Literal::Integer->hex_all_numbers());
  ok(SPVM::TestCase::Literal::Integer->hex_all_f());
  ok(SPVM::TestCase::Literal::Integer->hex_max_int());
  ok(SPVM::TestCase::Literal::Integer->hex_min_int());
  ok(SPVM::TestCase::Literal::Integer->hex_combination());
  ok(SPVM::TestCase::Literal::Integer->hex_long_all_f());
}

# Integer Literal - octal notation
{
  ok(SPVM::TestCase::Literal::Integer->octal_all_numbers());
  ok(SPVM::TestCase::Literal::Integer->octal_combination());
}

# Integer Literal - binary notation
{
  ok(SPVM::TestCase::Literal::Integer->binary_all_numbers());
  ok(SPVM::TestCase::Literal::Integer->binary_combination());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
