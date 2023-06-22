// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

#include "spvm_native.h"

#include "spvm_api.h"
#include "spvm_vm.h"
#include "spvm_api_runtime.h"
#include "spvm_api_allocator.h"
#include "spvm_api_string_buffer.h"
#include "spvm_opcode.h"

#include "spvm_strerror.h"
#include "spvm_object.h"
#include "spvm_allocator.h"
#include "spvm_weaken_backref.h"
#include "spvm_hash.h"
#include "spvm_string_buffer.h"

#include "spvm_runtime.h"
#include "spvm_runtime_constant_string.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_class_var.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_method.h"

#include "spvm_implement.h"

#ifndef SPVM_NO_COMPILER_API
#  include "spvm_api_compiler.h"
#  include "spvm_api_precompile.h"
#endif

static const char* FILE_NAME = "spvm_api.c";

SPVM_ENV* SPVM_API_new_env_raw(void) {

  // Env Allocator
  SPVM_ENV_ALLOCATOR* env_allocator = SPVM_API_ALLOCATOR_new_env();

  // Env String Buffer
  SPVM_ENV_STRING_BUFFER* env_string_buffer = SPVM_API_STRING_BUFFER_new_env();

#ifdef SPVM_NO_COMPILER_API

  // Env Compiler
  SPVM_ENV_COMPILER* env_compiler = NULL;

  // Env Precompile
  SPVM_ENV_PRECOMPILE* env_precompile = NULL;
  

#else

  // Env Compiler
  SPVM_ENV_COMPILER* env_compiler = SPVM_API_COMPILER_new_env();

  // Env Precompile
  SPVM_ENV_PRECOMPILE* env_precompile = SPVM_API_PRECOMPILE_new_env();

#endif

  // Env Runtime
  SPVM_ENV_RUNTIME* env_runtime = SPVM_API_RUNTIME_new_env();

  // Env API
  void* env_api_init[]  = {
    env_allocator,
    env_string_buffer,
    env_compiler,
    env_precompile,
    env_runtime,
  };
  SPVM_ENV_API* env_api = calloc(1, sizeof(env_api_init));
  memcpy(env_api, env_api_init, sizeof(env_api_init));

  // Allocator
  SPVM_ALLOCATOR* allocator = SPVM_ALLOCATOR_new();














  // The impelements of Native APIs
  void* env_init[]  = {
    NULL, // class_vars_heap
    (void*)(intptr_t)sizeof(SPVM_OBJECT), // object_header_size
    (void*)(intptr_t)offsetof(SPVM_OBJECT, weaken_backref_head), // weaken_backref_head
    (void*)(intptr_t)offsetof(SPVM_OBJECT, ref_count), // object_ref_count_offset
    (void*)(intptr_t)-1,
    (void*)(intptr_t)offsetof(SPVM_OBJECT, type_dimension), // object_type_dimension_offset
    (void*)(intptr_t)offsetof(SPVM_OBJECT, flag), // object_flag_offset
    (void*)(intptr_t)offsetof(SPVM_OBJECT, length), // object_length_offset
    env_api,
    allocator, // allocator
    SPVM_API_new_env_raw,
    SPVM_API_free_env_raw,
    SPVM_API_isa,
    SPVM_API_elem_isa,
    NULL, // runtime
    SPVM_API_get_basic_type_id, // Asserted
    SPVM_API_get_field_id,
    SPVM_API_get_field_offset,
    SPVM_API_get_class_var,
    SPVM_API_get_class_method,
    SPVM_API_get_instance_method,
    SPVM_API_new_object_raw,
    SPVM_API_new_object,
    SPVM_API_new_byte_array_raw,
    SPVM_API_new_byte_array,
    SPVM_API_new_short_array_raw,
    SPVM_API_new_short_array,
    SPVM_API_new_int_array_raw,
    SPVM_API_new_int_array,
    SPVM_API_new_long_array_raw,
    SPVM_API_new_long_array,
    SPVM_API_new_float_array_raw,
    SPVM_API_new_float_array,
    SPVM_API_new_double_array_raw,
    SPVM_API_new_double_array,
    SPVM_API_new_object_array_raw,
    SPVM_API_new_object_array,
    SPVM_API_new_muldim_array_raw,
    SPVM_API_new_muldim_array,
    SPVM_API_new_mulnum_array_raw,
    SPVM_API_new_mulnum_array,
    SPVM_API_new_string_nolen_raw,
    SPVM_API_new_string_nolen,
    SPVM_API_new_string_raw,
    SPVM_API_new_string,
    SPVM_API_concat_raw,
    SPVM_API_concat,
    SPVM_API_new_stack_trace_raw,
    SPVM_API_new_stack_trace,
    SPVM_API_length,
    SPVM_API_get_elems_byte,
    SPVM_API_get_elems_short,
    SPVM_API_get_elems_int,
    SPVM_API_get_elems_long,
    SPVM_API_get_elems_float,
    SPVM_API_get_elems_double,
    SPVM_API_get_elem_object,
    SPVM_API_set_elem_object,
    SPVM_API_get_field_byte,
    SPVM_API_get_field_short,
    SPVM_API_get_field_int,
    SPVM_API_get_field_long,
    SPVM_API_get_field_float,
    SPVM_API_get_field_double,
    SPVM_API_get_field_object,
    SPVM_API_set_field_byte,
    SPVM_API_set_field_short,
    SPVM_API_set_field_int,
    SPVM_API_set_field_long,
    SPVM_API_set_field_float,
    SPVM_API_set_field_double,
    SPVM_API_set_field_object,
    SPVM_API_get_class_var_byte,
    SPVM_API_get_class_var_short,
    SPVM_API_get_class_var_int,
    SPVM_API_get_class_var_long,
    SPVM_API_get_class_var_float,
    SPVM_API_get_class_var_double,
    SPVM_API_get_class_var_object,
    SPVM_API_set_class_var_byte,
    SPVM_API_set_class_var_short,
    SPVM_API_set_class_var_int,
    SPVM_API_set_class_var_long,
    SPVM_API_set_class_var_float,
    SPVM_API_set_class_var_double,
    SPVM_API_set_class_var_object,
    SPVM_API_get_pointer,
    SPVM_API_set_pointer,
    SPVM_API_call_method_raw,
    SPVM_API_exception,
    SPVM_API_set_exception,
    SPVM_API_ref_count,
    SPVM_API_inc_ref_count,
    SPVM_API_dec_ref_count,
    SPVM_API_enter_scope,
    SPVM_API_push_mortal,
    SPVM_API_leave_scope,
    SPVM_API_remove_mortal,
    SPVM_API_is_type,
    SPVM_API_is_object_array,
    SPVM_API_get_object_basic_type_id,
    SPVM_API_get_object_type_dimension,
    SPVM_API_weaken,
    SPVM_API_isweak,
    SPVM_API_unweaken,
    SPVM_API_new_memory_env, // env->alloc_memory_block_zero
    SPVM_API_free_memory_env, // env->free_memory_block
    SPVM_API_get_memory_blocks_count_env, // env->get_memory_blocks_count
    SPVM_API_get_type_name_raw,
    SPVM_API_get_type_name,
    SPVM_API_new_env,
    SPVM_API_free_env,
    NULL, // memory_blocks_count
    SPVM_API_get_chars,
    SPVM_API_die,
    SPVM_API_new_object_by_name,
    SPVM_API_set_field_byte_by_name,
    SPVM_API_set_field_short_by_name,
    SPVM_API_set_field_int_by_name,
    SPVM_API_set_field_long_by_name,
    SPVM_API_set_field_float_by_name,
    SPVM_API_set_field_double_by_name,
    SPVM_API_set_field_object_by_name,
    SPVM_API_get_field_byte_by_name,
    SPVM_API_get_field_short_by_name,
    SPVM_API_get_field_int_by_name,
    SPVM_API_get_field_long_by_name,
    SPVM_API_get_field_float_by_name,
    SPVM_API_get_field_double_by_name,
    SPVM_API_get_field_object_by_name,
    SPVM_API_set_class_var_byte_by_name,
    SPVM_API_set_class_var_short_by_name,
    SPVM_API_set_class_var_int_by_name,
    SPVM_API_set_class_var_long_by_name,
    SPVM_API_set_class_var_float_by_name,
    SPVM_API_set_class_var_double_by_name,
    SPVM_API_set_class_var_object_by_name,
    SPVM_API_get_class_var_byte_by_name,
    SPVM_API_get_class_var_short_by_name,
    SPVM_API_get_class_var_int_by_name,
    SPVM_API_get_class_var_long_by_name,
    SPVM_API_get_class_var_float_by_name,
    SPVM_API_get_class_var_double_by_name,
    SPVM_API_get_class_var_object_by_name,
    SPVM_API_call_class_method_by_name,
    SPVM_API_call_instance_method_by_name,
    SPVM_API_get_field_string_chars_by_name,
    SPVM_API_free_env_prepared,
    SPVM_API_dump_raw,
    SPVM_API_dump,
    SPVM_API_get_instance_method_static,
    SPVM_API_get_bool_object_value,
    SPVM_API_cleanup_global_vars,
    SPVM_API_make_read_only,
    SPVM_API_is_read_only,
    SPVM_API_is_array,
    SPVM_API_is_string,
    SPVM_API_is_numeric_array,
    SPVM_API_is_mulnum_array,
    SPVM_API_get_elem_size,
    SPVM_API_new_array_proto_raw,
    SPVM_API_new_array_proto,
    SPVM_API_copy_raw,
    SPVM_API_copy,
    SPVM_API_shorten,
    SPVM_API_has_interface,
    SPVM_API_print,
    SPVM_API_print_stderr,
    SPVM_API_init_env,
    SPVM_API_call_init_blocks,
    NULL, // reserved170
    SPVM_API_new_stack,
    SPVM_API_free_stack,
    SPVM_API_new_memory_env,
    SPVM_API_free_memory_env,
    SPVM_API_get_memory_blocks_count_env,
    SPVM_API_new_memory_stack,
    SPVM_API_free_memory_stack,
    SPVM_API_get_memory_blocks_count_stack,
    SPVM_API_set_command_info_program_name,
    SPVM_API_set_command_info_argv,
    NULL, // reserved19
    SPVM_API_strerror,
    SPVM_API_new_string_array,
    SPVM_API_get_args_stack_length,
    SPVM_API_set_args_stack_length,
    SPVM_API_dumpc,
    SPVM_API_new_pointer_object_raw,
    SPVM_API_new_pointer_object,
    SPVM_API_new_pointer_object_by_name,
    SPVM_API_get_elem_string,
    SPVM_API_set_elem_string,
    SPVM_API_is_class,
    SPVM_API_is_pointer_class,
    SPVM_API_strerror_string,
    SPVM_API_get_basic_type_id_by_name, // Asserted
    SPVM_API_get_field_id_static, // Asserted
    SPVM_API_items,
    SPVM_API_call_instance_method_static_by_name,
    SPVM_API_get_method,
    SPVM_API_strerror_nolen,
    SPVM_API_strerror_string_nolen,
    SPVM_API_get_compile_type_name_raw,
    SPVM_API_get_compile_type_name,
    SPVM_API_set_command_info_base_time,
    SPVM_API_get_spvm_version_string,
    SPVM_API_get_spvm_version_number,
    SPVM_API_get_version_string,
    SPVM_API_get_version_number,
    SPVM_API_call_method,
    NULL, // init_flags
    SPVM_API_get_object_basic_type_name,
    SPVM_API_isa_by_name,
    SPVM_API_is_type_by_name,
    SPVM_API_new_object_array_by_name,
    SPVM_API_new_muldim_array_by_name,
    SPVM_API_new_mulnum_array_by_name,
    SPVM_API_has_interface_by_name,
    SPVM_API_get_field_byte_v2,
    SPVM_API_get_field_short_v2,
    SPVM_API_get_field_int_v2,
    SPVM_API_get_field_long_v2,
    SPVM_API_get_field_float_v2,
    SPVM_API_get_field_double_v2,
    SPVM_API_get_field_object_v2,
    SPVM_API_set_field_byte_v2,
    SPVM_API_set_field_short_v2,
    SPVM_API_set_field_int_v2,
    SPVM_API_set_field_long_v2,
    SPVM_API_set_field_float_v2,
    SPVM_API_set_field_double_v2,
    SPVM_API_set_field_object_v2,
    SPVM_API_get_field,
  };
  SPVM_ENV* env = calloc(1, sizeof(env_init));
  if (env == NULL) {
    return NULL;
  }
  memcpy(env, env_init, sizeof(env_init));

  return env;
}

SPVM_OBJECT* SPVM_API_new_object_common(SPVM_ENV* env, SPVM_VALUE* stack, size_t alloc_size, int32_t basic_type_id, int32_t type_dimension, int32_t length, int32_t flag) {
  
  SPVM_OBJECT* object = SPVM_API_new_memory_stack(env, stack, alloc_size);
  
  if (object) {
    object->basic_type_id = basic_type_id;
    object->type_dimension = type_dimension;
    object->length = length;
    object->flag = flag;
  }
  
  return object;
}

int32_t SPVM_API_init_env(SPVM_ENV* env) {
  
  SPVM_RUNTIME* runtime = env->runtime;

  // Initialize Class Variables
  void* class_vars_heap = SPVM_API_new_memory_env(env, sizeof(SPVM_VALUE) * ((int64_t)runtime->class_vars_length + 1));
  if (class_vars_heap == NULL) {
    return 2;
  }
  
  env->class_vars_heap = class_vars_heap;
  
  // Initialize class initialized flags
  void* init_flags = SPVM_API_new_memory_env(env, sizeof(int32_t) * ((int64_t)runtime->basic_types_length + 1));
  if (init_flags == NULL) {
    return 2;
  }
  
  env->init_flags = init_flags;
  
  // Adjust alignment SPVM_VALUE
  int32_t object_header_size = sizeof(SPVM_OBJECT);
  if (object_header_size % sizeof(SPVM_VALUE) != 0) {
    object_header_size += (sizeof(SPVM_VALUE) - object_header_size % sizeof(SPVM_VALUE));
  }
  assert(object_header_size % sizeof(SPVM_VALUE) == 0);
  
  // Object header byte size
  env->object_header_size = (void*)(intptr_t)object_header_size;
  
  return 0;
}

void SPVM_API_make_read_only(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string) {
  int32_t string_basci_type_id = SPVM_API_get_object_basic_type_id(env, stack, string);
  if (string && string_basci_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && string->type_dimension == 0) {
    string->flag |= SPVM_OBJECT_C_FLAG_IS_READ_ONLY;
  }
}

int32_t SPVM_API_is_read_only(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string) {
  
  int32_t is_read_only;
  if (string) {
    if (string->flag & SPVM_OBJECT_C_FLAG_IS_READ_ONLY) {
      is_read_only = 1;
    }
    else {
      is_read_only = 0;
    }
  }
  else {
    is_read_only = 0;
  }
  
  return is_read_only;
}

SPVM_OBJECT* SPVM_API_dump(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  SPVM_OBJECT* str = SPVM_API_dump_raw(env, stack, object);
  
  SPVM_API_push_mortal(env, stack, str);
  
  return str;
}

