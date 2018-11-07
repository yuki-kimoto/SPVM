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
#include "spvm_runtime_my.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_info_type.h"
#include "spvm_runtime_info_switch_info.h"
#include "spvm_runtime_info_case_info.h"

// Only use constant
#include "spvm_package.h"
#include "spvm_basic_type.h"
#include "spvm_type.h"
#include "spvm_sub.h"

int32_t SPVM_RUNTIME_API_call_sub(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* stack) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;

  // Sub
  SPVM_RUNTIME_SUB* sub = &runtime->subs[sub_id];
  
  // Call native sub
  if (sub->flag & SPVM_SUB_C_FLAG_HAVE_NATIVE_DESC) {
    // Enter scope
    int32_t original_mortal_stack_top = SPVM_RUNTIME_API_enter_scope(env);

    // Call native subrotuine
    int32_t (*native_address)(SPVM_ENV*, SPVM_VALUE*) = runtime->sub_native_addresses[sub->id];
    int32_t exception_flag = (*native_address)(env, stack);
    
    // Leave scope
    SPVM_RUNTIME_API_leave_scope(env, original_mortal_stack_top);

    // Set default exception message
    if (exception_flag && runtime->exception == NULL) {
      void* exception = env->new_string_raw(env, "Error", 0);
      env->set_exception(env, exception);
    }
    
    return exception_flag;
  }
  // Call precompiled sub
  else if (sub->flag & SPVM_SUB_C_FLAG_IS_COMPILED) {
    int32_t (*precompile_address)(SPVM_ENV*, SPVM_VALUE*) = runtime->sub_precompile_addresses[sub->id];
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
  {
    // Numeric area byte size
    int32_t numeric_area_byte_size = 0;
    numeric_area_byte_size += sub->long_vars_alloc_length * 8;
    numeric_area_byte_size += sub->double_vars_alloc_length * 8;
    numeric_area_byte_size += sub->int_vars_alloc_length * 4;
    numeric_area_byte_size += sub->float_vars_alloc_length * 4;
    numeric_area_byte_size += sub->short_vars_alloc_length * 2;
    numeric_area_byte_size += sub->mortal_stack_length * 2;
    numeric_area_byte_size += sub->byte_vars_alloc_length * 1;
    
    if (numeric_area_byte_size % 8 != 0) {
      numeric_area_byte_size += (8 - (numeric_area_byte_size % 8));
    }
    
    // Address area byte size
    int32_t address_area_byte_size = 0;
    address_area_byte_size += sub->object_vars_alloc_length * sizeof(void*);
    address_area_byte_size += sub->ref_vars_alloc_length * sizeof(void*);
    
    // Total area byte size
    int32_t total_area_byte_size = numeric_area_byte_size + address_area_byte_size;
    
    int32_t total_call_stack_length =
      sub->object_vars_alloc_length +
      sub->ref_vars_alloc_length +
      sub->double_vars_alloc_length +
      sub->long_vars_alloc_length +
      sub->float_vars_alloc_length +
      sub->int_vars_alloc_length +
      sub->short_vars_alloc_length +
      sub->byte_vars_alloc_length +
      sub->mortal_stack_length;
    
    if (total_call_stack_length > 0) {
      call_stack = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, sizeof(SPVM_VALUE) * total_call_stack_length);

      int32_t call_stack_byte_offset = 0;
      
      // Double variables
      double_vars = (double*)&call_stack[call_stack_byte_offset];
      call_stack_byte_offset += sub->double_vars_alloc_length * 8;
      
      // Long varialbes
      long_vars = (SPVM_VALUE_long*)&call_stack[call_stack_byte_offset];
      call_stack_byte_offset += sub->long_vars_alloc_length * 8;
      
      // Float variables
      float_vars = (float*)&call_stack[call_stack_byte_offset];
      call_stack_byte_offset += sub->float_vars_alloc_length * 4;
      
      // Int variables
      int_vars = (SPVM_VALUE_int*)&call_stack[call_stack_byte_offset];
      call_stack_byte_offset += sub->int_vars_alloc_length * 4;

      // Short variables
      short_vars = (SPVM_VALUE_short*)&call_stack[call_stack_byte_offset];
      call_stack_byte_offset += sub->short_vars_alloc_length * 2;

      // Mortal stack
      mortal_stack = (uint16_t*)&call_stack[call_stack_byte_offset];
      call_stack_byte_offset += sub->mortal_stack_length * 2;
      
      // Byte variables
      byte_vars = (SPVM_VALUE_byte*)&call_stack[call_stack_byte_offset];
      call_stack_byte_offset += sub->byte_vars_alloc_length * 1;
      
      call_stack_byte_offset = numeric_area_byte_size;

      // Object variables
      object_vars = (void**)&call_stack[call_stack_byte_offset];
      call_stack_byte_offset += sub->object_vars_alloc_length * sizeof(void*);
      
      // Refernce variables
      ref_vars = (void**)&call_stack[call_stack_byte_offset];
      call_stack_byte_offset += sub->ref_vars_alloc_length * sizeof(void*);
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
      SPVM_RUNTIME_MY* arg = &runtime->args[arg_index];
      
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
            SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(object);
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
  
  // Execute operation codes
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
        int32_t info_constant_id = opcode->operand1;
        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[package->info_types_base + info_constant_id];
        int32_t check_basic_type_id = type->basic_type_id;
        int32_t check_type_dimension = type->dimension;
        
        if (object) {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);
          condition_flag = (object_basic_type_id == check_basic_type_id && object_type_dimension == check_type_dimension);
        }
        else {
          condition_flag = 0;
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_ISA_INTERFACE: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t info_constant_id = opcode->operand1;
        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[package->info_types_base + info_constant_id];
        int32_t check_basic_type_id = type->basic_type_id;
        int32_t check_type_dimension = type->dimension;
        
        if (object) {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);
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
        int32_t constant_pool_id = opcode->operand1;
        int64_t long_value;
        memcpy(&long_value, &runtime->global_constant_pool[package->constant_pool_base + constant_pool_id], sizeof(int64_t));
        long_vars[opcode->operand0] = long_value;
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_FLOAT:
        float_vars[opcode->operand0] = *(float*)&opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_GET_CONSTANT_DOUBLE: {
        int32_t info_constant_id = opcode->operand1;
        double double_value = runtime->info_double_values[package->info_double_values_base + info_constant_id];
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
        int32_t info_constant_id = opcode->operand1;
        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[package->info_types_base + info_constant_id];
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
        int32_t info_constant_id = opcode->operand1;
        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[package->info_types_base + info_constant_id];
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
        int32_t info_constant_id = opcode->operand1;
        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[package->info_types_base + info_constant_id];
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
        int32_t info_constant_id = opcode->operand1;
        SPVM_RUNTIME_INFO_TYPE* type = &runtime->info_types[package->info_types_base + info_constant_id];
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
        int32_t info_constant_id = opcode->operand1;
        const char* string_value = runtime->info_string_values[package->info_string_values_base + info_constant_id];
        int32_t string_length = runtime->info_string_lengths[package->info_string_values_base + info_constant_id];
        
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
        int32_t info_field_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[package->info_field_ids_base + info_field_id];
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
          int32_t info_constant_id = opcode->operand2;
          SPVM_RUNTIME_INFO_TYPE* check_type = &runtime->info_types[package->info_types_base + info_constant_id];
          int32_t check_basic_type_id = check_type->basic_type_id;
          int32_t check_type_dimension = check_type->dimension;
          
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);
          
          if (object_basic_type_id == check_basic_type_id && object_type_dimension == check_type_dimension) {
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
          int32_t info_constant_id = opcode->operand2;
          SPVM_RUNTIME_INFO_TYPE* interface_type = &runtime->info_types[package->info_types_base + info_constant_id];
          int32_t interface_basic_type_id = interface_type->basic_type_id;
          int32_t interface_type_dimension = interface_type->dimension;
          
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_byte_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);
          
          if (env->has_interface(env, object_basic_type_id, object_type_dimension, interface_basic_type_id, interface_type_dimension)) {
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
        int32_t constant_pool_id = opcode->operand1;
        int32_t call_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
        SPVM_RUNTIME_SUB* call_sub = &runtime->subs[call_sub_id];
        call_sub_arg_stack_top -= call_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB_BYTE:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t call_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
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
        int32_t call_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
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
        int32_t constant_pool_id = opcode->operand1;
        int32_t call_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
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
        int32_t call_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
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
        int32_t call_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
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
        int32_t call_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
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
        int32_t call_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
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
        int32_t constant_pool_id = opcode->operand1;
        int32_t call_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
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
        int32_t call_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
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
        int32_t call_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
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
        int32_t call_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
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
        int32_t call_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
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
        int32_t call_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
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
        int32_t decl_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_name, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_BYTE:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t decl_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_name, decl_sub_signature);
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
        int32_t decl_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_name, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          short_vars[opcode->operand0] = *(SPVM_VALUE_short*)&stack[0];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_INT_TMP:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t decl_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_name, decl_sub_signature);
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
        int32_t decl_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_name, decl_sub_signature);
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
        int32_t decl_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_name, decl_sub_signature);
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
        int32_t decl_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_name, decl_sub_signature);
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
        int32_t decl_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_name, decl_sub_signature);
        call_sub_arg_stack_top -= decl_sub->args_alloc_length;
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], stack[0].oval);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD_VALUE_BYTE:
      {
        int32_t constant_pool_id = opcode->operand1;
        int32_t decl_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_name, decl_sub_signature);
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
        int32_t decl_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_name, decl_sub_signature);
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
        int32_t decl_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_name, decl_sub_signature);
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
        int32_t decl_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_name, decl_sub_signature);
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
        int32_t decl_sub_id = runtime->info_sub_ids[package->info_sub_ids_base + constant_pool_id];
        SPVM_RUNTIME_SUB* decl_sub = &runtime->subs[decl_sub_id];
        void* object = *(void**)&object_vars[opcode->operand2];
        const char* decl_sub_name = &runtime->string_pool[decl_sub->name_id];
        const char* decl_sub_signature = &runtime->string_pool[decl_sub->signature_id];
        int32_t call_sub_id = env->get_sub_id_method_call(env, object, decl_sub_name, decl_sub_signature);
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
      case SPVM_OPCODE_C_ID_IF_CROAK_CATCH: {
        if (exception_flag) {
          exception_flag = 0;
          
          SPVM_RUNTIME_SUB* sub = SPVM_LIST_fetch(package->subs, opcode->operand1);
          int32_t sub_id = sub->id;
          int32_t rel_line = opcode->operand2;
          int32_t line = sub->line + rel_line;
          
          const char* sub_name = &runtime->string_pool[sub->name_id];
          SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
          const char* package_name = &runtime->string_pool[sub_package->name_id];
          const char* file = &runtime->string_pool[sub->file_id];
          
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
          
          const char* sub_name = &runtime->string_pool[sub->name_id];
          SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
          const char* package_name = &runtime->string_pool[sub_package->name_id];
          const char* file = &runtime->string_pool[sub->file_id];

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
      case SPVM_OPCODE_C_ID_LOOKUP_SWITCH: {

        int32_t info_constant_id = opcode->operand2;
        SPVM_RUNTIME_INFO_SWITCH_INFO* switch_info = SPVM_LIST_fetch(runtime->info_switch_infos, package->info_switch_infos_base + info_constant_id);
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
        int32_t info_field_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[package->info_field_ids_base + info_field_id];
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
        int32_t info_field_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[package->info_field_ids_base + info_field_id];
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
        int32_t info_field_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[package->info_field_ids_base + info_field_id];
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
        int32_t info_field_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[package->info_field_ids_base + info_field_id];
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
        int32_t info_field_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[package->info_field_ids_base + info_field_id];
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
        int32_t info_field_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[package->info_field_ids_base + info_field_id];
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
        int32_t info_field_id = opcode->operand2;
        int32_t field_id = runtime->info_field_ids[package->info_field_ids_base + info_field_id];
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
          void* object_field = *(void**)&fields[field_index];
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], SPVM_RUNTIME_C_INLINE_GET_OBJECT_NO_WEAKEN_ADDRESS(object_field));
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_BYTE: {
        void* object = *(void**)&object_vars[opcode->operand0];
        
        int32_t info_field_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[package->info_field_ids_base + info_field_id];
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

        int32_t info_field_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[package->info_field_ids_base + info_field_id];
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

        int32_t info_field_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[package->info_field_ids_base + info_field_id];
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

        int32_t info_field_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[package->info_field_ids_base + info_field_id];
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

        int32_t info_field_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[package->info_field_ids_base + info_field_id];
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

        int32_t info_field_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[package->info_field_ids_base + info_field_id];
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

        int32_t info_field_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[package->info_field_ids_base + info_field_id];
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

        int32_t info_field_id = opcode->operand1;
        int32_t field_id = runtime->info_field_ids[package->info_field_ids_base + info_field_id];
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
        int32_t info_package_var_id = opcode->operand1;
        int32_t package_var_id = runtime->info_package_var_ids[package->info_package_var_ids_base + info_package_var_id];
        
        byte_vars[opcode->operand0] = *(SPVM_VALUE_byte*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_SHORT: {
        int32_t info_package_var_id = opcode->operand1;
        int32_t package_var_id = runtime->info_package_var_ids[package->info_package_var_ids_base + info_package_var_id];
        
        short_vars[opcode->operand0] = *(SPVM_VALUE_short*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_INT: {
        int32_t info_package_var_id = opcode->operand1;
        int32_t package_var_id = runtime->info_package_var_ids[package->info_package_var_ids_base + info_package_var_id];
        
        int_vars[opcode->operand0] = *(SPVM_VALUE_int*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_LONG: {
        int32_t info_package_var_id = opcode->operand1;
        int32_t package_var_id = runtime->info_package_var_ids[package->info_package_var_ids_base + info_package_var_id];
        
        long_vars[opcode->operand0] = *(SPVM_VALUE_long*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_FLOAT: {
        int32_t info_package_var_id = opcode->operand1;
        int32_t package_var_id = runtime->info_package_var_ids[package->info_package_var_ids_base + info_package_var_id];
        
        float_vars[opcode->operand0] = *(float*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_DOUBLE: {
        int32_t info_package_var_id = opcode->operand1;
        int32_t package_var_id = runtime->info_package_var_ids[package->info_package_var_ids_base + info_package_var_id];
        
        double_vars[opcode->operand0] = *(double*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_OBJECT: {
        int32_t info_package_var_id = opcode->operand1;
        int32_t package_var_id = runtime->info_package_var_ids[package->info_package_var_ids_base + info_package_var_id];
        
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&object_vars[opcode->operand0], *(void**)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id]);
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_BYTE: {
        int32_t info_package_var_id = opcode->operand0;
        int32_t package_var_id = runtime->info_package_var_ids[package->info_package_var_ids_base + info_package_var_id];
        
        *(SPVM_VALUE_byte*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id] = byte_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_SHORT: {
        int32_t info_package_var_id = opcode->operand0;
        int32_t package_var_id = runtime->info_package_var_ids[package->info_package_var_ids_base + info_package_var_id];
        
        *(SPVM_VALUE_short*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id] = short_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_INT: {
        int32_t info_package_var_id = opcode->operand0;
        int32_t package_var_id = runtime->info_package_var_ids[package->info_package_var_ids_base + info_package_var_id];
        
        *(SPVM_VALUE_int*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id] = int_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_LONG: {
        int32_t info_package_var_id = opcode->operand0;
        int32_t package_var_id = runtime->info_package_var_ids[package->info_package_var_ids_base + info_package_var_id];
        
        *(SPVM_VALUE_long*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id] = long_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_FLOAT: {
        int32_t info_package_var_id = opcode->operand0;
        int32_t package_var_id = runtime->info_package_var_ids[package->info_package_var_ids_base + info_package_var_id];
        
        *(float*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id] = float_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_DOUBLE: {
        int32_t info_package_var_id = opcode->operand0;
        int32_t package_var_id = runtime->info_package_var_ids[package->info_package_var_ids_base + info_package_var_id];
        
        *(double*)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id] = double_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_OBJECT: {
        int32_t info_package_var_id = opcode->operand0;
        int32_t package_var_id = runtime->info_package_var_ids[package->info_package_var_ids_base + info_package_var_id];
        
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&(*(SPVM_VALUE**)(env->runtime + (intptr_t)env->runtime_package_vars_heap_byte_offset))[package_var_id], *(void**)&object_vars[opcode->operand1]);
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_UNDEF: {
        int32_t info_package_var_id = opcode->operand0;
        int32_t package_var_id = runtime->info_package_var_ids[package->info_package_var_ids_base + info_package_var_id];
        
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
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);
          if (object_basic_type_id == (intptr_t)(void*)env->basic_type_id_byte_object && object_type_dimension == 0) {
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
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);
          if (object_basic_type_id == (intptr_t)(void*)env->basic_type_id_short_object && object_type_dimension == 0) {
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
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);
          if (object_basic_type_id == (intptr_t)(void*)env->basic_type_id_int_object && object_type_dimension == 0) {
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
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);
          if (object_basic_type_id == (intptr_t)(void*)env->basic_type_id_long_object && object_type_dimension == 0) {
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
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);
          if (object_basic_type_id == (intptr_t)(void*)env->basic_type_id_float_object && object_type_dimension == 0) {
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
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_byte_offset);
          if (object_basic_type_id == (intptr_t)(void*)env->basic_type_id_double_object && object_type_dimension == 0) {
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
    switch (sub->return_runtime_type) {
      case SPVM_TYPE_C_RUNTIME_TYPE_ANY_OBJECT:
      case SPVM_TYPE_C_RUNTIME_TYPE_PACKAGE:
      case SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY:
      case SPVM_TYPE_C_RUNTIME_TYPE_VALUE_ARRAY:
      case SPVM_TYPE_C_RUNTIME_TYPE_OBJECT_ARRAY:
      {
        if (*(void**)&stack[0] != NULL) {
          SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*(void**)&stack[0]);
        }
      }
    }
  }
  
  SPVM_RUNTIME_API_free_memory_block(runtime, call_stack);
  
  return exception_flag;
}

int32_t SPVM_RUNTIME_API_call_entry_point_sub(SPVM_ENV* env, const char* package_name, int32_t argc, const char *argv[]) {
  
  SPVM_RUNTIME* runtime = env->runtime;

  // Package
  int32_t sub_id = 0;
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));
  if (package) {
  
    const char* sub_name = "main";
    
    SPVM_RUNTIME_SUB* sub = SPVM_HASH_fetch(package->sub_symtable, sub_name, strlen(sub_name));
    if (sub) {
      sub_id = sub->id;
    }
    else {
      fprintf(stderr, "Can't find entry point subroutine %s", sub_name);
      exit(EXIT_FAILURE);
    }
  }
  else {
    fprintf(stderr, "Can't find entry point package %s\n", package_name);
  }
  
  // Enter scope
  int32_t scope_id = env->enter_scope(env);
  
  // new byte[][args_length] object
  int32_t arg_type_basic_id = env->get_basic_type_id(env, "byte");
  void* cmd_args_obj = env->new_multi_array(env, arg_type_basic_id, 1, argc);
  
  // Set command line arguments
  for (int32_t arg_index = 0; arg_index < argc; arg_index++) {
    void* cmd_arg_obj = env->new_string(env, argv[arg_index], strlen(argv[arg_index]));
    env->set_object_array_element(env, cmd_args_obj, arg_index, cmd_arg_obj);
  }
  
  SPVM_VALUE stack[255];
  stack[0].oval = cmd_args_obj;
  
  // Run
  int32_t exception_flag = env->call_sub(env, sub_id, stack);
  
  int32_t status_code;
  if (exception_flag) {
    SPVM_RUNTIME_API_print(env, runtime->exception);
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

int32_t SPVM_RUNTIME_API_has_interface(SPVM_ENV* env, int32_t object_basic_type_id, int32_t object_type_dimension, int32_t interface_basic_type_id, int32_t interface_type_dimension) {
  (void)env;

  SPVM_RUNTIME* runtime = env->runtime;

  SPVM_RUNTIME_BASIC_TYPE* object_basic_type = object_basic_type_id >= 0 ? &runtime->basic_types[object_basic_type_id] : NULL;
  SPVM_RUNTIME_BASIC_TYPE* interface_basic_type = interface_basic_type_id >= 0 ? &runtime->basic_types[interface_basic_type_id] : NULL;

  SPVM_RUNTIME_PACKAGE* object_package = object_basic_type->package_id ? &runtime->packages[object_basic_type->package_id] : NULL;
  SPVM_RUNTIME_PACKAGE* interface_package = interface_basic_type->package_id ? &runtime->packages[interface_basic_type->package_id] : NULL;
  
  assert(object_package);
  assert(interface_package);
  
  assert(interface_package->subs->length == 1);
  
  SPVM_RUNTIME_SUB* sub_interface = SPVM_LIST_fetch(interface_package->subs, 0);
  
  const char* sub_interface_name = &runtime->string_pool[sub_interface->name_id];
  const char* sub_interface_signature = &runtime->string_pool[sub_interface->signature_id];
  
  SPVM_RUNTIME_SUB* found_sub;
  if (object_package->flag & SPVM_PACKAGE_C_FLAG_IS_HAS_ONLY_ANON_SUB) {
    found_sub = SPVM_LIST_fetch(object_package->subs, 0);
  }
  else {
    found_sub = SPVM_HASH_fetch(object_package->sub_symtable, sub_interface_name, strlen(sub_interface_name));
  } 
  if (!found_sub) {
    return 0;
  }
  
  if (strcmp(sub_interface_signature, &runtime->string_pool[found_sub->signature_id]) == 0) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_RUNTIME_API_enter_scope(SPVM_ENV* env) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  int32_t mortal_stack_top = runtime->mortal_stack_top;
  
  return mortal_stack_top;
}

void SPVM_RUNTIME_API_push_mortal(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;

  SPVM_RUNTIME* runtime = env->runtime;
  
  if (object != NULL) {
    // Extend mortal stack
    if (runtime->mortal_stack_top >= runtime->mortal_stack_capacity) {
      int32_t new_mortal_stack_capacity = runtime->mortal_stack_capacity * 2;
      SPVM_OBJECT** new_mortal_stack = SPVM_RUNTIME_API_safe_malloc_zero(sizeof(void*) * new_mortal_stack_capacity);
      memcpy(new_mortal_stack, runtime->mortal_stack, sizeof(void*) * runtime->mortal_stack_capacity);
      runtime->mortal_stack_capacity = new_mortal_stack_capacity;
      runtime->mortal_stack = new_mortal_stack;
    }
    
    runtime->mortal_stack[runtime->mortal_stack_top] = object;
    runtime->mortal_stack_top++;
    
    object->ref_count++;
  }
}

void SPVM_RUNTIME_API_leave_scope(SPVM_ENV* env, int32_t original_mortal_stack_top) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;

  int32_t mortal_stack_index;
  for (mortal_stack_index = original_mortal_stack_top; mortal_stack_index < runtime->mortal_stack_top; mortal_stack_index++) {
    SPVM_OBJECT* object = runtime->mortal_stack[mortal_stack_index];
    
    if (object != NULL) {
      if (object->ref_count > 1) {
        object->ref_count--;
      }
      else {
        SPVM_RUNTIME_API_dec_ref_count(env, object);
      }
    }
    
    runtime->mortal_stack[mortal_stack_index] = NULL;
  }
  
  runtime->mortal_stack_top = original_mortal_stack_top;
}

SPVM_OBJECT* SPVM_RUNTIME_API_create_exception_stack_trace(SPVM_ENV* env, SPVM_OBJECT* exception, const char* package_name, const char* sub_name, const char* file, int32_t line) {
  
  // stack trace symbols
  const char* from_part = "\n  from ";
  const char* arrow_part = "->";
  const char* at_part = " at ";

  // Exception
  int8_t* exception_bytes = env->get_byte_array_elements(env, exception);
  int32_t exception_length = env->get_array_length(env, exception);
  
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
  void* new_exception = env->new_string_raw(env, NULL, total_length);
  int8_t* new_exception_bytes = env->get_byte_array_elements(env, new_exception);
  
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

void SPVM_RUNTIME_API_print(SPVM_ENV* env, SPVM_OBJECT* string) {
  (void)env;
  
  int8_t* bytes = env->get_byte_array_elements(env, string);
  int32_t string_length = env->get_array_length(env, string);
  
  {
    int32_t i;
    for (i = 0; i < string_length; i++) {
      putchar((char)bytes[i]);
    }
  }
}

SPVM_OBJECT* SPVM_RUNTIME_API_concat(SPVM_ENV* env, SPVM_OBJECT* string1, SPVM_OBJECT* string2) {
  (void)env;

  int32_t string1_length = SPVM_RUNTIME_API_get_array_length(env, string1);
  int32_t string2_length = SPVM_RUNTIME_API_get_array_length(env, string2);
  
  int32_t string3_length = string1_length + string2_length;
  SPVM_OBJECT* string3 = SPVM_RUNTIME_API_new_string_raw(env, NULL, string3_length);
  
  int8_t* string1_bytes = SPVM_RUNTIME_API_get_byte_array_elements(env, string1);
  int8_t* string2_bytes = SPVM_RUNTIME_API_get_byte_array_elements(env, string2);
  int8_t* string3_bytes = SPVM_RUNTIME_API_get_byte_array_elements(env, string3);
  
  memcpy(string3_bytes, string1_bytes, string1_length);
  memcpy(string3_bytes + string1_length, string2_bytes, string2_length);
  
  return string3;
}

int32_t SPVM_RUNTIME_API_get_memory_blocks_count(SPVM_ENV* env) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  return runtime->memory_blocks_count;
}

void SPVM_RUNTIME_API_free_weaken_back_refs(SPVM_ENV* env, void** weaken_back_refs, int32_t weaken_back_refs_length) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  {
    int32_t i;
    for (i = 0; i < weaken_back_refs_length; i++) {
      *(void**)weaken_back_refs[i] = NULL;
    }
  }
  
  SPVM_RUNTIME_API_free_memory_block(runtime, weaken_back_refs);
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
  
  // Weaken is implemented tag pointer. If pointer first bit is 1, object is weaken.
  *object_address = (SPVM_OBJECT*)((intptr_t)*object_address | 1);
  
  // Create array of weaken_back_refs if need
  if (object->weaken_back_refs == NULL) {
    object->weaken_back_refs_capacity = 1;
    object->weaken_back_refs = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, sizeof(void*) * object->weaken_back_refs_capacity);
  }
  
  int32_t capacity = object->weaken_back_refs_capacity;
  int32_t length = object->weaken_back_refs_length;
  
  // Extend capacity
  assert(capacity >= length);
  if (length == capacity) {
    int32_t new_capacity = capacity * 2;
    void** new_weaken_back_refs = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, sizeof(void*) * new_capacity);
    
    void** weaken_back_refs = object->weaken_back_refs;
    memcpy(new_weaken_back_refs, weaken_back_refs, length * sizeof(void*));
    
    // Old object become NULL
    memset(weaken_back_refs, 0, length * sizeof(void*));
    
    // Free old weaken back references
    SPVM_RUNTIME_API_free_memory_block(runtime, object->weaken_back_refs);
    
    object->weaken_back_refs = new_weaken_back_refs;
    object->weaken_back_refs_capacity = new_capacity;
  }
  
  object->weaken_back_refs[length] = object_address;
  object->weaken_back_refs_length++;
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

  int32_t length = object->weaken_back_refs_length;
  
  void** weaken_back_refs = object->weaken_back_refs;
  
  {
    int32_t i;
    int32_t found_index = -1;
    for (i = 0; i < length; i++) {
      if (weaken_back_refs[i] == object_address) {
        found_index = i;
        break;
      }
    }
    
    if (found_index == -1) {
      fprintf(stderr, "Not weakened address is specified(SPVM_RUNTIME_API_unweaken())");
      abort();
    }
    if (found_index < length - 1) {
      int32_t move_length = length - found_index - 1;
      memmove(&weaken_back_refs[found_index], &weaken_back_refs[found_index + 1], move_length * sizeof(void*));
    }
  }
  object->weaken_back_refs_length--;
}

void SPVM_RUNTIME_API_set_exception(SPVM_ENV* env, SPVM_OBJECT* exception) {
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (runtime->exception != NULL) {
    SPVM_RUNTIME_API_dec_ref_count(env, (SPVM_OBJECT*)runtime->exception);
  }
  
  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&runtime->exception, exception);
  
  if (runtime->exception != NULL) {
    runtime->exception->ref_count++;
  }
}

SPVM_OBJECT* SPVM_RUNTIME_API_get_exception(SPVM_ENV* env) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  return runtime->exception;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_byte_array(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_byte_array_raw(env, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_short_array(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_short_array_raw(env, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_int_array(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_int_array_raw(env, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_long_array(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_long_array_raw(env, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_float_array(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_float_array_raw(env, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_double_array(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_double_array_raw(env, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_object_array(SPVM_ENV* env, int32_t basic_type_id, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_object_array_raw(env, basic_type_id, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_multi_array(SPVM_ENV* env, int32_t basic_type_id, int32_t element_dimension, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_multi_array_raw(env, basic_type_id, element_dimension, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_value_t_array(SPVM_ENV* env, int32_t basic_type_id, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_value_t_array_raw(env, basic_type_id, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_object(SPVM_ENV* env, int32_t basic_type_id) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_object_raw(env, basic_type_id);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_pointer(SPVM_ENV* env, int32_t basic_type_id, void* pointer) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_pointer_raw(env, basic_type_id, pointer);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_string(SPVM_ENV* env, const char* bytes, int32_t length) {
  (void)env;
  
  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_string_raw(env, bytes, length);
  
  SPVM_RUNTIME_API_push_mortal(env, object);
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_byte_array_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  
  // If lenght is less than 0, return NULL.
  if (length < 0) {
    return NULL;
  }
  
  // Create object
  SPVM_RUNTIME* runtime = env->runtime;
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Body byte size. Alloc length + 1
  size_t body_byte_size = (length + 1) * sizeof(SPVM_VALUE_byte);
  if (body_byte_size > SIZE_MAX) {
    return NULL;
  }
  
  // Alloc body by 0
  void* body = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, body_byte_size);
  if (body == NULL) {
    return NULL;
  }
  
  // Set object fields
  object->body = body;
  object->type_dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_BYTE;
  object->elements_length = length;
  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_short_array_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = env->runtime;

  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_short));
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_SHORT;
  
  // Set array length
  object->elements_length = length;

  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY;

  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_int_array_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = env->runtime;

  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_int));
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_INT;

  // Set array length
  object->elements_length = length;

  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_long_array_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = env->runtime;
  
  if (length < 0) {
    return NULL;
  }
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));
  
  // Alloc body length + 1
  object->body = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_long));
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_LONG;

  // Set array length
  object->elements_length = length;

  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_float_array_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = env->runtime;

  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_float));
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_FLOAT;

  // Set array length
  object->elements_length = length;

  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_double_array_raw(SPVM_ENV* env, int32_t length) {
  (void)env;
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_double));
  
  object->type_dimension = 1;
  object->basic_type_id = SPVM_BASIC_TYPE_C_ID_DOUBLE;
  
  // Set array length
  object->elements_length = length;

  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_object_array_raw(SPVM_ENV* env, int32_t basic_type_id, int32_t length) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;

  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_object));
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];

  object->basic_type_id = basic_type->id;
  object->type_dimension = 1;

  // Set array length
  object->elements_length = length;
  
  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_OBJECT_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_multi_array_raw(SPVM_ENV* env, int32_t basic_type_id, int32_t element_dimension, int32_t length) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, (length + 1) * sizeof(SPVM_VALUE_object));
  
  object->basic_type_id = basic_type_id;
  object->type_dimension = element_dimension + 1;
  
  // Set array length
  object->elements_length = length;
  
  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_OBJECT_ARRAY;
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_value_t_array_raw(SPVM_ENV* env, int32_t basic_type_id, int32_t length) {
  (void)env;

  SPVM_RUNTIME* runtime = env->runtime;

  // valut_t array dimension must be 1
  SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
  const char* basic_type_name = &runtime->string_pool[basic_type->name_id];
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, basic_type_name, strlen(basic_type_name));
  int32_t fields_length = package->fields->length;
  SPVM_RUNTIME_FIELD* field_first = SPVM_LIST_fetch(package->fields, 0);
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

  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  object->body = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, (length + 1) * unit_size * fields_length);

  object->basic_type_id = basic_type->id;
  object->type_dimension = 1;

  // Set array length
  object->elements_length = length;

  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_VALUE_ARRAY;

  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_object_raw(SPVM_ENV* env, int32_t basic_type_id) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
  
  SPVM_RUNTIME_PACKAGE* package;
  if (basic_type->package_id == 0) {
    package = NULL;
  }
  else {
    package = &runtime->packages[basic_type->package_id];
  }
  if (!package) {
    return NULL;
  }

  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  // Alloc body length + 1
  int32_t fields_length = package->fields->length;
  object->body = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, (fields_length + 1) * sizeof(SPVM_VALUE));
  
  object->basic_type_id = basic_type->id;
  object->type_dimension = 0;

  object->elements_length = fields_length;

  // Object type id
  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_PACKAGE;
  
  // Has destructor
  if (package->destructor_sub_id > 0) {
    object->has_destructor = 1;
  }
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_pointer_raw(SPVM_ENV* env, int32_t basic_type_id, void* pointer) {
  (void)env;
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];

  SPVM_RUNTIME_PACKAGE* package;
  if (basic_type->package_id == 0) {
    package = NULL;
  }
  else {
    package = &runtime->packages[basic_type->package_id];
  }
  if (!package) {
    return NULL;
  }

  // Create object
  SPVM_OBJECT* object = SPVM_RUNTIME_API_alloc_memory_block_zero(runtime, sizeof(SPVM_OBJECT));

  object->body = pointer;

  object->basic_type_id = basic_type->id;
  object->type_dimension = 0;

  object->elements_length = 1;

  // Object type id
  object->runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_PACKAGE;
  
  // Has destructor
  if (package->destructor_sub_id > 0) {
    object->has_destructor = 1;
  }
  
  return object;
}

SPVM_OBJECT* SPVM_RUNTIME_API_new_string_raw(SPVM_ENV* env, const char* bytes, int32_t length) {
  (void)env;

  if (length == 0) {
    length = strlen((char*)bytes);
  }

  SPVM_OBJECT* object = SPVM_RUNTIME_API_new_byte_array_raw(env, length);
  
  if (length > 0) {
    if (bytes == NULL) {
      memset(object->body, 0, length);
    }
    else {
      memcpy(object->body, (char*)bytes, length);
    }
  }

  return object;
}

int32_t SPVM_RUNTIME_API_get_array_length(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return object->elements_length;
}

int8_t* SPVM_RUNTIME_API_get_byte_array_elements(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;

  return *(SPVM_VALUE_byte**)&object->body;
}

int16_t* SPVM_RUNTIME_API_get_short_array_elements(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return *(SPVM_VALUE_short**)&object->body;
}

int32_t* SPVM_RUNTIME_API_get_int_array_elements(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return *(SPVM_VALUE_int**)&object->body;
}

int64_t* SPVM_RUNTIME_API_get_long_array_elements(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return *(SPVM_VALUE_long**)&object->body;
}

float* SPVM_RUNTIME_API_get_float_array_elements(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return *(SPVM_VALUE_float**)&object->body;
}

double* SPVM_RUNTIME_API_get_double_array_elements(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return *(SPVM_VALUE_double**)&object->body;
}

SPVM_OBJECT* SPVM_RUNTIME_API_get_object_array_element(SPVM_ENV* env, SPVM_OBJECT* object, int32_t index) {
  (void)env;
  
  assert(object);
  assert(index >= 0);
  assert(index <= object->elements_length);
  
  SPVM_OBJECT* oval = SPVM_RUNTIME_C_INLINE_GET_OBJECT_NO_WEAKEN_ADDRESS((*(SPVM_VALUE_object**)&(*(void**)object))[index]);
  
  return oval;
}

void SPVM_RUNTIME_API_set_object_array_element(SPVM_ENV* env, SPVM_OBJECT* object, int32_t index, SPVM_OBJECT* oval) {
  (void)env;
  
  void* object_address = &((*(SPVM_VALUE_object**)&(*(void**)object))[index]);
  
  assert(object);
  assert(index >= 0);
  assert(index <= object->elements_length);
  
  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(object_address, oval);
}

void* SPVM_RUNTIME_API_get_pointer(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return object->body;
}

void SPVM_RUNTIME_API_inc_dec_ref_count(SPVM_ENV* env, SPVM_OBJECT* object) {
  SPVM_RUNTIME_API_inc_ref_count(env, object);
  SPVM_RUNTIME_API_dec_ref_count(env, object);
}

void SPVM_RUNTIME_API_dec_ref_count_only(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  if (object != NULL) {
    assert(object->ref_count > 0);
    // Increment reference count
    object->ref_count--;
  }
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
    if (basic_type->package_id == 0) {
      package = NULL;
    }
    else {
      package = &runtime->packages[basic_type->package_id];
    }
    int32_t is_pointer = 0;
    if (package) {
      if (package->flag & SPVM_PACKAGE_C_FLAG_IS_POINTER) {
        is_pointer = 1;
      }
    }

    if (object->runtime_type == SPVM_TYPE_C_RUNTIME_TYPE_OBJECT_ARRAY) {
      int32_t length = object->elements_length;
      {
        int32_t index;
        for (index = 0; index < length; index++) {
          SPVM_OBJECT** object_field_address = (SPVM_OBJECT**)&((*(SPVM_VALUE_object**)&(*(void**)object))[index]);
          if (*object_field_address != NULL) {
            // If object is weak, unweaken
            if (SPVM_RUNTIME_API_isweak(env, object_field_address)) {
              SPVM_RUNTIME_API_unweaken(env, object_field_address);
              (*object_field_address)->ref_count--;
            }
            else {
              SPVM_RUNTIME_API_dec_ref_count(env, *object_field_address);
            }
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
      
      {
        int32_t index;
        for (index = 0; index < package->object_field_indexes->length; index++) {
          int32_t object_field_index = (intptr_t)SPVM_LIST_fetch(package->object_field_indexes, index);
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          
          SPVM_OBJECT** object_field_address = (SPVM_OBJECT**)&fields[object_field_index];
          if (*object_field_address != NULL) {
            // If object is weak, unweaken
            if (SPVM_RUNTIME_API_isweak(env, object_field_address)) {
              SPVM_RUNTIME_API_unweaken(env, object_field_address);
              (*object_field_address)->ref_count--;
            }
            else {
              SPVM_RUNTIME_API_dec_ref_count(env, *object_field_address);
            }
          }
        }
      }
    }
    if (object->weaken_back_refs != NULL) {
      SPVM_RUNTIME_API_free_weaken_back_refs(env, object->weaken_back_refs, object->weaken_back_refs_length);
    }
    
    // Free object body
    if (object->body != NULL && !is_pointer) {
      SPVM_RUNTIME_API_free_memory_block(runtime, object->body);
    }
    
    // Free object
    SPVM_RUNTIME_API_free_memory_block(runtime, object);
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

int32_t SPVM_RUNTIME_API_get_ref_count(SPVM_ENV* env, SPVM_OBJECT* object) {
  (void)env;
  
  return object->ref_count;
}

int32_t SPVM_RUNTIME_API_get_field_index(SPVM_ENV* env, int32_t field_id) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
  
  return field->index;
}

int32_t SPVM_RUNTIME_API_get_field_id(SPVM_ENV* env, const char* package_name, const char* field_name, const char* signature) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Package
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));
  if (!package) {
    return 0;
  }
  
  // Field
  SPVM_RUNTIME_FIELD* field = SPVM_HASH_fetch(package->field_symtable, field_name, strlen(field_name));
  if (!field) {
    return 0;
  }

  // Signature
  if (strcmp(signature, &runtime->string_pool[field->signature_id]) != 0) {
    return 0;
  }
  
  int32_t field_id = field->id;
  
  return field_id;
}

int32_t SPVM_RUNTIME_API_get_package_var_id(SPVM_ENV* env, const char* package_name, const char* package_var_name, const char* signature) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Package name
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));
  if (!package) {
    return 0;
  }
  
  // Package variable name
  SPVM_RUNTIME_PACKAGE_VAR* package_var = SPVM_HASH_fetch(package->package_var_symtable, package_var_name, strlen(package_var_name));
  if (!package_var) {
    return 0;
  }
  
  // Signature
  if (strcmp(signature, &runtime->string_pool[package_var->signature_id]) != 0) {
    return 0;
  }
  
  int32_t package_var_id = package_var->id;
  
  return package_var_id;
}

int32_t SPVM_RUNTIME_API_get_sub_id(SPVM_ENV* env, const char* package_name, const char* sub_name, const char* signature) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Package name
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));
  if (package == NULL) {
    return 0;
  }
  
  // Subroutine name
  SPVM_RUNTIME_SUB* sub = SPVM_HASH_fetch(package->sub_symtable, sub_name, strlen(sub_name));
  if (sub == NULL) {
    return 0;
  }
  
  
  // Signature
  if (strcmp(signature, &runtime->string_pool[sub->signature_id]) != 0) {
    return 0;
  }
  
  int32_t sub_id = sub->id;
  
  return sub_id;
}

int32_t SPVM_RUNTIME_API_get_sub_id_method_call(SPVM_ENV* env, SPVM_OBJECT* object, const char* sub_name, const char* signature) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Package name
  SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[object->basic_type_id];
  const char* basic_type_name = &runtime->string_pool[basic_type->name_id];
  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, basic_type_name, strlen(basic_type_name));  
  if (package == NULL) {
    return 0;
  }
  
  // Package which have only anon sub
  SPVM_RUNTIME_SUB* sub;
  if (package->flag & SPVM_PACKAGE_C_FLAG_IS_HAS_ONLY_ANON_SUB) {
    // Subroutine name
    sub = SPVM_LIST_fetch(package->subs, 0);
     
    // Signature
    if (strcmp(signature, &runtime->string_pool[sub->signature_id]) != 0) {
      return 0;
    }
  }
  // Normal sub
  else {
    // Subroutine name
    sub = SPVM_HASH_fetch(package->sub_symtable, sub_name, strlen(sub_name));
    if (sub == NULL) {
      return 0;
    }
    
    // Signature
    if (strcmp(signature, &runtime->string_pool[sub->signature_id]) != 0) {
      return 0;
    }
  }
  
  return sub->id;
}

int32_t SPVM_RUNTIME_API_get_basic_type_id(SPVM_ENV* env, const char* name) {
  (void)env;
  
  if (name == NULL) {
    return 0;
  }
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_HASH_fetch(runtime->basic_type_symtable, name, strlen(name));
  if (basic_type) {
    int32_t basic_type_id = basic_type->id;
    return basic_type_id;
  }
  else {
    return 0;
  }
}

int8_t SPVM_RUNTIME_API_get_byte_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
  
  // Get field value
  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
  SPVM_VALUE_byte value = *(SPVM_VALUE_byte*)&fields[field->index];

  return value;
}

int16_t SPVM_RUNTIME_API_get_short_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
  
  // Get field value
  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
  SPVM_VALUE_short value = *(SPVM_VALUE_short*)&fields[field->index];
  
  return value;
}

