use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::TypeCast';
use SPVM 'TestCase::Operator::TypeCast';


# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Convert undef to object
{
  ok(SPVM::TestCase::Operator::TypeCast->undef_to_object);
}
 
# Convert type - floating point narrowing convertion
{
  ok(SPVM::TestCase::Operator::TypeCast->float_to_byte);
  ok(SPVM::TestCase::Operator::TypeCast->float_to_short);
  ok(SPVM::TestCase::Operator::TypeCast->float_to_int);
  ok(SPVM::TestCase::Operator::TypeCast->float_to_long);
  ok(SPVM::TestCase::Operator::TypeCast->double_to_byte);
  ok(SPVM::TestCase::Operator::TypeCast->double_to_short);
  ok(SPVM::TestCase::Operator::TypeCast->double_to_int);
  ok(SPVM::TestCase::Operator::TypeCast->double_to_long);
  ok(SPVM::TestCase::Operator::TypeCast->double_to_float);
}

# Convert type - floating point widening convertion
{
  ok(SPVM::TestCase::Operator::TypeCast->byte_to_float);
  ok(SPVM::TestCase::Operator::TypeCast->short_to_float);
  ok(SPVM::TestCase::Operator::TypeCast->int_to_float);
  ok(SPVM::TestCase::Operator::TypeCast->long_to_float);
  ok(SPVM::TestCase::Operator::TypeCast->byte_to_double);
  ok(SPVM::TestCase::Operator::TypeCast->short_to_double);
  ok(SPVM::TestCase::Operator::TypeCast->int_to_double);
  ok(SPVM::TestCase::Operator::TypeCast->long_to_double);
  ok(SPVM::TestCase::Operator::TypeCast->float_to_double);
}

# Convert type - integral number widning convertion
{
  ok(SPVM::TestCase::Operator::TypeCast->byte_to_short_plus);
  ok(SPVM::TestCase::Operator::TypeCast->byte_to_short_minus);
  ok(SPVM::TestCase::Operator::TypeCast->byte_to_int_plus);
  ok(SPVM::TestCase::Operator::TypeCast->byte_to_int_minus);
  ok(SPVM::TestCase::Operator::TypeCast->byte_to_long_plus);
  ok(SPVM::TestCase::Operator::TypeCast->byte_to_long_minus);
  ok(SPVM::TestCase::Operator::TypeCast->short_to_int_plus);
  ok(SPVM::TestCase::Operator::TypeCast->short_to_int_minus);
  ok(SPVM::TestCase::Operator::TypeCast->short_to_long_plus);
  ok(SPVM::TestCase::Operator::TypeCast->short_to_long_minus);
  ok(SPVM::TestCase::Operator::TypeCast->int_to_long_plus);
  ok(SPVM::TestCase::Operator::TypeCast->int_to_long_minus);
}

# Convert type - same type
{
  ok(SPVM::TestCase::Operator::TypeCast->long_to_long);
  ok(SPVM::TestCase::Operator::TypeCast->int_to_int);
  ok(SPVM::TestCase::Operator::TypeCast->short_to_short);
  ok(SPVM::TestCase::Operator::TypeCast->byte_to_byte);
}

# Convert type - integral number narrowing convertion
{
  ok(SPVM::TestCase::Operator::TypeCast->long_to_int);
  ok(SPVM::TestCase::Operator::TypeCast->long_to_short);
  ok(SPVM::TestCase::Operator::TypeCast->long_to_byte);
  ok(SPVM::TestCase::Operator::TypeCast->int_to_short);
  ok(SPVM::TestCase::Operator::TypeCast->int_to_byte);
  ok(SPVM::TestCase::Operator::TypeCast->short_to_byte);
}

# Convert to string
{
  ok(SPVM::TestCase::Operator::TypeCast->byte_to_string);
  ok(SPVM::TestCase::Operator::TypeCast->short_to_string);
  ok(SPVM::TestCase::Operator::TypeCast->int_to_string);
  ok(SPVM::TestCase::Operator::TypeCast->long_to_string);
  ok(SPVM::TestCase::Operator::TypeCast->float_to_string);
  ok(SPVM::TestCase::Operator::TypeCast->double_to_string);
}

