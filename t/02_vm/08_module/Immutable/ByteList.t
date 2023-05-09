use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Immutable::ByteList';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# ByteList
{
  ok(SPVM::TestCase::Module::Immutable::ByteList->fields);
  ok(SPVM::TestCase::Module::Immutable::ByteList->new);
  ok(SPVM::TestCase::Module::Immutable::ByteList->new_len);
  ok(SPVM::TestCase::Module::Immutable::ByteList->get);
  ok(SPVM::TestCase::Module::Immutable::ByteList->to_array);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
