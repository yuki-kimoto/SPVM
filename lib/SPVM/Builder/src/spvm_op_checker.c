#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <ctype.h>


#include "spvm_compiler.h"
#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_compiler_allocator.h"
#include "spvm_yacc_util.h"
#include "spvm_op.h"
#include "spvm_op_checker.h"
#include "spvm_sub.h"
#include "spvm_constant.h"
#include "spvm_field.h"
#include "spvm_my.h"
#include "spvm_var.h"
#include "spvm_enumeration_value.h"
#include "spvm_type.h"
#include "spvm_enumeration.h"
#include "spvm_package.h"
#include "spvm_field_access.h"
#include "spvm_call_sub.h"
#include "spvm_type.h"
#include "spvm_switch_info.h"
#include "spvm_limit.h"
#include "spvm_package_var.h"
#include "spvm_package_var_access.h"
#include "spvm_block.h"
#include "spvm_basic_type.h"
#include "spvm_case_info.h"
#include "spvm_array_field_access.h"

SPVM_OP* SPVM_OP_CHECKER_new_op_var_tmp(SPVM_COMPILER* compiler, SPVM_TYPE* type, const char* file, int32_t line) {

  // Temparary variable name
  char* name = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, strlen("@tmp2147483647") + 1);
  sprintf(name, "@tmp%d", compiler->tmp_var_length);
  compiler->tmp_var_length++;
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NAME, file, line);
  op_name->uv.name = name;
  SPVM_OP* op_var = SPVM_OP_build_var(compiler, op_name);
  SPVM_MY* my = SPVM_MY_new(compiler);
  SPVM_OP* op_my = SPVM_OP_new_op_my(compiler, my, file, line);
  SPVM_OP* op_type = NULL;
  if (type) {
    op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  }
  SPVM_OP_build_my(compiler, op_my, op_var, op_type);
  
  op_my->uv.my->is_tmp = 1;
  
  return op_var;
}

void SPVM_OP_CHECKER_apply_unary_string_convertion(SPVM_COMPILER* compiler, SPVM_OP* op_term) {
  
  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_term);
  
  SPVM_TYPE* dist_type;
  if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
    SPVM_OP* op_dist_type = SPVM_OP_new_op_string_type(compiler, op_term->file, op_term->line);
    dist_type = op_dist_type->uv.type;
  }
  else {
    return;
  }
  
  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term);
  
  SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, op_term->file, op_term->line);
  SPVM_OP* op_dist_type = SPVM_OP_new_op_type(compiler, dist_type, op_term->file, op_term->line);
  SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_term);
  
  SPVM_OP_replace_op(compiler, op_stab, op_convert);
}

void SPVM_OP_CHECKER_apply_unary_numeric_convertion(SPVM_COMPILER* compiler, SPVM_OP* op_term) {
  
  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_term);
  
  SPVM_TYPE* dist_type;
  if (type->dimension == 0 && type->basic_type->id <= SPVM_BASIC_TYPE_C_ID_INT) {
    SPVM_OP* op_dist_type = SPVM_OP_new_op_int_type(compiler, op_term->file, op_term->line);
    dist_type = op_dist_type->uv.type;
  }
  else {
    return;
  }
  
  if (!(type->basic_type->id == dist_type->basic_type->id && type->dimension == dist_type->dimension)) {
    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term);
    
    SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, op_term->file, op_term->line);
    SPVM_OP* op_dist_type = SPVM_OP_new_op_type(compiler, dist_type, op_term->file, op_term->line);
    SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_term);
    
    SPVM_OP_replace_op(compiler, op_stab, op_convert);
  }
}

void SPVM_OP_apply_binary_numeric_convertion(SPVM_COMPILER* compiler, SPVM_OP* op_first, SPVM_OP* op_last) {
  
  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_first);
  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_last);
  
  SPVM_TYPE* dist_type;
  if ((first_type->dimension == 0 && first_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) || (last_type->dimension == 0 && last_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE)) {
    SPVM_OP* op_dist_type = SPVM_OP_new_op_double_type(compiler, op_first->file, op_first->line);
    dist_type = op_dist_type->uv.type;
  }
  else if ((first_type->dimension == 0 && first_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) || (last_type->dimension == 0 && last_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT)) {
    SPVM_OP* op_dist_type = SPVM_OP_new_op_float_type(compiler, op_first->file, op_first->line);
    dist_type = op_dist_type->uv.type;
  }
  else if ((first_type->dimension == 0 && first_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) || (last_type->dimension == 0 && last_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG)) {
    SPVM_OP* op_dist_type = SPVM_OP_new_op_long_type(compiler, op_first->file, op_first->line);
    dist_type = op_dist_type->uv.type;
  }
  else {
    SPVM_OP* op_dist_type = SPVM_OP_new_op_int_type(compiler, op_first->file, op_first->line);
    dist_type = op_dist_type->uv.type;
  }
  
  if (!(first_type->basic_type->id == dist_type->basic_type->id && first_type->dimension == dist_type->dimension)) {
    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_first);
    
    SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, op_first->file, op_first->line);
    SPVM_OP* op_dist_type = SPVM_OP_new_op_type(compiler, dist_type, op_first->file, op_first->line);
    SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_first);
    
    SPVM_OP_replace_op(compiler, op_stab, op_convert);
  }
  
  if (!(last_type->basic_type->id == dist_type->basic_type->id && last_type->dimension == dist_type->dimension)) {
    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_last);
    
    SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, op_last->file, op_last->line);
    SPVM_OP* op_dist_type = SPVM_OP_new_op_type(compiler, dist_type, op_last->file, op_last->line);
    SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_last);
    SPVM_OP_replace_op(compiler, op_stab, op_convert);
  }
}

