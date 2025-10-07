use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Accessor';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Accessor 
{
  ok(SPVM::TestCase::Accessor->field_accessor);
  ok(SPVM::TestCase::Accessor->field_accessor_user_defined);
  ok(SPVM::TestCase::Accessor->class_var_accessor);
  ok(SPVM::TestCase::Accessor->class_var_user_defined);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);



done_testing;
