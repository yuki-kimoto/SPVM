use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::QueueList';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# SPVM::QueueList
{
  # Fields
  ok(SPVM::TestCase::Module::QueueList->fields);
  
  # Class methods
  ok(SPVM::TestCase::Module::QueueList->new);
  ok(SPVM::TestCase::Module::QueueList->new_len);
  
  # Instance methods
  ok(SPVM::TestCase::Module::QueueList->get);
  ok(SPVM::TestCase::Module::QueueList->insert);
  ok(SPVM::TestCase::Module::QueueList->pop);
  ok(SPVM::TestCase::Module::QueueList->push);
  ok(SPVM::TestCase::Module::QueueList->remove);
  ok(SPVM::TestCase::Module::QueueList->replace);
  ok(SPVM::TestCase::Module::QueueList->splice);
  ok(SPVM::TestCase::Module::QueueList->reserve);
  ok(SPVM::TestCase::Module::QueueList->resize);
  ok(SPVM::TestCase::Module::QueueList->shift);
  ok(SPVM::TestCase::Module::QueueList->set);
  ok(SPVM::TestCase::Module::QueueList->to_array);
  ok(SPVM::TestCase::Module::QueueList->unshift);
  ok(SPVM::TestCase::Module::QueueList->clone);
  ok(SPVM::TestCase::Module::QueueList->push_);
  ok(SPVM::TestCase::Module::QueueList->unshift_);
}

{
  ok(SPVM::TestCase::Module::QueueList->extra);
  ok(SPVM::TestCase::Module::QueueList->check_offset_logic);
}

# All object is freed
$api->set_exception(undef);
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
