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
#include "spvm_runtime_type.h"
#include "spvm_runtime_class.h"
#include "spvm_runtime_class_var.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_method.h"

#include "spvm_api_string_buffer.h"
#include "spvm_api_allocator.h"
#include "spvm_api_runtime.h"

#include "spvm_implement.h"

static const char* FILE_NAME = "spvm_vm.c";

int32_t SPVM_VM_call_spvm_method(SPVM_ENV* env, SPVM_VALUE* stack, int32_t current_method_id, int32_t args_stack_length) {
  (void)env;

  // Opcode relative index
  register int32_t opcode_rel_index = 0;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;

  // Runtime current_method
  SPVM_RUNTIME_METHOD* current_method = SPVM_API_RUNTIME_get_method(runtime, current_method_id);
  
  const char* current_method_name =  SPVM_API_RUNTIME_get_name(runtime, current_method->name_id);
  
  // Runtime class
  SPVM_RUNTIME_CLASS* current_class = SPVM_API_RUNTIME_get_class(runtime, current_method->class_id);

  const char* current_class_name =  SPVM_API_RUNTIME_get_name(runtime, current_class->name_id);

  // Operation codes
  SPVM_OPCODE* opcodes = runtime->opcodes;

  // Error
  int32_t error = 0;

  // Caught eval error
  int32_t eval_error = 0;
  
  // Error code value
  int32_t error_code = 1;
  
  // Operation code base
  int32_t current_method_opcodes_base_id = current_method->opcodes_base_id;

  // Call current_method argument stack top
  int32_t stack_index = 0;
  
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
    int32_t numeric_vars_byte_size = 0;
    numeric_vars_byte_size += current_method->call_stack_long_vars_length * 8;
    numeric_vars_byte_size += current_method->call_stack_double_vars_length * 8;
    numeric_vars_byte_size += current_method->call_stack_int_vars_length * 4;
    numeric_vars_byte_size += current_method->call_stack_float_vars_length * 4;
    numeric_vars_byte_size += current_method->mortal_stack_length * 4;
    numeric_vars_byte_size += current_method->call_stack_short_vars_length * 2;
    numeric_vars_byte_size += current_method->call_stack_byte_vars_length * 1;
    
    if (numeric_vars_byte_size % 8 != 0) {
      numeric_vars_byte_size += (8 - (numeric_vars_byte_size % 8));
    }
    
    // Address area byte size
    int32_t address_vars_byte_size = 0;
    address_vars_byte_size += current_method->call_stack_object_vars_length * sizeof(void*);
    address_vars_byte_size += current_method->call_stack_ref_vars_length * sizeof(void*);
    
    // Total area byte size
    int32_t total_vars_byte_size = numeric_vars_byte_size + address_vars_byte_size;
    
    call_stack = SPVM_API_new_memory_stack(env, stack, total_vars_byte_size + 1);
    if (call_stack == NULL) {
      void* exception = env->new_string_nolen_raw(env, stack, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_CALL_STACK_ALLOCATION_FAILED]);
      env->set_exception(env, stack, exception);
      error = 1;
      return error;
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
    
    call_stack_offset = numeric_vars_byte_size;

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
  
  int32_t object_header_byte_size = (intptr_t)env->object_header_byte_size;

  // Execute operation codes
  while (1) {
    SPVM_OPCODE* opcode = &(opcodes[current_method_opcodes_base_id + opcode_rel_index]);
    
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
      case SPVM_OPCODE_C_ID_IF_EXCEPTION_CATCH: {
        if (__builtin_expect(error, 0)) {
          int32_t method_id = opcode->operand1;
          int32_t line = opcode->operand2;
          eval_error = error;
          error = 0;
          env->set_exception(env, stack, env->new_stack_trace_raw(env, stack, env->get_exception(env, stack), method_id, line));
          opcode_rel_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_IF_EXCEPTION_RETURN: {
        if (__builtin_expect(error, 0)) {
          int32_t method_id = opcode->operand1;
          int32_t line = opcode->operand2;
          env->set_exception(env, stack, env->new_stack_trace_raw(env, stack, env->get_exception(env, stack), method_id, line));
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
          SPVM_OPCODE* opcode_case_info_min = &(opcodes[current_method_opcodes_base_id + opcode_rel_index + 1 + 0]);
          int32_t min = opcode_case_info_min->operand1;
          
          // max
          SPVM_OPCODE* opcode_case_info_max = &(opcodes[current_method_opcodes_base_id + opcode_rel_index + 1 + case_infos_length - 1]);
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
              SPVM_OPCODE* opcode_case_cur_half = &(opcodes[current_method_opcodes_base_id + opcode_rel_index + 1 + cur_half_pos]);
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
      case SPVM_OPCODE_C_ID_INIT_BYTE: {
        SPVM_IMPLEMENT_INIT_BYTE(byte_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_SHORT: {
        SPVM_IMPLEMENT_INIT_SHORT(short_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_INT: {
        SPVM_IMPLEMENT_INIT_INT(int_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_LONG: {
        SPVM_IMPLEMENT_INIT_LONG(long_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_FLOAT: {
        SPVM_IMPLEMENT_INIT_FLOAT(float_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_DOUBLE: {
        SPVM_IMPLEMENT_INIT_DOUBLE(double_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_OBJECT: {
        SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, &object_vars[opcode->operand0], NULL);
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_BYTE: {
        SPVM_IMPLEMENT_INIT_MULNUM_BYTE(env, stack, &byte_vars[opcode->operand0], opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_SHORT: {
        SPVM_IMPLEMENT_INIT_MULNUM_SHORT(env, stack, &short_vars[opcode->operand0], opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_INT: {
        SPVM_IMPLEMENT_INIT_MULNUM_INT(env, stack, &int_vars[opcode->operand0], opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_LONG: {
        SPVM_IMPLEMENT_INIT_MULNUM_LONG(env, stack, &long_vars[opcode->operand0], opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_FLOAT: {
        SPVM_IMPLEMENT_INIT_MULNUM_FLOAT(env, stack, &float_vars[opcode->operand0], opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_DOUBLE: {
        SPVM_IMPLEMENT_INIT_MULNUM_DOUBLE(env, stack, &double_vars[opcode->operand0], opcode->operand2);
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
        
        SPVM_IMPLEMENT_MOVE_OBJECT_WITH_TYPE_CHECKING(env, stack, &object_vars[opcode->operand0], object_vars[opcode->operand1], cast_basic_type_id, cast_type_dimension, &error);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_OBJECT_CHECK_READ_ONLY: {
        SPVM_IMPLEMENT_MOVE_OBJECT_CHECK_READ_ONLY(env, stack, &object_vars[opcode->operand0], object_vars[opcode->operand1], &error);
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
        SPVM_IMPLEMENT_DIVIDE_INT(env, stack, &int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2], &error);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_LONG: {
        SPVM_IMPLEMENT_DIVIDE_LONG(env, stack, &long_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2], &error);
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
        SPVM_IMPLEMENT_DIVIDE_UNSIGNED_INT(env, stack, &int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2], &error);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_UNSIGNED_LONG: {
        SPVM_IMPLEMENT_DIVIDE_UNSIGNED_LONG(env, stack, &long_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2], &error);
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_INT: {
        SPVM_IMPLEMENT_REMAINDER_INT(env, stack, &int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2], &error);
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_LONG: {
        SPVM_IMPLEMENT_REMAINDER_LONG(env, stack, &long_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2], &error);
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_UNSIGNED_INT: {
        SPVM_IMPLEMENT_REMAINDER_UNSIGNED_INT(env, stack, &int_vars[opcode->operand0], int_vars[opcode->operand1], int_vars[opcode->operand2], &error);
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_UNSIGNED_LONG: {
        SPVM_IMPLEMENT_REMAINDER_UNSIGNED_LONG(env, stack, &long_vars[opcode->operand0], long_vars[opcode->operand1], long_vars[opcode->operand2], &error);
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
        SPVM_IMPLEMENT_CONCAT(env, stack, &object_vars[opcode->operand0], object_vars[opcode->operand1], object_vars[opcode->operand2], &error);
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
        SPVM_IMPLEMENT_NEW_OBJECT(env, stack, &object_vars[opcode->operand0], basic_type_id, &error);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        int32_t length = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_NEW_OBJECT_ARRAY(env, stack, &object_vars[opcode->operand0], basic_type_id, length, &error);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULDIM_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        int32_t element_dimension = opcode->operand3;
        int32_t length = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_NEW_MULDIM_ARRAY(env, stack, &object_vars[opcode->operand0], basic_type_id, element_dimension, length, &error);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULNUM_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        int32_t length = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_NEW_MULNUM_ARRAY(env, stack, &object_vars[opcode->operand0], basic_type_id, length, &error);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_BYTE_ARRAY: {
        int32_t length = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_NEW_BYTE_ARRAY(env, stack, &object_vars[opcode->operand0], length, &error);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY: {
        int32_t length = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_NEW_SHORT_ARRAY(env, stack, &object_vars[opcode->operand0], length, &error);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_INT_ARRAY: {
        int32_t length = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_NEW_INT_ARRAY(env, stack, &object_vars[opcode->operand0], length, &error);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_LONG_ARRAY: {
        int32_t length = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_NEW_LONG_ARRAY(env, stack, &object_vars[opcode->operand0], length, &error);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY: {
        int32_t length = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_NEW_FLOAT_ARRAY(env, stack, &object_vars[opcode->operand0], length, &error);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY: {
        int32_t length = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_NEW_DOUBLE_ARRAY(env, stack, &object_vars[opcode->operand0], length, &error);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING: {
        int32_t constant_string_id = opcode->operand1;
        int32_t constant_string_length;
        const char* constant_string = SPVM_API_RUNTIME_get_constant_string_value(runtime, constant_string_id, &constant_string_length);
        SPVM_IMPLEMENT_NEW_STRING(env, stack, &object_vars[opcode->operand0], constant_string, constant_string_length, &error);
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING_LEN: {
        int32_t length = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_NEW_STRING_LEN(env, stack, &object_vars[opcode->operand0], length, &error);
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
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_BYTE(env, stack, &byte_vars[opcode->operand0], array, index, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_SHORT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_SHORT(env, stack, &short_vars[opcode->operand0], array, index, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_INT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_INT(env, stack, &int_vars[opcode->operand0], array, index, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_LONG: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_LONG(env, stack, &long_vars[opcode->operand0], array, index, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_FLOAT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_FLOAT(env, stack, &float_vars[opcode->operand0], array, index, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_DOUBLE: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_DOUBLE(env, stack, &double_vars[opcode->operand0], array, index, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_OBJECT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_OBJECT(env, stack, &object_vars[opcode->operand0], array, index, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_BYTE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_BYTE(env, stack, array, index, byte_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_SHORT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_SHORT(env, stack, array, index, short_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_INT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_INT(env, stack, array, index, int_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_LONG: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_LONG(env, stack, array, index, long_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_FLOAT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_FLOAT(env, stack, array, index, float_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_DOUBLE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_DOUBLE(env, stack, array, index, double_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_OBJECT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_OBJECT(env, stack, array, index, object_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE(env, stack, array, index, object_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_UNDEF: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_UNDEF(env, stack, array, index, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LENGTH: {
        SPVM_IMPLEMENT_ARRAY_LENGTH(env, stack, &int_vars[opcode->operand0], object_vars[opcode->operand1], &error);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_BYTE: {
        void* object = object_vars[opcode->operand1];
        int32_t field_id = opcode->operand2;
        SPVM_IMPLEMENT_GET_FIELD_BYTE(env, stack, &byte_vars[opcode->operand0], object, field_id, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_SHORT: {
        void* object = object_vars[opcode->operand1];
        int32_t field_id = opcode->operand2;
        SPVM_IMPLEMENT_GET_FIELD_SHORT(env, stack, &short_vars[opcode->operand0], object, field_id, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_INT: {
        void* object = object_vars[opcode->operand1];
        int32_t field_id = opcode->operand2;
        SPVM_IMPLEMENT_GET_FIELD_INT(env, stack, &int_vars[opcode->operand0], object, field_id, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_LONG: {
        void* object = object_vars[opcode->operand1];
        int32_t field_id = opcode->operand2;
        SPVM_IMPLEMENT_GET_FIELD_LONG(env, stack, &long_vars[opcode->operand0], object, field_id, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_FLOAT: {
        void* object = object_vars[opcode->operand1];
        int32_t field_id = opcode->operand2;
        SPVM_IMPLEMENT_GET_FIELD_FLOAT(env, stack, &float_vars[opcode->operand0], object, field_id, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE: {
        void* object = object_vars[opcode->operand1];
        int32_t field_id = opcode->operand2;
        SPVM_IMPLEMENT_GET_FIELD_DOUBLE(env, stack, &double_vars[opcode->operand0], object, field_id, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_OBJECT: {
        void* object = object_vars[opcode->operand1];
        int32_t field_id = opcode->operand2;
        SPVM_IMPLEMENT_GET_FIELD_OBJECT(env, stack, &object_vars[opcode->operand0], object, field_id, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_BYTE: {
        void* object = object_vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        SPVM_IMPLEMENT_SET_FIELD_BYTE(env, stack, object, field_id, byte_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_SHORT: {
        void* object = object_vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        SPVM_IMPLEMENT_SET_FIELD_SHORT(env, stack, object, field_id, short_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_INT: {
        void* object = object_vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        SPVM_IMPLEMENT_SET_FIELD_INT(env, stack, object, field_id, int_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_LONG: {
        void* object = object_vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        SPVM_IMPLEMENT_SET_FIELD_LONG(env, stack, object, field_id, long_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_FLOAT: {
        void* object = object_vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        SPVM_IMPLEMENT_SET_FIELD_FLOAT(env, stack, object, field_id, float_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE: {
        void* object = object_vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        SPVM_IMPLEMENT_SET_FIELD_DOUBLE(env, stack, object, field_id, double_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_OBJECT: {
        void* object = object_vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        SPVM_IMPLEMENT_SET_FIELD_OBJECT(env, stack, object, field_id, object_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_UNDEF: {
        void* object = object_vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        SPVM_IMPLEMENT_SET_FIELD_UNDEF(env, stack, object, field_id, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_BYTE: {
        int32_t class_var_id = opcode->operand1;
        SPVM_IMPLEMENT_GET_CLASS_VAR_BYTE(env, stack, byte_vars[opcode->operand0], class_var_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_SHORT: {
        int32_t class_var_id = opcode->operand1;
        SPVM_IMPLEMENT_GET_CLASS_VAR_SHORT(env, stack, short_vars[opcode->operand0], class_var_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_INT: {
        int32_t class_var_id = opcode->operand1;
        SPVM_IMPLEMENT_GET_CLASS_VAR_INT(env, stack, int_vars[opcode->operand0], class_var_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_LONG: {
        int32_t class_var_id = opcode->operand1;
        SPVM_IMPLEMENT_GET_CLASS_VAR_LONG(env, stack, long_vars[opcode->operand0], class_var_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_FLOAT: {
        int32_t class_var_id = opcode->operand1;
        SPVM_IMPLEMENT_GET_CLASS_VAR_FLOAT(env, stack, float_vars[opcode->operand0], class_var_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_DOUBLE: {
        int32_t class_var_id = opcode->operand1;
        SPVM_IMPLEMENT_GET_CLASS_VAR_DOUBLE(env, stack, double_vars[opcode->operand0], class_var_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_OBJECT: {
        int32_t class_var_id = opcode->operand1;
        SPVM_IMPLEMENT_GET_CLASS_VAR_OBJECT(env, stack, &object_vars[opcode->operand0], class_var_id);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_BYTE: {
        int32_t class_var_id = opcode->operand0;
        SPVM_IMPLEMENT_SET_CLASS_VAR_BYTE(env, stack, class_var_id, byte_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_SHORT: {
        int32_t class_var_id = opcode->operand0;
        SPVM_IMPLEMENT_SET_CLASS_VAR_SHORT(env, stack, class_var_id, short_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_INT: {
        int32_t class_var_id = opcode->operand0;
        SPVM_IMPLEMENT_SET_CLASS_VAR_INT(env, stack, class_var_id, int_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_LONG: {
        int32_t class_var_id = opcode->operand0;
        SPVM_IMPLEMENT_SET_CLASS_VAR_LONG(env, stack, class_var_id, long_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_FLOAT: {
        int32_t class_var_id = opcode->operand0;
        SPVM_IMPLEMENT_SET_CLASS_VAR_FLOAT(env, stack, class_var_id, float_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_DOUBLE: {
        int32_t class_var_id = opcode->operand0;
        SPVM_IMPLEMENT_SET_CLASS_VAR_DOUBLE(env, stack, class_var_id, double_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_OBJECT: {
        int32_t class_var_id = opcode->operand0;
        SPVM_IMPLEMENT_SET_CLASS_VAR_OBJECT(env, stack, class_var_id, object_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_UNDEF: {
        int32_t class_var_id = opcode->operand0;
        SPVM_IMPLEMENT_SET_CLASS_VAR_UNDEF(env, stack, class_var_id);
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
      case SPVM_OPCODE_C_ID_IS_TYPE: {
        void* object = object_vars[opcode->operand1];
        int32_t basic_type_id = opcode->operand2;
        int32_t type_dimension = opcode->operand3;
        SPVM_IMPLEMENT_IS_TYPE(env, stack, &int_vars[0], object, basic_type_id, type_dimension);
        break;
      }
      case SPVM_OPCODE_C_ID_HAS_IMPL: {
        void* object = object_vars[opcode->operand0];
        int32_t method_id = opcode->operand1;
        SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
        const char* method_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, method->name_id, NULL);
        SPVM_IMPLEMENT_HAS_IMPL(env, stack, int_vars[0], object, method_name);
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
        
        const char* module_dir = NULL;
        const char* module_dir_sep;
        int32_t module_dir_id = current_class->module_dir_id;
        if (module_dir_id >= 0) {
          module_dir_sep = "/";
          module_dir = SPVM_API_RUNTIME_get_constant_string_value(runtime, current_class->module_dir_id, NULL);
        }
        else {
          module_dir_sep = "";
          module_dir = "";
        }
        const char* module_rel_file = SPVM_API_RUNTIME_get_constant_string_value(runtime, current_class->module_rel_file_id, NULL);

        SPVM_IMPLEMENT_WARN(env, stack, string, module_dir, module_dir_sep, module_rel_file, line);
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ERROR_CODE: {
        SPVM_IMPLEMENT_GET_ERROR_CODE(int_vars[opcode->operand0], error_code);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ERROR_CODE: {
        int32_t tmp_error_code = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_SET_ERROR_CODE(env, stack, &int_vars[opcode->operand0], &error_code, int_vars[opcode->operand1], &error);
        break;
      }
      case SPVM_OPCODE_C_ID_CLEAR_EVAL_ERROR: {
        SPVM_IMPLEMENT_CLEAR_EVAL_ERROR(eval_error);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_EVAL_ERROR: {
        SPVM_IMPLEMENT_GET_EVAL_ERROR(int_vars[opcode->operand0], eval_error);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ERROR: {
        SPVM_IMPLEMENT_SET_ERROR(error, error_code);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_ID: {
        int32_t class_id = opcode->operand1;
        SPVM_IMPLEMENT_GET_CLASS_ID(int_vars[opcode->operand0], class_id);
        break;
      }
      case SPVM_OPCODE_C_ID_REFOP: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_REFOP(env, stack, &object_vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_DUMP: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_DUMP(env, stack, &object_vars[opcode->operand0], object);
        break;
      }
      case SPVM_OPCODE_C_ID_COPY: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_COPY(env, stack, &object_vars[opcode->operand0], object, &error);
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
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_BYTE(env, stack, &byte_vars[opcode->operand0], array, index, fields_length, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_SHORT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_SHORT(env, stack, &short_vars[opcode->operand0], array, index, fields_length, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_INT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_INT(env, stack, &int_vars[opcode->operand0], array, index, fields_length, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_LONG: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_LONG(env, stack, &long_vars[opcode->operand0], array, index, fields_length, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FLOAT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FLOAT(env, stack, &float_vars[opcode->operand0], array, index, fields_length, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_DOUBLE: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_DOUBLE(env, stack, &double_vars[opcode->operand0], array, index, fields_length, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_BYTE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_BYTE(env, stack, array, index, fields_length, &byte_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_SHORT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_SHORT(env, stack, array, index, fields_length, &short_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_INT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_INT(env, stack, array, index, fields_length, &int_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_LONG: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_LONG(env, stack, array, index, fields_length, &long_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FLOAT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FLOAT(env, stack, array, index, fields_length, &float_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_DOUBLE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_DOUBLE(env, stack, array, index, fields_length, &double_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_BYTE: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_BYTE(env, stack, &byte_vars[opcode->operand0], array, index, field_index, fields_length, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_SHORT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_SHORT(env, stack, &short_vars[opcode->operand0], array, index, field_index, fields_length, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_INT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_INT(env, stack, &int_vars[opcode->operand0], array, index, field_index, fields_length, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_LONG: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_LONG(env, stack, &long_vars[opcode->operand0], array, index, field_index, fields_length, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_FLOAT: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_FLOAT(env, stack, &float_vars[opcode->operand0], array, index, field_index, fields_length, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_DOUBLE: {
        void* array = object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_DOUBLE(env, stack, &double_vars[opcode->operand0], array, index, field_index, fields_length, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_BYTE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_BYTE(env, stack, array, index, field_index, fields_length, byte_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_SHORT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_SHORT(env, stack, array, index, field_index, fields_length, short_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_INT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_INT(env, stack, array, index, field_index, fields_length, int_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_LONG: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_LONG(env, stack, array, index, field_index, fields_length, long_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_FLOAT: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_FLOAT(env, stack, array, index, field_index, fields_length, float_vars[opcode->operand2], &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_DOUBLE: {
        void* array = object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_DOUBLE(env, stack, array, index, field_index, fields_length, double_vars[opcode->operand2], &error, object_header_byte_size);
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
      case SPVM_OPCODE_C_ID_WEAKEN_FIELD: {
        int32_t field_id = opcode->operand1;
        void* object = object_vars[opcode->operand0];
        SPVM_IMPLEMENT_WEAKEN_FIELD(env, stack, object, field_id, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_UNWEAKEN_FIELD: {
        int32_t field_id = opcode->operand1;
        void* object = object_vars[opcode->operand0];
        SPVM_IMPLEMENT_UNWEAKEN_FIELD(env, stack, object, field_id, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_ISWEAK_FIELD: {
        int32_t field_id = opcode->operand2;
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_ISWEAK_FIELD(env, stack, &int_vars[0], object, field_id, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_REFCNT: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_REFCNT(env, stack, &int_vars[opcode->operand0], object);
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
        SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_STRING(env, stack, &object_vars[opcode->operand0], byte_vars[opcode->operand1], tmp_buffer);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_STRING: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_STRING(env, stack, &object_vars[opcode->operand0], short_vars[opcode->operand1], tmp_buffer);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_STRING: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_STRING(env, stack, &object_vars[opcode->operand0], int_vars[opcode->operand1], tmp_buffer);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_STRING: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_STRING(env, stack, &object_vars[opcode->operand0], byte_vars[opcode->operand1], tmp_buffer);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_STRING: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_STRING(env, stack, &object_vars[opcode->operand0], float_vars[opcode->operand1], tmp_buffer);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_STRING: {
        SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_STRING(env, stack, &object_vars[opcode->operand0], double_vars[opcode->operand1], tmp_buffer);
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
        SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_BYTE_OBJECT(env, stack, &object_vars[opcode->operand0], value, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_SHORT_OBJECT: {
        int16_t value = short_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_SHORT_OBJECT(env, stack, &object_vars[opcode->operand0], value, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_INT_OBJECT: {
        int32_t value = int_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_INT_OBJECT(env, stack, &object_vars[opcode->operand0], value, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_LONG_OBJECT: {
        int64_t value = long_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_LONG_OBJECT(env, stack, &object_vars[opcode->operand0], value, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_FLOAT_OBJECT: {
        float value = float_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_FLOAT_OBJECT(env, stack, &object_vars[opcode->operand0], value, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_DOUBLE_OBJECT: {
        double value = double_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_DOUBLE_OBJECT(env, stack, &object_vars[opcode->operand0], value, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_OBJECT_TO_BYTE: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_OBJECT_TO_BYTE(env, stack, &byte_vars[opcode->operand0], object, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_OBJECT_TO_SHORT: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_OBJECT_TO_SHORT(env, stack, &short_vars[opcode->operand0], object, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_OBJECT_TO_INT: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_INT_OBJECT_TO_INT(env, stack, &int_vars[opcode->operand0], object, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_OBJECT_TO_LONG: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_OBJECT_TO_LONG(env, stack, &long_vars[opcode->operand0], object, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_OBJECT_TO_FLOAT: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_OBJECT_TO_FLOAT(env, stack, &float_vars[opcode->operand0], object, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_OBJECT_TO_DOUBLE: {
        void* object = object_vars[opcode->operand1];
        SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_OBJECT_TO_DOUBLE(env, stack, &double_vars[opcode->operand0], object, &error, object_header_byte_size);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_BYTE: {
        SPVM_IMPLEMENT_SET_STACK_BYTE(stack, stack_index, byte_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_SHORT: {
        SPVM_IMPLEMENT_SET_STACK_SHORT(stack, stack_index, short_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_INT: {
        SPVM_IMPLEMENT_SET_STACK_INT(stack, stack_index, int_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_LONG: {
        SPVM_IMPLEMENT_SET_STACK_LONG(stack, stack_index, long_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_FLOAT: {
        SPVM_IMPLEMENT_SET_STACK_FLOAT(stack, stack_index, float_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_DOUBLE: {
        SPVM_IMPLEMENT_SET_STACK_DOUBLE(stack, stack_index, double_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_OBJECT: {
        SPVM_IMPLEMENT_SET_STACK_OBJECT(stack, stack_index, object_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_REF: {
        SPVM_IMPLEMENT_SET_STACK_REF(stack, stack_index, ref_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_UNDEF: {
        SPVM_IMPLEMENT_SET_STACK_UNDEF(stack, stack_index);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_MULNUM_BYTE: {
        int32_t fields_length = opcode->operand1;
        SPVM_IMPLEMENT_SET_STACK_MULNUM_BYTE(env, stack, &stack_index, fields_length, &byte_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_MULNUM_SHORT: {
        int32_t fields_length = opcode->operand1;
        SPVM_IMPLEMENT_SET_STACK_MULNUM_SHORT(env, stack, &stack_index, fields_length, &short_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_MULNUM_INT: {
        int32_t fields_length = opcode->operand1;
        SPVM_IMPLEMENT_SET_STACK_MULNUM_INT(env, stack, &stack_index, fields_length, &int_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_MULNUM_LONG: {
        int32_t fields_length = opcode->operand1;
        SPVM_IMPLEMENT_SET_STACK_MULNUM_LONG(env, stack, &stack_index, fields_length, &long_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_MULNUM_FLOAT: {
        int32_t fields_length = opcode->operand1;
        SPVM_IMPLEMENT_SET_STACK_MULNUM_FLOAT(env, stack, &stack_index, fields_length, &float_vars[opcode->operand0]);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_MULNUM_DOUBLE: {
        int32_t fields_length = opcode->operand1;
        SPVM_IMPLEMENT_SET_STACK_MULNUM_DOUBLE(env, stack, &stack_index, fields_length, &double_vars[opcode->operand0]);
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
      case SPVM_OPCODE_C_ID_CALL_METHOD_ONLY: {
        int32_t method_id = opcode->operand1;
        int32_t return_stack_length = opcode->operand3;
        
        int32_t is_class_method_call = opcode->operand2 & 0xF;
        int32_t is_static_instance_method_call = (opcode->operand2 >> 8) & 0xF;
        int32_t call_method_args_stack_length = opcode->operand2 >> 16;
        int32_t is_interface = !is_class_method_call && !is_static_instance_method_call;
        
        int32_t call_method_id;
        if (is_interface) {
          int32_t decl_method_id = method_id;
          SPVM_RUNTIME_METHOD* decl_method = SPVM_API_RUNTIME_get_method(runtime, decl_method_id);
          void* object = stack[0].oval;
          const char* decl_method_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, decl_method->name_id, NULL);
          
          call_method_id = env->get_instance_method_id(env, object, decl_method_name);
          if (call_method_id < 0) {
            memset(tmp_buffer, sizeof(tmp_buffer), 0);
            SPVM_RUNTIME_CLASS* decl_method_class = SPVM_API_RUNTIME_get_class(runtime, decl_method->class_id);
            snprintf(tmp_buffer, 255, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_CALL_INSTANCE_METHOD_NOT_FOUND], decl_method_name, SPVM_API_RUNTIME_get_constant_string_value(runtime, decl_method_class->name_id, NULL));
            void* exception = env->new_string_nolen_raw(env, stack, tmp_buffer);
            env->set_exception(env, stack, exception);
            error = 1;
          }
        }
        else {
          call_method_id = method_id;
        }
        
        if (!error) {
          stack_index = 0;
          error = env->call_spvm_method(env, stack, call_method_id, call_method_args_stack_length);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_METHOD: {
        int32_t method_id = opcode->operand1;
        int32_t return_stack_length = opcode->operand3;
        
        int32_t is_class_method_call = opcode->operand2 & 0xF;
        int32_t is_static_instance_method_call = (opcode->operand2 >> 8) & 0xF;
        int32_t call_method_args_stack_length = opcode->operand2 >> 16;
        int32_t is_interface = !is_class_method_call && !is_static_instance_method_call;
        
        int32_t call_method_id;
        if (is_interface) {
          int32_t decl_method_id = method_id;
          SPVM_RUNTIME_METHOD* decl_method = SPVM_API_RUNTIME_get_method(runtime, decl_method_id);
          void* object = stack[0].oval;
          const char* decl_method_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, decl_method->name_id, NULL);
          
          call_method_id = env->get_instance_method_id(env, object, decl_method_name);
          if (call_method_id < 0) {
            memset(tmp_buffer, sizeof(tmp_buffer), 0);
            SPVM_RUNTIME_CLASS* decl_method_class = SPVM_API_RUNTIME_get_class(runtime, decl_method->class_id);
            snprintf(tmp_buffer, 255, SPVM_IMPLEMENT_STRING_LITERALS[SPVM_IMPLEMENT_C_STRING_CALL_INSTANCE_METHOD_NOT_FOUND], decl_method_name, SPVM_API_RUNTIME_get_constant_string_value(runtime, decl_method_class->name_id, NULL));
            void* exception = env->new_string_nolen_raw(env, stack, tmp_buffer);
            env->set_exception(env, stack, exception);
            error = 1;
          }
        }
        else {
          call_method_id = method_id;
        }
        
        if (!error) {
          stack_index = 0;
          error = env->call_spvm_method(env, stack, call_method_id, call_method_args_stack_length);
        }

        int8_t* out_byte_vars = &byte_vars[opcode->operand0];
        int16_t* out_short_vars = &short_vars[opcode->operand0];
        int32_t* out_int_vars = &int_vars[opcode->operand0];
        int64_t* out_long_vars = &long_vars[opcode->operand0];
        float* out_float_vars = &float_vars[opcode->operand0];
        double* out_double_vars = &double_vars[opcode->operand0];
        void** out_object_vars = &object_vars[opcode->operand0];
        
        if (error == 0) {
          SPVM_RUNTIME_METHOD* call_spvm_method = SPVM_API_RUNTIME_get_method(runtime, call_method_id);
          SPVM_RUNTIME_TYPE* call_spvm_method_return_type =SPVM_API_RUNTIME_get_type(runtime, call_spvm_method->return_type_id);
          int32_t call_spvm_method_return_basic_type_id = call_spvm_method_return_type->basic_type_id;
          int32_t call_spvm_method_return_type_dimension = call_spvm_method_return_type->dimension;
          int32_t call_spvm_method_return_basic_type_category = SPVM_API_RUNTIME_get_basic_type_category(runtime, call_spvm_method_return_type->basic_type_id);
          if (call_spvm_method_return_type_dimension == 0) {
            switch (call_spvm_method_return_basic_type_category) {
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_VOID: {
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC: {
                switch (call_spvm_method_return_basic_type_id) {
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                    *out_byte_vars = *(int8_t*)&stack[0];
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                    *out_short_vars = *(int16_t*)&stack[0];
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                    *out_int_vars = *(int32_t*)&stack[0];
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                    *out_long_vars = *(int64_t*)&stack[0];
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                    *out_float_vars = *(float*)&stack[0];
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                    *out_double_vars = *(double*)&stack[0];
                    break;
                  }
                  default: {
                    assert(0);
                  }
                }
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING:
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS:
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE:
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT:
              {
                SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out_object_vars, stack[0].oval);
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
              {
                int32_t method_return_class_id = SPVM_API_RUNTIME_get_basic_type_class_id(runtime, call_spvm_method_return_basic_type_id);
                int32_t method_return_class_fields_length = SPVM_API_RUNTIME_get_class_fields_length(runtime, method_return_class_id);
                int32_t method_return_class_fields_base_id = SPVM_API_RUNTIME_get_class_fields_base_id(runtime, method_return_class_id);
                int32_t method_return_mulnum_field_id = method_return_class_fields_base_id;
                int32_t method_return_mulnum_field_type_id = SPVM_API_RUNTIME_get_field_type_id(runtime, method_return_mulnum_field_id);
                int32_t method_return_mulnum_field_type_basic_type_id = SPVM_API_RUNTIME_get_type_basic_type_id(runtime, method_return_mulnum_field_type_id);
                
                switch(method_return_mulnum_field_type_basic_type_id) {
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                    for (int32_t stack_index = 0; stack_index < return_stack_length; stack_index++) {
                      *(out_byte_vars + stack_index) = *(int8_t*)&stack[stack_index];
                    }
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                    for (int32_t stack_index = 0; stack_index < return_stack_length; stack_index++) {
                      *(out_short_vars + stack_index) = *(int16_t*)&stack[stack_index];
                    }
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                    for (int32_t stack_index = 0; stack_index < return_stack_length; stack_index++) {
                      *(out_int_vars + stack_index) = *(int32_t*)&stack[stack_index];
                    }
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                    for (int32_t stack_index = 0; stack_index < return_stack_length; stack_index++) {
                      *(out_long_vars + stack_index) = *(int64_t*)&stack[stack_index];
                    }
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                    for (int32_t stack_index = 0; stack_index < return_stack_length; stack_index++) {
                      *(out_float_vars + stack_index) = *(float*)&stack[stack_index];
                    }
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                    for (int32_t stack_index = 0; stack_index < return_stack_length; stack_index++) {
                      *(out_double_vars + stack_index) = *(double*)&stack[stack_index];
                    }
                    break;
                  }
                  default: {
                    assert(0);
                  }
                }
                break;
              }
              default: {
                assert(0);
              }
            }
          }
          else if (call_spvm_method_return_type_dimension > 0) {
            SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, out_object_vars, stack[0].oval);
          }
          else {
            assert(0);
          }
        }

        break;
      }
    }
    opcode_rel_index++;
  }

  label_END_OF_METHOD: {
  
    // Decrement ref count of return value
    int32_t return_value = 0;
    if (error) {
      return_value = error;
    }
    else {
      int32_t method_return_type_is_object = SPVM_API_RUNTIME_get_type_is_object(runtime, current_method->return_type_id);
      if (method_return_type_is_object) {
        if (*(void**)&stack[0] != NULL) {
          SPVM_IMPLEMENT_DEC_REF_COUNT_ONLY(env, stack, *(void**)&stack[0]);
        }
      }
    }
    
    SPVM_API_free_memory_stack(env, stack, call_stack);
    call_stack = NULL;
    
    return return_value;
  }
}
