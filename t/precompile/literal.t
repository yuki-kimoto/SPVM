use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Literal';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Number literal
{
  ok(TestCase::Literal->number_literal_underline_hex());
  ok(TestCase::Literal->number_literal_underline());
  ok(TestCase::Literal->number_literal_hex_specifier());
  ok(TestCase::Literal->number_literal_hex_all_number());
  ok(TestCase::Literal->number_literal_hex_int());
  ok(TestCase::Literal->number_literal_hex_int_max());
  ok(TestCase::Literal->number_literal_hex_long_max());

  ok(TestCase::Literal->number_literal_octal_specifier());
  ok(TestCase::Literal->number_literal_octal_all_number());
  ok(TestCase::Literal->number_literal_octal_int());
  ok(TestCase::Literal->number_literal_octal_int_max());
  ok(TestCase::Literal->number_literal_octal_long_max());

  ok(TestCase::Literal->number_literal_binary_specifier());
  ok(TestCase::Literal->number_literal_binary_all_number());
  ok(TestCase::Literal->number_literal_binary_int());
  ok(TestCase::Literal->number_literal_binary_int_max());
  ok(TestCase::Literal->number_literal_binary_long_max());
}

# Character literal
{
  ok(TestCase::Literal->literal_character());
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
