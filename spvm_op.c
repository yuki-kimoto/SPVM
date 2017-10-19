#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>
#include <ctype.h>

#include "spvm_compiler.h"
#include "spvm_dynamic_array.h"
#include "spvm_hash.h"
#include "spvm_yacc_util.h"
#include "spvm_op.h"
#include "spvm_sub.h"
#include "spvm_constant.h"
#include "spvm_field.h"
#include "spvm_my_var.h"
#include "spvm_var.h"
#include "spvm_enumeration_value.h"
#include "spvm_type.h"
#include "spvm_enumeration.h"
#include "spvm_package.h"
#include "spvm_call_field.h"
#include "spvm_call_sub.h"
#include "spvm_type.h"
#include "spvm_bytecode_builder.h"
#include "spvm_op_checker.h"
#include "spvm_switch_info.h"
#include "spvm_descriptor.h"
#include "spvm_compiler_allocator.h"
#include "spvm_limit.h"
#include "spvm_use.h"
#include "spvm_constant_pool.h"
#include "spvm_constant_pool_type.h"
#include "spvm_constant_pool_package.h"




const char* const SPVM_OP_C_CODE_NAMES[] = {
  "IF",
  "ELSIF",
  "ELSE",
  "FOR",
  "WHILE",
  "NULL",
  "LIST",
  "PUSHMARK",
  "GRAMMAR",
  "NAME",
  "PACKAGE",
  "MY",
  "FIELD",
  "SUB",
  "ENUM",
  "DESCRIPTOR",
  "ENUMERATION_VALUE",
  "BLOCK",
  "ENUM_BLOCK",
  "CLASS_BLOCK",
  "TYPE",
  "CONSTANT",
  "PRE_INC",
  "POST_INC",
  "PRE_DEC",
  "POST_DEC",
  "COMPLEMENT",
  "NEGATE",
  "PLUS",
  "EQ",
  "NE",
  "LT",
  "LE",
  "GT",
  "GE",
  "ADD",
  "SUBTRACT",
  "MULTIPLY",
  "DIVIDE",
  "BIT_AND",
  "BIT_OR",
  "BIT_XOR",
  "BIT_NOT",
  "REMAINDER",
  "LEFT_SHIFT",
  "RIGHT_SHIFT",
  "RIGHT_SHIFT_UNSIGNED",
  "AND",
  "OR",
  "NOT",
  "ARRAY_ELEM",
  "ASSIGN",
  "CALL_SUB",
  "CALL_FIELD",
  "USE",
  "RETURN",
  "LAST",
  "NEXT",
  "LOOP",
  "VAR",
  "CONVERT",
  "POP",
  "UNDEF",
  "ARRAY_LENGTH",
  "CONDITION",
  "CROAK",
  "SWITCH",
  "CASE",
  "DEFAULT",
  "SWITCH_CONDITION",
  "VOID",
  "EVAL",
  "BLOCK_END",
  "EXCEPTION_VAR",
  "ASSIGN_PROCESS",
  "NEW",
  "STAB",
  "BYTE",
  "SHORT",
  "INT",
  "LONG",
  "FLOAT",
  "DOUBLE",
  "STRING",
  "WEAKEN",
  "WEAKEN_FIELD",
  "SPECIAL_ASSIGN",
  "CONCAT_STRING",
  "SET",
  "GET",
};

SPVM_OP* SPVM_OP_build_setters(SPVM_COMPILER* compiler, SPVM_OP* op_set, SPVM_OP* op_names) {
  
  SPVM_OP_insert_child(compiler, op_set, op_set->last, op_names);
  
  return op_set;
}

SPVM_OP* SPVM_OP_build_getters(SPVM_COMPILER* compiler, SPVM_OP* op_get, SPVM_OP* op_names) {

  SPVM_OP_insert_child(compiler, op_get, op_get->last, op_names);
  
  return op_get;
}

SPVM_OP* SPVM_OP_clone_op_type(SPVM_COMPILER* compiler, SPVM_OP* op_type) {
  
  SPVM_OP* op_type_new = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_type->file, op_type->line);
  
  op_type_new->uv.type = op_type->uv.type;
  
  // Add types
  SPVM_DYNAMIC_ARRAY_push(compiler->op_types, op_type_new);
  
  return op_type_new;
}

SPVM_OP* SPVM_OP_new_op_name(SPVM_COMPILER* compiler, const char* name, const char* file, int32_t line) {
  
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NAME, file, line);
  
  op_name->uv.name = name;
  
  return op_name;
}

SPVM_OP* SPVM_OP_new_op_var(SPVM_COMPILER* compiler, SPVM_OP* op_name) {
  
  SPVM_OP* op_var = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_VAR, op_name->file, op_name->line);

  SPVM_VAR* var = SPVM_VAR_new(compiler);
  var->op_name = op_name;
  op_var->uv.var = var;
  
  return op_var;
}

SPVM_OP* SPVM_OP_build_sub_getter(SPVM_COMPILER* compiler, SPVM_OP* op_package, SPVM_OP* op_field) {
  
  /*
    sub get_x($self : Point) : int { return $self->{x} }
  */
  
  // Package name
  SPVM_PACKAGE* package = op_package->uv.package;
  
  // Package type
  SPVM_OP* op_type_package = SPVM_OP_clone_op_type(compiler, package->op_type);
  
  // Field name
  SPVM_FIELD* field = op_field->uv.field;
  const char* field_name = field->op_name->uv.name;
  
  // Field type
  SPVM_OP* op_type_field = SPVM_OP_clone_op_type(compiler, field->op_type);
  
  // File
  const char* file = op_field->file;
  
  // Line
  int32_t line = op_field->line;
  
  // sub
  SPVM_OP* op_sub = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_SUB, file, line);
  
  // Subroutine name
  int32_t sub_name_length = (int32_t)(4 + strlen(field_name));
  char* sub_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, sub_name_length);
  sprintf(sub_name, "get_%s", field_name);  
  SPVM_OP* op_name_sub = SPVM_OP_new_op_name(compiler, sub_name, file, line);

  // Variable Object argument
  SPVM_OP* op_name_object_arg = SPVM_OP_new_op_name(compiler, "$self", file, line);
  SPVM_OP* op_var_object_arg = SPVM_OP_new_op_var(compiler, op_name_object_arg);
  
  // Object type
  SPVM_OP* op_type_object_arg = op_type_package;
  
  // Argument
  SPVM_OP* op_var_arg = SPVM_OP_build_my_var(compiler, op_var_object_arg, op_type_object_arg);
  
  // Arguments
  SPVM_OP* op_list_args = SPVM_OP_new_op_list(compiler, file, line);
  SPVM_OP_insert_child(compiler, op_list_args, op_list_args->last, op_var_arg);
  
  // Return type
  SPVM_OP* op_type_return = op_type_field;
  
  // Variable Object invocant
  SPVM_OP* op_name_object_invocant = SPVM_OP_new_op_name(compiler, "$self", file, line);
  SPVM_OP* op_var_object_invocant = SPVM_OP_new_op_var(compiler, op_name_object_invocant);
  
  // Field name
  SPVM_OP* op_name_field = SPVM_OP_new_op_name(compiler, field_name, file, line);
  
  // Call field
  SPVM_OP* op_call_field = SPVM_OP_build_call_field(compiler, op_var_object_invocant, op_name_field);
  
  // Return
  SPVM_OP* op_return = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_RETURN, file, line);
  SPVM_OP_insert_child(compiler, op_return, op_return->last, op_call_field);

  // Statements
  SPVM_OP* op_list_statements = SPVM_OP_new_op_list(compiler, file, line);
  SPVM_OP_insert_child(compiler, op_list_statements, op_list_statements->last, op_return);
  
  // Block
  SPVM_OP* op_block = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, file, line);
  SPVM_OP_insert_child(compiler, op_block, op_block->last, op_list_statements);

  op_sub = SPVM_OP_build_sub(compiler, op_sub, op_name_sub, op_list_args, NULL, op_type_return, op_block);
  
  return op_sub;
}

SPVM_OP* SPVM_OP_build_sub_setter(SPVM_COMPILER* compiler, SPVM_OP* op_package, SPVM_OP* op_field) {
  
  /*
    sub set_x($self : Point, $value : int) : void { $self->{x} = $value }
  */
  
  // Package name
  SPVM_PACKAGE* package = op_package->uv.package;
  
  // Package type
  SPVM_OP* op_type_package = SPVM_OP_clone_op_type(compiler, package->op_type);
  
  // Field name
  SPVM_FIELD* field = op_field->uv.field;
  const char* field_name = field->op_name->uv.name;
  
  // Field type
  SPVM_OP* op_type_field = SPVM_OP_clone_op_type(compiler, field->op_type);
  
  // File
  const char* file = op_field->file;
  
  // Line
  int32_t line = op_field->line;
  
  // sub
  SPVM_OP* op_sub = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_SUB, file, line);
  
  // Subroutine name
  int32_t sub_name_length = (int32_t)(4 + strlen(field_name));
  char* sub_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, sub_name_length);
  sprintf(sub_name, "set_%s", field_name);  
  SPVM_OP* op_name_sub = SPVM_OP_new_op_name(compiler, sub_name, file, line);

  // Variable Object argument
  SPVM_OP* op_name_object_arg = SPVM_OP_new_op_name(compiler, "$self", file, line);
  SPVM_OP* op_var_object_arg = SPVM_OP_new_op_var(compiler, op_name_object_arg);
  
  // Object type
  SPVM_OP* op_type_object_arg = op_type_package;

  // Variable Value argument
  SPVM_OP* op_name_value_arg = SPVM_OP_new_op_name(compiler, "$value", file, line);
  SPVM_OP* op_var_value_arg = SPVM_OP_new_op_var(compiler, op_name_value_arg);
  
  // Value type
  SPVM_OP* op_type_value_arg = op_type_field;

  // Argument object
  SPVM_OP* op_var_arg_object = SPVM_OP_build_my_var(compiler, op_var_object_arg, op_type_object_arg);

  // Argument value
  SPVM_OP* op_var_arg_value = SPVM_OP_build_my_var(compiler, op_var_value_arg, op_type_value_arg);
  
  // Arguments
  SPVM_OP* op_list_args = SPVM_OP_new_op_list(compiler, file, line);
  SPVM_OP_insert_child(compiler, op_list_args, op_list_args->last, op_var_arg_object);
  SPVM_OP_insert_child(compiler, op_list_args, op_list_args->last, op_var_arg_value);
  
  // Return type
  SPVM_OP* op_type_return = SPVM_OP_build_void(compiler, op_field);
  
  // Assign
  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ASSIGN, file, line);
  
  // Variable Object invocant
  SPVM_OP* op_name_object_invocant = SPVM_OP_new_op_name(compiler, "$self", file, line);
  SPVM_OP* op_var_object_invocant = SPVM_OP_new_op_var(compiler, op_name_object_invocant);
  
  // Field name
  SPVM_OP* op_name_field = SPVM_OP_new_op_name(compiler, field_name, file, line);
  
  // Call field
  SPVM_OP* op_call_field = SPVM_OP_build_call_field(compiler, op_var_object_invocant, op_name_field);
  
  // Variable assinged Value
  SPVM_OP* op_name_assigned_value = SPVM_OP_new_op_name(compiler, "$value", file, line);
  SPVM_OP* op_var_assigned_value = SPVM_OP_new_op_var(compiler, op_name_assigned_value);
  
  SPVM_OP* op_build_assign = SPVM_OP_build_assign(compiler, op_assign, op_call_field, op_var_assigned_value);
  
  // Statements
  SPVM_OP* op_list_statements = SPVM_OP_new_op_list(compiler, file, line);
  SPVM_OP_insert_child(compiler, op_list_statements, op_list_statements->last, op_build_assign);
  
  // Block
  SPVM_OP* op_block = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, file, line);
  SPVM_OP_insert_child(compiler, op_block, op_block->last, op_list_statements);

  op_sub = SPVM_OP_build_sub(compiler, op_sub, op_name_sub, op_list_args, NULL, op_type_return, op_block);
  
  return op_sub;
}

