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
#include "spvm_our.h"
#include "spvm_package_var.h"
#include "spvm_undef.h"
#include "spvm_block.h"

SPVM_OP* SPVM_OP_CHECKEKR_new_op_var_tmp(SPVM_COMPILER* compiler, SPVM_TYPE* type, SPVM_LIST* op_mys, const char* file, int32_t line) {

  // Create temporary variable
  // my
  SPVM_MY* my = SPVM_MY_new(compiler);

  // Temparary variable name
  char* name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, strlen("@tmp2147483647"));
  sprintf(name, "@tmp%d", op_mys->length);
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NAME, file, line);
  op_name->uv.name = name;
  my->op_name = op_name;

  // Set type to my var
  my->op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, file, line);
  my->op_type->uv.type = type;

  // op my
  SPVM_OP* op_my = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MY, file, line);
  op_my->uv.my = my;

  // Add my var
  SPVM_LIST_push(op_mys, op_my);
  
  SPVM_OP* op_var = SPVM_OP_new_op_var_from_op_my(compiler, op_my);
  
  return op_var;
}

void SPVM_OP_CHECKER_check(SPVM_COMPILER* compiler) {
  
  SPVM_LIST* op_types = compiler->op_types;
  
  // Resolve String type
  SPVM_TYPE* type_string = SPVM_LIST_fetch(compiler->types, SPVM_TYPE_C_ID_STRING);
  type_string->op_package = SPVM_HASH_search(compiler->op_package_symtable, "String", strlen("String"));
  
  // Resolve types
  {
    int32_t i;
    for (i = 0; i < op_types->length; i++) {
      assert(compiler->types->length <= SPVM_LIMIT_C_TYPES);
      
      SPVM_OP* op_type = SPVM_LIST_fetch(op_types, i);
      
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
        type->id = compiler->types->length;
        type->id = compiler->types->length;
        
        SPVM_TYPE* new_type = SPVM_TYPE_new(compiler);
        memcpy(new_type, type, sizeof(SPVM_TYPE));
        SPVM_LIST_push(compiler->types, new_type);
        SPVM_HASH_insert(compiler->type_symtable, type->name, strlen(type->name), new_type);
        
        new_type->op_package = SPVM_HASH_search(compiler->op_package_symtable, type->name, strlen(type->name));
        
        op_type->uv.type = new_type;
      }
    }
  }

  // Set parent type id and element type id
  {
    int32_t i;
    for (i = 0; i < compiler->types->length; i++) {
      SPVM_TYPE* type = SPVM_LIST_fetch(compiler->types, i);
      
      char* parent_type_name = SPVM_TYPE_get_parent_name(compiler, type->name);
      SPVM_TYPE* parent_type = (SPVM_TYPE*)SPVM_HASH_search(compiler->type_symtable, parent_type_name, strlen(parent_type_name));
      if (parent_type) {
        type->parent_type_id = parent_type->id;
      }
      
      // Element type id
      char* element_type_name = SPVM_TYPE_get_element_name(compiler, type->name);
      if (element_type_name) {
        SPVM_TYPE* element_type = (SPVM_TYPE*)SPVM_HASH_search(compiler->type_symtable, element_type_name, strlen(element_type_name));
        if (element_type) {
          type->element_type_id = element_type->id;
        }
        else {
          assert(0);
        }
      }
    }
  }

  // Calcurate fild byte offset and package byte size
  SPVM_LIST* op_packages = compiler->op_packages;
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
      SPVM_OP* op_package = SPVM_LIST_fetch(op_packages, package_pos);
      SPVM_PACKAGE* package = op_package->uv.package;
      SPVM_LIST* op_fields = package->op_fields;
      
      // Separate reference type and value type
      int32_t next_max_byte_size = alignment;
      int32_t current_byte_offset = 0;
      {
        int32_t field_pos;
        for (field_pos = 0; field_pos < op_fields->length; field_pos++) {
          SPVM_OP* op_field = SPVM_LIST_fetch(op_fields, field_pos);
          SPVM_FIELD* field = op_field->uv.field;
          SPVM_TYPE* field_type = field->op_type->uv.type;
          
          int32_t field_byte_size;
          switch (field_type->id) {
            case SPVM_TYPE_C_ID_BYTE:
              field_byte_size = sizeof(int8_t);
              break;
            case SPVM_TYPE_C_ID_SHORT:
              field_byte_size = sizeof(int16_t);
              break;
            case SPVM_TYPE_C_ID_INT:
              field_byte_size = sizeof(int32_t);
              break;
            case SPVM_TYPE_C_ID_LONG:
              field_byte_size = sizeof(int64_t);
              break;
            case SPVM_TYPE_C_ID_FLOAT:
              field_byte_size = sizeof(float);
              break;
            case SPVM_TYPE_C_ID_DOUBLE:
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
      SPVM_OP* op_package = SPVM_LIST_fetch(op_packages, package_pos);
      SPVM_PACKAGE* package = op_package->uv.package;
      SPVM_LIST* op_fields = package->op_fields;
      
      // Calculate package byte size
      {
        int32_t field_pos;
        for (field_pos = 0; field_pos < op_fields->length; field_pos++) {
          SPVM_OP* op_field = SPVM_LIST_fetch(op_fields, field_pos);
          SPVM_FIELD* field = op_field->uv.field;
          field->index = field_pos;
        }
      }
    }
  }
  
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < compiler->op_subs->length; sub_index++) {
      
      SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, sub_index);
      SPVM_SUB* sub = op_sub->uv.sub;
      SPVM_OP* op_package = sub->op_package;
      SPVM_PACKAGE* package = op_package->uv.package;
      
      // Set subroutine id
      sub->id = sub_index;
      
      int32_t eval_block_stack_length = 0;
      int32_t loop_block_stack_length = 0;
      
      SPVM_LIST* op_mys = sub->op_mys;
      SPVM_LIST* op_my_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
      SPVM_LIST* block_my_base_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
      
      // Switch stack
      SPVM_LIST* op_switch_stack = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
      
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
          
          if (arg_type->id != package->op_type->uv.type->id) {
            error = 1;
          }
        }
        
        if (error) {
          SPVM_yyerror_format(compiler, "DESTROY argument must be self\n", op_sub->file, op_sub->line);
        }
      }
      
      if (package->is_interface && (sub->op_block || sub->is_native)) {
        SPVM_yyerror_format(compiler, "Subroutine in interface package can't have implementation\n", op_sub->file, op_sub->line);
      }
      
      // Only process normal subroutine
      if (!sub->is_native) {
        
        // Run OPs
        SPVM_OP* op_base = SPVM_OP_get_op_block_from_op_sub(compiler, op_sub);
        SPVM_OP* op_cur = op_base;
        _Bool finish = 0;
        while (op_cur) {
          // [START]Preorder traversal position
          
          switch (op_cur->id) {
            case SPVM_OP_C_ID_SWITCH: {
              SPVM_LIST_push(op_switch_stack, op_cur);
              break;
            }
            // Start scope
            case SPVM_OP_C_ID_BLOCK: {
              
              int32_t block_my_base = op_my_stack->length;
              int32_t* block_my_base_ptr = SPVM_COMPILER_ALLOCATOR_alloc_int(compiler, compiler->allocator);
              *block_my_base_ptr = block_my_base;
              SPVM_LIST_push(block_my_base_stack, block_my_base_ptr);
              
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
                    compiler->fatal_error = 1;
                    return;
                  }
                  break;
                }
                case SPVM_OP_C_ID_LAST: {
                  if (loop_block_stack_length == 0 && op_switch_stack->length == 0) {
                    SPVM_yyerror_format(compiler, "last statement must be in loop block or switch block at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  break;
                }
                case SPVM_OP_C_ID_SWITCH: {
                  
                  SPVM_OP* op_switch_condition = op_cur->first;
                  
                  SPVM_TYPE* term_type = SPVM_OP_get_type(compiler, op_switch_condition->first);
                  
                  // Check type
                  if (!term_type || !(term_type->id == SPVM_TYPE_C_ID_INT)) {
                    SPVM_yyerror_format(compiler, "Switch condition need int value at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
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
                        SPVM_yyerror_format(compiler, "case need constant at %s line %d\n", op_cur->file, op_cur->line);
                        compiler->fatal_error = 1;
                        return;
                      }
                      
                      SPVM_TYPE* case_value_type = SPVM_OP_get_type(compiler, op_constant);
                      
                      if (case_value_type->id != term_type->id) {
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
                      SPVM_OP* op_case = SPVM_LIST_fetch(op_cases, i);
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
                  
                  // tableswitch if the following. SWITCHRTIO is 1.5 by default
                  // 4 + range <= (3 + 2 * length) * SWITCHRTIO
                  double range = (double) max - (double) min;
                  int32_t id;
                  if (4.0 + range <= (3.0 + 2.0 * (double) length) * 1.5) {
                    id = SPVM_SWITCH_INFO_C_ID_TABLE_SWITCH;
                  }
                  else {
                    id = SPVM_SWITCH_INFO_C_ID_LOOKUP_SWITCH;
                  }
                  
                  switch_info->id = id;
                  switch_info->min = min;
                  switch_info->max = max;
                  
                  SPVM_LIST_pop(op_switch_stack);
                  
                  break;
                }
                case SPVM_OP_C_ID_CASE: {
                  if (op_switch_stack->length > 0) {
                    SPVM_OP* op_switch = SPVM_LIST_fetch(op_switch_stack, op_switch_stack->length - 1);
                    SPVM_SWITCH_INFO* switch_info = op_switch->uv.switch_info;
                    if (switch_info->op_cases->length == SPVM_LIMIT_C_CASES) {
                      SPVM_yyerror_format(compiler, "Too many case statements at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }

                    SPVM_LIST_push(switch_info->op_cases, op_cur);
                  }
                  break;
                }
                case SPVM_OP_C_ID_DEFAULT: {
                  if (op_switch_stack->length > 0) {
                    SPVM_OP* op_switch = SPVM_LIST_fetch(op_switch_stack, op_switch_stack->length - 1);
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
                  else if (op_first->id != SPVM_OP_C_ID_UNDEF && op_last->id == SPVM_OP_C_ID_UNDEF) {
                    SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                    if (SPVM_TYPE_is_numeric(compiler, first_type)) {
                      SPVM_yyerror_format(compiler, "== left value must be object at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                  }
                  // undef == term
                  else if (op_first->id == SPVM_OP_C_ID_UNDEF && op_last->id != SPVM_OP_C_ID_UNDEF) {
                    SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                    if (SPVM_TYPE_is_numeric(compiler, last_type)) {
                      SPVM_yyerror_format(compiler, "== right value must be object at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
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
                  else if (op_first->id != SPVM_OP_C_ID_UNDEF && op_last->id == SPVM_OP_C_ID_UNDEF) {
                    SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);

                    if (SPVM_TYPE_is_numeric(compiler, first_type)) {
                      SPVM_yyerror_format(compiler, "!= left value must be object at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                  }
                  // undef != term
                  else if (op_first->id == SPVM_OP_C_ID_UNDEF && op_last->id != SPVM_OP_C_ID_UNDEF) {
                    SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

                    if (SPVM_TYPE_is_numeric(compiler, last_type)) {
                      SPVM_yyerror_format(compiler, "!= right value must be object at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
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

                  SPVM_OP_apply_binary_numeric_promotion(compiler, op_cur->first, op_cur->last);

                  break;
                }
                case SPVM_OP_C_ID_LE: {

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

                  SPVM_OP_apply_binary_numeric_promotion(compiler, op_cur->first, op_cur->last);
                  
                  break;
                }
                case SPVM_OP_C_ID_GT: {

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

                  SPVM_OP_apply_binary_numeric_promotion(compiler, op_cur->first, op_cur->last);
                  
                  break;
                }
                case SPVM_OP_C_ID_GE: {

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
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  if (SPVM_TYPE_is_integral(compiler, last_type)) {
                    SPVM_OP_apply_unary_numeric_promotion(compiler, op_cur->last);
                    
                    if (last_type->id >= SPVM_TYPE_C_ID_LONG) {
                      SPVM_yyerror_format(compiler, "<< operator right value must be int at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                  }
                  else {
                    SPVM_yyerror_format(compiler, "<< operator right value must be int at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
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
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  if (SPVM_TYPE_is_integral(compiler, last_type)) {
                    SPVM_OP_apply_unary_numeric_promotion(compiler, op_cur->last);
                    
                    if (last_type->id >= SPVM_TYPE_C_ID_LONG) {
                      SPVM_yyerror_format(compiler, ">> operator right value must be int at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                  }
                  else {
                    SPVM_yyerror_format(compiler, ">> operator right value must be int at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
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
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  if (SPVM_TYPE_is_integral(compiler, last_type)) {
                    SPVM_OP_apply_unary_numeric_promotion(compiler, op_cur->last);
                    
                    if (last_type->id >= SPVM_TYPE_C_ID_LONG) {
                      SPVM_yyerror_format(compiler, ">>> operator right value must be int at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                  }
                  else {
                    SPVM_yyerror_format(compiler, ">>> operator right value must be int at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_ID_NEW: {
                  if (op_cur->first->id == SPVM_OP_C_ID_TYPE) {
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
                      else {
                        if (SPVM_TYPE_is_numeric(compiler, index_type)) {
                          SPVM_OP_apply_unary_numeric_promotion(compiler, op_index_term);
                          
                          SPVM_TYPE* index_type = SPVM_OP_get_type(compiler, op_index_term);
                          
                          if (index_type->id >= SPVM_TYPE_C_ID_LONG) {
                            SPVM_yyerror_format(compiler, "new operator can't create array which don't have int length \"%s\" at %s line %d\n", type->name, op_cur->file, op_cur->line);
                            compiler->fatal_error = 1;
                            return;
                          }
                        }
                        else {
                          SPVM_yyerror_format(compiler, "new operator can't create array which don't have numeric length \"%s\" at %s line %d\n", type->name, op_cur->file, op_cur->line);
                          compiler->fatal_error = 1;
                          return;
                        }
                      }
                    }
                    else {
                      if (SPVM_TYPE_is_numeric(compiler, type)) {
                        SPVM_yyerror_format(compiler,
                          "new operator can't receive numeric type at %s line %d\n", op_cur->file, op_cur->line);
                        compiler->fatal_error = 1;
                        return;
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
                  if (!SPVM_TYPE_is_integral(compiler, first_type) || !SPVM_TYPE_is_integral(compiler, last_type)) {
                    SPVM_yyerror_format(compiler,
                      "^ operator can receive only integral type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
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
                    compiler->fatal_error = 1;
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
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  SPVM_OP_apply_binary_numeric_promotion(compiler, op_cur->first, op_cur->last);
                  
                  break;
                }
                case SPVM_OP_C_ID_ARRAY_LENGTH: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  
                  // First value must be array
                  if (!SPVM_TYPE_is_array(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "right of @ or len must be array at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_ID_ARRAY_ELEM: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                  
                  // Left value must be array
                  if (!SPVM_TYPE_is_array(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "left value must be array at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Right value must be integer
                  if (SPVM_TYPE_is_numeric(compiler, last_type)) {
                    SPVM_OP_apply_unary_numeric_promotion(compiler, op_cur->last);
                    SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                    
                    if (last_type->id != SPVM_TYPE_C_ID_INT) {
                      SPVM_yyerror_format(compiler, "array index must be int type at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                  }
                  else {
                    SPVM_yyerror_format(compiler, "array index must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_ID_ASSIGN: {
                  SPVM_OP* op_assign_to = op_cur->last;
                  SPVM_OP* op_assign_from = op_cur->first;
                  
                  SPVM_TYPE* assign_to_type = SPVM_OP_get_type(compiler, op_assign_to);
                  SPVM_TYPE* assign_from_type = SPVM_OP_get_type(compiler, op_assign_from);
                  
                  // Can't assign undef to numeric value
                  if (SPVM_TYPE_is_numeric(compiler, assign_to_type) && op_assign_from->id == SPVM_OP_C_ID_UNDEF) {
                    SPVM_yyerror_format(compiler, "Can't assign undef to numeric type at %s line %d\n", op_assign_to->file, op_assign_to->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Copy left type to undef
                  if (op_assign_from->id == SPVM_OP_C_ID_UNDEF) {
                    assign_from_type = assign_to_type;
                    op_assign_from->uv.undef->type = assign_from_type;
                  }
                  
                  // Numeric type check
                  if (SPVM_TYPE_is_numeric(compiler, assign_to_type) && SPVM_TYPE_is_numeric(compiler, assign_from_type)) {
                    int32_t do_convert = 0;
                    if (assign_to_type->id > assign_from_type->id) {
                      do_convert = 1;
                    }
                    // Narrowng convetion only when constant is in range
                    else if (assign_to_type->id < assign_from_type->id) {
                      int32_t compile_error = 0;
                      if (op_assign_from->id == SPVM_OP_C_ID_CONSTANT) {
                        int32_t compile_error = 0;
                        SPVM_CONSTANT* constant = op_assign_from->uv.constant;
                        int64_t constant_value;
                        if (constant->type->id == SPVM_TYPE_C_ID_INT || constant->type->id == SPVM_TYPE_C_ID_LONG) {
                          if (constant->type->id == SPVM_TYPE_C_ID_INT) {
                            constant_value = constant->value.int_value;
                          }
                          else if (constant->type->id == SPVM_TYPE_C_ID_LONG) {
                            constant_value = constant->value.long_value;
                          }
                          
                          if (assign_to_type->id == SPVM_OP_C_ID_BYTE) {
                            if (!(constant_value >= INT8_MIN && constant_value <= INT8_MAX)) {
                              compile_error = 1;
                            }
                          }
                          else if (assign_to_type->id == SPVM_OP_C_ID_SHORT) {
                            if (!(constant_value >= INT16_MIN && constant_value <= INT16_MAX)) {
                              compile_error = 1;
                            }
                          }
                          else if (assign_to_type->id == SPVM_OP_C_ID_INT) {
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
                        SPVM_yyerror_format(compiler, "Can't do implicite narrowing convertion at %s line %d\n", op_cur->file, op_cur->line);
                        compiler->fatal_error = 1;
                        return;
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

                      op_convert->is_var_assign_from = op_convert->first->is_var_assign_from;
                      op_convert->is_assign_from = op_convert->first->is_assign_from;
                      
                      op_convert->first->is_var_assign_from = 0;
                      op_convert->first->is_assign_from = 0;
                    }
                  }
                  // Object type check
                  else {
                    _Bool incompatible_type = 0;
                    if (assign_to_type->id != assign_from_type->id) {
                      if (assign_to_type->dimension != assign_from_type->dimension) {
                        incompatible_type = 1;
                      }
                      else {
                        SPVM_TYPE* assign_to_base_type = assign_to_type->base_type;
                        SPVM_TYPE* assign_from_base_type = assign_from_type->base_type;
                        if (assign_to_base_type->id != assign_from_type->base_type->id) {
                          incompatible_type = 1;
                        }
                      }
                    }
                    if (incompatible_type) {
                      SPVM_yyerror_format(compiler, "Invalid type is assigned at %s line %d\n", op_cur->file, op_cur->line);
                    }
                  }
                  
                  if (op_assign_to->id == SPVM_OP_C_ID_VAR) {
                    if (op_assign_from->id == SPVM_OP_C_ID_CONCAT_STRING) {
                      int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                      
                      if (op_assign_from->first->id == SPVM_OP_C_ID_VAR) {
                        int32_t index_in1 = SPVM_OP_get_my_index(compiler, op_assign_from->first);
                        if (index_out == index_in1) {
                          op_assign_from->first->uv.var->create_tmp_var = 1;
                        }
                      }
                      
                      if (op_assign_from->last->id == SPVM_OP_C_ID_VAR) {
                        int32_t index_in2 = SPVM_OP_get_my_index(compiler, op_assign_from->last);
                        if (index_out == index_in2) {
                          op_assign_from->last->uv.var->create_tmp_var = 1;
                        }
                      }
                    }
                    else if (op_assign_from->id == SPVM_OP_C_ID_CALL_SUB) {
                      int32_t index_out = SPVM_OP_get_my_index(compiler, op_assign_to);
                      
                      // Push args
                      SPVM_OP* op_args =op_assign_from->last;
                      SPVM_OP* op_arg = op_args->first;
                      while ((op_arg = SPVM_OP_sibling(compiler, op_arg))) {
                        if (op_arg->id == SPVM_OP_C_ID_VAR) {
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
                case SPVM_OP_C_ID_RETURN: {
                  
                  SPVM_OP* op_term = op_cur->first;
                  
                  if (op_term) {
                    SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_term);
                    SPVM_TYPE* sub_return_type = SPVM_OP_get_type(compiler, sub->op_return_type);
                    
                    _Bool is_invalid = 0;
                    
                    
                    // Undef
                    if (op_term->id == SPVM_OP_C_ID_UNDEF) {
                      if (sub->op_return_type->uv.type->id == SPVM_TYPE_C_ID_VOID) {
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
                      if (first_type->id != sub_return_type->id) {
                        is_invalid = 1;
                      }
                    }
                    // Empty
                    else {
                      if (sub->op_return_type->uv.type->id != SPVM_TYPE_C_ID_VOID) {
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
                case SPVM_OP_C_ID_NEGATE: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  
                  // Must be numeric type
                  if (SPVM_TYPE_is_object(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "- operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
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
                    compiler->fatal_error = 1;
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
                    compiler->fatal_error = 1;
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
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Right value must not be undef
                  if (!last_type) {
                    SPVM_yyerror_format(compiler, "+ operator right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }

                  // Left value must not be object type
                  if (SPVM_TYPE_is_object(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "+ operator left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }

                  // Right value must not be object type
                  if (SPVM_TYPE_is_object(compiler, last_type)) {
                    SPVM_yyerror_format(compiler, "+ operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
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
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Right value Must not be undef
                  if (!last_type) {
                    SPVM_yyerror_format(compiler, "- operator right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }

                  // Left value must not be object type
                  if (SPVM_TYPE_is_object(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "- operator left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }

                  // Right value must not be object type
                  if (SPVM_TYPE_is_object(compiler, last_type)) {
                    SPVM_yyerror_format(compiler, "- operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
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
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Right value Must not be undef
                  if (!last_type) {
                    SPVM_yyerror_format(compiler, "* operator right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Left value must not be object type
                  if (SPVM_TYPE_is_object(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "* operator left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }

                  // Right value must not be object type
                  if (SPVM_TYPE_is_object(compiler, last_type)) {
                    SPVM_yyerror_format(compiler, "* operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
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
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Right value Must not be undef
                  if (!last_type) {
                    SPVM_yyerror_format(compiler, "/ operator right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }

                  // Left value must not be object type
                  if (SPVM_TYPE_is_object(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "/ operator left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }

                  // Right value must not be object type
                  if (SPVM_TYPE_is_object(compiler, last_type)) {
                    SPVM_yyerror_format(compiler, "/ operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
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
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Right value Must not be undef
                  if (!last_type) {
                    SPVM_yyerror_format(compiler, "%% operator right value must be not undef at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }

                  // Left value must not be object type
                  if (SPVM_TYPE_is_object(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "%% operator left value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }

                  // Right value must not be object type
                  if (SPVM_TYPE_is_object(compiler, last_type)) {
                    SPVM_yyerror_format(compiler, "%% operator right value must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Upgrade type
                  SPVM_OP_apply_binary_numeric_promotion(compiler, op_cur->first, op_cur->last);
                                                  
                  break;
                }
                case SPVM_OP_C_ID_PRE_INC:
                case SPVM_OP_C_ID_POST_INC:
                case SPVM_OP_C_ID_PRE_DEC:
                case SPVM_OP_C_ID_POST_DEC: {
                  SPVM_OP* op_first = op_cur->first;
                  if (op_first->id != SPVM_OP_C_ID_VAR) {
                    SPVM_yyerror_format(compiler, "invalid is_assign_to in increment at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_first);
                  
                  // Numeric type
                  if (!SPVM_TYPE_is_numeric(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "increment or decrement operand must be numeric type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  op_cur->first->is_assign_to = 1;
                  
                  break;
                }
                case SPVM_OP_C_ID_LOOP: {
                  
                  break;
                }
                case SPVM_OP_C_ID_CONCAT_STRING: {
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
                    SPVM_OP* op_concat_string2 = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONCAT_STRING, op_concat_string1->file, op_concat_string1->line);


                    SPVM_OP* op_term1 = op_concat_string1->first;
                    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term1);
                    
                    // Empty string
                    SPVM_OP* op_constant_empty_string = SPVM_OP_new_op_constant_string(compiler, "", 0, op_concat_string1->file, op_concat_string1->line);
                    SPVM_OP* op_build_constant = SPVM_OP_build_constant(compiler, op_constant_empty_string);
                    
                    SPVM_OP_insert_child(compiler, op_concat_string2, op_concat_string2->last, op_build_constant);
                    SPVM_OP_insert_child(compiler, op_concat_string2, op_concat_string2->last, op_term1);
                    
                    SPVM_OP_replace_op(compiler, op_stab, op_concat_string2);
                  }
                  
                  break;
                }
                case SPVM_OP_C_ID_CROAK: {
                  if (op_cur->first->id == SPVM_OP_C_ID_UNDEF) {
                    op_cur->first->uv.undef->type = SPVM_TYPE_get_string_type(compiler);
                  }
                  else {
                    SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                    if (first_type->id != SPVM_TYPE_C_ID_STRING) {
                      SPVM_yyerror_format(compiler, "croak argument type must be String at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                  }
                  break;
                }
                // End of scope
                case SPVM_OP_C_ID_BLOCK: {
                  // Pop block my variable base
                  assert(block_my_base_stack->length > 0);
                  int32_t* block_my_base_ptr = SPVM_LIST_pop(block_my_base_stack);
                  int32_t block_my_base = *block_my_base_ptr;
                    
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
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Assign initial value
                  if (op_cur->first && op_cur->first->id == SPVM_OP_C_ID_MY) {
                    SPVM_OP* op_my = op_cur->first;
                    SPVM_MY* my = op_my->uv.my;
                    
                    if (!op_cur->is_assign_to && !my->is_arg) {
                      // Before
                      // VAR
                      
                      // After
                      // ASSIGN
                      //  CONSTANT_XXX_0
                      //  VAR
                      
                      SPVM_TYPE* var_type = SPVM_OP_get_type(compiler, op_cur);
                      assert(var_type);
                      
                      SPVM_OP* op_assign_from;
                      switch (var_type->id) {
                        case SPVM_TYPE_C_ID_BYTE:
                          op_assign_from = SPVM_OP_new_op_constant_byte(compiler, 0, op_cur->file, op_cur->line);
                          break;
                        case SPVM_TYPE_C_ID_SHORT:
                          op_assign_from = SPVM_OP_new_op_constant_short(compiler, 0, op_cur->file, op_cur->line);
                          break;
                        case SPVM_TYPE_C_ID_INT:
                          op_assign_from = SPVM_OP_new_op_constant_int(compiler, 0, op_cur->file, op_cur->line);
                          break;
                        case SPVM_TYPE_C_ID_LONG:
                          op_assign_from = SPVM_OP_new_op_constant_long(compiler, 0, op_cur->file, op_cur->line);
                          break;
                        case SPVM_TYPE_C_ID_FLOAT:
                          op_assign_from = SPVM_OP_new_op_constant_float(compiler, 0, op_cur->file, op_cur->line);
                          break;
                        case SPVM_TYPE_C_ID_DOUBLE:
                          op_assign_from = SPVM_OP_new_op_constant_double(compiler, 0, op_cur->file, op_cur->line);
                          break;
                        default:
                          op_assign_from = SPVM_OP_new_op_undef(compiler, op_cur->file, op_cur->line);
                      }
                      
                      SPVM_OP* op_var = op_cur;
                      
                      // Cut VAR
                      SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);

                      // ASSIGN
                      SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_cur->file, op_cur->line);
                      SPVM_OP* op_build_assign = SPVM_OP_build_assign(compiler, op_assign, op_var, op_assign_from);

                      SPVM_OP_replace_op(compiler, op_stab, op_build_assign);
                      
                      op_cur = op_var;
                    }
                  }
                  
                  break;
                }
                case SPVM_OP_C_ID_MY: {
                  SPVM_MY* my = op_cur->uv.my;
                  
                  // Redeclaration error if same name variable is declare in same block
                  _Bool found = 0;
                  int32_t* block_my_base_ptr = SPVM_LIST_fetch(
                    block_my_base_stack,
                    block_my_base_stack->length - 1
                  );
                  int32_t block_my_base = *block_my_base_ptr;
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
                    compiler->fatal_error = 1;
                    return;
                  }
                  else {
                    SPVM_LIST_push(op_mys, op_cur);
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
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_ID_CALL_SUB: {
                  
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
                  
                  if (call_sub->call_type_id != call_sub->sub->call_type_id) {
                    SPVM_yyerror_format(compiler, "Invalid subroutine call \"%s\" at %s line %d\n",
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
                    
                    SPVM_OP* op_sub_arg_my = SPVM_LIST_fetch(call_sub->sub->op_args, call_sub_args_count - 1);
                    
                    SPVM_TYPE* sub_arg_type = SPVM_OP_get_type(compiler, op_sub_arg_my);
                    
                    // Undef
                    if (op_term->id == SPVM_OP_C_ID_UNDEF) {
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
                      
                      if (op_term_type->id !=  sub_arg_type->id) {
                        is_invalid = 1;
                      }
                    }
                    if (is_invalid) {
                      SPVM_yyerror_format(compiler, "%dth argument type must be %s (%s()) at %s line %d\n", (int)call_sub_args_count, sub_arg_type->name, sub_abs_name, op_cur->file, op_cur->line);
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
                  
                  break;
                }
                case SPVM_OP_C_ID_PACKAGE_VAR: {
                  
                  // Check field name
                  SPVM_OP_resolve_package_var(compiler, op_cur, op_package);
                  if (!op_cur->uv.package_var->op_our) {
                    SPVM_yyerror_format(compiler, "Package variable not found \"%s\" at %s line %d\n",
                      op_cur->uv.package_var->op_name->uv.name, op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_ID_CALL_FIELD: {
                  SPVM_OP* op_term_invocker = op_cur->first;
                  SPVM_OP* op_name = op_cur->last;
                  
                  if (op_term_invocker->id == SPVM_OP_C_ID_ASSIGN) {
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
                  
                  break;
                }
                case SPVM_OP_C_ID_WEAKEN_FIELD: {
                  SPVM_OP* op_call_field = op_cur->first;
                  
                  SPVM_FIELD* field = op_call_field->uv.call_field->field;
                  
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_call_field);
                  
                  if (type->id <= SPVM_TYPE_C_ID_DOUBLE) {
                    SPVM_yyerror_format(compiler, "weaken is only used for object field \"%s\" \"%s\" at %s line %d\n",
                      field->op_package->uv.package->op_name->uv.name, field->op_name->uv.name, op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
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
              // Create temporary variable for no is_var_assign_from term which is not variable
              int32_t create_tmp_var = 0;
              SPVM_TYPE* tmp_var_type = SPVM_OP_get_type(compiler, op_cur);
              
              // [START]Postorder traversal position
              if (!op_cur->is_assign_to && !op_cur->is_var_assign_from) {
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
                  case SPVM_OP_C_ID_CONCAT_STRING:
                  case SPVM_OP_C_ID_EXCEPTION_VAR:
                  case SPVM_OP_C_ID_PACKAGE_VAR:
                  case SPVM_OP_C_ID_ARRAY_ELEM:
                  case SPVM_OP_C_ID_SWITCH_CONDITION:
                    create_tmp_var = 1;
                    break;
                  case SPVM_OP_C_ID_UNDEF: {
                    if (op_cur->uv.undef->type) {
                      create_tmp_var = 1;
                    }
                    break;
                  }
                  case SPVM_OP_C_ID_CONSTANT: {
                    if (SPVM_TYPE_is_numeric(compiler, tmp_var_type) && op_cur->flag != SPVM_OP_C_FLAG_CONSTANT_CASE) {
                      create_tmp_var = 1;
                    }
                    break;
                  }
                  case SPVM_OP_C_ID_CALL_FIELD: {
                    if (!(op_cur->flag &= SPVM_OP_C_FLAG_CALL_FIELD_WEAKEN)) {
                      create_tmp_var = 1;
                    }
                    break;
                  }
                  case SPVM_OP_C_ID_CALL_SUB: {
                    if (tmp_var_type->id != SPVM_TYPE_C_ID_VOID) {
                      create_tmp_var = 1;
                    }
                    break;
                  }
                  case SPVM_OP_C_ID_VAR: {
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
                SPVM_OP* op_var_tmp = SPVM_OP_CHECKEKR_new_op_var_tmp(compiler, tmp_var_type, op_mys, op_cur->file, op_cur->line);
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
      
        // SPVM_DUMPER_dump_ast(compiler, op_base);

      }

      assert(sub->file_name);
      
      // My index
      {
        int32_t my_index;
        for (my_index = 0; my_index < sub->op_mys->length; my_index++) {
          SPVM_OP* op_my = SPVM_LIST_fetch(sub->op_mys, my_index);
          SPVM_MY* my = op_my->uv.my;
          my->index = my_index;
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
}
