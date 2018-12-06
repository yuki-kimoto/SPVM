use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use utf8;

use Test::More 'no_plan';

use SPVM 'TestCase::ComparisonOperator';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# String comparison operator
{
  {
    ok(TestCase::ComparisonOperator->string_comparison_operator);
  }
}

# Bool
{
  ok(TestCase::ComparisonOperator->if_true_byte);
  ok(TestCase::ComparisonOperator->if_true_short);
  ok(TestCase::ComparisonOperator->if_true_int);
  ok(TestCase::ComparisonOperator->if_true_long);
  ok(TestCase::ComparisonOperator->if_true_float);
  ok(TestCase::ComparisonOperator->if_true_double);
  ok(TestCase::ComparisonOperator->if_true_object);

  ok(TestCase::ComparisonOperator->if_false_byte);
  ok(TestCase::ComparisonOperator->if_false_short);
  ok(TestCase::ComparisonOperator->if_false_int);
  ok(TestCase::ComparisonOperator->if_false_long);
  ok(TestCase::ComparisonOperator->if_false_float);
  ok(TestCase::ComparisonOperator->if_false_double);
  ok(TestCase::ComparisonOperator->if_false_object);

  ok(TestCase::ComparisonOperator->if_else);
  ok(TestCase::ComparisonOperator->if_elsif);
  ok(TestCase::ComparisonOperator->if_elsif_2);
  ok(TestCase::ComparisonOperator->if_duplicate);
}

# a > b
{
  ok(TestCase::ComparisonOperator->if_gt_byte_left_big);
  ok(TestCase::ComparisonOperator->if_gt_byte_same);
  ok(TestCase::ComparisonOperator->if_gt_byte_right_big);
  ok(TestCase::ComparisonOperator->if_gt_short_left_big);
  ok(TestCase::ComparisonOperator->if_gt_short_same);
  ok(TestCase::ComparisonOperator->if_gt_short_right_big);
  ok(TestCase::ComparisonOperator->if_gt_int_left_big);
  ok(TestCase::ComparisonOperator->if_gt_int_same);
  ok(TestCase::ComparisonOperator->if_gt_int_right_big);
  ok(TestCase::ComparisonOperator->if_gt_long_left_big);
  ok(TestCase::ComparisonOperator->if_gt_long_same);
  ok(TestCase::ComparisonOperator->if_gt_long_right_big);
  ok(TestCase::ComparisonOperator->if_gt_float_left_big);
  ok(TestCase::ComparisonOperator->if_gt_float_same);
  ok(TestCase::ComparisonOperator->if_gt_float_right_big);
  ok(TestCase::ComparisonOperator->if_gt_double_left_big);
  ok(TestCase::ComparisonOperator->if_gt_double_same);
  ok(TestCase::ComparisonOperator->if_gt_double_right_big);
}

# a >= b
{
  ok(TestCase::ComparisonOperator->if_ge_byte_left_big);
  ok(TestCase::ComparisonOperator->if_ge_byte_same);
  ok(TestCase::ComparisonOperator->if_ge_byte_right_big);
  ok(TestCase::ComparisonOperator->if_ge_short_left_big);
  ok(TestCase::ComparisonOperator->if_ge_short_same);
  ok(TestCase::ComparisonOperator->if_ge_short_right_big);
  ok(TestCase::ComparisonOperator->if_ge_int_left_big);
  ok(TestCase::ComparisonOperator->if_ge_int_same);
  ok(TestCase::ComparisonOperator->if_ge_int_right_big);
  ok(TestCase::ComparisonOperator->if_ge_long_left_big);
  ok(TestCase::ComparisonOperator->if_ge_long_same);
  ok(TestCase::ComparisonOperator->if_ge_long_right_big);
  ok(TestCase::ComparisonOperator->if_ge_float_left_big);
  ok(TestCase::ComparisonOperator->if_ge_float_same);
  ok(TestCase::ComparisonOperator->if_ge_float_right_big);
  ok(TestCase::ComparisonOperator->if_ge_double_left_big);
  ok(TestCase::ComparisonOperator->if_ge_double_same);
  ok(TestCase::ComparisonOperator->if_ge_double_right_big);
}

