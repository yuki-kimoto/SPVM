#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>

#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_object.h"
#include "spvm_native.h"

#include "spvm_list.h"
#include "spvm_hash.h"

#include "spvm_opcode.h"

#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_package.h"
#include "spvm_runtime_sub.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_package_var.h"
#include "spvm_runtime_arg.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_weaken_backref.h"
#include "spvm_portable.h"

// Only use constant
#include "spvm_package.h"
#include "spvm_basic_type.h"
#include "spvm_type.h"
#include "spvm_sub.h"
#include "spvm_limit.h"











SPVM_ENV* SPVM_RUNTIME_API_create_env(SPVM_RUNTIME* runtime) {

  void* env_init[]  = {
    NULL, // exception_object
    NULL, // native_mortal_stack
    NULL, // native_mortal_stack_top
    NULL, // native_mortal_stack_capacity
    runtime,
    (void*)(intptr_t)offsetof(SPVM_RUNTIME, package_vars_heap), // runtime_package_vars_heap_offset
    (void*)(intptr_t)sizeof(SPVM_OBJECT), // object_header_byte_size
    (void*)(intptr_t)offsetof(SPVM_OBJECT, ref_count), // object_ref_count_offset
    (void*)(intptr_t)offsetof(SPVM_OBJECT, basic_type_id), // object_basic_type_id_offset
    (void*)(intptr_t)offsetof(SPVM_OBJECT, type_dimension), // object_dimension_offset
    (void*)(intptr_t)offsetof(SPVM_OBJECT, array_length), // object_array_length_offset
    (void*)(intptr_t)SPVM_BASIC_TYPE_C_ID_BYTE_OBJECT, // byte_object_basic_type_id
    (void*)(intptr_t)SPVM_BASIC_TYPE_C_ID_SHORT_OBJECT, // short_object_basic_type_id
    (void*)(intptr_t)SPVM_BASIC_TYPE_C_ID_INT_OBJECT, // int_object_basic_type_id
    (void*)(intptr_t)SPVM_BASIC_TYPE_C_ID_LONG_OBJECT,  // long_object_basic_type_id
    (void*)(intptr_t)SPVM_BASIC_TYPE_C_ID_FLOAT_OBJECT, // float_object_basic_type_id
    (void*)(intptr_t)SPVM_BASIC_TYPE_C_ID_DOUBLE_OBJECT, // double_object_basic_type_id
    SPVM_RUNTIME_API_memory_blocks_count,
    SPVM_RUNTIME_API_new_env,
    SPVM_RUNTIME_API_free_env,
    SPVM_RUNTIME_API_exception,
    SPVM_RUNTIME_API_set_exception,
    SPVM_RUNTIME_API_sub_id,
    SPVM_RUNTIME_API_method_sub_id,
    SPVM_RUNTIME_API_basic_type_id,
    SPVM_RUNTIME_API_pkgvar_id,
    SPVM_RUNTIME_API_field_offset,
    SPVM_RUNTIME_API_call_sub,
    SPVM_RUNTIME_API_is_type,
    SPVM_RUNTIME_API_has_interface,
    SPVM_RUNTIME_API_new_obj_raw,
    SPVM_RUNTIME_API_new_obj,
    SPVM_RUNTIME_API_new_barray_raw,
    SPVM_RUNTIME_API_new_barray,
    SPVM_RUNTIME_API_new_sarray_raw,
    SPVM_RUNTIME_API_new_sarray,
    SPVM_RUNTIME_API_new_iarray_raw,
    SPVM_RUNTIME_API_new_iarray,
    SPVM_RUNTIME_API_new_larray_raw,
    SPVM_RUNTIME_API_new_larray,
    SPVM_RUNTIME_API_new_farray_raw,
    SPVM_RUNTIME_API_new_farray,
    SPVM_RUNTIME_API_new_darray_raw,
    SPVM_RUNTIME_API_new_darray,
    SPVM_RUNTIME_API_new_oarray_raw,
    SPVM_RUNTIME_API_new_oarray,
    SPVM_RUNTIME_API_new_marray_raw,
    SPVM_RUNTIME_API_new_marray,
    SPVM_RUNTIME_API_new_varray_raw,
    SPVM_RUNTIME_API_new_varray,
    SPVM_RUNTIME_API_new_str_raw,
    SPVM_RUNTIME_API_new_str,
    SPVM_RUNTIME_API_new_pointer_raw,
    SPVM_RUNTIME_API_new_pointer,
    SPVM_RUNTIME_API_concat_raw,
    SPVM_RUNTIME_API_concat,
    SPVM_RUNTIME_API_i_to_str,
    SPVM_RUNTIME_API_i_to_str,
    SPVM_RUNTIME_API_l_to_str,
    SPVM_RUNTIME_API_l_to_str,
    SPVM_RUNTIME_API_f_to_str,
    SPVM_RUNTIME_API_f_to_str,
    SPVM_RUNTIME_API_d_to_str,
    SPVM_RUNTIME_API_d_to_str,
    SPVM_RUNTIME_API_new_stack_trace_raw,
    SPVM_RUNTIME_API_new_stack_trace,
    SPVM_RUNTIME_API_len,
    SPVM_RUNTIME_API_belems,
    SPVM_RUNTIME_API_selems,
    SPVM_RUNTIME_API_ielems,
    SPVM_RUNTIME_API_lelems,
    SPVM_RUNTIME_API_felems,
    SPVM_RUNTIME_API_delems,
    SPVM_RUNTIME_API_oelems,
    SPVM_RUNTIME_API_set_oelems,
    SPVM_RUNTIME_API_field_id,
    SPVM_RUNTIME_API_bfield,
    SPVM_RUNTIME_API_sfield,
    SPVM_RUNTIME_API_ifield,
    SPVM_RUNTIME_API_lfield,
    SPVM_RUNTIME_API_ffield,
    SPVM_RUNTIME_API_dfield,
    SPVM_RUNTIME_API_ofield,
    SPVM_RUNTIME_API_set_bfield,
    SPVM_RUNTIME_API_set_sfield,
    SPVM_RUNTIME_API_set_ifield,
    SPVM_RUNTIME_API_set_lfield,
    SPVM_RUNTIME_API_set_ffield,
    SPVM_RUNTIME_API_set_dfield,
    SPVM_RUNTIME_API_set_ofield,
    SPVM_RUNTIME_API_bpkgvar,
    SPVM_RUNTIME_API_spkgvar,
    SPVM_RUNTIME_API_ipkgvar,
    SPVM_RUNTIME_API_lpkgvar,
    SPVM_RUNTIME_API_fpkgvar,
    SPVM_RUNTIME_API_dpkgvar,
    SPVM_RUNTIME_API_opkgvar,
    SPVM_RUNTIME_API_set_bpkgvar,
    SPVM_RUNTIME_API_set_spkgvar,
    SPVM_RUNTIME_API_set_ipkgvar,
    SPVM_RUNTIME_API_set_lpkgvar,
    SPVM_RUNTIME_API_set_fpkgvar,
    SPVM_RUNTIME_API_set_dpkgvar,
    SPVM_RUNTIME_API_set_opkgvar,
    SPVM_RUNTIME_API_pointer,
    SPVM_RUNTIME_API_weaken,
    SPVM_RUNTIME_API_isweak,
    SPVM_RUNTIME_API_unweaken,
    SPVM_RUNTIME_API_ref_count,
    SPVM_RUNTIME_API_inc_ref_count,
    SPVM_RUNTIME_API_dec_ref_count,
    SPVM_RUNTIME_API_enter_scope,
    SPVM_RUNTIME_API_push_mortal,
    SPVM_RUNTIME_API_leave_scope,
    SPVM_RUNTIME_API_type_name_raw,
    SPVM_RUNTIME_API_type_name,
  };
  
  int32_t env_length = 255;
  SPVM_ENV* env = SPVM_RUNTIME_API_safe_malloc_zero(sizeof(void*) * env_length);
  memcpy(&env[0], &env_init[0], sizeof(void*) * env_length);

  // Mortal stack
  env->native_mortal_stack_capacity = (void*)(intptr_t)1;
  env->native_mortal_stack = (void*)SPVM_RUNTIME_API_alloc_memory_block_zero(env, sizeof(SPVM_OBJECT*) * (intptr_t)env->native_mortal_stack_capacity);

  // Adjust alignment SPVM_VALUE
  int32_t object_header_byte_size = sizeof(SPVM_OBJECT);
  if (object_header_byte_size % sizeof(SPVM_VALUE) != 0) {
    object_header_byte_size += (sizeof(SPVM_VALUE) - object_header_byte_size % sizeof(SPVM_VALUE));
  }
  assert(object_header_byte_size % sizeof(SPVM_VALUE) == 0);
  
  // Object header byte size
  env->object_header_byte_size = (void*)(intptr_t)object_header_byte_size;
  
  return env;
}

SPVM_OBJECT* SPVM_RUNTIME_API_i_to_str_raw(SPVM_ENV* env, int32_t value) {
  char string_convert_buffer[21];

  sprintf(string_convert_buffer, "%" PRId32, value);
  int32_t string_length = strlen(string_convert_buffer);
  void* string = env->new_str_raw(env, string_convert_buffer, string_length);
  
  return string;
}

SPVM_OBJECT* SPVM_RUNTIME_API_i_to_str(SPVM_ENV* env, int32_t value) {
  (void)env;
  
  SPVM_OBJECT* str = SPVM_RUNTIME_API_i_to_str_raw(env, value);
  
  SPVM_RUNTIME_API_push_mortal(env, str);
  
  return str;
}

SPVM_OBJECT* SPVM_RUNTIME_API_l_to_str_raw(SPVM_ENV* env, int64_t value) {
  char string_convert_buffer[21];

  sprintf(string_convert_buffer, "%" PRId64, value);
  int32_t string_length = strlen(string_convert_buffer);
  void* string = env->new_str_raw(env, string_convert_buffer, string_length);
  
  return string;
}

SPVM_OBJECT* SPVM_RUNTIME_API_l_to_str(SPVM_ENV* env, int64_t value) {
  (void)env;
  
  SPVM_OBJECT* str = SPVM_RUNTIME_API_l_to_str_raw(env, value);
  
  SPVM_RUNTIME_API_push_mortal(env, str);
  
  return str;
}

SPVM_OBJECT* SPVM_RUNTIME_API_f_to_str_raw(SPVM_ENV* env, float value) {
  char string_convert_buffer[21];

  sprintf(string_convert_buffer, "%f", value);
  int32_t string_length = strlen(string_convert_buffer);
  void* string = env->new_str_raw(env, string_convert_buffer, string_length);
  
  return string;
}

SPVM_OBJECT* SPVM_RUNTIME_API_f_to_str(SPVM_ENV* env, float value) {
  (void)env;
  
  SPVM_OBJECT* str = SPVM_RUNTIME_API_f_to_str_raw(env, value);
  
  SPVM_RUNTIME_API_push_mortal(env, str);
  
  return str;
}

SPVM_OBJECT* SPVM_RUNTIME_API_d_to_str_raw(SPVM_ENV* env, double value) {
  char string_convert_buffer[21];

  sprintf(string_convert_buffer, "%f", value);
  int32_t string_length = strlen(string_convert_buffer);
  void* string = env->new_str_raw(env, string_convert_buffer, string_length);
  
  return string;
}

SPVM_OBJECT* SPVM_RUNTIME_API_d_to_str(SPVM_ENV* env, double value) {
  (void)env;
  
  SPVM_OBJECT* str = SPVM_RUNTIME_API_d_to_str_raw(env, value);
  
  SPVM_RUNTIME_API_push_mortal(env, str);
  
  return str;
}

SPVM_ENV* SPVM_RUNTIME_API_new_env(SPVM_ENV* env) {
  return SPVM_RUNTIME_API_create_env(env->runtime);
}

void SPVM_RUNTIME_API_free_env(SPVM_ENV* env) {
  // Free mortal stack
  SPVM_RUNTIME_API_free_memory_block(env, env->native_mortal_stack);
  
  // Free exception
  SPVM_RUNTIME_API_set_exception(env, NULL);
  
  free(env);
}

SPVM_RUNTIME* SPVM_RUNTIME_API_build_runtime(SPVM_PORTABLE* portable) {
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_safe_malloc_zero(sizeof(SPVM_RUNTIME));

  runtime->portable = portable;
  
  runtime->string_pool = portable->string_pool;
  runtime->string_pool_length = portable->string_pool_length;
  
  runtime->constant_pool = portable->constant_pool;
  runtime->constant_pool_length = portable->constant_pool_length;
  
  runtime->basic_types = portable->basic_types;
  runtime->basic_types_length = portable->basic_types_length;
  
  // Create basic type rank(string_pool_id and rank)
  runtime->sorted_basic_types = SPVM_RUNTIME_API_safe_malloc_zero(sizeof(SPVM_BASIC_TYPE) * runtime->basic_types_length);
  memcpy(runtime->sorted_basic_types, runtime->basic_types, sizeof(SPVM_BASIC_TYPE) * runtime->basic_types_length);
  
  // Sort basic type id
  for (int32_t i = 0; i < runtime->basic_types_length - 1; i++) {
    for (int32_t j = (runtime->basic_types_length - 1); j > i; j--) {
      SPVM_RUNTIME_BASIC_TYPE* basic_type1 = &runtime->sorted_basic_types[j - 1];
      SPVM_RUNTIME_BASIC_TYPE* basic_type2 = &runtime->sorted_basic_types[j];
      
      const char* basic_type1_name = &runtime->string_pool[basic_type1->name_id];
      const char* basic_type2_name = &runtime->string_pool[basic_type2->name_id];
      
      if (strcmp(basic_type1_name, basic_type2_name) > 0) {
        SPVM_RUNTIME_BASIC_TYPE temp = *(SPVM_RUNTIME_BASIC_TYPE*)&runtime->sorted_basic_types[j - 1];
        *(SPVM_RUNTIME_BASIC_TYPE*)&runtime->sorted_basic_types[j - 1] = *(SPVM_RUNTIME_BASIC_TYPE*)&runtime->sorted_basic_types[j];
        *(SPVM_RUNTIME_BASIC_TYPE*)&runtime->sorted_basic_types[j] = temp;
      }
    }
  }

  runtime->fields = (SPVM_RUNTIME_FIELD*)portable->fields;
  runtime->fields_length = portable->fields_length;
  runtime->package_vars = (SPVM_RUNTIME_PACKAGE_VAR*)portable->package_vars;
  runtime->package_vars_length = portable->package_vars_length;
  runtime->args = (SPVM_RUNTIME_ARG*)portable->args;
  runtime->opcodes = (SPVM_OPCODE*)portable->opcodes;
  runtime->subs = (SPVM_RUNTIME_SUB*)portable->subs;
  runtime->subs_length = portable->subs_length;
  runtime->packages_length = portable->packages_length;
  runtime->packages = (SPVM_RUNTIME_PACKAGE*)portable->packages;

  // C function addresses(native or precompile)
  runtime->sub_cfunc_addresses = SPVM_RUNTIME_API_safe_malloc_zero(sizeof(void*) * (runtime->subs_length + 1));
  
  // Initialize Package Variables
  runtime->package_vars_heap = SPVM_RUNTIME_API_safe_malloc_zero(sizeof(SPVM_VALUE) * (runtime->package_vars_length + 1));
  
  return runtime;
}

void SPVM_RUNTIME_API_free_runtime(SPVM_RUNTIME* runtime) {
  
  // Free portable
  SPVM_PORTABLE_free(runtime->portable);
  
  // Free C function addresses
  free(runtime->sub_cfunc_addresses);
  
  // Free package variables heap
  free(runtime->package_vars_heap);
  
  // Free runtime
  free(runtime);
}

void SPVM_RUNTIME_API_call_begin_blocks(SPVM_ENV* env) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Call BEGIN blocks
  int32_t packages_length = runtime->packages_length;
  SPVM_VALUE stack[SPVM_LIMIT_C_STACK_MAX];
  for (int32_t package_id = 0; package_id < packages_length; package_id++) {
    SPVM_RUNTIME_PACKAGE* package = &runtime->packages[package_id];
    
    int32_t begin_sub_id = package->begin_sub_id;
    if (begin_sub_id >= 0) {
      SPVM_RUNTIME_SUB* begin_sub = &runtime->subs[begin_sub_id];
      env->call_sub(env, begin_sub->id, stack);
    }
  }
}

