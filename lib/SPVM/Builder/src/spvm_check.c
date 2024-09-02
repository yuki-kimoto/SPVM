// Copyright (c) 2023 Yuki Kimoto
// MIT License

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
#include "spvm_check.h"
#include "spvm_method.h"
#include "spvm_constant.h"
#include "spvm_field.h"
#include "spvm_var_decl.h"
#include "spvm_var.h"
#include "spvm_type.h"
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
#include "spvm_string_buffer.h"
#include "spvm_use.h"
#include "spvm_interface.h"
#include "spvm_string.h"
#include "spvm_attribute.h"
#include "spvm_dumper.h"
#include "spvm_allow.h"

void SPVM_CHECK_check(SPVM_COMPILER* compiler) {
  // Check type ops
  SPVM_CHECK_check_op_types(compiler);
  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
    return;
  }
  
  // Check basic types
  SPVM_CHECK_check_basic_types(compiler);
  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
    return;
  }
  
#ifdef SPVM_DEBUG_COMPILE
  if (SPVM_COMPILER_get_error_messages_length(compiler) == 0) {
    fprintf(stderr, "\n[Basic types]\n");
    SPVM_DUMPER_dump_basic_types(compiler, compiler->basic_types);
  }
#endif
}

void SPVM_CHECK_check_basic_types(SPVM_COMPILER* compiler) {
  
  SPVM_CHECK_check_basic_types_relation(compiler);
  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
    return;
  }
  
  SPVM_CHECK_check_class_vars(compiler);
  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
    return;
  }
  
  SPVM_CHECK_check_fields(compiler);
  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
    return;
  }
  
  SPVM_CHECK_check_methods(compiler);
  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
    return;
  }
  
  SPVM_CHECK_check_asts(compiler);
  if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
    return;
  }
}

void SPVM_CHECK_check_basic_types_relation(SPVM_COMPILER* compiler) {
  for (int32_t basic_type_id = compiler->basic_types_base_id; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    
    const char* basic_type_name = basic_type->name;
    
    const char* parent_basic_type_name = basic_type->parent_name;
    if (parent_basic_type_name) {
      SPVM_BASIC_TYPE* parent_basic_type = SPVM_HASH_get(compiler->basic_type_symtable, parent_basic_type_name, strlen(parent_basic_type_name));

      if (!SPVM_BASIC_TYPE_is_class_type(compiler, parent_basic_type->id)) {
        SPVM_COMPILER_error(compiler, "The parant class must be a class type.\n  at %s line %d", basic_type->op_extends->file, basic_type->op_extends->line);
        return;
      }
      if (!SPVM_BASIC_TYPE_is_class_type(compiler, basic_type->id)) {
        SPVM_COMPILER_error(compiler, "The current class must be a class type when the class becomes a child class.\n  at %s line %d", basic_type->op_extends->file, basic_type->op_extends->line);
        return;
      }
      
      if (strcmp(basic_type->name, parent_basic_type->name) == 0) {
        SPVM_COMPILER_error(compiler, "The name of the parant class must be different from the name of the class.\n  at %s line %d", basic_type->op_extends->file, basic_type->op_extends->line);
        return;
      }
      basic_type->parent = parent_basic_type;
    }
    
    // Add interface_basic_types
    for (int32_t i = 0; i < basic_type->interface_decls->length; i++) {
      SPVM_INTERFACE* interface_decl = SPVM_LIST_get(basic_type->interface_decls, i);
      SPVM_BASIC_TYPE* interface_basic_type = SPVM_HASH_get(compiler->basic_type_symtable, interface_decl->op_type->uv.type->unresolved_basic_type_name, strlen(interface_decl->op_type->uv.type->unresolved_basic_type_name));
      
      if (!SPVM_BASIC_TYPE_is_interface_type(compiler, interface_basic_type->id)) {
        SPVM_COMPILER_error(compiler, "The interface specified by the interface statement must be an interface type.\n  at %s line %d", interface_decl->op_interface->file, interface_decl->op_interface->line);
        return;
      }
      
      SPVM_LIST_push(basic_type->interface_basic_types, interface_basic_type);
      SPVM_HASH_set(basic_type->interface_basic_symtable, interface_basic_type->name, strlen(interface_basic_type->name), interface_basic_type);
    }
  }
  
  for (int32_t basic_type_id = compiler->basic_types_base_id; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    SPVM_BASIC_TYPE* parent_basic_type = basic_type->parent;
    while (1) {
      if (parent_basic_type) {
        if (strcmp(parent_basic_type->name, basic_type->name) == 0) {
          SPVM_COMPILER_error(compiler, "Recursive inheritance. Found the current class %s in a super class.\n  at %s line %d", basic_type->name, basic_type->op_extends->file, basic_type->op_extends->line);
          return;
        }
        parent_basic_type = parent_basic_type->parent;
      }
      else {
        break;
      }
    }
  }
  
  for (int32_t basic_type_id = compiler->basic_types_base_id; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    // Merge inheritance
    SPVM_LIST* basic_type_merge_stack = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
    SPVM_LIST_push(basic_type_merge_stack, basic_type);
    
    SPVM_LIST* merged_interface_basic_types = SPVM_LIST_new_list_permanent(compiler->current_each_compile_allocator, 0);
    
    SPVM_BASIC_TYPE* parent_basic_type = basic_type->parent;
    while (1) {
      if (parent_basic_type) {
        SPVM_LIST_push(basic_type_merge_stack, parent_basic_type);
        parent_basic_type = parent_basic_type->parent;
      }
      else {
        break;
      }
    }
    
    SPVM_BASIC_TYPE* current_basic_type = basic_type;
    for (int32_t basic_type_id = basic_type_merge_stack->length - 1; basic_type_id >= 0; basic_type_id--) {
      SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(basic_type_merge_stack, basic_type_id);
      
      // All interface_basic_types
      SPVM_LIST* interface_basic_types = basic_type->interface_basic_types;
      for (int32_t interface_index = 0; interface_index < interface_basic_types->length; interface_index++) {
        SPVM_BASIC_TYPE* interface_basic_type = SPVM_LIST_get(interface_basic_types, interface_index);
        SPVM_LIST_push(merged_interface_basic_types, interface_basic_type);
      }
    }
    
    // Add parent interface_basic_types
    basic_type->interface_basic_types = merged_interface_basic_types;
    for (int32_t i = 0; i < merged_interface_basic_types->length; i++) {
      SPVM_BASIC_TYPE* interface_basic_type = SPVM_LIST_get(merged_interface_basic_types, i);
      SPVM_BASIC_TYPE* found_interface_basic_type = SPVM_HASH_get(basic_type->interface_basic_symtable, interface_basic_type->name, strlen(interface_basic_type->name));
      if (!found_interface_basic_type) {
        SPVM_LIST_push(basic_type->interface_basic_types, interface_basic_type);
        SPVM_HASH_set(basic_type->interface_basic_symtable, interface_basic_type->name, strlen(interface_basic_type->name), interface_basic_type);
      }
    }
    
    SPVM_LIST_free(basic_type_merge_stack);
  }
  
  // Outer class
  for (int32_t basic_type_id = compiler->basic_types_base_id; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    
    for (int32_t method_index = 0; method_index < basic_type->methods->length; method_index++) {
      SPVM_METHOD* method = SPVM_LIST_get(basic_type->methods, method_index);
      
      if (method->current_basic_type->is_generated_by_anon_method) {
        char* found_ptr = strstr(basic_type->name, "::anon_method::");
        assert(found_ptr);
        int32_t outmost_basic_type_name_length = (int32_t)(found_ptr - basic_type->name);
        
        SPVM_BASIC_TYPE* outmost_basic_type = SPVM_HASH_get(compiler->basic_type_symtable, basic_type->name, outmost_basic_type_name_length);
        assert(outmost_basic_type);
        
        basic_type->outmost = outmost_basic_type;
      }
    }
  }
}

void SPVM_CHECK_check_class_vars(SPVM_COMPILER* compiler) {
  
  for (int32_t basic_type_id = compiler->basic_types_base_id; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    int32_t compile_error = 0;
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    const char* basic_type_name = basic_type->name;
    
    // Check class var
    for (int32_t class_var_index = 0; class_var_index < basic_type->class_vars->length; class_var_index++) {
      SPVM_CLASS_VAR* class_var = SPVM_LIST_get(basic_type->class_vars, class_var_index);
      SPVM_TYPE* class_var_type = class_var->type;
      int32_t is_mulnum_t = SPVM_TYPE_is_mulnum_type(compiler, class_var_type->basic_type->id, class_var_type->dimension, class_var_type->flag);
      
      // valut_t cannnot become class variable
      if (is_mulnum_t) {
        SPVM_COMPILER_error(compiler, "The multi-numeric type cannnot used in the definition of the class variable.\n  at %s line %d", class_var->op_class_var->file, class_var->op_class_var->line);
        return;
      }
    }
  }
}

void SPVM_CHECK_check_fields(SPVM_COMPILER* compiler) {
  for (int32_t basic_type_id = compiler->basic_types_base_id; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    int32_t compile_error = 0;
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    const char* basic_type_name = basic_type->name;
    
    // Check class var
    for (int32_t class_var_index = 0; class_var_index < basic_type->class_vars->length; class_var_index++) {
      SPVM_CLASS_VAR* class_var = SPVM_LIST_get(basic_type->class_vars, class_var_index);
      SPVM_TYPE* class_var_type = class_var->type;
      int32_t is_mulnum_t = SPVM_TYPE_is_mulnum_type(compiler, class_var_type->basic_type->id, class_var_type->dimension, class_var_type->flag);
      
      // valut_t cannnot become class variable
      if (is_mulnum_t) {
        SPVM_COMPILER_error(compiler, "The multi-numeric type cannnot used in the definition of the class variable.\n  at %s line %d", class_var->op_class_var->file, class_var->op_class_var->line);
        return;
      }
    }
    
    // Class variable
    for (int32_t i = 0; i < basic_type->class_vars->length; i++) {
      SPVM_CLASS_VAR* class_var = SPVM_LIST_get(basic_type->class_vars, i);
      
      class_var->index = i;
    }
    
    // Multi-numeric type limitation
    if (basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM) {
      SPVM_LIST* fields = basic_type->unmerged_fields;
      SPVM_FIELD* first_field = SPVM_LIST_get(fields, 0);
      SPVM_TYPE* first_field_type = first_field->type;
      if (!SPVM_TYPE_is_numeric_type(compiler, first_field_type->basic_type->id, first_field_type->dimension, first_field_type->flag)) {
        SPVM_COMPILER_error(compiler, "The multi-numeric type must have the only fields of numeric types.\n  at %s line %d", first_field->op_field->file, first_field->op_field->line);
        return;
      }
      
      int32_t field_index;
      for (field_index = 0; field_index < basic_type->unmerged_fields->length; field_index++) {
        SPVM_FIELD* field = SPVM_LIST_get(fields, field_index);
        SPVM_TYPE* field_type = field->type;
        if (!(field_type->basic_type->id == first_field_type->basic_type->id && field_type->dimension == first_field_type->dimension)) {
          SPVM_COMPILER_error(compiler, "The fields of the multi-numeric type must be of the same type.\n  at %s line %d", field_type->basic_type->name, field->op_field->file, field->op_field->line);
          return;
        }
      }
      
      // Check type name
      char* tail_name = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->current_each_compile_allocator, 255);
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
      int32_t basic_type_name_length = strlen(basic_type_name);
      
      char* found_pos_ptr = strstr(basic_type_name + basic_type_name_length - tail_name_length, tail_name);
      if (!found_pos_ptr) {
        SPVM_COMPILER_error(compiler, "The name of the multi-numeric type %s must end with with %s.\n  at %s line %d", basic_type->name, tail_name, basic_type->op_class->file, basic_type->op_class->line);
        return;
      }
    }
    
    // Check fields
    for (int32_t field_index = 0; field_index < basic_type->unmerged_fields->length; field_index++) {
      SPVM_FIELD* field = SPVM_LIST_get(basic_type->unmerged_fields, field_index);
      SPVM_TYPE* field_type = field->type;

      // valut_t cannnot become field
      int32_t is_mulnum_t = SPVM_TYPE_is_mulnum_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag);
      if (is_mulnum_t) {
        SPVM_COMPILER_error(compiler, "The multi-numeric type cannnot used in the definition of the field.\n  at %s line %d", field->op_field->file, field->op_field->line);
        return;
      }
    }
    
    {
      // Merge fields
      SPVM_LIST* basic_type_merge_stack = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
      SPVM_LIST_push(basic_type_merge_stack, basic_type);
      
      SPVM_LIST* merged_fields = SPVM_LIST_new_list_permanent(compiler->current_each_compile_allocator, 0);
      
      SPVM_BASIC_TYPE* parent_basic_type = basic_type->parent;
      while (1) {
        if (parent_basic_type) {
          SPVM_LIST_push(basic_type_merge_stack, parent_basic_type);
          parent_basic_type = parent_basic_type->parent;
        }
        else {
          break;
        }
      }
      
      SPVM_BASIC_TYPE* current_basic_type = basic_type;
      int32_t merged_fields_index = 0;
      for (int32_t basic_type_id = basic_type_merge_stack->length - 1; basic_type_id >= 0; basic_type_id--) {
        SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(basic_type_merge_stack, basic_type_id);
        
        SPVM_LIST* fields = basic_type->unmerged_fields;
        int32_t field_index = 0;
        int32_t fields_length = fields->length;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_FIELD* field = SPVM_LIST_get(fields, field_index);

          SPVM_FIELD* found_field_in_super_class = SPVM_CHECK_search_unmerged_field(compiler, basic_type->parent, field->name);
          if (found_field_in_super_class) {
            SPVM_COMPILER_error(compiler, "%s field cannot be defined in %s class. This field is already defined in its super class.\n  at %s line %d", field->name, basic_type->name, field->op_field->file, field->op_field->line);
            compile_error = 1;
            break;
          }
          
          SPVM_FIELD* new_field;
          if (strcmp(field->current_basic_type->name, current_basic_type->name) == 0) {
            new_field = field;
          }
          // Clone field
          else {
            new_field = SPVM_FIELD_new(compiler);
            new_field->name = field->name;
            new_field->current_basic_type = current_basic_type;
            new_field->type = field->type;
            new_field->access_control_type = field->access_control_type;
            new_field->is_parent_field = field->is_parent_field;
          }
          SPVM_LIST_push(merged_fields, new_field);
          merged_fields_index++;
        }
        if (compile_error) {
          break;
        }
      }
      
      if (!(merged_fields->length <= 65535)) {
        SPVM_COMPILER_error(compiler, "The length of fields in %s class must be lower than 65535.\n  at %s line %d", basic_type->op_class->file, basic_type->op_class->line);
        return;
      }
      
      for (int32_t field_index = 0; field_index < merged_fields->length; field_index++) {
        SPVM_FIELD* field = SPVM_LIST_get(merged_fields, field_index);
        field->index = field_index;
        SPVM_HASH_set(basic_type->field_symtable, field->name, strlen(field->name), field);
      }
      
      basic_type->fields = merged_fields;
      
      // Resove field offset
      SPVM_CHECK_check_field_offset(compiler, basic_type);
      
      SPVM_LIST_free(basic_type_merge_stack);
      if (compile_error) {
        return;
      }
    }
    
  }
}