SPVM_OP* SPVM_OP_build_default_new(SPVM_COMPILER* compiler, SPVM_OP* op_type) {
  
  // New op
  SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NEW, op_type->file, op_type->line);
  
  // New type
  SPVM_OP* op_type_new = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_type->file, op_type->line);
  op_type_new->uv.type = op_type->uv.type;
  SPVM_OP_insert_child(compiler, op_new, op_new->last, op_type_new);
  
  SPVM_DYNAMIC_ARRAY_push(compiler->op_types, op_type_new);
  
  // Return
  SPVM_OP* op_return = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_RETURN, op_type->file, op_type->line);
  SPVM_OP_insert_child(compiler, op_return, op_return->last, op_new);
  
  // Statements
  SPVM_OP* op_list_statements = SPVM_OP_new_op_list(compiler, op_type->file, op_type->line);
  SPVM_OP_insert_child(compiler, op_list_statements, op_list_statements->last, op_return);
  
  // Block
  SPVM_OP* op_block = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, op_type->file, op_type->line);
  SPVM_OP_insert_child(compiler, op_block, op_block->last, op_list_statements);
  
  // sub
  SPVM_OP* op_sub = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_SUB, op_type->file, op_type->line);
  op_sub->file = op_type->file;
  op_sub->line = op_type->line;
  
  // Type
  SPVM_OP* op_return_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_type->file, op_type->line);
  op_return_type->uv.type = op_type->uv.type;
  SPVM_DYNAMIC_ARRAY_push(compiler->op_types, op_return_type);
  
  // Build subroutine
  op_sub = SPVM_OP_build_sub(compiler, op_sub, op_type, NULL, NULL, op_return_type, op_block);
  
  return op_sub;
}

SPVM_OP* SPVM_OP_get_parent(SPVM_COMPILER* compiler, SPVM_OP* op_target) {
  (void)compiler;
  
  SPVM_OP* op_parent;
  SPVM_OP* op_cur = op_target;
  while (1) {
    if (op_cur->moresib) {
      op_cur = op_cur->sibparent;
    }
    else {
      op_parent = op_cur->sibparent;
      break;
    }
  }
  
  return op_parent;
}

void SPVM_OP_get_before(SPVM_COMPILER* compiler, SPVM_OP* op_target, SPVM_OP** op_before_ptr, _Bool* next_is_child_ptr) {

  // Get parent
  SPVM_OP* op_parent = SPVM_OP_get_parent(compiler, op_target);
  
  SPVM_OP* op_before;
  _Bool next_is_child = 0;
  if (op_parent->first == op_target) {
    op_before = op_parent;
    next_is_child = 1;
  }
  else {
    op_before = op_parent->first;
    while (1) {
      if (op_before->sibparent == op_target) {
        break;
      }
      else {
        op_before = op_before->sibparent;
      }
    }
  }
  
  *op_before_ptr = op_before;
  *next_is_child_ptr = next_is_child;
}

// Replace target op with replace op
void SPVM_OP_replace_op(SPVM_COMPILER* compiler, SPVM_OP* op_target, SPVM_OP* op_replace) {
  (void)compiler;

  // Get before op
  _Bool next_is_child;
  SPVM_OP* op_before;
  SPVM_OP_get_before(compiler, op_target, &op_before, &next_is_child);
  
  // Stab
  if (next_is_child) {
    // One child
    if (op_before->first == op_before->last) {
      op_before->first = op_replace;
      op_before->last = op_replace;
    }
    // More
    else {
      op_before->first = op_replace;
    }
  }
  else {
    op_before->sibparent = op_replace;
  }
  op_replace->moresib = op_target->moresib;
  op_replace->sibparent = op_target->sibparent;
}

// Cut op and insert stab into original position and return stab
SPVM_OP* SPVM_OP_cut_op(SPVM_COMPILER* compiler, SPVM_OP* op_target) {
  // Get before op
  _Bool next_is_child;
  SPVM_OP* op_before;
  SPVM_OP_get_before(compiler, op_target, &op_before, &next_is_child);
  
  // Stab
  SPVM_OP* op_stab = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_STAB, op_target->file, op_target->line);
  if (next_is_child) {
    
    // One child
    if (op_before->first == op_before->last) {
      op_before->first = op_stab;
      op_before->last = op_stab;
    }
    // More
    else {
      op_before->first = op_stab;
    }
  }
  else {
    op_before->sibparent = op_stab;
  }
  op_stab->moresib = op_target->moresib;
  op_stab->sibparent = op_target->sibparent;

  // Clear target
  op_target->moresib = 0;
  op_target->sibparent = NULL;
  
  return op_stab;
}

SPVM_OP* SPVM_OP_build_constant(SPVM_COMPILER* compiler, SPVM_OP* op_constant) {
  
  SPVM_CONSTANT* constant = op_constant->uv.constant;
  
  if (constant->type->code == SPVM_TYPE_C_CODE_STRING) {
    SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NEW, op_constant->file, op_constant->line);
    SPVM_OP_insert_child(compiler, op_new, op_new->last, op_constant);
    return op_new;
  }
  else {
    return op_constant;
  }
}

SPVM_OP* SPVM_OP_new_op_use_from_package_name(SPVM_COMPILER* compiler, const char* package_name, const char* file, int32_t line) {

  SPVM_OP* op_name_package = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NAME, file, line);
  op_name_package->uv.name = package_name;
  SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_USE, file, line);
  SPVM_USE* use = SPVM_USE_new(compiler);
  use->package_name = package_name;
  use->package_name_with_template_args = package_name;
  op_use->uv.use = use;
  SPVM_OP_insert_child(compiler, op_use, op_use->last, op_name_package);
  
  return op_use;
}

SPVM_OP* SPVM_OP_new_op_constant_byte(SPVM_COMPILER* compiler, int8_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.byte_value = value;
  constant->type = SPVM_TYPE_get_byte_type(compiler);
  
  op_constant->uv.constant = constant;

  SPVM_DYNAMIC_ARRAY_push(compiler->op_constants, op_constant);
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_short(SPVM_COMPILER* compiler, int16_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.short_value = value;
  constant->type = SPVM_TYPE_get_short_type(compiler);
  
  op_constant->uv.constant = constant;

  SPVM_DYNAMIC_ARRAY_push(compiler->op_constants, op_constant);

  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_int(SPVM_COMPILER* compiler, int32_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.int_value = value;
  constant->type = SPVM_TYPE_get_int_type(compiler);
  
  op_constant->uv.constant = constant;

  SPVM_DYNAMIC_ARRAY_push(compiler->op_constants, op_constant);

  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_long(SPVM_COMPILER* compiler, int64_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.long_value = value;
  constant->type = SPVM_TYPE_get_long_type(compiler);
  
  op_constant->uv.constant = constant;

  SPVM_DYNAMIC_ARRAY_push(compiler->op_constants, op_constant);

  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_float(SPVM_COMPILER* compiler, float value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.float_value = value;
  constant->type = SPVM_TYPE_get_float_type(compiler);
  
  op_constant->uv.constant = constant;

  SPVM_DYNAMIC_ARRAY_push(compiler->op_constants, op_constant);

  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_double(SPVM_COMPILER* compiler, double value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.double_value = value;
  constant->type = SPVM_TYPE_get_double_type(compiler);
  
  op_constant->uv.constant = constant;
  
  SPVM_DYNAMIC_ARRAY_push(compiler->op_constants, op_constant);
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_string(SPVM_COMPILER* compiler, char* string, const char* file, int32_t line) {

  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  constant->value.string_value = string;
  constant->type = SPVM_TYPE_get_string_type(compiler);
  op_constant->uv.constant = constant;
  
  SPVM_DYNAMIC_ARRAY_push(compiler->op_constants, op_constant);
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_byte_array_string(SPVM_COMPILER* compiler, char* string, const char* file, int32_t line) {

  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  constant->value.string_value = string;
  constant->type = SPVM_TYPE_get_string_type(compiler);
  op_constant->uv.constant = constant;
  
  SPVM_DYNAMIC_ARRAY_push(compiler->op_constants, op_constant);
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_var_from_op_my_var(SPVM_COMPILER* compiler, SPVM_OP* op_my_var) {
  (void)compiler;
  
  SPVM_VAR* var = SPVM_VAR_new(compiler);
  SPVM_OP* op_var = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_VAR, op_my_var->file, op_my_var->line);
  
  SPVM_MY_VAR* my_var = op_my_var->uv.my_var;
  
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NAME, op_my_var->file, op_my_var->line);
  op_name->uv.name = my_var->op_name->uv.name;
  var->op_name = op_name;
  var->op_my_var = op_my_var;
  op_var->uv.var = var;
  
  return op_var;
}

SPVM_OP* SPVM_OP_get_op_block_from_op_sub(SPVM_COMPILER* compiler, SPVM_OP* op_sub) {
  (void)compiler;
  
  SPVM_OP* op_block = op_sub->last;
  
  if (op_block->code == SPVM_OP_C_CODE_BLOCK) {
    return op_block;
  }
  else {
    return NULL;
  }
}

SPVM_OP* SPVM_OP_build_eval(SPVM_COMPILER* compiler, SPVM_OP* op_eval, SPVM_OP* op_eval_block) {
  
  SPVM_OP_insert_child(compiler, op_eval, op_eval->last, op_eval_block);
  
  // eval block
  op_eval_block->flag |= SPVM_OP_C_FLAG_BLOCK_EVAL;
  
  return op_eval;
}

SPVM_OP* SPVM_OP_build_switch_statement(SPVM_COMPILER* compiler, SPVM_OP* op_switch, SPVM_OP* op_term_condition, SPVM_OP* op_block) {
  
  SPVM_OP* op_switch_condition = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_SWITCH_CONDITION, op_term_condition->file, op_term_condition->line);
  SPVM_OP_insert_child(compiler, op_switch_condition, op_switch_condition->last, op_term_condition);
  
  SPVM_OP_insert_child(compiler, op_switch, op_switch->last, op_switch_condition);
  SPVM_OP_insert_child(compiler, op_switch, op_switch->last, op_block);
  
  op_block->flag |= SPVM_OP_C_FLAG_BLOCK_SWITCH;
  
  SPVM_SWITCH_INFO* switch_info = SPVM_SWITCH_INFO_new(compiler);
  op_switch->uv.switch_info = switch_info;
  
  op_switch_condition->uv.switch_info = switch_info;
  
  return op_switch;
}

SPVM_OP* SPVM_OP_build_case_statement(SPVM_COMPILER* compiler, SPVM_OP* op_case, SPVM_OP* op_term) {
  
  SPVM_OP_insert_child(compiler, op_case, op_case->last, op_term);
  
  op_term->flag = SPVM_OP_C_FLAG_CONSTANT_CASE;
  
  return op_case;
}

SPVM_OP* SPVM_OP_build_for_statement(SPVM_COMPILER* compiler, SPVM_OP* op_for, SPVM_OP* op_statement_init, SPVM_OP* op_term_condition, SPVM_OP* op_term_next_value, SPVM_OP* op_block) {
  
  // Outer block for initialize loop variable
  SPVM_OP* op_block_outer = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, op_for->file, op_for->line);
  SPVM_OP_insert_child(compiler, op_block_outer, op_block_outer->last, op_statement_init);
  
  // Loop
  SPVM_OP* op_loop = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_LOOP, op_for->file, op_for->line);
  
  // Condition
  SPVM_OP* op_condition = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONDITION, op_term_condition->file, op_term_condition->line);
  op_condition->flag |= SPVM_OP_C_FLAG_CONDITION_LOOP;
  SPVM_OP_insert_child(compiler, op_condition, op_condition->last, op_term_condition);
  
  // Set block flag
  op_block->flag |= SPVM_OP_C_FLAG_BLOCK_LOOP;
  
  // Push next value to the last of statements in block
  SPVM_OP* op_statements = op_block->first;
  if (op_term_next_value->code != SPVM_OP_C_CODE_NULL) {
    SPVM_OP_insert_child(compiler, op_statements, op_statements->last, op_term_next_value);
  }
  
  SPVM_OP_insert_child(compiler, op_loop, op_loop->last, op_condition);
  SPVM_OP_insert_child(compiler, op_loop, op_loop->last, op_block);
  
  SPVM_OP_insert_child(compiler, op_block_outer, op_block_outer->last, op_loop);
  
  return op_block_outer;
}

SPVM_OP* SPVM_OP_build_while_statement(SPVM_COMPILER* compiler, SPVM_OP* op_while, SPVM_OP* op_term, SPVM_OP* op_block) {
  
  // Loop
  SPVM_OP* op_loop = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_LOOP, op_while->file, op_while->line);
  
  // Condition
  SPVM_OP* op_condition = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONDITION, op_term->file, op_term->line);
  op_condition->flag |= SPVM_OP_C_FLAG_CONDITION_LOOP;
  SPVM_OP_insert_child(compiler, op_condition, op_condition->last, op_term);
  
  // Set block flag
  op_block->flag |= SPVM_OP_C_FLAG_BLOCK_LOOP;
  
  SPVM_OP_insert_child(compiler, op_loop, op_loop->last, op_condition);
  SPVM_OP_insert_child(compiler, op_loop, op_loop->last, op_block);
  
  // while is wraped with block to allow the following syntax
  // while (my $var = 3) { ... }
  SPVM_OP* op_block_outer = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, op_while->file, op_while->line);
  SPVM_OP_insert_child(compiler, op_block_outer, op_block_outer->last, op_loop);
  
  return op_block_outer;
}

