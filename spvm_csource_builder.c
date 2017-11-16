#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#include "spvm_compiler.h"
#include "spvm_csource_builder.h"
#include "spvm_bytecode.h"
#include "spvm_bytecode_array.h"
#include "spvm_constant.h"
#include "spvm_op.h"
#include "spvm_type.h"
#include "spvm_type.h"
#include "spvm_dynamic_array.h"
#include "spvm_sub.h"
#include "spvm_var.h"
#include "spvm_my_var.h"
#include "spvm_compiler_allocator.h"
#include "spvm_package.h"
#include "spvm_call_field.h"
#include "spvm_call_sub.h"
#include "spvm_hash.h"
#include "spvm_field.h"
#include "spvm_switch_info.h"
#include "spvm_constant_pool.h"
#include "spvm_type.h"
#include "spvm_limit.h"
#include "spvm_constant_pool_sub.h"
#include "spvm_constant_pool_field.h"
#include "spvm_constant_pool_package.h"
#include "spvm_object.h"
#include "spvm_our.h"
#include "spvm_package_var.h"
#include "spvm_string_buffer.h"

void SPVM_CSOURCE_BUILDER_build_csource(SPVM_COMPILER* compiler) {
  
  SPVM_STRING_BUFFER* string_buffer = SPVM_STRING_BUFFER_new(0);
  
  // API header
  SPVM_STRING_BUFFER_add(string_buffer, "#include <spvm_api.h>\n");
  
  // Operator macro
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_ADD_BYTE(x, y) ((int8_t)x + (int8_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_ADD_SHORT(x, y) ((int16_t)x + (int16_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_ADD_INT(x, y) ((int32_t)x + (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_ADD_LONG(x, y) ((int64_t)x + (int64_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_ADD_FLOAT(x, y) ((float)x + (float)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_ADD_DOUBLE(x, y) ((double)x + (double)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_SUBTRACT_BYTE(x, y) ((int8_t)x - (int8_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_SUBTRACT_SHORT(x, y) ((int16_t)x - (int16_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_SUBTRACT_INT(x, y) ((int32_t)x - (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_SUBTRACT_LONG(x, y) ((int64_t)x - (int64_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_SUBTRACT_FLOAT(x, y) ((float)x - (float)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_SUBTRACT_DOUBLE(x, y) ((double)x - (double)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_MULTIPY_BYTE(x, y) ((int8_t)x * (int8_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_MULTIPY_SHORT(x, y) ((int16_t)x * (int16_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_MULTIPY_INT(x, y) ((int32_t)x * (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_MULTIPY_LONG(x, y) ((int64_t)x * (int64_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_MULTIPY_FLOAT(x, y) ((float)x * (float)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_MULTIPY_DOUBLE(x, y) ((double)x * (double)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_DIVIDE_BYTE(x, y) ((int8_t)x / (int8_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_DIVIDE_SHORT(x, y) ((int16_t)x / (int16_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_DIVIDE_INT(x, y) ((int32_t)x / (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_DIVIDE_LONG(x, y) ((int64_t)x / (int64_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_DIVIDE_FLOAT(x, y) ((float)x / (float)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_DIVIDE_DOUBLE(x, y) ((double)x / (double)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_REMAINDER_BYTE(x, y) ((int8_t)x % (int8_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_REMAINDER_SHORT(x, y) ((int16_t)x % (int16_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_REMAINDER_INT(x, y) ((int32_t)x % (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_REMAINDER_LONG(x, y) ((int64_t)x % (int64_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_REMAINDER_FLOAT(x, y) ((float)x % (float)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_REMAINDER_DOUBLE(x, y) ((double)x % (double)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_LEFT_SHIFT_BYTE(x, y) ((int8_t)x << (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_LEFT_SHIFT_SHORT(x, y) ((int16_t)x << (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_LEFT_SHIFT_INT(x, y) ((int32_t)x << (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_LEFT_SHIFT_LONG(x, y) ((int64_t)x << (int32_t)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_RIGHT_SHIFT_BYTE(x, y) ((int8_t)x >> (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_RIGHT_SHIFT_SHORT(x, y) ((int16_t)x >> (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_RIGHT_SHIFT_INT(x, y) ((int32_t)x >> (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_RIGHT_SHIFT_LONG(x, y) ((int64_t)x >> (int32_t)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_RIGHT_SHIFT_UNSIGNED_BYTE(x, y) ((int8_t)((uint8_t)x >> (int32_t)y))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_RIGHT_SHIFT_UNSIGNED_SHORT(x, y) ((int16_t)((uint16_t)x >> (int32_t)y))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_RIGHT_SHIFT_UNSIGNED_INT(x, y) ((int32_t)((uint32_t)x >> (int32_t)y))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_RIGHT_SHIFT_UNSIGNED_LONG(x, y) ((int64_t)((uint64_t)x >> (int32_t)y))\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_AND_BYTE(x, y) ((int8_t)x & (int8_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_AND_SHORT(x, y) ((int16_t)x & (int16_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_AND_INT(x, y) ((int32_t)x & (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_AND_LONG(x, y) ((int64_t)x & (int64_t)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_OR_BYTE(x, y) ((int8_t)x | (int8_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_OR_SHORT(x, y) ((int16_t)x | (int16_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_OR_INT(x, y) ((int32_t)x | (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_OR_LONG(x, y) ((int64_t)x | (int64_t)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_XOR_BYTE(x, y) ((int8_t)x ^ (int8_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_XOR_SHORT(x, y) ((int16_t)x ^ (int16_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_XOR_INT(x, y) ((int32_t)x ^ (int32_t)y)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_BIT_XOR_LONG(x, y) ((int64_t)x ^ (int64_t)y)\n");

  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_AND(x, y) ((x) && (y))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_OR(x, y) ((x) || (y))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_MACRO_NOT(x) (!(x))\n");

  // warn("AAAAAAAA\n%s", string_buffer->buffer);
  
  {
    int32_t sub_pos;
    for (sub_pos = 0; sub_pos < compiler->op_subs->length; sub_pos++) {
      SPVM_OP* op_sub = SPVM_DYNAMIC_ARRAY_fetch(compiler->op_subs, sub_pos);
      SPVM_SUB* sub = op_sub->uv.sub;
      
      // Check sub information
      assert(sub->id > -1);
      assert(sub->op_name);
      assert(sub->op_return_type);
      assert(sub->abs_name);
      assert(sub->file_name);
      
      if (sub->is_native) {
        continue;
      }
      
      // Run OPs
      SPVM_OP* op_base = SPVM_OP_get_op_block_from_op_sub(compiler, op_sub);
      SPVM_OP* op_cur = op_base;
      _Bool finish = 0;
      
      // IF bytecode index(except loop)
      SPVM_DYNAMIC_ARRAY* if_bytecode_index_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
      
      // GOTO bytecode index for last
      SPVM_DYNAMIC_ARRAY* goto_last_bytecode_index_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
      
      // GOTO bytecode index for end of if block
      SPVM_DYNAMIC_ARRAY* goto_if_block_end_bytecode_index_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
      
      // GOTO bytecode index for loop start
      SPVM_DYNAMIC_ARRAY* goto_loop_start_bytecode_index_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
      
      // GOTO bytecode index for exception handler
      SPVM_DYNAMIC_ARRAY* push_catch_exception_bytecode_index_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);

      // Switch stack
      SPVM_DYNAMIC_ARRAY* switch_info_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
      
      while (op_cur) {
        // [START]Preorder traversal position
        
        switch (op_cur->code) {
          case SPVM_OP_C_CODE_BLOCK: {
            if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_LOOP) {
              // Add goto
              // TODO SPVM_BYTECODE_C_CODE_GOTO);
              
              
              
              
              int32_t* bytecode_index_ptr = SPVM_COMPILER_ALLOCATOR_alloc_int(compiler, compiler->allocator);
              
              SPVM_DYNAMIC_ARRAY_push(goto_loop_start_bytecode_index_stack, bytecode_index_ptr);
              
              // TODO 0);
            }
            else if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_EVAL) {
              // TODO SPVM_BYTECODE_C_CODE_PUSH_CATCH_EXCEPTION);
              
              int32_t* bytecode_index_ptr = SPVM_COMPILER_ALLOCATOR_alloc_int(compiler, compiler->allocator);
              
              SPVM_DYNAMIC_ARRAY_push(push_catch_exception_bytecode_index_stack, bytecode_index_ptr);
              
              // TODO 0);
            }
          }
        }
        
        // [END]Preorder traversal position
        
        if (op_cur->first) {
          op_cur = op_cur->first;
        }
        else {
          while (1) {
            if (compiler->debug) {
              _Bool is_operation;
              switch (op_cur->code) {
                case SPVM_OP_C_CODE_NULL:
                case SPVM_OP_C_CODE_STAB:
                case SPVM_OP_C_CODE_PUSHMARK:
                case SPVM_OP_C_CODE_LIST:
                case SPVM_OP_C_CODE_BLOCK:
                case SPVM_OP_C_CODE_NAME:
                case SPVM_OP_C_CODE_MY:
                case SPVM_OP_C_CODE_TYPE:
                  is_operation = 0;
                  break;
                default:
                  is_operation = 1;
              }
              
              if (is_operation) {
                // TODO SPVM_BYTECODE_C_CODE_CURRENT_LINE);
                
                
                

                // TODO op_cur->line);
              }
            }
            
            // [START]Postorder traversal position
            switch (op_cur->code) {
              case SPVM_OP_C_CODE_SWITCH_CONDITION: {
                
                SPVM_SWITCH_INFO* switch_info = op_cur->uv.switch_info;
                
                // tableswitch
                if (switch_info->code == SPVM_SWITCH_INFO_C_CODE_TABLE_SWITCH) {
                  // TODO switch_info->max);
                }
                // lookupswitch
                else if (switch_info->code == SPVM_SWITCH_INFO_C_CODE_LOOKUP_SWITCH) {
                  // TODO
                }
                
                break;
              }
              case SPVM_OP_C_CODE_SWITCH: {
                
                // Pop switch information
                SPVM_SWITCH_INFO* switch_info = SPVM_DYNAMIC_ARRAY_pop(switch_info_stack);
                int32_t switch_bytecode_index = switch_info->bytecode_index;
                int32_t default_bytecode_index = switch_info->default_bytecode_index;
                SPVM_DYNAMIC_ARRAY* case_bytecode_indexes = switch_info->case_bytecode_indexes;
                
                // tableswitch
                if (switch_info->code == SPVM_SWITCH_INFO_C_CODE_TABLE_SWITCH) {
                  // TODO
                }
                // lookupswitch
                else if (switch_info->code == SPVM_SWITCH_INFO_C_CODE_LOOKUP_SWITCH) {
                  // TODO
                }
                
                // Set last position
                while (goto_last_bytecode_index_stack->length > 0) {
                  // TODO
                }
                
                break;
              }
              case SPVM_OP_C_CODE_CASE: {
                // TODO
                break;
              }
              case SPVM_OP_C_CODE_DEFAULT: {
                // TODO
                break;
              }
              case SPVM_OP_C_CODE_CALL_FIELD: {
                
                if (!op_cur->is_assign_left) {
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                  
                  // Weaken field
                  if (op_cur->flag &= SPVM_OP_C_FLAG_CALL_FIELD_WEAKEN) {
                    // TODO SPVM_BYTECODE_C_CODE_WEAKEN_FIELD_OBJECT);
                  }
                  // Get field
                  else {
                    if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                      // TODO SPVM_BYTECODE_C_CODE_GET_FIELD_BYTE);
                      
                      
                      
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                      // TODO SPVM_BYTECODE_C_CODE_GET_FIELD_SHORT);
                      
                      
                      
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_INT) {
                      // TODO SPVM_BYTECODE_C_CODE_GET_FIELD_INT);
                      
                      
                      
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                      // TODO SPVM_BYTECODE_C_CODE_GET_FIELD_LONG);
                      
                      
                      
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                      // TODO SPVM_BYTECODE_C_CODE_GET_FIELD_FLOAT);
                      
                      
                      
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                      // TODO SPVM_BYTECODE_C_CODE_GET_FIELD_DOUBLE);
                      
                      
                      
                    }
                    else {
                      // TODO SPVM_BYTECODE_C_CODE_GET_FIELD_OBJECT);
                      
                      
                      
                    }
                  }

                  SPVM_FIELD* field = op_cur->uv.call_field->field;
                  
                  // TODO field->id);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_CALL_SUB: {
                
                // Call subroutine
                // TODO SPVM_BYTECODE_C_CODE_CALL_SUB);
                
                
                

                SPVM_CALL_SUB* call_sub = op_cur->uv.call_sub;
                const char* sub_name = call_sub->resolved_name;
                
                SPVM_OP* op_sub = SPVM_HASH_search(compiler->op_sub_symtable, sub_name, strlen(sub_name));
                SPVM_SUB* sub = op_sub->uv.sub;
                
                int32_t id = sub->id;
                
                // TODO id);
                
                if (compiler->debug) {
                  // TODO SPVM_BYTECODE_C_CODE_CURRENT_LINE);
                  
                  
                  

                  // TODO op_cur->line);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_CROAK: {
                
                // TODO SPVM_BYTECODE_C_CODE_CROAK);
                
                
                
                
                break;
              }
              case SPVM_OP_C_CODE_LAST: {
                // TODO

                break;
              }
              case SPVM_OP_C_CODE_NEXT: {
                int32_t* bytecode_index_ptr = SPVM_DYNAMIC_ARRAY_fetch(goto_loop_start_bytecode_index_stack, goto_loop_start_bytecode_index_stack->length - 1);
                int32_t bytecode_index = *bytecode_index_ptr;
                
                // TODO
                
                break;
              }
              case SPVM_OP_C_CODE_BLOCK: {
                if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_IF_FALSE) {
                  // TODO
                }
                else if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_IF_TRUE) {
                  // TODO
                }
                else if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_LOOP) {
                  // TODO
                }
                else if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_EVAL) {
                  // TODO
                }
                break;
              }
              case SPVM_OP_C_CODE_LOOP: {
                
                // Set last position
                while (goto_last_bytecode_index_stack->length > 0) {
                  // TODO
                }
                
                break;
              }
              case SPVM_OP_C_CODE_EQ: {
                break;
              }
              case SPVM_OP_C_CODE_NE: {
                break;
              }
              case SPVM_OP_C_CODE_GT: {
                break;
              }
              case SPVM_OP_C_CODE_GE: {
                break;
              }
              case SPVM_OP_C_CODE_LT: {
                break;
              }
              case SPVM_OP_C_CODE_LE: {
                break;
              }
              case SPVM_OP_C_CODE_BOOL: {
                break;
              }

              case SPVM_OP_C_CODE_CONDITION: {
                
                break;
              }
              case SPVM_OP_C_CODE_ARRAY_LENGTH : {
                // TODO SPVM_BYTECODE_C_CODE_ARRAY_LENGTH);
                
                
                
                
                break;
              }
              case SPVM_OP_C_CODE_LEFT_SHIFT: {
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  // TODO SPVM_BYTECODE_C_CODE_LEFT_SHIFT_BYTE);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  // TODO SPVM_BYTECODE_C_CODE_LEFT_SHIFT_SHORT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  // TODO SPVM_BYTECODE_C_CODE_LEFT_SHIFT_INT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  // TODO SPVM_BYTECODE_C_CODE_LEFT_SHIFT_LONG);
                  
                  
                  
                }
                
                break;
              }
              case SPVM_OP_C_CODE_RIGHT_SHIFT: {
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  // TODO SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_BYTE);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  // TODO SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_SHORT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  // TODO SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_INT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  // TODO SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_LONG);
                  
                  
                  
                }
                
                break;
              }
              case SPVM_OP_C_CODE_RIGHT_SHIFT_UNSIGNED: {
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  // TODO SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_BYTE);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  // TODO SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_SHORT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  // TODO SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_INT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  // TODO SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_LONG);
                  
                  
                  
                }
                
                break;
              }
              case SPVM_OP_C_CODE_NEW: {
                if (op_cur->first->code == SPVM_OP_C_CODE_CONSTANT) {
                  SPVM_CONSTANT* constant = op_cur->first->uv.constant;
                  
                  // TODO SPVM_BYTECODE_C_CODE_NEW_STRING);
                  
                  
                  
                  
                  // TODO constant->id);
                }
                else if (op_cur->first->code == SPVM_OP_C_CODE_TYPE) {
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur->first);
                  
                  if (SPVM_TYPE_is_array(compiler, type)) {
                    switch (type->code) {
                      case SPVM_TYPE_C_CODE_BYTE_ARRAY:
                        // TODO SPVM_BYTECODE_C_CODE_NEW_BYTE_ARRAY);
                        
                        
                        
                        break;
                      case SPVM_TYPE_C_CODE_SHORT_ARRAY:
                        // TODO SPVM_BYTECODE_C_CODE_NEW_SHORT_ARRAY);
                        
                        
                        
                        break;
                      case SPVM_TYPE_C_CODE_INT_ARRAY:
                        // TODO SPVM_BYTECODE_C_CODE_NEW_INT_ARRAY);
                        
                        
                        
                        break;
                      case SPVM_TYPE_C_CODE_LONG_ARRAY:
                        // TODO SPVM_BYTECODE_C_CODE_NEW_LONG_ARRAY);
                        
                        
                        
                        break;
                      case SPVM_TYPE_C_CODE_FLOAT_ARRAY:
                        // TODO SPVM_BYTECODE_C_CODE_NEW_FLOAT_ARRAY);
                        
                        
                        
                        break;
                      case SPVM_TYPE_C_CODE_DOUBLE_ARRAY:
                        // TODO SPVM_BYTECODE_C_CODE_NEW_DOUBLE_ARRAY);
                        
                        
                        
                        break;
                      default: {
                        // TODO SPVM_BYTECODE_C_CODE_NEW_OBJECT_ARRAY);
                        
                        
                        
                        
                        // TODO type->id);
                      }
                    }
                  }
                  else {
                    // TODO SPVM_BYTECODE_C_CODE_NEW_OBJECT);
                    
                    
                    
                    
                    int32_t type_id = op_cur->first->uv.type->id;
                    assert(type_id);
                    
                    // TODO type_id);
                  }
                }
                else {
                  assert(0);
                }
                
                break;
              }
              
              case SPVM_OP_C_CODE_UNDEF: {
                
                // TODO SPVM_BYTECODE_C_CODE_UNDEF);
                
                
                
                
                break;
              }
              case SPVM_OP_C_CODE_PRE_INC: {
                // TODO
                
                
                break;
              }
              case SPVM_OP_C_CODE_POST_INC: {
                
                // TODO
                
                break;
              }
              case SPVM_OP_C_CODE_PRE_DEC: {
                // TODO
                
                
                break;
              }
              case SPVM_OP_C_CODE_POST_DEC: {
                
                // TODO
                
                break;
              }
              case SPVM_OP_C_CODE_BIT_XOR: {
                
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  // TODO SPVM_BYTECODE_C_CODE_BIT_XOR_BYTE);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  // TODO SPVM_BYTECODE_C_CODE_BIT_XOR_SHORT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  // TODO SPVM_BYTECODE_C_CODE_BIT_XOR_INT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  // TODO SPVM_BYTECODE_C_CODE_BIT_XOR_LONG);
                  
                  
                  
                }
                
                break;
              }
              case SPVM_OP_C_CODE_BIT_OR: {
                
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  // TODO SPVM_BYTECODE_C_CODE_BIT_OR_BYTE);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  // TODO SPVM_BYTECODE_C_CODE_BIT_OR_SHORT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  // TODO SPVM_BYTECODE_C_CODE_BIT_OR_INT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  // TODO SPVM_BYTECODE_C_CODE_BIT_OR_LONG);
                  
                  
                  
                }
                              
                break;
              }
              case SPVM_OP_C_CODE_BIT_AND: {
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  // TODO SPVM_BYTECODE_C_CODE_BIT_AND_BYTE);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  // TODO SPVM_BYTECODE_C_CODE_BIT_AND_SHORT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  // TODO SPVM_BYTECODE_C_CODE_BIT_AND_INT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  // TODO SPVM_BYTECODE_C_CODE_BIT_AND_LONG);
                  
                  
                  
                }
                
                break;
              }
              case SPVM_OP_C_CODE_ARRAY_ELEM: {
                
                if (op_cur->is_assign_left) {
                  break;
                }
                
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                
                assert(last_type->code == SPVM_TYPE_C_CODE_INT);
                
                if (type->code == SPVM_TYPE_C_CODE_BYTE)
                {
                  // TODO SPVM_BYTECODE_C_CODE_ARRAY_LOAD_BYTE);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  // TODO SPVM_BYTECODE_C_CODE_ARRAY_LOAD_SHORT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  // TODO SPVM_BYTECODE_C_CODE_ARRAY_LOAD_INT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  // TODO SPVM_BYTECODE_C_CODE_ARRAY_LOAD_LONG);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  // TODO SPVM_BYTECODE_C_CODE_ARRAY_LOAD_FLOAT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  // TODO SPVM_BYTECODE_C_CODE_ARRAY_LOAD_DOUBLE);
                  
                  
                  
                }
                else {
                  // TODO SPVM_BYTECODE_C_CODE_ARRAY_LOAD_OBJECT);
                  
                  
                  
                }

                
                break;
              }
              case SPVM_OP_C_CODE_ASSIGN: {
                
                if (op_cur->first->code == SPVM_OP_C_CODE_VAR) {
                  SPVM_OP* op_var = op_cur->first;
                  int32_t my_var_index = op_var->uv.var->op_my_var->uv.my_var->index;
                  
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_var);
                  
                  if (SPVM_TYPE_is_numeric(compiler, type)) {
                    // TODO SPVM_BYTECODE_C_CODE_STORE);
                    
                    
                    
                  }
                  else {
                    // TODO SPVM_BYTECODE_C_CODE_STORE_OBJECT);
                    
                    
                    
                  }
                  
                  // TODO my_var_index);
                }
                else if (op_cur->first->code == SPVM_OP_C_CODE_PACKAGE_VAR) {
                  SPVM_OP* op_package_var = op_cur->first;
                  
                  SPVM_PACKAGE_VAR* package_var = op_package_var->uv.package_var;

                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_package_var);

                  if (SPVM_TYPE_is_numeric(compiler, type)) {
                    // TODO SPVM_BYTECODE_C_CODE_STORE_PACKAGE_VAR);
                    
                    
                    
                  }
                  else {
                    // TODO SPVM_BYTECODE_C_CODE_STORE_PACKAGE_VAR_OBJECT);
                    
                    
                    
                  }
                                    
                  int32_t package_var_id = package_var->op_our->uv.our->id;

                  // TODO package_var_id);
                }
                else if (op_cur->first->code == SPVM_OP_C_CODE_ARRAY_ELEM) {
                  
                  SPVM_OP* op_array_elem = op_cur->first;
                  SPVM_OP* op_term_index = op_array_elem->last;
                  
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_array_elem);
                  SPVM_TYPE* index_type = SPVM_OP_get_type(compiler, op_term_index);
                  
                  assert(index_type->code == SPVM_TYPE_C_CODE_INT);
                  
                  if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                    // TODO SPVM_BYTECODE_C_CODE_ARRAY_STORE_BYTE);
                    
                    
                    
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                    // TODO SPVM_BYTECODE_C_CODE_ARRAY_STORE_SHORT);
                    
                    
                    
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_INT) {
                    // TODO SPVM_BYTECODE_C_CODE_ARRAY_STORE_INT);
                    
                    
                    
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                    // TODO SPVM_BYTECODE_C_CODE_ARRAY_STORE_LONG);
                    
                    
                    
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    // TODO SPVM_BYTECODE_C_CODE_ARRAY_STORE_FLOAT);
                    
                    
                    
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    // TODO SPVM_BYTECODE_C_CODE_ARRAY_STORE_DOUBLE);
                    
                    
                    
                  }
                  else {
                    // TODO SPVM_BYTECODE_C_CODE_ARRAY_STORE_OBJECT);
                    
                    
                    
                  }
                }
                else if (op_cur->first->code == SPVM_OP_C_CODE_CALL_FIELD) {
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur->first);
                  
                  if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                    // TODO SPVM_BYTECODE_C_CODE_SET_FIELD_BYTE);
                    
                    
                    
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                    // TODO SPVM_BYTECODE_C_CODE_SET_FIELD_SHORT);
                    
                    
                    
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_INT) {
                    // TODO SPVM_BYTECODE_C_CODE_SET_FIELD_INT);
                    
                    
                    
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                    // TODO SPVM_BYTECODE_C_CODE_SET_FIELD_LONG);
                    
                    
                    
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    // TODO SPVM_BYTECODE_C_CODE_SET_FIELD_FLOAT);
                    
                    
                    
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    // TODO SPVM_BYTECODE_C_CODE_SET_FIELD_DOUBLE);
                    
                    
                    
                  }
                  else {
                    // TODO SPVM_BYTECODE_C_CODE_SET_FIELD_OBJECT);
                    
                    
                    
                  }
                  
                  // Call field
                  SPVM_CALL_FIELD* call_field = op_cur->first->uv.call_field;
                  SPVM_FIELD* field = call_field->field;

                  // TODO field->id);
                }
                else if (op_cur->first->code == SPVM_OP_C_CODE_EXCEPTION_VAR) {
                  // TODO SPVM_BYTECODE_C_CODE_STORE_EXCEPTION);
                  
                  
                  
                }
                else {
                  assert(0);
                }
                
                break;
              }
              
              case SPVM_OP_C_CODE_RETURN: {
                SPVM_OP* op_return_type = sub->op_return_type;
                
                SPVM_TYPE* return_type = op_return_type->uv.type;
                if (return_type->code == SPVM_TYPE_C_CODE_VOID) {
                  // TODO SPVM_BYTECODE_C_CODE_RETURN_VOID);
                  
                  
                  
                }
                else if (return_type->code == SPVM_TYPE_C_CODE_BYTE) {
                  // TODO SPVM_BYTECODE_C_CODE_RETURN_BYTE);
                  
                  
                  
                }
                else if (return_type->code == SPVM_TYPE_C_CODE_SHORT) {
                  // TODO SPVM_BYTECODE_C_CODE_RETURN_SHORT);
                  
                  
                  
                }
                else if (return_type->code == SPVM_TYPE_C_CODE_INT) {
                  // TODO SPVM_BYTECODE_C_CODE_RETURN_INT);
                  
                  
                  
                }
                else if (return_type->code == SPVM_TYPE_C_CODE_LONG) {
                  // TODO SPVM_BYTECODE_C_CODE_RETURN_LONG);
                  
                  
                  
                }
                else if (return_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  // TODO SPVM_BYTECODE_C_CODE_RETURN_FLOAT);
                  
                  
                  
                }
                else if (return_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  // TODO SPVM_BYTECODE_C_CODE_RETURN_DOUBLE);
                  
                  
                  
                }
                else {
                  // TODO SPVM_BYTECODE_C_CODE_RETURN_OBJECT);
                  
                  
                  
                }
                
                break;
              }
              case SPVM_OP_C_CODE_NEGATE: {
                
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  // TODO SPVM_BYTECODE_C_CODE_NEGATE_BYTE);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  // TODO SPVM_BYTECODE_C_CODE_NEGATE_SHORT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  // TODO SPVM_BYTECODE_C_CODE_NEGATE_INT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  // TODO SPVM_BYTECODE_C_CODE_NEGATE_LONG);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  // TODO SPVM_BYTECODE_C_CODE_NEGATE_FLOAT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  // TODO SPVM_BYTECODE_C_CODE_NEGATE_DOUBLE);
                  
                  
                  
                }
                
                break;
              }
              case SPVM_OP_C_CODE_CONVERT: {
                
                SPVM_OP* op_src_term = op_cur->first;
                SPVM_OP* op_dist_type = op_cur->last;
                
                SPVM_TYPE* src_type = SPVM_OP_get_type(compiler, op_src_term);
                SPVM_TYPE* dist_type = SPVM_OP_get_type(compiler, op_dist_type);
                
                if (src_type->code == SPVM_TYPE_C_CODE_BYTE) {
                  if (dist_type->code == SPVM_TYPE_C_CODE_BYTE) {
                    // None
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_SHORT) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_SHORT);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_INT) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_INT);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_LONG) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_LONG);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_FLOAT);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_DOUBLE);
                    
                    
                    
                  }
                  else {
                    assert(0);
                  }
                }
                else if (src_type->code == SPVM_TYPE_C_CODE_SHORT) {
                  if (dist_type->code == SPVM_TYPE_C_CODE_BYTE) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_BYTE);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_SHORT) {
                    // None
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_INT) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_INT);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_LONG) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_LONG);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_FLOAT);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_DOUBLE);
                    
                    
                    
                  }
                  else {
                    assert(0);
                  }
                }
                else if (src_type->code == SPVM_TYPE_C_CODE_INT) {
                  if (dist_type->code == SPVM_TYPE_C_CODE_BYTE) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_BYTE);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_SHORT) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_SHORT);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_INT) {
                    // None
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_LONG) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_LONG);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_FLOAT);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_DOUBLE);
                    
                    
                    
                  }
                  else {
                    assert(0);
                  }
                }
                else if (src_type->code == SPVM_TYPE_C_CODE_LONG) {
                  if (dist_type->code == SPVM_TYPE_C_CODE_BYTE) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_BYTE);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_SHORT) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_SHORT);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_INT) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_INT);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_LONG) {
                    // None
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_FLOAT);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_DOUBLE);
                    
                    
                    
                  }
                  else {
                    assert(0);
                  }
                }
                else if (src_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  if (dist_type->code == SPVM_TYPE_C_CODE_BYTE) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_BYTE);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_SHORT) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_SHORT);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_INT) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_INT);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_LONG) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_LONG);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    // None
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_DOUBLE);
                    
                    
                    
                  }
                  else {
                    assert(0);
                  }
                }
                else if (src_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  if (dist_type->code == SPVM_TYPE_C_CODE_BYTE) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_BYTE);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_SHORT) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_SHORT);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_INT) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_INT);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_LONG) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_LONG);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    // TODO SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_FLOAT);
                    
                    
                    
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    // None
                  }
                  else {
                    assert(0);
                  }
                }
                else {
                    assert(0);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_ADD: {
                
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                assert(type);
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  // TODO SPVM_BYTECODE_C_CODE_ADD_BYTE);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  // TODO SPVM_BYTECODE_C_CODE_ADD_SHORT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  // TODO SPVM_BYTECODE_C_CODE_ADD_INT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  // TODO SPVM_BYTECODE_C_CODE_ADD_LONG);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  // TODO SPVM_BYTECODE_C_CODE_ADD_FLOAT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  // TODO SPVM_BYTECODE_C_CODE_ADD_DOUBLE);
                  
                  
                  
                }
                
                break;
              }
              case SPVM_OP_C_CODE_CONCAT_STRING: {
                
                SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                assert(first_type->code == SPVM_TYPE_C_CODE_STRING);
                
                SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                if (last_type->code == SPVM_TYPE_C_CODE_STRING) {
                  // TODO SPVM_BYTECODE_C_CODE_CONCAT_STRING_STRING);
                  
                  
                  
                }
                else if (last_type->code == SPVM_TYPE_C_CODE_BYTE) {
                  // TODO SPVM_BYTECODE_C_CODE_CONCAT_STRING_BYTE);
                  
                  
                  
                }
                else if (last_type->code == SPVM_TYPE_C_CODE_SHORT) {
                  // TODO SPVM_BYTECODE_C_CODE_CONCAT_STRING_SHORT);
                  
                  
                  
                }
                else if (last_type->code == SPVM_TYPE_C_CODE_INT) {
                  // TODO SPVM_BYTECODE_C_CODE_CONCAT_STRING_INT);
                  
                  
                  
                }
                else if (last_type->code == SPVM_TYPE_C_CODE_LONG) {
                  // TODO SPVM_BYTECODE_C_CODE_CONCAT_STRING_LONG);
                  
                  
                  
                }
                else if (last_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  // TODO SPVM_BYTECODE_C_CODE_CONCAT_STRING_FLOAT);
                  
                  
                  
                }
                else if (last_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  // TODO SPVM_BYTECODE_C_CODE_CONCAT_STRING_DOUBLE);
                  
                  
                  
                }
                
                break;
              }
              case SPVM_OP_C_CODE_SUBTRACT: {
                
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  // TODO SPVM_BYTECODE_C_CODE_SUBTRACT_BYTE);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  // TODO SPVM_BYTECODE_C_CODE_SUBTRACT_SHORT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  // TODO SPVM_BYTECODE_C_CODE_SUBTRACT_INT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  // TODO SPVM_BYTECODE_C_CODE_SUBTRACT_LONG);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  // TODO SPVM_BYTECODE_C_CODE_SUBTRACT_FLOAT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  // TODO SPVM_BYTECODE_C_CODE_SUBTRACT_DOUBLE);
                  
                  
                  
                }
                
                break;
              }
              case SPVM_OP_C_CODE_MULTIPLY: {
                
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  // TODO SPVM_BYTECODE_C_CODE_MULTIPLY_BYTE);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  // TODO SPVM_BYTECODE_C_CODE_MULTIPLY_SHORT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  // TODO SPVM_BYTECODE_C_CODE_MULTIPLY_INT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  // TODO SPVM_BYTECODE_C_CODE_MULTIPLY_LONG);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  // TODO SPVM_BYTECODE_C_CODE_MULTIPLY_FLOAT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  // TODO SPVM_BYTECODE_C_CODE_MULTIPLY_DOUBLE);
                  
                  
                  
                }
                
                break;
              }
              case SPVM_OP_C_CODE_DIVIDE: {
                
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  // TODO SPVM_BYTECODE_C_CODE_DIVIDE_BYTE);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  // TODO SPVM_BYTECODE_C_CODE_DIVIDE_SHORT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  // TODO SPVM_BYTECODE_C_CODE_DIVIDE_INT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  // TODO SPVM_BYTECODE_C_CODE_DIVIDE_LONG);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  // TODO SPVM_BYTECODE_C_CODE_DIVIDE_FLOAT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  // TODO SPVM_BYTECODE_C_CODE_DIVIDE_DOUBLE);
                  
                  
                  
                }
                
                break;
              }
              case SPVM_OP_C_CODE_REMAINDER: {
                
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  // TODO SPVM_BYTECODE_C_CODE_REMAINDER_BYTE);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  // TODO SPVM_BYTECODE_C_CODE_REMAINDER_SHORT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  // TODO SPVM_BYTECODE_C_CODE_REMAINDER_INT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  // TODO SPVM_BYTECODE_C_CODE_REMAINDER_LONG);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  // TODO SPVM_BYTECODE_C_CODE_REMAINDER_FLOAT);
                  
                  
                  
                }
                else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  // TODO SPVM_BYTECODE_C_CODE_REMAINDER_DOUBLE);
                  
                  
                  
                }
                
                break;
              }
              case SPVM_OP_C_CODE_VAR: {
                if (op_cur->is_assign_left) {
                  break;
                }
                
                // TODO
                
                break;
              }
              case SPVM_OP_C_CODE_PACKAGE_VAR: {
                if (op_cur->is_assign_left) {
                  break;
                }
                
                SPVM_OUR* our = op_cur->uv.package_var->op_our->uv.our;
                
                int32_t package_var_id = our->id;

                // TODO SPVM_BYTECODE_C_CODE_LOAD_PACKAGE_VAR);
                
                
                

                // TODO package_var_id);
                
                break;
              }
              case SPVM_OP_C_CODE_EXCEPTION_VAR: {
                if (op_cur->is_assign_left) {
                  break;
                }
                
                // TODO SPVM_BYTECODE_C_CODE_LOAD_EXCEPTION);
                
                
                
                
                break;
              }
              case SPVM_OP_C_CODE_CONSTANT: {
                SPVM_CONSTANT* constant = op_cur->uv.constant;
                
                if (op_cur->flag == SPVM_OP_C_FLAG_CONSTANT_CASE) {
                  break;
                }
                
                _Bool bytecode_set = 0;
                
                if (constant->type->code == SPVM_TYPE_C_CODE_BYTE) {
                  // Nothing
                }
                else if (constant->type->code == SPVM_TYPE_C_CODE_SHORT) {
                  // Nothing
                }
                else if (constant->type->code == SPVM_TYPE_C_CODE_INT) {
                  // Nothing
                }
                else if (constant->type->code == SPVM_TYPE_C_CODE_LONG) {
                  // Nothing
                }
                else if (constant->type->code == SPVM_TYPE_C_CODE_FLOAT) {
                }
                else if (constant->type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                }
                else if (constant->type->code == SPVM_TYPE_C_CODE_STRING) {
                  break;
                }
                else {
                  assert(0);
                }
                
                if (!bytecode_set) {
                  if (constant->type->code == SPVM_TYPE_C_CODE_BYTE
                    || constant->type->code == SPVM_TYPE_C_CODE_SHORT
                    || constant->type->code == SPVM_TYPE_C_CODE_INT
                    || constant->type->code == SPVM_TYPE_C_CODE_FLOAT)
                  {
                    // TODO SPVM_BYTECODE_C_CODE_LOAD_CONSTANT);
                    
                    
                    
                  }
                  else if (constant->type->code == SPVM_TYPE_C_CODE_LONG || constant->type->code == SPVM_TYPE_C_CODE_DOUBLE) {

                  }
                  else {
                    assert(0);
                  }
                  
                  assert(constant->id != -1);
                  
                }
                
                break;
              }
            }
            
            // [END]Postorder traversal position
            
            if (op_cur == op_base) {
              finish = 1;
              break;
            }
            
            // Next sibling
            if (op_cur->moresib) {
              op_cur = SPVM_OP_sibling(compiler, op_cur);
              break;
            }
            // Next is parent
            else {
              op_cur = op_cur->sibparent;
            }
          }
          if (finish) {
            break;
          }
        }
      }
    }
  }
}
