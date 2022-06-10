use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::TypeCast';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# TypeCast
{
  ok(SPVM::TestCase::TypeCast->to_numeric_type);
  ok(SPVM::TestCase::TypeCast->to_mulnum_type);
  ok(SPVM::TestCase::TypeCast->to_reference_type);
}


# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
