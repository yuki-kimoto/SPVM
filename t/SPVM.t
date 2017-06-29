# Before 'make install' is performed this script should be runnable with
# 'make test'. After 'make install' it should work as 'perl SPVM.t'

#########################

# change 'tests => 1' to 'tests => last_test_to_print';

use strict;
use warnings;
use Data::Dumper;


use Test::More 'no_plan';;
BEGIN { use_ok('SPVM') };

#########################

# Insert your test code below, the Test::More module is use()ed here so read
# its man page ( perldoc Test::More ) for help writing this test script.

my $file = 't/SPVM.t';

use SPVM 'XSTest'; my $use_test_line = __LINE__;
use SPVM 'std'; my $use_std_line = __LINE__;

is_deeply(
  \@SPVM::PACKAGE_INFOS,
  [
    {name => 'XSTest', file => $file, line => $use_test_line},
    {name => 'std', file => $file, line => $use_std_line}
  ]
);
$DB::single = 1;

# byte
{
  my $total = SPVM::XSTest::sum_byte(SPVM::byte(8), SPVM::byte(3));
  is($total->value, 11);
}

# short
{
  my $total = SPVM::XSTest::sum_short(SPVM::short(8), SPVM::short(3));
  is($total->value, 11);
}

# int
{
  my $total = SPVM::XSTest::sum_int(SPVM::int(8), SPVM::int(3));
  is($total->value, 11);
}

# long
{
  my $total = SPVM::XSTest::sum_long(SPVM::long(8), SPVM::long(3));
  is($total->value, 11);
}
{
  my $total = SPVM::XSTest::sum_long(SPVM::long(9223372036854775806), SPVM::long(1));
  is($total->value, 9223372036854775807);
}

# float
{
  my $total = SPVM::XSTest::sum_float(SPVM::float(0.25), SPVM::float(0.25));
  cmp_ok($total->value, '==', 0.5);
}

# double
{
  my $total = SPVM::XSTest::sum_double(SPVM::double(0.25), SPVM::double(0.25));
  cmp_ok($total->value, '==', 0.5);
}
