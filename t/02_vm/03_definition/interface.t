use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Interface';
use SPVM 'TestCase::InterfaceNoRequiredMethodTest';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

{
  ok(SPVM::TestCase::Interface->basic);
  ok(SPVM::TestCase::Interface->interface_array);
  ok(SPVM::TestCase::Interface->interface_muldim_array);
  ok(SPVM::TestCase::Interface->can);
  ok(SPVM::TestCase::InterfaceNoRequiredMethodTest->basic);
  ok(SPVM::TestCase::Interface->void_and_any_object_return_type);
  ok(SPVM::TestCase::Interface->string_type_has_stringable_interface);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);


done_testing;
