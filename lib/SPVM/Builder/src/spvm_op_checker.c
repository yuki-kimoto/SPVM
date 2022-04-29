#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <ctype.h>

#include "spvm_compiler.h"
#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_allocator.h"
#include "spvm_op.h"
#include "spvm_op_checker.h"
#include "spvm_method.h"
#include "spvm_constant.h"
#include "spvm_field.h"
#include "spvm_var_decl.h"
#include "spvm_var.h"
#include "spvm_type.h"
#include "spvm_class.h"
#include "spvm_field_access.h"
#include "spvm_call_method.h"
#include "spvm_type.h"
#include "spvm_switch_info.h"
#include "spvm_class_var.h"
#include "spvm_class_var_access.h"
#include "spvm_block.h"
#include "spvm_basic_type.h"
#include "spvm_case_info.h"
#include "spvm_array_field_access.h"
#include "spvm_check_ast_info.h"
#include "spvm_string_buffer.h"
#include "spvm_use.h"
#include "spvm_interface.h"
#include "spvm_constant_string.h"

int SPVM_OP_CHECKER_method_name_cmp(const void* method1_ptr, const void* method2_ptr) {
  
  SPVM_METHOD* method1 = *(SPVM_METHOD**)method1_ptr;
  SPVM_METHOD* method2 = *(SPVM_METHOD**)method2_ptr;
  
  const char* method1_name = method1->name;
  const char* method2_name = method2->name;
  
  return strcmp(method1_name, method2_name);
}

void SPVM_OP_CHECKER_free_mem_id(SPVM_COMPILER* compiler, SPVM_LIST* mem_stack, SPVM_VAR_DECL* var_decl) {
  (void)compiler;
  
  SPVM_TYPE* my_type = var_decl->type;
  
  int32_t width = SPVM_TYPE_get_width(compiler, my_type->basic_type->id, my_type->dimension, my_type->flag);

  for (int32_t mem_id = 0; mem_id < mem_stack->length; mem_id++) {
    int32_t my_id = (intptr_t)SPVM_LIST_get(mem_stack, mem_id);
    if (my_id == var_decl->id) {
      assert(mem_id + width <= mem_stack->length);
      for (int32_t i = 0; i < width; i++) {
        mem_stack->values[mem_id + i] = (void*)(intptr_t)-1;
      }
    }
  }
}

int32_t SPVM_OP_CHECKER_get_mem_id(SPVM_COMPILER* compiler, SPVM_LIST* mem_stack, SPVM_VAR_DECL* var_decl) {
  
  int32_t found_mem_id = -1;
  
  SPVM_TYPE* my_type = var_decl->type;

  int32_t width = SPVM_TYPE_get_width(compiler, my_type->basic_type->id, my_type->dimension, my_type->flag);
  
  // Search free memory
  int32_t found = 0;
  for (int32_t mem_id = 0; mem_id < mem_stack->length; mem_id++) {
    if (mem_id + width <= mem_stack->length) {
      int32_t is_used = 0;
      for (int32_t i = 0; i < width; i++) {
        int32_t my_id = (intptr_t)SPVM_LIST_get(mem_stack, mem_id + i);
        if (my_id >= 0) {
          is_used = 1;
          break;
        }
      }
      if (!is_used) {
        found = 1;
        found_mem_id = mem_id;
        for (int32_t i = 0; i < width; i++) {
          mem_stack->values[mem_id + i] = (void*)(intptr_t)var_decl->id;
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
      SPVM_LIST_push(mem_stack, (void*)(intptr_t)var_decl->id);
    }
  }
  
  return found_mem_id;
}

SPVM_OP* SPVM_OP_CHECKER_new_op_var_tmp(SPVM_COMPILER* compiler, SPVM_METHOD* method, SPVM_TYPE* type, const char* file, int32_t line) {

  // Temparary variable name
  char* name = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, strlen("$.tmp_2147483647") + 1);
  sprintf(name, "$.tmp_%d", method->tmp_vars_length);
  method->tmp_vars_length++;
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NAME, file, line);
  op_name->uv.name = name;
  SPVM_OP* op_var = SPVM_OP_build_var(compiler, op_name);
  SPVM_OP* op_var_decl = SPVM_OP_new_op_var_decl(compiler, file, line);
  assert(type);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  SPVM_OP_build_var_decl(compiler, op_var_decl, op_var, op_type, NULL);
  
  op_var_decl->uv.var_decl->is_tmp = 1;
  op_var->uv.var->is_initialized = 1;
  
  return op_var;
}

