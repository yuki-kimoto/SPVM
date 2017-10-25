#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#include "spvm_compiler.h"
#include "spvm_bytecode_builder.h"
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


void SPVM_BYTECODE_BUILDER_push_inc_bytecode(SPVM_COMPILER* compiler, SPVM_BYTECODE_ARRAY* bytecode_array, SPVM_OP* op_inc, int32_t value) {
  
  SPVM_VAR* var = op_inc->first->uv.var;
  SPVM_MY_VAR* my_var = var->op_my_var->uv.my_var;
  
  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_inc);
  if (type->code == SPVM_TYPE_C_CODE_BYTE) {
    if (my_var->index > 0xFF || (value < -128 || value > 127)) {
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_WIDE);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_INC_BYTE);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (my_var->index >> 8) & 0xFF);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, my_var->index & 0xFF);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (value >> 8) & 0xFF);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, value & 0xFF);
    }
    else {
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_INC_BYTE);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, my_var->index);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, value);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
    }
  }
  else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
    if (my_var->index > 0xFF || (value < -128 || value > 127)) {
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_WIDE);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_INC_SHORT);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (my_var->index >> 8) & 0xFF);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, my_var->index & 0xFF);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (value >> 8) & 0xFF);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, value & 0xFF);
    }
    else {
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_INC_SHORT);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, my_var->index);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, value);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
    }
  }
  else if (type->code == SPVM_TYPE_C_CODE_INT) {
    if (my_var->index > 0xFF || (value < -128 || value > 127)) {
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_WIDE);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_INC_INT);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (my_var->index >> 8) & 0xFF);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, my_var->index & 0xFF);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (value >> 8) & 0xFF);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, value & 0xFF);
    }
    else {
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_INC_INT);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, my_var->index);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, value);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
    }
  }
  else if (type->code == SPVM_TYPE_C_CODE_LONG) {
    if (my_var->index > 0xFF || (value < -128 || value > 127)) {
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_WIDE);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_INC_LONG);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (my_var->index >> 8) & 0xFF);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, my_var->index & 0xFF);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (value >> 8) & 0xFF);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, value & 0xFF);
    }
    else {
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_INC_LONG);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, my_var->index);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, value);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
    }
  }
}

void SPVM_BYTECODE_BUILDER_push_load_bytecode(SPVM_COMPILER* compiler, SPVM_BYTECODE_ARRAY* bytecode_array, SPVM_OP* op_var) {
  
  (void)compiler;
  
  SPVM_VAR* var = op_var->uv.var;
  
  int32_t my_var_index = var->op_my_var->uv.my_var->index;

  if (my_var_index > 0xFF) {
    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_WIDE);
  }
  
  _Bool has_operand = 0;
  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_LOAD);
  has_operand = 1;
  
  if (has_operand) {
    if (my_var_index > 0xFF) {
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (my_var_index >> 8) & 0xFF);
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, my_var_index);
    }
    else {
      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, my_var_index);
    }
  }
}

