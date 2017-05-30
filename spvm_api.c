#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "spvm.h"
#include "spvm_api.h"
#include "spvm_hash.h"
#include "spvm_allocator_util.h"
#include "spvm_bytecode_array.h"
#include "spvm_extention.h"
#include "spvm_bytecode.h"
#include "spvm_allocator_runtime.h"
#include "spvm_constant_pool.h"
#include "spvm_constant_pool_sub.h"
#include "spvm_constant_pool_package.h"
#include "spvm_constant_pool_field.h"
#include "spvm_resolved_type.h"
#include "spvm_env.h"
#include "spvm_sv.h"
#include "spvm_compat.h"
#include "spvm_ref.h"
#include "spvm_ref_array.h"
#include "spvm_ref_object.h"
#include "spvm_ref_string.h"
#include "spvm_value.h"

void SPVM_API_call_sub(SPVM* spvm, SPVM_ENV* env, const char* sub_abs_name) {
  (void)spvm;
  (void)env;
  
  // Jump table for direct threaded code
  static void* jump[] = {
    &&case_SPVM_BYTECODE_C_CODE_NOP,
    &&case_SPVM_BYTECODE_C_CODE_UNDEF,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_BYTE_0,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_BYTE_1,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_SHORT_0,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_SHORT_1,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_M1,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_0,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_1,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_2,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_3,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_4,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_5,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_M1,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_0,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_1,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_2,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_3,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_4,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_5,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_FLOAT_0,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_FLOAT_1,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_FLOAT_2,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_DOUBLE_0,
    &&case_SPVM_BYTECODE_C_CODE_CONSTANT_DOUBLE_1,
    &&case_SPVM_BYTECODE_C_CODE_PUSH_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_PUSH_BYTE_TO_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_PUSH_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_PUSH_BYTE_TO_INT,
    &&case_SPVM_BYTECODE_C_CODE_PUSH_SHORT_TO_INT,
    &&case_SPVM_BYTECODE_C_CODE_PUSH_BYTE_TO_LONG,
    &&case_SPVM_BYTECODE_C_CODE_PUSH_SHORT_TO_LONG,
    &&case_SPVM_BYTECODE_C_CODE_LOAD_CONSTANT,
    &&case_SPVM_BYTECODE_C_CODE_ADD_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_ADD_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_ADD_INT,
    &&case_SPVM_BYTECODE_C_CODE_ADD_LONG,
    &&case_SPVM_BYTECODE_C_CODE_ADD_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_ADD_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_SUBTRACT_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_SUBTRACT_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_SUBTRACT_INT,
    &&case_SPVM_BYTECODE_C_CODE_SUBTRACT_LONG,
    &&case_SPVM_BYTECODE_C_CODE_SUBTRACT_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_SUBTRACT_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_MULTIPLY_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_MULTIPLY_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_MULTIPLY_INT,
    &&case_SPVM_BYTECODE_C_CODE_MULTIPLY_LONG,
    &&case_SPVM_BYTECODE_C_CODE_MULTIPLY_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_MULTIPLY_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_DIVIDE_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_DIVIDE_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_DIVIDE_INT,
    &&case_SPVM_BYTECODE_C_CODE_DIVIDE_LONG,
    &&case_SPVM_BYTECODE_C_CODE_DIVIDE_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_DIVIDE_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_REMAINDER_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_REMAINDER_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_REMAINDER_INT,
    &&case_SPVM_BYTECODE_C_CODE_REMAINDER_LONG,
    &&case_SPVM_BYTECODE_C_CODE_REMAINDER_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_REMAINDER_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_NEGATE_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_NEGATE_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_NEGATE_INT,
    &&case_SPVM_BYTECODE_C_CODE_NEGATE_LONG,
    &&case_SPVM_BYTECODE_C_CODE_NEGATE_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_NEGATE_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_LEFT_SHIFT_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_LEFT_SHIFT_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_LEFT_SHIFT_INT,
    &&case_SPVM_BYTECODE_C_CODE_LEFT_SHIFT_LONG,
    &&case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_INT,
    &&case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_LONG,
    &&case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_INT,
    &&case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_LONG,
    &&case_SPVM_BYTECODE_C_CODE_BIT_AND_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_BIT_AND_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_BIT_AND_INT,
    &&case_SPVM_BYTECODE_C_CODE_BIT_AND_LONG,
    &&case_SPVM_BYTECODE_C_CODE_BIT_OR_BYTE ,
    &&case_SPVM_BYTECODE_C_CODE_BIT_OR_SHORT ,
    &&case_SPVM_BYTECODE_C_CODE_BIT_OR_INT,
    &&case_SPVM_BYTECODE_C_CODE_BIT_OR_LONG,
    &&case_SPVM_BYTECODE_C_CODE_BIT_XOR_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_BIT_XOR_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_BIT_XOR_INT,
    &&case_SPVM_BYTECODE_C_CODE_BIT_XOR_LONG,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_INT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_LONG,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_INT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_LONG,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_LONG,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_INT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_INT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_LONG,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_INT,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_LONG,
    &&case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_INC_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_INC_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_INC_INT,
    &&case_SPVM_BYTECODE_C_CODE_INC_LONG,
    &&case_SPVM_BYTECODE_C_CODE_LOAD,
    &&case_SPVM_BYTECODE_C_CODE_LOAD_0,
    &&case_SPVM_BYTECODE_C_CODE_LOAD_1,
    &&case_SPVM_BYTECODE_C_CODE_LOAD_2,
    &&case_SPVM_BYTECODE_C_CODE_LOAD_3,
    &&case_SPVM_BYTECODE_C_CODE_STORE,
    &&case_SPVM_BYTECODE_C_CODE_STORE_0,
    &&case_SPVM_BYTECODE_C_CODE_STORE_1,
    &&case_SPVM_BYTECODE_C_CODE_STORE_2,
    &&case_SPVM_BYTECODE_C_CODE_STORE_3,
    &&case_SPVM_BYTECODE_C_CODE_STORE_ADDRESS,
    &&case_SPVM_BYTECODE_C_CODE_POP,
    &&case_SPVM_BYTECODE_C_CODE_POP_ADDRESS,
    &&case_SPVM_BYTECODE_C_CODE_MALLOC_OBJECT,
    &&case_SPVM_BYTECODE_C_CODE_MALLOC_STRING,
    &&case_SPVM_BYTECODE_C_CODE_MALLOC_ARRAY,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_INT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_LONG,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_ADDRESS,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_INT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_LONG,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_ADDRESS,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LENGTH,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_INT,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_LONG,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_ADDRESS,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_INT,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_LONG,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_ADDRESS,
    &&case_SPVM_BYTECODE_C_CODE_CMP_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_CMP_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_CMP_LONG,
    &&case_SPVM_BYTECODE_C_CODE_CMP_FLOAT_L,
    &&case_SPVM_BYTECODE_C_CODE_CMP_FLOAT_G,
    &&case_SPVM_BYTECODE_C_CODE_CMP_DOUBLE_L,
    &&case_SPVM_BYTECODE_C_CODE_CMP_DOUBLE_G,
    &&case_SPVM_BYTECODE_C_CODE_IF_EQ_ZERO,
    &&case_SPVM_BYTECODE_C_CODE_IF_NE_ZERO,
    &&case_SPVM_BYTECODE_C_CODE_IF_LT_ZERO,
    &&case_SPVM_BYTECODE_C_CODE_IF_GE_ZERO,
    &&case_SPVM_BYTECODE_C_CODE_IF_GT_ZERO,
    &&case_SPVM_BYTECODE_C_CODE_IF_LE_ZERO,
    &&case_SPVM_BYTECODE_C_CODE_IF_EQ_CMP,
    &&case_SPVM_BYTECODE_C_CODE_IF_NE_CMP,
    &&case_SPVM_BYTECODE_C_CODE_IF_LT_CMP,
    &&case_SPVM_BYTECODE_C_CODE_IF_GE_CMP,
    &&case_SPVM_BYTECODE_C_CODE_IF_GT_CMP,
    &&case_SPVM_BYTECODE_C_CODE_IF_LE_CMP,
    &&case_SPVM_BYTECODE_C_CODE_IF_EQ_CMP_ADDRESS,
    &&case_SPVM_BYTECODE_C_CODE_IF_NE_CMP_ADDRESS,
    &&case_SPVM_BYTECODE_C_CODE_IF_NULL,
    &&case_SPVM_BYTECODE_C_CODE_IF_NON_NULL,
    &&case_SPVM_BYTECODE_C_CODE_TABLE_SWITCH,
    &&case_SPVM_BYTECODE_C_CODE_LOOKUP_SWITCH,
    &&case_SPVM_BYTECODE_C_CODE_GOTO,
    &&case_SPVM_BYTECODE_C_CODE_CALL_SUB,
    &&case_SPVM_BYTECODE_C_CODE_RETURN_VOID,
    &&case_SPVM_BYTECODE_C_CODE_RETURN,
    &&case_SPVM_BYTECODE_C_CODE_DIE,
    &&case_SPVM_BYTECODE_C_CODE_INC_REF_COUNT,
    &&case_SPVM_BYTECODE_C_CODE_DEC_REF_COUNT,
    &&case_SPVM_BYTECODE_C_CODE_WIDE,
  };
  
  // Constant pool
  SPVM_VALUE* constant_pool = spvm->constant_pool->values;
  
  // Bytecode
  uint8_t* bytecodes = spvm->bytecode_array->values;
  
  // Variables
  SPVM_VALUE* vars = &env->call_stack[env->call_stack_base];
  
  // Constant pool sub
  int32_t sub_constant_pool_address
    = (int32_t)(intptr_t)SPVM_HASH_search(spvm, spvm->constant_pool_sub_symtable, sub_abs_name, strlen(sub_abs_name));
  
  SPVM_VALUE* call_stack = env->call_stack;
  
  // Program counter
  register uint8_t* pc = NULL;
  
  // Top position of operand stack
  register int32_t operand_stack_top = env->operand_stack_top;
  
  register int32_t success;
  
  int32_t call_stack_base = env->call_stack_base;
  int32_t call_stack_base_start = call_stack_base;
  
  SPVM_REF_ARRAY* ref_array;
  SPVM_REF_OBJECT* ref_object;
  int32_t index;
  
  SPVM_ALLOCATOR_RUNTIME* allocator = spvm->allocator_runtime;
  
  SPVM_CONSTANT_POOL_SUB* constant_pool_sub = NULL;
  
  // Goto subroutine
  goto CALLSUB_COMMON;
  
  // while (1) {
    // switch (*pc) {
      case_SPVM_BYTECODE_C_CODE_CALL_SUB:
      {
        // Get subroutine ID
        sub_constant_pool_address
          = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
        
        CALLSUB_COMMON: {

          constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&constant_pool[sub_constant_pool_address];

          // Extend call stack(current size + 2(return address + call stack base before) + lexical variable area + operand_stack area)
          int32_t call_stack_max = operand_stack_top + 2 + constant_pool_sub->my_vars_length + constant_pool_sub->operand_stack_max;
          
          while (call_stack_max > env->call_stack_capacity) {
            env->call_stack_capacity = env->call_stack_capacity * 2;
            env->call_stack = call_stack = realloc(call_stack, sizeof(SPVM_VALUE) * env->call_stack_capacity);
          }

          operand_stack_top -= constant_pool_sub->args_length;

          // Prepare arguments
          memmove(&call_stack[operand_stack_top + 4], &call_stack[operand_stack_top + 1], constant_pool_sub->args_length * sizeof(SPVM_VALUE));

          // Save return address(operand + (throw or goto exception handler))
          if (call_stack_base == call_stack_base_start) {
            call_stack[operand_stack_top + 1].address_value = (void*)-1;
          }
          else {
            call_stack[operand_stack_top + 1].address_value = (void*)((intptr_t)pc + 5 + 3);
          }
          
          // Save sub_constant_pool_address
          call_stack[operand_stack_top + 2].int_value = sub_constant_pool_address;
          
          // Save vars base before
          call_stack[operand_stack_top + 3].int_value = call_stack_base;
          
          // Set vars base
          call_stack_base = operand_stack_top + 4;
          
          // Initialize my variables
          memset(&call_stack[call_stack_base + constant_pool_sub->args_length], 0, (constant_pool_sub->my_vars_length - constant_pool_sub->args_length) * sizeof(SPVM_VALUE));
          
          // Set variables to local variable
          vars = &call_stack[call_stack_base];
          
          // Set operant stack top
          operand_stack_top = call_stack_base + constant_pool_sub->my_vars_length - 1;
          
          // Call native sub
          if (constant_pool_sub->is_native) {
            // Set environment
            env->operand_stack_top = operand_stack_top;
            env->call_stack_base = call_stack_base;
            
            // Call native sub
            void (*native_address)(SPVM* spvm, SPVM_ENV* env) = constant_pool_sub->native_address;
            (*native_address)(spvm, env);
            
            // Get enviromnet
            operand_stack_top = env->operand_stack_top;
            call_stack_base = env->call_stack_base;
            
            if (env->abort) {
              goto case_SPVM_BYTECODE_C_CODE_DIE;
            }
            else {
              if (constant_pool_sub->has_return_value) {
                goto case_SPVM_BYTECODE_C_CODE_RETURN;
              }
              else {
                goto case_SPVM_BYTECODE_C_CODE_RETURN_VOID;
              }
            }
          }
          // Call normal sub
          else {
            pc = &bytecodes[constant_pool_sub->bytecode_base];
          }
          goto *jump[*pc];
        }
      }
      case_SPVM_BYTECODE_C_CODE_RETURN: {
        
        // Get return value
        SPVM_VALUE return_value = call_stack[operand_stack_top];
        
        // Restore operand stack top
        operand_stack_top = call_stack_base - 4;
        
        // Get return address
        uint8_t* return_address = call_stack[call_stack_base - 3].address_value;
        
        // Get sub_constant_pool_address
        sub_constant_pool_address = call_stack[call_stack_base - 2].int_value;
        
        // Resotre call stack base
        call_stack_base = call_stack[call_stack_base - 1].int_value;
        
        // Push return value
        operand_stack_top++;
        call_stack[operand_stack_top] = return_value;
        
        // Finish call sub
        if (call_stack_base == call_stack_base_start) {
          env->call_stack_base = call_stack_base;
          env->operand_stack_top = operand_stack_top;
          env->abort = 0;
          return;
        }
        else {
          // Restore vars
          vars = &call_stack[call_stack_base];
          
          pc = return_address;
          goto *jump[*pc];
        }
      }
      case_SPVM_BYTECODE_C_CODE_RETURN_VOID: {
        
        // Restore operand stack top
        operand_stack_top = call_stack_base - 4;
        
        // Return address
        uint8_t* return_address = call_stack[call_stack_base - 3].address_value;

        // Get sub_constant_pool_address
        sub_constant_pool_address = call_stack[call_stack_base - 2].int_value;

        // Resotre vars base
        call_stack_base = call_stack[call_stack_base - 1].int_value;
        
        // Finish call sub
        if (call_stack_base == call_stack_base_start) {
          env->call_stack_base = call_stack_base;
          env->operand_stack_top = operand_stack_top;
          env->abort = 0;
          return;
        }
        else {
          // Restore vars
          vars = &call_stack[call_stack_base];

          pc = return_address;
          goto *jump[*pc];
        }
      }
      case_SPVM_BYTECODE_C_CODE_DIE: {
        
        // Return value
        void* return_value = call_stack[operand_stack_top].address_value;
        
        // Restore operand stack top
        operand_stack_top = call_stack_base - 4;
        
        // Return address
        uint8_t* return_address = call_stack[call_stack_base - 3].address_value;

        // Get sub_constant_pool_address
        sub_constant_pool_address = call_stack[call_stack_base - 2].int_value;
        
        // Get constant pool sub
        constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&constant_pool[sub_constant_pool_address];
        
        // Sub name
        int32_t sub_name_constant_pool_address = constant_pool_sub->abs_name_constant_pool_address;
        const char* sub_name = SPVM_CONSTANT_POOL_get_string_value(spvm, spvm->constant_pool, sub_name_constant_pool_address);
        
        // File name
        int32_t file_name_constant_pool_address = constant_pool_sub->file_name_constant_pool_address;
        const char* file_name = SPVM_CONSTANT_POOL_get_string_value(spvm, spvm->constant_pool, file_name_constant_pool_address);
        
        SPVM_SV* sv_message = SPVM_API_get_string_sv(spvm, env, return_value);
        
        const char* pv_message = SPVM_API_get_string_value(spvm, env, return_value);
        
        // Free string if need
        if (return_value != NULL) {
          int32_t ref_count = SPVM_API_get_ref_count(spvm, env, return_value);
          if (ref_count == 0) {
            SPVM_SvREFCNT_dec(sv_message);
            SPVM_ALLOCATOR_RUNTIME_free_ref(spvm, spvm->allocator_runtime, return_value);
          }
        }

        // New sv
        SPVM_SV* new_sv_message = SPVM_COMPAT_newSVpvn(spvm, pv_message, strlen(pv_message));
        
        void* new_message_address = SPVM_API_create_string_sv(spvm, env, new_sv_message);
        
        SPVM_COMPAT_sv_catpvn(new_sv_message, "\n from ", strlen("\n from "));
        SPVM_COMPAT_sv_catpvn(new_sv_message, sub_name, strlen(sub_name));
        SPVM_COMPAT_sv_catpvn(new_sv_message, " at ", strlen(" at "));
        SPVM_COMPAT_sv_catpvn(new_sv_message, file_name, strlen(file_name));
        
        // Resotre vars base
        call_stack_base = call_stack[call_stack_base - 1].int_value;
        
        // Push return value
        operand_stack_top++;
        call_stack[operand_stack_top].address_value = new_message_address;
        
        // Finish call sub with exception
        if (call_stack_base == call_stack_base_start) {
          env->call_stack_base = call_stack_base;
          env->operand_stack_top = operand_stack_top;
          env->abort = 1;
          return;
        }
        else {
          // Restore vars
          vars = &call_stack[call_stack_base];
          
          pc = (uint8_t*)(return_address - 3);
          goto *jump[*pc];
        }
      }
      case_SPVM_BYTECODE_C_CODE_NOP:
        // Not used
        assert(0);
      case_SPVM_BYTECODE_C_CODE_UNDEF:
        operand_stack_top++;
        call_stack[operand_stack_top].address_value = (void*)NULL;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_BYTE_0:
        operand_stack_top++;
        call_stack[operand_stack_top].byte_value = 0;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_BYTE_1:
        operand_stack_top++;
        call_stack[operand_stack_top].byte_value = 1;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_SHORT_0:
        operand_stack_top++;
        call_stack[operand_stack_top].short_value = 0;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_SHORT_1:
        operand_stack_top++;
        call_stack[operand_stack_top].short_value = 1;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_M1:
        operand_stack_top++;
        call_stack[operand_stack_top].int_value = -1;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_0:
        operand_stack_top++;
        call_stack[operand_stack_top].int_value = 0;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_1:
        operand_stack_top++;
        call_stack[operand_stack_top].int_value = 1;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_2:
        operand_stack_top++;
        call_stack[operand_stack_top].int_value = 2;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_3:
        operand_stack_top++;
        call_stack[operand_stack_top].int_value = 3;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_4:
        operand_stack_top++;
        call_stack[operand_stack_top].int_value = 4;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_INT_5:
        operand_stack_top++;
        call_stack[operand_stack_top].int_value = 5;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_M1:
        operand_stack_top++;
        call_stack[operand_stack_top].long_value = -1L;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_0:
        operand_stack_top++;
        call_stack[operand_stack_top].long_value = 0L;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_1:
        operand_stack_top++;
        call_stack[operand_stack_top].long_value = 1L;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_2:
        
        operand_stack_top++;
        call_stack[operand_stack_top].long_value = 2L;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_3:
        operand_stack_top++;
        call_stack[operand_stack_top].long_value = 3L;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_4:
        operand_stack_top++;
        call_stack[operand_stack_top].long_value = 4L;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_LONG_5:
        operand_stack_top++;
        call_stack[operand_stack_top].long_value = 5L;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_FLOAT_0:
        operand_stack_top++;
        call_stack[operand_stack_top].float_value = 0.F;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_FLOAT_1:
        operand_stack_top++;
        call_stack[operand_stack_top].float_value = 1.F;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_FLOAT_2:
        operand_stack_top++;
        call_stack[operand_stack_top].float_value = 2.F;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_DOUBLE_0:
        operand_stack_top++;
        call_stack[operand_stack_top].double_value = 0.0;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONSTANT_DOUBLE_1:
        operand_stack_top++;
        call_stack[operand_stack_top].double_value = 1.0;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_PUSH_BYTE:
        operand_stack_top++;
        call_stack[operand_stack_top].byte_value = *(pc + 1);
        pc += 2;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_PUSH_BYTE_TO_SHORT:
        operand_stack_top++;
        call_stack[operand_stack_top].short_value = *(pc + 1);
        pc += 2;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_PUSH_SHORT:
        operand_stack_top++;
        call_stack[operand_stack_top].short_value = (*(pc + 1) << 8) +  *(pc + 2);
        pc += 3;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_PUSH_BYTE_TO_INT:
        operand_stack_top++;
        call_stack[operand_stack_top].int_value = *(pc + 1);
        pc += 2;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_PUSH_SHORT_TO_LONG:
        operand_stack_top++;
        call_stack[operand_stack_top].long_value = (*(pc + 1) << 8) +  *(pc + 2);
        pc += 3;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_PUSH_BYTE_TO_LONG:
        operand_stack_top++;
        call_stack[operand_stack_top].long_value = *(pc + 1);
        pc += 2;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_PUSH_SHORT_TO_INT:
        operand_stack_top++;
        call_stack[operand_stack_top].int_value = (*(pc + 1) << 8) +  *(pc + 2);
        pc += 3;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_LOAD_CONSTANT:
        operand_stack_top++;
        call_stack[operand_stack_top] = constant_pool[(*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4)];
        pc += 5;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_LOAD:
        operand_stack_top++;
        call_stack[operand_stack_top] = vars[*(pc + 1)];
        pc += 2;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_LOAD_0:
        operand_stack_top++;
        call_stack[operand_stack_top] = vars[0];
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_LOAD_1:
        operand_stack_top++;
        call_stack[operand_stack_top] = vars[1];
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_LOAD_2:
        operand_stack_top++;
        call_stack[operand_stack_top] = vars[2];
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_LOAD_3:
        operand_stack_top++;
        call_stack[operand_stack_top] = vars[3];
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_BYTE:
        ref_array = (SPVM_REF_ARRAY*)call_stack[operand_stack_top - 1].address_value;
        index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!ref_array, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The array of byte to get the element must not be undef");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          if (__builtin_expect(index < 0 || index >= ref_array->length, 0)) {
            SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The index of the array of byte to get the element is out of range");
            operand_stack_top++;
            call_stack[operand_stack_top].address_value = ref_string_error;
            goto case_SPVM_BYTECODE_C_CODE_DIE;
          }
          else {
            call_stack[operand_stack_top - 1].byte_value
              = *(int8_t*)((intptr_t)ref_array + sizeof(SPVM_REF_ARRAY) + sizeof(int8_t) * index);
            operand_stack_top--;
            pc++;
            goto *jump[*pc];
          }
        }
      case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_SHORT:
        ref_array = (SPVM_REF_ARRAY*)call_stack[operand_stack_top - 1].address_value;
        index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!ref_array, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The array of short to get the element must not be undef");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          if (__builtin_expect(index < 0 || index >= ref_array->length, 0)) {
            SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The index of the array of short to get the element is out of range");
            operand_stack_top++;
            call_stack[operand_stack_top].address_value = ref_string_error;
            goto case_SPVM_BYTECODE_C_CODE_DIE;
          }
          else {
            call_stack[operand_stack_top - 1].short_value
              = *(int16_t*)((intptr_t)ref_array + sizeof(SPVM_REF_ARRAY) + sizeof(int16_t) * index);
            operand_stack_top--;
            pc++;
            goto *jump[*pc];
          }
        }
      case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_INT:
        ref_array = (SPVM_REF_ARRAY*)call_stack[operand_stack_top - 1].address_value;
        index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!ref_array, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The array of int to get the element must not be undef");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          if (__builtin_expect(index < 0 || index >= ref_array->length, 0)) {
            SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The index of the array of int to get the element is out of range");
            operand_stack_top++;
            call_stack[operand_stack_top].address_value = ref_string_error;
            goto case_SPVM_BYTECODE_C_CODE_DIE;
          }
          else {
            call_stack[operand_stack_top - 1].int_value = *(int32_t*)((intptr_t)ref_array + sizeof(SPVM_REF_ARRAY) + sizeof(int32_t) * index);
            operand_stack_top--;
            pc++;
            goto *jump[*pc];
          }
        }
      case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_LONG: {
        ref_array = (SPVM_REF_ARRAY*)call_stack[operand_stack_top - 1].address_value;
        index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!ref_array, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The array of long to get the element must not be undef");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          if (__builtin_expect(index < 0 || index >= ref_array->length, 0)) {
            SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The index of the array of long to get the element is out of range");
            operand_stack_top++;
            call_stack[operand_stack_top].address_value = ref_string_error;
            goto case_SPVM_BYTECODE_C_CODE_DIE;
          }
          else {
            call_stack[operand_stack_top - 1].long_value = *(int64_t*)((intptr_t)ref_array + sizeof(SPVM_REF_ARRAY) + sizeof(int64_t) * index);
            operand_stack_top--;
            pc++;
            goto *jump[*pc];
          }
        }
      }
      case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_FLOAT:
        ref_array = (SPVM_REF_ARRAY*)call_stack[operand_stack_top - 1].address_value;
        index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!ref_array, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The array of float to get the element must not be undef");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          if (__builtin_expect(index < 0 || index >= ref_array->length, 0)) {
            SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The index of the array of float to get the element is out of range");
            operand_stack_top++;
            call_stack[operand_stack_top].address_value = ref_string_error;
            goto case_SPVM_BYTECODE_C_CODE_DIE;
          }
          else {
            call_stack[operand_stack_top - 1].float_value = *(float*)((intptr_t)ref_array + sizeof(SPVM_REF_ARRAY) + sizeof(float) * index);
            operand_stack_top--;
            pc++;
            goto *jump[*pc];
          }
        }
      case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_DOUBLE:
        ref_array = (SPVM_REF_ARRAY*)call_stack[operand_stack_top - 1].address_value;
        index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!ref_array, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The array of double to get the element must not be undef");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          if (__builtin_expect(index < 0 || index >= ref_array->length, 0)) {
            SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The index of the array of double to get the element is out of range");
            operand_stack_top++;
            call_stack[operand_stack_top].address_value = ref_string_error;
            goto case_SPVM_BYTECODE_C_CODE_DIE;
          }
          else {
            call_stack[operand_stack_top - 1].double_value = *(double*)((intptr_t)ref_array + sizeof(SPVM_REF_ARRAY) + sizeof(double) * index);
            operand_stack_top--;
            pc++;
            goto *jump[*pc];
          }
        }
      case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_ADDRESS:
        ref_array = (SPVM_REF_ARRAY*)call_stack[operand_stack_top - 1].address_value;
        index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!ref_array, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The array of reference to get the element must not be undef");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          if (__builtin_expect(index < 0 || index >= ref_array->length, 0)) {
            SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The index of the array of reference to get the element is out of range");
            operand_stack_top++;
            call_stack[operand_stack_top].address_value = ref_string_error;
            goto case_SPVM_BYTECODE_C_CODE_DIE;
          }
          else {
            call_stack[operand_stack_top - 1].address_value = *(void**)((intptr_t)ref_array + sizeof(SPVM_REF_ARRAY) + sizeof(void*) * index);
            operand_stack_top--;
            pc++;
            goto *jump[*pc];
          }
        }
      case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_BYTE:
        ref_array = (SPVM_REF_ARRAY*)call_stack[operand_stack_top - 2].address_value;
        index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!ref_array, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The array of byte to set the element must not be undef");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          if (__builtin_expect(index < 0 || index >= ref_array->length, 0)) {
            SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The index of the array of byte to set the element is out of range");
            operand_stack_top++;
            call_stack[operand_stack_top].address_value = ref_string_error;
            goto case_SPVM_BYTECODE_C_CODE_DIE;
          }
          else {
            *(int8_t*)((intptr_t)call_stack[operand_stack_top - 2].address_value + sizeof(SPVM_REF_ARRAY) + sizeof(int8_t) * call_stack[operand_stack_top - 1].int_value)
              = call_stack[operand_stack_top].byte_value;
            operand_stack_top -= 3;
            pc++;
            goto *jump[*pc];
          }
        }
      case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_SHORT:
        ref_array = (SPVM_REF_ARRAY*)call_stack[operand_stack_top - 2].address_value;
        index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!ref_array, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The array of short to set the element must not be undef");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          if (__builtin_expect(index < 0 || index >= ref_array->length, 0)) {
            SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The index of the array of short to set the element is out of range");
            operand_stack_top++;
            call_stack[operand_stack_top].address_value = ref_string_error;
            goto case_SPVM_BYTECODE_C_CODE_DIE;
          }
          else {
            *(int16_t*)((intptr_t)call_stack[operand_stack_top - 2].address_value + sizeof(SPVM_REF_ARRAY) + sizeof(int16_t) * call_stack[operand_stack_top - 1].int_value)
              = call_stack[operand_stack_top].short_value;
            operand_stack_top -= 3;
            pc++;
            goto *jump[*pc];
          }
        }
      case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_INT:
        ref_array = (SPVM_REF_ARRAY*)call_stack[operand_stack_top - 2].address_value;
        index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!ref_array, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The array of int to set the element must not be undef");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          if (__builtin_expect(index < 0 || index >= ref_array->length, 0)) {
            SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The index of the array of int to set the element is out of range");
            operand_stack_top++;
            call_stack[operand_stack_top].address_value = ref_string_error;
            goto case_SPVM_BYTECODE_C_CODE_DIE;
          }
          else {
            *(int32_t*)((intptr_t)ref_array + sizeof(SPVM_REF_ARRAY) + sizeof(int32_t) * index) = call_stack[operand_stack_top].int_value;
            operand_stack_top -= 3;
            pc++;
            goto *jump[*pc];
          }
        }
      case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_LONG:
        ref_array = (SPVM_REF_ARRAY*)call_stack[operand_stack_top - 2].address_value;
        index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!ref_array, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The array of long to set the element must not be undef");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          if (__builtin_expect(index < 0 || index >= ref_array->length, 0)) {
            SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The index of the array of int to set the element is out of range");
            operand_stack_top++;
            call_stack[operand_stack_top].address_value = ref_string_error;
            goto case_SPVM_BYTECODE_C_CODE_DIE;
          }
          else {
            *(int64_t*)((intptr_t)ref_array + sizeof(SPVM_REF_ARRAY) + sizeof(int64_t) * index) = call_stack[operand_stack_top].long_value;
            operand_stack_top -= 3;
            pc++;
            goto *jump[*pc];
          }
        }
      case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_FLOAT:
        ref_array = (SPVM_REF_ARRAY*)call_stack[operand_stack_top - 2].address_value;
        index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!ref_array, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The array of float to set the element must not be undef");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          if (__builtin_expect(index < 0 || index >= ref_array->length, 0)) {
            SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The index of the array of float to set the element is out of range");
            operand_stack_top++;
            call_stack[operand_stack_top].address_value = ref_string_error;
            goto case_SPVM_BYTECODE_C_CODE_DIE;
          }
          else {
            *(float*)((intptr_t)ref_array + sizeof(SPVM_REF_ARRAY) + sizeof(float) * index) = call_stack[operand_stack_top - 1].float_value;
            operand_stack_top -= 3;
            pc++;
            goto *jump[*pc];
          }
        }
      case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_DOUBLE:
        ref_array = (SPVM_REF_ARRAY*)call_stack[operand_stack_top - 2].address_value;
        index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!ref_array, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The array of double to set the element must not be undef");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          if (__builtin_expect(index < 0 || index >= ref_array->length, 0)) {
            SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The index of the array of double to set the element is out of range");
            operand_stack_top++;
            call_stack[operand_stack_top].address_value = ref_string_error;
            goto case_SPVM_BYTECODE_C_CODE_DIE;
          }
          else {
            *(double*)((intptr_t)call_stack[operand_stack_top - 2].address_value + sizeof(SPVM_REF_ARRAY) + sizeof(double) * call_stack[operand_stack_top - 1].int_value)
              = call_stack[operand_stack_top].double_value;
            operand_stack_top -= 3;
            pc++;
            goto *jump[*pc];
          }
        }
      case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_ADDRESS: {
        ref_array = (SPVM_REF_ARRAY*)call_stack[operand_stack_top - 2].address_value;
        index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!ref_array, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The array of reference to set the element must not be undef");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          if (__builtin_expect(index < 0 || index >= ref_array->length, 0)) {
            SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The index of the array of reference to set the element is out of range");
            operand_stack_top++;
            call_stack[operand_stack_top].address_value = ref_string_error;
            goto case_SPVM_BYTECODE_C_CODE_DIE;
          }
          else {
            void** array_index = (void**)((intptr_t)ref_array + sizeof(SPVM_REF_ARRAY) + sizeof(void*) * index);
            
            // Increment reference count
            SPVM_API_inc_ref_count(spvm, env, call_stack[operand_stack_top].address_value);
            
            // Decrement reference count
            SPVM_API_dec_ref_count(spvm, env, *array_index);
            
            // Store address
            *array_index = call_stack[operand_stack_top].address_value;
            
            operand_stack_top -= 3;
            pc++;
            goto *jump[*pc];
          }
        }
      }
      case_SPVM_BYTECODE_C_CODE_STORE:
        vars[*(pc + 1)] = call_stack[operand_stack_top];
        operand_stack_top--;
        pc += 2;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_STORE_0:
        vars[0] = call_stack[operand_stack_top];
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_STORE_1:
        vars[1] = call_stack[operand_stack_top];
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_STORE_2:
        vars[2] = call_stack[operand_stack_top];
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_STORE_3:
        vars[3] = call_stack[operand_stack_top];
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_STORE_ADDRESS: {
        int32_t vars_index = *(pc + 1);
        
        // Increment reference count
        SPVM_API_inc_ref_count(spvm, env, call_stack[operand_stack_top].address_value);
        
        // Decrement reference count
        SPVM_API_dec_ref_count(spvm, env, vars[vars_index].address_value);
        
        // Store address
        vars[vars_index] = call_stack[operand_stack_top];
        
        operand_stack_top--;
        pc += 2;
        goto *jump[*pc];
      }
      case_SPVM_BYTECODE_C_CODE_DEC_REF_COUNT: {
        void* address = call_stack[operand_stack_top].address_value;
        
        // Decrement reference count
        SPVM_API_dec_ref_count(spvm, env, address);
        
        pc += 1;
        goto *jump[*pc];
      }
      case_SPVM_BYTECODE_C_CODE_INC_REF_COUNT: {
        void* address = call_stack[operand_stack_top].address_value;
        
        // Increment reference count
        SPVM_API_inc_ref_count(spvm, env, address);
        
        pc += 1;
        goto *jump[*pc];
      }
      case_SPVM_BYTECODE_C_CODE_POP:
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_POP_ADDRESS: {
        
        SPVM_REF* data = call_stack[operand_stack_top].address_value;
        
        // Free object
        if (data != NULL) {
          int32_t ref_count = data->ref_count;
          if (ref_count == 0) {
            SPVM_ALLOCATOR_RUNTIME_free_ref(spvm, spvm->allocator_runtime, call_stack[operand_stack_top].address_value);
          }
        }
        
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
      case_SPVM_BYTECODE_C_CODE_ADD_BYTE:
        call_stack[operand_stack_top - 1].byte_value += call_stack[operand_stack_top].byte_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_ADD_SHORT:
        call_stack[operand_stack_top - 1].short_value += call_stack[operand_stack_top].short_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_ADD_INT:
        call_stack[operand_stack_top - 1].int_value += call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_ADD_LONG:
        call_stack[operand_stack_top - 1].long_value += call_stack[operand_stack_top].long_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_ADD_FLOAT:
        call_stack[operand_stack_top -1].float_value += call_stack[operand_stack_top - 1].float_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_ADD_DOUBLE:
        call_stack[operand_stack_top - 1].double_value += call_stack[operand_stack_top].double_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_SUBTRACT_BYTE:
        call_stack[operand_stack_top - 1].byte_value -= call_stack[operand_stack_top].byte_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_SUBTRACT_SHORT:
        call_stack[operand_stack_top - 1].short_value -= call_stack[operand_stack_top].short_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_SUBTRACT_INT:
        call_stack[operand_stack_top - 1].int_value -= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_SUBTRACT_LONG:
        call_stack[operand_stack_top - 1].long_value -= call_stack[operand_stack_top].long_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_SUBTRACT_FLOAT:
        call_stack[operand_stack_top - 1].float_value -= call_stack[operand_stack_top - 1].float_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_SUBTRACT_DOUBLE:
        call_stack[operand_stack_top - 1].double_value -= call_stack[operand_stack_top].double_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_MULTIPLY_BYTE:
        call_stack[operand_stack_top - 1].byte_value *= call_stack[operand_stack_top].byte_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_MULTIPLY_SHORT:
        call_stack[operand_stack_top - 1].short_value *= call_stack[operand_stack_top].short_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_MULTIPLY_INT:
        call_stack[operand_stack_top - 1].int_value *= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_MULTIPLY_LONG:
        call_stack[operand_stack_top - 1].long_value *= call_stack[operand_stack_top].long_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_MULTIPLY_FLOAT:
        call_stack[operand_stack_top - 1].float_value *= call_stack[operand_stack_top - 1].float_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_MULTIPLY_DOUBLE:
        call_stack[operand_stack_top - 1].double_value *= call_stack[operand_stack_top].double_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_DIVIDE_BYTE:
        call_stack[operand_stack_top - 1].byte_value /= call_stack[operand_stack_top].byte_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_DIVIDE_SHORT:
        call_stack[operand_stack_top - 1].short_value /= call_stack[operand_stack_top].short_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_DIVIDE_INT:
        call_stack[operand_stack_top - 1].int_value /= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_DIVIDE_LONG:
        call_stack[operand_stack_top - 1].long_value /= call_stack[operand_stack_top].long_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_DIVIDE_FLOAT:
        call_stack[operand_stack_top - 1].float_value /= call_stack[operand_stack_top - 1].float_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_DIVIDE_DOUBLE:
        call_stack[operand_stack_top - 1].double_value /= call_stack[operand_stack_top].double_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_REMAINDER_BYTE:
        call_stack[operand_stack_top - 1].byte_value
          = call_stack[operand_stack_top - 1].byte_value % call_stack[operand_stack_top].byte_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_REMAINDER_SHORT:
        call_stack[operand_stack_top - 1].short_value
          = call_stack[operand_stack_top - 1].short_value % call_stack[operand_stack_top].short_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_REMAINDER_INT:
        call_stack[operand_stack_top - 1].int_value
          = call_stack[operand_stack_top - 1].int_value % call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_REMAINDER_LONG:
        // z = a - (a/b) * b;
        call_stack[operand_stack_top - 1].long_value
          = call_stack[operand_stack_top - 1].long_value % call_stack[operand_stack_top].long_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_REMAINDER_FLOAT:
        call_stack[operand_stack_top - 1].float_value
          = (float)fmod((double)call_stack[operand_stack_top - 1].float_value, (double)call_stack[operand_stack_top - 1].float_value);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_REMAINDER_DOUBLE:
        call_stack[operand_stack_top - 1].double_value
          = fmod(call_stack[operand_stack_top - 1].double_value, call_stack[operand_stack_top].double_value);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_NEGATE_BYTE:
        call_stack[operand_stack_top].byte_value = -call_stack[operand_stack_top].byte_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_NEGATE_SHORT:
        call_stack[operand_stack_top].short_value = -call_stack[operand_stack_top].short_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_NEGATE_INT:
        call_stack[operand_stack_top].int_value = -call_stack[operand_stack_top].int_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_NEGATE_LONG:
        call_stack[operand_stack_top].long_value = -call_stack[operand_stack_top].long_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_NEGATE_FLOAT:
        call_stack[operand_stack_top].float_value = -call_stack[operand_stack_top].float_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_NEGATE_DOUBLE:
        call_stack[operand_stack_top].double_value = -call_stack[operand_stack_top].double_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_LEFT_SHIFT_BYTE:
        call_stack[operand_stack_top - 1].byte_value <<= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_LEFT_SHIFT_SHORT:
        call_stack[operand_stack_top - 1].short_value <<= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_LEFT_SHIFT_INT:
        call_stack[operand_stack_top - 1].int_value <<= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_LEFT_SHIFT_LONG:
        call_stack[operand_stack_top - 1].long_value <<= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_BYTE:
        call_stack[operand_stack_top - 1].byte_value >>= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_SHORT:
        call_stack[operand_stack_top - 1].short_value >>= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_INT:
        call_stack[operand_stack_top - 1].int_value >>= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_LONG:
        call_stack[operand_stack_top - 1].long_value >>= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_BYTE:
        call_stack[operand_stack_top - 1].byte_value
          = (call_stack[operand_stack_top - 1].byte_value >> call_stack[operand_stack_top].int_value) & 0xFF;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_SHORT:
        call_stack[operand_stack_top - 1].byte_value
          = (call_stack[operand_stack_top - 1].short_value >> call_stack[operand_stack_top].int_value) & 0xFFFF;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_INT:
        call_stack[operand_stack_top - 1].int_value
          = (call_stack[operand_stack_top - 1].int_value >> call_stack[operand_stack_top].int_value) & 0xFFFFFFFF;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_LONG:
        call_stack[operand_stack_top - 1].long_value
          = (call_stack[operand_stack_top - 1].long_value >> call_stack[operand_stack_top].int_value) & 0xFFFFFFFFFFFFFFFF;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_BIT_AND_BYTE:
        call_stack[operand_stack_top - 1].byte_value &= call_stack[operand_stack_top].byte_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_BIT_AND_SHORT:
        call_stack[operand_stack_top - 1].short_value &= call_stack[operand_stack_top].short_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_BIT_AND_INT:
        call_stack[operand_stack_top - 1].int_value &= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_BIT_AND_LONG:
        call_stack[operand_stack_top - 1].long_value &= call_stack[operand_stack_top].long_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_BIT_OR_BYTE:
        call_stack[operand_stack_top - 1].byte_value |= call_stack[operand_stack_top].byte_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_BIT_OR_SHORT:
        call_stack[operand_stack_top - 1].short_value |= call_stack[operand_stack_top].short_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_BIT_OR_INT:
        call_stack[operand_stack_top - 1].int_value |= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_BIT_OR_LONG:
        call_stack[operand_stack_top - 1].long_value |= call_stack[operand_stack_top].long_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_BIT_XOR_BYTE:
        call_stack[operand_stack_top - 1].byte_value ^= call_stack[operand_stack_top].byte_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_BIT_XOR_SHORT:
        call_stack[operand_stack_top - 1].short_value ^= call_stack[operand_stack_top].short_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_BIT_XOR_INT:
        call_stack[operand_stack_top - 1].int_value ^= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_BIT_XOR_LONG:
        call_stack[operand_stack_top - 1].long_value ^= call_stack[operand_stack_top].long_value;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_INC_BYTE:
        vars[*(pc + 1)].byte_value += (int8_t)*(pc + 2);
        pc += 3;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_INC_SHORT:
        vars[*(pc + 1)].short_value += (int8_t)*(pc + 2);
        pc += 3;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_INC_INT:
        vars[*(pc + 1)].int_value += (int8_t)*(pc + 2);
        pc += 3;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_INC_LONG:
        vars[*(pc + 1)].long_value += (int8_t)*(pc + 2);
        pc += 3;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_LONG:
        call_stack[operand_stack_top].long_value = (int64_t)call_stack[operand_stack_top].int_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_FLOAT:
        call_stack[operand_stack_top].float_value = (float)call_stack[operand_stack_top].int_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_DOUBLE:
        call_stack[operand_stack_top].double_value = (double)call_stack[operand_stack_top].int_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_INT:
        call_stack[operand_stack_top].int_value = (int32_t)call_stack[operand_stack_top].long_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_FLOAT:
        call_stack[operand_stack_top].float_value = (float)call_stack[operand_stack_top].long_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_DOUBLE:
        call_stack[operand_stack_top].double_value = (double)call_stack[operand_stack_top].long_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_INT:
        call_stack[operand_stack_top].int_value = (int32_t)call_stack[operand_stack_top].float_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_LONG:
        call_stack[operand_stack_top].long_value = (int64_t)call_stack[operand_stack_top].float_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_DOUBLE:
        call_stack[operand_stack_top].double_value = (double)call_stack[operand_stack_top].float_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_INT:
        call_stack[operand_stack_top].int_value = (int32_t)call_stack[operand_stack_top].double_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_LONG:
        call_stack[operand_stack_top].long_value = (int64_t)call_stack[operand_stack_top].double_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_FLOAT:
        call_stack[operand_stack_top].float_value = (float)call_stack[operand_stack_top].double_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_BYTE:
        call_stack[operand_stack_top].byte_value = (int8_t)(call_stack[operand_stack_top].int_value);
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_SHORT:
        call_stack[operand_stack_top].short_value = (int16_t)(call_stack[operand_stack_top].int_value);
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_INT:
        call_stack[operand_stack_top].int_value = (int32_t)call_stack[operand_stack_top].byte_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_INT:
        call_stack[operand_stack_top].int_value = (int32_t)call_stack[operand_stack_top].short_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_LONG:
        call_stack[operand_stack_top].long_value = (int64_t)call_stack[operand_stack_top].byte_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_FLOAT:
        call_stack[operand_stack_top - 1].float_value = (float)call_stack[operand_stack_top].byte_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_DOUBLE:
        call_stack[operand_stack_top].double_value = (double)call_stack[operand_stack_top].byte_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_BYTE:
        call_stack[operand_stack_top].byte_value = (int8_t)call_stack[operand_stack_top].short_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_LONG:
        call_stack[operand_stack_top].long_value = (int64_t)call_stack[operand_stack_top].short_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_FLOAT:
        call_stack[operand_stack_top - 1].float_value = (float)call_stack[operand_stack_top].short_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_DOUBLE:
        call_stack[operand_stack_top].double_value = (double)call_stack[operand_stack_top].short_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_BYTE:
        call_stack[operand_stack_top].byte_value = (int8_t)call_stack[operand_stack_top].long_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_SHORT:
        call_stack[operand_stack_top].short_value = (int16_t)call_stack[operand_stack_top].long_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_BYTE:
        // TODO
        call_stack[operand_stack_top].byte_value = (int8_t)call_stack[operand_stack_top - 1].float_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_SHORT:
        // TODO
        call_stack[operand_stack_top].short_value = (int16_t)call_stack[operand_stack_top - 1].float_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_BYTE:
        // TODO
        call_stack[operand_stack_top].byte_value = (int8_t)call_stack[operand_stack_top].double_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_SHORT:
        // TODO
        call_stack[operand_stack_top].byte_value = (int16_t)call_stack[operand_stack_top].double_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_SHORT:
        call_stack[operand_stack_top].short_value = (int16_t)call_stack[operand_stack_top].byte_value;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CMP_BYTE:
        // z = (x > y) + (x < y) * -1
        call_stack[operand_stack_top - 1].byte_value
          = (call_stack[operand_stack_top - 1].byte_value > call_stack[operand_stack_top].byte_value)
          + (call_stack[operand_stack_top - 1].byte_value < call_stack[operand_stack_top].byte_value) * -1;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CMP_SHORT:
        // z = (x > y) + (x < y) * -1
        call_stack[operand_stack_top - 1].short_value
          = (call_stack[operand_stack_top - 1].short_value > call_stack[operand_stack_top].short_value)
          + (call_stack[operand_stack_top - 1].short_value < call_stack[operand_stack_top].short_value) * -1;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CMP_LONG:
        // z = (x > y) + (x < y) * -1
        call_stack[operand_stack_top - 1].long_value
          = (call_stack[operand_stack_top - 1].long_value > call_stack[operand_stack_top].long_value)
          + (call_stack[operand_stack_top - 1].long_value < call_stack[operand_stack_top].long_value) * -1;
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CMP_FLOAT_L:
        call_stack[operand_stack_top - 1].int_value
          = (call_stack[operand_stack_top - 1].float_value > call_stack[operand_stack_top - 1].float_value)
          + (call_stack[operand_stack_top - 1].float_value < call_stack[operand_stack_top - 1].float_value) * -1
          + -!!(
            isnan(call_stack[operand_stack_top - 1].float_value)
            | isnan(call_stack[operand_stack_top - 1].float_value)
          );
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CMP_FLOAT_G:
        call_stack[operand_stack_top - 1].int_value
          = (call_stack[operand_stack_top - 1].float_value > call_stack[operand_stack_top - 1].float_value)
          + (call_stack[operand_stack_top - 1].float_value < call_stack[operand_stack_top - 1].float_value) * -1
          + !!(
            isnan(call_stack[operand_stack_top - 1].float_value)
            | isnan(call_stack[operand_stack_top - 1].float_value)
          );
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CMP_DOUBLE_L:
        call_stack[operand_stack_top - 1].int_value
          = (call_stack[operand_stack_top - 1].double_value > call_stack[operand_stack_top].double_value)
          + (call_stack[operand_stack_top - 1].double_value < call_stack[operand_stack_top].double_value) * -1
          + -!!(
            isnan(call_stack[operand_stack_top - 1].double_value)
            | isnan(call_stack[operand_stack_top].double_value)
          );
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_CMP_DOUBLE_G:
        call_stack[operand_stack_top - 1].int_value
          = (call_stack[operand_stack_top - 1].double_value > call_stack[operand_stack_top].double_value)
          + (call_stack[operand_stack_top - 1].double_value < call_stack[operand_stack_top].double_value) * -1
          + !!(
            isnan(call_stack[operand_stack_top - 1].double_value)
            | isnan(call_stack[operand_stack_top].double_value)
          );
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_IF_EQ_ZERO:
        success = call_stack[operand_stack_top].int_value == 0;
        pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
        operand_stack_top--;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_IF_NE_ZERO:
        success = call_stack[operand_stack_top].int_value != 0;
        pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
        operand_stack_top--;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_IF_LT_ZERO:
        success = call_stack[operand_stack_top].int_value < 0;
        pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
        operand_stack_top--;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_IF_GE_ZERO:
        success = call_stack[operand_stack_top].int_value >= 0;
        pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
        operand_stack_top--;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_IF_GT_ZERO:
        success = call_stack[operand_stack_top].int_value > 0;
        pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
        operand_stack_top--;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_IF_LE_ZERO:
        success = call_stack[operand_stack_top].int_value <= 0;
        pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
        operand_stack_top--;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_IF_EQ_CMP:
        success = call_stack[operand_stack_top - 1].int_value == call_stack[operand_stack_top].int_value;
        pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
        operand_stack_top -= 2;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_IF_NE_CMP:
        success = call_stack[operand_stack_top - 1].int_value != call_stack[operand_stack_top].int_value;
        pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
        operand_stack_top -= 2;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_IF_LT_CMP:
        success = call_stack[operand_stack_top - 1].int_value < call_stack[operand_stack_top].int_value;
        pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
        operand_stack_top -= 2;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_IF_GE_CMP:
        success = call_stack[operand_stack_top - 1].int_value >= call_stack[operand_stack_top].int_value;
        pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
        operand_stack_top -= 2;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_IF_GT_CMP:
        success = call_stack[operand_stack_top - 1].int_value > call_stack[operand_stack_top].int_value;
        pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
        operand_stack_top -= 2;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_IF_LE_CMP:
        success = call_stack[operand_stack_top - 1].int_value <= call_stack[operand_stack_top].int_value;
        pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
        operand_stack_top -= 2;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_IF_EQ_CMP_ADDRESS:
        success = call_stack[operand_stack_top - 1].address_value == call_stack[operand_stack_top].address_value;
        pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
        operand_stack_top -= 2;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_IF_NE_CMP_ADDRESS:
        success = call_stack[operand_stack_top - 1].address_value != call_stack[operand_stack_top].address_value;
        pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
        operand_stack_top -= 2;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_GOTO:
        pc += (int16_t)((*(pc + 1) << 8) +  *(pc + 2));
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_TABLE_SWITCH: {
        // Padding
        int32_t padding = (sizeof(int32_t) - 1) - ((intptr_t)pc % sizeof(int32_t));
        
        // default offset
        int32_t default_offset = *(int32_t*)(pc + padding + 1);
        
        // min
        int32_t min = *(int32_t*)(pc + padding + sizeof(int32_t) + 1);
        
        // max
        int32_t max = *(int32_t*)(pc + padding + sizeof(int32_t) * 2 + 1);
        
        if (call_stack[operand_stack_top].int_value >= min && call_stack[operand_stack_top].int_value <= max) {
          int32_t branch_offset
            = *(int32_t*)((pc + padding + sizeof(int32_t) * 3 + 1) + (call_stack[operand_stack_top].int_value - min) * sizeof(int32_t));
          pc += branch_offset;
        }
        else {
          pc += default_offset;
        }
        
        goto *jump[*pc];
      }
      case_SPVM_BYTECODE_C_CODE_LOOKUP_SWITCH: {

        // Padding
        int32_t padding = (sizeof(int32_t) - 1) - ((intptr_t)pc % sizeof(int32_t));

        /*
        1  default
        5  npare
        9  match  13 branch // min
        17 match 21 branch
        25 match 29 branch // max
        */
        
        // default offset
        int32_t default_offset = *(int32_t*)(pc + padding + 1);
        
        // npare
        int32_t pair_count = *(int32_t*)(pc + padding + sizeof(int32_t) + 1);
        
        // min
        int32_t min = *(int32_t*)(pc + padding + sizeof(int32_t) * 2 + 1);
        
        // max
        int32_t max = *(int32_t*)(pc + padding + sizeof(int32_t) * 2 + 1 + ((pair_count - 1) * sizeof(int32_t) * 2));
        
        if (call_stack[operand_stack_top].int_value >= min && call_stack[operand_stack_top].int_value <= max) {
          // 2 branch searching
          int32_t cur_min_pos = 0;
          int32_t cur_max_pos = pair_count - 1;

          while (1) {
            if (cur_max_pos < cur_min_pos) {
              pc += default_offset;
              goto *jump[*pc];
            }
            int32_t cur_half_pos = cur_min_pos + (cur_max_pos - cur_min_pos) / 2;
            int32_t cur_half = *(int32_t*)(pc + padding + sizeof(int32_t) * 2 + 1 + (cur_half_pos * sizeof(int32_t) * 2));
            
            if (call_stack[operand_stack_top].int_value > cur_half) {
              cur_min_pos = cur_half_pos + 1;
            }
            else if (call_stack[operand_stack_top].int_value < cur_half) {
              cur_max_pos = cur_half_pos - 1;
            }
            else {
              int32_t branch_offset = *(int32_t*)(pc + padding + sizeof(int32_t) * 2 + 1 + (cur_half_pos * sizeof(int32_t) * 2) + sizeof(int32_t));
              pc += branch_offset;
              goto *jump[*pc];
            }
          }
        }
        else {
          pc += default_offset;
        }
        
        goto *jump[*pc];
      }
      case_SPVM_BYTECODE_C_CODE_MALLOC_OBJECT: {
        // Get subroutine ID
        int32_t package_constant_pool_address
          = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
        SPVM_CONSTANT_POOL_PACKAGE* constant_pool_package = (SPVM_CONSTANT_POOL_PACKAGE*)&constant_pool[package_constant_pool_address];
        
        // Allocate memory
        int32_t fields_byte_size = constant_pool_package->byte_size;
        int32_t ref_object_byte_size = sizeof(SPVM_REF_OBJECT) + fields_byte_size;
        SPVM_REF_OBJECT* ref_object = SPVM_ALLOCATOR_RUNTIME_malloc(spvm, allocator, ref_object_byte_size);

        // Memory allocation error
        if (!ref_object) {
          // Sub name
          int32_t sub_name_constant_pool_address = constant_pool_sub->abs_name_constant_pool_address;
          const char* sub_name = SPVM_CONSTANT_POOL_get_string_value(spvm, spvm->constant_pool, sub_name_constant_pool_address);
          
          // File name
          int32_t file_name_constant_pool_address = constant_pool_sub->file_name_constant_pool_address;
          const char* file_name = SPVM_CONSTANT_POOL_get_string_value(spvm, spvm->constant_pool, file_name_constant_pool_address);

          fprintf(stderr, "Failed to allocate memory(malloc PACKAGE) from %s at %s", sub_name, file_name);
          abort();
        }
        
        // Set type
        ref_object->type = SPVM_REF_C_TYPE_OBJECT;
        
        // Set reference count
        ref_object->ref_count = 0;
        
        // Initialize reference fields by 0
        memset((void*)((intptr_t)ref_object + sizeof(SPVM_REF_OBJECT)), 0, sizeof(void*) * constant_pool_package->ref_fields_count);
        
        // Package constant pool address
        ref_object->package_constant_pool_address = package_constant_pool_address;
        
        assert(ref_object_byte_size == SPVM_REF_calcurate_byte_size(spvm, (SPVM_REF*)ref_object));
        
        // Push object
        operand_stack_top++;
        call_stack[operand_stack_top].address_value = ref_object;
        
        pc += 5;
        goto *jump[*pc];
      }
      case_SPVM_BYTECODE_C_CODE_MALLOC_STRING: {
        SPVM_VALUE* string_constant_pool_addresss
          = (SPVM_VALUE*)&constant_pool[(*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4)];
        
        int32_t length = string_constant_pool_addresss[0].int_value;
        char* pv = (char*)&string_constant_pool_addresss[1];
        
        // New sv
        SPVM_SV* sv = SPVM_COMPAT_newSVpvn(spvm, pv, length);
        
        // Create string
        SPVM_REF_STRING* ref_string = SPVM_API_create_string_sv(spvm, env, sv);
        
        // Memory allocation error
        if (!ref_string) {
          // Sub name
          int32_t sub_name_constant_pool_address = constant_pool_sub->abs_name_constant_pool_address;
          const char* sub_name = SPVM_CONSTANT_POOL_get_string_value(spvm, spvm->constant_pool, sub_name_constant_pool_address);
          
          // File name
          int32_t file_name_constant_pool_address = constant_pool_sub->file_name_constant_pool_address;
          const char* file_name = SPVM_CONSTANT_POOL_get_string_value(spvm, spvm->constant_pool, file_name_constant_pool_address);

          fprintf(stderr, "Failed to allocate memory(malloc STRING) from %s at %s", sub_name, file_name);
          abort();
        }
        
        // Set string
        operand_stack_top++;
        call_stack[operand_stack_top].address_value = ref_string;
        
        pc += 5;
        goto *jump[*pc];
      }
      case_SPVM_BYTECODE_C_CODE_MALLOC_ARRAY: {
        int32_t value_type = (int32_t)*(pc + 1);
        
        int32_t size = SPVM_REF_ARRAY_C_VALUE_SIZES[value_type];
        
        // Array length
        int32_t length = call_stack[operand_stack_top].int_value;
        
        // Allocate array
        int32_t ref_array_byte_size = sizeof(SPVM_REF_ARRAY) + size * length;
        SPVM_REF_ARRAY* ref_array = SPVM_ALLOCATOR_RUNTIME_malloc(spvm, allocator, ref_array_byte_size);
        
        // Memory allocation error
        if (!ref_array) {
          // Error message
          SPVM_REF_STRING* ref_string_message = SPVM_API_create_ref_string_from_pv(spvm, env, "Failed to allocate memory(MALLOC_ARRAY)");
          
          // Error is converted to exception
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_message;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        
        // Init null if sub type is array of reference
        if (value_type == SPVM_REF_ARRAY_C_VALUE_TYPE_REF) {
          memset(ref_array + sizeof(SPVM_REF_ARRAY), 0, size * length);
        }
        
        // Set type
        ref_array->type = SPVM_REF_C_TYPE_ARRAY;
        
        // Set sub type
        ref_array->value_type = value_type;
        
        // Set reference count
        ref_array->ref_count = 0;
        
        // Set array length
        ref_array->length = length;

        assert(ref_array_byte_size == SPVM_REF_calcurate_byte_size(spvm, (SPVM_REF*)ref_array));
        
        // Set array
        call_stack[operand_stack_top].address_value = ref_array;
        
        pc += 2;
        goto *jump[*pc];
      }
      case_SPVM_BYTECODE_C_CODE_ARRAY_LENGTH:
        call_stack[operand_stack_top].int_value = (int32_t)((SPVM_REF_ARRAY*)call_stack[operand_stack_top].address_value)->length;
        pc++;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_WIDE:
        // iload, fload, aload, lload, dload, istore, fstore, astore, lstore, dstore, or iinc
        
        if (*(pc + 1) == SPVM_BYTECODE_C_CODE_LOAD) {
          operand_stack_top++;
          call_stack[operand_stack_top] = vars[(*(pc + 2) << 8) + *(pc + 3)];
          pc +=4;
        }
        else if (*(pc + 1) == SPVM_BYTECODE_C_CODE_STORE) {
          vars[(*(pc + 2) << 8) + *(pc + 3)] = call_stack[operand_stack_top];
          operand_stack_top--;
          pc +=4;
        }
        else if (*(pc + 1) == SPVM_BYTECODE_C_CODE_STORE_ADDRESS) {
          int32_t var_index = (*(pc + 2) << 8) + *(pc + 3);

          // Increment reference count
          SPVM_API_inc_ref_count(spvm, env, call_stack[operand_stack_top].address_value);
          
          // Decrement reference count if original object is not null
          SPVM_API_dec_ref_count(spvm, env, vars[var_index].address_value);
          
          // Store address
          vars[var_index] = call_stack[operand_stack_top];
          
          operand_stack_top--;
          pc +=4;
        }
        else if (*(pc + 1) == SPVM_BYTECODE_C_CODE_INC_BYTE) {
          vars[(*(pc + 2) << 8) + *(pc + 3)].byte_value += (int8_t)((*(pc + 4) << 8) + *(pc + 5));
          pc += 6;
        }
        else if (*(pc + 1) == SPVM_BYTECODE_C_CODE_INC_SHORT) {
          vars[(*(pc + 2) << 8) + *(pc + 3)].short_value += (int16_t)((*(pc + 4) << 8) + *(pc + 5));
          pc += 6;
        }
        else if (*(pc + 1) == SPVM_BYTECODE_C_CODE_INC_INT) {
          vars[(*(pc + 2) << 8) + *(pc + 3)].int_value += (int32_t)((*(pc + 4) << 8) + *(pc + 5));
          pc += 6;
        }
        else if (*(pc + 1) == SPVM_BYTECODE_C_CODE_INC_LONG) {
          vars[(*(pc + 2) << 8) + *(pc + 3)].long_value += (int64_t)((*(pc + 4) << 8) + *(pc + 5));
          pc += 6;
        }
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_IF_NULL:
        success = call_stack[operand_stack_top].address_value == (void*)NULL;
        pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
        operand_stack_top--;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_IF_NON_NULL:
        success = call_stack[operand_stack_top].address_value != (void*)NULL;
        pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
        operand_stack_top--;
        goto *jump[*pc];
      case_SPVM_BYTECODE_C_CODE_GET_FIELD_BYTE: {
        ref_object = (SPVM_REF_OBJECT*)call_stack[operand_stack_top - 1].address_value;
        if (__builtin_expect(!ref_object, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The object to get an byte field must not be undefined.");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          int32_t field_constant_pool_address
            = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
          SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_constant_pool_address];
          call_stack[operand_stack_top].byte_value
            = *(int8_t*)((intptr_t)ref_object + sizeof(SPVM_REF_OBJECT) + constant_pool_field->package_byte_offset);
          pc += 5;
          goto *jump[*pc];
        }
      }
      case_SPVM_BYTECODE_C_CODE_GET_FIELD_SHORT: {
        ref_object = (SPVM_REF_OBJECT*)call_stack[operand_stack_top].address_value;
        if (__builtin_expect(!ref_object, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The object to get an short field must not be undefined.");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          int32_t field_constant_pool_address
            = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
          SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_constant_pool_address];
          call_stack[operand_stack_top].short_value
            = *(int16_t*)((intptr_t)ref_object + sizeof(SPVM_REF_OBJECT) + constant_pool_field->package_byte_offset);
          pc += 5;
          goto *jump[*pc];
        }
      }
      case_SPVM_BYTECODE_C_CODE_GET_FIELD_INT: {
        ref_object = (SPVM_REF_OBJECT*)call_stack[operand_stack_top].address_value;
        if (__builtin_expect(!ref_object, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The object to get an int field must not be undefined.");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          int32_t field_constant_pool_address
            = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
          SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_constant_pool_address];
          call_stack[operand_stack_top].int_value
            = *(int32_t*)((intptr_t)ref_object + sizeof(SPVM_REF_OBJECT) + constant_pool_field->package_byte_offset);
          pc += 5;
          goto *jump[*pc];
        }
      }
      case_SPVM_BYTECODE_C_CODE_GET_FIELD_LONG: {
        ref_object = (SPVM_REF_OBJECT*)call_stack[operand_stack_top].address_value;
        if (__builtin_expect(!ref_object, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The object to get an long field must not be undefined.");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          int32_t field_constant_pool_address
            = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
          SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_constant_pool_address];
          call_stack[operand_stack_top].long_value
            = *(int64_t*)((intptr_t)ref_object + sizeof(SPVM_REF_OBJECT) + constant_pool_field->package_byte_offset);
          pc += 5;
          goto *jump[*pc];
        }
      }
      case_SPVM_BYTECODE_C_CODE_GET_FIELD_FLOAT: {
        ref_object = (SPVM_REF_OBJECT*)call_stack[operand_stack_top].address_value;
        if (__builtin_expect(!ref_object, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The object to get an float field must not be undefined.");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          int32_t field_constant_pool_address
            = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
          SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_constant_pool_address];
          call_stack[operand_stack_top - 1].float_value
            = *(float*)((intptr_t)ref_object + sizeof(SPVM_REF_OBJECT) + constant_pool_field->package_byte_offset);
          pc += 5;
          goto *jump[*pc];
        }
      }
      case_SPVM_BYTECODE_C_CODE_GET_FIELD_DOUBLE: {
        ref_object = (SPVM_REF_OBJECT*)call_stack[operand_stack_top].address_value;
        if (__builtin_expect(!ref_object, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The object to get an double field must not be undefined.");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          int32_t field_constant_pool_address
            = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
          SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_constant_pool_address];
          call_stack[operand_stack_top].double_value
            = *(double*)((intptr_t)ref_object + sizeof(SPVM_REF_OBJECT) + constant_pool_field->package_byte_offset);
          pc += 5;
          goto *jump[*pc];
        }
      }
      case_SPVM_BYTECODE_C_CODE_GET_FIELD_ADDRESS: {
        ref_object = (SPVM_REF_OBJECT*)call_stack[operand_stack_top].address_value;
        if (__builtin_expect(!ref_object, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The object to get an reference field must not be undefined.");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          int32_t field_constant_pool_address
            = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
          SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_constant_pool_address];
          call_stack[operand_stack_top].address_value
            = *(void**)((intptr_t)call_stack[operand_stack_top].address_value + sizeof(SPVM_REF_OBJECT) + constant_pool_field->package_byte_offset);
          pc += 5;
          goto *jump[*pc];
        }
      }
      case_SPVM_BYTECODE_C_CODE_SET_FIELD_BYTE: {
        ref_object = (SPVM_REF_OBJECT*)call_stack[operand_stack_top - 1].address_value;
        if (__builtin_expect(!ref_object, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The object to set an byte field must not be undefined.");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          int32_t field_constant_pool_address
            = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
          SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_constant_pool_address];
          *(int8_t*)((intptr_t)ref_object + constant_pool_field->package_byte_offset)
            = call_stack[operand_stack_top].byte_value;
          operand_stack_top -= 2;
          pc += 5;
          goto *jump[*pc];
        }
      }
      case_SPVM_BYTECODE_C_CODE_SET_FIELD_SHORT: {
        ref_object = (SPVM_REF_OBJECT*)call_stack[operand_stack_top - 1].address_value;
        if (__builtin_expect(!ref_object, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The object to set an short field must not be undefined.");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          int32_t field_constant_pool_address
            = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
          SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_constant_pool_address];
          *(int16_t*)((intptr_t)ref_object + sizeof(SPVM_REF_OBJECT) + constant_pool_field->package_byte_offset)
            = call_stack[operand_stack_top].short_value;
          operand_stack_top -= 2;
          pc += 5;
          goto *jump[*pc];
        }
      }
      case_SPVM_BYTECODE_C_CODE_SET_FIELD_INT: {
        ref_object = (SPVM_REF_OBJECT*)call_stack[operand_stack_top - 1].address_value;
        if (__builtin_expect(!ref_object, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The object to set an int field must not be undefined.");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          int32_t field_constant_pool_address
            = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
          SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_constant_pool_address];
          *(int32_t*)((intptr_t)ref_object + sizeof(SPVM_REF_OBJECT) + constant_pool_field->package_byte_offset)
            = call_stack[operand_stack_top].int_value;
          operand_stack_top -= 2;
          pc += 5;
          goto *jump[*pc];
        }
      }
      case_SPVM_BYTECODE_C_CODE_SET_FIELD_LONG: {
        ref_object = (SPVM_REF_OBJECT*)call_stack[operand_stack_top - 1].address_value;
        if (__builtin_expect(!ref_object, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The object to set an long field must not be undefined.");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          int32_t field_constant_pool_address
            = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
          SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_constant_pool_address];
          *(int64_t*)((intptr_t)ref_object + sizeof(SPVM_REF_OBJECT) + constant_pool_field->package_byte_offset)
            = call_stack[operand_stack_top].long_value;
          operand_stack_top -= 2;
          pc += 5;
          goto *jump[*pc];
        }
      }
      case_SPVM_BYTECODE_C_CODE_SET_FIELD_FLOAT: {
        ref_object = (SPVM_REF_OBJECT*)call_stack[operand_stack_top - 1].address_value;
        if (__builtin_expect(!ref_object, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The object to set an float field must not be undefined.");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          int32_t field_constant_pool_address
            = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
          SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_constant_pool_address];
          *(float*)((intptr_t)ref_object + sizeof(SPVM_REF_OBJECT) + constant_pool_field->package_byte_offset)
            = call_stack[operand_stack_top - 1].float_value;
          operand_stack_top -= 2;
          pc += 5;
          goto *jump[*pc];
        }
      }
      case_SPVM_BYTECODE_C_CODE_SET_FIELD_DOUBLE: {
        ref_object = (SPVM_REF_OBJECT*)call_stack[operand_stack_top - 1].address_value;
        if (__builtin_expect(!ref_object, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The object to set an double field must not be undefined.");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          int32_t field_constant_pool_address
            = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
          SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_constant_pool_address];
          *(double*)((intptr_t)ref_object + sizeof(SPVM_REF_OBJECT) + constant_pool_field->package_byte_offset)
            = call_stack[operand_stack_top].double_value;
          operand_stack_top -= 2;
          pc += 5;
          goto *jump[*pc];
        }
      }
      case_SPVM_BYTECODE_C_CODE_SET_FIELD_ADDRESS: {
        ref_object = (SPVM_REF_OBJECT*)call_stack[operand_stack_top - 1].address_value;
        if (__builtin_expect(!ref_object, 0)) {
          SPVM_REF_STRING* ref_string_error = SPVM_API_create_ref_string_from_pv(spvm, env, "The object to set an reference field must not be undefined.");
          operand_stack_top++;
          call_stack[operand_stack_top].address_value = ref_string_error;
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          int32_t field_constant_pool_address
            = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
          SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_constant_pool_address];
          
          void** field_index = (void**)((intptr_t)ref_object + constant_pool_field->package_byte_offset);

          // Increment reference count
          SPVM_API_inc_ref_count(spvm, env, call_stack[operand_stack_top].address_value);
          
          // Decrement reference count
          SPVM_API_dec_ref_count(spvm, env, *field_index);
          
          // Store object
          *field_index = call_stack[operand_stack_top].address_value;
          
          operand_stack_top -= 2;
          pc += 5;
          goto *jump[*pc];
        }
      }
    // }
  // }
}

