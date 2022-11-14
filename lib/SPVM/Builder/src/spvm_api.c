#include <inttypes.h>
#include <stdlib.h>
#include <assert.h>

#include "spvm_native.h"

#include "spvm_api.h"
#include "spvm_api_vm.h"
#include "spvm_api_runtime.h"
#include "spvm_api_allocator.h"
#include "spvm_api_string_buffer.h"

#include "spvm_strerror.h"
#include "spvm_object.h"
#include "spvm_allocator.h"
#include "spvm_weaken_backref.h"
#include "spvm_hash.h"
#include "spvm_string_buffer.h"

#include "spvm_runtime.h"
#include "spvm_runtime_constant_string.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_type.h"
#include "spvm_runtime_class.h"
#include "spvm_runtime_class_var.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_method.h"

#ifndef SPVM_NO_COMPILER_API
#  include "spvm_api_compiler.h"
#  include "spvm_api_precompile.h"
#endif

static const char* FILE_NAME = "spvm_api.c";

SPVM_ENV* SPVM_API_new_env_raw() {

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
    (void*)(intptr_t)sizeof(SPVM_OBJECT), // object_header_byte_size
    (void*)(intptr_t)offsetof(SPVM_OBJECT, weaken_backref_head), // weaken_backref_head
    (void*)(intptr_t)offsetof(SPVM_OBJECT, ref_count), // object_ref_count_offset
    (void*)(intptr_t)offsetof(SPVM_OBJECT, basic_type_id), // object_basic_type_id_offset
    (void*)(intptr_t)offsetof(SPVM_OBJECT, type_dimension), // object_type_dimension_offset
    (void*)NULL, // object_type_category_offset(unused)
    (void*)(intptr_t)offsetof(SPVM_OBJECT, flag), // object_flag_offset
    (void*)(intptr_t)offsetof(SPVM_OBJECT, length), // object_length_offset
    env_api,
    allocator, // allocator
    SPVM_API_new_env_raw,
    SPVM_API_free_env_raw,
    SPVM_API_isa,
    SPVM_API_elem_isa,
    NULL, // runtime
    SPVM_API_get_field_object_by_name_v2,
    SPVM_API_set_field_object_by_name_v2,
    NULL, // reserved18
    NULL, // reserved19
    SPVM_API_get_basic_type_id,
    SPVM_API_get_field_id,
    SPVM_API_get_field_offset,
    SPVM_API_get_class_var_id,
    SPVM_API_get_class_method_id,
    SPVM_API_get_instance_method_id,
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
    SPVM_API_new_pointer_raw,
    SPVM_API_new_pointer,
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
    SPVM_API_call_spvm_method,
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
    SPVM_API_new_pointer_by_name,
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
    SPVM_API_call_class_method,
    SPVM_API_call_instance_method,
    SPVM_API_get_instance_method_id_static,
    SPVM_API_get_bool_object_value,
    SPVM_API_cleanup_global_vars,
    SPVM_API_make_read_only,
    SPVM_API_is_read_only,
    SPVM_API_is_array,
    SPVM_API_is_string,
    SPVM_API_is_numeric_array,
    SPVM_API_is_mulnum_array,
    SPVM_API_get_elem_byte_size,
    SPVM_API_new_array_proto_raw,
    SPVM_API_new_array_proto,
    SPVM_API_copy_raw,
    SPVM_API_copy,
    SPVM_API_shorten,
    SPVM_API_has_interface,
    NULL,
    NULL,
    NULL,
    SPVM_API_print,
    SPVM_API_print_stderr,
    SPVM_API_init_env,
    SPVM_API_call_init_blocks,
    SPVM_API_get_class_id,
    SPVM_API_new_stack,
    SPVM_API_free_stack,
    NULL,
    SPVM_API_new_memory_env,
    SPVM_API_free_memory_env,
    SPVM_API_get_memory_blocks_count_env,
    SPVM_API_new_memory_stack,
    SPVM_API_free_memory_stack,
    SPVM_API_get_memory_blocks_count_stack,
    SPVM_API_set_command_info_program_name,
    SPVM_API_set_command_info_argv,
    SPVM_API_get_class_id_by_name,
    SPVM_API_strerror,
    SPVM_API_new_string_array,
    SPVM_API_get_args_stack_length,
    SPVM_API_set_args_stack_length,
    SPVM_API_dumpc,
    SPVM_API_new_pointer_with_fields_raw,
    SPVM_API_new_pointer_with_fields,
    SPVM_API_new_pointer_with_fields_by_name,
    SPVM_API_get_pointer_no_need_free,
    SPVM_API_set_pointer_no_need_free,
    SPVM_API_get_pointer_length,
    SPVM_API_set_pointer_length,
    SPVM_API_is_class,
    SPVM_API_is_pointer_class,
    SPVM_API_get_pointer_fields_length,
    SPVM_API_get_pointer_field_byte,
    SPVM_API_get_pointer_field_short,
    SPVM_API_get_pointer_field_int,
    SPVM_API_get_pointer_field_long,
    SPVM_API_get_pointer_field_float,
    SPVM_API_get_pointer_field_double,
    SPVM_API_get_pointer_field_pointer,
    SPVM_API_set_pointer_field_byte,
    SPVM_API_set_pointer_field_short,
    SPVM_API_set_pointer_field_int,
    SPVM_API_set_pointer_field_long,
    SPVM_API_set_pointer_field_float,
    SPVM_API_set_pointer_field_double,
    SPVM_API_set_pointer_field_pointer,
    SPVM_API_strerror_string,
    SPVM_API_get_basic_type_id_by_name,
  };
  
  SPVM_ENV* env = calloc(1, sizeof(env_init));
  if (env == NULL) {
    return NULL;
  }
  memcpy(env, env_init, sizeof(env_init));

  return env;
}

int32_t SPVM_API_init_env(SPVM_ENV* env) {
  
  SPVM_RUNTIME* runtime = env->runtime;

  // Initialize Class Variables
  void* class_vars_heap = SPVM_API_new_memory_env(env, sizeof(SPVM_VALUE) * ((int64_t)runtime->class_vars_length + 1));
  if (class_vars_heap == NULL) {
    return 2;
  }
  
  env->class_vars_heap = class_vars_heap;

  // Adjust alignment SPVM_VALUE
  int32_t object_header_byte_size = sizeof(SPVM_OBJECT);
  if (object_header_byte_size % sizeof(SPVM_VALUE) != 0) {
    object_header_byte_size += (sizeof(SPVM_VALUE) - object_header_byte_size % sizeof(SPVM_VALUE));
  }
  assert(object_header_byte_size % sizeof(SPVM_VALUE) == 0);
  
  // Object header byte size
  env->object_header_byte_size = (void*)(intptr_t)object_header_byte_size;
  
  return 0;
}

