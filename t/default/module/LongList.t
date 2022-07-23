use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::LongList';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# LongList
{
  ok(SPVM::TestCase::Module::LongList->fields);
  ok(SPVM::TestCase::Module::LongList->new);
  ok(SPVM::TestCase::Module::LongList->new_len);
  ok(SPVM::TestCase::Module::LongList->get);
  ok(SPVM::TestCase::Module::LongList->insert);
  ok(SPVM::TestCase::Module::LongList->pop);
  ok(SPVM::TestCase::Module::LongList->push);
  ok(SPVM::TestCase::Module::LongList->remove);
  ok(SPVM::TestCase::Module::LongList->replace);
  ok(SPVM::TestCase::Module::LongList->resize);
  ok(SPVM::TestCase::Module::LongList->set);
  ok(SPVM::TestCase::Module::LongList->set_array);
  ok(SPVM::TestCase::Module::LongList->shift);
  ok(SPVM::TestCase::Module::LongList->to_array);
  ok(SPVM::TestCase::Module::LongList->unshift);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
