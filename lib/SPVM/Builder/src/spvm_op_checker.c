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
#include "spvm_check_ast_info.h"
#include "spvm_string_buffer.h"
#include "spvm_use.h"

void SPVM_OP_CHECKER_free_mem_id(SPVM_COMPILER* compiler, SPVM_LIST* mem_stack, SPVM_MY* my) {
  (void)compiler;
  
  int32_t width = my->type_width;

  for (int32_t mem_id = 0; mem_id < mem_stack->length; mem_id++) {
    int32_t my_id = (intptr_t)SPVM_LIST_fetch(mem_stack, mem_id);
    if (my_id == my->id) {
      assert(mem_id + width <= mem_stack->length);
      for (int32_t i = 0; i < width; i++) {
        mem_stack->values[mem_id + i] = (void*)(intptr_t)-1;
      }
    }
  }
}

int32_t SPVM_OP_CHECKER_get_mem_id(SPVM_COMPILER* compiler, SPVM_LIST* mem_stack, SPVM_MY* my) {
  
  int32_t found_mem_id = -1;
  
  int32_t width = my->type_width;
  
  // Search free memory
  int32_t found = 0;
  for (int32_t mem_id = 0; mem_id < mem_stack->length; mem_id++) {
    if (mem_id + width <= mem_stack->length) {
      int32_t is_used = 0;
      for (int32_t i = 0; i < width; i++) {
        int32_t my_id = (intptr_t)SPVM_LIST_fetch(mem_stack, mem_id + i);
        if (my_id >= 0) {
          is_used = 1;
          break;
        }
      }
      if (!is_used) {
        found = 1;
        found_mem_id = mem_id;
        for (int32_t i = 0; i < width; i++) {
          mem_stack->values[mem_id + i] = (void*)(intptr_t)my->id;
        }
        break;
      }
    }
    
    if (found) {
      break;
    }
  }
  
  // Add stack
  if (!found) {
    found_mem_id = mem_stack->length;
    for (int32_t i = 0; i < width; i++) {
      SPVM_LIST_push(mem_stack, (void*)(intptr_t)my->id);
    }
  }
  
  return found_mem_id;
}

SPVM_OP* SPVM_OP_CHECKER_new_op_var_tmp(SPVM_COMPILER* compiler, SPVM_SUB* sub, SPVM_TYPE* type, const char* file, int32_t line) {

  // Temparary variable name
  char* name = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, strlen("@tmp2147483647") + 1);
  sprintf(name, "@tmp%d", sub->tmp_vars_length);
  sub->tmp_vars_length++;
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NAME, file, line);
  op_name->uv.name = name;
  SPVM_OP* op_var = SPVM_OP_build_var(compiler, op_name);
  SPVM_MY* my = SPVM_MY_new(compiler);
  SPVM_OP* op_my = SPVM_OP_new_op_my(compiler, my, file, line);
  assert(type);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  SPVM_OP_build_my(compiler, op_my, op_var, op_type);
  
  op_my->uv.my->is_tmp = 1;
  op_var->uv.var->is_initialized = 1;
  
  return op_var;
}

void SPVM_OP_CHECKER_add_no_dup_basic_type(SPVM_COMPILER* compiler, SPVM_OP* op_package, SPVM_OP* op_type) {

  if (SPVM_TYPE_is_object_type(compiler, op_type->uv.type->basic_type->id, op_type->uv.type->dimension, op_type->uv.type->flag)) {
    SPVM_PACKAGE* package = op_package->uv.package;

    SPVM_TYPE* type = op_type->uv.type;

    // Runtime type
    int32_t runtime_basic_type_id;
    int32_t runtime_type_dimension;
    const char* runtime_basic_type_name;
    runtime_basic_type_id = type->basic_type->id;
    runtime_type_dimension = type->dimension;
    runtime_basic_type_name = type->basic_type->name;
    
    // No duplicate basic type id
    SPVM_BASIC_TYPE* found_basic_type = SPVM_HASH_fetch(package->info_basic_type_id_symtable, runtime_basic_type_name, strlen(runtime_basic_type_name));
    if (found_basic_type == NULL) {
      SPVM_LIST_push(package->info_basic_type_ids, (void*)(intptr_t)runtime_basic_type_id);
      SPVM_HASH_insert(package->info_basic_type_id_symtable, runtime_basic_type_name, strlen(runtime_basic_type_name), type->basic_type);
    }
  }
}

