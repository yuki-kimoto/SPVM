use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;


use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase::Add';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Spec tests
{
  # Add - Operation
  {
    ok(SPVM::TestCase::Add->add_byte_byte);
    ok(SPVM::TestCase::Add->add_short_short);
    ok(SPVM::TestCase::Add->add_int_byte);
    ok(SPVM::TestCase::Add->add_int_short);
    ok(SPVM::TestCase::Add->add_byte_int);
    ok(SPVM::TestCase::Add->add_short_int);
    ok(SPVM::TestCase::Add->add_int_int);
    ok(SPVM::TestCase::Add->add_long_long);
    ok(SPVM::TestCase::Add->add_int_float);
    ok(SPVM::TestCase::Add->add_int_double);
    ok(SPVM::TestCase::Add->add_float_float);
    ok(SPVM::TestCase::Add->add_double_double);
    ok(SPVM::TestCase::Add->add_double_double_big);
    ok(SPVM::TestCase::Add->add_minus);
    ok(SPVM::TestCase::Add->add_zero_minus);
  }

  # Add - Compile Error
  {
    {
      my $build = SPVM::Builder->new;
      my $success = $build->compile_spvm('TestCase::CompileError::Add::LeftIsNotNumeric', __LINE__, __FILE__);
      ok($success == 0);
    }
    {
      my $build = SPVM::Builder->new;
      my $success = $build->compile_spvm('TestCase::CompileError::Add::RightIsNotNumeric', __LINE__, __FILE__);
      ok($success == 0);
    }
  }
}

# Optional tests
{
  ok(SPVM::TestCase::Add->add);
  is(SPVM::TestCase::Add->add_int_max(), 2147483647);
  is(SPVM::TestCase::Add->add_int_min(), -2147483647);
  is(SPVM::TestCase::Add->add_long_max(), 9223372036854775807);
  is(SPVM::TestCase::Add->add_long_min(), -9223372036854775807);
}

# 2's complement
{
  ok(SPVM::TestCase::Add->add_int_max_plus_one_2s_complement());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);



done_testing;