void SPVM_CHECK_check_methods(SPVM_COMPILER* compiler) {

  for (int32_t basic_type_id = compiler->basic_types_base_id; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    int32_t compile_error = 0;
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    const char* basic_type_name = basic_type->name;
    
    // Edit INIT block
    // The INIT mehtods that is the parent basic type and used basic types in the order.
    SPVM_METHOD* init_method = basic_type->init_method;
    if (init_method) {
      SPVM_OP* op_block = init_method->op_block;
      SPVM_OP* op_list_statement = op_block->first;
      
      SPVM_LIST* use_basic_type_names = basic_type->use_basic_type_names;
      
      for (int32_t i = use_basic_type_names->length - 1; i >= 0; i--) {
        const char* use_basic_type_name = SPVM_LIST_get(use_basic_type_names, i);
        
        SPVM_BASIC_TYPE* use_basic_type = SPVM_HASH_get(compiler->basic_type_symtable, use_basic_type_name, strlen(use_basic_type_name));
        if (use_basic_type) {
          if (use_basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS) {
            SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, op_block->file, op_block->line);
            SPVM_OP* op_name_invocant = SPVM_OP_new_op_name(compiler, use_basic_type_name, op_block->file, op_block->line);
            SPVM_OP* op_name_method = SPVM_OP_new_op_name(compiler, "INIT", op_block->file, op_block->line);
            SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, op_block->file, op_block->line);
            SPVM_OP* op_type_invocant = SPVM_OP_build_basic_type(compiler, op_name_invocant);
            SPVM_OP_build_call_method(compiler, op_call_method, op_type_invocant, op_name_method, op_operators);
            SPVM_OP_insert_child(compiler, op_list_statement, op_list_statement->first, op_call_method);
          }
        }
      }
      
      const char* parent_basic_type_name = basic_type->parent_name;
      if (parent_basic_type_name) {
        SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, op_block->file, op_block->line);
        SPVM_OP* op_name_invocant = SPVM_OP_new_op_name(compiler, parent_basic_type_name, op_block->file, op_block->line);
        SPVM_OP* op_name_method = SPVM_OP_new_op_name(compiler, "INIT", op_block->file, op_block->line);
        SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, op_block->file, op_block->line);
        SPVM_OP* op_type_invocant = SPVM_OP_build_basic_type(compiler, op_name_invocant);
        SPVM_OP_build_call_method(compiler, op_call_method, op_type_invocant, op_name_method, op_operators);
        SPVM_OP_insert_child(compiler, op_list_statement, op_list_statement->first, op_call_method);
      }
    }
    
    // Check methods
    SPVM_LIST* methods = basic_type->methods;
    for (int32_t i = 0; i < methods->length; i++) {
      SPVM_METHOD* method = SPVM_LIST_get(methods, i);
      
      // Argument limit check
      int32_t args_width = 0;
      SPVM_TYPE* last_arg_type = NULL;
      int32_t found_optional_arg = 0;
      for (int32_t arg_index = 0; arg_index < method->args_length; arg_index++) {
        SPVM_VAR_DECL* arg_var_decl = SPVM_LIST_get(method->var_decls, arg_index);
        
        SPVM_TYPE* arg_type = arg_var_decl->type;
        
        int32_t is_arg_type_is_mulnum_type = SPVM_TYPE_is_mulnum_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag);
        
        // Optional argument
        SPVM_OP* op_arg_default = arg_var_decl->op_arg_default;
        if (op_arg_default) {
          found_optional_arg = 1;
          arg_var_decl->is_optional_arg = 1;
          if (SPVM_TYPE_is_numeric_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag)) {
            if (op_arg_default->id != SPVM_OP_C_ID_CONSTANT) {
              SPVM_COMPILER_error(compiler, "The default value of the optional argument %s must be a constant value.\n  at %s line %d", arg_var_decl->var->name, method->op_method->file, method->op_method->line);
              return;
            }
            else {
              SPVM_TYPE* constant_type = SPVM_CHECK_get_type(compiler, op_arg_default);
              int32_t need_data_conversion = 0;
              int32_t allow_narrowing_conversion = SPVM_CHECK_check_allow_narrowing_conversion(compiler, arg_type, op_arg_default);
              int32_t interface_match = 0;
              char error_reason[1024] = {0};
              int32_t satisfy_assignment_requirement = SPVM_TYPE_satisfy_assignment_requirement(
                compiler,
                arg_type->basic_type->id, arg_type->dimension, arg_type->flag,
                constant_type->basic_type->id, constant_type->dimension, constant_type->flag,
                &need_data_conversion, allow_narrowing_conversion, interface_match,
                error_reason
              );
              
              if (!satisfy_assignment_requirement) {
                if (strlen(error_reason)) {
                  SPVM_COMPILER_error(compiler, error_reason);
                }
                
                SPVM_COMPILER_error(compiler, "The default value of the optional argument %s must be able to be assigned to the argument.\n  at %s line %d", arg_var_decl->var->name, method->op_method->file, method->op_method->line);
                return;
              }
            }
            
            switch (arg_type->basic_type->id) {
              case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                switch (op_arg_default->uv.constant->type->basic_type->id) {
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                    arg_var_decl->arg_default_value.bval = (int8_t)op_arg_default->uv.constant->value.bval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                    arg_var_decl->arg_default_value.bval = (int8_t)op_arg_default->uv.constant->value.sval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                    arg_var_decl->arg_default_value.bval = (int8_t)op_arg_default->uv.constant->value.ival;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                    arg_var_decl->arg_default_value.bval = (int8_t)op_arg_default->uv.constant->value.lval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                    arg_var_decl->arg_default_value.bval = (int8_t)op_arg_default->uv.constant->value.fval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                    arg_var_decl->arg_default_value.bval = (int8_t)op_arg_default->uv.constant->value.dval;
                    break;
                  }
                  default: {
                    assert(0);
                  }
                }
                
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                switch (op_arg_default->uv.constant->type->basic_type->id) {
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                    arg_var_decl->arg_default_value.sval = (int16_t)op_arg_default->uv.constant->value.bval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                    arg_var_decl->arg_default_value.sval = (int16_t)op_arg_default->uv.constant->value.sval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                    arg_var_decl->arg_default_value.sval = (int16_t)op_arg_default->uv.constant->value.ival;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                    arg_var_decl->arg_default_value.sval = (int16_t)op_arg_default->uv.constant->value.lval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                    arg_var_decl->arg_default_value.sval = (int16_t)op_arg_default->uv.constant->value.fval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                    arg_var_decl->arg_default_value.sval = (int16_t)op_arg_default->uv.constant->value.dval;
                    break;
                  }
                  default: {
                    assert(0);
                  }
                }
                
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                switch (op_arg_default->uv.constant->type->basic_type->id) {
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                    arg_var_decl->arg_default_value.ival = (int32_t)op_arg_default->uv.constant->value.bval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                    arg_var_decl->arg_default_value.ival = (int32_t)op_arg_default->uv.constant->value.sval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                    arg_var_decl->arg_default_value.ival = (int32_t)op_arg_default->uv.constant->value.ival;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                    arg_var_decl->arg_default_value.ival = (int32_t)op_arg_default->uv.constant->value.lval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                    arg_var_decl->arg_default_value.ival = (int32_t)op_arg_default->uv.constant->value.fval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                    arg_var_decl->arg_default_value.ival = (int32_t)op_arg_default->uv.constant->value.dval;
                    break;
                  }
                  default: {
                    assert(0);
                  }
                }
                
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                switch (op_arg_default->uv.constant->type->basic_type->id) {
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                    arg_var_decl->arg_default_value.lval = (int64_t)op_arg_default->uv.constant->value.bval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                    arg_var_decl->arg_default_value.lval = (int64_t)op_arg_default->uv.constant->value.sval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                    arg_var_decl->arg_default_value.lval = (int64_t)op_arg_default->uv.constant->value.ival;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                    arg_var_decl->arg_default_value.lval = (int64_t)op_arg_default->uv.constant->value.lval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                    arg_var_decl->arg_default_value.lval = (int64_t)op_arg_default->uv.constant->value.fval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                    arg_var_decl->arg_default_value.lval = (int64_t)op_arg_default->uv.constant->value.dval;
                    break;
                  }
                  default: {
                    assert(0);
                  }
                }
                
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                switch (op_arg_default->uv.constant->type->basic_type->id) {
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                    arg_var_decl->arg_default_value.fval = (float)op_arg_default->uv.constant->value.bval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                    arg_var_decl->arg_default_value.fval = (float)op_arg_default->uv.constant->value.sval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                    arg_var_decl->arg_default_value.fval = (float)op_arg_default->uv.constant->value.ival;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                    arg_var_decl->arg_default_value.fval = (float)op_arg_default->uv.constant->value.lval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                    arg_var_decl->arg_default_value.fval = (float)op_arg_default->uv.constant->value.fval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                    arg_var_decl->arg_default_value.fval = (float)op_arg_default->uv.constant->value.dval;
                    break;
                  }
                  default: {
                    assert(0);
                  }
                }
                
                break;
              }
              case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                switch (op_arg_default->uv.constant->type->basic_type->id) {
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                    arg_var_decl->arg_default_value.dval = (double)op_arg_default->uv.constant->value.bval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                    arg_var_decl->arg_default_value.dval = (double)op_arg_default->uv.constant->value.sval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                    arg_var_decl->arg_default_value.dval = (double)op_arg_default->uv.constant->value.ival;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                    arg_var_decl->arg_default_value.dval = (double)op_arg_default->uv.constant->value.lval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                    arg_var_decl->arg_default_value.dval = (double)op_arg_default->uv.constant->value.fval;
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                    arg_var_decl->arg_default_value.dval = (double)op_arg_default->uv.constant->value.dval;
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
          else if (SPVM_TYPE_is_object_type(compiler, arg_type->basic_type->id, arg_type->dimension, arg_type->flag)) {
            if (op_arg_default->id != SPVM_OP_C_ID_UNDEF) {
              SPVM_COMPILER_error(compiler, "The default value of the optional argument %s must be undef.\n  at %s line %d", arg_var_decl->var->name, method->op_method->file, method->op_method->line);
              return;
            }
          }
          else {
            SPVM_COMPILER_error(compiler, "The types other than the numeric type and the object type cannnot be used in the optional argument.\n  at %s line %d", method->op_method->file, method->op_method->line);
            return;
          }
        }
        else {
          if (found_optional_arg) {
            SPVM_COMPILER_error(compiler, "Arguments after optional arguments must be optional arguments.\n  at %s line %d", method->op_method->file, method->op_method->line);
            return;
          }
        }
        
        arg_var_decl->stack_index = args_width;
        
        if (is_arg_type_is_mulnum_type) {
          args_width += arg_type->basic_type->unmerged_fields->length;
        }
        else {
          args_width++;
        }
        
        if (arg_index == method->args_length - 1) {
          last_arg_type = arg_type;
        }
      }
      
      if (!(args_width <= 255)) {
        SPVM_COMPILER_error(compiler, "The width of the arguments must be less than or equal to 255.\n  at %s line %d", method->op_method->file, method->op_method->line);
        return;
      }
      
      // Can't return refernece type
      if (SPVM_TYPE_is_ref_type(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag)) {
        SPVM_COMPILER_error(compiler, "The return type cannnot be a reference type.\n  at %s line %d", method->op_method->file, method->op_method->line);
        return;
      }
      
      // Copy has_precomile_attribute from anon method defined basic type
      if (method->outmost_basic_type_name) {
        SPVM_BASIC_TYPE* anon_method_defined_basic_type = SPVM_HASH_get(compiler->basic_type_symtable, method->outmost_basic_type_name, strlen(method->outmost_basic_type_name));
        basic_type->is_precompile = anon_method_defined_basic_type->is_precompile;
      }
      
      // Add variable declarations if the block does not exist
      if (!method->op_block) {
        for (int32_t arg_index = 0; arg_index < method->args_length; arg_index++) {
          SPVM_VAR_DECL* arg_var_decl = SPVM_LIST_get(method->var_decls, arg_index);
          SPVM_LIST_push(method->var_decls, arg_var_decl);
        }
      }
      
      // Set is_precompile field of methods
      if (basic_type->is_precompile) {
        int32_t can_precompile;
        if (method->is_init) {
          can_precompile = 0;
        }
        else if (method->is_enum) {
          can_precompile = 0;
        }
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
    }
    
    // Check interface requirement to the super classes
    SPVM_BASIC_TYPE* parent_basic_type = basic_type->parent;
    while (1) {
      if (!parent_basic_type) {
        break;
      }
      
      char error_reason[1024] = {0};
      int32_t has_interface = SPVM_BASIC_TYPE_has_interface_common(compiler, basic_type->id, parent_basic_type->id, error_reason);
      
      if (!has_interface) {
        SPVM_COMPILER_error(compiler, error_reason);
        return;
      }
      
      parent_basic_type = parent_basic_type->parent;
    }
    
    // Check interface requirement to interfaces
    for (int32_t interface_basic_type_index = 0; interface_basic_type_index < basic_type->interface_basic_types->length; interface_basic_type_index++) {
      SPVM_BASIC_TYPE* interface_basic_type = SPVM_LIST_get(basic_type->interface_basic_types, interface_basic_type_index);
      
      char error_reason[1024] = {0};
      int32_t has_interface = SPVM_BASIC_TYPE_has_interface(compiler, basic_type->id, interface_basic_type->id, error_reason);
      
      if (!has_interface) {
        SPVM_COMPILER_error(compiler, error_reason);
        return;
      }
    }
    
    // Sort methods by name
    qsort(methods->values, methods->length, sizeof(SPVM_METHOD*), &SPVM_CHECK_method_name_compare_cb);
    
    // Create method IDs
    for (int32_t i = 0; i < methods->length; i++) {
      SPVM_METHOD* method = SPVM_LIST_get(methods, i);
      
      method->index = i;
    }
    
  }
}

  
void SPVM_CHECK_check_asts(SPVM_COMPILER* compiler) {
  for (int32_t basic_type_id = compiler->basic_types_base_id; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    
    SPVM_BASIC_TYPE_add_constant_string(compiler, basic_type, basic_type->name, strlen(basic_type->name));
    
    if (basic_type->file) {
      SPVM_BASIC_TYPE_add_constant_string(compiler, basic_type, basic_type->file, strlen(basic_type->file));
    }
    
    if (basic_type->class_dir) {
      SPVM_BASIC_TYPE_add_constant_string(compiler, basic_type, basic_type->class_dir, strlen(basic_type->class_dir));
    }
    
    if (basic_type->class_rel_file) {
      SPVM_BASIC_TYPE_add_constant_string(compiler, basic_type, basic_type->class_rel_file, strlen(basic_type->class_rel_file));
    }
    
    if (basic_type->version_string) {
      SPVM_BASIC_TYPE_add_constant_string(compiler, basic_type, basic_type->version_string, strlen(basic_type->version_string));
    }
    
    for (int32_t class_var_index = 0; class_var_index < basic_type->class_vars->length; class_var_index++) {
      SPVM_CLASS_VAR* class_var = SPVM_LIST_get(basic_type->class_vars, class_var_index);
      SPVM_BASIC_TYPE_add_constant_string(compiler, basic_type, class_var->name, strlen(class_var->name));
    }
    
    for (int32_t field_index = 0; field_index < basic_type->fields->length; field_index++) {
      SPVM_FIELD* field = SPVM_LIST_get(basic_type->fields, field_index);
      SPVM_BASIC_TYPE_add_constant_string(compiler, basic_type, field->name, strlen(field->name));
    }
    
    for (int32_t method_index = 0; method_index < basic_type->methods->length; method_index++) {
      SPVM_METHOD* method = SPVM_LIST_get(basic_type->methods, method_index);
      SPVM_BASIC_TYPE_add_constant_string(compiler, basic_type, method->name, strlen(method->name));
    }
    
    int32_t compile_error = 0;
    for (int32_t method_index = 0; method_index < basic_type->methods->length; method_index++) {
      SPVM_METHOD* method = SPVM_LIST_get(basic_type->methods, method_index);
      // AST traversals
      if (method->op_block) {
        SPVM_CHECK_check_ast_op_types(compiler, basic_type, method);
        if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
          return;
        }
        
        // AST traversal - Check syntax and generate some operations
        SPVM_CHECK_check_ast_syntax(compiler, basic_type, method);
        if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
          return;
        }
        
        // AST traversal - assign an unassigned operator to a variable
        SPVM_CHECK_check_ast_assign_unassigned_op_to_var(compiler, basic_type, method);
        assert(SPVM_COMPILER_get_error_messages_length(compiler) == 0);
        
        // AST traversal - Check if a block needs "leave scope" operation
        SPVM_CHECK_check_ast_if_block_need_leave_scope(compiler, basic_type, method);
        assert(SPVM_COMPILER_get_error_messages_length(compiler) == 0);
        
        // AST traversal - Check call stack ids of variable declarations
        SPVM_CHECK_check_ast_typed_var_indexs(compiler, basic_type, method);
        assert(SPVM_COMPILER_get_error_messages_length(compiler) == 0);
      }
    }
    
    // String pool must end with "\0"
    // This is not needed, but maybe there are bugs in other places
    SPVM_STRING_BUFFER_add_len(basic_type->string_pool, "\0\0\0\0", 4);
  }
}

void SPVM_CHECK_check_op_type(SPVM_COMPILER* compiler, SPVM_OP* op_type) {
  
  SPVM_TYPE* type = op_type->uv.type;
  
  if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_UNKNOWN) {
    const char* unresolved_basic_type_name = type->unresolved_basic_type_name;
    
    assert(unresolved_basic_type_name);
    
    SPVM_BASIC_TYPE* found_basic_type = SPVM_HASH_get(compiler->basic_type_symtable, unresolved_basic_type_name, strlen(unresolved_basic_type_name));
    if (found_basic_type) {
      type->basic_type = found_basic_type;
    }
  }
  
  // Basic type name
  const char* basic_type_name = type->basic_type->name;
  
  if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_UNKNOWN) {
    const char* if_require_not_found_basic_type_name = SPVM_HASH_get(compiler->if_require_not_found_basic_type_name_symtable, type->unresolved_basic_type_name, strlen(type->unresolved_basic_type_name));
    
    if (!if_require_not_found_basic_type_name) {
      SPVM_COMPILER_error(compiler, "%s class is not found.\n  at %s line %d", type->unresolved_basic_type_name, op_type->file, op_type->line);
      return;
    }
  }
  
  // Reference type must be numeric refernce type or multi-numeric reference type
  if (SPVM_TYPE_is_ref_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
    if (!(SPVM_TYPE_is_numeric_ref_type(compiler, type->basic_type->id, type->dimension, type->flag) || SPVM_TYPE_is_mulnum_ref_type(compiler, type->basic_type->id, type->dimension, type->flag))) {
      SPVM_COMPILER_error(compiler, "The reference type must be a numeric refernce type or a multi-numeric reference type.\n  at %s line %d", op_type->file, op_type->line);
    }
  }

  // mutable only allow string type
  if (type->flag & SPVM_NATIVE_C_TYPE_FLAG_MUTABLE && !(type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_STRING && type->dimension == 0)) {
    SPVM_COMPILER_error(compiler, "The type qualifier \"mutable\" is only allowed in string type.\n  at %s line %d", op_type->file, op_type->line);
  }
  
  if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT && type->dimension > 1) {
    const char* type_name = SPVM_TYPE_new_type_name(compiler, type->basic_type->id, type->dimension, type->flag);
    SPVM_COMPILER_error(compiler, "The multi dimensional array of any object is not allowed.\n  at %s line %d", op_type->file, op_type->line);
  }
  

}

void SPVM_CHECK_check_op_types(SPVM_COMPILER* compiler) {
  
  SPVM_LIST* op_types = compiler->op_types;
  
  // Check type names
  for (int32_t i = 0; i < op_types->length; i++) {
    SPVM_OP* op_type = SPVM_LIST_get(op_types, i);
    
    if (!op_type->uv.type->resolved_in_ast) {
      SPVM_CHECK_check_op_type(compiler, op_type);
    }
  }
}

void SPVM_CHECK_check_class_var_access(SPVM_COMPILER* compiler, SPVM_OP* op_class_var_access, SPVM_METHOD* current_method) {
  
  if (op_class_var_access->uv.class_var_access->class_var) {
    return;
  }
  assert(op_class_var_access->uv.class_var_access);
  
  SPVM_OP* op_name = op_class_var_access->uv.class_var_access->op_name;
  
  char* basic_type_name;
  char* base_name;
  
  const char* name = op_name->uv.name;
  
  char* colon_ptr = strrchr(name, ':');
  if (colon_ptr) {
    // Basic type name
    // (end - start + 1) - $ - colon * 2
    int32_t basic_type_name_length = (colon_ptr - name + 1) - 1 - 2;
    basic_type_name = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->current_each_compile_allocator, basic_type_name_length + 1);
    memcpy(basic_type_name, name + 1, basic_type_name_length);
    
    // Base name($foo)
    int32_t base_name_length = 1 + (name + strlen(name) - 1) - colon_ptr;
    base_name = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->current_each_compile_allocator, base_name_length + 1);
    base_name[0] = '$';
    memcpy(base_name + 1, colon_ptr + 1, base_name_length);
  }
  else {
    if (current_method->current_basic_type->is_generated_by_anon_method) {
      basic_type_name = (char*)current_method->outmost_basic_type_name;
    }
    else {
      basic_type_name = (char*)current_method->current_basic_type->name;
    }
    
    base_name = (char*)name;
  }
  
  SPVM_BASIC_TYPE* found_basic_type = SPVM_HASH_get(compiler->basic_type_symtable, basic_type_name, strlen(basic_type_name));
  if (found_basic_type) {
    SPVM_CLASS_VAR* found_class_var = SPVM_HASH_get(found_basic_type->class_var_symtable, base_name, strlen(base_name));
    if (found_class_var) {
      op_class_var_access->uv.class_var_access->class_var = found_class_var;
    }
  }
}

void SPVM_CHECK_check_field_access(SPVM_COMPILER* compiler, SPVM_OP* op_field_access) {

  SPVM_FIELD_ACCESS* field_access = op_field_access->uv.field_access;

  if (field_access->field) {
    return;
  }

  SPVM_OP* op_operand = op_field_access->first;
  SPVM_OP* op_name = field_access->op_name;
  
  SPVM_TYPE* invocant_type = SPVM_CHECK_get_type(compiler, op_operand);
  SPVM_BASIC_TYPE* basic_type = SPVM_HASH_get(compiler->basic_type_symtable, invocant_type->basic_type->name, strlen(invocant_type->basic_type->name));
  const char* field_name = op_name->uv.name;

  // Search the field of the super class
  SPVM_FIELD* found_field = NULL;
  SPVM_BASIC_TYPE* parent_basic_type = basic_type;
  
  while (1) {
    found_field = SPVM_HASH_get(
      parent_basic_type->field_symtable,
      field_name,
      strlen(field_name)
    );
    if (found_field) {
      break;
    }
    parent_basic_type = parent_basic_type->parent;
    if (!parent_basic_type) {
      break;
    }
  }
  
  if (found_field) {
    op_field_access->uv.field_access->field = found_field;
  }
  else {
    SPVM_COMPILER_error(compiler, "%s field is not found in %s class or its super classes.\n  at %s line %d", field_name, basic_type->name, op_field_access->file, op_field_access->line);
    return;
  }
}

