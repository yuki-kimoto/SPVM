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
#include "spvm_field_info.h"
#include "spvm_my_var.h"
#include "spvm_var.h"
#include "spvm_enumeration_value.h"
#include "spvm_type.h"
#include "spvm_enumeration.h"
#include "spvm_package.h"
#include "spvm_name_info.h"
#include "spvm_type.h"
#include "spvm_switch_info.h"
#include "spvm_limit.h"
#include "spvm_sub_check_info.h"

SPVM_OP* SPVM_OP_CHECKEKR_new_op_var_tmp(SPVM_COMPILER* compiler, SPVM_TYPE* type, SPVM_SUB_CHECK_INFO* sub_check_info, const char* file, int32_t line) {

  assert(sub_check_info->my_var_length <= SPVM_LIMIT_C_MY_VARS);
  if (sub_check_info->my_var_length == SPVM_LIMIT_C_MY_VARS) {
    SPVM_yyerror_format(compiler, "too many lexical variables(Temparay variable is created in new) at %s line %d\n", file, line);
    compiler->fatal_error = 1;
    return NULL;
  }
                    
  // Create temporary variable
  // my_var
  SPVM_MY_VAR* my_var = SPVM_MY_VAR_new(compiler);

  // Temparary variable name
  char* name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, strlen("@tmp2147483647"));
  sprintf(name, "@tmp%d", sub_check_info->my_var_tmp_index++);
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NAME, file, line);
  op_name->uv.name = name;
  my_var->op_name = op_name;

  // Set type to my var
  my_var->op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, file, line);
  my_var->op_type->uv.type = type;

  // Index
  my_var->index = sub_check_info->my_var_length++;

  // op my_var
  SPVM_OP* op_my_var = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_MY, file, line);
  op_my_var->uv.my_var = my_var;

  // Add my var
  SPVM_DYNAMIC_ARRAY_push(sub_check_info->op_my_vars, op_my_var);
  SPVM_DYNAMIC_ARRAY_push(sub_check_info->op_my_var_stack, op_my_var);
  
  SPVM_OP* op_var = SPVM_OP_new_op_var_from_op_my_var(compiler, op_my_var);
  
  return op_var;
}

