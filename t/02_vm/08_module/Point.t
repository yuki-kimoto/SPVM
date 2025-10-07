use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Point';

use SPVM 'TestCase::ModuleContainsMultiClass';

use Devel::Peek;

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Point
{
  # Interfaces
  ok(SPVM::TestCase::Module::Point->interfaces);
  
  # Fields
  ok(SPVM::TestCase::Module::Point->fields);
  
  # Class methods
  ok(SPVM::TestCase::Module::Point->new);
  ok(SPVM::TestCase::Module::Point->clear);
  ok(SPVM::TestCase::Module::Point->to_string);
  ok(SPVM::TestCase::Module::Point->eq);
  
  # Extra
  ok(SPVM::TestCase::Module::Point->extra);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