SPVM_OP* SPVM_OP_build_if_statement(SPVM_COMPILER* compiler, SPVM_OP* op_if, SPVM_OP* op_term, SPVM_OP* op_block_true, SPVM_OP* op_block_false) {
  
  // ELSIF is same as IF
  if (op_if->code == SPVM_OP_C_CODE_ELSIF) {
    op_if->code = SPVM_OP_C_CODE_IF;
  }
  
  // Condition
  SPVM_OP* op_condition = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONDITION, op_term->file, op_term->line);
  op_condition->flag |= SPVM_OP_C_FLAG_CONDITION_IF;
  SPVM_OP_insert_child(compiler, op_condition, op_condition->last, op_term);

  // Create true block if needed
  if (op_block_true->code != SPVM_OP_C_CODE_BLOCK) {
    SPVM_OP* op_not_block = op_block_true;
    
    op_block_true = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, op_not_block->file, op_not_block->line);
    SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, op_not_block->file, op_not_block->line);
    SPVM_OP_insert_child(compiler, op_list, op_list->last, op_not_block);
    SPVM_OP_insert_child(compiler, op_block_true, op_block_true->last, op_list);
  }
  op_block_true->flag |= SPVM_OP_C_FLAG_BLOCK_IF_TRUE;
  
  // Create false block if needed
  if (op_block_false->code != SPVM_OP_C_CODE_BLOCK) {
    SPVM_OP* op_not_block = op_block_false;
    
    // Create block
    op_block_false = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, op_not_block->file, op_not_block->line);
    SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, op_not_block->file, op_not_block->line);
    SPVM_OP_insert_child(compiler, op_list, op_list->last, op_not_block);
    SPVM_OP_insert_child(compiler, op_block_false, op_block_false->last, op_list);
  }
  op_block_false->flag |= SPVM_OP_C_FLAG_BLOCK_IF_FALSE;
  
  SPVM_OP_insert_child(compiler, op_if, op_if->last, op_condition);
  SPVM_OP_insert_child(compiler, op_if, op_if->last, op_block_false);
  SPVM_OP_insert_child(compiler, op_if, op_if->last, op_block_true);
  
  return op_if;
}

SPVM_OP* SPVM_OP_build_array_length(SPVM_COMPILER* compiler, SPVM_OP* op_array_length, SPVM_OP* op_term) {
  
  SPVM_OP_insert_child(compiler, op_array_length, op_array_length->last, op_term);
  
  return op_array_length;
}

SPVM_OP* SPVM_OP_build_new_object(SPVM_COMPILER* compiler, SPVM_OP* op_new, SPVM_OP* op_type) {
  
  SPVM_OP_insert_child(compiler, op_new, op_new->last, op_type);
  
  return op_new;
}

SPVM_TYPE* SPVM_OP_get_type(SPVM_COMPILER* compiler, SPVM_OP* op) {
  
  SPVM_TYPE*  type = NULL;
  
  switch (op->code) {
    case SPVM_OP_C_CODE_CONCAT_STRING:
      type = SPVM_TYPE_get_string_type(compiler);
      break;
    case SPVM_OP_C_CODE_ASSIGN_PROCESS:
      type = SPVM_OP_get_type(compiler, op->first);
      break;
    case SPVM_OP_C_CODE_ARRAY_LENGTH:
      type = SPVM_TYPE_get_int_type(compiler);
      break;
    case SPVM_OP_C_CODE_ARRAY_ELEM: {
      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op->first);
      if (strcmp(first_type->name, "string") == 0) {
        type = SPVM_HASH_search(compiler->type_symtable, "byte", strlen("byte"));
      }
      else {
        type = SPVM_HASH_search(compiler->type_symtable, first_type->name, strlen(first_type->name) - 2);
      }
      break;
    }
    case SPVM_OP_C_CODE_ADD:
    case SPVM_OP_C_CODE_SUBTRACT:
    case SPVM_OP_C_CODE_MULTIPLY:
    case SPVM_OP_C_CODE_DIVIDE:
    case SPVM_OP_C_CODE_REMAINDER:
    case SPVM_OP_C_CODE_PRE_INC:
    case SPVM_OP_C_CODE_POST_INC:
    case SPVM_OP_C_CODE_PRE_DEC:
    case SPVM_OP_C_CODE_POST_DEC:
    case SPVM_OP_C_CODE_LEFT_SHIFT:
    case SPVM_OP_C_CODE_RIGHT_SHIFT:
    case SPVM_OP_C_CODE_RIGHT_SHIFT_UNSIGNED:
    case SPVM_OP_C_CODE_BIT_XOR:
    case SPVM_OP_C_CODE_BIT_OR:
    case SPVM_OP_C_CODE_BIT_AND:
    case SPVM_OP_C_CODE_PLUS:
    case SPVM_OP_C_CODE_NEGATE:
    case SPVM_OP_C_CODE_ASSIGN:
    case SPVM_OP_C_CODE_NEW:
    {
      type = SPVM_OP_get_type(compiler, op->first);
      break;
    }
    case SPVM_OP_C_CODE_RETURN: {
      if (op->first) {
        type = SPVM_OP_get_type(compiler, op->first);
      }
      break;
    }
    case SPVM_OP_C_CODE_CONVERT: {
      SPVM_OP* op_type = op->last;
      type = SPVM_OP_get_type(compiler, op_type);
      break;
    }
    case SPVM_OP_C_CODE_TYPE: {
      if (op->uv.type) {
        type = op->uv.type;
      }
      break;
    }
    case SPVM_OP_C_CODE_SWITCH_CONDITION : {
      type = SPVM_OP_get_type(compiler, op->first);
      break;
    }
    case SPVM_OP_C_CODE_UNDEF : {
      type = NULL;
      break;
    }
    case SPVM_OP_C_CODE_CONSTANT: {
      SPVM_CONSTANT* constant = op->uv.constant;
      type = constant->type;
      break;
    }
    case SPVM_OP_C_CODE_VAR: {
      SPVM_VAR* var = op->uv.var;
      if (var->op_my_var->uv.my_var->op_type) {
        type = var->op_my_var->uv.my_var->op_type->uv.type;
      }
      break;
    }
    case SPVM_OP_C_CODE_EXCEPTION_VAR: {
      type = SPVM_TYPE_get_string_type(compiler);
      break;
    }
    case SPVM_OP_C_CODE_MY: {
      
      SPVM_MY_VAR* my_var = op->uv.my_var;
      if ( my_var->op_type) {
        type = my_var->op_type->uv.type;
      }
      break;
    }
    case SPVM_OP_C_CODE_CALL_SUB: {
      SPVM_CALL_SUB* call_sub = op->uv.call_sub;
      const char* abs_name = call_sub->resolved_name;
      SPVM_OP* op_sub = SPVM_HASH_search(compiler->op_sub_symtable, abs_name, strlen(abs_name));
      SPVM_SUB* sub = op_sub->uv.sub;
      type = sub->op_return_type->uv.type;
      break;
    }
    case SPVM_OP_C_CODE_CALL_FIELD: {
      SPVM_CALL_FIELD* call_field = op->uv.call_field;
      SPVM_FIELD* field = call_field->field;
      type = field->op_type->uv.type;
      break;
    }
  }
  
  return type;
}

void SPVM_OP_resolve_call_sub(SPVM_COMPILER* compiler, SPVM_OP* op_package, SPVM_OP* op_name) {
  (void)op_package;
  
  SPVM_CALL_SUB* call_sub = op_name->uv.call_sub;
  
  const char* sub_abs_name = NULL;
  if (call_sub->code == SPVM_CALL_SUB_C_CODE_METHOD_CALL) {
    const char* package_name = call_sub->op_term->uv.var->op_my_var->uv.my_var->op_type->uv.type->name;
    const char* sub_name = call_sub->op_name->uv.name;
    sub_abs_name = SPVM_OP_create_abs_name(compiler, package_name, sub_name);
  }
  else if (call_sub->code == SPVM_CALL_SUB_C_CODE_SUB_CALL) {
    sub_abs_name = call_sub->op_name->uv.name;
  }
  else {
    assert(0);
  }
  
  call_sub->resolved_name = sub_abs_name;
  
  SPVM_OP* found_op_sub= SPVM_HASH_search(
    compiler->op_sub_symtable,
    sub_abs_name,
    strlen(sub_abs_name)
  );
  if (found_op_sub) {
    call_sub->sub = found_op_sub->uv.sub;
  }
}

