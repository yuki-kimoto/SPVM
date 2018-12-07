use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Extension';
use SPVM 'TestCase::Extension2';
use SPVM 'TestCase::Pointer';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# has_interface
{
  ok(TestCase::Extension->has_interface);
}

# is_type
{
  ok(TestCase::Extension->is_type);
}

# Native Exception
{
  ok(TestCase::Extension->native_use_strlen_test);
  ok(TestCase::Extension->call_void_sub_exception);
}

# Check mortal API
{
  ok(TestCase::Extension->mortal_api);
  ok(TestCase::Extension->enter_scope_leave_scope);
}

# env->call_sub
{
  ok(TestCase::Extension->native_call_sub);
}

# Field
{
  ok(TestCase::Extension->bfield());
  ok(TestCase::Extension->sfield());
  ok(TestCase::Extension->ifield());
  ok(TestCase::Extension->lfield());
  ok(TestCase::Extension->ffield());
  ok(TestCase::Extension->dfield());
  ok(TestCase::Extension->ofield());

  ok(TestCase::Extension->set_bfield());
  ok(TestCase::Extension->set_sfield());
  ok(TestCase::Extension->set_ifield());
  ok(TestCase::Extension->set_lfield());
  ok(TestCase::Extension->set_ffield());
  ok(TestCase::Extension->set_dfield());
  ok(TestCase::Extension->set_ofield());

}

# Ref
{
  ok(TestCase::Extension->ref_byte());
  ok(TestCase::Extension->ref_short());
  ok(TestCase::Extension->ref_int());
  ok(TestCase::Extension->ref_long());
  ok(TestCase::Extension->ref_float());
  ok(TestCase::Extension->ref_double());
}

# Native Exception
{
  is(TestCase::Extension2->mul(2, 3), 6);
  ok(TestCase::Extension2->spvm_extension2());
}

# Pointer
{
  ok(TestCase::Pointer->struct_test());
}


# Clear exception
SPVM::set_exception_undef();

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
