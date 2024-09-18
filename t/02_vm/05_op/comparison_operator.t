use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use utf8;

use Test::More;

use SPVM 'TestCase::Operator::ComparisonOperator';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count();

# Spec tests
{
  # a > b
  {
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt_byte_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt_byte_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt_byte_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt_short_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt_short_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt_short_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt_int_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt_int_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt_int_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt_long_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt_long_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt_long_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt_float_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt_float_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt_float_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt_double_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt_double_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_gt_double_right_big);
  }

  # a >= b
  {
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge_byte_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge_byte_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge_byte_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge_short_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge_short_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge_short_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge_int_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge_int_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge_int_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge_long_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge_long_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge_long_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge_float_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge_float_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge_float_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge_double_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge_double_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ge_double_right_big);
  }

  # a < b
  {
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt_byte_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt_byte_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt_byte_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt_short_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt_short_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt_short_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt_int_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt_int_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt_int_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt_long_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt_long_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt_long_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt_float_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt_float_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt_float_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt_double_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt_double_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_lt_double_right_big);
  }

  # a <= b
  {
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le_byte_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le_byte_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le_byte_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le_short_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le_short_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le_short_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le_int_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le_int_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le_int_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le_long_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le_long_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le_long_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le_float_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le_float_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le_float_right_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le_double_left_big);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le_double_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_le_double_right_big);
  }

  # a == b
  {
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_eq_byte_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_eq_byte_different);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_eq_short_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_eq_short_different);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_eq_int_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_eq_int_different);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_eq_long_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_eq_long_different);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_eq_float_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_eq_float_different);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_eq_double_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_eq_double_different);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_eq_object_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_eq_object_different);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_eq_undef);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_eq_ref_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_eq_ref_different);
  }

  # a != b
  {
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ne_byte_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ne_byte_different);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ne_short_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ne_short_different);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ne_int_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ne_int_different);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ne_long_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ne_long_different);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ne_float_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ne_float_different);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ne_double_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ne_double_different);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ne_object_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ne_object_different);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ne_undef);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ne_ref_same);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_ne_ref_different);
  }

  # a <=> b
  {
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_cmp_byte);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_cmp_short);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_cmp_int);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_cmp_long);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_cmp_float);
    ok(SPVM::TestCase::Operator::ComparisonOperator->numeric_cmp_double);
  }

  # String comparison operator
  {
    {
      ok(SPVM::TestCase::Operator::ComparisonOperator->string_eq);
      ok(SPVM::TestCase::Operator::ComparisonOperator->string_ne);
      ok(SPVM::TestCase::Operator::ComparisonOperator->string_gt);
      ok(SPVM::TestCase::Operator::ComparisonOperator->string_ge);
      ok(SPVM::TestCase::Operator::ComparisonOperator->string_lt);
      ok(SPVM::TestCase::Operator::ComparisonOperator->string_le);
      ok(SPVM::TestCase::Operator::ComparisonOperator->string_cmp);
    }
  }
}

# All object is freed
$api->set_exception(undef);
my $end_memory_blocks_count = $api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
