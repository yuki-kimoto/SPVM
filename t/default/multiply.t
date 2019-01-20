use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';


use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase::Multiply';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Spec tests
{
  # Multiply - Operation
  {
    ok(TestCase::Multiply->multiply_byte_byte);
    ok(TestCase::Multiply->multiply_short_short);
    ok(TestCase::Multiply->multiply_int_byte);
    ok(TestCase::Multiply->multiply_int_short);
    ok(TestCase::Multiply->multiply_byte_int);
    ok(TestCase::Multiply->multiply_short_int);
    ok(TestCase::Multiply->multiply_int_int);
    ok(TestCase::Multiply->multiply_long_long);
    ok(TestCase::Multiply->multiply_int_float);
    ok(TestCase::Multiply->multiply_int_double);
    ok(TestCase::Multiply->multiply_float_float);
    ok(TestCase::Multiply->multiply_double_double);
    ok(TestCase::Multiply->multiply_double_double_big);
  }

  # Multiply - Compile Error
  {
    {
      my $build = SPVM::Builder->new;
      $build->use('TestCase::CompileError::Multiply::LeftIsNotNumeric');
      my $success = $build->compile_spvm();
      ok($success == 0);
    }
    {
      my $build = SPVM::Builder->new;
      $build->use('TestCase::CompileError::Multiply::RightIsNotNumeric');
      my $success = $build->compile_spvm();
      ok($success == 0);
    }
  }
}

# Optional tests
{
  ok(TestCase::Multiply->multiply());

  is(TestCase::Multiply->multiply_int_plus(), 1073741824);
  is(TestCase::Multiply->multiply_int_minus(), -1073741824);
  is(TestCase::Multiply->multiply_int_overflow(), -2147483648);
  is(TestCase::Multiply->multiply_long_plus(), 4611686018427387904);
  is(TestCase::Multiply->multiply_long_minus(), -4611686018427387904);
  is(TestCase::Multiply->multiply_long_overflow(), -9223372036854775808);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);


