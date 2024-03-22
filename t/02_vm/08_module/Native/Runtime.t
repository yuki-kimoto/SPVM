use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Native::Runtime';

my $api = SPVM::api;

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count;

{
  ok(SPVM::TestCase::Module::Native::Runtime->get_method_by_name);
  ok(SPVM::TestCase::Module::Native::Runtime->get_field_by_name);
  ok(SPVM::TestCase::Module::Native::Runtime->get_class_var_by_name);
  
  ok(SPVM::TestCase::Module::Native::Runtime->get_basic_types);
}

# All object is freed
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
