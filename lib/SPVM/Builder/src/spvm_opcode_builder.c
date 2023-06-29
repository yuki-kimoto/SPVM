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
#include "spvm_opcode_array.h"
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
#include "spvm_constant_string.h"
#include "spvm_dumper.h"

void SPVM_OPCODE_BUILDER_build_opcode_array(SPVM_COMPILER* compiler) {
  
  // Operation code
  SPVM_OPCODE_ARRAY* opcode_array = compiler->opcode_array;
  
  for (int32_t basic_type_id = compiler->basic_types_base_id; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    SPVM_LIST* methods = basic_type->methods;
    for (int32_t method_index = 0; method_index < methods->length; method_index++) {
      SPVM_METHOD* method = SPVM_LIST_get(methods, method_index);
      
      int32_t method_opcodes_base_address_id = opcode_array->length;
      
      method->opcodes_base_address_id = method_opcodes_base_address_id;
      
      // Check sub information
      assert(method->op_name);
      assert(method->return_type);
      assert(method->current_basic_type->module_file);
      
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
        
        int32_t items = SPVM_TYPE_get_items(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag);

        if (arg_type_dimension == 0) {
          if (arg_type_is_ref) {
            switch (arg_basic_type_category) {
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC:
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
              {
                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_REF);
                opcode.operand0 = arg->call_stack_index;
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
                    if (arg->op_optional_arg_default) {
                      SPVM_CONSTANT* constant = arg->op_optional_arg_default->uv.constant;
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_BYTE);
                      opcode.operand1 = (uint16_t)(uint8_t)constant->value.bval;
                    }
                    else {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_BYTE);
                    }
                    opcode.operand0 = arg->call_stack_index;
                    opcode.operand3 = stack_index & 0xFF;
                    stack_index++;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                    if (arg->op_optional_arg_default) {
                      SPVM_CONSTANT* constant = arg->op_optional_arg_default->uv.constant;
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_SHORT);
                      opcode.operand1 = (uint16_t)constant->value.sval;
                    }
                    else {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_SHORT);
                    }
                    opcode.operand0 = arg->call_stack_index;
                    opcode.operand3 = stack_index & 0xFF;
                    stack_index++;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                    if (arg->op_optional_arg_default) {
                      SPVM_CONSTANT* constant = arg->op_optional_arg_default->uv.constant;
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_INT);
                      opcode.operand1 = (uint32_t)constant->value.ival;
                    }
                    else {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_INT);
                    }
                    opcode.operand0 = arg->call_stack_index;
                    opcode.operand3 = stack_index & 0xFF;
                    stack_index++;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                    if (arg->op_optional_arg_default) {
                      SPVM_CONSTANT* constant = arg->op_optional_arg_default->uv.constant;
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_LONG);
                      *(int64_t*)&opcode.operand1 = constant->value.lval;
                    }
                    else {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_LONG);
                    }
                    opcode.operand0 = arg->call_stack_index;
                    opcode.operand3 = stack_index & 0xFF;
                    stack_index++;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                    if (arg->op_optional_arg_default) {
                      SPVM_CONSTANT* constant = arg->op_optional_arg_default->uv.constant;
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_FLOAT);
                      opcode.operand1 = (uint32_t)constant->value.ival;
                    }
                    else {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_FLOAT);
                    }
                    opcode.operand0 = arg->call_stack_index;
                    opcode.operand3 = stack_index & 0xFF;
                    stack_index++;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                    if (arg->op_optional_arg_default) {
                      SPVM_CONSTANT* constant = arg->op_optional_arg_default->uv.constant;
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_DOUBLE);
                      *(double*)&opcode.operand1 = constant->value.dval;
                    }
                    else {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_DOUBLE);
                    }
                    opcode.operand0 = arg->call_stack_index;
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
                opcode.operand0 = arg->call_stack_index;
                assert(items < 0xFFFF);
                opcode.operand3 = items << 8 | stack_index & 0xFF;
                stack_index += items;
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING:
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS:
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE:
              case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT:
              {
                if (arg->op_optional_arg_default) {
                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_OBJECT);
                }
                else {
                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_OBJECT);
                }
                opcode.operand0 = arg->call_stack_index;
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
              if (arg->op_optional_arg_default) {
                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_OBJECT);
              }
              else {
                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_OBJECT);
              }
              opcode.operand0 = arg->call_stack_index;
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
          if (arg->op_optional_arg_default) {
            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_OBJECT);
          }
          else {
            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_STACK_OBJECT);
          }
          opcode.operand0 = arg->call_stack_index;
          opcode.operand3 = stack_index & 0xFF;
          stack_index++;
        }
        else {
          assert(0);
        }
        
        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
      }
      
      {
        SPVM_OPCODE opcode = {0};
        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_END_ARGS);
        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
      }
      
      if (method->is_native) {
        continue;
      }
      
      SPVM_LIST* block_stack_call_stack_index_top = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* if_block_stack_goto_end_opcode_rel_index = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* loop_block_stack_goto_opcode_rel_index = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* loop_block_stack_next_base = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* loop_block_stack_last_base = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* switch_stack_switch_info = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* switch_block_stack_break_base = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* eval_block_stack_goto_opcode_rel_index = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* unresolved_if_eq_or_if_ne_opcode_rel_index_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* unresolved_last_opcode_rel_index_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* unresolved_break_opcode_rel_index_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* unresolved_next_opcode_rel_index_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* unresolved_return_opcode_rel_index_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      SPVM_LIST* call_stack_indexs_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      
      // Run OPs
      SPVM_OP* op_base = method->op_block;
      SPVM_OP* op_cur = op_base;
      int32_t finish = 0;
      
      int32_t call_stack_indexs_stack_top = 0;

      while (op_cur) {
        
        // [START]Preorder traversal position
        switch (op_cur->id) {
          case SPVM_OP_C_ID_BLOCK: { // Preorder
            
            SPVM_BLOCK* block = op_cur->uv.block;
            
            if (block->id == SPVM_BLOCK_C_ID_LOOP_INIT) {
              // Push last block base stack
              int32_t last_block_base = unresolved_last_opcode_rel_index_stack->length;
              SPVM_LIST_push(loop_block_stack_last_base, (void*)(intptr_t)last_block_base);
            }
            else if (block->id == SPVM_BLOCK_C_ID_LOOP_STATEMENTS) {
              
              // Push next block base stack
              int32_t next_block_base = unresolved_next_opcode_rel_index_stack->length;
              SPVM_LIST_push(loop_block_stack_next_base, (void*)(intptr_t)next_block_base);

              SPVM_OPCODE opcode = {0};
              
              // Add goto
              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GOTO);
              SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
              
              int32_t opcode_rel_index = opcode_array->length - 1 - method_opcodes_base_address_id;
              
              SPVM_LIST_push(loop_block_stack_goto_opcode_rel_index, (void*)(intptr_t)opcode_rel_index);
            }
            else if (block->id == SPVM_BLOCK_C_ID_SWITCH) {
              // Push break block base stack
              int32_t break_block_base = unresolved_break_opcode_rel_index_stack->length;
              SPVM_LIST_push(switch_block_stack_break_base, (void*)(intptr_t)break_block_base);
            }
            else if (block->id == SPVM_BLOCK_C_ID_EVAL) {
              int32_t opcode_rel_index = opcode_array->length - method_opcodes_base_address_id;
              
              SPVM_LIST_push(eval_block_stack_goto_opcode_rel_index, (void*)(intptr_t)opcode_rel_index);

              // Set exception var to undef in eval block start
              {
                SPVM_OPCODE opcode = {0};
                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CLEAR_EVAL_ERROR_ID);
                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
              }
              {
                SPVM_OPCODE opcode = {0};
                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR_UNDEF);
                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
              }
            }
            
            int32_t call_stack_indexs_top = call_stack_indexs_stack->length;
            SPVM_LIST_push(block_stack_call_stack_index_top, (void*)(intptr_t)call_stack_indexs_top);
            
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
              int32_t opcode_rel_index = opcode_array->length - method_opcodes_base_address_id;
              op_cur->uv.case_info->goto_opcode_rel_index = opcode_rel_index;
            }
            break;
          }
          case SPVM_OP_C_ID_DEFAULT: {
            if (switch_stack_switch_info->length > 0) {
              SPVM_SWITCH_INFO* switch_info = SPVM_LIST_get(switch_stack_switch_info, switch_stack_switch_info->length - 1);
              switch_info->default_opcode_rel_index = opcode_array->length - method_opcodes_base_address_id;
            }
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
                
                if (block->id == SPVM_BLOCK_C_ID_IF) {
                  
                  {
                    SPVM_OPCODE opcode = {0};
                    
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GOTO);
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    
                    int32_t opcode_rel_index = opcode_array->length - 1 - method_opcodes_base_address_id;
                    SPVM_LIST_push(if_block_stack_goto_end_opcode_rel_index, (void*)(intptr_t)opcode_rel_index);
                  }
                  
                  int32_t if_eq_or_if_ne_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(unresolved_if_eq_or_if_ne_opcode_rel_index_stack);
                  
                  SPVM_OPCODE* if_eq_or_if_ne_goto = (opcode_array->values + method_opcodes_base_address_id + if_eq_or_if_ne_goto_opcode_rel_index);
                  int32_t if_eq_or_if_ne_goto_opcode_base_rel_index = opcode_array->length - method_opcodes_base_address_id;
                  if_eq_or_if_ne_goto->operand0 = if_eq_or_if_ne_goto_opcode_base_rel_index;
                }
                else if (block->id == SPVM_BLOCK_C_ID_ELSE) {
                  
                  assert(if_block_stack_goto_end_opcode_rel_index->length > 0);
                  
                  int32_t if_block_end_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(if_block_stack_goto_end_opcode_rel_index);
                  
                  SPVM_OPCODE* if_block_end_goto = (opcode_array->values + method_opcodes_base_address_id + if_block_end_goto_opcode_rel_index);
                  int32_t if_block_end_goto_opcode_base_rel_index = opcode_array->length - method_opcodes_base_address_id;
                  if_block_end_goto->operand0 = if_block_end_goto_opcode_base_rel_index;
                }
                else if (block->id == SPVM_BLOCK_C_ID_LOOP_INIT) {
                  // last block base
                  int32_t last_block_base = (intptr_t)SPVM_LIST_pop(loop_block_stack_last_base);

                  // Set last position
                  int32_t unresolved_last_opcode_rel_index_stack_pop_count = unresolved_last_opcode_rel_index_stack->length - last_block_base;
                  for (int32_t i = 0; i < unresolved_last_opcode_rel_index_stack_pop_count; i++) {
                    int32_t last_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(unresolved_last_opcode_rel_index_stack);
                    
                    SPVM_OPCODE* last_goto = (opcode_array->values + method_opcodes_base_address_id + last_goto_opcode_rel_index);
                    int32_t last_goto_opcode_base_rel_index = opcode_array->length - method_opcodes_base_address_id;
                    last_goto->operand0 = last_goto_opcode_base_rel_index;
                  }
                }
                else if (block->id == SPVM_BLOCK_C_ID_LOOP_STATEMENTS) {
                  // next block base
                  int32_t next_block_base = (intptr_t)SPVM_LIST_pop(loop_block_stack_next_base);
                  
                  // Set next position
                  int32_t unresolved_next_opcode_rel_index_stack_pop_count = unresolved_next_opcode_rel_index_stack->length - next_block_base;
                  for (int32_t i = 0; i < unresolved_next_opcode_rel_index_stack_pop_count; i++) {
                    int32_t next_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(unresolved_next_opcode_rel_index_stack);
                    
                    SPVM_OPCODE* next_goto = (opcode_array->values + method_opcodes_base_address_id + next_goto_opcode_rel_index);
                    int32_t next_goto_opcode_base_rel_index = opcode_array->length - method_opcodes_base_address_id;
                    next_goto->operand0 = next_goto_opcode_base_rel_index;
                  }
                }
                else if (block->id == SPVM_BLOCK_C_ID_SWITCH) {
                  // break block base
                  int32_t break_block_base = (intptr_t)SPVM_LIST_pop(switch_block_stack_break_base);
                  
                  // Set break position
                  int32_t unresolved_break_opcode_rel_index_stack_pop_count = unresolved_break_opcode_rel_index_stack->length - break_block_base;
                  for (int32_t i = 0; i < unresolved_break_opcode_rel_index_stack_pop_count; i++) {
                    int32_t break_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(unresolved_break_opcode_rel_index_stack);
                    
                    SPVM_OPCODE* break_goto = (opcode_array->values + method_opcodes_base_address_id + break_goto_opcode_rel_index);
                    int32_t break_goto_opcode_base_rel_index = opcode_array->length - method_opcodes_base_address_id;
                    break_goto->operand0 = break_goto_opcode_base_rel_index;
                  }
                }
                else if (block->id == SPVM_BLOCK_C_ID_EVAL) {
                  // Set IF_EXCEPTION_CATCH opcode index
                  while (unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack->length > 0) {
                    int32_t goto_end_of_eval_on_exception_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack);
                    
                    SPVM_OPCODE* goto_end_of_eval_on_exception_goto = (opcode_array->values + method_opcodes_base_address_id + goto_end_of_eval_on_exception_goto_opcode_rel_index);
                    int32_t goto_end_of_eval_on_exception_goto_opcode_base_rel_index = opcode_array->length - method_opcodes_base_address_id;
                    goto_end_of_eval_on_exception_goto->operand0 = goto_end_of_eval_on_exception_goto_opcode_base_rel_index;
                  }
                  
                  SPVM_LIST_pop(eval_block_stack_goto_opcode_rel_index);
                }
                else if (block->id == SPVM_BLOCK_C_ID_METHOD) {
                  while (unresolved_return_opcode_rel_index_stack->length > 0) {
                    
                    int32_t return_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(unresolved_return_opcode_rel_index_stack);
                    
                    SPVM_OPCODE* return_goto = (opcode_array->values + method_opcodes_base_address_id + return_goto_opcode_rel_index);
                    int32_t return_goto_opcode_base_rel_index = opcode_array->length - method_opcodes_base_address_id;
                    return_goto->operand1 = return_goto_opcode_base_rel_index;
                  }

                  while (unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack->length > 0) {
                    int32_t goto_end_of_method_on_exception_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack);
                    
                    SPVM_OPCODE* goto_end_of_method_on_exception_goto = (opcode_array->values + method_opcodes_base_address_id + goto_end_of_method_on_exception_goto_opcode_rel_index);
                    int32_t goto_end_of_method_on_exception_goto_opcode_base_rel_index = opcode_array->length - method_opcodes_base_address_id;
                    goto_end_of_method_on_exception_goto->operand0 = goto_end_of_method_on_exception_goto_opcode_base_rel_index;
                  }
                }
                
                int32_t call_stack_indexs_top = (intptr_t)SPVM_LIST_get(block_stack_call_stack_index_top, block_stack_call_stack_index_top->length - 1);
                
                // Leave scope
                if (block->need_leave_scope) {
                  
                  SPVM_OPCODE opcode = {0};
                  
                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LEAVE_SCOPE);
                  opcode.operand0 = call_stack_indexs_top;
                  
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                }
                
                while (call_stack_indexs_stack->length > call_stack_indexs_top) {
                  SPVM_LIST_pop(call_stack_indexs_stack);
                }
                
                SPVM_LIST_pop(block_stack_call_stack_index_top);
                
                break;
              }
              case SPVM_OP_C_ID_LOOP_INCREMENT: {
                // Set loop first GOTO opcode
                int32_t loop_first_goto_opcode_rel_index = (intptr_t)SPVM_LIST_get(loop_block_stack_goto_opcode_rel_index, loop_block_stack_goto_opcode_rel_index->length - 1);
                
                SPVM_OPCODE* loop_first_goto = (opcode_array->values + method_opcodes_base_address_id + loop_first_goto_opcode_rel_index);
                int32_t loop_first_goto_opcode_base_rel_index = opcode_array->length - method_opcodes_base_address_id;
                loop_first_goto->operand0 = loop_first_goto_opcode_base_rel_index;
                
                break;
              }
              case SPVM_OP_C_ID_CONDITION:
              case SPVM_OP_C_ID_CONDITION_NOT:
              {
                
                int32_t opcode_rel_index = opcode_array->length - method_opcodes_base_address_id;

                SPVM_OPCODE opcode = {0};
                

                if (op_cur->id == SPVM_OP_C_ID_CONDITION) {
                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IF_EQ_ZERO);
                }
                else {
                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IF_NE_ZERO);
                }
                
                if (op_cur->flag & SPVM_OP_C_FLAG_CONDITION_IF) {
                  SPVM_LIST_push(unresolved_if_eq_or_if_ne_opcode_rel_index_stack, (void*)(intptr_t)opcode_rel_index);
                }
                else if (op_cur->flag & SPVM_OP_C_FLAG_CONDITION_LOOP) {
                  assert(loop_block_stack_goto_opcode_rel_index->length > 0);
                  
                  int32_t loop_first_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(loop_block_stack_goto_opcode_rel_index);
                  
                  opcode.operand0 = loop_first_goto_opcode_rel_index + 1;
                }
                
                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                
                break;
              }
              case SPVM_OP_C_ID_NEXT: {
                // GOTO increment statement
                SPVM_OPCODE opcode = {0};
                
                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GOTO);
                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                
                int32_t opcode_rel_index = opcode_array->length - 1 - method_opcodes_base_address_id;
                
                SPVM_LIST_push(unresolved_next_opcode_rel_index_stack, (void*)(intptr_t)opcode_rel_index);
                
                break;
              }
              case SPVM_OP_C_ID_LAST: {
                // GOTO end of loop init block
                SPVM_OPCODE opcode = {0};
                
                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GOTO);
                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                
                int32_t opcode_rel_index = opcode_array->length - 1 - method_opcodes_base_address_id;
                
                SPVM_LIST_push(unresolved_last_opcode_rel_index_stack, (void*)(intptr_t)opcode_rel_index);
                
                break;
              }
              case SPVM_OP_C_ID_SWITCH: {
                
                // Pop switch information
                SPVM_SWITCH_INFO* switch_info = SPVM_LIST_pop(switch_stack_switch_info);
                
                // Set the information of switch opcodes
                int32_t opcode_address_id = switch_info->opcode_address_id;
                SPVM_OPCODE* opcode = (SPVM_OPCODE*)&opcode_array->values[opcode_address_id];
                opcode->operand1 = switch_info->default_opcode_rel_index;
                opcode->operand2 = switch_info->case_infos->length;

                // Set case info operands
                SPVM_LIST* case_infos = switch_info->case_infos;
                for (int32_t i = 0; i < switch_info->case_infos->length; i++) {
                  SPVM_OPCODE* opcode_case_info = (SPVM_OPCODE*)&opcode_array->values[opcode_address_id + 1 + i];
                  SPVM_CASE_INFO* case_info = SPVM_LIST_get(case_infos, i);
                  opcode_case_info->operand1 = case_info->case_value;
                  opcode_case_info->operand2 = case_info->goto_opcode_rel_index;
                }
                
                break;
              }
              case SPVM_OP_C_ID_SWITCH_CONDITION: {
                assert(switch_stack_switch_info->length > 0);
                
                SPVM_SWITCH_INFO* switch_info = SPVM_LIST_get(switch_stack_switch_info, switch_stack_switch_info->length - 1);;

                int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur->first);
                
                int32_t opcode_address_id = opcode_array->length;
                switch_info->opcode_address_id = opcode_address_id;

                // Add switch opcode
                SPVM_OPCODE opcode_switch_info;
                memset(&opcode_switch_info, 0, sizeof(SPVM_OPCODE));
                opcode_switch_info.id = SPVM_OPCODE_C_ID_LOOKUP_SWITCH;
                opcode_switch_info.operand0 = call_stack_index_in;
                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode_switch_info);

                // Match values and branchs
                for (int32_t i = 0; i < switch_info->case_infos->length; i++) {
                  SPVM_CASE_INFO* case_info = SPVM_LIST_get(switch_info->case_infos, i);
                  
                  // Branch
                  SPVM_CASE_INFO* branch_opcode_rel_index_case_info = switch_info->case_infos->values[i];
                  branch_opcode_rel_index_case_info->goto_opcode_rel_index = case_info->goto_opcode_rel_index;
                  
                  // Add case info
                  SPVM_OPCODE opcode_case_info;
                  memset(&opcode_case_info, 0, sizeof(SPVM_OPCODE));
                  opcode_case_info.id = SPVM_OPCODE_C_ID_CASE_INFO;
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode_case_info);
                }

                // Default branch
                int32_t default_opcode_rel_index = switch_info->default_opcode_rel_index;
                if (default_opcode_rel_index == 0) {
                  default_opcode_rel_index = opcode_array->length + 1 - method_opcodes_base_address_id;
                }
                switch_info->default_opcode_rel_index = default_opcode_rel_index;

                break;
              }
              case SPVM_OP_C_ID_BREAK: {
                // GOTO end of switch block
                SPVM_OPCODE opcode = {0};
                
                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GOTO);
                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                
                int32_t opcode_rel_index = opcode_array->length - 1 - method_opcodes_base_address_id;
                
                SPVM_LIST_push(unresolved_break_opcode_rel_index_stack, (void*)(intptr_t)opcode_rel_index);
                
                break;
              }
              case SPVM_OP_C_ID_RETURN: {
                if (op_cur->first) {
                  SPVM_TYPE* return_type = SPVM_CHECK_get_type(compiler, op_cur->first);
                  
                  if (SPVM_TYPE_is_undef_type(compiler, return_type->basic_type->id, return_type->dimension, return_type->flag)) {
                    SPVM_OPCODE opcode = {0};
                    
                    
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_UNDEF);
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else {
                    SPVM_OPCODE opcode = {0};
                    
                     
                    
                    int32_t call_stack_index_in;
                    if (SPVM_TYPE_is_numeric_type(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag)) {
                      switch (method->return_type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_BYTE);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur->first);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_SHORT);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur->first);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_INT);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur->first);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_LONG);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur->first);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_FLOAT);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur->first);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_DOUBLE);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur->first);
                          break;
                        }
                        default:
                          assert(0);
                      }
                    }
                    else if (SPVM_TYPE_is_object_type(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag)) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_OBJECT);
                      call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur->first);
                    }
                    else if (SPVM_TYPE_is_mulnum_type(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag)) {
                      SPVM_FIELD* first_field = SPVM_LIST_get(return_type->basic_type->fields, 0);
                      assert(first_field);
                      
                      SPVM_TYPE* field_type = SPVM_CHECK_get_type(compiler, first_field->op_field);
                      assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));

                      switch (field_type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur->first);
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_MULNUM_BYTE);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur->first);
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_MULNUM_SHORT);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur->first);
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_MULNUM_INT);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur->first);
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_MULNUM_LONG);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur->first);
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_MULNUM_FLOAT);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur->first);
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
                    
                    int32_t method_return_items = SPVM_TYPE_get_items(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag);

                    opcode.operand0 = call_stack_index_in;
                    opcode.operand2 = method_return_items;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                }
                else {
                  SPVM_OPCODE opcode = {0};
                  
                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_VOID);
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                }
                
                int32_t return_opcode_rel_index = opcode_array->length - 1 - method_opcodes_base_address_id;
                
                SPVM_LIST_push(unresolved_return_opcode_rel_index_stack, (void*)(intptr_t)return_opcode_rel_index);
                
                break;
              }
              case SPVM_OP_C_ID_DIE: {
                
                SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, op_cur->last);
                
                // SET_ERROR_ID
                {
                  SPVM_OPCODE opcode = {0};
                  
                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ERROR_ID);
                  opcode.operand0 = type->basic_type->id;
                  
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                }
                
                SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_cur->line);
                
                break;
              }
              case SPVM_OP_C_ID_VAR: {
                if (op_cur->uv.var->is_declaration) {
                  
                  SPVM_VAR_DECL* var_decl = op_cur->uv.var->var_decl;
                  
                  SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, var_decl->op_var_decl);
                  if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                    
                    SPVM_OPCODE opcode = {0};
                    
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PUSH_MORTAL);
                    int32_t call_stack_index = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur);
                    opcode.operand0 = call_stack_index;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    
                    SPVM_LIST_push(call_stack_indexs_stack, (void*)(intptr_t)call_stack_index);
                    
                    call_stack_indexs_stack_top++;
                  }
                  
                  // Initialized not initialized variable
                  if (!op_cur->uv.var->is_initialized && !op_cur->uv.var->var_decl->is_arg) {
                    // Multi numeric type
                    if (SPVM_TYPE_is_mulnum_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                      SPVM_FIELD* first_field = SPVM_LIST_get(type->basic_type->fields, 0);
                      assert(first_field);
                      
                      SPVM_TYPE* field_type = SPVM_CHECK_get_type(compiler, first_field->op_field);
                      assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      int32_t call_stack_index_out;
                      int32_t call_stack_index_in;
                      switch (field_type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_BYTE_ZERO);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_SHORT_ZERO);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_INT_ZERO);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_LONG_ZERO);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_FLOAT_ZERO);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_DOUBLE_ZERO);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur);
                          break;
                        }
                        default:
                          assert(0);
                      }
                      
                      int32_t fields_length = type->basic_type->fields->length;
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand2 = fields_length;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    }
                    // Object type
                    else if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_UNDEF);
                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur);
                      
                      opcode.operand0 = call_stack_index_out;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
                    }
                    // Numeric type
                    else if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      int32_t call_stack_index_out;
                      switch (type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_BYTE_ZERO);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_SHORT_ZERO);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_INT_ZERO);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_LONG_ZERO);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_FLOAT_ZERO);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_DOUBLE_ZERO);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_cur);
                          break;
                        }
                        default: {
                          assert(0);
                        }
                      }

                      opcode.operand0 = call_stack_index_out;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
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
                    case SPVM_OP_C_ID_CONCAT: {
                      SPVM_TYPE* first_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                      
                      assert(SPVM_TYPE_is_string_or_byte_array_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag));
                      
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONCAT);
                      
                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      int32_t call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                      int32_t call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);

                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                      SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                      break;
                    }
                    case SPVM_OP_C_ID_TYPE_NAME : {
                      
                      SPVM_TYPE* first_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                      
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_NAME);
                      
                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);

                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_DUMP : {
                      
                      SPVM_TYPE* first_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                      
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DUMP);
                      
                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);

                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_NEW_STRING_LEN : {
                      
                      SPVM_TYPE* first_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                      
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_STRING_LEN);
                      
                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);

                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                      SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_IS_READ_ONLY : {
                      
                      SPVM_TYPE* first_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                      
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_READ_ONLY);
                      
                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);

                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_UNDEF : {

                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_UNDEF);
                      
                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      opcode.operand0 = call_stack_index_out;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_CALL_METHOD: {
                      
                      SPVM_CALL_METHOD* call_method = op_assign_src->uv.call_method;
                      const char* call_method_method_name = call_method->method->name;
                      
                      SPVM_METHOD* method_call_method = SPVM_HASH_get(call_method->method->current_basic_type->method_symtable, call_method_method_name, strlen(call_method_method_name));
                      
                      int32_t first_arg_call_stack_index = -1;
                      SPVM_OP* op_term_args = op_assign_src->first;
                      SPVM_OP* op_term_arg = op_term_args->first;

                      SPVM_LIST* args = method_call_method->var_decls;
                      int32_t items = 0;
                      {
                        for (int32_t arg_index = 0; arg_index < method_call_method->args_length; arg_index++) {
                          SPVM_VAR_DECL* arg_var_decl = SPVM_LIST_get(args, arg_index);
                          
                          // Argument type
                          SPVM_TYPE* arg_type = arg_var_decl->type;
                          int32_t arg_items = SPVM_TYPE_get_items(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag);
                          
                          // Term argment type
                          op_term_arg = SPVM_OP_sibling(compiler, op_term_arg);
                          if (!op_term_arg) {
                            break;
                          }
                          
                          SPVM_TYPE* term_arg_type = SPVM_CHECK_get_type(compiler, op_term_arg);
                          
                          SPVM_OPCODE opcode = {0};
                          
                          opcode.operand3 = items;
                          
                          if (SPVM_TYPE_is_undef_type(compiler, term_arg_type->basic_type->id, term_arg_type->dimension, term_arg_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_UNDEF);
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else {
                            if (SPVM_TYPE_is_ref_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_REF);

                              // Term of argument
                              int32_t call_stack_index_arg = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_arg);
                              
                              opcode.operand0 = call_stack_index_arg;
                              
                              SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            }
                            else if (SPVM_TYPE_is_mulnum_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag)) {

                              SPVM_FIELD* first_field = SPVM_LIST_get(arg_type->basic_type->fields, 0);
                              assert(first_field);
                              
                              SPVM_TYPE* field_type = SPVM_CHECK_get_type(compiler, first_field->op_field);
                              assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                              
                              int32_t call_stack_index_arg;
                              switch (field_type->basic_type->id) {
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_MULNUM_BYTE);
                                  call_stack_index_arg = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_arg);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_MULNUM_SHORT);
                                  call_stack_index_arg = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_arg);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_MULNUM_INT);
                                  call_stack_index_arg = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_arg);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_MULNUM_LONG);
                                  call_stack_index_arg = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_arg);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_MULNUM_FLOAT);
                                  call_stack_index_arg = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_arg);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_MULNUM_DOUBLE);
                                  call_stack_index_arg = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_arg);
                                  break;
                                }
                                default:
                                  assert(0);
                              }
                              
                              int32_t fields_length = arg_type->basic_type->fields->length;
                              opcode.operand0 = call_stack_index_arg;
                              opcode.operand1 = fields_length;
                              
                              SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            }
                            // Object type
                            else if (SPVM_TYPE_is_object_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_OBJECT);
                              int32_t call_stack_index_arg = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_arg);
                              
                              opcode.operand0 = call_stack_index_arg;
                              
                              if (arg_index == 0) {
                                first_arg_call_stack_index = call_stack_index_arg;
                              }
                              SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            }
                            // Numeric type
                            else if (SPVM_TYPE_is_numeric_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag)) {
                              int32_t call_stack_index_arg;
                              switch (arg_type->basic_type->id) {
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_BYTE);
                                  call_stack_index_arg = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_arg);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_SHORT);
                                  call_stack_index_arg = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_arg);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_INT);
                                  call_stack_index_arg = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_arg);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_LONG);
                                  call_stack_index_arg = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_arg);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_FLOAT);
                                  call_stack_index_arg = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_arg);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_STACK_DOUBLE);
                                  call_stack_index_arg = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_arg);
                                  break;
                                }
                                default:
                                  assert(0);
                              }
                              
                              opcode.operand0 = call_stack_index_arg;
                              
                              if (arg_index == 0) {
                                first_arg_call_stack_index = call_stack_index_arg;
                              }
                              SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            }
                            else {
                              assert(0);
                            }
                          }
                          items += arg_items;
                        }
                      }

                      int32_t call_stack_index_out;

                      // Return
                      SPVM_TYPE* call_method_return_type = call_method->method->return_type;
                      // Call method
                      SPVM_OPCODE opcode = {0};
                      
                      if (call_method->is_class_method) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CALL_CLASS_METHOD);
                      }
                      else {
                        if (call_method->is_class_method_instance_method_call) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD_STATIC);
                        }
                        else {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD);
                        }
                      }
                      opcode.operand0 = call_method->method->current_basic_type->id;
                      opcode.operand1 = call_method->method->index;
                      opcode.operand2 = items;
                      
                      SPVM_OPCODE opcode_return = {0};
                      {
                        call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                        opcode_return.operand0 = call_stack_index_out;
                        opcode_return.operand3 = 0;

                        // Numeric type
                        if (SPVM_TYPE_is_numeric_type(compiler, call_method_return_type->basic_type->id, call_method_return_type->dimension, call_method_return_type->flag)) {
                          switch (call_method_return_type->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_return, SPVM_OPCODE_C_ID_GET_STACK_BYTE);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_return, SPVM_OPCODE_C_ID_GET_STACK_SHORT);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_return, SPVM_OPCODE_C_ID_GET_STACK_INT);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_return, SPVM_OPCODE_C_ID_GET_STACK_LONG);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_return, SPVM_OPCODE_C_ID_GET_STACK_FLOAT);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_return, SPVM_OPCODE_C_ID_GET_STACK_DOUBLE);
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
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_return, SPVM_OPCODE_C_ID_GET_STACK_OBJECT);
                        }
                        // Multi numeric type
                        else if (SPVM_TYPE_is_mulnum_type(compiler, call_method_return_type->basic_type->id, call_method_return_type->dimension, call_method_return_type->flag)) {

                          SPVM_FIELD* first_field = SPVM_LIST_get(call_method_return_type->basic_type->fields, 0);
                          assert(first_field);
                          
                          SPVM_TYPE* field_type = SPVM_CHECK_get_type(compiler, first_field->op_field);
                          assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                          
                          int32_t call_method_return_items = SPVM_TYPE_get_items(compiler, call_method_return_type->basic_type->id, call_method_return_type->dimension, call_method_return_type->flag);
                          assert(call_method_return_items < 0xFFFF);
                          opcode_return.operand3 = call_method_return_items << 8 | 0;

                          switch (field_type->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_return, SPVM_OPCODE_C_ID_GET_STACK_MULNUM_BYTE);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_return, SPVM_OPCODE_C_ID_GET_STACK_MULNUM_SHORT);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_return, SPVM_OPCODE_C_ID_GET_STACK_MULNUM_INT);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_return, SPVM_OPCODE_C_ID_GET_STACK_MULNUM_LONG);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_return, SPVM_OPCODE_C_ID_GET_STACK_MULNUM_FLOAT);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode_return, SPVM_OPCODE_C_ID_GET_STACK_MULNUM_DOUBLE);
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
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
                      SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                      
                      if (!SPVM_TYPE_is_void_type(compiler, call_method_return_type->basic_type->id, call_method_return_type->dimension, call_method_return_type->flag)) {
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode_return);
                      }
                      break;
                    }
                    case SPVM_OP_C_ID_STRING_LENGTH : {
                      
                      // String length logic is same as ARRAY_LENGTH opcode
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_ARRAY_LENGTH);
                      
                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                      SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                      break;
                    }
                    case SPVM_OP_C_ID_ARRAY_LENGTH : {
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_ARRAY_LENGTH);
                      
                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                      SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
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
                      
                      int32_t call_stack_index_out;
                      switch (element_type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_BYTE);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_SHORT);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_INT);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_LONG);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_FLOAT);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          break;
                        }
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_DOUBLE);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          break;
                        }
                        default: {
                          assert(0);
                        }
                      }
                      
                      // Field absolute name symbol
                      int32_t call_stack_index_invocant = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);
                      int32_t call_stack_index_index = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_index);
                      
                      int32_t fields_length = array_basic_type->fields->length;
                      int32_t field_offset = field->index;

                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_invocant;
                      opcode.operand2 = call_stack_index_index;
                      int32_t operand3 = (field_offset << 8) + (fields_length - 1);
                      assert(operand3 < 0xFFFF);
                      opcode.operand3 = operand3;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                      SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                      break;
                    }
                    case SPVM_OP_C_ID_FIELD_ACCESS : {

                      // Weaken field
                      if (op_assign_src->flag & SPVM_OP_C_FLAG_FIELD_ACCESS_WEAKEN) {
                        SPVM_OPCODE opcode = {0};
                        

                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_WEAKEN_FIELD);
                        
                        SPVM_OP* op_term_invocant = op_assign_src->first;
                        int32_t call_stack_index_invocant = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);

                        SPVM_FIELD* field = op_assign_src->uv.field_access->field;

                        opcode.operand0 = call_stack_index_invocant;
                        opcode.operand2 = field->current_basic_type->id;
                        opcode.operand3 = (uint16_t)field->index;
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                        SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign_src->line);
                      }
                      else if (op_assign_src->flag & SPVM_OP_C_FLAG_FIELD_ACCESS_UNWEAKEN) {
                        SPVM_OPCODE opcode = {0};
                        

                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_UNWEAKEN_FIELD);
                        
                        SPVM_OP* op_term_invocant = op_assign_src->first;
                        int32_t call_stack_index_invocant = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);

                        SPVM_FIELD* field = op_assign_src->uv.field_access->field;
                        
                        opcode.operand0 = call_stack_index_invocant;
                        opcode.operand2 = field->current_basic_type->id;
                        opcode.operand3 = (uint16_t)field->index;
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                        SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign_src->line);
                      }
                      else if (op_assign_src->flag & SPVM_OP_C_FLAG_FIELD_ACCESS_ISWEAK) {
                        SPVM_OPCODE opcode = {0};
                        

                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_ISWEAK_FIELD);
                        
                        SPVM_OP* op_term_invocant = op_assign_src->first;
                        int32_t call_stack_index_invocant = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);

                        SPVM_FIELD* field = op_assign_src->uv.field_access->field;
                        
                        opcode.operand1 = call_stack_index_invocant;
                        opcode.operand2 = field->current_basic_type->id;
                        opcode.operand3 = (uint16_t)field->index;
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                        SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign_src->line);
                      }
                      else {
                        // $VAR = $VAR_OBJECT->{NAME}
                        SPVM_OP* op_field_access = op_assign_src;
                        SPVM_OP* op_term_invocant = op_field_access->first;
                        
                        // Call field
                        SPVM_FIELD_ACCESS* field_access = op_field_access->uv.field_access;
                        
                        SPVM_TYPE* field_type = SPVM_CHECK_get_type(compiler, op_field_access);

                        SPVM_TYPE* invocant_type = SPVM_CHECK_get_type(compiler, op_term_invocant);

                        // Value field dereference access
                        if (SPVM_TYPE_is_mulnum_ref_type(compiler, invocant_type->basic_type->id, invocant_type->dimension, invocant_type->flag)) {
                          SPVM_FIELD* field = field_access->field;
                          
                          SPVM_OPCODE opcode = {0};
                          
                          int32_t call_stack_index_out;
                          switch (field_type->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_BYTE);
                              call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_SHORT);
                              call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_INT);
                              call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_LONG);
                              call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_FLOAT);
                              call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_DOUBLE);
                              call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                              break;
                            }
                            default: {
                              assert(0);
                            }
                          }
                          
                          int32_t call_stack_index_invocant = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);
                          int32_t field_offset = field->index;

                          opcode.operand0 = call_stack_index_out;
                          opcode.operand1 = call_stack_index_invocant;
                          opcode.operand2 = field_offset;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                        }
                        // Mulnum field access
                        else if (SPVM_TYPE_is_mulnum_type(compiler, invocant_type->basic_type->id, invocant_type->dimension, invocant_type->flag)) {
                          SPVM_OPCODE opcode = {0};
                          
                          
                          int32_t call_stack_index_out;
                          int32_t call_stack_index_in;
                          switch (field_type->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_BYTE);
                              call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                              call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_SHORT);
                              call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                              call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_INT);
                              call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                              call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_LONG);
                              call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                              call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_FLOAT);
                              call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                              call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DOUBLE);
                              call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                              call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);
                              break;
                            }
                            default: {
                              assert(0);
                            }
                          }

                          SPVM_FIELD* field = field_access->field;
                          
                          opcode.operand0 = call_stack_index_out;
                          opcode.operand1 = call_stack_index_in;
                          opcode.operand2 = field->index;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                        }
                        // Field access
                        else {
                          SPVM_OPCODE opcode = {0};
                          
                          int32_t call_stack_index_invocant = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);
                          int32_t call_stack_index_out;
                          if (SPVM_TYPE_is_object_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_OBJECT);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          }
                          else {
                            switch (field_type->basic_type->id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_BYTE);
                                call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_SHORT);
                                call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_INT);
                                call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_LONG);
                                call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_FLOAT);
                                call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE);
                                call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                                break;
                              }
                              default: {
                                assert(0);
                              }
                            }
                          }

                          SPVM_FIELD* field = field_access->field;
                          
                          opcode.operand0 = call_stack_index_out;
                          opcode.operand1 = call_stack_index_invocant;
                          opcode.operand2 = field->current_basic_type->id;
                          opcode.operand3 = (uint16_t)field->index;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                        }
                      }
                      break;
                    }
                    case SPVM_OP_C_ID_ARRAY_ACCESS : {
                      
                      // $VAR = $VAR_ARRAY->[$VAR_INDEX]
                      SPVM_OP* op_array_access = op_assign_src;
                      SPVM_OP* op_term_array = op_array_access->first;
                      SPVM_OP* op_term_index = op_array_access->last;
                      
                      SPVM_TYPE* array_type = SPVM_CHECK_get_type(compiler, op_term_array);

                      if (SPVM_TYPE_is_mulnum_array_type(compiler, array_type->basic_type->id, array_type->dimension, array_type->flag)) {
                        SPVM_FIELD* first_field = SPVM_LIST_get(array_type->basic_type->fields, 0);
                        
                        SPVM_TYPE* element_type = SPVM_CHECK_get_type(compiler, first_field->op_field);
                        
                        SPVM_OPCODE opcode = {0};
                        
                        assert(SPVM_TYPE_is_numeric_type(compiler, element_type->basic_type->id, element_type->dimension, element_type->flag));
                        int32_t call_stack_index_out;
                        switch (element_type->basic_type->id) {
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_BYTE);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_SHORT);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_INT);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_LONG);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FLOAT);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_DOUBLE);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          }
                          default: {
                            assert(0);
                          }
                        }
                        int32_t call_stack_index_array = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_array);
                        int32_t call_stack_index_index = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_index);
                        int32_t fields_length = array_type->basic_type->fields->length;

                        opcode.operand0 = call_stack_index_out;
                        opcode.operand1 = call_stack_index_array;
                        opcode.operand2 = call_stack_index_index;
                        int32_t operand3 = fields_length;
                        assert(operand3 < 0xFFFF);
                        opcode.operand3 = operand3;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                        SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                      }
                      else {
                        SPVM_TYPE* element_type = SPVM_CHECK_get_type(compiler, op_array_access);
                      
                        SPVM_OPCODE opcode = {0};
                        
                        int32_t call_stack_index_out;
                        if (SPVM_TYPE_is_object_type(compiler, element_type->basic_type->id, element_type->dimension, element_type->flag)) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_OBJECT);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                        }
                        else {
                          switch (element_type->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_BYTE);
                              call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_SHORT);
                              call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_INT);
                              call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_LONG);
                              call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_FLOAT);
                              call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_DOUBLE);
                              call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                              break;
                            }
                            default: {
                              assert(0);
                            }
                          }
                        }

                        int32_t call_stack_index_array = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_array);
                        int32_t call_stack_index_index = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_index);

                        opcode.operand0 = call_stack_index_out;
                        opcode.operand1 = call_stack_index_array;
                        opcode.operand2 = call_stack_index_index;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                        SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                      }
                      break;
                    }
                    case SPVM_OP_C_ID_CLASS_VAR_ACCESS : {
                      SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, op_assign_src);
                      
                      SPVM_CLASS_VAR_ACCESS* class_var_access = op_assign_src->uv.class_var_access;
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      int32_t call_stack_index_out;
                      if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_OBJECT);
                        call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      }
                      else {
                        switch (type->basic_type->id) {
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_BYTE);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_SHORT);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_INT);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_LONG);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_FLOAT);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_DOUBLE);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          }
                          default: {
                            assert(0);
                          }
                        }
                      }
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = class_var_access->class_var->current_basic_type->id;
                      opcode.operand2 = class_var_access->class_var->index;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_DEREF : {
                      SPVM_TYPE* src_type = SPVM_CHECK_get_type(compiler, op_assign_src);
                      
                      if (SPVM_TYPE_is_mulnum_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                        SPVM_FIELD* first_field = SPVM_LIST_get(src_type->basic_type->fields, 0);
                      
                        SPVM_TYPE* element_type = SPVM_CHECK_get_type(compiler, first_field->op_field);

                        SPVM_OPCODE opcode = {0};
                        
                        
                        assert(SPVM_TYPE_is_numeric_type(compiler, element_type->basic_type->id, element_type->dimension, element_type->flag));
                        int32_t call_stack_index_out;
                        if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DEREF_MULNUM_BYTE);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DEREF_MULNUM_SHORT);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DEREF_MULNUM_INT);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DEREF_MULNUM_LONG);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DEREF_MULNUM_FLOAT);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DEREF_MULNUM_DOUBLE);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                        }
                        else {
                          assert(0);
                        }

                        int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                        int32_t fields_length = src_type->basic_type->fields->length;
                        
                        opcode.operand0 = call_stack_index_out;
                        opcode.operand1 = call_stack_index_in;
                        int32_t operand3 = fields_length;
                        assert(operand3 < 0xFFFF);
                        opcode.operand3 = operand3;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {

                        SPVM_OPCODE opcode = {0};
                        
                        
                        int32_t call_stack_index_out;
                        switch (src_type->basic_type->id) {
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_DEREF_BYTE);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_DEREF_SHORT);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_DEREF_INT);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_DEREF_LONG);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_DEREF_FLOAT);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_DEREF_DOUBLE);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          }
                          default: {
                            assert(0);
                          }
                        }
                        
                        int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                        
                        opcode.operand0 = call_stack_index_out;
                        opcode.operand1 = call_stack_index_in;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else {
                        assert(0);
                      }
                      break;
                    }
                    case SPVM_OP_C_ID_CREATE_REF : {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      int32_t call_stack_index_in;
                      SPVM_TYPE* src_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                      if (SPVM_TYPE_is_mulnum_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                        
                        SPVM_FIELD* first_field = SPVM_LIST_get(src_type->basic_type->fields, 0);
                        assert(first_field);
                        
                        SPVM_TYPE* field_type = SPVM_CHECK_get_type(compiler, first_field->op_field);
                        assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                        
                        switch (field_type->basic_type->id) {
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_BYTE);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_SHORT);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_INT);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_LONG);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_FLOAT);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_DOUBLE);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          default:
                            assert(0);
                        }
                      }
                      else if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                        switch (src_type->basic_type->id) {
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_BYTE);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_SHORT);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_INT);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_LONG);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_FLOAT);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_DOUBLE);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          default:
                            assert(0);
                        }
                      }
                      else {
                        assert(0);
                      }
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_EXCEPTION_VAR : {
                      // VAR = EXCEPTION_VAR
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_EXCEPTION_VAR);

                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      
                      opcode.operand0 = call_stack_index_out;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
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
                      
                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      int32_t call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                      int32_t call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
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

                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      int32_t call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                      int32_t call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
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

                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      int32_t call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                      int32_t call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
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

                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      int32_t call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                      int32_t call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
                      // Check die
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                        break;
                      }
                      
                      break;
                    }
                    case SPVM_OP_C_ID_DIVIDE_UNSIGNED_INT : {

                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DIVIDE_UNSIGNED_INT);

                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      int32_t call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                      int32_t call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
                      // Check die
                      SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);                              
                      break;
                    }
                    case SPVM_OP_C_ID_DIVIDE_UNSIGNED_LONG : {

                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DIVIDE_UNSIGNED_LONG);

                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      int32_t call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                      int32_t call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
                      SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_REMAINDER : {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t call_stack_index_out;
                      int32_t call_stack_index_in1;
                      int32_t call_stack_index_in2;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REMAINDER_INT);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REMAINDER_LONG);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        default:
                          assert(0);
                      }
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                      // Check die
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                        break;
                      }
                      break;
                    }
                    case SPVM_OP_C_ID_REMAINDER_UNSIGNED_INT : {

                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REMAINDER_UNSIGNED_INT);

                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      int32_t call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                      int32_t call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
                      // Check die
                      SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);                              
                      break;
                    }
                    case SPVM_OP_C_ID_REMAINDER_UNSIGNED_LONG : {

                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REMAINDER_UNSIGNED_LONG);

                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      int32_t call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                      int32_t call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
                      SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_LEFT_SHIFT : {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t call_stack_index_in1;
                      int32_t call_stack_index_out;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LEFT_SHIFT_INT);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LEFT_SHIFT_LONG);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          break;
                        default:
                          assert(0);
                      }

                      int32_t call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_RIGHT_ARITHMETIC_SHIFT : {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t call_stack_index_in1;
                      int32_t call_stack_index_out;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_INT);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_LONG);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          break;
                        default:
                          assert(0);
                      }

                      int32_t call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_RIGHT_LOGICAL_SHIFT : {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t call_stack_index_out;
                      int32_t call_stack_index_in1;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_INT);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_LONG);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          break;
                        default:
                          assert(0);
                      }

                      int32_t call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_BIT_AND : {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t call_stack_index_out;
                      int32_t call_stack_index_in1;
                      int32_t call_stack_index_in2;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_AND_INT);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_AND_LONG);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        default:
                          assert(0);
                      }

                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_BIT_OR : {

                      SPVM_OPCODE opcode = {0};
                      
                      
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t call_stack_index_out;
                      int32_t call_stack_index_in1;
                      int32_t call_stack_index_in2;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_OR_INT);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_OR_LONG);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        default:
                          assert(0);
                      }

                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_BIT_XOR : {

                      SPVM_OPCODE opcode = {0};
                      
                      
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t call_stack_index_out;
                      int32_t call_stack_index_in1;
                      int32_t call_stack_index_in2;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_XOR_INT);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_XOR_LONG);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        default:
                          assert(0);
                      }

                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_BIT_NOT : {

                      SPVM_OPCODE opcode = {0};
                      

                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t call_stack_index_out;
                      int32_t call_stack_index_in;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_NOT_INT);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_NOT_LONG);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          break;
                        default:
                          assert(0);
                      }
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_PLUS : {

                      SPVM_OPCODE opcode = {0};
                      
                     
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t call_stack_index_out;
                      int32_t call_stack_index_in;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_INT);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_LONG);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_FLOAT);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_DOUBLE);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          break;
                        default:
                          assert(0);
                      }
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_COPY : {

                      SPVM_OPCODE opcode = {0};
                      
                     
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_COPY);
                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                      SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                      break;
                    }
                    case SPVM_OP_C_ID_MINUS : {

                      SPVM_OPCODE opcode = {0};
                      
                     
                      assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                      int32_t call_stack_index_out;
                      int32_t call_stack_index_in;
                      switch (type_dist->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEGATE_INT);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEGATE_LONG);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEGATE_FLOAT);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEGATE_DOUBLE);
                          call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          break;
                        default:
                          assert(0);
                      }
                      
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = call_stack_index_in;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_CONSTANT : {
                      SPVM_CONSTANT* constant = op_assign_src->uv.constant;

                      if (SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        

                        int32_t call_stack_index_out;
                        switch (type_dist->basic_type->id) {
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_CONSTANT_BYTE);
                            opcode.operand1 = (uint16_t)(uint8_t)constant->value.bval;
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_CONSTANT_INT);
                            opcode.operand1 = (uint32_t)constant->value.ival;
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_CONSTANT_LONG);
                            *(int64_t*)&opcode.operand1 = constant->value.lval;
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_CONSTANT_FLOAT);
                            opcode.operand1 = (uint32_t)constant->value.ival;
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_CONSTANT_DOUBLE);
                            *(double*)&opcode.operand1 = constant->value.dval;
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            break;
                          default:
                            assert(0);
                        }
                        
                        opcode.operand0 = call_stack_index_out;
                       
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (SPVM_TYPE_is_string_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_STRING);
                        
                        int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                        SPVM_CONSTANT* constant = op_assign_src->uv.constant;
                        
                        const char* constant_string_value = constant->value.oval;
                        int32_t constant_string_length = constant->string_length;
                        SPVM_CONSTANT_STRING* global_constant_string = SPVM_HASH_get(compiler->global_constant_string_symtable, constant_string_value, constant_string_length);
                        assert(global_constant_string);
                        
                        opcode.operand0 = call_stack_index_out;
                        
                        SPVM_CONSTANT_STRING* constant_string = SPVM_HASH_get(basic_type->constant_string_symtable, constant_string_value, constant_string_length);
                        assert(constant_string);
                        
                        assert(constant_string->index >= 0);
                        opcode.operand3 = constant_string->index;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                        
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
                          
                          int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_dist_term);
                          opcode.operand0 = call_stack_index_out;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                        }
                        else {
                          assert(0);
                        }
                      }
                      else {
                        SPVM_OPCODE opcode = {0};
                        int32_t throw_exception = 0;
                        int32_t call_stack_index_out;
                        int32_t call_stack_index_in;

                        call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_dist_term);
                        call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_src_term);
                        
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
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_OBJECT_TO_BYTE);
                            throw_exception = 1;
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_OBJECT_TO_BYTE);
                            throw_exception = 1;
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
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_OBJECT_TO_SHORT);
                            throw_exception = 1;
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_OBJECT_TO_SHORT);
                            throw_exception = 1;
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
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_OBJECT_TO_INT);
                            throw_exception = 1;
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_OBJECT_TO_INT);
                            throw_exception = 1;
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
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_OBJECT_TO_LONG);
                            throw_exception = 1;
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_OBJECT_TO_LONG);
                            throw_exception = 1;
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
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_OBJECT_TO_FLOAT);
                            throw_exception = 1;
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_OBJECT_TO_FLOAT);
                            throw_exception = 1;
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
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_OBJECT_TO_DOUBLE);
                            throw_exception = 1;
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_OBJECT_TO_DOUBLE);
                            throw_exception = 1;
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
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECKING);
                            opcode.operand2 = op_cast_type->uv.type->basic_type->id;
                            int32_t operand3 = op_cast_type->uv.type->dimension;
                            assert(operand3 < 0xFFFF);
                            opcode.operand3 = operand3;
                            throw_exception = 1;
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
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECKING);
                            opcode.operand2 = op_cast_type->uv.type->basic_type->id;
                            int32_t operand3 = op_cast_type->uv.type->dimension;
                            assert(operand3 < 0xFFFF);
                            opcode.operand3 = operand3;
                            throw_exception = 1;
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
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECKING);
                            opcode.operand2 = op_cast_type->uv.type->basic_type->id;
                            int32_t operand3 = op_cast_type->uv.type->dimension;
                            assert(operand3 < 0xFFFF);
                            opcode.operand3 = operand3;
                            throw_exception = 1;
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
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECKING);
                            opcode.operand2 = op_cast_type->uv.type->basic_type->id;
                            int32_t operand3 = op_cast_type->uv.type->dimension;
                            assert(operand3 < 0xFFFF);
                            opcode.operand3 = operand3;
                            throw_exception = 1;
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
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECKING);
                            opcode.operand2 = op_cast_type->uv.type->basic_type->id;
                            int32_t operand3 = op_cast_type->uv.type->dimension;
                            assert(operand3 < 0xFFFF);
                            opcode.operand3 = operand3;
                            throw_exception = 1;
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
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECKING);
                            opcode.operand2 = op_cast_type->uv.type->basic_type->id;
                            int32_t operand3 = op_cast_type->uv.type->dimension;
                            assert(operand3 < 0xFFFF);
                            opcode.operand3 = operand3;
                            throw_exception = 1;
                          }
                          else {
                            assert(0);
                          }
                        }
                        // To String
                        else if (SPVM_TYPE_is_string_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                          if (SPVM_TYPE_is_string_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            if (cast_type->flag & SPVM_NATIVE_C_TYPE_FLAG_MUTABLE && !(src_type->flag & SPVM_NATIVE_C_TYPE_FLAG_MUTABLE)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_CHECK_READ_ONLY);
                              throw_exception = 1;
                            }
                            else {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                            }
                          }
                          else if (SPVM_TYPE_is_byte_array_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_ARRAY_TO_STRING);
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECKING);
                            opcode.operand2 = op_cast_type->uv.type->basic_type->id;
                            int32_t operand3 = op_cast_type->uv.type->dimension;
                            assert(operand3 < 0xFFFF);
                            opcode.operand3 = operand3;
                            throw_exception = 1;
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
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECKING);
                            opcode.operand2 = op_cast_type->uv.type->basic_type->id;
                            int32_t operand3 = op_cast_type->uv.type->dimension;
                            assert(operand3 < 0xFFFF);
                            opcode.operand3 = operand3;
                            throw_exception = 1;
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

                            int32_t need_implicite_conversion = 0;
                            int32_t allow_narrowing_conversion = 0;
                            
                            int32_t runtime_assignability = SPVM_TYPE_can_assign(
                              compiler,
                              cast_type_basic_type_id, cast_type_dimension, cast_type_flag,
                              src_type_basic_type_id, src_type_dimension, src_type_flag,
                              &need_implicite_conversion, allow_narrowing_conversion
                            );
                            assert(need_implicite_conversion == 0);
                            
                            if (runtime_assignability) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                            }
                            else {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECKING);
                              opcode.operand2 = op_cast_type->uv.type->basic_type->id;
                            int32_t operand3 = op_cast_type->uv.type->dimension;
                            assert(operand3 < 0xFFFF);
                            opcode.operand3 = operand3;
                              throw_exception = 1;
                            }
                          }
                          else {
                            assert(0);
                          }
                        }

                        opcode.operand0 = call_stack_index_out;
                        opcode.operand1 = call_stack_index_in;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                        
                        if (throw_exception) {
                          SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                        }
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

                                int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                                int32_t call_stack_index_index = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);

                                opcode.operand0 = call_stack_index_out;
                                opcode.operand1 = call_stack_index_index;

                                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                                SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                                
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                SPVM_OPCODE opcode = {0};
                                
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY);

                                int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                                int32_t call_stack_index_index = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                                
                                opcode.operand0 = call_stack_index_out;
                                opcode.operand1 = call_stack_index_index;

                                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                                SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                                
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                SPVM_OPCODE opcode = {0};
                                

                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_INT_ARRAY);

                                int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                                int32_t call_stack_index_index = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);

                                opcode.operand0 = call_stack_index_out;
                                opcode.operand1 = call_stack_index_index;

                                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                                SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                                
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                SPVM_OPCODE opcode = {0};
                                

                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_LONG_ARRAY);

                                int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                                int32_t call_stack_index_index = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);

                                opcode.operand0 = call_stack_index_out;
                                opcode.operand1 = call_stack_index_index;

                                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                                
                                SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);

                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                SPVM_OPCODE opcode = {0};
                                

                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY);

                                int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                                int32_t call_stack_index_index = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);

                                opcode.operand0 = call_stack_index_out;
                                opcode.operand1 = call_stack_index_index;

                                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                                
                                SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);

                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                SPVM_OPCODE opcode = {0};
                                

                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY);
                                
                                int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                                int32_t call_stack_index_index = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);

                                opcode.operand0 = call_stack_index_out;
                                opcode.operand1 = call_stack_index_index;

                                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                                SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);

                                break;
                              }
                              default: {
                                if (SPVM_TYPE_is_mulnum_array_type(compiler, basic_type_id, type_dimension, type->flag)) {
                                  SPVM_OPCODE opcode = {0};
                                  

                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_MULNUM_ARRAY);

                                  int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                                  int32_t call_stack_index_index = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);

                                  opcode.operand0 = call_stack_index_out;
                                  opcode.operand1 = type->basic_type->id;
                                  opcode.operand2 = call_stack_index_index;

                                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                                  SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                                }
                                else {
                                  SPVM_OPCODE opcode = {0};
                                  

                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY);

                                  int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                                  int32_t call_stack_index_index = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);

                                  opcode.operand0 = call_stack_index_out;
                                  opcode.operand1 = type->basic_type->id;
                                  opcode.operand2 = call_stack_index_index;

                                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                                  SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                                }
                              }
                            }
                          }
                          else if (type_dimension > 1) {
                            SPVM_OPCODE opcode = {0};
                            

                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_MULDIM_ARRAY);

                            int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            int32_t call_stack_index_index = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);

                            opcode.operand0 = call_stack_index_out;
                            opcode.operand1 = type->basic_type->id;
                            opcode.operand2 = call_stack_index_index;
                            int32_t operand3 = type->dimension;
                            assert(operand3 < 0xFFFF);
                            opcode.operand3 = operand3;

                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                            SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                          }
                          else {
                            assert(0);
                          }
                        }
                        else {
                          SPVM_OPCODE opcode = {0};
                          

                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_OBJECT);
                          
                          int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                          
                          opcode.operand0 = call_stack_index_out;
                          opcode.operand1 = type->basic_type->id;
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
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
                      
                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      opcode.operand0 = call_stack_index_out;
                      opcode.operand1 = basic_type_id;
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                      SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_assign->line);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_EVAL_ERROR_ID : {
                      
                      SPVM_OPCODE opcode = {0};
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_EVAL_ERROR_ID);
                      
                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      opcode.operand0 = call_stack_index_out;
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_ITEMS : {
                      
                      SPVM_OPCODE opcode = {0};
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_ITEMS);
                      
                      int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                      opcode.operand0 = call_stack_index_out;
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_VAR : {
                      // Multi numeric type
                      if (SPVM_TYPE_is_mulnum_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        
                        SPVM_FIELD* first_field = SPVM_LIST_get(type_dist->basic_type->fields, 0);
                        assert(first_field);
                        
                        SPVM_TYPE* field_type = SPVM_CHECK_get_type(compiler, first_field->op_field);
                        assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                        
                        SPVM_OPCODE opcode = {0};
                        
                        
                        int32_t call_stack_index_out;
                        int32_t call_stack_index_in;
                        switch (field_type->basic_type->id) {
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_BYTE);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_SHORT);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_INT);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_LONG);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_FLOAT);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_DOUBLE);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          }
                          default:
                            assert(0);
                        }

                        int32_t fields_length = type_dist->basic_type->fields->length;
                        opcode.operand0 = call_stack_index_out;
                        opcode.operand1 = call_stack_index_in;
                        opcode.operand2 = fields_length;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      // Object type
                      else if (SPVM_TYPE_is_object_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                        int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                        int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);

                        opcode.operand0 = call_stack_index_out;
                        opcode.operand1 = call_stack_index_in;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                        
                      }
                      else if (SPVM_TYPE_is_ref_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_REF);
                        int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                        int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);

                        opcode.operand0 = call_stack_index_out;
                        opcode.operand1 = call_stack_index_in;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                        
                      }
                      // Numeric type
                      else {
                        SPVM_OPCODE opcode = {0};
                        
                        
                        assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                        
                        int32_t call_stack_index_out;
                        int32_t call_stack_index_in;
                        switch (type_dist->basic_type->id) {
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_BYTE);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_SHORT);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_INT);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_LONG);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_FLOAT);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_DOUBLE);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          }
                          default: {
                            assert(0);
                          }
                        }

                        opcode.operand0 = call_stack_index_out;
                        opcode.operand1 = call_stack_index_in;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      break;
                    }
                    case SPVM_OP_C_ID_NUMERIC_EQ : {
                      if (op_assign_src->first->id == SPVM_OP_C_ID_UNDEF || op_assign_src->last->id == SPVM_OP_C_ID_UNDEF) {
                        SPVM_OPCODE opcode = {0};
                        

                        int32_t call_stack_index_in;

                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_UNDEF);
                        if (op_assign_src->first->id == SPVM_OP_C_ID_UNDEF) {
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          
                          opcode.operand1 = call_stack_index_in;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                        }
                        else {
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          
                          opcode.operand1 = call_stack_index_in;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                        }
                      }
                      else {
                        SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                        
                        SPVM_OPCODE opcode = {0};
                        
                        
                        int32_t call_stack_index_in1;
                        int32_t call_stack_index_in2;
                        if (SPVM_TYPE_is_numeric_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                          if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                            assert(0);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                            assert(0);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_EQ_INT);
                            call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                            call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_EQ_LONG);
                            call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                            call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_EQ_FLOAT);
                            call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                            call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_EQ_DOUBLE);
                            call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                            call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          }
                          else {
                            assert(0);
                          }
                        }
                        else if (SPVM_TYPE_is_object_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_EQ_OBJECT);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                        }
                        else if (SPVM_TYPE_is_ref_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_EQ_REF);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                        }
                        else {
                          assert(0);
                        }
                        
                        opcode.operand1 = call_stack_index_in1;
                        opcode.operand2 = call_stack_index_in2;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      break;
                    }
                    case SPVM_OP_C_ID_NUMERIC_NE : {
                      if (op_assign_src->first->id == SPVM_OP_C_ID_UNDEF ||op_assign_src->last->id == SPVM_OP_C_ID_UNDEF) {
                        SPVM_OPCODE opcode = {0};
                        
                        
                        int32_t call_stack_index_in;

                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_NOT_UNDEF);
                        if (op_assign_src->first->id == SPVM_OP_C_ID_UNDEF) {
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          
                          opcode.operand1 = call_stack_index_in;
                        }
                        else {
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          
                          opcode.operand1 = call_stack_index_in;
                        }
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else {
                        SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);

                        SPVM_OPCODE opcode = {0};
                        
                        
                        int32_t call_stack_index_in1;
                        int32_t call_stack_index_in2;
                        if (SPVM_TYPE_is_numeric_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                          if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                            assert(0);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                            assert(0);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NE_INT);
                            call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                            call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NE_LONG);
                            call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                            call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NE_FLOAT);
                            call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                            call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          }
                          else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NE_DOUBLE);
                            call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                            call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          }
                          else {
                            assert(0);
                          }
                        }
                        else if (SPVM_TYPE_is_object_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NE_OBJECT);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                        }
                        else if (SPVM_TYPE_is_ref_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NE_REF);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                        }
                        else {
                          assert(0);
                        }
                        
                        opcode.operand1 = call_stack_index_in1;
                        opcode.operand2 = call_stack_index_in2;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      break;
                    }
                    case SPVM_OP_C_ID_NUMERIC_GT : {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);

                      int32_t call_stack_index_in1;
                      int32_t call_stack_index_in2;
                      switch (operand_type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GT_INT);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GT_LONG);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GT_FLOAT);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GT_DOUBLE);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        default:
                          assert(0);
                      }
                      
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_NUMERIC_GE : {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);

                      int32_t call_stack_index_in1;
                      int32_t call_stack_index_in2;
                      switch (operand_type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GE_INT);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GE_LONG);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GE_FLOAT);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GE_DOUBLE);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        default:
                          assert(0);
                      }
                      
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_NUMERIC_LT : {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);

                      int32_t call_stack_index_in1;
                      int32_t call_stack_index_in2;
                      switch (operand_type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LT_INT);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LT_LONG);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LT_FLOAT);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LT_DOUBLE);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        default:
                          assert(0);
                      }
                      
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_NUMERIC_LE : {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);

                      int32_t call_stack_index_in1;
                      int32_t call_stack_index_in2;
                      switch (operand_type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LE_INT);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LE_LONG);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LE_FLOAT);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LE_DOUBLE);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        default:
                          assert(0);
                      }
                      
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_NUMERIC_CMP : {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_assign_src->first);

                      int32_t call_stack_index_in1;
                      int32_t call_stack_index_in2;
                      switch (operand_type->basic_type->id) {
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CMP_INT);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CMP_LONG);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CMP_FLOAT);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CMP_DOUBLE);
                          call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                          break;
                        default:
                          assert(0);
                      }
                      
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      break;
                    }
                    case SPVM_OP_C_ID_STRING_EQ:
                    case SPVM_OP_C_ID_STRING_NE:
                    case SPVM_OP_C_ID_STRING_GT:
                    case SPVM_OP_C_ID_STRING_GE:
                    case SPVM_OP_C_ID_STRING_LT:
                    case SPVM_OP_C_ID_STRING_LE:
                    case SPVM_OP_C_ID_STRING_CMP:
                    {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      switch (op_assign_src->id) {
                        case SPVM_OP_C_ID_STRING_EQ: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_STRING_EQ);
                          break;
                        }
                        case SPVM_OP_C_ID_STRING_NE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_STRING_NE);
                          break;
                        }
                        case SPVM_OP_C_ID_STRING_GT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_STRING_GT);
                          break;
                        }
                        case SPVM_OP_C_ID_STRING_GE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_STRING_GE);
                          break;
                        }
                        case SPVM_OP_C_ID_STRING_LT: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_STRING_LT);
                          break;
                        }
                        case SPVM_OP_C_ID_STRING_LE: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_STRING_LE);
                          break;
                        }
                        case SPVM_OP_C_ID_STRING_CMP: {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_STRING_CMP);
                          break;
                        }
                        default: {
                          assert(0);
                        }
                      }
                      
                      int32_t call_stack_index_in1 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                      int32_t call_stack_index_in2 = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->last);
                      
                      opcode.operand1 = call_stack_index_in1;
                      opcode.operand2 = call_stack_index_in2;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
                      break;
                    }
                    case  SPVM_OP_C_ID_BOOL: {
                      SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, op_assign_src->first);
                      
                      if (op_assign_src->first->id != SPVM_OP_C_ID_IF) {

                        SPVM_OPCODE opcode = {0};
                        
                        
                        int32_t call_stack_index_in;
                        if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                          if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                            assert(0);
                          }
                          else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                            assert(0);
                          }
                          else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BOOL_CONVERSION_INT);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          }
                          else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BOOL_CONVERSION_LONG);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          }
                          else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BOOL_CONVERSION_FLOAT);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          }
                          else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BOOL_CONVERSION_DOUBLE);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                          }
                          else {
                            assert(0);
                          }
                        }
                        else if (SPVM_TYPE_is_bool_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BOOL_CONVERSION_BOOL_OBJECT);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                        }
                        else if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BOOL_CONVERSION_OBJECT);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                        }
                        else if (SPVM_TYPE_is_ref_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BOOL_CONVERSION_REF);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                        }
                        else {
                          assert(0);
                        }
                        opcode.operand1 = call_stack_index_in;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      
                      break;
                    }
                    case SPVM_OP_C_ID_ISA:
                    case SPVM_OP_C_ID_ISA_ERROR:
                    case SPVM_OP_C_ID_IS_TYPE:
                    case SPVM_OP_C_ID_IS_ERROR:
                    {
                      int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                      
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
                      
                      opcode.operand1 = call_stack_index_in;
                      
                      opcode.operand2 = type->basic_type->id;
                      int32_t operand3 = type->dimension;
                      assert(operand3 < 0xFFFF);
                      opcode.operand3 = operand3;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_CAN: {
                      SPVM_OP* op_var = op_assign_src->first;
                      int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_var);
                      
                      SPVM_TYPE* invocant_decl_type = SPVM_CHECK_get_type(compiler, op_var);
                      SPVM_BASIC_TYPE* invocant_decl_basic_type = invocant_decl_type->basic_type;
                      SPVM_OP* op_name_decl_method = op_assign_src->last;
                      
                      const char* decl_method_name = op_name_decl_method->uv.name;
                      SPVM_METHOD* decl_method = SPVM_HASH_get(invocant_decl_basic_type->method_symtable, decl_method_name, strlen(decl_method_name));
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CAN);
                      
                      opcode.operand0 = call_stack_index_in;
                      opcode.operand1 = invocant_decl_basic_type->id;
                      opcode.operand2 = decl_method->index;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_WARN: {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_WARN);
                      
                      int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                      opcode.operand0 = call_stack_index_in;
                      opcode.operand1 = op_assign->line;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_PRINT: {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PRINT);
                      
                      int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                      opcode.operand0 = call_stack_index_in;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_SAY: {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SAY);
                      
                      int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                      opcode.operand0 = call_stack_index_in;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_MAKE_READ_ONLY: {
                      
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MAKE_READ_ONLY);
                      
                      int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src->first);
                      opcode.operand0 = call_stack_index_in;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
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
                        
                        int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_var_dist);
                        int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_var_src);

                        opcode.operand0 = call_stack_index_out;
                        opcode.operand1 = call_stack_index_in;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (SPVM_TYPE_is_short_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_SHORT);
                        
                        int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_var_dist);
                        int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_var_src);

                        opcode.operand0 = call_stack_index_out;
                        opcode.operand1 = call_stack_index_in;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (SPVM_TYPE_is_int_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_INT);
                        
                        int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_var_dist);
                        int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_var_src);

                        opcode.operand0 = call_stack_index_out;
                        opcode.operand1 = call_stack_index_in;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (SPVM_TYPE_is_long_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_LONG);
                        
                        int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_var_dist);
                        int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_var_src);

                        opcode.operand0 = call_stack_index_out;
                        opcode.operand1 = call_stack_index_in;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (SPVM_TYPE_is_float_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_FLOAT);
                        
                        int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_var_dist);
                        int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_var_src);

                        opcode.operand0 = call_stack_index_out;
                        opcode.operand1 = call_stack_index_in;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (SPVM_TYPE_is_double_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_DOUBLE);
                        
                        int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_var_dist);
                        int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_var_src);

                        opcode.operand0 = call_stack_index_out;
                        opcode.operand1 = call_stack_index_in;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (SPVM_TYPE_is_object_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                        
                        int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_var_dist);
                        int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_var_src);

                        opcode.operand0 = call_stack_index_out;
                        opcode.operand1 = call_stack_index_in;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (SPVM_TYPE_is_ref_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_OPCODE opcode = {0};
                        
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_REF);
                        
                        int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_var_dist);
                        int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_var_src);

                        opcode.operand0 = call_stack_index_out;
                        opcode.operand1 = call_stack_index_in;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (SPVM_TYPE_is_mulnum_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                        SPVM_FIELD* first_field = SPVM_LIST_get(type_dist->basic_type->fields, 0);
                        assert(first_field);
                        
                        SPVM_TYPE* field_type = SPVM_CHECK_get_type(compiler, first_field->op_field);
                        assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                        
                        SPVM_OPCODE opcode = {0};
                        

                        int32_t call_stack_index_out;
                        int32_t call_stack_index_in;
                        switch (field_type->basic_type->id) {
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_BYTE);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_SHORT);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_INT);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_LONG);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_FLOAT);
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            break;
                          }
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                            call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                            call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_DOUBLE);
                            break;
                          }
                          default: {
                            assert(0);
                          }
                        }

                        int32_t fields_length = type_dist->basic_type->fields->length;
                        opcode.operand0 = call_stack_index_out;
                        opcode.operand1 = call_stack_index_in;
                        opcode.operand2 = fields_length;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
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
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  // CLASS_VAR_ACCESS = $var
                  else {
                    SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, op_class_var_access);

                    SPVM_OPCODE opcode = {0};
                    
                    
                    int32_t call_stack_index_in;
                    if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_OBJECT);
                      call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                    }
                    else {
                      if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_BYTE);
                        call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                      }
                      else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_SHORT);
                        call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                      }
                      else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_INT);
                        call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                      }
                      else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_LONG);
                        call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                      }
                      else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_FLOAT);
                        call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                      }
                      else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_DOUBLE);
                        call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                      }
                      else {
                        assert(0);
                      }
                    }
                                      
                    opcode.operand0 = class_var_access->class_var->current_basic_type->id;
                    opcode.operand1 = class_var_access->class_var->index;
                    opcode.operand2 = call_stack_index_in;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                }
                // $$var_ref = $var
                else if (op_assign_dist->id == SPVM_OP_C_ID_DEREF) {
                  SPVM_OP* op_deref = op_assign_dist;

                  SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, op_deref->first);

                  SPVM_OPCODE opcode = {0};
                  
                  
                  assert(SPVM_TYPE_is_numeric_ref_type(compiler, type->basic_type->id, type->dimension, type->flag));
                  int32_t call_stack_index_in;
                  if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_DEREF_BYTE);
                    call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                  }
                  else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_DEREF_SHORT);
                    call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                  }
                  else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_DEREF_INT);
                    call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                  }
                  else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_DEREF_LONG);
                    call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                  }
                  else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_DEREF_FLOAT);
                    call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                  }
                  else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_DEREF_DOUBLE);
                    call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                  }
                  else {
                    assert(0);
                  }
                  
                  int32_t call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_dist);
                  
                  opcode.operand0 = call_stack_index_out;
                  opcode.operand1 = call_stack_index_in;
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                }
                // $@ = $var
                else if (op_assign_dist->id == SPVM_OP_C_ID_EXCEPTION_VAR) {
                  
                  SPVM_TYPE* src_type = SPVM_CHECK_get_type(compiler, op_assign_src);
                  
                  if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                    // EXCEPTION_VAR = undef
                    SPVM_OPCODE opcode = {0};
                    
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR_UNDEF);
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else {
                    // EXCEPTION_VAR = $var
                    SPVM_OPCODE opcode = {0};
                    
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR);
                    int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                    opcode.operand0 = call_stack_index_in;
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                }
                // $array->[$index] = $var
                else if (op_assign_dist->id == SPVM_OP_C_ID_ARRAY_ACCESS) {
                  
                  // $VAR_ARRAY->[$VAR_INDEX] = $VAR_TERM
                  
                  SPVM_OP* op_array_access = op_assign_dist;
                  SPVM_OP* op_term_array = op_array_access->first;
                  SPVM_OP* op_term_index = op_array_access->last;

                  SPVM_TYPE* array_type = SPVM_CHECK_get_type(compiler, op_term_array);
                  int32_t array_type_dimension = array_type->dimension;
                  int32_t array_basic_type_id = array_type->basic_type->id;
                  int32_t array_basic_type_category = array_type->basic_type->category;

                  if (SPVM_TYPE_is_any_object_array_type(compiler, array_type->basic_type->id, array_type->dimension, array_type->flag)) {
                    SPVM_TYPE* src_type = SPVM_CHECK_get_type(compiler, op_assign_src);

                    if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_UNDEF);
                      
                      int32_t call_stack_index_array = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_array);
                      int32_t call_stack_index_index = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_index);
                      
                      opcode.operand0 = call_stack_index_array;
                      opcode.operand1 = call_stack_index_index;
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    }
                    else {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE);
                      int32_t call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                      
                      int32_t call_stack_index_array = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_array);
                      int32_t call_stack_index_index = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_index);
                      
                      opcode.operand0 = call_stack_index_array;
                      opcode.operand1 = call_stack_index_index;
                      opcode.operand2 = call_stack_index_in;
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                      SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_cur->line);
                    }
                  }
                  else if (SPVM_TYPE_is_mulnum_array_type(compiler, array_type->basic_type->id, array_type->dimension, array_type->flag)) {
                    SPVM_FIELD* first_field = SPVM_LIST_get(array_type->basic_type->fields, 0);
                  
                    SPVM_TYPE* element_type = SPVM_CHECK_get_type(compiler, first_field->op_field);

                    SPVM_OPCODE opcode = {0};
                    
                    
                    assert(SPVM_TYPE_is_numeric_type(compiler, element_type->basic_type->id, element_type->dimension, element_type->flag));
                    int32_t call_stack_index_in;
                    if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_BYTE);
                      call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                    }
                    else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_SHORT);
                      call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                    }
                    else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_INT);
                      call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                    }
                    else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_LONG);
                      call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                    }
                    else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FLOAT);
                      call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                    }
                    else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_DOUBLE);
                      call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                    }
                    else {
                      assert(0);
                    }

                    int32_t call_stack_index_array = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_array);
                    int32_t call_stack_index_index = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_index);
                    int32_t fields_length = array_type->basic_type->fields->length;
                    
                    opcode.operand0 = call_stack_index_array;
                    opcode.operand1 = call_stack_index_index;
                    opcode.operand2 = call_stack_index_in;
                    int32_t operand3 = fields_length;
                    assert(operand3 < 0xFFFF);
                    opcode.operand3 = operand3;

                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                    SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_cur->line);
                  }
                  else {
                  
                    SPVM_TYPE* element_type = SPVM_CHECK_get_type(compiler, op_assign_src);

                    if (SPVM_TYPE_is_undef_type(compiler, element_type->basic_type->id, element_type->dimension, element_type->flag)) {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_UNDEF);
                      
                      int32_t call_stack_index_array = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_array);
                      int32_t call_stack_index_index = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_index);
                      
                      opcode.operand0 = call_stack_index_array;
                      opcode.operand1 = call_stack_index_index;
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                      SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_cur->line);
                    }
                    else {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      int32_t call_stack_index_in;
                      if (SPVM_TYPE_is_numeric_type(compiler, element_type->basic_type->id, element_type->dimension, element_type->flag)) {
                        if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_BYTE);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_SHORT);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_INT);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_LONG);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_FLOAT);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_DOUBLE);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
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
                        call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                      }
                      
                      int32_t call_stack_index_array = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_array);
                      int32_t call_stack_index_index = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_index);
                      
                      opcode.operand0 = call_stack_index_array;
                      opcode.operand1 = call_stack_index_index;
                      opcode.operand2 = call_stack_index_in;
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                      SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_cur->line);
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
                    
                    int32_t call_stack_index_in;
                    switch (src_type->basic_type->id) {
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_BYTE);
                        call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_SHORT);
                        call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_INT);
                        call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_LONG);
                        call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_FLOAT);
                        call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_DOUBLE);
                        call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                        break;
                      }
                      default: {
                        assert(0);
                      }
                    }

                    int32_t call_stack_index_invocant = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);
                    int32_t field_offset = field->index;

                    opcode.operand0 = call_stack_index_invocant;
                    opcode.operand1 = call_stack_index_in;
                    opcode.operand2 = field_offset;

                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (SPVM_TYPE_is_mulnum_type(compiler, invocant_type->basic_type->id, invocant_type->dimension, invocant_type->flag)) {
                    SPVM_OPCODE opcode = {0};
                    
                    
                    assert(SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag));
                    int32_t call_stack_index_out;
                    int32_t call_stack_index_in;
                    if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_BYTE);
                      call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);
                      call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                    }
                    else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_SHORT);
                      call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);
                      call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                    }
                    else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_INT);
                      call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);
                      call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                    }
                    else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_LONG);
                      call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);
                      call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                    }
                    else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_FLOAT);
                      call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);
                      call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                    }
                    else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DOUBLE);
                      call_stack_index_out = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);
                      call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                    }
                    else {
                      assert(0);
                    }
                    
                    SPVM_FIELD* field = field_access->field;
                    int32_t field_offset = field->index;
                    
                    opcode.operand0 = call_stack_index_out;
                    opcode.operand1 = call_stack_index_in;
                    opcode.operand2 = field_offset;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else {
                    if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                      SPVM_OPCODE opcode = {0};
                      
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_UNDEF);
                      
                      int32_t call_stack_index_invocant = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);

                      SPVM_FIELD* field = field_access->field;
                      
                      opcode.operand0 = call_stack_index_invocant;
                      opcode.operand2 = field->current_basic_type->id;
                      opcode.operand3 = (uint16_t)field->index;
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                      SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_cur->line);
                    }
                    else {
                      SPVM_OPCODE opcode = {0};
                      
                      
                      int32_t call_stack_index_in;
                      if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                        if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_BYTE);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                        }
                        else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_SHORT);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                        }
                        else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_INT);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                        }
                        else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_LONG);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                        }
                        else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_FLOAT);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                        }
                        else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE);
                          call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                        }
                        else {
                          assert(0);
                        }
                      }
                      else if (SPVM_TYPE_is_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_OBJECT);
                        call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                      }
                      else {
                        assert(0);
                      }
                      
                      int32_t call_stack_index_invocant = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);

                      SPVM_FIELD* field = field_access->field;
                      
                      opcode.operand0 = call_stack_index_invocant;
                      opcode.operand1 = call_stack_index_in;
                      opcode.operand2 = field->current_basic_type->id;
                      opcode.operand3 = (uint16_t)field->index;
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                      SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_cur->line);
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
                  
                  
                  int32_t call_stack_index_in;
                  if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_BYTE);
                    call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                  }
                  else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_SHORT);
                    call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                  }
                  else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_INT);
                    call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                  }
                  else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_LONG);
                    call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                  }
                  else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_FLOAT);
                    call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                  }
                  else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_DOUBLE);
                    call_stack_index_in = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_assign_src);
                  }
                  else {
                    assert(0);
                  }
                  
                  int32_t call_stack_index_invocant = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_invocant);
                  int32_t call_stack_index_index = SPVM_OPCODE_BUILDER_get_call_stack_index(compiler, op_term_index);

                  int32_t fields_length = array_basic_type->fields->length;
                  int32_t field_offset = field->index;
                  
                  opcode.operand0 = call_stack_index_invocant;
                  opcode.operand1 = call_stack_index_index;
                  opcode.operand2 = call_stack_index_in;
                  int32_t operand3 = (field_offset << 8) + (fields_length - 1);
                  assert(operand3 < 0xFFFF);
                  opcode.operand3 = operand3;
                  
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                  SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(compiler, opcode_array, eval_block_stack_goto_opcode_rel_index->length, unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, method->op_method, op_cur->line);
                }
                else {
                  assert(0);
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

      SPVM_OPCODE opcode = {0};
      
      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode,  SPVM_OPCODE_C_ID_END_METHOD);
      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

      method->opcodes_length = opcode_array->length - method->opcodes_base_address_id;
      
      method->mortal_stack_length = call_stack_indexs_stack_top + 1;
      
      // Free list
      SPVM_LIST_free(unresolved_if_eq_or_if_ne_opcode_rel_index_stack);
      SPVM_LIST_free(if_block_stack_goto_end_opcode_rel_index);
      SPVM_LIST_free(loop_block_stack_goto_opcode_rel_index);
      SPVM_LIST_free(unresolved_last_opcode_rel_index_stack);
      SPVM_LIST_free(unresolved_break_opcode_rel_index_stack);
      SPVM_LIST_free(unresolved_next_opcode_rel_index_stack);
      SPVM_LIST_free(eval_block_stack_goto_opcode_rel_index);
      SPVM_LIST_free(unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack);
      SPVM_LIST_free(unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack);
      SPVM_LIST_free(unresolved_return_opcode_rel_index_stack);
      SPVM_LIST_free(switch_stack_switch_info);
      SPVM_LIST_free(loop_block_stack_next_base);
      SPVM_LIST_free(loop_block_stack_last_base);
      SPVM_LIST_free(switch_block_stack_break_base);
      SPVM_LIST_free(call_stack_indexs_stack);
      SPVM_LIST_free(block_stack_call_stack_index_top);
    }
  }
  
