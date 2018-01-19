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
#define SPVM_INFO_RUNTIME_EXCEPTION_BYTE_OFFSET ((int32_t)offsetof(SPVM_RUNTIME, exception))
#define SPVM_INFO_TYPE_CODE_VOID (SPVM_TYPE_C_CODE_VOID)
#define SPVM_INFO_TYPE_CODE_BYTE (SPVM_TYPE_C_CODE_BYTE)
#define SPVM_INFO_TYPE_CODE_SHORT (SPVM_TYPE_C_CODE_SHORT)
#define SPVM_INFO_TYPE_CODE_INT (SPVM_TYPE_C_CODE_INT)
#define SPVM_INFO_TYPE_CODE_LONG (SPVM_TYPE_C_CODE_LONG)
#define SPVM_INFO_TYPE_CODE_FLOAT (SPVM_TYPE_C_CODE_FLOAT)
#define SPVM_INFO_TYPE_CODE_DOUBLE (SPVM_TYPE_C_CODE_DOUBLE)

#define SPVM_INLINE_GET_REF_COUNT(object) ((*(SPVM_API_int*)((intptr_t)object + SPVM_INFO_OBJECT_REF_COUNT_BYTE_OFFSET)))
#define SPVM_INLINE_INC_REF_COUNT(object) ((*(SPVM_API_int*)((intptr_t)object + SPVM_INFO_OBJECT_REF_COUNT_BYTE_OFFSET))++)
#define SPVM_INLINE_DEC_REF_COUNT_ONLY(object) ((*(SPVM_API_int*)((intptr_t)object + SPVM_INFO_OBJECT_REF_COUNT_BYTE_OFFSET))--)
#define SPVM_INLINE_GET_EXCEPTION() (*(SPVM_API_OBJECT**)((intptr_t)runtime + SPVM_INFO_RUNTIME_EXCEPTION_BYTE_OFFSET))
#define SPVM_INLINE_SET_EXCEPTION_NULL() \
  do { \
    if ((*(SPVM_API_OBJECT**)((intptr_t)runtime + SPVM_INFO_RUNTIME_EXCEPTION_BYTE_OFFSET)) != NULL) { \
      api->dec_ref_count(api, (*(SPVM_API_OBJECT**)((intptr_t)runtime + SPVM_INFO_RUNTIME_EXCEPTION_BYTE_OFFSET))); \
    } \
    (*(SPVM_API_OBJECT**)((intptr_t)runtime + SPVM_INFO_RUNTIME_EXCEPTION_BYTE_OFFSET)) = NULL; \
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
  SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&constant_pool[sub_id];
  
  // Subroutine object my length
  int32_t sub_object_mys_length = constant_pool_sub->object_mys_length;
  
  // Subroutine object my base index
  int32_t sub_object_mys_base = constant_pool_sub->object_mys_base;
  
  // Subroutine return type id
  int32_t sub_return_type_id = constant_pool_sub->return_type_id;
  
  // Subroutine is native
  int32_t sub_is_native = constant_pool_sub->is_native;
  
  // Subroutine object args length
  int32_t sub_object_args_length = constant_pool_sub->object_args_length;

  // Subroutine object args length
  int32_t sub_object_args_base = constant_pool_sub->object_args_base;
  
  // Bytecodes
  SPVM_OPCODE* opcodes = runtime->opcodes;
  
  // Opcode base
  int32_t sub_opcode_base = constant_pool_sub->opcode_base;
  
  // Args length
  int32_t args_length = constant_pool_sub->args_length;
  
  // Native address
  void* sub_native_address = constant_pool_sub->native_address;
  
  // Constant pool type
  SPVM_CONSTANT_POOL_TYPE* sub_return_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[sub_return_type_id];

  // Return type code
  int32_t sub_return_type_code = sub_return_type->code;
  
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
  
  // Croak flag
  int32_t croak_flag = 0;
  
  // Copy arguments
  memcpy(vars, args, args_length * sizeof(SPVM_API_VALUE));

  // Set exception to NULL at start of subroutine
  SPVM_INLINE_SET_EXCEPTION_NULL();
  
  // Call native sub
  if (sub_is_native) {

    // Call native subroutine
    if (sub_return_type_code == SPVM_INFO_TYPE_CODE_VOID) {
      void (*native_address)(SPVM_API*, SPVM_API_VALUE*) = sub_native_address;
      (*native_address)(api, (SPVM_API_VALUE*)vars);
    }
    else if (sub_return_type_code == SPVM_INFO_TYPE_CODE_BYTE) {
      SPVM_API_byte (*native_address)(SPVM_API*, SPVM_API_VALUE*) = sub_native_address;
      SPVM_API_byte return_value_native = (*native_address)(api, (SPVM_API_VALUE*)vars);
      *(SPVM_API_byte*)&return_value = return_value_native;
    }
    else if (sub_return_type_code == SPVM_INFO_TYPE_CODE_SHORT) {
      SPVM_API_short (*native_address)(SPVM_API*, SPVM_API_VALUE*) = sub_native_address;
      SPVM_API_short return_value_native = (*native_address)(api, (SPVM_API_VALUE*)vars);
      *(SPVM_API_short*)&return_value = return_value_native;
    }
    else if (sub_return_type_code == SPVM_INFO_TYPE_CODE_INT) {
      SPVM_API_int (*native_address)(SPVM_API*, SPVM_API_VALUE*) = sub_native_address;
      SPVM_API_int return_value_native = (*native_address)(api, (SPVM_API_VALUE*)vars);
      *(SPVM_API_int*)&return_value = return_value_native;
    }
    else if (sub_return_type_code == SPVM_INFO_TYPE_CODE_LONG) {
      SPVM_API_long (*native_address)(SPVM_API*, SPVM_API_VALUE*) = sub_native_address;
      SPVM_API_long return_value_native = (*native_address)(api, (SPVM_API_VALUE*)vars);
      *(SPVM_API_long*)&return_value = return_value_native;
    }
    else if (sub_return_type_code == SPVM_INFO_TYPE_CODE_FLOAT) {
      float (*native_address)(SPVM_API*, SPVM_API_VALUE*) = sub_native_address;
      float return_value_native = (*native_address)(api, (SPVM_API_VALUE*)vars);
      *(float*)&return_value = return_value_native;
    }
    else if (sub_return_type_code == SPVM_INFO_TYPE_CODE_DOUBLE) {
      double (*native_address)(SPVM_API*, SPVM_API_VALUE*) = sub_native_address;
      double return_value_native = (*native_address)(api, (SPVM_API_VALUE*)vars);
      *(double*)&return_value = return_value_native;
    }
    else {
      SPVM_API_OBJECT* (*native_address)(SPVM_API*, SPVM_API_VALUE*) = sub_native_address;
      SPVM_API_OBJECT* return_value_native = (*native_address)(api, (SPVM_API_VALUE*)vars);
      return_value.object_value = return_value_native;
    }
    return return_value;
  }
  
  // Call normal sub
  // If arg is object, increment reference count
  {
    int32_t i;
    for (i = 0; i < sub_object_args_length; i++) {
      int32_t arg_index = constant_pool[sub_object_args_base + i];
      
      SPVM_API_OBJECT* object = vars[arg_index].object_value;
      if (object != NULL) {
        SPVM_INLINE_INC_REF_COUNT(object);
      }
    }
  }
  
  register int32_t opcode_index = sub_opcode_base;
  
  while (1) {
    SPVM_OPCODE* opcode = &(opcodes[opcode_index]);
    
    switch (opcode->code) {
      case SPVM_OPCODE_C_CODE_NOP:
        abort();
      case SPVM_OPCODE_C_CODE_BOOL_BYTE:
        condition_flag = !!*(SPVM_API_byte*)&vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_CODE_BOOL_SHORT:
        condition_flag = !!*(SPVM_API_short*)&vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_CODE_BOOL_INT:
        condition_flag = !!*(SPVM_API_int*)&vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_CODE_BOOL_LONG:
        condition_flag = !!*(SPVM_API_long*)&vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_CODE_BOOL_FLOAT:
        condition_flag = !!*(float*)&vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_CODE_BOOL_DOUBLE:
        condition_flag = !!*(double*)&vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_CODE_BOOL_OBJECT:
        condition_flag = !!*(SPVM_API_OBJECT**)&vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_CODE_IS_UNDEF:
        condition_flag = *(SPVM_API_OBJECT**)&vars[opcode->operand0] == NULL;
        break;
      case SPVM_OPCODE_C_CODE_IS_NOT_UNDEF:
        condition_flag = *(SPVM_API_OBJECT**)&vars[opcode->operand0] != NULL;
        break;
      case SPVM_OPCODE_C_CODE_EQ_BYTE:
        condition_flag = *(SPVM_API_byte*)&vars[opcode->operand0] == *(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_EQ_SHORT:
        condition_flag = *(SPVM_API_short*)&vars[opcode->operand0] == *(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_EQ_INT:
        condition_flag = *(SPVM_API_int*)&vars[opcode->operand0] == *(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_EQ_LONG:
        condition_flag = *(SPVM_API_long*)&vars[opcode->operand0] == *(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_EQ_FLOAT:
        condition_flag = *(float*)&vars[opcode->operand0] == *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_EQ_DOUBLE:
        condition_flag = *(double*)&vars[opcode->operand0] == *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_EQ_OBJECT:
        condition_flag = *(SPVM_API_OBJECT**)&vars[opcode->operand0] == *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_NE_BYTE:
        condition_flag = *(SPVM_API_byte*)&vars[opcode->operand0] != *(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_NE_SHORT:
        condition_flag = *(SPVM_API_short*)&vars[opcode->operand0] != *(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_NE_INT:
        condition_flag = *(SPVM_API_int*)&vars[opcode->operand0] != *(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_NE_LONG:
        condition_flag = *(SPVM_API_long*)&vars[opcode->operand0] != *(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_NE_FLOAT:
        condition_flag = *(float*)&vars[opcode->operand0] != *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_NE_DOUBLE:
        condition_flag = *(double*)&vars[opcode->operand0] != *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_NE_OBJECT:
        condition_flag = *(SPVM_API_OBJECT**)&vars[opcode->operand0] != *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_GT_BYTE:
        condition_flag = *(SPVM_API_byte*)&vars[opcode->operand0] > *(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_GT_SHORT:
        condition_flag = *(SPVM_API_short*)&vars[opcode->operand0] > *(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_GT_INT:
        condition_flag = *(SPVM_API_int*)&vars[opcode->operand0] > *(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_GT_LONG:
        condition_flag = *(SPVM_API_long*)&vars[opcode->operand0] > *(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_GT_FLOAT:
        condition_flag = *(float*)&vars[opcode->operand0] > *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_GT_DOUBLE:
        condition_flag = *(double*)&vars[opcode->operand0] > *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_GE_BYTE:
        condition_flag = *(SPVM_API_byte*)&vars[opcode->operand0] >= *(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_GE_SHORT:
        condition_flag = *(SPVM_API_short*)&vars[opcode->operand0] >= *(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_GE_INT:
        condition_flag = *(SPVM_API_int*)&vars[opcode->operand0] >= *(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_GE_LONG:
        condition_flag = *(SPVM_API_long*)&vars[opcode->operand0] >= *(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_GE_FLOAT:
        condition_flag = *(float*)&vars[opcode->operand0] >= *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_GE_DOUBLE:
        condition_flag = *(double*)&vars[opcode->operand0] >= *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_LT_BYTE:
        condition_flag = *(SPVM_API_byte*)&vars[opcode->operand0] < *(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_LT_SHORT:
        condition_flag = *(SPVM_API_short*)&vars[opcode->operand0] < *(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_LT_INT:
        condition_flag = *(SPVM_API_int*)&vars[opcode->operand0] < *(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_LT_LONG:
        condition_flag = *(SPVM_API_long*)&vars[opcode->operand0] < *(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_LT_FLOAT:
        condition_flag = *(float*)&vars[opcode->operand0] < *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_LT_DOUBLE:
        condition_flag = *(double*)&vars[opcode->operand0] < *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_LE_BYTE:
        condition_flag = *(SPVM_API_byte*)&vars[opcode->operand0] <= *(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_LE_SHORT:
        condition_flag = *(SPVM_API_short*)&vars[opcode->operand0] <= *(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_LE_INT:
        condition_flag = *(SPVM_API_int*)&vars[opcode->operand0] <= *(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_LE_LONG:
        condition_flag = *(SPVM_API_long*)&vars[opcode->operand0] <= *(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_LE_FLOAT:
        condition_flag = *(float*)&vars[opcode->operand0] <= *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_LE_DOUBLE:
        condition_flag = *(double*)&vars[opcode->operand0] <= *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_ADD_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = *(SPVM_API_byte*)&vars[opcode->operand1] + *(SPVM_API_byte*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_ADD_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = *(SPVM_API_short*)&vars[opcode->operand1] + *(SPVM_API_short*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_ADD_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)&vars[opcode->operand1] + *(SPVM_API_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_ADD_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = *(SPVM_API_long*)&vars[opcode->operand1] + *(SPVM_API_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_ADD_FLOAT:
        *(float*)&vars[opcode->operand0] = *(float*)&vars[opcode->operand1] + *(float*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_ADD_DOUBLE:
        *(double*)&vars[opcode->operand0] = *(double*)&vars[opcode->operand1] + *(double*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_SUBTRACT_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = *(SPVM_API_byte*)&vars[opcode->operand1] - *(SPVM_API_byte*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_SUBTRACT_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = *(SPVM_API_short*)&vars[opcode->operand1] - *(SPVM_API_short*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_SUBTRACT_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)&vars[opcode->operand1] - *(SPVM_API_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_SUBTRACT_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = *(SPVM_API_long*)&vars[opcode->operand1] - *(SPVM_API_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_SUBTRACT_FLOAT:
        *(float*)&vars[opcode->operand0] = *(float*)&vars[opcode->operand1] - *(float*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_SUBTRACT_DOUBLE:
        *(double*)&vars[opcode->operand0] = *(double*)&vars[opcode->operand1] - *(double*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_MULTIPLY_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = *(SPVM_API_byte*)&vars[opcode->operand1] * *(SPVM_API_byte*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_MULTIPLY_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = *(SPVM_API_short*)&vars[opcode->operand1] * *(SPVM_API_short*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_MULTIPLY_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)&vars[opcode->operand1] * *(SPVM_API_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_MULTIPLY_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = *(SPVM_API_long*)&vars[opcode->operand1] * *(SPVM_API_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_MULTIPLY_FLOAT:
        *(float*)&vars[opcode->operand0] = *(float*)&vars[opcode->operand1] * *(float*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_MULTIPLY_DOUBLE:
        *(double*)&vars[opcode->operand0] = *(double*)&vars[opcode->operand1] * *(double*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_DIVIDE_BYTE:
        if (__builtin_expect(*(SPVM_API_byte*)&vars[opcode->operand2] == 0, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_byte*)&vars[opcode->operand0]
            = *(SPVM_API_byte*)&vars[opcode->operand1] / *(SPVM_API_byte*)&vars[opcode->operand2];
        }
        break;
      case SPVM_OPCODE_C_CODE_DIVIDE_SHORT:
        if (__builtin_expect(*(SPVM_API_short*)&vars[opcode->operand2] == 0, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_short*)&vars[opcode->operand0]
            = *(SPVM_API_short*)&vars[opcode->operand1] / *(SPVM_API_short*)&vars[opcode->operand2];
        }
        break;
      case SPVM_OPCODE_C_CODE_DIVIDE_INT:
        if (__builtin_expect(*(SPVM_API_int*)&vars[opcode->operand2] == 0, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_int*)&vars[opcode->operand0]
            = *(SPVM_API_int*)&vars[opcode->operand1] / *(SPVM_API_int*)&vars[opcode->operand2];
        }
        break;
      case SPVM_OPCODE_C_CODE_DIVIDE_LONG:
        if (__builtin_expect(*(SPVM_API_long*)&vars[opcode->operand2] == 0, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_long*)&vars[opcode->operand0]
            = *(SPVM_API_long*)&vars[opcode->operand1] / *(SPVM_API_long*)&vars[opcode->operand2];
        }
        break;
      case SPVM_OPCODE_C_CODE_DIVIDE_FLOAT:
        *(float*)&vars[opcode->operand0]
          = *(float*)&vars[opcode->operand1] / *(float*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_DIVIDE_DOUBLE:
        *(double*)&vars[opcode->operand0]
          = *(double*)&vars[opcode->operand1] / *(double*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_REMAINDER_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0]
          = *(SPVM_API_byte*)&vars[opcode->operand1] % *(SPVM_API_byte*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_REMAINDER_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0]
          = *(SPVM_API_short*)&vars[opcode->operand1] % *(SPVM_API_short*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_REMAINDER_INT:
        *(SPVM_API_int*)&vars[opcode->operand0]
          = *(SPVM_API_int*)&vars[opcode->operand1] % *(SPVM_API_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_REMAINDER_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0]
          = *(SPVM_API_long*)&vars[opcode->operand1] % *(SPVM_API_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_REMAINDER_FLOAT:
        *(float*)&vars[opcode->operand0]
          = (float)fmod((double)*(float*)&vars[opcode->operand1], *(float*)&vars[opcode->operand2]);
        break;
      case SPVM_OPCODE_C_CODE_REMAINDER_DOUBLE:
        *(double*)&vars[opcode->operand0]
          = fmod(*(double*)&vars[opcode->operand1], *(double*)&vars[opcode->operand2]);
        break;
      case SPVM_OPCODE_C_CODE_LEFT_SHIFT_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0]
          = *(SPVM_API_byte*)&vars[opcode->operand1] << *(SPVM_API_byte*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_LEFT_SHIFT_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0]
          = *(SPVM_API_short*)&vars[opcode->operand1] << *(SPVM_API_short*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_LEFT_SHIFT_INT:
        *(SPVM_API_int*)&vars[opcode->operand0]
          = *(SPVM_API_int*)&vars[opcode->operand1] << *(SPVM_API_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_LEFT_SHIFT_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0]
          = *(SPVM_API_long*)&vars[opcode->operand1] << *(SPVM_API_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0]
          = *(SPVM_API_byte*)&vars[opcode->operand1] >> *(SPVM_API_byte*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0]
          = *(SPVM_API_short*)&vars[opcode->operand1] >> *(SPVM_API_short*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_INT:
        *(SPVM_API_int*)&vars[opcode->operand0]
          = *(SPVM_API_int*)&vars[opcode->operand1] >> *(SPVM_API_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0]
          = *(SPVM_API_long*)&vars[opcode->operand1] >> *(SPVM_API_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0]
          = (int8_t)((uint8_t)*(SPVM_API_byte*)&vars[opcode->operand1] >> *(SPVM_API_byte*)&vars[opcode->operand2]);
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0]
          = (int16_t)((uint16_t)*(SPVM_API_short*)&vars[opcode->operand1] >> *(SPVM_API_short*)&vars[opcode->operand2]);
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_INT:
        *(SPVM_API_int*)&vars[opcode->operand0]
          = (int32_t)((uint32_t)*(SPVM_API_int*)&vars[opcode->operand1] >> *(SPVM_API_int*)&vars[opcode->operand2]);
        break;
      case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0]
          = (int64_t)((uint64_t)*(SPVM_API_long*)&vars[opcode->operand1] >> *(SPVM_API_long*)&vars[opcode->operand2]);
        break;
      case SPVM_OPCODE_C_CODE_BIT_AND_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0]
          = *(SPVM_API_byte*)&vars[opcode->operand1] & *(SPVM_API_byte*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_BIT_AND_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0]
          = *(SPVM_API_short*)&vars[opcode->operand1] & *(SPVM_API_short*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_BIT_AND_INT:
        *(SPVM_API_int*)&vars[opcode->operand0]
          = *(SPVM_API_int*)&vars[opcode->operand1] & *(SPVM_API_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_BIT_AND_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0]
          = *(SPVM_API_long*)&vars[opcode->operand1] & *(SPVM_API_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_BIT_OR_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0]
          = *(SPVM_API_byte*)&vars[opcode->operand1] | *(SPVM_API_byte*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_BIT_OR_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0]
          = *(SPVM_API_short*)&vars[opcode->operand1] | *(SPVM_API_short*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_BIT_OR_INT:
        *(SPVM_API_int*)&vars[opcode->operand0]
          = *(SPVM_API_int*)&vars[opcode->operand1] | *(SPVM_API_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_BIT_OR_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0]
          = *(SPVM_API_long*)&vars[opcode->operand1] | *(SPVM_API_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_BIT_XOR_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0]
          = *(SPVM_API_byte*)&vars[opcode->operand1] ^ *(SPVM_API_byte*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_BIT_XOR_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0]
          = *(SPVM_API_short*)&vars[opcode->operand1] ^ *(SPVM_API_short*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_BIT_XOR_INT:
        *(SPVM_API_int*)&vars[opcode->operand0]
          = *(SPVM_API_int*)&vars[opcode->operand1] ^ *(SPVM_API_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_BIT_XOR_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0]
          = *(SPVM_API_long*)&vars[opcode->operand1] ^ *(SPVM_API_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_CODE_NEGATE_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = -*(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_NEGATE_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = -*(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_NEGATE_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = -*(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_NEGATE_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = -*(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_NEGATE_FLOAT:
        *(float*)&vars[opcode->operand0] = -*(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_NEGATE_DOUBLE:
        *(double*)&vars[opcode->operand0] = -*(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_COMPLEMENT_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = ~*(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_COMPLEMENT_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = ~*(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_COMPLEMENT_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = ~*(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_COMPLEMENT_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = ~*(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_INC_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] += (int8_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_INC_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] += (int16_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_INC_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] += (int32_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_INC_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] += (int64_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = (int64_t)*(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_FLOAT:
        *(float*)&vars[opcode->operand0] = (float)*(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_DOUBLE:
        *(double*)&vars[opcode->operand0] = (double)*(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = (int32_t)*(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_FLOAT:
        *(float*)&vars[opcode->operand0] = (float)*(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_DOUBLE:
        *(double*)&vars[opcode->operand0] = (double)*(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = (int32_t)*(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = (int64_t)*(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_DOUBLE:
        *(double*)&vars[opcode->operand0] = (double)*(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = (int32_t)*(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = (int64_t)*(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_FLOAT:
        *(float*)&vars[opcode->operand0] = (float)*(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = (int8_t)(*(SPVM_API_int*)&vars[opcode->operand1]);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = (int16_t)(*(SPVM_API_int*)&vars[opcode->operand1]);
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = (int32_t)*(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = (int32_t)*(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = (int64_t)*(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_FLOAT:
        *(float*)&vars[opcode->operand0] = (float)*(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_DOUBLE:
        *(double*)&vars[opcode->operand0] = (double)*(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = (int8_t)*(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = (int64_t)*(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_FLOAT:
        *(float*)&vars[opcode->operand0] = (float)*(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_DOUBLE:
        *(double*)&vars[opcode->operand0] = (double)*(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = (int8_t)*(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = (int16_t)*(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = (int8_t)*(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = (int16_t)*(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = (int8_t)*(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = (int16_t)*(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = (int16_t)*(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = *(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = *(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = *(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_FLOAT:
        *(float*)&vars[opcode->operand0] = *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_DOUBLE:
        *(double*)&vars[opcode->operand0] = *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_LOAD_UNDEF:
        *(SPVM_API_OBJECT**)&vars[opcode->operand0] = NULL;
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_BYTE_0:
        *(SPVM_API_byte*)&vars[opcode->operand0] = (int8_t)0;
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_SHORT_0:
        *(SPVM_API_short*)&vars[opcode->operand0] = (int16_t)0;
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_INT_0:
        *(SPVM_API_int*)&vars[opcode->operand0] = (int32_t)0;
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_LONG_0:
        *(SPVM_API_long*)&vars[opcode->operand0] = (int64_t)0;
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_FLOAT_0:
        *(float*)&vars[opcode->operand0] = (float)0;
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_DOUBLE_0:
        *(double*)&vars[opcode->operand0] = (double)0;
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = *(SPVM_API_byte*)&constant_pool[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = *(SPVM_API_short*)&constant_pool[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)&constant_pool[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = *(SPVM_API_long*)&constant_pool[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_FLOAT:
        *(float*)&vars[opcode->operand0] = *(float*)&constant_pool[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_DOUBLE:
        *(double*)&vars[opcode->operand0] = *(double*)&constant_pool[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_BYTE: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand2];
        if (__builtin_expect(array == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(SPVM_API_byte*)&vars[opcode->operand0] = *(SPVM_API_byte*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int8_t) * index);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_SHORT: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(SPVM_API_short*)&vars[opcode->operand0]
              = *(SPVM_API_short*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int16_t) * index);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_INT: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int32_t) * index);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_LONG: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(SPVM_API_long*)&vars[opcode->operand0] = *(SPVM_API_long*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int64_t) * index);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_FLOAT: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(float*)&vars[opcode->operand0] = *(float*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(float) * index);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_DOUBLE: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(double*)&vars[opcode->operand0] = *(double*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(double) * index);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_ARRAY_LOAD_OBJECT: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(SPVM_API_OBJECT**)&vars[opcode->operand0] = *(SPVM_API_OBJECT**)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_OBJECT*) * index);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_BYTE: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(SPVM_API_byte*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int8_t) * index) = *(SPVM_API_byte*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_SHORT: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(SPVM_API_short*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int16_t) * index) = *(SPVM_API_short*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_INT: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(SPVM_API_int*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int32_t) * index) = *(SPVM_API_int*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_LONG: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(SPVM_API_long*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(int64_t) * index) = *(SPVM_API_long*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_FLOAT: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(float*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(float) * index) = *(float*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_DOUBLE: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(double*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(double) * index) = *(double*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_ARRAY_STORE_OBJECT: {
        
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Array must not be undef", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "Index is out of range", 0);
            api->set_exception(api, exception);
            croak_flag = 1;
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
            *object_address = *(SPVM_API_OBJECT**)&vars[opcode->operand2];

            // Increment new object reference count
            if (*object_address != NULL) {
              SPVM_INLINE_INC_REF_COUNT(*object_address);
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_MOVE:
        vars[opcode->operand0] = vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_CODE_INC_REF_COUNT: {
        // Increment new value reference count
        if (*(SPVM_API_OBJECT**)&vars[opcode->operand0] != NULL) {
          SPVM_INLINE_INC_REF_COUNT(*(SPVM_API_OBJECT**)&vars[opcode->operand0]);
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_DEC_REF_COUNT: {
        // Decrement reference count
        if (*(SPVM_API_OBJECT**)&vars[opcode->operand0] != NULL) {
          if (SPVM_INLINE_GET_REF_COUNT(*(SPVM_API_OBJECT**)&vars[opcode->operand0]) > 1) {
            SPVM_INLINE_DEC_REF_COUNT_ONLY(*(SPVM_API_OBJECT**)&vars[opcode->operand0]);
          }
          else {
            api->dec_ref_count(api, *(SPVM_API_OBJECT**)&vars[opcode->operand0]);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_OBJECT: {
        // Get subroutine ID
        int32_t type_id = opcode->operand1;
        
        SPVM_API_OBJECT* object = api->new_object(api, type_id);
        
        // Push object
        *(SPVM_API_OBJECT**)&vars[opcode->operand0] = object;
        
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_BYTE_ARRAY: {
        
        // length
        int32_t length = *(SPVM_API_int*)&vars[opcode->operand1];
        
        SPVM_API_OBJECT* object = api->new_byte_array(api, length);
        
        // Set array
        *(SPVM_API_OBJECT**)&vars[opcode->operand0] = object;
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_SHORT_ARRAY: {
        
        // length
        int32_t length = *(SPVM_API_int*)&vars[opcode->operand1];
        
        SPVM_API_OBJECT* object = api->new_short_array(api, length);
        
        // Set array
        *(SPVM_API_OBJECT**)&vars[opcode->operand0] = object;
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_INT_ARRAY: {
        
        // length
        int32_t length = *(SPVM_API_int*)&vars[opcode->operand1];
        
        SPVM_API_OBJECT* object = api->new_int_array(api, length);
        
        // Set array
        *(SPVM_API_OBJECT**)&vars[opcode->operand0] = object;
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_LONG_ARRAY: {
        
        // length
        int32_t length = *(SPVM_API_int*)&vars[opcode->operand1];
        
        SPVM_API_OBJECT* object = api->new_long_array(api, length);
        
        // Set array
        *(SPVM_API_OBJECT**)&vars[opcode->operand0] = object;
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_FLOAT_ARRAY: {
        
        // length
        int32_t length = *(SPVM_API_int*)&vars[opcode->operand1];
        
        SPVM_API_OBJECT* object = api->new_float_array(api, length);
        
        // Set array
        *(SPVM_API_OBJECT**)&vars[opcode->operand0] = object;
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_DOUBLE_ARRAY: {
        
        // length
        int32_t length = *(SPVM_API_int*)&vars[opcode->operand1];
        
        SPVM_API_OBJECT* object = api->new_double_array(api, length);
        
        // Set array
        *(SPVM_API_OBJECT**)&vars[opcode->operand0] = object;
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_OBJECT_ARRAY: {
        int32_t element_type_id = opcode->operand1;
        
        // length
        int32_t length = *(SPVM_API_int*)&vars[opcode->operand2];
        
        SPVM_API_OBJECT* object = api->new_object_array(api, element_type_id, length);
        
        // Set object
        *(SPVM_API_OBJECT**)&vars[opcode->operand0] = object;
        break;
      }
      case SPVM_OPCODE_C_CODE_NEW_STRING: {
        int32_t name_id = opcode->operand1;
        
        SPVM_API_OBJECT* string = api->new_string(api, (char*)&constant_pool[name_id + 1], constant_pool[name_id]);

        // Set string
        *(SPVM_API_OBJECT**)&vars[opcode->operand0] = string;
        break;
      }
      case SPVM_OPCODE_C_CODE_ARRAY_LENGTH:
        if (*(SPVM_API_OBJECT**)&vars[opcode->operand1] == NULL) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Can't get array length of undef value.", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)((intptr_t)*(SPVM_API_OBJECT**)&vars[opcode->operand1] + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET);
        }
        break;
      case SPVM_OPCODE_C_CODE_GET_FIELD_BYTE: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        
        int32_t field_id = opcode->operand2;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_byte*)&vars[opcode->operand0] = *(SPVM_API_byte*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_GET_FIELD_SHORT: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        
        int32_t field_id = opcode->operand2;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_short*)&vars[opcode->operand0] = *(SPVM_API_short*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_GET_FIELD_INT: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        
        int32_t field_id = opcode->operand2;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_GET_FIELD_LONG: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        
        int32_t field_id = opcode->operand2;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_long*)&vars[opcode->operand0] = *(SPVM_API_long*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_GET_FIELD_FLOAT: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        
        int32_t field_id = opcode->operand2;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(float*)&vars[opcode->operand0] = *(float*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_GET_FIELD_DOUBLE: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        
        int32_t field_id = opcode->operand2;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(double*)&vars[opcode->operand0] = *(double*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_GET_FIELD_OBJECT: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        
        int32_t field_id = opcode->operand2;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_OBJECT**)&vars[opcode->operand0] = *(SPVM_API_OBJECT**)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_BYTE: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_byte*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset) = *(SPVM_API_byte*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_SHORT: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_short*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset) = *(SPVM_API_short*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_INT: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_int*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset) = *(SPVM_API_int*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_LONG: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_long*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset) = *(SPVM_API_long*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_FLOAT: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(float*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset) = *(float*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_DOUBLE: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        
        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(double*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset) = *(double*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_FIELD_OBJECT: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t field_id = opcode->operand1;

        // Index
        SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
        int32_t field_byte_offset = constant_pool_field->byte_offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object must be not undef.", 0);
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
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
          
          *field_address = *(SPVM_API_OBJECT**)&vars[opcode->operand2];
          
          if(*field_address != NULL) {
            SPVM_INLINE_INC_REF_COUNT(*field_address);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_WEAKEN_FIELD_OBJECT: {
        
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        
        api->weaken_object_field(api, object, field_id);
        
        if (SPVM_INLINE_GET_EXCEPTION()) {
          croak_flag = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_STRING: {
        *(SPVM_API_OBJECT**)&vars[opcode->operand0] = api->concat_string_string(api, *(SPVM_API_OBJECT**)&vars[opcode->operand1], *(SPVM_API_OBJECT**)&vars[opcode->operand2]);
        
        if (*(SPVM_API_OBJECT**)&vars[opcode->operand0] == NULL) {
          croak_flag = 1;
        }
        
        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_BYTE: {
        *(SPVM_API_OBJECT**)&vars[opcode->operand0] = api->concat_string_byte(api, *(SPVM_API_OBJECT**)&vars[opcode->operand1], *(SPVM_API_byte*)&vars[opcode->operand2]);
        
        if (*(SPVM_API_OBJECT**)&vars[opcode->operand0] == NULL) {
          croak_flag = 1;
        }

        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_SHORT: {
        *(SPVM_API_OBJECT**)&vars[opcode->operand0] = api->concat_string_short(api, *(SPVM_API_OBJECT**)&vars[opcode->operand1], *(SPVM_API_short*)&vars[opcode->operand2]);
        
        if (*(SPVM_API_OBJECT**)&vars[opcode->operand0] == NULL) {
          croak_flag = 1;
        }
        
        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_INT: {
        *(SPVM_API_OBJECT**)&vars[opcode->operand0] = api->concat_string_int(api, *(SPVM_API_OBJECT**)&vars[opcode->operand1], *(SPVM_API_int*)&vars[opcode->operand2]);
        
        if (*(SPVM_API_OBJECT**)&vars[opcode->operand0] == NULL) {
          croak_flag = 1;
        }

        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_LONG: {
        *(SPVM_API_OBJECT**)&vars[opcode->operand0] = api->concat_string_long(api, *(SPVM_API_OBJECT**)&vars[opcode->operand1], *(SPVM_API_long*)&vars[opcode->operand2]);
        
        if (*(SPVM_API_OBJECT**)&vars[opcode->operand0] == NULL) {
          croak_flag = 1;
        }

        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_FLOAT: {
       *(SPVM_API_OBJECT**)&vars[opcode->operand0] = api->concat_string_float(api, *(SPVM_API_OBJECT**)&vars[opcode->operand1], *(float*)&vars[opcode->operand2]);
        
        if (*(SPVM_API_OBJECT**)&vars[opcode->operand0] == NULL) {
          croak_flag = 1;
        }

        break;
      }
      case SPVM_OPCODE_C_CODE_CONCAT_STRING_DOUBLE: {
        *(SPVM_API_OBJECT**)&vars[opcode->operand0] = api->concat_string_double(api, *(SPVM_API_OBJECT**)&vars[opcode->operand1], *(double*)&vars[opcode->operand2]);
        
        if (*(SPVM_API_OBJECT**)&vars[opcode->operand0] == NULL) {
          croak_flag = 1;
        }
        
        break;
      }
      case SPVM_OPCODE_C_CODE_PUSH_EVAL: {
        // Set exception to NULL at start of eval block
        SPVM_INLINE_SET_EXCEPTION_NULL();
        
        eval_stack_top++;
        eval_stack[eval_stack_top] = opcode->operand0;
        
        break;
      }
      case SPVM_OPCODE_C_CODE_POP_EVAL: {
        eval_stack_top--;
        
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_EXCEPTION_VAR: {
        *(SPVM_API_OBJECT**)&vars[opcode->operand0] = SPVM_INLINE_GET_EXCEPTION();
        
        break;
      }
      case SPVM_OPCODE_C_CODE_STORE_EXCEPTION_VAR: {
        
        api->set_exception(api, *(SPVM_API_OBJECT**)&vars[opcode->operand0]);
        
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_BYTE: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand1;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        *(SPVM_API_byte*)&vars[opcode->operand0] = *(SPVM_API_byte*)&package_vars[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_SHORT: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand1;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        *(SPVM_API_short*)&vars[opcode->operand0] = *(SPVM_API_short*)&package_vars[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_INT: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand1;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)&package_vars[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_LONG: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand1;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        *(SPVM_API_long*)&vars[opcode->operand0] = *(SPVM_API_long*)&package_vars[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_FLOAT: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand1;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        *(float*)&vars[opcode->operand0] = *(float*)&package_vars[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_DOUBLE: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand1;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        *(double*)&vars[opcode->operand0] = *(double*)&package_vars[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_OBJECT: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand1;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        *(SPVM_API_OBJECT**)&vars[opcode->operand0] = *(SPVM_API_OBJECT**)&package_vars[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_BYTE: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand0;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        *(SPVM_API_byte*)&package_vars[package_var_id] = *(SPVM_API_byte*)&vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_SHORT: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand0;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        *(SPVM_API_short*)&package_vars[package_var_id] = *(SPVM_API_short*)&vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_INT: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand0;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        *(SPVM_API_int*)&package_vars[package_var_id] = *(SPVM_API_int*)&vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_LONG: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand0;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        *(SPVM_API_long*)&package_vars[package_var_id] = *(SPVM_API_long*)&vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_FLOAT: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand0;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        *(float*)&package_vars[package_var_id] = *(float*)&vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_DOUBLE: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand0;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        *(double*)&package_vars[package_var_id] = *(double*)&vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_OBJECT: {
        // Get subroutine ID
        int32_t package_var_id = opcode->operand0;
        
        SPVM_API_VALUE* package_vars = runtime->package_vars;
        
        SPVM_API_OBJECT** package_var_address = (SPVM_API_OBJECT**)&package_vars[package_var_id];
        
        // Decrement reference count
        if (*(SPVM_API_OBJECT**)package_var_address != NULL) {
          if (SPVM_INLINE_GET_REF_COUNT(*(SPVM_API_OBJECT**)package_var_address) > 1) {
            SPVM_INLINE_DEC_REF_COUNT_ONLY(*(SPVM_API_OBJECT**)package_var_address);
          }
          else {
            api->dec_ref_count(api, *(SPVM_API_OBJECT**)package_var_address);
          }
        }
        
        // Store object
        *(SPVM_API_OBJECT**)package_var_address = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        
        // Increment new value reference count
        if (package_vars[package_var_id].object_value != NULL) {
          SPVM_INLINE_INC_REF_COUNT(*(SPVM_API_OBJECT**)package_var_address);
        }
        
        break;
      }
      case SPVM_OPCODE_C_CODE_CURRENT_LINE:
        current_line = opcode->operand0;
        break;
      case SPVM_OPCODE_C_CODE_GOTO:
        opcode_index = opcode->operand0;
        continue;
      case SPVM_OPCODE_C_CODE_IF_EQ_ZERO: {
        if (condition_flag == 0) {
          opcode_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_IF_NE_ZERO: {
        if (condition_flag) {
          opcode_index = opcode->operand0;
          continue;
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
        SPVM_CONSTANT_POOL_SUB* constant_pool_sub_call_sub = (SPVM_CONSTANT_POOL_SUB*)&constant_pool[call_sub_id];
        
        // Call subroutine return type id
        int32_t call_sub_return_type_id = constant_pool_sub_call_sub->return_type_id;
        
        // Constant pool type
        SPVM_CONSTANT_POOL_TYPE* call_sub_return_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[call_sub_return_type_id];
        
        // Return type code
        int32_t call_sub_return_type_code = call_sub_return_type->code;
        
        // Subroutine argument length
        int32_t call_sub_args_length = constant_pool_sub_call_sub->args_length;
        
        // Subroutine argument length
        int32_t call_sub_is_void = constant_pool_sub_call_sub->is_void;
        
        call_sub_arg_stack_top -= call_sub_args_length;
        
        SPVM_API_VALUE args[255];
        {
          int32_t i;
          for (i = 0; i < call_sub_args_length; i++) {
            int32_t var_index = call_sub_arg_stack[call_sub_arg_stack_top + 1 + i].int_value;
            args[i] = vars[var_index];
          }
        }
        
        // Call subroutine
        if (call_sub_is_void) {
          api->call_void_sub(api, call_sub_id, args);
        }
        else if (call_sub_return_type_code == SPVM_INFO_TYPE_CODE_BYTE) {
          *(SPVM_API_byte*)&vars[opcode->operand0] = api->call_byte_sub(api, call_sub_id, args);
        }
        else if (call_sub_return_type_code == SPVM_INFO_TYPE_CODE_SHORT) {
          *(SPVM_API_short*)&vars[opcode->operand0] = api->call_short_sub(api, call_sub_id, args);
        }
        else if (call_sub_return_type_code == SPVM_INFO_TYPE_CODE_INT) {
          *(SPVM_API_int*)&vars[opcode->operand0] = api->call_int_sub(api, call_sub_id, args);
        }
        else if (call_sub_return_type_code == SPVM_INFO_TYPE_CODE_LONG) {
          *(SPVM_API_long*)&vars[opcode->operand0] = api->call_long_sub(api, call_sub_id, args);
        }
        else if (call_sub_return_type_code == SPVM_INFO_TYPE_CODE_FLOAT) {
          *(float*)&vars[opcode->operand0] = api->call_float_sub(api, call_sub_id, args);
        }
        else if (call_sub_return_type_code == SPVM_INFO_TYPE_CODE_DOUBLE) {
          *(double*)&vars[opcode->operand0] = api->call_double_sub(api, call_sub_id, args);
        }
        else {
          *(SPVM_API_OBJECT**)&vars[opcode->operand0] = api->call_object_sub(api, call_sub_id, args);
        }
        
        if (SPVM_INLINE_GET_EXCEPTION()) {
          croak_flag = 1;
          goto label_SPVM_OPCODE_C_CODE_CROAK;
        }
        else {
          // Next operation
          opcode_index++;
        }
        
        continue;
      }
      case SPVM_OPCODE_C_CODE_CROAK: {
        
        label_SPVM_OPCODE_C_CODE_CROAK:
        
        // Catch croak
        if (eval_stack_top > -1) {
          opcode_index = eval_stack[eval_stack_top];
          eval_stack_top--;
          croak_flag = 0;
          continue;
        }
        // Croak
        else {
          assert(croak_flag == 1);
          goto label_SPVM_OPCODE_C_CODE_RETURN;
        }
      }
      case SPVM_OPCODE_C_CODE_IF_CROAK_CATCH: {
        if (croak_flag) {
          croak_flag = 0;
          opcode_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_IF_CROAK_RETURN: {
        if (croak_flag) {
          goto label_SPVM_OPCODE_C_CODE_RETURN;
        }
        break;
      }
      case SPVM_OPCODE_C_CODE_SET_CROAK_FLAG_TRUE: {
        croak_flag = 1;
        break;
      }
      case SPVM_OPCODE_C_CODE_RETURN:
      {
        // Get return value
        if (!constant_pool_sub->is_void) {
          return_value = vars[opcode->operand0];
        }
        
        goto label_SPVM_OPCODE_C_CODE_RETURN;
      }
      case SPVM_OPCODE_C_CODE_TABLE_SWITCH:
        // TABLE_SWITCH is no longer used
        assert(0);
      case SPVM_OPCODE_C_CODE_LOOKUP_SWITCH: {
        // 1  default
        // 5  npare
        // 9  match1 offset1 // min
        // 17 match2 offset2
        // 25 match3 offset3 // max
        
        // default offset
        int32_t default_branch = opcode->operand1;
        
        // npare
        int32_t case_count = opcode->operand2;
        
        // min
        int32_t min = (opcode + 1)->operand0;
        
        // max
        int32_t max = (opcode + 1 + case_count - 1)->operand0;
        
        if (*(SPVM_API_int*)&vars[opcode->operand0] >= min && *(SPVM_API_int*)&vars[opcode->operand0] <= max) {
          // 2 branch searching
          int32_t cur_min_pos = 0;
          int32_t cur_max_pos = case_count - 1;
          
          while (1) {
            if (cur_max_pos < cur_min_pos) {
              opcode_index = default_branch;
              break;
            }
            int32_t cur_half_pos = cur_min_pos + (cur_max_pos - cur_min_pos) / 2;
            int32_t cur_half = (opcode + 1 + cur_half_pos)->operand0;
            
            if (*(SPVM_API_int*)&vars[opcode->operand0] > cur_half) {
              cur_min_pos = cur_half_pos + 1;
            }
            else if (*(SPVM_API_int*)&vars[opcode->operand0] < cur_half) {
              cur_max_pos = cur_half_pos - 1;
            }
            else {
              int32_t branch = (opcode + 1 + cur_half_pos)->operand1;
              opcode_index = branch;
              break;
            }
          }
        }
        else {
          opcode_index = default_branch;
        }
        
        continue;
      }
    }
    opcode_index++;
  }

  label_SPVM_OPCODE_C_CODE_RETURN: {
    
    // Increment ref count of return value not to release by decrement
    if (sub_return_type_code > SPVM_TYPE_C_CODE_DOUBLE) {
      if (return_value.object_value != NULL) {
        SPVM_INLINE_INC_REF_COUNT(return_value.object_value);
      }
    }
    
    // Decrement my vars
    {
      int32_t i;
      for (i = 0; i < sub_object_mys_length; i++) {
        int32_t my_var_index = constant_pool[sub_object_mys_base + i];
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
    if (sub_return_type_code > SPVM_TYPE_C_CODE_DOUBLE) {
      if (return_value.object_value != NULL) {
        SPVM_INLINE_DEC_REF_COUNT_ONLY(return_value.object_value);
      }
    }
    
    // Croak
    if (croak_flag) {
      if (runtime->debug) {
        // Exception stack trace
        SPVM_API_OBJECT* exception_stack_trace = api->create_exception_stack_trace(api, sub_id, SPVM_INLINE_GET_EXCEPTION(), current_line);
        api->set_exception(api, exception_stack_trace);
      }
      memset(&return_value, 0, sizeof(SPVM_API_VALUE));
    }
    // RETURN
    else {
      SPVM_INLINE_SET_EXCEPTION_NULL();
    }
    
    return return_value;
  }
}