void SPVM_API_make_read_only(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string) {
  if (string && (string->basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && string->type_dimension == 0)) {
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
    int32_t basic_type_id = object->basic_type_id;
    int32_t type_dimension = object->type_dimension;
    
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
    const char* basic_type_name = SPVM_API_RUNTIME_get_basic_type_name(runtime, basic_type->id);
    
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
            
      for (int32_t array_index = 0; array_index < array_length; array_index++) {
    
        for (int32_t depth_index = 0; depth_index < *depth + 1; depth_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
        }

        if (SPVM_API_is_mulnum_array(env, stack, object)) {

          SPVM_STRING_BUFFER_add(string_buffer, "{\n");

          SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
          SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, basic_type->class_id);
          int32_t fields_length = class->fields_length;
          
          for (int32_t field_index = 0; field_index < fields_length; field_index++) {
            for (int32_t depth_index = 0; depth_index < *depth + 2; depth_index++) {
              SPVM_STRING_BUFFER_add(string_buffer, "  ");
            }
            
            SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, class->fields_base_id + field_index);
            
            SPVM_RUNTIME_TYPE* field_type =SPVM_API_RUNTIME_get_type(runtime, field->type_id);

            int32_t field_basic_type_id = field_type->basic_type_id;

            const char* field_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, field->name_id, NULL);
            SPVM_STRING_BUFFER_add(string_buffer, field_name);
            SPVM_STRING_BUFFER_add(string_buffer, " => ");

            switch (field_basic_type_id) {
              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                int8_t* element = &((int8_t*)((intptr_t)object + env->object_header_byte_size))[array_index * fields_length];
                sprintf(tmp_buffer, "%d", element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                int16_t* element = &((int16_t*)((intptr_t)object + env->object_header_byte_size))[array_index * fields_length];
                sprintf(tmp_buffer, "%d", element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                int32_t* element = &((int32_t*)((intptr_t)object + env->object_header_byte_size))[array_index * fields_length];
                sprintf(tmp_buffer, "%d", element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                int64_t* element = &((int64_t*)((intptr_t)object + env->object_header_byte_size))[array_index * fields_length];
                sprintf(tmp_buffer, "%lld", (long long int)element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                float* element = &((float*)((intptr_t)object + env->object_header_byte_size))[array_index * fields_length];
                sprintf(tmp_buffer, "%g", element[field_index]);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                double* element = &((double*)((intptr_t)object + env->object_header_byte_size))[array_index * fields_length];
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
              int8_t element = ((int8_t*)((intptr_t)object + env->object_header_byte_size))[array_index];
              sprintf(tmp_buffer, "%d", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
              int16_t element = ((int16_t*)((intptr_t)object + env->object_header_byte_size))[array_index];
              sprintf(tmp_buffer, "%d", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
              int32_t element = ((int32_t*)((intptr_t)object + env->object_header_byte_size))[array_index];
              sprintf(tmp_buffer, "%d", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
              int64_t element = ((int64_t*)((intptr_t)object + env->object_header_byte_size))[array_index];
              sprintf(tmp_buffer, "%lld", (long long int)element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
              float element = ((float*)((intptr_t)object + env->object_header_byte_size))[array_index];
              sprintf(tmp_buffer, "%g", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
              double element = ((double*)((intptr_t)object + env->object_header_byte_size))[array_index];
              sprintf(tmp_buffer, "%g", element);
              SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
              break;
            }
          }
        }
        else if (SPVM_API_is_object_array(env, stack, object)) {
          SPVM_OBJECT* element = (((SPVM_OBJECT**)((intptr_t)object + env->object_header_byte_size))[array_index]);
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
      sprintf(tmp_buffer, "(%p)", (void*)((intptr_t)object & ~1));
      SPVM_STRING_BUFFER_add(string_buffer, tmp_buffer);
    }
    else {

      // If the object is weaken, this get the real address
      sprintf(tmp_buffer, "%p", (void*)((intptr_t)object & ~1));
      int32_t exists = (int32_t)(intptr_t)SPVM_HASH_get(address_symtable, tmp_buffer, strlen(tmp_buffer));
      if (exists) {
        // If the object is weaken, this get the real address
        sprintf(tmp_buffer, "REUSE_OBJECT(%p)", (void*)((intptr_t)object & ~1));
        SPVM_STRING_BUFFER_add(string_buffer, tmp_buffer);
      }
      else {
        SPVM_HASH_set(address_symtable, tmp_buffer, strlen(tmp_buffer), (void*)(intptr_t)1);
        
        SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
        SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, basic_type->class_id);
        assert(class);

        SPVM_STRING_BUFFER_add(string_buffer, basic_type_name);
        sprintf(tmp_buffer, " (%p) ", object);
        SPVM_STRING_BUFFER_add(string_buffer, tmp_buffer);

        SPVM_STRING_BUFFER_add(string_buffer, "{\n");
        
        // Free object fields
        int32_t fields_length = class->fields_length;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          for (int32_t depth_index = 0; depth_index < *depth + 1; depth_index++) {
            SPVM_STRING_BUFFER_add(string_buffer, "  ");
          }

          SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, class->fields_base_id + field_index);
          
          SPVM_RUNTIME_TYPE* field_type =SPVM_API_RUNTIME_get_type(runtime, field->type_id);
          
          int32_t field_basic_type_id = field_type->basic_type_id;
          int32_t field_type_dimension = field_type->dimension;
          int32_t field_offset = field->offset;
          const char* field_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, field->name_id, NULL);
          
          SPVM_STRING_BUFFER_add(string_buffer, field_name);
          SPVM_STRING_BUFFER_add(string_buffer, " => ");
          if (field_type_dimension == 0 && field_basic_type_id >= SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE && field_basic_type_id <= SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
            switch (field_basic_type_id) {
              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                int8_t field_value = *(int8_t*)((intptr_t)object + (intptr_t)env->object_header_byte_size + field_offset);
                sprintf(tmp_buffer, "%d", field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                int16_t field_value = *(int16_t*)((intptr_t)object + (intptr_t)env->object_header_byte_size + field_offset);
                sprintf(tmp_buffer, "%d", field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                int32_t field_value = *(int32_t*)((intptr_t)object + (intptr_t)env->object_header_byte_size + field_offset);
                sprintf(tmp_buffer, "%d", field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                int64_t field_value = *(int64_t*)((intptr_t)object + (intptr_t)env->object_header_byte_size + field_offset);
                sprintf(tmp_buffer, "%lld", (long long int)field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                float field_value = *(float*)((intptr_t)object + (intptr_t)env->object_header_byte_size + field_offset);
                sprintf(tmp_buffer, "%g", field_value);
                SPVM_STRING_BUFFER_add(string_buffer, (const char*)tmp_buffer);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                double field_value = *(double*)((intptr_t)object + (intptr_t)env->object_header_byte_size + field_offset);
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
            SPVM_OBJECT* field_value = *(SPVM_OBJECT**)((intptr_t)object + (intptr_t)env->object_header_byte_size + field_offset);
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

const char* SPVM_API_get_field_string_chars_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* error, const char* file, int32_t line) {
  *error = 0;

  int32_t id = env->get_field_id(env, class_name, field_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The field %s->%s is not defined", class_name, field_name, file, line);
    return NULL;
  };
  SPVM_OBJECT* value = env->get_field_object(env, stack, object, id);
  if (value == NULL) {
    return NULL;
  }
  else {
    const char* chars = env->get_chars(env, stack, value);
    return chars;
  }
}

int32_t SPVM_API_call_class_method_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* method_name, int32_t args_stack_length, const char* file, int32_t line) {
  
  int32_t method_id = env->get_class_method_id(env, class_name, method_name);
  if (method_id < 0) {
    env->die(env, stack, "The class method %s->%s is not defined", class_name, method_name, file, line);
    return 1;
  }
  int32_t e = env->call_class_method(env, stack, method_id, args_stack_length);
  if (e) {
    const char* message = env->get_chars(env, stack, env->get_exception(env, stack));
    env->die(env, stack, "%s", message, file, line);
    return e;
  }
  
  return 0;
}

int32_t SPVM_API_call_instance_method_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* method_name, int32_t args_stack_length, const char* file, int32_t line) {
  
  if (object == NULL) {
    env->die(env, stack, "Object must not be NULL", file, line);
    return 1;
  };

  int32_t method_id = env->get_instance_method_id(env, object, method_name);
  if (method_id < 0) {
    env->die(env, stack, "The instance method INVOCANT<%p>->%s is not defined", object, method_name, file, line);
    return 1;
  };
  int32_t e = env->call_instance_method(env, stack, method_id, args_stack_length);
  
  if (e) {
    const char* message = env->get_chars(env, stack, env->get_exception(env, stack));
    env->die(env, stack, "%s", message, file, line);
    return e;
  }
  
  return 0;
}

void* SPVM_API_new_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_basic_type_id(env, class_name);
  if (id < 0) {
    env->die(env, stack, "The class \"%s\" is not loaded", class_name, file, line);
    *error = 1;
    return NULL;
  };
  
  void* object = env->new_object(env, stack, id);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_pointer_with_fields_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, void* pointer, int32_t fields_length, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_basic_type_id(env, class_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The class \"%s\" is not loaded", class_name, file, line);
    return NULL;
  };
  SPVM_OBJECT* object = SPVM_API_new_pointer_with_fields(env, stack, id, pointer, fields_length);
  return object;
}

SPVM_OBJECT* SPVM_API_new_pointer_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, void* pointer, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_basic_type_id(env, class_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The class \"%s\" is not loaded", class_name, file, line);
    return NULL;
  };
  SPVM_OBJECT* object = env->new_pointer(env, stack, id, pointer);
  return object;
}

void SPVM_API_set_field_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int8_t value, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_field_id(env, class_name, field_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The field %s->%s is not defined", class_name, field_name, file, line);
    return;
  }
  env->set_field_byte(env, stack, object, id, value);
}

void SPVM_API_set_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int16_t value, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_field_id(env, class_name, field_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The field %s->%s is not defined", class_name, field_name, file, line);
    return;
  };
  env->set_field_short(env, stack, object, id, value);
}

void SPVM_API_set_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t value, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_field_id(env, class_name, field_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The field %s->%s is not defined", class_name, field_name, file, line);
    return;
  };
  env->set_field_int(env, stack, object, id, value);
}

void SPVM_API_set_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int64_t value, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_field_id(env, class_name, field_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The field %s->%s is not defined", class_name, field_name, file, line);
    return;
  };
  env->set_field_long(env, stack, object, id, value);
}

void SPVM_API_set_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, float value, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_field_id(env, class_name, field_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The field %s->%s is not defined", class_name, field_name, file, line);
    return;
  };
  env->set_field_float(env, stack, object, id, value);
}

void SPVM_API_set_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, double value, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_field_id(env, class_name, field_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The field %s->%s is not defined", class_name, field_name, file, line);
    return;
  };
  env->set_field_double(env, stack, object, id, value);
}

void SPVM_API_set_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, SPVM_OBJECT* value, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_field_id(env, class_name, field_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The field %s->%s is not defined", class_name, field_name, file, line);
    return;
  };
  env->set_field_object(env, stack, object, id, value);
}

