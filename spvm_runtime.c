#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stddef.h>

#include "spvm_api.h"
#include "spvm_runtime_api.h"
#include "spvm_bytecode.h"
#include "spvm_object.h"
#include "spvm_type.h"
#include "spvm_value.h"
#include "spvm_runtime.h"
#include "spvm_constant_pool.h"
#include "spvm_constant_pool_sub.h"
#include "spvm_constant_pool_field.h"
#include "spvm_constant_pool_type.h"

#define SPVM_INFO_OBJECT_HEADER_BYTE_SIZE sizeof(SPVM_OBJECT)
#define SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET ((int32_t)offsetof(SPVM_OBJECT, length))
#define SPVM_INFO_OBJECT_REF_COUNT_BYTE_OFFSET ((int32_t)offsetof(SPVM_OBJECT, ref_count))
#define SPVM_INFO_RUNTIME_EXCEPTION_BYTE_OFFSET ((int32_t)offsetof(SPVM_RUNTIME, exception))
#define SPVM_INFO_TYPE_CODE_VOID (SPVM_TYPE_C_CODE_VOID)
#define SPVM_INFO_TYPE_CODE_BYTE (SPVM_TYPE_C_CODE_BYTE)
#define SPVM_INFO_TYPE_CODE_SHORT (SPVM_TYPE_C_CODE_SHORT)
#define SPVM_INFO_TYPE_CODE_INT (SPVM_TYPE_C_CODE_INT)
#define SPVM_INFO_TYPE_CODE_LONG (SPVM_TYPE_C_CODE_LONG)
#define SPVM_INFO_TYPE_CODE_FLOAT (SPVM_TYPE_C_CODE_FLOAT)
#define SPVM_INFO_TYPE_CODE_DOUBLE (SPVM_TYPE_C_CODE_DOUBLE)

#define SPVM_INLINE_INC_REF_COUNT(object) ((*(int32_t*)((intptr_t)object + SPVM_INFO_OBJECT_REF_COUNT_BYTE_OFFSET))++)
#define SPVM_INLINE_DEC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + SPVM_INFO_OBJECT_REF_COUNT_BYTE_OFFSET))--)
#define SPVM_INLINE_GET_EXCEPTION() (*(SPVM_API_OBJECT**)((intptr_t)SPVM_INFO_RUNTIME + SPVM_INFO_RUNTIME_EXCEPTION_BYTE_OFFSET))
#define SPVM_INLINE_SET_EXCEPTION_NULL() \
  do { \
    if ((*(SPVM_API_OBJECT**)((intptr_t)SPVM_INFO_RUNTIME + SPVM_INFO_RUNTIME_EXCEPTION_BYTE_OFFSET)) != NULL) { \
      api->dec_ref_count(api, (*(SPVM_API_OBJECT**)((intptr_t)SPVM_INFO_RUNTIME + SPVM_INFO_RUNTIME_EXCEPTION_BYTE_OFFSET))); \
    } \
    (*(SPVM_API_OBJECT**)((intptr_t)SPVM_INFO_RUNTIME + SPVM_INFO_RUNTIME_EXCEPTION_BYTE_OFFSET)) = NULL; \
  } \
  while (0) \

