use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::StringBuffer';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count();

# SPVM::StringBuffer
{
  # Fields
  ok(SPVM::TestCase::Module::StringBuffer->fields);
  
  # Class methods
  ok(SPVM::TestCase::Module::StringBuffer->new);
  
  ok(SPVM::TestCase::Module::StringBuffer->new_len);
  
  # Instance methods
  ok(SPVM::TestCase::Module::StringBuffer->push);
  
  ok(SPVM::TestCase::Module::StringBuffer->push_char);
  
  ok(SPVM::TestCase::Module::StringBuffer->replace);
  
  ok(SPVM::TestCase::Module::StringBuffer->reserve);
  
  ok(SPVM::TestCase::Module::StringBuffer->to_string);
  
  ok(SPVM::TestCase::Module::StringBuffer->get_string_unsafe);
  
  ok(SPVM::TestCase::Module::StringBuffer->set_length);
  
  ok(SPVM::TestCase::Module::StringBuffer->set);
  
  ok(SPVM::TestCase::Module::StringBuffer->clone);
  
  ok(SPVM::TestCase::Module::StringBuffer->cmp);
  
  ok(SPVM::TestCase::Module::StringBuffer->eq);
  # Extra
  ok(SPVM::TestCase::Module::StringBuffer->extra);
}

# All object is freed
$api->set_exception(undef);
my $end_memory_blocks_count = $api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
