#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <inttypes.h>
#include <stdarg.h>

#include "spvm_api.h"
#include "spvm_api_vm.h"
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

static const char* FILE_NAME = "spvm_vm.c";

enum {
  SPVM_API_EXCEPTION_CALL_STACK_ALLOCATION_FAILED,
  SPVM_API_EXCEPTION_VALUE_ASSIGN_NON_ASSIGNABLE_TYPE,
  SPVM_API_EXCEPTION_ASSIGN_READ_ONLY_STRING_TO_MUTABLE_TYPE,
  SPVM_API_EXCEPTION_DIVIDE_ZERO,
  SPVM_API_EXCEPTION_CONCAT_LEFT_UNDEFINED,
  SPVM_API_EXCEPTION_CONCAT_RIGHT_UNDEFINED,
  SPVM_API_EXCEPTION_NEW_OBJECT_FAILED,
  SPVM_API_EXCEPTION_NEW_ARRAY_FAILED,
  SPVM_API_EXCEPTION_ARRRAY_LENGTH_SMALL,
  SPVM_API_EXCEPTION_NEW_STRING_FAILED,
  SPVM_API_EXCEPTION_STRING_LENGTH_SMALL,
  SPVM_API_EXCEPTION_ARRAY_UNDEFINED,
  SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE,
  SPVM_API_EXCEPTION_ELEMENT_ASSIGN_NON_ASSIGNABLE_TYPE,
  SPVM_API_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED,
  SPVM_API_EXCEPTION_UNBOXING_CONVERSION_FROM_UNDEF,
  SPVM_API_EXCEPTION_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE,
  SPVM_API_EXCEPTION_WEAKEN_BACK_REFERENCE_ALLOCATION_FAILED,
  SPVM_API_EXCEPTION_COPY_OPERAND_INVALID,
  SPVM_API_EXCEPTION_ERROR_CODE_TOO_SMALL,
};

static const char* exception_messages[] = {
  "The memory allocation for the call stack failed",
  "The value can't be cast to the non-assignable type",
  "The read-only string can't be cast to the mutable string type",
  "Integral type values can't be divided by 0",
  "The left operand of the \".\" operator must be defined",
  "The right operand of the \".\" operator must be defined",
  "The object creating failed",
  "The array creating failed",
  "The length of the array must be greater than or equal to 0",
  "The string creating failed",
  "The length of the string must be greater than or equal to 0",
  "The array must be defined",
  "The index of the array access must be greater than or equal to 0 and less than the length of the array"
  "The element can't be assigned to the non-assignable type",
  "The unboxing conversion can't be performed on the undefined value",
  "The source of the unboxing conversion must be the corresponding numeric object type",
  "The memory allocation for the weaken back reference failed",
  "The operand of the copy operator must be a string type, a numeric type, or a multi numeric type",
  "The error code must be greater than or equal to 1",
};