void SPVM_OP_resolve_call_field(SPVM_COMPILER* compiler, SPVM_OP* op_call_field) {
  
  SPVM_OP* op_term = op_call_field->first;
  SPVM_OP* op_name = op_call_field->last;
  
  SPVM_TYPE* invoker_type = SPVM_OP_get_type(compiler, op_term);
  SPVM_PACKAGE* package = invoker_type->op_package->uv.package;
  const char* field_name = op_name->uv.name;
  
  SPVM_OP* found_op_field = SPVM_HASH_search(
    package->op_field_symtable,
    field_name,
    strlen(field_name)
  );
  if (found_op_field) {
    op_call_field->uv.call_field->field = found_op_field->uv.field;
  }
}

SPVM_OP* SPVM_OP_build_array_elem(SPVM_COMPILER* compiler, SPVM_OP* op_var, SPVM_OP* op_term) {
  
  SPVM_OP* op_array_elem = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ARRAY_ELEM, op_var->file, op_var->line);
  SPVM_OP_insert_child(compiler, op_array_elem, op_array_elem->last, op_var);
  SPVM_OP_insert_child(compiler, op_array_elem, op_array_elem->last, op_term);
  
  return op_array_elem;
}

SPVM_OP* SPVM_OP_build_call_field(SPVM_COMPILER* compiler, SPVM_OP* op_term, SPVM_OP* op_name_field) {
  SPVM_OP* op_field = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CALL_FIELD, op_term->file, op_term->line);
  SPVM_OP_insert_child(compiler, op_field, op_field->last, op_term);
  SPVM_OP_insert_child(compiler, op_field, op_field->last, op_name_field);
  
  SPVM_CALL_FIELD* call_field = SPVM_CALL_FIELD_new(compiler);
  
  if (strchr(op_name_field->uv.name, ':')) {
    SPVM_yyerror_format(compiler, "field name \"%s\" can't contain :: at %s line %d\n",
      op_name_field, op_name_field->file, op_name_field->line);
  }
  
  call_field->op_term = op_term;
  call_field->op_name = op_name_field;
  op_field->uv.call_field = call_field;
  
  return op_field;
}

SPVM_OP* SPVM_OP_build_weaken_field(SPVM_COMPILER* compiler, SPVM_OP* op_weaken, SPVM_OP* op_call_field) {
  
  SPVM_OP* op_weaken_field = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_WEAKEN_FIELD, op_weaken->file, op_weaken->line);
  SPVM_OP_insert_child(compiler, op_weaken_field, op_weaken_field->last, op_call_field);
  
  op_call_field->flag |= SPVM_OP_C_FLAG_CALL_FIELD_WEAKEN;
  
  return op_weaken_field;
}

SPVM_OP* SPVM_OP_build_convert_type(SPVM_COMPILER* compiler, SPVM_OP* op_type, SPVM_OP* op_term) {
  
  SPVM_OP* op_convert_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONVERT, op_type->file, op_type->line);
  SPVM_OP_insert_child(compiler, op_convert_type, op_convert_type->last, op_term);
  SPVM_OP_insert_child(compiler, op_convert_type, op_convert_type->last, op_type);
  
  op_convert_type->file = op_type->file;
  op_convert_type->line = op_type->line;
  
  return op_convert_type;
}

void SPVM_OP_build_constant_pool(SPVM_COMPILER* compiler) {
  SPVM_DYNAMIC_ARRAY* op_packages = compiler->op_packages;
  
  // Push constant to constant pool
  {
    int32_t i;
    for (i = 0; i < compiler->op_constants->length; i++) {
      SPVM_OP* op_constant = SPVM_DYNAMIC_ARRAY_fetch(compiler->op_constants, i);
      
      // Constant
      SPVM_CONSTANT* constant = op_constant->uv.constant;
      
      // Constant pool
      SPVM_CONSTANT_POOL* constant_pool = compiler->constant_pool;
      
      // Push value to constant pool
      switch (constant->type->code) {
        case SPVM_TYPE_C_CODE_BYTE: {
          break;
        }
        case SPVM_TYPE_C_CODE_SHORT: {
          break;
        }
        case SPVM_TYPE_C_CODE_INT: {
          
          int32_t value = constant->value.int_value;
          if (value >= -32768 && value <= 32767) {
            break;
          }
          
          constant->id = SPVM_CONSTANT_POOL_push_int(compiler, constant_pool, (int32_t)value);
          break;
        }
        case SPVM_TYPE_C_CODE_LONG: {
          int64_t value = constant->value.long_value;
          
          if (value >= -32768 && value <= 32767) {
            break;
          }
          
          constant->id = SPVM_CONSTANT_POOL_push_long(compiler, constant_pool, value);
          break;
        }
        case SPVM_TYPE_C_CODE_FLOAT: {
          float value = constant->value.float_value;
          
          if (value == 0 || value == 1 || value == 2) {
            break;
          }
          
          constant->id = SPVM_CONSTANT_POOL_push_float(compiler, constant_pool, value);
          break;
        }
        case SPVM_TYPE_C_CODE_DOUBLE: {
          double value = constant->value.double_value;
          
          if (value == 0 || value == 1) {
            break;
          }
          
          constant->id = SPVM_CONSTANT_POOL_push_double(compiler, constant_pool, value);
          break;
        }
        case SPVM_TYPE_C_CODE_STRING: {
          const char* value = constant->value.string_value;
          
          constant->id = SPVM_CONSTANT_POOL_push_string(compiler, constant_pool, value);
          
          break;
        }
        default:
          assert(0);
      }
    }
  }
  
  // Push types to constant pool
  {
    int32_t i;
    for (i = 0; i < compiler->types->length; i++) {
      SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, i);
      type->id = SPVM_CONSTANT_POOL_push_type(compiler, compiler->constant_pool, type);
    }
  }

  // Set parent type id and element type id
  {
    int32_t i;
    for (i = 0; i < compiler->types->length; i++) {
      SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, i);
      
      char* parent_type_name = SPVM_TYPE_get_parent_name(compiler, type->name);
      SPVM_TYPE* parent_type = (SPVM_TYPE*)SPVM_HASH_search(compiler->type_symtable, parent_type_name, strlen(parent_type_name));
      if (parent_type) {
        SPVM_CONSTANT_POOL_TYPE* constant_pool_type = (SPVM_CONSTANT_POOL_TYPE*)&compiler->constant_pool->values[type->id];
        constant_pool_type->parent_type_id = parent_type->id;
      }
      
      // Element type id
      char* element_type_name = SPVM_TYPE_get_element_name(compiler, type->name);
      if (element_type_name) {
        SPVM_TYPE* element_type = (SPVM_TYPE*)SPVM_HASH_search(compiler->type_symtable, element_type_name, strlen(element_type_name));
        if (element_type) {
          SPVM_CONSTANT_POOL_TYPE* constant_pool_type = (SPVM_CONSTANT_POOL_TYPE*)&compiler->constant_pool->values[type->id];
          constant_pool_type->element_type_id = element_type->id;
        }
        else {
          assert(0);
        }
      }
    }
  }
  
  // Push type index to constant pool
  {
    int32_t i;
    for (i = 0; i < compiler->types->length; i++) {
      SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, i);
      int32_t type_id = type->id;
      int32_t added_id = SPVM_CONSTANT_POOL_push_int(compiler, compiler->constant_pool, type_id);
      if (compiler->types_base == 0) {
        compiler->types_base = added_id;
      }
    }
  }

  // Push type code to id index to constant pool
  {
    int32_t type_code;
    for (type_code = 0; type_code < SPVM_TYPE_C_CORE_LENGTH; type_code++) {
      SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, type_code);
      int32_t type_id = type->id;
      
      int32_t added_id = SPVM_CONSTANT_POOL_push_int(compiler, compiler->constant_pool, type_id);
      if (!compiler->type_code_to_id_base) {
        compiler->type_code_to_id_base = added_id;
      }
    }
  }
  
  // Push package into constant_pool
  {
    int32_t package_index;
    for (package_index = 0; package_index < op_packages->length; package_index++) {
      SPVM_OP* op_package = SPVM_DYNAMIC_ARRAY_fetch(op_packages, package_index);
      SPVM_PACKAGE* package = op_package->uv.package;
      
      // Push field information to constant pool
      {
        int32_t field_index;
        for (field_index = 0; field_index < package->op_fields->length; field_index++) {
          SPVM_OP* op_field = SPVM_DYNAMIC_ARRAY_fetch(package->op_fields, field_index);
          SPVM_FIELD* field = op_field->uv.field;
          
          // Add field to constant pool
          field->id = SPVM_CONSTANT_POOL_push_field(compiler, compiler->constant_pool, field);
        }
      }
      package->id = SPVM_CONSTANT_POOL_push_package(compiler, compiler->constant_pool, package);
    }
  }

  // Push package indexes
  {
    int32_t package_index;
    for (package_index = 0; package_index < op_packages->length; package_index++) {
      SPVM_OP* op_package = SPVM_DYNAMIC_ARRAY_fetch(op_packages, package_index);
      int32_t package_id = op_package->uv.package->id;
      
      int32_t added_id = SPVM_CONSTANT_POOL_push_int(compiler, compiler->constant_pool, package_id);
      if (!compiler->packages_base) {
        compiler->packages_base = added_id;
      }
    }
  }
  
  // Set package id to type constant pool
  {
    {
      int32_t i;
      for (i = 0; i < compiler->types->length; i++) {
        SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, i);
        if (type->op_package) {
          SPVM_PACKAGE* package = type->op_package->uv.package;
          int32_t type_id = type->id;
          SPVM_CONSTANT_POOL_TYPE* constant_pool_type = (SPVM_CONSTANT_POOL_TYPE*)&compiler->constant_pool->values[type_id];
          constant_pool_type->package_id = package->id;
        }
      }
    }
  }
  
  // Push subroutine into constant pool
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < compiler->op_subs->length; sub_index++) {
      SPVM_OP* op_sub = SPVM_DYNAMIC_ARRAY_fetch(compiler->op_subs, sub_index);
      SPVM_SUB* sub = op_sub->uv.sub;
      sub->id = SPVM_CONSTANT_POOL_push_sub(compiler, compiler->constant_pool, sub);
    }
  }

  // Push subroutine index to constant pool
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < compiler->op_subs->length; sub_index++) {
      
      SPVM_OP* op_sub = SPVM_DYNAMIC_ARRAY_fetch(compiler->op_subs, sub_index);
      SPVM_SUB* sub = op_sub->uv.sub;
      int32_t sub_id = sub->id;
      int32_t added_id = SPVM_CONSTANT_POOL_push_int(compiler, compiler->constant_pool, sub_id);
      if (!compiler->subs_base) {
        compiler->subs_base = added_id;
      }
    }
  }

  // Set destcutor sub id to package
  {
    int32_t package_index;
    for (package_index = 0; package_index < op_packages->length; package_index++) {
      SPVM_OP* op_package = SPVM_DYNAMIC_ARRAY_fetch(op_packages, package_index);
      SPVM_PACKAGE* package = op_package->uv.package;
      
      int32_t package_id = package->id;
      
      SPVM_CONSTANT_POOL_PACKAGE* constant_pool_package = (SPVM_CONSTANT_POOL_PACKAGE*)&compiler->constant_pool->values[package_id];
      
      if (package->op_sub_destructor) {
        constant_pool_package->destructor_sub_id = package->op_sub_destructor->uv.sub->id;
      }
    }
  }
}

