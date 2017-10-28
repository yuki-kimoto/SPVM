#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include "spvm_api.h"
#include "spvm_bytecode.h"
#include "spvm_constant_pool_sub.h"

SPVM_API_VALUE SPVM_RUNTIME_call_sub(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args) {
  (void)api;
  
  // SPVM Object header byte size
  const int32_t OBJECT_HEADER_BYTE_SIZE = api->get_object_header_byte_size(api);
  
  // SPVM Object header length offset
  const int32_t OBJECT_HEADER_LENGTH_OFFSET = api->get_object_header_length_offset(api);
  
  // Void type code
  const int32_t VOID_TYPE_CODE = api->get_void_type_code(api);

  // Byte type code
  const int32_t BYTE_TYPE_CODE = api->get_byte_type_code(api);

  // Short type code
  const int32_t SHORT_TYPE_CODE = api->get_short_type_code(api);

  // Int type code
  const int32_t INT_TYPE_CODE = api->get_int_type_code(api);

  // Long type code
  const int32_t LONG_TYPE_CODE = api->get_long_type_code(api);

  // Float type code
  const int32_t FLOAT_TYPE_CODE = api->get_float_type_code(api);

  // Double type code
  const int32_t DOUBLE_TYPE_CODE = api->get_double_type_code(api);
  
  // Debug
  const int32_t debug = api->is_debug(api) ? 1 : 0;
  
  // Constant pool
  const int32_t* constant_pool = api->get_constant_pool(api);
  
  // Package variables
  SPVM_API_VALUE* package_vars = api->get_package_vars(api);
  
  // Bytecodes
  const int32_t* bytecodes = api->get_bytecodes(api);
  
  int32_t bytecode_index = 0;

  // Constant pool subroutine
  SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&constant_pool[sub_id];
  
  // Args length
  int32_t args_length = api->get_sub_args_length(api, sub_id);
  
  // Lexical varialbe length
  int32_t my_vars_length = api->get_sub_my_vars_length(api, sub_id);
  register int32_t operand_stack_top = -1 + my_vars_length;
  
  // Call_stack_max
  int32_t call_stack_length = my_vars_length + api->get_sub_operand_stack_max(api, sub_id);
  
  // Call stack
  SPVM_API_OBJECT* call_stack_array = api->new_value_array(api, call_stack_length);
  api->inc_ref_count(api, call_stack_array);
  SPVM_API_VALUE* call_stack = SPVM_RUNTIME_API_get_value_array_elements(api, (SPVM_API_OBJECT*)call_stack_array);

  // Catch stack
  int16_t catch_exception_stack[255];
  
  // Catch stack top
  int32_t catch_exception_stack_top = -1;

  register int32_t success;
  int32_t current_line = 0;
  
  char tmp_string[30];

  // Copy arguments
  memcpy(call_stack, args, args_length * sizeof(SPVM_API_VALUE));
  
  // If arg is object, increment reference count
  if (api->get_sub_object_args_length(api, sub_id)) {
    int32_t object_args_base = constant_pool_sub->object_args_base;
    int32_t object_args_length = api->get_sub_object_args_length(api, sub_id);
    {
      int32_t i;
      for (i = 0; i < object_args_length; i++) {
        int32_t arg_index = constant_pool[object_args_base + i];
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[arg_index].object_value;
        if (object != NULL) {
          api->inc_ref_count(api, object);
        }
      }
    }
  }
  
  // Set exception to undef at top of call_sub
  api->set_exception(api, NULL);
  
  // Call native sub
  if (constant_pool_sub->is_native) {
    // Set runtimeironment
    int32_t return_type_code = api->get_type_code(api, constant_pool_sub->return_type_id);
    
    // Call native subroutine
    if (return_type_code == VOID_TYPE_CODE) {
      void (*native_address)(SPVM_API*, SPVM_API_VALUE*) = constant_pool_sub->native_address;
      (*native_address)(api, (SPVM_API_VALUE*)call_stack);
      
      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      goto label_SPVM_BYTECODE_C_CODE_RETURN_VOID;
    }
    else if (return_type_code == BYTE_TYPE_CODE) {
      int8_t (*native_address)(SPVM_API*, SPVM_API_VALUE*) = constant_pool_sub->native_address;
      int8_t return_value = (*native_address)(api, (SPVM_API_VALUE*)call_stack);

      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      operand_stack_top++;
      call_stack[operand_stack_top].byte_value = return_value;
      goto label_SPVM_BYTECODE_C_CODE_RETURN_BYTE;
    }
    else if (return_type_code == SHORT_TYPE_CODE) {
      int16_t (*native_address)(SPVM_API*, SPVM_API_VALUE*) = constant_pool_sub->native_address;
      int16_t return_value = (*native_address)(api, (SPVM_API_VALUE*)call_stack);

      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }

      operand_stack_top++;
      call_stack[operand_stack_top].short_value = return_value;
      goto label_SPVM_BYTECODE_C_CODE_RETURN_SHORT;
    }
    else if (return_type_code == INT_TYPE_CODE) {
        
      int32_t (*native_address)(SPVM_API*, SPVM_API_VALUE*) = constant_pool_sub->native_address;
      
      int32_t return_value = (*native_address)(api, (SPVM_API_VALUE*)call_stack);

      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }

      operand_stack_top++;
      call_stack[operand_stack_top].int_value = return_value;
      goto label_SPVM_BYTECODE_C_CODE_RETURN_INT;
    }
    else if (return_type_code == LONG_TYPE_CODE) {
      int64_t (*native_address)(SPVM_API*, SPVM_API_VALUE*) = constant_pool_sub->native_address;
      int64_t return_value = (*native_address)(api, (SPVM_API_VALUE*)call_stack);

      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }

      operand_stack_top++;
      call_stack[operand_stack_top].long_value = return_value;
      goto label_SPVM_BYTECODE_C_CODE_RETURN_LONG;
    }
    else if (return_type_code == FLOAT_TYPE_CODE) {
      float (*native_address)(SPVM_API*, SPVM_API_VALUE*) = constant_pool_sub->native_address;
      float return_value = (*native_address)(api, (SPVM_API_VALUE*)call_stack);

      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      operand_stack_top++;
      call_stack[operand_stack_top].float_value = return_value;
      goto label_SPVM_BYTECODE_C_CODE_RETURN_FLOAT;
    }
    else if (return_type_code == DOUBLE_TYPE_CODE) {
      double (*native_address)(SPVM_API*, SPVM_API_VALUE*) = constant_pool_sub->native_address;
      double return_value = (*native_address)(api, (SPVM_API_VALUE*)call_stack);

      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      operand_stack_top++;
      call_stack[operand_stack_top].double_value = return_value;
      goto label_SPVM_BYTECODE_C_CODE_RETURN_DOUBLE;
    }
    else {
      SPVM_API_OBJECT* (*native_address)(SPVM_API*, SPVM_API_VALUE*) = constant_pool_sub->native_address;
      SPVM_API_OBJECT* return_value = (*native_address)(api, (SPVM_API_VALUE*)call_stack);
      
      if (api->get_exception(api)) {
        goto label_SPVM_BYTECODE_C_CODE_CROAK;
      }
      
      operand_stack_top++;
      call_stack[operand_stack_top].object_value = return_value;
      goto label_SPVM_BYTECODE_C_CODE_RETURN_OBJECT;
    }
  }
  // Call normal sub
  else {
    bytecode_index = constant_pool_sub->bytecode_base;
  }
  
  while (1) {
    switch (bytecodes[bytecode_index]) {
      case SPVM_BYTECODE_C_CODE_LOAD_PACKAGE_VAR: {
        // Get subroutine ID
        int32_t package_var_id = bytecodes[bytecode_index + 1];
        
        operand_stack_top++;
        call_stack[operand_stack_top] = package_vars[package_var_id];
        
        bytecode_index += 2;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_STORE_PACKAGE_VAR: {
        // Get subroutine ID
        int32_t package_var_id = bytecodes[bytecode_index + 1];

        package_vars[package_var_id] = call_stack[operand_stack_top];
        operand_stack_top--;

        bytecode_index += 2;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_STORE_PACKAGE_VAR_OBJECT: {
        // Get subroutine ID
        int32_t package_var_id = bytecodes[bytecode_index + 1];
        
        // Decrement reference count
        if (package_vars[package_var_id].object_value != NULL) {
          api->dec_ref_count(api, package_vars[package_var_id].object_value);
        }
        
        // Store object
        package_vars[package_var_id].object_value = call_stack[operand_stack_top].object_value;
        
        // Increment new value reference count
        if (package_vars[package_var_id].object_value != NULL) {
          api->inc_ref_count(api, package_vars[package_var_id].object_value);;
        }
        
        operand_stack_top--;

        bytecode_index += 2;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_PUSH_CATCH_EXCEPTION: {
        // Next operation
        int16_t jump_offset_abs = (int16_t)(bytecodes[bytecode_index + 1]);
        
        catch_exception_stack_top++;
        catch_exception_stack[catch_exception_stack_top] = jump_offset_abs;
        
        bytecode_index += 2;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_POP_CATCH_EXCEPTION: {
        catch_exception_stack_top--;
        
        bytecode_index++;;
        
        break;
      }
      case SPVM_BYTECODE_C_CODE_CALL_SUB: {
        // Get subroutine ID
        int32_t call_sub_id = bytecodes[bytecode_index + 1];
        
        SPVM_CONSTANT_POOL_SUB* constant_pool_sub_called = (SPVM_CONSTANT_POOL_SUB*)&constant_pool[call_sub_id];
        
        int32_t args_length = constant_pool_sub_called->args_length;
        
        operand_stack_top -= args_length;
        
        SPVM_API_VALUE args[255];
        memcpy(args, &call_stack[operand_stack_top + 1], sizeof(SPVM_API_VALUE) * args_length);
        
        // Call subroutine
        SPVM_API_VALUE return_value = SPVM_RUNTIME_call_sub(api, call_sub_id, args);
        
        if (api->get_exception(api)) {
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (!constant_pool_sub_called->is_void) {
            operand_stack_top++;
            call_stack[operand_stack_top] = return_value;
          }
          
          // Next operation
          bytecode_index += 2 + (debug * 2);
          
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_RETURN_BYTE:
      case SPVM_BYTECODE_C_CODE_RETURN_SHORT:
      case SPVM_BYTECODE_C_CODE_RETURN_INT:
      case SPVM_BYTECODE_C_CODE_RETURN_LONG:
      case SPVM_BYTECODE_C_CODE_RETURN_FLOAT:
      case SPVM_BYTECODE_C_CODE_RETURN_DOUBLE:
      {
        label_SPVM_BYTECODE_C_CODE_RETURN_BYTE:
        label_SPVM_BYTECODE_C_CODE_RETURN_SHORT:
        label_SPVM_BYTECODE_C_CODE_RETURN_INT:
        label_SPVM_BYTECODE_C_CODE_RETURN_LONG:
        label_SPVM_BYTECODE_C_CODE_RETURN_FLOAT:
        label_SPVM_BYTECODE_C_CODE_RETURN_DOUBLE:
        {
        
          // Get return value
          SPVM_API_VALUE return_value = call_stack[operand_stack_top];
          
          // Decrement object my vars reference count
          int32_t object_my_vars_length = constant_pool_sub->object_my_vars_length;
          int32_t object_my_vars_base = constant_pool_sub->object_my_vars_base;
          
          if (object_my_vars_length) {
            {
              int32_t i;
              for (i = 0; i < object_my_vars_length; i++) {
                int32_t my_var_index = constant_pool[object_my_vars_base + i];
                SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[my_var_index].object_value;
                
                if (object != NULL) {
                  api->dec_ref_count(api, object);
                }
              }
            }
          }
          
          api->dec_ref_count(api, call_stack_array);
          
          // No exception
          api->set_exception(api, NULL);
          
          return return_value;
        }
      }
      case SPVM_BYTECODE_C_CODE_RETURN_OBJECT: {

        label_SPVM_BYTECODE_C_CODE_RETURN_OBJECT: {
        
          SPVM_API_VALUE return_value = call_stack[operand_stack_top];
          
          // Increment ref count of return value not to release by decrement
          if (return_value.object_value != NULL) {
            api->inc_ref_count(api, return_value.object_value);
          }
          
          // Decrement object my vars reference count
          int32_t object_my_vars_length = constant_pool_sub->object_my_vars_length;
          int32_t object_my_vars_base = constant_pool_sub->object_my_vars_base;
          if (object_my_vars_length) {
            {
              int32_t i;
              for (i = 0; i < object_my_vars_length; i++) {
                int32_t my_var_index = constant_pool[object_my_vars_base + i];
                SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[my_var_index].object_value;
                
                if (object != NULL) {
                  api->dec_ref_count(api, object);
                }
              }
            }
          }

          // Decrement ref count of return value
          if (return_value.object_value != NULL) {
            api->dec_ref_count_only(api, return_value.object_value);
          }
          
          api->dec_ref_count(api, call_stack_array);
          
          // No exception
          api->set_exception(api, NULL);
          
          return return_value;
        }
      }
      case SPVM_BYTECODE_C_CODE_RETURN_VOID: {

        label_SPVM_BYTECODE_C_CODE_RETURN_VOID: {

          SPVM_API_VALUE return_value;
          memset(&return_value, 0, sizeof(SPVM_API_VALUE));
          
          // Decrement object my vars reference count
          int32_t object_my_vars_length = constant_pool_sub->object_my_vars_length;
          int32_t object_my_vars_base = constant_pool_sub->object_my_vars_base;
          if (object_my_vars_length) {
            {
              int32_t i;
              for (i = 0; i < object_my_vars_length; i++) {
                int32_t my_var_index = constant_pool[object_my_vars_base + i];
                SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[my_var_index].object_value;
                
                if (object != NULL) {
                  api->dec_ref_count(api, object);
                }
              }
            }
          }
          
          api->dec_ref_count(api, call_stack_array);
          
          // No exception
          api->set_exception(api, NULL);

          return return_value;
        }
      }
      case SPVM_BYTECODE_C_CODE_LOAD_EXCEPTION: {
        operand_stack_top++;
        call_stack[operand_stack_top].object_value = (SPVM_API_OBJECT*)api->get_exception(api);
        
        bytecode_index++;;
        break;
      }
      case SPVM_BYTECODE_C_CODE_STORE_EXCEPTION: {
        
        api->set_exception(api, (SPVM_API_OBJECT*)call_stack[operand_stack_top].object_value);
        
        operand_stack_top--;
        
        bytecode_index++;;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CROAK: {
        
        label_SPVM_BYTECODE_C_CODE_CROAK:
        
        // Catch exception
        if (catch_exception_stack_top > -1) {
          
          int16_t jump_offset_abs = catch_exception_stack[catch_exception_stack_top];
          catch_exception_stack_top--;
          
          bytecode_index = constant_pool_sub->bytecode_base + jump_offset_abs;
          
          break;
        }
        
        // Decrement object my vars reference count
        int32_t object_my_vars_length = constant_pool_sub->object_my_vars_length;
        int32_t object_my_vars_base = constant_pool_sub->object_my_vars_base;
        if (object_my_vars_length) {
          {
            int32_t i;
            for (i = 0; i < object_my_vars_length; i++) {
              int32_t my_var_index = constant_pool[object_my_vars_base + i];
              SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[my_var_index].object_value;
              
              if (object != NULL) {
                api->dec_ref_count(api, object);
              }
            }
          }
        }
        
        // Sub name
        int32_t sub_name_id = api->get_sub_name_id(api, sub_id);
        const char* sub_name = (char*)&constant_pool[sub_name_id + 1];
        
        // File name
        int32_t file_name_id = api->get_sub_file_name_id(api, sub_id);
        const char* file_name = (char*)&constant_pool[file_name_id + 1];
        
        // stack trace strings
        const char* from = "\n  from ";
        const char* at = "() at ";

        // Exception
        SPVM_API_OBJECT* exception = api->get_exception(api);
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
        
        if (debug) {
          sprintf(line_str, "%" PRId32, current_line);
          total_length += strlen(line);
          total_length += strlen(line_str);
        }
        
        // Create exception message
        SPVM_API_OBJECT* new_exception = api->new_string(api, NULL, total_length);
        char* new_exception_chars = api->get_string_chars(api, new_exception);
        
        memcpy(
          (void*)(new_exception_chars),
          (void*)(exception_chars),
          exception_length
        );
        if (debug) {
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
        
        SPVM_API_VALUE return_value;
        
        memset(&return_value, 0, sizeof(SPVM_API_VALUE));
        
        api->dec_ref_count(api, call_stack_array);
        
        return return_value;
      }
      case SPVM_BYTECODE_C_CODE_NOP:
        // Not used
        assert(0);
      case SPVM_BYTECODE_C_CODE_UNDEF:
        operand_stack_top++;
        call_stack[operand_stack_top].object_value = (void*)NULL;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_LOAD_CONSTANT:
        operand_stack_top++;
        memcpy(&call_stack[operand_stack_top], &constant_pool[bytecodes[bytecode_index + 1]], sizeof(int32_t));
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_LOAD_CONSTANT2:
        operand_stack_top++;
        memcpy(&call_stack[operand_stack_top], &constant_pool[bytecodes[bytecode_index + 1]], sizeof(int64_t));
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_LOAD:
        operand_stack_top++;
        call_stack[operand_stack_top] = call_stack[bytecodes[bytecode_index + 1]];
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_BYTE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        int32_t index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "BYTE_ARRAY must not be undef(BYTE_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(BYTE_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[operand_stack_top - 1].byte_value
              = *(int8_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int8_t) * index);
            operand_stack_top--;
            bytecode_index++;;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_SHORT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        int32_t index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "SHORT_ARRAY must not be undef(SHORT_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(SHORT_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[operand_stack_top - 1].short_value
              = *(int16_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int16_t) * index);
            operand_stack_top--;
            bytecode_index++;;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_INT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        int32_t index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "INT_ARRAY must not be undef(INT_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(INT_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[operand_stack_top - 1].int_value = *(int32_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int32_t) * index);
            operand_stack_top--;
            bytecode_index++;;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_LONG: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        int32_t index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "LONG_ARRAY must not be undef(LONG_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(LONG_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[operand_stack_top - 1].long_value = *(int64_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int64_t) * index);
            operand_stack_top--;
            bytecode_index++;;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_FLOAT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        int32_t index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "FLOAT_ARRAY must not be undef(FLOAT_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(FLOAT_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[operand_stack_top - 1].float_value = *(float*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(float) * index);
            operand_stack_top--;
            bytecode_index++;;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_DOUBLE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        int32_t index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "DOUBLE_ARRAY must not be undef(DOUBLE_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(DOUBLE_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[operand_stack_top - 1].double_value = *(double*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(double) * index);
            operand_stack_top--;
            bytecode_index++;;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LOAD_OBJECT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        int32_t index = call_stack[operand_stack_top].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "OBJECT_ARRAY must not be undef(OBJECT_ARRAY->[INDEX])", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(OBJECT_ARRAY->[INDEX])", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            call_stack[operand_stack_top - 1] = *(SPVM_API_VALUE*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index);
            operand_stack_top--;
            bytecode_index++;;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_BYTE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 2].object_value;
        int32_t index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "BYTE_ARRAY must not be undef(BYTE_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(BYTE_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            *(int8_t*)((intptr_t)call_stack[operand_stack_top - 2].object_value + OBJECT_HEADER_BYTE_SIZE + sizeof(int8_t) * call_stack[operand_stack_top - 1].int_value)
              = call_stack[operand_stack_top].byte_value;
            operand_stack_top -= 3;
            bytecode_index++;;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_SHORT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 2].object_value;
        int32_t index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "SHORT_ARRAY must not be undef(SHORT_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(SHORT_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            *(int16_t*)((intptr_t)call_stack[operand_stack_top - 2].object_value + OBJECT_HEADER_BYTE_SIZE + sizeof(int16_t) * call_stack[operand_stack_top - 1].int_value)
              = call_stack[operand_stack_top].short_value;
            operand_stack_top -= 3;
            bytecode_index++;;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_INT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 2].object_value;
        int32_t index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "INT_ARRAY must not be undef(INT_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(INT_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            *(int32_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int32_t) * index) = call_stack[operand_stack_top].int_value;
            operand_stack_top -= 3;
            bytecode_index++;;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_LONG: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 2].object_value;
        int32_t index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "LONG_ARRAY must not be undef(LONG_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(LONG_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            *(int64_t*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(int64_t) * index) = call_stack[operand_stack_top].long_value;
            operand_stack_top -= 3;
            bytecode_index++;;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_FLOAT: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 2].object_value;
        int32_t index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "FLOAT_ARRAY must not be undef(FLOAT_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(FLOAT_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            *(float*)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(float) * index) = call_stack[operand_stack_top].float_value;
            operand_stack_top -= 3;
            bytecode_index++;;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_DOUBLE: {
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 2].object_value;
        int32_t index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "DOUBLE_ARRAY must not be undef(DOUBLE_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(DOUBLE_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            *(double*)((intptr_t)call_stack[operand_stack_top - 2].object_value + OBJECT_HEADER_BYTE_SIZE + sizeof(double) * call_stack[operand_stack_top - 1].int_value)
              = call_stack[operand_stack_top].double_value;
            operand_stack_top -= 3;
            bytecode_index++;;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_STORE_OBJECT: {
        
        SPVM_API_OBJECT* array = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 2].object_value;
        int32_t index = call_stack[operand_stack_top - 1].int_value;
        if (__builtin_expect(!array, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "OBJECT_ARRAY must not be undef(OBJECT_ARRAY->[INDEX] = VALUE)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + OBJECT_HEADER_LENGTH_OFFSET), 0)) {
            SPVM_API_OBJECT* exception = api->new_string(api, "INDEX is out of range(OBJECT_ARRAY->[INDEX] = VALUE)", 0);
            api->set_exception(api, exception);
            goto label_SPVM_BYTECODE_C_CODE_CROAK;
          }
          else {
            SPVM_API_OBJECT** object_address = (SPVM_API_OBJECT**)((intptr_t)array + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index);
            
            // Decrement old object reference count
            if (*object_address != NULL) {
              api->dec_ref_count(api, *object_address);
            }
            
            // Store address
            *object_address = call_stack[operand_stack_top].object_value;

            // Increment new object reference count
            if (*object_address != NULL) {
              api->inc_ref_count(api, *object_address);
            }
            
            operand_stack_top -= 3;
            bytecode_index++;;
            break;
          }
        }
      }
      case SPVM_BYTECODE_C_CODE_STORE:
        call_stack[bytecodes[bytecode_index + 1]] = call_stack[operand_stack_top];
        operand_stack_top--;
        bytecode_index += 2;
        break;
      case SPVM_BYTECODE_C_CODE_STORE_OBJECT: {
        int32_t index = bytecodes[bytecode_index + 1];
        
        // Decrement reference count
        if (call_stack[index].object_value != NULL) {
          api->dec_ref_count(api, call_stack[index].object_value);
        }
        
        // Store object
        call_stack[index].object_value = call_stack[operand_stack_top].object_value;
        
        // Increment new value reference count
        if (call_stack[index].object_value != NULL) {
          api->inc_ref_count(api, call_stack[index].object_value);
        }
        
        operand_stack_top--;
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_POP:
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_ADD_BYTE:
        call_stack[operand_stack_top - 1].byte_value += call_stack[operand_stack_top].byte_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_ADD_SHORT:
        call_stack[operand_stack_top - 1].short_value += call_stack[operand_stack_top].short_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_ADD_INT:
        call_stack[operand_stack_top - 1].int_value += call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_ADD_LONG:
        call_stack[operand_stack_top - 1].long_value += call_stack[operand_stack_top].long_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_ADD_FLOAT:
        call_stack[operand_stack_top - 1].float_value += call_stack[operand_stack_top].float_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_ADD_DOUBLE:
        call_stack[operand_stack_top - 1].double_value += call_stack[operand_stack_top].double_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_SUBTRACT_BYTE:
        call_stack[operand_stack_top - 1].byte_value -= call_stack[operand_stack_top].byte_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_SUBTRACT_SHORT:
        call_stack[operand_stack_top - 1].short_value -= call_stack[operand_stack_top].short_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_SUBTRACT_INT:
        call_stack[operand_stack_top - 1].int_value -= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_SUBTRACT_LONG:
        call_stack[operand_stack_top - 1].long_value -= call_stack[operand_stack_top].long_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_SUBTRACT_FLOAT:
        call_stack[operand_stack_top - 1].float_value -= call_stack[operand_stack_top].float_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_SUBTRACT_DOUBLE:
        call_stack[operand_stack_top - 1].double_value -= call_stack[operand_stack_top].double_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_MULTIPLY_BYTE:
        call_stack[operand_stack_top - 1].byte_value *= call_stack[operand_stack_top].byte_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_MULTIPLY_SHORT:
        call_stack[operand_stack_top - 1].short_value *= call_stack[operand_stack_top].short_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_MULTIPLY_INT:
        call_stack[operand_stack_top - 1].int_value *= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_MULTIPLY_LONG:
        call_stack[operand_stack_top - 1].long_value *= call_stack[operand_stack_top].long_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_MULTIPLY_FLOAT:
        call_stack[operand_stack_top - 1].float_value *= call_stack[operand_stack_top].float_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_MULTIPLY_DOUBLE:
        call_stack[operand_stack_top - 1].double_value *= call_stack[operand_stack_top].double_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_DIVIDE_BYTE:
        if (call_stack[operand_stack_top].byte_value == 0) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division (byte / byte)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          call_stack[operand_stack_top - 1].byte_value /= call_stack[operand_stack_top].byte_value;
          operand_stack_top--;
          bytecode_index++;;
          break;
        }
      case SPVM_BYTECODE_C_CODE_DIVIDE_SHORT:
        if (call_stack[operand_stack_top].short_value == 0) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division (short / short)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          call_stack[operand_stack_top - 1].short_value /= call_stack[operand_stack_top].short_value;
          operand_stack_top--;
          bytecode_index++;;
          break;
        }
      case SPVM_BYTECODE_C_CODE_DIVIDE_INT:
        if (call_stack[operand_stack_top].int_value == 0) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division (int / int)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          call_stack[operand_stack_top - 1].int_value /= call_stack[operand_stack_top].int_value;
          operand_stack_top--;
          bytecode_index++;;
          break;
        }
      case SPVM_BYTECODE_C_CODE_DIVIDE_LONG:
        if (call_stack[operand_stack_top].long_value == 0) {
          SPVM_API_OBJECT* exception = api->new_string(api, "0 division (long / long)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          call_stack[operand_stack_top - 1].long_value /= call_stack[operand_stack_top].long_value;
          operand_stack_top--;
          bytecode_index++;;
          break;
        }
      case SPVM_BYTECODE_C_CODE_DIVIDE_FLOAT:
        call_stack[operand_stack_top - 1].float_value /= call_stack[operand_stack_top].float_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_DIVIDE_DOUBLE:
        call_stack[operand_stack_top - 1].double_value /= call_stack[operand_stack_top].double_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_REMAINDER_BYTE:
        call_stack[operand_stack_top - 1].byte_value
          = call_stack[operand_stack_top - 1].byte_value % call_stack[operand_stack_top].byte_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_REMAINDER_SHORT:
        call_stack[operand_stack_top - 1].short_value
          = call_stack[operand_stack_top - 1].short_value % call_stack[operand_stack_top].short_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_REMAINDER_INT:
        call_stack[operand_stack_top - 1].int_value
          = call_stack[operand_stack_top - 1].int_value % call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_REMAINDER_LONG:
        // z = a - (a/b) * b;
        call_stack[operand_stack_top - 1].long_value
          = call_stack[operand_stack_top - 1].long_value % call_stack[operand_stack_top].long_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_REMAINDER_FLOAT:
        call_stack[operand_stack_top - 1].float_value
          = (float)fmod((double)call_stack[operand_stack_top - 1].float_value, (double)call_stack[operand_stack_top].float_value);
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_REMAINDER_DOUBLE:
        call_stack[operand_stack_top - 1].double_value
          = fmod(call_stack[operand_stack_top - 1].double_value, call_stack[operand_stack_top].double_value);
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_NEGATE_BYTE:
        call_stack[operand_stack_top].byte_value = -call_stack[operand_stack_top].byte_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_NEGATE_SHORT:
        call_stack[operand_stack_top].short_value = -call_stack[operand_stack_top].short_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_NEGATE_INT:
        call_stack[operand_stack_top].int_value = -call_stack[operand_stack_top].int_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_NEGATE_LONG:
        call_stack[operand_stack_top].long_value = -call_stack[operand_stack_top].long_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_NEGATE_FLOAT:
        call_stack[operand_stack_top].float_value = -call_stack[operand_stack_top].float_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_NEGATE_DOUBLE:
        call_stack[operand_stack_top].double_value = -call_stack[operand_stack_top].double_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_LEFT_SHIFT_BYTE:
        call_stack[operand_stack_top - 1].byte_value <<= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_LEFT_SHIFT_SHORT:
        call_stack[operand_stack_top - 1].short_value <<= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_LEFT_SHIFT_INT:
        call_stack[operand_stack_top - 1].int_value <<= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_LEFT_SHIFT_LONG:
        call_stack[operand_stack_top - 1].long_value <<= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_BYTE:
        call_stack[operand_stack_top - 1].byte_value >>= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_SHORT:
        call_stack[operand_stack_top - 1].short_value >>= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_INT:
        call_stack[operand_stack_top - 1].int_value >>= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_LONG:
        call_stack[operand_stack_top - 1].long_value >>= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_BYTE:
        call_stack[operand_stack_top - 1].byte_value
          = (int8_t)(((uint8_t)call_stack[operand_stack_top - 1].byte_value) >> call_stack[operand_stack_top].int_value);
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_SHORT:
        call_stack[operand_stack_top - 1].short_value
          = (int16_t)(((uint16_t)call_stack[operand_stack_top - 1].short_value) >> call_stack[operand_stack_top].int_value);
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_INT:
        call_stack[operand_stack_top - 1].int_value
          = (int32_t)(((uint32_t)call_stack[operand_stack_top - 1].int_value) >> call_stack[operand_stack_top].int_value);
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_LONG:
        call_stack[operand_stack_top - 1].long_value
          = (int64_t)(((uint64_t)call_stack[operand_stack_top - 1].long_value) >> call_stack[operand_stack_top].int_value);
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_AND_BYTE:
        call_stack[operand_stack_top - 1].byte_value &= call_stack[operand_stack_top].byte_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_AND_SHORT:
        call_stack[operand_stack_top - 1].short_value &= call_stack[operand_stack_top].short_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_AND_INT:
        call_stack[operand_stack_top - 1].int_value &= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_AND_LONG:
        call_stack[operand_stack_top - 1].long_value &= call_stack[operand_stack_top].long_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_OR_BYTE:
        call_stack[operand_stack_top - 1].byte_value |= call_stack[operand_stack_top].byte_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_OR_SHORT:
        call_stack[operand_stack_top - 1].short_value |= call_stack[operand_stack_top].short_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_OR_INT:
        call_stack[operand_stack_top - 1].int_value |= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_OR_LONG:
        call_stack[operand_stack_top - 1].long_value |= call_stack[operand_stack_top].long_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_XOR_BYTE:
        call_stack[operand_stack_top - 1].byte_value ^= call_stack[operand_stack_top].byte_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_XOR_SHORT:
        call_stack[operand_stack_top - 1].short_value ^= call_stack[operand_stack_top].short_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_XOR_INT:
        call_stack[operand_stack_top - 1].int_value ^= call_stack[operand_stack_top].int_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_BIT_XOR_LONG:
        call_stack[operand_stack_top - 1].long_value ^= call_stack[operand_stack_top].long_value;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_INC_BYTE:
        call_stack[bytecodes[bytecode_index + 1]].byte_value += (int8_t)(bytecodes[bytecode_index + 2]);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_INC_SHORT:
        call_stack[bytecodes[bytecode_index + 1]].short_value += (int16_t)(bytecodes[bytecode_index + 2]);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_INC_INT:
        call_stack[bytecodes[bytecode_index + 1]].int_value += (int32_t)(bytecodes[bytecode_index + 2]);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_INC_LONG:
        call_stack[bytecodes[bytecode_index + 1]].long_value += (int64_t)(bytecodes[bytecode_index + 2]);
        bytecode_index += 3;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_LONG:
        call_stack[operand_stack_top].long_value = (int64_t)call_stack[operand_stack_top].int_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_FLOAT:
        call_stack[operand_stack_top].float_value = (float)call_stack[operand_stack_top].int_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_DOUBLE:
        call_stack[operand_stack_top].double_value = (double)call_stack[operand_stack_top].int_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_INT:
        call_stack[operand_stack_top].int_value = (int32_t)call_stack[operand_stack_top].long_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_FLOAT:
        call_stack[operand_stack_top].float_value = (float)call_stack[operand_stack_top].long_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_DOUBLE:
        call_stack[operand_stack_top].double_value = (double)call_stack[operand_stack_top].long_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_INT:
        call_stack[operand_stack_top].int_value = (int32_t)call_stack[operand_stack_top].float_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_LONG:
        call_stack[operand_stack_top].long_value = (int64_t)call_stack[operand_stack_top].float_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_DOUBLE:
        call_stack[operand_stack_top].double_value = (double)call_stack[operand_stack_top].float_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_INT:
        call_stack[operand_stack_top].int_value = (int32_t)call_stack[operand_stack_top].double_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_LONG:
        call_stack[operand_stack_top].long_value = (int64_t)call_stack[operand_stack_top].double_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_FLOAT:
        call_stack[operand_stack_top].float_value = (float)call_stack[operand_stack_top].double_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_BYTE:
        call_stack[operand_stack_top].byte_value = (int8_t)(call_stack[operand_stack_top].int_value);
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_SHORT:
        call_stack[operand_stack_top].short_value = (int16_t)(call_stack[operand_stack_top].int_value);
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_INT:
        call_stack[operand_stack_top].int_value = (int32_t)call_stack[operand_stack_top].byte_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_INT:
        call_stack[operand_stack_top].int_value = (int32_t)call_stack[operand_stack_top].short_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_LONG:
        call_stack[operand_stack_top].long_value = (int64_t)call_stack[operand_stack_top].byte_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_FLOAT:
        call_stack[operand_stack_top].float_value = (float)call_stack[operand_stack_top].byte_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_DOUBLE:
        call_stack[operand_stack_top].double_value = (double)call_stack[operand_stack_top].byte_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_BYTE:
        call_stack[operand_stack_top].byte_value = (int8_t)call_stack[operand_stack_top].short_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_LONG:
        call_stack[operand_stack_top].long_value = (int64_t)call_stack[operand_stack_top].short_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_FLOAT:
        call_stack[operand_stack_top].float_value = (float)call_stack[operand_stack_top].short_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_DOUBLE:
        call_stack[operand_stack_top].double_value = (double)call_stack[operand_stack_top].short_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_BYTE:
        call_stack[operand_stack_top].byte_value = (int8_t)call_stack[operand_stack_top].long_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_SHORT:
        call_stack[operand_stack_top].short_value = (int16_t)call_stack[operand_stack_top].long_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_BYTE:
        // TODO
        call_stack[operand_stack_top].byte_value = (int8_t)call_stack[operand_stack_top].float_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_SHORT:
        // TODO
        call_stack[operand_stack_top].short_value = (int16_t)call_stack[operand_stack_top].float_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_BYTE:
        // TODO
        call_stack[operand_stack_top].byte_value = (int8_t)call_stack[operand_stack_top].double_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_SHORT:
        // TODO
        call_stack[operand_stack_top].short_value = (int16_t)call_stack[operand_stack_top].double_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_SHORT:
        call_stack[operand_stack_top].short_value = (int16_t)call_stack[operand_stack_top].byte_value;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CMP_BYTE:
        // z = (x > y) + (x < y) * -1
        call_stack[operand_stack_top - 1].int_value
          = (call_stack[operand_stack_top - 1].byte_value > call_stack[operand_stack_top].byte_value)
          + (call_stack[operand_stack_top - 1].byte_value < call_stack[operand_stack_top].byte_value) * -1;
        
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CMP_SHORT:
        // z = (x > y) + (x < y) * -1
        call_stack[operand_stack_top - 1].int_value
          = (call_stack[operand_stack_top - 1].short_value > call_stack[operand_stack_top].short_value)
          + (call_stack[operand_stack_top - 1].short_value < call_stack[operand_stack_top].short_value) * -1;
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CMP_LONG:
        // z = (x > y) + (x < y) * -1
        call_stack[operand_stack_top - 1].int_value
          = (call_stack[operand_stack_top - 1].long_value > call_stack[operand_stack_top].long_value)
          + (call_stack[operand_stack_top - 1].long_value < call_stack[operand_stack_top].long_value) * -1;
        
        
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CMP_FLOAT_L:
        call_stack[operand_stack_top - 1].int_value
          = (call_stack[operand_stack_top - 1].float_value > call_stack[operand_stack_top].float_value)
          + (call_stack[operand_stack_top - 1].float_value < call_stack[operand_stack_top].float_value) * -1
          + -!!(
            isnan(call_stack[operand_stack_top - 1].float_value)
            | isnan(call_stack[operand_stack_top - 1].float_value)
          );
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CMP_FLOAT_G:
        call_stack[operand_stack_top - 1].int_value
          = (call_stack[operand_stack_top - 1].float_value > call_stack[operand_stack_top].float_value)
          + (call_stack[operand_stack_top - 1].float_value < call_stack[operand_stack_top].float_value) * -1
          + !!(
            isnan(call_stack[operand_stack_top - 1].float_value)
            | isnan(call_stack[operand_stack_top - 1].float_value)
          );
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CMP_DOUBLE_L:
        call_stack[operand_stack_top - 1].int_value
          = (call_stack[operand_stack_top - 1].double_value > call_stack[operand_stack_top].double_value)
          + (call_stack[operand_stack_top - 1].double_value < call_stack[operand_stack_top].double_value) * -1
          + -!!(
            isnan(call_stack[operand_stack_top - 1].double_value)
            | isnan(call_stack[operand_stack_top].double_value)
          );
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_CMP_DOUBLE_G:
        call_stack[operand_stack_top - 1].int_value
          = (call_stack[operand_stack_top - 1].double_value > call_stack[operand_stack_top].double_value)
          + (call_stack[operand_stack_top - 1].double_value < call_stack[operand_stack_top].double_value) * -1
          + !!(
            isnan(call_stack[operand_stack_top - 1].double_value)
            | isnan(call_stack[operand_stack_top].double_value)
          );
        operand_stack_top--;
        bytecode_index++;;
        break;
      case SPVM_BYTECODE_C_CODE_IF_EQ_ZERO:
        success = call_stack[operand_stack_top].int_value == 0;
        bytecode_index += success * (int16_t)(bytecodes[bytecode_index + 1]) + (~success & 1) * 2;
        operand_stack_top--;
        break;
      case SPVM_BYTECODE_C_CODE_IF_NE_ZERO:
        success = call_stack[operand_stack_top].int_value != 0;
        bytecode_index += success * (int16_t)(bytecodes[bytecode_index + 1]) + (~success & 1) * 2;
        operand_stack_top--;
        break;
      case SPVM_BYTECODE_C_CODE_IF_LT_ZERO:
        success = call_stack[operand_stack_top].int_value < 0;
        bytecode_index += success * (int16_t)(bytecodes[bytecode_index + 1]) + (~success & 1) * 2;
        operand_stack_top--;
        break;
      case SPVM_BYTECODE_C_CODE_IF_GE_ZERO:
        success = call_stack[operand_stack_top].int_value >= 0;
        bytecode_index += success * (int16_t)(bytecodes[bytecode_index + 1]) + (~success & 1) * 2;
        operand_stack_top--;
        break;
      case SPVM_BYTECODE_C_CODE_IF_GT_ZERO:
        success = call_stack[operand_stack_top].int_value > 0;
        bytecode_index += success * (int16_t)(bytecodes[bytecode_index + 1]) + (~success & 1) * 2;
        operand_stack_top--;
        break;
      case SPVM_BYTECODE_C_CODE_IF_LE_ZERO:
        success = call_stack[operand_stack_top].int_value <= 0;
        bytecode_index += success * (int16_t)(bytecodes[bytecode_index + 1]) + (~success & 1) * 2;
        operand_stack_top--;
        break;
      case SPVM_BYTECODE_C_CODE_IF_EQ_CMP:
        success = call_stack[operand_stack_top - 1].int_value == call_stack[operand_stack_top].int_value;
        bytecode_index += success * (int16_t)(bytecodes[bytecode_index + 1]) + (~success & 1) * 2;
        operand_stack_top -= 2;
        break;
      case SPVM_BYTECODE_C_CODE_IF_NE_CMP:
        success = call_stack[operand_stack_top - 1].int_value != call_stack[operand_stack_top].int_value;
        bytecode_index += success * (int16_t)(bytecodes[bytecode_index + 1]) + (~success & 1) * 2;
        operand_stack_top -= 2;
        break;
      case SPVM_BYTECODE_C_CODE_IF_LT_CMP:
        success = call_stack[operand_stack_top - 1].int_value < call_stack[operand_stack_top].int_value;
        bytecode_index += success * (int16_t)(bytecodes[bytecode_index + 1]) + (~success & 1) * 2;
        operand_stack_top -= 2;
        break;
      case SPVM_BYTECODE_C_CODE_IF_GE_CMP:
        success = call_stack[operand_stack_top - 1].int_value >= call_stack[operand_stack_top].int_value;
        bytecode_index += success * (int16_t)(bytecodes[bytecode_index + 1]) + (~success & 1) * 2;
        operand_stack_top -= 2;
        break;
      case SPVM_BYTECODE_C_CODE_IF_GT_CMP:
        success = call_stack[operand_stack_top - 1].int_value > call_stack[operand_stack_top].int_value;
        bytecode_index += success * (int16_t)(bytecodes[bytecode_index + 1]) + (~success & 1) * 2;
        operand_stack_top -= 2;
        break;
      case SPVM_BYTECODE_C_CODE_IF_LE_CMP:
        success = call_stack[operand_stack_top - 1].int_value <= call_stack[operand_stack_top].int_value;
        bytecode_index += success * (int16_t)(bytecodes[bytecode_index + 1]) + (~success & 1) * 2;
        operand_stack_top -= 2;
        break;
      case SPVM_BYTECODE_C_CODE_IF_EQ_CMP_OBJECT:
        success = call_stack[operand_stack_top - 1].object_value == call_stack[operand_stack_top].object_value;
        bytecode_index += success * (int16_t)(bytecodes[bytecode_index + 1]) + (~success & 1) * 2;
        operand_stack_top -= 2;
        break;
      case SPVM_BYTECODE_C_CODE_IF_NE_CMP_OBJECT:
        success = call_stack[operand_stack_top - 1].object_value != call_stack[operand_stack_top].object_value;
        bytecode_index += success * (int16_t)(bytecodes[bytecode_index + 1]) + (~success & 1) * 2;
        operand_stack_top -= 2;
        break;
      case SPVM_BYTECODE_C_CODE_GOTO:
        bytecode_index += (int16_t)(bytecodes[bytecode_index + 1]);
        break;
      case SPVM_BYTECODE_C_CODE_TABLE_SWITCH: {
        // default offset
        int32_t default_offset = *(int32_t*)(&bytecodes[bytecode_index + 1]);
        
        // min
        int32_t min = *(int32_t*)(&bytecodes[bytecode_index + 1 + 1]);
        
        // max
        int32_t max = *(int32_t*)(&bytecodes[bytecode_index + 1 + 1 * 2]);
        
        if (call_stack[operand_stack_top].int_value >= min && call_stack[operand_stack_top].int_value <= max) {
          int32_t branch_offset
            = *(int32_t*)((&bytecodes[bytecode_index + 1 + 1 * 3]) + (call_stack[operand_stack_top].int_value - min) * 1);
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
        int32_t default_offset = *(int32_t*)(&bytecodes[bytecode_index + 1]);
        
        // npare
        int32_t pair_count = *(int32_t*)(&bytecodes[bytecode_index + 1 + 1]);
        
        // min
        int32_t min = *(int32_t*)(&bytecodes[bytecode_index + 1 + 1 * 2]);
        
        // max
        int32_t max = *(int32_t*)(&bytecodes[bytecode_index + 1 + 1 * 2 + ((pair_count - 1) * 1 * 2)]);
        
        if (call_stack[operand_stack_top].int_value >= min && call_stack[operand_stack_top].int_value <= max) {
          // 2 branch searching
          int32_t cur_min_pos = 0;
          int32_t cur_max_pos = pair_count - 1;

          while (1) {
            if (cur_max_pos < cur_min_pos) {
              bytecode_index += default_offset;
              break;
            }
            int32_t cur_half_pos = cur_min_pos + (cur_max_pos - cur_min_pos) / 2;
            int32_t cur_half = *(int32_t*)(&bytecodes[bytecode_index + 1 + 1 * 2 + (cur_half_pos * 1 * 2)]);
            
            if (call_stack[operand_stack_top].int_value > cur_half) {
              cur_min_pos = cur_half_pos + 1;
            }
            else if (call_stack[operand_stack_top].int_value < cur_half) {
              cur_max_pos = cur_half_pos - 1;
            }
            else {
              int32_t branch_offset = *(int32_t*)(&bytecodes[bytecode_index + 1 + 1 * 2 + (cur_half_pos * 1 * 2) + 1]);
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
      case SPVM_BYTECODE_C_CODE_NEW_OBJECT: {
        // Get subroutine ID
        int32_t type_id = bytecodes[bytecode_index + 1];
        
        SPVM_API_OBJECT* object = api->new_object(api, type_id);

        // Memory allocation error
        if (__builtin_expect(!object, 0)) {
          // Sub name
          int32_t abs_name_id = api->get_sub_name_id(api, sub_id);
          const char* sub_name = (char*)&constant_pool[abs_name_id + 1];
          
          // File name
          int32_t file_name_id = api->get_sub_file_name_id(api, sub_id);
          const char* file_name = (char*)&constant_pool[file_name_id + 1];
          
          fprintf(stderr, "Failed to allocate memory(new package) from %s at %s\n", sub_name, file_name);
          abort();
        }
        
        // Push object
        operand_stack_top++;
        call_stack[operand_stack_top].object_value = (SPVM_API_OBJECT*)object;
        
        bytecode_index += 2;
        break;
      }
      case SPVM_BYTECODE_C_CODE_NEW_BYTE_ARRAY: {
        
        // length
        int32_t length = call_stack[operand_stack_top].int_value;
        
        SPVM_API_OBJECT* object = api->new_byte_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          // Set array
          call_stack[operand_stack_top].object_value = object;
          
          bytecode_index++;;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_NEW_SHORT_ARRAY: {
        
        // length
        int32_t length = call_stack[operand_stack_top].int_value;
        
        SPVM_API_OBJECT* object = api->new_short_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          // Set array
          call_stack[operand_stack_top].object_value = object;
          
          bytecode_index++;;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_NEW_INT_ARRAY: {
        
        // length
        int32_t length = call_stack[operand_stack_top].int_value;
        
        SPVM_API_OBJECT* object = api->new_int_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          // Set array
          call_stack[operand_stack_top].object_value = object;
          
          bytecode_index++;;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_NEW_LONG_ARRAY: {
        
        // length
        int32_t length = call_stack[operand_stack_top].int_value;
        
        SPVM_API_OBJECT* object = api->new_long_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          // Set array
          call_stack[operand_stack_top].object_value = object;
          
          bytecode_index++;;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_NEW_FLOAT_ARRAY: {
        
        // length
        int32_t length = call_stack[operand_stack_top].int_value;
        
        SPVM_API_OBJECT* object = api->new_float_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          // Set array
          call_stack[operand_stack_top].object_value = object;
          
          bytecode_index++;;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_NEW_DOUBLE_ARRAY: {
        
        // length
        int32_t length = call_stack[operand_stack_top].int_value;
        
        SPVM_API_OBJECT* object = api->new_double_array(api, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          // Set array
          call_stack[operand_stack_top].object_value = object;
          
          bytecode_index++;;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_NEW_OBJECT_ARRAY: {
        int32_t element_type_id = bytecodes[bytecode_index + 1];
        
        // length
        int32_t length = call_stack[operand_stack_top].int_value;
        
        SPVM_API_OBJECT* object = api->new_object_array(api, element_type_id, length);
        
        if (__builtin_expect(object == NULL, 0)) {
          // Throw exception
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          // Set object
          call_stack[operand_stack_top].object_value = object;
          
          bytecode_index += 2;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_NEW_STRING: {
        int32_t name_id = bytecodes[bytecode_index + 1];
        
        SPVM_API_OBJECT* string = api->new_string(api, (char*)&constant_pool[name_id + 1], constant_pool[name_id]);
        if (__builtin_expect(string != NULL, 1)) {
          // Set string
          operand_stack_top++;
          call_stack[operand_stack_top].object_value = string;
          
          bytecode_index += 2;
          break;
        }
        // Memory allocation error
        else {
          // Sub name
          int32_t abs_name_id = api->get_sub_name_id(api, sub_id);
          const char* sub_name = (char*)&constant_pool[abs_name_id + 1];
          
          // File name
          int32_t file_name_id = api->get_sub_file_name_id(api, sub_id);
          const char* file_name = (char*)&constant_pool[file_name_id + 1];
          
          fprintf(stderr, "Failed to allocate memory(new string) from %s at %s\n", sub_name, file_name);
          abort();
        }
      }
      case SPVM_BYTECODE_C_CODE_ARRAY_LENGTH:
        if (call_stack[operand_stack_top].object_value == NULL) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Can't get array length of undef value.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          call_stack[operand_stack_top].int_value = *(int32_t*)((intptr_t)call_stack[operand_stack_top].object_value + OBJECT_HEADER_LENGTH_OFFSET);
          bytecode_index++;;
          break;
        }
      case SPVM_BYTECODE_C_CODE_IF_NULL:
        success = call_stack[operand_stack_top].object_value == (void*)NULL;
        bytecode_index += success * (int16_t)(bytecodes[bytecode_index + 1]) + (~success & 1) * 2;
        operand_stack_top--;
        break;
      case SPVM_BYTECODE_C_CODE_IF_NON_NULL:
        
        success = call_stack[operand_stack_top].object_value != (void*)NULL;
        bytecode_index += success * (int16_t)(bytecodes[bytecode_index + 1]) + (~success & 1) * 2;
        operand_stack_top--;
        break;
      case SPVM_BYTECODE_C_CODE_GET_FIELD_BYTE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top].object_value;
        if (__builtin_expect(!object, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object to get an byte field must not be undefined.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          int32_t index = bytecodes[bytecode_index + 1];
          call_stack[operand_stack_top].byte_value
            = *(int8_t*)((intptr_t)object + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index);
          bytecode_index += 2;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_SHORT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top].object_value;
        if (__builtin_expect(!object, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object to get an short field must not be undefined.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          int32_t index = bytecodes[bytecode_index + 1];
          call_stack[operand_stack_top].short_value
            = *(int16_t*)((intptr_t)object + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index);
          bytecode_index += 2;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_INT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top].object_value;
        if (__builtin_expect(!object, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object to get an int field must not be undefined.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          int32_t index = bytecodes[bytecode_index + 1];
          call_stack[operand_stack_top].int_value
            = *(int32_t*)((intptr_t)object + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index);
          bytecode_index += 2;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_LONG: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top].object_value;
        if (__builtin_expect(!object, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object to get an long field must not be undefined.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          int32_t index = bytecodes[bytecode_index + 1];
          call_stack[operand_stack_top].long_value
            = *(int64_t*)((intptr_t)object + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index);
          bytecode_index += 2;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_FLOAT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top].object_value;
        if (__builtin_expect(!object, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object to get an float field must not be undefined.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          int32_t index = bytecodes[bytecode_index + 1];
          call_stack[operand_stack_top].float_value
            = *(float*)((intptr_t)object + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index);
          
          bytecode_index += 2;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_DOUBLE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top].object_value;
        if (__builtin_expect(!object, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object to get an double field must not be undefined.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          int32_t index = bytecodes[bytecode_index + 1];
          call_stack[operand_stack_top].double_value
            = *(double*)((intptr_t)object + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index);
          bytecode_index += 2;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_GET_FIELD_OBJECT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top].object_value;
        if (__builtin_expect(!object, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object to get an object field must not be undefined.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          int32_t index = bytecodes[bytecode_index + 1];
          call_stack[operand_stack_top].object_value
            = *(void**)((intptr_t)call_stack[operand_stack_top].object_value + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index);
          bytecode_index += 2;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_WEAKEN_FIELD_OBJECT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top].object_value;
        if (__builtin_expect(!object, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object to weaken an object field must not be undefined.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          int32_t index = bytecodes[bytecode_index + 1];
          SPVM_API_OBJECT** object_address = (SPVM_API_OBJECT**)((intptr_t)object + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index);
          
          // Weaken object field
          if (*object_address != NULL) {
            SPVM_RUNTIME_API_weaken(api, object_address);
          }
          
          bytecode_index += 2;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_BYTE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        if (__builtin_expect(!object, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object to set an byte field must not be undefined.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          int32_t index = bytecodes[bytecode_index + 1];
          *(int8_t*)((intptr_t)object + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index)
            = call_stack[operand_stack_top].byte_value;
          operand_stack_top -= 2;
          bytecode_index += 2;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_SHORT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        if (__builtin_expect(!object, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object to set an short field must not be undefined.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          int32_t index = bytecodes[bytecode_index + 1];
          *(int16_t*)((intptr_t)object + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index)
            = call_stack[operand_stack_top].short_value;
          operand_stack_top -= 2;
          bytecode_index += 2;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_INT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        if (__builtin_expect(!object, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object to set an int field must not be undefined.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          int32_t index = bytecodes[bytecode_index + 1];
          *(int32_t*)((intptr_t)object + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index)
            = call_stack[operand_stack_top].int_value;
          
          operand_stack_top -= 2;
          bytecode_index += 2;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_LONG: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        if (__builtin_expect(!object, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object to set an long field must not be undefined.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          int32_t index = bytecodes[bytecode_index + 1];
          *(int64_t*)((intptr_t)object + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index)
            = call_stack[operand_stack_top].long_value;
          operand_stack_top -= 2;
          bytecode_index += 2;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_FLOAT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        if (__builtin_expect(!object, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object to set an float field must not be undefined.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          int32_t index = bytecodes[bytecode_index + 1];
          *(float*)((intptr_t)object + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index)
            = call_stack[operand_stack_top].float_value;
          operand_stack_top -= 2;
          bytecode_index += 2;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_DOUBLE: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        if (__builtin_expect(!object, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object to set an double field must not be undefined.", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          int32_t index = bytecodes[bytecode_index + 1];
          *(double*)((intptr_t)object + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index)
            = call_stack[operand_stack_top].double_value;
          operand_stack_top -= 2;
          bytecode_index += 2;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_SET_FIELD_OBJECT: {
        SPVM_API_OBJECT* object = (SPVM_API_OBJECT*)call_stack[operand_stack_top - 1].object_value;
        if (__builtin_expect(!object, 0)) {
          SPVM_API_OBJECT* exception = api->new_string(api, "Object to set an object field must not be undefined", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else {
          int32_t index = bytecodes[bytecode_index + 1];
          SPVM_API_OBJECT** object_address = (SPVM_API_OBJECT**)((intptr_t)object + OBJECT_HEADER_BYTE_SIZE + sizeof(SPVM_API_VALUE) * index);
          
          if (*object_address != NULL) {
            // If object is weak, unweaken
            if (api->isweak(api, *object_address)) {
              api->unweaken(api, object_address);
            }
            
            // Decrement old ojbect reference count
            api->dec_ref_count(api, *object_address);
          }
          
          // Store object
          *object_address = call_stack[operand_stack_top].object_value;
          
          // Increment new object reference count
          if (*object_address != NULL) {
            api->inc_ref_count(api, *object_address);
          }
          
          operand_stack_top -= 2;
          bytecode_index += 2;
          break;
        }
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_STRING: {
        SPVM_API_OBJECT* string1 = call_stack[operand_stack_top - 1].object_value;
        SPVM_API_OBJECT* string2 = call_stack[operand_stack_top].object_value;
        
        if (string1 == NULL) {
          SPVM_API_OBJECT* exception = api->new_string(api, ". operater left string must be defined(string . string)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        else if (string2 == NULL) {
          SPVM_API_OBJECT* exception = api->new_string(api, ". operater right string must be defined(string . string)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        int32_t string1_length = api->get_string_length(api, string1);
        int32_t string2_length = api->get_string_length(api, string2);
        
        int32_t string3_length = string1_length + string2_length;
        SPVM_API_OBJECT* string3 = api->new_string(api, NULL, string3_length);
        
        char* string1_chars = (char*)api->get_string_chars(api, string1);
        char* string2_chars = (char*)api->get_string_chars(api, string2);
        char* string3_chars = (char*)api->get_string_chars(api, string3);
        
        memcpy(string3_chars, string1_chars, string1_length);
        memcpy(string3_chars + string1_length, string2_chars, string2_length);
        
        call_stack[operand_stack_top - 1].object_value = string3;
        
        operand_stack_top--;
        bytecode_index++;;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_BYTE: {
        SPVM_API_OBJECT* string1 = call_stack[operand_stack_top - 1].object_value;
        int8_t string2 = call_stack[operand_stack_top].byte_value;
        
        if (string1 == NULL) {
          SPVM_API_OBJECT* exception = api->new_string(api, ". operater left string must be defined(string . byte)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        sprintf(tmp_string, "%" PRId8, string2);
        
        int32_t string1_length = api->get_string_length(api, string1);
        int32_t tmp_string_length = strlen(tmp_string);
        
        int32_t string3_length = string1_length + tmp_string_length;
        SPVM_API_OBJECT* string3 = api->new_string(api, NULL, string3_length);
        
        char* string1_chars = (char*)api->get_string_chars(api, string1);
        char* string3_chars = (char*)api->get_string_chars(api, string3);
        
        memcpy(string3_chars, string1_chars, string1_length);
        memcpy(string3_chars + string1_length, tmp_string, tmp_string_length);
        
        call_stack[operand_stack_top - 1].object_value = string3;
        
        operand_stack_top--;
        bytecode_index++;;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_SHORT: {
        SPVM_API_OBJECT* string1 = call_stack[operand_stack_top - 1].object_value;
        int16_t string2 = call_stack[operand_stack_top].short_value;
        
        if (string1 == NULL) {
          SPVM_API_OBJECT* exception = api->new_string(api, ". operater left string must be defined(string . short)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        sprintf(tmp_string, "%" PRId16, string2);
        
        int32_t string1_length = api->get_string_length(api, string1);
        int32_t tmp_string_length = strlen(tmp_string);
        
        int32_t string3_length = string1_length + tmp_string_length;
        SPVM_API_OBJECT* string3 = api->new_string(api, NULL, string3_length);
        
        char* string1_chars = (char*)api->get_string_chars(api, string1);
        char* string3_chars = (char*)api->get_string_chars(api, string3);
        
        memcpy(string3_chars, string1_chars, string1_length);
        memcpy(string3_chars + string1_length, tmp_string, tmp_string_length);
        
        call_stack[operand_stack_top - 1].object_value = string3;
        
        operand_stack_top--;
        bytecode_index++;;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_INT: {
        SPVM_API_OBJECT* string1 = call_stack[operand_stack_top - 1].object_value;
        int32_t string2 = call_stack[operand_stack_top].int_value;
        
        if (string1 == NULL) {
          SPVM_API_OBJECT* exception = api->new_string(api, ". operater left string must be defined(string . int)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        sprintf(tmp_string, "%" PRId32, string2);
        
        int32_t string1_length = api->get_string_length(api, string1);
        int32_t tmp_string_length = strlen(tmp_string);
        
        int32_t string3_length = string1_length + tmp_string_length;
        SPVM_API_OBJECT* string3 = api->new_string(api, NULL, string3_length);
        
        char* string1_chars = (char*)api->get_string_chars(api, string1);
        char* string3_chars = (char*)api->get_string_chars(api, string3);
        
        memcpy(string3_chars, string1_chars, string1_length);
        memcpy(string3_chars + string1_length, tmp_string, tmp_string_length);
        
        call_stack[operand_stack_top - 1].object_value = string3;
        
        operand_stack_top--;
        bytecode_index++;;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_LONG: {
        SPVM_API_OBJECT* string1 = call_stack[operand_stack_top - 1].object_value;
        int64_t string2 = call_stack[operand_stack_top].long_value;
        
        if (string1 == NULL) {
          SPVM_API_OBJECT* exception = api->new_string(api, ". operater left string must be defined(string . long)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        sprintf(tmp_string, "%" PRId64, string2);
        
        int32_t string1_length = api->get_string_length(api, string1);
        int32_t tmp_string_length = strlen(tmp_string);
        
        int32_t string3_length = string1_length + tmp_string_length;
        SPVM_API_OBJECT* string3 = api->new_string(api, NULL, string3_length);
        
        char* string1_chars = (char*)api->get_string_chars(api, string1);
        char* string3_chars = (char*)api->get_string_chars(api, string3);
        
        memcpy(string3_chars, string1_chars, string1_length);
        memcpy(string3_chars + string1_length, tmp_string, tmp_string_length);
        
        call_stack[operand_stack_top - 1].object_value = string3;
        
        operand_stack_top--;
        bytecode_index++;;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_FLOAT: {
        SPVM_API_OBJECT* string1 = call_stack[operand_stack_top - 1].object_value;
        float string2 = call_stack[operand_stack_top].float_value;
        
        if (string1 == NULL) {
          SPVM_API_OBJECT* exception = api->new_string(api, ". operater left string must be defined(string . float)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        sprintf(tmp_string, "%f", string2);
        
        int32_t string1_length = api->get_string_length(api, string1);
        int32_t tmp_string_length = strlen(tmp_string);
        
        int32_t string3_length = string1_length + tmp_string_length;
        SPVM_API_OBJECT* string3 = api->new_string(api, NULL, string3_length);
        
        char* string1_chars = (char*)api->get_string_chars(api, string1);
        char* string3_chars = (char*)api->get_string_chars(api, string3);
        
        memcpy(string3_chars, string1_chars, string1_length);
        memcpy(string3_chars + string1_length, tmp_string, tmp_string_length);
        
        call_stack[operand_stack_top - 1].object_value = string3;
        
        operand_stack_top--;
        bytecode_index++;;
        break;
      }
      case SPVM_BYTECODE_C_CODE_CONCAT_STRING_DOUBLE: {
        SPVM_API_OBJECT* string1 = call_stack[operand_stack_top - 1].object_value;
        double string2 = call_stack[operand_stack_top].double_value;
        
        if (string1 == NULL) {
          SPVM_API_OBJECT* exception = api->new_string(api, ". operater left string must be defined(string . double)", 0);
          api->set_exception(api, exception);
          goto label_SPVM_BYTECODE_C_CODE_CROAK;
        }
        
        sprintf(tmp_string, "%f", string2);
        
        int32_t string1_length = api->get_string_length(api, string1);
        int32_t tmp_string_length = strlen(tmp_string);
        
        int32_t string3_length = string1_length + tmp_string_length;
        SPVM_API_OBJECT* string3 = api->new_string(api, NULL, string3_length);
        
        char* string1_chars = (char*)api->get_string_chars(api, string1);
        char* string3_chars = (char*)api->get_string_chars(api, string3);
        
        memcpy(string3_chars, string1_chars, string1_length);
        memcpy(string3_chars + string1_length, tmp_string, tmp_string_length);
        
        call_stack[operand_stack_top - 1].object_value = string3;
        
        operand_stack_top--;
        bytecode_index++;;
        break;
      }
      
      case SPVM_BYTECODE_C_CODE_CURRENT_LINE:
        current_line = bytecodes[bytecode_index + 1];
        bytecode_index += 2;
        break;
    }
  }
}
