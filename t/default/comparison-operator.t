use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use utf8;

use Test::More 'no_plan';

use SPVM 'TestCase::ComparisonOperator';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Spec tests
{
  # Bool
  {
    ok(TestCase::ComparisonOperator->bool_true_byte);
    ok(TestCase::ComparisonOperator->bool_true_short);
    ok(TestCase::ComparisonOperator->bool_true_int);
    ok(TestCase::ComparisonOperator->bool_true_long);
    ok(TestCase::ComparisonOperator->bool_true_float);
    ok(TestCase::ComparisonOperator->bool_true_double);
    ok(TestCase::ComparisonOperator->bool_true_object);

    ok(TestCase::ComparisonOperator->bool_false_byte);
    ok(TestCase::ComparisonOperator->bool_false_short);
    ok(TestCase::ComparisonOperator->bool_false_int);
    ok(TestCase::ComparisonOperator->bool_false_long);
    ok(TestCase::ComparisonOperator->bool_false_float);
    ok(TestCase::ComparisonOperator->bool_false_double);
    ok(TestCase::ComparisonOperator->bool_false_object);

    ok(TestCase::ComparisonOperator->bool_else);
    ok(TestCase::ComparisonOperator->bool_elsif);
    ok(TestCase::ComparisonOperator->bool_elsbool_2);
    ok(TestCase::ComparisonOperator->bool_duplicate);
  }

  # a > b
  {
    ok(TestCase::ComparisonOperator->numeric_gt_byte_left_big);
    ok(TestCase::ComparisonOperator->numeric_gt_byte_same);
    ok(TestCase::ComparisonOperator->numeric_gt_byte_right_big);
    ok(TestCase::ComparisonOperator->numeric_gt_short_left_big);
    ok(TestCase::ComparisonOperator->numeric_gt_short_same);
    ok(TestCase::ComparisonOperator->numeric_gt_short_right_big);
    ok(TestCase::ComparisonOperator->numeric_gt_int_left_big);
    ok(TestCase::ComparisonOperator->numeric_gt_int_same);
    ok(TestCase::ComparisonOperator->numeric_gt_int_right_big);
    ok(TestCase::ComparisonOperator->numeric_gt_long_left_big);
    ok(TestCase::ComparisonOperator->numeric_gt_long_same);
    ok(TestCase::ComparisonOperator->numeric_gt_long_right_big);
    ok(TestCase::ComparisonOperator->numeric_gt_float_left_big);
    ok(TestCase::ComparisonOperator->numeric_gt_float_same);
    ok(TestCase::ComparisonOperator->numeric_gt_float_right_big);
    ok(TestCase::ComparisonOperator->numeric_gt_double_left_big);
    ok(TestCase::ComparisonOperator->numeric_gt_double_same);
    ok(TestCase::ComparisonOperator->numeric_gt_double_right_big);
  }

  # a >= b
  {
    ok(TestCase::ComparisonOperator->numeric_ge_byte_left_big);
    ok(TestCase::ComparisonOperator->numeric_ge_byte_same);
    ok(TestCase::ComparisonOperator->numeric_ge_byte_right_big);
    ok(TestCase::ComparisonOperator->numeric_ge_short_left_big);
    ok(TestCase::ComparisonOperator->numeric_ge_short_same);
    ok(TestCase::ComparisonOperator->numeric_ge_short_right_big);
    ok(TestCase::ComparisonOperator->numeric_ge_int_left_big);
    ok(TestCase::ComparisonOperator->numeric_ge_int_same);
    ok(TestCase::ComparisonOperator->numeric_ge_int_right_big);
    ok(TestCase::ComparisonOperator->numeric_ge_long_left_big);
    ok(TestCase::ComparisonOperator->numeric_ge_long_same);
    ok(TestCase::ComparisonOperator->numeric_ge_long_right_big);
    ok(TestCase::ComparisonOperator->numeric_ge_float_left_big);
    ok(TestCase::ComparisonOperator->numeric_ge_float_same);
    ok(TestCase::ComparisonOperator->numeric_ge_float_right_big);
    ok(TestCase::ComparisonOperator->numeric_ge_double_left_big);
    ok(TestCase::ComparisonOperator->numeric_ge_double_same);
    ok(TestCase::ComparisonOperator->numeric_ge_double_right_big);
  }

  # a < b
  {
    ok(TestCase::ComparisonOperator->numeric_lt_byte_left_big);
    ok(TestCase::ComparisonOperator->numeric_lt_byte_same);
    ok(TestCase::ComparisonOperator->numeric_lt_byte_right_big);
    ok(TestCase::ComparisonOperator->numeric_lt_short_left_big);
    ok(TestCase::ComparisonOperator->numeric_lt_short_same);
    ok(TestCase::ComparisonOperator->numeric_lt_short_right_big);
    ok(TestCase::ComparisonOperator->numeric_lt_int_left_big);
    ok(TestCase::ComparisonOperator->numeric_lt_int_same);
    ok(TestCase::ComparisonOperator->numeric_lt_int_right_big);
    ok(TestCase::ComparisonOperator->numeric_lt_long_left_big);
    ok(TestCase::ComparisonOperator->numeric_lt_long_same);
    ok(TestCase::ComparisonOperator->numeric_lt_long_right_big);
    ok(TestCase::ComparisonOperator->numeric_lt_float_left_big);
    ok(TestCase::ComparisonOperator->numeric_lt_float_same);
    ok(TestCase::ComparisonOperator->numeric_lt_float_right_big);
    ok(TestCase::ComparisonOperator->numeric_lt_double_left_big);
    ok(TestCase::ComparisonOperator->numeric_lt_double_same);
    ok(TestCase::ComparisonOperator->numeric_lt_double_right_big);
  }

  # a <= b
  {
    ok(TestCase::ComparisonOperator->numeric_le_byte_left_big);
    ok(TestCase::ComparisonOperator->numeric_le_byte_same);
    ok(TestCase::ComparisonOperator->numeric_le_byte_right_big);
    ok(TestCase::ComparisonOperator->numeric_le_short_left_big);
    ok(TestCase::ComparisonOperator->numeric_le_short_same);
    ok(TestCase::ComparisonOperator->numeric_le_short_right_big);
    ok(TestCase::ComparisonOperator->numeric_le_int_left_big);
    ok(TestCase::ComparisonOperator->numeric_le_int_same);
    ok(TestCase::ComparisonOperator->numeric_le_int_right_big);
    ok(TestCase::ComparisonOperator->numeric_le_long_left_big);
    ok(TestCase::ComparisonOperator->numeric_le_long_same);
    ok(TestCase::ComparisonOperator->numeric_le_long_right_big);
    ok(TestCase::ComparisonOperator->numeric_le_float_left_big);
    ok(TestCase::ComparisonOperator->numeric_le_float_same);
    ok(TestCase::ComparisonOperator->numeric_le_float_right_big);
    ok(TestCase::ComparisonOperator->numeric_le_double_left_big);
    ok(TestCase::ComparisonOperator->numeric_le_double_same);
    ok(TestCase::ComparisonOperator->numeric_le_double_right_big);
  }

  # a == b
  {
    ok(TestCase::ComparisonOperator->numeric_eq_byte_same);
    ok(TestCase::ComparisonOperator->numeric_eq_byte_different);
    ok(TestCase::ComparisonOperator->numeric_eq_short_same);
    ok(TestCase::ComparisonOperator->numeric_eq_short_different);
    ok(TestCase::ComparisonOperator->numeric_eq_int_same);
    ok(TestCase::ComparisonOperator->numeric_eq_int_different);
    ok(TestCase::ComparisonOperator->numeric_eq_long_same);
    ok(TestCase::ComparisonOperator->numeric_eq_long_different);
    ok(TestCase::ComparisonOperator->numeric_eq_float_same);
    ok(TestCase::ComparisonOperator->numeric_eq_float_different);
    ok(TestCase::ComparisonOperator->numeric_eq_double_same);
    ok(TestCase::ComparisonOperator->numeric_eq_double_different);
    ok(TestCase::ComparisonOperator->numeric_eq_object_same);
    ok(TestCase::ComparisonOperator->numeric_eq_object_different);
    ok(TestCase::ComparisonOperator->numeric_eq_undef);
  }

  # a != b
  {
    ok(TestCase::ComparisonOperator->numeric_ne_byte_same);
    ok(TestCase::ComparisonOperator->numeric_ne_byte_different);
    ok(TestCase::ComparisonOperator->numeric_ne_short_same);
    ok(TestCase::ComparisonOperator->numeric_ne_short_different);
    ok(TestCase::ComparisonOperator->numeric_ne_int_same);
    ok(TestCase::ComparisonOperator->numeric_ne_int_different);
    ok(TestCase::ComparisonOperator->numeric_ne_long_same);
    ok(TestCase::ComparisonOperator->numeric_ne_long_different);
    ok(TestCase::ComparisonOperator->numeric_ne_float_same);
    ok(TestCase::ComparisonOperator->numeric_ne_float_different);
    ok(TestCase::ComparisonOperator->numeric_ne_double_same);
    ok(TestCase::ComparisonOperator->numeric_ne_double_different);
    ok(TestCase::ComparisonOperator->numeric_ne_object_same);
    ok(TestCase::ComparisonOperator->numeric_ne_object_different);
    ok(TestCase::ComparisonOperator->numeric_ne_undef);
  }

  # String comparison operator
  {
    {
      ok(TestCase::ComparisonOperator->string_eq);
      ok(TestCase::ComparisonOperator->string_ne);
      ok(TestCase::ComparisonOperator->string_gt);
      ok(TestCase::ComparisonOperator->string_ge);
      ok(TestCase::ComparisonOperator->string_lt);
      ok(TestCase::ComparisonOperator->string_le);
    }
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
