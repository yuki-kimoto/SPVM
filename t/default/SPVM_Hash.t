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
  ok(TestCase::Lib::SPVM::Hash->rehash);
  ok(TestCase::Lib::SPVM::Hash->set_get_numeric);
  ok(TestCase::Lib::SPVM::Hash->murmur_hash);
  ok(TestCase::Lib::SPVM::Hash->set);
  ok(TestCase::Lib::SPVM::Hash->set_do_not_refer_caller_key);
  ok(TestCase::Lib::SPVM::Hash->get);
  ok(TestCase::Lib::SPVM::Hash->exists);
  ok(TestCase::Lib::SPVM::Hash->delete_with_no_hash_collision);
  ok(TestCase::Lib::SPVM::Hash->delete_with_hash_collision);
  ok(TestCase::Lib::SPVM::Hash->keys);
  ok(TestCase::Lib::SPVM::Hash->values);
  ok(TestCase::Lib::SPVM::Hash->copy);
  ok(TestCase::Lib::SPVM::Hash->newa);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