SPVM_OP* SPVM_OP_build_grammar(SPVM_COMPILER* compiler, SPVM_OP* op_packages) {
  
  SPVM_OP* op_grammar = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_GRAMMAR, op_packages->file, op_packages->line);
  SPVM_OP_insert_child(compiler, op_grammar, op_grammar->last, op_packages);
  
  compiler->op_grammar = op_grammar;
  
  // Check syntax and data validity
  SPVM_OP_CHECKER_check(compiler);
  
  // Build constant pool
  SPVM_OP_build_constant_pool(compiler);
  
  if (compiler->fatal_error) {
    return NULL;
  }
  
  // Create bytecodes
  if (compiler->error_count > 0) {
    return NULL;
  }
  
  SPVM_BYTECODE_BUILDER_build_bytecode_array(compiler);
  
  return op_grammar;
}

const char* SPVM_OP_create_abs_name(SPVM_COMPILER* compiler, const char* package_name, const char* name) {
  int32_t length = (int32_t)(strlen(package_name) + 2 + strlen(name));
  
  char* abs_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, length);
  
  sprintf(abs_name, "%s::%s", package_name, name);
  
  return abs_name;
}

const char* SPVM_OP_create_getter_name(SPVM_COMPILER* compiler, const char* package_name, const char* name) {
  // Foo::set_bar
  int32_t length = (int32_t)(strlen(package_name) + 6 + strlen(name));
  
  char* abs_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, length);
  
  sprintf(abs_name, "%s::get_%s", package_name, name);
  
  return abs_name;
}

const char* SPVM_OP_create_setter_name(SPVM_COMPILER* compiler, const char* package_name, const char* name) {
  int32_t length = (int32_t)(strlen(package_name) + 6 + strlen(name));
  
  char* abs_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, length);
  
  sprintf(abs_name, "%s::set_%s", package_name, name);
  
  return abs_name;
}

SPVM_OP* SPVM_OP_build_package(SPVM_COMPILER* compiler, SPVM_OP* op_package, SPVM_OP* op_name_package, SPVM_OP* op_block) {
  
  SPVM_OP_insert_child(compiler, op_package, op_package->last, op_name_package);
  SPVM_OP_insert_child(compiler, op_package, op_package->last, op_block);
  
  const char* package_name = op_name_package->uv.name;
  SPVM_HASH* op_package_symtable = compiler->op_package_symtable;
  
  // Redeclaration package error
  SPVM_OP* found_op_package = SPVM_HASH_search(op_package_symtable, package_name, strlen(package_name));
  if (found_op_package) {
    SPVM_yyerror_format(compiler, "redeclaration of package \"%s\" at %s line %d\n", package_name, op_package->file, op_package->line);
  }
  else {
    // Package
    SPVM_PACKAGE* package = SPVM_PACKAGE_new(compiler);
    package->op_name = op_name_package;
    
    // Type(type is same as package name)
    SPVM_TYPE* type = SPVM_TYPE_new(compiler);
    type->name = package_name;
    type->op_package = op_package;
    type->base_type = type;
    
    // Type OP
    SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_name_package->file, op_name_package->line);
    op_type->uv.type = type;
    
    // Add type
    package->op_type = op_type;
    SPVM_DYNAMIC_ARRAY_push(compiler->op_types, op_type);
    
    SPVM_DYNAMIC_ARRAY* op_fields = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
    SPVM_DYNAMIC_ARRAY* op_subs = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
    
    SPVM_DYNAMIC_ARRAY* op_names_set_field = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
    SPVM_DYNAMIC_ARRAY* op_names_get_field = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
    
    SPVM_OP* op_decls = op_block->first;
    SPVM_OP* op_decl = op_decls->first;
    while ((op_decl = SPVM_OP_sibling(compiler, op_decl))) {
      if (op_decl->code == SPVM_OP_C_CODE_FIELD) {
        SPVM_DYNAMIC_ARRAY_push(op_fields, op_decl);
      }
      else if (op_decl->code == SPVM_OP_C_CODE_SUB) {
        SPVM_DYNAMIC_ARRAY_push(op_subs, op_decl);
      }
      else if (op_decl->code == SPVM_OP_C_CODE_ENUM) {
        SPVM_OP* op_enum_block = op_decl->first;
        SPVM_OP* op_enumeration_values = op_enum_block->first;
        SPVM_OP* op_sub = op_enumeration_values->first;
        while ((op_sub = SPVM_OP_sibling(compiler, op_sub))) {
          SPVM_DYNAMIC_ARRAY_push(op_subs, op_sub);
        }
      }
      else if (op_decl->code == SPVM_OP_C_CODE_SET) {
        SPVM_OP* op_list = op_decl->first;
        SPVM_OP* op_name = op_list->first;
        while ((op_name = SPVM_OP_sibling(compiler, op_name))) {
          SPVM_DYNAMIC_ARRAY_push(op_names_set_field, op_name);
        }
      }
      else if (op_decl->code == SPVM_OP_C_CODE_GET) {
        SPVM_OP* op_list = op_decl->first;
        SPVM_OP* op_name = op_list->first;
        while ((op_name = SPVM_OP_sibling(compiler, op_name))) {
          SPVM_DYNAMIC_ARRAY_push(op_names_get_field, op_name);
        }
      }
      else {
        assert(0);
      }
    }
    
    // Register field
    {
      int32_t i;
      for (i = 0; i < op_fields->length; i++) {
        SPVM_OP* op_field = SPVM_DYNAMIC_ARRAY_fetch(op_fields, i);
        
        SPVM_FIELD* field = op_field->uv.field;
        const char* field_name = field->op_name->uv.name;
        
        SPVM_OP* found_op_field = SPVM_HASH_search(package->op_field_symtable, field_name, strlen(field_name));
        
        assert(op_fields->length <= SPVM_LIMIT_C_FIELDS);
        
        if (found_op_field) {
          SPVM_yyerror_format(compiler, "Redeclaration of field \"%s::%s\" at %s line %d\n", package_name, field_name, op_field->file, op_field->line);
        }
        else if (op_fields->length == SPVM_LIMIT_C_FIELDS) {
          SPVM_yyerror_format(compiler, "Too many fields, field \"%s\" ignored at %s line %d\n", field_name, op_field->file, op_field->line);
          compiler->fatal_error = 1;
        }
        else {
          SPVM_HASH_insert(package->op_field_symtable, field_name, strlen(field_name), op_field);
          
          // Add op package
          field->op_package = op_package;
          
          
        }
      }
    }

    // Add package
    op_package->uv.package = package;
    
    // Subroutine limit rest. new and getter and setter
    int32_t sub_limit_rest = 1 + op_fields->length * 2;
    
    // Register subrotuine
    {
      int32_t i;
      for (i = 0; i < op_subs->length; i++) {
        SPVM_OP* op_sub = SPVM_DYNAMIC_ARRAY_fetch(op_subs, i);

        SPVM_SUB* sub = op_sub->uv.sub;
        
        SPVM_OP* op_name_sub = sub->op_name;
        const char* sub_name = op_name_sub->uv.name;
        const char* sub_abs_name = SPVM_OP_create_abs_name(compiler, package_name, sub_name);
        
        SPVM_OP* found_op_sub = SPVM_HASH_search(compiler->op_sub_symtable, sub_abs_name, strlen(sub_abs_name));
        
        if (found_op_sub) {
          SPVM_yyerror_format(compiler, "Redeclaration of sub \"%s\" at %s line %d\n", sub_abs_name, op_sub->file, op_sub->line);
        }
        else if (op_subs->length == SPVM_LIMIT_C_SUBS - sub_limit_rest) {
          SPVM_yyerror_format(compiler, "Too many subroutines at %s line %d\n", sub_name, op_sub->file, op_sub->line);
          compiler->fatal_error = 1;
        }
        // Unknown sub
        else {
          // Bind standard functions
          if (sub->is_native) {
            SPVM_DYNAMIC_ARRAY_push(compiler->native_subs, sub);
            SPVM_DYNAMIC_ARRAY_push(package->native_subs, sub);
          }
          
          sub->abs_name = sub_abs_name;
          
          sub->op_package = op_package;
          
          if (sub->is_destructor) {
            package->op_sub_destructor = op_sub;
          }
          
          assert(op_sub->file);
          
          sub->file_name = op_sub->file;
          
          SPVM_DYNAMIC_ARRAY_push(compiler->op_subs, op_sub);
          SPVM_HASH_insert(compiler->op_sub_symtable, sub_abs_name, strlen(sub_abs_name), op_sub);
        }
      }
    }

    // Create gettter
    {
      int32_t i;
      for (i = 0; i < op_names_get_field->length; i++) {
        SPVM_OP* op_name = SPVM_DYNAMIC_ARRAY_fetch(op_names_get_field, i);
        
        const char* field_name = op_name->uv.name;
        
        const char* sub_abs_name_getter = SPVM_OP_create_getter_name(compiler, package_name, field_name);
        
        SPVM_OP* op_field_found = SPVM_HASH_search(package->op_field_symtable, field_name, strlen(field_name));
        
        if (!op_field_found) {
          SPVM_yyerror_format(compiler, "Can't create get accessor get_%s because %s field is not declared in %s package",
            field_name, field_name, package_name, op_name->file, op_name->line);
        }
        else {
          SPVM_OP* found_op_sub_getter = SPVM_HASH_search(compiler->op_sub_symtable, sub_abs_name_getter, strlen(sub_abs_name_getter));
          
          if (found_op_sub_getter) {
            SPVM_yyerror_format(compiler, "Can't create get accessor get_%s because %s subroutine is already declared in %s package",
              field_name, field_name, package_name, op_name->file, op_name->line);
          }
          else {
            SPVM_OP* op_sub_getter = SPVM_OP_build_sub_getter(compiler, op_package, op_field_found);
            
            SPVM_SUB* sub_getter = op_sub_getter->uv.sub;
            sub_getter->abs_name = sub_abs_name_getter;
            sub_getter->file_name = op_package->file;
            sub_getter->op_package = op_package;
            
            SPVM_DYNAMIC_ARRAY_push(compiler->op_subs, op_sub_getter);
            SPVM_HASH_insert(compiler->op_sub_symtable, sub_abs_name_getter, strlen(sub_abs_name_getter), op_sub_getter);
          }
        }
      }
    }

    // Create setter
    {
      int32_t i;
      for (i = 0; i < op_names_set_field->length; i++) {
        SPVM_OP* op_name = SPVM_DYNAMIC_ARRAY_fetch(op_names_set_field, i);
        
        const char* field_name = op_name->uv.name;
        
        const char* sub_abs_name_setter = SPVM_OP_create_setter_name(compiler, package_name, field_name);
        
        SPVM_OP* op_field_found = SPVM_HASH_search(package->op_field_symtable, field_name, strlen(field_name));
        
        if (!op_field_found) {
          SPVM_yyerror_format(compiler, "Can't create set accessor set_%s because %s field is not declared in %s package",
            field_name, field_name, package_name, op_name->file, op_name->line);
        }
        else {
          SPVM_OP* found_op_sub_setter = SPVM_HASH_search(compiler->op_sub_symtable, sub_abs_name_setter, strlen(sub_abs_name_setter));
          
          if (found_op_sub_setter) {
            SPVM_yyerror_format(compiler, "Can't create set accessor set_%s because %s subroutine is already declared in %s package",
              field_name, field_name, package_name, op_name->file, op_name->line);
          }
          else {
            SPVM_OP* op_sub_setter = SPVM_OP_build_sub_setter(compiler, op_package, op_field_found);
            
            SPVM_SUB* sub_setter = op_sub_setter->uv.sub;
            sub_setter->abs_name = sub_abs_name_setter;
            sub_setter->file_name = op_package->file;
            sub_setter->op_package = op_package;
            
            SPVM_DYNAMIC_ARRAY_push(compiler->op_subs, op_sub_setter);
            SPVM_HASH_insert(compiler->op_sub_symtable, sub_abs_name_setter, strlen(sub_abs_name_setter), op_sub_setter);
          }
        }
      }
    }
    
    // Add default constructor
    const char* sub_abs_name_new = SPVM_OP_create_abs_name(compiler, package_name, "new");
    SPVM_OP* found_op_sub_new = SPVM_HASH_search(compiler->op_sub_symtable, sub_abs_name_new, strlen(sub_abs_name_new));
    if (!found_op_sub_new) {
      SPVM_OP* op_sub_new = SPVM_OP_build_default_new(compiler, package->op_type);
      SPVM_SUB* sub_new = op_sub_new->uv.sub;
      sub_new->abs_name = sub_abs_name_new;
      sub_new->file_name = op_package->file;
      sub_new->op_package = op_package;
      
      SPVM_DYNAMIC_ARRAY_push(compiler->op_subs, op_sub_new);
      SPVM_HASH_insert(compiler->op_sub_symtable, sub_abs_name_new, strlen(sub_abs_name_new), op_sub_new);
    }
    
    // Add op fields
    package->op_fields = op_fields;
    
    SPVM_DYNAMIC_ARRAY_push(compiler->op_packages, op_package);
    SPVM_HASH_insert(compiler->op_package_symtable, package_name, strlen(package_name), op_package);
  }
  
  return op_package;
}

