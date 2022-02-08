use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;


use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase::Divide';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Spec tests
{
  # Division operator
  {
    ok(SPVM::TestCase::Divide->divide_byte_byte);
    ok(SPVM::TestCase::Divide->divide_short_short);
    ok(SPVM::TestCase::Divide->divide_int_byte);
    ok(SPVM::TestCase::Divide->divide_int_short);
    ok(SPVM::TestCase::Divide->divide_byte_int);
    ok(SPVM::TestCase::Divide->divide_short_int);
    ok(SPVM::TestCase::Divide->divide_int_int);
    ok(SPVM::TestCase::Divide->divide_long_long);
    ok(SPVM::TestCase::Divide->divide_int_float);
    ok(SPVM::TestCase::Divide->divide_int_double);
    ok(SPVM::TestCase::Divide->divide_float_float);
    ok(SPVM::TestCase::Divide->divide_double_double);
    ok(SPVM::TestCase::Divide->divide_double_double_big);
  }

  # Divide - Compile Error
  {
    {
      my $build = SPVM::Builder->new;
      my $success = $build->compile_spvm('TestCase::CompileError::Divide::LeftIsNotNumeric', __LINE__, __FILE__);
      ok($success == 0);
    }
    {
      my $build = SPVM::Builder->new;
      my $success = $build->compile_spvm('TestCase::CompileError::Divide::RightIsNotNumeric', __LINE__, __FILE__);
      ok($success == 0);
    }
  }

  # Divide Unsinged operator
  {
    ok(SPVM::TestCase::Divide->divide_unsigned_int);
    ok(SPVM::TestCase::Divide->divide_unsigned_long);
  }
}

# Optional tests
{
  ok(SPVM::TestCase::Divide->divide());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
