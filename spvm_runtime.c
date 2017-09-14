#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_runtime_allocator.h"
#include "spvm_bytecode.h"
#include "spvm_constant_pool_sub.h"
#include "spvm_constant_pool_field_info.h"
#include "spvm_constant_pool_package.h"
#include "spvm_constant_pool_type.h"
#include "spvm_object.h"
#include "spvm_util_allocator.h"
#include "spvm_value.h"
#include "spvm_api.h"
#include "spvm_type.h"
#include "spvm_hash.h"
#include "spvm_dynamic_array.h"






static const void* SPVM_NATIVE_INTERFACE[]  = {
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
  SPVM_RUNTIME_API_get_byte_field,
  SPVM_RUNTIME_API_get_short_field,
  SPVM_RUNTIME_API_get_int_field,
  SPVM_RUNTIME_API_get_long_field,
  SPVM_RUNTIME_API_get_float_field,
  SPVM_RUNTIME_API_get_double_field,
  SPVM_RUNTIME_API_get_object_field,
  SPVM_RUNTIME_API_set_byte_field,
  SPVM_RUNTIME_API_set_short_field,
  SPVM_RUNTIME_API_set_int_field,
  SPVM_RUNTIME_API_set_long_field,
  SPVM_RUNTIME_API_set_float_field,
  SPVM_RUNTIME_API_set_double_field,
  SPVM_RUNTIME_API_set_object_field,
  SPVM_RUNTIME_API_get_sub_id,
  SPVM_RUNTIME_API_call_void_sub,
  SPVM_RUNTIME_API_call_byte_sub,
  SPVM_RUNTIME_API_call_short_sub,
  SPVM_RUNTIME_API_call_int_sub,
  SPVM_RUNTIME_API_call_long_sub,
  SPVM_RUNTIME_API_call_float_sub,
  SPVM_RUNTIME_API_call_double_sub,
  SPVM_RUNTIME_API_call_object_sub,
  SPVM_RUNTIME_API_get_type_id,
  SPVM_RUNTIME_API_new_object,
  SPVM_RUNTIME_API_new_byte_array,
  SPVM_RUNTIME_API_new_short_array,
  SPVM_RUNTIME_API_new_int_array,
  SPVM_RUNTIME_API_new_long_array,
  SPVM_RUNTIME_API_new_float_array,
  SPVM_RUNTIME_API_new_double_array,
  SPVM_RUNTIME_API_new_object_array,
  SPVM_RUNTIME_API_get_exception,
  SPVM_RUNTIME_API_set_exception,
  SPVM_RUNTIME_API_get_ref_count,
  SPVM_RUNTIME_API_inc_ref_count,
  SPVM_RUNTIME_API_dec_ref_count,
  SPVM_RUNTIME_API_inc_dec_ref_count,
  SPVM_RUNTIME_API_get_objects_count,
  SPVM_RUNTIME_API_get_runtime,
  SPVM_RUNTIME_API_new_string,
};

SPVM_RUNTIME* SPVM_RUNTIME_new() {
  
  SPVM_RUNTIME* runtime = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME));
  
  // Runtime memory allocator
  runtime->allocator = SPVM_RUNTIME_ALLOCATOR_new(runtime);
  
  SPVM_API* api = (SPVM_API*)SPVM_NATIVE_INTERFACE;
  
  runtime->api = api;
  
  // Constant pool subroutine symbol table
  runtime->sub_id_symtable = SPVM_HASH_new(0);
  
  // Constant pool type symbol table
  runtime->type_id_symtable = SPVM_HASH_new(0);
  
  // Constant pool type symbol table
  runtime->field_id_symtable = SPVM_HASH_new(0);
  
  // Constant pool type symbol table
  runtime->field_info_id_symtable = SPVM_HASH_new(0);
  
  // Constant pool type symbol table
  runtime->use_package_path_id_symtable = SPVM_HASH_new(0);
  
  runtime->native_sub_name_ids_symtable = SPVM_HASH_new(0);
  
  return runtime;
}

