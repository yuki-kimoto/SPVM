// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#include "spvm_compiler.h"
#include "spvm_opcode_builder.h"
#include "spvm_opcode.h"
#include "spvm_opcode_list.h"
#include "spvm_constant.h"
#include "spvm_op.h"
#include "spvm_check.h"
#include "spvm_type.h"
#include "spvm_list.h"
#include "spvm_method.h"
#include "spvm_var.h"
#include "spvm_var_decl.h"
#include "spvm_allocator.h"
#include "spvm_field_access.h"
#include "spvm_call_method.h"
#include "spvm_hash.h"
#include "spvm_field.h"
#include "spvm_switch_info.h"
#include "spvm_type.h"
#include "spvm_object.h"
#include "spvm_class_var.h"
#include "spvm_class_var_access.h"
#include "spvm_dumper.h"
#include "spvm_opcode.h"
#include "spvm_block.h"
#include "spvm_basic_type.h"
#include "spvm_case_info.h"
#include "spvm_array_field_access.h"
#include "spvm_string.h"
#include "spvm_dumper.h"

void SPVM_OPCODE_BUILDER_build_opcodes(SPVM_COMPILER* compiler) {
  
  for (int32_t basic_type_id = compiler->basic_types_base_id; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    SPVM_LIST* methods = basic_type->methods;
    for (int32_t method_index = 0; method_index < methods->length; method_index++) {
      SPVM_METHOD* method = SPVM_LIST_get(methods, method_index);
      
      SPVM_OPCODE_LIST* opcode_list = method->opcode_list;
      
      int32_t method_opcodes_base_address_id = 0;
      
      // Check sub information
      assert(method->op_name);
      assert(method->return_type);
      assert(method->current_basic_type->file);
      
      // Copy arguments to variables
      int32_t stack_index = 0;
      for (int32_t args_index = 0; args_index < method->args_length; args_index++) {
        SPVM_VAR_DECL* arg = SPVM_LIST_get(method->var_decls, args_index);
        SPVM_TYPE* arg_type = arg->type;
        int32_t arg_type_dimension = arg->type->dimension;
        SPVM_BASIC_TYPE* arg_basic_type = arg_type->basic_type;
        int32_t arg_type_is_ref = SPVM_TYPE_is_ref_type(compiler, arg_basic_type->id, arg_type_dimension, arg_type->flag);
        int32_t arg_basic_type_category = arg_type->basic_type->category;
        
        SPVM_OPCODE opcode = {0};
        
        int32_t arg_type_width = SPVM_TYPE_get_type_width(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag);

        if (arg_type_dimension == 0) {
          if (arg_type_is_ref) {
            switch (arg_basic_type_category) {
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC:
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
              {
                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_REF);
                opcode.operand0 = arg->typed_var_index;
                opcode.operand3 = stack_index & 0xFF;
                stack_index++;
                break;
              }
              default: {
                assert(0);
              }
            }
          }
          else {
            switch (arg_basic_type_category) {
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC: {
                switch (arg_basic_type->id) {
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_BYTE);
                    opcode.operand0 = arg->typed_var_index;
                    opcode.operand3 = stack_index & 0xFF;
                    stack_index++;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_SHORT);
                    opcode.operand0 = arg->typed_var_index;
                    opcode.operand3 = stack_index & 0xFF;
                    stack_index++;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_INT);
                    opcode.operand0 = arg->typed_var_index;
                    opcode.operand3 = stack_index & 0xFF;
                    stack_index++;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_LONG);
                    opcode.operand0 = arg->typed_var_index;
                    opcode.operand3 = stack_index & 0xFF;
                    stack_index++;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_FLOAT);
                    opcode.operand0 = arg->typed_var_index;
                    opcode.operand3 = stack_index & 0xFF;
                    stack_index++;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_DOUBLE);
                    opcode.operand0 = arg->typed_var_index;
                    opcode.operand3 = stack_index & 0xFF;
                    stack_index++;
                    break;
                  }
                  default: {
                    assert(0);
                  }
                }
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
              {
                SPVM_FIELD* arg_mulnum_field = SPVM_LIST_get(arg_basic_type->fields, 0);
                SPVM_TYPE* arg_mulnum_field_type = arg_mulnum_field->type;
                SPVM_BASIC_TYPE* arg_mulnum_field_basic_type = arg_mulnum_field_type->basic_type;
                
                switch (arg_mulnum_field_basic_type->id) {
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_MULNUM_BYTE);
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_MULNUM_SHORT);
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_MULNUM_INT);
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_MULNUM_LONG);
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_MULNUM_FLOAT);
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_MULNUM_DOUBLE);
                    break;
                  }
                }
                opcode.operand0 = arg->typed_var_index;
                assert(arg_type_width < 0xFFFF);
                opcode.operand3 = arg_type_width << 8 | stack_index & 0xFF;
                stack_index += arg_type_width;
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING:
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS:
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE:
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT:
              {
                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_OBJECT);
                opcode.operand0 = arg->typed_var_index;
                opcode.operand3 = stack_index & 0xFF;
                stack_index++;
                break;
              }
              default: {
                assert(0);
              }
            }
          }
        }
        else if (arg_type_dimension == 1) {
          switch (arg_basic_type_category) {
            case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC:
            case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
            case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING:
            case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS:
            case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE:
            case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT:
            {
              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_OBJECT);
              opcode.operand0 = arg->typed_var_index;
              opcode.operand3 = stack_index & 0xFF;
              stack_index++;
              break;
            }
            default: {
              assert(0);
            }
          }
        }
        else if (arg_type_dimension == 2) {
          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_OBJECT);
          opcode.operand0 = arg->typed_var_index;
          opcode.operand3 = stack_index & 0xFF;
          stack_index++;
        }
        else {
          assert(0);
        }
        
        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
      }
      
      {
        SPVM_OPCODE opcode = {0};
        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_END_ARGS);
        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
      }
      
      int32_t mortal_stack_tops_index = 0;
      
      int32_t mortal_stack_max = 0;
      
      int32_t mortal_stack_tops_max = 0;
      
      if (method->is_native) {
        goto END_OF_FUNCTION;
      }
      
      SPVM_LIST* block_stack = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* switch_stack_switch_info = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* break_opcode_index_stack = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* break_opcode_index_base_stack = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* last_opcode_index_stack = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* last_opcode_index_base_stack = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* next_opcode_index_stack = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* next_opcode_index_base_stack = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* return_opcode_index_stack = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* eval_block_stack = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* catch_on_exception_opcode_index_stack = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* return_on_exception_opcode_index_stack = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* mortal_stack = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      // Run OPs
      SPVM_OP* op_base = method->op_block;
      SPVM_OP* op_cur = op_base;
      int32_t finish = 0;
      
      int32_t new_object_count = 0;
      while (op_cur) {
        
        int32_t check_exception = 0;
        
        // [START]Preorder traversal position
        switch (op_cur->id) {
          case SPVM_OP_C_ID_BLOCK: { // Preorder
            
            SPVM_BLOCK* block = op_cur->uv.block;
            
            block->begin_opcode_index = opcode_list->length;
            
            SPVM_LIST_push(block_stack, (void*)(intptr_t)block);
            
            if (block->id == SPVM_BLOCK_C_ID_ELSE) {
              SPVM_OPCODE* condition_goto = (opcode_list->values + block->condition_opcode_index);
              int32_t condition_goto_opcode_base_index = opcode_list->length;
              condition_goto->operand0 = condition_goto_opcode_base_index;
            }
            else if (block->id == SPVM_BLOCK_C_ID_LOOP_OUTER) {
              int32_t last_block_base = last_opcode_index_stack->length;
              SPVM_LIST_push(last_opcode_index_base_stack, (void*)(intptr_t)last_block_base);
            }
            else if (block->id == SPVM_BLOCK_C_ID_LOOP_INNER) {
              int32_t next_block_base = next_opcode_index_stack->length;
              SPVM_LIST_push(next_opcode_index_base_stack, (void*)(intptr_t)next_block_base);
            }
            else if (block->id == SPVM_BLOCK_C_ID_SWITCH_OUTER) {
              int32_t break_block_base = break_opcode_index_stack->length;
              SPVM_LIST_push(break_opcode_index_base_stack, (void*)(intptr_t)break_block_base);
            }
            else if (block->id == SPVM_BLOCK_C_ID_EVAL) {
              SPVM_LIST_push(eval_block_stack, block);
              
              // Set exception var to undef in the beginning of eval block
              {
                SPVM_OPCODE opcode = {0};
                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CLEAR_EVAL_ERROR_ID);
                SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
              }
              {
                SPVM_OPCODE opcode = {0};
                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR_UNDEF);
                SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
              }
            }
            
            if (block->need_leave_scope) {
              SPVM_OPCODE opcode = {0};
              
              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_ENTER_SCOPE);
              opcode.operand0 = mortal_stack_tops_index;
              block->mortal_stack_tops_index = mortal_stack_tops_index;
              mortal_stack_tops_index++;
              if (mortal_stack_tops_index > mortal_stack_tops_max) {
                mortal_stack_tops_max = mortal_stack_tops_index;
              }
              
              SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
            }
            
            break;
          }
          case SPVM_OP_C_ID_SWITCH: {
            SPVM_SWITCH_INFO* switch_info = op_cur->uv.switch_info;
            SPVM_LIST_push(switch_stack_switch_info, switch_info);
            break;
          }
          case SPVM_OP_C_ID_CASE: {
            if (switch_stack_switch_info->length > 0) {
              SPVM_SWITCH_INFO* switch_info = SPVM_LIST_get(switch_stack_switch_info, switch_stack_switch_info->length - 1);
              int32_t opcode_index = opcode_list->length;
              op_cur->uv.case_info->goto_opcode_index = opcode_index;
            }
            break;
          }
          case SPVM_OP_C_ID_DEFAULT: {
            if (switch_stack_switch_info->length > 0) {
              SPVM_SWITCH_INFO* switch_info = SPVM_LIST_get(switch_stack_switch_info, switch_stack_switch_info->length - 1);
              switch_info->default_opcode_index = opcode_list->length;
            }
            break;
          }
          case SPVM_OP_C_ID_LOOP_INCREMENT: {
            
            SPVM_BLOCK* block = SPVM_LIST_get(block_stack, block_stack->length - 1);
            
            block->loop_increment_opcode_index = opcode_list->length;
            
            break;
          }
        }
        
        // [END]Preorder traversal position
        
        if (op_cur->first) {
          op_cur = op_cur->first;
        }
        else {
          while (1) {
            // [START]Postorder traversal position
            switch (op_cur->id) {
              case SPVM_OP_C_ID_BLOCK: { // Postorder
                SPVM_BLOCK* block = op_cur->uv.block;
                
                if (block->id == SPVM_BLOCK_C_ID_EVAL) {
                  
                  // Set exception variable to undef in the end of eval block
                  {
                    SPVM_OPCODE opcode = {0};
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CLEAR_EVAL_ERROR_ID);
                    SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                  }
                  {
                    SPVM_OPCODE opcode = {0};
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR_UNDEF);
                    SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                  }
                  
                  while (catch_on_exception_opcode_index_stack->length > 0) {
                    int32_t catch_on_exception_goto_opcode_index = (intptr_t)SPVM_LIST_pop(catch_on_exception_opcode_index_stack);
                    SPVM_OPCODE* catch_on_exception_goto = (opcode_list->values + catch_on_exception_goto_opcode_index);
                    catch_on_exception_goto->operand0 = opcode_list->length;
                  }
                  
                  SPVM_LIST_pop(eval_block_stack);
                }
                else if (block->id == SPVM_BLOCK_C_ID_METHOD) {
                  while (return_opcode_index_stack->length > 0) {
                    int32_t return_goto_opcode_index = (intptr_t)SPVM_LIST_pop(return_opcode_index_stack);
                    SPVM_OPCODE* return_goto = (opcode_list->values + return_goto_opcode_index);
                    return_goto->operand1 = opcode_list->length;
                  }

                  while (return_on_exception_opcode_index_stack->length > 0) {
                    int32_t return_on_exception_goto_opcode_index = (intptr_t)SPVM_LIST_pop(return_on_exception_opcode_index_stack);
                    SPVM_OPCODE* return_on_exception_goto = (opcode_list->values + return_on_exception_goto_opcode_index);
                    return_on_exception_goto->operand0 = opcode_list->length;
                  }
                }
                else if (block->id == SPVM_BLOCK_C_ID_SWITCH_OUTER) {
                  int32_t break_opcode_index_base = (intptr_t)SPVM_LIST_pop(break_opcode_index_base_stack);
                  int32_t break_opcode_index_stack_pop_count = break_opcode_index_stack->length - break_opcode_index_base;
                  for (int32_t i = 0; i < break_opcode_index_stack_pop_count; i++) {
                    int32_t break_goto_opcode_index = (intptr_t)SPVM_LIST_pop(break_opcode_index_stack);
                    SPVM_OPCODE* break_goto = (opcode_list->values + break_goto_opcode_index);
                    break_goto->operand0 = opcode_list->length;
                  }
                }
                else if (block->id == SPVM_BLOCK_C_ID_LOOP_OUTER) {
                  int32_t last_opcode_index_base = (intptr_t)SPVM_LIST_pop(last_opcode_index_base_stack);
                  int32_t last_opcode_index_stack_pop_count = last_opcode_index_stack->length - last_opcode_index_base;
                  for (int32_t i = 0; i < last_opcode_index_stack_pop_count; i++) {
                    int32_t last_goto_opcode_index = (intptr_t)SPVM_LIST_pop(last_opcode_index_stack);
                    SPVM_OPCODE* last_goto = (opcode_list->values + last_goto_opcode_index);
                    last_goto->operand0 = opcode_list->length;
                  }
                }
                else if (block->id == SPVM_BLOCK_C_ID_LOOP_INNER) {
                  int32_t next_opcode_index_base = (intptr_t)SPVM_LIST_pop(next_opcode_index_base_stack);
                  int32_t next_opcode_index_stack_pop_count = next_opcode_index_stack->length - next_opcode_index_base;
                  for (int32_t i = 0; i < next_opcode_index_stack_pop_count; i++) {
                    int32_t next_goto_opcode_index = (intptr_t)SPVM_LIST_pop(next_opcode_index_stack);
                    SPVM_OPCODE* next_goto = (opcode_list->values + next_goto_opcode_index);
                    next_goto->operand0 = block->loop_increment_opcode_index;
                  }
                }
                
                // Leave scope
                if (block->need_leave_scope) {
                  mortal_stack_tops_index--;
                  
                  SPVM_OPCODE opcode = {0};
                   
                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LEAVE_SCOPE);
                  opcode.operand0 = mortal_stack_tops_index;
                  SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                }
                
                if (block->id == SPVM_BLOCK_C_ID_IF) {
                  block->if_end_goto_opcode_index = opcode_list->length;
                  
                  SPVM_OPCODE opcode = {0};
                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GOTO);
                  SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                }
                else if (block->id == SPVM_BLOCK_C_ID_ELSE) {
                  SPVM_OP* op_if = SPVM_OP_get_parent(compiler, op_cur);
                  SPVM_OP* op_block_true = SPVM_OP_sibling(compiler, op_if->first);
                  assert(op_block_true->id == SPVM_OP_C_ID_BLOCK);
                  
                  SPVM_OPCODE* if_block_end_goto = (opcode_list->values + op_block_true->uv.block->if_end_goto_opcode_index);
                  if_block_end_goto->operand0 = opcode_list->length;
                }
                else if (block->id == SPVM_BLOCK_C_ID_LOOP_INNER) {
                  
                  SPVM_OPCODE opcode = {0};
                  
                  // Add goto
                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GOTO);
                  opcode.operand0 = block->begin_opcode_index;
                  SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                }
                
                SPVM_LIST_pop(block_stack);
                
                break;
              }
              case SPVM_OP_C_ID_CONDITION:
              case SPVM_OP_C_ID_CONDITION_NOT:
              {
                
                int32_t opcode_index = opcode_list->length;
                
                SPVM_OP* op_block_true = SPVM_OP_sibling(compiler, op_cur);
                assert(op_block_true->id == SPVM_OP_C_ID_BLOCK);
                op_block_true->uv.block->condition_opcode_index = opcode_index;
                
                SPVM_OP* op_block_false = SPVM_OP_sibling(compiler, op_block_true);
                assert(op_block_false->id == SPVM_OP_C_ID_BLOCK);
                op_block_false->uv.block->condition_opcode_index = opcode_index;
                
                SPVM_OPCODE opcode = {0};
                
                if (op_cur->id == SPVM_OP_C_ID_CONDITION) {
                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IF_EQ_ZERO);
                }
                else if (op_cur->id == SPVM_OP_C_ID_CONDITION_NOT) {
                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IF_NE_ZERO);
                }
                else {
                  assert(0);
                }
                
                int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur->first);
                
                opcode.operand1 = typed_var_index_in;
                
                SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                
                break;
              }
              case SPVM_OP_C_ID_NEXT: {
                // GOTO increment statement
                SPVM_OPCODE opcode = {0};
                
                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GOTO);
                SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                
                int32_t opcode_index = opcode_list->length - 1;
                
                SPVM_LIST_push(next_opcode_index_stack, (void*)(intptr_t)opcode_index);
                
                break;
              }
              case SPVM_OP_C_ID_LAST: {
                // GOTO end of loop init block
                SPVM_OPCODE opcode = {0};
                
                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GOTO);
                SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                
                int32_t opcode_index = opcode_list->length - 1;
                
                SPVM_LIST_push(last_opcode_index_stack, (void*)(intptr_t)opcode_index);
                
                break;
              }
              case SPVM_OP_C_ID_SWITCH: {
                
                // Pop switch information
                SPVM_SWITCH_INFO* switch_info = SPVM_LIST_pop(switch_stack_switch_info);
                
                // Set the information of switch opcodes
                int32_t opcode_index = switch_info->opcode_index;
                SPVM_OPCODE* opcode = opcode_list->values + opcode_index;
                opcode->operand1 = switch_info->default_opcode_index;
                opcode->operand2 = switch_info->case_infos->length;

                // Set case info operands
                SPVM_LIST* case_infos = switch_info->case_infos;
                for (int32_t i = 0; i < switch_info->case_infos->length; i++) {
                  SPVM_OPCODE* opcode_case_info = opcode_list->values + opcode_index + 1 + i;
                  SPVM_CASE_INFO* case_info = SPVM_LIST_get(case_infos, i);
                  opcode_case_info->operand1 = case_info->case_value;
                  opcode_case_info->operand2 = case_info->goto_opcode_index;
                }
                
                break;
              }
              case SPVM_OP_C_ID_SWITCH_CONDITION: {
                assert(switch_stack_switch_info->length > 0);
                
                SPVM_SWITCH_INFO* switch_info = SPVM_LIST_get(switch_stack_switch_info, switch_stack_switch_info->length - 1);
                
                int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur->first);
                
                int32_t opcode_index = opcode_list->length;
                switch_info->opcode_index = opcode_index;
                
                // Add switch opcode
                SPVM_OPCODE opcode_switch_info;
                memset(&opcode_switch_info, 0, sizeof(SPVM_OPCODE));
                opcode_switch_info.id = SPVM_OPCODE_C_ID_LOOKUP_SWITCH;
                opcode_switch_info.operand0 = typed_var_index_in;
                SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode_switch_info);
                
                // Match values and branchs
                for (int32_t i = 0; i < switch_info->case_infos->length; i++) {
                  SPVM_CASE_INFO* case_info = SPVM_LIST_get(switch_info->case_infos, i);
                  
                  // Branch
                  SPVM_CASE_INFO* branch_opcode_index_case_info = switch_info->case_infos->values[i];
                  branch_opcode_index_case_info->goto_opcode_index = case_info->goto_opcode_index;
                  
                  // Add case info
                  SPVM_OPCODE opcode_case_info;
                  memset(&opcode_case_info, 0, sizeof(SPVM_OPCODE));
                  opcode_case_info.id = SPVM_OPCODE_C_ID_CASE_INFO;
                  SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode_case_info);
                }
                
                // Default branch
                int32_t default_opcode_index = switch_info->default_opcode_index;
                if (default_opcode_index == 0) {
                  default_opcode_index = opcode_list->length + 1;
                }
                switch_info->default_opcode_index = default_opcode_index;
                
                break;
              }
              case SPVM_OP_C_ID_BREAK: {
                // GOTO end of switch block
                SPVM_OPCODE opcode = {0};
                
                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GOTO);
                SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                
                int32_t opcode_index = opcode_list->length - 1;
                
                SPVM_LIST_push(break_opcode_index_stack, (void*)(intptr_t)opcode_index);
                
                break;
              }
              case SPVM_OP_C_ID_RETURN: {
                if (op_cur->first) {
                  SPVM_TYPE* return_type = SPVM_CHECK_get_type(compiler, op_cur->first);
                  
                  if (SPVM_TYPE_is_undef_type(compiler, return_type->basic_type->id, return_type->dimension, return_type->flag)) {
                    SPVM_OPCODE opcode = {0};
                    
                    
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_UNDEF);
                    
                    SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                  }
                  else {
                    SPVM_OPCODE opcode = {0};
                    
                     
                    
                    int32_t typed_var_index_in;
                    if (SPVM_TYPE_is_numeric_type(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag)) {
                      switch (method->return_type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_BYTE);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur->first);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_SHORT);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur->first);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_INT);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur->first);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_LONG);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur->first);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_FLOAT);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur->first);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_DOUBLE);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur->first);
                          break;
                        }
                        default:
                          assert(0);
                      }
                    }
                    else if (SPVM_TYPE_is_object_type(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag)) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_OBJECT);
                      typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur->first);
                    }
                    else if (SPVM_TYPE_is_mulnum_type(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag)) {
                      SPVM_FIELD* first_field = SPVM_LIST_get(return_type->basic_type->fields, 0);
                      assert(first_field);
                      
                      SPVM_TYPE* field_type = first_field->type;
                      assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));

                      switch (field_type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur->first);
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_MULNUM_BYTE);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur->first);
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_MULNUM_SHORT);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur->first);
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_MULNUM_INT);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur->first);
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_MULNUM_LONG);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur->first);
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_MULNUM_FLOAT);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur->first);
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_MULNUM_DOUBLE);
                          break;
                        }
                        default:
                          assert(0);
                      }
                    }
                    else {
                      assert(0);
                    }
                    
                    int32_t method_return_width = SPVM_TYPE_get_type_width(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag);

                    opcode.operand0 = typed_var_index_in;
                    opcode.operand2 = method_return_width;
                    
                    SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                  }
                }
                else {
                  SPVM_OPCODE opcode = {0};
                  
                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_VOID);
                  SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                }
                
                int32_t return_opcode_index = opcode_list->length - 1;
                
                SPVM_LIST_push(return_opcode_index_stack, (void*)(intptr_t)return_opcode_index);
                
                break;
              }
              case SPVM_OP_C_ID_DIE: {
                
                SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, op_cur->last);
                
                // SET_ERROR_ID_BY_TYPE
                {
                  SPVM_OPCODE opcode = {0};
                  
                  // Type
                  if (op_cur->last->id == SPVM_OP_C_ID_TYPE) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ERROR_ID_BY_TYPE);
                    opcode.operand0 = type->basic_type->id;
                  }
                  // Basic type ID
                  else {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ERROR_ID);
                    opcode.operand0 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur->last);
                  }
                  SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                }
                
                check_exception = 1;
                
                break;
              }
              case SPVM_OP_C_ID_VAR: {
                if (op_cur->uv.var->is_declaration) {
                  
                  SPVM_VAR_DECL* var_decl = op_cur->uv.var->var_decl;
                  
                  SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, var_decl->op_var_decl);
                  if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                    
                    SPVM_OPCODE opcode = {0};
                    
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PUSH_MORTAL);
                    int32_t typed_var_index = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur);
                    opcode.operand0 = typed_var_index;
                    SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                    
                    SPVM_LIST_push(mortal_stack, (void*)(intptr_t)typed_var_index);
                    
                    if (mortal_stack->length > mortal_stack_max) {
                      mortal_stack_max = mortal_stack->length;
                    }
                  }
                  
                  // Initialized not initialized variable
                  if (!op_cur->uv.var->is_initialized && !op_cur->uv.var->var_decl->is_arg) {
                    // Multi numeric type
                    if (SPVM_TYPE_is_mulnum_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                      SPVM_FIELD* first_field = SPVM_LIST_get(type->basic_type->fields, 0);
                      assert(first_field);
                      
                      SPVM_TYPE* field_type = first_field->type;
                      assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      int32_t typed_var_index_out;
                      int32_t typed_var_index_in;
                      switch (field_type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_BYTE_ZERO);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_SHORT_ZERO);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_INT_ZERO);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_LONG_ZERO);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_FLOAT_ZERO);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_DOUBLE_ZERO);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur);
                          break;
                        }
                        default:
                          assert(0);
                      }
                      
                      int32_t fields_length = type->basic_type->fields->length;
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand2 = fields_length;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                    }
                    // Object type
                    else if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_UNDEF);
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur);
                      
                      opcode.operand0 = typed_var_index_out;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                    }
                    // Referece type
                    else if (SPVM_TYPE_is_ref_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_REF_UNDEF);
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur);
                      
                      opcode.operand0 = typed_var_index_out;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                    }
                    // Numeric type
                    else if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      int32_t typed_var_index_out;
                      switch (type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_BYTE_ZERO);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_SHORT_ZERO);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_INT_ZERO);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_LONG_ZERO);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_FLOAT_ZERO);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_DOUBLE_ZERO);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_cur);
                          break;
                        }
                        default: {
                          assert(0);
                        }
                      }

                      opcode.operand0 = typed_var_index_out;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                    }
                    else {
                      // TODO ref type which is not sub arg is invalid
                      // assert(0);
                    }
                  }
                }
                
                break;
              }
              // all operators are assigned to variables by SPVM_CHECK_traverse_ast_assign_unassigned_op_to_var.
              case SPVM_OP_C_ID_ASSIGN: {
                SPVM_OP* op_assign = op_cur;
                
                SPVM_OP* op_assign_dist = op_assign->last;
                SPVM_OP* op_assign_src = op_assign->first;
                
                if (op_assign_src->id == SPVM_OP_C_ID_SEQUENCE) {
                  op_assign_src = op_assign_src->last;
                }
                
                // $var = OPERATOR
                if (op_assign_dist->id == SPVM_OP_C_ID_VAR) {
                  SPVM_TYPE* type_dist = SPVM_CHECK_get_type(compiler, op_assign_dist);
                  
                  switch (op_assign_src->id) {
                    case SPVM_OP_C_ID_STRING_CONCAT: {
                      SPVM_TYPE* first_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                      
                      assert(SPVM_TYPE_is_string_or_byte_array_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag));
                      
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_STRING_CONCAT);
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      int32_t typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      check_exception = 1;
                      
                      break;
                    }
                    case SPVM_OP_C_ID_TYPE_NAME : {
                      
                      SPVM_TYPE* first_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                      
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_NAME);
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);

                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_DUMP : {
                      
                      SPVM_TYPE* first_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                      
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DUMP);
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);

                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_NEW_STRING_LEN : {
                      
                      SPVM_TYPE* first_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                      
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_STRING_LEN);
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      check_exception = 1;
                      
                      break;
                    }
                    case SPVM_OP_C_ID_IS_READ_ONLY : {
                      
                      SPVM_TYPE* first_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                      
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_READ_ONLY);
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_IS_FIXED_LENGTH : {
                      
                      SPVM_TYPE* first_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                      
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_FIXED_LENGTH);
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_IS_OPTIONS : {
                      
                      SPVM_TYPE* first_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                      
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_OPTIONS);
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_UNDEF : {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      if (SPVM_TYPE_is_object_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_UNDEF);
                      }
                      else if (SPVM_TYPE_is_ref_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_REF_UNDEF);
                      }
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      opcode.operand0 = typed_var_index_out;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_CALL_METHOD: {
                      
                      SPVM_CALL_METHOD* call_method = op_assign_src->uv.call_method;
                      const char* call_method_method_name = call_method->method->name;
                      
                      SPVM_METHOD* method_call_method = SPVM_HASH_get(call_method->method->current_basic_type->method_symtable, call_method_method_name, strlen(call_method_method_name));
                      
                      SPVM_OP* op_term_args = op_assign_src->first;
                      SPVM_OP* op_term_arg = op_term_args->first;

                      // Call method
                      SPVM_OPCODE opcode = {0};
                      
                      int32_t opcode_id = -1;
                      if (call_method->is_class_method) {
                        opcode_id = SPVM_OPCODE_C_ID_CALL_CLASS_METHOD;
                      }
                      else {
                        if (call_method->is_instance_method_static) {
                          opcode_id = SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD_STATIC;
                        }
                        else {
                          opcode_id = SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD;
                        }
                      }
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, opcode_id);
                      
                      SPVM_LIST* args = method_call_method->var_decls;
                      int32_t args_type_width = 0;
                      
                      for (int32_t arg_index = 0; arg_index < method_call_method->args_length; arg_index++) {
                        SPVM_VAR_DECL* arg_var_decl = SPVM_LIST_get(args, arg_index);
                        
                        // Argument type
                        SPVM_TYPE* arg_type = arg_var_decl->type;
                        int32_t arg_type_width = SPVM_TYPE_get_type_width(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag);
                        
                        // Term argment type
                        op_term_arg = SPVM_OP_sibling(compiler, op_term_arg);
                        if (!op_term_arg) {
                          break;
                        }
                        
                        SPVM_TYPE* term_arg_type = SPVM_CHECK_get_type(compiler, op_term_arg);
                        
                        SPVM_OPCODE opcode = {0};
                        
                        int32_t stack_index = args_type_width;
                        opcode.operand3 = stack_index;
                        
                        if (SPVM_TYPE_is_undef_type(compiler, term_arg_type->basic_type->id, term_arg_type->dimension, term_arg_type->flag)) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_UNDEF);
                          SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                        }
                        else {
                          if (SPVM_TYPE_is_ref_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_REF);

                            // Term of argument
                            int32_t typed_var_index_arg = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_arg);
                            
                            opcode.operand0 = typed_var_index_arg;
                            
                            SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                          }
                          else if (SPVM_TYPE_is_mulnum_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag)) {

                            SPVM_FIELD* first_field = SPVM_LIST_get(arg_type->basic_type->fields, 0);
                            assert(first_field);
                            
                            SPVM_TYPE* field_type = first_field->type;
                            assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                            
                            int32_t typed_var_index_arg;
                            switch (field_type->basic_type->id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_MULNUM_BYTE);
                                typed_var_index_arg = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_arg);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_MULNUM_SHORT);
                                typed_var_index_arg = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_arg);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_MULNUM_INT);
                                typed_var_index_arg = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_arg);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_MULNUM_LONG);
                                typed_var_index_arg = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_arg);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_MULNUM_FLOAT);
                                typed_var_index_arg = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_arg);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_MULNUM_DOUBLE);
                                typed_var_index_arg = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_arg);
                                break;
                              }
                              default:
                                assert(0);
                            }
                            
                            int32_t fields_length = arg_type->basic_type->fields->length;
                            opcode.operand0 = typed_var_index_arg;
                            opcode.operand1 = fields_length;
                            
                            SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                          }
                          // Object type
                          else if (SPVM_TYPE_is_object_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag)) {
                            
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_OBJECT);
                            int32_t typed_var_index_arg = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_arg);
                            
                            opcode.operand0 = typed_var_index_arg;
                            
                            SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                          }
                          // Numeric type
                          else if (SPVM_TYPE_is_numeric_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag)) {
                            int32_t typed_var_index_arg;
                            switch (arg_type->basic_type->id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_BYTE);
                                typed_var_index_arg = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_arg);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_SHORT);
                                typed_var_index_arg = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_arg);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_INT);
                                typed_var_index_arg = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_arg);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_LONG);
                                typed_var_index_arg = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_arg);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_FLOAT);
                                typed_var_index_arg = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_arg);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_DOUBLE);
                                typed_var_index_arg = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_arg);
                                break;
                              }
                              default:
                                assert(0);
                            }
                            
                            opcode.operand0 = typed_var_index_arg;
                            
                            SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                          }
                          else {
                            assert(0);
                          }
                        }
                        args_type_width += arg_type_width;
                      }
                      
                      int32_t typed_var_index_out;
                      
                      // Return
                      SPVM_TYPE* call_method_return_type = call_method->method->return_type;
                      
                      opcode.operand0 = call_method->method->current_basic_type->id;
                      opcode.operand1 = call_method->method->index;
                      opcode.operand2 = args_type_width;
                      
                      SPVM_OPCODE opcode_get_stack = {0};
                      {
                        typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                        opcode_get_stack.operand0 = typed_var_index_out;

                        // Numeric type
                        if (SPVM_TYPE_is_numeric_type(compiler, call_method_return_type->basic_type->id, call_method_return_type->dimension, call_method_return_type->flag)) {
                          switch (call_method_return_type->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_get_stack, SPVM_OPCODE_C_ID_GET_STACK_BYTE);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_get_stack, SPVM_OPCODE_C_ID_GET_STACK_SHORT);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_get_stack, SPVM_OPCODE_C_ID_GET_STACK_INT);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_get_stack, SPVM_OPCODE_C_ID_GET_STACK_LONG);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_get_stack, SPVM_OPCODE_C_ID_GET_STACK_FLOAT);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_get_stack, SPVM_OPCODE_C_ID_GET_STACK_DOUBLE);
                              break;
                            }
                            default:
                              assert(0);
                          }
                        }
                        // void type
                        else if (SPVM_TYPE_is_void_type(compiler, call_method_return_type->basic_type->id, call_method_return_type->dimension, call_method_return_type->flag)) {
                        }
                        // Object type
                        else if (SPVM_TYPE_is_object_type(compiler, call_method_return_type->basic_type->id, call_method_return_type->dimension, call_method_return_type->flag)) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_get_stack, SPVM_OPCODE_C_ID_GET_STACK_OBJECT);
                        }
                        // Multi numeric type
                        else if (SPVM_TYPE_is_mulnum_type(compiler, call_method_return_type->basic_type->id, call_method_return_type->dimension, call_method_return_type->flag)) {

                          SPVM_FIELD* first_field = SPVM_LIST_get(call_method_return_type->basic_type->fields, 0);
                          assert(first_field);
                          
                          SPVM_TYPE* field_type = first_field->type;
                          assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                          
                          int32_t call_method_return_type_width = SPVM_TYPE_get_type_width(compiler, call_method_return_type->basic_type->id, call_method_return_type->dimension, call_method_return_type->flag);
                          assert(call_method_return_type_width < 0xFFFF);
                          opcode_get_stack.operand3 = call_method_return_type_width << 8 | 0;

                          switch (field_type->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_get_stack, SPVM_OPCODE_C_ID_GET_STACK_MULNUM_BYTE);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_get_stack, SPVM_OPCODE_C_ID_GET_STACK_MULNUM_SHORT);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_get_stack, SPVM_OPCODE_C_ID_GET_STACK_MULNUM_INT);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_get_stack, SPVM_OPCODE_C_ID_GET_STACK_MULNUM_LONG);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_get_stack, SPVM_OPCODE_C_ID_GET_STACK_MULNUM_FLOAT);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_get_stack, SPVM_OPCODE_C_ID_GET_STACK_MULNUM_DOUBLE);
                              break;
                            }
                            default: {
                              assert(0);
                            }
                          }
                        }
                        else {
                          assert(0);
                        }
                      }
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      SPVM_OPCODE_BUILDER_push_opcode_on_exception(compiler, opcode_list, eval_block_stack->length, catch_on_exception_opcode_index_stack, return_on_exception_opcode_index_stack, method->op_method, op_cur->line);
                      
                      if (!SPVM_TYPE_is_void_type(compiler, call_method_return_type->basic_type->id, call_method_return_type->dimension, call_method_return_type->flag)) {
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode_get_stack);
                      }
                      break;
                    }
                    case SPVM_OP_C_ID_STRING_LENGTH : {
                      
                      // String length logic is same as ARRAY_LENGTH opcode
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_STRING_LENGTH);
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_ARRAY_LENGTH : {
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_ARRAY_LENGTH);
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      check_exception = 1;
                      
                      break;
                    }
                    case SPVM_OP_C_ID_CAPACITY : {
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CAPACITY);
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      check_exception = 1;
                      
                      break;
                    }
                    case SPVM_OP_C_ID_ARRAY_FIELD_ACCESS : {
                      
                      // $VAR = $VAR_OBJECT->[INDEX]{NAME}
                      SPVM_OP* op_array_field_access = op_assign_src;
                      SPVM_OP* op_term_invocant = op_array_field_access->first;
                      SPVM_OP* op_term_index = op_array_field_access->last;
                      
                      // Call field
                      SPVM_ARRAY_FIELD_ACCESS* array_field_access = op_array_field_access->uv.array_field_access;
                      
                      SPVM_FIELD* field = array_field_access->field;
                      
                      // Array type
                      SPVM_TYPE* array_type = SPVM_CHECK_get_type(compiler, op_array_field_access->first);
                      SPVM_BASIC_TYPE* array_basic_type = array_type->basic_type;
                      
                      // Element type
                      SPVM_TYPE* element_type = SPVM_CHECK_get_type(compiler, op_array_field_access);

                      SPVM_OPCODE opcode = {0};
                      
                      int32_t typed_var_index_out;
                      switch (element_type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_BYTE);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_SHORT);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_INT);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_LONG);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_FLOAT);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_DOUBLE);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          break;
                        }
                        default: {
                          assert(0);
                        }
                      }
                      
                      // Field absolute name symbol
                      int32_t typed_var_index_invocant = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                      int32_t typed_var_index_index = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_index);
                      
                      int32_t fields_length = array_basic_type->fields->length;
                      int32_t field_offset = field->index;

                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_invocant;
                      opcode.operand2 = typed_var_index_index;
                      int32_t operand3 = (field_offset << 8) + (fields_length - 1);
                      assert(operand3 < 0xFFFF);
                      opcode.operand3 = operand3;

                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);

                      check_exception = 1;
                      
                      break;
                    }
                    case SPVM_OP_C_ID_FIELD_ACCESS : {

                      // Weaken field
                      if (op_assign_src->flag & SPVM_OP_C_FLAG_FIELD_ACCESS_WEAKEN) {
                        SPVM_OPCODE opcode = {0};
                        

                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_WEAKEN_FIELD);
                        
                        SPVM_OP* op_term_invocant = op_assign_src->first;
                        int32_t typed_var_index_invocant = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);

                        SPVM_FIELD* field = op_assign_src->uv.field_access->field;

                        opcode.operand0 = typed_var_index_invocant;
                        opcode.operand2 = field->current_basic_type->id;
                        opcode.operand3 = (uint16_t)field->index;
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);

                        check_exception = 1;
                        
                      }
                      else if (op_assign_src->flag & SPVM_OP_C_FLAG_FIELD_ACCESS_UNWEAKEN) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_UNWEAKEN_FIELD);
                        
                        SPVM_OP* op_term_invocant = op_assign_src->first;
                        int32_t typed_var_index_invocant = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                        
                        SPVM_FIELD* field = op_assign_src->uv.field_access->field;
                        
                        opcode.operand0 = typed_var_index_invocant;
                        opcode.operand2 = field->current_basic_type->id;
                        opcode.operand3 = (uint16_t)field->index;
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                        
                        check_exception = 1;
                        
                      }
                      else if (op_assign_src->flag & SPVM_OP_C_FLAG_FIELD_ACCESS_ISWEAK) {
                        SPVM_OPCODE opcode = {0};
                        
                        int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_ISWEAK_FIELD);
                        
                        SPVM_OP* op_term_invocant = op_assign_src->first;
                        int32_t typed_var_index_invocant = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                        
                        SPVM_FIELD* field = op_assign_src->uv.field_access->field;
                        
                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_invocant;
                        opcode.operand2 = field->current_basic_type->id;
                        opcode.operand3 = (uint16_t)field->index;
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                        
                        check_exception = 1;
                        
                      }
                      else if (op_assign_src->flag & SPVM_OP_C_FLAG_FIELD_ACCESS_EXISTS) {
                        SPVM_OPCODE opcode = {0};
                        
                        int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_EXISTS);
                        
                        SPVM_OP* op_term_invocant = op_assign_src->first;
                        int32_t typed_var_index_invocant = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                        
                        SPVM_FIELD* field = op_assign_src->uv.field_access->field;
                        
                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_invocant;
                        opcode.operand2 = field->current_basic_type->id;
                        opcode.operand3 = (uint16_t)field->index;
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                        
                        check_exception = 1;
                        
                      }
                      else if (op_assign_src->flag & SPVM_OP_C_FLAG_FIELD_ACCESS_DELETE) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DELETE);
                        
                        SPVM_OP* op_term_invocant = op_assign_src->first;
                        int32_t typed_var_index_invocant = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                        
                        SPVM_FIELD* field = op_assign_src->uv.field_access->field;
                        
                        opcode.operand0 = typed_var_index_invocant;
                        opcode.operand2 = field->current_basic_type->id;
                        opcode.operand3 = (uint16_t)field->index;
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                        
                        check_exception = 1;
                        
                      }
                      else {
                        SPVM_OP* op_field_access = op_assign_src;
                        SPVM_OP* op_term_invocant = op_field_access->first;
                        
                        SPVM_FIELD_ACCESS* field_access = op_field_access->uv.field_access;
                        
                        SPVM_TYPE* field_type = SPVM_CHECK_get_type(compiler, op_field_access);
                        
                        SPVM_TYPE* invocant_type = SPVM_CHECK_get_type(compiler, op_term_invocant);
                        
                        if (SPVM_TYPE_is_mulnum_ref_type(compiler, invocant_type->basic_type->id, invocant_type->dimension, invocant_type->flag)) {
                          SPVM_FIELD* field = field_access->field;
                          
                          SPVM_OPCODE opcode = {0};
                          
                          int32_t typed_var_index_out;
                          switch (field_type->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_BYTE);
                              typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_SHORT);
                              typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_INT);
                              typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_LONG);
                              typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_FLOAT);
                              typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_DOUBLE);
                              typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                              break;
                            }
                            default: {
                              assert(0);
                            }
                          }
                          
                          int32_t typed_var_index_invocant = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                          int32_t field_offset = field->index;

                          opcode.operand0 = typed_var_index_out;
                          opcode.operand1 = typed_var_index_invocant;
                          opcode.operand2 = field_offset;

                          SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                          
                          check_exception = 1;
                          
                        }
                        // Mulnum field access
                        else if (SPVM_TYPE_is_mulnum_type(compiler, invocant_type->basic_type->id, invocant_type->dimension, invocant_type->flag)) {
                          SPVM_OPCODE opcode = {0};
                          
                          
                          int32_t typed_var_index_out;
                          int32_t typed_var_index_in;
                          switch (field_type->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_BYTE);
                              typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                              typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_SHORT);
                              typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                              typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_INT);
                              typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                              typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_LONG);
                              typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                              typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_FLOAT);
                              typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                              typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DOUBLE);
                              typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                              typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                              break;
                            }
                            default: {
                              assert(0);
                            }
                          }

                          SPVM_FIELD* field = field_access->field;
                          
                          opcode.operand0 = typed_var_index_out;
                          opcode.operand1 = typed_var_index_in;
                          opcode.operand2 = field->index;

                          SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                        }
                        // Field access
                        else {
                          SPVM_OPCODE opcode = {0};
                          
                          int32_t typed_var_index_invocant = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                          int32_t typed_var_index_out;
                          if (SPVM_TYPE_is_object_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_OBJECT);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          }
                          else {
                            switch (field_type->basic_type->id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_BYTE);
                                typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_SHORT);
                                typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_INT);
                                typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_LONG);
                                typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_FLOAT);
                                typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE);
                                typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                                break;
                              }
                              default: {
                                assert(0);
                              }
                            }
                          }

                          SPVM_FIELD* field = field_access->field;
                          
                          opcode.operand0 = typed_var_index_out;
                          opcode.operand1 = typed_var_index_invocant;
                          opcode.operand2 = field->current_basic_type->id;
                          opcode.operand3 = (uint16_t)field->index;

                          SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);

                          check_exception = 1;
                          
                        }
                      }
                      break;
                    }
                    case SPVM_OP_C_ID_ARRAY_ELEMENT_ACCESS : {
                      
                      // $VAR = $VAR_ARRAY->[$VAR_INDEX]
                      SPVM_OP* op_element_access = op_assign_src;
                      SPVM_OP* op_term_array = op_element_access->first;
                      SPVM_OP* op_term_index = op_element_access->last;
                      
                      SPVM_TYPE* array_type = SPVM_CHECK_get_type(compiler, op_term_array);

                      if (SPVM_TYPE_is_mulnum_array_type(compiler, array_type->basic_type->id, array_type->dimension, array_type->flag)) {
                        SPVM_FIELD* first_field = SPVM_LIST_get(array_type->basic_type->fields, 0);
                        
                        SPVM_TYPE* element_type = first_field->type;
                        
                        SPVM_OPCODE opcode = {0};
                        
                        assert(SPVM_TYPE_is_numeric_type(compiler, element_type->basic_type->id, element_type->dimension, element_type->flag));
                        int32_t typed_var_index_out;
                        switch (element_type->basic_type->id) {
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_BYTE);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_SHORT);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_INT);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_LONG);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FLOAT);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_DOUBLE);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          }
                          default: {
                            assert(0);
                          }
                        }
                        int32_t typed_var_index_array = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_array);
                        int32_t typed_var_index_index = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_index);
                        int32_t fields_length = array_type->basic_type->fields->length;

                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_array;
                        opcode.operand2 = typed_var_index_index;
                        int32_t operand3 = fields_length;
                        assert(operand3 < 0xFFFF);
                        opcode.operand3 = operand3;

                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);

                        check_exception = 1;
                        
                      }
                      else {
                        SPVM_TYPE* element_type = SPVM_CHECK_get_type(compiler, op_element_access);
                      
                        SPVM_OPCODE opcode = {0};
                        
                        int32_t typed_var_index_out;
                        if (SPVM_TYPE_is_object_type(compiler, element_type->basic_type->id, element_type->dimension, element_type->flag)) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_OBJECT);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                        }
                        else {
                          switch (element_type->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_BYTE);
                              typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_SHORT);
                              typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_INT);
                              typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_LONG);
                              typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_FLOAT);
                              typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_DOUBLE);
                              typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                              break;
                            }
                            default: {
                              assert(0);
                            }
                          }
                        }

                        int32_t typed_var_index_array = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_array);
                        int32_t typed_var_index_index = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_index);

                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_array;
                        opcode.operand2 = typed_var_index_index;

                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);

                        check_exception = 1;
                        
                      }
                      break;
                    }
                    case SPVM_OP_C_ID_CLASS_VAR_ACCESS : {
                      SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, op_assign_src);
                      
                      SPVM_CLASS_VAR_ACCESS* class_var_access = op_assign_src->uv.class_var_access;
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      int32_t typed_var_index_out;
                      if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_OBJECT);
                        typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      }
                      else {
                        switch (type->basic_type->id) {
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_BYTE);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_SHORT);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_INT);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_LONG);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_FLOAT);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_DOUBLE);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          }
                          default: {
                            assert(0);
                          }
                        }
                      }
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = class_var_access->class_var->current_basic_type->id;
                      opcode.operand2 = class_var_access->class_var->index;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_DEREFERENCE : {
                      SPVM_TYPE* src_type = SPVM_CHECK_get_type(compiler, op_assign_src);
                      
                      if (SPVM_TYPE_is_mulnum_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                        SPVM_FIELD* first_field = SPVM_LIST_get(src_type->basic_type->fields, 0);
                      
                        SPVM_TYPE* element_type = first_field->type;

                        SPVM_OPCODE opcode = {0};
                        
                        
                        assert(SPVM_TYPE_is_numeric_type(compiler, element_type->basic_type->id, element_type->dimension, element_type->flag));
                        int32_t typed_var_index_out;
                        if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DEREF_MULNUM_BYTE);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DEREF_MULNUM_SHORT);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DEREF_MULNUM_INT);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DEREF_MULNUM_LONG);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DEREF_MULNUM_FLOAT);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DEREF_MULNUM_DOUBLE);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                        }
                        else {
                          assert(0);
                        }

                        int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        int32_t fields_length = src_type->basic_type->fields->length;
                        
                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_in;
                        int32_t operand3 = fields_length;
                        assert(operand3 < 0xFFFF);
                        opcode.operand3 = operand3;

                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                        
                        check_exception = 1;
                        
                      }
                      else if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {

                        SPVM_OPCODE opcode = {0};
                        
                        
                        int32_t typed_var_index_out;
                        switch (src_type->basic_type->id) {
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_DEREF_BYTE);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_DEREF_SHORT);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_DEREF_INT);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_DEREF_LONG);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_DEREF_FLOAT);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_DEREF_DOUBLE);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          }
                          default: {
                            assert(0);
                          }
                        }
                        
                        int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        
                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_in;
                        
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                        
                        check_exception = 1;
                        
                      }
                      else {
                        assert(0);
                      }
                      break;
                    }
                    case SPVM_OP_C_ID_REFERENCE : {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in;
                      SPVM_TYPE* src_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                      if (SPVM_TYPE_is_mulnum_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                        
                        SPVM_FIELD* first_field = SPVM_LIST_get(src_type->basic_type->fields, 0);
                        assert(first_field);
                        
                        SPVM_TYPE* field_type = first_field->type;
                        assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                        
                        switch (field_type->basic_type->id) {
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_BYTE);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_SHORT);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_INT);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_LONG);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_FLOAT);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_DOUBLE);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          default:
                            assert(0);
                        }
                      }
                      else if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                        switch (src_type->basic_type->id) {
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_BYTE);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_SHORT);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_INT);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_LONG);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_FLOAT);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_DOUBLE);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          default:
                            assert(0);
                        }
                      }
                      else {
                        assert(0);
                      }
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_EXCEPTION_VAR : {
                      // VAR = EXCEPTION_VAR
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_EXCEPTION_VAR);

                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      
                      opcode.operand0 = typed_var_index_out;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_ADD : {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));

                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_ADD_INT);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_ADD_LONG);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_ADD_FLOAT);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_ADD_DOUBLE);
                          break;
                        default:
                          assert(0);
                      }
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      int32_t typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;

                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_SUBTRACT : {

                      SPVM_OPCODE opcode = {0};
                      

                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SUBTRACT_INT);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SUBTRACT_LONG);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SUBTRACT_FLOAT);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SUBTRACT_DOUBLE);
                          break;
                        default:
                          assert(0);
                      }

                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      int32_t typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;

                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_MULTIPLY : {

                      SPVM_OPCODE opcode = {0};
                      

                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MULTIPLY_INT);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MULTIPLY_LONG);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MULTIPLY_FLOAT);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MULTIPLY_DOUBLE);
                          break;
                        default:
                          assert(0);
                      }

                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      int32_t typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;

                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_DIVIDE : {

                      SPVM_OPCODE opcode = {0};
                      
                      
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DIVIDE_INT);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DIVIDE_LONG);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DIVIDE_FLOAT);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DIVIDE_DOUBLE);
                          break;
                        default:
                          assert(0);
                      }

                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      int32_t typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      // Check die
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          check_exception = 1;
                        
                        break;
                      }
                      
                      break;
                    }
                    case SPVM_OP_C_ID_DIVIDE_UNSIGNED_INT : {

                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DIVIDE_UNSIGNED_INT);

                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      int32_t typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      check_exception = 1;
                        
                      break;
                    }
                    case SPVM_OP_C_ID_DIVIDE_UNSIGNED_LONG : {

                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DIVIDE_UNSIGNED_LONG);

                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      int32_t typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      check_exception = 1;
                      
                      
                      break;
                    }
                    case SPVM_OP_C_ID_MODULO : {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t typed_var_index_out;
                      int32_t typed_var_index_in1;
                      int32_t typed_var_index_in2;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MODULO_INT);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MODULO_LONG);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        default:
                          assert(0);
                      }
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;

                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);

                      // Check die
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                        {
                          check_exception = 1;
                          
                          break;
                        }
                      }
                      break;
                    }
                    case SPVM_OP_C_ID_MODULO_UNSIGNED_INT : {

                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MODULO_UNSIGNED_INT);

                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      int32_t typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      check_exception = 1;
                      
                      break;
                    }
                    case SPVM_OP_C_ID_MODULO_UNSIGNED_LONG : {

                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MODULO_UNSIGNED_LONG);

                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      int32_t typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      check_exception = 1;
                      
                      break;
                    }
                    case SPVM_OP_C_ID_LEFT_SHIFT : {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t typed_var_index_in1;
                      int32_t typed_var_index_out;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LEFT_SHIFT_INT);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LEFT_SHIFT_LONG);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          break;
                        default:
                          assert(0);
                      }

                      int32_t typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;

                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_RIGHT_ARITHMETIC_SHIFT : {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t typed_var_index_in1;
                      int32_t typed_var_index_out;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_INT);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_LONG);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          break;
                        default:
                          assert(0);
                      }

                      int32_t typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;

                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_RIGHT_LOGICAL_SHIFT : {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t typed_var_index_out;
                      int32_t typed_var_index_in1;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_INT);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_LONG);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          break;
                        default:
                          assert(0);
                      }

                      int32_t typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;

                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_BIT_AND : {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t typed_var_index_out;
                      int32_t typed_var_index_in1;
                      int32_t typed_var_index_in2;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_AND_INT);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_AND_LONG);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        default:
                          assert(0);
                      }

                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;

                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_BIT_OR : {

                      SPVM_OPCODE opcode = {0};
                      
                      
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t typed_var_index_out;
                      int32_t typed_var_index_in1;
                      int32_t typed_var_index_in2;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_OR_INT);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_OR_LONG);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        default:
                          assert(0);
                      }

                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;

                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_BIT_XOR : {

                      SPVM_OPCODE opcode = {0};
                      
                      
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t typed_var_index_out;
                      int32_t typed_var_index_in1;
                      int32_t typed_var_index_in2;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_XOR_INT);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_XOR_LONG);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        default:
                          assert(0);
                      }

                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;

                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_BIT_NOT : {

                      SPVM_OPCODE opcode = {0};
                      

                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t typed_var_index_out;
                      int32_t typed_var_index_in;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_NOT_INT);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_NOT_LONG);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          break;
                        default:
                          assert(0);
                      }
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_PLUS : {

                      SPVM_OPCODE opcode = {0};
                      
                     
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t typed_var_index_out;
                      int32_t typed_var_index_in;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_INT);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_LONG);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_FLOAT);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_DOUBLE);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          break;
                        default:
                          assert(0);
                      }
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_COPY : {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_COPY);
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_ADDRESS : {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                      int32_t is_ref_type = SPVM_TYPE_is_ref_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag);
                      
                      if (is_ref_type) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ADDRESS_REF);
                      }
                      else {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ADDRESS_OBJECT);
                      }
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_MINUS : {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t typed_var_index_out;
                      int32_t typed_var_index_in;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEGATE_INT);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEGATE_LONG);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEGATE_FLOAT);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEGATE_DOUBLE);
                          typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          break;
                        default:
                          assert(0);
                      }
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_CONSTANT : {
                      SPVM_CONSTANT* constant = op_assign_src->uv.constant;

                      if (SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        

                        int32_t typed_var_index_out;
                        switch (type_dist->basic_type->id) {
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_CONSTANT_BYTE);
                            opcode.operand1 = (uint16_t)(uint8_t)constant->value.bval;
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_CONSTANT_INT);
                            opcode.operand1 = (uint32_t)constant->value.ival;
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_CONSTANT_LONG);
                            *(int64_t*)&opcode.operand1 = constant->value.lval;
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_CONSTANT_FLOAT);
                            opcode.operand1 = (uint32_t)constant->value.ival;
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_CONSTANT_DOUBLE);
                            *(double*)&opcode.operand1 = constant->value.dval;
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            break;
                          default:
                            assert(0);
                        }
                        
                        opcode.operand0 = typed_var_index_out;
                       
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      }
                      else if (SPVM_TYPE_is_string_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)
                        || SPVM_TYPE_is_object_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_STRING);
                        
                        int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                        SPVM_CONSTANT* constant = op_assign_src->uv.constant;
                        
                        const char* constant_string_value = constant->value.oval;
                        int32_t constant_string_length = constant->string_length;
                        
                        opcode.operand0 = typed_var_index_out;
                        
                        SPVM_STRING* constant_string = SPVM_HASH_get(basic_type->constant_string_symtable, constant_string_value, constant_string_length);
                        assert(constant_string);
                        
                        assert(constant_string->index >= 0);
                        opcode.operand1 = constant_string->index;
                        
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      }
                      else {
                        assert(0);
                      }
                      break;
                    }
                    case SPVM_OP_C_ID_TYPE_CAST : {
                      
                      SPVM_OP* op_dist_term = op_assign_dist;
                      SPVM_OP* op_src_term = op_assign_src->first;
                      SPVM_OP* op_cast_type = op_assign_src->last;
                      
                      SPVM_TYPE* src_type = SPVM_CHECK_get_type(compiler, op_src_term);
                      SPVM_TYPE* cast_type = SPVM_CHECK_get_type(compiler, op_cast_type);

                      // Source is undef type
                      if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                        SPVM_OPCODE opcode = {0};
                        if (SPVM_TYPE_is_object_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_UNDEF);
                          
                          int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_dist_term);
                          opcode.operand0 = typed_var_index_out;
                          
                          SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                        }
                        else if (SPVM_TYPE_is_ref_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_REF_UNDEF);
                          
                          int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_dist_term);
                          opcode.operand0 = typed_var_index_out;
                          
                          SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                        }
                        else {
                          assert(0);
                        }
                      }
                      else {
                        SPVM_OPCODE opcode = {0};
                        int32_t typed_var_index_out;
                        int32_t typed_var_index_in;

                        typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_dist_term);
                        typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_src_term);
                        
                        // To byte
                        if (SPVM_TYPE_is_byte_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          if (SPVM_TYPE_is_byte_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_BYTE);
                          }
                          else if (SPVM_TYPE_is_short_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_BYTE);
                          }
                          else if (SPVM_TYPE_is_int_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_BYTE);
                          }
                          else if (SPVM_TYPE_is_long_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_BYTE);
                          }
                          else if (SPVM_TYPE_is_float_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_BYTE);
                          }
                          else if (SPVM_TYPE_is_double_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_BYTE);
                          }
                          else if (SPVM_TYPE_is_byte_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_OBJECT_TO_BYTE);
                            check_exception = 1;
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_OBJECT_TO_BYTE);
                            check_exception = 1;
                          }
                          else if (SPVM_TYPE_is_string_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_STRING_TO_BYTE);
                          }
                          else {
                            assert(0);
                          }
                        }
                        // To short
                        else if (SPVM_TYPE_is_short_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          if (SPVM_TYPE_is_byte_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_SHORT);
                          }
                          else if (SPVM_TYPE_is_short_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_SHORT);
                          }
                          else if (SPVM_TYPE_is_int_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_SHORT);
                          }
                          else if (SPVM_TYPE_is_long_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_SHORT);
                          }
                          else if (SPVM_TYPE_is_float_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_SHORT);
                          }
                          else if (SPVM_TYPE_is_double_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_SHORT);
                          }
                          else if (SPVM_TYPE_is_short_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_OBJECT_TO_SHORT);
                            check_exception = 1;
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_OBJECT_TO_SHORT);
                            check_exception = 1;
                          }
                          else if (SPVM_TYPE_is_string_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_STRING_TO_SHORT);
                          }
                          else {
                            assert(0);
                          }
                        }
                        // To int
                        else if (SPVM_TYPE_is_int_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          if (SPVM_TYPE_is_byte_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_INT);
                          }
                          else if (SPVM_TYPE_is_short_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_INT);
                          }
                          else if (SPVM_TYPE_is_int_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_INT);
                          }
                          else if (SPVM_TYPE_is_long_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_INT);
                          }
                          else if (SPVM_TYPE_is_float_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_INT);
                          }
                          else if (SPVM_TYPE_is_double_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_INT);
                          }
                          else if (SPVM_TYPE_is_int_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_OBJECT_TO_INT);
                            check_exception = 1;
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_OBJECT_TO_INT);
                            check_exception = 1;
                          }
                          else if (SPVM_TYPE_is_string_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_STRING_TO_INT);
                          }
                          else {
                            assert(0);
                          }
                        }
                        // To long
                        else if (SPVM_TYPE_is_long_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          if (SPVM_TYPE_is_byte_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_LONG);
                          }
                          else if (SPVM_TYPE_is_short_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_LONG);
                          }
                          else if (SPVM_TYPE_is_int_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_LONG);
                          }
                          else if (SPVM_TYPE_is_long_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_LONG);
                          }
                          else if (SPVM_TYPE_is_float_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_LONG);
                          }
                          else if (SPVM_TYPE_is_double_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_LONG);
                          }
                          else if (SPVM_TYPE_is_long_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_OBJECT_TO_LONG);
                            check_exception = 1;
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_OBJECT_TO_LONG);
                            check_exception = 1;
                          }
                          else if (SPVM_TYPE_is_string_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_STRING_TO_LONG);
                          }
                          else {
                            assert(0);
                          }
                        }
                        // To float
                        else if (SPVM_TYPE_is_float_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          if (SPVM_TYPE_is_byte_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_FLOAT);
                          }
                          else if (SPVM_TYPE_is_short_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_FLOAT);
                          }
                          else if (SPVM_TYPE_is_int_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_FLOAT);
                          }
                          else if (SPVM_TYPE_is_long_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_FLOAT);
                          }
                          else if (SPVM_TYPE_is_float_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_FLOAT);
                          }
                          else if (SPVM_TYPE_is_double_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_FLOAT);
                          }
                          else if (SPVM_TYPE_is_float_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_OBJECT_TO_FLOAT);
                            check_exception = 1;
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_OBJECT_TO_FLOAT);
                            check_exception = 1;
                          }
                          else if (SPVM_TYPE_is_string_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_STRING_TO_FLOAT);
                          }
                          else {
                            assert(0);
                          }
                        }
                        // To double
                        else if (SPVM_TYPE_is_double_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          if (SPVM_TYPE_is_byte_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_DOUBLE);
                          }
                          else if (SPVM_TYPE_is_short_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_DOUBLE);
                          }
                          else if (SPVM_TYPE_is_int_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_DOUBLE);
                          }
                          else if (SPVM_TYPE_is_long_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_DOUBLE);
                          }
                          else if (SPVM_TYPE_is_float_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_DOUBLE);
                          }
                          else if (SPVM_TYPE_is_double_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_DOUBLE);
                          }
                          else if (SPVM_TYPE_is_double_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_OBJECT_TO_DOUBLE);
                            check_exception = 1;
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_OBJECT_TO_DOUBLE);
                            check_exception = 1;
                          }
                          else if (SPVM_TYPE_is_string_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_STRING_TO_DOUBLE);
                          }
                          else {
                            assert(0);
                          }
                        }
                        // To mulnum
                        else if (SPVM_TYPE_is_mulnum_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          // Not yet implemented
                          assert(0);
                        }
                        // To Byte object
                        else if (SPVM_TYPE_is_byte_object_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          if (SPVM_TYPE_is_byte_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                          }
                          else if (SPVM_TYPE_is_byte_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_BYTE_OBJECT);
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECK);
                            opcode.operand2 = op_cast_type->uv.type->basic_type->id;
                            int32_t operand3 = op_cast_type->uv.type->dimension;
                            assert(operand3 < 0xFFFF);
                            opcode.operand3 = operand3;
                            check_exception = 1;
                          }
                          else {
                            assert(0);
                          }
                        }
                        // To Short object
                        else if (SPVM_TYPE_is_short_object_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          if (SPVM_TYPE_is_short_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                          }
                          else if (SPVM_TYPE_is_short_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_SHORT_OBJECT);
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECK);
                            opcode.operand2 = op_cast_type->uv.type->basic_type->id;
                            int32_t operand3 = op_cast_type->uv.type->dimension;
                            assert(operand3 < 0xFFFF);
                            opcode.operand3 = operand3;
                            check_exception = 1;
                          }
                          else {
                            assert(0);
                          }
                        }
                        // To Int object
                        else if (SPVM_TYPE_is_int_object_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          if (SPVM_TYPE_is_int_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                          }
                          else if (SPVM_TYPE_is_int_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_INT_OBJECT);
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECK);
                            opcode.operand2 = op_cast_type->uv.type->basic_type->id;
                            int32_t operand3 = op_cast_type->uv.type->dimension;
                            assert(operand3 < 0xFFFF);
                            opcode.operand3 = operand3;
                            check_exception = 1;
                          }
                          else {
                            assert(0);
                          }
                        }
                        // To Long object
                        else if (SPVM_TYPE_is_long_object_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          if (SPVM_TYPE_is_long_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                          }
                          else if (SPVM_TYPE_is_long_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_LONG_OBJECT);
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECK);
                            opcode.operand2 = op_cast_type->uv.type->basic_type->id;
                            int32_t operand3 = op_cast_type->uv.type->dimension;
                            assert(operand3 < 0xFFFF);
                            opcode.operand3 = operand3;
                            check_exception = 1;
                          }
                          else {
                            assert(0);
                          }
                        }
                        // To Float object
                        else if (SPVM_TYPE_is_float_object_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          if (SPVM_TYPE_is_float_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                          }
                          else if (SPVM_TYPE_is_float_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_FLOAT_OBJECT);
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECK);
                            opcode.operand2 = op_cast_type->uv.type->basic_type->id;
                            int32_t operand3 = op_cast_type->uv.type->dimension;
                            assert(operand3 < 0xFFFF);
                            opcode.operand3 = operand3;
                            check_exception = 1;
                          }
                          else {
                            assert(0);
                          }
                        }
                        // To Double object
                        else if (SPVM_TYPE_is_double_object_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          if (SPVM_TYPE_is_double_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                          }
                          else if (SPVM_TYPE_is_double_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_DOUBLE_OBJECT);
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECK);
                            opcode.operand2 = op_cast_type->uv.type->basic_type->id;
                            int32_t operand3 = op_cast_type->uv.type->dimension;
                            assert(operand3 < 0xFFFF);
                            opcode.operand3 = operand3;
                            check_exception = 1;
                          }
                          else {
                            assert(0);
                          }
                        }
                        // To String
                        else if (SPVM_TYPE_is_string_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          if (SPVM_TYPE_is_string_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            if (cast_type->flag & SPVM_NATIVE_C_TYPE_FLAG_MUTABLE && !(src_type->flag & SPVM_NATIVE_C_TYPE_FLAG_MUTABLE)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_CHECK_READ_ONLY_STRING);
                              check_exception = 1;
                            }
                            else {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                            }
                          }
                          else if (SPVM_TYPE_is_byte_array_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_ARRAY_TO_STRING);
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            if (cast_type->flag & SPVM_NATIVE_C_TYPE_FLAG_MUTABLE) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_CHECK_READ_ONLY_STRING);
                              check_exception = 1;
                            }
                            else {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECK);
                              opcode.operand2 = op_cast_type->uv.type->basic_type->id;
                              int32_t operand3 = op_cast_type->uv.type->dimension;
                              assert(operand3 < 0xFFFF);
                              opcode.operand3 = operand3;
                              check_exception = 1;
                            }
                          }
                          else if (SPVM_TYPE_is_byte_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_STRING);
                          }
                          else if (SPVM_TYPE_is_short_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_STRING);
                          }
                          else if (SPVM_TYPE_is_int_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_STRING);
                          }
                          else if (SPVM_TYPE_is_long_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_STRING);
                          }
                          else if (SPVM_TYPE_is_float_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_STRING);
                          }
                          else if (SPVM_TYPE_is_double_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_STRING);
                          }
                          else {
                            assert(0);
                          }
                        }
                        // To byte[]
                        else if (SPVM_TYPE_is_byte_array_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          if (SPVM_TYPE_is_byte_array_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                          }
                          else if (SPVM_TYPE_is_string_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_STRING_TO_BYTE_ARRAY);
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECK);
                            opcode.operand2 = op_cast_type->uv.type->basic_type->id;
                            int32_t operand3 = op_cast_type->uv.type->dimension;
                            assert(operand3 < 0xFFFF);
                            opcode.operand3 = operand3;
                            check_exception = 1;
                          }
                          else {
                            assert(0);
                          }
                        }
                        // To any object
                        else if (SPVM_TYPE_is_any_object_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          if (SPVM_TYPE_is_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                          }
                          else if (SPVM_TYPE_is_byte_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_BYTE_OBJECT);
                          }
                          else if (SPVM_TYPE_is_short_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_SHORT_OBJECT);
                          }
                          else if (SPVM_TYPE_is_int_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_INT_OBJECT);
                          }
                          else if (SPVM_TYPE_is_long_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_LONG_OBJECT);
                          }
                          else if (SPVM_TYPE_is_float_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_FLOAT_OBJECT);
                          }
                          else if (SPVM_TYPE_is_double_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_DOUBLE_OBJECT);
                          }
                          else {
                            assert(0);
                          }
                        }
                        // To object type
                        else if (SPVM_TYPE_is_object_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          if (SPVM_TYPE_is_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            int32_t cast_type_basic_type_id = op_cast_type->uv.type->basic_type->id;
                            int32_t cast_type_dimension = op_cast_type->uv.type->dimension;
                            int32_t cast_type_flag = op_cast_type->uv.type->flag;
                            
                            int32_t src_type_basic_type_id = src_type->basic_type->id;
                            int32_t src_type_dimension = src_type->dimension;
                            int32_t src_type_flag = src_type->flag;
                            
                            int32_t satisfy_assignment_requirement_without_data_conversion = SPVM_TYPE_satisfy_assignment_requirement_without_data_conversion(
                              compiler,
                              cast_type_basic_type_id, cast_type_dimension, cast_type_flag,
                              src_type_basic_type_id, src_type_dimension, src_type_flag,
                              NULL
                            );
                            
                            if (satisfy_assignment_requirement_without_data_conversion) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                            }
                            else {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECK);
                              opcode.operand2 = op_cast_type->uv.type->basic_type->id;
                              int32_t operand3 = op_cast_type->uv.type->dimension;
                              assert(operand3 < 0xFFFF);
                              opcode.operand3 = operand3;
                              check_exception = 1;
                            }
                          }
                          else {
                            assert(0);
                          }
                        }
                        
                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_in;
                        
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      }
                      
                      break;
                    }
                    case SPVM_OP_C_ID_NEW : {
                      
                      if (op_assign_src->first->id == SPVM_OP_C_ID_TYPE || op_assign_src->first->id == SPVM_OP_C_ID_VAR) {
                        
                        SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, op_assign_src);
                        
                        // Runtime type
                        int32_t basic_type_id = type->basic_type->id;
                        int32_t type_dimension = type->dimension;
                        
                        if (type_dimension > 0) {
                          /*
                            NEW op_assign_src
                               TYPE op_assign_src->first
                                 ELEMENT_TYPE op_assign_src->first->first
                                 INDEX op_assign_src->last
                          */
                          
                          if (type_dimension == 1) {
                            switch (basic_type_id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                SPVM_OPCODE opcode = {0};
                                
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_BYTE_ARRAY);

                                int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                                int32_t typed_var_index_index = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);

                                opcode.operand0 = typed_var_index_out;
                                opcode.operand1 = typed_var_index_index;

                                SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);

                                check_exception = 1;
                                
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                SPVM_OPCODE opcode = {0};
                                
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY);

                                int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                                int32_t typed_var_index_index = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                                
                                opcode.operand0 = typed_var_index_out;
                                opcode.operand1 = typed_var_index_index;

                                SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);

                                check_exception = 1;
                                
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                SPVM_OPCODE opcode = {0};
                                

                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_INT_ARRAY);

                                int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                                int32_t typed_var_index_index = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);

                                opcode.operand0 = typed_var_index_out;
                                opcode.operand1 = typed_var_index_index;

                                SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);

                                check_exception = 1;
                                
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                SPVM_OPCODE opcode = {0};
                                

                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_LONG_ARRAY);

                                int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                                int32_t typed_var_index_index = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);

                                opcode.operand0 = typed_var_index_out;
                                opcode.operand1 = typed_var_index_index;

                                SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                                
                                check_exception = 1;
                                
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                SPVM_OPCODE opcode = {0};
                                

                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY);

                                int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                                int32_t typed_var_index_index = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);

                                opcode.operand0 = typed_var_index_out;
                                opcode.operand1 = typed_var_index_index;

                                SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                                
                                check_exception = 1;
                                
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                SPVM_OPCODE opcode = {0};
                                

                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY);
                                
                                int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                                int32_t typed_var_index_index = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);

                                opcode.operand0 = typed_var_index_out;
                                opcode.operand1 = typed_var_index_index;

                                SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);

                                check_exception = 1;
                                
                                break;
                              }
                              default: {
                                if (SPVM_TYPE_is_mulnum_array_type(compiler, basic_type_id, type_dimension, type->flag)) {
                                  SPVM_OPCODE opcode = {0};
                                  

                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_MULNUM_ARRAY);

                                  int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                                  int32_t typed_var_index_index = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);

                                  opcode.operand0 = typed_var_index_out;
                                  opcode.operand1 = type->basic_type->id;
                                  opcode.operand2 = typed_var_index_index;

                                  SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);

                                  check_exception = 1;
                                  
                                }
                                else {
                                  SPVM_OPCODE opcode = {0};
                                  

                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY);

                                  int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                                  int32_t typed_var_index_index = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);

                                  opcode.operand0 = typed_var_index_out;
                                  opcode.operand1 = type->basic_type->id;
                                  opcode.operand2 = typed_var_index_index;

                                  SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);

                                  check_exception = 1;
                                  
                                }
                              }
                            }
                          }
                          else if (type_dimension > 1) {
                            SPVM_OPCODE opcode = {0};
                            

                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_MULDIM_ARRAY);

                            int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            int32_t typed_var_index_index = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);

                            opcode.operand0 = typed_var_index_out;
                            opcode.operand1 = type->basic_type->id;
                            opcode.operand2 = typed_var_index_index;
                            int32_t operand3 = type->dimension;
                            assert(operand3 < 0xFFFF);
                            opcode.operand3 = operand3;

                            SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);

                            check_exception = 1;
                          }
                          else {
                            assert(0);
                          }
                        }
                        else {
                          SPVM_OPCODE opcode = {0};
                          

                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_OBJECT);
                          
                          int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          
                          opcode.operand0 = typed_var_index_out;
                          opcode.operand1 = type->basic_type->id;
                          SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                        }
                      }
                      else {
                        assert(0);
                      }
                      
                      break;
                    }
                    case SPVM_OP_C_ID_BASIC_TYPE_ID : {
                      
                      SPVM_OP* op_type = op_assign_src->first;
                      
                      int32_t basic_type_id = op_type->uv.type->basic_type->id;
                      
                      SPVM_OPCODE opcode = {0};
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_BASIC_TYPE_ID);
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = basic_type_id;
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);

                      check_exception = 1;
                      
                      break;
                    }
                    case SPVM_OP_C_ID_EVAL_ERROR_ID : {
                      
                      SPVM_OPCODE opcode = {0};
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_EVAL_ERROR_ID);
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      opcode.operand0 = typed_var_index_out;
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_ARGS_WIDTH : {
                      
                      SPVM_OPCODE opcode = {0};
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_ARGS_WIDTH);
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      opcode.operand0 = typed_var_index_out;
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_VAR : {
                      // Multi numeric type
                      if (SPVM_TYPE_is_mulnum_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        
                        SPVM_FIELD* first_field = SPVM_LIST_get(type_dist->basic_type->fields, 0);
                        assert(first_field);
                        
                        SPVM_TYPE* field_type = first_field->type;
                        assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                        
                        SPVM_OPCODE opcode = {0};
                        
                        
                        int32_t typed_var_index_out;
                        int32_t typed_var_index_in;
                        switch (field_type->basic_type->id) {
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_BYTE);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_SHORT);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_INT);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_LONG);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_FLOAT);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_DOUBLE);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          }
                          default:
                            assert(0);
                        }

                        int32_t fields_length = type_dist->basic_type->fields->length;
                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_in;
                        opcode.operand2 = fields_length;
                        
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      }
                      // Object type
                      else if (SPVM_TYPE_is_object_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                        int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                        int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);

                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_in;
                        
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                        
                      }
                      else if (SPVM_TYPE_is_ref_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_REF);
                        int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                        int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);

                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_in;
                        
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                        
                      }
                      // Numeric type
                      else {
                        SPVM_OPCODE opcode = {0};
                        
                        
                        assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                        
                        int32_t typed_var_index_out;
                        int32_t typed_var_index_in;
                        switch (type_dist->basic_type->id) {
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_BYTE);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_SHORT);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_INT);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_LONG);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_FLOAT);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_DOUBLE);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          }
                          default: {
                            assert(0);
                          }
                        }

                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_in;
                        
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      }
                      break;
                    }
                    case SPVM_OP_C_ID_NUMERIC_COMPARISON_EQ : {
                      if (op_assign_src->first->id == SPVM_OP_C_ID_UNDEF || op_assign_src->last->id == SPVM_OP_C_ID_UNDEF) {
                        SPVM_OPCODE opcode = {0};
                        
                        int32_t typed_var_index_in;
                        
                        if (op_assign_src->first->id == SPVM_OP_C_ID_UNDEF) {
                          SPVM_TYPE* src_last_type = SPVM_CHECK_get_type(compiler, op_assign_src->last);
                          if (SPVM_TYPE_is_object_type(compiler, src_last_type->basic_type->id, src_last_type->dimension, src_last_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_UNDEF_OBJECT);
                          }
                          else if (SPVM_TYPE_is_ref_type(compiler, src_last_type->basic_type->id, src_last_type->dimension, src_last_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_UNDEF_REF);
                          }
                          
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          
                          int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          opcode.operand0 = typed_var_index_out;
                          opcode.operand1 = typed_var_index_in;
                          
                          SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                        }
                        else {
                          SPVM_TYPE* src_first_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                          if (SPVM_TYPE_is_object_type(compiler, src_first_type->basic_type->id, src_first_type->dimension, src_first_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_UNDEF_OBJECT);
                          }
                          else if (SPVM_TYPE_is_ref_type(compiler, src_first_type->basic_type->id, src_first_type->dimension, src_first_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_UNDEF_REF);
                          }
                          
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          
                          int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                          opcode.operand0 = typed_var_index_out;
                          opcode.operand1 = typed_var_index_in;
                          
                          SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                        }
                      }
                      else {
                        SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                        
                        SPVM_OPCODE opcode = {0};
                        
                        
                        int32_t typed_var_index_in1;
                        int32_t typed_var_index_in2;
                        if (SPVM_TYPE_is_numeric_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                          if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                            assert(0);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                            assert(0);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_EQ_INT);
                            typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                            typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_EQ_LONG);
                            typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                            typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_EQ_FLOAT);
                            typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                            typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_EQ_DOUBLE);
                            typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                            typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          }
                          else {
                            assert(0);
                          }
                        }
                        else if (SPVM_TYPE_is_object_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_EQ_OBJECT);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                        }
                        else if (SPVM_TYPE_is_ref_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_EQ_REF);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                        }
                        else {
                          assert(0);
                        }
                        
                        int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_in1;
                        opcode.operand2 = typed_var_index_in2;
                        
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      }
                      break;
                    }
                    case SPVM_OP_C_ID_NUMERIC_COMPARISON_NE : {
                      if (op_assign_src->first->id == SPVM_OP_C_ID_UNDEF ||op_assign_src->last->id == SPVM_OP_C_ID_UNDEF) {
                        SPVM_OPCODE opcode = {0};
                        
                        
                        int32_t typed_var_index_in;
                         
                        if (op_assign_src->first->id == SPVM_OP_C_ID_UNDEF) {
                          SPVM_TYPE* src_last_type = SPVM_CHECK_get_type(compiler, op_assign_src->last);
                          if (SPVM_TYPE_is_object_type(compiler, src_last_type->basic_type->id, src_last_type->dimension, src_last_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_NOT_UNDEF_OBJECT);
                          }
                          else if (SPVM_TYPE_is_ref_type(compiler, src_last_type->basic_type->id, src_last_type->dimension, src_last_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_NOT_UNDEF_REF);
                          }
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          
                          opcode.operand1 = typed_var_index_in;
                        }
                        else {
                          SPVM_TYPE* src_first_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                          if (SPVM_TYPE_is_object_type(compiler, src_first_type->basic_type->id, src_first_type->dimension, src_first_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_NOT_UNDEF_OBJECT);
                          }
                          else if (SPVM_TYPE_is_ref_type(compiler, src_first_type->basic_type->id, src_first_type->dimension, src_first_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_NOT_UNDEF_REF);
                          }
                          
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          
                          opcode.operand1 = typed_var_index_in;
                        }
                        
                        int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                        opcode.operand0 = typed_var_index_out;
                        
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      }
                      else {
                        SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);

                        SPVM_OPCODE opcode = {0};
                        
                        
                        int32_t typed_var_index_in1;
                        int32_t typed_var_index_in2;
                        if (SPVM_TYPE_is_numeric_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                          if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                            assert(0);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                            assert(0);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_NE_INT);
                            typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                            typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_NE_LONG);
                            typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                            typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_NE_FLOAT);
                            typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                            typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_NE_DOUBLE);
                            typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                            typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          }
                          else {
                            assert(0);
                          }
                        }
                        else if (SPVM_TYPE_is_object_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_NE_OBJECT);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                        }
                        else if (SPVM_TYPE_is_ref_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_NE_REF);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                        }
                        else {
                          assert(0);
                        }
                        
                        int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_in1;
                        opcode.operand2 = typed_var_index_in2;

                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      }
                      break;
                    }
                    case SPVM_OP_C_ID_NUMERIC_COMPARISON_GT : {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);

                      int32_t typed_var_index_in1;
                      int32_t typed_var_index_in2;
                      switch (operand_type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_GT_INT);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_GT_LONG);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_GT_FLOAT);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_GT_DOUBLE);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        default:
                          assert(0);
                      }
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;

                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_NUMERIC_COMPARISON_GE : {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);

                      int32_t typed_var_index_in1;
                      int32_t typed_var_index_in2;
                      switch (operand_type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_GE_INT);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_GE_LONG);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_GE_FLOAT);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_GE_DOUBLE);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        default:
                          assert(0);
                      }
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;

                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_NUMERIC_COMPARISON_LT : {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);

                      int32_t typed_var_index_in1;
                      int32_t typed_var_index_in2;
                      switch (operand_type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_LT_INT);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_LT_LONG);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_LT_FLOAT);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_LT_DOUBLE);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        default:
                          assert(0);
                      }
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;

                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_NUMERIC_COMPARISON_LE : {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);

                      int32_t typed_var_index_in1;
                      int32_t typed_var_index_in2;
                      switch (operand_type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_LE_INT);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_LE_LONG);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_LE_FLOAT);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_LE_DOUBLE);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        default:
                          assert(0);
                      }
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;

                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_NUMERIC_COMPARISON_CMP : {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);

                      int32_t typed_var_index_in1;
                      int32_t typed_var_index_in2;
                      switch (operand_type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_CMP_INT);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_CMP_LONG);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_CMP_FLOAT);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NUMERIC_COMPARISON_CMP_DOUBLE);
                          typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                          break;
                        default:
                          assert(0);
                      }
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;

                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_STRING_COMPARISON_EQ:
                    case SPVM_OP_C_ID_STRING_COMPARISON_NE:
                    case SPVM_OP_C_ID_STRING_COMPARISON_GT:
                    case SPVM_OP_C_ID_STRING_COMPARISON_GE:
                    case SPVM_OP_C_ID_STRING_COMPARISON_LT:
                    case SPVM_OP_C_ID_STRING_COMPARISON_LE:
                    case SPVM_OP_C_ID_STRING_COMPARISON_CMP:
                    {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      switch (op_assign_src->id) {
                        case SPVM_OP_C_ID_STRING_COMPARISON_EQ: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_STRING_COMPARISON_EQ);
                          break;
                        }
                        case SPVM_OP_C_ID_STRING_COMPARISON_NE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_STRING_COMPARISON_NE);
                          break;
                        }
                        case SPVM_OP_C_ID_STRING_COMPARISON_GT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_STRING_COMPARISON_GT);
                          break;
                        }
                        case SPVM_OP_C_ID_STRING_COMPARISON_GE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_STRING_COMPARISON_GE);
                          break;
                        }
                        case SPVM_OP_C_ID_STRING_COMPARISON_LT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_STRING_COMPARISON_LT);
                          break;
                        }
                        case SPVM_OP_C_ID_STRING_COMPARISON_LE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_STRING_COMPARISON_LE);
                          break;
                        }
                        case SPVM_OP_C_ID_STRING_COMPARISON_CMP: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_STRING_COMPARISON_CMP);
                          break;
                        }
                        default: {
                          assert(0);
                        }
                      }
                      
                      int32_t typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      int32_t typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in1;
                      opcode.operand2 = typed_var_index_in2;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      break;
                    }
                    case  SPVM_OP_C_ID_CONDITION_EVALUATION: {
                      SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                      
                      if (op_assign_src->first->id != SPVM_OP_C_ID_IF) {

                        SPVM_OPCODE opcode = {0};
                        
                        
                        int32_t typed_var_index_in;
                        if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                          if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                            assert(0);
                          }
                          else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                            assert(0);
                          }
                          else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONDITION_EVALUATION_INT);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          }
                          else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONDITION_EVALUATION_LONG);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          }
                          else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONDITION_EVALUATION_FLOAT);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          }
                          else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONDITION_EVALUATION_DOUBLE);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                          }
                          else {
                            assert(0);
                          }
                        }
                        else if (SPVM_TYPE_is_bool_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONDITION_EVALUATION_BOOL_OBJECT);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                        }
                        else if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONDITION_EVALUATION_OBJECT);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                        }
                        else if (SPVM_TYPE_is_ref_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONDITION_EVALUATION_REF);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                        }
                        else {
                          assert(0);
                        }
                        int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_in;
                        
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                        
                        // Set $.condition_flag
                        {
                          SPVM_OPCODE opcode = {0};
                          
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_INT);
                          
                          opcode.operand0 = 0;
                          opcode.operand1 = typed_var_index_out;
                          
                          SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                        }
                      }
                      
                      break;
                    }
                    case SPVM_OP_C_ID_ISA:
                    case SPVM_OP_C_ID_ISA_ERROR:
                    case SPVM_OP_C_ID_IS_TYPE:
                    case SPVM_OP_C_ID_IS_ERROR:
                    {
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      
                      SPVM_OP* op_type = op_assign_src->last;
                      SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, op_type);
                      
                      SPVM_OPCODE opcode = {0};
                      
                      if (op_assign_src->id == SPVM_OP_C_ID_ISA) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_ISA);
                      }
                      else if (op_assign_src->id == SPVM_OP_C_ID_ISA_ERROR) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_ISA_ERROR);
                      }
                      else if (op_assign_src->id == SPVM_OP_C_ID_IS_TYPE) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_TYPE);
                      }
                      else if (op_assign_src->id == SPVM_OP_C_ID_IS_ERROR) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_ERROR);
                      }
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in;
                      
                      opcode.operand2 = type->basic_type->id;
                      int32_t operand3 = type->dimension;
                      assert(operand3 < 0xFFFF);
                      opcode.operand3 = operand3;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_CAN: {
                      SPVM_OP* op_var = op_assign_src->first;
                      
                      int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_var);
                      
                      SPVM_OP* op_name_can_method = op_assign_src->last;
                      
                      const char* can_method_name = op_name_can_method->uv.name;
                      
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_STRING* can_method_name_constant_string = SPVM_HASH_get(basic_type->constant_string_symtable, can_method_name, strlen(can_method_name));
                      assert(can_method_name_constant_string);
                      
                      assert(can_method_name_constant_string->index >= 0);
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CAN);
                      
                      opcode.operand0 = typed_var_index_out;
                      opcode.operand1 = typed_var_index_in;
                      opcode.operand2 = can_method_name_constant_string->index;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_WARN: {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_WARN);
                      
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      opcode.operand0 = typed_var_index_in;
                      opcode.operand1 = op_assign->line;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_PRINT: {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PRINT);
                      
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      opcode.operand0 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_SAY: {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SAY);
                      
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      opcode.operand0 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_SET_LENGTH: {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_LENGTH);
                      
                      int32_t typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      int32_t typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = typed_var_index_in1;
                      opcode.operand1 = typed_var_index_in2;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      check_exception = 1;
                      
                      break;
                    }
                    case SPVM_OP_C_ID_SET_CAPACITY: {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CAPACITY);
                      
                      int32_t typed_var_index_in1 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      int32_t typed_var_index_in2 = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = typed_var_index_in1;
                      opcode.operand1 = typed_var_index_in2;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      check_exception = 1;
                      
                      break;
                    }
                    case SPVM_OP_C_ID_MAKE_READ_ONLY: {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MAKE_READ_ONLY);
                      
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      opcode.operand0 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_MAKE_FIXED_LENGTH: {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MAKE_FIXED_LENGTH);
                      
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      opcode.operand0 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_ENABLE_OPTIONS: {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_ENABLE_OPTIONS);
                      
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      opcode.operand0 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_DISABLE_OPTIONS: {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DISABLE_OPTIONS);
                      
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src->first);
                      opcode.operand0 = typed_var_index_in;
                      
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      break;
                    }
                    // $var_dist = ($var_src = ASSIGN)
                    // $var_dist = (ASSIGN = $var_src)
                    case SPVM_OP_C_ID_ASSIGN: {
                      SPVM_OP* op_var_src;
                      if (op_assign_src->first->id == SPVM_OP_C_ID_VAR || op_assign_src->first->id == SPVM_OP_C_ID_ASSIGN) {
                        op_var_src = op_assign_src->first;
                      }
                      else if (op_assign_src->last->id == SPVM_OP_C_ID_VAR || op_assign_src->last->id == SPVM_OP_C_ID_ASSIGN) {
                        op_var_src = op_assign_src->last;
                      }
                      else {
                        assert(0);
                      }
                      
                      SPVM_OP* op_var_dist = op_assign->last;
                      
                      if (SPVM_TYPE_is_byte_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_BYTE);
                        
                        int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_var_dist);
                        int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_var_src);

                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_in;
                        
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      }
                      else if (SPVM_TYPE_is_short_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_SHORT);
                        
                        int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_var_dist);
                        int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_var_src);

                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_in;
                        
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      }
                      else if (SPVM_TYPE_is_int_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_INT);
                        
                        int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_var_dist);
                        int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_var_src);

                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_in;
                        
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      }
                      else if (SPVM_TYPE_is_long_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_LONG);
                        
                        int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_var_dist);
                        int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_var_src);

                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_in;
                        
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      }
                      else if (SPVM_TYPE_is_float_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_FLOAT);
                        
                        int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_var_dist);
                        int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_var_src);

                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_in;
                        
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      }
                      else if (SPVM_TYPE_is_double_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_DOUBLE);
                        
                        int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_var_dist);
                        int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_var_src);

                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_in;
                        
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      }
                      else if (SPVM_TYPE_is_object_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                        
                        int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_var_dist);
                        int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_var_src);

                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_in;
                        
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      }
                      else if (SPVM_TYPE_is_ref_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_REF);
                        
                        int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_var_dist);
                        int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_var_src);

                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_in;
                        
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      }
                      else if (SPVM_TYPE_is_mulnum_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_FIELD* first_field = SPVM_LIST_get(type_dist->basic_type->fields, 0);
                        assert(first_field);
                        
                        SPVM_TYPE* field_type = first_field->type;
                        assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                        
                        SPVM_OPCODE opcode = {0};
                        

                        int32_t typed_var_index_out;
                        int32_t typed_var_index_in;
                        switch (field_type->basic_type->id) {
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_BYTE);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_SHORT);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_INT);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_LONG);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_FLOAT);
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                            typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                            typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_DOUBLE);
                            break;
                          }
                          default: {
                            assert(0);
                          }
                        }

                        int32_t fields_length = type_dist->basic_type->fields->length;
                        opcode.operand0 = typed_var_index_out;
                        opcode.operand1 = typed_var_index_in;
                        opcode.operand2 = fields_length;
                        
                        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      }
                      else if (SPVM_TYPE_is_void_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        // Do nothing
                      }
                      else {
                        assert(0);
                      }
                      
                      break;
                    }
                  }
                }
                // $VAR = $var
                else if (op_assign_dist->id == SPVM_OP_C_ID_CLASS_VAR_ACCESS) {
                  SPVM_OP* op_class_var_access = op_assign_dist;
                  SPVM_CLASS_VAR_ACCESS* class_var_access = op_class_var_access->uv.class_var_access;

                  SPVM_TYPE* src_type = SPVM_CHECK_get_type(compiler, op_assign_src);

                  // CLASS_VAR_ACCESS = UNDEF
                  if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                    SPVM_OPCODE opcode = {0};
                    
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_UNDEF);
                    opcode.operand0 = class_var_access->class_var->current_basic_type->id;
                    opcode.operand1 = class_var_access->class_var->index;
                    SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                  }
                  // CLASS_VAR_ACCESS = $var
                  else {
                    SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, op_class_var_access);

                    SPVM_OPCODE opcode = {0};
                    
                    
                    int32_t typed_var_index_in;
                    if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_OBJECT);
                      typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                    }
                    else {
                      if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_BYTE);
                        typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                      }
                      else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_SHORT);
                        typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                      }
                      else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_INT);
                        typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                      }
                      else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_LONG);
                        typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                      }
                      else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_FLOAT);
                        typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                      }
                      else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_DOUBLE);
                        typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                      }
                      else {
                        assert(0);
                      }
                    }
                                      
                    opcode.operand0 = class_var_access->class_var->current_basic_type->id;
                    opcode.operand1 = class_var_access->class_var->index;
                    opcode.operand2 = typed_var_index_in;
                    
                    SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                  }
                }
                // $$var_ref = $var
                else if (op_assign_dist->id == SPVM_OP_C_ID_DEREFERENCE) {
                  SPVM_OP* op_deref = op_assign_dist;

                  SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, op_deref->first);

                  SPVM_OPCODE opcode = {0};
                  
                  
                  assert(SPVM_TYPE_is_numeric_ref_type(compiler, type->basic_type->id, type->dimension, type->flag));
                  int32_t typed_var_index_in;
                  if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_DEREF_BYTE);
                    typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                  }
                  else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_DEREF_SHORT);
                    typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                  }
                  else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_DEREF_INT);
                    typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                  }
                  else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_DEREF_LONG);
                    typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                  }
                  else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_DEREF_FLOAT);
                    typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                  }
                  else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_DEREF_DOUBLE);
                    typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                  }
                  else {
                    assert(0);
                  }
                  
                  int32_t typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_dist);
                  
                  opcode.operand0 = typed_var_index_out;
                  opcode.operand1 = typed_var_index_in;
                  SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                  
                  check_exception = 1;
                  
                }
                // $@ = $var
                else if (op_assign_dist->id == SPVM_OP_C_ID_EXCEPTION_VAR) {
                  
                  SPVM_TYPE* src_type = SPVM_CHECK_get_type(compiler, op_assign_src);
                  
                  if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                    // EXCEPTION_VAR = undef
                    SPVM_OPCODE opcode = {0};
                    
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR_UNDEF);
                    SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                  }
                  else {
                    // EXCEPTION_VAR = $var
                    SPVM_OPCODE opcode = {0};
                    
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR);
                    int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                    opcode.operand0 = typed_var_index_in;
                    SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                  }
                }
                // $array->[$index] = $var
                else if (op_assign_dist->id == SPVM_OP_C_ID_ARRAY_ELEMENT_ACCESS) {
                  
                  // $VAR_ARRAY->[$VAR_INDEX] = $VAR_TERM
                  
                  SPVM_OP* op_element_access = op_assign_dist;
                  SPVM_OP* op_term_array = op_element_access->first;
                  SPVM_OP* op_term_index = op_element_access->last;

                  SPVM_TYPE* array_type = SPVM_CHECK_get_type(compiler, op_term_array);
                  int32_t array_type_dimension = array_type->dimension;
                  int32_t array_basic_type_id = array_type->basic_type->id;
                  int32_t array_basic_type_category = array_type->basic_type->category;

                  if (SPVM_TYPE_is_any_object_array_type(compiler, array_type->basic_type->id, array_type->dimension, array_type->flag)) {
                    SPVM_TYPE* src_type = SPVM_CHECK_get_type(compiler, op_assign_src);

                    if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_UNDEF);
                      
                      int32_t typed_var_index_array = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_array);
                      int32_t typed_var_index_index = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_index);
                      
                      opcode.operand0 = typed_var_index_array;
                      opcode.operand1 = typed_var_index_index;
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                    }
                    else {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE);
                      int32_t typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                      
                      int32_t typed_var_index_array = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_array);
                      int32_t typed_var_index_index = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_index);
                      
                      opcode.operand0 = typed_var_index_array;
                      opcode.operand1 = typed_var_index_index;
                      opcode.operand2 = typed_var_index_in;
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                      
                      check_exception = 1;
                      
                    }
                  }
                  else if (SPVM_TYPE_is_mulnum_array_type(compiler, array_type->basic_type->id, array_type->dimension, array_type->flag)) {
                    SPVM_FIELD* first_field = SPVM_LIST_get(array_type->basic_type->fields, 0);
                  
                    SPVM_TYPE* element_type = first_field->type;

                    SPVM_OPCODE opcode = {0};
                    
                    
                    assert(SPVM_TYPE_is_numeric_type(compiler, element_type->basic_type->id, element_type->dimension, element_type->flag));
                    int32_t typed_var_index_in;
                    if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_BYTE);
                      typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                    }
                    else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_SHORT);
                      typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                    }
                    else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_INT);
                      typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                    }
                    else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_LONG);
                      typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                    }
                    else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FLOAT);
                      typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                    }
                    else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_DOUBLE);
                      typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                    }
                    else {
                      assert(0);
                    }

                    int32_t typed_var_index_array = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_array);
                    int32_t typed_var_index_index = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_index);
                    int32_t fields_length = array_type->basic_type->fields->length;
                    
                    opcode.operand0 = typed_var_index_array;
                    opcode.operand1 = typed_var_index_index;
                    opcode.operand2 = typed_var_index_in;
                    int32_t operand3 = fields_length;
                    assert(operand3 < 0xFFFF);
                    opcode.operand3 = operand3;

                    SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);

                    check_exception = 1;
                    
                  }
                  else {
                  
                    SPVM_TYPE* element_type = SPVM_CHECK_get_type(compiler, op_assign_src);

                    if (SPVM_TYPE_is_undef_type(compiler, element_type->basic_type->id, element_type->dimension, element_type->flag)) {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_UNDEF);
                      
                      int32_t typed_var_index_array = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_array);
                      int32_t typed_var_index_index = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_index);
                      
                      opcode.operand0 = typed_var_index_array;
                      opcode.operand1 = typed_var_index_index;
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);

                      check_exception = 1;
                      
                    }
                    else {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      int32_t typed_var_index_in;
                      if (SPVM_TYPE_is_numeric_type(compiler, element_type->basic_type->id, element_type->dimension, element_type->flag)) {
                        if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_BYTE);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_SHORT);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_INT);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_LONG);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_FLOAT);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_DOUBLE);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        }
                        else {
                          assert(0);
                        }
                      }
                      else {
                        int32_t is_check_type;
                        if (array_type_dimension == 1) {
                          switch (array_basic_type_category) {
                            case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE:
                            case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT:
                            {
                              is_check_type = 1;
                              break;
                            }
                            default: {
                              is_check_type = 0;
                              break;
                            }
                          }
                        }
                        
                        if (is_check_type) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE);
                        }
                        else {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_OBJECT);
                        }
                        typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                      }
                      
                      int32_t typed_var_index_array = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_array);
                      int32_t typed_var_index_index = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_index);
                      
                      opcode.operand0 = typed_var_index_array;
                      opcode.operand1 = typed_var_index_index;
                      opcode.operand2 = typed_var_index_in;
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);

                      check_exception = 1;
                      
                    }
                  }
                }
                // $invocant->{FIELD_NAME} = $var
                else if (op_assign_dist->id == SPVM_OP_C_ID_FIELD_ACCESS) {
                  
                  SPVM_OP* op_field_access = op_assign_dist;
                  SPVM_OP* op_term_invocant = op_field_access->first;

                  // Call field
                  SPVM_FIELD_ACCESS* field_access = op_field_access->uv.field_access;

                  SPVM_TYPE* src_type = SPVM_CHECK_get_type(compiler, op_assign_src);
                  
                  SPVM_TYPE* invocant_type = SPVM_CHECK_get_type(compiler, op_term_invocant);
                  
                  if (SPVM_TYPE_is_mulnum_ref_type(compiler, invocant_type->basic_type->id, invocant_type->dimension, invocant_type->flag)) {
                    SPVM_FIELD* field = field_access->field;
                    
                    SPVM_OPCODE opcode = {0};
                    
                    int32_t typed_var_index_in;
                    switch (src_type->basic_type->id) {
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_BYTE);
                        typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_SHORT);
                        typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_INT);
                        typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_LONG);
                        typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_FLOAT);
                        typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_DOUBLE);
                        typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        break;
                      }
                      default: {
                        assert(0);
                      }
                    }

                    int32_t typed_var_index_invocant = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                    int32_t field_offset = field->index;

                    opcode.operand0 = typed_var_index_invocant;
                    opcode.operand1 = typed_var_index_in;
                    opcode.operand2 = field_offset;

                    SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                    
                    check_exception = 1;
                    
                  }
                  else if (SPVM_TYPE_is_mulnum_type(compiler, invocant_type->basic_type->id, invocant_type->dimension, invocant_type->flag)) {
                    SPVM_OPCODE opcode = {0};
                    
                    
                    assert(SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag));
                    int32_t typed_var_index_out;
                    int32_t typed_var_index_in;
                    if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_BYTE);
                      typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                      typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                    }
                    else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_SHORT);
                      typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                      typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                    }
                    else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_INT);
                      typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                      typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                    }
                    else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_LONG);
                      typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                      typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                    }
                    else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_FLOAT);
                      typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                      typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                    }
                    else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DOUBLE);
                      typed_var_index_out = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                      typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                    }
                    else {
                      assert(0);
                    }
                    
                    SPVM_FIELD* field = field_access->field;
                    int32_t field_offset = field->index;
                    
                    opcode.operand0 = typed_var_index_out;
                    opcode.operand1 = typed_var_index_in;
                    opcode.operand2 = field_offset;
                    
                    SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                  }
                  else {
                    if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_UNDEF);
                      
                      int32_t typed_var_index_invocant = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);

                      SPVM_FIELD* field = field_access->field;
                      
                      opcode.operand0 = typed_var_index_invocant;
                      opcode.operand2 = field->current_basic_type->id;
                      opcode.operand3 = (uint16_t)field->index;
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);

                      check_exception = 1;
                      
                    }
                    else {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      int32_t typed_var_index_in;
                      if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                        if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_BYTE);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        }
                        else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_SHORT);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        }
                        else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_INT);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        }
                        else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_LONG);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        }
                        else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_FLOAT);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        }
                        else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE);
                          typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                        }
                        else {
                          assert(0);
                        }
                      }
                      else if (SPVM_TYPE_is_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_OBJECT);
                        typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                      }
                      else {
                        assert(0);
                      }
                      
                      int32_t typed_var_index_invocant = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);

                      SPVM_FIELD* field = field_access->field;
                      
                      opcode.operand0 = typed_var_index_invocant;
                      opcode.operand1 = typed_var_index_in;
                      opcode.operand2 = field->current_basic_type->id;
                      opcode.operand3 = (uint16_t)field->index;
                      SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);

                      check_exception = 1;
                      
                    }
                  }
                }
                // $mulnum_array->[$index]{FIELD_NAME} = $var
                else if (op_assign_dist->id == SPVM_OP_C_ID_ARRAY_FIELD_ACCESS) {
                  
                  SPVM_OP* op_array_field_access = op_assign_dist;
                  SPVM_OP* op_term_invocant = op_array_field_access->first;
                  SPVM_OP* op_term_index = op_array_field_access->last;

                  // Call field
                  SPVM_ARRAY_FIELD_ACCESS* array_field_access = op_array_field_access->uv.array_field_access;
                  SPVM_FIELD* field = array_field_access->field;

                  // Array type
                  SPVM_TYPE* array_type = SPVM_CHECK_get_type(compiler, op_array_field_access->first);
                  SPVM_BASIC_TYPE* array_basic_type = array_type->basic_type;

                  // Element type
                  SPVM_TYPE* element_type = SPVM_CHECK_get_type(compiler, op_assign_src);
                  
                  SPVM_OPCODE opcode = {0};
                  
                  
                  int32_t typed_var_index_in;
                  if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_BYTE);
                    typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                  }
                  else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_SHORT);
                    typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                  }
                  else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_INT);
                    typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                  }
                  else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_LONG);
                    typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                  }
                  else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_FLOAT);
                    typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                  }
                  else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_DOUBLE);
                    typed_var_index_in = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_assign_src);
                  }
                  else {
                    assert(0);
                  }
                  
                  int32_t typed_var_index_invocant = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_invocant);
                  int32_t typed_var_index_index = SPVM_OPCODE_BUILDER_get_typed_var_index(compiler, op_term_index);
                  
                  int32_t fields_length = array_basic_type->fields->length;
                  int32_t field_offset = field->index;
                  
                  opcode.operand0 = typed_var_index_invocant;
                  opcode.operand1 = typed_var_index_index;
                  opcode.operand2 = typed_var_index_in;
                  int32_t operand3 = (field_offset << 8) + (fields_length - 1);
                  assert(operand3 < 0xFFFF);
                  opcode.operand3 = operand3;
                  
                  SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
                  
                  check_exception = 1;
                  
                }
                else {
                  assert(0);
                }
                
                break;
              }
            }
            
            if (check_exception) {
              SPVM_OPCODE_BUILDER_push_opcode_on_exception(compiler, opcode_list, eval_block_stack->length, catch_on_exception_opcode_index_stack, return_on_exception_opcode_index_stack, method->op_method, op_cur->line);
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
      
      // Free list
      SPVM_LIST_free(block_stack);
      SPVM_LIST_free(switch_stack_switch_info);
      SPVM_LIST_free(break_opcode_index_stack);
      SPVM_LIST_free(break_opcode_index_base_stack);
      SPVM_LIST_free(last_opcode_index_stack);
      SPVM_LIST_free(last_opcode_index_base_stack);
      SPVM_LIST_free(next_opcode_index_stack);
      SPVM_LIST_free(next_opcode_index_base_stack);
      SPVM_LIST_free(mortal_stack);
      SPVM_LIST_free(return_opcode_index_stack);
      SPVM_LIST_free(eval_block_stack);
      SPVM_LIST_free(catch_on_exception_opcode_index_stack);
      SPVM_LIST_free(return_on_exception_opcode_index_stack);
      
      END_OF_FUNCTION: {
        
        SPVM_OPCODE opcode = {0};
        
        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode,  SPVM_OPCODE_C_ID_END_METHOD);
        SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
        
        method->mortal_stack_length = mortal_stack_max;
        
        method->mortal_stack_tops_length = mortal_stack_tops_max;
        
        assert(mortal_stack_tops_index == 0);
      }
    }
  }
  
