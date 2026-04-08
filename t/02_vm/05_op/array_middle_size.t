use lib "t/lib";
use TestAuto;
use TestUtil::MyLib;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::ArrayMiddleSize';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

my $at_least_memory_size = 0;
my $free_result = `free`;
if (defined $free_result && $free_result =~ /Mem: +(\d+)/) {
  $at_least_memory_size = $1;
}

SKIP: {
  unless (defined $at_least_memory_size && $at_least_memory_size > 1_026_060) {
    skip "Memory must need at least $at_least_memory_size", 6;
  }
  
  ok(SPVM::TestCase::Operator::ArrayMiddleSize->array_middle_index_byte);
  ok(SPVM::TestCase::Operator::ArrayMiddleSize->array_middle_index_short);
  ok(SPVM::TestCase::Operator::ArrayMiddleSize->array_middle_index_int);
  ok(SPVM::TestCase::Operator::ArrayMiddleSize->array_middle_index_long);
  ok(SPVM::TestCase::Operator::ArrayMiddleSize->array_middle_index_float);
  ok(SPVM::TestCase::Operator::ArrayMiddleSize->array_middle_index_double);
};

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
