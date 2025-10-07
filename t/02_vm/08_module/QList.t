use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::QList';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# SPVM::QList
{
  # Fields
  ok(SPVM::TestCase::Module::QList->fields);
  
  # Class methods
  ok(SPVM::TestCase::Module::QList->new);
  ok(SPVM::TestCase::Module::QList->new_len);
  
  # Instance methods
  ok(SPVM::TestCase::Module::QList->get);
  ok(SPVM::TestCase::Module::QList->insert);
  ok(SPVM::TestCase::Module::QList->pop);
  ok(SPVM::TestCase::Module::QList->push);
  ok(SPVM::TestCase::Module::QList->remove);
  ok(SPVM::TestCase::Module::QList->replace);
  ok(SPVM::TestCase::Module::QList->splice);
  ok(SPVM::TestCase::Module::QList->reserve);
  ok(SPVM::TestCase::Module::QList->resize);
  ok(SPVM::TestCase::Module::QList->shift);
  ok(SPVM::TestCase::Module::QList->set);
  ok(SPVM::TestCase::Module::QList->to_array);
  ok(SPVM::TestCase::Module::QList->unshift);
  ok(SPVM::TestCase::Module::QList->clone);
  ok(SPVM::TestCase::Module::QList->push_);
  ok(SPVM::TestCase::Module::QList->unshift_);
}

{
  ok(SPVM::TestCase::Module::QList->extra);
  ok(SPVM::TestCase::Module::QList->check_offset_logic);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