#ifdef SPVM_DEBUG_COMPILE
  fprintf(stderr, "\n[Opcodes]\n");
  SPVM_DUMPER_dump_basic_types_opcode_list(compiler, compiler->basic_types);
#endif

}

void SPVM_OPCODE_BUILDER_set_opcode_id(SPVM_COMPILER* compiler, SPVM_OPCODE* opcode, int32_t opcode_id) {
  opcode->id = opcode_id;
}

void SPVM_OPCODE_BUILDER_push_opcode_on_exception(
  SPVM_COMPILER* compiler,
  SPVM_OPCODE_LIST* opcode_list,
  int32_t in_eval_block,
  SPVM_LIST* catch_on_exception_opcode_index_stack,
  SPVM_LIST* return_on_exception_opcode_index_stack,
  SPVM_OP* op_method,
  int32_t line
)
{
  SPVM_METHOD* method = op_method->uv.method;
  int32_t method_opcodes_base_address_id = 0;
  
  if (in_eval_block) {
    SPVM_OPCODE opcode = {0};
    
    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CATCH_ON_EXCEPTION);
    
    opcode.operand2 = line;
    
    SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
    
    int32_t opcode_index = opcode_list->length - 1;
    
    SPVM_LIST_push(catch_on_exception_opcode_index_stack, (void*)(intptr_t)opcode_index);
  }
  else {
    SPVM_OPCODE opcode = {0};
    
    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_ON_EXCEPTION);
    opcode.operand2 = line;
    SPVM_OPCODE_LIST_push_opcode(compiler, opcode_list, &opcode);
    
    int32_t opcode_index = opcode_list->length - 1;
    
    SPVM_LIST_push(return_on_exception_opcode_index_stack, (void*)(intptr_t)(opcode_index));
  }
}