SPVM_OBJECT* SPVM_API_dump_raw(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t depth = 0;
  SPVM_STRING_BUFFER* string_buffer = SPVM_STRING_BUFFER_new(runtime->allocator, 255, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  SPVM_HASH* address_symtable = SPVM_HASH_new(runtime->allocator, 255, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  
  SPVM_API_dump_recursive(env, stack, object, &depth, string_buffer, address_symtable);
  
  int32_t string_buffer_length = string_buffer->length;
  
  SPVM_OBJECT* dump = SPVM_API_new_string_raw(env, stack, string_buffer->value, string_buffer->length);
  
  SPVM_HASH_free(address_symtable);
  address_symtable = NULL;
  
  SPVM_STRING_BUFFER_free(string_buffer);
  string_buffer = NULL;
  
  return dump;
}

const char* SPVM_API_dumpc(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  SPVM_OBJECT* obj_dump = SPVM_API_dump(env, stack, object);
  
  const char* dump_chars = env->get_chars(env, stack, obj_dump);
  
  return dump_chars;
}

void SPVM_API_dump_recursive(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t* depth, SPVM_STRING_BUFFER* string_buffer, SPVM_HASH* address_symtable) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  char tmp_buffer[256];
  
  SPVM_OBJECT* dump;
  if (object == NULL) {
    SPVM_STRING_BUFFER_add(string_buffer, "undef");
  }
  else {
    int32_t type_dimension = object->type_dimension;
    
    if (SPVM_API_is_string(env, stack, object)) {
      const char* chars = env->get_chars(env, stack, object);
      int32_t chars_length  = env->length(env, stack, object);
      SPVM_STRING_BUFFER_add(string_buffer, "\"");
      SPVM_STRING_BUFFER_add_len(string_buffer, (char*)chars, chars_length);
      SPVM_STRING_BUFFER_add(string_buffer, "\"");
    }
    else if (type_dimension > 0) {
      int32_t array_length = object->length;
      int32_t element_type_dimension = type_dimension - 1;
      
      SPVM_STRING_BUFFER_add(string_buffer, "[\n");
            
      int32_t basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, object);
      const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
          
      for (int32_t array_index = 0; array_index < array_length; array_index++) {
        
        for (int32_t depth_index = 0; depth_index < *depth + 1; depth_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
        }
        
        if (SPVM_API_is_mulnum_array(env, stack, object)) {
          
          SPVM_STRING_BUFFER_add(string_buffer, "{\n");
          
          SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, basic_type_id);
          int32_t fields_length = basic_type->fields_length;
          
          for (int32_t field_index = 0; field_index < fields_length; field_index++) {
            for (int32_t depth_index = 0; depth_index < *depth + 2; depth_index++) {
              SPVM_STRING_BUFFER_add(string_buffer, "  ");
            }
            
            SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, basic_type->fields_base_address_id + field_index);
            
            int32_t field_basic_type_id = field->basic_type_id;
            
            const char* field_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, field->name_id, NULL);
            SPVM_STRING_BUFFER_add(string_buffer, field_name);
            SPVM_STRING_BUFFER_add(string_buffer, " => ");
            
            switch (field_basic_type_id) {
              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                int8_t* element = &((int8_t*)((intptr_t)object + env->object_header_size))[array_index * fields_length];
                sprintf(tmp_buffer, "%d", element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                int16_t* element = &((int16_t*)((intptr_t)object + env->object_header_size))[array_index * fields_length];
                sprintf(tmp_buffer, "%d", element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                int32_t* element = &((int32_t*)((intptr_t)object + env->object_header_size))[array_index * fields_length];
                sprintf(tmp_buffer, "%d", element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                int64_t* element = &((int64_t*)((intptr_t)object + env->object_header_size))[array_index * fields_length];
                sprintf(tmp_buffer, "%lld", (long long int)element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                float* element = &((float*)((intptr_t)object + env->object_header_size))[array_index * fields_length];
                sprintf(tmp_buffer, "%g", element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                double* element = &((double*)((intptr_t)object + env->object_header_size))[array_index * fields_length];
                sprintf(tmp_buffer, "%g", element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
            }
            
            if (field_index == fields_length - 1) {
              SPVM_STRING_BUFFER_add(string_buffer, "\n");
            }
            else {
              SPVM_STRING_BUFFER_add(string_buffer, ",\n");
            }
          }
          
          SPVM_STRING_BUFFER_add(string_buffer, "  }");
        }
        else if (SPVM_API_is_numeric_array(env, stack, object)) {
          switch (basic_type_id) {
            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
              int8_t element = ((int8_t*)((intptr_t)object + env->object_header_size))[array_index];
              sprintf(tmp_buffer, "%d", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
              int16_t element = ((int16_t*)((intptr_t)object + env->object_header_size))[array_index];
              sprintf(tmp_buffer, "%d", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
              int32_t element = ((int32_t*)((intptr_t)object + env->object_header_size))[array_index];
              sprintf(tmp_buffer, "%d", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
              int64_t element = ((int64_t*)((intptr_t)object + env->object_header_size))[array_index];
              sprintf(tmp_buffer, "%lld", (long long int)element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
              float element = ((float*)((intptr_t)object + env->object_header_size))[array_index];
              sprintf(tmp_buffer, "%g", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
              double element = ((double*)((intptr_t)object + env->object_header_size))[array_index];
              sprintf(tmp_buffer, "%g", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
          }
        }
        else if (SPVM_API_is_object_array(env, stack, object)) {
          SPVM_OBJECT* element = (((SPVM_OBJECT**)((intptr_t)object + env->object_header_size))[array_index]);
          element = SPVM_IMPLEMENT_GET_OBJECT_NO_WEAKEN_ADDRESS(env, stack, element);
          (*depth)++;
          SPVM_API_dump_recursive(env, stack, element, depth, string_buffer, address_symtable);
          (*depth)--;
        }
        else {
          assert(0);
        }
        
        if (array_index == array_length - 1) {
          SPVM_STRING_BUFFER_add(string_buffer, "\n");
        }
        else {
          SPVM_STRING_BUFFER_add(string_buffer, ",\n");
        }
      }
      
      for (int32_t depth_index = 0; depth_index < *depth; depth_index++) {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
      }
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      
      SPVM_STRING_BUFFER_add(string_buffer, " : ");
      SPVM_STRING_BUFFER_add(string_buffer, basic_type_name);
      for (int32_t type_dimension_index = 0; type_dimension_index < type_dimension; type_dimension_index++) {
        SPVM_STRING_BUFFER_add(string_buffer, "[]");
      }
      
      // If the object is weaken, this get the real address
      sprintf(tmp_buffer, "(%p)", SPVM_IMPLEMENT_GET_OBJECT_NO_WEAKEN_ADDRESS(env, stack, object));
      SPVM_STRING_BUFFER_add(string_buffer, tmp_buffer);
    }
    else {
      // If the object is weaken, this get the real address
      sprintf(tmp_buffer, "%p", SPVM_IMPLEMENT_GET_OBJECT_NO_WEAKEN_ADDRESS(env, stack, object));
      int32_t exists = (int32_t)(intptr_t)SPVM_HASH_get(address_symtable, tmp_buffer, strlen(tmp_buffer));
      if (exists) {
        // If the object is weaken, this get the real address
        sprintf(tmp_buffer, "REUSE_OBJECT(%p)", SPVM_IMPLEMENT_GET_OBJECT_NO_WEAKEN_ADDRESS(env, stack, object));
        SPVM_STRING_BUFFER_add(string_buffer, tmp_buffer);
      }
      else {
        int32_t basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, object);
        const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
        
        SPVM_HASH_set(address_symtable, tmp_buffer, strlen(tmp_buffer), (void*)(intptr_t)1);
        
        SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, basic_type_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, basic_type_name);
        sprintf(tmp_buffer, " (%p) ", object);
        SPVM_STRING_BUFFER_add(string_buffer, tmp_buffer);
        
        SPVM_STRING_BUFFER_add(string_buffer, "{\n");
        
        // Free object fields
        int32_t fields_length = basic_type->fields_length;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          for (int32_t depth_index = 0; depth_index < *depth + 1; depth_index++) {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
          }
          
          SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, basic_type->fields_base_address_id + field_index);
          
          int32_t field_basic_type_id = field->basic_type_id;
          int32_t field_type_dimension = field->type_dimension;
          int32_t field_offset = field->offset;
          const char* field_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, field->name_id, NULL);
          
          SPVM_STRING_BUFFER_add(string_buffer, field_name);
          SPVM_STRING_BUFFER_add(string_buffer, " => ");
          if (field_type_dimension == 0 && field_basic_type_id >= SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE && field_basic_type_id <= SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
            switch (field_basic_type_id) {
              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                int8_t field_value = *(int8_t*)((intptr_t)object + (size_t)env->object_header_size + field_offset);
                sprintf(tmp_buffer, "%d", field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                int16_t field_value = *(int16_t*)((intptr_t)object + (size_t)env->object_header_size + field_offset);
                sprintf(tmp_buffer, "%d", field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                int32_t field_value = *(int32_t*)((intptr_t)object + (size_t)env->object_header_size + field_offset);
                sprintf(tmp_buffer, "%d", field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                int64_t field_value = *(int64_t*)((intptr_t)object + (size_t)env->object_header_size + field_offset);
                sprintf(tmp_buffer, "%lld", (long long int)field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                float field_value = *(float*)((intptr_t)object + (size_t)env->object_header_size + field_offset);
                sprintf(tmp_buffer, "%g", field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                double field_value = *(double*)((intptr_t)object + (size_t)env->object_header_size + field_offset);
                sprintf(tmp_buffer, "%g", field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              default : {
                assert(0);
              }
            }
          }
          else  {
            SPVM_OBJECT* field_value = *(SPVM_OBJECT**)((intptr_t)object + (size_t)env->object_header_size + field_offset);
            field_value = SPVM_IMPLEMENT_GET_OBJECT_NO_WEAKEN_ADDRESS(env, stack, field_value);
            (*depth)++;
            SPVM_API_dump_recursive(env, stack, field_value, depth, string_buffer, address_symtable);
            (*depth)--;
          }
          
          if (field_index == fields_length - 1) {
            SPVM_STRING_BUFFER_add(string_buffer, "\n");
          }
          else {
            SPVM_STRING_BUFFER_add(string_buffer, ",\n");
          }
        }
        
        for (int32_t depth_index = 0; depth_index < *depth; depth_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
        }
        SPVM_STRING_BUFFER_add(string_buffer, "}");
      }
    }
  }
}

int32_t SPVM_API_call_class_method_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name, int32_t args_stack_length, const char* func_name, const char* file, int32_t line) {
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method_by_name(env->runtime, basic_type_id, method_name);
  if (!method) {
    env->die(env, stack, "The %s class method in the %s class is not found", method_name, basic_type_name, func_name, file, line);
    return 1;
  }
  int32_t e = env->call_method_raw(env, stack, method, args_stack_length);
  if (e) {
    const char* message = env->get_chars(env, stack, env->get_exception(env, stack));
    env->die(env, stack, "%s", message, func_name, file, line);
    return e;
  }
  
  return 0;
}

int32_t SPVM_API_call_instance_method_static_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name, int32_t args_stack_length, const char* func_name, const char* file, int32_t line) {
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method_by_name(env->runtime, basic_type_id, method_name);
  if (!method) {
    env->die(env, stack, "The %s instance method in the %s class is not found", method_name, basic_type_name, func_name, file, line);
    return 1;
  }
  int32_t e = env->call_method_raw(env, stack, method, args_stack_length);
  if (e) {
    const char* message = env->get_chars(env, stack, env->get_exception(env, stack));
    env->die(env, stack, "%s", message, func_name, file, line);
    return e;
  }
  
  return 0;
}

int32_t SPVM_API_call_instance_method_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t args_stack_length, const char* func_name, const char* file, int32_t line) {
  
  SPVM_OBJECT* object = stack[0].oval;
  
  if (object == NULL) {
    env->die(env, stack, "The object must be defined", func_name, file, line);
    return 1;
  };
  
  if (object->type_dimension > 0) {
    env->die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return 1;
  };
  
  SPVM_RUNTIME_METHOD* method = env->get_instance_method(env, stack, object, method_name);
  if (!method) {
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    env->die(env, stack, "The %s instance method is not found in the %s class or its super class", method_name, basic_type_name, func_name, file, line);
    return 1;
  };
  
  int32_t e = env->call_method_raw(env, stack, method, args_stack_length);
  
  if (e) {
    const char* message = env->get_chars(env, stack, env->get_exception(env, stack));
    env->die(env, stack, "%s", message, func_name, file, line);
    return e;
  }
  
  return 0;
}

void* SPVM_API_new_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    env->die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error = 1;
    return NULL;
  };
  
  void* object = env->new_object(env, stack, basic_type_id);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_pointer_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, void* pointer, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    *error = 1;
    env->die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    return NULL;
  };
  SPVM_OBJECT* object = env->new_pointer_object(env, stack, basic_type_id, pointer);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_object_array_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t length, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    env->die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error = 1;
    return NULL;
  };
  
  void* object = env->new_object_array(env, stack, basic_type_id, length);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_muldim_array_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t type_dimension, int32_t length, int32_t* error, const char* func_name, const char* file, int32_t line) {  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    env->die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error = 1;
    return NULL;
  };
  
  void* object = env->new_muldim_array(env, stack, basic_type_id, type_dimension, length);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_mulnum_array_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t length, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    env->die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error = 1;
    return NULL;
  };
  
  void* object = env->new_mulnum_array(env, stack, basic_type_id, length);
  
  return object;
}

int8_t SPVM_API_get_field_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  if (object == NULL) {
    env->die(env, stack, "The object must be defined", func_name, file, line);
    return 0;
  };
  
  if (object->type_dimension > 0) {
    env->die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = env->get_field(env, stack, object, field_name);
  if (!field) {
    *error = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    env->die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return 0;
  };
  int8_t value = env->get_field_byte_v2(env, stack, object, field);
  return value;
}

int16_t SPVM_API_get_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  if (object == NULL) {
    env->die(env, stack, "The object must be defined", func_name, file, line);
    return 0;
  };
  
  if (object->type_dimension > 0) {
    env->die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = env->get_field(env, stack, object, field_name);
  if (!field) {
    *error = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    env->die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return 0;
  };
  int16_t value = env->get_field_short_v2(env, stack, object, field);
  return value;
}

int32_t SPVM_API_get_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  if (object == NULL) {
    env->die(env, stack, "The object must be defined", func_name, file, line);
    return 0;
  };
  
  if (object->type_dimension > 0) {
    env->die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = env->get_field(env, stack, object, field_name);
  if (!field) {
    *error = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    env->die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return 0;
  };
  int32_t value = env->get_field_int_v2(env, stack, object, field);
  return value;
}

int64_t SPVM_API_get_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  if (object == NULL) {
    env->die(env, stack, "The object must be defined", func_name, file, line);
    return 0;
  };
  
  if (object->type_dimension > 0) {
    env->die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = env->get_field(env, stack, object, field_name);
  if (!field) {
    *error = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    env->die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return 0;
  };
  int64_t value = env->get_field_long_v2(env, stack, object, field);
  return value;
}

float SPVM_API_get_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  if (object == NULL) {
    env->die(env, stack, "The object must be defined", func_name, file, line);
    return 0;
  };
  
  if (object->type_dimension > 0) {
    env->die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = env->get_field(env, stack, object, field_name);
  if (!field) {
    *error = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    env->die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return 0;
  };
  float value = env->get_field_float_v2(env, stack, object, field);
  return value;
}

double SPVM_API_get_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  if (object == NULL) {
    env->die(env, stack, "The object must be defined", func_name, file, line);
    return 0;
  };
  
  if (object->type_dimension > 0) {
    env->die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return 0;
  };
  
  SPVM_RUNTIME_FIELD* field = env->get_field(env, stack, object, field_name);
  if (!field) {
    *error = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    env->die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return 0;
  };
  double value = env->get_field_double_v2(env, stack, object, field);
  return value;
}

