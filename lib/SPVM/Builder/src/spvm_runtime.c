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
#include "spvm_opcode.h"
#include "spvm_object.h"
#include "spvm_util_allocator.h"

#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_runtime_allocator.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_package.h"
#include "spvm_runtime_sub.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_package_var.h"
#include "spvm_runtime_my.h"
#include "spvm_runtime_info_type.h"
#include "spvm_runtime_info_switch_info.h"
#include "spvm_runtime_info_case_info.h"
#include "spvm_portable.h"

// Only use for constant value
#include "spvm_type.h"
#include "spvm_package.h"
#include "spvm_package_var.h"
#include "spvm_sub.h"
#include "spvm_basic_type.h"
#include "spvm_field.h"

int32_t SPVM_RUNTIME_call_sub(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* stack) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;

  // Constant pool sub
  SPVM_RUNTIME_SUB* sub = &runtime->subs[sub_id];
  
  int32_t exception_flag = 0;
  if (sub->flag & SPVM_SUB_C_FLAG_HAVE_NATIVE_DESC) {
    int32_t original_mortal_stack_top = SPVM_RUNTIME_API_enter_scope(env);
    exception_flag = SPVM_RUNTIME_call_sub_native(env, sub_id, stack);
    SPVM_RUNTIME_API_leave_scope(env, original_mortal_stack_top);
  }
  else if (sub->flag & SPVM_SUB_C_FLAG_IS_COMPILED) {
    exception_flag = SPVM_RUNTIME_call_sub_precompile(env, sub_id, stack);
  }
  else {
    exception_flag = SPVM_RUNTIME_call_sub_vm(env, sub_id, stack);
  }
  
  // Set default exception message
  if (exception_flag && runtime->exception == NULL) {
    void* exception = env->new_string_raw(env, "Error", 0);
    env->set_exception(env, exception);
  }
  
  return exception_flag;
}

int32_t SPVM_RUNTIME_call_sub_precompile(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* stack) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;

  // Constant pool sub
  SPVM_RUNTIME_SUB* sub = &runtime->subs[sub_id];

  // Subroutine is Precompile
  assert(sub->flag & SPVM_SUB_C_FLAG_IS_COMPILED);
  
  // Call precompile subroutine
  int32_t (*precompile_address)(SPVM_ENV*, SPVM_VALUE*) = runtime->sub_precompile_addresses[sub->id];
  return (*precompile_address)(env, stack);
}

int32_t SPVM_RUNTIME_call_sub_native(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* stack) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;

  // Constant pool sub
  SPVM_RUNTIME_SUB* sub = &runtime->subs[sub_id];

  // Subroutine is native
  assert(sub->flag & SPVM_SUB_C_FLAG_HAVE_NATIVE_DESC);

  // Call native subrotuine
  int32_t (*native_address)(SPVM_ENV*, SPVM_VALUE*) = runtime->sub_native_addresses[sub->id];
  return (*native_address)(env, stack);
}