int32_t SPVM_OPCODE_BUILDER_get_typed_var_index(SPVM_COMPILER* compiler, SPVM_OP* op) {
  
  switch (op->id) {
    default: {
      SPVM_OP* op_var;
      if (op->id == SPVM_OP_C_ID_VAR) {
        op_var = op;
      }
      else if (op->id == SPVM_OP_C_ID_ASSIGN) {
        if (op->first->id == SPVM_OP_C_ID_VAR || op->first->id == SPVM_OP_C_ID_ASSIGN) {
          op_var = SPVM_OPCODE_BUILDER_get_op_var(compiler, op->first);
        }
        else if (op->last->id == SPVM_OP_C_ID_VAR || op->last->id == SPVM_OP_C_ID_ASSIGN) {
          op_var = SPVM_OPCODE_BUILDER_get_op_var(compiler, op->last);
        }
        else {
          assert(0);
        }
      }
      else if (op->id == SPVM_OP_C_ID_SEQUENCE) {
        op_var = SPVM_OPCODE_BUILDER_get_op_var(compiler, op->last);
      }
      else if (op->id == SPVM_OP_C_ID_REFERENCE) {
        op_var = SPVM_OPCODE_BUILDER_get_op_var(compiler, op->first);
      }
      else if (op->id == SPVM_OP_C_ID_DEREFERENCE) {
        op_var = SPVM_OPCODE_BUILDER_get_op_var(compiler, op->first);
      }
      else {
        spvm_warn("Unexpcted op:%s", op->name);
        assert(0);
      }
      
      return op_var->uv.var->var_decl->typed_var_index;
    }
  }
  
  return -1;
}