#ifdef SPVM_DEBUG_COMPILE
  fprintf(stderr, "\n[Opcodes]\n");
  SPVM_DUMPER_dump_basic_types_opcode_array(compiler, compiler->basic_types);
#endif

}

void SPVM_OPCODE_BUILDER_set_opcode_id(SPVM_COMPILER* compiler, SPVM_OPCODE* opcode, int32_t opcode_id) {
  opcode->id = opcode_id;
}

void SPVM_OPCODE_BUILDER_push_unresolved_goto_end_of_eval_or_end_of_method_on_exception(
  SPVM_COMPILER* compiler,
  SPVM_OPCODE_ARRAY* opcode_array,
  int32_t in_eval_block,
  SPVM_LIST* unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack,
  SPVM_LIST* unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack,
  SPVM_OP* op_method,
  int32_t line
)
{
  SPVM_METHOD* method = op_method->uv.method;
  int32_t method_opcodes_base_address_id = method->opcodes_base_address_id;
  
  if (in_eval_block) {
    SPVM_OPCODE opcode = {0};
    
    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GOTO_END_OF_EVAL_ON_EXCEPTION);
    
    opcode.operand2 = line;
    
    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
    
    int32_t goto_end_of_eval_on_exception_opcode_rel_index = opcode_array->length - 1 - method_opcodes_base_address_id;
    
    SPVM_LIST_push(unresolved_goto_end_of_eval_on_exception_opcode_rel_index_stack, (void*)(intptr_t)goto_end_of_eval_on_exception_opcode_rel_index);
  }
  else {
    SPVM_OPCODE opcode = {0};
    
    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GOTO_END_OF_METHOD_ON_EXCEPTION);
    opcode.operand2 = line;
    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
    
    int32_t goto_end_of_method_on_exception_opcode_rel_index = opcode_array->length - 1 - method_opcodes_base_address_id;
    
    SPVM_LIST_push(unresolved_goto_end_of_method_on_exception_opcode_rel_index_stack, (void*)(intptr_t)(goto_end_of_method_on_exception_opcode_rel_index));
  }
}