void SPVM_CHECK_check_field_offset(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type) {
  if (basic_type->category != SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS) {
    return;
  }
  
  int32_t alignment_size;
  if (sizeof(void*) > sizeof(int64_t)) {
    alignment_size = sizeof(void*);
  }
  else {
    alignment_size = sizeof(int64_t);
  }
  
  int32_t alignment_index = 0;
  int32_t offset = 0;
  int32_t offset_size;
  
  // 8 byte data
  for (int32_t field_index = 0; field_index < basic_type->fields->length; field_index++) {
    SPVM_FIELD* field = SPVM_LIST_get(basic_type->fields, field_index);
    SPVM_TYPE* field_type = field->type;
    
    int32_t next_offset;
    if (SPVM_TYPE_is_double_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)
      || SPVM_TYPE_is_long_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)) {
      offset_size = 8;
    }
    else if (SPVM_TYPE_is_float_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)
      || SPVM_TYPE_is_int_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)) {
      offset_size = 4;
    }
    else if (SPVM_TYPE_is_short_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)) {
      offset_size = 2;
    }
    else if (SPVM_TYPE_is_byte_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)) {
      offset_size = 1;
    }
    else if (SPVM_TYPE_is_object_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)) {
      offset_size = sizeof(void*);
    }
    else {
      assert(0);
    }
    
    next_offset = offset + offset_size;
    
    if (next_offset % offset_size != 0) {
      offset += (offset_size - offset % offset_size);
    }
    
    if (next_offset == alignment_size * (alignment_index + 1)) {
      alignment_index++;
    }
    else if (next_offset > alignment_size * (alignment_index + 1)) {
      alignment_index++;
      // Next alignment
      offset += (alignment_size - offset % alignment_size);
      
      assert(offset % alignment_size == 0);
    }
    
    field->offset = offset;
    
    offset += offset_size;
  }
  
  basic_type->fields_size = offset;
}

void SPVM_CHECK_check_call_method(SPVM_COMPILER* compiler, SPVM_OP* op_call_method, SPVM_METHOD* current_method) {
  
  SPVM_CALL_METHOD* call_method = op_call_method->uv.call_method;
  
  if (call_method->method) {
    return;
  }
  
  const char* method_name = call_method->op_name->uv.name;
  
  // Class method call
  if (call_method->is_class_method) {
    SPVM_METHOD* found_method = NULL;
    // Basic type name + method name
    const char* basic_type_name;
    if (call_method->is_current) {
      if (current_method->current_basic_type->is_generated_by_anon_method) {
        basic_type_name = current_method->outmost_basic_type_name;
      }
      else {
        basic_type_name = current_method->current_basic_type->name;
      }
    }
    else {
      SPVM_OP* op_type_basic_type = op_call_method->last;
      basic_type_name = op_type_basic_type->uv.type->basic_type->name;
    }
    
    SPVM_BASIC_TYPE* found_basic_type = SPVM_HASH_get(compiler->basic_type_symtable, basic_type_name, strlen(basic_type_name));
    
    found_method = SPVM_HASH_get(
      found_basic_type->method_symtable,
      method_name,
      strlen(method_name)
    );
    
    if (found_method && !found_method->is_class_method) {
      found_method = NULL;
    }
  
    if (found_method) {
      call_method->method = found_method;
    }
    else {
      SPVM_COMPILER_error(compiler, "%s#%s method is not found.\n  at %s line %d", found_basic_type->name, method_name, op_call_method->file, op_call_method->line);
      return;
    }
  }
  // Instance method call
  else {
    SPVM_OP* op_list_args = op_call_method->first;
    SPVM_OP* op_invocant = SPVM_OP_sibling(compiler, op_list_args->first);
    
    SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, op_invocant);
    if (!(SPVM_TYPE_is_class_type(compiler, type->basic_type->id, type->dimension, type->flag) || SPVM_TYPE_is_interface_type(compiler, type->basic_type->id, type->dimension, type->flag))) {
      SPVM_COMPILER_error(compiler, "The invocant of %s method must be a class type or an interface type.\n  at %s line %d", method_name, op_call_method->file, op_call_method->line);
      return;
    }
    
    const char* basic_type_name = type->basic_type->name;
    
    SPVM_BASIC_TYPE* basic_type = SPVM_HASH_get(compiler->basic_type_symtable, basic_type_name, strlen(basic_type_name));
    
    // Static instance method call
    char* last_colon_pos = strrchr(method_name, ':');
    if (last_colon_pos) {
      const char* abs_method_name = method_name;
      call_method->is_instance_method_static = 1;
      method_name = last_colon_pos + 1;
      int32_t basic_type_name_length = (last_colon_pos - 1) - abs_method_name;
      
      // SUPER::
      SPVM_METHOD* found_method = NULL;
      if (strstr(abs_method_name, "SUPER::") == abs_method_name) {
        SPVM_BASIC_TYPE* parent_basic_type = basic_type->parent;
        if (parent_basic_type) {
          // Search the method of the super class
          found_method = SPVM_CHECK_search_method(compiler, parent_basic_type, method_name);
        }
      }
      else {
        SPVM_BASIC_TYPE* found_basic_type = SPVM_HASH_get(compiler->basic_type_symtable, abs_method_name, basic_type_name_length);
        if (!found_basic_type) {
          SPVM_COMPILER_error(compiler, "The class included in the method call %s is not found.\n  at %s line %d", abs_method_name, op_call_method->file, op_call_method->line);
          return;
        }
        if (found_basic_type) {
          found_method = SPVM_HASH_get(
            found_basic_type->method_symtable,
            method_name,
            strlen(method_name)
          );
        }
      }
      
      if (found_method) {
        basic_type = found_method->current_basic_type;
        if (found_method->is_class_method) {
          SPVM_COMPILER_error(compiler, "%s#%s method is found, but this is not an instance method.\n  at %s line %d", basic_type->name, abs_method_name, op_call_method->file, op_call_method->line);
          return;
        }
        call_method->method = found_method;
      }
      else {
        SPVM_COMPILER_error(compiler, "%s method is not found.\n  at %s line %d", abs_method_name, op_call_method->file, op_call_method->line);
        return;
      }
    }
    // Instance method
    else {
      SPVM_METHOD* found_method = SPVM_CHECK_search_method(compiler, basic_type, method_name);
      
      if (found_method) {
        if (found_method->is_class_method) {
          basic_type = found_method->current_basic_type;
          SPVM_COMPILER_error(compiler, "%s#%s method is found, but this method must be an instance method.\n  at %s line %d", basic_type->name, method_name, op_call_method->file, op_call_method->line);
          return;
        }
        call_method->method = found_method;
      }
      else {
        SPVM_COMPILER_error(compiler, "%s method is not found in %s class or its super classes .\n  at %s line %d", method_name, basic_type->name, op_call_method->file, op_call_method->line);
        return;
      }
    }
  }
}

