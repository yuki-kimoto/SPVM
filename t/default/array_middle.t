use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::ArrayMiddleSize';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

my $free_result = `free`;
my $at_least_memory_size = '';
if ($at_least_memory_size =~ /Mem: +(\d+)/) {
  $at_least_memory_size = $1;
}

SKIP: {
  if ($at_least_memory_size < 1_026_060) {
    skip "Memory must need at least $at_least_memory_size", 6;
  }
  
  ok(SPVM::TestCase::ArrayMiddleSize->array_middle_index_byte);
  ok(SPVM::TestCase::ArrayMiddleSize->array_middle_index_short);
  ok(SPVM::TestCase::ArrayMiddleSize->array_middle_index_int);
  ok(SPVM::TestCase::ArrayMiddleSize->array_middle_index_long);
  ok(SPVM::TestCase::ArrayMiddleSize->array_middle_index_float);
  ok(SPVM::TestCase::ArrayMiddleSize->array_middle_index_double);
};

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
