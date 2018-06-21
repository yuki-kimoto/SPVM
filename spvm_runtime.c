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
#include "spvm_symbol.h"
#include "spvm_package_var.h"
#include "spvm_package_var_access.h"
#include "spvm_field_access.h"


SPVM_RUNTIME* SPVM_RUNTIME_new(SPVM_COMPILER* compiler) {
  
  SPVM_RUNTIME* runtime = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME));
  
  SPVM_ENV* env = (SPVM_ENV*)SPVM_RUNTIME_API_get_env_runtime();
  
  runtime->env = env;

  runtime->compiler = compiler;
  
  // Set global runtime
  SPVM_RUNTIME_API_set_runtime(env, runtime);
  
  // Initialize Package Variables
  runtime->package_var_accesss = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_VALUE) * (compiler->op_package_vars->length + 1));

  // Arguments
  runtime->args = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_VALUE) * 255);
  
  return runtime;
}

int32_t SPVM_RUNTIME_call_sub(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(env);
  
  SPVM_COMPILER* compiler = runtime->compiler;

  // Constant pool sub
  SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, sub_id);
  SPVM_SUB* sub = op_sub->uv.sub;
  
  if (sub->have_native_desc) {
    return SPVM_RUNTIME_call_sub_native(env, sub_id, args);
  }
  else if (sub->is_compiled) {
    return SPVM_RUNTIME_call_sub_precompile(env, sub_id, args);
  }
  else {
    return SPVM_RUNTIME_call_sub_vm(env, sub_id, args);
  }
}

int32_t SPVM_RUNTIME_call_sub_precompile(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(env);
  SPVM_COMPILER* compiler = runtime->compiler;

  // Constant pool sub
  SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, sub_id);
  SPVM_SUB* sub = op_sub->uv.sub;

  // Subroutine is Precompile
  assert(sub->is_compiled);
  
  // Call precompile subroutine
  int32_t (*precompile_address)(SPVM_ENV*, SPVM_VALUE*) = sub->precompile_address;
  return (*precompile_address)(env, args);
}

int32_t SPVM_RUNTIME_call_sub_native(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(env);
  SPVM_COMPILER* compiler = runtime->compiler;

  // Constant pool sub
  SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, sub_id);
  SPVM_SUB* sub = op_sub->uv.sub;

  // Subroutine is native
  assert(sub->have_native_desc);

  // Set exception to NULL at start of subroutine
  env->set_exception(env, NULL);
  
  // Call native subrotuine
  int32_t (*native_address)(SPVM_ENV*, SPVM_VALUE*) = sub->native_address;
  return (*native_address)(env, args);
}

