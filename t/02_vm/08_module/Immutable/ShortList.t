use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Immutable::ShortList';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# ShortList
{
  ok(SPVM::TestCase::Module::Immutable::ShortList->fields);
  ok(SPVM::TestCase::Module::Immutable::ShortList->new);
  ok(SPVM::TestCase::Module::Immutable::ShortList->new_len);
  ok(SPVM::TestCase::Module::Immutable::ShortList->get);
  ok(SPVM::TestCase::Module::Immutable::ShortList->to_array);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
