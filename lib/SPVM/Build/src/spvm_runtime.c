#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stddef.h>

#include "spvm_native.h"
#include "spvm_runtime_api.h"
#include "spvm_opcode.h"
#include "spvm_object.h"
#include "spvm_type.h"
#include "spvm_runtime.h"
#include "spvm_opcode.h"
#include "spvm_opcode_array.h"
#include "spvm_util_allocator.h"
#include "spvm_runtime_allocator.h"

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
#include "spvm_package_var.h"
#include "spvm_package_var_access.h"
#include "spvm_field_access.h"
#include "spvm_call_sub.h"
#include "spvm_constant.h"
#include "spvm_switch_info.h"
#include "spvm_case_info.h"

int32_t SPVM_RUNTIME_call_sub(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* stack) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(env);
  
  SPVM_COMPILER* compiler = runtime->compiler;

  // Constant pool sub
  SPVM_SUB* sub = SPVM_LIST_fetch(compiler->subs, sub_id);
  
  int32_t exception_flag = 0;
  if (sub->have_native_desc) {
    int32_t original_mortal_stack_top = SPVM_RUNTIME_API_enter_scope(env);
    exception_flag = SPVM_RUNTIME_call_sub_native(env, sub_id, stack);
    SPVM_RUNTIME_API_leave_scope(env, original_mortal_stack_top);
  }
  else if (sub->is_compiled) {
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
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(env);
  SPVM_COMPILER* compiler = runtime->compiler;

  // Constant pool sub
  SPVM_SUB* sub = SPVM_LIST_fetch(compiler->subs, sub_id);

  // Subroutine is Precompile
  assert(sub->is_compiled);
  
  // Call precompile subroutine
  int32_t (*precompile_address)(SPVM_ENV*, SPVM_VALUE*) = sub->precompile_address;
  return (*precompile_address)(env, stack);
}

int32_t SPVM_RUNTIME_call_sub_native(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* stack) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(env);
  SPVM_COMPILER* compiler = runtime->compiler;

  // Constant pool sub
  SPVM_SUB* sub = SPVM_LIST_fetch(compiler->subs, sub_id);

  // Subroutine is native
  assert(sub->have_native_desc);

  // Call native subrotuine
  int32_t (*native_address)(SPVM_ENV*, SPVM_VALUE*) = sub->native_address;
  return (*native_address)(env, stack);
}