void SPVM_API_dec_ref_count(SPVM* spvm, SPVM_ENV* env, SPVM_REF* ref) {
  (void)spvm;
  (void)env;
  
  if (ref != NULL) {
    
    assert(ref->ref_count > 0);
    
    // Decrement reference count
    ref->ref_count -= 1;
    
    // If reference count is zero, free address.
    if (ref->ref_count == 0) {
      
      // Reference is string
      if (ref->type == SPVM_REF_C_TYPE_STRING) {
        SPVM_REF_STRING* ref_string = (SPVM_REF_STRING*)ref;
        
        SPVM_SV* sv = ref_string->sv;
        SPVM_SvREFCNT_dec(sv);
        SPVM_ALLOCATOR_RUNTIME_free_ref(spvm, spvm->allocator_runtime, (SPVM_REF*)ref_string);
      }
      // Reference is array
      else if (ref->type == SPVM_REF_C_TYPE_ARRAY) {
        SPVM_REF_ARRAY* ref_array = (SPVM_REF_ARRAY*)ref;
        if (ref_array->value_type == SPVM_REF_ARRAY_C_VALUE_TYPE_REF) {
          
          // Array length
          int32_t length = ref_array->length;
          
          for (int32_t i = 0; i < length; i++) {
            SPVM_REF* ref_element = *(SPVM_REF**)((intptr_t)ref_array + sizeof(SPVM_REF_ARRAY) + sizeof(void*) * i);
            SPVM_API_dec_ref_count(spvm, env, ref_element);
          }
        }
        SPVM_ALLOCATOR_RUNTIME_free_ref(spvm, spvm->allocator_runtime, ref);
      }
      // Reference is object
      else if (ref->type == SPVM_REF_C_TYPE_OBJECT) {
        SPVM_REF_OBJECT* ref_object = (SPVM_REF_OBJECT*)ref;
        
        int32_t package_constant_pool_address = ref_object->package_constant_pool_address;
        SPVM_CONSTANT_POOL_PACKAGE* constant_pool_package = (SPVM_CONSTANT_POOL_PACKAGE*)&spvm->constant_pool->values[package_constant_pool_address];
        
        int32_t ref_fields_count = constant_pool_package->ref_fields_count;
        
        for (int i = 0; i < ref_fields_count; i++) {
          SPVM_REF* ref_field = *(SPVM_REF**)((intptr_t)ref_object + sizeof(SPVM_REF_OBJECT) + sizeof(void*) * i);
          SPVM_API_dec_ref_count(spvm, env, ref_field);
        }
        
        SPVM_ALLOCATOR_RUNTIME_free_ref(spvm, spvm->allocator_runtime, (SPVM_REF*)ref_object);
      }
    }
  }
}

