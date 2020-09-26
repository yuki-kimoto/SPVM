use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Array';

if ($ENV{SPVM_TEST_PRIVATE}) {
  plan 'no_plan';
}
else {
  plan skip_all => 'This is private test because not understandable memory error occured' ;
}

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# big size array
my $array_big_index_long_cant_alloc_memory;

ok(TestCase::Array->array_big_index_byte);
ok(TestCase::Array->array_big_index_short);
ok(TestCase::Array->array_big_index_int);
ok(TestCase::Array->array_big_index_long);
ok(TestCase::Array->array_big_index_float);
ok(TestCase::Array->array_big_index_double);

ok(TestCase::Array->array_max_index_byte);

# Clear exception
SPVM::set_exception(undef);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