SPVM_OP* SPVM_OP_build_use(SPVM_COMPILER* compiler, SPVM_OP* op_use, SPVM_OP* op_name_package_with_template_args) {
  
  SPVM_OP_insert_child(compiler, op_use, op_use->last, op_name_package_with_template_args);

  const char* package_name_with_template_args = op_name_package_with_template_args->uv.name;
  
  SPVM_USE* use = SPVM_USE_new(compiler);
  op_use->uv.use = use;
  use->package_name_with_template_args = package_name_with_template_args;
  
  SPVM_DYNAMIC_ARRAY* part_names = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  
  const char* found_ptr = package_name_with_template_args;
  const char* base_ptr = package_name_with_template_args;
  
  while (1) {
    found_ptr = strchr(base_ptr, '_');
    if (found_ptr) {
      int32_t length = (int32_t)(found_ptr - base_ptr);
      char* part_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, length);
      memcpy(part_name, base_ptr, length);
      part_name[length] = '\0';
      SPVM_DYNAMIC_ARRAY_push(part_names, part_name);
      base_ptr = found_ptr + 1;
    }
    else {
      break;
    }
  }
  {
    int32_t length = (int32_t)(&package_name_with_template_args[strlen(package_name_with_template_args)] - base_ptr);
    char* part_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, length);
    memcpy(part_name, base_ptr, length);
    part_name[length] = '\0';
    SPVM_DYNAMIC_ARRAY_push(part_names, part_name);
  }
  
  const char* package_name = SPVM_DYNAMIC_ARRAY_fetch(part_names, 0);
  use->package_name = package_name;
  if (part_names->length > 1) {
    int32_t i;
    for (i = 1; i < part_names->length; i++) {
      char* part_name = SPVM_DYNAMIC_ARRAY_fetch(part_names, i);
      SPVM_DYNAMIC_ARRAY_push(use->template_args, part_name);
    }
  }
  
  SPVM_OP* found_op_use = SPVM_HASH_search(compiler->op_use_symtable, package_name_with_template_args, strlen(package_name));
  
  if (!found_op_use) {
    SPVM_DYNAMIC_ARRAY_push(compiler->op_use_stack, op_use);
    SPVM_HASH_insert(compiler->op_use_symtable, package_name_with_template_args, strlen(package_name), op_use);
  }
  
  return op_use;
}

SPVM_OP* SPVM_OP_build_my_var(SPVM_COMPILER* compiler, SPVM_OP* op_var, SPVM_OP* op_type) {
  
  SPVM_OP* op_my_var = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_MY, op_var->file, op_var->line);
  
  // Create my var information
  SPVM_MY_VAR* my_var = SPVM_MY_VAR_new(compiler);
  if (op_type) {
    my_var->op_type = op_type;
  }
  else {
    SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_var->file, op_var->line);
    my_var->op_type = op_type;
  }
  
  // Name OP
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NAME, op_var->file, op_var->line);
  op_name->uv.name = op_var->uv.var->op_name->uv.name;
  my_var->op_name = op_name;

  // Add my_var information to op
  op_my_var->uv.my_var = my_var;
  
  op_var->uv.var->op_my_var = op_my_var;
  
  SPVM_OP_insert_child(compiler, op_var, op_var->last, op_my_var);
  
  assert(op_var->first);
  
  return op_var;
}

SPVM_OP* SPVM_OP_build_field(SPVM_COMPILER* compiler, SPVM_OP* op_field, SPVM_OP* op_name_field, SPVM_OP* op_descriptors, SPVM_OP* op_type) {

  if (op_descriptors == NULL) {
    op_descriptors = SPVM_OP_new_op_list(compiler, op_field->file, op_field->line);
  }
  
  // Build OP
  SPVM_OP_insert_child(compiler, op_field, op_field->last, op_name_field);
  SPVM_OP_insert_child(compiler, op_field, op_field->last, op_descriptors);
  SPVM_OP_insert_child(compiler, op_field, op_field->last, op_type);
  
  // Create field information
  SPVM_FIELD* field = SPVM_FIELD_new(compiler);
  
  // Name
  field->op_name = op_name_field;
  
  // Type
  field->op_type = op_type;

  // field->is_private = 1;
  
  // Set field informaiton
  op_field->uv.field = field;
  
  return op_field;
}

SPVM_OP* SPVM_OP_build_sub(SPVM_COMPILER* compiler, SPVM_OP* op_sub, SPVM_OP* op_name_sub, SPVM_OP* op_args, SPVM_OP* op_descriptors, SPVM_OP* op_return_type, SPVM_OP* op_block) {
  
  if (op_name_sub->code == SPVM_OP_C_CODE_NEW) {
    op_name_sub->code = SPVM_OP_C_CODE_NAME;
    op_name_sub->uv.name = "new";
  }
  
  if (op_args == NULL) {
    op_args = SPVM_OP_new_op_list(compiler, op_sub->file, op_sub->line);
  }
  if (op_descriptors == NULL) {
    op_descriptors = SPVM_OP_new_op_list(compiler, op_sub->file, op_sub->line);
  }
  
  // Build OP_SUB
  SPVM_OP_insert_child(compiler, op_sub, op_sub->last, op_name_sub);
  SPVM_OP_insert_child(compiler, op_sub, op_sub->last, op_args);
  SPVM_OP_insert_child(compiler, op_sub, op_sub->last, op_descriptors);
  SPVM_OP_insert_child(compiler, op_sub, op_sub->last, op_return_type);
  if (op_block) {
    op_block->flag = SPVM_OP_C_FLAG_BLOCK_SUB;
    SPVM_OP_insert_child(compiler, op_sub, op_sub->last, op_block);
  }
  
  // Create sub information
  SPVM_SUB* sub = SPVM_SUB_new(compiler);
  sub->op_name = op_name_sub;
  
  // Descriptors
  SPVM_OP* op_descriptor = op_descriptors->first;
  while ((op_descriptor = SPVM_OP_sibling(compiler, op_descriptor))) {
    if (op_descriptor->code == SPVM_DESCRIPTOR_C_CODE_NATIVE) {
      sub->is_native = 1;
    }
    else {
      SPVM_yyerror_format(compiler, "invalid subroutine descriptor %s", SPVM_DESCRIPTOR_C_CODE_NAMES[op_descriptor->code], op_descriptors->file, op_descriptors->line);
    }
  }
  
  // Native subroutine can't have block
  if (sub->is_native && op_block) {
    SPVM_yyerror_format(compiler, "Native subroutine can't have block", op_block->file, op_block->line);
  }
  
  // subargs
  {
    SPVM_OP* op_arg = op_args->first;
    while ((op_arg = SPVM_OP_sibling(compiler, op_arg))) {
      SPVM_DYNAMIC_ARRAY_push(sub->op_args, op_arg->first);
    }
  }

  // Native my vars is same as arguments
  if (sub->is_native) {
    SPVM_OP* op_arg = op_args->first;
    while ((op_arg = SPVM_OP_sibling(compiler, op_arg))) {
      SPVM_DYNAMIC_ARRAY_push(sub->op_my_vars, op_arg->first);
    }
  }

  // return type
  sub->op_return_type = op_return_type;
  
  if (strcmp(sub->op_name->uv.name, "DESTROY") == 0) {
    sub->is_destructor = 1;
    // DESTROY return type must be void
    if (sub->op_return_type->uv.type->code != SPVM_TYPE_C_CODE_VOID) {
      SPVM_yyerror_format(compiler, "DESTROY return type must be void\n", op_block->file, op_block->line);
    }
  }
  
  // Add my declaration to first of block
  if (op_block) {
    SPVM_OP* op_list_statement = op_block->first;
    {
      int32_t i;
      for (i = sub->op_args->length - 1; i >= 0; i--) {
        SPVM_OP* op_arg = SPVM_DYNAMIC_ARRAY_fetch(sub->op_args, i);
        SPVM_OP* op_my_var = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_MY, op_arg->file, op_arg->line);
        op_my_var->uv.my_var = op_arg->uv.my_var;
        SPVM_OP_insert_child(compiler, op_list_statement, op_list_statement->first, op_my_var);
      }
    }
    
    // Add return to last of statement if need
    if (!op_list_statement->last || op_list_statement->last->code != SPVM_OP_C_CODE_RETURN) {
      SPVM_OP* op_return = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_RETURN, op_list_statement->file, op_list_statement->line);
      SPVM_TYPE* return_type = sub->op_return_type->uv.type;
      
      SPVM_OP* op_constant;
      if (return_type->code == SPVM_TYPE_C_CODE_VOID) {
        // Nothing
      }
      else if (return_type->code == SPVM_TYPE_C_CODE_BYTE) {
        op_constant = SPVM_OP_new_op_constant_byte(compiler, 0, op_list_statement->file, op_list_statement->line);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
      }
      else if (return_type->code == SPVM_TYPE_C_CODE_SHORT) {
        op_constant = SPVM_OP_new_op_constant_short(compiler, 0, op_list_statement->file, op_list_statement->line);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
      }
      else if (return_type->code == SPVM_TYPE_C_CODE_INT) {
        op_constant = SPVM_OP_new_op_constant_int(compiler, 0, op_list_statement->file, op_list_statement->line);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
      }
      else if (return_type->code == SPVM_TYPE_C_CODE_LONG) {
        op_constant = SPVM_OP_new_op_constant_long(compiler, 0, op_list_statement->file, op_list_statement->line);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
      }
      else if (return_type->code == SPVM_TYPE_C_CODE_FLOAT) {
        op_constant = SPVM_OP_new_op_constant_float(compiler, 0, op_list_statement->file, op_list_statement->line);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
      }
      else if (return_type->code == SPVM_TYPE_C_CODE_DOUBLE) {
        op_constant = SPVM_OP_new_op_constant_double(compiler, 0, op_list_statement->file, op_list_statement->line);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
      }
      else {
        // Undef
        SPVM_OP* op_undef = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_UNDEF, op_list_statement->file, op_list_statement->line);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_undef);
      }
      
      SPVM_OP_insert_child(compiler, op_list_statement, op_list_statement->last, op_return);
    }
  }
  
  // Save block
  sub->op_block = op_block;

  op_sub->uv.sub = sub;
  
  return op_sub;
}

