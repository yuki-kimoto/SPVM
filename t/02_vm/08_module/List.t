use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::List';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# SPVM::List
{
  # Fields
  ok(SPVM::TestCase::Module::List->fields);
  
  # Class methods
  ok(SPVM::TestCase::Module::List->new);
  ok(SPVM::TestCase::Module::List->new_len);
  ok(SPVM::TestCase::Module::List->new_ref);
  
  # Instance methods
  ok(SPVM::TestCase::Module::List->get);
  ok(SPVM::TestCase::Module::List->insert);
  ok(SPVM::TestCase::Module::List->pop);
  ok(SPVM::TestCase::Module::List->push);
  ok(SPVM::TestCase::Module::List->remove);
  ok(SPVM::TestCase::Module::List->replace);
  ok(SPVM::TestCase::Module::List->splice);
  ok(SPVM::TestCase::Module::List->reserve);
  ok(SPVM::TestCase::Module::List->resize);
  ok(SPVM::TestCase::Module::List->shift);
  ok(SPVM::TestCase::Module::List->set);
  ok(SPVM::TestCase::Module::List->to_array);
  ok(SPVM::TestCase::Module::List->unshift);
  ok(SPVM::TestCase::Module::List->clone);
  ok(SPVM::TestCase::Module::List->push_);
  ok(SPVM::TestCase::Module::List->unshift_);
  ok(SPVM::TestCase::Module::List->get_array_unsafe);
  ok(SPVM::TestCase::Module::List->get_array);
}

{
  ok(SPVM::TestCase::Module::List->extra);
  ok(SPVM::TestCase::Module::List->check_offset_logic);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