void SPVM_OP_CHECKER_check_tree(SPVM_COMPILER* compiler, SPVM_OP* op_root, SPVM_CHECK_AST_INFO* check_ast_info) {

  // Class
  SPVM_CLASS* class = check_ast_info->class;
  
  // Method
  SPVM_METHOD* method = check_ast_info->method;
  
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
        const char* use_class_name = use->class_name;
        const char* not_found_class_class_name = SPVM_HASH_get(compiler->not_found_class_class_symtable, use_class_name, strlen(use_class_name));
        if (not_found_class_class_name) {
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
          int32_t block_var_decl_base = check_ast_info->my_stack->length;
          SPVM_LIST_push(check_ast_info->block_var_decl_base_stack, (void*)(intptr_t)block_var_decl_base);
          
          if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_LOOP_STATEMENTS) {
            check_ast_info->loop_block_stack_length++;
          }
          else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_EVAL) {
            check_ast_info->eval_block_stack_length++;
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
              
              const char* file = op_list_elements->file;
              int32_t line = op_list_elements->line;
              
              SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, file, line);

              SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, file, line);
              op_cur = op_sequence;
              SPVM_OP* op_assign_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, file, line);
              
              // Array length
              int32_t length = 0;
              {
                SPVM_OP* op_term_element = op_list_elements->first;
                int32_t index = 0;
                while ((op_term_element = SPVM_OP_sibling(compiler, op_term_element))) {
                  index++;
                }
                length = index;
              }

              SPVM_OP* op_type_element = NULL;
              SPVM_OP* op_type_new = NULL;
              if (length > 0) {
                SPVM_OP* op_term_element = op_list_elements->first;

                op_term_element = SPVM_OP_sibling(compiler, op_term_element);
                if (op_term_element->id == SPVM_OP_C_ID_UNDEF) {
                  SPVM_COMPILER_error(compiler, "Array initialization first element must not be undef at %s line %d", file, line);
                  return;
                }
                SPVM_TYPE* type_term_element = SPVM_OP_get_type(compiler, op_term_element);

                // Create element type
                op_type_element = SPVM_OP_new_op_type(compiler, type_term_element, file, line);
                
                // Create array type
                SPVM_TYPE* type_new = SPVM_TYPE_new(compiler, type_term_element->basic_type->id, type_term_element->dimension + 1, 0);
                op_type_new = SPVM_OP_new_op_type(compiler, type_new, file, line);
              }
              else if (length == 0) {
                op_type_element = SPVM_OP_new_op_any_object_type(compiler, op_cur->file, op_cur->line);
                SPVM_TYPE* type_element = op_type_element->uv.type;
                SPVM_TYPE* type_new = SPVM_TYPE_new(compiler, type_element->basic_type->id, type_element->dimension + 1, 0);
                op_type_new = SPVM_OP_new_op_type(compiler, type_new, file, line);
              }
              else {
                assert(0);
              }
              
              SPVM_OP* op_var_tmp_new = SPVM_OP_CHECKER_new_op_var_tmp(compiler, method, op_type_new->uv.type, file, line);
              
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
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_NEXT: {
              if (check_ast_info->loop_block_stack_length == 0) {
                SPVM_COMPILER_error(compiler, "next statement must be in loop block at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              break;
            }
            case SPVM_OP_C_ID_LAST: {
              if (check_ast_info->loop_block_stack_length == 0) {
                SPVM_COMPILER_error(compiler, "last statement must be in loop block at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              break;
            }
            case SPVM_OP_C_ID_BREAK: {
              if (check_ast_info->op_switch_stack->length == 0) {
                SPVM_COMPILER_error(compiler, "break statement must be in switch block or switch block at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              break;
            }
            case SPVM_OP_C_ID_CURRENT_CLASS_NAME: {
              SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
              SPVM_OP* op_constant = SPVM_OP_new_op_constant_string(compiler, class->name, strlen(class->name), op_cur->file, op_cur->line);

              SPVM_OP_CHECKER_check_tree(compiler, op_constant, check_ast_info);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
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
                SPVM_COMPILER_error(compiler, "Operand of refcnt must be variable of object type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_REFOP: {
              
              SPVM_OP* op_term = op_cur->first;
              
              SPVM_TYPE* term_type = SPVM_OP_get_type(compiler, op_term);
              
              // Must be object type
              if (!SPVM_TYPE_is_object_type(compiler, term_type->basic_type->id, term_type->dimension, term_type->flag)) {
                SPVM_COMPILER_error(compiler, "The operand of ref operator must be a object type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_DUMP: {
              
              SPVM_OP* op_term = op_cur->first;
              
              SPVM_TYPE* term_type = SPVM_OP_get_type(compiler, op_term);
              
              // Must be object type
              if (!SPVM_TYPE_is_object_type(compiler, term_type->basic_type->id, term_type->dimension, term_type->flag)) {
                SPVM_COMPILER_error(compiler, "The operand of dump operator must be a object type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_NEW_STRING_LEN: {
              
              SPVM_OP* op_length_term = op_cur->first;

              SPVM_TYPE* length_type = SPVM_OP_get_type(compiler, op_length_term);
              
              assert(length_type);
              int32_t is_length_type_integral_type_except_for_long;
              if (SPVM_TYPE_is_integral_type(compiler, length_type->basic_type->id, length_type->dimension, length_type->flag)) {
                SPVM_OP_CHECKER_apply_unary_numeric_widening_conversion(compiler, op_length_term);
                
                SPVM_TYPE* length_type_after_conversion = SPVM_OP_get_type(compiler, op_cur->first);
                
                if (SPVM_TYPE_is_int_type(compiler, length_type_after_conversion->basic_type->id, length_type_after_conversion->dimension, length_type_after_conversion->flag)) {
                  is_length_type_integral_type_except_for_long = 1;
                }
                else {
                  is_length_type_integral_type_except_for_long = 0;
                }
              }
              else {
                is_length_type_integral_type_except_for_long = 0;
              }
              
              if (!is_length_type_integral_type_except_for_long) {
                SPVM_COMPILER_error(compiler, "The length of the new_string_len operator must be an integral type except for a long type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_SWITCH: {
              
              SPVM_OP* op_switch_condition = op_cur->first;
              
              SPVM_TYPE* term_type = SPVM_OP_get_type(compiler, op_switch_condition->first);
              
              // Check type
              if (!term_type || !(term_type->dimension == 0 && term_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT)) {
                SPVM_COMPILER_error(compiler, "Switch condition must be int value at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              SPVM_SWITCH_INFO* switch_info = op_cur->uv.switch_info;
              SPVM_LIST* cases = switch_info->case_infos;
              int32_t cases_length = cases->length;
              
              // Need at least one case
              if (cases_length == 0) {
                SPVM_COMPILER_error(compiler, "Switch statement need at least one case statement in  at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Check case type
              for (int32_t i = 0; i < cases_length; i++) {
                SPVM_CASE_INFO* case_info = SPVM_LIST_get(cases, i);
                SPVM_OP* op_constant = case_info->op_case_info->first;
                SPVM_CONSTANT* constant = op_constant->uv.constant;

                if (op_constant->id != SPVM_OP_C_ID_CONSTANT) {
                  SPVM_COMPILER_error(compiler, "case value must be constant at %s line %d", op_cur->file, op_cur->line);
                  return;
                }

                // Upgrade byte to int
                if (constant->type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                  constant->type = SPVM_TYPE_new_int_type(compiler);
                  constant->value.ival = (int32_t)constant->value.bval;
                }
                
                SPVM_TYPE* case_value_type = SPVM_OP_get_type(compiler, op_constant);
                if (!(case_value_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT && case_value_type->dimension == 0)) {
                  SPVM_COMPILER_error(compiler, "case value must be int constant at %s line %d", case_info->op_case_info->file, case_info->op_case_info->line);
                  return;
                }
                case_info->condition_value = constant->value.ival;
              }

              // sort by asc order
              for (int32_t i = 0; i < switch_info->case_infos->length; i++) {
                for (int32_t j = i + 1; j < switch_info->case_infos->length; j++) {
                  SPVM_CASE_INFO* case_i = SPVM_LIST_get(switch_info->case_infos, i);
                  SPVM_CASE_INFO* case_j = SPVM_LIST_get(switch_info->case_infos, j);
                  int32_t match_i = case_i->condition_value;
                  int32_t match_j = case_j->condition_value;
                  
                  if (match_i > match_j) {
                    SPVM_LIST_set(switch_info->case_infos, i, case_j);
                    SPVM_LIST_set(switch_info->case_infos, j, case_i);
                  }
                }
              }
              
              SPVM_LIST_pop(check_ast_info->op_switch_stack);

              op_cur->uv.switch_info->switch_id = compiler->switch_infos->length;
              SPVM_LIST_push(compiler->switch_infos, op_cur->uv.switch_info);
              
              // Min
              SPVM_CASE_INFO* case_info_mini = SPVM_LIST_get(switch_info->case_infos, 0);
              int32_t min = case_info_mini->condition_value;
              
              // Max
              SPVM_CASE_INFO* case_info_max = SPVM_LIST_get(switch_info->case_infos, switch_info->case_infos->length - 1);
              int32_t max = case_info_max->condition_value;
              
              // Decide switch type
              switch_info->id = SPVM_SWITCH_INFO_C_ID_LOOKUP_SWITCH;
              
              break;
            }
            case SPVM_OP_C_ID_CASE: {
              if (check_ast_info->op_switch_stack->length > 0) {
                SPVM_OP* op_switch = SPVM_LIST_get(check_ast_info->op_switch_stack, check_ast_info->op_switch_stack->length - 1);
                SPVM_SWITCH_INFO* switch_info = op_switch->uv.switch_info;
                op_cur->uv.case_info->index = switch_info->case_infos->length;
                SPVM_LIST_push(switch_info->case_infos, op_cur->uv.case_info);
              }
              break;
            }
            case SPVM_OP_C_ID_DEFAULT: {
              if (check_ast_info->op_switch_stack->length > 0) {
                SPVM_OP* op_switch = SPVM_LIST_get(check_ast_info->op_switch_stack, check_ast_info->op_switch_stack->length - 1);
                SPVM_SWITCH_INFO* switch_info = op_switch->uv.switch_info;
                
                if (switch_info->op_default) {
                  SPVM_COMPILER_error(compiler, "Duplicate default statement at %s line %d", op_cur->file, op_cur->line);
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
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
              }
              // Numeric type
              else if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag))
              {
                // Convert byte or short type to int type
                SPVM_OP_CHECKER_apply_unary_numeric_widening_conversion(compiler, op_first);
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
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
                SPVM_COMPILER_error(compiler, "Operand of condition must be numeric type or object type or undef type at %s line %d", op_cur->file, op_cur->line);
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
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
              }
              // expression == undef
              else if (!SPVM_TYPE_is_undef_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_undef_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                if (!SPVM_TYPE_is_object_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                  SPVM_COMPILER_error(compiler, "The left operand of the == operator must be a object type at %s line %d", op_cur->file, op_cur->line);
                  return;
                }
              }
              // undef == expression
              else if (SPVM_TYPE_is_undef_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && !SPVM_TYPE_is_undef_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                if (!SPVM_TYPE_is_object_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                  SPVM_COMPILER_error(compiler, "The right operand of the == operator must be a object type at %s line %d", op_cur->file, op_cur->line);
                  return;
                }
              }
              // expression == expression
              else {
                int32_t is_valid_type;
                
                // Numeric type
                if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                  
                  is_valid_type = 1;
                  
                  SPVM_OP_CHECKER_apply_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
                  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
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
                  SPVM_COMPILER_error(compiler, "Left and right operand of == operator must be a numeric type or object type at %s line %d", op_cur->file, op_cur->line);
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
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
              }
              // expression == undef
              else if (!SPVM_TYPE_is_undef_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_undef_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                if (!SPVM_TYPE_is_object_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                  SPVM_COMPILER_error(compiler, "The left operand of the == operator must be a object type at %s line %d", op_cur->file, op_cur->line);
                  return;
                }
              }
              // undef == expression
              else if (SPVM_TYPE_is_undef_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && !SPVM_TYPE_is_undef_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                if (!SPVM_TYPE_is_object_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                  SPVM_COMPILER_error(compiler, "The right operand of the == operator must be a object type at %s line %d", op_cur->file, op_cur->line);
                  return;
                }
              }
              // expression == expression
              else {
                int32_t is_valid_type;
                
                // Numeric type
                if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) && SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                  
                  is_valid_type = 1;
                  
                  SPVM_OP_CHECKER_apply_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
                  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
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
                  SPVM_COMPILER_error(compiler, "Left and right operand of == operator must be a numeric type or object type at %s line %d", op_cur->file, op_cur->line);
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
                SPVM_COMPILER_error(compiler, "The left operand of the > operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of the > operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Apply binary numeric conversion
              SPVM_OP_CHECKER_apply_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_NUMERIC_GE: {

              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

              // Left operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of the >= operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of the >= operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Apply binary numeric conversion
              SPVM_OP_CHECKER_apply_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_NUMERIC_LT: {

              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of the < operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of the < operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Apply binary numeric conversion
              SPVM_OP_CHECKER_apply_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }

              break;
            }
            case SPVM_OP_C_ID_NUMERIC_LE: {

              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

              // Left operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of the <= operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of the <= operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Apply binary numeric conversion
              SPVM_OP_CHECKER_apply_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_NUMERIC_CMP: {

              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

              // Left operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of the > operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of the > operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Apply binary numeric conversion
              SPVM_OP_CHECKER_apply_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_STRING_EQ: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be the string type
              if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of eq operator must be a string or byte[] type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be the string type
              if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of eq operator must be a string or byte[] type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_STRING_NE: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be the string type
              if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of ne operator must be a string or byte[] type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be the string type
              if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of ne operator must be a string or byte[] type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_STRING_GT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be the string type
              if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of gt operator must be a string or byte[] type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be the string type
              if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of gt operator must be a string or byte[] type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_STRING_GE: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be the string type
              if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of ge operator must be a string or byte[] type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be the string type
              if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of ge operator must be a string or byte[] type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_STRING_LT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be the string type
              if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of lt operator must be a string or byte[] type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be the string type
              if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of lt operator must be a string or byte[] type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_STRING_LE: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be the string type
              if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of le operator must be a string or byte[] type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be the string type
              if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of le operator must be a string or byte[] type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_STRING_CMP: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be the string type
              if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of cmp operator must be a string or byte[] type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be the string type
              if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of cmp operator must be a string or byte[] type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_CONCAT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left type is numeric type
              if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_OP_CHECKER_apply_numeric_to_string_conversion(compiler, op_cur->first);
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
              }
              // Left type is not string type or byte array type
              else if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of \".\" operator must be a string or byte[] type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand is numeric type
              if (SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_OP_CHECKER_apply_numeric_to_string_conversion(compiler, op_cur->last);
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
              }
              // Right operand is not string type or byte array type
              else if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of \".\" operator must be a string or byte[] type at %s line %d", op_cur->file, op_cur->line);
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
                
                int32_t memory_blocks_count_tmp = compiler->allocator->memory_blocks_count_tmp;
                char* concat_string_tmp = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, string1_length + string2_length + 1);
                memcpy(concat_string_tmp, string1, string1_length);
                memcpy(concat_string_tmp + string1_length, string2, string2_length);
                int32_t concant_string_length = string1_length + string2_length;
                
                SPVM_CONSTANT_STRING* concat_string_string = SPVM_CONSTANT_STRING_new(compiler, concat_string_tmp, concant_string_length);
                const char* concat_string = concat_string_string->value;
                
                SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, concat_string_tmp);
                
                assert(compiler->allocator->memory_blocks_count_tmp == memory_blocks_count_tmp);
                
                SPVM_OP* op_concat_constant_string = SPVM_OP_new_op_constant_string(compiler, concat_string, concant_string_length, op_cur->file, op_cur->line);
                
                SPVM_OP_replace_op(compiler, op_stab, op_concat_constant_string);
                
                op_cur = op_concat_constant_string;
              }
              
              break;
            }
            case SPVM_OP_C_ID_NEW: {
              assert(op_cur->first);
              if (op_cur->first->id == SPVM_OP_C_ID_TYPE) {
                SPVM_OP* op_type = op_cur->first;
                SPVM_TYPE* type = op_type->uv.type;
                
                SPVM_CLASS* new_class = type->basic_type->class;
                
                // Anon sub
                if (new_class && new_class->is_anon) {
                  SPVM_OP* op_type = op_cur->first;
                  
                  SPVM_METHOD* anon_method = SPVM_LIST_get(new_class->methods, 0);
                  if (anon_method->captures->length) {
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
                    SPVM_OP* op_var_tmp_new = SPVM_OP_CHECKER_new_op_var_tmp(compiler, method, op_type->uv.type, file, line);
                    
                    SPVM_OP_build_assign(compiler, op_assign_new, op_var_tmp_new, op_new);

                    SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_assign_new);
                    
                    // Check capture variable exists
                    for (int32_t caputre_index = 0; caputre_index < anon_method->captures->length; caputre_index++) {
                      SPVM_VAR_DECL* capture_var_decl = SPVM_LIST_get(anon_method->captures, caputre_index);
                      const char* capture_name = capture_var_decl->var->name;

                      // Search same name variable
                      SPVM_VAR_DECL* found_var_decl = NULL;
                      for (int32_t stack_var_decl_index = check_ast_info->my_stack->length - 1; stack_var_decl_index >= 0; stack_var_decl_index--) {
                        SPVM_VAR_DECL* var_decl = SPVM_LIST_get(check_ast_info->my_stack, stack_var_decl_index);
                        if (strcmp(capture_name, var_decl->var->name) == 0) {
                          found_var_decl = var_decl;
                          break;
                        }
                      }
                      if (!found_var_decl) {
                        SPVM_COMPILER_error(compiler, "Capture variable \"%s\" is not declared at %s line %d", capture_name, op_cur->file, op_cur->line);
                        return;
                      }
                      
                      // Create field assignment
                      SPVM_OP* op_name_invoker = SPVM_OP_new_op_name(compiler, op_var_tmp_new->uv.var->name , op_cur->file, op_cur->line);
                      SPVM_OP* op_term_invoker = SPVM_OP_new_op_var(compiler, op_name_invoker);
                      op_term_invoker->uv.var->var_decl = found_var_decl;
                      SPVM_OP* op_name_field = SPVM_OP_new_op_name(compiler, found_var_decl->var->name + 1, op_cur->file, op_cur->line);
                      
                      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, op_cur->file, op_cur->line);
                      SPVM_OP_build_field_access(compiler, op_field_access, op_term_invoker, op_name_field);
                      
                      SPVM_OP* op_name_var_capture = SPVM_OP_new_op_name(compiler, found_var_decl->var->name, op_cur->file, op_cur->line);
                      SPVM_OP* op_var_capture = SPVM_OP_new_op_var(compiler, op_name_var_capture);
                      op_var_capture->uv.var->var_decl = found_var_decl;

                      SPVM_FIELD* capture_field = SPVM_HASH_get(new_class->field_symtable, found_var_decl->var->name + 1, strlen(found_var_decl->var->name) - 1);
                      op_field_access->uv.field_access->field = capture_field;
                      
                      SPVM_OP* op_assign_field_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                      SPVM_OP_build_assign(compiler, op_assign_field_access, op_field_access, op_var_capture);
                      
                      SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_assign_field_access);
                    }
                    
                    SPVM_OP* op_var_tmp_ret = SPVM_OP_new_op_var_clone(compiler, op_var_tmp_new, op_var_tmp_new->file, op_var_tmp_new->line);
                    
                    SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_var_tmp_ret);
                    
                    SPVM_OP_replace_op(compiler, op_stab, op_sequence);
                    
                    SPVM_OP_CHECKER_check_tree(compiler, op_sequence, check_ast_info);
                    if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                      return;
                    }
                  }
                }
                // Array type
                else if (SPVM_TYPE_is_array_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                  
                  SPVM_OP* op_index_term = op_type->last;

                  SPVM_TYPE* index_type = SPVM_OP_get_type(compiler, op_index_term);
                  
                  assert(index_type);
                  int32_t is_length_type_integral_type_except_for_long;
                  if (SPVM_TYPE_is_integral_type(compiler, index_type->basic_type->id, index_type->dimension, index_type->flag)) {
                    SPVM_OP_CHECKER_apply_unary_numeric_widening_conversion(compiler, op_index_term);
                    
                    SPVM_TYPE* index_type_after_conversion = SPVM_OP_get_type(compiler, op_type->last);
                    
                    if (SPVM_TYPE_is_int_type(compiler, index_type_after_conversion->basic_type->id, index_type_after_conversion->dimension, index_type_after_conversion->flag)) {
                      is_length_type_integral_type_except_for_long = 1;
                    }
                    else {
                      is_length_type_integral_type_except_for_long = 0;
                    }
                  }
                  else {
                    is_length_type_integral_type_except_for_long = 0;
                  }
                  
                  if (!is_length_type_integral_type_except_for_long) {
                    const char* type_name = SPVM_TYPE_new_type_name(compiler, type->basic_type->id, type->dimension, type->flag);
                    SPVM_COMPILER_error(compiler, "The array length of new %s must be an integral type except for a long type at %s line %d", type_name, op_cur->file, op_cur->line);
                    return;
                  }
                }
                // Numeric type
                else if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                  SPVM_COMPILER_error(compiler, "new operator can't receive numeric type at %s line %d", op_cur->file, op_cur->line);
                  return;
                }
                // Object type
                else if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                  SPVM_CLASS* class = SPVM_HASH_get(compiler->class_symtable, type->basic_type->name, strlen(type->basic_type->name));
                  
                  if (class->category == SPVM_CLASS_C_CATEGORY_CALLBACK) {
                    SPVM_COMPILER_error(compiler, "Can't create the object of a callback type at %s line %d", op_cur->file, op_cur->line);
                    return;
                  }
                  else if (class->category == SPVM_CLASS_C_CATEGORY_INTERFACE) {
                    SPVM_COMPILER_error(compiler, "Can't create the object of a interface type at %s line %d", op_cur->file, op_cur->line);
                    return;
                  }
                  else if (class->category == SPVM_CLASS_C_CATEGORY_MULNUM) {
                    SPVM_COMPILER_error(compiler, "Can't create the object of a multi numeric type at %s line %d", op_cur->file, op_cur->line);
                    return;
                  }
                  else if (class->is_pointer) {
                    SPVM_COMPILER_error(compiler, "Can't create the object of a pointer type at %s line %d", op_cur->file, op_cur->line);
                    return;
                  }
                  
                  // Access control
                  int32_t is_private;
                  if (class->is_public) {
                    is_private = 0;
                  }
                  // Default
                  else {
                    is_private = 1;
                  }
                  
                  if (is_private && !(op_cur->flag & SPVM_OP_C_FLAG_NEW_INLINE)) {
                    if (!SPVM_OP_is_allowed(compiler, method->class->op_class, new_class->op_class)) {
                      SPVM_COMPILER_error(compiler, "Can't create object of private class at %s line %d", op_cur->file, op_cur->line);
                      return;
                    }
                  }
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
            case SPVM_OP_C_ID_BIT_XOR: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Can receive only integral type
              if (!SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag) || !SPVM_TYPE_is_integral_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "^ operator can receive only integral type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              SPVM_OP_CHECKER_apply_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
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
              else if (SPVM_TYPE_is_mulnum_type(compiler, check_type->basic_type->id, check_type->dimension, check_type->flag)) {
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
                  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
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
                  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                    return;
                  }
                  op_cur = op_assign_bool;
                }
              }
              else {
                // Left term must be object type
                if (!SPVM_TYPE_is_object_type(compiler, term_type->basic_type->id, term_type->dimension, term_type->flag)) {
                  SPVM_COMPILER_error(compiler, "The left operand of the isa operator must be a object type at %s line %d", op_cur->file, op_cur->line);
                  return;
                }
                
                // Right type must be object type
                if (!SPVM_TYPE_is_object_type(compiler, check_type->basic_type->id, check_type->dimension, check_type->flag)) {
                  SPVM_COMPILER_error(compiler, "The right operand of the isa operator must be a object type at %s line %d", op_cur->file, op_cur->line);
                  return;
                }
              }
              
              break;
            }
            case SPVM_OP_C_ID_ARRAY_LENGTH: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              // First value must be array
              if (!SPVM_TYPE_is_array_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of the @ operator must be a array type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_STRING_LENGTH: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              // First must be the string type
              if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "length argument must be the string type at %s line %d", op_cur->file, op_cur->line);
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
                SPVM_COMPILER_error(compiler, "increment operand must be numeric type at %s line %d", op_cur->file, op_cur->line);
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
                SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, op_cur->file, op_cur->line);
                SPVM_OP* op_convert_type = SPVM_OP_new_op_type(compiler, term_mutable_type, op_cur->file, op_cur->line);
                SPVM_OP_build_convert(compiler, op_convert, op_convert_type, op_add, NULL);
                SPVM_OP_build_assign(compiler, op_assign, op_term_mutable_clone, op_convert);
              }
              else {
                SPVM_OP_build_assign(compiler, op_assign, op_term_mutable_clone, op_add);
              }
              
              SPVM_OP_replace_op(compiler, op_stab, op_assign);
              
              op_cur = op_assign;
              
              SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
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
                SPVM_COMPILER_error(compiler, "decrement operand must be numeric type at %s line %d", op_cur->file, op_cur->line);
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
                SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, op_cur->file, op_cur->line);
                SPVM_OP* op_dist_type = SPVM_OP_new_op_type(compiler, term_mutable_type, op_cur->file, op_cur->line);
                SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_subtract, NULL);
                SPVM_OP_build_assign(compiler, op_assign, op_term_mutable_clone, op_convert);
              }
              else {
                SPVM_OP_build_assign(compiler, op_assign, op_term_mutable_clone, op_subtract);
              }
              
              SPVM_OP_replace_op(compiler, op_stab, op_assign);
              
              op_cur = op_assign;
              
              SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
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
                SPVM_COMPILER_error(compiler, "increment operand must be numeric type at %s line %d", op_cur->file, op_cur->line);
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
              SPVM_OP* op_var_tmp1 = SPVM_OP_CHECKER_new_op_var_tmp(compiler, method, term_mutable_type, op_cur->file, op_cur->line);

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
                SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, op_cur->file, op_cur->line);
                SPVM_OP* op_dist_type = SPVM_OP_new_op_type(compiler, term_mutable_type, op_cur->file, op_cur->line);
                SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_add, NULL);
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
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
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
                SPVM_COMPILER_error(compiler, "decrement operand must be numeric type at %s line %d", op_cur->file, op_cur->line);
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
              
              SPVM_OP* op_var_tmp1 = SPVM_OP_CHECKER_new_op_var_tmp(compiler, method, term_mutable_type, op_cur->file, op_cur->line);
              
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
                SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, op_cur->file, op_cur->line);
                SPVM_OP* op_dist_type = SPVM_OP_new_op_type(compiler, term_mutable_type, op_cur->file, op_cur->line);
                SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_subtract, NULL);
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
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
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
                SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, op_cur->file, op_cur->line);
                SPVM_OP* op_dist_type = SPVM_OP_new_op_type(compiler, term_mutable_type, op_cur->file, op_cur->line);
                SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_culc, NULL);
                SPVM_OP_build_assign(compiler, op_assign, op_term_mutable_clone, op_convert);
              }
              else {
                SPVM_OP_build_assign(compiler, op_assign, op_term_mutable_clone, op_culc);
              }
              
              SPVM_OP_replace_op(compiler, op_stab, op_assign);
              
              op_cur = op_assign;
              
              SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
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
                SPVM_VAR_DECL* var_decl = op_term_dist->uv.var->var_decl;
                if (var_decl->type == NULL) {
                  var_decl->type = SPVM_OP_get_type(compiler, op_term_src);
                }
                if (var_decl->type == NULL) {
                  SPVM_COMPILER_error(compiler, "Type can't be detected at %s line %d", var_decl->op_var_decl->file, var_decl->op_var_decl->line);
                  return;
                }
                op_term_dist->uv.var->is_initialized = 1;
              }
              
              // Check if source can be assigned to dist
              // If needed, numeric conversion op is added
              dist_type = SPVM_OP_get_type(compiler, op_term_dist);
              SPVM_OP_CHECKER_check_assign(compiler, dist_type, op_term_src, "assign operator", op_cur->file, op_cur->line);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }

              // If dist is string access and const, it is invalid
              if (op_term_dist->id == SPVM_OP_C_ID_ARRAY_ACCESS && op_term_dist->flag & SPVM_OP_C_FLAG_ARRAY_ACCESS_STRING) {
                SPVM_OP* op_array = op_term_dist->first;
                SPVM_TYPE* array_type = SPVM_OP_get_type(compiler, op_array);
                int32_t is_mutable = array_type->flag & SPVM_TYPE_C_FLAG_MUTABLE;

                if(!is_mutable) {
                  SPVM_COMPILER_error(compiler, "Can't set the character of non-mutable string at %s line %d", op_term_dist->file, op_term_dist->line);
                  return;
                }
              }
              
              break;
            }
            case SPVM_OP_C_ID_RETURN: {
              
              SPVM_OP* op_term = op_cur->first;
              
              // Void type
              if (SPVM_TYPE_is_void_type(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag)) {
                if (op_term) {
                  SPVM_COMPILER_error(compiler, "void method must not have return value at %s line %d", op_cur->file, op_cur->line);
                  return;
                }
              }
              else {
                if (op_term) {
                  // Automatical numeric conversion
                  SPVM_OP_CHECKER_check_assign(compiler, method->return_type, op_term, "return statement", op_cur->file, op_cur->line);
                  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                    return;
                  }
                }
                else {
                  SPVM_COMPILER_error(compiler, "non-void method must have return value at %s line %d", op_cur->file, op_cur->line);
                  return;
                }
              }

              break;
            }
            case SPVM_OP_C_ID_PLUS: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              // Operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Operand of unary + operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Apply unary widening conversion
              SPVM_OP_CHECKER_apply_unary_numeric_widening_conversion(compiler, op_cur->first);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_COPY: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              // Operand must be numeric type
              if (!SPVM_TYPE_is_object_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Operand of unary + operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_MINUS: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              // Operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Operand of unary - operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              // Apply unary widening conversion
              SPVM_OP_CHECKER_apply_unary_numeric_widening_conversion(compiler, op_cur->first);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_BIT_NOT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              // Operand must be numeric type
              if (!SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "Operand of ~ operator must be an integral type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Apply unary widening conversion
              SPVM_OP_CHECKER_apply_unary_numeric_widening_conversion(compiler, op_cur->first);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_ADD: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of the + operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of the + operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              // Apply binary numeric conversion
              SPVM_OP_CHECKER_apply_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
                                              
              break;
            }
            case SPVM_OP_C_ID_SUBTRACT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of the - operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of the - operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              // Apply binary numeric conversion
              SPVM_OP_CHECKER_apply_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_MULTIPLY: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of the * operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of the * operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Apply binary numeric conversion
              SPVM_OP_CHECKER_apply_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_DIVIDE: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of the / operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of the / operator must be a numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              // Apply binary numeric conversion
              SPVM_OP_CHECKER_apply_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }

              break;
            }
            case SPVM_OP_C_ID_DIVIDE_UNSIGNED_INT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (!SPVM_TYPE_is_int_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of the \"divui\" operator must be the int type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_int_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of the \"divui\" operator must be the int type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_DIVIDE_UNSIGNED_LONG: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (!SPVM_TYPE_is_long_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of the \"divul\" operator must be a long type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_long_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of the \"divul\" operator must be a long type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_REMAINDER: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be integral type
              if (!SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of the %% operator must be an integral type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be integral type
              if (!SPVM_TYPE_is_integral_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of the %% operator must be an integral type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              // Apply binary numeric conversion
              SPVM_OP_CHECKER_apply_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
                                              
              break;
            }
            case SPVM_OP_C_ID_REMAINDER_UNSIGNED_INT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (!SPVM_TYPE_is_int_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of the \"remui\" operator must be the int type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_int_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of the \"remui\" operator must be the int type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_REMAINDER_UNSIGNED_LONG: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (!SPVM_TYPE_is_long_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of the \"remul\" operator must be a long type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be numeric type
              if (!SPVM_TYPE_is_long_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of the \"remul\" operator must be a long type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_BIT_AND: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be integral type
              if (!SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of the & operator must be an integral type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be integral type
              if (!SPVM_TYPE_is_integral_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of the & operator must be an integral type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              SPVM_OP_CHECKER_apply_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_BIT_OR: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be integral type
              if (!SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The left operand of the | operator must be an integral type at %s line %d", op_cur->file, op_cur->line);
                return;
              }

              // Right operand must be integral type
              if (!SPVM_TYPE_is_integral_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_COMPILER_error(compiler, "The right operand of the | operator must be an integral type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              SPVM_OP_CHECKER_apply_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_LEFT_SHIFT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_OP_CHECKER_apply_unary_numeric_widening_conversion(compiler, op_cur->first);
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
              }
              else {
                SPVM_COMPILER_error(compiler, "The left operand of the << operator must be an integral type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be int type
              if (SPVM_TYPE_is_integral_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_OP_CHECKER_apply_unary_numeric_widening_conversion(compiler, op_cur->last);
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
                
                if (last_type->dimension == 0 && last_type->basic_type->id >= SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                  SPVM_COMPILER_error(compiler, "The right operand of the << operator must be the int type at %s line %d", op_cur->file, op_cur->line);
                  return;
                }
              }
              else {
                SPVM_COMPILER_error(compiler, "The right operand of the << operator must be the int type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_RIGHT_ARITHMETIC_SHIFT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_OP_CHECKER_apply_unary_numeric_widening_conversion(compiler, op_cur->first);
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
              }
              else {
                SPVM_COMPILER_error(compiler, "The left operand of the >> operator must be an integral type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be int type
              if (SPVM_TYPE_is_integral_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_OP_CHECKER_apply_unary_numeric_widening_conversion(compiler, op_cur->last);
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
                
                if (last_type->dimension == 0 && last_type->basic_type->id >= SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                  SPVM_COMPILER_error(compiler, "The right operand of the >> operator must be the int type at %s line %d", op_cur->file, op_cur->line);
                  return;
                }
              }
              else {
                SPVM_COMPILER_error(compiler, "The right operand of the >> operator must be the int type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_RIGHT_LOGICAL_SHIFT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
              
              // Left operand must be numeric type
              if (SPVM_TYPE_is_integral_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_OP_CHECKER_apply_unary_numeric_widening_conversion(compiler, op_cur->first);
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
              }
              else {
                SPVM_COMPILER_error(compiler, "The left operand of the >>> operator must be an integral type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              // Right operand must be int type
              if (SPVM_TYPE_is_integral_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_OP_CHECKER_apply_unary_numeric_widening_conversion(compiler, op_cur->last);
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
                
                if (last_type->dimension == 0 && last_type->basic_type->id >= SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                  SPVM_COMPILER_error(compiler, "The right operand of the >>> operator must be the int type at %s line %d", op_cur->file, op_cur->line);
                  return;
                }
              }
              else {
                SPVM_COMPILER_error(compiler, "The right operand of the >>> operator must be the int type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_DIE: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);

              if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_OP_CHECKER_apply_numeric_to_string_conversion(compiler, op_cur->first);
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
              }
              
              first_type = SPVM_OP_get_type(compiler, op_cur->first);

              if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The operand of the die statement must be the string type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              break;
            }
            case SPVM_OP_C_ID_WARN: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_OP_CHECKER_apply_numeric_to_string_conversion(compiler, op_cur->first);
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
              }
              
              first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The operand of the warn statement must be the string type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              break;
            }
            case SPVM_OP_C_ID_PRINT: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              if (SPVM_TYPE_is_numeric_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_OP_CHECKER_apply_numeric_to_string_conversion(compiler, op_cur->first);
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
              }
              
              first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The operand of the print statement must be the string type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              break;
            }
            case SPVM_OP_C_ID_MAKE_READ_ONLY: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The operand of the make_read_only statement must be the string type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              break;
            }
            case SPVM_OP_C_ID_IS_READ_ONLY: {
              SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              first_type = SPVM_OP_get_type(compiler, op_cur->first);
              
              if (!SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                SPVM_COMPILER_error(compiler, "The operand of the is_read_only operator must be the string type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              break;
            }
            // End of scope
            case SPVM_OP_C_ID_BLOCK: {
              // Pop block var_decl variable base
              assert(check_ast_info->block_var_decl_base_stack->length > 0);
              int32_t block_var_decl_base = (intptr_t)SPVM_LIST_pop(check_ast_info->block_var_decl_base_stack);
                
              int32_t my_stack_pop_count = check_ast_info->my_stack->length - block_var_decl_base;
              
              for (int32_t i = 0; i < my_stack_pop_count; i++) {
                SPVM_LIST_pop(check_ast_info->my_stack);
              }

              // Pop loop block var_decl variable base
              if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_LOOP_STATEMENTS) {
                check_ast_info->loop_block_stack_length--;
              }
              // Pop try block var_decl variable base
              else if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_EVAL) {
                check_ast_info->eval_block_stack_length--;
              }
              
              break;
            }
            case SPVM_OP_C_ID_CREATE_REF: {
              
              SPVM_OP* op_var = op_cur->first;
              SPVM_TYPE* var_type = SPVM_OP_get_type(compiler, op_var);
              if (!(SPVM_TYPE_is_numeric_type(compiler, var_type->basic_type->id, var_type->dimension, var_type->flag) || SPVM_TYPE_is_mulnum_type(compiler, var_type->basic_type->id, var_type->dimension, var_type->flag))) {
                SPVM_COMPILER_error(compiler, "Refernece target must be numeric type or multi numeric type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_DEREF: {
              SPVM_OP* op_var = op_cur->first;
              SPVM_TYPE* var_type = SPVM_OP_get_type(compiler, op_var);
              
              if (!(SPVM_TYPE_is_numeric_ref_type(compiler, var_type->basic_type->id, var_type->dimension, var_type->flag) || SPVM_TYPE_is_mulnum_ref_type(compiler, var_type->basic_type->id, var_type->dimension, var_type->flag))) {
                SPVM_COMPILER_error(compiler, "Dereference target must be numeric reference type or value reference type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            // Add var_decl var
            case SPVM_OP_C_ID_VAR: {
              
              if (op_cur->uv.var->is_declaration) {
                
                SPVM_VAR_DECL* var_decl = op_cur->uv.var->var_decl;
                
                // Redeclaration error if same name variable is declare in same block
                int32_t found = 0;
                int32_t block_var_decl_base = (intptr_t)SPVM_LIST_get(check_ast_info->block_var_decl_base_stack, check_ast_info->block_var_decl_base_stack->length - 1);
                for (int32_t i = block_var_decl_base; i < check_ast_info->my_stack->length; i++) {
                  SPVM_VAR_DECL* bef_var_decl = SPVM_LIST_get(check_ast_info->my_stack, i);
                  
                  if (strcmp(var_decl->var->name, bef_var_decl->var->name) == 0) {
                    // Temporaly variable is not duplicated
                    if (strncmp(var_decl->var->name, "$.", 2) != 0) {
                      found = 1;
                    }
                    break;
                  }
                }
                
                if (found) {
                  SPVM_COMPILER_error(compiler, "Redeclaration of variable \"%s\" at %s line %d", var_decl->var->name, var_decl->op_var_decl->file, var_decl->op_var_decl->line);
                  return;
                }
                else {
                  var_decl->id = method->var_decls->length;
                  SPVM_LIST_push(method->var_decls, var_decl);
                  SPVM_LIST_push(check_ast_info->my_stack, var_decl);
                }
                
                // Type can't be detected
                if (!op_cur->is_lvalue && var_decl->type == NULL) {
                  SPVM_COMPILER_error(compiler, "Type can't be detected at %s line %d", var_decl->op_var_decl->file, var_decl->op_var_decl->line);
                  return;
                }
              }
              
              SPVM_VAR* var = op_cur->uv.var;
              
              // Search same name variable
              SPVM_VAR_DECL* found_var_decl = NULL;
              for (int32_t i = check_ast_info->my_stack->length - 1; i >= 0; i--) {
                SPVM_VAR_DECL* var_decl = SPVM_LIST_get(check_ast_info->my_stack, i);
                assert(var_decl);
                if (strcmp(var->name, var_decl->var->name) == 0) {
                  found_var_decl = var_decl;
                  break;
                }
              }
              
              if (found_var_decl) {
                // Add var_decl var information to var
                var->var_decl = found_var_decl;
              }
              else {
                // Variable is capture var
                SPVM_FIELD* found_capture_field = SPVM_HASH_get(class->field_symtable, var->name + 1, strlen(var->name) - 1);
                if (found_capture_field && found_capture_field->is_captured) {
                  
                  // Capture var is converted to field access
                  SPVM_VAR_DECL* arg_first_var_decl = SPVM_LIST_get(method->var_decls, 0);
                  assert(arg_first_var_decl);
                  SPVM_OP* op_name_invoker = SPVM_OP_new_op_name(compiler, arg_first_var_decl->var->name, op_cur->file, op_cur->line);
                  SPVM_OP* op_term_invoker = SPVM_OP_new_op_var(compiler, op_name_invoker);
                  op_term_invoker->uv.var->var_decl = arg_first_var_decl;
                  SPVM_OP* op_name_field = SPVM_OP_new_op_name(compiler, op_cur->uv.var->name + 1, op_cur->file, op_cur->line);
                  
                  SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, op_cur->file, op_cur->line);
                  SPVM_OP_build_field_access(compiler, op_field_access, op_term_invoker, op_name_field);
                  op_field_access->uv.field_access->field = found_capture_field;

                  op_field_access->is_lvalue = op_cur->is_lvalue;
                  op_field_access->is_assigned_to_var = op_cur->is_assigned_to_var;
                  op_field_access->is_passed_to_method = op_cur->is_passed_to_method;
                  if (op_cur->uv.var->call_method) {
                    op_cur->uv.var->call_method->op_invocant = op_field_access;
                  }
                  
                  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                  SPVM_OP_replace_op(compiler, op_stab, op_field_access);
                  
                  op_cur = op_field_access;
                  
                  SPVM_OP_CHECKER_check_tree(compiler, op_field_access, check_ast_info);
                  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                    return;
                  }
                }
                else {
                  // Variable is class var
                  SPVM_OP* op_name_class_var = SPVM_OP_new_op_name(compiler, op_cur->uv.var->name, op_cur->file, op_cur->line);
                  SPVM_OP* op_class_var_access = SPVM_OP_new_op_class_var_access(compiler, op_name_class_var);
                  
                  op_class_var_access->is_lvalue = op_cur->is_lvalue;
                  op_class_var_access->is_assigned_to_var = op_cur->is_assigned_to_var;
                  op_class_var_access->is_passed_to_method = op_cur->is_passed_to_method;
                  if (op_cur->uv.var->call_method) {
                    op_cur->uv.var->call_method->op_invocant = op_class_var_access;
                  }

                  SPVM_OP_CHECKER_resolve_class_var_access(compiler, op_class_var_access, class->op_class);
                  if (op_class_var_access->uv.class_var_access->class_var) {
                    
                    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                    SPVM_OP_replace_op(compiler, op_stab, op_class_var_access);

                    op_cur = op_class_var_access;
                    
                    SPVM_OP_CHECKER_check_tree(compiler, op_class_var_access, check_ast_info);
                    if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                      return;
                    }
                  }
                  else {
                    SPVM_COMPILER_error(compiler, "Local variable %s is not declared at %s line %d", var->name, op_cur->file, op_cur->line);
                    return;
                  }
                }
              }
              
              break;
            }
            case SPVM_OP_C_ID_CALL_METHOD: {
              
              SPVM_OP* op_call_method = op_cur;

              assert(op_cur->first->id == SPVM_OP_C_ID_LIST);
                  
              
              // Resulve sub
              SPVM_OP_CHECKER_resolve_call_method(compiler, op_cur, class->op_class);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              SPVM_OP* op_list_args = op_cur->last;
              
              SPVM_CALL_METHOD* call_method = op_call_method->uv.call_method;
              const char* method_name = call_method->method->name;
              
              if (call_method->method->is_class_method) {
                if (!call_method->is_class_method_call) {
                  SPVM_COMPILER_error(compiler, "Class methods can't be called as instance methods \"%s->%s\" at %s line %d", op_cur->uv.call_method->method->class->name, method_name, op_cur->file, op_cur->line);
                  return;
                }
              }
              else {
                if (call_method->is_class_method_call) {
                  SPVM_COMPILER_error(compiler, "Instance methods can't be called as class methods \"%s->%s\" at %s line %d", op_cur->uv.call_method->method->class->name, method_name, op_cur->file, op_cur->line);
                  return;
                }
              }

              // Access control
              int32_t is_private;
              if (call_method->method->is_private) {
                is_private = 1;
              }
              // Default
              else {
                is_private = 0;
              }
              
              if (is_private) {
                if (!SPVM_OP_is_allowed(compiler, method->class->op_class, call_method->method->class->op_class)) {
                  SPVM_COMPILER_error(compiler, "Can't call private method %s->%s at %s line %d", call_method->method->class->name, call_method->method->name, op_cur->file, op_cur->line);
                  return;
                }
              }
              
              int32_t args_count = call_method->method->args_length;
              int32_t method_is_vaarg = call_method->method->have_vaarg;

              // Variable length argument. Last argument is not array.
              int32_t vaarg_last_arg_is_not_array = 0;
              if (method_is_vaarg) {
                int32_t arg_index = 0;
                SPVM_OP* op_term = op_list_args->first;
                while ((op_term = SPVM_OP_sibling(compiler, op_term))) {
                  if (arg_index == args_count - 1) {
                    SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_term);
                    if (!SPVM_TYPE_is_array_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                      vaarg_last_arg_is_not_array = 1;
                    }
                  }
                  
                  arg_index++;
                }
                
                // Empty vaargs 
                if (arg_index == args_count - 1) {
                  vaarg_last_arg_is_not_array = 1;
                }
              }

              // Variable length arguments
              if (vaarg_last_arg_is_not_array) {
                
                SPVM_OP* op_list_args_new = SPVM_OP_new_op_list(compiler, op_call_method->file, op_call_method->line);
                
                const char* file = op_cur->file;
                int32_t line = op_cur->line;
                
                // New
                SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, op_cur->file, op_cur->line);
                
                SPVM_VAR_DECL* vaarg_last_arg_var_decl = SPVM_LIST_get(call_method->method->var_decls, call_method->method->args_length - 1);
                SPVM_TYPE* vaarg_last_arg_type = vaarg_last_arg_var_decl->type;

                // Create new type
                SPVM_OP* op_type_new = SPVM_OP_new_op_type(compiler, vaarg_last_arg_type, op_cur->file, op_cur->line);
                
                // Create element type
                SPVM_TYPE* type_element = SPVM_TYPE_new(compiler, vaarg_last_arg_type->basic_type->id, vaarg_last_arg_type->dimension - 1, vaarg_last_arg_type->flag);
                SPVM_OP* op_type_element = SPVM_OP_new_op_type(compiler, type_element, op_cur->file, op_cur->line);
                
                // Sequence
                SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, file, line);
                SPVM_OP* op_assign_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, file, line);
                SPVM_OP* op_var_tmp_new = SPVM_OP_CHECKER_new_op_var_tmp(compiler, method, op_type_new->uv.type, file, line);
                
                SPVM_OP_build_assign(compiler, op_assign_new, op_var_tmp_new, op_new);

                SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_assign_new);
                
                int32_t length;
                int32_t arg_index = 0;
                int32_t vaarg_index = 0;
                
                SPVM_OP* op_term_element = op_list_args->first;
                while ((op_term_element = SPVM_OP_sibling(compiler, op_term_element))) {

                  op_term_element->no_need_check = 1;

                  if (arg_index < args_count - 1) {
                    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term_element);
                    SPVM_OP_insert_child(compiler, op_list_args_new, op_list_args_new->last, op_term_element);
                    op_term_element = op_stab;
                  }
                  else {
                    op_var_tmp_new->uv.var->var_decl->type = op_type_new->uv.type;

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

                SPVM_OP_replace_op(compiler, op_call_method->last, op_list_args_new);

                SPVM_OP_CHECKER_check_tree(compiler, op_list_args_new, check_ast_info);
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
                
                op_list_args = op_list_args_new;
              }
              
              int32_t call_method_args_count = 0;
              {
                SPVM_OP* op_term = op_list_args->first;
                while ((op_term = SPVM_OP_sibling(compiler, op_term))) {
                  call_method_args_count++;
                  if (call_method_args_count > args_count) {
                    SPVM_COMPILER_error(compiler, "Too many arguments \"%s->%s\" at %s line %d", op_cur->uv.call_method->method->class->name, method_name, op_cur->file, op_cur->line);
                    return;
                  }
                  
                  SPVM_VAR_DECL* arg_var_decl = SPVM_LIST_get(call_method->method->var_decls, call_method_args_count - 1);
                  SPVM_TYPE* arg_var_decl_type = arg_var_decl->type;
                  
                  // Check if source can be assigned to dist
                  // If needed, numeric conversion op is added
                  char place[50];
                  sprintf(place, "%dth argument", call_method_args_count);
                  
                  op_term = SPVM_OP_CHECKER_check_assign(compiler, arg_var_decl_type, op_term, place, op_cur->file, op_cur->line);
                  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                    return;
                  }
                }
              }
              
              if (call_method_args_count < args_count) {
                SPVM_COMPILER_error(compiler, "Too few argument \"%s->%s\" at %s line %d", op_cur->uv.call_method->method->class->name, method_name, op_cur->file, op_cur->line);
                return;
              }
              
              if (call_method->method->is_destructor) {
                SPVM_COMPILER_error(compiler, "Can't call DESTROY in yourself at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              // Inline expansion
              {
                // Enum is replaced to constant value
                if (call_method->method->is_enum) {
                  // Replace sub to constant
                  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                  
                  int32_t value = call_method->method->op_inline->uv.constant->value.ival;
                  SPVM_OP* op_constant = SPVM_OP_new_op_constant_int(compiler, value, op_cur->file, op_cur->line);
                  
                  SPVM_OP_replace_op(compiler, op_stab, op_constant);
                  
                  op_cur = op_constant;
                }
                // Constant method is replaced to constant value
                else if (call_method->method->is_constant) {
                  // Replace method to constant
                  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                  
                  int32_t value = call_method->method->op_inline->uv.constant->value.ival;
                  SPVM_OP* op_constant = SPVM_OP_new_op_constant_int(compiler, value, op_cur->file, op_cur->line);
                  
                  SPVM_OP_replace_op(compiler, op_stab, op_constant);
                  
                  op_cur = op_constant;
                }
                // Simple constructor is inlined
                else if (call_method->method->is_simple_constructor) {
                  // Replace sub to constant
                  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                  
                  SPVM_OP* op_type_original = call_method->method->op_inline;
                  assert(op_type_original->id == SPVM_OP_C_ID_TYPE);
                  SPVM_TYPE* type_original = op_type_original->uv.type;
                  
                  SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, op_cur->file, op_cur->line);
                  op_new->flag |= SPVM_OP_C_FLAG_NEW_INLINE;
                  
                  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type_original, op_cur->file, op_cur->line);
                  op_new = SPVM_OP_build_new(compiler, op_new, op_type, NULL);
                  
                  SPVM_OP_CHECKER_check_tree(compiler, op_new, check_ast_info);
                  
                  SPVM_OP_replace_op(compiler, op_stab, op_new);
                  
                  op_cur = op_new;
                }
                // Field getter is replaced to field access
                else if (call_method->method->is_field_getter) {
                  // [Before]
                  // $object->foo
                  // [After]
                  // $object->{foo}
                  
                  SPVM_OP* op_list_args = op_cur->first;
                  SPVM_OP* op_invocant = SPVM_OP_sibling(compiler, op_list_args->first);
                  assert(op_invocant);
                  SPVM_OP_cut_op(compiler, op_invocant);
                  
                  const char* field_name = call_method->method->accessor_original_name;

                  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                
                  SPVM_OP* op_name_field_access = SPVM_OP_new_op_name(compiler, field_name, op_cur->file, op_cur->line);
                  SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, op_cur->file, op_cur->line);
                  SPVM_OP_build_field_access(compiler, op_field_access, op_invocant, op_name_field_access);
                  op_field_access->uv.field_access->inline_expansion = 1;

                  SPVM_OP_replace_op(compiler, op_stab, op_field_access);
                  
                  SPVM_OP_CHECKER_check_tree(compiler, op_field_access, check_ast_info);
                  op_cur = op_field_access;
                }
                // Field setter is replaced to field access
                else if (call_method->method->is_field_setter) {
                  
                  // [Before]
                  // $object->set_foo($value)
                  // [After]
                  // $object->{foo} = $value

                  SPVM_OP* op_list_args = op_cur->first;
                  SPVM_OP* op_invocant = SPVM_OP_sibling(compiler, op_list_args->first);
                  assert(op_invocant);
                  SPVM_OP_cut_op(compiler, op_invocant);

                  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                  
                  SPVM_OP* op_args = op_cur->last;
                  SPVM_OP* op_term_value = op_args->last;
                  
                  SPVM_OP_cut_op(compiler, op_term_value);

                  op_term_value->no_need_check = 1;

                  const char* field_name = call_method->method->accessor_original_name;
                  SPVM_OP* op_name_field_access = SPVM_OP_new_op_name(compiler, field_name, op_cur->file, op_cur->line);
                  SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, op_cur->file, op_cur->line);
                  SPVM_OP_build_field_access(compiler, op_field_access, op_invocant, op_name_field_access);
                  op_field_access->uv.field_access->inline_expansion = 1;
                  
                  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                  SPVM_OP_build_assign(compiler, op_assign, op_field_access, op_term_value);
                  
                  SPVM_OP_replace_op(compiler, op_stab, op_assign);
                  
                  SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
                  
                  op_cur = op_assign;
                }
                // Class var getter is replaced to class var access
                else if (call_method->method->is_class_var_getter) {
                  // [Before]
                  // Class->FOO
                  // [After]
                  // $Class::FOO
                  
                  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                  
                  const char* class_name = call_method->method->class->name;
                  const char* class_var_base_name = call_method->method->accessor_original_name;
                  char* class_var_name_tmp = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, 1 + strlen(class_name) + 2 + strlen(class_var_base_name));
                  memcpy(class_var_name_tmp, "$", 1);
                  memcpy(class_var_name_tmp + 1, class_name, strlen(class_name));
                  memcpy(class_var_name_tmp + 1 + strlen(class_name), "::", 2);
                  memcpy(class_var_name_tmp + 1 + strlen(class_name) + 2, class_var_base_name + 1, strlen(class_var_base_name) - 1);
                  
                  SPVM_CONSTANT_STRING* class_var_name_string = SPVM_CONSTANT_STRING_new(compiler, class_var_name_tmp, strlen(class_var_name_tmp));
                  const char* class_var_name = class_var_name_string->value;
                  
                  SPVM_OP* op_class_var_name = SPVM_OP_new_op_name(compiler, class_var_name, op_cur->file, op_cur->line);
                  SPVM_OP* op_class_var_access = SPVM_OP_new_op_class_var_access(compiler, op_class_var_name);
                  op_class_var_access->uv.class_var_access->inline_expansion = 1;
                  
                  SPVM_OP_replace_op(compiler, op_stab, op_class_var_access);
                  
                  SPVM_OP_CHECKER_check_tree(compiler, op_class_var_access, check_ast_info);

                  op_cur = op_class_var_access;

                }
                // Class var setter is replaced to class var access
                else if (call_method->method->is_class_var_setter) {
                  // [Before]
                  // Class->SET_FOO($value)
                  // [After]
                  // $Class::FOO = $value
                  
                  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                  
                  SPVM_OP* op_args = op_cur->last;
                  SPVM_OP* op_term_value = op_args->last;
                  
                  SPVM_OP_cut_op(compiler, op_term_value);

                  op_term_value->no_need_check = 1;
                  
                  const char* class_name = call_method->method->class->name;
                  const char* class_var_base_name = call_method->method->accessor_original_name;
                  char* class_var_name_tmp = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, 1 + strlen(class_name) + 2 + strlen(class_var_base_name));
                  memcpy(class_var_name_tmp, "$", 1);
                  memcpy(class_var_name_tmp + 1, class_name, strlen(class_name));
                  memcpy(class_var_name_tmp + 1 + strlen(class_name), "::", 2);
                  memcpy(class_var_name_tmp + 1 + strlen(class_name) + 2, class_var_base_name + 1, strlen(class_var_base_name) - 1);
                  SPVM_CONSTANT_STRING* class_var_name_string = SPVM_CONSTANT_STRING_new(compiler, class_var_name_tmp, strlen(class_var_name_tmp));
                  const char* class_var_name = class_var_name_string->value;
                  
                  SPVM_OP* op_class_var_name = SPVM_OP_new_op_name(compiler, class_var_name, op_cur->file, op_cur->line);
                  SPVM_OP* op_class_var_access = SPVM_OP_new_op_class_var_access(compiler, op_class_var_name);
                  op_class_var_access->uv.class_var_access->inline_expansion = 1;
                  
                  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                  SPVM_OP_build_assign(compiler, op_assign, op_class_var_access, op_term_value);
                  
                  SPVM_OP_replace_op(compiler, op_stab, op_assign);
                  
                  SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
                  
                  op_cur = op_assign;
                }
              }
              
              break;
            }
            case SPVM_OP_C_ID_CLASS_VAR_ACCESS: {
              
              // Check field name
              SPVM_OP_CHECKER_resolve_class_var_access(compiler, op_cur, class->op_class);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              if (!op_cur->uv.class_var_access->class_var) {
                SPVM_COMPILER_error(compiler, "Class variable not found \"%s\" at %s line %d", op_cur->uv.class_var_access->op_name->uv.name, op_cur->file, op_cur->line);
                return;
              }
              
              SPVM_CLASS_VAR_ACCESS* class_var_access = op_cur->uv.class_var_access;
              SPVM_CLASS_VAR* class_var = class_var_access->class_var;
              SPVM_CLASS* class_var_access_class = class_var->class;
              
              int32_t is_private;
              // Public flag
              if (class_var->is_public) {
                is_private = 0;
              }
              // Default is private
              else {
                is_private = 1;
              }

              if (is_private && !op_cur->uv.class_var_access->inline_expansion) {
                if (!SPVM_OP_is_allowed(compiler, method->class->op_class, class_var_access_class->op_class)) {
                  SPVM_COMPILER_error(compiler, "Can't access to private class variable \"%s\" at %s line %d", op_cur->uv.class_var_access->op_name->uv.name, op_cur->file, op_cur->line);
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
                SPVM_COMPILER_error(compiler, "Array access invocant must be array or string at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              // String access
              if (SPVM_TYPE_is_string_type(compiler, first_type->basic_type->id, first_type->dimension, first_type->flag)) {
                op_cur->flag |= SPVM_OP_C_FLAG_ARRAY_ACCESS_STRING;
              }
              
              // Right operand must be integer
              if (SPVM_TYPE_is_numeric_type(compiler, last_type->basic_type->id, last_type->dimension, last_type->flag)) {
                SPVM_OP_CHECKER_apply_unary_numeric_widening_conversion(compiler, op_cur->last);
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
                
                SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                
                if (last_type->dimension == 0 && last_type->basic_type->id != SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                  SPVM_COMPILER_error(compiler, "array index must be int type at %s line %d", op_cur->file, op_cur->line);
                  return;
                }
              }
              else {
                SPVM_COMPILER_error(compiler, "array index must be numeric type at %s line %d", op_cur->file, op_cur->line);
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
                
                SPVM_OP* op_var_tmp = SPVM_OP_CHECKER_new_op_var_tmp(compiler, method, term_index_type, op_cur->file, op_cur->line);

                SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);

                SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_term_array);
                
                // Convert cur new op to var
                SPVM_OP_replace_op(compiler, op_stab, op_assign);
                
                SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
              }
              
              // If array access index term is not var, create assign operator
              SPVM_OP* op_term_index = op_cur->last;
              if (op_term_index->id != SPVM_OP_C_ID_VAR) {
                
                op_cur->no_need_check = 1;

                SPVM_TYPE* term_index_type = SPVM_OP_get_type(compiler, op_term_index);

                SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term_index);
                
                SPVM_OP* op_var_tmp = SPVM_OP_CHECKER_new_op_var_tmp(compiler, method, term_index_type, op_cur->file, op_cur->line);
                
                SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);

                SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_term_index);
                
                // Convert cur new op to var
                SPVM_OP_replace_op(compiler, op_stab, op_assign);

                SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
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
                else if (SPVM_TYPE_is_mulnum_type(compiler, invoker_type->basic_type->id, invoker_type->dimension, invoker_type->flag)) {
                  is_valid_invoker_type = 1;
                }
                else if (SPVM_TYPE_is_mulnum_ref_type(compiler, invoker_type->basic_type->id, invoker_type->dimension, invoker_type->flag)) {
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
                SPVM_COMPILER_error(compiler, "The type of the invocant of the field access must be a class type, or a multi numeric type, or a multi numeric reference type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              // Check field name
              SPVM_OP_CHECKER_resolve_field_access(compiler, op_cur);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              SPVM_FIELD* field = op_cur->uv.field_access->field;
              
              if (!field) {
                const char* invoker_type_name = SPVM_TYPE_new_type_name(compiler, invoker_type->basic_type->id, invoker_type->dimension, invoker_type->flag);
                SPVM_COMPILER_error(compiler, "Unknown field %s->{%s} at %s line %d", invoker_type_name, op_name->uv.name, op_cur->file, op_cur->line);
                return;
              }
              
              // weaken operator
              if (op_cur->flag & SPVM_OP_C_FLAG_FIELD_ACCESS_WEAKEN) {
                if (!SPVM_TYPE_is_object_type(compiler, field->type->basic_type->id, field->type->dimension, field->type->flag)) {
                  SPVM_COMPILER_error(compiler, "The type of the field targeted by the weaken operator must be a object type \"%s\" \"%s\" at %s line %d", field->class->op_name->uv.name, field->op_name->uv.name, op_cur->file, op_cur->line);
                  return;
                }
              }
              // unweaken operator
              else if (op_cur->flag & SPVM_OP_C_FLAG_FIELD_ACCESS_UNWEAKEN) {
                if (!SPVM_TYPE_is_object_type(compiler, field->type->basic_type->id, field->type->dimension, field->type->flag)) {
                  SPVM_COMPILER_error(compiler, "The type of the field targeted by the unweaken operator must be a object type \"%s\" \"%s\" at %s line %d", field->class->op_name->uv.name, field->op_name->uv.name, op_cur->file, op_cur->line);
                  return;
                }
              }
              // isweak operator
              else if (op_cur->flag & SPVM_OP_C_FLAG_FIELD_ACCESS_ISWEAK) {
                if (!SPVM_TYPE_is_object_type(compiler, field->type->basic_type->id, field->type->dimension, field->type->flag)) {
                  SPVM_COMPILER_error(compiler, "The type of the field targeted by the isweak operator must be a object type \"%s\" \"%s\" at %s line %d", field->class->op_name->uv.name, field->op_name->uv.name, op_cur->file, op_cur->line);
                  return;
                }
              }

              // Access control
              int32_t is_private;
              if (field->is_public) {
                is_private = 0;
              }
              // Default
              else {
                // If anon method, field is public
                if (field->class->is_anon) {
                  is_private = 0;
                }
                // If multi numeric type, field is public
                else if (field->class->category == SPVM_CLASS_C_CATEGORY_MULNUM) {
                  is_private = 0;
                }
                // Default is private
                else {
                  is_private = 1;
                }
              }
              
              if (is_private && !op_cur->uv.field_access->inline_expansion) {
                if (!SPVM_OP_is_allowed(compiler, method->class->op_class, field->class->op_class)) {
                  SPVM_COMPILER_error(compiler, "Can't access to private field \"%s\" at %s line %d", op_name->uv.name, op_cur->file, op_cur->line);
                  return;
                }
              }
              
              // If invocker is array access and array access object is mulnum_t, this op become array field access
              if (op_term_invocker->id == SPVM_OP_C_ID_ARRAY_ACCESS) {
                SPVM_OP* op_array_access = op_term_invocker;
                
                SPVM_TYPE* array_element_type = SPVM_OP_get_type(compiler, op_array_access);
                
                int32_t is_basic_type_mulnum_t = SPVM_BASIC_TYPE_is_mulnum_type(compiler, array_element_type->basic_type->id);
                if (is_basic_type_mulnum_t) {
                  if (array_element_type->dimension != 0) {
                    SPVM_COMPILER_error(compiler, "mulnum_t array field access must be 1-dimension array at %s line %d", op_cur->file, op_cur->line);
                    return;
                  }
                  else {
                    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                    
                    SPVM_OP* op_array_field_access = SPVM_OP_new_op_array_field_access(compiler, op_cur->file, op_cur->line);
                    op_array_field_access->is_lvalue = op_cur->is_lvalue;

                    op_cur = op_array_field_access;
                    
                    SPVM_ARRAY_FIELD_ACCESS* array_field_access = op_array_field_access->uv.array_field_access;
                    array_field_access->field = field;
                    
                    SPVM_OP* op_array = op_array_access->first;
                    SPVM_OP* op_index = op_array_access->last;
                    SPVM_OP_cut_op(compiler, op_array_access->first);
                    SPVM_OP_cut_op(compiler, op_array_access->last);
                    
                    SPVM_OP_insert_child(compiler, op_array_field_access, op_array_field_access->last, op_array);
                    SPVM_OP_insert_child(compiler, op_array_field_access, op_array_field_access->last, op_index);
                    
                    SPVM_OP_replace_op(compiler, op_stab, op_array_field_access);
                    
                    SPVM_OP_CHECKER_check_tree(compiler, op_array_field_access, check_ast_info);
                    if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
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
                  
                  SPVM_OP* op_var_tmp = SPVM_OP_CHECKER_new_op_var_tmp(compiler, method, term_index_type, op_cur->file, op_cur->line);

                  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);

                  SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_term_array);
                  
                  // Convert cur new op to var
                  SPVM_OP_replace_op(compiler, op_stab, op_assign);
                  
                  SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
                  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                    return;
                  }
                }
                
                // If array access index term is not var, create assign operator
                SPVM_OP* op_term_index = op_cur->last;
                if (op_term_index->id != SPVM_OP_C_ID_VAR) {
                  op_cur->no_need_check = 1;

                  SPVM_TYPE* term_index_type = SPVM_OP_get_type(compiler, op_term_index);

                  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term_index);
                  
                  SPVM_OP* op_var_tmp = SPVM_OP_CHECKER_new_op_var_tmp(compiler, method, term_index_type, op_cur->file, op_cur->line);
                  
                  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);

                  SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_term_index);
                  
                  // Convert cur new op to var
                  SPVM_OP_replace_op(compiler, op_stab, op_assign);
                  
                  SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
                  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
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
                  
                  SPVM_OP* op_var_tmp = SPVM_OP_CHECKER_new_op_var_tmp(compiler, method, term_index_type, op_cur->file, op_cur->line);
                  
                  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                  SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_term_invocker);
                  
                  // Convert cur new op to var
                  SPVM_OP_replace_op(compiler, op_stab, op_assign);

                  SPVM_OP_CHECKER_check_tree(compiler, op_assign, check_ast_info);
                  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                    return;
                  }
                }
              }
              
              break;
            }
            case SPVM_OP_C_ID_HAS_IMPLEMENT: {
              SPVM_OP* op_var = op_cur->first;
              SPVM_OP* op_name = op_cur->last;
              
              SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_var);
              
              if (!(SPVM_TYPE_is_class_type(compiler, type->basic_type->id, type->dimension, type->flag) || SPVM_TYPE_is_interface_type(compiler, type->basic_type->id, type->dimension, type->flag))) {
                SPVM_COMPILER_error(compiler, "The invocant of the has_implement operator must be a class type or an interface type at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              break;
            }
            case SPVM_OP_C_ID_TYPE_CAST: {
              
              SPVM_OP* op_src = op_cur->first;
              SPVM_OP* op_cast = op_cur->last;
              
              SPVM_TYPE* src_type = SPVM_OP_get_type(compiler, op_src);
              assert(src_type);
              
              SPVM_TYPE* cast_type = SPVM_OP_get_type(compiler, op_cast);
              assert(cast_type);
              
              // To numeric
              int32_t is_valid = 0;
              if (SPVM_TYPE_is_numeric_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                // Soruce type is numeric type
                if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                  is_valid = 1;
                }
                else if (SPVM_TYPE_is_numeric_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                  if (cast_type->basic_type->id + SPVM_BASIC_TYPE_C_NUMERIC_OBJECT_UPGRADE_SHIFT == src_type->basic_type->id) {
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
              // To multi numeric
              else if (SPVM_TYPE_is_mulnum_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                if (cast_type->basic_type->id == src_type->basic_type->id && cast_type->dimension == src_type->dimension && cast_type->flag == src_type->flag) {
                  is_valid = 1;
                }
                else {
                  is_valid = 0;
                }
              }
              // To referece
              else if (SPVM_TYPE_is_ref_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                if (cast_type->basic_type->id == src_type->basic_type->id && cast_type->dimension == src_type->dimension && cast_type->flag == src_type->flag) {
                  is_valid = 1;
                }
                else {
                  is_valid = 0;
                }
              }
              // Dist type is object type
              else if (SPVM_TYPE_is_object_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                // Source type is undef
                if (SPVM_TYPE_is_undef_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                  is_valid = 1;
                }
                else {
                  // Dist type is any object array type
                  if (SPVM_TYPE_is_any_object_array_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                    if (SPVM_TYPE_is_basic_object_array_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                      is_valid = 1;
                    }
                    else if (SPVM_TYPE_is_any_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                      is_valid = 1;
                    }
                    else {
                      is_valid = 0;
                    }
                  }
                  // Dist type is string type
                  else if (SPVM_TYPE_is_string_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
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
                  else if (SPVM_TYPE_is_byte_array_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
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
                  // Dist type is numeric array type except for byte array
                  else if (SPVM_TYPE_is_numeric_array_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                    if (cast_type->basic_type->id == src_type->basic_type->id) {
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
                  else if (SPVM_TYPE_is_any_object_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
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
                  else if (SPVM_TYPE_is_numeric_object_type(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag)) {
                    if (SPVM_TYPE_is_numeric_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
                      if (cast_type->basic_type->id == src_type->basic_type->id + SPVM_BASIC_TYPE_C_NUMERIC_OBJECT_UPGRADE_SHIFT) {
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
                  // Dist type is ohter object types
                  else {
                    // Source type is object type
                    if (SPVM_TYPE_is_object_type(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
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
              }
              else {
                assert(0);
              }

              if (!is_valid) {
                const char* src_type_name = SPVM_TYPE_new_type_name(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag);
                const char* cast_type_name = SPVM_TYPE_new_type_name(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag);
                SPVM_COMPILER_error(compiler, "Can't perform the type cast from %s to %s at %s line %d", src_type_name, cast_type_name, op_src->file, op_src->line);
                return;
              }
              
              // Remove type cast op if not needed
              if (cast_type->basic_type->id == src_type->basic_type->id && cast_type->dimension == src_type->dimension && cast_type->flag == src_type->flag) {
                SPVM_OP_cut_op(compiler, op_src);
                SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                SPVM_OP_replace_op(compiler, op_stab, op_src);
                op_cur = op_src;
              }
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

void SPVM_OP_CHECKER_apply_numeric_to_string_conversion(SPVM_COMPILER* compiler, SPVM_OP* op_term) {
  
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
  
  SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, op_term->file, op_term->line);
  SPVM_OP* op_dist_type = SPVM_OP_new_op_type(compiler, dist_type, op_term->file, op_term->line);
  SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_term, NULL);
  
  SPVM_OP_replace_op(compiler, op_stab, op_convert);
}

void SPVM_OP_CHECKER_apply_unary_numeric_widening_conversion(SPVM_COMPILER* compiler, SPVM_OP* op_term) {
  
  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_term);
  
  SPVM_TYPE* dist_type;
  if (type->dimension == 0 && type->basic_type->id <= SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
    SPVM_OP* op_dist_type = SPVM_OP_new_op_int_type(compiler, op_term->file, op_term->line);
    dist_type = op_dist_type->uv.type;
  }
  else {
    return;
  }
  
  if (!(type->basic_type->id == dist_type->basic_type->id && type->dimension == dist_type->dimension)) {
    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term);
    
    SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, op_term->file, op_term->line);
    SPVM_OP* op_dist_type = SPVM_OP_new_op_type(compiler, dist_type, op_term->file, op_term->line);
    SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_term, NULL);
    
    SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_convert);
    
    SPVM_OP_replace_op(compiler, op_stab, op_convert);
  }
}

void SPVM_OP_CHECKER_apply_binary_numeric_conversion(SPVM_COMPILER* compiler, SPVM_OP* op_first, SPVM_OP* op_last) {
  
  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_first);
  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_last);
  
  SPVM_TYPE* dist_type;
  if ((first_type->dimension == 0 && first_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) || (last_type->dimension == 0 && last_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE)) {
    SPVM_OP* op_dist_type = SPVM_OP_new_op_double_type(compiler, op_first->file, op_first->line);
    dist_type = op_dist_type->uv.type;
  }
  else if ((first_type->dimension == 0 && first_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) || (last_type->dimension == 0 && last_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT)) {
    SPVM_OP* op_dist_type = SPVM_OP_new_op_float_type(compiler, op_first->file, op_first->line);
    dist_type = op_dist_type->uv.type;
  }
  else if ((first_type->dimension == 0 && first_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) || (last_type->dimension == 0 && last_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG)) {
    SPVM_OP* op_dist_type = SPVM_OP_new_op_long_type(compiler, op_first->file, op_first->line);
    dist_type = op_dist_type->uv.type;
  }
  else {
    SPVM_OP* op_dist_type = SPVM_OP_new_op_int_type(compiler, op_first->file, op_first->line);
    dist_type = op_dist_type->uv.type;
  }
  
  if (!(first_type->basic_type->id == dist_type->basic_type->id && first_type->dimension == dist_type->dimension)) {
    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_first);
    
    SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, op_first->file, op_first->line);
    SPVM_OP* op_dist_type = SPVM_OP_new_op_type(compiler, dist_type, op_first->file, op_first->line);
    SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_first, NULL);
    
    SPVM_OP_replace_op(compiler, op_stab, op_convert);
  }
  
  if (!(last_type->basic_type->id == dist_type->basic_type->id && last_type->dimension == dist_type->dimension)) {
    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_last);
    
    SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, op_last->file, op_last->line);
    SPVM_OP* op_dist_type = SPVM_OP_new_op_type(compiler, dist_type, op_last->file, op_last->line);
    SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_last, NULL);
    SPVM_OP_replace_op(compiler, op_stab, op_convert);
  }
}

void SPVM_OP_CHECKER_check(SPVM_COMPILER* compiler) {
  
  // Resolve type ops
  SPVM_OP_CHECKER_resolve_op_types(compiler);
  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
    return;
  }
  
  // Resolve basic types
  SPVM_OP_CHECKER_resolve_basic_types(compiler);
  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
    return;
  }
  
  // Resolve classes
  SPVM_OP_CHECKER_resolve_classes(compiler);
  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
    return;
  }
  
  // Resolve types
  SPVM_OP_CHECKER_resolve_types(compiler);

  // Check trees
  {
    int32_t class_index;
    for (class_index = compiler->cur_class_base; class_index < compiler->classes->length; class_index++) {
      SPVM_CLASS* class = SPVM_LIST_get(compiler->classes, class_index);
      SPVM_LIST* methods = class->methods;
      {
        int32_t method_index;
        for (method_index = 0; method_index < methods->length; method_index++) {
          
          SPVM_METHOD* method = SPVM_LIST_get(methods, method_index);
          SPVM_CLASS* class = method->class;
          SPVM_TYPE* class_type = class->type;
          
          // Destructor must receive own class object
          if (method->is_destructor) {
            // DESTROY argument must be 0
            int32_t error = 0;
            if (method->args_length != 1) {
              error = 1;
            }
            else {
              SPVM_VAR_DECL* arg_var_decl = SPVM_LIST_get(method->var_decls, 0);
              SPVM_TYPE* arg_type = arg_var_decl->type;
              
              if (!(arg_type->basic_type->id == class_type->basic_type->id && arg_type->dimension == class_type->dimension)) {
                error = 1;
              }
            }
            
            if (error) {
              SPVM_COMPILER_error(compiler, "DESTROY argument must be self at %s line %d", method->op_method->file, method->op_method->line);
              return;
            }
          }
          
          // Check method
          if (!(method->is_native)) {
            SPVM_CHECK_AST_INFO check_ast_info_struct = {0};
            SPVM_CHECK_AST_INFO* check_ast_info = &check_ast_info_struct;
            
            // Class
            check_ast_info->class = class;
            
            // Method
            check_ast_info->method = method;

            // Eval block stack length
            check_ast_info->eval_block_stack_length = 0;
            
            // Loop block stack length
            check_ast_info->loop_block_stack_length = 0;
            
            // My stack
            check_ast_info->my_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
            
            // Block var_decl base stack
            check_ast_info->block_var_decl_base_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
            
            // Switch stack
            check_ast_info->op_switch_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
            
            // First tree traversal
            SPVM_OP_CHECKER_check_tree(compiler, method->op_block, check_ast_info);

            // Free list
            SPVM_LIST_free(check_ast_info->my_stack);
            SPVM_LIST_free(check_ast_info->block_var_decl_base_stack);
            SPVM_LIST_free(check_ast_info->op_switch_stack);
            
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }
            
            // Second tree traversal
            // set assign_to_var flag - 
            // Add string to constant pool
            // Check ref 
            {
              // Run OPs
              SPVM_OP* op_root = method->op_block;
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
              SPVM_OP* op_root = method->op_block;
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
                        case SPVM_OP_C_ID_TYPE_CAST:
                        case SPVM_OP_C_ID_SWITCH:
                        case SPVM_OP_C_ID_DEFAULT:
                        case SPVM_OP_C_ID_CASE:
                        case SPVM_OP_C_ID_DIE:
                        case SPVM_OP_C_ID_WARN:
                        case SPVM_OP_C_ID_PRINT:
                        case SPVM_OP_C_ID_MAKE_READ_ONLY:
                        case SPVM_OP_C_ID_IS_READ_ONLY:
                        case SPVM_OP_C_ID_LAST:
                        case SPVM_OP_C_ID_NEXT:
                        case SPVM_OP_C_ID_BREAK:
                        case SPVM_OP_C_ID_ADD:
                        case SPVM_OP_C_ID_SUBTRACT:
                        case SPVM_OP_C_ID_MULTIPLY:
                        case SPVM_OP_C_ID_DIVIDE:
                        case SPVM_OP_C_ID_DIVIDE_UNSIGNED_INT:
                        case SPVM_OP_C_ID_DIVIDE_UNSIGNED_LONG:
                        case SPVM_OP_C_ID_REMAINDER:
                        case SPVM_OP_C_ID_REMAINDER_UNSIGNED_INT:
                        case SPVM_OP_C_ID_REMAINDER_UNSIGNED_LONG:
                        case SPVM_OP_C_ID_BIT_AND:
                        case SPVM_OP_C_ID_BIT_OR:
                        case SPVM_OP_C_ID_BIT_XOR:
                        case SPVM_OP_C_ID_BIT_NOT:
                        case SPVM_OP_C_ID_LEFT_SHIFT:
                        case SPVM_OP_C_ID_RIGHT_ARITHMETIC_SHIFT:
                        case SPVM_OP_C_ID_RIGHT_LOGICAL_SHIFT:
                        case SPVM_OP_C_ID_MINUS:
                        case SPVM_OP_C_ID_PLUS:
                        case SPVM_OP_C_ID_COPY:
                        case SPVM_OP_C_ID_ARRAY_LENGTH:
                        case SPVM_OP_C_ID_STRING_LENGTH:
                        case SPVM_OP_C_ID_NEW:
                        case SPVM_OP_C_ID_CONCAT:
                        case SPVM_OP_C_ID_REFOP:
                        case SPVM_OP_C_ID_DUMP:
                        case SPVM_OP_C_ID_NEW_STRING_LEN:
                        case SPVM_OP_C_ID_EXCEPTION_VAR:
                        case SPVM_OP_C_ID_CLASS_VAR_ACCESS:
                        case SPVM_OP_C_ID_SWITCH_CONDITION:
                        case SPVM_OP_C_ID_ARRAY_FIELD_ACCESS:
                        case SPVM_OP_C_ID_CREATE_REF:
                        case SPVM_OP_C_ID_DEREF:
                        case SPVM_OP_C_ID_REFCNT:
                        case SPVM_OP_C_ID_FIELD_ACCESS:
                        case SPVM_OP_C_ID_ARRAY_ACCESS:
                        case SPVM_OP_C_ID_CALL_METHOD:
                        case SPVM_OP_C_ID_TRUE:
                        case SPVM_OP_C_ID_FALSE:
                        {
                          create_tmp_var = 1;
                          break;
                        }
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
                      SPVM_OP* op_var_tmp = SPVM_OP_CHECKER_new_op_var_tmp(compiler, method, tmp_var_type, op_cur->file, op_cur->line);
                      
                      op_var_tmp->uv.var->var_decl->id = method->var_decls->length;
                      SPVM_LIST_push(method->op_method->uv.method->var_decls, op_var_tmp->uv.var->var_decl);
                      
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
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }
            assert(method->class->module_file);
            
            // Add op var_decl if need
            if (method->class->category == SPVM_CLASS_C_CATEGORY_CALLBACK || method->class->category == SPVM_CLASS_C_CATEGORY_INTERFACE) {
              int32_t arg_index;
              for (arg_index = 0; arg_index < method->args_length; arg_index++) {
                SPVM_VAR_DECL* arg_var_decl = SPVM_LIST_get(method->var_decls, arg_index);
                SPVM_LIST_push(method->var_decls, arg_var_decl);
              }
            }

            // Fourth tree traversal
            // Fix LEAVE_SCOPE
            {
              // Block stack
              SPVM_LIST* op_block_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
              
              // Run OPs
              SPVM_OP* op_root = method->op_block;
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
                        SPVM_OP* op_block_current = SPVM_LIST_get(op_block_stack, op_block_stack->length - 1);

                        SPVM_LIST_pop(op_block_stack);
                        
                        // Parent block need LEAVE_SCOPE if child is needing LEAVE_SCOPE
                        if (op_block_stack->length > 0) {
                          SPVM_OP* op_block_parent = SPVM_LIST_get(op_block_stack, op_block_stack->length - 1);
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
                          int32_t type_is_mulnum_t = SPVM_TYPE_is_mulnum_type(compiler, type->basic_type->id, type->dimension, type->flag);
                          
                          if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag) && !type_is_mulnum_t) {
                            SPVM_OP* op_block_current = SPVM_LIST_get(op_block_stack, op_block_stack->length - 1);
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

          // Fifth tree traversal
          // Resolve var_decl mem ids
          if (!(method->is_native)) {
            {
              SPVM_LIST* tmp_var_decl_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
              SPVM_LIST* no_tmp_var_decl_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
              SPVM_LIST* block_no_tmp_var_decl_base_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
              
              SPVM_LIST* call_stack_byte_vars = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
              SPVM_LIST* call_stack_short_vars = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
              SPVM_LIST* call_stack_int_vars = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
              SPVM_LIST* call_stack_long_vars = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
              SPVM_LIST* call_stack_float_vars = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
              SPVM_LIST* call_stack_double_vars = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
              SPVM_LIST* call_stack_object_vars = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
              SPVM_LIST* call_stack_ref_vars = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);

              // Run OPs
              SPVM_OP* op_root = method->op_block;
              SPVM_OP* op_cur = op_root;
              int32_t finish = 0;
              while (op_cur) {
                // [START]Preorder traversal position
                switch (op_cur->id) {
                  // Start scope
                  case SPVM_OP_C_ID_BLOCK: {
                    int32_t block_no_tmp_var_decl_base = no_tmp_var_decl_stack->length;
                    SPVM_LIST_push(block_no_tmp_var_decl_base_stack, (void*)(intptr_t)block_no_tmp_var_decl_base);
                    
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
                        int32_t length = tmp_var_decl_stack->length;
                        for (int32_t i = 0; i < length; i++) {
                          SPVM_VAR_DECL* var_decl = SPVM_LIST_pop(tmp_var_decl_stack);

                          SPVM_TYPE* type = SPVM_OP_get_type(compiler, var_decl->op_var_decl);
                          
                          // Free tmp mem id
                          if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_object_vars, var_decl);
                          }
                          else if (SPVM_TYPE_is_ref_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_ref_vars, var_decl);
                          }
                          else if (SPVM_TYPE_is_mulnum_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_CLASS* value_class =  type->basic_type->class;
                            
                            SPVM_FIELD* first_field = SPVM_LIST_get(value_class->fields, 0);
                            assert(first_field);
                            
                            SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, first_field->op_field);
                            
                            switch (field_type->basic_type->id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_byte_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_short_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_int_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_long_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_float_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_double_vars, var_decl);
                                break;
                              }
                              default:
                                assert(0);
                            }
                          }
                          else if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_TYPE* numeric_type = SPVM_OP_get_type(compiler, var_decl->op_var_decl);
                            switch(numeric_type->basic_type->id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_byte_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_short_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_int_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_long_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_float_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_double_vars, var_decl);
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
                        // Pop block no tmp var_decl variable base
                        int32_t block_no_tmp_var_decl_base = (intptr_t)SPVM_LIST_pop(block_no_tmp_var_decl_base_stack);
                        int32_t no_tmp_var_decl_stack_pop_count = no_tmp_var_decl_stack->length - block_no_tmp_var_decl_base;
                        
                        for (int32_t i = 0; i < no_tmp_var_decl_stack_pop_count; i++) {
                          SPVM_VAR_DECL* var_decl = SPVM_LIST_pop(no_tmp_var_decl_stack);

                          SPVM_TYPE* type = SPVM_OP_get_type(compiler, var_decl->op_var_decl);
                          
                          // Free tmp mem id
                          if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_object_vars, var_decl);
                          }
                          else if (SPVM_TYPE_is_ref_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_ref_vars, var_decl);
                          }
                          else if (SPVM_TYPE_is_mulnum_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_CLASS* value_class =  type->basic_type->class;
                            
                            SPVM_FIELD* first_field = SPVM_LIST_get(value_class->fields, 0);
                            assert(first_field);
                            
                            SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, first_field->op_field);
                            
                            switch (field_type->basic_type->id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_byte_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_short_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_int_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_long_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_float_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_double_vars, var_decl);
                                break;
                              }
                              default:
                                assert(0);
                            }
                          }
                          else if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_TYPE* numeric_type = SPVM_OP_get_type(compiler, var_decl->op_var_decl);
                            switch(numeric_type->basic_type->id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_byte_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_short_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_int_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_long_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_float_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                SPVM_OP_CHECKER_free_mem_id(compiler, call_stack_double_vars, var_decl);
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
                          SPVM_VAR_DECL* var_decl = op_cur->uv.var->var_decl;
                          
                          SPVM_TYPE* type = SPVM_OP_get_type(compiler, var_decl->op_var_decl);
                          
                          // Resolve mem id
                          int32_t mem_id;
                          if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, call_stack_object_vars, var_decl);
                          }
                          else if (SPVM_TYPE_is_ref_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, call_stack_ref_vars, var_decl);
                          }
                          else if (SPVM_TYPE_is_mulnum_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_CLASS* value_class =  type->basic_type->class;
                            
                            SPVM_FIELD* first_field = SPVM_LIST_get(value_class->fields, 0);
                            assert(first_field);
                            
                            SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, first_field->op_field);
                            
                            switch (field_type->basic_type->id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, call_stack_byte_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, call_stack_short_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, call_stack_int_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, call_stack_long_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, call_stack_float_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, call_stack_double_vars, var_decl);
                                break;
                              }
                              default:
                                assert(0);
                            }
                          }
                          else if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                            SPVM_TYPE* numeric_type = SPVM_OP_get_type(compiler, var_decl->op_var_decl);
                            switch(numeric_type->basic_type->id) {
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, call_stack_byte_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, call_stack_short_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, call_stack_int_vars, var_decl);
                                if (strcmp(var_decl->var->name, "$.condition_flag") == 0) {
                                  assert(mem_id == 0);
                                }
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, call_stack_long_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, call_stack_float_vars, var_decl);
                                break;
                              }
                              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                                mem_id = SPVM_OP_CHECKER_get_mem_id(compiler, call_stack_double_vars, var_decl);
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
                          var_decl->mem_id = mem_id;
                          
                          // Add stack
                          if (var_decl->is_tmp) {
                            SPVM_LIST_push(tmp_var_decl_stack, var_decl);
                          }
                          else {
                            SPVM_LIST_push(no_tmp_var_decl_stack, var_decl);
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
              
              method->call_stack_byte_vars_length = call_stack_byte_vars->length;
              method->call_stack_short_vars_length = call_stack_short_vars->length;
              method->call_stack_int_vars_length = call_stack_int_vars->length;
              method->call_stack_long_vars_length = call_stack_long_vars->length;
              method->call_stack_float_vars_length = call_stack_float_vars->length;
              method->call_stack_double_vars_length = call_stack_double_vars->length;
              method->call_stack_object_vars_length = call_stack_object_vars->length;
              method->call_stack_ref_vars_length = call_stack_ref_vars->length;

              SPVM_LIST_free(tmp_var_decl_stack);
              SPVM_LIST_free(no_tmp_var_decl_stack);
              SPVM_LIST_free(block_no_tmp_var_decl_base_stack);

              SPVM_LIST_free(call_stack_byte_vars);
              SPVM_LIST_free(call_stack_short_vars);
              SPVM_LIST_free(call_stack_int_vars);
              SPVM_LIST_free(call_stack_long_vars);
              SPVM_LIST_free(call_stack_float_vars);
              SPVM_LIST_free(call_stack_double_vars);
              SPVM_LIST_free(call_stack_object_vars);
              SPVM_LIST_free(call_stack_ref_vars);
            }
          }
        }
      }
    }
  }

