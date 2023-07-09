use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use Config;
use Errno;

use SPVM 'TestCase::NativeAPI';
use SPVM 'TestCase::Pointer';

my $build_dir = $ENV{SPVM_BUILD_DIR};

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# new_object_by_name
{
  ok(SPVM::TestCase::NativeAPI->new_object_by_name);
  ok(SPVM::TestCase::NativeAPI->new_object_by_name_exception);
}

# new_pointer_object_by_name
{
  ok(SPVM::TestCase::NativeAPI->new_pointer_object_by_name);
  ok(SPVM::TestCase::NativeAPI->new_pointer_object_by_name_exception);
}

{
  ok(SPVM::TestCase::NativeAPI->check_native_api_indexes);
  ok(SPVM::TestCase::NativeAPI->check_native_api_constant_values);
  ok(SPVM::TestCase::NativeAPI->check_native_api_compiler_indexes);
  ok(SPVM::TestCase::NativeAPI->check_native_api_string_buffer_indexes);
  ok(SPVM::TestCase::NativeAPI->check_native_api_runtime_indexes);
  ok(SPVM::TestCase::NativeAPI->check_native_api_allocator_indexes);
}

# get_field_string_chars_by_name
{
  ok(SPVM::TestCase::NativeAPI->get_field_string_chars_by_name);
  ok(SPVM::TestCase::NativeAPI->get_field_string_chars_by_name_exception);
}

# class variable access
{
  ok(SPVM::TestCase::NativeAPI->get_class_var_by_index);
  
  ok(SPVM::TestCase::NativeAPI->get_class_var_byte_by_name);
  ok(SPVM::TestCase::NativeAPI->get_class_var_byte_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->get_class_var_short_by_name);
  ok(SPVM::TestCase::NativeAPI->get_class_var_short_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->get_class_var_int_by_name);
  ok(SPVM::TestCase::NativeAPI->get_class_var_int_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->get_class_var_long_by_name);
  ok(SPVM::TestCase::NativeAPI->get_class_var_long_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->get_class_var_float_by_name);
  ok(SPVM::TestCase::NativeAPI->get_class_var_float_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->get_class_var_double_by_name);
  ok(SPVM::TestCase::NativeAPI->get_class_var_double_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->get_class_var_object_by_name);
  ok(SPVM::TestCase::NativeAPI->get_class_var_object_by_name_exception);

  ok(SPVM::TestCase::NativeAPI->set_class_var_byte_by_name);
  ok(SPVM::TestCase::NativeAPI->set_class_var_byte_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->set_class_var_short_by_name);
  ok(SPVM::TestCase::NativeAPI->set_class_var_short_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->set_class_var_int_by_name);
  ok(SPVM::TestCase::NativeAPI->set_class_var_int_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->set_class_var_long_by_name);
  ok(SPVM::TestCase::NativeAPI->set_class_var_long_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->set_class_var_float_by_name);
  ok(SPVM::TestCase::NativeAPI->set_class_var_float_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->set_class_var_double_by_name);
  ok(SPVM::TestCase::NativeAPI->set_class_var_double_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->set_class_var_object_by_name);
  ok(SPVM::TestCase::NativeAPI->set_class_var_object_by_name_exception);
  

  ok(SPVM::TestCase::NativeAPI->push_mortal_multi);
}

# Field
{
  ok(SPVM::TestCase::NativeAPI->get_field_byte_by_name);
  ok(SPVM::TestCase::NativeAPI->get_field_byte_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->get_field_short_by_name);
  ok(SPVM::TestCase::NativeAPI->get_field_short_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->get_field_int_by_name);
  ok(SPVM::TestCase::NativeAPI->get_field_int_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->get_field_long_by_name);
  ok(SPVM::TestCase::NativeAPI->get_field_long_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->get_field_float_by_name);
  ok(SPVM::TestCase::NativeAPI->get_field_float_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->get_field_double_by_name);
  ok(SPVM::TestCase::NativeAPI->get_field_double_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->get_field_object_by_name);
  ok(SPVM::TestCase::NativeAPI->get_field_object_by_name_exception);

  ok(SPVM::TestCase::NativeAPI->set_field_byte_by_name);
  ok(SPVM::TestCase::NativeAPI->set_field_byte_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->set_field_short_by_name);
  ok(SPVM::TestCase::NativeAPI->set_field_short_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->set_field_int_by_name);
  ok(SPVM::TestCase::NativeAPI->set_field_int_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->set_field_long_by_name);
  ok(SPVM::TestCase::NativeAPI->set_field_long_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->set_field_float_by_name);
  ok(SPVM::TestCase::NativeAPI->set_field_float_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->set_field_double_by_name);
  ok(SPVM::TestCase::NativeAPI->set_field_double_by_name_exception);
  ok(SPVM::TestCase::NativeAPI->set_field_object_by_name);
  ok(SPVM::TestCase::NativeAPI->set_field_object_by_name_exception);
}

# has_interface
{
  ok(SPVM::TestCase::NativeAPI->has_interface);
}

# is_type
{
  ok(SPVM::TestCase::NativeAPI->is_type);
}

# Native Exception
{
  ok(SPVM::TestCase::NativeAPI->native_use_strlen_test);
  ok(SPVM::TestCase::NativeAPI->call_void_method_exception);
}

