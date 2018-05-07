use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Std::ArrayUtil';

# SPVM::Std::Arrays;
{
  ok(SPVM::TestCase::Std::ArrayUtil->eq_bytes());
  ok(SPVM::TestCase::Std::ArrayUtil->eq_shorts());
  ok(SPVM::TestCase::Std::ArrayUtil->eq_ints());
  ok(SPVM::TestCase::Std::ArrayUtil->eq_longs());
  ok(SPVM::TestCase::Std::ArrayUtil->eq_floats());
  ok(SPVM::TestCase::Std::ArrayUtil->eq_doubles());

  ok(SPVM::TestCase::Std::ArrayUtil->copy_bytes());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_bytes_over());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_bytes_less());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_bytes_undef());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_bytes_negative());

  ok(SPVM::TestCase::Std::ArrayUtil->copy_shorts());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_shorts_over());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_shorts_less());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_shorts_undef());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_shorts_negative());

  ok(SPVM::TestCase::Std::ArrayUtil->copy_ints());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_ints_over());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_ints_less());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_ints_undef());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_ints_negative());

  ok(SPVM::TestCase::Std::ArrayUtil->copy_longs());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_longs_over());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_longs_less());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_longs_undef());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_longs_negative());

  ok(SPVM::TestCase::Std::ArrayUtil->copy_floats());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_floats_over());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_floats_less());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_floats_undef());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_floats_negative());

  ok(SPVM::TestCase::Std::ArrayUtil->copy_doubles());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_doubles_over());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_doubles_less());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_doubles_undef());
  ok(SPVM::TestCase::Std::ArrayUtil->copy_doubles_negative());
  1;
}

