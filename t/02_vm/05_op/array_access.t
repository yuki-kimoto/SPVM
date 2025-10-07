use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::ArrayAccess';

my $api = SPVM::api();

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# array - set and get array element, first element
{
  my $element = SPVM::TestCase::Operator::ArrayAccess->array_set_and_get_array_element_first();
  is($element, 345);
}

# array - set and get array element, last element
{
  my $element = SPVM::TestCase::Operator::ArrayAccess->array_set_and_get_array_element_last();
  is($element, 298);
}

# array - culcurate sum by for
{
  my $total = SPVM::TestCase::Operator::ArrayAccess->array_culcurate_sum_by_for();
  is($total, 6);
}

ok(SPVM::TestCase::Operator::ArrayAccess->set_cannot_assign);

ok(SPVM::TestCase::Operator::ArrayAccess->array);
ok(SPVM::TestCase::Operator::ArrayAccess->mulnum_array);

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