# a < b
{
  ok(TestCase::ComparisonOperator->if_lt_byte_left_big);
  ok(TestCase::ComparisonOperator->if_lt_byte_same);
  ok(TestCase::ComparisonOperator->if_lt_byte_right_big);
  ok(TestCase::ComparisonOperator->if_lt_short_left_big);
  ok(TestCase::ComparisonOperator->if_lt_short_same);
  ok(TestCase::ComparisonOperator->if_lt_short_right_big);
  ok(TestCase::ComparisonOperator->if_lt_int_left_big);
  ok(TestCase::ComparisonOperator->if_lt_int_same);
  ok(TestCase::ComparisonOperator->if_lt_int_right_big);
  ok(TestCase::ComparisonOperator->if_lt_long_left_big);
  ok(TestCase::ComparisonOperator->if_lt_long_same);
  ok(TestCase::ComparisonOperator->if_lt_long_right_big);
  ok(TestCase::ComparisonOperator->if_lt_float_left_big);
  ok(TestCase::ComparisonOperator->if_lt_float_same);
  ok(TestCase::ComparisonOperator->if_lt_float_right_big);
  ok(TestCase::ComparisonOperator->if_lt_double_left_big);
  ok(TestCase::ComparisonOperator->if_lt_double_same);
  ok(TestCase::ComparisonOperator->if_lt_double_right_big);
}

# a <= b
{
  ok(TestCase::ComparisonOperator->if_le_byte_left_big);
  ok(TestCase::ComparisonOperator->if_le_byte_same);
  ok(TestCase::ComparisonOperator->if_le_byte_right_big);
  ok(TestCase::ComparisonOperator->if_le_short_left_big);
  ok(TestCase::ComparisonOperator->if_le_short_same);
  ok(TestCase::ComparisonOperator->if_le_short_right_big);
  ok(TestCase::ComparisonOperator->if_le_int_left_big);
  ok(TestCase::ComparisonOperator->if_le_int_same);
  ok(TestCase::ComparisonOperator->if_le_int_right_big);
  ok(TestCase::ComparisonOperator->if_le_long_left_big);
  ok(TestCase::ComparisonOperator->if_le_long_same);
  ok(TestCase::ComparisonOperator->if_le_long_right_big);
  ok(TestCase::ComparisonOperator->if_le_float_left_big);
  ok(TestCase::ComparisonOperator->if_le_float_same);
  ok(TestCase::ComparisonOperator->if_le_float_right_big);
  ok(TestCase::ComparisonOperator->if_le_double_left_big);
  ok(TestCase::ComparisonOperator->if_le_double_same);
  ok(TestCase::ComparisonOperator->if_le_double_right_big);
}

# a == b
{
  ok(TestCase::ComparisonOperator->if_eq_byte_same);
  ok(TestCase::ComparisonOperator->if_eq_byte_different);
  ok(TestCase::ComparisonOperator->if_eq_short_same);
  ok(TestCase::ComparisonOperator->if_eq_short_different);
  ok(TestCase::ComparisonOperator->if_eq_int_same);
  ok(TestCase::ComparisonOperator->if_eq_int_different);
  ok(TestCase::ComparisonOperator->if_eq_long_same);
  ok(TestCase::ComparisonOperator->if_eq_long_different);
  ok(TestCase::ComparisonOperator->if_eq_float_same);
  ok(TestCase::ComparisonOperator->if_eq_float_different);
  ok(TestCase::ComparisonOperator->if_eq_double_same);
  ok(TestCase::ComparisonOperator->if_eq_double_different);
  ok(TestCase::ComparisonOperator->if_eq_object_same);
  ok(TestCase::ComparisonOperator->if_eq_object_different);
  ok(TestCase::ComparisonOperator->if_eq_undef);
}

# a != b
{
  ok(TestCase::ComparisonOperator->if_ne_byte_same);
  ok(TestCase::ComparisonOperator->if_ne_byte_different);
  ok(TestCase::ComparisonOperator->if_ne_short_same);
  ok(TestCase::ComparisonOperator->if_ne_short_different);
  ok(TestCase::ComparisonOperator->if_ne_int_same);
  ok(TestCase::ComparisonOperator->if_ne_int_different);
  ok(TestCase::ComparisonOperator->if_ne_long_same);
  ok(TestCase::ComparisonOperator->if_ne_long_different);
  ok(TestCase::ComparisonOperator->if_ne_float_same);
  ok(TestCase::ComparisonOperator->if_ne_float_different);
  ok(TestCase::ComparisonOperator->if_ne_double_same);
  ok(TestCase::ComparisonOperator->if_ne_double_different);
  ok(TestCase::ComparisonOperator->if_ne_object_same);
  ok(TestCase::ComparisonOperator->if_ne_object_different);
  ok(TestCase::ComparisonOperator->if_ne_undef);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
