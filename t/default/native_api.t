use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use FindBin;
use Config;

use SPVM 'TestCase::NativeAPI';
use SPVM 'TestCase::NativeAPI2';
use SPVM 'TestCase::Pointer';

my $build_dir = $ENV{SPVM_BUILD_DIR};

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

{
  my $link_info = $main::NATIVE_API2_LINK_INFO;
  
  my $config = SPVM::Builder::Config->new_gnu99;
  
  ok($link_info->class_name, 'TestCase::NativeAPI2');
  ok($link_info->ld, $config->ld);
  ok($link_info->ldflags, $config->ldflags);
  like($link_info->output_file, qr|TestCase/NativeAPI2\.$Config{dlext}|);
  my $is_object_file_infos = 1;
  for my $object_file_info (@{$link_info->object_file_infos}) {
    unless ($object_file_info->isa('SPVM::Builder::ObjectFileInfo')) {
      $is_object_file_infos = 0;
    }
  }
  ok($is_object_file_infos);
}

# Use resource
{
  ok(SPVM::TestCase::NativeAPI2->use_resource);
}

# new_object_by_name
{
  ok(SPVM::TestCase::NativeAPI->new_object_by_name);
  ok(SPVM::TestCase::NativeAPI->new_object_by_name_exception);
}


# new_pointer_by_name
{
  ok(SPVM::TestCase::NativeAPI->new_pointer_by_name);
  ok(SPVM::TestCase::NativeAPI->new_pointer_by_name_exception);
}

{
  ok(SPVM::TestCase::NativeAPI->check_native_api_indexes);
  ok(SPVM::TestCase::NativeAPI->check_native_api_constant_values);
  ok(SPVM::TestCase::NativeAPI->check_native_api_precompile_indexes);
}

# get_field_string_chars_by_name
{
  ok(SPVM::TestCase::NativeAPI->get_field_string_chars_by_name);
  ok(SPVM::TestCase::NativeAPI->get_field_string_chars_by_name_exception);
}

# class variable access
{
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
  ok(SPVM::TestCase::NativeAPI->get_field_byte_by_name());
  ok(SPVM::TestCase::NativeAPI->get_field_byte_by_name_exception());
  ok(SPVM::TestCase::NativeAPI->get_field_short_by_name());
  ok(SPVM::TestCase::NativeAPI->get_field_short_by_name_exception());
  ok(SPVM::TestCase::NativeAPI->get_field_int_by_name());
  ok(SPVM::TestCase::NativeAPI->get_field_int_by_name_exception());
  ok(SPVM::TestCase::NativeAPI->get_field_long_by_name());
  ok(SPVM::TestCase::NativeAPI->get_field_long_by_name_exception());
  ok(SPVM::TestCase::NativeAPI->get_field_float_by_name());
  ok(SPVM::TestCase::NativeAPI->get_field_float_by_name_exception());
  ok(SPVM::TestCase::NativeAPI->get_field_double_by_name());
  ok(SPVM::TestCase::NativeAPI->get_field_double_by_name_exception());
  ok(SPVM::TestCase::NativeAPI->get_field_object_by_name());
  ok(SPVM::TestCase::NativeAPI->get_field_object_by_name_exception());

  ok(SPVM::TestCase::NativeAPI->set_field_byte_by_name());
  ok(SPVM::TestCase::NativeAPI->set_field_byte_by_name_exception());
  ok(SPVM::TestCase::NativeAPI->set_field_short_by_name());
  ok(SPVM::TestCase::NativeAPI->set_field_short_by_name_exception());
  ok(SPVM::TestCase::NativeAPI->set_field_int_by_name());
  ok(SPVM::TestCase::NativeAPI->set_field_int_by_name_exception());
  ok(SPVM::TestCase::NativeAPI->set_field_long_by_name());
  ok(SPVM::TestCase::NativeAPI->set_field_long_by_name_exception());
  ok(SPVM::TestCase::NativeAPI->set_field_float_by_name());
  ok(SPVM::TestCase::NativeAPI->set_field_float_by_name_exception());
  ok(SPVM::TestCase::NativeAPI->set_field_double_by_name());
  ok(SPVM::TestCase::NativeAPI->set_field_double_by_name_exception());
  ok(SPVM::TestCase::NativeAPI->set_field_object_by_name());
  ok(SPVM::TestCase::NativeAPI->set_field_object_by_name_exception());
}

# has_callback
{
  ok(SPVM::TestCase::NativeAPI->has_callback);
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

# env->call_spvm_method
{
  ok(SPVM::TestCase::NativeAPI->native_call_spvm_method);
}

# env->call_class_method
{
  ok(SPVM::TestCase::NativeAPI->native_call_class_method);
}

# env->call_instance_method
{
  ok(SPVM::TestCase::NativeAPI->native_call_instance_method);
}

# env->call_class_method_by_name
{
  ok(SPVM::TestCase::NativeAPI->native_call_class_method_by_name);
  
  eval { SPVM::TestCase::NativeAPI->native_call_class_method_by_name_exception; };
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
  ok(SPVM::TestCase::NativeAPI->ref_byte());
  ok(SPVM::TestCase::NativeAPI->ref_short());
  ok(SPVM::TestCase::NativeAPI->ref_int());
  ok(SPVM::TestCase::NativeAPI->ref_long());
  ok(SPVM::TestCase::NativeAPI->ref_float());
  ok(SPVM::TestCase::NativeAPI->ref_double());
}

# Native Exception
{
  is(SPVM::TestCase::NativeAPI2->mul(2, 3), 6);
  ok(SPVM::TestCase::NativeAPI2->spvm_extension2());
}

# Pointer
{
  ok(SPVM::TestCase::Pointer->struct_test());
}

# src and include directory
{
  ok(SPVM::TestCase::NativeAPI2->src_foo);
  ok(SPVM::TestCase::NativeAPI2->src_bar);
}

# get string field
{
  ok(SPVM::TestCase::NativeAPI2->get_string_field);
}

# Check not creating no needed object file
ok(!-f "$build_dir/work/object/SPVM/CORE.o");

# get_instance_method_id_static
{
  ok(SPVM::TestCase::NativeAPI->get_instance_method_id_static);
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

# Clear exception
SPVM::set_exception(undef);

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
