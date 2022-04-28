use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::TypeConversion';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Convert undef to object
{
  ok(SPVM::TestCase::TypeConversion->convert_undef_to_object);
}

# Convert type - floating point narrowing convertion
{
  ok(SPVM::TestCase::TypeConversion->convert_float_to_byte());
  ok(SPVM::TestCase::TypeConversion->convert_float_to_short());
  ok(SPVM::TestCase::TypeConversion->convert_float_to_int());
  ok(SPVM::TestCase::TypeConversion->convert_float_to_long());
  ok(SPVM::TestCase::TypeConversion->convert_double_to_byte());
  ok(SPVM::TestCase::TypeConversion->convert_double_to_short());
  ok(SPVM::TestCase::TypeConversion->convert_double_to_int());
  ok(SPVM::TestCase::TypeConversion->convert_double_to_long());
  ok(SPVM::TestCase::TypeConversion->convert_double_to_float());
}

# Convert type - floating point widening convertion
{
  ok(SPVM::TestCase::TypeConversion->convert_byte_to_float());
  ok(SPVM::TestCase::TypeConversion->convert_short_to_float());
  ok(SPVM::TestCase::TypeConversion->convert_int_to_float());
  ok(SPVM::TestCase::TypeConversion->convert_long_to_float());
  ok(SPVM::TestCase::TypeConversion->convert_byte_to_double());
  ok(SPVM::TestCase::TypeConversion->convert_short_to_double());
  ok(SPVM::TestCase::TypeConversion->convert_int_to_double());
  ok(SPVM::TestCase::TypeConversion->convert_long_to_double());
  ok(SPVM::TestCase::TypeConversion->convert_float_to_double());
}

# Convert type - integral number widning convertion
{
  ok(SPVM::TestCase::TypeConversion->convert_byte_to_short_plus());
  ok(SPVM::TestCase::TypeConversion->convert_byte_to_short_minus());
  ok(SPVM::TestCase::TypeConversion->convert_byte_to_int_plus());
  ok(SPVM::TestCase::TypeConversion->convert_byte_to_int_minus());
  ok(SPVM::TestCase::TypeConversion->convert_byte_to_long_plus());
  ok(SPVM::TestCase::TypeConversion->convert_byte_to_long_minus());
  ok(SPVM::TestCase::TypeConversion->convert_short_to_int_plus());
  ok(SPVM::TestCase::TypeConversion->convert_short_to_int_minus());
  ok(SPVM::TestCase::TypeConversion->convert_short_to_long_plus());
  ok(SPVM::TestCase::TypeConversion->convert_short_to_long_minus());
  ok(SPVM::TestCase::TypeConversion->convert_int_to_long_plus());
  ok(SPVM::TestCase::TypeConversion->convert_int_to_long_minus());
}

# Convert type - same type
{
  ok(SPVM::TestCase::TypeConversion->convert_long_to_long());
  ok(SPVM::TestCase::TypeConversion->convert_int_to_int());
  ok(SPVM::TestCase::TypeConversion->convert_short_to_short());
  ok(SPVM::TestCase::TypeConversion->convert_byte_to_byte());
}

# Convert type - integral number narrowing convertion
{
  ok(SPVM::TestCase::TypeConversion->convert_long_to_int());
  ok(SPVM::TestCase::TypeConversion->convert_long_to_short());
  ok(SPVM::TestCase::TypeConversion->convert_long_to_byte());
  ok(SPVM::TestCase::TypeConversion->convert_int_to_short());
  ok(SPVM::TestCase::TypeConversion->convert_int_to_byte());
  ok(SPVM::TestCase::TypeConversion->convert_short_to_byte());
}

# Convert to string
{
  ok(SPVM::TestCase::TypeConversion->convert_to_string());
}

{
  ok(SPVM::TestCase::TypeConversion->convert_to_numeric_array);
  ok(SPVM::TestCase::TypeConversion->convert_to_object_array);
  ok(SPVM::TestCase::TypeConversion->convert_to_callback_array);
  ok(SPVM::TestCase::TypeConversion->convert_to_any_object);
  ok(SPVM::TestCase::TypeConversion->convert_to_callback);
  ok(SPVM::TestCase::TypeConversion->convert_to_undef_to_any_object);
  ok(SPVM::TestCase::TypeConversion->convert_to_undef_to_callback);
  ok(SPVM::TestCase::TypeConversion->convert_to_undef_to_object);

  ok(SPVM::TestCase::TypeConversion->convert_byte_to_byte_object);
  ok(SPVM::TestCase::TypeConversion->convert_short_to_short_object);
  ok(SPVM::TestCase::TypeConversion->convert_int_to_int_object);
  ok(SPVM::TestCase::TypeConversion->convert_long_to_long_object);
  ok(SPVM::TestCase::TypeConversion->convert_float_to_float_object);
  ok(SPVM::TestCase::TypeConversion->convert_double_to_double_object);
  
  ok(SPVM::TestCase::TypeConversion->convert_byte_to_any_object);
  ok(SPVM::TestCase::TypeConversion->convert_short_to_any_object);
  ok(SPVM::TestCase::TypeConversion->convert_int_to_any_object);
  ok(SPVM::TestCase::TypeConversion->convert_long_to_any_object);
  ok(SPVM::TestCase::TypeConversion->convert_float_to_any_object);
  ok(SPVM::TestCase::TypeConversion->convert_double_to_any_object);
  
  ok(SPVM::TestCase::TypeConversion->convert_byte_object_to_byte);
  ok(SPVM::TestCase::TypeConversion->convert_short_object_to_short);
  ok(SPVM::TestCase::TypeConversion->convert_int_object_to_int);
  ok(SPVM::TestCase::TypeConversion->convert_long_object_to_long);
  ok(SPVM::TestCase::TypeConversion->convert_float_object_to_float);
  ok(SPVM::TestCase::TypeConversion->convert_double_object_to_double);
  
  ok(SPVM::TestCase::TypeConversion->convert_any_object_to_byte);
  ok(SPVM::TestCase::TypeConversion->convert_any_object_to_short);
  ok(SPVM::TestCase::TypeConversion->convert_any_object_to_int);
  ok(SPVM::TestCase::TypeConversion->convert_any_object_to_long);
  ok(SPVM::TestCase::TypeConversion->convert_any_object_to_float);
  ok(SPVM::TestCase::TypeConversion->convert_any_object_to_double);
}

# Convert to string
{
  ok(SPVM::TestCase::TypeConversion->convert_postfix);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