void SPVM_API_set_field_object_by_name_v2(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, SPVM_OBJECT* value, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->api->runtime->get_field_id_by_name(env->runtime, class_name, field_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The field %s->%s is not defined", class_name, field_name, file, line);
    return;
  };
  env->set_field_object(env, stack, object, id, value);
}

int8_t SPVM_API_get_field_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_field_id(env, class_name, field_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The field %s->%s is not defined", class_name, field_name, file, line);
    return 0;
  };
  int8_t value = env->get_field_byte(env, stack, object, id);
  return value;
}

int16_t SPVM_API_get_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_field_id(env, class_name, field_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The field %s->%s is not defined", class_name, field_name, file, line);
    return 0;
  };
  int16_t value = env->get_field_short(env, stack, object, id);
  return value;
}

int32_t SPVM_API_get_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_field_id(env, class_name, field_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The field %s->%s is not defined", class_name, field_name, file, line);
    return 0;
  };
  int32_t value = env->get_field_int(env, stack, object, id);
  return value;
}

int64_t SPVM_API_get_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_field_id(env, class_name, field_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The field %s->%s is not defined", class_name, field_name, file, line);
    return 0;
  };
  int64_t value = env->get_field_long(env, stack, object, id);
  return value;
}

float SPVM_API_get_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_field_id(env, class_name, field_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The field %s->%s is not defined", class_name, field_name, file, line);
    return 0;
  };
  float value = env->get_field_float(env, stack, object, id);
  return value;
}

double SPVM_API_get_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_field_id(env, class_name, field_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The field %s->%s is not defined", class_name, field_name, file, line);
    return 0;
  };
  double value = env->get_field_double(env, stack, object, id);
  return value;
}

SPVM_OBJECT* SPVM_API_get_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_field_id(env, class_name, field_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The field %s->%s is not defined", class_name, field_name, file, line);
    return NULL;
  };
  SPVM_OBJECT* value = env->get_field_object(env, stack, object, id);
  return value;
}

SPVM_OBJECT* SPVM_API_get_field_object_by_name_v2(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t id = env->api->runtime->get_field_id_by_name(runtime, class_name, field_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The field %s->%s is not defined", class_name, field_name, file, line);
    return NULL;
  };
  SPVM_OBJECT* value = env->get_field_object(env, stack, object, id);
  return value;
}

void SPVM_API_set_class_var_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int8_t value, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_class_var_id(env, class_name, class_var_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The class variable %s in %s is not defined", class_var_name, class_name, file, line);
    return;
  };
  env->set_class_var_byte(env, stack, id, value);
}

void SPVM_API_set_class_var_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int16_t value, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_class_var_id(env, class_name, class_var_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The class variable %s in %s is not defined", class_var_name, class_name, file, line);
    return;
  };
  env->set_class_var_short(env, stack, id, value);
}

void SPVM_API_set_class_var_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t value, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_class_var_id(env, class_name, class_var_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The class variable %s in %s is not defined", class_var_name, class_name, file, line);
    return;
  };
  env->set_class_var_int(env, stack, id, value);
}

void SPVM_API_set_class_var_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int64_t value, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_class_var_id(env, class_name, class_var_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The class variable %s in %s is not defined", class_var_name, class_name, file, line);
    return;
  };
  env->set_class_var_long(env, stack, id, value);
}

void SPVM_API_set_class_var_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, float value, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_class_var_id(env, class_name, class_var_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The class variable %s in %s is not defined", class_var_name, class_name, file, line);
    return;
  };
  env->set_class_var_float(env, stack, id, value);
}

void SPVM_API_set_class_var_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, double value, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_class_var_id(env, class_name, class_var_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The class variable %s in %s is not defined", class_var_name, class_name, file, line);
    return;
  };
  env->set_class_var_double(env, stack, id, value);
}

void SPVM_API_set_class_var_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, SPVM_OBJECT* value, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_class_var_id(env, class_name, class_var_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The class variable %s in %s is not defined", class_var_name, class_name, file, line);
    return;
  };
  env->set_class_var_object(env, stack, id, value);
}

int8_t SPVM_API_get_class_var_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_class_var_id(env, class_name, class_var_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The class variable %s in %s is not defined", class_var_name, class_name, file, line);
    return 0;
  };
  int8_t value = env->get_class_var_byte(env, stack, id);
  return value;
}

int16_t SPVM_API_get_class_var_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_class_var_id(env, class_name, class_var_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The class variable %s in %s is not defined", class_var_name, class_name, file, line);
    return 0;
  };
  int16_t value = env->get_class_var_short(env, stack, id);
  return value;
}

int32_t SPVM_API_get_class_var_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_class_var_id(env, class_name, class_var_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The class variable %s in %s is not defined", class_var_name, class_name, file, line);
    return 0;
  };
  int32_t value = env->get_class_var_int(env, stack, id);
  return value;
}

int64_t SPVM_API_get_class_var_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_class_var_id(env, class_name, class_var_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The class variable %s in %s is not defined", class_var_name, class_name, file, line);
    return 0;
  };
  int64_t value = env->get_class_var_long(env, stack, id);
  return value;
}

float SPVM_API_get_class_var_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_class_var_id(env, class_name, class_var_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The class variable %s in %s is not defined", class_var_name, class_name, file, line);
    return 0;
  };
  float value = env->get_class_var_float(env, stack, id);
  return value;
}

double SPVM_API_get_class_var_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_class_var_id(env, class_name, class_var_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The class variable %s in %s is not defined", class_var_name, class_name, file, line);
    return 0;
  };
  double value = env->get_class_var_double(env, stack, id);
  return value;
}

SPVM_OBJECT* SPVM_API_get_class_var_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t id = env->get_class_var_id(env, class_name, class_var_name);
  if (id < 0) {
    *error = 1;
    env->die(env, stack, "The class variable %s in %s is not defined", class_var_name, class_name, file, line);
    return NULL;
  };
  SPVM_OBJECT* value = env->get_class_var_object(env, stack, id);
  return value;
}