void SPVM_OP_CHECKER_check(SPVM_COMPILER* compiler) {
  
  // Resolve types
  SPVM_OP_CHECKER_resolve_types(compiler);
  if (compiler->error_count > 0) {
    return;
  }
  
  // Resolve basic types
  SPVM_OP_CHECKER_resolve_basic_types(compiler);
  
  // Resolve packages
  SPVM_OP_CHECKER_resolve_packages(compiler);
  if (compiler->error_count > 0) {
    return;
  }

  // Temporary buffer
  char tmp_buffer[UINT16_MAX];
  char tmp_buffer2[UINT16_MAX];
  
  // Check trees
  {
    int32_t package_index;
    for (package_index = 0; package_index < compiler->packages->length; package_index++) {
      SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_index);
      SPVM_LIST* subs = package->subs;
      {
        int32_t sub_index;
        for (sub_index = 0; sub_index < subs->length; sub_index++) {
          
          SPVM_SUB* sub = SPVM_LIST_fetch(subs, sub_index);
          SPVM_PACKAGE* package = sub->package;
          SPVM_TYPE* package_type = package->op_type->uv.type;
          
          // Destructor must receive own package object
          if (sub->flag & SPVM_SUB_C_FLAG_IS_DESTRUCTOR) {
            // DESTROY argument must be 0
            int32_t error = 0;
            if (sub->args->length != 1) {
              error = 1;
            }
            else {
              SPVM_MY* arg_my = SPVM_LIST_fetch(sub->args, 0);
              SPVM_TYPE* arg_type = SPVM_OP_get_type(compiler, arg_my->op_my);
              
              if (!(arg_type->basic_type->id == package_type->basic_type->id && arg_type->dimension == package_type->dimension)) {
                error = 1;
              }
            }
            
            if (error) {
              SPVM_yyerror_format(compiler, "DESTROY argument must be self\n", sub->op_sub->file, sub->op_sub->line);
            }
          }
          
          {
            int32_t arg_index;
            for (arg_index = 0 ; arg_index < sub->args->length; arg_index++) {
              SPVM_MY* arg_my = SPVM_LIST_fetch(sub->args, arg_index);
              SPVM_TYPE* arg_type = SPVM_OP_get_type(compiler, arg_my->op_my);
              if (SPVM_TYPE_is_object_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag)) {
                SPVM_LIST_push(sub->object_arg_ids, (void*)(intptr_t)arg_index);
              }
            }
          }
          
          if (package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE && (sub->op_block || sub->flag & SPVM_SUB_C_FLAG_HAVE_NATIVE_DESC)) {
            SPVM_yyerror_format(compiler, "Interface sub can't have implementation\n", sub->op_sub->file, sub->op_sub->line);
          }
          
          // Check subroutine - First tree traversal
          if (!(sub->flag & SPVM_SUB_C_FLAG_HAVE_NATIVE_DESC)) {
            // Eval block stack length
            int32_t eval_block_stack_length = 0;
            
            // Loop block stack length
            int32_t loop_block_stack_length = 0;
            
            // My stack
            SPVM_LIST* my_stack = SPVM_LIST_new(0);
            
            // Block my base stack
            SPVM_LIST* block_my_base_stack = SPVM_LIST_new(0);
            
            // Switch stack
            SPVM_LIST* op_switch_stack = SPVM_LIST_new(0);
            
            // Run OPs
            SPVM_OP* op_base = sub->op_block;
            SPVM_OP* op_cur = op_base;
            int32_t finish = 0;
            while (op_cur) {
              int32_t rel_line = op_cur->line - sub->op_sub->line;
              if (op_cur->line >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                SPVM_yyerror_format(compiler, "Too many lines at %s line %d\n", op_cur->file, op_cur->line);
              }
              
              // [START]Preorder traversal position
              if (!op_cur->no_need_check) {
                switch (op_cur->id) {
                  // Start scope
                  case SPVM_OP_C_ID_BLOCK: {
                    int32_t block_my_base = my_stack->length;
                    SPVM_LIST_push(block_my_base_stack, (void*)(intptr_t)block_my_base);
                    
                    if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_LOOP_STATEMENTS) {
                      loop_block_stack_length++;
                    }
                    else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_EVAL) {
                      // Eval block max length
                      eval_block_stack_length++;
                      if (eval_block_stack_length > sub->eval_stack_max_length) {
                        sub->eval_stack_max_length = eval_block_stack_length;
                      }
                    }
                    
                    break;
                  }
                  case SPVM_OP_C_ID_SWITCH: {
                    SPVM_LIST_push(op_switch_stack, op_cur);
                    break;
                  }
                }
              }
              // [END]Preorder traversal position
              
              if (op_cur->first) {
                op_cur = op_cur->first;
              }
              else {
                while (1) {
                  // [START]Postorder traversal position
                  if (!op_cur->no_need_check) {
                    switch (op_cur->id) {
                      case SPVM_OP_C_ID_ARRAY_INIT: {
                        SPVM_OP* op_array_init = op_cur;
                        
                        SPVM_OP* op_list_elements = op_cur->first;
                        SPVM_OP* op_type_new_default = op_cur->last;
                        
                        const char* file = op_list_elements->file;
                        int32_t line = op_list_elements->line;
                        
                        SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, file, line);

                        SPVM_OP* op_type_new = NULL;
                        SPVM_OP* op_type_element = NULL;
                        
                        if (op_type_new_default->id == SPVM_OP_C_ID_TYPE) {
                          op_type_new = op_type_new_default;
                          
                          // Create element type
                          SPVM_TYPE* type_element = SPVM_TYPE_new(compiler);
                          type_element->basic_type = op_type_new->uv.type->basic_type;
                          type_element->dimension = op_type_new->uv.type->dimension - 1;
                          type_element->flag = op_type_new->uv.type->flag;
                          op_type_element = SPVM_OP_new_op_type(compiler, type_element, op_type_new_default->file, op_type_new_default->line);
                        }
                        
                        SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, file, line);
                        SPVM_OP* op_assign_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, file, line);
                        SPVM_OP* op_var_tmp_new = SPVM_OP_CHECKER_new_op_var_tmp(compiler, NULL, file, line);
                        SPVM_LIST_push(sub->op_sub->uv.sub->mys, op_var_tmp_new->uv.var->my);
                        SPVM_LIST_push(my_stack, op_var_tmp_new->uv.var->my);
                        
                        SPVM_OP_build_assign(compiler, op_assign_new, op_var_tmp_new, op_new);

                        SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_assign_new);
                        
                        int32_t length;
                        {
                          SPVM_OP* op_term_element = op_list_elements->first;
                          int32_t index = 0;
                          while ((op_term_element = SPVM_OP_sibling(compiler, op_term_element))) {
                            if (index == 0) {
                              
                              if (op_term_element->id == SPVM_OP_C_ID_UNDEF) {
                                SPVM_yyerror_format(compiler, "Array initialization first element must not be undef at %s line %d\n", file, line);
                              }

                              SPVM_TYPE* type_term_element = SPVM_OP_get_type(compiler, op_term_element);
                              
                              op_term_element->no_need_check = 1;

                              // Create element type
                              if (op_type_element == NULL) {
                                SPVM_TYPE* type_element = SPVM_TYPE_new(compiler);
                                type_element->basic_type = type_term_element->basic_type;
                                type_element->dimension = type_term_element->dimension;
                                if (type_term_element->flag & SPVM_TYPE_C_FLAG_CONST) {
                                  type_element->flag |= SPVM_TYPE_C_FLAG_CONST;
                                }
                                op_type_element = SPVM_OP_new_op_type(compiler, type_element, file, line);
                              }
                              
                              if (!SPVM_TYPE_is_numeric_type(compiler, op_type_element->uv.type->basic_type->id,op_type_element->uv.type->dimension, op_type_element->uv.type->flag)) {
                                {
                                  SPVM_OP* op_type_tmp = op_type_element;
                                  op_type_tmp->uv.type->info_constant_id = package->info_types->length;
                                  SPVM_LIST_push(package->info_types, op_type_tmp->uv.type);
                                  if (package->info_types->length > SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                                    SPVM_yyerror_format(compiler, "Too many types at %s line %d\n", op_type_tmp->file, op_type_tmp->line);
                                  }
                                }
                              }
                                                      
                              // Create array type
                              if (op_type_new == NULL) {
                                SPVM_TYPE* type_new = SPVM_TYPE_new(compiler);
                                type_new->basic_type = type_term_element->basic_type;
                                type_new->dimension = type_term_element->dimension + 1;
                                if (type_term_element->flag & SPVM_TYPE_C_FLAG_CONST) {
                                  type_new->flag |= SPVM_TYPE_C_FLAG_CONST;
                                }
                                op_type_new = SPVM_OP_new_op_type(compiler, type_new, file, line);
                              }

                              if (!SPVM_TYPE_is_numeric_type(compiler, op_type_new->uv.type->basic_type->id, op_type_new->uv.type->dimension, op_type_new->uv.type->flag)) {
                                {
                                  SPVM_OP* op_type_tmp = op_type_new;
                                  op_type_tmp->uv.type->info_constant_id = package->info_types->length;
                                  SPVM_LIST_push(package->info_types, op_type_tmp->uv.type);
                                  if (package->info_types->length > SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                                    SPVM_yyerror_format(compiler, "Too many types at %s line %d\n", op_type_tmp->file, op_type_tmp->line);
                                  }
                                }
                              }
                              
                              op_var_tmp_new->uv.var->my->type = op_type_new->uv.type;
                            }
                            
                            SPVM_OP* op_assign_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, file, line);
                            SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term_element);
                            
                            SPVM_OP* op_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_ACCESS, file, line);

                            SPVM_OP* op_var_tmp_array_access = SPVM_OP_new_op_var_clone(compiler, op_var_tmp_new, op_var_tmp_new->file, op_var_tmp_new->line);
                            SPVM_OP_insert_child(compiler, op_array_access, op_array_access->last, op_var_tmp_array_access);

                            SPVM_OP* op_constant_index = SPVM_OP_new_op_constant_int(compiler, index, file, line);
                            SPVM_OP_insert_child(compiler, op_array_access, op_array_access->last, op_constant_index);
                            
                            SPVM_OP_build_assign(compiler, op_assign_array_access, op_array_access, op_term_element);
                            
                            SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_assign_array_access);
                            
                            index++;
                            op_term_element = op_stab;
                          }
                          length = index;
                        }
                        
                        SPVM_OP_insert_child(compiler, op_new, op_new->last, op_type_new);
                        SPVM_OP_insert_child(compiler, op_type_new, op_type_new->last, op_type_element);

                        SPVM_OP* op_constant_length = SPVM_OP_new_op_constant_int(compiler, length, file, line);
                        SPVM_OP_insert_child(compiler, op_type_new, op_type_new->last, op_constant_length);
                        
                        SPVM_OP* op_var_tmp_ret = SPVM_OP_new_op_var_clone(compiler, op_var_tmp_new, op_var_tmp_new->file, op_var_tmp_new->line);
                        
                        SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_var_tmp_ret);

                        if (length == 0) {
                          SPVM_yyerror_format(compiler, "Array initialization need at least one element at %s line %d\n", file, line);
                        }
                        
                        SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                        
                        SPVM_OP_replace_op(compiler, op_stab, op_sequence);
                        
                        op_array_init->first = op_sequence;
                        
                        op_cur = op_sequence->first;
                        
                        break;
                      }
                      case SPVM_OP_C_ID_NEXT: {
                        if (loop_block_stack_length == 0) {
                          SPVM_yyerror_format(compiler, "next statement must be in loop block at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        break;
                      }
                      case SPVM_OP_C_ID_LAST: {
                        if (loop_block_stack_length == 0 && op_switch_stack->length == 0) {
                          SPVM_yyerror_format(compiler, "last statement must be in loop block or switch block at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        break;
                      }
                      case SPVM_OP_C_ID_CONSTANT: {
                        SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                        
                        int32_t add_constant = 0;
                        
                        // long or double
                        if (type->dimension == 0) {
                          switch (type->basic_type->id) {
                            case SPVM_BASIC_TYPE_C_ID_LONG: {
                              add_constant = 1;

                              // Add long constant
                              char long_value_string[sizeof(int64_t)];
                              memcpy(long_value_string, &op_cur->uv.constant->value.lval, sizeof(int64_t));
                              int32_t found_long_constant_id_plus1 = (intptr_t)SPVM_HASH_fetch(package->info_long_constant_symtable, long_value_string, sizeof(int64_t));
                              if (found_long_constant_id_plus1 > 0) {
                                op_cur->uv.constant->info_long_constant_id = found_long_constant_id_plus1 - 1;
                              }
                              else {
                                op_cur->uv.constant->info_long_constant_id = package->info_long_constants->length;
                                SPVM_LIST_push(package->info_long_constants, (void*)(intptr_t)op_cur->uv.constant);
                                int32_t info_long_constant_id_plus1 = op_cur->uv.constant->info_long_constant_id + 1;
                                SPVM_HASH_insert(package->info_long_constant_symtable, long_value_string, sizeof(int64_t), (void*)(intptr_t)info_long_constant_id_plus1);
                              }
                              if (package->info_long_constants->length > SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                                SPVM_yyerror_format(compiler, "Too many package variable access at %s line %d\n", op_cur->file, op_cur->line);
                              }
                              
                            }
                            case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                              add_constant = 1;
                              
                              // Add double constant
                              char double_value_string[sizeof(double)];
                              memcpy(double_value_string, &op_cur->uv.constant->value.lval, sizeof(double));
                              int32_t found_double_constant_id_plus1 = (intptr_t)SPVM_HASH_fetch(package->info_double_constant_symtable, double_value_string, sizeof(double));
                              if (found_double_constant_id_plus1 > 0) {
                                op_cur->uv.constant->info_double_constant_id = found_double_constant_id_plus1 - 1;
                              }
                              else {
                                op_cur->uv.constant->info_double_constant_id = package->info_double_constants->length;
                                SPVM_LIST_push(package->info_double_constants, (void*)(intptr_t)op_cur->uv.constant);
                                int32_t info_double_constant_id_plus1 = op_cur->uv.constant->info_double_constant_id + 1;
                                SPVM_HASH_insert(package->info_double_constant_symtable, double_value_string, sizeof(double), (void*)(intptr_t)info_double_constant_id_plus1);
                              }
                              if (package->info_double_constants->length > SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                                SPVM_yyerror_format(compiler, "Too many package variable access at %s line %d\n", op_cur->file, op_cur->line);
                              }
                            }
                          }
                        }
                        // String
                        else if (SPVM_TYPE_is_string_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                          add_constant = 1;
                          
                          char* string_value_string = op_cur->uv.constant->value.oval;
                          int32_t string_length = op_cur->uv.constant->string_length;
                          int32_t found_string_constant_id_plus1 = (intptr_t)SPVM_HASH_fetch(package->info_string_constant_symtable, string_value_string, string_length);
                          if (found_string_constant_id_plus1 > 0) {
                            op_cur->uv.constant->info_string_constant_id = found_string_constant_id_plus1 - 1;
                          }
                          else {
                            op_cur->uv.constant->info_string_constant_id = package->info_string_constants->length;
                            SPVM_LIST_push(package->info_string_constants, (void*)(intptr_t)op_cur->uv.constant);
                            int32_t info_string_constant_id_plus1 = op_cur->uv.constant->info_string_constant_id + 1;
                            SPVM_HASH_insert(package->info_string_constant_symtable, string_value_string, string_length, (void*)(intptr_t)info_string_constant_id_plus1);
                          }
                          if (package->info_string_constants->length > SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                            SPVM_yyerror_format(compiler, "Too many package variable access at %s line %d\n", op_cur->file, op_cur->line);
                          }
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_SWITCH: {
                        
                        SPVM_OP* op_switch_condition = op_cur->first;
                        
                        SPVM_TYPE* term_type = SPVM_OP_get_type(compiler, op_switch_condition->first);
                        
                        // Check type
                        if (!term_type || !(term_type->dimension == 0 && term_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT)) {
                          SPVM_yyerror_format(compiler, "Switch condition must be int value at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        SPVM_SWITCH_INFO* switch_info = op_cur->uv.switch_info;
                        SPVM_LIST* cases = switch_info->cases;
                        int32_t length = cases->length;
                        
                        // Check case type
                        {
                          int32_t i;
                          for (i = 0; i < length; i++) {
                            SPVM_CASE_INFO* case_info = SPVM_LIST_fetch(cases, i);
                            SPVM_OP* op_constant = case_info->op_case_info->first;
                            SPVM_CONSTANT* constant = op_constant->uv.constant;

                            if (op_constant->id != SPVM_OP_C_ID_CONSTANT) {
                              SPVM_yyerror_format(compiler, "case value must be constant at %s line %d\n", op_cur->file, op_cur->line);
                            }
                            
                            SPVM_TYPE* case_value_type = SPVM_OP_get_type(compiler, op_constant);
                            if (!(case_value_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT && case_value_type->dimension == 0)) {
                              SPVM_yyerror_format(compiler, "case value must be int constant at %s line %d\n", case_info->op_case_info->file, case_info->op_case_info->line);
                            }
                            case_info->constant = constant;
                          }
                        }
                        
                        switch_info->id = SPVM_SWITCH_INFO_C_ID_LOOKUP_SWITCH;
                        
                        SPVM_LIST_pop(op_switch_stack);

                        if (package->info_switch_infos->length >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                          SPVM_yyerror_format(compiler, "Too many switch at %s line %d\n", op_cur->file, op_cur->line);
                        }
                        op_cur->uv.switch_info->info_constant_id = package->info_switch_infos->length;
                        SPVM_LIST_push(package->info_switch_infos, op_cur->uv.switch_info);
                        
                        break;
                      }
                      case SPVM_OP_C_ID_CASE: {
                        if (op_switch_stack->length > 0) {
                          SPVM_OP* op_switch = SPVM_LIST_fetch(op_switch_stack, op_switch_stack->length - 1);
                          SPVM_SWITCH_INFO* switch_info = op_switch->uv.switch_info;
                          op_cur->uv.case_info->index = switch_info->cases->length;
                          SPVM_LIST_push(switch_info->cases, op_cur->uv.case_info);
                        }
                        break;
                      }
                      case SPVM_OP_C_ID_DEFAULT: {
                        if (op_switch_stack->length > 0) {
                          SPVM_OP* op_switch = SPVM_LIST_fetch(op_switch_stack, op_switch_stack->length - 1);
                          SPVM_SWITCH_INFO* switch_info = op_switch->uv.switch_info;
                          
                          if (switch_info->op_default) {
                            SPVM_yyerror_format(compiler, "Duplicate default statement at %s line %d\n", op_cur->file, op_cur->line);
                          }
                          else {
                            switch_info->op_default = op_cur;
                          }
                        }
                        break;
                      }
                      case SPVM_OP_C_ID_BOOL: {
                        SPVM_OP* op_first = op_cur->first;
                        
                        // undef
                        if (op_first->id == SPVM_OP_C_ID_UNDEF) {
                          
                          SPVM_OP* op_false = SPVM_OP_new_op_constant_int(compiler, 0, op_first->file, op_first->line);
                          
                          SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_first);
                          
                          SPVM_OP_replace_op(compiler, op_stab, op_false);
                          
                          op_cur = op_false;
                        }
                        else {
                          if (op_first->id == SPVM_OP_C_ID_IF) {
                            // OK
                          }
                          else {
                            SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_first);
                            
                            // Numeric or object
                            if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag) || SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag))
                            {
                              // OK
                            }
                            else {
                              SPVM_yyerror_format(compiler, "Invalid boolean type at %s line %d\n", op_cur->file, op_cur->line);
                            }
                          }
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_EQ: {
                        SPVM_OP* op_first = op_cur->first;
                        SPVM_OP* op_last = op_cur->last;
                        
                        // undef == undef
                        if (op_first->id == SPVM_OP_C_ID_UNDEF && op_last->id == SPVM_OP_C_ID_UNDEF) {
                          
                          SPVM_OP* op_true = SPVM_OP_new_op_constant_int(compiler, 1, op_first->file, op_first->line);
                          SPVM_OP* op_bool = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BOOL, op_first->file, op_first->line);
                          
                          SPVM_OP_insert_child(compiler, op_bool, op_bool->last, op_true);
                          
                          SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                          
                          SPVM_OP_replace_op(compiler, op_stab, op_bool);
                          
                          op_cur = op_true;
                        }
                        // term == term
                        else if (op_first->id != SPVM_OP_C_ID_UNDEF && op_last->id != SPVM_OP_C_ID_UNDEF) {
                          SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                          SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                          
                          // numeric == numeric
                          if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                            SPVM_OP_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
                          }
                          // object == object
                          else if (SPVM_TYPE_is_object_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_object_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                            // OK
                          }
                          else {
                            SPVM_yyerror_format(compiler, "Invalid == comparison at %s line %d\n", op_cur->file, op_cur->line);
                          }
                        }
                        // term == undef
                        else if (op_first->id != SPVM_OP_C_ID_UNDEF && op_last->id == SPVM_OP_C_ID_UNDEF) {
                          SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                          if (!SPVM_TYPE_is_object_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                            SPVM_yyerror_format(compiler, "== left value must be object at %s line %d\n", op_cur->file, op_cur->line);
                          }
                        }
                        // undef == term
                        else if (op_first->id == SPVM_OP_C_ID_UNDEF && op_last->id != SPVM_OP_C_ID_UNDEF) {
                          SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                          if (!SPVM_TYPE_is_object_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                            SPVM_yyerror_format(compiler, "== right value must be object at %s line %d\n", op_cur->file, op_cur->line);
                          }
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_NE: {
                        SPVM_OP* op_first = op_cur->first;
                        SPVM_OP* op_last = op_cur->last;

                        // undef != undef
                        if (op_first->id == SPVM_OP_C_ID_UNDEF && op_last->id == SPVM_OP_C_ID_UNDEF) {
                          
                          SPVM_OP* op_false = SPVM_OP_new_op_constant_int(compiler, 0, op_first->file, op_first->line);
                          SPVM_OP* op_bool = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BOOL, op_first->file, op_first->line);
                          
                          SPVM_OP_insert_child(compiler, op_bool, op_bool->last, op_false);
                          
                          SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                          
                          SPVM_OP_replace_op(compiler, op_stab, op_bool);
                          
                          op_cur = op_false;
                        }
                        // term != term
                        else if (op_first->id != SPVM_OP_C_ID_UNDEF && op_last->id != SPVM_OP_C_ID_UNDEF) {
                          SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                          SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

                          // numeric != numeric
                          if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                            SPVM_OP_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
                          }
                          // numeric != object
                          else if (SPVM_TYPE_is_object_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_object_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                            // OK
                          }
                          else {
                            SPVM_yyerror_format(compiler, "Invalid != comparison at %s line %d\n", op_cur->file, op_cur->line);
                          }
                        }
                        // term != undef
                        else if (op_first->id != SPVM_OP_C_ID_UNDEF && op_last->id == SPVM_OP_C_ID_UNDEF) {
                          SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);

                          if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                            SPVM_yyerror_format(compiler, "!= left value must be object at %s line %d\n", op_cur->file, op_cur->line);
                          }
                        }
                        // undef != term
                        else if (op_first->id == SPVM_OP_C_ID_UNDEF && op_last->id != SPVM_OP_C_ID_UNDEF) {
                          SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

                          if (SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                            SPVM_yyerror_format(compiler, "!= right value must be object at %s line %d\n", op_cur->file, op_cur->line);
                          }
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_LT: {

                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_OP_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
                        }
                        else {
                          SPVM_yyerror_format(compiler, "Invalid < comparison at %s line %d\n", op_cur->file, op_cur->line);
                        }

                        break;
                      }
                      case SPVM_OP_C_ID_LE: {

                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

                        if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_OP_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
                        }
                        else {
                          SPVM_yyerror_format(compiler, "Invalid <= comparison at %s line %d\n", op_cur->file, op_cur->line);
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_GT: {

                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

                        if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_OP_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
                        }
                        else {
                          SPVM_yyerror_format(compiler, "Invalid > comparison at %s line %d\n", op_cur->file, op_cur->line);
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_GE: {

                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

                        if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_OP_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
                        }
                        else {
                          SPVM_yyerror_format(compiler, "Invalid <= comparison at %s line %d\n", op_cur->file, op_cur->line);
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_LEFT_SHIFT: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        // Can receive only numeric type
                        if (SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_OP_CHECKER_apply_unary_numeric_convertion(compiler, op_cur->first);
                        }
                        else {
                          SPVM_yyerror_format(compiler, "<< operator left value must be integral at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        if (SPVM_TYPE_is_integral_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_OP_CHECKER_apply_unary_numeric_convertion(compiler, op_cur->last);
                          
                          if (last_type->dimension == 0 && last_type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_LONG) {
                            SPVM_yyerror_format(compiler, "<< operator right value must be int at %s line %d\n", op_cur->file, op_cur->line);
                            
                            return;
                          }
                        }
                        else {
                          SPVM_yyerror_format(compiler, "<< operator right value must be int at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_RIGHT_SHIFT: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        // Can receive only numeric type
                        if (SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_OP_CHECKER_apply_unary_numeric_convertion(compiler, op_cur->first);
                        }
                        else {
                          SPVM_yyerror_format(compiler, ">> operator left value must be integral at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        if (SPVM_TYPE_is_integral_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_OP_CHECKER_apply_unary_numeric_convertion(compiler, op_cur->last);
                          
                          if (last_type->dimension == 0 && last_type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_LONG) {
                            SPVM_yyerror_format(compiler, ">> operator right value must be int at %s line %d\n", op_cur->file, op_cur->line);
                            
                            return;
                          }
                        }
                        else {
                          SPVM_yyerror_format(compiler, ">> operator right value must be int at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_RIGHT_SHIFT_UNSIGNED: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        // Can receive only numeric type
                        if (SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_OP_CHECKER_apply_unary_numeric_convertion(compiler, op_cur->first);
                        }
                        else {
                          SPVM_yyerror_format(compiler, ">>> operator left value must be integral at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        if (SPVM_TYPE_is_integral_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_OP_CHECKER_apply_unary_numeric_convertion(compiler, op_cur->last);
                          
                          if (last_type->dimension == 0 && last_type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_LONG) {
                            SPVM_yyerror_format(compiler, ">>> operator right value must be int at %s line %d\n", op_cur->file, op_cur->line);
                            
                            return;
                          }
                        }
                        else {
                          SPVM_yyerror_format(compiler, ">>> operator right value must be int at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_NEW: {
                        assert(op_cur->first);
                              
                        if (op_cur->first->id == SPVM_OP_C_ID_TYPE) {
                          SPVM_PACKAGE* new_package = op_cur->first->uv.type->basic_type->package;
                          
                          if (new_package && new_package->flag & SPVM_PACKAGE_C_FLAG_IS_HAS_ONLY_ANON_SUB) {
                            SPVM_OP* op_type = op_cur->first;
                          
                            SPVM_SUB* anon_sub = SPVM_LIST_fetch(new_package->subs, 0);
                            if (anon_sub->captures->length) {
                              // [Before]
                              // NEW
                              //   TYPE
                              // [After]
                              // SEQUENCE
                              //   ASSIGN_NEW
                              //     NEW
                              //       TYPE
                              //     VAR_TMP_NEW
                              // ASSIGN_FIELD_ACCESS1
                              //   VAR_CAPTURE1
                              //   FIELD_ACCESS1
                              //     VAR_TMP_NEW1
                              //     NAME_FIELD1
                              // ASSIGN_FIELD_ACCESS2
                              //   VAR_CAPTURE2
                              //   FIELD_ACCESS2
                              //     VAR_TMP_NEW2
                              //     NAME_FIELD2
                              // VAR_TMP_NEW_RET
                            
                              const char* file = op_cur->file;
                              int32_t line = op_cur->line;
                              
                              SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                              
                              SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, file, line);
                              SPVM_OP* op_assign_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, file, line);
                              SPVM_OP* op_var_tmp_new = SPVM_OP_CHECKER_new_op_var_tmp(compiler, NULL, file, line);
                              SPVM_LIST_push(sub->op_sub->uv.sub->mys, op_var_tmp_new->uv.var->my);
                              SPVM_LIST_push(my_stack, op_var_tmp_new->uv.var->my);
                              
                              SPVM_OP_build_assign(compiler, op_assign_new, op_var_tmp_new, op_cur);

                              SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_assign_new);
                              
                              // Check capture variable exists
                              for (int32_t caputre_index = 0; caputre_index < anon_sub->captures->length; caputre_index++) {
                                SPVM_MY* capture_my = SPVM_LIST_fetch(anon_sub->captures, caputre_index);
                                const char* capture_name = capture_my->op_name->uv.name;

                                // Search same name variable
                                SPVM_MY* found_my = NULL;
                                for (int32_t stack_my_index = my_stack->length - 1; stack_my_index >= 0; stack_my_index--) {
                                  SPVM_MY* my = SPVM_LIST_fetch(my_stack, stack_my_index);
                                  if (strcmp(capture_name, my->op_name->uv.name) == 0) {
                                    found_my = my;
                                    break;
                                  }
                                }
                                if (!found_my) {
                                  SPVM_yyerror_format(compiler, "Capture variable \"%s\" is not declared at %s line %d\n", capture_name, op_cur->file, op_cur->line);
                                  break;
                                }
                                
                                // Create field assignment
                                SPVM_OP* op_name_invoker = SPVM_OP_new_op_name(compiler, op_var_tmp_new->uv.var->op_name->uv.name , op_cur->file, op_cur->line);
                                SPVM_OP* op_term_invoker = SPVM_OP_new_op_var(compiler, op_name_invoker);
                                op_term_invoker->uv.var->my = found_my;
                                SPVM_OP* op_name_field = SPVM_OP_new_op_name(compiler, found_my->op_name->uv.name + 1, op_cur->file, op_cur->line);
                                SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, op_term_invoker, op_name_field);
                                
                                SPVM_OP* op_name_var_capture = SPVM_OP_new_op_name(compiler, found_my->op_name->uv.name, op_cur->file, op_cur->line);
                                SPVM_OP* op_var_capture = SPVM_OP_new_op_var(compiler, op_name_var_capture);
                                op_var_capture->uv.var->my = found_my;

                                SPVM_FIELD* capture_field = SPVM_HASH_fetch(new_package->field_symtable, found_my->op_name->uv.name + 1, strlen(found_my->op_name->uv.name) - 1);
                                op_field_access->uv.field_access->field = capture_field;
                                
                                SPVM_OP* op_assign_field_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                                SPVM_OP_build_assign(compiler, op_assign_field_access, op_field_access, op_var_capture);
                                
                                SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_assign_field_access);
                              }
                              
                              SPVM_OP* op_var_tmp_ret = SPVM_OP_new_op_var_clone(compiler, op_var_tmp_new, op_var_tmp_new->file, op_var_tmp_new->line);
                              
                              SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_var_tmp_ret);
                              
                              SPVM_OP_replace_op(compiler, op_stab, op_sequence);
                              
                              op_cur = op_sequence->first;
                              
                              {
                                SPVM_OP* op_type_tmp = op_type;
                                op_type_tmp->uv.type->info_constant_id = package->info_types->length;
                                SPVM_LIST_push(package->info_types, op_type_tmp->uv.type);
                                if (package->info_types->length > SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                                  SPVM_yyerror_format(compiler, "Too many types at %s line %d\n", op_type_tmp->file, op_type_tmp->line);
                                }
                              }
                              
                              continue;
                            }
                          }
                          
                          SPVM_OP* op_type = op_cur->first;
                          
                          SPVM_TYPE* type = op_type->uv.type;
                          
                          // Array
                          if (SPVM_TYPE_is_array_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            
                            SPVM_OP* op_index_term = op_type->last;

                            SPVM_TYPE* index_type = SPVM_OP_get_type(compiler, op_index_term);
                            
                            assert(index_type);
                            if (SPVM_TYPE_is_numeric_type(compiler, index_type->basic_type->id, index_type->dimension, index_type->flag)) {
                              SPVM_OP_CHECKER_apply_unary_numeric_convertion(compiler, op_index_term);
                              
                              SPVM_TYPE* index_type = SPVM_OP_get_type(compiler, op_index_term);
                              
                              if (!(index_type->dimension == 0 && index_type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_BYTE && index_type->basic_type->id <= SPVM_BASIC_TYPE_C_ID_INT)) {
                                char* type_name = tmp_buffer;
                                SPVM_TYPE_sprint_type_name(compiler, type_name, type->basic_type->id, type->dimension, type->flag);
                                SPVM_yyerror_format(compiler, "new operator can't create array which don't have int length \"%s\" at %s line %d\n", type_name, op_cur->file, op_cur->line);
                                return;
                              }
                            }
                            else {
                              char* type_name = tmp_buffer;
                              SPVM_TYPE_sprint_type_name(compiler, type_name, type->basic_type->id, type->dimension, type->flag);
                              SPVM_yyerror_format(compiler, "new operator can't create array which don't have numeric length \"%s\" at %s line %d\n", type_name, op_cur->file, op_cur->line);
                              return;
                            }
                          }
                          // Numeric type
                          else if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_yyerror_format(compiler, "new operator can't receive numeric type at %s line %d\n", op_cur->file, op_cur->line);
                          }
                          // Object type
                          else if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, type->basic_type->name, strlen(type->basic_type->name));
                            
                            if (package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE) {
                              SPVM_yyerror_format(compiler, "Can't create object of interface package at %s line %d\n", op_cur->file, op_cur->line);
                            }
                            else if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE_T) {
                              SPVM_yyerror_format(compiler, "Can't create object of value_t package at %s line %d\n", op_cur->file, op_cur->line);
                            }
                            else if (package->flag & SPVM_PACKAGE_C_FLAG_IS_POINTER) {
                              SPVM_yyerror_format(compiler, "Can't create object of struct package at %s line %d\n", op_cur->file, op_cur->line);
                            }
                            else if (package->flag & SPVM_PACKAGE_C_FLAG_IS_PRIVATE) {
                              if (strcmp(package->op_name->uv.name, sub->package->op_name->uv.name) != 0) {
                                SPVM_yyerror_format(compiler, "Can't create object of private package at %s line %d\n", op_cur->file, op_cur->line);
                              }
                            }
                          }
                          else {
                            assert(0);
                          }
                          
                          if (!SPVM_TYPE_is_numeric_type(compiler, op_type->uv.type->basic_type->id, op_type->uv.type->dimension, op_type->uv.type->flag)) {
                            {
                              SPVM_OP* op_type_tmp = op_type;
                              op_type_tmp->uv.type->info_constant_id = package->info_types->length;
                              SPVM_LIST_push(package->info_types, op_type_tmp->uv.type);
                              if (package->info_types->length > SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                                SPVM_yyerror_format(compiler, "Too many types at %s line %d\n", op_type_tmp->file, op_type_tmp->line);
                              }
                            }
                          }
                        }
                        else if (op_cur->first->id == SPVM_OP_C_ID_CONSTANT) {
                          // Constant string
                        }
                        else {
                          assert(0);
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_BIT_XOR: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        // Can receive only integral type
                        if (!SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) || !SPVM_TYPE_is_integral_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_yyerror_format(compiler,
                            "^ operator can receive only integral type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        SPVM_OP_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
                        
                        break;
                      }
                      case SPVM_OP_C_ID_BIT_OR: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        // Can receive only integral type
                        if (!SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) || !SPVM_TYPE_is_integral_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_yyerror_format(compiler,
                            "| operator can receive only integral type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        
                        SPVM_OP_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
                        
                        break;
                      }
                      case SPVM_OP_C_ID_BIT_AND: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        // Can receive only integral type
                        if (!SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) || !SPVM_TYPE_is_integral_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_yyerror_format(compiler,
                            "& operator can receive only integral type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        SPVM_OP_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
                        
                        break;
                      }
                      case SPVM_OP_C_ID_ISA: {
                        SPVM_TYPE* term_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_OP* op_type = op_cur->last;
                        
                        // Left term must be object type
                        if (!SPVM_TYPE_is_object_type(compiler, term_type->basic_type->id, term_type->dimension, term_type->flag)) {
                          SPVM_yyerror_format(compiler, "isa left value must be object type at %s line %d\n", op_cur->file, op_cur->line);
                        }
                        
                        // Right type must be object type
                        if (SPVM_TYPE_is_object_type(compiler, op_type->uv.type->basic_type->id, op_type->uv.type->dimension, op_type->uv.type->flag)) {
                          // Right type must be not any object type
                          if (SPVM_TYPE_is_any_object_type(compiler, op_type->uv.type->basic_type->id, op_type->uv.type->dimension, op_type->uv.type->flag)) {
                            SPVM_yyerror_format(compiler, "isa rigth type must be not any object type at %s line %d\n", op_cur->file, op_cur->line);
                          }
                        }
                        else {
                          SPVM_yyerror_format(compiler, "isa rigth type must be object type at %s line %d\n", op_cur->file, op_cur->line);
                        }

                        if (!SPVM_TYPE_is_numeric_type(compiler, op_type->uv.type->basic_type->id, op_type->uv.type->dimension, op_type->uv.type->flag)) {

                          {
                            SPVM_OP* op_type_tmp = op_type;
                            op_type_tmp->uv.type->info_constant_id = package->info_types->length;
                            SPVM_LIST_push(package->info_types, op_type_tmp->uv.type);
                            if (package->info_types->length > SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                              SPVM_yyerror_format(compiler, "Too many types at %s line %d\n", op_type_tmp->file, op_type_tmp->line);
                            }
                          }
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_STRING_EQ: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        // undef check
                        if (!first_type) {
                          SPVM_yyerror_format(compiler, "eq left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        if (!last_type) {
                          SPVM_yyerror_format(compiler, "eq right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        
                        // Can receive only numeric type
                        if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "eq left type must be string at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        if (!SPVM_TYPE_is_string_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_yyerror_format(compiler, "eq right type must be string at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_STRING_NE: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        // undef check
                        if (!first_type) {
                          SPVM_yyerror_format(compiler, "ne left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        if (!last_type) {
                          SPVM_yyerror_format(compiler, "ne right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        
                        // Can receive only numeric type
                        if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "ne left type must be string at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        if (!SPVM_TYPE_is_string_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_yyerror_format(compiler, "ne right type must be string at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_STRING_GT: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        // undef check
                        if (!first_type) {
                          SPVM_yyerror_format(compiler, "gt left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        if (!last_type) {
                          SPVM_yyerror_format(compiler, "gt right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        
                        // Can receive only numeric type
                        if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "gt left type must be string at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        if (!SPVM_TYPE_is_string_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_yyerror_format(compiler, "gt right type must be string at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_STRING_GE: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        // undef check
                        if (!first_type) {
                          SPVM_yyerror_format(compiler, "ge left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        if (!last_type) {
                          SPVM_yyerror_format(compiler, "ge right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        
                        // Can receive only numeric type
                        if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "ge left type must be string at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        if (!SPVM_TYPE_is_string_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_yyerror_format(compiler, "ge right type must be string at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_STRING_LT: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        // undef check
                        if (!first_type) {
                          SPVM_yyerror_format(compiler, "lt left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        if (!last_type) {
                          SPVM_yyerror_format(compiler, "lt right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        
                        // Can receive only numeric type
                        if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "lt left type must be string at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        if (!SPVM_TYPE_is_string_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_yyerror_format(compiler, "lt right type must be string at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_STRING_LE: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        // undef check
                        if (!first_type) {
                          SPVM_yyerror_format(compiler, "le left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        if (!last_type) {
                          SPVM_yyerror_format(compiler, "le right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        
                        // Can receive only numeric type
                        if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "le left type must be string at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        if (!SPVM_TYPE_is_string_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_yyerror_format(compiler, "le right type must be string at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_ARRAY_LENGTH: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        
                        // First value must be array
                        if (!SPVM_TYPE_is_array_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "right of @ or len must be array at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_PRE_INC:
                      {
                        SPVM_OP* op_first = op_cur->first;
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_first);
                        
                        // Numeric type
                        if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "increment operand must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        // Convert PRE_INC
                        // [before]
                        // PRE_INC
                        //   TERM_MUTABLE
                        // 
                        // [after]
                        // ASSIGN
                        //   ADD
                        //     TERM_MUTABLE
                        //     CONST 1
                        //   TERM_MUTABLE_CLONE
                        SPVM_OP* op_term_mutable = op_cur->first;
                        
                        op_term_mutable->no_need_check = 1;

                        SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                        SPVM_OP_cut_op(compiler, op_term_mutable);
                        
                        SPVM_OP* op_term_mutable_clone = SPVM_OP_new_op_term_mutable_clone(compiler, op_term_mutable);
                        
                        SPVM_OP* op_add = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, op_cur->file, op_cur->line);
                        SPVM_OP* op_constant = SPVM_OP_new_op_constant_int(compiler, 1, op_cur->file, op_cur->line);
                        SPVM_OP_build_binop(compiler, op_add, op_term_mutable, op_constant);
                        
                        SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                        
                        SPVM_TYPE* term_mutable_type = SPVM_OP_get_type(compiler, op_term_mutable);
                        if (SPVM_TYPE_is_byte_type(compiler, term_mutable_type->basic_type->id, term_mutable_type->dimension, term_mutable_type->flag)
                          || SPVM_TYPE_is_short_type(compiler, term_mutable_type->basic_type->id, term_mutable_type->dimension, term_mutable_type->flag))
                        {
                          SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, op_cur->file, op_cur->line);
                          SPVM_OP* op_convert_type = SPVM_OP_new_op_type(compiler, term_mutable_type, op_cur->file, op_cur->line);
                          SPVM_OP_build_convert(compiler, op_convert, op_convert_type, op_add);
                          SPVM_OP_build_assign(compiler, op_assign, op_term_mutable_clone, op_convert);
                        }
                        else {
                          SPVM_OP_build_assign(compiler, op_assign, op_term_mutable_clone, op_add);
                        }
                        
                        SPVM_OP_replace_op(compiler, op_stab, op_assign);
                        
                        op_cur = op_term_mutable;
                        
                        break;
                      }
                      case SPVM_OP_C_ID_PRE_DEC:
                      {
                        SPVM_OP* op_first = op_cur->first;
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_first);
                        
                        // Numeric type
                        if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "decrement operand must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        // Convert PRE_DEC
                        // [before]
                        // PRE_DEC
                        //   TERM_MUTABLE
                        // 
                        // [after]
                        // ASSIGN
                        //   SUBTRACT
                        //     TERM_MUTABLE
                        //     CONST 1
                        //   TERM_MUTABLE_CLONE
                        SPVM_OP* op_term_mutable = op_cur->first;
                        
                        op_term_mutable->no_need_check = 1;

                        SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                        SPVM_OP_cut_op(compiler, op_term_mutable);
                        
                        SPVM_OP* op_term_mutable_clone = SPVM_OP_new_op_term_mutable_clone(compiler, op_term_mutable);
                        
                        SPVM_OP* op_subtract = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, op_cur->file, op_cur->line);
                        SPVM_OP* op_constant = SPVM_OP_new_op_constant_int(compiler, 1, op_cur->file, op_cur->line);
                        SPVM_OP_build_binop(compiler, op_subtract, op_term_mutable, op_constant);
                        
                        SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                        
                        SPVM_TYPE* term_mutable_type = SPVM_OP_get_type(compiler, op_term_mutable);
                        if (SPVM_TYPE_is_byte_type(compiler, term_mutable_type->basic_type->id, term_mutable_type->dimension, term_mutable_type->flag)
                          || SPVM_TYPE_is_short_type(compiler, term_mutable_type->basic_type->id, term_mutable_type->dimension, term_mutable_type->flag))
                        {
                          SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, op_cur->file, op_cur->line);
                          SPVM_OP* op_convert_type = SPVM_OP_new_op_type(compiler, term_mutable_type, op_cur->file, op_cur->line);
                          SPVM_OP_build_convert(compiler, op_convert, op_convert_type, op_subtract);
                          SPVM_OP_build_assign(compiler, op_assign, op_term_mutable_clone, op_convert);
                        }
                        else {
                          SPVM_OP_build_assign(compiler, op_assign, op_term_mutable_clone, op_subtract);
                        }
                        
                        SPVM_OP_replace_op(compiler, op_stab, op_assign);
                        
                        op_cur = op_term_mutable;
                        
                        break;
                      }
                      case SPVM_OP_C_ID_POST_INC:
                      {
                        SPVM_OP* op_first = op_cur->first;
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_first);
                        
                        // Numeric type
                        if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "increment operand must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }

                        // Convert POST_INC
                        // [before]
                        // POST_INC
                        //   TERM_MUTABLE
                        // 
                        // [after]
                        // SEQUENCE
                        //   ASSIGN_TMP
                        //     TERM_MUTABLE
                        //     VAR_TMP1
                        //   ASSIGN_ADD
                        //     ADD
                        //       VAR_TMP2
                        //       CONST 1
                        //     TERM_MUTABLE_CLONE
                        //   VAR_TMP3
                        
                        SPVM_OP* op_term_mutable = op_cur->first;

                        op_term_mutable->no_need_check = 1;

                        SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                        SPVM_OP_cut_op(compiler, op_term_mutable);

                        SPVM_TYPE* term_mutable_type = SPVM_OP_get_type(compiler, op_term_mutable);
                        
                        SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, op_cur->file, op_cur->line);
                        SPVM_OP* op_var_tmp1 = SPVM_OP_CHECKER_new_op_var_tmp(compiler, term_mutable_type, op_cur->file, op_cur->line);
                        SPVM_LIST_push(sub->op_sub->uv.sub->mys, op_var_tmp1->uv.var->my);
                        SPVM_LIST_push(my_stack, op_var_tmp1->uv.var->my);

                        SPVM_OP* op_var_tmp2 = SPVM_OP_new_op_var_clone(compiler, op_var_tmp1, op_cur->file, op_cur->line);
                  
                        SPVM_OP* op_assign_tmp = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                        SPVM_OP_build_assign(compiler, op_assign_tmp, op_var_tmp1, op_term_mutable);

                        SPVM_OP* op_add = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, op_cur->file, op_cur->line);
                        SPVM_OP* op_constant = SPVM_OP_new_op_constant_int(compiler, 1, op_cur->file, op_cur->line);
                        SPVM_OP_build_binop(compiler, op_add, op_var_tmp2, op_constant);
                        SPVM_OP* op_assign_add = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                        
                        SPVM_OP* op_term_mutable_clone = SPVM_OP_new_op_term_mutable_clone(compiler, op_term_mutable);
                        if (SPVM_TYPE_is_byte_type(compiler, term_mutable_type->basic_type->id, term_mutable_type->dimension, term_mutable_type->flag)
                          || SPVM_TYPE_is_short_type(compiler, term_mutable_type->basic_type->id, term_mutable_type->dimension, term_mutable_type->flag))
                        {
                          SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, op_cur->file, op_cur->line);
                          SPVM_OP* op_convert_type = SPVM_OP_new_op_type(compiler, term_mutable_type, op_cur->file, op_cur->line);
                          SPVM_OP_build_convert(compiler, op_convert, op_convert_type, op_add);
                          SPVM_OP_build_assign(compiler, op_assign_add, op_term_mutable_clone, op_convert);
                        }
                        else {
                          SPVM_OP_build_assign(compiler, op_assign_add, op_term_mutable_clone, op_add);
                        }

                        SPVM_OP* op_var_tmp3 = SPVM_OP_new_op_var_clone(compiler, op_var_tmp1, op_cur->file, op_cur->line);
                        SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_assign_tmp);
                        SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_assign_add);
                        SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_var_tmp3);
                        
                        SPVM_OP_replace_op(compiler, op_stab, op_sequence);
                        
                        op_cur = op_term_mutable;
                        
                        
                        break;
                      }
                      case SPVM_OP_C_ID_POST_DEC:
                      {
                        SPVM_OP* op_first = op_cur->first;
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_first);
                        
                        // Numeric type
                        if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "decrement operand must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }

                        // Convert POST_DEC
                        // [before]
                        // POST_DEC
                        //   TERM_MUTABLE
                        // 
                        // [after]
                        // SEQUENCE
                        //   ASSIGN_TMP
                        //     TERM_MUTABLE
                        //     VAR_TMP1
                        //   ASSIGN_ADD
                        //     SUBTRACT
                        //       VAR_TMP2
                        //       CONST 1
                        //     TERM_MUTABLE_CLONE
                        //   VAR_TMP3
                        
                        SPVM_OP* op_term_mutable = op_cur->first;

                        op_term_mutable->no_need_check = 1;

                        SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                        SPVM_OP_cut_op(compiler, op_term_mutable);

                        SPVM_TYPE* term_mutable_type = SPVM_OP_get_type(compiler, op_term_mutable);
                        
                        SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, op_cur->file, op_cur->line);
                        
                        SPVM_OP* op_var_tmp1 = SPVM_OP_CHECKER_new_op_var_tmp(compiler, term_mutable_type, op_cur->file, op_cur->line);
                        SPVM_LIST_push(sub->op_sub->uv.sub->mys, op_var_tmp1->uv.var->my);
                        SPVM_LIST_push(my_stack, op_var_tmp1->uv.var->my);
                        
                        SPVM_OP* op_var_tmp2 = SPVM_OP_new_op_var_clone(compiler, op_var_tmp1, op_cur->file, op_cur->line);
                  
                        SPVM_OP* op_assign_tmp = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                        SPVM_OP_build_assign(compiler, op_assign_tmp, op_var_tmp1, op_term_mutable);

                        SPVM_OP* op_subtract = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, op_cur->file, op_cur->line);
                        SPVM_OP* op_constant = SPVM_OP_new_op_constant_int(compiler, 1, op_cur->file, op_cur->line);
                        SPVM_OP_build_binop(compiler, op_subtract, op_var_tmp2, op_constant);
                        SPVM_OP* op_assign_subtract = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                        
                        SPVM_OP* op_term_mutable_clone = SPVM_OP_new_op_term_mutable_clone(compiler, op_term_mutable);
                        if (SPVM_TYPE_is_byte_type(compiler, term_mutable_type->basic_type->id, term_mutable_type->dimension, term_mutable_type->flag)
                          || SPVM_TYPE_is_short_type(compiler, term_mutable_type->basic_type->id, term_mutable_type->dimension, term_mutable_type->flag))
                        {
                          SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, op_cur->file, op_cur->line);
                          SPVM_OP* op_convert_type = SPVM_OP_new_op_type(compiler, term_mutable_type, op_cur->file, op_cur->line);
                          SPVM_OP_build_convert(compiler, op_convert, op_convert_type, op_subtract);
                          SPVM_OP_build_assign(compiler, op_assign_subtract, op_term_mutable_clone, op_convert);
                        }
                        else {
                          SPVM_OP_build_assign(compiler, op_assign_subtract, op_term_mutable_clone, op_subtract);
                        }

                        SPVM_OP* op_var_tmp3 = SPVM_OP_new_op_var_clone(compiler, op_var_tmp1, op_cur->file, op_cur->line);
                        SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_assign_tmp);
                        SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_assign_subtract);
                        SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_var_tmp3);
                        
                        SPVM_OP_replace_op(compiler, op_stab, op_sequence);
                        
                        op_cur = op_term_mutable;
                        
                        break;
                      }
                      case SPVM_OP_C_ID_SPECIAL_ASSIGN: {
                        SPVM_OP* op_term_src = op_cur->first;
                        SPVM_OP* op_term_mutable = op_cur->last;
                        
                        // Convert SPECIAL_ASSIGN
                        // [before]
                        // SPECIAL_ASSIGN
                        //   TERM_SRC
                        //   TERM_MUTABLE
                        // [after]
                        // ASSIGN
                        //   CULC
                        //     TERM_MUTABLE
                        //     TERM_SRC
                        //   TERM_MUTABLE_CLONE
                        
                        op_term_mutable->no_need_check = 1;
                        op_term_src->no_need_check = 1;

                        SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                        SPVM_OP_cut_op(compiler, op_term_mutable);
                        SPVM_OP_cut_op(compiler, op_term_src);
                        
                        SPVM_OP* op_term_mutable_clone = SPVM_OP_new_op_term_mutable_clone(compiler, op_term_mutable);
                        op_term_mutable_clone->is_lvalue = 1;
                        
                        int32_t culc_op_id;
                        switch (op_cur->flag) {
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_ADD:
                            culc_op_id = SPVM_OP_C_ID_ADD;
                            break;
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_SUBTRACT:
                            culc_op_id = SPVM_OP_C_ID_SUBTRACT;
                            break;
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_MULTIPLY:
                            culc_op_id = SPVM_OP_C_ID_MULTIPLY;
                            break;
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_DIVIDE:
                            culc_op_id = SPVM_OP_C_ID_DIVIDE;
                            break;
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_REMAINDER:
                            culc_op_id = SPVM_OP_C_ID_REMAINDER;
                            break;
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_LEFT_SHIFT:
                            culc_op_id = SPVM_OP_C_ID_LEFT_SHIFT;
                            break;
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_SHIFT:
                            culc_op_id = SPVM_OP_C_ID_RIGHT_SHIFT;
                            break;
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_SHIFT_UNSIGNED:
                            culc_op_id = SPVM_OP_C_ID_RIGHT_SHIFT_UNSIGNED;
                            break;
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_XOR:
                            culc_op_id = SPVM_OP_C_ID_BIT_XOR;
                            break;
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_OR:
                            culc_op_id = SPVM_OP_C_ID_BIT_OR;
                            break;
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_AND:
                            culc_op_id = SPVM_OP_C_ID_BIT_AND;
                            break;
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_CONCAT:
                            culc_op_id = SPVM_OP_C_ID_CONCAT;
                            break;
                          default:
                            assert(0);
                            break;
                        }
                        
                        SPVM_OP* op_culc = SPVM_OP_new_op(compiler, culc_op_id, op_cur->file, op_cur->line);
                        
                        SPVM_OP_build_binop(compiler, op_culc, op_term_mutable, op_term_src);
                        
                        SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                        
                        SPVM_TYPE* term_mutable_type = SPVM_OP_get_type(compiler, op_term_mutable);
                        SPVM_TYPE* term_src_type = SPVM_OP_get_type(compiler, op_term_src);
                        
                        int32_t need_conversion = 0;
                        switch (op_cur->flag) {
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_ADD:
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_SUBTRACT:
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_MULTIPLY:
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_DIVIDE:
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_REMAINDER:
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_XOR:
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_OR:
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_AND:
                            if (SPVM_TYPE_is_numeric_type(compiler, term_src_type->basic_type->id, term_src_type->dimension, term_src_type->flag)) {
                              if (SPVM_TYPE_is_numeric_type(compiler, term_mutable_type->basic_type->id, term_mutable_type->dimension, term_mutable_type->flag)) {
                                if (term_src_type->basic_type->id > term_mutable_type->basic_type->id) {
                                  need_conversion = 1;
                                }
                              }
                            }
                            
                            break;

                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_LEFT_SHIFT:
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_SHIFT:
                          case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_SHIFT_UNSIGNED:
                            if (SPVM_TYPE_is_byte_type(compiler, term_mutable_type->basic_type->id, term_mutable_type->dimension, term_mutable_type->flag)
                              || SPVM_TYPE_is_short_type(compiler, term_mutable_type->basic_type->id, term_mutable_type->dimension, term_mutable_type->flag))
                            {
                              need_conversion = 1;
                            }
                            break;
                        }
                        
                        if (need_conversion) {
                          SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, op_cur->file, op_cur->line);
                          SPVM_OP* op_convert_type = SPVM_OP_new_op_type(compiler, term_mutable_type, op_cur->file, op_cur->line);
                          SPVM_OP_build_convert(compiler, op_convert, op_convert_type, op_culc);
                          SPVM_OP_build_assign(compiler, op_assign, op_term_mutable_clone, op_convert);
                        }
                        else {
                          SPVM_OP_build_assign(compiler, op_assign, op_term_mutable_clone, op_culc);
                        }
                        
                        SPVM_OP_replace_op(compiler, op_stab, op_assign);
                        
                        op_cur = op_term_mutable;
                        
                        break;
                      }
                      case SPVM_OP_C_ID_ASSIGN: {
                        SPVM_OP* op_term_dist = op_cur->last;
                        SPVM_OP* op_term_src = op_cur->first;
                        
                        SPVM_TYPE* dist_type = SPVM_OP_get_type(compiler, op_term_dist);
                        SPVM_TYPE* src_type = SPVM_OP_get_type(compiler, op_term_src);

                        // Type inference
                        if (op_term_dist->id == SPVM_OP_C_ID_VAR) {
                          SPVM_MY* my = op_term_dist->uv.var->my;
                          if (my->type == NULL) {
                            my->type = SPVM_OP_get_type(compiler, op_term_src);
                          }
                          if (my->type == NULL) {
                            SPVM_yyerror_format(compiler, "Type can't be detected at %s line %d\n", my->op_my->file, my->op_my->line);
                            return;
                          }
                        }
                        
                        // Check if source can be assigned to dist
                        // If needed, numeric convertion op is added
                        SPVM_OP_CHECKER_check_assign(compiler, op_term_dist, op_term_src);
                        
                        break;
                      }
                      case SPVM_OP_C_ID_RETURN: {
                        
                        SPVM_OP* op_term = op_cur->first;
                        
                        if (op_term) {
                          SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_term);
                          SPVM_TYPE* sub_return_type = SPVM_OP_get_type(compiler, sub->return_type->op_type);
                          
                          int32_t is_invalid = 0;
                          
                          // Can't return refernece type
                          if (SPVM_TYPE_is_ref_type(compiler, sub_return_type->basic_type->id, sub_return_type->dimension, sub_return_type->flag)) {
                            SPVM_yyerror_format(compiler, "Can't return reference type at %s line %d\n", op_cur->file, op_cur->line);
                          }
                          
                          // Undef
                          if (op_term->id == SPVM_OP_C_ID_UNDEF) {
                            if (sub->return_type->dimension == 0 && sub->return_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_VOID) {
                              is_invalid = 1;
                            }
                            else {
                              if (SPVM_TYPE_is_numeric_type(compiler, sub_return_type->basic_type->id, sub_return_type->dimension, sub_return_type->flag)) {
                                is_invalid = 1;
                              }
                            }
                          }
                          else if (op_term->id == SPVM_OP_C_ID_CALL_SUB) {
                            SPVM_CALL_SUB* call_sub = op_term->uv.call_sub;
                            SPVM_SUB* sub = call_sub->sub;
                            if (sub->return_type->dimension == 0 && sub->return_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_VOID) {
                              SPVM_yyerror_format(compiler, "Can't return value of void subroutine at %s line %d\n", op_cur->file, op_cur->line);
                            }
                          }
                          // Normal
                          else if (op_term) {
                            if (!(first_type->basic_type->id == sub_return_type->basic_type->id && first_type->dimension == sub_return_type->dimension)) {
                              is_invalid = 1;
                            }
                          }
                          // Empty
                          else {
                            if (!(sub->return_type->dimension == 0 && sub->return_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_VOID)) {
                              is_invalid = 1;
                            }
                          }
                          
                          if (is_invalid) {
                            SPVM_yyerror_format(compiler, "Invalid return type at %s line %d\n", op_cur->file, op_cur->line);
                            
                            return;
                          }
                        }
                        break;
                      }
                      case SPVM_OP_C_ID_NEGATE: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        
                        // Must be numeric type
                        if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "- operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        SPVM_OP_CHECKER_apply_unary_numeric_convertion(compiler, op_cur->first);
                        
                        break;
                      }
                      case SPVM_OP_C_ID_COMPLEMENT: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        
                        // Must be numeric type
                        if (!SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "~ operator right value must be integral type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }

                        SPVM_OP_CHECKER_apply_unary_numeric_convertion(compiler, op_cur->first);
                        
                        break;
                      }
                      case SPVM_OP_C_ID_PLUS: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        
                        // Must be numeric type
                        if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "+ operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }

                        SPVM_OP_CHECKER_apply_unary_numeric_convertion(compiler, op_cur->first);
                        
                        break;
                      }
                      case SPVM_OP_C_ID_ADD: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        // Left value must not be undef
                        if (!first_type) {
                          SPVM_yyerror_format(compiler, "+ operator left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        // Right value must not be undef
                        if (!last_type) {
                          SPVM_yyerror_format(compiler, "+ operator right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }

                        // Left value must not be object type
                        if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "+ operator left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }

                        // Right value must not be object type
                        if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_yyerror_format(compiler, "+ operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        // Upgrade type
                        SPVM_OP_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
                                                        
                        break;
                      }
                      case SPVM_OP_C_ID_SUBTRACT: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        // Left value must not be undef
                        if (!first_type) {
                          SPVM_yyerror_format(compiler, "- operator left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        // Right value Must not be undef
                        if (!last_type) {
                          SPVM_yyerror_format(compiler, "- operator right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }

                        // Left value must not be object type
                        if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "- operator left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }

                        // Right value must not be object type
                        if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_yyerror_format(compiler, "- operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        // Upgrade type
                        SPVM_OP_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
                        
                        break;
                      }
                      case SPVM_OP_C_ID_MULTIPLY: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        // Left value must not be undef
                        if (!first_type) {
                          SPVM_yyerror_format(compiler, "* operator left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        // Right value Must not be undef
                        if (!last_type) {
                          SPVM_yyerror_format(compiler, "* operator right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        // Left value must not be object type
                        if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "* operator left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }

                        // Right value must not be object type
                        if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_yyerror_format(compiler, "* operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }

                        // Upgrade type
                        SPVM_OP_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
                        
                        break;
                      }
                      case SPVM_OP_C_ID_DIVIDE: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        // Left value must not be undef
                        if (!first_type) {
                          SPVM_yyerror_format(compiler, "/ operator left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        // Right value Must not be undef
                        if (!last_type) {
                          SPVM_yyerror_format(compiler, "/ operator right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }

                        // Left value must not be object type
                        if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "/ operator left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }

                        // Right value must not be object type
                        if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_yyerror_format(compiler, "/ operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        // Upgrade type
                        SPVM_OP_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);

                        break;
                      }
                      case SPVM_OP_C_ID_REMAINDER: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        // Left value must not be undef
                        if (!first_type) {
                          SPVM_yyerror_format(compiler, "%% operator left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        // Right value Must not be undef
                        if (!last_type) {
                          SPVM_yyerror_format(compiler, "%% operator right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }

                        // Left value must not be object type
                        if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "%% operator left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }

                        // Right value must not be object type
                        if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_yyerror_format(compiler, "%% operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        // Upgrade type
                        SPVM_OP_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
                                                        
                        break;
                      }
                      case SPVM_OP_C_ID_CONCAT: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        // Left type is numeric type
                        if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_OP_CHECKER_apply_unary_string_convertion(compiler, op_cur->first);
                        }
                        // Left type is not string type
                        else if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "\".\" operator left value must be string at %s line %d\n", op_cur->file, op_cur->line);
                        }
                        
                        // Right value is numeric type
                        if (SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_OP_CHECKER_apply_unary_string_convertion(compiler, op_cur->last);
                        }
                        // Right value is not string type
                        else if (!SPVM_TYPE_is_string_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_yyerror_format(compiler, "\".\" operator right value must be string at %s line %d\n", op_cur->file, op_cur->line);
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_CROAK: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "croak argument must be string at %s line %d\n", op_cur->file, op_cur->line);
                        }
                        break;
                      }
                      // End of scope
                      case SPVM_OP_C_ID_BLOCK: {
                        // Pop block my variable base
                        assert(block_my_base_stack->length > 0);
                        int32_t block_my_base = (intptr_t)SPVM_LIST_pop(block_my_base_stack);
                          
                        int32_t my_stack_pop_count = my_stack->length - block_my_base;
                        
                        {
                          int32_t i;
                          for (i = 0; i < my_stack_pop_count; i++) {
                            SPVM_LIST_pop(my_stack);
                          }
                        }

                        // Pop loop block my variable base
                        if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_LOOP_STATEMENTS) {
                          loop_block_stack_length--;
                        }
                        // Pop try block my variable base
                        else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_EVAL) {
                          eval_block_stack_length--;
                        }

                        
                        break;
                      }
                      case SPVM_OP_C_ID_REF: {
                        
                        SPVM_OP* op_var = op_cur->first;
                        SPVM_TYPE* var_type = SPVM_OP_get_type(compiler, op_var);
                        if (!(SPVM_TYPE_is_numeric_type(compiler, var_type->basic_type->id, var_type->dimension, var_type->flag) || SPVM_TYPE_is_value_type(compiler, var_type->basic_type->id, var_type->dimension, var_type->flag))) {
                          SPVM_yyerror_format(compiler, "Refernece target must be numeric type or value type at %s line %d\n", op_cur->file, op_cur->line);
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_DEREF: {
                        SPVM_OP* op_var = op_cur->first;
                        SPVM_TYPE* var_type = SPVM_OP_get_type(compiler, op_var);
                        
                        if (!(SPVM_TYPE_is_numeric_ref_type(compiler, var_type->basic_type->id, var_type->dimension, var_type->flag) || SPVM_TYPE_is_value_ref_type(compiler, var_type->basic_type->id, var_type->dimension, var_type->flag))) {
                          SPVM_yyerror_format(compiler, "Dereference target must be numeric reference type or value reference type at %s line %d\n", op_cur->file, op_cur->line);
                        }
                        
                        break;
                      }
                      // Add my var
                      case SPVM_OP_C_ID_VAR: {
                        
                        if (op_cur->uv.var->is_declaration) {
                          
                          SPVM_MY* my = op_cur->uv.var->my;
                          
                          // Redeclaration error if same name variable is declare in same block
                          int32_t found = 0;
                          int32_t block_my_base = (intptr_t)SPVM_LIST_fetch(block_my_base_stack, block_my_base_stack->length - 1);
                          {
                            int32_t i;
                            for (i = block_my_base; i < my_stack->length; i++) {
                              SPVM_MY* bef_my = SPVM_LIST_fetch(my_stack, i);
                              if (strcmp(my->op_name->uv.name, bef_my->op_name->uv.name) == 0) {
                                // Temporaly variable is not duplicated
                                if (my->op_name->uv.name[0] != '@') {
                                  found = 1;
                                }
                                break;
                              }
                            }
                          }
                          
                          if (found) {
                            SPVM_yyerror_format(compiler, "redeclaration of my \"%s\" at %s line %d\n", my->op_name->uv.name, my->op_my->file, my->op_my->line);
                            
                            return;
                          }
                          else {
                            if (!my->is_tmp) {
                              SPVM_LIST_push(sub->mys, my);
                              SPVM_LIST_push(my_stack, my);
                            }
                          }
                          
                          // Type can't be detected
                          if (!op_cur->is_lvalue && my->type == NULL) {
                            SPVM_yyerror_format(compiler, "Type can't be detected at %s line %d\n", my->op_my->file, my->op_my->line);
                            
                            return;
                          }
                        }
                        
                        SPVM_VAR* var = op_cur->uv.var;
                        
                        // Search same name variable
                        SPVM_MY* found_my = NULL;
                        {
                          int32_t i;
                          for (i = my_stack->length - 1; i >= 0; i--) {
                            SPVM_MY* my = SPVM_LIST_fetch(my_stack, i);
                            assert(my);
                            if (strcmp(var->op_name->uv.name, my->op_name->uv.name) == 0) {
                              found_my = my;
                              break;
                            }
                          }
                        }
                        
                        if (found_my) {
                          // Add my var information to var
                          var->my = found_my;
                        }
                        else {
                          // Variable is capture var
                          int32_t is_capture_var;
                          SPVM_FIELD* found_capture_field = SPVM_HASH_fetch(package->field_symtable, var->op_name->uv.name + 1, strlen(var->op_name->uv.name) - 1);
                          if (found_capture_field && found_capture_field->is_captured) {
                            
                            // Capture var is converted to field access
                            SPVM_MY* arg_first_my = SPVM_LIST_fetch(sub->args, 0);
                            assert(arg_first_my);
                            SPVM_OP* op_name_invoker = SPVM_OP_new_op_name(compiler, arg_first_my->op_name->uv.name, op_cur->file, op_cur->line);
                            SPVM_OP* op_term_invoker = SPVM_OP_new_op_var(compiler, op_name_invoker);
                            op_term_invoker->uv.var->my = arg_first_my;
                            SPVM_OP* op_name_field = SPVM_OP_new_op_name(compiler, op_cur->uv.var->op_name->uv.name + 1, op_cur->file, op_cur->line);
                            SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, op_term_invoker, op_name_field);
                            op_field_access->uv.field_access->field = found_capture_field;
                            
                            SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                            SPVM_OP_replace_op(compiler, op_stab, op_field_access);
                            
                            op_field_access->is_lvalue = op_cur->is_lvalue;
                            
                            op_cur = op_field_access;
                            continue;
                          }
                          else {
                            // Variable is package var
                            int32_t is_package_var;
                            SPVM_PACKAGE_VAR* found_package_var = SPVM_HASH_fetch(compiler->package_var_symtable, var->op_name->uv.name, strlen(var->op_name->uv.name));
                            if (!found_package_var) {
                              found_package_var = SPVM_HASH_fetch(package->package_var_symtable, var->op_name->uv.name, strlen(var->op_name->uv.name));
                            }
                            if (found_package_var) {
                              // Var OP
                              SPVM_OP* op_name_package_var = SPVM_OP_new_op_name(compiler, op_cur->uv.var->op_name->uv.name, op_cur->file, op_cur->line);
                              SPVM_OP* op_package_var_access = SPVM_OP_new_op_package_var_access(compiler, op_name_package_var);
                              op_package_var_access->uv.package_var_access->package_var = found_package_var;
                              
                              SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                              SPVM_OP_replace_op(compiler, op_stab, op_package_var_access);
                              
                              op_package_var_access->is_lvalue = op_cur->is_lvalue;
                              
                              op_cur = op_package_var_access;
                              continue;
                            }
                            // Error
                            else {
                              SPVM_yyerror_format(compiler, "%s is not declared at %s line %d\n", var->op_name->uv.name, op_cur->file, op_cur->line);
                              return;
                            }
                          }
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_CALL_SUB: {
                        
                        // Check sub name
                        SPVM_OP_CHECKER_resolve_call_sub(compiler, op_cur, package->op_package);
                        
                        SPVM_OP* op_list_args = op_cur->last;
                        
                        SPVM_CALL_SUB* call_sub = op_cur->uv.call_sub;

                        if (!call_sub->sub) {
                          SPVM_yyerror_format(compiler, "unknown sub \"%s\" at %s line %d\n",
                            op_cur->first->uv.name, op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        if (call_sub->call_type_id != call_sub->sub->call_type_id) {
                          SPVM_yyerror_format(compiler, "Invalid subroutine call \"%s\" at %s line %d\n",
                            op_cur->first->uv.name, op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        const char* sub_abs_name = call_sub->sub->abs_name;
                        const char* sub_name = call_sub->sub->op_name->uv.name;
                        
                        int32_t sub_args_count = call_sub->sub->args->length;
                        
                        SPVM_OP* op_term = op_list_args->first;
                        int32_t call_sub_args_count = 0;
                        while ((op_term = SPVM_OP_sibling(compiler, op_term))) {
                          call_sub_args_count++;
                          if (call_sub_args_count > sub_args_count) {
                            SPVM_yyerror_format(compiler, "Too many arguments \"%s\" at %s line %d\n", sub_abs_name, op_cur->file, op_cur->line);
                            
                            return;
                          }
                          
                          SPVM_MY* sub_arg_my = SPVM_LIST_fetch(call_sub->sub->args, call_sub_args_count - 1);
                          
                          // Check if source can be assigned to dist
                          // If needed, numeric convertion op is added
                          op_term = SPVM_OP_CHECKER_check_assign(compiler, sub_arg_my->op_my, op_term);
                        }
                        
                        if (call_sub_args_count < sub_args_count) {
                          SPVM_yyerror_format(compiler, "Too few argument. sub \"%s\" at %s line %d\n", sub_abs_name, op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        // Constant subroutine
                        if (call_sub->sub->flag & SPVM_SUB_C_FLAG_IS_ENUM) {
                          // Replace sub to constant
                          op_cur->id = SPVM_OP_C_ID_CONSTANT;
                          op_cur->uv.constant = call_sub->sub->op_constant->uv.constant;
                          
                          op_cur->first = NULL;
                          op_cur->last = NULL;
                          break;
                        }
                        
                        // Update operand stack max
                        if (call_sub_args_count > sub->call_sub_arg_stack_max) {
                          sub->call_sub_arg_stack_max = call_sub_args_count;
                        }

                        // Add info sub id
                        char sub_id_string[sizeof(int32_t)];
                        memcpy(sub_id_string, &op_cur->uv.call_sub->sub->id, sizeof(int32_t));
                        int32_t found_sub_id_plus1 = (intptr_t)SPVM_HASH_fetch(package->info_sub_id_symtable, sub_id_string, sizeof(int32_t));
                        if (found_sub_id_plus1 > 0) {
                          op_cur->uv.call_sub->info_constant_id = found_sub_id_plus1 - 1;
                        }
                        else {
                          op_cur->uv.call_sub->info_constant_id = package->info_sub_ids->length;
                          SPVM_LIST_push(package->info_sub_ids, (void*)(intptr_t)op_cur->uv.call_sub->sub->id);
                          int32_t info_sub_id_plus1 = op_cur->uv.call_sub->info_constant_id + 1;
                          SPVM_HASH_insert(package->info_sub_id_symtable, sub_id_string, sizeof(int32_t), (void*)(intptr_t)info_sub_id_plus1);
                        }
                        if (package->info_sub_ids->length > SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                          SPVM_yyerror_format(compiler, "Too many package variable access at %s line %d\n", op_cur->file, op_cur->line);
                        }
                        
                        if (call_sub->sub->flag & SPVM_SUB_C_FLAG_IS_DESTRUCTOR) {
                          SPVM_yyerror_format(compiler, "Can't call DESTROY in yourself at %s line %d\n", op_cur->file, op_cur->line);
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_PACKAGE_VAR_ACCESS: {
                        
                        // Check field name
                        SPVM_OP_CHECKER_resolve_package_var_access(compiler, op_cur, package->op_package);
                        if (!op_cur->uv.package_var_access->package_var) {
                          SPVM_yyerror_format(compiler, "Package variable not found \"%s\" at %s line %d\n",
                            op_cur->uv.package_var_access->op_name->uv.name, op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        // Add info package var id
                        char package_var_id_string[sizeof(int32_t)];
                        memcpy(package_var_id_string, &op_cur->uv.package_var_access->package_var->id, sizeof(int32_t));
                        const char* package_var_name = op_cur->uv.package_var_access->package_var->name;
                        int32_t found_package_var_id_plus1 = (intptr_t)SPVM_HASH_fetch(package->info_package_var_id_symtable, package_var_id_string, sizeof(int32_t));
                        if (found_package_var_id_plus1 > 0) {
                          op_cur->uv.package_var_access->info_package_var_id = found_package_var_id_plus1 - 1;
                        }
                        else {
                          op_cur->uv.package_var_access->info_package_var_id = package->info_package_var_ids->length;
                          SPVM_LIST_push(package->info_package_var_ids, (void*)(intptr_t)op_cur->uv.package_var_access->package_var->id);
                          int32_t info_package_var_id_plus1 = op_cur->uv.package_var_access->info_package_var_id + 1;
                          SPVM_HASH_insert(package->info_package_var_id_symtable, package_var_id_string, sizeof(int32_t), (void*)(intptr_t)info_package_var_id_plus1);
                        }
                        if (package->info_package_var_ids->length > SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                          SPVM_yyerror_format(compiler, "Too many package variable access at %s line %d\n", op_cur->file, op_cur->line);
                        }                        
                        break;
                      }
                      case SPVM_OP_C_ID_ARRAY_ACCESS: {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        
                        // Left value must be array
                        if (!SPVM_TYPE_is_array_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                          SPVM_yyerror_format(compiler, "left value must be array at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        // Right value must be integer
                        if (SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                          SPVM_OP_CHECKER_apply_unary_numeric_convertion(compiler, op_cur->last);
                          SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                          
                          if (last_type->dimension == 0 && last_type->basic_type->id != SPVM_BASIC_TYPE_C_ID_INT) {
                            SPVM_yyerror_format(compiler, "array index must be int type at %s line %d\n", op_cur->file, op_cur->line);
                            
                            return;
                          }
                        }
                        else {
                          SPVM_yyerror_format(compiler, "array index must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        assert(op_cur->first);
                        assert(op_cur->last);
                        
                        // If array term is not var, create assign operator
                        SPVM_OP* op_term_array = op_cur->first;
                        if (op_term_array->id != SPVM_OP_C_ID_VAR) {
                          op_cur->no_need_check = 1;

                          SPVM_TYPE* term_index_type = SPVM_OP_get_type(compiler, op_term_array);

                          SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term_array);
                          
                          SPVM_OP* op_var_tmp = SPVM_OP_CHECKER_new_op_var_tmp(compiler, term_index_type, op_cur->file, op_cur->line);
                          SPVM_LIST_push(sub->op_sub->uv.sub->mys, op_var_tmp->uv.var->my);
                          SPVM_LIST_push(my_stack, op_var_tmp->uv.var->my);
                          SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);

                          SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_term_array);
                          
                          // Convert cur new op to var
                          SPVM_OP_replace_op(compiler, op_stab, op_assign);
                        }
                        
                        // If array access index term is not var, create assign operator
                        SPVM_OP* op_term_index = op_cur->last;
                        if (op_term_index->id != SPVM_OP_C_ID_VAR) {
                          
                          op_cur->no_need_check = 1;

                          SPVM_TYPE* term_index_type = SPVM_OP_get_type(compiler, op_term_index);

                          SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term_index);
                          
                          SPVM_OP* op_var_tmp = SPVM_OP_CHECKER_new_op_var_tmp(compiler, term_index_type, op_cur->file, op_cur->line);
                          SPVM_LIST_push(sub->op_sub->uv.sub->mys, op_var_tmp->uv.var->my);
                          SPVM_LIST_push(my_stack, op_var_tmp->uv.var->my);
                          SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);

                          SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_term_index);
                          
                          // Convert cur new op to var
                          SPVM_OP_replace_op(compiler, op_stab, op_assign);
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_FIELD_ACCESS: {
                        SPVM_OP* op_term_invocker = op_cur->first;
                        SPVM_OP* op_name = op_cur->uv.field_access->op_name;
                        
                        if (op_term_invocker->id == SPVM_OP_C_ID_ASSIGN) {
                          op_term_invocker = op_term_invocker->first;
                        }
                        
                        SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_term_invocker);
                        SPVM_PACKAGE* invocant_package = SPVM_HASH_fetch(compiler->package_symtable, type->basic_type->name, strlen(type->basic_type->name));
                        
                        if (!(type && invocant_package)) {
                          SPVM_yyerror_format(compiler, "Can't access field at %s line %d\n", op_cur->file, op_cur->line);
                          return;
                        }
                        
                        // Check field name
                        SPVM_OP_CHECKER_resolve_field_access(compiler, op_cur);
                        
                        SPVM_FIELD* field = op_cur->uv.field_access->field;
                        
                        if (!field) {
                          char* type_name = tmp_buffer;
                          SPVM_TYPE_sprint_type_name(compiler, type_name, type->basic_type->id, type->dimension, type->flag);
                          SPVM_yyerror_format(compiler, "Unknown field %s::%s at %s line %d\n",
                            type_name, op_name->uv.name, op_cur->file, op_cur->line);
                          return;
                        }
                        
                        if (field->flag & SPVM_FIELD_C_FLAG_PRIVATE) {
                          if (strcmp(type->basic_type->name, sub->package->op_name->uv.name) != 0) {
                            char* type_name = tmp_buffer;
                            SPVM_TYPE_sprint_type_name(compiler, type_name, type->basic_type->id, type->dimension, type->flag);
                            SPVM_yyerror_format(compiler, "Can't access to private field %s::%s at %s line %d\n",
                              type_name, op_name->uv.name, op_cur->file, op_cur->line);
                          }
                        }
                        
                        // Add info field id
                        char field_id_string[sizeof(int32_t)];
                        memcpy(field_id_string, &op_cur->uv.field_access->field->id, sizeof(int32_t));
                        const char* field_name = op_cur->uv.field_access->field->name;
                        int32_t found_field_id_plus1 = (intptr_t)SPVM_HASH_fetch(package->info_field_id_symtable, field_id_string, sizeof(int32_t));
                        if (found_field_id_plus1 > 0) {
                          op_cur->uv.field_access->info_field_id = found_field_id_plus1 - 1;
                        }
                        else {
                          op_cur->uv.field_access->info_field_id = package->info_field_ids->length;
                          SPVM_LIST_push(package->info_field_ids, (void*)(intptr_t)op_cur->uv.field_access->field->id);
                          int32_t info_field_id_plus1 = op_cur->uv.field_access->info_field_id + 1;
                          SPVM_HASH_insert(package->info_field_id_symtable, field_id_string, sizeof(int32_t), (void*)(intptr_t)info_field_id_plus1);
                        }
                        if (package->info_field_ids->length > SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                          SPVM_yyerror_format(compiler, "Too many package variable access at %s line %d\n", op_cur->file, op_cur->line);
                        }
                        
                        // If invocker is array access and array access object is value_t, this op become array field access
                        if (op_term_invocker->id == SPVM_OP_C_ID_ARRAY_ACCESS) {
                          SPVM_OP* op_array_access = op_term_invocker;
                          
                          SPVM_TYPE* array_element_type = SPVM_OP_get_type(compiler, op_array_access);
                          
                          int32_t is_basic_type_value_t = SPVM_TYPE_basic_type_is_value_type(compiler, array_element_type->basic_type->id, array_element_type->dimension, array_element_type->flag);
                          if (is_basic_type_value_t) {
                            if (array_element_type->dimension != 0) {
                              SPVM_yyerror_format(compiler, "value_t array field access must be 1-dimension array at %s line %d\n", op_cur->file, op_cur->line);
                            }
                            else {
                              SPVM_OP* op_array_field_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_FIELD_ACCESS, op_cur->file, op_cur->line);
                              op_array_field_access->is_lvalue = op_cur->is_lvalue;
                              
                              SPVM_ARRAY_FIELD_ACCESS* array_field_access = SPVM_ARRAY_FIELD_ACCESS_new(compiler);
                              array_field_access->field = field;
                              op_array_field_access->uv.array_field_access = array_field_access;
                              
                              SPVM_OP* op_array = op_array_access->first;
                              SPVM_OP* op_index = op_array_access->last;
                              SPVM_OP_cut_op(compiler, op_array_access->first);
                              SPVM_OP_cut_op(compiler, op_array_access->last);
                              
                              SPVM_OP_insert_child(compiler, op_array_field_access, op_array_field_access->last, op_array);
                              SPVM_OP_insert_child(compiler, op_array_field_access, op_array_field_access->last, op_index);
                              
                              SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                              SPVM_OP_replace_op(compiler, op_stab, op_array_field_access);
                              
                              op_cur = op_array_field_access;
                            }
                          }
                        }
                        
                        if (op_cur->id == SPVM_OP_C_ID_ARRAY_FIELD_ACCESS) {
                          // If array term is not var, create assign operator
                          SPVM_OP* op_term_array = op_cur->first;
                          if (op_term_array->id != SPVM_OP_C_ID_VAR) {
                            op_cur->no_need_check = 1;

                            SPVM_TYPE* term_index_type = SPVM_OP_get_type(compiler, op_term_array);

                            SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term_array);
                            
                            SPVM_OP* op_var_tmp = SPVM_OP_CHECKER_new_op_var_tmp(compiler, term_index_type, op_cur->file, op_cur->line);
                            SPVM_LIST_push(sub->op_sub->uv.sub->mys, op_var_tmp->uv.var->my);
                            SPVM_LIST_push(my_stack, op_var_tmp->uv.var->my);

                            SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);

                            SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_term_array);
                            
                            // Convert cur new op to var
                            SPVM_OP_replace_op(compiler, op_stab, op_assign);
                          }
                          
                          // If array access index term is not var, create assign operator
                          SPVM_OP* op_term_index = op_cur->last;
                          if (op_term_index->id != SPVM_OP_C_ID_VAR) {
                            op_cur->no_need_check = 1;

                            SPVM_TYPE* term_index_type = SPVM_OP_get_type(compiler, op_term_index);

                            SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term_index);
                            
                            SPVM_OP* op_var_tmp = SPVM_OP_CHECKER_new_op_var_tmp(compiler, term_index_type, op_cur->file, op_cur->line);
                            SPVM_LIST_push(sub->op_sub->uv.sub->mys, op_var_tmp->uv.var->my);
                            SPVM_LIST_push(my_stack, op_var_tmp->uv.var->my);
                            
                            SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);

                            SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_term_index);
                            
                            // Convert cur new op to var
                            SPVM_OP_replace_op(compiler, op_stab, op_assign);
                          }
                        }
                        else {
                          // If invoker term is not var, create assign operator
                          // [Before]
                          // TERM
                          // [After]
                          // ASSIGN
                          //   TERM
                          //   VAR
                          SPVM_OP* op_term_invocker = op_cur->first;
                          if (op_term_invocker->id != SPVM_OP_C_ID_VAR) {
                            op_cur->no_need_check = 1;

                            SPVM_TYPE* term_index_type = SPVM_OP_get_type(compiler, op_term_invocker);

                            SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term_invocker);
                            
                            SPVM_OP* op_var_tmp = SPVM_OP_CHECKER_new_op_var_tmp(compiler, term_index_type, op_cur->file, op_cur->line);
                            SPVM_LIST_push(sub->op_sub->uv.sub->mys, op_var_tmp->uv.var->my);
                            SPVM_LIST_push(my_stack, op_var_tmp->uv.var->my);
                            
                            SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                            SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_term_invocker);
                            
                            // Convert cur new op to var
                            SPVM_OP_replace_op(compiler, op_stab, op_assign);
                          }
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_WEAKEN_FIELD: {
                        SPVM_OP* op_field_access = op_cur->first;
                        
                        SPVM_FIELD* field = op_field_access->uv.field_access->field;
                        
                        SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_field_access);
                        
                        if (!SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                          SPVM_yyerror_format(compiler, "weaken is only used for object field \"%s\" \"%s\" at %s line %d\n",
                            field->package->op_name->uv.name, field->op_name->uv.name, op_cur->file, op_cur->line);
                          
                          break;
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_WEAKEN_ARRAY_ELEMENT: {
                        SPVM_OP* op_array_access = op_cur->first;
                        SPVM_OP* op_term_array = op_array_access->first;
                        
                        SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_array_access);
                        if (!SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                          SPVM_yyerror_format(compiler, "weaken is only used for object element at %s line %d\n", op_cur->file, op_cur->line);
                          break;
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_CONVERT: {
                        
                        SPVM_OP* op_src = op_cur->first;
                        SPVM_OP* op_dist = op_cur->last;
                        
                        SPVM_TYPE* src_type = SPVM_OP_get_type(compiler, op_src);
                        assert(src_type);
                        
                        SPVM_TYPE* dist_type = SPVM_OP_get_type(compiler, op_dist);
                        assert(dist_type);
                        
                        // Dist type is numeric type
                        int32_t can_convert = 0;
                        int32_t narrowing_convertion_error = 0;
                        if (SPVM_TYPE_is_numeric_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                          // Soruce type is numeric type
                          if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            can_convert = 1;
                          }
                          else if (SPVM_TYPE_is_numeric_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            if (dist_type->basic_type->id + SPVM_BASIC_TYPE_C_NUMERIC_OBJECT_UPGRADE_SHIFT == src_type->basic_type->id) {
                              can_convert = 1;
                            }
                            else {
                              can_convert = 0;
                            }
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                            can_convert = 1;
                          }
                          else {
                            can_convert = 0;
                          }
                        }
                        // Dist type is referece type
                        else if (SPVM_TYPE_is_ref_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                          can_convert = 0;
                        }
                        // Dist type is value type
                        else if (SPVM_TYPE_is_value_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                          can_convert = 0;
                        }
                        // Dist type is object type
                        else if (SPVM_TYPE_is_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                          // Dist type is string type
                          if (SPVM_TYPE_is_string_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                            if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                              can_convert = 1;
                            }
                            else if (SPVM_TYPE_is_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                              can_convert = 1;
                            }
                            else {
                              can_convert = 0;
                            }
                          }
                          else if (SPVM_TYPE_is_any_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                            if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                              can_convert = 1;
                            }
                            else if (SPVM_TYPE_is_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                              can_convert = 1;
                            }
                            else {
                              can_convert = 0;
                            }
                          }
                          else if (SPVM_TYPE_is_numeric_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                            if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                              if (dist_type->basic_type->id == src_type->basic_type->id + SPVM_BASIC_TYPE_C_NUMERIC_OBJECT_UPGRADE_SHIFT) {
                                can_convert = 1;
                              }
                              else {
                                can_convert = 0;
                              }
                            }
                            else if (SPVM_TYPE_is_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                              can_convert = 1;
                            }
                            else {
                              can_convert = 0;
                            }
                          }
                          else  {
                            // Source type is object type
                            if (SPVM_TYPE_is_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                              can_convert = 1;
                            }
                            // Source type is undef type
                            else if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                              can_convert = 1;
                            }
                            else {
                              can_convert = 0;
                            }
                          }
                        }
                        else {
                          assert(0);
                        }

                        if (!can_convert) {
                          SPVM_TYPE_sprint_type_name(compiler, compiler->buffer1, src_type->basic_type->id, src_type->dimension, src_type->flag);
                          SPVM_TYPE_sprint_type_name(compiler, compiler->buffer2, dist_type->basic_type->id, dist_type->dimension, dist_type->flag);
                          SPVM_yyerror_format(compiler, "Can't convert %s to %s at %s line %d\n", compiler->buffer1, compiler->buffer2, op_src->file, op_src->line);
                        }
                        
                        if (SPVM_TYPE_is_object_type(compiler, op_dist->uv.type->basic_type->id, op_dist->uv.type->dimension, op_dist->uv.type->flag)) {

                          {
                            SPVM_OP* op_type_tmp = op_dist;
                            op_type_tmp->uv.type->info_constant_id = package->info_types->length;
                            SPVM_LIST_push(package->info_types, op_type_tmp->uv.type);
                            if (package->info_types->length > SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                              SPVM_yyerror_format(compiler, "Too many types at %s line %d\n", op_type_tmp->file, op_type_tmp->line);
                            }
                          }
                          break;
                        }
                      }
                      break;
                    }
                    
                    // [END]Postorder traversal position
                  }
                  
                  if (op_cur == op_base) {

                    // Finish
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
            SPVM_LIST_free(my_stack);
            SPVM_LIST_free(block_my_base_stack);
            SPVM_LIST_free(op_switch_stack);
          }

          // set assign_to_var flag - Second tree traversal
          if (!(sub->flag & SPVM_SUB_C_FLAG_HAVE_NATIVE_DESC)) {
            // Run OPs
            SPVM_OP* op_base = sub->op_block;
            SPVM_OP* op_cur = op_base;
            int32_t finish = 0;
            while (op_cur) {
              // [START]Preorder traversal position
              if (op_cur->first) {
                op_cur = op_cur->first;
              }
              else {
                while (1) {
                  // [START]Postorder traversal position
                  switch (op_cur->id) {
                    case SPVM_OP_C_ID_ASSIGN:
                      if (op_cur->last->id == SPVM_OP_C_ID_VAR) {
                        op_cur->first->is_assigned_to_var = 1;
                      }
                      break;
                  }

                  if (op_cur == op_base) {

                    // Finish
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
          
          // Create temporary variables for not assigned values - Third tree traversal
          if (!(sub->flag & SPVM_SUB_C_FLAG_HAVE_NATIVE_DESC)) {
            // Run OPs
            SPVM_OP* op_base = sub->op_block;
            SPVM_OP* op_cur = op_base;
            int32_t finish = 0;
            while (op_cur) {
              // [START]Preorder traversal position
              if (op_cur->first) {
                op_cur = op_cur->first;
              }
              else {
                while (1) {
                  // Create temporary variable for no is_assigned_to_var term which is not variable
                  int32_t create_tmp_var = 0;
                  SPVM_TYPE* tmp_var_type = SPVM_OP_get_type(compiler, op_cur);
                  
                  // [START]Postorder traversal position
                  if (!op_cur->is_lvalue && !op_cur->is_assigned_to_var) {
                    switch (op_cur->id) {
                      case SPVM_OP_C_ID_CONVERT:
                        create_tmp_var = 1;
                        break;
                      case SPVM_OP_C_ID_ADD:
                      case SPVM_OP_C_ID_SUBTRACT:
                      case SPVM_OP_C_ID_MULTIPLY:
                      case SPVM_OP_C_ID_DIVIDE:
                      case SPVM_OP_C_ID_BIT_AND:
                      case SPVM_OP_C_ID_BIT_OR:
                      case SPVM_OP_C_ID_BIT_XOR:
                      case SPVM_OP_C_ID_BIT_NOT:
                      case SPVM_OP_C_ID_REMAINDER:
                      case SPVM_OP_C_ID_LEFT_SHIFT:
                      case SPVM_OP_C_ID_RIGHT_SHIFT:
                      case SPVM_OP_C_ID_RIGHT_SHIFT_UNSIGNED:
                      case SPVM_OP_C_ID_COMPLEMENT:
                      case SPVM_OP_C_ID_NEGATE:
                      case SPVM_OP_C_ID_PLUS:
                      case SPVM_OP_C_ID_ARRAY_LENGTH:
                      case SPVM_OP_C_ID_NEW:
                      case SPVM_OP_C_ID_CONCAT:
                      case SPVM_OP_C_ID_EXCEPTION_VAR:
                      case SPVM_OP_C_ID_PACKAGE_VAR_ACCESS:
                      case SPVM_OP_C_ID_SWITCH_CONDITION:
                      case SPVM_OP_C_ID_ARRAY_FIELD_ACCESS:
                      case SPVM_OP_C_ID_REF:
                      case SPVM_OP_C_ID_DEREF:
                        create_tmp_var = 1;
                        break;
                      case SPVM_OP_C_ID_CONSTANT: {
                        if (SPVM_TYPE_is_numeric_type(compiler, tmp_var_type->basic_type->id, tmp_var_type->dimension, tmp_var_type->flag) && op_cur->flag != SPVM_OP_C_FLAG_CONSTANT_CASE) {
                          create_tmp_var = 1;
                        }
                        break;
                      }
                      case SPVM_OP_C_ID_FIELD_ACCESS: {
                        if (!(op_cur->flag &= SPVM_OP_C_FLAG_FIELD_ACCESS_WEAKEN)) {
                          create_tmp_var = 1;
                        }
                        break;
                      }
                      case SPVM_OP_C_ID_ARRAY_ACCESS:{
                        if (!(op_cur->flag &= SPVM_OP_C_FLAG_ARRAY_ACCESS_WEAKEN)) {
                          create_tmp_var = 1;
                        }
                        break;
                      }
                      case SPVM_OP_C_ID_CALL_SUB: {
                        if (!(tmp_var_type->dimension == 0 && tmp_var_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_VOID)) {
                          create_tmp_var = 1;
                        }
                        break;
                      }
                    }
                  }

                  // Create temporary variable
                  if (create_tmp_var) {
                    SPVM_OP* op_var_tmp = SPVM_OP_CHECKER_new_op_var_tmp(compiler, tmp_var_type, op_cur->file, op_cur->line);
                    SPVM_LIST_push(sub->op_sub->uv.sub->mys, op_var_tmp->uv.var->my);
                    
                    if (op_var_tmp == NULL) {
                      return;
                    }
                    
                    // Cut new op
                    SPVM_OP* op_target = op_cur;
                    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_target);

                    // Assing op
                    SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                    SPVM_OP* op_build_assign = SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_target);
                    
                    // Convert cur new op to var
                    SPVM_OP_replace_op(compiler, op_stab, op_build_assign);
                    op_target->uv = op_cur->uv;
                    
                    op_cur = op_target;
                  }

                  if (op_cur == op_base) {

                    // Finish
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
          
          if (compiler->error_count > 0) {
            return;
          }

          assert(sub->file);
          
          // Add op my if need
          if (sub->package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE) {
            int32_t arg_index;
            for (arg_index = 0; arg_index < sub->args->length; arg_index++) {
              SPVM_MY* arg_my = SPVM_LIST_fetch(sub->args, arg_index);
              SPVM_LIST_push(sub->mys, arg_my);
            }
          }
          
          // Resolve my var id
          {
            int32_t my_index;
            int32_t my_var_id = 0;
            int32_t my_byte_var_id = 0;
            int32_t my_short_var_id = 0;
            int32_t my_int_var_id = 0;
            int32_t my_long_var_id = 0;
            int32_t my_float_var_id = 0;
            int32_t my_double_var_id = 0;
            int32_t my_object_var_id = 0;
            int32_t my_ref_var_id = 0;
            for (my_index = 0; my_index < sub->mys->length; my_index++) {
              SPVM_MY* my = SPVM_LIST_fetch(sub->mys, my_index);
              assert(my);
              SPVM_TYPE* type = SPVM_OP_get_type(compiler, my->op_my);
              
              int32_t width = SPVM_TYPE_get_width(compiler, type->basic_type->id, type->dimension, type->flag);
              if (my_var_id + (width - 1) > SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                SPVM_yyerror_format(compiler, "Too many variable declarations at %s line %d\n", my->op_my->file, my->op_my->line);
              }
              my->var_id = my_var_id;
              my_var_id += width;
              
              if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                SPVM_TYPE* numeric_type = SPVM_OP_get_type(compiler, my->op_my);
                switch(numeric_type->basic_type->id) {
                  case SPVM_BASIC_TYPE_C_ID_BYTE: {
                    my->var_id = my_byte_var_id;
                    my_byte_var_id++;
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_SHORT: {
                    my->var_id = my_short_var_id;
                    my_short_var_id++;
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_INT: {
                    my->var_id = my_int_var_id;
                    my_int_var_id++;
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_LONG: {
                    my->var_id = my_long_var_id;
                    my_long_var_id++;
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                    my->var_id = my_float_var_id;
                    my_float_var_id++;
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                    my->var_id = my_double_var_id;
                    my_double_var_id++;
                    break;
                  }
                }
              }
              else if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                my->var_id = my_object_var_id;
                my_object_var_id += width;
              }
              else if (SPVM_TYPE_is_ref_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                my->var_id = my_ref_var_id;
                my_ref_var_id += width;
              }
              else if (SPVM_TYPE_is_value_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                SPVM_PACKAGE* value_package =  type->basic_type->package;
                assert(package);
                
                SPVM_FIELD* first_field = SPVM_LIST_fetch(value_package->fields, 0);
                assert(first_field);
                
                SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, first_field->op_field);
                assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));
                
                switch (field_type->basic_type->id) {
                  case SPVM_BASIC_TYPE_C_ID_BYTE: {
                    my->var_id = my_byte_var_id;
                    my_byte_var_id += width;
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_SHORT: {
                    my->var_id = my_short_var_id;
                    my_short_var_id += width;
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_INT: {
                    my->var_id = my_int_var_id;
                    my_int_var_id += width;
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_LONG: {
                    my->var_id = my_long_var_id;
                    my_long_var_id += width;
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                    my->var_id = my_float_var_id;
                    my_float_var_id += width;
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                    my->var_id = my_double_var_id;
                    my_double_var_id += width;
                    break;
                  }
                  default:
                    assert(0);
                }
              }
              else {
                assert(0);
              }
            }

            int32_t args_alloc_length = SPVM_SUB_get_arg_alloc_length(compiler, sub);
            sub->args_alloc_length = args_alloc_length;

            sub->byte_vars_alloc_length = my_byte_var_id;
            sub->short_vars_alloc_length = my_short_var_id;
            sub->int_vars_alloc_length = my_int_var_id;
            sub->long_vars_alloc_length = my_long_var_id;
            sub->float_vars_alloc_length = my_float_var_id;
            sub->double_vars_alloc_length = my_double_var_id;

            sub->object_vars_alloc_length = my_object_var_id;
            sub->ref_vars_alloc_length = my_ref_var_id;
            
            sub->return_runtime_type = SPVM_TYPE_get_runtime_type(compiler, sub->return_type->basic_type->id, sub->return_type->dimension, sub->return_type->flag);

            // Resolve my runtime type and width
            for (int32_t my_index = 0; my_index < sub->mys->length; my_index++) {
              SPVM_MY* my = SPVM_LIST_fetch(sub->mys, my_index);
              SPVM_TYPE* my_type = SPVM_OP_get_type(compiler, my->op_my);
              
              my->runtime_type = SPVM_TYPE_get_runtime_type(compiler, my_type->basic_type->id, my_type->dimension, my_type->flag);
              
              int32_t type_width;
              if (SPVM_TYPE_is_numeric_type(compiler, my_type->basic_type->id, my_type->dimension, my_type->flag)) {
                type_width = 1;
                switch (my_type->basic_type->id) {
                  case SPVM_BASIC_TYPE_C_ID_BYTE: {
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_SHORT: {
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_INT: {
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_LONG: {
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                    break;
                  }
                  default: {
                    assert(0);
                    break;
                  }
                }
              }
              else if (SPVM_TYPE_is_value_type(compiler, my_type->basic_type->id, my_type->dimension, my_type->flag)) {
                SPVM_PACKAGE* value_package =  my_type->basic_type->package;
                assert(package);
                
                SPVM_FIELD* first_field = SPVM_LIST_fetch(value_package->fields, 0);
                assert(first_field);
                
                SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, first_field->op_field);
                assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));

                type_width = value_package->fields->length;
                switch (field_type->basic_type->id) {
                  case SPVM_BASIC_TYPE_C_ID_BYTE: {
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_SHORT: {
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_INT: {
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_LONG: {
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                    break;
                  }
                  default: {
                    assert(0);
                  }
                }
              }
              else if (SPVM_TYPE_is_object_type(compiler, my_type->basic_type->id, my_type->dimension, my_type->flag)) {
                type_width = 1;
              }
              else if (SPVM_TYPE_is_ref_type(compiler, my_type->basic_type->id, my_type->dimension, my_type->flag)) {
                switch (my_type->basic_type->id) {
                  case SPVM_BASIC_TYPE_C_ID_BYTE: {
                    type_width = 1;
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_SHORT: {
                    type_width = 1;
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_INT: {
                    type_width = 1;
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_LONG: {
                    type_width = 1;
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                    type_width = 1;
                    break;
                  }
                  case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                    type_width = 1;
                    break;
                  }
                  default: {
                    SPVM_PACKAGE* value_package =  my_type->basic_type->package;
                    assert(package);
                    
                    SPVM_FIELD* first_field = SPVM_LIST_fetch(value_package->fields, 0);
                    assert(first_field);
                    
                    SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, first_field->op_field);
                    assert(SPVM_TYPE_is_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag));

                    type_width = 1;

                    switch (field_type->basic_type->id) {
                      case SPVM_BASIC_TYPE_C_ID_BYTE: {
                        break;
                      }
                      case SPVM_BASIC_TYPE_C_ID_SHORT: {
                        break;
                      }
                      case SPVM_BASIC_TYPE_C_ID_INT: {
                        break;
                      }
                      case SPVM_BASIC_TYPE_C_ID_LONG: {
                        break;
                      }
                      case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                        break;
                      }
                      case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                        break;
                      }
                      default: {
                        assert(0);
                      }
                    }
                    break;
                  }
                }
              }
              else {
                assert(0);
              }
              
              my->type_width = type_width;
            }
          }

          // Add more information for opcode building - Fourth tree traversal
          if (!(sub->flag & SPVM_SUB_C_FLAG_HAVE_NATIVE_DESC)) {
            // Block stack
            SPVM_LIST* op_block_stack = SPVM_LIST_new(0);
            
            // Run OPs
            SPVM_OP* op_base = sub->op_block;
            SPVM_OP* op_cur = op_base;
            int32_t finish = 0;
            while (op_cur) {
              // [START]Preorder traversal position
              switch (op_cur->id) {
                // Start scope
                case SPVM_OP_C_ID_BLOCK: {
                  // Push block
                  SPVM_LIST_push(op_block_stack, op_cur);
                  
                  break;
                }
              }

              if (op_cur->first) {
                op_cur = op_cur->first;
              }
              else {
                while (1) {
                  // [START]Postorder traversal position
                  switch (op_cur->id) {
                    case SPVM_OP_C_ID_BLOCK: {
                      SPVM_OP* op_block_current = SPVM_LIST_fetch(op_block_stack, op_block_stack->length - 1);

                      SPVM_LIST_pop(op_block_stack);
                      
                      // Parent block need LEAVE_SCOPE if child is needing LEAVE_SCOPE
                      if (op_block_stack->length > 0) {
                        SPVM_OP* op_block_parent = SPVM_LIST_fetch(op_block_stack, op_block_stack->length - 1);
                        if (!op_block_parent->uv.block->have_object_var_decl) {
                          if (op_block_current->uv.block->have_object_var_decl) {
                            op_block_parent->uv.block->have_object_var_decl = 1;
                          }
                        }
                      }
                    
                      break;
                    }
                    case SPVM_OP_C_ID_VAR: {
                      if (op_cur->uv.var->is_declaration) {
                        SPVM_MY* my = op_cur->uv.var->my;
                        
                        SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                        int32_t type_is_value_t = SPVM_TYPE_is_value_type(compiler, type->basic_type->id, type->dimension, type->flag);
                        
                        if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag) && !type_is_value_t) {
                          SPVM_OP* op_block_current = SPVM_LIST_fetch(op_block_stack, op_block_stack->length - 1);
                          op_block_current->uv.block->have_object_var_decl = 1;
                        }
                      }
                      
                      break;
                    }
                  }

                  if (op_cur == op_base) {

                    // Finish
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
            SPVM_LIST_free(op_block_stack);
          }
        }
      }
    }
  }

  // Resolve constant id
  {
    int32_t constant_index;
    for (constant_index = 0; constant_index < compiler->op_constants->length; constant_index++) {
      SPVM_OP* op_constant = SPVM_LIST_fetch(compiler->op_constants, constant_index);
      SPVM_CONSTANT* constant = op_constant->uv.constant;
      constant->id = constant_index;
    }
  }


#ifdef SPVM_DEBUG_DUMP
#include "spvm_dumper.h"
  if (compiler->error_count == 0) {
    printf("\n[Basic types]\n");
    SPVM_DUMPER_dump_basic_types(compiler, compiler->basic_types);
    
    printf("\n[Packages]\n");
    SPVM_DUMPER_dump_packages(compiler, compiler->packages);
  }
#endif
}

SPVM_OP* SPVM_OP_CHECKER_check_assign(SPVM_COMPILER* compiler, SPVM_OP* op_dist, SPVM_OP* op_src) {
  SPVM_TYPE* dist_type = SPVM_OP_get_type(compiler, op_dist);
  SPVM_TYPE* src_type = SPVM_OP_get_type(compiler, op_src);
  
  // Dist type is numeric type
  int32_t can_assign = 0;
  int32_t narrowing_convertion_error = 0;
  int32_t need_convertion = 0;
  if (SPVM_TYPE_is_numeric_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
    // Soruce type is numeric type
    if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
      // Dist type is same as source type
      if (dist_type->basic_type->id == src_type->basic_type->id) {
        can_assign = 1;
      }
      // Dist type is more wide than source type
      else if (dist_type->basic_type->id > src_type->basic_type->id) {
        can_assign = 1;
        need_convertion = 1;
      }
      // Dist type is narrow than source type
      else if (dist_type->basic_type->id < src_type->basic_type->id) {
        int32_t can_narrowing_convertion = 0;
        if (op_src->id == SPVM_OP_C_ID_CONSTANT) {
          SPVM_CONSTANT* constant = op_src->uv.constant;
          assert(constant->type->dimension == 0);
          if (constant->type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT || constant->type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
            int64_t constant_value;
            if (constant->type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
              constant_value = constant->value.ival;
            }
            else if (constant->type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
              constant_value = constant->value.lval;
            }
            else {
              assert(0);
            }
            
            if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
              if (constant_value >= INT8_MIN && constant_value <= INT8_MAX) {
                can_narrowing_convertion = 1;
              }
              else {
                can_narrowing_convertion = 0;
              }
            }
            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT) {
              if (constant_value >= INT16_MIN && constant_value <= INT16_MAX) {
                can_narrowing_convertion = 1;
              }
              else {
                can_narrowing_convertion = 0;
              }
            }
            else if (dist_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
              if (constant_value >= INT32_MIN && constant_value <= INT32_MAX) {
                can_narrowing_convertion = 1;
              }
              else {
                can_narrowing_convertion = 0;
              }
            }
            else {
              assert(0);
            }
          }
          else {
            can_narrowing_convertion = 0;
          }
        }
        else {
          can_assign = 0;
        }
        
        if (can_narrowing_convertion) {
          need_convertion = 1;
          can_assign = 1;
        }
        else {
          narrowing_convertion_error = 1;
          can_assign = 0;
        }
      }
    }
    else if (SPVM_TYPE_is_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
      if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
        can_assign = 1;
        need_convertion = 1;
      }
      else if (SPVM_TYPE_is_numeric_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
        if (src_type->basic_type->id == dist_type->basic_type->id + SPVM_BASIC_TYPE_C_NUMERIC_OBJECT_UPGRADE_SHIFT) {
          can_assign = 1;
          need_convertion = 1;
        }
        else {
          can_assign = 0;
        }
      }
      else {
        can_assign = 0;
      }
    }
    else {
      can_assign = 0;
    }
  }
  // Dist type is referece type
  else if (SPVM_TYPE_is_ref_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
    if (SPVM_TYPE_is_ref_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
      if (dist_type->basic_type->id == src_type->basic_type->id && dist_type->dimension == src_type->dimension) {
        can_assign = 1;
      }
      else {
        can_assign = 0;
      }
    }
    else {
      can_assign = 0;
    }
  }
  // Dist type is value type
  else if (SPVM_TYPE_is_value_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
    if (SPVM_TYPE_is_value_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
      if (dist_type->basic_type->id == src_type->basic_type->id && dist_type->dimension == src_type->dimension) {
        can_assign = 1;
      }
      else {
        can_assign = 0;
      }
    }
    else {
      can_assign = 0;
    }
  }
  // Dist type is object type
  else if (SPVM_TYPE_is_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
    // Dist type is string type
    if (SPVM_TYPE_is_string_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
      // Source type is number
      if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
        can_assign = 1;
        need_convertion = 1;
      }
      // Source type is string
      else if (SPVM_TYPE_is_string_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
        can_assign = 1;
      }
      else if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
        can_assign = 1;
      }
      else {
        can_assign = 0;
      }
    }
    // Dist type is any object type
    else if (SPVM_TYPE_is_any_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
      // Source type is object type
      if (SPVM_TYPE_is_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
        can_assign = 1;
      }
      // Source type is numeric type
      else if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
        can_assign = 1;
        need_convertion = 1;
      }
      // Source type is undef type
      else if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
        can_assign = 1;
      }
      else {
        can_assign = 0;
      }
    }
    // Dist type is numeric object type
    else if (SPVM_TYPE_is_numeric_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
      if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
        if (dist_type->basic_type->id == src_type->basic_type->id + SPVM_BASIC_TYPE_C_NUMERIC_OBJECT_UPGRADE_SHIFT) {
          can_assign = 1;
          need_convertion = 1;
        }
        else {
          can_assign = 0;
        }
      }
      else if (SPVM_TYPE_is_numeric_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
        if (src_type->basic_type->id == dist_type->basic_type->id) {
          can_assign = 1;
        }
        else {
          can_assign = 0;
        }
      }
      else if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
        can_assign = 1;
      }
      else {
        can_assign = 0;
      }
    }
    // Dist type is object type without string type and any object type and numeric object type
    else {
      // Source type is object type
      if (SPVM_TYPE_is_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
        if (dist_type->dimension > 0){
          if (dist_type->basic_type->id == src_type->basic_type->id && dist_type->dimension == src_type->dimension) {
            can_assign = 1;
          }
          else {
            can_assign = 0;
          }
        }
        // Dist type is class or interface
        else if (dist_type->dimension == 0){
          // Dist type is class
          if (SPVM_TYPE_is_class_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
            if (SPVM_TYPE_is_class_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
              if (dist_type->basic_type->id == src_type->basic_type->id) {
                can_assign = 1;
              }
              else {
                can_assign = 0;
              }
            }
            else {
              can_assign = 0;
            }
          }
          // Dist type is interface
          else if (SPVM_TYPE_is_interface_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
            
            // Source type is class or interface
            if (
              SPVM_TYPE_is_class_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)
              || SPVM_TYPE_is_interface_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)
            )
            {
              can_assign = SPVM_TYPE_has_interface(
                compiler,
                src_type->basic_type->id, src_type->dimension, src_type->flag,
                dist_type->basic_type->id, dist_type->dimension, dist_type->flag
              );
            }
            else {
              can_assign = 0;
            }
          }
          else {
            assert(0);
          }
        }
        else {
          assert(0);
        }
      }
      // Source type is undef type
      else if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
        can_assign = 1;
      }
      else {
        can_assign = 0;
      }
    }
  }
  else {
    SPVM_yyerror_format(compiler, "Can't assign to empty type at %s line %d\n", op_src->file, op_src->line);
  }
    
  if (!can_assign) {
    if (narrowing_convertion_error) {
      SPVM_yyerror_format(compiler, "Can't apply narrowing convertion at %s line %d\n", op_src->file, op_src->line);
    }
    else {
      SPVM_TYPE_sprint_type_name(compiler, compiler->buffer1, src_type->basic_type->id, src_type->dimension, src_type->flag);
      SPVM_TYPE_sprint_type_name(compiler, compiler->buffer2, dist_type->basic_type->id, dist_type->dimension, dist_type->flag);
      SPVM_yyerror_format(compiler, "Can't convert %s to %s at %s line %d\n", compiler->buffer1, compiler->buffer2, op_src->file, op_src->line);
    }
  }

  // Const check
  if (!(dist_type->flag & SPVM_TYPE_C_FLAG_CONST) && (src_type->flag & SPVM_TYPE_C_FLAG_CONST)) {
    SPVM_yyerror_format(compiler, "Can't convert const type to not const type at %s line %d\n", op_src->file, op_src->line);
  }

  if (need_convertion) {
    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_src);
    
    SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, op_src->file, op_src->line);
    SPVM_OP* op_dist_type = SPVM_OP_new_op_type(compiler, dist_type, op_src->file, op_src->line);
    SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_src);
    
    SPVM_OP_replace_op(compiler, op_stab, op_convert);
    return op_convert;
  }
  
  return op_src;
}

void SPVM_OP_CHECKER_resolve_types(SPVM_COMPILER* compiler) {

  SPVM_LIST* op_types = compiler->op_types;
  
  // Check type names
  for (int32_t i = 0; i < op_types->length; i++) {
    SPVM_OP* op_type = SPVM_LIST_fetch(op_types, i);
    
    SPVM_TYPE* type = op_type->uv.type;
    
    if (type->is_self) {
      continue;
    }
    
    // Basic type name
    const char* basic_type_name = type->basic_type->name;

    // Check if type name is package
    if (type->basic_type->id > SPVM_BASIC_TYPE_C_ID_ANY_OBJECT) {
      
      // Unknonw package
      SPVM_HASH* package_symtable = compiler->package_symtable;
      SPVM_PACKAGE* found_package = SPVM_HASH_fetch(package_symtable, basic_type_name, strlen(basic_type_name));
      if (!found_package) {
        SPVM_yyerror_format(compiler, "Unknown package \"%s\" at %s line %d\n", basic_type_name, op_type->file, op_type->line);
      }
    }
    
    // Reference type must be numeric refernce type or value reference type
    if (SPVM_TYPE_is_ref_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
      if (!(SPVM_TYPE_is_numeric_ref_type(compiler, type->basic_type->id, type->dimension, type->flag) || SPVM_TYPE_is_value_ref_type(compiler, type->basic_type->id, type->dimension, type->flag))) {
        SPVM_yyerror_format(compiler, "Reference type must be numeric refernce type or value_t reference type \"%s\"\\ at %s line %d\n", basic_type_name, op_type->file, op_type->line);
      }
    }
    
    // Interface array is invalid
    if (type->basic_type->package && type->basic_type->package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE) {
      if (type->dimension > 1) {
        SPVM_yyerror_format(compiler, "Array of interface is invalid at %s line %d\n", op_type->file, op_type->line);
      }
    }
  }
}

void SPVM_OP_CHECKER_resolve_call_sub(SPVM_COMPILER* compiler, SPVM_OP* op_call_sub, SPVM_OP* op_package_current) {
  
  SPVM_CALL_SUB* call_sub = op_call_sub->uv.call_sub;
  
  if (call_sub->sub) {
    return;
  }
  
  SPVM_SUB* found_sub;
  
  const char* sub_name = call_sub->op_name->uv.name;
  // $obj->sub_name
  if (call_sub->call_type_id == SPVM_SUB_C_CALL_TYPE_ID_METHOD) {
    SPVM_TYPE* type = SPVM_OP_get_type(compiler, call_sub->op_invocant);
    const char* basic_type_name = type->basic_type->name;
    const char* sub_abs_name = SPVM_OP_create_abs_name(compiler, basic_type_name, sub_name);
    
    found_sub= SPVM_HASH_fetch(
      compiler->sub_symtable,
      sub_abs_name,
      strlen(sub_abs_name)
    );
  }
  else {
    // Package->sub_name
    if (call_sub->op_invocant) {
      const char* package_name = call_sub->op_invocant->uv.type->basic_type->name;
      const char* sub_abs_name = SPVM_OP_create_abs_name(compiler, package_name, sub_name);
      found_sub= SPVM_HASH_fetch(
        compiler->sub_symtable,
        sub_abs_name,
        strlen(sub_abs_name)
      );
    }
    // sub_name
    else {
      // Search current pacakge
      SPVM_PACKAGE* package = op_package_current->uv.package;
      const char* package_name = package->op_name->uv.name;
      const char* sub_abs_name = SPVM_OP_create_abs_name(compiler, package_name, sub_name);
      found_sub= SPVM_HASH_fetch(
        compiler->sub_symtable,
        sub_abs_name,
        strlen(sub_abs_name)
      );
      
      // Search SPVM::CORE
      if (!found_sub) {
        sub_abs_name = SPVM_OP_create_abs_name(compiler, "SPVM::CORE", sub_name);
        
        found_sub= SPVM_HASH_fetch(
          compiler->sub_symtable,
          sub_abs_name,
          strlen(sub_abs_name)
        );
      }
    }
  }
  
  if (found_sub) {
    call_sub->sub = found_sub;
  }
}

void SPVM_OP_CHECKER_resolve_field_access(SPVM_COMPILER* compiler, SPVM_OP* op_field_access) {

  SPVM_FIELD_ACCESS* field_access = op_field_access->uv.field_access;

  if (field_access->field) {
    return;
  }

  SPVM_OP* op_term = op_field_access->first;
  SPVM_OP* op_name = field_access->op_name;
  
  SPVM_TYPE* invoker_type = SPVM_OP_get_type(compiler, op_term);
  SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, invoker_type->basic_type->name, strlen(invoker_type->basic_type->name));
  const char* field_name = op_name->uv.name;
  
  SPVM_FIELD* found_field = SPVM_HASH_fetch(
    package->field_symtable,
    field_name,
    strlen(field_name)
  );
  if (found_field) {
    op_field_access->uv.field_access->field = found_field;
  }
}

void SPVM_OP_CHECKER_resolve_package_var_access(SPVM_COMPILER* compiler, SPVM_OP* op_package_var_access, SPVM_OP* op_package) {
  
  SPVM_OP* op_name = op_package_var_access->uv.package_var_access->op_name;
  
  const char* name = op_name->uv.name;
  const char* abs_name;
  if (strchr(name, ':')) {
    abs_name = name;
  }
  else {
    abs_name = SPVM_OP_create_package_var_access_abs_name(compiler, op_package->uv.package->op_name->uv.name, name);
  }
  
  SPVM_PACKAGE_VAR* package_var = SPVM_HASH_fetch(compiler->package_var_symtable, abs_name, strlen(abs_name));
  
  if (package_var) {
    op_package_var_access->uv.package_var_access->package_var = package_var;
  }
}

void SPVM_OP_CHECKER_resolve_basic_types(SPVM_COMPILER* compiler) {
  SPVM_LIST* basic_types = compiler->basic_types;
  
  {
    int32_t basic_type_index;
    for (basic_type_index = 0; basic_type_index < basic_types->length; basic_type_index++) {
      SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(basic_types, basic_type_index);
      int32_t basic_type_id = basic_type->id;
      SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, basic_type->name, strlen(basic_type->name));
      if (package) {
        basic_type->package = package;
      }
    }
  }
}

void SPVM_OP_CHECKER_resolve_packages(SPVM_COMPILER* compiler) {
  
  // Sort package by package name
  for (int32_t i = 0; i < (compiler->packages->length - 1); i++) {
    for (int32_t j = (compiler->packages->length - 1); j > i; j--) {
      SPVM_PACKAGE* package1 = SPVM_LIST_fetch(compiler->packages, j-1);
      SPVM_PACKAGE* package2 = SPVM_LIST_fetch(compiler->packages, j);
      
      void** values = compiler->packages->values;

      if (strcmp(package1->name, package2->name) > 0) {
        SPVM_PACKAGE* temp = values[j-1];
        values[j-1] = values[j];
        values[j] = temp;
      }
    }
  }
  
  // Set package id
  for (int32_t package_index = 0; package_index < compiler->packages->length; package_index++) {
    SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_index);
    package->id = package_index + 1;
  }
  
  for (int32_t package_index = 0; package_index < compiler->packages->length; package_index++) {
    SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_index);
    
    const char* package_name = package->op_name->uv.name;
    
    // value_t package limitation
    if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE_T) {
      // Can't have subroutines
      if (package->subs->length > 0) {
        SPVM_yyerror_format(compiler, "value_t package can't have subroutines at %s line %d\n", package->op_package->file, package->op_package->line);
      }
      // Can't have package variables
      if (package->package_vars->length > 0) {
        SPVM_yyerror_format(compiler, "value_t package can't have package variables at %s line %d\n", package->op_package->file, package->op_package->line);
      }
      
      // At least have one field
      if (package->fields->length == 0) {
        SPVM_yyerror_format(compiler, "value_t package have at least one field at %s line %d\n", package->op_package->file, package->op_package->line);
      }
      // Max fields length is 16
      else if (package->fields->length > SPVM_LIMIT_C_VALUE_T_FIELDS_LENGTH_MAX) {
        SPVM_yyerror_format(compiler, "Too many fields at %s line %d\n", package->op_package->file, package->op_package->line);
      }
      else {
        SPVM_LIST* fields = package->fields;
        SPVM_FIELD* first_field = SPVM_LIST_fetch(fields, 0);
        SPVM_TYPE* first_field_type = SPVM_OP_get_type(compiler, first_field->op_field);
        if (!SPVM_TYPE_is_numeric_type(compiler, first_field_type->basic_type->id, first_field_type->dimension, first_field_type->flag)) {
          SPVM_yyerror_format(compiler, "value_t package must have numeric field at %s line %d\n", first_field->op_field->file, first_field->op_field->line);
        }
        else {
          int32_t field_index;
          int32_t numeric_field_error = 0;
          for (field_index = 0; field_index < package->fields->length; field_index++) {
            SPVM_FIELD* field = SPVM_LIST_fetch(fields, field_index);
            SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, field->op_field);
            if (!(field_type->basic_type->id == first_field_type->basic_type->id && field_type->dimension == first_field_type->dimension)) {
              SPVM_yyerror_format(compiler, "field must have %s type at %s line %d\n", field_type->basic_type->name, field->op_field->file, field->op_field->line);
              numeric_field_error = 1;
            }
          }
          if (!numeric_field_error) {
            // Check type name
            char* tail_name = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, 255);
            switch (first_field_type->basic_type->id) {
              case SPVM_BASIC_TYPE_C_ID_BYTE:
                sprintf(tail_name, "_b%d", fields->length);
                break;
              case SPVM_BASIC_TYPE_C_ID_SHORT:
                sprintf(tail_name, "_s%d", fields->length);
                break;
              case SPVM_BASIC_TYPE_C_ID_INT:
                sprintf(tail_name, "_i%d", fields->length);
                break;
              case SPVM_BASIC_TYPE_C_ID_LONG:
                sprintf(tail_name, "_l%d", fields->length);
                break;
              case SPVM_BASIC_TYPE_C_ID_FLOAT:
                sprintf(tail_name, "_f%d", fields->length);
                break;
              case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                sprintf(tail_name, "_d%d", fields->length);
                break;
              default:
                assert(0);
            }
            int32_t tail_name_length = (int32_t)strlen(tail_name);
            
            char* found_pos_ptr = strstr(package_name, tail_name);
            if (found_pos_ptr) {
              if (*(found_pos_ptr + tail_name_length) != '\0') {
                SPVM_yyerror_format(compiler, "package name must end with %s at %s line %d\n", tail_name, package->op_package->file, package->op_package->line);
              }
            }
            else {
              SPVM_yyerror_format(compiler, "package name must end with %s at %s line %d\n", tail_name, package->op_package->file, package->op_package->line);
            }
          }
        }
      }
    }
    
    // Check fields
    {
      int32_t field_index;
      for (field_index = 0; field_index < package->fields->length; field_index++) {
        SPVM_FIELD* field = SPVM_LIST_fetch(package->fields, field_index);
        SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, field->op_field);

        // valut_t can't become field
        int32_t is_value_t = SPVM_TYPE_is_value_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag);
        if (is_value_t) {
          SPVM_yyerror_format(compiler, "value_t type can't become field at %s line %d\n", field->op_field->file, field->op_field->line);
        }
        else {
          // Add object field indexes
          if (SPVM_TYPE_is_object_type(compiler, field->type->basic_type->id, field->type->dimension, field->type->flag)) {
            SPVM_LIST_push(package->object_field_indexes, (void*)(intptr_t)field->index);
          }
        }
        
        // Set runtime type
        field->runtime_type = SPVM_TYPE_get_runtime_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag);
      }
    }
    
    // valut_t can't become package variable
    {
      int32_t package_var_index;
      for (package_var_index = 0; package_var_index < package->package_vars->length; package_var_index++) {
        SPVM_PACKAGE_VAR* package_var = SPVM_LIST_fetch(package->package_vars, package_var_index);
        SPVM_TYPE* package_var_type = SPVM_OP_get_type(compiler, package_var->op_package_var);
        int32_t is_value_t = SPVM_TYPE_is_value_type(compiler, package_var_type->basic_type->id, package_var_type->dimension, package_var_type->flag);
        
        if (is_value_t) {
          SPVM_yyerror_format(compiler, "value_t type can't become package variable at %s line %d\n", package_var->op_package_var->file, package_var->op_package_var->line);
        }
      }
    }

    // Check subroutines
    {
      int32_t i;
      for (i = 0; i < package->subs->length; i++) {
        SPVM_SUB* sub = SPVM_LIST_fetch(package->subs, i);
        
        // Argument limit check
        int32_t arg_allow_count = 0;
        for (int32_t arg_index = 0; arg_index < sub->args->length; arg_index++) {
          SPVM_MY* arg_my = SPVM_LIST_fetch(sub->args, arg_index);

          SPVM_TYPE* arg_type = SPVM_OP_get_type(compiler, arg_my->op_my);
          
          int32_t is_arg_type_is_value_type = SPVM_TYPE_is_value_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag);
          int32_t is_arg_type_is_value_ref_type = SPVM_TYPE_is_value_ref_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag);
          
          if (is_arg_type_is_value_type || is_arg_type_is_value_ref_type) {
            arg_allow_count += arg_type->basic_type->package->fields->length;
          }
          else {
            arg_allow_count++;
          }
        }
        if (arg_allow_count > 255) {
          SPVM_yyerror_format(compiler, "Over argument limit at %s line %d\n", sub->op_sub->file, sub->op_sub->line);
        }
      }
    }

    // Register sub signature
    {
      int32_t i;
      for (i = 0; i < package->subs->length; i++) {
        SPVM_SUB* sub = SPVM_LIST_fetch(package->subs, i);
        const char* sub_signature = SPVM_OP_CHECKER_create_sub_signature(compiler, sub);
        sub->signature = sub_signature;
      }
    }

    // Register field signature
    {
      int32_t i;
      for (i = 0; i < package->fields->length; i++) {
        SPVM_FIELD* field = SPVM_LIST_fetch(package->fields, i);
        const char* field_signature = SPVM_OP_CHECKER_create_field_signature(compiler, field);
        field->signature = field_signature;
      }
    }

    // Register package_var signature
    {
      int32_t i;
      for (i = 0; i < package->package_vars->length; i++) {
        SPVM_PACKAGE_VAR* package_var = SPVM_LIST_fetch(package->package_vars, i);
        const char* package_var_signature = SPVM_OP_CHECKER_create_package_var_signature(compiler, package_var);
        package_var->signature = package_var_signature;
      }
    }

  }
}

