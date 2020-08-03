use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Array';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# big size array
my $array_big_index_long_cant_alloc_memory;

eval {
  TestCase::Array->array_big_index_long
};
if ($@) {
  $array_big_index_long_cant_alloc_memory = 1;
}
SKIP: {
  if ($array_big_index_long_cant_alloc_memory) {
    skip "Can't alloc memory for big size array", 6;
  }
  ok(TestCase::Array->array_big_index_byte);
  ok(TestCase::Array->array_big_index_short);
  ok(TestCase::Array->array_big_index_int);
  ok(TestCase::Array->array_big_index_long);
  ok(TestCase::Array->array_big_index_float);
  ok(TestCase::Array->array_big_index_double);
};

# Max Index array
my $array_max_index_byte_cant_alloc_memory;
eval {
  TestCase::Array->array_max_index_byte
};
if ($@) {
  $array_max_index_byte_cant_alloc_memory = 1;
}
SKIP: {
  if ($array_max_index_byte_cant_alloc_memory) {
    skip "Can't alloc memory for max size index test", 1;
  }
  ok(TestCase::Array->array_max_index_byte);
};

# Clear exception
SPVM::set_exception(undef);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