int32_t SPVM_API_die(SPVM_ENV* env, SPVM_VALUE* stack, const char* message, ...) {
  
  va_list args;
  
  char* message_with_line = (char*)SPVM_API_new_memory_stack(env, stack, 512);
  int32_t message_length = strlen(message);
  if (message_length > 255) {
    message_length = 255;
  }
  memcpy(message_with_line, message, message_length);
  const char* file_line = " at %s line %d";
  memcpy(message_with_line + message_length, file_line, strlen(file_line));

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
  
  return SPVM_NATIVE_C_CLASS_ID_ERROR;
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
  for (int32_t class_var_id = 0; class_var_id < runtime->class_vars_length; class_var_id++) {
    SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var(runtime, class_var_id);

    int32_t class_var_type_is_object = SPVM_API_RUNTIME_get_type_is_object(runtime, class_var->type_id);
    if (class_var_type_is_object) {
      SPVM_OBJECT* object = *(void**)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id];
      if (object) {
        SPVM_API_dec_ref_count(env, stack, object);
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

int32_t SPVM_API_call_class_method(SPVM_ENV* env, SPVM_VALUE* stack, int32_t method_id, int32_t args_stack_length) {
  return SPVM_API_call_spvm_method(env, stack, method_id, args_stack_length);
}

int32_t SPVM_API_call_instance_method(SPVM_ENV* env, SPVM_VALUE* stack, int32_t method_id, int32_t args_stack_length) {
  return SPVM_API_call_spvm_method(env, stack, method_id, args_stack_length);
}

int32_t SPVM_API_call_spvm_method_precompile_address(SPVM_ENV* env, SPVM_VALUE* stack, int32_t method_id, int32_t args_stack_length) {
  
}

int32_t SPVM_API_call_spvm_method(SPVM_ENV* env, SPVM_VALUE* stack, int32_t method_id, int32_t args_stack_length) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Method
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  
  int32_t error = 0;
  stack[STACK_INDEX_ARGS_LENGTH].ival = args_stack_length;
  stack[STACK_INDEX_CALL_DEPTH].ival++;
  
  int32_t max_call_depth = 10000;
  if (stack[STACK_INDEX_CALL_DEPTH].ival > max_call_depth) {
    error = env->die(env, stack, "Deep recursion occurs. The depth of a method call must be less than %d", max_call_depth, FILE_NAME, __LINE__);
  }
  else {
    // Call native method
    if (method->is_native) {
      // Enter scope
      int32_t original_mortal_stack_top = SPVM_API_enter_scope(env, stack);

      // Call native subrotuine
      int32_t (*native_address)(SPVM_ENV*, SPVM_VALUE*) = runtime->method_native_addresses[method->id];
      assert(native_address != NULL);
      error = (*native_address)(env, stack);
      
      int32_t method_return_type_is_object = SPVM_API_RUNTIME_get_type_is_object(runtime, method->return_type_id);
      
      // Increment ref count of return value
      if (!error) {
        if (method_return_type_is_object) {
          if (*(void**)&stack[0] != NULL) {
            SPVM_API_INC_REF_COUNT_ONLY(env, stack, *(void**)&stack[0]);
          }
        }
      }

      // Leave scope
      SPVM_API_leave_scope(env, stack, original_mortal_stack_top);

      // Decrement ref count of return value
      if (!error) {
        if (method_return_type_is_object) {
          if (*(void**)&stack[0] != NULL) {
            SPVM_API_DEC_REF_COUNT_ONLY(env, stack, *(void**)&stack[0]);
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
      void* method_precompile_address = runtime->method_precompile_addresses[method->id];
      if (method_precompile_address) {
        int32_t (*precompile_address)(SPVM_ENV*, SPVM_VALUE*) = method_precompile_address;
        error = (*precompile_address)(env, stack);
      }
      // Call sub virtual machine
      else {
        error = SPVM_API_VM_call_spvm_method_vm(env, stack, method_id, args_stack_length);
      }
    }
  }
  
  stack[STACK_INDEX_CALL_DEPTH].ival--;
  
  return error;
}

int32_t SPVM_API_is_type(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t basic_type_id, int32_t type_dimension) {
  
  // Object must be not null
  assert(object);
  
  if (object->basic_type_id == basic_type_id && object->type_dimension == type_dimension) {
    return 1;
  }
  else {
    return 0;
  }
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
    is_string = (object->basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && object->type_dimension == 0);
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
      int32_t object_basic_type_id = object->basic_type_id;
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
      int32_t object_basic_type_id = object->basic_type_id;
      int32_t object_basic_type_category = SPVM_API_RUNTIME_get_basic_type_category(runtime, object_basic_type_id);
      
      switch (object_basic_type_category) {
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING:
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS:
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE:
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT:
        {
          is_object_array = 1;
          break;
        }
        default: {
          is_object_array = 0;
        }
      }
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
      int32_t object_basic_type_id = object->basic_type_id;
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
      int32_t object_basic_type_id = object->basic_type_id;
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
      int32_t object_basic_type_id = object->basic_type_id;
      int32_t object_basic_type_category = SPVM_API_RUNTIME_get_basic_type_category(runtime, object_basic_type_id);
      
      switch (object_basic_type_category) {
        case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS: {
          int32_t class_id = SPVM_API_RUNTIME_get_basic_type_class_id(runtime, object_basic_type_id);
          int32_t class_is_pointer = SPVM_API_RUNTIME_get_class_is_pointer(runtime, class_id);
          
          if (class_is_pointer) {
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

int32_t SPVM_API_get_elem_byte_size(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t elem_byte_size;
  if (array) {
    if (SPVM_API_is_string(env, stack, array)) {
      elem_byte_size = 1;
    }
    else if (SPVM_API_is_object_array(env, stack, array)) {
      elem_byte_size = sizeof(void*);
    }
    else if (SPVM_API_is_numeric_array(env, stack, array)) {
      int32_t basic_type_id = array->basic_type_id;
      int32_t type_dimension = array->type_dimension;
      assert(type_dimension == 1);
      
      SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
      if (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
        elem_byte_size = 1;
      }
      else if (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
        elem_byte_size = 2;
      }
      else if (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT || basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
        elem_byte_size = 4;
      }
      else if (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG || basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
        elem_byte_size = 8;
      }
      else {
        assert(0);
      }
    }
    else if (SPVM_API_is_mulnum_array(env, stack, array)) {
      int32_t basic_type_id = array->basic_type_id;
      int32_t type_dimension = array->type_dimension;
      assert(type_dimension == 1);
      
      SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
      assert(basic_type->class_id > -1);
      SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, basic_type->class_id);
      
      int32_t fields_length = class->fields_length;
      
      SPVM_RUNTIME_FIELD* first_field = SPVM_API_RUNTIME_get_field(runtime, class->fields_base_id + 0);
      int32_t first_field_type_id = first_field->type_id;
      assert(first_field_type_id > -1);
      SPVM_RUNTIME_TYPE* first_field_type =SPVM_API_RUNTIME_get_type(runtime, first_field_type_id);
      
      int32_t field_basic_type_id = first_field_type->basic_type_id;
      
      if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
        elem_byte_size = 1 * fields_length;
      }
      else if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
        elem_byte_size = 2 * fields_length;
      }
      else if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT || field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
        elem_byte_size = 4 * fields_length;
      }
      else if (field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG || field_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
        elem_byte_size = 8 * fields_length;
      }
      else {
        assert(0);
      }
    }
  }
  else {
    elem_byte_size = 0;
  }
  
  return elem_byte_size;
}

int32_t SPVM_API_has_interface(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t interface_basic_type_id) {
  (void)env;

  SPVM_RUNTIME* runtime = env->runtime;

  // Object must be not null
  assert(object);
  
  int32_t object_type_dimension = object->type_dimension;
  int32_t has_interface;
  if (object->type_dimension > 0) {
    has_interface = 0;
  }
  else {
    int32_t object_basic_type_id = object->basic_type_id;
    has_interface = SPVM_API_RUNTIME_has_interface_by_id(runtime, object_basic_type_id, interface_basic_type_id);
  }
  
  return has_interface;
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
  
  int32_t basic_type_id = object->basic_type_id;
  int32_t type_dimension = object->type_dimension;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  const char* basic_type_name = SPVM_API_RUNTIME_get_basic_type_name(runtime, basic_type->id);
  
  int32_t length = 0;
  
  
  // Basic type
  length += strlen(basic_type_name);
  
  //[]
  length += type_dimension * 2;
  
  int32_t scope_id = env->enter_scope(env, stack);
  void* type_name_byte_array = env->new_byte_array(env, stack, length + 1);
  
  
  char* cur = SPVM_API_new_memory_stack(env, stack, length + 1);
  
  int32_t cur_index = 0;
  sprintf((char*)cur, "%s", basic_type_name);
  cur_index += strlen(basic_type_name);
  
  int32_t dim_index;
  for (dim_index = 0; dim_index < type_dimension; dim_index++) {
    sprintf((char*)(cur + cur_index), "[]");
    cur_index += 2;
  }
  
  void* sv_type_name = env->new_string_raw(env, stack, (const char*)cur, length);
  
  SPVM_API_free_memory_stack(env, stack, cur);
  
  env->leave_scope(env, stack, scope_id);
  
  return sv_type_name;
}

SPVM_OBJECT* SPVM_API_get_type_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object_in) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_get_type_name_raw(env, stack, object_in);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
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

SPVM_OBJECT* SPVM_API_new_stack_trace_raw(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* exception, int32_t method_id, int32_t line) {

  if (stack[STACK_INDEX_CALL_DEPTH].ival > 100) {
    return exception;
  }

  SPVM_RUNTIME* runtime = env->runtime;

  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  const char* method_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, method->name_id, NULL);
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, method->class_id);
  const char* class_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, class->name_id, NULL);

  int32_t module_dir_id = class->module_dir_id;
  int32_t module_rel_file_id = class->module_rel_file_id;
  
  const char* module_dir;
  const char* module_dir_sep;
  if (module_dir_id >= 0) {
    module_dir = SPVM_API_RUNTIME_get_name(runtime, module_dir_id);
    module_dir_sep = "/";
  }
  else {
    module_dir = "";
    module_dir_sep = "";
  }
  
  const char* module_rel_file = SPVM_API_RUNTIME_get_name(runtime, module_rel_file_id);
  
  // stack trace symbols
  const char* new_line_part = "\n    ";
  const char* arrow_part = "->";
  const char* at_part = " at ";

  // Exception
  const char* exception_bytes = env->get_chars(env, stack, exception);
  int32_t exception_length = env->length(env, stack, exception);
  
  // Total string length
  int32_t total_length = 0;
  total_length += exception_length;
  total_length += strlen(new_line_part);
  total_length += strlen(class_name);
  total_length += strlen(arrow_part);
  total_length += strlen(method_name);
  total_length += strlen(at_part);
  total_length += strlen(module_dir);
  total_length += strlen(module_dir_sep);
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
    class_name,
    arrow_part,
    method_name,
    at_part,
    module_dir,
    module_dir_sep,
    module_rel_file,
    line_part,
    line
  );
  
  return new_exception;
}

