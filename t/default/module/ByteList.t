use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::ByteList';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# ByteList
{
  ok(SPVM::TestCase::Module::ByteList->fields);
  ok(SPVM::TestCase::Module::ByteList->new);
  ok(SPVM::TestCase::Module::ByteList->new_len);
  ok(SPVM::TestCase::Module::ByteList->get);
  ok(SPVM::TestCase::Module::ByteList->insert);
  ok(SPVM::TestCase::Module::ByteList->pop);
  ok(SPVM::TestCase::Module::ByteList->push);
  ok(SPVM::TestCase::Module::ByteList->remove);
  ok(SPVM::TestCase::Module::ByteList->replace);
  ok(SPVM::TestCase::Module::ByteList->resize);
  ok(SPVM::TestCase::Module::ByteList->set);
  ok(SPVM::TestCase::Module::ByteList->set_array);
  ok(SPVM::TestCase::Module::ByteList->shift);
  ok(SPVM::TestCase::Module::ByteList->to_array);
  ok(SPVM::TestCase::Module::ByteList->unshift);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