void SPVM_API_inc_ref_count(SPVM* spvm, SPVM_ENV* env, SPVM_REF* ref) {
  (void)spvm;
  (void)env;
  
  if (ref != NULL) {
    assert(ref->ref_count >= 0);
    // Increment reference count
    ref->ref_count += 1;
  }
}

void SPVM_API_push_return_value_byte(SPVM* spvm, SPVM_ENV* env, int8_t value) {
  (void)spvm;
  (void)env;
  
  env->operand_stack_top++;
  env->call_stack[env->operand_stack_top].byte_value = value;
}

void SPVM_API_push_return_value_short(SPVM* spvm, SPVM_ENV* env, int16_t value) {
  (void)spvm;
  (void)env;
  
  env->operand_stack_top++;
  env->call_stack[env->operand_stack_top].short_value = value;
}

void SPVM_API_push_return_value_int(SPVM* spvm, SPVM_ENV* env, int32_t value) {
  (void)spvm;
  (void)env;
  
  env->operand_stack_top++;
  env->call_stack[env->operand_stack_top].int_value = value;
}

void SPVM_API_push_return_value_long(SPVM* spvm, SPVM_ENV* env, int64_t value) {
  (void)spvm;
  (void)env;
  
  env->operand_stack_top++;
  env->call_stack[env->operand_stack_top].long_value = value;
}

