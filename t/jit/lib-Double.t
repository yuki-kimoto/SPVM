use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Double';

use POSIX ();

my $BYTE_MAX = 127;
my $BYTE_MIN = -128;
my $SHORT_MAX = 32767;
my $SHORT_MIN = -32768;
my $INT_MAX = 2147483647;
my $INT_MIN = -2147483648;
my $LONG_MAX = 9223372036854775807;
my $LONG_MIN = -9223372036854775808;
my $FLOAT_MAX = POSIX::FLT_MAX();
my $FLOAT_MIN = POSIX::FLT_MIN();
my $DOUBLE_MAX = POSIX::DBL_MAX();
my $DOUBLE_MIN = POSIX::DBL_MIN();
my $FLOAT_PRECICE = 16384.5;
my $DOUBLE_PRECICE = 65536.5;

my $POSITIVE_INFINITY = 9**9**9 ;

my $NEGATIVE_INFINITY = -9**9**9;

my $NaN = 9**9**9 / 9**9**9;

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# SPVM::Double
{
  ok(SPVM::TestCase::Double->basic());
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