int32_t SPVM_RUNTIME_API_get_int_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
  SPVM_VALUE_int value = *(SPVM_VALUE_int*)&fields[field->index];
  
  return value;
}

int64_t SPVM_RUNTIME_API_get_long_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
  SPVM_VALUE_long value = *(SPVM_VALUE_long*)&fields[field->index];
  
  return value;
}

float SPVM_RUNTIME_API_get_float_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
  SPVM_VALUE_float value = *(SPVM_VALUE_float*)&fields[field->index];
  
  return value;
}

double SPVM_RUNTIME_API_get_double_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
  SPVM_VALUE_double value = *(SPVM_VALUE_double*)&fields[field->index];
  
  return value;
}

SPVM_OBJECT* SPVM_RUNTIME_API_get_object_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
  
  // Get field value
  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
  void* value = SPVM_RUNTIME_C_INLINE_GET_OBJECT_NO_WEAKEN_ADDRESS(*(SPVM_VALUE_object*)&fields[field->index]);
  
  return value;
}

void SPVM_RUNTIME_API_set_byte_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id, int8_t value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
  *(SPVM_VALUE_byte*)&fields[field->index] = value;
}

void SPVM_RUNTIME_API_set_short_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id, int16_t value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
  *(SPVM_VALUE_short*)&fields[field->index] = value;
}