SPVM_OBJECT* SPVM_API_new_stack_trace(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* exception, int32_t method_id, int32_t line) {
  (void)env;
  
  SPVM_OBJECT* stack_trace = SPVM_API_new_stack_trace_raw(env, stack, exception, method_id, line);
  
  SPVM_API_push_mortal(env, stack, stack_trace);
  
  return stack_trace;
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
  (void)env;

  int32_t string1_length = SPVM_API_length(env, stack, string1);
  int32_t string2_length = SPVM_API_length(env, stack, string2);
  
  int32_t string3_length = string1_length + string2_length;
  SPVM_OBJECT* string3 = SPVM_API_new_byte_array_raw(env, stack, string3_length);

  string3->basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_STRING;
  string3->type_dimension = 0;

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
  
  SPVM_API_OBJECT_ASSIGN(env, stack, cur_excetpion_ptr, exception);
  
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

SPVM_OBJECT* SPVM_API_new_object_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_new_object_array_raw(env, stack, basic_type_id, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_string_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_new_object_array(env, stack, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING, length);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_muldim_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t element_dimension, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_new_muldim_array_raw(env, stack, basic_type_id, element_dimension, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_mulnum_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_new_mulnum_array_raw(env, stack, basic_type_id, length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_object(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_new_object_raw(env, stack, basic_type_id);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_pointer(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, void* pointer) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_new_pointer_raw(env, stack, basic_type_id, pointer);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_pointer_with_fields(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, void* pointer, int32_t fields_length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_API_new_pointer_with_fields_raw(env, stack, basic_type_id, pointer, fields_length);
  
  SPVM_API_push_mortal(env, stack, object);
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_string_nolen_raw(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes) {
  (void)env;
  
  int32_t length = strlen((char*)bytes);
  
  SPVM_OBJECT* object = SPVM_API_new_byte_array_raw(env, stack, length);
  
  object->basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_STRING;
  object->type_dimension = 0;
  
  if (bytes != NULL && length > 0) {
    memcpy((void*)((intptr_t)object + env->object_header_byte_size), (char*)bytes, length);
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

  SPVM_OBJECT* object = SPVM_API_new_byte_array_raw(env, stack, length);
  
  object->basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_STRING;
  object->type_dimension = 0;

  if (bytes != NULL && length > 0) {
    memcpy((void*)((intptr_t)object + env->object_header_byte_size), (char*)bytes, length);
  }

  return object;
}

int32_t SPVM_API_get_filed_first_int(SPVM_ENV* env, SPVM_OBJECT* object) {

  int32_t value = *(int32_t*)((intptr_t)object + env->object_header_byte_size);
  
  return value;
}

int32_t SPVM_API_get_bool_object_value(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* bool_object) {
  (void)env;

  int32_t value = SPVM_API_get_filed_first_int(env, bool_object);
  
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
  
  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + sizeof(int8_t) * ((int64_t)length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_API_new_memory_stack(env, stack, alloc_byte_size);
  if (!object) {
    return NULL;
  }

  object->type_dimension = 1;
  object->basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE;
  object->length = length;
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_short_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  (void)env;
  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + sizeof(int16_t) * ((int64_t)length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_API_new_memory_stack(env, stack, alloc_byte_size);
  if (!object) {
    return NULL;
  }
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT;
  
  // Set array length
  object->length = length;

  return object;
}

SPVM_OBJECT* SPVM_API_new_int_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  (void)env;

  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + sizeof(int32_t) * ((int64_t)length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_API_new_memory_stack(env, stack, alloc_byte_size);
  if (!object) {
    return NULL;
  }
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_INT;

  // Set array length
  object->length = length;

  return object;
}

SPVM_OBJECT* SPVM_API_new_long_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  (void)env;

  if (length < 0) {
    return NULL;
  }
  
  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + sizeof(int64_t) * ((int64_t)length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_API_new_memory_stack(env, stack, alloc_byte_size);
  if (!object) {
    return NULL;
  }
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_LONG;

  // Set array length
  object->length = length;

  return object;
}

SPVM_OBJECT* SPVM_API_new_float_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  (void)env;

  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + sizeof(float) * ((int64_t)length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_API_new_memory_stack(env, stack, alloc_byte_size);
  if (!object) {
    return NULL;
  }
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT;

  // Set array length
  object->length = length;

  return object;
}

SPVM_OBJECT* SPVM_API_new_double_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length) {
  (void)env;

  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + sizeof(double) * ((int64_t)length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_API_new_memory_stack(env, stack, alloc_byte_size);
  if (!object) {
    return NULL;
  }
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE;
  
  // Set array length
  object->length = length;

  return object;
}

SPVM_OBJECT* SPVM_API_new_object_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;

  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  if (!basic_type) {
    return NULL;
  }
  
  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + sizeof(void*) * ((int64_t)length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_API_new_memory_stack(env, stack, alloc_byte_size);
  if (!object) {
    return NULL;
  }

  for (int32_t index = 0; index < length; index++) {
    SPVM_OBJECT* get_field_object = ((SPVM_OBJECT**)((intptr_t)object + env->object_header_byte_size))[index];
  }

  object->basic_type_id = basic_type->id;
  object->type_dimension = 1;

  // Set array length
  object->length = length;
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_muldim_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t element_dimension, int32_t length) {
  (void)env;
  
  if (element_dimension < 1) {
    return NULL;
  }
  else if (basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT) {
    return NULL;
  }
  
  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + sizeof(void*) * ((int64_t)length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_API_new_memory_stack(env, stack, alloc_byte_size);
  if (!object) {
    return NULL;
  }
  
  object->basic_type_id = basic_type_id;
  object->type_dimension = element_dimension + 1;
  
  // Set array length
  object->length = length;
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_mulnum_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length) {
  (void)env;

  SPVM_RUNTIME* runtime = env->runtime;

  // valut_t array dimension must be 1
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  const char* basic_type_name = SPVM_API_RUNTIME_get_basic_type_name(runtime, basic_type->id);
  
  // Class
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, basic_type->class_id);
  int32_t fields_length = class->fields_length;
  SPVM_RUNTIME_FIELD* field_first = SPVM_API_RUNTIME_get_field(runtime, class->fields_base_id + 0);

  SPVM_RUNTIME_TYPE* first_field_type =SPVM_API_RUNTIME_get_type(runtime, field_first->type_id);

  int32_t field_basic_type_id = first_field_type->basic_type_id;

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

  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + unit_size * fields_length * ((int64_t)length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_API_new_memory_stack(env, stack, alloc_byte_size);
  if (!object) {
    return NULL;
  }

  object->basic_type_id = basic_type->id;
  object->type_dimension = 1;

  // Set array length
  object->length = length;

  return object;
}

SPVM_OBJECT* SPVM_API_new_object_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);
  
  SPVM_RUNTIME_CLASS* class;
  if (!SPVM_API_RUNTIME_get_class(runtime, basic_type->class_id)) {
    class = NULL;
  }
  else {
    class = SPVM_API_RUNTIME_get_class(runtime, basic_type->class_id);
  }
  if (!class) {
    return NULL;
  }

  // Alloc body length + 1
  int32_t fields_length = class->fields_length;

  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + class->fields_byte_size + 1;
  
  // Create object
  SPVM_OBJECT* object = SPVM_API_new_memory_stack(env, stack, alloc_byte_size);
  if (!object) {
    return NULL;
  }
  
  object->basic_type_id = basic_type->id;
  object->type_dimension = 0;

  object->length = fields_length;

  // Has destructor
  if (class->destructor_method_id >= 0) {
    object->flag |= SPVM_OBJECT_C_FLAG_HAS_DESTRUCTOR;
  }
  
  return object;
}

SPVM_OBJECT* SPVM_API_new_pointer_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, void* pointer) {
  int32_t fields_length = 0;
  return SPVM_API_new_pointer_with_fields_raw(env, stack, basic_type_id, pointer, fields_length);
}

SPVM_OBJECT* SPVM_API_new_pointer_with_fields_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, void* pointer, int32_t fields_length) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, basic_type_id);

  SPVM_RUNTIME_CLASS* class;
  if (!SPVM_API_RUNTIME_get_class(runtime, basic_type->class_id)) {
    class = NULL;
  }
  else {
    class = SPVM_API_RUNTIME_get_class(runtime, basic_type->class_id);
  }
  if (!class) {
    return NULL;
  }
  
  // First data is the pointer data. The default is NULL (oval).
  // Second data is the length of the pointer fields. The default is 0 (ival).
  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE) * (2 + fields_length);
  
  // Create object
  SPVM_OBJECT* object = SPVM_API_new_memory_stack(env, stack, alloc_byte_size);
  if (!object) {
    return NULL;
  }
  
  *(void**)((intptr_t)object + (intptr_t)env->object_header_byte_size) = pointer;
  *(int32_t*)((intptr_t)object + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE)) = fields_length;

  object->basic_type_id = basic_type->id;
  object->type_dimension = 0;

  object->length = 0;

  // Has destructor
  if (SPVM_API_RUNTIME_get_method(runtime, class->destructor_method_id)) {
    object->flag |= SPVM_OBJECT_C_FLAG_HAS_DESTRUCTOR;
  }
  
  return object;
}

int32_t SPVM_API_get_object_basic_type_id(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  return object->basic_type_id;
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

  return (int8_t*)((intptr_t)object + env->object_header_byte_size);
}

const char* SPVM_API_get_chars(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string) {
  (void)env;

  return (const char*)((intptr_t)string + env->object_header_byte_size);
}

int16_t* SPVM_API_get_elems_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  return (int16_t*)((intptr_t)object + env->object_header_byte_size);
}

int32_t* SPVM_API_get_elems_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  return (int32_t*)((intptr_t)object + env->object_header_byte_size);
}