SPVM_OBJECT* SPVM_API_get_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  if (object == NULL) {
    env->die(env, stack, "The object must be defined", func_name, file, line);
    return NULL;
  };
  
  if (object->type_dimension > 0) {
    env->die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return NULL;
  };
  
  SPVM_RUNTIME_FIELD* field = env->get_field(env, stack, object, field_name);
  if (!field) {
    *error = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    env->die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return NULL;
  };
  SPVM_OBJECT* value = env->get_field_object_v2(env, stack, object, field);
  return value;
}

const char* SPVM_API_get_field_string_chars_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  SPVM_RUNTIME_FIELD* field = env->get_field(env, stack, object, field_name);
  if (!field) {
    *error = 1;
    env->die(env, stack, "The %s field is not found", field_name, func_name, file, line);
    return NULL;
  };
  SPVM_OBJECT* value = env->get_field_object_v2(env, stack, object, field);
  if (value == NULL) {
    return NULL;
  }
  else {
    const char* chars = env->get_chars(env, stack, value);
    return chars;
  }
}

void SPVM_API_set_field_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int8_t value, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  if (object == NULL) {
    env->die(env, stack, "The object must be defined", func_name, file, line);
    return;
  };
  
  if (object->type_dimension > 0) {
    env->die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = env->get_field(env, stack, object, field_name);
  if (!field) {
    *error = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    env->die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return;
  }
  env->set_field_byte_v2(env, stack, object, field, value);
}

void SPVM_API_set_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int16_t value, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  if (object == NULL) {
    env->die(env, stack, "The object must be defined", func_name, file, line);
    return;
  };
  
  if (object->type_dimension > 0) {
    env->die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = env->get_field(env, stack, object, field_name);
  if (!field) {
    *error = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    env->die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return;
  };
  env->set_field_short_v2(env, stack, object, field, value);
}

void SPVM_API_set_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t value, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  if (object == NULL) {
    env->die(env, stack, "The object must be defined", func_name, file, line);
    return;
  };
  
  if (object->type_dimension > 0) {
    env->die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = env->get_field(env, stack, object, field_name);
  if (!field) {
    *error = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    env->die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return;
  };
  env->set_field_int_v2(env, stack, object, field, value);
}

void SPVM_API_set_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int64_t value, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  if (object == NULL) {
    env->die(env, stack, "The object must be defined", func_name, file, line);
    return;
  };
  
  if (object->type_dimension > 0) {
    env->die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = env->get_field(env, stack, object, field_name);
  if (!field) {
    *error = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    env->die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return;
  };
  env->set_field_long_v2(env, stack, object, field, value);
}

void SPVM_API_set_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, float value, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  if (object == NULL) {
    env->die(env, stack, "The object must be defined", func_name, file, line);
    return;
  };
  
  if (object->type_dimension > 0) {
    env->die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = env->get_field(env, stack, object, field_name);
  if (!field) {
    *error = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    env->die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return;
  };
  env->set_field_float_v2(env, stack, object, field, value);
}

void SPVM_API_set_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, double value, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  if (object == NULL) {
    env->die(env, stack, "The object must be defined", func_name, file, line);
    return;
  };
  
  if (object->type_dimension > 0) {
    env->die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = env->get_field(env, stack, object, field_name);
  if (!field) {
    *error = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    env->die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return;
  };
  env->set_field_double_v2(env, stack, object, field, value);
}

void SPVM_API_set_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, SPVM_OBJECT* value, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  if (object == NULL) {
    env->die(env, stack, "The object must be defined", func_name, file, line);
    return;
  };
  
  if (object->type_dimension > 0) {
    env->die(env, stack, "The type dimension of the object must be equal to 0", func_name, file, line);
    return;
  };
  
  SPVM_RUNTIME_FIELD* field = env->get_field(env, stack, object, field_name);
  if (!field) {
    *error = 1;
    const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
    env->die(env, stack, "The %s field is not found in the %s class or its super class", field_name, basic_type_name, func_name, file, line);
    return;
  };
  env->set_field_object_v2(env, stack, object, field, value);
}

int8_t SPVM_API_get_class_var_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    env->die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error = 1;
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_name(env->runtime, basic_type_id, class_var_name);
  if (!class_var) {
    *error = 1;
    env->die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return 0;
  };
  
  int8_t value = env->get_class_var_byte(env, stack, class_var);
  return value;
}

int16_t SPVM_API_get_class_var_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    env->die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error = 1;
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_name(env->runtime, basic_type_id, class_var_name);
  if (!class_var) {
    *error = 1;
    env->die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return 0;
  };
  
  int16_t value = env->get_class_var_short(env, stack, class_var);
  return value;
}

int32_t SPVM_API_get_class_var_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    env->die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error = 1;
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_name(env->runtime, basic_type_id, class_var_name);
  if (!class_var) {
    *error = 1;
    env->die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return 0;
  };
  
  int32_t value = env->get_class_var_int(env, stack, class_var);
  return value;
}

int64_t SPVM_API_get_class_var_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    env->die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error = 1;
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_name(env->runtime, basic_type_id, class_var_name);
  if (!class_var) {
    *error = 1;
    env->die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return 0;
  };
  
  int64_t value = env->get_class_var_long(env, stack, class_var);
  return value;
}

float SPVM_API_get_class_var_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    env->die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error = 1;
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_name(env->runtime, basic_type_id, class_var_name);
  if (!class_var) {
    *error = 1;
    env->die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return 0;
  };
  
  float value = env->get_class_var_float(env, stack, class_var);
  return value;
}

double SPVM_API_get_class_var_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    env->die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error = 1;
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_name(env->runtime, basic_type_id, class_var_name);
  if (!class_var) {
    *error = 1;
    env->die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return 0;
  };
  
  double value = env->get_class_var_double(env, stack, class_var);
  return value;
}

SPVM_OBJECT* SPVM_API_get_class_var_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    env->die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error = 1;
    return 0;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_name(env->runtime, basic_type_id, class_var_name);
  if (!class_var) {
    *error = 1;
    env->die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return 0;
  };
  
  SPVM_OBJECT* value = env->get_class_var_object(env, stack, class_var);
  return value;
}

void SPVM_API_set_class_var_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int8_t value, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    env->die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error = 1;
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_name(env->runtime, basic_type_id, class_var_name);
  if (!class_var) {
    *error = 1;
    env->die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return;
  };
  
  env->set_class_var_byte(env, stack, class_var, value);
}

void SPVM_API_set_class_var_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int16_t value, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    env->die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error = 1;
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_name(env->runtime, basic_type_id, class_var_name);
  if (!class_var) {
    *error = 1;
    env->die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return;
  };
  
  env->set_class_var_short(env, stack, class_var, value);
}

void SPVM_API_set_class_var_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t value, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    env->die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error = 1;
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_name(env->runtime, basic_type_id, class_var_name);
  if (!class_var) {
    *error = 1;
    env->die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return;
  };
  
  env->set_class_var_int(env, stack, class_var, value);
}

void SPVM_API_set_class_var_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int64_t value, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    env->die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error = 1;
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_name(env->runtime, basic_type_id, class_var_name);
  if (!class_var) {
    *error = 1;
    env->die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return;
  };
  
  env->set_class_var_long(env, stack, class_var, value);
}

void SPVM_API_set_class_var_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, float value, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    env->die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error = 1;
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_name(env->runtime, basic_type_id, class_var_name);
  if (!class_var) {
    *error = 1;
    env->die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return;
  };
  
  env->set_class_var_float(env, stack, class_var, value);
}

void SPVM_API_set_class_var_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, double value, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    env->die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error = 1;
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_name(env->runtime, basic_type_id, class_var_name);
  if (!class_var) {
    *error = 1;
    env->die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return;
  };
  
  env->set_class_var_double(env, stack, class_var, value);
}

void SPVM_API_set_class_var_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, SPVM_OBJECT* value, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    env->die(env, stack, "The %s class is not found", basic_type_name, func_name, file, line);
    *error = 1;
    return;
  }
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_name(env->runtime, basic_type_id, class_var_name);
  if (!class_var) {
    *error = 1;
    env->die(env, stack, "The %s class variable in the %s class is not found", class_var_name, basic_type_name, func_name, file, line);
    return;
  };
  
  env->set_class_var_object(env, stack, class_var, value);
}

int32_t SPVM_API_die(SPVM_ENV* env, SPVM_VALUE* stack, const char* message, ...) {
  
  va_list args;
  
  char* message_with_line = (char*)SPVM_API_new_memory_stack(env, stack, 512);
  int32_t message_length = strlen(message);
  if (message_length > 255) {
    message_length = 255;
  }
  memcpy(message_with_line, message, message_length);
  const char* place = "\n    %s at %s line %d";
  memcpy(message_with_line + message_length, place, strlen(place));

  char* buffer = (char*)SPVM_API_new_memory_stack(env, stack, 512);
  va_start(args, message);
  vsnprintf(buffer, 511, message_with_line, args);
  va_end(args);
  
  void* exception = env->new_string_raw(env, stack, buffer, strlen(buffer));
  
  SPVM_API_free_memory_stack(env, stack, message_with_line);
  message_with_line = NULL;
  
  SPVM_API_free_memory_stack(env, stack, buffer);
  buffer = NULL;
  
  env->set_exception(env, stack, exception);
  
  return SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
}

int32_t SPVM_API_remove_mortal(SPVM_ENV* env, SPVM_VALUE* stack, int32_t original_mortal_stack_top, SPVM_OBJECT* remove_object) {
  (void)env;

  SPVM_OBJECT*** cur_mortal_stack_ptr = (SPVM_OBJECT***)&stack[STACK_INDEX_MORTAL_STACK];
  int32_t* cur_mortal_stack_top_ptr = (int32_t*)&stack[STACK_INDEX_MORTAL_STACK_TOP];
  int32_t* cur_mortal_stack_capacity_ptr = (int32_t*)&stack[STACK_INDEX_MORTAL_STACK_CAPACITY];

  int32_t remove_count = 0;
  if (remove_object != NULL) {
    int32_t match_mortal_stack_index = -1;
    for (int32_t mortal_stack_index = original_mortal_stack_top; mortal_stack_index < *cur_mortal_stack_top_ptr; mortal_stack_index++) {
      SPVM_OBJECT* object = (*cur_mortal_stack_ptr)[mortal_stack_index];
      
      if (remove_object == object) {
        remove_count++;
        match_mortal_stack_index = mortal_stack_index;
        SPVM_API_dec_ref_count(env, stack, object);
      }
    }
    
    if (remove_count) {
      for (int32_t mortal_stack_index = match_mortal_stack_index; mortal_stack_index < *cur_mortal_stack_top_ptr; mortal_stack_index++) {
        (*cur_mortal_stack_ptr)[mortal_stack_index] = (*cur_mortal_stack_ptr)[mortal_stack_index + 1];
      }
      *cur_mortal_stack_top_ptr = *cur_mortal_stack_top_ptr - remove_count;
    }
  }
  return remove_count;
}

void SPVM_API_cleanup_global_vars(SPVM_ENV* env, SPVM_VALUE* stack){

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  assert(runtime);
  
  // Free exception
  SPVM_API_set_exception(env, stack, NULL);

  // Free objects of class variables
  for (int32_t basic_type_id = 0; basic_type_id < runtime->basic_types_length; basic_type_id++) {
    SPVM_RUNTIME_BASIC_TYPE* basic_type = env->api->runtime->get_basic_type(env->runtime, basic_type_id);
    
    for (int32_t class_var_index = 0; class_var_index < basic_type->class_vars_length; class_var_index++) {
      
      SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var(runtime, basic_type_id, class_var_index);
      
      int32_t class_var_basic_type_id = env->api->runtime->get_class_var_basic_type_id(runtime, class_var);
      int32_t class_var_type_dimension = env->api->runtime->get_class_var_type_dimension(runtime, class_var);
      int32_t class_var_type_flag = env->api->runtime->get_class_var_type_flag(runtime, class_var);
      
      int32_t class_var_type_is_object = env->api->runtime->is_object_type(runtime, class_var_basic_type_id, class_var_type_dimension, class_var_type_flag);
      if (class_var_type_is_object) {
        SPVM_OBJECT* object = *(void**)&((SPVM_VALUE*)env->class_vars_heap)[basic_type->class_vars_base_address_id + class_var_index];
        if (object) {
          SPVM_API_dec_ref_count(env, stack, object);
        }
      }
    }
  }
}

void SPVM_API_free_env_raw(SPVM_ENV* env) {

  // Free class variables heap
  if (env->class_vars_heap != NULL) {
    free(env->class_vars_heap);
    env->class_vars_heap = NULL;
  }
  
  // Free class initialized flags
  if (env->init_flags != NULL) {
    free(env->init_flags);
    env->init_flags = NULL;
  }
  
  // Free env api
  free(env->api->allocator);
  free(env->api->string_buffer);
  free(env->api->compiler);
  free(env->api->precompile);
  free(env->api->runtime);
  free(env->api);
  
  // Free allocator
  free(env->allocator);
  
  // Free env
  free(env);
  env = NULL;
}

SPVM_VALUE* SPVM_API_new_stack(SPVM_ENV* env) {
  
  // Arguments and return values : 0-255
  // Stack local varialbe : 256-511
  //   Exception message 511
  //   Mortal stack 510
  //   Motal stack top 509
  //   Motal stack capacity 508
  
  SPVM_VALUE* stack = SPVM_API_new_memory_env(env, sizeof(SPVM_VALUE) * 512);

  // Mortal stack
  int32_t native_mortal_stack_capacity = 1;
  void* native_mortal_stack = SPVM_API_new_memory_stack(env, stack, sizeof(SPVM_OBJECT*) * native_mortal_stack_capacity);
  if (native_mortal_stack == NULL) {
    return NULL;
  }
  stack[STACK_INDEX_MORTAL_STACK_CAPACITY].ival = native_mortal_stack_capacity;
  stack[STACK_INDEX_MORTAL_STACK].oval = native_mortal_stack;
  
  return stack;
}

void SPVM_API_free_stack(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  // Free exception
  env->set_exception(env, stack, NULL);
  
  // Free mortal stack
  SPVM_OBJECT** mortal_stack = stack[STACK_INDEX_MORTAL_STACK].oval;
  
  if (mortal_stack != NULL) {
    SPVM_API_free_memory_stack(env, stack, mortal_stack);
    mortal_stack = NULL;
  }
  
  SPVM_API_free_memory_env(env, stack);
  stack = NULL;
}

int32_t SPVM_API_call_method_raw(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* method, int32_t args_stack_length) {
  
  int32_t mortal = 0;
  int32_t e = SPVM_API_call_method_common(env, stack, method, args_stack_length, mortal);
  
  return e;
}

