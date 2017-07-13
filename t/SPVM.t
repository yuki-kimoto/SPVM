use strict;
use warnings;
use Data::Dumper;

use Test::More 'no_plan';;

my $file = 't/SPVM.t';

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase'; my $use_test_line = __LINE__;
use SPVM 'std'; my $use_std_line = __LINE__;

use SPVM::Object;

is_deeply(
  \@SPVM::PACKAGE_INFOS,
  [
    {name => 'TestCase', file => $file, line => $use_test_line},
    {name => 'std', file => $file, line => $use_std_line}
  ]
);

# Add
{
  is(SPVM::TestCase::add_byte_max(), 127);
  is(SPVM::TestCase::add_byte_min(), -127);
  is(SPVM::TestCase::add_byte_overflow(), -128);
  is(SPVM::TestCase::add_short_max(), 32767);
  is(SPVM::TestCase::add_short_min(), -32767);
  is(SPVM::TestCase::add_short_overflow(), -32768);
  is(SPVM::TestCase::add_int_max(), 2147483647);
  is(SPVM::TestCase::add_int_min(), -2147483647);
  is(SPVM::TestCase::add_int_overflow(), -2147483648);
  is(SPVM::TestCase::add_long_max(), 9223372036854775807);
  is(SPVM::TestCase::add_long_min(), -9223372036854775807);
  is(SPVM::TestCase::add_long_overflow(), -9223372036854775808);
}

# call_sub array
{
  # call_sub byte_array
  {
    my $nums = SPVM::byte_array([1, 2, 3]);
    is(SPVM::TestCase::call_sub_byte_array($nums), 6);
  }

  # call_sub short_array
  {
    my $nums = SPVM::short_array([1, 2, 3]);
    is(SPVM::TestCase::call_sub_short_array($nums), 6);
  }

  # call_sub int_array
  {
    my $nums = SPVM::int_array([1, 2, 3]);
    is(SPVM::TestCase::call_sub_int_array($nums), 6);
  }

  # call_sub long_array
  {
    my $nums = SPVM::long_array([1, 2, 3]);
    is(SPVM::TestCase::call_sub_long_array($nums), 6);
  }

  # call_sub float_array
  {
    my $nums = SPVM::float_array([0.5, 0.5, 1.0]);
    is(SPVM::TestCase::call_sub_float_array($nums), 2.0);
  }

  # call_sub double_array
  {
    my $nums = SPVM::double_array([0.5, 0.5, 1.0]);
    is(SPVM::TestCase::call_sub_double_array($nums), 2.0);
  }
}

# SPVM::ArrayObject
{
  my $data_nums = SPVM::ArrayObject->malloc_int_array(3);
  $data_nums->set_int_array_elements([1, 2, 3]);
}