#ifdef SPVM_DEBUG_DUMP
#include "spvm_dumper.h"
  if (SPVM_COMPILER_get_error_messages_length(compiler) == 0) {
    printf("\n[Basic types]\n");
    SPVM_DUMPER_dump_basic_types(compiler, compiler->basic_types);
    
    printf("\n[Classes]\n");
    SPVM_DUMPER_dump_classes(compiler, compiler->classes);
  }
#endif
}

SPVM_OP* SPVM_OP_CHECKER_check_assign(SPVM_COMPILER* compiler, SPVM_TYPE* dist_type, SPVM_OP* op_src, const char* place, const char* file, int32_t line) {
  SPVM_TYPE* src_type = SPVM_OP_get_type(compiler, op_src);
  
  int32_t dist_type_basic_type_id = dist_type->basic_type->id;
  int32_t dist_type_dimension = dist_type->dimension;
  int32_t dist_type_flag = dist_type->flag;
  
  int32_t src_type_basic_type_id = src_type->basic_type->id;
  int32_t src_type_dimension = src_type->dimension;
  int32_t src_type_flag = src_type->flag;

  SPVM_CONSTANT* src_constant = NULL;
  if (op_src->id == SPVM_OP_C_ID_CONSTANT) {
    src_constant = op_src->uv.constant;
  }

  int32_t need_implicite_conversion = 0;
  int32_t narrowing_conversion_error = 0;
  int32_t mutable_invalid = 0;
  
  int32_t can_assign = SPVM_TYPE_can_assign(
    compiler,
    dist_type_basic_type_id, dist_type_dimension, dist_type_flag,
    src_type_basic_type_id, src_type_dimension, src_type_flag,
    src_constant, &need_implicite_conversion, &narrowing_conversion_error, &mutable_invalid
  );
    
  if (!can_assign) {
    if (mutable_invalid) {
      SPVM_COMPILER_error(compiler, "Can't assign a non-mutable to a mutable type in %s, at %s line %d", place, file, line);
    }
    if (narrowing_conversion_error) {
      SPVM_COMPILER_error(compiler, "Can't apply narrowing conversion in %s at %s line %d", place, file, line);
      return NULL;
    }
    else {
      const char* src_type_name = SPVM_TYPE_new_type_name(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag);
      const char* dist_type_name = SPVM_TYPE_new_type_name(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag);
      SPVM_COMPILER_error(compiler, "Can't convert %s to %s by implicite type conversion in %s at %s line %d", src_type_name, dist_type_name, place, file, line);
      return NULL;
    }
  }
  
  if (need_implicite_conversion) {
    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_src);
    
    SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, file, line);
    SPVM_OP* op_dist_type = SPVM_OP_new_op_type(compiler, dist_type, file, line);
    SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_src, NULL);
    
    SPVM_OP_replace_op(compiler, op_stab, op_convert);
    return op_convert;
  }
  
  return op_src;
}