int32_t SPVM_API_call_method(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* method, int32_t args_stack_length) {
  
  int32_t mortal = 1;
  int32_t e = SPVM_API_call_method_common(env, stack, method, args_stack_length, mortal);
  
  return e;
}

int32_t SPVM_API_call_method_common(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* method, int32_t args_stack_length, int32_t mortal) {
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t error = 0;
  stack[STACK_INDEX_ARGS_STACK_LENGTH].ival = args_stack_length;
  stack[STACK_INDEX_CALL_DEPTH].ival++;
  
  int32_t max_call_depth = 10000;
  if (stack[STACK_INDEX_CALL_DEPTH].ival > max_call_depth) {
    error = env->die(env, stack, "Deep recursion occurs. The depth of a method call must be less than %d", max_call_depth, FILE_NAME, __LINE__);
  }
  else {
    int32_t method_return_basic_type_id = method->return_basic_type_id;
    int32_t method_return_type_dimension = method->return_type_dimension;
    int32_t method_return_type_flag = method->return_type_flag;
    
    int32_t current_basic_type_id = method->current_basic_type_id;
    SPVM_RUNTIME_BASIC_TYPE* current_basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, current_basic_type_id);
    
    int32_t method_return_type_is_object = SPVM_API_RUNTIME_is_object_type(runtime, method_return_basic_type_id, method_return_type_dimension, method_return_type_flag);
    int32_t no_need_call = 0;
    if (method->is_init) {
      int32_t* init_flags = (int32_t*)env->init_flags;
      int32_t basic_type_id = method->current_basic_type_id;
      int32_t init_flag = init_flags[basic_type_id];
      if (init_flag) {
        no_need_call = 1;
      }
      else {
        init_flags[basic_type_id]++;
      }
    }
    
    if (!no_need_call) {
      // Call native method
      if (method->is_native) {
        // Enter scope
        int32_t original_mortal_stack_top = SPVM_API_enter_scope(env, stack);
        
        // Set argument default values
        int32_t optional_args_length = method->args_length - method->required_args_length;
        if (optional_args_length > 0) {
          
          // Operation codes
          SPVM_OPCODE* opcodes = runtime->opcodes;
          
          // Operation code base
          int32_t method_opcodes_base_address_id = method->opcodes_base_address_id;
          
          // Execute operation codes
          int32_t opcode_rel_index = 0;
          while (1) {
            
            SPVM_OPCODE* opcode = &(opcodes[method_opcodes_base_address_id + opcode_rel_index]);
            
            if (opcode->id == SPVM_OPCODE_C_ID_END_ARGS) {
              break;
            }
            
            switch (opcode->id) {
              case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_BYTE: {
                int32_t stack_index = opcode->operand3 & 0xFF;
                if (stack_index >= args_stack_length) {
                  stack[stack_index].bval = (int8_t)(uint8_t)opcode->operand1;
                }
                break;
              }
              case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_SHORT: {
                int32_t stack_index = opcode->operand3 & 0xFF;
                if (stack_index >= args_stack_length) {
                  stack[stack_index].sval = (int16_t)(uint16_t)opcode->operand1;
                }
                break;
              }
              case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_INT: {
                int32_t stack_index = opcode->operand3 & 0xFF;
                if (stack_index >= args_stack_length) {
                  stack[stack_index].ival = (int32_t)opcode->operand1;
                }
                break;
              }
              case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_LONG: {
                int32_t stack_index = opcode->operand3 & 0xFF;
                if (stack_index >= args_stack_length) {
                  stack[stack_index].lval = *(int64_t*)&opcode->operand1;
                }
                break;
              }
              case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_FLOAT: {
                int32_t stack_index = opcode->operand3 & 0xFF;
                if (stack_index >= args_stack_length) {
                  SPVM_VALUE default_value;
                  default_value.ival = (int32_t)opcode->operand1;
                  stack[stack_index].fval = default_value.fval;
                }
                break;
              }
              case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_DOUBLE: {
                int32_t stack_index = opcode->operand3 & 0xFF;
                if (stack_index >= args_stack_length) {
                  stack[stack_index].dval = *(double*)&opcode->operand1;
                }
                break;
              }
              case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_OBJECT: {
                int32_t stack_index = opcode->operand3 & 0xFF;
                if (stack_index >= args_stack_length) {
                  stack[stack_index].oval = NULL;
                }
                break;
              }
            }
            
            opcode_rel_index++;
          }
        }
        
        // Call native subrotuine
        int32_t (*native_address)(SPVM_ENV*, SPVM_VALUE*) = runtime->method_native_addresses[current_basic_type->methods_base_address_id + method->index];
        assert(native_address != NULL);
        error = (*native_address)(env, stack);
        
        // Increment ref count of return value
        if (!error) {
          if (method_return_type_is_object) {
            if (*(void**)&stack[0] != NULL) {
              SPVM_IMPLEMENT_INC_REF_COUNT_ONLY(env, stack, *(void**)&stack[0]);
            }
          }
        }
        
        // Leave scope
        SPVM_API_leave_scope(env, stack, original_mortal_stack_top);
        
        // Decrement ref count of return value
        if (!error) {
          if (method_return_type_is_object) {
            if (*(void**)&stack[0] != NULL) {
              SPVM_IMPLEMENT_DEC_REF_COUNT_ONLY(env, stack, *(void**)&stack[0]);
            }
          }
        }
        
        // Set default exception message
        if (error && env->get_exception(env, stack) == NULL) {
          void* exception = env->new_string_nolen_raw(env, stack, "Error");
          env->set_exception(env, stack, exception);
        }
      }
      else {
        // Call precompiled method
        void* method_precompile_address = runtime->method_precompile_addresses[current_basic_type->methods_base_address_id + method->index];
        if (method_precompile_address) {
          int32_t (*precompile_address)(SPVM_ENV*, SPVM_VALUE*) = method_precompile_address;
          error = (*precompile_address)(env, stack);
        }
        // Call sub virtual machine
        else {
          error = SPVM_API_call_method_vm(env, stack, method, args_stack_length);
        }
      }
      
      if (mortal && method_return_type_is_object) {
        env->push_mortal(env, stack, stack[0].oval);
      }
    }
  }
  
  stack[STACK_INDEX_CALL_DEPTH].ival--;
  
  return error;
}

int32_t SPVM_API_is_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  int32_t is_array;
  if (object) {
    is_array = object->type_dimension > 0;
  }
  else {
    is_array = 0;
  }
  
  return is_array;
}

int32_t SPVM_API_is_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  int32_t is_string;
  if (object) {
    int32_t object_basci_type_id = SPVM_API_get_object_basic_type_id(env, stack, object);
    is_string = (object_basci_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && object->type_dimension == 0);
  }
  else {
    is_string = 0;
  }
  
  return is_string;
}

int32_t SPVM_API_is_numeric_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {

  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t is_numeric_array;
  if (object) {
    int32_t object_type_dimension = object->type_dimension;
    if (object_type_dimension == 0) {
      is_numeric_array = 0;
    }
    else if (object_type_dimension == 1) {
      int32_t object_basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, object);
      int32_t object_basic_type_category = SPVM_API_RUNTIME_get_basic_type_category(runtime, object_basic_type_id);
      switch (object_basic_type_category) {
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC:
        {
          is_numeric_array = 1;
          break;
        }
        default: {
          is_numeric_array = 0;
        }
      }
    }
    else if (object_type_dimension > 1) {
      is_numeric_array = 0;
    }
    else {
      assert(0);
    }
  }
  else {
    is_numeric_array = 0;
  }

  return is_numeric_array;
}


int32_t SPVM_API_is_object_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  SPVM_RUNTIME* runtime = env->runtime;

  int32_t is_object_array;
  if (object) {
    int32_t object_type_dimension = object->type_dimension;
    if (object_type_dimension == 0) {
      is_object_array = 0;
    }
    else if (object_type_dimension == 1) {
      int32_t object_basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, object);
      assert(object_basic_type_id >= 0);
      int32_t element_type_dimension = 0;
      int32_t type_flag = 0;
      is_object_array = SPVM_API_RUNTIME_is_object_type(env->runtime, object_basic_type_id, element_type_dimension, type_flag);
    }
    else if (object_type_dimension > 1) {
      is_object_array = 1;
    }
    else {
      assert(0);
    }
  }
  else {
    is_object_array = 0;
  }
  
  return is_object_array;
}

int32_t SPVM_API_is_mulnum_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {

  SPVM_RUNTIME* runtime = env->runtime;

  int32_t is_mulnum_array;
  if (object) {
    int32_t object_type_dimension = object->type_dimension;
    if (object_type_dimension == 0) {
      is_mulnum_array = 0;
    }
    else if (object_type_dimension == 1) {
      int32_t object_basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, object);
      int32_t object_basic_type_category = SPVM_API_RUNTIME_get_basic_type_category(runtime, object_basic_type_id);
      switch (object_basic_type_category) {
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
        {
          is_mulnum_array = 1;
          break;
        }
        default: {
          is_mulnum_array = 0;
        }
      }
    }
    else if (object_type_dimension > 1) {
      is_mulnum_array = 0;
    }
    else {
      assert(0);
    }
  }
  else {
    is_mulnum_array = 0;
  }

  return is_mulnum_array;
}

int32_t SPVM_API_is_class(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  SPVM_RUNTIME* runtime = env->runtime;

  int32_t is_class;
  if (object) {
    int32_t object_type_dimension = object->type_dimension;
    if (object_type_dimension == 0) {
      int32_t object_basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, object);
      int32_t object_basic_type_category = SPVM_API_RUNTIME_get_basic_type_category(runtime, object_basic_type_id);
      
      switch (object_basic_type_category) {
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS: {
          is_class = 1;
          break;
        }
        default: {
          is_class = 0;
        }
      }
    }
    else {
      is_class = 0;
    }
  }
  else {
    is_class = 0;
  }
  
  return is_class;
}

int32_t SPVM_API_is_pointer_class(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t is_pointer_class;
  if (object) {
    int32_t object_type_dimension = object->type_dimension;
    if (object_type_dimension == 0) {
      int32_t object_basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, object);
      int32_t object_basic_type_category = SPVM_API_RUNTIME_get_basic_type_category(runtime, object_basic_type_id);
      
      switch (object_basic_type_category) {
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS: {
          int32_t basic_type_is_pointer = SPVM_API_RUNTIME_get_basic_type_is_pointer(runtime, object_basic_type_id);
          
          if (basic_type_is_pointer) {
            is_pointer_class = 1;
          }
          else {
            is_pointer_class = 0;
          }
          break;
        }
        default: {
          is_pointer_class = 0;
        }
      }
    }
    else {
      is_pointer_class = 0;
    }
  }
  else {
    is_pointer_class = 0;
  }
  
  return is_pointer_class;
}

int32_t SPVM_API_get_elem_size(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t elem_size;
  if (array) {
    if (SPVM_API_is_string(env, stack, array)) {
      elem_size = 1;
    }
    else if (SPVM_API_is_object_array(env, stack, array)) {
      elem_size = sizeof(void*);
    }
    else if (SPVM_API_is_numeric_array(env, stack, array)) {

      int32_t basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, array);
      
      int32_t type_dimension = array->type_dimension;
      assert(type_dimension == 1);
      
      SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, basic_type_id);
      if (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
        elem_size = 1;
      }
      else if (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
        elem_size = 2;
      }
      else if (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT || basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
        elem_size = 4;
      }
      else if (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG || basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
        elem_size = 8;
      }
      else {
        assert(0);
      }
    }
    else if (SPVM_API_is_mulnum_array(env, stack, array)) {
      int32_t basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, array);
      int32_t type_dimension = array->type_dimension;
      assert(type_dimension == 1);
      
      SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, basic_type_id);
      
      int32_t fields_length = basic_type->fields_length;
      
      SPVM_RUNTIME_FIELD* first_field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, basic_type->fields_base_address_id + 0);
      
      int32_t field_basic_type_id = first_field->basic_type_id;
      
      if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
        elem_size = 1 * fields_length;
      }
      else if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
        elem_size = 2 * fields_length;
      }
      else if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT || field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
        elem_size = 4 * fields_length;
      }
      else if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG || field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
        elem_size = 8 * fields_length;
      }
      else {
        assert(0);
      }
    }
  }
  else {
    elem_size = 0;
  }
  
  return elem_size;
}

int32_t SPVM_API_enter_scope(SPVM_ENV* env, SPVM_VALUE* stack){
  (void)env;

  SPVM_OBJECT*** cur_mortal_stack_ptr = (SPVM_OBJECT***)&stack[STACK_INDEX_MORTAL_STACK];
  int32_t* cur_mortal_stack_top_ptr = (int32_t*)&stack[STACK_INDEX_MORTAL_STACK_TOP];
  int32_t* cur_mortal_stack_capacity_ptr = (int32_t*)&stack[STACK_INDEX_MORTAL_STACK_CAPACITY];
  
  int32_t mortal_stack_top = *cur_mortal_stack_top_ptr ;
  
  return mortal_stack_top;
}

int32_t SPVM_API_push_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;

  SPVM_OBJECT*** cur_mortal_stack_ptr = (SPVM_OBJECT***)&stack[STACK_INDEX_MORTAL_STACK];
  int32_t* cur_mortal_stack_top_ptr = (int32_t*)&stack[STACK_INDEX_MORTAL_STACK_TOP];
  int32_t* cur_mortal_stack_capacity_ptr = (int32_t*)&stack[STACK_INDEX_MORTAL_STACK_CAPACITY];

  if (object != NULL) {
    // Extend mortal stack
    if (*cur_mortal_stack_top_ptr >= *cur_mortal_stack_capacity_ptr) {
      int32_t new_mortal_stack_capacity = *cur_mortal_stack_capacity_ptr * 2;
      SPVM_OBJECT** new_mortal_stack = SPVM_API_new_memory_stack(env, stack, sizeof(void*) * new_mortal_stack_capacity);
      if (new_mortal_stack == NULL) {
        return 1;
      }
      memcpy(new_mortal_stack, *cur_mortal_stack_ptr, sizeof(void*) * *cur_mortal_stack_capacity_ptr);
      *cur_mortal_stack_capacity_ptr = new_mortal_stack_capacity;
      SPVM_API_free_memory_stack(env, stack, *cur_mortal_stack_ptr);
      *cur_mortal_stack_ptr = NULL;
      *cur_mortal_stack_ptr = new_mortal_stack;
    }
    
    (*cur_mortal_stack_ptr)[*cur_mortal_stack_top_ptr] = object;
    *cur_mortal_stack_top_ptr = *cur_mortal_stack_top_ptr + 1;
    
    object->ref_count++;
  }
  
  return 0;
}

SPVM_OBJECT* SPVM_API_get_type_name_raw(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  assert(object);
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  const char* basic_type_name = SPVM_API_get_object_basic_type_name(env, stack, object);
  int32_t type_dimension = object->type_dimension;
  
  int32_t length = 0;
  
  // Basic type
  length += strlen(basic_type_name);
  
  //[]
  length += type_dimension * 2;
  
  void* obj_type_name = env->new_string_raw(env, stack, NULL, length);
  
  char* type_name = (char*)env->get_chars(env, stack, obj_type_name);
  
  int32_t type_name_index = 0;
  sprintf((char*)type_name, "%s", basic_type_name);
  type_name_index += strlen(basic_type_name);
  
  int32_t dim_index;
  for (dim_index = 0; dim_index < type_dimension; dim_index++) {
    sprintf((char*)(type_name + type_name_index), "[]");
    type_name_index += 2;
  }
  
  return obj_type_name;
}