void SPVM_API_push_return_value_float(SPVM* spvm, SPVM_ENV* env, float value) {
  (void)spvm;
  (void)env;
  
  env->operand_stack_top++;
  env->call_stack[env->operand_stack_top].float_value = value;
}

void SPVM_API_push_return_value_double(SPVM* spvm, SPVM_ENV* env, double value) {
  (void)spvm;
  (void)env;
  
  env->operand_stack_top++;
  env->call_stack[env->operand_stack_top].double_value = value;
}

void SPVM_API_push_ret(SPVM* spvm, SPVM_ENV* env, void* value) {
  (void)spvm;
  (void)env;
  
  env->operand_stack_top++;
  env->call_stack[env->operand_stack_top].address_value = value;
}

int8_t SPVM_API_pop_return_value_byte(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  int8_t ret = env->call_stack[env->operand_stack_top].byte_value;
  env->operand_stack_top--;
  return ret;
}

int16_t SPVM_API_pop_return_value_short(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  int16_t ret = env->call_stack[env->operand_stack_top].short_value;
  env->operand_stack_top--;
  return ret;
}

int32_t SPVM_API_pop_return_value_int(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  int32_t ret = env->call_stack[env->operand_stack_top].int_value;
  env->operand_stack_top--;
  return ret;
}

