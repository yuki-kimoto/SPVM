use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::ClassVar';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Class variable relative name
{
  my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;
  ok(SPVM::TestCase::Operator::ClassVar->class_var_name);
  my $end_memory_blocks_count = $api->get_memory_blocks_count;
  is($start_memory_blocks_count, $end_memory_blocks_count);
}

# Class variable
{
  my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;
  ok(SPVM::TestCase::Operator::ClassVar->class_var);
  ok(SPVM::TestCase::Operator::ClassVar->class_var_other_class);
  my $end_memory_blocks_count = $api->get_memory_blocks_count;
  is($start_memory_blocks_count, $end_memory_blocks_count);
}

# Accessor
{
  ok(SPVM::TestCase::Operator::ClassVar->field_method);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