SPVM_OBJECT* SPVM_API_get_type_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  SPVM_OBJECT* obj_type_name = SPVM_API_get_type_name_raw(env, stack, object);
  
  SPVM_API_push_mortal(env, stack, obj_type_name);
  
  return obj_type_name;
}

int32_t SPVM_API_get_compile_type_name_length(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t type_dimension, int32_t type_flag) {
  
  int32_t compile_type_name_length = 0;
  
  // mutable
  if (type_flag & SPVM_NATIVE_C_TYPE_FLAG_MUTABLE) {
    compile_type_name_length += strlen("mutable ");
  }
  
  // Basic type
  compile_type_name_length += strlen(basic_type_name);
  
  // []
  compile_type_name_length += type_dimension * 2;
  
  // *
  if (type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF) {
    compile_type_name_length += 1;
  }
  
  return compile_type_name_length;
}

SPVM_OBJECT* SPVM_API_get_compile_type_name_raw(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t type_dimension, int32_t type_flag) {
  
  int32_t compile_type_name_length = SPVM_API_get_compile_type_name_length(env, stack, basic_type_name, type_dimension, type_flag);
  
  void* obj_compile_type_name = env->new_string_raw(env, stack, NULL, compile_type_name_length);
  
  char* compile_type_name = (char*)env->get_chars(env, stack, obj_compile_type_name);
  
  if (type_flag & SPVM_NATIVE_C_TYPE_FLAG_MUTABLE) {
    sprintf(compile_type_name, "mutable ");
    compile_type_name += strlen("mutable ");
  }
  
  sprintf(compile_type_name, "%s", basic_type_name);
  compile_type_name += strlen(basic_type_name);
  
  for (int32_t type_dimension_index = 0; type_dimension_index < type_dimension; type_dimension_index++) {
    sprintf(compile_type_name, "[]");
    compile_type_name += 2;
  }
  
  // Reference
  if (type_flag & SPVM_NATIVE_C_TYPE_FLAG_REF) {
    sprintf(compile_type_name, "*");
    compile_type_name += 1;
  }
  
  *compile_type_name = '\0';
  compile_type_name++;
  
  return obj_compile_type_name;
}

SPVM_OBJECT* SPVM_API_get_compile_type_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t type_dimension, int32_t type_flag) {
  
  SPVM_OBJECT* obj_compile_type_name = SPVM_API_get_compile_type_name_raw(env, stack, basic_type_name, type_dimension, type_flag);
  
  SPVM_API_push_mortal(env, stack, obj_compile_type_name);
  
  return obj_compile_type_name;
}

void SPVM_API_leave_scope(SPVM_ENV* env, SPVM_VALUE* stack, int32_t original_mortal_stack_top) {
  (void)env;

  SPVM_OBJECT*** cur_mortal_stack_ptr = (SPVM_OBJECT***)&stack[STACK_INDEX_MORTAL_STACK];
  int32_t* cur_mortal_stack_top_ptr = (int32_t*)&stack[STACK_INDEX_MORTAL_STACK_TOP];
  int32_t* cur_mortal_stack_capacity_ptr = (int32_t*)&stack[STACK_INDEX_MORTAL_STACK_CAPACITY];

  int32_t mortal_stack_index;
  for (mortal_stack_index = original_mortal_stack_top; mortal_stack_index < *cur_mortal_stack_top_ptr; mortal_stack_index++) {
    SPVM_OBJECT* object = (*cur_mortal_stack_ptr)[mortal_stack_index];
    
    if (object != NULL) {
      if (object->ref_count > 1) {
        object->ref_count--;
      }
      else {
        SPVM_API_dec_ref_count(env, stack, object);
      }
    }
    
    (*cur_mortal_stack_ptr)[mortal_stack_index] = NULL;
  }
  
  *cur_mortal_stack_top_ptr = original_mortal_stack_top;
}

SPVM_OBJECT* SPVM_API_new_stack_trace_raw(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* exception, SPVM_RUNTIME_METHOD* method, int32_t line) {

  if (stack[STACK_INDEX_CALL_DEPTH].ival > 100) {
    return exception;
  }

  SPVM_RUNTIME* runtime = env->runtime;

  const char* method_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, method->name_id, NULL);
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, method->current_basic_type_id);
  const char* basic_type_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, basic_type->name_id, NULL);

  int32_t include_dir_id = basic_type->module_dir_id;
  int32_t module_rel_file_id = basic_type->module_rel_file_id;
  
  const char* include_dir;
  const char* include_dir_sep;
  if (include_dir_id >= 0) {
    include_dir = SPVM_API_RUNTIME_get_name(runtime, include_dir_id);
    include_dir_sep = "/";
  }
  else {
    include_dir = "";
    include_dir_sep = "";
  }
  
  const char* module_rel_file = SPVM_API_RUNTIME_get_name(runtime, module_rel_file_id);
  
  // Basic type name and method name
  const char* new_line_part = "\n  ";
  const char* arrow_part = "->";
  const char* at_part = " at ";

  // Exception
  const char* exception_bytes = env->get_chars(env, stack, exception);
  int32_t exception_length = env->length(env, stack, exception);
  
  // Total string length
  int32_t total_length = 0;
  total_length += exception_length;
  total_length += strlen(new_line_part);
  total_length += strlen(basic_type_name);
  total_length += strlen(arrow_part);
  total_length += strlen(method_name);
  total_length += strlen(at_part);
  total_length += strlen(include_dir);
  total_length += strlen(include_dir_sep);
  total_length += strlen(module_rel_file);

  const char* line_part = " line ";
  char line_str[20];
  
  sprintf(line_str, "%" PRId32, line);
  total_length += strlen(line_part);
  total_length += strlen(line_str);
  
  // Create exception message
  void* new_exception = env->new_string_raw(env, stack, NULL, total_length);
  const char* new_exception_bytes = env->get_chars(env, stack, new_exception);
  
  memcpy(
    (void*)(new_exception_bytes),
    (void*)(exception_bytes),
    exception_length
  );

  sprintf(
    (char*)new_exception_bytes + exception_length,
    "%s%s%s%s%s%s%s%s%s%" PRId32,
    new_line_part,
    basic_type_name,
    arrow_part,
    method_name,
    at_part,
    include_dir,
    include_dir_sep,
    module_rel_file,
    line_part,
    line
  );
  
  return new_exception;
}

SPVM_OBJECT* SPVM_API_new_stack_trace(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* exception, SPVM_RUNTIME_METHOD* method, int32_t line) {
  (void)env;
  
  SPVM_OBJECT* stack_trace = SPVM_API_new_stack_trace_raw(env, stack, exception, method, line);
  
  SPVM_API_push_mortal(env, stack, stack_trace);
  
  return stack_trace;
}

SPVM_OBJECT* SPVM_API_new_stack_trace_raw_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* exception, const char* basic_type_name, const char* method_name, int32_t line) {

  if (stack[STACK_INDEX_CALL_DEPTH].ival > 100) {
    return exception;
  }

  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t basic_type_id = SPVM_API_RUNTIME_get_basic_type_id_by_name(runtime, basic_type_name);
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, basic_type_id);

  int32_t include_dir_id = basic_type->module_dir_id;
  int32_t module_rel_file_id = basic_type->module_rel_file_id;
  
  const char* include_dir;
  const char* include_dir_sep;
  if (include_dir_id >= 0) {
    include_dir = SPVM_API_RUNTIME_get_name(runtime, include_dir_id);
    include_dir_sep = "/";
  }
  else {
    include_dir = "";
    include_dir_sep = "";
  }
  
  const char* module_rel_file = SPVM_API_RUNTIME_get_name(runtime, module_rel_file_id);
  
  // Basic type name and method name
  const char* new_line_part = "\n  ";
  const char* arrow_part = "->";
  const char* at_part = " at ";

  // Exception
  const char* exception_bytes = env->get_chars(env, stack, exception);
  int32_t exception_length = env->length(env, stack, exception);
  
  // Total string length
  int32_t total_length = 0;
  total_length += exception_length;
  total_length += strlen(new_line_part);
  total_length += strlen(basic_type_name);
  total_length += strlen(arrow_part);
  total_length += strlen(method_name);
  total_length += strlen(at_part);
  total_length += strlen(include_dir);
  total_length += strlen(include_dir_sep);
  total_length += strlen(module_rel_file);

  const char* line_part = " line ";
  char line_str[20];
  
  sprintf(line_str, "%" PRId32, line);
  total_length += strlen(line_part);
  total_length += strlen(line_str);
  
  // Create exception message
  void* new_exception = env->new_string_raw(env, stack, NULL, total_length);
  const char* new_exception_bytes = env->get_chars(env, stack, new_exception);
  
  memcpy(
    (void*)(new_exception_bytes),
    (void*)(exception_bytes),
    exception_length
  );

  sprintf(
    (char*)new_exception_bytes + exception_length,
    "%s%s%s%s%s%s%s%s%s%" PRId32,
    new_line_part,
    basic_type_name,
    arrow_part,
    method_name,
    at_part,
    include_dir,
    include_dir_sep,
    module_rel_file,
    line_part,
    line
  );
  
  return new_exception;
}

void SPVM_API_fprint(SPVM_ENV* env, SPVM_VALUE* stack, FILE* fh, SPVM_OBJECT* string) {
  (void)env;
  
  if (string == NULL) {
    return;
  }
  
  const char* bytes = env->get_chars(env, stack, string);
  int32_t string_length = env->length(env, stack, string);
  
  {
    int32_t i;
    for (i = 0; i < string_length; i++) {
      putc((char)bytes[i], fh);
    }
  }
}

void SPVM_API_print(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string) {
  (void)env;
  
  SPVM_API_fprint(env, stack, stdout, string);
}

void SPVM_API_print_stderr(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string) {
  (void)env;
  
  SPVM_API_fprint(env, stack, stderr, string);
}

SPVM_OBJECT* SPVM_API_concat_raw(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string1, SPVM_OBJECT* string2) {
  
  int32_t string1_length = SPVM_API_length(env, stack, string1);
  int32_t string2_length = SPVM_API_length(env, stack, string2);
  
  int32_t string3_length = string1_length + string2_length;
  SPVM_OBJECT* string3 = SPVM_API_new_string_raw(env, stack, NULL, string3_length);
  
  const char* string1_bytes = SPVM_API_get_chars(env, stack, string1);
  const char* string2_bytes = SPVM_API_get_chars(env, stack, string2);
  char* string3_bytes = (char*)SPVM_API_get_chars(env, stack, string3);
  
  if (string1_length > 0) {
    memcpy(string3_bytes, string1_bytes, string1_length);
  }
  if (string2_length) {
    memcpy(string3_bytes + string1_length, string2_bytes, string2_length);
  }
  
  return string3;
}

SPVM_OBJECT* SPVM_API_concat(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string1, SPVM_OBJECT* string2) {
  (void)env;
  
  SPVM_OBJECT* str = SPVM_API_concat_raw(env, stack, string1, string2);
  
  SPVM_API_push_mortal(env, stack, str);
  
  return str;
}

void SPVM_API_free_weaken_back_refs(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_WEAKEN_BACKREF* weaken_backref_head) {
  (void)env;
  
  SPVM_WEAKEN_BACKREF* weaken_backref_head_cur = weaken_backref_head;
  SPVM_WEAKEN_BACKREF* weaken_backref_head_next = NULL;
  while (weaken_backref_head_cur != NULL){
    *(weaken_backref_head_cur->object_address) = NULL;
    weaken_backref_head_next = weaken_backref_head_cur->next;
    SPVM_API_free_memory_stack(env, stack, weaken_backref_head_cur);
    weaken_backref_head_cur = NULL;
    weaken_backref_head_cur = weaken_backref_head_next;
  }
}

int32_t SPVM_API_isweak(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** object_address) {
  (void)env;
  
  int32_t isweak = (intptr_t)*object_address & 1;
  
  return isweak;
}

int32_t SPVM_API_weaken(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** object_address) {
  (void)env;
  
  assert(object_address);

  if (*object_address == NULL) {
    return 0;
  }
  
  if (SPVM_API_isweak(env, stack, object_address)) {
    return 0;
  }
  
  SPVM_OBJECT* object = *object_address;
  
  // Decrelement reference count
  if (object->ref_count == 1) {
    // If reference count is 1, the object is freeed without weaken
    SPVM_API_dec_ref_count(env, stack, *object_address);
    *object_address = NULL;
    return 0;
  }
  else {
    object->ref_count--;
  }

  // Create weaken_backref_head
  if (object->weaken_backref_head == NULL) {
    SPVM_WEAKEN_BACKREF* new_weaken_backref = SPVM_API_new_memory_stack(env, stack, sizeof(SPVM_WEAKEN_BACKREF));
    if (new_weaken_backref == NULL) {
      return 1;
    }
    new_weaken_backref->object_address = object_address;
    object->weaken_backref_head = new_weaken_backref;
  }
  // Add weaken_back_ref
  else {
    SPVM_WEAKEN_BACKREF* weaken_backref_next = object->weaken_backref_head;

    SPVM_WEAKEN_BACKREF* new_weaken_backref = SPVM_API_new_memory_stack(env, stack, sizeof(SPVM_WEAKEN_BACKREF));
    if (new_weaken_backref) {
      return 1;
    }
    new_weaken_backref->object_address = object_address;
    
    while (weaken_backref_next->next != NULL){
      weaken_backref_next = weaken_backref_next->next;
    }
    weaken_backref_next->next = new_weaken_backref;
  }
  
  // Weaken is implemented by tag pointer.
  // If pointer most right bit is 1, object is weaken.
  *object_address = (SPVM_OBJECT*)((intptr_t)*object_address | 1);
  
  return 0;
}

void SPVM_API_unweaken(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** object_address) {
  (void)env;

  assert(object_address);
  
  if (*object_address == NULL) {
    return;
  }
  
  if (!SPVM_API_isweak(env, stack, object_address)) {
    return;
  }
  
  // Unweaken
  *object_address = (SPVM_OBJECT*)((intptr_t)*object_address & ~(intptr_t)1);
  
  SPVM_OBJECT* object = *object_address;
  
  // Increment reference count
  object->ref_count++;

  // Remove weaken back ref
  SPVM_WEAKEN_BACKREF** weaken_backref_next_address = &object->weaken_backref_head;
  assert(*weaken_backref_next_address);
  
  int32_t pass_one = 0;
  while (*weaken_backref_next_address != NULL){
    if ((*weaken_backref_next_address)->object_address == object_address) {
      pass_one++;
      SPVM_WEAKEN_BACKREF* tmp = (*weaken_backref_next_address)->next;
      SPVM_API_free_memory_stack(env, stack, *weaken_backref_next_address);
      *weaken_backref_next_address = NULL;
      *weaken_backref_next_address = tmp;
      break;
    }
    *weaken_backref_next_address = (*weaken_backref_next_address)->next;
  }
  assert(pass_one == 1);
}

int32_t SPVM_API_set_exception(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* exception) {
  
  SPVM_OBJECT** cur_excetpion_ptr = (SPVM_OBJECT**)&stack[STACK_INDEX_EXCEPTION];
  
  if (*cur_excetpion_ptr != NULL) {
    SPVM_API_dec_ref_count(env, stack, *cur_excetpion_ptr);
  }
  
  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, (void**)cur_excetpion_ptr, exception);
  
  if (*cur_excetpion_ptr != NULL) {
    (*cur_excetpion_ptr)->ref_count++;
  }
  
  return 1;
}