SPVM_VALUE SPVM_RUNTIME_call_sub(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args) {
  (void)api;
  
  // Runtime
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  _Bool debug = runtime->debug ? 1 : 0;
  
  // Constant pool
  int32_t* constant_pool = runtime->constant_pool;
  
  // Program counter
  register uint8_t* pc = NULL;
  
  // Constant pool subroutine
  SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&constant_pool[sub_id];
  
  // Args length
  int32_t args_length = constant_pool_sub->args_length;
  
  // Lexical varialbe length
  int32_t my_vars_length = constant_pool_sub->my_vars_length;
  register int32_t operand_stack_top = -1 + my_vars_length;
  
  // Call_stack_max
  int32_t call_stack_length = my_vars_length + constant_pool_sub->operand_stack_max;
  
  // Call stack
  SPVM_OBJECT* call_stack_array = SPVM_RUNTIME_API_new_value_array(api, call_stack_length);
  call_stack_array->ref_count++;
  SPVM_VALUE* call_stack = SPVM_RUNTIME_API_get_value_array_elements(api, call_stack_array);

  register int32_t success;
  int32_t current_line = 0;

  // Copy arguments
  memcpy(call_stack, args, args_length * sizeof(SPVM_VALUE));
  
  // If arg is object, increment reference count
  if (constant_pool_sub->object_args_length) {
    int32_t object_args_base = constant_pool_sub->object_args_base;
    int32_t object_args_length = constant_pool_sub->object_args_length;
    {
      int32_t i;
      for (i = 0; i < object_args_length; i++) {
        int32_t arg_index = constant_pool[object_args_base + i];
        SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[arg_index].object_value;
        if (object != NULL) {
          object->ref_count++;
        }
      }
    }
  }
  
  // Set exception to undef at top of call_sub
  SPVM_RUNTIME_API_set_exception(api, NULL);
  
  // Call native sub
  if (constant_pool_sub->is_native) {
    // Set runtimeironment
    SPVM_CONSTANT_POOL_TYPE* constant_pool_sub_return_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[constant_pool_sub->return_type_id];

    
    // Call native subroutine
    switch (constant_pool_sub_return_type->code) {
      case SPVM_TYPE_C_CODE_VOID: {
        void (*native_address)(SPVM_API*, SPVM_API_VALUE*) = constant_pool_sub->native_address;
        (*native_address)(api, (SPVM_API_VALUE*)call_stack);
        
        goto case_SPVM_BYTECODE_C_CODE_RETURN_VOID;
      }
      case SPVM_TYPE_C_CODE_BYTE: {
        int8_t (*native_address)(SPVM_API*, SPVM_API_VALUE*) = constant_pool_sub->native_address;
        int8_t return_value = (*native_address)(api, (SPVM_API_VALUE*)call_stack);

        if (runtime->exception) {
          return_value = 0;
        }
        
        operand_stack_top++;
        call_stack[operand_stack_top].byte_value = return_value;
        goto case_SPVM_BYTECODE_C_CODE_RETURN_BYTE;
      }
      case SPVM_TYPE_C_CODE_SHORT: {
        int16_t (*native_address)(SPVM_API*, SPVM_API_VALUE*) = constant_pool_sub->native_address;
        int16_t return_value = (*native_address)(api, (SPVM_API_VALUE*)call_stack);

        if (runtime->exception) {
          return_value = 0;
        }

        operand_stack_top++;
        call_stack[operand_stack_top].short_value = return_value;
        goto case_SPVM_BYTECODE_C_CODE_RETURN_SHORT;
      }
      case SPVM_TYPE_C_CODE_INT: {
        
        int32_t (*native_address)(SPVM_API*, SPVM_API_VALUE*) = constant_pool_sub->native_address;
        
        int32_t return_value = (*native_address)(api, (SPVM_API_VALUE*)call_stack);

        if (runtime->exception) {
          return_value = 0;
        }

        operand_stack_top++;
        call_stack[operand_stack_top].int_value = return_value;
        goto case_SPVM_BYTECODE_C_CODE_RETURN_INT;
      }
      case SPVM_TYPE_C_CODE_FLOAT: {
        float (*native_address)(SPVM_API*, SPVM_API_VALUE*) = constant_pool_sub->native_address;
        float return_value = (*native_address)(api, (SPVM_API_VALUE*)call_stack);

        if (runtime->exception) {
          return_value = 0;
        }
        
        operand_stack_top++;
        call_stack[operand_stack_top].float_value = return_value;
        goto case_SPVM_BYTECODE_C_CODE_RETURN_FLOAT;
      }
      case SPVM_TYPE_C_CODE_DOUBLE: {
        double (*native_address)(SPVM_API*, SPVM_API_VALUE*) = constant_pool_sub->native_address;
        double return_value = (*native_address)(api, (SPVM_API_VALUE*)call_stack);

        if (runtime->exception) {
          return_value = 0;
        }
        
        operand_stack_top++;
        call_stack[operand_stack_top].double_value = return_value;
        goto case_SPVM_BYTECODE_C_CODE_RETURN_DOUBLE;
      }
      default: {
        SPVM_OBJECT* (*native_address)(SPVM_API*, SPVM_API_VALUE*) = constant_pool_sub->native_address;
        SPVM_OBJECT* return_value = (*native_address)(api, (SPVM_API_VALUE*)call_stack);

        if (runtime->exception) {
          return_value = NULL;
        }
        
        operand_stack_top++;
        call_stack[operand_stack_top].object_value = return_value;
        goto case_SPVM_BYTECODE_C_CODE_RETURN_OBJECT;
      }
    }
  }
  // Call normal sub
  else {
    pc = &runtime->bytecodes[constant_pool_sub->bytecode_base];
  }
  
  // Jump table for direct threaded code
  // This must be same as bytecode order
  static const void* jump[] = {
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
    &&case_SPVM_BYTECODE_C_CODE_STORE_OBJECT,
    &&case_SPVM_BYTECODE_C_CODE_POP,
    &&case_SPVM_BYTECODE_C_CODE_NEW_OBJECT,
    &&case_SPVM_BYTECODE_C_CODE_NEW_STRING,
    &&case_SPVM_BYTECODE_C_CODE_NEW_OBJECT_ARRAY,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_INT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_LONG,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_OBJECT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_INT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_LONG,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_OBJECT,
    &&case_SPVM_BYTECODE_C_CODE_ARRAY_LENGTH,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_INT,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_LONG,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_GET_FIELD_OBJECT,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_INT,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_LONG,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_SET_FIELD_OBJECT,
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
    &&case_SPVM_BYTECODE_C_CODE_IF_EQ_CMP_OBJECT,
    &&case_SPVM_BYTECODE_C_CODE_IF_NE_CMP_OBJECT,
    &&case_SPVM_BYTECODE_C_CODE_IF_NULL,
    &&case_SPVM_BYTECODE_C_CODE_IF_NON_NULL,
    &&case_SPVM_BYTECODE_C_CODE_TABLE_SWITCH,
    &&case_SPVM_BYTECODE_C_CODE_LOOKUP_SWITCH,
    &&case_SPVM_BYTECODE_C_CODE_GOTO,
    &&case_SPVM_BYTECODE_C_CODE_CALL_SUB,
    &&case_SPVM_BYTECODE_C_CODE_RETURN_VOID,
    &&case_SPVM_BYTECODE_C_CODE_RETURN_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_RETURN_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_RETURN_INT,
    &&case_SPVM_BYTECODE_C_CODE_RETURN_LONG,
    &&case_SPVM_BYTECODE_C_CODE_RETURN_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_RETURN_DOUBLE,
    &&case_SPVM_BYTECODE_C_CODE_RETURN_OBJECT,
    &&case_SPVM_BYTECODE_C_CODE_DIE,
    &&case_SPVM_BYTECODE_C_CODE_LOAD_EXCEPTION,
    &&case_SPVM_BYTECODE_C_CODE_STORE_EXCEPTION,
    &&case_SPVM_BYTECODE_C_CODE_WIDE,
    &&case_SPVM_BYTECODE_C_CODE_CURRENT_LINE,
    &&case_SPVM_BYTECODE_C_CODE_WEAKEN_FIELD_OBJECT,
    &&case_SPVM_BYTECODE_C_CODE_NEW_BYTE_ARRAY,
    &&case_SPVM_BYTECODE_C_CODE_NEW_SHORT_ARRAY,
    &&case_SPVM_BYTECODE_C_CODE_NEW_INT_ARRAY,
    &&case_SPVM_BYTECODE_C_CODE_NEW_LONG_ARRAY,
    &&case_SPVM_BYTECODE_C_CODE_NEW_FLOAT_ARRAY,
    &&case_SPVM_BYTECODE_C_CODE_NEW_DOUBLE_ARRAY,
    &&case_SPVM_BYTECODE_C_CODE_CONCAT_STRING_STRING,
    &&case_SPVM_BYTECODE_C_CODE_CONCAT_STRING_BYTE,
    &&case_SPVM_BYTECODE_C_CODE_CONCAT_STRING_SHORT,
    &&case_SPVM_BYTECODE_C_CODE_CONCAT_STRING_INT,
    &&case_SPVM_BYTECODE_C_CODE_CONCAT_STRING_LONG,
    &&case_SPVM_BYTECODE_C_CODE_CONCAT_STRING_FLOAT,
    &&case_SPVM_BYTECODE_C_CODE_CONCAT_STRING_DOUBLE,
  };
  
  goto *jump[*pc];
  
  case_SPVM_BYTECODE_C_CODE_CALL_SUB: {
    // Get subroutine ID
    sub_id = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
    
    SPVM_CONSTANT_POOL_SUB* constant_pool_sub_called = (SPVM_CONSTANT_POOL_SUB*)&constant_pool[sub_id];
    
    int32_t args_length = constant_pool_sub_called->args_length;
    
    operand_stack_top -= args_length;
    
    SPVM_VALUE args[255];
    memcpy(args, &call_stack[operand_stack_top + 1], sizeof(SPVM_VALUE) * args_length);
    
    // Call subroutine
    SPVM_VALUE return_value = SPVM_RUNTIME_call_sub(api, sub_id, args);
    
    if (api->get_exception(api)) {
      memset(&return_value, 0, sizeof(SPVM_VALUE));
      
      // Exception handler
      pc += 5 + (debug * 5);
      
      goto *jump[*pc];
    }
    else {
      if (!constant_pool_sub_called->is_void) {
        operand_stack_top++;
        call_stack[operand_stack_top] = return_value;
      }
      
      // Next operation
      pc += 5 + (debug * 5) + 3;
      
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_RETURN_BYTE:
  case_SPVM_BYTECODE_C_CODE_RETURN_SHORT:
  case_SPVM_BYTECODE_C_CODE_RETURN_INT:
  case_SPVM_BYTECODE_C_CODE_RETURN_LONG:
  case_SPVM_BYTECODE_C_CODE_RETURN_FLOAT:
  case_SPVM_BYTECODE_C_CODE_RETURN_DOUBLE:
  {
    // Get return value
    SPVM_VALUE return_value = call_stack[operand_stack_top];
    
    // Decrement object my vars reference count
    int32_t object_my_vars_length = constant_pool_sub->object_my_vars_length;
    int32_t object_my_vars_base = constant_pool_sub->object_my_vars_base;
    
    if (object_my_vars_length) {
      {
        int32_t i;
        for (i = 0; i < object_my_vars_length; i++) {
          int32_t my_var_index = constant_pool[object_my_vars_base + i];
          SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[my_var_index].object_value;
          
          if (object != NULL) {
            SPVM_RUNTIME_API_dec_ref_count(api, object);
          }
        }
      }
    }
    
    SPVM_RUNTIME_API_dec_ref_count(api, call_stack_array);
    
    // No exception
    SPVM_RUNTIME_API_set_exception(api, NULL);
    
    return return_value;
  }
  case_SPVM_BYTECODE_C_CODE_RETURN_OBJECT: {
    
    SPVM_VALUE return_value = call_stack[operand_stack_top];
    
    // Increment ref count of return value not to release by decrement
    if (return_value.object_value != NULL) {
      return_value.object_value->ref_count++;
    }
    
    // Decrement object my vars reference count
    int32_t object_my_vars_length = constant_pool_sub->object_my_vars_length;
    int32_t object_my_vars_base = constant_pool_sub->object_my_vars_base;
    if (object_my_vars_length) {
      {
        int32_t i;
        for (i = 0; i < object_my_vars_length; i++) {
          int32_t my_var_index = constant_pool[object_my_vars_base + i];
          SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[my_var_index].object_value;
          
          if (object != NULL) {
            SPVM_RUNTIME_API_dec_ref_count(api, object);
          }
        }
      }
    }

    // Increment ref count of return value not to release by decrement
    if (return_value.object_value != NULL) {
      return_value.object_value->ref_count--;
    }
    
    SPVM_RUNTIME_API_dec_ref_count(api, call_stack_array);
    
    // No exception
    SPVM_RUNTIME_API_set_exception(api, NULL);
    
    return return_value;
  }
  case_SPVM_BYTECODE_C_CODE_RETURN_VOID: {
    SPVM_VALUE return_value;
    memset(&return_value, 0, sizeof(SPVM_VALUE));
    
    // Decrement object my vars reference count
    int32_t object_my_vars_length = constant_pool_sub->object_my_vars_length;
    int32_t object_my_vars_base = constant_pool_sub->object_my_vars_base;
    if (object_my_vars_length) {
      {
        int32_t i;
        for (i = 0; i < object_my_vars_length; i++) {
          int32_t my_var_index = constant_pool[object_my_vars_base + i];
          SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[my_var_index].object_value;
          
          if (object != NULL) {
            SPVM_RUNTIME_API_dec_ref_count(api, object);
          }
        }
      }
    }
    
    SPVM_RUNTIME_API_dec_ref_count(api, call_stack_array);
    
    // No exception
    SPVM_RUNTIME_API_set_exception(api, NULL);
    
    return return_value;
  }
  case_SPVM_BYTECODE_C_CODE_LOAD_EXCEPTION: {
    operand_stack_top++;
    call_stack[operand_stack_top].object_value = (SPVM_OBJECT*)runtime->exception;
    
    pc++;
    goto *jump[*pc];
  }
  case_SPVM_BYTECODE_C_CODE_STORE_EXCEPTION: {
    
    SPVM_RUNTIME_API_set_exception(api, (SPVM_OBJECT*)call_stack[operand_stack_top].object_value);
    
    operand_stack_top--;
    
    pc++;
    goto *jump[*pc];
  }
  case_SPVM_BYTECODE_C_CODE_DIE: {
    // Decrement object my vars reference count
    int32_t object_my_vars_length = constant_pool_sub->object_my_vars_length;
    int32_t object_my_vars_base = constant_pool_sub->object_my_vars_base;
    if (object_my_vars_length) {
      {
        int32_t i;
        for (i = 0; i < object_my_vars_length; i++) {
          int32_t my_var_index = constant_pool[object_my_vars_base + i];
          SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[my_var_index].object_value;
          
          if (object != NULL) {
            SPVM_RUNTIME_API_dec_ref_count(api, object);
          }
        }
      }
    }
    
    // Sub name
    int32_t sub_name_id = constant_pool_sub->abs_name_id;
    const char* sub_name = (char*)&constant_pool[sub_name_id + 1];
    
    // File name
    int32_t file_name_id = constant_pool_sub->file_name_id;
    const char* file_name = (char*)&constant_pool[file_name_id + 1];
    
    // stack trace strings
    const char* from = "\n  from ";
    const char* at = "() at ";
    
    // Total string length
    int32_t total_length = 0;
    total_length += SPVM_RUNTIME_API_get_string_length(api, runtime->exception);
    total_length += strlen(from);
    total_length += strlen(sub_name);
    total_length += strlen(at);
    total_length += strlen(file_name);

    const char* line = " line ";
    char line_str[20];
    
    if (debug) {
      sprintf(line_str, "%" PRId32, current_line);
      total_length += strlen(line);
      total_length += strlen(line_str);
    }
    
    // Create exception message
    SPVM_OBJECT* new_exception = SPVM_RUNTIME_API_new_string_len(api, total_length);
    memcpy(
      (void*)((intptr_t)new_exception + sizeof(SPVM_OBJECT)),
      (void*)((intptr_t)runtime->exception + sizeof(SPVM_OBJECT)),
      SPVM_RUNTIME_API_get_string_length(api, runtime->exception)
    );
    if (debug) {
      sprintf(
        (char*)((intptr_t)new_exception + sizeof(SPVM_OBJECT) + SPVM_RUNTIME_API_get_string_length(api, runtime->exception)),
        "%s%s%s%s%s%" PRId32,
        from,
        sub_name,
        at,
        file_name,
        line,
        current_line
      );
    }
    else {
      sprintf(
        (char*)((intptr_t)new_exception + sizeof(SPVM_OBJECT) + SPVM_RUNTIME_API_get_string_length(api, runtime->exception)),
        "%s%s%s%s",
        from,
        sub_name,
        at,
        file_name
      );
    }
    
    // Set exception
    SPVM_RUNTIME_API_set_exception(api, new_exception);
    
    SPVM_VALUE return_value;
    
    memset(&return_value, 0, sizeof(SPVM_VALUE));
    
    SPVM_RUNTIME_API_dec_ref_count(api, call_stack_array);
    
    return return_value;
  }
  case_SPVM_BYTECODE_C_CODE_NOP:
    // Not used
    assert(0);
  case_SPVM_BYTECODE_C_CODE_UNDEF:
    operand_stack_top++;
    call_stack[operand_stack_top].object_value = (void*)NULL;
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
    call_stack[operand_stack_top].byte_value = (int8_t)*(pc + 1);
    pc += 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_PUSH_BYTE_TO_SHORT:
    operand_stack_top++;
    call_stack[operand_stack_top].short_value = (int16_t)(int8_t)*(pc + 1);
    pc += 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_PUSH_SHORT:
    operand_stack_top++;
    call_stack[operand_stack_top].short_value = (int16_t)((*(pc + 1) << 8) +  *(pc + 2));
    pc += 3;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_PUSH_BYTE_TO_INT:
    operand_stack_top++;
    call_stack[operand_stack_top].int_value = (int32_t)(int8_t)*(pc + 1);
    pc += 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_PUSH_SHORT_TO_LONG:
    operand_stack_top++;
    call_stack[operand_stack_top].long_value = (int64_t)(int16_t)((*(pc + 1) << 8) +  *(pc + 2));
    pc += 3;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_PUSH_BYTE_TO_LONG:
    operand_stack_top++;
    call_stack[operand_stack_top].long_value = (int64_t)(int8_t)*(pc + 1);
    pc += 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_PUSH_SHORT_TO_INT:
    operand_stack_top++;
    call_stack[operand_stack_top].int_value = (int32_t)(int16_t)((*(pc + 1) << 8) +  *(pc + 2));
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
    call_stack[operand_stack_top] = call_stack[*(pc + 1)];
    pc += 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_LOAD_0:
    operand_stack_top++;
    call_stack[operand_stack_top] = call_stack[0];
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_LOAD_1:
    operand_stack_top++;
    call_stack[operand_stack_top] = call_stack[1];
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_LOAD_2:
    operand_stack_top++;
    call_stack[operand_stack_top] = call_stack[2];
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_LOAD_3:
    operand_stack_top++;
    call_stack[operand_stack_top] = call_stack[3];
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_BYTE: {
    SPVM_OBJECT* array = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    int32_t index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!array, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "BYTE_ARRAY must not be undef(BYTE_ARRAY->[INDEX])");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "INDEX is out of range(BYTE_ARRAY->[INDEX])");
        SPVM_RUNTIME_API_set_exception(api, exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].byte_value
          = *(int8_t*)((intptr_t)array + sizeof(SPVM_OBJECT) + sizeof(int8_t) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_SHORT: {
    SPVM_OBJECT* array = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    int32_t index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!array, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "SHORT_ARRAY must not be undef(SHORT_ARRAY->[INDEX])");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "INDEX is out of range(SHORT_ARRAY->[INDEX])");
        SPVM_RUNTIME_API_set_exception(api, exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].short_value
          = *(int16_t*)((intptr_t)array + sizeof(SPVM_OBJECT) + sizeof(int16_t) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_INT: {
    SPVM_OBJECT* array = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    int32_t index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!array, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "INT_ARRAY must not be undef(INT_ARRAY->[INDEX])");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "INDEX is out of range(INT_ARRAY->[INDEX])");
        SPVM_RUNTIME_API_set_exception(api, exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].int_value = *(int32_t*)((intptr_t)array + sizeof(SPVM_OBJECT) + sizeof(int32_t) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_LONG: {
    SPVM_OBJECT* array = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    int32_t index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!array, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "LONG_ARRAY must not be undef(LONG_ARRAY->[INDEX])");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "INDEX is out of range(LONG_ARRAY->[INDEX])");
        SPVM_RUNTIME_API_set_exception(api, exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].long_value = *(int64_t*)((intptr_t)array + sizeof(SPVM_OBJECT) + sizeof(int64_t) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_FLOAT: {
    SPVM_OBJECT* array = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    int32_t index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!array, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "FLOAT_ARRAY must not be undef(FLOAT_ARRAY->[INDEX])");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "INDEX is out of range(FLOAT_ARRAY->[INDEX])");
        SPVM_RUNTIME_API_set_exception(api, exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].float_value = *(float*)((intptr_t)array + sizeof(SPVM_OBJECT) + sizeof(float) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_DOUBLE: {
    SPVM_OBJECT* array = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    int32_t index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!array, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "DOUBLE_ARRAY must not be undef(DOUBLE_ARRAY->[INDEX])");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "INDEX is out of range(DOUBLE_ARRAY->[INDEX])");
        SPVM_RUNTIME_API_set_exception(api, exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1].double_value = *(double*)((intptr_t)array + sizeof(SPVM_OBJECT) + sizeof(double) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LOAD_OBJECT: {
    SPVM_OBJECT* array = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    int32_t index = call_stack[operand_stack_top].int_value;
    if (__builtin_expect(!array, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "OBJECT_ARRAY must not be undef(OBJECT_ARRAY->[INDEX])");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "INDEX is out of range(OBJECT_ARRAY->[INDEX])");
        SPVM_RUNTIME_API_set_exception(api, exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        call_stack[operand_stack_top - 1] = *(SPVM_VALUE*)((intptr_t)array + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * index);
        operand_stack_top--;
        pc++;
        goto *jump[*pc];
      }
    }
  }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_BYTE: {
    SPVM_OBJECT* array = (SPVM_OBJECT*)call_stack[operand_stack_top - 2].object_value;
    int32_t index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!array, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "BYTE_ARRAY must not be undef(BYTE_ARRAY->[INDEX] = VALUE)");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "INDEX is out of range(BYTE_ARRAY->[INDEX] = VALUE)");
        SPVM_RUNTIME_API_set_exception(api, exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        *(int8_t*)((intptr_t)call_stack[operand_stack_top - 2].object_value + sizeof(SPVM_OBJECT) + sizeof(int8_t) * call_stack[operand_stack_top - 1].int_value)
          = call_stack[operand_stack_top].byte_value;
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_SHORT: {
    SPVM_OBJECT* array = (SPVM_OBJECT*)call_stack[operand_stack_top - 2].object_value;
    int32_t index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!array, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "SHORT_ARRAY must not be undef(SHORT_ARRAY->[INDEX] = VALUE)");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "INDEX is out of range(SHORT_ARRAY->[INDEX] = VALUE)");
        SPVM_RUNTIME_API_set_exception(api, exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        *(int16_t*)((intptr_t)call_stack[operand_stack_top - 2].object_value + sizeof(SPVM_OBJECT) + sizeof(int16_t) * call_stack[operand_stack_top - 1].int_value)
          = call_stack[operand_stack_top].short_value;
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_INT: {
    SPVM_OBJECT* array = (SPVM_OBJECT*)call_stack[operand_stack_top - 2].object_value;
    int32_t index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!array, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "INT_ARRAY must not be undef(INT_ARRAY->[INDEX] = VALUE)");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "INDEX is out of range(INT_ARRAY->[INDEX] = VALUE)");
        SPVM_RUNTIME_API_set_exception(api, exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        *(int32_t*)((intptr_t)array + sizeof(SPVM_OBJECT) + sizeof(int32_t) * index) = call_stack[operand_stack_top].int_value;
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_LONG: {
    SPVM_OBJECT* array = (SPVM_OBJECT*)call_stack[operand_stack_top - 2].object_value;
    int32_t index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!array, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "LONG_ARRAY must not be undef(LONG_ARRAY->[INDEX] = VALUE)");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "INDEX is out of range(LONG_ARRAY->[INDEX] = VALUE)");
        SPVM_RUNTIME_API_set_exception(api, exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        *(int64_t*)((intptr_t)array + sizeof(SPVM_OBJECT) + sizeof(int64_t) * index) = call_stack[operand_stack_top].long_value;
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_FLOAT: {
    SPVM_OBJECT* array = (SPVM_OBJECT*)call_stack[operand_stack_top - 2].object_value;
    int32_t index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!array, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "FLOAT_ARRAY must not be undef(FLOAT_ARRAY->[INDEX] = VALUE)");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "INDEX is out of range(FLOAT_ARRAY->[INDEX] = VALUE)");
        SPVM_RUNTIME_API_set_exception(api, exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        *(float*)((intptr_t)array + sizeof(SPVM_OBJECT) + sizeof(float) * index) = call_stack[operand_stack_top].float_value;
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_DOUBLE: {
    SPVM_OBJECT* array = (SPVM_OBJECT*)call_stack[operand_stack_top - 2].object_value;
    int32_t index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!array, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "DOUBLE_ARRAY must not be undef(DOUBLE_ARRAY->[INDEX] = VALUE)");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "INDEX is out of range(DOUBLE_ARRAY->[INDEX] = VALUE)");
        SPVM_RUNTIME_API_set_exception(api, exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        *(double*)((intptr_t)call_stack[operand_stack_top - 2].object_value + sizeof(SPVM_OBJECT) + sizeof(double) * call_stack[operand_stack_top - 1].int_value)
          = call_stack[operand_stack_top].double_value;
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  }
  case_SPVM_BYTECODE_C_CODE_ARRAY_STORE_OBJECT: {
    
    SPVM_OBJECT* array = (SPVM_OBJECT*)call_stack[operand_stack_top - 2].object_value;
    int32_t index = call_stack[operand_stack_top - 1].int_value;
    if (__builtin_expect(!array, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "OBJECT_ARRAY must not be undef(OBJECT_ARRAY->[INDEX] = VALUE)");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      if (__builtin_expect(index < 0 || index >= array->length, 0)) {
        SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "INDEX is out of range(OBJECT_ARRAY->[INDEX] = VALUE)");
        SPVM_RUNTIME_API_set_exception(api, exception);
        goto case_SPVM_BYTECODE_C_CODE_DIE;
      }
      else {
        SPVM_OBJECT** object_address = (SPVM_OBJECT**)((intptr_t)array + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * index);
        
        // Decrement old object reference count
        if (*object_address != NULL) {
          SPVM_RUNTIME_API_dec_ref_count(api, *object_address);
        }
        
        // Store address
        *object_address = call_stack[operand_stack_top].object_value;

        // Increment new object reference count
        if (*object_address != NULL) {
          (*object_address)->ref_count++;
        }
        
        operand_stack_top -= 3;
        pc++;
        goto *jump[*pc];
      }
    }
  }
  case_SPVM_BYTECODE_C_CODE_STORE:
    call_stack[*(pc + 1)] = call_stack[operand_stack_top];
    operand_stack_top--;
    pc += 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_STORE_0:
    call_stack[0] = call_stack[operand_stack_top];
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_STORE_1:
    call_stack[1] = call_stack[operand_stack_top];
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_STORE_2:
    call_stack[2] = call_stack[operand_stack_top];
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_STORE_3:
    call_stack[3] = call_stack[operand_stack_top];
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_STORE_OBJECT: {
    int32_t index = *(pc + 1);
    
    // Decrement reference count
    if (call_stack[index].object_value != NULL) {
      SPVM_RUNTIME_API_dec_ref_count(api, call_stack[index].object_value);
    }
    
    // Store object
    call_stack[index].object_value = call_stack[operand_stack_top].object_value;
    
    // Increment new value reference count
    if (call_stack[index].object_value != NULL) {
      call_stack[index].object_value->ref_count++;
    }
    
    operand_stack_top--;
    pc += 2;
    goto *jump[*pc];
  }
  case_SPVM_BYTECODE_C_CODE_POP:
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
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
    call_stack[operand_stack_top - 1].float_value += call_stack[operand_stack_top].float_value;
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
    call_stack[operand_stack_top - 1].float_value -= call_stack[operand_stack_top].float_value;
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
    call_stack[operand_stack_top - 1].float_value *= call_stack[operand_stack_top].float_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_MULTIPLY_DOUBLE:
    call_stack[operand_stack_top - 1].double_value *= call_stack[operand_stack_top].double_value;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_DIVIDE_BYTE:
    if (call_stack[operand_stack_top].byte_value == 0) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "0 division (byte / byte)");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      call_stack[operand_stack_top - 1].byte_value /= call_stack[operand_stack_top].byte_value;
      operand_stack_top--;
      pc++;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_DIVIDE_SHORT:
    if (call_stack[operand_stack_top].short_value == 0) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "0 division (short / short)");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      call_stack[operand_stack_top - 1].short_value /= call_stack[operand_stack_top].short_value;
      operand_stack_top--;
      pc++;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_DIVIDE_INT:
    if (call_stack[operand_stack_top].int_value == 0) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "0 division (int / int)");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      call_stack[operand_stack_top - 1].int_value /= call_stack[operand_stack_top].int_value;
      operand_stack_top--;
      pc++;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_DIVIDE_LONG:
    if (call_stack[operand_stack_top].long_value == 0) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "0 division (long / long)");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      call_stack[operand_stack_top - 1].long_value /= call_stack[operand_stack_top].long_value;
      operand_stack_top--;
      pc++;
      goto *jump[*pc];
    }
  case_SPVM_BYTECODE_C_CODE_DIVIDE_FLOAT:
    call_stack[operand_stack_top - 1].float_value /= call_stack[operand_stack_top].float_value;
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
      = (float)fmod((double)call_stack[operand_stack_top - 1].float_value, (double)call_stack[operand_stack_top].float_value);
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
      = (int8_t)(((uint8_t)call_stack[operand_stack_top - 1].byte_value) >> call_stack[operand_stack_top].int_value);
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_SHORT:
    call_stack[operand_stack_top - 1].short_value
      = (int16_t)(((uint16_t)call_stack[operand_stack_top - 1].short_value) >> call_stack[operand_stack_top].int_value);
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_INT:
    call_stack[operand_stack_top - 1].int_value
      = (int32_t)(((uint32_t)call_stack[operand_stack_top - 1].int_value) >> call_stack[operand_stack_top].int_value);
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_LONG:
    call_stack[operand_stack_top - 1].long_value
      = (int64_t)(((uint64_t)call_stack[operand_stack_top - 1].long_value) >> call_stack[operand_stack_top].int_value);
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
    call_stack[*(pc + 1)].byte_value += (int8_t)*(pc + 2);
    pc += 3;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_INC_SHORT:
    call_stack[*(pc + 1)].short_value += (int8_t)*(pc + 2);
    pc += 3;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_INC_INT:
    call_stack[*(pc + 1)].int_value += (int8_t)*(pc + 2);
    pc += 3;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_INC_LONG:
    call_stack[*(pc + 1)].long_value += (int8_t)*(pc + 2);
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
    call_stack[operand_stack_top].float_value = (float)call_stack[operand_stack_top].byte_value;
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
    call_stack[operand_stack_top].float_value = (float)call_stack[operand_stack_top].short_value;
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
    call_stack[operand_stack_top].byte_value = (int8_t)call_stack[operand_stack_top].float_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_SHORT:
    // TODO
    call_stack[operand_stack_top].short_value = (int16_t)call_stack[operand_stack_top].float_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_BYTE:
    // TODO
    call_stack[operand_stack_top].byte_value = (int8_t)call_stack[operand_stack_top].double_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_SHORT:
    // TODO
    call_stack[operand_stack_top].short_value = (int16_t)call_stack[operand_stack_top].double_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_SHORT:
    call_stack[operand_stack_top].short_value = (int16_t)call_stack[operand_stack_top].byte_value;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CMP_BYTE:
    // z = (x > y) + (x < y) * -1
    call_stack[operand_stack_top - 1].int_value
      = (call_stack[operand_stack_top - 1].byte_value > call_stack[operand_stack_top].byte_value)
      + (call_stack[operand_stack_top - 1].byte_value < call_stack[operand_stack_top].byte_value) * -1;
    
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CMP_SHORT:
    // z = (x > y) + (x < y) * -1
    call_stack[operand_stack_top - 1].int_value
      = (call_stack[operand_stack_top - 1].short_value > call_stack[operand_stack_top].short_value)
      + (call_stack[operand_stack_top - 1].short_value < call_stack[operand_stack_top].short_value) * -1;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CMP_LONG:
    // z = (x > y) + (x < y) * -1
    call_stack[operand_stack_top - 1].int_value
      = (call_stack[operand_stack_top - 1].long_value > call_stack[operand_stack_top].long_value)
      + (call_stack[operand_stack_top - 1].long_value < call_stack[operand_stack_top].long_value) * -1;
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CMP_FLOAT_L:
    call_stack[operand_stack_top - 1].int_value
      = (call_stack[operand_stack_top - 1].float_value > call_stack[operand_stack_top].float_value)
      + (call_stack[operand_stack_top - 1].float_value < call_stack[operand_stack_top].float_value) * -1
      + -!!(
        isnan(call_stack[operand_stack_top - 1].float_value)
        | isnan(call_stack[operand_stack_top - 1].float_value)
      );
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_CMP_FLOAT_G:
    call_stack[operand_stack_top - 1].int_value
      = (call_stack[operand_stack_top - 1].float_value > call_stack[operand_stack_top].float_value)
      + (call_stack[operand_stack_top - 1].float_value < call_stack[operand_stack_top].float_value) * -1
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
  case_SPVM_BYTECODE_C_CODE_IF_EQ_CMP_OBJECT:
    success = call_stack[operand_stack_top - 1].object_value == call_stack[operand_stack_top].object_value;
    pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
    operand_stack_top -= 2;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_IF_NE_CMP_OBJECT:
    success = call_stack[operand_stack_top - 1].object_value != call_stack[operand_stack_top].object_value;
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
  case_SPVM_BYTECODE_C_CODE_NEW_OBJECT: {
    // Get subroutine ID
    int32_t type_id = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
    
    SPVM_OBJECT* object = SPVM_RUNTIME_API_new_object(api, type_id);

    // Memory allocation error
    if (__builtin_expect(!object, 0)) {
      // Sub name
      int32_t abs_name_id = constant_pool_sub->abs_name_id;
      const char* sub_name = (char*)&constant_pool[abs_name_id + 1];
      
      // File name
      int32_t file_name_id = constant_pool_sub->file_name_id;
      const char* file_name = (char*)&constant_pool[file_name_id + 1];
      
      fprintf(stderr, "Failed to allocate memory(new package) from %s at %s\n", sub_name, file_name);
      abort();
    }
    
    // Push object
    operand_stack_top++;
    call_stack[operand_stack_top].object_value = (SPVM_OBJECT*)object;
    
    pc += 5;
    goto *jump[*pc];
  }
  case_SPVM_BYTECODE_C_CODE_NEW_BYTE_ARRAY: {
    
    // length
    int32_t length = call_stack[operand_stack_top].int_value;
    
    SPVM_OBJECT* object = SPVM_RUNTIME_API_new_byte_array(api, length);
    
    if (__builtin_expect(object == NULL, 0)) {
      // Throw exception
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      // Set array
      call_stack[operand_stack_top].object_value = object;
      
      pc++;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_NEW_SHORT_ARRAY: {
    
    // length
    int32_t length = call_stack[operand_stack_top].int_value;
    
    SPVM_OBJECT* object = SPVM_RUNTIME_API_new_short_array(api, length);
    
    if (__builtin_expect(object == NULL, 0)) {
      // Throw exception
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      // Set array
      call_stack[operand_stack_top].object_value = object;
      
      pc++;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_NEW_INT_ARRAY: {
    
    // length
    int32_t length = call_stack[operand_stack_top].int_value;
    
    SPVM_OBJECT* object = SPVM_RUNTIME_API_new_int_array(api, length);
    
    if (__builtin_expect(object == NULL, 0)) {
      // Throw exception
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      // Set array
      call_stack[operand_stack_top].object_value = object;
      
      pc++;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_NEW_LONG_ARRAY: {
    
    // length
    int32_t length = call_stack[operand_stack_top].int_value;
    
    SPVM_OBJECT* object = SPVM_RUNTIME_API_new_long_array(api, length);
    
    if (__builtin_expect(object == NULL, 0)) {
      // Throw exception
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      // Set array
      call_stack[operand_stack_top].object_value = object;
      
      pc++;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_NEW_FLOAT_ARRAY: {
    
    // length
    int32_t length = call_stack[operand_stack_top].int_value;
    
    SPVM_OBJECT* object = SPVM_RUNTIME_API_new_float_array(api, length);
    
    if (__builtin_expect(object == NULL, 0)) {
      // Throw exception
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      // Set array
      call_stack[operand_stack_top].object_value = object;
      
      pc++;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_NEW_DOUBLE_ARRAY: {
    
    // length
    int32_t length = call_stack[operand_stack_top].int_value;
    
    SPVM_OBJECT* object = SPVM_RUNTIME_API_new_double_array(api, length);
    
    if (__builtin_expect(object == NULL, 0)) {
      // Throw exception
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      // Set array
      call_stack[operand_stack_top].object_value = object;
      
      pc++;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_NEW_OBJECT_ARRAY: {
    int32_t element_type_id = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
    
    // length
    int32_t length = call_stack[operand_stack_top].int_value;
    
    SPVM_OBJECT* object = SPVM_RUNTIME_API_new_object_array(api, element_type_id, length);
    
    if (__builtin_expect(object == NULL, 0)) {
      // Throw exception
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      // Set object
      call_stack[operand_stack_top].object_value = object;
      
      pc += 5;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_NEW_STRING: {
    int32_t name_id = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
    
    SPVM_OBJECT* array = SPVM_RUNTIME_API_new_string(api, (char*)&constant_pool[name_id + 1]);
    if (__builtin_expect(array != NULL, 1)) {
      // Set string
      operand_stack_top++;
      call_stack[operand_stack_top].object_value = (SPVM_OBJECT*)array;
      
      pc += 5;
      goto *jump[*pc];
    }
    // Memory allocation error
    else {
      // Sub name
      int32_t abs_name_id = constant_pool_sub->abs_name_id;
      const char* sub_name = (char*)&constant_pool[abs_name_id + 1];
      
      // File name
      int32_t file_name_id = constant_pool_sub->file_name_id;
      const char* file_name = (char*)&constant_pool[file_name_id + 1];
      
      fprintf(stderr, "Failed to allocate memory(new string) from %s at %s\n", sub_name, file_name);
      abort();
    }
  }
  case_SPVM_BYTECODE_C_CODE_ARRAY_LENGTH:
    call_stack[operand_stack_top].int_value = (int32_t)((SPVM_OBJECT*)call_stack[operand_stack_top].object_value)->length;
    pc++;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_WIDE:
    // iload, fload, aload, lload, dload, istore, fstore, astore, lstore, dstore, or iinc
    
    switch(*(pc + 1)) {
      case SPVM_BYTECODE_C_CODE_LOAD:
        operand_stack_top++;
        call_stack[operand_stack_top] = call_stack[(*(pc + 2) << 8) + *(pc + 3)];
        pc +=4;
        break;
      case SPVM_BYTECODE_C_CODE_STORE:
        call_stack[(*(pc + 2) << 8) + *(pc + 3)] = call_stack[operand_stack_top];
        operand_stack_top--;
        pc +=4;
        break;
      case SPVM_BYTECODE_C_CODE_STORE_OBJECT: {
        int32_t index = (*(pc + 2) << 8) + *(pc + 3);
        
        // Decrement reference count
        if (call_stack[index].object_value != NULL) {
          SPVM_RUNTIME_API_dec_ref_count(api, call_stack[index].object_value);
        }
        
        // Store object
        call_stack[index].object_value = call_stack[operand_stack_top].object_value;
        
        // Increment new value reference count
        if (call_stack[index].object_value != NULL) {
          call_stack[index].object_value->ref_count++;
        }
        
        operand_stack_top--;
        pc +=4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_INC_BYTE:
        call_stack[(*(pc + 2) << 8) + *(pc + 3)].byte_value += (int8_t)((*(pc + 4) << 8) + *(pc + 5));
        pc += 6;
        break;
      case SPVM_BYTECODE_C_CODE_INC_SHORT:
        call_stack[(*(pc + 2) << 8) + *(pc + 3)].short_value += (int16_t)((*(pc + 4) << 8) + *(pc + 5));
        pc += 6;
        break;
      case SPVM_BYTECODE_C_CODE_INC_INT:
        call_stack[(*(pc + 2) << 8) + *(pc + 3)].int_value += (int32_t)((*(pc + 4) << 8) + *(pc + 5));
        pc += 6;
        break;
      case SPVM_BYTECODE_C_CODE_INC_LONG:
        call_stack[(*(pc + 2) << 8) + *(pc + 3)].long_value += (int64_t)((*(pc + 4) << 8) + *(pc + 5));
        pc += 6;
        break;
    }
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_IF_NULL:
    success = call_stack[operand_stack_top].object_value == (void*)NULL;
    pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
    operand_stack_top--;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_IF_NON_NULL:
    
    success = call_stack[operand_stack_top].object_value != (void*)NULL;
    pc += success * (int16_t)((*(pc + 1) << 8) +  *(pc + 2)) + (~success & 1) * 3;
    operand_stack_top--;
    goto *jump[*pc];
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_BYTE: {
    SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[operand_stack_top].object_value;
    if (__builtin_expect(!object, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Object to get an byte field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      int32_t field_id = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top].byte_value
        = *(int8_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * (field_id - 1));
      pc += 3;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_SHORT: {
    SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[operand_stack_top].object_value;
    if (__builtin_expect(!object, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Object to get an short field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      int32_t field_id = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top].short_value
        = *(int16_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * (field_id - 1));
      pc += 3;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_INT: {
    SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[operand_stack_top].object_value;
    if (__builtin_expect(!object, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Object to get an int field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      int32_t field_id = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top].int_value
        = *(int32_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * (field_id - 1));
      pc += 3;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_LONG: {
    SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[operand_stack_top].object_value;
    if (__builtin_expect(!object, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Object to get an long field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      int32_t field_id = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top].long_value
        = *(int64_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * (field_id - 1));
      pc += 3;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_FLOAT: {
    SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[operand_stack_top].object_value;
    if (__builtin_expect(!object, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Object to get an float field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      int32_t field_id = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top].float_value
        = *(float*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * (field_id - 1));
      pc += 3;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_DOUBLE: {
    SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[operand_stack_top].object_value;
    if (__builtin_expect(!object, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Object to get an double field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      int32_t field_id = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top].double_value
        = *(double*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * (field_id - 1));
      pc += 3;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_GET_FIELD_OBJECT: {
    SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[operand_stack_top].object_value;
    if (__builtin_expect(!object, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Object to get an object field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      int32_t field_id = (*(pc + 1) << 8) + *(pc + 2);
      call_stack[operand_stack_top].object_value
        = *(void**)((intptr_t)call_stack[operand_stack_top].object_value + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * (field_id - 1));
      pc += 3;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_WEAKEN_FIELD_OBJECT: {
    SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[operand_stack_top].object_value;
    if (__builtin_expect(!object, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Object to weaken an object field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      int32_t field_id = (*(pc + 1) << 8) + *(pc + 2);
      SPVM_OBJECT** object_address = (SPVM_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * (field_id - 1));
      
      // Weaken object field
      if (*object_address != NULL) {
        SPVM_RUNTIME_API_weaken(api, object_address);
      }
      
      pc += 3;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_BYTE: {
    SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    if (__builtin_expect(!object, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Object to set an byte field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      int32_t field_id = (*(pc + 1) << 8) + *(pc + 2);
      *(int8_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * (field_id - 1))
        = call_stack[operand_stack_top].byte_value;
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_SHORT: {
    SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    if (__builtin_expect(!object, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Object to set an short field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      int32_t field_id = (*(pc + 1) << 8) + *(pc + 2);
      *(int16_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * (field_id - 1))
        = call_stack[operand_stack_top].short_value;
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_INT: {
    SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    if (__builtin_expect(!object, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Object to set an int field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      int32_t field_id = (*(pc + 1) << 8) + *(pc + 2);
      *(int32_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * (field_id - 1))
        = call_stack[operand_stack_top].int_value;
      
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_LONG: {
    SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    if (__builtin_expect(!object, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Object to set an long field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      int32_t field_id = (*(pc + 1) << 8) + *(pc + 2);
      *(int64_t*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * (field_id - 1))
        = call_stack[operand_stack_top].long_value;
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_FLOAT: {
    SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    if (__builtin_expect(!object, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Object to set an float field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      int32_t field_id = (*(pc + 1) << 8) + *(pc + 2);
      *(float*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * (field_id - 1))
        = call_stack[operand_stack_top].float_value;
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_DOUBLE: {
    SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    if (__builtin_expect(!object, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Object to set an double field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      int32_t field_id = (*(pc + 1) << 8) + *(pc + 2);
      *(double*)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * (field_id - 1))
        = call_stack[operand_stack_top].double_value;
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_SET_FIELD_OBJECT: {
    SPVM_OBJECT* object = (SPVM_OBJECT*)call_stack[operand_stack_top - 1].object_value;
    if (__builtin_expect(!object, 0)) {
      SPVM_OBJECT* exception = SPVM_RUNTIME_API_new_string(api, "Object to set an object field must not be undefined.");
      SPVM_RUNTIME_API_set_exception(api, exception);
      goto case_SPVM_BYTECODE_C_CODE_DIE;
    }
    else {
      int32_t field_id = (*(pc + 1) << 8) + *(pc + 2);
      SPVM_OBJECT** object_address = (SPVM_OBJECT**)((intptr_t)object + sizeof(SPVM_OBJECT) + sizeof(SPVM_VALUE) * (field_id - 1));
      
      if (*object_address != NULL) {
        // If object is weak, unweaken
        if (SPVM_RUNTIME_API_isweak(api, *object_address)) {
          SPVM_RUNTIME_API_unweaken(api, object_address);
        }
        
        // Decrement old ojbect reference count
        SPVM_RUNTIME_API_dec_ref_count(api, *object_address);
      }
      
      // Store object
      *object_address = call_stack[operand_stack_top].object_value;
      
      // Increment new object reference count
      if (*object_address != NULL) {
        (*object_address)->ref_count++;
      }
      
      operand_stack_top -= 2;
      pc += 3;
      goto *jump[*pc];
    }
  }
  case_SPVM_BYTECODE_C_CODE_CONCAT_STRING_STRING: {
    SPVM_OBJECT* value1 = call_stack[operand_stack_top - 1].object_value;
    SPVM_OBJECT* value2 = call_stack[operand_stack_top].object_value;
    
    int32_t value1_length = SPVM_RUNTIME_API_get_string_length(api, value1);
    int32_t value2_length = SPVM_RUNTIME_API_get_string_length(api, value2);
    
    int32_t value3_length = value1_length + value2_length;
    SPVM_OBJECT* value3 = SPVM_RUNTIME_API_new_string_len(api, value3_length);
    
    char* value1_bytes = SPVM_RUNTIME_API_get_string_bytes(api, value1);
    char* value2_bytes = SPVM_RUNTIME_API_get_string_bytes(api, value2);
    char* value3_bytes = SPVM_RUNTIME_API_get_string_bytes(api, value3);
    
    memcpy(value3_bytes, value1_bytes, value1_length);
    memcpy(value3_bytes + value1_length, value2_bytes, value2_length);
    
    call_stack[operand_stack_top - 1].object_value = value3;
    
    operand_stack_top--;
    pc++;
    goto *jump[*pc];
  }
  case_SPVM_BYTECODE_C_CODE_CONCAT_STRING_BYTE: {
    assert(0);
  }
  case_SPVM_BYTECODE_C_CODE_CONCAT_STRING_SHORT: {
    assert(0);
  }
  case_SPVM_BYTECODE_C_CODE_CONCAT_STRING_INT: {
    assert(0);
  }
  case_SPVM_BYTECODE_C_CODE_CONCAT_STRING_LONG: {
    assert(0);
  }
  case_SPVM_BYTECODE_C_CODE_CONCAT_STRING_FLOAT: {
    assert(0);
  }
  case_SPVM_BYTECODE_C_CODE_CONCAT_STRING_DOUBLE: {
    assert(0);
  }
  
  case_SPVM_BYTECODE_C_CODE_CURRENT_LINE:
    current_line = (*(pc + 1) << 24) + (*(pc + 2) << 16) + (*(pc + 3) << 8) + *(pc + 4);
    pc += 5;
    goto *jump[*pc];
}

void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime) {

  // Free exception
  SPVM_RUNTIME_API_set_exception(runtime->api, NULL);
  
  // Free runtime allocator
  SPVM_RUNTIME_ALLOCATOR_free(runtime, runtime->allocator);

  free(runtime);
}