int32_t SPVM_RUNTIME_API_call_sub(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* stack) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;

  // Sub
  SPVM_RUNTIME_SUB* sub = &runtime->subs[sub_id];
  
  // Call native sub
  if (sub->flag & SPVM_SUB_C_FLAG_NATIVE) {
    // Enter scope
    int32_t original_mortal_stack_top = SPVM_RUNTIME_API_enter_scope(env);

    // Call native subrotuine
    int32_t (*native_address)(SPVM_ENV*, SPVM_VALUE*) = runtime->sub_cfunc_addresses[sub->id];
    int32_t exception_flag = (*native_address)(env, stack);
    
    // Increment ref count of return value
    if (!exception_flag) {
      switch (sub->return_runtime_type) {
        case SPVM_TYPE_C_RUNTIME_TYPE_ANY_OBJECT:
        case SPVM_TYPE_C_RUNTIME_TYPE_PACKAGE:
        case SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY:
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_ARRAY:
        case SPVM_TYPE_C_RUNTIME_TYPE_OBJECT_ARRAY:
        {
          if (*(void**)&stack[0] != NULL) {
            SPVM_RUNTIME_API_INC_REF_COUNT_ONLY(*(void**)&stack[0]);
          }
        }
      }
    }

    // Leave scope
    SPVM_RUNTIME_API_leave_scope(env, original_mortal_stack_top);

    // Decrement ref count of return value
    if (!exception_flag) {
      switch (sub->return_runtime_type) {
        case SPVM_TYPE_C_RUNTIME_TYPE_ANY_OBJECT:
        case SPVM_TYPE_C_RUNTIME_TYPE_PACKAGE:
        case SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY:
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_ARRAY:
        case SPVM_TYPE_C_RUNTIME_TYPE_OBJECT_ARRAY:
        {
          if (*(void**)&stack[0] != NULL) {
            SPVM_RUNTIME_API_DEC_REF_COUNT_ONLY(*(void**)&stack[0]);
          }
        }
      }
    }
    
    // Set default exception message
    if (exception_flag && env->exception_object == NULL) {
      void* exception = env->new_str_raw(env, "Error", 0);
      env->set_exception(env, exception);
    }
    
    return exception_flag;
  }
  // Call precompiled sub
  else if (sub->flag & SPVM_SUB_C_FLAG_PRECOMPILE) {
    int32_t (*precompile_address)(SPVM_ENV*, SPVM_VALUE*) = runtime->sub_cfunc_addresses[sub->id];
    return (*precompile_address)(env, stack);
  }
  // Call sub virtual machine
  else {
    return SPVM_RUNTIME_API_call_sub_vm(env, sub_id, stack);
  }
}