SPVM_OBJECT* SPVM_API_exception(SPVM_ENV* env, SPVM_VALUE* stack){
  (void)env;

  SPVM_OBJECT** cur_excetpion_ptr = (SPVM_OBJECT**)&stack[STACK_INDEX_EXCEPTION];
  SPVM_OBJECT* cur_excetpion = *cur_excetpion_ptr;
  
  return cur_excetpion;
}

SPVM_OBJECT* SPVM_API_new_byte_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_new_byte_array_raw(env, stack, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_short_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_new_short_array_raw(env, stack, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_int_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_new_int_array_raw(env, stack, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_long_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_new_long_array_raw(env, stack, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_float_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_new_float_array_raw(env, stack, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_double_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_new_double_array_raw(env, stack, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_string_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_new_object_array(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING, length);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_object(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_new_object_raw(env, stack, basic_type_id);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_pointer_object(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, void* pointer) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_new_pointer_object_raw(env, stack, basic_type_id, pointer);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_string_nolen_raw(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes) {
  (void)env;
  
  int32_t length = strlen((char*)bytes);
  
  SPVM_OBJECT* object = SPVM_API_new_string_raw(env, stack, NULL, length);
  
  if (bytes != NULL && length > 0) {
    memcpy((void*)((intptr_t)object + env->object_header_size), (char*)bytes, length);
  }
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_string_nolen(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_new_string_nolen_raw(env, stack, bytes);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_string_raw(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length) {
  (void)env;
  
  if (length < 0) {
    return NULL;
  }
  
  size_t alloc_size = (size_t)env->object_header_size + sizeof(char) * (length + 1);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING, 0, length, 0);
  
  if (object) {
    if (bytes != NULL && length > 0) {
      memcpy((void*)((intptr_t)object + env->object_header_size), (char*)bytes, length);
    }
  }
  
  return object;
}

int32_t SPVM_API_get_field_first_int(SPVM_ENV* env, SPVM_OBJECT* object) {

  int32_t value = *(int32_t*)((intptr_t)object + env->object_header_size);
  
  return value;
}

int32_t SPVM_API_get_bool_object_value(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* bool_object) {
  (void)env;

  int32_t value = SPVM_API_get_field_first_int(env, bool_object);
  
  return value;
}

SPVM_OBJECT* SPVM_API_new_string(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_new_string_raw(env, stack, bytes, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_byte_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  (void)env;
  
  // If lenght is less than 0, return NULL.
  if (length < 0) {
    return NULL;
  }
  
  size_t alloc_size = (size_t)env->object_header_size + sizeof(int8_t) * (length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE, 1, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_short_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  size_t alloc_size = (size_t)env->object_header_size + sizeof(int16_t) * (length + 1);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT, 1, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_int_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  size_t alloc_size = (size_t)env->object_header_size + sizeof(int32_t) * (length + 1);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, SPVM_NATIVE_C_BASIC_TYPE_ID_INT, 1, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_long_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  if (length < 0) {
    return NULL;
  }
  
  size_t alloc_size = (size_t)env->object_header_size + sizeof(int64_t) * (length + 1);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, SPVM_NATIVE_C_BASIC_TYPE_ID_LONG, 1, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_float_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  size_t alloc_size = (size_t)env->object_header_size + sizeof(float) * (length + 1);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT, 1, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_double_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  
  size_t alloc_size = (size_t)env->object_header_size + sizeof(double) * (length + 1);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE, 1, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_object_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_OBJECT object_for_type_check;
  object_for_type_check.basic_type_id = basic_type_id;
  object_for_type_check.type_dimension = 1;
  
  int32_t is_object_array = SPVM_API_is_object_array(env, stack, &object_for_type_check);
  
  if (!is_object_array) {
    return NULL;
  }
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, basic_type_id);
  
  if (!basic_type) {
    return NULL;
  }
  
  size_t alloc_size = (size_t)env->object_header_size + sizeof(void*) * (length + 1);
  
  const char* basic_type_name = env->api->runtime->get_name(env->runtime, basic_type->name_id);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, basic_type_id, 1, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_object_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length) {
  
  SPVM_OBJECT* object = SPVM_API_new_object_array_raw(env, stack, basic_type_id, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_muldim_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t type_dimension, int32_t length) {
  
  if (type_dimension < 2) {
    return NULL;
  }
  else if (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT) {
    return NULL;
  }
  
  size_t alloc_size = (size_t)env->object_header_size + sizeof(void*) * (length + 1);
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, basic_type_id);
  if (!basic_type) {
    return NULL;
  }
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, basic_type_id, type_dimension, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_muldim_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t type_dimension, int32_t length) {
  
  SPVM_OBJECT* object = SPVM_API_new_muldim_array_raw(env, stack, basic_type_id, type_dimension, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_mulnum_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  // valut_t array dimension must be 1
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, basic_type_id);
  const char* basic_type_name = SPVM_API_RUNTIME_get_basic_type_name(runtime, basic_type_id);
  
  int32_t fields_length = basic_type->fields_length;
  SPVM_RUNTIME_FIELD* field_first = SPVM_API_RUNTIME_get_field_by_address_id(runtime, basic_type->fields_base_address_id + 0);
  
  int32_t field_basic_type_id = field_first->basic_type_id;
  
  int32_t unit_size;
  if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
    unit_size = sizeof(int8_t);
  }
  else if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
    unit_size = sizeof(int16_t);
  }
  else if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
    unit_size = sizeof(int32_t);
  }
  else if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
    unit_size = sizeof(int64_t);
  }
  else if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
    unit_size = sizeof(float);
  }
  else if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
    unit_size = sizeof(double);
  }
  else {
    assert(0);
  }
  
  size_t alloc_size = (size_t)env->object_header_size + unit_size * fields_length * (length + 1);
  
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, basic_type_id, 1, length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_mulnum_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length) {
  
  SPVM_OBJECT* object = SPVM_API_new_mulnum_array_raw(env, stack, basic_type_id, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_object_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, basic_type_id);
  
  if (!basic_type) {
    return NULL;
  }
  
  if (basic_type->category != SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS) {
    return NULL;
  }
  
  // Alloc body length + 1
  int32_t fields_length = basic_type->fields_length;
  
  size_t alloc_size = (size_t)env->object_header_size + basic_type->fields_size + 1;
  
  if (!basic_type) {
    return NULL;
  }
  SPVM_OBJECT* object = SPVM_API_new_object_common(env, stack, alloc_size, basic_type_id, 0, fields_length, 0);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_pointer_object_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, void* pointer) {
  (void)env;
  
  void* obj_object = SPVM_API_new_object_raw(env, stack, basic_type_id);
  
  env->set_pointer(env, stack, obj_object, pointer);
  
  return obj_object;
}

int32_t SPVM_API_get_object_basic_type_id(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  return object->basic_type_id;
}

const char* SPVM_API_get_object_basic_type_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  int32_t basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, object);
  int32_t basic_type_name_id = env->api->runtime->get_basic_type_name_id(env->runtime, basic_type_id);
  const char* basic_type_name = env->api->runtime->get_name(env->runtime, basic_type_name_id);
  
  assert(basic_type_name);
  
  return basic_type_name;
}

int32_t SPVM_API_get_object_type_dimension(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  return object->type_dimension;
}

int32_t SPVM_API_length(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  int32_t length = object->length;
  
  return length;
}

int8_t* SPVM_API_get_elems_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;

  return (int8_t*)((intptr_t)object + env->object_header_size);
}

const char* SPVM_API_get_chars(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string) {
  (void)env;

  return (const char*)((intptr_t)string + env->object_header_size);
}

int16_t* SPVM_API_get_elems_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  return (int16_t*)((intptr_t)object + env->object_header_size);
}

int32_t* SPVM_API_get_elems_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  return (int32_t*)((intptr_t)object + env->object_header_size);
}

int64_t* SPVM_API_get_elems_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  return (int64_t*)((intptr_t)object + env->object_header_size);
}

float* SPVM_API_get_elems_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  return (float*)((intptr_t)object + env->object_header_size);
}

double* SPVM_API_get_elems_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  return (double*)((intptr_t)object + env->object_header_size);
}

SPVM_OBJECT* SPVM_API_get_elem_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t index) {
  (void)env;
  
  SPVM_OBJECT* object_maybe_weaken = ((SPVM_OBJECT**)((intptr_t)array + env->object_header_size))[index];
  SPVM_OBJECT* object = SPVM_IMPLEMENT_GET_OBJECT_NO_WEAKEN_ADDRESS(env, stack, object_maybe_weaken);
  
  return object;
}

void SPVM_API_set_elem_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t index, SPVM_OBJECT* object) {
  (void)env;
  
  void* object_address = &((void**)((intptr_t)array + env->object_header_size))[index];
  
  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, object_address, object);
}

SPVM_OBJECT* SPVM_API_get_elem_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t index) {
  (void)env;
  
  return SPVM_API_get_elem_object(env, stack, array, index);
}

void SPVM_API_set_elem_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t index, SPVM_OBJECT* string) {
  (void)env;
  
  SPVM_API_set_elem_object(env, stack, array, index, string);
}

void* SPVM_API_get_pointer(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  return object->pointer;
}

void SPVM_API_set_pointer(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, void* pointer) {
  (void)env;
  
  object->pointer = pointer;
}

void SPVM_API_dec_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  SPVM_RUNTIME* runtime = env->runtime;

  assert(object != NULL);
  assert(object->ref_count > 0);
  
  // Not weakened
  assert((((intptr_t)object) & 1) == 0);
  
  // If reference count is zero, free address.
  if (object->ref_count == 1) {
    // Free object array
    if (SPVM_API_is_object_array(env, stack, object)) {
      int32_t length = object->length;
      for (int32_t index = 0; index < length; index++) {
        SPVM_OBJECT** get_field_object_address = &(((SPVM_OBJECT**)((intptr_t)object + env->object_header_size))[index]);

        if (*get_field_object_address != NULL) {
          SPVM_API_dec_ref_count(env, stack, *get_field_object_address);
        }
      }
    }
    // Free object
    else {
      int32_t object_basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, object);
      int32_t object_basic_type_category = SPVM_API_RUNTIME_get_basic_type_category(runtime, object_basic_type_id);
      if (object_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS) {
        // Class
        SPVM_RUNTIME* runtime = env->runtime;
        SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, object_basic_type_id);
        
        // Call destructor
        if (basic_type->destructor_method_index >= 0) {
          int32_t args_stack_length = 1;
          SPVM_VALUE save_stack0 = stack[0];
          void* save_exception = env->get_exception(env, stack);
          if (save_exception) {
            env->inc_ref_count(env, stack, save_exception);
          }
          
          stack[0].oval = object;
          SPVM_RUNTIME_METHOD* destructor_method = SPVM_API_RUNTIME_get_method(env->runtime, object_basic_type_id, basic_type->destructor_method_index);
          
          int32_t error = SPVM_API_call_method_raw(env, stack, destructor_method, args_stack_length);
          
          // Exception in destructor is changed to warning
          if (error) {
            void* exception = env->get_exception(env, stack);
            const char* exception_chars = env->get_chars(env, stack, exception);
            fprintf(stderr, "[The following exception is coverted to a warning because it is thrown in the DESTROY method]\n%s\n", exception_chars);
          }
          
          // Restore stack and excetpion
          stack[0] = save_stack0;
          env->set_exception(env, stack, save_exception);
          if (save_exception) {
            env->dec_ref_count(env, stack, save_exception);
          }
          
          assert(object->ref_count > 0);
        }
        
        // Free object fields
        int32_t object_fields_base_address_id = SPVM_API_RUNTIME_get_basic_type_fields_base_address_id(runtime, object_basic_type_id);
        int32_t object_fields_length = SPVM_API_RUNTIME_get_basic_type_fields_length(runtime, object_basic_type_id);
        for (int32_t field_index = 0; field_index < object_fields_length; field_index++) {
          SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, object_basic_type_id, field_index);
          
          int32_t field_basic_type_id = field->basic_type_id;
          int32_t field_type_dimension = field->type_dimension;
          int32_t field_type_flag = field->type_flag;
          int32_t field_type_is_object = SPVM_API_RUNTIME_is_object_type(runtime, field_basic_type_id, field_type_dimension, field_type_flag);
          
          if (field_type_is_object) {
            SPVM_OBJECT** get_field_object_address = (SPVM_OBJECT**)((intptr_t)object + (size_t)env->object_header_size + field->offset);
            if (*get_field_object_address != NULL) {
              // If object is weak, unweaken
              if (SPVM_API_isweak(env, stack, get_field_object_address)) {
                SPVM_API_unweaken(env, stack, get_field_object_address);
              }
              
              SPVM_API_dec_ref_count(env, stack, *get_field_object_address);
            }
          }
        }
      }
    }
    
    // Free weak back refenreces
    if (object->weaken_backref_head != NULL) {
      SPVM_API_free_weaken_back_refs(env, stack, object->weaken_backref_head);
      object->weaken_backref_head = NULL;
    }
    
    // Decrement reference count
    object->ref_count--;
  
    // Free object
    SPVM_API_free_memory_stack(env, stack, object);
    object = NULL;
  }
  else {
    // Decrement reference count
    object->ref_count--;
  }
}

void SPVM_API_inc_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  if (object != NULL) {
    assert(object->ref_count >= 0);
    // Increment reference count
    object->ref_count++;
  }
}

int32_t SPVM_API_get_basic_type_id(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name) {
  (void)env;

  SPVM_RUNTIME* runtime = env->runtime;

  if (basic_type_name == NULL) {
    return -1;
  }

  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type_by_name(runtime, basic_type_name);
  if (basic_type) {
    int32_t basic_type_id = basic_type->id;
    return basic_type_id;
  }
  else {
    return -1;
  }
}

int32_t SPVM_API_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  return object->ref_count;
}

SPVM_RUNTIME_FIELD* SPVM_API_get_field(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name) {
  
  SPVM_RUNTIME_FIELD* field = NULL;
  
  // Compiler
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (!object) {
    return NULL;
  }
  
  // Basic type
  int32_t object_basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, object);
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, object_basic_type_id);

  // Type dimension
  if (object->type_dimension != 0) {
    return NULL;
  }

  SPVM_RUNTIME_BASIC_TYPE* parent_basic_type = object_basic_type;
  
  while (1) {
    if (!parent_basic_type) {
      break;
    }
    
    // Method
    field = SPVM_API_RUNTIME_get_field_by_name(runtime, object_basic_type->id, field_name);
    if (field) {
      break;
    }
    
    if (parent_basic_type->parent_id != -1) {
      parent_basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, parent_basic_type->parent_id);
    }
    else {
      parent_basic_type = NULL;
    }
  }
  
  return field;
}

SPVM_RUNTIME_FIELD* SPVM_API_get_field_static(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, const char* field_name) {
  
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_name(env->runtime, basic_type_id, field_name);
  
  return field;
}

SPVM_RUNTIME_CLASS_VAR* SPVM_API_get_class_var(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, const char* class_var_name) {
  
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_name(env->runtime, basic_type_id, class_var_name);
  
  return class_var;
}