const char* SPVM_OP_CHECKER_create_sub_signature(SPVM_COMPILER* compiler, SPVM_SUB* sub) {
  
  int32_t length = 0;
  
  // Calcurate signature length
  {
    // Return type basic type
    length += strlen(sub->return_type->basic_type->name);
    
    // Return type dimension
    length += sub->return_type->dimension * 2;
    
    // (
    length += 1;
    
    int32_t arg_index;
    for (arg_index = 0; arg_index < sub->args->length; arg_index++) {
      if (sub->call_type_id == SPVM_SUB_C_CALL_TYPE_ID_METHOD && arg_index == 0) {
        // self
        length += 4;
      }
      else {
        SPVM_MY* arg_my_sub = SPVM_LIST_fetch(sub->args, arg_index);
        SPVM_TYPE* type_arg_sub = SPVM_OP_get_type(compiler, arg_my_sub->op_my);
        
        // Ref
        if (SPVM_TYPE_is_ref_type(compiler, type_arg_sub->basic_type->id, type_arg_sub->dimension, type_arg_sub->flag)) {
          length += 1;
        }
        
        // TYPE
        length += strlen(type_arg_sub->basic_type->name);
        
        // Dimension
        length += type_arg_sub->dimension * 2;
      }
      // ,
      if (arg_index != sub->args->length - 1) {
        length += 1;
      }
    }
    
    // )
    length += 1;
  }
  
  char* sub_signature = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, length + 1);
  
  // Calcurate sub signature length
  char* bufptr = sub_signature;
  {
    // Return type
    memcpy(bufptr, sub->return_type->basic_type->name, strlen(sub->return_type->basic_type->name));
    bufptr += strlen(sub->return_type->basic_type->name);
    
    int32_t dim_index;
    for (dim_index = 0; dim_index < sub->return_type->dimension; dim_index++) {
      memcpy(bufptr, "[]", 2);
      bufptr += 2;
    }
    
    // (
    *bufptr = '(';
    bufptr += 1;
    
    int32_t arg_index;
    for (arg_index = 0; arg_index < sub->args->length; arg_index++) {
      // self
      if (sub->call_type_id == SPVM_SUB_C_CALL_TYPE_ID_METHOD && arg_index == 0) {
        memcpy(bufptr, "self", 4);
        bufptr += 4;
      }
      else {
        SPVM_MY* arg_my_sub = SPVM_LIST_fetch(sub->args, arg_index);
        SPVM_TYPE* type_arg_sub = SPVM_OP_get_type(compiler, arg_my_sub->op_my);
        
        // Ref
        if (SPVM_TYPE_is_ref_type(compiler, type_arg_sub->basic_type->id, type_arg_sub->dimension, type_arg_sub->flag)) {
          *bufptr = '&';
          bufptr += 1;
        }
        
        // TYPE
        memcpy(bufptr, type_arg_sub->basic_type->name, strlen(type_arg_sub->basic_type->name));
        bufptr += strlen(type_arg_sub->basic_type->name);

        int32_t dim_index;
        for (dim_index = 0; dim_index < type_arg_sub->dimension; dim_index++) {
          memcpy(bufptr, "[]", 2);
          bufptr += 2;
        }
      }

      // ,
      if (arg_index != sub->args->length - 1) {
        memcpy(bufptr, ",", 1);
        bufptr += 1;
      }
    }
    
    // )
    memcpy(bufptr, ")", 1);
    bufptr += 1;
  }
  
  return sub_signature;
}

