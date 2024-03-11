use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Native::Runtime::Info';

my $api = SPVM::api;

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count;

{
  ok(SPVM::TestCase::Module::Native::Runtime::Info->get_class_names);
  ok(SPVM::TestCase::Module::Native::Runtime::Info->get_basic_type_names);
  ok(SPVM::TestCase::Module::Native::Runtime::Info->get_method_names);
  ok(SPVM::TestCase::Module::Native::Runtime::Info->get_field_names);
  ok(SPVM::TestCase::Module::Native::Runtime::Info->get_class_var_names);
  ok(SPVM::TestCase::Module::Native::Runtime::Info->get_method);
  ok(SPVM::TestCase::Module::Native::Runtime::Info->get_field);
  ok(SPVM::TestCase::Module::Native::Runtime::Info->get_class_var);
}

# All object is freed
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
