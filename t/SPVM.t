# Before 'make install' is performed this script should be runnable with
# 'make test'. After 'make install' it should work as 'perl SPVM.t'

#########################

# change 'tests => 1' to 'tests => last_test_to_print';

use strict;
use warnings;
use Data::Dumper;


use Test::More 'no_plan';;

#########################

# Insert your test code below, the Test::More module is use()ed here so read
# its man page ( perldoc Test::More ) for help writing this test script.

my $file = 't/SPVM.t';

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'XSTest'; my $use_test_line = __LINE__;
use SPVM 'std'; my $use_std_line = __LINE__;

is_deeply(
  \@SPVM::PACKAGE_INFOS,
  [
    {name => 'XSTest', file => $file, line => $use_test_line},
    {name => 'std', file => $file, line => $use_std_line}
  ]
);

# byte
{
  my $total = SPVM::XSTest::sum_byte(8, 3);
  is($total, 11);
}

# short
{
  my $total = SPVM::XSTest::sum_short(8, 3);
  is($total, 11);
}

# int
{
  my $total = SPVM::XSTest::sum_int(8, 3);
  is($total, 11);
}

# long
{
  my $total = SPVM::XSTest::sum_long(8, 3);
  is($total, 11);
}
{
  my $total = SPVM::XSTest::sum_long(9223372036854775806, 1);
  is($total, 9223372036854775807);
}

# float
{
  my $total = SPVM::XSTest::sum_float(0.25, 0.25);
  cmp_ok($total, '==', 0.5);
}

# double
{
  my $total = SPVM::XSTest::sum_double(0.25, 0.25);
  cmp_ok($total, '==', 0.5);
}

# for
{
  my $total = SPVM::XSTest::test_for();
  cmp_ok($total, '==', 6);
}

# if
{
  # if gt int left big
  { 
    my $success = SPVM::XSTest::test_if_gt_int_left_big();
    ok($success == 1);
  }

  # if gt int same
  { 
    my $success = SPVM::XSTest::test_if_gt_int_same();
    ok($success == 0);
  }

  # if gt int right big
  { 
    my $success = SPVM::XSTest::test_if_gt_int_right_big();
    ok($success == 0);
  }
}
