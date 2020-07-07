use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';


use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase::Remainder';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Spec tests
{
  # Remainder - Operation
  {
    ok(TestCase::Remainder->remainder_byte_byte);
    ok(TestCase::Remainder->remainder_short_short);
    ok(TestCase::Remainder->remainder_int_byte);
    ok(TestCase::Remainder->remainder_int_short);
    ok(TestCase::Remainder->remainder_byte_int);
    ok(TestCase::Remainder->remainder_short_int);
    ok(TestCase::Remainder->remainder_int_int);
    ok(TestCase::Remainder->remainder_long_long);
  }

  # Remainder - Compile Error
  {
    {
      my $build = SPVM::Builder->new;
      $build->use('TestCase::CompileError::Remainder::LeftIsNotIntegral', __LINE__, __FILE__);
      my $success = $build->compile_spvm();
      ok($success == 0);
    }
    {
      my $build = SPVM::Builder->new;
      $build->use('TestCase::CompileError::Remainder::RightIsNotIntegral', __LINE__, __FILE__);
      my $success = $build->compile_spvm();
      ok($success == 0);
    }
  }
}

# Optional tests
{
  ok(TestCase::Remainder->remainder());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