SPVM_RUNTIME_METHOD* SPVM_API_get_method(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, const char* method_name) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method_by_name(env->runtime, basic_type_id, method_name);
  
  return method;
}

SPVM_RUNTIME_METHOD* SPVM_API_get_class_method(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, const char* method_name) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method_by_name(env->runtime, basic_type_id, method_name);
  
  if (method) {
    int32_t is_class_method = SPVM_API_RUNTIME_get_method_is_class_method(env->runtime, method);
    if (!is_class_method) {
      return NULL;
    }
  }
  
  return method;
}

SPVM_RUNTIME_METHOD* SPVM_API_get_instance_method_static(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, const char* method_name) {
  
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method_by_name(env->runtime, basic_type_id, method_name);
  
  if (method) {
    int32_t is_class_method = SPVM_API_RUNTIME_get_method_is_class_method(env->runtime, method);
    if (is_class_method) {
      return NULL;
    }
  }
  
  return method;
}

SPVM_RUNTIME_METHOD* SPVM_API_get_instance_method(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* method_name) {
  
  // Method
  SPVM_RUNTIME_METHOD* method = NULL;
  
  // Compiler
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (!object) {
    return NULL;
  }
  
  // Basic type
  int32_t object_basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, object);
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, object_basic_type_id);
  
  SPVM_RUNTIME_BASIC_TYPE* parent_basic_type = object_basic_type;
  
  while (1) {
    if (!parent_basic_type) {
      break;
    }
    
    // Method
    method = SPVM_API_RUNTIME_get_method_by_name(runtime, parent_basic_type->id, method_name);
    if (method) {
      // Instance method
      if (method->is_class_method) {
        method = NULL;
      }
      break;
    }
    
    if (parent_basic_type->parent_id != -1) {
      parent_basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, parent_basic_type->parent_id);
    }
    else {
      parent_basic_type = NULL;
    }
  }
  
  return method;
}

int8_t SPVM_API_get_field_byte_v2(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {

  // Get field value
  int8_t value = *(int8_t*)((intptr_t)object + env->object_header_size + field->offset);

  return value;
}

int16_t SPVM_API_get_field_short_v2(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {

  // Get field value
  int16_t value = *(int16_t*)((intptr_t)object + env->object_header_size + field->offset);
  
  return value;
}

int32_t SPVM_API_get_field_int_v2(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {

  // Get field value
  int32_t value = *(int32_t*)((intptr_t)object + env->object_header_size + field->offset);
  
  return value;
}

int64_t SPVM_API_get_field_long_v2(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {

  // Get field value
  int64_t value = *(int64_t*)((intptr_t)object + env->object_header_size + field->offset);
  
  return value;
}

float SPVM_API_get_field_float_v2(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {

  // Get field value
  float value = *(float*)((intptr_t)object + env->object_header_size + field->offset);
  
  return value;
}

double SPVM_API_get_field_double_v2(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {

  // Get field value
  double value = *(double*)((intptr_t)object + env->object_header_size + field->offset);
  
  return value;
}

SPVM_OBJECT* SPVM_API_get_field_object_v2(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field) {

  // Get field value
  SPVM_OBJECT* value_maybe_weaken = *(SPVM_OBJECT**)((intptr_t)object + env->object_header_size + field->offset);
  SPVM_OBJECT* value = SPVM_IMPLEMENT_GET_OBJECT_NO_WEAKEN_ADDRESS(env, stack, value_maybe_weaken);
  
  return value;
}

void SPVM_API_set_field_byte_v2(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, int8_t value) {

  // Get field value
  *(int8_t*)((intptr_t)object + env->object_header_size + field->offset) = value;
}

void SPVM_API_set_field_short_v2(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, int16_t value) {

  // Get field value
  *(int16_t*)((intptr_t)object + env->object_header_size + field->offset) = value;
}

void SPVM_API_set_field_int_v2(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, int32_t value) {

  // Get field value
  *(int32_t*)((intptr_t)object + env->object_header_size + field->offset) = value;
}

void SPVM_API_set_field_long_v2(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, int64_t value) {

  // Get field value
  *(int64_t*)((intptr_t)object + env->object_header_size + field->offset) = value;
}

void SPVM_API_set_field_float_v2(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, float value) {

  // Get field value
  *(float*)((intptr_t)object + env->object_header_size + field->offset) = value;
}

void SPVM_API_set_field_double_v2(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, double value) {

  // Get field value
  *(double*)((intptr_t)object + env->object_header_size + field->offset) = value;
}

void SPVM_API_set_field_object_v2(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, SPVM_OBJECT* value) {

  // Get field value
  void* get_field_object_address = (void**)((intptr_t)object + env->object_header_size + field->offset);

  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, get_field_object_address, value);
}

void* SPVM_API_new_memory_env(SPVM_ENV* env, size_t size) {

  assert(size > 0);

  if ((uint64_t)size > (uint64_t)SIZE_MAX) {
    return NULL;
  }
  
  void* block = SPVM_ALLOCATOR_alloc_memory_block_tmp(env->allocator, (size_t)size);
  
#ifdef SPVM_DEBUG_MEMORY
    SPVM_ALLOCATOR* allocator = env->allocator;
    assert(allocator->memory_blocks_count_permanent == 0);
    fprintf(stderr, "[new_memory_env %p (Env:%d)]\n", block, allocator->memory_blocks_count_tmp);
#endif

  return block;
}

void SPVM_API_free_memory_env(SPVM_ENV* env, void* block) {

  if (block) {
    SPVM_ALLOCATOR_free_memory_block_tmp(env->allocator, block);
#ifdef SPVM_DEBUG_MEMORY
    SPVM_ALLOCATOR* allocator = env->allocator;
    assert(allocator->memory_blocks_count_permanent == 0);
    fprintf(stderr, "[free_memory_env %p (Env:%d)]\n", block, allocator->memory_blocks_count_tmp);
#endif
  }
}

int32_t SPVM_API_get_memory_blocks_count_env(SPVM_ENV* env) {
  (void)env;
  
  SPVM_ALLOCATOR* allocator = env->allocator;
  
  assert(allocator->memory_blocks_count_permanent == 0);
  int32_t memory_blocks_count_env = allocator->memory_blocks_count_tmp;
  
  return memory_blocks_count_env;
}

void* SPVM_API_new_memory_stack(SPVM_ENV* env, SPVM_VALUE* stack, size_t size) {
  
  assert(size > 0);
  
  if ((uint64_t)size > (uint64_t)SIZE_MAX) {
    return NULL;
  }
  
  void* block = SPVM_ALLOCATOR_alloc_memory_block_tmp(env->allocator, (size_t)size);
  
  stack[STACK_INDEX_MEMORY_BLOCKS_COUNT].ival++;
  
#ifdef SPVM_DEBUG_MEMORY
    SPVM_ALLOCATOR* allocator = env->allocator;
    assert(allocator->memory_blocks_count_permanent == 0);
    fprintf(stderr, "[Debug]new_memory_stack Mem, %p Env(%p):%d, Stack(%p):%d\n", block, env, allocator->memory_blocks_count_tmp, stack, stack[STACK_INDEX_MEMORY_BLOCKS_COUNT].ival);
#endif
  
  return block;
}

void SPVM_API_free_memory_stack(SPVM_ENV* env, SPVM_VALUE* stack, void* block) {

  if (block) {
    SPVM_ALLOCATOR_free_memory_block_tmp(env->allocator, block);
    stack[STACK_INDEX_MEMORY_BLOCKS_COUNT].ival--;
#ifdef SPVM_DEBUG_MEMORY
    SPVM_ALLOCATOR* allocator = env->allocator;
    assert(allocator->memory_blocks_count_permanent == 0);
    fprintf(stderr, "[Debug]free_memory_stack Mem %p, Env(%p):%d, Stack(%p):%d\n", block, env, allocator->memory_blocks_count_tmp, stack, stack[STACK_INDEX_MEMORY_BLOCKS_COUNT].ival);
#endif
  }
}

int32_t SPVM_API_get_memory_blocks_count_stack(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  int32_t memory_blocks_count_stack = stack[STACK_INDEX_MEMORY_BLOCKS_COUNT].ival;
  
  return memory_blocks_count_stack;
}

int8_t SPVM_API_get_class_var_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, class_var->current_basic_type_id);
  
  assert(basic_type);
  
  int32_t class_vars_length = basic_type->class_vars_length;
  
  assert(class_var->index >= 0 && class_var->index < class_vars_length);
  
  int8_t value = ((SPVM_VALUE*)(env->class_vars_heap))[basic_type->class_vars_base_address_id + class_var->index].bval;
  
  return value;
}

int16_t SPVM_API_get_class_var_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, class_var->current_basic_type_id);
  
  assert(basic_type);
  
  int32_t class_vars_length = basic_type->class_vars_length;
  
  assert(class_var->index >= 0 && class_var->index < class_vars_length);
  
  int16_t value = ((SPVM_VALUE*)(env->class_vars_heap))[basic_type->class_vars_base_address_id + class_var->index].sval;
  
  return value;
}

int32_t SPVM_API_get_class_var_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, class_var->current_basic_type_id);
  
  assert(basic_type);
  
  int32_t class_vars_length = basic_type->class_vars_length;
  
  assert(class_var->index >= 0 && class_var->index < class_vars_length);
  
  int32_t value = ((SPVM_VALUE*)(env->class_vars_heap))[basic_type->class_vars_base_address_id + class_var->index].ival;
  
  return value;
}

int64_t SPVM_API_get_class_var_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, class_var->current_basic_type_id);
  
  
  assert(basic_type);
  
  int32_t class_vars_length = basic_type->class_vars_length;
  
  assert(class_var->index >= 0 && class_var->index < class_vars_length);
  
  int64_t value = ((SPVM_VALUE*)(env->class_vars_heap))[basic_type->class_vars_base_address_id + class_var->index].lval;
  
  return value;
}

float SPVM_API_get_class_var_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, class_var->current_basic_type_id);
  
  assert(basic_type);
  
  int32_t class_vars_length = basic_type->class_vars_length;
  
  assert(class_var->index >= 0 && class_var->index < class_vars_length);
  
  float value = ((SPVM_VALUE*)(env->class_vars_heap))[basic_type->class_vars_base_address_id + class_var->index].fval;
 
  return value;
}

double SPVM_API_get_class_var_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, class_var->current_basic_type_id);
  
  assert(basic_type);
  
  int32_t class_vars_length = basic_type->class_vars_length;
  
  assert(class_var->index >= 0 && class_var->index < class_vars_length);
  
  double value = ((SPVM_VALUE*)(env->class_vars_heap))[basic_type->class_vars_base_address_id + class_var->index].dval;
  
  return value;
}

SPVM_OBJECT* SPVM_API_get_class_var_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, class_var->current_basic_type_id);
  
  assert(basic_type);
  
  int32_t class_vars_length = basic_type->class_vars_length;
  
  assert(class_var->index >= 0 && class_var->index < class_vars_length);
  
  SPVM_OBJECT* value_maybe_weaken = (SPVM_OBJECT*)((SPVM_VALUE*)(env->class_vars_heap))[basic_type->class_vars_base_address_id + class_var->index].oval;
  SPVM_OBJECT* value = SPVM_IMPLEMENT_GET_OBJECT_NO_WEAKEN_ADDRESS(env, stack, value_maybe_weaken);
  
  return value;
}

void SPVM_API_set_class_var_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, int8_t value) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, class_var->current_basic_type_id);
  
  assert(basic_type);
  
  int32_t class_vars_length = basic_type->class_vars_length;
  
  assert(class_var->index >= 0 && class_var->index < class_vars_length);
  
  ((SPVM_VALUE*)(env->class_vars_heap))[basic_type->class_vars_base_address_id + class_var->index].bval = value;
}

void SPVM_API_set_class_var_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, int16_t value) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, class_var->current_basic_type_id);
  
  assert(basic_type);
  
  int32_t class_vars_length = basic_type->class_vars_length;
  
  assert(class_var->index >= 0 && class_var->index < class_vars_length);
  
  ((SPVM_VALUE*)(env->class_vars_heap))[basic_type->class_vars_base_address_id + class_var->index].sval = value;
}

void SPVM_API_set_class_var_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, int32_t value) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, class_var->current_basic_type_id);
  
  assert(basic_type);
  
  int32_t class_vars_length = basic_type->class_vars_length;
  
  assert(class_var->index >= 0 && class_var->index < class_vars_length);
  
  ((SPVM_VALUE*)(env->class_vars_heap))[basic_type->class_vars_base_address_id + class_var->index].ival = value;
}

void SPVM_API_set_class_var_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, int64_t value) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, class_var->current_basic_type_id);
  
  assert(basic_type);
  
  int32_t class_vars_length = basic_type->class_vars_length;
  
  assert(class_var->index >= 0 && class_var->index < class_vars_length);
  
  ((SPVM_VALUE*)(env->class_vars_heap))[basic_type->class_vars_base_address_id + class_var->index].lval = value;
}

void SPVM_API_set_class_var_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, float value) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, class_var->current_basic_type_id);
  
  assert(basic_type);
  
  int32_t class_vars_length = basic_type->class_vars_length;
  
  assert(class_var->index >= 0 && class_var->index < class_vars_length);
  
  ((SPVM_VALUE*)(env->class_vars_heap))[basic_type->class_vars_base_address_id + class_var->index].fval = value;
}

void SPVM_API_set_class_var_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, double value) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, class_var->current_basic_type_id);
  
  assert(basic_type);
  
  int32_t class_vars_length = basic_type->class_vars_length;
  
  assert(class_var->index >= 0 && class_var->index < class_vars_length);
  
  ((SPVM_VALUE*)(env->class_vars_heap))[basic_type->class_vars_base_address_id + class_var->index].dval = value;
}

void SPVM_API_set_class_var_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, SPVM_OBJECT* value) {
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, class_var->current_basic_type_id);
  
  assert(basic_type);
  
  int32_t class_vars_length = basic_type->class_vars_length;
  
  assert(class_var->index >= 0 && class_var->index < class_vars_length);
  
  void* get_field_object_address = &((SPVM_VALUE*)(env->class_vars_heap))[basic_type->class_vars_base_address_id + class_var->index].oval;
  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, get_field_object_address, value);
}

SPVM_OBJECT* SPVM_API_new_array_proto_raw(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t length) {

  if (array == NULL) {
    return NULL;
  }
  
  if (length < 0) {
    return NULL;
  }
  
  size_t element_size = env->get_elem_size(env, stack, array);
  
  size_t alloc_size = (size_t)env->object_header_size + element_size * (length + 1);
  
  int32_t array_basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, array);
  SPVM_OBJECT* new_array = SPVM_API_new_object_common(env, stack, alloc_size, array_basic_type_id, array->type_dimension, length, 0);
  
  return new_array;
}