int32_t SPVM_OPCODE_BUILDER_get_call_stack_index(SPVM_COMPILER* compiler, SPVM_OP* op) {
  (void)compiler;
  
  switch (op->id) {
    case SPVM_OP_C_ID_BOOL:
    case SPVM_OP_C_ID_NUMERIC_EQ:
    case SPVM_OP_C_ID_NUMERIC_NE:
    case SPVM_OP_C_ID_NUMERIC_GT:
    case SPVM_OP_C_ID_NUMERIC_GE:
    case SPVM_OP_C_ID_NUMERIC_LT:
    case SPVM_OP_C_ID_NUMERIC_LE:
    case SPVM_OP_C_ID_NUMERIC_CMP:
    case SPVM_OP_C_ID_STRING_EQ:
    case SPVM_OP_C_ID_STRING_NE:
    case SPVM_OP_C_ID_STRING_GT:
    case SPVM_OP_C_ID_STRING_GE:
    case SPVM_OP_C_ID_STRING_LT:
    case SPVM_OP_C_ID_STRING_LE:
    case SPVM_OP_C_ID_STRING_CMP:
    case SPVM_OP_C_ID_ISA:
    case SPVM_OP_C_ID_ISA_ERROR:
    case SPVM_OP_C_ID_IS_TYPE:
    case SPVM_OP_C_ID_IS_ERROR:
    case SPVM_OP_C_ID_IS_COMPILE_TYPE:
    case SPVM_OP_C_ID_ISWEAK_FIELD:
    case SPVM_OP_C_ID_CAN:
    {
      return 0;
    }
    default: {
      SPVM_OP* op_var;
      if (op->id == SPVM_OP_C_ID_VAR) {
        op_var = op;
      }
      else if (op->id == SPVM_OP_C_ID_ASSIGN) {
        if (op->first->id == SPVM_OP_C_ID_VAR || op->first->id == SPVM_OP_C_ID_ASSIGN) {
          op_var = SPVM_OPCODE_BUILDER_get_returned_op_var(compiler, op->first);
        }
        else if (op->last->id == SPVM_OP_C_ID_VAR || op->last->id == SPVM_OP_C_ID_ASSIGN) {
          op_var = SPVM_OPCODE_BUILDER_get_returned_op_var(compiler, op->last);
        }
        else {
          assert(0);
        }
      }
      else if (op->id == SPVM_OP_C_ID_SEQUENCE) {
        op_var = SPVM_OPCODE_BUILDER_get_returned_op_var(compiler, op->last);
      }
      else if (op->id == SPVM_OP_C_ID_CREATE_REF) {
        op_var = SPVM_OPCODE_BUILDER_get_returned_op_var(compiler, op->first);
      }
      else if (op->id == SPVM_OP_C_ID_DEREF) {
        op_var = SPVM_OPCODE_BUILDER_get_returned_op_var(compiler, op->first);
      }
      else {
        spvm_warn("Unexpcted op:%s", SPVM_OP_get_op_name(compiler, op->id));
        assert(0);
      }
      
      return op_var->uv.var->var_decl->call_stack_index;
    }
  }
  
  return -1;
}

