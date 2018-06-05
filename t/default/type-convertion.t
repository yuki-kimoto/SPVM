use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Convert type - floating point narrowing convertion
{
  ok(TestCase->convert_float_to_byte());
  ok(TestCase->convert_float_to_short());
  ok(TestCase->convert_float_to_int());
  ok(TestCase->convert_float_to_long());
  ok(TestCase->convert_double_to_byte());
  ok(TestCase->convert_double_to_short());
  ok(TestCase->convert_double_to_int());
  ok(TestCase->convert_double_to_long());
  ok(TestCase->convert_double_to_float());
}

# Convert type - floating point widening convertion
{
  ok(TestCase->convert_byte_to_float());
  ok(TestCase->convert_short_to_float());
  ok(TestCase->convert_int_to_float());
  ok(TestCase->convert_long_to_float());
  ok(TestCase->convert_byte_to_double());
  ok(TestCase->convert_short_to_double());
  ok(TestCase->convert_int_to_double());
  ok(TestCase->convert_long_to_double());
  ok(TestCase->convert_float_to_double());
}

# Convert type - integral number widning convertion
{
  ok(TestCase->convert_byte_to_short_plus());
  ok(TestCase->convert_byte_to_short_minus());
  ok(TestCase->convert_byte_to_int_plus());
  ok(TestCase->convert_byte_to_int_minus());
  ok(TestCase->convert_byte_to_long_plus());
  ok(TestCase->convert_byte_to_long_minus());
  ok(TestCase->convert_short_to_int_plus());
  ok(TestCase->convert_short_to_int_minus());
  ok(TestCase->convert_short_to_long_plus());
  ok(TestCase->convert_short_to_long_minus());
  ok(TestCase->convert_int_to_long_plus());
  ok(TestCase->convert_int_to_long_minus());
}

# Convert type - same type
{
  ok(TestCase->convert_long_to_long());
  ok(TestCase->convert_int_to_int());
  ok(TestCase->convert_short_to_short());
  ok(TestCase->convert_byte_to_byte());
}

# Convert type - integral number narrowing convertion
{
  ok(TestCase->convert_long_to_int());
  ok(TestCase->convert_long_to_short());
  ok(TestCase->convert_long_to_byte());
  ok(TestCase->convert_int_to_short());
  ok(TestCase->convert_int_to_byte());
  ok(TestCase->convert_short_to_byte());
}

# Convert to string
{
  ok(TestCase->convert_to_string());
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