{
  ok(SPVM::TestCase::Operator::TypeCast->to_numeric_array);
  ok(SPVM::TestCase::Operator::TypeCast->to_object_array);
  ok(SPVM::TestCase::Operator::TypeCast->to_callback_array);
  ok(SPVM::TestCase::Operator::TypeCast->to_any_object);
  ok(SPVM::TestCase::Operator::TypeCast->to_callback);
  ok(SPVM::TestCase::Operator::TypeCast->undef_to_any_object);
  ok(SPVM::TestCase::Operator::TypeCast->undef_to_callback);
  ok(SPVM::TestCase::Operator::TypeCast->undef_to_object2);
  ok(SPVM::TestCase::Operator::TypeCast->undef_to_ref);

  ok(SPVM::TestCase::Operator::TypeCast->byte_to_byte_object);
  ok(SPVM::TestCase::Operator::TypeCast->short_to_short_object);
  ok(SPVM::TestCase::Operator::TypeCast->int_to_int_object);
  ok(SPVM::TestCase::Operator::TypeCast->long_to_long_object);
  ok(SPVM::TestCase::Operator::TypeCast->float_to_float_object);
  ok(SPVM::TestCase::Operator::TypeCast->double_to_double_object);
  
  ok(SPVM::TestCase::Operator::TypeCast->byte_to_any_object);
  ok(SPVM::TestCase::Operator::TypeCast->short_to_any_object);
  ok(SPVM::TestCase::Operator::TypeCast->int_to_any_object);
  ok(SPVM::TestCase::Operator::TypeCast->long_to_any_object);
  ok(SPVM::TestCase::Operator::TypeCast->float_to_any_object);
  ok(SPVM::TestCase::Operator::TypeCast->double_to_any_object);
  
  ok(SPVM::TestCase::Operator::TypeCast->byte_object_to_byte);
  ok(SPVM::TestCase::Operator::TypeCast->short_object_to_short);
  ok(SPVM::TestCase::Operator::TypeCast->int_object_to_int);
  ok(SPVM::TestCase::Operator::TypeCast->long_object_to_long);
  ok(SPVM::TestCase::Operator::TypeCast->float_object_to_float);
  ok(SPVM::TestCase::Operator::TypeCast->double_object_to_double);
  
  ok(SPVM::TestCase::Operator::TypeCast->any_object_to_byte);
  ok(SPVM::TestCase::Operator::TypeCast->any_object_to_short);
  ok(SPVM::TestCase::Operator::TypeCast->any_object_to_int);
  ok(SPVM::TestCase::Operator::TypeCast->any_object_to_long);
  ok(SPVM::TestCase::Operator::TypeCast->any_object_to_float);
  ok(SPVM::TestCase::Operator::TypeCast->any_object_to_double); 
}

# Convert to string
{
  ok(SPVM::TestCase::Operator::TypeCast->string_to_byte);
  ok(SPVM::TestCase::Operator::TypeCast->string_to_short);
  ok(SPVM::TestCase::Operator::TypeCast->string_to_int);
  ok(SPVM::TestCase::Operator::TypeCast->string_to_long);
  ok(SPVM::TestCase::Operator::TypeCast->string_to_float);
  ok(SPVM::TestCase::Operator::TypeCast->string_to_double);
  ok(SPVM::TestCase::Operator::TypeCast->string_to_byte_array);
}

# Convert to string
{
  ok(SPVM::TestCase::Operator::TypeCast->postfix);
}

# Extra
{
  # TypeCast
  {
    ok(SPVM::TestCase::Operator::TypeCast->to_numeric_type);
    ok(SPVM::TestCase::Operator::TypeCast->to_mulnum_type);
    ok(SPVM::TestCase::Operator::TypeCast->to_reference_type);
    ok(SPVM::TestCase::Operator::TypeCast->to_string);
  }
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
