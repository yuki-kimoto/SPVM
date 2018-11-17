use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::HashMap';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::HashMap
{
  ok(TestCase::HashMap->test_hasher);
  ok(TestCase::HashMap->test_value_int);
  ok(TestCase::HashMap->test_value_string);
  ok(TestCase::HashMap->test_load_factor);
  ok(TestCase::HashMap->test_rehash);
  ok(TestCase::HashMap->test_rehash_with_max_load_factor_0_5);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