void SPVM_OP_CHECKER_check_tree(SPVM_COMPILER* compiler, SPVM_OP* op_root, SPVM_CHECK_AST_INFO* check_ast_info) {

  // Package
  SPVM_PACKAGE* package = check_ast_info->package;
  
  // Sub
  SPVM_SUB* sub = check_ast_info->sub;
  
  // Check tree
  SPVM_OP* op_cur = op_root;
  int32_t finish = 0;
  while (op_cur) {
    // [START]Preorder traversal position
    if (!op_cur->no_need_check) {
      if (op_cur->id == SPVM_OP_C_ID_IF_REQUIRE) {
        SPVM_USE* use = op_cur->first->uv.use;
        SPVM_OP* op_block_true = SPVM_OP_sibling(compiler, op_cur->first);
        SPVM_OP* op_block_false = op_cur->last;
        
        // Execute false block
        if (use->op_type->uv.type->basic_type->fail_load) {
          SPVM_OP_cut_op(compiler, op_block_false);
          SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
          SPVM_OP_replace_op(compiler, op_stab, op_block_false);
          op_cur = op_block_false;
        }
        // Execute true block
        else {
          SPVM_OP_cut_op(compiler, op_block_true);
          SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
          SPVM_OP_replace_op(compiler, op_stab, op_block_true);
          op_cur = op_block_true;
        }
      }
      switch (op_cur->id) {
        // Start scope
        case SPVM_OP_C_ID_BLOCK: {
          int32_t block_my_base = check_ast_info->my_stack->length;
          SPVM_LIST_push(check_ast_info->block_my_base_stack, (void*)(intptr_t)block_my_base);
          
          if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_LOOP_STATEMENTS) {
            check_ast_info->loop_block_stack_length++;
          }
          else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_EVAL) {
            // Eval block max length
            check_ast_info->eval_block_stack_length++;
            if (check_ast_info->eval_block_stack_length > sub->eval_stack_max_length) {
              sub->eval_stack_max_length = check_ast_info->eval_block_stack_length;
            }
          }
          
          break;
        }
        case SPVM_OP_C_ID_SWITCH: {
          SPVM_LIST_push(check_ast_info->op_switch_stack, op_cur);
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
              SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
              
              SPVM_OP* op_list_elements = op_array_init->first;
              SPVM_OP* op_type_new_default = op_array_init->last;
              
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
              op_cur = op_sequence;
              SPVM_OP* op_assign_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, file, line);
              
              // Resolve array type and element type
              int32_t length = 0;
              {
                SPVM_OP* op_term_element = op_list_elements->first;
                int32_t index = 0;
                while ((op_term_element = SPVM_OP_sibling(compiler, op_term_element))) {
                  if (index == 0) {
                    if (op_term_element->id == SPVM_OP_C_ID_UNDEF) {
                      SPVM_COMPILER_error(compiler, "Array initialization first element must not be undef at %s line %d\n", file, line);
                      return;
                    }

                    SPVM_TYPE* type_term_element = SPVM_OP_get_type(compiler, op_term_element);
                    
                    op_term_element->no_need_check = 1;

                    // Create element type
                    if (op_type_element == NULL) {
                      SPVM_TYPE* type_element = SPVM_TYPE_new(compiler);
                      type_element->basic_type = type_term_element->basic_type;
                      type_element->dimension = type_term_element->dimension;
                      op_type_element = SPVM_OP_new_op_type(compiler, type_element, file, line);
                    }
                    
                    if (!SPVM_TYPE_is_numeric_type(compiler, op_type_element->uv.type->basic_type->id,op_type_element->uv.type->dimension, op_type_element->uv.type->flag)) {
                      {
                        SPVM_OP* op_type_tmp = op_type_element;

                        SPVM_OP_CHECKER_add_no_dup_basic_type(compiler, package->op_package, op_type_tmp);
                      }
                    }
                                            
                    // Create array type
                    if (op_type_new == NULL) {
                      SPVM_TYPE* type_new = SPVM_TYPE_new(compiler);
                      type_new->basic_type = type_term_element->basic_type;
                      type_new->dimension = type_term_element->dimension + 1;
                      op_type_new = SPVM_OP_new_op_type(compiler, type_new, file, line);
                    }
                  }
                  index++;
                }
                length = index;
              }
              
              if (length == 0 || op_array_init->flag & SPVM_OP_C_FLAG_ARRAY_INIT_IS_KEY_VALUES) {
                op_type_element = SPVM_OP_new_op_any_object_type(compiler, op_cur->file, op_cur->line);
                SPVM_TYPE* type_element = op_type_element->uv.type;
                SPVM_TYPE* type_new = SPVM_TYPE_new(compiler);
                type_new->basic_type = type_element->basic_type;
                type_new->dimension = type_element->dimension + 1;
                op_type_new = SPVM_OP_new_op_type(compiler, type_new, file, line);
              }

              SPVM_TYPE* type_var_tmp_new = SPVM_TYPE_new(compiler);
              type_var_tmp_new->basic_type =op_type_new->uv.type->basic_type;
              type_var_tmp_new->dimension = op_type_new->uv.type->dimension;
              type_var_tmp_new->flag = op_type_new->uv.type->flag;
              SPVM_OP* op_var_tmp_new = SPVM_OP_CHECKER_new_op_var_tmp(compiler, sub, type_var_tmp_new, file, line);
              
              SPVM_OP_build_assign(compiler, op_assign_new, op_var_tmp_new, op_new);
              SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_assign_new);

              if (length > 0) {
                SPVM_OP* op_term_element = op_list_elements->first;
                int32_t index = 0;
                while ((op_term_element = SPVM_OP_sibling(compiler, op_term_element))) {
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
              }
              
              SPVM_OP_insert_child(compiler, op_new, op_new->last, op_type_new);
              SPVM_OP_insert_child(compiler, op_type_new, op_type_new->last, op_type_element);

              SPVM_OP* op_constant_length = SPVM_OP_new_op_constant_int(compiler, length, file, line);
              SPVM_OP_insert_child(compiler, op_type_new, op_type_new->last, op_constant_length);
              
              SPVM_OP* op_var_tmp_ret = SPVM_OP_new_op_var_clone(compiler, op_var_tmp_new, op_var_tmp_new->file, op_var_tmp_new->line);
              
              SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_var_tmp_ret);

              SPVM_OP_replace_op(compiler, op_stab, op_sequence);
              SPVM_OP_CHECKER_check_tree(compiler, op_sequence, check_ast_info);
              if (compiler->error_count > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_NEXT: {
              if (check_ast_info->loop_block_stack_length == 0) {
                SPVM_COMPILER_error(compiler, "next statement must be in loop block at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              break;
            }
            case SPVM_OP_C_ID_LAST: {
              if (check_ast_info->loop_block_stack_length == 0) {
                SPVM_COMPILER_error(compiler, "last statement must be in loop block at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              break;
            }
            case SPVM_OP_C_ID_BREAK: {
              if (check_ast_info->op_switch_stack->length == 0) {
                SPVM_COMPILER_error(compiler, "break statement must be in switch block or switch block at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              break;
            }
            case SPVM_OP_C_ID_CURRENT_PACKAGE: {
              SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
              SPVM_OP* op_constant = SPVM_OP_new_op_constant_string(compiler, package->name, strlen(package->name), op_cur->file, op_cur->line);

              SPVM_OP_CHECKER_check_tree(compiler, op_constant, check_ast_info);
              if (compiler->error_count > 0) {
                return;
              }

              SPVM_OP_replace_op(compiler, op_stab, op_constant);
              op_cur = op_constant;
              
              break;
            }
            case SPVM_OP_C_ID_REFCNT: {
              
              SPVM_OP* op_term = op_cur->first;
              
              SPVM_TYPE* term_type = SPVM_OP_get_type(compiler, op_term);
              
              // Must be object variable
              if (!(op_term->id == SPVM_OP_C_ID_VAR && SPVM_TYPE_is_object_type(compiler, term_type->basic_type->id, term_type->dimension, term_type->flag))) {
                SPVM_COMPILER_error(compiler, "Operand of refcnt must be variable of object type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_REFOP: {
              
              SPVM_OP* op_term = op_cur->first;
              
              SPVM_TYPE* term_type = SPVM_OP_get_type(compiler, op_term);
              
              // Must be object type
              if (!SPVM_TYPE_is_object_type(compiler, term_type->basic_type->id, term_type->dimension, term_type->flag)) {
                SPVM_COMPILER_error(compiler, "Operand of ref must be object type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_SWITCH: {
              
              SPVM_OP* op_switch_condition = op_cur->first;
              
              SPVM_TYPE* term_type = SPVM_OP_get_type(compiler, op_switch_condition->first);
              
              // Check type
              if (!term_type || !(term_type->dimension == 0 && term_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT)) {
                SPVM_COMPILER_error(compiler, "Switch condition must be int value at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              SPVM_SWITCH_INFO* switch_info = op_cur->uv.switch_info;
              SPVM_LIST* cases = switch_info->case_infos;
              int32_t cases_length = cases->length;
              
              // Need at least one case
              if (cases_length == 0) {
                SPVM_COMPILER_error(compiler, "Switch statement need at least one case statement in  at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Check case type
              {
                int32_t i;
                for (i = 0; i < cases_length; i++) {
                  SPVM_CASE_INFO* case_info = SPVM_LIST_fetch(cases, i);
                  SPVM_OP* op_constant = case_info->op_case_info->first;
                  SPVM_CONSTANT* constant = op_constant->uv.constant;

                  if (op_constant->id != SPVM_OP_C_ID_CONSTANT) {
                    SPVM_COMPILER_error(compiler, "case value must be constant at %s line %d\n", op_cur->file, op_cur->line);
                    return;
                  }

                  // Upgrade byte to int
                  if (constant->type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                    constant->type = SPVM_TYPE_create_int_type(compiler);
                    constant->value.ival = (int32_t)constant->value.bval;
                  }
                  
                  SPVM_TYPE* case_value_type = SPVM_OP_get_type(compiler, op_constant);
                  if (!(case_value_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT && case_value_type->dimension == 0)) {
                    SPVM_COMPILER_error(compiler, "case value must be int constant at %s line %d\n", case_info->op_case_info->file, case_info->op_case_info->line);
                    return;
                  }
                  case_info->constant = constant;
                }
              }

              // sort by asc order
              for (int32_t i = 0; i < switch_info->case_infos->length; i++) {
                for (int32_t j = i + 1; j < switch_info->case_infos->length; j++) {
                  SPVM_CASE_INFO* case_i = SPVM_LIST_fetch(switch_info->case_infos, i);
                  SPVM_CASE_INFO* case_j = SPVM_LIST_fetch(switch_info->case_infos, j);
                  int32_t match_i = case_i->constant->value.ival;
                  int32_t match_j = case_j->constant->value.ival;
                  
                  if (match_i > match_j) {
                    SPVM_LIST_store(switch_info->case_infos, i, case_j);
                    SPVM_LIST_store(switch_info->case_infos, j, case_i);
                  }
                }
              }
              
              SPVM_LIST_pop(check_ast_info->op_switch_stack);

              op_cur->uv.switch_info->switch_id = package->info_switch_infos->length;
              SPVM_LIST_push(package->info_switch_infos, op_cur->uv.switch_info);
              
              // Min
              SPVM_CASE_INFO* case_info_mini = SPVM_LIST_fetch(switch_info->case_infos, 0);
              int32_t min = case_info_mini->constant->value.ival;
              
              // Max
              SPVM_CASE_INFO* case_info_max = SPVM_LIST_fetch(switch_info->case_infos, switch_info->case_infos->length - 1);
              int32_t max = case_info_max->constant->value.ival;
              
              // Decide switch type
              switch_info->id = SPVM_SWITCH_INFO_C_ID_LOOKUP_SWITCH;
              
              break;
            }
            case SPVM_OP_C_ID_CASE: {
              if (check_ast_info->op_switch_stack->length > 0) {
                SPVM_OP* op_switch = SPVM_LIST_fetch(check_ast_info->op_switch_stack, check_ast_info->op_switch_stack->length - 1);
                SPVM_SWITCH_INFO* switch_info = op_switch->uv.switch_info;
                op_cur->uv.case_info->index = switch_info->case_infos->length;
                SPVM_LIST_push(switch_info->case_infos, op_cur->uv.case_info);
              }
              break;
            }
            case SPVM_OP_C_ID_DEFAULT: {
              if (check_ast_info->op_switch_stack->length > 0) {
                SPVM_OP* op_switch = SPVM_LIST_fetch(check_ast_info->op_switch_stack, check_ast_info->op_switch_stack->length - 1);
                SPVM_SWITCH_INFO* switch_info = op_switch->uv.switch_info;
                
                if (switch_info->op_default) {
                  SPVM_COMPILER_error(compiler, "Duplicate default statement at %s line %d\n", op_cur->file, op_cur->line);
                  return;
                }
                else {
                  switch_info->op_default = op_cur;
                }
              }
              break;
            }
            case SPVM_OP_C_ID_BOOL: {
              SPVM_OP* op_first = op_cur->first;
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              int32_t is_valid_type;
                
              // undef type
              if (SPVM_TYPE_is_undef_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                
                is_valid_type = 1;
                
                // Return constant 0
                SPVM_OP* op_false = SPVM_OP_new_op_constant_int(compiler, 0, op_first->file, op_first->line);
                SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_first);
                SPVM_OP_replace_op(compiler, op_stab, op_false);
                SPVM_OP_CHECKER_check_tree(compiler, op_false, check_ast_info);
                if (compiler->error_count > 0) {
                  return;
                }
              }
              // Numeric type
              else if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag))
              {
                // Convert byte or short type to int type
                SPVM_OP_CHECKER_apply_unary_numeric_widening_convertion(compiler, op_first);
                if (compiler->error_count > 0) {
                  return;
                }
                is_valid_type = 1;
              }
              // Object type
              else if (SPVM_TYPE_is_object_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                is_valid_type = 1;
              }
              else {
                is_valid_type = 0;
              }
              
              if (!is_valid_type) {
                SPVM_COMPILER_error(compiler, "Operand of condition must be numeric type or object type or undef type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_NUMERIC_EQ: {
              SPVM_OP* op_first = op_cur->first;

              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // undef == undef
              if (SPVM_TYPE_is_undef_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_undef_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                
                // Return constant 1
                SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                SPVM_OP* op_true = SPVM_OP_new_op_constant_int(compiler, 1, op_first->file, op_first->line);
                SPVM_OP* op_assign_bool = SPVM_OP_new_op_assign_bool(compiler, op_true, op_first->file, op_first->line);
                op_cur = op_assign_bool;
                SPVM_OP_replace_op(compiler, op_stab, op_assign_bool);
                SPVM_OP_CHECKER_check_tree(compiler, op_assign_bool, check_ast_info);
                if (compiler->error_count > 0) {
                  return;
                }
              }
              // expression == undef
              else if (!SPVM_TYPE_is_undef_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_undef_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                if (!SPVM_TYPE_is_object_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                  SPVM_COMPILER_error(compiler, "Left operand of == operator must be object type at %s line %d\n", op_cur->file, op_cur->line);
                  return;
                }
              }
              // undef == expression
              else if (SPVM_TYPE_is_undef_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && !SPVM_TYPE_is_undef_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                if (!SPVM_TYPE_is_object_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                  SPVM_COMPILER_error(compiler, "Right operand of == operator must be object type at %s line %d\n", op_cur->file, op_cur->line);
                  return;
                }
              }
              // expression == expression
              else {
                int32_t is_valid_type;
                
                // Numeric type
                if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                  
                  is_valid_type = 1;
                  
                  SPVM_OP_CHECKER_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
                  if (compiler->error_count > 0) {
                    return;
                  }
                }
                // Object type
                else if (SPVM_TYPE_is_object_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_object_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                  is_valid_type = 1;
                }
                else {
                  is_valid_type = 0;
                }
                
                if (!is_valid_type) {
                  SPVM_COMPILER_error(compiler, "Left and right operand of == operator must be numeric type or object type at %s line %d\n", op_cur->file, op_cur->line);
                  return;
                }
              }
              
              break;
            }
            case SPVM_OP_C_ID_NUMERIC_NE: {
              SPVM_OP* op_first = op_cur->first;

              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // undef == undef
              if (SPVM_TYPE_is_undef_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_undef_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                
                // Return constant 0
                SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                SPVM_OP* op_false = SPVM_OP_new_op_constant_int(compiler, 0, op_first->file, op_first->line);
                SPVM_OP* op_assign_bool = SPVM_OP_new_op_assign_bool(compiler, op_false, op_first->file, op_first->line);
                op_cur = op_assign_bool;
                SPVM_OP_replace_op(compiler, op_stab, op_assign_bool);
                SPVM_OP_CHECKER_check_tree(compiler, op_assign_bool, check_ast_info);
                if (compiler->error_count > 0) {
                  return;
                }
              }
              // expression == undef
              else if (!SPVM_TYPE_is_undef_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_undef_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                if (!SPVM_TYPE_is_object_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                  SPVM_COMPILER_error(compiler, "Left operand of == operator must be object type at %s line %d\n", op_cur->file, op_cur->line);
                  return;
                }
              }
              // undef == expression
              else if (SPVM_TYPE_is_undef_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && !SPVM_TYPE_is_undef_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                if (!SPVM_TYPE_is_object_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                  SPVM_COMPILER_error(compiler, "Right operand of == operator must be object type at %s line %d\n", op_cur->file, op_cur->line);
                  return;
                }
              }
              // expression == expression
              else {
                int32_t is_valid_type;
                
                // Numeric type
                if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                  
                  is_valid_type = 1;
                  
                  SPVM_OP_CHECKER_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
                  if (compiler->error_count > 0) {
                    return;
                  }
                }
                // Object type
                else if (SPVM_TYPE_is_object_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_object_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                  is_valid_type = 1;
                }
                else {
                  is_valid_type = 0;
                }
                
                if (!is_valid_type) {
                  SPVM_COMPILER_error(compiler, "Left and right operand of == operator must be numeric type or object type at %s line %d\n", op_cur->file, op_cur->line);
                  return;
                }
              }
              
              break;
            }
            case SPVM_OP_C_ID_NUMERIC_GT: {

              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

              // Left operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Left operand of > operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of > operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Apply binary numeric convertion
              SPVM_OP_CHECKER_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
              if (compiler->error_count > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_NUMERIC_GE: {

              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

              // Left operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Left operand of >= operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of >= operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Apply binary numeric convertion
              SPVM_OP_CHECKER_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
              if (compiler->error_count > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_NUMERIC_LT: {

              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Left operand of < operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of < operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Apply binary numeric convertion
              SPVM_OP_CHECKER_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
              if (compiler->error_count > 0) {
                return;
              }

              break;
            }
            case SPVM_OP_C_ID_NUMERIC_LE: {

              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

              // Left operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Left operand of <= operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of <= operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Apply binary numeric convertion
              SPVM_OP_CHECKER_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
              if (compiler->error_count > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_NUMERIC_CMP: {

              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

              // Left operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Left operand of > operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of > operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Apply binary numeric convertion
              SPVM_OP_CHECKER_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
              if (compiler->error_count > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_STRING_EQ: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be string type
              if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Left operand of eq operator must be string type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be string type
              if (!SPVM_TYPE_is_string_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of eq operator must be string type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_STRING_NE: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be string type
              if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Left operand of eq operator must be string type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be string type
              if (!SPVM_TYPE_is_string_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of eq operator must be string type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_STRING_GT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be string type
              if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Left operand of eq operator must be string type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be string type
              if (!SPVM_TYPE_is_string_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of eq operator must be string type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_STRING_GE: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be string type
              if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Left operand of eq operator must be string type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be string type
              if (!SPVM_TYPE_is_string_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of eq operator must be string type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_STRING_LT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be string type
              if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Left operand of eq operator must be string type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be string type
              if (!SPVM_TYPE_is_string_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of eq operator must be string type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_STRING_LE: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be string type
              if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Left operand of eq operator must be string type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be string type
              if (!SPVM_TYPE_is_string_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of eq operator must be string type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_STRING_CMP: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be string type
              if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Left operand of eq operator must be string type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be string type
              if (!SPVM_TYPE_is_string_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of eq operator must be string type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_NEW: {
              assert(op_cur->first);
              if (op_cur->first->id == SPVM_OP_C_ID_TYPE) {
                SPVM_OP* op_type = op_cur->first;
                SPVM_TYPE* type = op_type->uv.type;
                
                SPVM_PACKAGE* new_package = type->basic_type->package;
                
                // Anon sub
                if (new_package && new_package->flag & SPVM_PACKAGE_C_FLAG_ANON_SUB_PACKAGE) {
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
                    
                    SPVM_OP* op_new = op_cur;
                    
                    op_new->no_need_check = 1;
                  
                    const char* file = op_new->file;
                    int32_t line = op_new->line;
                    
                    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                    
                    SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, file, line);
                    SPVM_OP* op_assign_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, file, line);
                    SPVM_TYPE* type_var_tmp_new = SPVM_TYPE_new(compiler);
                    type_var_tmp_new->basic_type = op_type->uv.type->basic_type;
                    type_var_tmp_new->dimension = op_type->uv.type->dimension;
                    type_var_tmp_new->flag = op_type->uv.type->flag;
                    SPVM_OP* op_var_tmp_new = SPVM_OP_CHECKER_new_op_var_tmp(compiler, sub, type_var_tmp_new, file, line);
                    
                    SPVM_OP_build_assign(compiler, op_assign_new, op_var_tmp_new, op_new);

                    SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_assign_new);
                    
                    // Check capture variable exists
                    for (int32_t caputre_index = 0; caputre_index < anon_sub->captures->length; caputre_index++) {
                      SPVM_MY* capture_my = SPVM_LIST_fetch(anon_sub->captures, caputre_index);
                      const char* capture_name = capture_my->op_name->uv.name;

                      // Search same name variable
                      SPVM_MY* found_my = NULL;
                      for (int32_t stack_my_index = check_ast_info->my_stack->length - 1; stack_my_index >= 0; stack_my_index--) {
                        SPVM_MY* my = SPVM_LIST_fetch(check_ast_info->my_stack, stack_my_index);
                        if (strcmp(capture_name, my->op_name->uv.name) == 0) {
                          found_my = my;
                          break;
                        }
                      }
                      if (!found_my) {
                        SPVM_COMPILER_error(compiler, "Capture variable \"%s\" is not declared at %s line %d\n", capture_name, op_cur->file, op_cur->line);
                        return;
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
                    
                    SPVM_OP_CHECKER_check_tree(compiler, op_sequence, check_ast_info);
                    if (compiler->error_count > 0) {
                      return;
                    }

                    // Add type info to constant pool
                    SPVM_OP_CHECKER_add_no_dup_basic_type(compiler, package->op_package, op_type);
                  }
                }
                // Array type
                else if (SPVM_TYPE_is_array_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                  
                  SPVM_OP* op_index_term = op_type->last;

                  SPVM_TYPE* index_type = SPVM_OP_get_type(compiler, op_index_term);
                  
                  assert(index_type);
                  if (SPVM_TYPE_is_numeric_type(compiler, index_type->basic_type->id, index_type->dimension, index_type->flag)) {
                    SPVM_OP_CHECKER_apply_unary_numeric_widening_convertion(compiler, op_index_term);
                    if (compiler->error_count > 0) {
                      return;
                    }
                    
                    SPVM_TYPE* index_type = SPVM_OP_get_type(compiler, op_index_term);
                    
                    if (!(index_type->dimension == 0 && index_type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_BYTE && index_type->basic_type->id <= SPVM_BASIC_TYPE_C_ID_INT)) {
                      const char* type_name = SPVM_TYPE_new_type_name(compiler, type->basic_type->id, type->dimension, type->flag);
                      SPVM_COMPILER_error(compiler, "new operator can't create array which don't have int length \"%s\" at %s line %d\n", type_name, op_cur->file, op_cur->line);
                      return;
                    }
                  }
                  else {
                    const char* type_name = SPVM_TYPE_new_type_name(compiler, type->basic_type->id, type->dimension, type->flag);
                    SPVM_COMPILER_error(compiler, "new operator can't create array which don't have numeric length \"%s\" at %s line %d\n", type_name, op_cur->file, op_cur->line);
                    return;
                  }
                }
                // Numeric type
                else if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                  SPVM_COMPILER_error(compiler, "new operator can't receive numeric type at %s line %d\n", op_cur->file, op_cur->line);
                  return;
                }
                // Object type
                else if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                  SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, type->basic_type->name, strlen(type->basic_type->name));
                  
                  if (package->category == SPVM_PACKAGE_C_CATEGORY_CALLBACK) {
                    SPVM_COMPILER_error(compiler, "Can't create object of callback package at %s line %d\n", op_cur->file, op_cur->line);
                    return;
                  }
                  else if (package->category == SPVM_PACKAGE_C_CATEGORY_MULNUM) {
                    SPVM_COMPILER_error(compiler, "Can't create object of mulnum_t package at %s line %d\n", op_cur->file, op_cur->line);
                    return;
                  }
                  else if (package->flag & SPVM_PACKAGE_C_FLAG_POINTER) {
                    SPVM_COMPILER_error(compiler, "Can't create object of struct package at %s line %d\n", op_cur->file, op_cur->line);
                    return;
                  }
                  
                  // Access control
                  int32_t is_private;
                  if (package->flag & SPVM_PACKAGE_C_FLAG_PUBLIC) {
                    is_private = 0;
                  }
                  // Default
                  else {
                    is_private = 1;
                  }
                  
                  if (is_private && !(op_cur->flag & SPVM_OP_C_FLAG_NEW_INLINE)) {
                    if (!SPVM_OP_is_allowed(compiler, sub->package->op_package, new_package->op_package)) {
                      SPVM_COMPILER_error(compiler, "Can't create object of private package at %s line %d\n", op_cur->file, op_cur->line);
                      return;
                    }
                  }
                }
                else {
                  assert(0);
                }
                
                // Add type info to constant pool
                SPVM_OP_CHECKER_add_no_dup_basic_type(compiler, package->op_package, op_type);
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
                SPVM_COMPILER_error(compiler, "^ operator can receive only integral type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              SPVM_OP_CHECKER_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
              if (compiler->error_count > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_ISA: {
              SPVM_TYPE* term_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_OP* op_type = op_cur->last;
              
              SPVM_TYPE* check_type = op_type->uv.type;
              
              int32_t compile_time_check;
              if (SPVM_TYPE_is_numeric_type(compiler, check_type->basic_type->id, check_type->dimension, check_type->flag)) {
                compile_time_check = 1;
              }
              else if (SPVM_TYPE_is_multi_numeric_type(compiler, check_type->basic_type->id, check_type->dimension, check_type->flag)) {
                compile_time_check = 1;
              }
              else if (SPVM_TYPE_is_any_object_type(compiler, check_type->basic_type->id, check_type->dimension, check_type->flag)) {
                compile_time_check = 1;
              }
              else if (SPVM_TYPE_is_ref_type(compiler, check_type->basic_type->id, check_type->dimension, check_type->flag)) {
                compile_time_check = 1;
              }
              else {
                compile_time_check = 0;
              }
              if (compile_time_check) {
                // If left type is same as right type, this return true, otherwise return false
                if (term_type->basic_type->id == check_type->basic_type->id && term_type->dimension == check_type->dimension) {
                  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                  SPVM_OP* op_constant_true = SPVM_OP_new_op_constant_int(compiler, 1, op_cur->file, op_cur->line);
                  SPVM_OP* op_assign_bool = SPVM_OP_new_op_assign_bool(compiler, op_constant_true, op_cur->file, op_cur->line);
                  SPVM_OP_replace_op(compiler, op_stab, op_assign_bool);
                  SPVM_OP_CHECKER_check_tree(compiler, op_assign_bool, check_ast_info);
                  if (compiler->error_count > 0) {
                    return;
                  }
                  op_cur = op_assign_bool;
                }
                else {
                  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                  SPVM_OP* op_constant_false = SPVM_OP_new_op_constant_int(compiler, 0, op_cur->file, op_cur->line);
                  SPVM_OP* op_assign_bool = SPVM_OP_new_op_assign_bool(compiler, op_constant_false, op_cur->file, op_cur->line);
                  SPVM_OP_replace_op(compiler, op_stab, op_assign_bool);
                  SPVM_OP_CHECKER_check_tree(compiler, op_assign_bool, check_ast_info);
                  if (compiler->error_count > 0) {
                    return;
                  }
                  op_cur = op_assign_bool;
                }
              }
              else {
                // Left term must be object type
                if (!SPVM_TYPE_is_object_type(compiler, term_type->basic_type->id, term_type->dimension, term_type->flag)) {
                  SPVM_COMPILER_error(compiler, "Left operand of isa operator must be object type at %s line %d\n", op_cur->file, op_cur->line);
                  return;
                }
                
                // Right type must be object type
                if (!SPVM_TYPE_is_object_type(compiler, check_type->basic_type->id, check_type->dimension, check_type->flag)) {
                  SPVM_COMPILER_error(compiler, "Right operand of isa operator must be object type at %s line %d\n", op_cur->file, op_cur->line);
                  return;
                }

                // Add type info to constant pool
                SPVM_OP_CHECKER_add_no_dup_basic_type(compiler, package->op_package, op_type);
              }
              
              break;
            }
            case SPVM_OP_C_ID_ARRAY_LENGTH: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              // First value must be array
              if (!SPVM_TYPE_is_array_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of @ operator must be array type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_STRING_LENGTH: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              // First must be string type
              if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "length argument must be string type at %s line %d\n", op_cur->file, op_cur->line);
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
                SPVM_COMPILER_error(compiler, "increment operand must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
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
              SPVM_OP_build_binary_op(compiler, op_add, op_term_mutable, op_constant);
              
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
              
              op_cur = op_assign;
              
              SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
              if (compiler->error_count > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_PRE_DEC:
            {
              SPVM_OP* op_first = op_cur->first;
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_first);
              
              // Numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "decrement operand must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
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
              SPVM_OP_build_binary_op(compiler, op_subtract, op_term_mutable, op_constant);
              
              SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
              
              SPVM_TYPE* term_mutable_type = SPVM_OP_get_type(compiler, op_term_mutable);
              if (SPVM_TYPE_is_byte_type(compiler, term_mutable_type->basic_type->id, term_mutable_type->dimension, term_mutable_type->flag)
                || SPVM_TYPE_is_short_type(compiler, term_mutable_type->basic_type->id, term_mutable_type->dimension, term_mutable_type->flag))
              {
                SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, op_cur->file, op_cur->line);
                SPVM_OP* op_dist_type = SPVM_OP_new_op_type(compiler, term_mutable_type, op_cur->file, op_cur->line);
                SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_subtract);
                SPVM_OP_build_assign(compiler, op_assign, op_term_mutable_clone, op_convert);
              }
              else {
                SPVM_OP_build_assign(compiler, op_assign, op_term_mutable_clone, op_subtract);
              }
              
              SPVM_OP_replace_op(compiler, op_stab, op_assign);
              
              op_cur = op_assign;
              
              SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
              if (compiler->error_count > 0) {
                return;
              }
              break;
            }
            case SPVM_OP_C_ID_POST_INC:
            {
              SPVM_OP* op_first = op_cur->first;
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_first);
              
              // Numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "increment operand must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
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
              SPVM_OP* op_var_tmp1 = SPVM_OP_CHECKER_new_op_var_tmp(compiler, sub, term_mutable_type, op_cur->file, op_cur->line);

              SPVM_OP* op_var_tmp2 = SPVM_OP_new_op_var_clone(compiler, op_var_tmp1, op_cur->file, op_cur->line);
        
              SPVM_OP* op_assign_tmp = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
              SPVM_OP_build_assign(compiler, op_assign_tmp, op_var_tmp1, op_term_mutable);

              SPVM_OP* op_add = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, op_cur->file, op_cur->line);
              SPVM_OP* op_constant = SPVM_OP_new_op_constant_int(compiler, 1, op_cur->file, op_cur->line);
              SPVM_OP_build_binary_op(compiler, op_add, op_var_tmp2, op_constant);
              SPVM_OP* op_assign_add = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
              
              SPVM_OP* op_term_mutable_clone = SPVM_OP_new_op_term_mutable_clone(compiler, op_term_mutable);
              if (SPVM_TYPE_is_byte_type(compiler, term_mutable_type->basic_type->id, term_mutable_type->dimension, term_mutable_type->flag)
                || SPVM_TYPE_is_short_type(compiler, term_mutable_type->basic_type->id, term_mutable_type->dimension, term_mutable_type->flag))
              {
                SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, op_cur->file, op_cur->line);
                SPVM_OP* op_dist_type = SPVM_OP_new_op_type(compiler, term_mutable_type, op_cur->file, op_cur->line);
                SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_add);
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
              
              op_cur = op_sequence;
              
              SPVM_OP_CHECKER_check_tree(compiler, op_sequence, check_ast_info);
              if (compiler->error_count > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_POST_DEC:
            {
              SPVM_OP* op_first = op_cur->first;
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_first);
              
              // Numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "decrement operand must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
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
              
              SPVM_OP* op_var_tmp1 = SPVM_OP_CHECKER_new_op_var_tmp(compiler, sub, term_mutable_type, op_cur->file, op_cur->line);
              
              SPVM_OP* op_var_tmp2 = SPVM_OP_new_op_var_clone(compiler, op_var_tmp1, op_cur->file, op_cur->line);
        
              SPVM_OP* op_assign_tmp = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
              SPVM_OP_build_assign(compiler, op_assign_tmp, op_var_tmp1, op_term_mutable);

              SPVM_OP* op_subtract = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, op_cur->file, op_cur->line);
              SPVM_OP* op_constant = SPVM_OP_new_op_constant_int(compiler, 1, op_cur->file, op_cur->line);
              SPVM_OP_build_binary_op(compiler, op_subtract, op_var_tmp2, op_constant);
              SPVM_OP* op_assign_subtract = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
              
              SPVM_OP* op_term_mutable_clone = SPVM_OP_new_op_term_mutable_clone(compiler, op_term_mutable);
              if (SPVM_TYPE_is_byte_type(compiler, term_mutable_type->basic_type->id, term_mutable_type->dimension, term_mutable_type->flag)
                || SPVM_TYPE_is_short_type(compiler, term_mutable_type->basic_type->id, term_mutable_type->dimension, term_mutable_type->flag))
              {
                SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, op_cur->file, op_cur->line);
                SPVM_OP* op_dist_type = SPVM_OP_new_op_type(compiler, term_mutable_type, op_cur->file, op_cur->line);
                SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_subtract);
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
              
              op_cur = op_sequence;
              
              SPVM_OP_CHECKER_check_tree(compiler, op_sequence, check_ast_info);
              if (compiler->error_count > 0) {
                return;
              }
              
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
                case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_ARITHMETIC_SHIFT:
                  culc_op_id = SPVM_OP_C_ID_RIGHT_ARITHMETIC_SHIFT;
                  break;
                case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_LOGICAL_SHIFT:
                  culc_op_id = SPVM_OP_C_ID_RIGHT_LOGICAL_SHIFT;
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
              
              SPVM_OP_build_binary_op(compiler, op_culc, op_term_mutable, op_term_src);
              
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
                case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_ARITHMETIC_SHIFT:
                case SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_LOGICAL_SHIFT:
                  if (SPVM_TYPE_is_byte_type(compiler, term_mutable_type->basic_type->id, term_mutable_type->dimension, term_mutable_type->flag)
                    || SPVM_TYPE_is_short_type(compiler, term_mutable_type->basic_type->id, term_mutable_type->dimension, term_mutable_type->flag))
                  {
                    need_conversion = 1;
                  }
                  break;
              }
              
              if (need_conversion) {
                SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, op_cur->file, op_cur->line);
                SPVM_OP* op_dist_type = SPVM_OP_new_op_type(compiler, term_mutable_type, op_cur->file, op_cur->line);
                SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_culc);
                SPVM_OP_build_assign(compiler, op_assign, op_term_mutable_clone, op_convert);
              }
              else {
                SPVM_OP_build_assign(compiler, op_assign, op_term_mutable_clone, op_culc);
              }
              
              SPVM_OP_replace_op(compiler, op_stab, op_assign);
              
              op_cur = op_assign;
              
              SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
              if (compiler->error_count > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_ASSIGN: {
              SPVM_OP* op_term_dist = op_cur->last;
              SPVM_OP* op_term_src = op_cur->first;
              
              SPVM_TYPE* dist_type = SPVM_OP_get_type(compiler, op_term_dist);

              // Type inference
              if (op_term_dist->id == SPVM_OP_C_ID_VAR) {
                SPVM_MY* my = op_term_dist->uv.var->my;
                if (my->type == NULL) {
                  my->type = SPVM_OP_get_type(compiler, op_term_src);
                }
                if (my->type == NULL) {
                  SPVM_COMPILER_error(compiler, "Type can't be detected at %s line %d\n", my->op_my->file, my->op_my->line);
                  return;
                }
                op_term_dist->uv.var->is_initialized = 1;
              }
              
              // Check if source can be assigned to dist
              // If needed, numeric convertion op is added
              dist_type = SPVM_OP_get_type(compiler, op_term_dist);
              SPVM_OP_CHECKER_check_assign(compiler, dist_type, op_term_src, "assign operator", op_cur->file, op_cur->line);
              if (compiler->error_count > 0) {
                return;
              }

              // If dist is string access and const, it is invalid
              if (op_term_dist->id == SPVM_OP_C_ID_ARRAY_ACCESS && op_term_dist->flag & SPVM_OP_C_FLAG_ARRAY_ACCESS_CONST) {
                SPVM_COMPILER_error(compiler, "Can't change each character of string at %s line %d\n", op_term_dist->file, op_term_dist->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_RETURN: {
              
              SPVM_OP* op_term = op_cur->first;
              
              // Void type
              if (SPVM_TYPE_is_void_type(compiler, sub->return_type->basic_type->id, sub->return_type->dimension, sub->return_type->flag)) {
                if (op_term) {
                  SPVM_COMPILER_error(compiler, "void subroutine must not have return value at %s line %d\n", op_cur->file, op_cur->line);
                  return;
                }
              }
              else {
                if (op_term) {
                  // Automatical numeric convertion
                  SPVM_OP_CHECKER_check_assign(compiler, sub->return_type, op_term, "return statement", op_cur->file, op_cur->line);
                  if (compiler->error_count > 0) {
                    return;
                  }
                }
                else {
                  SPVM_COMPILER_error(compiler, "non-void subroutine must have return value at %s line %d\n", op_cur->file, op_cur->line);
                  return;
                }
              }

              break;
            }
            case SPVM_OP_C_ID_PLUS: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              // Operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Operand of unary + operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Apply unary widening convertion
              SPVM_OP_CHECKER_apply_unary_numeric_widening_convertion(compiler, op_cur->first);
              if (compiler->error_count > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_MINUS: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              // Operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Operand of unary - operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // Apply unary widening convertion
              SPVM_OP_CHECKER_apply_unary_numeric_widening_convertion(compiler, op_cur->first);
              if (compiler->error_count > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_BIT_NOT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              // Operand must be numeric type
              if (!SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Operand of ~ operator must be integral type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Apply unary widening convertion
              SPVM_OP_CHECKER_apply_unary_numeric_widening_convertion(compiler, op_cur->first);
              if (compiler->error_count > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_ADD: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Left operand of + operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of + operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // Apply binary numeric convertion
              SPVM_OP_CHECKER_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
              if (compiler->error_count > 0) {
                return;
              }
                                              
              break;
            }
            case SPVM_OP_C_ID_SUBTRACT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Left operand of - operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of - operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // Apply binary numeric convertion
              SPVM_OP_CHECKER_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
              if (compiler->error_count > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_MULTIPLY: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Left operand of * operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of * operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Apply binary numeric convertion
              SPVM_OP_CHECKER_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
              if (compiler->error_count > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_DIVIDE: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Left operand of / operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of / operator must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // Apply binary numeric convertion
              SPVM_OP_CHECKER_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
              if (compiler->error_count > 0) {
                return;
              }

              break;
            }
            case SPVM_OP_C_ID_REMAINDER: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be integral type
              if (!SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Left operand of %% operator must be integral type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be integral type
              if (!SPVM_TYPE_is_integral_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of %% operator must be integral type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // Apply binary numeric convertion
              SPVM_OP_CHECKER_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
              if (compiler->error_count > 0) {
                return;
              }
                                              
              break;
            }
            case SPVM_OP_C_ID_BIT_AND: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be integral type
              if (!SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Left operand of & operator must be integral type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be integral type
              if (!SPVM_TYPE_is_integral_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of & operator must be integral type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              SPVM_OP_CHECKER_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
              if (compiler->error_count > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_BIT_OR: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be integral type
              if (!SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Left operand of | operator must be integral type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be integral type
              if (!SPVM_TYPE_is_integral_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "Right operand of | operator must be integral type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              SPVM_OP_CHECKER_apply_binary_numeric_convertion(compiler, op_cur->first, op_cur->last);
              if (compiler->error_count > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_LEFT_SHIFT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_OP_CHECKER_apply_unary_numeric_widening_convertion(compiler, op_cur->first);
                if (compiler->error_count > 0) {
                  return;
                }
              }
              else {
                SPVM_COMPILER_error(compiler, "Left operand of << operator must be integral type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be int type
              if (SPVM_TYPE_is_integral_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_OP_CHECKER_apply_unary_numeric_widening_convertion(compiler, op_cur->last);
                if (compiler->error_count > 0) {
                  return;
                }
                
                if (last_type->dimension == 0 && last_type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_LONG) {
                  SPVM_COMPILER_error(compiler, "Right operand of << operator must be int type at %s line %d\n", op_cur->file, op_cur->line);
                  return;
                }
              }
              else {
                SPVM_COMPILER_error(compiler, "Right operand of << operator must be int type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_RIGHT_ARITHMETIC_SHIFT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_OP_CHECKER_apply_unary_numeric_widening_convertion(compiler, op_cur->first);
                if (compiler->error_count > 0) {
                  return;
                }
              }
              else {
                SPVM_COMPILER_error(compiler, "Left operand of >> operator must be integral type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be int type
              if (SPVM_TYPE_is_integral_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_OP_CHECKER_apply_unary_numeric_widening_convertion(compiler, op_cur->last);
                if (compiler->error_count > 0) {
                  return;
                }
                
                if (last_type->dimension == 0 && last_type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_LONG) {
                  SPVM_COMPILER_error(compiler, "Right operand of >> operator must be int type at %s line %d\n", op_cur->file, op_cur->line);
                  return;
                }
              }
              else {
                SPVM_COMPILER_error(compiler, "Right operand of >> operator must be int type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_RIGHT_LOGICAL_SHIFT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_OP_CHECKER_apply_unary_numeric_widening_convertion(compiler, op_cur->first);
                if (compiler->error_count > 0) {
                  return;
                }
              }
              else {
                SPVM_COMPILER_error(compiler, "Left operand of >>> operator must be integral type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be int type
              if (SPVM_TYPE_is_integral_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_OP_CHECKER_apply_unary_numeric_widening_convertion(compiler, op_cur->last);
                if (compiler->error_count > 0) {
                  return;
                }
                
                if (last_type->dimension == 0 && last_type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_LONG) {
                  SPVM_COMPILER_error(compiler, "Right operand of >>> operator must be int type at %s line %d\n", op_cur->file, op_cur->line);
                  return;
                }
              }
              else {
                SPVM_COMPILER_error(compiler, "Right operand of >>> operator must be int type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_CONCAT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left type is numeric type
              if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_OP_CHECKER_apply_numeric_to_string_convertion(compiler, op_cur->first);
                if (compiler->error_count > 0) {
                  return;
                }
              }
              // Left type is not string type
              else if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "\".\" operator left value must be string type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand is numeric type
              if (SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_OP_CHECKER_apply_numeric_to_string_convertion(compiler, op_cur->last);
                if (compiler->error_count > 0) {
                  return;
                }
              }
              // Right operand is not string type
              else if (!SPVM_TYPE_is_string_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "\".\" operator right value must be string type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // If . left and right is both string literal, concat them at compile time
              if (op_cur->first->id == SPVM_OP_C_ID_CONSTANT && op_cur->last->id == SPVM_OP_C_ID_CONSTANT) {
                SPVM_OP* op_constant_string1 = op_cur->first;
                int32_t string1_length = op_constant_string1->uv.constant->string_length;
                const char* string1 = op_constant_string1->uv.constant->value.oval;
                
                SPVM_OP* op_constant_string2 = op_cur->last;
                int32_t string2_length = op_constant_string2->uv.constant->string_length;
                const char* string2 = op_constant_string2->uv.constant->value.oval;
                
                SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                
                char* concat_string = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, string1_length + string2_length + 1);
                memcpy(concat_string, string1, string1_length);
                memcpy(concat_string + string1_length, string2, string2_length);
                int32_t concant_string_length = string1_length + string2_length;
                SPVM_OP* op_concat_constant_string = SPVM_OP_new_op_constant_string(compiler, concat_string, concant_string_length, op_cur->file, op_cur->line);
                
                SPVM_OP_replace_op(compiler, op_stab, op_concat_constant_string);
                
                op_cur = op_concat_constant_string;
              }
              
              break;
            }
            case SPVM_OP_C_ID_DIE: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);

              if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_OP_CHECKER_apply_numeric_to_string_convertion(compiler, op_cur->first);
                if (compiler->error_count > 0) {
                  return;
                }
              }
              
              first_type = SPVM_OP_get_type(compiler, op_cur->first);

              if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "die argument must be string type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              break;
            }
            case SPVM_OP_C_ID_WARN: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_OP_CHECKER_apply_numeric_to_string_convertion(compiler, op_cur->first);
                if (compiler->error_count > 0) {
                  return;
                }
              }
              
              first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "warn argument must be string type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              break;
            }
            case SPVM_OP_C_ID_PRINT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_OP_CHECKER_apply_numeric_to_string_convertion(compiler, op_cur->first);
                if (compiler->error_count > 0) {
                  return;
                }
              }
              
              first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "print argument must be string type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              break;
            }
            // End of scope
            case SPVM_OP_C_ID_BLOCK: {
              // Pop block my variable base
              assert(check_ast_info->block_my_base_stack->length > 0);
              int32_t block_my_base = (intptr_t)SPVM_LIST_pop(check_ast_info->block_my_base_stack);
                
              int32_t my_stack_pop_count = check_ast_info->my_stack->length - block_my_base;
              
              {
                int32_t i;
                for (i = 0; i < my_stack_pop_count; i++) {
                  SPVM_LIST_pop(check_ast_info->my_stack);
                }
              }

              // Pop loop block my variable base
              if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_LOOP_STATEMENTS) {
                check_ast_info->loop_block_stack_length--;
              }
              // Pop try block my variable base
              else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_EVAL) {
                check_ast_info->eval_block_stack_length--;
              }
              
              break;
            }
            case SPVM_OP_C_ID_CREATE_REF: {
              
              SPVM_OP* op_var = op_cur->first;
              SPVM_TYPE* var_type = SPVM_OP_get_type(compiler, op_var);
              if (!(SPVM_TYPE_is_numeric_type(compiler, var_type->basic_type->id, var_type->dimension, var_type->flag) || SPVM_TYPE_is_multi_numeric_type(compiler, var_type->basic_type->id, var_type->dimension, var_type->flag))) {
                SPVM_COMPILER_error(compiler, "Refernece target must be numeric type or multi numeric type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_DEREF: {
              SPVM_OP* op_var = op_cur->first;
              SPVM_TYPE* var_type = SPVM_OP_get_type(compiler, op_var);
              
              if (!(SPVM_TYPE_is_numeric_ref_type(compiler, var_type->basic_type->id, var_type->dimension, var_type->flag) || SPVM_TYPE_is_value_ref_type(compiler, var_type->basic_type->id, var_type->dimension, var_type->flag))) {
                SPVM_COMPILER_error(compiler, "Dereference target must be numeric reference type or value reference type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            // Add my var
            case SPVM_OP_C_ID_VAR: {
              
              if (op_cur->uv.var->is_declaration) {
                
                SPVM_MY* my = op_cur->uv.var->my;
                
                // Redeclaration error if same name variable is declare in same block
                int32_t found = 0;
                int32_t block_my_base = (intptr_t)SPVM_LIST_fetch(check_ast_info->block_my_base_stack, check_ast_info->block_my_base_stack->length - 1);
                {
                  int32_t i;
                  for (i = block_my_base; i < check_ast_info->my_stack->length; i++) {
                    SPVM_MY* bef_my = SPVM_LIST_fetch(check_ast_info->my_stack, i);
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
                  SPVM_COMPILER_error(compiler, "redeclaration of my \"%s\" at %s line %d\n", my->op_name->uv.name, my->op_my->file, my->op_my->line);
                  return;
                }
                else {
                  my->id = sub->mys->length;
                  SPVM_LIST_push(sub->mys, my);
                  SPVM_LIST_push(check_ast_info->my_stack, my);
                }
                
                // Type can't be detected
                if (!op_cur->is_lvalue && my->type == NULL) {
                  SPVM_COMPILER_error(compiler, "Type can't be detected at %s line %d\n", my->op_my->file, my->op_my->line);
                  return;
                }
              }
              
              SPVM_VAR* var = op_cur->uv.var;
              
              // Search same name variable
              SPVM_MY* found_my = NULL;
              {
                int32_t i;
                for (i = check_ast_info->my_stack->length - 1; i >= 0; i--) {
                  SPVM_MY* my = SPVM_LIST_fetch(check_ast_info->my_stack, i);
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

                  op_field_access->is_lvalue = op_cur->is_lvalue;
                  op_field_access->is_assigned_to_var = op_cur->is_assigned_to_var;
                  op_field_access->is_passed_to_sub = op_cur->is_passed_to_sub;
                  if (op_cur->uv.var->call_sub) {
                    op_cur->uv.var->call_sub->op_invocant = op_field_access;
                  }
                  
                  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                  SPVM_OP_replace_op(compiler, op_stab, op_field_access);
                  
                  op_cur = op_field_access;
                  
                  SPVM_OP_CHECKER_check_tree(compiler, op_field_access, check_ast_info);
                  if (compiler->error_count > 0) {
                    return;
                  }
                }
                else {
                  // Variable is package var
                  SPVM_OP* op_name_package_var = SPVM_OP_new_op_name(compiler, op_cur->uv.var->op_name->uv.name, op_cur->file, op_cur->line);
                  SPVM_OP* op_package_var_access = SPVM_OP_build_package_var_access(compiler, op_name_package_var);
                  
                  op_package_var_access->is_lvalue = op_cur->is_lvalue;
                  op_package_var_access->is_assigned_to_var = op_cur->is_assigned_to_var;
                  op_package_var_access->is_passed_to_sub = op_cur->is_passed_to_sub;
                  if (op_cur->uv.var->call_sub) {
                    op_cur->uv.var->call_sub->op_invocant = op_package_var_access;
                  }

                  SPVM_OP_CHECKER_resolve_package_var_access(compiler, op_package_var_access, package->op_package);
                  if (op_package_var_access->uv.package_var_access->package_var) {
                    
                    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                    SPVM_OP_replace_op(compiler, op_stab, op_package_var_access);

                    op_cur = op_package_var_access;
                    
                    SPVM_OP_CHECKER_check_tree(compiler, op_package_var_access, check_ast_info);
                    if (compiler->error_count > 0) {
                      return;
                    }
                  }
                  else {
                    SPVM_COMPILER_error(compiler, "%s is not declared at %s line %d\n", var->op_name->uv.name, op_cur->file, op_cur->line);
                    return;
                  }
                }
              }
              
              break;
            }
            case SPVM_OP_C_ID_CALL_SUB: {
              
              SPVM_OP* op_call_sub = op_cur;
              
              // Resulve sub
              SPVM_OP_CHECKER_resolve_call_sub(compiler, op_cur, package->op_package);
              if (compiler->error_count > 0) {
                return;
              }
              
              SPVM_OP* op_list_args = op_cur->last;
              
              SPVM_CALL_SUB* call_sub = op_call_sub->uv.call_sub;
              const char* sub_name = call_sub->sub->op_name->uv.name;

              if (call_sub->call_type_id != call_sub->sub->call_type_id) {
                SPVM_COMPILER_error(compiler, "Invalid method call \"%s->%s()\" at %s line %d\n", op_cur->uv.call_sub->sub->package->name, sub_name, op_cur->file, op_cur->line);
                return;
              }

              // Access control
              int32_t is_private;
              if (call_sub->sub->flag & SPVM_SUB_C_FLAG_PRIVATE) {
                is_private = 1;
              }
              // Default
              else {
                is_private = 0;
              }
              
              if (is_private) {
                if (!SPVM_OP_is_allowed(compiler, sub->package->op_package, call_sub->sub->package->op_package)) {
                  SPVM_COMPILER_error(compiler, "Can't call private method %s->%s at %s line %d\n", call_sub->sub->package->name, call_sub->sub->name, op_cur->file, op_cur->line);
                  return;
                }
              }
              
              int32_t sub_args_count = call_sub->sub->args->length;
              int32_t sub_is_vaarg = call_sub->sub->have_vaarg;

              // Variable length argument. Last argument is not array.
              int32_t vaarg_last_arg_is_not_array = 0;
              if (sub_is_vaarg) {
                int32_t arg_index = 0;
                SPVM_OP* op_term = op_list_args->first;
                while ((op_term = SPVM_OP_sibling(compiler, op_term))) {
                  if (arg_index == sub_args_count - 1) {
                    SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_term);
                    if (!SPVM_TYPE_is_array_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                      vaarg_last_arg_is_not_array = 1;
                    }
                  }
                  
                  arg_index++;
                }
                
                // Empty vaargs 
                if (arg_index == sub_args_count - 1) {
                  vaarg_last_arg_is_not_array = 1;
                }
              }

              // Variable length arguments
              if (vaarg_last_arg_is_not_array) {
                
                SPVM_OP* op_list_args_new = SPVM_OP_new_op_list(compiler, op_call_sub->file, op_call_sub->line);
                
                const char* file = op_cur->file;
                int32_t line = op_cur->line;
                
                // New
                SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, op_cur->file, op_cur->line);
                
                SPVM_MY* vaarg_last_arg_my = SPVM_LIST_fetch(call_sub->sub->args, call_sub->sub->args->length - 1);
                SPVM_TYPE* vaarg_last_arg_type = vaarg_last_arg_my->type;

                // Create new type
                SPVM_TYPE* type_new = SPVM_TYPE_new(compiler);
                type_new->basic_type = vaarg_last_arg_type->basic_type;
                type_new->dimension = vaarg_last_arg_type->dimension;
                type_new->flag = vaarg_last_arg_type->flag;
                SPVM_OP* op_type_new = SPVM_OP_new_op_type(compiler, type_new, op_cur->file, op_cur->line);
                
                // Create element type
                SPVM_TYPE* type_element = SPVM_TYPE_new(compiler);
                type_element->basic_type = vaarg_last_arg_type->basic_type;
                type_element->dimension = vaarg_last_arg_type->dimension - 1;
                type_element->flag = vaarg_last_arg_type->flag;
                SPVM_OP* op_type_element = SPVM_OP_new_op_type(compiler, type_element, op_cur->file, op_cur->line);
                
                // Sequence
                SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, file, line);
                SPVM_OP* op_assign_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, file, line);
                SPVM_TYPE* type_var_tmp_new = SPVM_TYPE_new(compiler);
                type_var_tmp_new->basic_type = type_new->basic_type;
                type_var_tmp_new->dimension = type_new->dimension;
                type_var_tmp_new->flag = type_new->flag;
                SPVM_OP* op_var_tmp_new = SPVM_OP_CHECKER_new_op_var_tmp(compiler, sub, type_var_tmp_new, file, line);
                
                SPVM_OP_build_assign(compiler, op_assign_new, op_var_tmp_new, op_new);

                SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_assign_new);
                
                int32_t length;
                int32_t arg_index = 0;
                int32_t vaarg_index = 0;
                
                SPVM_OP* op_term_element = op_list_args->first;
                while ((op_term_element = SPVM_OP_sibling(compiler, op_term_element))) {

                  op_term_element->no_need_check = 1;

                  if (arg_index < sub_args_count - 1) {
                    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term_element);
                    SPVM_OP_insert_child(compiler, op_list_args_new, op_list_args_new->last, op_term_element);
                    op_term_element = op_stab;
                  }
                  else {
                    op_var_tmp_new->uv.var->my->type = op_type_new->uv.type;

                    SPVM_OP* op_assign_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, file, line);
                    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term_element);
                    
                    SPVM_OP* op_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_ACCESS, file, line);

                    SPVM_OP* op_var_tmp_array_access = SPVM_OP_new_op_var_clone(compiler, op_var_tmp_new, op_var_tmp_new->file, op_var_tmp_new->line);
                    SPVM_OP_insert_child(compiler, op_array_access, op_array_access->last, op_var_tmp_array_access);

                    SPVM_OP* op_constant_index = SPVM_OP_new_op_constant_int(compiler, vaarg_index, file, line);
                    SPVM_OP_insert_child(compiler, op_array_access, op_array_access->last, op_constant_index);
                    
                    SPVM_OP_build_assign(compiler, op_assign_array_access, op_array_access, op_term_element);
                    
                    SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_assign_array_access);
                    
                    vaarg_index++;
                    op_term_element = op_stab;
                  }
                  arg_index++;
                }
                length = vaarg_index;
                
                SPVM_OP_insert_child(compiler, op_new, op_new->last, op_type_new);
                SPVM_OP_insert_child(compiler, op_type_new, op_type_new->last, op_type_element);

                SPVM_OP* op_constant_length = SPVM_OP_new_op_constant_int(compiler, length, file, line);
                SPVM_OP_insert_child(compiler, op_type_new, op_type_new->last, op_constant_length);
                
                SPVM_OP* op_var_tmp_ret = SPVM_OP_new_op_var_clone(compiler, op_var_tmp_new, op_var_tmp_new->file, op_var_tmp_new->line);
                
                SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_var_tmp_ret);

                SPVM_OP_insert_child(compiler, op_list_args_new, op_list_args_new->last, op_sequence);

                SPVM_OP_replace_op(compiler, op_call_sub->last, op_list_args_new);

                SPVM_OP_CHECKER_check_tree(compiler, op_list_args_new, check_ast_info);
                if (compiler->error_count > 0) {
                  return;
                }
                
                op_list_args = op_list_args_new;
              }
              
              int32_t call_sub_args_count = 0;
              {
                SPVM_OP* op_term = op_list_args->first;
                while ((op_term = SPVM_OP_sibling(compiler, op_term))) {
                  call_sub_args_count++;
                  if (call_sub_args_count > sub_args_count) {
                    SPVM_COMPILER_error(compiler, "Too many arguments \"%s->%s()\" at %s line %d\n", op_cur->uv.call_sub->sub->package->name, sub_name, op_cur->file, op_cur->line);
                    return;
                  }
                  
                  SPVM_MY* sub_arg_my = SPVM_LIST_fetch(call_sub->sub->args, call_sub_args_count - 1);
                  SPVM_TYPE* sub_arg_my_type = SPVM_OP_get_type(compiler, sub_arg_my->op_my);
                  
                  // Check if source can be assigned to dist
                  // If needed, numeric convertion op is added
                  char place[50];
                  sprintf(place, "arguments %d", call_sub_args_count);
                  
                  op_term = SPVM_OP_CHECKER_check_assign(compiler, sub_arg_my_type, op_term, place, op_cur->file, op_cur->line);
                  if (compiler->error_count > 0) {
                    return;
                  }
                }
              }
              
              if (call_sub_args_count < sub_args_count) {
                SPVM_COMPILER_error(compiler, "Too few argument. sub \"%s->%s()\" at %s line %d\n", op_cur->uv.call_sub->sub->package->name, sub_name, op_cur->file, op_cur->line);
                return;
              }
              
              // Update operand stack max
              if (call_sub_args_count > sub->call_sub_arg_stack_max) {
                sub->call_sub_arg_stack_max = call_sub_args_count;
              }

              // Call sub constant pool id
              char sub_id_string[sizeof(int32_t)];
              memcpy(sub_id_string, &op_cur->uv.call_sub->sub->id, sizeof(int32_t));

              // No duplicate sub access sub id
              SPVM_SUB* found_sub = SPVM_HASH_fetch(package->info_sub_id_symtable, sub_id_string, sizeof(int32_t));
              if (found_sub == NULL) {
                SPVM_LIST_push(package->info_sub_ids, (void*)(intptr_t)op_cur->uv.call_sub->sub->id);
                SPVM_HASH_insert(package->info_sub_id_symtable, sub_id_string, sizeof(int32_t), op_cur->uv.call_sub->sub);
              }
              
              if (call_sub->sub->flag & SPVM_SUB_C_FLAG_DESTRUCTOR) {
                SPVM_COMPILER_error(compiler, "Can't call DESTROY in yourself at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // Inline expansion
              {
                // Enum is replaced to constant value
                if (call_sub->sub->flag & SPVM_SUB_C_FLAG_ENUM) {
                  // Replace sub to constant
                  op_cur->id = SPVM_OP_C_ID_CONSTANT;
                  op_cur->uv.constant = call_sub->sub->op_inline->uv.constant;
                  
                  op_cur->first = NULL;
                  op_cur->last = NULL;
                }
                // Constant sub is replaced to constant value
                else if (call_sub->sub->is_constant) {
                  // Replace sub to constant
                  op_cur->id = SPVM_OP_C_ID_CONSTANT;
                  op_cur->uv.constant = call_sub->sub->op_inline->uv.constant;
                  
                  op_cur->first = NULL;
                  op_cur->last = NULL;
                }
                // Simple constructor is inlined
                else if (call_sub->sub->is_simple_constructor) {
                  // Replace sub to constant
                  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                  
                  SPVM_OP* op_type_original = call_sub->sub->op_inline;
                  assert(op_type_original->id == SPVM_OP_C_ID_TYPE);
                  SPVM_TYPE* type_original = op_type_original->uv.type;
                  
                  SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, op_cur->file, op_cur->line);
                  op_new->flag |= SPVM_OP_C_FLAG_NEW_INLINE;
                  
                  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
                  type->basic_type = type_original->basic_type;
                  type->dimension = type_original->dimension;
                  type->flag = type_original->flag;
                  
                  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, op_cur->file, op_cur->line);
                  op_new = SPVM_OP_build_new(compiler, op_new, op_type, NULL);
                  
                  SPVM_OP_CHECKER_check_tree(compiler, op_new, check_ast_info);
                  
                  SPVM_OP_replace_op(compiler, op_stab, op_new);
                  
                  op_cur = op_new;
                }
                // Field getter is replaced to field access
                else if (call_sub->sub->is_field_getter) {
                  // [Before]
                  // $object->foo
                  // [After]
                  // $object->{foo}
                  const char* field_name = call_sub->sub->accessor_original_name;

                  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);

                  SPVM_OP_cut_op(compiler, call_sub->op_invocant);

                  SPVM_OP* op_name_field_access = SPVM_OP_new_op_name(compiler, field_name, op_cur->file, op_cur->line);
                  SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, call_sub->op_invocant, op_name_field_access);
                  op_field_access->uv.field_access->inline_expansion = 1;

                  // Replace parent call sub op's op_invocant
                  SPVM_OP* op_parent_list =  SPVM_OP_get_parent(compiler, op_stab);
                  if (op_parent_list->id == SPVM_OP_C_ID_LIST) {
                    SPVM_OP* op_parent_call_sub =  SPVM_OP_get_parent(compiler, op_parent_list);
                    if (op_parent_call_sub->id == SPVM_OP_C_ID_CALL_SUB) {
                      if (op_parent_call_sub->uv.call_sub->call_type_id == SPVM_SUB_C_CALL_TYPE_ID_METHOD) {
                        op_parent_call_sub->uv.call_sub->op_invocant = op_field_access;
                      }
                    }
                  }
                  
                  SPVM_OP_replace_op(compiler, op_stab, op_field_access);
                  
                  SPVM_OP_CHECKER_check_tree(compiler, op_field_access, check_ast_info);
                  
                  op_cur = op_field_access;
                }
                // Field setter is replaced to field access
                else if (call_sub->sub->is_field_setter) {
                  // [Before]
                  // $object->set_foo($value)
                  // [After]
                  // $object->{foo} = $value

                  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                  
                  SPVM_OP* op_args = op_cur->last;
                  SPVM_OP* op_term_value = op_args->last;
                  
                  SPVM_OP_cut_op(compiler, op_term_value);

                  op_term_value->no_need_check = 1;

                  SPVM_OP_cut_op(compiler, call_sub->op_invocant);
                  
                  const char* field_name = call_sub->sub->accessor_original_name;
                  SPVM_OP* op_name_field_access = SPVM_OP_new_op_name(compiler, field_name, op_cur->file, op_cur->line);
                  SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, call_sub->op_invocant, op_name_field_access);
                  op_field_access->uv.field_access->inline_expansion = 1;
                  
                  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                  SPVM_OP_build_assign(compiler, op_assign, op_field_access, op_term_value);
                  
                  SPVM_OP_replace_op(compiler, op_stab, op_assign);
                  
                  SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
                  
                  op_cur = op_assign;
                }
                // Package var getter is replaced to package var access
                else if (call_sub->sub->is_package_var_getter) {
                  // [Before]
                  // Class->FOO
                  // [After]
                  // $Class::FOO
                  
                  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                  
                  const char* package_name = call_sub->sub->package->name;
                  const char* package_var_base_name = call_sub->sub->accessor_original_name;
                  char* package_var_name = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, 1 + strlen(package_name) + 2 + strlen(package_var_base_name));
                  memcpy(package_var_name, "$", 1);
                  memcpy(package_var_name + 1, package_name, strlen(package_name));
                  memcpy(package_var_name + 1 + strlen(package_name), "::", 2);
                  memcpy(package_var_name + 1 + strlen(package_name) + 2, package_var_base_name + 1, strlen(package_var_base_name) - 1);
                  SPVM_OP* op_package_var_name = SPVM_OP_new_op_name(compiler, package_var_name, op_cur->file, op_cur->line);
                  SPVM_OP* op_package_var_access = SPVM_OP_build_package_var_access(compiler, op_package_var_name);
                  op_package_var_access->uv.package_var_access->inline_expansion = 1;
                  
                  SPVM_OP_replace_op(compiler, op_stab, op_package_var_access);
                  
                  SPVM_OP_CHECKER_check_tree(compiler, op_package_var_access, check_ast_info);

                  op_cur = op_package_var_access;

                }
                // Package var setter is replaced to package var access
                else if (call_sub->sub->is_package_var_setter) {
                  // [Before]
                  // Class->SET_FOO($value)
                  // [After]
                  // $Class::FOO = $value
                  

                  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                  
                  SPVM_OP* op_args = op_cur->last;
                  SPVM_OP* op_term_value = op_args->last;
                  
                  SPVM_OP_cut_op(compiler, op_term_value);

                  op_term_value->no_need_check = 1;
                  
                  const char* package_name = call_sub->sub->package->name;
                  const char* package_var_base_name = call_sub->sub->accessor_original_name;
                  char* package_var_name = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, 1 + strlen(package_name) + 2 + strlen(package_var_base_name));
                  memcpy(package_var_name, "$", 1);
                  memcpy(package_var_name + 1, package_name, strlen(package_name));
                  memcpy(package_var_name + 1 + strlen(package_name), "::", 2);
                  memcpy(package_var_name + 1 + strlen(package_name) + 2, package_var_base_name + 1, strlen(package_var_base_name) - 1);
                  SPVM_OP* op_package_var_name = SPVM_OP_new_op_name(compiler, package_var_name, op_cur->file, op_cur->line);
                  SPVM_OP* op_package_var_access = SPVM_OP_build_package_var_access(compiler, op_package_var_name);
                  op_package_var_access->uv.package_var_access->inline_expansion = 1;
                  
                  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                  SPVM_OP_build_assign(compiler, op_assign, op_package_var_access, op_term_value);
                  
                  SPVM_OP_replace_op(compiler, op_stab, op_assign);
                  
                  SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
                  
                  op_cur = op_assign;
                }
              }
              
              break;
            }
            case SPVM_OP_C_ID_PACKAGE_VAR_ACCESS: {
              
              // Check field name
              SPVM_OP_CHECKER_resolve_package_var_access(compiler, op_cur, package->op_package);
              if (compiler->error_count > 0) {
                return;
              }
              
              if (!op_cur->uv.package_var_access->package_var) {
                SPVM_COMPILER_error(compiler, "Package variable not found \"%s\" at %s line %d\n", op_cur->uv.package_var_access->op_name->uv.name, op_cur->file, op_cur->line);
                return;
              }
              
              SPVM_PACKAGE_VAR_ACCESS* package_var_access = op_cur->uv.package_var_access;
              SPVM_PACKAGE_VAR* package_var = package_var_access->package_var;
              SPVM_PACKAGE* package_var_access_package = package_var->package;
              
              // Field accesss constant pool id
              char package_var_id_string[sizeof(int32_t)];
              memcpy(package_var_id_string, &op_cur->uv.package_var_access->package_var->id, sizeof(int32_t));

              // No duplicate package_var access package_var id
              SPVM_FIELD* found_package_var = SPVM_HASH_fetch(package->info_package_var_id_symtable, package_var_id_string, sizeof(int32_t));
              if (found_package_var == NULL) {
                SPVM_LIST_push(package->info_package_var_ids, (void*)(intptr_t)op_cur->uv.package_var_access->package_var->id);
                SPVM_HASH_insert(package->info_package_var_id_symtable, package_var_id_string, sizeof(int32_t), op_cur->uv.package_var_access->package_var);
              }

              int32_t is_private;
              // Public flag
              if (package_var->flag & SPVM_PACKAGE_VAR_C_FLAG_PUBLIC) {
                is_private = 0;
              }
              // Default is private
              else {
                is_private = 1;
              }

              if (is_private && !op_cur->uv.package_var_access->inline_expansion) {
                if (!SPVM_OP_is_allowed(compiler, sub->package->op_package, package_var_access_package->op_package)) {
                  SPVM_COMPILER_error(compiler, "Can't access to private package variable \"%s\" at %s line %d\n", op_cur->uv.package_var_access->op_name->uv.name, op_cur->file, op_cur->line);
                  return;
                }
              }
              
              break;
            }
            case SPVM_OP_C_ID_ARRAY_ACCESS: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be array or string
              if (!SPVM_TYPE_is_array_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) &&
                !SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)
              )
              {
                SPVM_COMPILER_error(compiler, "Array access invocant must be array or string at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // String access is const
              if (SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                op_cur->flag |= SPVM_OP_C_FLAG_ARRAY_ACCESS_CONST;
              }
              
              // Right operand must be integer
              if (SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_OP_CHECKER_apply_unary_numeric_widening_convertion(compiler, op_cur->last);
                if (compiler->error_count > 0) {
                  return;
                }
                
                SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                
                if (last_type->dimension == 0 && last_type->basic_type->id != SPVM_BASIC_TYPE_C_ID_INT) {
                  SPVM_COMPILER_error(compiler, "array index must be int type at %s line %d\n", op_cur->file, op_cur->line);
                  return;
                }
              }
              else {
                SPVM_COMPILER_error(compiler, "array index must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
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
                
                SPVM_OP* op_var_tmp = SPVM_OP_CHECKER_new_op_var_tmp(compiler, sub, term_index_type, op_cur->file, op_cur->line);

                SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);

                SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_term_array);
                
                // Convert cur new op to var
                SPVM_OP_replace_op(compiler, op_stab, op_assign);
                
                SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
                if (compiler->error_count > 0) {
                  return;
                }
              }
              
              // If array access index term is not var, create assign operator
              SPVM_OP* op_term_index = op_cur->last;
              if (op_term_index->id != SPVM_OP_C_ID_VAR) {
                
                op_cur->no_need_check = 1;

                SPVM_TYPE* term_index_type = SPVM_OP_get_type(compiler, op_term_index);

                SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term_index);
                
                SPVM_OP* op_var_tmp = SPVM_OP_CHECKER_new_op_var_tmp(compiler, sub, term_index_type, op_cur->file, op_cur->line);
                
                SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);

                SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_term_index);
                
                // Convert cur new op to var
                SPVM_OP_replace_op(compiler, op_stab, op_assign);

                SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
                if (compiler->error_count > 0) {
                  return;
                }
              }
              
              break;
            }
            case SPVM_OP_C_ID_FIELD_ACCESS: {
              SPVM_OP* op_term_invocker = op_cur->first;
              SPVM_OP* op_name = op_cur->uv.field_access->op_name;
              
              if (op_term_invocker->id == SPVM_OP_C_ID_ASSIGN) {
                op_term_invocker = op_term_invocker->first;
              }
              
              // Invoker type check
              SPVM_TYPE* invoker_type = SPVM_OP_get_type(compiler, op_term_invocker);
              int32_t is_valid_invoker_type;
              if (invoker_type) {
                if (SPVM_TYPE_is_class_type(compiler, invoker_type->basic_type->id, invoker_type->dimension, invoker_type->flag)) {
                  is_valid_invoker_type = 1;
                }
                else if (SPVM_TYPE_is_multi_numeric_type(compiler, invoker_type->basic_type->id, invoker_type->dimension, invoker_type->flag)) {
                  is_valid_invoker_type = 1;
                }
                else if (SPVM_TYPE_is_value_ref_type(compiler, invoker_type->basic_type->id, invoker_type->dimension, invoker_type->flag)) {
                  is_valid_invoker_type = 1;
                }
                else {
                  is_valid_invoker_type = 0;
                }
              }
              else {
                is_valid_invoker_type = 0;
              }
              if (!is_valid_invoker_type) {
                SPVM_COMPILER_error(compiler, "Invocker of field access must be class type, or multi numeric type, or numeric reference type at %s line %d\n", op_cur->file, op_cur->line);
                return;
              }
              
              // Check field name
              SPVM_OP_CHECKER_resolve_field_access(compiler, op_cur);
              if (compiler->error_count > 0) {
                return;
              }
              
              SPVM_FIELD* field = op_cur->uv.field_access->field;
              
              if (!field) {
                const char* invoker_type_name = SPVM_TYPE_new_type_name(compiler, invoker_type->basic_type->id, invoker_type->dimension, invoker_type->flag);
                SPVM_COMPILER_error(compiler, "Unknown field %s->%s at %s line %d\n", invoker_type_name, op_name->uv.name, op_cur->file, op_cur->line);
                return;
              }

              // Access control
              int32_t is_private;
              if (field->flag & SPVM_FIELD_C_FLAG_PUBLIC) {
                is_private = 0;
              }
              // Default
              else {
                // If anon sub, field is public
                if (field->package->flag & SPVM_PACKAGE_C_FLAG_ANON_SUB_PACKAGE) {
                  is_private = 0;
                }
                // If multi numeric type, field is public
                else if (field->package->category == SPVM_PACKAGE_C_CATEGORY_MULNUM) {
                  is_private = 0;
                }
                // Default is private
                else {
                  is_private = 1;
                }
              }
              
              if (is_private && !op_cur->uv.field_access->inline_expansion) {
                if (!SPVM_OP_is_allowed(compiler, sub->package->op_package, field->package->op_package)) {
                  SPVM_COMPILER_error(compiler, "Can't access to private field \"%s\" at %s line %d\n", op_name->uv.name, op_cur->file, op_cur->line);
                  return;
                }
              }
              
              // Field accesss constant pool id
              char field_id_string[sizeof(int32_t)];
              memcpy(field_id_string, &op_cur->uv.field_access->field->id, sizeof(int32_t));

              // No duplicate field access field id
              SPVM_FIELD* found_field = SPVM_HASH_fetch(package->info_field_id_symtable, field_id_string, sizeof(int32_t));
              if (found_field == NULL) {
                SPVM_LIST_push(package->info_field_ids, (void*)(intptr_t)op_cur->uv.field_access->field->id);
                SPVM_HASH_insert(package->info_field_id_symtable, field_id_string, sizeof(int32_t), op_cur->uv.field_access->field);
              }
              
              // If invocker is array access and array access object is mulnum_t, this op become array field access
              if (op_term_invocker->id == SPVM_OP_C_ID_ARRAY_ACCESS) {
                SPVM_OP* op_array_access = op_term_invocker;
                
                SPVM_TYPE* array_element_type = SPVM_OP_get_type(compiler, op_array_access);
                
                int32_t is_basic_type_mulnum_t = SPVM_TYPE_basic_type_is_multi_numeric_type(compiler, array_element_type->basic_type->id, array_element_type->dimension, array_element_type->flag);
                if (is_basic_type_mulnum_t) {
                  if (array_element_type->dimension != 0) {
                    SPVM_COMPILER_error(compiler, "mulnum_t array field access must be 1-dimension array at %s line %d\n", op_cur->file, op_cur->line);
                    return;
                  }
                  else {
                    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                    
                    SPVM_OP* op_array_field_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_FIELD_ACCESS, op_cur->file, op_cur->line);
                    op_array_field_access->is_lvalue = op_cur->is_lvalue;

                    op_cur = op_array_field_access;
                    
                    SPVM_ARRAY_FIELD_ACCESS* array_field_access = SPVM_ARRAY_FIELD_ACCESS_new(compiler);
                    array_field_access->field = field;
                    op_array_field_access->uv.array_field_access = array_field_access;
                    
                    SPVM_OP* op_array = op_array_access->first;
                    SPVM_OP* op_index = op_array_access->last;
                    SPVM_OP_cut_op(compiler, op_array_access->first);
                    SPVM_OP_cut_op(compiler, op_array_access->last);
                    
                    SPVM_OP_insert_child(compiler, op_array_field_access, op_array_field_access->last, op_array);
                    SPVM_OP_insert_child(compiler, op_array_field_access, op_array_field_access->last, op_index);
                    
                    SPVM_OP_replace_op(compiler, op_stab, op_array_field_access);
                    
                    SPVM_OP_CHECKER_check_tree(compiler, op_array_field_access, check_ast_info);
                    if (compiler->error_count > 0) {
                      return;
                    }
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
                  
                  SPVM_OP* op_var_tmp = SPVM_OP_CHECKER_new_op_var_tmp(compiler, sub, term_index_type, op_cur->file, op_cur->line);

                  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);

                  SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_term_array);
                  
                  // Convert cur new op to var
                  SPVM_OP_replace_op(compiler, op_stab, op_assign);
                  
                  SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
                  if (compiler->error_count > 0) {
                    return;
                  }
                }
                
                // If array access index term is not var, create assign operator
                SPVM_OP* op_term_index = op_cur->last;
                if (op_term_index->id != SPVM_OP_C_ID_VAR) {
                  op_cur->no_need_check = 1;

                  SPVM_TYPE* term_index_type = SPVM_OP_get_type(compiler, op_term_index);

                  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term_index);
                  
                  SPVM_OP* op_var_tmp = SPVM_OP_CHECKER_new_op_var_tmp(compiler, sub, term_index_type, op_cur->file, op_cur->line);
                  
                  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);

                  SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_term_index);
                  
                  // Convert cur new op to var
                  SPVM_OP_replace_op(compiler, op_stab, op_assign);
                  
                  SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
                  if (compiler->error_count > 0) {
                    return;
                  }
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
                  
                  SPVM_OP* op_var_tmp = SPVM_OP_CHECKER_new_op_var_tmp(compiler, sub, term_index_type, op_cur->file, op_cur->line);
                  
                  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                  SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_term_invocker);
                  
                  // Convert cur new op to var
                  SPVM_OP_replace_op(compiler, op_stab, op_assign);

                  SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
                  if (compiler->error_count > 0) {
                    return;
                  }
                }
              }
              
              break;
            }
            case SPVM_OP_C_ID_WEAKEN_FIELD: {
              SPVM_OP* op_field_access = op_cur->first;
              
              SPVM_FIELD* field = op_field_access->uv.field_access->field;
              
              SPVM_TYPE* type = field->type;
              
              if (!SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                SPVM_COMPILER_error(compiler, "weaken is only used for object field \"%s\" \"%s\" at %s line %d\n", field->package->op_name->uv.name, field->op_name->uv.name, op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_UNWEAKEN_FIELD: {
              SPVM_OP* op_field_access = op_cur->first;
              
              SPVM_FIELD* field = op_field_access->uv.field_access->field;
              
              SPVM_TYPE* type = field->type;
              
              if (!SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                SPVM_COMPILER_error(compiler, "unweaken is only used for object field \"%s\" \"%s\" at %s line %d\n", field->package->op_name->uv.name, field->op_name->uv.name, op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_ISWEAK_FIELD: {
              SPVM_OP* op_field_access = op_cur->first;
              
              SPVM_FIELD* field = op_field_access->uv.field_access->field;
              
              SPVM_TYPE* type = field->type;
              
              if (!SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                SPVM_COMPILER_error(compiler, "isweak is only used for object field \"%s\" \"%s\" at %s line %d\n", field->package->op_name->uv.name, field->op_name->uv.name, op_cur->file, op_cur->line);
                return;
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
              int32_t is_valid = 0;
              if (SPVM_TYPE_is_numeric_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                // Soruce type is numeric type
                if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                  is_valid = 1;
                }
                else if (SPVM_TYPE_is_numeric_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                  if (dist_type->basic_type->id + SPVM_BASIC_TYPE_C_NUMERIC_OBJECT_UPGRADE_SHIFT == src_type->basic_type->id) {
                    is_valid = 1;
                  }
                  else {
                    is_valid = 0;
                  }
                }
                else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                  is_valid = 1;
                }
                else {
                  is_valid = 0;
                }
              }
              // Dist type is referece type
              else if (SPVM_TYPE_is_ref_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                is_valid = 0;
              }
              // Dist type is multi numeric type
              else if (SPVM_TYPE_is_multi_numeric_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                is_valid = 0;
              }
              // Dist type is object type
              else if (SPVM_TYPE_is_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                // Source type is undef
                if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                  is_valid = 1;
                }
                else {
                  // Dist type is oarray type
                  if (SPVM_TYPE_is_oarray_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                    if (SPVM_TYPE_is_object_array_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                      is_valid = 1;
                    }
                    else {
                      is_valid = 0;
                    }
                  }
                  // Dist type is string type
                  else if (SPVM_TYPE_is_string_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                    if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                      is_valid = 1;
                    }
                    else if (SPVM_TYPE_is_string_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                      is_valid = 1;
                    }
                    else if (SPVM_TYPE_is_byte_array_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                      is_valid = 1;
                    }
                    else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                      is_valid = 1;
                    }
                    else {
                      is_valid = 0;
                    }
                  }
                  // Dist type is byte array type
                  else if (SPVM_TYPE_is_byte_array_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                    if (SPVM_TYPE_is_string_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                      is_valid = 1;
                    }
                    else if (SPVM_TYPE_is_byte_array_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                      is_valid = 1;
                    }
                    else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                      is_valid = 1;
                    }
                    else {
                      is_valid = 0;
                    }
                  }
                  // Dist type is any object type
                  else if (SPVM_TYPE_is_any_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                    if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                      is_valid = 1;
                    }
                    else if (SPVM_TYPE_is_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                      is_valid = 1;
                    }
                    else {
                      is_valid = 0;
                    }
                  }
                  // Dist type is numeric_object type
                  else if (SPVM_TYPE_is_numeric_object_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
                    if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                      if (dist_type->basic_type->id == src_type->basic_type->id + SPVM_BASIC_TYPE_C_NUMERIC_OBJECT_UPGRADE_SHIFT) {
                        is_valid = 1;
                      }
                      else {
                        is_valid = 0;
                      }
                    }
                    else if (SPVM_TYPE_is_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                      is_valid = 1;
                    }
                    else {
                      is_valid = 0;
                    }
                  }
                  // Source type is package type
                  else if (SPVM_TYPE_is_package_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                    is_valid = 1;
                  }
                  // Source type is object type
                  else if (SPVM_TYPE_is_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                    is_valid = 1;
                  }
                  // Source type is undef type
                  else if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                    is_valid = 1;
                  }
                  else {
                    is_valid = 0;
                  }
                }
              }
              else {
                assert(0);
              }

              if (!is_valid) {
                const char* src_type_name = SPVM_TYPE_new_type_name(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag);
                const char* dist_type_name = SPVM_TYPE_new_type_name(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag);
                SPVM_COMPILER_error(compiler, "Can't convert %s to %s by type convert at %s line %d\n", src_type_name, dist_type_name, op_src->file, op_src->line);
                return;
              }
              
              // Add type info to constant pool
              SPVM_OP_CHECKER_add_no_dup_basic_type(compiler, package->op_package, op_dist);
            }
            break;
          }
          
          // [END]Postorder traversal position
        }
        
        if (op_cur == op_root) {

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

void SPVM_OP_CHECKER_apply_numeric_to_string_convertion(SPVM_COMPILER* compiler, SPVM_OP* op_term) {
  
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

void SPVM_OP_CHECKER_apply_unary_numeric_widening_convertion(SPVM_COMPILER* compiler, SPVM_OP* op_term) {
  
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

void SPVM_OP_CHECKER_apply_binary_numeric_convertion(SPVM_COMPILER* compiler, SPVM_OP* op_first, SPVM_OP* op_last) {
  
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
  if (compiler->error_count > 0) {
    return;
  }
  
  // Resolve packages
  SPVM_OP_CHECKER_resolve_packages(compiler);
  if (compiler->error_count > 0) {
    return;
  }
  
  // Check trees
  {
    int32_t package_index;
    for (package_index = compiler->cur_package_base; package_index < compiler->packages->length; package_index++) {
      SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_index);
      SPVM_LIST* subs = package->subs;
      {
        int32_t sub_index;
        for (sub_index = 0; sub_index < subs->length; sub_index++) {
          
          SPVM_SUB* sub = SPVM_LIST_fetch(subs, sub_index);
          SPVM_PACKAGE* package = sub->package;
          SPVM_TYPE* package_type = package->op_type->uv.type;
          
          // Destructor must receive own package object
          if (sub->flag & SPVM_SUB_C_FLAG_DESTRUCTOR) {
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
              SPVM_COMPILER_error(compiler, "DESTROY argument must be self\n", sub->op_sub->file, sub->op_sub->line);
              return;
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
          
          if (package->category == SPVM_PACKAGE_C_CATEGORY_CALLBACK && (sub->op_block || sub->flag & SPVM_SUB_C_FLAG_NATIVE)) {
            SPVM_COMPILER_error(compiler, "Callback sub can't have implementation\n", sub->op_sub->file, sub->op_sub->line);
            return;
          }
          
          // Check subroutine
          if (!(sub->flag & SPVM_SUB_C_FLAG_NATIVE)) {
            SPVM_CHECK_AST_INFO check_ast_info_struct = {0};
            SPVM_CHECK_AST_INFO* check_ast_info = &check_ast_info_struct;
            
            // Package
            check_ast_info->package = package;
            
            // Sub
            check_ast_info->sub = sub;

            // Eval block stack length
            check_ast_info->eval_block_stack_length = 0;
            
            // Loop block stack length
            check_ast_info->loop_block_stack_length = 0;
            
            // My stack
            check_ast_info->my_stack = SPVM_LIST_new(0);
            
            // Block my base stack
            check_ast_info->block_my_base_stack = SPVM_LIST_new(0);
            
            // Switch stack
            check_ast_info->op_switch_stack = SPVM_LIST_new(0);
            
            // First tree traversal
            SPVM_OP_CHECKER_check_tree(compiler, sub->op_block, check_ast_info);
            
            if (compiler->error_count > 0) {
              return;
            }
            
            // Free list
            SPVM_LIST_free(check_ast_info->my_stack);
            SPVM_LIST_free(check_ast_info->block_my_base_stack);
            SPVM_LIST_free(check_ast_info->op_switch_stack);

            // Second tree traversal
            // set assign_to_var flag - 
            // Add string to constant pool
            // Check ref 
            {
              // Run OPs
              SPVM_OP* op_root = sub->op_block;
              SPVM_OP* op_cur = op_root;
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
                      case SPVM_OP_C_ID_CONSTANT: {
                        SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                        
                        // String
                        if (SPVM_TYPE_is_string_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                          // Add string constant
                          op_cur->uv.constant->constant_id = package->info_constants->length;
                          SPVM_LIST_push(package->info_constants, op_cur->uv.constant);
                        }
                        // long or double
                        else if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                          switch (type->basic_type->id) {
                            case SPVM_BASIC_TYPE_C_ID_LONG: {
                              // Add long constant
                              op_cur->uv.constant->constant_id = package->info_constants->length;
                              SPVM_LIST_push(package->info_constants, op_cur->uv.constant);
                            }
                            case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                              // Add double constant
                              op_cur->uv.constant->constant_id = package->info_constants->length;
                              SPVM_LIST_push(package->info_constants, op_cur->uv.constant);
                            }
                          }
                        }
                        
                        break;
                      }
                    }

                    if (op_cur == op_root) {

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
            
            // Third tree traversal
            // Create temporary variables for not assigned values - 
            {
              // Run OPs
              SPVM_OP* op_root = sub->op_block;
              SPVM_OP* op_cur = op_root;
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
                        case SPVM_OP_C_ID_RETURN:
                        case SPVM_OP_C_ID_LOOP_INCREMENT:
                        case SPVM_OP_C_ID_CONDITION:
                        case SPVM_OP_C_ID_CONDITION_NOT:
                        case SPVM_OP_C_ID_FREE_TMP:
                        case SPVM_OP_C_ID_CONVERT:
                        case SPVM_OP_C_ID_SWITCH:
                        case SPVM_OP_C_ID_DEFAULT:
                        case SPVM_OP_C_ID_CASE:
                        case SPVM_OP_C_ID_DIE:
                        case SPVM_OP_C_ID_WARN:
                        case SPVM_OP_C_ID_PRINT:
                        case SPVM_OP_C_ID_LAST:
                        case SPVM_OP_C_ID_NEXT:
                        case SPVM_OP_C_ID_BREAK:
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
                        case SPVM_OP_C_ID_RIGHT_ARITHMETIC_SHIFT:
                        case SPVM_OP_C_ID_RIGHT_LOGICAL_SHIFT:
                        case SPVM_OP_C_ID_MINUS:
                        case SPVM_OP_C_ID_PLUS:
                        case SPVM_OP_C_ID_ARRAY_LENGTH:
                        case SPVM_OP_C_ID_STRING_LENGTH:
                        case SPVM_OP_C_ID_NEW:
                        case SPVM_OP_C_ID_CONCAT:
                        case SPVM_OP_C_ID_REFOP:
                        case SPVM_OP_C_ID_EXCEPTION_VAR:
                        case SPVM_OP_C_ID_PACKAGE_VAR_ACCESS:
                        case SPVM_OP_C_ID_SWITCH_CONDITION:
                        case SPVM_OP_C_ID_ARRAY_FIELD_ACCESS:
                        case SPVM_OP_C_ID_CREATE_REF:
                        case SPVM_OP_C_ID_DEREF:
                        case SPVM_OP_C_ID_REFCNT:
                        case SPVM_OP_C_ID_FIELD_ACCESS:
                        case SPVM_OP_C_ID_ARRAY_ACCESS:
                        case SPVM_OP_C_ID_CALL_SUB:
                          create_tmp_var = 1;
                          break;
                        case SPVM_OP_C_ID_CONSTANT: {
                          if (op_cur->flag != SPVM_OP_C_FLAG_CONSTANT_CASE) {
                            if (SPVM_TYPE_is_numeric_type(compiler, tmp_var_type->basic_type->id, tmp_var_type->dimension, tmp_var_type->flag)) {
                              create_tmp_var = 1;
                            }
                            else if (SPVM_TYPE_is_string_type(compiler, tmp_var_type->basic_type->id, tmp_var_type->dimension, tmp_var_type->flag)) {
                              create_tmp_var = 1;
                            }
                          }
                          break;
                        }
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
                        case SPVM_OP_C_ID_BOOL:
                          assert(0);
                          break;
                      }
                    }

                    // Create temporary variable
                    if (create_tmp_var) {
                      SPVM_OP* op_var_tmp = SPVM_OP_CHECKER_new_op_var_tmp(compiler, sub, tmp_var_type, op_cur->file, op_cur->line);
                      
                      op_var_tmp->uv.var->my->id = sub->mys->length;
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

                    if (op_cur == op_root) {

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
            assert(sub->package->module_file);
            
            // Add op my if need
            if (sub->package->category == SPVM_PACKAGE_C_CATEGORY_CALLBACK) {
              int32_t arg_index;
              for (arg_index = 0; arg_index < sub->args->length; arg_index++) {
                SPVM_MY* arg_my = SPVM_LIST_fetch(sub->args, arg_index);
                SPVM_LIST_push(sub->mys, arg_my);
              }
            }

            // Fourth tree traversal
            // Fix LEAVE_SCOPE
            {
              // Block stack
              SPVM_LIST* op_block_stack = SPVM_LIST_new(0);
              
              // Run OPs
              SPVM_OP* op_root = sub->op_block;
              SPVM_OP* op_cur = op_root;
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
                          SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                          int32_t type_is_mulnum_t = SPVM_TYPE_is_multi_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag);
                          
                          if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag) && !type_is_mulnum_t) {
                            SPVM_OP* op_block_current = SPVM_LIST_fetch(op_block_stack, op_block_stack->length - 1);
                            op_block_current->uv.block->have_object_var_decl = 1;
                          }
                        }
                        
                        break;
                      }
                    }

                    if (op_cur == op_root) {

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

          // Resolve my type width
          for (int32_t my_index = 0; my_index < sub->mys->length; my_index++) {
            SPVM_MY* my = SPVM_LIST_fetch(sub->mys, my_index);
            SPVM_TYPE* my_type = SPVM_OP_get_type(compiler, my->op_my);
            
            int32_t type_width;
            if (SPVM_TYPE_is_multi_numeric_type(compiler, my_type->basic_type->id, my_type->dimension, my_type->flag)) {
              SPVM_PACKAGE* value_package =  my_type->basic_type->package;
              type_width = value_package->fields->length;
            }
            else {
              type_width = 1;
            }
            my->type_width = type_width;
          }

          // Resolve my runtime type
          for (int32_t my_index = 0; my_index < sub->mys->length; my_index++) {
            SPVM_MY* my = SPVM_LIST_fetch(sub->mys, my_index);
            SPVM_TYPE* my_type = SPVM_OP_get_type(compiler, my->op_my);
            my->type_category = SPVM_TYPE_get_type_category(compiler, my_type->basic_type->id, my_type->dimension, my_type->flag);
          }

          // Resolve return runtime type
          sub->return_type_category = SPVM_TYPE_get_type_category(compiler, sub->return_type->basic_type->id, sub->return_type->dimension, sub->return_type->flag);
          
          // Arg alloc length
          int32_t args_alloc_length = SPVM_SUB_get_arg_alloc_length(compiler, sub);
          sub->args_alloc_length = args_alloc_length;

          // Fifth tree traversal
          // Resolve my mem ids
          if (!(sub->flag & SPVM_SUB_C_FLAG_NATIVE)) {
            {
              SPVM_LIST* tmp_my_stack = SPVM_LIST_new(0);
              SPVM_LIST* no_tmp_my_stack = SPVM_LIST_new(0);
              SPVM_LIST* block_no_tmp_my_base_stack = SPVM_LIST_new(0);
              
              SPVM_LIST* byte_mem_stack = SPVM_LIST_new(0);
              SPVM_LIST* short_mem_stack = SPVM_LIST_new(0);
              SPVM_LIST* int_mem_stack = SPVM_LIST_new(0);
              SPVM_LIST* long_mem_stack = SPVM_LIST_new(0);
              SPVM_LIST* float_mem_stack = SPVM_LIST_new(0);
              SPVM_LIST* double_mem_stack = SPVM_LIST_new(0);
              SPVM_LIST* object_mem_stack = SPVM_LIST_new(0);
              SPVM_LIST* ref_mem_stack = SPVM_LIST_new(0);

              // Run OPs
              SPVM_OP* op_root = sub->op_block;
              SPVM_OP* op_cur = op_root;
              int32_t finish = 0;
              while (op_cur) {
                // [START]Preorder traversal position
                switch (op_cur->id) {
                  // Start scope
                  case SPVM_OP_C_ID_BLOCK: {
                    int32_t block_no_tmp_my_base = no_tmp_my_stack->length;
                    SPVM_LIST_push(block_no_tmp_my_base_stack, (void*)(intptr_t)block_no_tmp_my_base);
                    
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
                      case SPVM_OP_C_ID_FREE_TMP: {
                        
                        // Free temporary variables
                        int32_t length = tmp_my_stack->length;
                        for (int32_t i = 0; i < length; i++) {
                          SPVM_MY* my = SPVM_LIST_pop(tmp_my_stack);

                          SPVM_TYPE* type = SPVM_OP_get_type(compiler, my->op_my);
                          
                          // Free tmp mem id
                          if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_OP_CHECKER_free_mem_id(compiler, object_mem_stack, my);
                          }
                          else if (SPVM_TYPE_is_ref_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_OP_CHECKER_free_mem_id(compiler, ref_mem_stack, my);
                          }
                          else if (SPVM_TYPE_is_multi_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_PACKAGE* value_package =  type->basic_type->package;
                            
                            SPVM_FIELD* first_field = SPVM_LIST_fetch(value_package->fields, 0);
                            assert(first_field);
                            
                            SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, first_field->op_field);
                            
                            switch (field_type->basic_type->id) {
                              case SPVM_BASIC_TYPE_C_ID_BYTE: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, byte_mem_stack, my);
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_SHORT: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, short_mem_stack, my);
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_INT: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, int_mem_stack, my);
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_LONG: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, long_mem_stack, my);
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, float_mem_stack, my);
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, double_mem_stack, my);
                                break;
                              }
                              default:
                                assert(0);
                            }
                          }
                          else if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_TYPE* numeric_type = SPVM_OP_get_type(compiler, my->op_my);
                            switch(numeric_type->basic_type->id) {
                              case SPVM_BASIC_TYPE_C_ID_BYTE: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, byte_mem_stack, my);
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_SHORT: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, short_mem_stack, my);
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_INT: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, int_mem_stack, my);
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_LONG: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, long_mem_stack, my);
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, float_mem_stack, my);
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, double_mem_stack, my);
                                break;
                              }
                              default:
                                assert(0);
                            }
                          }
                          else if (SPVM_TYPE_is_void_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            
                          }
                          else {
                            assert(0);
                          }
                        }
                        break;
                      }
                      case SPVM_OP_C_ID_BLOCK: {
                        // Pop block no tmp my variable base
                        int32_t block_no_tmp_my_base = (intptr_t)SPVM_LIST_pop(block_no_tmp_my_base_stack);
                        int32_t no_tmp_my_stack_pop_count = no_tmp_my_stack->length - block_no_tmp_my_base;
                        
                        {
                          int32_t i;
                          for (i = 0; i < no_tmp_my_stack_pop_count; i++) {
                            SPVM_MY* my = SPVM_LIST_pop(no_tmp_my_stack);

                            SPVM_TYPE* type = SPVM_OP_get_type(compiler, my->op_my);
                            
                            // Free tmp mem id
                            if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                              SPVM_OP_CHECKER_free_mem_id(compiler, object_mem_stack, my);
                            }
                            else if (SPVM_TYPE_is_ref_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                              SPVM_OP_CHECKER_free_mem_id(compiler, ref_mem_stack, my);
                            }
                            else if (SPVM_TYPE_is_multi_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                              SPVM_PACKAGE* value_package =  type->basic_type->package;
                              
                              SPVM_FIELD* first_field = SPVM_LIST_fetch(value_package->fields, 0);
                              assert(first_field);
                              
                              SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, first_field->op_field);
                              
                              switch (field_type->basic_type->id) {
                                case SPVM_BASIC_TYPE_C_ID_BYTE: {
                                  SPVM_OP_CHECKER_free_mem_id(compiler, byte_mem_stack, my);
                                  break;
                                }
                                case SPVM_BASIC_TYPE_C_ID_SHORT: {
                                  SPVM_OP_CHECKER_free_mem_id(compiler, short_mem_stack, my);
                                  break;
                                }
                                case SPVM_BASIC_TYPE_C_ID_INT: {
                                  SPVM_OP_CHECKER_free_mem_id(compiler, int_mem_stack, my);
                                  break;
                                }
                                case SPVM_BASIC_TYPE_C_ID_LONG: {
                                  SPVM_OP_CHECKER_free_mem_id(compiler, long_mem_stack, my);
                                  break;
                                }
                                case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                                  SPVM_OP_CHECKER_free_mem_id(compiler, float_mem_stack, my);
                                  break;
                                }
                                case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                                  SPVM_OP_CHECKER_free_mem_id(compiler, double_mem_stack, my);
                                  break;
                                }
                                default:
                                  assert(0);
                              }
                            }
                            else if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                              SPVM_TYPE* numeric_type = SPVM_OP_get_type(compiler, my->op_my);
                              switch(numeric_type->basic_type->id) {
                                case SPVM_BASIC_TYPE_C_ID_BYTE: {
                                  SPVM_OP_CHECKER_free_mem_id(compiler, byte_mem_stack, my);
                                  break;
                                }
                                case SPVM_BASIC_TYPE_C_ID_SHORT: {
                                  SPVM_OP_CHECKER_free_mem_id(compiler, short_mem_stack, my);
                                  break;
                                }
                                case SPVM_BASIC_TYPE_C_ID_INT: {
                                  SPVM_OP_CHECKER_free_mem_id(compiler, int_mem_stack, my);
                                  break;
                                }
                                case SPVM_BASIC_TYPE_C_ID_LONG: {
                                  SPVM_OP_CHECKER_free_mem_id(compiler, long_mem_stack, my);
                                  break;
                                }
                                case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                                  SPVM_OP_CHECKER_free_mem_id(compiler, float_mem_stack, my);
                                  break;
                                }
                                case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                                  SPVM_OP_CHECKER_free_mem_id(compiler, double_mem_stack, my);
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
                        }

                        // Move loop condition to last sibling before opcode building
                        if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_LOOP_INIT) {
                          SPVM_OP* op_term_init = op_cur->first;
                          SPVM_OP* op_condition = op_cur->first->sibparent;
                          SPVM_OP* op_block_statements = op_cur->first->sibparent->sibparent;
                          SPVM_OP* op_loop_increment = op_cur->first->sibparent->sibparent->sibparent;
                          
                          op_term_init->sibparent = op_block_statements;
                          op_loop_increment->sibparent = op_condition;
                          op_loop_increment->moresib = 1;
                          
                          op_condition->sibparent = op_cur;
                          op_condition->moresib = 0;
                        }
                        
                        break;
                      }
                      case SPVM_OP_C_ID_VAR: {
                        if (op_cur->uv.var->is_declaration) {
                          SPVM_MY* my = op_cur->uv.var->my;
                          
                          SPVM_TYPE* type = SPVM_OP_get_type(compiler, my->op_my);
                          
                          // Resolve mem id
                          int32_t mem_id;
                          if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, object_mem_stack, my);
                          }
                          else if (SPVM_TYPE_is_ref_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, ref_mem_stack, my);
                          }
                          else if (SPVM_TYPE_is_multi_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_PACKAGE* value_package =  type->basic_type->package;
                            
                            SPVM_FIELD* first_field = SPVM_LIST_fetch(value_package->fields, 0);
                            assert(first_field);
                            
                            SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, first_field->op_field);
                            
                            switch (field_type->basic_type->id) {
                              case SPVM_BASIC_TYPE_C_ID_BYTE: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, byte_mem_stack, my);
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_SHORT: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, short_mem_stack, my);
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_INT: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, int_mem_stack, my);
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_LONG: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, long_mem_stack, my);
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, float_mem_stack, my);
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, double_mem_stack, my);
                                break;
                              }
                              default:
                                assert(0);
                            }
                          }
                          else if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_TYPE* numeric_type = SPVM_OP_get_type(compiler, my->op_my);
                            switch(numeric_type->basic_type->id) {
                              case SPVM_BASIC_TYPE_C_ID_BYTE: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, byte_mem_stack, my);
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_SHORT: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, short_mem_stack, my);
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_INT: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, int_mem_stack, my);
                                if (strcmp(my->op_name->uv.name, "@condition_flag") == 0) {
                                  assert(mem_id == 0);
                                }
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_LONG: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, long_mem_stack, my);
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, float_mem_stack, my);
                                break;
                              }
                              case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, double_mem_stack, my);
                                break;
                              }
                              default:
                                assert(0);
                            }
                          }
                          else if (SPVM_TYPE_is_void_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            mem_id = -1;
                          }
                          else {
                            assert(0);
                          }
                          my->mem_id = mem_id;
                          
                          // Add stack
                          if (my->is_tmp) {
                            SPVM_LIST_push(tmp_my_stack, my);
                          }
                          else {
                            SPVM_LIST_push(no_tmp_my_stack, my);
                          }
                        }
                        break;
                      }
                    }

                    if (op_cur == op_root) {
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

              sub->byte_vars_alloc_length = byte_mem_stack->length;
              sub->short_vars_alloc_length = short_mem_stack->length;
              sub->int_vars_alloc_length = int_mem_stack->length;
              sub->long_vars_alloc_length = long_mem_stack->length;
              sub->float_vars_alloc_length = float_mem_stack->length;
              sub->double_vars_alloc_length = double_mem_stack->length;

              sub->object_vars_alloc_length = object_mem_stack->length;
              sub->ref_vars_alloc_length = ref_mem_stack->length;

              SPVM_LIST_free(tmp_my_stack);
              SPVM_LIST_free(no_tmp_my_stack);
              SPVM_LIST_free(block_no_tmp_my_base_stack);

              SPVM_LIST_free(byte_mem_stack);
              SPVM_LIST_free(short_mem_stack);
              SPVM_LIST_free(int_mem_stack);
              SPVM_LIST_free(long_mem_stack);
              SPVM_LIST_free(float_mem_stack);
              SPVM_LIST_free(double_mem_stack);
              SPVM_LIST_free(object_mem_stack);
              SPVM_LIST_free(ref_mem_stack);
            }
          }
        }
      }
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