int64_t SPVM_API_pop_return_value_long(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;

  int64_t ret = env->call_stack[env->operand_stack_top].long_value;
  env->operand_stack_top--;
  return ret;
}

float SPVM_API_pop_return_value_float(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  float ret = env->call_stack[env->operand_stack_top].float_value;
  env->operand_stack_top--;
  return ret;
}

double SPVM_API_pop_return_value_double(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  double ret = env->call_stack[env->operand_stack_top].double_value;
  env->operand_stack_top--;
  return ret;
}

void* SPVM_API_pop_return_value_address(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  void* ret = env->call_stack[env->operand_stack_top].address_value;
  env->operand_stack_top--;
  return ret;
}

int8_t SPVM_API_get_var_byte(SPVM* spvm, SPVM_ENV* env, int32_t index) {
  (void)spvm;
  (void)env;
  
  return env->call_stack[env->call_stack_base + (size_t)index].byte_value;
}

int16_t SPVM_API_get_var_short(SPVM* spvm, SPVM_ENV* env, int32_t index) {
  (void)spvm;
  (void)env;
  
  return env->call_stack[env->call_stack_base + (size_t)index].short_value;
}

int32_t SPVM_API_get_var_int(SPVM* spvm, SPVM_ENV* env, int32_t index) {
  (void)spvm;
  (void)env;
  
  return env->call_stack[env->call_stack_base + (size_t)index].int_value;
}

