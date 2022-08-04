use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::List';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::List
{
  # Fields
  ok(SPVM::TestCase::Module::List->fields);
  
  # Class methods
  ok(SPVM::TestCase::Module::List->new);
  ok(SPVM::TestCase::Module::List->new_len);
  
  # Instance methods
  ok(SPVM::TestCase::Module::List->get);
  ok(SPVM::TestCase::Module::List->insert);
  ok(SPVM::TestCase::Module::List->pop);
  ok(SPVM::TestCase::Module::List->push);
  ok(SPVM::TestCase::Module::List->remove);
  ok(SPVM::TestCase::Module::List->replace);
  ok(SPVM::TestCase::Module::List->reserve);
  ok(SPVM::TestCase::Module::List->resize);
  ok(SPVM::TestCase::Module::List->shift);
  ok(SPVM::TestCase::Module::List->set);
  ok(SPVM::TestCase::Module::List->set_array);
  ok(SPVM::TestCase::Module::List->to_array);
  ok(SPVM::TestCase::Module::List->unshift);
  ok(SPVM::TestCase::Module::List->extra);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
