use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Hash';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::Hash
{
  ok(TestCase::Hash->test_hasher);
  ok(TestCase::Hash->test_new_with_capacity);
  ok(TestCase::Hash->test_new_with_array);
  ok(TestCase::Hash->test_new_with_array_allocated_capacity_should_power_of_2);
  ok(TestCase::Hash->test_new_with_array_croak_when_odd_number_array);
  ok(TestCase::Hash->test_new_with_array_do_not_refer_key_string);
  ok(TestCase::Hash->test_set);
  ok(TestCase::Hash->test_get);
  ok(TestCase::Hash->test_exists);
  ok(TestCase::Hash->test_delete);
  ok(TestCase::Hash->test_load_factor);
  ok(TestCase::Hash->test_rehash);
  ok(TestCase::Hash->test_rehash_with_max_load_factor_0_5);
  ok(TestCase::Hash->test_keys);
  ok(TestCase::Hash->test_values);
  ok(TestCase::Hash->test_many_hash_collisions);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