SPVM_OP* SPVM_OP_CHECKER_check_assign(SPVM_COMPILER* compiler, SPVM_TYPE* dist_type, SPVM_OP* op_src, const char* place, const char* file, int32_t line) {
  SPVM_TYPE* src_type = SPVM_OP_get_type(compiler, op_src);
  
  // Dist type is numeric type
  int32_t can_assign = 0;
  int32_t narrowing_convertion_error = 0;
  int32_t need_implicite_convertion = 0;
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
        need_implicite_convertion = 1;
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
          need_implicite_convertion = 1;
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
        need_implicite_convertion = 1;
      }
      else if (SPVM_TYPE_is_numeric_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
        if (src_type->basic_type->id == dist_type->basic_type->id + SPVM_BASIC_TYPE_C_NUMERIC_OBJECT_UPGRADE_SHIFT) {
          can_assign = 1;
          need_implicite_convertion = 1;
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
  // Dist type is multi numeric type
  else if (SPVM_TYPE_is_multi_numeric_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
    if (SPVM_TYPE_is_multi_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
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
    // Dist type is oarray type
    if (SPVM_TYPE_is_oarray_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
      if (SPVM_TYPE_is_object_array_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
        can_assign = 1;
      }
      else if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
        can_assign = 1;
      }
      else {
        can_assign = 0;
      }
    }
    // Dist type is string type
    else if (SPVM_TYPE_is_string_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
      // Source type is number
      if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
        can_assign = 1;
        need_implicite_convertion = 1;
      }
      // Source type is string
      else if (SPVM_TYPE_is_string_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
        can_assign = 1;
      }
      // Source type is byte array
      else if (SPVM_TYPE_is_byte_array_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
        can_assign = 0;
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
        need_implicite_convertion = 1;
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
          need_implicite_convertion = 1;
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
        // Dist type is class or callback
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
          // Dist type is callback
          else if (SPVM_TYPE_is_callback_type(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag)) {
            
            // Source type is class or callback
            if (
              SPVM_TYPE_is_class_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)
              || SPVM_TYPE_is_callback_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)
            )
            {
              can_assign = SPVM_TYPE_has_callback(
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
    SPVM_COMPILER_error(compiler, "Can't assign to empty type in %s, at %s line %d\n", place, file, line);
    return NULL;
  }
    
  if (!can_assign) {
    if (narrowing_convertion_error) {
      SPVM_COMPILER_error(compiler, "Can't apply narrowing convertion in %s at %s line %d\n", place, file, line);
      return NULL;
    }
    else {
      const char* src_type_name = SPVM_TYPE_new_type_name(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag);
      const char* dist_type_name = SPVM_TYPE_new_type_name(compiler, dist_type->basic_type->id, dist_type->dimension, dist_type->flag);
      SPVM_COMPILER_error(compiler, "Can't convert %s to %s by implicite type convertion in %s at %s line %d\n", src_type_name, dist_type_name, place, file, line);
      return NULL;
    }
  }
  
  if (need_implicite_convertion) {
    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_src);
    
    SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, file, line);
    SPVM_OP* op_dist_type = SPVM_OP_new_op_type(compiler, dist_type, file, line);
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
    if (type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_BYTE_OBJECT) {
      
      // Unknonw package
      SPVM_HASH* package_symtable = compiler->package_symtable;
      SPVM_PACKAGE* found_package = SPVM_HASH_fetch(package_symtable, basic_type_name, strlen(basic_type_name));
      if (!found_package) {
        SPVM_COMPILER_error(compiler, "Unknown package \"%s\" at %s line %d\n", basic_type_name, op_type->file, op_type->line);
        return;
      }
    }
    
    // Reference type must be numeric refernce type or value reference type
    if (SPVM_TYPE_is_ref_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
      if (!(SPVM_TYPE_is_numeric_ref_type(compiler, type->basic_type->id, type->dimension, type->flag) || SPVM_TYPE_is_value_ref_type(compiler, type->basic_type->id, type->dimension, type->flag))) {
        SPVM_COMPILER_error(compiler, "Reference type must be numeric refernce type or mulnum_t reference type \"%s\"\\ at %s line %d\n", basic_type_name, op_type->file, op_type->line);
        return;
      }
    }
    
    // array of oarray is invalid
    if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_OARRAY && type->dimension > 0) {
      SPVM_COMPILER_error(compiler, "Array of oarray type is invalid type at %s line %d\n", op_type->file, op_type->line);
      return;
    }
  }
}

