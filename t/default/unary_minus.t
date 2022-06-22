use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;


use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase::UnaryMinus';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Spec tests
{
  # Unary minus - Operation
  {
    ok(SPVM::TestCase::UnaryMinus->unary_minus_byte);
    ok(SPVM::TestCase::UnaryMinus->unary_minus_short);
    ok(SPVM::TestCase::UnaryMinus->unary_minus_int);
    ok(SPVM::TestCase::UnaryMinus->unary_minus_long);
    ok(SPVM::TestCase::UnaryMinus->unary_minus_float);
    ok(SPVM::TestCase::UnaryMinus->unary_minus_double);
  }
}
# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
