#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_runtime_allocator.h"
#include "spvm_bytecode.h"
#include "spvm_constant_pool_sub.h"
#include "spvm_constant_pool_package.h"
#include "spvm_constant_pool_field.h"
#include "spvm_data_api.h"
#include "spvm_util_allocator.h"

SPVM_RUNTIME* SPVM_RUNTIME_new() {
  
  assert(sizeof(SPVM_DATA_ARRAY) <= SPVM_DATA_C_HEADER_BYTE_SIZE);
  assert(sizeof(SPVM_DATA_OBJECT) <= SPVM_DATA_C_HEADER_BYTE_SIZE);
  
  SPVM_RUNTIME* runtime = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(1, sizeof(SPVM_RUNTIME));
  
  // Runtime memory allocator
  runtime->allocator = SPVM_RUNTIME_ALLOCATOR_new(runtime);
  
  runtime->call_stack_capacity = 0xFF;
  runtime->call_stack = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(runtime->call_stack_capacity, sizeof(SPVM_VALUE));
  
  SPVM_RUNTIME_init(runtime);
  
  return runtime;
}

void SPVM_RUNTIME_init(SPVM_RUNTIME* runtime) {
  
  runtime->call_stack_base = -1;
  runtime->operand_stack_top = -1;
  runtime->abort = 0;
}