void SPVM_CHECK_check_ast_op_types(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type, SPVM_METHOD* method) {
  
  // Run OPs
  SPVM_OP* op_root = method->op_block;
  SPVM_OP* op_cur = op_root;
  int32_t finish = 0;
  while (op_cur) {
    // [START]Preorder traversal position
    if (op_cur->id == SPVM_OP_C_ID_IF_REQUIRE) {
      SPVM_USE* use = op_cur->first->uv.use;
      SPVM_OP* op_block_true = SPVM_OP_sibling(compiler, op_cur->first);
      SPVM_OP* op_block_false = op_cur->last;
      
      // Execute false block
      const char* use_basic_type_name = use->op_type->uv.type->unresolved_basic_type_name;
      
      SPVM_BASIC_TYPE* found_basic_type = SPVM_HASH_get(compiler->basic_type_symtable, use_basic_type_name, strlen(use_basic_type_name));
      
      if (found_basic_type) {
        SPVM_OP_cut_op(compiler, op_block_true);
        SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
        SPVM_OP_replace_op(compiler, op_stab, op_block_true);
        op_cur = op_block_true;
      }
      // Execute true block
      else {
        SPVM_OP_cut_op(compiler, op_block_false);
        SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
        SPVM_OP_replace_op(compiler, op_stab, op_block_false);
        op_cur = op_block_false;
      }
    }
    
    if (op_cur->first) {
      op_cur = op_cur->first;
    }
    else {
      while (1) {
        // [START]Postorder traversal position
        switch (op_cur->id) {
          case SPVM_OP_C_ID_TYPE: {
            SPVM_OP* op_type = op_cur;
            if (op_type->uv.type->resolved_in_ast) {
              const char* unresolved_basic_type_name_maybe_alias = op_type->uv.type->unresolved_basic_type_name;
              
              SPVM_HASH* alias_symtable = NULL;
              if (basic_type->is_generated_by_anon_method && basic_type->outmost) {
                alias_symtable = basic_type->outmost->alias_symtable;
              }
              else {
                alias_symtable = basic_type->alias_symtable;
              }
              
              const char* unresolved_basic_type_name = SPVM_HASH_get(alias_symtable, unresolved_basic_type_name_maybe_alias, strlen(unresolved_basic_type_name_maybe_alias));
              if (unresolved_basic_type_name) {
                op_type->uv.type->unresolved_basic_type_name = unresolved_basic_type_name;
                op_type->uv.type->basic_type = SPVM_LIST_get(compiler->basic_types, 0);
              }
              
              SPVM_CHECK_check_op_type(compiler, op_type);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              SPVM_BASIC_TYPE_add_constant_string(compiler, basic_type, op_type->uv.type->basic_type->name, strlen(op_type->uv.type->basic_type->name));
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

void SPVM_CHECK_check_ast_syntax(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type, SPVM_METHOD* method) {
  
  if (!method->op_block) {
    return;
  }
  
  // Eval block stack length
  int32_t eval_block_stack_length = 0;
  
  // Loop block stack length
  int32_t loop_block_stack_length = 0;
  
  SPVM_LIST* var_decl_stack = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT);
  SPVM_LIST* var_decl_scope_base_stack = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT);
  SPVM_LIST* op_switch_stack = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT);
  
  // Check tree
  SPVM_OP* op_root = method->op_block;
  SPVM_OP* op_cur = op_root;
  int32_t finish = 0;
  while (op_cur) {
    // [START]Preorder traversal position
    
    switch (op_cur->id) {
      case SPVM_OP_C_ID_BLOCK: {
        SPVM_BLOCK* block = op_cur->uv.block;
        // Start scope
        if (!block->no_scope) {
          int32_t block_var_decl_base = var_decl_stack->length;
          SPVM_LIST_push(var_decl_scope_base_stack, (void*)(intptr_t)block_var_decl_base);
        }
        
        if (block->id == SPVM_BLOCK_C_ID_LOOP_STATEMENTS) {
          loop_block_stack_length++;
        }
        else if (block->id == SPVM_BLOCK_C_ID_EVAL) {
          eval_block_stack_length++;
        }
        
        break;
      }
      case SPVM_OP_C_ID_SWITCH: {
        SPVM_LIST_push(op_switch_stack, op_cur);
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
              SPVM_COMPILER_error(compiler, "The next statement must be in a loop block.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            break;
          }
          case SPVM_OP_C_ID_LAST: {
            if (loop_block_stack_length == 0) {
              SPVM_COMPILER_error(compiler, "The last statement must be in a loop block.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            break;
          }
          case SPVM_OP_C_ID_BREAK: {
            if (op_switch_stack->length == 0) {
              SPVM_COMPILER_error(compiler, "The break statement must be in a switch block.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            break;
          }
          case SPVM_OP_C_ID_OUTMOST_CLASS_NAME: {
            SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
            
            const char* current_class_name = NULL;
            if (method->current_basic_type->is_generated_by_anon_method) {
              SPVM_BASIC_TYPE_add_constant_string(compiler, basic_type, method->outmost_basic_type_name, strlen(method->outmost_basic_type_name));
              current_class_name = method->outmost_basic_type_name;
            }
            else {
              current_class_name = basic_type->name;
            }
            
            SPVM_OP* op_constant = SPVM_OP_new_op_constant_string(compiler, current_class_name, strlen(current_class_name), op_cur->file, op_cur->line);
            SPVM_OP_replace_op(compiler, op_stab, op_constant);
            op_cur = op_constant;
            
            break;
          }
          case SPVM_OP_C_ID_TYPE_NAME: {
            
            SPVM_OP* op_operand = op_cur->first;
            
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_operand);
            
            // Must be object type
            if (!SPVM_TYPE_is_object_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the operand of type_name operator must be an object type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_COMPILE_TYPE_NAME: {
            
            SPVM_OP* op_operand = op_cur->first;
            
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_operand);
            const char* type_name = SPVM_TYPE_new_type_name(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag);
            SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
            SPVM_OP* op_constant_string = SPVM_OP_new_op_constant_string(compiler, type_name, strlen(type_name), op_cur->file, op_cur->line);
            SPVM_OP_replace_op(compiler, op_stab, op_constant_string);
            op_cur = op_constant_string;
            
            break;
          }
          case SPVM_OP_C_ID_DUMP: {
            
            SPVM_OP* op_operand = op_cur->first;
            
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_operand);
            
            // Must be object type
            if (!SPVM_TYPE_is_object_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the operand of dump operator must be an object type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_NEW_STRING_LEN: {
            
            SPVM_OP* op_operand = op_cur->first;
            
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_operand);
            
            assert(operand_type);
            
            if (!SPVM_TYPE_is_integer_type_within_int(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the operand of new_string_len operator must be an integer type within int.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            SPVM_CHECK_perform_integer_promotional_conversion(compiler, op_operand);
            
            break;
          }
          
          case SPVM_OP_C_ID_BASIC_TYPE_ID: {
            
            // Nothing to do
            
            break;
          }
          case SPVM_OP_C_ID_SWITCH: {
            
            SPVM_OP* op_switch_condition = op_cur->first;
            
            // Perform numeric widening conversion
            
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_switch_condition->first);
            if (!SPVM_TYPE_is_integer_type_within_int(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The condition of the switch statement must be an integer type within int.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            SPVM_CHECK_perform_integer_promotional_conversion(compiler, op_switch_condition->first->first);
            
            SPVM_SWITCH_INFO* switch_info = op_cur->uv.switch_info;
            SPVM_LIST* cases = switch_info->case_infos;
            int32_t cases_length = cases->length;
            
            // sort by asc order
            for (int32_t i = 0; i < switch_info->case_infos->length; i++) {
              for (int32_t j = i + 1; j < switch_info->case_infos->length; j++) {
                SPVM_CASE_INFO* case_i = SPVM_LIST_get(switch_info->case_infos, i);
                SPVM_CASE_INFO* case_j = SPVM_LIST_get(switch_info->case_infos, j);
                int32_t match_i = case_i->case_value;
                int32_t match_j = case_j->case_value;
                
                if (match_i > match_j) {
                  SPVM_LIST_set(switch_info->case_infos, i, case_j);
                  SPVM_LIST_set(switch_info->case_infos, j, case_i);
                }
              }
            }
            
            // Check duplication
            for (int32_t i = 0; i < switch_info->case_infos->length - 1; i++) {
              SPVM_CASE_INFO* case_info = SPVM_LIST_get(switch_info->case_infos, i);
              SPVM_CASE_INFO* case_info_next = SPVM_LIST_get(switch_info->case_infos, i + 1);
              if (case_info->case_value == case_info_next->case_value) {
                SPVM_COMPILER_error(compiler, "The value of the case statement cannnot be duplicated.\n  at %s line %d", case_info->op_case_info->file, case_info->op_case_info->line);
              }
            }
            
            SPVM_LIST_pop(op_switch_stack);
            
            // Decide switch type
            switch_info->id = SPVM_SWITCH_INFO_C_ID_LOOKUP_SWITCH;
            
            if (!switch_info->op_default) {
              SPVM_OP* op_switch_block = op_cur->last;
              
              SPVM_OP* op_default = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DEFAULT, op_cur->file, op_cur->line);
              SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, op_cur->file, op_cur->line);
              SPVM_OP_build_default_statement(compiler, op_default, op_block);
              
              SPVM_OP_insert_child(compiler, op_switch_block, op_switch_block->last, op_default);
            }
            
            break;
          }
          case SPVM_OP_C_ID_CASE: {
            if (op_switch_stack->length > 0) {
              SPVM_OP* op_switch = SPVM_LIST_get(op_switch_stack, op_switch_stack->length - 1);
              SPVM_SWITCH_INFO* switch_info = op_switch->uv.switch_info;
              SPVM_LIST_push(switch_info->case_infos, op_cur->uv.case_info);
            }
            
            SPVM_CASE_INFO* case_info = op_cur->uv.case_info;
            SPVM_OP* op_constant = op_cur->first;
            SPVM_CONSTANT* constant = op_constant->uv.constant;
            
            SPVM_TYPE* case_value_type = SPVM_CHECK_get_type(compiler, op_constant);
            if (!(
              op_constant->id == SPVM_OP_C_ID_CONSTANT &&
              (
                SPVM_TYPE_is_byte_type(compiler, case_value_type->basic_type->id, case_value_type->dimension, case_value_type->flag) ||
                SPVM_TYPE_is_int_type(compiler, case_value_type->basic_type->id, case_value_type->dimension, case_value_type->flag)
              )
            ))
            {
              SPVM_COMPILER_error(compiler, "The operand of case statement must be an integer literal of int type, a character litaral, or an enumeration value.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            // Upgrade byte to int
            if (constant->type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
              constant->type = SPVM_TYPE_new_int_type(compiler);
              constant->value.ival = (int32_t)constant->value.bval;
            }
            
            case_info->case_value = constant->value.ival;
            
            // Remove case value operation because this is a constant value for a case statemenet.
            SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur->first);
            SPVM_OP* op_do_nothing = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, op_cur->first->file, op_cur->first->line);
            SPVM_OP_replace_op(compiler, op_stab, op_do_nothing);
            
            break;
          }
          case SPVM_OP_C_ID_DEFAULT: {
            if (op_switch_stack->length > 0) {
              SPVM_OP* op_switch = SPVM_LIST_get(op_switch_stack, op_switch_stack->length - 1);
              SPVM_SWITCH_INFO* switch_info = op_switch->uv.switch_info;
              
              switch_info->op_default = op_cur;
            }
            break;
          }
          case SPVM_OP_C_ID_BOOL: {
            SPVM_OP* op_operand = op_cur->first;
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            
            int32_t is_valid_type;
              
            // undef type
            if (SPVM_TYPE_is_undef_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              
              is_valid_type = 1;
              
              SPVM_OP* op_constant_zero = SPVM_OP_new_op_constant_int(compiler, 0, op_operand->file, op_operand->line);
              SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_operand);
              SPVM_OP_replace_op(compiler, op_stab, op_constant_zero);
            }
            // Numeric type
            else if (SPVM_TYPE_is_numeric_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag))
            {
              // Convert byte or short type to int type
              SPVM_CHECK_perform_integer_promotional_conversion(compiler, op_operand);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              is_valid_type = 1;
            }
            // Object type
            else if (SPVM_TYPE_is_object_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              is_valid_type = 1;
            }
            // Reference type
            else if (SPVM_TYPE_is_ref_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              is_valid_type = 1;
            }
            else {
              is_valid_type = 0;
            }
            
            if (!is_valid_type) {
              SPVM_COMPILER_error(compiler, "The type of the operand of bool type conversion must be a numeric type or an object type or a reference type or undef type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_NUMERIC_COMPARISON_EQ: {
            SPVM_OP* op_left_operand = op_cur->first;
            
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            int32_t left_operand_type_is_valid
              = SPVM_TYPE_is_numeric_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)
              || SPVM_TYPE_is_object_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)
              || SPVM_TYPE_is_ref_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)
              || SPVM_TYPE_is_undef_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag);
            
            if (!left_operand_type_is_valid) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of == operator must be a numeric type, an object type, a reference type, or undef type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            int32_t right_operand_type_is_valid
              = SPVM_TYPE_is_numeric_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)
              || SPVM_TYPE_is_object_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)
              || SPVM_TYPE_is_ref_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)
              || SPVM_TYPE_is_undef_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag);
            
            if (!right_operand_type_is_valid) {
              SPVM_COMPILER_error(compiler, "The type of the right operand of == operator must be a numeric type, an object type, a reference type, or undef type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            if (SPVM_TYPE_is_numeric_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              if (!SPVM_TYPE_is_numeric_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
                SPVM_COMPILER_error(compiler, "If the type of the left operand of == operator is a numeric type, the type of the right operand must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
                return;
              }
            }
            
            if (SPVM_TYPE_is_object_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              if (!(SPVM_TYPE_is_object_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)
                || SPVM_TYPE_is_undef_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)))
              {
                SPVM_COMPILER_error(compiler, "If the type of the left operand of == operator is an object type, the type of the right operand must be an object type or undef type.\n  at %s line %d", op_cur->file, op_cur->line);
                return;
              }
            }
            
            if (SPVM_TYPE_is_undef_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              if (!(SPVM_TYPE_is_object_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)
                || SPVM_TYPE_is_undef_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)))
              {
                SPVM_COMPILER_error(compiler, "If the type of the left operand of == operator is the undef type, the type of the right operand must be an object type or undef type.\n  at %s line %d", op_cur->file, op_cur->line);
                return;
              }
            }
            
            if (SPVM_TYPE_is_ref_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              if (!SPVM_TYPE_is_ref_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
                SPVM_COMPILER_error(compiler, "If the type of the left operand of == operator is a reference type, the type of the right operand must be a reference type.\n  at %s line %d", op_cur->file, op_cur->line);
                return;
              }
            }
            
            if (SPVM_TYPE_is_undef_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)
              && SPVM_TYPE_is_undef_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag))
            {
              // Constant 1
              SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
              SPVM_OP* op_constant_one = SPVM_OP_new_op_constant_int(compiler, 1, op_left_operand->file, op_left_operand->line);
              SPVM_OP_replace_op(compiler, op_stab, op_constant_one);
              op_cur = op_constant_one;
            }
            else if (SPVM_TYPE_is_numeric_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              assert(SPVM_TYPE_is_numeric_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag));
               
              SPVM_CHECK_perform_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
              
              assert(SPVM_COMPILER_get_error_messages_length(compiler) == 0);
            }
            
            break;
          }
          case SPVM_OP_C_ID_NUMERIC_COMPARISON_NE: {
            SPVM_OP* op_left_operand = op_cur->first;
            
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            int32_t left_operand_type_is_valid
              = SPVM_TYPE_is_numeric_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)
              || SPVM_TYPE_is_object_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)
              || SPVM_TYPE_is_ref_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)
              || SPVM_TYPE_is_undef_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag);
            
            if (!left_operand_type_is_valid) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of != operator must be a numeric type, an object type, a reference type, or undef type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            int32_t right_operand_type_is_valid
              = SPVM_TYPE_is_numeric_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)
              || SPVM_TYPE_is_object_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)
              || SPVM_TYPE_is_ref_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)
              || SPVM_TYPE_is_undef_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag);
            
            if (!right_operand_type_is_valid) {
              SPVM_COMPILER_error(compiler, "The type of the right operand of != operator must be a numeric type, an object type, a reference type, or undef type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            if (SPVM_TYPE_is_numeric_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              if (!SPVM_TYPE_is_numeric_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
                SPVM_COMPILER_error(compiler, "If the type of the left operand of != operator is a numeric type, the type of the right operand must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
                return;
              }
            }
            
            if (SPVM_TYPE_is_object_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              if (!(SPVM_TYPE_is_object_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)
                || SPVM_TYPE_is_undef_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)))
              {
                SPVM_COMPILER_error(compiler, "If the type of the left operand of != operator is an object type, the type of the right operand must be an object type or undef type.\n  at %s line %d", op_cur->file, op_cur->line);
                return;
              }
            }
            
            if (SPVM_TYPE_is_undef_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              if (!(SPVM_TYPE_is_object_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)
                || SPVM_TYPE_is_undef_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)))
              {
                SPVM_COMPILER_error(compiler, "If the type of the left operand of != operator is the undef type, the type of the right operand must be an object type or undef type.\n  at %s line %d", op_cur->file, op_cur->line);
                return;
              }
            }
            
            if (SPVM_TYPE_is_ref_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              if (!SPVM_TYPE_is_ref_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
                SPVM_COMPILER_error(compiler, "If the type of the left operand of != operator is a reference type, the type of the right operand must be a reference type.\n  at %s line %d", op_cur->file, op_cur->line);
                return;
              }
            }
            
            if (SPVM_TYPE_is_undef_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)
              && SPVM_TYPE_is_undef_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag))
            {
              // Constant 0
              SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
              SPVM_OP* op_constant_zero = SPVM_OP_new_op_constant_int(compiler, 0, op_left_operand->file, op_left_operand->line);
              SPVM_OP_replace_op(compiler, op_stab, op_constant_zero);
              op_cur = op_constant_zero;
            }
            else if (SPVM_TYPE_is_numeric_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              
              assert(SPVM_TYPE_is_numeric_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag));
               
              SPVM_CHECK_perform_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
              
              assert(SPVM_COMPILER_get_error_messages_length(compiler) == 0);
            }
            
            break;
          }
          case SPVM_OP_C_ID_NUMERIC_COMPARISON_GT: {

            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);

            // Left operand must be a numeric type
            if (!SPVM_TYPE_is_numeric_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of > operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }

            // Right operand must be a numeric type
            if (!SPVM_TYPE_is_numeric_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of > operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }

            // Apply binary numeric conversion
            SPVM_CHECK_perform_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_NUMERIC_COMPARISON_GE: {

            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);

            // Left operand must be a numeric type
            if (!SPVM_TYPE_is_numeric_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of >= operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }

            // Right operand must be a numeric type
            if (!SPVM_TYPE_is_numeric_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of >= operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }

            // Apply binary numeric conversion
            SPVM_CHECK_perform_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_NUMERIC_COMPARISON_LT: {

            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            // Left operand must be a numeric type
            if (!SPVM_TYPE_is_numeric_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of < operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }

            // Right operand must be a numeric type
            if (!SPVM_TYPE_is_numeric_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of < operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }

            // Apply binary numeric conversion
            SPVM_CHECK_perform_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }

            break;
          }
          case SPVM_OP_C_ID_NUMERIC_COMPARISON_LE: {

            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);

            // Left operand must be a numeric type
            if (!SPVM_TYPE_is_numeric_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of <= operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }

            // Right operand must be a numeric type
            if (!SPVM_TYPE_is_numeric_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of <= operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }

            // Apply binary numeric conversion
            SPVM_CHECK_perform_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_NUMERIC_COMPARISON_CMP: {

            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);

            // Left operand must be a numeric type
            if (!SPVM_TYPE_is_numeric_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of <=> operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }

            // Right operand must be a numeric type
            if (!SPVM_TYPE_is_numeric_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of <=> operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }

            // Apply binary numeric conversion
            SPVM_CHECK_perform_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_STRING_COMPARISON_EQ: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            // Left operand must be string type
            if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of eq operator must be string type or byte[] type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            // Right operand must be string type
            if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of eq operator must be string type or byte[] type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_STRING_COMPARISON_NE: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            // Left operand must be string type
            if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of ne operator must be string type or byte[] type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            // Right operand must be string type
            if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of ne operator must be string type or byte[] type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_STRING_COMPARISON_GT: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            // Left operand must be string type
            if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of gt operator must be string type or byte[] type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            // Right operand must be string type
            if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of gt operator must be string type or byte[] type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_STRING_COMPARISON_GE: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            // Left operand must be string type
            if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of ge operator must be string type or byte[] type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            // Right operand must be string type
            if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of ge operator must be string type or byte[] type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_STRING_COMPARISON_LT: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            // Left operand must be string type
            if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of lt operator must be string type or byte[] type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            // Right operand must be string type
            if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of lt operator must be string type or byte[] type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_STRING_COMPARISON_LE: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            // Left operand must be string type
            if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of le operator must be string type or byte[] type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            // Right operand must be string type
            if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of le operator must be string type or byte[] type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_STRING_COMPARISON_CMP: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            // Left operand must be string type
            if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of cmp operator must be string type or byte[] type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            // Right operand must be string type
            if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of cmp operator must be string type or byte[] type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_STRING_CONCAT: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            // Left type is numeric type
            if (SPVM_TYPE_is_numeric_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_CHECK_perform_numeric_to_string_conversion(compiler, op_cur->first);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
            }
            // Left type is not string type or byte array type
            else if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of . operator must be string type or byte[] type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            // Right operand is numeric type
            if (SPVM_TYPE_is_numeric_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_CHECK_perform_numeric_to_string_conversion(compiler, op_cur->last);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
            }
            // Right operand is not string type or byte array type
            else if (!SPVM_TYPE_is_string_or_byte_array_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of . operator must be string type or byte[] type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_CONSTANT : {
            SPVM_OP* op_constant = op_cur;
            
            SPVM_TYPE* constant_type = SPVM_CHECK_get_type(compiler, op_constant);
            
            if (SPVM_TYPE_is_string_type(compiler, constant_type->basic_type->id, constant_type->dimension, constant_type->flag)) {
              SPVM_CONSTANT* constant = op_constant->uv.constant;
              
              const char* constant_string_value = constant->value.oval;
              int32_t constant_string_length = constant->string_length;
              
              SPVM_BASIC_TYPE_add_constant_string(compiler, basic_type, constant_string_value, constant_string_length);
            }
            
            break;
          }
          case SPVM_OP_C_ID_NEW: {
            SPVM_OP* op_new = op_cur;
            
            assert(op_new->first);
            assert(op_new->first->id == SPVM_OP_C_ID_TYPE || op_new->first->id == SPVM_OP_C_ID_VAR);
            
            SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, op_new);
            
            SPVM_BASIC_TYPE* new_basic_type = type->basic_type;
            
            // Array type
            if (SPVM_TYPE_is_array_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
              
              SPVM_OP* op_length = op_new->last;
              
              SPVM_TYPE* length_type = SPVM_CHECK_get_type(compiler, op_length);
              
              assert(length_type);
              if (!SPVM_TYPE_is_integer_type_within_int(compiler, length_type->basic_type->id, length_type->dimension, length_type->flag)) {
                const char* type_name = SPVM_TYPE_new_type_name(compiler, type->basic_type->id, type->dimension, type->flag);
                SPVM_COMPILER_error(compiler, "The array length specified by new operator must be an integer type within int.\n  at %s line %d", op_new->file, op_new->line);
                return;
              }
              else if (type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT && type->dimension > 1) {
                SPVM_COMPILER_error(compiler, "The creation of a multi dimensional array of any object is not allowed.\n  at %s line %d", op_new->file, op_new->line);
                return;
              }
              
              SPVM_CHECK_perform_integer_promotional_conversion(compiler, op_length);
            }
            // Numeric type
            else if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the operand of new operator cannnot be a numeric type.\n  at %s line %d", op_new->file, op_new->line);
              return;
            }
            // Object type
            else if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
              SPVM_BASIC_TYPE* basic_type = SPVM_HASH_get(compiler->basic_type_symtable, type->basic_type->name, strlen(type->basic_type->name));
              
              if (basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE) {
                SPVM_COMPILER_error(compiler, "The type of the operand of new operator cannnot be an interface type.\n  at %s line %d", op_new->file, op_new->line);
                return;
              }
              else if (basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM) {
                SPVM_COMPILER_error(compiler, "The type of the operand of new operator cannnot be a multi-numeric type.\n  at %s line %d", op_new->file, op_new->line);
                return;
              }

              SPVM_BASIC_TYPE* current_basic_type = method->current_basic_type;
              if (!SPVM_CHECK_can_access(compiler, current_basic_type, new_basic_type, new_basic_type->access_control_type, 0)) {
                if (!SPVM_OP_is_allowed(compiler, current_basic_type, new_basic_type, 0)) {
                  SPVM_COMPILER_error(compiler, "The object of the %s %s class cannnot be created from the current class %s.\n  at %s line %d", SPVM_ATTRIBUTE_get_name(compiler, new_basic_type->access_control_type), new_basic_type->name, current_basic_type->name, op_new->file, op_new->line);
                  return;
                }
              }
            }
            else {
              assert(0);
            }
            
            break;
          }
          case SPVM_OP_C_ID_BIT_XOR: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            // Can receive only integer type
            if (!SPVM_TYPE_is_integer_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag) || !SPVM_TYPE_is_integer_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The left and right operand of ^ operator must be an integer type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            SPVM_CHECK_perform_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_ISA: {
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_OP* op_type = op_cur->last;
            
            SPVM_TYPE* type = op_type->uv.type;
            
            if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)
              || SPVM_TYPE_is_mulnum_type(compiler, type->basic_type->id, type->dimension, type->flag)
              || SPVM_TYPE_is_ref_type(compiler, type->basic_type->id, type->dimension, type->flag))
            {
              int32_t need_data_conversion = 0;
              int32_t allow_narrowing_conversion = 0;
              
              char error_reason[1024] = {0};
              int32_t satisfy_assignment_requirement_without_data_conversion = SPVM_TYPE_satisfy_assignment_requirement_without_data_conversion(
                compiler,
                type->basic_type->id, type->dimension, type->flag,
                operand_type->basic_type->id, operand_type->dimension, operand_type->flag,
                error_reason
              );
              
              if (satisfy_assignment_requirement_without_data_conversion) {
                SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                SPVM_OP* op_constant_true = SPVM_OP_new_op_constant_int(compiler, 1, op_cur->file, op_cur->line);
                SPVM_OP_replace_op(compiler, op_stab, op_constant_true);
                op_cur = op_constant_true;
              }
              else {
                if (strlen(error_reason)) {
                  SPVM_COMPILER_error(compiler, error_reason);
                }
                SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                SPVM_OP* op_constant_false = SPVM_OP_new_op_constant_int(compiler, 0, op_cur->file, op_cur->line);
                SPVM_OP_replace_op(compiler, op_stab, op_constant_false);
                op_cur = op_constant_false;
              }
            }
            else if (SPVM_TYPE_is_any_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
              SPVM_COMPILER_error(compiler, "The right type of isa operator must not be any object type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            else if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
              if (!SPVM_TYPE_is_object_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                SPVM_COMPILER_error(compiler, "The type of the left operand of isa operator must be an object type.\n  at %s line %d", op_cur->file, op_cur->line);
                return;
              }
            }
            else {
              assert(0);
            }
            
            break;
          }
          case SPVM_OP_C_ID_IS_TYPE: {
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_OP* op_type = op_cur->last;
            
            SPVM_TYPE* type = op_type->uv.type;
            
            if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)
              || SPVM_TYPE_is_mulnum_type(compiler, type->basic_type->id, type->dimension, type->flag)
              || SPVM_TYPE_is_ref_type(compiler, type->basic_type->id, type->dimension, type->flag))
            {
              if (operand_type->basic_type->id == type->basic_type->id && operand_type->dimension == type->dimension) {
                SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                SPVM_OP* op_constant_true = SPVM_OP_new_op_constant_int(compiler, 1, op_cur->file, op_cur->line);
                SPVM_OP_replace_op(compiler, op_stab, op_constant_true);
                op_cur = op_constant_true;
              }
              else {
                SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                SPVM_OP* op_constant_false = SPVM_OP_new_op_constant_int(compiler, 0, op_cur->file, op_cur->line);
                SPVM_OP_replace_op(compiler, op_stab, op_constant_false);
                op_cur = op_constant_false;
              }
            }
            else if (SPVM_TYPE_is_any_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
              SPVM_COMPILER_error(compiler, "The right type of is_type operator must not be any object type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            else if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
              if (!SPVM_TYPE_is_object_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                SPVM_COMPILER_error(compiler, "The type of the left operand of is_type operator must be an object type.\n  at %s line %d", op_cur->file, op_cur->line);
                return;
              }
            }
            else {
              assert(0);
            }
            
            break;
          }
          case SPVM_OP_C_ID_IS_COMPILE_TYPE: {
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_OP* op_type = op_cur->last;
            
            SPVM_TYPE* type = op_type->uv.type;
            
            // If left type is same as right type, this return true. Otherwise, return false
            if (operand_type->basic_type->id == type->basic_type->id && operand_type->dimension == type->dimension) {
              SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
              SPVM_OP* op_constant_true = SPVM_OP_new_op_constant_int(compiler, 1, op_cur->file, op_cur->line);
              SPVM_OP_replace_op(compiler, op_stab, op_constant_true);
              op_cur = op_constant_true;
            }
            else {
              SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
              SPVM_OP* op_constant_false = SPVM_OP_new_op_constant_int(compiler, 0, op_cur->file, op_cur->line);
              SPVM_OP_replace_op(compiler, op_stab, op_constant_false);
              op_cur = op_constant_false;
            }
            
            break;
          }
          case SPVM_OP_C_ID_ISA_ERROR: {
            
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            if (!SPVM_TYPE_is_integer_type_within_int(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the operand of isa_error operator must be an integer type within int.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            SPVM_CHECK_perform_integer_promotional_conversion(compiler, op_cur->first);
            
            if (!SPVM_TYPE_is_class_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
              SPVM_COMPILER_error(compiler, "The type given to the isa_error operator must be a class type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_IS_ERROR: {
            
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            if (!SPVM_TYPE_is_integer_type_within_int(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the operand of is_error operator must be an integer type within int.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            SPVM_CHECK_perform_integer_promotional_conversion(compiler, op_cur->first);
            
            if (!SPVM_TYPE_is_class_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
              SPVM_COMPILER_error(compiler, "The type given to the is_error operator must be a class type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_ARRAY_LENGTH: {
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            
            // First value must be an array
            if (!SPVM_TYPE_is_array_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of @ operator must be an array type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_STRING_LENGTH: {
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            
            // First must be string type
            if (!SPVM_TYPE_is_string_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the operand of length operator must be string type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_ASSIGN: {
            SPVM_OP* op_dist = op_cur->last;
            SPVM_OP* op_src = op_cur->first;
            
            SPVM_TYPE* dist_type = SPVM_CHECK_get_type(compiler, op_dist);
            
            // Type inference
            if (op_dist->id == SPVM_OP_C_ID_VAR) {
              SPVM_VAR_DECL* var_decl = op_dist->uv.var->var_decl;
              if (var_decl->type == NULL) {
                var_decl->type = SPVM_CHECK_get_type(compiler, op_src);
              }
              assert(var_decl->type);
              if (SPVM_TYPE_is_undef_type(compiler, var_decl->type->basic_type->id, var_decl->type->dimension, var_decl->type->flag)) {
                SPVM_COMPILER_error(compiler, "The type of %s local variable cannnot be undef type.\n  at %s line %d", op_dist->uv.var->name, var_decl->op_var_decl->file, var_decl->op_var_decl->line);
                return;
              }
              op_dist->uv.var->is_initialized = 1;
            }
            
            // Check if source can be assigned to dist
            // If needed, numeric conversion op is added
            dist_type = SPVM_CHECK_get_type(compiler, op_dist);
            SPVM_CHECK_check_assign(compiler, dist_type, op_src, "assignment operator", op_cur->file, op_cur->line);
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }
            
            if (op_dist->id == SPVM_OP_C_ID_ELEMENT_ACCESS && op_dist->flag & SPVM_OP_C_FLAG_ELEMENT_ACCESS_STRING) {
              SPVM_OP* op_array = op_dist->first;
              SPVM_TYPE* array_type = SPVM_CHECK_get_type(compiler, op_array);
              int32_t is_mutable = array_type->flag & SPVM_NATIVE_C_TYPE_FLAG_MUTABLE;
              
              if(!is_mutable) {
                SPVM_COMPILER_error(compiler, "Characters cannot be set to non-mutable strings.\n  at %s line %d", op_dist->file, op_dist->line);
                return;
              }
            }
            
            break;
          }
          case SPVM_OP_C_ID_RETURN: {
            
            SPVM_OP* op_operand = op_cur->first;
            
            if (SPVM_TYPE_is_void_type(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag)) {
              if (op_operand) {
                SPVM_COMPILER_error(compiler, "The void method cannnot return the value.\n  at %s line %d", op_cur->file, op_cur->line);
                return;
              }
            }
            else {
              if (op_operand) {
                SPVM_CHECK_check_assign(compiler, method->return_type, op_operand, "the return statement", op_cur->file, op_cur->line);
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
              }
              else {
                SPVM_COMPILER_error(compiler, "The non-void method must return a value.\n  at %s line %d", op_cur->file, op_cur->line);
                return;
              }
            }
            
            break;
          }
          case SPVM_OP_C_ID_PLUS: {
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            
            if (!SPVM_TYPE_is_numeric_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the operand of unary + operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            SPVM_CHECK_perform_integer_promotional_conversion(compiler, op_cur->first);
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_MINUS: {
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            
            if (!SPVM_TYPE_is_numeric_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the operand of unary - operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            SPVM_CHECK_perform_integer_promotional_conversion(compiler, op_cur->first);
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_COPY: {
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            
            int32_t is_copyable_type
              =  SPVM_TYPE_is_string_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)
              || SPVM_TYPE_is_numeric_array_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)
              || SPVM_TYPE_is_mulnum_array_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag);
            
            if (!is_copyable_type) {
              SPVM_COMPILER_error(compiler, "The type of the operand of copy operator must be string type, a numeric type, or a multi-numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_BIT_NOT: {
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            
            if (!SPVM_TYPE_is_integer_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the operand of ~ operator must be an integer type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            SPVM_CHECK_perform_integer_promotional_conversion(compiler, op_cur->first);
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_ADD: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            if (!SPVM_TYPE_is_numeric_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              if (op_cur->original_id == SPVM_OP_C_ID_PRE_INC || op_cur->original_id == SPVM_OP_C_ID_POST_INC) {
                SPVM_COMPILER_error(compiler, "The type of the operand of increment operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              }
              else {
                SPVM_COMPILER_error(compiler, "The type of the left operand of + operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              }
              
              return;
            }
            
            if (!SPVM_TYPE_is_numeric_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of + operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            SPVM_CHECK_perform_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }
                                            
            break;
          }
          case SPVM_OP_C_ID_SUBTRACT: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            if (!SPVM_TYPE_is_numeric_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              if (op_cur->original_id == SPVM_OP_C_ID_PRE_DEC || op_cur->original_id == SPVM_OP_C_ID_POST_DEC) {
                SPVM_COMPILER_error(compiler, "The type of the operand of decrement operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              }
              else {
                SPVM_COMPILER_error(compiler, "The type of the left operand of - operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              }
              return;
            }
            
            if (!SPVM_TYPE_is_numeric_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of - operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            SPVM_CHECK_perform_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_MULTIPLY: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            if (!SPVM_TYPE_is_numeric_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of * operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            if (!SPVM_TYPE_is_numeric_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of * operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            SPVM_CHECK_perform_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_DIVIDE: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            if (!SPVM_TYPE_is_numeric_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of / operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            if (!SPVM_TYPE_is_numeric_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of / operator must be a numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            SPVM_CHECK_perform_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }

            break;
          }
          case SPVM_OP_C_ID_DIVIDE_UNSIGNED_INT: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            if (!SPVM_TYPE_is_int_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of div_uint operator must be int type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            if (!SPVM_TYPE_is_int_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of div_uint operator must be int type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_DIVIDE_UNSIGNED_LONG: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            if (!SPVM_TYPE_is_long_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of div_ulong operator must be long type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            if (!SPVM_TYPE_is_long_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of div_ulong operator must be long type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_MODULO: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            if (!SPVM_TYPE_is_integer_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of %% operator must be an integer type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            if (!SPVM_TYPE_is_integer_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of %% operator must be an integer type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            SPVM_CHECK_perform_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }
                                            
            break;
          }
          case SPVM_OP_C_ID_MODULO_UNSIGNED_INT: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            if (!SPVM_TYPE_is_int_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of mod_uint operator must be int type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            if (!SPVM_TYPE_is_int_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of mod_uint operator must be int type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_MODULO_UNSIGNED_LONG: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            // Left operand must be a numeric type
            if (!SPVM_TYPE_is_long_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of mod_ulong operator must be long type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }

            // Right operand must be a numeric type
            if (!SPVM_TYPE_is_long_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of mod_ulong operator must be long type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_BIT_AND: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            // Left operand must be integer type
            if (!SPVM_TYPE_is_integer_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of & operator must be an integer type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }

            // Right operand must be integer type
            if (!SPVM_TYPE_is_integer_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of & operator must be an integer type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            SPVM_CHECK_perform_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_BIT_OR: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            // Left operand must be integer type
            if (!SPVM_TYPE_is_integer_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the left operand of | operator must be an integer type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }

            // Right operand must be integer type
            if (!SPVM_TYPE_is_integer_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The right operand of | operator must be an integer type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            SPVM_CHECK_perform_binary_numeric_conversion(compiler, op_cur->first, op_cur->last);
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_LEFT_SHIFT: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            // Left operand must be a numeric type
            if (SPVM_TYPE_is_integer_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_CHECK_perform_integer_promotional_conversion(compiler, op_cur->first);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
            }
            else {
              SPVM_COMPILER_error(compiler, "The type of the left operand of << operator must be an integer type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            // Right operand must be int type
            if (SPVM_TYPE_is_integer_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_CHECK_perform_integer_promotional_conversion(compiler, op_cur->last);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              if (right_operand_type->dimension == 0 && right_operand_type->basic_type->id >= SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                SPVM_COMPILER_error(compiler, "The right operand of << operator must be int type.\n  at %s line %d", op_cur->file, op_cur->line);
                return;
              }
            }
            else {
              SPVM_COMPILER_error(compiler, "The right operand of << operator must be int type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_RIGHT_ARITHMETIC_SHIFT: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            // Left operand must be a numeric type
            if (SPVM_TYPE_is_integer_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_CHECK_perform_integer_promotional_conversion(compiler, op_cur->first);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
            }
            else {
              SPVM_COMPILER_error(compiler, "The type of the left operand of >> operator must be an integer type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            // Right operand must be int type
            if (SPVM_TYPE_is_integer_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_CHECK_perform_integer_promotional_conversion(compiler, op_cur->last);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              if (right_operand_type->dimension == 0 && right_operand_type->basic_type->id >= SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                SPVM_COMPILER_error(compiler, "The right operand of >> operator must be int type.\n  at %s line %d", op_cur->file, op_cur->line);
                return;
              }
            }
            else {
              SPVM_COMPILER_error(compiler, "The right operand of >> operator must be int type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_RIGHT_LOGICAL_SHIFT: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            // Left operand must be a numeric type
            if (SPVM_TYPE_is_integer_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              SPVM_CHECK_perform_integer_promotional_conversion(compiler, op_cur->first);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
            }
            else {
              SPVM_COMPILER_error(compiler, "The type of the left operand of >>> operator must be an integer type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            // Right operand must be int type
            if (SPVM_TYPE_is_integer_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_CHECK_perform_integer_promotional_conversion(compiler, op_cur->last);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              if (right_operand_type->dimension == 0 && right_operand_type->basic_type->id >= SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                SPVM_COMPILER_error(compiler, "The right operand of >>> operator must be int type.\n  at %s line %d", op_cur->file, op_cur->line);
                return;
              }
            }
            else {
              SPVM_COMPILER_error(compiler, "The right operand of >>> operator must be int type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_DIE: {
            SPVM_TYPE* error_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            // Type
            if (op_cur->last->id == SPVM_OP_C_ID_TYPE) {
              if (!SPVM_TYPE_is_class_type(compiler, error_type->basic_type->id, error_type->dimension, error_type->flag)) {
                SPVM_COMPILER_error(compiler, "The error class of the die statement must be a class type.\n  at %s line %d", op_cur->file, op_cur->line);
                return;
              }
            }
            // Basic type ID
            else {
              if (!SPVM_TYPE_is_integer_type_within_int(compiler, error_type->basic_type->id, error_type->dimension, error_type->flag)) {
                SPVM_COMPILER_error(compiler, "The error ID must be an integer type within int.\n  at %s line %d", op_cur->file, op_cur->line);
                return;
              }
              
              SPVM_CHECK_perform_integer_promotional_conversion(compiler, op_cur->last);
            }
            
            break;
          }
          case SPVM_OP_C_ID_WARN: {
            if (op_cur->first) {
              SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
              
              if (SPVM_TYPE_is_numeric_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                SPVM_CHECK_perform_numeric_to_string_conversion(compiler, op_cur->first);
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
              }
              
              operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
              
              if (!SPVM_TYPE_is_object_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
                SPVM_COMPILER_error(compiler, "The type of the operand of warn operator must be an object type.\n  at %s line %d", op_cur->file, op_cur->line);
                return;
              }
            }
            
            break;
          }
          case SPVM_OP_C_ID_PRINT: {
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            
            if (SPVM_TYPE_is_numeric_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              SPVM_CHECK_perform_numeric_to_string_conversion(compiler, op_cur->first);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
            }
            
            operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            
            if (!SPVM_TYPE_is_string_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the operand of print operator must be string type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            break;
          }
          case SPVM_OP_C_ID_SAY: {
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            
            if (SPVM_TYPE_is_numeric_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              SPVM_CHECK_perform_numeric_to_string_conversion(compiler, op_cur->first);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
            }
            
            operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            
            if (!SPVM_TYPE_is_string_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the operand of say operator must be string type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            break;
          }
          case SPVM_OP_C_ID_MAKE_READ_ONLY: {
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            
            operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            
            if (!SPVM_TYPE_is_string_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the operand of make_read_only operator must be string type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            break;
          }
          case SPVM_OP_C_ID_IS_READ_ONLY: {
            SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            
            operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            
            if (!SPVM_TYPE_is_string_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag)) {
              SPVM_COMPILER_error(compiler, "The type of the operand of is_read_only operator must be string type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            break;
          }
          case SPVM_OP_C_ID_BLOCK: {
            SPVM_BLOCK* block = op_cur->uv.block;
            // End of scope
            if (!block->no_scope) {
              // Pop block var_decl variable base
              assert(var_decl_scope_base_stack->length > 0);
              int32_t block_var_decl_base = (intptr_t)SPVM_LIST_pop(var_decl_scope_base_stack);
                
              int32_t var_decl_stack_pop_count = var_decl_stack->length - block_var_decl_base;
              
              for (int32_t i = 0; i < var_decl_stack_pop_count; i++) {
                SPVM_LIST_pop(var_decl_stack);
              }
            }
            
            // Pop loop block var_decl variable base
            if (block->id == SPVM_BLOCK_C_ID_LOOP_STATEMENTS) {
              loop_block_stack_length--;
            }
            // Pop try block var_decl variable base
            else if (block->id == SPVM_BLOCK_C_ID_EVAL) {
              eval_block_stack_length--;
            }
            
            break;
          }
          case SPVM_OP_C_ID_REFERENCE: {
            
            SPVM_OP* op_var = op_cur->first;
            SPVM_TYPE* var_type = SPVM_CHECK_get_type(compiler, op_var);
            if (!(SPVM_TYPE_is_numeric_type(compiler, var_type->basic_type->id, var_type->dimension, var_type->flag) || SPVM_TYPE_is_mulnum_type(compiler, var_type->basic_type->id, var_type->dimension, var_type->flag))) {
              SPVM_COMPILER_error(compiler, "The type of the operand of refernece operator must be a numeric type or a multi-numeric type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_DEREFERENCE: {
            SPVM_OP* op_var = op_cur->first;
            SPVM_TYPE* var_type = SPVM_CHECK_get_type(compiler, op_var);
            
            if (!(SPVM_TYPE_is_numeric_ref_type(compiler, var_type->basic_type->id, var_type->dimension, var_type->flag) || SPVM_TYPE_is_mulnum_ref_type(compiler, var_type->basic_type->id, var_type->dimension, var_type->flag))) {
              SPVM_COMPILER_error(compiler, "The type of the operand of dereference operaotr must be a numeric reference type or a multi-numeric reference type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          // Local variable or class variable
          case SPVM_OP_C_ID_VAR: {
            
            if (op_cur->uv.var->is_declaration) {
              
              SPVM_VAR_DECL* var_decl = op_cur->uv.var->var_decl;
              
              // Redeclaration error if same name variable is declare in same block
              int32_t found = 0;
              int32_t block_var_decl_base = (intptr_t)SPVM_LIST_get(var_decl_scope_base_stack, var_decl_scope_base_stack->length - 1);
              for (int32_t i = block_var_decl_base; i < var_decl_stack->length; i++) {
                SPVM_VAR_DECL* bef_var_decl = SPVM_LIST_get(var_decl_stack, i);
                
                if (strcmp(var_decl->var->name, bef_var_decl->var->name) == 0) {
                  // Temporaly variable is not duplicated
                  if (strncmp(var_decl->var->name, "$.", 2) != 0) {
                    found = 1;
                  }
                  break;
                }
              }
              
              if (found) {
                SPVM_COMPILER_error(compiler, "Redeclaration of %s variable.\n  at %s line %d", var_decl->var->name, var_decl->op_var_decl->file, var_decl->op_var_decl->line);
                return;
              }
              else {
                var_decl->index = method->var_decls->length;
                SPVM_LIST_push(method->var_decls, var_decl);
                SPVM_LIST_push(var_decl_stack, var_decl);
              }
              
              // Type cannnot be detected
              if (!op_cur->is_dist && var_decl->type == NULL) {
                SPVM_COMPILER_error(compiler, "The type of %s variable is not detected.\n  at %s line %d", op_cur->uv.var->name, var_decl->op_var_decl->file, var_decl->op_var_decl->line);
                return;
              }
            }
            
            SPVM_VAR* var = op_cur->uv.var;
            
            // Search same name variable
            SPVM_VAR_DECL* found_var_decl = NULL;
            for (int32_t i = var_decl_stack->length - 1; i >= 0; i--) {
              SPVM_VAR_DECL* var_decl = SPVM_LIST_get(var_decl_stack, i);
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
              // Search a class variable
              SPVM_OP* op_name_basic_type_var = SPVM_OP_new_op_name(compiler, op_cur->uv.var->name, op_cur->file, op_cur->line);
              SPVM_OP* op_class_var_access = SPVM_OP_new_op_class_var_access(compiler, op_name_basic_type_var);
              
              op_class_var_access->is_dist = op_cur->is_dist;
              
              SPVM_CHECK_check_class_var_access(compiler, op_class_var_access, method);
              if (op_class_var_access->uv.class_var_access->class_var) {
                
                SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                
                // Check field name
                SPVM_CHECK_check_class_var_access(compiler, op_class_var_access, method);
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
                
                SPVM_CLASS_VAR_ACCESS* class_var_access = op_class_var_access->uv.class_var_access;
                SPVM_CLASS_VAR* class_var = class_var_access->class_var;
                SPVM_BASIC_TYPE* class_var_access_basic_type = class_var->current_basic_type;
                
                if (!SPVM_CHECK_can_access(compiler, method->current_basic_type, class_var_access_basic_type, class_var_access->class_var->access_control_type, 0)) {
                  if (!SPVM_OP_is_allowed(compiler, method->current_basic_type, class_var_access_basic_type, 0)) {
                    SPVM_COMPILER_error(compiler, "The %s %s#%s class variable cannnot be accessed from the current class %s.\n  at %s line %d", SPVM_ATTRIBUTE_get_name(compiler, class_var_access->class_var->access_control_type), class_var_access_basic_type->name, class_var->name, method->current_basic_type->name, op_class_var_access->file, op_class_var_access->line);
                    return;
                  }
                }
                
                var->class_var = class_var;
                
                SPVM_OP_replace_op(compiler, op_stab, op_class_var_access);
                
                op_cur = op_class_var_access;
              }
              else {
                SPVM_COMPILER_error(compiler, "%s variable is not found.\n  at %s line %d", var->name, op_cur->file, op_cur->line);
                return;
              }
            }
            
            break;
          }
          case SPVM_OP_C_ID_CALL_METHOD: {
            
            SPVM_OP* op_call_method = op_cur;

            assert(op_cur->first->id == SPVM_OP_C_ID_LIST);
                
            
            // Check method
            SPVM_CHECK_check_call_method(compiler, op_cur, method);
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }
            
            SPVM_OP* op_list_args = op_cur->first;
            
            SPVM_CALL_METHOD* call_method = op_call_method->uv.call_method;
            const char* method_name = call_method->method->name;

            if (!SPVM_CHECK_can_access(compiler, method->current_basic_type, call_method->method->current_basic_type, call_method->method->access_control_type, 0)) {
              if (!SPVM_OP_is_allowed(compiler, method->current_basic_type, call_method->method->current_basic_type, 0)) {
                SPVM_COMPILER_error(compiler, "The %s %s#%s method cannnot be called from the current class %s.\n  at %s line %d", SPVM_ATTRIBUTE_get_name(compiler, call_method->method->access_control_type), call_method->method->current_basic_type->name, call_method->method->name, method->current_basic_type->name, op_cur->file, op_cur->line);
                return;
              }
            }
            
            int32_t args_length = call_method->method->args_length;
            
            int32_t call_method_args_length = 0;
            {
              SPVM_OP* op_operand = op_list_args->first;
              while ((op_operand = SPVM_OP_sibling(compiler, op_operand))) {
                call_method_args_length++;
                if (call_method_args_length > args_length) {
                  int32_t args_length_for_user = args_length;
                  if (!call_method->method->is_class_method) {
                    args_length_for_user--;
                  }
                  
                  SPVM_COMPILER_error(compiler, "Too many arguments are passed to %s#%s method.\n  at %s line %d", op_cur->uv.call_method->method->current_basic_type->name, method_name, op_cur->file, op_cur->line);
                  
                  return;
                }
                
                SPVM_VAR_DECL* arg_var_decl = SPVM_LIST_get(call_method->method->var_decls, call_method_args_length - 1);
                SPVM_TYPE* arg_var_decl_type = arg_var_decl->type;
                
                // Check if source can be assigned to dist
                // If needed, numeric conversion op is added
                char place[255];
                int32_t call_method_args_length_for_user = call_method_args_length;
                if (!call_method->method->is_class_method) {
                  call_method_args_length_for_user--;
                }
                sprintf(place, "the %dth argument of %s#%s method", call_method_args_length_for_user, op_cur->uv.call_method->method->current_basic_type->name, method_name);
                
                // Invocant is not checked.
                op_operand = SPVM_CHECK_check_assign(compiler, arg_var_decl_type, op_operand, place, op_cur->file, op_cur->line);
                
                if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                  return;
                }
              }
            }
            
            if (call_method_args_length < call_method->method->required_args_length) {
              int32_t required_args_length_for_user = call_method->method->required_args_length;
              if (!call_method->method->is_class_method) {
                required_args_length_for_user--;
              }
              
              SPVM_COMPILER_error(compiler, "Too few arguments are passed to %s#%s method.\n  at %s line %d", op_cur->uv.call_method->method->current_basic_type->name, method_name, op_cur->file, op_cur->line);
              
              return;
            }
            
            call_method->args_length = call_method_args_length;
            
            // A method call to get a enumeration value is replaced to a constant value
            if (call_method->method->is_enum) {
              // Replace method to constant
              SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
              
              int32_t enum_value = call_method->method->enum_value;
              SPVM_OP* op_constant = SPVM_OP_new_op_constant_int(compiler, enum_value, op_cur->file, op_cur->line);
              
              SPVM_OP_replace_op(compiler, op_stab, op_constant);
              
              op_cur = op_constant;
            }
            
            if (call_method->method->is_class_method) {
              SPVM_BASIC_TYPE_add_constant_string(compiler, basic_type, call_method->method->current_basic_type->name, strlen(call_method->method->current_basic_type->name));
            }
            
            SPVM_BASIC_TYPE_add_constant_string(compiler, basic_type, call_method->method->name, strlen(call_method->method->name));
            
            break;
          }
          case SPVM_OP_C_ID_ELEMENT_ACCESS: {
            SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_cur->first);
            SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
            
            // Left operand must be an array or string
            if (!SPVM_TYPE_is_array_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag) &&
              !SPVM_TYPE_is_string_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)
            )
            {
              SPVM_COMPILER_error(compiler, "The invocant of the element access must be an array type or string type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            // String access
            if (SPVM_TYPE_is_string_type(compiler, left_operand_type->basic_type->id, left_operand_type->dimension, left_operand_type->flag)) {
              op_cur->flag |= SPVM_OP_C_FLAG_ELEMENT_ACCESS_STRING;
            }
            
            // Right operand must be integer
            if (SPVM_TYPE_is_numeric_type(compiler, right_operand_type->basic_type->id, right_operand_type->dimension, right_operand_type->flag)) {
              SPVM_CHECK_perform_integer_promotional_conversion(compiler, op_cur->last);
              if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
                return;
              }
              
              SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_cur->last);
              
              if (right_operand_type->dimension == 0 && right_operand_type->basic_type->id != SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                SPVM_COMPILER_error(compiler, "The index of the element access must be int type.\n  at %s line %d", op_cur->file, op_cur->line);
                return;
              }
            }
            else {
              SPVM_COMPILER_error(compiler, "The index of the element access must be int type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            break;
          }
          case SPVM_OP_C_ID_FIELD_ACCESS: {
            SPVM_OP* op_invocant = op_cur->first;
            SPVM_OP* op_name = op_cur->uv.field_access->op_name;
            
            if (op_invocant->id == SPVM_OP_C_ID_ASSIGN) {
              op_invocant = op_invocant->first;
            }
            
            // Invoker type check
            SPVM_TYPE* invocant_type = SPVM_CHECK_get_type(compiler, op_invocant);
            int32_t is_valid_invocant_type;
            if (invocant_type) {
              if (SPVM_TYPE_is_class_type(compiler, invocant_type->basic_type->id, invocant_type->dimension, invocant_type->flag)) {
                is_valid_invocant_type = 1;
              }
              else if (SPVM_TYPE_is_mulnum_type(compiler, invocant_type->basic_type->id, invocant_type->dimension, invocant_type->flag)) {
                is_valid_invocant_type = 1;
              }
              else if (SPVM_TYPE_is_mulnum_ref_type(compiler, invocant_type->basic_type->id, invocant_type->dimension, invocant_type->flag)) {
                is_valid_invocant_type = 1;
              }
              else {
                is_valid_invocant_type = 0;
              }
            }
            else {
              is_valid_invocant_type = 0;
            }
            if (!is_valid_invocant_type) {
              SPVM_COMPILER_error(compiler, "The invocant of the field access must be a class type, or a multi-numeric type, or a multi-numeric reference type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            // Check field name
            SPVM_CHECK_check_field_access(compiler, op_cur);
            if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
              return;
            }
            
            SPVM_FIELD* field = op_cur->uv.field_access->field;
            
            if (!field) {
              const char* invocant_type_name = SPVM_TYPE_new_type_name(compiler, invocant_type->basic_type->id, invocant_type->dimension, invocant_type->flag);
              SPVM_COMPILER_error(compiler, "The %s#%s field is not found.\n  at %s line %d", invocant_type_name, op_name->uv.name, op_cur->file, op_cur->line);
              return;
            }
            
            // weaken operator
            if (op_cur->flag & SPVM_OP_C_FLAG_FIELD_ACCESS_WEAKEN) {
              if (!SPVM_TYPE_is_object_type(compiler, field->type->basic_type->id, field->type->dimension, field->type->flag)) {
                SPVM_COMPILER_error(compiler, "The %s#%s field operated by weaken operator must be an object type.\n  at %s line %d", field->current_basic_type->name, field->op_name->uv.name, op_cur->file, op_cur->line);
                return;
              }
            }
            // unweaken operator
            else if (op_cur->flag & SPVM_OP_C_FLAG_FIELD_ACCESS_UNWEAKEN) {
              if (!SPVM_TYPE_is_object_type(compiler, field->type->basic_type->id, field->type->dimension, field->type->flag)) {
                SPVM_COMPILER_error(compiler, "The %s#%s field operated by unweaken operator must be an object type.\n  at %s line %d", field->current_basic_type->name, field->op_name->uv.name, op_cur->file, op_cur->line);
                return;
              }
            }
            // isweak operator
            else if (op_cur->flag & SPVM_OP_C_FLAG_FIELD_ACCESS_ISWEAK) {
              if (!SPVM_TYPE_is_object_type(compiler, field->type->basic_type->id, field->type->dimension, field->type->flag)) {
                SPVM_COMPILER_error(compiler, "The %s#%s field operated by isweak operator must be an object type.\n  at %s line %d", field->current_basic_type->name, field->op_name->uv.name, op_cur->file, op_cur->line);
                return;
              }
            }

            SPVM_FIELD_ACCESS* field_access = op_cur->uv.field_access;
            
            SPVM_FIELD* found_field_in_current_basic_type = SPVM_HASH_get(method->current_basic_type->unmerged_field_symtable, field_access->field->name, strlen(field_access->field->name));
            
            int32_t is_parent_field = !found_field_in_current_basic_type && !method->current_basic_type->is_generated_by_anon_method;
            
            if (!SPVM_CHECK_can_access(compiler, method->current_basic_type,  field_access->field->current_basic_type, field_access->field->access_control_type, is_parent_field)) {
              if (!SPVM_OP_is_allowed(compiler, method->current_basic_type, field->current_basic_type, is_parent_field)) {
                
                SPVM_FIELD* found_unmerged_field = SPVM_CHECK_search_unmerged_field(compiler, field->current_basic_type, field->name);
                
                SPVM_COMPILER_error(compiler, "The %s %s#%s field cannnot be accessed from the current class %s.\n  at %s line %d", SPVM_ATTRIBUTE_get_name(compiler, field_access->field->access_control_type), found_unmerged_field->current_basic_type->name, found_unmerged_field->name, method->current_basic_type->name, op_cur->file, op_cur->line);
                return;
              }
            }
            
            // If invocant is element access and element access object is mulnum_t, this op is multi-numeric array field access
            if (op_invocant->id == SPVM_OP_C_ID_ELEMENT_ACCESS) {
              SPVM_OP* op_element_access = op_invocant;
              
              SPVM_TYPE* array_element_type = SPVM_CHECK_get_type(compiler, op_element_access);
              
              int32_t is_basic_type_mulnum_t = SPVM_BASIC_TYPE_is_mulnum_type(compiler, array_element_type->basic_type->id);
              if (is_basic_type_mulnum_t && array_element_type->dimension == 0) {
                SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
                
                SPVM_OP* op_array_field_access = SPVM_OP_new_op_array_field_access(compiler, op_cur->file, op_cur->line);
                op_array_field_access->is_dist = op_cur->is_dist;

                SPVM_ARRAY_FIELD_ACCESS* array_field_access = op_array_field_access->uv.array_field_access;
                array_field_access->field = field;
                
                SPVM_OP* op_array = op_element_access->first;
                SPVM_OP* op_index = op_element_access->last;
                SPVM_OP_cut_op(compiler, op_element_access->first);
                SPVM_OP_cut_op(compiler, op_element_access->last);
                
                SPVM_OP_insert_child(compiler, op_array_field_access, op_array_field_access->last, op_array);
                SPVM_OP_insert_child(compiler, op_array_field_access, op_array_field_access->last, op_index);
                
                SPVM_OP_replace_op(compiler, op_stab, op_array_field_access);
                
                op_cur = op_array_field_access;
              }
            }
            
            
            SPVM_BASIC_TYPE_add_constant_string(compiler, basic_type, field_access->field->current_basic_type->name, strlen(field_access->field->current_basic_type->name));
            
            SPVM_BASIC_TYPE_add_constant_string(compiler, basic_type, field_access->field->name, strlen(field_access->field->name));
            
            break;
          }
          case SPVM_OP_C_ID_CAN: {
            SPVM_OP* op_var = op_cur->first;
            SPVM_OP* op_name_method = op_cur->last;
            
            SPVM_TYPE* var_type = SPVM_CHECK_get_type(compiler, op_var);
            
            if (!(SPVM_TYPE_is_class_type(compiler, var_type->basic_type->id, var_type->dimension, var_type->flag) || SPVM_TYPE_is_interface_type(compiler, var_type->basic_type->id, var_type->dimension, var_type->flag))) {
              SPVM_COMPILER_error(compiler, "The invocant of can operator must be a class type or an interface type.\n  at %s line %d", op_cur->file, op_cur->line);
              return;
            }
            
            const char* var_basic_type_name = var_type->basic_type->name;
            SPVM_BASIC_TYPE* var_basic_type = SPVM_HASH_get(compiler->basic_type_symtable, var_basic_type_name, strlen(var_basic_type_name));
            
            const char* method_name = op_name_method->uv.name;
            SPVM_METHOD* found_method = SPVM_HASH_get(
              var_basic_type->method_symtable,
              method_name,
              strlen(method_name)
            );
            
            if (!found_method) {
              SPVM_COMPILER_error(compiler, "%s#%s method, the operand of can operator, must be defined.\n  at %s line %d", var_basic_type_name, method_name, op_name_method->file, op_name_method->line);
              return;
            }
            
            SPVM_BASIC_TYPE_add_constant_string(compiler, basic_type, method_name, strlen(method_name));
            
            break;
          }
          case SPVM_OP_C_ID_TYPE_CAST: {
            
            SPVM_OP* op_src = op_cur->first;
            SPVM_OP* op_cast = op_cur->last;
            
            SPVM_TYPE* src_type = SPVM_CHECK_get_type(compiler, op_src);
            assert(src_type);
            
            SPVM_TYPE* cast_type = SPVM_CHECK_get_type(compiler, op_cast);
            assert(cast_type);
            
            char error_reason[1024] = {0};
            int32_t castability = SPVM_TYPE_satisfy_cast_requirement(
              compiler,
              cast_type->basic_type->id, cast_type->dimension, cast_type->flag,
              src_type->basic_type->id, src_type->dimension, src_type->flag,
              error_reason
            );
            
            if (!castability) {
              if (strlen(error_reason)) {
                SPVM_COMPILER_error(compiler, error_reason);
              }
              
              const char* src_type_name = SPVM_TYPE_new_type_name(compiler, src_type->basic_type->id, src_type->dimension, src_type->flag);
              const char* cast_type_name = SPVM_TYPE_new_type_name(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag);
              SPVM_COMPILER_error(compiler, "The type cast from %s to %s is not allowed.\n  at %s line %d", src_type_name, cast_type_name, op_src->file, op_src->line);
              return;
            }
            
            // Remove type cast op if not needed
            if (SPVM_TYPE_equals(compiler, cast_type->basic_type->id, cast_type->dimension, cast_type->flag, src_type->basic_type->id, src_type->dimension, src_type->flag)) {
              SPVM_OP_cut_op(compiler, op_src);
              SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_cur);
              SPVM_OP_replace_op(compiler, op_stab, op_src);
              op_cur = op_src;
            }
          }
          break;
        }
        
        // [END]Postorder traversal position
        
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

void SPVM_CHECK_check_ast_assign_unassigned_op_to_var(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type, SPVM_METHOD* method) {
  
  if (!method->op_block) {
    return;
  }
  
  // check AST
  SPVM_OP* op_root = method->op_block;
  SPVM_OP* op_cur = op_root;
  int32_t finish = 0;
  while (op_cur) {
    // [START]Preorder traversal position
    switch (op_cur->id) {
      case SPVM_OP_C_ID_ASSIGN: {
        if (op_cur->last->id == SPVM_OP_C_ID_VAR) {
          op_cur->first->is_assigned_to_var = 1;
        }
        break;
      }
    }
    
    if (op_cur->first) {
      op_cur = op_cur->first;
    }
    else {
      while (1) {
        // [START]Postorder traversal position
        
        // Convert an operator to a assignment operator
        {
          int32_t convert_to_assign = 0;
          
          if (!op_cur->is_dist && !op_cur->is_assigned_to_var) {
            switch (op_cur->id) {
              case SPVM_OP_C_ID_TYPE_CAST:
              case SPVM_OP_C_ID_WARN:
              case SPVM_OP_C_ID_PRINT:
              case SPVM_OP_C_ID_SAY:
              case SPVM_OP_C_ID_MAKE_READ_ONLY:
              case SPVM_OP_C_ID_IS_READ_ONLY:
              case SPVM_OP_C_ID_ISWEAK_FIELD:
              case SPVM_OP_C_ID_CAN:
              case SPVM_OP_C_ID_ADD:
              case SPVM_OP_C_ID_SUBTRACT:
              case SPVM_OP_C_ID_MULTIPLY:
              case SPVM_OP_C_ID_DIVIDE:
              case SPVM_OP_C_ID_DIVIDE_UNSIGNED_INT:
              case SPVM_OP_C_ID_DIVIDE_UNSIGNED_LONG:
              case SPVM_OP_C_ID_MODULO:
              case SPVM_OP_C_ID_MODULO_UNSIGNED_INT:
              case SPVM_OP_C_ID_MODULO_UNSIGNED_LONG:
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
              case SPVM_OP_C_ID_BASIC_TYPE_ID:
              case SPVM_OP_C_ID_EVAL_ERROR_ID:
              case SPVM_OP_C_ID_ARGS_WIDTH:
              case SPVM_OP_C_ID_STRING_CONCAT:
              case SPVM_OP_C_ID_TYPE_NAME:
              case SPVM_OP_C_ID_COMPILE_TYPE_NAME:
              case SPVM_OP_C_ID_DUMP:
              case SPVM_OP_C_ID_NEW_STRING_LEN:
              case SPVM_OP_C_ID_EXCEPTION_VAR:
              case SPVM_OP_C_ID_CLASS_VAR_ACCESS:
              case SPVM_OP_C_ID_ARRAY_FIELD_ACCESS:
              case SPVM_OP_C_ID_REFERENCE:
              case SPVM_OP_C_ID_DEREFERENCE:
              case SPVM_OP_C_ID_FIELD_ACCESS:
              case SPVM_OP_C_ID_ELEMENT_ACCESS:
              case SPVM_OP_C_ID_CALL_METHOD:
              case SPVM_OP_C_ID_TRUE:
              case SPVM_OP_C_ID_FALSE:
              case SPVM_OP_C_ID_CONSTANT:
              case SPVM_OP_C_ID_NUMERIC_COMPARISON_EQ:
              case SPVM_OP_C_ID_NUMERIC_COMPARISON_NE:
              case SPVM_OP_C_ID_NUMERIC_COMPARISON_GT:
              case SPVM_OP_C_ID_NUMERIC_COMPARISON_GE:
              case SPVM_OP_C_ID_NUMERIC_COMPARISON_LT:
              case SPVM_OP_C_ID_NUMERIC_COMPARISON_LE:
              case SPVM_OP_C_ID_NUMERIC_COMPARISON_CMP:
              case SPVM_OP_C_ID_STRING_COMPARISON_EQ:
              case SPVM_OP_C_ID_STRING_COMPARISON_NE:
              case SPVM_OP_C_ID_STRING_COMPARISON_GT:
              case SPVM_OP_C_ID_STRING_COMPARISON_GE:
              case SPVM_OP_C_ID_STRING_COMPARISON_LT:
              case SPVM_OP_C_ID_STRING_COMPARISON_LE:
              case SPVM_OP_C_ID_STRING_COMPARISON_CMP:
              case SPVM_OP_C_ID_ISA:
              case SPVM_OP_C_ID_ISA_ERROR:
              case SPVM_OP_C_ID_IS_TYPE:
              case SPVM_OP_C_ID_IS_ERROR:
              case SPVM_OP_C_ID_IS_COMPILE_TYPE:
              case SPVM_OP_C_ID_BOOL:
              {
                convert_to_assign = 1;
                break;
              }
              case SPVM_OP_C_ID_LOOP_INCREMENT:
              case SPVM_OP_C_ID_CONDITION:
              case SPVM_OP_C_ID_CONDITION_NOT:
              case SPVM_OP_C_ID_NEXT:
              case SPVM_OP_C_ID_LAST:
              case SPVM_OP_C_ID_SWITCH:
              case SPVM_OP_C_ID_SWITCH_CONDITION:
              case SPVM_OP_C_ID_DEFAULT:
              case SPVM_OP_C_ID_CASE:
              case SPVM_OP_C_ID_BREAK:
              case SPVM_OP_C_ID_RETURN:
              case SPVM_OP_C_ID_DIE:
              case SPVM_OP_C_ID_VAR:
              case SPVM_OP_C_ID_ASSIGN:
              case SPVM_OP_C_ID_LIST:
              case SPVM_OP_C_ID_PUSHMARK:
              case SPVM_OP_C_ID_NAME:
              case SPVM_OP_C_ID_TYPE:
              case SPVM_OP_C_ID_BLOCK:
              case SPVM_OP_C_ID_IF:
              case SPVM_OP_C_ID_LOOP:
              case SPVM_OP_C_ID_EVAL:
              case SPVM_OP_C_ID_UNDEF:
              case SPVM_OP_C_ID_SEQUENCE:
              case SPVM_OP_C_ID_DO_NOTHING:
              case SPVM_OP_C_ID_WEAKEN_FIELD:
              case SPVM_OP_C_ID_UNWEAKEN_FIELD:
              {
                // Do nothing
                break;
              }
              default: {
                fprintf(stderr, "[Unexpected Error]The %s operator", SPVM_OP_get_op_name(compiler, op_cur->id));
                assert(0);
              }
            }
          }
          
          if (convert_to_assign) {
            SPVM_TYPE* tmp_var_type = SPVM_CHECK_get_type(compiler, op_cur);
            SPVM_OP* op_var_tmp = SPVM_CHECK_new_op_var_tmp(compiler, tmp_var_type, method, op_cur->file, op_cur->line);
            
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

void SPVM_CHECK_check_ast_if_block_need_leave_scope(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type, SPVM_METHOD* method) {
  
  // Block stack
  SPVM_LIST* op_block_stack = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  
  // Run OPs
  SPVM_OP* op_root = method->op_block;
  SPVM_OP* op_cur = op_root;
  int32_t finish = 0;
  while (op_cur) {
    // [START]Preorder traversal position
    switch (op_cur->id) {
      // Start scope
      case SPVM_OP_C_ID_BLOCK: {
        SPVM_BLOCK* block = op_cur->uv.block;
        
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
            SPVM_OP* op_block_current = op_cur;
            SPVM_BLOCK* block_current = op_block_current->uv.block;
            
            SPVM_LIST_pop(op_block_stack);
            
            // The current block needs the LEAVE_SCOPE opcode
            if (block_current->has_object_var_decls && !block_current->no_scope) {
              block_current->need_leave_scope = 1;
            }
            
            // The parent block needs the LEAVE_SCOPE opcode if the child block has object variable declarations
            if (op_block_stack->length > 0) {
              SPVM_OP* op_block_parent = SPVM_LIST_get(op_block_stack, op_block_stack->length - 1);
              SPVM_BLOCK* block_parent = op_block_parent->uv.block;
              
              if (block_current->has_object_var_decls) {
                block_parent->has_object_var_decls = 1;
              }
              
              if (block_current->has_object_var_decls && !block_parent->no_scope) {
                block_parent->need_leave_scope = 1;
              }
            }
            
            break;
          }
          case SPVM_OP_C_ID_VAR: {
            SPVM_OP* op_var = op_cur;
            
            SPVM_OP* op_block_current = SPVM_LIST_get(op_block_stack, op_block_stack->length - 1);
            SPVM_BLOCK* block_current = op_block_current->uv.block;
            
            if (op_var->uv.var->is_declaration) {
              SPVM_TYPE* var_type = SPVM_CHECK_get_type(compiler, op_var);
              if (SPVM_TYPE_is_object_type(compiler, var_type->basic_type->id, var_type->dimension, var_type->flag)) {
                block_current->has_object_var_decls = 1;
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

void SPVM_CHECK_check_ast_typed_var_indexs(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type, SPVM_METHOD* method) {
  
  SPVM_LIST* tmp_var_decl_stack = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);

  SPVM_LIST* runtime_vars_byte = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  SPVM_LIST* runtime_vars_short = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  SPVM_LIST* runtime_vars_int = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  SPVM_LIST* runtime_vars_long = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  SPVM_LIST* runtime_vars_float = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  SPVM_LIST* runtime_vars_double = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  SPVM_LIST* runtime_vars_object = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  SPVM_LIST* runtime_vars_ref = SPVM_LIST_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);

  // Run OPs
  SPVM_OP* op_root = method->op_block;
  SPVM_OP* op_cur = op_root;
  int32_t finish = 0;
  while (op_cur) {
    // [START]Preorder traversal position
    switch (op_cur->id) {
    }

    if (op_cur->first) {
      op_cur = op_cur->first;
    }
    else {
      while (1) {
        // [START]Postorder traversal position
        switch (op_cur->id) {
          case SPVM_OP_C_ID_BLOCK: {
            SPVM_BLOCK* block = op_cur->uv.block;
            // Move loop condition to last sibling before opcode building
            if (op_cur->uv.block->id == SPVM_BLOCK_C_ID_LOOP_INIT) {
              SPVM_OP* op_init = op_cur->first;
              SPVM_OP* op_condition = op_cur->first->sibparent;
              SPVM_OP* op_block_statements = op_cur->first->sibparent->sibparent;
              SPVM_OP* op_loop_increment = op_cur->first->sibparent->sibparent->sibparent;
              
              op_init->sibparent = op_block_statements;
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
              
              SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, var_decl->op_var_decl);
              
              // Check mem id
              int32_t typed_var_index;
              if (SPVM_TYPE_is_object_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                typed_var_index = SPVM_CHECK_get_typed_var_index(compiler, runtime_vars_object, var_decl);
              }
              else if (SPVM_TYPE_is_ref_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                typed_var_index = SPVM_CHECK_get_typed_var_index(compiler, runtime_vars_ref, var_decl);
              }
              else if (SPVM_TYPE_is_mulnum_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                SPVM_FIELD* first_field = SPVM_LIST_get(type->basic_type->fields, 0);
                assert(first_field);
                
                SPVM_TYPE* field_type = first_field->type;
                
                switch (field_type->basic_type->id) {
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                    typed_var_index = SPVM_CHECK_get_typed_var_index(compiler, runtime_vars_byte, var_decl);
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                    typed_var_index = SPVM_CHECK_get_typed_var_index(compiler, runtime_vars_short, var_decl);
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                    typed_var_index = SPVM_CHECK_get_typed_var_index(compiler, runtime_vars_int, var_decl);
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                    typed_var_index = SPVM_CHECK_get_typed_var_index(compiler, runtime_vars_long, var_decl);
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                    typed_var_index = SPVM_CHECK_get_typed_var_index(compiler, runtime_vars_float, var_decl);
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                    typed_var_index = SPVM_CHECK_get_typed_var_index(compiler, runtime_vars_double, var_decl);
                    break;
                  }
                  default:
                    assert(0);
                }
              }
              else if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                SPVM_TYPE* numeric_type = SPVM_CHECK_get_type(compiler, var_decl->op_var_decl);
                switch(numeric_type->basic_type->id) {
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                    typed_var_index = SPVM_CHECK_get_typed_var_index(compiler, runtime_vars_byte, var_decl);
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                    typed_var_index = SPVM_CHECK_get_typed_var_index(compiler, runtime_vars_short, var_decl);
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                    typed_var_index = SPVM_CHECK_get_typed_var_index(compiler, runtime_vars_int, var_decl);
                    if (strcmp(var_decl->var->name, "$.condition_flag") == 0) {
                      assert(typed_var_index == 0);
                    }
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                    typed_var_index = SPVM_CHECK_get_typed_var_index(compiler, runtime_vars_long, var_decl);
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                    typed_var_index = SPVM_CHECK_get_typed_var_index(compiler, runtime_vars_float, var_decl);
                    break;
                  }
                  case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                    typed_var_index = SPVM_CHECK_get_typed_var_index(compiler, runtime_vars_double, var_decl);
                    break;
                  }
                  default:
                    assert(0);
                }
              }
              else if (SPVM_TYPE_is_void_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
                typed_var_index = -1;
              }
              else {
                assert(0);
              }
              var_decl->typed_var_index = typed_var_index;
              
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
  
  method->byte_vars_width = runtime_vars_byte->length;
  method->short_vars_width = runtime_vars_short->length;
  method->int_vars_width = runtime_vars_int->length;
  method->long_vars_width = runtime_vars_long->length;
  method->float_vars_width = runtime_vars_float->length;
  method->double_vars_width = runtime_vars_double->length;
  method->object_vars_width = runtime_vars_object->length;
  method->ref_vars_width = runtime_vars_ref->length;
  
  SPVM_LIST_free(tmp_var_decl_stack);
  
  SPVM_LIST_free(runtime_vars_byte);
  SPVM_LIST_free(runtime_vars_short);
  SPVM_LIST_free(runtime_vars_int);
  SPVM_LIST_free(runtime_vars_long);
  SPVM_LIST_free(runtime_vars_float);
  SPVM_LIST_free(runtime_vars_double);
  SPVM_LIST_free(runtime_vars_object);
  SPVM_LIST_free(runtime_vars_ref);
}

SPVM_METHOD* SPVM_CHECK_search_method(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type, const char* method_name) {
  SPVM_METHOD* found_method = NULL;
  
  SPVM_BASIC_TYPE* parent_basic_type = basic_type;
  while (1) {
    found_method = SPVM_HASH_get(
      parent_basic_type->method_symtable,
      method_name,
      strlen(method_name)
    );
    if (found_method) {
      break;
    }
    parent_basic_type = parent_basic_type->parent;
    
    if (!parent_basic_type) {
      break;
    }
  }
  
  return found_method;
}

SPVM_FIELD* SPVM_CHECK_search_unmerged_field(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type, const char* field_name) {
  SPVM_FIELD* found_field = NULL;
  
  if (basic_type) {
    SPVM_BASIC_TYPE* parent_basic_type = basic_type;
    while (1) {
      found_field = SPVM_HASH_get(
        parent_basic_type->unmerged_field_symtable,
        field_name,
        strlen(field_name)
      );
      if (found_field) {
        break;
      }
      parent_basic_type = parent_basic_type->parent;
      
      if (!parent_basic_type) {
        break;
      }
    }
  }
  
  return found_field;
}

int32_t SPVM_CHECK_can_access(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* src_basic_type, SPVM_BASIC_TYPE* dist_basic_type, int32_t dist_access_controll_flag, int32_t is_parent_field) {
  
  int32_t can_access = 0;
  
  if (src_basic_type->is_generated_by_anon_method) {
    src_basic_type = src_basic_type->outmost;
  }
  
  if (dist_access_controll_flag == SPVM_ATTRIBUTE_C_ID_PRIVATE) {
    if (is_parent_field) {
      can_access = 0;
    }
    else {
      if (strcmp(src_basic_type->name, dist_basic_type->name) == 0) {
        can_access = 1;
      }
      else {
        can_access = 0;
      }
    }
  }
  else if (dist_access_controll_flag == SPVM_ATTRIBUTE_C_ID_PROTECTED) {
    if (strcmp(src_basic_type->name, dist_basic_type->name) == 0) {
      can_access = 1;
    }
    else {
      if (SPVM_BASIC_TYPE_is_super_class(compiler, dist_basic_type->id, src_basic_type->id)) {
        can_access = 1;
      }
      else {
        can_access = 0;
      }
    }
  }
  else if (dist_access_controll_flag == SPVM_ATTRIBUTE_C_ID_PUBLIC) {
    can_access = 1;
  }
  else {
    assert(0);
  }
  
  return can_access;
}

int SPVM_CHECK_method_name_compare_cb(const void* method1_ptr, const void* method2_ptr) {
  
  SPVM_METHOD* method1 = *(SPVM_METHOD**)method1_ptr;
  SPVM_METHOD* method2 = *(SPVM_METHOD**)method2_ptr;
  
  const char* method1_name = method1->name;
  const char* method2_name = method2->name;
  
  return strcmp(method1_name, method2_name);
}

void SPVM_CHECK_perform_numeric_to_string_conversion(SPVM_COMPILER* compiler, SPVM_OP* op_operand) {
  
  SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, op_operand);
  
  SPVM_TYPE* dist_type;
  if (SPVM_TYPE_is_numeric_type(compiler, type->basic_type->id, type->dimension, type->flag)) {
    SPVM_OP* op_dist_type = SPVM_OP_new_op_string_type(compiler, op_operand->file, op_operand->line);
    dist_type = op_dist_type->uv.type;
  }
  else {
    return;
  }
  
  SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_operand);
  
  SPVM_OP* op_type_cast = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, op_operand->file, op_operand->line);
  SPVM_OP* op_dist_type = SPVM_CHECK_new_op_type_shared(compiler, dist_type, op_operand->file, op_operand->line);
  SPVM_OP_build_type_cast(compiler, op_type_cast, op_dist_type, op_operand, NULL);
  
  SPVM_OP_replace_op(compiler, op_stab, op_type_cast);
}

void SPVM_CHECK_perform_integer_promotional_conversion(SPVM_COMPILER* compiler, SPVM_OP* op_operand) {
  
  SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, op_operand);
  
  SPVM_TYPE* dist_type;
  if (type->dimension == 0 && type->basic_type->id <= SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
    SPVM_OP* op_dist_type = SPVM_OP_new_op_int_type(compiler, op_operand->file, op_operand->line);
    dist_type = op_dist_type->uv.type;
  }
  else {
    return;
  }
  
  if (!(type->basic_type->id == dist_type->basic_type->id && type->dimension == dist_type->dimension)) {
    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_operand);
    
    SPVM_OP* op_type_cast = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, op_operand->file, op_operand->line);
    SPVM_OP* op_dist_type = SPVM_CHECK_new_op_type_shared(compiler, dist_type, op_operand->file, op_operand->line);
    SPVM_OP_build_type_cast(compiler, op_type_cast, op_dist_type, op_operand, NULL);
    
    SPVM_TYPE* type = SPVM_CHECK_get_type(compiler, op_type_cast);
    
    SPVM_OP_replace_op(compiler, op_stab, op_type_cast);
  }
}

void SPVM_CHECK_perform_binary_numeric_conversion(SPVM_COMPILER* compiler, SPVM_OP* op_left_operand, SPVM_OP* op_right_operand) {
  
  SPVM_TYPE* left_operand_type = SPVM_CHECK_get_type(compiler, op_left_operand);
  SPVM_TYPE* right_operand_type = SPVM_CHECK_get_type(compiler, op_right_operand);
  
  SPVM_TYPE* dist_type;
  if ((left_operand_type->dimension == 0 && left_operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) || (right_operand_type->dimension == 0 && right_operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE)) {
    SPVM_OP* op_dist_type = SPVM_OP_new_op_double_type(compiler, op_left_operand->file, op_left_operand->line);
    dist_type = op_dist_type->uv.type;
  }
  else if ((left_operand_type->dimension == 0 && left_operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) || (right_operand_type->dimension == 0 && right_operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT)) {
    SPVM_OP* op_dist_type = SPVM_OP_new_op_float_type(compiler, op_left_operand->file, op_left_operand->line);
    dist_type = op_dist_type->uv.type;
  }
  else if ((left_operand_type->dimension == 0 && left_operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) || (right_operand_type->dimension == 0 && right_operand_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG)) {
    SPVM_OP* op_dist_type = SPVM_OP_new_op_long_type(compiler, op_left_operand->file, op_left_operand->line);
    dist_type = op_dist_type->uv.type;
  }
  else {
    SPVM_OP* op_dist_type = SPVM_OP_new_op_int_type(compiler, op_left_operand->file, op_left_operand->line);
    dist_type = op_dist_type->uv.type;
  }
  
  if (!(left_operand_type->basic_type->id == dist_type->basic_type->id && left_operand_type->dimension == dist_type->dimension)) {
    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_left_operand);
    
    SPVM_OP* op_type_cast = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, op_left_operand->file, op_left_operand->line);
    SPVM_OP* op_dist_type = SPVM_CHECK_new_op_type_shared(compiler, dist_type, op_left_operand->file, op_left_operand->line);
    SPVM_OP_build_type_cast(compiler, op_type_cast, op_dist_type, op_left_operand, NULL);
    
    SPVM_OP_replace_op(compiler, op_stab, op_type_cast);
  }
  
  if (!(right_operand_type->basic_type->id == dist_type->basic_type->id && right_operand_type->dimension == dist_type->dimension)) {
    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_right_operand);
    
    SPVM_OP* op_type_cast = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, op_right_operand->file, op_right_operand->line);
    SPVM_OP* op_dist_type = SPVM_CHECK_new_op_type_shared(compiler, dist_type, op_right_operand->file, op_right_operand->line);
    SPVM_OP_build_type_cast(compiler, op_type_cast, op_dist_type, op_right_operand, NULL);
    SPVM_OP_replace_op(compiler, op_stab, op_type_cast);
  }
}

int32_t SPVM_CHECK_check_allow_narrowing_conversion(SPVM_COMPILER* compiler, SPVM_TYPE* dist_type, SPVM_OP* op_src) {
  
  int32_t allow_narrowing_conversion = 0;
  if (op_src->allow_narrowing_conversion) {
    allow_narrowing_conversion = 1;
  }
  else {
    SPVM_TYPE* src_type = SPVM_CHECK_get_type(compiler, op_src);
    
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
    
    // Dist type is numeric type or numeric array type
    if (SPVM_TYPE_is_numeric_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag) || SPVM_TYPE_is_numeric_array_type(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag)) {
      // Soruce type is numeric type
      if (SPVM_TYPE_is_numeric_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
        // Dist type is same as source type
        if (src_type_basic_type_id == dist_type_basic_type_id) {
          
        }
        // Dist type is more wide than source type
        else if (dist_type_basic_type_id > src_type_basic_type_id) {
          
        }
        // Dist type is narrow than source type
        else if (dist_type_basic_type_id < src_type_basic_type_id) {
          if (src_constant) {
            assert(src_type_dimension == 0);
            if (src_type_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT || src_type_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
              int64_t src_constant_value;
              if (src_type_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                src_constant_value = src_constant->value.ival;
              }
              else if (src_type_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_LONG) {
                src_constant_value = src_constant->value.lval;
              }
              else {
                assert(0);
              }
              
              if (dist_type_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE) {
                if (src_constant_value >= INT8_MIN && src_constant_value <= INT8_MAX) {
                  allow_narrowing_conversion = 1;
                }
                else {
                  allow_narrowing_conversion = 0;
                }
              }
              else if (dist_type_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT) {
                if (src_constant_value >= INT16_MIN && src_constant_value <= INT16_MAX) {
                  allow_narrowing_conversion = 1;
                }
                else {
                  allow_narrowing_conversion = 0;
                }
              }
              else if (dist_type_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
                if (src_constant_value >= INT32_MIN && src_constant_value <= INT32_MAX) {
                  allow_narrowing_conversion = 1;
                }
                else {
                  allow_narrowing_conversion = 0;
                }
              }
              else {
                assert(0);
              }
            }
            else if (src_type_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
              double src_constant_value;
              if (src_type_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE) {
                src_constant_value = src_constant->value.dval;
              }
              else {
                assert(0);
              }
              
              if (dist_type_basic_type_id == SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT) {
                allow_narrowing_conversion = 1;
              }
              else {
                allow_narrowing_conversion = 0;
              }
            }
            else {
              allow_narrowing_conversion = 0;
            }
          }
        }
      }
    }
  }
  
  return allow_narrowing_conversion;
}

SPVM_OP* SPVM_CHECK_check_assign(SPVM_COMPILER* compiler, SPVM_TYPE* dist_type, SPVM_OP* op_src, const char* place, const char* file, int32_t line) {
  SPVM_TYPE* src_type = SPVM_CHECK_get_type(compiler, op_src);
  
  int32_t dist_type_basic_type_id = dist_type->basic_type->id;
  int32_t dist_type_dimension = dist_type->dimension;
  int32_t dist_type_flag = dist_type->flag;
  
  int32_t src_type_basic_type_id = src_type->basic_type->id;
  int32_t src_type_dimension = src_type->dimension;
  int32_t src_type_flag = src_type->flag;
  
  const char* src_type_name = SPVM_TYPE_new_type_name(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag);
  const char* dist_type_name = SPVM_TYPE_new_type_name(compiler, dist_type_basic_type_id, dist_type_dimension, dist_type_flag);
  
  if (SPVM_TYPE_is_void_type(compiler, src_type_basic_type_id, src_type_dimension, src_type_flag)) {
    SPVM_COMPILER_error(compiler, "The void type cannnot be assigned in %s.\n  at %s line %d", place, file, line);
    return NULL;
  }
  
  int32_t need_data_conversion = 0;
  int32_t allow_narrowing_conversion = SPVM_CHECK_check_allow_narrowing_conversion(compiler, dist_type, op_src);
  int32_t interface_match = 0;
  char error_reason[1024] = {0};
  int32_t satisfy_assignment_requirement = SPVM_TYPE_satisfy_assignment_requirement(
    compiler,
    dist_type_basic_type_id, dist_type_dimension, dist_type_flag,
    src_type_basic_type_id, src_type_dimension, src_type_flag,
    &need_data_conversion, allow_narrowing_conversion, interface_match,
    error_reason
  );
    
  if (!satisfy_assignment_requirement) {
    if (strlen(error_reason)) {
      SPVM_COMPILER_error(compiler, error_reason);
    }
    
    SPVM_COMPILER_error(compiler, "%s type cannot be assigned to %s type in %s.\n  at %s line %d", src_type_name, dist_type_name, place, file, line);
    return NULL;
  }
  
  if (need_data_conversion) {
    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_src);
    
    SPVM_OP* op_type_cast = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, file, line);
    SPVM_OP* op_dist_type = SPVM_CHECK_new_op_type_shared(compiler, dist_type, file, line);
    SPVM_OP_build_type_cast(compiler, op_type_cast, op_dist_type, op_src, NULL);
    
    SPVM_OP_replace_op(compiler, op_stab, op_type_cast);
    return op_type_cast;
  }
  
  return op_src;
}

int32_t SPVM_CHECK_get_typed_var_index(SPVM_COMPILER* compiler, SPVM_LIST* runtime_vars, SPVM_VAR_DECL* var_decl) {
  
  int32_t found_typed_var_index = -1;
  
  SPVM_TYPE* var_decl_type = var_decl->type;

  int32_t var_width = SPVM_TYPE_get_width(compiler, var_decl_type->basic_type->id, var_decl_type->dimension, var_decl_type->flag);
  
  // Search free memory
  int32_t found = 0;
  for (int32_t typed_var_index = 0; typed_var_index < runtime_vars->length; typed_var_index++) {
    if (typed_var_index + var_width <= runtime_vars->length) {
      int32_t is_used = 0;
      for (int32_t i = 0; i < var_width; i++) {
        int32_t var_decl_id = (intptr_t)SPVM_LIST_get(runtime_vars, typed_var_index + i);
        if (var_decl_id >= 0) {
          is_used = 1;
          break;
        }
      }
      if (!is_used) {
        found = 1;
        found_typed_var_index = typed_var_index;
        for (int32_t i = 0; i < var_width; i++) {
          runtime_vars->values[typed_var_index + i] = (void*)(intptr_t)var_decl->index;
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
    found_typed_var_index = runtime_vars->length;
    for (int32_t i = 0; i < var_width; i++) {
      SPVM_LIST_push(runtime_vars, (void*)(intptr_t)var_decl->index);
    }
  }
  
  return found_typed_var_index;
}

SPVM_OP* SPVM_CHECK_new_op_var_tmp(SPVM_COMPILER* compiler, SPVM_TYPE* type, SPVM_METHOD* method, const char* file, int32_t line) {
  
  // Temparary variable name
  char* name = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->current_each_compile_allocator, strlen("$.tmp_in_method2147483647") + 1);
  sprintf(name, "$.tmp_in_method%d", method->tmp_vars_length);
  method->tmp_vars_length++;
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NAME, file, line);
  op_name->uv.name = name;
  SPVM_OP* op_var_tmp = SPVM_OP_build_var(compiler, op_name);
  SPVM_OP* op_var_tmp_decl = SPVM_OP_new_op_var_decl(compiler, file, line);
  assert(type);
  SPVM_OP* op_type = SPVM_CHECK_new_op_type_shared(compiler, type, file, line);
  
  SPVM_OP_build_var_decl(compiler, op_var_tmp_decl, op_var_tmp, op_type, NULL);
  
  op_var_tmp->uv.var->is_initialized = 1;
  
  op_var_tmp->uv.var->var_decl->index = method->var_decls->length;
  SPVM_LIST_push(method->op_method->uv.method->var_decls, op_var_tmp->uv.var->var_decl);
  
  return op_var_tmp;
}

// Don't use this method in spvm_op.c because types must not be shared in builiding AST.
SPVM_OP* SPVM_CHECK_new_op_type_shared(SPVM_COMPILER* compiler, SPVM_TYPE* type, const char* file, int32_t line) {
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, file, line);
  op_type->uv.type = type;
  
  SPVM_LIST_push(compiler->op_types, op_type);
  
  return op_type;
}

// Don't use this method in spvm_op.c because types must not be shared in builiding AST.
SPVM_TYPE* SPVM_CHECK_get_type(SPVM_COMPILER* compiler, SPVM_OP* op) {
  
  SPVM_TYPE*  type = NULL;
  
  switch (op->id) {
    case SPVM_OP_C_ID_TRUE:
    case SPVM_OP_C_ID_FALSE:
    {
      type = SPVM_TYPE_new_bool_object_type(compiler);
      break;
    }
    case SPVM_OP_C_ID_RETURN:
    case SPVM_OP_C_ID_LOOP_INCREMENT:
    case SPVM_OP_C_ID_CONDITION:
    case SPVM_OP_C_ID_CONDITION_NOT:
    case SPVM_OP_C_ID_SWITCH:
    case SPVM_OP_C_ID_DEFAULT:
    case SPVM_OP_C_ID_CASE:
    case SPVM_OP_C_ID_LAST:
    case SPVM_OP_C_ID_NEXT:
    case SPVM_OP_C_ID_BREAK:
    case SPVM_OP_C_ID_DIE:
    case SPVM_OP_C_ID_WARN:
    case SPVM_OP_C_ID_PRINT:
    case SPVM_OP_C_ID_SAY:
    case SPVM_OP_C_ID_MAKE_READ_ONLY:
    {
      // Dummy int variable
      type = SPVM_TYPE_new_int_type(compiler);
      break;
    }
    case SPVM_OP_C_ID_NUMERIC_COMPARISON_EQ:
    case SPVM_OP_C_ID_NUMERIC_COMPARISON_NE:
    case SPVM_OP_C_ID_NUMERIC_COMPARISON_GT:
    case SPVM_OP_C_ID_NUMERIC_COMPARISON_GE:
    case SPVM_OP_C_ID_NUMERIC_COMPARISON_LT:
    case SPVM_OP_C_ID_NUMERIC_COMPARISON_LE:
    case SPVM_OP_C_ID_NUMERIC_COMPARISON_CMP:
    case SPVM_OP_C_ID_BOOL:
    case SPVM_OP_C_ID_STRING_COMPARISON_EQ:
    case SPVM_OP_C_ID_STRING_COMPARISON_NE:
    case SPVM_OP_C_ID_STRING_COMPARISON_GT:
    case SPVM_OP_C_ID_STRING_COMPARISON_GE:
    case SPVM_OP_C_ID_STRING_COMPARISON_LT:
    case SPVM_OP_C_ID_STRING_COMPARISON_LE:
    case SPVM_OP_C_ID_STRING_COMPARISON_CMP:
    case SPVM_OP_C_ID_ISA:
    case SPVM_OP_C_ID_ISA_ERROR:
    case SPVM_OP_C_ID_IS_TYPE:
    case SPVM_OP_C_ID_IS_ERROR:
    case SPVM_OP_C_ID_IF:
    case SPVM_OP_C_ID_ISWEAK_FIELD:
    case SPVM_OP_C_ID_IS_READ_ONLY:
    case SPVM_OP_C_ID_CAN:
    case SPVM_OP_C_ID_BASIC_TYPE_ID:
    case SPVM_OP_C_ID_EVAL_ERROR_ID:
    case SPVM_OP_C_ID_ARGS_WIDTH:
    {
      type = SPVM_TYPE_new_int_type(compiler);
      break;
    }
    case SPVM_OP_C_ID_ARRAY_LENGTH:
    case SPVM_OP_C_ID_STRING_LENGTH:
    {
      type = SPVM_TYPE_new_int_type(compiler);
      break;
    }
    case SPVM_OP_C_ID_ELEMENT_ACCESS: {
      SPVM_TYPE* array_type = SPVM_CHECK_get_type(compiler, op->first);
      SPVM_BASIC_TYPE* basic_type = SPVM_HASH_get(compiler->basic_type_symtable, array_type->basic_type->name, strlen(array_type->basic_type->name));
      if (SPVM_TYPE_is_string_type(compiler, basic_type->id, array_type->dimension, 0)) {
        type = SPVM_TYPE_new_byte_type(compiler);
      }
      else if (SPVM_TYPE_is_any_object_array_type(compiler, basic_type->id, array_type->dimension, 0)) {
        type = SPVM_TYPE_new_any_object_type(compiler);
      }
      else {
        type = SPVM_TYPE_new(compiler, basic_type->id, array_type->dimension - 1, 0);
      }
      
      break;
    }
    case SPVM_OP_C_ID_ADD:
    case SPVM_OP_C_ID_SUBTRACT:
    case SPVM_OP_C_ID_MULTIPLY:
    case SPVM_OP_C_ID_DIVIDE:
    case SPVM_OP_C_ID_DIVIDE_UNSIGNED_INT:
    case SPVM_OP_C_ID_DIVIDE_UNSIGNED_LONG:
    case SPVM_OP_C_ID_MODULO:
    case SPVM_OP_C_ID_MODULO_UNSIGNED_INT:
    case SPVM_OP_C_ID_MODULO_UNSIGNED_LONG:
    case SPVM_OP_C_ID_INC:
    case SPVM_OP_C_ID_PRE_INC:
    case SPVM_OP_C_ID_POST_INC:
    case SPVM_OP_C_ID_DEC:
    case SPVM_OP_C_ID_PRE_DEC:
    case SPVM_OP_C_ID_POST_DEC:
    case SPVM_OP_C_ID_LEFT_SHIFT:
    case SPVM_OP_C_ID_RIGHT_ARITHMETIC_SHIFT:
    case SPVM_OP_C_ID_RIGHT_LOGICAL_SHIFT:
    case SPVM_OP_C_ID_BIT_XOR:
    case SPVM_OP_C_ID_BIT_OR:
    case SPVM_OP_C_ID_BIT_AND:
    case SPVM_OP_C_ID_BIT_NOT:
    case SPVM_OP_C_ID_PLUS:
    case SPVM_OP_C_ID_MINUS:
    case SPVM_OP_C_ID_ARRAY_INIT:
    case SPVM_OP_C_ID_COPY:
    {
      type = SPVM_CHECK_get_type(compiler, op->first);
      break;
    }
    case SPVM_OP_C_ID_NEW: {
      if (op->first->id == SPVM_OP_C_ID_TYPE) {
        type = op->first->uv.type;
      }
      else if (op->first->id == SPVM_OP_C_ID_VAR) {
        SPVM_OP* op_var_element = op->first;
        SPVM_TYPE* element_type = SPVM_CHECK_get_type(compiler, op_var_element);
        type = SPVM_TYPE_new(compiler, element_type->basic_type->id, element_type->dimension + 1, element_type->flag);
      }
      else {
        assert(0);
      }
      break;
    }
    case SPVM_OP_C_ID_LIST:
    case SPVM_OP_C_ID_SEQUENCE:
      type = SPVM_CHECK_get_type(compiler, op->last);
      break;
    case SPVM_OP_C_ID_ASSIGN: {
      type = SPVM_CHECK_get_type(compiler, op->last);
      break;
    }
    case SPVM_OP_C_ID_TYPE_CAST: {
      SPVM_OP* op_type = op->last;
      type = SPVM_CHECK_get_type(compiler, op_type);
      break;
    }
    case SPVM_OP_C_ID_TYPE: {
      if (op->uv.type) {
        type = op->uv.type;
      }
      break;
    }
    case SPVM_OP_C_ID_SWITCH_CONDITION : {
      type = SPVM_CHECK_get_type(compiler, op->first);
      break;
    }
    case SPVM_OP_C_ID_UNDEF : {
      type = SPVM_TYPE_new_undef_type(compiler);
      break;
    }
    case SPVM_OP_C_ID_CONSTANT: {
      SPVM_CONSTANT* constant = op->uv.constant;
      type = constant->type;
      break;
    }
    case SPVM_OP_C_ID_VAR: {
      SPVM_VAR* var = op->uv.var;
      type = var->var_decl->type;
      break;
    }
    case SPVM_OP_C_ID_CLASS_VAR_ACCESS: {
      SPVM_CLASS_VAR* class_var = op->uv.class_var_access->class_var;
      if (class_var->type) {
        type = class_var->type;
      }
      break;
    }
    case SPVM_OP_C_ID_CLASS_VAR: {
      SPVM_CLASS_VAR* class_var = op->uv.class_var;
      if (class_var->type) {
        type = class_var->type;
      }
      break;
    }
    case SPVM_OP_C_ID_STRING_CONCAT:
    case SPVM_OP_C_ID_TYPE_NAME:
    case SPVM_OP_C_ID_COMPILE_TYPE_NAME:
    case SPVM_OP_C_ID_DUMP:
    case SPVM_OP_C_ID_EXCEPTION_VAR:
    case SPVM_OP_C_ID_NEW_STRING_LEN:
    {
      type = SPVM_TYPE_new_string_type(compiler);
      break;
    }
    case SPVM_OP_C_ID_VAR_DECL: {
      
      SPVM_VAR_DECL* var_decl = op->uv.var_decl;
      type = var_decl->type;
      break;
    }
    case SPVM_OP_C_ID_CALL_METHOD: {
      SPVM_CALL_METHOD*call_method = op->uv.call_method;
      const char*call_method_method_name =call_method->method->name;
      SPVM_METHOD* method = SPVM_HASH_get(call_method->method->current_basic_type->method_symtable,call_method_method_name, strlen(call_method_method_name));
      type = method->return_type;
      break;
    }
    case SPVM_OP_C_ID_FIELD_ACCESS: {
      if (op->flag & (SPVM_OP_C_FLAG_FIELD_ACCESS_WEAKEN|SPVM_OP_C_FLAG_FIELD_ACCESS_UNWEAKEN|SPVM_OP_C_FLAG_FIELD_ACCESS_ISWEAK)) {
        type = SPVM_TYPE_new_int_type(compiler);
      }
      else {
        SPVM_FIELD_ACCESS* field_access = op->uv.field_access;
        SPVM_FIELD* field = field_access->field;
        type = field->type;
      }
      break;
    }
    case SPVM_OP_C_ID_ARRAY_FIELD_ACCESS: {
      SPVM_ARRAY_FIELD_ACCESS* array_field_access = op->uv.array_field_access;
      SPVM_FIELD* field = array_field_access->field;
      type = field->type;
      break;
    }
    case SPVM_OP_C_ID_FIELD: {
      SPVM_FIELD* field = op->uv.field;
      type = field->type;
      break;
    }
    case SPVM_OP_C_ID_REFERENCE: {
      SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op->first);
      assert(operand_type->dimension == 0);
      switch (operand_type->basic_type->id) {
        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
          type = SPVM_TYPE_new_byte_ref_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
          type = SPVM_TYPE_new_short_ref_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
          type = SPVM_TYPE_new_int_ref_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
          type = SPVM_TYPE_new_long_ref_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
          type = SPVM_TYPE_new_float_ref_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
          type = SPVM_TYPE_new_double_ref_type(compiler);
          break;
        }
        default: {
          assert(SPVM_TYPE_is_mulnum_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag));
          type = SPVM_TYPE_new(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag | SPVM_NATIVE_C_TYPE_FLAG_REF);
        }
      }
      break;
    }
    case SPVM_OP_C_ID_DEREFERENCE: {
      SPVM_TYPE* operand_type = SPVM_CHECK_get_type(compiler, op->first);
      assert(operand_type->dimension == 0);
      switch (operand_type->basic_type->id) {
        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
          type = SPVM_TYPE_new_byte_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
          type = SPVM_TYPE_new_short_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
          type = SPVM_TYPE_new_int_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
          type = SPVM_TYPE_new_long_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
          type = SPVM_TYPE_new_float_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
          type = SPVM_TYPE_new_double_type(compiler);
          break;
        }
        default: {
          assert(SPVM_TYPE_is_mulnum_ref_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag));
          type = SPVM_TYPE_new(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag & ~SPVM_NATIVE_C_TYPE_FLAG_REF);
        }
      }
      break;
    }
    default: {
      assert(0);
    }
  }
  
  return type;
}