void SPVM_OP_CHECKER_resolve_op_types(SPVM_COMPILER* compiler) {

  SPVM_LIST* op_types = compiler->op_types;
  
  // Check type names
  for (int32_t i = 0; i < op_types->length; i++) {
    SPVM_OP* op_type = SPVM_LIST_get(op_types, i);
    
    SPVM_TYPE* type = op_type->uv.type;

    if (op_type->flag & SPVM_OP_C_FLAG_TYPE_IS_SELF) {
      continue;
    }
    else if (op_type->flag & SPVM_OP_C_FLAG_TYPE_IS_MAYBE_CLASS_ALIAS) {
      continue;
    }
    
    // Basic type name
    const char* basic_type_name = type->basic_type->name;
    
    // Check if type name is class
    if (type->basic_type->id >= SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_OBJECT) {
      
      // Unknonw class
      SPVM_HASH* class_symtable = compiler->class_symtable;
      SPVM_CLASS* found_class = SPVM_HASH_get(class_symtable, basic_type_name, strlen(basic_type_name));
      if (!found_class) {
        const char* not_found_class_class_name = SPVM_HASH_get(compiler->not_found_class_class_symtable, basic_type_name, strlen(basic_type_name));
        if (!not_found_class_class_name) {
          SPVM_COMPILER_error(compiler, "Unknown class \"%s\" at %s line %d", basic_type_name, op_type->file, op_type->line);
        }
      }
    }
    
    // Reference type must be numeric refernce type or value reference type
    if (SPVM_TYPE_is_ref_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
      if (!(SPVM_TYPE_is_numeric_ref_type(compiler, type->basic_type->id, type->dimension, type->flag) || SPVM_TYPE_is_mulnum_ref_type(compiler, type->basic_type->id, type->dimension, type->flag))) {
        SPVM_COMPILER_error(compiler, "Reference type must be numeric refernce type or mulnum_t reference type \"%s\"\\ at %s line %d", basic_type_name, op_type->file, op_type->line);
      }
    }
    
    // mutable only allow string type
    if (type->flag & SPVM_TYPE_C_FLAG_MUTABLE && !(type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && type->dimension == 0)) {
      SPVM_COMPILER_error(compiler, "The mutable type qualifier can use only string type at %s line %d", op_type->file, op_type->line);
    }

    if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT && type->dimension > 1) {
      const char* type_name = SPVM_TYPE_new_type_name(compiler, type->basic_type->id, type->dimension, type->flag);
      SPVM_COMPILER_error(compiler, "Multi dimensional array of any object is forbidden at %s line %d", op_type->file, op_type->line);
    }
  }
}

