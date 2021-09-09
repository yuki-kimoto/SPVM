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
    ok(SPVM::TestCase::Remainder->remainder_byte_byte);
    ok(SPVM::TestCase::Remainder->remainder_short_short);
    ok(SPVM::TestCase::Remainder->remainder_int_byte);
    ok(SPVM::TestCase::Remainder->remainder_int_short);
    ok(SPVM::TestCase::Remainder->remainder_byte_int);
    ok(SPVM::TestCase::Remainder->remainder_short_int);
    ok(SPVM::TestCase::Remainder->remainder_int_int);
    ok(SPVM::TestCase::Remainder->remainder_long_long);
  }

  # Remainder - Compile Error
  {
    {
      my $build = SPVM::Builder->new;
      my $success = $build->compile_spvm('TestCase::CompileError::Remainder::LeftIsNotIntegral', __LINE__, __FILE__);
      ok($success == 0);
    }
    {
      my $build = SPVM::Builder->new;
      my $success = $build->compile_spvm('TestCase::CompileError::Remainder::RightIsNotIntegral', __LINE__, __FILE__);
      ok($success == 0);
    }
  }
}

# Optional tests
{
  ok(SPVM::TestCase::Remainder->remainder());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