int32_t SPVM_RUNTIME_API_call_sub_vm(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* stack) {
  (void)env;

  // Condition flag
  register int32_t condition_flag = 0;
  
  // Opcode relative index
  register int32_t opcode_rel_index = 0;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;

  // Runtime subroutine
  SPVM_RUNTIME_SUB* sub = &runtime->subs[sub_id];
  
  // Runtime package
  SPVM_RUNTIME_PACKAGE* package = &runtime->packages[sub->package_id];

  // Operation codes
  SPVM_OPCODE* opcodes = runtime->opcodes;

  // Exception flag
  int32_t exception_flag = 0;

  // Operation code base
  int32_t sub_opcodes_base = sub->opcodes_base;

  // Call subroutine argument stack top
  int32_t call_sub_arg_stack_top = 0;
  
  // Mortal stack
  uint16_t* mortal_stack = NULL;
  int32_t mortal_stack_top = 0;
  
  // object variables
  void** object_vars = NULL;
  
  // ref variables
  void** ref_vars = NULL;
  
  // double variables
  SPVM_VALUE_double* double_vars = NULL;
  
  // float variables
  SPVM_VALUE_float* float_vars = NULL;

  // long variables
  SPVM_VALUE_long* long_vars = NULL;

  // int variables
  SPVM_VALUE_int* int_vars = NULL;

  // short variables
  SPVM_VALUE_short* short_vars = NULL;
  
  // byte variables
  SPVM_VALUE_byte* byte_vars = NULL;
  
  // Alloc variable memory
  // Allignment is 8. This is numeric type max byte size
  // Order 8, 4, 2, 1 numeric variable, and addrress variables
  char* call_stack = NULL;
  char call_stack_small[256];
  int8_t need_free_call_stack = 0;
  {
    // Numeric area byte size
    int32_t numeric_vars_byte_size = 0;
    numeric_vars_byte_size += sub->long_vars_alloc_length * 8;
    numeric_vars_byte_size += sub->double_vars_alloc_length * 8;
    numeric_vars_byte_size += sub->int_vars_alloc_length * 4;
    numeric_vars_byte_size += sub->float_vars_alloc_length * 4;
    numeric_vars_byte_size += sub->short_vars_alloc_length * 2;
    numeric_vars_byte_size += sub->mortal_stack_length * 2;
    numeric_vars_byte_size += sub->byte_vars_alloc_length * 1;
    
    if (numeric_vars_byte_size % 8 != 0) {
      numeric_vars_byte_size += (8 - (numeric_vars_byte_size % 8));
    }
    
    // Address area byte size
    int32_t address_vars_byte_size = 0;
    address_vars_byte_size += sub->object_vars_alloc_length * sizeof(void*);
    address_vars_byte_size += sub->ref_vars_alloc_length * sizeof(void*);
    
    // Total area byte size
    int32_t total_vars_byte_size = numeric_vars_byte_size + address_vars_byte_size;
    
    if (total_vars_byte_size > 0) {
      if (total_vars_byte_size <= 256) {
        call_stack = call_stack_small;
        memset(call_stack, 0, total_vars_byte_size);
      }
      else {
        call_stack = SPVM_RUNTIME_API_alloc_memory_block_zero(env, total_vars_byte_size);
        need_free_call_stack = 1;
      }

      int32_t call_stack_offset = 0;
      
      // Double variables
      double_vars = (double*)&call_stack[call_stack_offset];
      call_stack_offset += sub->double_vars_alloc_length * 8;
      
      // Long varialbes
      long_vars = (SPVM_VALUE_long*)&call_stack[call_stack_offset];
      call_stack_offset += sub->long_vars_alloc_length * 8;
      
      // Float variables
      float_vars = (float*)&call_stack[call_stack_offset];
      call_stack_offset += sub->float_vars_alloc_length * 4;
      
      // Int variables
      int_vars = (SPVM_VALUE_int*)&call_stack[call_stack_offset];
      call_stack_offset += sub->int_vars_alloc_length * 4;

      // Short variables
      short_vars = (SPVM_VALUE_short*)&call_stack[call_stack_offset];
      call_stack_offset += sub->short_vars_alloc_length * 2;

      // Mortal stack
      mortal_stack = (uint16_t*)&call_stack[call_stack_offset];
      call_stack_offset += sub->mortal_stack_length * 2;
      
      // Byte variables
      byte_vars = (SPVM_VALUE_byte*)&call_stack[call_stack_offset];
      call_stack_offset += sub->byte_vars_alloc_length * 1;
      
      call_stack_offset = numeric_vars_byte_size;

      // Object variables
      object_vars = (void**)&call_stack[call_stack_offset];
      call_stack_offset += sub->object_vars_alloc_length * sizeof(void*);
      
      // Refernce variables
      ref_vars = (void**)&call_stack[call_stack_offset];
      call_stack_offset += sub->ref_vars_alloc_length * sizeof(void*);
    }
  }

  // Buffer for string convertion
  // double need 17 digit
  // int64_t need 21 gidit (-9223372036854775808 + (null character))
  char string_convert_buffer[21];
  
  // Copy arguments to variables
  {
    int32_t stack_index = 0;
    for (int32_t arg_index = sub->arg_ids_base; arg_index < sub->arg_ids_base + sub->arg_ids_length; arg_index++) {
      SPVM_RUNTIME_ARG* arg = &runtime->args[arg_index];
      
      int32_t type_width = arg->type_width;
      switch (arg->runtime_type) {
        case SPVM_TYPE_C_RUNTIME_TYPE_BYTE: {
          byte_vars[arg->var_id] = *(SPVM_VALUE_byte*)&stack[stack_index];
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_SHORT: {
          short_vars[arg->var_id] = *(SPVM_VALUE_short*)&stack[stack_index];
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_INT: {
          int_vars[arg->var_id] = *(SPVM_VALUE_int*)&stack[stack_index];
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_LONG: {
          long_vars[arg->var_id] = *(SPVM_VALUE_long*)&stack[stack_index];
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_FLOAT: {
          float_vars[arg->var_id] = *(SPVM_VALUE_float*)&stack[stack_index];
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_DOUBLE: {
          double_vars[arg->var_id] = *(SPVM_VALUE_double*)&stack[stack_index];
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_BYTE: {
          for (int32_t field_index = 0; field_index < type_width; field_index++) {
            byte_vars[arg->var_id + field_index] = *(SPVM_VALUE_byte*)&stack[stack_index + field_index];
          }
          stack_index += type_width;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_SHORT: {
          for (int32_t field_index = 0; field_index < type_width; field_index++) {
            short_vars[arg->var_id + field_index] = *(SPVM_VALUE_short*)&stack[stack_index + field_index];
          }
          stack_index += type_width;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_INT: {
          for (int32_t field_index = 0; field_index < type_width; field_index++) {
            int_vars[arg->var_id + field_index] = *(SPVM_VALUE_int*)&stack[stack_index + field_index];
          }
          stack_index += type_width;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_LONG: {
          for (int32_t field_index = 0; field_index < type_width; field_index++) {
            long_vars[arg->var_id + field_index] = *(SPVM_VALUE_long*)&stack[stack_index + field_index];
          }
          stack_index += type_width;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_FLOAT: {
          for (int32_t field_index = 0; field_index < type_width; field_index++) {
            float_vars[arg->var_id + field_index] = *(SPVM_VALUE_float*)&stack[stack_index + field_index];
          }
          stack_index += type_width;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_DOUBLE: {
          for (int32_t field_index = 0; field_index < type_width; field_index++) {
            double_vars[arg->var_id + field_index] = *(SPVM_VALUE_double*)&stack[stack_index + field_index];
          }
          stack_index += type_width;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_ANY_OBJECT:
        case SPVM_TYPE_C_RUNTIME_TYPE_PACKAGE:
        case SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY:
        case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_ARRAY:
        case SPVM_TYPE_C_RUNTIME_TYPE_OBJECT_ARRAY:
        {
          object_vars[arg->var_id] = *(void**)&stack[stack_index];

          // If arg is object, increment reference count
          void* object = *(void**)&object_vars[arg->var_id];
          if (object != NULL) {
            SPVM_RUNTIME_API_INC_REF_COUNT_ONLY(object);
          }
          stack_index++;
          break;
        }
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_BYTE:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_SHORT:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_INT:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_LONG:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_FLOAT:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_DOUBLE:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_BYTE:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_SHORT:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_INT:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_LONG:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_FLOAT:
        case SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_DOUBLE:
        {
          ref_vars[arg->var_id] = *(void**)&stack[stack_index];
          stack_index++;
          break;
        }
        default:
          assert(0);
      }
    }
  }

  int32_t object_header_byte_size = (intptr_t)env->object_header_byte_size;

  // Execute operation codes
  while (1) {
    SPVM_OPCODE* opcode = &(opcodes[sub_opcodes_base + opcode_rel_index]);
    
    int32_t opcode_id = __builtin_expect(opcode->id == SPVM_OPCODE_C_ID_WIDE, 0) ? 255 + opcode->operand3 : opcode->id;
    
    switch (opcode_id) {
      case SPVM_OPCODE_C_ID_BOOL_INT:
        condition_flag = int_vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_ID_BOOL_LONG:
        condition_flag = !!long_vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_ID_BOOL_FLOAT:
        condition_flag = !!float_vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_ID_BOOL_DOUBLE:
        condition_flag = !!double_vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_ID_BOOL_OBJECT:
        condition_flag = !!*(void**)&object_vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_ID_IS_UNDEF:
        condition_flag = *(void**)&object_vars[opcode->operand0] == NULL;
        break;
      case SPVM_OPCODE_C_ID_IS_NOT_UNDEF:
        condition_flag = *(void**)&object_vars[opcode->operand0] != NULL;
        break;
      case SPVM_OPCODE_C_ID_EQ_INT:
        condition_flag = int_vars[opcode->operand0] == int_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_EQ_LONG:
        condition_flag = long_vars[opcode->operand0] == long_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_EQ_FLOAT:
        condition_flag = float_vars[opcode->operand0] == float_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_EQ_DOUBLE:
        condition_flag = double_vars[opcode->operand0] == double_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_EQ_OBJECT:
        condition_flag = *(void**)&object_vars[opcode->operand0] == *(void**)&object_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NE_INT:
        condition_flag = int_vars[opcode->operand0] != int_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NE_LONG:
        condition_flag = long_vars[opcode->operand0] != long_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NE_FLOAT:
        condition_flag = float_vars[opcode->operand0] != float_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NE_DOUBLE:
        condition_flag = double_vars[opcode->operand0] != double_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NE_OBJECT:
        condition_flag = *(void**)&object_vars[opcode->operand0] != *(void**)&object_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GT_INT:
        condition_flag = int_vars[opcode->operand0] > int_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GT_LONG:
        condition_flag = long_vars[opcode->operand0] > long_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GT_FLOAT:
        condition_flag = float_vars[opcode->operand0] > float_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GT_DOUBLE:
        condition_flag = double_vars[opcode->operand0] > double_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GE_INT:
        condition_flag = int_vars[opcode->operand0] >= int_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GE_LONG:
        condition_flag = long_vars[opcode->operand0] >= long_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GE_FLOAT:
        condition_flag = float_vars[opcode->operand0] >= float_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GE_DOUBLE:
        condition_flag = double_vars[opcode->operand0] >= double_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LT_INT:
        condition_flag = int_vars[opcode->operand0] < int_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LT_LONG:
        condition_flag = long_vars[opcode->operand0] < long_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LT_FLOAT:
        condition_flag = float_vars[opcode->operand0] < float_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LT_DOUBLE:
        condition_flag = double_vars[opcode->operand0] < double_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LE_INT:
        condition_flag = int_vars[opcode->operand0] <= int_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LE_LONG:
        condition_flag = long_vars[opcode->operand0] <= long_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LE_FLOAT:
        condition_flag = float_vars[opcode->operand0] <= float_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LE_DOUBLE:
        condition_flag = double_vars[opcode->operand0] <= double_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_IS_TYPE: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t constant_pool_id = opcode->operand1;
        int32_t check_basic_type_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        int32_t check_type_dimension = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];

        assert(check_basic_type_id != SPVM_BASIC_TYPE_C_ID_STRING);
        
        if (object) {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
          condition_flag = (object_basic_type_id == check_basic_type_id && object_type_dimension == check_type_dimension);
        }
        else {
          condition_flag = 0;
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_HAS_INTERFACE: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t constant_pool_id = opcode->operand1;
        int32_t interface_basic_type_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        if (object) {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
          condition_flag = env->has_interface(env, object, interface_basic_type_id);
        }
        else {
          condition_flag = 0;
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_EQ:
      case SPVM_OPCODE_C_ID_STRING_NE:
      case SPVM_OPCODE_C_ID_STRING_GT:
      case SPVM_OPCODE_C_ID_STRING_GE:
      case SPVM_OPCODE_C_ID_STRING_LT:
      case SPVM_OPCODE_C_ID_STRING_LE:
      {
        void* object1 = *(void**)&object_vars[opcode->operand0];
        void* object2 = *(void**)&object_vars[opcode->operand1];
        
        if (__builtin_expect(object1 == NULL || object2 == NULL, 0)) {
          condition_flag = 0;
          void* exception = env->new_str_raw(env, "Use of uninitialized value in string comparison operator", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int32_t length1 = *(SPVM_VALUE_int*)((intptr_t)object1 + (intptr_t)env->object_array_length_offset);
          int32_t length2 = *(SPVM_VALUE_int*)((intptr_t)object2 + (intptr_t)env->object_array_length_offset);
          
          SPVM_VALUE_byte* bytes1 = env->belems(env, object1);
          SPVM_VALUE_byte* bytes2 = env->belems(env, object2);
          
          int32_t short_string_length = length1 < length2 ? length1 : length2;
          int32_t retval = memcmp(bytes1, bytes2, short_string_length);
          int32_t cmp;
          if (retval) {
            cmp = retval < 0 ? -1 : 1;
          } else if (length1 == length2) {
            cmp = 0;
          } else {
            cmp = length1 < length2 ? -1 : 1;
          }
          
          switch (opcode_id) {
            case SPVM_OPCODE_C_ID_STRING_EQ:
              condition_flag = (cmp == 0);
              break;
            case SPVM_OPCODE_C_ID_STRING_NE:
              condition_flag = (cmp != 0);
              break;
            case SPVM_OPCODE_C_ID_STRING_GT:
              condition_flag = (cmp == 1);
              break;
            case SPVM_OPCODE_C_ID_STRING_GE:
              condition_flag = (cmp >= 0);
              break;
            case SPVM_OPCODE_C_ID_STRING_LT:
              condition_flag = (cmp == -1);
              break;
            case SPVM_OPCODE_C_ID_STRING_LE:
              condition_flag = (cmp <= 0);
              break;
          }
        }

        break;
      }
      case SPVM_OPCODE_C_ID_ADD_INT:
        int_vars[opcode->operand0] = int_vars[opcode->operand1] + int_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_ADD_LONG:
        long_vars[opcode->operand0] = long_vars[opcode->operand1] + long_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_ADD_FLOAT:
        float_vars[opcode->operand0] = float_vars[opcode->operand1] + float_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_ADD_DOUBLE:
        double_vars[opcode->operand0] = double_vars[opcode->operand1] + double_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_INT:
        int_vars[opcode->operand0] = int_vars[opcode->operand1] - int_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_LONG:
        long_vars[opcode->operand0] = long_vars[opcode->operand1] - long_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_FLOAT:
        float_vars[opcode->operand0] = float_vars[opcode->operand1] - float_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_DOUBLE:
        double_vars[opcode->operand0] = double_vars[opcode->operand1] - double_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_INT:
        int_vars[opcode->operand0] = int_vars[opcode->operand1] * int_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_LONG:
        long_vars[opcode->operand0] = long_vars[opcode->operand1] * long_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_FLOAT:
        float_vars[opcode->operand0] = float_vars[opcode->operand1] * float_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_DOUBLE:
        double_vars[opcode->operand0] = double_vars[opcode->operand1] * double_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_INT:
        if (__builtin_expect(int_vars[opcode->operand2] == 0, 0)) {
          void* exception = env->new_str_raw(env, "0 division", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int_vars[opcode->operand0]
            = int_vars[opcode->operand1] / int_vars[opcode->operand2];
        }
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_LONG:
        if (__builtin_expect(long_vars[opcode->operand2] == 0, 0)) {
          void* exception = env->new_str_raw(env, "0 division", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          long_vars[opcode->operand0]
            = long_vars[opcode->operand1] / long_vars[opcode->operand2];
        }
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_FLOAT:
        float_vars[opcode->operand0]
          = float_vars[opcode->operand1] / float_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_DOUBLE:
        double_vars[opcode->operand0]
          = double_vars[opcode->operand1] / double_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_INT:
        if (__builtin_expect(int_vars[opcode->operand2] == 0, 0)) {
          void* exception = env->new_str_raw(env, "0 division", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int_vars[opcode->operand0] = int_vars[opcode->operand1] % int_vars[opcode->operand2];
        }
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_LONG:
        if (__builtin_expect(long_vars[opcode->operand2] == 0, 0)) {
          void* exception = env->new_str_raw(env, "0 division", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          long_vars[opcode->operand0] = long_vars[opcode->operand1] % long_vars[opcode->operand2];
        }
        break;
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_INT:
        int_vars[opcode->operand0]
          = int_vars[opcode->operand1] << int_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_LONG:
        long_vars[opcode->operand0]
          = long_vars[opcode->operand1] << int_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_INT:
        int_vars[opcode->operand0]
          = int_vars[opcode->operand1] >> int_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_LONG:
        long_vars[opcode->operand0]
          = long_vars[opcode->operand1] >> int_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_INT:
        int_vars[opcode->operand0]
          = (int32_t)((uint32_t)int_vars[opcode->operand1] >> int_vars[opcode->operand2]);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_LONG:
        long_vars[opcode->operand0]
          = (int64_t)((uint64_t)long_vars[opcode->operand1] >> int_vars[opcode->operand2]);
        break;
      case SPVM_OPCODE_C_ID_BIT_AND_INT:
        int_vars[opcode->operand0]
          = int_vars[opcode->operand1] & int_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_BIT_AND_LONG:
        long_vars[opcode->operand0]
          = long_vars[opcode->operand1] & long_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_BIT_OR_INT:
        int_vars[opcode->operand0]
          = int_vars[opcode->operand1] | int_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_BIT_OR_LONG:
        long_vars[opcode->operand0]
          = long_vars[opcode->operand1] | long_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_BIT_XOR_INT:
        int_vars[opcode->operand0]
          = int_vars[opcode->operand1] ^ int_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_BIT_XOR_LONG:
        long_vars[opcode->operand0]
          = long_vars[opcode->operand1] ^ long_vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_NEGATE_INT:
        int_vars[opcode->operand0] = -int_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NEGATE_LONG:
        long_vars[opcode->operand0] = -long_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NEGATE_FLOAT:
        float_vars[opcode->operand0] = -float_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NEGATE_DOUBLE:
        double_vars[opcode->operand0] = -double_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_BIT_NOT_INT:
        int_vars[opcode->operand0] = ~int_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_BIT_NOT_LONG:
        long_vars[opcode->operand0] = ~long_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_LONG:
        long_vars[opcode->operand0] = (int64_t)int_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_FLOAT:
        float_vars[opcode->operand0] = (float)int_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_DOUBLE:
        double_vars[opcode->operand0] = (double)int_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_INT:
        int_vars[opcode->operand0] = (int32_t)long_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_FLOAT:
        float_vars[opcode->operand0] = (float)long_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_DOUBLE:
        double_vars[opcode->operand0] = (double)long_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_INT:
        int_vars[opcode->operand0] = (int32_t)float_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_LONG:
        long_vars[opcode->operand0] = (int64_t)float_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_DOUBLE:
        double_vars[opcode->operand0] = (double)float_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_INT:
        int_vars[opcode->operand0] = (int32_t)double_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_LONG:
        long_vars[opcode->operand0] = (int64_t)double_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_FLOAT:
        float_vars[opcode->operand0] = (float)double_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_BYTE:
        byte_vars[opcode->operand0] = (int8_t)(int_vars[opcode->operand1]);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_SHORT:
        short_vars[opcode->operand0] = (int16_t)(int_vars[opcode->operand1]);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_INT:
        int_vars[opcode->operand0] = (int32_t)byte_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_INT:
        int_vars[opcode->operand0] = (int32_t)short_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_LONG:
        long_vars[opcode->operand0] = (int64_t)byte_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_FLOAT:
        float_vars[opcode->operand0] = (float)byte_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_DOUBLE:
        double_vars[opcode->operand0] = (double)byte_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_BYTE:
        byte_vars[opcode->operand0] = (int8_t)short_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_LONG:
        long_vars[opcode->operand0] = (int64_t)short_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_FLOAT:
        float_vars[opcode->operand0] = (float)short_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_DOUBLE:
        double_vars[opcode->operand0] = (double)short_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_BYTE:
        byte_vars[opcode->operand0] = (int8_t)long_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_SHORT:
        short_vars[opcode->operand0] = (int16_t)long_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_BYTE:
        byte_vars[opcode->operand0] = (int8_t)float_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_SHORT:
        short_vars[opcode->operand0] = (int16_t)float_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_BYTE:
        byte_vars[opcode->operand0] = (int8_t)double_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_SHORT:
        short_vars[opcode->operand0] = (int16_t)double_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_SHORT:
        short_vars[opcode->operand0] = (int16_t)byte_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_STRING: {
        sprintf(string_convert_buffer, "%" PRId8, byte_vars[opcode->operand1]);
        int32_t string_length = strlen(string_convert_buffer);
        void* string = env->new_str_raw(env, string_convert_buffer, string_length);
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], string);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_STRING_TO_BYTE_ARRAY:
      {
        void* src_string = object_vars[opcode->operand1];
        int32_t src_string_length = env->len(env, src_string);
        int8_t* src_string_data = env->belems(env, src_string);
        void* string = env->new_str_raw(env, (const char*)src_string_data, src_string_length);
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], string);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_STRING: {
        sprintf(string_convert_buffer, "%" PRId16, short_vars[opcode->operand1]);
        int32_t string_length = strlen(string_convert_buffer);
        void* string = env->new_str_raw(env, string_convert_buffer, string_length);
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], string);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_STRING: {
        sprintf(string_convert_buffer, "%" PRId32, int_vars[opcode->operand1]);
        int32_t string_length = strlen(string_convert_buffer);
        void* string = env->new_str_raw(env, string_convert_buffer, string_length);
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], string);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_STRING: {
        sprintf(string_convert_buffer, "%" PRId64, long_vars[opcode->operand1]);
        int32_t string_length = strlen(string_convert_buffer);
        void* string = env->new_str_raw(env, string_convert_buffer, string_length);
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], string);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_STRING: {
        sprintf(string_convert_buffer, "%g", float_vars[opcode->operand1]);
        int32_t string_length = strlen(string_convert_buffer);
        void* string = env->new_str_raw(env, string_convert_buffer, string_length);
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], string);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_STRING: {
        sprintf(string_convert_buffer, "%g", double_vars[opcode->operand1]);
        int32_t string_length = strlen(string_convert_buffer);
        void* string = env->new_str_raw(env, string_convert_buffer, string_length);
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], string);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_UNDEF:
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], NULL);
        break;
      case SPVM_OPCODE_C_ID_GET_CONSTANT_CHAR:
        byte_vars[opcode->operand0] = (int8_t)(uint8_t)opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_GET_CONSTANT_INT:
        int_vars[opcode->operand0] = (int32_t)((opcode->operand1 << 16) + opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_GET_CONSTANT_LONG: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t high_value = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        int32_t low_value = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];
        
        long_vars[opcode->operand0] = (int64_t)(((uint64_t)(uint32_t)high_value << 32) + (uint64_t)(uint32_t)low_value);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_FLOAT: {
        SPVM_VALUE value;
        value.ival = (int32_t)((opcode->operand1 << 16) + opcode->operand2);
        float_vars[opcode->operand0] = value.fval;
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_DOUBLE: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t high_value = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        int32_t low_value = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];

        SPVM_VALUE value;
        value.lval = (int64_t)(((uint64_t)(uint32_t)high_value << 32) + (uint64_t)(uint32_t)low_value);

        double double_value;
        double_vars[opcode->operand0] = value.dval;
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_BYTE: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            byte_vars[opcode->operand0] = ((SPVM_VALUE_byte*)((intptr_t)array + object_header_byte_size))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_SHORT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            short_vars[opcode->operand0] = ((SPVM_VALUE_short*)((intptr_t)array + object_header_byte_size))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_INT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int_vars[opcode->operand0] = ((SPVM_VALUE_int*)((intptr_t)array + object_header_byte_size))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_LONG: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            long_vars[opcode->operand0] = ((SPVM_VALUE_long*)((intptr_t)array + object_header_byte_size))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_FLOAT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            float_vars[opcode->operand0] = ((SPVM_VALUE_float*)((intptr_t)array + object_header_byte_size))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_DOUBLE: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            double_vars[opcode->operand0] = ((SPVM_VALUE_double*)((intptr_t)array + object_header_byte_size))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_OBJECT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            void* object = ((SPVM_VALUE_object*)((intptr_t)array + object_header_byte_size))[index];
            SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_BYTE: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            ((SPVM_VALUE_byte*)((intptr_t)array + object_header_byte_size))[index] = byte_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_SHORT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
           ((SPVM_VALUE_short*)((intptr_t)array + object_header_byte_size))[index] = short_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_INT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            ((SPVM_VALUE_int*)((intptr_t)array + object_header_byte_size))[index] = int_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_LONG: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            ((SPVM_VALUE_long*)((intptr_t)array + object_header_byte_size))[index] = long_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_FLOAT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            ((SPVM_VALUE_float*)((intptr_t)array + object_header_byte_size))[index] = float_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_DOUBLE: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            ((SPVM_VALUE_double*)((intptr_t)array + object_header_byte_size))[index] = double_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_OBJECT: {
        
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            void* object_address = &((SPVM_VALUE_object*)((intptr_t)array + object_header_byte_size))[index];
            SPVM_RUNTIME_API_OBJECT_ASSIGN(object_address, *(void**)&object_vars[opcode->operand2]);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_UNDEF: {
        
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            void* object_address = &((SPVM_VALUE_object*)((intptr_t)array + object_header_byte_size))[index];
            SPVM_RUNTIME_API_OBJECT_ASSIGN(object_address, NULL);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FETCH_BYTE: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t field_length = opcode->operand3;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              byte_vars[opcode->operand0 + field_index] = ((SPVM_VALUE_byte*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FETCH_SHORT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t field_length = opcode->operand3;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              short_vars[opcode->operand0 + field_index] = ((SPVM_VALUE_short*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FETCH_INT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              int_vars[opcode->operand0 + field_index] = ((SPVM_VALUE_int*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FETCH_LONG: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              long_vars[opcode->operand0 + field_index] = ((SPVM_VALUE_long*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FETCH_FLOAT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              float_vars[opcode->operand0 + field_index] = ((SPVM_VALUE_float*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FETCH_DOUBLE: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              double_vars[opcode->operand0 + field_index] = ((SPVM_VALUE_double*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_FETCH_BYTE: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            byte_vars[opcode->operand0] = ((SPVM_VALUE_byte*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_FETCH_SHORT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            short_vars[opcode->operand0] = ((SPVM_VALUE_short*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_FETCH_INT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int_vars[opcode->operand0] = ((SPVM_VALUE_int*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_FETCH_LONG: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            long_vars[opcode->operand0] = ((SPVM_VALUE_long*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_FETCH_FLOAT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            float_vars[opcode->operand0] = ((SPVM_VALUE_float*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_FETCH_DOUBLE: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            double_vars[opcode->operand0] = ((SPVM_VALUE_double*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_STORE_BYTE: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t field_length = opcode->operand3;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              ((SPVM_VALUE_byte*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index] = byte_vars[opcode->operand2 + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_STORE_SHORT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t field_length = opcode->operand3;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              ((SPVM_VALUE_short*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index] = short_vars[opcode->operand2 + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_STORE_INT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t field_length = opcode->operand3;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              ((SPVM_VALUE_int*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index] = int_vars[opcode->operand2 + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_STORE_LONG: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t field_length = opcode->operand3;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              ((SPVM_VALUE_long*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index] = long_vars[opcode->operand2 + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_STORE_FLOAT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t field_length = opcode->operand3;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              ((SPVM_VALUE_float*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index] = float_vars[opcode->operand2 + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_STORE_DOUBLE: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t field_length = opcode->operand3;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              ((SPVM_VALUE_double*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index] = double_vars[opcode->operand2 + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_STORE_BYTE: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            ((SPVM_VALUE_byte*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index] = byte_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_STORE_SHORT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            ((SPVM_VALUE_short*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index] = short_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_STORE_INT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            ((SPVM_VALUE_int*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index] = int_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_STORE_LONG: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            ((SPVM_VALUE_long*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index] = long_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_STORE_FLOAT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            ((SPVM_VALUE_float*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index] = float_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FIELD_STORE_DOUBLE: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t field_length = opcode->operand3 & 0xF;
        int32_t field_index = opcode->operand3 >> 4;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            ((SPVM_VALUE_double*)((intptr_t)array + object_header_byte_size))[field_length * index + field_index] = double_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_BYTE: {
        SPVM_VALUE_byte* value_ref = *(SPVM_VALUE_byte**)&ref_vars[opcode->operand1];
        int32_t field_length = opcode->operand3;
        
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          byte_vars[opcode->operand0 + field_index] = value_ref[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SHORT: {
        SPVM_VALUE_short* value_ref = *(SPVM_VALUE_short**)&ref_vars[opcode->operand1];
        int32_t field_length = opcode->operand3;
        
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          short_vars[opcode->operand0 + field_index] = value_ref[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_INT: {
        SPVM_VALUE_int* value_ref = *(SPVM_VALUE_int**)&ref_vars[opcode->operand1];
        int32_t field_length = opcode->operand3;
        
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          int_vars[opcode->operand0 + field_index] = value_ref[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_LONG: {
        SPVM_VALUE_long* value_ref = *(SPVM_VALUE_long**)&ref_vars[opcode->operand1];
        int32_t field_length = opcode->operand3;
        
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          long_vars[opcode->operand0 + field_index] = value_ref[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_FLOAT: {
        SPVM_VALUE_float* value_ref = *(SPVM_VALUE_float**)&ref_vars[opcode->operand1];
        int32_t field_length = opcode->operand3;
        
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          float_vars[opcode->operand0 + field_index] = value_ref[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_DOUBLE: {
        SPVM_VALUE_double* value_ref = *(SPVM_VALUE_double**)&ref_vars[opcode->operand1];
        int32_t field_length = opcode->operand3;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          double_vars[opcode->operand0 + field_index] = value_ref[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_GET_FIELD_BYTE: {
        SPVM_VALUE_byte* value_ref = *(SPVM_VALUE_byte**)&ref_vars[opcode->operand1];
        int32_t field_index = opcode->operand2;
        byte_vars[opcode->operand0] = value_ref[field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_GET_FIELD_SHORT: {
        SPVM_VALUE_short* value_ref = *(SPVM_VALUE_short**)&ref_vars[opcode->operand1];
        int32_t field_index = opcode->operand2;
        short_vars[opcode->operand0] = value_ref[field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_GET_FIELD_INT: {
        SPVM_VALUE_int* value_ref = *(SPVM_VALUE_int**)&ref_vars[opcode->operand1];
        int32_t field_index = opcode->operand2;
        int_vars[opcode->operand0] = value_ref[field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_GET_FIELD_LONG: {
        SPVM_VALUE_long* value_ref = *(SPVM_VALUE_long**)&ref_vars[opcode->operand1];
        int32_t field_index = opcode->operand2;
        long_vars[opcode->operand0] = value_ref[field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_GET_FIELD_FLOAT: {
        SPVM_VALUE_float* value_ref = *(SPVM_VALUE_float**)&ref_vars[opcode->operand1];
        int32_t field_index = opcode->operand2;
        float_vars[opcode->operand0] = value_ref[field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_GET_FIELD_DOUBLE: {
        SPVM_VALUE_double* value_ref = *(SPVM_VALUE_double**)&ref_vars[opcode->operand1];
        int32_t field_index = opcode->operand2;
        double_vars[opcode->operand0] = value_ref[field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SET_FIELD_BYTE: {
        SPVM_VALUE_byte* value_ref = *(SPVM_VALUE_byte**)&ref_vars[opcode->operand0];
        int32_t field_index = opcode->operand2;
        value_ref[field_index] = byte_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SET_FIELD_SHORT: {
        SPVM_VALUE_short* value_ref = *(SPVM_VALUE_short**)&ref_vars[opcode->operand0];
        int32_t field_index = opcode->operand2;
        value_ref[field_index] = short_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SET_FIELD_INT: {
        SPVM_VALUE_int* value_ref = *(SPVM_VALUE_int**)&ref_vars[opcode->operand0];
        int32_t field_index = opcode->operand2;
        value_ref[field_index] = int_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SET_FIELD_LONG: {
        SPVM_VALUE_long* value_ref = *(SPVM_VALUE_long**)&ref_vars[opcode->operand0];
        int32_t field_index = opcode->operand2;
        value_ref[field_index] = long_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SET_FIELD_FLOAT: {
        SPVM_VALUE_float* value_ref = *(SPVM_VALUE_float**)&ref_vars[opcode->operand0];
        int32_t field_index = opcode->operand2;
        value_ref[field_index] = float_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_DEREF_SET_FIELD_DOUBLE: {
        SPVM_VALUE_double* value_ref = *(SPVM_VALUE_double**)&ref_vars[opcode->operand0];
        int32_t field_index = opcode->operand2;
        value_ref[field_index] = double_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_BYTE:
        byte_vars[opcode->operand0] = byte_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_MOVE_SHORT:
        short_vars[opcode->operand0] = short_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_MOVE_INT:
        int_vars[opcode->operand0] = int_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_MOVE_LONG:
        long_vars[opcode->operand0] = long_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_MOVE_FLOAT:
        float_vars[opcode->operand0] = float_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_MOVE_DOUBLE:
        double_vars[opcode->operand0] = double_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_MOVE_OBJECT:
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], *(void**)&object_vars[opcode->operand1]);
        break;
      case SPVM_OPCODE_C_ID_MOVE_REF:
        *(void**)&ref_vars[opcode->operand0] = *(void**)&ref_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_VALUE_MOVE_BYTE: {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          byte_vars[opcode->operand0 + field_index] = byte_vars[opcode->operand1 + field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_MOVE_SHORT: {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          short_vars[opcode->operand0 + field_index] = short_vars[opcode->operand1 + field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_MOVE_INT: {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          int_vars[opcode->operand0 + field_index] = int_vars[opcode->operand1 + field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_MOVE_LONG: {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          long_vars[opcode->operand0 + field_index] = long_vars[opcode->operand1 + field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_MOVE_FLOAT: {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          float_vars[opcode->operand0 + field_index] = float_vars[opcode->operand1 + field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_MOVE_DOUBLE: {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          double_vars[opcode->operand0 + field_index] = double_vars[opcode->operand1 + field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_GET_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        byte_vars[opcode->operand0] = byte_vars[opcode->operand1 + field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_GET_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        short_vars[opcode->operand0] = short_vars[opcode->operand1 + field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_GET_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        int_vars[opcode->operand0] = int_vars[opcode->operand1 + field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_GET_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        long_vars[opcode->operand0] = long_vars[opcode->operand1 + field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_GET_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        float_vars[opcode->operand0] = float_vars[opcode->operand1 + field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_GET_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        double_vars[opcode->operand0] = double_vars[opcode->operand1 + field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_SET_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        byte_vars[opcode->operand0 + field_index] = byte_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_SET_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        short_vars[opcode->operand0 + field_index] = short_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_SET_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        int_vars[opcode->operand0 + field_index] = int_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_SET_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        long_vars[opcode->operand0 + field_index] = long_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_SET_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        float_vars[opcode->operand0 + field_index] = float_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_SET_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        double_vars[opcode->operand0 + field_index] = double_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_MORTAL: {
        mortal_stack[mortal_stack_top] = opcode->operand0;
        mortal_stack_top++;
        
        break;
      }
      case SPVM_OPCODE_C_ID_LEAVE_SCOPE: {
        int32_t original_mortal_stack_top = opcode->operand0;
        int32_t mortal_stack_index;
        for (mortal_stack_index = original_mortal_stack_top; mortal_stack_index < mortal_stack_top; mortal_stack_index++) {
          int32_t var_index = mortal_stack[mortal_stack_index];
          void** object_address = (void**)&object_vars[var_index];
          
          if (*(void**)&object_vars[var_index] != NULL) {
            if (SPVM_RUNTIME_API_GET_REF_COUNT(*object_address) > 1) { SPVM_RUNTIME_API_DEC_REF_COUNT_ONLY(*object_address); }
            else { env->dec_ref_count(env, *object_address); }
          }
          
          *object_address = NULL;
        }
        
        mortal_stack_top = original_mortal_stack_top;
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t basic_type_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        void* object = env->new_obj_raw(env, basic_type_id);
        
        // Push object
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_BYTE_ARRAY: {
        int32_t length = int_vars[opcode->operand1];
        if (length >= 0) {
          void* object = env->new_barray_raw(env, length);
          SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_str_raw(env, "Array length must be more than or equal to 0", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY: {
        
        // length
        int32_t length = int_vars[opcode->operand1];
        
        if (length >= 0) {
          void* object = env->new_sarray_raw(env, length);
          
          // Set array
          SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_str_raw(env, "Array length must be more than or equal to 0", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_INT_ARRAY: {
        
        // length
        int32_t length = int_vars[opcode->operand1];
        
        if (length >= 0) {
          void* object = env->new_iarray_raw(env, length);
          
          // Set array
          SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_str_raw(env, "Array length must be more than or equal to 0", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_LONG_ARRAY: {
        
        int32_t length = int_vars[opcode->operand1];
        if (length >= 0) {
          void* object = env->new_larray_raw(env, length);
          SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_str_raw(env, "Array length must be more than or equal to 0", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY: {
        
        int32_t length = int_vars[opcode->operand1];
        if (length >= 0) {
          void* object = env->new_farray_raw(env, length);
          SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_str_raw(env, "Array length must be more than or equal to 0", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY: {
        
        int32_t length = int_vars[opcode->operand1];
        if (length >= 0) {
          void* object = env->new_darray_raw(env, length);
          SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_str_raw(env, "Array length must be more than or equal to 0", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t basic_type_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        int32_t length = int_vars[opcode->operand2];
        if (length >= 0) {
          void* object = env->new_oarray_raw(env, basic_type_id, length);
          SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_str_raw(env, "Array length must be more than or equal to 0", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULTI_ARRAY: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t basic_type_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        int32_t element_dimension = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1] - 1;
        
        int32_t length = int_vars[opcode->operand2];
        if (length >= 0) {
          void* object = env->new_marray_raw(env, basic_type_id, element_dimension, length);
          SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_str_raw(env, "Array length must be more than or equal to 0", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_VALUE_ARRAY: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t basic_type_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        // length
        int32_t length = int_vars[opcode->operand2];
        
        if (length >= 0) {
          void* object = env->new_varray_raw(env, basic_type_id, length);
          
          // Set object
          SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_str_raw(env, "Array length must be more than or equal to 0", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t string_length = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        int32_t string_pool_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];
        const char* string_value = &runtime->string_pool[string_pool_id];
        
        void* string = env->new_str_raw(env, string_value, string_length);
  
        
        // Set string
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0] , string);

        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LENGTH:
        if (*(void**)&object_vars[opcode->operand1] == NULL) {
          void* exception = env->new_str_raw(env, "Can't get array length of undef value.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int_vars[opcode->operand0] = *(SPVM_VALUE_int*)((intptr_t)*(void**)&object_vars[opcode->operand1] + (intptr_t)env->object_array_length_offset);
        }
        break;
      case SPVM_OPCODE_C_ID_CONCAT: {
        
        void* string1 = *(void**)&object_vars[opcode->operand1];
        void* string2 = *(void**)&object_vars[opcode->operand2];
        if (string1 == NULL) {
          void* exception = env->new_str_raw(env, "\".\" operater left value must be defined", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else if (string2 == NULL) {
          void* exception = env->new_str_raw(env, "\".\" operater right value must be defined", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          void* string3 = env->concat_raw(env, string1, string2);
          SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], string3);
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_GOTO:
        opcode_rel_index = opcode->operand0;
        continue;
      case SPVM_OPCODE_C_ID_IF_EQ_ZERO: {
        if (condition_flag == 0) {
          opcode_rel_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_IF_NE_ZERO: {
        if (condition_flag) {
          opcode_rel_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_BYTE: {
        *(SPVM_VALUE_byte*)&stack[call_sub_arg_stack_top] = byte_vars[opcode->operand0];
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_SHORT: {
        *(SPVM_VALUE_short*)&stack[call_sub_arg_stack_top] = short_vars[opcode->operand0];
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_INT: {
        *(SPVM_VALUE_int*)&stack[call_sub_arg_stack_top] = int_vars[opcode->operand0];
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_LONG: {
        *(SPVM_VALUE_long*)&stack[call_sub_arg_stack_top] = long_vars[opcode->operand0];
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_FLOAT: {
        *(SPVM_VALUE_float*)&stack[call_sub_arg_stack_top] = float_vars[opcode->operand0];
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_DOUBLE: {
        *(SPVM_VALUE_double*)&stack[call_sub_arg_stack_top] = double_vars[opcode->operand0];
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_OBJECT: {
        *(void**)&stack[call_sub_arg_stack_top] = *(void**)&object_vars[opcode->operand0];
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_REF: {
        *(void**)&stack[call_sub_arg_stack_top] = *(void**)&ref_vars[opcode->operand0];
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_UNDEF:
        *(void**)&stack[call_sub_arg_stack_top] = NULL;
        call_sub_arg_stack_top++;
        
        break;
      case SPVM_OPCODE_C_ID_PUSH_ARG_VALUE_BYTE: {
        int32_t field_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          *(SPVM_VALUE_byte*)&stack[call_sub_arg_stack_top + field_index] = byte_vars[opcode->operand0 + field_index];
        }
        call_sub_arg_stack_top += field_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_VALUE_SHORT: {
        int32_t field_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          *(SPVM_VALUE_short*)&stack[call_sub_arg_stack_top + field_index] = short_vars[opcode->operand0 + field_index];
        }
        call_sub_arg_stack_top += field_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_VALUE_INT: {
        int32_t field_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          *(SPVM_VALUE_int*)&stack[call_sub_arg_stack_top + field_index] = int_vars[opcode->operand0 + field_index];
        }
        call_sub_arg_stack_top += field_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_VALUE_LONG: {
        int32_t field_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          *(SPVM_VALUE_long*)&stack[call_sub_arg_stack_top + field_index] = long_vars[opcode->operand0 + field_index];
        }
        call_sub_arg_stack_top += field_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_VALUE_FLOAT: {
        int32_t field_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          *(SPVM_VALUE_float*)&stack[call_sub_arg_stack_top + field_index] = float_vars[opcode->operand0 + field_index];
        }
        call_sub_arg_stack_top += field_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_VALUE_DOUBLE: {
        int32_t field_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          *(SPVM_VALUE_double*)&stack[call_sub_arg_stack_top + field_index] = double_vars[opcode->operand0 + field_index];
        }
        call_sub_arg_stack_top += field_length;
        break;
      }
      case SPVM_OPCODE_C_ID_CHECK_OBJECT_TYPE: {
        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (object != NULL) {
          int32_t constant_pool_id = opcode->operand2;
          int32_t check_basic_type_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
          int32_t check_type_dimension = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];
          
          assert(check_basic_type_id != SPVM_BASIC_TYPE_C_ID_STRING);
          
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
          
          if (object_basic_type_id == check_basic_type_id && object_type_dimension == check_type_dimension) {
            SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], *(void**)&object_vars[opcode->operand1]);
          }
          else {
            void* exception = env->new_str_raw(env, "Can't convert imcompatible object type.", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_CHECK_INTERFACE: {
        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (object != NULL) {
          int32_t constant_pool_id = opcode->operand2;
          int32_t interface_basic_type_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
          int32_t interface_type_dimension = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];
          
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
          
          if (env->has_interface(env, object, interface_basic_type_id)) {
            SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], *(void**)&object_vars[opcode->operand1]);
          }
          else {
            void* exception = env->new_str_raw(env, "Can't convert imcompatible interface type.", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_VOID:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t call_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_BYTE:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t call_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          byte_vars[opcode->operand0] = *(SPVM_VALUE_byte*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_SHORT:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t call_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          short_vars[opcode->operand0] = *(SPVM_VALUE_short*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_INT:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t call_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int_vars[opcode->operand0] = *(SPVM_VALUE_int*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_LONG:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t call_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          long_vars[opcode->operand0] = *(SPVM_VALUE_long*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_FLOAT:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t call_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          float_vars[opcode->operand0] = *(SPVM_VALUE_float*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_DOUBLE:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t call_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          double_vars[opcode->operand0] = *(SPVM_VALUE_double*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_OBJECT:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t call_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], stack[0].oval);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_BYTE:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t call_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < field_length; field_index++) {
            byte_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_byte*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_SHORT:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t call_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < field_length; field_index++) {
            short_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_short*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_INT:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t call_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < field_length; field_index++) {
            int_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_int*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_LONG:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t call_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < field_length; field_index++) {
            long_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_long*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_FLOAT:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t call_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < field_length; field_index++) {
            float_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_float*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_DOUBLE:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t call_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < field_length; field_index++) {
            double_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_double*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_VOID:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t decl_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->method_sub_id(env, object, decl_sub_name, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_BYTE:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t decl_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->method_sub_id(env, object, decl_sub_name, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          byte_vars[opcode->operand0] = *(SPVM_VALUE_byte*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_SHORT:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t decl_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->method_sub_id(env, object, decl_sub_name, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          short_vars[opcode->operand0] = *(SPVM_VALUE_short*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_INT:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t decl_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->method_sub_id(env, object, decl_sub_name, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int_vars[opcode->operand0] = *(SPVM_VALUE_int*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_LONG:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t decl_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->method_sub_id(env, object, decl_sub_name, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          long_vars[opcode->operand0] = *(SPVM_VALUE_long*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_FLOAT:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t decl_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->method_sub_id(env, object, decl_sub_name, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          float_vars[opcode->operand0] = *(SPVM_VALUE_float*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_DOUBLE:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t decl_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->method_sub_id(env, object, decl_sub_name, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          double_vars[opcode->operand0] = *(SPVM_VALUE_double*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_OBJECT:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t decl_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->method_sub_id(env, object, decl_sub_name, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], stack[0].oval);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_BYTE:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t decl_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->method_sub_id(env, object, decl_sub_name, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < field_length; field_index++) {
            byte_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_byte*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_SHORT:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t decl_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->method_sub_id(env, object, decl_sub_name, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < field_length; field_index++) {
            short_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_short*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_INT:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t decl_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->method_sub_id(env, object, decl_sub_name, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < field_length; field_index++) {
            int_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_int*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_FLOAT:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t decl_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->method_sub_id(env, object, decl_sub_name, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < field_length; field_index++) {
            float_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_float*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_DOUBLE:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t decl_sub_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->method_sub_id(env, object, decl_sub_name, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < field_length; field_index++) {
            double_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_double*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_IF_EXCEPTION_CATCH: {
        if (exception_flag) {
          exception_flag = 0;
          
          SPVM_RUNTIME_SUB* sub = &runtime->subs[package->subs_base + opcode->operand1];
          int32_t sub_id = sub->id;
          int32_t rel_line = opcode->operand2;
          int32_t line = sub->line + rel_line;
          
          const char* sub_name = &runtime->string_pool[sub->name_id];
          SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
          const char* package_name = &runtime->string_pool[sub_package->name_id];
          const char* file = &runtime->string_pool[sub->file_id];
          
          // Exception stack trace
          env->set_exception(env, env->new_stack_trace_raw(env, env->exception(env), package_name, sub_name, file, line));
          opcode_rel_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_IF_EXCEPTION_RETURN: {
        if (exception_flag) {
          SPVM_RUNTIME_SUB* sub = &runtime->subs[package->subs_base + opcode->operand1];
          int32_t sub_id = sub->id;
          int32_t rel_line = opcode->operand2;
          int32_t line = sub->line + rel_line;
          
          const char* sub_name = &runtime->string_pool[sub->name_id];
          SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
          const char* package_name = &runtime->string_pool[sub_package->name_id];
          const char* file = &runtime->string_pool[sub->file_id];

          // Exception stack trace
          env->set_exception(env, env->new_stack_trace_raw(env, env->exception(env), package_name, sub_name, file, line));
          opcode_rel_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CROAK_FLAG_TRUE: {
        exception_flag = 1;
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_VOID:
      {
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_BYTE:
      {
        *(SPVM_VALUE_byte*)&stack[0] = byte_vars[opcode->operand0];
        
        opcode_rel_index = opcode->operand1;
        
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_SHORT:
      {
        *(SPVM_VALUE_short*)&stack[0] = short_vars[opcode->operand0];
        
        opcode_rel_index = opcode->operand1;
        
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_INT:
      {
        *(SPVM_VALUE_int*)&stack[0] = int_vars[opcode->operand0];
        
        opcode_rel_index = opcode->operand1;
        
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_LONG:
      {
        *(SPVM_VALUE_long*)&stack[0] = long_vars[opcode->operand0];
        
        opcode_rel_index = opcode->operand1;
        
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_FLOAT:
      {
        *(SPVM_VALUE_float*)&stack[0] = float_vars[opcode->operand0];
        
        opcode_rel_index = opcode->operand1;
        
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_DOUBLE:
      {
        *(SPVM_VALUE_double*)&stack[0] = double_vars[opcode->operand0];
        
        opcode_rel_index = opcode->operand1;
        
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_OBJECT:
      {
        *(void**)&stack[0] = *(void**)&object_vars[opcode->operand0];
        // Increment ref count of return value not to release by leave scope
        if (*(void**)&stack[0] != NULL) {
          SPVM_RUNTIME_API_INC_REF_COUNT_ONLY(*(void**)&stack[0]);
        }
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_UNDEF:
      {
        *(void**)&stack[0] = NULL;
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_VALUE_BYTE:
      {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          *(SPVM_VALUE_byte*)&stack[field_index] = byte_vars[opcode->operand0 + field_index];
        }
        opcode_rel_index = opcode->operand1;
        
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_VALUE_SHORT:
      {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          *(SPVM_VALUE_short*)&stack[field_index] = short_vars[opcode->operand0 + field_index];
        }
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_VALUE_INT:
      {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          *(SPVM_VALUE_int*)&stack[field_index] = int_vars[opcode->operand0 + field_index];
        }
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_VALUE_LONG:
      {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          *(SPVM_VALUE_long*)&stack[field_index] = long_vars[opcode->operand0 + field_index];
        }
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_VALUE_FLOAT:
      {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          *(SPVM_VALUE_float*)&stack[field_index] = float_vars[opcode->operand0 + field_index];
        }
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_VALUE_DOUBLE:
      {
        int32_t field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < field_length; field_index++) {
          *(SPVM_VALUE_double*)&stack[field_index] = double_vars[opcode->operand0 + field_index];
        }
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_TABLE_SWITCH: {
        int32_t constant_pool_id = opcode->operand1;

        // Default branch
        int32_t default_opcode_rel_index = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        // Min
        int32_t min = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];

        // Max
        int32_t max = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 2];
        
        // Range
        int32_t range = max - min + 1;
        
        if (int_vars[opcode->operand0] >= min && int_vars[opcode->operand0] <= max) {
          // Offset
          int32_t offset = int_vars[opcode->operand0] - min;
          opcode_rel_index = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 3 + offset];
        }
        else {
          opcode_rel_index = default_opcode_rel_index;
        }
        
        continue;
      }
      case SPVM_OPCODE_C_ID_LOOKUP_SWITCH: {
        
        int32_t constant_pool_id = opcode->operand1;

        // Default branch
        int32_t default_opcode_rel_index = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        // Cases length
        int32_t case_infos_length = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 1];

        if (case_infos_length > 0) {
          // min
          int32_t min = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 2];
          
          // max
          int32_t max = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 2 + (2 * (case_infos_length - 1))];


          
          if (int_vars[opcode->operand0] >= min && int_vars[opcode->operand0] <= max) {
            // 2 opcode_rel_index searching
            int32_t cur_min_pos = 0;
            int32_t cur_max_pos = case_infos_length - 1;
            
            while (1) {
              if (cur_max_pos < cur_min_pos) {
                opcode_rel_index = default_opcode_rel_index;
                break;
              }
              int32_t cur_half_pos = cur_min_pos + (cur_max_pos - cur_min_pos) / 2;
              int32_t cur_half = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 2 + (2 * cur_half_pos)];
              
              if (int_vars[opcode->operand0] > cur_half) {
                cur_min_pos = cur_half_pos + 1;
              }
              else if (int_vars[opcode->operand0] < cur_half) {
                cur_max_pos = cur_half_pos - 1;
              }
              else {
                opcode_rel_index = runtime->constant_pool[package->constant_pool_base + constant_pool_id + 2 + (2 * cur_half_pos) + 1];
                break;
              }
            }
          }
          else {
            opcode_rel_index = default_opcode_rel_index;
          }
        }
        else {
          opcode_rel_index = default_opcode_rel_index;
        }
        
        continue;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_BYTE: {
        int32_t constant_pool_id = opcode->operand2;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_offset = field->offset;

        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          byte_vars[opcode->operand0] = *(SPVM_VALUE_byte*)((intptr_t)object + object_header_byte_size + field_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_SHORT: {
        int32_t constant_pool_id = opcode->operand2;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_offset = field->offset;

        void* object = *(void**)&object_vars[opcode->operand1];

        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          short_vars[opcode->operand0] = *(SPVM_VALUE_short*)((intptr_t)object + object_header_byte_size + field_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_INT: {
        int32_t constant_pool_id = opcode->operand2;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_offset = field->offset;

        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int_vars[opcode->operand0] = *(SPVM_VALUE_int*)((intptr_t)object + object_header_byte_size + field_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_LONG: {
        int32_t constant_pool_id = opcode->operand2;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_offset = field->offset;

        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
          long_vars[opcode->operand0] = *(SPVM_VALUE_long*)((intptr_t)object + object_header_byte_size + field_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_FLOAT: {
        int32_t constant_pool_id = opcode->operand2;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_offset = field->offset;

        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          float_vars[opcode->operand0] = *(SPVM_VALUE_float*)((intptr_t)object + object_header_byte_size + field_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE: {
        int32_t constant_pool_id = opcode->operand2;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_offset = field->offset;

        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          double_vars[opcode->operand0] = *(SPVM_VALUE_double*)((intptr_t)object + object_header_byte_size + field_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_OBJECT: {
        int32_t constant_pool_id = opcode->operand2;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_offset = field->offset;

        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          void* ofield = *(SPVM_VALUE_object*)((intptr_t)object + object_header_byte_size + field_offset);
          SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], ofield);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_BYTE: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t constant_pool_id = opcode->operand1;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_offset = field->offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_byte*)((intptr_t)object + object_header_byte_size + field_offset) = byte_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_SHORT: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t constant_pool_id = opcode->operand1;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_offset = field->offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_short*)((intptr_t)object + object_header_byte_size + field_offset) = short_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_INT: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t constant_pool_id = opcode->operand1;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_offset = field->offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_int*)((intptr_t)object + object_header_byte_size + field_offset) = int_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_LONG: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t constant_pool_id = opcode->operand1;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_offset = field->offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_long*)((intptr_t)object + object_header_byte_size + field_offset) = long_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_FLOAT: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t constant_pool_id = opcode->operand1;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_offset = field->offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_float*)((intptr_t)object + object_header_byte_size + field_offset) = float_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t constant_pool_id = opcode->operand1;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_offset = field->offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_double*)((intptr_t)object + object_header_byte_size + field_offset) = double_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_OBJECT: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t constant_pool_id = opcode->operand1;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_offset = field->offset;

        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          void* ofield_address = (SPVM_VALUE_object*)((intptr_t)object + object_header_byte_size + field_offset);
          SPVM_RUNTIME_API_OBJECT_ASSIGN(ofield_address, *(void**)&object_vars[opcode->operand2]);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_UNDEF: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t constant_pool_id = opcode->operand1;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_offset = field->offset;

        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_str_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          void* ofield_address = (SPVM_VALUE_object*)((intptr_t)object + object_header_byte_size + field_offset);
          SPVM_RUNTIME_API_OBJECT_ASSIGN(ofield_address, NULL);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_WEAKEN_FIELD: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t field_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_offset = field->offset;
        void* object = *(void**)&object_vars[opcode->operand0];
        if (object == NULL) {
          SPVM_OBJECT* exception = env->new_str_raw(env, "Object to weaken an object field must not be undefined.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          void** ofield_address = (SPVM_VALUE_object*)((intptr_t)object + object_header_byte_size + field_offset);
          env->weaken(env, ofield_address);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_WEAKEN_ARRAY_ELEMENT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_str_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_array_length_offset), 0)) {
            void* exception = env->new_str_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            void** elements = (void**)((intptr_t)array + env->object_header_byte_size);
            void** object_element_address = (void**)&elements[index];
            env->weaken(env, object_element_address);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_REF_BYTE:
        *(void**)&ref_vars[opcode->operand0] = &byte_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_REF_SHORT:
        *(void**)&ref_vars[opcode->operand0] = &short_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_REF_INT:
        *(void**)&ref_vars[opcode->operand0] = &int_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_REF_LONG:
        *(void**)&ref_vars[opcode->operand0] = &long_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_REF_FLOAT:
        *(void**)&ref_vars[opcode->operand0] = &float_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_REF_DOUBLE:
        *(void**)&ref_vars[opcode->operand0] = &double_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GET_DEREF_BYTE: {
        byte_vars[opcode->operand0] = *(SPVM_VALUE_byte*)*(void**)&ref_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_SHORT: {
        short_vars[opcode->operand0] = *(SPVM_VALUE_short*)*(void**)&ref_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_INT: {
        int_vars[opcode->operand0] = *(SPVM_VALUE_int*)*(void**)&ref_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_LONG: {
        long_vars[opcode->operand0] = *(SPVM_VALUE_long*)*(void**)&ref_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_FLOAT: {
        float_vars[opcode->operand0] = *(SPVM_VALUE_float*)*(void**)&ref_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_DOUBLE: {
        double_vars[opcode->operand0] = *(SPVM_VALUE_double*)*(void**)&ref_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_BYTE: {
        *(SPVM_VALUE_byte*)*(void**)&ref_vars[opcode->operand0] = byte_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_SHORT: {
        *(SPVM_VALUE_short*)*(void**)&ref_vars[opcode->operand0] = short_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_INT: {
        *(SPVM_VALUE_int*)*(void**)&ref_vars[opcode->operand0] = int_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_LONG: {
        *(SPVM_VALUE_long*)*(void**)&ref_vars[opcode->operand0] = long_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_FLOAT: {
        *(SPVM_VALUE_float*)*(void**)&ref_vars[opcode->operand0] = float_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_DOUBLE: {
        *(SPVM_VALUE_double*)*(void**)&ref_vars[opcode->operand0] = double_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_BYTE: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        byte_vars[opcode->operand0] = *(SPVM_VALUE_byte*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_SHORT: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        short_vars[opcode->operand0] = *(SPVM_VALUE_short*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_INT: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        int_vars[opcode->operand0] = *(SPVM_VALUE_int*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_LONG: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        long_vars[opcode->operand0] = *(SPVM_VALUE_long*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_FLOAT: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        float_vars[opcode->operand0] = *(float*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_DOUBLE: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        double_vars[opcode->operand0] = *(double*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_OBJECT: {
        int32_t constant_pool_id = opcode->operand1;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], *(void**)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[package_var_id]);
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_BYTE: {
        int32_t constant_pool_id = opcode->operand0;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        *(SPVM_VALUE_byte*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[package_var_id] = byte_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_SHORT: {
        int32_t constant_pool_id = opcode->operand0;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        *(SPVM_VALUE_short*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[package_var_id] = short_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_INT: {
        int32_t constant_pool_id = opcode->operand0;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        *(SPVM_VALUE_int*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[package_var_id] = int_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_LONG: {
        int32_t constant_pool_id = opcode->operand0;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        *(SPVM_VALUE_long*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[package_var_id] = long_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_FLOAT: {
        int32_t constant_pool_id = opcode->operand0;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        *(float*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[package_var_id] = float_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_DOUBLE: {
        int32_t constant_pool_id = opcode->operand0;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        *(double*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[package_var_id] = double_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_OBJECT: {
        int32_t constant_pool_id = opcode->operand0;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[package_var_id], *(void**)&object_vars[opcode->operand1]);
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_UNDEF: {
        int32_t constant_pool_id = opcode->operand0;
        int32_t package_var_id = runtime->constant_pool[package->constant_pool_base + constant_pool_id];
        
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_offset))[package_var_id], NULL);
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_EXCEPTION_VAR: {
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], env->exception(env));
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR: {
        
        env->set_exception(env, *(void**)&object_vars[opcode->operand0]);
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR_UNDEF: {
        
        env->set_exception(env, NULL);
        
        break;
      }
      case SPVM_OPCODE_C_ID_END_SUB: {
        goto label_END_SUB;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_BYTE_OBJECT: {
        SPVM_VALUE_byte value = byte_vars[opcode->operand1];
        int32_t basic_type_id = (intptr_t)(void*)env->byte_object_basic_type_id;

        void* object = env->new_obj_raw(env, basic_type_id);
        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
        *(SPVM_VALUE_byte*)&fields[0] = value;
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_SHORT_OBJECT: {
        SPVM_VALUE_short value = short_vars[opcode->operand1];
        int32_t basic_type_id = (intptr_t)(void*)env->short_object_basic_type_id;
        void* object = env->new_obj_raw(env, basic_type_id);
        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
        *(SPVM_VALUE_short*)&fields[0] = value;
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_INT_OBJECT: {
        SPVM_VALUE_int value = int_vars[opcode->operand1];
        int32_t basic_type_id = (intptr_t)(void*)env->int_object_basic_type_id;
        void* object = env->new_obj_raw(env, basic_type_id);
        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
        *(SPVM_VALUE_int*)&fields[0] = value;
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_LONG_OBJECT: {
        SPVM_VALUE_long value = long_vars[opcode->operand1];
        int32_t basic_type_id = (intptr_t)(void*)env->long_object_basic_type_id;
        void* object = env->new_obj_raw(env, basic_type_id);
        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
        *(SPVM_VALUE_long*)&fields[0] = value;
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_FLOAT_OBJECT: {
        SPVM_VALUE_float value = float_vars[opcode->operand1];
        int32_t basic_type_id = (intptr_t)(void*)env->float_object_basic_type_id;
        void* object = env->new_obj_raw(env, basic_type_id);
        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
        *(SPVM_VALUE_float*)&fields[0] = value;
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_DOUBLE_OBJECT: {
        SPVM_VALUE_double value = double_vars[opcode->operand1];
        int32_t basic_type_id = (intptr_t)(void*)env->double_object_basic_type_id;
        void* object = env->new_obj_raw(env, basic_type_id);
        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
        *(SPVM_VALUE_double*)&fields[0] = value;
        SPVM_RUNTIME_API_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_OBJECT_TO_BYTE: {
        void* object = *(void**)&object_vars[opcode->operand1];
        if (object == NULL) {
          void* exception = env->new_str_raw(env, "Can't convert undef value.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
          if (object_basic_type_id == (intptr_t)(void*)env->byte_object_basic_type_id && object_type_dimension == 0) {
            SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
            byte_vars[opcode->operand0] = *(SPVM_VALUE_byte*)&fields[0];
          }
          else {
            void* exception = env->new_str_raw(env, "Can't convert imcompatible object type.", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_OBJECT_TO_SHORT: {
        void* object = *(void**)&object_vars[opcode->operand1];
        if (object == NULL) {
          void* exception = env->new_str_raw(env, "Can't convert undef value.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
          if (object_basic_type_id == (intptr_t)(void*)env->short_object_basic_type_id && object_type_dimension == 0) {
            SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
            short_vars[opcode->operand0] = *(SPVM_VALUE_short*)&fields[0];
          }
          else {
            void* exception = env->new_str_raw(env, "Can't convert imcompatible object type.", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_OBJECT_TO_INT: {
        void* object = *(void**)&object_vars[opcode->operand1];
        if (object == NULL) {
          void* exception = env->new_str_raw(env, "Can't convert undef value.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
          if (object_basic_type_id == (intptr_t)(void*)env->int_object_basic_type_id && object_type_dimension == 0) {
            SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
            int_vars[opcode->operand0] = *(SPVM_VALUE_int*)&fields[0];
          }
          else {
            void* exception = env->new_str_raw(env, "Can't convert imcompatible object type.", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_OBJECT_TO_LONG: {
        void* object = *(void**)&object_vars[opcode->operand1];
        if (object == NULL) {
          void* exception = env->new_str_raw(env, "Can't convert undef value.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
          if (object_basic_type_id == (intptr_t)(void*)env->long_object_basic_type_id && object_type_dimension == 0) {
            SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
            long_vars[opcode->operand0] = *(SPVM_VALUE_long*)&fields[0];
          }
          else {
            void* exception = env->new_str_raw(env, "Can't convert imcompatible object type.", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_OBJECT_TO_FLOAT: {
        void* object = *(void**)&object_vars[opcode->operand1];
        if (object == NULL) {
          void* exception = env->new_str_raw(env, "Can't convert undef value.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
          if (object_basic_type_id == (intptr_t)(void*)env->float_object_basic_type_id && object_type_dimension == 0) {
            SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
            float_vars[opcode->operand0] = *(SPVM_VALUE_float*)&fields[0];
          }
          else {
            void* exception = env->new_str_raw(env, "Can't convert imcompatible object type.", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_OBJECT_TO_DOUBLE: {
        void* object = *(void**)&object_vars[opcode->operand1];
        if (object == NULL) {
          void* exception = env->new_str_raw(env, "Can't convert undef value.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
          if (object_basic_type_id == (intptr_t)(void*)env->double_object_basic_type_id && object_type_dimension == 0) {
            SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
            double_vars[opcode->operand0] = *(SPVM_VALUE_double*)&fields[0];
          }
          else {
            void* exception = env->new_str_raw(env, "Can't convert imcompatible object type.", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
        }
        
        break;
      }
    }
    opcode_rel_index++;
  }

  label_END_SUB:
  
  // Decrement ref count of return value
  if (!exception_flag) {
    switch (sub->return_runtime_type) {
      case SPVM_TYPE_C_RUNTIME_TYPE_ANY_OBJECT:
      case SPVM_TYPE_C_RUNTIME_TYPE_PACKAGE:
      case SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY:
      case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_ARRAY:
      case SPVM_TYPE_C_RUNTIME_TYPE_OBJECT_ARRAY:
      {
        if (*(void**)&stack[0] != NULL) {
          SPVM_RUNTIME_API_DEC_REF_COUNT_ONLY(*(void**)&stack[0]);
        }
      }
    }
  }
  
  if (need_free_call_stack) {
    SPVM_RUNTIME_API_free_memory_block(env, call_stack);
  }
  
  return exception_flag;
}

int32_t SPVM_RUNTIME_API_call_entry_point_sub(SPVM_ENV* env, const char* package_name, int32_t argc, const char *argv[]) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Package
  int32_t sub_id = SPVM_RUNTIME_API_sub_id(env, package_name, "main", "int(string[])");
  
  if (sub_id < 0) {
    fprintf(stderr, "Can't find entry point package %s\n", package_name);
    exit(EXIT_FAILURE);
  }
  
  // Enter scope
  int32_t scope_id = env->enter_scope(env);
  
  // new byte[][args_length] object
  int32_t arg_type_basic_id = env->basic_type_id(env, "byte");
  void* cmd_args_obj = env->new_marray(env, arg_type_basic_id, 1, argc);
  
  // Set command line arguments
  for (int32_t arg_index = 0; arg_index < argc; arg_index++) {
    void* cmd_arg_obj = env->new_str(env, argv[arg_index], strlen(argv[arg_index]));
    env->set_oelem(env, cmd_args_obj, arg_index, cmd_arg_obj);
  }
  
  SPVM_VALUE stack[255];
  stack[0].oval = cmd_args_obj;
  
  // Run
  int32_t exception_flag = env->call_sub(env, sub_id, stack);
  
  int32_t status_code;
  if (exception_flag) {
    SPVM_RUNTIME_API_print(env, env->exception_object);
    printf("\n");
    status_code = 255;
  }
  else {
    status_code = stack[0].ival;
  }
  
  // Leave scope
  env->leave_scope(env, scope_id);
  
  return status_code;
}

int32_t SPVM_RUNTIME_API_is_type(SPVM_ENV* env, SPVM_OBJECT* object, int32_t basic_type_id, int32_t type_dimension) {
  
  // Object must be not null
  assert(object);
  
  if (object->basic_type_id == basic_type_id && object->type_dimension == type_dimension) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_RUNTIME_API_has_interface(SPVM_ENV* env, SPVM_OBJECT* object, int32_t interface_basic_type_id) {
  (void)env;
  
  // Object must be not null
  assert(object);
  
  int32_t object_basic_type_id = object->basic_type_id;
  int32_t object_type_dimension = object->type_dimension;
  
  int32_t has_interface;
  if (object_type_dimension != 0) {
    has_interface = 0;
  }
  else {
    SPVM_RUNTIME* runtime = env->runtime;

    SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object_basic_type_id >= 0 ? &runtime->basic_types[object_basic_type_id] : NULL;
    SPVM_RUNTIME_BASIC_TYPE* interface_basic_type = interface_basic_type_id >= 0 ? &runtime->basic_types[interface_basic_type_id] : NULL;

    SPVM_RUNTIME_PACKAGE* object_package = object_basic_type->package_id ? &runtime->packages[object_basic_type->package_id] : NULL;
    SPVM_RUNTIME_PACKAGE* interface_package = interface_basic_type->package_id ? &runtime->packages[interface_basic_type->package_id] : NULL;
    
    SPVM_RUNTIME_SUB* sub_interface = &runtime->subs[interface_package->subs_base];
    
    const char* sub_interface_signature = &runtime->string_pool[sub_interface->signature_id];
    if (object_package->flag & SPVM_PACKAGE_C_FLAG_ANON_SUB_PACKAGE) {
      SPVM_RUNTIME_SUB* sub = &runtime->subs[object_package->subs_base];
      if (strcmp(sub_interface_signature, &runtime->string_pool[sub->signature_id]) == 0) {
        has_interface = 1;
      }
      else {
        has_interface = 0;
      }
    }
    else {
      const char* object_package_name = &runtime->string_pool[object_package->name_id];
      const char* sub_interface_name = &runtime->string_pool[sub_interface->name_id];
      int32_t sub_id = SPVM_RUNTIME_API_sub_id(env, object_package_name, sub_interface_name, sub_interface_signature);
      if (sub_id >= 0) {
        has_interface = 1;
      }
      else {
        has_interface = 0;
      }
    }
  }
  
  return has_interface;
}

int32_t SPVM_RUNTIME_API_enter_scope(SPVM_ENV* env) {
  (void)env;
  
  int32_t mortal_stack_top = (intptr_t)env->native_mortal_stack_top;
  
  return mortal_stack_top;
}

void SPVM_RUNTIME_API_push_mortal(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;

  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object != NULL) {
    // Extend mortal stack
    if (env->native_mortal_stack_top >= env->native_mortal_stack_capacity) {
      int32_t new_mortal_stack_capacity = (intptr_t)env->native_mortal_stack_capacity * 2;
      SPVM_OBJECT** new_mortal_stack = SPVM_RUNTIME_API_alloc_memory_block_zero(env, sizeof(void*) * new_mortal_stack_capacity);
      memcpy(new_mortal_stack, env->native_mortal_stack, sizeof(void*) * (intptr_t)env->native_mortal_stack_capacity);
      env->native_mortal_stack_capacity = (void*)(intptr_t)new_mortal_stack_capacity;
      SPVM_RUNTIME_API_free_memory_block(env, env->native_mortal_stack);
      env->native_mortal_stack = new_mortal_stack;
    }
    
    ((SPVM_OBJECT**)(env->native_mortal_stack))[(intptr_t)env->native_mortal_stack_top] = object;
    env->native_mortal_stack_top = (void*)((intptr_t)env->native_mortal_stack_top + 1);
    
    object->ref_count++;
  }
}

SPVM_OBJECT* SPVM_RUNTIME_API_type_name_raw(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  assert(object);
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t basic_type_id = object->basic_type_id;
  int32_t type_dimension = object->type_dimension;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
  const char* basic_type_name = &runtime->string_pool[basic_type->name_id];
  
  int32_t length = 0;
  
  // Basic type
  length += strlen(basic_type_name);
  
  // []
  length += type_dimension * 2;
  
  void* type_name_barray = env->new_barray_raw(env, length);
  
  char* cur = (char*)env->belems(env, type_name_barray);
  
  sprintf(cur, "%s", basic_type_name);
  cur += strlen(basic_type_name);
  
  int32_t dim_index;
  for (dim_index = 0; dim_index < type_dimension; dim_index++) {
    sprintf(cur, "[]");
    cur += 2;
  }
  
  return type_name_barray;
}

SPVM_OBJECT* SPVM_RUNTIME_API_type_name(SPVM_ENV* env, SPVM_OBJECT* object_in) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_type_name_raw(env, object_in);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

void SPVM_RUNTIME_API_leave_scope(SPVM_ENV* env, int32_t original_mortal_stack_top) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;

  int32_t mortal_stack_index;
  for (mortal_stack_index = original_mortal_stack_top; mortal_stack_index < (intptr_t)env->native_mortal_stack_top; mortal_stack_index++) {
    SPVM_OBJECT* object = ((SPVM_OBJECT**)(env->native_mortal_stack))[mortal_stack_index];
    
    if (object != NULL) {
      if (object->ref_count > 1) {
        object->ref_count--;
      }
      else {
        SPVM_RUNTIME_API_dec_ref_count(env, object);
      }
    }
    
    ((SPVM_OBJECT**)(env->native_mortal_stack))[mortal_stack_index] = NULL;
  }
  
  env->native_mortal_stack_top = (void*)(intptr_t)original_mortal_stack_top;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_stack_trace_raw(SPVM_ENV* env, SPVM_OBJECT* exception, const char* package_name, const char* sub_name, const char* file, int32_t line) {
  
  // stack trace symbols
  const char* from_part = "\n  from ";
  const char* arrow_part = "->";
  const char* at_part = " at ";

  // Exception
  int8_t* exception_bytes = env->belems(env, exception);
  int32_t exception_length = env->len(env, exception);
  
  // Total string length
  int32_t total_length = 0;
  total_length += exception_length;
  total_length += strlen(from_part);
  total_length += strlen(package_name);
  total_length += strlen(arrow_part);
  total_length += strlen(sub_name);
  total_length += strlen(at_part);
  total_length += strlen(file);

  const char* line_part = " line ";
  char line_str[20];
  
  sprintf(line_str, "%" PRId32, line);
  total_length += strlen(line_part);
  total_length += strlen(line_str);
  
  // Create exception message
  void* new_exception = env->new_str_raw(env, NULL, total_length);
  int8_t* new_exception_bytes = env->belems(env, new_exception);
  
  memcpy(
    (void*)(new_exception_bytes),
    (void*)(exception_bytes),
    exception_length
  );

  sprintf(
    (char*)new_exception_bytes + exception_length,
    "%s%s%s%s%s%s%s%" PRId32,
    from_part,
    package_name,
    arrow_part,
    sub_name,
    at_part,
    file,
    line_part,
    line
  );
  
  return new_exception;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_stack_trace(SPVM_ENV* env, SPVM_OBJECT* exception, const char* package_name, const char* sub_name, const char* file, int32_t line) {
  (void)env;
  
  SPVM_OBJECT* str = SPVM_RUNTIME_API_new_stack_trace_raw(env, exception, package_name, sub_name, file, line);
  
  SPVM_RUNTIME_API_push_mortal(env, str);
  
  return str;
}

void SPVM_RUNTIME_API_print(SPVM_ENV* env, SPVM_OBJECT* string) {
  (void)env;
  
  int8_t* bytes = env->belems(env, string);
  int32_t string_length = env->len(env, string);
  
  {
    int32_t i;
    for (i = 0; i < string_length; i++) {
      putchar((char)bytes[i]);
    }
  }
}

SPVM_OBJECT* SPVM_RUNTIME_API_concat_raw(SPVM_ENV* env, SPVM_OBJECT* string1, SPVM_OBJECT* string2) {
  (void)env;

  int32_t string1_length = SPVM_RUNTIME_API_len(env, string1);
  int32_t string2_length = SPVM_RUNTIME_API_len(env, string2);
  
  int32_t string3_length = string1_length + string2_length;
  SPVM_OBJECT* string3 = SPVM_RUNTIME_API_new_barray_raw(env, string3_length);
  
  int8_t* string1_bytes = SPVM_RUNTIME_API_belems(env, string1);
  int8_t* string2_bytes = SPVM_RUNTIME_API_belems(env, string2);
  int8_t* string3_bytes = SPVM_RUNTIME_API_belems(env, string3);
  
  if (string1_length > 0) {
    memcpy(string3_bytes, string1_bytes, string1_length);
  }
  if (string2_length) {
    memcpy(string3_bytes + string1_length, string2_bytes, string2_length);
  }
  
  return string3;
}

SPVM_OBJECT* SPVM_RUNTIME_API_concat(SPVM_ENV* env, SPVM_OBJECT* string1, SPVM_OBJECT* string2) {
  (void)env;
  
  SPVM_OBJECT* str = SPVM_RUNTIME_API_concat_raw(env, string1, string2);
  
  SPVM_RUNTIME_API_push_mortal(env, str);
  
  return str;
}

int32_t SPVM_RUNTIME_API_memory_blocks_count(SPVM_ENV* env) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  return runtime->memory_blocks_count;
}

void SPVM_RUNTIME_API_free_weaken_back_refs(SPVM_ENV* env, SPVM_RUNTIME_WEAKEN_BACKREF* weaken_backref_head) {
  (void)env;
  
  SPVM_RUNTIME_WEAKEN_BACKREF* temp = weaken_backref_head;
  SPVM_RUNTIME_WEAKEN_BACKREF* swap = NULL;

  while(temp != NULL){
    swap = temp->next;
    *(temp->object_address) = NULL;
    SPVM_RUNTIME_API_free_memory_block(env, temp);
    temp = swap;
  }
}

int32_t SPVM_RUNTIME_API_isweak(SPVM_ENV* env, SPVM_OBJECT** object_address) {
  (void)env;
  
  int32_t isweak = (intptr_t)*object_address & 1;
  
  return isweak;
}

void SPVM_RUNTIME_API_weaken(SPVM_ENV* env, SPVM_OBJECT** object_address) {
  (void)env;
  
  assert(object_address);

  SPVM_RUNTIME* runtime = env->runtime;
  
  if (*object_address == NULL) {
    return;
  }
  
  if (SPVM_RUNTIME_API_isweak(env, object_address)) {
    return;
  }
  
  SPVM_OBJECT* object = *object_address;
  
  // Decrelement reference count
  if (object->ref_count == 1) {
    // If reference count is 1, the object is freeed without weaken
    SPVM_RUNTIME_API_dec_ref_count(env, *object_address);
    *object_address = NULL;
    return;
  }
  else {
    object->ref_count--;
  }

  // Create weaken_backref_head
  if (object->weaken_backref_head == NULL) {
    SPVM_RUNTIME_WEAKEN_BACKREF* new_weaken_backref = SPVM_RUNTIME_API_alloc_memory_block_zero(env, sizeof(SPVM_RUNTIME_WEAKEN_BACKREF));
    new_weaken_backref->object_address = object_address;
    object->weaken_backref_head = new_weaken_backref;
  }
  // Add weaken_back_ref
  else {
    SPVM_RUNTIME_WEAKEN_BACKREF* weaken_backref_next = object->weaken_backref_head;

    SPVM_RUNTIME_WEAKEN_BACKREF* new_weaken_backref = SPVM_RUNTIME_API_alloc_memory_block_zero(env, sizeof(SPVM_RUNTIME_WEAKEN_BACKREF));
    new_weaken_backref->object_address = object_address;
    
    while (weaken_backref_next->next != NULL){
      weaken_backref_next = weaken_backref_next->next;
    }
    weaken_backref_next->next = new_weaken_backref;
  }
  
  // Weaken is implemented by tag pointer.
  // If pointer most right bit is 1, object is weaken.
  *object_address = (SPVM_OBJECT*)((intptr_t)*object_address | 1);
}

void SPVM_RUNTIME_API_unweaken(SPVM_ENV* env, SPVM_OBJECT** object_address) {
  (void)env;

  assert(object_address);
  
  if (*object_address == NULL) {
    return;
  }
  
  if (!SPVM_RUNTIME_API_isweak(env, object_address)) {
    return;
  }
  
  // Unweaken
  *object_address = (SPVM_OBJECT*)((intptr_t)*object_address & ~(intptr_t)1);
  
  SPVM_OBJECT* object = *object_address;
  
  // Increment reference count
  object->ref_count++;
  
  // Remove weaken back ref
  SPVM_RUNTIME_WEAKEN_BACKREF** weaken_backref_next_address = &object->weaken_backref_head;
  assert(*weaken_backref_next_address);
  while ((*weaken_backref_next_address)->next != NULL){
    if ((*weaken_backref_next_address)->next->object_address == object_address) {
      SPVM_RUNTIME_API_free_memory_block(env, (*weaken_backref_next_address)->next);
      *weaken_backref_next_address = (*weaken_backref_next_address)->next->next;
      break;
    }
    *weaken_backref_next_address = (*weaken_backref_next_address)->next;
  }
}

void SPVM_RUNTIME_API_set_exception(SPVM_ENV* env, SPVM_OBJECT* exception) {
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (env->exception_object != NULL) {
    SPVM_RUNTIME_API_dec_ref_count(env, (SPVM_OBJECT*)env->exception_object);
  }
  
  SPVM_RUNTIME_API_OBJECT_ASSIGN(&env->exception_object, exception);
  
  if (env->exception_object != NULL) {
    ((SPVM_OBJECT*)env->exception_object)->ref_count++;
  }
}

SPVM_OBJECT* SPVM_RUNTIME_API_exception(SPVM_ENV* env) {
  (void)env;
  
  return env->exception_object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_barray(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_barray_raw(env, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_sarray(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_sarray_raw(env, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_iarray(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_iarray_raw(env, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_larray(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_larray_raw(env, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_farray(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_farray_raw(env, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_darray(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_darray_raw(env, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_oarray(SPVM_ENV* env, int32_t basic_type_id, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_oarray_raw(env, basic_type_id, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_marray(SPVM_ENV* env, int32_t basic_type_id, int32_t element_dimension, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_marray_raw(env, basic_type_id, element_dimension, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_varray(SPVM_ENV* env, int32_t basic_type_id, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_varray_raw(env, basic_type_id, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_obj(SPVM_ENV* env, int32_t basic_type_id) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_obj_raw(env, basic_type_id);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_pointer(SPVM_ENV* env, int32_t basic_type_id, void* pointer) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_pointer_raw(env, basic_type_id, pointer);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_str(SPVM_ENV* env, const char* bytes, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_str_raw(env, bytes, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_barray_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  // If lenght is less than 0, return NULL.
  if (length < 0) {
    return NULL;
  }
  
  // Create object
  SPVM_RUNTIME* runtime = env->runtime;

  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE_byte) * (length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(env, alloc_byte_size);

  object->type_dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_BYTE;
  object->array_length = length;
  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_sarray_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = env->runtime;

  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE_short) * (length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(env, alloc_byte_size);
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_SHORT;
  
  // Set array length
  object->array_length = length;

  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY;

  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_iarray_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = env->runtime;
  
  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE_int) * (length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(env, alloc_byte_size);
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_INT;

  // Set array length
  object->array_length = length;

  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_larray_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (length < 0) {
    return NULL;
  }
  
  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE_long) * (length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(env, alloc_byte_size);
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_LONG;

  // Set array length
  object->array_length = length;

  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_farray_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = env->runtime;

  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE_float) * (length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(env, alloc_byte_size);
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_FLOAT;

  // Set array length
  object->array_length = length;

  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_darray_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = env->runtime;
  
  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE_double) * (length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(env, alloc_byte_size);
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_DOUBLE;
  
  // Set array length
  object->array_length = length;

  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_oarray_raw(SPVM_ENV* env, int32_t basic_type_id, int32_t length) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;

  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + sizeof(void*) * (length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(env, alloc_byte_size);

  for (int32_t index = 0; index < length; index++) {
    SPVM_OBJECT* ofield = ((SPVM_OBJECT**)((intptr_t)object + env->object_header_byte_size))[index];
  }

  SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];

  object->basic_type_id = basic_type->id;
  object->type_dimension = 1;

  // Set array length
  object->array_length = length;
  
  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_OBJECT_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_marray_raw(SPVM_ENV* env, int32_t basic_type_id, int32_t element_dimension, int32_t length) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE_object) * (length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(env, alloc_byte_size);
  
  object->basic_type_id = basic_type_id;
  object->type_dimension = element_dimension + 1;
  
  // Set array length
  object->array_length = length;
  
  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_OBJECT_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_varray_raw(SPVM_ENV* env, int32_t basic_type_id, int32_t length) {
  (void)env;

  SPVM_RUNTIME* runtime = env->runtime;

  // valut_t array dimension must be 1
  SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
  const char* basic_type_name = &runtime->string_pool[basic_type->name_id];
  
  // Package
  SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
  int32_t fields_length = package->fields_length;
  SPVM_RUNTIME_FIELD* field_first = &runtime->fields[package->fields_base];
  int32_t field_basic_type_id = field_first->basic_type_id;

  int32_t unit_size;
  if (field_basic_type_id == SPVM_BASIC_TYPE_C_ID_BYTE) {
    unit_size = sizeof(int8_t);
  }
  else if (field_basic_type_id == SPVM_BASIC_TYPE_C_ID_SHORT) {
    unit_size = sizeof(int16_t);
  }
  else if (field_basic_type_id == SPVM_BASIC_TYPE_C_ID_INT) {
    unit_size = sizeof(int32_t);
  }
  else if (field_basic_type_id == SPVM_BASIC_TYPE_C_ID_LONG) {
    unit_size = sizeof(int64_t);
  }
  else if (field_basic_type_id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
    unit_size = sizeof(float);
  }
  else if (field_basic_type_id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
    unit_size = sizeof(double);
  }
  else {
    assert(0);
  }

  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + unit_size * fields_length * (length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(env, alloc_byte_size);

  object->basic_type_id = basic_type->id;
  object->type_dimension = 1;

  // Set array length
  object->array_length = length;

  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_VALUE_ARRAY;

  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_obj_raw(SPVM_ENV* env, int32_t basic_type_id) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
  
  SPVM_RUNTIME_PACKAGE* package;
  if (basic_type->package_id < 0) {
    package = NULL;
  }
  else {
    package = &runtime->packages[basic_type->package_id];
  }
  if (!package) {
    return NULL;
  }

  // Alloc body length + 1
  int32_t fields_length = package->fields_length;

  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE) * (fields_length + 1);
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(env, alloc_byte_size);
  
  object->basic_type_id = basic_type->id;
  object->type_dimension = 0;

  object->array_length = fields_length;

  // Object type id
  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_PACKAGE;
  
  // Has destructor
  if (package->destructor_sub_id >= 0) {
    object->has_destructor = 1;
  }
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_pointer_raw(SPVM_ENV* env, int32_t basic_type_id, void* pointer) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];

  SPVM_RUNTIME_PACKAGE* package;
  if (basic_type->package_id < 0) {
    package = NULL;
  }
  else {
    package = &runtime->packages[basic_type->package_id];
  }
  if (!package) {
    return NULL;
  }

  int64_t alloc_byte_size = (intptr_t)env->object_header_byte_size + sizeof(void*);
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(env, alloc_byte_size);
  
  *(void**)((intptr_t)object + (intptr_t)env->object_header_byte_size) = pointer;

  object->basic_type_id = basic_type->id;
  object->type_dimension = 0;

  object->array_length = 0;

  // Object type id
  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_PACKAGE;
  
  // Has destructor
  if (package->destructor_sub_id >= 0) {
    object->has_destructor = 1;
  }
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_str_raw(SPVM_ENV* env, const char* bytes, int32_t length) {
  (void)env;
  
  if (length == 0) {
    length = strlen((char*)bytes);
  }

  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_barray_raw(env, length);
  
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_BYTE;
  object->type_dimension = 1;
  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY;
  
  if (length > 0) {
    if (bytes == NULL) {
      memset((void*)((intptr_t)object + env->object_header_byte_size), 0, length);
    }
    else {
      memcpy((void*)((intptr_t)object + env->object_header_byte_size), (char*)bytes, length);
    }
  }

  return object;
}

int32_t SPVM_RUNTIME_API_len(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return object->array_length;
}

int8_t* SPVM_RUNTIME_API_belems(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;

  return (SPVM_VALUE_byte*)((intptr_t)object + env->object_header_byte_size);
}

int16_t* SPVM_RUNTIME_API_selems(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return (SPVM_VALUE_short*)((intptr_t)object + env->object_header_byte_size);
}

int32_t* SPVM_RUNTIME_API_ielems(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return (SPVM_VALUE_int*)((intptr_t)object + env->object_header_byte_size);
}

int64_t* SPVM_RUNTIME_API_lelems(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return (SPVM_VALUE_long*)((intptr_t)object + env->object_header_byte_size);
}

float* SPVM_RUNTIME_API_felems(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return (SPVM_VALUE_float*)((intptr_t)object + env->object_header_byte_size);
}

double* SPVM_RUNTIME_API_delems(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return (SPVM_VALUE_double*)((intptr_t)object + env->object_header_byte_size);
}

SPVM_OBJECT* SPVM_RUNTIME_API_oelems(SPVM_ENV* env, SPVM_OBJECT* array, int32_t index) {
  (void)env;
  
  SPVM_OBJECT* oval = SPVM_RUNTIME_API_GET_OBJECT_NO_WEAKEN_ADDRESS(((SPVM_VALUE_object*)((intptr_t)array + env->object_header_byte_size))[index]);
  
  return oval;
}

void SPVM_RUNTIME_API_set_oelems(SPVM_ENV* env, SPVM_OBJECT* array, int32_t index, SPVM_OBJECT* oval) {
  (void)env;
  
  void* object_address = &((SPVM_VALUE_object*)((intptr_t)array + env->object_header_byte_size))[index];
  
  SPVM_RUNTIME_API_OBJECT_ASSIGN(object_address, oval);
}

void* SPVM_RUNTIME_API_pointer(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return *(void**)((intptr_t)object + (intptr_t)env->object_header_byte_size);
}

void SPVM_RUNTIME_API_dec_ref_count(SPVM_ENV* env, SPVM_OBJECT* object) {
  
  assert(object != NULL);
  assert(object->ref_count > 0);
  
  // Not weakened
  assert((((intptr_t)object) & 1) == 0);
  
  if (object->ref_count < 1) {
    fprintf(stderr, "Found invalid reference count object(SPVM_RUNTIME_API_dec_ref_count())");
    abort();
  }
  
  // Decrement reference count
  object->ref_count--;
  
  // If reference count is zero, free address.
  if (object->ref_count == 0) {
    SPVM_RUNTIME* runtime = env->runtime;
    
    SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[object->basic_type_id];
    SPVM_RUNTIME_PACKAGE* package;
    if (basic_type->package_id < 0) {
      package = NULL;
    }
    else {
      package = &runtime->packages[basic_type->package_id];
    }
    int32_t is_pointer = 0;
    if (package) {
      if (package->flag & SPVM_PACKAGE_C_FLAG_POINTER) {
        is_pointer = 1;
      }
    }

    if (object->runtime_type == SPVM_TYPE_C_RUNTIME_TYPE_OBJECT_ARRAY) {
      int32_t length = object->array_length;
      for (int32_t index = 0; index < length; index++) {
        SPVM_OBJECT** ofield_address = &(((SPVM_OBJECT**)((intptr_t)object + env->object_header_byte_size))[index]);

        if (*ofield_address != NULL) {
          // If object is weak, unweaken
          if (SPVM_RUNTIME_API_isweak(env, ofield_address)) {
            SPVM_RUNTIME_API_unweaken(env, ofield_address);
            (*ofield_address)->ref_count--;
          }
          else {
            SPVM_RUNTIME_API_dec_ref_count(env, *ofield_address);
          }
        }
      }
    }
    else if (object->runtime_type == SPVM_TYPE_C_RUNTIME_TYPE_PACKAGE) {
      
      if (object->has_destructor) {
        if (object->in_destroy) {
          return;
        }
        else {
          // Call destructor
          SPVM_VALUE args[1];
          args[0].oval = object;
          object->in_destroy = 1;
          SPVM_RUNTIME_API_call_sub(env, package->destructor_sub_id, args);
          object->in_destroy = 0;
          
          if (object->ref_count < 0) {
            printf("object reference count become minus in DESTROY()\n");
            abort();
          }
        }
      }
      
      int32_t object_fields_offset = package->object_fields_offset;
      int32_t object_fields_length = package->object_fields_length;
      
      for (int32_t index = 0; index < object_fields_length; index++) {
        SPVM_OBJECT** ofield_address = &(((SPVM_OBJECT**)((intptr_t)object + (intptr_t)env->object_header_byte_size + object_fields_offset))[index]);
        if (*ofield_address != NULL) {
          // If object is weak, unweaken
          if (SPVM_RUNTIME_API_isweak(env, ofield_address)) {
            SPVM_RUNTIME_API_unweaken(env, ofield_address);
            (*ofield_address)->ref_count--;
          }
          else {
            SPVM_RUNTIME_API_dec_ref_count(env, *ofield_address);
          }
        }
      }
    }
    if (object->weaken_backref_head != NULL) {
      SPVM_RUNTIME_API_free_weaken_back_refs(env, object->weaken_backref_head);
      object->weaken_backref_head = NULL;
    }
    
    // Free object
    SPVM_RUNTIME_API_free_memory_block(env, object);
  }
}

void SPVM_RUNTIME_API_inc_ref_count(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  if (object != NULL) {
    assert(object->ref_count >= 0);
    // Increment reference count
    object->ref_count++;
  }
}

int32_t SPVM_RUNTIME_API_ref_count(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return object->ref_count;
}

int32_t SPVM_RUNTIME_API_field_offset(SPVM_ENV* env, int32_t field_id) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
  
  return field->offset;
}

SPVM_RUNTIME_FIELD* SPVM_RUNTIME_API_field(SPVM_ENV* env, SPVM_RUNTIME_PACKAGE* package, const char* field_name) {
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;

  // Find fieldroutine by binary search
  int32_t fields_length = package->fields_length;
  int32_t fields_base = package->fields_base;
  SPVM_RUNTIME_FIELD* field = NULL;
  int low = fields_base;
  int high = fields_base + fields_length - 1;
  while (low < high) {
    int32_t middle = (low + high) / 2;
    SPVM_RUNTIME_FIELD* middle_field = &runtime->fields[middle];
    const char* middle_field_name = &runtime->string_pool[middle_field->name_id];
    
    if (strcmp(field_name, middle_field_name) > 0) {
      low = middle + 1;
    }
    else if (strcmp(field_name, middle_field_name) < 0) {
      high = middle - 1;
    }
    else {
      field = middle_field;
      break;
    }
  }
  if (field == NULL) {
    SPVM_RUNTIME_FIELD* low_field = &runtime->fields[low];
    const char* low_field_name = &runtime->string_pool[low_field->name_id];
    if (strcmp(field_name, low_field_name) == 0) {
      field = low_field;
    }
  }
  
  return field;
}

int32_t SPVM_RUNTIME_API_field_id(SPVM_ENV* env, const char* package_name, const char* field_name, const char* signature) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  
  // Basic type
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name);
  if (!basic_type) {
    return -1;
  }
  
  if (basic_type->package_id < 0) {
    return -1;
  }
  
  // Package
  SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_RUNTIME_API_field(env, package, field_name);
  if (!field) {
    return -1;
  }

  // Signature
  if (strcmp(signature, &runtime->string_pool[field->signature_id]) != 0) {
    return -1;
  }
  
  int32_t field_id = field->id;
  
  return field_id;
}

SPVM_RUNTIME_PACKAGE_VAR* SPVM_RUNTIME_API_package_var(SPVM_ENV* env, SPVM_RUNTIME_PACKAGE* package, const char* package_var_name) {
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;

  // Find package_varroutine by binary search
  int32_t package_vars_length = package->package_vars_length;
  int32_t package_vars_base = package->package_vars_base;
  
  SPVM_RUNTIME_PACKAGE_VAR* package_var = NULL;
  int low = package_vars_base;
  int high = package_vars_base + package_vars_length - 1;
  while (low < high) {
    int32_t middle = (low + high) / 2;
    
    SPVM_RUNTIME_PACKAGE_VAR* middle_package_var = &runtime->package_vars[middle];
    const char* middle_package_var_name = &runtime->string_pool[middle_package_var->name_id];
    
    if (strcmp(package_var_name, middle_package_var_name) > 0) {
      low = middle + 1;
    }
    else if (strcmp(package_var_name, middle_package_var_name) < 0) {
      high = middle - 1;
    }
    else {
      package_var = middle_package_var;
      break;
    }
  }
  if (package_var == NULL) {
    SPVM_RUNTIME_PACKAGE_VAR* low_package_var = &runtime->package_vars[low];
    const char* low_package_var_name = &runtime->string_pool[low_package_var->name_id];
    if (strcmp(package_var_name, low_package_var_name) == 0) {
      package_var = low_package_var;
    }
  }
  
  return package_var;
}

int32_t SPVM_RUNTIME_API_pkgvar_id(SPVM_ENV* env, const char* package_name, const char* package_var_name, const char* signature) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Basic type
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name);
  
  // Package name
  SPVM_RUNTIME_PACKAGE* package;
  if (basic_type->package_id < 0) {
    return -1;
  }
  else {
    package = &runtime->packages[basic_type->package_id];
  }

  // Package variable name
  SPVM_RUNTIME_PACKAGE_VAR* package_var = SPVM_RUNTIME_API_package_var(env, package, package_var_name);
  if (!package_var) {
    return -1;
  }
  
  // Signature
  if (strcmp(signature, &runtime->string_pool[package_var->signature_id]) != 0) {
    return -1;
  }
  
  return package_var->id;
}

SPVM_RUNTIME_SUB* SPVM_RUNTIME_API_sub(SPVM_ENV* env, SPVM_RUNTIME_PACKAGE* package, const char* sub_name) {
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;

  // Find subroutine by binary search
  int32_t subs_length = package->subs_length;
  int32_t subs_base = package->subs_base;
  SPVM_RUNTIME_SUB* sub = NULL;
  int low = subs_base;
  int high = subs_base + subs_length - 1;
  while (low < high) {
    int32_t middle = (low + high) / 2;
    SPVM_RUNTIME_SUB* middle_sub = &runtime->subs[middle];
    const char* middle_sub_name = &runtime->string_pool[middle_sub->name_id];
    
    if (strcmp(sub_name, middle_sub_name) > 0) {
      low = middle + 1;
    }
    else if (strcmp(sub_name, middle_sub_name) < 0) {
      high = middle - 1;
    }
    else {
      sub = middle_sub;
      break;
    }
  }
  if (sub == NULL) {
    SPVM_RUNTIME_SUB* low_sub = &runtime->subs[low];
    const char* low_sub_name = &runtime->string_pool[low_sub->name_id];
    if (strcmp(sub_name, low_sub_name) == 0) {
      sub = low_sub;
    }
  }
  
  return sub;
}

int32_t SPVM_RUNTIME_API_sub_id(SPVM_ENV* env, const char* package_name, const char* sub_name, const char* signature) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Sub id
  int32_t sub_id;
  
  // Basic type
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name);
  
  // Package name
  SPVM_RUNTIME_PACKAGE* package;
  if (basic_type->package_id < 0) {
    package = NULL;
  }
  else {
    package = &runtime->packages[basic_type->package_id];
  }
  
  if (package == NULL) {
    sub_id = -1;
  }
  else {
    int32_t subs_length = package->subs_length;
    int32_t subs_base = package->subs_base;
    
    if (subs_length == 0) {
      sub_id = -1;
    }
    else {
      // Sub
      SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);
      if (sub == NULL) {
        sub_id = -1;
      }
      else {
        // Signature
        if (strcmp(signature, &runtime->string_pool[sub->signature_id]) == 0) {
          sub_id = sub->id;
        }
        else {
          sub_id = -1;
        }
      }
    }
  }
  
  return sub_id;
}

int32_t SPVM_RUNTIME_API_method_sub_id(SPVM_ENV* env, SPVM_OBJECT* object, const char* sub_name, const char* signature) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Package name
  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = &runtime->basic_types[object->basic_type_id];
  SPVM_RUNTIME_PACKAGE* object_package;
  if (object_basic_type->package_id >= 0) {
    object_package = &runtime->packages[object_basic_type->package_id];
  }
  else {
    object_package = NULL;
  }
  
  if (object_package == NULL) {
    return 0;
  }
  
  // Package which have only anon sub
  int32_t sub_id;
  if (object_package->flag & SPVM_PACKAGE_C_FLAG_ANON_SUB_PACKAGE) {
    // Subroutine name
    SPVM_RUNTIME_SUB* sub = &runtime->subs[object_package->subs_base];
     
    // Signature
    if (strcmp(signature, &runtime->string_pool[sub->signature_id]) == 0) {
      sub_id = sub->id;
    }
    else {
      sub_id = 0;
    }
  }
  // Normal sub
  else {
    const char* object_package_name = &runtime->string_pool[object_package->name_id];
    sub_id = SPVM_RUNTIME_API_sub_id(env, object_package_name, sub_name, signature);
  }
  
  return sub_id;
}

SPVM_RUNTIME_BASIC_TYPE* SPVM_RUNTIME_API_basic_type(SPVM_ENV* env,  const char* basic_type_name) {
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;

  // Find basic_typeroutine by binary search
  int32_t basic_types_length = runtime->basic_types_length;
  int32_t basic_types_base = 0;
  SPVM_RUNTIME_BASIC_TYPE* basic_type = NULL;
  int low = basic_types_base;
  int high = basic_types_base + basic_types_length - 1;
  while (low < high) {
    int32_t middle = (low + high) / 2;
    SPVM_RUNTIME_BASIC_TYPE* middle_basic_type = &runtime->sorted_basic_types[middle];
    const char* middle_basic_type_name = &runtime->string_pool[middle_basic_type->name_id];
    
    if (strcmp(basic_type_name, middle_basic_type_name) > 0) {
      low = middle + 1;
    }
    else if (strcmp(basic_type_name, middle_basic_type_name) < 0) {
      high = middle - 1;
    }
    else {
      basic_type = middle_basic_type;
      break;
    }
  }
  if (basic_type == NULL) {
    SPVM_RUNTIME_BASIC_TYPE* low_basic_type = &runtime->sorted_basic_types[low];
    const char* low_basic_type_name = &runtime->string_pool[low_basic_type->name_id];
    if (strcmp(basic_type_name, low_basic_type_name) == 0) {
      basic_type = low_basic_type;
    }
  }
  
  return basic_type;
}

int32_t SPVM_RUNTIME_API_basic_type_id(SPVM_ENV* env, const char* basic_type_name) {
  (void)env;
  
  if (basic_type_name == NULL) {
    return -1;
  }
  
  SPVM_RUNTIME* runtime = env->runtime;

  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, basic_type_name);
  if (basic_type) {
    int32_t basic_type_id = basic_type->id;
    return basic_type_id;
  }
  else {
    return -1;
  }
}

int8_t SPVM_RUNTIME_API_bfield(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
  
  // Get field value
  SPVM_VALUE_byte value = *(SPVM_VALUE_byte*)((intptr_t)object + env->object_header_byte_size + field->offset);

  return value;
}

int16_t SPVM_RUNTIME_API_sfield(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
  
  // Get field value
  SPVM_VALUE_short value = *(SPVM_VALUE_short*)((intptr_t)object + env->object_header_byte_size + field->offset);
  
  return value;
}

int32_t SPVM_RUNTIME_API_ifield(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  SPVM_VALUE_int value = *(SPVM_VALUE_int*)((intptr_t)object + env->object_header_byte_size + field->offset);
  
  return value;
}

int64_t SPVM_RUNTIME_API_lfield(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  SPVM_VALUE_long value = *(SPVM_VALUE_long*)((intptr_t)object + env->object_header_byte_size + field->offset);
  
  return value;
}

float SPVM_RUNTIME_API_ffield(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  SPVM_VALUE_float value = *(SPVM_VALUE_float*)((intptr_t)object + env->object_header_byte_size + field->offset);
  
  return value;
}

double SPVM_RUNTIME_API_dfield(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  SPVM_VALUE_double value = *(SPVM_VALUE_double*)((intptr_t)object + env->object_header_byte_size + field->offset);
  
  return value;
}

SPVM_OBJECT* SPVM_RUNTIME_API_ofield(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
  
  // Get field value
  void* value = SPVM_RUNTIME_API_GET_OBJECT_NO_WEAKEN_ADDRESS(*(SPVM_VALUE_object*)((intptr_t)object + env->object_header_byte_size + field->offset));
  
  return value;
}

void SPVM_RUNTIME_API_set_bfield(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id, int8_t value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  *(SPVM_VALUE_byte*)((intptr_t)object + env->object_header_byte_size + field->offset) = value;
}

void SPVM_RUNTIME_API_set_sfield(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id, int16_t value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  *(SPVM_VALUE_short*)((intptr_t)object + env->object_header_byte_size + field->offset) = value;
}

void SPVM_RUNTIME_API_set_ifield(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id, int32_t value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  *(SPVM_VALUE_int*)((intptr_t)object + env->object_header_byte_size + field->offset) = value;
}

void SPVM_RUNTIME_API_set_lfield(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id, int64_t value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  *(SPVM_VALUE_long*)((intptr_t)object + env->object_header_byte_size + field->offset) = value;
}

void SPVM_RUNTIME_API_set_ffield(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id, float value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  *(SPVM_VALUE_float*)((intptr_t)object + env->object_header_byte_size + field->offset) = value;
}

void SPVM_RUNTIME_API_set_dfield(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id, double value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  *(SPVM_VALUE_double*)((intptr_t)object + env->object_header_byte_size + field->offset) = value;
}

void SPVM_RUNTIME_API_set_ofield(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id, SPVM_OBJECT* value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
  
  // Get field value
  void* ofield_address = (SPVM_VALUE_object*)((intptr_t)object + env->object_header_byte_size + field->offset);

  SPVM_RUNTIME_API_OBJECT_ASSIGN(ofield_address, value);
}

void* SPVM_RUNTIME_API_alloc_memory_block_zero(SPVM_ENV* env, int64_t byte_size) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  void* block = SPVM_RUNTIME_API_safe_malloc_zero(byte_size);
  runtime->memory_blocks_count++;
  
#ifdef SPVM_DEBUG_OBJECT_COUNT
  fprintf(stderr, "[INC_MEMORY_BLOCK_CNT] %d\n", runtime->memory_blocks_count);
#endif
  
  return block;
}

void SPVM_RUNTIME_API_free_memory_block(SPVM_ENV* env, void* block) {

  SPVM_RUNTIME* runtime = env->runtime;
  
  if (block) {
    free(block);
    runtime->memory_blocks_count--;
    
#ifdef SPVM_DEBUG_OBJECT_COUNT
    fprintf(stderr, "[INC_MEMORY_BLOCK_CNT] %d\n", runtime->memory_blocks_count);
#endif
  }
}

void* SPVM_RUNTIME_API_safe_malloc_zero(int64_t byte_size) {
  
  assert(byte_size > 0);
  
  if ((uint64_t)byte_size > SIZE_MAX) {
    fprintf(stderr, "Failed to allocate memory. Specified memroy size is too big\n");
    abort();
  }
  
  void* block = calloc(1, (size_t)byte_size);
  
  if (block == NULL) {
    fprintf(stderr, "Failed to allocate memory. calloc function return NULL\n");
    abort();
  }
  
  return block;
}

int8_t SPVM_RUNTIME_API_bpkgvar(SPVM_ENV* env, int32_t pkgvar_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Get field value
  int8_t value = runtime->package_vars_heap[pkgvar_id].bval;

  return value;
}

int16_t SPVM_RUNTIME_API_spkgvar(SPVM_ENV* env, int32_t pkgvar_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Get field value
  int16_t value = runtime->package_vars_heap[pkgvar_id].sval;

  return value;
}

int32_t SPVM_RUNTIME_API_ipkgvar(SPVM_ENV* env, int32_t pkgvar_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Get field value
  int32_t value = runtime->package_vars_heap[pkgvar_id].ival;

  return value;
}

int64_t SPVM_RUNTIME_API_lpkgvar(SPVM_ENV* env, int32_t pkgvar_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Get field value
  int64_t value = runtime->package_vars_heap[pkgvar_id].lval;

  return value;
}

float SPVM_RUNTIME_API_fpkgvar(SPVM_ENV* env, int32_t pkgvar_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Get field value
  float value = runtime->package_vars_heap[pkgvar_id].fval;

  return value;
}

double SPVM_RUNTIME_API_dpkgvar(SPVM_ENV* env, int32_t pkgvar_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Get field value
  double value = runtime->package_vars_heap[pkgvar_id].dval;

  return value;
}

SPVM_OBJECT* SPVM_RUNTIME_API_opkgvar(SPVM_ENV* env, int32_t pkgvar_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Get field value
  void* value = SPVM_RUNTIME_API_GET_OBJECT_NO_WEAKEN_ADDRESS(runtime->package_vars_heap[pkgvar_id].oval);
  
  return value;
}

void SPVM_RUNTIME_API_set_bpkgvar(SPVM_ENV* env, int32_t pkgvar_id, int8_t value) {
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Get field value
  runtime->package_vars_heap[pkgvar_id].bval = value;
}

void SPVM_RUNTIME_API_set_spkgvar(SPVM_ENV* env, int32_t pkgvar_id, int16_t value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Get field value
  runtime->package_vars_heap[pkgvar_id].sval = value;
}

void SPVM_RUNTIME_API_set_ipkgvar(SPVM_ENV* env, int32_t pkgvar_id, int32_t value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Get field value
  runtime->package_vars_heap[pkgvar_id].ival = value;
}

void SPVM_RUNTIME_API_set_lpkgvar(SPVM_ENV* env, int32_t pkgvar_id, int64_t value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Get field value
  runtime->package_vars_heap[pkgvar_id].lval = value;
}

void SPVM_RUNTIME_API_set_fpkgvar(SPVM_ENV* env, int32_t pkgvar_id, float value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Get field value
  runtime->package_vars_heap[pkgvar_id].fval = value;
}

void SPVM_RUNTIME_API_set_dpkgvar(SPVM_ENV* env, int32_t pkgvar_id, double value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Get field value
  runtime->package_vars_heap[pkgvar_id].dval = value;
}

void SPVM_RUNTIME_API_set_opkgvar(SPVM_ENV* env, int32_t pkgvar_id, SPVM_OBJECT* value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Get field value
  void* ofield_address = &runtime->package_vars_heap[pkgvar_id].oval;
  SPVM_RUNTIME_API_OBJECT_ASSIGN(ofield_address, value);
}