SPVM_OBJECT* SPVM_API_new_array_proto(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_new_array_proto_raw(env, stack, array, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_copy_raw(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  if (!object) {
    return NULL;
  }
  
  SPVM_OBJECT* new_object;
  
  int32_t length = object->length;
  
  if (env->is_string(env, stack, object)) {
    new_object = env->new_string_raw(env, stack, NULL, length);
    
    const char* object_chars = env->get_chars(env, stack, object);
    char* new_object_chars = (char*)env->get_chars(env, stack, new_object);
    
    memcpy(new_object_chars, object_chars, length);
  }
  else if (env->is_numeric_array(env, stack, object) || env->is_mulnum_array(env, stack, object)) {
    new_object = env->new_array_proto_raw(env, stack, object, length);
    
    const char* object_bytes = (const char*)env->get_elems_byte(env, stack, object);
    char* new_object_bytes = (char*)env->get_elems_byte(env, stack, new_object);
    
    size_t element_size = env->get_elem_size(env, stack, object);
    
    memcpy(new_object_bytes, object_bytes, element_size * length);
  }
  else {
    new_object = NULL;
  }
  
  return new_object;
}

SPVM_OBJECT* SPVM_API_copy(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  SPVM_OBJECT* new_object = SPVM_API_copy_raw(env, stack, object);
  
  SPVM_API_push_mortal(env, stack, new_object);
  
  return new_object;
}

void SPVM_API_shorten(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string, int32_t new_length) {
  (void)env;
  
  if (string != NULL) {
    if (env->is_string(env, stack, string)) {
      if (!env->is_read_only(env, stack, string)) {
        int32_t length = string->length;
        
        if (new_length > length) {
          new_length = length;
        }
        else if (new_length < 0) {
          new_length = 0;
        }
        
        string->length = new_length;
        char* chars = (char*)env->get_chars(env, stack, string);
        if (new_length > length) {
          memset(chars + new_length, 0, new_length - length);
        }
      }
    }
  }
}

int32_t SPVM_API_call_init_blocks(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e = 0;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Call INIT blocks
  int32_t basic_types_length = runtime->basic_types_length;
  for (int32_t basic_type_id = 0; basic_type_id < basic_types_length; basic_type_id++) {
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, basic_type_id);
    int32_t init_method_index = basic_type->init_method_index;
    if (init_method_index >= 0) {
      SPVM_RUNTIME_METHOD* init_method = SPVM_API_RUNTIME_get_method(env->runtime, basic_type_id, init_method_index);
      int32_t items = 0;
      e = env->call_method_raw(env, stack, init_method, items);
      if (e) { break; }
    }
  }
  
  return e;
}

int32_t SPVM_API_set_command_info_program_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* obj_program_name) {
  
  int32_t e = 0;
  
  if (!obj_program_name) {
    return env->die(env, stack, "The obj_program_name must be defined", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t obj_program_name_basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, obj_program_name);
  if (!(obj_program_name_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && obj_program_name->type_dimension == 0)) {
    return env->die(env, stack, "The obj_program_name must be a string", __func__, FILE_NAME, __LINE__);
  }
  
  env->set_class_var_object_by_name(env, stack, "CommandInfo", "$PROGRAM_NAME", obj_program_name, &e, __func__, __FILE__, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM_API_set_command_info_argv(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* obj_argv) {
  
  int32_t e = 0;
  
  if (!obj_argv) {
    return env->die(env, stack, "The obj_argv must be defined", __func__, FILE_NAME, __LINE__);
  }
  
  int32_t obj_argv_basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, obj_argv);
  if (!(obj_argv_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && obj_argv->type_dimension == 1)) {
    return env->die(env, stack, "The obj_argv must be a string array", __func__, FILE_NAME, __LINE__);
  }
  
  env->set_class_var_object_by_name(env, stack, "CommandInfo", "$ARGV", obj_argv, &e, __func__, __FILE__, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM_API_set_command_info_base_time(SPVM_ENV* env, SPVM_VALUE* stack, int64_t base_time) {
  
  int32_t e = 0;
  
  env->set_class_var_long_by_name(env, stack, "CommandInfo", "$BASE_TIME", base_time, &e, __func__, __FILE__, __LINE__);
  if (e) { return e; }
  
  return 0;
}

SPVM_ENV* SPVM_API_new_env(SPVM_ENV* env) {
  (void)env;
  
  // New raw env
  SPVM_ENV* new_env = SPVM_API_new_env_raw();
  
  // Set the runtime
  new_env->runtime = env->runtime;
  
  // Initialize env
  new_env->init_env(new_env);
  
  return new_env;
}

void SPVM_API_free_env(SPVM_ENV* env) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  SPVM_ALLOCATOR* allocator = runtime->allocator;
  SPVM_ALLOCATOR_free(allocator);
  runtime->allocator = NULL;
  allocator= NULL;
  
  env->free_env_raw(env);
}

void SPVM_API_free_env_prepared(SPVM_ENV* env) {

  SPVM_RUNTIME* runtime = env->runtime;

  // Free runtime
  SPVM_API_RUNTIME_free_object(runtime);
  env->runtime = NULL;
  
  // Free env
  env->free_env_raw(env);
}

int32_t SPVM_API_elem_isa(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, SPVM_OBJECT* element) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  assert(array);
  
  int32_t array_basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, array);
  int32_t array_type_dimension = array->type_dimension;
  
  assert(array_type_dimension > 0);
  int32_t runtime_assignability = SPVM_API_isa(env, stack, element, array_basic_type_id, array_type_dimension - 1);

  return runtime_assignability;
}

int32_t SPVM_API_is_type(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t basic_type_id, int32_t type_dimension) {
  
  // Object must be not null
  assert(object);

  int32_t object_basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, object);
  if (object_basic_type_id == basic_type_id && object->type_dimension == type_dimension) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_API_is_type_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* basic_type_name, int32_t type_dimension) {
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    return 0;
  };
  
  int32_t is_type = SPVM_API_is_type(env, stack, object, basic_type_id, type_dimension);
  
  return is_type;
}

int32_t SPVM_API_isa(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t basic_type_id, int32_t type_dimension) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t isa;
  if (object == NULL) {
    isa = 1;
  }
  else {
    int32_t object_basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, object);
    int32_t object_type_dimension = object->type_dimension;
    
    isa = SPVM_API_RUNTIME_can_assign(env->runtime, basic_type_id, type_dimension, 0, object_basic_type_id, object_type_dimension, 0);
  }
  
  return isa;
}

int32_t SPVM_API_isa_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* basic_type_name, int32_t type_dimension) {
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    return 0;
  };
  
  int32_t isa = SPVM_API_isa(env, stack, object, basic_type_id, type_dimension);
  
  return isa;
}

int32_t SPVM_API_has_interface(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t interface_basic_type_id) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  assert(object);
  
  int32_t object_type_dimension = object->type_dimension;
  int32_t has_interface;
  if (object->type_dimension > 0) {
    has_interface = 0;
  }
  else {
    int32_t object_basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, object);
    has_interface = SPVM_API_RUNTIME_has_interface_by_id(runtime, object_basic_type_id, interface_basic_type_id);
  }
  
  return has_interface;
}

int32_t SPVM_API_has_interface_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* basic_type_name) {
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    return 0;
  };
  
  int32_t has_interface = SPVM_API_has_interface(env, stack, object, basic_type_id);
  
  return has_interface;
}

int32_t SPVM_API_get_basic_type_id_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error, const char* func_name, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, stack, basic_type_name);
  if (basic_type_id < 0) {
    *error = 1;
    env->die(env, stack, "The %s basic type is not found", basic_type_name, func_name, file, line);
  };
  return basic_type_id;
}

void* SPVM_API_strerror_string(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length) {
  
  if (length < 0) {
    return NULL;
  }
  
  if (length == 0) {
    length = 64;
  }
  
  void* obj_strerror_value = env->new_string(env, stack, NULL, length);
  char* strerror_value = (char*)env->get_chars(env, stack, obj_strerror_value);
  
  int32_t status = SPVM_STRERROR_strerror(errno_value, strerror_value, length);
  
  if (status == 0) {
    env->shorten(env, stack, obj_strerror_value, strlen(strerror_value));
    return obj_strerror_value;
  }
  else {
    return NULL;
  }
}

const char* SPVM_API_strerror(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length) {
  
  void* obj_strerror_value = SPVM_API_strerror_string(env, stack, errno_value, length);
  
  if (obj_strerror_value) {
    char* strerror_value = (char*)env->get_chars(env, stack, obj_strerror_value);
    return strerror_value;
  }
  else {
    return NULL;
  }
}

void* SPVM_API_strerror_string_nolen(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value) {
  return SPVM_API_strerror_string(env, stack, errno_value, 0);
}

const char* SPVM_API_strerror_nolen(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value) {
  return SPVM_API_strerror(env, stack, errno_value, 0);
}

int32_t SPVM_API_get_args_stack_length(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  int32_t args_length = stack[STACK_INDEX_ARGS_STACK_LENGTH].ival;
  
  return args_length;
}

int32_t SPVM_API_items(SPVM_ENV* env, SPVM_VALUE* stack) {
  return SPVM_API_get_args_stack_length(env, stack);
}

void SPVM_API_set_args_stack_length(SPVM_ENV* env, SPVM_VALUE* stack, int32_t args_length) {
  (void)env;
  
  stack[STACK_INDEX_ARGS_STACK_LENGTH].ival = args_length;
}

int32_t SPVM_API_call_method_vm(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* method, int32_t args_stack_length) {
  return SPVM_VM_call_method(env, stack, method, args_stack_length);
}

const char* SPVM_API_get_spvm_version_string(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  const char* spvm_version = SPVM_VERSION;
  
  return spvm_version;
}

double SPVM_API_get_spvm_version_number(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  const char* spvm_version_string = env->get_spvm_version_string(env, stack);
  
  assert(spvm_version_string);
  
  int32_t spvm_version_string_length = strlen(spvm_version_string);
  
  char spvm_version_string_without_hyphen[20] = {0};
  int32_t spvm_version_string_without_hyphen_length = 0;
  for (int32_t i = 0; i < spvm_version_string_length; i++) {
    char ch = spvm_version_string[i];
    if (!(ch == '_')) {
      spvm_version_string_without_hyphen[spvm_version_string_without_hyphen_length] = ch;
      spvm_version_string_without_hyphen_length++;
    }
  }
  
  char *end;
  errno = 0;
  double version_number = strtod(spvm_version_string_without_hyphen, &end);
  assert(*end == '\0');
  assert(errno == 0);
  
  return version_number;
}

const char* SPVM_API_get_version_string(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id){
  
  int32_t version_string_id = env->api->runtime->get_basic_type_version_string_id(env->runtime, basic_type_id);
  
  const char* version_string = NULL;
  if (version_string_id >= 0) {
    version_string = env->api->runtime->get_name(env->runtime, version_string_id);
  }
  
  return version_string;
}

double SPVM_API_get_version_number(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id) {
  
  const char* version_string = env->get_version_string(env, stack, basic_type_id);
  
  if (!version_string) {
    return -1;
  }
  
  int32_t version_string_length = strlen(version_string);
  
  char version_string_without_hyphen[20] = {0};
  int32_t version_string_without_hyphen_length = 0;
  for (int32_t i = 0; i < version_string_length; i++) {
    char ch = version_string[i];
    if (!(ch == '_')) {
      version_string_without_hyphen[version_string_without_hyphen_length] = ch;
      version_string_without_hyphen_length++;
    }
  }
  
  char *end;
  errno = 0;
  double version_number = strtod(version_string_without_hyphen, &end);
  assert(*end == '\0');
  assert(errno == 0);
  
  return version_number;
}

// Will be removed
int32_t SPVM_API_get_field_id(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name) {
  (void)env;
  
  int32_t field_address_id = -1;
  
  // Compiler
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (!object) {
    return -1;
  }
  
  // Basic type
  int32_t object_basic_type_id = SPVM_API_get_object_basic_type_id(env, stack, object);
  
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, object_basic_type_id);

  // Type dimension
  if (object->type_dimension != 0) {
    return -1;
  }

  SPVM_RUNTIME_BASIC_TYPE* parent_basic_type = object_basic_type;
  
  while (1) {
    if (!parent_basic_type) {
      break;
    }
    
    // Method
    SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_name(runtime, object_basic_type->id, field_name);
    if (field) {
      field_address_id = field->address_id;
      break;
    }
    
    if (parent_basic_type->parent_id != -1) {
      parent_basic_type = SPVM_API_RUNTIME_get_basic_type(env->runtime, parent_basic_type->parent_id);
    }
    else {
      parent_basic_type = NULL;
    }
  }
  
  return field_address_id;
}

// Will be removed
int32_t SPVM_API_get_field_id_static(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* field_name) {
  int32_t field_address_id = SPVM_API_RUNTIME_get_field_address_id_by_name(env->runtime, basic_type_name, field_name);
  
  return field_address_id;
}

int8_t SPVM_API_get_field_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_address_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);
  
  // Get field value
  int8_t value = *(int8_t*)((intptr_t)object + env->object_header_size + field->offset);

  return value;
}

int16_t SPVM_API_get_field_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_address_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);
  
  // Get field value
  int16_t value = *(int16_t*)((intptr_t)object + env->object_header_size + field->offset);
  
  return value;
}

int32_t SPVM_API_get_field_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_address_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);

  // Get field value
  int32_t value = *(int32_t*)((intptr_t)object + env->object_header_size + field->offset);
  
  return value;
}

int64_t SPVM_API_get_field_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_address_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);

  // Get field value
  int64_t value = *(int64_t*)((intptr_t)object + env->object_header_size + field->offset);
  
  return value;
}

float SPVM_API_get_field_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_address_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);

  // Get field value
  float value = *(float*)((intptr_t)object + env->object_header_size + field->offset);
  
  return value;
}

double SPVM_API_get_field_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_address_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);

  // Get field value
  double value = *(double*)((intptr_t)object + env->object_header_size + field->offset);
  
  return value;
}

SPVM_OBJECT* SPVM_API_get_field_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_address_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);
  
  // Get field value
  SPVM_OBJECT* value_maybe_weaken = *(SPVM_OBJECT**)((intptr_t)object + env->object_header_size + field->offset);
  SPVM_OBJECT* value = SPVM_IMPLEMENT_GET_OBJECT_NO_WEAKEN_ADDRESS(env, stack, value_maybe_weaken);
  
  return value;
}

void SPVM_API_set_field_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_address_id, int8_t value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);

  // Get field value
  *(int8_t*)((intptr_t)object + env->object_header_size + field->offset) = value;
}

void SPVM_API_set_field_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_address_id, int16_t value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);

  // Get field value
  *(int16_t*)((intptr_t)object + env->object_header_size + field->offset) = value;
}

void SPVM_API_set_field_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_address_id, int32_t value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);

  // Get field value
  *(int32_t*)((intptr_t)object + env->object_header_size + field->offset) = value;
}

void SPVM_API_set_field_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_address_id, int64_t value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);

  // Get field value
  *(int64_t*)((intptr_t)object + env->object_header_size + field->offset) = value;
}

void SPVM_API_set_field_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_address_id, float value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);

  // Get field value
  *(float*)((intptr_t)object + env->object_header_size + field->offset) = value;
}

void SPVM_API_set_field_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_address_id, double value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);

  // Get field value
  *(double*)((intptr_t)object + env->object_header_size + field->offset) = value;
}

void SPVM_API_set_field_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_address_id, SPVM_OBJECT* value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);
  
  // Get field value
  void* get_field_object_address = (void**)((intptr_t)object + env->object_header_size + field->offset);

  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, get_field_object_address, value);
}

// Will be removed
int32_t SPVM_API_get_field_offset(SPVM_ENV* env, SPVM_VALUE* stack, int32_t field_address_id) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);
  
  return field->offset;
}
