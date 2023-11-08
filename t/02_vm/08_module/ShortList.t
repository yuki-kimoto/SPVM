use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::ShortList';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# ShortList
{
  ok(SPVM::TestCase::Module::ShortList->fields);
  ok(SPVM::TestCase::Module::ShortList->new);
  ok(SPVM::TestCase::Module::ShortList->new_len);
  ok(SPVM::TestCase::Module::ShortList->get);
  ok(SPVM::TestCase::Module::ShortList->insert);
  ok(SPVM::TestCase::Module::ShortList->pop);
  ok(SPVM::TestCase::Module::ShortList->push);
  ok(SPVM::TestCase::Module::ShortList->remove);
  ok(SPVM::TestCase::Module::ShortList->replace);
  ok(SPVM::TestCase::Module::ShortList->reserve);
  ok(SPVM::TestCase::Module::ShortList->resize);
  ok(SPVM::TestCase::Module::ShortList->set);
  ok(SPVM::TestCase::Module::ShortList->shift);
  ok(SPVM::TestCase::Module::ShortList->to_array);
  ok(SPVM::TestCase::Module::ShortList->get_array_unsafe);
  ok(SPVM::TestCase::Module::ShortList->unshift);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
