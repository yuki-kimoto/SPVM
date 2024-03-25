use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::Ref';



# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# Numeric reference dereference
{
  ok(SPVM::TestCase::Operator::Ref->numeric_ref_deref_byte());
  ok(SPVM::TestCase::Operator::Ref->numeric_ref_deref_short());
  ok(SPVM::TestCase::Operator::Ref->numeric_ref_deref_int());
  ok(SPVM::TestCase::Operator::Ref->numeric_ref_deref_long());
  ok(SPVM::TestCase::Operator::Ref->numeric_ref_deref_float());
  ok(SPVM::TestCase::Operator::Ref->numeric_ref_deref_double());
}

# Value reference dereference
{
  # byte
  {
    ok(SPVM::TestCase::Operator::Ref->mulnum_ref_deref_byte());
    ok(SPVM::TestCase::Operator::Ref->mulnum_ref_deref_get_field_byte());
    ok(SPVM::TestCase::Operator::Ref->mulnum_ref_deref_set_field_byte());
    ok(SPVM::TestCase::Operator::Ref->test_pass_mulnum_ref_byte());
  }

  # short
  {
    ok(SPVM::TestCase::Operator::Ref->mulnum_ref_deref_short());
    ok(SPVM::TestCase::Operator::Ref->mulnum_ref_deref_get_field_short());
    ok(SPVM::TestCase::Operator::Ref->mulnum_ref_deref_set_field_short());
    ok(SPVM::TestCase::Operator::Ref->test_pass_mulnum_ref_short());
  }

  # int
  {
    ok(SPVM::TestCase::Operator::Ref->mulnum_ref_deref_int());
    ok(SPVM::TestCase::Operator::Ref->mulnum_ref_deref_get_field_int());
    ok(SPVM::TestCase::Operator::Ref->mulnum_ref_deref_set_field_int());
    ok(SPVM::TestCase::Operator::Ref->test_pass_mulnum_ref_int());
  }

  # long
  {
    ok(SPVM::TestCase::Operator::Ref->mulnum_ref_deref_long());
    ok(SPVM::TestCase::Operator::Ref->mulnum_ref_deref_get_field_long());
    ok(SPVM::TestCase::Operator::Ref->mulnum_ref_deref_set_field_long());
    ok(SPVM::TestCase::Operator::Ref->test_pass_mulnum_ref_long());
  }
  
  # float
  {
    ok(SPVM::TestCase::Operator::Ref->mulnum_ref_deref_float());
    ok(SPVM::TestCase::Operator::Ref->mulnum_ref_deref_get_field_float());
    ok(SPVM::TestCase::Operator::Ref->mulnum_ref_deref_set_field_float());
    ok(SPVM::TestCase::Operator::Ref->test_pass_mulnum_ref_float());
  }

  # double
  {
    ok(SPVM::TestCase::Operator::Ref->mulnum_ref_deref_double());
    ok(SPVM::TestCase::Operator::Ref->mulnum_ref_deref_get_field_double());
    ok(SPVM::TestCase::Operator::Ref->mulnum_ref_deref_set_field_double());
    ok(SPVM::TestCase::Operator::Ref->test_pass_mulnum_ref_double());
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
