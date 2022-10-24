use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::StringList';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# StringList
{
  ok(SPVM::TestCase::Module::StringList->fields);
  ok(SPVM::TestCase::Module::StringList->new);
  ok(SPVM::TestCase::Module::StringList->new_len);
  ok(SPVM::TestCase::Module::StringList->get);
  ok(SPVM::TestCase::Module::StringList->insert);
  ok(SPVM::TestCase::Module::StringList->pop);
  ok(SPVM::TestCase::Module::StringList->push);
  ok(SPVM::TestCase::Module::StringList->remove);
  ok(SPVM::TestCase::Module::StringList->replace);
  ok(SPVM::TestCase::Module::StringList->reserve);
  ok(SPVM::TestCase::Module::StringList->resize);
  ok(SPVM::TestCase::Module::StringList->set);
  ok(SPVM::TestCase::Module::StringList->set_array);
  ok(SPVM::TestCase::Module::StringList->shift);
  ok(SPVM::TestCase::Module::StringList->to_array);
  ok(SPVM::TestCase::Module::StringList->unshift);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
