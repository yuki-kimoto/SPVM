use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;


use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase::Multiply';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Spec tests
{
  # Multiply - Operation
  {
    ok(SPVM::TestCase::Multiply->multiply_byte_byte);
    ok(SPVM::TestCase::Multiply->multiply_short_short);
    ok(SPVM::TestCase::Multiply->multiply_int_byte);
    ok(SPVM::TestCase::Multiply->multiply_int_short);
    ok(SPVM::TestCase::Multiply->multiply_byte_int);
    ok(SPVM::TestCase::Multiply->multiply_short_int);
    ok(SPVM::TestCase::Multiply->multiply_int_int);
    ok(SPVM::TestCase::Multiply->multiply_long_long);
    ok(SPVM::TestCase::Multiply->multiply_int_float);
    ok(SPVM::TestCase::Multiply->multiply_int_double);
    ok(SPVM::TestCase::Multiply->multiply_float_float);
    ok(SPVM::TestCase::Multiply->multiply_double_double);
    ok(SPVM::TestCase::Multiply->multiply_double_double_big);
  }

  # Multiply - Compile Error
  {
    {
      my $build = SPVM::Builder->new;
      my $success = $build->compile_spvm('TestCase::CompileError::Multiply::LeftIsNotNumeric', __LINE__, __FILE__);
      ok($success == 0);
    }
    {
      my $build = SPVM::Builder->new;
      my $success = $build->compile_spvm('TestCase::CompileError::Multiply::RightIsNotNumeric', __LINE__, __FILE__);
      ok($success == 0);
    }
  }
}

# Optional tests
{
  ok(SPVM::TestCase::Multiply->multiply());

  is(SPVM::TestCase::Multiply->multiply_int_plus(), 1073741824);
  is(SPVM::TestCase::Multiply->multiply_int_minus(), -1073741824);
  is(SPVM::TestCase::Multiply->multiply_int_overflow(), -2147483648);
  is(SPVM::TestCase::Multiply->multiply_long_plus(), 4611686018427387904);
  is(SPVM::TestCase::Multiply->multiply_long_minus(), -4611686018427387904);
  is(SPVM::TestCase::Multiply->multiply_long_overflow(), -9223372036854775808);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);



done_testing;