void SPVM_RUNTIME_API_set_int_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id, int32_t value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
  *(SPVM_VALUE_int*)&fields[field->index] = value;
}

void SPVM_RUNTIME_API_set_long_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id, int64_t value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
  *(SPVM_VALUE_long*)&fields[field->index] = value;
}

void SPVM_RUNTIME_API_set_float_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id, float value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
  *(SPVM_VALUE_float*)&fields[field->index] = value;
}

void SPVM_RUNTIME_API_set_double_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id, double value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];

  // Get field value
  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
  *(SPVM_VALUE_double*)&fields[field->index] = value;
}

void SPVM_RUNTIME_API_set_object_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_id, SPVM_OBJECT* value) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Field
  SPVM_RUNTIME_FIELD* field = &runtime->fields[field_id];
  
  // Get field value
  SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
  void* object_field_address = (SPVM_VALUE_object*)&fields[field->index];

  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(object_field_address, value);
}

void* SPVM_RUNTIME_API_alloc_memory_block_zero(SPVM_RUNTIME* runtime, size_t byte_size) {
  (void)runtime;
  
  void* block = SPVM_RUNTIME_API_safe_malloc_zero(byte_size);
  runtime->memory_blocks_count++;
  
#ifdef SPVM_DEBUG_OBJECT_COUNT
  fprintf(stderr, "[INC_MEMORY_BLOCK_CNT] %d\n", runtime->memory_blocks_count);
#endif
  
  return block;
}

void SPVM_RUNTIME_API_free_memory_block(SPVM_RUNTIME* runtime, void* block) {
  (void)runtime;
  
  if (block) {
    free(block);
    runtime->memory_blocks_count--;
    
#ifdef SPVM_DEBUG_OBJECT_COUNT
    fprintf(stderr, "[INC_MEMORY_BLOCK_CNT] %d\n", runtime->memory_blocks_count);
#endif
  }
}

void* SPVM_RUNTIME_API_safe_malloc_zero(size_t byte_size) {
  
  if (byte_size < 1) {
    fprintf(stderr, "Failed to allocate memory. Size must be more than 0(SPVM_RUNTIME_API_safe_malloc_zero())\n");
    abort();
  }
  
  if ((size_t)byte_size > SIZE_MAX) {
    fprintf(stderr, "Failed to allocate memory. Size is too big(SPVM_RUNTIME_API_safe_malloc_zero())\n");
    abort();
  }
  
  void* block = calloc(1, (size_t)byte_size);
  
  if (block == NULL) {
    fprintf(stderr, "Failed to allocate memory. malloc function return NULL(SPVM_RUNTIME_API_safe_malloc_zero())\n");
    abort();
  }
  
  return block;
}
