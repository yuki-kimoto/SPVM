#include "spvm_env.h"
#include "spvm_util_allocator.h"
#include "spvm_runtime_api.h"

SPVM_ENV* SPVM_ENV_new() {
  SPVM_ENV* env = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(1, sizeof(SPVM_ENV));
  
  env->get_array_length = SPVM_RUNTIME_API_get_array_length;
  env->calcurate_data_byte_size = SPVM_RUNTIME_API_calcurate_data_byte_size;
  env->create_data_array_byte = SPVM_RUNTIME_API_create_data_array_byte;
  env->create_data_array_byte_from_pv = SPVM_RUNTIME_API_create_data_array_byte_from_pv;
  env->dec_ref_count = SPVM_RUNTIME_API_dec_ref_count;
  env->inc_ref_count = SPVM_RUNTIME_API_inc_ref_count;
  env->push_return_value_byte = SPVM_RUNTIME_API_push_return_value_byte;
  env->push_return_value_short = SPVM_RUNTIME_API_push_return_value_short;
  env->push_return_value_int = SPVM_RUNTIME_API_push_return_value_int;
  env->push_return_value_long = SPVM_RUNTIME_API_push_return_value_long;
  env->push_return_value_float = SPVM_RUNTIME_API_push_return_value_float;
  env->push_return_value_double = SPVM_RUNTIME_API_push_return_value_double;
  env->push_ret = SPVM_RUNTIME_API_push_ret;
  env->pop_return_value_byte = SPVM_RUNTIME_API_pop_return_value_byte;
  env->pop_return_value_short = SPVM_RUNTIME_API_pop_return_value_short;
  env->pop_return_value_int = SPVM_RUNTIME_API_pop_return_value_int;
  env->pop_return_value_long = SPVM_RUNTIME_API_pop_return_value_long;
  env->pop_return_value_float = SPVM_RUNTIME_API_pop_return_value_float;
  env->pop_return_value_double = SPVM_RUNTIME_API_pop_return_value_double;
  env->pop_return_value_address = SPVM_RUNTIME_API_pop_return_value_address;
  env->get_var_byte = SPVM_RUNTIME_API_get_var_byte;
  env->get_var_short = SPVM_RUNTIME_API_get_var_short;
  env->get_var_int = SPVM_RUNTIME_API_get_var_int;
  env->get_var_long = SPVM_RUNTIME_API_get_var_long;
  env->get_var_float = SPVM_RUNTIME_API_get_var_float;
  env->get_var_double = SPVM_RUNTIME_API_get_var_double;
  env->get_var_address = SPVM_RUNTIME_API_get_var_address;
  env->push_var_byte = SPVM_RUNTIME_API_push_var_byte;
  env->push_var_short = SPVM_RUNTIME_API_push_var_short;
  env->push_var_int = SPVM_RUNTIME_API_push_var_int;
  env->push_var_long = SPVM_RUNTIME_API_push_var_long;
  env->push_var_float = SPVM_RUNTIME_API_push_var_float;
  env->push_var_double = SPVM_RUNTIME_API_push_var_double;
  env->push_var_address = SPVM_RUNTIME_API_push_var_address;
  env->get_array_value_size = SPVM_RUNTIME_API_get_array_value_size;
  env->get_object_fields = SPVM_RUNTIME_API_get_object_fields;
  env->get_object_field_index = SPVM_RUNTIME_API_get_object_field_index;
  env->get_object_fields_length = SPVM_RUNTIME_API_get_object_fields_length;
  env->set_object_field_value_byte = SPVM_RUNTIME_API_set_object_field_value_byte;
  env->set_object_field_value_short = SPVM_RUNTIME_API_set_object_field_value_short;
  env->set_object_field_value_int = SPVM_RUNTIME_API_set_object_field_value_int;
  env->set_object_field_value_long = SPVM_RUNTIME_API_set_object_field_value_long;
  env->set_object_field_value_float = SPVM_RUNTIME_API_set_object_field_value_float;
  env->set_object_field_value_double = SPVM_RUNTIME_API_set_object_field_value_double;
  env->get_object_field_value_byte = SPVM_RUNTIME_API_get_object_field_value_byte;
  env->get_object_field_value_short = SPVM_RUNTIME_API_get_object_field_value_short;
  env->get_object_field_value_int = SPVM_RUNTIME_API_get_object_field_value_int;
  env->get_object_field_value_long = SPVM_RUNTIME_API_get_object_field_value_long;
  env->get_object_field_value_float = SPVM_RUNTIME_API_get_object_field_value_float;
  env->get_object_field_value_double = SPVM_RUNTIME_API_get_object_field_value_double;
  env->get_object_field_value_ref = SPVM_RUNTIME_API_get_object_field_value_ref;
  env->dump_object_field_names = SPVM_RUNTIME_API_dump_object_field_names;
  env->get_ref_count = SPVM_RUNTIME_API_get_ref_count;
  env->get_array_values_byte = SPVM_RUNTIME_API_get_array_values_byte;
  env->get_array_values_short = SPVM_RUNTIME_API_get_array_values_short;
  env->get_array_values_int = SPVM_RUNTIME_API_get_array_values_int;
  env->get_array_values_long = SPVM_RUNTIME_API_get_array_values_long;
  env->get_array_values_float = SPVM_RUNTIME_API_get_array_values_float;
  env->get_array_values_double = SPVM_RUNTIME_API_get_array_values_double;
  env->get_array_values_ref = SPVM_RUNTIME_API_get_array_values_ref;

  return env;
}