void SPVM_OP_CHECKER_resolve_types(SPVM_COMPILER* compiler) {

  SPVM_LIST* types = compiler->types;
  
  // Check type names
  for (int32_t i = 0; i < types->length; i++) {
    SPVM_TYPE* type = SPVM_LIST_get(types, i);
    type->width = SPVM_TYPE_get_width(compiler, type->basic_type->id, type->dimension, type->flag);
    
    if (type->basic_type->category == 0) {
      type->basic_type->category = SPVM_BASIC_TYPE_get_category(compiler, type->basic_type->id);
    }
  }
}

void SPVM_OP_CHECKER_resolve_call_method(SPVM_COMPILER* compiler, SPVM_OP* op_call_method, SPVM_OP* op_class_current) {
  
  SPVM_CALL_METHOD* call_method = op_call_method->uv.call_method;
  
  if (call_method->method) {
    return;
  }
  
  SPVM_CLASS* found_class;
  SPVM_METHOD* found_method;
  
  const char* method_name = call_method->op_name->uv.name;
  // Instance method call
  if (!call_method->is_class_method_call) {
    SPVM_TYPE* type = SPVM_OP_get_type(compiler, call_method->op_invocant);
    if (SPVM_TYPE_is_array_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
      const char* type_name = SPVM_TYPE_new_type_name(compiler, type->basic_type->id, type->dimension, type->flag);
      SPVM_COMPILER_error(compiler, "Unknown instance method \"%s->%s\" at %s line %d", type_name, method_name, op_call_method->file, op_call_method->line);
      return;
    }
    else {
      const char* basic_type_name = type->basic_type->name;
      
      found_class = SPVM_HASH_get(compiler->class_symtable, basic_type_name, strlen(basic_type_name));
      
      if (!found_class) {
        SPVM_COMPILER_error(compiler, "Unknown instance method \"%s->%s\" at %s line %d", basic_type_name, method_name, op_call_method->file, op_call_method->line);
        return;
      }
      
      found_method = SPVM_HASH_get(
        found_class->method_symtable,
        method_name,
        strlen(method_name)
      );
    }
  }
  // Class method call
  else {
    // Class name + method name
    if (call_method->op_invocant) {
      const char* class_name;
      if (call_method->op_invocant->id == SPVM_OP_C_ID_CURRENT_CLASS) {
        class_name = op_class_current->uv.class->name;
      }
      else {
        const char* class_name_maybe = call_method->op_invocant->uv.name;
        SPVM_CLASS* class_current = op_class_current->uv.class;
        class_name = SPVM_HASH_get(class_current->class_alias_symtable, class_name_maybe, strlen(class_name_maybe));
        if (class_name == NULL) {
          class_name = class_name_maybe;
        }
      }
      
      found_class = SPVM_HASH_get(compiler->class_symtable, class_name, strlen(class_name));
      
      if (found_class) {
        found_method = SPVM_HASH_get(
          found_class->method_symtable,
          method_name,
          strlen(method_name)
        );
      }
      else {
        SPVM_COMPILER_error(compiler, "Class \"%s\" not found at %s line %d", class_name, op_call_method->file, op_call_method->line);
        return;
      }
    }
    else {
      SPVM_COMPILER_error(compiler, "Unqualified method names are forbbiden \"%s\" at %s line %d", method_name, op_call_method->file, op_call_method->line);
      return;
    }
  }
  
  if (found_method) {
    call_method->method = found_method;
  }
  else {
    assert(found_class);
    SPVM_COMPILER_error(compiler, "Unknown method \"%s->%s\" at %s line %d", found_class->name, method_name, op_call_method->file, op_call_method->line);
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
  SPVM_CLASS* class = SPVM_HASH_get(compiler->class_symtable, invoker_type->basic_type->name, strlen(invoker_type->basic_type->name));
  const char* field_name = op_name->uv.name;
  
  SPVM_FIELD* found_field = SPVM_HASH_get(
    class->field_symtable,
    field_name,
    strlen(field_name)
  );
  if (found_field) {
    op_field_access->uv.field_access->field = found_field;
  }
}

void SPVM_OP_CHECKER_resolve_class_var_access(SPVM_COMPILER* compiler, SPVM_OP* op_class_var_access, SPVM_OP* op_current_class) {
  
  if (op_class_var_access->uv.class_var_access->class_var) {
    return;
  }
  assert(op_class_var_access->uv.class_var_access);
  
  SPVM_OP* op_name = op_class_var_access->uv.class_var_access->op_name;
  
  char* class_name;
  char* base_name;
  
  const char* name = op_name->uv.name;
  
  char* colon_ptr = strrchr(name, ':');
  if (colon_ptr) {
    // Class name
    // (end - start + 1) - $ - colon * 2
    int32_t class_name_length = (colon_ptr - name + 1) - 1 - 2;
    class_name = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, class_name_length + 1);
    memcpy(class_name, name + 1, class_name_length);
    
    // Base name($foo)
    int32_t base_name_length = 1 + (name + strlen(name) - 1) - colon_ptr;
    base_name = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, base_name_length + 1);
    base_name[0] = '$';
    memcpy(base_name + 1, colon_ptr + 1, base_name_length);
  }
  else {
    class_name = (char*)op_current_class->uv.class->name;
    base_name = (char*)name;
  }
  
  SPVM_CLASS* found_class = SPVM_HASH_get(compiler->class_symtable, class_name, strlen(class_name));
  if (found_class) {
    SPVM_CLASS_VAR* found_class_var = SPVM_HASH_get(found_class->class_var_symtable, base_name, strlen(base_name));
    if (found_class_var) {
      op_class_var_access->uv.class_var_access->class_var = found_class_var;
    }
  }
}

