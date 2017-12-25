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
#include "spvm_opcode.h"
#include "spvm_object.h"
#include "spvm_type.h"
#include "spvm_runtime.h"
#include "spvm_constant_pool.h"
#include "spvm_constant_pool_sub.h"
#include "spvm_constant_pool_field.h"
#include "spvm_constant_pool_type.h"
#include "spvm_opcode.h"
#include "spvm_opcode_array.h"

#define SPVM_INFO_OBJECT_HEADER_BYTE_SIZE sizeof(SPVM_OBJECT)
#define SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET ((int32_t)offsetof(SPVM_OBJECT, length))
#define SPVM_INFO_OBJECT_REF_COUNT_BYTE_OFFSET ((int32_t)offsetof(SPVM_OBJECT, ref_count))
#define runtime_EXCEPTION_BYTE_OFFSET ((int32_t)offsetof(SPVM_RUNTIME, exception))
#define SPVM_INFO_TYPE_CODE_VOID (SPVM_TYPE_C_CODE_VOID)
#define SPVM_INFO_TYPE_CODE_BYTE (SPVM_TYPE_C_CODE_BYTE)
#define SPVM_INFO_TYPE_CODE_SHORT (SPVM_TYPE_C_CODE_SHORT)
#define SPVM_INFO_TYPE_CODE_INT (SPVM_TYPE_C_CODE_INT)
#define SPVM_INFO_TYPE_CODE_LONG (SPVM_TYPE_C_CODE_LONG)
#define SPVM_INFO_TYPE_CODE_FLOAT (SPVM_TYPE_C_CODE_FLOAT)
#define SPVM_INFO_TYPE_CODE_DOUBLE (SPVM_TYPE_C_CODE_DOUBLE)

#define SPVM_INLINE_GET_REF_COUNT(object) ((*(int32_t*)((intptr_t)object + SPVM_INFO_OBJECT_REF_COUNT_BYTE_OFFSET)))
#define SPVM_INLINE_INC_REF_COUNT(object) ((*(int32_t*)((intptr_t)object + SPVM_INFO_OBJECT_REF_COUNT_BYTE_OFFSET))++)
#define SPVM_INLINE_DEC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + SPVM_INFO_OBJECT_REF_COUNT_BYTE_OFFSET))--)
#define SPVM_INLINE_GET_EXCEPTION() (*(SPVM_API_OBJECT**)((intptr_t)runtime + runtime_EXCEPTION_BYTE_OFFSET))
#define SPVM_INLINE_SET_EXCEPTION_NULL() \
  do { \
    if ((*(SPVM_API_OBJECT**)((intptr_t)runtime + runtime_EXCEPTION_BYTE_OFFSET)) != NULL) { \
      api->dec_ref_count(api, (*(SPVM_API_OBJECT**)((intptr_t)runtime + runtime_EXCEPTION_BYTE_OFFSET))); \
    } \
    (*(SPVM_API_OBJECT**)((intptr_t)runtime + runtime_EXCEPTION_BYTE_OFFSET)) = NULL; \
  } \
  while (0) \

#define SPVM_INLINE_ISWEAK(object) ((intptr_t)object & 1)


