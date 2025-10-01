use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Queue';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# SPVM::Queue
{
  # Fields
  ok(SPVM::TestCase::Module::Queue->fields);
  
  # Class methods
  ok(SPVM::TestCase::Module::Queue->new);
  ok(SPVM::TestCase::Module::Queue->new_len);
  
  # Instance methods
  ok(SPVM::TestCase::Module::Queue->get);
  ok(SPVM::TestCase::Module::Queue->insert);
  ok(SPVM::TestCase::Module::Queue->pop);
  ok(SPVM::TestCase::Module::Queue->push);
  ok(SPVM::TestCase::Module::Queue->remove);
  ok(SPVM::TestCase::Module::Queue->replace);
  ok(SPVM::TestCase::Module::Queue->splice);
  ok(SPVM::TestCase::Module::Queue->reserve);
  ok(SPVM::TestCase::Module::Queue->resize);
  ok(SPVM::TestCase::Module::Queue->shift);
  ok(SPVM::TestCase::Module::Queue->set);
  ok(SPVM::TestCase::Module::Queue->to_array);
  ok(SPVM::TestCase::Module::Queue->unshift);
  ok(SPVM::TestCase::Module::Queue->clone);
  ok(SPVM::TestCase::Module::Queue->push_);
  ok(SPVM::TestCase::Module::Queue->unshift_);
}

{
  ok(SPVM::TestCase::Module::Queue->extra);
  ok(SPVM::TestCase::Module::Queue->check_offset_logic);
}

# All object is freed
$api->set_exception(undef);
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