SPVM_OP* SPVM_OPCODE_BUILDER_get_returned_op_var(SPVM_COMPILER* compiler, SPVM_OP* op) {
  (void)compiler;
  
  SPVM_OP* op_var;
  if (op->id == SPVM_OP_C_ID_VAR) {
    op_var = op;
  }
  else if (op->id == SPVM_OP_C_ID_ASSIGN) {
    if (op->first->id == SPVM_OP_C_ID_VAR || op->first->id == SPVM_OP_C_ID_ASSIGN) {
      op_var = SPVM_OPCODE_BUILDER_get_returned_op_var(compiler, op->first);
    }
    else if (op->last->id == SPVM_OP_C_ID_VAR || op->last->id == SPVM_OP_C_ID_ASSIGN) {
      op_var = SPVM_OPCODE_BUILDER_get_returned_op_var(compiler, op->last);
    }
    else {
      assert(0);
    }
  }
  else if (op->id == SPVM_OP_C_ID_SEQUENCE) {
    op_var = SPVM_OPCODE_BUILDER_get_returned_op_var(compiler, op->last);
  }
  else if (op->id == SPVM_OP_C_ID_CREATE_REF) {
    op_var = SPVM_OPCODE_BUILDER_get_returned_op_var(compiler, op->first);
  }
  else if (op->id == SPVM_OP_C_ID_DEREF) {
    op_var = SPVM_OPCODE_BUILDER_get_returned_op_var(compiler, op->first);
  }
  else {
    spvm_warn("Unexpcted op:%s", SPVM_OP_get_op_name(compiler, op->id));
    assert(0);
  }
  
  return op_var;
}