SPVM_OP* SPVM_OP_build_enumeration_value(SPVM_COMPILER* compiler, SPVM_OP* op_name, SPVM_OP* op_constant) {
  
  if (op_constant) {
    
    SPVM_CONSTANT* constant = op_constant->uv.constant;
    
    compiler->enum_default_type_code = constant->type->code;
    
    // TODO add type
    if (compiler->enum_default_type_code == SPVM_TYPE_C_CODE_BYTE) {
      compiler->enum_default_value = constant->value.byte_value;
    }
    else if (compiler->enum_default_type_code == SPVM_TYPE_C_CODE_SHORT) {
      compiler->enum_default_value = constant->value.short_value;
    }
    else if (compiler->enum_default_type_code == SPVM_TYPE_C_CODE_INT) {
      compiler->enum_default_value = constant->value.int_value;
    }
    else if (compiler->enum_default_type_code == SPVM_TYPE_C_CODE_LONG) {
      compiler->enum_default_value = constant->value.long_value;
    }
    else if (compiler->enum_default_type_code == SPVM_TYPE_C_CODE_FLOAT) {
      compiler->enum_default_value = (int64_t)constant->value.float_value;
    }
    else if (compiler->enum_default_type_code == SPVM_TYPE_C_CODE_DOUBLE) {
      compiler->enum_default_value = (int64_t)constant->value.double_value;
    }
    
    compiler->enum_default_value++;
  }
  else {
    // TODO add type
    if (compiler->enum_default_type_code == SPVM_TYPE_C_CODE_BYTE) {
      op_constant = SPVM_OP_new_op_constant_byte(compiler, (int8_t)compiler->enum_default_value, op_name->file, op_name->line);
    }
    else if (compiler->enum_default_type_code == SPVM_TYPE_C_CODE_SHORT) {
      op_constant = SPVM_OP_new_op_constant_short(compiler, (int16_t)compiler->enum_default_value, op_name->file, op_name->line);
    }
    else if (compiler->enum_default_type_code == SPVM_TYPE_C_CODE_INT) {
      op_constant = SPVM_OP_new_op_constant_int(compiler, (int32_t)compiler->enum_default_value, op_name->file, op_name->line);
    }
    else if (compiler->enum_default_type_code == SPVM_TYPE_C_CODE_LONG) {
      op_constant = SPVM_OP_new_op_constant_long(compiler, (int64_t)compiler->enum_default_value, op_name->file, op_name->line);
    }
    else if (compiler->enum_default_type_code == SPVM_TYPE_C_CODE_FLOAT) {
      op_constant = SPVM_OP_new_op_constant_float(compiler, (float)compiler->enum_default_value, op_name->file, op_name->line);
    }
    else if (compiler->enum_default_type_code == SPVM_TYPE_C_CODE_DOUBLE) {
      op_constant = SPVM_OP_new_op_constant_double(compiler, (double)compiler->enum_default_value, op_name->file, op_name->line);
    }
    else {
      assert(0);
    }
    
    compiler->enum_default_value++;
  }
  
  // Return
  SPVM_OP* op_return = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_RETURN, op_name->file, op_name->line);
  SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
  
  // Statements
  SPVM_OP* op_list_statements = SPVM_OP_new_op_list(compiler, op_name->file, op_name->line);
  SPVM_OP_insert_child(compiler, op_list_statements, op_list_statements->last, op_return);

  // Block
  SPVM_OP* op_block = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, op_name->file, op_name->line);
  SPVM_OP_insert_child(compiler, op_block, op_block->last, op_list_statements);
  
  // sub
  SPVM_OP* op_sub = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_SUB, op_name->file, op_name->line);
  op_sub->file = op_name->file;
  op_sub->line = op_name->line;
  
  // Type
  SPVM_OP* op_return_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_name->file, op_name->line);
  op_return_type->uv.type = op_constant->uv.constant->type;
  
  // Build subroutine
  op_sub = SPVM_OP_build_sub(compiler, op_sub, op_name, NULL, NULL, op_return_type, op_block);
  
  // Set constant
  op_sub->uv.sub->op_constant = op_constant;
  
  // Subroutine is constant
  op_sub->uv.sub->is_constant = 1;
  
  return op_sub;
}

SPVM_OP* SPVM_OP_build_enumeration(SPVM_COMPILER* compiler, SPVM_OP* op_enumeration, SPVM_OP* op_enumeration_block) {
  
  // Build OP_SUB
  SPVM_OP_insert_child(compiler, op_enumeration, op_enumeration->last, op_enumeration_block);
  
  // Reset enum information
  compiler->enum_default_value = 0;
  compiler->enum_default_type_code = SPVM_TYPE_C_CODE_INT;
  
  return op_enumeration;
}

SPVM_OP* SPVM_OP_build_call_sub(SPVM_COMPILER* compiler, SPVM_OP* op_invocant, SPVM_OP* op_name_sub, SPVM_OP* op_terms) {
  
  // Build OP_SUB
  SPVM_OP* op_call_sub = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CALL_SUB, op_name_sub->file, op_name_sub->line);
  SPVM_OP_insert_child(compiler, op_call_sub, op_call_sub->last, op_name_sub);
  SPVM_OP_insert_child(compiler, op_call_sub, op_call_sub->last, op_terms);
  
  SPVM_CALL_SUB* call_sub = SPVM_CALL_SUB_new(compiler);
  
  const char* sub_name = op_name_sub->uv.name;
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NAME, op_invocant->file, op_invocant->line);
  
  // Normal call
  if (op_invocant->code == SPVM_OP_C_CODE_NULL) {
    call_sub->code = SPVM_CALL_SUB_C_CODE_SUB_CALL;
    op_name->uv.name = sub_name;
    call_sub->op_name = op_name;
  }
  // Method call
  else {
    call_sub->code = SPVM_CALL_SUB_C_CODE_METHOD_CALL;
    call_sub->op_term = op_invocant;
    call_sub->op_name = op_name_sub;
    
    SPVM_OP_insert_child(compiler, op_terms, op_terms->last, op_invocant);
  }
  
  op_call_sub->uv.call_sub = call_sub;
  
  return op_call_sub;
}

SPVM_OP* SPVM_OP_build_unop(SPVM_COMPILER* compiler, SPVM_OP* op_unary, SPVM_OP* op_first) {
  
  // Build op
  SPVM_OP_insert_child(compiler, op_unary, op_unary->last, op_first);
  
  return op_unary;
}

SPVM_OP* SPVM_OP_build_binop(SPVM_COMPILER* compiler, SPVM_OP* op_bin, SPVM_OP* op_first, SPVM_OP* op_last) {
  
  // Build op
  SPVM_OP_insert_child(compiler, op_bin, op_bin->last, op_first);
  SPVM_OP_insert_child(compiler, op_bin, op_bin->last, op_last);
  
  return op_bin;
}

SPVM_OP* SPVM_OP_build_concat_string(SPVM_COMPILER* compiler, SPVM_OP* op_cancat_string, SPVM_OP* op_first, SPVM_OP* op_last) {
  
  // Build op
  SPVM_OP_insert_child(compiler, op_cancat_string, op_cancat_string->last, op_first);
  SPVM_OP_insert_child(compiler, op_cancat_string, op_cancat_string->last, op_last);
  
  return op_cancat_string;
}

SPVM_OP* SPVM_OP_build_and(SPVM_COMPILER* compiler, SPVM_OP* op_and, SPVM_OP* op_first, SPVM_OP* op_last) {
  
  // Convert && to if statement
  /* before
    AND
      first
      last
  */
  
  /* after 
    IF              if1
      CONDITION
        first
      IF            if2
        CONDITION
          last
        1           true1
        0           false1
      0             false2
  */
  
  SPVM_OP* op_if1 = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_IF, op_and->file, op_and->line);
  
  // Constant true
  SPVM_OP* op_constant_true = SPVM_OP_new_op_constant_int(compiler, 1, op_if1->file, op_if1->line);

  // Constant false 1
  SPVM_OP* op_constant_false1 = SPVM_OP_new_op_constant_int(compiler, 0, op_if1->file, op_if1->line);
  
  // Constant false 2
  SPVM_OP* op_constant_false2 = SPVM_OP_new_op_constant_int(compiler, 0, op_if1->file, op_if1->line);
  
  // if2
  SPVM_OP* op_if2 = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_IF, op_if1->file, op_if1->line);
  
  // Build if tree
  SPVM_OP_build_if_statement(compiler, op_if2, op_last, op_constant_true, op_constant_false1);
  SPVM_OP_build_if_statement(compiler, op_if1, op_first, op_if2, op_constant_false2);
  
  return op_if1;
}

SPVM_OP* SPVM_OP_build_or(SPVM_COMPILER* compiler, SPVM_OP* op_or, SPVM_OP* op_first, SPVM_OP* op_last) {
  
  // Convert || to if statement
  // before
  //  OR
  //    first
  //    last
  
  // after 
  //  IF      if1
  //    first
  //    1     true1
  //    IF    if2
  //      last
  //      1   true2
  //      0   false
  
  SPVM_OP* op_if1 = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_IF, op_or->file, op_or->line);
  
  // Constant true 1
  SPVM_OP* op_constant_true1 = SPVM_OP_new_op_constant_int(compiler, 1, op_if1->file, op_if1->line);
  
  // Constant true 2
  SPVM_OP* op_constant_true2 = SPVM_OP_new_op_constant_int(compiler, 1, op_if1->file, op_if1->line);
  
  // Constant false
  SPVM_OP* op_constant_false = SPVM_OP_new_op_constant_int(compiler, 0, op_if1->file, op_if1->line);
  
  // if2
  SPVM_OP* op_if2 = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_IF, op_if1->file, op_if1->line);
  
  // Build if tree
  SPVM_OP_build_if_statement(compiler, op_if2, op_last, op_constant_true2, op_constant_false);
  SPVM_OP_build_if_statement(compiler, op_if1, op_first, op_constant_true1, op_if2);
  
  return op_if1;
}

SPVM_OP* SPVM_OP_build_not(SPVM_COMPILER* compiler, SPVM_OP* op_not, SPVM_OP* op_first) {
  
  // Convert ! to if statement
  // before
  //  NOT
  //    first
  
  // after 
  //  IF
  //    first
  //    0
  //    1
  
  SPVM_OP* op_if = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_IF, op_not->file, op_not->line);
  
  // Constant false
  SPVM_OP* op_constant_false = SPVM_OP_new_op_constant_int(compiler, 0, op_if->file, op_if->line);

  // Constant true
  SPVM_OP* op_constant_true = SPVM_OP_new_op_constant_int(compiler, 1, op_if->file, op_if->line);
  
  // Build if tree
  SPVM_OP_build_if_statement(compiler, op_if, op_first, op_constant_false, op_constant_true);
  
  return op_if;
}