void SPVM_OP_CHECKER_check(SPVM_COMPILER* compiler) {
  
  SPVM_DYNAMIC_ARRAY* op_types = compiler->op_types;
  
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
          SPVM_yyerror_format(compiler, "unknown package \"%s\" at %s line %d\n", base_name, op_type->file, op_type->line);
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
  
  // Reorder fields. Reference types place before value types.
  SPVM_DYNAMIC_ARRAY* op_packages = compiler->op_packages;
  {
    int32_t package_pos;
    for (package_pos = 0; package_pos < op_packages->length; package_pos++) {

      SPVM_OP* op_package = SPVM_DYNAMIC_ARRAY_fetch(op_packages, package_pos);
      SPVM_PACKAGE* package = op_package->uv.package;
      const char* package_name = package->op_name->uv.name;
      SPVM_DYNAMIC_ARRAY* op_fields = package->op_fields;

      if (islower(package_name[0])) {
        if (strcmp(package_name, "std") != 0) {
          SPVM_yyerror_format(compiler, "Package name \"%s\" must be start with upper case. Lowercase is reserved for core package  at %s line %d\n", package_name, op_package->file, op_package->line);
          compiler->fatal_error = 1;
          return;
        }
      }
      
      SPVM_DYNAMIC_ARRAY* op_fields_object = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
      SPVM_DYNAMIC_ARRAY* op_fields_numeric = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
      
      // Separate reference type and value type
      {
        int32_t field_pos;
        for (field_pos = 0; field_pos < op_fields->length; field_pos++) {
          SPVM_OP* op_field = SPVM_DYNAMIC_ARRAY_fetch(op_fields, field_pos);
          SPVM_FIELD_INFO* field = op_field->uv.field;
          SPVM_TYPE* field_type = field->op_type->uv.type;
          
          if (SPVM_TYPE_is_numeric(compiler, field_type)) {
            SPVM_DYNAMIC_ARRAY_push(op_fields_numeric, op_field);
          }
          else {
            SPVM_DYNAMIC_ARRAY_push(op_fields_object, op_field);
          }
        }
      }
      
      // Create ordered op fields
      SPVM_DYNAMIC_ARRAY* ordered_op_fields = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
      {
        int32_t field_pos;
        for (field_pos = 0; field_pos < op_fields_object->length; field_pos++) {
          SPVM_OP* op_field = SPVM_DYNAMIC_ARRAY_fetch(op_fields_object, field_pos);
          SPVM_DYNAMIC_ARRAY_push(ordered_op_fields, op_field);
        }
      }
      
      {
        int32_t field_pos;
        for (field_pos = 0; field_pos < op_fields_numeric->length; field_pos++) {
          SPVM_OP* op_field = SPVM_DYNAMIC_ARRAY_fetch(op_fields_numeric, field_pos);
          SPVM_DYNAMIC_ARRAY_push(ordered_op_fields, op_field);
        }
      }
      package->op_fields = ordered_op_fields;
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
          SPVM_FIELD_INFO* field = op_field->uv.field;
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
      
      // Only process normal subroutine
      if (!sub->is_native) {
        
        SPVM_SUB_CHECK_INFO* sub_check_info = SPVM_SUB_CHECK_INFO_new(compiler);
        
        // Run OPs
        SPVM_OP* op_base = SPVM_OP_get_op_block_from_op_sub(compiler, op_sub);
        SPVM_OP* op_cur = op_base;
        _Bool finish = 0;
        while (op_cur) {
          sub_check_info->op_count++;
          
          // [START]Preorder traversal position
          
          switch (op_cur->code) {
            case SPVM_OP_C_CODE_SWITCH: {
              SPVM_DYNAMIC_ARRAY_push(sub_check_info->op_switch_stack, op_cur);
              break;
            }
            // Start scope
            case SPVM_OP_C_CODE_BLOCK: {
              
              sub_check_info->block_my_var_base = sub_check_info->op_my_var_stack->length;
              int32_t* block_my_var_base_ptr = SPVM_COMPILER_ALLOCATOR_alloc_int(compiler, compiler->allocator);
              *block_my_var_base_ptr = sub_check_info->block_my_var_base;
              SPVM_DYNAMIC_ARRAY_push(sub_check_info->block_my_var_base_stack, block_my_var_base_ptr);
              
              if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_LOOP) {
                SPVM_DYNAMIC_ARRAY_push(sub_check_info->loop_block_my_var_base_stack, block_my_var_base_ptr);
              }
              else if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_EVAL) {
                SPVM_DYNAMIC_ARRAY_push(sub_check_info->try_block_my_var_base_stack, block_my_var_base_ptr);
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
                  if (sub_check_info->loop_block_my_var_base_stack->length == 0) {
                    SPVM_yyerror_format(compiler, "next statement must be in loop block at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  break;
                }
                case SPVM_OP_C_CODE_LAST: {
                  if (sub_check_info->loop_block_my_var_base_stack->length == 0 && sub_check_info->op_switch_stack->length == 0) {
                    SPVM_yyerror_format(compiler, "last statement must be in loop block or switch block at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  break;
                }
                case SPVM_OP_C_CODE_POP: {
                  if (op_cur->first->code == SPVM_OP_C_CODE_CALL_SUB) {
                    SPVM_OP* op_call_sub = op_cur->first;
                    
                    const char* sub_name = op_call_sub->uv.name_info->resolved_name;
                    
                    SPVM_OP* op_sub= SPVM_HASH_search(
                      compiler->op_sub_symtable,
                      sub_name,
                      strlen(sub_name)
                    );
                    SPVM_SUB* sub = op_sub->uv.sub;
                    
                    if (sub->op_return_type->uv.type->code == SPVM_TYPE_C_CODE_VOID) {
                      op_cur->code = SPVM_OP_C_CODE_NULL;
                    }
                  }
                  else if (op_cur->first->code == SPVM_OP_C_CODE_ASSIGN) {
                    op_cur->code = SPVM_OP_C_CODE_NULL;
                  }
                  else if (op_cur->first->code == SPVM_OP_C_CODE_VAR) {
                    op_cur->code = SPVM_OP_C_CODE_NULL;
                    op_cur->first->code = SPVM_OP_C_CODE_NULL;
                  }
                  else if (op_cur->first->code == SPVM_OP_C_CODE_ASSIGN_PROCESS && op_cur->first->first->code  == SPVM_OP_C_CODE_VAR) {
                    op_cur->code = SPVM_OP_C_CODE_NULL;
                    op_cur->first->first->code = SPVM_OP_C_CODE_NULL;
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
                  
                  double range = (double) max - (double) min;
                  
                  int32_t code;
                  if (4.0 + range <= (3.0 + 2.0 * (double) length) * 1.5) {
                    code = SPVM_SWITCH_INFO_C_CODE_TABLE_SWITCH;
                  }
                  else {
                    code = SPVM_SWITCH_INFO_C_CODE_LOOKUP_SWITCH;
                  }
                  
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
                case SPVM_OP_C_CODE_EQ: {
                  SPVM_OP* op_first = op_cur->first;
                  SPVM_OP* op_last = op_cur->last;
                  
                  // term == term
                  if (op_first->code != SPVM_OP_C_CODE_UNDEF && op_last->code != SPVM_OP_C_CODE_UNDEF) {
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
                    // core == OBJ
                    else if (SPVM_TYPE_is_numeric(compiler, first_type)) {
                      SPVM_yyerror_format(compiler, "== left value must be object at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                    // OBJ == core
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

                  // term == term
                  if (op_first->code != SPVM_OP_C_CODE_UNDEF && op_last->code != SPVM_OP_C_CODE_UNDEF) {
                    SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                    SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);

                    // core == core
                    if (SPVM_TYPE_is_numeric(compiler, first_type) && SPVM_TYPE_is_numeric(compiler, last_type)) {
                      if (first_type->code != last_type->code) {
                        SPVM_yyerror_format(compiler, "!= operator two operands must be same type at %s line %d\n", op_cur->file, op_cur->line);
                        compiler->fatal_error = 1;
                        return;
                      }
                    }
                    // core == OBJ
                    else if (SPVM_TYPE_is_numeric(compiler, first_type)) {
                      SPVM_yyerror_format(compiler, "!= left value must be object at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                    // OBJ == core
                    else if (SPVM_TYPE_is_numeric(compiler, last_type)) {
                      SPVM_yyerror_format(compiler, "!= right value must be object at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                  }
                  // term == undef
                  else if (op_first->code != SPVM_OP_C_CODE_UNDEF && op_last->code == SPVM_OP_C_CODE_UNDEF) {
                    SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);

                    if (SPVM_TYPE_is_numeric(compiler, first_type)) {
                      SPVM_yyerror_format(compiler, "!= left value must be object at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                  }
                  // undef == term
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
                  
                  // Can receive only core type
                  if (!SPVM_TYPE_is_numeric(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "< left value must be core type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  if (!SPVM_TYPE_is_numeric(compiler, last_type)) {
                    SPVM_yyerror_format(compiler, "< right value must be core type at %s line %d\n", op_cur->file, op_cur->line);
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
                                  
                  // Can receive only core type
                  if (!SPVM_TYPE_is_numeric(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "<= left value must be core type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  if (!SPVM_TYPE_is_numeric(compiler, last_type)) {
                    SPVM_yyerror_format(compiler, "<= right value must be core type at %s line %d\n", op_cur->file, op_cur->line);
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
                  
                  // Can receive only core type
                  if (!SPVM_TYPE_is_numeric(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "> left value must be core type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  if (!SPVM_TYPE_is_numeric(compiler, last_type)) {
                    SPVM_yyerror_format(compiler, "> right value must be core type at %s line %d\n", op_cur->file, op_cur->line);
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
                  
                  // Can receive only core type
                  if (SPVM_TYPE_is_numeric(compiler, first_type) && !SPVM_TYPE_is_numeric(compiler, last_type)) {
                    SPVM_yyerror_format(compiler, ">= left value must be core type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  if (!SPVM_TYPE_is_numeric(compiler, first_type) && SPVM_TYPE_is_numeric(compiler, last_type)) {
                    SPVM_yyerror_format(compiler, ">= right value must be core type at %s line %d\n", op_cur->file, op_cur->line);
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
                  
                  // Can receive only core type
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
                  
                  // Can receive only core type
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
                  
                  // Can receive only core type
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
                          "new operator can't receive core type at %s line %d\n", op_cur->file, op_cur->line);
                        compiler->fatal_error = 1;
                        return;
                      }
                    }
                  }
                  else if (op_cur->first->code == SPVM_OP_C_CODE_CONSTANT) {
                    // Constant string
                  }
                  else {
                    assert(0);
                  }
                  
                  // If NEW is not rvalue, temparary variable is created, and assinged.
                  if (!op_cur->rvalue) {
                    
                    // Create temporary variable
                    SPVM_TYPE* var_type = SPVM_OP_get_type(compiler, op_cur->first);
                    SPVM_OP* op_var_tmp = SPVM_OP_CHECKEKR_new_op_var_tmp(compiler, var_type, sub_check_info, op_cur->file, op_cur->line);
                    if (op_var_tmp == NULL) {
                      return;
                    }
                    
                    // Cut new op
                    SPVM_OP* op_new = op_cur;
                    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_new);

                    // Assing op
                    SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ASSIGN, op_cur->file, op_cur->line);
                    SPVM_OP* op_build_assign = SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_new);
                    
                    // Convert cur new op to var
                    SPVM_OP_replace_op(compiler, op_stab, op_build_assign);
                    
                    op_cur = op_new;
                  }

                  break;
                }
                case SPVM_OP_C_CODE_BIT_XOR: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                  
                  // Can receive only core type
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
                  
                  // Can receive only core type
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
                  
                  // Can receive only core type
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
                  
                  // Check left term
                  if (op_cur->first->code == SPVM_OP_C_CODE_VAR
                    || op_cur->first->code == SPVM_OP_C_CODE_ARRAY_ELEM
                    || op_cur->first->code == SPVM_OP_C_CODE_CALL_FIELD
                    || op_cur->first->code == SPVM_OP_C_CODE_EXCEPTION_VAR
                  )
                  {
                    SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                    SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_cur->last);
                    
                    // Type inference
                    if (!first_type) {
                      SPVM_OP* op_var = op_cur->first;
                      SPVM_MY_VAR* my_var = op_var->uv.var->op_my_var->uv.my_var;
                      first_type = last_type;
                      
                      if (last_type) {
                        my_var->op_type->uv.type = last_type;
                      }
                      else {
                        SPVM_yyerror_format(compiler, "Type can't be detected at %s line %d\n", op_cur->first->file, op_cur->first->line);
                        compiler->fatal_error = 1;
                        return;
                      }
                    }
                    
                    // It is OK that left type is object and right is undef
                    if (!SPVM_TYPE_is_numeric(compiler, first_type) && !last_type) {
                      // OK
                    }
                    // Invalid type
                    else if (first_type->code != last_type->code) {
                      SPVM_yyerror_format(compiler, "Invalid type value is assigned at %s line %d\n", op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                  }
                  else {
                    SPVM_yyerror_format(compiler, "Can't assign to left at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
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
                  
                  // Must be int, long, float, double
                  if (!SPVM_TYPE_is_numeric(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "Type of - operator right value must be int, long, float, double at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_PLUS: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  
                  // Must be int, long, float, double
                  if (!SPVM_TYPE_is_numeric(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "Type of + operator right value must be int, long, float, double at %s line %d\n", op_cur->file, op_cur->line);
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
                    SPVM_yyerror_format(compiler, "Type of + operator left and right value must be same at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                                                  
                  // Value must be int, long, float, double
                  if (!SPVM_TYPE_is_numeric(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "Type of + operator left and right value must be core type at %s line %d\n", op_cur->file, op_cur->line);
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
                    SPVM_yyerror_format(compiler, "Type of - operator left and right value must be same at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                                                  
                  // Value must be int, long, float, double
                  if (!SPVM_TYPE_is_numeric(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "Type of - operator left and right value must be core type at %s line %d\n", op_cur->file, op_cur->line);
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
                  
                  if (!op_cur->rvalue) {
                    // Create temporary variable
                    SPVM_TYPE* var_type = SPVM_TYPE_get_string_type(compiler);
                    SPVM_OP* op_var_tmp = SPVM_OP_CHECKEKR_new_op_var_tmp(compiler, var_type, sub_check_info, op_cur->file, op_cur->line);
                    if (op_var_tmp == NULL) {
                      return;
                    }
                    
                    // Cut new op
                    SPVM_OP* op_concat_string = op_cur;
                    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_concat_string);

                    // Assing op
                    SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ASSIGN, op_cur->file, op_cur->line);
                    SPVM_OP* op_build_assign = SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_concat_string);
                    
                    // Convert cur new op to var
                    SPVM_OP_replace_op(compiler, op_stab, op_build_assign);
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
                    
                    {
                      // Create temporary variable for concat_string2
                      SPVM_TYPE* var_type = SPVM_TYPE_get_string_type(compiler);
                      SPVM_OP* op_var_tmp = SPVM_OP_CHECKEKR_new_op_var_tmp(compiler, var_type, sub_check_info, op_cur->file, op_cur->line);
                      if (op_var_tmp == NULL) {
                        return;
                      }
                      
                      // Cut new op
                      SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_concat_string2);

                      // Assing op
                      SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ASSIGN, op_cur->file, op_cur->line);
                      SPVM_OP* op_build_assign = SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_concat_string2);
                      
                      // Convert cur new op to var
                      SPVM_OP_replace_op(compiler, op_stab, op_build_assign);
                    }

                    {
                      // Create temporary variable for new
                      SPVM_TYPE* var_type = SPVM_TYPE_get_string_type(compiler);
                      SPVM_OP* op_var_tmp = SPVM_OP_CHECKEKR_new_op_var_tmp(compiler, var_type, sub_check_info, op_cur->file, op_cur->line);
                      if (op_var_tmp == NULL) {
                        return;
                      }
                      
                      // Cut new op
                      SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_build_constant);

                      // Assing op
                      SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ASSIGN, op_cur->file, op_cur->line);
                      SPVM_OP* op_build_assign = SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_build_constant);
                      
                      // Convert cur new op to var
                      SPVM_OP_replace_op(compiler, op_stab, op_build_assign);
                    }                    
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
                    SPVM_yyerror_format(compiler, "Type of * operator left and right value must be same at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                                                  
                  // Value must be int, long, float, double
                  if (!SPVM_TYPE_is_numeric(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "Type of * operator left and right value must be core type at %s line %d\n", op_cur->file, op_cur->line);
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
                    SPVM_yyerror_format(compiler, "Type of / operator left and right value must be same at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                                                  
                  // Value must be int, long, float, double
                  if (!SPVM_TYPE_is_numeric(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "Type of / operator left and right value must be core type at %s line %d\n", op_cur->file, op_cur->line);
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
                    SPVM_yyerror_format(compiler, "Type of % operator left and right value must be same at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                                                  
                  // Value must be int, long, float, double
                  if (!SPVM_TYPE_is_numeric(compiler, first_type)) {
                    SPVM_yyerror_format(compiler, "Type of % operator left and right value must be core type at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_CROAK: {
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_cur->first);
                  
                  if (!first_type || first_type->code != SPVM_TYPE_C_CODE_STRING) {
                    SPVM_yyerror_format(compiler, "croak argument type must be String at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  break;
                }
                case SPVM_OP_C_CODE_PRE_INC:
                case SPVM_OP_C_CODE_POST_INC:
                case SPVM_OP_C_CODE_PRE_DEC:
                case SPVM_OP_C_CODE_POST_DEC: {
                  SPVM_OP* op_first = op_cur->first;
                  if (op_first->code != SPVM_OP_C_CODE_VAR) {
                    SPVM_yyerror_format(compiler, "invalid lvalue in increment at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_first);
                  
                  // Only int or long
                  if (first_type->code > SPVM_TYPE_C_CODE_LONG) {
                    SPVM_yyerror_format(compiler, "Type of increment or decrement target must be integral at %s line %d\n", op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  op_cur->first->lvalue = 1;
                  
                  break;
                }
                case SPVM_OP_C_CODE_LOOP: {
                  // Exchange condition and loop block to move condition to end of block
                  SPVM_OP* op_condition = op_cur->first;
                  SPVM_OP* op_block_loop = op_cur->last;
                  op_cur->first = op_block_loop;
                  op_cur->last = op_condition;
                  op_block_loop->moresib = 1;
                  op_block_loop->sibparent = op_condition;
                  op_condition->moresib = 0;
                  op_condition->sibparent = op_cur;
                  break;
                }
                // End of scope
                case SPVM_OP_C_CODE_BLOCK: {
                  // Pop block my variable base
                  assert(sub_check_info->block_my_var_base_stack->length > 0);
                  int32_t* block_my_var_base_ptr = SPVM_DYNAMIC_ARRAY_pop(sub_check_info->block_my_var_base_stack);
                  sub_check_info->block_my_var_base = *block_my_var_base_ptr;

                  // Pop loop block my variable base
                  if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_LOOP) {
                    assert(sub_check_info->loop_block_my_var_base_stack->length > 0);
                    SPVM_DYNAMIC_ARRAY_pop(sub_check_info->loop_block_my_var_base_stack);
                  }
                  // Pop try block my variable base
                  else if (op_cur->flag & SPVM_OP_C_FLAG_BLOCK_EVAL) {
                    assert(sub_check_info->try_block_my_var_base_stack->length > 0);
                    SPVM_DYNAMIC_ARRAY_pop(sub_check_info->try_block_my_var_base_stack);
                  }
                  
                  if (sub_check_info->block_my_var_base_stack->length > 0) {
                    int32_t* before_block_my_var_base_ptr = SPVM_DYNAMIC_ARRAY_fetch(
                      sub_check_info->block_my_var_base_stack,
                      sub_check_info->block_my_var_base_stack->length - 1
                    );
                    int32_t before_block_my_var_base = *before_block_my_var_base_ptr;
                    sub_check_info->block_my_var_base = before_block_my_var_base;
                  }
                  else {
                    sub_check_info->block_my_var_base = 0;
                  }
                  
                  break;
                }
                // Add my var
                case SPVM_OP_C_CODE_VAR: {
                  
                  SPVM_VAR* var = op_cur->uv.var;
                  
                  // Search same name variable
                  SPVM_OP* op_my_var = NULL;
                  {
                    int32_t i;
                    for (i = sub_check_info->op_my_var_stack->length; i-- > 0; ) {
                      SPVM_OP* op_my_var_tmp = SPVM_DYNAMIC_ARRAY_fetch(sub_check_info->op_my_var_stack, i);
                      SPVM_MY_VAR* my_var_tmp = op_my_var_tmp->uv.my_var;
                      if (strcmp(var->op_name->uv.name, my_var_tmp->op_name->uv.name) == 0) {
                        op_my_var = op_my_var_tmp;
                        break;
                      }
                    }
                  }
                  
                  if (op_my_var) {
                    // Add my var information to var
                    var->op_my_var = op_my_var;
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
                  SPVM_MY_VAR* my_var = op_cur->uv.my_var;
                  
                  assert(sub_check_info->my_var_length <= SPVM_LIMIT_C_MY_VARS);
                  if (sub_check_info->my_var_length == SPVM_LIMIT_C_MY_VARS) {
                    SPVM_yyerror_format(compiler, "too many lexical variables, my \"%s\" ignored at %s line %d\n", my_var->op_name->uv.name, op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Search same name variable
                  _Bool found = 0;
                  
                  {
                    int32_t i;
                    for (i = sub_check_info->op_my_var_stack->length; i-- > sub_check_info->block_my_var_base; ) {
                      SPVM_OP* op_bef_my_var = SPVM_DYNAMIC_ARRAY_fetch(sub_check_info->op_my_var_stack, i);
                      SPVM_MY_VAR* bef_my_var = op_bef_my_var->uv.my_var;
                      if (strcmp(my_var->op_name->uv.name, bef_my_var->op_name->uv.name) == 0) {
                        found = 1;
                        break;
                      }
                    }
                  }
                  
                  if (found) {
                    SPVM_yyerror_format(compiler, "redeclaration of my \"%s\" at %s line %d\n", my_var->op_name->uv.name, op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  else {
                    my_var->index = sub_check_info->my_var_length++;
                    SPVM_DYNAMIC_ARRAY_push(sub_check_info->op_my_vars, op_cur);
                    SPVM_DYNAMIC_ARRAY_push(sub_check_info->op_my_var_stack, op_cur);
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_CALL_SUB: {
                  
                  // Check sub name
                  SPVM_OP_resolve_sub_name(compiler, op_package, op_cur);
                  
                  SPVM_OP* op_list_args = op_cur->last;
                  
                  SPVM_NAME_INFO* name_info = op_cur->uv.name_info;
                  
                  const char* sub_abs_name = name_info->resolved_name;
                  
                  SPVM_OP* found_op_sub= SPVM_HASH_search(
                    compiler->op_sub_symtable,
                    sub_abs_name,
                    strlen(sub_abs_name)
                  );
                  if (!found_op_sub) {
                    SPVM_yyerror_format(compiler, "unknown sub \"%s\" at %s line %d\n",
                      sub_abs_name, op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Constant
                  SPVM_SUB* found_sub = found_op_sub->uv.sub;

                  int32_t sub_args_count = found_sub->op_args->length;
                  SPVM_OP* op_term = op_list_args->first;
                  int32_t call_sub_args_count = 0;
                  while ((op_term = SPVM_OP_sibling(compiler, op_term))) {
                    call_sub_args_count++;
                    if (call_sub_args_count > sub_args_count) {
                      SPVM_yyerror_format(compiler, "Too may arguments. sub \"%s\" at %s line %d\n", sub_abs_name, op_cur->file, op_cur->line);
                      compiler->fatal_error = 1;
                      return;
                    }
                    
                    _Bool is_invalid = 0;
                    
                    SPVM_OP* op_sub_arg_my_var = SPVM_DYNAMIC_ARRAY_fetch(found_sub->op_args, call_sub_args_count - 1);
                    
                    SPVM_TYPE* sub_arg_type = SPVM_OP_get_type(compiler, op_sub_arg_my_var);
                    
                    // Undef
                    if (op_term->code == SPVM_OP_C_CODE_UNDEF) {
                      if (SPVM_TYPE_is_numeric(compiler, sub_arg_type)) {
                        is_invalid = 1;
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
                      SPVM_yyerror_format(compiler, "Type of %d argument must be %s(%s()) at %s line %d\n", (int)call_sub_args_count, sub_arg_type->name, sub_abs_name, op_cur->file, op_cur->line);
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
                  if (found_sub->is_constant) {
                    // Replace sub to constant
                    op_cur->code = SPVM_OP_C_CODE_CONSTANT;
                    op_cur->uv.constant = found_sub->op_constant->uv.constant;
                    
                    op_cur->first = NULL;
                    op_cur->last = NULL;
                    break;
                  }
                  
                  SPVM_TYPE* return_type = SPVM_OP_get_type(compiler, found_op_sub->uv.sub->op_return_type);
                  
                  // If CALL_SUB is is not rvalue and return type is object, temparary variable is created, and assinged.
                  if (!op_cur->rvalue && (return_type->code != SPVM_TYPE_C_CODE_VOID && !SPVM_TYPE_is_numeric(compiler, return_type))) {

                    // Create temporary variable
                    SPVM_TYPE* var_type = SPVM_OP_get_type(compiler, found_sub->op_return_type);
                    SPVM_OP* op_var_tmp = SPVM_OP_CHECKEKR_new_op_var_tmp(compiler, var_type, sub_check_info, op_cur->file, op_cur->line);
                    if (op_var_tmp == NULL) {
                      return;
                    }
                    
                    // New op
                    SPVM_OP* op_call_sub = op_cur;
                    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_call_sub);

                    // Assing op
                    SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ASSIGN, op_cur->file, op_cur->line);
                    SPVM_OP* op_build_assign = SPVM_OP_build_assign(compiler, op_assign, op_var_tmp, op_call_sub);
                    
                    // Convert cur call_sub op to var
                    SPVM_OP_replace_op(compiler, op_stab, op_build_assign);
                    op_call_sub->uv.name_info = name_info;
                    
                    op_cur = op_call_sub;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_CALL_FIELD: {
                  SPVM_OP* op_term = op_cur->first;
                  SPVM_OP* op_name = op_cur->last;
                  
                  if (op_term->code == SPVM_OP_C_CODE_ASSIGN_PROCESS) {
                    op_term = op_term->first;
                  }
                  
                  if (op_term->code != SPVM_OP_C_CODE_VAR
                    && op_term->code != SPVM_OP_C_CODE_ARRAY_ELEM
                    && op_term->code != SPVM_OP_C_CODE_CALL_FIELD
                    && op_term->code != SPVM_OP_C_CODE_CALL_SUB
                    && op_term->code != SPVM_OP_C_CODE_NEW)
                  {
                    SPVM_yyerror_format(compiler, "field invoker is invalid \"%s\" at %s line %d\n",
                      op_name->uv.name, op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  // Check field name
                  SPVM_OP_resolve_field_name(compiler, op_cur);
                  
                  const char* field_abs_name = op_cur->uv.name_info->resolved_name;
                  
                  SPVM_OP* found_op_field= SPVM_HASH_search(
                    compiler->op_field_symtable,
                    field_abs_name,
                    strlen(field_abs_name)
                  );
                  if (!found_op_field) {
                    SPVM_yyerror_format(compiler, "unknown field \"%s\" at %s line %d\n",
                      field_abs_name, op_cur->file, op_cur->line);
                    compiler->fatal_error = 1;
                    return;
                  }
                  
                  break;
                }
                case SPVM_OP_C_CODE_WEAKEN_FIELD: {
                  SPVM_OP* op_call_field = op_cur->first;
                  const char* field_abs_name = op_call_field->uv.name_info->resolved_name;
                  
                  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_call_field);
                  
                  if (type->code <= SPVM_TYPE_C_CODE_DOUBLE) {
                    SPVM_yyerror_format(compiler, "weaken is only used for object field \"%s\" at %s line %d\n",
                      field_abs_name, op_cur->file, op_cur->line);
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
        sub->op_my_vars = sub_check_info->op_my_vars;
        
        // Operand stack max
        sub->operand_stack_max = sub_check_info->op_count * 2;
      }

      assert(sub->file_name);
      
    }
  }
}
