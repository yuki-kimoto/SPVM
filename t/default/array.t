use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Array
{
  # int array and get length
  {
    ok(TestCase->get_array_length_at());
    ok(TestCase->get_array_length_len());
    ok(TestCase->get_array_length_undef());
  }

  # array - set and get array element, first element
  {
    my $element = TestCase->array_set_and_get_array_element_first();
    is($element, 345);
  }
  
  # array - set and get array element, last element
  {
    my $element = TestCase->array_set_and_get_array_element_last();
    is($element, 298);
  }

  # array - culcurate sum by for
  {
    my $total = TestCase->array_culcurate_sum_by_for();
    is($total, 6);
  }
}

# Array default
{
  ok(TestCase->array_default_zero_memory_pool());
  ok(TestCase->array_default_zero_not_memory_pool());
}

# Array initialization
{
  ok(TestCase->array_init_byte());
  ok(TestCase->array_init_short());
  ok(TestCase->array_init_int());
  ok(TestCase->array_init_long());
  ok(TestCase->array_init_float());
  ok(TestCase->array_init_double());
}

# Array
{
  ok(TestCase->array());
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