int32_t SPVM_API_VM_call_spvm_method_vm(SPVM_ENV* env, SPVM_VALUE* stack, int32_t method_id, int32_t args_stack_length) {
  (void)env;

  // Opcode relative index
  register int32_t opcode_rel_index = 0;
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;

  // Runtime method
  SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
  
  const char* method_name =  SPVM_API_RUNTIME_get_name(runtime, method->name_id);
  
  // Runtime class
  SPVM_RUNTIME_CLASS* class = SPVM_API_RUNTIME_get_class(runtime, method->class_id);

  const char* class_name =  SPVM_API_RUNTIME_get_name(runtime, class->name_id);

  // Operation codes
  SPVM_OPCODE* opcodes = runtime->opcodes;

  // Error
  int32_t error = 0;

  // Caught eval error
  int32_t eval_error = 0;
  
  // Error code value
  int32_t error_code = 1;
  
  // Operation code base
  int32_t method_opcodes_base_id = method->opcodes_base_id;

  // Call method argument stack top
  int32_t stack_index = 0;
  
  // Mortal stack
  uint16_t* mortal_stack = NULL;
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
    numeric_vars_byte_size += method->call_stack_long_vars_length * 8;
    numeric_vars_byte_size += method->call_stack_double_vars_length * 8;
    numeric_vars_byte_size += method->call_stack_int_vars_length * 4;
    numeric_vars_byte_size += method->call_stack_float_vars_length * 4;
    numeric_vars_byte_size += method->call_stack_short_vars_length * 2;
    numeric_vars_byte_size += method->mortal_stack_length * 2;
    numeric_vars_byte_size += method->call_stack_byte_vars_length * 1;
    
    if (numeric_vars_byte_size % 8 != 0) {
      numeric_vars_byte_size += (8 - (numeric_vars_byte_size % 8));
    }
    
    // Address area byte size
    int32_t address_vars_byte_size = 0;
    address_vars_byte_size += method->call_stack_object_vars_length * sizeof(void*);
    address_vars_byte_size += method->call_stack_ref_vars_length * sizeof(void*);
    
    // Total area byte size
    int32_t total_vars_byte_size = numeric_vars_byte_size + address_vars_byte_size;
    
    call_stack = SPVM_API_new_memory_stack(env, stack, total_vars_byte_size + 1);
    if (call_stack == NULL) {
      void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_CALL_STACK_ALLOCATION_FAILED]);
      env->set_exception(env, stack, exception);
      error = 1;
      return error;
    }

    int32_t call_stack_offset = 0;
    
    // Double variables
    double_vars = (double*)&call_stack[call_stack_offset];
    call_stack_offset += method->call_stack_double_vars_length * 8;
    
    // Long varialbes
    long_vars = (int64_t*)&call_stack[call_stack_offset];
    call_stack_offset += method->call_stack_long_vars_length * 8;
    
    // Float variables
    float_vars = (float*)&call_stack[call_stack_offset];
    call_stack_offset += method->call_stack_float_vars_length * 4;
    
    // Int variables
    int_vars = (int32_t*)&call_stack[call_stack_offset];
    call_stack_offset += method->call_stack_int_vars_length * 4;

    // Short variables
    short_vars = (int16_t*)&call_stack[call_stack_offset];
    call_stack_offset += method->call_stack_short_vars_length * 2;

    // Mortal stack
    mortal_stack = (uint16_t*)&call_stack[call_stack_offset];
    call_stack_offset += method->mortal_stack_length * 2;
    
    // Byte variables
    byte_vars = (int8_t*)&call_stack[call_stack_offset];
    call_stack_offset += method->call_stack_byte_vars_length * 1;
    
    call_stack_offset = numeric_vars_byte_size;

    // Object variables
    object_vars = (void**)&call_stack[call_stack_offset];
    call_stack_offset += method->call_stack_object_vars_length * sizeof(void*);
    
    // Refernce variables
    ref_vars = (void**)&call_stack[call_stack_offset];
    call_stack_offset += method->call_stack_ref_vars_length * sizeof(void*);
  }

  // Buffer for string convertion
  // double need 17 digit
  // int64_t need 21 gidit (-9223372036854775808 + (null character))
  char tmp_buffer[256];
  
  int32_t object_header_byte_size = (intptr_t)env->object_header_byte_size;

  // Execute operation codes
  while (1) {
    SPVM_OPCODE* opcode = &(opcodes[method_opcodes_base_id + opcode_rel_index]);
    
    int32_t opcode_id = opcode->id;
    
    switch (opcode_id) {

      case SPVM_OPCODE_C_ID_END_METHOD: {
        goto label_END_OF_METHOD;
      }
      case SPVM_OPCODE_C_ID_GOTO:
        opcode_rel_index = opcode->operand0;
        continue;
      case SPVM_OPCODE_C_ID_IF_EQ_ZERO: {
        if (int_vars[0] == 0) {
          opcode_rel_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_IF_NE_ZERO: {
        if (int_vars[0]) {
          opcode_rel_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_IF_EXCEPTION_CATCH: {
        if (error) {
          eval_error = error;
          error = 0;
          
          int32_t method_id = opcode->operand1;
          SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
          int32_t line = opcode->operand2;
          
          const char* method_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, method->name_id, NULL);
          SPVM_RUNTIME_CLASS* method_class = SPVM_API_RUNTIME_get_class(runtime, method->class_id);
          const char* class_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, method_class->name_id, NULL);
          
          // Exception stack trace
          env->set_exception(env, stack, env->new_stack_trace_raw(env, stack, env->get_exception(env, stack), method_id, line));
          opcode_rel_index = opcode->operand0;
          continue;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_IF_EXCEPTION_RETURN: {
        
        if (error) {
          int32_t method_id = opcode->operand1;
          SPVM_RUNTIME_METHOD* method = SPVM_API_RUNTIME_get_method(runtime, method_id);
          int32_t line = opcode->operand2;
          
          const char* method_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, method->name_id, NULL);
          SPVM_RUNTIME_CLASS* method_class = SPVM_API_RUNTIME_get_class(runtime, method->class_id);
          const char* class_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, method_class->name_id, NULL);

          // Exception stack trace
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
          SPVM_OPCODE* opcode_case_info_min = &(opcodes[method_opcodes_base_id + opcode_rel_index + 1 + 0]);
          int32_t min = opcode_case_info_min->operand1;
          
          // max
          SPVM_OPCODE* opcode_case_info_max = &(opcodes[method_opcodes_base_id + opcode_rel_index + 1 + case_infos_length - 1]);
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
              SPVM_OPCODE* opcode_case_cur_half = &(opcodes[method_opcodes_base_id + opcode_rel_index + 1 + cur_half_pos]);
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
        mortal_stack[mortal_stack_top] = opcode->operand0;
        mortal_stack_top++;
        
        break;
      }
      case SPVM_OPCODE_C_ID_LEAVE_SCOPE: {
        int32_t original_mortal_stack_top = opcode->operand0;
        int32_t mortal_stack_index;
        for (mortal_stack_index = original_mortal_stack_top; mortal_stack_index < mortal_stack_top; mortal_stack_index++) {
          int32_t var_index = mortal_stack[mortal_stack_index];
          void** object_address = (void**)&object_vars[var_index];
          
          if (*(void**)&object_vars[var_index] != NULL) {
            if (SPVM_API_GET_REF_COUNT(env, stack, *object_address) > 1) { SPVM_API_DEC_REF_COUNT_ONLY(env, stack, *object_address); }
            else { env->dec_ref_count(env, stack, *object_address); }
          }
          
          *object_address = NULL;
        }
        
        mortal_stack_top = original_mortal_stack_top;
        
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_BYTE:
        byte_vars[opcode->operand0] = 0;
        break;
      case SPVM_OPCODE_C_ID_INIT_SHORT:
        short_vars[opcode->operand0] = 0;
        break;
      case SPVM_OPCODE_C_ID_INIT_INT:
        int_vars[opcode->operand0] = 0;
        break;
      case SPVM_OPCODE_C_ID_INIT_LONG: {
        long_vars[opcode->operand0] = 0;
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_FLOAT: {
        float_vars[opcode->operand0] = 0;
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_DOUBLE: {
        double_vars[opcode->operand0] = 0;
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_UNDEF:
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], NULL);
        break;
      case SPVM_OPCODE_C_ID_INIT_MULNUM_BYTE: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          byte_vars[opcode->operand0 + field_index] = 0;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_SHORT: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          short_vars[opcode->operand0 + field_index] = 0;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_INT: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          int_vars[opcode->operand0 + field_index] = 0;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_LONG: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          long_vars[opcode->operand0 + field_index] = 0;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_FLOAT: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          float_vars[opcode->operand0 + field_index] = 0;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_DOUBLE: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          double_vars[opcode->operand0 + field_index] = 0;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_BYTE:
        byte_vars[opcode->operand0] = (int8_t)(uint8_t)opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_INT:
        int_vars[opcode->operand0] = (int32_t)opcode->operand1;
        break;
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_LONG: {
        long_vars[opcode->operand0] = *(int64_t*)&opcode->operand1;
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_FLOAT: {
        SPVM_VALUE value;
        value.ival = (int32_t)opcode->operand1;
        float_vars[opcode->operand0] = value.fval;
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_DOUBLE: {
        double_vars[opcode->operand0] = *(double*)&opcode->operand1;
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_BYTE: {
        byte_vars[opcode->operand0] = byte_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_SHORT: {
        short_vars[opcode->operand0] = short_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_INT: {
        int_vars[opcode->operand0] = int_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_LONG: {
        long_vars[opcode->operand0] = long_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_FLOAT: {
        float_vars[opcode->operand0] = float_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_DOUBLE: {
        double_vars[opcode->operand0] = double_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_OBJECT: {
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], *(void**)&object_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECKING: {
        void* object = *(void**)&object_vars[opcode->operand1];
        
        int32_t cast_basic_type_id = opcode->operand2;
        int32_t cast_type_dimension = opcode->operand3;
        
        int32_t isa = env->isa(env, stack, object, cast_basic_type_id, cast_type_dimension);
        if (isa) {
          SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], *(void**)&object_vars[opcode->operand1]);
        }
        else {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_VALUE_ASSIGN_NON_ASSIGNABLE_TYPE]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_OBJECT_CHECK_READ_ONLY: {
        void* string = *(void**)&object_vars[opcode->operand1];
        if (env->is_read_only(env, stack, string)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ASSIGN_READ_ONLY_STRING_TO_MUTABLE_TYPE]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], string);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_UNDEF: {
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], NULL);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_REF: {
        *(void**)&ref_vars[opcode->operand0] = *(void**)&ref_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_ADD_INT: {
        int_vars[opcode->operand0] = int_vars[opcode->operand1] + int_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_ADD_LONG: {
        long_vars[opcode->operand0] = long_vars[opcode->operand1] + long_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_ADD_FLOAT: {
        float_vars[opcode->operand0] = float_vars[opcode->operand1] + float_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_ADD_DOUBLE: {
        double_vars[opcode->operand0] = double_vars[opcode->operand1] + double_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_INT: {
        int_vars[opcode->operand0] = int_vars[opcode->operand1] - int_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_LONG: {
        long_vars[opcode->operand0] = long_vars[opcode->operand1] - long_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_FLOAT: {
        float_vars[opcode->operand0] = float_vars[opcode->operand1] - float_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_DOUBLE: {
        double_vars[opcode->operand0] = double_vars[opcode->operand1] - double_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_INT: {
        int_vars[opcode->operand0] = int_vars[opcode->operand1] * int_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_LONG: {
        long_vars[opcode->operand0] = long_vars[opcode->operand1] * long_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_FLOAT: {
        float_vars[opcode->operand0] = float_vars[opcode->operand1] * float_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_DOUBLE: {
        double_vars[opcode->operand0] = double_vars[opcode->operand1] * double_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_INT: {
        if (__builtin_expect(int_vars[opcode->operand2] == 0, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_DIVIDE_ZERO]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          int_vars[opcode->operand0]
            = int_vars[opcode->operand1] / int_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_LONG: {
        if (__builtin_expect(long_vars[opcode->operand2] == 0, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_DIVIDE_ZERO]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          long_vars[opcode->operand0]
            = long_vars[opcode->operand1] / long_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_FLOAT: {
        float_vars[opcode->operand0]
          = float_vars[opcode->operand1] / float_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_DOUBLE: {
        double_vars[opcode->operand0]
          = double_vars[opcode->operand1] / double_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_UNSIGNED_INT: {
        if (__builtin_expect(int_vars[opcode->operand2] == 0, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_DIVIDE_ZERO]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          int_vars[opcode->operand0]
            = (uint32_t)int_vars[opcode->operand1] / (uint32_t)int_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_UNSIGNED_LONG: {
        if (__builtin_expect(long_vars[opcode->operand2] == 0, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_DIVIDE_ZERO]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          long_vars[opcode->operand0]
            = (uint64_t)long_vars[opcode->operand1] / (uint64_t)long_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_INT: {
        if (__builtin_expect(int_vars[opcode->operand2] == 0, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_DIVIDE_ZERO]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          int_vars[opcode->operand0] = int_vars[opcode->operand1] % int_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_LONG: {
        if (__builtin_expect(long_vars[opcode->operand2] == 0, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_DIVIDE_ZERO]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          long_vars[opcode->operand0] = long_vars[opcode->operand1] % long_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_UNSIGNED_INT: {
        if (__builtin_expect(int_vars[opcode->operand2] == 0, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_DIVIDE_ZERO]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          int_vars[opcode->operand0] = (uint32_t)int_vars[opcode->operand1] % (uint32_t)int_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_UNSIGNED_LONG: {
        if (__builtin_expect(long_vars[opcode->operand2] == 0, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_DIVIDE_ZERO]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          long_vars[opcode->operand0] = (uint64_t)long_vars[opcode->operand1] % (uint64_t)long_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_INT: {
        int_vars[opcode->operand0]
          = int_vars[opcode->operand1] << int_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_LONG: {
        long_vars[opcode->operand0]
          = long_vars[opcode->operand1] << int_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_INT: {
        int_vars[opcode->operand0]
          = int_vars[opcode->operand1] >> int_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_LONG: {
        long_vars[opcode->operand0]
          = long_vars[opcode->operand1] >> int_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_INT: {
        int_vars[opcode->operand0]
          = (int32_t)((uint32_t)int_vars[opcode->operand1] >> int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_LONG: {
        long_vars[opcode->operand0]
          = (int64_t)((uint64_t)long_vars[opcode->operand1] >> int_vars[opcode->operand2]);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_AND_INT: {
        int_vars[opcode->operand0]
          = int_vars[opcode->operand1] & int_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_AND_LONG: {
        long_vars[opcode->operand0]
          = long_vars[opcode->operand1] & long_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_OR_INT: {
        int_vars[opcode->operand0]
          = int_vars[opcode->operand1] | int_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_OR_LONG: {
        long_vars[opcode->operand0]
          = long_vars[opcode->operand1] | long_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_XOR_INT: {
        int_vars[opcode->operand0]
          = int_vars[opcode->operand1] ^ int_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_XOR_LONG: {
        long_vars[opcode->operand0]
          = long_vars[opcode->operand1] ^ long_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_NOT_INT: {
        int_vars[opcode->operand0] = ~int_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_NOT_LONG: {
        long_vars[opcode->operand0] = ~long_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_INT: {
        int_vars[opcode->operand0] = -int_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_LONG: {
        long_vars[opcode->operand0] = -long_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_FLOAT: {
        float_vars[opcode->operand0] = -float_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_DOUBLE: {
        double_vars[opcode->operand0] = -double_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_CONCAT: {
        
        void* string1 = *(void**)&object_vars[opcode->operand1];
        void* string2 = *(void**)&object_vars[opcode->operand2];
        if (string1 == NULL) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_CONCAT_LEFT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else if (string2 == NULL) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_CONCAT_RIGHT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          void* string3 = env->concat_raw(env, stack, string1, string2);
          SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], string3);
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_INT: {
        int_vars[0] = int_vars[opcode->operand1] == int_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_LONG: {
        int_vars[0] = long_vars[opcode->operand1] == long_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_FLOAT: {
        int_vars[0] = float_vars[opcode->operand1] == float_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_DOUBLE: {
        int_vars[0] = double_vars[opcode->operand1] == double_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_OBJECT: {
        int_vars[0] = *(void**)&object_vars[opcode->operand1] == *(void**)&object_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_NE_INT: {
        int_vars[0] = int_vars[opcode->operand1] != int_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_NE_LONG: {
        int_vars[0] = long_vars[opcode->operand1] != long_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_NE_FLOAT: {
        int_vars[0] = float_vars[opcode->operand1] != float_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_NE_DOUBLE: {
        int_vars[0] = double_vars[opcode->operand1] != double_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_NE_OBJECT: {
        int_vars[0] = *(void**)&object_vars[opcode->operand1] != *(void**)&object_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_GT_INT: {
        int_vars[0] = int_vars[opcode->operand1] > int_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_GT_LONG: {
        int_vars[0] = long_vars[opcode->operand1] > long_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_GT_FLOAT: {
        int_vars[0] = float_vars[opcode->operand1] > float_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_GT_DOUBLE: {
        int_vars[0] = double_vars[opcode->operand1] > double_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_GE_INT: {
        int_vars[0] = int_vars[opcode->operand1] >= int_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_GE_LONG: {
        int_vars[0] = long_vars[opcode->operand1] >= long_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_GE_FLOAT: {
        int_vars[0] = float_vars[opcode->operand1] >= float_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_GE_DOUBLE: {
        int_vars[0] = double_vars[opcode->operand1] >= double_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_LT_INT: {
        int_vars[0] = int_vars[opcode->operand1] < int_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_LT_LONG: {
        int_vars[0] = long_vars[opcode->operand1] < long_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_LT_FLOAT: {
        int_vars[0] = float_vars[opcode->operand1] < float_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_LT_DOUBLE: {
        int_vars[0] = double_vars[opcode->operand1] < double_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_LE_INT: {
        int_vars[0] = int_vars[opcode->operand1] <= int_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_LE_LONG: {
        int_vars[0] = long_vars[opcode->operand1] <= long_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_LE_FLOAT: {
        int_vars[0] = float_vars[opcode->operand1] <= float_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_LE_DOUBLE: {
        int_vars[0] = double_vars[opcode->operand1] <= double_vars[opcode->operand2];
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_INT: {
        int_vars[0] = int_vars[opcode->operand1] > int_vars[opcode->operand2] ? 1
                    : int_vars[opcode->operand1] < int_vars[opcode->operand2] ? -1
                    : 0;
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_LONG: {
        int_vars[0] = long_vars[opcode->operand1] > long_vars[opcode->operand2] ? 1
                    : long_vars[opcode->operand1] < long_vars[opcode->operand2] ? -1
                    : 0;
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_FLOAT: {
        int_vars[0] = float_vars[opcode->operand1] > float_vars[opcode->operand2] ? 1
                    : float_vars[opcode->operand1] < float_vars[opcode->operand2] ? -1
                    : 0;
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_DOUBLE: {
        int_vars[0] = double_vars[opcode->operand1] > double_vars[opcode->operand2] ? 1
                    : double_vars[opcode->operand1] < double_vars[opcode->operand2] ? -1
                    : 0;
        break;
      }
      case SPVM_OPCODE_C_ID_IS_UNDEF: {
        int_vars[0] = *(void**)&object_vars[opcode->operand1] == NULL;
        break;
      }
      case SPVM_OPCODE_C_ID_IS_NOT_UNDEF: {
        int_vars[0] = *(void**)&object_vars[opcode->operand1] != NULL;
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_EQ:
      case SPVM_OPCODE_C_ID_STRING_NE:
      case SPVM_OPCODE_C_ID_STRING_GT:
      case SPVM_OPCODE_C_ID_STRING_GE:
      case SPVM_OPCODE_C_ID_STRING_LT:
      case SPVM_OPCODE_C_ID_STRING_LE:
      case SPVM_OPCODE_C_ID_STRING_CMP:
      {
        void* object1 = *(void**)&object_vars[opcode->operand1];
        void* object2 = *(void**)&object_vars[opcode->operand2];
        
        if (object1 == NULL && object2 == NULL) {
         switch (opcode_id) {
            case SPVM_OPCODE_C_ID_STRING_EQ: {
              int_vars[0] = 1;
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_NE: {
              int_vars[0] = 0;
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_GT: {
              int_vars[0] = 0;
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_GE: {
              int_vars[0] = 1;
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_LT: {
              int_vars[0] = 0;
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_LE: {
              int_vars[0] = 1;
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_CMP: {
              int_vars[0] = 0;
              break;
            }
          }
        }
        else if (object1 != NULL && object2 == NULL) {
          switch (opcode_id) {
            case SPVM_OPCODE_C_ID_STRING_EQ: {
              int_vars[0] = 0;
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_NE: {
              int_vars[0] = 1;
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_GT: {
              int_vars[0] = 1;
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_GE: {
              int_vars[0] = 1;
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_LT: {
              int_vars[0] = 0;
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_LE: {
              int_vars[0] = 0;
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_CMP: {
              int_vars[0] = 1;
              break;
            }
          }
        }
        else if (object1 == NULL && object2 != NULL) {
          switch (opcode_id) {
            case SPVM_OPCODE_C_ID_STRING_EQ: {
              int_vars[0] = 0;
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_NE: {
              int_vars[0] = 1;
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_GT: {
              int_vars[0] = 0;
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_GE: {
              int_vars[0] = 0;
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_LT: {
              int_vars[0] = 1;
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_LE: {
              int_vars[0] = 1;
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_CMP: {
              int_vars[0] = -1;
              break;
            }
          }
        }
        else {
          int32_t length1 = *(int32_t*)((intptr_t)object1 + (intptr_t)env->object_length_offset);
          int32_t length2 = *(int32_t*)((intptr_t)object2 + (intptr_t)env->object_length_offset);
          
          const char* bytes1 = env->get_chars(env, stack, object1);
          const char* bytes2 = env->get_chars(env, stack, object2);
          
          int32_t short_string_length = length1 < length2 ? length1 : length2;
          int32_t retval = memcmp(bytes1, bytes2, short_string_length);
          int32_t cmp;
          if (retval) {
            cmp = retval < 0 ? -1 : 1;
          } else if (length1 == length2) {
            cmp = 0;
          } else {
            cmp = length1 < length2 ? -1 : 1;
          }
          
          switch (opcode_id) {
            case SPVM_OPCODE_C_ID_STRING_EQ: {
              int_vars[0] = (cmp == 0);
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_NE: {
              int_vars[0] = (cmp != 0);
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_GT: {
              int_vars[0] = (cmp == 1);
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_GE: {
              int_vars[0] = (cmp >= 0);
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_LT: {
              int_vars[0] = (cmp == -1);
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_LE: {
              int_vars[0] = (cmp <= 0);
              break;
            }
            case SPVM_OPCODE_C_ID_STRING_CMP: {
              int_vars[0] = cmp;
              break;
            }
          }
        }

        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT: {
        int32_t basic_type_id = opcode->operand1;
        
        void* object = env->new_object_raw(env, stack, basic_type_id);
        if (object == NULL) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_NEW_OBJECT_FAILED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          // Push object
          SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], object);
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        
        int32_t length = int_vars[opcode->operand2];
        if (length >= 0) {
          void* object = env->new_object_array_raw(env, stack, basic_type_id, length);
          if (object == NULL) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_NEW_ARRAY_FAILED]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], object);
          }
        }
        else {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRRAY_LENGTH_SMALL]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULTI_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        int32_t element_dimension = opcode->operand3;
        int32_t length = int_vars[opcode->operand2];
        
        if (length >= 0) {
          void* object = env->new_muldim_array_raw(env, stack, basic_type_id, element_dimension, length);
          if (object == NULL) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_NEW_ARRAY_FAILED]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], object);
          }
        }
        else {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRRAY_LENGTH_SMALL]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULNUM_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        
        int32_t length = int_vars[opcode->operand2];
        
        if (length >= 0) {
          void* object = env->new_mulnum_array_raw(env, stack, basic_type_id, length);
          if (object == NULL) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_NEW_ARRAY_FAILED]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], object);
          }
        }
        else {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRRAY_LENGTH_SMALL]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_BYTE_ARRAY: {
        int32_t length = int_vars[opcode->operand1];
        if (length >= 0) {
          void* object = env->new_byte_array_raw(env, stack, length);
          if (object == NULL) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_NEW_ARRAY_FAILED]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], object);
          }
        }
        else {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRRAY_LENGTH_SMALL]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY: {
        
        // length
        int32_t length = int_vars[opcode->operand1];
        
        if (length >= 0) {
          void* object = env->new_short_array_raw(env, stack, length);
          if (object == NULL) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_NEW_ARRAY_FAILED]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            // Set array
            SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], object);
          }
        }
        else {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRRAY_LENGTH_SMALL]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_INT_ARRAY: {
        
        // length
        int32_t length = int_vars[opcode->operand1];
        
        if (length >= 0) {
          void* object = env->new_int_array_raw(env, stack, length);
          if (object == NULL) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_NEW_ARRAY_FAILED]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            // Set array
            SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], object);
          }
        }
        else {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRRAY_LENGTH_SMALL]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_LONG_ARRAY: {
        
        int32_t length = int_vars[opcode->operand1];
        if (length >= 0) {
          void* object = env->new_long_array_raw(env, stack, length);
          if (object == NULL) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_NEW_ARRAY_FAILED]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], object);
          }
        }
        else {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRRAY_LENGTH_SMALL]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY: {
        
        int32_t length = int_vars[opcode->operand1];
        if (length >= 0) {
          void* object = env->new_float_array_raw(env, stack, length);
          if (object == NULL) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_NEW_ARRAY_FAILED]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], object);
          }
        }
        else {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRRAY_LENGTH_SMALL]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY: {
        
        int32_t length = int_vars[opcode->operand1];
        if (length >= 0) {
          void* object = env->new_double_array_raw(env, stack, length);
          if (object == NULL) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_NEW_ARRAY_FAILED]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], object);
          }
        }
        else {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRRAY_LENGTH_SMALL]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING: {
        int32_t constant_string_id = opcode->operand1;
        int32_t constant_string_length;
        const char* constant_string = SPVM_API_RUNTIME_get_constant_string_value(runtime, constant_string_id, &constant_string_length);
        void* string = env->new_string_raw(env, stack, constant_string, constant_string_length);
        if (string == NULL) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_NEW_STRING_FAILED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          env->make_read_only(env, stack, string);
          SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0] , string);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING_LEN: {
        int32_t length = int_vars[opcode->operand1];
        if (length >= 0) {
          void* string = env->new_string_raw(env, stack, NULL, length);
          if (string == NULL) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_NEW_STRING_FAILED]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], string);
          }
        }
        else {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_STRING_LENGTH_SMALL]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_IS_READ_ONLY: {
        void* string = *(void**)&object_vars[opcode->operand1];
        int32_t is_read_only = env->is_read_only(env, stack, string);
        int_vars[0] = is_read_only;
        break;
      }
      case SPVM_OPCODE_C_ID_MAKE_READ_ONLY: {
        void* string = object_vars[opcode->operand0];
        env->make_read_only(env, stack, string);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_BYTE: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            byte_vars[opcode->operand0] = ((int8_t*)((intptr_t)array + object_header_byte_size))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_SHORT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            short_vars[opcode->operand0] = ((int16_t*)((intptr_t)array + object_header_byte_size))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_INT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            int_vars[opcode->operand0] = ((int32_t*)((intptr_t)array + object_header_byte_size))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_LONG: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            long_vars[opcode->operand0] = ((int64_t*)((intptr_t)array + object_header_byte_size))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_FLOAT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            float_vars[opcode->operand0] = ((float*)((intptr_t)array + object_header_byte_size))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_DOUBLE: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            double_vars[opcode->operand0] = ((double*)((intptr_t)array + object_header_byte_size))[index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_OBJECT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            void* object = ((void**)((intptr_t)array + object_header_byte_size))[index];
            SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], object);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_BYTE: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            ((int8_t*)((intptr_t)array + object_header_byte_size))[index] = byte_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_SHORT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
           ((int16_t*)((intptr_t)array + object_header_byte_size))[index] = short_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_INT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            ((int32_t*)((intptr_t)array + object_header_byte_size))[index] = int_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_LONG: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            ((int64_t*)((intptr_t)array + object_header_byte_size))[index] = long_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_FLOAT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            ((float*)((intptr_t)array + object_header_byte_size))[index] = float_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_DOUBLE: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            ((double*)((intptr_t)array + object_header_byte_size))[index] = double_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_OBJECT: {
        
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            void** element_address = &((void**)((intptr_t)array + object_header_byte_size))[index];
            SPVM_API_OBJECT_ASSIGN(env, stack, element_address, *(void**)&object_vars[opcode->operand2]);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE: {
        
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            void** element_address = &((void**)((intptr_t)array + object_header_byte_size))[index];
            void* object = *(void**)&object_vars[opcode->operand2];
            int32_t elem_isa = env->elem_isa(env, stack, array, object);
            if (elem_isa) {
              SPVM_API_OBJECT_ASSIGN(env, stack, element_address, object);
            }
            else {
              void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ELEMENT_ASSIGN_NON_ASSIGNABLE_TYPE]);
              env->set_exception(env, stack, exception);
              error = 1;
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_UNDEF: {
        
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            void* object_address = &((void**)((intptr_t)array + object_header_byte_size))[index];
            SPVM_API_OBJECT_ASSIGN(env, stack, object_address, NULL);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LENGTH: {
        if (*(void**)&object_vars[opcode->operand1] == NULL) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          int_vars[opcode->operand0] = *(int32_t*)((intptr_t)*(void**)&object_vars[opcode->operand1] + (intptr_t)env->object_length_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_BYTE: {
        int32_t field_id = opcode->operand2;
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
        int32_t field_offset = field->offset;

        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          byte_vars[opcode->operand0] = *(int8_t*)((intptr_t)object + object_header_byte_size + field_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_SHORT: {
        int32_t field_id = opcode->operand2;
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
        int32_t field_offset = field->offset;

        void* object = *(void**)&object_vars[opcode->operand1];

        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          short_vars[opcode->operand0] = *(int16_t*)((intptr_t)object + object_header_byte_size + field_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_INT: {
        int32_t field_id = opcode->operand2;
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
        int32_t field_offset = field->offset;

        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          int_vars[opcode->operand0] = *(int32_t*)((intptr_t)object + object_header_byte_size + field_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_LONG: {
        int32_t field_id = opcode->operand2;
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
        int32_t field_offset = field->offset;

        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          long_vars[opcode->operand0] = *(int64_t*)((intptr_t)object + object_header_byte_size + field_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_FLOAT: {
        int32_t field_id = opcode->operand2;
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
        int32_t field_offset = field->offset;

        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          float_vars[opcode->operand0] = *(float*)((intptr_t)object + object_header_byte_size + field_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE: {
        int32_t field_id = opcode->operand2;
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
        int32_t field_offset = field->offset;

        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          double_vars[opcode->operand0] = *(double*)((intptr_t)object + object_header_byte_size + field_offset);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_OBJECT: {
        int32_t field_id = opcode->operand2;
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
        int32_t field_offset = field->offset;

        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          void* get_field_object = *(void**)((intptr_t)object + object_header_byte_size + field_offset);
          SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], get_field_object);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_BYTE: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
        int32_t field_offset = field->offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          *(int8_t*)((intptr_t)object + object_header_byte_size + field_offset) = byte_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_SHORT: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
        int32_t field_offset = field->offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          *(int16_t*)((intptr_t)object + object_header_byte_size + field_offset) = short_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_INT: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
        int32_t field_offset = field->offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          *(int32_t*)((intptr_t)object + object_header_byte_size + field_offset) = int_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_LONG: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
        int32_t field_offset = field->offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          *(int64_t*)((intptr_t)object + object_header_byte_size + field_offset) = long_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_FLOAT: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
        int32_t field_offset = field->offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          *(float*)((intptr_t)object + object_header_byte_size + field_offset) = float_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
        int32_t field_offset = field->offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          *(double*)((intptr_t)object + object_header_byte_size + field_offset) = double_vars[opcode->operand2];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_OBJECT: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
        int32_t field_offset = field->offset;
        
        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          void* get_field_object_address = (void**)((intptr_t)object + object_header_byte_size + field_offset);
          SPVM_API_OBJECT_ASSIGN(env, stack, get_field_object_address, *(void**)&object_vars[opcode->operand2]);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_UNDEF: {
        void* object = *(void**)&object_vars[opcode->operand0];
        int32_t field_id = opcode->operand1;
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
        int32_t field_offset = field->offset;

        if (__builtin_expect(object == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          void* get_field_object_address = (void**)((intptr_t)object + object_header_byte_size + field_offset);
          SPVM_API_OBJECT_ASSIGN(env, stack, get_field_object_address, NULL);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_BYTE: {
        int32_t class_var_id = opcode->operand1;
        
        byte_vars[opcode->operand0] = *(int8_t*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_SHORT: {
        int32_t class_var_id = opcode->operand1;
        
        short_vars[opcode->operand0] = *(int16_t*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_INT: {
        
        int32_t class_var_id = opcode->operand1;
        
        int_vars[opcode->operand0] = *(int32_t*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_LONG: {
        int32_t class_var_id = opcode->operand1;
        
        long_vars[opcode->operand0] = *(int64_t*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_FLOAT: {
        int32_t class_var_id = opcode->operand1;
        
        float_vars[opcode->operand0] = *(float*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_DOUBLE: {
        int32_t class_var_id = opcode->operand1;
        
        double_vars[opcode->operand0] = *(double*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id];
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_OBJECT: {
        int32_t class_var_id = opcode->operand1;
        
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], *(void**)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id]);
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_BYTE: {
        int32_t class_var_id = opcode->operand0;
        
        *(int8_t*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id] = byte_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_SHORT: {
        int32_t class_var_id = opcode->operand0;
        
        *(int16_t*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id] = short_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_INT: {
        int32_t class_var_id = opcode->operand0;
        
        *(int32_t*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id] = int_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_LONG: {
        int32_t class_var_id = opcode->operand0;
        
        *(int64_t*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id] = long_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_FLOAT: {
        int32_t class_var_id = opcode->operand0;
        
        *(float*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id] = float_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_DOUBLE: {
        int32_t class_var_id = opcode->operand0;
        
        *(double*)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id] = double_vars[opcode->operand1];
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_OBJECT: {
        int32_t class_var_id = opcode->operand0;
        
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id], *(void**)&object_vars[opcode->operand1]);
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_UNDEF: {
        int32_t class_var_id = opcode->operand0;
        
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&((SPVM_VALUE*)env->class_vars_heap)[class_var_id], NULL);
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_EXCEPTION_VAR: {
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], env->get_exception(env, stack));
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR: {
        
        env->set_exception(env, stack, *(void**)&object_vars[opcode->operand0]);
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR_UNDEF: {
        
        env->set_exception(env, stack, NULL);
        
        break;
      }
      case SPVM_OPCODE_C_ID_ISA: {
        void* object = *(void**)&object_vars[opcode->operand1];
        int32_t dist_basic_type_id = opcode->operand2;
        int32_t dist_type_dimension = opcode->operand3;

        if (object) {
          int_vars[0] = env->isa(env, stack, object, dist_basic_type_id, dist_type_dimension);
        }
        else {
          int_vars[0] = 0;
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_IS_TYPE: {
        void* object = *(void**)&object_vars[opcode->operand1];
        int32_t dist_basic_type_id = opcode->operand2;
        int32_t dist_type_dimension = opcode->operand3;

        if (object) {
          int_vars[0] = env->is_type(env, stack, object, dist_basic_type_id, dist_type_dimension);
        }
        else {
          int_vars[0] = 0;
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_HAS_IMPL: {
        int32_t implement_method_id = opcode->operand1;
        SPVM_RUNTIME_METHOD* implement_method = SPVM_API_RUNTIME_get_method(runtime, implement_method_id);
        const char* implement_method_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, implement_method->name_id, NULL);
        
        int32_t interface_basic_type_id = opcode->operand2;
        SPVM_RUNTIME_BASIC_TYPE* interface_basic_type = SPVM_API_RUNTIME_get_basic_type(runtime, interface_basic_type_id);
        SPVM_RUNTIME_CLASS* interface = SPVM_API_RUNTIME_get_class(runtime, interface_basic_type->class_id);
        SPVM_RUNTIME_METHOD* interface_method = SPVM_API_RUNTIME_get_method_by_class_id_and_method_name(runtime, interface->id, implement_method_name);
        
        void* object = *(void**)&object_vars[opcode->operand0];
        
        int32_t call_method_id = env->get_instance_method_id(env, object, implement_method_name);
        
        int_vars[0] = call_method_id >= 0;

        break;
      }
      case SPVM_OPCODE_C_ID_PRINT: {
        void* object = object_vars[opcode->operand0];
        if (object) {
          const char* bytes = env->get_chars(env, stack, object);
          int32_t string_length = env->length(env, stack, object);
          
          if (string_length > 0) {
            size_t ret = fwrite(bytes, 1, string_length, stdout);
          }
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_WARN: {
        int32_t line = opcode->operand1;
        
        const char* module_dir = NULL;
        const char* module_dir_sep;
        int32_t module_dir_id = class->module_dir_id;
        if (module_dir_id >= 0) {
          module_dir_sep = "/";
          module_dir = SPVM_API_RUNTIME_get_constant_string_value(runtime, class->module_dir_id, NULL);
        }
        else {
          module_dir_sep = "";
          module_dir = "";
        }
        const char* module_rel_file = SPVM_API_RUNTIME_get_constant_string_value(runtime, class->module_rel_file_id, NULL);

        void* object = object_vars[opcode->operand0];
        
        int32_t empty_or_undef = 0;
        if (object) {
          const char* bytes = env->get_chars(env, stack, object);
          int32_t string_length = env->length(env, stack, object);

          if (string_length > 0) {
            size_t ret = fwrite(bytes, 1, string_length, stderr);
            // Add line and file information if last character is not '\n'
            int32_t add_line_file;
            if (bytes[string_length - 1] != '\n') {
              fprintf(stderr, " at %s%s%s line %d\n", module_dir, module_dir_sep, module_rel_file, line);
            }
          }
          else {
            empty_or_undef = 1;
          }
        }
        else {
          empty_or_undef = 1;
        }
        
        if (empty_or_undef) {
          fprintf(stderr, "Warning: something's wrong at %s%s%s line %d\n", module_dir, module_dir_sep, module_rel_file, line);
        }
        
        fflush(stderr);
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ERROR_CODE: {
        int_vars[opcode->operand0] = error_code;
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ERROR_CODE: {
        int32_t tmp_error_code = int_vars[opcode->operand1];
        if (tmp_error_code < 1) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ERROR_CODE_TOO_SMALL]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          error_code = tmp_error_code;
          int_vars[opcode->operand0] = error_code;
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CLEAR_EVAL_ERROR: {
        eval_error = 0;
        break;
      }
      case SPVM_OPCODE_C_ID_GET_EVAL_ERROR: {
        int_vars[opcode->operand0] = eval_error;
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_ID: {
        int32_t class_id = opcode->operand1;
        int_vars[opcode->operand0] = class_id;
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ERROR: {
        error = error_code;
        break;
      }
      case SPVM_OPCODE_C_ID_REFOP: {
        void* object = object_vars[opcode->operand1];
        if (object == NULL) {
          object_vars[opcode->operand0] = NULL;
        }
        else {
          void* type_name = env->get_type_name_raw(env, stack, object);
          SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], type_name);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_DUMP: {
        void* object = object_vars[opcode->operand1];
        void* dump = env->dump_raw(env, stack, object);
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], dump);
        break;
      }
      case SPVM_OPCODE_C_ID_COPY: {
        void* object = *(void**)&object_vars[opcode->operand1];
        
        if (object) {
          if (!(env->is_string(env, stack, object) || env->is_numeric_array(env, stack, object) || env->is_mulnum_array(env, stack, object))) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_COPY_OPERAND_INVALID]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            void* new_object_raw = env->copy_raw(env, stack, object);
            SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], new_object_raw);
          }
        }
        else {
          SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], NULL);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_REF_BYTE:
        *(void**)&ref_vars[opcode->operand0] = &byte_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_REF_SHORT:
        *(void**)&ref_vars[opcode->operand0] = &short_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_REF_INT:
        *(void**)&ref_vars[opcode->operand0] = &int_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_REF_LONG:
        *(void**)&ref_vars[opcode->operand0] = &long_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_REF_FLOAT:
        *(void**)&ref_vars[opcode->operand0] = &float_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_REF_DOUBLE:
        *(void**)&ref_vars[opcode->operand0] = &double_vars[opcode->operand1];
        break;
      case SPVM_OPCODE_C_ID_GET_DEREF_BYTE: {
        byte_vars[opcode->operand0] = *(int8_t*)*(void**)&ref_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_SHORT: {
        short_vars[opcode->operand0] = *(int16_t*)*(void**)&ref_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_INT: {
        int_vars[opcode->operand0] = *(int32_t*)*(void**)&ref_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_LONG: {
        long_vars[opcode->operand0] = *(int64_t*)*(void**)&ref_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_FLOAT: {
        float_vars[opcode->operand0] = *(float*)*(void**)&ref_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_DOUBLE: {
        double_vars[opcode->operand0] = *(double*)*(void**)&ref_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_BYTE: {
        *(int8_t*)*(void**)&ref_vars[opcode->operand0] = byte_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_SHORT: {
        *(int16_t*)*(void**)&ref_vars[opcode->operand0] = short_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_INT: {
        *(int32_t*)*(void**)&ref_vars[opcode->operand0] = int_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_LONG: {
        *(int64_t*)*(void**)&ref_vars[opcode->operand0] = long_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_FLOAT: {
        *(float*)*(void**)&ref_vars[opcode->operand0] = float_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_DOUBLE: {
        *(double*)*(void**)&ref_vars[opcode->operand0] = double_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        byte_vars[opcode->operand0] = byte_vars[opcode->operand1 + field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        short_vars[opcode->operand0] = short_vars[opcode->operand1 + field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        int_vars[opcode->operand0] = int_vars[opcode->operand1 + field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        long_vars[opcode->operand0] = long_vars[opcode->operand1 + field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        float_vars[opcode->operand0] = float_vars[opcode->operand1 + field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        double_vars[opcode->operand0] = double_vars[opcode->operand1 + field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        byte_vars[opcode->operand0 + field_index] = byte_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        short_vars[opcode->operand0 + field_index] = short_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        int_vars[opcode->operand0 + field_index] = int_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        long_vars[opcode->operand0 + field_index] = long_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        float_vars[opcode->operand0 + field_index] = float_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        double_vars[opcode->operand0 + field_index] = double_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_BYTE: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          byte_vars[opcode->operand0 + field_index] = byte_vars[opcode->operand1 + field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_SHORT: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          short_vars[opcode->operand0 + field_index] = short_vars[opcode->operand1 + field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_INT: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          int_vars[opcode->operand0 + field_index] = int_vars[opcode->operand1 + field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_LONG: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          long_vars[opcode->operand0 + field_index] = long_vars[opcode->operand1 + field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_FLOAT: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          float_vars[opcode->operand0 + field_index] = float_vars[opcode->operand1 + field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_DOUBLE: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          double_vars[opcode->operand0 + field_index] = double_vars[opcode->operand1 + field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_BYTE: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < fields_length; field_index++) {
              byte_vars[opcode->operand0 + field_index] = ((int8_t*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_SHORT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            for (int32_t field_index = 0; field_index < fields_length; field_index++) {
              short_vars[opcode->operand0 + field_index] = ((int16_t*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_INT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            for (int32_t field_index = 0; field_index < fields_length; field_index++) {
              int_vars[opcode->operand0 + field_index] = ((int32_t*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_LONG: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < fields_length; field_index++) {
              long_vars[opcode->operand0 + field_index] = ((int64_t*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FLOAT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < fields_length; field_index++) {
              float_vars[opcode->operand0 + field_index] = ((float*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_DOUBLE: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = opcode->operand3;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < fields_length; field_index++) {
              double_vars[opcode->operand0 + field_index] = ((double*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_BYTE: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < fields_length; field_index++) {
              ((int8_t*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index] = byte_vars[opcode->operand2 + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_SHORT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < fields_length; field_index++) {
              ((int16_t*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index] = short_vars[opcode->operand2 + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_INT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < fields_length; field_index++) {
              ((int32_t*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index] = int_vars[opcode->operand2 + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_LONG: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < fields_length; field_index++) {
              ((int64_t*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index] = long_vars[opcode->operand2 + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FLOAT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < fields_length; field_index++) {
              ((float*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index] = float_vars[opcode->operand2 + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_DOUBLE: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            int32_t field_index;
            for (field_index = 0; field_index < fields_length; field_index++) {
              ((double*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index] = double_vars[opcode->operand2 + field_index];
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_BYTE: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            byte_vars[opcode->operand0] = ((int8_t*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_SHORT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            short_vars[opcode->operand0] = ((int16_t*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_INT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            int_vars[opcode->operand0] = ((int32_t*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_LONG: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            long_vars[opcode->operand0] = ((int64_t*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_FLOAT: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            float_vars[opcode->operand0] = ((float*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_DOUBLE: {
        void* array = *(void**)&object_vars[opcode->operand1];
        int32_t index = int_vars[opcode->operand2];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        
        if (__builtin_expect(array == NULL, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            double_vars[opcode->operand0] = ((double*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_BYTE: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            ((int8_t*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index] = byte_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_SHORT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            ((int16_t*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index] = short_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_INT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            ((int32_t*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index] = int_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_LONG: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            ((int64_t*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index] = long_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_FLOAT: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            ((float*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index] = float_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_DOUBLE: {
        void* array = *(void**)&object_vars[opcode->operand0];
        int32_t index = int_vars[opcode->operand1];
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        if (__builtin_expect(!array, 0)) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_ARRAY_ACCESS_INDEX_OUT_OF_RANGE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
          else {
            ((double*)((intptr_t)array + object_header_byte_size))[fields_length * index + field_index] = double_vars[opcode->operand2];
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_BYTE: {
        int8_t* value_ref = *(int8_t**)&ref_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          byte_vars[opcode->operand0 + field_index] = value_ref[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_SHORT: {
        int16_t* value_ref = *(int16_t**)&ref_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          short_vars[opcode->operand0 + field_index] = value_ref[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_INT: {
        int32_t* value_ref = *(int32_t**)&ref_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          int_vars[opcode->operand0 + field_index] = value_ref[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_LONG: {
        int64_t* value_ref = *(int64_t**)&ref_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          long_vars[opcode->operand0 + field_index] = value_ref[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_FLOAT: {
        float* value_ref = *(float**)&ref_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          float_vars[opcode->operand0 + field_index] = value_ref[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_DOUBLE: {
        double* value_ref = *(double**)&ref_vars[opcode->operand1];
        int32_t fields_length = opcode->operand3;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          double_vars[opcode->operand0 + field_index] = value_ref[field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_BYTE: {
        int8_t* value_ref = *(int8_t**)&ref_vars[opcode->operand1];
        int32_t field_index = opcode->operand2;
        byte_vars[opcode->operand0] = value_ref[field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_SHORT: {
        int16_t* value_ref = *(int16_t**)&ref_vars[opcode->operand1];
        int32_t field_index = opcode->operand2;
        short_vars[opcode->operand0] = value_ref[field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_INT: {
        int32_t* value_ref = *(int32_t**)&ref_vars[opcode->operand1];
        int32_t field_index = opcode->operand2;
        int_vars[opcode->operand0] = value_ref[field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_LONG: {
        int64_t* value_ref = *(int64_t**)&ref_vars[opcode->operand1];
        int32_t field_index = opcode->operand2;
        long_vars[opcode->operand0] = value_ref[field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_FLOAT: {
        float* value_ref = *(float**)&ref_vars[opcode->operand1];
        int32_t field_index = opcode->operand2;
        float_vars[opcode->operand0] = value_ref[field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_DOUBLE: {
        double* value_ref = *(double**)&ref_vars[opcode->operand1];
        int32_t field_index = opcode->operand2;
        double_vars[opcode->operand0] = value_ref[field_index];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_BYTE: {
        int8_t* value_ref = *(int8_t**)&ref_vars[opcode->operand0];
        int32_t field_index = opcode->operand2;
        value_ref[field_index] = byte_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_SHORT: {
        int16_t* value_ref = *(int16_t**)&ref_vars[opcode->operand0];
        int32_t field_index = opcode->operand2;
        value_ref[field_index] = short_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_INT: {
        int32_t* value_ref = *(int32_t**)&ref_vars[opcode->operand0];
        int32_t field_index = opcode->operand2;
        value_ref[field_index] = int_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_LONG: {
        int64_t* value_ref = *(int64_t**)&ref_vars[opcode->operand0];
        int32_t field_index = opcode->operand2;
        value_ref[field_index] = long_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_FLOAT: {
        float* value_ref = *(float**)&ref_vars[opcode->operand0];
        int32_t field_index = opcode->operand2;
        value_ref[field_index] = float_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_DOUBLE: {
        double* value_ref = *(double**)&ref_vars[opcode->operand0];
        int32_t field_index = opcode->operand2;
        value_ref[field_index] = double_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_WEAKEN_FIELD: {
        int32_t field_id = opcode->operand1;
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
        int32_t field_offset = field->offset;
        void* object = *(void**)&object_vars[opcode->operand0];
        if (object == NULL) {
          SPVM_OBJECT* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          void** get_field_object_address = (void**)((intptr_t)object + object_header_byte_size + field_offset);
          int32_t status = env->weaken(env, stack, get_field_object_address);
          if (status != 0) {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_WEAKEN_BACK_REFERENCE_ALLOCATION_FAILED]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_UNWEAKEN_FIELD: {
        int32_t field_id = opcode->operand1;
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
        int32_t field_offset = field->offset;
        void* object = *(void**)&object_vars[opcode->operand0];
        if (object == NULL) {
          SPVM_OBJECT* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          void** get_field_object_address = (void**)((intptr_t)object + object_header_byte_size + field_offset);
          env->unweaken(env, stack, get_field_object_address);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_ISWEAK_FIELD: {
        int32_t field_id = opcode->operand2;
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field(runtime, field_id);
        int32_t field_offset = field->offset;
        void* object = *(void**)&object_vars[opcode->operand1];
        if (object == NULL) {
          SPVM_OBJECT* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_FIELD_ACCESS_INVOCANT_UNDEFINED]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          void** get_field_object_address = (void**)((intptr_t)object + object_header_byte_size + field_offset);
          int_vars[0] = env->isweak(env, stack, get_field_object_address);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_REFCNT: {
        void* object = object_vars[opcode->operand1];
        if (object == NULL) {
          int_vars[opcode->operand0] = 0;
        }
        else {
          int_vars[opcode->operand0] = env->get_ref_count(env, stack, object);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_SHORT: {
        short_vars[opcode->operand0] = (int16_t)byte_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_INT: {
        int_vars[opcode->operand0] = (int32_t)byte_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_LONG: {
        long_vars[opcode->operand0] = (int64_t)byte_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_FLOAT: {
        float_vars[opcode->operand0] = (float)byte_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_DOUBLE: {
        double_vars[opcode->operand0] = (double)byte_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_BYTE: {
        byte_vars[opcode->operand0] = (int8_t)short_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_INT: {
        int_vars[opcode->operand0] = (int32_t)short_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_LONG: {
        long_vars[opcode->operand0] = (int64_t)short_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_FLOAT: {
        float_vars[opcode->operand0] = (float)short_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_DOUBLE: {
        double_vars[opcode->operand0] = (double)short_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_BYTE: {
        byte_vars[opcode->operand0] = (int8_t)(int_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_SHORT: {
        short_vars[opcode->operand0] = (int16_t)(int_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_LONG: {
        long_vars[opcode->operand0] = (int64_t)int_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_FLOAT: {
        float_vars[opcode->operand0] = (float)int_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_DOUBLE: {
        double_vars[opcode->operand0] = (double)int_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_BYTE: {
        byte_vars[opcode->operand0] = (int8_t)long_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_SHORT: {
        short_vars[opcode->operand0] = (int16_t)long_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_INT: {
        int_vars[opcode->operand0] = (int32_t)long_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_FLOAT: {
        float_vars[opcode->operand0] = (float)long_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_DOUBLE: {
        double_vars[opcode->operand0] = (double)long_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_BYTE: {
        byte_vars[opcode->operand0] = (int8_t)float_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_SHORT: {
        short_vars[opcode->operand0] = (int16_t)float_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_INT: {
        int_vars[opcode->operand0] = (int32_t)float_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_LONG: {
        long_vars[opcode->operand0] = (int64_t)float_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_DOUBLE: {
        double_vars[opcode->operand0] = (double)float_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_BYTE: {
        byte_vars[opcode->operand0] = (int8_t)double_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_SHORT: {
        short_vars[opcode->operand0] = (int16_t)double_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_INT: {
        int_vars[opcode->operand0] = (int32_t)double_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_LONG: {
        long_vars[opcode->operand0] = (int64_t)double_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_FLOAT: {
        float_vars[opcode->operand0] = (float)double_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_STRING: {
        sprintf(tmp_buffer, "%" PRId8, byte_vars[opcode->operand1]);
        int32_t string_length = strlen(tmp_buffer);
        void* string = env->new_string_raw(env, stack, tmp_buffer, string_length);
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], string);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_STRING: {
        sprintf(tmp_buffer, "%" PRId16, short_vars[opcode->operand1]);
        int32_t string_length = strlen(tmp_buffer);
        void* string = env->new_string_raw(env, stack, tmp_buffer, string_length);
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], string);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_STRING: {
        sprintf(tmp_buffer, "%" PRId32, int_vars[opcode->operand1]);
        int32_t string_length = strlen(tmp_buffer);
        void* string = env->new_string_raw(env, stack, tmp_buffer, string_length);
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], string);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_STRING: {
        sprintf(tmp_buffer, "%" PRId64, long_vars[opcode->operand1]);
        int32_t string_length = strlen(tmp_buffer);
        void* string = env->new_string_raw(env, stack, tmp_buffer, string_length);
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], string);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_STRING: {
        sprintf(tmp_buffer, "%g", float_vars[opcode->operand1]);
        int32_t string_length = strlen(tmp_buffer);
        void* string = env->new_string_raw(env, stack, tmp_buffer, string_length);
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], string);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_STRING: {
        sprintf(tmp_buffer, "%g", double_vars[opcode->operand1]);
        int32_t string_length = strlen(tmp_buffer);
        void* string = env->new_string_raw(env, stack, tmp_buffer, string_length);
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], string);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_STRING_TO_BYTE_ARRAY: {
        void* src_string = object_vars[opcode->operand1];
        int32_t src_string_length = env->length(env, stack, src_string);
        const char* src_string_data = env->get_chars(env, stack, src_string);
        void* byte_array = env->new_byte_array_raw(env, stack, src_string_length);
        int8_t* byte_array_data = env->get_elems_byte(env, stack, byte_array);
        memcpy(byte_array_data, src_string_data, src_string_length);
        
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], byte_array);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_ARRAY_TO_STRING: {
        void* src_byte_array = object_vars[opcode->operand1];
        int32_t src_byte_array_length = env->length(env, stack, src_byte_array);
        int8_t* src_byte_array_data = env->get_elems_byte(env, stack, src_byte_array);
        void* string = env->new_string_raw(env, stack, (const char*)src_byte_array_data, src_byte_array_length);
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], string);
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_BYTE_OBJECT: {
        int8_t value = byte_vars[opcode->operand1];
        int32_t basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_CLASS;

        void* object = env->new_object_raw(env, stack, basic_type_id);
        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
        *(int8_t*)&fields[0] = value;
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_SHORT_OBJECT: {
        int16_t value = short_vars[opcode->operand1];
        int32_t basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_CLASS;
        void* object = env->new_object_raw(env, stack, basic_type_id);
        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
        *(int16_t*)&fields[0] = value;
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_INT_OBJECT: {
        int32_t value = int_vars[opcode->operand1];
        int32_t basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_INT_CLASS;
        void* object = env->new_object_raw(env, stack, basic_type_id);
        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
        *(int32_t*)&fields[0] = value;
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_LONG_OBJECT: {
        int64_t value = long_vars[opcode->operand1];
        int32_t basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_CLASS;
        void* object = env->new_object_raw(env, stack, basic_type_id);
        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
        *(int64_t*)&fields[0] = value;
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_FLOAT_OBJECT: {
        float value = float_vars[opcode->operand1];
        int32_t basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_CLASS;
        void* object = env->new_object_raw(env, stack, basic_type_id);
        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
        *(float*)&fields[0] = value;
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_DOUBLE_OBJECT: {
        double value = double_vars[opcode->operand1];
        int32_t basic_type_id = SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_CLASS;
        void* object = env->new_object_raw(env, stack, basic_type_id);
        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
        *(double*)&fields[0] = value;
        SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], object);
        
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_OBJECT_TO_BYTE: {
        void* object = *(void**)&object_vars[opcode->operand1];
        if (object == NULL) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_UNBOXING_CONVERSION_FROM_UNDEF]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
          if (object_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_CLASS && object_type_dimension == 0) {
            SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
            byte_vars[opcode->operand0] = *(int8_t*)&fields[0];
          }
          else {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_OBJECT_TO_SHORT: {
        void* object = *(void**)&object_vars[opcode->operand1];
        if (object == NULL) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_UNBOXING_CONVERSION_FROM_UNDEF]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
          if (object_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_CLASS && object_type_dimension == 0) {
            SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
            short_vars[opcode->operand0] = *(int16_t*)&fields[0];
          }
          else {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_OBJECT_TO_INT: {
        void* object = *(void**)&object_vars[opcode->operand1];
        if (object == NULL) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_UNBOXING_CONVERSION_FROM_UNDEF]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
          if (object_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT_CLASS && object_type_dimension == 0) {
            SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
            int_vars[opcode->operand0] = *(int32_t*)&fields[0];
          }
          else {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_OBJECT_TO_LONG: {
        void* object = *(void**)&object_vars[opcode->operand1];
        if (object == NULL) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_UNBOXING_CONVERSION_FROM_UNDEF]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
          if (object_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_CLASS && object_type_dimension == 0) {
            SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
            long_vars[opcode->operand0] = *(int64_t*)&fields[0];
          }
          else {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_OBJECT_TO_FLOAT: {
        void* object = *(void**)&object_vars[opcode->operand1];
        if (object == NULL) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_UNBOXING_CONVERSION_FROM_UNDEF]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
          if (object_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_CLASS && object_type_dimension == 0) {
            SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
            float_vars[opcode->operand0] = *(float*)&fields[0];
          }
          else {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_OBJECT_TO_DOUBLE: {
        void* object = *(void**)&object_vars[opcode->operand1];
        if (object == NULL) {
          void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_UNBOXING_CONVERSION_FROM_UNDEF]);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);
          int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);
          if (object_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_CLASS && object_type_dimension == 0) {
            SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);
            double_vars[opcode->operand0] = *(double*)&fields[0];
          }
          else {
            void* exception = env->new_string_nolen_raw(env, stack, exception_messages[SPVM_API_EXCEPTION_UNBOXING_CONVERSION_NON_CORRESPONDING_NUMERIC_OBJECT_TYPE]);
            env->set_exception(env, stack, exception);
            error = 1;
          }
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_CONDITINAL_INT: {
        int_vars[0] = int_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_CONDITINAL_LONG: {
        int_vars[0] = !!long_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_CONDITINAL_FLOAT: {
        int_vars[0] = !!float_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_CONDITINAL_DOUBLE: {
        int_vars[0] = !!double_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_CONDITINAL_OBJECT: {
        int_vars[0] = !!*(void**)&object_vars[opcode->operand1];
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_CONDITINAL_BOOL_OBJECT: {
        int_vars[0] = !!env->get_bool_object_value(env, stack, *(void**)&object_vars[opcode->operand1]);
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_BYTE: {
        *(int8_t*)&stack[stack_index] = byte_vars[opcode->operand0];
        stack_index++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_SHORT: {
        *(int16_t*)&stack[stack_index] = short_vars[opcode->operand0];
        stack_index++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_INT: {
        *(int32_t*)&stack[stack_index] = int_vars[opcode->operand0];
        stack_index++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_LONG: {
        *(int64_t*)&stack[stack_index] = long_vars[opcode->operand0];
        stack_index++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_FLOAT: {
        *(float*)&stack[stack_index] = float_vars[opcode->operand0];
        stack_index++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_DOUBLE: {
        *(double*)&stack[stack_index] = double_vars[opcode->operand0];
        stack_index++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_OBJECT: {
        *(void**)&stack[stack_index] = *(void**)&object_vars[opcode->operand0];
        stack_index++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_REF: {
        *(void**)&stack[stack_index] = *(void**)&ref_vars[opcode->operand0];
        stack_index++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_UNDEF:
        *(void**)&stack[stack_index] = NULL;
        stack_index++;
        
        break;
      case SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_BYTE: {
        int32_t fields_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          *(int8_t*)&stack[stack_index + field_index] = byte_vars[opcode->operand0 + field_index];
        }
        stack_index += fields_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_SHORT: {
        int32_t fields_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          *(int16_t*)&stack[stack_index + field_index] = short_vars[opcode->operand0 + field_index];
        }
        stack_index += fields_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_INT: {
        int32_t fields_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          *(int32_t*)&stack[stack_index + field_index] = int_vars[opcode->operand0 + field_index];
        }
        stack_index += fields_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_LONG: {
        int32_t fields_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          *(int64_t*)&stack[stack_index + field_index] = long_vars[opcode->operand0 + field_index];
        }
        stack_index += fields_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_FLOAT: {
        int32_t fields_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          *(float*)&stack[stack_index + field_index] = float_vars[opcode->operand0 + field_index];
        }
        stack_index += fields_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_DOUBLE: {
        int32_t fields_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          *(double*)&stack[stack_index + field_index] = double_vars[opcode->operand0 + field_index];
        }
        stack_index += fields_length;
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_CLASS_METHOD_BY_ID:
      case SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD_BY_ID:
      {
        int32_t call_method_id = opcode->operand1;
        int32_t call_method_args_stack_length = opcode->operand2 >> 16;
        
        stack_index = 0;
        error = env->call_spvm_method(env, stack, call_method_id, call_method_args_stack_length);
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
                    byte_vars[opcode->operand0] = *(int8_t*)&stack[0];
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                    short_vars[opcode->operand0] = *(int16_t*)&stack[0];
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                    int_vars[opcode->operand0] = *(int32_t*)&stack[0];
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                    long_vars[opcode->operand0] = *(int64_t*)&stack[0];
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                    float_vars[opcode->operand0] = *(float*)&stack[0];
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                    double_vars[opcode->operand0] = *(double*)&stack[0];
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
                SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], stack[0].oval);
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
                    int32_t fields_length = opcode->operand3;
                    for (int32_t field_index = 0; field_index < fields_length; field_index++) {
                      byte_vars[opcode->operand0 + field_index] = *(int8_t*)&stack[field_index];
                    }
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                    int32_t fields_length = opcode->operand3;
                    for (int32_t field_index = 0; field_index < fields_length; field_index++) {
                      short_vars[opcode->operand0 + field_index] = *(int16_t*)&stack[field_index];
                    }
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                    int32_t fields_length = opcode->operand3;
                    for (int32_t field_index = 0; field_index < fields_length; field_index++) {
                      int_vars[opcode->operand0 + field_index] = *(int32_t*)&stack[field_index];
                    }
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                    int32_t fields_length = opcode->operand3;
                    for (int32_t field_index = 0; field_index < fields_length; field_index++) {
                      long_vars[opcode->operand0 + field_index] = *(int64_t*)&stack[field_index];
                    }
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                    int32_t fields_length = opcode->operand3;
                    for (int32_t field_index = 0; field_index < fields_length; field_index++) {
                      float_vars[opcode->operand0 + field_index] = *(float*)&stack[field_index];
                    }
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                    int32_t fields_length = opcode->operand3;
                    for (int32_t field_index = 0; field_index < fields_length; field_index++) {
                      double_vars[opcode->operand0 + field_index] = *(double*)&stack[field_index];
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
            SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], stack[0].oval);
          }
          else {
            assert(0);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD_BY_NAME:
      {
        int32_t decl_method_id = opcode->operand1;
        SPVM_RUNTIME_METHOD* decl_method = SPVM_API_RUNTIME_get_method(runtime, decl_method_id);
        void* object = stack[0].oval;
        const char* decl_method_name = SPVM_API_RUNTIME_get_constant_string_value(runtime, decl_method->name_id, NULL);
        int32_t is_call_super = opcode->operand2 & 0xFFFF;
        int32_t call_method_args_stack_length = opcode->operand2 >> 16;
        
        int32_t call_method_id;
        if (is_call_super) {
          call_method_id = env->get_instance_method_id_super(env, object, decl_method_name);
        }
        else {
          call_method_id = env->get_instance_method_id(env, object, decl_method_name);
        }

        stack_index = 0;
        if (call_method_id < 0) {
          memset(tmp_buffer, sizeof(tmp_buffer), 0);
          SPVM_RUNTIME_CLASS* decl_method_class = SPVM_API_RUNTIME_get_class(runtime, decl_method->class_id);
          snprintf(tmp_buffer, 255, "Can't find the instance method \"%s\" defined in \"%s\"", decl_method_name, SPVM_API_RUNTIME_get_constant_string_value(runtime, decl_method_class->name_id, NULL));
          void* exception = env->new_string_nolen_raw(env, stack, tmp_buffer);
          env->set_exception(env, stack, exception);
          error = 1;
        }
        else {
          stack[STACK_INDEX_ARGS_LENGTH].ival = call_method_args_stack_length;
          error = env->call_spvm_method(env, stack, call_method_id, call_method_args_stack_length);
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
                      byte_vars[opcode->operand0] = *(int8_t*)&stack[0];
                      break;
                    }
                    case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                      short_vars[opcode->operand0] = *(int16_t*)&stack[0];
                      break;
                    }
                    case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                      int_vars[opcode->operand0] = *(int32_t*)&stack[0];
                      break;
                    }
                    case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                      long_vars[opcode->operand0] = *(int64_t*)&stack[0];
                      break;
                    }
                    case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                      float_vars[opcode->operand0] = *(float*)&stack[0];
                      break;
                    }
                    case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                      double_vars[opcode->operand0] = *(double*)&stack[0];
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
                  SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], stack[0].oval);
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
                      int32_t fields_length = opcode->operand3;
                      for (int32_t field_index = 0; field_index < fields_length; field_index++) {
                        byte_vars[opcode->operand0 + field_index] = *(int8_t*)&stack[field_index];
                      }
                      break;
                    }
                    case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                      int32_t fields_length = opcode->operand3;
                      for (int32_t field_index = 0; field_index < fields_length; field_index++) {
                        short_vars[opcode->operand0 + field_index] = *(int16_t*)&stack[field_index];
                      }
                      break;
                    }
                    case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                      int32_t fields_length = opcode->operand3;
                      for (int32_t field_index = 0; field_index < fields_length; field_index++) {
                        int_vars[opcode->operand0 + field_index] = *(int32_t*)&stack[field_index];
                      }
                      break;
                    }
                    case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                      int32_t fields_length = opcode->operand3;
                      for (int32_t field_index = 0; field_index < fields_length; field_index++) {
                        long_vars[opcode->operand0 + field_index] = *(int64_t*)&stack[field_index];
                      }
                      break;
                    }
                    case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                      int32_t fields_length = opcode->operand3;
                      for (int32_t field_index = 0; field_index < fields_length; field_index++) {
                        float_vars[opcode->operand0 + field_index] = *(float*)&stack[field_index];
                      }
                      break;
                    }
                    case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                      int32_t fields_length = opcode->operand3;
                      for (int32_t field_index = 0; field_index < fields_length; field_index++) {
                        double_vars[opcode->operand0 + field_index] = *(double*)&stack[field_index];
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
              SPVM_API_OBJECT_ASSIGN(env, stack, (void**)&object_vars[opcode->operand0], stack[0].oval);
            }
            else {
              assert(0);
            }
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_BYTE: {
        byte_vars[opcode->operand0] = *(int8_t*)&stack[opcode->operand3 & 0xFF];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_SHORT: {
        short_vars[opcode->operand0] = *(int16_t*)&stack[opcode->operand3 & 0xFF];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_INT: {
        int_vars[opcode->operand0] = *(int32_t*)&stack[opcode->operand3 & 0xFF];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_LONG: {
        long_vars[opcode->operand0] = *(int64_t*)&stack[opcode->operand3 & 0xFF];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_FLOAT: {
        float_vars[opcode->operand0] = *(float*)&stack[opcode->operand3 & 0xFF];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_DOUBLE: {
        double_vars[opcode->operand0] = *(double*)&stack[opcode->operand3 & 0xFF];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_OBJECT: {
        object_vars[opcode->operand0] = *(void**)&stack[opcode->operand3 & 0xFF];
        void* object = *(void**)&object_vars[opcode->operand0];
        if (object != NULL) {
          SPVM_API_INC_REF_COUNT_ONLY(env, stack, object);
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_REF: {
        ref_vars[opcode->operand0] = *(void**)&stack[opcode->operand3 & 0xFF];
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_MULNUM_BYTE: {
        int32_t type_stack_length = opcode->operand3 >> 8;
        for (int32_t field_index = 0; field_index < type_stack_length; field_index++) {
          byte_vars[opcode->operand0 + field_index] = *(int8_t*)&stack[(opcode->operand3 & 0xFF) + field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_MULNUM_SHORT: {
        int32_t type_stack_length = opcode->operand3 >> 8;
        for (int32_t field_index = 0; field_index < type_stack_length; field_index++) {
          short_vars[opcode->operand0 + field_index] = *(int16_t*)&stack[(opcode->operand3 & 0xFF) + field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_MULNUM_INT: {
        int32_t type_stack_length = opcode->operand3 >> 8;
        for (int32_t field_index = 0; field_index < type_stack_length; field_index++) {
          int_vars[opcode->operand0 + field_index] = *(int32_t*)&stack[(opcode->operand3 & 0xFF) + field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_MULNUM_LONG: {
        int32_t type_stack_length = opcode->operand3 >> 8;
        for (int32_t field_index = 0; field_index < type_stack_length; field_index++) {
          long_vars[opcode->operand0 + field_index] = *(int64_t*)&stack[(opcode->operand3 & 0xFF) + field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_MULNUM_FLOAT: {
        int32_t type_stack_length = opcode->operand3 >> 8;
        for (int32_t field_index = 0; field_index < type_stack_length; field_index++) {
          float_vars[opcode->operand0 + field_index] = *(float*)&stack[(opcode->operand3 & 0xFF) + field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_MULNUM_DOUBLE: {
        int32_t type_stack_length = opcode->operand3 >> 8;
        for (int32_t field_index = 0; field_index < type_stack_length; field_index++) {
          double_vars[opcode->operand0 + field_index] = *(double*)&stack[(opcode->operand3 & 0xFF) + field_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_OPTIONAL_BYTE: {
        int32_t args_length = env->get_args_stack_length(env, stack);
        int32_t args_index = opcode->operand3 & 0xFF;
        if (args_index >= args_length) {
          byte_vars[opcode->operand0] = (int8_t)(uint8_t)opcode->operand1;
        }
        else {
          byte_vars[opcode->operand0] = *(int8_t*)&stack[args_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_OPTIONAL_SHORT: {
        int32_t args_length = env->get_args_stack_length(env, stack);
        int32_t args_index = opcode->operand3 & 0xFF;
        if (args_index >= args_length) {
          short_vars[opcode->operand0] = (int16_t)(uint16_t)opcode->operand1;
        }
        else {
          short_vars[opcode->operand0] = *(int16_t*)&stack[args_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_OPTIONAL_INT: {
        int32_t args_length = env->get_args_stack_length(env, stack);
        int32_t args_index = opcode->operand3 & 0xFF;
        
        if (args_index >= args_length) {
          int_vars[opcode->operand0] = (int32_t)opcode->operand1;
        }
        else {
          int_vars[opcode->operand0] = *(int32_t*)&stack[args_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_OPTIONAL_LONG: {
        int32_t args_length = env->get_args_stack_length(env, stack);
        int32_t args_index = opcode->operand3 & 0xFF;
        if (args_index >= args_length) {
          long_vars[opcode->operand0] = *(int64_t*)&opcode->operand1;
        }
        else {
          long_vars[opcode->operand0] = *(int64_t*)&stack[args_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_OPTIONAL_FLOAT: {
        int32_t args_length = env->get_args_stack_length(env, stack);
        int32_t args_index = opcode->operand3 & 0xFF;
        if (args_index >= args_length) {
          SPVM_VALUE value;
          value.ival = (int32_t)opcode->operand1;
          float_vars[opcode->operand0] = value.fval;
        }
        else {
          float_vars[opcode->operand0] = *(float*)&stack[args_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_OPTIONAL_DOUBLE: {
        int32_t args_length = env->get_args_stack_length(env, stack);
        int32_t args_index = opcode->operand3 & 0xFF;
        if (args_index >= args_length) {
          double_vars[opcode->operand0] = *(double*)&opcode->operand1;
        }
        else {
          double_vars[opcode->operand0] = *(double*)&stack[args_index];
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_OPTIONAL_OBJECT: {
        int32_t args_length = env->get_args_stack_length(env, stack);
        int32_t args_index = opcode->operand3 & 0xFF;
        if (args_index >= args_length) {
          object_vars[opcode->operand0] = NULL;
        }
        else {
          object_vars[opcode->operand0] = *(void**)&stack[args_index];
          void* object = *(void**)&object_vars[opcode->operand0];
          if (object != NULL) {
            SPVM_API_INC_REF_COUNT_ONLY(env, stack, object);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_VOID:
      {
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_BYTE:
      {
        *(int8_t*)&stack[0] = byte_vars[opcode->operand0];
        
        opcode_rel_index = opcode->operand1;
        
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_SHORT:
      {
        *(int16_t*)&stack[0] = short_vars[opcode->operand0];
        
        opcode_rel_index = opcode->operand1;
        
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_INT:
      {
        *(int32_t*)&stack[0] = int_vars[opcode->operand0];
        
        opcode_rel_index = opcode->operand1;
        
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_LONG:
      {
        *(int64_t*)&stack[0] = long_vars[opcode->operand0];
        
        opcode_rel_index = opcode->operand1;
        
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_FLOAT:
      {
        *(float*)&stack[0] = float_vars[opcode->operand0];
        
        opcode_rel_index = opcode->operand1;
        
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_DOUBLE:
      {
        *(double*)&stack[0] = double_vars[opcode->operand0];
        
        opcode_rel_index = opcode->operand1;
        
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_OBJECT:
      {
        *(void**)&stack[0] = *(void**)&object_vars[opcode->operand0];
        // Increment ref count of return value not to release by leave scope
        if (*(void**)&stack[0] != NULL) {
          SPVM_API_INC_REF_COUNT_ONLY(env, stack, *(void**)&stack[0]);
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
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_BYTE:
      {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          *(int8_t*)&stack[field_index] = byte_vars[opcode->operand0 + field_index];
        }
        opcode_rel_index = opcode->operand1;
        
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_SHORT:
      {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          *(int16_t*)&stack[field_index] = short_vars[opcode->operand0 + field_index];
        }
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_INT:
      {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          *(int32_t*)&stack[field_index] = int_vars[opcode->operand0 + field_index];
        }
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_LONG:
      {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          *(int64_t*)&stack[field_index] = long_vars[opcode->operand0 + field_index];
        }
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_FLOAT:
      {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          *(float*)&stack[field_index] = float_vars[opcode->operand0 + field_index];
        }
        opcode_rel_index = opcode->operand1;
        continue;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_DOUBLE:
      {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          *(double*)&stack[field_index] = double_vars[opcode->operand0 + field_index];
        }
        opcode_rel_index = opcode->operand1;
        continue;
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
      int32_t method_return_type_is_object = SPVM_API_RUNTIME_get_type_is_object(runtime, method->return_type_id);
      if (method_return_type_is_object) {
        if (*(void**)&stack[0] != NULL) {
          SPVM_API_DEC_REF_COUNT_ONLY(env, stack, *(void**)&stack[0]);
        }
      }
    }
    
    SPVM_API_free_memory_stack(env, stack, call_stack);
    call_stack = NULL;
    
    return return_value;
  }
}
