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
#include "spvm_sub.h"
#include "spvm_var.h"
#include "spvm_my.h"
#include "spvm_compiler_allocator.h"
#include "spvm_package.h"
#include "spvm_field_access.h"
#include "spvm_call_sub.h"
#include "spvm_hash.h"
#include "spvm_field.h"
#include "spvm_switch_info.h"
#include "spvm_type.h"
#include "spvm_limit.h"
#include "spvm_object.h"
#include "spvm_package_var.h"
#include "spvm_package_var_access.h"
#include "spvm_dumper.h"
#include "spvm_opcode.h"
#include "spvm_block.h"
#include "spvm_basic_type.h"
#include "spvm_yacc_util.h"
#include "spvm_case_info.h"
#include "spvm_array_field_access.h"

void SPVM_OPCODE_BUILDER_push_if_croak(
  SPVM_COMPILER* compiler,
  SPVM_OPCODE_ARRAY* opcode_array,
  SPVM_LIST* push_eval_opcode_rel_index_stack,
  SPVM_LIST* if_croak_catch_goto_opcode_rel_index_stack,
  SPVM_LIST* if_croak_return_goto_opcode_rel_index_stack,
  SPVM_OP* op_sub,
  int32_t line
)
{
  SPVM_SUB* sub = op_sub->uv.sub;
  int32_t sub_opcode_base = sub->opcode_base;
  
  if (push_eval_opcode_rel_index_stack->length > 0) {
    SPVM_OPCODE opcode;
    memset(&opcode, 0, sizeof(SPVM_OPCODE));
    opcode.id = SPVM_OPCODE_C_ID_IF_CROAK_CATCH;
    opcode.operand1 = sub->rel_id;
    int32_t rel_line = line - op_sub->line;
    opcode.operand2 = rel_line;
    
    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
    
    int32_t if_croak_catch_opcode_rel_index = opcode_array->length - 1 - sub_opcode_base;
    
    SPVM_LIST_push(if_croak_catch_goto_opcode_rel_index_stack, (void*)(intptr_t)if_croak_catch_opcode_rel_index);
  }
  else {
    SPVM_OPCODE opcode;
    memset(&opcode, 0, sizeof(SPVM_OPCODE));
    opcode.id = SPVM_OPCODE_C_ID_IF_CROAK_RETURN;
    opcode.operand1 = sub->rel_id;
    int32_t rel_line = line - op_sub->line;
    opcode.operand2 = rel_line;
    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

    int32_t if_croak_return_opcode_rel_index = opcode_array->length - 1 - sub_opcode_base;
    
    SPVM_LIST_push(if_croak_return_goto_opcode_rel_index_stack, (void*)(intptr_t)(if_croak_return_opcode_rel_index));
  }
}

