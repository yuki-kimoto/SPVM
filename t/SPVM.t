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

# Array
{
  # int array and get length
  {
    my $len = SPVM::TestCase::array_malloc_int_array_and_length();
    is($len, 3);
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

# if
{
  # if gt int left big
  { 
    my $success = SPVM::TestCase::if_gt_int_left_big();
    ok($success == 1);
  }

  # if gt int same
  { 
    my $success = SPVM::TestCase::if_gt_int_same();
    ok($success == 0);
  }

  # if gt int right big
  { 
    my $success = SPVM::TestCase::if_gt_int_right_big();
    ok($success == 0);
  }
}

