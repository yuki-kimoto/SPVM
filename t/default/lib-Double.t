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

# Positive infinity(unix like system : inf, Windows : 1.#INF)
my $POSITIVE_INFINITY = SPVM::POSITIVE_INFINITY();

# Negative infinity(unix like system : -inf, Windows : -1.#INF)
my $NEGATIVE_INFINITY = SPVM::NEGATIVE_INFINITY();

my $NaN = SPVM::NaN();

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# SPVM::Double
{
  ok(SPVM::TestCase::Double::pass_positive_infinity($POSITIVE_INFINITY));
  ok(SPVM::TestCase::Double::pass_negative_infinity($NEGATIVE_INFINITY));
  ok(SPVM::TestCase::Double::pass_nan($NaN));
  
  ok(SPVM::TestCase::Double::constant());
  ok(SPVM::TestCase::Double::is_infinite());
  ok(SPVM::TestCase::Double::is_finite());
  ok(SPVM::TestCase::Double::is_nan());
  ok(SPVM::TestCase::Double::long_bits_to_double());
  ok(SPVM::TestCase::Double::long_bits_to_double_nan_first_condition());
  ok(SPVM::TestCase::Double::long_bits_to_double_nan_first_condition_is_nan());
  ok(SPVM::TestCase::Double::long_bits_to_double_nan_second_condition());
  ok(SPVM::TestCase::Double::long_bits_to_double_nan_second_condition_is_nan());
  
  ok(SPVM::TestCase::Double::double_to_raw_long_bits());
  ok(SPVM::TestCase::Double::double_to_raw_long_bits_nan());
  ok(SPVM::TestCase::Double::double_to_long_bits());
  ok(SPVM::TestCase::Double::double_to_long_bits_nan());
  
  is(SPVM::Double::POSITIVE_INFINITY(), $POSITIVE_INFINITY);
  is(SPVM::Double::NEGATIVE_INFINITY(), $NEGATIVE_INFINITY);
  
  cmp_ok(SPVM::Double::NaN(), 'eq', $NaN);
  
  # Check not Inf or NaN in Perl value
  like(SPVM::Double::MAX_VALUE(), qr/[0-9]/);
  like(SPVM::Double::MIN_VALUE(), qr/[0-9]/);
  like(SPVM::Double::MIN_NORMAL(), qr/[0-9]/);
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