void SPVM_OP_CHECKER_resolve_basic_types(SPVM_COMPILER* compiler) {
  SPVM_LIST* basic_types = compiler->basic_types;
  
  for (int32_t basic_type_index = 0; basic_type_index < basic_types->length; basic_type_index++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(basic_types, basic_type_index);
    SPVM_CLASS* class = SPVM_HASH_get(compiler->class_symtable, basic_type->name, strlen(basic_type->name));
    if (class) {
      basic_type->class = class;
    }
  }
}

void SPVM_OP_CHECKER_resolve_field_offset(SPVM_COMPILER* compiler, SPVM_CLASS* class) {
  if (class->category != SPVM_CLASS_C_CATEGORY_CLASS) {
    return;
  }
  
  int32_t offset = 0;
  // 8 byte data
  for (int32_t field_index = 0; field_index < class->fields->length; field_index++) {
    SPVM_FIELD* field = SPVM_LIST_get(class->fields, field_index);
    SPVM_TYPE* field_type = field->type;
    if (SPVM_TYPE_is_double_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)
      || SPVM_TYPE_is_long_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)) {
      field->offset = offset;
      offset += 8;
    }
  }
  
  // 4 byte data
  for (int32_t field_index = 0; field_index < class->fields->length; field_index++) {
    SPVM_FIELD* field = SPVM_LIST_get(class->fields, field_index);
    SPVM_TYPE* field_type = field->type;
    if (SPVM_TYPE_is_float_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)
      || SPVM_TYPE_is_int_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)) {
      field->offset = offset;
      offset += 4;
    }
  }
  
  // 2 byte data
  for (int32_t field_index = 0; field_index < class->fields->length; field_index++) {
    SPVM_FIELD* field = SPVM_LIST_get(class->fields, field_index);
    SPVM_TYPE* field_type = field->type;
    if (SPVM_TYPE_is_short_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)) {
      field->offset = offset;
      offset += 2;
    }
  }
  
  // 1 byte data
  for (int32_t field_index = 0; field_index < class->fields->length; field_index++) {
    SPVM_FIELD* field = SPVM_LIST_get(class->fields, field_index);
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

  class->object_fields_offset = offset;
  
  // address data
  int32_t object_fields_length = 0;
  for (int32_t field_index = 0; field_index < class->fields->length; field_index++) {
    SPVM_FIELD* field = SPVM_LIST_get(class->fields, field_index);
    SPVM_TYPE* field_type = field->type;
    if (SPVM_TYPE_is_object_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)) {
      field->offset = offset;
      offset += sizeof(void*);
      object_fields_length++;
    }
  }
  class->object_fields_length = object_fields_length;
  class->fields_byte_size = offset;
}