SPVM_OP* SPVM_OPCODE_BUILDER_get_op_var(SPVM_COMPILER* compiler, SPVM_OP* op) {
  
  SPVM_OP* op_var;
  if (op->id == SPVM_OP_C_ID_VAR) {
    op_var = op;
  }
  else if (op->id == SPVM_OP_C_ID_ASSIGN) {
    if (op->first->id == SPVM_OP_C_ID_VAR || op->first->id == SPVM_OP_C_ID_ASSIGN) {
      op_var = SPVM_OPCODE_BUILDER_get_op_var(compiler, op->first);
    }
    else if (op->last->id == SPVM_OP_C_ID_VAR || op->last->id == SPVM_OP_C_ID_ASSIGN) {
      op_var = SPVM_OPCODE_BUILDER_get_op_var(compiler, op->last);
    }
    else {
      assert(0);
    }
  }
  else if (op->id == SPVM_OP_C_ID_SEQUENCE) {
    op_var = SPVM_OPCODE_BUILDER_get_op_var(compiler, op->last);
  }
  else if (op->id == SPVM_OP_C_ID_REFERENCE) {
    op_var = SPVM_OPCODE_BUILDER_get_op_var(compiler, op->first);
  }
  else if (op->id == SPVM_OP_C_ID_DEREFERENCE) {
    op_var = SPVM_OPCODE_BUILDER_get_op_var(compiler, op->first);
  }
  else {
    spvm_warn("Unexpcted op:%s", op->name);
    assert(0);
  }
  
  return op_var;
}