SPVM_API_VALUE SPVM_RUNTIME_call_sub(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args) {
  (void)api;
  
  // Runtime
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  // Constant pool
  int32_t* constant_pool = runtime->constant_pool;

  // Constant pool sub
  SPVM_CONSTANT_POOL_SUB* constant_pool_SUB_XXX = (SPVM_CONSTANT_POOL_SUB*)&constant_pool[sub_id];
  
  // Debug
  int32_t SPVM_INFO_DEBUG = runtime->debug ? 1 : 0;
  
  // Subroutine object my length
  int32_t SPVM_INFO_SUB_XXX_OBJECT_MYS_LENGTH = constant_pool_SUB_XXX->object_mys_length;
  
  // Subroutine object my base index
  int32_t SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE = constant_pool_SUB_XXX->object_mys_base;
  
  // Subroutine name id
  int32_t SPVM_INFO_SUB_XXX_ABS_NAME_ID = constant_pool_SUB_XXX->abs_name_id;
  
  // Subroutine file name id
  int32_t SPVM_INFO_SUB_XXX_FILE_NAME_ID = constant_pool_SUB_XXX->file_name_id;
  
  // Subroutine return type id
  int32_t SPVM_INFO_SUB_XXX_RETURN_TYPE_ID = constant_pool_SUB_XXX->return_type_id;
  
  // Subroutine is native
  int32_t SPVM_INFO_SUB_XXX_IS_NATIVE = constant_pool_SUB_XXX->is_native;
  
  // Subroutine object args length
  int32_t SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH = constant_pool_SUB_XXX->object_args_length;

  // Subroutine object args length
  int32_t SPVM_INFO_SUB_XXX_OBJECT_ARGS_BASE = constant_pool_SUB_XXX->object_args_base;
  
  // Bytecodes
  SPVM_OPCODE* SPVM_INFO_OPCODES = runtime->opcodes;
  
  // Opcode base
  int32_t SPVM_INFO_SUB_XXX_OPCODE_BASE = constant_pool_SUB_XXX->opcode_base;
  
  // Args length
  int32_t args_length = constant_pool_SUB_XXX->args_length;
  
  // Native address
  void* SPVM_INFO_SUB_XXX_NATIVE_ADDRESS = constant_pool_SUB_XXX->native_address;
  
  // Constant pool type
  SPVM_CONSTANT_POOL_TYPE* SPVM_INFO_SUB_XXX_RETURN_TYPE = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[SPVM_INFO_SUB_XXX_RETURN_TYPE_ID];

  // Return type code
  int32_t SPVM_INFO_SUB_XXX_RETURN_TYPE_CODE = SPVM_INFO_SUB_XXX_RETURN_TYPE->code;
  
  // Call stack
  SPVM_API_VALUE vars[65535];
  
  // Eval stack
  int32_t eval_stack[255];
  
  // Eval stack top
  int32_t eval_stack_top = -1;
  
  // Call subroutine argument stack
  SPVM_API_VALUE call_sub_arg_stack[255];
  
  // Call subroutine argument stack top
  int32_t call_sub_arg_stack_top = -1;
  
  // Current line
  int32_t current_line = 0;
  
  // Condition flag
  register int32_t condition_flag = 0;

  // Return value
  SPVM_API_VALUE return_value;
  
  // Copy arguments
  memcpy(vars, args, args_length * sizeof(SPVM_API_VALUE));
  
  // Set exception to NULL;
  SPVM_INLINE_SET_EXCEPTION_NULL();
  
  // Call native sub
  if (SPVM_INFO_SUB_XXX_IS_NATIVE) {
    // Call native subroutine
    if (SPVM_INFO_SUB_XXX_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_VOID) {
      void (*native_address)(SPVM_API*, SPVM_API_VALUE*) = SPVM_INFO_SUB_XXX_NATIVE_ADDRESS;
      (*native_address)(api, (SPVM_API_VALUE*)vars);
    }
    else if (SPVM_INFO_SUB_XXX_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_BYTE) {
      int8_t (*native_address)(SPVM_API*, SPVM_API_VALUE*) = SPVM_INFO_SUB_XXX_NATIVE_ADDRESS;
      int8_t return_value_native = (*native_address)(api, (SPVM_API_VALUE*)vars);
      return_value.byte_value = return_value_native;
    }
    else if (SPVM_INFO_SUB_XXX_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_SHORT) {
      int16_t (*native_address)(SPVM_API*, SPVM_API_VALUE*) = SPVM_INFO_SUB_XXX_NATIVE_ADDRESS;
      int16_t return_value_native = (*native_address)(api, (SPVM_API_VALUE*)vars);
      return_value.short_value = return_value_native;
    }
    else if (SPVM_INFO_SUB_XXX_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_INT) {
      int32_t (*native_address)(SPVM_API*, SPVM_API_VALUE*) = SPVM_INFO_SUB_XXX_NATIVE_ADDRESS;
      int32_t return_value_native = (*native_address)(api, (SPVM_API_VALUE*)vars);
      return_value.int_value = return_value_native;
    }
    else if (SPVM_INFO_SUB_XXX_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_LONG) {
      int64_t (*native_address)(SPVM_API*, SPVM_API_VALUE*) = SPVM_INFO_SUB_XXX_NATIVE_ADDRESS;
      int64_t return_value_native = (*native_address)(api, (SPVM_API_VALUE*)vars);
      return_value.long_value = return_value_native;
    }
    else if (SPVM_INFO_SUB_XXX_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_FLOAT) {
      float (*native_address)(SPVM_API*, SPVM_API_VALUE*) = SPVM_INFO_SUB_XXX_NATIVE_ADDRESS;
      float return_value_native = (*native_address)(api, (SPVM_API_VALUE*)vars);
      return_value.float_value = return_value_native;
    }
    else if (SPVM_INFO_SUB_XXX_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_DOUBLE) {
      double (*native_address)(SPVM_API*, SPVM_API_VALUE*) = SPVM_INFO_SUB_XXX_NATIVE_ADDRESS;
      double return_value_native = (*native_address)(api, (SPVM_API_VALUE*)vars);
      return_value.double_value = return_value_native;
    }
    else {
      SPVM_API_OBJECT* (*native_address)(SPVM_API*, SPVM_API_VALUE*) = SPVM_INFO_SUB_XXX_NATIVE_ADDRESS;
      SPVM_API_OBJECT* return_value_native = (*native_address)(api, (SPVM_API_VALUE*)vars);
      return_value.object_value = return_value_native;
    }
    return return_value;
  }
  
  // Call normal sub
  // If arg is object, increment reference count
  {
    int32_t i;
    for (i = 0; i < SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH; i++) {
      int32_t arg_index = constant_pool[SPVM_INFO_SUB_XXX_OBJECT_ARGS_BASE + i];
      
      SPVM_API_OBJECT* object = vars[arg_index].object_value;
      if (object != NULL) {
        SPVM_INLINE_INC_REF_COUNT(object);
      }
    }
  }
  
  register int32_t opcode_index = SPVM_INFO_SUB_XXX_OPCODE_BASE;
  
  while (1) {
    SPVM_OPCODE* opcode = &(SPVM_INFO_OPCODES[opcode_index]);
    
    switch (opcode->code) {
      case SPVM_OPCODE_C_CODE_NOP:
        abort();
      case SPVM_OPCODE_C_CODE_BOOL_BYTE:
        condition_flag = !!vars[opcode->operand0].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_BOOL_SHORT:
        condition_flag = !!vars[opcode->operand0].short_value;
        break;
      case SPVM_OPCODE_C_CODE_BOOL_INT:
        condition_flag = !!vars[opcode->operand0].int_value;
        break;
      case SPVM_OPCODE_C_CODE_BOOL_LONG:
        condition_flag = !!vars[opcode->operand0].long_value;
        break;
      case SPVM_OPCODE_C_CODE_BOOL_FLOAT:
        condition_flag = !!vars[opcode->operand0].float_value;
        break;
      case SPVM_OPCODE_C_CODE_BOOL_DOUBLE:
        condition_flag = !!vars[opcode->operand0].double_value;
        break;
      case SPVM_OPCODE_C_CODE_BOOL_OBJECT:
        condition_flag = !!vars[opcode->operand0].object_value;
        break;
      case SPVM_OPCODE_C_CODE_IS_UNDEF:
        condition_flag = vars[opcode->operand0].object_value == NULL;
        break;
      case SPVM_OPCODE_C_CODE_IS_NOT_UNDEF:
        condition_flag = vars[opcode->operand0].object_value != NULL;
        break;
      case SPVM_OPCODE_C_CODE_EQ_BYTE:
        condition_flag = vars[opcode->operand0].byte_value == vars[opcode->operand1].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_EQ_SHORT:
        condition_flag = vars[opcode->operand0].short_value == vars[opcode->operand1].short_value;
        break;
      case SPVM_OPCODE_C_CODE_EQ_INT:
        condition_flag = vars[opcode->operand0].int_value == vars[opcode->operand1].int_value;
        break;
      case SPVM_OPCODE_C_CODE_EQ_LONG:
        condition_flag = vars[opcode->operand0].long_value == vars[opcode->operand1].long_value;
        break;
      case SPVM_OPCODE_C_CODE_EQ_FLOAT:
        condition_flag = vars[opcode->operand0].float_value == vars[opcode->operand1].float_value;
        break;
      case SPVM_OPCODE_C_CODE_EQ_DOUBLE:
        condition_flag = vars[opcode->operand0].double_value == vars[opcode->operand1].double_value;
        break;
      case SPVM_OPCODE_C_CODE_EQ_OBJECT:
        condition_flag = vars[opcode->operand0].object_value == vars[opcode->operand1].object_value;
        break;
      case SPVM_OPCODE_C_CODE_NE_BYTE:
        condition_flag = vars[opcode->operand0].byte_value != vars[opcode->operand1].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_NE_SHORT:
        condition_flag = vars[opcode->operand0].short_value != vars[opcode->operand1].short_value;
        break;
      case SPVM_OPCODE_C_CODE_NE_INT:
        condition_flag = vars[opcode->operand0].int_value != vars[opcode->operand1].int_value;
        break;
      case SPVM_OPCODE_C_CODE_NE_LONG:
        condition_flag = vars[opcode->operand0].long_value != vars[opcode->operand1].long_value;
        break;
      case SPVM_OPCODE_C_CODE_NE_FLOAT:
        condition_flag = vars[opcode->operand0].float_value != vars[opcode->operand1].float_value;
        break;
      case SPVM_OPCODE_C_CODE_NE_DOUBLE:
        condition_flag = vars[opcode->operand0].double_value != vars[opcode->operand1].double_value;
        break;
      case SPVM_OPCODE_C_CODE_NE_OBJECT:
        condition_flag = vars[opcode->operand0].object_value != vars[opcode->operand1].object_value;
        break;
      case SPVM_OPCODE_C_CODE_GT_BYTE:
        condition_flag = vars[opcode->operand0].byte_value > vars[opcode->operand1].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_GT_SHORT:
        condition_flag = vars[opcode->operand0].short_value > vars[opcode->operand1].short_value;
        break;
      case SPVM_OPCODE_C_CODE_GT_INT:
        condition_flag = vars[opcode->operand0].int_value > vars[opcode->operand1].int_value;
        break;
      case SPVM_OPCODE_C_CODE_GT_LONG:
        condition_flag = vars[opcode->operand0].long_value > vars[opcode->operand1].long_value;
        break;
      case SPVM_OPCODE_C_CODE_GT_FLOAT:
        condition_flag = vars[opcode->operand0].float_value > vars[opcode->operand1].float_value;
        break;
      case SPVM_OPCODE_C_CODE_GT_DOUBLE:
        condition_flag = vars[opcode->operand0].double_value > vars[opcode->operand1].double_value;
        break;
      case SPVM_OPCODE_C_CODE_GE_BYTE:
        condition_flag = vars[opcode->operand0].byte_value >= vars[opcode->operand1].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_GE_SHORT:
        condition_flag = vars[opcode->operand0].short_value >= vars[opcode->operand1].short_value;
        break;
      case SPVM_OPCODE_C_CODE_GE_INT:
        condition_flag = vars[opcode->operand0].int_value >= vars[opcode->operand1].int_value;
        break;
      case SPVM_OPCODE_C_CODE_GE_LONG:
        condition_flag = vars[opcode->operand0].long_value >= vars[opcode->operand1].long_value;
        break;
      case SPVM_OPCODE_C_CODE_GE_FLOAT:
        condition_flag = vars[opcode->operand0].float_value >= vars[opcode->operand1].float_value;
        break;
      case SPVM_OPCODE_C_CODE_GE_DOUBLE:
        condition_flag = vars[opcode->operand0].double_value >= vars[opcode->operand1].double_value;
        break;
      case SPVM_OPCODE_C_CODE_LT_BYTE:
        condition_flag = vars[opcode->operand0].byte_value < vars[opcode->operand1].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_LT_SHORT:
        condition_flag = vars[opcode->operand0].short_value < vars[opcode->operand1].short_value;
        break;
      case SPVM_OPCODE_C_CODE_LT_INT:
        condition_flag = vars[opcode->operand0].int_value < vars[opcode->operand1].int_value;
        break;
      case SPVM_OPCODE_C_CODE_LT_LONG:
        condition_flag = vars[opcode->operand0].long_value < vars[opcode->operand1].long_value;
        break;
      case SPVM_OPCODE_C_CODE_LT_FLOAT:
        condition_flag = vars[opcode->operand0].float_value < vars[opcode->operand1].float_value;
        break;
      case SPVM_OPCODE_C_CODE_LT_DOUBLE:
        condition_flag = vars[opcode->operand0].double_value < vars[opcode->operand1].double_value;
        break;
      case SPVM_OPCODE_C_CODE_LE_BYTE:
        condition_flag = vars[opcode->operand0].byte_value <= vars[opcode->operand1].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_LE_SHORT:
        condition_flag = vars[opcode->operand0].short_value <= vars[opcode->operand1].short_value;
        break;
      case SPVM_OPCODE_C_CODE_LE_INT:
        condition_flag = vars[opcode->operand0].int_value <= vars[opcode->operand1].int_value;
        break;
      case SPVM_OPCODE_C_CODE_LE_LONG:
        condition_flag = vars[opcode->operand0].long_value <= vars[opcode->operand1].long_value;
        break;
      case SPVM_OPCODE_C_CODE_LE_FLOAT:
        condition_flag = vars[opcode->operand0].float_value <= vars[opcode->operand1].float_value;
        break;
      case SPVM_OPCODE_C_CODE_LE_DOUBLE:
        condition_flag = vars[opcode->operand0].double_value <= vars[opcode->operand1].double_value;
        break;
      case SPVM_OPCODE_C_CODE_ADD_BYTE:
        vars[opcode->operand0].byte_value
          = vars[opcode->operand1].byte_value + vars[opcode->operand2].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_ADD_SHORT:
        vars[opcode->operand0].short_value
          = vars[opcode->operand1].short_value + vars[opcode->operand2].short_value;
        break;
      case SPVM_OPCODE_C_CODE_ADD_INT:
        vars[opcode->operand0].int_value
          = vars[opcode->operand1].int_value + vars[opcode->operand2].int_value;
        break;
      case SPVM_OPCODE_C_CODE_ADD_LONG:
        vars[opcode->operand0].long_value
          = vars[opcode->operand1].long_value + vars[opcode->operand2].long_value;
        break;
      case SPVM_OPCODE_C_CODE_ADD_FLOAT:
        vars[opcode->operand0].float_value
          = vars[opcode->operand1].float_value + vars[opcode->operand2].float_value;
        break;
      case SPVM_OPCODE_C_CODE_ADD_DOUBLE:
        vars[opcode->operand0].double_value
          = vars[opcode->operand1].double_value + vars[opcode->operand2].double_value;
        break;
      case SPVM_OPCODE_C_CODE_SUBTRACT_BYTE:
        vars[opcode->operand0].byte_value
          = vars[opcode->operand1].byte_value - vars[opcode->operand2].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_SUBTRACT_SHORT:
        vars[opcode->operand0].short_value
          = vars[opcode->operand1].short_value - vars[opcode->operand2].short_value;
        break;
      case SPVM_OPCODE_C_CODE_SUBTRACT_INT:
        vars[opcode->operand0].int_value
          = vars[opcode->operand1].int_value - vars[opcode->operand2].int_value;
        break;
      case SPVM_OPCODE_C_CODE_SUBTRACT_LONG:
        vars[opcode->operand0].long_value
          = vars[opcode->operand1].long_value - vars[opcode->operand2].long_value;
        break;
      case SPVM_OPCODE_C_CODE_SUBTRACT_FLOAT:
        vars[opcode->operand0].float_value
          = vars[opcode->operand1].float_value - vars[opcode->operand2].float_value;
        break;
      case SPVM_OPCODE_C_CODE_SUBTRACT_DOUBLE:
        vars[opcode->operand0].double_value
          = vars[opcode->operand1].double_value - vars[opcode->operand2].double_value;
        break;
      case SPVM_OPCODE_C_CODE_MULTIPLY_BYTE:
        vars[opcode->operand0].byte_value
          = vars[opcode->operand1].byte_value * vars[opcode->operand2].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_MULTIPLY_SHORT:
        vars[opcode->operand0].short_value
          = vars[opcode->operand1].short_value * vars[opcode->operand2].short_value;
        break;
      case SPVM_OPCODE_C_CODE_MULTIPLY_INT:
        vars[opcode->operand0].int_value
          = vars[opcode->operand1].int_value * vars[opcode->operand2].int_value;
        break;
      case SPVM_OPCODE_C_CODE_MULTIPLY_LONG:
        vars[opcode->operand0].long_value
          = vars[opcode->operand1].long_value * vars[opcode->operand2].long_value;
        break;
      case SPVM_OPCODE_C_CODE_MULTIPLY_FLOAT:
        vars[opcode->operand0].float_value
          = vars[opcode->operand1].float_value * vars[opcode->operand2].float_value;
        break;
      case SPVM_OPCODE_C_CODE_MULTIPLY_DOUBLE:
        vars[opcode->operand0].double_value
          = vars[opcode->operand1].double_value * vars[opcode->operand2].double_value;
        break;
      case SPVM_OPCODE_C_CODE_DIVIDE_BYTE:
        if (__builtin_expect(vars[opcode->operand2].byte_value == 0, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          vars[opcode->operand0].byte_value
            = vars[opcode->operand1].byte_value / vars[opcode->operand2].byte_value;
          break;
        }
      case SPVM_OPCODE_C_CODE_DIVIDE_SHORT:
        if (__builtin_expect(vars[opcode->operand2].short_value == 0, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          vars[opcode->operand0].short_value
            = vars[opcode->operand1].short_value / vars[opcode->operand2].short_value;
          break;
        }
      case SPVM_OPCODE_C_CODE_DIVIDE_INT:
        if (__builtin_expect(vars[opcode->operand2].int_value == 0, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          vars[opcode->operand0].int_value
            = vars[opcode->operand1].int_value / vars[opcode->operand2].int_value;
          break;
        }
      case SPVM_OPCODE_C_CODE_DIVIDE_LONG:
        if (__builtin_expect(vars[opcode->operand2].long_value == 0, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          vars[opcode->operand0].long_value
            = vars[opcode->operand1].long_value / vars[opcode->operand2].long_value;
          break;
        }
      case SPVM_OPCODE_C_CODE_DIVIDE_FLOAT:
        vars[opcode->operand0].float_value
          = vars[opcode->operand1].float_value / vars[opcode->operand2].float_value;
        break;
      case SPVM_OPCODE_C_CODE_DIVIDE_DOUBLE:
        vars[opcode->operand0].double_value
          = vars[opcode->operand1].double_value / vars[opcode->operand2].double_value;
        break;
      case SPVM_OPCODE_C_CODE_REMAINDER_BYTE:
        vars[opcode->operand0].byte_value
          = vars[opcode->operand1].byte_value % vars[opcode->operand2].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_REMAINDER_SHORT:
        vars[opcode->operand0].short_value
          = vars[opcode->operand1].short_value % vars[opcode->operand2].short_value;
        break;
      case SPVM_OPCODE_C_CODE_REMAINDER_INT:
        vars[opcode->operand0].int_value
          = vars[opcode->operand1].int_value % vars[opcode->operand2].int_value;
        break;
      case SPVM_OPCODE_C_CODE_REMAINDER_LONG:
        vars[opcode->operand0].long_value
          = vars[opcode->operand1].long_value % vars[opcode->operand2].long_value;
        break;
      case SPVM_OPCODE_C_CODE_REMAINDER_FLOAT:
        vars[opcode->operand0].float_value
          = (float)fmod((double)vars[opcode->operand1].float_value, vars[opcode->operand2].float_value);
        break;
      case SPVM_OPCODE_C_CODE_REMAINDER_DOUBLE:
        vars[opcode->operand0].double_value
          = fmod(vars[opcode->operand1].double_value, vars[opcode->operand2].double_value);
        break;
      case SPVM_OPCODE_C_CODE_LEFT_SHIFT_BYTE:
        vars[opcode->operand0].byte_value
          = vars[opcode->operand1].byte_value << vars[opcode->operand2].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_LEFT_SHIFT_SHORT:
        vars[opcode->operand0].short_value
          = vars[opcode->operand1].short_value << vars[opcode->operand2].short_value;
        break;
      case SPVM_OPCODE_C_CODE_LEFT_SHIFT_INT:
        vars[opcode->operand0].int_value
          = vars[opcode->operand1].int_value << vars[opcode->operand2].int_value;
        break;
      case SPVM_OPCODE_C_CODE_LEFT_SHIFT_LONG:
        vars[opcode->operand0].long_value
          = vars[opcode->operand1].long_value << vars[opcode->operand2].long_value;
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_BYTE:
        vars[opcode->operand0].byte_value
          = vars[opcode->operand1].byte_value >> vars[opcode->operand2].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_SHORT:
        vars[opcode->operand0].short_value
          = vars[opcode->operand1].short_value >> vars[opcode->operand2].short_value;
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_INT:
        vars[opcode->operand0].int_value
          = vars[opcode->operand1].int_value >> vars[opcode->operand2].int_value;
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_LONG:
        vars[opcode->operand0].long_value
          = vars[opcode->operand1].long_value >> vars[opcode->operand2].long_value;
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_BYTE:
        vars[opcode->operand0].byte_value
          = (int8_t)((uint8_t)vars[opcode->operand1].byte_value >> vars[opcode->operand2].byte_value);
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_SHORT:
        vars[opcode->operand0].short_value
          = (int16_t)((uint16_t)vars[opcode->operand1].short_value >> vars[opcode->operand2].short_value);
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_INT:
        vars[opcode->operand0].int_value
          = (int32_t)((uint32_t)vars[opcode->operand1].int_value >> vars[opcode->operand2].int_value);
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_LONG:
        vars[opcode->operand0].long_value
          = (int64_t)((uint64_t)vars[opcode->operand1].long_value >> vars[opcode->operand2].long_value);
        break;
      case SPVM_OPCODE_C_CODE_BIT_AND_BYTE:
        vars[opcode->operand0].byte_value
          = vars[opcode->operand1].byte_value & vars[opcode->operand2].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_BIT_AND_SHORT:
        vars[opcode->operand0].short_value
          = vars[opcode->operand1].short_value & vars[opcode->operand2].short_value;
        break;
      case SPVM_OPCODE_C_CODE_BIT_AND_INT:
        vars[opcode->operand0].int_value
          = vars[opcode->operand1].int_value & vars[opcode->operand2].int_value;
        break;
      case SPVM_OPCODE_C_CODE_BIT_AND_LONG:
        vars[opcode->operand0].long_value
          = vars[opcode->operand1].long_value & vars[opcode->operand2].long_value;
        break;
      case SPVM_OPCODE_C_CODE_BIT_OR_BYTE:
        vars[opcode->operand0].byte_value
          = vars[opcode->operand1].byte_value | vars[opcode->operand2].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_BIT_OR_SHORT:
        vars[opcode->operand0].short_value
          = vars[opcode->operand1].short_value | vars[opcode->operand2].short_value;
        break;
      case SPVM_OPCODE_C_CODE_BIT_OR_INT:
        vars[opcode->operand0].int_value
          = vars[opcode->operand1].int_value | vars[opcode->operand2].int_value;
        break;
      case SPVM_OPCODE_C_CODE_BIT_OR_LONG:
        vars[opcode->operand0].long_value
          = vars[opcode->operand1].long_value | vars[opcode->operand2].long_value;
        break;
      case SPVM_OPCODE_C_CODE_BIT_XOR_BYTE:
        vars[opcode->operand0].byte_value
          = vars[opcode->operand1].byte_value ^ vars[opcode->operand2].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_BIT_XOR_SHORT:
        vars[opcode->operand0].short_value
          = vars[opcode->operand1].short_value ^ vars[opcode->operand2].short_value;
        break;
      case SPVM_OPCODE_C_CODE_BIT_XOR_INT:
        vars[opcode->operand0].int_value
          = vars[opcode->operand1].int_value ^ vars[opcode->operand2].int_value;
        break;
      case SPVM_OPCODE_C_CODE_BIT_XOR_LONG:
        vars[opcode->operand0].long_value
          = vars[opcode->operand1].long_value ^ vars[opcode->operand2].long_value;
        break;
      case SPVM_OPCODE_C_CODE_NEGATE_BYTE:
        vars[opcode->operand0].byte_value = -vars[opcode->operand1].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_NEGATE_SHORT:
        vars[opcode->operand0].short_value = -vars[opcode->operand1].short_value;
        break;
      case SPVM_OPCODE_C_CODE_NEGATE_INT:
        vars[opcode->operand0].int_value = -vars[opcode->operand1].int_value;
        break;
      case SPVM_OPCODE_C_CODE_NEGATE_LONG:
        vars[opcode->operand0].long_value = -vars[opcode->operand1].long_value;
        break;
      case SPVM_OPCODE_C_CODE_NEGATE_FLOAT:
        vars[opcode->operand0].float_value = -vars[opcode->operand1].float_value;
        break;
      case SPVM_OPCODE_C_CODE_NEGATE_DOUBLE:
        vars[opcode->operand0].double_value = -vars[opcode->operand1].double_value;
        break;
      case SPVM_OPCODE_C_CODE_COMPLEMENT_BYTE:
        vars[opcode->operand0].byte_value = ~vars[opcode->operand1].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_COMPLEMENT_SHORT:
        vars[opcode->operand0].short_value = ~vars[opcode->operand1].short_value;
        break;
      case SPVM_OPCODE_C_CODE_COMPLEMENT_INT:
        vars[opcode->operand0].int_value = ~vars[opcode->operand1].int_value;
        break;
      case SPVM_OPCODE_C_CODE_COMPLEMENT_LONG:
        vars[opcode->operand0].long_value = ~vars[opcode->operand1].long_value;
        break;
      case SPVM_OPCODE_C_CODE_INC_BYTE:
        vars[opcode->operand0].byte_value += (int8_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_INC_SHORT:
        vars[opcode->operand0].short_value += (int16_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_INC_INT:
        vars[opcode->operand0].int_value += (int32_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_INC_LONG:
        vars[opcode->operand0].long_value += (int64_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_LONG:
        vars[opcode->operand0].long_value = (int64_t)vars[opcode->operand1].int_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_FLOAT:
        vars[opcode->operand0].float_value = (float)vars[opcode->operand1].int_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_DOUBLE:
        vars[opcode->operand0].double_value = (double)vars[opcode->operand1].int_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_INT:
        vars[opcode->operand0].int_value = (int32_t)vars[opcode->operand1].long_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_FLOAT:
        vars[opcode->operand0].float_value = (float)vars[opcode->operand1].long_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_DOUBLE:
        vars[opcode->operand0].double_value = (double)vars[opcode->operand1].long_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_INT:
        vars[opcode->operand0].int_value = (int32_t)vars[opcode->operand1].float_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_LONG:
        vars[opcode->operand0].long_value = (int64_t)vars[opcode->operand1].float_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_DOUBLE:
        vars[opcode->operand0].double_value = (double)vars[opcode->operand1].float_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_INT:
        vars[opcode->operand0].int_value = (int32_t)vars[opcode->operand1].double_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_LONG:
        vars[opcode->operand0].long_value = (int64_t)vars[opcode->operand1].double_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_FLOAT:
        vars[opcode->operand0].float_value = (float)vars[opcode->operand1].double_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_BYTE:
        vars[opcode->operand0].byte_value = (int8_t)(vars[opcode->operand1].int_value);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_SHORT:
        vars[opcode->operand0].short_value = (int16_t)(vars[opcode->operand1].int_value);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_INT:
        vars[opcode->operand0].int_value = (int32_t)vars[opcode->operand1].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_INT:
        vars[opcode->operand0].int_value = (int32_t)vars[opcode->operand1].short_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_LONG:
        vars[opcode->operand0].long_value = (int64_t)vars[opcode->operand1].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_FLOAT:
        vars[opcode->operand0].float_value = (float)vars[opcode->operand1].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_DOUBLE:
        vars[opcode->operand0].double_value = (double)vars[opcode->operand1].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_BYTE:
        vars[opcode->operand0].byte_value = (int8_t)vars[opcode->operand1].short_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_LONG:
        vars[opcode->operand0].long_value = (int64_t)vars[opcode->operand1].short_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_FLOAT:
        vars[opcode->operand0].float_value = (float)vars[opcode->operand1].short_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_DOUBLE:
        vars[opcode->operand0].double_value = (double)vars[opcode->operand1].short_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_BYTE:
        vars[opcode->operand0].byte_value = (int8_t)vars[opcode->operand1].long_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_SHORT:
        vars[opcode->operand0].short_value = (int16_t)vars[opcode->operand1].long_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_BYTE:
        vars[opcode->operand0].byte_value = (int8_t)vars[opcode->operand1].float_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_SHORT:
        vars[opcode->operand0].short_value = (int16_t)vars[opcode->operand1].float_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_BYTE:
        vars[opcode->operand0].byte_value = (int8_t)vars[opcode->operand1].double_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_SHORT:
        vars[opcode->operand0].short_value = (int16_t)vars[opcode->operand1].double_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_SHORT:
        vars[opcode->operand0].short_value = (int16_t)vars[opcode->operand1].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_BYTE:
        vars[opcode->operand0].byte_value = vars[opcode->operand1].byte_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_SHORT:
        vars[opcode->operand0].short_value = vars[opcode->operand1].short_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_INT:
        vars[opcode->operand0].int_value = vars[opcode->operand1].int_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_LONG:
        vars[opcode->operand0].long_value = vars[opcode->operand1].long_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_FLOAT:
        vars[opcode->operand0].float_value = vars[opcode->operand1].float_value;
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_DOUBLE:
        vars[opcode->operand0].double_value = vars[opcode->operand1].double_value;
        break;
      case SPVM_OPCODE_C_CODE_UNDEF:
        vars[opcode->operand0].object_value = NULL;
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_0:
        memset(&vars[opcode->operand0], 0, sizeof(int32_t));
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT2_0:
        memset(&vars[opcode->operand0], 0, sizeof(int64_t));
        break;
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_BYTE: {
        SPVM_API_OBJECT* array = vars[opcode->operand1].object_value;
        int32_t index = vars[opcode->operand2].int_value;
        if (__builtin_expect(array == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            goto label_SPVM_OPCODE_C_CODE_CROAK;
          }
          else {
            vars[opcode->operand0].byte_value = *(int8_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int8_t) * index);
            break;
          }
        }
      }
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_SHORT: {
        SPVM_API_OBJECT* array = vars[opcode->operand1].object_value;
        int32_t index = vars[opcode->operand2].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            goto label_SPVM_OPCODE_C_CODE_CROAK;
          }
          else {
            vars[opcode->operand0].short_value
              = *(int16_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int16_t) * index);
            break;
          }
        }
      }
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_INT: {
        SPVM_API_OBJECT* array = vars[opcode->operand1].object_value;
        int32_t index = vars[opcode->operand2].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            goto label_SPVM_OPCODE_C_CODE_CROAK;
          }
          else {
            vars[opcode->operand0].int_value = *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int32_t) * index);
            break;
          }
        }
      }
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_LONG: {
        SPVM_API_OBJECT* array = vars[opcode->operand1].object_value;
        int32_t index = vars[opcode->operand2].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            goto label_SPVM_OPCODE_C_CODE_CROAK;
          }
          else {
            vars[opcode->operand0].long_value = *(int64_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int64_t) * index);
            break;
          }
        }
      }
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_FLOAT: {
        SPVM_API_OBJECT* array = vars[opcode->operand1].object_value;
        int32_t index = vars[opcode->operand2].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            goto label_SPVM_OPCODE_C_CODE_CROAK;
          }
          else {
            vars[opcode->operand0].float_value = *(float*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(float) * index);
            break;
          }
        }
      }
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_DOUBLE: {
        SPVM_API_OBJECT* array = vars[opcode->operand1].object_value;
        int32_t index = vars[opcode->operand2].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            goto label_SPVM_OPCODE_C_CODE_CROAK;
          }
          else {
            vars[opcode->operand0].double_value = *(double*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(double) * index);
            break;
          }
        }
      }
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_OBJECT: {
        SPVM_API_OBJECT* array = vars[opcode->operand1].object_value;
        int32_t index = vars[opcode->operand2].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            goto label_SPVM_OPCODE_C_CODE_CROAK;
          }
          else {
            vars[opcode->operand0].object_value = *(SPVM_API_OBJECT**)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_OBJECT*) * index);
            break;
          }
        }
      }
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_BYTE: {
        SPVM_API_OBJECT* array = vars[opcode->operand0].object_value;
        int32_t index = vars[opcode->operand1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            goto label_SPVM_OPCODE_C_CODE_CROAK;
          }
          else {
            *(int8_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int8_t) * index) = vars[opcode->operand2].byte_value;
            break;
          }
        }
      }
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_SHORT: {
        SPVM_API_OBJECT* array = vars[opcode->operand0].object_value;
        int32_t index = vars[opcode->operand1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            goto label_SPVM_OPCODE_C_CODE_CROAK;
          }
          else {
            *(int16_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int16_t) * index) = vars[opcode->operand2].short_value;
            break;
          }
        }
      }
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_INT: {
        SPVM_API_OBJECT* array = vars[opcode->operand0].object_value;
        int32_t index = vars[opcode->operand1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            goto label_SPVM_OPCODE_C_CODE_CROAK;
          }
          else {
            *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int32_t) * index) = vars[opcode->operand2].int_value;
            break;
          }
        }
      }
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_LONG: {
        SPVM_API_OBJECT* array = vars[opcode->operand0].object_value;
        int32_t index = vars[opcode->operand1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            goto label_SPVM_OPCODE_C_CODE_CROAK;
          }
          else {
            *(int64_t*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int64_t) * index) = vars[opcode->operand2].long_value;
            break;
          }
        }
      }
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_FLOAT: {
        SPVM_API_OBJECT* array = vars[opcode->operand0].object_value;
        int32_t index = vars[opcode->operand1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            goto label_SPVM_OPCODE_C_CODE_CROAK;
          }
          else {
            *(float*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(float) * index) = vars[opcode->operand2].float_value;
            break;
          }
        }
      }
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_DOUBLE: {
        SPVM_API_OBJECT* array = vars[opcode->operand0].object_value;
        int32_t index = vars[opcode->operand1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            goto label_SPVM_OPCODE_C_CODE_CROAK;
          }
          else {
            *(double*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(double) * index) = vars[opcode->operand2].double_value;
            break;
          }
        }
      }
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_OBJECT: {
        
        SPVM_API_OBJECT* array = vars[opcode->operand0].object_value;
        int32_t index = vars[opcode->operand1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            goto label_SPVM_OPCODE_C_CODE_CROAK;
          }
          else {
            SPVM_API_OBJECT** object_address = (SPVM_API_OBJECT**)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_OBJECT*) * index);
            
            // Decrement old object reference count
            if (*object_address != NULL) {
              if (SPVM_INLINE_GET_REF_COUNT(*object_address) > 1) {
                SPVM_INLINE_DEC_REF_COUNT_ONLY(*object_address);
              }
              else {
                api->dec_ref_count(api, *object_address);
              }
            }
            
            // Store address
            *object_address = vars[opcode->operand2].object_value;

            // Increment new object reference count
            if (*object_address != NULL) {
              SPVM_INLINE_INC_REF_COUNT(*object_address);
            }
            break;
          }
        }
      }
      case SPVM_OPCODE_C_CODE_MOVE:
        vars[opcode->operand0] = vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_INC_REF_COUNT: {
        // Increment new value reference count
        if (vars[opcode->operand0].object_value != NULL) {
          SPVM_INLINE_INC_REF_COUNT(vars[opcode->operand0].object_value);
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_DEC_REF_COUNT: {
        // Decrement reference count
        if (vars[opcode->operand0].object_value != NULL) {
          if (SPVM_INLINE_GET_REF_COUNT(vars[opcode->operand0].object_value) > 1) {
            SPVM_INLINE_DEC_REF_COUNT_ONLY(vars[opcode->operand0].object_value);
          }
          else {
            api->dec_ref_count(api, vars[opcode->operand0].object_value);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_OBJECT: {
        // Get subroutine ID
        int32_t type_id = opcode->operand1;
        
        SPVM_API_OBJECT* object = api->new_object(api, type_id);
        
        // Push object
        vars[opcode->operand0].object_value = object;
        
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_BYTE_ARRAY: {
        
        // length
        int32_t length = vars[opcode->operand1].int_value;
        
        SPVM_API_OBJECT* object = api->new_byte_array(api, length);
        
        // Set array
        vars[opcode->operand0].object_value = object;
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_SHORT_ARRAY: {
        
        // length
        int32_t length = vars[opcode->operand1].int_value;
        
        SPVM_API_OBJECT* object = api->new_short_array(api, length);
        
        // Set array
        vars[opcode->operand0].object_value = object;
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_INT_ARRAY: {
        
        // length
        int32_t length = vars[opcode->operand1].int_value;
        
        SPVM_API_OBJECT* object = api->new_int_array(api, length);
        
        // Set array
        vars[opcode->operand0].object_value = object;
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_LONG_ARRAY: {
        
        // length
        int32_t length = vars[opcode->operand1].int_value;
        
        SPVM_API_OBJECT* object = api->new_long_array(api, length);
        
        // Set array
        vars[opcode->operand0].object_value = object;
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_FLOAT_ARRAY: {
        
        // length
        int32_t length = vars[opcode->operand1].int_value;
        
        SPVM_API_OBJECT* object = api->new_float_array(api, length);
        
        // Set array
        vars[opcode->operand0].object_value = object;
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_DOUBLE_ARRAY: {
        
        // length
        int32_t length = vars[opcode->operand1].int_value;
        
        SPVM_API_OBJECT* object = api->new_double_array(api, length);
        
        // Set array
        vars[opcode->operand0].object_value = object;
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_OBJECT_ARRAY: {
        int32_t element_type_id = opcode->operand1;
        
        // length
        int32_t length = vars[opcode->operand2].int_value;
        
        SPVM_API_OBJECT* object = api->new_object_array(api, element_type_id, length);
        
        // Set object
        vars[opcode->operand0].object_value = object;
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_STRING: {
        int32_t name_id = opcode->operand1;
        
        SPVM_API_OBJECT* string = api->new_string(api, (char*)&constant_pool[name_id + 1], constant_pool[name_id]);

        // Set string
        vars[opcode->operand0].object_value = string;
        break;
      }
      case SPVM_OPCODE_C_CODE_ARRAY_LENGTH:
        if (vars[opcode->operand1].object_value == NULL) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Can't get array length of undef value.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          vars[opcode->operand0].int_value = *(int32_t*)((intptr_t)vars[opcode->operand1].object_value + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET);
        }
        break;
      case SPVM_OPCODE_C_CODE_GET_FIELD_BYTE: {
        SPVM_API_OBJECT* object = vars[opcode->operand1].object_value;
        
        int32_t field_id = opcode->operand2;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          vars[opcode->operand0].byte_value = *(int8_t*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_GET_FIELD_SHORT: {
        SPVM_API_OBJECT* object = vars[opcode->operand1].object_value;
        
        int32_t field_id = opcode->operand2;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          vars[opcode->operand0].short_value = *(int16_t*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_GET_FIELD_INT: {
        SPVM_API_OBJECT* object = vars[opcode->operand1].object_value;
        
        int32_t field_id = opcode->operand2;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          vars[opcode->operand0].int_value = *(int32_t*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_GET_FIELD_LONG: {
        SPVM_API_OBJECT* object = vars[opcode->operand1].object_value;
        
        int32_t field_id = opcode->operand2;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          vars[opcode->operand0].long_value = *(int64_t*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_GET_FIELD_FLOAT: {
        SPVM_API_OBJECT* object = vars[opcode->operand1].object_value;
        
        int32_t field_id = opcode->operand2;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          vars[opcode->operand0].float_value = *(float*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_GET_FIELD_DOUBLE: {
        SPVM_API_OBJECT* object = vars[opcode->operand1].object_value;
        
        int32_t field_id = opcode->operand2;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          vars[opcode->operand0].double_value = *(double*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_GET_FIELD_OBJECT: {
        SPVM_API_OBJECT* object = vars[opcode->operand1].object_value;
        
        int32_t field_id = opcode->operand2;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          vars[opcode->operand0].object_value = *(SPVM_API_OBJECT**)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_BYTE: {
        SPVM_API_OBJECT* object = vars[opcode->operand0].object_value;
        int32_t field_id = opcode->operand1;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        
        *(int8_t*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset) = vars[opcode->operand2].byte_value;
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_SHORT: {
        SPVM_API_OBJECT* object = vars[opcode->operand0].object_value;
        int32_t field_id = opcode->operand1;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        
        *(int16_t*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset) = vars[opcode->operand2].short_value;
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_INT: {
        SPVM_API_OBJECT* object = vars[opcode->operand0].object_value;
        int32_t field_id = opcode->operand1;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        
        *(int32_t*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset) = vars[opcode->operand2].int_value;
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_LONG: {
        SPVM_API_OBJECT* object = vars[opcode->operand0].object_value;
        int32_t field_id = opcode->operand1;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        
        *(int64_t*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset) = vars[opcode->operand2].long_value;
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_FLOAT: {
        SPVM_API_OBJECT* object = vars[opcode->operand0].object_value;
        int32_t field_id = opcode->operand1;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        
        *(float*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset) = vars[opcode->operand2].float_value;
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_DOUBLE: {
        SPVM_API_OBJECT* object = vars[opcode->operand0].object_value;
        int32_t field_id = opcode->operand1;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        
        *(double*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset) = vars[opcode->operand2].double_value;
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_OBJECT: {
        SPVM_API_OBJECT* object = vars[opcode->operand0].object_value;
        int32_t field_id = opcode->operand1;

        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        
        SPVM_API_OBJECT** field_address = (SPVM_API_OBJECT**)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset);
        
        if(*field_address != NULL) {
          // If object is weak, unweaken
          if (SPVM_INLINE_ISWEAK(*field_address)) {
            api->unweaken(api, field_address);
          }
          
          if (SPVM_INLINE_GET_REF_COUNT(*field_address) > 1) {
            SPVM_INLINE_DEC_REF_COUNT_ONLY(*field_address);
          }
          else {
            api->dec_ref_count(api, *field_address);
          }
        }
        
        *field_address = vars[opcode->operand2].object_value;
        
        if(*field_address != NULL) {
          SPVM_INLINE_INC_REF_COUNT(*field_address);
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_WEAKEN_FIELD_OBJECT: {
        
        SPVM_API_OBJECT* object = vars[opcode->operand0].object_value;
        int32_t field_id = opcode->operand1;
        
        api->weaken_object_field(api, object, field_id);
        
        if (SPVM_INLINE_GET_EXCEPTION()) {
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_STRING: {
        vars[opcode->operand0].object_value = api->concat_string_string(api, vars[opcode->operand1].object_value, vars[opcode->operand2].object_value);
        
        if (vars[opcode->operand0].object_value == NULL) {
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        
        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_BYTE: {
        vars[opcode->operand0].object_value = api->concat_string_byte(api, vars[opcode->operand1].object_value, vars[opcode->operand2].byte_value);
        
        if (vars[opcode->operand0].object_value == NULL) {
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }

        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_SHORT: {
        vars[opcode->operand0].object_value = api->concat_string_short(api, vars[opcode->operand1].object_value, vars[opcode->operand2].short_value);
        
        if (vars[opcode->operand0].object_value == NULL) {
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        
        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_INT: {
        vars[opcode->operand0].object_value = api->concat_string_int(api, vars[opcode->operand1].object_value, vars[opcode->operand2].int_value);
        
        if (vars[opcode->operand0].object_value == NULL) {
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }

        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_LONG: {
        vars[opcode->operand0].object_value = api->concat_string_long(api, vars[opcode->operand1].object_value, vars[opcode->operand2].long_value);
        
        if (vars[opcode->operand0].object_value == NULL) {
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }

        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_FLOAT: {
       vars[opcode->operand0].object_value = api->concat_string_float(api, vars[opcode->operand1].object_value, vars[opcode->operand2].float_value);
        
        if (vars[opcode->operand0].object_value == NULL) {
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }

        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_DOUBLE: {
        vars[opcode->operand0].object_value = api->concat_string_double(api, vars[opcode->operand1].object_value, vars[opcode->operand2].double_value);
        
        if (vars[opcode->operand0].object_value == NULL) {
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        
        break;
      }
      case SPVM_OPCODE_C_CODE_PUSH_EVAL: {
        // Next operation
        int16_t jump_offset_abs = opcode->operand0;
        
        eval_stack_top++;
        eval_stack[eval_stack_top] = jump_offset_abs;
        
        break;
      }
      case SPVM_OPCODE_C_CODE_POP_EVAL: {
        eval_stack_top--;
        
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_EXCEPTION_VAR: {
        vars[opcode->operand0].object_value = SPVM_INLINE_GET_EXCEPTION();
        
        break;
      }
      case SPVM_OPCODE_C_CODE_STORE_EXCEPTION_VAR: {
        
        api->set_exception(api, vars[opcode->operand0].object_value);
        
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_BYTE: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand1;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        vars[opcode->operand0].byte_value = package_vars[package_var_id].byte_value;
        
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_SHORT: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand1;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        vars[opcode->operand0].short_value = package_vars[package_var_id].short_value;
        
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_INT: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand1;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        vars[opcode->operand0].int_value = package_vars[package_var_id].int_value;
        
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_LONG: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand1;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        vars[opcode->operand0].long_value = package_vars[package_var_id].long_value;
        
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_FLOAT: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand1;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        vars[opcode->operand0].float_value = package_vars[package_var_id].float_value;
        
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_DOUBLE: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand1;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        vars[opcode->operand0].double_value = package_vars[package_var_id].double_value;
        
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_OBJECT: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand1;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        vars[opcode->operand0].object_value = package_vars[package_var_id].object_value;
        
        break;
      }
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_BYTE: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand0;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        package_vars[package_var_id].byte_value = vars[opcode->operand1].byte_value;
        
        break;
      }
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_SHORT: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand0;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        package_vars[package_var_id].short_value = vars[opcode->operand1].short_value;
        
        break;
      }
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_INT: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand0;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        package_vars[package_var_id].int_value = vars[opcode->operand1].int_value;
        
        break;
      }
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_LONG: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand0;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        package_vars[package_var_id].long_value = vars[opcode->operand1].long_value;
        
        break;
      }
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_FLOAT: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand0;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        package_vars[package_var_id].float_value = vars[opcode->operand1].float_value;
        
        break;
      }
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_DOUBLE: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand0;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        package_vars[package_var_id].double_value = vars[opcode->operand1].double_value;
        
        break;
      }
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_OBJECT: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand0;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        // Decrement reference count
        if (package_vars[package_var_id].object_value != NULL) {
          if (SPVM_INLINE_GET_REF_COUNT(package_vars[package_var_id].object_value) > 1) {
            SPVM_INLINE_DEC_REF_COUNT_ONLY(package_vars[package_var_id].object_value);
          }
          else {
            api->dec_ref_count(api, package_vars[package_var_id].object_value);
          }
        }
        
        // Store object
        package_vars[package_var_id].object_value = vars[opcode->operand1].object_value;
        
        // Increment new value reference count
        if (package_vars[package_var_id].object_value != NULL) {
          SPVM_INLINE_INC_REF_COUNT(package_vars[package_var_id].object_value);
        }
        
        break;
      }
      case SPVM_OPCODE_C_CODE_PUSH_ARG:
        call_sub_arg_stack_top++;
        call_sub_arg_stack[call_sub_arg_stack_top].int_value = opcode->operand0;
        
        break;
      case SPVM_OPCODE_C_CODE_CALL_SUB:
      {
        // Get subroutine ID
        int32_t call_sub_id = opcode->operand1;

        // Constant pool sub
        SPVM_CONSTANT_POOL_SUB* constant_pool_SUB_YYY = (SPVM_CONSTANT_POOL_SUB*)&constant_pool[call_sub_id];
        
        // Call subroutine return type id
        int32_t SPVM_INFO_SUB_YYY_RETURN_TYPE_ID = constant_pool_SUB_YYY->return_type_id;
        
        // Constant pool type
        SPVM_CONSTANT_POOL_TYPE* SPVM_INFO_SUB_YYY_RETURN_TYPE = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[SPVM_INFO_SUB_YYY_RETURN_TYPE_ID];
        
        // Return type code
        int32_t SPVM_INFO_SUB_YYY_RETURN_TYPE_CODE = SPVM_INFO_SUB_YYY_RETURN_TYPE->code;
        
        // Subroutine argument length
        int32_t SPVM_INFO_SUB_YYY_ARGS_LENGTH = constant_pool_SUB_YYY->args_length;

        // Subroutine argument length
        int32_t SPVM_INFO_SUB_YYY_IS_VOID = constant_pool_SUB_YYY->is_void;
        
        call_sub_arg_stack_top -= SPVM_INFO_SUB_YYY_ARGS_LENGTH;
        
        SPVM_API_VALUE args[255];
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
          vars[opcode->operand0].byte_value = api->call_byte_sub(api, call_sub_id, (SPVM_API_VALUE*)args);
        }
        else if (SPVM_INFO_SUB_YYY_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_SHORT) {
          vars[opcode->operand0].short_value = api->call_short_sub(api, call_sub_id, (SPVM_API_VALUE*)args);
        }
        else if (SPVM_INFO_SUB_YYY_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_INT) {
          vars[opcode->operand0].int_value = api->call_int_sub(api, call_sub_id, (SPVM_API_VALUE*)args);
        }
        else if (SPVM_INFO_SUB_YYY_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_LONG) {
          vars[opcode->operand0].long_value = api->call_long_sub(api, call_sub_id, (SPVM_API_VALUE*)args);
        }
        else if (SPVM_INFO_SUB_YYY_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_FLOAT) {
          vars[opcode->operand0].float_value = api->call_float_sub(api, call_sub_id, (SPVM_API_VALUE*)args);
        }
        else if (SPVM_INFO_SUB_YYY_RETURN_TYPE_CODE == SPVM_INFO_TYPE_CODE_DOUBLE) {
          vars[opcode->operand0].double_value = api->call_double_sub(api, call_sub_id, (SPVM_API_VALUE*)args);
        }
        else {
          vars[opcode->operand0].object_value = api->call_object_sub(api, call_sub_id, (SPVM_API_VALUE*)args);
        }
        
        if (SPVM_INLINE_GET_EXCEPTION()) {
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          // Next operation
          opcode_index++;
        }
        
        continue;
      }
      case SPVM_OPCODE_C_CODE_RETURN_BYTE:
      case SPVM_OPCODE_C_CODE_RETURN_SHORT:
      case SPVM_OPCODE_C_CODE_RETURN_INT:
      case SPVM_OPCODE_C_CODE_RETURN_LONG:
      case SPVM_OPCODE_C_CODE_RETURN_FLOAT:
      case SPVM_OPCODE_C_CODE_RETURN_DOUBLE:
      {
        // Get return value
        return_value = vars[opcode->operand0];
          
        // Decrement my vars which is arguments - decrement only
        {
          int32_t i;
          for (i = 0; i < SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH; i++) {
            int32_t my_var_index = constant_pool[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
            SPVM_API_OBJECT* object = vars[my_var_index].object_value;
            
            if (object != NULL) {
              SPVM_INLINE_DEC_REF_COUNT_ONLY(object);
            }
          }
        }

        // Decrement my vars which is not arguments - decrement and if reference count is 0, free object
        {
          int32_t i;
          for (i = SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH; i < SPVM_INFO_SUB_XXX_OBJECT_MYS_LENGTH; i++) {
            int32_t my_var_index = constant_pool[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
            SPVM_API_OBJECT* object = vars[my_var_index].object_value;
            
            if (object != NULL) {
              if (SPVM_INLINE_GET_REF_COUNT(object) > 1) {
                SPVM_INLINE_DEC_REF_COUNT_ONLY(object);
              }
              else {
                api->dec_ref_count(api, object);
              }
            }
          }
        }
        
        // No exception
        SPVM_INLINE_SET_EXCEPTION_NULL();
        
        return return_value;
      }
      case SPVM_OPCODE_C_CODE_RETURN_OBJECT: {

        return_value = vars[opcode->operand0];
          
        // Increment ref count of return value not to release by decrement
        if (return_value.object_value != NULL) {
          SPVM_INLINE_INC_REF_COUNT(return_value.object_value);
        }
        
        // Decrement my vars which is arguments - decrement only
        {
          int32_t i;
          for (i = 0; i < SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH; i++) {
            int32_t my_var_index = constant_pool[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
            SPVM_API_OBJECT* object = vars[my_var_index].object_value;
            
            if (object != NULL) {
              SPVM_INLINE_DEC_REF_COUNT_ONLY(object);
            }
          }
        }

        // Decrement my vars which is not arguments - decrement and if reference count is 0, free object
        {
          int32_t i;
          for (i = SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH; i < SPVM_INFO_SUB_XXX_OBJECT_MYS_LENGTH; i++) {
            int32_t my_var_index = constant_pool[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
            SPVM_API_OBJECT* object = vars[my_var_index].object_value;
            
            if (object != NULL) {
              if (SPVM_INLINE_GET_REF_COUNT(object) > 1) {
                SPVM_INLINE_DEC_REF_COUNT_ONLY(object);
              }
              else {
                api->dec_ref_count(api, object);
              }
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
      case SPVM_OPCODE_C_CODE_RETURN_VOID: {

        memset(&return_value, 0, sizeof(SPVM_API_VALUE));
        
        // Decrement object my vars reference count
        {
          int32_t i;
          for (i = 0; i < SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH; i++) {
            int32_t my_var_index = constant_pool[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
            SPVM_API_OBJECT* object = vars[my_var_index].object_value;
            
            if (object != NULL) {
              SPVM_INLINE_DEC_REF_COUNT_ONLY(object);
            }
          }
        }
        {
          int32_t i;
          for (i = SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH; i < SPVM_INFO_SUB_XXX_OBJECT_MYS_LENGTH; i++) {
            int32_t my_var_index = constant_pool[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
            SPVM_API_OBJECT* object = vars[my_var_index].object_value;
            
            if (object != NULL) {
              if (SPVM_INLINE_GET_REF_COUNT(object) > 1) {
                SPVM_INLINE_DEC_REF_COUNT_ONLY(object);
              }
              else {
                api->dec_ref_count(api, object);
              }
            }
          }
        }
        
        // No exception
        SPVM_INLINE_SET_EXCEPTION_NULL();

        return return_value;
      }
      case SPVM_OPCODE_C_CODE_CROAK: {
        
        label_SPVM_OPCODE_C_CODE_CROAK:
        
        // Catch exception
        if (eval_stack_top > -1) {
          
          int32_t jump_offset_abs = eval_stack[eval_stack_top];
          eval_stack_top--;
          
          opcode_index = SPVM_INFO_SUB_XXX_OPCODE_BASE + jump_offset_abs;
          continue;
        }
        
        // Decrement my vars which is arguments - decrement only
        {
          int32_t i;
          for (i = 0; i < SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH; i++) {
            int32_t my_var_index = constant_pool[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
            SPVM_API_OBJECT* object = vars[my_var_index].object_value;
            
            if (object != NULL) {
              SPVM_INLINE_DEC_REF_COUNT_ONLY(object);
            }
          }
        }

        // Decrement my vars which is not arguments - decrement and if reference count is 0, free object
        {
          int32_t i;
          for (i = SPVM_INFO_SUB_XXX_OBJECT_ARGS_LENGTH; i < SPVM_INFO_SUB_XXX_OBJECT_MYS_LENGTH; i++) {
            int32_t my_var_index = constant_pool[SPVM_INFO_SUB_XXX_OBJECT_MYS_BASE + i];
            SPVM_API_OBJECT* object = vars[my_var_index].object_value;
            
            if (object != NULL) {
              if (SPVM_INLINE_GET_REF_COUNT(object) > 1) {
                SPVM_INLINE_DEC_REF_COUNT_ONLY(object);
              }
              else {
                api->dec_ref_count(api, object);
              }
            }
          }
        }
        
        if (SPVM_INFO_DEBUG) {
          // Sub name
          const char* sub_name = (char*)&constant_pool[SPVM_INFO_SUB_XXX_ABS_NAME_ID + 1];
          
          // File name
          const char* file_name = (char*)&constant_pool[SPVM_INFO_SUB_XXX_FILE_NAME_ID + 1];
          
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
          
          // Set exception
          api->set_exception(api, new_exception);
        }
        
        memset(&return_value, 0, sizeof(SPVM_API_VALUE));
        
        return return_value;
      }
      case SPVM_OPCODE_C_CODE_TABLE_SWITCH: {
        int32_t* intcodes = (int32_t*)SPVM_INFO_OPCODES;
        int32_t intcode_index = opcode_index * 8;
        
        // default offset
        int32_t default_offset = intcodes[intcode_index + 2];
        
        // min
        int32_t min = intcodes[intcode_index + 3];
        
        // max
        int32_t max = intcodes[intcode_index + 4];
        
        if (vars[opcode->operand0].int_value >= min && vars[opcode->operand0].int_value <= max) {
          int32_t branch_offset
            = *(int32_t*)((&intcodes[intcode_index + 8]) + (vars[opcode->operand0].int_value - min));
          opcode_index += branch_offset;
        }
        else {
          opcode_index += default_offset;
        }
        
        continue;
      }
      case SPVM_OPCODE_C_CODE_LOOKUP_SWITCH: {
        int32_t* intcodes = (int32_t*)SPVM_INFO_OPCODES;
        int32_t intcode_index = opcode_index * 8;
        
        // 1  default
        // 5  npare
        // 9  match1 offset1 // min
        // 17 match2 offset2
        // 25 match3 offset3 // max
        
        // default offset
        int32_t default_offset = intcodes[intcode_index + 2];
        
        // npare
        int32_t pair_count = intcodes[intcode_index + 3];
        
        // min
        int32_t min = intcodes[intcode_index + 8];
        
        // max
        int32_t max = intcodes[intcode_index + 8 + (pair_count - 1) * 2];
        
        if (vars[opcode->operand0].int_value >= min && vars[opcode->operand0].int_value <= max) {
          // 2 branch searching
          int32_t cur_min_pos = 0;
          int32_t cur_max_pos = pair_count - 1;

          while (1) {
            if (cur_max_pos < cur_min_pos) {
              opcode_index += default_offset;
              break;
            }
            int32_t cur_half_pos = cur_min_pos + (cur_max_pos - cur_min_pos) / 2;
            int32_t cur_half = intcodes[intcode_index + 8 + (cur_half_pos * 2)];
            
            if (vars[opcode->operand0].int_value > cur_half) {
              cur_min_pos = cur_half_pos + 1;
            }
            else if (vars[opcode->operand0].int_value < cur_half) {
              cur_max_pos = cur_half_pos - 1;
            }
            else {
              int32_t branch_offset = intcodes[intcode_index + 8 + (cur_half_pos * 2) + 1];
              opcode_index += branch_offset;
              break;
            }
          }
        }
        else {
          opcode_index += default_offset;
        }
        
        continue;
      }
      case SPVM_OPCODE_C_CODE_GOTO:
        opcode_index += opcode->operand0;
        continue;
      case SPVM_OPCODE_C_CODE_IF_EQ_ZERO: {
        if (condition_flag == 0) {
          opcode_index += opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_IF_NE_ZERO: {
        if (condition_flag) {
          opcode_index += opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_CURRENT_LINE:
        current_line = opcode->operand0;
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT:
        memcpy(&vars[opcode->operand0], &constant_pool[opcode->operand1], sizeof(int32_t));
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT2:
        memcpy(&vars[opcode->operand0], &constant_pool[opcode->operand1], sizeof(int64_t));
        break;
    }
    opcode_index++;
  }
}