int64_t* SPVM_API_get_elems_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  return (int64_t*)((intptr_t)object + env->object_header_byte_size);
}

float* SPVM_API_get_elems_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  return (float*)((intptr_t)object + env->object_header_byte_size);
}

double* SPVM_API_get_elems_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  return (double*)((intptr_t)object + env->object_header_byte_size);
}

SPVM_OBJECT* SPVM_API_get_elem_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t index) {
  (void)env;
  
  SPVM_OBJECT* object_maybe_weaken = ((SPVM_OBJECT**)((intptr_t)array + env->object_header_byte_size))[index];
  SPVM_OBJECT* object = SPVM_API_GET_OBJECT_NO_WEAKEN_ADDRESS(env, stack, object_maybe_weaken);
  
  return object;
}

void SPVM_API_set_elem_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t index, SPVM_OBJECT* oval) {
  (void)env;
  
  void* object_address = &((void**)((intptr_t)array + env->object_header_byte_size))[index];
  
  SPVM_API_OBJECT_ASSIGN(env, stack, object_address, oval);
}

void* SPVM_API_get_pointer(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  return *(void**)((intptr_t)object + (intptr_t)env->object_header_byte_size);
}

void SPVM_API_set_pointer(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, void* ptr) {
  (void)env;
  
  *(void**)((intptr_t)object + (intptr_t)env->object_header_byte_size) = ptr;
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
        SPVM_OBJECT** get_field_object_address = &(((SPVM_OBJECT**)((intptr_t)object + env->object_header_byte_size))[index]);

        if (*get_field_object_address != NULL) {
          SPVM_API_dec_ref_count(env, stack, *get_field_object_address);
        }
      }
    }
    // Free object
    else {
      int32_t object_basic_type_id = object->basic_type_id;
      int32_t object_basic_type_category = SPVM_API_RUNTIME_get_basic_type_category(runtime, object_basic_type_id);
      if (object_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS) {
        // Class
        SPVM_RUNTIME* runtime = env->runtime;
        SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, object->basic_type_id);
        SPVM_RUNTIME_CLASS* class;
        if (!SPVM_API_RUNTIME_get_class(runtime, basic_type->class_id)) {
          class = NULL;
        }
        else {
          class = SPVM_API_RUNTIME_get_class(runtime, basic_type->class_id);
        }
        
        int32_t is_pointer = 0;
        if (class) {
          if (class->is_pointer) {
            is_pointer = 1;
          }
        }
        
        // Call destructor
        if (object->flag & SPVM_OBJECT_C_FLAG_HAS_DESTRUCTOR) {
          int32_t args_stack_length = 1;
          SPVM_VALUE save_stack0 = stack[0];
          stack[0].oval = object;
          int32_t error = SPVM_API_call_spvm_method(env, stack, class->destructor_method_id, args_stack_length);
          
          // Exception in destructor is changed to warning
          if (error) {
            void* exception = env->get_exception(env, stack);
            const char* exception_chars = env->get_chars(env, stack, exception);
            fprintf(stderr, "(An exception thrown in the DESTROY method is converted to a warning)%s\n", exception_chars);
          }
          
          stack[0] = save_stack0;
          
          assert(object->ref_count > 0);
        }
        
        // Free object fields
        int32_t object_fields_base = SPVM_API_RUNTIME_get_class_fields_base_id(runtime, class->id);
        int32_t object_fields_length = SPVM_API_RUNTIME_get_class_fields_length(runtime, class->id);
        for (int32_t field_id = object_fields_base; field_id < object_fields_base + object_fields_length; field_id++) {
          int32_t field_type_id = SPVM_API_RUNTIME_get_field_type_id(runtime, field_id);
          int32_t field_type_is_object = SPVM_API_RUNTIME_get_type_is_object(runtime, field_type_id);
          SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
          if (field_type_is_object) {
            SPVM_OBJECT** get_field_object_address = (SPVM_OBJECT**)((intptr_t)object + (intptr_t)env->object_header_byte_size + field->offset);
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

int32_t SPVM_API_get_basic_type_id(SPVM_ENV* env, const char* basic_type_name) {
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

int32_t SPVM_API_get_class_id(SPVM_ENV* env, const char* class_name) {
  (void)env;

  SPVM_RUNTIME* runtime = env->runtime;

  if (class_name == NULL) {
    return -1;
  }

  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class_by_name(runtime, class_name);
  if (class) {
    int32_t class_id = class->id;
    return class_id;
  }
  else {
    return -1;
  }
}

int32_t SPVM_API_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  return object->ref_count;
}

int32_t SPVM_API_get_field_offset(SPVM_ENV* env, int32_t field_id) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
  
  return field->offset;
}

int32_t SPVM_API_get_field_id(SPVM_ENV* env, const char* class_name, const char* field_name) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Basic type
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type_by_name(runtime, class_name);
  if (!basic_type) {
    return -1;
  }
  
  if (!SPVM_API_RUNTIME_get_class(runtime, basic_type->class_id)) {
    return -1;
  }
  
  // Class
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, basic_type->class_id);
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_class_id_and_field_name(runtime, class->id, field_name);
  if (!field) {
    return -1;
  }
  
  int32_t field_id = field->id;
  
  return field_id;
}

int32_t SPVM_API_get_field_id_invocant(SPVM_ENV* env, SPVM_OBJECT* object, const char* field_name) {
  (void)env;
  
  // Method ID
  int32_t field_id = -1;
  
  // Compiler
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (!object) {
    return -1;
  }
  
  // Basic type
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, object->basic_type_id);

  // Type dimension
  if (object->type_dimension != 0) {
    return -1;
  }

  // Class
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, basic_type->class_id);
  
  SPVM_RUNTIME_CLASS* parent_class = class;
  
  while (1) {
    if (!parent_class) {
      break;
    }
    
    // Method
    SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_class_id_and_field_name(runtime, parent_class->id, field_name);
    if (field) {
      field_id = field->id;
      break;
    }
    
    if (parent_class->parent_class_id != -1) {
      parent_class = SPVM_API_RUNTIME_get_class(runtime, parent_class->parent_class_id);
    }
    else {
      parent_class = NULL;
    }
  }
  
  return field_id;
}

int32_t SPVM_API_get_class_var_id(SPVM_ENV* env, const char* class_name, const char* class_var_name) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Basic type
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type_by_name(runtime, class_name);
  
  // Class name
  SPVM_RUNTIME_CLASS* class;
  if (!basic_type) {
    return -1;
  }
  else if (!SPVM_API_RUNTIME_get_class(runtime, basic_type->class_id)) {
    return -1;
  }
  else {
    class = SPVM_API_RUNTIME_get_class(runtime, basic_type->class_id);
  }
  
  // Class variable name
  SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_class_id_and_class_var_name(runtime, class->id, class_var_name);
  if (!class_var) {
    return -1;
  }
  
  return class_var->id;
}

int32_t SPVM_API_get_class_method_id(SPVM_ENV* env, const char* class_name, const char* method_name) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Method ID
  int32_t method_id = -1;
  
  // Basic type
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type_by_name(runtime, class_name);
  if (basic_type) {
    
    // Class
    SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, basic_type->class_id);
    if (class) {

      // Method
      SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method_by_class_id_and_method_name(runtime, class->id, method_name);
      
      if (method) {
        // Class method
        if (method->is_class_method) {
          method_id = method->id;
        }
      }
    }
  }
  
  return method_id;
}

int32_t SPVM_API_get_instance_method_id_static(SPVM_ENV* env, const char* class_name, const char* method_name) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Method ID
  int32_t method_id = -1;
  
  // Basic type
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type_by_name(runtime, class_name);
  if (basic_type) {
    
    // Class
    SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, basic_type->class_id);
    if (class) {

      // Method
      SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method_by_class_id_and_method_name(runtime, class->id, method_name);
      if (method) {
        // Instance method
        if (!method->is_class_method) {
          method_id = method->id;
        }
      }
    }
  }
  
  return method_id;
}


int32_t SPVM_API_get_instance_method_id(SPVM_ENV* env, SPVM_OBJECT* object, const char* method_name) {
  (void)env;
  
  // Method ID
  int32_t method_id = -1;
  
  // Compiler
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (!object) {
    return -1;
  }
  
  // Basic type
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, object->basic_type_id);
  
  // Class
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, basic_type->class_id);
  
  SPVM_RUNTIME_CLASS* parent_class = class;
  
  while (1) {
    if (!parent_class) {
      break;
    }
    
    // Method
    SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method_by_class_id_and_method_name(runtime, parent_class->id, method_name);
    if (method) {
      // Instance method
      if (!method->is_class_method) {
        method_id = method->id;
      }
      break;
    }
    
    if (parent_class->parent_class_id != -1) {
      parent_class = SPVM_API_RUNTIME_get_class(runtime, parent_class->parent_class_id);
    }
    else {
      parent_class = NULL;
    }
  }
  
  return method_id;
}