# Check mortal API
{
  ok(SPVM::TestCase::NativeAPI->mortal_api);
  ok(SPVM::TestCase::NativeAPI->enter_scope_leave_scope);
}

# env->call_method_raw
{
  ok(SPVM::TestCase::NativeAPI->native_call_method_raw);
}

# env->call_method
{
  ok(SPVM::TestCase::NativeAPI->native_call_method);
}

# env->call_class_method_by_name
{
  ok(SPVM::TestCase::NativeAPI->native_call_class_method_by_name);
  
  eval { SPVM::TestCase::NativeAPI->native_call_class_method_by_name_exception; };
  ok($@);
  like($@, qr|SPVM__TestCase__NativeAPI__native_call_class_method_by_name_exception at TestCase/NativeAPI\.c line \d+|);
}

# env->call_instance_method_static_by_name
{
  ok(SPVM::TestCase::NativeAPI->call_instance_method_static_by_name);
  
  eval { SPVM::TestCase::NativeAPI->call_instance_method_static_by_name_exception; };
  ok($@);
}

# env->call_instance_method_by_name
{
  ok(SPVM::TestCase::NativeAPI->call_instance_method_by_name);
  
  eval { SPVM::TestCase::NativeAPI->call_instance_method_by_name_exception; };
  ok($@);
}

# Ref
{
  ok(SPVM::TestCase::NativeAPI->ref_byte);
  ok(SPVM::TestCase::NativeAPI->ref_short);
  ok(SPVM::TestCase::NativeAPI->ref_int);
  ok(SPVM::TestCase::NativeAPI->ref_long);
  ok(SPVM::TestCase::NativeAPI->ref_float);
  ok(SPVM::TestCase::NativeAPI->ref_double);
}

# Pointer
{
  ok(SPVM::TestCase::Pointer->struct_test);
}

# Check not creating no needed object file
ok(!-f "$build_dir/work/object/SPVM/CORE.o");

# get_instance_method_static
{
  ok(SPVM::TestCase::NativeAPI->get_instance_method_static);
}

# get_bool_object_value
{
  ok(SPVM::TestCase::NativeAPI->get_bool_object_value);
}

# new_string_raw
{
  ok(SPVM::TestCase::NativeAPI->new_string_raw);
}

# new_string
{
  ok(SPVM::TestCase::NativeAPI->new_string);
}

# new_string_nolen_raw
{
  ok(SPVM::TestCase::NativeAPI->new_string_nolen_raw);
}

# new_string_nolen
{
  ok(SPVM::TestCase::NativeAPI->new_string_nolen);
}

# get_basic_type_id
{
  ok(SPVM::TestCase::NativeAPI->get_basic_type_id);
}

# strerror
{
  if (exists $!{EAGAIN}) {
    $! = Errno::EAGAIN;
    is(SPVM::TestCase::NativeAPI->strerror_value(Errno::EAGAIN)->to_string, "$!");
  }
}

# strerror_string
{
  if (exists $!{EAGAIN}) {
    my $strerror_string = SPVM::TestCase::NativeAPI->strerror_string_value(Errno::EAGAIN);
    ok(ref $strerror_string);
    $! = Errno::EAGAIN;
    is("$strerror_string", "$!");
  }
}

# strerror_nolen
{
  if (exists $!{EAGAIN}) {
    $! = Errno::EAGAIN;
    is(SPVM::TestCase::NativeAPI->strerror_nolen_value(Errno::EAGAIN)->to_string, "$!");
  }
}

# strerror_string_nolen
{
  if (exists $!{EAGAIN}) {
    my $strerror_nolen_string = SPVM::TestCase::NativeAPI->strerror_string_nolen_value(Errno::EAGAIN);
    ok(ref $strerror_nolen_string);
    $! = Errno::EAGAIN;
    is("$strerror_nolen_string", "$!");
  }
}

# new_object_array_raw
{
  ok(SPVM::TestCase::NativeAPI->new_object_array_raw);
}

# items
{
  ok(SPVM::TestCase::NativeAPI->items);
}

# Default
{
  ok(SPVM::TestCase::NativeAPI->default_all_types);
}

# new_string_array
{
  ok(SPVM::TestCase::NativeAPI->new_string_array);
  is_deeply(SPVM::TestCase::NativeAPI->new_string_array_value->to_elems, ['abc', 'def']);
}

ok(SPVM::TestCase::NativeAPI->new_memory_apis);

ok(SPVM::TestCase::NativeAPI->new_memory_apis);

ok(SPVM::TestCase::NativeAPI->dumpc);

ok(SPVM::TestCase::NativeAPI->precompile_build_methodd_source);

ok(SPVM::TestCase::NativeAPI->get_compile_type_name);

ok(SPVM::TestCase::NativeAPI->runtime_get_method_is_enum);

# get string field
{
  ok(SPVM::TestCase::NativeAPI->floating_point_constant);
}
{
  ok(SPVM::TestCase::NativeAPI->call_method_in_precompile_class);
}

{
  ok(SPVM::TestCase::NativeAPI->get_object_basic_type_name);
}

# Clear exception
SPVM::api->set_exception(undef);

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
