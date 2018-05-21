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
#include "spvm_opcode.h"
#include "spvm_opcode_array.h"
#include "spvm_runtime_allocator.h"
#include "spvm_call_stack_info.h"

#include "spvm_package.h"
#include "spvm_sub.h"
#include "spvm_package.h"
#include "spvm_type.h"
#include "spvm_field.h"
#include "spvm_compiler.h"
#include "spvm_my.h"
#include "spvm_op.h"
#include "spvm_list.h"
#include "spvm_opcode_array.h"
#include "spvm_constant.h"
#include "spvm_hash.h"
#include "spvm_basic_type.h"

SPVM_API_VALUE SPVM_RUNTIME_call_sub(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args) {
  (void)api;
  
  // Runtime
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  
  SPVM_COMPILER* compiler = runtime->compiler;

  // Constant pool sub
  SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, sub_id);
  SPVM_SUB* sub = op_sub->uv.sub;
  
  if (sub->is_native) {
    return SPVM_RUNTIME_call_sub_native(api, sub_id, args);
  }
  else if (sub->is_jit) {
    return SPVM_RUNTIME_call_sub_jit(api, sub_id, args);
  }
  else {
    // Compile JIT subroutine
    if (compiler->enable_jit && sub->have_jit_desc) {
      api->compile_jit_sub(api, sub_id);
      return SPVM_RUNTIME_call_sub_jit(api, sub_id, args);
    }
    
    return SPVM_RUNTIME_call_sub_vm(api, sub_id, args);
  }
}

SPVM_API_VALUE SPVM_RUNTIME_call_sub_jit(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args) {
  (void)api;
  
  // Runtime
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_COMPILER* compiler = runtime->compiler;

  // Constant pool sub
  SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, sub_id);
  SPVM_SUB* sub = op_sub->uv.sub;
  
  // Subroutine return type
  SPVM_TYPE* sub_return_type = sub->op_return_type->uv.type;
  
  int32_t sub_return_basic_type_id = sub_return_type->basic_type->id;
  
  int32_t sub_return_type_dimension = sub_return_type->dimension;
  
  // Return value
  SPVM_API_VALUE return_value;
  
  // Subroutine is JIT
  assert(sub->is_jit);
  
  void* sub_jit_address = sub->jit_address;
  
  // Call JIT subroutine
  if (sub_return_type_dimension == 0) {
    if (sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_VOID) {
      void (*jit_address)(SPVM_API*, SPVM_API_VALUE*) = sub_jit_address;
      (*jit_address)(api, (SPVM_API_VALUE*)args);
    }
    else if (sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_BYTE) {
      SPVM_API_byte (*jit_address)(SPVM_API*, SPVM_API_VALUE*) = sub_jit_address;
      SPVM_API_byte return_value_jit = (*jit_address)(api, (SPVM_API_VALUE*)args);
      *(SPVM_API_byte*)&return_value = return_value_jit;
    }
    else if (sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_SHORT) {
      SPVM_API_short (*jit_address)(SPVM_API*, SPVM_API_VALUE*) = sub_jit_address;
      SPVM_API_short return_value_jit = (*jit_address)(api, (SPVM_API_VALUE*)args);
      *(SPVM_API_short*)&return_value = return_value_jit;
    }
    else if (sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_INT) {
      SPVM_API_int (*jit_address)(SPVM_API*, SPVM_API_VALUE*) = sub_jit_address;
      SPVM_API_int return_value_jit = (*jit_address)(api, (SPVM_API_VALUE*)args);
      *(SPVM_API_int*)&return_value = return_value_jit;
    }
    else if (sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_LONG) {
      SPVM_API_long (*jit_address)(SPVM_API*, SPVM_API_VALUE*) = sub_jit_address;
      SPVM_API_long return_value_jit = (*jit_address)(api, (SPVM_API_VALUE*)args);
      *(SPVM_API_long*)&return_value = return_value_jit;
    }
    else if (sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
      float (*jit_address)(SPVM_API*, SPVM_API_VALUE*) = sub_jit_address;
      float return_value_jit = (*jit_address)(api, (SPVM_API_VALUE*)args);
      *(float*)&return_value = return_value_jit;
    }
    else if (sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
      double (*jit_address)(SPVM_API*, SPVM_API_VALUE*) = sub_jit_address;
      double return_value_jit = (*jit_address)(api, (SPVM_API_VALUE*)args);
      *(double*)&return_value = return_value_jit;
    }
    else {
      SPVM_API_OBJECT* (*jit_address)(SPVM_API*, SPVM_API_VALUE*) = sub_jit_address;
      SPVM_API_OBJECT* return_value_jit = (*jit_address)(api, (SPVM_API_VALUE*)args);
      *(SPVM_API_OBJECT**)&return_value = return_value_jit;
    }
  }
  else {
    SPVM_API_OBJECT* (*jit_address)(SPVM_API*, SPVM_API_VALUE*) = sub_jit_address;
    SPVM_API_OBJECT* return_value_jit = (*jit_address)(api, (SPVM_API_VALUE*)args);
    *(SPVM_API_OBJECT**)&return_value = return_value_jit;
  }
  
  return return_value;
}

SPVM_API_VALUE SPVM_RUNTIME_call_sub_native(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args) {
  (void)api;
  
  // Runtime
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_COMPILER* compiler = runtime->compiler;

  // Constant pool sub
  SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, sub_id);
  SPVM_SUB* sub = op_sub->uv.sub;

  // Subroutine is native
  assert(sub->is_native);

  // Subroutine return type
  SPVM_TYPE* sub_return_type = sub->op_return_type->uv.type;
  
  int32_t sub_return_basic_type_id = sub_return_type->basic_type->id;
  
  int32_t sub_return_type_dimension = sub_return_type->dimension;
  
  // Return value
  SPVM_API_VALUE return_value;

  // Set exception to NULL at start of subroutine
  api->set_exception(api, NULL);
  
  // Native address
  void* sub_native_address = sub->native_address;
  
  if (sub_return_type_dimension == 0) {
    if (sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_VOID) {
      void (*native_address)(SPVM_API*, SPVM_API_VALUE*) = sub_native_address;
      (*native_address)(api, (SPVM_API_VALUE*)args);
    }
    else if (sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_BYTE) {
      SPVM_API_byte (*native_address)(SPVM_API*, SPVM_API_VALUE*) = sub_native_address;
      SPVM_API_byte return_value_native = (*native_address)(api, (SPVM_API_VALUE*)args);
      *(SPVM_API_byte*)&return_value = return_value_native;
    }
    else if (sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_SHORT) {
      SPVM_API_short (*native_address)(SPVM_API*, SPVM_API_VALUE*) = sub_native_address;
      SPVM_API_short return_value_native = (*native_address)(api, (SPVM_API_VALUE*)args);
      *(SPVM_API_short*)&return_value = return_value_native;
    }
    else if (sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_INT) {
      SPVM_API_int (*native_address)(SPVM_API*, SPVM_API_VALUE*) = sub_native_address;
      SPVM_API_int return_value_native = (*native_address)(api, (SPVM_API_VALUE*)args);
      *(SPVM_API_int*)&return_value = return_value_native;
    }
    else if (sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_LONG) {
      SPVM_API_long (*native_address)(SPVM_API*, SPVM_API_VALUE*) = sub_native_address;
      SPVM_API_long return_value_native = (*native_address)(api, (SPVM_API_VALUE*)args);
      *(SPVM_API_long*)&return_value = return_value_native;
    }
    else if (sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
      float (*native_address)(SPVM_API*, SPVM_API_VALUE*) = sub_native_address;
      float return_value_native = (*native_address)(api, (SPVM_API_VALUE*)args);
      *(float*)&return_value = return_value_native;
    }
    else if (sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
      double (*native_address)(SPVM_API*, SPVM_API_VALUE*) = sub_native_address;
      double return_value_native = (*native_address)(api, (SPVM_API_VALUE*)args);
      *(double*)&return_value = return_value_native;
    }
    else {
      SPVM_API_OBJECT* (*native_address)(SPVM_API*, SPVM_API_VALUE*) = sub_native_address;
      SPVM_API_OBJECT* return_value_native = (*native_address)(api, (SPVM_API_VALUE*)args);
      *(SPVM_API_OBJECT**)&return_value = return_value_native;
    }
  }
  else {
    SPVM_API_OBJECT* (*native_address)(SPVM_API*, SPVM_API_VALUE*) = sub_native_address;
    SPVM_API_OBJECT* return_value_native = (*native_address)(api, (SPVM_API_VALUE*)args);
    *(SPVM_API_OBJECT**)&return_value = return_value_native;
  }
  
  return return_value;
}