int8_t SPVM_API_get_field_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
  
  // Get field value
  int8_t value = *(int8_t*)((intptr_t)object + env->object_header_byte_size + field->offset);

  return value;
}

int16_t SPVM_API_get_field_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
  
  // Get field value
  int16_t value = *(int16_t*)((intptr_t)object + env->object_header_byte_size + field->offset);
  
  return value;
}

int32_t SPVM_API_get_field_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);

  // Get field value
  int32_t value = *(int32_t*)((intptr_t)object + env->object_header_byte_size + field->offset);
  
  return value;
}

int64_t SPVM_API_get_field_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);

  // Get field value
  int64_t value = *(int64_t*)((intptr_t)object + env->object_header_byte_size + field->offset);
  
  return value;
}

float SPVM_API_get_field_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);

  // Get field value
  float value = *(float*)((intptr_t)object + env->object_header_byte_size + field->offset);
  
  return value;
}

double SPVM_API_get_field_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);

  // Get field value
  double value = *(double*)((intptr_t)object + env->object_header_byte_size + field->offset);
  
  return value;
}

SPVM_OBJECT* SPVM_API_get_field_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
  
  // Get field value
  SPVM_OBJECT* value_maybe_weaken = *(SPVM_OBJECT**)((intptr_t)object + env->object_header_byte_size + field->offset);
  SPVM_OBJECT* value = SPVM_API_GET_OBJECT_NO_WEAKEN_ADDRESS(env, stack, value_maybe_weaken);
  
  return value;
}

void SPVM_API_set_field_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_id, int8_t value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);

  // Get field value
  *(int8_t*)((intptr_t)object + env->object_header_byte_size + field->offset) = value;
}

void SPVM_API_set_field_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_id, int16_t value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);

  // Get field value
  *(int16_t*)((intptr_t)object + env->object_header_byte_size + field->offset) = value;
}

void SPVM_API_set_field_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_id, int32_t value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);

  // Get field value
  *(int32_t*)((intptr_t)object + env->object_header_byte_size + field->offset) = value;
}

void SPVM_API_set_field_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_id, int64_t value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);

  // Get field value
  *(int64_t*)((intptr_t)object + env->object_header_byte_size + field->offset) = value;
}

void SPVM_API_set_field_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_id, float value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);

  // Get field value
  *(float*)((intptr_t)object + env->object_header_byte_size + field->offset) = value;
}

void SPVM_API_set_field_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_id, double value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);

  // Get field value
  *(double*)((intptr_t)object + env->object_header_byte_size + field->offset) = value;
}

void SPVM_API_set_field_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_id, SPVM_OBJECT* value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
  
  // Get field value
  void* get_field_object_address = (void**)((intptr_t)object + env->object_header_byte_size + field->offset);

  SPVM_API_OBJECT_ASSIGN(env, stack, get_field_object_address, value);
}

void* SPVM_API_new_memory_env(SPVM_ENV* env, size_t byte_size) {

  assert(byte_size > 0);

  if ((uint64_t)byte_size > (uint64_t)SIZE_MAX) {
    return NULL;
  }
  
  void* block = SPVM_ALLOCATOR_alloc_memory_block_tmp(env->allocator, (size_t)byte_size);
  
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

void* SPVM_API_new_memory_stack(SPVM_ENV* env, SPVM_VALUE* stack, size_t byte_size) {
  
  assert(byte_size > 0);
  
  if ((uint64_t)byte_size > (uint64_t)SIZE_MAX) {
    return NULL;
  }
  
  void* block = SPVM_ALLOCATOR_alloc_memory_block_tmp(env->allocator, (size_t)byte_size);
  
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

int8_t SPVM_API_get_class_var_byte(SPVM_ENV* env, SPVM_VALUE* stack, int32_t packagke_var_id) {

  // Get field value
  int8_t value = ((SPVM_VALUE*)(env->class_vars_heap))[packagke_var_id].bval;

  return value;
}

int16_t SPVM_API_get_class_var_short(SPVM_ENV* env, SPVM_VALUE* stack, int32_t packagke_var_id) {

  // Get field value
  int16_t value = ((SPVM_VALUE*)(env->class_vars_heap))[packagke_var_id].sval;

  return value;
}

int32_t SPVM_API_get_class_var_int(SPVM_ENV* env, SPVM_VALUE* stack, int32_t packagke_var_id) {

  // Get field value
  int32_t value = ((SPVM_VALUE*)(env->class_vars_heap))[packagke_var_id].ival;

  return value;
}

int64_t SPVM_API_get_class_var_long(SPVM_ENV* env, SPVM_VALUE* stack, int32_t packagke_var_id) {

  // Get field value
  int64_t value = ((SPVM_VALUE*)(env->class_vars_heap))[packagke_var_id].lval;

  return value;
}

float SPVM_API_get_class_var_float(SPVM_ENV* env, SPVM_VALUE* stack, int32_t packagke_var_id) {

  // Get field value
  float value = ((SPVM_VALUE*)(env->class_vars_heap))[packagke_var_id].fval;

  return value;
}

double SPVM_API_get_class_var_double(SPVM_ENV* env, SPVM_VALUE* stack, int32_t packagke_var_id) {

  // Get field value
  double value = ((SPVM_VALUE*)(env->class_vars_heap))[packagke_var_id].dval;

  return value;
}

SPVM_OBJECT* SPVM_API_get_class_var_object(SPVM_ENV* env, SPVM_VALUE* stack, int32_t packagke_var_id) {

  // Get field value
  SPVM_OBJECT* value_maybe_weaken = (SPVM_OBJECT*)((SPVM_VALUE*)(env->class_vars_heap))[packagke_var_id].oval;
  SPVM_OBJECT* value = SPVM_API_GET_OBJECT_NO_WEAKEN_ADDRESS(env, stack, value_maybe_weaken);
  
  return value;
}

void SPVM_API_set_class_var_byte(SPVM_ENV* env, SPVM_VALUE* stack, int32_t packagke_var_id, int8_t value) {
  
  // Get field value
  ((SPVM_VALUE*)(env->class_vars_heap))[packagke_var_id].bval = value;
}

void SPVM_API_set_class_var_short(SPVM_ENV* env, SPVM_VALUE* stack, int32_t packagke_var_id, int16_t value) {

  // Get field value
  ((SPVM_VALUE*)(env->class_vars_heap))[packagke_var_id].sval = value;
}

void SPVM_API_set_class_var_int(SPVM_ENV* env, SPVM_VALUE* stack, int32_t packagke_var_id, int32_t value) {

  // Get field value
  ((SPVM_VALUE*)(env->class_vars_heap))[packagke_var_id].ival = value;
}

void SPVM_API_set_class_var_long(SPVM_ENV* env, SPVM_VALUE* stack, int32_t packagke_var_id, int64_t value) {

  // Get field value
  ((SPVM_VALUE*)(env->class_vars_heap))[packagke_var_id].lval = value;
}

void SPVM_API_set_class_var_float(SPVM_ENV* env, SPVM_VALUE* stack, int32_t packagke_var_id, float value) {

  // Get field value
  ((SPVM_VALUE*)(env->class_vars_heap))[packagke_var_id].fval = value;
}

void SPVM_API_set_class_var_double(SPVM_ENV* env, SPVM_VALUE* stack, int32_t packagke_var_id, double value) {

  // Get field value
  ((SPVM_VALUE*)(env->class_vars_heap))[packagke_var_id].dval = value;
}

void SPVM_API_set_class_var_object(SPVM_ENV* env, SPVM_VALUE* stack, int32_t packagke_var_id, SPVM_OBJECT* value) {

  // Get field value
  void* get_field_object_address = &((SPVM_VALUE*)(env->class_vars_heap))[packagke_var_id].oval;
  SPVM_API_OBJECT_ASSIGN(env, stack, get_field_object_address, value);
}


SPVM_OBJECT* SPVM_API_new_array_proto_raw(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t length) {

  if (array == NULL) {
    return NULL;
  }
  
  if (length < 0) {
    return NULL;
  }
  
  int32_t element_byte_size = env->get_elem_byte_size(env, stack, array);
  

  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + element_byte_size * ((int64_t)length + 1);
  
  // Create object
  SPVM_OBJECT* new_array = SPVM_API_new_memory_stack(env, stack, (size_t)alloc_byte_size);
  if (!new_array) {
    return NULL;
  }

  new_array->basic_type_id = array->basic_type_id;
  new_array->type_dimension = array->type_dimension;
  new_array->length = length;
  
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
    
    int32_t element_byte_size = env->get_elem_byte_size(env, stack, object);
    
    memcpy(new_object_bytes, object_bytes, element_byte_size * length);
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

void SPVM_API_call_init_blocks(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Call INIT blocks
  int32_t classes_length = runtime->classes_length;
  for (int32_t class_id = 0; class_id < classes_length; class_id++) {
    SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, class_id);
    if (class->has_init_block) {
      SPVM_RUNTIME_METHOD* init_method = SPVM_API_RUNTIME_get_method_by_class_id_and_method_name(runtime, class->id, "INIT");
      assert(init_method);
      int32_t args_stack_length = 0;
      env->call_spvm_method(env, stack, init_method->id, args_stack_length);
    }
  }
}

int32_t SPVM_API_set_command_info_program_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* obj_program_name) {
  (void)env;
  
  int32_t e;
  
  if (obj_program_name && !(obj_program_name->basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && obj_program_name->type_dimension == 0)) {
    return env->die(env, stack, "The type of the program name must be the string type", __FILE__, __LINE__);
  }
  
  env->set_class_var_object_by_name(env, stack, "CommandInfo", "$PROGRAM_NAME", obj_program_name, &e, __FILE__, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPVM_API_set_command_info_argv(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* obj_argv) {
  (void)env;
  
  int32_t e;
  
  if (obj_argv && !(obj_argv->basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && obj_argv->type_dimension == 1)) {
    return env->die(env, stack, "The type of the argv must be the string[] type", __FILE__, __LINE__);
  }
  
  env->set_class_var_object_by_name(env, stack, "CommandInfo", "$ARGV", obj_argv, &e, __FILE__, __LINE__);
  if (e) { return e; }
  
  return 0;
}

SPVM_ENV* SPVM_API_new_env(SPVM_ENV* env) {
  (void)env;
  
  // New raw env
  SPVM_ENV* new_env = SPVM_API_new_env_raw(NULL);
  
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
  SPVM_API_RUNTIME_free_runtime(runtime);
  env->runtime = NULL;
  
  // Free env
  env->free_env_raw(env);
}

int32_t SPVM_API_elem_isa(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, SPVM_OBJECT* element) {
  
  SPVM_RUNTIME* runtime = env->runtime;

  assert(array);

  int32_t array_basic_type_id = array->basic_type_id;
  int32_t array_type_dimension = array->type_dimension;
  
  assert(array_type_dimension > 0);
  int32_t runtime_assignability = SPVM_API_isa(env, stack, element, array_basic_type_id, array_type_dimension - 1);

  return runtime_assignability;
}

int32_t SPVM_API_isa(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t dist_basic_type_id, int32_t dist_type_dimension) {
  
  SPVM_RUNTIME* runtime = env->runtime;

  int32_t isa;
  if (object == NULL) {
    isa = 1;
  }
  else {
    int32_t dist_basic_type_category = SPVM_API_RUNTIME_get_basic_type_category(runtime, dist_basic_type_id);
    int32_t object_basic_type_id = object->basic_type_id;
    int32_t object_type_dimension = object->type_dimension;
    int32_t object_basic_type_category = SPVM_API_RUNTIME_get_basic_type_category(runtime, object_basic_type_id);
    
    if (dist_basic_type_id == object_basic_type_id && dist_type_dimension == object_type_dimension) {
      isa = 1;
    }
    else if (dist_type_dimension == 0 && dist_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT) {
      assert(object_type_dimension >= 0);
      isa = 1;
    }
    else if (dist_type_dimension == 1 && dist_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT) {
      if (object_type_dimension >= 1) {
        isa = 1;
      }
      else {
        isa = 0;
      }
    }
    else if (dist_type_dimension == object_type_dimension) {
      if (dist_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE) {
        isa = SPVM_API_RUNTIME_has_interface_by_id(runtime, object_basic_type_id, dist_basic_type_id);
      }
      else if (dist_basic_type_category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS) {
        isa = SPVM_API_RUNTIME_is_super_class_by_id(runtime, dist_basic_type_id, object_basic_type_id);
      }
      else {
        isa = 0;
      }
    }
    else {
      isa = 0;
    }
  }
  
  return isa;
}

int32_t SPVM_API_get_class_id_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t class_id = env->get_class_id(env, class_name);
  if (class_id < 0) {
    *error = 1;
    env->die(env, stack, "The class \"%s\" is not loaded", class_name, file, line);
  };
  return class_id;
}

int32_t SPVM_API_get_basic_type_id_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error, const char* file, int32_t line) {
  *error = 0;
  
  int32_t basic_type_id = env->get_basic_type_id(env, basic_type_name);
  if (basic_type_id < 0) {
    *error = 1;
    env->die(env, stack, "The basic_type \"%s\" is not loaded", basic_type_name, file, line);
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

int32_t SPVM_API_get_args_stack_length(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  int32_t args_length = stack[STACK_INDEX_ARGS_LENGTH].ival;
  
  return args_length;
}

void SPVM_API_set_args_stack_length(SPVM_ENV* env, SPVM_VALUE* stack, int32_t args_length) {
  (void)env;
  
  stack[STACK_INDEX_ARGS_LENGTH].ival = args_length;
}

int32_t SPVM_API_get_pointer_fields_length(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  
  // Get fields length
  int32_t fields_length = *(int32_t*)((intptr_t)object + env->object_header_byte_size + sizeof(SPVM_VALUE));
  
  return fields_length;
}

int8_t SPVM_API_get_pointer_field_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index) {

  // Get field value
  int8_t value = *(int8_t*)((intptr_t)object + env->object_header_byte_size + sizeof(SPVM_VALUE) * (2 + field_index));

  return value;
}

int16_t SPVM_API_get_pointer_field_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index) {

  // Get field value
  int16_t value = *(int16_t*)((intptr_t)object + env->object_header_byte_size + sizeof(SPVM_VALUE) * (2 + field_index));
  
  return value;
}

int32_t SPVM_API_get_pointer_field_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index) {

  // Get field value
  int32_t value = *(int32_t*)((intptr_t)object + env->object_header_byte_size + sizeof(SPVM_VALUE) * (2 + field_index));
  
  return value;
}