# constant int
{
  is(SPVM::TestCase::load_constant_int_min(), -2147483647);
  is(SPVM::TestCase::load_constant_int_m32769(), -32769);
  is(SPVM::TestCase::load_constant_int_m32768(), -32768);
  is(SPVM::TestCase::load_constant_int_m129(), -129);
  is(SPVM::TestCase::load_constant_int_m128(), -128);
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

# constant long
{
  is(SPVM::TestCase::load_constant_long_min(), -9223372036854775808);
  is(SPVM::TestCase::load_constant_long_m32769(), -32769);
  is(SPVM::TestCase::load_constant_long_m32768(), -32768);
  is(SPVM::TestCase::load_constant_long_m129(), -129);
  is(SPVM::TestCase::load_constant_long_m128(), -128);
  is(SPVM::TestCase::load_constant_long_m2(), -2);
  is(SPVM::TestCase::load_constant_long_m1(), -1);
  is(SPVM::TestCase::load_constant_long_0(), 0);
  is(SPVM::TestCase::load_constant_long_1(), 1);
  is(SPVM::TestCase::load_constant_long_2(), 2);
  is(SPVM::TestCase::load_constant_long_3(), 3);
  is(SPVM::TestCase::load_constant_long_4(), 4);
  is(SPVM::TestCase::load_constant_long_5(), 5);
  is(SPVM::TestCase::load_constant_long_6(), 6);
  is(SPVM::TestCase::load_constant_long_127(), 127);
  is(SPVM::TestCase::load_constant_long_128(), 128);
  is(SPVM::TestCase::load_constant_long_32767(), 32767);
  is(SPVM::TestCase::load_constant_long_32768(), 32768);
  is(SPVM::TestCase::load_constant_long_max(), 9223372036854775807);
}

# constant float
{
  is(SPVM::TestCase::load_constant_float_0(), 0.0);
  is(SPVM::TestCase::load_constant_float_1(), 1.0);
  is(SPVM::TestCase::load_constant_float_0_5(), 0.5);
  is(SPVM::TestCase::load_constant_float_exponent_E_plus(), 0.5E+3);
  is(SPVM::TestCase::load_constant_float_exponent_e_plus(), 0.5e+3);
  is(SPVM::TestCase::load_constant_float_exponent_E_minus(), 62.5E-3);
  is(SPVM::TestCase::load_constant_float_exponent_e_minus(), 62.5e-3);
  is(SPVM::TestCase::load_constant_double_exponent_E_plus(), 0.5E+3);
  is(SPVM::TestCase::load_constant_double_exponent_e_plus(), 0.5e+3);
  is(SPVM::TestCase::load_constant_double_exponent_E_minus(), 62.5E-3);
  is(SPVM::TestCase::load_constant_double_exponent_e_minus(), 62.5e-3);
}

# constant double
{
  is(SPVM::TestCase::load_constant_double_0(), 0.0);
  is(SPVM::TestCase::load_constant_double_1(), 1.0);
  is(SPVM::TestCase::load_constant_double_0_5(), 0.5);
}

# call_sub
{
  ok(SPVM::TestCase::call_sub_args_int(1, 2147483647, -2147483647, 0));
  ok(SPVM::TestCase::call_sub_args_long(1, 9223372036854775807, -9223372036854775808, 0));
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

# If a >= b
{
  ok(SPVM::TestCase::if_ge_byte_left_big());
  ok(SPVM::TestCase::if_ge_byte_same());
  ok(SPVM::TestCase::if_ge_byte_right_big());
  ok(SPVM::TestCase::if_ge_short_left_big());
  ok(SPVM::TestCase::if_ge_short_same());
  ok(SPVM::TestCase::if_ge_short_right_big());
  ok(SPVM::TestCase::if_ge_int_left_big());
  ok(SPVM::TestCase::if_ge_int_same());
  ok(SPVM::TestCase::if_ge_int_right_big());
  ok(SPVM::TestCase::if_ge_long_left_big());
  ok(SPVM::TestCase::if_ge_long_same());
  ok(SPVM::TestCase::if_ge_long_right_big());
  ok(SPVM::TestCase::if_ge_float_left_big());
  ok(SPVM::TestCase::if_ge_float_same());
  ok(SPVM::TestCase::if_ge_float_right_big());
  ok(SPVM::TestCase::if_ge_double_left_big());
  ok(SPVM::TestCase::if_ge_double_same());
  ok(SPVM::TestCase::if_ge_double_right_big());
}

# If a < b
{
  ok(SPVM::TestCase::if_lt_byte_left_big());
  ok(SPVM::TestCase::if_lt_byte_same());
  ok(SPVM::TestCase::if_lt_byte_right_big());
  ok(SPVM::TestCase::if_lt_short_left_big());
  ok(SPVM::TestCase::if_lt_short_same());
  ok(SPVM::TestCase::if_lt_short_right_big());
  ok(SPVM::TestCase::if_lt_int_left_big());
  ok(SPVM::TestCase::if_lt_int_same());
  ok(SPVM::TestCase::if_lt_int_right_big());
  ok(SPVM::TestCase::if_lt_long_left_big());
  ok(SPVM::TestCase::if_lt_long_same());
  ok(SPVM::TestCase::if_lt_long_right_big());
  ok(SPVM::TestCase::if_lt_float_left_big());
  ok(SPVM::TestCase::if_lt_float_same());
  ok(SPVM::TestCase::if_lt_float_right_big());
  ok(SPVM::TestCase::if_lt_double_left_big());
  ok(SPVM::TestCase::if_lt_double_same());
  ok(SPVM::TestCase::if_lt_double_right_big());
}

# If a <= b
{
  ok(SPVM::TestCase::if_le_byte_left_big());
  ok(SPVM::TestCase::if_le_byte_same());
  ok(SPVM::TestCase::if_le_byte_right_big());
  ok(SPVM::TestCase::if_le_short_left_big());
  ok(SPVM::TestCase::if_le_short_same());
  ok(SPVM::TestCase::if_le_short_right_big());
  ok(SPVM::TestCase::if_le_int_left_big());
  ok(SPVM::TestCase::if_le_int_same());
  ok(SPVM::TestCase::if_le_int_right_big());
  ok(SPVM::TestCase::if_le_long_left_big());
  ok(SPVM::TestCase::if_le_long_same());
  ok(SPVM::TestCase::if_le_long_right_big());
  ok(SPVM::TestCase::if_le_float_left_big());
  ok(SPVM::TestCase::if_le_float_same());
  ok(SPVM::TestCase::if_le_float_right_big());
  ok(SPVM::TestCase::if_le_double_left_big());
  ok(SPVM::TestCase::if_le_double_same());
  ok(SPVM::TestCase::if_le_double_right_big());
}

# If a == b
{
  ok(SPVM::TestCase::if_eq_byte_same());
  ok(SPVM::TestCase::if_eq_byte_different());
  ok(SPVM::TestCase::if_eq_short_same());
  ok(SPVM::TestCase::if_eq_short_different());
  ok(SPVM::TestCase::if_eq_int_same());
  ok(SPVM::TestCase::if_eq_int_different());
  ok(SPVM::TestCase::if_eq_long_same());
  ok(SPVM::TestCase::if_eq_long_different());
  ok(SPVM::TestCase::if_eq_float_same());
  ok(SPVM::TestCase::if_eq_float_different());
  ok(SPVM::TestCase::if_eq_double_same());
  ok(SPVM::TestCase::if_eq_double_different());
  ok(SPVM::TestCase::if_eq_object_same());
  ok(SPVM::TestCase::if_eq_object_different());
}

# If a != b
{
  ok(SPVM::TestCase::if_ne_byte_same());
  ok(SPVM::TestCase::if_ne_byte_different());
  ok(SPVM::TestCase::if_ne_short_same());
  ok(SPVM::TestCase::if_ne_short_different());
  ok(SPVM::TestCase::if_ne_int_same());
  ok(SPVM::TestCase::if_ne_int_different());
  ok(SPVM::TestCase::if_ne_long_same());
  ok(SPVM::TestCase::if_ne_long_different());
  ok(SPVM::TestCase::if_ne_float_same());
  ok(SPVM::TestCase::if_ne_float_different());
  ok(SPVM::TestCase::if_ne_double_same());
  ok(SPVM::TestCase::if_ne_double_different());
  ok(SPVM::TestCase::if_ne_object_same());
  ok(SPVM::TestCase::if_ne_object_different());
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
