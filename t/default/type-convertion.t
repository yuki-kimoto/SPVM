use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Convert type - floating point narrowing convertion
{
  ok(SPVM::TestCase::convert_float_to_byte());
  ok(SPVM::TestCase::convert_float_to_short());
  ok(SPVM::TestCase::convert_float_to_int());
  ok(SPVM::TestCase::convert_float_to_long());
  ok(SPVM::TestCase::convert_double_to_byte());
  ok(SPVM::TestCase::convert_double_to_short());
  ok(SPVM::TestCase::convert_double_to_int());
  ok(SPVM::TestCase::convert_double_to_long());
  ok(SPVM::TestCase::convert_double_to_float());
}

# Convert type - floating point widening convertion
{
  ok(SPVM::TestCase::convert_byte_to_float());
  ok(SPVM::TestCase::convert_short_to_float());
  ok(SPVM::TestCase::convert_int_to_float());
  ok(SPVM::TestCase::convert_long_to_float());
  ok(SPVM::TestCase::convert_byte_to_double());
  ok(SPVM::TestCase::convert_short_to_double());
  ok(SPVM::TestCase::convert_int_to_double());
  ok(SPVM::TestCase::convert_long_to_double());
  ok(SPVM::TestCase::convert_float_to_double());
}

# Convert type - integral number widning convertion
{
  ok(SPVM::TestCase::convert_byte_to_short_plus());
  ok(SPVM::TestCase::convert_byte_to_short_minus());
  ok(SPVM::TestCase::convert_byte_to_int_plus());
  ok(SPVM::TestCase::convert_byte_to_int_minus());
  ok(SPVM::TestCase::convert_byte_to_long_plus());
  ok(SPVM::TestCase::convert_byte_to_long_minus());
  ok(SPVM::TestCase::convert_short_to_int_plus());
  ok(SPVM::TestCase::convert_short_to_int_minus());
  ok(SPVM::TestCase::convert_short_to_long_plus());
  ok(SPVM::TestCase::convert_short_to_long_minus());
  ok(SPVM::TestCase::convert_int_to_long_plus());
  ok(SPVM::TestCase::convert_int_to_long_minus());
}

# Convert type - same type
{
  ok(SPVM::TestCase::convert_long_to_long());
  ok(SPVM::TestCase::convert_int_to_int());
  ok(SPVM::TestCase::convert_short_to_short());
  ok(SPVM::TestCase::convert_byte_to_byte());
}

# Convert type - integral number narrowing convertion
{
  ok(SPVM::TestCase::convert_long_to_int());
  ok(SPVM::TestCase::convert_long_to_short());
  ok(SPVM::TestCase::convert_long_to_byte());
  ok(SPVM::TestCase::convert_int_to_short());
  ok(SPVM::TestCase::convert_int_to_byte());
  ok(SPVM::TestCase::convert_short_to_byte());
}

# Convert to string
{
  ok(SPVM::TestCase::convert_to_string());
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