int32_t SPVM_RUNTIME_call_sub_vm(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* stack) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(env);
  SPVM_COMPILER* compiler = runtime->compiler;

  // Subroutine
  SPVM_SUB* sub = SPVM_LIST_fetch(compiler->subs, sub_id);

  // Subroutine return type
  SPVM_TYPE* sub_return_type = sub->op_return_type->uv.type;
  int32_t sub_return_type_width = SPVM_TYPE_get_width(compiler, sub_return_type->basic_type->id, sub_return_type->dimension, sub_return_type->flag);
  
  // Package
  SPVM_PACKAGE* package = sub->package;

  // Operation codes
  SPVM_OPCODE* opcodes = compiler->opcode_array->values;
  register int32_t opcode_rel_index = 0;
  
  // Operation code base
  int32_t sub_opcode_base = sub->opcode_base;

  // Call subroutine argument stack top
  int32_t call_sub_arg_stack_top = 0;
  
  // Condition flag
  register int32_t condition_flag = 0;

  // Croak flag
  int32_t exception_flag = 0;
  
  // Buffer for string convertion
  char string_convert_buffer[30];
  
  // Variables
  SPVM_VALUE* vars = NULL;
  int32_t var_alloc_length = SPVM_SUB_get_var_alloc_length(compiler, sub);
  if (var_alloc_length > 0) {
    vars = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(SPVM_VALUE) * var_alloc_length);
  }
  
  // Copy arguments to variables
  if (vars) {
    int32_t arg_alloc_length = SPVM_SUB_get_arg_alloc_length(compiler, sub);
    if (arg_alloc_length > 0) {
      memcpy(vars, stack, sizeof(SPVM_VALUE) * arg_alloc_length);
    }
  }
  
  // If arg is object, increment reference count
  {
    int32_t arg_index;
    for (arg_index = 0; arg_index < sub->op_args->length; arg_index++) {
      SPVM_OP* op_arg = SPVM_LIST_fetch(sub->op_args, arg_index);
      SPVM_TYPE* arg_type = op_arg->uv.my->op_type->uv.type;
      _Bool arg_type_is_value_t = SPVM_TYPE_is_value_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag);
      if (SPVM_TYPE_is_object_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag) && !arg_type_is_value_t) {
        SPVM_MY* my_arg = op_arg->uv.my;
        void* object = *(void**)&vars[my_arg->var_id];
        if (object != NULL) {
          SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(object);
        }
      }
    }
  }
  
  // Mortal stack
  int32_t* mortal_stack = NULL;
  if (sub->mortal_stack_length > 0) {
    mortal_stack = SPVM_RUNTIME_ALLOCATOR_alloc_memory_block_zero(runtime, sizeof(int32_t) * sub->mortal_stack_length);
  }
  int32_t mortal_stack_top = 0;
  
  while (1) {
    SPVM_OPCODE* opcode = &(opcodes[sub_opcode_base + opcode_rel_index]);
    
    switch (opcode->id) {
      case SPVM_OPCODE_C_ID_BOOL_INT:
        condition_flag = !!*(SPVM_VALUE_int*)&vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_ID_BOOL_LONG:
        condition_flag = !!*(SPVM_VALUE_long*)&vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_ID_BOOL_FLOAT:
        condition_flag = !!*(float*)&vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_ID_BOOL_DOUBLE:
        condition_flag = !!*(double*)&vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_ID_BOOL_OBJECT:
        condition_flag = !!*(void**)&vars[opcode->operand0];
        break;
      case SPVM_OPCODE_C_ID_IS_UNDEF:
        condition_flag = *(void**)&vars[opcode->operand0] == NULL;
        break;
      case SPVM_OPCODE_C_ID_IS_NOT_UNDEF:
        condition_flag = *(void**)&vars[opcode->operand0] != NULL;
        break;
      case SPVM_OPCODE_C_ID_EQ_INT:
        condition_flag = *(SPVM_VALUE_int*)&vars[opcode->operand0] == *(SPVM_VALUE_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_EQ_LONG:
        condition_flag = *(SPVM_VALUE_long*)&vars[opcode->operand0] == *(SPVM_VALUE_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_EQ_FLOAT:
        condition_flag = *(float*)&vars[opcode->operand0] == *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_EQ_DOUBLE:
        condition_flag = *(double*)&vars[opcode->operand0] == *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_EQ_OBJECT:
        condition_flag = *(void**)&vars[opcode->operand0] == *(void**)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NE_INT:
        condition_flag = *(SPVM_VALUE_int*)&vars[opcode->operand0] != *(SPVM_VALUE_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NE_LONG:
        condition_flag = *(SPVM_VALUE_long*)&vars[opcode->operand0] != *(SPVM_VALUE_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NE_FLOAT:
        condition_flag = *(float*)&vars[opcode->operand0] != *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NE_DOUBLE:
        condition_flag = *(double*)&vars[opcode->operand0] != *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NE_OBJECT:
        condition_flag = *(void**)&vars[opcode->operand0] != *(void**)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GT_INT:
        condition_flag = *(SPVM_VALUE_int*)&vars[opcode->operand0] > *(SPVM_VALUE_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GT_LONG:
        condition_flag = *(SPVM_VALUE_long*)&vars[opcode->operand0] > *(SPVM_VALUE_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GT_FLOAT:
        condition_flag = *(float*)&vars[opcode->operand0] > *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GT_DOUBLE:
        condition_flag = *(double*)&vars[opcode->operand0] > *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GE_INT:
        condition_flag = *(SPVM_VALUE_int*)&vars[opcode->operand0] >= *(SPVM_VALUE_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GE_LONG:
        condition_flag = *(SPVM_VALUE_long*)&vars[opcode->operand0] >= *(SPVM_VALUE_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GE_FLOAT:
        condition_flag = *(float*)&vars[opcode->operand0] >= *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GE_DOUBLE:
        condition_flag = *(double*)&vars[opcode->operand0] >= *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LT_INT:
        condition_flag = *(SPVM_VALUE_int*)&vars[opcode->operand0] < *(SPVM_VALUE_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LT_LONG:
        condition_flag = *(SPVM_VALUE_long*)&vars[opcode->operand0] < *(SPVM_VALUE_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LT_FLOAT:
        condition_flag = *(float*)&vars[opcode->operand0] < *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LT_DOUBLE:
        condition_flag = *(double*)&vars[opcode->operand0] < *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LE_INT:
        condition_flag = *(SPVM_VALUE_int*)&vars[opcode->operand0] <= *(SPVM_VALUE_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LE_LONG:
        condition_flag = *(SPVM_VALUE_long*)&vars[opcode->operand0] <= *(SPVM_VALUE_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LE_FLOAT:
        condition_flag = *(float*)&vars[opcode->operand0] <= *(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_LE_DOUBLE:
        condition_flag = *(double*)&vars[opcode->operand0] <= *(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_ISA:
      {
        void* object = *(void**)&vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        SPVM_TYPE* type = SPVM_LIST_fetch(sub->info_types, rel_id);
        int32_t basic_type_id = type->basic_type->id;
        int32_t dimension = type->dimension;
        
        condition_flag = (*(int32_t*)(object + (intptr_t)env->object_basic_type_id_byte_offset) == basic_type_id && *(int32_t*)(object + (intptr_t)env->object_dimension_byte_offset) == dimension);
        
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_EQ:
      case SPVM_OPCODE_C_ID_STRING_NE:
      case SPVM_OPCODE_C_ID_STRING_GT:
      case SPVM_OPCODE_C_ID_STRING_GE:
      case SPVM_OPCODE_C_ID_STRING_LT:
      case SPVM_OPCODE_C_ID_STRING_LE:
      {
        void* object1 = *(void**)&vars[opcode->operand0];
        void* object2 = *(void**)&vars[opcode->operand1];

        int32_t length1 = *(SPVM_VALUE_int*)((intptr_t)object1 + (intptr_t)env->object_elements_length_byte_offset);
        int32_t length2 = *(SPVM_VALUE_int*)((intptr_t)object2 + (intptr_t)env->object_elements_length_byte_offset);
        
        SPVM_VALUE_byte* bytes1 = *(SPVM_VALUE_byte**)&(*(void**)object1);
        SPVM_VALUE_byte* bytes2 = *(SPVM_VALUE_byte**)&(*(void**)object2);
        
        int32_t short_string_length = length1 < length1 ? length1 : length2;
        int32_t retval = memcmp(bytes1, bytes2, short_string_length);
        int32_t cmp;
        if (retval) {
          cmp = retval < 0 ? -1 : 1;
        } else if (length1 == length2) {
          cmp = 0;
        } else {
          cmp = length1 < length2 ? -1 : 1;
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
        *(SPVM_VALUE_int*)&vars[opcode->operand0] = *(SPVM_VALUE_int*)&vars[opcode->operand1] + *(SPVM_VALUE_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_ADD_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0] = *(SPVM_VALUE_long*)&vars[opcode->operand1] + *(SPVM_VALUE_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_ADD_FLOAT:
        *(float*)&vars[opcode->operand0] = *(float*)&vars[opcode->operand1] + *(float*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_ADD_DOUBLE:
        *(double*)&vars[opcode->operand0] = *(double*)&vars[opcode->operand1] + *(double*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_INT:
        *(SPVM_VALUE_int*)&vars[opcode->operand0] = *(SPVM_VALUE_int*)&vars[opcode->operand1] - *(SPVM_VALUE_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0] = *(SPVM_VALUE_long*)&vars[opcode->operand1] - *(SPVM_VALUE_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_FLOAT:
        *(float*)&vars[opcode->operand0] = *(float*)&vars[opcode->operand1] - *(float*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_DOUBLE:
        *(double*)&vars[opcode->operand0] = *(double*)&vars[opcode->operand1] - *(double*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_INT:
        *(SPVM_VALUE_int*)&vars[opcode->operand0] = *(SPVM_VALUE_int*)&vars[opcode->operand1] * *(SPVM_VALUE_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0] = *(SPVM_VALUE_long*)&vars[opcode->operand1] * *(SPVM_VALUE_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_FLOAT:
        *(float*)&vars[opcode->operand0] = *(float*)&vars[opcode->operand1] * *(float*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_DOUBLE:
        *(double*)&vars[opcode->operand0] = *(double*)&vars[opcode->operand1] * *(double*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_INT:
        if (__builtin_expect(*(SPVM_VALUE_int*)&vars[opcode->operand2] == 0, 0)) {
          void* exception = env->new_string_raw(env, "0 division", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_int*)&vars[opcode->operand0]
            = *(SPVM_VALUE_int*)&vars[opcode->operand1] / *(SPVM_VALUE_int*)&vars[opcode->operand2];
        }
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_LONG:
        if (__builtin_expect(*(SPVM_VALUE_long*)&vars[opcode->operand2] == 0, 0)) {
          void* exception = env->new_string_raw(env, "0 division", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_long*)&vars[opcode->operand0]
            = *(SPVM_VALUE_long*)&vars[opcode->operand1] / *(SPVM_VALUE_long*)&vars[opcode->operand2];
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
        if (__builtin_expect(*(SPVM_VALUE_short*)&vars[opcode->operand2] == 0, 0)) {
          void* exception = env->new_string_raw(env, "0 division", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_int*)&vars[opcode->operand0] = *(SPVM_VALUE_int*)&vars[opcode->operand1] % *(SPVM_VALUE_int*)&vars[opcode->operand2];
        }
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_LONG:
        if (__builtin_expect(*(SPVM_VALUE_short*)&vars[opcode->operand2] == 0, 0)) {
          void* exception = env->new_string_raw(env, "0 division", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_long*)&vars[opcode->operand0] = *(SPVM_VALUE_long*)&vars[opcode->operand1] % *(SPVM_VALUE_long*)&vars[opcode->operand2];
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
        *(SPVM_VALUE_int*)&vars[opcode->operand0]
          = *(SPVM_VALUE_int*)&vars[opcode->operand1] << (*(SPVM_VALUE_int*)&vars[opcode->operand2] & 0x1f);
        break;
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0]
          = *(SPVM_VALUE_long*)&vars[opcode->operand1] << (*(SPVM_VALUE_int*)&vars[opcode->operand2] & 0x3f);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_INT:
        *(SPVM_VALUE_int*)&vars[opcode->operand0]
          = *(SPVM_VALUE_int*)&vars[opcode->operand1] >> (*(SPVM_VALUE_int*)&vars[opcode->operand2] & 0x1f);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0]
          = *(SPVM_VALUE_long*)&vars[opcode->operand1] >> (*(SPVM_VALUE_int*)&vars[opcode->operand2] & 0x3f);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_UNSIGNED_INT:
        *(SPVM_VALUE_int*)&vars[opcode->operand0]
          = (int32_t)((uint32_t)*(SPVM_VALUE_int*)&vars[opcode->operand1] >> (*(SPVM_VALUE_int*)&vars[opcode->operand2] & 0x1f));
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_UNSIGNED_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0]
          = (int64_t)((uint64_t)*(SPVM_VALUE_long*)&vars[opcode->operand1] >> (*(SPVM_VALUE_int*)&vars[opcode->operand2] & 0x3f));
        break;
      case SPVM_OPCODE_C_ID_BIT_AND_INT:
        *(SPVM_VALUE_int*)&vars[opcode->operand0]
          = *(SPVM_VALUE_int*)&vars[opcode->operand1] & *(SPVM_VALUE_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_BIT_AND_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0]
          = *(SPVM_VALUE_long*)&vars[opcode->operand1] & *(SPVM_VALUE_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_BIT_OR_INT:
        *(SPVM_VALUE_int*)&vars[opcode->operand0]
          = *(SPVM_VALUE_int*)&vars[opcode->operand1] | *(SPVM_VALUE_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_BIT_OR_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0]
          = *(SPVM_VALUE_long*)&vars[opcode->operand1] | *(SPVM_VALUE_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_BIT_XOR_INT:
        *(SPVM_VALUE_int*)&vars[opcode->operand0]
          = *(SPVM_VALUE_int*)&vars[opcode->operand1] ^ *(SPVM_VALUE_int*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_BIT_XOR_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0]
          = *(SPVM_VALUE_long*)&vars[opcode->operand1] ^ *(SPVM_VALUE_long*)&vars[opcode->operand2];
        break;
      case SPVM_OPCODE_C_ID_NEGATE_INT:
        *(SPVM_VALUE_int*)&vars[opcode->operand0] = -*(SPVM_VALUE_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NEGATE_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0] = -*(SPVM_VALUE_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NEGATE_FLOAT:
        *(float*)&vars[opcode->operand0] = -*(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_NEGATE_DOUBLE:
        *(double*)&vars[opcode->operand0] = -*(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_COMPLEMENT_INT:
        *(SPVM_VALUE_int*)&vars[opcode->operand0] = ~*(SPVM_VALUE_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_COMPLEMENT_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0] = ~*(SPVM_VALUE_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_INC_BYTE:
        *(SPVM_VALUE_byte*)&vars[opcode->operand0] += (int16_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_SHORT:
        *(SPVM_VALUE_short*)&vars[opcode->operand0] += (int16_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_INT:
        *(SPVM_VALUE_int*)&vars[opcode->operand0] += (int16_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0] += (int16_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_FLOAT:
        *(float*)&vars[opcode->operand0] += (int16_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_DOUBLE:
        *(double*)&vars[opcode->operand0] += (int16_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0] = (int64_t)*(SPVM_VALUE_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_FLOAT:
        *(float*)&vars[opcode->operand0] = (float)*(SPVM_VALUE_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_DOUBLE:
        *(double*)&vars[opcode->operand0] = (double)*(SPVM_VALUE_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_INT:
        *(SPVM_VALUE_int*)&vars[opcode->operand0] = (int32_t)*(SPVM_VALUE_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_FLOAT:
        *(float*)&vars[opcode->operand0] = (float)*(SPVM_VALUE_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_DOUBLE:
        *(double*)&vars[opcode->operand0] = (double)*(SPVM_VALUE_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_INT:
        *(SPVM_VALUE_int*)&vars[opcode->operand0] = (int32_t)*(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0] = (int64_t)*(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_DOUBLE:
        *(double*)&vars[opcode->operand0] = (double)*(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_INT:
        *(SPVM_VALUE_int*)&vars[opcode->operand0] = (int32_t)*(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0] = (int64_t)*(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_FLOAT:
        *(float*)&vars[opcode->operand0] = (float)*(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_BYTE:
        *(SPVM_VALUE_byte*)&vars[opcode->operand0] = (int8_t)(*(SPVM_VALUE_int*)&vars[opcode->operand1]);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_SHORT:
        *(SPVM_VALUE_short*)&vars[opcode->operand0] = (int16_t)(*(SPVM_VALUE_int*)&vars[opcode->operand1]);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_INT:
        *(SPVM_VALUE_int*)&vars[opcode->operand0] = (int32_t)*(SPVM_VALUE_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_INT:
        *(SPVM_VALUE_int*)&vars[opcode->operand0] = (int32_t)*(SPVM_VALUE_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0] = (int64_t)*(SPVM_VALUE_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_FLOAT:
        *(float*)&vars[opcode->operand0] = (float)*(SPVM_VALUE_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_DOUBLE:
        *(double*)&vars[opcode->operand0] = (double)*(SPVM_VALUE_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_BYTE:
        *(SPVM_VALUE_byte*)&vars[opcode->operand0] = (int8_t)*(SPVM_VALUE_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0] = (int64_t)*(SPVM_VALUE_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_FLOAT:
        *(float*)&vars[opcode->operand0] = (float)*(SPVM_VALUE_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_DOUBLE:
        *(double*)&vars[opcode->operand0] = (double)*(SPVM_VALUE_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_BYTE:
        *(SPVM_VALUE_byte*)&vars[opcode->operand0] = (int8_t)*(SPVM_VALUE_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_SHORT:
        *(SPVM_VALUE_short*)&vars[opcode->operand0] = (int16_t)*(SPVM_VALUE_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_BYTE:
        *(SPVM_VALUE_byte*)&vars[opcode->operand0] = (int8_t)*(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_SHORT:
        *(SPVM_VALUE_short*)&vars[opcode->operand0] = (int16_t)*(float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_BYTE:
        *(SPVM_VALUE_byte*)&vars[opcode->operand0] = (int8_t)*(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_SHORT:
        *(SPVM_VALUE_short*)&vars[opcode->operand0] = (int16_t)*(double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_SHORT:
        *(SPVM_VALUE_short*)&vars[opcode->operand0] = (int16_t)*(SPVM_VALUE_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_BYTE:
        *(SPVM_VALUE_byte*)&vars[opcode->operand0] = *(SPVM_VALUE_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_SHORT:
        *(SPVM_VALUE_short*)&vars[opcode->operand0] = *(SPVM_VALUE_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_INT:
        *(SPVM_VALUE_int*)&vars[opcode->operand0] = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0] = *(SPVM_VALUE_long*)&vars[opcode->operand1];
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
            sprintf(string_convert_buffer, "%" PRId8, *(SPVM_VALUE_byte*)&vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_STRING:
            sprintf(string_convert_buffer, "%" PRId16, *(SPVM_VALUE_short*)&vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_INT_TO_STRING:
            sprintf(string_convert_buffer, "%" PRId32, *(SPVM_VALUE_int*)&vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_STRING:
            sprintf(string_convert_buffer, "%" PRId64, *(SPVM_VALUE_long*)&vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_STRING:
            sprintf(string_convert_buffer, "%g", *(SPVM_VALUE_float*)&vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_STRING:
            sprintf(string_convert_buffer, "%g", *(SPVM_VALUE_double*)&vars[opcode->operand1]);
            break;
        }
        
        int32_t string_length = strlen(string_convert_buffer);
        void* string = env->new_string_raw(env, string_convert_buffer, string_length);
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], string);

        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_UNDEF:
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], NULL);
        break;
      case SPVM_OPCODE_C_ID_GET_CONSTANT_BYTE:
        *(SPVM_VALUE_byte*)&vars[opcode->operand0] = *(SPVM_VALUE_byte*)&opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_GET_CONSTANT_SHORT:
        *(SPVM_VALUE_short*)&vars[opcode->operand0] = *(SPVM_VALUE_short*)&opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_GET_CONSTANT_INT:
        *(SPVM_VALUE_int*)&vars[opcode->operand0] = *(SPVM_VALUE_int*)&opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_GET_CONSTANT_LONG: {
        int32_t rel_id = opcode->operand1;
        SPVM_CONSTANT* constant = SPVM_LIST_fetch(sub->info_constants, rel_id);
        *(SPVM_VALUE_long*)&vars[opcode->operand0] = *(SPVM_VALUE_long*)&constant->value;
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_FLOAT:
        *(float*)&vars[opcode->operand0] = *(float*)&opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_GET_CONSTANT_DOUBLE: {
        int32_t rel_id = opcode->operand1;
        SPVM_CONSTANT* constant = SPVM_LIST_fetch(sub->info_constants, rel_id);
        *(SPVM_VALUE_double*)&vars[opcode->operand0] = *(SPVM_VALUE_double*)&constant->value;
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_BYTE: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
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
            *(SPVM_VALUE_byte*)&vars[opcode->operand0] = (*(SPVM_VALUE_byte**)&(*(void**)array))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_SHORT: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
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
            *(SPVM_VALUE_short*)&vars[opcode->operand0] = (*(SPVM_VALUE_short**)&(*(void**)array))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_INT: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
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
            *(SPVM_VALUE_int*)&vars[opcode->operand0] = (*(SPVM_VALUE_int**)&(*(void**)array))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_LONG: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
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
            *(SPVM_VALUE_long*)&vars[opcode->operand0] = (*(SPVM_VALUE_long**)&(*(void**)array))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_FLOAT: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
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
            *(float*)&vars[opcode->operand0] = (*(SPVM_VALUE_float**)&(*(void**)array))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_DOUBLE: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
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
            *(double*)&vars[opcode->operand0] = (*(SPVM_VALUE_double**)&(*(void**)array))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_OBJECT: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
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
            void* object = (*(SPVM_VALUE_object**)&(*(void**)array))[index];
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_BYTE: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
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
            (*(SPVM_VALUE_byte**)&(*(void**)array))[index] = *(SPVM_VALUE_byte*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_SHORT: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
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
           (*(SPVM_VALUE_short**)&(*(void**)array))[index] = *(SPVM_VALUE_short*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_INT: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
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
            (*(SPVM_VALUE_int**)&(*(void**)array))[index] = *(SPVM_VALUE_int*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_LONG: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
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
            (*(SPVM_VALUE_long**)&(*(void**)array))[index] = *(SPVM_VALUE_long*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_FLOAT: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
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
            (*(SPVM_VALUE_float**)&(*(void**)array))[index] = *(float*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_DOUBLE: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
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
            (*(SPVM_VALUE_double**)&(*(void**)array))[index] = *(double*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_OBJECT: {
        
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
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
            void* object_address = &((*(SPVM_VALUE_object**)&(*(void**)array))[index]);
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(object_address, *(void**)&vars[opcode->operand2]);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_UNDEF: {
        
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
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
            void* object_address = &((*(SPVM_VALUE_object**)&(*(void**)array))[index]);
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(object_address, NULL);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FETCH_BYTE: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        int32_t unit = opcode->operand3;
        
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
            int32_t offset;
            for (offset = 0; offset < unit; offset++) {
              *(SPVM_VALUE_byte*)&vars[opcode->operand0 + offset] = (*(SPVM_VALUE_byte**)&(*(void**)array))[unit * index + offset];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FETCH_SHORT: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        int32_t unit = opcode->operand3;
        
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
            int32_t offset;
            for (offset = 0; offset < unit; offset++) {
              *(SPVM_VALUE_short*)&vars[opcode->operand0 + offset] = (*(SPVM_VALUE_short**)&(*(void**)array))[unit * index + offset];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FETCH_INT: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        
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
            int32_t offset;
            for (offset = 0; offset < unit; offset++) {
              *(SPVM_VALUE_int*)&vars[opcode->operand0 + offset] = (*(SPVM_VALUE_int**)&(*(void**)array))[unit * index + offset];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FETCH_LONG: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        
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
            int32_t offset;
            for (offset = 0; offset < unit; offset++) {
              *(SPVM_VALUE_long*)&vars[opcode->operand0 + offset] = (*(SPVM_VALUE_long**)&(*(void**)array))[unit * index + offset];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FETCH_FLOAT: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        
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
            int32_t offset;
            for (offset = 0; offset < unit; offset++) {
              *(SPVM_VALUE_float*)&vars[opcode->operand0 + offset] = (*(SPVM_VALUE_float**)&(*(void**)array))[unit * index + offset];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FETCH_DOUBLE: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        
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
            int32_t offset;
            for (offset = 0; offset < unit; offset++) {
              *(SPVM_VALUE_double*)&vars[opcode->operand0 + offset] = (*(SPVM_VALUE_double**)&(*(void**)array))[unit * index + offset];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_FETCH_BYTE: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        
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
            *(SPVM_VALUE_byte*)&vars[opcode->operand0] = (*(SPVM_VALUE_byte**)&(*(void**)array))[unit * index + offset];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_FETCH_SHORT: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        
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
            *(SPVM_VALUE_short*)&vars[opcode->operand0] = (*(SPVM_VALUE_short**)&(*(void**)array))[unit * index + offset];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_FETCH_INT: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        
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
            *(SPVM_VALUE_int*)&vars[opcode->operand0] = (*(SPVM_VALUE_int**)&(*(void**)array))[unit * index + offset];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_FETCH_LONG: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        
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
            *(SPVM_VALUE_long*)&vars[opcode->operand0] = (*(SPVM_VALUE_long**)&(*(void**)array))[unit * index + offset];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_FETCH_FLOAT: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        
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
            *(SPVM_VALUE_float*)&vars[opcode->operand0] = (*(SPVM_VALUE_float**)&(*(void**)array))[unit * index + offset];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_FETCH_DOUBLE: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        
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
            *(SPVM_VALUE_double*)&vars[opcode->operand0] = (*(SPVM_VALUE_double**)&(*(void**)array))[unit * index + offset];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_STORE_BYTE: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        int32_t unit = opcode->operand3;
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
            int32_t offset;
            for (offset = 0; offset < unit; offset++) {
              (*(SPVM_VALUE_byte**)&(*(void**)array))[unit * index + offset] = *(SPVM_VALUE_byte*)&vars[opcode->operand2 + offset];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_STORE_SHORT: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        int32_t unit = opcode->operand3;
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
            int32_t offset;
            for (offset = 0; offset < unit; offset++) {
              (*(SPVM_VALUE_short**)&(*(void**)array))[unit * index + offset] = *(SPVM_VALUE_short*)&vars[opcode->operand2 + offset];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_STORE_INT: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        int32_t unit = opcode->operand3;
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
            int32_t offset;
            for (offset = 0; offset < unit; offset++) {
              (*(SPVM_VALUE_int**)&(*(void**)array))[unit * index + offset] = *(SPVM_VALUE_int*)&vars[opcode->operand2 + offset];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_STORE_LONG: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        int32_t unit = opcode->operand3;
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
            int32_t offset;
            for (offset = 0; offset < unit; offset++) {
              (*(SPVM_VALUE_long**)&(*(void**)array))[unit * index + offset] = *(SPVM_VALUE_long*)&vars[opcode->operand2 + offset];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_STORE_FLOAT: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        int32_t unit = opcode->operand3;
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
            int32_t offset;
            for (offset = 0; offset < unit; offset++) {
              (*(SPVM_VALUE_float**)&(*(void**)array))[unit * index + offset] = *(SPVM_VALUE_float*)&vars[opcode->operand2 + offset];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_STORE_DOUBLE: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        int32_t unit = opcode->operand3;
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
            int32_t offset;
            for (offset = 0; offset < unit; offset++) {
              (*(SPVM_VALUE_double**)&(*(void**)array))[unit * index + offset] = *(SPVM_VALUE_double*)&vars[opcode->operand2 + offset];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_STORE_BYTE: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
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
            (*(SPVM_VALUE_byte**)&(*(void**)array))[unit * index + offset] = *(SPVM_VALUE_byte*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_STORE_SHORT: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
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
            (*(SPVM_VALUE_short**)&(*(void**)array))[unit * index + offset] = *(SPVM_VALUE_short*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_STORE_INT: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
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
            (*(SPVM_VALUE_int**)&(*(void**)array))[unit * index + offset] = *(SPVM_VALUE_int*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_STORE_LONG: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
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
            (*(SPVM_VALUE_long**)&(*(void**)array))[unit * index + offset] = *(SPVM_VALUE_long*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_STORE_FLOAT: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
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
            (*(SPVM_VALUE_float**)&(*(void**)array))[unit * index + offset] = *(SPVM_VALUE_float*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_STORE_DOUBLE: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
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
            (*(SPVM_VALUE_double**)&(*(void**)array))[unit * index + offset] = *(SPVM_VALUE_double*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_DEREF_BYTE: {
        SPVM_VALUE* value_ref = *(SPVM_VALUE**)&vars[opcode->operand1];
        int32_t unit = opcode->operand3;
        
        for (int32_t offset = 0; offset < unit; offset++) {
          *(SPVM_VALUE_byte*)&vars[opcode->operand0 + offset] = *(SPVM_VALUE_byte*)&value_ref[offset];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_DEREF_SHORT: {
        SPVM_VALUE* value_ref = *(SPVM_VALUE**)&vars[opcode->operand1];
        int32_t unit = opcode->operand3;
        
        for (int32_t offset = 0; offset < unit; offset++) {
          *(SPVM_VALUE_short*)&vars[opcode->operand0 + offset] = *(SPVM_VALUE_short*)&value_ref[offset];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_DEREF_INT: {
        SPVM_VALUE* value_ref = *(SPVM_VALUE**)&vars[opcode->operand1];
        int32_t unit = opcode->operand3;
        
        for (int32_t offset = 0; offset < unit; offset++) {
          *(SPVM_VALUE_int*)&vars[opcode->operand0 + offset] = *(SPVM_VALUE_int*)&value_ref[offset];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_DEREF_LONG: {
        SPVM_VALUE* value_ref = *(SPVM_VALUE**)&vars[opcode->operand1];
        int32_t unit = opcode->operand3;
        
        for (int32_t offset = 0; offset < unit; offset++) {
          *(SPVM_VALUE_long*)&vars[opcode->operand0 + offset] = *(SPVM_VALUE_long*)&value_ref[offset];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_DEREF_FLOAT: {
        SPVM_VALUE* value_ref = *(SPVM_VALUE**)&vars[opcode->operand1];
        int32_t unit = opcode->operand3;
        
        for (int32_t offset = 0; offset < unit; offset++) {
          *(SPVM_VALUE_float*)&vars[opcode->operand0 + offset] = *(SPVM_VALUE_float*)&value_ref[offset];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_DEREF_DOUBLE: {
        SPVM_VALUE* value_ref = *(SPVM_VALUE**)&vars[opcode->operand1];
        int32_t unit = opcode->operand3;
        
        for (int32_t offset = 0; offset < unit; offset++) {
          *(SPVM_VALUE_double*)&vars[opcode->operand0 + offset] = *(SPVM_VALUE_double*)&value_ref[offset];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_DEREF_GET_FIELD_BYTE: {
        SPVM_VALUE* value_ref = *(SPVM_VALUE**)&vars[opcode->operand1];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        
        *(SPVM_VALUE_byte*)&vars[opcode->operand0] = *(SPVM_VALUE_byte*)&value_ref[offset];

        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_DEREF_GET_FIELD_SHORT: {
        SPVM_VALUE* value_ref = *(SPVM_VALUE**)&vars[opcode->operand1];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        
        *(SPVM_VALUE_short*)&vars[opcode->operand0] = *(SPVM_VALUE_short*)&value_ref[offset];

        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_DEREF_GET_FIELD_INT: {
        SPVM_VALUE* value_ref = *(SPVM_VALUE**)&vars[opcode->operand1];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        
        *(SPVM_VALUE_int*)&vars[opcode->operand0] = *(SPVM_VALUE_int*)&value_ref[offset];

        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_DEREF_GET_FIELD_LONG: {
        SPVM_VALUE* value_ref = *(SPVM_VALUE**)&vars[opcode->operand1];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        
        *(SPVM_VALUE_long*)&vars[opcode->operand0] = *(SPVM_VALUE_long*)&value_ref[offset];

        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_DEREF_GET_FIELD_FLOAT: {
        SPVM_VALUE* value_ref = *(SPVM_VALUE**)&vars[opcode->operand1];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        
        *(SPVM_VALUE_float*)&vars[opcode->operand0] = *(SPVM_VALUE_float*)&value_ref[offset];

        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_DEREF_GET_FIELD_DOUBLE: {
        SPVM_VALUE* value_ref = *(SPVM_VALUE**)&vars[opcode->operand1];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        
        *(SPVM_VALUE_double*)&vars[opcode->operand0] = *(SPVM_VALUE_double*)&value_ref[offset];

        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_DEREF_SET_FIELD_BYTE: {
        SPVM_VALUE* value_ref = *(SPVM_VALUE**)&vars[opcode->operand0];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        *(SPVM_VALUE_byte*)&value_ref[offset] = *(SPVM_VALUE_byte*)&vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_DEREF_SET_FIELD_SHORT: {
        SPVM_VALUE* value_ref = *(SPVM_VALUE**)&vars[opcode->operand0];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        *(SPVM_VALUE_short*)&value_ref[offset] = *(SPVM_VALUE_short*)&vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_DEREF_SET_FIELD_INT: {
        SPVM_VALUE* value_ref = *(SPVM_VALUE**)&vars[opcode->operand0];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        *(SPVM_VALUE_int*)&value_ref[offset] = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_DEREF_SET_FIELD_LONG: {
        SPVM_VALUE* value_ref = *(SPVM_VALUE**)&vars[opcode->operand0];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        *(SPVM_VALUE_long*)&value_ref[offset] = *(SPVM_VALUE_long*)&vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_DEREF_SET_FIELD_FLOAT: {
        SPVM_VALUE* value_ref = *(SPVM_VALUE**)&vars[opcode->operand0];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        *(SPVM_VALUE_float*)&value_ref[offset] = *(SPVM_VALUE_float*)&vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_DEREF_SET_FIELD_DOUBLE: {
        SPVM_VALUE* value_ref = *(SPVM_VALUE**)&vars[opcode->operand0];
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        *(SPVM_VALUE_double*)&value_ref[offset] = *(SPVM_VALUE_double*)&vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_BYTE:
        *(SPVM_VALUE_byte*)&vars[opcode->operand0] = *(SPVM_VALUE_byte*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_MOVE_SHORT:
        *(SPVM_VALUE_short*)&vars[opcode->operand0] = *(SPVM_VALUE_short*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_MOVE_INT:
        *(SPVM_VALUE_int*)&vars[opcode->operand0] = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_MOVE_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0] = *(SPVM_VALUE_long*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_MOVE_FLOAT:
        *(SPVM_VALUE_float*)&vars[opcode->operand0] = *(SPVM_VALUE_float*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_MOVE_DOUBLE:
        *(SPVM_VALUE_double*)&vars[opcode->operand0] = *(SPVM_VALUE_double*)&vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_MOVE_OBJECT:
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], *(void**)&vars[opcode->operand1]);
        break;
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
          
          if (*(void**)&vars[var_index] != NULL) {
            if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(*(void**)&vars[var_index]) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*(void**)&vars[var_index]); }
            else { env->dec_ref_count(env, *(void**)&vars[var_index]); }
          }
          
          *(void**)&vars[var_index] = NULL;
        }
        
        mortal_stack_top = original_mortal_stack_top;
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT: {
        int32_t rel_id = opcode->operand1;
        SPVM_TYPE* type = SPVM_LIST_fetch(sub->info_types, rel_id);
        int32_t basic_type_id = type->basic_type->id;
        
        void* object = env->new_object_raw(env, basic_type_id);
        
        // Push object
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_BYTE_ARRAY: {
        
        // length
        int32_t length = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        
        void* object = env->new_byte_array_raw(env, length);
        
        // Set array
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY: {
        
        // length
        int32_t length = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        
        void* object = env->new_short_array_raw(env, length);
        
        // Set array
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_INT_ARRAY: {
        
        // length
        int32_t length = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        
        void* object = env->new_int_array_raw(env, length);
        
        // Set array
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_LONG_ARRAY: {
        
        // length
        int32_t length = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        
        void* object = env->new_long_array_raw(env, length);
        
        // Set array
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY: {
        
        // length
        int32_t length = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        
        void* object = env->new_float_array_raw(env, length);
        
        // Set array
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY: {
        
        // length
        int32_t length = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        
        void* object = env->new_double_array_raw(env, length);
        
        // Set array
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY: {
        int32_t rel_id = opcode->operand1;
        SPVM_TYPE* type = SPVM_LIST_fetch(sub->info_types, rel_id);
        int32_t basic_type_id = type->basic_type->id;
        
        // length
        int32_t length = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        
        void* object = env->new_object_array_raw(env, basic_type_id, length);
        
        // Set object
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULTI_ARRAY: {
        int32_t rel_id = opcode->operand1;
        SPVM_TYPE* type = SPVM_LIST_fetch(sub->info_types, rel_id);
        int32_t basic_type_id = type->basic_type->id;
        int32_t element_dimension = type->dimension - 1;
        
        // length
        int32_t length = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        
        void* object = env->new_multi_array_raw(env, basic_type_id, element_dimension, length);
        
        // Set object
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_VALUE_T_ARRAY: {
        int32_t rel_id = opcode->operand1;
        SPVM_TYPE* type = SPVM_LIST_fetch(sub->info_types, rel_id);
        int32_t basic_type_id = type->basic_type->id;
        
        // length
        int32_t length = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        
        void* object = env->new_value_t_array_raw(env, basic_type_id, length);
        
        // Set object
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING: {
        int32_t rel_id = opcode->operand1;
        SPVM_CONSTANT* constant = SPVM_LIST_fetch(sub->info_constants, rel_id);
        
        void* string = env->new_string_raw(env, constant->value.oval, constant->string_length);
        
        // Set string
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0] , string);

        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LENGTH:
        if (*(void**)&vars[opcode->operand1] == NULL) {
          void* exception = env->new_string_raw(env, "Can't get array length of undef value.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_int*)&vars[opcode->operand0] = *(SPVM_VALUE_int*)((intptr_t)*(void**)&vars[opcode->operand1] + (intptr_t)env->object_elements_length_byte_offset);
        }
        break;
      case SPVM_OPCODE_C_ID_WEAKEN_FIELD_OBJECT: {
        void* object = *(void**)&vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        SPVM_FIELD_ACCESS* field_access = SPVM_LIST_fetch(sub->info_field_accesses, rel_id);
        int32_t field_index = field_access->field->index;
        
        exception_flag = env->weaken_object_field(env, object, field_index);

        break;
      }
      case SPVM_OPCODE_C_ID_CONCAT: {
        void* concat_string = env->concat(env, *(void**)&vars[opcode->operand1], *(void**)&vars[opcode->operand2]);
        if (concat_string == NULL) {
          exception_flag = 1;
        }
        else {
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], concat_string);
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
        *(SPVM_VALUE_byte*)&stack[call_sub_arg_stack_top] = *(SPVM_VALUE_byte*)&vars[opcode->operand0];
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_SHORT: {
        *(SPVM_VALUE_short*)&stack[call_sub_arg_stack_top] = *(SPVM_VALUE_short*)&vars[opcode->operand0];
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_INT: {
        *(SPVM_VALUE_int*)&stack[call_sub_arg_stack_top] = *(SPVM_VALUE_int*)&vars[opcode->operand0];
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_LONG: {
        *(SPVM_VALUE_long*)&stack[call_sub_arg_stack_top] = *(SPVM_VALUE_long*)&vars[opcode->operand0];
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_FLOAT: {
        *(SPVM_VALUE_float*)&stack[call_sub_arg_stack_top] = *(SPVM_VALUE_float*)&vars[opcode->operand0];
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_DOUBLE: {
        *(SPVM_VALUE_double*)&stack[call_sub_arg_stack_top] = *(SPVM_VALUE_double*)&vars[opcode->operand0];
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_OBJECT: {
        *(SPVM_VALUE_object*)&stack[call_sub_arg_stack_top] = *(SPVM_VALUE_object*)&vars[opcode->operand0];
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_UNDEF:
        *(void**)&stack[call_sub_arg_stack_top] = NULL;
        call_sub_arg_stack_top++;
        
        break;
      case SPVM_OPCODE_C_ID_CAST: {
        void* object = *(void**)&vars[opcode->operand1];

        int32_t rel_id = opcode->operand2;
        SPVM_TYPE* type = SPVM_LIST_fetch(sub->info_types, rel_id);
        int32_t cast_basic_type_id = type->basic_type->id;
        int32_t cast_type_dimension = type->dimension;
        
        _Bool can_cast = env->check_cast(env, cast_basic_type_id, cast_type_dimension, object);
        if (can_cast) {
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_string_raw(env, "Can't cast uncompatible type.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB:
      case SPVM_OPCODE_C_ID_CALL_INTERFACE_METHOD:
      {
        int32_t rel_id = opcode->operand1;
        SPVM_CALL_SUB* call_sub = SPVM_LIST_fetch(sub->info_call_subs, rel_id);
        int32_t decl_sub_id = call_sub->sub->id;

        // Declare subroutine
        SPVM_SUB* decl_sub = SPVM_LIST_fetch(compiler->subs, decl_sub_id);
        
        // Declare subroutine return type
        SPVM_TYPE* decl_sub_return_type = decl_sub->op_return_type->uv.type;
        int32_t decl_sub_return_type_is_object = SPVM_TYPE_is_object_type(compiler, decl_sub_return_type->basic_type->id, decl_sub_return_type->dimension, decl_sub_return_type->flag);
        int32_t decl_sub_return_type_is_value_t = SPVM_TYPE_is_value_type(compiler, decl_sub_return_type->basic_type->id, decl_sub_return_type->dimension, decl_sub_return_type->flag);
        
        // Declare subroutine argument length
        int32_t decl_sub_args_length = decl_sub->op_args->length;
        
        // Call subroutine id
        int32_t call_sub_id;
        if (opcode->id == SPVM_OPCODE_C_ID_CALL_SUB) {
           call_sub_id = decl_sub_id;
        }
        else if (opcode->id == SPVM_OPCODE_C_ID_CALL_INTERFACE_METHOD) {
          void* object = *(void**)&vars[opcode->operand2];
          call_sub_id = env->get_sub_id_method_call(env, object, decl_sub->signature);
        }
        else {
          assert(0);
        }
        
        call_sub_arg_stack_top -= SPVM_SUB_get_arg_alloc_length(compiler, decl_sub);
        
        // Call subroutine
        exception_flag = env->call_sub(env, call_sub_id, stack);
        if (!exception_flag) {
          if (decl_sub_return_type_is_value_t) {
            int32_t decl_sub_return_type_width = SPVM_TYPE_get_width(compiler, decl_sub_return_type->basic_type->id, decl_sub_return_type->dimension, decl_sub_return_type->flag);
            int32_t decl_sub_return_basic_type_id = decl_sub_return_type->basic_type->id;
            memcpy(&vars[opcode->operand0], &stack[0], sizeof(SPVM_VALUE) * decl_sub_return_type_width);
          }
          else if (decl_sub_return_type_is_object) {
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], stack[0].oval);
          }
          else {
            int32_t decl_sub_return_basic_type_id = decl_sub_return_type->basic_type->id;
            if (decl_sub_return_basic_type_id != SPVM_BASIC_TYPE_C_ID_VOID) {
              vars[opcode->operand0] = stack[0];
            }
          }
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_IF_CROAK_CATCH: {
        if (exception_flag) {
          exception_flag = 0;
          
          SPVM_SUB* sub = SPVM_LIST_fetch(package->subs, opcode->operand1);
          int32_t sub_id = sub->id;
          int32_t rel_line = opcode->operand2;
          int32_t line = sub->op_sub->line + rel_line;
          
          const char* sub_name = sub->op_name->uv.name;
          const char* package_name = sub->package->op_name->uv.name;
          const char* file = sub->op_sub->file;
          
          // Exception stack trace
          env->set_exception(env, env->create_exception_stack_trace(env, env->get_exception(env), package_name, sub_name, file, line));
          opcode_rel_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_IF_CROAK_RETURN: {
        if (exception_flag) {
          SPVM_SUB* sub = SPVM_LIST_fetch(package->subs, opcode->operand1);
          int32_t sub_id = sub->id;
          int32_t rel_line = opcode->operand2;
          int32_t line = sub->op_sub->line + rel_line;
          
          const char* sub_name = sub->op_name->uv.name;
          const char* package_name = sub->package->op_name->uv.name;
          const char* file = sub->op_sub->file;

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
      case SPVM_OPCODE_C_ID_RETURN:
      {
        memcpy(&stack[0], &vars[opcode->operand0], sizeof(SPVM_VALUE) * sub_return_type_width);
        
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_OBJECT:
      {
        *(void**)&stack[0] = *(void**)&vars[opcode->operand0];
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
      case SPVM_OPCODE_C_ID_LOOKUP_SWITCH: {

        int32_t rel_id = opcode->operand2;
        SPVM_SWITCH_INFO* switch_info = SPVM_LIST_fetch(sub->info_switch_infos, rel_id);
        SPVM_LIST* op_cases = switch_info->op_cases_ordered;
        
        // default offset
        int32_t default_opcode_rel_index = switch_info->default_opcode_rel_index;
        
        // cases length
        int32_t cases_length = op_cases->length;
        
        if (cases_length > 0) {
          
          SPVM_OP* op_case_min = SPVM_LIST_fetch(op_cases, 0);
          SPVM_OP* op_case_max = SPVM_LIST_fetch(op_cases, op_cases->length - 1);
          
          // min
          int32_t min = op_case_min->uv.case_info->constant->value.ival;
          
          // max
          int32_t max = op_case_max->uv.case_info->constant->value.ival;
          
          if (*(SPVM_VALUE_int*)&vars[opcode->operand0] >= min && *(SPVM_VALUE_int*)&vars[opcode->operand0] <= max) {
            // 2 opcode_rel_index searching
            int32_t cur_min_pos = 0;
            int32_t cur_max_pos = cases_length - 1;
            
            while (1) {
              if (cur_max_pos < cur_min_pos) {
                opcode_rel_index = default_opcode_rel_index;
                break;
              }
              int32_t cur_half_pos = cur_min_pos + (cur_max_pos - cur_min_pos) / 2;
              SPVM_OP* op_case_half = SPVM_LIST_fetch(op_cases, cur_half_pos);
              int32_t cur_half = op_case_half->uv.case_info->constant->value.ival;
              
              if (*(SPVM_VALUE_int*)&vars[opcode->operand0] > cur_half) {
                cur_min_pos = cur_half_pos + 1;
              }
              else if (*(SPVM_VALUE_int*)&vars[opcode->operand0] < cur_half) {
                cur_max_pos = cur_half_pos - 1;
              }
              else {
                opcode_rel_index = op_case_half->uv.case_info->opcode_rel_index;
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
      case SPVM_OPCODE_C_ID_END_SUB: {
        goto label_END_SUB;
      }
      case SPVM_OPCODE_C_ID_REF:
        *(void**)&vars[opcode->operand0] = &vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GET_FIELD_BYTE: {
        int32_t rel_id = opcode->operand2;
        SPVM_FIELD_ACCESS* field_access = SPVM_LIST_fetch(sub->info_field_accesses, rel_id);
        int32_t field_index = field_access->field->index;

        void* object = *(void**)&vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          *(SPVM_VALUE_byte*)&vars[opcode->operand0] = *(SPVM_VALUE_byte*)&fields[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_SHORT: {
        int32_t rel_id = opcode->operand2;
        SPVM_FIELD_ACCESS* field_access = SPVM_LIST_fetch(sub->info_field_accesses, rel_id);
        int32_t field_index = field_access->field->index;

        void* object = *(void**)&vars[opcode->operand1];

        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          *(SPVM_VALUE_short*)&vars[opcode->operand0] = *(SPVM_VALUE_short*)&fields[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_INT: {
        int32_t rel_id = opcode->operand2;
        SPVM_FIELD_ACCESS* field_access = SPVM_LIST_fetch(sub->info_field_accesses, rel_id);
        int32_t field_index = field_access->field->index;

        void* object = *(void**)&vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          *(SPVM_VALUE_int*)&vars[opcode->operand0] = *(SPVM_VALUE_int*)&fields[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_LONG: {
        int32_t rel_id = opcode->operand2;
        SPVM_FIELD_ACCESS* field_access = SPVM_LIST_fetch(sub->info_field_accesses, rel_id);
        int32_t field_index = field_access->field->index;

        void* object = *(void**)&vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          *(SPVM_VALUE_long*)&vars[opcode->operand0] = *(SPVM_VALUE_long*)&fields[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_FLOAT: {
        int32_t rel_id = opcode->operand2;
        SPVM_FIELD_ACCESS* field_access = SPVM_LIST_fetch(sub->info_field_accesses, rel_id);
        int32_t field_index = field_access->field->index;

        void* object = *(void**)&vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          *(SPVM_VALUE_float*)&vars[opcode->operand0] = *(SPVM_VALUE_float*)&fields[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE: {
        int32_t rel_id = opcode->operand2;
        SPVM_FIELD_ACCESS* field_access = SPVM_LIST_fetch(sub->info_field_accesses, rel_id);
        int32_t field_index = field_access->field->index;

        void* object = *(void**)&vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          *(SPVM_VALUE_double*)&vars[opcode->operand0] = *(SPVM_VALUE_double*)&fields[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_OBJECT: {
        int32_t rel_id = opcode->operand2;
        SPVM_FIELD_ACCESS* field_access = SPVM_LIST_fetch(sub->info_field_accesses, rel_id);
        int32_t field_index = field_access->field->index;

        void* object = *(void**)&vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          void* object_field = *(SPVM_VALUE_object*)&fields[field_index];;
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object_field);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_BYTE: {
        void* object = *(void**)&vars[opcode->operand0];
        
        int32_t rel_id = opcode->operand1;
        SPVM_FIELD_ACCESS* field_access = SPVM_LIST_fetch(sub->info_field_accesses, rel_id);
        int32_t field_index = field_access->field->index;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          *(SPVM_VALUE_byte*)&fields[field_index] = *(SPVM_VALUE_byte*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_SHORT: {
        void* object = *(void**)&vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        SPVM_FIELD_ACCESS* field_access = SPVM_LIST_fetch(sub->info_field_accesses, rel_id);
        int32_t field_index = field_access->field->index;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          *(SPVM_VALUE_short*)&fields[field_index] = *(SPVM_VALUE_short*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_INT: {
        void* object = *(void**)&vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        SPVM_FIELD_ACCESS* field_access = SPVM_LIST_fetch(sub->info_field_accesses, rel_id);
        int32_t field_index = field_access->field->index;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          *(SPVM_VALUE_int*)&fields[field_index] = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_LONG: {
        void* object = *(void**)&vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        SPVM_FIELD_ACCESS* field_access = SPVM_LIST_fetch(sub->info_field_accesses, rel_id);
        int32_t field_index = field_access->field->index;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          *(SPVM_VALUE_long*)&fields[field_index] = *(SPVM_VALUE_long*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_FLOAT: {
        void* object = *(void**)&vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        SPVM_FIELD_ACCESS* field_access = SPVM_LIST_fetch(sub->info_field_accesses, rel_id);
        int32_t field_index = field_access->field->index;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          *(SPVM_VALUE_float*)&fields[field_index] = *(SPVM_VALUE_float*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE: {
        void* object = *(void**)&vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        SPVM_FIELD_ACCESS* field_access = SPVM_LIST_fetch(sub->info_field_accesses, rel_id);
        int32_t field_index = field_access->field->index;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          *(SPVM_VALUE_double*)&fields[field_index] = *(SPVM_VALUE_double*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_OBJECT: {
        void* object = *(void**)&vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        SPVM_FIELD_ACCESS* field_access = SPVM_LIST_fetch(sub->info_field_accesses, rel_id);
        int32_t field_index = field_access->field->index;

        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          void* object_field_address = (SPVM_VALUE_object*)&fields[field_index];
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(object_field_address, *(void**)&vars[opcode->operand2]);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_UNDEF: {
        void* object = *(void**)&vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        SPVM_FIELD_ACCESS* field_access = SPVM_LIST_fetch(sub->info_field_accesses, rel_id);
        int32_t field_index = field_access->field->index;

        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_raw(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);
          void* object_field_address = (SPVM_VALUE_object*)&fields[field_index];
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(object_field_address, NULL);
        }
        break;
      }
      default:
        assert(0);
      case SPVM_OPCODE_C_ID_WIDE: {
        // Operand 3 is operation code for wide operation
        switch (255 + opcode->operand3) {
          case SPVM_OPCODE_C_ID_GET_DEREF_BYTE: {
            *(SPVM_VALUE_byte*)&vars[opcode->operand0] = *(SPVM_VALUE_byte*)*(void**)&vars[opcode->operand1];
            break;
          }
          case SPVM_OPCODE_C_ID_GET_DEREF_SHORT: {
            *(SPVM_VALUE_short*)&vars[opcode->operand0] = *(SPVM_VALUE_short*)*(void**)&vars[opcode->operand1];
            break;
          }
          case SPVM_OPCODE_C_ID_GET_DEREF_INT: {
            *(SPVM_VALUE_int*)&vars[opcode->operand0] = *(SPVM_VALUE_int*)*(void**)&vars[opcode->operand1];
            break;
          }
          case SPVM_OPCODE_C_ID_GET_DEREF_LONG: {
            *(SPVM_VALUE_long*)&vars[opcode->operand0] = *(SPVM_VALUE_long*)*(void**)&vars[opcode->operand1];
            break;
          }
          case SPVM_OPCODE_C_ID_GET_DEREF_FLOAT: {
            *(SPVM_VALUE_float*)&vars[opcode->operand0] = *(SPVM_VALUE_float*)*(void**)&vars[opcode->operand1];
            break;
          }
          case SPVM_OPCODE_C_ID_GET_DEREF_DOUBLE: {
            *(SPVM_VALUE_double*)&vars[opcode->operand0] = *(SPVM_VALUE_double*)*(void**)&vars[opcode->operand1];
            break;
          }
          case SPVM_OPCODE_C_ID_SET_DEREF_BYTE: {
            *(SPVM_VALUE_byte*)*(void**)&vars[opcode->operand0] = *(SPVM_VALUE_byte*)&vars[opcode->operand1];
            break;
          }
          case SPVM_OPCODE_C_ID_SET_DEREF_SHORT: {
            *(SPVM_VALUE_short*)*(void**)&vars[opcode->operand0] = *(SPVM_VALUE_short*)&vars[opcode->operand1];
            break;
          }
          case SPVM_OPCODE_C_ID_SET_DEREF_INT: {
            *(SPVM_VALUE_int*)*(void**)&vars[opcode->operand0] = *(SPVM_VALUE_int*)&vars[opcode->operand1];
            break;
          }
          case SPVM_OPCODE_C_ID_SET_DEREF_LONG: {
            *(SPVM_VALUE_long*)*(void**)&vars[opcode->operand0] = *(SPVM_VALUE_long*)&vars[opcode->operand1];
            break;
          }
          case SPVM_OPCODE_C_ID_SET_DEREF_FLOAT: {
            *(SPVM_VALUE_float*)*(void**)&vars[opcode->operand0] = *(SPVM_VALUE_float*)&vars[opcode->operand1];
            break;
          }
          case SPVM_OPCODE_C_ID_SET_DEREF_DOUBLE: {
            *(SPVM_VALUE_double*)*(void**)&vars[opcode->operand0] = *(SPVM_VALUE_double*)&vars[opcode->operand1];
            break;
          }
          case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_BYTE: {
            int32_t rel_id = opcode->operand1;
            SPVM_PACKAGE_VAR_ACCESS* package_var_access = SPVM_LIST_fetch(sub->info_package_var_accesses, rel_id);
            int32_t package_var_id = package_var_access->package_var->id;
            
            *(SPVM_VALUE_byte*)&vars[opcode->operand0] = *(SPVM_VALUE_byte*)&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[package_var_id];
            
            break;
          }
          case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_SHORT: {
            int32_t rel_id = opcode->operand1;
            SPVM_PACKAGE_VAR_ACCESS* package_var_access = SPVM_LIST_fetch(sub->info_package_var_accesses, rel_id);
            int32_t package_var_id = package_var_access->package_var->id;
            
            *(SPVM_VALUE_short*)&vars[opcode->operand0] = *(SPVM_VALUE_short*)&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[package_var_id];
            
            break;
          }
          case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_INT: {
            int32_t rel_id = opcode->operand1;
            SPVM_PACKAGE_VAR_ACCESS* package_var_access = SPVM_LIST_fetch(sub->info_package_var_accesses, rel_id);
            int32_t package_var_id = package_var_access->package_var->id;
            
            *(SPVM_VALUE_int*)&vars[opcode->operand0] = *(SPVM_VALUE_int*)&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[package_var_id];
            
            break;
          }
          case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_LONG: {
            int32_t rel_id = opcode->operand1;
            SPVM_PACKAGE_VAR_ACCESS* package_var_access = SPVM_LIST_fetch(sub->info_package_var_accesses, rel_id);
            int32_t package_var_id = package_var_access->package_var->id;
            
            *(SPVM_VALUE_long*)&vars[opcode->operand0] = *(SPVM_VALUE_long*)&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[package_var_id];
            
            break;
          }
          case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_FLOAT: {
            int32_t rel_id = opcode->operand1;
            SPVM_PACKAGE_VAR_ACCESS* package_var_access = SPVM_LIST_fetch(sub->info_package_var_accesses, rel_id);
            int32_t package_var_id = package_var_access->package_var->id;
            
            *(float*)&vars[opcode->operand0] = *(float*)&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[package_var_id];
            
            break;
          }
          case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_DOUBLE: {
            int32_t rel_id = opcode->operand1;
            SPVM_PACKAGE_VAR_ACCESS* package_var_access = SPVM_LIST_fetch(sub->info_package_var_accesses, rel_id);
            int32_t package_var_id = package_var_access->package_var->id;
            
            *(double*)&vars[opcode->operand0] = *(double*)&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[package_var_id];
            
            break;
          }
          case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_OBJECT: {
            int32_t rel_id = opcode->operand1;
            SPVM_PACKAGE_VAR_ACCESS* package_var_access = SPVM_LIST_fetch(sub->info_package_var_accesses, rel_id);
            int32_t package_var_id = package_var_access->package_var->id;
            
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], *(void**)&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[package_var_id]);
            
            break;
          }
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_BYTE: {
            int32_t rel_id = opcode->operand0;
            SPVM_PACKAGE_VAR_ACCESS* package_var_access = SPVM_LIST_fetch(sub->info_package_var_accesses, rel_id);
            int32_t package_var_id = package_var_access->package_var->id;
            
            *(SPVM_VALUE_byte*)&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[package_var_id] = *(SPVM_VALUE_byte*)&vars[opcode->operand1];
            
            break;
          }
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_SHORT: {
            int32_t rel_id = opcode->operand0;
            SPVM_PACKAGE_VAR_ACCESS* package_var_access = SPVM_LIST_fetch(sub->info_package_var_accesses, rel_id);
            int32_t package_var_id = package_var_access->package_var->id;
            
            *(SPVM_VALUE_short*)&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[package_var_id] = *(SPVM_VALUE_short*)&vars[opcode->operand1];
            
            break;
          }
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_INT: {
            int32_t rel_id = opcode->operand0;
            SPVM_PACKAGE_VAR_ACCESS* package_var_access = SPVM_LIST_fetch(sub->info_package_var_accesses, rel_id);
            int32_t package_var_id = package_var_access->package_var->id;
            
            *(SPVM_VALUE_int*)&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[package_var_id] = *(SPVM_VALUE_int*)&vars[opcode->operand1];
            
            break;
          }
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_LONG: {
            int32_t rel_id = opcode->operand0;
            SPVM_PACKAGE_VAR_ACCESS* package_var_access = SPVM_LIST_fetch(sub->info_package_var_accesses, rel_id);
            int32_t package_var_id = package_var_access->package_var->id;
            
            *(SPVM_VALUE_long*)&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[package_var_id] = *(SPVM_VALUE_long*)&vars[opcode->operand1];
            
            break;
          }
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_FLOAT: {
            int32_t rel_id = opcode->operand0;
            SPVM_PACKAGE_VAR_ACCESS* package_var_access = SPVM_LIST_fetch(sub->info_package_var_accesses, rel_id);
            int32_t package_var_id = package_var_access->package_var->id;
            
            *(float*)&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[package_var_id] = *(float*)&vars[opcode->operand1];
            
            break;
          }
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_DOUBLE: {
            int32_t rel_id = opcode->operand0;
            SPVM_PACKAGE_VAR_ACCESS* package_var_access = SPVM_LIST_fetch(sub->info_package_var_accesses, rel_id);
            int32_t package_var_id = package_var_access->package_var->id;
            
            *(double*)&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[package_var_id] = *(double*)&vars[opcode->operand1];
            
            break;
          }
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_OBJECT: {
            int32_t rel_id = opcode->operand0;
            SPVM_PACKAGE_VAR_ACCESS* package_var_access = SPVM_LIST_fetch(sub->info_package_var_accesses, rel_id);
            int32_t package_var_id = package_var_access->package_var->id;
            
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[package_var_id], *(void**)&vars[opcode->operand1]);
            
            break;
          }
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_UNDEF: {
            int32_t rel_id = opcode->operand0;
            SPVM_PACKAGE_VAR_ACCESS* package_var_access = SPVM_LIST_fetch(sub->info_package_var_accesses, rel_id);
            int32_t package_var_id = package_var_access->package_var->id;
            
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[package_var_id], NULL);
            
            break;
          }
          case SPVM_OPCODE_C_ID_GET_EXCEPTION_VAR: {
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], env->get_exception(env));
            
            break;
          }
          case SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR: {
            
            env->set_exception(env, *(void**)&vars[opcode->operand0]);
            
            break;
          }
          case SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR_UNDEF: {
            
            env->set_exception(env, NULL);
            
            break;
          }
        }
      }
    }
    opcode_rel_index++;
  }

  label_END_SUB:
    
  // Croak
  if (!exception_flag) {
    
    int32_t sub_return_type_is_object = SPVM_TYPE_is_object_type(compiler, sub_return_type->basic_type->id, sub_return_type->dimension, sub_return_type->flag);
    _Bool sub_return_type_is_value_t = SPVM_TYPE_is_value_type(compiler, sub_return_type->basic_type->id, sub_return_type->dimension, sub_return_type->flag);
    
    // Decrement ref count of return value
    if (sub_return_type_is_object && !sub_return_type_is_value_t) {
      if (*(void**)&stack[0] != NULL) {
        SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*(void**)&stack[0]);
      }
    }
  }
  
  SPVM_RUNTIME_ALLOCATOR_free_memory_block(runtime, vars);
  SPVM_RUNTIME_ALLOCATOR_free_memory_block(runtime, mortal_stack);
  
  return exception_flag;
}

void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime) {
  
  // Free exception
  SPVM_RUNTIME_API_set_exception(runtime->env, NULL);
  
  free(runtime->package_vars);
  
  free(runtime);
}