SPVM_API_VALUE SPVM_RUNTIME_call_sub_vm(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args) {
  (void)api;
  
  // Runtime
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(api);
  SPVM_COMPILER* compiler = runtime->compiler;

  // Constant pool sub
  SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, sub_id);
  SPVM_SUB* sub = op_sub->uv.sub;

  // Subroutine return type
  SPVM_TYPE* sub_return_type = sub->op_return_type->uv.type;
  
  int32_t sub_return_basic_type_id = sub_return_type->basic_type->id;
  int32_t sub_return_type_dimension = sub_return_type->dimension;
  
  // Return value
  SPVM_API_VALUE return_value;
  
  // Args length
  int32_t args_length = sub->op_args->length;
  
  // Bytecodes
  SPVM_OPCODE* opcodes = compiler->opcode_array->values;
  
  // Opcode base
  int32_t sub_opcode_base = sub->opcode_base;
  
  SPVM_CALL_STACK_INFO call_stack_info;
  SPVM_CALL_STACK_init_call_stack_info(&call_stack_info, runtime, sub_id);

  // Subroutine stack
  // This is used Variables, Auto decrement stack, loop count
  SPVM_API_OBJECT* call_stack_object = SPVM_RUNTIME_API_new_call_stack_object(api, call_stack_info.length);
  SPVM_API_VALUE* call_stack = call_stack_object + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE;
  
  // Variables
  SPVM_API_VALUE* vars = call_stack;

  // Auto decrement reference count variable index stack top
  SPVM_API_VALUE* mortal_stack = &call_stack[call_stack_info.mortal_stack_base];
  int32_t mortal_stack_top = -1;

  // Call subroutine argument stack top
  int32_t call_sub_arg_stack_top = -1;
  
  // Condition flag
  register int32_t condition_flag = 0;

  // Croak flag
  int32_t croak_flag = 0;
  
  // Call sub arguments
  SPVM_API_VALUE call_sub_args[255];
  
  char tmp_string[30];

  register int32_t opcode_index = sub_opcode_base;

  // Initialize variables
  memset(vars, 0, sizeof(SPVM_API_VALUE) * sub->op_mys->length);
  
  // Copy arguments to variables
  memcpy(vars, args, args_length * sizeof(SPVM_API_VALUE));
  
  // Inilialize return value
  memset(&return_value, 0, sizeof(SPVM_API_VALUE));
  
  // If arg is object, increment reference count
  {
    int32_t index;
    for (index = 0; index < sub->object_arg_ids->length; index++) {
      int32_t object_arg_index = (intptr_t)SPVM_LIST_fetch(sub->object_arg_ids, index);
      
      SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[object_arg_index];
      if (object != NULL) {
        SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(object);
      }
    }
  }
  
  while (1) {
    SPVM_OPCODE* opcode = &(opcodes[opcode_index]);
    
    switch (opcode->id) {
      case SPVM_OPCODE_C_ID_BOOL_INT:
        condition_flag = !!*(SPVM_API_int*)&vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_ID_BOOL_LONG:
        condition_flag = !!*(SPVM_API_long*)&vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_ID_BOOL_FLOAT:
        condition_flag = !!*(float*)&vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_ID_BOOL_DOUBLE:
        condition_flag = !!*(double*)&vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_ID_BOOL_OBJECT:
        condition_flag = !!*(SPVM_API_OBJECT**)&vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_ID_IS_UNDEF:
        condition_flag = *(SPVM_API_OBJECT**)&vars[opcode->operand0] == NULL;
        break;
      case SPVM_OPCODE_C_ID_IS_NOT_UNDEF:
        condition_flag = *(SPVM_API_OBJECT**)&vars[opcode->operand0] != NULL;
        break;
      case SPVM_OPCODE_C_ID_EQ_INT:
        condition_flag = *(SPVM_API_int*)&vars[opcode->operand0] == *(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_EQ_LONG:
        condition_flag = *(SPVM_API_long*)&vars[opcode->operand0] == *(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_EQ_FLOAT:
        condition_flag = *(float*)&vars[opcode->operand0] == *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_EQ_DOUBLE:
        condition_flag = *(double*)&vars[opcode->operand0] == *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_EQ_OBJECT:
        condition_flag = *(SPVM_API_OBJECT**)&vars[opcode->operand0] == *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NE_INT:
        condition_flag = *(SPVM_API_int*)&vars[opcode->operand0] != *(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NE_LONG:
        condition_flag = *(SPVM_API_long*)&vars[opcode->operand0] != *(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NE_FLOAT:
        condition_flag = *(float*)&vars[opcode->operand0] != *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NE_DOUBLE:
        condition_flag = *(double*)&vars[opcode->operand0] != *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NE_OBJECT:
        condition_flag = *(SPVM_API_OBJECT**)&vars[opcode->operand0] != *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GT_INT:
        condition_flag = *(SPVM_API_int*)&vars[opcode->operand0] > *(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GT_LONG:
        condition_flag = *(SPVM_API_long*)&vars[opcode->operand0] > *(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GT_FLOAT:
        condition_flag = *(float*)&vars[opcode->operand0] > *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GT_DOUBLE:
        condition_flag = *(double*)&vars[opcode->operand0] > *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GE_INT:
        condition_flag = *(SPVM_API_int*)&vars[opcode->operand0] >= *(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GE_LONG:
        condition_flag = *(SPVM_API_long*)&vars[opcode->operand0] >= *(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GE_FLOAT:
        condition_flag = *(float*)&vars[opcode->operand0] >= *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GE_DOUBLE:
        condition_flag = *(double*)&vars[opcode->operand0] >= *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LT_INT:
        condition_flag = *(SPVM_API_int*)&vars[opcode->operand0] < *(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LT_LONG:
        condition_flag = *(SPVM_API_long*)&vars[opcode->operand0] < *(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LT_FLOAT:
        condition_flag = *(float*)&vars[opcode->operand0] < *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LT_DOUBLE:
        condition_flag = *(double*)&vars[opcode->operand0] < *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LE_INT:
        condition_flag = *(SPVM_API_int*)&vars[opcode->operand0] <= *(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LE_LONG:
        condition_flag = *(SPVM_API_long*)&vars[opcode->operand0] <= *(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LE_FLOAT:
        condition_flag = *(float*)&vars[opcode->operand0] <= *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LE_DOUBLE:
        condition_flag = *(double*)&vars[opcode->operand0] <= *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_ISA:
      {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t basic_type_id = opcode->operand1;
        int32_t dimension = opcode->operand2;
        
        condition_flag = (*(int32_t*)(object + SPVM_RUNTIME_C_OBJECT_BASIC_TYPE_ID_BYTE_OFFSET) == basic_type_id && *(int32_t*)(object + SPVM_RUNTIME_C_OBJECT_DIMENSION_BYTE_OFFSET) == dimension);
        
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_EQ:
      case SPVM_OPCODE_C_ID_STRING_NE:
      case SPVM_OPCODE_C_ID_STRING_GT:
      case SPVM_OPCODE_C_ID_STRING_GE:
      case SPVM_OPCODE_C_ID_STRING_LT:
      case SPVM_OPCODE_C_ID_STRING_LE:
      {
        SPVM_API_OBJECT* string1 = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        SPVM_API_OBJECT* string2 = *(SPVM_API_OBJECT**)&vars[opcode->operand1];

        SPVM_API_OBJECT* string1_object = *(SPVM_API_OBJECT**)((intptr_t)string1 + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE);
        SPVM_API_OBJECT* string2_object = *(SPVM_API_OBJECT**)((intptr_t)string2 + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE);

        int32_t string1_length = *(SPVM_API_int*)((intptr_t)string1_object + SPVM_RUNTIME_C_OBJECT_UNITS_LENGTH_BYTE_OFFSET);
        int32_t string2_length = *(SPVM_API_int*)((intptr_t)string2_object + SPVM_RUNTIME_C_OBJECT_UNITS_LENGTH_BYTE_OFFSET);
        
        SPVM_API_byte* string1_bytes = (SPVM_API_byte*)((intptr_t)string1_object + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE);
        SPVM_API_byte* string2_bytes = (SPVM_API_byte*)((intptr_t)string2_object + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE);
        
        int32_t short_string_length = string1_length < string2_length ? string1_length : string2_length;
        int32_t retval = memcmp(string1_bytes, string2_bytes, short_string_length);
        int32_t cmp;
        if (retval) {
          cmp = retval < 0 ? -1 : 1;
        } else if (string1_length == string2_length) {
          cmp = 0;
        } else {
          cmp = string1_length < string2_length ? -1 : 1;
        }
        
        switch (opcode->id) {
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
        *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)&vars[opcode->operand1] + *(SPVM_API_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_ADD_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = *(SPVM_API_long*)&vars[opcode->operand1] + *(SPVM_API_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_ADD_FLOAT:
        *(float*)&vars[opcode->operand0] = *(float*)&vars[opcode->operand1] + *(float*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_ADD_DOUBLE:
        *(double*)&vars[opcode->operand0] = *(double*)&vars[opcode->operand1] + *(double*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)&vars[opcode->operand1] - *(SPVM_API_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = *(SPVM_API_long*)&vars[opcode->operand1] - *(SPVM_API_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_FLOAT:
        *(float*)&vars[opcode->operand0] = *(float*)&vars[opcode->operand1] - *(float*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_DOUBLE:
        *(double*)&vars[opcode->operand0] = *(double*)&vars[opcode->operand1] - *(double*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)&vars[opcode->operand1] * *(SPVM_API_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = *(SPVM_API_long*)&vars[opcode->operand1] * *(SPVM_API_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_FLOAT:
        *(float*)&vars[opcode->operand0] = *(float*)&vars[opcode->operand1] * *(float*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_DOUBLE:
        *(double*)&vars[opcode->operand0] = *(double*)&vars[opcode->operand1] * *(double*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_INT:
        if (__builtin_expect(*(SPVM_API_int*)&vars[opcode->operand2] == 0, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "0 division");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_int*)&vars[opcode->operand0]
            = *(SPVM_API_int*)&vars[opcode->operand1] / *(SPVM_API_int*)&vars[opcode->operand2];
        }
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_LONG:
        if (__builtin_expect(*(SPVM_API_long*)&vars[opcode->operand2] == 0, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "0 division");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_long*)&vars[opcode->operand0]
            = *(SPVM_API_long*)&vars[opcode->operand1] / *(SPVM_API_long*)&vars[opcode->operand2];
        }
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_FLOAT:
        *(float*)&vars[opcode->operand0]
          = *(float*)&vars[opcode->operand1] / *(float*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_DOUBLE:
        *(double*)&vars[opcode->operand0]
          = *(double*)&vars[opcode->operand1] / *(double*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_INT:
        if (__builtin_expect(*(SPVM_API_short*)&vars[opcode->operand2] == 0, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "0 division");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)&vars[opcode->operand1] % *(SPVM_API_int*)&vars[opcode->operand2];
        }
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_LONG:
        if (__builtin_expect(*(SPVM_API_short*)&vars[opcode->operand2] == 0, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "0 division");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_long*)&vars[opcode->operand0] = *(SPVM_API_long*)&vars[opcode->operand1] % *(SPVM_API_long*)&vars[opcode->operand2];
        }
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_FLOAT:
        *(float*)&vars[opcode->operand0]
          = (float)remainderf(*(float*)&vars[opcode->operand1], *(float*)&vars[opcode->operand2]);
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_DOUBLE:
        *(double*)&vars[opcode->operand0]
          = remainder(*(double*)&vars[opcode->operand1], *(double*)&vars[opcode->operand2]);
        break;
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_INT:
        *(SPVM_API_int*)&vars[opcode->operand0]
          = *(SPVM_API_int*)&vars[opcode->operand1] << (*(SPVM_API_int*)&vars[opcode->operand2] & 0x1f);
        break;
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0]
          = *(SPVM_API_long*)&vars[opcode->operand1] << (*(SPVM_API_int*)&vars[opcode->operand2] & 0x3f);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_INT:
        *(SPVM_API_int*)&vars[opcode->operand0]
          = *(SPVM_API_int*)&vars[opcode->operand1] >> (*(SPVM_API_int*)&vars[opcode->operand2] & 0x1f);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0]
          = *(SPVM_API_long*)&vars[opcode->operand1] >> (*(SPVM_API_int*)&vars[opcode->operand2] & 0x3f);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_UNSIGNED_INT:
        *(SPVM_API_int*)&vars[opcode->operand0]
          = (int32_t)((uint32_t)*(SPVM_API_int*)&vars[opcode->operand1] >> (*(SPVM_API_int*)&vars[opcode->operand2] & 0x1f));
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_UNSIGNED_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0]
          = (int64_t)((uint64_t)*(SPVM_API_long*)&vars[opcode->operand1] >> (*(SPVM_API_int*)&vars[opcode->operand2] & 0x3f));
        break;
      case SPVM_OPCODE_C_ID_BIT_AND_INT:
        *(SPVM_API_int*)&vars[opcode->operand0]
          = *(SPVM_API_int*)&vars[opcode->operand1] & *(SPVM_API_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_BIT_AND_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0]
          = *(SPVM_API_long*)&vars[opcode->operand1] & *(SPVM_API_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_BIT_OR_INT:
        *(SPVM_API_int*)&vars[opcode->operand0]
          = *(SPVM_API_int*)&vars[opcode->operand1] | *(SPVM_API_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_BIT_OR_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0]
          = *(SPVM_API_long*)&vars[opcode->operand1] | *(SPVM_API_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_BIT_XOR_INT:
        *(SPVM_API_int*)&vars[opcode->operand0]
          = *(SPVM_API_int*)&vars[opcode->operand1] ^ *(SPVM_API_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_BIT_XOR_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0]
          = *(SPVM_API_long*)&vars[opcode->operand1] ^ *(SPVM_API_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_NEGATE_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = -*(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NEGATE_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = -*(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NEGATE_FLOAT:
        *(float*)&vars[opcode->operand0] = -*(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NEGATE_DOUBLE:
        *(double*)&vars[opcode->operand0] = -*(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_COMPLEMENT_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = ~*(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_COMPLEMENT_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = ~*(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_INC_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] += (int32_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] += (int32_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] += (int32_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] += (int32_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_FLOAT:
        *(float*)&vars[opcode->operand0] += (int32_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_DOUBLE:
        *(double*)&vars[opcode->operand0] += (int32_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = (int64_t)*(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_FLOAT:
        *(float*)&vars[opcode->operand0] = (float)*(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_DOUBLE:
        *(double*)&vars[opcode->operand0] = (double)*(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = (int32_t)*(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_FLOAT:
        *(float*)&vars[opcode->operand0] = (float)*(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_DOUBLE:
        *(double*)&vars[opcode->operand0] = (double)*(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = (int32_t)*(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = (int64_t)*(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_DOUBLE:
        *(double*)&vars[opcode->operand0] = (double)*(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = (int32_t)*(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = (int64_t)*(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_FLOAT:
        *(float*)&vars[opcode->operand0] = (float)*(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = (int8_t)(*(SPVM_API_int*)&vars[opcode->operand1]);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = (int16_t)(*(SPVM_API_int*)&vars[opcode->operand1]);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = (int32_t)*(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = (int32_t)*(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = (int64_t)*(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_FLOAT:
        *(float*)&vars[opcode->operand0] = (float)*(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_DOUBLE:
        *(double*)&vars[opcode->operand0] = (double)*(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = (int8_t)*(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = (int64_t)*(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_FLOAT:
        *(float*)&vars[opcode->operand0] = (float)*(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_DOUBLE:
        *(double*)&vars[opcode->operand0] = (double)*(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = (int8_t)*(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = (int16_t)*(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = (int8_t)*(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = (int16_t)*(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = (int8_t)*(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = (int16_t)*(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = (int16_t)*(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = *(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = *(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = *(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_FLOAT:
        *(float*)&vars[opcode->operand0] = *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_DOUBLE:
        *(double*)&vars[opcode->operand0] = *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_STRING:
      {
        switch (opcode->id) {
          case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_STRING:
            sprintf(tmp_string, "%" PRId8, *(SPVM_API_byte*)&vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_STRING:
            sprintf(tmp_string, "%" PRId16, *(SPVM_API_short*)&vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_INT_TO_STRING:
            sprintf(tmp_string, "%" PRId32, *(SPVM_API_int*)&vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_STRING:
            sprintf(tmp_string, "%" PRId64, *(SPVM_API_long*)&vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_STRING:
            sprintf(tmp_string, "%g", *(SPVM_API_float*)&vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_STRING:
            sprintf(tmp_string, "%g", *(SPVM_API_double*)&vars[opcode->operand1]);
            break;
        }
        
        int32_t string_length = strlen(tmp_string);
        SPVM_API_OBJECT* string = api->new_string(api, (int8_t*)tmp_string, string_length);
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0], string);

        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_ARRAY_TO_STRING_ARRAY:
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_ARRAY_TO_STRING_ARRAY:
      case SPVM_OPCODE_C_ID_CONVERT_INT_ARRAY_TO_STRING_ARRAY:
      case SPVM_OPCODE_C_ID_CONVERT_LONG_ARRAY_TO_STRING_ARRAY:
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_ARRAY_TO_STRING_ARRAY:
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_ARRAY_TO_STRING_ARRAY:
      {
        SPVM_API_OBJECT* numeric_array = *(SPVM_API_OBJECT**)&vars[opcode->operand1];

        if (*(SPVM_API_OBJECT**)&vars[opcode->operand1] == NULL) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Array must not be undef");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          int32_t length = *(SPVM_API_int*)((intptr_t)*(SPVM_API_OBJECT**)&vars[opcode->operand1] + SPVM_RUNTIME_C_OBJECT_UNITS_LENGTH_BYTE_OFFSET);
          
          SPVM_API_OBJECT* string_array = api->new_object_array(api, SPVM_BASIC_TYPE_C_ID_STRING, length);
          
          switch (opcode->id) {
            case SPVM_OPCODE_C_ID_CONVERT_BYTE_ARRAY_TO_STRING_ARRAY: {
              int32_t index;
              for (index = 0; index < length; index++) {
                SPVM_API_byte value = *(SPVM_API_byte*)((intptr_t)numeric_array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_byte) * index);
                sprintf(tmp_string, "%" PRId8, value);
                SPVM_API_OBJECT* string = api->new_string(api, (int8_t*)tmp_string, strlen(tmp_string));
                SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(string);
                *(SPVM_API_OBJECT**)((intptr_t)string_array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_OBJECT*) * index) = string;
              }
              break;
            }
            case SPVM_OPCODE_C_ID_CONVERT_SHORT_ARRAY_TO_STRING_ARRAY: {
              int32_t index;
              for (index = 0; index < length; index++) {
                SPVM_API_short value = *(SPVM_API_short*)((intptr_t)numeric_array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_short) * index);
                sprintf(tmp_string, "%" PRId16, value);
                SPVM_API_OBJECT* string = api->new_string(api, (int8_t*)tmp_string, strlen(tmp_string));
                SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(string);
                *(SPVM_API_OBJECT**)((intptr_t)string_array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_OBJECT*) * index) = string;
              }
              break;
            }
            case SPVM_OPCODE_C_ID_CONVERT_INT_ARRAY_TO_STRING_ARRAY: {
              int32_t index;
              for (index = 0; index < length; index++) {
                SPVM_API_int value = *(SPVM_API_int*)((intptr_t)numeric_array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_int) * index);
                sprintf(tmp_string, "%" PRId32, value);
                SPVM_API_OBJECT* string = api->new_string(api, (int8_t*)tmp_string, strlen(tmp_string));
                SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(string);
                *(SPVM_API_OBJECT**)((intptr_t)string_array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_OBJECT*) * index) = string;
              }
              break;
            }
            case SPVM_OPCODE_C_ID_CONVERT_LONG_ARRAY_TO_STRING_ARRAY: {
              int32_t index;
              for (index = 0; index < length; index++) {
                SPVM_API_long value = *(SPVM_API_long*)((intptr_t)numeric_array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_long) * index);
                sprintf(tmp_string, "%" PRId64, value);
                SPVM_API_OBJECT* string = api->new_string(api, (int8_t*)tmp_string, strlen(tmp_string));
                SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(string);
                *(SPVM_API_OBJECT**)((intptr_t)string_array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_OBJECT*) * index) = string;
              }
              break;
            }
            case SPVM_OPCODE_C_ID_CONVERT_FLOAT_ARRAY_TO_STRING_ARRAY: {
              int32_t index;
              for (index = 0; index < length; index++) {
                SPVM_API_float value = *(SPVM_API_float*)((intptr_t)numeric_array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_float) * index);
                sprintf(tmp_string, "%g", value);
                SPVM_API_OBJECT* string = api->new_string(api, (int8_t*)tmp_string, strlen(tmp_string));
                SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(string);
                *(SPVM_API_OBJECT**)((intptr_t)string_array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_OBJECT*) * index) = string;
              }
              break;
            }
            case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_ARRAY_TO_STRING_ARRAY: {
              int32_t index;
              for (index = 0; index < length; index++) {
                SPVM_API_double value = *(SPVM_API_double*)((intptr_t)numeric_array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_double) * index);
                sprintf(tmp_string, "%g", value);
                SPVM_API_OBJECT* string = api->new_string(api, (int8_t*)tmp_string, strlen(tmp_string));
                SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(string);
                *(SPVM_API_OBJECT**)((intptr_t)string_array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_OBJECT*) * index) = string;
              }
              break;
            }
          }
          
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0], string_array);
        }

        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_UNDEF:
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0], NULL);
        break;
      case SPVM_OPCODE_C_ID_LOAD_CONSTANT_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = *(SPVM_API_byte*)&opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_LOAD_CONSTANT_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = *(SPVM_API_short*)&opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_LOAD_CONSTANT_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)&opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_LOAD_CONSTANT_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = *(SPVM_API_long*)&opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_LOAD_CONSTANT_FLOAT:
        *(float*)&vars[opcode->operand0] = *(float*)&opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_LOAD_CONSTANT_DOUBLE:
        *(double*)&vars[opcode->operand0] = *(double*)&opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_ARRAY_LOAD_BYTE: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand2];
        if (__builtin_expect(array == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Array must not be undef");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_UNITS_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string_chars(api, "Index is out of range");
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(SPVM_API_byte*)&vars[opcode->operand0] = *(SPVM_API_byte*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(int8_t) * index);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LOAD_SHORT: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Array must not be undef");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_UNITS_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string_chars(api, "Index is out of range");
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(SPVM_API_short*)&vars[opcode->operand0]
              = *(SPVM_API_short*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(int16_t) * index);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LOAD_INT: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Array must not be undef");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_UNITS_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string_chars(api, "Index is out of range");
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(int32_t) * index);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LOAD_LONG: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Array must not be undef");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_UNITS_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string_chars(api, "Index is out of range");
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(SPVM_API_long*)&vars[opcode->operand0] = *(SPVM_API_long*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(int64_t) * index);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LOAD_FLOAT: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Array must not be undef");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_UNITS_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string_chars(api, "Index is out of range");
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(float*)&vars[opcode->operand0] = *(float*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(float) * index);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LOAD_DOUBLE: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Array must not be undef");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_UNITS_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string_chars(api, "Index is out of range");
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(double*)&vars[opcode->operand0] = *(double*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(double) * index);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LOAD_OBJECT: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Array must not be undef");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_UNITS_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string_chars(api, "Index is out of range");
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(
              (SPVM_API_OBJECT**)&vars[opcode->operand0],
              *(SPVM_API_OBJECT**)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_OBJECT*) * index)
            );
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_BYTE: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Array must not be undef");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_UNITS_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string_chars(api, "Index is out of range");
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(SPVM_API_byte*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(int8_t) * index) = *(SPVM_API_byte*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_SHORT: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Array must not be undef");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_UNITS_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string_chars(api, "Index is out of range");
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(SPVM_API_short*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(int16_t) * index) = *(SPVM_API_short*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_INT: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Array must not be undef");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_UNITS_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string_chars(api, "Index is out of range");
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(SPVM_API_int*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(int32_t) * index) = *(SPVM_API_int*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_LONG: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Array must not be undef");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_UNITS_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string_chars(api, "Index is out of range");
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(SPVM_API_long*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(int64_t) * index) = *(SPVM_API_long*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_FLOAT: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Array must not be undef");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_UNITS_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string_chars(api, "Index is out of range");
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(float*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(float) * index) = *(float*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_DOUBLE: {
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Array must not be undef");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_UNITS_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string_chars(api, "Index is out of range");
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            *(double*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(double) * index) = *(double*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_OBJECT: {
        
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Array must not be undef");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_UNITS_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string_chars(api, "Index is out of range");
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(
              (SPVM_API_OBJECT**)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_OBJECT*) * index),
              *(SPVM_API_OBJECT**)&vars[opcode->operand2]
            );
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_UNDEF: {
        
        SPVM_API_OBJECT* array = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        int32_t index = *(SPVM_API_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Array must not be undef");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_API_int*)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_UNITS_LENGTH_BYTE_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string_chars(api, "Index is out of range");
            api->set_exception(api, exception);
            croak_flag = 1;
          }
          else {
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(
              (SPVM_API_OBJECT**)((intptr_t)array + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_OBJECT*) * index),
              NULL
            );
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_BYTE:
        *(SPVM_API_byte*)&vars[opcode->operand0] = *(SPVM_API_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_MOVE_SHORT:
        *(SPVM_API_short*)&vars[opcode->operand0] = *(SPVM_API_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_MOVE_INT:
        *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_MOVE_LONG:
        *(SPVM_API_long*)&vars[opcode->operand0] = *(SPVM_API_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_MOVE_FLOAT:
        *(SPVM_API_float*)&vars[opcode->operand0] = *(SPVM_API_float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_MOVE_DOUBLE:
        *(SPVM_API_double*)&vars[opcode->operand0] = *(SPVM_API_double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_MOVE_OBJECT:
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0], *(SPVM_API_OBJECT**)&vars[opcode->operand1]);
        break;
      case SPVM_OPCODE_C_ID_PUSH_MORTAL: {
        mortal_stack_top++;
        *(int32_t*)&mortal_stack[mortal_stack_top] = opcode->operand0;
        
        break;
      }
      case SPVM_OPCODE_C_ID_LEAVE_SCOPE: {
        int32_t mortal_stack_current_base = opcode->operand0;
        int32_t object_var_index_index;
        for (object_var_index_index = mortal_stack_current_base; object_var_index_index <= mortal_stack_top; object_var_index_index++) {
          int32_t var_index = mortal_stack[object_var_index_index].int_value;
          
          if (*(SPVM_API_OBJECT**)&vars[var_index] != NULL) {
            if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(*(SPVM_API_OBJECT**)&vars[var_index]) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*(SPVM_API_OBJECT**)&vars[var_index]); }
            else { api->dec_ref_count(api, *(SPVM_API_OBJECT**)&vars[var_index]); }
          }
          
          *(SPVM_API_OBJECT**)&vars[var_index] = NULL;
        }
        
        mortal_stack_top = mortal_stack_current_base - 1;
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT: {
        // Get subroutine ID
        int32_t basic_type_id = opcode->operand1;
        
        SPVM_API_OBJECT* object = api->new_object(api, basic_type_id);
        
        // Push object
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_BYTE_ARRAY: {
        
        // length
        int32_t length = *(SPVM_API_int*)&vars[opcode->operand1];
        
        SPVM_API_OBJECT* object = api->new_byte_array(api, length);
        
        // Set array
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY: {
        
        // length
        int32_t length = *(SPVM_API_int*)&vars[opcode->operand1];
        
        SPVM_API_OBJECT* object = api->new_short_array(api, length);
        
        // Set array
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_INT_ARRAY: {
        
        // length
        int32_t length = *(SPVM_API_int*)&vars[opcode->operand1];
        
        SPVM_API_OBJECT* object = api->new_int_array(api, length);
        
        // Set array
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_LONG_ARRAY: {
        
        // length
        int32_t length = *(SPVM_API_int*)&vars[opcode->operand1];
        
        SPVM_API_OBJECT* object = api->new_long_array(api, length);
        
        // Set array
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY: {
        
        // length
        int32_t length = *(SPVM_API_int*)&vars[opcode->operand1];
        
        SPVM_API_OBJECT* object = api->new_float_array(api, length);
        
        // Set array
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY: {
        
        // length
        int32_t length = *(SPVM_API_int*)&vars[opcode->operand1];
        
        SPVM_API_OBJECT* object = api->new_double_array(api, length);
        
        // Set array
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        
        // length
        int32_t length = *(SPVM_API_int*)&vars[opcode->operand2];
        
        SPVM_API_OBJECT* object = api->new_object_array(api, basic_type_id, length);
        
        // Set object
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULTI_ARRAY: {
        int32_t basic_type_id = (uint32_t)opcode->operand1 & 0xFFFFFF;
        int32_t dimension  = (uint32_t)opcode->operand1 >> 24;
        
        // length
        int32_t length = *(SPVM_API_int*)&vars[opcode->operand2];
        
        SPVM_API_OBJECT* object = api->new_multi_array(api, basic_type_id, dimension, length);
        
        // Set object
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING: {
        int32_t constant_id = opcode->operand1;
        
        SPVM_OP* op_constant = SPVM_LIST_fetch(compiler->op_constants, constant_id);
        SPVM_CONSTANT* constant = op_constant->uv.constant;
        
        SPVM_API_OBJECT* string = api->new_string(api, (int8_t*)constant->value.string_value, constant->string_length);
        
        // Set string
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0] , string);

        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LENGTH:
        if (*(SPVM_API_OBJECT**)&vars[opcode->operand1] == NULL) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Can't get array length of undef value.");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)((intptr_t)*(SPVM_API_OBJECT**)&vars[opcode->operand1] + SPVM_RUNTIME_C_OBJECT_UNITS_LENGTH_BYTE_OFFSET);
        }
        break;
      case SPVM_OPCODE_C_ID_GET_FIELD_BYTE: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Object must be not undef.");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_byte*)&vars[opcode->operand0] = *(SPVM_API_byte*)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + opcode->operand2);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_SHORT: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand1];

        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Object must be not undef.");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_short*)&vars[opcode->operand0] = *(SPVM_API_short*)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + opcode->operand2);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_INT: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Object must be not undef.");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + opcode->operand2);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_LONG: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Object must be not undef.");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_long*)&vars[opcode->operand0] = *(SPVM_API_long*)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + opcode->operand2);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_FLOAT: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Object must be not undef.");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(float*)&vars[opcode->operand0] = *(float*)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + opcode->operand2);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Object must be not undef.");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(double*)&vars[opcode->operand0] = *(double*)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + opcode->operand2);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_OBJECT: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Object must be not undef.");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0], *(SPVM_API_OBJECT**)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + opcode->operand2));
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_BYTE: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Object must be not undef.");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_byte*)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + opcode->operand1) = *(SPVM_API_byte*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_SHORT: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Object must be not undef.");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_short*)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + opcode->operand1) = *(SPVM_API_short*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_INT: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Object must be not undef.");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_int*)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + opcode->operand1) = *(SPVM_API_int*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_LONG: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Object must be not undef.");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(SPVM_API_long*)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + opcode->operand1) = *(SPVM_API_long*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_FLOAT: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Object must be not undef.");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(float*)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + opcode->operand1) = *(float*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        
        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Object must be not undef.");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          *(double*)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + opcode->operand1) = *(double*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_OBJECT: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand0];

        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Object must be not undef.");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(
            (SPVM_API_OBJECT**)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + opcode->operand1),
            *(SPVM_API_OBJECT**)&vars[opcode->operand2]
          );
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_UNDEF: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand0];

        if (__builtin_expect(object == NULL, 0)) {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Object must be not undef.");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        else {
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(
            (SPVM_API_OBJECT**)((intptr_t)object + SPVM_RUNTIME_C_OBJECT_HEADER_BYTE_SIZE + opcode->operand1),
            NULL
          );
        }
        break;
      }
      case SPVM_OPCODE_C_ID_WEAKEN_FIELD_OBJECT: {
        
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        
        api->weaken_object_field(api, object, opcode->operand1);
        
        if (api->get_exception(api)) {
          croak_flag = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CONCAT: {
        SPVM_API_OBJECT* concat_string = api->concat(api, *(SPVM_API_OBJECT**)&vars[opcode->operand1], *(SPVM_API_OBJECT**)&vars[opcode->operand2]);
        if (concat_string == NULL) {
          croak_flag = 1;
        }
        else {
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(
            (SPVM_API_OBJECT**)&vars[opcode->operand0],
            concat_string
          );
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_LOAD_EXCEPTION_VAR: {
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0], api->get_exception(api));
        
        break;
      }
      case SPVM_OPCODE_C_ID_STORE_EXCEPTION_VAR: {
        
        api->set_exception(api, *(SPVM_API_OBJECT**)&vars[opcode->operand0]);
        
        break;
      }
      case SPVM_OPCODE_C_ID_STORE_EXCEPTION_VAR_UNDEF: {
        
        api->set_exception(api, NULL);
        
        break;
      }
      case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_BYTE: {

        *(SPVM_API_byte*)&vars[opcode->operand0] = *(SPVM_API_byte*)&(*(SPVM_API_VALUE**)(api->get_runtime(api) + offsetof(SPVM_RUNTIME, package_vars)))[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_SHORT: {
        
        *(SPVM_API_short*)&vars[opcode->operand0] = *(SPVM_API_short*)&(*(SPVM_API_VALUE**)(api->get_runtime(api) + offsetof(SPVM_RUNTIME, package_vars)))[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_INT: {
        *(SPVM_API_int*)&vars[opcode->operand0] = *(SPVM_API_int*)&(*(SPVM_API_VALUE**)(api->get_runtime(api) + offsetof(SPVM_RUNTIME, package_vars)))[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_LONG: {
        *(SPVM_API_long*)&vars[opcode->operand0] = *(SPVM_API_long*)&(*(SPVM_API_VALUE**)(api->get_runtime(api) + offsetof(SPVM_RUNTIME, package_vars)))[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_FLOAT: {
        *(float*)&vars[opcode->operand0] = *(float*)&(*(SPVM_API_VALUE**)(api->get_runtime(api) + offsetof(SPVM_RUNTIME, package_vars)))[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_DOUBLE: {
        *(double*)&vars[opcode->operand0] = *(double*)&(*(SPVM_API_VALUE**)(api->get_runtime(api) + offsetof(SPVM_RUNTIME, package_vars)))[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_LOAD_PACKAGE_VAR_OBJECT: {
       SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0], *(SPVM_API_OBJECT**)&(*(SPVM_API_VALUE**)(api->get_runtime(api) + offsetof(SPVM_RUNTIME, package_vars)))[opcode->operand1]);
        
        break;
      }
      case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_BYTE: {
        *(SPVM_API_byte*)&(*(SPVM_API_VALUE**)(api->get_runtime(api) + offsetof(SPVM_RUNTIME, package_vars)))[opcode->operand0] = *(SPVM_API_byte*)&vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_SHORT: {
        *(SPVM_API_short*)&(*(SPVM_API_VALUE**)(api->get_runtime(api) + offsetof(SPVM_RUNTIME, package_vars)))[opcode->operand0] = *(SPVM_API_short*)&vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_INT: {
        *(SPVM_API_int*)&(*(SPVM_API_VALUE**)(api->get_runtime(api) + offsetof(SPVM_RUNTIME, package_vars)))[opcode->operand0] = *(SPVM_API_int*)&vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_LONG: {
        *(SPVM_API_long*)&(*(SPVM_API_VALUE**)(api->get_runtime(api) + offsetof(SPVM_RUNTIME, package_vars)))[opcode->operand0] = *(SPVM_API_long*)&vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_FLOAT: {
        *(float*)&(*(SPVM_API_VALUE**)(api->get_runtime(api) + offsetof(SPVM_RUNTIME, package_vars)))[opcode->operand0] = *(float*)&vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_DOUBLE: {
        *(double*)&(*(SPVM_API_VALUE**)(api->get_runtime(api) + offsetof(SPVM_RUNTIME, package_vars)))[opcode->operand0] = *(double*)&vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_OBJECT: {
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&(*(SPVM_API_VALUE**)(api->get_runtime(api) + offsetof(SPVM_RUNTIME, package_vars)))[opcode->operand0], *(SPVM_API_OBJECT**)&vars[opcode->operand1]);
        
        break;
      }
      case SPVM_OPCODE_C_ID_STORE_PACKAGE_VAR_UNDEF: {
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&(*(SPVM_API_VALUE**)(api->get_runtime(api) + offsetof(SPVM_RUNTIME, package_vars)))[opcode->operand0], NULL);
        
        break;
      }
      case SPVM_OPCODE_C_ID_GOTO:
        opcode_index = opcode->operand0;
        continue;
      case SPVM_OPCODE_C_ID_IF_EQ_ZERO: {
        if (condition_flag == 0) {
          opcode_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_IF_NE_ZERO: {
        if (condition_flag) {
          opcode_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_BYTE:
        call_sub_arg_stack_top++;
        *(SPVM_API_byte*)&call_sub_args[call_sub_arg_stack_top] = *(SPVM_API_byte*)&vars[opcode->operand0];
        
        break;
      case SPVM_OPCODE_C_ID_PUSH_ARG_SHORT:
        call_sub_arg_stack_top++;
        *(SPVM_API_short*)&call_sub_args[call_sub_arg_stack_top] = *(SPVM_API_short*)&vars[opcode->operand0];
        
        break;
      case SPVM_OPCODE_C_ID_PUSH_ARG_INT:
        call_sub_arg_stack_top++;
        *(SPVM_API_int*)&call_sub_args[call_sub_arg_stack_top] = *(SPVM_API_int*)&vars[opcode->operand0];
        
        break;
      case SPVM_OPCODE_C_ID_PUSH_ARG_LONG:
        call_sub_arg_stack_top++;
        *(SPVM_API_long*)&call_sub_args[call_sub_arg_stack_top] = *(SPVM_API_long*)&vars[opcode->operand0];
        
        break;
      case SPVM_OPCODE_C_ID_PUSH_ARG_FLOAT:
        call_sub_arg_stack_top++;
        *(SPVM_API_float*)&call_sub_args[call_sub_arg_stack_top] = *(SPVM_API_float*)&vars[opcode->operand0];
        
        break;
      case SPVM_OPCODE_C_ID_PUSH_ARG_DOUBLE:
        call_sub_arg_stack_top++;
        *(SPVM_API_double*)&call_sub_args[call_sub_arg_stack_top] = *(SPVM_API_double*)&vars[opcode->operand0];
        
        break;
      case SPVM_OPCODE_C_ID_PUSH_ARG_OBJECT:
        call_sub_arg_stack_top++;
        *(SPVM_API_OBJECT**)&call_sub_args[call_sub_arg_stack_top] = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        
        break;
      case SPVM_OPCODE_C_ID_PUSH_ARG_UNDEF:
        call_sub_arg_stack_top++;
        *(SPVM_API_OBJECT**)&call_sub_args[call_sub_arg_stack_top] = NULL;
        
        break;
      case SPVM_OPCODE_C_ID_CHECK_CAST: {
        SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand1];

        int32_t cast_basic_type_id = (uint32_t)opcode->operand2 & 0xFFFFFF;
        int32_t cast_type_dimension  = (uint32_t)opcode->operand2 >> 24;
        
        _Bool can_assign = api->check_cast(api, cast_basic_type_id, cast_type_dimension, object);
        if (can_assign) {
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0], object);
        }
        else {
          SPVM_API_OBJECT* exception = api->new_string_chars(api, "Can't cast uncompatible type.");
          api->set_exception(api, exception);
          croak_flag = 1;
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB:
      case SPVM_OPCODE_C_ID_CALL_INTERFACE_METHOD:
      {
        int32_t decl_sub_id = opcode->operand1;

        // Declare subroutine
        SPVM_OP* op_sub_decl = SPVM_LIST_fetch(compiler->op_subs, decl_sub_id);
        SPVM_SUB* decl_sub = op_sub_decl->uv.sub;
        
        // Declare subroutine return type
        SPVM_TYPE* decl_sub_return_type = decl_sub->op_return_type->uv.type;
        
        int32_t decl_sub_return_basic_type_id = decl_sub_return_type->basic_type->id;
        int32_t decl_sub_return_return_dimension = decl_sub_return_type->dimension;
        
        // Declare subroutine argument length
        int32_t decl_sub_args_length = decl_sub->op_args->length;
        
        // Call subroutine id
        int32_t call_sub_id;
        if (opcode->id == SPVM_OPCODE_C_ID_CALL_SUB) {
           call_sub_id = decl_sub_id;
        }
        else if (opcode->id == SPVM_OPCODE_C_ID_CALL_INTERFACE_METHOD) {
          SPVM_API_OBJECT* object = *(SPVM_API_OBJECT**)&vars[opcode->operand2];
          call_sub_id = api->get_sub_id_interface_method(api, object, decl_sub_id);
        }
        else {
          assert(0);
        }
        
        call_sub_arg_stack_top -= decl_sub_args_length;
        
        // Call subroutine
        if (decl_sub_return_return_dimension == 0) {
          if (decl_sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_VOID) {
            api->call_void_sub(api, call_sub_id, call_sub_args);
            if (api->get_exception(api)) {
              croak_flag = 1;
            }
          }
          else if (decl_sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_BYTE) {
            SPVM_API_byte value = api->call_byte_sub(api, call_sub_id, call_sub_args);
            if (api->get_exception(api)) {
              croak_flag = 1;
            }
            else {
              *(SPVM_API_byte*)&vars[opcode->operand0] = value;
            }
          }
          else if (decl_sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_SHORT) {
            SPVM_API_short value = api->call_short_sub(api, call_sub_id, call_sub_args);
            if (api->get_exception(api)) {
              croak_flag = 1;
            }
            else {
              *(SPVM_API_short*)&vars[opcode->operand0] = value;
            }
          }
          else if (decl_sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_INT) {
            SPVM_API_int value = api->call_int_sub(api, call_sub_id, call_sub_args);
            if (api->get_exception(api)) {
              croak_flag = 1;
            }
            else {
              *(SPVM_API_int*)&vars[opcode->operand0] = value;
            }
          }
          else if (decl_sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_LONG) {
            SPVM_API_long value = api->call_long_sub(api, call_sub_id, call_sub_args);
            if (api->get_exception(api)) {
              croak_flag = 1;
            }
            else {
              *(SPVM_API_long*)&vars[opcode->operand0] = value;
            }
          }
          else if (decl_sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
            SPVM_API_float value = api->call_float_sub(api, call_sub_id, call_sub_args);
            if (api->get_exception(api)) {
              croak_flag = 1;
            }
            else {
              *(SPVM_API_float*)&vars[opcode->operand0] = value;
            }
          }
          else if (decl_sub_return_basic_type_id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
            SPVM_API_double value = api->call_double_sub(api, call_sub_id, call_sub_args);
            if (api->get_exception(api)) {
              croak_flag = 1;
            }
            else {
              *(SPVM_API_double*)&vars[opcode->operand0] = value;
            }
          }
          else {
            SPVM_API_OBJECT* value = api->call_object_sub(api, call_sub_id, call_sub_args);
            if (api->get_exception(api)) {
              croak_flag = 1;
            }
            else {
              SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0], value);
            }
          }
        }
        else {
          SPVM_API_OBJECT* value = api->call_object_sub(api, call_sub_id, call_sub_args);
          if (api->get_exception(api)) {
            croak_flag = 1;
          }
          else {
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((SPVM_API_OBJECT**)&vars[opcode->operand0], value);
          }
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_IF_CROAK_CATCH: {
        if (croak_flag) {
          croak_flag = 0;
          
          // Exception stack trace
          api->set_exception(api, api->create_exception_stack_trace(api, api->get_exception(api), opcode->operand1, opcode->operand2));
          opcode_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_IF_CROAK_RETURN: {
        if (croak_flag) {
          // Exception stack trace
          api->set_exception(api, api->create_exception_stack_trace(api, api->get_exception(api), opcode->operand1, opcode->operand2));
          opcode_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CROAK_FLAG_TRUE: {
        croak_flag = 1;
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_VOID:
      {
        opcode_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_BYTE:
      {
        *(SPVM_API_byte*)&return_value = *(SPVM_API_byte*)&vars[opcode->operand0];
        opcode_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_SHORT:
      {
        *(SPVM_API_short*)&return_value = *(SPVM_API_short*)&vars[opcode->operand0];
        opcode_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_INT:
      {
        *(SPVM_API_int*)&return_value = *(SPVM_API_int*)&vars[opcode->operand0];
        opcode_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_LONG:
      {
        *(SPVM_API_long*)&return_value = *(SPVM_API_long*)&vars[opcode->operand0];
        opcode_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_FLOAT:
      {
        *(SPVM_API_float*)&return_value = *(SPVM_API_float*)&vars[opcode->operand0];
        opcode_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_DOUBLE:
      {
        *(SPVM_API_double*)&return_value = *(SPVM_API_double*)&vars[opcode->operand0];
        opcode_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_OBJECT:
      {
        *(SPVM_API_OBJECT**)&return_value = *(SPVM_API_OBJECT**)&vars[opcode->operand0];
        // Increment ref count of return value not to release by leave scope
        if (*(SPVM_API_OBJECT**)&return_value != NULL) {
          SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(*(SPVM_API_OBJECT**)&return_value);
        }
        opcode_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_UNDEF:
      {
        *(SPVM_API_OBJECT**)&return_value = NULL;
        opcode_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_TABLE_SWITCH: {
        // default offset
        int32_t default_offset = opcode->operand1;
        
        // min
        int32_t min = (opcode + 1)->operand0;
        
        // max
        int32_t max = (opcode + 1)->operand1;
        
        if (*(SPVM_API_int*)&vars[opcode->operand0] >= min && *(SPVM_API_int*)&vars[opcode->operand0] <= max) {
          int32_t branch_offset = (opcode + 2 + *(SPVM_API_int*)&vars[opcode->operand0] - min)->operand1;
          opcode_index = branch_offset;
        }
        else {
          opcode_index = default_offset;
        }
        
        continue;
      }
      case SPVM_OPCODE_C_ID_LOOKUP_SWITCH: {
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
      case SPVM_OPCODE_C_ID_END_SUB: {
        goto label_END_SUB;
      }
    }
    opcode_index++;
  }

  label_END_SUB:
    
  // Croak
  if (!croak_flag) {
    // Decrement ref count of return value
    if (sub_return_type_dimension > 0 || sub_return_basic_type_id > SPVM_BASIC_TYPE_C_ID_DOUBLE) {
      if (*(SPVM_API_OBJECT**)&return_value != NULL) {
        SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*(SPVM_API_OBJECT**)&return_value);
      }
    }
    
    api->set_exception(api, NULL);
  }
  
  // Free call stack
  SPVM_RUNTIME_ALLOCATOR_free_object(api, runtime->allocator, call_stack_object);
  
  return return_value;
}
