// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>
#include <stdarg.h>

#include "spvm_api.h"
#include "spvm_vm.h"
#include "spvm_native.h"

#include "spvm_allocator.h"

#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_string_buffer.h"

#include "spvm_opcode.h"
#include "spvm_object.h"
#include "spvm_weaken_backref.h"

#include "spvm_runtime.h"
#include "spvm_runtime_string.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_class_var.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_method.h"

#include "spvm_api_string_buffer.h"
#include "spvm_api_allocator.h"
#include "spvm_api_runtime.h"
#include "spvm_api_basic_type.h"
#include "spvm_api_class_var.h"
#include "spvm_api_field.h"
#include "spvm_api_method.h"
#include "spvm_api_arg.h"

#include "spvm_implement.h"
#include "spvm_type.h"
#include "spvm_runtime_call_stack_frame_info.h"

static const char* FILE_NAME = "spvm_vm.c";

int32_t SPVM_VM_call_method(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* current_method, int32_t args_width) {
  
  int32_t error_id = 0;
  
  int64_t* long_vars = NULL;
  
  double* double_vars = NULL;
  
  void** object_vars = NULL;
  
  void** ref_vars = NULL;
  
  int32_t* int_vars = NULL;
  
  float* float_vars = NULL;
  
  // Mortal stack for object variable indexes
  int32_t* mortal_stack = NULL;
  int32_t mortal_stack_top = 0;
  int32_t* mortal_stack_tops = NULL;
  
  int16_t* short_vars = NULL;
  
  int8_t* byte_vars = NULL;
  
  SPVM_RUNTIME_CALL_STACK_FRAME_INFO call_stack_frame_info_st = {0};
  SPVM_RUNTIME_CALL_STACK_FRAME_INFO* call_stack_frame_info = &call_stack_frame_info_st;
  
  call_stack_frame_info->long_vars_address = &long_vars;
  call_stack_frame_info->double_vars_address = &double_vars;
  call_stack_frame_info->object_vars_address = &object_vars;
  call_stack_frame_info->ref_vars_address = &ref_vars;
  call_stack_frame_info->int_vars_address = &int_vars;
  call_stack_frame_info->float_vars_address = &float_vars;
  call_stack_frame_info->mortal_stack_address = &mortal_stack;
  call_stack_frame_info->mortal_stack_tops_address = &mortal_stack_tops;
  call_stack_frame_info->short_vars_address = &short_vars;
  call_stack_frame_info->byte_vars_address = &byte_vars;
  call_stack_frame_info->method = current_method;
  
  // Alloc variable memory
  // Allignment is 8. This is numeric type max byte size
  // Order 8, 4, 2, 1 numeric variable, and addrress variables
  int32_t status_push_call_stack_frame = SPVM_API_push_call_stack_frame(env, stack, call_stack_frame_info);
  if (!(status_push_call_stack_frame == 0)) {
    void* exception = SPVM_API_new_string_nolen_no_mortal(env, stack, "A creation of a stack frame failed.");
    SPVM_API_set_exception(env, stack, exception);
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    goto END_OF_FUNC;
  }
  
  SPVM_RUNTIME* runtime = env->runtime;
  SPVM_RUNTIME_BASIC_TYPE* current_basic_type = current_method->current_basic_type;
  SPVM_OPCODE* opcodes = current_method->opcodes;
  int32_t eval_error_id = 0;
  
  // Execute operation codes
  int32_t opcode_rel_index = 0;
  while (1) {
    SPVM_OPCODE* opcode = &(opcodes[opcode_rel_index]);
    
    int32_t opcode_id = opcode->id;
    
    // spvm_warn("[OPCODE]%s %s#%s", SPVM_OPCODE_get_opcode_name(opcode_id), current_basic_type->name, current_method->name);
    
    switch (opcode_id) {

      case SPVM_OPCODE_C_ID_END_METHOD: {
        goto END_OF_FUNC;
      }
      case SPVM_OPCODE_C_ID_GOTO: {
        opcode_rel_index = opcode->operand0;
        continue;
      }
      case SPVM_OPCODE_C_ID_IF_EQ_ZERO: {
        if (int_vars[opcode->operand1] == 0) {
          opcode_rel_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_IF_NE_ZERO: {
        if (int_vars[opcode->operand1] != 0) {
          opcode_rel_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CATCH_ON_EXCEPTION: {
        if (__builtin_expect(error_id, 0)) {
          int32_t line = opcode->operand2;
          eval_error_id = error_id;
          error_id = 0;
          SPVM_API_set_exception(env, stack, SPVM_API_new_stack_trace_no_mortal(env, stack, SPVM_API_get_exception(env, stack), current_method, line));
          opcode_rel_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_ON_EXCEPTION: {
        if (__builtin_expect(error_id, 0)) {
          int32_t line = opcode->operand2;
          SPVM_API_set_exception(env, stack, SPVM_API_new_stack_trace_no_mortal(env, stack, SPVM_API_get_exception(env, stack), current_method, line));
          opcode_rel_index = opcode->operand0; 
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_LOOKUP_SWITCH: {
        
        // Default branch
        int32_t default_opcode_rel_index = opcode->operand1;
        
        // Cases length
        int32_t case_infos_length = opcode->operand2;

        if (case_infos_length > 0) {
          // min
          SPVM_OPCODE* opcode_case_info_min = &(opcodes[opcode_rel_index + 1 + 0]);
          int32_t min = opcode_case_info_min->operand1;
          
          // max
          SPVM_OPCODE* opcode_case_info_max = &(opcodes[opcode_rel_index + 1 + case_infos_length - 1]);
          int32_t max = opcode_case_info_max->operand1;
          
          if (int_vars[opcode->operand0] >= min && int_vars[opcode->operand0] <= max) {
            // 2 opcode_rel_index searching
            int32_t current_min_pos = 0;
            int32_t current_max_pos = case_infos_length - 1;
            
            while (1) {
              if (current_max_pos < current_min_pos) {
                opcode_rel_index = default_opcode_rel_index;
                break;
              }
              int32_t current_half_pos = current_min_pos + (current_max_pos - current_min_pos) / 2;
              SPVM_OPCODE* opcode_case_cur_half = &(opcodes[opcode_rel_index + 1 + current_half_pos]);
              int32_t current_half = opcode_case_cur_half->operand1;
              
              if (int_vars[opcode->operand0] > current_half) {
                current_min_pos = current_half_pos + 1;
              }
              else if (int_vars[opcode->operand0] < current_half) {
                current_max_pos = current_half_pos - 1;
              }
              else {
                opcode_rel_index = opcode_case_cur_half->operand2;
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
      case SPVM_OPCODE_C_ID_PUSH_MORTAL: {
        SPVM_IMPLEMENT_PUSH_MORTAL(mortal_stack, mortal_stack_top, opcode->operand0);
        break;
      }
      case SPVM_OPCODE_C_ID_ENTER_SCOPE: {
        int32_t mortal_stack_tops_index = opcode->operand0;
        SPVM_IMPLEMENT_ENTER_SCOPE(mortal_stack, mortal_stack_top, mortal_stack_tops, mortal_stack_tops_index);
        break;
      }
      case SPVM_OPCODE_C_ID_LEAVE_SCOPE: {
        int32_t mortal_stack_tops_index = opcode->operand0;
        SPVM_IMPLEMENT_LEAVE_SCOPE(env, stack, object_vars, mortal_stack, &mortal_stack_top, mortal_stack_tops, mortal_stack_tops_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_BYTE_ZERO: {
        SPVM_IMPLEMENT_MOVE_BYTE_ZERO(byte_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_SHORT_ZERO: {
        SPVM_IMPLEMENT_MOVE_SHORT_ZERO(short_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_INT_ZERO: {
        SPVM_IMPLEMENT_MOVE_INT_ZERO(int_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_LONG_ZERO: {
        SPVM_IMPLEMENT_MOVE_LONG_ZERO(long_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_FLOAT_ZERO: {
        SPVM_IMPLEMENT_MOVE_FLOAT_ZERO(float_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_DOUBLE_ZERO: {
        SPVM_IMPLEMENT_MOVE_DOUBLE_ZERO(double_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_OBJECT_UNDEF: {
        SPVM_IMPLEMENT_MOVE_OBJECT_UNDEF(env, stack, &object_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_BYTE_ZERO: {
        SPVM_IMPLEMENT_MOVE_MULNUM_BYTE_ZERO(env, stack, &byte_vars[opcode->operand0], opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_SHORT_ZERO: {
        SPVM_IMPLEMENT_MOVE_MULNUM_SHORT_ZERO(env, stack, &short_vars[opcode->operand0], opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_INT_ZERO: {
        SPVM_IMPLEMENT_MOVE_MULNUM_INT_ZERO(env, stack, &int_vars[opcode->operand0], opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_LONG_ZERO: {
        SPVM_IMPLEMENT_MOVE_MULNUM_LONG_ZERO(env, stack, &long_vars[opcode->operand0], opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_FLOAT_ZERO: {
        SPVM_IMPLEMENT_MOVE_MULNUM_FLOAT_ZERO(env, stack, &float_vars[opcode->operand0], opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_DOUBLE_ZERO: {
        SPVM_IMPLEMENT_MOVE_MULNUM_DOUBLE_ZERO(env, stack, &double_vars[opcode->operand0], opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_BYTE: {
        SPVM_IMPLEMENT_MOVE_CONSTANT_BYTE(byte_vars[opcode->operand0], (int8_t)(uint8_t)opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_INT: {
        SPVM_IMPLEMENT_MOVE_CONSTANT_INT(int_vars[opcode->operand0], (int32_t)opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_LONG: {
        SPVM_IMPLEMENT_MOVE_CONSTANT_LONG(long_vars[opcode->operand0], *(int64_t*)&opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_FLOAT: {
        SPVM_VALUE value;
        value.ival = (int32_t)opcode->operand1;
        SPVM_IMPLEMENT_MOVE_CONSTANT_FLOAT(float_vars[opcode->operand0], value.fval);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_DOUBLE: {
        SPVM_IMPLEMENT_MOVE_CONSTANT_DOUBLE(double_vars[opcode->operand0], *(double*)&opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_BYTE: {
        SPVM_IMPLEMENT_MOVE_BYTE(byte_vars[opcode->operand0], byte_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_SHORT: {
        SPVM_IMPLEMENT_MOVE_SHORT(short_vars[opcode->operand0], short_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_INT: {
        SPVM_IMPLEMENT_MOVE_INT(int_vars[opcode->operand0], int_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_LONG: {
        SPVM_IMPLEMENT_MOVE_LONG(long_vars[opcode->operand0], long_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_FLOAT: {
        SPVM_IMPLEMENT_MOVE_FLOAT(float_vars[opcode->operand0], float_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_DOUBLE: {
        SPVM_IMPLEMENT_MOVE_DOUBLE(double_vars[opcode->operand0], double_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_OBJECT: {
        SPVM_IMPLEMENT_MOVE_OBJECT(env, stack, &object_vars[opcode->operand0], object_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECK: {
        int32_t dist_basic_type_id = opcode->operand2;
        int32_t dist_type_dimension = opcode->operand3;
        
        void* dist_basic_type = runtime->basic_types[dist_basic_type_id];
        
        SPVM_IMPLEMENT_MOVE_OBJECT_WITH_TYPE_CHECK(env, stack, &object_vars[opcode->operand0], object_vars[opcode->operand1], dist_basic_type, dist_type_dimension, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_OBJECT_CHECK_READ_ONLY_STRING: {
        SPVM_IMPLEMENT_MOVE_OBJECT_CHECK_READ_ONLY_STRING(env, stack, &object_vars[opcode->operand0], object_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_ANY_OBJECT_TO_STRING: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_ANY_OBJECT_TO_STRING(env, stack, &object_vars[opcode->operand0], object_vars[opcode->operand1], opcode->operand2, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_REF: {
        SPVM_IMPLEMENT_MOVE_REF(ref_vars[opcode->operand0], ref_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_REF_UNDEF: {
        SPVM_IMPLEMENT_MOVE_REF_UNDEF(ref_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_ADD_INT: {
        SPVM_IMPLEMENT_ADD_INT(int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_ADD_LONG: {
        SPVM_IMPLEMENT_ADD_LONG(long_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_ADD_FLOAT: {
        SPVM_IMPLEMENT_ADD_FLOAT(float_vars[opcode->operand0], float_vars[opcode->operand1], float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_ADD_DOUBLE: {
        SPVM_IMPLEMENT_ADD_DOUBLE(double_vars[opcode->operand0], double_vars[opcode->operand1], double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_INT: {
        SPVM_IMPLEMENT_SUBTRACT_INT(int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_LONG: {
        SPVM_IMPLEMENT_SUBTRACT_LONG(long_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_FLOAT: {
        SPVM_IMPLEMENT_SUBTRACT_FLOAT(float_vars[opcode->operand0], float_vars[opcode->operand1], float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_DOUBLE: {
        SPVM_IMPLEMENT_SUBTRACT_DOUBLE(double_vars[opcode->operand0], double_vars[opcode->operand1], double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_INT: {
        SPVM_IMPLEMENT_MULTIPLY_INT(int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_LONG: {
        SPVM_IMPLEMENT_MULTIPLY_LONG(long_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_FLOAT: {
        SPVM_IMPLEMENT_MULTIPLY_FLOAT(float_vars[opcode->operand0], float_vars[opcode->operand1], float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_DOUBLE: {
        SPVM_IMPLEMENT_MULTIPLY_DOUBLE(double_vars[opcode->operand0], double_vars[opcode->operand1], double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_INT: {
        SPVM_IMPLEMENT_DIVIDE_INT(env, stack, &int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_LONG: {
        SPVM_IMPLEMENT_DIVIDE_LONG(env, stack, &long_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_FLOAT: {
        SPVM_IMPLEMENT_DIVIDE_FLOAT(float_vars[opcode->operand0], float_vars[opcode->operand1], float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_DOUBLE: {
        SPVM_IMPLEMENT_DIVIDE_DOUBLE(double_vars[opcode->operand0], double_vars[opcode->operand1], double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_UNSIGNED_INT: {
        SPVM_IMPLEMENT_DIVIDE_UNSIGNED_INT(env, stack, &int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_UNSIGNED_LONG: {
        SPVM_IMPLEMENT_DIVIDE_UNSIGNED_LONG(env, stack, &long_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_MODULO_INT: {
        SPVM_IMPLEMENT_MODULO_INT(env, stack, &int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_MODULO_LONG: {
        SPVM_IMPLEMENT_MODULO_LONG(env, stack, &long_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_MODULO_UNSIGNED_INT: {
        SPVM_IMPLEMENT_MODULO_UNSIGNED_INT(env, stack, &int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_MODULO_UNSIGNED_LONG: {
        SPVM_IMPLEMENT_MODULO_UNSIGNED_LONG(env, stack, &long_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_INT: {
        SPVM_IMPLEMENT_LEFT_SHIFT_INT(int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_LONG: {
        SPVM_IMPLEMENT_LEFT_SHIFT_LONG(long_vars[opcode->operand0], long_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_INT: {
        SPVM_IMPLEMENT_RIGHT_ARITHMETIC_SHIFT_INT(int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_LONG: {
        SPVM_IMPLEMENT_RIGHT_ARITHMETIC_SHIFT_LONG(long_vars[opcode->operand0], long_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_INT: {
        SPVM_IMPLEMENT_RIGHT_LOGICAL_SHIFT_INT(int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_LONG: {
        SPVM_IMPLEMENT_RIGHT_LOGICAL_SHIFT_LONG(long_vars[opcode->operand0], long_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_AND_INT: {
        SPVM_IMPLEMENT_BIT_AND_INT(int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_AND_LONG: {
        SPVM_IMPLEMENT_BIT_AND_LONG(long_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_OR_INT: {
        SPVM_IMPLEMENT_BIT_OR_INT(int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_OR_LONG: {
        SPVM_IMPLEMENT_BIT_OR_LONG(long_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_XOR_INT: {
        SPVM_IMPLEMENT_BIT_XOR_INT(int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_XOR_LONG: {
        SPVM_IMPLEMENT_BIT_XOR_LONG(long_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_NOT_INT: {
        SPVM_IMPLEMENT_BIT_NOT_INT(int_vars[opcode->operand0], int_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_NOT_LONG: {
        SPVM_IMPLEMENT_BIT_NOT_LONG(long_vars[opcode->operand0], long_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_INT: {
        SPVM_IMPLEMENT_NEGATE_INT(int_vars[opcode->operand0], int_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_LONG: {
        SPVM_IMPLEMENT_NEGATE_LONG(long_vars[opcode->operand0], long_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_FLOAT: {
        SPVM_IMPLEMENT_NEGATE_FLOAT(float_vars[opcode->operand0], float_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_DOUBLE: {
        SPVM_IMPLEMENT_NEGATE_DOUBLE(double_vars[opcode->operand0], double_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_CONCAT: {
        SPVM_IMPLEMENT_STRING_CONCAT(env, stack, &object_vars[opcode->operand0], object_vars[opcode->operand1], object_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_CONDITION_EVALUATION_INT: {
        SPVM_IMPLEMENT_CONDITION_EVALUATION_INT(int_vars[opcode->operand0], int_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_CONDITION_EVALUATION_LONG: {
        SPVM_IMPLEMENT_CONDITION_EVALUATION_LONG(int_vars[opcode->operand0], long_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_CONDITION_EVALUATION_FLOAT: {
        SPVM_IMPLEMENT_CONDITION_EVALUATION_FLOAT(int_vars[opcode->operand0], float_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_CONDITION_EVALUATION_DOUBLE: {
        SPVM_IMPLEMENT_CONDITION_EVALUATION_DOUBLE(int_vars[opcode->operand0], double_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_CONDITION_EVALUATION_OBJECT: {
        SPVM_IMPLEMENT_CONDITION_EVALUATION_OBJECT(int_vars[opcode->operand0], object_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_CONDITION_EVALUATION_REF: {
        SPVM_IMPLEMENT_CONDITION_EVALUATION_REF(int_vars[opcode->operand0], ref_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_CONDITION_EVALUATION_BOOL_OBJECT: {
        SPVM_IMPLEMENT_CONDITION_EVALUATION_BOOL_OBJECT(env, stack, int_vars[opcode->operand0], object_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_EQ_INT: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_EQ_INT(int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_EQ_LONG: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_EQ_LONG(int_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_EQ_FLOAT: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_EQ_FLOAT(int_vars[opcode->operand0], float_vars[opcode->operand1], float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_EQ_DOUBLE: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_EQ_DOUBLE(int_vars[opcode->operand0], double_vars[opcode->operand1], double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_EQ_OBJECT: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_EQ_OBJECT(int_vars[opcode->operand0], object_vars[opcode->operand1], object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_EQ_REF: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_EQ_REF(int_vars[opcode->operand0], ref_vars[opcode->operand1], ref_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_NE_INT: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_NE_INT(int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_NE_LONG: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_NE_LONG(int_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_NE_FLOAT: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_NE_FLOAT(int_vars[opcode->operand0], float_vars[opcode->operand1], float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_NE_DOUBLE: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_NE_DOUBLE(int_vars[opcode->operand0], double_vars[opcode->operand1], double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_NE_OBJECT: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_NE_OBJECT(int_vars[opcode->operand0], object_vars[opcode->operand1], object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_NE_REF: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_NE_REF(int_vars[opcode->operand0], ref_vars[opcode->operand1], ref_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_GT_INT: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_GT_INT(int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_GT_LONG: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_GT_LONG(int_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_GT_FLOAT: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_GT_FLOAT(int_vars[opcode->operand0], float_vars[opcode->operand1], float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_GT_DOUBLE: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_GT_DOUBLE(int_vars[opcode->operand0], double_vars[opcode->operand1], double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_GE_INT: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_GE_INT(int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_GE_LONG: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_GE_LONG(int_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_GE_FLOAT: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_GE_FLOAT(int_vars[opcode->operand0], float_vars[opcode->operand1], float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_GE_DOUBLE: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_GE_DOUBLE(int_vars[opcode->operand0], double_vars[opcode->operand1], double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_LT_INT: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_LT_INT(int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_LT_LONG: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_LT_LONG(int_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_LT_FLOAT: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_LT_FLOAT(int_vars[opcode->operand0], float_vars[opcode->operand1], float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_LT_DOUBLE: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_LT_DOUBLE(int_vars[opcode->operand0], double_vars[opcode->operand1], double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_LE_INT: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_LE_INT(int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_LE_LONG: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_LE_LONG(int_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_LE_FLOAT: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_LE_FLOAT(int_vars[opcode->operand0], float_vars[opcode->operand1], float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_LE_DOUBLE: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_LE_DOUBLE(int_vars[opcode->operand0], double_vars[opcode->operand1], double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_CMP_INT: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_CMP_INT(int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_CMP_LONG: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_CMP_LONG(int_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_CMP_FLOAT: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_CMP_FLOAT(int_vars[opcode->operand0], float_vars[opcode->operand1], float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_CMP_DOUBLE: {
        SPVM_IMPLEMENT_NUMERIC_COMPARISON_CMP_DOUBLE(int_vars[opcode->operand0], double_vars[opcode->operand1], double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_IS_UNDEF_OBJECT: {
        SPVM_IMPLEMENT_IS_UNDEF_OBJECT(int_vars[opcode->operand0], object_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_IS_UNDEF_REF: {
        SPVM_IMPLEMENT_IS_UNDEF_REF(int_vars[opcode->operand0], ref_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_IS_NOT_UNDEF_OBJECT: {
        SPVM_IMPLEMENT_IS_NOT_UNDEF_OBJECT(int_vars[opcode->operand0], object_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_IS_NOT_UNDEF_REF: {
        SPVM_IMPLEMENT_IS_NOT_UNDEF_REF(int_vars[opcode->operand0], ref_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_COMPARISON_EQ: {
        SPVM_IMPLEMENT_STRING_COMPARISON_EQ(env, stack, &int_vars[opcode->operand0], object_vars[opcode->operand1], object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_COMPARISON_NE: {
        SPVM_IMPLEMENT_STRING_COMPARISON_NE(env, stack, &int_vars[opcode->operand0], object_vars[opcode->operand1], object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_COMPARISON_GT: {
        SPVM_IMPLEMENT_STRING_COMPARISON_GT(env, stack, &int_vars[opcode->operand0], object_vars[opcode->operand1], object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_COMPARISON_GE: {
        SPVM_IMPLEMENT_STRING_COMPARISON_GE(env, stack, &int_vars[opcode->operand0], object_vars[opcode->operand1], object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_COMPARISON_LT: {
        SPVM_IMPLEMENT_STRING_COMPARISON_LT(env, stack, &int_vars[opcode->operand0], object_vars[opcode->operand1], object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_COMPARISON_LE: {
        SPVM_IMPLEMENT_STRING_COMPARISON_LE(env, stack, &int_vars[opcode->operand0], object_vars[opcode->operand1], object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_COMPARISON_CMP: {
        SPVM_IMPLEMENT_STRING_COMPARISON_CMP(env, stack, &int_vars[opcode->operand0], object_vars[opcode->operand1], object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT: {
        int32_t basic_type_id = opcode->operand1;
        
        SPVM_RUNTIME_BASIC_TYPE* basic_type = runtime->basic_types[basic_type_id];
        
        SPVM_IMPLEMENT_NEW_OBJECT(env, stack, &object_vars[opcode->operand0], basic_type, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        int32_t length = int_vars[opcode->operand2];
        
        SPVM_RUNTIME_BASIC_TYPE* basic_type = runtime->basic_types[basic_type_id];
        
        SPVM_IMPLEMENT_NEW_OBJECT_ARRAY(env, stack, &object_vars[opcode->operand0], basic_type, length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULDIM_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        int32_t type_dimension = opcode->operand3;
        int32_t length = int_vars[opcode->operand2];
        
        SPVM_RUNTIME_BASIC_TYPE* basic_type = runtime->basic_types[basic_type_id];
        
        SPVM_IMPLEMENT_NEW_MULDIM_ARRAY(env, stack, &object_vars[opcode->operand0], basic_type, type_dimension, length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULNUM_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        int32_t length = int_vars[opcode->operand2];
        
        SPVM_RUNTIME_BASIC_TYPE* basic_type = runtime->basic_types[basic_type_id];
        
        SPVM_IMPLEMENT_NEW_MULNUM_ARRAY(env, stack, &object_vars[opcode->operand0], basic_type, length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_BYTE_ARRAY: {
        int32_t length = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_NEW_BYTE_ARRAY(env, stack, &object_vars[opcode->operand0], length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY: {
        int32_t length = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_NEW_SHORT_ARRAY(env, stack, &object_vars[opcode->operand0], length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_INT_ARRAY: {
        int32_t length = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_NEW_INT_ARRAY(env, stack, &object_vars[opcode->operand0], length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_LONG_ARRAY: {
        int32_t length = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_NEW_LONG_ARRAY(env, stack, &object_vars[opcode->operand0], length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY: {
        int32_t length = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_NEW_FLOAT_ARRAY(env, stack, &object_vars[opcode->operand0], length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY: {
        int32_t length = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_NEW_DOUBLE_ARRAY(env, stack, &object_vars[opcode->operand0], length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING: {
        int32_t constant_string_index = opcode->operand1;
        SPVM_RUNTIME_STRING* constant_string = &current_basic_type->constant_strings[constant_string_index];
        const char* constant_string_value = constant_string->value;
        int32_t constant_string_length = constant_string->length;
        SPVM_IMPLEMENT_NEW_STRING(env, stack, &object_vars[opcode->operand0], constant_string_value, constant_string_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING_LEN: {
        int32_t length = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_NEW_STRING_LEN(env, stack, &object_vars[opcode->operand0], length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_IS_READ_ONLY: {
        SPVM_IMPLEMENT_IS_READ_ONLY(env, stack, int_vars[opcode->operand0], object_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_IS_FIXED_LENGTH: {
        SPVM_IMPLEMENT_IS_FIXED_LENGTH(env, stack, int_vars[opcode->operand0], object_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_IS_OPTIONS: {
        SPVM_IMPLEMENT_IS_OPTIONS(env, stack, int_vars[opcode->operand0], object_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_MAKE_READ_ONLY: {
        SPVM_IMPLEMENT_MAKE_READ_ONLY(env, stack, object_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_MAKE_FIXED_LENGTH: {
        SPVM_IMPLEMENT_MAKE_FIXED_LENGTH(env, stack, object_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_ENABLE_OPTIONS: {
        SPVM_IMPLEMENT_ENABLE_OPTIONS(env, stack, object_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_DISABLE_OPTIONS: {
        SPVM_IMPLEMENT_DISABLE_OPTIONS(env, stack, object_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_BYTE: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_BYTE(env, stack, &byte_vars[opcode->operand0], array, index, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_SHORT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_SHORT(env, stack, &short_vars[opcode->operand0], array, index, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_INT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_INT(env, stack, &int_vars[opcode->operand0], array, index, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_LONG: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_LONG(env, stack, &long_vars[opcode->operand0], array, index, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_FLOAT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_FLOAT(env, stack, &float_vars[opcode->operand0], array, index, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_DOUBLE: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_DOUBLE(env, stack, &double_vars[opcode->operand0], array, index, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_OBJECT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_OBJECT(env, stack, &object_vars[opcode->operand0], array, index, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_BYTE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_BYTE(env, stack, array, index, byte_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_SHORT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_SHORT(env, stack, array, index, short_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_INT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_INT(env, stack, array, index, int_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_LONG: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_LONG(env, stack, array, index, long_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_FLOAT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_FLOAT(env, stack, array, index, float_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_DOUBLE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_DOUBLE(env, stack, array, index, double_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_OBJECT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_OBJECT(env, stack, array, index, object_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE(env, stack, array, index, object_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_UNDEF: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_UNDEF(env, stack, array, index, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LENGTH: {
        SPVM_IMPLEMENT_ARRAY_LENGTH(env, stack, &int_vars[opcode->operand0], object_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_LENGTH: {
        SPVM_IMPLEMENT_STRING_LENGTH(env, stack, &int_vars[opcode->operand0], object_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_LENGTH: {
        SPVM_IMPLEMENT_SET_LENGTH(env, stack, object_vars[opcode->operand0], int_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_CAPACITY: {
        SPVM_IMPLEMENT_CAPACITY(env, stack, &int_vars[opcode->operand0], object_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CAPACITY: {
        SPVM_IMPLEMENT_SET_CAPACITY(env, stack, object_vars[opcode->operand0], int_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_BYTE: {
        void* object = object_vars[opcode->operand1];
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        int32_t field_offset = field->offset;
        
        SPVM_IMPLEMENT_GET_FIELD_BYTE(env, stack, &byte_vars[opcode->operand0], object, field_offset, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_SHORT: {
        void* object = object_vars[opcode->operand1];
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        int32_t field_offset = field->offset;
        
        SPVM_IMPLEMENT_GET_FIELD_SHORT(env, stack, &short_vars[opcode->operand0], object, field_offset, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_INT: {
        void* object = object_vars[opcode->operand1];
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        int32_t field_offset = field->offset;
        
        SPVM_IMPLEMENT_GET_FIELD_INT(env, stack, &int_vars[opcode->operand0], object, field_offset, &error_id);
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_LONG: {
        void* object = object_vars[opcode->operand1];
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        int32_t field_offset = field->offset;
        
        SPVM_IMPLEMENT_GET_FIELD_LONG(env, stack, &long_vars[opcode->operand0], object, field_offset, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_FLOAT: {
        void* object = object_vars[opcode->operand1];
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        int32_t field_offset = field->offset;
        
        SPVM_IMPLEMENT_GET_FIELD_FLOAT(env, stack, &float_vars[opcode->operand0], object, field_offset, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE: {
        void* object = object_vars[opcode->operand1];
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        int32_t field_offset = field->offset;
        
        SPVM_IMPLEMENT_GET_FIELD_DOUBLE(env, stack, &double_vars[opcode->operand0], object, field_offset, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_OBJECT: {
        void* object = object_vars[opcode->operand1];
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        int32_t field_offset = field->offset;
        
        SPVM_IMPLEMENT_GET_FIELD_OBJECT(env, stack, &object_vars[opcode->operand0], object, field_offset, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_BYTE: {
        void* object = object_vars[opcode->operand0];
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        int32_t field_offset = field->offset;
        
        int32_t fields_exists_offset = field->exists_offset;
        int32_t fields_exists_bit = field->exists_bit;
        
        SPVM_IMPLEMENT_SET_FIELD_BYTE(env, stack, object, field_offset, byte_vars[opcode->operand1], &error_id, fields_exists_offset, fields_exists_bit);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_SHORT: {
        void* object = object_vars[opcode->operand0];
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        int32_t field_offset = field->offset;
        
        int32_t fields_exists_offset = field->exists_offset;
        int32_t fields_exists_bit = field->exists_bit;
        
        SPVM_IMPLEMENT_SET_FIELD_SHORT(env, stack, object, field_offset, short_vars[opcode->operand1], &error_id, fields_exists_offset, fields_exists_bit);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_INT: {
        void* object = object_vars[opcode->operand0];
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        int32_t field_offset = field->offset;
        
        int32_t fields_exists_offset = field->exists_offset;
        int32_t fields_exists_bit = field->exists_bit;
        
        SPVM_IMPLEMENT_SET_FIELD_INT(env, stack, object, field_offset, int_vars[opcode->operand1], &error_id, fields_exists_offset, fields_exists_bit);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_LONG: {
        void* object = object_vars[opcode->operand0];
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        int32_t field_offset = field->offset;
        
        int32_t fields_exists_offset = field->exists_offset;
        int32_t fields_exists_bit = field->exists_bit;
        
        SPVM_IMPLEMENT_SET_FIELD_LONG(env, stack, object, field_offset, long_vars[opcode->operand1], &error_id, fields_exists_offset, fields_exists_bit);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_FLOAT: {
        void* object = object_vars[opcode->operand0];
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        int32_t field_offset = field->offset;
        
        int32_t fields_exists_offset = field->exists_offset;
        int32_t fields_exists_bit = field->exists_bit;
        
        SPVM_IMPLEMENT_SET_FIELD_FLOAT(env, stack, object, field_offset, float_vars[opcode->operand1], &error_id, fields_exists_offset, fields_exists_bit);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE: {
        void* object = object_vars[opcode->operand0];
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        int32_t field_offset = field->offset;
        
        int32_t fields_exists_offset = field->exists_offset;
        int32_t fields_exists_bit = field->exists_bit;
        
        SPVM_IMPLEMENT_SET_FIELD_DOUBLE(env, stack, object, field_offset, double_vars[opcode->operand1], &error_id, fields_exists_offset, fields_exists_bit);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_OBJECT: {
        void* object = object_vars[opcode->operand0];
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        int32_t field_offset = field->offset;
        
        int32_t fields_exists_offset = field->exists_offset;
        int32_t fields_exists_bit = field->exists_bit;
        
        SPVM_IMPLEMENT_SET_FIELD_OBJECT(env, stack, object, field_offset, object_vars[opcode->operand1], &error_id, fields_exists_offset, fields_exists_bit);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_UNDEF: {
        void* object = object_vars[opcode->operand0];
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        int32_t field_offset = field->offset;
        
        int32_t fields_exists_offset = field->exists_offset;
        int32_t fields_exists_bit = field->exists_bit;
        
        SPVM_IMPLEMENT_SET_FIELD_UNDEF(env, stack, object, field_offset, &error_id, fields_exists_offset, fields_exists_bit);
        break;
      }
      case SPVM_OPCODE_C_ID_WEAKEN_FIELD: {
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        void* object = object_vars[opcode->operand0];
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        int32_t field_offset = field->offset;
        
        SPVM_IMPLEMENT_WEAKEN_FIELD(env, stack, object, field_offset, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_UNWEAKEN_FIELD: {
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        void* object = object_vars[opcode->operand0];
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        int32_t field_offset = field->offset;
        
        SPVM_IMPLEMENT_UNWEAKEN_FIELD(env, stack, object, field_offset, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_ISWEAK_FIELD: {
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        void* object = object_vars[opcode->operand1];
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        int32_t field_offset = field->offset;
        
        SPVM_IMPLEMENT_ISWEAK_FIELD(env, stack, &int_vars[opcode->operand0], object, field_offset, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_EXISTS: {
        
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        void* object = object_vars[opcode->operand1];
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        int32_t field_exists_offset = field->exists_offset;
        int32_t field_exists_bit = field->exists_bit;
        
        SPVM_IMPLEMENT_EXISTS(env, stack, &int_vars[opcode->operand0], object, field_exists_offset, field_exists_bit, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_DELETE: {
        int32_t field_current_basic_type_id = opcode->operand2;
        int32_t field_index = (uint16_t)opcode->operand3;
        void* object = object_vars[opcode->operand0];
        
        SPVM_RUNTIME_BASIC_TYPE* field_current_basic_type = runtime->basic_types[field_current_basic_type_id];
        SPVM_RUNTIME_FIELD* field = &field_current_basic_type->fields[field_index];
        
        SPVM_IMPLEMENT_DELETE(env, stack, object, field, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_BYTE: {
        int32_t class_var_current_basic_type_id = opcode->operand1;
        int32_t class_var_index = opcode->operand2;
        
        SPVM_RUNTIME_BASIC_TYPE* class_var_current_basic_type = runtime->basic_types[class_var_current_basic_type_id];
        SPVM_RUNTIME_CLASS_VAR* class_var = &class_var_current_basic_type->class_vars[class_var_index];
        
        SPVM_IMPLEMENT_GET_CLASS_VAR_BYTE(env, stack, byte_vars[opcode->operand0], class_var);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_SHORT: {
        int32_t class_var_current_basic_type_id = opcode->operand1;
        int32_t class_var_index = opcode->operand2;
        
        SPVM_RUNTIME_BASIC_TYPE* class_var_current_basic_type = runtime->basic_types[class_var_current_basic_type_id];
        SPVM_RUNTIME_CLASS_VAR* class_var = &class_var_current_basic_type->class_vars[class_var_index];
        
        SPVM_IMPLEMENT_GET_CLASS_VAR_SHORT(env, stack, short_vars[opcode->operand0], class_var);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_INT: {
        int32_t class_var_current_basic_type_id = opcode->operand1;
        int32_t class_var_index = opcode->operand2;
        
        SPVM_RUNTIME_BASIC_TYPE* class_var_current_basic_type = runtime->basic_types[class_var_current_basic_type_id];
        SPVM_RUNTIME_CLASS_VAR* class_var = &class_var_current_basic_type->class_vars[class_var_index];
        
        SPVM_IMPLEMENT_GET_CLASS_VAR_INT(env, stack, int_vars[opcode->operand0], class_var);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_LONG: {
        int32_t class_var_current_basic_type_id = opcode->operand1;
        int32_t class_var_index = opcode->operand2;
        
        SPVM_RUNTIME_BASIC_TYPE* class_var_current_basic_type = runtime->basic_types[class_var_current_basic_type_id];
        SPVM_RUNTIME_CLASS_VAR* class_var = &class_var_current_basic_type->class_vars[class_var_index];
        
        SPVM_IMPLEMENT_GET_CLASS_VAR_LONG(env, stack, long_vars[opcode->operand0], class_var);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_FLOAT: {
        int32_t class_var_current_basic_type_id = opcode->operand1;
        int32_t class_var_index = opcode->operand2;
        
        SPVM_RUNTIME_BASIC_TYPE* class_var_current_basic_type = runtime->basic_types[class_var_current_basic_type_id];
        SPVM_RUNTIME_CLASS_VAR* class_var = &class_var_current_basic_type->class_vars[class_var_index];
        
        SPVM_IMPLEMENT_GET_CLASS_VAR_FLOAT(env, stack, float_vars[opcode->operand0], class_var);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_DOUBLE: {
        int32_t class_var_current_basic_type_id = opcode->operand1;
        int32_t class_var_index = opcode->operand2;
        
        SPVM_RUNTIME_BASIC_TYPE* class_var_current_basic_type = runtime->basic_types[class_var_current_basic_type_id];
        SPVM_RUNTIME_CLASS_VAR* class_var = &class_var_current_basic_type->class_vars[class_var_index];
        
        SPVM_IMPLEMENT_GET_CLASS_VAR_DOUBLE(env, stack, double_vars[opcode->operand0], class_var);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_OBJECT: {
        int32_t class_var_current_basic_type_id = opcode->operand1;
        int32_t class_var_index = opcode->operand2;
        
        SPVM_RUNTIME_BASIC_TYPE* class_var_current_basic_type = runtime->basic_types[class_var_current_basic_type_id];
        SPVM_RUNTIME_CLASS_VAR* class_var = &class_var_current_basic_type->class_vars[class_var_index];
        
        SPVM_IMPLEMENT_GET_CLASS_VAR_OBJECT(env, stack, &object_vars[opcode->operand0], class_var);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_BYTE: {
        int32_t class_var_current_basic_type_id = opcode->operand0;
        int32_t class_var_index = opcode->operand1;
        
        SPVM_RUNTIME_BASIC_TYPE* class_var_current_basic_type = runtime->basic_types[class_var_current_basic_type_id];
        SPVM_RUNTIME_CLASS_VAR* class_var = &class_var_current_basic_type->class_vars[class_var_index];
        
        SPVM_IMPLEMENT_SET_CLASS_VAR_BYTE(env, stack, class_var, byte_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_SHORT: {
        int32_t class_var_current_basic_type_id = opcode->operand0;
        int32_t class_var_index = opcode->operand1;
        
        SPVM_RUNTIME_BASIC_TYPE* class_var_current_basic_type = runtime->basic_types[class_var_current_basic_type_id];
        SPVM_RUNTIME_CLASS_VAR* class_var = &class_var_current_basic_type->class_vars[class_var_index];
        
        SPVM_IMPLEMENT_SET_CLASS_VAR_SHORT(env, stack, class_var, short_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_INT: {
        int32_t class_var_current_basic_type_id = opcode->operand0;
        int32_t class_var_index = opcode->operand1;
        
        SPVM_RUNTIME_BASIC_TYPE* class_var_current_basic_type = runtime->basic_types[class_var_current_basic_type_id];
        SPVM_RUNTIME_CLASS_VAR* class_var = &class_var_current_basic_type->class_vars[class_var_index];
        
        SPVM_IMPLEMENT_SET_CLASS_VAR_INT(env, stack, class_var, int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_LONG: {
        int32_t class_var_current_basic_type_id = opcode->operand0;
        int32_t class_var_index = opcode->operand1;
        
        SPVM_RUNTIME_BASIC_TYPE* class_var_current_basic_type = runtime->basic_types[class_var_current_basic_type_id];
        SPVM_RUNTIME_CLASS_VAR* class_var = &class_var_current_basic_type->class_vars[class_var_index];
        
        SPVM_IMPLEMENT_SET_CLASS_VAR_LONG(env, stack, class_var, long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_FLOAT: {
        int32_t class_var_current_basic_type_id = opcode->operand0;
        int32_t class_var_index = opcode->operand1;
        
        SPVM_RUNTIME_BASIC_TYPE* class_var_current_basic_type = runtime->basic_types[class_var_current_basic_type_id];
        SPVM_RUNTIME_CLASS_VAR* class_var = &class_var_current_basic_type->class_vars[class_var_index];
        
        SPVM_IMPLEMENT_SET_CLASS_VAR_FLOAT(env, stack, class_var, float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_DOUBLE: {
        int32_t class_var_current_basic_type_id = opcode->operand0;
        int32_t class_var_index = opcode->operand1;
        
        SPVM_RUNTIME_BASIC_TYPE* class_var_current_basic_type = runtime->basic_types[class_var_current_basic_type_id];
        SPVM_RUNTIME_CLASS_VAR* class_var = &class_var_current_basic_type->class_vars[class_var_index];
        
        SPVM_IMPLEMENT_SET_CLASS_VAR_DOUBLE(env, stack, class_var, double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_OBJECT: {
        int32_t class_var_current_basic_type_id = opcode->operand0;
        int32_t class_var_index = opcode->operand1;
        
        SPVM_RUNTIME_BASIC_TYPE* class_var_current_basic_type = runtime->basic_types[class_var_current_basic_type_id];
        SPVM_RUNTIME_CLASS_VAR* class_var = &class_var_current_basic_type->class_vars[class_var_index];
        
        SPVM_IMPLEMENT_SET_CLASS_VAR_OBJECT(env, stack, class_var, object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_UNDEF: {
        int32_t class_var_current_basic_type_id = opcode->operand0;
        int32_t class_var_index = opcode->operand1;
        
        SPVM_RUNTIME_BASIC_TYPE* class_var_current_basic_type = runtime->basic_types[class_var_current_basic_type_id];
        SPVM_RUNTIME_CLASS_VAR* class_var = &class_var_current_basic_type->class_vars[class_var_index];
        
        SPVM_IMPLEMENT_SET_CLASS_VAR_UNDEF(env, stack, class_var);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_EXCEPTION_VAR: {
        SPVM_IMPLEMENT_GET_EXCEPTION_VAR(env, stack, &object_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR: {
        SPVM_IMPLEMENT_SET_EXCEPTION_VAR(env, stack, object_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR_UNDEF: {
        SPVM_IMPLEMENT_SET_EXCEPTION_VAR_UNDEF(env, stack);
        break;
      }
      case SPVM_OPCODE_C_ID_ISA: {
        void* object = object_vars[opcode->operand1];
        int32_t basic_type_id = opcode->operand2;
        int32_t type_dimension = opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* basic_type = runtime->basic_types[basic_type_id];
        
        SPVM_IMPLEMENT_ISA(env, stack, &int_vars[opcode->operand0], object, basic_type, type_dimension);
        break;
      }
      case SPVM_OPCODE_C_ID_ISA_ERROR: {
        int32_t src_basic_type_id = int_vars[opcode->operand1];
        int32_t basic_type_id = opcode->operand2;
        int32_t type_dimension = opcode->operand3;
        
        void* src_basic_type = runtime->basic_types[src_basic_type_id];
        
        SPVM_RUNTIME_BASIC_TYPE* basic_type = runtime->basic_types[basic_type_id];
        
        SPVM_IMPLEMENT_ISA_ERROR(env, stack, &int_vars[opcode->operand0], src_basic_type, basic_type, type_dimension);
        break;
      }
      case SPVM_OPCODE_C_ID_IS_TYPE: {
        void* object = object_vars[opcode->operand1];
        int32_t basic_type_id = opcode->operand2;
        int32_t type_dimension = opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* basic_type = runtime->basic_types[basic_type_id];
        
        SPVM_IMPLEMENT_IS_TYPE(env, stack, &int_vars[opcode->operand0], object, basic_type, type_dimension);
        break;
      }
      case SPVM_OPCODE_C_ID_IS_ERROR: {
        int32_t src_basic_type_id = int_vars[opcode->operand1];
        int32_t basic_type_id = opcode->operand2;
        int32_t type_dimension = opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* basic_type = runtime->basic_types[basic_type_id];
        
        void* src_basic_type = runtime->basic_types[src_basic_type_id];
        
        SPVM_IMPLEMENT_IS_ERROR(env, stack, &int_vars[opcode->operand0], src_basic_type, basic_type, type_dimension);
        break;
      }
      case SPVM_OPCODE_C_ID_CAN: {
        void* object = object_vars[opcode->operand1];
        
        int32_t can_method_name_constant_string_index = opcode->operand2;
        SPVM_RUNTIME_STRING* can_method_name_constant_string = &current_basic_type->constant_strings[can_method_name_constant_string_index];
        const char* can_method_name = can_method_name_constant_string->value;
        
        SPVM_IMPLEMENT_CAN(env, stack, int_vars[opcode->operand0], object, can_method_name);
        break;
      }
      case SPVM_OPCODE_C_ID_PRINT: {
        void* string = object_vars[opcode->operand0];
        SPVM_IMPLEMENT_PRINT(env, stack, string, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_SAY: {
        void* string = object_vars[opcode->operand0];
        SPVM_IMPLEMENT_SAY(env, stack, string, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_WARN: {
        void* string = object_vars[opcode->operand0];
        int32_t line = opcode->operand1;
        
        const char* basic_type_name = current_basic_type->name;
        
        const char* method_name = current_method->name;
        
        const char* file = current_basic_type->file;
        
        SPVM_IMPLEMENT_WARN(env, stack, string, basic_type_name, method_name, file, line);
        
        break;
      }
      case SPVM_OPCODE_C_ID_CLEAR_EVAL_ERROR_ID: {
        SPVM_IMPLEMENT_CLEAR_EVAL_ERROR_ID(eval_error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_EVAL_ERROR_ID: {
        SPVM_IMPLEMENT_GET_EVAL_ERROR_ID(int_vars[opcode->operand0], eval_error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ERROR_ID_BY_TYPE: {
        int32_t basic_type_id = opcode->operand0;
        
        SPVM_IMPLEMENT_SET_ERROR_ID(error_id, basic_type_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ERROR_ID: {
        int32_t basic_type_id = int_vars[opcode->operand0];
        
        SPVM_IMPLEMENT_SET_ERROR_ID(error_id, basic_type_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_BASIC_TYPE_ID: {
        int32_t basic_type_id = opcode->operand1;
        
        SPVM_RUNTIME_BASIC_TYPE* basic_type = runtime->basic_types[basic_type_id];
        
        SPVM_IMPLEMENT_GET_BASIC_TYPE_ID(env, stack, int_vars[opcode->operand0], basic_type);
        
        break;
      }
      case SPVM_OPCODE_C_ID_ARGS_WIDTH: {
        SPVM_IMPLEMENT_ARGS_WIDTH(env, stack, int_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_NAME: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_NAME(env, stack, &object_vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_DUMP: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_DUMP(env, stack, &object_vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_COPY: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_COPY(env, stack, &object_vars[opcode->operand0], object, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_REF_BYTE: {
        SPVM_IMPLEMENT_REF_BYTE(ref_vars[opcode->operand0], &byte_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_REF_SHORT: {
        SPVM_IMPLEMENT_REF_SHORT(ref_vars[opcode->operand0], &short_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_REF_INT: {
        SPVM_IMPLEMENT_REF_INT(ref_vars[opcode->operand0], &int_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_REF_LONG: {
        SPVM_IMPLEMENT_REF_LONG(ref_vars[opcode->operand0], &long_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_REF_FLOAT: {
        SPVM_IMPLEMENT_REF_FLOAT(ref_vars[opcode->operand0], &float_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_REF_DOUBLE: {
        SPVM_IMPLEMENT_REF_DOUBLE(ref_vars[opcode->operand0], &double_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_BYTE: {
        SPVM_IMPLEMENT_GET_DEREF_BYTE(env, stack, &byte_vars[opcode->operand0], &ref_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_SHORT: {
        SPVM_IMPLEMENT_GET_DEREF_SHORT(env, stack, &short_vars[opcode->operand0], &ref_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_INT: {
        SPVM_IMPLEMENT_GET_DEREF_INT(env, stack, &int_vars[opcode->operand0], &ref_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_LONG: {
        SPVM_IMPLEMENT_GET_DEREF_LONG(env, stack, &long_vars[opcode->operand0], &ref_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_FLOAT: {
        SPVM_IMPLEMENT_GET_DEREF_FLOAT(env, stack, &float_vars[opcode->operand0], &ref_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_DOUBLE: {
        SPVM_IMPLEMENT_GET_DEREF_DOUBLE(env, stack, &double_vars[opcode->operand0], &ref_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_BYTE: {
        SPVM_IMPLEMENT_SET_DEREF_BYTE(env, stack, &ref_vars[opcode->operand0], byte_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_SHORT: {
        SPVM_IMPLEMENT_SET_DEREF_SHORT(env, stack, &ref_vars[opcode->operand0], short_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_INT: {
        SPVM_IMPLEMENT_SET_DEREF_INT(env, stack, &ref_vars[opcode->operand0], int_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_LONG: {
        SPVM_IMPLEMENT_SET_DEREF_LONG(env, stack, &ref_vars[opcode->operand0], long_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_FLOAT: {
        SPVM_IMPLEMENT_SET_DEREF_FLOAT(env, stack, &ref_vars[opcode->operand0], float_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_DOUBLE: {
        SPVM_IMPLEMENT_SET_DEREF_DOUBLE(env, stack, &ref_vars[opcode->operand0], double_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_GET_MULNUM_FIELD_BYTE(byte_vars[opcode->operand0], &byte_vars[opcode->operand1], field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_GET_MULNUM_FIELD_SHORT(short_vars[opcode->operand0], &short_vars[opcode->operand1], field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_GET_MULNUM_FIELD_INT(int_vars[opcode->operand0], &int_vars[opcode->operand1], field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_GET_MULNUM_FIELD_LONG(long_vars[opcode->operand0], &long_vars[opcode->operand1], field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_GET_MULNUM_FIELD_FLOAT(float_vars[opcode->operand0], &float_vars[opcode->operand1], field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_GET_MULNUM_FIELD_DOUBLE(double_vars[opcode->operand0], &double_vars[opcode->operand1], field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_SET_MULNUM_FIELD_BYTE(&byte_vars[opcode->operand0], field_index, byte_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_SET_MULNUM_FIELD_SHORT(&short_vars[opcode->operand0], field_index, short_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_SET_MULNUM_FIELD_INT(&int_vars[opcode->operand0], field_index, int_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_SET_MULNUM_FIELD_LONG(&long_vars[opcode->operand0], field_index, long_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_SET_MULNUM_FIELD_FLOAT(&float_vars[opcode->operand0], field_index, float_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_SET_MULNUM_FIELD_DOUBLE(&double_vars[opcode->operand0], field_index, double_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_BYTE: {
        int32_t fields_length = opcode->operand2;
        SPVM_IMPLEMENT_MOVE_MULNUM_BYTE(env, stack, &byte_vars[opcode->operand0], &byte_vars[opcode->operand1], fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_SHORT: {
        int32_t fields_length = opcode->operand2;
        SPVM_IMPLEMENT_MOVE_MULNUM_SHORT(env, stack, &short_vars[opcode->operand0], &short_vars[opcode->operand1], fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_INT: {
        int32_t fields_length = opcode->operand2;
        SPVM_IMPLEMENT_MOVE_MULNUM_INT(env, stack, &int_vars[opcode->operand0], &int_vars[opcode->operand1], fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_LONG: {
        int32_t fields_length = opcode->operand2;
        SPVM_IMPLEMENT_MOVE_MULNUM_LONG(env, stack, &long_vars[opcode->operand0], &long_vars[opcode->operand1], fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_FLOAT: {
        int32_t fields_length = opcode->operand2;
        SPVM_IMPLEMENT_MOVE_MULNUM_FLOAT(env, stack, &float_vars[opcode->operand0], &float_vars[opcode->operand1], fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_DOUBLE: {
        int32_t fields_length = opcode->operand2;
        SPVM_IMPLEMENT_MOVE_MULNUM_DOUBLE(env, stack, &double_vars[opcode->operand0], &double_vars[opcode->operand1], fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_BYTE: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_BYTE(env, stack, &byte_vars[opcode->operand0], array, index, fields_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_SHORT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_SHORT(env, stack, &short_vars[opcode->operand0], array, index, fields_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_INT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_INT(env, stack, &int_vars[opcode->operand0], array, index, fields_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_LONG: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_LONG(env, stack, &long_vars[opcode->operand0], array, index, fields_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FLOAT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FLOAT(env, stack, &float_vars[opcode->operand0], array, index, fields_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_DOUBLE: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_DOUBLE(env, stack, &double_vars[opcode->operand0], array, index, fields_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_BYTE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_BYTE(env, stack, array, index, fields_length, &byte_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_SHORT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_SHORT(env, stack, array, index, fields_length, &short_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_INT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_INT(env, stack, array, index, fields_length, &int_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_LONG: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_LONG(env, stack, array, index, fields_length, &long_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FLOAT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FLOAT(env, stack, array, index, fields_length, &float_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_DOUBLE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_DOUBLE(env, stack, array, index, fields_length, &double_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_BYTE: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_BYTE(env, stack, &byte_vars[opcode->operand0], array, index, field_index, fields_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_SHORT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_SHORT(env, stack, &short_vars[opcode->operand0], array, index, field_index, fields_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_INT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_INT(env, stack, &int_vars[opcode->operand0], array, index, field_index, fields_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_LONG: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_LONG(env, stack, &long_vars[opcode->operand0], array, index, field_index, fields_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_FLOAT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_FLOAT(env, stack, &float_vars[opcode->operand0], array, index, field_index, fields_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_DOUBLE: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_DOUBLE(env, stack, &double_vars[opcode->operand0], array, index, field_index, fields_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_BYTE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_BYTE(env, stack, array, index, field_index, fields_length, byte_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_SHORT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_SHORT(env, stack, array, index, field_index, fields_length, short_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_INT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_INT(env, stack, array, index, field_index, fields_length, int_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_LONG: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_LONG(env, stack, array, index, field_index, fields_length, long_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_FLOAT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_FLOAT(env, stack, array, index, field_index, fields_length, float_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_DOUBLE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_DOUBLE(env, stack, array, index, field_index, fields_length, double_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_BYTE: {
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_DEREF_MULNUM_BYTE(env, stack, &byte_vars[opcode->operand0], ref_vars[opcode->operand1], fields_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_SHORT: {
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_DEREF_MULNUM_SHORT(env, stack, &short_vars[opcode->operand0], ref_vars[opcode->operand1], fields_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_INT: {
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_DEREF_MULNUM_INT(env, stack, &int_vars[opcode->operand0], ref_vars[opcode->operand1], fields_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_LONG: {
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_DEREF_MULNUM_LONG(env, stack, &long_vars[opcode->operand0], ref_vars[opcode->operand1], fields_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_FLOAT: {
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_DEREF_MULNUM_FLOAT(env, stack, &float_vars[opcode->operand0], ref_vars[opcode->operand1], fields_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_DOUBLE: {
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_DEREF_MULNUM_DOUBLE(env, stack, &double_vars[opcode->operand0], ref_vars[opcode->operand1], fields_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_BYTE(env, stack, &byte_vars[opcode->operand0], ref_vars[opcode->operand1], field_index, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_SHORT(env, stack, &short_vars[opcode->operand0], ref_vars[opcode->operand1], field_index, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_INT(env, stack, &int_vars[opcode->operand0], ref_vars[opcode->operand1], field_index, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_LONG(env, stack, &long_vars[opcode->operand0], ref_vars[opcode->operand1], field_index, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_FLOAT(env, stack, &float_vars[opcode->operand0], ref_vars[opcode->operand1], field_index, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_DOUBLE(env, stack, &double_vars[opcode->operand0], ref_vars[opcode->operand1], field_index, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_BYTE(env, stack, ref_vars[opcode->operand0], field_index, byte_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_SHORT(env, stack, ref_vars[opcode->operand0], field_index, short_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_INT(env, stack, ref_vars[opcode->operand0], field_index, int_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_LONG(env, stack, ref_vars[opcode->operand0], field_index, long_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_FLOAT(env, stack, ref_vars[opcode->operand0], field_index, float_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_DOUBLE(env, stack, ref_vars[opcode->operand0], field_index, double_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_SHORT: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_SHORT(short_vars[opcode->operand0], byte_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_INT: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_INT(int_vars[opcode->operand0], byte_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_LONG: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_LONG(long_vars[opcode->operand0], byte_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_FLOAT: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_FLOAT(float_vars[opcode->operand0], byte_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_DOUBLE: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_DOUBLE(double_vars[opcode->operand0], byte_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_BYTE: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_BYTE(byte_vars[opcode->operand0], short_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_INT: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_INT(int_vars[opcode->operand0], short_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_LONG: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_LONG(long_vars[opcode->operand0], short_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_FLOAT: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_FLOAT(float_vars[opcode->operand0], short_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_DOUBLE: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_DOUBLE(double_vars[opcode->operand0], short_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_BYTE: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_BYTE(byte_vars[opcode->operand0], int_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_SHORT: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_SHORT(short_vars[opcode->operand0], int_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_LONG: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_LONG(long_vars[opcode->operand0], int_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_FLOAT: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_FLOAT(float_vars[opcode->operand0], int_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_DOUBLE: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_DOUBLE(double_vars[opcode->operand0], int_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_BYTE: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_BYTE(byte_vars[opcode->operand0], long_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_SHORT: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_SHORT(short_vars[opcode->operand0], long_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_INT: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_INT(int_vars[opcode->operand0], long_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_FLOAT: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_FLOAT(float_vars[opcode->operand0], long_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_DOUBLE: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_DOUBLE(double_vars[opcode->operand0], long_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_BYTE: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_BYTE(byte_vars[opcode->operand0], float_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_SHORT: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_SHORT(short_vars[opcode->operand0], float_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_INT: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_INT(int_vars[opcode->operand0], float_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_LONG: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_LONG(long_vars[opcode->operand0], float_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_DOUBLE: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_DOUBLE(double_vars[opcode->operand0], float_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_BYTE: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_BYTE(byte_vars[opcode->operand0], double_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_SHORT: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_SHORT(short_vars[opcode->operand0], double_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_INT: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_INT(int_vars[opcode->operand0], double_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_LONG: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_LONG(long_vars[opcode->operand0], double_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_FLOAT: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_FLOAT(float_vars[opcode->operand0], double_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_STRING: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_STRING(env, stack, &object_vars[opcode->operand0], byte_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_STRING: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_STRING(env, stack, &object_vars[opcode->operand0], short_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_STRING: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_STRING(env, stack, &object_vars[opcode->operand0], int_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_STRING: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_STRING(env, stack, &object_vars[opcode->operand0], long_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_STRING: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_STRING(env, stack, &object_vars[opcode->operand0], float_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_STRING: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_STRING(env, stack, &object_vars[opcode->operand0], double_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_STRING_TO_BYTE: {
        void* src_string = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_BYTE(env, stack, &byte_vars[opcode->operand0], src_string);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_STRING_TO_SHORT: {
        void* src_string = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_SHORT(env, stack, &short_vars[opcode->operand0], src_string);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_STRING_TO_INT: {
        void* src_string = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_INT(env, stack, &int_vars[opcode->operand0], src_string);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_STRING_TO_LONG: {
        void* src_string = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_LONG(env, stack, &long_vars[opcode->operand0], src_string);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_STRING_TO_FLOAT: {
        void* src_string = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_FLOAT(env, stack, &float_vars[opcode->operand0], src_string);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_STRING_TO_DOUBLE: {
        void* src_string = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_DOUBLE(env, stack, &double_vars[opcode->operand0], src_string);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_STRING_TO_BYTE_ARRAY: {
        void* src_string = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_BYTE_ARRAY(env, stack, &object_vars[opcode->operand0], src_string);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_ARRAY_TO_STRING: {
        void* src_byte_array = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_ARRAY_TO_STRING(env, stack, &object_vars[opcode->operand0], src_byte_array);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_BYTE_OBJECT: {
        int8_t value = byte_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_BYTE_OBJECT(env, stack, &object_vars[opcode->operand0], value);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_SHORT_OBJECT: {
        int16_t value = short_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_SHORT_OBJECT(env, stack, &object_vars[opcode->operand0], value);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_INT_OBJECT: {
        int32_t value = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_INT_OBJECT(env, stack, &object_vars[opcode->operand0], value);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_LONG_OBJECT: {
        int64_t value = long_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_LONG_OBJECT(env, stack, &object_vars[opcode->operand0], value);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_FLOAT_OBJECT: {
        float value = float_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_FLOAT_OBJECT(env, stack, &object_vars[opcode->operand0], value);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_DOUBLE_OBJECT: {
        double value = double_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_DOUBLE_OBJECT(env, stack, &object_vars[opcode->operand0], value);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_ANY_OBJECT_TO_BYTE: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_ANY_OBJECT_TO_BYTE(env, stack, &byte_vars[opcode->operand0], object, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_ANY_OBJECT_TO_SHORT: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_ANY_OBJECT_TO_SHORT(env, stack, &short_vars[opcode->operand0], object, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_ANY_OBJECT_TO_INT: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_ANY_OBJECT_TO_INT(env, stack, &int_vars[opcode->operand0], object, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_ANY_OBJECT_TO_LONG: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_ANY_OBJECT_TO_LONG(env, stack, &long_vars[opcode->operand0], object, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_ANY_OBJECT_TO_FLOAT: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_ANY_OBJECT_TO_FLOAT(env, stack, &float_vars[opcode->operand0], object, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_ANY_OBJECT_TO_DOUBLE: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_ANY_OBJECT_TO_DOUBLE(env, stack, &double_vars[opcode->operand0], object, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_BYTE: {
        SPVM_IMPLEMENT_GET_STACK_BYTE(byte_vars[opcode->operand0], stack, opcode->operand3 & 0xFF);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_SHORT: {
        SPVM_IMPLEMENT_GET_STACK_SHORT(short_vars[opcode->operand0], stack, opcode->operand3 & 0xFF);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_INT: {
        SPVM_IMPLEMENT_GET_STACK_INT(int_vars[opcode->operand0], stack, opcode->operand3 & 0xFF);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_LONG: {
        SPVM_IMPLEMENT_GET_STACK_LONG(long_vars[opcode->operand0], stack, opcode->operand3 & 0xFF);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_FLOAT: {
       SPVM_IMPLEMENT_GET_STACK_FLOAT(float_vars[opcode->operand0], stack, opcode->operand3 & 0xFF);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_DOUBLE: {
        SPVM_IMPLEMENT_GET_STACK_DOUBLE(double_vars[opcode->operand0], stack, opcode->operand3 & 0xFF);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_OBJECT: {
        SPVM_IMPLEMENT_GET_STACK_OBJECT(env, &object_vars[opcode->operand0], stack, opcode->operand3 & 0xFF);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_REF: {
        SPVM_IMPLEMENT_GET_STACK_REF(ref_vars[opcode->operand0], stack, opcode->operand3 & 0xFF);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_MULNUM_BYTE: {
        int32_t args_width = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_STACK_MULNUM_BYTE(env, &byte_vars[opcode->operand0], stack, opcode->operand3 & 0xFF, args_width);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_MULNUM_SHORT: {
        int32_t args_width = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_STACK_MULNUM_SHORT(env, &short_vars[opcode->operand0], stack, opcode->operand3 & 0xFF, args_width);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_MULNUM_INT: {
        int32_t args_width = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_STACK_MULNUM_INT(env, &int_vars[opcode->operand0], stack, opcode->operand3 & 0xFF, args_width);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_MULNUM_LONG: {
        int32_t args_width = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_STACK_MULNUM_LONG(env, &long_vars[opcode->operand0], stack, opcode->operand3 & 0xFF, args_width);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_MULNUM_FLOAT: {
        int32_t args_width = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_STACK_MULNUM_FLOAT(env, &float_vars[opcode->operand0], stack, opcode->operand3 & 0xFF, args_width);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_MULNUM_DOUBLE: {
        int32_t args_width = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_STACK_MULNUM_DOUBLE(env, &double_vars[opcode->operand0], stack, opcode->operand3 & 0xFF, args_width);
        break;
      }
      case SPVM_OPCODE_C_ID_END_ARGS: {
        // Do nothing
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_BYTE: {
        SPVM_IMPLEMENT_SET_STACK_BYTE(stack, opcode->operand3, byte_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_SHORT: {
        SPVM_IMPLEMENT_SET_STACK_SHORT(stack, opcode->operand3, short_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_INT: {
        SPVM_IMPLEMENT_SET_STACK_INT(stack, opcode->operand3, int_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_LONG: {
        SPVM_IMPLEMENT_SET_STACK_LONG(stack, opcode->operand3, long_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_FLOAT: {
        SPVM_IMPLEMENT_SET_STACK_FLOAT(stack, opcode->operand3, float_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_DOUBLE: {
        SPVM_IMPLEMENT_SET_STACK_DOUBLE(stack, opcode->operand3, double_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_OBJECT: {
        SPVM_IMPLEMENT_SET_STACK_OBJECT(stack, opcode->operand3, object_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_REF: {
        SPVM_IMPLEMENT_SET_STACK_REF(stack, opcode->operand3, ref_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_UNDEF: {
        SPVM_IMPLEMENT_SET_STACK_UNDEF(stack, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_MULNUM_BYTE: {
        int32_t fields_length = opcode->operand1;
        SPVM_IMPLEMENT_SET_STACK_MULNUM_BYTE(env, stack, opcode->operand3, fields_length, &byte_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_MULNUM_SHORT: {
        int32_t fields_length = opcode->operand1;
        SPVM_IMPLEMENT_SET_STACK_MULNUM_SHORT(env, stack, opcode->operand3, fields_length, &short_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_MULNUM_INT: {
        int32_t fields_length = opcode->operand1;
        SPVM_IMPLEMENT_SET_STACK_MULNUM_INT(env, stack, opcode->operand3, fields_length, &int_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_MULNUM_LONG: {
        int32_t fields_length = opcode->operand1;
        SPVM_IMPLEMENT_SET_STACK_MULNUM_LONG(env, stack, opcode->operand3, fields_length, &long_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_MULNUM_FLOAT: {
        int32_t fields_length = opcode->operand1;
        SPVM_IMPLEMENT_SET_STACK_MULNUM_FLOAT(env, stack, opcode->operand3, fields_length, &float_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_MULNUM_DOUBLE: {
        int32_t fields_length = opcode->operand1;
        SPVM_IMPLEMENT_SET_STACK_MULNUM_DOUBLE(env, stack, opcode->operand3, fields_length, &double_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_VOID: {
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_BYTE: {
        SPVM_IMPLEMENT_RETURN_BYTE(stack, byte_vars[opcode->operand0]);
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_SHORT: {
        SPVM_IMPLEMENT_RETURN_SHORT(stack, short_vars[opcode->operand0]);
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_INT: {
        SPVM_IMPLEMENT_RETURN_INT(stack, int_vars[opcode->operand0]);
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_LONG: {
        SPVM_IMPLEMENT_RETURN_LONG(stack, long_vars[opcode->operand0]);
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_FLOAT: {
        SPVM_IMPLEMENT_RETURN_FLOAT(stack, float_vars[opcode->operand0]);
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_DOUBLE: {
        SPVM_IMPLEMENT_RETURN_DOUBLE(stack, double_vars[opcode->operand0]);
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_OBJECT: {
        SPVM_IMPLEMENT_RETURN_OBJECT(env, stack, object_vars[opcode->operand0]);
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_UNDEF: {
        SPVM_IMPLEMENT_RETURN_UNDEF(stack);
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_BYTE: {
        int32_t fields_length = opcode->operand2;
        SPVM_IMPLEMENT_RETURN_MULNUM_BYTE(env, stack, &byte_vars[opcode->operand0], fields_length);
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_SHORT: {
        int32_t fields_length = opcode->operand2;
        SPVM_IMPLEMENT_RETURN_MULNUM_SHORT(env, stack, &short_vars[opcode->operand0], fields_length);
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_INT: {
        int32_t fields_length = opcode->operand2;
        SPVM_IMPLEMENT_RETURN_MULNUM_INT(env, stack, &int_vars[opcode->operand0], fields_length);
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_LONG: {
        int32_t fields_length = opcode->operand2;
        SPVM_IMPLEMENT_RETURN_MULNUM_LONG(env, stack, &long_vars[opcode->operand0], fields_length);
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_FLOAT: {
        int32_t fields_length = opcode->operand2;
        SPVM_IMPLEMENT_RETURN_MULNUM_FLOAT(env, stack, &float_vars[opcode->operand0], fields_length);
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_DOUBLE: {
        int32_t fields_length = opcode->operand2;
        SPVM_IMPLEMENT_RETURN_MULNUM_DOUBLE(env, stack, &double_vars[opcode->operand0], fields_length);
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_CALL_CLASS_METHOD: {
        int32_t invocant_decl_basic_type_id = opcode->operand0;
        int32_t decl_method_index = opcode->operand1;
        int32_t args_width = opcode->operand2;
        int32_t line = opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* invocant_decl_basic_type = runtime->basic_types[invocant_decl_basic_type_id];
        
        SPVM_RUNTIME_METHOD* method = &invocant_decl_basic_type->methods[decl_method_index];
        
        SPVM_IMPLEMENT_CALL_CLASS_METHOD(env, stack, error_id, method, args_width, env->api->method->get_name(env->runtime, method), NULL, line); // TODO: abs_name, file
        
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD_STATIC: {
        int32_t invocant_decl_basic_type_id = opcode->operand0;
        int32_t decl_method_index = opcode->operand1;
        int32_t args_width = opcode->operand2;
        int32_t line = opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* invocant_decl_basic_type = runtime->basic_types[invocant_decl_basic_type_id];
        
        SPVM_RUNTIME_METHOD* method = &invocant_decl_basic_type->methods[decl_method_index];
        
        SPVM_IMPLEMENT_CALL_INSTANCE_METHOD_STATIC(env, stack, error_id, method, args_width, env->api->method->get_name(env->runtime, method), NULL, line); // TODO: abs_name, file
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD: {
        int32_t invocant_decl_basic_type_id = opcode->operand0;
        int32_t decl_method_index = opcode->operand1;
        int32_t args_width = opcode->operand2;
        int32_t line = opcode->operand3;
        
        SPVM_RUNTIME_BASIC_TYPE* invocant_decl_basic_type = runtime->basic_types[invocant_decl_basic_type_id];
        
        SPVM_RUNTIME_METHOD* decl_method = &invocant_decl_basic_type->methods[decl_method_index];
        
        const char* method_name = decl_method->name;
        
        SPVM_IMPLEMENT_CALL_INSTANCE_METHOD(env, stack, error_id, method_name, args_width, decl_method->args_signature, method_name, NULL, line); // TODO: abs_name, file
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ADDRESS_OBJECT: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_GET_ADDRESS(env, stack, &object_vars[opcode->operand0], object);
        break;
      }
      
      case SPVM_OPCODE_C_ID_GET_ADDRESS_REF: {
        void* ref = ref_vars[opcode->operand1];
        SPVM_IMPLEMENT_GET_ADDRESS(env, stack, &object_vars[opcode->operand0], ref);
        break;
      }
    }
    opcode_rel_index++;
  }
  
  END_OF_FUNC: {
    
    if (__builtin_expect(error_id == 0, 1)) {
      SPVM_RUNTIME_BASIC_TYPE* current_method_return_basic_type = current_method->return_basic_type;
      int32_t current_method_return_type_dimension = current_method->return_type_dimension;
      int32_t current_method_return_type_flag =current_method->return_type_flag;
      int32_t method_return_type_is_object = SPVM_TYPE_is_object_type(runtime->compiler, current_method_return_basic_type->id, current_method_return_type_dimension, current_method_return_type_flag);
      if (method_return_type_is_object) {
        if (*(void**)&stack[0] != NULL) {
          SPVM_API_dec_ref_count(env, stack, *(void**)&stack[0]);
        }
      }
    }
    
    if (__builtin_expect(status_push_call_stack_frame == 0, 1)) {
      SPVM_API_pop_call_stack_frame(env, stack, call_stack_frame_info);
    }
    
    return error_id;
  }
}