SPVM_OP* SPVM_OP_build_assign(SPVM_COMPILER* compiler, SPVM_OP* op_assign, SPVM_OP* op_first, SPVM_OP* op_last) {
  
  if (op_assign->code == SPVM_OP_C_CODE_SPECIAL_ASSIGN) {
    int32_t flag = op_assign->flag;
    
    SPVM_OP* op_operation;
    if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_ADD) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ADD, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_SUBTRACT) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_SUBTRACT, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_MULTIPLY) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_MULTIPLY, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_DIVIDE) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_DIVIDE, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_REMAINDER) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_REMAINDER, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_LEFT_SHIFT) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_LEFT_SHIFT, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_SHIFT) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_RIGHT_SHIFT, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_SHIFT_UNSIGNED) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_RIGHT_SHIFT_UNSIGNED, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_XOR) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BIT_XOR, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_OR) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BIT_OR, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_AND) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BIT_AND, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_CONCAT_STRING) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONCAT_STRING, op_assign->file, op_assign->line);
    }
    else {
      assert(0);
    }
    
    SPVM_OP* op_var_right = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_VAR, op_assign->file, op_assign->line);
    op_var_right->uv.var = op_first->uv.var;
    
    SPVM_OP_insert_child(compiler, op_operation, op_operation->last, op_var_right);
    SPVM_OP_insert_child(compiler, op_operation, op_operation->last, op_last);
    
    op_last = op_operation;
    
    op_assign->code = SPVM_OP_C_CODE_ASSIGN;
  }
  
  // Stab to add after process
  SPVM_OP* op_assign_process = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ASSIGN_PROCESS, op_assign->file, op_assign->line);
  
  // Build op
  SPVM_OP_insert_child(compiler, op_assign, op_assign->last, op_first);
  SPVM_OP_insert_child(compiler, op_assign, op_assign->last, op_last);
  
  op_assign->first->lvalue = 1;
  op_assign->last->rvalue = 1;
  
  // Return variable if first children is var
  if (op_first->code == SPVM_OP_C_CODE_VAR) {
    SPVM_OP* op_var = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_VAR, op_assign->file, op_assign->line);
    op_var->uv.var = op_first->uv.var;
    SPVM_OP_insert_child(compiler, op_var, op_var->last, op_assign);
    
    SPVM_OP_insert_child(compiler, op_assign_process, op_assign_process->last, op_var);

    // Array initialization
    if (op_last->code == SPVM_OP_C_CODE_LIST) {
      SPVM_OP* op_list = op_last;
      
      op_list->moresib = 0;
      op_list->sibparent = NULL;
      
      // Length term
      int32_t length = 0;
      SPVM_OP* op_term = op_list->first;
      while ((op_term = SPVM_OP_sibling(compiler, op_term))) {
        length++;
      }
      SPVM_OP* op_constant_length = SPVM_OP_new_op_constant_int(compiler, length, op_list->file, op_list->line);
      
      // New
      SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NEW, op_list->file, op_list->line);
      
      // Type
      SPVM_OP* op_type_new = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_list->file, op_list->line);
      SPVM_VAR* var = op_assign->first->uv.var;
      SPVM_MY_VAR* my_var = var->op_my_var->uv.my_var;
      SPVM_TYPE* type =  my_var->op_type->uv.type;
      op_type_new->uv.type = type;
      
      // Add OP type
      SPVM_DYNAMIC_ARRAY_push(compiler->op_types, op_type_new);
      
      SPVM_OP_insert_child(compiler, op_new, op_new->last, op_type_new);
      
      op_assign->last = op_new;
      op_new->moresib = 0;
      op_new->sibparent = op_assign;
      op_first->sibparent = op_new;
      
      // Add length term
      SPVM_OP_insert_child(compiler, op_type_new, op_type_new->last, op_constant_length);
      
      // Assign array element
      SPVM_OP* op_list_new = SPVM_OP_new_op_list(compiler, op_list->file, op_list->line);
      SPVM_DYNAMIC_ARRAY* op_terms = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
      op_term = op_list->first;
      while ((op_term = SPVM_OP_sibling(compiler, op_term))) {
        SPVM_DYNAMIC_ARRAY_push(op_terms, op_term);
      }
      {
        int32_t i;
        for (i = 0; i < op_terms->length; i++) {
          SPVM_OP* op_term = SPVM_DYNAMIC_ARRAY_fetch(op_terms, i);
          
          SPVM_OP* op_assign_array = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ASSIGN, op_list->file, op_list->line);
          SPVM_OP* op_array_elem = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ARRAY_ELEM, op_list->file, op_list->line);
          SPVM_OP* op_var_array_elem = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_VAR, op_list->file, op_list->line);
          op_var_array_elem->uv.var = op_first->uv.var;
          SPVM_OP_insert_child(compiler, op_array_elem, op_array_elem->last, op_var_array_elem);
          
          SPVM_OP* op_constant_index = SPVM_OP_new_op_constant_int(compiler, i, op_list->file, op_list->line);
          SPVM_OP_insert_child(compiler, op_array_elem, op_array_elem->last, op_constant_index);
          
          SPVM_OP_insert_child(compiler, op_assign_array, op_assign_array->last, op_array_elem);
          op_term->moresib = 0;
          op_term->sibparent = NULL;
          SPVM_OP_insert_child(compiler, op_assign_array, op_assign_array->last, op_term);
          
          op_assign_array->first->lvalue = 1;
          op_assign_array->last->rvalue = 1;
          
          SPVM_OP_insert_child(compiler, op_list_new, op_list_new->last, op_assign_array);
        }
      }
      
      SPVM_OP_insert_child(compiler, op_assign_process, op_assign_process->last, op_list_new);
    }
  }
  else {
    SPVM_OP_insert_child(compiler, op_assign_process, op_assign_process->last, op_assign);
  }
  
  return op_assign_process;
}


SPVM_OP* SPVM_OP_build_return(SPVM_COMPILER* compiler, SPVM_OP* op_return, SPVM_OP* op_term) {
  
  if (op_term) {
    SPVM_OP_insert_child(compiler, op_return, op_return->last, op_term);
  }
  
  return op_return;
}

SPVM_OP* SPVM_OP_build_croak(SPVM_COMPILER* compiler, SPVM_OP* op_croak, SPVM_OP* op_term) {
  
  if (!op_term) {
    // Default error message
    op_term =SPVM_OP_new_op_constant_byte_array_string(compiler, "Error", op_croak->file, op_croak->line);;
  }
  
  // Exception variable
  SPVM_OP* op_exception_var = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_EXCEPTION_VAR, op_term->file, op_term->line);
  
  // Assign
  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ASSIGN, op_term->file, op_term->line);
  SPVM_OP_insert_child(compiler, op_assign, op_assign->last, op_exception_var);
  SPVM_OP_insert_child(compiler, op_assign, op_assign->last, op_term);
  
  op_assign->first->lvalue = 1;
  op_assign->last->rvalue = 1;
  
  SPVM_OP_insert_child(compiler, op_croak, op_croak->last, op_assign);
  
  return op_croak;
}

SPVM_OP* SPVM_OP_build_void(SPVM_COMPILER* compiler, SPVM_OP* op_void) {
  
  // Type op
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_void->file, op_void->line);
  
  op_type->uv.type = SPVM_TYPE_get_void_type(compiler);
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_type_byte(SPVM_COMPILER* compiler, SPVM_OP* op_byte) {
  
  // Type op
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_byte->file, op_byte->line);
  op_type->uv.type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_CODE_BYTE);
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_type_short(SPVM_COMPILER* compiler, SPVM_OP* op_short) {

  // Type op
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_short->file, op_short->line);
  op_type->uv.type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_CODE_SHORT);
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_type_int(SPVM_COMPILER* compiler, SPVM_OP* op_int) {
  // Type op
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_int->file, op_int->line);
  op_type->uv.type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_CODE_INT);
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_type_long(SPVM_COMPILER* compiler, SPVM_OP* op_long) {
  // Type op
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_long->file, op_long->line);
  op_type->uv.type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_CODE_LONG);
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_type_float(SPVM_COMPILER* compiler, SPVM_OP* op_float) {
  // Type op
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_float->file, op_float->line);
  op_type->uv.type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_CODE_FLOAT);
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_type_double(SPVM_COMPILER* compiler, SPVM_OP* op_double) {
  // Type op
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_double->file, op_double->line);
  op_type->uv.type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_CODE_DOUBLE);
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_type_name(SPVM_COMPILER* compiler, SPVM_OP* op_name) {
  
  // Type
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->name = op_name->uv.name;
  
  // Type op
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_name->file, op_name->line);
  SPVM_OP_insert_child(compiler, op_type, op_type->last, op_name);
  op_type->uv.type = type;
  
  // Add types
  SPVM_DYNAMIC_ARRAY_push(compiler->op_types, op_type);
  
  type->base_type = type;
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_type_array(SPVM_COMPILER* compiler, SPVM_OP* op_type_child, SPVM_OP* op_term_length) {
  
  // Type
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->name = SPVM_TYPE_create_array_name(compiler, op_type_child->uv.type->name);
  type->dimension++;
  
  type->base_type = op_type_child->uv.type->base_type;
  
  // Type OP
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_type_child->file, op_type_child->line);
  SPVM_OP_insert_child(compiler, op_type, op_type->last, op_type_child);
  
  if (op_term_length) {
    SPVM_OP_insert_child(compiler, op_type, op_type->last, op_term_length);
  }
  else {
    SPVM_OP* op_null = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, op_type_child->file, op_type_child->line);
    SPVM_OP_insert_child(compiler, op_type, op_type->last, op_null);
  }
  
  op_type->uv.type = type;
  op_type->file = op_type_child->file;
  op_type->line = op_type_child->line;
  
  SPVM_DYNAMIC_ARRAY_push(compiler->op_types, op_type);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_list(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  
  SPVM_OP* op_pushmark = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PUSHMARK, file, line);
  
  SPVM_OP* op_list = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_LIST, file, line);
  SPVM_OP_insert_child(compiler, op_list, op_list->last, op_pushmark);
  
  return op_list;
}


SPVM_OP* SPVM_OP_new_op(SPVM_COMPILER* compiler, int32_t code, const char* file, int32_t line) {

  SPVM_OP *op = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_OP));
  
  memset(op, 0, sizeof(SPVM_OP));
  
  op->code = code;
  
  assert(!op->file);
  assert(!op->line);
  
  op->file = file;
  op->line = line;
  
  return op;
}

// Insert child. Child must not have sibling.
void SPVM_OP_insert_child(SPVM_COMPILER* compiler, SPVM_OP* parent, SPVM_OP* start, SPVM_OP* insert) {
  (void)compiler;
  
  // del_count not used
  assert(parent);
  assert(insert);
  assert(insert->moresib == 0);
  
  if (start) {
    if (start->moresib) {
      insert->moresib = 1;
      insert->sibparent = start->sibparent;
      
      start->sibparent = insert;
    }
    else {
      parent->last = insert;

      insert->moresib = 0;
      insert->sibparent = parent;
      
      start->moresib = 1;
      start->sibparent = insert;
    }
  }
  else {
    if (parent->first) {
      insert->moresib = 1;
      insert->sibparent = parent->first;
      
      parent->first = insert;
    }
    else {
      insert->moresib = 0;
      insert->sibparent = parent;
      
      parent->first = insert;
      parent->last = insert;
    }
  }
}

SPVM_OP* SPVM_OP_sibling(SPVM_COMPILER* compiler, SPVM_OP* op) {
  (void)compiler;
  
  return op->moresib ? op->sibparent : NULL;
}
