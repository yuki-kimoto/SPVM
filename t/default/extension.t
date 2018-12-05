use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Extension';
use SPVM 'TestCase::Extension2';
use SPVM 'TestCase::Pointer';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

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
  ok(TestCase::Extension->get_byte_field());
  ok(TestCase::Extension->get_short_field());
  ok(TestCase::Extension->get_int_field());
  ok(TestCase::Extension->get_long_field());
  ok(TestCase::Extension->get_float_field());
  ok(TestCase::Extension->get_double_field());
  ok(TestCase::Extension->get_object_field());

  ok(TestCase::Extension->set_byte_field());
  ok(TestCase::Extension->set_short_field());
  ok(TestCase::Extension->set_int_field());
  ok(TestCase::Extension->set_long_field());
  ok(TestCase::Extension->set_float_field());
  ok(TestCase::Extension->set_double_field());
  ok(TestCase::Extension->set_object_field());

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
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
