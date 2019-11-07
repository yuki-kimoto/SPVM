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
  ok(TestCase::Extension->set_package_var_byte);
  ok(TestCase::Extension->set_package_var_short);
  ok(TestCase::Extension->set_package_var_int);
  ok(TestCase::Extension->set_package_var_long);
  ok(TestCase::Extension->set_package_var_float);
  ok(TestCase::Extension->set_package_var_double);
  ok(TestCase::Extension->set_package_var_object);
  ok(TestCase::Extension->get_package_var_byte);
  ok(TestCase::Extension->get_package_var_short);
  ok(TestCase::Extension->get_package_var_int);
  ok(TestCase::Extension->get_package_var_long);
  ok(TestCase::Extension->get_package_var_float);
  ok(TestCase::Extension->get_package_var_double);
  ok(TestCase::Extension->get_package_var_object);
  ok(TestCase::Extension->push_mortal_multi);
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
  ok(TestCase::Extension->get_field_byte());
  ok(TestCase::Extension->get_field_short());
  ok(TestCase::Extension->get_field_int());
  ok(TestCase::Extension->get_field_long());
  ok(TestCase::Extension->get_field_float());
  ok(TestCase::Extension->get_field_double());
  ok(TestCase::Extension->get_field_object());

  ok(TestCase::Extension->set_field_byte());
  ok(TestCase::Extension->set_field_short());
  ok(TestCase::Extension->set_field_int());
  ok(TestCase::Extension->set_field_long());
  ok(TestCase::Extension->set_field_float());
  ok(TestCase::Extension->set_field_double());
  ok(TestCase::Extension->set_field_object());

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
SPVM::set_exception(undef);

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
