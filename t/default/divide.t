use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';


use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase::Divide';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Spec tests
{
  # Divide - Operation
  {
    ok(TestCase::Divide->divide_byte_byte);
    ok(TestCase::Divide->divide_short_short);
    ok(TestCase::Divide->divide_int_byte);
    ok(TestCase::Divide->divide_int_short);
    ok(TestCase::Divide->divide_byte_int);
    ok(TestCase::Divide->divide_short_int);
    ok(TestCase::Divide->divide_int_int);
    ok(TestCase::Divide->divide_long_long);
    ok(TestCase::Divide->divide_int_float);
    ok(TestCase::Divide->divide_int_double);
    ok(TestCase::Divide->divide_float_float);
    ok(TestCase::Divide->divide_double_double);
    ok(TestCase::Divide->divide_double_double_big);
  }

  # Divide - Compile Error
  {
    {
      my $build = SPVM::Builder->new;
      $build->use('TestCase::CompileError::Divide::LeftIsNotNumeric');
      my $success = $build->compile_spvm();
      ok($success == 0);
    }
    {
      my $build = SPVM::Builder->new;
      $build->use('TestCase::CompileError::Divide::RightIsNotNumeric');
      my $success = $build->compile_spvm();
      ok($success == 0);
    }
  }
}

# Optional tests
{
  ok(TestCase::Divide->divide());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
