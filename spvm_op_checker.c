#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <ctype.h>


#include "spvm_compiler.h"
#include "spvm_dynamic_array.h"
#include "spvm_hash.h"
#include "spvm_compiler_allocator.h"
#include "spvm_yacc_util.h"
#include "spvm_op.h"
#include "spvm_sub.h"
#include "spvm_constant.h"
#include "spvm_field.h"
#include "spvm_my.h"
#include "spvm_var.h"
#include "spvm_enumeration_value.h"
#include "spvm_type.h"
#include "spvm_enumeration.h"
#include "spvm_package.h"
#include "spvm_call_field.h"
#include "spvm_call_sub.h"
#include "spvm_type.h"
#include "spvm_switch_info.h"
#include "spvm_limit.h"
#include "spvm_sub_check_info.h"
#include "spvm_our.h"
#include "spvm_package_var.h"
#include "spvm_undef.h"

SPVM_OP* SPVM_OP_CHECKEKR_new_op_var_tmp(SPVM_COMPILER* compiler, SPVM_TYPE* type, SPVM_SUB_CHECK_INFO* sub_check_info, const char* file, int32_t line) {

  // Create temporary variable
  // my
  SPVM_MY* my = SPVM_MY_new(compiler);

  // Temparary variable name
  char* name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, strlen("@tmp2147483647"));
  sprintf(name, "@tmp%d", sub_check_info->my_tmp_index++);
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NAME, file, line);
  op_name->uv.name = name;
  my->op_name = op_name;

  // Set type to my var
  my->op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, file, line);
  my->op_type->uv.type = type;

  // Index
  my->index = sub_check_info->op_mys->length;

  // op my
  SPVM_OP* op_my = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_MY, file, line);
  op_my->uv.my = my;

  // Add my var
  SPVM_DYNAMIC_ARRAY_push(sub_check_info->op_mys, op_my);
  SPVM_DYNAMIC_ARRAY_push(sub_check_info->op_my_stack, op_my);
  
  SPVM_OP* op_var = SPVM_OP_new_op_var_from_op_my(compiler, op_my);
  
  return op_var;
}