void SPVM_BYTECODE_BUILDER_build_bytecode_array(SPVM_COMPILER* compiler) {
  
  // Bytecode
  SPVM_BYTECODE_ARRAY* bytecode_array = compiler->bytecode_array;
  
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
      
      sub->bytecode_base = bytecode_array->length;
      
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
              SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_GOTO);
              
              int32_t* bytecode_index_ptr = SPVM_COMPILER_ALLOCATOR_alloc_int(compiler, compiler->allocator);
              *bytecode_index_ptr = bytecode_array->length - 1;
              
              SPVM_DYNAMIC_ARRAY_push(goto_loop_start_bytecode_index_stack, bytecode_index_ptr);
              
              SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, 0);
              SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, 0);
            }
            else if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_EVAL) {
              SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_PUSH_CATCH_EXCEPTION);
              
              int32_t* bytecode_index_ptr = SPVM_COMPILER_ALLOCATOR_alloc_int(compiler, compiler->allocator);
              *bytecode_index_ptr = bytecode_array->length - 1;
              
              SPVM_DYNAMIC_ARRAY_push(push_catch_exception_bytecode_index_stack, bytecode_index_ptr);
              
              SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, 0);
              SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, 0);
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
                case SPVM_OP_C_CODE_ASSIGN_PROCESS:
                case SPVM_OP_C_CODE_TYPE:
                case SPVM_OP_C_CODE_POP:
                  is_operation = 0;
                  break;
                default:
                  is_operation = 1;
              }
              
              if (is_operation) {
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CURRENT_LINE);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (op_cur->line >> 24) & 0xFF);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (op_cur->line >> 16) & 0xFF);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (op_cur->line >> 8) & 0xFF);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, op_cur->line & 0xFF);
              }
            }
            
            // [START]Postorder traversal position
            switch (op_cur->code) {
              case SPVM_OP_C_CODE_SWITCH_CONDITION: {
                
                SPVM_SWITCH_INFO* switch_info = op_cur->uv.switch_info;
                
                // tableswitch
                if (switch_info->code == SPVM_SWITCH_INFO_C_CODE_TABLE_SWITCH) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_TABLE_SWITCH);
                  
                  // Switch bytecode index
                  int32_t switch_bytecode_index = bytecode_array->length - 1;
                  
                  // Push switch information stack
                  switch_info->bytecode_index = switch_bytecode_index;
                  SPVM_DYNAMIC_ARRAY_push(switch_info_stack, switch_info);
                  
                  // Padding
                  int32_t padding = ((int32_t)sizeof(int32_t) - 1) - (switch_bytecode_index % (int32_t)sizeof(int32_t));
                  
                  {
                    int32_t i;
                    for (i = 0; i < padding; i++) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, 0);
                    }
                  }
                  
                  // Default
                  {
                    int32_t i;
                    for (i = 0; i < (int32_t)sizeof(int32_t); i++) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, 0);
                    }
                  }
                  
                  // Low
                  {
                    int32_t i;
                    for (i = 0; i < (int32_t)sizeof(int32_t); i++) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, 0);
                    }
                  }
                  int32_t min = (int32_t)switch_info->min;
                  *(int32_t*)&bytecode_array->values[bytecode_array->length - sizeof(int32_t)] = (int32_t)min;
                  
                  // High
                  {
                    int32_t i;
                    for (i = 0; i < (int32_t)sizeof(int32_t); i++) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, 0);
                    }
                  }
                  int32_t max = (int32_t)switch_info->max;
                  *(int32_t*)&bytecode_array->values[bytecode_array->length - sizeof(int32_t)] = (int32_t)switch_info->max;
                  
                  // Offsets
                  {
                    int32_t i;
                    for (i = 0; i < (max - min + 1) * (int32_t)sizeof(int32_t); i++) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, 0);
                    }
                  }
                }
                // lookupswitch
                else if (switch_info->code == SPVM_SWITCH_INFO_C_CODE_LOOKUP_SWITCH) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_LOOKUP_SWITCH);
                  
                  // Switch bytecode index
                  int32_t switch_bytecode_index = bytecode_array->length - 1;
                  
                  // Push switch information stack
                  switch_info->bytecode_index = switch_bytecode_index;
                  SPVM_DYNAMIC_ARRAY_push(switch_info_stack, switch_info);
                  
                  // Padding
                  int32_t padding = (sizeof(int32_t) - 1) - (switch_bytecode_index % sizeof(int32_t));
                  
                  {
                    int32_t i;
                    for (i = 0; i < padding; i++) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, 0);
                    }
                  }
                  
                  // Default
                  {
                    int32_t i;
                    for (i = 0; i < (int32_t)sizeof(int32_t); i++) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, 0);
                    }
                  }
                  
                  // Case count
                  {
                    int32_t i;
                    for (i = 0; i < (int32_t)sizeof(int32_t); i++) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, 0);
                    }
                  }
                  int32_t const length = switch_info->op_cases->length;
                  *(int32_t*)&bytecode_array->values[bytecode_array->length - (int32_t)sizeof(int32_t)] = length;
                  
                  int32_t size_of_match_offset_pairs = length * (int32_t)sizeof(int32_t) * 2;
                  {
                    int32_t i;
                    for (i = 0; i < size_of_match_offset_pairs; i++) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, 0);
                    }
                  }
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
                  int32_t padding = (sizeof(int32_t) - 1) - (switch_bytecode_index % sizeof(int32_t));
                  
                  // Default offset
                  int32_t default_offset;
                  if (!default_bytecode_index) {
                    default_offset = bytecode_array->length - switch_bytecode_index;
                  }
                  else {
                    default_offset = default_bytecode_index - switch_bytecode_index;
                  }
                  *(int32_t*)&bytecode_array->values[switch_bytecode_index + padding + 1] = default_offset;
                  
                  // min
                  int32_t min = *(int32_t*)&bytecode_array->values[switch_bytecode_index + padding + sizeof(int32_t) + 1];
                  
                  // max
                  int32_t max = *(int32_t*)&bytecode_array->values[switch_bytecode_index + padding + sizeof(int32_t) * 2 + 1];
                  
                  int32_t length = (int32_t)(max - min + 1);
                  
                  int32_t case_pos = 0;
                  {
                    int32_t i;
                    for (i = 0; i < length; i++) {
                      SPVM_OP* op_case = SPVM_DYNAMIC_ARRAY_fetch(switch_info->op_cases, case_pos);
                      SPVM_OP* op_constant = op_case->first;
                      if (op_constant->uv.constant->value.int_value - min == i) {
                        // Case
                        int32_t* case_bytecode_index_ptr = SPVM_DYNAMIC_ARRAY_fetch(case_bytecode_indexes, case_pos);
                        int32_t case_bytecode_index = *case_bytecode_index_ptr;
                        int32_t case_offset = case_bytecode_index - switch_bytecode_index;
                        
                        *(int32_t*)&bytecode_array->values[switch_bytecode_index + padding + sizeof(int32_t) * 3 + 1 + (sizeof(int32_t) * i)] = case_offset;
                        
                        case_pos++;
                      }
                      else {
                        // Default
                        *(int32_t*)&bytecode_array->values[switch_bytecode_index + padding + sizeof(int32_t) * 3 + 1 + (sizeof(int32_t) * i)] = default_offset;
                      }
                    }
                  }
                }
                // lookupswitch
                else if (switch_info->code == SPVM_SWITCH_INFO_C_CODE_LOOKUP_SWITCH) {
                  int32_t padding = (sizeof(int32_t) - 1) - (switch_bytecode_index % sizeof(int32_t));
                  
                  // Default offset
                  int32_t default_offset;
                  if (!default_bytecode_index) {
                    default_offset = bytecode_array->length - switch_bytecode_index;
                  }
                  else {
                    default_offset = default_bytecode_index - switch_bytecode_index;
                  }
                  *(int32_t*)&bytecode_array->values[switch_bytecode_index + padding + 1] = default_offset;
                  
                  int32_t const length = (int32_t) switch_info->op_cases->length;
                  
                  SPVM_DYNAMIC_ARRAY* ordered_op_cases = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
                  {
                    int32_t i;
                    for (i = 0; i < length; i++) {
                      SPVM_OP* op_case = SPVM_DYNAMIC_ARRAY_fetch(switch_info->op_cases, i);
                      SPVM_DYNAMIC_ARRAY_push(ordered_op_cases, op_case);
                    }
                  }
                  SPVM_DYNAMIC_ARRAY* ordered_case_bytecode_indexes = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
                  {
                    int32_t i;
                    for (i = 0; i < length; i++) {
                      int32_t* case_bytecode_index_ptr = SPVM_DYNAMIC_ARRAY_fetch(case_bytecode_indexes, i);
                      SPVM_DYNAMIC_ARRAY_push(ordered_case_bytecode_indexes, case_bytecode_index_ptr);
                    }
                  }
                  
                  // sort by asc order
                  {
                    int32_t i;
                    for (i = 0; i < length; i++) {
                      int32_t j;
                      {
                        for (j = i + 1; j < length; j++) {
                          SPVM_OP* op_case_i = SPVM_DYNAMIC_ARRAY_fetch(ordered_op_cases, i);
                          SPVM_OP* op_case_j = SPVM_DYNAMIC_ARRAY_fetch(ordered_op_cases, j);
                          int32_t match_i = op_case_i->first->uv.constant->value.int_value;
                          int32_t match_j = op_case_j->first->uv.constant->value.int_value;
                          
                          int32_t* case_bytecode_index_i = SPVM_DYNAMIC_ARRAY_fetch(ordered_case_bytecode_indexes, i);
                          int32_t* case_bytecode_index_j = SPVM_DYNAMIC_ARRAY_fetch(ordered_case_bytecode_indexes, j);
                          
                          if (match_i > match_j) {
                            SPVM_DYNAMIC_ARRAY_store(ordered_op_cases, i, op_case_j);
                            SPVM_DYNAMIC_ARRAY_store(ordered_op_cases, j, op_case_i);
                            
                            SPVM_DYNAMIC_ARRAY_store(ordered_case_bytecode_indexes, i, case_bytecode_index_j);
                            SPVM_DYNAMIC_ARRAY_store(ordered_case_bytecode_indexes, j, case_bytecode_index_i);
                          }
                        }
                      }
                    }
                  }
                  
                  {
                    int32_t i;
                    for (i = 0; i < length; i++) {
                      SPVM_OP* op_case = SPVM_DYNAMIC_ARRAY_fetch(ordered_op_cases, i);
                      SPVM_OP* op_constant = op_case->first;
                      int32_t match = op_constant->uv.constant->value.int_value;

                      int32_t* case_bytecode_index_ptr = SPVM_DYNAMIC_ARRAY_fetch(ordered_case_bytecode_indexes, i);
                      int32_t case_bytecode_index = *case_bytecode_index_ptr;
                      int32_t case_offset = case_bytecode_index - switch_bytecode_index;
                      
                      // Match
                      *(int32_t*)&bytecode_array->values[switch_bytecode_index + padding + sizeof(int32_t) * 2 + 1 + (sizeof(int32_t) * 2 * i)] = match;

                      // Offset
                      *(int32_t*)&bytecode_array->values[switch_bytecode_index + padding + sizeof(int32_t) * 3 + 1 + (sizeof(int32_t) * 2 * i)] = case_offset;
                    }
                  }
                }
                
                // Set last position
                while (goto_last_bytecode_index_stack->length > 0) {
                  
                  int32_t* goto_last_bytecode_index_ptr = SPVM_DYNAMIC_ARRAY_pop(goto_last_bytecode_index_stack);
                  int32_t goto_last_bytecode_index = *goto_last_bytecode_index_ptr;
                  
                  // Last offset
                  int32_t goto_last_offset = bytecode_array->length - goto_last_bytecode_index;
                  
                  bytecode_array->values[goto_last_bytecode_index + 1] = (goto_last_offset >> 8) & 0xFF;
                  bytecode_array->values[goto_last_bytecode_index + 2] = goto_last_offset & 0xFF;
                }
                
                break;
              }
              case SPVM_OP_C_CODE_CASE: {
                if (switch_info_stack->length > 0) {
                  SPVM_SWITCH_INFO* switch_info = SPVM_DYNAMIC_ARRAY_fetch(switch_info_stack, switch_info_stack->length - 1);
                  int32_t* bytecode_index_ptr = SPVM_COMPILER_ALLOCATOR_alloc_int(compiler, compiler->allocator);
                  *bytecode_index_ptr = bytecode_array->length;
                  
                  SPVM_DYNAMIC_ARRAY_push(switch_info->case_bytecode_indexes, bytecode_index_ptr);
                }
                break;
              }
              case SPVM_OP_C_CODE_DEFAULT: {
                if (switch_info_stack->length > 0) {
                  SPVM_SWITCH_INFO* switch_info = SPVM_DYNAMIC_ARRAY_fetch(switch_info_stack, switch_info_stack->length - 1);
                  switch_info->default_bytecode_index = bytecode_array->length;
                }
                break;
              }
              case SPVM_OP_C_CODE_CALL_FIELD: {
                
                if (!op_cur->lvalue) {
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                  
                  // Weaken field
                  if (op_cur->flag &= SPVM_OP_C_FLAG_CALL_FIELD_WEAKEN) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_WEAKEN_FIELD_OBJECT);
                  }
                  // Get field
                  else {
                    if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_GET_FIELD_BYTE);
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_GET_FIELD_SHORT);
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_INT) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_GET_FIELD_INT);
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_GET_FIELD_LONG);
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_GET_FIELD_FLOAT);
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_GET_FIELD_DOUBLE);
                    }
                    else {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_GET_FIELD_OBJECT);
                    }
                  }
                  
                  SPVM_FIELD* field = op_cur->uv.call_field->field;
                  
                  SPVM_CONSTANT_POOL_FIELD constant_pool_field;
                  memcpy(&constant_pool_field, &compiler->constant_pool->values[field->id], sizeof(SPVM_CONSTANT_POOL_FIELD));
                  
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, ((constant_pool_field.index) >> 8) & 0xFF);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (constant_pool_field.index) & 0xFF);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_CALL_SUB: {
                
                // Call subroutine
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CALL_SUB);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);

                SPVM_CALL_SUB* call_sub = op_cur->uv.call_sub;
                const char* sub_name = call_sub->resolved_name;
                
                SPVM_OP* op_sub = SPVM_HASH_search(compiler->op_sub_symtable, sub_name, strlen(sub_name));
                SPVM_SUB* sub = op_sub->uv.sub;
                
                int32_t id = sub->id;
                
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (id >> 24) & 0xFF);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (id >> 16) & 0xFF);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (id >> 8) & 0xFF);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, id & 0xFF);
                
                if (compiler->debug) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CURRENT_LINE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (op_cur->line >> 24) & 0xFF);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (op_cur->line >> 16) & 0xFF);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (op_cur->line >> 8) & 0xFF);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, op_cur->line & 0xFF);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_CROAK: {
                
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CROAK);
                
                break;
              }
              case SPVM_OP_C_CODE_LAST: {
                // Add goto
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_GOTO);
                
                int32_t* bytecode_index_ptr = SPVM_COMPILER_ALLOCATOR_alloc_int(compiler, compiler->allocator);
                *bytecode_index_ptr = bytecode_array->length - 1;
                
                SPVM_DYNAMIC_ARRAY_push(goto_last_bytecode_index_stack, bytecode_index_ptr);
                
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, 0);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, 0);
                break;
              }
              case SPVM_OP_C_CODE_NEXT: {
                int32_t* bytecode_index_ptr = SPVM_DYNAMIC_ARRAY_fetch(goto_loop_start_bytecode_index_stack, goto_loop_start_bytecode_index_stack->length - 1);
                int32_t bytecode_index = *bytecode_index_ptr;
                
                // Add "goto"
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_GOTO);
                
                // Jump offset
                int32_t jump_offset = bytecode_index - (bytecode_array->length - 1) + 3;
                
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (jump_offset >> 8) & 0xFF);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, jump_offset & 0xFF);
                
                break;
              }
              case SPVM_OP_C_CODE_BLOCK: {
                if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_IF_FALSE) {
                  
                  {
                    // Prepare to jump to end of true block
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_GOTO);
                    
                    int32_t* bytecode_index_ptr = SPVM_COMPILER_ALLOCATOR_alloc_int(compiler, compiler->allocator);
                    *bytecode_index_ptr = bytecode_array->length - 1;
                    SPVM_DYNAMIC_ARRAY_push(goto_if_block_end_bytecode_index_stack, bytecode_index_ptr);
                    
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, 0);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, 0);
                  }

                  assert(if_bytecode_index_stack->length > 0);

                  // Set if jump bytecode index
                  int32_t* bytecode_index_ptr = SPVM_DYNAMIC_ARRAY_pop(if_bytecode_index_stack);
                  int32_t bytecode_index = *bytecode_index_ptr;
                  
                  // Jump offset
                  int32_t jump_offset = bytecode_array->length - bytecode_index;
                  
                  // Set jump offset
                  bytecode_array->values[bytecode_index + 1] = (jump_offset >> 8) & 0xFF;
                  bytecode_array->values[bytecode_index + 2] = jump_offset & 0xFF;
                }
                else if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_IF_TRUE) {
                  
                  assert(goto_if_block_end_bytecode_index_stack->length > 0);
                  
                  int32_t* bytecode_index_ptr = SPVM_DYNAMIC_ARRAY_pop(goto_if_block_end_bytecode_index_stack);
                  int32_t bytecode_index = *bytecode_index_ptr;
                  
                  // Jump offset
                  int32_t jump_offset = bytecode_array->length - bytecode_index;
                  
                  // Set jump offset
                  bytecode_array->values[bytecode_index + 1] = (jump_offset >> 8) & 0xFF;
                  bytecode_array->values[bytecode_index + 2] = jump_offset & 0xFF;
                }
                else if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_LOOP) {
                  
                  int32_t* goto_loop_start_bytecode_index_ptr = SPVM_DYNAMIC_ARRAY_fetch(goto_loop_start_bytecode_index_stack, goto_loop_start_bytecode_index_stack->length - 1);
                  int32_t goto_loop_start_bytecode_index = *goto_loop_start_bytecode_index_ptr;
                  
                  // Jump offset
                  int32_t goto_loop_start_offset = bytecode_array->length - goto_loop_start_bytecode_index;
                  
                  bytecode_array->values[goto_loop_start_bytecode_index + 1] = (goto_loop_start_offset >> 8) & 0xFF;
                  bytecode_array->values[goto_loop_start_bytecode_index + 2] = goto_loop_start_offset & 0xFF;
                }
                else if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_EVAL) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_POP_CATCH_EXCEPTION);
                  
                  int32_t* bytecode_index_ptr = SPVM_DYNAMIC_ARRAY_pop(push_catch_exception_bytecode_index_stack);
                  int32_t bytecode_index = *bytecode_index_ptr;
                  
                  int32_t jump_offset_abs = bytecode_array->length - sub->bytecode_base;
                  
                  bytecode_array->values[bytecode_index + 1] = (jump_offset_abs >> 8) & 0xFF;
                  bytecode_array->values[bytecode_index + 2] = jump_offset_abs & 0xFF;
                }
                break;
              }
              case SPVM_OP_C_CODE_LOOP: {
                
                // Set last position
                while (goto_last_bytecode_index_stack->length > 0) {
                  
                  int32_t* goto_last_bytecode_index_ptr = SPVM_DYNAMIC_ARRAY_pop(goto_last_bytecode_index_stack);
                  int32_t goto_last_bytecode_index = *goto_last_bytecode_index_ptr;
                  
                  // Last offset
                  int32_t goto_last_offset = bytecode_array->length - goto_last_bytecode_index;
                  
                  bytecode_array->values[goto_last_bytecode_index + 1] = (goto_last_offset >> 8) & 0xFF;
                  bytecode_array->values[goto_last_bytecode_index + 2] = goto_last_offset & 0xFF;
                }
                
                break;
              }
              case SPVM_OP_C_CODE_CONDITION: {
                SPVM_OP* op_condition_target = op_cur->first;

                if (op_condition_target->code == SPVM_OP_C_CODE_UNDEF) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_NON_NULL);
                }
                else if (op_condition_target->code == SPVM_OP_C_CODE_EQ) {
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_condition_target->first);
                  if (!type) {
                    type = SPVM_OP_get_type(compiler, op_condition_target->last);
                  }
                  
                  if (!type) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_EQ_CMP_OBJECT);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_BYTE);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_EQ_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_SHORT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_EQ_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_INT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_EQ_CMP);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_LONG);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_EQ_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_FLOAT_G);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_EQ_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_DOUBLE_G);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_EQ_ZERO);
                  }
                  else {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_EQ_CMP_OBJECT);
                  }
                }
                else if (op_condition_target->code == SPVM_OP_C_CODE_NE) {
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_condition_target->first);
                  if (!type) {
                    type = SPVM_OP_get_type(compiler, op_condition_target->last);
                  }
                  
                  if (!type) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_NE_CMP_OBJECT);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_BYTE);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_NE_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_SHORT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_NE_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_INT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_NE_CMP);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_LONG);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_NE_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_FLOAT_G);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_NE_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_DOUBLE_G);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_NE_ZERO);
                  }
                  else {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_NE_CMP_OBJECT);
                  }
                }
                else if (op_condition_target->code == SPVM_OP_C_CODE_GT) {
                  
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_condition_target->first);
                  if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_BYTE);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_GT_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_SHORT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_GT_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_INT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_GT_CMP);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_LONG);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_GT_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_FLOAT_L);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_GT_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_DOUBLE_L);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_GT_ZERO);
                  }
                  else {
                    assert(0);
                  }
                }
                else if (op_condition_target->code == SPVM_OP_C_CODE_GE) {
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_condition_target->first);
                  if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_BYTE);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_GE_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_SHORT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_GE_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_INT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_GE_CMP);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_LONG);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_GE_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_FLOAT_L);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_GE_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_DOUBLE_L);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_GE_ZERO);
                  }
                  else {
                    assert(0);
                  }
                }
                else if (op_condition_target->code == SPVM_OP_C_CODE_LT) {
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_condition_target->first);
                  if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_BYTE);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_LT_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_SHORT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_LT_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_INT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_LT_CMP);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_LONG);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_LT_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_FLOAT_G);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_LT_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_DOUBLE_G);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_LT_ZERO);
                  }
                  else {
                    assert(0);
                  }
                }
                else if (op_condition_target->code == SPVM_OP_C_CODE_LE) {
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_condition_target->first);
                  if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_BYTE);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_LE_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_SHORT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_LE_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_INT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_LE_CMP);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_LONG);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_LE_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_FLOAT_G);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_LE_ZERO);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CMP_DOUBLE_G);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_LE_ZERO);
                  }
                  else {
                    assert(0);
                  }
                }
                else if (op_condition_target) {
                  
                  if (op_condition_target->code == SPVM_OP_C_CODE_IF) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_NE_ZERO);
                  }
                  else {
                    SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_condition_target);
                    assert(type);
                    if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_INT);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_NE_ZERO);
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_INT);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_NE_ZERO);
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_INT) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_NE_ZERO);
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_INT);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_NE_ZERO);
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_INT);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_NE_ZERO);
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_INT);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_NE_ZERO);
                    }
                    else {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_IF_NON_NULL);
                    }
                  }
                }
                
                int32_t bytecode_index = bytecode_array->length - 1;
                
                if (op_cur->flag & SPVM_OP_C_FLAG_CONDITION_IF) {
                  int32_t* bytecode_index_ptr = SPVM_COMPILER_ALLOCATOR_alloc_int(compiler, compiler->allocator);
                  *bytecode_index_ptr = bytecode_index;
                  
                  SPVM_DYNAMIC_ARRAY_push(if_bytecode_index_stack, bytecode_index_ptr);
                  
                  // Prepare for bytecode position of branch
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, 0);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, 0);
                }
                else if (op_cur->flag & SPVM_OP_C_FLAG_CONDITION_LOOP) {
                  assert(goto_loop_start_bytecode_index_stack->length > 0);
                  
                  int32_t* goto_loop_start_bytecode_index_ptr = SPVM_DYNAMIC_ARRAY_pop(goto_loop_start_bytecode_index_stack);
                  int32_t goto_loop_start_bytecode_index = *goto_loop_start_bytecode_index_ptr;
                  
                  // Jump offset
                  int32_t goto_loop_start_offset = goto_loop_start_bytecode_index - (bytecode_array->length - 1) + 3;
                  
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (goto_loop_start_offset >> 8) & 0xFF);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, goto_loop_start_offset & 0xFF);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_ARRAY_LENGTH : {
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ARRAY_LENGTH);
                
                break;
              }
              case SPVM_OP_C_CODE_LEFT_SHIFT: {
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_LEFT_SHIFT_BYTE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_LEFT_SHIFT_SHORT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_LEFT_SHIFT_INT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_LEFT_SHIFT_LONG);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_RIGHT_SHIFT: {
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_BYTE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_SHORT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_INT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_LONG);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_RIGHT_SHIFT_UNSIGNED: {
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_BYTE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_SHORT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_INT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_RIGHT_SHIFT_UNSIGNED_LONG);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_NEW: {
                if (op_cur->first->code == SPVM_OP_C_CODE_CONSTANT) {
                  SPVM_CONSTANT* constant = op_cur->first->uv.constant;
                  
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NEW_STRING);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (constant->id >> 24) & 0xFF);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (constant->id >> 16) & 0xFF);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (constant->id >> 8) & 0xFF);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, constant->id & 0xFF);
                }
                else if (op_cur->first->code == SPVM_OP_C_CODE_TYPE) {
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur->first);
                  
                  if (SPVM_TYPE_is_array(compiler, type)) {
                    switch (type->code) {
                      case SPVM_TYPE_C_CODE_BYTE_ARRAY:
                        SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NEW_BYTE_ARRAY);
                        break;
                      case SPVM_TYPE_C_CODE_SHORT_ARRAY:
                        SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NEW_SHORT_ARRAY);
                        break;
                      case SPVM_TYPE_C_CODE_INT_ARRAY:
                        SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NEW_INT_ARRAY);
                        break;
                      case SPVM_TYPE_C_CODE_LONG_ARRAY:
                        SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NEW_LONG_ARRAY);
                        break;
                      case SPVM_TYPE_C_CODE_FLOAT_ARRAY:
                        SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NEW_FLOAT_ARRAY);
                        break;
                      case SPVM_TYPE_C_CODE_DOUBLE_ARRAY:
                        SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NEW_DOUBLE_ARRAY);
                        break;
                      default:
                        SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NEW_OBJECT_ARRAY);
                        SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (type->id >> 24) & 0xFF);
                        SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (type->id >> 16) & 0xFF);
                        SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (type->id >> 8) & 0xFF);
                        SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, type->id & 0xFF);
                    }
                  }
                  else {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NEW_OBJECT);
                    
                    int32_t type_id = op_cur->first->uv.type->id;
                    assert(type_id);
                    
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (type_id >> 24) & 0xFF);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (type_id >> 16) & 0xFF);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (type_id >> 8) & 0xFF);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, type_id & 0xFF);
                  }
                }
                else {
                  assert(0);
                }
                
                break;
              }
              
              case SPVM_OP_C_CODE_UNDEF: {
                
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_UNDEF);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                
                break;
              }
              case SPVM_OP_C_CODE_PRE_INC: {
                SPVM_BYTECODE_BUILDER_push_inc_bytecode(compiler, bytecode_array, op_cur, 1);
                SPVM_BYTECODE_BUILDER_push_load_bytecode(compiler, bytecode_array, op_cur->first);
                
                break;
              }
              case SPVM_OP_C_CODE_POST_INC: {
                SPVM_BYTECODE_BUILDER_push_load_bytecode(compiler, bytecode_array, op_cur->first);
                SPVM_BYTECODE_BUILDER_push_inc_bytecode(compiler, bytecode_array, op_cur, 1);
                
                break;
              }
              case SPVM_OP_C_CODE_PRE_DEC: {
                SPVM_BYTECODE_BUILDER_push_inc_bytecode(compiler, bytecode_array, op_cur, -1);
                SPVM_BYTECODE_BUILDER_push_load_bytecode(compiler, bytecode_array, op_cur->first);
                
                break;
              }
              case SPVM_OP_C_CODE_POST_DEC: {
                SPVM_BYTECODE_BUILDER_push_load_bytecode(compiler, bytecode_array, op_cur->first);
                SPVM_BYTECODE_BUILDER_push_inc_bytecode(compiler, bytecode_array, op_cur, -1);
                
                break;
              }
              case SPVM_OP_C_CODE_BIT_XOR: {
                
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_BIT_XOR_BYTE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_BIT_XOR_SHORT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_BIT_XOR_INT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_BIT_XOR_LONG);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_BIT_OR: {
                
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_BIT_OR_BYTE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_BIT_OR_SHORT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_BIT_OR_INT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_BIT_OR_LONG);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                              
                break;
              }
              case SPVM_OP_C_CODE_BIT_AND: {
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_BIT_AND_BYTE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_BIT_AND_SHORT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_BIT_AND_INT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_BIT_AND_LONG);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_ARRAY_ELEM: {
                
                if (op_cur->lvalue) {
                  break;
                }
                
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                
                assert(last_type->code == SPVM_TYPE_C_CODE_INT);
                
                if (type->code == SPVM_TYPE_C_CODE_BYTE)
                {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ARRAY_LOAD_BYTE);
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ARRAY_LOAD_SHORT);
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ARRAY_LOAD_INT);
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ARRAY_LOAD_LONG);
                }
                else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ARRAY_LOAD_FLOAT);
                }
                else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ARRAY_LOAD_DOUBLE);
                }
                else {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ARRAY_LOAD_OBJECT);
                }

                
                break;
              }
              case SPVM_OP_C_CODE_ASSIGN: {
                
                if (op_cur->first->code == SPVM_OP_C_CODE_VAR) {
                  SPVM_OP* op_var = op_cur->first;
                  int32_t my_var_index = op_var->uv.var->op_my_var->uv.my_var->index;
                  
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_var);
                  
                  if (my_var_index > 0xFF) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_WIDE);
                  }
                  
                  _Bool has_operand = 0;
                  
                  if (SPVM_TYPE_is_numeric(compiler, type)) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_STORE);
                    has_operand = 1;
                  }
                  else {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_STORE_OBJECT);
                    has_operand = 1;
                  }
                  
                  if (has_operand) {
                    if (my_var_index > 0xFF) {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (my_var_index >> 8) & 0xFF);
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, my_var_index);
                    }
                    else {
                      SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, my_var_index);
                    }
                  }
                }
                else if (op_cur->first->code == SPVM_OP_C_CODE_PACKAGE_VAR) {
                  SPVM_OP* op_package_var = op_cur->first;
                  
                  SPVM_PACKAGE_VAR* package_var = op_package_var->uv.package_var;

                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_package_var);

                  if (SPVM_TYPE_is_numeric(compiler, type)) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_STORE_PACKAGE_VAR);
                  }
                  else {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_STORE_PACKAGE_VAR_OBJECT);
                  }
                                    
                  int32_t package_var_id = package_var->op_our->uv.our->id;

                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (package_var_id >> 24) & 0xFF);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (package_var_id >> 16) & 0xFF);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (package_var_id >> 8) & 0xFF);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, package_var_id & 0xFF);
                }
                else if (op_cur->first->code == SPVM_OP_C_CODE_ARRAY_ELEM) {
                  
                  SPVM_OP* op_array_elem = op_cur->first;
                  SPVM_OP* op_term_index = op_array_elem->last;
                  
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_array_elem);
                  SPVM_TYPE* index_type = SPVM_OP_get_type(compiler, op_term_index);
                  
                  assert(index_type->code == SPVM_TYPE_C_CODE_INT);
                  
                  if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ARRAY_STORE_BYTE);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ARRAY_STORE_SHORT);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_INT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ARRAY_STORE_INT);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ARRAY_STORE_LONG);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ARRAY_STORE_FLOAT);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ARRAY_STORE_DOUBLE);
                  }
                  else {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ARRAY_STORE_OBJECT);
                  }
                }
                else if (op_cur->first->code == SPVM_OP_C_CODE_CALL_FIELD) {
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur->first);
                  
                  if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_SET_FIELD_BYTE);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_SET_FIELD_SHORT);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_INT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_SET_FIELD_INT);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_SET_FIELD_LONG);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_SET_FIELD_FLOAT);
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_SET_FIELD_DOUBLE);
                  }
                  else {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_SET_FIELD_OBJECT);
                  }
                  
                  // Call field
                  SPVM_CALL_FIELD* call_field = op_cur->first->uv.call_field;
                  SPVM_FIELD* field = call_field->field;

                  SPVM_CONSTANT_POOL_FIELD constant_pool_field;
                  memcpy(&constant_pool_field, &compiler->constant_pool->values[field->id], sizeof(SPVM_CONSTANT_POOL_FIELD));
                  
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, ((constant_pool_field.index) >> 8) & 0xFF);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (constant_pool_field.index) & 0xFF);
                }
                else if (op_cur->first->code == SPVM_OP_C_CODE_EXCEPTION_VAR) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_STORE_EXCEPTION);
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
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_RETURN_VOID);
                }
                else if (return_type->code == SPVM_TYPE_C_CODE_BYTE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_RETURN_BYTE);
                }
                else if (return_type->code == SPVM_TYPE_C_CODE_SHORT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_RETURN_SHORT);
                }
                else if (return_type->code == SPVM_TYPE_C_CODE_INT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_RETURN_INT);
                }
                else if (return_type->code == SPVM_TYPE_C_CODE_LONG) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_RETURN_LONG);
                }
                else if (return_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_RETURN_FLOAT);
                }
                else if (return_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_RETURN_DOUBLE);
                }
                else {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_RETURN_OBJECT);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_NEGATE: {
                
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NEGATE_BYTE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NEGATE_SHORT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NEGATE_INT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NEGATE_LONG);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NEGATE_FLOAT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NEGATE_DOUBLE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
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
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_SHORT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_INT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_INT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_LONG) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_LONG);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_FLOAT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_BYTE_TO_DOUBLE);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else {
                    assert(0);
                  }
                }
                else if (src_type->code == SPVM_TYPE_C_CODE_SHORT) {
                  if (dist_type->code == SPVM_TYPE_C_CODE_BYTE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_BYTE);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_SHORT) {
                    // None
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_INT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_INT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_LONG) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_LONG);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_FLOAT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_SHORT_TO_DOUBLE);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else {
                    assert(0);
                  }
                }
                else if (src_type->code == SPVM_TYPE_C_CODE_INT) {
                  if (dist_type->code == SPVM_TYPE_C_CODE_BYTE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_BYTE);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_SHORT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_SHORT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_INT) {
                    // None
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_LONG) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_LONG);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_FLOAT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_INT_TO_DOUBLE);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else {
                    assert(0);
                  }
                }
                else if (src_type->code == SPVM_TYPE_C_CODE_LONG) {
                  if (dist_type->code == SPVM_TYPE_C_CODE_BYTE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_BYTE);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_SHORT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_SHORT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_INT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_INT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_LONG) {
                    // None
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_FLOAT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_LONG_TO_DOUBLE);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else {
                    assert(0);
                  }
                }
                else if (src_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  if (dist_type->code == SPVM_TYPE_C_CODE_BYTE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_BYTE);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_SHORT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_SHORT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_INT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_INT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_LONG) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_LONG);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    // None
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_FLOAT_TO_DOUBLE);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else {
                    assert(0);
                  }
                }
                else if (src_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  if (dist_type->code == SPVM_TYPE_C_CODE_BYTE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_BYTE);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_SHORT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_SHORT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_INT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_INT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_LONG) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_LONG);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (dist_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONVERT_DOUBLE_TO_FLOAT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
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
              case SPVM_OP_C_CODE_POP: {
                
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_POP);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                
                break;
              }
              case SPVM_OP_C_CODE_ADD: {
                
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                assert(type);
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ADD_BYTE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ADD_SHORT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ADD_INT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ADD_LONG);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ADD_FLOAT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_ADD_DOUBLE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_CONCAT_STRING: {
                
                SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                assert(first_type->code == SPVM_TYPE_C_CODE_STRING);
                
                SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                if (last_type->code == SPVM_TYPE_C_CODE_STRING) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONCAT_STRING_STRING);
                }
                else if (last_type->code == SPVM_TYPE_C_CODE_BYTE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONCAT_STRING_BYTE);
                }
                else if (last_type->code == SPVM_TYPE_C_CODE_SHORT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONCAT_STRING_SHORT);
                }
                else if (last_type->code == SPVM_TYPE_C_CODE_INT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONCAT_STRING_INT);
                }
                else if (last_type->code == SPVM_TYPE_C_CODE_LONG) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONCAT_STRING_LONG);
                }
                else if (last_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONCAT_STRING_FLOAT);
                }
                else if (last_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_CONCAT_STRING_DOUBLE);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_SUBTRACT: {
                
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_SUBTRACT_BYTE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_SUBTRACT_SHORT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_SUBTRACT_INT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_SUBTRACT_LONG);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_SUBTRACT_FLOAT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_SUBTRACT_DOUBLE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_MULTIPLY: {
                
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_MULTIPLY_BYTE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_MULTIPLY_SHORT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_MULTIPLY_INT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_MULTIPLY_LONG);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_MULTIPLY_FLOAT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_MULTIPLY_DOUBLE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_DIVIDE: {
                
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_DIVIDE_BYTE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_DIVIDE_SHORT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_DIVIDE_INT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_DIVIDE_LONG);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_DIVIDE_FLOAT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_DIVIDE_DOUBLE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_REMAINDER: {
                
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_REMAINDER_BYTE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_REMAINDER_SHORT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_REMAINDER_INT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_REMAINDER_LONG);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_REMAINDER_FLOAT);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_REMAINDER_DOUBLE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_VAR: {
                if (op_cur->lvalue) {
                  break;
                }
                
                SPVM_BYTECODE_BUILDER_push_load_bytecode(compiler, bytecode_array, op_cur);
                
                break;
              }
              case SPVM_OP_C_CODE_PACKAGE_VAR: {
                if (op_cur->lvalue) {
                  break;
                }
                
                SPVM_OUR* our = op_cur->uv.package_var->op_our->uv.our;
                
                int32_t package_var_id = our->id;

                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_LOAD_PACKAGE_VAR);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (package_var_id >> 24) & 0xFF);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (package_var_id >> 16) & 0xFF);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (package_var_id >> 8) & 0xFF);
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, package_var_id & 0xFF);
                
                break;
              }
              case SPVM_OP_C_CODE_EXCEPTION_VAR: {
                if (op_cur->lvalue) {
                  break;
                }
                
                SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_LOAD_EXCEPTION);
                
                break;
              }
              case SPVM_OP_C_CODE_CONSTANT: {
                SPVM_CONSTANT* constant = op_cur->uv.constant;
                
                if (op_cur->flag == SPVM_OP_C_FLAG_CONSTANT_CASE) {
                  break;
                }
                
                _Bool bytecode_set = 0;
                
                if (constant->type->code == SPVM_TYPE_C_CODE_BYTE) {
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_PUSH_BYTE);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, constant->value.byte_value);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  bytecode_set = 1;
                }
                else if (constant->type->code == SPVM_TYPE_C_CODE_SHORT) {
                  if (constant->value.short_value >= -128 && constant->value.short_value <= 127) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_PUSH_BYTE_TO_SHORT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, constant->value.short_value & 0xFF);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    
                    bytecode_set = 1;
                  }
                  else {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_PUSH_SHORT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (constant->value.short_value >> 8) & 0xFF);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, constant->value.short_value & 0xFF);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);

                    bytecode_set = 1;
                  }
                }
                else if (constant->type->code == SPVM_TYPE_C_CODE_INT) {
                  
                  if (constant->value.int_value >= -128 && constant->value.int_value <= 127) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_PUSH_BYTE_TO_INT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, constant->value.int_value & 0xFF);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  
                    bytecode_set = 1;
                  }
                  else if (constant->value.int_value >= -32768 && constant->value.int_value <= 32767) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_PUSH_SHORT_TO_INT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (constant->value.int_value >> 8) & 0xFF);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, constant->value.int_value & 0xFF);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    
                    bytecode_set = 1;
                  }
                }
                else if (constant->type->code == SPVM_TYPE_C_CODE_LONG) {
                  if (constant->value.long_value >= -128 && constant->value.long_value <= 127) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_PUSH_BYTE_TO_LONG);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, constant->value.long_value & 0xFF);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  
                    bytecode_set = 1;
                  }
                  else if (constant->value.long_value >= -32768 && constant->value.long_value <= 32767) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_PUSH_SHORT_TO_LONG);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);

                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (constant->value.long_value >> 8) & 0xFF);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, constant->value.long_value & 0xFF);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    
                    bytecode_set = 1;
                  }
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
                  if (constant->type->code == SPVM_TYPE_C_CODE_INT || constant->type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_LOAD_CONSTANT);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else if (constant->type->code == SPVM_TYPE_C_CODE_LONG || constant->type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_LOAD_CONSTANT2);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                    SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, SPVM_BYTECODE_C_CODE_NOP);
                  }
                  else {
                    assert(0);
                  }
                  
                  assert(constant->id != -1);
                  
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (constant->id >> 24) & 0xFF);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (constant->id >> 16) & 0xFF);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, (constant->id >> 8) & 0xFF);
                  SPVM_BYTECODE_ARRAY_push(compiler, bytecode_array, constant->id & 0xFF);
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
      sub->bytecode_length = bytecode_array->length - sub->bytecode_base;
      
      // Set bytecode base to sub
      SPVM_CONSTANT_POOL_SUB constant_pool_sub;
      memcpy(&constant_pool_sub, &compiler->constant_pool->values[sub->id], sizeof(SPVM_CONSTANT_POOL_SUB));
      constant_pool_sub.bytecode_base = sub->bytecode_base;
      memcpy(&compiler->constant_pool->values[sub->id], &constant_pool_sub, sizeof(SPVM_CONSTANT_POOL_SUB));
      
    }
  }
}
