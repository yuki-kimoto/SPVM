use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Std::Number::Util';

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

# SPVM::Std::Number::Util
{
  ok(SPVM::TestCase::Std::Number::Util->byte_constant());
  ok(SPVM::TestCase::Std::Number::Util->short_constant());
  ok(SPVM::TestCase::Std::Number::Util->int_constant());
}

# float
{
  ok(SPVM::TestCase::Std::Number::Util->float_pass_positive_infinity($POSITIVE_INFINITY));
  ok(SPVM::TestCase::Std::Number::Util->float_pass_negative_infinity($NEGATIVE_INFINITY));
  ok(SPVM::TestCase::Std::Number::Util->float_pass_nan($NaN));
  
  ok(SPVM::TestCase::Std::Number::Util->float_constant());
  ok(SPVM::TestCase::Std::Number::Util->float_is_infinite());
  ok(SPVM::TestCase::Std::Number::Util->float_is_finite());
  ok(SPVM::TestCase::Std::Number::Util->float_is_nan());
  
  is(SPVM::Std::Number::Util->FLOAT_POSITIVE_INFINITY(), $POSITIVE_INFINITY);
  is(SPVM::Std::Number::Util->FLOAT_NEGATIVE_INFINITY(), $NEGATIVE_INFINITY);
  
  like(SPVM::Std::Number::Util->FLOAT_NAN(), $nan_re);
  
  # Check not Inf or NaN in Perl value
  like(SPVM::Std::Number::Util->FLOAT_MAX_VALUE(), qr/[0-9]/);
  like(SPVM::Std::Number::Util->FLOAT_MIN_VALUE(), qr/[0-9]/);
  like(SPVM::Std::Number::Util->FLOAT_MIN_NORMAL(), qr/[0-9]/);
}

# SPVM::Double
{
  ok(SPVM::TestCase::Std::Number::Util->double_pass_positive_infinity($POSITIVE_INFINITY));
  ok(SPVM::TestCase::Std::Number::Util->double_pass_negative_infinity($NEGATIVE_INFINITY));
  ok(SPVM::TestCase::Std::Number::Util->double_pass_nan($NaN));
  
  ok(SPVM::TestCase::Std::Number::Util->double_constant());
  ok(SPVM::TestCase::Std::Number::Util->double_is_infinite());
  ok(SPVM::TestCase::Std::Number::Util->double_is_finite());
  ok(SPVM::TestCase::Std::Number::Util->double_is_nan());
  
  is(SPVM::Std::Number::Util->DOUBLE_POSITIVE_INFINITY(), $POSITIVE_INFINITY);
  is(SPVM::Std::Number::Util->DOUBLE_NEGATIVE_INFINITY(), $NEGATIVE_INFINITY);
  
  like(SPVM::Std::Number::Util->DOUBLE_NAN(), $nan_re);
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
