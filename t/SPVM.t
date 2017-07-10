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

# Number literal
{
  ok(SPVM::TestCase::number_literal_hex_int());
  ok(SPVM::TestCase::number_literal_hex_int_max());
  ok(SPVM::TestCase::number_literal_hex_long());
  ok(SPVM::TestCase::number_literal_hex_long_max());
}

# if
{
  ok(SPVM::TestCase::if_gt_int_left_big());
  ok(SPVM::TestCase::if_gt_int_same());
  ok(SPVM::TestCase::if_gt_int_right_big());
}


# Bit shift
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