int32_t SPVM_RUNTIME_call_sub_vm(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* stack) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;

  // Runtime subroutine
  SPVM_RUNTIME_SUB* sub = &runtime->subs[sub_id];
  
  // Runtime package
  SPVM_RUNTIME_PACKAGE* package = &runtime->packages[sub->package_id];

  // Operation codes
  SPVM_OPCODE* opcodes = runtime->opcodes;
  
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

  // Exception flag
  int32_t exception_flag = 0;

  // Operation code base
  int32_t sub_opcodes_base = sub->opcodes_base;

  // Call subroutine argument stack top
  int32_t call_sub_arg_stack_top = 0;
  
  // Mortal stack
  int32_t* mortal_stack = NULL;
  int32_t mortal_stack_top = 0;

  // Condition flag
  register int32_t condition_flag = 0;
  
  // Opcode relative index
  register int32_t opcode_rel_index = 0;

  // short variables
  SPVM_VALUE_short* short_vars = NULL;
  int32_t short_vars_alloc_length = sub->short_vars_alloc_length;
  
  // byte variables
  SPVM_VALUE_byte* byte_vars = NULL;
  int32_t byte_vars_alloc_length = sub->byte_vars_alloc_length;
  
  // Buffer for string convertion
  char string_convert_buffer[30];
  
  // Alloc memory
  if (sub->object_vars_alloc_length > 0) {
    object_vars = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(void*) * sub->object_vars_alloc_length);
  }
  if (sub->double_vars_alloc_length > 0) {
    double_vars = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_VALUE_double) * sub->double_vars_alloc_length);
  }
  if (sub->ref_vars_alloc_length > 0) {
    ref_vars = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(void*) * sub->ref_vars_alloc_length);
  }
  if (sub->long_vars_alloc_length > 0) {
    long_vars = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_VALUE_long) * sub->long_vars_alloc_length);
  }
  if (sub->float_vars_alloc_length > 0) {
    float_vars = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_VALUE_float) * sub->float_vars_alloc_length);
  }
  if (sub->int_vars_alloc_length > 0) {
    int_vars = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_VALUE_int) * sub->int_vars_alloc_length);
  }
  if (short_vars_alloc_length > 0) {
    short_vars = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_VALUE_short) * short_vars_alloc_length);
  }
  if (byte_vars_alloc_length > 0) {
    byte_vars = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_VALUE_byte) * byte_vars_alloc_length);
  }

  {
    int32_t stack_index = 0;
    for (int32_t arg_index = sub->arg_ids_base; arg_index < sub->arg_ids_base + sub->arg_ids_length; arg_index++) {
      SPVM_RUNTIME_MY* arg = &runtime->args[arg_index];
      
      int32_t arg_width;
      if (SPVM_RUNTIME_API_is_numeric_type(env, arg->basic_type_id, arg->type_dimension, arg->type_flag)) {
        arg_width = 1;
        switch (arg->basic_type_id) {
          case SPVM_BASIC_TYPE_C_ID_BYTE: {
            byte_vars[arg->byte_var_id] = *(SPVM_VALUE_byte*)&stack[stack_index];
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_SHORT: {
            short_vars[arg->short_var_id] = *(SPVM_VALUE_short*)&stack[stack_index];
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_INT: {
            int_vars[arg->int_var_id] = *(SPVM_VALUE_int*)&stack[stack_index];
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_LONG: {
            long_vars[arg->long_var_id] = *(SPVM_VALUE_long*)&stack[stack_index];
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_FLOAT: {
            float_vars[arg->float_var_id] = *(SPVM_VALUE_float*)&stack[stack_index];
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
            double_vars[arg->double_var_id] = *(SPVM_VALUE_double*)&stack[stack_index];
            break;
          }
          default: {
            assert(0);
            break;
          }
        }
      }
      else if (SPVM_RUNTIME_API_is_value_type(env, arg->basic_type_id, arg->type_dimension, arg->type_flag)) {
        arg_width = SPVM_RUNTIME_API_get_width(env, arg->basic_type_id, arg->type_dimension, arg->type_flag);
        switch (arg->value_field_basic_type_id) {
          case SPVM_BASIC_TYPE_C_ID_BYTE: {
            for (int32_t field_index = 0; field_index < arg_width; field_index++) {
              byte_vars[arg->byte_var_id + field_index] = *(SPVM_VALUE_byte*)&stack[stack_index + field_index];
            }
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_SHORT: {
            for (int32_t field_index = 0; field_index < arg_width; field_index++) {
              short_vars[arg->short_var_id + field_index] = *(SPVM_VALUE_short*)&stack[stack_index + field_index];
            }
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_INT: {
            for (int32_t field_index = 0; field_index < arg_width; field_index++) {
              int_vars[arg->int_var_id + field_index] = *(SPVM_VALUE_int*)&stack[stack_index + field_index];
            }
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_LONG: {
            for (int32_t field_index = 0; field_index < arg_width; field_index++) {
              long_vars[arg->long_var_id + field_index] = *(SPVM_VALUE_long*)&stack[stack_index + field_index];
            }
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_FLOAT: {
            for (int32_t field_index = 0; field_index < arg_width; field_index++) {
              float_vars[arg->float_var_id + field_index] = *(SPVM_VALUE_float*)&stack[stack_index + field_index];
            }
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
            for (int32_t field_index = 0; field_index < arg_width; field_index++) {
              double_vars[arg->double_var_id + field_index] = *(SPVM_VALUE_double*)&stack[stack_index + field_index];
            }
            break;
          }
          default: {
            assert(0);
          }
        }
      }
      else if (SPVM_RUNTIME_API_is_object_type(env, arg->basic_type_id, arg->type_dimension, arg->type_flag)) {
        arg_width = 1;
        object_vars[arg->object_var_id] = *(void**)&stack[stack_index];
      }
      else if (SPVM_RUNTIME_API_is_ref_type(env, arg->basic_type_id, arg->type_dimension, arg->type_flag)) {
        arg_width = 1;
        ref_vars[arg->ref_var_id] = *(void**)&stack[stack_index];
      }
      else {
        assert(0);
      }
      
      // If arg is object, increment reference count
      if (SPVM_RUNTIME_API_is_object_type(env, arg->basic_type_id, arg->type_dimension, arg->type_flag)) {
        void* object = *(void**)&object_vars[arg->address_var_id];
        if (object != NULL) {
          SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(object);
        }
      }
      
      stack_index += arg_width;
    }
  }
  
  // Mortal stack
  if (sub->mortal_stack_length > 0) {
    mortal_stack = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(int32_t) * sub->mortal_stack_length);
  }
  
  while (1) {
    SPVM_OPCODE* opcode = &(opcodes[sub_opcodes_base + opcode_rel_index]);
    
    int32_t opcode_id = __builtin_expect(opcode->id == SPVM_OPCODE_C_ID_WIDE, 0) ? 255 + opcode->operand3 : opcode->id;
    
    switch (opcode_id) {
      case SPVM_OPCODE_C_ID_BOOL_INT:
        condition_flag = !!int_vars[opcode->operand0];
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
      case SPVM_OPCODE_C_ID_ISA_OBJECT: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t rel_id = opcode->operand1;
        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[sub->info_types_base + rel_id];
        int32_t check_basic_type_id = type->basic_type_id;
        int32_t check_type_dimension = type->dimension;
        
        if (object) {
          int32_t object_basic_type_id = *(int32_t*)(object + (intptr_t)env->object_basic_type_id_byte_offset);
          int32_t object_type_dimension = *(int32_t*)(object + (intptr_t)env->object_type_dimension_byte_offset);
          condition_flag = (object_basic_type_id == check_basic_type_id && object_type_dimension == check_type_dimension);
        }
        else {
          condition_flag = 0;
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_ISA_INTERFACE: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t rel_id = opcode->operand1;
        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[sub->info_types_base + rel_id];
        int32_t check_basic_type_id = type->basic_type_id;
        int32_t check_type_dimension = type->dimension;
        
        if (object) {
          int32_t object_basic_type_id = *(int32_t*)(object + (intptr_t)env->object_basic_type_id_byte_offset);
          int32_t object_type_dimension = *(int32_t*)(object + (intptr_t)env->object_type_dimension_byte_offset);
          condition_flag = env->has_interface(env, object_basic_type_id, object_type_dimension, check_basic_type_id, check_type_dimension);
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

        int32_t length1 = *(SPVM_VALUE_int*)((intptr_t)object1 + (intptr_t)env->object_elements_length_byte_offset);
        int32_t length2 = *(SPVM_VALUE_int*)((intptr_t)object2 + (intptr_t)env->object_elements_length_byte_offset);
        
        SPVM_VALUE_byte* bytes1 = *(SPVM_VALUE_byte**)&(*(void**)object1);
        SPVM_VALUE_byte* bytes2 = *(SPVM_VALUE_byte**)&(*(void**)object2);
        
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
          void* exception = env->new_string_raw(env, "0 division", 0);
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
          void* exception = env->new_string_raw(env, "0 division", 0);
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
          void* exception = env->new_string_raw(env, "0 division", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int_vars[opcode->operand0] = int_vars[opcode->operand1] % int_vars[opcode->operand2];
        }
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_LONG:
        if (__builtin_expect(long_vars[opcode->operand2] == 0, 0)) {
          void* exception = env->new_string_raw(env, "0 division", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          long_vars[opcode->operand0] = long_vars[opcode->operand1] % long_vars[opcode->operand2];
        }
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_FLOAT:
        float_vars[opcode->operand0]
          = (float)remainderf(float_vars[opcode->operand1], float_vars[opcode->operand2]);
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_DOUBLE:
        double_vars[opcode->operand0]
          = remainder(double_vars[opcode->operand1], double_vars[opcode->operand2]);
        break;
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_INT:
        int_vars[opcode->operand0]
          = int_vars[opcode->operand1] << (int_vars[opcode->operand2] & 0x1f);
        break;
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_LONG:
        long_vars[opcode->operand0]
          = long_vars[opcode->operand1] << (int_vars[opcode->operand2] & 0x3f);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_INT:
        int_vars[opcode->operand0]
          = int_vars[opcode->operand1] >> (int_vars[opcode->operand2] & 0x1f);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_LONG:
        long_vars[opcode->operand0]
          = long_vars[opcode->operand1] >> (int_vars[opcode->operand2] & 0x3f);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_UNSIGNED_INT:
        int_vars[opcode->operand0]
          = (int32_t)((uint32_t)int_vars[opcode->operand1] >> (int_vars[opcode->operand2] & 0x1f));
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_UNSIGNED_LONG:
        long_vars[opcode->operand0]
          = (int64_t)((uint64_t)long_vars[opcode->operand1] >> (int_vars[opcode->operand2] & 0x3f));
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
      case SPVM_OPCODE_C_ID_COMPLEMENT_INT:
        int_vars[opcode->operand0] = ~int_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_COMPLEMENT_LONG:
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
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_STRING:
      {
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_STRING:
            sprintf(string_convert_buffer, "%" PRId8, byte_vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_STRING:
            sprintf(string_convert_buffer, "%" PRId16, short_vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_INT_TO_STRING:
            sprintf(string_convert_buffer, "%" PRId32, int_vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_STRING:
            sprintf(string_convert_buffer, "%" PRId64, long_vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_STRING:
            sprintf(string_convert_buffer, "%g", float_vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_STRING:
            sprintf(string_convert_buffer, "%g", double_vars[opcode->operand1]);
            break;
        }
        
        int32_t string_length = strlen(string_convert_buffer);
        void* string = env->new_string_raw(env, string_convert_buffer, string_length);
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], string);

        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_UNDEF:
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], NULL);
        break;
      case SPVM_OPCODE_C_ID_GET_CONSTANT_BYTE:
        byte_vars[opcode->operand0] = *(SPVM_VALUE_byte*)&opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_GET_CONSTANT_SHORT:
        short_vars[opcode->operand0] = *(SPVM_VALUE_short*)&opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_GET_CONSTANT_INT:
        int_vars[opcode->operand0] = *(SPVM_VALUE_int*)&opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_GET_CONSTANT_LONG: {
        int32_t rel_id = opcode->operand2;
        int64_t long_value = runtime->info_long_values[sub->info_long_values_base + rel_id];
        long_vars[opcode->operand0] = long_value;
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_FLOAT:
        float_vars[opcode->operand0] = *(float*)&opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_GET_CONSTANT_DOUBLE: {
        int32_t rel_id = opcode->operand2;
        double double_value = runtime->info_double_values[sub->info_double_values_base + rel_id];
        double_vars[opcode->operand0] = double_value;
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_BYTE: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            byte_vars[opcode->operand0] = (*(SPVM_VALUE_byte**)&(*(void**)array))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_SHORT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            short_vars[opcode->operand0] = (*(SPVM_VALUE_short**)&(*(void**)array))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_INT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int_vars[opcode->operand0] = (*(SPVM_VALUE_int**)&(*(void**)array))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_LONG: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            long_vars[opcode->operand0] = (*(SPVM_VALUE_long**)&(*(void**)array))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_FLOAT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            float_vars[opcode->operand0] = (*(SPVM_VALUE_float**)&(*(void**)array))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_DOUBLE: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            double_vars[opcode->operand0] = (*(SPVM_VALUE_double**)&(*(void**)array))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_OBJECT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            void* object = (*(void***)&(*(void**)array))[index];
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], SPVM_RUNTIME_C_INLINE_GET_OBJECT_NO_WEAKEN_ADDRESS(object));
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_BYTE: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            (*(SPVM_VALUE_byte**)&(*(void**)array))[index] = byte_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_SHORT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
           (*(SPVM_VALUE_short**)&(*(void**)array))[index] = short_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_INT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            (*(SPVM_VALUE_int**)&(*(void**)array))[index] = int_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_LONG: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            (*(SPVM_VALUE_long**)&(*(void**)array))[index] = long_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_FLOAT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            (*(SPVM_VALUE_float**)&(*(void**)array))[index] = float_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_DOUBLE: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            (*(SPVM_VALUE_double**)&(*(void**)array))[index] = double_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_OBJECT: {
        
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            void* object_address = &((*(void***)&(*(void**)array))[index]);
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(object_address, *(void**)&object_vars[opcode->operand2]);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_UNDEF: {
        
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            void* object_address = &((*(void***)&(*(void**)array))[index]);
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(object_address, NULL);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_FETCH_BYTE: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t field_length = opcode->operand3;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              byte_vars[opcode->operand0 + field_index] = (*(SPVM_VALUE_byte**)&(*(void**)array))[field_length * index + field_index];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              short_vars[opcode->operand0 + field_index] = (*(SPVM_VALUE_short**)&(*(void**)array))[field_length * index + field_index];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              int_vars[opcode->operand0 + field_index] = (*(SPVM_VALUE_int**)&(*(void**)array))[field_length * index + field_index];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              long_vars[opcode->operand0 + field_index] = (*(SPVM_VALUE_long**)&(*(void**)array))[field_length * index + field_index];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              float_vars[opcode->operand0 + field_index] = (*(SPVM_VALUE_float**)&(*(void**)array))[field_length * index + field_index];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              double_vars[opcode->operand0 + field_index] = (*(SPVM_VALUE_double**)&(*(void**)array))[field_length * index + field_index];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            byte_vars[opcode->operand0] = (*(SPVM_VALUE_byte**)&(*(void**)array))[field_length * index + field_index];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            short_vars[opcode->operand0] = (*(SPVM_VALUE_short**)&(*(void**)array))[field_length * index + field_index];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int_vars[opcode->operand0] = (*(SPVM_VALUE_int**)&(*(void**)array))[field_length * index + field_index];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            long_vars[opcode->operand0] = (*(SPVM_VALUE_long**)&(*(void**)array))[field_length * index + field_index];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            float_vars[opcode->operand0] = (*(SPVM_VALUE_float**)&(*(void**)array))[field_length * index + field_index];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            double_vars[opcode->operand0] = (*(SPVM_VALUE_double**)&(*(void**)array))[field_length * index + field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_ARRAY_STORE_BYTE: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t field_length = opcode->operand3;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              (*(SPVM_VALUE_byte**)&(*(void**)array))[field_length * index + field_index] = byte_vars[opcode->operand2 + field_index];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              (*(SPVM_VALUE_short**)&(*(void**)array))[field_length * index + field_index] = short_vars[opcode->operand2 + field_index];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              (*(SPVM_VALUE_int**)&(*(void**)array))[field_length * index + field_index] = int_vars[opcode->operand2 + field_index];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              (*(SPVM_VALUE_long**)&(*(void**)array))[field_length * index + field_index] = long_vars[opcode->operand2 + field_index];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              (*(SPVM_VALUE_float**)&(*(void**)array))[field_length * index + field_index] = float_vars[opcode->operand2 + field_index];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < field_length; field_index++) {
              (*(SPVM_VALUE_double**)&(*(void**)array))[field_length * index + field_index] = double_vars[opcode->operand2 + field_index];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            (*(SPVM_VALUE_byte**)&(*(void**)array))[field_length * index + field_index] = byte_vars[opcode->operand2];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            (*(SPVM_VALUE_short**)&(*(void**)array))[field_length * index + field_index] = short_vars[opcode->operand2];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            (*(SPVM_VALUE_int**)&(*(void**)array))[field_length * index + field_index] = int_vars[opcode->operand2];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            (*(SPVM_VALUE_long**)&(*(void**)array))[field_length * index + field_index] = long_vars[opcode->operand2];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            (*(SPVM_VALUE_float**)&(*(void**)array))[field_length * index + field_index] = float_vars[opcode->operand2];
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
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            (*(SPVM_VALUE_double**)&(*(void**)array))[field_length * index + field_index] = double_vars[opcode->operand2];
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
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], *(void**)&object_vars[opcode->operand1]);
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
        assert(mortal_stack_top < sub->mortal_stack_length);
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
            if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(*object_address) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*object_address); }
            else { env->dec_ref_count(env, *object_address); }
          }
          
          *object_address = NULL;
        }
        
        mortal_stack_top = original_mortal_stack_top;
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT: {
        int32_t rel_id = opcode->operand1;
        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[sub->info_types_base + rel_id];
        int32_t basic_type_id = type->basic_type_id;
        
        void* object = env->new_object_raw(env, basic_type_id);
        
        // Push object
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_BYTE_ARRAY: {
        int32_t length = int_vars[opcode->operand1];
        if (length >= 0) {
          void* object = env->new_byte_array_raw(env, length);
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_string_raw(env, "Array length must be more than or equal to 0", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY: {
        
        // length
        int32_t length = int_vars[opcode->operand1];
        
        if (length >= 0) {
          void* object = env->new_short_array_raw(env, length);
          
          // Set array
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_string_raw(env, "Array length must be more than or equal to 0", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_INT_ARRAY: {
        
        // length
        int32_t length = int_vars[opcode->operand1];
        
        if (length >= 0) {
          void* object = env->new_int_array_raw(env, length);
          
          // Set array
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_string_raw(env, "Array length must be more than or equal to 0", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_LONG_ARRAY: {
        
        int32_t length = int_vars[opcode->operand1];
        if (length >= 0) {
          void* object = env->new_long_array_raw(env, length);
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_string_raw(env, "Array length must be more than or equal to 0", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY: {
        
        int32_t length = int_vars[opcode->operand1];
        if (length >= 0) {
          void* object = env->new_float_array_raw(env, length);
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_string_raw(env, "Array length must be more than or equal to 0", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY: {
        
        int32_t length = int_vars[opcode->operand1];
        if (length >= 0) {
          void* object = env->new_double_array_raw(env, length);
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_string_raw(env, "Array length must be more than or equal to 0", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY: {
        int32_t rel_id = opcode->operand1;
        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[sub->info_types_base + rel_id];
        int32_t basic_type_id = type->basic_type_id;
        
        int32_t length = int_vars[opcode->operand2];
        if (length >= 0) {
          void* object = env->new_object_array_raw(env, basic_type_id, length);
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_string_raw(env, "Array length must be more than or equal to 0", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULTI_ARRAY: {
        int32_t rel_id = opcode->operand1;
        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[sub->info_types_base + rel_id];
        int32_t basic_type_id = type->basic_type_id;
        int32_t element_dimension = type->dimension - 1;
        
        int32_t length = int_vars[opcode->operand2];
        if (length >= 0) {
          void* object = env->new_multi_array_raw(env, basic_type_id, element_dimension, length);
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_string_raw(env, "Array length must be more than or equal to 0", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_VALUE_ARRAY: {
        int32_t rel_id = opcode->operand1;
        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[sub->info_types_base + rel_id];
        int32_t basic_type_id = type->basic_type_id;
        
        // length
        int32_t length = int_vars[opcode->operand2];
        
        if (length >= 0) {
          void* object = env->new_value_t_array_raw(env, basic_type_id, length);
          
          // Set object
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_string_raw(env, "Array length must be more than or equal to 0", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING: {
        int32_t rel_id = opcode->operand2;
        const char* string_value = runtime->info_string_values[sub->info_string_values_base + rel_id];
        int32_t string_length = runtime->info_string_lengths[sub->info_string_values_base + rel_id];
        
        void* string = env->new_string_raw(env, string_value, string_length);
        
        // Set string
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0] , string);

        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LENGTH:
        if (*(void**)&object_vars[opcode->operand1] == NULL) {
          void* exception = env->new_string_raw(env, "Can't get array length of undef value.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int_vars[opcode->operand0] = *(SPVM_VALUE_int*)((intptr_t)*(void**)&object_vars[opcode->operand1] + (intptr_t)env->object_elements_length_byte_offset);
        }
        break;
      case SPVM_OPCODE_C_ID_WEAKEN_FIELD: {
        int32_t rel_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_index = field->index;
        void* object = *(void**)&object_vars[opcode->operand0];
        if (object == NULL) {
          SPVM_OBJECT* exception = env->new_string_raw(env, "Object to weaken an object field must not be undefined.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          void** object_field_address = (void**)&fields[field_index];
          env->weaken(env, object_field_address);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_WEAKEN_ARRAY_ELEMENT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_raw(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string_raw(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            void** elements = *(void***)&(*(void**)array);
            void** object_element_address = (void**)&elements[index];
            env->weaken(env, object_element_address);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_WEAKEN_SCALAR: {
        void* object = *(void**)&object_vars[opcode->operand1];
        env->weaken(env, &object);
        break;
      }
      case SPVM_OPCODE_C_ID_CONCAT: {
        
        void* string1 = *(void**)&object_vars[opcode->operand1];
        void* string2 = *(void**)&object_vars[opcode->operand2];
        if (string1 == NULL) {
          void* exception = env->new_string_raw(env, "\".\" operater left value must be defined", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else if (string2 == NULL) {
          void* exception = env->new_string_raw(env, "\".\" operater right value must be defined", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          void* string3 = env->concat(env, string1, string2);
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], string3);
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
          int32_t rel_id = opcode->operand2;
          SPVM_RUNTIME_INFO_TYPE* check_type = &runtime->info_types[sub->info_types_base + rel_id];
          int32_t check_basic_type_id = check_type->basic_type_id;
          int32_t check_type_dimension = check_type->dimension;
          
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);
          int32_t object_type_dimension_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);
          
          if (object_basic_type_id == check_basic_type_id && object_type_dimension_id == check_type_dimension) {
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], *(void**)&object_vars[opcode->operand1]);
          }
          else {
            void* exception = env->new_string_raw(env, "Can't convert imcompatible object type.", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_CHECK_INTERFACE_TYPE: {
        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (object != NULL) {
          int32_t rel_id = opcode->operand2;
          SPVM_RUNTIME_INFO_TYPE* interface_type = &runtime->info_types[sub->info_types_base + rel_id];
          int32_t interface_basic_type_id = interface_type->basic_type_id;
          int32_t interface_type_dimension = interface_type->dimension;
          
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);
          int32_t object_type_dimension_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);
          
          if (env->has_interface(env, object_basic_type_id, object_type_dimension_id, interface_basic_type_id, interface_type_dimension)) {
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], *(void**)&object_vars[opcode->operand1]);
          }
          else {
            void* exception = env->new_string_raw(env, "Can't convert imcompatible interface type.", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_VOID:
      {
        int32_t rel_id = opcode->operand1;
        int32_t call_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_BYTE:
      {
        int32_t rel_id = opcode->operand1;
        int32_t call_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
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
        int32_t rel_id = opcode->operand1;
        int32_t call_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          short_vars[opcode->operand0] = *(SPVM_VALUE_short*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_INT_TMP:
      {
        int32_t rel_id = opcode->operand1;
        int32_t call_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
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
        int32_t rel_id = opcode->operand1;
        int32_t call_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
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
        int32_t rel_id = opcode->operand1;
        int32_t call_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
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
        int32_t rel_id = opcode->operand1;
        int32_t call_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
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
        int32_t rel_id = opcode->operand1;
        int32_t call_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], stack[0].oval);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_BYTE:
      {
        int32_t rel_id = opcode->operand1;
        int32_t call_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t call_sub_return_type_field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < call_sub_return_type_field_length; field_index++) {
            byte_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_byte*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_SHORT:
      {
        int32_t rel_id = opcode->operand1;
        int32_t call_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t call_sub_return_type_field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < call_sub_return_type_field_length; field_index++) {
            short_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_short*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_INT:
      {
        int32_t rel_id = opcode->operand1;
        int32_t call_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t call_sub_return_type_field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < call_sub_return_type_field_length; field_index++) {
            int_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_int*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_LONG:
      {
        int32_t rel_id = opcode->operand1;
        int32_t call_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t call_sub_return_type_field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < call_sub_return_type_field_length; field_index++) {
            long_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_long*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_FLOAT:
      {
        int32_t rel_id = opcode->operand1;
        int32_t call_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t call_sub_return_type_field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < call_sub_return_type_field_length; field_index++) {
            float_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_float*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_VALUE_DOUBLE:
      {
        int32_t rel_id = opcode->operand1;
        int32_t call_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t call_sub_return_type_field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < call_sub_return_type_field_length; field_index++) {
            double_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_double*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_VOID:
      {
        int32_t rel_id = opcode->operand1;
        int32_t decl_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_signature = runtime->symbols[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_BYTE:
      {
        int32_t rel_id = opcode->operand1;
        int32_t decl_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_signature = runtime->symbols[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          byte_vars[opcode->operand0] = *(SPVM_VALUE_byte*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_SHORT:
      {
        int32_t rel_id = opcode->operand1;
        int32_t decl_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_signature = runtime->symbols[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          short_vars[opcode->operand0] = *(SPVM_VALUE_short*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_INT_TMP:
      {
        int32_t rel_id = opcode->operand1;
        int32_t decl_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_signature = runtime->symbols[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int_vars[opcode->operand0] = *(SPVM_VALUE_int*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_LONG:
      {
        int32_t rel_id = opcode->operand1;
        int32_t decl_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_signature = runtime->symbols[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          long_vars[opcode->operand0] = *(SPVM_VALUE_long*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_FLOAT:
      {
        int32_t rel_id = opcode->operand1;
        int32_t decl_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_signature = runtime->symbols[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          float_vars[opcode->operand0] = *(SPVM_VALUE_float*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_DOUBLE:
      {
        int32_t rel_id = opcode->operand1;
        int32_t decl_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_signature = runtime->symbols[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          double_vars[opcode->operand0] = *(SPVM_VALUE_double*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_OBJECT:
      {
        int32_t rel_id = opcode->operand1;
        int32_t decl_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_signature = runtime->symbols[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], stack[0].oval);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_BYTE:
      {
        int32_t rel_id = opcode->operand1;
        int32_t decl_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_signature = runtime->symbols[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t call_sub_return_type_field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < call_sub_return_type_field_length; field_index++) {
            byte_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_byte*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_SHORT:
      {
        int32_t rel_id = opcode->operand1;
        int32_t decl_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_signature = runtime->symbols[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t call_sub_return_type_field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < call_sub_return_type_field_length; field_index++) {
            short_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_short*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_INT:
      {
        int32_t rel_id = opcode->operand1;
        int32_t decl_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_signature = runtime->symbols[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t call_sub_return_type_field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < call_sub_return_type_field_length; field_index++) {
            int_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_int*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_FLOAT:
      {
        int32_t rel_id = opcode->operand1;
        int32_t decl_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_signature = runtime->symbols[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          int32_t call_sub_return_type_field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < call_sub_return_type_field_length; field_index++) {
            float_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_float*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_DOUBLE:
      {
        int32_t rel_id = opcode->operand1;
        int32_t decl_sub_id = runtime->info_sub_ids[sub->info_sub_ids_base + rel_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_signature = runtime->symbols[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        int32_t decl_sub_return_basic_type_id = decl_sub->return_basic_type_id;
        int32_t decl_sub_return_type_dimension = decl_sub->return_type_dimension;
        int32_t decl_sub_return_type_flag = decl_sub->return_type_flag;
        if (!exception_flag) {
          int32_t call_sub_return_type_field_length = opcode->operand3;
          for (int32_t field_index = 0; field_index < call_sub_return_type_field_length; field_index++) {
            double_vars[opcode->operand0 + field_index] = *(SPVM_VALUE_double*)&stack[field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_IF_CROAK_CATCH: {
        if (exception_flag) {
          exception_flag = 0;
          
          SPVM_RUNTIME_SUB* sub = SPVM_LIST_fetch(package->subs, opcode->operand1);
          int32_t sub_id = sub->id;
          int32_t rel_line = opcode->operand2;
          int32_t line = sub->line + rel_line;
          
          const char* sub_name = runtime->symbols[sub->name_id];
          SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
          const char* package_name = runtime->symbols[sub_package->name_id];
          const char* file = runtime->symbols[sub->file_id];
          
          // Exception stack trace
          env->set_exception(env, env->create_exception_stack_trace(env, env->get_exception(env), package_name, sub_name, file, line));
          opcode_rel_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_IF_CROAK_RETURN: {
        if (exception_flag) {
          SPVM_RUNTIME_SUB* sub = SPVM_LIST_fetch(package->subs, opcode->operand1);
          int32_t sub_id = sub->id;
          int32_t rel_line = opcode->operand2;
          int32_t line = sub->line + rel_line;
          
          const char* sub_name = runtime->symbols[sub->name_id];
          SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
          const char* package_name = runtime->symbols[sub_package->name_id];
          const char* file = runtime->symbols[sub->file_id];

          // Exception stack trace
          env->set_exception(env, env->create_exception_stack_trace(env, env->get_exception(env), package_name, sub_name, file, line));
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
          SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(*(void**)&stack[0]);
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
        int32_t sub_return_type_field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < sub_return_type_field_length; field_index++) {
          *(SPVM_VALUE_byte*)&stack[field_index] = byte_vars[opcode->operand0 + field_index];
        }
        opcode_rel_index = opcode->operand1;
        
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_VALUE_SHORT:
      {
        int32_t sub_return_type_field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < sub_return_type_field_length; field_index++) {
          *(SPVM_VALUE_short*)&stack[field_index] = short_vars[opcode->operand0 + field_index];
        }
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_VALUE_INT:
      {
        int32_t sub_return_type_field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < sub_return_type_field_length; field_index++) {
          *(SPVM_VALUE_int*)&stack[field_index] = int_vars[opcode->operand0 + field_index];
        }
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_VALUE_LONG:
      {
        int32_t sub_return_type_field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < sub_return_type_field_length; field_index++) {
          *(SPVM_VALUE_long*)&stack[field_index] = long_vars[opcode->operand0 + field_index];
        }
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_VALUE_FLOAT:
      {
        int32_t sub_return_type_field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < sub_return_type_field_length; field_index++) {
          *(SPVM_VALUE_float*)&stack[field_index] = float_vars[opcode->operand0 + field_index];
        }
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_VALUE_DOUBLE:
      {
        int32_t sub_return_type_field_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < sub_return_type_field_length; field_index++) {
          *(SPVM_VALUE_double*)&stack[field_index] = double_vars[opcode->operand0 + field_index];
        }
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_LOOKUP_SWITCH: {

        int32_t rel_id = opcode->operand2;
        SPVM_RUNTIME_INFO_SWITCH_INFO* switch_info = SPVM_LIST_fetch(runtime->info_switch_infos, sub->info_switch_infos_base + rel_id);
        SPVM_LIST* case_infos = switch_info->case_infos;
        
        // default
        int32_t default_opcode_rel_index = switch_info->default_opcode_rel_index;
        
        // cases length
        int32_t case_infos_length = case_infos->length;
        
        if (case_infos_length > 0) {
          
          SPVM_RUNTIME_INFO_CASE_INFO* case_min = SPVM_LIST_fetch(case_infos, 0);
          SPVM_RUNTIME_INFO_CASE_INFO* case_max = SPVM_LIST_fetch(case_infos, case_infos->length - 1);
          
          // min
          int32_t min = case_min->match;
          
          // max
          int32_t max = case_max->match;
          
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
              SPVM_RUNTIME_INFO_CASE_INFO* case_half = SPVM_LIST_fetch(case_infos, cur_half_pos);
              int32_t cur_half = case_half->match;
              
              if (int_vars[opcode->operand0] > cur_half) {
                cur_min_pos = cur_half_pos + 1;
              }
              else if (int_vars[opcode->operand0] < cur_half) {
                cur_max_pos = cur_half_pos - 1;
              }
              else {
                opcode_rel_index = case_half->opcode_rel_index;
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
        int32_t rel_id = opcode->operand2;

        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_index = field->index;

        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          byte_vars[opcode->operand0] = *(SPVM_VALUE_byte*)&fields[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_SHORT: {
        int32_t rel_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_index = field->index;

        void* object = *(void**)&object_vars[opcode->operand1];

        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          short_vars[opcode->operand0] = *(SPVM_VALUE_short*)&fields[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_INT: {
        int32_t rel_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_index = field->index;

        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          int_vars[opcode->operand0] = *(SPVM_VALUE_int*)&fields[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_LONG: {
        int32_t rel_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_index = field->index;

        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          long_vars[opcode->operand0] = *(SPVM_VALUE_long*)&fields[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_FLOAT: {
        int32_t rel_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_index = field->index;

        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          float_vars[opcode->operand0] = *(SPVM_VALUE_float*)&fields[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE: {
        int32_t rel_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_index = field->index;

        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          double_vars[opcode->operand0] = *(SPVM_VALUE_double*)&fields[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_OBJECT: {
        int32_t rel_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_index = field->index;

        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          void* object_field = *(void**)&fields[field_index];;
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], SPVM_RUNTIME_C_INLINE_GET_OBJECT_NO_WEAKEN_ADDRESS(object_field));
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_BYTE: {
        void* object = *(void**)&object_vars[opcode->operand0];
        
        int32_t rel_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_index = field->index;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          *(SPVM_VALUE_byte*)&fields[field_index] = byte_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_SHORT: {
        void* object = *(void**)&object_vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_index = field->index;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          *(SPVM_VALUE_short*)&fields[field_index] = short_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_INT: {
        void* object = *(void**)&object_vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_index = field->index;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          *(SPVM_VALUE_int*)&fields[field_index] = int_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_LONG: {
        void* object = *(void**)&object_vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_index = field->index;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          *(SPVM_VALUE_long*)&fields[field_index] = long_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_FLOAT: {
        void* object = *(void**)&object_vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_index = field->index;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          *(SPVM_VALUE_float*)&fields[field_index] = float_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE: {
        void* object = *(void**)&object_vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_index = field->index;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          *(SPVM_VALUE_double*)&fields[field_index] = double_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_OBJECT: {
        void* object = *(void**)&object_vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_index = field->index;

        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          void* object_field_address = (void**)&fields[field_index];
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(object_field_address, *(void**)&object_vars[opcode->operand2]);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_UNDEF: {
        void* object = *(void**)&object_vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[sub->info_field_ids_base + rel_id];
        SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
        int32_t field_index = field->index;

        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          void* object_field_address = (void**)&fields[field_index];
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(object_field_address, NULL);
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
        int32_t rel_id = opcode->operand1;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        
        byte_vars[opcode->operand0] = *(SPVM_VALUE_byte*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_SHORT: {
        int32_t rel_id = opcode->operand1;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        
        short_vars[opcode->operand0] = *(SPVM_VALUE_short*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_INT: {
        int32_t rel_id = opcode->operand1;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        
        int_vars[opcode->operand0] = *(SPVM_VALUE_int*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_LONG: {
        int32_t rel_id = opcode->operand1;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        
        long_vars[opcode->operand0] = *(SPVM_VALUE_long*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_FLOAT: {
        int32_t rel_id = opcode->operand1;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        
        float_vars[opcode->operand0] = *(float*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_DOUBLE: {
        int32_t rel_id = opcode->operand1;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        
        double_vars[opcode->operand0] = *(double*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_OBJECT: {
        int32_t rel_id = opcode->operand1;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], *(void**)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id]);
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_BYTE: {
        int32_t rel_id = opcode->operand0;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        
        *(SPVM_VALUE_byte*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id] = byte_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_SHORT: {
        int32_t rel_id = opcode->operand0;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        
        *(SPVM_VALUE_short*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id] = short_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_INT: {
        int32_t rel_id = opcode->operand0;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        
        *(SPVM_VALUE_int*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id] = int_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_LONG: {
        int32_t rel_id = opcode->operand0;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        
        *(SPVM_VALUE_long*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id] = long_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_FLOAT: {
        int32_t rel_id = opcode->operand0;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        
        *(float*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id] = float_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_DOUBLE: {
        int32_t rel_id = opcode->operand0;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        
        *(double*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id] = double_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_OBJECT: {
        int32_t rel_id = opcode->operand0;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id], *(void**)&object_vars[opcode->operand1]);
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_UNDEF: {
        int32_t rel_id = opcode->operand0;
        int32_t package_var_id = runtime->info_package_var_ids[sub->info_package_var_ids_base + rel_id];
        
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id], NULL);
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_EXCEPTION_VAR: {
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], env->get_exception(env));
        
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
        int32_t basic_type_id = (intptr_t)(void*)env->basic_type_id_byte_object;

        void* object = env->new_object_raw(env, basic_type_id);
        SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
        *(SPVM_VALUE_byte*)&fields[0] = value;
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_SHORT_OBJECT: {
        SPVM_VALUE_short value = short_vars[opcode->operand1];
        int32_t basic_type_id = (intptr_t)(void*)env->basic_type_id_short_object;
        void* object = env->new_object_raw(env, basic_type_id);
        SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
        *(SPVM_VALUE_short*)&fields[0] = value;
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_INT_OBJECT: {
        SPVM_VALUE_int value = int_vars[opcode->operand1];
        int32_t basic_type_id = (intptr_t)(void*)env->basic_type_id_int_object;
        void* object = env->new_object_raw(env, basic_type_id);
        SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
        *(SPVM_VALUE_int*)&fields[0] = value;
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_LONG_OBJECT: {
        SPVM_VALUE_long value = long_vars[opcode->operand1];
        int32_t basic_type_id = (intptr_t)(void*)env->basic_type_id_long_object;
        void* object = env->new_object_raw(env, basic_type_id);
        SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
        *(SPVM_VALUE_long*)&fields[0] = value;
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_FLOAT_OBJECT: {
        SPVM_VALUE_float value = float_vars[opcode->operand1];
        int32_t basic_type_id = (intptr_t)(void*)env->basic_type_id_float_object;
        void* object = env->new_object_raw(env, basic_type_id);
        SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
        *(SPVM_VALUE_float*)&fields[0] = value;
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_DOUBLE_OBJECT: {
        SPVM_VALUE_double value = double_vars[opcode->operand1];
        int32_t basic_type_id = (intptr_t)(void*)env->basic_type_id_double_object;
        void* object = env->new_object_raw(env, basic_type_id);
        SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
        *(SPVM_VALUE_double*)&fields[0] = value;
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_OBJECT_TO_BYTE: {
        void* object = *(void**)&object_vars[opcode->operand1];
        if (object == NULL) {
          void* exception = env->new_string_raw(env, "Can't convert undef value.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);
          int32_t object_type_dimension_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);
          if (object_basic_type_id == (intptr_t)(void*)env->basic_type_id_byte_object && object_type_dimension_id == 0) {
            SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
            byte_vars[opcode->operand0] = *(SPVM_VALUE_byte*)&fields[0];
          }
          else {
            void* exception = env->new_string_raw(env, "Can't convert imcompatible object type.", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_OBJECT_TO_SHORT: {
        void* object = *(void**)&object_vars[opcode->operand1];
        if (object == NULL) {
          void* exception = env->new_string_raw(env, "Can't convert undef value.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);
          int32_t object_type_dimension_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);
          if (object_basic_type_id == (intptr_t)(void*)env->basic_type_id_short_object && object_type_dimension_id == 0) {
            SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
            short_vars[opcode->operand0] = *(SPVM_VALUE_short*)&fields[0];
          }
          else {
            void* exception = env->new_string_raw(env, "Can't convert imcompatible object type.", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_OBJECT_TO_INT: {
        void* object = *(void**)&object_vars[opcode->operand1];
        if (object == NULL) {
          void* exception = env->new_string_raw(env, "Can't convert undef value.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);
          int32_t object_type_dimension_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);
          if (object_basic_type_id == (intptr_t)(void*)env->basic_type_id_int_object && object_type_dimension_id == 0) {
            SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
            int_vars[opcode->operand0] = *(SPVM_VALUE_int*)&fields[0];
          }
          else {
            void* exception = env->new_string_raw(env, "Can't convert imcompatible object type.", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_OBJECT_TO_LONG: {
        void* object = *(void**)&object_vars[opcode->operand1];
        if (object == NULL) {
          void* exception = env->new_string_raw(env, "Can't convert undef value.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);
          int32_t object_type_dimension_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);
          if (object_basic_type_id == (intptr_t)(void*)env->basic_type_id_long_object && object_type_dimension_id == 0) {
            SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
            long_vars[opcode->operand0] = *(SPVM_VALUE_long*)&fields[0];
          }
          else {
            void* exception = env->new_string_raw(env, "Can't convert imcompatible object type.", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_OBJECT_TO_FLOAT: {
        void* object = *(void**)&object_vars[opcode->operand1];
        if (object == NULL) {
          void* exception = env->new_string_raw(env, "Can't convert undef value.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);
          int32_t object_type_dimension_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);
          if (object_basic_type_id == (intptr_t)(void*)env->basic_type_id_float_object && object_type_dimension_id == 0) {
            SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
            float_vars[opcode->operand0] = *(SPVM_VALUE_float*)&fields[0];
          }
          else {
            void* exception = env->new_string_raw(env, "Can't convert imcompatible object type.", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_OBJECT_TO_DOUBLE: {
        void* object = *(void**)&object_vars[opcode->operand1];
        if (object == NULL) {
          void* exception = env->new_string_raw(env, "Can't convert undef value.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);
          int32_t object_type_dimension_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);
          if (object_basic_type_id == (intptr_t)(void*)env->basic_type_id_double_object && object_type_dimension_id == 0) {
            SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
            double_vars[opcode->operand0] = *(SPVM_VALUE_double*)&fields[0];
          }
          else {
            void* exception = env->new_string_raw(env, "Can't convert imcompatible object type.", 0);
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
    int32_t sub_return_basic_type_id = sub->return_basic_type_id;
    int32_t sub_return_type_dimension = sub->return_type_dimension;
    int32_t sub_return_type_flag = sub->return_type_flag;
    if (SPVM_RUNTIME_API_is_object_type(env, sub_return_basic_type_id, sub_return_type_dimension, sub_return_type_flag)) {
      if (*(void**)&stack[0] != NULL) {
        SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*(void**)&stack[0]);
      }
    }
  }
  
  SPVM_RUNTIME_ALLOCATOR_free_memory_block(runtime, mortal_stack);

  SPVM_RUNTIME_ALLOCATOR_free_memory_block(runtime, byte_vars);
  SPVM_RUNTIME_ALLOCATOR_free_memory_block(runtime, short_vars);
  SPVM_RUNTIME_ALLOCATOR_free_memory_block(runtime, int_vars);
  SPVM_RUNTIME_ALLOCATOR_free_memory_block(runtime, long_vars);
  SPVM_RUNTIME_ALLOCATOR_free_memory_block(runtime, float_vars);
  SPVM_RUNTIME_ALLOCATOR_free_memory_block(runtime, double_vars);
  SPVM_RUNTIME_ALLOCATOR_free_memory_block(runtime, object_vars);
  SPVM_RUNTIME_ALLOCATOR_free_memory_block(runtime, ref_vars);
  
  return exception_flag;
}

void SPVM_RUNTIME_free(SPVM_ENV* env) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Free exception
  SPVM_RUNTIME_API_set_exception(env, NULL);
  
  // Free portable
  SPVM_PORTABLE_free(runtime->portable);
  
  free(runtime->sub_native_addresses);
  free(runtime->sub_precompile_addresses);
  
  if (runtime->exception != NULL) {
    free(runtime->exception);
  }
  
  free(runtime->mortal_stack);
  
  SPVM_HASH_free(runtime->basic_type_symtable);
  SPVM_HASH_free(runtime->field_symtable);
  SPVM_HASH_free(runtime->sub_symtable);
  
  for (int32_t switch_index = 0; switch_index < runtime->info_switch_infos->length; switch_index++) {
    SPVM_RUNTIME_INFO_SWITCH_INFO* info_switch_info = SPVM_LIST_fetch(runtime->info_switch_infos, switch_index);
    
    SPVM_LIST* case_infos = info_switch_info->case_infos;
    for (int32_t case_index = 0; case_index < case_infos->length; case_index++) {
      SPVM_RUNTIME_INFO_CASE_INFO* info_case_info = SPVM_LIST_fetch(case_infos, case_index);
      free(info_case_info);
    }
    SPVM_LIST_free(info_switch_info->case_infos);
  }
  SPVM_LIST_free(runtime->info_switch_infos);

  for (int32_t package_id = 0; package_id < runtime->packages_length; package_id++) {
    
    SPVM_RUNTIME_PACKAGE* package = &runtime->packages[package_id];
    
    SPVM_LIST_free(package->fields);
    SPVM_LIST_free(package->field_signatures);
    SPVM_LIST_free(package->package_vars);
    SPVM_LIST_free(package->package_var_signatures);
    SPVM_LIST_free(package->subs);
    SPVM_LIST_free(package->sub_signatures);
    SPVM_LIST_free(package->object_field_indexes);

    SPVM_HASH_free(package->field_symtable);
    SPVM_HASH_free(package->field_signature_symtable);
    SPVM_HASH_free(package->package_var_symtable);
    SPVM_HASH_free(package->package_var_signature_symtable);
    SPVM_HASH_free(package->sub_symtable);
    SPVM_HASH_free(package->sub_signature_symtable);
  }
  SPVM_HASH_free(runtime->package_symtable);

  // Free package variables heap
  free(runtime->package_vars_heap);
  
  // Free runtime
  free(runtime);
}
