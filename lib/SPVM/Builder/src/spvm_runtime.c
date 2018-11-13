#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stddef.h>

#include "spvm_native.h"

#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_object.h"

#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_package.h"
#include "spvm_runtime_sub.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_package_var.h"
#include "spvm_runtime_arg.h"
#include "spvm_portable.h"

// Only use for constant value
#include "spvm_type.h"
#include "spvm_package.h"
#include "spvm_package_var.h"
#include "spvm_sub.h"
#include "spvm_basic_type.h"
#include "spvm_field.h"

SPVM_ENV* SPVM_RUNTIME_create_env(SPVM_RUNTIME* runtime) {

  void* env_init[]  = {
    SPVM_RUNTIME_API_get_array_length,
    SPVM_RUNTIME_API_get_byte_array_elements,
    SPVM_RUNTIME_API_get_short_array_elements,
    SPVM_RUNTIME_API_get_int_array_elements,
    SPVM_RUNTIME_API_get_long_array_elements,
    SPVM_RUNTIME_API_get_float_array_elements,
    SPVM_RUNTIME_API_get_double_array_elements,
    SPVM_RUNTIME_API_get_object_array_element,
    SPVM_RUNTIME_API_set_object_array_element,
    SPVM_RUNTIME_API_get_field_id,
    SPVM_RUNTIME_API_get_field_index,
    SPVM_RUNTIME_API_get_byte_field,
    SPVM_RUNTIME_API_get_short_field,
    SPVM_RUNTIME_API_get_int_field,
    SPVM_RUNTIME_API_get_long_field,
    SPVM_RUNTIME_API_get_float_field,
    SPVM_RUNTIME_API_get_double_field,
    SPVM_RUNTIME_API_get_object_field,
    SPVM_RUNTIME_API_get_pointer,
    SPVM_RUNTIME_API_set_byte_field,
    SPVM_RUNTIME_API_set_short_field,
    SPVM_RUNTIME_API_set_int_field,
    SPVM_RUNTIME_API_set_long_field,
    SPVM_RUNTIME_API_set_float_field,
    SPVM_RUNTIME_API_set_double_field,
    SPVM_RUNTIME_API_set_object_field,
    SPVM_RUNTIME_API_get_sub_id,
    SPVM_RUNTIME_API_get_sub_id_method_call,
    SPVM_RUNTIME_API_get_basic_type_id,
    SPVM_RUNTIME_API_new_object_raw,
    SPVM_RUNTIME_API_new_byte_array_raw,
    SPVM_RUNTIME_API_new_short_array_raw,
    SPVM_RUNTIME_API_new_int_array_raw,
    SPVM_RUNTIME_API_new_long_array_raw,
    SPVM_RUNTIME_API_new_float_array_raw,
    SPVM_RUNTIME_API_new_double_array_raw,
    SPVM_RUNTIME_API_new_object_array_raw,
    SPVM_RUNTIME_API_new_multi_array_raw,
    SPVM_RUNTIME_API_new_value_t_array_raw,
    SPVM_RUNTIME_API_new_string_raw,
    SPVM_RUNTIME_API_new_pointer_raw,
    SPVM_RUNTIME_API_get_exception,
    SPVM_RUNTIME_API_set_exception,
    SPVM_RUNTIME_API_get_ref_count,
    SPVM_RUNTIME_API_inc_ref_count,
    SPVM_RUNTIME_API_dec_ref_count,
    SPVM_RUNTIME_API_inc_dec_ref_count,
    SPVM_RUNTIME_API_get_memory_blocks_count,
    SPVM_RUNTIME_API_dec_ref_count_only,
    SPVM_RUNTIME_API_weaken,
    SPVM_RUNTIME_API_isweak,
    SPVM_RUNTIME_API_unweaken,
    SPVM_RUNTIME_API_concat,
    SPVM_RUNTIME_API_create_exception_stack_trace,
    (void*)(intptr_t)sizeof(SPVM_OBJECT), // object_header_byte_size
    (void*)(intptr_t)offsetof(SPVM_OBJECT, ref_count), // object_ref_count_byte_offset
    (void*)(intptr_t)offsetof(SPVM_OBJECT, basic_type_id), // object_basic_type_id_byte_offset
    (void*)(intptr_t)offsetof(SPVM_OBJECT, type_dimension), // object_dimension_byte_offset
    (void*)(intptr_t)offsetof(SPVM_OBJECT, elements_length), // object_elements_length_byte_offset
    SPVM_RUNTIME_API_call_sub,
    SPVM_RUNTIME_API_enter_scope,
    SPVM_RUNTIME_API_push_mortal,
    SPVM_RUNTIME_API_leave_scope,
    SPVM_RUNTIME_API_new_object,
    SPVM_RUNTIME_API_new_byte_array,
    SPVM_RUNTIME_API_new_short_array,
    SPVM_RUNTIME_API_new_int_array,
    SPVM_RUNTIME_API_new_long_array,
    SPVM_RUNTIME_API_new_float_array,
    SPVM_RUNTIME_API_new_double_array,
    SPVM_RUNTIME_API_new_object_array,
    SPVM_RUNTIME_API_new_multi_array,
    SPVM_RUNTIME_API_new_value_t_array,
    SPVM_RUNTIME_API_new_string,
    SPVM_RUNTIME_API_new_pointer,
    SPVM_RUNTIME_API_get_package_var_id,
    (void*)(intptr_t)offsetof(SPVM_RUNTIME, package_vars_heap), // runtime_package_vars_heap_byte_offset
    runtime,
    SPVM_RUNTIME_API_has_interface,
    (void*)(intptr_t)SPVM_BASIC_TYPE_C_ID_BYTE_OBJECT,
    (void*)(intptr_t)SPVM_BASIC_TYPE_C_ID_SHORT_OBJECT,
    (void*)(intptr_t)SPVM_BASIC_TYPE_C_ID_INT_OBJECT,
    (void*)(intptr_t)SPVM_BASIC_TYPE_C_ID_LONG_OBJECT,
    (void*)(intptr_t)SPVM_BASIC_TYPE_C_ID_FLOAT_OBJECT,
    (void*)(intptr_t)SPVM_BASIC_TYPE_C_ID_DOUBLE_OBJECT,
  };
  
  int32_t env_length = 85;
  SPVM_ENV* env = SPVM_RUNTIME_API_safe_malloc_zero(sizeof(void*) * env_length);
  memcpy(&env[0], &env_init[0], sizeof(void*) * env_length);
  
  return env;
}