int64_t SPVM_API_get_var_long(SPVM* spvm, SPVM_ENV* env, int32_t index) {
  (void)spvm;
  (void)env;
  
  return env->call_stack[env->call_stack_base + (size_t)index].long_value;
}

float SPVM_API_get_var_float(SPVM* spvm, SPVM_ENV* env, int32_t index) {
  (void)spvm;
  (void)env;
  
  return env->call_stack[env->call_stack_base + (size_t)index].float_value;
}

double SPVM_API_get_var_double(SPVM* spvm, SPVM_ENV* env, int32_t index) {
  (void)spvm;
  (void)env;
  
  return env->call_stack[env->call_stack_base + (size_t)index].double_value;
}

void* SPVM_API_get_var_address(SPVM* spvm, SPVM_ENV* env, int32_t index) {
  (void)spvm;
  (void)env;
  
  return env->call_stack[env->call_stack_base + (size_t)index].address_value;
}

void SPVM_API_push_var_byte(SPVM* spvm, SPVM_ENV* env, int8_t value) {
  (void)spvm;
  (void)env;
  
  env->operand_stack_top++;
  env->call_stack[env->operand_stack_top].byte_value = value;
}

void SPVM_API_push_var_short(SPVM* spvm, SPVM_ENV* env, int16_t value) {
  (void)spvm;
  (void)env;
  
  env->operand_stack_top++;
  env->call_stack[env->operand_stack_top].short_value = value;
}