void SPVM_OP_CHECKER_check(SPVM_COMPILER* compiler) {
  
  SPVM_DYNAMIC_ARRAY* op_types = compiler->op_types;
  
  // Resolve String type
  SPVM_TYPE* type_string = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_CODE_STRING);
  type_string->op_package = SPVM_HASH_search(compiler->op_package_symtable, "String", strlen("String"));
  
  // Resolve types
  {
    int32_t i;
    for (i = 0; i < op_types->length; i++) {
      assert(compiler->types->length <= SPVM_LIMIT_C_TYPES);
      
      SPVM_OP* op_type = SPVM_DYNAMIC_ARRAY_fetch(op_types, i);
      
      if (compiler->types->length == SPVM_LIMIT_C_TYPES) {
        SPVM_yyerror_format(compiler, "too many types at %s line %d\n", op_type->file, op_type->line);
        compiler->fatal_error = 1;
        return;
      }
      
      SPVM_TYPE* type = op_type->uv.type;
      
      const char* base_name = SPVM_TYPE_get_base_name(compiler, type->name);
        
      // Core type or array
      if (
        SPVM_TYPE_is_array(compiler, type) || strcmp(base_name, "void") == 0 || strcmp(base_name, "byte") == 0
        || strcmp(base_name, "short") == 0 || strcmp(base_name, "int") == 0 || strcmp(base_name, "long") == 0
        || strcmp(base_name, "float") == 0 || strcmp(base_name, "double") == 0 || strcmp(base_name, "string") == 0
      )
      {
        // Nothing
      }
      else {
        // Package
        SPVM_HASH* op_package_symtable = compiler->op_package_symtable;
        SPVM_OP* op_found_package = SPVM_HASH_search(op_package_symtable, base_name, strlen(base_name));
        
        if (op_found_package) {
          // Nothing
        }
        else {
          SPVM_yyerror_format(compiler, "Unknown package \"%s\" at %s line %d\n", base_name, op_type->file, op_type->line);
          compiler->fatal_error = 1;
          return;
        }
      }
      
      // Create resolved type id
      SPVM_TYPE* found_type = SPVM_HASH_search(compiler->type_symtable, type->name, strlen(type->name));
      if (found_type) {
        op_type->uv.type = found_type;
      }
      else {
        type->code = compiler->types->length;
        
        SPVM_TYPE* new_type = SPVM_TYPE_new(compiler);
        memcpy(new_type, type, sizeof(SPVM_TYPE));
        SPVM_DYNAMIC_ARRAY_push(compiler->types, new_type);
        SPVM_HASH_insert(compiler->type_symtable, type->name, strlen(type->name), new_type);
        
        new_type->op_package = SPVM_HASH_search(compiler->op_package_symtable, type->name, strlen(type->name));
        
        op_type->uv.type = new_type;
      }
    }
  }

  // Calcurate fild byte offset and package byte size
  SPVM_DYNAMIC_ARRAY* op_packages = compiler->op_packages;
  int32_t alignment;
  if (sizeof(void*) > sizeof(int64_t)) {
    alignment = sizeof(void*);
  }
  else {
    alignment = sizeof(int64_t);
  }
  
  {
    int32_t package_pos;
    for (package_pos = 0; package_pos < op_packages->length; package_pos++) {
      SPVM_OP* op_package = SPVM_DYNAMIC_ARRAY_fetch(op_packages, package_pos);
      SPVM_PACKAGE* package = op_package->uv.package;
      SPVM_DYNAMIC_ARRAY* op_fields = package->op_fields;
      
      // Separate reference type and value type
      int32_t next_max_byte_size = alignment;
      int32_t current_byte_offset = 0;
      {
        int32_t field_pos;
        for (field_pos = 0; field_pos < op_fields->length; field_pos++) {
          SPVM_OP* op_field = SPVM_DYNAMIC_ARRAY_fetch(op_fields, field_pos);
          SPVM_FIELD* field = op_field->uv.field;
          SPVM_TYPE* field_type = field->op_type->uv.type;
          
          int32_t field_byte_size;
          switch (field_type->code) {
            case SPVM_TYPE_C_CODE_BYTE:
              field_byte_size = sizeof(int8_t);
              break;
            case SPVM_TYPE_C_CODE_SHORT:
              field_byte_size = sizeof(int16_t);
              break;
            case SPVM_TYPE_C_CODE_INT:
              field_byte_size = sizeof(int32_t);
              break;
            case SPVM_TYPE_C_CODE_LONG:
              field_byte_size = sizeof(int64_t);
              break;
            case SPVM_TYPE_C_CODE_FLOAT:
              field_byte_size = sizeof(float);
              break;
            case SPVM_TYPE_C_CODE_DOUBLE:
              field_byte_size = sizeof(double);
              break;
            default: {
              field_byte_size = sizeof(SPVM_OBJECT*);
            }
          }
          
          int32_t padding = 0;
          if (current_byte_offset % field_byte_size != 0) {
            padding = field_byte_size - (current_byte_offset % field_byte_size);
          }
          current_byte_offset += padding;
          
          if (current_byte_offset + field_byte_size <= next_max_byte_size) {
            field->byte_offset = current_byte_offset;
          }
          else {
            current_byte_offset = next_max_byte_size;
            field->byte_offset = current_byte_offset;
          }
          current_byte_offset += field_byte_size;
          if (current_byte_offset % alignment == 0) {
            next_max_byte_size += alignment;
          }
        }
      }
      if (current_byte_offset % alignment == 0) {
        package->byte_size = next_max_byte_size - alignment;
      }
      else {
        package->byte_size = next_max_byte_size;
      }
    }
  }
  
  // Resolve package
  {
    int32_t package_pos;
    for (package_pos = 0; package_pos < op_packages->length; package_pos++) {
      SPVM_OP* op_package = SPVM_DYNAMIC_ARRAY_fetch(op_packages, package_pos);
      SPVM_PACKAGE* package = op_package->uv.package;
      SPVM_DYNAMIC_ARRAY* op_fields = package->op_fields;
      
      // Calculate package byte size
      {
        int32_t field_pos;
        for (field_pos = 0; field_pos < op_fields->length; field_pos++) {
          SPVM_OP* op_field = SPVM_DYNAMIC_ARRAY_fetch(op_fields, field_pos);
          SPVM_FIELD* field = op_field->uv.field;
          field->index = field_pos;
        }
      }
    }
  }
  
  {
    int32_t sub_pos;
    for (sub_pos = 0; sub_pos < compiler->op_subs->length; sub_pos++) {
      
      SPVM_OP* op_sub = SPVM_DYNAMIC_ARRAY_fetch(compiler->op_subs, sub_pos);
      SPVM_SUB* sub = op_sub->uv.sub;
      SPVM_OP* op_package = sub->op_package;
      SPVM_PACKAGE* package = op_package->uv.package;
      
      int32_t eval_stack_length = 0;
      
      // Destructor must receive own package object
      if (sub->is_destructor) {
        // DESTROY argument must be 0
        _Bool error = 0;
        if (sub->op_args->length != 1) {
          error = 1;
        }
        else {
          SPVM_OP* op_arg = SPVM_DYNAMIC_ARRAY_fetch(sub->op_args, 0);
          SPVM_TYPE* arg_type = SPVM_OP_get_type(compiler, op_arg);
          
          if (arg_type->code != package->op_type->uv.type->code) {
            error = 1;
          }
        }
        
        if (error) {
          SPVM_yyerror_format(compiler, "DESTROY argument type must be %s\n", package->op_name->uv.name, op_sub->file, op_sub->line);
        }
      }

        
      SPVM_SUB_CHECK_INFO* sub_check_info = SPVM_SUB_CHECK_INFO_new(compiler);
      
      // Resolve lexical variable names
      if (!sub->is_native) {
        // Run OPs
        SPVM_OP* op_base = SPVM_OP_get_op_block_from_op_sub(compiler, op_sub);
        SPVM_OP* op_cur = op_base;
        _Bool finish = 0;
        while (op_cur) {
          
          if (op_cur->first) {
            op_cur = op_cur->first;
          }
          else {
            while (1) {
              // [START]Postorder traversal position
              switch (op_cur->code) {
                case SPVM_OP_C_CODE_VAR:
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
      
      // Only process normal subroutine
      if (!sub->is_native) {
        
        // Run OPs
        SPVM_OP* op_base = SPVM_OP_get_op_block_from_op_sub(compiler, op_sub);
        SPVM_OP* op_cur = op_base;
        _Bool finish = 0;
        while (op_cur) {
          // [START]Preorder traversal position
          
          switch (op_cur->code) {
            case SPVM_OP_C_CODE_SWITCH: {
              SPVM_DYNAMIC_ARRAY_push(sub_check_info->op_switch_stack, op_cur);
              break;
            }
            // Start scope
            case SPVM_OP_C_CODE_BLOCK: {
              
              int32_t block_my_base = sub_check_info->op_my_stack->length;
              int32_t* block_my_base_ptr = SPVM_COMPILER_ALLOCATOR_alloc_int(compiler, compiler->allocator);
              *block_my_base_ptr = block_my_base;
              SPVM_DYNAMIC_ARRAY_push(sub_check_info->block_my_base_stack, block_my_base_ptr);
              
              if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_LOOP) {
                SPVM_DYNAMIC_ARRAY_push(sub_check_info->loop_block_my_base_stack, block_my_base_ptr);
              }
              else if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_EVAL) {
                SPVM_DYNAMIC_ARRAY_push(sub_check_info->eval_block_my_base_stack, block_my_base_ptr);
                
                // Eval block max length
                eval_stack_length++;
                if (eval_stack_length > sub->eval_stack_max_length) {
                  sub->eval_stack_max_length = eval_stack_length;
                }
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
              switch (op_cur->code) {
                case SPVM_OP_C_CODE_NEXT: {
                  if (sub_check_info->loop_block_my_base_stack->length == 0) {
                    SPVM_yyerror_format(compiler, "next statement must be in loop block at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  break;
                }
                case SPVM_OP_C_CODE_LAST: {
                  if (sub_check_info->loop_block_my_base_stack->length == 0 && sub_check_info->op_switch_stack->length == 0) {
                    SPVM_yyerror_format(compiler, "last statement must be in loop block or switch block at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  break;
                }
                case SPVM_OP_C_CODE_SWITCH: {
                  
                  SPVM_OP* op_switch_condition = op_cur->first;
                  
                  SPVM_TYPE* term_type = SPVM_OP_get_type(compiler, op_switch_condition->first);
                  
                  // Check type
                  if (!term_type || !(term_type->code == SPVM_TYPE_C_CODE_INT)) {
                    SPVM_yyerror_format(compiler, "Switch condition need int value at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // tableswitch if the following. SWITCHRTIO is 1.5 by default
                  // 4 + range <= (3 + 2 * length) * SWITCHRTIO
                  
                  SPVM_SWITCH_INFO* switch_info = op_cur->uv.switch_info;
                  SPVM_DYNAMIC_ARRAY* op_cases = switch_info->op_cases;
                  int32_t length = op_cases->length;
                  
                  // Check case type
                  {
                    int32_t i;
                    for (i = 0; i < length; i++) {
                      SPVM_OP* op_case = SPVM_DYNAMIC_ARRAY_fetch(op_cases, i);
                      SPVM_OP* op_constant = op_case->first;

                      if (op_constant->code != SPVM_OP_C_CODE_CONSTANT) {
                        SPVM_yyerror_format(compiler, "case need constant at %s line %d\n", op_cur->file, op_cur->line);
                        compiler->fatal_error = 1;
                        return;
                      }
                      
                      SPVM_TYPE* case_value_type = SPVM_OP_get_type(compiler, op_constant);
                      
                      if (case_value_type->code != term_type->code) {
                        SPVM_yyerror_format(compiler, "case value type must be same as switch condition value type at %s line %d\n", op_case->file, op_case->line);
                        compiler->fatal_error = 1;
                        return;
                      }
                    }
                  }
                  
                  int32_t min = INT32_MAX;
                  int32_t max = INT32_MIN;
                  {
                    int32_t i;
                    for (i = 0; i < length; i++) {
                      SPVM_OP* op_case = SPVM_DYNAMIC_ARRAY_fetch(op_cases, i);
                      SPVM_OP* op_constant = op_case->first;
                      int32_t value = op_constant->uv.constant->value.int_value;
                      
                      if (value < min) {
                        min = value;
                      }
                      if (value > max) {
                        max = value;
                      }
                    }
                  }
                  
                  // double range = (double) max - (double) min;
                  // int32_t code;
                  // if (4.0 + range <= (3.0 + 2.0 * (double) length) * 1.5) {
                  //   code = SPVM_SWITCH_INFO_C_CODE_TABLE_SWITCH;
                  // }
                  // else {
                  //   code = SPVM_SWITCH_INFO_C_CODE_LOOKUP_SWITCH;
                  // }

                  int32_t code = SPVM_SWITCH_INFO_C_CODE_LOOKUP_SWITCH;
                  
                  switch_info->code = code;
                  switch_info->min = min;
                  switch_info->max = max;
                  
                  SPVM_DYNAMIC_ARRAY_pop(sub_check_info->op_switch_stack);
                  
                  break;
                }
                case SPVM_OP_C_CODE_CASE: {
                  if (sub_check_info->op_switch_stack->length > 0) {
                    SPVM_OP* op_switch = SPVM_DYNAMIC_ARRAY_fetch(sub_check_info->op_switch_stack, sub_check_info->op_switch_stack->length - 1);
                    SPVM_SWITCH_INFO* switch_info = op_switch->uv.switch_info;
                    if (switch_info->op_cases->length == SPVM_LIMIT_C_CASES) {
                      SPVM_yyerror_format(compiler, "Too many case statements at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }

                    SPVM_DYNAMIC_ARRAY_push(switch_info->op_cases, op_cur);
                  }
                  break;
                }
                case SPVM_OP_C_CODE_DEFAULT: {
                  if (sub_check_info->op_switch_stack->length > 0) {
                    SPVM_OP* op_switch = SPVM_DYNAMIC_ARRAY_fetch(sub_check_info->op_switch_stack, sub_check_info->op_switch_stack->length - 1);
                    SPVM_SWITCH_INFO* switch_info = op_switch->uv.switch_info;
                    
                    if (switch_info->op_default) {
                      SPVM_yyerror_format(compiler, "multiple default is forbidden at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                    else {
                      switch_info->op_default = op_cur;
                    }
                  }
                  break;
                }
                case SPVM_OP_C_CODE_BOOL: {
                  SPVM_OP* op_first = op_cur->first;
                  
                  // undef
                  if (op_first->code == SPVM_OP_C_CODE_UNDEF) {
                    
                    SPVM_OP* op_false = SPVM_OP_new_op_constant_int(compiler, 0, op_first->file, op_first->line);
                    
                    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_first);
                    
                    SPVM_OP_replace_op(compiler, op_stab, op_false);
                    
                    op_cur = op_false;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_EQ: {
                  SPVM_OP* op_first = op_cur->first;
                  SPVM_OP* op_last = op_cur->last;
                  
                  // term == term
                  if (op_first->code == SPVM_OP_C_CODE_UNDEF && op_last->code == SPVM_OP_C_CODE_UNDEF) {
                    
                    SPVM_OP* op_true = SPVM_OP_new_op_constant_int(compiler, 1, op_first->file, op_first->line);
                    SPVM_OP* op_bool = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BOOL, op_first->file, op_first->line);
                    
                    SPVM_OP_insert_child(compiler, op_bool, op_bool->last, op_true);
                    
                    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                    
                    SPVM_OP_replace_op(compiler, op_stab, op_bool);
                    
                    op_cur = op_true;
                  }
                  else if (op_first->code != SPVM_OP_C_CODE_UNDEF && op_last->code != SPVM_OP_C_CODE_UNDEF) {
                    SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                    SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                    
                    // numeric == numeric
                    if (SPVM_TYPE_is_numeric(compiler, first_type) && SPVM_TYPE_is_numeric(compiler, last_type)) {
                      if (first_type->code != last_type->code) {
                        SPVM_yyerror_format(compiler, "== operator two operands must be same type at %s line %d\n", op_cur->file, op_cur->line);
                        compiler->fatal_error = 1;
                        return;
                      }
                    }
                    // numeric == OBJ
                    else if (SPVM_TYPE_is_numeric(compiler, first_type)) {
                      SPVM_yyerror_format(compiler, "== left value must be object at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                    // OBJ == numeric
                    else if (SPVM_TYPE_is_numeric(compiler, last_type)) {
                      SPVM_yyerror_format(compiler, "== right value must be object at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                  }
                  // term == undef
                  else if (op_first->code != SPVM_OP_C_CODE_UNDEF && op_last->code == SPVM_OP_C_CODE_UNDEF) {
                    SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                    if (SPVM_TYPE_is_numeric(compiler, first_type)) {
                      SPVM_yyerror_format(compiler, "== left value must be object at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                  }
                  // undef == term
                  else if (op_first->code == SPVM_OP_C_CODE_UNDEF && op_last->code != SPVM_OP_C_CODE_UNDEF) {
                    SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                    if (SPVM_TYPE_is_numeric(compiler, last_type)) {
                      SPVM_yyerror_format(compiler, "== right value must be object at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_NE: {
                  SPVM_OP* op_first = op_cur->first;
                  SPVM_OP* op_last = op_cur->last;

                  // term != term
                  if (op_first->code == SPVM_OP_C_CODE_UNDEF && op_last->code == SPVM_OP_C_CODE_UNDEF) {
                    
                    SPVM_OP* op_false = SPVM_OP_new_op_constant_int(compiler, 0, op_first->file, op_first->line);
                    SPVM_OP* op_bool = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BOOL, op_first->file, op_first->line);
                    
                    SPVM_OP_insert_child(compiler, op_bool, op_bool->last, op_false);
                    
                    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                    
                    SPVM_OP_replace_op(compiler, op_stab, op_bool);
                    
                    op_cur = op_false;
                  }
                  else if (op_first->code != SPVM_OP_C_CODE_UNDEF && op_last->code != SPVM_OP_C_CODE_UNDEF) {
                    SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                    SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

                    // numeric != numeric
                    if (SPVM_TYPE_is_numeric(compiler, first_type) && SPVM_TYPE_is_numeric(compiler, last_type)) {
                      if (first_type->code != last_type->code) {
                        SPVM_yyerror_format(compiler, "!= operator two operands must be same type at %s line %d\n", op_cur->file, op_cur->line);
                        compiler->fatal_error = 1;
                        return;
                      }
                    }
                    // numeric != OBJ
                    else if (SPVM_TYPE_is_numeric(compiler, first_type)) {
                      SPVM_yyerror_format(compiler, "!= left value must be object at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                    // OBJ != numeric
                    else if (SPVM_TYPE_is_numeric(compiler, last_type)) {
                      SPVM_yyerror_format(compiler, "!= right value must be object at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                  }
                  // term != undef
                  else if (op_first->code != SPVM_OP_C_CODE_UNDEF && op_last->code == SPVM_OP_C_CODE_UNDEF) {
                    SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);

                    if (SPVM_TYPE_is_numeric(compiler, first_type)) {
                      SPVM_yyerror_format(compiler, "!= left value must be object at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                  }
                  // undef != term
                  else if (op_first->code == SPVM_OP_C_CODE_UNDEF && op_last->code != SPVM_OP_C_CODE_UNDEF) {
                    SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

                    if (SPVM_TYPE_is_numeric(compiler, last_type)) {
                      SPVM_yyerror_format(compiler, "!= right value must be object at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_LT: {

                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                  
                  // undef check
                  if (!first_type) {
                    SPVM_yyerror_format(compiler, "< left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  if (!last_type) {
                    SPVM_yyerror_format(compiler, "< right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Can receive only numeric type
                  if (SPVM_TYPE_is_object(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "< left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  if (SPVM_TYPE_is_object(compiler, last_type)) {
                    SPVM_yyerror_format(compiler, "< right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }

                  if (first_type->code != last_type->code) {
                    SPVM_yyerror_format(compiler, "< operator two operands must be same type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }

                  break;
                }
                case SPVM_OP_C_CODE_LE: {

                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

                  // undef check
                  if (!first_type) {
                    SPVM_yyerror_format(compiler, "<= left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  if (!last_type) {
                    SPVM_yyerror_format(compiler, "<= right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                                  
                  // Can receive only numeric type
                  if (SPVM_TYPE_is_object(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "<= left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  if (SPVM_TYPE_is_object(compiler, last_type)) {
                    SPVM_yyerror_format(compiler, "<= right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }

                  if (first_type->code != last_type->code) {
                    SPVM_yyerror_format(compiler, "<= operator two operands must be same type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_GT: {

                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

                  // undef check
                  if (!first_type) {
                    SPVM_yyerror_format(compiler, "> left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  if (!last_type) {
                    SPVM_yyerror_format(compiler, "> right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Can receive only numeric type
                  if (SPVM_TYPE_is_object(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "> left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  if (SPVM_TYPE_is_object(compiler, last_type)) {
                    SPVM_yyerror_format(compiler, "> right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }

                  if (first_type->code != last_type->code) {
                    SPVM_yyerror_format(compiler, "> operator two operands must be same type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_GE: {

                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

                  // undef check
                  if (!first_type) {
                    SPVM_yyerror_format(compiler, "<= left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  if (!last_type) {
                    SPVM_yyerror_format(compiler, "<= right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Can receive only numeric type
                  if (SPVM_TYPE_is_numeric(compiler, first_type) && SPVM_TYPE_is_object(compiler, last_type)) {
                    SPVM_yyerror_format(compiler, ">= left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  if (SPVM_TYPE_is_object(compiler, first_type) && SPVM_TYPE_is_numeric(compiler, last_type)) {
                    SPVM_yyerror_format(compiler, ">= right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }

                  if (first_type->code != last_type->code) {
                    SPVM_yyerror_format(compiler, ">= operator two operands must be same type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_LEFT_SHIFT: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                  
                  // Can receive only numeric type
                  if (!SPVM_TYPE_is_integral(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "<< operator left value must be integral at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  if (last_type->code != SPVM_TYPE_C_CODE_INT) {
                    SPVM_yyerror_format(compiler, "<< operator right value must be int at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_RIGHT_SHIFT: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                  
                  // Can receive only numeric type
                  if (!SPVM_TYPE_is_integral(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, ">> operator left value must be integral at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  if (last_type->code != SPVM_TYPE_C_CODE_INT) {
                    SPVM_yyerror_format(compiler, ">> operator right value must be int at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_RIGHT_SHIFT_UNSIGNED: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                  
                  // Can receive only numeric type
                  if (!SPVM_TYPE_is_integral(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, ">>> operator left value must be integral at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  if (last_type->code > SPVM_TYPE_C_CODE_INT) {
                    SPVM_yyerror_format(compiler, ">>> operator right value must be int at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_NEW: {
                  if (op_cur->first->code == SPVM_OP_C_CODE_TYPE) {
                    SPVM_OP* op_type = op_cur->first;
                    SPVM_TYPE* type = op_type->uv.type;
                    
                    if (SPVM_TYPE_is_array(compiler, type)) {
                      SPVM_OP* op_index_term = op_type->last;
                      SPVM_TYPE* index_type = SPVM_OP_get_type(compiler, op_index_term);
                      
                      if (!index_type) {
                        SPVM_yyerror_format(compiler, "new operator can't create array which don't have length \"%s\" at %s line %d\n", type->name, op_cur->file, op_cur->line);
                        compiler->fatal_error = 1;
                        return;
                      }
                      else if (index_type->code != SPVM_TYPE_C_CODE_INT) {
                        SPVM_yyerror_format(compiler, "new operator can't create array which don't have int length \"%s\" at %s line %d\n", type->name, op_cur->file, op_cur->line);
                        compiler->fatal_error = 1;
                        return;
                      }
                    }
                    else {
                      if (SPVM_TYPE_is_numeric(compiler, type)) {
                        SPVM_yyerror_format(compiler,
                          "new operator can't receive numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        compiler->fatal_error = 1;
                        return;
                      }
                      else if (strcmp(type->name, op_package->uv.package->op_name->uv.name) != 0) {
                        SPVM_yyerror_format(compiler,
                          "new operator is private at %s line %d\n", op_cur->file, op_cur->line);
                      }
                    }
                  }
                  else if (op_cur->first->code == SPVM_OP_C_CODE_CONSTANT) {
                    // Constant string
                  }
                  else {
                    assert(0);
                  }

                  break;
                }
                case SPVM_OP_C_CODE_BIT_XOR: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                  
                  // Can receive only numeric type
                  if (first_type->code >= SPVM_TYPE_C_CODE_FLOAT || last_type->code >= SPVM_TYPE_C_CODE_FLOAT) {
                    SPVM_yyerror_format(compiler,
                      "& operator can receive only integral type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_BIT_OR: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                  
                  // Can receive only numeric type
                  if (first_type->code >= SPVM_TYPE_C_CODE_FLOAT || last_type->code >= SPVM_TYPE_C_CODE_FLOAT) {
                    SPVM_yyerror_format(compiler,
                      "& operator can receive only integral type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_BIT_AND: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                  
                  // Can receive only numeric type
                  if (first_type->code >= SPVM_TYPE_C_CODE_FLOAT || last_type->code >= SPVM_TYPE_C_CODE_FLOAT) {
                    SPVM_yyerror_format(compiler,
                      "& operator can receive only integral type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_ARRAY_LENGTH: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  
                  // First value must be array
                  if (!SPVM_TYPE_is_array(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "right of @ or len must be array at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_ARRAY_ELEM: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                  
                  // Left value must be array
                  if (!SPVM_TYPE_is_array(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "left value must be array at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Right value must be integer
                  if (last_type->code != SPVM_TYPE_C_CODE_INT) {
                    SPVM_yyerror_format(compiler, "array index must be int at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_ASSIGN: {
                  
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                  
                  // Type inference
                  if (op_cur->first->code == SPVM_OP_C_CODE_VAR) {
                    if (!first_type) {
                      first_type = last_type;
                    }
                    
                    if (first_type) {
                      SPVM_OP* op_var = op_cur->first;
                      SPVM_MY* my = op_var->uv.var->op_my->uv.my;
                      my->op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_var->file, op_var->line);
                      my->op_type->uv.type = first_type;
                    }
                  }
                  
                  // Type can't be detected
                  if (!first_type) {
                    SPVM_yyerror_format(compiler, "Type can't be detected at %s line %d\n", op_cur->first->file, op_cur->first->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Can't assign undef to numeric value
                  if (SPVM_TYPE_is_numeric(compiler, first_type) && op_cur->last->code == SPVM_OP_C_CODE_UNDEF) {
                    SPVM_yyerror_format(compiler, "Can't assign undef to numeric type at %s line %d\n", op_cur->first->file, op_cur->first->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Copy left type to undef
                  if (op_cur->last->code == SPVM_OP_C_CODE_UNDEF) {
                    last_type = first_type;
                    op_cur->last->uv.undef->type = last_type;
                  }
                  
                  // Invalid if left type is different to right value
                  if (first_type->code != last_type->code) {
                    SPVM_yyerror_format(compiler, "Invalid type value is assigned at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  if (op_cur->first->code == SPVM_OP_C_CODE_VAR) {
                    if (op_cur->last->code == SPVM_OP_C_CODE_CONCAT_STRING) {
                      int32_t index_out = SPVM_OP_get_my_index(compiler, op_cur->first);
                      
                      if (op_cur->last->first->code == SPVM_OP_C_CODE_VAR) {
                        int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_cur->last->first);
                        if (index_out == index_in1) {
                          op_cur->last->first->uv.var->create_tmp_var = 1;
                        }
                      }
                      
                      if (op_cur->last->last->code == SPVM_OP_C_CODE_VAR) {
                        int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_cur->last->last);
                        if (index_out == index_in2) {
                          op_cur->last->last->uv.var->create_tmp_var = 1;
                        }
                      }
                    }
                    else if (op_cur->last->code == SPVM_OP_C_CODE_CALL_SUB) {
                      int32_t index_out = SPVM_OP_get_my_index(compiler, op_cur->first);
                      
                      // Push args
                      SPVM_OP* op_args =op_cur->last->last;
                      SPVM_OP* op_arg = op_args->first;
                      while ((op_arg = SPVM_OP_sibling(compiler, op_arg))) {
                        if (op_arg->code == SPVM_OP_C_CODE_VAR) {
                          int32_t index_arg = SPVM_OP_get_my_index(compiler, op_arg);
                          if (index_arg == index_out) {
                            op_arg->uv.var->create_tmp_var = 1;
                            break;
                          }
                        }
                      }
                    }
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_RETURN: {
                  
                  SPVM_OP* op_term = op_cur->first;
                  
                  if (op_term) {
                    SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_term);
                    SPVM_TYPE* sub_return_type = SPVM_OP_get_type(compiler, sub->op_return_type);
                    
                    _Bool is_invalid = 0;
                    
                    
                    // Undef
                    if (op_term->code == SPVM_OP_C_CODE_UNDEF) {
                      if (sub->op_return_type->uv.type->code == SPVM_TYPE_C_CODE_VOID) {
                        is_invalid = 1;
                      }
                      else {
                        if (SPVM_TYPE_is_numeric(compiler, sub_return_type)) {
                          is_invalid = 1;
                        }
                        else {
                          op_term->uv.undef->type = sub_return_type;
                        }
                      }
                    }
                    // Normal
                    else if (op_term) {
                      if (first_type->code != sub_return_type->code) {
                        is_invalid = 1;
                      }
                    }
                    // Empty
                    else {
                      if (sub->op_return_type->uv.type->code != SPVM_TYPE_C_CODE_VOID) {
                        is_invalid = 1;
                      }
                    }
                    
                    if (is_invalid) {
                      SPVM_yyerror_format(compiler, "Invalid return type at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                  }
                  break;
                }
                case SPVM_OP_C_CODE_NEGATE: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  
                  // Must be numeric type
                  if (SPVM_TYPE_is_object(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "- operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_COMPLEMENT: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  
                  // Must be numeric type
                  if (!SPVM_TYPE_is_integral(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "~ operator right value must be integral type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_PLUS: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  
                  // Must be numeric type
                  if (SPVM_TYPE_is_object(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "+ operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_ADD: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                  
                  // Left value must not be undef
                  if (!first_type) {
                    SPVM_yyerror_format(compiler, "+ operator left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Right value Must not be undef
                  if (!last_type) {
                    SPVM_yyerror_format(compiler, "+ operator right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Must be same type
                  if (first_type->code != last_type->code) {
                    SPVM_yyerror_format(compiler, "+ operator left and right value must be same at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                                                  
                  // Value must be numeric type
                  if (SPVM_TYPE_is_object(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "+ operator left and right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_SUBTRACT: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                  
                  // Left value must not be undef
                  if (!first_type) {
                    SPVM_yyerror_format(compiler, "- operator left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Right value Must not be undef
                  if (!last_type) {
                    SPVM_yyerror_format(compiler, "- operator right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Must be same type
                  if (first_type->code != last_type->code) {
                    SPVM_yyerror_format(compiler, "- operator left and right value must be same at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                                                  
                  // Value must be numeric type
                  if (SPVM_TYPE_is_object(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "- operator left and right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_CONCAT_STRING: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                  
                  // First value must be numeric or byte array
                  if (!(SPVM_TYPE_is_numeric(compiler, first_type) || SPVM_TYPE_is_string(compiler, first_type))) {
                    SPVM_yyerror_format(compiler, ". operator left value must be numeric or string at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // First value must be numeric or byte array
                  if (!(SPVM_TYPE_is_numeric(compiler, last_type) || SPVM_TYPE_is_string(compiler, last_type))) {
                    SPVM_yyerror_format(compiler, ". operator right value must be numeric or string at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // If left type is not string, add another concat
                  /*
                    Before
                      concat_string1
                        term1
                        term2
                    After
                      concat_string1
                        concat_string2
                          new
                            ""
                          term1
                        term2
                  */
                  
                  if (!SPVM_TYPE_is_string(compiler, first_type)) {
                    SPVM_OP* op_concat_string1 = op_cur;
                    SPVM_OP* op_concat_string2 = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONCAT_STRING, op_concat_string1->file, op_concat_string1->line);


                    SPVM_OP* op_term1 = op_concat_string1->first;
                    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term1);
                    
                    // Empty string
                    SPVM_OP* op_constant_empty_string = SPVM_OP_new_op_constant_byte_array_string(compiler, "", op_concat_string1->file, op_concat_string1->line);
                    SPVM_OP* op_build_constant = SPVM_OP_build_constant(compiler, op_constant_empty_string);
                    
                    SPVM_OP_insert_child(compiler, op_concat_string2, op_concat_string2->last, op_build_constant);
                    SPVM_OP_insert_child(compiler, op_concat_string2, op_concat_string2->last, op_term1);
                    
                    SPVM_OP_replace_op(compiler, op_stab, op_concat_string2);
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_MULTIPLY: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                  
                  // Left value must not be undef
                  if (!first_type) {
                    SPVM_yyerror_format(compiler, "* operator left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Right value Must not be undef
                  if (!last_type) {
                    SPVM_yyerror_format(compiler, "* operator right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Must be same type
                  if (first_type->code != last_type->code) {
                    SPVM_yyerror_format(compiler, "* operator left and right value must be same at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                                                  
                  // Value must be numeric type
                  if (SPVM_TYPE_is_object(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "* operator left and right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_DIVIDE: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                  
                  // Left value must not be undef
                  if (!first_type) {
                    SPVM_yyerror_format(compiler, "/ operator left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Right value Must not be undef
                  if (!last_type) {
                    SPVM_yyerror_format(compiler, "/ operator right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Must be same type
                  if (first_type->code != last_type->code) {
                    SPVM_yyerror_format(compiler, "/ operator left and right value must be same at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                                                  
                  // Value must be numeric type
                  if (SPVM_TYPE_is_object(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "/ operator left and right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_REMAINDER: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                  
                  // Left value must not be undef
                  if (!first_type) {
                    SPVM_yyerror_format(compiler, "% operator left value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Right value Must not be undef
                  if (!last_type) {
                    SPVM_yyerror_format(compiler, "% operator right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Must be same type
                  if (first_type->code != last_type->code) {
                    SPVM_yyerror_format(compiler, "% operator left and right value must be same at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                                                  
                  // Value must be numeric type
                  if (SPVM_TYPE_is_object(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "% operator left and right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_CROAK: {
                  if (op_cur->first->code == SPVM_OP_C_CODE_UNDEF) {
                    op_cur->first->uv.undef->type = SPVM_TYPE_get_string_type(compiler);
                  }
                  else {
                    SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                    if (first_type->code != SPVM_TYPE_C_CODE_STRING) {
                      SPVM_yyerror_format(compiler, "croak argument type must be String at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                  }
                  break;
                }
                case SPVM_OP_C_CODE_PRE_INC:
                case SPVM_OP_C_CODE_POST_INC:
                case SPVM_OP_C_CODE_PRE_DEC:
                case SPVM_OP_C_CODE_POST_DEC: {
                  SPVM_OP* op_first = op_cur->first;
                  if (op_first->code != SPVM_OP_C_CODE_VAR) {
                    SPVM_yyerror_format(compiler, "invalid is_assign_left in increment at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_first);
                  
                  // Only int or long
                  if (first_type->code > SPVM_TYPE_C_CODE_LONG) {
                    SPVM_yyerror_format(compiler, "increment or decrement target must be integral at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  op_cur->first->is_assign_left = 1;
                  
                  break;
                }
                case SPVM_OP_C_CODE_LOOP: {
                  // Exchange condition and loop block to move condition to end of block
                  SPVM_OP* op_block_outer = op_cur->first;
                  
                  SPVM_OP* op_condition = op_block_outer->first->sibparent;
                  SPVM_OP* op_block_loop = op_block_outer->last;
                  
                  SPVM_OP* op_stab_condition = SPVM_OP_cut_op(compiler, op_condition);
                  SPVM_OP* op_stab_block_loop = SPVM_OP_cut_op(compiler, op_block_loop);
                  
                  SPVM_OP_replace_op(compiler, op_stab_condition, op_block_loop);
                  SPVM_OP_replace_op(compiler, op_stab_block_loop, op_condition);
                  
                  break;
                }
                // End of scope
                case SPVM_OP_C_CODE_BLOCK: {
                  // Pop block my variable base
                  assert(sub_check_info->block_my_base_stack->length > 0);
                  int32_t* block_my_base_ptr = SPVM_DYNAMIC_ARRAY_pop(sub_check_info->block_my_base_stack);
                  int32_t block_my_base = *block_my_base_ptr;
                    
                  int32_t my_stack_pop_count = sub_check_info->op_my_stack->length - block_my_base;
                  
                  {
                    int32_t i;
                    for (i = 0; i < my_stack_pop_count; i++) {
                      SPVM_DYNAMIC_ARRAY_pop(sub_check_info->op_my_stack);
                    }
                  }

                  // Pop loop block my variable base
                  if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_LOOP) {
                    assert(sub_check_info->loop_block_my_base_stack->length > 0);
                    SPVM_DYNAMIC_ARRAY_pop(sub_check_info->loop_block_my_base_stack);
                  }
                  // Pop try block my variable base
                  else if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_EVAL) {
                    assert(sub_check_info->eval_block_my_base_stack->length > 0);
                    SPVM_DYNAMIC_ARRAY_pop(sub_check_info->eval_block_my_base_stack);
                    eval_stack_length--;
                  }
                  
                  break;
                }
                // Add my var
                case SPVM_OP_C_CODE_VAR: {
                  
                  SPVM_VAR* var = op_cur->uv.var;
                  
                  // Search same name variable
                  SPVM_OP* found_op_my = NULL;
                  {
                    int32_t i;
                    for (i = sub_check_info->op_my_stack->length - 1; i >= 0; i--) {
                      SPVM_OP* op_my = SPVM_DYNAMIC_ARRAY_fetch(sub_check_info->op_my_stack, i);
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
                    compiler->fatal_error = 1;
                    return;
                  }
                  break;
                }
                case SPVM_OP_C_CODE_MY: {
                  SPVM_MY* my = op_cur->uv.my;
                  
                  // Search same name variable
                  _Bool found = 0;
                  
                  int32_t* block_my_base_ptr = SPVM_DYNAMIC_ARRAY_fetch(
                    sub_check_info->block_my_base_stack,
                    sub_check_info->block_my_base_stack->length - 1
                  );
                  
                  int32_t block_my_base = *block_my_base_ptr;
                  
                  {
                    int32_t i;
                    for (i = block_my_base; i < sub_check_info->op_my_stack->length; i++) {
                      SPVM_OP* op_bef_my = SPVM_DYNAMIC_ARRAY_fetch(sub_check_info->op_my_stack, i);
                      SPVM_MY* bef_my = op_bef_my->uv.my;
                      if (strcmp(my->op_name->uv.name, bef_my->op_name->uv.name) == 0) {
                        found = 1;
                        break;
                      }
                    }
                  }
                  
                  if (found) {
                    SPVM_yyerror_format(compiler, "redeclaration of my \"%s\" at %s line %d\n", my->op_name->uv.name, op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  else {
                    my->index = sub_check_info->op_mys->length;
                    SPVM_DYNAMIC_ARRAY_push(sub_check_info->op_mys, op_cur);
                    SPVM_DYNAMIC_ARRAY_push(sub_check_info->op_my_stack, op_cur);
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_CALL_SUB: {
                  
                  // Check sub name
                  SPVM_OP_resolve_call_sub(compiler, op_cur, op_package);
                  
                  SPVM_OP* op_list_args = op_cur->last;
                  
                  SPVM_CALL_SUB* call_sub = op_cur->uv.call_sub;

                  if (!call_sub->sub) {
                    SPVM_yyerror_format(compiler, "unknown sub \"%s\" at %s line %d\n",
                      op_cur->first->uv.name, op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  const char* sub_abs_name = call_sub->sub->abs_name;
                  
                  int32_t sub_args_count = call_sub->sub->op_args->length;
                  SPVM_OP* op_term = op_list_args->first;
                  int32_t call_sub_args_count = 0;
                  while ((op_term = SPVM_OP_sibling(compiler, op_term))) {
                    call_sub_args_count++;
                    if (call_sub_args_count > sub_args_count) {
                      SPVM_yyerror_format(compiler, "Too many arguments. sub \"%s\" at %s line %d\n", sub_abs_name, op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                    
                    _Bool is_invalid = 0;
                    
                    SPVM_OP* op_sub_arg_my = SPVM_DYNAMIC_ARRAY_fetch(call_sub->sub->op_args, call_sub_args_count - 1);
                    
                    SPVM_TYPE* sub_arg_type = SPVM_OP_get_type(compiler, op_sub_arg_my);
                    
                    // Undef
                    if (op_term->code == SPVM_OP_C_CODE_UNDEF) {
                      if (SPVM_TYPE_is_numeric(compiler, sub_arg_type)) {
                        is_invalid = 1;
                      }
                      else {
                        // Set undef type
                        op_term->uv.undef->type = sub_arg_type;
                      }
                    }
                    // Normal
                    else if (op_term) {
                      SPVM_TYPE* op_term_type = SPVM_OP_get_type(compiler, op_term);
                      
                      if (op_term_type->code !=  sub_arg_type->code) {
                        is_invalid = 1;
                      }
                    }
                    if (is_invalid) {
                      SPVM_yyerror_format(compiler, "%d argument must be %s (%s()) at %s line %d\n", (int)call_sub_args_count, sub_arg_type->name, sub_abs_name, op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                  }
                  
                  if (call_sub_args_count < sub_args_count) {
                    SPVM_yyerror_format(compiler, "Too few argument. sub \"%s\" at %s line %d\n", sub_abs_name, op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Constant subroutine
                  if (call_sub->sub->is_constant) {
                    // Replace sub to constant
                    op_cur->code = SPVM_OP_C_CODE_CONSTANT;
                    op_cur->uv.constant = call_sub->sub->op_constant->uv.constant;
                    
                    op_cur->first = NULL;
                    op_cur->last = NULL;
                    break;
                  }
                  
                  // Update operand stack max
                  if (sub->call_sub_arg_stack_max > call_sub_args_count) {
                    sub->call_sub_arg_stack_max = call_sub_args_count;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_PACKAGE_VAR: {
                  
                  // Check field name
                  SPVM_OP_resolve_package_var(compiler, op_cur, op_package);
                  if (!op_cur->uv.package_var->op_our) {
                    SPVM_yyerror_format(compiler, "Package variable not found \"%s\" at %s line %d\n",
                      op_cur->uv.package_var->op_name->uv.name, op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  SPVM_OUR* our = op_cur->uv.package_var->op_our->uv.our;
                  
                  if (package != our->op_package->uv.package) {
                    SPVM_yyerror_format(compiler, "Package variable is private \"%s\" \"%s\" at %s line %d\n",
                      our->op_package->uv.package->op_name->uv.name, our->op_package_var->uv.package_var->op_name->uv.name, op_cur->file, op_cur->line);
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_CALL_FIELD: {
                  SPVM_OP* op_term_invocker = op_cur->first;
                  SPVM_OP* op_name = op_cur->last;
                  
                  if (op_term_invocker->code == SPVM_OP_C_CODE_ASSIGN) {
                    op_term_invocker = op_term_invocker->first;
                  }
                  
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_term_invocker);
                  
                  if (!(type && type->op_package)) {
                    SPVM_yyerror_format(compiler, "field invoker is invalid \"%s\" at %s line %d\n",
                      op_name->uv.name, op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Check field name
                  SPVM_OP_resolve_call_field(compiler, op_cur);
                  
                  SPVM_FIELD* field = op_cur->uv.call_field->field;
                  
                  if (!field) {
                    SPVM_yyerror_format(compiler, "unknown field \"%s\" \"%s\" at %s line %d\n",
                      type->name, op_name->uv.name, op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  if ( package != field->op_package->uv.package) {
                    SPVM_yyerror_format(compiler, "Field is private \"%s\" \"%s\" at %s line %d\n",
                      field->op_package->uv.package->op_name->uv.name, field->op_name->uv.name, op_cur->file, op_cur->line);
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_WEAKEN_FIELD: {
                  SPVM_OP* op_call_field = op_cur->first;
                  
                  SPVM_FIELD* field = op_call_field->uv.call_field->field;
                  
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_call_field);
                  
                  if (type->code <= SPVM_TYPE_C_CODE_DOUBLE) {
                    SPVM_yyerror_format(compiler, "weaken is only used for object field \"%s\" \"%s\" at %s line %d\n",
                      field->op_package->uv.package->op_name->uv.name, field->op_name->uv.name, op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    break;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_CONVERT: {
                  
                  SPVM_OP* op_term = op_cur->first;
                  SPVM_OP* op_type = op_cur->last;
                  
                  SPVM_TYPE* term_type = SPVM_OP_get_type(compiler, op_term);
                  assert(term_type);
                  
                  SPVM_TYPE* type_type = SPVM_OP_get_type(compiler, op_type);
                  assert(type_type);
                  
                  _Bool can_convert = 0;
                  if (SPVM_TYPE_is_numeric(compiler, term_type) && SPVM_TYPE_is_numeric(compiler, type_type)) {
                    can_convert = 1;
                  }
                  
                  if (!can_convert) {
                    SPVM_yyerror_format(compiler, "can't convert type %s to %s at %s line %d\n",
                    term_type->name, type_type->name, op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
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
        // Set my var information
        sub->op_mys = sub_check_info->op_mys;
      }

      if (!sub->is_native) {
        // Run OPs
        SPVM_OP* op_base = SPVM_OP_get_op_block_from_op_sub(compiler, op_sub);
        SPVM_OP* op_cur = op_base;
        _Bool finish = 0;
        while (op_cur) {
          
          if (op_cur->first) {
            op_cur = op_cur->first;
          }
          else {
            while (1) {
              // Create temporary variable for no is_var_assign_right term witch is not variable
              int32_t create_tmp_var = 0;
              SPVM_TYPE* tmp_var_type = SPVM_OP_get_type(compiler, op_cur);
              
              // [START]Postorder traversal position
              if (!op_cur->is_assign_left && !op_cur->is_var_assign_right) {
                switch (op_cur->code) {
                  case SPVM_OP_C_CODE_ADD:
                  case SPVM_OP_C_CODE_SUBTRACT:
                  case SPVM_OP_C_CODE_MULTIPLY:
                  case SPVM_OP_C_CODE_DIVIDE:
                  case SPVM_OP_C_CODE_BIT_AND:
                  case SPVM_OP_C_CODE_BIT_OR:
                  case SPVM_OP_C_CODE_BIT_XOR:
                  case SPVM_OP_C_CODE_BIT_NOT:
                  case SPVM_OP_C_CODE_REMAINDER:
                  case SPVM_OP_C_CODE_LEFT_SHIFT:
                  case SPVM_OP_C_CODE_RIGHT_SHIFT:
                  case SPVM_OP_C_CODE_RIGHT_SHIFT_UNSIGNED:
                  case SPVM_OP_C_CODE_COMPLEMENT:
                  case SPVM_OP_C_CODE_NEGATE:
                  case SPVM_OP_C_CODE_PLUS:
                  case SPVM_OP_C_CODE_CONVERT:
                  case SPVM_OP_C_CODE_ARRAY_LENGTH:
                  case SPVM_OP_C_CODE_NEW:
                  case SPVM_OP_C_CODE_CONCAT_STRING:
                  case SPVM_OP_C_CODE_EXCEPTION_VAR:
                  case SPVM_OP_C_CODE_PACKAGE_VAR:
                  case SPVM_OP_C_CODE_ARRAY_ELEM:
                  case SPVM_OP_C_CODE_SWITCH_CONDITION:
                    create_tmp_var = 1;
                    break;
                  case SPVM_OP_C_CODE_UNDEF: {
                    if (op_cur->uv.undef->type) {
                      create_tmp_var = 1;
                    }
                    break;
                  }
                  case SPVM_OP_C_CODE_CONSTANT: {
                    if (SPVM_TYPE_is_numeric(compiler, tmp_var_type) && op_cur->flag != SPVM_OP_C_FLAG_CONSTANT_CASE) {
                      create_tmp_var = 1;
                    }
                    break;
                  }
                  case SPVM_OP_C_CODE_CALL_FIELD: {
                    if (!(op_cur->flag &= SPVM_OP_C_FLAG_CALL_FIELD_WEAKEN)) {
                      create_tmp_var = 1;
                    }
                    break;
                  }
                  case SPVM_OP_C_CODE_CALL_SUB: {
                    if (tmp_var_type->code != SPVM_TYPE_C_CODE_VOID) {
                      create_tmp_var = 1;
                    }
                    break;
                  }
                  case SPVM_OP_C_CODE_VAR: {
                    if (op_cur->uv.var->create_tmp_var) {
                      if (!op_cur->uv.var->created_tmp_var) {
                        create_tmp_var = 1;
                        op_cur->uv.var->created_tmp_var = 1;
                      }
                    }
                    break;
                  }
                }
              }

              // Create temporary variable
              if (create_tmp_var) {
                SPVM_OP* op_var_tmp = SPVM_OP_CHECKEKR_new_op_var_tmp(compiler, tmp_var_type, sub_check_info, op_cur->file, op_cur->line);
                if (op_var_tmp == NULL) {
                  return;
                }
                
                // Cut new op
                SPVM_OP* op_target = op_cur;
                SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_target);

                // Assing op
                SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ASSIGN, op_cur->file, op_cur->line);
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
      
    }
  }
}
