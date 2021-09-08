use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';


use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase::BitNot';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Spec tests
{
  # Bit not - Operation
  {
    ok(SPVM::TestCase::BitNot->bit_not_byte);
    ok(SPVM::TestCase::BitNot->bit_not_short);
    ok(SPVM::TestCase::BitNot->bit_not_int);
    ok(SPVM::TestCase::BitNot->bit_not_int_theory);
    ok(SPVM::TestCase::BitNot->bit_not_long);
  }

  # Bit not - Compile Error
  {
    {
      my $build = SPVM::Builder->new;
      my $success = $build->compile_spvm('SPVM::TestCase::CompileError::BitNot::NotIntegral', __FILE__, __LINE__);
      ok($success == 0);
    }
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