void SPVM_API_push_var_int(SPVM* spvm, SPVM_ENV* env, int32_t value) {
  (void)spvm;
  (void)env;
  
  env->operand_stack_top++;
  env->call_stack[env->operand_stack_top].int_value = value;
}

void SPVM_API_push_var_long(SPVM* spvm, SPVM_ENV* env, int64_t value) {
  (void)spvm;
  (void)env;
  
  env->operand_stack_top++;
  env->call_stack[env->operand_stack_top].long_value = value;
}

void SPVM_API_push_var_float(SPVM* spvm, SPVM_ENV* env, float value) {
  (void)spvm;
  (void)env;
  
  env->operand_stack_top++;
  env->call_stack[env->operand_stack_top].float_value = value;
}

void SPVM_API_push_var_double(SPVM* spvm, SPVM_ENV* env, double value) {
  (void)spvm;
  (void)env;
  
  env->operand_stack_top++;
  env->call_stack[env->operand_stack_top].double_value = value;
}

void SPVM_API_push_var_address(SPVM* spvm, SPVM_ENV* env, void* value) {
  (void)spvm;
  (void)env;
  
  env->operand_stack_top++;
  env->call_stack[env->operand_stack_top].address_value = value;
}

int32_t SPVM_API_get_array_length(SPVM* spvm, SPVM_ENV* env, SPVM_REF_ARRAY* array) {
  (void)spvm;
  (void)env;
  
  return array->length;
}

