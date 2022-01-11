use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use FindBin;

use SPVM 'TestCase::NativeAPICpp';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

{
  is(SPVM::TestCase::NativeAPICpp->call_cpp_func(2), 4);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