void SPVM_OPCODE_BUILDER_build_opcode_array(SPVM_COMPILER* compiler) {
  
  // Operation code
  SPVM_OPCODE_ARRAY* opcode_array = compiler->opcode_array;
  
  {
    int32_t package_index;
    for (package_index = 0; package_index < compiler->op_packages->length; package_index++) {
      SPVM_OP* op_package = SPVM_LIST_fetch(compiler->op_packages, package_index);
      SPVM_PACKAGE* package = op_package->uv.package;
      SPVM_LIST* op_subs = package->op_subs;
      {
        int32_t sub_index;
        for (sub_index = 0; sub_index < op_subs->length; sub_index++) {
          // opcode index stack for if start
          SPVM_LIST* if_eq_or_if_ne_goto_opcode_rel_index_stack = SPVM_LIST_new(0);
          
          // opcode index stack for if end
          SPVM_LIST* if_block_end_goto_opcode_rel_index_stack = SPVM_LIST_new(0);
          
          // opcode index stack for loop start
          SPVM_LIST* loop_first_goto_opcode_rel_index_stack = SPVM_LIST_new(0);
          
          // opcode index stack for last
          SPVM_LIST* last_goto_opcode_rel_index_stack = SPVM_LIST_new(0);
          
          // opcode index stack for next
          SPVM_LIST* next_goto_opcode_rel_index_stack = SPVM_LIST_new(0);
          
          // opcode index stack for eval start
          SPVM_LIST* push_eval_opcode_rel_index_stack = SPVM_LIST_new(0);
          
          // IF_CROAK_CATCH opcode index stack
          SPVM_LIST* if_croak_catch_goto_opcode_rel_index_stack = SPVM_LIST_new(0);

          // IF_CROAK_RETURN opcode index stack
          SPVM_LIST* if_croak_return_goto_opcode_rel_index_stack = SPVM_LIST_new(0);

          // RETURN goto opcode index stack
          SPVM_LIST* return_goto_opcode_rel_index_stack = SPVM_LIST_new(0);
          
          // Switch stack
          SPVM_LIST* switch_info_stack = SPVM_LIST_new(0);
          
          // Block stack
          SPVM_LIST* op_block_stack = SPVM_LIST_new(0);
          
          // Mortal variable stack
          SPVM_LIST* mortal_stack = SPVM_LIST_new(0);
          
          // Mortal variable base stack
          SPVM_LIST* mortal_top_stack = SPVM_LIST_new(0);

          SPVM_OP* op_sub = SPVM_LIST_fetch(op_subs, sub_index);
          SPVM_SUB* sub = op_sub->uv.sub;
          
          // Check sub information
          assert(sub->id > -1);
          assert(sub->op_name);
          assert(sub->op_return_type);
          assert(sub->abs_name);
          assert(sub->file_name);
          
          if (sub->have_native_desc) {
            continue;
          }
          
          int32_t sub_opcode_base = opcode_array->length;
          
          sub->opcode_base = sub_opcode_base;
          
          // Run OPs
          SPVM_OP* op_base = SPVM_OP_get_op_block_from_op_sub(compiler, op_sub);
          SPVM_OP* op_cur = op_base;
          _Bool finish = 0;
          
          int32_t mortal_stack_max = 0;
          
          while (op_cur) {
            int32_t opcode_length = opcode_array->length - sub->opcode_base;
            if (opcode_length >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
              SPVM_yyerror_format(compiler, "Too many opcodes", op_cur->file, op_cur->line);
            }
            
            // [START]Preorder traversal position
            switch (op_cur->id) {
              case SPVM_OP_C_ID_BLOCK: { // Preorder
                
                // Push block
                SPVM_LIST_push(op_block_stack, op_cur);
                
                if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_LOOP_STATEMENTS) {
                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));
                  // Add goto
                  opcode.id = SPVM_OPCODE_C_ID_GOTO;
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                  
                  int32_t opcode_rel_index = opcode_array->length - 1 - sub_opcode_base;
                  
                  SPVM_LIST_push(loop_first_goto_opcode_rel_index_stack, (void*)(intptr_t)opcode_rel_index);
                }
                else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_EVAL) {
                  int32_t opcode_rel_index = opcode_array->length - sub_opcode_base;
                  
                  SPVM_LIST_push(push_eval_opcode_rel_index_stack, (void*)(intptr_t)opcode_rel_index);

                  // Set exception var to undef in eval block start
                  SPVM_OPCODE opcode;
                  memset(&opcode, 0, sizeof(SPVM_OPCODE));
                  opcode.id = SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR_UNDEF;
                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                }
                
                int32_t mortal_top = mortal_stack->length;
                SPVM_LIST_push(mortal_top_stack, (void*)(intptr_t)mortal_top);
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
                  case SPVM_OP_C_ID_ASSIGN: {
                    SPVM_OP* op_assign_to = op_cur->last;
                    SPVM_OP* op_assign_from = op_cur->first;
                    
                    if (op_assign_from->id == SPVM_OP_C_ID_SEQUENCE) {
                      op_assign_from = op_assign_from->last;
                    }
                    
                    if (op_assign_to->id == SPVM_OP_C_ID_VAR) {
                      SPVM_TYPE* type_to = SPVM_OP_get_type(compiler, op_assign_to);
                      
                      // Skip if same variable assignment
                      if (op_assign_from->id == SPVM_OP_C_ID_VAR) {
                        int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_from);
                        if (var_id_in == var_id_out) {
                          break;
                        }
                      }

                      if (0) {
                        
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_CONCAT) {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_assign_from->first);
                        
                        assert(first_type->dimension == 1 && first_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE);
                        
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        opcode.id = SPVM_OPCODE_C_ID_CONCAT;
                        
                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_assign_from->first);
                        int32_t var_id_in2 = SPVM_OP_get_my_var_id(compiler, op_assign_from->last);

                        opcode.operand0 = var_id_out;
                        opcode.operand1 = var_id_in1;
                        opcode.operand2 = var_id_in2;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                        SPVM_OPCODE_BUILDER_push_if_croak(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_croak_catch_goto_opcode_rel_index_stack, if_croak_return_goto_opcode_rel_index_stack, op_sub, op_cur->line);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_UNDEF) {

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        opcode.id = SPVM_OPCODE_C_ID_MOVE_UNDEF;
                        
                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        opcode.operand0 = var_id_out;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_CALL_SUB) {
                        
                        SPVM_CALL_SUB* call_sub = op_assign_from->uv.call_sub;
                        const char* call_sub_abs_name = call_sub->sub->abs_name;
                        
                        SPVM_OP* op_sub_call_sub = SPVM_HASH_fetch(compiler->op_sub_symtable, call_sub_abs_name, strlen(call_sub_abs_name));
                        SPVM_SUB* sub_call_sub = op_sub_call_sub->uv.sub;
                        
                        int32_t first_arg_var_id = -1;
                        SPVM_OP* op_term_args = op_assign_from->last;
                        SPVM_OP* op_term_arg = op_term_args->first;

                        SPVM_LIST* op_args = sub_call_sub->op_args;
                        {
                          int32_t arg_index;
                          for (arg_index = 0; arg_index < sub_call_sub->op_args->length; arg_index++) {
                            SPVM_OP* op_arg = SPVM_LIST_fetch(op_args, arg_index);
                            SPVM_MY* my_arg = op_arg->uv.my;
                            
                            // Argument type
                            SPVM_TYPE* arg_type = SPVM_OP_get_type(compiler, op_arg);

                            // Term argment type
                            op_term_arg = SPVM_OP_sibling(compiler, op_term_arg);
                            SPVM_TYPE* term_arg_type = SPVM_OP_get_type(compiler, op_term_arg);
                            
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));
                            
                            if (SPVM_TYPE_is_undef_type(compiler, term_arg_type)) {
                              assert(!sub_call_sub->op_package->uv.package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE);
                              opcode.id = SPVM_OPCODE_C_ID_PUSH_ARG_UNDEF;
                            }
                            else {
                              opcode.id = SPVM_OPCODE_C_ID_PUSH_ARG;

                              // Term of argument
                              int32_t var_id_arg = SPVM_OP_get_my_var_id(compiler, op_term_arg);
                              
                              opcode.operand0 = var_id_arg;
                              
                              if (arg_index == 0) {
                                first_arg_var_id = var_id_arg;
                              }
                            }
                            opcode.operand1 = SPVM_TYPE_get_width(compiler, arg_type);
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            
                          }
                        }

                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);

                        // Call subroutine
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        opcode.operand0 = var_id_out;

                        if (sub_call_sub->op_package->uv.package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE) {
                          opcode.id = SPVM_OPCODE_C_ID_CALL_INTERFACE_METHOD;
                          opcode.operand1 = call_sub->sub_rel_id;
                          opcode.operand2 = first_arg_var_id;
                        }
                        else {
                          opcode.id = SPVM_OPCODE_C_ID_CALL_SUB;
                          opcode.operand1 = call_sub->sub_rel_id;
                        }

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                        SPVM_OPCODE_BUILDER_push_if_croak(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_croak_catch_goto_opcode_rel_index_stack, if_croak_return_goto_opcode_rel_index_stack, op_sub, op_cur->line);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_ARRAY_LENGTH) {
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        opcode.id = SPVM_OPCODE_C_ID_ARRAY_LENGTH;
                        
                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_assign_from->first);
                        
                        opcode.operand0 = var_id_out;
                        opcode.operand1 = var_id_in;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                        SPVM_OPCODE_BUILDER_push_if_croak(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_croak_catch_goto_opcode_rel_index_stack, if_croak_return_goto_opcode_rel_index_stack, op_sub, op_cur->line);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_ARRAY_FIELD_ACCESS) {
                        
                        // $VAR = $VAR_OBJECT->[INDEX]{NAME}
                        SPVM_OP* op_array_field_access = op_assign_from;
                        SPVM_OP* op_term_object = op_array_field_access->first;
                        SPVM_OP* op_term_index = op_array_field_access->last;
                        
                        // Call field
                        SPVM_ARRAY_FIELD_ACCESS* array_field_access = op_array_field_access->uv.array_field_access;
                        SPVM_FIELD* field = array_field_access->field;
                        
                        // Array type
                        SPVM_TYPE* array_type = SPVM_OP_get_type(compiler, op_array_field_access->first);
                        SPVM_BASIC_TYPE* array_basic_type = array_type->basic_type;
                        
                        // Element type
                        SPVM_TYPE* element_type = SPVM_OP_get_type(compiler, op_array_field_access);
                        SPVM_BASIC_TYPE* element_basic_type = element_type->basic_type;

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        switch (element_type->basic_type->id) {
                          case SPVM_BASIC_TYPE_C_ID_BYTE:
                            opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_FETCH_BYTE;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_SHORT:
                            opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_FETCH_SHORT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_INT:
                            opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_FETCH_INT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_LONG:
                            opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_FETCH_LONG;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_FLOAT:
                            opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_FETCH_FLOAT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                            opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_FETCH_DOUBLE;
                            break;
                          default:
                            assert(0);
                        }
                        
                        // Field absolute name symbol
                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        int32_t index_term_object = SPVM_OP_get_my_var_id(compiler, op_term_object);
                        int32_t index_term_index = SPVM_OP_get_my_var_id(compiler, op_term_index);
                        
                        int32_t unit = array_basic_type->op_package->uv.package->op_fields->length;
                        int32_t offset = field->index;

                        opcode.operand0 = var_id_out;
                        opcode.operand1 = index_term_object;
                        opcode.operand2 = index_term_index;
                        opcode.operand3 = (offset << 4) + unit;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                        SPVM_OPCODE_BUILDER_push_if_croak(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_croak_catch_goto_opcode_rel_index_stack, if_croak_return_goto_opcode_rel_index_stack, op_sub, op_cur->line);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_FIELD_ACCESS) {
                        
                        // $VAR = $VAR_OBJECT->{NAME}
                        SPVM_OP* op_field_access = op_assign_from;
                        SPVM_OP* op_term_object = op_field_access->first;
                        
                        // Call field
                        SPVM_FIELD_ACCESS* field_access = op_field_access->uv.field_access;
                        
                        SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_field_access);

                        SPVM_TYPE* field_access_type = SPVM_OP_get_type(compiler, op_field_access->uv.field_access->field->op_package);
                        
                        _Bool is_value_access = SPVM_TYPE_is_value_type(compiler, field_access_type);
                        
                        if (is_value_access) {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          switch (type->basic_type->id) {
                            case SPVM_BASIC_TYPE_C_ID_BYTE:
                              opcode.id = SPVM_OPCODE_C_ID_MOVE_BYTE;
                              break;
                            case SPVM_BASIC_TYPE_C_ID_SHORT:
                              opcode.id = SPVM_OPCODE_C_ID_MOVE_SHORT;
                              break;
                            case SPVM_BASIC_TYPE_C_ID_INT:
                              opcode.id = SPVM_OPCODE_C_ID_MOVE_INT;
                              break;
                            case SPVM_BASIC_TYPE_C_ID_LONG:
                              opcode.id = SPVM_OPCODE_C_ID_MOVE_LONG;
                              break;
                            case SPVM_BASIC_TYPE_C_ID_FLOAT:
                              opcode.id = SPVM_OPCODE_C_ID_MOVE_FLOAT;
                              break;
                            case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                              opcode.id = SPVM_OPCODE_C_ID_MOVE_DOUBLE;
                              break;
                            default:
                              assert(0);
                          }
                          
                          // Field absolute name symbol
                          int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                          int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_term_object) + op_field_access->uv.field_access->field->index;

                          opcode.operand0 = var_id_out;
                          opcode.operand1 = var_id_in;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                        }
                        else {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          if (type->dimension == 0) {
                            switch (type->basic_type->id) {
                              case SPVM_BASIC_TYPE_C_ID_BYTE:
                                opcode.id = SPVM_OPCODE_C_ID_GET_FIELD_BYTE;
                                break;
                              case SPVM_BASIC_TYPE_C_ID_SHORT:
                                opcode.id = SPVM_OPCODE_C_ID_GET_FIELD_SHORT;
                                break;
                              case SPVM_BASIC_TYPE_C_ID_INT:
                                opcode.id = SPVM_OPCODE_C_ID_GET_FIELD_INT;
                                break;
                              case SPVM_BASIC_TYPE_C_ID_LONG:
                                opcode.id = SPVM_OPCODE_C_ID_GET_FIELD_LONG;
                                break;
                              case SPVM_BASIC_TYPE_C_ID_FLOAT:
                                opcode.id = SPVM_OPCODE_C_ID_GET_FIELD_FLOAT;
                                break;
                              case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                                opcode.id = SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE;
                                break;
                              default:
                                opcode.id = SPVM_OPCODE_C_ID_GET_FIELD_OBJECT;
                            }
                          }
                          else {
                            opcode.id = SPVM_OPCODE_C_ID_GET_FIELD_OBJECT;
                          }
                          
                          // Field absolute name symbol
                          int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                          int32_t index_term_object = SPVM_OP_get_my_var_id(compiler, op_term_object);

                          opcode.operand0 = var_id_out;
                          opcode.operand1 = index_term_object;
                          opcode.operand2 = field_access->sub_rel_id;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          SPVM_OPCODE_BUILDER_push_if_croak(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_croak_catch_goto_opcode_rel_index_stack, if_croak_return_goto_opcode_rel_index_stack, op_sub, op_cur->line);
                        }
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_ARRAY_ACCESS) {
                        
                        // $VAR = $VAR_ARRAY->[$VAR_INDEX]
                        SPVM_OP* op_array_access = op_assign_from;
                        SPVM_OP* op_term_array = op_array_access->first;
                        SPVM_OP* op_term_index = op_array_access->last;
                        
                        SPVM_TYPE* array_type = SPVM_OP_get_type(compiler, op_term_array);

                        _Bool is_value_t_array = 0;
                        SPVM_BASIC_TYPE* array_basic_type = array_type->basic_type;
                        SPVM_OP* op_package = SPVM_HASH_fetch(compiler->op_package_symtable, array_basic_type->name, strlen(array_basic_type->name));
                        if (op_package) {
                          SPVM_PACKAGE* package = op_package->uv.package;
                          if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE_T) {
                            assert(array_type->dimension == 1);
                            is_value_t_array = 1;
                          }
                        }
                        
                        if (is_value_t_array) {
                          SPVM_OP* op_first_field = SPVM_LIST_fetch(op_package->uv.package->op_fields, 0);
                          
                          SPVM_TYPE* element_type = SPVM_OP_get_type(compiler, op_first_field);
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          assert(element_type->dimension == 0);
                          switch (element_type->basic_type->id) {
                            case SPVM_BASIC_TYPE_C_ID_BYTE:
                              opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FETCH_BYTE;
                              break;
                            case SPVM_BASIC_TYPE_C_ID_SHORT:
                              opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FETCH_SHORT;
                              break;
                            case SPVM_BASIC_TYPE_C_ID_INT:
                              opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FETCH_INT;
                              break;
                            case SPVM_BASIC_TYPE_C_ID_LONG:
                              opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FETCH_LONG;
                              break;
                            case SPVM_BASIC_TYPE_C_ID_FLOAT:
                              opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FETCH_FLOAT;
                              break;
                            case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                              opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FETCH_DOUBLE;
                              break;
                            default:
                              assert(0);
                          }
                          int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                          int32_t index_term_array = SPVM_OP_get_my_var_id(compiler, op_term_array);
                          int32_t index_term_index = SPVM_OP_get_my_var_id(compiler, op_term_index);
                          int32_t unit = array_basic_type->op_package->uv.package->op_fields->length;

                          opcode.operand0 = var_id_out;
                          opcode.operand1 = index_term_array;
                          opcode.operand2 = index_term_index;
                          opcode.operand3 = unit;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          SPVM_OPCODE_BUILDER_push_if_croak(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_croak_catch_goto_opcode_rel_index_stack, if_croak_return_goto_opcode_rel_index_stack, op_sub, op_cur->line);
                        }
                        else {
                          SPVM_TYPE* element_type = SPVM_OP_get_type(compiler, op_array_access);
                        
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          if (element_type->dimension == 0) {
                            switch (element_type->basic_type->id) {
                              case SPVM_BASIC_TYPE_C_ID_BYTE:
                                opcode.id = SPVM_OPCODE_C_ID_ARRAY_FETCH_BYTE;
                                break;
                              case SPVM_BASIC_TYPE_C_ID_SHORT:
                                opcode.id = SPVM_OPCODE_C_ID_ARRAY_FETCH_SHORT;
                                break;
                              case SPVM_BASIC_TYPE_C_ID_INT:
                                opcode.id = SPVM_OPCODE_C_ID_ARRAY_FETCH_INT;
                                break;
                              case SPVM_BASIC_TYPE_C_ID_LONG:
                                opcode.id = SPVM_OPCODE_C_ID_ARRAY_FETCH_LONG;
                                break;
                              case SPVM_BASIC_TYPE_C_ID_FLOAT:
                                opcode.id = SPVM_OPCODE_C_ID_ARRAY_FETCH_FLOAT;
                                break;
                              case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                                opcode.id = SPVM_OPCODE_C_ID_ARRAY_FETCH_DOUBLE;
                                break;
                              default:
                                opcode.id = SPVM_OPCODE_C_ID_ARRAY_FETCH_OBJECT;
                            }
                          }
                          else {
                            opcode.id = SPVM_OPCODE_C_ID_ARRAY_FETCH_OBJECT;
                          }

                          int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                          int32_t index_term_array = SPVM_OP_get_my_var_id(compiler, op_term_array);
                          int32_t index_term_index = SPVM_OP_get_my_var_id(compiler, op_term_index);

                          opcode.operand0 = var_id_out;
                          opcode.operand1 = index_term_array;
                          opcode.operand2 = index_term_index;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          SPVM_OPCODE_BUILDER_push_if_croak(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_croak_catch_goto_opcode_rel_index_stack, if_croak_return_goto_opcode_rel_index_stack, op_sub, op_cur->line);
                        }
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_PACKAGE_VAR_ACCESS) {
                        SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_assign_from);
                        
                        SPVM_PACKAGE_VAR_ACCESS* package_var_access = op_assign_from->uv.package_var_access;
                        
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        if (type->dimension == 0) {
                          switch (type->basic_type->id) {
                            case SPVM_BASIC_TYPE_C_ID_BYTE:
                              opcode.id = SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_BYTE;
                              break;
                            case SPVM_BASIC_TYPE_C_ID_SHORT:
                              opcode.id = SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_SHORT;
                              break;
                            case SPVM_BASIC_TYPE_C_ID_INT:
                              opcode.id = SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_INT;
                              break;
                            case SPVM_BASIC_TYPE_C_ID_LONG:
                              opcode.id = SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_LONG;
                              break;
                            case SPVM_BASIC_TYPE_C_ID_FLOAT:
                              opcode.id = SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_FLOAT;
                              break;
                            case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                              opcode.id = SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_DOUBLE;
                              break;
                            default:
                              opcode.id = SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_OBJECT;
                          }
                        }
                        else {
                          opcode.id = SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_OBJECT;
                        }
                        
                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        
                        opcode.operand0 = var_id_out;
                        opcode.operand1 = package_var_access->sub_rel_id;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_EXCEPTION_VAR) {
                        // VAR = EXCEPTION_VAR
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        opcode.id = SPVM_OPCODE_C_ID_GET_EXCEPTION_VAR;

                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        
                        opcode.operand0 = var_id_out;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_ADD) {
                        
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        assert(type_to->dimension == 0);
                        
                        switch (type_to->basic_type->id) {
                          case SPVM_BASIC_TYPE_C_ID_INT:
                            opcode.id = SPVM_OPCODE_C_ID_ADD_INT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_LONG:
                            opcode.id = SPVM_OPCODE_C_ID_ADD_LONG;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_FLOAT:
                            opcode.id = SPVM_OPCODE_C_ID_ADD_FLOAT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                            opcode.id = SPVM_OPCODE_C_ID_ADD_DOUBLE;
                            break;
                          default:
                            assert(0);
                        }

                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_assign_from->first);
                        int32_t var_id_in2 = SPVM_OP_get_my_var_id(compiler, op_assign_from->last);
                        
                        opcode.operand0 = var_id_out;
                        opcode.operand1 = var_id_in1;
                        opcode.operand2 = var_id_in2;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_SUBTRACT) {

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));

                        assert(type_to->dimension == 0);
                        switch (type_to->basic_type->id) {
                          case SPVM_BASIC_TYPE_C_ID_INT:
                            opcode.id = SPVM_OPCODE_C_ID_SUBTRACT_INT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_LONG:
                            opcode.id = SPVM_OPCODE_C_ID_SUBTRACT_LONG;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_FLOAT:
                            opcode.id = SPVM_OPCODE_C_ID_SUBTRACT_FLOAT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                            opcode.id = SPVM_OPCODE_C_ID_SUBTRACT_DOUBLE;
                            break;
                          default:
                            assert(0);
                        }
                        
                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_assign_from->first);
                        int32_t var_id_in2 = SPVM_OP_get_my_var_id(compiler, op_assign_from->last);
                        
                        opcode.operand0 = var_id_out;
                        opcode.operand1 = var_id_in1;
                        opcode.operand2 = var_id_in2;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_MULTIPLY) {

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));

                        assert(type_to->dimension == 0);
                        switch (type_to->basic_type->id) {
                          case SPVM_BASIC_TYPE_C_ID_INT:
                            opcode.id = SPVM_OPCODE_C_ID_MULTIPLY_INT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_LONG:
                            opcode.id = SPVM_OPCODE_C_ID_MULTIPLY_LONG;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_FLOAT:
                            opcode.id = SPVM_OPCODE_C_ID_MULTIPLY_FLOAT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                            opcode.id = SPVM_OPCODE_C_ID_MULTIPLY_DOUBLE;
                            break;
                          default:
                            assert(0);
                        }
                        
                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_assign_from->first);
                        int32_t var_id_in2 = SPVM_OP_get_my_var_id(compiler, op_assign_from->last);
                        
                        opcode.operand0 = var_id_out;
                        opcode.operand1 = var_id_in1;
                        opcode.operand2 = var_id_in2;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_DIVIDE) {

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        assert(type_to->dimension == 0);
                        switch (type_to->basic_type->id) {
                          case SPVM_BASIC_TYPE_C_ID_INT:
                            opcode.id = SPVM_OPCODE_C_ID_DIVIDE_INT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_LONG:
                            opcode.id = SPVM_OPCODE_C_ID_DIVIDE_LONG;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_FLOAT:
                            opcode.id = SPVM_OPCODE_C_ID_DIVIDE_FLOAT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                            opcode.id = SPVM_OPCODE_C_ID_DIVIDE_DOUBLE;
                            break;
                          default:
                            assert(0);
                        }
                        
                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_assign_from->first);
                        int32_t var_id_in2 = SPVM_OP_get_my_var_id(compiler, op_assign_from->last);
                        
                        opcode.operand0 = var_id_out;
                        opcode.operand1 = var_id_in1;
                        opcode.operand2 = var_id_in2;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                        
                        // Check croak
                        assert(type_to->dimension == 0);
                        switch (type_to->basic_type->id) {
                          case SPVM_BASIC_TYPE_C_ID_INT:
                          case SPVM_BASIC_TYPE_C_ID_LONG:
                            SPVM_OPCODE_BUILDER_push_if_croak(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_croak_catch_goto_opcode_rel_index_stack, if_croak_return_goto_opcode_rel_index_stack, op_sub, op_cur->line);
                          break;
                        }
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_REMAINDER) {
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        assert(type_to->dimension == 0);
                        switch (type_to->basic_type->id) {
                          case SPVM_BASIC_TYPE_C_ID_INT:
                            opcode.id = SPVM_OPCODE_C_ID_REMAINDER_INT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_LONG:
                            opcode.id = SPVM_OPCODE_C_ID_REMAINDER_LONG;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_FLOAT:
                            opcode.id = SPVM_OPCODE_C_ID_REMAINDER_FLOAT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                            opcode.id = SPVM_OPCODE_C_ID_REMAINDER_DOUBLE;
                            break;
                          default:
                            assert(0);
                        }
                        
                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_assign_from->first);
                        int32_t var_id_in2 = SPVM_OP_get_my_var_id(compiler, op_assign_from->last);
                        
                        opcode.operand0 = var_id_out;
                        opcode.operand1 = var_id_in1;
                        opcode.operand2 = var_id_in2;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                        // Check croak
                        assert(type_to->dimension == 0);
                        switch (type_to->basic_type->id) {
                          case SPVM_BASIC_TYPE_C_ID_INT:
                          case SPVM_BASIC_TYPE_C_ID_LONG:
                            SPVM_OPCODE_BUILDER_push_if_croak(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_croak_catch_goto_opcode_rel_index_stack, if_croak_return_goto_opcode_rel_index_stack, op_sub, op_cur->line);
                          break;
                        }
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_LEFT_SHIFT) {

                        

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        assert(type_to->dimension == 0);
                        switch (type_to->basic_type->id) {
                          case SPVM_BASIC_TYPE_C_ID_INT:
                            opcode.id = SPVM_OPCODE_C_ID_LEFT_SHIFT_INT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_LONG:
                            opcode.id = SPVM_OPCODE_C_ID_LEFT_SHIFT_LONG;
                            break;
                          default:
                            assert(0);
                        }

                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_assign_from->first);
                        int32_t var_id_in2 = SPVM_OP_get_my_var_id(compiler, op_assign_from->last);
                        
                        opcode.operand0 = var_id_out;
                        opcode.operand1 = var_id_in1;
                        opcode.operand2 = var_id_in2;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_RIGHT_SHIFT) {

                        

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        assert(type_to->dimension == 0);
                        switch (type_to->basic_type->id) {
                          case SPVM_BASIC_TYPE_C_ID_INT:
                            opcode.id = SPVM_OPCODE_C_ID_RIGHT_SHIFT_INT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_LONG:
                            opcode.id = SPVM_OPCODE_C_ID_RIGHT_SHIFT_LONG;
                            break;
                          default:
                            assert(0);
                        }

                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_assign_from->first);
                        int32_t var_id_in2 = SPVM_OP_get_my_var_id(compiler, op_assign_from->last);
                        
                        opcode.operand0 = var_id_out;
                        opcode.operand1 = var_id_in1;
                        opcode.operand2 = var_id_in2;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_RIGHT_SHIFT_UNSIGNED) {

                        

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        assert(type_to->dimension == 0);
                        switch (type_to->basic_type->id) {
                          case SPVM_BASIC_TYPE_C_ID_INT:
                            opcode.id = SPVM_OPCODE_C_ID_RIGHT_SHIFT_UNSIGNED_INT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_LONG:
                            opcode.id = SPVM_OPCODE_C_ID_RIGHT_SHIFT_UNSIGNED_LONG;
                            break;
                          default:
                            assert(0);
                        }

                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_assign_from->first);
                        int32_t var_id_in2 = SPVM_OP_get_my_var_id(compiler, op_assign_from->last);
                        
                        opcode.operand0 = var_id_out;
                        opcode.operand1 = var_id_in1;
                        opcode.operand2 = var_id_in2;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_BIT_AND) {

                        

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        assert(type_to->dimension == 0);
                        switch (type_to->basic_type->id) {
                          case SPVM_BASIC_TYPE_C_ID_INT:
                            opcode.id = SPVM_OPCODE_C_ID_BIT_AND_INT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_LONG:
                            opcode.id = SPVM_OPCODE_C_ID_BIT_AND_LONG;
                            break;
                          default:
                            assert(0);
                        }

                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_assign_from->first);
                        int32_t var_id_in2 = SPVM_OP_get_my_var_id(compiler, op_assign_from->last);
                        
                        opcode.operand0 = var_id_out;
                        opcode.operand1 = var_id_in1;
                        opcode.operand2 = var_id_in2;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_BIT_OR) {

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        assert(type_to->dimension == 0);
                        switch (type_to->basic_type->id) {
                          case SPVM_BASIC_TYPE_C_ID_INT:
                            opcode.id = SPVM_OPCODE_C_ID_BIT_OR_INT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_LONG:
                            opcode.id = SPVM_OPCODE_C_ID_BIT_OR_LONG;
                            break;
                          default:
                            assert(0);
                        }

                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_assign_from->first);
                        int32_t var_id_in2 = SPVM_OP_get_my_var_id(compiler, op_assign_from->last);
                        
                        opcode.operand0 = var_id_out;
                        opcode.operand1 = var_id_in1;
                        opcode.operand2 = var_id_in2;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_BIT_XOR) {

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        assert(type_to->dimension == 0);
                        switch (type_to->basic_type->id) {
                          case SPVM_BASIC_TYPE_C_ID_INT:
                            opcode.id = SPVM_OPCODE_C_ID_BIT_XOR_INT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_LONG:
                            opcode.id = SPVM_OPCODE_C_ID_BIT_XOR_LONG;
                            break;
                          default:
                            assert(0);
                        }

                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_assign_from->first);
                        int32_t var_id_in2 = SPVM_OP_get_my_var_id(compiler, op_assign_from->last);
                        
                        opcode.operand0 = var_id_out;
                        opcode.operand1 = var_id_in1;
                        opcode.operand2 = var_id_in2;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_COMPLEMENT) {

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));

                        assert(type_to->dimension == 0);
                        switch (type_to->basic_type->id) {
                          case SPVM_BASIC_TYPE_C_ID_INT:
                            opcode.id = SPVM_OPCODE_C_ID_COMPLEMENT_INT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_LONG:
                            opcode.id = SPVM_OPCODE_C_ID_COMPLEMENT_LONG;
                            break;
                          default:
                            assert(0);
                        }
                        
                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_assign_from->first);
                        
                        opcode.operand0 = var_id_out;
                        opcode.operand1 = var_id_in;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_PLUS) {

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                       
                        assert(type_to->dimension == 0);
                        switch (type_to->basic_type->id) {
                          case SPVM_BASIC_TYPE_C_ID_INT:
                            opcode.id = SPVM_OPCODE_C_ID_MOVE_INT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_LONG:
                            opcode.id = SPVM_OPCODE_C_ID_MOVE_LONG;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_FLOAT:
                            opcode.id = SPVM_OPCODE_C_ID_MOVE_FLOAT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                            opcode.id = SPVM_OPCODE_C_ID_MOVE_DOUBLE;
                            break;
                          default:
                            assert(0);
                        }
                        
                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_assign_from->first);
                        
                        opcode.operand0 = var_id_out;
                        opcode.operand1 = var_id_in;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_NEGATE) {

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                       
                        assert(type_to->dimension == 0);
                        switch (type_to->basic_type->id) {
                          case SPVM_BASIC_TYPE_C_ID_INT:
                            opcode.id = SPVM_OPCODE_C_ID_NEGATE_INT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_LONG:
                            opcode.id = SPVM_OPCODE_C_ID_NEGATE_LONG;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_FLOAT:
                            opcode.id = SPVM_OPCODE_C_ID_NEGATE_FLOAT;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                            opcode.id = SPVM_OPCODE_C_ID_NEGATE_DOUBLE;
                            break;
                          default:
                            assert(0);
                        }
                        
                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_assign_from->first);
                        
                        opcode.operand0 = var_id_out;
                        opcode.operand1 = var_id_in;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_CONSTANT) {
                        SPVM_CONSTANT* constant = op_assign_from->uv.constant;

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                        opcode.operand0 = var_id_out;

                        assert(type_to->dimension == 0);
                        switch (type_to->basic_type->id) {
                          case SPVM_BASIC_TYPE_C_ID_BYTE:
                            opcode.id = SPVM_OPCODE_C_ID_GET_CONSTANT_BYTE;
                            *(SPVM_VALUE_byte*)&opcode.operand1 = *(SPVM_VALUE_byte*)&constant->value;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_SHORT:
                            opcode.id = SPVM_OPCODE_C_ID_GET_CONSTANT_SHORT;
                            *(SPVM_VALUE_short*)&opcode.operand1 = *(SPVM_VALUE_short*)&constant->value;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_INT:
                            opcode.id = SPVM_OPCODE_C_ID_GET_CONSTANT_INT;
                            *(SPVM_VALUE_int*)&opcode.operand1 = *(SPVM_VALUE_int*)&constant->value;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_LONG:
                            opcode.id = SPVM_OPCODE_C_ID_GET_CONSTANT_LONG;
                            opcode.operand1 = constant->sub_rel_id;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_FLOAT:
                            opcode.id = SPVM_OPCODE_C_ID_GET_CONSTANT_FLOAT;
                            *(SPVM_VALUE_float*)&opcode.operand1 = *(SPVM_VALUE_float*)&constant->value;
                            break;
                          case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                            opcode.id = SPVM_OPCODE_C_ID_GET_CONSTANT_DOUBLE;
                            opcode.operand1 = constant->sub_rel_id;
                            break;
                          default:
                            assert(0);
                        }
                        
                        assert(constant->id != -1);
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_CONVERT) {
                        
                        SPVM_OP* op_dist_term = op_assign_to;
                        SPVM_OP* op_src_term = op_assign_from->first;
                        SPVM_OP* op_dist_type = op_assign_from->last;
                        
                        SPVM_TYPE* src_type = SPVM_OP_get_type(compiler, op_src_term);
                        SPVM_TYPE* dist_type = SPVM_OP_get_type(compiler, op_dist_type);

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        if (src_type->dimension == 0 && src_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                          if (dist_type->dimension == 0) {
                            if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_BYTE;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_SHORT;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_INT;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_LONG;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_FLOAT;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_DOUBLE;
                            }
                          }
                          else if (dist_type->dimension == 1 && dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                            opcode.id = SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_STRING;
                          }
                          else {
                            assert(0);
                          }
                        }
                        else if (src_type->dimension == 0 && src_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT) {
                          if (dist_type->dimension == 0) {
                            if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_BYTE;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_SHORT;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_INT;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_LONG;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_FLOAT;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_DOUBLE;
                            }
                          }
                          else if (dist_type->dimension == 1 && dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                            opcode.id = SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_STRING;
                          }
                          else {
                            assert(0);
                          }
                        }
                        else if (src_type->dimension == 0 && src_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
                          if (dist_type->dimension == 0) {
                            if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_INT_TO_BYTE;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_INT_TO_SHORT;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_INT_TO_INT;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_INT_TO_LONG;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_INT_TO_FLOAT;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_INT_TO_DOUBLE;
                            }
                          }
                          else if (dist_type->dimension == 1 && dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                            opcode.id = SPVM_OPCODE_C_ID_CONVERT_INT_TO_STRING;
                          }
                          else {
                            assert(0);
                          }
                        }
                        else if (src_type->dimension == 0 && src_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
                          if (dist_type->dimension == 0) {
                            if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_LONG_TO_BYTE;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_LONG_TO_SHORT;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_LONG_TO_INT;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_LONG_TO_LONG;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_LONG_TO_FLOAT;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_LONG_TO_DOUBLE;
                            }
                          }
                          else if (dist_type->dimension == 1 && dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                            opcode.id = SPVM_OPCODE_C_ID_CONVERT_LONG_TO_STRING;
                          }
                          else {
                            assert(0);
                          }
                        }
                        else if (src_type->dimension == 0 && src_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
                          if (dist_type->dimension == 0) {
                            if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_BYTE;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_SHORT;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_INT;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_LONG;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_FLOAT;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_DOUBLE;
                            }
                          }
                          else if (dist_type->dimension == 1 && dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                            opcode.id = SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_STRING;
                          }
                          else {
                            assert(0);
                          }
                        }
                        else if (src_type->dimension == 0 && src_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
                          if (dist_type->dimension == 0) {
                            if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_BYTE;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_SHORT;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_INT;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_LONG;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_FLOAT;
                            }
                            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
                              opcode.id = SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_DOUBLE;
                            }
                          }
                          else if (dist_type->dimension == 1 && dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                            opcode.id = SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_STRING;
                          }
                          else {
                            assert(0);
                          }
                        }
                        // Check cast
                        else {
                          if (src_type->basic_type->id == dist_type->basic_type->id && src_type->dimension == dist_type->dimension) {
                            if (src_type->dimension == 0) {
                              switch (src_type->basic_type->id) {
                                case SPVM_BASIC_TYPE_C_ID_BYTE:
                                  opcode.id = SPVM_OPCODE_C_ID_MOVE_BYTE;
                                  break;
                                case SPVM_BASIC_TYPE_C_ID_SHORT:
                                  opcode.id = SPVM_OPCODE_C_ID_MOVE_SHORT;
                                  break;
                                case SPVM_BASIC_TYPE_C_ID_INT:
                                  opcode.id = SPVM_OPCODE_C_ID_MOVE_INT;
                                  break;
                                case SPVM_BASIC_TYPE_C_ID_LONG:
                                  opcode.id = SPVM_OPCODE_C_ID_MOVE_LONG;
                                  break;
                                case SPVM_BASIC_TYPE_C_ID_FLOAT:
                                  opcode.id = SPVM_OPCODE_C_ID_MOVE_FLOAT;
                                  break;
                                case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                                  opcode.id = SPVM_OPCODE_C_ID_MOVE_DOUBLE;
                                  break;
                                default:
                                  opcode.id = SPVM_OPCODE_C_ID_MOVE_OBJECT;
                              }
                            }
                            else {
                              opcode.id = SPVM_OPCODE_C_ID_MOVE_OBJECT;
                            }
                          }
                          else {
                            opcode.id = SPVM_OPCODE_C_ID_CHECK_CAST;
                            opcode.operand2 = op_dist_type->uv.type->sub_rel_id;
                          }
                        }

                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_dist_term);
                        int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_src_term);
                        
                        opcode.operand0 = var_id_out;
                        opcode.operand1 = var_id_in;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_NEW) {
                        
                        if (op_assign_from->first->id == SPVM_OP_C_ID_CONSTANT) {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          opcode.id = SPVM_OPCODE_C_ID_NEW_STRING;

                          int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                          SPVM_CONSTANT* constant = op_assign_from->first->uv.constant;

                          opcode.operand0 = var_id_out;
                          opcode.operand1 = constant->sub_rel_id;

                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                        }
                        else if (op_assign_from->first->id == SPVM_OP_C_ID_TYPE) {
                          
                          SPVM_OP* op_type = op_assign_from->first;
                          
                          SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_assign_from->first);
                          
                          if (type->dimension > 0) {
                            /*
                              NEW op_assign_from
                                 TYPE op_assign_from->first
                                   ELEMENT_TYPE op_assign_from->first->first
                                   INDEX op_assign_from->first->last
                            */
                            
                            if (type->dimension == 1) {
                              switch (type->basic_type->id) {
                                case SPVM_BASIC_TYPE_C_ID_BYTE: {
                                  SPVM_OPCODE opcode;
                                  memset(&opcode, 0, sizeof(SPVM_OPCODE));
                                  opcode.id = SPVM_OPCODE_C_ID_NEW_BYTE_ARRAY;

                                  int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                                  int32_t var_id_index = SPVM_OP_get_my_var_id(compiler, op_assign_from->first->last);

                                  opcode.operand0 = var_id_out;
                                  opcode.operand1 = var_id_index;

                                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                                  
                                  break;
                                }
                                case SPVM_BASIC_TYPE_C_ID_SHORT: {
                                  SPVM_OPCODE opcode;
                                  memset(&opcode, 0, sizeof(SPVM_OPCODE));
                                  opcode.id = SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY;

                                  int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                                  int32_t var_id_index = SPVM_OP_get_my_var_id(compiler, op_assign_from->first->last);
                                  
                                  opcode.operand0 = var_id_out;
                                  opcode.operand1 = var_id_index;

                                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                                  
                                  break;
                                }
                                case SPVM_BASIC_TYPE_C_ID_INT: {
                                  SPVM_OPCODE opcode;
                                  memset(&opcode, 0, sizeof(SPVM_OPCODE));

                                  opcode.id = SPVM_OPCODE_C_ID_NEW_INT_ARRAY;

                                  int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                                  int32_t var_id_index = SPVM_OP_get_my_var_id(compiler, op_assign_from->first->last);

                                  opcode.operand0 = var_id_out;
                                  opcode.operand1 = var_id_index;

                                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                                  
                                  break;
                                }
                                case SPVM_BASIC_TYPE_C_ID_LONG: {
                                  SPVM_OPCODE opcode;
                                  memset(&opcode, 0, sizeof(SPVM_OPCODE));

                                  opcode.id = SPVM_OPCODE_C_ID_NEW_LONG_ARRAY;

                                  int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                                  int32_t var_id_index = SPVM_OP_get_my_var_id(compiler, op_assign_from->first->last);

                                  opcode.operand0 = var_id_out;
                                  opcode.operand1 = var_id_index;

                                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                                  
                                  break;
                                }
                                case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                                  SPVM_OPCODE opcode;
                                  memset(&opcode, 0, sizeof(SPVM_OPCODE));

                                  opcode.id = SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY;

                                  int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                                  int32_t var_id_index = SPVM_OP_get_my_var_id(compiler, op_assign_from->first->last);

                                  opcode.operand0 = var_id_out;
                                  opcode.operand1 = var_id_index;

                                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                                  
                                  break;
                                }
                                case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                                  SPVM_OPCODE opcode;
                                  memset(&opcode, 0, sizeof(SPVM_OPCODE));

                                  opcode.id = SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY;
                                  
                                  int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                                  int32_t var_id_index = SPVM_OP_get_my_var_id(compiler, op_assign_from->first->last);

                                  opcode.operand0 = var_id_out;
                                  opcode.operand1 = var_id_index;

                                  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                                  break;
                                }
                                default: {
                                  _Bool is_value_t_array = 0;
                                  
                                  SPVM_BASIC_TYPE* basic_type = type->basic_type;
                                  SPVM_OP* op_package = SPVM_HASH_fetch(compiler->op_package_symtable, basic_type->name, strlen(basic_type->name));
                                  if (op_package) {
                                    SPVM_PACKAGE* package = op_package->uv.package;
                                    if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE_T) {
                                      assert(type->dimension == 1);
                                      is_value_t_array = 1;
                                    }
                                  }
                                  
                                  if (is_value_t_array) {
                                    SPVM_OPCODE opcode;
                                    memset(&opcode, 0, sizeof(SPVM_OPCODE));

                                    opcode.id = SPVM_OPCODE_C_ID_NEW_VALUE_T_ARRAY;

                                    int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                                    SPVM_TYPE* type = op_assign_from->first->first->uv.type;
                                    int32_t basic_type_id = type->basic_type->id;
                                    int32_t var_id_index = SPVM_OP_get_my_var_id(compiler, op_assign_from->first->last);

                                    opcode.operand0 = var_id_out;
                                    opcode.operand1 = op_type->uv.type->sub_rel_id;
                                    opcode.operand2 = var_id_index;

                                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                                  }
                                  else {
                                    SPVM_OPCODE opcode;
                                    memset(&opcode, 0, sizeof(SPVM_OPCODE));

                                    opcode.id = SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY;

                                    int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                                    SPVM_TYPE* type = op_assign_from->first->first->uv.type;
                                    int32_t basic_type_id = type->basic_type->id;
                                    int32_t var_id_index = SPVM_OP_get_my_var_id(compiler, op_assign_from->first->last);

                                    opcode.operand0 = var_id_out;
                                    opcode.operand1 = op_type->uv.type->sub_rel_id;
                                    opcode.operand2 = var_id_index;

                                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                                  }
                                }
                              }
                            }
                            else {
                              SPVM_OPCODE opcode;
                              memset(&opcode, 0, sizeof(SPVM_OPCODE));

                              opcode.id = SPVM_OPCODE_C_ID_NEW_MULTI_ARRAY;

                              int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                              SPVM_TYPE* type = op_assign_from->first->first->uv.type;
                              int32_t var_id_index = SPVM_OP_get_my_var_id(compiler, op_assign_from->first->last);
                              
                              opcode.operand0 = var_id_out;
                              opcode.operand1 = op_type->uv.type->sub_rel_id;
                              opcode.operand2 = var_id_index;

                              SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                            }
                          }
                          else {
                            SPVM_OPCODE opcode;
                            memset(&opcode, 0, sizeof(SPVM_OPCODE));

                            opcode.id = SPVM_OPCODE_C_ID_NEW_OBJECT;
                            
                            int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                            
                            opcode.operand0 = var_id_out;
                            opcode.operand1 = type->sub_rel_id;
                            SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          }
                        }
                        else {
                          assert(0);
                        }
                      }
                      else if (op_assign_from->id == SPVM_OP_C_ID_VAR || op_assign_from->id == SPVM_OP_C_ID_ASSIGN) {
                        _Bool type_to_is_value_t = SPVM_TYPE_is_value_type(compiler, type_to);
                        
                        if (type_to_is_value_t) {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          opcode.id = SPVM_OPCODE_C_ID_MOVE_VALUES;

                          int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                          int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_assign_from);

                          opcode.operand0 = var_id_out;
                          opcode.operand1 = var_id_in;
                          opcode.operand2 = SPVM_TYPE_get_width(compiler, type_to);
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                        }
                        else {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          if (type_to->dimension == 0) {
                            switch (type_to->basic_type->id) {
                              case SPVM_BASIC_TYPE_C_ID_BYTE:
                                opcode.id = SPVM_OPCODE_C_ID_MOVE_BYTE;
                                break;
                              case SPVM_BASIC_TYPE_C_ID_SHORT:
                                opcode.id = SPVM_OPCODE_C_ID_MOVE_SHORT;
                                break;
                              case SPVM_BASIC_TYPE_C_ID_INT:
                                opcode.id = SPVM_OPCODE_C_ID_MOVE_INT;
                                break;
                              case SPVM_BASIC_TYPE_C_ID_LONG:
                                opcode.id = SPVM_OPCODE_C_ID_MOVE_LONG;
                                break;
                              case SPVM_BASIC_TYPE_C_ID_FLOAT:
                                opcode.id = SPVM_OPCODE_C_ID_MOVE_FLOAT;
                                break;
                              case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                                opcode.id = SPVM_OPCODE_C_ID_MOVE_DOUBLE;
                                break;
                              default:
                                opcode.id = SPVM_OPCODE_C_ID_MOVE_OBJECT;
                            }
                          }
                          else {
                            opcode.id = SPVM_OPCODE_C_ID_MOVE_OBJECT;
                          }

                          int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_assign_to);
                          int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_assign_from);

                          opcode.operand0 = var_id_out;
                          opcode.operand1 = var_id_in;
                          
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                        }
                      }
                      else {
                        break;
                      }
                    }
                    else if (op_assign_to->id == SPVM_OP_C_ID_PACKAGE_VAR_ACCESS) {
                      SPVM_OP* op_package_var_access = op_assign_to;
                      SPVM_PACKAGE_VAR_ACCESS* package_var_access = op_package_var_access->uv.package_var_access;

                      SPVM_TYPE* from_type = SPVM_OP_get_type(compiler, op_assign_from);

                      // PACKAGE_VAR_ACCESS = UNDEF
                      if (SPVM_TYPE_is_undef_type(compiler, from_type)) {
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        int32_t package_var_access_id = package_var_access->op_package_var->uv.package_var->id;
                        opcode.id = SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_UNDEF;
                        opcode.operand0 = package_var_access->sub_rel_id;
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      // PACKAGE_VAR_ACCESS = VAR
                      else {
                        SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_package_var_access);

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        if (type->dimension == 0) {
                          if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                            opcode.id = SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_BYTE;
                          }
                          else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT) {
                            opcode.id = SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_SHORT;
                          }
                          else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
                            opcode.id = SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_INT;
                          }
                          else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
                            opcode.id = SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_LONG;
                          }
                          else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
                            opcode.id = SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_FLOAT;
                          }
                          else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
                            opcode.id = SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_DOUBLE;
                          }
                          else {
                            opcode.id = SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_OBJECT;
                          }
                        }
                        else {
                          opcode.id = SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_OBJECT;
                        }
                                          
                        int32_t package_var_access_id = package_var_access->op_package_var->uv.package_var->id;
                        int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_assign_from);
                        
                        opcode.operand0 = package_var_access->sub_rel_id;
                        opcode.operand1 = var_id_in;
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                    }
                    else if (op_assign_to->id == SPVM_OP_C_ID_EXCEPTION_VAR) {
                      
                      SPVM_TYPE* from_type = SPVM_OP_get_type(compiler, op_assign_from);
                      
                      if (SPVM_TYPE_is_undef_type(compiler, from_type)) {
                        // EXCEPTION_VAR = undef
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        opcode.id = SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR_UNDEF;
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else {
                        // EXCEPTION_VAR = VAR
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        opcode.id = SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR;
                        int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_assign_from);
                        opcode.operand0 = var_id_in;
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                    }
                    else if (op_assign_to->id == SPVM_OP_C_ID_ARRAY_ACCESS) {
                      
                      // $VAR_ARRAY->[$VAR_INDEX] = $VAR_TERM
                      
                      SPVM_OP* op_array_access = op_assign_to;
                      SPVM_OP* op_term_array = op_array_access->first;
                      SPVM_OP* op_term_index = op_array_access->last;

                      SPVM_TYPE* array_type = SPVM_OP_get_type(compiler, op_term_array);

                      _Bool is_value_t_array = 0;
                      SPVM_BASIC_TYPE* array_basic_type = array_type->basic_type;
                      SPVM_OP* op_package = SPVM_HASH_fetch(compiler->op_package_symtable, array_basic_type->name, strlen(array_basic_type->name));
                      if (op_package) {
                        SPVM_PACKAGE* package = op_package->uv.package;
                        if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE_T) {
                          assert(array_type->dimension == 1);
                          is_value_t_array = 1;
                        }
                      }
                      
                      if (is_value_t_array) {
                        SPVM_OP* op_first_field = SPVM_LIST_fetch(op_package->uv.package->op_fields, 0);
                      
                        SPVM_TYPE* element_type = SPVM_OP_get_type(compiler, op_first_field);

                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        assert(element_type->dimension == 0);
                        if (element_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                          opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_STORE_BYTE;
                        }
                        else if (element_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT) {
                          opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_STORE_SHORT;
                        }
                        else if (element_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
                          opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_STORE_INT;
                        }
                        else if (element_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
                          opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_STORE_LONG;
                        }
                        else if (element_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
                          opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_STORE_FLOAT;
                        }
                        else if (element_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
                          opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_STORE_DOUBLE;
                        }

                        int32_t index_term_array = SPVM_OP_get_my_var_id(compiler, op_term_array);
                        int32_t index_term_index = SPVM_OP_get_my_var_id(compiler, op_term_index);
                        int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_assign_from);
                        int32_t unit = array_basic_type->op_package->uv.package->op_fields->length;
                        
                        opcode.operand0 = index_term_array;
                        opcode.operand1 = index_term_index;
                        opcode.operand2 = var_id_in;
                        opcode.operand3 = unit;

                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                        SPVM_OPCODE_BUILDER_push_if_croak(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_croak_catch_goto_opcode_rel_index_stack, if_croak_return_goto_opcode_rel_index_stack, op_sub, op_cur->line);
                      }
                      else {
                      
                        SPVM_TYPE* element_type = SPVM_OP_get_type(compiler, op_assign_from);

                        if (SPVM_TYPE_is_undef_type(compiler, element_type)) {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          opcode.id = SPVM_OPCODE_C_ID_ARRAY_STORE_UNDEF;
                          
                          int32_t index_term_array = SPVM_OP_get_my_var_id(compiler, op_term_array);
                          int32_t index_term_index = SPVM_OP_get_my_var_id(compiler, op_term_index);
                          
                          opcode.operand0 = index_term_array;
                          opcode.operand1 = index_term_index;
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          SPVM_OPCODE_BUILDER_push_if_croak(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_croak_catch_goto_opcode_rel_index_stack, if_croak_return_goto_opcode_rel_index_stack, op_sub, op_cur->line);
                        }
                        else {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          if (element_type->dimension == 0) {
                            if (element_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                              opcode.id = SPVM_OPCODE_C_ID_ARRAY_STORE_BYTE;
                            }
                            else if (element_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT) {
                              opcode.id = SPVM_OPCODE_C_ID_ARRAY_STORE_SHORT;
                            }
                            else if (element_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
                              opcode.id = SPVM_OPCODE_C_ID_ARRAY_STORE_INT;
                            }
                            else if (element_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
                              opcode.id = SPVM_OPCODE_C_ID_ARRAY_STORE_LONG;
                            }
                            else if (element_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
                              opcode.id = SPVM_OPCODE_C_ID_ARRAY_STORE_FLOAT;
                            }
                            else if (element_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
                              opcode.id = SPVM_OPCODE_C_ID_ARRAY_STORE_DOUBLE;
                            }
                            else {
                              opcode.id = SPVM_OPCODE_C_ID_ARRAY_STORE_OBJECT;
                            }
                          }
                          else {
                            opcode.id = SPVM_OPCODE_C_ID_ARRAY_STORE_OBJECT;
                          }
                          
                          int32_t index_term_array = SPVM_OP_get_my_var_id(compiler, op_term_array);
                          int32_t index_term_index = SPVM_OP_get_my_var_id(compiler, op_term_index);
                          int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_assign_from);
                          
                          opcode.operand0 = index_term_array;
                          opcode.operand1 = index_term_index;
                          opcode.operand2 = var_id_in;
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          SPVM_OPCODE_BUILDER_push_if_croak(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_croak_catch_goto_opcode_rel_index_stack, if_croak_return_goto_opcode_rel_index_stack, op_sub, op_cur->line);
                        }
                      }
                    }
                    // Set field
                    else if (op_assign_to->id == SPVM_OP_C_ID_FIELD_ACCESS) {
                      
                      SPVM_OP* op_field_access = op_assign_to;
                      SPVM_OP* op_term_object = op_field_access->first;

                      // Call field
                      SPVM_FIELD_ACCESS* field_access = op_field_access->uv.field_access;

                      SPVM_TYPE* from_type = SPVM_OP_get_type(compiler, op_assign_from);
                      
                      SPVM_TYPE* field_access_type = SPVM_OP_get_type(compiler, op_field_access->uv.field_access->field->op_package);
                      
                      _Bool is_value_access = SPVM_TYPE_is_value_type(compiler, field_access_type);
                      if (is_value_access) {
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        assert(from_type->dimension == 0);
                        if (from_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                          opcode.id = SPVM_OPCODE_C_ID_MOVE_BYTE;
                        }
                        else if (from_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT) {
                          opcode.id = SPVM_OPCODE_C_ID_MOVE_SHORT;
                        }
                        else if (from_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
                          opcode.id = SPVM_OPCODE_C_ID_MOVE_INT;
                        }
                        else if (from_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
                          opcode.id = SPVM_OPCODE_C_ID_MOVE_LONG;
                        }
                        else if (from_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
                          opcode.id = SPVM_OPCODE_C_ID_MOVE_FLOAT;
                        }
                        else if (from_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
                          opcode.id = SPVM_OPCODE_C_ID_MOVE_DOUBLE;
                        }
                        else {
                          assert(0);
                        }
                        
                        int32_t var_id_out = SPVM_OP_get_my_var_id(compiler, op_term_object) + op_field_access->uv.field_access->field->index;
                        int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_assign_from);
                        
                        opcode.operand0 = var_id_out;
                        opcode.operand1 = var_id_in;
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else {
                        if (SPVM_TYPE_is_undef_type(compiler, from_type)) {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          opcode.id = SPVM_OPCODE_C_ID_SET_FIELD_UNDEF;
                          
                          int32_t index_term_object = SPVM_OP_get_my_var_id(compiler, op_term_object);

                          opcode.operand0 = index_term_object;
                          opcode.operand1 = field_access->sub_rel_id;
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          SPVM_OPCODE_BUILDER_push_if_croak(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_croak_catch_goto_opcode_rel_index_stack, if_croak_return_goto_opcode_rel_index_stack, op_sub, op_cur->line);
                        }
                        else {
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          if (from_type->dimension == 0) {
                            if (from_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                              opcode.id = SPVM_OPCODE_C_ID_SET_FIELD_BYTE;
                            }
                            else if (from_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT) {
                              opcode.id = SPVM_OPCODE_C_ID_SET_FIELD_SHORT;
                            }
                            else if (from_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
                              opcode.id = SPVM_OPCODE_C_ID_SET_FIELD_INT;
                            }
                            else if (from_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
                              opcode.id = SPVM_OPCODE_C_ID_SET_FIELD_LONG;
                            }
                            else if (from_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
                              opcode.id = SPVM_OPCODE_C_ID_SET_FIELD_FLOAT;
                            }
                            else if (from_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
                              opcode.id = SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE;
                            }
                            else {
                              opcode.id = SPVM_OPCODE_C_ID_SET_FIELD_OBJECT;
                            }
                          }
                          else {
                            opcode.id = SPVM_OPCODE_C_ID_SET_FIELD_OBJECT;
                          }
                          
                          int32_t index_term_object = SPVM_OP_get_my_var_id(compiler, op_term_object);
                          int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_assign_from);
                          
                          opcode.operand0 = index_term_object;
                          opcode.operand1 = field_access->sub_rel_id;
                          opcode.operand2 = var_id_in;
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                          SPVM_OPCODE_BUILDER_push_if_croak(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_croak_catch_goto_opcode_rel_index_stack, if_croak_return_goto_opcode_rel_index_stack, op_sub, op_cur->line);
                        }
                      }
                    }
                    // Set field
                    else if (op_assign_to->id == SPVM_OP_C_ID_ARRAY_FIELD_ACCESS) {
                      
                      SPVM_OP* op_array_field_access = op_assign_to;
                      SPVM_OP* op_term_object = op_array_field_access->first;
                      SPVM_OP* op_term_index = op_array_field_access->last;

                      // Call field
                      SPVM_ARRAY_FIELD_ACCESS* array_field_access = op_array_field_access->uv.array_field_access;
                      SPVM_FIELD* field = array_field_access->field;

                      // Array type
                      SPVM_TYPE* array_type = SPVM_OP_get_type(compiler, op_array_field_access->first);
                      SPVM_BASIC_TYPE* array_basic_type = array_type->basic_type;

                      // Element type
                      SPVM_TYPE* element_type = SPVM_OP_get_type(compiler, op_assign_from);
                      SPVM_BASIC_TYPE* element_basic_type = element_type->basic_type;
                      
                      SPVM_OPCODE opcode;
                      memset(&opcode, 0, sizeof(SPVM_OPCODE));
                      
                      if (element_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                        opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_STORE_BYTE;
                      }
                      else if (element_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT) {
                        opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_STORE_SHORT;
                      }
                      else if (element_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
                        opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_STORE_INT;
                      }
                      else if (element_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
                        opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_STORE_LONG;
                      }
                      else if (element_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
                        opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_STORE_FLOAT;
                      }
                      else if (element_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
                        opcode.id = SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_STORE_DOUBLE;
                      }
                      
                      int32_t index_term_object = SPVM_OP_get_my_var_id(compiler, op_term_object);
                      int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_assign_from);
                      int32_t index_term_index = SPVM_OP_get_my_var_id(compiler, op_term_index);

                      int32_t unit = array_basic_type->op_package->uv.package->op_fields->length;
                      int32_t offset = field->index;
                      
                      opcode.operand0 = index_term_object;
                      opcode.operand1 = index_term_index;
                      opcode.operand2 = var_id_in;
                      opcode.operand3 = (offset << 4) + unit;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                      SPVM_OPCODE_BUILDER_push_if_croak(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_croak_catch_goto_opcode_rel_index_stack, if_croak_return_goto_opcode_rel_index_stack, op_sub, op_cur->line);
                    }
                    else {
                      assert(0);
                    }
                    
                    break;
                  }
                  case SPVM_OP_C_ID_SWITCH_CONDITION: {
                    
                    SPVM_SWITCH_INFO* switch_info = op_cur->uv.switch_info;

                    SPVM_OPCODE opcode_switch_info;
                    memset(&opcode_switch_info, 0, sizeof(SPVM_OPCODE));

                    opcode_switch_info.id = SPVM_OPCODE_C_ID_LOOKUP_SWITCH;

                    int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_cur->first);
                    opcode_switch_info.operand0 = var_id_in;
                    
                    // Default
                    opcode_switch_info.operand1 = 0;
                    
                    // Case count
                    int32_t cases_length = switch_info->op_cases->length;
                    opcode_switch_info.operand2 = switch_info->sub_rel_id;

                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode_switch_info);
                    
                    // Switch opcode index
                    SPVM_LIST_push(switch_info_stack, switch_info);
                    
                    break;
                  }
                  case SPVM_OP_C_ID_SWITCH: {
                    
                    // Pop switch information
                    SPVM_SWITCH_INFO* switch_info = SPVM_LIST_pop(switch_info_stack);
                    
                    int32_t cases_length = (int32_t) switch_info->op_cases->length;
                    
                    {
                      int32_t i;
                      for (i = 0; i < cases_length; i++) {
                        SPVM_OP* op_case = SPVM_LIST_fetch(switch_info->op_cases, i);
                        SPVM_LIST_push(switch_info->op_cases_ordered, op_case);
                      }
                    }
                    // sort by asc order
                    {
                      int32_t i;
                      for (i = 0; i < cases_length; i++) {
                        int32_t j;
                        {
                          for (j = i + 1; j < cases_length; j++) {
                            SPVM_OP* op_case_i = SPVM_LIST_fetch(switch_info->op_cases_ordered, i);
                            SPVM_OP* op_case_j = SPVM_LIST_fetch(switch_info->op_cases_ordered, j);
                            int32_t match_i = op_case_i->uv.case_info->op_constant->uv.constant->value.ival;
                            int32_t match_j = op_case_j->uv.case_info->op_constant->uv.constant->value.ival;
                            
                            if (match_i > match_j) {
                              SPVM_LIST_store(switch_info->op_cases_ordered, i, op_case_j);
                              SPVM_LIST_store(switch_info->op_cases_ordered, j, op_case_i);
                            }
                          }
                        }
                      }
                    }
                    
                    // Set last position
                    while (last_goto_opcode_rel_index_stack->length > 0) {
                      
                      int32_t last_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(last_goto_opcode_rel_index_stack);
                      
                      SPVM_OPCODE* opcode_goto = (opcode_array->values + sub_opcode_base + last_goto_opcode_rel_index);
                      int32_t last_goto_jump_opcode_rel_index = opcode_array->length - sub_opcode_base;
                      opcode_goto->operand0 = last_goto_jump_opcode_rel_index;
                    }
                    
                    break;
                  }
                  case SPVM_OP_C_ID_CASE: {
                    if (switch_info_stack->length > 0) {
                      SPVM_SWITCH_INFO* switch_info = SPVM_LIST_fetch(switch_info_stack, switch_info_stack->length - 1);
                      int32_t opcode_rel_index = opcode_array->length - sub_opcode_base;
                      op_cur->uv.case_info->opcode_rel_index = opcode_rel_index;
                    }
                    break;
                  }
                  case SPVM_OP_C_ID_DEFAULT: {
                    if (switch_info_stack->length > 0) {
                      SPVM_SWITCH_INFO* switch_info = SPVM_LIST_fetch(switch_info_stack, switch_info_stack->length - 1);
                      switch_info->default_opcode_rel_index = opcode_array->length - sub_opcode_base;
                    }
                    break;
                  }
                  case SPVM_OP_C_ID_FIELD_ACCESS: {
                    // Weaken field
                    if (op_cur->flag &= SPVM_OP_C_FLAG_FIELD_ACCESS_WEAKEN) {
                      SPVM_OPCODE opcode;
                      memset(&opcode, 0, sizeof(SPVM_OPCODE));

                      opcode.id = SPVM_OPCODE_C_ID_WEAKEN_FIELD_OBJECT;
                      
                      SPVM_OP* op_term_object = op_cur->first;
                      int32_t index_term_object = SPVM_OP_get_my_var_id(compiler, op_term_object);

                      opcode.operand0 = index_term_object;
                      opcode.operand1 = op_cur->uv.field_access->sub_rel_id;
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                      SPVM_OPCODE_BUILDER_push_if_croak(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_croak_catch_goto_opcode_rel_index_stack, if_croak_return_goto_opcode_rel_index_stack, op_sub, op_cur->line);
                    }
                    
                    break;
                  }
                  case SPVM_OP_C_ID_CROAK: {
                    
                    // SET_CROAK_FLAG_TRUE
                    {
                      SPVM_OPCODE opcode;
                      memset(&opcode, 0, sizeof(SPVM_OPCODE));
                      
                      opcode.id = SPVM_OPCODE_C_ID_SET_CROAK_FLAG_TRUE;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    }
                    
                    SPVM_OPCODE_BUILDER_push_if_croak(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_croak_catch_goto_opcode_rel_index_stack, if_croak_return_goto_opcode_rel_index_stack, op_sub, op_cur->line);
                    
                    break;
                  }
                  case SPVM_OP_C_ID_LAST: {
                    // GOTO end of loop init block
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    opcode.id = SPVM_OPCODE_C_ID_GOTO;
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    
                    int32_t opcode_rel_index = opcode_array->length - 1 - sub_opcode_base;
                    
                    SPVM_LIST_push(last_goto_opcode_rel_index_stack, (void*)(intptr_t)opcode_rel_index);
                    
                    break;
                  }
                  case SPVM_OP_C_ID_NEXT: {
                    // GOTO increment statement
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    opcode.id = SPVM_OPCODE_C_ID_GOTO;
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    
                    int32_t opcode_rel_index = opcode_array->length - 1 - sub_opcode_base;
                    
                    SPVM_LIST_push(next_goto_opcode_rel_index_stack, (void*)(intptr_t)opcode_rel_index);
                    
                    break;
                  }
                  case SPVM_OP_C_ID_BLOCK: { // Postorder
                    
                    if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_IF) {
                      
                      {
                        // Prepare to jump to end of true block
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));

                        opcode.id = SPVM_OPCODE_C_ID_GOTO;
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                        
                        int32_t opcode_rel_index = opcode_array->length - 1 - sub_opcode_base;
                        SPVM_LIST_push(if_block_end_goto_opcode_rel_index_stack, (void*)(intptr_t)opcode_rel_index);
                      }

                      int32_t if_eq_or_if_ne_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(if_eq_or_if_ne_goto_opcode_rel_index_stack);
                      
                      // Set jump
                      SPVM_OPCODE* if_eq_or_if_ne_goto = (opcode_array->values + sub_opcode_base + if_eq_or_if_ne_goto_opcode_rel_index);
                      int32_t if_eq_or_if_ne_jump_opcode_rel_index = opcode_array->length - sub_opcode_base;
                      if_eq_or_if_ne_goto->operand0 = if_eq_or_if_ne_jump_opcode_rel_index;
                    }
                    else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_ELSE) {
                      
                      assert(if_block_end_goto_opcode_rel_index_stack->length > 0);
                      
                      int32_t if_block_end_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(if_block_end_goto_opcode_rel_index_stack);
                      
                      SPVM_OPCODE* if_block_end_goto = (opcode_array->values + sub_opcode_base + if_block_end_goto_opcode_rel_index);
                      int32_t if_block_end_jump_opcode_rel_index = opcode_array->length - sub_opcode_base;
                      if_block_end_goto->operand0 = if_block_end_jump_opcode_rel_index;
                    }
                    else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_LOOP_INIT) {
                      // Set last position
                      while (last_goto_opcode_rel_index_stack->length > 0) {
                        
                        int32_t last_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(last_goto_opcode_rel_index_stack);
                        
                        SPVM_OPCODE* last_goto = (opcode_array->values + sub_opcode_base + last_goto_opcode_rel_index);
                        int32_t last_goto_jump_opcode_rel_index = opcode_array->length - sub_opcode_base;
                        last_goto->operand0 = last_goto_jump_opcode_rel_index;
                      }
                    }
                    else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_LOOP_STATEMENTS) {
                      // Set next position
                      while (next_goto_opcode_rel_index_stack->length > 0) {
                        
                        int32_t next_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(next_goto_opcode_rel_index_stack);
                        
                        SPVM_OPCODE* next_goto = (opcode_array->values + sub_opcode_base + next_goto_opcode_rel_index);
                        int32_t next_goto_jump_opcode_rel_index = opcode_array->length - sub_opcode_base;
                        next_goto->operand0 = next_goto_jump_opcode_rel_index;
                      }
                    }
                    else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_EVAL) {
                      // Set IF_CROAK_CATCH opcode index
                      while (if_croak_catch_goto_opcode_rel_index_stack->length > 0) {
                        int32_t if_croak_catch_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(if_croak_catch_goto_opcode_rel_index_stack);
                        
                        SPVM_OPCODE* if_croak_catch_goto = (opcode_array->values + sub_opcode_base + if_croak_catch_goto_opcode_rel_index);
                        int32_t if_croak_catch_goto_jump_rel_index = opcode_array->length - sub_opcode_base;
                        if_croak_catch_goto->operand0 = if_croak_catch_goto_jump_rel_index;
                      }
                      
                      SPVM_LIST_pop(push_eval_opcode_rel_index_stack);
                    }
                    else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_SUB) {
                      while (return_goto_opcode_rel_index_stack->length > 0) {
                        
                        int32_t return_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(return_goto_opcode_rel_index_stack);
                        
                        SPVM_OPCODE* return_goto = (opcode_array->values + sub_opcode_base + return_goto_opcode_rel_index);
                        int32_t return_goto_jump_opcode_rel_index = opcode_array->length - sub_opcode_base;
                        return_goto->operand1 = return_goto_jump_opcode_rel_index;
                      }

                      // Set IF_CROAK_RETURN opcode index
                      while (if_croak_return_goto_opcode_rel_index_stack->length > 0) {
                        int32_t if_croak_return_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(if_croak_return_goto_opcode_rel_index_stack);
                        
                        SPVM_OPCODE* if_croak_return_goto = (opcode_array->values + sub_opcode_base + if_croak_return_goto_opcode_rel_index);
                        int32_t if_croak_return_goto_jump_opcode_rel_index = opcode_array->length - sub_opcode_base;
                        if_croak_return_goto->operand0 = if_croak_return_goto_jump_opcode_rel_index;
                      }
                    }
                    
                    // Leave scope
                    int32_t mortal_top = (intptr_t)SPVM_LIST_pop(mortal_top_stack);

                    SPVM_OP* op_block_current = SPVM_LIST_fetch(op_block_stack, op_block_stack->length - 1);
                    
                    if (op_block_current->uv.block->have_object_var_decl) {
                      while (mortal_stack->length > mortal_top) {
                        SPVM_LIST_pop(mortal_stack);
                      }
                      
                      SPVM_OPCODE opcode;
                      memset(&opcode, 0, sizeof(SPVM_OPCODE));
                      opcode.id = SPVM_OPCODE_C_ID_LEAVE_SCOPE;
                      opcode.operand0 = mortal_top;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    }

                    SPVM_LIST_pop(op_block_stack);

                    break;
                  }
                  case SPVM_OP_C_ID_LOOP_INCREMENT: {
                    // Set loop first GOTO opcode
                    int32_t loop_first_goto_opcode_rel_index = (intptr_t)SPVM_LIST_fetch(loop_first_goto_opcode_rel_index_stack, loop_first_goto_opcode_rel_index_stack->length - 1);
                    
                    SPVM_OPCODE* loop_first_goto = (opcode_array->values + sub_opcode_base + loop_first_goto_opcode_rel_index);
                    int32_t loop_first_goto_jump_opcode_rel_index = opcode_array->length - sub_opcode_base;
                    loop_first_goto->operand0 = loop_first_goto_jump_opcode_rel_index;
                    
                    break;
                  }
                  case SPVM_OP_C_ID_CONDITION:
                  case SPVM_OP_C_ID_CONDITION_NOT:
                  {
                    
                    int32_t opcode_rel_index = opcode_array->length - sub_opcode_base;

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));

                    if (op_cur->id == SPVM_OP_C_ID_CONDITION) {
                      opcode.id = SPVM_OPCODE_C_ID_IF_EQ_ZERO;
                    }
                    else {
                      opcode.id = SPVM_OPCODE_C_ID_IF_NE_ZERO;
                    }
                    
                    if (op_cur->flag & SPVM_OP_C_FLAG_CONDITION_IF) {
                      SPVM_LIST_push(if_eq_or_if_ne_goto_opcode_rel_index_stack, (void*)(intptr_t)opcode_rel_index);
                    }
                    else if (op_cur->flag & SPVM_OP_C_FLAG_CONDITION_LOOP) {
                      assert(loop_first_goto_opcode_rel_index_stack->length > 0);
                      
                      int32_t loop_first_goto_opcode_rel_index = (intptr_t)SPVM_LIST_pop(loop_first_goto_opcode_rel_index_stack);
                      
                      opcode.operand0 = loop_first_goto_opcode_rel_index + 1;
                    }
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    
                    break;
                  }
                  case SPVM_OP_C_ID_MY: {
                    SPVM_MY* my = op_cur->uv.my;
                    
                    SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                    _Bool type_is_value_t = SPVM_TYPE_is_value_type(compiler, type);
                    
                    if (SPVM_TYPE_is_object_type(compiler, type) && !type_is_value_t) {
                      
                      SPVM_OPCODE opcode;
                      memset(&opcode, 0, sizeof(SPVM_OPCODE));
                      opcode.id = SPVM_OPCODE_C_ID_PUSH_MORTAL;
                      opcode.operand0 = my->var_id;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
                      int32_t my_var_id = my->var_id;
                      SPVM_LIST_push(mortal_stack, (void*)(intptr_t)my_var_id);
                      
                      if (mortal_stack->length > mortal_stack_max) {
                        mortal_stack_max = mortal_stack->length;
                      }
                      
                      SPVM_OP* op_block_current = SPVM_LIST_fetch(op_block_stack, op_block_stack->length - 1);
                      op_block_current->uv.block->have_object_var_decl = 1;
                    }
                    
                    break;
                  }
                  case SPVM_OP_C_ID_INC:
                  case SPVM_OP_C_ID_DEC:
                  {
                    SPVM_VAR* var = op_cur->first->uv.var;
                    SPVM_MY* my = var->op_my->uv.my;
                    
                    SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                    SPVM_OPCODE opcode;
                    assert(type->dimension == 0);
                    switch (type->basic_type->id) {
                      case SPVM_BASIC_TYPE_C_ID_BYTE:
                        opcode.id = SPVM_OPCODE_C_ID_INC_BYTE;
                        break;
                      case SPVM_BASIC_TYPE_C_ID_SHORT:
                        opcode.id = SPVM_OPCODE_C_ID_INC_SHORT;
                        break;
                      case SPVM_BASIC_TYPE_C_ID_INT:
                        opcode.id = SPVM_OPCODE_C_ID_INC_INT;
                        break;
                      case SPVM_BASIC_TYPE_C_ID_LONG:
                        opcode.id = SPVM_OPCODE_C_ID_INC_LONG;
                        break;
                      case SPVM_BASIC_TYPE_C_ID_FLOAT:
                        opcode.id = SPVM_OPCODE_C_ID_INC_FLOAT;
                        break;
                      case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                        opcode.id = SPVM_OPCODE_C_ID_INC_DOUBLE;
                        break;
                    }
                    opcode.operand0 = my->var_id;
                    
                    if (op_cur->id == SPVM_OP_C_ID_INC) {
                      opcode.operand1 = (int16_t)1;
                    }
                    else if (op_cur->id == SPVM_OP_C_ID_DEC) {
                      opcode.operand1 = (int16_t)-1;
                    }
                    else {
                      assert(0);
                    }
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    break;
                  }
                  case SPVM_OP_C_ID_GT: {
                    SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur->first);

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    
                    assert(type->dimension == 0);
                    switch (type->basic_type->id) {
                      case SPVM_BASIC_TYPE_C_ID_INT:
                        opcode.id = SPVM_OPCODE_C_ID_GT_INT;
                        break;
                      case SPVM_BASIC_TYPE_C_ID_LONG:
                        opcode.id = SPVM_OPCODE_C_ID_GT_LONG;
                        break;
                      case SPVM_BASIC_TYPE_C_ID_FLOAT:
                        opcode.id = SPVM_OPCODE_C_ID_GT_FLOAT;
                        break;
                      case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                        opcode.id = SPVM_OPCODE_C_ID_GT_DOUBLE;
                        break;
                      default:
                        assert(0);
                    }
                    
                    int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_cur->first);
                    int32_t var_id_in2 = SPVM_OP_get_my_var_id(compiler, op_cur->last);
                    
                    opcode.operand0 = var_id_in1;
                    opcode.operand1 = var_id_in2;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    
                    break;
                  }
                  case SPVM_OP_C_ID_GE: {

                    SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur->first);

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    
                    assert(type->dimension == 0);
                    switch (type->basic_type->id) {
                      case SPVM_BASIC_TYPE_C_ID_INT:
                        opcode.id = SPVM_OPCODE_C_ID_GE_INT;
                        break;
                      case SPVM_BASIC_TYPE_C_ID_LONG:
                        opcode.id = SPVM_OPCODE_C_ID_GE_LONG;
                        break;
                      case SPVM_BASIC_TYPE_C_ID_FLOAT:
                        opcode.id = SPVM_OPCODE_C_ID_GE_FLOAT;
                        break;
                      case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                        opcode.id = SPVM_OPCODE_C_ID_GE_DOUBLE;
                        break;
                      default:
                        assert(0);
                    }
                    
                    int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_cur->first);
                    int32_t var_id_in2 = SPVM_OP_get_my_var_id(compiler, op_cur->last);
                    
                    opcode.operand0 = var_id_in1;
                    opcode.operand1 = var_id_in2;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

                    break;
                  }
                  case  SPVM_OP_C_ID_LT: {
                    SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur->first);
                    
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    
                    assert(type->dimension == 0);
                    switch (type->basic_type->id) {
                      case SPVM_BASIC_TYPE_C_ID_INT:
                        opcode.id = SPVM_OPCODE_C_ID_LT_INT;
                        break;
                      case SPVM_BASIC_TYPE_C_ID_LONG:
                        opcode.id = SPVM_OPCODE_C_ID_LT_LONG;
                        break;
                      case SPVM_BASIC_TYPE_C_ID_FLOAT:
                        opcode.id = SPVM_OPCODE_C_ID_LT_FLOAT;
                        break;
                      case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                        opcode.id = SPVM_OPCODE_C_ID_LT_DOUBLE;
                        break;
                      default:
                        assert(0);
                    }
                    
                    int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_cur->first);
                    int32_t var_id_in2 = SPVM_OP_get_my_var_id(compiler, op_cur->last);
                    
                    opcode.operand0 = var_id_in1;
                    opcode.operand1 = var_id_in2;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    
                    break;
                  }
                  case SPVM_OP_C_ID_LE: {

                    SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur->first);

                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    
                    assert(type->dimension == 0);
                    switch (type->basic_type->id) {
                      case SPVM_BASIC_TYPE_C_ID_INT:
                        opcode.id = SPVM_OPCODE_C_ID_LE_INT;
                        break;
                      case SPVM_BASIC_TYPE_C_ID_LONG:
                        opcode.id = SPVM_OPCODE_C_ID_LE_LONG;
                        break;
                      case SPVM_BASIC_TYPE_C_ID_FLOAT:
                        opcode.id = SPVM_OPCODE_C_ID_LE_FLOAT;
                        break;
                      case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                        opcode.id = SPVM_OPCODE_C_ID_LE_DOUBLE;
                        break;
                      default:
                        assert(0);
                    }
                    
                    int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_cur->first);
                    int32_t var_id_in2 = SPVM_OP_get_my_var_id(compiler, op_cur->last);
                    
                    opcode.operand0 = var_id_in1;
                    opcode.operand1 = var_id_in2;

                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    
                    break;
                  }
                  case  SPVM_OP_C_ID_EQ: {
                    if (op_cur->first->id == SPVM_OP_C_ID_UNDEF || op_cur->last->id == SPVM_OP_C_ID_UNDEF) {
                      SPVM_OPCODE opcode;
                      memset(&opcode, 0, sizeof(SPVM_OPCODE));

                      opcode.id = SPVM_OPCODE_C_ID_IS_UNDEF;
                      if (op_cur->first->id == SPVM_OP_C_ID_UNDEF) {
                        int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_cur->last);
                        
                        opcode.operand0 = var_id_in;
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else {
                        int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_cur->first);
                        
                        opcode.operand0 = var_id_in;
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                    }
                    else {
                      
                      SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur->first);
                      
                      SPVM_OPCODE opcode;
                      memset(&opcode, 0, sizeof(SPVM_OPCODE));
                      
                      if (type->dimension == 0) {
                        if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                          assert(0);
                        }
                        else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT) {
                          assert(0);
                        }
                        else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
                          opcode.id = SPVM_OPCODE_C_ID_EQ_INT;
                        }
                        else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
                          opcode.id = SPVM_OPCODE_C_ID_EQ_LONG;
                        }
                        else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
                          opcode.id = SPVM_OPCODE_C_ID_EQ_FLOAT;
                        }
                        else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
                          opcode.id = SPVM_OPCODE_C_ID_EQ_DOUBLE;
                        }
                        else {
                          opcode.id = SPVM_OPCODE_C_ID_EQ_OBJECT;
                        }
                      }
                      else {
                        opcode.id = SPVM_OPCODE_C_ID_EQ_OBJECT;
                      }
                      
                      int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_cur->first);
                      int32_t var_id_in2 = SPVM_OP_get_my_var_id(compiler, op_cur->last);
                      
                      opcode.operand0 = var_id_in1;
                      opcode.operand1 = var_id_in2;
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    }
                    break;
                  }
                  case  SPVM_OP_C_ID_NE: {
                    
                    if (op_cur->first->id == SPVM_OP_C_ID_UNDEF || op_cur->last->id == SPVM_OP_C_ID_UNDEF) {
                      SPVM_OPCODE opcode;
                      memset(&opcode, 0, sizeof(SPVM_OPCODE));

                      opcode.id = SPVM_OPCODE_C_ID_IS_NOT_UNDEF;
                      if (op_cur->first->id == SPVM_OP_C_ID_UNDEF) {
                        int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_cur->last);
                        opcode.operand0 = var_id_in;
                      }
                      else {
                        int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_cur->first);
                        opcode.operand0 = var_id_in;
                      }
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    }
                    else {
                      SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur->first);

                      SPVM_OPCODE opcode;
                      memset(&opcode, 0, sizeof(SPVM_OPCODE));
                      
                      if (type->dimension == 0) {
                        if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                          assert(0);
                        }
                        else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT) {
                          assert(0);
                        }
                        else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
                          opcode.id = SPVM_OPCODE_C_ID_NE_INT;
                        }
                        else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
                          opcode.id = SPVM_OPCODE_C_ID_NE_LONG;
                        }
                        else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
                          opcode.id = SPVM_OPCODE_C_ID_NE_FLOAT;
                        }
                        else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
                          opcode.id = SPVM_OPCODE_C_ID_NE_DOUBLE;
                        }
                        else {
                          opcode.id = SPVM_OPCODE_C_ID_NE_OBJECT;
                        }
                      }
                      else {
                        opcode.id = SPVM_OPCODE_C_ID_NE_OBJECT;
                      }
                      int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_cur->first);
                      int32_t var_id_in2 = SPVM_OP_get_my_var_id(compiler, op_cur->last);
                      
                      opcode.operand0 = var_id_in1;
                      opcode.operand1 = var_id_in2;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    }
                    break;
                  }
                  case SPVM_OP_C_ID_ISA: {
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    
                    opcode.id = SPVM_OPCODE_C_ID_ISA;
                    
                    int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_cur->first);
                    SPVM_OP* op_type = op_cur->last;
                    SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_type);
                    
                    opcode.operand0 = var_id_in1;
                    opcode.operand1 = op_type->uv.type->sub_rel_id;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    
                    break;
                  }
                  case SPVM_OP_C_ID_STRING_EQ:
                  case SPVM_OP_C_ID_STRING_NE:
                  case SPVM_OP_C_ID_STRING_GT:
                  case SPVM_OP_C_ID_STRING_GE:
                  case SPVM_OP_C_ID_STRING_LT:
                  case SPVM_OP_C_ID_STRING_LE:
                  {
                    SPVM_OPCODE opcode;
                    memset(&opcode, 0, sizeof(SPVM_OPCODE));
                    
                    switch (op_cur->id) {
                      case SPVM_OP_C_ID_STRING_EQ:
                        opcode.id = SPVM_OPCODE_C_ID_STRING_EQ;
                        break;
                      case SPVM_OP_C_ID_STRING_NE:
                        opcode.id = SPVM_OPCODE_C_ID_STRING_NE;
                        break;
                      case SPVM_OP_C_ID_STRING_GT:
                        opcode.id = SPVM_OPCODE_C_ID_STRING_GT;
                        break;
                      case SPVM_OP_C_ID_STRING_GE:
                        opcode.id = SPVM_OPCODE_C_ID_STRING_GE;
                        break;
                      case SPVM_OP_C_ID_STRING_LT:
                        opcode.id = SPVM_OPCODE_C_ID_STRING_LE;
                        break;
                      case SPVM_OP_C_ID_STRING_LE:
                        opcode.id = SPVM_OPCODE_C_ID_STRING_LE;
                        break;
                      default:
                        assert(0);
                    }
                    
                    int32_t var_id_in1 = SPVM_OP_get_my_var_id(compiler, op_cur->first);
                    int32_t var_id_in2 = SPVM_OP_get_my_var_id(compiler, op_cur->last);
                    
                    opcode.operand0 = var_id_in1;
                    opcode.operand1 = var_id_in2;
                    
                    SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    
                    break;
                  }
                  case  SPVM_OP_C_ID_BOOL: {
                    SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur->first);
                    
                    if (op_cur->first->id != SPVM_OP_C_ID_IF) {

                      SPVM_OPCODE opcode;
                      memset(&opcode, 0, sizeof(SPVM_OPCODE));
                      
                      if (type->dimension == 0) {
                        if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                          assert(0);
                        }
                        else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT) {
                          assert(0);
                        }
                        else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
                          opcode.id = SPVM_OPCODE_C_ID_BOOL_INT;
                        }
                        else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
                          opcode.id = SPVM_OPCODE_C_ID_BOOL_LONG;
                        }
                        else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
                          opcode.id = SPVM_OPCODE_C_ID_BOOL_FLOAT;
                        }
                        else if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
                          opcode.id = SPVM_OPCODE_C_ID_BOOL_DOUBLE;
                        }
                        else {
                          opcode.id = SPVM_OPCODE_C_ID_BOOL_OBJECT;
                        }
                      }
                      else {
                        opcode.id = SPVM_OPCODE_C_ID_BOOL_OBJECT;
                      }

                      int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_cur->first);
                      
                      opcode.operand0 = var_id_in;

                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    }
                    
                    break;
                  }
                  case SPVM_OP_C_ID_CALL_SUB: {
                    
                    SPVM_CALL_SUB* call_sub = op_cur->uv.call_sub;
                    const char* call_sub_abs_name = call_sub->sub->abs_name;
                    
                    SPVM_OP* op_sub_call_sub = SPVM_HASH_fetch(compiler->op_sub_symtable, call_sub_abs_name, strlen(call_sub_abs_name));
                    SPVM_SUB* sub_call_sub = op_sub_call_sub->uv.sub;
                    
                    if (sub_call_sub->op_return_type->uv.type->dimension == 0 && sub_call_sub->op_return_type->uv.type->basic_type->id == SPVM_BASIC_TYPE_C_ID_VOID) {
                      int32_t first_arg_var_id = -1;

                      SPVM_OP* op_term_args = op_cur->last;
                      SPVM_OP* op_term_arg = op_term_args->first;

                      SPVM_LIST* op_args = sub_call_sub->op_args;
                      {
                        int32_t arg_index;
                        for (arg_index = 0; arg_index < sub_call_sub->op_args->length; arg_index++) {
                          SPVM_OP* op_arg = SPVM_LIST_fetch(op_args, arg_index);
                          SPVM_MY* my_arg = op_arg->uv.my;
                          
                          // Argument type
                          SPVM_TYPE* arg_type = SPVM_OP_get_type(compiler, op_arg);
                          
                          // Term argment type
                          op_term_arg = SPVM_OP_sibling(compiler, op_term_arg);
                          SPVM_TYPE* term_arg_type = SPVM_OP_get_type(compiler, op_term_arg);
                          
                          SPVM_OPCODE opcode;
                          memset(&opcode, 0, sizeof(SPVM_OPCODE));
                          
                          if (SPVM_TYPE_is_undef_type(compiler, term_arg_type)) {
                            assert(!sub_call_sub->op_package->uv.package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE);
                            opcode.id = SPVM_OPCODE_C_ID_PUSH_ARG_UNDEF;
                          }
                          else {
                            opcode.id = SPVM_OPCODE_C_ID_PUSH_ARG;

                            // Term of argument
                            int32_t var_id_arg = SPVM_OP_get_my_var_id(compiler, op_term_arg);
                            
                            opcode.operand0 = var_id_arg;
                            
                            if (arg_index == 0) {
                              first_arg_var_id = var_id_arg;
                            }
                          }
                          opcode.operand1 = SPVM_TYPE_get_width(compiler, arg_type);
                          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                          
                        }
                      }

                      // CALL_SUB opcode
                      SPVM_OPCODE opcode;
                      memset(&opcode, 0, sizeof(SPVM_OPCODE));
                      
                      if (sub_call_sub->op_package->uv.package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE) {
                        opcode.id = SPVM_OPCODE_C_ID_CALL_INTERFACE_METHOD;
                        opcode.operand1 = call_sub->sub_rel_id;
                        opcode.operand2 = first_arg_var_id;
                      }
                      else {
                        opcode.id = SPVM_OPCODE_C_ID_CALL_SUB;
                        opcode.operand1 = call_sub->sub_rel_id;
                      }
                      
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      
                      SPVM_OPCODE_BUILDER_push_if_croak(compiler, opcode_array, push_eval_opcode_rel_index_stack, if_croak_catch_goto_opcode_rel_index_stack, if_croak_return_goto_opcode_rel_index_stack, op_sub, op_cur->line);
                    }
                    
                    break;
                  }
                  case SPVM_OP_C_ID_RETURN: {
                    if (op_cur->first) {
                      SPVM_TYPE* return_type = SPVM_OP_get_type(compiler, op_cur->first);
                      
                      if (SPVM_TYPE_is_undef_type(compiler, return_type)) {
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        opcode.id = SPVM_OPCODE_C_ID_RETURN_UNDEF;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                      else {
                        SPVM_OPCODE opcode;
                        memset(&opcode, 0, sizeof(SPVM_OPCODE));
                        
                        if (sub->op_return_type->uv.type->dimension == 0) {
                          switch (sub->op_return_type->uv.type->basic_type->id) {
                            case SPVM_BASIC_TYPE_C_ID_BYTE:
                            case SPVM_BASIC_TYPE_C_ID_SHORT:
                            case SPVM_BASIC_TYPE_C_ID_INT:
                            case SPVM_BASIC_TYPE_C_ID_LONG:
                            case SPVM_BASIC_TYPE_C_ID_FLOAT:
                            case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                              SPVM_TYPE* sub_return_type = sub->op_return_type->uv.type;
                              opcode.id = SPVM_OPCODE_C_ID_RETURN;
                              break;
                            }
                            default: {
                              _Bool return_type_is_value_t = SPVM_TYPE_is_value_type(compiler, return_type);
                              if (return_type_is_value_t) {
                                opcode.id = SPVM_OPCODE_C_ID_RETURN;
                              }
                              else {
                                opcode.id = SPVM_OPCODE_C_ID_RETURN_OBJECT;
                              }
                            }
                          }
                        }
                        else {
                          opcode.id = SPVM_OPCODE_C_ID_RETURN_OBJECT;
                        }
                        
                        int32_t var_id_in = SPVM_OP_get_my_var_id(compiler, op_cur->first);
                        
                        opcode.operand0 = var_id_in;
                        
                        SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                      }
                    }
                    else {
                      SPVM_OPCODE opcode;
                      memset(&opcode, 0, sizeof(SPVM_OPCODE));
                      opcode.id = SPVM_OPCODE_C_ID_RETURN_VOID;
                      SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);
                    }
                    
                    int32_t return_opcode_rel_index = opcode_array->length - 1 - sub_opcode_base;
                    
                    SPVM_LIST_push(return_goto_opcode_rel_index_stack, (void*)(intptr_t)return_opcode_rel_index);
                    
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
          opcode.id = SPVM_OPCODE_C_ID_END_SUB;
          SPVM_OPCODE_ARRAY_push_opcode(compiler, opcode_array, &opcode);

          sub->opcode_length = opcode_array->length - sub->opcode_base;
          
          sub->mortal_stack_max = mortal_stack_max;
          
          // Free list
          SPVM_LIST_free(if_eq_or_if_ne_goto_opcode_rel_index_stack);
          SPVM_LIST_free(if_block_end_goto_opcode_rel_index_stack);
          SPVM_LIST_free(loop_first_goto_opcode_rel_index_stack);
          SPVM_LIST_free(last_goto_opcode_rel_index_stack);
          SPVM_LIST_free(next_goto_opcode_rel_index_stack);
          SPVM_LIST_free(push_eval_opcode_rel_index_stack);
          SPVM_LIST_free(if_croak_catch_goto_opcode_rel_index_stack);
          SPVM_LIST_free(if_croak_return_goto_opcode_rel_index_stack);
          SPVM_LIST_free(return_goto_opcode_rel_index_stack);
          SPVM_LIST_free(switch_info_stack);
          SPVM_LIST_free(op_block_stack);
          SPVM_LIST_free(mortal_stack);
          SPVM_LIST_free(mortal_top_stack);
        }
      }
    }
  }
#ifdef SPVM_DEBUG_DUMP
#include "spvm_dumper.h"
  printf("\n[OP codes]\n");
  SPVM_DUMPER_dump_packages_opcode_array(compiler, compiler->op_packages);
#endif
  
}