void SPVM_OP_CHECKER_resolve_call_sub(SPVM_COMPILER* compiler, SPVM_OP* op_call_sub, SPVM_OP* op_package_current) {
  
  SPVM_CALL_SUB* call_sub = op_call_sub->uv.call_sub;
  
  if (call_sub->sub) {
    return;
  }
  
  SPVM_PACKAGE* found_package;
  SPVM_SUB* found_sub;
  
  const char* sub_name = call_sub->op_name->uv.name;
  // Method call
  if (call_sub->call_type_id == SPVM_SUB_C_CALL_TYPE_ID_METHOD) {
    SPVM_TYPE* type = SPVM_OP_get_type(compiler, call_sub->op_invocant);
    if (SPVM_TYPE_is_array_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
      const char* type_name = SPVM_TYPE_new_type_name(compiler, type->basic_type->id, type->dimension, type->flag);
      SPVM_COMPILER_error(compiler, "Unknown sub \"%s->%s\" at %s line %d\n", type_name, sub_name, op_call_sub->file, op_call_sub->line);
      return;
    }
    else {
      const char* basic_type_name = type->basic_type->name;
      
      SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, basic_type_name, strlen(basic_type_name));
      
      if (!package) {
        SPVM_COMPILER_error(compiler, "Unknown sub \"%s->%s\" at %s line %d\n", basic_type_name, sub_name, op_call_sub->file, op_call_sub->line);
        return;
      }
      
      found_package = package;
      found_sub = SPVM_HASH_fetch(
        package->sub_symtable,
        sub_name,
        strlen(sub_name)
      );
    }
  }
  // Static method call
  else {
    if (call_sub->op_invocant) {
      const char* package_name = call_sub->op_invocant->uv.type->basic_type->name;
      SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, package_name, strlen(package_name));
      assert(package);
      
      found_package = package;
      found_sub = SPVM_HASH_fetch(
        package->sub_symtable,
        sub_name,
        strlen(sub_name)
      );
    }
    // Subroutine call
    else {
      // Search current pacakge
      SPVM_PACKAGE* package = op_package_current->uv.package;
      found_package = package;
      found_sub = SPVM_HASH_fetch(
        package->sub_symtable,
        sub_name,
        strlen(sub_name)
      );
      
      // Search imported subs
      SPVM_LIST* op_uses = package->op_uses;
      if (op_uses) {
        for (int32_t use_index = 0; use_index < op_uses->length; use_index++) {
          SPVM_OP* op_use = SPVM_LIST_fetch(op_uses, use_index);
          SPVM_TYPE* type = op_use->uv.use->op_type->uv.type;
          const char* basic_type_name = type->basic_type->name;
          SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, basic_type_name, strlen(basic_type_name));
          assert(package);
          
          SPVM_LIST* import_sub_names = op_use->uv.use->sub_names;
          if (import_sub_names) {
            for (int32_t import_sub_name_index = 0; import_sub_name_index < import_sub_names->length; import_sub_name_index++) {
              const char* import_sub_name = SPVM_LIST_fetch(import_sub_names, import_sub_name_index);
              if (strcmp(sub_name, import_sub_name) == 0) {
                found_sub = SPVM_HASH_fetch(
                  package->sub_symtable,
                  sub_name,
                  strlen(sub_name)
                );
              }
            }
          }
        }
      }
    }
  }
  
  if (found_sub) {
    call_sub->sub = found_sub;
  }
  else {
    assert(found_package);
    SPVM_COMPILER_error(compiler, "Unknown sub \"%s->%s\" at %s line %d\n", found_package->name, sub_name, op_call_sub->file, op_call_sub->line);
    return;
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

void SPVM_OP_CHECKER_resolve_package_var_access(SPVM_COMPILER* compiler, SPVM_OP* op_package_var_access, SPVM_OP* op_current_package) {
  
  if (op_package_var_access->uv.package_var_access->package_var) {
    return;
  }
  assert(op_package_var_access->uv.package_var_access);
  
  SPVM_OP* op_name = op_package_var_access->uv.package_var_access->op_name;
  
  char* package_name;
  char* base_name;
  
  const char* name = op_name->uv.name;
  
  char* colon_ptr = strrchr(name, ':');
  if (colon_ptr) {
    // Package name
    // (end - start + 1) - $ - colon * 2
    int32_t package_name_length = (colon_ptr - name + 1) - 1 - 2;
    package_name = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, package_name_length + 1);
    memcpy(package_name, name + 1, package_name_length);
    
    // Base name($foo)
    int32_t base_name_length = 1 + (name + strlen(name) - 1) - colon_ptr;
    base_name = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, base_name_length + 1);
    base_name[0] = '$';
    memcpy(base_name + 1, colon_ptr + 1, base_name_length);
  }
  else {
    package_name = (char*)op_current_package->uv.package->name;
    base_name = (char*)name;
  }
  
  SPVM_PACKAGE* found_package = SPVM_HASH_fetch(compiler->package_symtable, package_name, strlen(package_name));
  if (found_package) {
    SPVM_PACKAGE_VAR* found_package_var = SPVM_HASH_fetch(found_package->package_var_symtable, base_name, strlen(base_name));
    if (found_package_var) {
      op_package_var_access->uv.package_var_access->package_var = found_package_var;
    }
  }
}

