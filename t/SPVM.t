use strict;
use warnings;
use Data::Dumper;

use Test::More 'no_plan';;

my $file = 't/SPVM.t';

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase'; my $use_test_line = __LINE__;
use SPVM 'std'; my $use_std_line = __LINE__;

is_deeply(
  \@SPVM::PACKAGE_INFOS,
  [
    {name => 'TestCase', file => $file, line => $use_test_line},
    {name => 'std', file => $file, line => $use_std_line}
  ]
);

# constant
{
  is(SPVM::TestCase::load_constant_int_min(), -2147483647);
  is(SPVM::TestCase::load_constant_int_m2(), -2);
  is(SPVM::TestCase::load_constant_int_m1(), -1);
  is(SPVM::TestCase::load_constant_int_0(), 0);
  is(SPVM::TestCase::load_constant_int_1(), 1);
  is(SPVM::TestCase::load_constant_int_2(), 2);
  is(SPVM::TestCase::load_constant_int_3(), 3);
  is(SPVM::TestCase::load_constant_int_4(), 4);
  is(SPVM::TestCase::load_constant_int_5(), 5);
  is(SPVM::TestCase::load_constant_int_6(), 6);
  is(SPVM::TestCase::load_constant_int_max(), 2147483647);
}

# call_sub
{
  ok(SPVM::TestCase::call_sub_args_int(1, 2147483647, -2147483647));
  ok(SPVM::TestCase::call_sub_args_long(1, 9223372036854775807, -9223372036854775808));
}

# If
{
  ok(SPVM::TestCase::if_true_byte());
  ok(SPVM::TestCase::if_true_short());
  ok(SPVM::TestCase::if_true_int());
  ok(SPVM::TestCase::if_true_long());
  ok(SPVM::TestCase::if_true_float());
  ok(SPVM::TestCase::if_true_double());
  ok(SPVM::TestCase::if_true_object());

  ok(SPVM::TestCase::if_false_byte());
  ok(SPVM::TestCase::if_false_short());
  ok(SPVM::TestCase::if_false_int());
  ok(SPVM::TestCase::if_false_long());
  ok(SPVM::TestCase::if_false_float());
  ok(SPVM::TestCase::if_false_double());
  ok(SPVM::TestCase::if_false_object());

  ok(SPVM::TestCase::if_else());
  ok(SPVM::TestCase::if_elsif());
  ok(SPVM::TestCase::if_elsif_2());
  ok(SPVM::TestCase::if_duplicate());
  
}

# If a > b
{
  ok(SPVM::TestCase::if_gt_byte_left_big());
  ok(SPVM::TestCase::if_gt_byte_same());
  ok(SPVM::TestCase::if_gt_byte_right_big());
  ok(SPVM::TestCase::if_gt_short_left_big());
  ok(SPVM::TestCase::if_gt_short_same());
  ok(SPVM::TestCase::if_gt_short_right_big());
  ok(SPVM::TestCase::if_gt_int_left_big());
  ok(SPVM::TestCase::if_gt_int_same());
  ok(SPVM::TestCase::if_gt_int_right_big());
  ok(SPVM::TestCase::if_gt_long_left_big());
  ok(SPVM::TestCase::if_gt_long_same());
  ok(SPVM::TestCase::if_gt_long_right_big());
  ok(SPVM::TestCase::if_gt_float_left_big());
  ok(SPVM::TestCase::if_gt_float_same());
  ok(SPVM::TestCase::if_gt_float_right_big());
  ok(SPVM::TestCase::if_gt_double_left_big());
  ok(SPVM::TestCase::if_gt_double_same());
  ok(SPVM::TestCase::if_gt_double_right_big());
}

# Number literal
{
  ok(SPVM::TestCase::number_literal_hex_int());
  ok(SPVM::TestCase::number_literal_hex_int_max());
  ok(SPVM::TestCase::number_literal_hex_long());
  ok(SPVM::TestCase::number_literal_hex_long_max());
}

# Bit shift left
{
  ok(SPVM::TestCase::bit_shift_left_byte());
  ok(SPVM::TestCase::bit_shift_left_byte_max());
  ok(SPVM::TestCase::bit_shift_left_byte_overflow());
  ok(SPVM::TestCase::bit_shift_left_short());
  ok(SPVM::TestCase::bit_shift_left_short_max());
  ok(SPVM::TestCase::bit_shift_left_short_overflow());
  ok(SPVM::TestCase::bit_shift_left_int());
  ok(SPVM::TestCase::bit_shift_left_int_max());
  ok(SPVM::TestCase::bit_shift_left_int_overflow());
  ok(SPVM::TestCase::bit_shift_left_long());
  ok(SPVM::TestCase::bit_shift_left_long_max());
  ok(SPVM::TestCase::bit_shift_left_long_overflow());
}

# Bit shift right logical
{
  ok(SPVM::TestCase::bit_shift_right_logical_byte());
  ok(SPVM::TestCase::bit_shift_right_logical_short());
  ok(SPVM::TestCase::bit_shift_right_logical_int());
  ok(SPVM::TestCase::bit_shift_right_logical_long());
}

# Bit shift right
{
  ok(SPVM::TestCase::bit_shift_right_byte());
  ok(SPVM::TestCase::bit_shift_right_short());
  ok(SPVM::TestCase::bit_shift_right_int());
  ok(SPVM::TestCase::bit_shift_right_long());
}


# Array
{
  # int array and get length
  {
    my $len = SPVM::TestCase::array_malloc_int_array_and_get_length();
    is($len, 3);
  }

  # array - set and get array element, first element
  {
    my $element = SPVM::TestCase::array_set_and_get_array_element_first();
    is($element, 345);
  }
  
  # array - set and get array element, last element
  {
    my $element = SPVM::TestCase::array_set_and_get_array_element_last();
    is($element, 298);
  }

  # array - culcurate sum by for
  {
    my $total = SPVM::TestCase::array_culcurate_sum_by_for();
    is($total, 6);
  }
}

# byte
{
  my $total = SPVM::TestCase::sum_byte(8, 3);
  is($total, 11);
}

# short
{
  my $total = SPVM::TestCase::sum_short(8, 3);
  is($total, 11);
}

# int
{
  my $total = SPVM::TestCase::sum_int(8, 3);
  is($total, 11);
}

# long
{
  my $total = SPVM::TestCase::sum_long(8, 3);
  is($total, 11);
}
{
  my $total = SPVM::TestCase::sum_long(9223372036854775806, 1);
  is($total, 9223372036854775807);
}

# float
{
  my $total = SPVM::TestCase::sum_float(0.25, 0.25);
  cmp_ok($total, '==', 0.5);
}

# double
{
  my $total = SPVM::TestCase::sum_double(0.25, 0.25);
  cmp_ok($total, '==', 0.5);
}

# for
{
  my $total = SPVM::TestCase::for_basic();
  cmp_ok($total, '==', 6);
}
