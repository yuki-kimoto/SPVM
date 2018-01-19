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
#include "spvm_dynamic_array.h"
#include "spvm_sub.h"
#include "spvm_var.h"
#include "spvm_my.h"
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
#include "spvm_dumper.h"
#include "spvm_opcode.h"


void SPVM_OPCODE_BUILDER_push_inc_opcode(SPVM_COMPILER* compiler, SPVM_OPCODE_ARRAY* opcode_array, SPVM_OP* op_inc, int32_t value) {
  
  SPVM_VAR* var = op_inc->first->uv.var;
  SPVM_MY* my = var->op_my->uv.my;
  
  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_inc);
  if (type->code == SPVM_TYPE_C_CODE_BYTE) {
    SPVM_OPCODE opcode;
    memset(&opcode, 0, sizeof(SPVM_OPCODE));
    
    opcode.code = SPVM_OPCODE_C_CODE_INC_BYTE;
    opcode.operand0 = my->index;
    opcode.operand1 = value;
    
    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
  }
  else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
    SPVM_OPCODE opcode;
    memset(&opcode, 0, sizeof(SPVM_OPCODE));
    
    opcode.code = SPVM_OPCODE_C_CODE_INC_SHORT;
    opcode.operand0 = my->index;
    opcode.operand1 = value;
    
    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
  }
  else if (type->code == SPVM_TYPE_C_CODE_INT) {
    SPVM_OPCODE opcode;
    memset(&opcode, 0, sizeof(SPVM_OPCODE));
    
    opcode.code = SPVM_OPCODE_C_CODE_INC_INT;
    opcode.operand0 = my->index;
    opcode.operand1 = value;
    
    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
  }
  else if (type->code == SPVM_TYPE_C_CODE_LONG) {
    SPVM_OPCODE opcode;
    memset(&opcode, 0, sizeof(SPVM_OPCODE));
    
    opcode.code = SPVM_OPCODE_C_CODE_INC_LONG;
    opcode.operand0 = my->index;
    opcode.operand1 = value;
    
    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
  }
}