void SPVM_OP_CHECKER_resolve_basic_types(SPVM_COMPILER* compiler) {
  SPVM_LIST* basic_types = compiler->basic_types;
  
  for (int32_t basic_type_index = 0; basic_type_index < basic_types->length; basic_type_index++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(basic_types, basic_type_index);
    SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, basic_type->name, strlen(basic_type->name));
    if (package) {
      basic_type->package = package;
    }
  }
}

void SPVM_OP_CHECKER_resolve_field_offset(SPVM_COMPILER* compiler, SPVM_PACKAGE* package) {
  if (package->category != SPVM_PACKAGE_C_CATEGORY_CLASS) {
    return;
  }
  
  int32_t offset = 0;
  // 8 byte data
  for (int32_t field_index = 0; field_index < package->fields->length; field_index++) {
    SPVM_FIELD* field = SPVM_LIST_fetch(package->fields, field_index);
    SPVM_TYPE* field_type = field->type;
    if (SPVM_TYPE_is_double_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)
      || SPVM_TYPE_is_long_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)) {
      field->offset = offset;
      offset += 8;
    }
  }
  
  // 4 byte data
  for (int32_t field_index = 0; field_index < package->fields->length; field_index++) {
    SPVM_FIELD* field = SPVM_LIST_fetch(package->fields, field_index);
    SPVM_TYPE* field_type = field->type;
    if (SPVM_TYPE_is_float_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)
      || SPVM_TYPE_is_int_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)) {
      field->offset = offset;
      offset += 4;
    }
  }
  
  // 2 byte data
  for (int32_t field_index = 0; field_index < package->fields->length; field_index++) {
    SPVM_FIELD* field = SPVM_LIST_fetch(package->fields, field_index);
    SPVM_TYPE* field_type = field->type;
    if (SPVM_TYPE_is_short_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)) {
      field->offset = offset;
      offset += 2;
    }
  }
  
  // 1 byte data
  for (int32_t field_index = 0; field_index < package->fields->length; field_index++) {
    SPVM_FIELD* field = SPVM_LIST_fetch(package->fields, field_index);
    SPVM_TYPE* field_type = field->type;
    if (SPVM_TYPE_is_byte_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)) {
      field->offset = offset;
      offset += 1;
    }
  }
  
  // Fix allignment
  if (offset % 8 != 0) {
    offset += (8 - offset % 8);
  }
  assert(offset % 8 == 0);

  package->object_fields_offset = offset;
  
  // address data
  int32_t object_fields_length = 0;
  for (int32_t field_index = 0; field_index < package->fields->length; field_index++) {
    SPVM_FIELD* field = SPVM_LIST_fetch(package->fields, field_index);
    SPVM_TYPE* field_type = field->type;
    if (SPVM_TYPE_is_object_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)) {
      field->offset = offset;
      offset += sizeof(void*);
      object_fields_length++;
    }
  }
  package->object_fields_length = object_fields_length;
  package->fields_byte_size = offset;
}