void SPVM_OP_CHECKER_resolve_classes(SPVM_COMPILER* compiler) {
  
  // Set class id
  for (int32_t class_index = compiler->cur_class_base; class_index < compiler->classes->length; class_index++) {
    SPVM_CLASS* class = SPVM_LIST_get(compiler->classes, class_index);
    class->id = class_index;
  }
  
  for (int32_t class_index = compiler->cur_class_base; class_index < compiler->classes->length; class_index++) {
    SPVM_CLASS* class = SPVM_LIST_get(compiler->classes, class_index);
    
    const char* class_name = class->op_name->uv.name;
    
    // mulnum_t class limitation
    if (class->category == SPVM_CLASS_C_CATEGORY_MULNUM) {
      // Can't have methods
      if (class->methods->length > 0) {
        SPVM_COMPILER_error(compiler, "mulnum_t class can't have methods at %s line %d", class->op_class->file, class->op_class->line);
        return;
      }
      // Can't have class variables
      if (class->class_vars->length > 0) {
        SPVM_COMPILER_error(compiler, "mulnum_t class can't have class variables at %s line %d", class->op_class->file, class->op_class->line);
        return;
      }
      
      // At least have one field
      if (class->fields->length == 0) {
        SPVM_COMPILER_error(compiler, "mulnum_t class have at least one field at %s line %d", class->op_class->file, class->op_class->line);
        return;
      }
      // Minilal mulnum_t fields length is 1
      else if (class->fields->length < 1) {
        SPVM_COMPILER_error(compiler, "Neet at least one field at %s line %d", class->op_class->file, class->op_class->line);
        return;
      }
      // Max fields length is 255
      else if (class->fields->length > 255) {
        SPVM_COMPILER_error(compiler, "Too many mulnum_t fields. Max count of mulnum_t fields is 255 at %s line %d", class->op_class->file, class->op_class->line);
        return;
      }
      else {
        SPVM_LIST* fields = class->fields;
        SPVM_FIELD* first_field = SPVM_LIST_get(fields, 0);
        SPVM_TYPE* first_field_type = SPVM_OP_get_type(compiler, first_field->op_field);
        if (!SPVM_TYPE_is_numeric_type(compiler, first_field_type->basic_type->id, first_field_type->dimension, first_field_type->flag)) {
          SPVM_COMPILER_error(compiler, "mulnum_t class must have numeric field at %s line %d", first_field->op_field->file, first_field->op_field->line);
          return;
        }
        else {
          int32_t field_index;
          for (field_index = 0; field_index < class->fields->length; field_index++) {
            SPVM_FIELD* field = SPVM_LIST_get(fields, field_index);
            SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, field->op_field);
            if (!(field_type->basic_type->id == first_field_type->basic_type->id && field_type->dimension == first_field_type->dimension)) {
              SPVM_COMPILER_error(compiler, "field must have %s type at %s line %d", field_type->basic_type->name, field->op_field->file, field->op_field->line);
              return;
            }
          }
          
          // Check type name
          char* tail_name = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, 255);
          switch (first_field_type->basic_type->id) {
            case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE:
              sprintf(tail_name, "_%db", fields->length);
              break;
            case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT:
              sprintf(tail_name, "_%ds", fields->length);
              break;
            case SPVM_NATIVE_C_BASIC_TYPE_ID_INT:
              sprintf(tail_name, "_%di", fields->length);
              break;
            case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG:
              sprintf(tail_name, "_%dl", fields->length);
              break;
            case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT:
              sprintf(tail_name, "_%df", fields->length);
              break;
            case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE:
              sprintf(tail_name, "_%dd", fields->length);
              break;
            default:
              assert(0);
          }
          int32_t tail_name_length = (int32_t)strlen(tail_name);
          
          char* found_pos_ptr = strstr(class_name, tail_name);
          if (found_pos_ptr) {
            if (*(found_pos_ptr + tail_name_length) != '\0') {
              SPVM_COMPILER_error(compiler, "class name must end with %s at %s line %d", tail_name, class->op_class->file, class->op_class->line);
              return;
            }
          }
          else {
            SPVM_COMPILER_error(compiler, "class name must end with %s at %s line %d", tail_name, class->op_class->file, class->op_class->line);
            return;
          }
        }
      }
    }

    // Check class var
    for (int32_t class_var_index = 0; class_var_index < class->class_vars->length; class_var_index++) {
      SPVM_CLASS_VAR* class_var = SPVM_LIST_get(class->class_vars, class_var_index);
      SPVM_TYPE* class_var_type = SPVM_OP_get_type(compiler, class_var->op_class_var);
      int32_t is_mulnum_t = SPVM_TYPE_is_mulnum_type(compiler, class_var_type->basic_type->id, class_var_type->dimension, class_var_type->flag);
      
      // valut_t can't become class variable
      if (is_mulnum_t) {
        SPVM_COMPILER_error(compiler, "mulnum_t type can't become class variable at %s line %d", class_var->op_class_var->file, class_var->op_class_var->line);
        return;
      }

      // Create class var signature
      const char* class_var_signature = SPVM_COMPILER_create_class_var_signature(compiler, class_var);
      class_var->signature = class_var_signature;
    }
    
    // Check fields
    for (int32_t field_index = 0; field_index < class->fields->length; field_index++) {
      SPVM_FIELD* field = SPVM_LIST_get(class->fields, field_index);
      SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, field->op_field);

      if (strchr(field->op_name->uv.name, ':')) {
        SPVM_COMPILER_error(compiler, "field name can't contain :: at %s line %d", field->op_name->file, field->op_name->line);
        return;
      }

      // valut_t can't become field
      int32_t is_mulnum_t = SPVM_TYPE_is_mulnum_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag);
      if (is_mulnum_t) {
        SPVM_COMPILER_error(compiler, "mulnum_t type can't become field at %s line %d", field->op_field->file, field->op_field->line);
        return;
      }
      
      // Create field signature
      const char* field_signature = SPVM_COMPILER_create_field_signature(compiler, field);
      field->signature = field_signature;
    }
    
    SPVM_OP_CHECKER_resolve_field_offset(compiler, class);
    
    // Check methods
    for (int32_t i = 0; i < class->methods->length; i++) {
      SPVM_METHOD* method = SPVM_LIST_get(class->methods, i);
      
      // Argument limit check
      int32_t args_width = 0;
      SPVM_TYPE* last_arg_type = NULL;
      for (int32_t arg_index = 0; arg_index < method->args_length; arg_index++) {
        SPVM_VAR_DECL* arg_var_decl = SPVM_LIST_get(method->var_decls, arg_index);

        SPVM_TYPE* arg_type = arg_var_decl->type;
        
        int32_t is_arg_type_is_mulnum_type = SPVM_TYPE_is_mulnum_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag);
        int32_t is_arg_type_is_value_ref_type = SPVM_TYPE_is_mulnum_ref_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag);
        
        if (is_arg_type_is_mulnum_type || is_arg_type_is_value_ref_type) {
          args_width += arg_type->basic_type->class->fields->length;
        }
        else {
          args_width++;
        }
        
        if (arg_index == method->args_length - 1) {
          last_arg_type = arg_type;
        }
      }
      if (args_width > 255) {
        SPVM_COMPILER_error(compiler, "Too many arguments at %s line %d", method->op_method->file, method->op_method->line);
        return;
      }
      
      if (method->have_vaarg && !SPVM_TYPE_is_array_type(compiler, last_arg_type->basic_type->id, last_arg_type->dimension, last_arg_type->flag)) {
        SPVM_COMPILER_error(compiler, "When ... is specified, last argument type must be array at %s line %d", method->op_method->file, method->op_method->line);
        return;
      }
      
      // Is constant sub
      {
        SPVM_OP* op_block = method->op_block;
        if (op_block) {
          SPVM_OP* op_statements = op_block->last;
          
          int32_t statements_count = SPVM_OP_get_list_elements_count(compiler, op_statements);
          if (statements_count == 1) {
            SPVM_OP* op_return = op_statements->last;
            assert(op_return->id == SPVM_OP_C_ID_RETURN);
            
            SPVM_OP* op_constant = op_return->first;
            if (op_constant && op_constant->id == SPVM_OP_C_ID_CONSTANT) {
              method->is_constant = 1;
              method->op_inline = op_constant;
            }
          }
        }
      }
      
      // Is simple constructor sub
      {
        SPVM_OP* op_block = method->op_block;
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
              if (SPVM_TYPE_is_class_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                if (method->args_length == 0) {
                  method->is_simple_constructor = 1;
                  method->op_inline = op_type;
                }
              }
            }
          }
        }
      }
      
      // Can't return refernece type
      if (SPVM_TYPE_is_ref_type(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag)) {
        SPVM_COMPILER_error(compiler, "Can't return reference type at %s line %d", method->op_method->file, method->op_method->line);
        return;
      }

      // Create sub signature
      const char* method_signature = SPVM_COMPILER_create_method_signature(compiler, method);
      method->signature = method_signature;

      // Copy has_precomile_descriptor from anon sub defined class
      if (method->anon_method_defined_class_name) {
        SPVM_CLASS* anon_method_defined_class = SPVM_HASH_get(compiler->class_symtable, method->anon_method_defined_class_name, strlen(method->anon_method_defined_class_name));
        SPVM_LIST_push(anon_method_defined_class->anon_methods, method);
        class->is_precompile = anon_method_defined_class->is_precompile;
      }
    }
  }
  
  // classes must be interface the interface classes 
  for (int32_t class_index = compiler->cur_class_base; class_index < compiler->classes->length; class_index++) {
    SPVM_CLASS* class = SPVM_LIST_get(compiler->classes, class_index);
    
    // Add the interfaces to the class
    for (int32_t i = 0; i < class->interface_decls->length; i++) {
      SPVM_INTERFACE* interface_decl =  SPVM_LIST_get(class->interface_decls, i);

      SPVM_OP* op_interface = interface_decl->op_interface;
      
      const char* interface_name = interface_decl->class_name;
      
      SPVM_CLASS* interface = SPVM_HASH_get(compiler->class_symtable, interface_name, strlen(interface_name));
      
      if (interface->category != SPVM_CLASS_C_CATEGORY_INTERFACE) {
        SPVM_COMPILER_error(compiler, "The operand of the interface statment must be the interface class at %s line %d", interface->name, op_interface->file, op_interface->line);
        return;
      }
      
      SPVM_CLASS* found_interface = SPVM_HASH_get(class->interface_symtable, interface->name, strlen(interface->name));
      if (!found_interface) {
        SPVM_LIST_push(class->interfaces, interface);
        SPVM_HASH_set(class->interface_symtable, interface->name, strlen(interface->name), interface);
      }
    }

    // Add the anon method
    for (int32_t anon_methods_index = 0; anon_methods_index < class->anon_methods->length; anon_methods_index++) {
      SPVM_METHOD* anon_method = SPVM_LIST_get(class->anon_methods, anon_methods_index);
      anon_method->anon_method_id = compiler->anon_methods->length;
      SPVM_LIST_push(compiler->anon_methods, anon_method);
    }
  }

  for (int32_t class_index = compiler->cur_class_base; class_index < compiler->classes->length; class_index++) {
    SPVM_CLASS* class = SPVM_LIST_get(compiler->classes, class_index);
    
    SPVM_LIST* methods = class->methods;
    
    // Sort methods by name
    qsort(methods->values, methods->length, sizeof(SPVM_METHOD*), &SPVM_OP_CHECKER_method_name_cmp);
    
    // Create method ids
    for (int32_t i = 0; i < class->methods->length; i++) {
      SPVM_METHOD* method = SPVM_LIST_get(class->methods, i);
      
      // Set method precompile flag if class have precompile descriptor
      if (class->is_precompile) {
        int32_t can_precompile;
        if (method->is_class_var_setter) {
          can_precompile = 0;
        }
        else if (method->is_class_var_getter) {
          can_precompile = 0;
        }
        else if (method->is_field_setter) {
          can_precompile = 0;
        }
        else if (method->is_field_getter) {
          can_precompile = 0;
        }
        else if (method->is_simple_constructor) {
          can_precompile = 0;
        }
        else if (method->is_constant) {
          can_precompile = 0;
        }
        else if (method->is_init) {
          can_precompile = 0;
        }
        else if (method->is_enum) {
          can_precompile = 0;
        }
        // native method, methods of callback type or interface type
        else if (!method->op_block) {
          can_precompile = 0;
        }
        else {
          can_precompile = 1;
        }
        
        if (can_precompile) {
          method->is_precompile = 1;
        }
      }

      // Set method id
      method->id = compiler->methods->length;

      // Add the method to the compiler
      SPVM_LIST_push(compiler->methods, method);
      
      // Add the method arguments
      for (int32_t args_index = 0; args_index < method->args_length; args_index++) {
        SPVM_VAR_DECL* arg = SPVM_LIST_get(method->var_decls, args_index);
        arg->arg_id = compiler->args->length;
        SPVM_LIST_push(compiler->args, arg);
      }
    }

    for (int32_t i = 0; i < class->fields->length; i++) {
      SPVM_FIELD* field = SPVM_LIST_get(class->fields, i);

      // Set field id
      field->id = compiler->fields->length;

      // Add the field to the compiler
      SPVM_LIST_push(compiler->fields, field);
    }

    for (int32_t i = 0; i < class->class_vars->length; i++) {
      SPVM_CLASS_VAR* class_var = SPVM_LIST_get(class->class_vars, i);

      // Set class_var id
      class_var->id = compiler->class_vars->length;

      // Add the class_var to the compiler
      SPVM_LIST_push(compiler->class_vars, class_var);
    }
  }
}
