use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Ref';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

{
  ok(TestCase::Ref->basic());
  ok(TestCase::Ref->value_ref_deref_get_field_double());
  ok(TestCase::Ref->value_ref_deref_set_field_double());
  ok(TestCase::Ref->test_pass_value_ref_double());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