const char* SPVM_OP_CHECKER_create_field_signature(SPVM_COMPILER* compiler, SPVM_FIELD* field) {
  
  int32_t length = 0;
  
  // Calcurate signature length
  {
    // Basic type
    length += strlen(field->type->basic_type->name);
    
    // Type dimension
    length += field->type->dimension * 2;
  }
  
  char* field_signature = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, length + 1);
  
  // Calcurate field signature length
  char* bufptr = field_signature;
  {
    // Basic type
    memcpy(bufptr, field->type->basic_type->name, strlen(field->type->basic_type->name));
    bufptr += strlen(field->type->basic_type->name);
    
    // Type dimension
    int32_t dim_index;
    for (dim_index = 0; dim_index < field->type->dimension; dim_index++) {
      memcpy(bufptr, "[]", 2);
      bufptr += 2;
    }
  }
  
  return field_signature;
}

const char* SPVM_OP_CHECKER_create_package_var_signature(SPVM_COMPILER* compiler, SPVM_PACKAGE_VAR* package_var) {
  
  int32_t length = 0;
  
  // Calcurate signature length
  {
    // Basic type
    length += strlen(package_var->type->basic_type->name);
    
    // Type dimension
    length += package_var->type->dimension * 2;
  }
  
  char* package_var_signature = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, length + 1);
  
  // Calcurate package_var signature length
  char* bufptr = package_var_signature;
  {
    // Basic type
    memcpy(bufptr, package_var->type->basic_type->name, strlen(package_var->type->basic_type->name));
    bufptr += strlen(package_var->type->basic_type->name);
    
    // Type dimension
    int32_t dim_index;
    for (dim_index = 0; dim_index < package_var->type->dimension; dim_index++) {
      memcpy(bufptr, "[]", 2);
      bufptr += 2;
    }
  }
  
  return package_var_signature;
}
