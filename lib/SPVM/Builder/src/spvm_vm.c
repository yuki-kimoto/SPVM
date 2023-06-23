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
#include "spvm_runtime_constant_string.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_class_var.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_method.h"

#include "spvm_api_string_buffer.h"
#include "spvm_api_allocator.h"
#include "spvm_api_runtime.h"

#include "spvm_implement.h"

static const char* FILE_NAME = "spvm_vm.c";

int32_t SPVM_VM_call_method(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* current_method, int32_t args_stack_length) {
  
  // Opcode relative index
  register int32_t opcode_rel_index = 0;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  const char* current_method_name =  SPVM_API_RUNTIME_get_name(runtime, current_method->name_id);
  
  // Current basic type
  SPVM_RUNTIME_BASIC_TYPE* current_basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, current_method->current_basic_type_id);
  
  const char* current_basic_type_name =  SPVM_API_RUNTIME_get_name(runtime, current_basic_type->name_id);
  
  // Operation codes
  SPVM_OPCODE* opcodes = runtime->opcodes;
  
  // Error
  int32_t error_id = 0;
  
  // Caught eval error_id
  int32_t eval_error_id = 0;
  
  // Operation code base
  int32_t current_method_opcodes_base_address_id = current_method->opcodes_base_address_id;
  
  // Mortal stack
  int32_t* mortal_stack = NULL;
  int32_t mortal_stack_top = 0;
  
  // object variables
  void** object_vars = NULL;
  
  // ref variables
  void** ref_vars = NULL;
  
  // double variables
  double* double_vars = NULL;
  
  // float variables
  float* float_vars = NULL;
  
  // long variables
  int64_t* long_vars = NULL;
  
  // int variables
  int32_t* int_vars = NULL;
  
  // short variables
  int16_t* short_vars = NULL;
  
  // byte variables
  int8_t* byte_vars = NULL;
  
  // Alloc variable memory
  // Allignment is 8. This is numeric type max byte size
  // Order 8, 4, 2, 1 numeric variable, and addrress variables
  char* call_stack = NULL;
  {
    // Numeric area byte size
    int32_t numeric_vars_size = 0;
    numeric_vars_size += current_method->call_stack_long_vars_length * 8;
    numeric_vars_size += current_method->call_stack_double_vars_length * 8;
    numeric_vars_size += current_method->call_stack_int_vars_length * 4;
    numeric_vars_size += current_method->call_stack_float_vars_length * 4;
    numeric_vars_size += current_method->mortal_stack_length * 4;
    numeric_vars_size += current_method->call_stack_short_vars_length * 2;
    numeric_vars_size += current_method->call_stack_byte_vars_length * 1;
    
    if (numeric_vars_size % 8 != 0) {
      numeric_vars_size += (8 - (numeric_vars_size % 8));
    }
    
    // Address area byte size
    int32_t address_vars_size = 0;
    address_vars_size += current_method->call_stack_object_vars_length * sizeof(void*);
    address_vars_size += current_method->call_stack_ref_vars_length * sizeof(void*);
    
    // Total area byte size
    int32_t total_vars_size = numeric_vars_size + address_vars_size;
    
    call_stack = SPVM_API_new_memory_stack(env, stack, total_vars_size + 1);
    if (call_stack == NULL) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_CALL_STACK_ALLOCATION_FAILED]);
      env->set_exception(env, stack, exception);
      error_id = 1;
      return error_id;
    }

    int32_t call_stack_offset = 0;
    
    // Double variables
    double_vars = (double*)&call_stack[call_stack_offset];
    call_stack_offset += current_method->call_stack_double_vars_length * 8;
    
    // Long varialbes
    long_vars = (int64_t*)&call_stack[call_stack_offset];
    call_stack_offset += current_method->call_stack_long_vars_length * 8;
    
    // Float variables
    float_vars = (float*)&call_stack[call_stack_offset];
    call_stack_offset += current_method->call_stack_float_vars_length * 4;
    
    // Int variables
    int_vars = (int32_t*)&call_stack[call_stack_offset];
    call_stack_offset += current_method->call_stack_int_vars_length * 4;

    // Mortal stack
    mortal_stack = (int32_t*)&call_stack[call_stack_offset];
    call_stack_offset += current_method->mortal_stack_length * 4;
    
    // Short variables
    short_vars = (int16_t*)&call_stack[call_stack_offset];
    call_stack_offset += current_method->call_stack_short_vars_length * 2;

    // Byte variables
    byte_vars = (int8_t*)&call_stack[call_stack_offset];
    call_stack_offset += current_method->call_stack_byte_vars_length * 1;
    
    call_stack_offset = numeric_vars_size;

    // Object variables
    object_vars = (void**)&call_stack[call_stack_offset];
    call_stack_offset += current_method->call_stack_object_vars_length * sizeof(void*);
    
    // Refernce variables
    ref_vars = (void**)&call_stack[call_stack_offset];
    call_stack_offset += current_method->call_stack_ref_vars_length * sizeof(void*);
  }

  // Buffer for string convertion
  // double need 17 digit
  // int64_t need 21 gidit (-9223372036854775808 + (null character))
  char tmp_buffer[256];
  
  int32_t object_header_size = (intptr_t)env->object_header_size;

  // Execute operation codes
  while (1) {
    SPVM_OPCODE* opcode = &(opcodes[current_method_opcodes_base_address_id + opcode_rel_index]);
    
    int32_t opcode_id = opcode->id;
    
    switch (opcode_id) {

      case SPVM_OPCODE_C_ID_END_METHOD: {
        goto label_END_OF_METHOD;
      }
      case SPVM_OPCODE_C_ID_GOTO: {
        opcode_rel_index = opcode->operand0;
        continue;
      }
      case SPVM_OPCODE_C_ID_IF_EQ_ZERO: {
        if (int_vars[0] == 0) {
          opcode_rel_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_IF_NE_ZERO: {
        if (int_vars[0] != 0) {
          opcode_rel_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GOTO_END_OF_EVAL_ON_EXCEPTION: {
        if (__builtin_expect(error_id, 0)) {
          int32_t line = opcode->operand2;
          eval_error_id = error_id;
          error_id = 0;
          env->set_exception(env, stack, env->new_stack_trace_raw(env, stack, env->get_exception(env, stack), current_method, line));
          opcode_rel_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GOTO_END_OF_METHOD_ON_EXCEPTION: {
        if (__builtin_expect(error_id, 0)) {
          int32_t line = opcode->operand2;
          env->set_exception(env, stack, env->new_stack_trace_raw(env, stack, env->get_exception(env, stack), current_method, line));
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
          SPVM_OPCODE* opcode_case_info_min = &(opcodes[current_method_opcodes_base_address_id + opcode_rel_index + 1 + 0]);
          int32_t min = opcode_case_info_min->operand1;
          
          // max
          SPVM_OPCODE* opcode_case_info_max = &(opcodes[current_method_opcodes_base_address_id + opcode_rel_index + 1 + case_infos_length - 1]);
          int32_t max = opcode_case_info_max->operand1;
          
          if (int_vars[opcode->operand0] >= min && int_vars[opcode->operand0] <= max) {
            // 2 opcode_rel_index searching
            int32_t cur_min_pos = 0;
            int32_t cur_max_pos = case_infos_length - 1;
            
            while (1) {
              if (cur_max_pos < cur_min_pos) {
                opcode_rel_index = default_opcode_rel_index;
                break;
              }
              int32_t cur_half_pos = cur_min_pos + (cur_max_pos - cur_min_pos) / 2;
              SPVM_OPCODE* opcode_case_cur_half = &(opcodes[current_method_opcodes_base_address_id + opcode_rel_index + 1 + cur_half_pos]);
              int32_t cur_half = opcode_case_cur_half->operand1;
              
              if (int_vars[opcode->operand0] > cur_half) {
                cur_min_pos = cur_half_pos + 1;
              }
              else if (int_vars[opcode->operand0] < cur_half) {
                cur_max_pos = cur_half_pos - 1;
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
      case SPVM_OPCODE_C_ID_LEAVE_SCOPE: {
        int32_t original_mortal_stack_top = opcode->operand0;
        SPVM_IMPLEMENT_LEAVE_SCOPE(env, stack, object_vars, mortal_stack, &mortal_stack_top, original_mortal_stack_top);
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
        SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, &object_vars[opcode->operand0], NULL);
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
      case SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECKING: {
        int32_t cast_basic_type_id = opcode->operand2;
        int32_t cast_type_dimension = opcode->operand3;
        
        SPVM_IMPLEMENT_MOVE_OBJECT_WITH_TYPE_CHECKING(env, stack, &object_vars[opcode->operand0], object_vars[opcode->operand1], cast_basic_type_id, cast_type_dimension, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_OBJECT_CHECK_READ_ONLY: {
        SPVM_IMPLEMENT_MOVE_OBJECT_CHECK_READ_ONLY(env, stack, &object_vars[opcode->operand0], object_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_REF: {
        SPVM_IMPLEMENT_MOVE_REF(ref_vars[opcode->operand0], ref_vars[opcode->operand1]);
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
      case SPVM_OPCODE_C_ID_REMAINDER_INT: {
        SPVM_IMPLEMENT_REMAINDER_INT(env, stack, &int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_LONG: {
        SPVM_IMPLEMENT_REMAINDER_LONG(env, stack, &long_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_UNSIGNED_INT: {
        SPVM_IMPLEMENT_REMAINDER_UNSIGNED_INT(env, stack, &int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_UNSIGNED_LONG: {
        SPVM_IMPLEMENT_REMAINDER_UNSIGNED_LONG(env, stack, &long_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2], &error_id);
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
      case SPVM_OPCODE_C_ID_CONCAT: {
        SPVM_IMPLEMENT_CONCAT(env, stack, &object_vars[opcode->operand0], object_vars[opcode->operand1], object_vars[opcode->operand2], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_CONVERSION_INT: {
        SPVM_IMPLEMENT_BOOL_CONVERSION_INT(int_vars[0], int_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_CONVERSION_LONG: {
        SPVM_IMPLEMENT_BOOL_CONVERSION_LONG(int_vars[0], long_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_CONVERSION_FLOAT: {
        SPVM_IMPLEMENT_BOOL_CONVERSION_FLOAT(int_vars[0], float_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_CONVERSION_DOUBLE: {
        SPVM_IMPLEMENT_BOOL_CONVERSION_DOUBLE(int_vars[0], double_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_CONVERSION_OBJECT: {
        SPVM_IMPLEMENT_BOOL_CONVERSION_OBJECT(int_vars[0], object_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_CONVERSION_REF: {
        SPVM_IMPLEMENT_BOOL_CONVERSION_REF(int_vars[0], ref_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_CONVERSION_BOOL_OBJECT: {
        SPVM_IMPLEMENT_BOOL_CONVERSION_BOOL_OBJECT(env, stack, int_vars[0], object_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_INT: {
        SPVM_IMPLEMENT_EQ_INT(int_vars[0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_LONG: {
        SPVM_IMPLEMENT_EQ_LONG(int_vars[0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_FLOAT: {
        SPVM_IMPLEMENT_EQ_FLOAT(int_vars[0], float_vars[opcode->operand1], float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_DOUBLE: {
        SPVM_IMPLEMENT_EQ_DOUBLE(int_vars[0], double_vars[opcode->operand1], double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_OBJECT: {
        SPVM_IMPLEMENT_EQ_OBJECT(int_vars[0], object_vars[opcode->operand1], object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_REF: {
        SPVM_IMPLEMENT_EQ_REF(int_vars[0], ref_vars[opcode->operand1], ref_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NE_INT: {
        SPVM_IMPLEMENT_NE_INT(int_vars[0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NE_LONG: {
        SPVM_IMPLEMENT_NE_LONG(int_vars[0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NE_FLOAT: {
        SPVM_IMPLEMENT_NE_FLOAT(int_vars[0], float_vars[opcode->operand1], float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NE_DOUBLE: {
        SPVM_IMPLEMENT_NE_DOUBLE(int_vars[0], double_vars[opcode->operand1], double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NE_OBJECT: {
        SPVM_IMPLEMENT_NE_OBJECT(int_vars[0], object_vars[opcode->operand1], object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NE_REF: {
        SPVM_IMPLEMENT_NE_REF(int_vars[0], ref_vars[opcode->operand1], ref_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_GT_INT: {
        SPVM_IMPLEMENT_GT_INT(int_vars[0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_GT_LONG: {
        SPVM_IMPLEMENT_GT_LONG(int_vars[0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_GT_FLOAT: {
        SPVM_IMPLEMENT_GT_FLOAT(int_vars[0], float_vars[opcode->operand1], float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_GT_DOUBLE: {
        SPVM_IMPLEMENT_GT_DOUBLE(int_vars[0], double_vars[opcode->operand1], double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_GE_INT: {
        SPVM_IMPLEMENT_GE_INT(int_vars[0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_GE_LONG: {
        SPVM_IMPLEMENT_GE_LONG(int_vars[0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_GE_FLOAT: {
        SPVM_IMPLEMENT_GE_FLOAT(int_vars[0], float_vars[opcode->operand1], float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_GE_DOUBLE: {
        SPVM_IMPLEMENT_GE_DOUBLE(int_vars[0], double_vars[opcode->operand1], double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_LT_INT: {
        SPVM_IMPLEMENT_LT_INT(int_vars[0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_LT_LONG: {
        SPVM_IMPLEMENT_LT_LONG(int_vars[0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_LT_FLOAT: {
        SPVM_IMPLEMENT_LT_FLOAT(int_vars[0], float_vars[opcode->operand1], float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_LT_DOUBLE: {
        SPVM_IMPLEMENT_LT_DOUBLE(int_vars[0], double_vars[opcode->operand1], double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_LE_INT: {
        SPVM_IMPLEMENT_LE_INT(int_vars[0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_LE_LONG: {
        SPVM_IMPLEMENT_LE_LONG(int_vars[0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_LE_FLOAT: {
        SPVM_IMPLEMENT_LE_FLOAT(int_vars[0], float_vars[opcode->operand1], float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_LE_DOUBLE: {
        SPVM_IMPLEMENT_LE_DOUBLE(int_vars[0], double_vars[opcode->operand1], double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_INT: {
        SPVM_IMPLEMENT_CMP_INT(int_vars[0], int_vars[opcode->operand1], int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_LONG: {
        SPVM_IMPLEMENT_CMP_LONG(int_vars[0], long_vars[opcode->operand1], long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_FLOAT: {
        SPVM_IMPLEMENT_CMP_FLOAT(int_vars[0], float_vars[opcode->operand1], float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_DOUBLE: {
        SPVM_IMPLEMENT_CMP_DOUBLE(int_vars[0], double_vars[opcode->operand1], double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_IS_UNDEF: {
        SPVM_IMPLEMENT_IS_UNDEF(int_vars[0], object_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_IS_NOT_UNDEF: {
        SPVM_IMPLEMENT_IS_NOT_UNDEF(int_vars[0], object_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_EQ: {
        SPVM_IMPLEMENT_STRING_EQ(env, stack, &int_vars[0], object_vars[opcode->operand1], object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_NE: {
        SPVM_IMPLEMENT_STRING_NE(env, stack, &int_vars[0], object_vars[opcode->operand1], object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_GT: {
        SPVM_IMPLEMENT_STRING_GT(env, stack, &int_vars[0], object_vars[opcode->operand1], object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_GE: {
        SPVM_IMPLEMENT_STRING_GE(env, stack, &int_vars[0], object_vars[opcode->operand1], object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_LT: {
        SPVM_IMPLEMENT_STRING_LT(env, stack, &int_vars[0], object_vars[opcode->operand1], object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_LE: {
        SPVM_IMPLEMENT_STRING_LE(env, stack, &int_vars[0], object_vars[opcode->operand1], object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_CMP: {
        SPVM_IMPLEMENT_STRING_CMP(env, stack, &int_vars[0], object_vars[opcode->operand1], object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT: {
        int32_t basic_type_id = opcode->operand1;
        SPVM_IMPLEMENT_NEW_OBJECT(env, stack, &object_vars[opcode->operand0], basic_type_id, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        int32_t length = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_NEW_OBJECT_ARRAY(env, stack, &object_vars[opcode->operand0], basic_type_id, length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULDIM_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        int32_t type_dimension = opcode->operand3;
        int32_t length = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_NEW_MULDIM_ARRAY(env, stack, &object_vars[opcode->operand0], basic_type_id, type_dimension, length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULNUM_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        int32_t length = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_NEW_MULNUM_ARRAY(env, stack, &object_vars[opcode->operand0], basic_type_id, length, &error_id);
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
        int32_t constant_string_id = opcode->operand1;
        int32_t constant_string_length;
        const char* constant_string = SPVM_API_RUNTIME_get_constant_string_value(runtime, constant_string_id, &constant_string_length);
        SPVM_IMPLEMENT_NEW_STRING(env, stack, &object_vars[opcode->operand0], constant_string, constant_string_length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING_LEN: {
        int32_t length = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_NEW_STRING_LEN(env, stack, &object_vars[opcode->operand0], length, &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_IS_READ_ONLY: {
        SPVM_IMPLEMENT_IS_READ_ONLY(env, stack, int_vars[0], object_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_MAKE_READ_ONLY: {
        SPVM_IMPLEMENT_MAKE_READ_ONLY(env, stack, object_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_BYTE: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_BYTE(env, stack, &byte_vars[opcode->operand0], array, index, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_SHORT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_SHORT(env, stack, &short_vars[opcode->operand0], array, index, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_INT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_INT(env, stack, &int_vars[opcode->operand0], array, index, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_LONG: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_LONG(env, stack, &long_vars[opcode->operand0], array, index, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_FLOAT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_FLOAT(env, stack, &float_vars[opcode->operand0], array, index, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_DOUBLE: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_DOUBLE(env, stack, &double_vars[opcode->operand0], array, index, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_OBJECT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_OBJECT(env, stack, &object_vars[opcode->operand0], array, index, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_BYTE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_BYTE(env, stack, array, index, byte_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_SHORT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_SHORT(env, stack, array, index, short_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_INT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_INT(env, stack, array, index, int_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_LONG: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_LONG(env, stack, array, index, long_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_FLOAT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_FLOAT(env, stack, array, index, float_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_DOUBLE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_DOUBLE(env, stack, array, index, double_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_OBJECT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_OBJECT(env, stack, array, index, object_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE(env, stack, array, index, object_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_UNDEF: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_UNDEF(env, stack, array, index, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LENGTH: {
        SPVM_IMPLEMENT_ARRAY_LENGTH(env, stack, &int_vars[opcode->operand0], object_vars[opcode->operand1], &error_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_BYTE: {
        void* object = object_vars[opcode->operand1];
        int32_t field_address_id = opcode->operand2;
        SPVM_IMPLEMENT_GET_FIELD_BYTE(env, stack, &byte_vars[opcode->operand0], object, field_address_id, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_SHORT: {
        void* object = object_vars[opcode->operand1];
        int32_t field_address_id = opcode->operand2;
        SPVM_IMPLEMENT_GET_FIELD_SHORT(env, stack, &short_vars[opcode->operand0], object, field_address_id, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_INT: {
        void* object = object_vars[opcode->operand1];
        int32_t field_address_id = opcode->operand2;
        SPVM_IMPLEMENT_GET_FIELD_INT(env, stack, &int_vars[opcode->operand0], object, field_address_id, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_LONG: {
        void* object = object_vars[opcode->operand1];
        int32_t field_address_id = opcode->operand2;
        SPVM_IMPLEMENT_GET_FIELD_LONG(env, stack, &long_vars[opcode->operand0], object, field_address_id, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_FLOAT: {
        void* object = object_vars[opcode->operand1];
        int32_t field_address_id = opcode->operand2;
        SPVM_IMPLEMENT_GET_FIELD_FLOAT(env, stack, &float_vars[opcode->operand0], object, field_address_id, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE: {
        void* object = object_vars[opcode->operand1];
        int32_t field_address_id = opcode->operand2;
        SPVM_IMPLEMENT_GET_FIELD_DOUBLE(env, stack, &double_vars[opcode->operand0], object, field_address_id, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_OBJECT: {
        void* object = object_vars[opcode->operand1];
        int32_t field_address_id = opcode->operand2;
        SPVM_IMPLEMENT_GET_FIELD_OBJECT(env, stack, &object_vars[opcode->operand0], object, field_address_id, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_BYTE: {
        void* object = object_vars[opcode->operand0];
        int32_t field_address_id = opcode->operand1;
        SPVM_IMPLEMENT_SET_FIELD_BYTE(env, stack, object, field_address_id, byte_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_SHORT: {
        void* object = object_vars[opcode->operand0];
        int32_t field_address_id = opcode->operand1;
        SPVM_IMPLEMENT_SET_FIELD_SHORT(env, stack, object, field_address_id, short_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_INT: {
        void* object = object_vars[opcode->operand0];
        int32_t field_address_id = opcode->operand1;
        SPVM_IMPLEMENT_SET_FIELD_INT(env, stack, object, field_address_id, int_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_LONG: {
        void* object = object_vars[opcode->operand0];
        int32_t field_address_id = opcode->operand1;
        SPVM_IMPLEMENT_SET_FIELD_LONG(env, stack, object, field_address_id, long_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_FLOAT: {
        void* object = object_vars[opcode->operand0];
        int32_t field_address_id = opcode->operand1;
        SPVM_IMPLEMENT_SET_FIELD_FLOAT(env, stack, object, field_address_id, float_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE: {
        void* object = object_vars[opcode->operand0];
        int32_t field_address_id = opcode->operand1;
        SPVM_IMPLEMENT_SET_FIELD_DOUBLE(env, stack, object, field_address_id, double_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_OBJECT: {
        void* object = object_vars[opcode->operand0];
        int32_t field_address_id = opcode->operand1;
        SPVM_IMPLEMENT_SET_FIELD_OBJECT(env, stack, object, field_address_id, object_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_UNDEF: {
        void* object = object_vars[opcode->operand0];
        int32_t field_address_id = opcode->operand1;
        SPVM_IMPLEMENT_SET_FIELD_UNDEF(env, stack, object, field_address_id, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_WEAKEN_FIELD: {
        int32_t field_address_id = opcode->operand1;
        void* object = object_vars[opcode->operand0];
        SPVM_IMPLEMENT_WEAKEN_FIELD(env, stack, object, field_address_id, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_UNWEAKEN_FIELD: {
        int32_t field_address_id = opcode->operand1;
        void* object = object_vars[opcode->operand0];
        SPVM_IMPLEMENT_UNWEAKEN_FIELD(env, stack, object, field_address_id, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_ISWEAK_FIELD: {
        int32_t field_address_id = opcode->operand2;
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_ISWEAK_FIELD(env, stack, &int_vars[0], object, field_address_id, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_BYTE: {
        int32_t class_var_current_basic_type_id = opcode->operand1;
        int32_t class_var_index = opcode->operand2;
        
        void* class_var = env->api->runtime->get_class_var(env->runtime, class_var_current_basic_type_id, class_var_index);
        
        SPVM_IMPLEMENT_GET_CLASS_VAR_BYTE_V2(env, stack, byte_vars[opcode->operand0], class_var);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_SHORT: {
        int32_t class_var_current_basic_type_id = opcode->operand1;
        int32_t class_var_index = opcode->operand2;
        
        void* class_var = env->api->runtime->get_class_var(env->runtime, class_var_current_basic_type_id, class_var_index);
        
        SPVM_IMPLEMENT_GET_CLASS_VAR_SHORT_V2(env, stack, short_vars[opcode->operand0], class_var);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_INT: {
        int32_t class_var_current_basic_type_id = opcode->operand1;
        int32_t class_var_index = opcode->operand2;
        
        void* class_var = env->api->runtime->get_class_var(env->runtime, class_var_current_basic_type_id, class_var_index);
        
        SPVM_IMPLEMENT_GET_CLASS_VAR_INT_V2(env, stack, int_vars[opcode->operand0], class_var);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_LONG: {
        int32_t class_var_current_basic_type_id = opcode->operand1;
        int32_t class_var_index = opcode->operand2;
        
        void* class_var = env->api->runtime->get_class_var(env->runtime, class_var_current_basic_type_id, class_var_index);
        
        SPVM_IMPLEMENT_GET_CLASS_VAR_LONG_V2(env, stack, long_vars[opcode->operand0], class_var);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_FLOAT: {
        int32_t class_var_current_basic_type_id = opcode->operand1;
        int32_t class_var_index = opcode->operand2;
        
        void* class_var = env->api->runtime->get_class_var(env->runtime, class_var_current_basic_type_id, class_var_index);
        
        SPVM_IMPLEMENT_GET_CLASS_VAR_FLOAT_V2(env, stack, float_vars[opcode->operand0], class_var);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_DOUBLE: {
        int32_t class_var_current_basic_type_id = opcode->operand1;
        int32_t class_var_index = opcode->operand2;
        
        void* class_var = env->api->runtime->get_class_var(env->runtime, class_var_current_basic_type_id, class_var_index);
        
        SPVM_IMPLEMENT_GET_CLASS_VAR_DOUBLE_V2(env, stack, double_vars[opcode->operand0], class_var);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_OBJECT: {
        int32_t class_var_current_basic_type_id = opcode->operand1;
        int32_t class_var_index = opcode->operand2;
        
        SPVM_IMPLEMENT_GET_CLASS_VAR_OBJECT(env, stack, &object_vars[opcode->operand0], class_var_current_basic_type_id, class_var_index);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_BYTE: {
        int32_t class_var_current_basic_type_id = opcode->operand0;
        int32_t class_var_index = opcode->operand1;
        SPVM_IMPLEMENT_SET_CLASS_VAR_BYTE(env, stack, class_var_current_basic_type_id, class_var_index, byte_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_SHORT: {
        int32_t class_var_current_basic_type_id = opcode->operand0;
        int32_t class_var_index = opcode->operand1;
        SPVM_IMPLEMENT_SET_CLASS_VAR_SHORT(env, stack, class_var_current_basic_type_id, class_var_index, short_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_INT: {
        int32_t class_var_current_basic_type_id = opcode->operand0;
        int32_t class_var_index = opcode->operand1;
        SPVM_IMPLEMENT_SET_CLASS_VAR_INT(env, stack, class_var_current_basic_type_id, class_var_index, int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_LONG: {
        int32_t class_var_current_basic_type_id = opcode->operand0;
        int32_t class_var_index = opcode->operand1;
        SPVM_IMPLEMENT_SET_CLASS_VAR_LONG(env, stack, class_var_current_basic_type_id, class_var_index, long_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_FLOAT: {
        int32_t class_var_current_basic_type_id = opcode->operand0;
        int32_t class_var_index = opcode->operand1;
        SPVM_IMPLEMENT_SET_CLASS_VAR_FLOAT(env, stack, class_var_current_basic_type_id, class_var_index, float_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_DOUBLE: {
        int32_t class_var_current_basic_type_id = opcode->operand0;
        int32_t class_var_index = opcode->operand1;
        SPVM_IMPLEMENT_SET_CLASS_VAR_DOUBLE(env, stack, class_var_current_basic_type_id, class_var_index, double_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_OBJECT: {
        int32_t class_var_current_basic_type_id = opcode->operand0;
        int32_t class_var_index = opcode->operand1;
        SPVM_IMPLEMENT_SET_CLASS_VAR_OBJECT(env, stack, class_var_current_basic_type_id, class_var_index, object_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_UNDEF: {
        int32_t class_var_current_basic_type_id = opcode->operand0;
        int32_t class_var_index = opcode->operand1;
        SPVM_IMPLEMENT_SET_CLASS_VAR_UNDEF(env, stack, class_var_current_basic_type_id, class_var_index);
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
        SPVM_IMPLEMENT_ISA(env, stack, &int_vars[0], object, basic_type_id, type_dimension);
        break;
      }
      case SPVM_OPCODE_C_ID_ISA_ERROR: {
        int32_t src_basic_type_id = int_vars[opcode->operand1];
        int32_t basic_type_id = opcode->operand2;
        int32_t type_dimension = opcode->operand3;
        SPVM_IMPLEMENT_ISA_ERROR(env, stack, &int_vars[0], src_basic_type_id, basic_type_id, type_dimension);
        break;
      }
      case SPVM_OPCODE_C_ID_IS_TYPE: {
        void* object = object_vars[opcode->operand1];
        int32_t basic_type_id = opcode->operand2;
        int32_t type_dimension = opcode->operand3;
        SPVM_IMPLEMENT_IS_TYPE(env, stack, &int_vars[0], object, basic_type_id, type_dimension);
        break;
      }
      case SPVM_OPCODE_C_ID_IS_ERROR: {
        int32_t src_basic_type_id = int_vars[opcode->operand1];
        int32_t basic_type_id = opcode->operand2;
        int32_t type_dimension = opcode->operand3;
        SPVM_IMPLEMENT_IS_ERROR(env, stack, &int_vars[0], src_basic_type_id, basic_type_id, type_dimension);
        break;
      }
      case SPVM_OPCODE_C_ID_CAN: {
        void* object = object_vars[opcode->operand0];
        int32_t invocant_decl_basic_type_id = opcode->operand1;
        int32_t decl_method_index = opcode->operand2;
        
        SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, invocant_decl_basic_type_id, decl_method_index);
        const char* method_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, method->name_id, NULL);
        SPVM_IMPLEMENT_CAN(env, stack, int_vars[0], object, method_name);
        break;
      }
      case SPVM_OPCODE_C_ID_PRINT: {
        void* string = object_vars[opcode->operand0];
        SPVM_IMPLEMENT_PRINT(env, stack, string);
        break;
      }
      case SPVM_OPCODE_C_ID_SAY: {
        void* string = object_vars[opcode->operand0];
        SPVM_IMPLEMENT_SAY(env, stack, string);
        break;
      }
      case SPVM_OPCODE_C_ID_WARN: {
        void* string = object_vars[opcode->operand0];
        int32_t line = opcode->operand1;
        
        const char* include_dir = NULL;
        const char* include_dir_sep;
        int32_t include_dir_id = current_basic_type->module_dir_id;
        if (include_dir_id >= 0) {
          include_dir_sep = "/";
          include_dir = SPVM_API_RUNTIME_get_constant_string_value(runtime, current_basic_type->module_dir_id, NULL);
        }
        else {
          include_dir_sep = "";
          include_dir = "";
        }
        const char* module_rel_file = SPVM_API_RUNTIME_get_constant_string_value(runtime, current_basic_type->module_rel_file_id, NULL);

        SPVM_IMPLEMENT_WARN(env, stack, string, include_dir, include_dir_sep, module_rel_file, line);
        
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
      case SPVM_OPCODE_C_ID_SET_ERROR_ID: {
        int32_t basic_type_id = opcode->operand0;
        SPVM_IMPLEMENT_SET_ERROR_ID(error_id, basic_type_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_BASIC_TYPE_ID: {
        int32_t basic_type_id = opcode->operand1;
        SPVM_IMPLEMENT_GET_BASIC_TYPE_ID(int_vars[opcode->operand0], basic_type_id);
        break;
      }
      case SPVM_OPCODE_C_ID_ITEMS: {
        SPVM_IMPLEMENT_ITEMS(env, stack, int_vars[opcode->operand0]);
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
        SPVM_IMPLEMENT_GET_DEREF_BYTE(byte_vars[opcode->operand0], &ref_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_SHORT: {
        SPVM_IMPLEMENT_GET_DEREF_SHORT(short_vars[opcode->operand0], &ref_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_INT: {
        SPVM_IMPLEMENT_GET_DEREF_INT(int_vars[opcode->operand0], &ref_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_LONG: {
        SPVM_IMPLEMENT_GET_DEREF_LONG(long_vars[opcode->operand0], &ref_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_FLOAT: {
        SPVM_IMPLEMENT_GET_DEREF_FLOAT(float_vars[opcode->operand0], &ref_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_DOUBLE: {
        SPVM_IMPLEMENT_GET_DEREF_DOUBLE(double_vars[opcode->operand0], &ref_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_BYTE: {
        SPVM_IMPLEMENT_SET_DEREF_BYTE(&ref_vars[opcode->operand0], byte_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_SHORT: {
        SPVM_IMPLEMENT_SET_DEREF_SHORT(&ref_vars[opcode->operand0], short_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_INT: {
        SPVM_IMPLEMENT_SET_DEREF_INT(&ref_vars[opcode->operand0], int_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_LONG: {
        SPVM_IMPLEMENT_SET_DEREF_LONG(&ref_vars[opcode->operand0], long_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_FLOAT: {
        SPVM_IMPLEMENT_SET_DEREF_FLOAT(&ref_vars[opcode->operand0], float_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_DOUBLE: {
        SPVM_IMPLEMENT_SET_DEREF_DOUBLE(&ref_vars[opcode->operand0], double_vars[opcode->operand1]);
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
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_BYTE(env, stack, &byte_vars[opcode->operand0], array, index, fields_length, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_SHORT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_SHORT(env, stack, &short_vars[opcode->operand0], array, index, fields_length, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_INT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_INT(env, stack, &int_vars[opcode->operand0], array, index, fields_length, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_LONG: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_LONG(env, stack, &long_vars[opcode->operand0], array, index, fields_length, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FLOAT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FLOAT(env, stack, &float_vars[opcode->operand0], array, index, fields_length, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_DOUBLE: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_DOUBLE(env, stack, &double_vars[opcode->operand0], array, index, fields_length, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_BYTE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_BYTE(env, stack, array, index, fields_length, &byte_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_SHORT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_SHORT(env, stack, array, index, fields_length, &short_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_INT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_INT(env, stack, array, index, fields_length, &int_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_LONG: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_LONG(env, stack, array, index, fields_length, &long_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FLOAT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FLOAT(env, stack, array, index, fields_length, &float_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_DOUBLE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_DOUBLE(env, stack, array, index, fields_length, &double_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_BYTE: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_BYTE(env, stack, &byte_vars[opcode->operand0], array, index, field_index, fields_length, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_SHORT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_SHORT(env, stack, &short_vars[opcode->operand0], array, index, field_index, fields_length, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_INT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_INT(env, stack, &int_vars[opcode->operand0], array, index, field_index, fields_length, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_LONG: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_LONG(env, stack, &long_vars[opcode->operand0], array, index, field_index, fields_length, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_FLOAT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_FLOAT(env, stack, &float_vars[opcode->operand0], array, index, field_index, fields_length, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_DOUBLE: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_DOUBLE(env, stack, &double_vars[opcode->operand0], array, index, field_index, fields_length, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_BYTE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_BYTE(env, stack, array, index, field_index, fields_length, byte_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_SHORT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_SHORT(env, stack, array, index, field_index, fields_length, short_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_INT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_INT(env, stack, array, index, field_index, fields_length, int_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_LONG: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_LONG(env, stack, array, index, field_index, fields_length, long_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_FLOAT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_FLOAT(env, stack, array, index, field_index, fields_length, float_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_DOUBLE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_DOUBLE(env, stack, array, index, field_index, fields_length, double_vars[opcode->operand2], &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_BYTE: {
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_DEREF_MULNUM_BYTE(env, stack, &byte_vars[opcode->operand0], ref_vars[opcode->operand1], fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_SHORT: {
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_DEREF_MULNUM_SHORT(env, stack, &short_vars[opcode->operand0], ref_vars[opcode->operand1], fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_INT: {
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_DEREF_MULNUM_INT(env, stack, &int_vars[opcode->operand0], ref_vars[opcode->operand1], fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_LONG: {
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_DEREF_MULNUM_LONG(env, stack, &long_vars[opcode->operand0], ref_vars[opcode->operand1], fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_FLOAT: {
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_DEREF_MULNUM_FLOAT(env, stack, &float_vars[opcode->operand0], ref_vars[opcode->operand1], fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_DOUBLE: {
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_DEREF_MULNUM_DOUBLE(env, stack, &double_vars[opcode->operand0], ref_vars[opcode->operand1], fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_BYTE(byte_vars[opcode->operand0], ref_vars[opcode->operand1], field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_SHORT(short_vars[opcode->operand0], ref_vars[opcode->operand1], field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_INT(int_vars[opcode->operand0], ref_vars[opcode->operand1], field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_LONG(long_vars[opcode->operand0], ref_vars[opcode->operand1], field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_FLOAT(float_vars[opcode->operand0], ref_vars[opcode->operand1], field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_DOUBLE(double_vars[opcode->operand0], ref_vars[opcode->operand1], field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_BYTE(ref_vars[opcode->operand0], field_index, byte_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_SHORT(ref_vars[opcode->operand0], field_index, short_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_INT(ref_vars[opcode->operand0], field_index, int_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_LONG(ref_vars[opcode->operand0], field_index, long_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_FLOAT(ref_vars[opcode->operand0], field_index, float_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_DOUBLE(ref_vars[opcode->operand0], field_index, double_vars[opcode->operand1]);
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
        SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_STRING(env, stack, &object_vars[opcode->operand0], byte_vars[opcode->operand1], tmp_buffer, sizeof(tmp_buffer));
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_STRING: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_STRING(env, stack, &object_vars[opcode->operand0], short_vars[opcode->operand1], tmp_buffer, sizeof(tmp_buffer));
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_STRING: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_STRING(env, stack, &object_vars[opcode->operand0], int_vars[opcode->operand1], tmp_buffer, sizeof(tmp_buffer));
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_STRING: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_STRING(env, stack, &object_vars[opcode->operand0], long_vars[opcode->operand1], tmp_buffer, sizeof(tmp_buffer));
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_STRING: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_STRING(env, stack, &object_vars[opcode->operand0], float_vars[opcode->operand1], tmp_buffer, sizeof(tmp_buffer));
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_STRING: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_STRING(env, stack, &object_vars[opcode->operand0], double_vars[opcode->operand1], tmp_buffer, sizeof(tmp_buffer));
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
        SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_BYTE_OBJECT(env, stack, &object_vars[opcode->operand0], value, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_SHORT_OBJECT: {
        int16_t value = short_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_SHORT_OBJECT(env, stack, &object_vars[opcode->operand0], value, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_INT_OBJECT: {
        int32_t value = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_INT_OBJECT(env, stack, &object_vars[opcode->operand0], value, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_LONG_OBJECT: {
        int64_t value = long_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_LONG_OBJECT(env, stack, &object_vars[opcode->operand0], value, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_FLOAT_OBJECT: {
        float value = float_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_FLOAT_OBJECT(env, stack, &object_vars[opcode->operand0], value, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_DOUBLE_OBJECT: {
        double value = double_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_DOUBLE_OBJECT(env, stack, &object_vars[opcode->operand0], value, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_OBJECT_TO_BYTE: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_OBJECT_TO_BYTE(env, stack, &byte_vars[opcode->operand0], object, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_OBJECT_TO_SHORT: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_OBJECT_TO_SHORT(env, stack, &short_vars[opcode->operand0], object, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_OBJECT_TO_INT: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_INT_OBJECT_TO_INT(env, stack, &int_vars[opcode->operand0], object, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_OBJECT_TO_LONG: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_OBJECT_TO_LONG(env, stack, &long_vars[opcode->operand0], object, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_OBJECT_TO_FLOAT: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_OBJECT_TO_FLOAT(env, stack, &float_vars[opcode->operand0], object, &error_id, object_header_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_OBJECT_TO_DOUBLE: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_OBJECT_TO_DOUBLE(env, stack, &double_vars[opcode->operand0], object, &error_id, object_header_size);
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
        int32_t type_stack_length = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_STACK_MULNUM_BYTE(env, &byte_vars[opcode->operand0], stack, opcode->operand3 & 0xFF, type_stack_length);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_MULNUM_SHORT: {
        int32_t type_stack_length = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_STACK_MULNUM_SHORT(env, &short_vars[opcode->operand0], stack, opcode->operand3 & 0xFF, type_stack_length);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_MULNUM_INT: {
        int32_t type_stack_length = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_STACK_MULNUM_INT(env, &int_vars[opcode->operand0], stack, opcode->operand3 & 0xFF, type_stack_length);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_MULNUM_LONG: {
        int32_t type_stack_length = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_STACK_MULNUM_LONG(env, &long_vars[opcode->operand0], stack, opcode->operand3 & 0xFF, type_stack_length);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_MULNUM_FLOAT: {
        int32_t type_stack_length = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_STACK_MULNUM_FLOAT(env, &float_vars[opcode->operand0], stack, opcode->operand3 & 0xFF, type_stack_length);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_MULNUM_DOUBLE: {
        int32_t type_stack_length = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_STACK_MULNUM_DOUBLE(env, &double_vars[opcode->operand0], stack, opcode->operand3 & 0xFF, type_stack_length);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_BYTE: {
        int32_t stack_index = opcode->operand3 & 0xFF;
        SPVM_IMPLEMENT_GET_STACK_OPTIONAL_BYTE(env, &byte_vars[opcode->operand0], stack, stack_index, (int8_t)(uint8_t)opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_SHORT: {
        int32_t stack_index = opcode->operand3 & 0xFF;
        SPVM_IMPLEMENT_GET_STACK_OPTIONAL_SHORT(env, &short_vars[opcode->operand0], stack, stack_index, (int16_t)(uint16_t)opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_INT: {
        int32_t stack_index = opcode->operand3 & 0xFF;
        SPVM_IMPLEMENT_GET_STACK_OPTIONAL_INT(env, &int_vars[opcode->operand0], stack, stack_index, (int32_t)opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_LONG: {
        int32_t stack_index = opcode->operand3 & 0xFF;
        SPVM_IMPLEMENT_GET_STACK_OPTIONAL_LONG(env, &long_vars[opcode->operand0], stack, stack_index, *(int64_t*)&opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_FLOAT: {
        int32_t stack_index = opcode->operand3 & 0xFF;
        SPVM_VALUE default_value;
        default_value.ival = (int32_t)opcode->operand1;
        SPVM_IMPLEMENT_GET_STACK_OPTIONAL_FLOAT(env, &float_vars[opcode->operand0], stack, stack_index, default_value.fval);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_DOUBLE: {
        int32_t stack_index = opcode->operand3 & 0xFF;
        SPVM_IMPLEMENT_GET_STACK_OPTIONAL_DOUBLE(env, &double_vars[opcode->operand0], stack, stack_index, *(double*)&opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_OBJECT: {
        int32_t stack_index = opcode->operand3 & 0xFF;
        SPVM_IMPLEMENT_GET_STACK_OPTIONAL_OBJECT(env, &object_vars[opcode->operand0], stack, stack_index);
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
        int32_t args_stack_length = opcode->operand2;
        
        SPVM_IMPLEMENT_CALL_CLASS_METHOD(env, stack, error_id, invocant_decl_basic_type_id, decl_method_index, args_stack_length);
        
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD_STATIC: {
        int32_t invocant_decl_basic_type_id = opcode->operand0;
        int32_t decl_method_index = opcode->operand1;
        int32_t args_stack_length = opcode->operand2;
        
        SPVM_IMPLEMENT_CALL_INSTANCE_METHOD_STATIC(env, stack, error_id, invocant_decl_basic_type_id, decl_method_index, args_stack_length);
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD: {
        int32_t invocant_decl_basic_type_id = opcode->operand0;
        int32_t decl_method_index = opcode->operand1;
        int32_t args_stack_length = opcode->operand2;
        
        SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, invocant_decl_basic_type_id, decl_method_index);
        const char* method_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, method->name_id, NULL);
        
        int32_t method_current_basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, method->current_basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, method_current_basic_type_name_id, NULL);
        
        void* object = stack[0].oval;
        SPVM_IMPLEMENT_CALL_INSTANCE_METHOD(env, stack, object, basic_type_name, method_name, args_stack_length, &error_id, tmp_buffer, sizeof(tmp_buffer));
        break;
      }
    }
    opcode_rel_index++;
  }

  label_END_OF_METHOD: {
  
    if (error_id == 0) {
      int32_t current_method_return_basic_type_id = SPVM_API_RUNTIME_get_method_return_basic_type_id(runtime, current_method);
      int32_t current_method_return_type_dimension = SPVM_API_RUNTIME_get_method_return_type_dimension(runtime, current_method);
      int32_t current_method_return_type_flag = SPVM_API_RUNTIME_get_method_return_type_flag(runtime, current_method);
      
      int32_t method_return_type_is_object = SPVM_API_RUNTIME_is_object_type(runtime, current_method_return_basic_type_id, current_method_return_type_dimension, current_method_return_type_flag);
      if (method_return_type_is_object) {
        if (*(void**)&stack[0] != NULL) {
          SPVM_IMPLEMENT_DEC_REF_COUNT_ONLY(env, stack, *(void**)&stack[0]);
        }
      }
    }
    
    SPVM_API_free_memory_stack(env, stack, call_stack);
    call_stack = NULL;
    
    return error_id;
  }
}