int32_t SPVM_API_get_ref_count(SPVM* spvm, SPVM_ENV* env, SPVM_REF* data) {
  (void)spvm;
  (void)env;
  
  return data->ref_count;
}

SPVM_SV* SPVM_API_get_string_sv(SPVM* spvm, SPVM_ENV* env, SPVM_REF_STRING* string) {
  (void)spvm;
  (void)env;
  
  return string->sv;
}

char* SPVM_API_get_string_value(SPVM* spvm, SPVM_ENV* env, SPVM_REF_STRING* ref_string) {
  (void)spvm;
  (void)env;
  
  SPVM_SV* sv = SPVM_API_get_string_sv(spvm, env, ref_string);
  assert(sv);
  char* value = SPVM_COMPAT_SVpv(sv);
  
  return value;
}

int8_t* SPVM_API_get_array_byte_values(SPVM* spvm, SPVM_ENV* env, void* address) {
  (void)spvm;
  (void)env;
  
  return (int8_t*)((intptr_t)address + sizeof(SPVM_REF_ARRAY));
}

int16_t* SPVM_API_get_array_short_values(SPVM* spvm, SPVM_ENV* env, void* address) {
  (void)spvm;
  (void)env;
  
  return (int16_t*)((intptr_t)address + sizeof(SPVM_REF_ARRAY));
}

int32_t* SPVM_API_get_array_int_values(SPVM* spvm, SPVM_ENV* env, void* address) {
  (void)spvm;
  (void)env;
  
  return (int32_t*)((intptr_t)address + sizeof(SPVM_REF_ARRAY));
}

int64_t* SPVM_API_get_array_long_values(SPVM* spvm, SPVM_ENV* env, void* address) {
  (void)spvm;
  (void)env;
  
  return (int64_t*)((intptr_t)address + sizeof(SPVM_REF_ARRAY));
}

float* SPVM_API_get_array_float_values(SPVM* spvm, SPVM_ENV* env, void* address) {
  (void)spvm;
  (void)env;
  
  return (float*)((intptr_t)address + sizeof(SPVM_REF_ARRAY));
}

double* SPVM_API_get_array_double_values(SPVM* spvm, SPVM_ENV* env, void* address) {
  (void)spvm;
  (void)env;
  
  return (double*)((intptr_t)address + sizeof(SPVM_REF_ARRAY));
}

void* SPVM_API_create_string_sv(SPVM* spvm, SPVM_ENV* env, SPVM_SV* sv) {
  (void)spvm;
  (void)env;
  
  SPVM_ALLOCATOR_RUNTIME* allocator = spvm->allocator_runtime;
  
  // Allocate array
  int32_t ref_string_byte_size = sizeof(SPVM_REF_STRING);
  SPVM_REF_STRING* ref_string = SPVM_ALLOCATOR_RUNTIME_malloc(spvm, allocator, ref_string_byte_size);
  
  // Set type
  ref_string->type = SPVM_REF_C_TYPE_STRING;
  
  // Set reference count
  ref_string->ref_count = 0;
  
  // Set sv
  ref_string->sv = sv;

  assert(ref_string_byte_size == SPVM_REF_calcurate_byte_size(spvm, (SPVM_REF*)ref_string));
  
  return ref_string;
}

SPVM_REF_STRING* SPVM_API_create_ref_string_from_pv(SPVM* spvm, SPVM_ENV* env, const char* pv) {
  (void)spvm;
  (void)env;
  
  // New sv
  SPVM_SV* sv = SPVM_COMPAT_newSVpvn(spvm, pv, strlen(pv));
  
  SPVM_ALLOCATOR_RUNTIME* allocator = spvm->allocator_runtime;
  
  // Allocate array
  int32_t ref_string_byte_size = sizeof(SPVM_REF_STRING);
  SPVM_REF_STRING* ref_string = SPVM_ALLOCATOR_RUNTIME_malloc(spvm, allocator, ref_string_byte_size);
  
  // Fatal memory allocation error
  if (!ref_string) {
    fprintf(stderr, "Failed to allocate memory(create_ref_string_from_pv)");
    abort();
  }
  
  // Set type
  ref_string->type = SPVM_REF_C_TYPE_STRING;
  
  // Set reference count
  ref_string->ref_count = 0;
  
  // Set sv
  ref_string->sv = sv;

  assert(ref_string_byte_size == SPVM_REF_calcurate_byte_size(spvm, (SPVM_REF*)ref_string));
  
  return ref_string;
}
