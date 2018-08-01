use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Ref';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Numeric reference dereference
{
  ok(TestCase::Ref->numeric_ref_deref_byte());
  ok(TestCase::Ref->numeric_ref_deref_int());
}

# Value reference dereference
{
  # byte
  {
    ok(TestCase::Ref->value_ref_deref_byte());
    ok(TestCase::Ref->value_ref_deref_get_field_byte());
    ok(TestCase::Ref->value_ref_deref_set_field_byte());
    ok(TestCase::Ref->test_pass_value_ref_byte());
  }

  # short
  {
    ok(TestCase::Ref->value_ref_deref_short());
    ok(TestCase::Ref->value_ref_deref_get_field_short());
    ok(TestCase::Ref->value_ref_deref_set_field_short());
    ok(TestCase::Ref->test_pass_value_ref_short());
  }

  # int
  {
    ok(TestCase::Ref->value_ref_deref_int());
    ok(TestCase::Ref->value_ref_deref_get_field_int());
    ok(TestCase::Ref->value_ref_deref_set_field_int());
    ok(TestCase::Ref->test_pass_value_ref_int());
  }

  # long
  {
    ok(TestCase::Ref->value_ref_deref_long());
    ok(TestCase::Ref->value_ref_deref_get_field_long());
    ok(TestCase::Ref->value_ref_deref_set_field_long());
    ok(TestCase::Ref->test_pass_value_ref_long());
  }
  
  # float
  {
    ok(TestCase::Ref->value_ref_deref_float());
    ok(TestCase::Ref->value_ref_deref_get_field_float());
    ok(TestCase::Ref->value_ref_deref_set_field_float());
    ok(TestCase::Ref->test_pass_value_ref_float());
  }

  # double
  {
    ok(TestCase::Ref->value_ref_deref_double());
    ok(TestCase::Ref->value_ref_deref_get_field_double());
    ok(TestCase::Ref->value_ref_deref_set_field_double());
    ok(TestCase::Ref->test_pass_value_ref_double());
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
