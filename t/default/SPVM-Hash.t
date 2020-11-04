use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::Hash';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::Hash
{
  ok(TestCase::Lib::SPVM::Hash->test_set_get_numeric);
  ok(TestCase::Lib::SPVM::Hash->test_murmur_hash);
  ok(TestCase::Lib::SPVM::Hash->test_new_capacity);
  ok(TestCase::Lib::SPVM::Hash->test_newa);
  ok(TestCase::Lib::SPVM::Hash->test_newa_allocated_capacity_should_power_of_2);
  ok(TestCase::Lib::SPVM::Hash->test_newa_die_when_odd_number_array);
  ok(TestCase::Lib::SPVM::Hash->test_newa_do_not_refer_caller_key);
  ok(TestCase::Lib::SPVM::Hash->test_set);
  ok(TestCase::Lib::SPVM::Hash->test_set_do_not_refer_caller_key);
  ok(TestCase::Lib::SPVM::Hash->test_get);
  ok(TestCase::Lib::SPVM::Hash->test_exists);
  ok(TestCase::Lib::SPVM::Hash->test_delete_with_no_hash_collision);
  ok(TestCase::Lib::SPVM::Hash->test_delete_with_hash_collision);
  ok(TestCase::Lib::SPVM::Hash->test_load_factor);
  ok(TestCase::Lib::SPVM::Hash->test_rehash);
  ok(TestCase::Lib::SPVM::Hash->test_rehash_with_max_load_factor_0_5);
  ok(TestCase::Lib::SPVM::Hash->test_set_rehash_when_max_load_factor_changes);
  ok(TestCase::Lib::SPVM::Hash->test_keys);
  ok(TestCase::Lib::SPVM::Hash->test_values);
  ok(TestCase::Lib::SPVM::Hash->test_each);
  ok(TestCase::Lib::SPVM::Hash->test_many_hash_collisions);
  ok(TestCase::Lib::SPVM::Hash->test_copy);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
