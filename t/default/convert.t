use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Convert';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Convert undef to object
{
  ok(TestCase::Convert->convert_undef_to_object);
}

# Convert type - floating point narrowing convertion
{
  ok(TestCase::Convert->convert_float_to_byte());
  ok(TestCase::Convert->convert_float_to_short());
  ok(TestCase::Convert->convert_float_to_int());
  ok(TestCase::Convert->convert_float_to_long());
  ok(TestCase::Convert->convert_double_to_byte());
  ok(TestCase::Convert->convert_double_to_short());
  ok(TestCase::Convert->convert_double_to_int());
  ok(TestCase::Convert->convert_double_to_long());
  ok(TestCase::Convert->convert_double_to_float());
}

# Convert type - floating point widening convertion
{
  ok(TestCase::Convert->convert_byte_to_float());
  ok(TestCase::Convert->convert_short_to_float());
  ok(TestCase::Convert->convert_int_to_float());
  ok(TestCase::Convert->convert_long_to_float());
  ok(TestCase::Convert->convert_byte_to_double());
  ok(TestCase::Convert->convert_short_to_double());
  ok(TestCase::Convert->convert_int_to_double());
  ok(TestCase::Convert->convert_long_to_double());
  ok(TestCase::Convert->convert_float_to_double());
}

# Convert type - integral number widning convertion
{
  ok(TestCase::Convert->convert_byte_to_short_plus());
  ok(TestCase::Convert->convert_byte_to_short_minus());
  ok(TestCase::Convert->convert_byte_to_int_plus());
  ok(TestCase::Convert->convert_byte_to_int_minus());
  ok(TestCase::Convert->convert_byte_to_long_plus());
  ok(TestCase::Convert->convert_byte_to_long_minus());
  ok(TestCase::Convert->convert_short_to_int_plus());
  ok(TestCase::Convert->convert_short_to_int_minus());
  ok(TestCase::Convert->convert_short_to_long_plus());
  ok(TestCase::Convert->convert_short_to_long_minus());
  ok(TestCase::Convert->convert_int_to_long_plus());
  ok(TestCase::Convert->convert_int_to_long_minus());
}

# Convert type - same type
{
  ok(TestCase::Convert->convert_long_to_long());
  ok(TestCase::Convert->convert_int_to_int());
  ok(TestCase::Convert->convert_short_to_short());
  ok(TestCase::Convert->convert_byte_to_byte());
}

# Convert type - integral number narrowing convertion
{
  ok(TestCase::Convert->convert_long_to_int());
  ok(TestCase::Convert->convert_long_to_short());
  ok(TestCase::Convert->convert_long_to_byte());
  ok(TestCase::Convert->convert_int_to_short());
  ok(TestCase::Convert->convert_int_to_byte());
  ok(TestCase::Convert->convert_short_to_byte());
}

# Convert to string
{
  ok(TestCase::Convert->convert_to_string());
}

{
  ok(TestCase::Convert->convert_to_numeric_array);
  ok(TestCase::Convert->convert_to_object_array);
  ok(TestCase::Convert->convert_to_callback_array);
  ok(TestCase::Convert->convert_to_any_object);
  ok(TestCase::Convert->convert_to_callback);
  ok(TestCase::Convert->convert_to_undef_to_any_object);
  ok(TestCase::Convert->convert_to_undef_to_callback);
  ok(TestCase::Convert->convert_to_undef_to_object);

  ok(TestCase::Convert->convert_byte_to_byte_object);
  ok(TestCase::Convert->convert_short_to_short_object);
  ok(TestCase::Convert->convert_int_to_int_object);
  ok(TestCase::Convert->convert_long_to_long_object);
  ok(TestCase::Convert->convert_float_to_float_object);
  ok(TestCase::Convert->convert_double_to_double_object);
  
  ok(TestCase::Convert->convert_byte_to_any_object);
  ok(TestCase::Convert->convert_short_to_any_object);
  ok(TestCase::Convert->convert_int_to_any_object);
  ok(TestCase::Convert->convert_long_to_any_object);
  ok(TestCase::Convert->convert_float_to_any_object);
  ok(TestCase::Convert->convert_double_to_any_object);
  
  ok(TestCase::Convert->convert_byte_object_to_byte);
  ok(TestCase::Convert->convert_short_object_to_short);
  ok(TestCase::Convert->convert_int_object_to_int);
  ok(TestCase::Convert->convert_long_object_to_long);
  ok(TestCase::Convert->convert_float_object_to_float);
  ok(TestCase::Convert->convert_double_object_to_double);
  
  ok(TestCase::Convert->convert_any_object_to_byte);
  ok(TestCase::Convert->convert_any_object_to_short);
  ok(TestCase::Convert->convert_any_object_to_int);
  ok(TestCase::Convert->convert_any_object_to_long);
  ok(TestCase::Convert->convert_any_object_to_float);
  ok(TestCase::Convert->convert_any_object_to_double);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
