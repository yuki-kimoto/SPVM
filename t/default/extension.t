use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use FindBin;

use SPVM 'TestCase::Extension';
use SPVM 'TestCase::Extension2';
use SPVM 'TestCase::Pointer';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# package variable access
{
  ok(TestCase::Extension->set_bpkgvar);
  ok(TestCase::Extension->set_spkgvar);
  ok(TestCase::Extension->set_ipkgvar);
  ok(TestCase::Extension->set_lpkgvar);
  ok(TestCase::Extension->set_fpkgvar);
  ok(TestCase::Extension->set_dpkgvar);
  ok(TestCase::Extension->set_opkgvar);
  ok(TestCase::Extension->bpkgvar);
  ok(TestCase::Extension->spkgvar);
  ok(TestCase::Extension->ipkgvar);
  ok(TestCase::Extension->lpkgvar);
  ok(TestCase::Extension->fpkgvar);
  ok(TestCase::Extension->dpkgvar);
  ok(TestCase::Extension->opkgvar);
}

# has_callback
{
  ok(TestCase::Extension->has_callback);
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

# Check not creating no needed object file
ok(!-f "$FindBin::Bin/spvm_build/work/object/SPVM/CORE.o");

# Clear exception
SPVM::set_exception_undef();

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
