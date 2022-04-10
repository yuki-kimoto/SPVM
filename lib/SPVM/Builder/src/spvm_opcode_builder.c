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
#include "spvm_type.h"
#include "spvm_type.h"
#include "spvm_list.h"
#include "spvm_method.h"
#include "spvm_var.h"
#include "spvm_var_decl.h"
#include "spvm_allocator.h"
#include "spvm_class.h"
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

void SPVM_OPCODE_BUILDER_set_opcode_id(SPVM_COMPILER* compiler, SPVM_OPCODE* opcode, int32_t opcode_id) {
  opcode->id = opcode_id;
}

void SPVM_OPCODE_BUILDER_push_if_die(
  SPVM_COMPILER* compiler,
  SPVM_OPCODE_ARRAY* opcode_array,
  SPVM_LIST* push_eval_opcode_rel_index_stack,
  SPVM_LIST* if_die_catch_goto_opcode_rel_index_stack,
  SPVM_LIST* if_die_return_goto_opcode_rel_index_stack,
  SPVM_OP* op_method,
  int32_t line
)
{
  SPVM_METHOD* method = op_method->uv.method;
  int32_t method_opcodes_base_id = method->opcodes_base_id;
  
  if (push_eval_opcode_rel_index_stack->length > 0) {
    SPVM_OPCODE opcode;
    memset(&opcode, 0, sizeof(SPVM_OPCODE));
    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IF_EXCEPTION_CATCH);
    
    opcode.operand1 = method->rel_id;
    opcode.operand2 = line;
    
    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
    
    int32_t if_die_catch_opcode_rel_index = opcode_array->length - 1 - method_opcodes_base_id;
    
    SPVM_LIST_push(if_die_catch_goto_opcode_rel_index_stack, (void*)(intptr_t)if_die_catch_opcode_rel_index);
  }
  else {
    SPVM_OPCODE opcode;
    memset(&opcode, 0, sizeof(SPVM_OPCODE));
    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IF_EXCEPTION_RETURN);
    opcode.operand1 = method->rel_id;
    opcode.operand2 = line;
    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

    int32_t if_die_return_opcode_rel_index = opcode_array->length - 1 - method_opcodes_base_id;
    
    SPVM_LIST_push(if_die_return_goto_opcode_rel_index_stack, (void*)(intptr_t)(if_die_return_opcode_rel_index));
  }
}

