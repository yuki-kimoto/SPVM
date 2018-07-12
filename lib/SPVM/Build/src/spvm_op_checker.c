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

void SPVM_OP_CHECKER_resolve_basic_type_category(SPVM_COMPILER* compiler) {
  SPVM_LIST* basic_types = compiler->basic_types;
  
  {
    int32_t basic_type_index;
    for (basic_type_index = 0; basic_type_index < basic_types->length; basic_type_index++) {
      SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(basic_types, basic_type_index);
      int32_t basic_type_id = basic_type->id;
      if (basic_type_id == SPVM_BASIC_TYPE_C_ID_UNKNOWN) {
        basic_type->category = SPVM_BASIC_TYPE_C_CATEGORY_UNKNOWN;
      }
      else if (basic_type_id == SPVM_BASIC_TYPE_C_ID_VOID) {
        basic_type->category = SPVM_BASIC_TYPE_C_CATEGORY_VOID;
      }
      else if (basic_type_id == SPVM_BASIC_TYPE_C_ID_UNDEF) {
        basic_type->category = SPVM_BASIC_TYPE_C_CATEGORY_UNDEF;
      }
      else if (basic_type_id >= SPVM_BASIC_TYPE_C_ID_BYTE && basic_type_id <= SPVM_BASIC_TYPE_C_ID_DOUBLE) {
        basic_type->category = SPVM_BASIC_TYPE_C_CATEGORY_NUMERIC;
      }
      else if (basic_type_id == SPVM_BASIC_TYPE_C_ID_ANY_OBJECT) {
        basic_type->category = SPVM_BASIC_TYPE_C_CATEGORY_ANY_OBJECT;
      }
      else {
        SPVM_OP* op_package = SPVM_HASH_fetch(compiler->op_package_symtable, basic_type->name, strlen(basic_type->name));
        if (op_package) {
          SPVM_PACKAGE* package = op_package->uv.package;
          if (package->category == SPVM_PACKAGE_C_CATEGORY_CLASS) {
            basic_type->category = SPVM_BASIC_TYPE_C_CATEGORY_NUMERIC;
          }
          else if (package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE) {
            basic_type->category = SPVM_BASIC_TYPE_C_CATEGORY_INTERFACE;
          }
          else if (package->category == SPVM_PACKAGE_C_CATEGORY_POINTER) {
            basic_type->category = SPVM_BASIC_TYPE_C_CATEGORY_POINTER;
          }
          else if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE_T) {
            basic_type->category = SPVM_BASIC_TYPE_C_CATEGORY_VALUE_T;
          }
          else {
            assert(0);
          }
          basic_type->op_package = op_package;
        }
      }
    }
  }
}

