use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::Array';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# Fat camma
{
  ok(SPVM::TestCase::Operator::Array->array_init_fatcamma);
}

# Array
{
  ok(SPVM::TestCase::Operator::Array->array());
  ok(SPVM::TestCase::Operator::Array->array_store_undef());
}

# Array length
{
  ok(SPVM::TestCase::Operator::Array->array_length_atmark());
  ok(SPVM::TestCase::Operator::Array->array_length_atmark_brace());
  ok(SPVM::TestCase::Operator::Array->array_length_scalar_atmark());
  ok(SPVM::TestCase::Operator::Array->array_length_scalar_atmark_brace());
  ok(SPVM::TestCase::Operator::Array->array_length_undef());
}

# [] Array initialization
{
  ok(SPVM::TestCase::Operator::Array->array_init_empty());
  ok(SPVM::TestCase::Operator::Array->array_init_byte());
  ok(SPVM::TestCase::Operator::Array->array_init_short());
  ok(SPVM::TestCase::Operator::Array->array_init_int());
  ok(SPVM::TestCase::Operator::Array->array_init_long());
  ok(SPVM::TestCase::Operator::Array->array_init_float());
  ok(SPVM::TestCase::Operator::Array->array_init_double());
  ok(SPVM::TestCase::Operator::Array->array_init_object());
}

# {} Array initialization
{
  ok(SPVM::TestCase::Operator::Array->array_init_key_values_empty());
  ok(SPVM::TestCase::Operator::Array->array_init_key_values());
}

# Array default
{
  ok(SPVM::TestCase::Operator::Array->array_default_zero_memory_pool());
  ok(SPVM::TestCase::Operator::Array->array_default_zero_not_memory_pool());
}

# array - set and get array element, first element
{
  my $element = SPVM::TestCase::Operator::Array->array_set_and_get_array_element_first();
  is($element, 345);
}

# array - set and get array element, last element
{
  my $element = SPVM::TestCase::Operator::Array->array_set_and_get_array_element_last();
  is($element, 298);
}

# array - culcurate sum by for
{
  my $total = SPVM::TestCase::Operator::Array->array_culcurate_sum_by_for();
  is($total, 6);
}

# any object array
{
  ok(SPVM::TestCase::Operator::Array->any_object_array);
}

# Clear exception
SPVM::api->set_exception(undef);

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
