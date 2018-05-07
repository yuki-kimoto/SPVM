use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Std::TypeUtil';

my $BYTE_MAX = 127;
my $BYTE_MIN = -128;
my $SHORT_MAX = 32767;
my $SHORT_MIN = -32768;
my $INT_MAX = 2147483647;
my $INT_MIN = -2147483648;
my $LONG_MAX = 9223372036854775807;
my $LONG_MIN = -9223372036854775808;
my $FLOAT_PRECICE = 16384.5;
my $DOUBLE_PRECICE = 65536.5;

# Positive infinity(unix like system : inf, Windows : 1.#INF)
my $POSITIVE_INFINITY = 9**9**9;

# Negative infinity(unix like system : -inf, Windows : -1.#INF)
my $NEGATIVE_INFINITY = -9**9**9;

my $NaN = 9**9**9 / 9**9**9;

my $nan_re = qr/(nan|ind)/i;

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# SPVM::Std::TypeUtil
{
  ok(SPVM::TestCase::Std::TypeUtil->byte_constant());
  ok(SPVM::TestCase::Std::TypeUtil->short_constant());
  ok(SPVM::TestCase::Std::TypeUtil->int_constant());
}

# float
{
  ok(SPVM::TestCase::Std::TypeUtil->float_pass_positive_infinity($POSITIVE_INFINITY));
  ok(SPVM::TestCase::Std::TypeUtil->float_pass_negative_infinity($NEGATIVE_INFINITY));
  ok(SPVM::TestCase::Std::TypeUtil->float_pass_nan($NaN));
  
  ok(SPVM::TestCase::Std::TypeUtil->isinff());
  ok(SPVM::TestCase::Std::TypeUtil->isfinitef());
  ok(SPVM::TestCase::Std::TypeUtil->isnanf());
  
  is(SPVM::Std::TypeUtil->FLOAT_POSITIVE_INFINITY(), $POSITIVE_INFINITY);
  is(SPVM::Std::TypeUtil->FLOAT_NEGATIVE_INFINITY(), $NEGATIVE_INFINITY);
  
  like(SPVM::Std::TypeUtil->FLOAT_NAN(), $nan_re);
  
  # Check not Inf or NaN in Perl value
  like(SPVM::Std::TypeUtil->FLOAT_MAX(), qr/[0-9]/);
  like(SPVM::Std::TypeUtil->FLOAT_MIN(), qr/[0-9]/);
  like(SPVM::Std::TypeUtil->FLOAT_MIN_NORMAL(), qr/[0-9]/);
}

# SPVM::Double
{
  ok(SPVM::TestCase::Std::TypeUtil->double_pass_positive_infinity($POSITIVE_INFINITY));
  ok(SPVM::TestCase::Std::TypeUtil->double_pass_negative_infinity($NEGATIVE_INFINITY));
  ok(SPVM::TestCase::Std::TypeUtil->double_pass_nan($NaN));
  
  ok(SPVM::TestCase::Std::TypeUtil->isinf());
  ok(SPVM::TestCase::Std::TypeUtil->isfinite());
  ok(SPVM::TestCase::Std::TypeUtil->isnan());
  
  is(SPVM::Std::TypeUtil->DOUBLE_POSITIVE_INFINITY(), $POSITIVE_INFINITY);
  is(SPVM::Std::TypeUtil->DOUBLE_NEGATIVE_INFINITY(), $NEGATIVE_INFINITY);
  
  like(SPVM::Std::TypeUtil->DOUBLE_NAN(), $nan_re);
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
