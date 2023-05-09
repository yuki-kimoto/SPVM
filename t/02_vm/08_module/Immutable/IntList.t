use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Immutable::IntList';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# IntList
{
  ok(SPVM::TestCase::Module::Immutable::IntList->fields);
  ok(SPVM::TestCase::Module::Immutable::IntList->new);
  ok(SPVM::TestCase::Module::Immutable::IntList->new_len);
  ok(SPVM::TestCase::Module::Immutable::IntList->get);
  ok(SPVM::TestCase::Module::Immutable::IntList->to_array);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
