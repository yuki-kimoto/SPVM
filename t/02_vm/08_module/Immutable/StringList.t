use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Immutable::StringList';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# StringList
{
  ok(SPVM::TestCase::Module::Immutable::StringList->fields);
  ok(SPVM::TestCase::Module::Immutable::StringList->new);
  ok(SPVM::TestCase::Module::Immutable::StringList->new_len);
  ok(SPVM::TestCase::Module::Immutable::StringList->get);
  ok(SPVM::TestCase::Module::Immutable::StringList->to_array);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
