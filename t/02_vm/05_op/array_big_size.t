use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::New::Array';

if ($ENV{SPVM_TEST_PRIVATE}) {
  plan;
}
else {
  plan skip_all => 'This is private test because not understandable memory error occured' ;
}

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# large size array
my $array_big_index_long_cant_alloc_memory;

ok(SPVM::TestCase::Operator::New::Array->array_big_index_byte);
ok(SPVM::TestCase::Operator::New::Array->array_big_index_short);
ok(SPVM::TestCase::Operator::New::Array->array_big_index_int);
ok(SPVM::TestCase::Operator::New::Array->array_big_index_long);
ok(SPVM::TestCase::Operator::New::Array->array_big_index_float);
ok(SPVM::TestCase::Operator::New::Array->array_big_index_double);

ok(SPVM::TestCase::Operator::New::Array->array_max_index_byte);

# Clear exception
$api->destroy_runtime_permanent_vars;

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