void SPVM_OPCODE_BUILDER_build_opcode_array(SPVM_COMPILER* compiler) {
  
  // Bytecode
  SPVM_OPCODE_ARRAY* opcode_array = compiler->opcode_array;
  
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
      
      sub->opcode_base = opcode_array->length;
      
      // Run OPs
      SPVM_OP* op_base = SPVM_OP_get_op_block_from_op_sub(compiler, op_sub);
      SPVM_OP* op_cur = op_base;
      _Bool finish = 0;
      
      // opcode index stack for if start
      SPVM_DYNAMIC_ARRAY* if_eq_or_if_ne_opcode_index_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
      
      // opcode index stack for if end
      SPVM_DYNAMIC_ARRAY* if_block_end_goto_opcode_index_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
      
      // opcode index stack for loop start
      SPVM_DYNAMIC_ARRAY* loop_start_goto_opcode_index_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
      
      // opcode index stack for last
      SPVM_DYNAMIC_ARRAY* last_goto_opcode_index_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
      
      // opcode index stack for next
      SPVM_DYNAMIC_ARRAY* next_goto_opcode_index_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
      
      // opcode index stack for eval start
      SPVM_DYNAMIC_ARRAY* push_eval_opcode_index_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);

      // Switch stack
      SPVM_DYNAMIC_ARRAY* switch_info_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
      
      // Initialize object lexical variable
      {
        int32_t my_index;
        
        for (my_index = sub->op_args->length; my_index < sub->op_mys->length; my_index++) {
          SPVM_OP* op_my = SPVM_DYNAMIC_ARRAY_fetch(sub->op_mys, my_index);
          SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_my);
          if (SPVM_TYPE_is_object(compiler, type)) {
            SPVM_OPCODE opcode;
            memset(&opcode, 0, sizeof(SPVM_OPCODE));
            opcode.code = SPVM_OPCODE_C_CODE_LOAD_UNDEF;
            int32_t index_out = op_my->uv.my->index;
            opcode.operand0 = index_out;
            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
          }
        }
      }
      
      while (op_cur) {
        // [START]Preorder traversal position
        
        switch (op_cur->code) {
          case SPVM_OP_C_CODE_BLOCK: {
            if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_LOOP) {
              SPVM_OPCODE opcode;
              memset(&opcode, 0, sizeof(SPVM_OPCODE));
              // Add goto
              opcode.code = SPVM_OPCODE_C_CODE_GOTO;
              SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
              
              int32_t* opcode_index_ptr = SPVM_COMPILER_ALLOCATOR_alloc_int(compiler, compiler->allocator);
              *opcode_index_ptr = opcode_array->length - 1;
              
              SPVM_DYNAMIC_ARRAY_push(loop_start_goto_opcode_index_stack, opcode_index_ptr);
            }
            else if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_EVAL) {
              SPVM_OPCODE opcode;
              memset(&opcode, 0, sizeof(SPVM_OPCODE));
              opcode.code = SPVM_OPCODE_C_CODE_PUSH_EVAL;
              SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
              
              int32_t* opcode_index_ptr = SPVM_COMPILER_ALLOCATOR_alloc_int(compiler, compiler->allocator);
              *opcode_index_ptr = opcode_array->length - 1;
              
              SPVM_DYNAMIC_ARRAY_push(push_eval_opcode_index_stack, opcode_index_ptr);
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
                SPVM_OPCODE opcode;
                memset(&opcode, 0, sizeof(SPVM_OPCODE));
                opcode.code = SPVM_OPCODE_C_CODE_CURRENT_LINE;
                opcode.operand0 = op_cur->line;
                
                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
              }
            }
            
            // [START]Postorder traversal position
            switch (op_cur->code) {
              case SPVM_OP_C_CODE_ASSIGN: {
                SPVM_OP* op_assign_to = op_cur->last;
                SPVM_OP* op_assign_from = op_cur->first;
                
                if (op_assign_to->code == SPVM_OP_C_CODE_VAR) {
                  SPVM_OP* op_var = op_assign_to;
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_var);

                  int32_t do_dec_ref_count = 0;
                  
                  // Do decrement reference count
                  // Variable type is object
                  if (SPVM_TYPE_is_object(compiler, type)) {
                    // Right value is variable
                    if (op_assign_from->code == SPVM_OP_C_CODE_VAR) {
                      int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                      int32_t index_in = SPVM_OP_get_my_index(compiler, op_assign_from);
                      // Left index is deferent from rithgt index
                      if (index_out != index_in) {
                        do_dec_ref_count = 1;
                      }
                    }
                    else {
                      do_dec_ref_count = 1;
                    }
                  }
                  
                  // Decrement refernece count
                  if (do_dec_ref_count) {
                    int32_t index_dec_ref_count = SPVM_OP_get_my_index(compiler, op_assign_to);
                    
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    opcode.code = SPVM_OPCODE_C_CODE_DEC_REF_COUNT;
                    opcode.operand0 = index_dec_ref_count;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  
                  if (0) {
                    
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_PRE_INC) {
                    
                    SPVM_OPCODE_BUILDER_push_inc_opcode(compiler, opcode_array, op_assign_from, 1);
                    
                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in = SPVM_OP_get_my_index(compiler, op_assign_from->first);
                    
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    opcode.code = SPVM_OPCODE_C_CODE_MOVE;
                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_POST_INC) {
                    

                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in = SPVM_OP_get_my_index(compiler, op_assign_from->first);

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    opcode.code = SPVM_OPCODE_C_CODE_MOVE;
                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                    SPVM_OPCODE_BUILDER_push_inc_opcode(compiler, opcode_array, op_assign_from, 1);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_PRE_DEC) {
                    
                    SPVM_OPCODE_BUILDER_push_inc_opcode(compiler, opcode_array, op_assign_from, -1);
                    
                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in = SPVM_OP_get_my_index(compiler, op_assign_from->first);

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    opcode.code = SPVM_OPCODE_C_CODE_MOVE;
                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_POST_DEC) {
                    

                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in = SPVM_OP_get_my_index(compiler, op_assign_from->first);

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    opcode.code = SPVM_OPCODE_C_CODE_MOVE;
                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                    SPVM_OPCODE_BUILDER_push_inc_opcode(compiler, opcode_array, op_assign_from, -1);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_CONCAT_STRING) {
                    
                    
                    SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_assign_from->first);
                    assert(first_type->code == SPVM_TYPE_C_CODE_STRING);
                    SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_assign_from->last);
                    
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    if (last_type->code == SPVM_TYPE_C_CODE_STRING) {
                      opcode.code = SPVM_OPCODE_C_CODE_CONCAT_STRING_STRING;
                    }
                    else if (last_type->code == SPVM_TYPE_C_CODE_BYTE) {
                      opcode.code = SPVM_OPCODE_C_CODE_CONCAT_STRING_BYTE;
                    }
                    else if (last_type->code == SPVM_TYPE_C_CODE_SHORT) {
                      opcode.code = SPVM_OPCODE_C_CODE_CONCAT_STRING_SHORT;
                    }
                    else if (last_type->code == SPVM_TYPE_C_CODE_INT) {
                      opcode.code = SPVM_OPCODE_C_CODE_CONCAT_STRING_INT;
                    }
                    else if (last_type->code == SPVM_TYPE_C_CODE_LONG) {
                      opcode.code = SPVM_OPCODE_C_CODE_CONCAT_STRING_LONG;
                    }
                    else if (last_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                      opcode.code = SPVM_OPCODE_C_CODE_CONCAT_STRING_FLOAT;
                    }
                    else if (last_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                      opcode.code = SPVM_OPCODE_C_CODE_CONCAT_STRING_DOUBLE;
                    }

                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_assign_from->first);
                    int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_assign_from->last);

                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in1;
                    opcode.operand2 = index_in2;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_UNDEF) {

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    opcode.code = SPVM_OPCODE_C_CODE_LOAD_UNDEF;
                    
                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    opcode.operand0 = index_out;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_CALL_SUB) {
                    
                    
                    SPVM_CALL_SUB* call_sub = op_assign_from->uv.call_sub;
                    const char* sub_name = call_sub->sub->abs_name;
                    
                    SPVM_OP* op_sub = SPVM_HASH_search(compiler->op_sub_symtable, sub_name, strlen(sub_name));
                    SPVM_SUB* sub = op_sub->uv.sub;

                    // Push args
                    SPVM_OP* op_args = op_assign_from->last;
                    SPVM_OP* op_arg = op_args->first;
                    while ((op_arg = SPVM_OP_sibling(compiler, op_arg))) {
                      SPVM_OPCODE opcode;
                      memset(&opcode, 0, sizeof(SPVM_OPCODE));
                      
                      opcode.code = SPVM_OPCODE_C_CODE_PUSH_ARG;
                      int32_t index_arg = SPVM_OP_get_my_index(compiler, op_arg);
                      
                      opcode.operand0 = index_arg;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    }

                    // Call subroutine
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    opcode.code = SPVM_OPCODE_C_CODE_CALL_SUB;

                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t id = sub->id;

                    opcode.operand0 = index_out;
                    opcode.operand1 = id;

                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    
                    if (compiler->debug) {
                      SPVM_OPCODE opcode;
                      memset(&opcode, 0, sizeof(SPVM_OPCODE));
                      opcode.code = SPVM_OPCODE_C_CODE_CURRENT_LINE;
                      opcode.operand0 = op_cur->line;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    }
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_ARRAY_LENGTH) {
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    opcode.code = SPVM_OPCODE_C_CODE_ARRAY_LENGTH;
                    
                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in = SPVM_OP_get_my_index(compiler, op_assign_from->first);
                    
                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in;

                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_CALL_FIELD) {
                    
                    // $VAR = $VAR_OBJECT->{NAME}
                    SPVM_OP* op_call_field = op_assign_from;
                    SPVM_OP* op_term_object = op_call_field->first;
                    
                    // Call field
                    SPVM_CALL_FIELD* call_field = op_call_field->uv.call_field;
                    SPVM_FIELD* field = call_field->field;
                    int32_t field_id = field->id;
                    
                    SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_call_field);
                    
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                      opcode.code = SPVM_OPCODE_C_CODE_GET_FIELD_BYTE;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                      opcode.code = SPVM_OPCODE_C_CODE_GET_FIELD_SHORT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_INT) {
                      opcode.code = SPVM_OPCODE_C_CODE_GET_FIELD_INT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                      opcode.code = SPVM_OPCODE_C_CODE_GET_FIELD_LONG;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                      opcode.code = SPVM_OPCODE_C_CODE_GET_FIELD_FLOAT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                      opcode.code = SPVM_OPCODE_C_CODE_GET_FIELD_DOUBLE;
                    }
                    else {
                      opcode.code = SPVM_OPCODE_C_CODE_GET_FIELD_OBJECT;
                    }

                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_term_object = SPVM_OP_get_my_index(compiler, op_term_object);

                    opcode.operand0 = index_out;
                    opcode.operand1 = index_term_object;
                    opcode.operand2 = field_id;

                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_ARRAY_ELEM) {
                    
                    // $VAR = $VAR_ARRAY->[$VAR_INDEX]
                    SPVM_OP* op_array_elem = op_assign_from;
                    SPVM_OP* op_term_array = op_array_elem->first;
                    SPVM_OP* op_term_index = op_array_elem->last;
                    
                    SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_array_elem);
                    
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                      opcode.code = SPVM_OPCODE_C_CODE_ARRAY_LOAD_BYTE;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                      opcode.code = SPVM_OPCODE_C_CODE_ARRAY_LOAD_SHORT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_INT) {
                      opcode.code = SPVM_OPCODE_C_CODE_ARRAY_LOAD_INT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                      opcode.code = SPVM_OPCODE_C_CODE_ARRAY_LOAD_LONG;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                      opcode.code = SPVM_OPCODE_C_CODE_ARRAY_LOAD_FLOAT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                      opcode.code = SPVM_OPCODE_C_CODE_ARRAY_LOAD_DOUBLE;
                    }
                    else {
                      opcode.code = SPVM_OPCODE_C_CODE_ARRAY_LOAD_OBJECT;
                    }

                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_term_array = SPVM_OP_get_my_index(compiler, op_term_array);
                    int32_t index_term_index = SPVM_OP_get_my_index(compiler, op_term_index);

                    opcode.operand0 = index_out;
                    opcode.operand1 = index_term_array;
                    opcode.operand2 = index_term_index;

                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_PACKAGE_VAR) {
                    SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_assign_from);

                    // VAR = PACKAGE_VAR
                    SPVM_OUR* our = op_assign_from->uv.package_var->op_our->uv.our;
                    
                    int32_t package_var_id = our->id;
                    
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    
                    if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                      opcode.code = SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_BYTE;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                      opcode.code = SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_SHORT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_INT) {
                      opcode.code = SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_INT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                      opcode.code = SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_LONG;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                      opcode.code = SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_FLOAT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                      opcode.code = SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_DOUBLE;
                    }
                    else {
                      opcode.code = SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_OBJECT;
                    }
                    
                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    
                    opcode.operand0 = index_out;
                    opcode.operand1 = package_var_id;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_EXCEPTION_VAR) {
                    // VAR = EXCEPTION_VAR
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    
                    opcode.code = SPVM_OPCODE_C_CODE_LOAD_EXCEPTION_VAR;

                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    
                    opcode.operand0 = index_out;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_ADD) {
                    
                    
                    
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    
                    if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                      opcode.code = SPVM_OPCODE_C_CODE_ADD_BYTE;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                      opcode.code = SPVM_OPCODE_C_CODE_ADD_SHORT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_INT) {
                      opcode.code = SPVM_OPCODE_C_CODE_ADD_INT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                      opcode.code = SPVM_OPCODE_C_CODE_ADD_LONG;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                      opcode.code = SPVM_OPCODE_C_CODE_ADD_FLOAT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                      opcode.code = SPVM_OPCODE_C_CODE_ADD_DOUBLE;
                    }

                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_assign_from->first);
                    int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_assign_from->last);
                    
                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in1;
                    opcode.operand2 = index_in2;

                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_SUBTRACT) {
                    
                    

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));

                    if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                      opcode.code = SPVM_OPCODE_C_CODE_SUBTRACT_BYTE;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                      opcode.code = SPVM_OPCODE_C_CODE_SUBTRACT_SHORT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_INT) {
                      opcode.code = SPVM_OPCODE_C_CODE_SUBTRACT_INT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                      opcode.code = SPVM_OPCODE_C_CODE_SUBTRACT_LONG;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                      opcode.code = SPVM_OPCODE_C_CODE_SUBTRACT_FLOAT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                      opcode.code = SPVM_OPCODE_C_CODE_SUBTRACT_DOUBLE;
                    }
                    
                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_assign_from->first);
                    int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_assign_from->last);
                    
                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in1;
                    opcode.operand2 = index_in2;

                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_MULTIPLY) {
                    
                    

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));

                    if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                      opcode.code = SPVM_OPCODE_C_CODE_MULTIPLY_BYTE;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                      opcode.code = SPVM_OPCODE_C_CODE_MULTIPLY_SHORT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_INT) {
                      opcode.code = SPVM_OPCODE_C_CODE_MULTIPLY_INT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                      opcode.code = SPVM_OPCODE_C_CODE_MULTIPLY_LONG;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                      opcode.code = SPVM_OPCODE_C_CODE_MULTIPLY_FLOAT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                      opcode.code = SPVM_OPCODE_C_CODE_MULTIPLY_DOUBLE;
                    }
                    
                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_assign_from->first);
                    int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_assign_from->last);
                    
                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in1;
                    opcode.operand2 = index_in2;

                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_DIVIDE) {
                    
                    

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));

                    if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                      opcode.code = SPVM_OPCODE_C_CODE_DIVIDE_BYTE;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                      opcode.code = SPVM_OPCODE_C_CODE_DIVIDE_SHORT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_INT) {
                      opcode.code = SPVM_OPCODE_C_CODE_DIVIDE_INT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                      opcode.code = SPVM_OPCODE_C_CODE_DIVIDE_LONG;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                      opcode.code = SPVM_OPCODE_C_CODE_DIVIDE_FLOAT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                      opcode.code = SPVM_OPCODE_C_CODE_DIVIDE_DOUBLE;
                    }
                    
                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_assign_from->first);
                    int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_assign_from->last);
                    
                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in1;
                    opcode.operand2 = index_in2;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_REMAINDER) {
                    
                    

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));

                    if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                      opcode.code = SPVM_OPCODE_C_CODE_REMAINDER_BYTE;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                      opcode.code = SPVM_OPCODE_C_CODE_REMAINDER_SHORT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_INT) {
                      opcode.code = SPVM_OPCODE_C_CODE_REMAINDER_INT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                      opcode.code = SPVM_OPCODE_C_CODE_REMAINDER_LONG;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                      opcode.code = SPVM_OPCODE_C_CODE_REMAINDER_FLOAT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                      opcode.code = SPVM_OPCODE_C_CODE_REMAINDER_DOUBLE;
                    }
                    
                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_assign_from->first);
                    int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_assign_from->last);
                    
                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in1;
                    opcode.operand2 = index_in2;

                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_LEFT_SHIFT) {

                    

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    
                    if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                      opcode.code = SPVM_OPCODE_C_CODE_LEFT_SHIFT_BYTE;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                      opcode.code = SPVM_OPCODE_C_CODE_LEFT_SHIFT_SHORT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_INT) {
                      opcode.code = SPVM_OPCODE_C_CODE_LEFT_SHIFT_INT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                      opcode.code = SPVM_OPCODE_C_CODE_LEFT_SHIFT_LONG;
                    }

                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_assign_from->first);
                    int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_assign_from->last);
                    
                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in1;
                    opcode.operand2 = index_in2;

                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_RIGHT_SHIFT) {

                    

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    
                    if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                      opcode.code = SPVM_OPCODE_C_CODE_RIGHT_SHIFT_BYTE;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                      opcode.code = SPVM_OPCODE_C_CODE_RIGHT_SHIFT_SHORT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_INT) {
                      opcode.code = SPVM_OPCODE_C_CODE_RIGHT_SHIFT_INT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                      opcode.code = SPVM_OPCODE_C_CODE_RIGHT_SHIFT_LONG;
                    }

                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_assign_from->first);
                    int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_assign_from->last);
                    
                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in1;
                    opcode.operand2 = index_in2;

                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_RIGHT_SHIFT_UNSIGNED) {

                    

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    
                    if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                      opcode.code = SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_BYTE;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                      opcode.code = SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_SHORT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_INT) {
                      opcode.code = SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_INT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                      opcode.code = SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_LONG;
                    }

                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_assign_from->first);
                    int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_assign_from->last);
                    
                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in1;
                    opcode.operand2 = index_in2;

                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_BIT_AND) {

                    

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    
                    if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                      opcode.code = SPVM_OPCODE_C_CODE_BIT_AND_BYTE;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                      opcode.code = SPVM_OPCODE_C_CODE_BIT_AND_SHORT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_INT) {
                      opcode.code = SPVM_OPCODE_C_CODE_BIT_AND_INT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                      opcode.code = SPVM_OPCODE_C_CODE_BIT_AND_LONG;
                    }
                    else {
                      assert(0);
                    }

                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_assign_from->first);
                    int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_assign_from->last);
                    
                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in1;
                    opcode.operand2 = index_in2;

                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_BIT_OR) {

                    

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    
                    if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                      opcode.code = SPVM_OPCODE_C_CODE_BIT_OR_BYTE;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                      opcode.code = SPVM_OPCODE_C_CODE_BIT_OR_SHORT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_INT) {
                      opcode.code = SPVM_OPCODE_C_CODE_BIT_OR_INT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                      opcode.code = SPVM_OPCODE_C_CODE_BIT_OR_LONG;
                    }
                    else {
                      assert(0);
                    }

                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_assign_from->first);
                    int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_assign_from->last);
                    
                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in1;
                    opcode.operand2 = index_in2;

                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_BIT_XOR) {

                    

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    
                    if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                      opcode.code = SPVM_OPCODE_C_CODE_BIT_XOR_BYTE;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                      opcode.code = SPVM_OPCODE_C_CODE_BIT_XOR_SHORT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_INT) {
                      opcode.code = SPVM_OPCODE_C_CODE_BIT_XOR_INT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                      opcode.code = SPVM_OPCODE_C_CODE_BIT_XOR_LONG;
                    }
                    else {
                      assert(0);
                    }

                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_assign_from->first);
                    int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_assign_from->last);
                    
                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in1;
                    opcode.operand2 = index_in2;

                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_COMPLEMENT) {

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));

                    if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                      opcode.code = SPVM_OPCODE_C_CODE_COMPLEMENT_BYTE;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                      opcode.code = SPVM_OPCODE_C_CODE_COMPLEMENT_SHORT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_INT) {
                      opcode.code = SPVM_OPCODE_C_CODE_COMPLEMENT_INT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                      opcode.code = SPVM_OPCODE_C_CODE_COMPLEMENT_LONG;
                    }
                    else {
                      assert(0);
                    }
                    
                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in = SPVM_OP_get_my_index(compiler, op_assign_from->first);
                    
                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_NEGATE) {

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                   
                    if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                      opcode.code = SPVM_OPCODE_C_CODE_NEGATE_BYTE;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                      opcode.code = SPVM_OPCODE_C_CODE_NEGATE_SHORT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_INT) {
                      opcode.code = SPVM_OPCODE_C_CODE_NEGATE_INT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                      opcode.code = SPVM_OPCODE_C_CODE_NEGATE_LONG;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                      opcode.code = SPVM_OPCODE_C_CODE_NEGATE_FLOAT;
                    }
                    else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                      opcode.code = SPVM_OPCODE_C_CODE_NEGATE_DOUBLE;
                    }
                    
                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in = SPVM_OP_get_my_index(compiler, op_assign_from->first);
                    
                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_CONSTANT) {
                    SPVM_CONSTANT* constant = op_assign_from->uv.constant;

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    
                    switch (type->code) {
                      case SPVM_TYPE_C_CODE_BYTE:
                        opcode.code = SPVM_OPCODE_C_CODE_LOAD_CONSTANT_BYTE;
                        break;
                      case SPVM_TYPE_C_CODE_SHORT:
                        opcode.code = SPVM_OPCODE_C_CODE_LOAD_CONSTANT_SHORT;
                        break;
                      case SPVM_TYPE_C_CODE_INT:
                        opcode.code = SPVM_OPCODE_C_CODE_LOAD_CONSTANT_INT;
                        break;
                      case SPVM_TYPE_C_CODE_LONG:
                        opcode.code = SPVM_OPCODE_C_CODE_LOAD_CONSTANT_LONG;
                        break;
                      case SPVM_TYPE_C_CODE_FLOAT:
                        opcode.code = SPVM_OPCODE_C_CODE_LOAD_CONSTANT_FLOAT;
                        break;
                      case SPVM_TYPE_C_CODE_DOUBLE:
                        opcode.code = SPVM_OPCODE_C_CODE_LOAD_CONSTANT_DOUBLE;
                        break;
                      default:
                        assert(0);
                    }
                    
                    assert(constant->id != -1);
                    
                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    
                    opcode.operand0 = index_out;
                    opcode.operand1 = constant->id;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_CONVERT) {
                    
                    SPVM_OP* op_dist_term = op_assign_to;
                    SPVM_OP* op_src_term = op_assign_from->first;
                    SPVM_OP* op_dist_type = op_assign_from->last;
                    
                    SPVM_TYPE* src_type = SPVM_OP_get_type(compiler, op_src_term);
                    SPVM_TYPE* dist_type = SPVM_OP_get_type(compiler, op_dist_type);

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    
                    if (src_type->code == SPVM_TYPE_C_CODE_BYTE) {
                      if (dist_type->code == SPVM_TYPE_C_CODE_BYTE) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_BYTE;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_SHORT) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_SHORT;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_INT) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_INT;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_LONG) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_LONG;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_FLOAT;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_DOUBLE;
                      }
                      else {
                        assert(0);
                      }
                    }
                    else if (src_type->code == SPVM_TYPE_C_CODE_SHORT) {
                      if (dist_type->code == SPVM_TYPE_C_CODE_BYTE) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_BYTE;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_SHORT) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_SHORT;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_INT) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_INT;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_LONG) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_LONG;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_FLOAT;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_DOUBLE;
                      }
                      else {
                        assert(0);
                      }
                    }
                    else if (src_type->code == SPVM_TYPE_C_CODE_INT) {
                      if (dist_type->code == SPVM_TYPE_C_CODE_BYTE) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_INT_TO_BYTE;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_SHORT) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_INT_TO_SHORT;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_INT) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_INT_TO_INT;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_LONG) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_INT_TO_LONG;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_INT_TO_FLOAT;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_INT_TO_DOUBLE;
                      }
                      else {
                        assert(0);
                      }
                    }
                    else if (src_type->code == SPVM_TYPE_C_CODE_LONG) {
                      if (dist_type->code == SPVM_TYPE_C_CODE_BYTE) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_BYTE;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_SHORT) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_SHORT;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_INT) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_INT;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_LONG) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_LONG;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_FLOAT;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_DOUBLE;
                      }
                      else {
                        assert(0);
                      }
                    }
                    else if (src_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                      if (dist_type->code == SPVM_TYPE_C_CODE_BYTE) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_BYTE;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_SHORT) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_SHORT;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_INT) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_INT;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_LONG) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_LONG;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_FLOAT;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_DOUBLE;
                      }
                      else {
                        assert(0);
                      }
                    }
                    else if (src_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                      if (dist_type->code == SPVM_TYPE_C_CODE_BYTE) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_BYTE;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_SHORT) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_SHORT;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_INT) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_INT;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_LONG) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_LONG;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_FLOAT) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_FLOAT;
                      }
                      else if (dist_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                        opcode.code = SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_DOUBLE;
                      }
                      else {
                        assert(0);
                      }
                    }
                    else {
                        assert(0);
                    }
                    
                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_dist_term);
                    int32_t index_in = SPVM_OP_get_my_index(compiler, op_src_term);
                    
                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_NEW) {
                    

                    if (op_assign_from->first->code == SPVM_OP_C_CODE_CONSTANT) {
                      SPVM_OPCODE opcode;
                      memset(&opcode, 0, sizeof(SPVM_OPCODE));
                      
                      opcode.code = SPVM_OPCODE_C_CODE_NEW_STRING;

                      int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                      SPVM_CONSTANT* constant = op_assign_from->first->uv.constant;

                      opcode.operand0 = index_out;
                      opcode.operand1 = constant->id;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    }
                    else if (op_assign_from->first->code == SPVM_OP_C_CODE_TYPE) {
                      
                      SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_assign_from->first);
                      
                      if (SPVM_TYPE_is_array(compiler, type)) {
                        /*
                          NEW op_assign_from
                             TYPE op_assign_from->first
                               ELEMENT_TYPE op_assign_from->first->first
                               INDEX op_assign_from->first->last
                        */
                        
                        switch (type->code) {
                          case SPVM_TYPE_C_CODE_BYTE_ARRAY: {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            opcode.code = SPVM_OPCODE_C_CODE_NEW_BYTE_ARRAY;

                            int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                            int32_t index_index = SPVM_OP_get_my_index(compiler, op_assign_from->first->last);

                            opcode.operand0 = index_out;
                            opcode.operand1 = index_index;

                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            
                            break;
                          }
                          case SPVM_TYPE_C_CODE_SHORT_ARRAY: {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            opcode.code = SPVM_OPCODE_C_CODE_NEW_SHORT_ARRAY;

                            int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                            int32_t index_index = SPVM_OP_get_my_index(compiler, op_assign_from->first->last);
                            
                            opcode.operand0 = index_out;
                            opcode.operand1 = index_index;

                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            
                            break;
                          }
                          case SPVM_TYPE_C_CODE_INT_ARRAY: {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));

                            opcode.code = SPVM_OPCODE_C_CODE_NEW_INT_ARRAY;

                            int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                            int32_t index_index = SPVM_OP_get_my_index(compiler, op_assign_from->first->last);

                            opcode.operand0 = index_out;
                            opcode.operand1 = index_index;

                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            
                            break;
                          }
                          case SPVM_TYPE_C_CODE_LONG_ARRAY: {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));

                            opcode.code = SPVM_OPCODE_C_CODE_NEW_LONG_ARRAY;

                            int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                            int32_t index_index = SPVM_OP_get_my_index(compiler, op_assign_from->first->last);

                            opcode.operand0 = index_out;
                            opcode.operand1 = index_index;

                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            
                            break;
                          }
                          case SPVM_TYPE_C_CODE_FLOAT_ARRAY: {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));

                            opcode.code = SPVM_OPCODE_C_CODE_NEW_FLOAT_ARRAY;

                            int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                            int32_t index_index = SPVM_OP_get_my_index(compiler, op_assign_from->first->last);

                            opcode.operand0 = index_out;
                            opcode.operand1 = index_index;

                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            
                            break;
                          }
                          case SPVM_TYPE_C_CODE_DOUBLE_ARRAY: {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));

                            opcode.code = SPVM_OPCODE_C_CODE_NEW_DOUBLE_ARRAY;
                            
                            int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                            int32_t index_index = SPVM_OP_get_my_index(compiler, op_assign_from->first->last);

                            opcode.operand0 = index_out;
                            opcode.operand1 = index_index;

                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                            break;
                          }
                          default: {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));

                            opcode.code = SPVM_OPCODE_C_CODE_NEW_OBJECT_ARRAY;

                            int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                            SPVM_TYPE* element_type = op_assign_from->first->first->uv.type;
                            int32_t index_index = SPVM_OP_get_my_index(compiler, op_assign_from->first->last);

                            opcode.operand0 = index_out;
                            opcode.operand1 = element_type->id;
                            opcode.operand2 = index_index;

                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                        }

                        if (op_assign_from->last->code == SPVM_OP_C_CODE_ARRAY_INIT) {
                          SPVM_OP* op_array_init = op_assign_from->last;
                          SPVM_OP* op_list_indexes = op_array_init->first;
                          SPVM_OP* op_list_elements = op_array_init->last;
                          
                          SPVM_OP* op_term_index = op_list_indexes->first;
                          SPVM_OP* op_term_element = op_list_elements->first;
                          
                          while ((op_term_index = SPVM_OP_sibling(compiler, op_term_index))) {
                            op_term_element = SPVM_OP_sibling(compiler, op_term_element);
                            
                            // $VAR_ARRAY->[$VAR_INDEX] = $VAR_TERM
                            
                            SPVM_OP* op_term_array = op_assign_to;
                            
                            SPVM_TYPE* type_element = SPVM_OP_get_type(compiler, op_term_element);

                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            
                            if (type_element->code == SPVM_TYPE_C_CODE_BYTE) {
                              opcode.code = SPVM_OPCODE_C_CODE_ARRAY_STORE_BYTE;
                            }
                            else if (type_element->code == SPVM_TYPE_C_CODE_SHORT) {
                              opcode.code = SPVM_OPCODE_C_CODE_ARRAY_STORE_SHORT;
                            }
                            else if (type_element->code == SPVM_TYPE_C_CODE_INT) {
                              opcode.code = SPVM_OPCODE_C_CODE_ARRAY_STORE_INT;
                            }
                            else if (type_element->code == SPVM_TYPE_C_CODE_LONG) {
                              opcode.code = SPVM_OPCODE_C_CODE_ARRAY_STORE_LONG;
                            }
                            else if (type_element->code == SPVM_TYPE_C_CODE_FLOAT) {
                              opcode.code = SPVM_OPCODE_C_CODE_ARRAY_STORE_FLOAT;
                            }
                            else if (type_element->code == SPVM_TYPE_C_CODE_DOUBLE) {
                              opcode.code = SPVM_OPCODE_C_CODE_ARRAY_STORE_DOUBLE;
                            }
                            else {
                              opcode.code = SPVM_OPCODE_C_CODE_ARRAY_STORE_OBJECT;
                            }
                            
                            int32_t index_term_array = SPVM_OP_get_my_index(compiler, op_term_array);
                            int32_t index_term_index = SPVM_OP_get_my_index(compiler, op_term_index);
                            int32_t index_in = SPVM_OP_get_my_index(compiler, op_term_element);
                            
                            opcode.operand0 = index_term_array;
                            opcode.operand1 = index_term_index;
                            opcode.operand2 = index_in;
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                        }
                      }
                      else {
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));

                        opcode.code = SPVM_OPCODE_C_CODE_NEW_OBJECT;
                        
                        int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                        int32_t type_id = op_assign_from->first->uv.type->id;
                        assert(type_id);
                        
                        opcode.operand0 = index_out;
                        opcode.operand1 = type_id;
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                    }
                    else {
                      assert(0);
                    }
                  }
                  else if (op_assign_from->code == SPVM_OP_C_CODE_VAR) {
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));

                    opcode.code = SPVM_OPCODE_C_CODE_MOVE;

                    int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                    int32_t index_in = SPVM_OP_get_my_index(compiler, op_assign_from);

                    opcode.operand0 = index_out;
                    opcode.operand1 = index_in;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else {
                    break;
                  }

                  // Do increment reference count
                  int32_t do_inc_ref_count = 0;
                  // Variable type is object
                  if (SPVM_TYPE_is_object(compiler, type)) {
                    // Right value is not undef
                    if (op_assign_from->code != SPVM_OP_C_CODE_UNDEF) {
                      // Right value is variable
                      if (op_assign_from->code == SPVM_OP_C_CODE_VAR) {
                        int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                        int32_t index_in = SPVM_OP_get_my_index(compiler, op_assign_from);
                        
                        // Right variable is different from left variable
                        if (index_out != index_in) {
                          do_inc_ref_count = 1;
                        }
                      }
                      // Right value is not variable
                      else {
                        do_inc_ref_count = 1;
                      }
                    }
                  }
                  
                  if (do_inc_ref_count) {
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    int32_t index_inc_ref_count = SPVM_OP_get_my_index(compiler, op_assign_to);
                    
                    opcode.code = SPVM_OPCODE_C_CODE_INC_REF_COUNT;
                    opcode.operand0 = index_inc_ref_count;
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                }
                else if (op_assign_to->code == SPVM_OP_C_CODE_PACKAGE_VAR) {
                  // PACKAGE_VAR = VAR
                  
                  SPVM_OP* op_package_var = op_assign_to;
                  
                  SPVM_PACKAGE_VAR* package_var = op_package_var->uv.package_var;

                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_package_var);

                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));

                  if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                    opcode.code = SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_BYTE;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                    opcode.code = SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_SHORT;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_INT) {
                    opcode.code = SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_INT;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                    opcode.code = SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_LONG;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    opcode.code = SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_FLOAT;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    opcode.code = SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_DOUBLE;
                  }
                  else {
                    opcode.code = SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_OBJECT;
                  }
                                    
                  int32_t package_var_id = package_var->op_our->uv.our->id;
                  int32_t index_in = SPVM_OP_get_my_index(compiler, op_assign_from);
                  
                  opcode.operand0 = package_var_id;
                  opcode.operand1 = index_in;
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                }
                else if (op_assign_to->code == SPVM_OP_C_CODE_EXCEPTION_VAR) {
                  // EXCEPTION_VAR = VAR
                  
                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));

                  opcode.code = SPVM_OPCODE_C_CODE_STORE_EXCEPTION_VAR;
                                    
                  int32_t index_in = SPVM_OP_get_my_index(compiler, op_assign_from);
                  
                  opcode.operand0 = index_in;
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                }
                else if (op_assign_to->code == SPVM_OP_C_CODE_ARRAY_ELEM) {
                  
                  // $VAR_ARRAY->[$VAR_INDEX] = $VAR_TERM
                  
                  SPVM_OP* op_array_elem = op_assign_to;
                  SPVM_OP* op_term_array = op_array_elem->first;
                  SPVM_OP* op_term_index = op_array_elem->last;
                  
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_array_elem);

                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));
                  
                  if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                    opcode.code = SPVM_OPCODE_C_CODE_ARRAY_STORE_BYTE;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                    opcode.code = SPVM_OPCODE_C_CODE_ARRAY_STORE_SHORT;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_INT) {
                    opcode.code = SPVM_OPCODE_C_CODE_ARRAY_STORE_INT;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                    opcode.code = SPVM_OPCODE_C_CODE_ARRAY_STORE_LONG;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    opcode.code = SPVM_OPCODE_C_CODE_ARRAY_STORE_FLOAT;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    opcode.code = SPVM_OPCODE_C_CODE_ARRAY_STORE_DOUBLE;
                  }
                  else {
                    opcode.code = SPVM_OPCODE_C_CODE_ARRAY_STORE_OBJECT;
                  }
                  
                  int32_t index_term_array = SPVM_OP_get_my_index(compiler, op_term_array);
                  int32_t index_term_index = SPVM_OP_get_my_index(compiler, op_term_index);
                  int32_t index_in = SPVM_OP_get_my_index(compiler, op_assign_from);
                  
                  opcode.operand0 = index_term_array;
                  opcode.operand1 = index_term_index;
                  opcode.operand2 = index_in;
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                }
                else if (op_assign_to->code == SPVM_OP_C_CODE_CALL_FIELD) {
                  
                  // $VAR_ARRAY->{NAME} = $VAR_TERM
                  
                  SPVM_OP* op_call_field = op_assign_to;
                  SPVM_OP* op_term_object = op_call_field->first;

                  // Call field
                  SPVM_CALL_FIELD* call_field = op_call_field->uv.call_field;
                  SPVM_FIELD* field = call_field->field;
                  int32_t field_id = field->id;

                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_call_field);

                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));
                  
                  if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                    opcode.code = SPVM_OPCODE_C_CODE_SET_FIELD_BYTE;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                    opcode.code = SPVM_OPCODE_C_CODE_SET_FIELD_SHORT;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_INT) {
                    opcode.code = SPVM_OPCODE_C_CODE_SET_FIELD_INT;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                    opcode.code = SPVM_OPCODE_C_CODE_SET_FIELD_LONG;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    opcode.code = SPVM_OPCODE_C_CODE_SET_FIELD_FLOAT;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    opcode.code = SPVM_OPCODE_C_CODE_SET_FIELD_DOUBLE;
                  }
                  else {
                    opcode.code = SPVM_OPCODE_C_CODE_SET_FIELD_OBJECT;
                  }
                  
                  int32_t index_term_object = SPVM_OP_get_my_index(compiler, op_term_object);
                  int32_t index_in = SPVM_OP_get_my_index(compiler, op_assign_from);
                  
                  opcode.operand0 = index_term_object;
                  opcode.operand1 = field_id;
                  opcode.operand2 = index_in;
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                }
                else {
                  assert(0);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_SWITCH_CONDITION: {
                
                SPVM_SWITCH_INFO* switch_info = op_cur->uv.switch_info;

                // tableswitch
                if (switch_info->code == SPVM_SWITCH_INFO_C_CODE_TABLE_SWITCH) {
                  // TABLE_SWITCH is no longer used
                  assert(0);
                }
                // lookupswitch
                else if (switch_info->code == SPVM_SWITCH_INFO_C_CODE_LOOKUP_SWITCH) {
                  SPVM_OPCODE opcode_switch_info;
                  memset(&opcode_switch_info, 0, sizeof(SPVM_OPCODE));

                  opcode_switch_info.code = SPVM_OPCODE_C_CODE_LOOKUP_SWITCH;

                  int32_t index_in = SPVM_OP_get_my_index(compiler, op_cur->first);
                  opcode_switch_info.operand0 = index_in;
                  
                  // Default
                  opcode_switch_info.operand1 = 0;
                  
                  // Case count
                  int32_t case_length = switch_info->op_cases->length;
                  opcode_switch_info.operand2 = case_length;

                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode_switch_info);
                  
                  // Switch opcode index
                  int32_t switch_opcode_index = opcode_array->length - 1;
                  switch_info->opcode_index = switch_opcode_index;
                  SPVM_DYNAMIC_ARRAY_push(switch_info_stack, switch_info);
                  
                  // Match-Offsets
                  {
                    int32_t i;
                    for (i = 0; i < case_length; i++) {
                      SPVM_OPCODE opcode_case;
                      memset(&opcode_case, 0, sizeof(SPVM_OPCODE));
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode_case);
                    }
                  }
                }
                
                break;
              }
              case SPVM_OP_C_CODE_SWITCH: {
                
                // Pop switch information
                SPVM_SWITCH_INFO* switch_info = SPVM_DYNAMIC_ARRAY_pop(switch_info_stack);
                int32_t switch_opcode_index = switch_info->opcode_index;
                int32_t default_opcode_index = switch_info->default_opcode_index;
                SPVM_DYNAMIC_ARRAY* case_opcode_indexes = switch_info->case_opcode_indexes;
                
                // tableswitch
                if (switch_info->code == SPVM_SWITCH_INFO_C_CODE_TABLE_SWITCH) {
                  // TABLE_SWITCH is no longer used
                  assert(0);
                }
                // lookupswitch
                else if (switch_info->code == SPVM_SWITCH_INFO_C_CODE_LOOKUP_SWITCH) {
                  // Default branch
                  if (!default_opcode_index) {
                    default_opcode_index = opcode_array->length;
                  }
                  (opcode_array->values + switch_opcode_index)->operand1 = default_opcode_index;
                  
                  int32_t case_length = (int32_t) switch_info->op_cases->length;
                  
                  SPVM_DYNAMIC_ARRAY* ordered_op_cases = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
                  {
                    int32_t i;
                    for (i = 0; i < case_length; i++) {
                      SPVM_OP* op_case = SPVM_DYNAMIC_ARRAY_fetch(switch_info->op_cases, i);
                      SPVM_DYNAMIC_ARRAY_push(ordered_op_cases, op_case);
                    }
                  }
                  SPVM_DYNAMIC_ARRAY* ordered_case_opcode_indexes = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
                  {
                    int32_t i;
                    for (i = 0; i < case_length; i++) {
                      int32_t* case_opcode_index_ptr = SPVM_DYNAMIC_ARRAY_fetch(case_opcode_indexes, i);
                      SPVM_DYNAMIC_ARRAY_push(ordered_case_opcode_indexes, case_opcode_index_ptr);
                    }
                  }
                  
                  // sort by asc order
                  {
                    int32_t i;
                    for (i = 0; i < case_length; i++) {
                      int32_t j;
                      {
                        for (j = i + 1; j < case_length; j++) {
                          SPVM_OP* op_case_i = SPVM_DYNAMIC_ARRAY_fetch(ordered_op_cases, i);
                          SPVM_OP* op_case_j = SPVM_DYNAMIC_ARRAY_fetch(ordered_op_cases, j);
                          int32_t match_i = op_case_i->first->uv.constant->value.int_value;
                          int32_t match_j = op_case_j->first->uv.constant->value.int_value;
                          
                          int32_t* case_opcode_index_i = SPVM_DYNAMIC_ARRAY_fetch(ordered_case_opcode_indexes, i);
                          int32_t* case_opcode_index_j = SPVM_DYNAMIC_ARRAY_fetch(ordered_case_opcode_indexes, j);
                          
                          if (match_i > match_j) {
                            SPVM_DYNAMIC_ARRAY_store(ordered_op_cases, i, op_case_j);
                            SPVM_DYNAMIC_ARRAY_store(ordered_op_cases, j, op_case_i);
                            
                            SPVM_DYNAMIC_ARRAY_store(ordered_case_opcode_indexes, i, case_opcode_index_j);
                            SPVM_DYNAMIC_ARRAY_store(ordered_case_opcode_indexes, j, case_opcode_index_i);
                          }
                        }
                      }
                    }
                  }
                  
                  {
                    int32_t i;
                    for (i = 0; i < case_length; i++) {
                      SPVM_OP* op_case = SPVM_DYNAMIC_ARRAY_fetch(ordered_op_cases, i);
                      SPVM_OP* op_constant = op_case->first;
                      int32_t match = op_constant->uv.constant->value.int_value;

                      int32_t* case_opcode_index_ptr = SPVM_DYNAMIC_ARRAY_fetch(ordered_case_opcode_indexes, i);
                      int32_t case_opcode_index = *case_opcode_index_ptr;
                      
                      SPVM_OPCODE* opcode_case = (opcode_array->values + switch_opcode_index + 1 + i);
                      
                      opcode_case->code = SPVM_OPCODE_C_CODE_CASE;
                      
                      // Match
                      opcode_case->operand0 = match;

                      // Branch
                      opcode_case->operand1 = case_opcode_index;
                    }
                  }
                }
                
                // Set last position
                while (last_goto_opcode_index_stack->length > 0) {
                  
                  int32_t* last_opcode_index_ptr = SPVM_DYNAMIC_ARRAY_pop(last_goto_opcode_index_stack);
                  int32_t last_opcode_index = *last_opcode_index_ptr;
                  
                  SPVM_OPCODE* opcode_goto = (opcode_array->values + last_opcode_index);
                  opcode_goto->operand0 = opcode_array->length;
                }
                
                break;
              }
              case SPVM_OP_C_CODE_CASE: {
                if (switch_info_stack->length > 0) {
                  SPVM_SWITCH_INFO* switch_info = SPVM_DYNAMIC_ARRAY_fetch(switch_info_stack, switch_info_stack->length - 1);
                  int32_t* opcode_index_ptr = SPVM_COMPILER_ALLOCATOR_alloc_int(compiler, compiler->allocator);
                  *opcode_index_ptr = opcode_array->length;
                  
                  SPVM_DYNAMIC_ARRAY_push(switch_info->case_opcode_indexes, opcode_index_ptr);
                }
                break;
              }
              case SPVM_OP_C_CODE_DEFAULT: {
                if (switch_info_stack->length > 0) {
                  SPVM_SWITCH_INFO* switch_info = SPVM_DYNAMIC_ARRAY_fetch(switch_info_stack, switch_info_stack->length - 1);
                  switch_info->default_opcode_index = opcode_array->length;
                }
                break;
              }
              case SPVM_OP_C_CODE_CALL_FIELD: {
                
                // Weaken field
                if (op_cur->flag &= SPVM_OP_C_FLAG_CALL_FIELD_WEAKEN) {
                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));

                  opcode.code = SPVM_OPCODE_C_CODE_WEAKEN_FIELD_OBJECT;
                  SPVM_FIELD* field = op_cur->uv.call_field->field;
                  int32_t field_id = field->id;
                  
                  SPVM_OP* op_term_object = op_cur->first;
                  int32_t index_term_object = SPVM_OP_get_my_index(compiler, op_term_object);
                    
                  opcode.operand0 = index_term_object;
                  opcode.operand1 = field_id;
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_CROAK: {
                
                // SET_CROAK_FLAG_TRUE
                {
                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));
                  
                  opcode.code = SPVM_OPCODE_C_CODE_SET_CROAK_FLAG_TRUE;
                  
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                }
                
                // CROAK
                {
                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));
                  
                  opcode.code = SPVM_OPCODE_C_CODE_CROAK;
                  
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_LAST: {
                SPVM_OPCODE opcode;
                memset(&opcode, 0, sizeof(SPVM_OPCODE));

                // Add goto
                opcode.code = SPVM_OPCODE_C_CODE_GOTO;
                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                
                int32_t* opcode_index_ptr = SPVM_COMPILER_ALLOCATOR_alloc_int(compiler, compiler->allocator);
                *opcode_index_ptr = opcode_array->length - 1;
                
                SPVM_DYNAMIC_ARRAY_push(last_goto_opcode_index_stack, opcode_index_ptr);
                
                break;
              }
              case SPVM_OP_C_CODE_NEXT: {
                SPVM_OPCODE opcode;
                memset(&opcode, 0, sizeof(SPVM_OPCODE));

                // Add goto
                opcode.code = SPVM_OPCODE_C_CODE_GOTO;
                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                
                int32_t* opcode_index_ptr = SPVM_COMPILER_ALLOCATOR_alloc_int(compiler, compiler->allocator);
                *opcode_index_ptr = opcode_array->length - 1;
                
                SPVM_DYNAMIC_ARRAY_push(next_goto_opcode_index_stack, opcode_index_ptr);
                
                break;
              }
              case SPVM_OP_C_CODE_BLOCK: {
                if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_IF) {
                  
                  {
                    // Prepare to jump to end of true block
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));

                    opcode.code = SPVM_OPCODE_C_CODE_GOTO;
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    
                    int32_t* opcode_index_ptr = SPVM_COMPILER_ALLOCATOR_alloc_int(compiler, compiler->allocator);
                    *opcode_index_ptr = opcode_array->length - 1;
                    SPVM_DYNAMIC_ARRAY_push(if_block_end_goto_opcode_index_stack, opcode_index_ptr);
                  }

                  // Set if jump opcode index
                  int32_t* opcode_index_ptr = SPVM_DYNAMIC_ARRAY_pop(if_eq_or_if_ne_opcode_index_stack);
                  int32_t opcode_index = *opcode_index_ptr;
                  
                  // Set jump
                  SPVM_OPCODE* opcode_goto = (opcode_array->values + opcode_index);
                  opcode_goto->operand0 = opcode_array->length;
                }
                else if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_ELSE) {
                  
                  assert(if_block_end_goto_opcode_index_stack->length > 0);
                  
                  int32_t* opcode_index_ptr = SPVM_DYNAMIC_ARRAY_pop(if_block_end_goto_opcode_index_stack);
                  int32_t opcode_index = *opcode_index_ptr;
                  
                  // Set jump
                  SPVM_OPCODE* opcode_goto = (opcode_array->values + opcode_index);
                  opcode_goto->operand0 = opcode_array->length;
                }
                else if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_LOOP) {
                  // Set next position
                  while (next_goto_opcode_index_stack->length > 0) {
                    
                    int32_t* next_opcode_index_ptr = SPVM_DYNAMIC_ARRAY_pop(next_goto_opcode_index_stack);
                    int32_t next_opcode_index = *next_opcode_index_ptr;
                    
                    SPVM_OPCODE* opcode_next = (opcode_array->values + next_opcode_index);
                    opcode_next->operand0 = opcode_array->length;
                  }
                }
                else if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_LOOP_NEXT_STEP) {
                  int32_t* loop_start_opcode_index_ptr = SPVM_DYNAMIC_ARRAY_fetch(loop_start_goto_opcode_index_stack, loop_start_goto_opcode_index_stack->length - 1);
                  int32_t loop_start_opcode_index = *loop_start_opcode_index_ptr;
                  
                  SPVM_OPCODE* opcode_loop_start = (opcode_array->values + loop_start_opcode_index);
                  opcode_loop_start->operand0 = opcode_array->length;
                }
                else if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_EVAL) {
                  // POP_EVAL
                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));
                  opcode.code = SPVM_OPCODE_C_CODE_POP_EVAL;
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  
                  // Set jump of eval block
                  int32_t* eval_start_opcode_index_ptr = SPVM_DYNAMIC_ARRAY_pop(push_eval_opcode_index_stack);
                  int32_t eval_start_opcode_index = *eval_start_opcode_index_ptr;
                  SPVM_OPCODE* opcode_jump = (opcode_array->values + eval_start_opcode_index);
                  opcode_jump->operand0 = opcode_array->length;
                }
                break;
              }
              case SPVM_OP_C_CODE_LOOP: {
                
                // Set last position
                while (last_goto_opcode_index_stack->length > 0) {
                  
                  int32_t* last_opcode_index_ptr = SPVM_DYNAMIC_ARRAY_pop(last_goto_opcode_index_stack);
                  int32_t last_opcode_index = *last_opcode_index_ptr;
                  
                  SPVM_OPCODE* opcode_last = (opcode_array->values + last_opcode_index);
                  opcode_last->operand0 = opcode_array->length;
                }
                
                break;
              }
              case SPVM_OP_C_CODE_CONDITION:
              case SPVM_OP_C_CODE_CONDITION_NOT:
              {
                int32_t opcode_index = opcode_array->length;

                SPVM_OPCODE opcode;
                memset(&opcode, 0, sizeof(SPVM_OPCODE));

                if (op_cur->code == SPVM_OP_C_CODE_CONDITION) {
                  opcode.code = SPVM_OPCODE_C_CODE_IF_EQ_ZERO;
                }
                else {
                  opcode.code = SPVM_OPCODE_C_CODE_IF_NE_ZERO;
                }
                
                if (op_cur->flag & SPVM_OP_C_FLAG_CONDITION_IF) {
                  int32_t* opcode_index_ptr = SPVM_COMPILER_ALLOCATOR_alloc_int(compiler, compiler->allocator);
                  *opcode_index_ptr = opcode_index;
                  
                  SPVM_DYNAMIC_ARRAY_push(if_eq_or_if_ne_opcode_index_stack, opcode_index_ptr);
                }
                else if (op_cur->flag & SPVM_OP_C_FLAG_CONDITION_LOOP) {
                  assert(loop_start_goto_opcode_index_stack->length > 0);
                  
                  int32_t* loop_start_opcode_index_ptr = SPVM_DYNAMIC_ARRAY_pop(loop_start_goto_opcode_index_stack);
                  int32_t loop_start_opcode_index = *loop_start_opcode_index_ptr;
                  
                  opcode.operand0 = loop_start_opcode_index + 1;
                }
                
                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                
                break;
              }
              case SPVM_OP_C_CODE_PRE_INC: {
                if (!op_cur->is_var_assign_from) {
                  SPVM_OPCODE_BUILDER_push_inc_opcode(compiler, opcode_array, op_cur, 1);
                }
                break;
              }
              case SPVM_OP_C_CODE_POST_INC: {
                if (!op_cur->is_var_assign_from) {
                  SPVM_OPCODE_BUILDER_push_inc_opcode(compiler, opcode_array, op_cur, 1);
                }
                break;
              }
              case SPVM_OP_C_CODE_PRE_DEC: {
                if (!op_cur->is_var_assign_from) {
                  SPVM_OPCODE_BUILDER_push_inc_opcode(compiler, opcode_array, op_cur, -1);
                }
                break;
              }
              case SPVM_OP_C_CODE_POST_DEC: {
                if (!op_cur->is_var_assign_from) {
                  SPVM_OPCODE_BUILDER_push_inc_opcode(compiler, opcode_array, op_cur, -1);
                }
                break;
              }
              
              case SPVM_OP_C_CODE_GT: {
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur->first);

                SPVM_OPCODE opcode;
                memset(&opcode, 0, sizeof(SPVM_OPCODE));
                
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  opcode.code = SPVM_OPCODE_C_CODE_GT_BYTE;
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  opcode.code = SPVM_OPCODE_C_CODE_GT_SHORT;
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  opcode.code = SPVM_OPCODE_C_CODE_GT_INT;
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  opcode.code = SPVM_OPCODE_C_CODE_GT_LONG;
                }
                else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  opcode.code = SPVM_OPCODE_C_CODE_GT_FLOAT;
                }
                else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  opcode.code = SPVM_OPCODE_C_CODE_GT_DOUBLE;
                }
                else {
                  assert(0);
                }
                int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_cur->first);
                int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_cur->last);
                
                opcode.operand0 = index_in1;
                opcode.operand1 = index_in2;
                
                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                
                break;
              }
              case SPVM_OP_C_CODE_GE: {

                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur->first);

                SPVM_OPCODE opcode;
                memset(&opcode, 0, sizeof(SPVM_OPCODE));
                
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  opcode.code = SPVM_OPCODE_C_CODE_GE_BYTE;
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  opcode.code = SPVM_OPCODE_C_CODE_GE_SHORT;
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  opcode.code = SPVM_OPCODE_C_CODE_GE_INT;
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  opcode.code = SPVM_OPCODE_C_CODE_GE_LONG;
                }
                else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  opcode.code = SPVM_OPCODE_C_CODE_GE_FLOAT;
                }
                else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  opcode.code = SPVM_OPCODE_C_CODE_GE_DOUBLE;
                }
                else {
                  assert(0);
                }
                int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_cur->first);
                int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_cur->last);
                
                opcode.operand0 = index_in1;
                opcode.operand1 = index_in2;
                
                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                break;
              }
              case  SPVM_OP_C_CODE_LT: {
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur->first);
                
                SPVM_OPCODE opcode;
                memset(&opcode, 0, sizeof(SPVM_OPCODE));

                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  opcode.code = SPVM_OPCODE_C_CODE_LT_BYTE;
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  opcode.code = SPVM_OPCODE_C_CODE_LT_SHORT;
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  opcode.code = SPVM_OPCODE_C_CODE_LT_INT;
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  opcode.code = SPVM_OPCODE_C_CODE_LT_LONG;
                }
                else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  opcode.code = SPVM_OPCODE_C_CODE_LT_FLOAT;
                }
                else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  opcode.code = SPVM_OPCODE_C_CODE_LT_DOUBLE;
                }
                else {
                  assert(0);
                }
                int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_cur->first);
                int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_cur->last);
                
                opcode.operand0 = index_in1;
                opcode.operand1 = index_in2;
                
                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                
                break;
              }
              case SPVM_OP_C_CODE_LE: {

                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur->first);

                SPVM_OPCODE opcode;
                memset(&opcode, 0, sizeof(SPVM_OPCODE));
                
                if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                  opcode.code = SPVM_OPCODE_C_CODE_LE_BYTE;
                }
                else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                  opcode.code = SPVM_OPCODE_C_CODE_LE_SHORT;
                }
                else if (type->code == SPVM_TYPE_C_CODE_INT) {
                  opcode.code = SPVM_OPCODE_C_CODE_LE_INT;
                }
                else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                  opcode.code = SPVM_OPCODE_C_CODE_LE_LONG;
                }
                else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                  opcode.code = SPVM_OPCODE_C_CODE_LE_FLOAT;
                }
                else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                  opcode.code = SPVM_OPCODE_C_CODE_LE_DOUBLE;
                }
                else {
                  assert(0);
                }
                int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_cur->first);
                int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_cur->last);
                
                opcode.operand0 = index_in1;
                opcode.operand1 = index_in2;

                SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                
                break;
              }
              case  SPVM_OP_C_CODE_EQ: {
                if (op_cur->first->code == SPVM_OP_C_CODE_UNDEF || op_cur->last->code == SPVM_OP_C_CODE_UNDEF) {
                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));

                  opcode.code = SPVM_OPCODE_C_CODE_IS_UNDEF;
                  if (op_cur->first->code == SPVM_OP_C_CODE_UNDEF) {
                    int32_t index_in = SPVM_OP_get_my_index(compiler, op_cur->last);
                    
                    opcode.operand0 = index_in;
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  else {
                    int32_t index_in = SPVM_OP_get_my_index(compiler, op_cur->first);
                    
                    opcode.operand0 = index_in;
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                }
                else {
                  
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur->first);
                  
                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));

                  if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                    opcode.code = SPVM_OPCODE_C_CODE_EQ_BYTE;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                    opcode.code = SPVM_OPCODE_C_CODE_EQ_SHORT;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_INT) {
                    opcode.code = SPVM_OPCODE_C_CODE_EQ_INT;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                    opcode.code = SPVM_OPCODE_C_CODE_EQ_LONG;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    opcode.code = SPVM_OPCODE_C_CODE_EQ_FLOAT;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    opcode.code = SPVM_OPCODE_C_CODE_EQ_DOUBLE;
                  }
                  else {
                    opcode.code = SPVM_OPCODE_C_CODE_EQ_OBJECT;
                  }
                  int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_cur->first);
                  int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_cur->last);
                  
                  opcode.operand0 = index_in1;
                  opcode.operand1 = index_in2;
                  
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                }
                break;
              }
              case  SPVM_OP_C_CODE_NE: {
                
                if (op_cur->first->code == SPVM_OP_C_CODE_UNDEF || op_cur->last->code == SPVM_OP_C_CODE_UNDEF) {
                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));

                  opcode.code = SPVM_OPCODE_C_CODE_IS_NOT_UNDEF;
                  if (op_cur->first->code == SPVM_OP_C_CODE_UNDEF) {
                    int32_t index_in = SPVM_OP_get_my_index(compiler, op_cur->last);
                    opcode.operand0 = index_in;
                  }
                  else {
                    int32_t index_in = SPVM_OP_get_my_index(compiler, op_cur->first);
                    opcode.operand0 = index_in;
                  }
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                }
                else {
                  
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur->first);

                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));
                  
                  if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                    opcode.code = SPVM_OPCODE_C_CODE_NE_BYTE;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                    opcode.code = SPVM_OPCODE_C_CODE_NE_SHORT;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_INT) {
                    opcode.code = SPVM_OPCODE_C_CODE_NE_INT;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                    opcode.code = SPVM_OPCODE_C_CODE_NE_LONG;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    opcode.code = SPVM_OPCODE_C_CODE_NE_FLOAT;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    opcode.code = SPVM_OPCODE_C_CODE_NE_DOUBLE;
                  }
                  else {
                    opcode.code = SPVM_OPCODE_C_CODE_NE_OBJECT;
                  }
                  int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_cur->first);
                  int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_cur->last);
                  
                  opcode.operand0 = index_in1;
                  opcode.operand1 = index_in2;

                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                }
                break;
              }
              case  SPVM_OP_C_CODE_BOOL: {
                SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur->first);
                
                if (op_cur->first->code != SPVM_OP_C_CODE_IF) {

                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));
                  
                  if (type->code == SPVM_TYPE_C_CODE_BYTE) {
                    opcode.code = SPVM_OPCODE_C_CODE_BOOL_BYTE;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_SHORT) {
                    opcode.code = SPVM_OPCODE_C_CODE_BOOL_SHORT;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_INT) {
                    opcode.code = SPVM_OPCODE_C_CODE_BOOL_INT;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_LONG) {
                    opcode.code = SPVM_OPCODE_C_CODE_BOOL_LONG;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_FLOAT) {
                    opcode.code = SPVM_OPCODE_C_CODE_BOOL_FLOAT;
                  }
                  else if (type->code == SPVM_TYPE_C_CODE_DOUBLE) {
                    opcode.code = SPVM_OPCODE_C_CODE_BOOL_DOUBLE;
                  }
                  else {
                    opcode.code = SPVM_OPCODE_C_CODE_BOOL_OBJECT;
                  }

                  int32_t index_in = SPVM_OP_get_my_index(compiler, op_cur->first);
                  
                  opcode.operand0 = index_in;

                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                }
                
                break;
              }
              case SPVM_OP_C_CODE_CALL_SUB: {
                SPVM_CALL_SUB* call_sub = op_cur->uv.call_sub;
                const char* sub_name = call_sub->sub->abs_name;
                
                SPVM_OP* op_sub = SPVM_HASH_search(compiler->op_sub_symtable, sub_name, strlen(sub_name));
                SPVM_SUB* sub = op_sub->uv.sub;
                
                if (sub->op_return_type->uv.type->code == SPVM_TYPE_C_CODE_VOID) {
                  // Push args
                  SPVM_OP* op_args = op_cur->last;
                  SPVM_OP* op_arg = op_args->first;
                  while ((op_arg = SPVM_OP_sibling(compiler, op_arg))) {
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));

                    opcode.code = SPVM_OPCODE_C_CODE_PUSH_ARG;

                    int32_t index_arg = SPVM_OP_get_my_index(compiler, op_arg);
                    opcode.operand0 = index_arg;
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  }
                  
                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));

                  // Call subroutine
                  opcode.code = SPVM_OPCODE_C_CODE_CALL_SUB;
                  
                  int32_t id = sub->id;
                  opcode.operand1 = id;

                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  
                  if (compiler->debug) {
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    opcode.code = SPVM_OPCODE_C_CODE_CURRENT_LINE;
                    opcode.operand0 = op_cur->line;
                  }
                }
                
                break;
              }
              case SPVM_OP_C_CODE_RETURN: {
                SPVM_OP* op_return_type = sub->op_return_type;
                
                SPVM_TYPE* return_type = op_return_type->uv.type;
                if (return_type->code == SPVM_TYPE_C_CODE_VOID) {
                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));
                  opcode.code = SPVM_OPCODE_C_CODE_RETURN;
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                }
                else {
                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));
                  opcode.code = SPVM_OPCODE_C_CODE_RETURN;
                  
                  int32_t index_in = SPVM_OP_get_my_index(compiler, op_cur->first);
                  
                  opcode.operand0 = index_in;

                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
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
      sub->opcode_length = opcode_array->length - sub->opcode_base;
      
      // Set opcode base to sub
      SPVM_CONSTANT_POOL_SUB constant_pool_sub;
      memcpy(&constant_pool_sub, &compiler->constant_pool->values[sub->id], sizeof(SPVM_CONSTANT_POOL_SUB));
      constant_pool_sub.opcode_base = sub->opcode_base;
      constant_pool_sub.opcode_length = sub->opcode_length;
      memcpy(&compiler->constant_pool->values[sub->id], &constant_pool_sub, sizeof(SPVM_CONSTANT_POOL_SUB));
      
    }
  }
  
  // Set label information
  {
    int32_t opcode_index;
    SPVM_OPCODE* opcodes = opcode_array->values;
    for (opcode_index = 0; opcode_index < opcode_array->length; opcode_index++) {
      
      if (opcodes[opcode_index].code == SPVM_OPCODE_C_CODE_GOTO) {
        int32_t branch_opcode_index = opcodes[opcode_index].operand0;
        opcodes[branch_opcode_index].has_label = 1;
      }
      else if (opcodes[opcode_index].code == SPVM_OPCODE_C_CODE_IF_EQ_ZERO || opcodes[opcode_index].code == SPVM_OPCODE_C_CODE_IF_NE_ZERO) {
        int32_t branch_opcode_index = opcodes[opcode_index].operand0;
        opcodes[branch_opcode_index].has_label = 1;
      }
      else if (opcodes[opcode_index].code == SPVM_OPCODE_C_CODE_PUSH_EVAL) {
        int32_t branch_opcode_index = opcodes[opcode_index].operand0;
        opcodes[branch_opcode_index].has_label = 1;
      }
      else if (opcodes[opcode_index].code == SPVM_OPCODE_C_CODE_LOOKUP_SWITCH) {
        // Default branch
        int32_t branch_opcode_index = opcodes[opcode_index].operand1;
        opcodes[branch_opcode_index].has_label = 1;
      }
      else if (opcodes[opcode_index].code == SPVM_OPCODE_C_CODE_CASE) {
        // Branch
        int32_t branch_opcode_index = opcodes[opcode_index].operand1;
        opcodes[branch_opcode_index].has_label = 1;
      }
    }
  }
}