void SPVM_RUNTIME_call_sub(SPVM_RUNTIME* runtime, int32_t sub_constant_pool_address) {
  (void)runtime;
  
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
    &&case_SPVM_BYTECODE_C_CODE_LOAD_CONSTANT2,
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
  int32_t* constant_pool = runtime->constant_pool;
  
  // Bytecode
  uint8_t* bytecodes = runtime->bytecodes;
  
  // Variables
  SPVM_VALUE* vars = &runtime->call_stack[runtime->call_stack_base];
  
  SPVM_VALUE* call_stack = runtime->call_stack;
  
  // Program counter
  register uint8_t* pc = NULL;
  
  // Top position of operand stack
  register int32_t operand_stack_top = runtime->operand_stack_top;
  
  register int32_t success;
  
  int32_t call_stack_base = runtime->call_stack_base;
  int32_t call_stack_base_start = call_stack_base;

  SPVM_RUNTIME_ALLOCATOR* allocator = runtime->allocator;
  
  // Offten used variables
  int32_t index;
  SPVM_DATA_ARRAY* data_array;
  SPVM_DATA_ARRAY* data_string_error;
  SPVM_DATA_OBJECT* data_object;
  SPVM_CONSTANT_POOL_SUB constant_pool_sub;
  
  // Goto subroutine
  goto CALLSUB_COMMON;
  
  case_SPVM_BYTECODE_C_CODE_CALL_SUB: {
    // Get subroutine ID
    sub_constant_pool_address
      = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
    
    CALLSUB_COMMON: {
      memcpy(&constant_pool_sub, &constant_pool[sub_constant_pool_address], sizeof(SPVM_CONSTANT_POOL_SUB));

      // Extend call stack(current size + 2(return address + call stack base before) + lexical variable area + operand_stack area)
      int32_t call_stack_max = operand_stack_top + 2 + constant_pool_sub.my_vars_length + constant_pool_sub.operand_stack_max;
      
      while (call_stack_max > runtime->call_stack_capacity) {
        runtime->call_stack_capacity = runtime->call_stack_capacity * 2;
        runtime->call_stack = call_stack = realloc(call_stack, sizeof(SPVM_VALUE) * runtime->call_stack_capacity);
      }

      operand_stack_top -= constant_pool_sub.args_length;

      // Prepare arguments
      memmove(&call_stack[operand_stack_top + 4], &call_stack[operand_stack_top + 1], constant_pool_sub.args_length * sizeof(SPVM_VALUE));

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
      memset(&call_stack[call_stack_base + constant_pool_sub.args_length], 0, (constant_pool_sub.my_vars_length - constant_pool_sub.args_length) * sizeof(SPVM_VALUE));
      
      // Set variables to local variable
      vars = &call_stack[call_stack_base];
      
      // Set operant stack top
      operand_stack_top = call_stack_base + constant_pool_sub.my_vars_length - 1;
      
      // Call native sub
      if (constant_pool_sub.is_native) {
        // Set runtimeironment
        runtime->operand_stack_top = operand_stack_top;
        runtime->call_stack_base = call_stack_base;
        
        // Call native sub
        void (*native_address)(SPVM_RUNTIME* runtime) = constant_pool_sub.native_address;
        (*native_address)(runtime);
        
        // Get runtimeiromnet
        operand_stack_top = runtime->operand_stack_top;
        call_stack_base = runtime->call_stack_base;
        
        if (runtime->abort) {
          goto case_SPVM_BYTECODE_C_CODE_DIE;
        }
        else {
          if (constant_pool_sub.has_return_value) {
            goto case_SPVM_BYTECODE_C_CODE_RETURN;
          }
          else {
            goto case_SPVM_BYTECODE_C_CODE_RETURN_VOID;
          }
        }
      }
      // Call normal sub
      else {
        pc = &bytecodes[constant_pool_sub.bytecode_base];
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
      runtime->call_stack_base = call_stack_base;
      runtime->operand_stack_top = operand_stack_top;
      runtime->abort = 0;
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
      runtime->call_stack_base = call_stack_base;
      runtime->operand_stack_top = operand_stack_top;
      runtime->abort = 0;
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
    memcpy(&constant_pool_sub, &constant_pool[sub_constant_pool_address], sizeof(SPVM_CONSTANT_POOL_SUB));
    
    // Sub name
    int32_t sub_name_constant_pool_address = constant_pool_sub.abs_name_constant_pool_address;
    const char* sub_name = (char*)&constant_pool[sub_name_constant_pool_address + 1];
    
    // File name
    int32_t file_name_constant_pool_address = constant_pool_sub.file_name_constant_pool_address;
    const char* file_name = (char*)&constant_pool[file_name_constant_pool_address + 1];
    
    // stack trace strings
    const char* exception = "Exception";
    const char* from = "\n  from ";
    const char* at = " at ";
    
    // Total string length
    int32_t total_length = 0;
    if (return_value == NULL) {
      total_length = strlen(exception);
    }
    else {
      total_length += SPVM_DATA_API_get_array_length(return_value);
    }
    total_length += strlen(from);
    total_length += strlen(sub_name);
    total_length += strlen(at);
    total_length += strlen(file_name);
    
    // Create exception message
    SPVM_DATA_ARRAY* new_data_array_message =  SPVM_RUNTIME_API_create_data_array_byte(runtime, total_length);
    if (return_value == NULL) {
      sprintf(
        (char*)((intptr_t)new_data_array_message + SPVM_DATA_C_HEADER_BYTE_SIZE),
        "%s%s%s%s%s",
        exception,
        from,
        sub_name,
        at,
        file_name
      );
    }
    else {
      memcpy(
        (void*)((intptr_t)new_data_array_message + SPVM_DATA_C_HEADER_BYTE_SIZE),
        (void*)((intptr_t)return_value + SPVM_DATA_C_HEADER_BYTE_SIZE),
        SPVM_DATA_API_get_array_length(return_value)
      );
      sprintf(
        (char*)((intptr_t)new_data_array_message + SPVM_DATA_C_HEADER_BYTE_SIZE + SPVM_DATA_API_get_array_length(return_value)),
        "%s%s%s%s",
        from,
        sub_name,
        at,
        file_name
      );
    }
    
    // Free original string if need
    if (return_value != NULL) {
      int32_t ref_count = SPVM_DATA_API_get_ref_count(return_value);
      if (ref_count == 0) {
        SPVM_RUNTIME_ALLOCATOR_free_data(runtime, runtime->allocator, return_value);
      }
    }
    
    // Resotre vars base
    call_stack_base = call_stack[call_stack_base - 1].int_value;
    
    // Push return value
    operand_stack_top++;
    call_stack[operand_stack_top].address_value = new_data_array_message;
    
    // Finish call sub with exception
    if (call_stack_base == call_stack_base_start) {
      runtime->call_stack_base = call_stack_base;
      runtime->operand_stack_top = operand_stack_top;
      runtime->abort = 1;
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
    memcpy(&call_stack[operand_stack_top], &constant_pool[(*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4)], sizeof(int32_t));
    pc += 5;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_LOAD_CONSTANT2:
    operand_stack_top++;
    memcpy(&call_stack[operand_stack_top], &constant_pool[(*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4)], sizeof(int64_t));
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
    data_array = (SPVM_DATA_ARRAY*)call_stack[operand_stack_top - 1].address_value;
    index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!data_array, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The array of byte to get the element must not be undef");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= data_array->length, 0)) {
        data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The index of the array of byte to get the element is out of range");
        operand_stack_top++;
        call_stack[operand_stack_top].address_value = data_string_error;
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].byte_value
          = *(int8_t*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(int8_t) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_SHORT:
    data_array = (SPVM_DATA_ARRAY*)call_stack[operand_stack_top - 1].address_value;
    index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!data_array, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The array of short to get the element must not be undef");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= data_array->length, 0)) {
        data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The index of the array of short to get the element is out of range");
        operand_stack_top++;
        call_stack[operand_stack_top].address_value = data_string_error;
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].short_value
          = *(int16_t*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(int16_t) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_INT:
    data_array = (SPVM_DATA_ARRAY*)call_stack[operand_stack_top - 1].address_value;
    index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!data_array, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The array of int to get the element must not be undef");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= data_array->length, 0)) {
        data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The index of the array of int to get the element is out of range");
        operand_stack_top++;
        call_stack[operand_stack_top].address_value = data_string_error;
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].int_value = *(int32_t*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(int32_t) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_LONG:
    data_array = (SPVM_DATA_ARRAY*)call_stack[operand_stack_top - 1].address_value;
    index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!data_array, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The array of long to get the element must not be undef");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= data_array->length, 0)) {
        data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The index of the array of long to get the element is out of range");
        operand_stack_top++;
        call_stack[operand_stack_top].address_value = data_string_error;
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].long_value = *(int64_t*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(int64_t) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_FLOAT:
    data_array = (SPVM_DATA_ARRAY*)call_stack[operand_stack_top - 1].address_value;
    index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!data_array, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The array of float to get the element must not be undef");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= data_array->length, 0)) {
        data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The index of the array of float to get the element is out of range");
        operand_stack_top++;
        call_stack[operand_stack_top].address_value = data_string_error;
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].float_value = *(float*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(float) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_DOUBLE:
    data_array = (SPVM_DATA_ARRAY*)call_stack[operand_stack_top - 1].address_value;
    index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!data_array, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The array of double to get the element must not be undef");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= data_array->length, 0)) {
        data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The index of the array of double to get the element is out of range");
        operand_stack_top++;
        call_stack[operand_stack_top].address_value = data_string_error;
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].double_value = *(double*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(double) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_ADDRESS:
    data_array = (SPVM_DATA_ARRAY*)call_stack[operand_stack_top - 1].address_value;
    index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!data_array, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The array of reference to get the element must not be undef");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= data_array->length, 0)) {
        data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The index of the array of reference to get the element is out of range");
        operand_stack_top++;
        call_stack[operand_stack_top].address_value = data_string_error;
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].address_value = *(void**)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(void*) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_BYTE:
    data_array = (SPVM_DATA_ARRAY*)call_stack[operand_stack_top - 2].address_value;
    index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!data_array, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The array of byte to set the element must not be undef");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= data_array->length, 0)) {
        data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The index of the array of byte to set the element is out of range");
        operand_stack_top++;
        call_stack[operand_stack_top].address_value = data_string_error;
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        *(int8_t*)((intptr_t)call_stack[operand_stack_top - 2].address_value + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(int8_t) * call_stack[operand_stack_top - 1].int_value)
          = call_stack[operand_stack_top].byte_value;
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_SHORT:
    data_array = (SPVM_DATA_ARRAY*)call_stack[operand_stack_top - 2].address_value;
    index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!data_array, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The array of short to set the element must not be undef");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= data_array->length, 0)) {
        data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The index of the array of short to set the element is out of range");
        operand_stack_top++;
        call_stack[operand_stack_top].address_value = data_string_error;
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        *(int16_t*)((intptr_t)call_stack[operand_stack_top - 2].address_value + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(int16_t) * call_stack[operand_stack_top - 1].int_value)
          = call_stack[operand_stack_top].short_value;
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_INT:
    data_array = (SPVM_DATA_ARRAY*)call_stack[operand_stack_top - 2].address_value;
    index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!data_array, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The array of int to set the element must not be undef");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= data_array->length, 0)) {
        data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The index of the array of int to set the element is out of range");
        operand_stack_top++;
        call_stack[operand_stack_top].address_value = data_string_error;
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        *(int32_t*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(int32_t) * index) = call_stack[operand_stack_top].int_value;
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_LONG:
    data_array = (SPVM_DATA_ARRAY*)call_stack[operand_stack_top - 2].address_value;
    index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!data_array, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The array of long to set the element must not be undef");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= data_array->length, 0)) {
        data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The index of the array of int to set the element is out of range");
        operand_stack_top++;
        call_stack[operand_stack_top].address_value = data_string_error;
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        *(int64_t*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(int64_t) * index) = call_stack[operand_stack_top].long_value;
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_FLOAT:
    data_array = (SPVM_DATA_ARRAY*)call_stack[operand_stack_top - 2].address_value;
    index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!data_array, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The array of float to set the element must not be undef");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= data_array->length, 0)) {
        data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The index of the array of float to set the element is out of range");
        operand_stack_top++;
        call_stack[operand_stack_top].address_value = data_string_error;
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        *(float*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(float) * index) = call_stack[operand_stack_top - 1].float_value;
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_DOUBLE:
    data_array = (SPVM_DATA_ARRAY*)call_stack[operand_stack_top - 2].address_value;
    index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!data_array, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The array of double to set the element must not be undef");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= data_array->length, 0)) {
        data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The index of the array of double to set the element is out of range");
        operand_stack_top++;
        call_stack[operand_stack_top].address_value = data_string_error;
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        *(double*)((intptr_t)call_stack[operand_stack_top - 2].address_value + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(double) * call_stack[operand_stack_top - 1].int_value)
          = call_stack[operand_stack_top].double_value;
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_ADDRESS: {
    data_array = (SPVM_DATA_ARRAY*)call_stack[operand_stack_top - 2].address_value;
    index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!data_array, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The array of reference to set the element must not be undef");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= data_array->length, 0)) {
        data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The index of the array of reference to set the element is out of range");
        operand_stack_top++;
        call_stack[operand_stack_top].address_value = data_string_error;
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        SPVM_DATA** data_address = (SPVM_DATA**)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(void*) * index);
        
        // Increment reference count
        SPVM_RUNTIME_API_inc_ref_count(runtime, call_stack[operand_stack_top].address_value);
        
        // Decrement reference count
        SPVM_RUNTIME_API_dec_ref_count(runtime, *data_address);
        
        // Store address
        *data_address = call_stack[operand_stack_top].address_value;
        
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
    SPVM_RUNTIME_API_inc_ref_count(runtime, call_stack[operand_stack_top].address_value);
    
    // Decrement reference count
    SPVM_RUNTIME_API_dec_ref_count(runtime, vars[vars_index].address_value);
    
    // Store address
    vars[vars_index] = call_stack[operand_stack_top];
    
    operand_stack_top--;
    pc += 2;
    goto *jump[*pc];
  }
  case_SPVM_BYTECODE_C_CODE_DEC_REF_COUNT: {
    void* address = call_stack[operand_stack_top].address_value;
    
    // Decrement reference count
    SPVM_RUNTIME_API_dec_ref_count(runtime, address);
    
    pc += 1;
    goto *jump[*pc];
  }
  case_SPVM_BYTECODE_C_CODE_INC_REF_COUNT: {
    void* address = call_stack[operand_stack_top].address_value;
    
    // Increment reference count
    SPVM_RUNTIME_API_inc_ref_count(runtime, address);
    
    pc += 1;
    goto *jump[*pc];
  }
  case_SPVM_BYTECODE_C_CODE_POP:
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_POP_ADDRESS: {
    
    SPVM_DATA* data = call_stack[operand_stack_top].address_value;
    
    // Free object
    if (data != NULL) {
      int32_t ref_count = data->ref_count;
      if (ref_count == 0) {
        SPVM_RUNTIME_ALLOCATOR_free_data(runtime, runtime->allocator, call_stack[operand_stack_top].address_value);
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
    SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
    memcpy(&constant_pool_package, &constant_pool[package_constant_pool_address], sizeof(SPVM_CONSTANT_POOL_PACKAGE));
    
    // Allocate memory
    int32_t fields_length = constant_pool_package.fields_length;
    int32_t data_object_byte_size = SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(SPVM_VALUE) * fields_length;
    SPVM_DATA_OBJECT* data_object = SPVM_RUNTIME_ALLOCATOR_malloc(runtime, allocator, data_object_byte_size);
    
    // Memory allocation error
    if (!data_object) {
      // Sub name
      int32_t sub_name_constant_pool_address = constant_pool_sub.abs_name_constant_pool_address;
      const char* sub_name = (char*)&constant_pool[sub_name_constant_pool_address + 1];
      
      // File name
      int32_t file_name_constant_pool_address = constant_pool_sub.file_name_constant_pool_address;
      const char* file_name = (char*)&constant_pool[file_name_constant_pool_address + 1];
      
      fprintf(stderr, "Failed to allocate memory(malloc PACKAGE) from %s at %s\n", sub_name, file_name);
      abort();
    }
    
    // Set constant pool
    data_object->constant_pool = runtime->constant_pool;
    
    // Set type
    data_object->type = SPVM_DATA_C_TYPE_OBJECT;
    
    // Set reference count
    data_object->ref_count = 0;
    
    // Initialize reference fields by 0
    memset((void*)((intptr_t)data_object + SPVM_DATA_C_HEADER_BYTE_SIZE), 0, sizeof(void*) * constant_pool_package.ref_fields_length);
    
    // Package constant pool address
    data_object->package_constant_pool_address = package_constant_pool_address;
    
    data_object->constant_pool = runtime->constant_pool;
    
    data_object->field_name_indexes_constant_pool_address = constant_pool_package.field_name_indexes_constant_pool_address;
    
    assert(data_object_byte_size == SPVM_RUNTIME_API_calcurate_data_byte_size(runtime, (SPVM_DATA*)data_object));
    
    // Push object
    operand_stack_top++;
    call_stack[operand_stack_top].address_value = data_object;
    
    pc += 5;
    goto *jump[*pc];
  }
  case_SPVM_BYTECODE_C_CODE_MALLOC_ARRAY: {
    int32_t value_type = *(pc + 1);
    
    int32_t size = SPVM_DATA_ARRAY_C_VALUE_SIZES[value_type];
    
    // Array length
    int32_t length = call_stack[operand_stack_top].int_value;
    
    // Allocate array
    int32_t data_array_byte_size = SPVM_DATA_C_HEADER_BYTE_SIZE + size * length;
    SPVM_DATA_ARRAY* data_array = SPVM_RUNTIME_ALLOCATOR_malloc(runtime, allocator, data_array_byte_size);
    
    // Memory allocation error
    if (!data_array) {
      // Error message
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "Failed to allocate memory(MALLOC_ARRAY)");
      
      // Error is converted to exception
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    
    // Init null if sub type is array of reference
    if (value_type == SPVM_DATA_ARRAY_C_VALUE_TYPE_REF) {
      memset((void*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE), 0, size * length);
    }
    
    // Set type
    data_array->type = SPVM_DATA_C_TYPE_ARRAY;
    
    // Set sub type
    data_array->value_type = value_type;
    
    // Set reference count
    data_array->ref_count = 0;
    
    // Set array length
    data_array->length = length;

    assert(data_array_byte_size == SPVM_RUNTIME_API_calcurate_data_byte_size(runtime, (SPVM_DATA*)data_array));
    
    // Set array
    call_stack[operand_stack_top].address_value = data_array;
    
    pc += 2;
    goto *jump[*pc];
  }
  case_SPVM_BYTECODE_C_CODE_MALLOC_STRING: {
    int32_t* string_constant_pool_addresss
      = &constant_pool[(*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4)];
    
    char* pv = (char*)&string_constant_pool_addresss[1];
    SPVM_DATA_ARRAY* data_array = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, pv);

    // Memory allocation error
    if (!data_array) {
      // Sub name
      int32_t sub_name_constant_pool_address = constant_pool_sub.abs_name_constant_pool_address;
      const char* sub_name = (char*)&constant_pool[sub_name_constant_pool_address + 1];
      
      // File name
      int32_t file_name_constant_pool_address = constant_pool_sub.file_name_constant_pool_address;
      const char* file_name = (char*)&constant_pool[file_name_constant_pool_address + 1];
      
      fprintf(stderr, "Failed to allocate memory(malloc STRING) from %s at %s\n", sub_name, file_name);
      abort();
    }
    
    // Set string
    operand_stack_top++;
    call_stack[operand_stack_top].address_value = data_array;
    
    pc += 5;
    goto *jump[*pc];
  }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LENGTH:
    call_stack[operand_stack_top].int_value = (int32_t)((SPVM_DATA_ARRAY*)call_stack[operand_stack_top].address_value)->length;
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
      SPVM_RUNTIME_API_inc_ref_count(runtime, call_stack[operand_stack_top].address_value);
      
      // Decrement reference count if original object is not null
      SPVM_RUNTIME_API_dec_ref_count(runtime, vars[var_index].address_value);
      
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
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_BYTE:
    data_object = (SPVM_DATA_OBJECT*)call_stack[operand_stack_top - 1].address_value;
    if (__builtin_expect(!data_object, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The object to get an byte field must not be undefined.");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top].byte_value
        = *(int8_t*)((intptr_t)data_object + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(SPVM_VALUE) * index);
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_SHORT:
    data_object = (SPVM_DATA_OBJECT*)call_stack[operand_stack_top].address_value;
    if (__builtin_expect(!data_object, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The object to get an short field must not be undefined.");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top].short_value
        = *(int16_t*)((intptr_t)data_object + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(SPVM_VALUE) * index);
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_INT:
    data_object = (SPVM_DATA_OBJECT*)call_stack[operand_stack_top].address_value;
    if (__builtin_expect(!data_object, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The object to get an int field must not be undefined.");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top].int_value
        = *(int32_t*)((intptr_t)data_object + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(SPVM_VALUE) * index);
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_LONG:
    data_object = (SPVM_DATA_OBJECT*)call_stack[operand_stack_top].address_value;
    if (__builtin_expect(!data_object, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The object to get an long field must not be undefined.");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top].long_value
        = *(int64_t*)((intptr_t)data_object + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(SPVM_VALUE) * index);
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_FLOAT:
    data_object = (SPVM_DATA_OBJECT*)call_stack[operand_stack_top].address_value;
    if (__builtin_expect(!data_object, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The object to get an float field must not be undefined.");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top - 1].float_value
        = *(float*)((intptr_t)data_object + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(SPVM_VALUE) * index);
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_DOUBLE:
    data_object = (SPVM_DATA_OBJECT*)call_stack[operand_stack_top].address_value;
    if (__builtin_expect(!data_object, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The object to get an double field must not be undefined.");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top].double_value
        = *(double*)((intptr_t)data_object + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(SPVM_VALUE) * index);
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_ADDRESS:
    data_object = (SPVM_DATA_OBJECT*)call_stack[operand_stack_top].address_value;
    if (__builtin_expect(!data_object, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The object to get an reference field must not be undefined.");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top].address_value
        = *(void**)((intptr_t)call_stack[operand_stack_top].address_value + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(SPVM_VALUE) * index);
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_BYTE:
    data_object = (SPVM_DATA_OBJECT*)call_stack[operand_stack_top - 1].address_value;
    if (__builtin_expect(!data_object, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The object to set an byte field must not be undefined.");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      *(int8_t*)((intptr_t)data_object + sizeof(SPVM_VALUE) * index)
        = call_stack[operand_stack_top].byte_value;
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_SHORT:
    data_object = (SPVM_DATA_OBJECT*)call_stack[operand_stack_top - 1].address_value;
    if (__builtin_expect(!data_object, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The object to set an short field must not be undefined.");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      *(int16_t*)((intptr_t)data_object + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(SPVM_VALUE) * index)
        = call_stack[operand_stack_top].short_value;
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_INT:
    data_object = (SPVM_DATA_OBJECT*)call_stack[operand_stack_top - 1].address_value;
    if (__builtin_expect(!data_object, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The object to set an int field must not be undefined.");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      *(int32_t*)((intptr_t)data_object + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(SPVM_VALUE) * index)
        = call_stack[operand_stack_top].int_value;
      
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_LONG:
    data_object = (SPVM_DATA_OBJECT*)call_stack[operand_stack_top - 1].address_value;
    if (__builtin_expect(!data_object, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The object to set an long field must not be undefined.");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      *(int64_t*)((intptr_t)data_object + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(SPVM_VALUE) * index)
        = call_stack[operand_stack_top].long_value;
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_FLOAT:
    data_object = (SPVM_DATA_OBJECT*)call_stack[operand_stack_top - 1].address_value;
    if (__builtin_expect(!data_object, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The object to set an float field must not be undefined.");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      *(float*)((intptr_t)data_object + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(SPVM_VALUE) * index)
        = call_stack[operand_stack_top - 1].float_value;
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_DOUBLE: 
    data_object = (SPVM_DATA_OBJECT*)call_stack[operand_stack_top - 1].address_value;
    if (__builtin_expect(!data_object, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The object to set an double field must not be undefined.");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      *(double*)((intptr_t)data_object + SPVM_DATA_C_HEADER_BYTE_SIZE + sizeof(SPVM_VALUE) * index)
        = call_stack[operand_stack_top].double_value;
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_ADDRESS: {
    data_object = (SPVM_DATA_OBJECT*)call_stack[operand_stack_top - 1].address_value;
    if (__builtin_expect(!data_object, 0)) {
      data_string_error = SPVM_RUNTIME_API_create_data_array_byte_from_pv(runtime, "The object to set an reference field must not be undefined.");
      operand_stack_top++;
      call_stack[operand_stack_top].address_value = data_string_error;
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      index = (*(pc + 1) << 8) + *(pc + 2);
      SPVM_DATA** data_address = (SPVM_DATA**)((intptr_t)data_object + sizeof(SPVM_VALUE) * index);

      // Increment reference count
      SPVM_RUNTIME_API_inc_ref_count(runtime, call_stack[operand_stack_top].address_value);
      
      // Decrement reference count
      SPVM_RUNTIME_API_dec_ref_count(runtime, *data_address);
      
      // Store object
      *data_address = call_stack[operand_stack_top].address_value;
      
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  }
}

void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime) {
  
  // Free call stack
  free(runtime->call_stack);
  
  // Free runtime allocator
  SPVM_RUNTIME_ALLOCATOR_free(runtime, runtime->allocator);

  free(runtime);
}