#define SPVM_INLINE_ISWEAK(object) ((intptr_t)object & 1)


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
  
  // Subroutine name id
  int32_t SPVM_INFO_SUB_XXX_ABS_NAME_ID = SPVM_INFO_CONSTANT_POOL_SUB_XXX->abs_name_id;
  
  // Subroutine file name id
  int32_t SPVM_INFO_SUB_XXX_FILE_NAME_ID = SPVM_INFO_CONSTANT_POOL_SUB_XXX->file_name_id;
  
  // Subroutine return type id
  int32_t SPVM_INFO_SUB_XXX_RETURN_TYPE_ID = SPVM_INFO_CONSTANT_POOL_SUB_XXX->return_type_id;
  
  // Subroutine is native
  int32_t SPVM_INFO_SUB_XXX_IS_NATIVE = SPVM_INFO_CONSTANT_POOL_SUB_XXX->is_native;
  
  // Subroutine object args length
  int32_t SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH = SPVM_INFO_CONSTANT_POOL_SUB_XXX->object_args_length;

  // Subroutine object args length
  int32_t SPVM_INFO_SUB_XXX_OBJECT_ARGS_BASE = SPVM_INFO_CONSTANT_POOL_SUB_XXX->object_args_base;
  
  // Bytecodes
  int32_t* SPVM_INFO_BYTECODES = SPVM_INFO_RUNTIME->bytecodes;
  
  // Bytecode base
  int32_t SPVM_INFO_SUB_XXX_BYTECODE_BASE = SPVM_INFO_CONSTANT_POOL_SUB_XXX->bytecode_base;
  
  // Args length
  int32_t args_length = SPVM_INFO_CONSTANT_POOL_SUB_XXX->args_length;
  
  // Lexical varialbe length
  int32_t SPVM_INFO_SUB_XXX_MYS_LENGTH = SPVM_INFO_CONSTANT_POOL_SUB_XXX->mys_length;
  
  // Native address
  void* SPVM_INFO_SUB_XXX_NATIVE_ADDRESS = SPVM_INFO_CONSTANT_POOL_SUB_XXX->native_address;
  
  // Constant pool type
  SPVM_CONSTANT_POOL_TYPE* SPVM_INFO_SUB_XXX_RETURN_TYPE = (SPVM_CONSTANT_POOL_TYPE*)&SPVM_INFO_CONSTANT_POOL[SPVM_INFO_SUB_XXX_RETURN_TYPE_ID];

  // Return type code
  int32_t SPVM_INFO_SUB_XXX_RETURN_TYPE_CODE = SPVM_INFO_SUB_XXX_RETURN_TYPE->code;
  
  // Call stack
  SPVM_VALUE vars[65535];
  memset(vars, 0, sizeof(SPVM_VALUE) * SPVM_INFO_SUB_XXX_MYS_LENGTH);
  
  // Eval stack
  int32_t eval_stack[255];
  
  // Eval stack top
  int32_t eval_stack_top = -1;
  
  // Call subroutine argument stack
  SPVM_VALUE call_sub_arg_stack[255];
  
  // Call subroutine argument stack top
  int32_t call_sub_arg_stack_top = -1;
  
  // Current line
  int32_t current_line = 0;
  
  // Condition flag
  register int32_t condition_flag = 0;

  // Bytecode index
  register int32_t bytecode_index = 0;
  
  // Return value
  SPVM_VALUE return_value;
  memset(&return_value, 0, sizeof(SPVM_VALUE));
  
  // Copy arguments
  memcpy(vars, args, args_length * sizeof(SPVM_VALUE));
  
  // If arg is object, increment reference count
  {
    int32_t i;
    for (i = 0; i < SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH; i++) {
      int32_t arg_index = SPVM_INFO_CONSTANT_POOL[SPVM_INFO_SUB_XXX_OBJECT_ARGS_BASE + i];
      SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[arg_index].object_value;
      if (object != NULL) {
        SPVM_INLINE_INC_REF_COUNT(object);
      }
    }
  }
  
  SPVM_INLINE_SET_EXCEPTION_NULL();

  // Call native sub
  if (SPVM_INFO_SUB_XXX_IS_NATIVE) {
    // Call native subroutine
    if (SPVM_INFO_SUB_XXX_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_VOID) {
      void (*native_address)(SPVM_API*, SPVM_VALUE*) = SPVM_INFO_SUB_XXX_NATIVE_ADDRESS;
      (*native_address)(api, (SPVM_VALUE*)vars);
      
      if (SPVM_INLINE_GET_EXCEPTION()) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      goto label_SPVM_BYTECODE_C_CODE_RETURN_VOID;
    }
    else if (SPVM_INFO_SUB_XXX_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_BYTE) {
      int8_t (*native_address)(SPVM_API*, SPVM_VALUE*) = SPVM_INFO_SUB_XXX_NATIVE_ADDRESS;
      int8_t return_value_native = (*native_address)(api, (SPVM_VALUE*)vars);
      return_value.byte_value = return_value_native;

      if (SPVM_INLINE_GET_EXCEPTION()) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      goto label_SPVM_BYTECODE_C_CODE_RETURN_BYTE;
    }
    else if (SPVM_INFO_SUB_XXX_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_SHORT) {
      int16_t (*native_address)(SPVM_API*, SPVM_VALUE*) = SPVM_INFO_SUB_XXX_NATIVE_ADDRESS;
      int16_t return_value_native = (*native_address)(api, (SPVM_VALUE*)vars);
      return_value.short_value = return_value_native;

      if (SPVM_INLINE_GET_EXCEPTION()) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }

      goto label_SPVM_BYTECODE_C_CODE_RETURN_SHORT;
    }
    else if (SPVM_INFO_SUB_XXX_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_INT) {
        
      int32_t (*native_address)(SPVM_API*, SPVM_VALUE*) = SPVM_INFO_SUB_XXX_NATIVE_ADDRESS;
      
      int32_t return_value_native = (*native_address)(api, (SPVM_VALUE*)vars);
      return_value.int_value = return_value_native;
      
      if (SPVM_INLINE_GET_EXCEPTION()) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      goto label_SPVM_BYTECODE_C_CODE_RETURN_INT;
    }
    else if (SPVM_INFO_SUB_XXX_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_LONG) {
      int64_t (*native_address)(SPVM_API*, SPVM_VALUE*) = SPVM_INFO_SUB_XXX_NATIVE_ADDRESS;
      int64_t return_value_native = (*native_address)(api, (SPVM_VALUE*)vars);
      return_value.long_value = return_value_native;

      if (SPVM_INLINE_GET_EXCEPTION()) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }

      goto label_SPVM_BYTECODE_C_CODE_RETURN_LONG;
    }
    else if (SPVM_INFO_SUB_XXX_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_FLOAT) {
      float (*native_address)(SPVM_API*, SPVM_VALUE*) = SPVM_INFO_SUB_XXX_NATIVE_ADDRESS;
      float return_value_native = (*native_address)(api, (SPVM_VALUE*)vars);
      return_value.float_value = return_value_native;

      if (SPVM_INLINE_GET_EXCEPTION()) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      goto label_SPVM_BYTECODE_C_CODE_RETURN_FLOAT;
    }
    else if (SPVM_INFO_SUB_XXX_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_DOUBLE) {
      double (*native_address)(SPVM_API*, SPVM_VALUE*) = SPVM_INFO_SUB_XXX_NATIVE_ADDRESS;
      double return_value_native = (*native_address)(api, (SPVM_VALUE*)vars);
      return_value.double_value = return_value_native;

      if (SPVM_INLINE_GET_EXCEPTION()) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      goto label_SPVM_BYTECODE_C_CODE_RETURN_DOUBLE;
    }
    else {
      
      SPVM_API_OBJECT* (*native_address)(SPVM_API*, SPVM_VALUE*) = SPVM_INFO_SUB_XXX_NATIVE_ADDRESS;

      SPVM_API_OBJECT* return_value_native = (*native_address)(api, (SPVM_VALUE*)vars);
      return_value.object_value = return_value_native;
      
      if (SPVM_INLINE_GET_EXCEPTION()) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      goto label_SPVM_BYTECODE_C_CODE_RETURN_OBJECT;
    }
  }
  // Call normal sub
  else {
    bytecode_index = SPVM_INFO_SUB_XXX_BYTECODE_BASE;
  }
  
  while (1) {
    
    switch (SPVM_INFO_BYTECODES[bytecode_index]) {
      case SPVM_BYTECODE_C_CODE_NOP:
        abort();
      case SPVM_BYTECODE_C_CODE_BOOL_BYTE:
        condition_flag = !!vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value;
        
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_BOOL_SHORT:
        condition_flag = !!vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value;
        
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_BOOL_INT:
        condition_flag = !!vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value;
        
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_BOOL_LONG:
        condition_flag = !!vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value;
        
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_BOOL_FLOAT:
        condition_flag = !!vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value;
        
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_BOOL_DOUBLE:
        condition_flag = !!vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value;
        
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_BOOL_OBJECT:
        condition_flag = !!vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_IS_UNDEF:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value == NULL;
        
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_IS_NOT_UNDEF:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value != NULL;
        
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_EQ_BYTE:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value == vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_EQ_SHORT:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value == vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_EQ_INT:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value == vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_EQ_LONG:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value == vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_EQ_FLOAT:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value == vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_EQ_DOUBLE:
      
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value == vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_EQ_OBJECT:
      
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value == vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NE_BYTE:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value != vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NE_SHORT:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value != vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NE_INT:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value != vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NE_LONG:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value != vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NE_FLOAT:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value != vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NE_DOUBLE:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value != vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NE_OBJECT:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value != vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GT_BYTE:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value > vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GT_SHORT:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value > vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GT_INT:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value > vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GT_LONG:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value > vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GT_FLOAT:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value > vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GT_DOUBLE:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value > vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GE_BYTE:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value >= vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GE_SHORT:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value >= vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GE_INT:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value >= vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GE_LONG:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value >= vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GE_FLOAT:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value >= vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_GE_DOUBLE:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value >= vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LT_BYTE:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value < vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LT_SHORT:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value < vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LT_INT:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value < vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LT_LONG:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value < vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LT_FLOAT:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value < vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LT_DOUBLE:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value < vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LE_BYTE:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value <= vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LE_SHORT:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value <= vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LE_INT:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value <= vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LE_LONG:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value <= vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LE_FLOAT:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value <= vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LE_DOUBLE:
        condition_flag = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value <= vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_ADD_BYTE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value + vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_ADD_SHORT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value + vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_ADD_INT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value + vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_ADD_LONG:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value + vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_ADD_FLOAT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value + vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].float_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_ADD_DOUBLE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value + vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].double_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_SUBTRACT_BYTE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value - vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_SUBTRACT_SHORT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value - vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_SUBTRACT_INT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value - vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_SUBTRACT_LONG:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value - vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_SUBTRACT_FLOAT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value - vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].float_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_SUBTRACT_DOUBLE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value - vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].double_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_MULTIPLY_BYTE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value * vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_MULTIPLY_SHORT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value * vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_MULTIPLY_INT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value * vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_MULTIPLY_LONG:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value * vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_MULTIPLY_FLOAT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value * vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].float_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_MULTIPLY_DOUBLE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value * vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].double_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_DIVIDE_BYTE:
        if (vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value == 0) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division (byte / byte)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
            = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value / vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
          bytecode_index += 4;
          break;
        }
      case SPVM_BYTECODE_C_CODE_DIVIDE_SHORT:
        if (vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value == 0) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division (short / short)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
            = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value / vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
          bytecode_index += 4;
          break;
        }
      case SPVM_BYTECODE_C_CODE_DIVIDE_INT:
        if (vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value == 0) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division (int / int)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
            = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value / vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
          bytecode_index += 4;
          break;
        }
      case SPVM_BYTECODE_C_CODE_DIVIDE_LONG:
        if (vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value == 0) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division (long / long)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
            = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value / vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
          bytecode_index += 4;
          break;
        }
      case SPVM_BYTECODE_C_CODE_DIVIDE_FLOAT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value / vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].float_value;
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_DIVIDE_DOUBLE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value / vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].double_value;
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REMAINDER_BYTE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value % vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REMAINDER_SHORT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value % vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REMAINDER_INT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value % vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REMAINDER_LONG:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value % vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REMAINDER_FLOAT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value
          = (float)fmod((double)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value, vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].float_value);
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_REMAINDER_DOUBLE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value
          = fmod(vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value, vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].double_value);
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_LEFT_SHIFT_BYTE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value << vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_LEFT_SHIFT_SHORT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value << vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_LEFT_SHIFT_INT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value << vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_LEFT_SHIFT_LONG:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value << vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_BYTE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value >> vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_SHORT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value >> vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_INT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value >> vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_LONG:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value >> vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_BYTE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = (int8_t)((uint8_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value >> vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value);
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_SHORT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = (int16_t)((uint16_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value >> vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value);
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_INT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = (int32_t)((uint32_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value >> vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value);
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_LONG:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = (int64_t)((uint64_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value >> vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value);
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_AND_BYTE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value & vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_AND_SHORT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value & vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_AND_INT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value & vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_AND_LONG:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value & vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_OR_BYTE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value | vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_OR_SHORT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value | vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_OR_INT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value | vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_OR_LONG:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value | vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_XOR_BYTE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value ^ vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_XOR_SHORT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value ^ vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_XOR_INT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value ^ vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_XOR_LONG:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value
          = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value ^ vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        bytecode_index += 4;
        break;
      case SPVM_BYTECODE_C_CODE_NEGATE_BYTE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value = -vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NEGATE_SHORT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value = -vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NEGATE_INT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = -vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NEGATE_LONG:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = -vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NEGATE_FLOAT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value = -vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_NEGATE_DOUBLE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value = -vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_COMPLEMENT_BYTE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value = ~vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_COMPLEMENT_SHORT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value = ~vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_COMPLEMENT_INT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = ~vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_COMPLEMENT_LONG:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = ~vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_INC_BYTE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value += (int8_t)(SPVM_INFO_BYTECODES[bytecode_index + 2]);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_INC_SHORT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value += (int16_t)(SPVM_INFO_BYTECODES[bytecode_index + 2]);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_INC_INT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value += (int32_t)(SPVM_INFO_BYTECODES[bytecode_index + 2]);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_INC_LONG:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value += (int64_t)(SPVM_INFO_BYTECODES[bytecode_index + 2]);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LOAD_CONSTANT:
        memcpy(&vars[SPVM_INFO_BYTECODES[bytecode_index + 1]], &SPVM_INFO_CONSTANT_POOL[SPVM_INFO_BYTECODES[bytecode_index + 2]], sizeof(int32_t));
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_LOAD_CONSTANT2:
        memcpy(&vars[SPVM_INFO_BYTECODES[bytecode_index + 1]], &SPVM_INFO_CONSTANT_POOL[SPVM_INFO_BYTECODES[bytecode_index + 2]], sizeof(int64_t));
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_LONG:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = (int64_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_FLOAT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value = (float)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_DOUBLE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value = (double)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_INT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = (int32_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_FLOAT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value = (float)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_DOUBLE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value = (double)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_INT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = (int32_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_LONG:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = (int64_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_DOUBLE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value = (double)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_INT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = (int32_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_LONG:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = (int64_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_FLOAT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value = (float)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_BYTE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value = (int8_t)(vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_SHORT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value = (int16_t)(vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_INT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = (int32_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_INT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = (int32_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_LONG:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = (int64_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_FLOAT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value = (float)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_DOUBLE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value = (double)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_BYTE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value = (int8_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_LONG:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = (int64_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_FLOAT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value = (float)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_DOUBLE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value = (double)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_BYTE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value = (int8_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_SHORT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value = (int16_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_BYTE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value = (int8_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_SHORT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value = (int16_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_BYTE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value = (int8_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_SHORT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value = (int16_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_SHORT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value = (int16_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_BYTE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].byte_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_SHORT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].short_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_INT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_LONG:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].long_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_FLOAT:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].float_value;
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_DOUBLE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].double_value;
        bytecode_index += 3;
        break;
      
      /* TODO */
      case SPVM_BYTECODE_C_CODE_UNDEF:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = NULL;
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_BYTE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t index = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
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
            vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value
              = *(int8_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int8_t) * index);
            
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_SHORT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t index = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
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
            vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value
              = *(int16_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int16_t) * index);
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_INT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t index = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
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
            vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int32_t) * index);
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_LONG: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t index = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
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
            vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = *(int64_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int64_t) * index);
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_FLOAT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t index = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
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
            vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value = *(float*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(float) * index);
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_DOUBLE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t index = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
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
            vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value = *(double*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(double) * index);
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_OBJECT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t index = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
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
            vars[SPVM_INFO_BYTECODES[bytecode_index + 1]] = *(SPVM_VALUE*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_VALUE) * index);
            
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_BYTE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t index = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
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
            *(int8_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int8_t) * index) = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_SHORT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t index = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
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
            *(int16_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int16_t) * index) = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_INT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t index = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
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
            *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int32_t) * index) = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_LONG: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t index = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
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
            *(int64_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int64_t) * index) = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_FLOAT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t index = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
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
            *(float*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(float) * index) = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].float_value;
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_DOUBLE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t index = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
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
            *(double*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(double) * index) = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].double_value;
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_OBJECT: {
        
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t index = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
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
            *object_address = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].object_value;

            // Increment new object reference count
            if (*object_address != NULL) {
              SPVM_INLINE_INC_REF_COUNT(*object_address);
            }
            
            bytecode_index += 4;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_MOVE:
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]] = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]];
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_INC_REF_COUNT: {
        // Increment new value reference count
        if (vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value != NULL) {
          SPVM_INLINE_INC_REF_COUNT(vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value);
        }

        bytecode_index += 2;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_DEC_REF_COUNT: {
        // Decrement reference count
        if (vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value != NULL) {
          api->dec_ref_count(api, vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value);
        }
        
        bytecode_index += 2;

        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_OBJECT: {
        // Get subroutine ID
        int32_t type_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        
        SPVM_API_OBJECT* object = api->new_object(api, type_id);
        
        // Push object
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = (SPVM_API_OBJECT*)object;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_BYTE_ARRAY: {
        
        // length
        int32_t length = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        SPVM_API_OBJECT* object = api->new_byte_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        // Set array
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = object;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_SHORT_ARRAY: {
        
        // length
        int32_t length = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        SPVM_API_OBJECT* object = api->new_short_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        // Set array
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = object;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_INT_ARRAY: {
        
        // length
        int32_t length = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        SPVM_API_OBJECT* object = api->new_int_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        // Set array
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = object;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_LONG_ARRAY: {
        
        // length
        int32_t length = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        SPVM_API_OBJECT* object = api->new_long_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        // Set array
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = object;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_FLOAT_ARRAY: {
        
        // length
        int32_t length = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        SPVM_API_OBJECT* object = api->new_float_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        // Set array
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = object;
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_DOUBLE_ARRAY: {
        
        // length
        int32_t length = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].int_value;
        
        SPVM_API_OBJECT* object = api->new_double_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        // Set array
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = object;

        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_OBJECT_ARRAY: {
        int32_t element_type_id = SPVM_INFO_BYTECODES[bytecode_index + 1];
        
        // length
        int32_t length = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        SPVM_API_OBJECT* object = api->new_object_array(api, element_type_id, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        // Set object
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = object;

        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_STRING: {
        int32_t name_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        
        SPVM_API_OBJECT* string = api->new_string(api, (char*)&SPVM_INFO_CONSTANT_POOL[name_id + 1], SPVM_INFO_CONSTANT_POOL[name_id]);

        // Set string
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = string;

        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LENGTH:
        if (vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value == NULL) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Can't get array length of undef value.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = *(int32_t*)((intptr_t)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET);
          bytecode_index += 3;
          break;
        }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_BYTE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 3];
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* SPVM_INFO_FIELD_XXX_YYY = (SPVM_CONSTANT_POOL_FIELD*)&SPVM_INFO_CONSTANT_POOL[field_id];
        int32_t SPVM_INFO_FIELD_XXX_YYY_INDEX = SPVM_INFO_FIELD_XXX_YYY->index;
        int32_t SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET = SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * SPVM_INFO_FIELD_XXX_YYY_INDEX;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef(get_byte_field).", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value = *(int8_t*)((intptr_t)object + SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET);
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_SHORT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 3];
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* SPVM_INFO_FIELD_XXX_YYY = (SPVM_CONSTANT_POOL_FIELD*)&SPVM_INFO_CONSTANT_POOL[field_id];
        int32_t SPVM_INFO_FIELD_XXX_YYY_INDEX = SPVM_INFO_FIELD_XXX_YYY->index;
        int32_t SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET = SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * SPVM_INFO_FIELD_XXX_YYY_INDEX;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef(get_byte_field).", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value = *(int16_t*)((intptr_t)object + SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET);
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_INT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 3];
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* SPVM_INFO_FIELD_XXX_YYY = (SPVM_CONSTANT_POOL_FIELD*)&SPVM_INFO_CONSTANT_POOL[field_id];
        int32_t SPVM_INFO_FIELD_XXX_YYY_INDEX = SPVM_INFO_FIELD_XXX_YYY->index;
        int32_t SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET = SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * SPVM_INFO_FIELD_XXX_YYY_INDEX;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef(get_byte_field).", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = *(int32_t*)((intptr_t)object + SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET);
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_LONG: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 3];
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* SPVM_INFO_FIELD_XXX_YYY = (SPVM_CONSTANT_POOL_FIELD*)&SPVM_INFO_CONSTANT_POOL[field_id];
        int32_t SPVM_INFO_FIELD_XXX_YYY_INDEX = SPVM_INFO_FIELD_XXX_YYY->index;
        int32_t SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET = SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * SPVM_INFO_FIELD_XXX_YYY_INDEX;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef(get_byte_field).", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = *(int64_t*)((intptr_t)object + SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET);
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_FLOAT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 3];
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* SPVM_INFO_FIELD_XXX_YYY = (SPVM_CONSTANT_POOL_FIELD*)&SPVM_INFO_CONSTANT_POOL[field_id];
        int32_t SPVM_INFO_FIELD_XXX_YYY_INDEX = SPVM_INFO_FIELD_XXX_YYY->index;
        int32_t SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET = SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * SPVM_INFO_FIELD_XXX_YYY_INDEX;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef(get_byte_field).", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value = *(float*)((intptr_t)object + SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET);
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_DOUBLE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 3];
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* SPVM_INFO_FIELD_XXX_YYY = (SPVM_CONSTANT_POOL_FIELD*)&SPVM_INFO_CONSTANT_POOL[field_id];
        int32_t SPVM_INFO_FIELD_XXX_YYY_INDEX = SPVM_INFO_FIELD_XXX_YYY->index;
        int32_t SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET = SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * SPVM_INFO_FIELD_XXX_YYY_INDEX;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef(get_byte_field).", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value = *(double*)((intptr_t)object + SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET);
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_OBJECT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 3];
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* SPVM_INFO_FIELD_XXX_YYY = (SPVM_CONSTANT_POOL_FIELD*)&SPVM_INFO_CONSTANT_POOL[field_id];
        int32_t SPVM_INFO_FIELD_XXX_YYY_INDEX = SPVM_INFO_FIELD_XXX_YYY->index;
        int32_t SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET = SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * SPVM_INFO_FIELD_XXX_YYY_INDEX;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef(get_byte_field).", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = *(SPVM_API_OBJECT**)((intptr_t)object + SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET);
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_WEAKEN_FIELD_OBJECT: {
        
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        
        api->weaken_object_field(api, object, field_id);
        
        if (SPVM_INLINE_GET_EXCEPTION()) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        bytecode_index += 3;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_BYTE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        int8_t value = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* SPVM_INFO_FIELD_XXX_YYY = (SPVM_CONSTANT_POOL_FIELD*)&SPVM_INFO_CONSTANT_POOL[field_id];
        int32_t SPVM_INFO_FIELD_XXX_YYY_INDEX = SPVM_INFO_FIELD_XXX_YYY->index;
        int32_t SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET = SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * SPVM_INFO_FIELD_XXX_YYY_INDEX;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef(get_byte_field).", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        *(int8_t*)((intptr_t)object + SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET) = value;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_SHORT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        int16_t value = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* SPVM_INFO_FIELD_XXX_YYY = (SPVM_CONSTANT_POOL_FIELD*)&SPVM_INFO_CONSTANT_POOL[field_id];
        int32_t SPVM_INFO_FIELD_XXX_YYY_INDEX = SPVM_INFO_FIELD_XXX_YYY->index;
        int32_t SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET = SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * SPVM_INFO_FIELD_XXX_YYY_INDEX;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef(get_byte_field).", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        *(int16_t*)((intptr_t)object + SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET) = value;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_INT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        int32_t value = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* SPVM_INFO_FIELD_XXX_YYY = (SPVM_CONSTANT_POOL_FIELD*)&SPVM_INFO_CONSTANT_POOL[field_id];
        int32_t SPVM_INFO_FIELD_XXX_YYY_INDEX = SPVM_INFO_FIELD_XXX_YYY->index;
        int32_t SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET = SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * SPVM_INFO_FIELD_XXX_YYY_INDEX;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef(get_byte_field).", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        *(int32_t*)((intptr_t)object + SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET) = value;

        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_LONG: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        int64_t value = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* SPVM_INFO_FIELD_XXX_YYY = (SPVM_CONSTANT_POOL_FIELD*)&SPVM_INFO_CONSTANT_POOL[field_id];
        int32_t SPVM_INFO_FIELD_XXX_YYY_INDEX = SPVM_INFO_FIELD_XXX_YYY->index;
        int32_t SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET = SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * SPVM_INFO_FIELD_XXX_YYY_INDEX;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef(get_byte_field).", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        *(int64_t*)((intptr_t)object + SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET) = value;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_FLOAT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        float value = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].float_value;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* SPVM_INFO_FIELD_XXX_YYY = (SPVM_CONSTANT_POOL_FIELD*)&SPVM_INFO_CONSTANT_POOL[field_id];
        int32_t SPVM_INFO_FIELD_XXX_YYY_INDEX = SPVM_INFO_FIELD_XXX_YYY->index;
        int32_t SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET = SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * SPVM_INFO_FIELD_XXX_YYY_INDEX;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef(get_byte_field).", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        *(float*)((intptr_t)object + SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET) = value;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_DOUBLE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        double value = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].double_value;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* SPVM_INFO_FIELD_XXX_YYY = (SPVM_CONSTANT_POOL_FIELD*)&SPVM_INFO_CONSTANT_POOL[field_id];
        int32_t SPVM_INFO_FIELD_XXX_YYY_INDEX = SPVM_INFO_FIELD_XXX_YYY->index;
        int32_t SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET = SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * SPVM_INFO_FIELD_XXX_YYY_INDEX;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef(get_byte_field).", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        *(double*)((intptr_t)object + SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET) = value;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_OBJECT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value;
        int32_t field_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        SPVM_API_OBJECT* value = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].object_value;

        // Index
        SPVM_CONSTANT_POOL_FIELD* SPVM_INFO_FIELD_XXX_YYY = (SPVM_CONSTANT_POOL_FIELD*)&SPVM_INFO_CONSTANT_POOL[field_id];
        int32_t SPVM_INFO_FIELD_XXX_YYY_INDEX = SPVM_INFO_FIELD_XXX_YYY->index;
        int32_t SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET = SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * SPVM_INFO_FIELD_XXX_YYY_INDEX;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef(get_byte_field).", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        SPVM_API_VALUE* field_address = (SPVM_API_VALUE*)((intptr_t)object + SPVM_INFO_FIELD_XXX_YYY_BYTE_OFFSET);
        
        if((*field_address).object_value != NULL) {
          // If object is weak, unweaken
          if (SPVM_INLINE_ISWEAK((*field_address).object_value)) {
            api->unweaken(api, (SPVM_API_OBJECT**)field_address);
          }
          api->dec_ref_count(api, (*field_address).object_value);
        }
        
        (*field_address).object_value = value;
        
        if((*field_address).object_value != NULL) {
          SPVM_INLINE_INC_REF_COUNT((*field_address).object_value);
        }
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_STRING: {
        SPVM_API_OBJECT* string1 = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        SPVM_API_OBJECT* string2 = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].object_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_string(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = string3;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_BYTE: {
        SPVM_API_OBJECT* string1 = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int8_t string2 = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].byte_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_byte(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = string3;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_SHORT: {
        SPVM_API_OBJECT* string1 = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int16_t string2 = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].short_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_short(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = string3;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_INT: {
        SPVM_API_OBJECT* string1 = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int32_t string2 = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].int_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_int(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = string3;

        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_LONG: {
        SPVM_API_OBJECT* string1 = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        int64_t string2 = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].long_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_long(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = string3;

        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_FLOAT: {
        SPVM_API_OBJECT* string1 = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        float string2 = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].float_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_float(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }

        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = string3;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_DOUBLE: {
        SPVM_API_OBJECT* string1 = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        double string2 = vars[SPVM_INFO_BYTECODES[bytecode_index + 3]].double_value;
        
        SPVM_API_OBJECT* string3 = api->concat_string_double(api, string1, string2);
        
        if (string3 == NULL) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = string3;
        
        bytecode_index += 4;
        break;
      }
      case SPVM_BYTECODE_C_CODE_LOAD_PACKAGE_VAR: {
        // Get subroutine ID
        int32_t package_var_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]] = SPVM_INFO_PACKAGE_VARS[package_var_id];
        
        bytecode_index += 3;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_LOAD_PACKAGE_VAR_OBJECT: {
        // Get subroutine ID
        int32_t package_var_id = SPVM_INFO_BYTECODES[bytecode_index + 2];
        
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = SPVM_INFO_PACKAGE_VARS[package_var_id].object_value;
        
        bytecode_index += 3;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_STORE_PACKAGE_VAR: {
        // Get subroutine ID
        int32_t package_var_id = SPVM_INFO_BYTECODES[bytecode_index + 1];

        SPVM_INFO_PACKAGE_VARS[package_var_id] = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]];

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
        SPVM_INFO_PACKAGE_VARS[package_var_id].object_value = vars[SPVM_INFO_BYTECODES[bytecode_index + 2]].object_value;
        
        // Increment new value reference count
        if (SPVM_INFO_PACKAGE_VARS[package_var_id].object_value != NULL) {
          SPVM_INLINE_INC_REF_COUNT(SPVM_INFO_PACKAGE_VARS[package_var_id].object_value);
        }

        bytecode_index += 3;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_PUSH_EVAL: {
        // Next operation
        int16_t jump_offset_abs = SPVM_INFO_BYTECODES[bytecode_index + 1];
        
        eval_stack_top++;
        eval_stack[eval_stack_top] = jump_offset_abs;
        
        bytecode_index += 2;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_POP_EVAL: {
        eval_stack_top--;
        
        bytecode_index++;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_LOAD_EXCEPTION_VAR: {
        vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = (SPVM_API_OBJECT*)SPVM_INLINE_GET_EXCEPTION();
        
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_STORE_EXCEPTION_VAR: {
        
        api->set_exception(api, (SPVM_API_OBJECT*)vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value);
        
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CURRENT_LINE:
        current_line = SPVM_INFO_BYTECODES[bytecode_index + 1];
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_CALL_SUB:
      {
        // Get subroutine ID
        int32_t call_sub_id = SPVM_INFO_BYTECODES[bytecode_index + 2];

        // Constant pool sub
        SPVM_CONSTANT_POOL_SUB* SPVM_INFO_CONSTANT_POOL_SUB_YYY = (SPVM_CONSTANT_POOL_SUB*)&SPVM_INFO_CONSTANT_POOL[call_sub_id];
        
        // Call subroutine return type id
        int32_t SPVM_INFO_SUB_YYY_RETURN_TYPE_ID = SPVM_INFO_CONSTANT_POOL_SUB_YYY->return_type_id;
        
        // Constant pool type
        SPVM_CONSTANT_POOL_TYPE* SPVM_INFO_SUB_YYY_RETURN_TYPE = (SPVM_CONSTANT_POOL_TYPE*)&SPVM_INFO_CONSTANT_POOL[SPVM_INFO_SUB_YYY_RETURN_TYPE_ID];
        
        // Return type code
        int32_t SPVM_INFO_SUB_YYY_RETURN_TYPE_CODE = SPVM_INFO_SUB_YYY_RETURN_TYPE->code;
        
        // Subroutine argument length
        int32_t SPVM_INFO_SUB_YYY_ARGS_LENGTH = SPVM_INFO_CONSTANT_POOL_SUB_YYY->args_length;

        // Subroutine argument length
        int32_t SPVM_INFO_SUB_YYY_IS_VOID = SPVM_INFO_CONSTANT_POOL_SUB_YYY->is_void;
        
        call_sub_arg_stack_top -= SPVM_INFO_SUB_YYY_ARGS_LENGTH;
        
        SPVM_VALUE args[255];
        {
          int32_t i;
          for (i = 0; i < SPVM_INFO_SUB_YYY_ARGS_LENGTH; i++) {
            int32_t var_index = call_sub_arg_stack[call_sub_arg_stack_top + 1 + i].int_value;
            args[i] = vars[var_index];
          }
        }
        
        // Call subroutine
        if (SPVM_INFO_SUB_YYY_IS_VOID) {
          api->call_void_sub(api, call_sub_id, (SPVM_API_VALUE*)args);
        }
        else if (SPVM_INFO_SUB_YYY_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_BYTE) {
          vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].byte_value = api->call_byte_sub(api, call_sub_id, (SPVM_API_VALUE*)args);
        }
        else if (SPVM_INFO_SUB_YYY_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_SHORT) {
          vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].short_value = api->call_short_sub(api, call_sub_id, (SPVM_API_VALUE*)args);
        }
        else if (SPVM_INFO_SUB_YYY_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_INT) {
          vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value = api->call_int_sub(api, call_sub_id, (SPVM_API_VALUE*)args);
        }
        else if (SPVM_INFO_SUB_YYY_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_LONG) {
          vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].long_value = api->call_long_sub(api, call_sub_id, (SPVM_API_VALUE*)args);
        }
        else if (SPVM_INFO_SUB_YYY_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_FLOAT) {
          vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].float_value = api->call_float_sub(api, call_sub_id, (SPVM_API_VALUE*)args);
        }
        else if (SPVM_INFO_SUB_YYY_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_DOUBLE) {
          vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].double_value = api->call_double_sub(api, call_sub_id, (SPVM_API_VALUE*)args);
        }
        else {
          vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].object_value = api->call_object_sub(api, call_sub_id, (SPVM_API_VALUE*)args);
        }
        
        if (SPVM_INLINE_GET_EXCEPTION()) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          // Next operation
          bytecode_index += 3 + (SPVM_INFO_DEBUG * 2);
        }
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_RETURN_BYTE:
      case SPVM_BYTECODE_C_CODE_RETURN_SHORT:
      case SPVM_BYTECODE_C_CODE_RETURN_INT:
      case SPVM_BYTECODE_C_CODE_RETURN_LONG:
      case SPVM_BYTECODE_C_CODE_RETURN_FLOAT:
      case SPVM_BYTECODE_C_CODE_RETURN_DOUBLE:
      {
        // Get return value
        return_value = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]];

        label_SPVM_BYTECODE_C_CODE_RETURN_BYTE:
        label_SPVM_BYTECODE_C_CODE_RETURN_SHORT:
        label_SPVM_BYTECODE_C_CODE_RETURN_INT:
        label_SPVM_BYTECODE_C_CODE_RETURN_LONG:
        label_SPVM_BYTECODE_C_CODE_RETURN_FLOAT:
        label_SPVM_BYTECODE_C_CODE_RETURN_DOUBLE:
        {
          
          // Decrement my vars which is arguments - decrement only
          {
            int32_t i;
            for (i = 0; i < SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH; i++) {
              int32_t my_var_index = SPVM_INFO_CONSTANT_POOL[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
              SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[my_var_index].object_value;
              
              if (object != NULL) {
                SPVM_INLINE_DEC_REF_COUNT_ONLY(object);
              }
            }
          }

          // Decrement my vars which is not arguments - decrement and if reference count is 0, free object
          {
            int32_t i;
            for (i = SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH; i < SPVM_INFO_SUB_XXX_OBJECT_MYS_LENGTH; i++) {
              int32_t my_var_index = SPVM_INFO_CONSTANT_POOL[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
              SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[my_var_index].object_value;
              
              if (object != NULL) {
                api->dec_ref_count(api, object);
              }
            }
          }
          
          // No exception
          SPVM_INLINE_SET_EXCEPTION_NULL();
          
          return return_value;
        }
      }
      case SPVM_BYTECODE_C_CODE_RETURN_OBJECT: {

        return_value = vars[SPVM_INFO_BYTECODES[bytecode_index + 1]];

        label_SPVM_BYTECODE_C_CODE_RETURN_OBJECT: {
        
          
          // Increment ref count of return value not to release by decrement
          if (return_value.object_value != NULL) {
            SPVM_INLINE_INC_REF_COUNT(return_value.object_value);
          }
          
          // Decrement my vars which is arguments - decrement only
          {
            int32_t i;
            for (i = 0; i < SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH; i++) {
              int32_t my_var_index = SPVM_INFO_CONSTANT_POOL[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
              SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[my_var_index].object_value;
              
              if (object != NULL) {
                SPVM_INLINE_DEC_REF_COUNT_ONLY(object);
              }
            }
          }

          // Decrement my vars which is not arguments - decrement and if reference count is 0, free object
          {
            int32_t i;
            for (i = SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH; i < SPVM_INFO_SUB_XXX_OBJECT_MYS_LENGTH; i++) {
              int32_t my_var_index = SPVM_INFO_CONSTANT_POOL[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
              SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[my_var_index].object_value;
              
              if (object != NULL) {
                api->dec_ref_count(api, object);
              }
            }
          }

          // Decrement ref count of return value
          if (return_value.object_value != NULL) {
            SPVM_INLINE_DEC_REF_COUNT_ONLY(return_value.object_value);
          }
          
          SPVM_INLINE_SET_EXCEPTION_NULL();
          
          return return_value;
        }
      }
      case SPVM_BYTECODE_C_CODE_RETURN_VOID: {

        label_SPVM_BYTECODE_C_CODE_RETURN_VOID: {

          memset(&return_value, 0, sizeof(SPVM_VALUE));
          
          // Decrement object my vars reference count
          {
            int32_t i;
            for (i = 0; i < SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH; i++) {
              int32_t my_var_index = SPVM_INFO_CONSTANT_POOL[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
              SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[my_var_index].object_value;
              
              if (object != NULL) {
                SPVM_INLINE_DEC_REF_COUNT_ONLY(object);
              }
            }
          }
          {
            int32_t i;
            for (i = SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH; i < SPVM_INFO_SUB_XXX_OBJECT_MYS_LENGTH; i++) {
              int32_t my_var_index = SPVM_INFO_CONSTANT_POOL[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
              SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[my_var_index].object_value;
              
              if (object != NULL) {
                api->dec_ref_count(api, object);
              }
            }
          }
          
          // No exception
          SPVM_INLINE_SET_EXCEPTION_NULL();

          return return_value;
        }
      }
      case SPVM_BYTECODE_C_CODE_CROAK: {
        
        label_SPVM_BYTECODE_C_CODE_CROAK:
        
        // Catch exception
        if (eval_stack_top > -1) {
          
          int32_t jump_offset_abs = eval_stack[eval_stack_top];
          eval_stack_top--;
          
          bytecode_index = SPVM_INFO_SUB_XXX_BYTECODE_BASE + jump_offset_abs;
          
          break;
        }
        
        // Decrement my vars which is arguments - decrement only
        {
          int32_t i;
          for (i = 0; i < SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH; i++) {
            int32_t my_var_index = SPVM_INFO_CONSTANT_POOL[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
            SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[my_var_index].object_value;
            
            if (object != NULL) {
              SPVM_INLINE_DEC_REF_COUNT_ONLY(object);
            }
          }
        }

        // Decrement my vars which is not arguments - decrement and if reference count is 0, free object
        {
          int32_t i;
          for (i = SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH; i < SPVM_INFO_SUB_XXX_OBJECT_MYS_LENGTH; i++) {
            int32_t my_var_index = SPVM_INFO_CONSTANT_POOL[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
            SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)vars[my_var_index].object_value;
            
            if (object != NULL) {
              api->dec_ref_count(api, object);
            }
          }
        }
        
        if (SPVM_INFO_DEBUG) {
          // Sub name
          const char* sub_name = (char*)&SPVM_INFO_CONSTANT_POOL[SPVM_INFO_SUB_XXX_ABS_NAME_ID + 1];
          
          // File name
          const char* file_name = (char*)&SPVM_INFO_CONSTANT_POOL[SPVM_INFO_SUB_XXX_FILE_NAME_ID + 1];
          
          // stack trace strings
          const char* from = "\n  from ";
          const char* at = "() at ";

          // Exception
          SPVM_API_OBJECT* exception = SPVM_INLINE_GET_EXCEPTION();
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
          
          sprintf(line_str, "%" PRId32, current_line);
          total_length += strlen(line);
          total_length += strlen(line_str);
          
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
        }
        
        memset(&return_value, 0, sizeof(SPVM_VALUE));
        
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
        
        if (vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value >= min && vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value <= max) {
          int32_t branch_offset
            = *(int32_t*)((&SPVM_INFO_BYTECODES[bytecode_index + 5]) + (vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value - min));
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
        
        if (vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value >= min && vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value <= max) {
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
            
            if (vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value > cur_half) {
              cur_min_pos = cur_half_pos + 1;
            }
            else if (vars[SPVM_INFO_BYTECODES[bytecode_index + 1]].int_value < cur_half) {
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
        call_sub_arg_stack_top++;
        call_sub_arg_stack[call_sub_arg_stack_top].int_value = SPVM_INFO_BYTECODES[bytecode_index + 1];
        
        bytecode_index += 2;
        break;
    }
  }
}
