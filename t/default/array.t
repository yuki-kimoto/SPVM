use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Array';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# big size array
my $array_big_index_long_cant_alloc_memory;

eval {
  TestCase::Array->array_big_index_long
};
if ($@) {
  $array_big_index_long_cant_alloc_memory = 1;
}
SKIP: {
  if ($array_big_index_long_cant_alloc_memory) {
    skip "Can't alloc memory for big size array", 6;
  }
  ok(TestCase::Array->array_big_index_byte);
  ok(TestCase::Array->array_big_index_short);
  ok(TestCase::Array->array_big_index_int);
  ok(TestCase::Array->array_big_index_long);
  ok(TestCase::Array->array_big_index_float);
  ok(TestCase::Array->array_big_index_double);
};

# Max Index array
my $array_max_index_byte_cant_alloc_memory;
eval {
  TestCase::Array->array_max_index_byte
};
if ($@) {
  $array_max_index_byte_cant_alloc_memory = 1;
}
SKIP: {
  if ($array_max_index_byte_cant_alloc_memory) {
    skip "Can't alloc memory for max size index test", 1;
  }
  ok(TestCase::Array->array_max_index_byte);
};


# Fat camma
{
  ok(TestCase::Array->array_init_fatcamma);
}

# Array
{
  ok(TestCase::Array->array());
  ok(TestCase::Array->array_store_undef());
}

# Array length
{
  ok(TestCase::Array->array_length_atmark());
  ok(TestCase::Array->array_length_atmark_brace());
  ok(TestCase::Array->array_length_scalar_atmark());
  ok(TestCase::Array->array_length_scalar_atmark_brace());
  ok(TestCase::Array->array_length_undef());
}

# Array initialization
{
  ok(TestCase::Array->array_init_empty());
  ok(TestCase::Array->array_init_byte());
  ok(TestCase::Array->array_init_short());
  ok(TestCase::Array->array_init_int());
  ok(TestCase::Array->array_init_long());
  ok(TestCase::Array->array_init_float());
  ok(TestCase::Array->array_init_double());
  ok(TestCase::Array->array_init_object());
}

# Array default
{
  ok(TestCase::Array->array_default_zero_memory_pool());
  ok(TestCase::Array->array_default_zero_not_memory_pool());
}

# array - set and get array element, first element
{
  my $element = TestCase::Array->array_set_and_get_array_element_first();
  is($element, 345);
}

# array - set and get array element, last element
{
  my $element = TestCase::Array->array_set_and_get_array_element_last();
  is($element, 298);
}

# array - culcurate sum by for
{
  my $total = TestCase::Array->array_culcurate_sum_by_for();
  is($total, 6);
}

# Clear exception
SPVM::set_exception(undef);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