void SPVM_OP_CHECKER_check(SPVM_COMPILER* compiler) {
  
  // Check types
  SPVM_OP_CHECKER_check_types(compiler);
  
  // Resolve basic type category
  SPVM_OP_CHECKER_resolve_basic_type_category(compiler);

  int32_t sub_id = 0;
  {
    int32_t package_index;
    for (package_index = 0; package_index < compiler->op_packages->length; package_index++) {
      SPVM_OP* op_package = SPVM_LIST_fetch(compiler->op_packages, package_index);
      
      SPVM_PACKAGE* package = op_package->uv.package;
      const char* package_name = package->op_name->uv.name;
      
      // value_t package limitation
      if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE_T) {
        // Can't have subroutines
        if (package->op_subs->length > 0) {
          SPVM_yyerror_format(compiler, "value_t package can't have subroutines at %s line %d\n", op_package->file, op_package->line);
        }
        // Can't have package variables
        if (package->op_package_vars->length > 0) {
          SPVM_yyerror_format(compiler, "value_t package can't have package variables at %s line %d\n", op_package->file, op_package->line);
        }
        
        // At least have one field
        if (package->op_fields->length == 0) {
          SPVM_yyerror_format(compiler, "value_t package have at least one field at %s line %d\n", op_package->file, op_package->line);
        }
        // Max fields length is 16
        else if (package->op_fields->length > SPVM_LIMIT_C_VALUE_T_FIELDS_LENGTH_MAX) {
          SPVM_yyerror_format(compiler, "Too many fields at %s line %d\n", op_package->file, op_package->line);
        }
        else {
          SPVM_LIST* op_fields = package->op_fields;
          SPVM_OP* op_first_field = SPVM_LIST_fetch(op_fields, 0);
          SPVM_TYPE* first_field_type = SPVM_OP_get_type(compiler, op_first_field);
          if (!SPVM_TYPE_is_numeric(compiler, first_field_type)) {
            SPVM_yyerror_format(compiler, "value_t package must have numeric field at %s line %d\n", op_first_field->file, op_first_field->line);
          }
          else {
            int32_t field_index;
            _Bool numeric_field_error = 0;
            for (field_index = 0; field_index < package->op_fields->length; field_index++) {
              SPVM_OP* op_field = SPVM_LIST_fetch(op_fields, field_index);
              SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, op_field);
              if (!(field_type->basic_type->id == first_field_type->basic_type->id && field_type->dimension == first_field_type->dimension)) {
                SPVM_yyerror_format(compiler, "field must have %s type at %s line %d\n", field_type->basic_type->name, op_field->file, op_field->line);
                numeric_field_error = 1;
              }
            }
            if (!numeric_field_error) {
              // Check type name
              char* tail_name = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, 255);
              switch (first_field_type->basic_type->id) {
                case SPVM_BASIC_TYPE_C_ID_BYTE:
                  sprintf(tail_name, "_b%d", op_fields->length);
                  break;
                case SPVM_BASIC_TYPE_C_ID_SHORT:
                  sprintf(tail_name, "_s%d", op_fields->length);
                  break;
                case SPVM_BASIC_TYPE_C_ID_INT:
                  sprintf(tail_name, "_i%d", op_fields->length);
                  break;
                case SPVM_BASIC_TYPE_C_ID_LONG:
                  sprintf(tail_name, "_l%d", op_fields->length);
                  break;
                case SPVM_BASIC_TYPE_C_ID_FLOAT:
                  sprintf(tail_name, "_f%d", op_fields->length);
                  break;
                case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                  sprintf(tail_name, "_d%d", op_fields->length);
                  break;
                default:
                  assert(0);
              }
              int32_t tail_name_length = (int32_t)strlen(tail_name);
              
              char* found_pos_ptr = strstr(package_name, tail_name);
              if (found_pos_ptr) {
                if (*(found_pos_ptr + tail_name_length) != '\0') {
                  SPVM_yyerror_format(compiler, "package name must end with %s at %s line %d\n", tail_name, op_package->file, op_package->line);
                }
              }
              else {
                SPVM_yyerror_format(compiler, "package name must end with %s at %s line %d\n", tail_name, op_package->file, op_package->line);
              }
            }
          }
        }
      }
      
      // valut_t can't become field
      {
        int32_t field_index;
        for (field_index = 0; field_index < op_package->uv.package->op_fields->length; field_index++) {
          SPVM_OP* op_field = SPVM_LIST_fetch(op_package->uv.package->op_fields, field_index);
          SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, op_field);
          _Bool is_value_t = SPVM_TYPE_is_value_t(compiler, field_type);
          
          if (is_value_t) {
            SPVM_yyerror_format(compiler, "value_t type can't become field at %s line %d\n", op_field->file, op_field->line);
          }
        }
      }
      
      // valut_t can't become package variable
      {
        int32_t package_var_index;
        for (package_var_index = 0; package_var_index < op_package->uv.package->op_package_vars->length; package_var_index++) {
          SPVM_OP* op_package_var = SPVM_LIST_fetch(op_package->uv.package->op_package_vars, package_var_index);
          SPVM_TYPE* package_var_type = SPVM_OP_get_type(compiler, op_package_var);
          _Bool is_value_t = SPVM_TYPE_is_value_t(compiler, package_var_type);
          
          if (is_value_t) {
            SPVM_yyerror_format(compiler, "value_t type can't become package variable at %s line %d\n", op_package_var->file, op_package_var->line);
          }
        }
      }

      SPVM_LIST* op_subs = op_package->uv.package->op_subs;
      {
        int32_t sub_index;
        for (sub_index = 0; sub_index < op_subs->length; sub_index++) {
          
          SPVM_OP* op_sub = SPVM_LIST_fetch(op_subs, sub_index);
          SPVM_SUB* sub = op_sub->uv.sub;
          SPVM_OP* op_package = sub->op_package;
          SPVM_PACKAGE* package = op_package->uv.package;
          SPVM_TYPE* package_type = package->op_type->uv.type;
          
          // Set subroutine id
          sub->id = sub_id++;
          
          
          // Destructor must receive own package object
          if (sub->is_destructor) {
            // DESTROY argument must be 0
            _Bool error = 0;
            if (sub->op_args->length != 1) {
              error = 1;
            }
            else {
              SPVM_OP* op_arg = SPVM_LIST_fetch(sub->op_args, 0);
              SPVM_TYPE* arg_type = SPVM_OP_get_type(compiler, op_arg);
              
              if (!(arg_type->basic_type->id == package_type->basic_type->id && arg_type->dimension == package_type->dimension)) {
                error = 1;
              }
            }
            
            if (error) {
              SPVM_yyerror_format(compiler, "DESTROY argument must be self\n", op_sub->file, op_sub->line);
            }
          }
          
          {
            int32_t arg_index;
            for (arg_index = 0 ; arg_index < sub->op_args->length; arg_index++) {
              SPVM_OP* op_arg = SPVM_LIST_fetch(sub->op_args, arg_index);
              SPVM_TYPE* arg_type = SPVM_OP_get_type(compiler, op_arg);
              if (SPVM_TYPE_is_object(compiler, arg_type)) {
                SPVM_LIST_push(sub->object_arg_ids, (void*)(intptr_t)arg_index);
              }
            }
          }
          
          if (package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE && (sub->op_block || sub->have_native_desc)) {
            SPVM_yyerror_format(compiler, "Interface sub can't have implementation\n", op_sub->file, op_sub->line);
          }
          
          // Check subroutine
          if (!sub->have_native_desc) {
            int32_t eval_block_stack_length = 0;
            int32_t loop_block_stack_length = 0;
            
            // My stack
            SPVM_LIST* op_my_stack = SPVM_LIST_new(0);
            
            // Block my base stack
            SPVM_LIST* block_my_base_stack = SPVM_LIST_new(0);
            
            // Switch stack
            SPVM_LIST* op_switch_stack = SPVM_LIST_new(0);
            
            // Run OPs
            SPVM_OP* op_base = SPVM_OP_get_op_block_from_op_sub(compiler, op_sub);
            SPVM_OP* op_cur = op_base;
            _Bool finish = 0;
            while (op_cur) {
              int32_t rel_line = op_cur->line - op_sub->line;
              if (op_cur->line >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                SPVM_yyerror_format(compiler, "Too many lines at %s line %d\n", op_cur->file, op_cur->line);
              }
              
              // [START]Preorder traversal position
              
              switch (op_cur->id) {
                // Start scope
                case SPVM_OP_C_ID_BLOCK: {

                  
                  int32_t block_my_base = op_my_stack->length;
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
                case SPVM_OP_C_ID_NEW: {
                  // If new package { ... } syntax, replace package to type
                  if (op_cur->first->id == SPVM_OP_C_ID_PACKAGE) {
                    SPVM_OP* op_package = op_cur->first;
                    SPVM_PACKAGE* package = op_package->uv.package;

                    SPVM_TYPE* type = package->op_type->uv.type;
                    
                    SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_package->file, op_package->line);
                    op_type->uv.type = type;
                    
                    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur->first);
                    SPVM_OP_replace_op(compiler, op_stab, op_type);
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
                      
                      _Bool add_constant = 0;
                      
                      if (type->dimension == 0) {
                        switch (type->basic_type->id) {
                          case SPVM_BASIC_TYPE_C_ID_LONG:
                          case SPVM_BASIC_TYPE_C_ID_DOUBLE:
                            add_constant = 1;
                        }
                      }
                      // String
                      else if (type->dimension == 1 && type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                        add_constant = 1;
                      }
                      
                      if (add_constant) {
                        if (sub->op_constants->length >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                          SPVM_yyerror_format(compiler, "Too many constant at %s line %d\n", op_cur->file, op_cur->line);
                        }
                        op_cur->uv.constant->sub_rel_id = sub->op_constants->length;
                        SPVM_LIST_push(sub->op_constants, op_cur);

                        if (sub->op_constants->length >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                          SPVM_yyerror_format(compiler, "Too many constant at %s line %d\n", op_cur->file, op_cur->line);
                        }
                        op_cur->uv.constant->sub_rel_id = sub->op_constants->length;
                        SPVM_LIST_push(sub->op_constants, op_cur);
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
                      SPVM_LIST* op_cases = switch_info->op_cases;
                      int32_t length = op_cases->length;
                      
                      // Check case type
                      {
                        int32_t i;
                        for (i = 0; i < length; i++) {
                          SPVM_OP* op_case = SPVM_LIST_fetch(op_cases, i);
                          SPVM_OP* op_constant = op_case->first;

                          if (op_constant->id != SPVM_OP_C_ID_CONSTANT) {
                            SPVM_yyerror_format(compiler, "case value must be constant at %s line %d\n", op_cur->file, op_cur->line);
                          }
                          
                          SPVM_TYPE* case_value_type = SPVM_OP_get_type(compiler, op_constant);
                          if (!(case_value_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT && case_value_type->dimension == 0)) {
                            SPVM_yyerror_format(compiler, "case value must be int constant at %s line %d\n", op_case->file, op_case->line);
                          }
                          op_case->uv.case_info->op_constant = op_constant;
                        }
                      }
                      
                      switch_info->id = SPVM_SWITCH_INFO_C_ID_LOOKUP_SWITCH;
                      
                      SPVM_LIST_pop(op_switch_stack);

                      if (sub->op_switch_infos->length >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                        SPVM_yyerror_format(compiler, "Too many switch at %s line %d\n", op_cur->file, op_cur->line);
                      }
                      op_cur->uv.switch_info->sub_rel_id = sub->op_switch_infos->length;
                      SPVM_LIST_push(sub->op_switch_infos, op_cur);
                    
                      break;
                    }
                    case SPVM_OP_C_ID_CASE: {
                      if (op_switch_stack->length > 0) {
                        SPVM_OP* op_switch = SPVM_LIST_fetch(op_switch_stack, op_switch_stack->length - 1);
                        SPVM_SWITCH_INFO* switch_info = op_switch->uv.switch_info;
                        op_cur->uv.case_info->index = switch_info->op_cases->length;
                        SPVM_LIST_push(switch_info->op_cases, op_cur);
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
                        if (SPVM_TYPE_is_numeric(compiler, first_type) && SPVM_TYPE_is_numeric(compiler, last_type)) {
                          SPVM_OP_apply_binary_numeric_promotion(compiler, op_cur->first, op_cur->last);
                        }
                        // numeric == OBJ
                        else if (SPVM_TYPE_is_numeric(compiler, first_type)) {
                          SPVM_yyerror_format(compiler, "== left value must be object at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        // OBJ == numeric
                        else if (SPVM_TYPE_is_numeric(compiler, last_type)) {
                          SPVM_yyerror_format(compiler, "== right value must be object at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                      }
                      // term == undef
                      else if (op_first->id != SPVM_OP_C_ID_UNDEF && op_last->id == SPVM_OP_C_ID_UNDEF) {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                        if (SPVM_TYPE_is_numeric(compiler, first_type)) {
                          SPVM_yyerror_format(compiler, "== left value must be object at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                      }
                      // undef == term
                      else if (op_first->id == SPVM_OP_C_ID_UNDEF && op_last->id != SPVM_OP_C_ID_UNDEF) {
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                        if (SPVM_TYPE_is_numeric(compiler, last_type)) {
                          SPVM_yyerror_format(compiler, "== right value must be object at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
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
                        if (SPVM_TYPE_is_numeric(compiler, first_type) && SPVM_TYPE_is_numeric(compiler, last_type)) {
                          SPVM_OP_apply_binary_numeric_promotion(compiler, op_cur->first, op_cur->last);
                        }
                        // numeric != OBJ
                        else if (SPVM_TYPE_is_numeric(compiler, first_type)) {
                          SPVM_yyerror_format(compiler, "!= left value must be object at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                        // OBJ != numeric
                        else if (SPVM_TYPE_is_numeric(compiler, last_type)) {
                          SPVM_yyerror_format(compiler, "!= right value must be object at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                      }
                      // term != undef
                      else if (op_first->id != SPVM_OP_C_ID_UNDEF && op_last->id == SPVM_OP_C_ID_UNDEF) {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);

                        if (SPVM_TYPE_is_numeric(compiler, first_type)) {
                          SPVM_yyerror_format(compiler, "!= left value must be object at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                      }
                      // undef != term
                      else if (op_first->id == SPVM_OP_C_ID_UNDEF && op_last->id != SPVM_OP_C_ID_UNDEF) {
                        SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

                        if (SPVM_TYPE_is_numeric(compiler, last_type)) {
                          SPVM_yyerror_format(compiler, "!= right value must be object at %s line %d\n", op_cur->file, op_cur->line);
                          
                          return;
                        }
                      }
                      
                      break;
                    }
                    case SPVM_OP_C_ID_LT: {

                      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                      SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                      
                      // undef check
                      if (!first_type) {
                        SPVM_yyerror_format(compiler, "< left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      if (!last_type) {
                        SPVM_yyerror_format(compiler, "< right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      // Can receive only numeric type
                      if (SPVM_TYPE_is_object(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "< left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      if (SPVM_TYPE_is_object(compiler, last_type)) {
                        SPVM_yyerror_format(compiler, "< right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }

                      SPVM_OP_apply_binary_numeric_promotion(compiler, op_cur->first, op_cur->last);

                      break;
                    }
                    case SPVM_OP_C_ID_LE: {

                      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                      SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

                      // undef check
                      if (!first_type) {
                        SPVM_yyerror_format(compiler, "<= left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      if (!last_type) {
                        SPVM_yyerror_format(compiler, "<= right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                                      
                      // Can receive only numeric type
                      if (SPVM_TYPE_is_object(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "<= left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      if (SPVM_TYPE_is_object(compiler, last_type)) {
                        SPVM_yyerror_format(compiler, "<= right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }

                      SPVM_OP_apply_binary_numeric_promotion(compiler, op_cur->first, op_cur->last);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_GT: {

                      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                      SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

                      // undef check
                      if (!first_type) {
                        SPVM_yyerror_format(compiler, "> left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      if (!last_type) {
                        SPVM_yyerror_format(compiler, "> right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      // Can receive only numeric type
                      if (SPVM_TYPE_is_object(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "> left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      if (SPVM_TYPE_is_object(compiler, last_type)) {
                        SPVM_yyerror_format(compiler, "> right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }

                      SPVM_OP_apply_binary_numeric_promotion(compiler, op_cur->first, op_cur->last);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_GE: {

                      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                      SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

                      // undef check
                      if (!first_type) {
                        SPVM_yyerror_format(compiler, "<= left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      if (!last_type) {
                        SPVM_yyerror_format(compiler, "<= right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      // Can receive only numeric type
                      if (SPVM_TYPE_is_numeric(compiler, first_type) && SPVM_TYPE_is_object(compiler, last_type)) {
                        SPVM_yyerror_format(compiler, ">= left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      if (SPVM_TYPE_is_object(compiler, first_type) && SPVM_TYPE_is_numeric(compiler, last_type)) {
                        SPVM_yyerror_format(compiler, ">= right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }

                      SPVM_OP_apply_binary_numeric_promotion(compiler, op_cur->first, op_cur->last);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_LEFT_SHIFT: {
                      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                      SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                      
                      // Can receive only numeric type
                      if (SPVM_TYPE_is_integral(compiler, first_type)) {
                        SPVM_OP_apply_unary_numeric_promotion(compiler, op_cur->first);
                      }
                      else {
                        SPVM_yyerror_format(compiler, "<< operator left value must be integral at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      if (SPVM_TYPE_is_integral(compiler, last_type)) {
                        SPVM_OP_apply_unary_numeric_promotion(compiler, op_cur->last);
                        
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
                      if (SPVM_TYPE_is_integral(compiler, first_type)) {
                        SPVM_OP_apply_unary_numeric_promotion(compiler, op_cur->first);
                      }
                      else {
                        SPVM_yyerror_format(compiler, ">> operator left value must be integral at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      if (SPVM_TYPE_is_integral(compiler, last_type)) {
                        SPVM_OP_apply_unary_numeric_promotion(compiler, op_cur->last);
                        
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
                      if (SPVM_TYPE_is_integral(compiler, first_type)) {
                        SPVM_OP_apply_unary_numeric_promotion(compiler, op_cur->first);
                      }
                      else {
                        SPVM_yyerror_format(compiler, ">>> operator left value must be integral at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      if (SPVM_TYPE_is_integral(compiler, last_type)) {
                        SPVM_OP_apply_unary_numeric_promotion(compiler, op_cur->last);
                        
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
                        SPVM_OP* op_type = op_cur->first;
                        
                        SPVM_TYPE* type = op_type->uv.type;
                        
                        // Array
                        if (SPVM_TYPE_is_array(compiler, type)) {
                          
                          SPVM_OP* op_index_term = op_type->last;

                          SPVM_TYPE* index_type = SPVM_OP_get_type(compiler, op_index_term);
                          
                          assert(index_type);
                          if (SPVM_TYPE_is_numeric(compiler, index_type)) {
                            SPVM_OP_apply_unary_numeric_promotion(compiler, op_index_term);
                            
                            SPVM_TYPE* index_type = SPVM_OP_get_type(compiler, op_index_term);
                            
                            if (!(index_type->dimension == 0 && index_type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_BYTE && index_type->basic_type->id <= SPVM_BASIC_TYPE_C_ID_INT)) {
                              char* type_name = compiler->tmp_buffer;
                              SPVM_TYPE_sprint_type_name(compiler, type_name, type->basic_type->id, type->dimension);
                              SPVM_yyerror_format(compiler, "new operator can't create array which don't have int length \"%s\" at %s line %d\n", type_name, op_cur->file, op_cur->line);
                              return;
                            }
                          }
                          else {
                            char* type_name = compiler->tmp_buffer;
                            SPVM_TYPE_sprint_type_name(compiler, type_name, type->basic_type->id, type->dimension);
                            SPVM_yyerror_format(compiler, "new operator can't create array which don't have numeric length \"%s\" at %s line %d\n", type_name, op_cur->file, op_cur->line);
                            return;
                          }
                          
                          // valut_t array dimension must be 1
                          SPVM_BASIC_TYPE* basic_type = type->basic_type;
                          SPVM_OP* op_package = SPVM_HASH_fetch(compiler->op_package_symtable, basic_type->name, strlen(basic_type->name));
                          if (op_package) {
                            SPVM_PACKAGE* package = op_package->uv.package;
                            if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE_T) {
                              if (type->dimension != 1) {
                                SPVM_yyerror_format(compiler, "Can't create multi dimention array of valut_t type at %s line %d\n", op_cur->file, op_cur->line);
                              }
                            }
                          }
                        }
                        // Numeric type
                        else if (SPVM_TYPE_is_numeric(compiler, type)) {
                          SPVM_yyerror_format(compiler, "new operator can't receive numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        }
                        // Object type
                        else if (SPVM_TYPE_is_object(compiler, type)) {
                          SPVM_OP* op_package = SPVM_HASH_fetch(compiler->op_package_symtable, type->basic_type->name, strlen(type->basic_type->name));
                          assert(op_package);
                          SPVM_PACKAGE* package = op_package->uv.package;
                          
                          if (package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE) {
                            SPVM_yyerror_format(compiler, "Can't create object of interface package at %s line %d\n", op_cur->file, op_cur->line);
                          }
                          else if (package->category == SPVM_PACKAGE_C_CATEGORY_POINTER) {
                            SPVM_yyerror_format(compiler, "Can't create object of struct package at %s line %d\n", op_cur->file, op_cur->line);
                          }
                          else if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE_T) {
                            SPVM_yyerror_format(compiler, "Can't create object of value_t package at %s line %d\n", op_cur->file, op_cur->line);
                          }
                          else if (package->is_private) {
                            if (strcmp(package->op_name->uv.name, sub->op_package->uv.package->op_name->uv.name) != 0) {
                              SPVM_yyerror_format(compiler, "Can't create object of private package at %s line %d\n", op_cur->file, op_cur->line);
                            }
                          }
                        }
                        else {
                          assert(0);
                        }
                        
                        if (sub->op_types->length >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                          SPVM_yyerror_format(compiler, "Too many types at %s line %d\n", op_cur->file, op_cur->line);
                        }
                        op_type->uv.type->sub_rel_id = sub->op_types->length;

                        if (sub->op_types->length >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                          SPVM_yyerror_format(compiler, "Too many types at %s line %d\n", op_cur->file, op_cur->line);
                        }
                        op_type->uv.type->sub_rel_id = sub->op_types->length;

                        SPVM_LIST_push(sub->op_types, op_type);
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
                      if (!SPVM_TYPE_is_integral(compiler, first_type) || !SPVM_TYPE_is_integral(compiler, last_type)) {
                        SPVM_yyerror_format(compiler,
                          "^ operator can receive only integral type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      SPVM_OP_apply_binary_numeric_promotion(compiler, op_cur->first, op_cur->last);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_BIT_OR: {
                      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                      SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                      
                      // Can receive only integral type
                      if (!SPVM_TYPE_is_integral(compiler, first_type) || !SPVM_TYPE_is_integral(compiler, last_type)) {
                        SPVM_yyerror_format(compiler,
                          "| operator can receive only integral type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      
                      SPVM_OP_apply_binary_numeric_promotion(compiler, op_cur->first, op_cur->last);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_BIT_AND: {
                      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                      SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                      
                      // Can receive only integral type
                      if (!SPVM_TYPE_is_integral(compiler, first_type) || !SPVM_TYPE_is_integral(compiler, last_type)) {
                        SPVM_yyerror_format(compiler,
                          "& operator can receive only integral type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      SPVM_OP_apply_binary_numeric_promotion(compiler, op_cur->first, op_cur->last);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_ISA: {
                      SPVM_TYPE* term_type = SPVM_OP_get_type(compiler, op_cur->first);
                      SPVM_OP* op_type = op_cur->last;
                      
                      // Can receive only numeric type
                      if (!SPVM_TYPE_is_object(compiler, term_type)) {
                        SPVM_yyerror_format(compiler, "isa left value must be object type at %s line %d\n", op_cur->file, op_cur->line);
                        return;
                      }

                      if (sub->op_types->length >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                        SPVM_yyerror_format(compiler, "Too many types at %s line %d\n", op_cur->file, op_cur->line);
                      }
                      op_type->uv.type->sub_rel_id = sub->op_types->length;

                      if (sub->op_types->length >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                        SPVM_yyerror_format(compiler, "Too many types at %s line %d\n", op_cur->file, op_cur->line);
                      }
                      op_type->uv.type->sub_rel_id = sub->op_types->length;

                      SPVM_LIST_push(sub->op_types, op_type);
                      
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
                      if (!SPVM_TYPE_is_string(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "eq left type must be string at %s line %d\n", op_cur->file, op_cur->line);
                        return;
                      }
                      if (!SPVM_TYPE_is_string(compiler, last_type)) {
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
                      if (!SPVM_TYPE_is_string(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "ne left type must be string at %s line %d\n", op_cur->file, op_cur->line);
                        return;
                      }
                      if (!SPVM_TYPE_is_string(compiler, last_type)) {
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
                      if (!SPVM_TYPE_is_string(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "gt left type must be string at %s line %d\n", op_cur->file, op_cur->line);
                        return;
                      }
                      if (!SPVM_TYPE_is_string(compiler, last_type)) {
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
                      if (!SPVM_TYPE_is_string(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "ge left type must be string at %s line %d\n", op_cur->file, op_cur->line);
                        return;
                      }
                      if (!SPVM_TYPE_is_string(compiler, last_type)) {
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
                      if (!SPVM_TYPE_is_string(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "lt left type must be string at %s line %d\n", op_cur->file, op_cur->line);
                        return;
                      }
                      if (!SPVM_TYPE_is_string(compiler, last_type)) {
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
                      if (!SPVM_TYPE_is_string(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "le left type must be string at %s line %d\n", op_cur->file, op_cur->line);
                        return;
                      }
                      if (!SPVM_TYPE_is_string(compiler, last_type)) {
                        SPVM_yyerror_format(compiler, "le right type must be string at %s line %d\n", op_cur->file, op_cur->line);
                        return;
                      }
                      
                      break;
                    }
                    case SPVM_OP_C_ID_ARRAY_LENGTH: {
                      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                      
                      // First value must be array
                      if (!SPVM_TYPE_is_array(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "right of @ or len must be array at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      break;
                    }
                    case SPVM_OP_C_ID_ARRAY_ACCESS: {
                      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                      SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                      
                      // Left value must be array
                      if (!SPVM_TYPE_is_array(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "left value must be array at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      // Right value must be integer
                      if (SPVM_TYPE_is_numeric(compiler, last_type)) {
                        SPVM_OP_apply_unary_numeric_promotion(compiler, op_cur->last);
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
                      
                      break;
                    }
                    case SPVM_OP_C_ID_ASSIGN: {
                      SPVM_OP* op_term_to = op_cur->last;
                      SPVM_OP* op_term_from = op_cur->first;
                      
                      SPVM_TYPE* to_type = SPVM_OP_get_type(compiler, op_term_to);
                      SPVM_TYPE* from_type = SPVM_OP_get_type(compiler, op_term_from);
                      
                      // From type is undef
                      if (from_type->dimension == 0 && from_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_UNDEF) {
                        // To type is undef
                        if (to_type->dimension == 0 && to_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_UNDEF) { 
                          SPVM_yyerror_format(compiler, "undef can't be assigned to undef at %s line %d\n", op_cur->file, op_cur->line);
                        }
                        else {
                          _Bool to_type_is_value_t = SPVM_TYPE_is_value_t(compiler, to_type);
                          if (to_type_is_value_t) {
                            SPVM_yyerror_format(compiler, "undef can't be assigned to value_t type at %s line %d\n", op_cur->file, op_cur->line);
                          }
                        }
                      }
                      
                      // Check if source value can be assigned to distination value
                      // If needed, automatical numeric convertion op is added
                      SPVM_OP_CHECKER_check_and_convert_type(compiler, op_term_to, op_term_from);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_RETURN: {
                      
                      SPVM_OP* op_term = op_cur->first;
                      
                      if (op_term) {
                        SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_term);
                        SPVM_TYPE* sub_return_type = SPVM_OP_get_type(compiler, sub->op_return_type);
                        
                        _Bool is_invalid = 0;
                        
                        
                        // Undef
                        if (op_term->id == SPVM_OP_C_ID_UNDEF) {
                          if (sub->op_return_type->uv.type->dimension == 0 && sub->op_return_type->uv.type->basic_type->id == SPVM_BASIC_TYPE_C_ID_VOID) {
                            is_invalid = 1;
                          }
                          else {
                            if (SPVM_TYPE_is_numeric(compiler, sub_return_type)) {
                              is_invalid = 1;
                            }
                          }
                        }
                        else if (op_term->id == SPVM_OP_C_ID_CALL_SUB) {
                          SPVM_CALL_SUB* call_sub = op_term->uv.call_sub;
                          SPVM_SUB* sub = call_sub->sub;
                          if (sub->op_return_type->uv.type->dimension == 0 && sub->op_return_type->uv.type->basic_type->id == SPVM_BASIC_TYPE_C_ID_VOID) {
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
                          if (!(sub->op_return_type->uv.type->dimension == 0 && sub->op_return_type->uv.type->basic_type->id == SPVM_BASIC_TYPE_C_ID_VOID)) {
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
                      if (SPVM_TYPE_is_object(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "- operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      SPVM_OP_apply_unary_numeric_promotion(compiler, op_cur->first);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_COMPLEMENT: {
                      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                      
                      // Must be numeric type
                      if (!SPVM_TYPE_is_integral(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "~ operator right value must be integral type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }

                      SPVM_OP_apply_unary_numeric_promotion(compiler, op_cur->first);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_PLUS: {
                      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                      
                      // Must be numeric type
                      if (SPVM_TYPE_is_object(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "+ operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }

                      SPVM_OP_apply_unary_numeric_promotion(compiler, op_cur->first);
                      
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
                      if (SPVM_TYPE_is_object(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "+ operator left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }

                      // Right value must not be object type
                      if (SPVM_TYPE_is_object(compiler, last_type)) {
                        SPVM_yyerror_format(compiler, "+ operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      // Upgrade type
                      SPVM_OP_apply_binary_numeric_promotion(compiler, op_cur->first, op_cur->last);
                                                      
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
                      if (SPVM_TYPE_is_object(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "- operator left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }

                      // Right value must not be object type
                      if (SPVM_TYPE_is_object(compiler, last_type)) {
                        SPVM_yyerror_format(compiler, "- operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      // Upgrade type
                      SPVM_OP_apply_binary_numeric_promotion(compiler, op_cur->first, op_cur->last);
                      
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
                      if (SPVM_TYPE_is_object(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "* operator left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }

                      // Right value must not be object type
                      if (SPVM_TYPE_is_object(compiler, last_type)) {
                        SPVM_yyerror_format(compiler, "* operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }

                      // Upgrade type
                      SPVM_OP_apply_binary_numeric_promotion(compiler, op_cur->first, op_cur->last);
                      
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
                      if (SPVM_TYPE_is_object(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "/ operator left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }

                      // Right value must not be object type
                      if (SPVM_TYPE_is_object(compiler, last_type)) {
                        SPVM_yyerror_format(compiler, "/ operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      // Upgrade type
                      SPVM_OP_apply_binary_numeric_promotion(compiler, op_cur->first, op_cur->last);

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
                      if (SPVM_TYPE_is_object(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "%% operator left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }

                      // Right value must not be object type
                      if (SPVM_TYPE_is_object(compiler, last_type)) {
                        SPVM_yyerror_format(compiler, "%% operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      // Upgrade type
                      SPVM_OP_apply_binary_numeric_promotion(compiler, op_cur->first, op_cur->last);
                                                      
                      break;
                    }
                    case SPVM_OP_C_ID_PRE_INC:
                    case SPVM_OP_C_ID_POST_INC:
                    {
                      SPVM_OP* op_first = op_cur->first;
                      if (op_first->id != SPVM_OP_C_ID_VAR) {
                        SPVM_yyerror_format(compiler, "Only increment var at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_first);
                      
                      // Numeric type
                      if (!SPVM_TYPE_is_numeric(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "increment operand must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      if (!op_cur->is_assigned_to_var && !op_cur->is_passed_to_sub) {
                        op_cur->id = SPVM_OP_C_ID_INC;
                      }
                      else {
                        // Convert PRE_INC
                        // [before]
                        // PRE_INC
                        //   VAR
                        // 
                        // [after]
                        // SEQUENCE
                        //   INC
                        //     VAR_INC
                        //   VAR_RET
                        if (op_cur->id == SPVM_OP_C_ID_PRE_INC) {
                          SPVM_OP* op_var = op_cur->first;
                        
                          SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, op_cur->file, op_cur->line);
                          SPVM_OP* op_var_inc = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_VAR, op_cur->file, op_cur->line);
                          op_var_inc->uv.var = op_var->uv.var;
                          
                          SPVM_OP* op_inc = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_INC, op_cur->file, op_cur->line);
                          SPVM_OP_insert_child(compiler, op_inc, op_inc->last, op_var_inc);
                          
                          SPVM_OP* op_var_ret = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_VAR, op_cur->file, op_cur->line);
                          op_var_ret->uv.var = op_var->uv.var;
                          SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_inc);
                          SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_var_ret);
                          
                          SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                          SPVM_OP_replace_op(compiler, op_stab, op_sequence);
                          
                          op_cur = op_sequence;
                        }
                        // Convert POST_INC
                        // [before]
                        // POST_INC
                        //   VAR
                        // 
                        // [after]
                        // SEQUENCE
                        //   ASSIGN
                        //     VAR_FROM
                        //     VAR_TMP
                        //   INC
                        //     VAR_INC
                        //   VAR_RET
                        else if (op_cur->id == SPVM_OP_C_ID_POST_INC) {
                          SPVM_OP* op_var = op_cur->first;
                        
                          SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, op_cur->file, op_cur->line);
                          SPVM_OP* op_var_from = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_VAR, op_cur->file, op_cur->line);
                          op_var_from->uv.var = op_var->uv.var;
                          
                          SPVM_OP* op_var_tmp = SPVM_OP_new_op_var_tmp(compiler, op_sub, op_var->uv.var->op_my->uv.my->op_type->uv.type, op_cur->file, op_cur->line);
                    
                          SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                          SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_var_from);
                          
                          SPVM_OP* op_var_inc = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_VAR, op_cur->file, op_cur->line);
                          op_var_inc->uv.var = op_var->uv.var;
                          
                          SPVM_OP* op_inc = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_INC, op_cur->file, op_cur->line);
                          SPVM_OP_insert_child(compiler, op_inc, op_inc->last, op_var_inc);
                          
                          SPVM_OP* op_var_ret = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_VAR, op_cur->file, op_cur->line);
                          op_var_ret->uv.var = op_var_tmp->uv.var;
                          SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_assign);
                          SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_inc);
                          SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_var_ret);
                          
                          SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                          SPVM_OP_replace_op(compiler, op_stab, op_sequence);
                          
                          op_cur = op_sequence;
                        }
                        else {
                          assert(0);
                        }
                      }
                      
                      break;
                    }
                    case SPVM_OP_C_ID_PRE_DEC:
                    case SPVM_OP_C_ID_POST_DEC:
                    {
                      SPVM_OP* op_first = op_cur->first;
                      if (op_first->id != SPVM_OP_C_ID_VAR) {
                        SPVM_yyerror_format(compiler, "Only decrement var at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_first);
                      
                      // Numeric type
                      if (!SPVM_TYPE_is_numeric(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, "decrement operand must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }

                      if (!op_cur->is_assigned_to_var && !op_cur->is_passed_to_sub) {
                        op_cur->id = SPVM_OP_C_ID_DEC;
                      }
                      else {
                        // Convert PRE_DEC
                        // [before]
                        // PRE_DEC
                        //   VAR
                        // 
                        // [after]
                        // SEQUENCE
                        //   DEC
                        //     VAR_DEC
                        //   VAR_RET
                        if (op_cur->id == SPVM_OP_C_ID_PRE_DEC) {
                          SPVM_OP* op_var = op_cur->first;
                          
                          SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, op_cur->file, op_cur->line);
                          SPVM_OP* op_var_dec = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_VAR, op_cur->file, op_cur->line);
                          op_var_dec->uv.var = op_var->uv.var;
                          
                          SPVM_OP* op_dec = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DEC, op_cur->file, op_cur->line);
                          SPVM_OP_insert_child(compiler, op_dec, op_dec->last, op_var_dec);
                          
                          SPVM_OP* op_var_ret = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_VAR, op_cur->file, op_cur->line);
                          op_var_ret->uv.var = op_var->uv.var;
                          SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_dec);
                          SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_var_ret);
                          
                          SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                          SPVM_OP_replace_op(compiler, op_stab, op_sequence);
                          
                          op_cur = op_sequence;
                        }
                        // Convert POST_DEC
                        // [before]
                        // POST_DEC
                        //   VAR
                        // 
                        // [after]
                        // SEQUENCE
                        //   ASSIGN
                        //     VAR_FROM
                        //     VAR_TMP
                        //   DEC
                        //     VAR_DEC
                        //   VAR_RET
                        else if (op_cur->id == SPVM_OP_C_ID_POST_DEC) {
                          SPVM_OP* op_var = op_cur->first;
                        
                          SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, op_cur->file, op_cur->line);
                          SPVM_OP* op_var_from = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_VAR, op_cur->file, op_cur->line);
                          op_var_from->uv.var = op_var->uv.var;
                          
                          SPVM_OP* op_var_tmp = SPVM_OP_new_op_var_tmp(compiler, op_sub, op_var->uv.var->op_my->uv.my->op_type->uv.type, op_cur->file, op_cur->line);
                    
                          SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                          SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_var_from);
                          
                          SPVM_OP* op_var_dec = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_VAR, op_cur->file, op_cur->line);
                          op_var_dec->uv.var = op_var->uv.var;
                          
                          SPVM_OP* op_dec = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DEC, op_cur->file, op_cur->line);
                          SPVM_OP_insert_child(compiler, op_dec, op_dec->last, op_var_dec);
                          
                          SPVM_OP* op_var_ret = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_VAR, op_cur->file, op_cur->line);
                          op_var_ret->uv.var = op_var_tmp->uv.var;
                          SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_assign);
                          SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_dec);
                          SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_var_ret);
                          
                          SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                          SPVM_OP_replace_op(compiler, op_stab, op_sequence);
                          
                          op_cur = op_sequence;
                        }
                        else {
                          assert(0);
                        }
                      }
                      
                      break;
                    }
                    case SPVM_OP_C_ID_CONCAT: {
                      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                      SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                      
                      // Left type must be string
                      if (!SPVM_TYPE_is_string(compiler, first_type)) {
                        SPVM_yyerror_format(compiler, ". operator left value must be string at %s line %d\n", op_cur->file, op_cur->line);
                        return;
                      }
                      
                      // First value must be numeric or byte array
                      if (!SPVM_TYPE_is_string(compiler, last_type)) {
                        SPVM_yyerror_format(compiler, ". operator right value must be string at %s line %d\n", op_cur->file, op_cur->line);
                        return;
                      }
                      
                      break;
                    }
                    case SPVM_OP_C_ID_CROAK: {
                      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                      if (first_type->dimension == 1 && first_type->basic_type->id != SPVM_BASIC_TYPE_C_ID_BYTE) {
                        SPVM_yyerror_format(compiler, "croak argument must be string at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      break;
                    }
                    // End of scope
                    case SPVM_OP_C_ID_BLOCK: {
                      // Pop block my variable base
                      assert(block_my_base_stack->length > 0);
                      int32_t block_my_base = (intptr_t)SPVM_LIST_pop(block_my_base_stack);
                        
                      int32_t my_stack_pop_count = op_my_stack->length - block_my_base;
                      
                      {
                        int32_t i;
                        for (i = 0; i < my_stack_pop_count; i++) {
                          SPVM_LIST_pop(op_my_stack);
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
                    // Add my var
                    case SPVM_OP_C_ID_VAR: {
                      
                      SPVM_VAR* var = op_cur->uv.var;
                      
                      // Search same name variable
                      SPVM_OP* found_op_my = NULL;
                      {
                        int32_t i;
                        for (i = op_my_stack->length - 1; i >= 0; i--) {
                          SPVM_OP* op_my = SPVM_LIST_fetch(op_my_stack, i);
                          SPVM_MY* my = op_my->uv.my;
                          if (strcmp(var->op_name->uv.name, my->op_name->uv.name) == 0) {
                            found_op_my = op_my;
                            break;
                          }
                        }
                      }
                      
                      if (found_op_my) {
                        // Add my var information to var
                        var->op_my = found_op_my;
                      }
                      else {
                        // Error
                        SPVM_yyerror_format(compiler, "%s is undeclared in this scope at %s line %d\n", var->op_name->uv.name, op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      break;
                    }
                    case SPVM_OP_C_ID_MY: {
                      SPVM_MY* my = op_cur->uv.my;
                      
                      // Redeclaration error if same name variable is declare in same block
                      _Bool found = 0;
                      int32_t block_my_base = (intptr_t)SPVM_LIST_fetch(block_my_base_stack, block_my_base_stack->length - 1);
                      {
                        int32_t i;
                        for (i = block_my_base; i < op_my_stack->length; i++) {
                          SPVM_OP* op_bef_my = SPVM_LIST_fetch(op_my_stack, i);
                          SPVM_MY* bef_my = op_bef_my->uv.my;
                          if (strcmp(my->op_name->uv.name, bef_my->op_name->uv.name) == 0) {
                            found = 1;
                            break;
                          }
                        }
                      }
                      if (found) {
                        SPVM_yyerror_format(compiler, "redeclaration of my \"%s\" at %s line %d\n", my->op_name->uv.name, op_cur->file, op_cur->line);
                        
                        return;
                      }
                      else {
                        SPVM_LIST_push(sub->op_mys, op_cur);
                        SPVM_LIST_push(op_my_stack, op_cur);
                      }
                      
                      // Type inference
                      if (my->op_type == NULL) {
                        if (my->try_type_inference) {
                          SPVM_OP* op_term_type_inference = my->op_term_type_inference;
                          
                          SPVM_TYPE* inferenced_type = SPVM_OP_get_type(compiler, op_term_type_inference);
                          
                          if (inferenced_type) {
                            my->op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_cur->file, op_cur->line);
                            my->op_type->uv.type = inferenced_type;
                          }
                        }
                      }
                      
                      // Type can't be detected
                      if (my->op_type == NULL) {
                        SPVM_yyerror_format(compiler, "Type can't be detected at %s line %d\n", op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      break;
                    }
                    case SPVM_OP_C_ID_CALL_SUB: {
                      
                      // Check sub name
                      SPVM_OP_CHECKER_resolve_call_sub(compiler, op_cur, op_package);
                      
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
                      
                      int32_t sub_args_count = call_sub->sub->op_args->length;
                      SPVM_OP* op_term = op_list_args->first;
                      int32_t call_sub_args_count = 0;
                      while ((op_term = SPVM_OP_sibling(compiler, op_term))) {
                        call_sub_args_count++;
                        if (call_sub_args_count > sub_args_count) {
                          SPVM_yyerror_format(compiler, "Too many arguments. sub \"%s\" at %s line %d\n", sub_abs_name, op_cur->file, op_cur->line);
                          
                          return;
                        }
                        
                        SPVM_OP* op_sub_arg_my = SPVM_LIST_fetch(call_sub->sub->op_args, call_sub_args_count - 1);
                        
                        op_term = SPVM_OP_CHECKER_check_and_convert_type(compiler, op_sub_arg_my, op_term);
                      }
                      
                      if (call_sub_args_count < sub_args_count) {
                        SPVM_yyerror_format(compiler, "Too few argument. sub \"%s\" at %s line %d\n", sub_abs_name, op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      // Constant subroutine
                      if (call_sub->sub->is_enum) {
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

                      if (sub->op_call_subs->length >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                        SPVM_yyerror_format(compiler, "Too many call sub at %s line %d\n", op_cur->file, op_cur->line);
                      }
                      op_cur->uv.call_sub->sub_rel_id = sub->op_call_subs->length;
                      SPVM_LIST_push(sub->op_call_subs, op_cur);
                      
                      if (sub->op_call_subs->length >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                        SPVM_yyerror_format(compiler, "Too many call sub at %s line %d\n", op_cur->file, op_cur->line);
                      }
                      op_cur->uv.call_sub->sub_rel_id = sub->op_call_subs->length;
                      SPVM_LIST_push(sub->op_call_subs, op_cur);
                      
                      if (call_sub->sub->is_destructor) {
                        SPVM_yyerror_format(compiler, "Can't call DESTROY in yourself at %s line %d\n", op_cur->file, op_cur->line);
                      }
                      
                      break;
                    }
                    case SPVM_OP_C_ID_PACKAGE_VAR_ACCESS: {
                      
                      // Check field name
                      SPVM_OP_CHECKER_resolve_package_var_access(compiler, op_cur, op_package);
                      if (!op_cur->uv.package_var_access->op_package_var) {
                        SPVM_yyerror_format(compiler, "Package variable not found \"%s\" at %s line %d\n",
                          op_cur->uv.package_var_access->op_name->uv.name, op_cur->file, op_cur->line);
                        
                        return;
                      }
                      
                      if (sub->op_package_var_accesses->length >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                        SPVM_yyerror_format(compiler, "Too many package variable access at %s line %d\n", op_cur->file, op_cur->line);
                      }
                      op_cur->uv.package_var_access->sub_rel_id = sub->op_package_var_accesses->length;
                      SPVM_LIST_push(sub->op_package_var_accesses, op_cur);
                      
                      break;
                    }
                    case SPVM_OP_C_ID_FIELD_ACCESS: {
                      SPVM_OP* op_term_invocker = op_cur->first;
                      SPVM_OP* op_name = op_cur->uv.field_access->op_name;
                      
                      if (op_term_invocker->id == SPVM_OP_C_ID_ASSIGN) {
                        op_term_invocker = op_term_invocker->first;
                      }
                      
                      SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_term_invocker);
                      SPVM_OP* op_package = SPVM_HASH_fetch(compiler->op_package_symtable, type->basic_type->name, strlen(type->basic_type->name));
                      
                      if (!(type && op_package)) {
                        SPVM_yyerror_format(compiler, "Invalid invoker at %s line %d\n", op_cur->file, op_cur->line);
                        return;
                      }
                      
                      // Check field name
                      SPVM_OP_CHECKER_resolve_field_access(compiler, op_cur);
                      
                      SPVM_FIELD* field = op_cur->uv.field_access->field;
                      
                      if (!field) {
                        char* type_name = compiler->tmp_buffer;
                        SPVM_TYPE_sprint_type_name(compiler, type_name, type->basic_type->id, type->dimension);
                        SPVM_yyerror_format(compiler, "Unknown field %s::%s at %s line %d\n",
                          type_name, op_name->uv.name, op_cur->file, op_cur->line);
                        return;
                      }
                      
                      if (field->is_private) {
                        if (strcmp(type->basic_type->name, sub->op_package->uv.package->op_name->uv.name) != 0) {
                          char* type_name = compiler->tmp_buffer;
                          SPVM_TYPE_sprint_type_name(compiler, type_name, type->basic_type->id, type->dimension);
                          SPVM_yyerror_format(compiler, "Can't access to private field %s::%s at %s line %d\n",
                            type_name, op_name->uv.name, op_cur->file, op_cur->line);
                        }
                      }
                      
                      if (sub->op_field_accesses->length >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                        SPVM_yyerror_format(compiler, "Too many field access at %s line %d\n", op_cur->file, op_cur->line);
                      }
                      op_cur->uv.field_access->sub_rel_id = sub->op_field_accesses->length;
                      SPVM_LIST_push(sub->op_field_accesses, op_cur);
                      
                      // If invocker is array access and array access object is value_t, this op become array field access
                      if (op_term_invocker->id == SPVM_OP_C_ID_ARRAY_ACCESS) {
                        SPVM_OP* op_array_access = op_term_invocker;
                        
                        SPVM_TYPE* array_element_type = SPVM_OP_get_type(compiler, op_array_access);
                        
                        _Bool is_basic_type_value_t = SPVM_TYPE_is_basic_type_value_t(compiler, array_element_type);
                        if (is_basic_type_value_t) {
                          if (array_element_type->dimension != 0) {
                            SPVM_yyerror_format(compiler, "value_t array field access must be 1-dimension array at %s line %d\n", op_cur->file, op_cur->line);
                          }
                          else {
                            SPVM_OP* op_array_field_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_FIELD_ACCESS, op_cur->file, op_cur->line);
                            op_array_field_access->is_lvalue = op_cur->is_lvalue;
                            op_array_field_access->is_assigned_to_var = op_cur->is_assigned_to_var;
                            
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
                      
                      break;
                    }
                    case SPVM_OP_C_ID_WEAKEN_FIELD: {
                      SPVM_OP* op_field_access = op_cur->first;
                      
                      SPVM_FIELD* field = op_field_access->uv.field_access->field;
                      
                      SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_field_access);
                      
                      if (type->dimension == 0 && type->basic_type->id <= SPVM_BASIC_TYPE_C_ID_DOUBLE) {
                        SPVM_yyerror_format(compiler, "weaken is only used for object field \"%s\" \"%s\" at %s line %d\n",
                          field->op_package->uv.package->op_name->uv.name, field->op_name->uv.name, op_cur->file, op_cur->line);
                        
                        break;
                      }
                      
                      break;
                    }
                    case SPVM_OP_C_ID_CONVERT: {
                      
                      SPVM_OP* op_term = op_cur->first;
                      SPVM_OP* op_type = op_cur->last;
                      
                      SPVM_TYPE* term_type = SPVM_OP_get_type(compiler, op_term);
                      assert(term_type);
                      
                      SPVM_TYPE* type_type = SPVM_OP_get_type(compiler, op_type);
                      assert(type_type);
                      
                      _Bool can_convert;
                      if (SPVM_TYPE_is_numeric(compiler, term_type) && SPVM_TYPE_is_numeric(compiler, type_type)) {
                        can_convert = 1;
                      }
                      else if (SPVM_TYPE_is_numeric(compiler, term_type) && (type_type->dimension == 1 && type_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE)) {
                        can_convert = 1;
                      }
                      else if (SPVM_TYPE_is_object(compiler, term_type) && SPVM_TYPE_is_object(compiler, type_type)) {
                        if (SPVM_TYPE_is_array_numeric(compiler, term_type) && !SPVM_TYPE_is_array_numeric(compiler, type_type)) {
                          if (type_type->dimension == 2 && type_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
                            can_convert = 1;
                          }
                          else {
                            can_convert = 0;
                          }
                        }
                        else if (!SPVM_TYPE_is_array_numeric(compiler, term_type) && SPVM_TYPE_is_array_numeric(compiler, type_type)) {
                          can_convert = 0;
                        }
                        else {
                          if (term_type->dimension == type_type->dimension) {
                            can_convert = 1;
                          }
                          else {
                            can_convert = 0;
                          }
                        }
                        
                      }
                      else {
                        can_convert = 0;
                      }
                      
                      if (!can_convert) {
                        char* type_type_name = compiler->tmp_buffer;
                        SPVM_TYPE_sprint_type_name(compiler, type_type_name, type_type->basic_type->id, type_type->dimension);
                        SPVM_yyerror_format(compiler, "Can't convert to %s at %s line %d\n", type_type_name, op_cur->file, op_cur->line);
                        
                        return;
                      }

                      if (sub->op_types->length >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                        SPVM_yyerror_format(compiler, "Too many types at %s line %d\n", op_cur->file, op_cur->line);
                      }
                      op_type->uv.type->sub_rel_id = sub->op_types->length;

                      if (sub->op_types->length >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                        SPVM_yyerror_format(compiler, "Too many types at %s line %d\n", op_cur->file, op_cur->line);
                      }
                      op_type->uv.type->sub_rel_id = sub->op_types->length;

                      SPVM_LIST_push(sub->op_types, op_type);
                    }
                    break;
                  }
                  
                  // [END]Postorder traversal position
                  
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
            SPVM_LIST_free(op_my_stack);
            SPVM_LIST_free(block_my_base_stack);
            SPVM_LIST_free(op_switch_stack);
          }
          
          // Create temporary variables for not assigned values
          if (!sub->have_native_desc) {
            // Run OPs
            SPVM_OP* op_base = SPVM_OP_get_op_block_from_op_sub(compiler, op_sub);
            SPVM_OP* op_cur = op_base;
            _Bool finish = 0;
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
                      case SPVM_OP_C_ID_ARRAY_ACCESS:
                      case SPVM_OP_C_ID_SWITCH_CONDITION:
                      case SPVM_OP_C_ID_ARRAY_FIELD_ACCESS:
                        create_tmp_var = 1;
                        break;
                      case SPVM_OP_C_ID_CONSTANT: {
                        if (SPVM_TYPE_is_numeric(compiler, tmp_var_type) && op_cur->flag != SPVM_OP_C_FLAG_CONSTANT_CASE) {
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
                    SPVM_OP* op_var_tmp = SPVM_OP_new_op_var_tmp(compiler, op_sub, tmp_var_type, op_cur->file, op_cur->line);
                    
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

          assert(sub->file_name);
          
          // Add op my if need
          if (sub->op_package->uv.package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE) {
            int32_t arg_index;
            for (arg_index = 0; arg_index < sub->op_args->length; arg_index++) {
              SPVM_OP* op_arg = SPVM_LIST_fetch(sub->op_args, arg_index);
              SPVM_LIST_push(sub->op_mys, op_arg);
            }
          }
          
          // Resolve my var id
          {
            int32_t my_index;
            int32_t my_var_id = 0;
            for (my_index = 0; my_index < sub->op_mys->length; my_index++) {
              SPVM_OP* op_my = SPVM_LIST_fetch(sub->op_mys, my_index);
              SPVM_MY* my = op_my->uv.my;
              SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_my);
              
              int32_t width = SPVM_TYPE_get_width(compiler, type);
              if (my_var_id + (width - 1) > SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
                SPVM_yyerror_format(compiler, "Too many variable declarations at %s line %d\n", op_my->file, op_my->line);
              }
              my->var_id = my_var_id;
              my_var_id += width;
            }
          }

          // Add more information for opcode building
          if (!sub->have_native_desc) {
            // Block stack
            SPVM_LIST* op_block_stack = SPVM_LIST_new(0);
            
            // Run OPs
            SPVM_OP* op_base = SPVM_OP_get_op_block_from_op_sub(compiler, op_sub);
            SPVM_OP* op_cur = op_base;
            _Bool finish = 0;
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
                    case SPVM_OP_C_ID_MY: {
                      SPVM_MY* my = op_cur->uv.my;
                      
                      SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_cur);
                      _Bool type_is_value_t = SPVM_TYPE_is_value_t(compiler, type);
                      
                      if (SPVM_TYPE_is_object(compiler, type) && !type_is_value_t) {
                        SPVM_OP* op_block_current = SPVM_LIST_fetch(op_block_stack, op_block_stack->length - 1);
                        op_block_current->uv.block->have_object_var_decl = 1;
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
  printf("\n[Basic types]\n");
  SPVM_DUMPER_dump_basic_types(compiler, compiler->basic_types);
  
  printf("\n[Packages]\n");
  SPVM_DUMPER_dump_packages(compiler, compiler->op_packages);
#endif
}

_Bool SPVM_OP_CHECKER_has_interface(SPVM_COMPILER* compiler, SPVM_PACKAGE* package, SPVM_PACKAGE* interface) {
  (void)compiler;
  
  // When left package is interface, right package have all methods which left package have
  assert(interface->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE);
  assert(!(package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE));
  
  SPVM_LIST* op_subs_interface = interface->op_subs;
  SPVM_LIST* op_subs_package = package->op_subs;
  
  int32_t has_interface_cache = (intptr_t)SPVM_HASH_fetch(package->has_interface_cache_symtable, interface->op_name->uv.name, strlen(interface->op_name->uv.name));
  
  int32_t is_cached = has_interface_cache & 1;
  int32_t has_interface;
  if (is_cached) {
    has_interface = has_interface_cache & 2;
  }
  else {
    has_interface = 1;
    
    {
      int32_t sub_index_interface;
      for (sub_index_interface = 0; sub_index_interface < op_subs_interface->length; sub_index_interface++) {
        SPVM_OP* op_sub_interface = SPVM_LIST_fetch(op_subs_interface, sub_index_interface);
        SPVM_SUB* sub_interface = op_sub_interface->uv.sub;
        assert(sub_interface->call_type_id == SPVM_SUB_C_CALL_TYPE_ID_METHOD);
        
        _Bool found = 0;
        {
          int32_t sub_index_package;
          for (sub_index_package = 0; sub_index_package < op_subs_package->length; sub_index_package++) {
            SPVM_OP* op_sub_package = SPVM_LIST_fetch(op_subs_package, sub_index_package);
            SPVM_SUB* sub_package = op_sub_package->uv.sub;
            
            if (strcmp(sub_interface->signature, sub_package->signature) == 0) {
              found = 1;
            }
          }
        }
        if (!found) {
          has_interface = 0;
          break;
        }
      }
    }
    
    // 1 bit : is cached
    // 2 bit : has interface
    int32_t new_has_interface_cache = 0;
    new_has_interface_cache |= 1;
    if (has_interface) {
      new_has_interface_cache |= 2;
    }
    
    SPVM_HASH_insert(package->has_interface_cache_symtable, interface->op_name->uv.name, strlen(interface->op_name->uv.name), (void*)(intptr_t)new_has_interface_cache);
  }
  
  return has_interface;
}

_Bool SPVM_OP_CHECKER_can_assign(SPVM_COMPILER* compiler, int32_t assign_to_basic_type_id, int32_t assign_to_type_dimension, int32_t assign_from_basic_type_id, int32_t assign_from_type_dimension) {
  
  if (assign_from_type_dimension == 0 && assign_from_basic_type_id == SPVM_BASIC_TYPE_C_ID_UNDEF) {
    return 1;
  }
  
  _Bool can_assign;
  
  // Same type
  if (assign_to_basic_type_id == assign_from_basic_type_id && assign_to_type_dimension == assign_from_type_dimension) {
    can_assign = 1;
  }
  // Different type
  else {
    // To dimension is greater than from dimension
    if (assign_to_type_dimension > assign_from_type_dimension) {
      can_assign = 0;
    }
    // To dimension is less than or equal to from dimension
    else if (assign_to_type_dimension <= assign_from_type_dimension) {
      
      // To basic type is any object
      if (assign_to_basic_type_id == SPVM_BASIC_TYPE_C_ID_ANY_OBJECT) {
        if (assign_from_type_dimension == 0) {
          SPVM_BASIC_TYPE* assign_from_basic_type = SPVM_LIST_fetch(compiler->basic_types, assign_from_basic_type_id);
          SPVM_OP* assign_from_basic_type_op_package = SPVM_HASH_fetch(compiler->op_package_symtable, assign_from_basic_type->name, strlen(assign_from_basic_type->name));
          SPVM_PACKAGE* package_assign_from_base = assign_from_basic_type_op_package->uv.package;
          if (package_assign_from_base->category == SPVM_PACKAGE_C_CATEGORY_VALUE_T) {
            can_assign = 0;
          }
          else {
            can_assign = 1;
          }
        }
        else {
          can_assign = 1;
        }
      }
      else {
        if (assign_to_type_dimension != assign_from_type_dimension) {
          can_assign = 0;
        }
        // Same dimension
        else {
          // Same base type
          if (assign_to_basic_type_id == assign_from_basic_type_id) {
            can_assign = 1;
          }
          // Different base type
          else {
            // At least one base type is number
            if ((assign_to_basic_type_id >= SPVM_BASIC_TYPE_C_ID_BYTE && assign_to_basic_type_id <= SPVM_BASIC_TYPE_C_ID_DOUBLE)
              || (assign_from_basic_type_id >= SPVM_BASIC_TYPE_C_ID_BYTE && assign_from_basic_type_id <= SPVM_BASIC_TYPE_C_ID_DOUBLE))
            {
              can_assign = 0;
            }
            else {
              SPVM_BASIC_TYPE* assign_to_basic_type = SPVM_LIST_fetch(compiler->basic_types, assign_to_basic_type_id);
              SPVM_BASIC_TYPE* assign_from_basic_type = SPVM_LIST_fetch(compiler->basic_types, assign_from_basic_type_id);
              
              SPVM_OP* assign_to_basic_type_op_package = SPVM_HASH_fetch(compiler->op_package_symtable, assign_to_basic_type->name, strlen(assign_to_basic_type->name));
              SPVM_OP* assign_from_basic_type_op_package = SPVM_HASH_fetch(compiler->op_package_symtable, assign_from_basic_type->name, strlen(assign_from_basic_type->name));
              
              SPVM_PACKAGE* package_assign_to_base = assign_to_basic_type_op_package->uv.package;
              SPVM_PACKAGE* package_assign_from_base = assign_from_basic_type_op_package->uv.package;
              
              // Left base type is interface
              if (package_assign_to_base->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE) {
                can_assign = SPVM_OP_CHECKER_has_interface(compiler, package_assign_from_base, package_assign_to_base);
              }
              else {
                can_assign = 0;
              }
            }
          }
        }
      }
    }
  }
  
  return can_assign;
}

SPVM_OP* SPVM_OP_CHECKER_check_and_convert_type(SPVM_COMPILER* compiler, SPVM_OP* op_assign_to, SPVM_OP* op_assign_from) {
  SPVM_TYPE* assign_to_type = SPVM_OP_get_type(compiler, op_assign_to);
  SPVM_TYPE* assign_from_type = SPVM_OP_get_type(compiler, op_assign_from);
  
  SPVM_OP* op_out = NULL;
  
  // Can't assign undef to numeric value
  if (SPVM_TYPE_is_numeric(compiler, assign_to_type) && op_assign_from->id == SPVM_OP_C_ID_UNDEF) {
    SPVM_yyerror_format(compiler, "Can't convert undef to numeric type at %s line %d\n", op_assign_to->file, op_assign_to->line);
  }
  else {
    // Numeric type check
    if (SPVM_TYPE_is_numeric(compiler, assign_to_type) && SPVM_TYPE_is_numeric(compiler, assign_from_type)) {
      int32_t do_convert = 0;
      if (assign_to_type->basic_type->id > assign_from_type->basic_type->id) {
        do_convert = 1;
      }
      // Narrowng convetion only when constant is in range
      else if (assign_to_type->basic_type->id < assign_from_type->basic_type->id) {
        int32_t compile_error = 0;
        if (op_assign_from->id == SPVM_OP_C_ID_CONSTANT) {
          int32_t compile_error = 0;
          SPVM_CONSTANT* constant = op_assign_from->uv.constant;
          int64_t constant_value;
          if ((constant->type->dimension == 0 && constant->type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT)
            || (constant->type->dimension == 0 && constant->type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG))
          {
            if ((constant->type->dimension == 0 && constant->type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT)) {
              constant_value = constant->value.ival;
            }
            else if ((constant->type->dimension == 0 && constant->type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG)) {
              constant_value = constant->value.lval;
            }
            
            if ((assign_to_type->dimension == 0 && assign_to_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE)) {
              if (!(constant_value >= INT8_MIN && constant_value <= INT8_MAX)) {
                compile_error = 1;
              }
            }
            else if ((assign_to_type->dimension == 0 && assign_to_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT)) {
              if (!(constant_value >= INT16_MIN && constant_value <= INT16_MAX)) {
                compile_error = 1;
              }
            }
            else if ((assign_to_type->dimension == 0 && assign_to_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT)) {
              if (!(constant_value >= INT32_MIN && constant_value <= INT32_MAX)) {
                compile_error = 1;
              }
            }
            else {
              compile_error = 1;
            }
          }
          else {
            compile_error = 1;
          }
        }
        else {
          compile_error = 1;
        }
        
        if (compile_error) {
          SPVM_yyerror_format(compiler, "Can't apply narrowing convertion at %s line %d\n", op_assign_from->file, op_assign_from->line);
        }
        else {
          do_convert = 1;
        }
      }
      
      if (do_convert) {
        SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_assign_from);
        
        SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, op_assign_from->file, op_assign_from->line);
        SPVM_OP* op_dist_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_assign_from->file, op_assign_from->line);
        op_dist_type->uv.type = assign_to_type;
        SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_assign_from);
        
        SPVM_OP_replace_op(compiler, op_stab, op_convert);

        op_convert->is_assigned_to_var = op_convert->first->is_assigned_to_var;
        
        op_convert->first->is_assigned_to_var = 0;
        
        op_out = op_convert;
      }
    }
    else {
      if ((assign_to_type->dimension == 1 && assign_to_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) && SPVM_TYPE_is_numeric(compiler, assign_from_type)) {
        // Convert numeric type to string
      }
      // object type check
      else {
        _Bool can_assign = SPVM_OP_CHECKER_can_assign(
          compiler, assign_to_type->basic_type->id, assign_to_type->dimension, assign_from_type->basic_type->id,  assign_from_type->dimension);
        if (!can_assign) {
          SPVM_yyerror_format(compiler, "Imcompatible object convertion at %s line %d\n", op_assign_from->file, op_assign_from->line);
        }
        // Const check
        if (!assign_to_type->is_const && assign_from_type->is_const) {
          SPVM_yyerror_format(compiler, "Can't assign const type to no const type at %s line %d\n", op_assign_from->file, op_assign_from->line);
        }
      }
    }
  }
  
  if (!op_out) {
    op_out = op_assign_from;
  }
  
  return op_out;
}

void SPVM_OP_CHECKER_check_types(SPVM_COMPILER* compiler) {

  SPVM_LIST* op_types = compiler->op_types;
  
  // Resolve types
  {
    int32_t i;
    for (i = 0; i < op_types->length; i++) {
      SPVM_OP* op_type = SPVM_LIST_fetch(op_types, i);
      
      SPVM_TYPE* type = op_type->uv.type;
      
      // Default core type is ok
      if (type->basic_type->id == SPVM_BASIC_TYPE_C_ID_VOID
        || (type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_BYTE && type->basic_type->id <= SPVM_BASIC_TYPE_C_ID_DOUBLE)
        || type->basic_type->id == SPVM_BASIC_TYPE_C_ID_ANY_OBJECT)
      {
        // Nothing
      }
      else {
        const char* basic_type_name = type->basic_type->name;
        
        // Package
        SPVM_HASH* op_package_symtable = compiler->op_package_symtable;
        SPVM_OP* op_found_package = SPVM_HASH_fetch(op_package_symtable, basic_type_name, strlen(basic_type_name));
        
        if (op_found_package) {
          // Nothing
        }
        else {
          SPVM_yyerror_format(compiler, "Unknown package \"%s\" at %s line %d\n", basic_type_name, op_type->file, op_type->line);
          
          return;
        }
      }
    }
  }
}

void SPVM_OP_CHECKER_resolve_call_sub(SPVM_COMPILER* compiler, SPVM_OP* op_call_sub, SPVM_OP* op_package_current) {
  
  SPVM_CALL_SUB* call_sub = op_call_sub->uv.call_sub;
  
  if (call_sub->sub) {
    return;
  }
  
  SPVM_OP* found_op_sub;
  
  const char* sub_name = call_sub->op_name->uv.name;
  // $obj->sub_name
  if (call_sub->call_type_id == SPVM_SUB_C_CALL_TYPE_ID_METHOD) {
    SPVM_TYPE* type = SPVM_OP_get_type(compiler, call_sub->op_invocant);
    const char* basic_type_name = type->basic_type->name;
    const char* sub_abs_name = SPVM_OP_create_abs_name(compiler, basic_type_name, sub_name);
    
    found_op_sub= SPVM_HASH_fetch(
      compiler->op_sub_symtable,
      sub_abs_name,
      strlen(sub_abs_name)
    );
  }
  else {
    // Package->sub_name
    if (call_sub->op_invocant) {
      const char* package_name = call_sub->op_invocant->uv.type->basic_type->name;
      const char* sub_abs_name = SPVM_OP_create_abs_name(compiler, package_name, sub_name);
      found_op_sub= SPVM_HASH_fetch(
        compiler->op_sub_symtable,
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
      found_op_sub= SPVM_HASH_fetch(
        compiler->op_sub_symtable,
        sub_abs_name,
        strlen(sub_abs_name)
      );
      
      // Search SPVM::CORE
      if (!found_op_sub) {
        sub_abs_name = SPVM_OP_create_abs_name(compiler, "SPVM::CORE", sub_name);
        
        found_op_sub= SPVM_HASH_fetch(
          compiler->op_sub_symtable,
          sub_abs_name,
          strlen(sub_abs_name)
        );
      }
    }
  }
  
  if (found_op_sub) {
    call_sub->sub = found_op_sub->uv.sub;
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
  SPVM_OP* op_package = SPVM_HASH_fetch(compiler->op_package_symtable, invoker_type->basic_type->name, strlen(invoker_type->basic_type->name));
  SPVM_PACKAGE* package = op_package->uv.package;
  const char* field_name = op_name->uv.name;
  
  SPVM_OP* found_op_field = SPVM_HASH_fetch(
    package->op_field_symtable,
    field_name,
    strlen(field_name)
  );
  if (found_op_field) {
    op_field_access->uv.field_access->field = found_op_field->uv.field;
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
  
  SPVM_OP* op_package_var = SPVM_HASH_fetch(compiler->op_package_var_symtable, abs_name, strlen(abs_name));
  
  if (op_package_var) {
    op_package_var_access->uv.package_var_access->op_package_var = op_package_var;
  }
}

