#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stddef.h>

#include "spvm_api.h"
#include "spvm_bytecode.h"
#include "spvm_object.h"
#include "spvm_type.h"
#include "spvm_value.h"
#include "spvm_runtime.h"
#include "spvm_constant_pool.h"
#include "spvm_constant_pool_sub.h"

#define SPVM_INFO_OBJECT_HEADER_BYTE_SIZE sizeof(SPVM_OBJECT)
#define SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET (int32_t)offsetof(SPVM_OBJECT, length)
#define SPVM_INFO_TYPE_CODE_VOID SPVM_TYPE_C_CODE_VOID
#define SPVM_INFO_TYPE_CODE_BYTE SPVM_TYPE_C_CODE_BYTE
#define SPVM_INFO_TYPE_CODE_SHORT SPVM_TYPE_C_CODE_SHORT
#define SPVM_INFO_TYPE_CODE_INT SPVM_TYPE_C_CODE_INT
#define SPVM_INFO_TYPE_CODE_LONG SPVM_TYPE_C_CODE_LONG
#define SPVM_INFO_TYPE_CODE_FLOAT SPVM_TYPE_C_CODE_FLOAT
#define SPVM_INFO_TYPE_CODE_DOUBLE SPVM_TYPE_C_CODE_DOUBLE

