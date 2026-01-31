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
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

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
  ok(SPVM::TestCase::NativeAPI->check_native_api_ids);
  
  ok(SPVM::TestCase::NativeAPI->check_native_api_allocator_ids);
  
  ok(SPVM::TestCase::NativeAPI->check_native_api_arg_ids);
  
  ok(SPVM::TestCase::NativeAPI->check_native_api_basic_type_ids);
  
  ok(SPVM::TestCase::NativeAPI->check_native_api_class_file_ids);
  
  ok(SPVM::TestCase::NativeAPI->check_native_api_class_var_ids);
  
  ok(SPVM::TestCase::NativeAPI->check_native_api_compiler_ids);
  
  ok(SPVM::TestCase::NativeAPI->check_native_api_field_ids);
  
  ok(SPVM::TestCase::NativeAPI->check_native_api_internal_ids);
  
  ok(SPVM::TestCase::NativeAPI->check_native_api_method_ids);
  
  ok(SPVM::TestCase::NativeAPI->check_native_api_mutex_ids);
  
  ok(SPVM::TestCase::NativeAPI->check_native_api_runtime_ids);
  
  ok(SPVM::TestCase::NativeAPI->check_native_api_string_buffer_ids);
  
  ok(SPVM::TestCase::NativeAPI->check_native_api_type_ids);
  
  ok(SPVM::TestCase::NativeAPI->check_native_api_constant_values);
}

# get_field_string_chars_by_name
{
  ok(SPVM::TestCase::NativeAPI->get_field_string_chars_by_name);
  ok(SPVM::TestCase::NativeAPI->get_field_string_chars_by_name_exception);
}

# class variable access
{
  ok(SPVM::TestCase::NativeAPI->get_class_var);
  
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

# get_class_var_byte
{
  ok(SPVM::TestCase::NativeAPI->get_class_var_byte);
}

# get_class_var_int
{
  ok(SPVM::TestCase::NativeAPI->get_class_var_int);
}

# get_class_var_short
{
  ok(SPVM::TestCase::NativeAPI->get_class_var_short);
}

# get_class_var_long
{
  ok(SPVM::TestCase::NativeAPI->get_class_var_long);
}

# get_class_var_float
{
  ok(SPVM::TestCase::NativeAPI->get_class_var_float);
}

# get_class_var_double
{
  ok(SPVM::TestCase::NativeAPI->get_class_var_double);
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

# env->call_method_no_mortal
{
  ok(SPVM::TestCase::NativeAPI->native_call_method_no_mortal);
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

# get_byte_object_value
{
  ok(SPVM::TestCase::NativeAPI->get_byte_object_value);
}

# get_short_object_value
{
  ok(SPVM::TestCase::NativeAPI->get_short_object_value);
}

# get_int_object_value
{
  ok(SPVM::TestCase::NativeAPI->get_int_object_value);
}

# get_long_object_value
{
  ok(SPVM::TestCase::NativeAPI->get_long_object_value);
}

# get_float_object_value
{
  ok(SPVM::TestCase::NativeAPI->get_float_object_value);
}

# get_double_object_value
{
  ok(SPVM::TestCase::NativeAPI->get_double_object_value);
}

# new_string_no_mortal
{
  ok(SPVM::TestCase::NativeAPI->new_string_no_mortal);
}

# new_string
{
  ok(SPVM::TestCase::NativeAPI->new_string);
}

# new_string_nolen_no_mortal
{
  ok(SPVM::TestCase::NativeAPI->new_string_nolen_no_mortal);
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
  ok(SPVM::TestCase::NativeAPI->strerror_string);
  
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

# new_object_array_no_mortal
{
  ok(SPVM::TestCase::NativeAPI->new_object_array_no_mortal);
}

# args_width
{
  ok(SPVM::TestCase::NativeAPI->args_width);
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

ok(SPVM::TestCase::NativeAPI->dumpc);

ok(SPVM::TestCase::NativeAPI->precompile_build_methodd_source);

ok(SPVM::TestCase::NativeAPI->get_compile_type_name);

ok(SPVM::TestCase::NativeAPI->runtime_get_method_is_enum);

ok(SPVM::TestCase::NativeAPI->method_native_api);

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

ok(SPVM::TestCase::NativeAPI->spvm_stdin);

ok(SPVM::TestCase::NativeAPI->spvm_stdout);

ok(SPVM::TestCase::NativeAPI->spvm_stderr);

ok(SPVM::TestCase::NativeAPI->spvm_warn);

ok(SPVM::TestCase::NativeAPI->spvm_warnf);

ok(SPVM::TestCase::NativeAPI->no_free);

ok(SPVM::TestCase::NativeAPI->die);

ok(SPVM::TestCase::NativeAPI->print_exception_to_stderr);

ok(SPVM::TestCase::NativeAPI->field_exists);

ok(SPVM::TestCase::NativeAPI->extra);

ok(SPVM::TestCase::NativeAPI->method_begin_and_end_cb);

# Clear exception
$api->destroy_runtime_permanent_vars;

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