void SPVM_OP_CHECKER_resolve_packages(SPVM_COMPILER* compiler) {
  
  // Set package id
  for (int32_t package_index = compiler->cur_package_base; package_index < compiler->packages->length; package_index++) {
    SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_index);
    package->id = package_index;
  }
  
  for (int32_t package_index = compiler->cur_package_base; package_index < compiler->packages->length; package_index++) {
    SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_index);
    
    const char* package_name = package->op_name->uv.name;
    
    // mulnum_t package limitation
    if (package->category == SPVM_PACKAGE_C_CATEGORY_MULNUM) {
      // Can't have subroutines
      if (package->subs->length > 0) {
        SPVM_COMPILER_error(compiler, "mulnum_t package can't have subroutines at %s line %d\n", package->op_package->file, package->op_package->line);
        return;
      }
      // Can't have package variables
      if (package->package_vars->length > 0) {
        SPVM_COMPILER_error(compiler, "mulnum_t package can't have package variables at %s line %d\n", package->op_package->file, package->op_package->line);
        return;
      }
      
      // At least have one field
      if (package->fields->length == 0) {
        SPVM_COMPILER_error(compiler, "mulnum_t package have at least one field at %s line %d\n", package->op_package->file, package->op_package->line);
        return;
      }
      // Minilal mulnum_t fields length is 1
      else if (package->fields->length < SPVM_LIMIT_C_MULNUM_T_FIELDS_MIN_COUNT) {
        SPVM_COMPILER_error(compiler, "Neet at least one field at %s line %d\n", package->op_package->file, package->op_package->line);
        return;
      }
      // Max fields length is 255
      else if (package->fields->length > SPVM_LIMIT_C_MULNUM_T_FIELDS_MAX_COUNT) {
        SPVM_COMPILER_error(compiler, "Too many mulnum_t fields. Max count of mulnum_t fields is 255 at %s line %d\n", package->op_package->file, package->op_package->line);
        return;
      }
      else {
        SPVM_LIST* fields = package->fields;
        SPVM_FIELD* first_field = SPVM_LIST_fetch(fields, 0);
        SPVM_TYPE* first_field_type = SPVM_OP_get_type(compiler, first_field->op_field);
        if (!SPVM_TYPE_is_numeric_type(compiler, first_field_type->basic_type->id, first_field_type->dimension, first_field_type->flag)) {
          SPVM_COMPILER_error(compiler, "mulnum_t package must have numeric field at %s line %d\n", first_field->op_field->file, first_field->op_field->line);
          return;
        }
        else {
          int32_t field_index;
          for (field_index = 0; field_index < package->fields->length; field_index++) {
            SPVM_FIELD* field = SPVM_LIST_fetch(fields, field_index);
            SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, field->op_field);
            if (!(field_type->basic_type->id == first_field_type->basic_type->id && field_type->dimension == first_field_type->dimension)) {
              SPVM_COMPILER_error(compiler, "field must have %s type at %s line %d\n", field_type->basic_type->name, field->op_field->file, field->op_field->line);
              return;
            }
          }
          
          // Check type name
          char* tail_name = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, 255);
          switch (first_field_type->basic_type->id) {
            case SPVM_BASIC_TYPE_C_ID_BYTE:
              sprintf(tail_name, "_%db", fields->length);
              break;
            case SPVM_BASIC_TYPE_C_ID_SHORT:
              sprintf(tail_name, "_%ds", fields->length);
              break;
            case SPVM_BASIC_TYPE_C_ID_INT:
              sprintf(tail_name, "_%di", fields->length);
              break;
            case SPVM_BASIC_TYPE_C_ID_LONG:
              sprintf(tail_name, "_%dl", fields->length);
              break;
            case SPVM_BASIC_TYPE_C_ID_FLOAT:
              sprintf(tail_name, "_%df", fields->length);
              break;
            case SPVM_BASIC_TYPE_C_ID_DOUBLE:
              sprintf(tail_name, "_%dd", fields->length);
              break;
            default:
              assert(0);
          }
          int32_t tail_name_length = (int32_t)strlen(tail_name);
          
          char* found_pos_ptr = strstr(package_name, tail_name);
          if (found_pos_ptr) {
            if (*(found_pos_ptr + tail_name_length) != '\0') {
              SPVM_COMPILER_error(compiler, "package name must end with %s at %s line %d\n", tail_name, package->op_package->file, package->op_package->line);
              return;
            }
          }
          else {
            SPVM_COMPILER_error(compiler, "package name must end with %s at %s line %d\n", tail_name, package->op_package->file, package->op_package->line);
            return;
          }
        }
      }
    }

    // Check package var
    for (int32_t package_var_index = 0; package_var_index < package->package_vars->length; package_var_index++) {
      SPVM_PACKAGE_VAR* package_var = SPVM_LIST_fetch(package->package_vars, package_var_index);
      SPVM_TYPE* package_var_type = SPVM_OP_get_type(compiler, package_var->op_package_var);
      int32_t is_mulnum_t = SPVM_TYPE_is_multi_numeric_type(compiler, package_var_type->basic_type->id, package_var_type->dimension, package_var_type->flag);
      
      // valut_t can't become package variable
      if (is_mulnum_t) {
        SPVM_COMPILER_error(compiler, "mulnum_t type can't become package variable at %s line %d\n", package_var->op_package_var->file, package_var->op_package_var->line);
        return;
      }

      // Create package var signature
      const char* package_var_signature = SPVM_COMPILER_create_package_var_signature(compiler, package_var);
      package_var->signature = package_var_signature;
    }
    
    // Check fields
    for (int32_t field_index = 0; field_index < package->fields->length; field_index++) {
      SPVM_FIELD* field = SPVM_LIST_fetch(package->fields, field_index);
      SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, field->op_field);

      if (strchr(field->op_name->uv.name, ':')) {
        SPVM_COMPILER_error(compiler, "field name can't contain :: at %s line %d\n", field->op_name->file, field->op_name->line);
        return;
      }

      // valut_t can't become field
      int32_t is_mulnum_t = SPVM_TYPE_is_multi_numeric_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag);
      if (is_mulnum_t) {
        SPVM_COMPILER_error(compiler, "mulnum_t type can't become field at %s line %d\n", field->op_field->file, field->op_field->line);
        return;
      }
      
      // Set runtime type
      field->type_category = SPVM_TYPE_get_type_category(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag);

      // Create field signature
      const char* field_signature = SPVM_COMPILER_create_field_signature(compiler, field);
      field->signature = field_signature;
    }
    
    SPVM_OP_CHECKER_resolve_field_offset(compiler, package);
    
    // Check subs
    for (int32_t i = 0; i < package->subs->length; i++) {
      SPVM_SUB* sub = SPVM_LIST_fetch(package->subs, i);
      
      // Argument limit check
      int32_t arg_allow_count = 0;
      SPVM_TYPE* last_arg_type = NULL;
      for (int32_t arg_index = 0; arg_index < sub->args->length; arg_index++) {
        SPVM_MY* arg_my = SPVM_LIST_fetch(sub->args, arg_index);

        SPVM_TYPE* arg_type = SPVM_OP_get_type(compiler, arg_my->op_my);
        
        int32_t is_arg_type_is_multi_numeric_type = SPVM_TYPE_is_multi_numeric_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag);
        int32_t is_arg_type_is_value_ref_type = SPVM_TYPE_is_value_ref_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag);
        
        if (is_arg_type_is_multi_numeric_type || is_arg_type_is_value_ref_type) {
          arg_allow_count += arg_type->basic_type->package->fields->length;
        }
        else {
          arg_allow_count++;
        }
        
        if (arg_index == sub->args->length - 1) {
          last_arg_type = arg_type;
        }
      }
      if (arg_allow_count > SPVM_LIMIT_C_SUB_ARGS_MAX_COUNT) {
        SPVM_COMPILER_error(compiler, "Too many subroutine arguments count. Max count of subroutine arguments is 255 at %s line %d\n", sub->op_sub->file, sub->op_sub->line);
        return;
      }
      
      if (sub->have_vaarg && !SPVM_TYPE_is_array_type(compiler, last_arg_type->basic_type->id, last_arg_type->dimension, last_arg_type->flag)) {
        SPVM_COMPILER_error(compiler, "When ... is specified, last argument type must be array at %s line %d\n", sub->op_sub->file, sub->op_sub->line);
        return;
      }
      
      // Is constant sub
      {
        SPVM_OP* op_block = sub->op_block;
        if (op_block) {
          SPVM_OP* op_statements = op_block->last;
          
          int32_t statements_count = SPVM_OP_get_list_elements_count(compiler, op_statements);
          if (statements_count == 1) {
            SPVM_OP* op_return = op_statements->last;
            assert(op_return->id == SPVM_OP_C_ID_RETURN);
            
            SPVM_OP* op_constant = op_return->first;
            if (op_constant && op_constant->id == SPVM_OP_C_ID_CONSTANT) {
              sub->is_constant = 1;
              sub->op_inline = op_constant;
            }
          }
        }
      }
      
      // Is simple constructor sub
      {
        SPVM_OP* op_block = sub->op_block;
        if (op_block) {
          SPVM_OP* op_statements = op_block->last;
          
          int32_t statements_count = SPVM_OP_get_list_elements_count(compiler, op_statements);
          if (statements_count == 1) {
            SPVM_OP* op_return = op_statements->last;
            assert(op_return->id == SPVM_OP_C_ID_RETURN);
            
            SPVM_OP* op_new = op_return->first;
            if (op_new && op_new->id == SPVM_OP_C_ID_NEW) {
              SPVM_OP* op_type = op_new->first;
              assert(op_type->id == SPVM_OP_C_ID_TYPE);
              SPVM_TYPE* type = op_type->uv.type;
              if (SPVM_TYPE_is_package_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                if (sub->args->length == 0) {
                  sub->is_simple_constructor = 1;
                  sub->op_inline = op_type;
                }
              }
            }
          }
        }
      }
      
      // Can't return refernece type
      if (SPVM_TYPE_is_ref_type(compiler, sub->return_type->basic_type->id, sub->return_type->dimension, sub->return_type->flag)) {
        SPVM_COMPILER_error(compiler, "Can't return reference type at %s line %d\n", sub->op_sub->file, sub->op_sub->line);
        return;
      }

      // Create sub signature
      const char* sub_signature = SPVM_COMPILER_create_sub_signature(compiler, sub);
      sub->signature = sub_signature;

      // Copy has_precomile_descriptor from anon sub defined package
      if (sub->anon_sub_defined_package_name) {
        SPVM_PACKAGE* anon_sub_defined_package = SPVM_HASH_fetch(compiler->package_symtable, sub->anon_sub_defined_package_name, strlen(sub->anon_sub_defined_package_name));
        SPVM_LIST_push(anon_sub_defined_package->anon_subs, sub);
        package->has_precompile_descriptor = anon_sub_defined_package->has_precompile_descriptor;
      }
    }
  }
  
  for (int32_t package_index = compiler->cur_package_base; package_index < compiler->packages->length; package_index++) {
    SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_index);
    // Check subs
    for (int32_t i = 0; i < package->subs->length; i++) {
      SPVM_SUB* sub = SPVM_LIST_fetch(package->subs, i);
      // Set sub precompile flag if package have precompile descriptor
      if (package->has_precompile_descriptor && sub->can_precompile) {
        sub->flag |= SPVM_SUB_C_FLAG_PRECOMPILE;
      }
    }
  }
  
  // Check import subroutine
  for (int32_t package_index = compiler->cur_package_base; package_index < compiler->packages->length; package_index++) {
    SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_index);
    const char* package_name = package->op_name->uv.name;
    SPVM_LIST* op_uses = package->op_uses;
    
    for (int32_t uses_index = 0; uses_index < op_uses->length; uses_index++) {
      SPVM_OP* op_use = (SPVM_OP*)SPVM_LIST_fetch(op_uses, uses_index);
      
      SPVM_OP* use_op_type = op_use->uv.use->op_type;
      const char* use_package_name = use_op_type->uv.type->basic_type->name;
      SPVM_PACKAGE* use_package = SPVM_HASH_fetch(compiler->package_symtable, use_package_name, strlen(use_package_name));
      
      SPVM_LIST* import_sub_names = op_use->uv.use->sub_names;
      if (import_sub_names) {
        for (int32_t import_sub_name_index = 0; import_sub_name_index < import_sub_names->length; import_sub_name_index++) {
          const char* import_sub_name = SPVM_LIST_fetch(import_sub_names, import_sub_name_index);
          SPVM_SUB* found_sub = SPVM_HASH_fetch(
            use_package->sub_symtable,
            import_sub_name,
            strlen(import_sub_name)
          );
          if (!found_sub) {
            SPVM_COMPILER_error(compiler, "Fail subroutine importing. Not found \"%s->%s\" at %s line %d\n", use_package_name, import_sub_name, op_use->file, op_use->line);
            return;
          }
        }
      }
    }
  }
}