SPVM_VALUE SPVM_RUNTIME_call_sub(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args) {
  (void)api;
  
  // Runtime
  SPVM_RUNTIME* SPVM_INFO_RUNTIME = SPVM_RUNTIME_API_get_runtime(api);
  
  // Constant pool
  int32_t* SPVM_INFO_CONSTANT_POOL = SPVM_INFO_RUNTIME->constant_pool;

  // Constant pool sub
  SPVM_CONSTANT_POOL_SUB* SPVM_INFO_CONSTANT_POOL_SUB_XXX = (SPVM_CONSTANT_POOL_SUB*)&SPVM_INFO_CONSTANT_POOL[sub_id];
  
  // Package variables
  SPVM_VALUE* SPVM_INFO_PACKAGE_VARS = SPVM_INFO_RUNTIME->package_vars;

  // Debug
  int32_t SPVM_INFO_DEBUG = SPVM_INFO_RUNTIME->debug ? 1 : 0;
  
  // Subroutine object my length
  int32_t SPVM_INFO_SUB_XXX_OBJECT_MYS_LENGTH = SPVM_INFO_CONSTANT_POOL_SUB_XXX->object_mys_length;
  
  // Subroutine object my base index
  int32_t SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE = SPVM_INFO_CONSTANT_POOL_SUB_XXX->object_mys_base;
  
  // Bytecodes
  int32_t* SPVM_INFO_BYTECODES = SPVM_INFO_RUNTIME->bytecodes;
  
  // Args length
  int32_t args_length = SPVM_INFO_CONSTANT_POOL_SUB_XXX->args_length;
  
  // Lexical varialbe length
  int32_t SPVM_INFO_SUB_XXX_MYS_LENGTH = SPVM_INFO_CONSTANT_POOL_SUB_XXX->mys_length;
  
  // Call_stack_max
  int32_t call_stack_length = SPVM_INFO_SUB_XXX_MYS_LENGTH + api->get_sub_operand_stack_max(api, sub_id);
  
  // Call stack
  SPVM_API_OBJECT* call_stack_array = api->new_value_array(api, call_stack_length);
  api->inc_ref_count(api, call_stack_array);
  SPVM_VALUE* call_stack = api->get_value_array_elements(api, (SPVM_API_OBJECT*)call_stack_array);
  
  // Catch stack
  int32_t catch_exception_stack[255];
  
  // Catch stack top
  int32_t catch_exception_stack_top = -1;
  
  // Current line
  int32_t current_line = 0;
  
  // Operand stack top
  register int32_t operand_stack_top = SPVM_INFO_SUB_XXX_MYS_LENGTH - 1;
  
  // Condition flag
  register int32_t condition_flag = 0;

  // Bytecode index
  int32_t bytecode_index = 0;
  
  SPVM_VALUE return_value;
  memset(&return_value, 0, sizeof(SPVM_VALUE));
  
  // Copy arguments
  memcpy(call_stack, args, args_length * sizeof(SPVM_VALUE));
  
  // If arg is object, increment reference count
  if (api->get_sub_object_args_length(api, sub_id)) {
    int32_t object_args_base = api->get_sub_object_args_base(api, sub_id);
    int32_t object_args_length = api->get_sub_object_args_length(api, sub_id);
    {
      int32_t i;
      for (i = 0; i < object_args_length; i++) {
        int32_t arg_index = SPVM_INFO_CONSTANT_POOL[object_args_base + i];
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[arg_index].object_value;
        if (object != NULL) {
          api->inc_ref_count(api, object);
        }
      }
    }
  }
  
  api->set_exception(api, NULL);
  
  // Call native sub
  if (api->get_sub_is_native(api, sub_id)) {
    int32_t return_type_code = api->get_type_code(api, api->get_sub_return_type_id(api, sub_id));
    
    // Call native subroutine
    if (return_type_code == SPVM_INFO_TYPE_CODE_VOID) {
      void (*native_address)(SPVM_API*, SPVM_VALUE*) = api->get_sub_native_address(api, sub_id);
      (*native_address)(api, (SPVM_VALUE*)call_stack);
      
      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      goto label_SPVM_BYTECODE_C_CODE_RETURN_VOID;
    }
    else if (return_type_code == SPVM_INFO_TYPE_CODE_BYTE) {
      int8_t (*native_address)(SPVM_API*, SPVM_VALUE*) = api->get_sub_native_address(api, sub_id);
      int8_t return_value_native = (*native_address)(api, (SPVM_VALUE*)call_stack);
      return_value.byte_value = return_value_native;

      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      goto label_SPVM_BYTECODE_C_CODE_RETURN_BYTE;
    }
    else if (return_type_code == SPVM_INFO_TYPE_CODE_SHORT) {
      int16_t (*native_address)(SPVM_API*, SPVM_VALUE*) = api->get_sub_native_address(api, sub_id);
      int16_t return_value_native = (*native_address)(api, (SPVM_VALUE*)call_stack);
      return_value.short_value = return_value_native;

      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }

      goto label_SPVM_BYTECODE_C_CODE_RETURN_SHORT;
    }
    else if (return_type_code == SPVM_INFO_TYPE_CODE_INT) {
        
      int32_t (*native_address)(SPVM_API*, SPVM_VALUE*) = api->get_sub_native_address(api, sub_id);
      
      int32_t return_value_native = (*native_address)(api, (SPVM_VALUE*)call_stack);
      return_value.int_value = return_value_native;
      
      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      goto label_SPVM_BYTECODE_C_CODE_RETURN_INT;
    }
    else if (return_type_code == SPVM_INFO_TYPE_CODE_LONG) {
      int64_t (*native_address)(SPVM_API*, SPVM_VALUE*) = api->get_sub_native_address(api, sub_id);
      int64_t return_value_native = (*native_address)(api, (SPVM_VALUE*)call_stack);
      return_value.long_value = return_value_native;

      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }

      goto label_SPVM_BYTECODE_C_CODE_RETURN_LONG;
    }
    else if (return_type_code == SPVM_INFO_TYPE_CODE_FLOAT) {
      float (*native_address)(SPVM_API*, SPVM_VALUE*) = api->get_sub_native_address(api, sub_id);
      float return_value_native = (*native_address)(api, (SPVM_VALUE*)call_stack);
      return_value.float_value = return_value_native;

      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      goto label_SPVM_BYTECODE_C_CODE_RETURN_FLOAT;
    }
    else if (return_type_code == SPVM_INFO_TYPE_CODE_DOUBLE) {
      double (*native_address)(SPVM_API*, SPVM_VALUE*) = api->get_sub_native_address(api, sub_id);
      double return_value_native = (*native_address)(api, (SPVM_VALUE*)call_stack);
      return_value.double_value = return_value_native;

      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      goto label_SPVM_BYTECODE_C_CODE_RETURN_DOUBLE;
    }
    else {
      
      SPVM_API_OBJECT* (*native_address)(SPVM_API*, SPVM_VALUE*) = api->get_sub_native_address(api, sub_id);

      SPVM_API_OBJECT* return_value_native = (*native_address)(api, (SPVM_VALUE*)call_stack);
      return_value.object_value = return_value_native;
      
      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      goto label_SPVM_BYTECODE_C_CODE_RETURN_OBJECT;
    }
  }
  // Call normal sub
  else {
    bytecode_index = api->get_sub_bytecode_base(api, sub_id);
  }
  
  while (1) {
    
    switch (SPVM_INFO_BYTECODES[bytecode_index]) {
      case SPVM_BYTECODE_C_CODE_NOP:
        abort();
      case SPVM_BYTECODE_C_CODE_BOOL_BYTE:
        condition_flag = !!call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value;
        
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_BOOL_SHORT:
        condition_flag = !!call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value;
        
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_BOOL_INT:
        condition_flag = !!call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value;
        
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_BOOL_LONG:
        condition_flag = !!call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value;
        
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_BOOL_FLOAT:
        condition_flag = !!call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value;
        
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_BOOL_DOUBLE:
        condition_flag = !!call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value;
        
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_BOOL_OBJECT:
        condition_flag = !!call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_IS_UNDEF:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value == NULL;
        
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_IS_NOT_UNDEF:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value != NULL;
        
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_EQ_BYTE:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value == call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_EQ_SHORT:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value == call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_EQ_INT:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value == call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_EQ_LONG:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value == call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_EQ_FLOAT:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value == call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_EQ_DOUBLE:
      
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value == call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_EQ_OBJECT:
      
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value == call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NE_BYTE:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value != call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NE_SHORT:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value != call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NE_INT:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value != call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NE_LONG:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value != call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NE_FLOAT:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value != call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NE_DOUBLE:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value != call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NE_OBJECT:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value != call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GT_BYTE:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value > call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GT_SHORT:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value > call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GT_INT:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value > call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GT_LONG:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value > call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GT_FLOAT:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value > call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GT_DOUBLE:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value > call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GE_BYTE:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value >= call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GE_SHORT:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value >= call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GE_INT:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value >= call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GE_LONG:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value >= call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GE_FLOAT:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value >= call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GE_DOUBLE:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value >= call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LT_BYTE:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value < call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LT_SHORT:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value < call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LT_INT:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value < call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LT_LONG:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value < call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LT_FLOAT:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value < call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LT_DOUBLE:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value < call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LE_BYTE:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value <= call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LE_SHORT:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value <= call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LE_INT:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value <= call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LE_LONG:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value <= call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LE_FLOAT:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value <= call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LE_DOUBLE:
        condition_flag = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value <= call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_ADD_BYTE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value + call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_ADD_SHORT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value + call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_ADD_INT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value + call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_ADD_LONG:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value + call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_ADD_FLOAT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value + call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].float_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_ADD_DOUBLE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value + call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].double_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_SUBTRACT_BYTE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value - call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_SUBTRACT_SHORT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value - call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_SUBTRACT_INT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value - call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_SUBTRACT_LONG:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value - call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_SUBTRACT_FLOAT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value - call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].float_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_SUBTRACT_DOUBLE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value - call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].double_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_MULTIPLY_BYTE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value * call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_MULTIPLY_SHORT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value * call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_MULTIPLY_INT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value * call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_MULTIPLY_LONG:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value * call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_MULTIPLY_FLOAT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value * call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].float_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_MULTIPLY_DOUBLE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value * call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].double_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_DIVIDE_BYTE:
        if (call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value == 0) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division (byte / byte)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
            = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value / call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
          bytecode_index += 4;
          break;
        }
      case SPVM_BYTECODE_C_CODE_DIVIDE_SHORT:
        if (call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value == 0) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division (short / short)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
            = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value / call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
          bytecode_index += 4;
          break;
        }
      case SPVM_BYTECODE_C_CODE_DIVIDE_INT:
        if (call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value == 0) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division (int / int)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
            = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value / call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
          bytecode_index += 4;
          break;
        }
      case SPVM_BYTECODE_C_CODE_DIVIDE_LONG:
        if (call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value == 0) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division (long / long)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
            = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value / call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
          bytecode_index += 4;
          break;
        }
      case SPVM_BYTECODE_C_CODE_DIVIDE_FLOAT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value / call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].float_value;
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_DIVIDE_DOUBLE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value / call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].double_value;
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REMAINDER_BYTE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value % call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REMAINDER_SHORT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value % call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REMAINDER_INT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value % call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REMAINDER_LONG:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value % call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REMAINDER_FLOAT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value
          = (float)fmod((double)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value, call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].float_value);
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REMAINDER_DOUBLE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value
          = fmod(call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value, call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].double_value);
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_LEFT_SHIFT_BYTE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value << call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_LEFT_SHIFT_SHORT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value << call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_LEFT_SHIFT_INT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value << call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_LEFT_SHIFT_LONG:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value << call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_BYTE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value >> call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_SHORT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value >> call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_INT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value >> call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_LONG:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value >> call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_BYTE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = (int8_t)((uint8_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value >> call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value);
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_SHORT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = (int16_t)((uint16_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value >> call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value);
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_INT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = (int32_t)((uint32_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value >> call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value);
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_LONG:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = (int64_t)((uint64_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value >> call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value);
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_AND_BYTE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value & call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_AND_SHORT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value & call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_AND_INT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value & call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_AND_LONG:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value & call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_OR_BYTE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value | call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_OR_SHORT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value | call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_OR_INT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value | call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_OR_LONG:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value | call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_XOR_BYTE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value ^ call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_XOR_SHORT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value ^ call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_XOR_INT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value ^ call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_XOR_LONG:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value ^ call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_NEGATE_BYTE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value = -call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NEGATE_SHORT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value = -call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NEGATE_INT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = -call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NEGATE_LONG:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = -call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NEGATE_FLOAT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value = -call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NEGATE_DOUBLE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value = -call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_COMPLEMENT_BYTE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value = ~call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_COMPLEMENT_SHORT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value = ~call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_COMPLEMENT_INT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = ~call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_COMPLEMENT_LONG:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = ~call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_INC_BYTE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value += (int8_t)(SPVM_INFO_BYTECODES[bytecode_index + 2]);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_INC_SHORT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value += (int16_t)(SPVM_INFO_BYTECODES[bytecode_index + 2]);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_INC_INT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value += (int32_t)(SPVM_INFO_BYTECODES[bytecode_index + 2]);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_INC_LONG:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value += (int64_t)(SPVM_INFO_BYTECODES[bytecode_index + 2]);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LOAD_CONSTANT:
        memcpy(&call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]], &SPVM_INFO_CONSTANT_POOL[SPVM_INFO_BYTECODES[bytecode_index + 2]], sizeof(int32_t));
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LOAD_CONSTANT2:
        memcpy(&call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]], &SPVM_INFO_CONSTANT_POOL[SPVM_INFO_BYTECODES[bytecode_index + 2]], sizeof(int64_t));
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_LONG:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = (int64_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_FLOAT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value = (float)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_DOUBLE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value = (double)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_INT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = (int32_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_FLOAT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value = (float)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_DOUBLE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value = (double)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_INT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = (int32_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_LONG:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = (int64_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_DOUBLE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value = (double)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_INT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = (int32_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_LONG:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = (int64_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_FLOAT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value = (float)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_BYTE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value = (int8_t)(call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_SHORT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value = (int16_t)(call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_INT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = (int32_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_INT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = (int32_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_LONG:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = (int64_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_FLOAT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value = (float)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_DOUBLE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value = (double)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_BYTE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value = (int8_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_LONG:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = (int64_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_FLOAT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value = (float)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_DOUBLE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value = (double)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_BYTE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value = (int8_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_SHORT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value = (int16_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_BYTE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value = (int8_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_SHORT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value = (int16_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_BYTE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value = (int8_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_SHORT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value = (int16_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_SHORT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value = (int16_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_BYTE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_SHORT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_INT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_LONG:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_FLOAT:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_DOUBLE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        bytecode_index += 3;
        break;
      
      /* TODO */
      case SPVM_BYTECODE_C_CODE_UNDEF:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = NULL;
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_BYTE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t index = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "BYTE_ARRAY must not be undef(BYTE_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(BYTE_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
              = *(int8_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int8_t) * index);
            
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_SHORT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t index = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "SHORT_ARRAY must not be undef(SHORT_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(SHORT_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
              = *(int16_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int16_t) * index);
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_INT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t index = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "INT_ARRAY must not be undef(INT_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(INT_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int32_t) * index);
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_LONG: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t index = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "LONG_ARRAY must not be undef(LONG_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(LONG_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = *(int64_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int64_t) * index);
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_FLOAT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t index = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "FLOAT_ARRAY must not be undef(FLOAT_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(FLOAT_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value = *(float*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(float) * index);
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_DOUBLE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t index = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "DOUBLE_ARRAY must not be undef(DOUBLE_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(DOUBLE_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value = *(double*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(double) * index);
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_OBJECT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t index = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "OBJECT_ARRAY must not be undef(OBJECT_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(OBJECT_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]] = *(SPVM_VALUE*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_VALUE) * index);
            
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_BYTE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t index = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "BYTE_ARRAY must not be undef(BYTE_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(BYTE_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            *(int8_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int8_t) * index) = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_SHORT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t index = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "SHORT_ARRAY must not be undef(SHORT_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(SHORT_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            *(int16_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int16_t) * index) = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_INT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t index = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "INT_ARRAY must not be undef(INT_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(INT_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int32_t) * index) = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_LONG: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t index = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "LONG_ARRAY must not be undef(LONG_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(LONG_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            *(int64_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int64_t) * index) = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_FLOAT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t index = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "FLOAT_ARRAY must not be undef(FLOAT_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(FLOAT_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            *(float*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(float) * index) = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].float_value;
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_DOUBLE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t index = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "DOUBLE_ARRAY must not be undef(DOUBLE_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(DOUBLE_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            *(double*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(double) * index) = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].double_value;
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_OBJECT: {
        
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t index = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "OBJECT_ARRAY must not be undef(OBJECT_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(OBJECT_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            SPVM_API_OBJECT** object_address = (SPVM_API_OBJECT**)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_VALUE) * index);
            
            // Decrement old object reference count
            if (*object_address != NULL) {
              api->dec_ref_count(api, *object_address);
            }
            
            // Store address
            *object_address = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].object_value;

            // Increment new object reference count
            if (*object_address != NULL) {
              api->inc_ref_count(api, *object_address);
            }
            
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_MOVE:
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]] = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]];
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_INC_REF_COUNT: {
        // Increment new value reference count
        if (call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value != NULL) {
          api->inc_ref_count(api, call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value);
        }

        bytecode_index += 2;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_DEC_REF_COUNT: {
        // Decrement reference count
        if (call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value != NULL) {
          api->dec_ref_count(api, call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value);
        }
        
        bytecode_index += 2;

        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_OBJECT: {
        // Get subroutine ID
        int32_t type_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        
        SPVM_API_OBJECT* object = api->new_object(api, type_id);
        
        // Push object
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = (SPVM_API_OBJECT*)object;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_BYTE_ARRAY: {
        
        // length
        int32_t length = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        SPVM_API_OBJECT* object = api->new_byte_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        // Set array
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = object;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_SHORT_ARRAY: {
        
        // length
        int32_t length = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        SPVM_API_OBJECT* object = api->new_short_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        // Set array
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = object;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_INT_ARRAY: {
        
        // length
        int32_t length = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        SPVM_API_OBJECT* object = api->new_int_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        // Set array
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = object;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_LONG_ARRAY: {
        
        // length
        int32_t length = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        SPVM_API_OBJECT* object = api->new_long_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        // Set array
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = object;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_FLOAT_ARRAY: {
        
        // length
        int32_t length = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        SPVM_API_OBJECT* object = api->new_float_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        // Set array
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = object;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_DOUBLE_ARRAY: {
        
        // length
        int32_t length = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        SPVM_API_OBJECT* object = api->new_double_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        // Set array
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = object;

        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_OBJECT_ARRAY: {
        int32_t element_type_id = SPVM_INFO_BYTECODES[bytecode_index + 1];
        
        // length
        int32_t length = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        SPVM_API_OBJECT* object = api->new_object_array(api, element_type_id, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        // Set object
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = object;

        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_STRING: {
        int32_t name_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        
        SPVM_API_OBJECT* string = api->new_string(api, (char*)&SPVM_INFO_CONSTANT_POOL[name_id + 1], SPVM_INFO_CONSTANT_POOL[name_id]);

        // Set string
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = string;

        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LENGTH:
        if (call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value == NULL) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Can't get array length of undef value.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = *(int32_t*)((intptr_t)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET);
          bytecode_index += 3;
          break;
        }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_BYTE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 3];

        int8_t value = api->get_byte_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value = value;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_SHORT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 3];

        int16_t value = api->get_short_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value = value;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_INT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 3];

        int32_t value = api->get_int_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = value;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_LONG: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 3];

        int64_t value = api->get_long_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = value;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_FLOAT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 3];

        float value = api->get_float_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value = value;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_DOUBLE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 3];

        double value = api->get_double_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value = value;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_OBJECT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 3];
        
        SPVM_API_OBJECT* value = api->get_object_field(api, object, field_id);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = value;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_WEAKEN_FIELD_OBJECT: {
        
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        
        api->weaken_object_field(api, object, field_id);

        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_BYTE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        int8_t value = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        api->set_byte_field(api, object, field_id, value);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_SHORT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        int16_t value = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        api->set_short_field(api, object, field_id, value);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_INT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        int32_t value = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        api->set_int_field(api, object, field_id, value);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_LONG: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        int64_t value = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        api->set_long_field(api, object, field_id, value);

        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_FLOAT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        float value = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].float_value;
        
        api->set_float_field(api, object, field_id, value);

        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_DOUBLE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        double value = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].double_value;
        
        api->set_double_field(api, object, field_id, value);

        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_OBJECT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        SPVM_API_OBJECT* value = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].object_value;
        
        api->set_object_field(api, object, field_id, value);

        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_STRING: {
        SPVM_API_OBJECT* string1 = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        SPVM_API_OBJECT* string2 = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].object_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_string(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = string3;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_BYTE: {
        SPVM_API_OBJECT* string1 = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int8_t string2 = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_byte(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = string3;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_SHORT: {
        SPVM_API_OBJECT* string1 = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int16_t string2 = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_short(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = string3;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_INT: {
        SPVM_API_OBJECT* string1 = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t string2 = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_int(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = string3;

        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_LONG: {
        SPVM_API_OBJECT* string1 = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int64_t string2 = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_long(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = string3;

        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_FLOAT: {
        SPVM_API_OBJECT* string1 = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        float string2 = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].float_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_float(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = string3;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_DOUBLE: {
        SPVM_API_OBJECT* string1 = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        double string2 = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 3]].double_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_double(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = string3;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_LOAD_PACKAGE_VAR: {
        // Get subroutine ID
        int32_t package_var_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]] = SPVM_INFO_PACKAGE_VARS[package_var_id];
        
        bytecode_index += 3;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_LOAD_PACKAGE_VAR_OBJECT: {
        // Get subroutine ID
        int32_t package_var_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = SPVM_INFO_PACKAGE_VARS[package_var_id].object_value;
        
        bytecode_index += 3;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_STORE_PACKAGE_VAR: {
        // Get subroutine ID
        int32_t package_var_id = SPVM_INFO_BYTECODES[bytecode_index + 1];

        SPVM_INFO_PACKAGE_VARS[package_var_id] = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]];

        bytecode_index += 3;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_STORE_PACKAGE_VAR_OBJECT: {
        // Get subroutine ID
        int32_t package_var_id = SPVM_INFO_BYTECODES[bytecode_index + 1];
        
        // Decrement reference count
        if (SPVM_INFO_PACKAGE_VARS[package_var_id].object_value != NULL) {
          api->dec_ref_count(api, SPVM_INFO_PACKAGE_VARS[package_var_id].object_value);
        }
        
        // Store object
        SPVM_INFO_PACKAGE_VARS[package_var_id].object_value = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        
        // Increment new value reference count
        if (SPVM_INFO_PACKAGE_VARS[package_var_id].object_value != NULL) {
          api->inc_ref_count(api, SPVM_INFO_PACKAGE_VARS[package_var_id].object_value);
        }

        bytecode_index += 3;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_PUSH_CATCH_EXCEPTION: {
        // Next operation
        int16_t jump_offset_abs = SPVM_INFO_BYTECODES[bytecode_index + 1];
        
        catch_exception_stack_top++;
        catch_exception_stack[catch_exception_stack_top] = jump_offset_abs;
        
        bytecode_index += 2;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_POP_CATCH_EXCEPTION: {
        catch_exception_stack_top--;
        
        bytecode_index++;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_LOAD_EXCEPTION_VAR: {
        call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = (SPVM_API_OBJECT*)api->get_exception(api);
        
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_STORE_EXCEPTION_VAR: {
        
        api->set_exception(api, (SPVM_API_OBJECT*)call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value);
        
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CURRENT_LINE:
        current_line = SPVM_INFO_BYTECODES[bytecode_index + 1];
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_CALL_SUB: {
        // Get subroutine ID
        int32_t call_sub_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        
        int32_t args_length = api->get_sub_args_length(api, call_sub_id);

        operand_stack_top -= args_length;
        
        SPVM_VALUE args[255];
        {
          int32_t i;
          for (i = 0; i < args_length; i++) {
            int32_t var_index = call_stack[operand_stack_top + 1 + i].int_value;
            args[i] = call_stack[var_index];
          }
        }
        
        // Call subroutine
        SPVM_VALUE call_sub_return_value = SPVM_RUNTIME_call_sub(api, call_sub_id, args);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]] = call_sub_return_value;
          
          // Next operation
          bytecode_index += 3 + (SPVM_INFO_DEBUG * 2);
          
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_CALL_OBJECT_SUB: {
        // Get subroutine ID
        int32_t call_sub_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        
        int32_t args_length = api->get_sub_args_length(api, call_sub_id);
        
        operand_stack_top -= args_length;
        
        SPVM_VALUE args[255];
        {
          int32_t i;
          for (i = 0; i < args_length; i++) {
            int32_t var_index = call_stack[operand_stack_top + 1 + i].int_value;
            args[i] = call_stack[var_index];
          }
        }
        
        // Call subroutine
        SPVM_VALUE call_sub_return_value = SPVM_RUNTIME_call_sub(api, call_sub_id, args);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          
          call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]] = call_sub_return_value;
          
          // Next operation
          bytecode_index += 3 + (SPVM_INFO_DEBUG * 2);
          
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_CALL_VOID_SUB: {
        // Get subroutine ID
        int32_t call_sub_id = SPVM_INFO_BYTECODES[bytecode_index + 1];
        
        int32_t args_length = api->get_sub_args_length(api, call_sub_id);
        
        operand_stack_top -= args_length;
        
        SPVM_VALUE args[255];
        {
          int32_t i;
          for (i = 0; i < args_length; i++) {
            int32_t var_index = call_stack[operand_stack_top + 1 + i].int_value;
            args[i] = call_stack[var_index];
          }
        }
        
        // Call subroutine
        SPVM_RUNTIME_call_sub(api, call_sub_id, args);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          // Next operation
          bytecode_index += 2 + (SPVM_INFO_DEBUG * 2);
          
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_RETURN_BYTE:
      case SPVM_BYTECODE_C_CODE_RETURN_SHORT:
      case SPVM_BYTECODE_C_CODE_RETURN_INT:
      case SPVM_BYTECODE_C_CODE_RETURN_LONG:
      case SPVM_BYTECODE_C_CODE_RETURN_FLOAT:
      case SPVM_BYTECODE_C_CODE_RETURN_DOUBLE:
      {
        // Get return value
        return_value = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]];

        label_SPVM_BYTECODE_C_CODE_RETURN_BYTE:
        label_SPVM_BYTECODE_C_CODE_RETURN_SHORT:
        label_SPVM_BYTECODE_C_CODE_RETURN_INT:
        label_SPVM_BYTECODE_C_CODE_RETURN_LONG:
        label_SPVM_BYTECODE_C_CODE_RETURN_FLOAT:
        label_SPVM_BYTECODE_C_CODE_RETURN_DOUBLE:
        {
        
          
          {
            int32_t i;
            for (i = 0; i < SPVM_INFO_SUB_XXX_OBJECT_MYS_LENGTH; i++) {
              int32_t my_var_index = SPVM_INFO_CONSTANT_POOL[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
              SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[my_var_index].object_value;
              
              if (object != NULL) {
                api->dec_ref_count(api, object);
              }
            }
          }
          
          api->dec_ref_count(api, call_stack_array);
          
          // No exception
          api->set_exception(api, NULL);
          
          return return_value;
        }
      }
      case SPVM_BYTECODE_C_CODE_RETURN_OBJECT: {

        return_value = call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]];

        label_SPVM_BYTECODE_C_CODE_RETURN_OBJECT: {
        
          
          // Increment ref count of return value not to release by decrement
          if (return_value.object_value != NULL) {
            api->inc_ref_count(api, return_value.object_value);
          }
          
          // Decrement object my vars reference count
          {
            int32_t i;
            for (i = 0; i < SPVM_INFO_SUB_XXX_OBJECT_MYS_LENGTH; i++) {
              int32_t my_var_index = SPVM_INFO_CONSTANT_POOL[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
              SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[my_var_index].object_value;
              
              if (object != NULL) {
                api->dec_ref_count(api, object);
              }
            }
          }

          // Decrement ref count of return value
          if (return_value.object_value != NULL) {
            api->dec_ref_count_only(api, return_value.object_value);
          }
          
          api->dec_ref_count(api, call_stack_array);
          
          // No exception
          api->set_exception(api, NULL);
          
          return return_value;
        }
      }
      case SPVM_BYTECODE_C_CODE_RETURN_VOID: {

        label_SPVM_BYTECODE_C_CODE_RETURN_VOID: {

          memset(&return_value, 0, sizeof(SPVM_VALUE));
          
          // Decrement object my vars reference count
          {
            int32_t i;
            for (i = 0; i < SPVM_INFO_SUB_XXX_OBJECT_MYS_LENGTH; i++) {
              int32_t my_var_index = SPVM_INFO_CONSTANT_POOL[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
              SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[my_var_index].object_value;
              
              if (object != NULL) {
                api->dec_ref_count(api, object);
              }
            }
          }
          
          api->dec_ref_count(api, call_stack_array);
          
          // No exception
          api->set_exception(api, NULL);

          return return_value;
        }
      }
      case SPVM_BYTECODE_C_CODE_CROAK: {
        
        label_SPVM_BYTECODE_C_CODE_CROAK:
        
        // Catch exception
        if (catch_exception_stack_top > -1) {
          
          int32_t jump_offset_abs = catch_exception_stack[catch_exception_stack_top];
          catch_exception_stack_top--;
          
          bytecode_index = api->get_sub_bytecode_base(api, sub_id) + jump_offset_abs;
          
          break;
        }
        
        {
          int32_t i;
          for (i = 0; i < SPVM_INFO_SUB_XXX_OBJECT_MYS_LENGTH; i++) {
            int32_t my_var_index = SPVM_INFO_CONSTANT_POOL[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
            SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[my_var_index].object_value;
            
            if (object != NULL) {
              api->dec_ref_count(api, object);
            }
          }
        }
        
        // Sub name
        int32_t sub_name_id = api->get_sub_name_id(api, sub_id);
        const char* sub_name = (char*)&SPVM_INFO_CONSTANT_POOL[sub_name_id + 1];
        
        // File name
        int32_t file_name_id = api->get_sub_file_name_id(api, sub_id);
        const char* file_name = (char*)&SPVM_INFO_CONSTANT_POOL[file_name_id + 1];
        
        // stack trace strings
        const char* from = "\n  from ";
        const char* at = "() at ";

        // Exception
        SPVM_API_OBJECT* exception = api->get_exception(api);
        char* exception_chars = api->get_string_chars(api, exception);
        int32_t exception_length = api->get_string_length(api, exception);
        
        // Total string length
        int32_t total_length = 0;
        total_length += exception_length;
        total_length += strlen(from);
        total_length += strlen(sub_name);
        total_length += strlen(at);
        total_length += strlen(file_name);

        const char* line = " line ";
        char line_str[20];
        
        if (SPVM_INFO_DEBUG) {
          sprintf(line_str, "%" PRId32, current_line);
          total_length += strlen(line);
          total_length += strlen(line_str);
        }
        
        // Create exception message
        SPVM_API_OBJECT* new_exception = api->new_string(api, NULL, total_length);
        char* new_exception_chars = api->get_string_chars(api, new_exception);
        
        memcpy(
          (void*)(new_exception_chars),
          (void*)(exception_chars),
          exception_length
        );
        if (SPVM_INFO_DEBUG) {
          sprintf(
            new_exception_chars + exception_length,
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
            new_exception_chars + exception_length,
            "%s%s%s%s",
            from,
            sub_name,
            at,
            file_name
          );
        }
        
        // Set exception
        api->set_exception(api, new_exception);
        
        memset(&return_value, 0, sizeof(SPVM_VALUE));
        
        api->dec_ref_count(api, call_stack_array);
        
        return return_value;
      }
      case SPVM_BYTECODE_C_CODE_IF_EQ_ZERO: {
        int32_t success = condition_flag == 0;
        bytecode_index += success * SPVM_INFO_BYTECODES[bytecode_index + 1] + (~success & 1) * 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_IF_NE_ZERO: {
        
        int32_t success = condition_flag != 0;
        bytecode_index += success * SPVM_INFO_BYTECODES[bytecode_index + 1] + (~success & 1) * 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_GOTO:
        bytecode_index += SPVM_INFO_BYTECODES[bytecode_index + 1];
        break;
      case SPVM_BYTECODE_C_CODE_TABLE_SWITCH: {
        // default offset
        int32_t default_offset = SPVM_INFO_BYTECODES[bytecode_index + 2];
        
        // min
        int32_t min = SPVM_INFO_BYTECODES[bytecode_index + 3];
        
        // max
        int32_t max = SPVM_INFO_BYTECODES[bytecode_index + 4];
        
        if (call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value >= min && call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value <= max) {
          int32_t branch_offset
            = *(int32_t*)((&SPVM_INFO_BYTECODES[bytecode_index + 5]) + (call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value - min));
          bytecode_index += branch_offset;
        }
        else {
          bytecode_index += default_offset;
        }
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_LOOKUP_SWITCH: {

        /*
        1  default
        5  npare
        9  match  13 branch // min
        17 match 21 branch
        25 match 29 branch // max
        */
        
        // default offset
        int32_t default_offset = SPVM_INFO_BYTECODES[bytecode_index + 2];
        
        // npare
        int32_t pair_count = SPVM_INFO_BYTECODES[bytecode_index + 3];
        
        // min
        int32_t min = SPVM_INFO_BYTECODES[bytecode_index + 4];
        
        // max
        int32_t max = SPVM_INFO_BYTECODES[bytecode_index + 4 + (pair_count - 1) * 2];
        
        if (call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value >= min && call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value <= max) {
          // 2 branch searching
          int32_t cur_min_pos = 0;
          int32_t cur_max_pos = pair_count - 1;

          while (1) {
            if (cur_max_pos < cur_min_pos) {
              bytecode_index += default_offset;
              break;
            }
            int32_t cur_half_pos = cur_min_pos + (cur_max_pos - cur_min_pos) / 2;
            int32_t cur_half = SPVM_INFO_BYTECODES[bytecode_index + 4 + (cur_half_pos * 2)];
            
            if (call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value > cur_half) {
              cur_min_pos = cur_half_pos + 1;
            }
            else if (call_stack[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value < cur_half) {
              cur_max_pos = cur_half_pos - 1;
            }
            else {
              int32_t branch_offset = SPVM_INFO_BYTECODES[bytecode_index + 4 + (cur_half_pos * 2) + 1];
              bytecode_index += branch_offset;
              break;
            }
          }
        }
        else {
          bytecode_index += default_offset;
        }
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_PUSH_ARG:
        operand_stack_top++;
        call_stack[operand_stack_top].int_value = SPVM_INFO_BYTECODES[bytecode_index + 1];
        
        bytecode_index += 2;
        break;
    }
  }
}