SPVM_ENV* SPVM_RUNTIME_build_runtime_env(SPVM_PORTABLE* portable) {
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_safe_malloc_zero(sizeof(SPVM_RUNTIME));
  
  runtime->portable = portable;
  
  SPVM_ENV* env = SPVM_RUNTIME_create_env(runtime);
  
  runtime->string_pool = portable->string_pool;
  runtime->string_pool_length = portable->string_pool_length;
  
  runtime->constant_pool = portable->constant_pool;
  runtime->constant_pool_length = portable->constant_pool_length;
  
  runtime->basic_types = portable->basic_types;
  runtime->basic_types_length = portable->basic_types_length;

  runtime->fields = (SPVM_RUNTIME_FIELD*)portable->fields;
  runtime->fields_length = portable->fields_length;
  runtime->package_vars = (SPVM_RUNTIME_PACKAGE_VAR*)portable->package_vars;
  runtime->package_vars_length = portable->package_vars_length;
  runtime->args = (SPVM_RUNTIME_ARG*)portable->args;
  runtime->opcodes = (SPVM_OPCODE*)portable->opcodes;
  runtime->subs = (SPVM_RUNTIME_SUB*)portable->subs;
  runtime->subs_length = portable->subs_length;

  // C function addresses(native or precompile)
  runtime->sub_cfunc_addresses = SPVM_RUNTIME_API_safe_malloc_zero(sizeof(void*) * (runtime->subs_length + 1));
  
  // build packages
  runtime->packages_length = portable->packages_length;
  runtime->packages = SPVM_RUNTIME_API_safe_malloc_zero(sizeof(SPVM_RUNTIME_PACKAGE) * (runtime->packages_length + 1));
  memcpy(runtime->packages, portable->packages, sizeof(SPVM_RUNTIME_PACKAGE) * runtime->packages_length);

  // build package symtable
  runtime->package_symtable = SPVM_HASH_new(0);
  for (int32_t package_id = 1; package_id < runtime->packages_length; package_id++) {
    
    SPVM_RUNTIME_PACKAGE* package = &runtime->packages[package_id];
    const char* package_name = &runtime->string_pool[package->name_id];
    SPVM_HASH_insert(runtime->package_symtable, package_name, strlen(package_name), package);
    
    package->field_symtable = SPVM_HASH_new(0);
    package->package_var_symtable = SPVM_HASH_new(0);
  }

  // Register field to package
  for (int32_t field_id = 1; field_id < runtime->fields_length; field_id++) {
    SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
    
    int32_t package_id = field->package_id;
    
    SPVM_RUNTIME_PACKAGE* package = &runtime->packages[package_id];
    
    const char* field_name = &runtime->string_pool[field->name_id];
    SPVM_HASH_insert(package->field_symtable, field_name, strlen(field_name), field);
  }
  
  // Register package_var to package
  for (int32_t package_var_id = 1; package_var_id < runtime->package_vars_length; package_var_id++) {
    SPVM_RUNTIME_PACKAGE_VAR* package_var = &runtime->package_vars[package_var_id];
    
    int32_t package_id = package_var->package_id;
    
    SPVM_RUNTIME_PACKAGE* package = &runtime->packages[package_id];
    
    const char* package_var_name = &runtime->string_pool[package_var->name_id];
    SPVM_HASH_insert(package->package_var_symtable, package_var_name, strlen(package_var_name), package_var);
  }

  // build runtime basic type symtable
  runtime->basic_type_symtable = SPVM_HASH_new(0);
  for (int32_t basic_type_id = 0; basic_type_id < runtime->basic_types_length; basic_type_id++) {
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = &runtime->basic_types[basic_type_id];
    const char* runtime_basic_type_name = &runtime->string_pool[runtime_basic_type->name_id];
    SPVM_HASH_insert(runtime->basic_type_symtable, runtime_basic_type_name, strlen(runtime_basic_type_name), runtime_basic_type);
  }
  
  // Initialize Package Variables
  runtime->package_vars_heap = SPVM_RUNTIME_API_safe_malloc_zero(sizeof(SPVM_VALUE) * (runtime->package_vars_length + 1));

  runtime->mortal_stack_capacity = 1;

  runtime->mortal_stack = SPVM_RUNTIME_API_safe_malloc_zero(sizeof(SPVM_OBJECT*) * runtime->mortal_stack_capacity);
  
  return env;
}

void SPVM_RUNTIME_free(SPVM_ENV* env) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Free exception
  SPVM_RUNTIME_API_set_exception(env, NULL);
  
  // Free portable
  SPVM_PORTABLE_free(runtime->portable);
  
  free(runtime->sub_cfunc_addresses);
  
  if (runtime->exception != NULL) {
    free(runtime->exception);
  }
  
  free(runtime->mortal_stack);
  
  SPVM_HASH_free(runtime->basic_type_symtable);
  
  for (int32_t package_id = 1; package_id < runtime->packages_length; package_id++) {
    
    SPVM_RUNTIME_PACKAGE* package = &runtime->packages[package_id];
    SPVM_HASH_free(package->field_symtable);
    SPVM_HASH_free(package->package_var_symtable);
  }
  SPVM_HASH_free(runtime->package_symtable);

  // Free package variables heap
  free(runtime->package_vars_heap);
  
  // Free runtime
  free(runtime);
}
