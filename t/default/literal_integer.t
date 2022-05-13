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

# Integer Literal - hexadecimal notation
{
  ok(SPVM::TestCase::Literal::Integer->integer_literal_hex_notation);
  ok(SPVM::TestCase::Literal::Integer->integer_literal_hex_notation_extra);
}

# Integer Literal - octal notation
{
  ok(SPVM::TestCase::Literal::Integer->integer_literal_octal_notation);
  ok(SPVM::TestCase::Literal::Integer->integer_literal_octal_notation_extra);
}

# Integer Literal - binary notation
{
  ok(SPVM::TestCase::Literal::Integer->integer_literal_binary_notation);
  ok(SPVM::TestCase::Literal::Integer->integer_literal_binary_notation_extra);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