int64_t SPVM_API_get_pointer_field_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index) {

  // Get field value
  int64_t value = *(int64_t*)((intptr_t)object + env->object_header_byte_size + sizeof(SPVM_VALUE) * (2 + field_index));
  
  return value;
}

float SPVM_API_get_pointer_field_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index) {

  // Get field value
  float value = *(float*)((intptr_t)object + env->object_header_byte_size + sizeof(SPVM_VALUE) * (2 + field_index));
  
  return value;
}

double SPVM_API_get_pointer_field_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index) {

  // Get field value
  double value = *(double*)((intptr_t)object + env->object_header_byte_size + sizeof(SPVM_VALUE) * (2 + field_index));
  
  return value;
}

void* SPVM_API_get_pointer_field_pointer(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index) {

  // Get field value
  void* value = *(void**)((intptr_t)object + env->object_header_byte_size + sizeof(SPVM_VALUE) * (2 + field_index));
  
  return value;
}

void SPVM_API_set_pointer_field_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, int8_t value) {

  // Get field value
  *(int8_t*)((intptr_t)object + env->object_header_byte_size + sizeof(SPVM_VALUE) * (2 + field_index)) = value;
}

void SPVM_API_set_pointer_field_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, int16_t value) {

  // Get field value
  *(int16_t*)((intptr_t)object + env->object_header_byte_size + sizeof(SPVM_VALUE) * (2 + field_index)) = value;
}

void SPVM_API_set_pointer_field_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, int32_t value) {

  // Get field value
  *(int32_t*)((intptr_t)object + env->object_header_byte_size + sizeof(SPVM_VALUE) * (2 + field_index)) = value;
}

void SPVM_API_set_pointer_field_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, int64_t value) {

  // Get field value
  *(int64_t*)((intptr_t)object + env->object_header_byte_size + sizeof(SPVM_VALUE) * (2 + field_index)) = value;
}

void SPVM_API_set_pointer_field_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, float value) {

  // Get field value
  *(float*)((intptr_t)object + env->object_header_byte_size + sizeof(SPVM_VALUE) * (2 + field_index)) = value;
}

void SPVM_API_set_pointer_field_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, double value) {

  // Get field value
  *(double*)((intptr_t)object + env->object_header_byte_size + sizeof(SPVM_VALUE) * (2 + field_index)) = value;
}

void SPVM_API_set_pointer_field_pointer(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, void* value) {

  // Get field value
  *(void**)((intptr_t)object + env->object_header_byte_size + sizeof(SPVM_VALUE) * (2 + field_index)) = value;
}

int32_t SPVM_API_get_pointer_no_need_free(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  int32_t flag = object->flag & SPVM_OBJECT_C_FLAG_POINTER_NO_NEED_FREE;
  
  return flag;
}

void SPVM_API_set_pointer_no_need_free(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t flag) {
  (void)env;
  
  if (flag) {
    object->flag |= SPVM_OBJECT_C_FLAG_POINTER_NO_NEED_FREE;
  }
  else {
    object->flag &= ~SPVM_OBJECT_C_FLAG_POINTER_NO_NEED_FREE;
  }
}

int32_t SPVM_API_get_pointer_length(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object) {
  (void)env;
  
  int32_t length = object->length;
  
  return length;
}

void SPVM_API_set_pointer_length(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t length) {
  (void)env;
  
  object->length = length;
}
