use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Immutable::DoubleList';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# DoubleList
{
  ok(SPVM::TestCase::Module::Immutable::DoubleList->fields);
  ok(SPVM::TestCase::Module::Immutable::DoubleList->new);
  ok(SPVM::TestCase::Module::Immutable::DoubleList->new_len);
  ok(SPVM::TestCase::Module::Immutable::DoubleList->get);
  ok(SPVM::TestCase::Module::Immutable::DoubleList->to_array);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
