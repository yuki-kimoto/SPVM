use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use FindBin;

use SPVM 'TestCase::NativeAPI';
use SPVM 'TestCase::NativeAPI2';
use SPVM 'TestCase::Pointer';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# new_object_by_name
{
  ok(TestCase::NativeAPI->new_object_by_name);
  ok(TestCase::NativeAPI->new_object_by_name_exception);
}

# new_pointer_by_name
{
  ok(TestCase::NativeAPI->new_pointer_by_name);
  ok(TestCase::NativeAPI->new_pointer_by_name_exception);
}

# package variable access
{
  ok(TestCase::NativeAPI->get_package_var_byte_by_name);
  ok(TestCase::NativeAPI->get_package_var_byte_by_name_exception);
  ok(TestCase::NativeAPI->get_package_var_short_by_name);
  ok(TestCase::NativeAPI->get_package_var_short_by_name_exception);
  ok(TestCase::NativeAPI->get_package_var_int_by_name);
  ok(TestCase::NativeAPI->get_package_var_int_by_name_exception);
  ok(TestCase::NativeAPI->get_package_var_long_by_name);
  ok(TestCase::NativeAPI->get_package_var_long_by_name_exception);
  ok(TestCase::NativeAPI->get_package_var_float_by_name);
  ok(TestCase::NativeAPI->get_package_var_float_by_name_exception);
  ok(TestCase::NativeAPI->get_package_var_double_by_name);
  ok(TestCase::NativeAPI->get_package_var_double_by_name_exception);
  ok(TestCase::NativeAPI->get_package_var_object_by_name);
  ok(TestCase::NativeAPI->get_package_var_object_by_name_exception);

  ok(TestCase::NativeAPI->set_package_var_byte_by_name);
  ok(TestCase::NativeAPI->set_package_var_byte_by_name_exception);
  ok(TestCase::NativeAPI->set_package_var_short_by_name);
  ok(TestCase::NativeAPI->set_package_var_short_by_name_exception);
  ok(TestCase::NativeAPI->set_package_var_int_by_name);
  ok(TestCase::NativeAPI->set_package_var_int_by_name_exception);
  ok(TestCase::NativeAPI->set_package_var_long_by_name);
  ok(TestCase::NativeAPI->set_package_var_long_by_name_exception);
  ok(TestCase::NativeAPI->set_package_var_float_by_name);
  ok(TestCase::NativeAPI->set_package_var_float_by_name_exception);
  ok(TestCase::NativeAPI->set_package_var_double_by_name);
  ok(TestCase::NativeAPI->set_package_var_double_by_name_exception);
  ok(TestCase::NativeAPI->set_package_var_object_by_name);
  ok(TestCase::NativeAPI->set_package_var_object_by_name_exception);
  

  ok(TestCase::NativeAPI->push_mortal_multi);
}

# Field
{
  ok(TestCase::NativeAPI->get_field_byte_by_name());
  ok(TestCase::NativeAPI->get_field_byte_by_name_exception());
  ok(TestCase::NativeAPI->get_field_short_by_name());
  ok(TestCase::NativeAPI->get_field_short_by_name_exception());
  ok(TestCase::NativeAPI->get_field_int_by_name());
  ok(TestCase::NativeAPI->get_field_int_by_name_exception());
  ok(TestCase::NativeAPI->get_field_long_by_name());
  ok(TestCase::NativeAPI->get_field_long_by_name_exception());
  ok(TestCase::NativeAPI->get_field_float_by_name());
  ok(TestCase::NativeAPI->get_field_float_by_name_exception());
  ok(TestCase::NativeAPI->get_field_double_by_name());
  ok(TestCase::NativeAPI->get_field_double_by_name_exception());
  ok(TestCase::NativeAPI->get_field_object_by_name());
  ok(TestCase::NativeAPI->get_field_object_by_name_exception());

  ok(TestCase::NativeAPI->set_field_byte_by_name());
  ok(TestCase::NativeAPI->set_field_byte_by_name_exception());
  ok(TestCase::NativeAPI->set_field_short_by_name());
  ok(TestCase::NativeAPI->set_field_short_by_name_exception());
  ok(TestCase::NativeAPI->set_field_int_by_name());
  ok(TestCase::NativeAPI->set_field_int_by_name_exception());
  ok(TestCase::NativeAPI->set_field_long_by_name());
  ok(TestCase::NativeAPI->set_field_long_by_name_exception());
  ok(TestCase::NativeAPI->set_field_float_by_name());
  ok(TestCase::NativeAPI->set_field_float_by_name_exception());
  ok(TestCase::NativeAPI->set_field_double_by_name());
  ok(TestCase::NativeAPI->set_field_double_by_name_exception());
  ok(TestCase::NativeAPI->set_field_object_by_name());
  ok(TestCase::NativeAPI->set_field_object_by_name_exception());
}

# has_callback
{
  ok(TestCase::NativeAPI->has_callback);
}

# is_type
{
  ok(TestCase::NativeAPI->is_type);
}

# Native Exception
{
  ok(TestCase::NativeAPI->native_use_strlen_test);
  ok(TestCase::NativeAPI->call_void_sub_exception);
}

# Check mortal API
{
  ok(TestCase::NativeAPI->mortal_api);
  ok(TestCase::NativeAPI->enter_scope_leave_scope);
}

# env->call_sub
{
  ok(TestCase::NativeAPI->native_call_sub);
}

# env->call_sub_by_name
{
  ok(TestCase::NativeAPI->native_call_sub);
  
  eval { TestCase::NativeAPI->native_call_sub_exception };
  ok($@);
}

# Ref
{
  ok(TestCase::NativeAPI->ref_byte());
  ok(TestCase::NativeAPI->ref_short());
  ok(TestCase::NativeAPI->ref_int());
  ok(TestCase::NativeAPI->ref_long());
  ok(TestCase::NativeAPI->ref_float());
  ok(TestCase::NativeAPI->ref_double());
}

# Native Exception
{
  is(TestCase::NativeAPI2->mul(2, 3), 6);
  ok(TestCase::NativeAPI2->spvm_extension2());
}

# Pointer
{
  ok(TestCase::Pointer->struct_test());
}

# src and include directory
{
  ok(TestCase::NativeAPI2->src_foo);
  ok(TestCase::NativeAPI2->src_bar);
}

# Check not creating no needed object file
ok(!-f "$FindBin::Bin/spvm_build/work/object/SPVM/CORE.o");

# Clear exception
SPVM::set_exception(undef);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