void SPVM_OPCODE_BUILDER_build_opcode_array(SPVM_COMPILER* compiler) {
  
  // Operation code
  SPVM_OPCODE_ARRAY* opcode_array = compiler->opcode_array;
  
  {
    int32_t class_index;
    for (class_index = compiler->cur_class_base; class_index < compiler->classes->length; class_index++) {
      SPVM_CLASS* class = SPVM_LIST_get(compiler->classes, class_index);
      SPVM_LIST* methods = class->methods;
      {
        int32_t method_index;
        for (method_index = 0; method_index < methods->length; method_index++) {
          SPVM_METHOD* method = SPVM_LIST_get(methods, method_index);
          
          // Check sub information
          assert(method->id > -1);
          assert(method->op_name);
          assert(method->return_type);
          assert(method->class->module_file);
          
          if (method->flag & SPVM_METHOD_C_FLAG_NATIVE) {
            continue;
          }

          // opcode index stack for if start
          SPVM_LIST* if_eq_or_if_ne_goto_opcode_rel_index_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
          
          // opcode index stack for if end
          SPVM_LIST* if_block_end_goto_opcode_rel_index_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
          
          // opcode index stack for loop start
          SPVM_LIST* loop_first_goto_opcode_rel_index_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
          
          // opcode index stack for last
          SPVM_LIST* last_goto_opcode_rel_index_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);

          // opcode index stack for break
          SPVM_LIST* break_goto_opcode_rel_index_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
          
          // opcode index stack for next
          SPVM_LIST* next_goto_opcode_rel_index_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
          
          // opcode index stack for eval start
          SPVM_LIST* push_eval_opcode_rel_index_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
          
          // IF_EXCEPTION_CATCH opcode index stack
          SPVM_LIST* if_die_catch_goto_opcode_rel_index_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);

          // IF_EXCEPTION_RETURN opcode index stack
          SPVM_LIST* if_die_return_goto_opcode_rel_index_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);

          // RETURN goto opcode index stack
          SPVM_LIST* return_goto_opcode_rel_index_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
          
          // Switch stack
          SPVM_LIST* switch_info_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
          
          // Block stack
          SPVM_LIST* op_block_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
          
          // next block base stack
          SPVM_LIST* next_block_base_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
          
          // last block base stack
          SPVM_LIST* last_block_base_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);

          // break block base stack
          SPVM_LIST* break_block_base_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
          
          // Mortal variable stack
          SPVM_LIST* mortal_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
          
          // Mortal variable base stack
          SPVM_LIST* mortal_top_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);

          // Object temporary variable stack
          SPVM_LIST* object_op_var_tmp_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
          
          int32_t method_opcodes_base_id = opcode_array->length;
          
          method->opcodes_base_id = method_opcodes_base_id;
          
          // Run OPs
          SPVM_OP* op_base = method->op_block;
          SPVM_OP* op_cur = op_base;
          int32_t finish = 0;
          
          int32_t mortal_stack_top_max = 0;

          // Copy arguments to variables
          int32_t stack_index = 0;
          for (int32_t args_index = 0; args_index < method->args_length; args_index++) {
            SPVM_VAR_DECL* arg = SPVM_LIST_get(method->var_decls, args_index);
            SPVM_TYPE* arg_type = arg->type;
            int32_t arg_type_dimension = arg->type->dimension;
            SPVM_BASIC_TYPE* arg_basic_type = arg_type->basic_type;
            int32_t arg_type_is_ref = SPVM_TYPE_is_ref_type(compiler, arg_basic_type->id, arg_type_dimension, arg_type->flag);
            int32_t arg_basic_type_category = arg_type->basic_type->category;
            
            SPVM_OPCODE opcode;
            memset(&opcode, 0, sizeof(SPVM_OPCODE));
            int32_t type_width = arg_type->width;

            if (arg_type_dimension == 0) {
              if (arg_type_is_ref) {
                switch (arg_basic_type_category) {
                  case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC:
                  case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
                  {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARG_REF);
                    opcode.operand1 = arg->mem_id;
                    opcode.operand2 = stack_index;
                    opcode.operand3 = type_width;
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
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARG_BYTE);
                        opcode.operand1 = arg->mem_id;
                        opcode.operand2 = stack_index;
                        stack_index++;
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARG_SHORT);
                        opcode.operand1 = arg->mem_id;
                        opcode.operand2 = stack_index;
                        stack_index++;
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARG_INT);
                        opcode.operand1 = arg->mem_id;
                        opcode.operand2 = stack_index;
                        stack_index++;
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARG_LONG);
                        opcode.operand1 = arg->mem_id;
                        opcode.operand2 = stack_index;
                        stack_index++;
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARG_FLOAT);
                        opcode.operand1 = arg->mem_id;
                        opcode.operand2 = stack_index;
                        stack_index++;
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARG_DOUBLE);
                        opcode.operand1 = arg->mem_id;
                        opcode.operand2 = stack_index;
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
                    SPVM_CLASS* arg_class = arg_basic_type->class;
                    SPVM_FIELD* arg_mulnum_field = SPVM_LIST_get(arg_class->fields, 0);
                    SPVM_TYPE* arg_mulnum_field_type = arg_mulnum_field->type;
                    SPVM_BASIC_TYPE* arg_mulnum_field_basic_type = arg_mulnum_field_type->basic_type;
                    
                    switch (arg_mulnum_field_basic_type->id) {
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARG_MULNUM_BYTE);
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARG_MULNUM_SHORT);
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARG_MULNUM_INT);
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARG_MULNUM_LONG);
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARG_MULNUM_FLOAT);
                        break;
                      }
                      case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARG_MULNUM_DOUBLE);
                        break;
                      }
                    }
                    opcode.operand1 = arg->mem_id;
                    opcode.operand2 = stack_index;
                    opcode.operand3 = type_width;
                    stack_index += type_width;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING:
                  case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS:
                  case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE:
                  case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CALLBACK:
                  case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT:
                  {
                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARG_OBJECT);
                    opcode.operand1 = arg->mem_id;
                    opcode.operand2 = stack_index;
                    opcode.operand3 = type_width;
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
                case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CALLBACK:
                case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT:
                {
                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARG_OBJECT);
                  opcode.operand1 = arg->mem_id;
                  opcode.operand2 = stack_index;
                  opcode.operand3 = type_width;
                  stack_index++;
                  break;
                }
                default: {
                  assert(0);
                }
              }
            }
            else if (arg_type_dimension == 2) {
              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARG_OBJECT);
              opcode.operand1 = arg->mem_id;
              opcode.operand2 = stack_index;
              opcode.operand3 = type_width;
              stack_index++;
            }
            else {
              assert(0);
            }
            
            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
          }

          while (op_cur) {
            
            // [START]Preorder traversal position
            switch (op_cur->id) {
              case SPVM_OP_C_ID_BLOCK: { // Preorder
                
                // Push block
                SPVM_LIST_push(op_block_stack, op_cur);
                
                if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_LOOP_INIT) {
                  // Push last block base stack
                  int32_t last_block_base = last_goto_opcode_rel_index_stack->length;
                  SPVM_LIST_push(last_block_base_stack, (void*)(intptr_t)last_block_base);
                }
                else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_LOOP_STATEMENTS) {
                  
                  // Push next block base stack
                  int32_t next_block_base = next_goto_opcode_rel_index_stack->length;
                  SPVM_LIST_push(next_block_base_stack, (void*)(intptr_t)next_block_base);

                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));
                  // Add goto
                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GOTO);
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  
                  int32_t opcode_rel_index = opcode_array->length - 1 - method_opcodes_base_id;
                  
                  SPVM_LIST_push(loop_first_goto_opcode_rel_index_stack, (void*)(intptr_t)opcode_rel_index);
                }
                else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_SWITCH) {
                  // Push break block base stack
                  int32_t break_block_base = break_goto_opcode_rel_index_stack->length;
                  SPVM_LIST_push(break_block_base_stack, (void*)(intptr_t)break_block_base);
                }
                else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_EVAL) {
                  int32_t opcode_rel_index = opcode_array->length - method_opcodes_base_id;
                  
                  SPVM_LIST_push(push_eval_opcode_rel_index_stack, (void*)(intptr_t)opcode_rel_index);

                  // Set exception var to undef in eval block start
                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));
                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR_UNDEF);
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                }
                
                int32_t mortal_top = mortal_stack->length;
                SPVM_LIST_push(mortal_top_stack, (void*)(intptr_t)mortal_top);
                break;
              }
              case SPVM_OP_C_ID_SWITCH: {
                SPVM_SWITCH_INFO* switch_info = op_cur->uv.switch_info;
                SPVM_LIST_push(switch_info_stack, switch_info);
                break;
              }
              case SPVM_OP_C_ID_CASE: {
                if (switch_info_stack->length > 0) {
                  SPVM_SWITCH_INFO* switch_info = SPVM_LIST_get(switch_info_stack, switch_info_stack->length - 1);
                  int32_t opcode_rel_index = opcode_array->length - method_opcodes_base_id;
                  op_cur->uv.case_info->opcode_rel_index = opcode_rel_index;
                }
                break;
              }
              case SPVM_OP_C_ID_DEFAULT: {
                if (switch_info_stack->length > 0) {
                  SPVM_SWITCH_INFO* switch_info = SPVM_LIST_get(switch_info_stack, switch_info_stack->length - 1);
                  switch_info->default_opcode_rel_index = opcode_array->length - method_opcodes_base_id;
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
                    if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_IF) {
                      
                      {
                        // Prepare to jump to end of true block
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));

                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GOTO);
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                        
                        int32_t opcode_rel_index = opcode_array->length - 1 - method_opcodes_base_id;
                        SPVM_LIST_push(if_block_end_goto_opcode_rel_index_stack, (void*)(intptr_t)opcode_rel_index);
                      }

                      int32_t if_eq_or_if_ne_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(if_eq_or_if_ne_goto_opcode_rel_index_stack);
                      
                      // Set jump
                      SPVM_OPCODE* if_eq_or_if_ne_goto = (opcode_array->values + method_opcodes_base_id + if_eq_or_if_ne_goto_opcode_rel_index);
                      int32_t if_eq_or_if_ne_jump_opcode_rel_index = opcode_array->length - method_opcodes_base_id;
                      if_eq_or_if_ne_goto->operand0 = if_eq_or_if_ne_jump_opcode_rel_index;
                    }
                    else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_ELSE) {
                      
                      assert(if_block_end_goto_opcode_rel_index_stack->length > 0);
                      
                      int32_t if_block_end_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(if_block_end_goto_opcode_rel_index_stack);
                      
                      SPVM_OPCODE* if_block_end_goto = (opcode_array->values + method_opcodes_base_id + if_block_end_goto_opcode_rel_index);
                      int32_t if_block_end_jump_opcode_rel_index = opcode_array->length - method_opcodes_base_id;
                      if_block_end_goto->operand0 = if_block_end_jump_opcode_rel_index;
                    }
                    else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_LOOP_INIT) {
                      // last block base
                      int32_t last_block_base = (intptr_t)SPVM_LIST_pop(last_block_base_stack);

                      // Set last position
                      int32_t last_goto_opcode_rel_index_stack_pop_count = last_goto_opcode_rel_index_stack->length - last_block_base;
                      for (int32_t i = 0; i < last_goto_opcode_rel_index_stack_pop_count; i++) {
                        int32_t last_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(last_goto_opcode_rel_index_stack);
                        
                        SPVM_OPCODE* last_goto = (opcode_array->values + method_opcodes_base_id + last_goto_opcode_rel_index);
                        int32_t last_goto_jump_opcode_rel_index = opcode_array->length - method_opcodes_base_id;
                        last_goto->operand0 = last_goto_jump_opcode_rel_index;
                      }
                    }
                    else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_LOOP_STATEMENTS) {
                      // next block base
                      int32_t next_block_base = (intptr_t)SPVM_LIST_pop(next_block_base_stack);
                      
                      // Set next position
                      int32_t next_goto_opcode_rel_index_stack_pop_count = next_goto_opcode_rel_index_stack->length - next_block_base;
                      for (int32_t i = 0; i < next_goto_opcode_rel_index_stack_pop_count; i++) {
                        int32_t next_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(next_goto_opcode_rel_index_stack);
                        
                        SPVM_OPCODE* next_goto = (opcode_array->values + method_opcodes_base_id + next_goto_opcode_rel_index);
                        int32_t next_goto_jump_opcode_rel_index = opcode_array->length - method_opcodes_base_id;
                        next_goto->operand0 = next_goto_jump_opcode_rel_index;
                      }
                    }
                    else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_SWITCH) {
                      // break block base
                      int32_t break_block_base = (intptr_t)SPVM_LIST_pop(break_block_base_stack);
                      
                      // Set break position
                      int32_t break_goto_opcode_rel_index_stack_pop_count = break_goto_opcode_rel_index_stack->length - break_block_base;
                      for (int32_t i = 0; i < break_goto_opcode_rel_index_stack_pop_count; i++) {
                        int32_t break_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(break_goto_opcode_rel_index_stack);
                        
                        SPVM_OPCODE* break_goto = (opcode_array->values + method_opcodes_base_id + break_goto_opcode_rel_index);
                        int32_t break_goto_jump_opcode_rel_index = opcode_array->length - method_opcodes_base_id;
                        break_goto->operand0 = break_goto_jump_opcode_rel_index;
                      }
                    }
                    else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_EVAL) {
                      // Set IF_EXCEPTION_CATCH opcode index
                      while (if_die_catch_goto_opcode_rel_index_stack->length > 0) {
                        int32_t if_die_catch_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(if_die_catch_goto_opcode_rel_index_stack);
                        
                        SPVM_OPCODE* if_die_catch_goto = (opcode_array->values + method_opcodes_base_id + if_die_catch_goto_opcode_rel_index);
                        int32_t if_die_catch_goto_jump_rel_index = opcode_array->length - method_opcodes_base_id;
                        if_die_catch_goto->operand0 = if_die_catch_goto_jump_rel_index;
                      }
                      
                      SPVM_LIST_pop(push_eval_opcode_rel_index_stack);
                    }
                    else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_METHOD) {
                      while (return_goto_opcode_rel_index_stack->length > 0) {
                        
                        int32_t return_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(return_goto_opcode_rel_index_stack);
                        
                        SPVM_OPCODE* return_goto = (opcode_array->values + method_opcodes_base_id + return_goto_opcode_rel_index);
                        int32_t return_goto_jump_opcode_rel_index = opcode_array->length - method_opcodes_base_id;
                        return_goto->operand1 = return_goto_jump_opcode_rel_index;
                      }

                      // Set IF_EXCEPTION_RETURN opcode index
                      while (if_die_return_goto_opcode_rel_index_stack->length > 0) {
                        int32_t if_die_return_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(if_die_return_goto_opcode_rel_index_stack);
                        
                        SPVM_OPCODE* if_die_return_goto = (opcode_array->values + method_opcodes_base_id + if_die_return_goto_opcode_rel_index);
                        int32_t if_die_return_goto_jump_opcode_rel_index = opcode_array->length - method_opcodes_base_id;
                        if_die_return_goto->operand0 = if_die_return_goto_jump_opcode_rel_index;
                      }
                    }
                    
                    // Leave scope
                    int32_t mortal_top = (intptr_t)SPVM_LIST_pop(mortal_top_stack);

                    SPVM_OP* op_block_current = SPVM_LIST_get(op_block_stack, op_block_stack->length - 1);
                    
                    if (op_block_current->uv.block->have_object_var_decl) {
                      while (mortal_stack->length > mortal_top) {
                        SPVM_LIST_pop(mortal_stack);
                      }
                      
                      SPVM_OPCODE opcode;
                      memset(&opcode, 0, sizeof(SPVM_OPCODE));
                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LEAVE_SCOPE);
                      opcode.operand0 = mortal_top;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    }

                    SPVM_LIST_pop(op_block_stack);

                    break;
                  }
                  case SPVM_OP_C_ID_VAR: {
                    if (op_cur->uv.var->is_declaration) {
                      
                      SPVM_VAR_DECL* var_decl = op_cur->uv.var->var_decl;
                      
                      SPVM_TYPE* type = SPVM_OP_get_type(compiler, var_decl->op_var_decl);
                      if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                        
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PUSH_MORTAL);
                        int32_t my_mem_id = SPVM_OP_get_mem_id(compiler, op_cur);
                        opcode.operand0 = my_mem_id;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                        
                        SPVM_LIST_push(mortal_stack, (void*)(intptr_t)my_mem_id);
                        
                        mortal_stack_top_max++;
                        
                        SPVM_OP* op_block_current = SPVM_LIST_get(op_block_stack, op_block_stack->length - 1);
                        op_block_current->uv.block->have_object_var_decl = 1;
                      }
                      
                      // Initialized not initialized variable
                      if (!op_cur->uv.var->is_initialized && !op_cur->uv.var->var_decl->is_arg) {
                        // Multi numeric type
                        if (SPVM_TYPE_is_mulnum_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                          SPVM_CLASS* value_class = type->basic_type->class;
                          assert(class);
                          
                          SPVM_FIELD* first_field = SPVM_LIST_get(value_class->fields, 0);
                          assert(first_field);
                          
                          SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, first_field->op_field);
                          assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          int32_t mem_id_out;
                          int32_t mem_id_in;
                          switch (field_type->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_INIT_MULNUM_BYTE);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_cur);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_INIT_MULNUM_SHORT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_cur);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_INIT_MULNUM_INT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_cur);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_INIT_MULNUM_LONG);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_cur);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_INIT_MULNUM_FLOAT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_cur);
                              break;
                            }
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_INIT_MULNUM_DOUBLE);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_cur);
                              break;
                            }
                            default:
                              assert(0);
                          }
                          
                          int32_t fields_length = value_class->fields->length;

                          opcode.operand0 = mem_id_out;
                          opcode.operand2 = fields_length;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                        }
                        // Object type
                        else if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_INIT_UNDEF);
                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_cur);

                          opcode.operand0 = mem_id_out;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                        }
                        // Numeric type
                        else if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          int32_t mem_id_out;
                          switch (type->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_INIT_BYTE);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_cur);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_INIT_SHORT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_cur);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_INIT_INT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_cur);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_INIT_LONG);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_cur);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_INIT_FLOAT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_cur);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_INIT_DOUBLE);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_cur);
                              break;
                            default:
                              assert(0);
                          }

                          opcode.operand0 = mem_id_out;
                          
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
                  case SPVM_OP_C_ID_ASSIGN: {
                    SPVM_OP* op_assign_dist = op_cur->last;
                    SPVM_OP* op_assign_src = op_cur->first;
                    
                    if (op_assign_src->id == SPVM_OP_C_ID_SEQUENCE) {
                      op_assign_src = op_assign_src->last;
                    }
                    
                    if (op_assign_dist->id == SPVM_OP_C_ID_VAR) {
                      SPVM_TYPE* type_dist = SPVM_OP_get_type(compiler, op_assign_dist);

                      // Push object temporary variable stack
                      if (op_assign_dist->uv.var->var_decl->is_tmp) {
                        if (SPVM_TYPE_is_object_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                          SPVM_LIST_push(object_op_var_tmp_stack, op_assign_dist);
                        }
                      }
                      
                      switch (op_assign_src->id) {
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
                          SPVM_OP* op_var_dist = op_cur->last;
                          
                          if (SPVM_TYPE_is_byte_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_BYTE);
                            
                            int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_var_dist);
                            int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_var_src);

                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else if (SPVM_TYPE_is_short_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_SHORT);
                            
                            int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_var_dist);
                            int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_var_src);

                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else if (SPVM_TYPE_is_int_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_INT);
                            
                            int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_var_dist);
                            int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_var_src);

                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else if (SPVM_TYPE_is_long_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_LONG);
                            
                            int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_var_dist);
                            int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_var_src);

                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else if (SPVM_TYPE_is_float_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_FLOAT);
                            
                            int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_var_dist);
                            int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_var_src);

                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else if (SPVM_TYPE_is_double_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_DOUBLE);
                            
                            int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_var_dist);
                            int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_var_src);

                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else if (SPVM_TYPE_is_object_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                            
                            int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_var_dist);
                            int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_var_src);

                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else if (SPVM_TYPE_is_ref_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_REF);
                            
                            int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_var_dist);
                            int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_var_src);

                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else if (SPVM_TYPE_is_mulnum_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                            SPVM_CLASS* value_class = type_dist->basic_type->class;
                            assert(value_class);
                            
                            SPVM_FIELD* first_field = SPVM_LIST_get(value_class->fields, 0);
                            assert(first_field);
                            
                            SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, first_field->op_field);
                            assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                            
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));

                            int32_t mem_id_out;
                            int32_t mem_id_in;
                            switch (field_type->basic_type->id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_BYTE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_SHORT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_INT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_LONG);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_FLOAT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_DOUBLE);
                                break;
                              }
                              default:
                                assert(0);
                            }

                            int32_t fields_length = value_class->fields->length;
                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            opcode.operand2 = fields_length;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else {
                            assert(0);
                          }
                          break;
                        }
                        case SPVM_OP_C_ID_FREE_TMP: {
                          // Free temporary variables
                          int32_t length = object_op_var_tmp_stack->length;
                          for (int32_t i = 0; i < length; i++) {
                            SPVM_OP* op_var_tmp = SPVM_LIST_pop(object_op_var_tmp_stack);
                            
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_INIT_UNDEF);
                            
                            int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_var_tmp);
                            opcode.operand0 = mem_id_out;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          break;
                        }
                        case SPVM_OP_C_ID_CONCAT: {
                          SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_assign_src->first);
                          
                          assert(SPVM_TYPE_is_string_or_byte_array_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag));
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONCAT);
                          
                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          int32_t mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                          int32_t mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);

                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                          break;
                        }
                        case SPVM_OP_C_ID_REFOP : {
                          
                          SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_assign_src->first);
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REFOP);
                          
                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);

                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                          break;
                        }
                        case SPVM_OP_C_ID_DUMP : {
                          
                          SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_assign_src->first);
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DUMP);
                          
                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);

                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                          break;
                        }
                        case SPVM_OP_C_ID_NEW_STRING_LEN : {
                          
                          SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_assign_src->first);
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_STRING_LEN);
                          
                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);

                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                          
                          break;
                        }
                        case SPVM_OP_C_ID_IS_READ_ONLY : {
                          
                          SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_assign_src->first);
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_READ_ONLY);
                          
                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);

                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_REFCNT : {
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));

                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REFCNT);
                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                          break;
                        }
                        case SPVM_OP_C_ID_UNDEF : {

                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_INIT_UNDEF);
                          
                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          opcode.operand0 = mem_id_out;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_CALL_METHOD: {
                          
                          SPVM_CALL_METHOD* call_method = op_assign_src->uv.call_method;
                          const char* call_method_method_name = call_method->method->name;
                          SPVM_CLASS* call_method_method_class = call_method->method->class;
                          
                          SPVM_METHOD* method_call_method = SPVM_HASH_get(call_method_method_class->method_symtable, call_method_method_name, strlen(call_method_method_name));
                          
                          int32_t first_arg_mem_id = -1;
                          SPVM_OP* op_term_args = op_assign_src->last;
                          SPVM_OP* op_term_arg = op_term_args->first;

                          SPVM_LIST* args = method_call_method->var_decls;
                          {
                            int32_t arg_index;
                            for (arg_index = 0; arg_index < method_call_method->args_length; arg_index++) {
                              SPVM_VAR_DECL* arg_var_decl = SPVM_LIST_get(args, arg_index);
                              
                              // Argument type
                              SPVM_TYPE* arg_type = arg_var_decl->type;

                              // Term argment type
                              op_term_arg = SPVM_OP_sibling(compiler, op_term_arg);
                              SPVM_TYPE* term_arg_type = SPVM_OP_get_type(compiler, op_term_arg);
                              
                              SPVM_OPCODE opcode;
                              memset(&opcode, 0, sizeof(SPVM_OPCODE));
                              
                              if (SPVM_TYPE_is_undef_type(compiler, term_arg_type->basic_type->id, term_arg_type->dimension, term_arg_type->flag)) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PUSH_ARG_UNDEF);
                                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                              }
                              else {
                                if (SPVM_TYPE_is_ref_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag)) {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PUSH_ARG_REF);

                                  // Term of argument
                                  int32_t mem_id_arg = SPVM_OP_get_mem_id(compiler, op_term_arg);
                                  
                                  opcode.operand0 = mem_id_arg;
                                  
                                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                                }
                                else if (SPVM_TYPE_is_mulnum_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag)) {

                                  SPVM_CLASS* value_class = arg_type->basic_type->class;
                                  assert(class);
                                  
                                  SPVM_FIELD* first_field = SPVM_LIST_get(value_class->fields, 0);
                                  assert(first_field);
                                  
                                  SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, first_field->op_field);
                                  assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                                  
                                  int32_t mem_id_arg;
                                  switch (field_type->basic_type->id) {
                                    case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_BYTE);
                                      mem_id_arg = SPVM_OP_get_mem_id(compiler, op_term_arg);
                                      break;
                                    }
                                    case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_SHORT);
                                      mem_id_arg = SPVM_OP_get_mem_id(compiler, op_term_arg);
                                      break;
                                    }
                                    case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_INT);
                                      mem_id_arg = SPVM_OP_get_mem_id(compiler, op_term_arg);
                                      break;
                                    }
                                    case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_LONG);
                                      mem_id_arg = SPVM_OP_get_mem_id(compiler, op_term_arg);
                                      break;
                                    }
                                    case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_FLOAT);
                                      mem_id_arg = SPVM_OP_get_mem_id(compiler, op_term_arg);
                                      break;
                                    }
                                    case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_DOUBLE);
                                      mem_id_arg = SPVM_OP_get_mem_id(compiler, op_term_arg);
                                      break;
                                    }
                                    default:
                                      assert(0);
                                  }
                                  
                                  int32_t fields_length = value_class->fields->length;
                                  opcode.operand0 = mem_id_arg;
                                  opcode.operand1 = fields_length;
                                  
                                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                                }
                                // Object type
                                else if (SPVM_TYPE_is_object_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag)) {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PUSH_ARG_OBJECT);
                                  int32_t mem_id_arg = SPVM_OP_get_mem_id(compiler, op_term_arg);
                                  
                                  opcode.operand0 = mem_id_arg;
                                  
                                  if (arg_index == 0) {
                                    first_arg_mem_id = mem_id_arg;
                                  }
                                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                                }
                                // Numeric type
                                else if (SPVM_TYPE_is_numeric_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag)) {
                                  int32_t mem_id_arg;
                                  switch (arg_type->basic_type->id) {
                                    case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PUSH_ARG_BYTE);
                                      mem_id_arg = SPVM_OP_get_mem_id(compiler, op_term_arg);
                                      break;
                                    }
                                    case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PUSH_ARG_SHORT);
                                      mem_id_arg = SPVM_OP_get_mem_id(compiler, op_term_arg);
                                      break;
                                    }
                                    case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PUSH_ARG_INT);
                                      mem_id_arg = SPVM_OP_get_mem_id(compiler, op_term_arg);
                                      break;
                                    }
                                    case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PUSH_ARG_LONG);
                                      mem_id_arg = SPVM_OP_get_mem_id(compiler, op_term_arg);
                                      break;
                                    }
                                    case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PUSH_ARG_FLOAT);
                                      mem_id_arg = SPVM_OP_get_mem_id(compiler, op_term_arg);
                                      break;
                                    }
                                    case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PUSH_ARG_DOUBLE);
                                      mem_id_arg = SPVM_OP_get_mem_id(compiler, op_term_arg);
                                      break;
                                    }
                                    default:
                                      assert(0);
                                  }
                                  
                                  opcode.operand0 = mem_id_arg;
                                  
                                  if (arg_index == 0) {
                                    first_arg_mem_id = mem_id_arg;
                                  }
                                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                                }
                                else {
                                  assert(0);
                                }
                              }
                            }
                          }

                          int32_t mem_id_out;

                          // Call method
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));

                          SPVM_TYPE* call_method_return_type = call_method->method->return_type;
                          if (method_call_method->class->category == SPVM_CLASS_C_CATEGORY_CALLBACK ||
                              method_call_method->class->category == SPVM_CLASS_C_CATEGORY_INTERFACE)
                          {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD_BY_SIGNATURE);

                            // Numeric type
                            if (SPVM_TYPE_is_numeric_type(compiler, call_method_return_type->basic_type->id, call_method_return_type->dimension, call_method_return_type->flag)) {
                              switch (call_method_return_type->basic_type->id) {
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                default:
                                  assert(0);
                              }
                            }
                            // void type
                            else if (SPVM_TYPE_is_void_type(compiler, call_method_return_type->basic_type->id, call_method_return_type->dimension, call_method_return_type->flag)) {
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                            }
                            // Object type
                            else if (SPVM_TYPE_is_object_type(compiler, call_method_return_type->basic_type->id, call_method_return_type->dimension, call_method_return_type->flag)) {
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                            }
                            // Multi numeric type
                            else if (SPVM_TYPE_is_mulnum_type(compiler, call_method_return_type->basic_type->id, call_method_return_type->dimension, call_method_return_type->flag)) {

                              SPVM_CLASS* value_class = call_method_return_type->basic_type->class;
                              assert(class);
                              
                              SPVM_FIELD* first_field = SPVM_LIST_get(value_class->fields, 0);
                              assert(first_field);
                              
                              SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, first_field->op_field);
                              assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                              
                              switch (field_type->basic_type->id) {
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                default:
                                  assert(0);
                              }
                            }
                            else {
                              assert(0);
                            }

                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = call_method->method->id;
                          }
                          else {
                            if (call_method->method->is_class_method) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CALL_CLASS_METHOD_BY_ID);
                            }
                            else {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD_BY_ID);
                            }

                            // Numeric type
                            if (SPVM_TYPE_is_numeric_type(compiler, call_method_return_type->basic_type->id, call_method_return_type->dimension, call_method_return_type->flag)) {
                              switch (call_method_return_type->basic_type->id) {
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                default:
                                  assert(0);
                              }
                            }
                            // void type
                            else if (SPVM_TYPE_is_void_type(compiler, call_method_return_type->basic_type->id, call_method_return_type->dimension, call_method_return_type->flag)) {
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                            }
                            // Object type
                            else if (SPVM_TYPE_is_object_type(compiler, call_method_return_type->basic_type->id, call_method_return_type->dimension, call_method_return_type->flag)) {
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                            }
                            // Multi numeric type
                            else if (SPVM_TYPE_is_mulnum_type(compiler, call_method_return_type->basic_type->id, call_method_return_type->dimension, call_method_return_type->flag)) {

                              SPVM_CLASS* value_class = call_method_return_type->basic_type->class;
                              assert(class);
                              
                              SPVM_FIELD* first_field = SPVM_LIST_get(value_class->fields, 0);
                              assert(first_field);
                              
                              SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, first_field->op_field);
                              assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                              
                              switch (field_type->basic_type->id) {
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                }
                                default:
                                  assert(0);
                              }
                            }
                            else {
                              assert(0);
                            }
                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = call_method->method->id;
                          }
                          
                          int32_t call_method_return_type_width = SPVM_TYPE_get_width(compiler, call_method_return_type->basic_type->id, call_method_return_type->dimension, call_method_return_type->flag);
                          opcode.operand3 = call_method_return_type_width;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                          SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                          break;
                        }
                        case SPVM_OP_C_ID_STRING_LENGTH : {
                          
                          // String length logic is same as ARRAY_LENGTH opcode
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_ARRAY_LENGTH);
                          
                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                          break;
                        }
                        case SPVM_OP_C_ID_ARRAY_LENGTH : {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_ARRAY_LENGTH);
                          
                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
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
                          SPVM_TYPE* array_type = SPVM_OP_get_type(compiler, op_array_field_access->first);
                          SPVM_BASIC_TYPE* array_basic_type = array_type->basic_type;
                          
                          // Element type
                          SPVM_TYPE* element_type = SPVM_OP_get_type(compiler, op_array_field_access);

                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          int32_t mem_id_out;
                          switch (element_type->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_BYTE);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_SHORT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_INT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_LONG);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_FLOAT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_DOUBLE);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              break;
                            default:
                              assert(0);
                          }
                          
                          // Field absolute name symbol
                          int32_t mem_id_invocant = SPVM_OP_get_mem_id(compiler, op_term_invocant);
                          int32_t mem_id_index = SPVM_OP_get_mem_id(compiler, op_term_index);
                          
                          int32_t fields_length = array_basic_type->class->fields->length;
                          int32_t field_offset = field->index;

                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_invocant;
                          opcode.operand2 = mem_id_index;
                          opcode.operand3 = (field_offset << 8) + (fields_length - 1);

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                          break;
                        }
                        case SPVM_OP_C_ID_FIELD_ACCESS : {

                          // Weaken field
                          if (op_assign_src->flag & SPVM_OP_C_FLAG_FIELD_ACCESS_WEAKEN) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));

                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_WEAKEN_FIELD);
                            
                            SPVM_OP* op_term_invocant = op_assign_src->first;
                            int32_t mem_id_invocant = SPVM_OP_get_mem_id(compiler, op_term_invocant);

                            opcode.operand0 = mem_id_invocant;
                            opcode.operand1 = op_assign_src->uv.field_access->field->id;
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                            SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_assign_src->line);
                          }
                          else if (op_assign_src->flag & SPVM_OP_C_FLAG_FIELD_ACCESS_UNWEAKEN) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));

                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_UNWEAKEN_FIELD);
                            
                            SPVM_OP* op_term_invocant = op_assign_src->first;
                            int32_t mem_id_invocant = SPVM_OP_get_mem_id(compiler, op_term_invocant);

                            opcode.operand0 = mem_id_invocant;
                            opcode.operand1 = op_assign_src->uv.field_access->field->id;
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                            SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_assign_src->line);
                          }
                          else if (op_assign_src->flag & SPVM_OP_C_FLAG_FIELD_ACCESS_ISWEAK) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));

                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_ISWEAK_FIELD);
                            
                            SPVM_OP* op_term_invocant = op_assign_src->first;
                            int32_t mem_id_invocant = SPVM_OP_get_mem_id(compiler, op_term_invocant);

                            opcode.operand1 = mem_id_invocant;
                            opcode.operand2 = op_assign_src->uv.field_access->field->id;
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                            SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_assign_src->line);
                          }
                          else {
                            // $VAR = $VAR_OBJECT->{NAME}
                            SPVM_OP* op_field_access = op_assign_src;
                            SPVM_OP* op_term_invocant = op_field_access->first;
                            
                            // Call field
                            SPVM_FIELD_ACCESS* field_access = op_field_access->uv.field_access;
                            
                            SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, op_field_access);

                            SPVM_TYPE* invocant_type = SPVM_OP_get_type(compiler, op_term_invocant);

                            // Value field dereference access
                            if (SPVM_TYPE_is_mulnum_ref_type(compiler, invocant_type->basic_type->id, invocant_type->dimension, invocant_type->flag)) {
                              SPVM_FIELD* field = field_access->field;
                              
                              SPVM_OPCODE opcode;
                              memset(&opcode, 0, sizeof(SPVM_OPCODE));
                              int32_t mem_id_out;
                              switch (field_type->basic_type->id) {
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_BYTE);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_SHORT);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_INT);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_LONG);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_FLOAT);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_DOUBLE);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                default:
                                  assert(0);
                              }
                              
                              int32_t mem_id_invocant = SPVM_OP_get_mem_id(compiler, op_term_invocant);
                              int32_t field_offset = field->index;

                              opcode.operand0 = mem_id_out;
                              opcode.operand1 = mem_id_invocant;
                              opcode.operand2 = field_offset;

                              SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            }
                            // Value field access
                            else if (SPVM_TYPE_is_mulnum_type(compiler, invocant_type->basic_type->id, invocant_type->dimension, invocant_type->flag)) {
                              SPVM_OPCODE opcode;
                              memset(&opcode, 0, sizeof(SPVM_OPCODE));
                              
                              int32_t mem_id_out;
                              int32_t mem_id_in;
                              switch (field_type->basic_type->id) {
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_BYTE);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_term_invocant);
                                  break;
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_SHORT);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_term_invocant);
                                  break;
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_INT);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_term_invocant);
                                  break;
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_LONG);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_term_invocant);
                                  break;
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_FLOAT);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_term_invocant);
                                  break;
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DOUBLE);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_term_invocant);
                                  break;
                                default:
                                  assert(0);
                              }
                              
                              opcode.operand0 = mem_id_out;
                              opcode.operand1 = mem_id_in;
                              opcode.operand2 = field_access->field->index;

                              SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            }
                            // Field access
                            else {
                              SPVM_OPCODE opcode;
                              memset(&opcode, 0, sizeof(SPVM_OPCODE));
                              int32_t mem_id_invocant = SPVM_OP_get_mem_id(compiler, op_term_invocant);
                              int32_t mem_id_out;
                              if (SPVM_TYPE_is_object_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_OBJECT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              }
                              else {
                                switch (field_type->basic_type->id) {
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_BYTE);
                                    mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                    break;
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_SHORT);
                                    mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                    break;
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_INT);
                                    mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                    break;
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_LONG);
                                    mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                    break;
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_FLOAT);
                                    mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                    break;
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE);
                                    mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                    break;
                                  default:
                                    assert(0);
                                }
                              }
                              
                              opcode.operand0 = mem_id_out;
                              opcode.operand1 = mem_id_invocant;
                              opcode.operand2 = field_access->field->id;

                              SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                              SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                            }
                          }
                          break;
                        }
                        case SPVM_OP_C_ID_ARRAY_ACCESS : {
                          
                          // $VAR = $VAR_ARRAY->[$VAR_INDEX]
                          SPVM_OP* op_array_access = op_assign_src;
                          SPVM_OP* op_term_array = op_array_access->first;
                          SPVM_OP* op_term_index = op_array_access->last;
                          
                          SPVM_TYPE* array_type = SPVM_OP_get_type(compiler, op_term_array);

                          if (SPVM_TYPE_is_mulnum_array_type(compiler, array_type->basic_type->id, array_type->dimension, array_type->flag)) {
                            SPVM_CLASS* class = array_type->basic_type->class;
                            SPVM_FIELD* first_field = SPVM_LIST_get(class->fields, 0);
                            
                            SPVM_TYPE* element_type = SPVM_OP_get_type(compiler, first_field->op_field);
                            
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            assert(SPVM_TYPE_is_numeric_type(compiler, element_type->basic_type->id, element_type->dimension, element_type->flag));
                            int32_t mem_id_out;
                            switch (element_type->basic_type->id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_BYTE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_SHORT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_INT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_LONG);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FLOAT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_DOUBLE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              default:
                                assert(0);
                            }
                            int32_t mem_id_array = SPVM_OP_get_mem_id(compiler, op_term_array);
                            int32_t mem_id_index = SPVM_OP_get_mem_id(compiler, op_term_index);
                            int32_t fields_length = array_type->basic_type->class->fields->length;

                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_array;
                            opcode.operand2 = mem_id_index;
                            opcode.operand3 = fields_length;

                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                            SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                          }
                          else {
                            SPVM_TYPE* element_type = SPVM_OP_get_type(compiler, op_array_access);
                          
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            int32_t mem_id_out;
                            if (SPVM_TYPE_is_object_type(compiler, element_type->basic_type->id, element_type->dimension, element_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_OBJECT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                            }
                            else {
                              switch (element_type->basic_type->id) {
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_BYTE);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_SHORT);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_INT);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_LONG);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_FLOAT);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_DOUBLE);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                  break;
                                default:
                                  assert(0);
                              }
                            }

                            int32_t mem_id_array = SPVM_OP_get_mem_id(compiler, op_term_array);
                            int32_t mem_id_index = SPVM_OP_get_mem_id(compiler, op_term_index);

                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_array;
                            opcode.operand2 = mem_id_index;

                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                            SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                          }
                          break;
                        }
                        case SPVM_OP_C_ID_CLASS_VAR_ACCESS : {
                          SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_assign_src);
                          
                          SPVM_CLASS_VAR_ACCESS* class_var_access = op_assign_src->uv.class_var_access;
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          int32_t mem_id_out;
                          if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_OBJECT);
                            mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          }
                          else {
                            switch (type->basic_type->id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_BYTE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_SHORT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_INT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_LONG);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_FLOAT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_CLASS_VAR_DOUBLE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              default:
                                assert(0);
                            }
                          }
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = class_var_access->class_var->id;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_DEREF : {
                          SPVM_TYPE* src_type = SPVM_OP_get_type(compiler, op_assign_src);
                          
                          if (SPVM_TYPE_is_mulnum_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_FIELD* first_field = SPVM_LIST_get(src_type->basic_type->class->fields, 0);
                          
                            SPVM_TYPE* element_type = SPVM_OP_get_type(compiler, first_field->op_field);

                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            
                            assert(SPVM_TYPE_is_numeric_type(compiler, element_type->basic_type->id, element_type->dimension, element_type->flag));
                            int32_t mem_id_out;
                            if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DEREF_MULNUM_BYTE);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                            }
                            else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DEREF_MULNUM_SHORT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                            }
                            else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DEREF_MULNUM_INT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                            }
                            else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DEREF_MULNUM_LONG);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                            }
                            else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DEREF_MULNUM_FLOAT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                            }
                            else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DEREF_MULNUM_DOUBLE);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                            }
                            else {
                              assert(0);
                            }

                            int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                            int32_t fields_length = src_type->basic_type->class->fields->length;
                            
                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            opcode.operand3 = fields_length;

                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {

                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            
                            int32_t mem_id_out;
                            switch (src_type->basic_type->id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_DEREF_BYTE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_DEREF_SHORT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_DEREF_INT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_DEREF_LONG);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_DEREF_FLOAT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_DEREF_DOUBLE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              default:
                                assert(0);
                            }
                            
                            int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                            
                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else {
                            assert(0);
                          }
                          break;
                        }
                        case SPVM_OP_C_ID_CREATE_REF : {
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          int32_t mem_id_in;
                          SPVM_TYPE* src_type = SPVM_OP_get_type(compiler, op_assign_src->first);
                          if (SPVM_TYPE_is_mulnum_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_CLASS* value_class = src_type->basic_type->class;
                            assert(class);
                            
                            SPVM_FIELD* first_field = SPVM_LIST_get(value_class->fields, 0);
                            assert(first_field);
                            
                            SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, first_field->op_field);
                            assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                            
                            switch (field_type->basic_type->id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_BYTE);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_SHORT);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_INT);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_LONG);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_FLOAT);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_DOUBLE);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              default:
                                assert(0);
                            }
                          }
                          else if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            switch (src_type->basic_type->id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_BYTE);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_SHORT);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_INT);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_LONG);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_FLOAT);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REF_DOUBLE);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              default:
                                assert(0);
                            }
                          }
                          else {
                            assert(0);
                          }
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_EXCEPTION_VAR : {
                          // VAR = EXCEPTION_VAR
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GET_EXCEPTION_VAR);

                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          
                          opcode.operand0 = mem_id_out;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_ADD : {
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
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
                          
                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          int32_t mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                          int32_t mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_SUBTRACT : {

                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));

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

                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          int32_t mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                          int32_t mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_MULTIPLY : {

                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));

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

                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          int32_t mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                          int32_t mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_DIVIDE : {

                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
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

                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          int32_t mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                          int32_t mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                          // Check die
                          switch (type_dist->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                              SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                            break;
                          }
                          
                          break;
                        }
                        case SPVM_OP_C_ID_DIVIDE_UNSIGNED_INT : {

                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DIVIDE_UNSIGNED_INT);

                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          int32_t mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                          int32_t mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                          // Check die
                          SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);                              
                          break;
                        }
                        case SPVM_OP_C_ID_DIVIDE_UNSIGNED_LONG : {

                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_DIVIDE_UNSIGNED_LONG);

                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          int32_t mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                          int32_t mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                          SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                          
                          break;
                        }
                        case SPVM_OP_C_ID_REMAINDER : {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                          int32_t mem_id_out;
                          int32_t mem_id_in1;
                          int32_t mem_id_in2;
                          switch (type_dist->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REMAINDER_INT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REMAINDER_LONG);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            default:
                              assert(0);
                          }
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          // Check die
                          assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                          switch (type_dist->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                              SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                            break;
                          }
                          break;
                        }
                        case SPVM_OP_C_ID_REMAINDER_UNSIGNED_INT : {

                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REMAINDER_UNSIGNED_INT);

                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          int32_t mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                          int32_t mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                          // Check die
                          SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);                              
                          break;
                        }
                        case SPVM_OP_C_ID_REMAINDER_UNSIGNED_LONG : {

                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_REMAINDER_UNSIGNED_LONG);

                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          int32_t mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                          int32_t mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                          SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                          
                          break;
                        }
                        case SPVM_OP_C_ID_LEFT_SHIFT : {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                          int32_t mem_id_in1;
                          int32_t mem_id_out;
                          switch (type_dist->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LEFT_SHIFT_INT);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LEFT_SHIFT_LONG);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              break;
                            default:
                              assert(0);
                          }

                          int32_t mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_RIGHT_ARITHMETIC_SHIFT : {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                          int32_t mem_id_in1;
                          int32_t mem_id_out;
                          switch (type_dist->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_INT);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_LONG);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              break;
                            default:
                              assert(0);
                          }

                          int32_t mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_RIGHT_LOGICAL_SHIFT : {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                          int32_t mem_id_out;
                          int32_t mem_id_in1;
                          switch (type_dist->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_INT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_LONG);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              break;
                            default:
                              assert(0);
                          }

                          int32_t mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_BIT_AND : {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                          int32_t mem_id_out;
                          int32_t mem_id_in1;
                          int32_t mem_id_in2;
                          switch (type_dist->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_AND_INT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_AND_LONG);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            default:
                              assert(0);
                          }

                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_BIT_OR : {

                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                          int32_t mem_id_out;
                          int32_t mem_id_in1;
                          int32_t mem_id_in2;
                          switch (type_dist->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_OR_INT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_OR_LONG);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            default:
                              assert(0);
                          }

                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_BIT_XOR : {

                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                          int32_t mem_id_out;
                          int32_t mem_id_in1;
                          int32_t mem_id_in2;
                          switch (type_dist->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_XOR_INT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_XOR_LONG);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            default:
                              assert(0);
                          }

                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_BIT_NOT : {

                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));

                          assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                          int32_t mem_id_out;
                          int32_t mem_id_in;
                          switch (type_dist->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_NOT_INT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BIT_NOT_LONG);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              break;
                            default:
                              assert(0);
                          }
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_PLUS : {

                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                         
                          assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                          int32_t mem_id_out;
                          int32_t mem_id_in;
                          switch (type_dist->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_INT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_LONG);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_FLOAT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_DOUBLE);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              break;
                            default:
                              assert(0);
                          }
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_COPY : {

                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                         
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_COPY);
                          int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                          int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                          break;
                        }
                        case SPVM_OP_C_ID_MINUS : {

                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                         
                          assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                          int32_t mem_id_out;
                          int32_t mem_id_in;
                          switch (type_dist->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEGATE_INT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEGATE_LONG);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEGATE_FLOAT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEGATE_DOUBLE);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              break;
                            default:
                              assert(0);
                          }
                          
                          opcode.operand0 = mem_id_out;
                          opcode.operand1 = mem_id_in;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_CONSTANT : {
                          SPVM_CONSTANT* constant = op_assign_src->uv.constant;

                          if (SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));

                            int32_t mem_id_out;
                            switch (type_dist->basic_type->id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_CONSTANT_BYTE);
                                opcode.operand1 = (uint16_t)(uint8_t)constant->value.bval;
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_CONSTANT_INT);
                                opcode.operand1 = (uint32_t)constant->value.ival;
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_CONSTANT_LONG);
                                *(int64_t*)&opcode.operand1 = constant->value.lval;
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_CONSTANT_FLOAT);
                                opcode.operand1 = (uint32_t)constant->value.ival;
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_CONSTANT_DOUBLE);
                                *(double*)&opcode.operand1 = constant->value.dval;
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                break;
                              default:
                                assert(0);
                            }
     
                            opcode.operand0 = mem_id_out;
                           
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else if (SPVM_TYPE_is_string_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_STRING);

                            int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                            SPVM_CONSTANT* constant = op_assign_src->uv.constant;
                            
                            const char* constant_string_value = constant->value.oval;
                            int32_t constant_string_length = constant->string_length;
                            SPVM_CONSTANT_STRING* constant_string = SPVM_HASH_get(compiler->constant_string_symtable, constant_string_value, constant_string_length);
                            assert(constant_string);
                            
                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = constant_string->id;

                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else {
                            assert(0);
                          }
                          break;
                        }
                        case SPVM_OP_C_ID_CONVERT : {
                          
                          SPVM_OP* op_dist_term = op_assign_dist;
                          SPVM_OP* op_src_term = op_assign_src->first;
                          SPVM_OP* op_dist_type = op_assign_src->last;
                          
                          SPVM_TYPE* src_type = SPVM_OP_get_type(compiler, op_src_term);
                          SPVM_TYPE* dist_type = SPVM_OP_get_type(compiler, op_dist_type);
                          

                          if (SPVM_TYPE_is_byte_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            int32_t mem_id_out;
                            int32_t mem_id_in;

                            if (SPVM_TYPE_is_numeric_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_BYTE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_SHORT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_INT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_LONG);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_FLOAT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_DOUBLE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else {
                                assert(0);
                              }
                            }
                            else if (SPVM_TYPE_is_byte_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_BYTE_OBJECT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else if (SPVM_TYPE_is_any_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_BYTE_OBJECT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else if (SPVM_TYPE_is_string_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_STRING);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else {
                              assert(0);
                            }

                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else if (SPVM_TYPE_is_short_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            int32_t mem_id_out;
                            int32_t mem_id_in;
                            if (SPVM_TYPE_is_numeric_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_BYTE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_SHORT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_INT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_LONG);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_FLOAT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_DOUBLE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else {
                                assert(0);
                              }
                            }
                            else if (SPVM_TYPE_is_short_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_SHORT_OBJECT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else if (SPVM_TYPE_is_any_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_SHORT_OBJECT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else if (SPVM_TYPE_is_string_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_STRING);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else {
                              assert(0);
                            }
                            
                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else if (SPVM_TYPE_is_int_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            int32_t mem_id_out;
                            int32_t mem_id_in;
                            if (SPVM_TYPE_is_numeric_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_INT_TO_BYTE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_INT_TO_SHORT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_INT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_INT_TO_LONG);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_INT_TO_FLOAT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_INT_TO_DOUBLE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else {
                                assert(0);
                              }
                            }
                            else if (SPVM_TYPE_is_int_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_INT_TO_INT_OBJECT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else if (SPVM_TYPE_is_any_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_INT_TO_INT_OBJECT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else if (SPVM_TYPE_is_string_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_INT_TO_STRING);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else {
                              assert(0);
                            }
                            
                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else if (SPVM_TYPE_is_long_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            int32_t mem_id_out;
                            int32_t mem_id_in;
                            if (SPVM_TYPE_is_numeric_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_LONG_TO_BYTE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_LONG_TO_SHORT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_LONG_TO_INT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_LONG);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_LONG_TO_FLOAT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_LONG_TO_DOUBLE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else {
                                assert(0);
                              }
                            }
                            else if (SPVM_TYPE_is_long_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_LONG_TO_LONG_OBJECT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else if (SPVM_TYPE_is_any_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_LONG_TO_LONG_OBJECT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else if (SPVM_TYPE_is_string_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_LONG_TO_STRING);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else {
                              assert(0);
                            }
                            
                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else if (SPVM_TYPE_is_float_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            int32_t mem_id_out;
                            int32_t mem_id_in;
                            if (SPVM_TYPE_is_numeric_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_BYTE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_SHORT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_INT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_LONG);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_FLOAT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_DOUBLE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else {
                                assert(0);
                              }
                            }
                            else if (SPVM_TYPE_is_float_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_FLOAT_OBJECT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else if (SPVM_TYPE_is_any_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_FLOAT_OBJECT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else if (SPVM_TYPE_is_string_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_STRING);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else {
                              assert(0);
                            }
                            
                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else if (SPVM_TYPE_is_double_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            int32_t mem_id_out;
                            int32_t mem_id_in;
                            if (SPVM_TYPE_is_numeric_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_BYTE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_SHORT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_INT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_LONG);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_FLOAT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else if (dist_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_DOUBLE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                              }
                              else {
                                assert(0);
                              }
                            }
                            else if (SPVM_TYPE_is_double_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_DOUBLE_OBJECT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else if (SPVM_TYPE_is_any_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_DOUBLE_OBJECT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else if (SPVM_TYPE_is_string_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_STRING);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else {
                              assert(0);
                            }
                            
                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else if (SPVM_TYPE_is_byte_array_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            int32_t mem_id_out;
                            int32_t mem_id_in;
                            if (SPVM_TYPE_is_byte_array_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else if (SPVM_TYPE_is_string_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_BYTE_ARRAY_TO_STRING);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else if (SPVM_TYPE_is_any_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else {
                              assert(0);
                            }
                            
                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else if (SPVM_TYPE_is_string_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            int32_t mem_id_out;
                            int32_t mem_id_in;
                            if (SPVM_TYPE_is_string_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              if (dist_type->flag & SPVM_TYPE_C_FLAG_MUTABLE && !(src_type->flag & SPVM_TYPE_C_FLAG_MUTABLE)) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT_CHECK_READ_ONLY);
                              }
                              else {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                              }
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else if (SPVM_TYPE_is_byte_array_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_STRING_TO_BYTE_ARRAY);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else if (SPVM_TYPE_is_any_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                              mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                            }
                            else {
                              assert(0);
                            }
                            
                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            
                            if (opcode.id == SPVM_OPCODE_C_ID_MOVE_OBJECT_CHECK_READ_ONLY) {
                              SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                            }
                          }
                          // Check convert
                          else if (SPVM_TYPE_is_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            
                            // Object convert
                            {
                              SPVM_OPCODE opcode = {0};
                              int32_t mem_id_out;
                              int32_t mem_id_in;
                              if (SPVM_TYPE_is_byte_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                                if (SPVM_TYPE_is_byte_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_BYTE_OBJECT_TO_BYTE);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                                }
                                else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_BYTE_OBJECT_TO_BYTE);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                                }
                                else {
                                  assert(0);
                                }
                              }
                              else if (SPVM_TYPE_is_short_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                                if (SPVM_TYPE_is_short_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_SHORT_OBJECT_TO_SHORT);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                                }
                                else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_SHORT_OBJECT_TO_SHORT);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                                }
                                else {
                                  assert(0);
                                }
                              }                              
                              else if (SPVM_TYPE_is_int_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                                if (SPVM_TYPE_is_int_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_INT_OBJECT_TO_INT);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                                }
                                else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_INT_OBJECT_TO_INT);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                                }
                                else {
                                  assert(0);
                                }
                              }                              
                              else if (SPVM_TYPE_is_long_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                                if (SPVM_TYPE_is_long_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_LONG_OBJECT_TO_LONG);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                                }
                                else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_LONG_OBJECT_TO_LONG);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                                }
                                else {
                                  assert(0);
                                }
                              }                              
                              else if (SPVM_TYPE_is_float_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                                if (SPVM_TYPE_is_float_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_FLOAT_OBJECT_TO_FLOAT);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                                }
                                else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_FLOAT_OBJECT_TO_FLOAT);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                                }
                                else {
                                  assert(0);
                                }
                              }                              
                              else if (SPVM_TYPE_is_double_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                                if (SPVM_TYPE_is_double_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_DOUBLE_OBJECT_TO_DOUBLE);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                                }
                                else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CONVERT_DOUBLE_OBJECT_TO_DOUBLE);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                                }
                                else {
                                  assert(0);
                                }
                              }
                              else {
                                int32_t dist_type_basic_type_id = op_dist_type->uv.type->basic_type->id;
                                int32_t dist_type_dimension = op_dist_type->uv.type->dimension;
                                int32_t dist_type_flag = op_dist_type->uv.type->flag;
                                
                                int32_t src_type_basic_type_id = src_type->basic_type->id;
                                int32_t src_type_dimension = src_type->dimension;
                                int32_t src_type_flag = src_type->flag;

                                int32_t need_implicite_conversion = 0;
                                int32_t narrowing_conversion_error = 0;
                                int32_t mutable_invalid = 0;
                                
                                int32_t can_assign = SPVM_TYPE_can_assign(
                                  compiler,
                                  dist_type_basic_type_id, dist_type_dimension, dist_type_flag,
                                  src_type_basic_type_id, src_type_dimension, src_type_flag,
                                  NULL, &need_implicite_conversion, &narrowing_conversion_error, &mutable_invalid
                                );
                                
                                assert(need_implicite_conversion == 0);
                                assert(narrowing_conversion_error == 0);
                                assert(mutable_invalid == 0);
                                
                                if (can_assign) {
                                  // MOVE_OBJECT
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                                }
                                // CHECK_CALLBACK
                                else if (SPVM_TYPE_is_callback_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CHECK_CALLBACK);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                                  opcode.operand2 = op_dist_type->uv.type->basic_type->id;
                                }
                                // CHECK_INTERFACE
                                else if (SPVM_TYPE_is_interface_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CHECK_INTERFACE);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                                  opcode.operand2 = op_dist_type->uv.type->basic_type->id;
                                }
                                else {
                                  // CHECK_OBJECT_TYPE
                                  SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CHECK_OBJECT_TYPE);
                                  mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                                  mem_id_in = SPVM_OP_get_mem_id(compiler, op_src_term);
                                  opcode.operand2 = op_dist_type->uv.type->basic_type->id;
                                  opcode.operand3 = op_dist_type->uv.type->dimension;
                                }
                              }
                              
                              opcode.operand0 = mem_id_out;
                              opcode.operand1 = mem_id_in;
                              
                              SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                              
                              SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                            }
                          }
                          // Source is undef type
                          else if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            if (SPVM_TYPE_is_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                              SPVM_OPCODE opcode = {0};
                              
                              // MOVE_UNDEF
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_UNDEF);
                              
                              int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_dist_term);
                              opcode.operand0 = mem_id_out;
                              
                              SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            }
                            else {
                              assert(0);
                            }
                          }
                          break;
                        }
                        case SPVM_OP_C_ID_NEW : {
                          
                          if (op_assign_src->first->id == SPVM_OP_C_ID_TYPE) {
                            
                            SPVM_OP* op_type = op_assign_src->first;
                            
                            SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_assign_src->first);

                            // Runtime type
                            int32_t basic_type_id = type->basic_type->id;
                            int32_t type_dimension = type->dimension;
                            
                            if (type_dimension > 0) {
                              /*
                                NEW op_assign_src
                                   TYPE op_assign_src->first
                                     ELEMENT_TYPE op_assign_src->first->first
                                     INDEX op_assign_src->first->last
                              */
                              
                              if (type_dimension == 1) {
                                switch (basic_type_id) {
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                    SPVM_OPCODE opcode;
                                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_BYTE_ARRAY);

                                    int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                    int32_t mem_id_index = SPVM_OP_get_mem_id(compiler, op_assign_src->first->last);

                                    opcode.operand0 = mem_id_out;
                                    opcode.operand1 = mem_id_index;

                                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                                    SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                                    
                                    break;
                                  }
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                    SPVM_OPCODE opcode;
                                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY);

                                    int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                    int32_t mem_id_index = SPVM_OP_get_mem_id(compiler, op_assign_src->first->last);
                                    
                                    opcode.operand0 = mem_id_out;
                                    opcode.operand1 = mem_id_index;

                                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                                    SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                                    
                                    break;
                                  }
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                    SPVM_OPCODE opcode;
                                    memset(&opcode, 0, sizeof(SPVM_OPCODE));

                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_INT_ARRAY);

                                    int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                    int32_t mem_id_index = SPVM_OP_get_mem_id(compiler, op_assign_src->first->last);

                                    opcode.operand0 = mem_id_out;
                                    opcode.operand1 = mem_id_index;

                                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                                    SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                                    
                                    break;
                                  }
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                    SPVM_OPCODE opcode;
                                    memset(&opcode, 0, sizeof(SPVM_OPCODE));

                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_LONG_ARRAY);

                                    int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                    int32_t mem_id_index = SPVM_OP_get_mem_id(compiler, op_assign_src->first->last);

                                    opcode.operand0 = mem_id_out;
                                    opcode.operand1 = mem_id_index;

                                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                                    
                                    SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);

                                    break;
                                  }
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                    SPVM_OPCODE opcode;
                                    memset(&opcode, 0, sizeof(SPVM_OPCODE));

                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY);

                                    int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                    int32_t mem_id_index = SPVM_OP_get_mem_id(compiler, op_assign_src->first->last);

                                    opcode.operand0 = mem_id_out;
                                    opcode.operand1 = mem_id_index;

                                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                                    
                                    SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);

                                    break;
                                  }
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                    SPVM_OPCODE opcode;
                                    memset(&opcode, 0, sizeof(SPVM_OPCODE));

                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY);
                                    
                                    int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                    int32_t mem_id_index = SPVM_OP_get_mem_id(compiler, op_assign_src->first->last);

                                    opcode.operand0 = mem_id_out;
                                    opcode.operand1 = mem_id_index;

                                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                                    SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);

                                    break;
                                  }
                                  default: {
                                    if (SPVM_TYPE_is_mulnum_array_type(compiler, basic_type_id, type_dimension, type->flag)) {
                                      SPVM_OPCODE opcode;
                                      memset(&opcode, 0, sizeof(SPVM_OPCODE));

                                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_MULNUM_ARRAY);

                                      int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                      int32_t mem_id_index = SPVM_OP_get_mem_id(compiler, op_assign_src->first->last);

                                      opcode.operand0 = mem_id_out;
                                      opcode.operand1 = op_type->uv.type->basic_type->id;
                                      opcode.operand2 = mem_id_index;

                                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                                      SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                                    }
                                    else {
                                      SPVM_OPCODE opcode;
                                      memset(&opcode, 0, sizeof(SPVM_OPCODE));

                                      SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY);

                                      int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                      int32_t mem_id_index = SPVM_OP_get_mem_id(compiler, op_assign_src->first->last);

                                      opcode.operand0 = mem_id_out;
                                      opcode.operand1 = op_type->uv.type->basic_type->id;
                                      opcode.operand2 = mem_id_index;

                                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                                      SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                                    }
                                  }
                                }
                              }
                              else if (type_dimension > 1) {
                                SPVM_OPCODE opcode;
                                memset(&opcode, 0, sizeof(SPVM_OPCODE));

                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_MULTI_ARRAY);

                                int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                int32_t mem_id_index = SPVM_OP_get_mem_id(compiler, op_assign_src->first->last);

                                opcode.operand0 = mem_id_out;
                                opcode.operand1 = op_type->uv.type->basic_type->id;
                                opcode.operand2 = mem_id_index;
                                opcode.operand3 = op_type->uv.type->dimension - 1;

                                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                                SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                              }
                              else {
                                assert(0);
                              }
                            }
                            else {
                              SPVM_OPCODE opcode;
                              memset(&opcode, 0, sizeof(SPVM_OPCODE));

                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NEW_OBJECT);
                              
                              int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                              
                              opcode.operand0 = mem_id_out;
                              opcode.operand1 = type->basic_type->id;
                              SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            }
                          }
                          else {
                            assert(0);
                          }
                          break;
                        }
                        case SPVM_OP_C_ID_VAR : {
                          // Multi numeric type
                          if (SPVM_TYPE_is_mulnum_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                            SPVM_CLASS* value_class = type_dist->basic_type->class;
                            assert(class);
                            
                            SPVM_FIELD* first_field = SPVM_LIST_get(value_class->fields, 0);
                            assert(first_field);
                            
                            SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, first_field->op_field);
                            assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                            
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            
                            int32_t mem_id_out;
                            int32_t mem_id_in;
                            switch (field_type->basic_type->id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_BYTE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_SHORT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_INT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_LONG);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_FLOAT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_MULNUM_DOUBLE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              }
                              default:
                                assert(0);
                            }

                            int32_t fields_length = value_class->fields->length;
                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            opcode.operand2 = fields_length;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          // Object type
                          else if (SPVM_TYPE_is_object_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_OBJECT);
                            int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                            int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);

                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            
                          }
                          else if (SPVM_TYPE_is_ref_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag)) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_REF);
                            int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                            int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);

                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            
                          }
                          // Numeric type
                          else {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            
                            assert(SPVM_TYPE_is_numeric_type(compiler, type_dist->basic_type->id, type_dist->dimension, type_dist->flag));
                            
                            int32_t mem_id_out;
                            int32_t mem_id_in;
                            switch (type_dist->basic_type->id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_BYTE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_SHORT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_INT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_LONG);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_FLOAT);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MOVE_DOUBLE);
                                mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                                break;
                              default:
                                assert(0);
                            }

                            opcode.operand0 = mem_id_out;
                            opcode.operand1 = mem_id_in;
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          break;
                        }
                        case SPVM_OP_C_ID_NUMERIC_EQ : {
                          if (op_assign_src->first->id == SPVM_OP_C_ID_UNDEF || op_assign_src->last->id == SPVM_OP_C_ID_UNDEF) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));

                            int32_t mem_id_in;

                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_UNDEF);
                            if (op_assign_src->first->id == SPVM_OP_C_ID_UNDEF) {
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              
                              opcode.operand1 = mem_id_in;

                              SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            }
                            else {
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              
                              opcode.operand1 = mem_id_in;
                              
                              SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            }
                          }
                          else {
                            SPVM_TYPE* operand_type = SPVM_OP_get_type(compiler, op_assign_src->first);
                            
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            
                            int32_t mem_id_in1;
                            int32_t mem_id_in2;
                            if (SPVM_TYPE_is_numeric_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                              if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                                assert(0);
                              }
                              else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                                assert(0);
                              }
                              else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_EQ_INT);
                                mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                                mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              }
                              else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_EQ_LONG);
                                mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                                mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              }
                              else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_EQ_FLOAT);
                                mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                                mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              }
                              else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_EQ_DOUBLE);
                                mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                                mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              }
                              else {
                                assert(0);
                              }
                            }
                            else if (SPVM_TYPE_is_object_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_EQ_OBJECT);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                            }
                            else {
                              assert(0);
                            }
                            
                            opcode.operand1 = mem_id_in1;
                            opcode.operand2 = mem_id_in2;

                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          break;
                        }
                        case SPVM_OP_C_ID_NUMERIC_NE : {
                          if (op_assign_src->first->id == SPVM_OP_C_ID_UNDEF ||op_assign_src->last->id == SPVM_OP_C_ID_UNDEF) {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            
                            int32_t mem_id_in;

                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_NOT_UNDEF);
                            if (op_assign_src->first->id == SPVM_OP_C_ID_UNDEF) {
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              
                              opcode.operand1 = mem_id_in;
                            }
                            else {
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              
                              opcode.operand1 = mem_id_in;
                            }
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          else {
                            SPVM_TYPE* operand_type = SPVM_OP_get_type(compiler, op_assign_src->first);

                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            
                            int32_t mem_id_in1;
                            int32_t mem_id_in2;
                            if (SPVM_TYPE_is_numeric_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                              if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                                assert(0);
                              }
                              else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                                assert(0);
                              }
                              else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NE_INT);
                                mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                                mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              }
                              else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NE_LONG);
                                mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                                mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              }
                              else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NE_FLOAT);
                                mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                                mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              }
                              else if (operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NE_DOUBLE);
                                mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                                mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              }
                              else {
                                assert(0);
                              }
                            }
                            else if (SPVM_TYPE_is_object_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_NE_OBJECT);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                            }
                            else {
                              assert(0);
                            }
                            
                            opcode.operand1 = mem_id_in1;
                            opcode.operand2 = mem_id_in2;

                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          break;
                        }
                        case SPVM_OP_C_ID_NUMERIC_GT : {
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          SPVM_TYPE* operand_type = SPVM_OP_get_type(compiler, op_assign_src->first);

                          int32_t mem_id_in1;
                          int32_t mem_id_in2;
                          switch (operand_type->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GT_INT);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GT_LONG);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GT_FLOAT);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GT_DOUBLE);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            default:
                              assert(0);
                          }
                          
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_NUMERIC_GE : {
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          SPVM_TYPE* operand_type = SPVM_OP_get_type(compiler, op_assign_src->first);

                          int32_t mem_id_in1;
                          int32_t mem_id_in2;
                          switch (operand_type->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GE_INT);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GE_LONG);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GE_FLOAT);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GE_DOUBLE);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            default:
                              assert(0);
                          }
                          
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_NUMERIC_LT : {
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          SPVM_TYPE* operand_type = SPVM_OP_get_type(compiler, op_assign_src->first);

                          int32_t mem_id_in1;
                          int32_t mem_id_in2;
                          switch (operand_type->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LT_INT);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LT_LONG);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LT_FLOAT);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LT_DOUBLE);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            default:
                              assert(0);
                          }
                          
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_NUMERIC_LE : {
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          SPVM_TYPE* operand_type = SPVM_OP_get_type(compiler, op_assign_src->first);

                          int32_t mem_id_in1;
                          int32_t mem_id_in2;
                          switch (operand_type->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LE_INT);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LE_LONG);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LE_FLOAT);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_LE_DOUBLE);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            default:
                              assert(0);
                          }
                          
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          break;
                        }
                        case SPVM_OP_C_ID_NUMERIC_CMP : {
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          SPVM_TYPE* operand_type = SPVM_OP_get_type(compiler, op_assign_src->first);

                          int32_t mem_id_in1;
                          int32_t mem_id_in2;
                          switch (operand_type->basic_type->id) {
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CMP_INT);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CMP_LONG);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CMP_FLOAT);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_CMP_DOUBLE);
                              mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                              break;
                            default:
                              assert(0);
                          }
                          
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;

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
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
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
                          
                          int32_t mem_id_in1 = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                          int32_t mem_id_in2 = SPVM_OP_get_mem_id(compiler, op_assign_src->last);
                          
                          opcode.operand1 = mem_id_in1;
                          opcode.operand2 = mem_id_in2;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                          break;
                        }
                        case  SPVM_OP_C_ID_BOOL: {
                          SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_assign_src->first);
                          
                          if (op_assign_src->first->id != SPVM_OP_C_ID_IF) {

                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            
                            int32_t mem_id_in;
                            if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                              if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                                assert(0);
                              }
                              else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                                assert(0);
                              }
                              else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BOOL_INT);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              }
                              else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BOOL_LONG);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              }
                              else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BOOL_FLOAT);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              }
                              else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BOOL_DOUBLE);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              }
                              else {
                                assert(0);
                              }
                            }
                            else if (SPVM_TYPE_is_bool_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BOOL_BOOL_OBJECT);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                            }
                            else if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_BOOL_OBJECT);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                            }
                            else {
                              assert(0);
                            }
                            opcode.operand1 = mem_id_in;

                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          
                          break;
                        }
                        case SPVM_OP_C_ID_ISA: {
                          int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                          
                          SPVM_OP* op_type = op_assign_src->last;
                          SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_type);
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          if (SPVM_TYPE_is_callback_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_HAS_CALLBACK);
                          }
                          else if (SPVM_TYPE_is_interface_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_HAS_INTERFACE);
                          }
                          else {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IS_TYPE);
                          }

                          opcode.operand1 = mem_id_in;

                          opcode.operand2 = type->basic_type->id;
                          opcode.operand3 = type->dimension;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                          break;
                        }
                        case SPVM_OP_C_ID_HAS_IMPLEMENT: {
                          SPVM_OP* op_var = op_assign_src->first;
                          int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_var);

                          SPVM_TYPE* interface_type = SPVM_OP_get_type(compiler, op_var);
                          SPVM_BASIC_TYPE* interface_basic_type = interface_type->basic_type;
                          SPVM_CLASS* interface_class = interface_basic_type->class;
                          
                          SPVM_OP* op_name_implement_method = op_assign_src->last;

                          const char* implement_method_name = op_name_implement_method->uv.name;
                          SPVM_METHOD* implement_method = SPVM_HASH_get(interface_class->method_symtable, implement_method_name, strlen(implement_method_name));
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_HAS_IMPLEMENT);

                          opcode.operand1 = mem_id_in;
                          opcode.operand2 = implement_method->id;
                          opcode.operand3 = interface_basic_type->id;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                          break;
                        }
                        case SPVM_OP_C_ID_SWITCH_CONDITION: {
                          assert(switch_info_stack->length > 0);
                          
                          SPVM_SWITCH_INFO* switch_info = SPVM_LIST_get(switch_info_stack, switch_info_stack->length - 1);;

                          int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                          
                          int32_t opcode_id = opcode_array->length;
                          switch_info->opcode_id = opcode_id;

                          // Add switch opcode
                          SPVM_OPCODE opcode_switch_info;
                          memset(&opcode_switch_info, 0, sizeof(SPVM_OPCODE));
                          opcode_switch_info.id = SPVM_OPCODE_C_ID_LOOKUP_SWITCH;
                          opcode_switch_info.operand0 = mem_id_in;
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode_switch_info);

                          // Match values and branchs
                          for (int32_t i = 0; i < switch_info->case_infos->length; i++) {
                            SPVM_CASE_INFO* case_info = SPVM_LIST_get(switch_info->case_infos, i);
                            
                            // Branch
                            SPVM_CASE_INFO* branch_opcode_rel_index_case_info = switch_info->case_infos->values[i];
                            branch_opcode_rel_index_case_info->opcode_rel_index = case_info->opcode_rel_index;
                            
                            // Add case info
                            SPVM_OPCODE opcode_case_info;
                            memset(&opcode_case_info, 0, sizeof(SPVM_OPCODE));
                            opcode_case_info.id = SPVM_OPCODE_C_ID_CASE_INFO;
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode_case_info);
                          }

                          // Default branch
                          int32_t default_opcode_rel_index = switch_info->default_opcode_rel_index;
                          if (default_opcode_rel_index == 0) {
                            default_opcode_rel_index = opcode_array->length + 1 - method_opcodes_base_id;
                          }
                          switch_info->default_opcode_rel_index = default_opcode_rel_index;

                          break;
                        }
                        case SPVM_OP_C_ID_SWITCH: {
                          
                          // Pop switch information
                          SPVM_SWITCH_INFO* switch_info = SPVM_LIST_pop(switch_info_stack);
                          
                          // Set the information of switch opcodes
                          int32_t opcode_id = switch_info->opcode_id;
                          SPVM_OPCODE* opcode = (SPVM_OPCODE*)&opcode_array->values[opcode_id];
                          opcode->operand1 = switch_info->switch_id;
                          opcode->operand2 = switch_info->default_opcode_rel_index;
                          opcode->operand3 = switch_info->case_infos->length;

                          // Set case info operands
                          SPVM_LIST* case_infos = switch_info->case_infos;
                          for (int32_t i = 0; i < switch_info->case_infos->length; i++) {
                            SPVM_OPCODE* opcode_case_info = (SPVM_OPCODE*)&opcode_array->values[opcode_id + 1 + i];
                            SPVM_CASE_INFO* case_info = SPVM_LIST_get(case_infos, i);
                            opcode_case_info->operand1 = case_info->condition_value;
                            opcode_case_info->operand2 = case_info->opcode_rel_index;
                          }
                          
                          break;
                        }
                        case SPVM_OP_C_ID_DIE: {
                          
                          // SET_DIE_FLAG_TRUE
                          {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_DIE_FLAG_TRUE);
                            
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          
                          SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                          
                          break;
                        }
                        case SPVM_OP_C_ID_WARN: {
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_WARN);
                          
                          int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                          opcode.operand0 = mem_id_in;
                          opcode.operand1 = op_cur->line;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                          break;
                        }
                        case SPVM_OP_C_ID_PRINT: {
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_PRINT);
                          
                          int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                          opcode.operand0 = mem_id_in;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                          break;
                        }
                        case SPVM_OP_C_ID_MAKE_READ_ONLY: {
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_MAKE_READ_ONLY);
                          
                          int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                          opcode.operand0 = mem_id_in;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                          break;
                        }
                        case SPVM_OP_C_ID_RETURN: {
                          if (op_assign_src->first) {
                            SPVM_TYPE* return_type = SPVM_OP_get_type(compiler, op_assign_src->first);
                            
                            if (SPVM_TYPE_is_undef_type(compiler, return_type->basic_type->id, return_type->dimension, return_type->flag)) {
                              SPVM_OPCODE opcode;
                              memset(&opcode, 0, sizeof(SPVM_OPCODE));
                              
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_UNDEF);
                              
                              SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            }
                            else {
                              SPVM_OPCODE opcode;
                              memset(&opcode, 0, sizeof(SPVM_OPCODE));
                               
                              
                              int32_t mem_id_in;
                              if (SPVM_TYPE_is_numeric_type(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag)) {
                                switch (method->return_type->basic_type->id) {
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_BYTE);
                                    mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                                    break;
                                  }
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_SHORT);
                                    mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                                    break;
                                  }
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_INT);
                                    mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                                    break;
                                  }
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_LONG);
                                    mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                                    break;
                                  }
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_FLOAT);
                                    mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                                    break;
                                  }
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_DOUBLE);
                                    mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                                    break;
                                  }
                                  default:
                                    assert(0);
                                }
                              }
                              else if (SPVM_TYPE_is_object_type(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag)) {
                                SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_OBJECT);
                                mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                              }
                              else if (SPVM_TYPE_is_mulnum_type(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag)) {
                                SPVM_CLASS* value_class = return_type->basic_type->class;
                                assert(class);
                                
                                SPVM_FIELD* first_field = SPVM_LIST_get(value_class->fields, 0);
                                assert(first_field);
                                
                                SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, first_field->op_field);
                                assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));

                                switch (field_type->basic_type->id) {
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                    mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_MULNUM_BYTE);
                                    break;
                                  }
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                    mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_MULNUM_SHORT);
                                    break;
                                  }
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                    mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_MULNUM_INT);
                                    break;
                                  }
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                    mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_MULNUM_LONG);
                                    break;
                                  }
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                    mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
                                    SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_MULNUM_FLOAT);
                                    break;
                                  }
                                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                    mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src->first);
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
                              
                              int32_t method_return_type_width = SPVM_TYPE_get_width(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag);

                              opcode.operand0 = mem_id_in;
                              opcode.operand2 = method_return_type_width;
                              
                              SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            }
                          }
                          else {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_RETURN_VOID);
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                          
                          int32_t return_opcode_rel_index = opcode_array->length - 1 - method_opcodes_base_id;
                          
                          SPVM_LIST_push(return_goto_opcode_rel_index_stack, (void*)(intptr_t)return_opcode_rel_index);
                          
                          break;
                        }
                        case SPVM_OP_C_ID_LAST: {
                          // GOTO end of loop init block
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GOTO);
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                          int32_t opcode_rel_index = opcode_array->length - 1 - method_opcodes_base_id;
                          
                          SPVM_LIST_push(last_goto_opcode_rel_index_stack, (void*)(intptr_t)opcode_rel_index);
                          
                          break;
                        }
                        case SPVM_OP_C_ID_BREAK: {
                          // GOTO end of switch block
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GOTO);
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                          int32_t opcode_rel_index = opcode_array->length - 1 - method_opcodes_base_id;
                          
                          SPVM_LIST_push(break_goto_opcode_rel_index_stack, (void*)(intptr_t)opcode_rel_index);
                          
                          break;
                        }
                        case SPVM_OP_C_ID_NEXT: {
                          // GOTO increment statement
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_GOTO);
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                          int32_t opcode_rel_index = opcode_array->length - 1 - method_opcodes_base_id;
                          
                          SPVM_LIST_push(next_goto_opcode_rel_index_stack, (void*)(intptr_t)opcode_rel_index);
                          
                          break;
                        }
                        case SPVM_OP_C_ID_LOOP_INCREMENT: {
                          // Set loop first GOTO opcode
                          int32_t loop_first_goto_opcode_rel_index = (intptr_t)SPVM_LIST_get(loop_first_goto_opcode_rel_index_stack, loop_first_goto_opcode_rel_index_stack->length - 1);
                          
                          SPVM_OPCODE* loop_first_goto = (opcode_array->values + method_opcodes_base_id + loop_first_goto_opcode_rel_index);
                          int32_t loop_first_goto_jump_opcode_rel_index = opcode_array->length - method_opcodes_base_id;
                          loop_first_goto->operand0 = loop_first_goto_jump_opcode_rel_index;
                          
                          break;
                        }
                        case SPVM_OP_C_ID_CONDITION:
                        case SPVM_OP_C_ID_CONDITION_NOT:
                        {
                          
                          int32_t opcode_rel_index = opcode_array->length - method_opcodes_base_id;

                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));

                          if (op_assign_src->id == SPVM_OP_C_ID_CONDITION) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IF_EQ_ZERO);
                          }
                          else {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_IF_NE_ZERO);
                          }
                          
                          if (op_assign_src->flag & SPVM_OP_C_FLAG_CONDITION_IF) {
                            SPVM_LIST_push(if_eq_or_if_ne_goto_opcode_rel_index_stack, (void*)(intptr_t)opcode_rel_index);
                          }
                          else if (op_assign_src->flag & SPVM_OP_C_FLAG_CONDITION_LOOP) {
                            assert(loop_first_goto_opcode_rel_index_stack->length > 0);
                            
                            int32_t loop_first_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(loop_first_goto_opcode_rel_index_stack);
                            
                            opcode.operand0 = loop_first_goto_opcode_rel_index + 1;
                          }
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                          break;
                        }
                      }
                    }
                    else if (op_assign_dist->id == SPVM_OP_C_ID_CLASS_VAR_ACCESS) {
                      SPVM_OP* op_class_var_access = op_assign_dist;
                      SPVM_CLASS_VAR_ACCESS* class_var_access = op_class_var_access->uv.class_var_access;

                      SPVM_TYPE* src_type = SPVM_OP_get_type(compiler, op_assign_src);

                      // CLASS_VAR_ACCESS = UNDEF
                      if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_UNDEF);
                        opcode.operand0 = class_var_access->class_var->id;
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      // CLASS_VAR_ACCESS = VAR
                      else {
                        SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_class_var_access);

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        int32_t mem_id_in;
                        if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_OBJECT);
                          mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                        }
                        else {
                          if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_BYTE);
                            mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                          }
                          else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_SHORT);
                            mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                          }
                          else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_INT);
                            mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                          }
                          else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_LONG);
                            mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                          }
                          else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_FLOAT);
                            mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                          }
                          else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_CLASS_VAR_DOUBLE);
                            mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                          }
                          else {
                            assert(0);
                          }
                        }
                                          
                        opcode.operand0 = class_var_access->class_var->id;
                        opcode.operand1 = mem_id_in;
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                    }
                    else if (op_assign_dist->id == SPVM_OP_C_ID_DEREF) {
                      SPVM_OP* op_deref = op_assign_dist;

                      SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_deref->first);

                      SPVM_OPCODE opcode;
                      memset(&opcode, 0, sizeof(SPVM_OPCODE));
                      
                      assert(SPVM_TYPE_is_numeric_ref_type(compiler, type->basic_type->id, type->dimension, type->flag));
                      int32_t mem_id_in;
                      if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_DEREF_BYTE);
                        mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                      }
                      else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_DEREF_SHORT);
                        mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                      }
                      else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_DEREF_INT);
                        mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                      }
                      else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_DEREF_LONG);
                        mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                      }
                      else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_DEREF_FLOAT);
                        mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                      }
                      else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_DEREF_DOUBLE);
                        mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                      }
                      else {
                        assert(0);
                      }
                      
                      int32_t mem_id_out = SPVM_OP_get_mem_id(compiler, op_assign_dist);
                      
                      opcode.operand0 = mem_id_out;
                      opcode.operand1 = mem_id_in;
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    }
                    else if (op_assign_dist->id == SPVM_OP_C_ID_EXCEPTION_VAR) {
                      
                      SPVM_TYPE* src_type = SPVM_OP_get_type(compiler, op_assign_src);
                      
                      if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                        // EXCEPTION_VAR = undef
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR_UNDEF);
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else {
                        // EXCEPTION_VAR = VAR
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR);
                        int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                        opcode.operand0 = mem_id_in;
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                    }
                    else if (op_assign_dist->id == SPVM_OP_C_ID_ARRAY_ACCESS) {
                      
                      // $VAR_ARRAY->[$VAR_INDEX] = $VAR_TERM
                      
                      SPVM_OP* op_array_access = op_assign_dist;
                      SPVM_OP* op_term_array = op_array_access->first;
                      SPVM_OP* op_term_index = op_array_access->last;

                      SPVM_TYPE* array_type = SPVM_OP_get_type(compiler, op_term_array);
                      int32_t array_type_dimension = array_type->dimension;
                      int32_t array_basic_type_id = array_type->basic_type->id;
                      int32_t array_basic_type_category = array_type->basic_type->category;

                      if (SPVM_TYPE_is_any_object_array_type(compiler, array_type->basic_type->id, array_type->dimension, array_type->flag)) {
                        SPVM_TYPE* src_type = SPVM_OP_get_type(compiler, op_assign_src);

                        if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_UNDEF);
                          
                          int32_t mem_id_array = SPVM_OP_get_mem_id(compiler, op_term_array);
                          int32_t mem_id_index = SPVM_OP_get_mem_id(compiler, op_term_index);
                          
                          opcode.operand0 = mem_id_array;
                          opcode.operand1 = mem_id_index;
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                        }
                        else {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE);
                          int32_t mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                          
                          int32_t mem_id_array = SPVM_OP_get_mem_id(compiler, op_term_array);
                          int32_t mem_id_index = SPVM_OP_get_mem_id(compiler, op_term_index);
                          
                          opcode.operand0 = mem_id_array;
                          opcode.operand1 = mem_id_index;
                          opcode.operand2 = mem_id_in;
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                        }
                      }
                      else if (SPVM_TYPE_is_mulnum_array_type(compiler, array_type->basic_type->id, array_type->dimension, array_type->flag)) {
                        SPVM_CLASS* class = array_type->basic_type->class;
                        SPVM_FIELD* first_field = SPVM_LIST_get(class->fields, 0);
                      
                        SPVM_TYPE* element_type = SPVM_OP_get_type(compiler, first_field->op_field);

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        assert(SPVM_TYPE_is_numeric_type(compiler, element_type->basic_type->id, element_type->dimension, element_type->flag));
                        int32_t mem_id_in;
                        if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_BYTE);
                          mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_SHORT);
                          mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_INT);
                          mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_LONG);
                          mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FLOAT);
                          mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                        }
                        else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_DOUBLE);
                          mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                        }
                        else {
                          assert(0);
                        }

                        int32_t mem_id_array = SPVM_OP_get_mem_id(compiler, op_term_array);
                        int32_t mem_id_index = SPVM_OP_get_mem_id(compiler, op_term_index);
                        int32_t fields_length = array_type->basic_type->class->fields->length;
                        
                        opcode.operand0 = mem_id_array;
                        opcode.operand1 = mem_id_index;
                        opcode.operand2 = mem_id_in;
                        opcode.operand3 = fields_length;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                        SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                      }
                      else {
                      
                        SPVM_TYPE* element_type = SPVM_OP_get_type(compiler, op_assign_src);

                        if (SPVM_TYPE_is_undef_type(compiler, element_type->basic_type->id, element_type->dimension, element_type->flag)) {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_UNDEF);
                          
                          int32_t mem_id_array = SPVM_OP_get_mem_id(compiler, op_term_array);
                          int32_t mem_id_index = SPVM_OP_get_mem_id(compiler, op_term_index);
                          
                          opcode.operand0 = mem_id_array;
                          opcode.operand1 = mem_id_index;
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                        }
                        else {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          int32_t mem_id_in;
                          if (SPVM_TYPE_is_numeric_type(compiler, element_type->basic_type->id, element_type->dimension, element_type->flag)) {
                            if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_BYTE);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                            }
                            else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_SHORT);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                            }
                            else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_INT);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                            }
                            else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_LONG);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                            }
                            else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_FLOAT);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                            }
                            else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_DOUBLE);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
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
                                case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CALLBACK:
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
                            mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                          }
                          
                          int32_t mem_id_array = SPVM_OP_get_mem_id(compiler, op_term_array);
                          int32_t mem_id_index = SPVM_OP_get_mem_id(compiler, op_term_index);
                          
                          opcode.operand0 = mem_id_array;
                          opcode.operand1 = mem_id_index;
                          opcode.operand2 = mem_id_in;
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                        }
                      }
                    }
                    // Set field
                    else if (op_assign_dist->id == SPVM_OP_C_ID_FIELD_ACCESS) {
                      
                      SPVM_OP* op_field_access = op_assign_dist;
                      SPVM_OP* op_term_invocant = op_field_access->first;

                      // Call field
                      SPVM_FIELD_ACCESS* field_access = op_field_access->uv.field_access;

                      SPVM_TYPE* src_type = SPVM_OP_get_type(compiler, op_assign_src);
                      
                      SPVM_TYPE* invocant_type = SPVM_OP_get_type(compiler, op_term_invocant);
                      
                      if (SPVM_TYPE_is_mulnum_ref_type(compiler, invocant_type->basic_type->id, invocant_type->dimension, invocant_type->flag)) {
                        SPVM_FIELD* field = field_access->field;
                        
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        int32_t mem_id_in;
                        switch (src_type->basic_type->id) {
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_BYTE);
                            mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_SHORT);
                            mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_INT);
                            mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_LONG);
                            mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_FLOAT);
                            mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                            break;
                          case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_DOUBLE);
                            mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                            break;
                          default:
                            assert(0);
                        }

                        int32_t mem_id_invocant = SPVM_OP_get_mem_id(compiler, op_term_invocant);
                        int32_t field_offset = field->index;

                        opcode.operand0 = mem_id_invocant;
                        opcode.operand1 = mem_id_in;
                        opcode.operand2 = field_offset;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (SPVM_TYPE_is_mulnum_type(compiler, invocant_type->basic_type->id, invocant_type->dimension, invocant_type->flag)) {
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        assert(SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag));
                        int32_t mem_id_out;
                        int32_t mem_id_in;
                        if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_BYTE);
                          mem_id_out = SPVM_OP_get_mem_id(compiler, op_term_invocant);
                          mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                        }
                        else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_SHORT);
                          mem_id_out = SPVM_OP_get_mem_id(compiler, op_term_invocant);
                          mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                        }
                        else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_INT);
                          mem_id_out = SPVM_OP_get_mem_id(compiler, op_term_invocant);
                          mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                        }
                        else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_LONG);
                          mem_id_out = SPVM_OP_get_mem_id(compiler, op_term_invocant);
                          mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                        }
                        else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_FLOAT);
                          mem_id_out = SPVM_OP_get_mem_id(compiler, op_term_invocant);
                          mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                        }
                        else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DOUBLE);
                          mem_id_out = SPVM_OP_get_mem_id(compiler, op_term_invocant);
                          mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                        }
                        else {
                          assert(0);
                        }
                        
                        SPVM_FIELD* field = field_access->field;
                        int32_t field_offset = field->index;
                        
                        opcode.operand0 = mem_id_out;
                        opcode.operand1 = mem_id_in;
                        opcode.operand2 = field_offset;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else {
                        if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_UNDEF);
                          
                          int32_t mem_id_invocant = SPVM_OP_get_mem_id(compiler, op_term_invocant);

                          opcode.operand0 = mem_id_invocant;
                          opcode.operand1 = field_access->field->id;
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                        }
                        else {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          int32_t mem_id_in;
                          if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_BYTE);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                            }
                            else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_SHORT);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                            }
                            else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_INT);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                            }
                            else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_LONG);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                            }
                            else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_FLOAT);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                            }
                            else if (src_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                              SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE);
                              mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                            }
                            else {
                              assert(0);
                            }
                          }
                          else if (SPVM_TYPE_is_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_FIELD_OBJECT);
                            mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                          }
                          else {
                            assert(0);
                          }
                          
                          int32_t mem_id_invocant = SPVM_OP_get_mem_id(compiler, op_term_invocant);
                          
                          opcode.operand0 = mem_id_invocant;
                          opcode.operand1 = field_access->field->id;
                          opcode.operand2 = mem_id_in;
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
                        }
                      }
                    }
                    // Set field
                    else if (op_assign_dist->id == SPVM_OP_C_ID_ARRAY_FIELD_ACCESS) {
                      
                      SPVM_OP* op_array_field_access = op_assign_dist;
                      SPVM_OP* op_term_invocant = op_array_field_access->first;
                      SPVM_OP* op_term_index = op_array_field_access->last;

                      // Call field
                      SPVM_ARRAY_FIELD_ACCESS* array_field_access = op_array_field_access->uv.array_field_access;
                      SPVM_FIELD* field = array_field_access->field;

                      // Array type
                      SPVM_TYPE* array_type = SPVM_OP_get_type(compiler, op_array_field_access->first);
                      SPVM_BASIC_TYPE* array_basic_type = array_type->basic_type;

                      // Element type
                      SPVM_TYPE* element_type = SPVM_OP_get_type(compiler, op_assign_src);
                      
                      SPVM_OPCODE opcode;
                      memset(&opcode, 0, sizeof(SPVM_OPCODE));
                      
                      int32_t mem_id_in;
                      if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_BYTE);
                        mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                      }
                      else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_SHORT);
                        mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                      }
                      else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_INT);
                        mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                      }
                      else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_LONG);
                        mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                      }
                      else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_FLOAT);
                        mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                      }
                      else if (element_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                        SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode, SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_DOUBLE);
                        mem_id_in = SPVM_OP_get_mem_id(compiler, op_assign_src);
                      }
                      else {
                        assert(0);
                      }
                      
                      int32_t mem_id_invocant = SPVM_OP_get_mem_id(compiler, op_term_invocant);
                      int32_t mem_id_index = SPVM_OP_get_mem_id(compiler, op_term_index);

                      int32_t fields_length = array_basic_type->class->fields->length;
                      int32_t field_offset = field->index;
                      
                      opcode.operand0 = mem_id_invocant;
                      opcode.operand1 = mem_id_index;
                      opcode.operand2 = mem_id_in;
                      opcode.operand3 = (field_offset << 8) + (fields_length - 1);
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                      SPVM_OPCODE_BUILDER_push_if_die(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_die_catch_goto_opcode_rel_index_stack, if_die_return_goto_opcode_rel_index_stack, method->op_method, op_cur->line);
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

          SPVM_OPCODE opcode;
          memset(&opcode, 0, sizeof(SPVM_OPCODE));
          SPVM_OPCODE_BUILDER_set_opcode_id(compiler, &opcode,  SPVM_OPCODE_C_ID_END_METHOD);
          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

          method->opcodes_length = opcode_array->length - method->opcodes_base_id;
          
          method->mortal_stack_length = mortal_stack_top_max + 1;
          
          // Free list
          SPVM_LIST_free(if_eq_or_if_ne_goto_opcode_rel_index_stack);
          SPVM_LIST_free(if_block_end_goto_opcode_rel_index_stack);
          SPVM_LIST_free(loop_first_goto_opcode_rel_index_stack);
          SPVM_LIST_free(last_goto_opcode_rel_index_stack);
          SPVM_LIST_free(break_goto_opcode_rel_index_stack);
          SPVM_LIST_free(next_goto_opcode_rel_index_stack);
          SPVM_LIST_free(push_eval_opcode_rel_index_stack);
          SPVM_LIST_free(if_die_catch_goto_opcode_rel_index_stack);
          SPVM_LIST_free(if_die_return_goto_opcode_rel_index_stack);
          SPVM_LIST_free(return_goto_opcode_rel_index_stack);
          SPVM_LIST_free(switch_info_stack);
          SPVM_LIST_free(op_block_stack);
          SPVM_LIST_free(next_block_base_stack);
          SPVM_LIST_free(last_block_base_stack);
          SPVM_LIST_free(break_block_base_stack);
          SPVM_LIST_free(mortal_stack);
          SPVM_LIST_free(mortal_top_stack);
          SPVM_LIST_free(object_op_var_tmp_stack);
        }
      }
    }
  }
  
#ifdef SPVM_DEBUG_DUMP
#include "spvm_dumper.h"
  printf("\n[OP codes]\n");
  SPVM_DUMPER_dump_classes_opcode_array(compiler, compiler->classes);
#endif

    

}