int32_t SPVM_RUNTIME_call_sub_vm(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args) {
  (void)env;
  
  // Runtime
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime(env);
  SPVM_COMPILER* compiler = runtime->compiler;

  // Constant pool sub
  SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, sub_id);
  SPVM_SUB* sub = op_sub->uv.sub;
  
  SPVM_OP* op_package = sub->op_package;
  SPVM_PACKAGE* package = op_package->uv.package;
  SPVM_HASH* symbol_name_symtable = package->symbol_name_symtable;

  // Subroutine return type
  SPVM_TYPE* sub_return_type = sub->op_return_type->uv.type;
  
  int32_t sub_return_type_is_object = SPVM_TYPE_is_object(compiler, sub_return_type);
  
  // Args length
  int32_t args_length = sub->op_args->length;
  
  // Bytecodes
  SPVM_OPCODE* opcodes = compiler->opcode_array->values;
  
  // Opcode base
  int32_t sub_opcode_base = sub->opcode_base;
  
  // Subroutine stack
  // This is used Variables, mortal stack
  int32_t call_frame_length = sub->op_mys->length + 1 + sub->mortal_stack_max;
  SPVM_VALUE* call_frame = SPVM_RUNTIME_ALLOCATOR_alloc(runtime, sizeof(SPVM_VALUE) * call_frame_length);
  
  // Variables
  SPVM_VALUE* vars = call_frame;

  // Auto decrement reference count variable index stack top
  int32_t mortal_stack_base = sub->op_mys->length + 1;
  SPVM_VALUE* mortal_stack = &call_frame[mortal_stack_base];
  int32_t mortal_stack_top = -1;

  // Call subroutine argument stack top
  int32_t call_sub_arg_stack_top = -1;
  
  // Condition flag
  register int32_t condition_flag = 0;

  // Croak flag
  int32_t exception_flag = 0;
  
  char tmp_string[30];

  register int32_t opcode_index = 0;

  // Initialize variables
  memset(vars, 0, sizeof(SPVM_VALUE) * sub->op_mys->length);
  
  // Copy arguments to variables
  memcpy(vars, args, args_length * sizeof(SPVM_VALUE));
  
  // If arg is object, increment reference count
  {
    int32_t index;
    for (index = 0; index < sub->object_arg_ids->length; index++) {
      int32_t object_arg_index = (intptr_t)SPVM_LIST_fetch(sub->object_arg_ids, index);
      
      void* object = *(void**)&vars[object_arg_index];
      if (object != NULL) {
        SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(object);
      }
    }
  }
  
  while (1) {
    SPVM_OPCODE* opcode = &(opcodes[sub_opcode_base + opcode_index]);
    
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
        int32_t basic_type_id = opcode->operand1;
        int32_t dimension = opcode->operand2;
        
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
        
        SPVM_VALUE_byte* bytes1 = (SPVM_VALUE_byte*)((intptr_t)object1 + (intptr_t)env->object_header_byte_size);
        SPVM_VALUE_byte* bytes2 = (SPVM_VALUE_byte*)((intptr_t)object2 + (intptr_t)env->object_header_byte_size);
        
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
          void* exception = env->new_string(env, "0 division", 0);
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
          void* exception = env->new_string(env, "0 division", 0);
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
          void* exception = env->new_string(env, "0 division", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_int*)&vars[opcode->operand0] = *(SPVM_VALUE_int*)&vars[opcode->operand1] % *(SPVM_VALUE_int*)&vars[opcode->operand2];
        }
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_LONG:
        if (__builtin_expect(*(SPVM_VALUE_short*)&vars[opcode->operand2] == 0, 0)) {
          void* exception = env->new_string(env, "0 division", 0);
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
        *(SPVM_VALUE_byte*)&vars[opcode->operand0] += (int32_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_SHORT:
        *(SPVM_VALUE_short*)&vars[opcode->operand0] += (int32_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_INT:
        *(SPVM_VALUE_int*)&vars[opcode->operand0] += (int32_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0] += (int32_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_FLOAT:
        *(float*)&vars[opcode->operand0] += (int32_t)(opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_DOUBLE:
        *(double*)&vars[opcode->operand0] += (int32_t)(opcode->operand1);
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
            sprintf(tmp_string, "%" PRId8, *(SPVM_VALUE_byte*)&vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_STRING:
            sprintf(tmp_string, "%" PRId16, *(SPVM_VALUE_short*)&vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_INT_TO_STRING:
            sprintf(tmp_string, "%" PRId32, *(SPVM_VALUE_int*)&vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_STRING:
            sprintf(tmp_string, "%" PRId64, *(SPVM_VALUE_long*)&vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_STRING:
            sprintf(tmp_string, "%g", *(SPVM_VALUE_float*)&vars[opcode->operand1]);
            break;
          case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_STRING:
            sprintf(tmp_string, "%g", *(SPVM_VALUE_double*)&vars[opcode->operand1]);
            break;
        }
        
        int32_t string_length = strlen(tmp_string);
        void* string = env->new_string(env, tmp_string, string_length);
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], string);

        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_ARRAY_TO_STRING_ARRAY:
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_ARRAY_TO_STRING_ARRAY:
      case SPVM_OPCODE_C_ID_CONVERT_INT_ARRAY_TO_STRING_ARRAY:
      case SPVM_OPCODE_C_ID_CONVERT_LONG_ARRAY_TO_STRING_ARRAY:
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_ARRAY_TO_STRING_ARRAY:
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_ARRAY_TO_STRING_ARRAY:
      {
        void* numeric_array = *(void**)&vars[opcode->operand1];

        if (*(void**)&vars[opcode->operand1] == NULL) {
          void* exception = env->new_string(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          int32_t length = *(SPVM_VALUE_int*)((intptr_t)*(void**)&vars[opcode->operand1] + (intptr_t)env->object_elements_length_byte_offset);
          
          void* string_array = env->new_multi_array(env, SPVM_BASIC_TYPE_C_ID_BYTE, 1, length);
          
          switch (opcode->id) {
            case SPVM_OPCODE_C_ID_CONVERT_BYTE_ARRAY_TO_STRING_ARRAY: {
              int32_t index;
              for (index = 0; index < length; index++) {
                SPVM_VALUE_byte value = *(SPVM_VALUE_byte*)((intptr_t)numeric_array + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE_byte) * index);
                sprintf(tmp_string, "%" PRId8, value);
                void* string = env->new_string(env, tmp_string, strlen(tmp_string));
                SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(string);
                *(void**)((intptr_t)string_array + (intptr_t)env->object_header_byte_size + sizeof(void*) * index) = string;
              }
              break;
            }
            case SPVM_OPCODE_C_ID_CONVERT_SHORT_ARRAY_TO_STRING_ARRAY: {
              int32_t index;
              for (index = 0; index < length; index++) {
                SPVM_VALUE_short value = *(SPVM_VALUE_short*)((intptr_t)numeric_array + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE_short) * index);
                sprintf(tmp_string, "%" PRId16, value);
                void* string = env->new_string(env, tmp_string, strlen(tmp_string));
                SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(string);
                *(void**)((intptr_t)string_array + (intptr_t)env->object_header_byte_size + sizeof(void*) * index) = string;
              }
              break;
            }
            case SPVM_OPCODE_C_ID_CONVERT_INT_ARRAY_TO_STRING_ARRAY: {
              int32_t index;
              for (index = 0; index < length; index++) {
                SPVM_VALUE_int value = *(SPVM_VALUE_int*)((intptr_t)numeric_array + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE_int) * index);
                sprintf(tmp_string, "%" PRId32, value);
                void* string = env->new_string(env, tmp_string, strlen(tmp_string));
                SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(string);
                *(void**)((intptr_t)string_array + (intptr_t)env->object_header_byte_size + sizeof(void*) * index) = string;
              }
              break;
            }
            case SPVM_OPCODE_C_ID_CONVERT_LONG_ARRAY_TO_STRING_ARRAY: {
              int32_t index;
              for (index = 0; index < length; index++) {
                SPVM_VALUE_long value = *(SPVM_VALUE_long*)((intptr_t)numeric_array + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE_long) * index);
                sprintf(tmp_string, "%" PRId64, value);
                void* string = env->new_string(env, tmp_string, strlen(tmp_string));
                SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(string);
                *(void**)((intptr_t)string_array + (intptr_t)env->object_header_byte_size + sizeof(void*) * index) = string;
              }
              break;
            }
            case SPVM_OPCODE_C_ID_CONVERT_FLOAT_ARRAY_TO_STRING_ARRAY: {
              int32_t index;
              for (index = 0; index < length; index++) {
                SPVM_VALUE_float value = *(SPVM_VALUE_float*)((intptr_t)numeric_array + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE_float) * index);
                sprintf(tmp_string, "%g", value);
                void* string = env->new_string(env, tmp_string, strlen(tmp_string));
                SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(string);
                *(void**)((intptr_t)string_array + (intptr_t)env->object_header_byte_size + sizeof(void*) * index) = string;
              }
              break;
            }
            case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_ARRAY_TO_STRING_ARRAY: {
              int32_t index;
              for (index = 0; index < length; index++) {
                SPVM_VALUE_double value = *(SPVM_VALUE_double*)((intptr_t)numeric_array + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE_double) * index);
                sprintf(tmp_string, "%g", value);
                void* string = env->new_string(env, tmp_string, strlen(tmp_string));
                SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(string);
                *(void**)((intptr_t)string_array + (intptr_t)env->object_header_byte_size + sizeof(void*) * index) = string;
              }
              break;
            }
          }
          
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], string_array);
        }

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
      case SPVM_OPCODE_C_ID_GET_CONSTANT_LONG:
        *(SPVM_VALUE_long*)&vars[opcode->operand0] = *(SPVM_VALUE_long*)&opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_GET_CONSTANT_FLOAT:
        *(float*)&vars[opcode->operand0] = *(float*)&opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_GET_CONSTANT_DOUBLE:
        *(double*)&vars[opcode->operand0] = *(double*)&opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_BYTE: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_string(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            *(SPVM_VALUE_byte*)&vars[opcode->operand0] = *(SPVM_VALUE_byte*)((intptr_t)array + (intptr_t)env->object_header_byte_size + sizeof(int8_t) * index);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_SHORT: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            *(SPVM_VALUE_short*)&vars[opcode->operand0]
              = *(SPVM_VALUE_short*)((intptr_t)array + (intptr_t)env->object_header_byte_size + sizeof(int16_t) * index);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_INT: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            *(SPVM_VALUE_int*)&vars[opcode->operand0] = *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_header_byte_size + sizeof(int32_t) * index);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_LONG: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            *(SPVM_VALUE_long*)&vars[opcode->operand0] = *(SPVM_VALUE_long*)((intptr_t)array + (intptr_t)env->object_header_byte_size + sizeof(int64_t) * index);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_FLOAT: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            *(float*)&vars[opcode->operand0] = *(float*)((intptr_t)array + (intptr_t)env->object_header_byte_size + sizeof(float) * index);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_DOUBLE: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            *(double*)&vars[opcode->operand0] = *(double*)((intptr_t)array + (intptr_t)env->object_header_byte_size + sizeof(double) * index);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_OBJECT: {
        void* array = *(void**)&vars[opcode->operand1];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(
              (void**)&vars[opcode->operand0],
              *(void**)((intptr_t)array + (intptr_t)env->object_header_byte_size + sizeof(void*) * index)
            );
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_BYTE: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            *(SPVM_VALUE_byte*)((intptr_t)array + (intptr_t)env->object_header_byte_size + sizeof(int8_t) * index) = *(SPVM_VALUE_byte*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_SHORT: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            *(SPVM_VALUE_short*)((intptr_t)array + (intptr_t)env->object_header_byte_size + sizeof(int16_t) * index) = *(SPVM_VALUE_short*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_INT: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_header_byte_size + sizeof(int32_t) * index) = *(SPVM_VALUE_int*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_LONG: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            *(SPVM_VALUE_long*)((intptr_t)array + (intptr_t)env->object_header_byte_size + sizeof(int64_t) * index) = *(SPVM_VALUE_long*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_FLOAT: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            *(float*)((intptr_t)array + (intptr_t)env->object_header_byte_size + sizeof(float) * index) = *(float*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_DOUBLE: {
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            *(double*)((intptr_t)array + (intptr_t)env->object_header_byte_size + sizeof(double) * index) = *(double*)&vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_OBJECT: {
        
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(
              (void**)((intptr_t)array + (intptr_t)env->object_header_byte_size + sizeof(SPVM_OBJECT*) * index),
              *(void**)&vars[opcode->operand2]
            );
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_UNDEF: {
        
        void* array = *(void**)&vars[opcode->operand0];
        int32_t index = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string(env, "Array must not be undef", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(SPVM_VALUE_int*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) {
            void* exception = env->new_string(env, "Index is out of range", 0);
            env->set_exception(env, exception);
            exception_flag = 1;
          }
          else {
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(
              (void**)((intptr_t)array + (intptr_t)env->object_header_byte_size + sizeof(SPVM_OBJECT*) * index),
              NULL
            );
          }
        }
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
        mortal_stack_top++;
        *(int32_t*)&mortal_stack[mortal_stack_top] = opcode->operand0;
        
        break;
      }
      case SPVM_OPCODE_C_ID_LEAVE_SCOPE: {
        int32_t mortal_stack_current_base = opcode->operand0;
        int32_t object_var_index_index;
        for (object_var_index_index = mortal_stack_current_base; object_var_index_index <= mortal_stack_top; object_var_index_index++) {
          int32_t var_index = mortal_stack[object_var_index_index].ival;
          
          if (*(void**)&vars[var_index] != NULL) {
            if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(*(void**)&vars[var_index]) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*(void**)&vars[var_index]); }
            else { env->dec_ref_count(env, *(void**)&vars[var_index]); }
          }
          
          *(void**)&vars[var_index] = NULL;
        }
        
        mortal_stack_top = mortal_stack_current_base - 1;
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT: {
        // Get field index
        int32_t basic_type_name_symbol_index = opcode->operand1;
        SPVM_SYMBOL* basic_type_name_symbol = SPVM_LIST_fetch(package->symbol_names, basic_type_name_symbol_index);
        const char* basic_type_name = basic_type_name_symbol->name;
        SPVM_BASIC_TYPE* basic_type = SPVM_HASH_fetch(compiler->basic_type_symtable, basic_type_name, strlen(basic_type_name));
        int32_t basic_type_id = basic_type->id;
        
        void* object = env->new_object(env, basic_type_id);
        
        // Push object
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_BYTE_ARRAY: {
        
        // length
        int32_t length = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        
        void* object = env->new_byte_array(env, length);
        
        // Set array
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY: {
        
        // length
        int32_t length = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        
        void* object = env->new_short_array(env, length);
        
        // Set array
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_INT_ARRAY: {
        
        // length
        int32_t length = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        
        void* object = env->new_int_array(env, length);
        
        // Set array
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_LONG_ARRAY: {
        
        // length
        int32_t length = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        
        void* object = env->new_long_array(env, length);
        
        // Set array
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY: {
        
        // length
        int32_t length = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        
        void* object = env->new_float_array(env, length);
        
        // Set array
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY: {
        
        // length
        int32_t length = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        
        void* object = env->new_double_array(env, length);
        
        // Set array
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        
        // length
        int32_t length = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        
        void* object = env->new_object_array(env, basic_type_id, length);
        
        // Set object
         SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULTI_ARRAY: {
        int32_t basic_type_id = (uint32_t)opcode->operand1 & 0xFFFFFF;
        int32_t element_dimension  = (uint32_t)opcode->operand1 >> 24;
        
        // length
        int32_t length = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        
        void* object = env->new_multi_array(env, basic_type_id, element_dimension, length);
        
        // Set object
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING: {
        int32_t constant_id = (opcode->operand1 << 16) + opcode->operand2;
        
        SPVM_OP* op_constant = SPVM_LIST_fetch(compiler->op_constants, constant_id);
        SPVM_CONSTANT* constant = op_constant->uv.constant;
        
        void* string = env->new_string(env, constant->value.oval, constant->string_length);
        
        // Set string
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0] , string);

        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LENGTH:
        if (*(void**)&vars[opcode->operand1] == NULL) {
          void* exception = env->new_string(env, "Can't get array length of undef value.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_int*)&vars[opcode->operand0] = *(SPVM_VALUE_int*)((intptr_t)*(void**)&vars[opcode->operand1] + (intptr_t)env->object_elements_length_byte_offset);
        }
        break;
      case SPVM_OPCODE_C_ID_GET_FIELD_BYTE: {
        int32_t rel_id = opcode->operand2;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(package->op_field_accesses, rel_id);
        int32_t field_rel_id = op_field_access->uv.field_access->field->rel_id;

        void* object = *(void**)&vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_byte*)&vars[opcode->operand0] = *(SPVM_VALUE_byte*)((intptr_t)object + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE) * field_rel_id);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_SHORT: {
        int32_t rel_id = opcode->operand2;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(package->op_field_accesses, rel_id);
        int32_t field_rel_id = op_field_access->uv.field_access->field->rel_id;

        void* object = *(void**)&vars[opcode->operand1];

        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_short*)&vars[opcode->operand0] = *(SPVM_VALUE_short*)((intptr_t)object + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE) * field_rel_id);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_INT: {
        int32_t rel_id = opcode->operand2;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(package->op_field_accesses, rel_id);
        int32_t field_rel_id = op_field_access->uv.field_access->field->rel_id;

        void* object = *(void**)&vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_int*)&vars[opcode->operand0] = *(SPVM_VALUE_int*)((intptr_t)object + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE) * field_rel_id);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_LONG: {
        int32_t rel_id = opcode->operand2;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(package->op_field_accesses, rel_id);
        int32_t field_rel_id = op_field_access->uv.field_access->field->rel_id;

        void* object = *(void**)&vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_long*)&vars[opcode->operand0] = *(SPVM_VALUE_long*)((intptr_t)object + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE) * field_rel_id);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_FLOAT: {
        int32_t rel_id = opcode->operand2;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(package->op_field_accesses, rel_id);
        int32_t field_rel_id = op_field_access->uv.field_access->field->rel_id;

        void* object = *(void**)&vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(float*)&vars[opcode->operand0] = *(float*)((intptr_t)object + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE) * field_rel_id);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE: {
        int32_t rel_id = opcode->operand2;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(package->op_field_accesses, rel_id);
        int32_t field_rel_id = op_field_access->uv.field_access->field->rel_id;

        void* object = *(void**)&vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(double*)&vars[opcode->operand0] = *(double*)((intptr_t)object + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE) * field_rel_id);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_OBJECT: {
        int32_t rel_id = opcode->operand2;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(package->op_field_accesses, rel_id);
        int32_t field_rel_id = op_field_access->uv.field_access->field->rel_id;

        void* object = *(void**)&vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], *(void**)((intptr_t)object + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE) * field_rel_id));
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_BYTE: {
        void* object = *(void**)&vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(package->op_field_accesses, rel_id);
        int32_t field_rel_id = op_field_access->uv.field_access->field->rel_id;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_byte*)((intptr_t)object + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE) * field_rel_id) = *(SPVM_VALUE_byte*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_SHORT: {
        void* object = *(void**)&vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(package->op_field_accesses, rel_id);
        int32_t field_rel_id = op_field_access->uv.field_access->field->rel_id;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_short*)((intptr_t)object + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE) * field_rel_id) = *(SPVM_VALUE_short*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_INT: {
        void* object = *(void**)&vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(package->op_field_accesses, rel_id);
        int32_t field_rel_id = op_field_access->uv.field_access->field->rel_id;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_int*)((intptr_t)object + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE) * field_rel_id) = *(SPVM_VALUE_int*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_LONG: {
        void* object = *(void**)&vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(package->op_field_accesses, rel_id);
        int32_t field_rel_id = op_field_access->uv.field_access->field->rel_id;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(SPVM_VALUE_long*)((intptr_t)object + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE) * field_rel_id) = *(SPVM_VALUE_long*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_FLOAT: {
        void* object = *(void**)&vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(package->op_field_accesses, rel_id);
        int32_t field_rel_id = op_field_access->uv.field_access->field->rel_id;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(float*)((intptr_t)object + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE) * field_rel_id) = *(float*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE: {
        void* object = *(void**)&vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(package->op_field_accesses, rel_id);
        int32_t field_rel_id = op_field_access->uv.field_access->field->rel_id;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          *(double*)((intptr_t)object + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE) * field_rel_id) = *(double*)&vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_OBJECT: {
        void* object = *(void**)&vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(package->op_field_accesses, rel_id);
        int32_t field_rel_id = op_field_access->uv.field_access->field->rel_id;

        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(
            (void**)((intptr_t)object + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE) * field_rel_id),
            *(void**)&vars[opcode->operand2]
          );
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_UNDEF: {
        void* object = *(void**)&vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(package->op_field_accesses, rel_id);
        int32_t field_rel_id = op_field_access->uv.field_access->field->rel_id;

        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string(env, "Object must be not undef.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
        }
        else {
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(
            (void**)((intptr_t)object + (intptr_t)env->object_header_byte_size + sizeof(SPVM_VALUE) * field_rel_id),
            NULL
          );
        }
        break;
      }
      case SPVM_OPCODE_C_ID_WEAKEN_FIELD_OBJECT: {
        void* object = *(void**)&vars[opcode->operand0];

        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(package->op_field_accesses, rel_id);
        int32_t field_rel_id = op_field_access->uv.field_access->field->rel_id;
        
        env->weaken_object_field(env, object, field_rel_id);
        
        if (env->get_exception(env)) {
          exception_flag = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CONCAT: {
        void* concat_string = env->concat(env, *(void**)&vars[opcode->operand1], *(void**)&vars[opcode->operand2]);
        if (concat_string == NULL) {
          exception_flag = 1;
        }
        else {
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(
            (void**)&vars[opcode->operand0],
            concat_string
          );
        }
        
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
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_BYTE: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(package->op_package_var_accesses, rel_id);
        int32_t package_var_id = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var->id;
        
        *(SPVM_VALUE_byte*)&vars[opcode->operand0] = *(SPVM_VALUE_byte*)&(*(SPVM_VALUE**)(env->get_runtime(env) + offsetof(SPVM_RUNTIME, package_var_accesss)))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_SHORT: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(package->op_package_var_accesses, rel_id);
        int32_t package_var_id = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var->id;
        
        *(SPVM_VALUE_short*)&vars[opcode->operand0] = *(SPVM_VALUE_short*)&(*(SPVM_VALUE**)(env->get_runtime(env) + offsetof(SPVM_RUNTIME, package_var_accesss)))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_INT: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(package->op_package_var_accesses, rel_id);
        int32_t package_var_id = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var->id;
        
        *(SPVM_VALUE_int*)&vars[opcode->operand0] = *(SPVM_VALUE_int*)&(*(SPVM_VALUE**)(env->get_runtime(env) + offsetof(SPVM_RUNTIME, package_var_accesss)))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_LONG: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(package->op_package_var_accesses, rel_id);
        int32_t package_var_id = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var->id;
        
        *(SPVM_VALUE_long*)&vars[opcode->operand0] = *(SPVM_VALUE_long*)&(*(SPVM_VALUE**)(env->get_runtime(env) + offsetof(SPVM_RUNTIME, package_var_accesss)))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_FLOAT: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(package->op_package_var_accesses, rel_id);
        int32_t package_var_id = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var->id;
        
        *(float*)&vars[opcode->operand0] = *(float*)&(*(SPVM_VALUE**)(env->get_runtime(env) + offsetof(SPVM_RUNTIME, package_var_accesss)))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_DOUBLE: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(package->op_package_var_accesses, rel_id);
        int32_t package_var_id = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var->id;
        
        *(double*)&vars[opcode->operand0] = *(double*)&(*(SPVM_VALUE**)(env->get_runtime(env) + offsetof(SPVM_RUNTIME, package_var_accesss)))[package_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_OBJECT: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(package->op_package_var_accesses, rel_id);
        int32_t package_var_id = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var->id;
        
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], *(void**)&(*(SPVM_VALUE**)(env->get_runtime(env) + offsetof(SPVM_RUNTIME, package_var_accesss)))[package_var_id]);
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_BYTE: {
        int32_t rel_id = opcode->operand0;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(package->op_package_var_accesses, rel_id);
        int32_t package_var_id = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var->id;
        
        *(SPVM_VALUE_byte*)&(*(SPVM_VALUE**)(env->get_runtime(env) + offsetof(SPVM_RUNTIME, package_var_accesss)))[package_var_id] = *(SPVM_VALUE_byte*)&vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_SHORT: {
        int32_t rel_id = opcode->operand0;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(package->op_package_var_accesses, rel_id);
        int32_t package_var_id = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var->id;
        
        *(SPVM_VALUE_short*)&(*(SPVM_VALUE**)(env->get_runtime(env) + offsetof(SPVM_RUNTIME, package_var_accesss)))[package_var_id] = *(SPVM_VALUE_short*)&vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_INT: {
        int32_t rel_id = opcode->operand0;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(package->op_package_var_accesses, rel_id);
        int32_t package_var_id = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var->id;
        
        *(SPVM_VALUE_int*)&(*(SPVM_VALUE**)(env->get_runtime(env) + offsetof(SPVM_RUNTIME, package_var_accesss)))[package_var_id] = *(SPVM_VALUE_int*)&vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_LONG: {
        int32_t rel_id = opcode->operand0;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(package->op_package_var_accesses, rel_id);
        int32_t package_var_id = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var->id;
        
        *(SPVM_VALUE_long*)&(*(SPVM_VALUE**)(env->get_runtime(env) + offsetof(SPVM_RUNTIME, package_var_accesss)))[package_var_id] = *(SPVM_VALUE_long*)&vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_FLOAT: {
        int32_t rel_id = opcode->operand0;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(package->op_package_var_accesses, rel_id);
        int32_t package_var_id = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var->id;
        
        *(float*)&(*(SPVM_VALUE**)(env->get_runtime(env) + offsetof(SPVM_RUNTIME, package_var_accesss)))[package_var_id] = *(float*)&vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_DOUBLE: {
        int32_t rel_id = opcode->operand0;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(package->op_package_var_accesses, rel_id);
        int32_t package_var_id = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var->id;
        
        *(double*)&(*(SPVM_VALUE**)(env->get_runtime(env) + offsetof(SPVM_RUNTIME, package_var_accesss)))[package_var_id] = *(double*)&vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_OBJECT: {
        int32_t rel_id = opcode->operand0;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(package->op_package_var_accesses, rel_id);
        int32_t package_var_id = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var->id;
        
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&(*(SPVM_VALUE**)(env->get_runtime(env) + offsetof(SPVM_RUNTIME, package_var_accesss)))[package_var_id], *(void**)&vars[opcode->operand1]);
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_UNDEF: {
        int32_t rel_id = opcode->operand0;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(package->op_package_var_accesses, rel_id);
        int32_t package_var_id = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var->id;
        
        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&(*(SPVM_VALUE**)(env->get_runtime(env) + offsetof(SPVM_RUNTIME, package_var_accesss)))[package_var_id], NULL);
        
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
        *(SPVM_VALUE_byte*)&args[call_sub_arg_stack_top] = *(SPVM_VALUE_byte*)&vars[opcode->operand0];
        
        break;
      case SPVM_OPCODE_C_ID_PUSH_ARG_SHORT:
        call_sub_arg_stack_top++;
        *(SPVM_VALUE_short*)&args[call_sub_arg_stack_top] = *(SPVM_VALUE_short*)&vars[opcode->operand0];
        
        break;
      case SPVM_OPCODE_C_ID_PUSH_ARG_INT:
        call_sub_arg_stack_top++;
        *(SPVM_VALUE_int*)&args[call_sub_arg_stack_top] = *(SPVM_VALUE_int*)&vars[opcode->operand0];
        
        break;
      case SPVM_OPCODE_C_ID_PUSH_ARG_LONG:
        call_sub_arg_stack_top++;
        *(SPVM_VALUE_long*)&args[call_sub_arg_stack_top] = *(SPVM_VALUE_long*)&vars[opcode->operand0];
        
        break;
      case SPVM_OPCODE_C_ID_PUSH_ARG_FLOAT:
        call_sub_arg_stack_top++;
        *(SPVM_VALUE_float*)&args[call_sub_arg_stack_top] = *(SPVM_VALUE_float*)&vars[opcode->operand0];
        
        break;
      case SPVM_OPCODE_C_ID_PUSH_ARG_DOUBLE:
        call_sub_arg_stack_top++;
        *(SPVM_VALUE_double*)&args[call_sub_arg_stack_top] = *(SPVM_VALUE_double*)&vars[opcode->operand0];
        
        break;
      case SPVM_OPCODE_C_ID_PUSH_ARG_OBJECT:
        call_sub_arg_stack_top++;
        *(void**)&args[call_sub_arg_stack_top] = *(void**)&vars[opcode->operand0];
        
        break;
      case SPVM_OPCODE_C_ID_PUSH_ARG_UNDEF:
        call_sub_arg_stack_top++;
        *(void**)&args[call_sub_arg_stack_top] = NULL;
        
        break;
      case SPVM_OPCODE_C_ID_CHECK_CAST: {
        void* object = *(void**)&vars[opcode->operand1];

        int32_t cast_basic_type_id = (uint32_t)opcode->operand2 & 0xFFFFFF;
        int32_t cast_type_dimension  = (uint32_t)opcode->operand2 >> 24;
        
        _Bool can_assign = env->check_cast(env, cast_basic_type_id, cast_type_dimension, object);
        if (can_assign) {
          SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], object);
        }
        else {
          void* exception = env->new_string(env, "Can't cast uncompatible type.", 0);
          env->set_exception(env, exception);
          exception_flag = 1;
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
        int32_t decl_sub_return_type_is_object = SPVM_TYPE_is_object(compiler, decl_sub_return_type);
        
        // Declare subroutine argument length
        int32_t decl_sub_args_length = decl_sub->op_args->length;
        
        // Call subroutine id
        int32_t call_sub_id;
        if (opcode->id == SPVM_OPCODE_C_ID_CALL_SUB) {
           call_sub_id = decl_sub_id;
        }
        else if (opcode->id == SPVM_OPCODE_C_ID_CALL_INTERFACE_METHOD) {
          void* object = *(void**)&vars[opcode->operand2];
          call_sub_id = env->get_sub_id_method_call(env, object, decl_sub->op_name->uv.name);
        }
        else {
          assert(0);
        }
        
        call_sub_arg_stack_top -= decl_sub_args_length;
        
        // Call subroutine
        exception_flag = env->call_sub(env, call_sub_id, args);
        if (!exception_flag) {
          if (decl_sub_return_type_is_object) {
            SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&vars[opcode->operand0], args[0].oval);
          }
          else {
            int32_t decl_sub_return_basic_type_id = decl_sub_return_type->basic_type->id;
            if (decl_sub_return_basic_type_id != SPVM_BASIC_TYPE_C_ID_VOID) {
              vars[opcode->operand0] = args[0];
            }
          }
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_IF_CROAK_CATCH: {
        if (exception_flag) {
          exception_flag = 0;
          
          int32_t sub_id = opcode->operand1;
          int32_t line = opcode->operand2;
          
          // Exception stack trace
          env->set_exception(env, env->create_exception_stack_trace(env, env->get_exception(env), sub_id, line));
          opcode_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_IF_CROAK_RETURN: {
        if (exception_flag) {
          int32_t sub_id = opcode->operand1;
          int32_t line = opcode->operand2;

          // Exception stack trace
          env->set_exception(env, env->create_exception_stack_trace(env, env->get_exception(env), sub_id, line));
          opcode_index = opcode->operand0;
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
        opcode_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_BYTE:
      {
        *(SPVM_VALUE_byte*)&args[0] = *(SPVM_VALUE_byte*)&vars[opcode->operand0];
        opcode_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_SHORT:
      {
        *(SPVM_VALUE_short*)&args[0] = *(SPVM_VALUE_short*)&vars[opcode->operand0];
        opcode_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_INT:
      {
        *(SPVM_VALUE_int*)&args[0] = *(SPVM_VALUE_int*)&vars[opcode->operand0];
        opcode_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_LONG:
      {
        *(SPVM_VALUE_long*)&args[0] = *(SPVM_VALUE_long*)&vars[opcode->operand0];
        opcode_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_FLOAT:
      {
        *(SPVM_VALUE_float*)&args[0] = *(SPVM_VALUE_float*)&vars[opcode->operand0];
        opcode_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_DOUBLE:
      {
        *(SPVM_VALUE_double*)&args[0] = *(SPVM_VALUE_double*)&vars[opcode->operand0];
        opcode_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_OBJECT:
      {
        *(void**)&args[0] = *(void**)&vars[opcode->operand0];
        // Increment ref count of return value not to release by leave scope
        if (*(void**)&args[0] != NULL) {
          SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(*(void**)&args[0]);
        }
        opcode_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_UNDEF:
      {
        *(void**)&args[0] = NULL;
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
        
        if (*(SPVM_VALUE_int*)&vars[opcode->operand0] >= min && *(SPVM_VALUE_int*)&vars[opcode->operand0] <= max) {
          int32_t branch_offset = (opcode + 2 + *(SPVM_VALUE_int*)&vars[opcode->operand0] - min)->operand1;
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
        
        if (*(SPVM_VALUE_int*)&vars[opcode->operand0] >= min && *(SPVM_VALUE_int*)&vars[opcode->operand0] <= max) {
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
            
            if (*(SPVM_VALUE_int*)&vars[opcode->operand0] > cur_half) {
              cur_min_pos = cur_half_pos + 1;
            }
            else if (*(SPVM_VALUE_int*)&vars[opcode->operand0] < cur_half) {
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
  if (!exception_flag) {
    // Decrement ref count of return value
    if (sub_return_type_is_object) {
      if (*(void**)&args[0] != NULL) {
        SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*(void**)&args[0]);
      }
    }
    
    env->set_exception(env, NULL);
  }
  
  SPVM_RUNTIME_ALLOCATOR_free(runtime, call_frame);
  
  return exception_flag;
}

void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime) {
  
  // Free exception
  SPVM_RUNTIME_API_set_exception(runtime->env, NULL);
  
  free(runtime->args);
  
  free(runtime->package_var_accesss);
  
  free(runtime);
}
