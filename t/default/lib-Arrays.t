use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Arrays';

# SPVM::Arrays;
{
  ok(SPVM::TestCase::Arrays::equals_byte());
  ok(SPVM::TestCase::Arrays::equals_short());
  ok(SPVM::TestCase::Arrays::equals_int());
  ok(SPVM::TestCase::Arrays::equals_long());
  ok(SPVM::TestCase::Arrays::equals_float());
  ok(SPVM::TestCase::Arrays::equals_double());

  ok(SPVM::TestCase::Arrays::copy_of_byte());
  ok(SPVM::TestCase::Arrays::copy_of_byte_over());
  ok(SPVM::TestCase::Arrays::copy_of_byte_less());
  ok(SPVM::TestCase::Arrays::copy_of_byte_undef());
  ok(SPVM::TestCase::Arrays::copy_of_byte_negative());

  ok(SPVM::TestCase::Arrays::copy_of_short());
  ok(SPVM::TestCase::Arrays::copy_of_short_over());
  ok(SPVM::TestCase::Arrays::copy_of_short_less());
  ok(SPVM::TestCase::Arrays::copy_of_short_undef());
  ok(SPVM::TestCase::Arrays::copy_of_short_negative());

  ok(SPVM::TestCase::Arrays::copy_of_int());
  ok(SPVM::TestCase::Arrays::copy_of_int_over());
  ok(SPVM::TestCase::Arrays::copy_of_int_less());
  ok(SPVM::TestCase::Arrays::copy_of_int_undef());
  ok(SPVM::TestCase::Arrays::copy_of_int_negative());

  ok(SPVM::TestCase::Arrays::copy_of_long());
  ok(SPVM::TestCase::Arrays::copy_of_long_over());
  ok(SPVM::TestCase::Arrays::copy_of_long_less());
  ok(SPVM::TestCase::Arrays::copy_of_long_undef());
  ok(SPVM::TestCase::Arrays::copy_of_long_negative());

  ok(SPVM::TestCase::Arrays::copy_of_float());
  ok(SPVM::TestCase::Arrays::copy_of_float_over());
  ok(SPVM::TestCase::Arrays::copy_of_float_less());
  ok(SPVM::TestCase::Arrays::copy_of_float_undef());
  ok(SPVM::TestCase::Arrays::copy_of_float_negative());

  ok(SPVM::TestCase::Arrays::copy_of_double());
  ok(SPVM::TestCase::Arrays::copy_of_double_over());
  ok(SPVM::TestCase::Arrays::copy_of_double_less());
  ok(SPVM::TestCase::Arrays::copy_of_double_undef());
  ok(SPVM::TestCase::Arrays::copy_of_double_negative());
  1;
}

