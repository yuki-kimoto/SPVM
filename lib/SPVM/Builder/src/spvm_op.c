#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>
#include <ctype.h>
#include "spvm_compiler.h"
#include "spvm_list.h"
#include "spvm_hash.h"
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
#include "spvm_field_access.h"
#include "spvm_call_sub.h"
#include "spvm_type.h"
#include "spvm_opcode_builder.h"
#include "spvm_op_checker.h"
#include "spvm_switch_info.h"
#include "spvm_descriptor.h"
#include "spvm_compiler_allocator.h"
#include "spvm_limit.h"
#include "spvm_use.h"
#include "spvm_package_var.h"
#include "spvm_package_var_access.h"
#include "spvm_csource_builder_precompile.h"
#include "spvm_block.h"
#include "spvm_basic_type.h"
#include "spvm_case_info.h"
#include "spvm_array_field_access.h"

const char* const SPVM_OP_C_ID_NAMES[] = {
  "IF",
  "UNLESS",
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
  "INC",
  "DEC",
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
  "ARRAY_ACCESS",
  "ASSIGN",
  "CALL_SUB",
  "FIELD_ACCESS",
  "USE",
  "RETURN",
  "LAST",
  "NEXT",
  "LOOP",
  "VAR",
  "CONVERT",
  "UNDEF",
  "ARRAY_LENGTH",
  "CONDITION",
  "CONDITION_NOT",
  "CROAK",
  "SWITCH",
  "CASE",
  "DEFAULT",
  "SWITCH_CONDITION",
  "VOID",
  "EVAL",
  "BLOCK_END",
  "EXCEPTION_VAR",
  "NEW",
  "STAB",
  "BYTE",
  "SHORT",
  "INT",
  "LONG",
  "FLOAT",
  "DOUBLE",
  "STRING",
  "OBJECT",
  "WEAKEN",
  "WEAKEN_FIELD",
  "WEAKEN_ARRAY_ELEMENT",
  "SPECIAL_ASSIGN",
  "CONCAT",
  "SET",
  "GET",
  "OUR",
  "PACKAGE_VAR_ACCESS",
  "ARRAY_INIT",
  "BOOL",
  "LOOP_INCREMENT",
  "SELF",
  "CHECK_CAST",
  "STRING_EQ",
  "STRING_NE",
  "STRING_GT",
  "STRING_GE",
  "STRING_LT",
  "STRING_LE",
  "ISA",
  "SEQUENCE",
  "COSNT",
  "COMPILE",
  "SCALAR",
  "ARRAY_FIELD_ACCESS",
  "REF",
  "DEREF",
  "BYTE_REF",
  "SHORT_REF",
  "INT_REF",
  "LONG_REF",
  "FLOAT_REF",
  "DOUBLE_REF",
};

SPVM_OP* SPVM_OP_new_op_my(SPVM_COMPILER* compiler, SPVM_MY* my, const char* file, int32_t line) {
  SPVM_OP* op_my = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MY, file, line);
  op_my->uv.my = my;
  my->op_my = op_my;
  
  return op_my;
}

SPVM_OP* SPVM_OP_new_op_type(SPVM_COMPILER* compiler, SPVM_TYPE* type, const char* file, int32_t line) {
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, file, line);
  op_type->uv.type = type;
  
  type->op_type = op_type;
  
  SPVM_LIST_push(compiler->op_types, op_type);
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_deref(SPVM_COMPILER* compiler, SPVM_OP* op_deref, SPVM_OP* op_var) {
  
  SPVM_OP_insert_child(compiler, op_deref, op_deref->last, op_var);

  return op_deref;
}

SPVM_OP* SPVM_OP_build_ref(SPVM_COMPILER* compiler, SPVM_OP* op_ref, SPVM_OP* op_var) {
  
  SPVM_OP_insert_child(compiler, op_ref, op_ref->last, op_var);
  
  return op_ref;
}

int32_t SPVM_OP_is_mutable(SPVM_COMPILER* compiler, SPVM_OP* op) {
  (void)compiler;
  
  switch (op->id) {
    case SPVM_OP_C_ID_VAR:
    case SPVM_OP_C_ID_PACKAGE_VAR_ACCESS:
    case SPVM_OP_C_ID_ARRAY_ACCESS:
    case SPVM_OP_C_ID_FIELD_ACCESS:
    case SPVM_OP_C_ID_DEREF:
    case SPVM_OP_C_ID_EXCEPTION_VAR:
    case SPVM_OP_C_ID_ARRAY_FIELD_ACCESS:
      return 1;
  }
  
  return 0;
}

int32_t SPVM_OP_is_rel_op(SPVM_COMPILER* compiler, SPVM_OP* op) {
  (void)compiler;
  
  switch (op->id) {
    case SPVM_OP_C_ID_EQ:
    case SPVM_OP_C_ID_NE:
    case SPVM_OP_C_ID_GT:
    case SPVM_OP_C_ID_GE:
    case SPVM_OP_C_ID_LT:
    case SPVM_OP_C_ID_LE:
    case SPVM_OP_C_ID_STRING_EQ:
    case SPVM_OP_C_ID_STRING_NE:
    case SPVM_OP_C_ID_STRING_GT:
    case SPVM_OP_C_ID_STRING_GE:
    case SPVM_OP_C_ID_STRING_LT:
    case SPVM_OP_C_ID_STRING_LE:
    case SPVM_OP_C_ID_ISA:
      return 1;
  }
  
  return 0;
}

void SPVM_OP_insert_to_most_left_deep_child(SPVM_COMPILER* compiler, SPVM_OP* op_parent, SPVM_OP* op_child) {
  
  assert(op_parent);
  assert(op_parent->first);
  
  SPVM_OP* op_most_left_deep_child_of_parent = op_parent;
  
  while (1) {
    if (op_most_left_deep_child_of_parent->first) {
      op_most_left_deep_child_of_parent = op_most_left_deep_child_of_parent->first;
      continue;
    }
    else {
      break;
    }
  }
  
  SPVM_OP_insert_child(compiler, op_most_left_deep_child_of_parent, op_most_left_deep_child_of_parent->last, op_child);
}

SPVM_OP* SPVM_OP_build_var(SPVM_COMPILER* compiler, SPVM_OP* op_var_name) {
      
  const char* var_name = op_var_name->uv.name;
  int32_t var_name_length = (int32_t)strlen(var_name);
  
  SPVM_OP* op_var_ret;
  
  // Exception variable
  if (var_name_length == 2 && var_name[1] == '@') {
    // Exception variable
    SPVM_OP* op_exception_var = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_EXCEPTION_VAR, op_var_name->file, op_var_name->line);
    op_var_ret = op_exception_var;
  }
  // Lexical variable
  else {
    // Var OP
    SPVM_OP* op_var = SPVM_OP_new_op_var(compiler, op_var_name);
    op_var_ret = op_var;
  }
  
  return op_var_ret;
}

SPVM_OP* SPVM_OP_new_op_descriptor(SPVM_COMPILER* compiler, int32_t id, const char* file, int32_t line) {
  SPVM_OP* op_descriptor = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DESCRIPTOR, file, line);
  
  SPVM_DESCRIPTOR* descriptor = SPVM_DESCRIPTOR_new(compiler);
  descriptor->id = id;
  op_descriptor->uv.descriptor = descriptor;
  
  return op_descriptor;
}

SPVM_OP* SPVM_OP_new_op_undef(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_OP* op_undef = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_UNDEF, file, line);
  
  return op_undef;
}

SPVM_OP* SPVM_OP_new_op_block(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_OP* op_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BLOCK, file, line);
  
  SPVM_BLOCK* block = SPVM_BLOCK_new(compiler);
  op_block->uv.block = block;
  
  return op_block;
}

SPVM_OP* SPVM_OP_new_op_package_var_access(SPVM_COMPILER* compiler, SPVM_OP* op_name) {
  SPVM_OP* op_package_var_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PACKAGE_VAR_ACCESS, op_name->file, op_name->line);

  SPVM_PACKAGE_VAR_ACCESS* package_var_access = SPVM_PACKAGE_VAR_ACCESS_new(compiler);
  package_var_access->op_name = op_name;
  op_package_var_access->uv.package_var_access = package_var_access;
  
  return op_package_var_access;
}

SPVM_OP* SPVM_OP_clone_op_type(SPVM_COMPILER* compiler, SPVM_OP* op_type) {
  
  SPVM_OP* op_type_new = SPVM_OP_new_op_type(compiler, op_type->uv.type, op_type->file, op_type->line);
  
  return op_type_new;
}

SPVM_OP* SPVM_OP_new_op_name(SPVM_COMPILER* compiler, const char* name, const char* file, int32_t line) {
  
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NAME, file, line);
  
  op_name->uv.name = name;
  
  return op_name;
}

SPVM_OP* SPVM_OP_new_op_var(SPVM_COMPILER* compiler, SPVM_OP* op_name) {
  
  SPVM_OP* op_var = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_VAR, op_name->file, op_name->line);

  SPVM_VAR* var = SPVM_VAR_new(compiler);
  var->op_name = op_name;
  op_var->uv.var = var;
  
  return op_var;
}

SPVM_OP* SPVM_OP_new_op_var_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_var, const char* file, int32_t line) {
  (void)compiler;
  
  SPVM_VAR* var = SPVM_VAR_new(compiler);
  SPVM_OP* op_var = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_VAR, file, line);
  
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NAME, file, line);
  op_name->uv.name = original_op_var->uv.var->my->op_name->uv.name;
  var->op_name = op_name;
  var->my = original_op_var->uv.var->my;
  op_var->uv.var = var;
  
  assert(original_op_var->uv.var != op_var->uv.var);
  
  return op_var;
}

SPVM_OP* SPVM_OP_new_op_var_clone_var_or_assign(SPVM_COMPILER* compiler, SPVM_OP* original_op_var_or_assign) {
  (void)compiler;
  
  SPVM_OP* original_op_var;
  if (original_op_var_or_assign->id == SPVM_OP_C_ID_ASSIGN) {
    if (original_op_var_or_assign->last->id == SPVM_OP_C_ID_VAR) {
      original_op_var = original_op_var_or_assign->last;
    }
    else {
      assert(0);
    }
  }
  else if (original_op_var_or_assign->id == SPVM_OP_C_ID_VAR) {
    original_op_var = original_op_var_or_assign;
  }
  else {
    assert(0);
  }
  
  SPVM_OP* op_var = SPVM_OP_new_op_var_clone(compiler, original_op_var, original_op_var_or_assign->file, original_op_var_or_assign->line);
  return op_var;
}


SPVM_OP* SPVM_OP_new_op_field_access_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_field_access) {
  (void)compiler;
  
  SPVM_OP* op_var_invoker = SPVM_OP_new_op_var_clone_var_or_assign(compiler, original_op_field_access->first);
  
  SPVM_OP* op_name_field = SPVM_OP_new_op_name(compiler, original_op_field_access->uv.field_access->op_name->uv.name, original_op_field_access->file, original_op_field_access->line);
  SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, op_var_invoker, op_name_field);
  
  op_field_access->uv.field_access = original_op_field_access->uv.field_access;
  
  return op_field_access;
}

SPVM_OP* SPVM_OP_new_op_array_access_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_array_access) {
  (void)compiler;
  
  SPVM_OP* op_var_array = SPVM_OP_new_op_var_clone_var_or_assign(compiler, original_op_array_access->first);
  SPVM_OP* op_var_index = SPVM_OP_new_op_var_clone_var_or_assign(compiler, original_op_array_access->last);
  
  SPVM_OP* op_array_access = SPVM_OP_build_array_access(compiler, op_var_array, op_var_index);
  
  return op_array_access;
}

SPVM_OP* SPVM_OP_new_op_array_field_access_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_array_field_access) {
  (void)compiler;
  
  SPVM_OP* op_array_field_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_FIELD_ACCESS, original_op_array_field_access->file, original_op_array_field_access->line);
  
  SPVM_OP* op_var_array = SPVM_OP_new_op_var_clone_var_or_assign(compiler, original_op_array_field_access->first);
  SPVM_OP* op_var_index = SPVM_OP_new_op_var_clone_var_or_assign(compiler, original_op_array_field_access->last);

  SPVM_OP_insert_child(compiler, op_array_field_access, op_array_field_access->last, op_var_array);
  SPVM_OP_insert_child(compiler, op_array_field_access, op_array_field_access->last, op_var_index);
  
  op_array_field_access->uv.array_field_access = original_op_array_field_access->uv.array_field_access;
  
  return op_array_field_access;
}

SPVM_OP* SPVM_OP_new_op_package_var_access_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_package_var_access) {
  (void)compiler;
  
  SPVM_OP* op_package_var_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PACKAGE_VAR_ACCESS, original_op_package_var_access->file, original_op_package_var_access->line);
  
  op_package_var_access->uv.package_var_access = original_op_package_var_access->uv.package_var_access;
  
  return op_package_var_access;
}

SPVM_OP* SPVM_OP_new_op_deref_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_deref) {
  (void)compiler;
  
  SPVM_OP* op_deref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DEREF, original_op_deref->file, original_op_deref->line);
  
  SPVM_OP* op_var = SPVM_OP_new_op_var_clone_var_or_assign(compiler, original_op_deref->first);
  
  SPVM_OP_build_deref(compiler, op_deref, op_var);
  
  return op_deref;
}

SPVM_OP* SPVM_OP_new_op_term_mutable_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_term_mutable) {
  
  SPVM_OP* op_term_mutable;
  switch (original_op_term_mutable->id) {
    case SPVM_OP_C_ID_VAR:
      op_term_mutable = SPVM_OP_new_op_var_clone(compiler, original_op_term_mutable, original_op_term_mutable->file, original_op_term_mutable->line);
      break;
    case SPVM_OP_C_ID_PACKAGE_VAR_ACCESS:
      op_term_mutable = SPVM_OP_new_op_package_var_access_clone(compiler, original_op_term_mutable);
      break;
    case SPVM_OP_C_ID_ARRAY_ACCESS:
      op_term_mutable = SPVM_OP_new_op_array_access_clone(compiler, original_op_term_mutable);
      break;
    case SPVM_OP_C_ID_FIELD_ACCESS:
      op_term_mutable = SPVM_OP_new_op_field_access_clone(compiler, original_op_term_mutable);
      break;
    case SPVM_OP_C_ID_ARRAY_FIELD_ACCESS:
      op_term_mutable = SPVM_OP_new_op_array_field_access_clone(compiler, original_op_term_mutable);
      break;
    case SPVM_OP_C_ID_DEREF:
      op_term_mutable = SPVM_OP_new_op_deref_clone(compiler, original_op_term_mutable);
      break;
    default:
      assert(0);
  }
  
  return op_term_mutable;
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

void SPVM_OP_get_before(SPVM_COMPILER* compiler, SPVM_OP* op_target, SPVM_OP** op_before_ptr, int32_t* next_is_child_ptr) {

  // Get parent
  SPVM_OP* op_parent = SPVM_OP_get_parent(compiler, op_target);
  
  SPVM_OP* op_before;
  int32_t next_is_child = 0;
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
  
  // Get parent op
  SPVM_OP* op_parent = SPVM_OP_get_parent(compiler, op_target);
  
  int32_t op_target_is_last_child = op_parent->last == op_target;

  // Get before op
  int32_t next_is_child;
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

  if (op_target_is_last_child) {
    op_parent->last = op_replace;
  }
}

// Cut op and insert stab into original position and return stab
SPVM_OP* SPVM_OP_cut_op(SPVM_COMPILER* compiler, SPVM_OP* op_target) {
  // Get parent op
  SPVM_OP* op_parent = SPVM_OP_get_parent(compiler, op_target);
  
  int32_t op_target_is_last_child = op_parent->last == op_target;

  // Get before op
  int32_t next_is_child;
  SPVM_OP* op_before;
  SPVM_OP_get_before(compiler, op_target, &op_before, &next_is_child);
  
  // Stab
  SPVM_OP* op_stab = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_STAB, op_target->file, op_target->line);
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
  
  if (op_target_is_last_child) {
    op_parent->last = op_stab;
  }
  
  return op_stab;
}

SPVM_OP* SPVM_OP_build_constant(SPVM_COMPILER* compiler, SPVM_OP* op_constant) {
  
  SPVM_CONSTANT* constant = op_constant->uv.constant;
  
  if (constant->type->dimension == 1 && constant->type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
    SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, op_constant->file, op_constant->line);
    SPVM_OP_insert_child(compiler, op_new, op_new->last, op_constant);
    return op_new;
  }
  else {
    return op_constant;
  }
}

SPVM_OP* SPVM_OP_new_op_constant_byte(SPVM_COMPILER* compiler, int8_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.bval = value;
  SPVM_OP* op_constant_type = SPVM_OP_new_op_byte_type(compiler, file, line);
  constant->type = op_constant_type->uv.type;
  
  op_constant->uv.constant = constant;

  SPVM_LIST_push(compiler->op_constants, op_constant);
  
  constant->op_constant = op_constant;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_short(SPVM_COMPILER* compiler, int16_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.sval = value;
  SPVM_OP* op_constant_type = SPVM_OP_new_op_short_type(compiler, file, line);
  constant->type = op_constant_type->uv.type;
  
  op_constant->uv.constant = constant;

  SPVM_LIST_push(compiler->op_constants, op_constant);

  constant->op_constant = op_constant;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_int(SPVM_COMPILER* compiler, int32_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.ival = value;
  SPVM_OP* op_constant_type = SPVM_OP_new_op_int_type(compiler, file, line);
  constant->type = op_constant_type->uv.type;
  
  op_constant->uv.constant = constant;

  SPVM_LIST_push(compiler->op_constants, op_constant);

  constant->op_constant = op_constant;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_long(SPVM_COMPILER* compiler, int64_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.lval = value;
  SPVM_OP* op_constant_type = SPVM_OP_new_op_long_type(compiler, file, line);
  constant->type = op_constant_type->uv.type;
  
  op_constant->uv.constant = constant;

  SPVM_LIST_push(compiler->op_constants, op_constant);

  constant->op_constant = op_constant;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_float(SPVM_COMPILER* compiler, float value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.fval = value;
  SPVM_OP* op_constant_type = SPVM_OP_new_op_float_type(compiler, file, line);
  constant->type = op_constant_type->uv.type;
  
  op_constant->uv.constant = constant;

  SPVM_LIST_push(compiler->op_constants, op_constant);

  constant->op_constant = op_constant;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_double(SPVM_COMPILER* compiler, double value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.dval = value;
  SPVM_OP* op_constant_type = SPVM_OP_new_op_double_type(compiler, file, line);
  constant->type = op_constant_type->uv.type;
  
  op_constant->uv.constant = constant;
  
  SPVM_LIST_push(compiler->op_constants, op_constant);
  
  constant->op_constant = op_constant;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_string(SPVM_COMPILER* compiler, char* string, int32_t length, const char* file, int32_t line) {

  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  constant->value.oval = string;
  SPVM_OP* op_constant_type = SPVM_OP_new_op_string_type(compiler, file, line);
  constant->type = op_constant_type->uv.type;
  constant->string_length = length;
  op_constant->uv.constant = constant;
  
  SPVM_LIST_push(compiler->op_constants, op_constant);
  
  constant->op_constant = op_constant;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_void_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_create_void_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_byte_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_create_byte_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_short_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_create_short_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_int_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_create_int_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_long_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_create_long_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_float_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_create_float_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_double_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_create_double_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_string_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_create_string_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_undef_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_create_undef_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_byte_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_create_byte_ref_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_short_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_create_short_ref_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_int_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_create_int_ref_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_long_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_create_long_ref_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_float_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_create_float_ref_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_double_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_create_double_ref_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_any_object_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_create_any_object_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_get_op_block_from_op_sub(SPVM_COMPILER* compiler, SPVM_OP* op_sub) {
  (void)compiler;
  
  SPVM_OP* op_block = op_sub->last;
  
  if (op_block->id == SPVM_OP_C_ID_BLOCK) {
    return op_block;
  }
  else {
    return NULL;
  }
}

SPVM_OP* SPVM_OP_build_eval(SPVM_COMPILER* compiler, SPVM_OP* op_eval, SPVM_OP* op_eval_block) {
  
  SPVM_OP_insert_child(compiler, op_eval, op_eval->last, op_eval_block);
  
  // eval block
  op_eval_block->uv.block->id = SPVM_BLOCK_C_ID_EVAL;
  
  return op_eval;
}

SPVM_OP* SPVM_OP_build_switch_statement(SPVM_COMPILER* compiler, SPVM_OP* op_switch, SPVM_OP* op_term_condition, SPVM_OP* op_block) {
  
  SPVM_OP* op_switch_condition = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SWITCH_CONDITION, op_term_condition->file, op_term_condition->line);
  SPVM_OP_insert_child(compiler, op_switch_condition, op_switch_condition->last, op_term_condition);
  
  SPVM_OP_insert_child(compiler, op_switch, op_switch->last, op_switch_condition);
  SPVM_OP_insert_child(compiler, op_switch, op_switch->last, op_block);
  
  op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
  
  SPVM_SWITCH_INFO* switch_info = SPVM_SWITCH_INFO_new(compiler);
  op_switch->uv.switch_info = switch_info;
  
  op_switch_condition->uv.switch_info = switch_info;
  
  return op_switch;
}

SPVM_OP* SPVM_OP_build_case_statement(SPVM_COMPILER* compiler, SPVM_OP* op_case_info, SPVM_OP* op_term) {
  
  SPVM_CASE_INFO* case_info = SPVM_CASE_INFO_new(compiler);
  
  SPVM_OP_insert_child(compiler, op_case_info, op_case_info->last, op_term);
  op_term->flag = SPVM_OP_C_FLAG_CONSTANT_CASE;
  
  case_info->op_case_info = op_case_info;
  
  op_case_info->uv.case_info = case_info;
  
  return op_case_info;
}

SPVM_OP* SPVM_OP_build_condition(SPVM_COMPILER* compiler, SPVM_OP* op_term_condition, int32_t is_not) {
  // Condition
  int32_t id;
  if (is_not) {
    id = SPVM_OP_C_ID_CONDITION_NOT;
  }
  else {
    id = SPVM_OP_C_ID_CONDITION;
  }
  SPVM_OP* op_condition = SPVM_OP_new_op(compiler, id, op_term_condition->file, op_term_condition->line);
  
  if (SPVM_OP_is_rel_op(compiler, op_term_condition)) {
    SPVM_OP_insert_child(compiler, op_condition, op_condition->last, op_term_condition);
  }
  else {
    SPVM_OP* op_bool = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BOOL, op_term_condition->file, op_term_condition->line);
    SPVM_OP_insert_child(compiler, op_bool, op_bool->last, op_term_condition);
    SPVM_OP_insert_child(compiler, op_condition, op_condition->last, op_bool);
  }
  
  return op_condition;
}

SPVM_OP* SPVM_OP_build_for_statement(SPVM_COMPILER* compiler, SPVM_OP* op_for, SPVM_OP* op_term_init, SPVM_OP* op_term_condition, SPVM_OP* op_term_increment, SPVM_OP* op_block_statements) {
  
  // Loop
  SPVM_OP* op_loop = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_LOOP, op_for->file, op_for->line);
  
  // Condition
  SPVM_OP* op_condition = SPVM_OP_build_condition(compiler, op_term_condition, 1);
  op_condition->flag |= SPVM_OP_C_FLAG_CONDITION_LOOP;
  
  // Set block flag
  op_block_statements->uv.block->id = SPVM_BLOCK_C_ID_LOOP_STATEMENTS;

  // Outer block for initialize loop variable
  SPVM_OP* op_block_init = SPVM_OP_new_op_block(compiler, op_for->file, op_for->line);
  op_block_init->uv.block->id = SPVM_BLOCK_C_ID_LOOP_INIT;
  
  // Block for increment
  SPVM_OP* op_loop_increment = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_LOOP_INCREMENT, op_for->file, op_for->line);
  SPVM_OP_insert_child(compiler, op_loop_increment, op_loop_increment->last, op_term_increment);
  
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_term_init);
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_block_statements);
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_loop_increment);
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_condition);
  
  SPVM_OP_insert_child(compiler, op_loop, op_loop->last, op_block_init);
  
  return op_loop;
}

SPVM_OP* SPVM_OP_build_while_statement(SPVM_COMPILER* compiler, SPVM_OP* op_while, SPVM_OP* op_term_condition, SPVM_OP* op_block_statements) {
  
  // Loop
  SPVM_OP* op_loop = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_LOOP, op_while->file, op_while->line);
  
  // Init statement. This is null.
  SPVM_OP* op_term_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, op_while->file, op_while->line);
  
  // Condition
  SPVM_OP* op_condition = SPVM_OP_build_condition(compiler, op_term_condition, 1);
  op_condition->flag |= SPVM_OP_C_FLAG_CONDITION_LOOP;
  
  // Set block flag
  op_block_statements->uv.block->id = SPVM_BLOCK_C_ID_LOOP_STATEMENTS;
  
  // Next value. This is null.
  SPVM_OP* op_term_increment = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, op_while->file, op_while->line);

  SPVM_OP* op_block_init = SPVM_OP_new_op_block(compiler, op_while->file, op_while->line);
  op_block_init->uv.block->id = SPVM_BLOCK_C_ID_LOOP_INIT;

  // Block for increment
  SPVM_OP* op_loop_increment = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_LOOP_INCREMENT, op_while->file, op_while->line);
  SPVM_OP_insert_child(compiler, op_loop_increment, op_loop_increment->last, op_term_increment);
  
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_term_init);
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_block_statements);
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_loop_increment);
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_condition);
  
  SPVM_OP_insert_child(compiler, op_loop, op_loop->last, op_block_init);
  
  return op_loop;
}

SPVM_OP* SPVM_OP_build_if_statement(SPVM_COMPILER* compiler, SPVM_OP* op_if, SPVM_OP* op_term_condition, SPVM_OP* op_block_true, SPVM_OP* op_block_false) {
  
  // ELSIF is same as IF
  int32_t not_condition = 0;
  
  if (op_if->id == SPVM_OP_C_ID_UNLESS) {
    op_if->id = SPVM_OP_C_ID_IF;
    not_condition = 1;
  }
  else if (op_if->id == SPVM_OP_C_ID_ELSIF) {
    op_if->id = SPVM_OP_C_ID_IF;
  }
  
  // Condition
  SPVM_OP* op_condition = SPVM_OP_build_condition(compiler, op_term_condition, not_condition);
  op_condition->flag |= SPVM_OP_C_FLAG_CONDITION_IF;

  // Create true block if needed
  if (op_block_true->id != SPVM_OP_C_ID_BLOCK) {
    SPVM_OP* op_not_block = op_block_true;
    
    op_block_true = SPVM_OP_new_op_block(compiler, op_not_block->file, op_not_block->line);
    SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, op_not_block->file, op_not_block->line);
    SPVM_OP_insert_child(compiler, op_list, op_list->last, op_not_block);
    SPVM_OP_insert_child(compiler, op_block_true, op_block_true->last, op_list);
  }
  op_block_true->uv.block->id = SPVM_BLOCK_C_ID_IF;
  
  // Create false block if needed
  if (op_block_false->id != SPVM_OP_C_ID_BLOCK) {
    SPVM_OP* op_not_block = op_block_false;
    
    // Create block
    op_block_false = SPVM_OP_new_op_block(compiler, op_not_block->file, op_not_block->line);
    SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, op_not_block->file, op_not_block->line);
    SPVM_OP_insert_child(compiler, op_list, op_list->last, op_not_block);
    SPVM_OP_insert_child(compiler, op_block_false, op_block_false->last, op_list);
  }
  op_block_false->uv.block->id = SPVM_BLOCK_C_ID_ELSE;
  
  SPVM_OP_insert_child(compiler, op_if, op_if->last, op_condition);
  SPVM_OP_insert_child(compiler, op_if, op_if->last, op_block_true);
  SPVM_OP_insert_child(compiler, op_if, op_if->last, op_block_false);
  
  return op_if;
}

SPVM_OP* SPVM_OP_build_array_length(SPVM_COMPILER* compiler, SPVM_OP* op_array_length, SPVM_OP* op_term) {
  
  SPVM_OP_insert_child(compiler, op_array_length, op_array_length->last, op_term);
  
  return op_array_length;
}

SPVM_OP* SPVM_OP_build_new(SPVM_COMPILER* compiler, SPVM_OP* op_new, SPVM_OP* op_type, SPVM_OP* op_list_elements) {
  
  SPVM_OP_insert_child(compiler, op_new, op_new->last, op_type);
  
  if (op_list_elements) {
    SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, op_list_elements->file, op_list_elements->line);
    SPVM_OP_insert_child(compiler, op_array_init, op_array_init->last, op_list_elements);
    SPVM_OP_insert_child(compiler, op_array_init, op_array_init->last, op_type);
    
    return op_array_init;
  }
  
  return op_new;
}

SPVM_OP* SPVM_OP_build_array_init(SPVM_COMPILER* compiler, SPVM_OP* op_array_init, SPVM_OP* op_list_elements) {
  
  SPVM_OP_insert_child(compiler, op_array_init, op_array_init->last, op_list_elements);
  
  return  op_array_init;
}

SPVM_OP* SPVM_OP_get_target_op_var(SPVM_COMPILER* compiler, SPVM_OP* op) {
  (void)compiler;
  
  SPVM_OP* op_var;
  if (op->id == SPVM_OP_C_ID_VAR) {
    op_var = op;
  }
  else if (op->id == SPVM_OP_C_ID_ASSIGN) {
    if (op->first->id == SPVM_OP_C_ID_VAR || op->first->id == SPVM_OP_C_ID_ASSIGN) {
      op_var = SPVM_OP_get_target_op_var(compiler, op->first);
    }
    else if (op->last->id == SPVM_OP_C_ID_VAR || op->last->id == SPVM_OP_C_ID_ASSIGN) {
      op_var = SPVM_OP_get_target_op_var(compiler, op->last);
    }
    else {
      assert(0);
    }
  }
  else if (op->id == SPVM_OP_C_ID_SEQUENCE) {
    op_var = SPVM_OP_get_target_op_var(compiler, op->last);
  }
  else if (op->id == SPVM_OP_C_ID_REF) {
    op_var = SPVM_OP_get_target_op_var(compiler, op->first);
  }
  else if (op->id == SPVM_OP_C_ID_DEREF) {
    op_var = SPVM_OP_get_target_op_var(compiler, op->first);
  }
  else {
    assert(0);
  }
  
  return op_var;
}

int32_t SPVM_OP_get_var_id(SPVM_COMPILER* compiler, SPVM_OP* op) {
  (void)compiler;
  
  SPVM_OP* op_var = SPVM_OP_get_target_op_var(compiler, op);
  
  return op_var->uv.var->my->var_id;
}

SPVM_TYPE* SPVM_OP_get_type(SPVM_COMPILER* compiler, SPVM_OP* op) {
  
  SPVM_TYPE*  type = NULL;
  
  switch (op->id) {
    case SPVM_OP_C_ID_PACKAGE: {
      SPVM_PACKAGE* package = op->uv.package;
      type = package->op_type->uv.type;
      break;
    }
    case SPVM_OP_C_ID_EQ:
    case SPVM_OP_C_ID_NE:
    case SPVM_OP_C_ID_GT:
    case SPVM_OP_C_ID_GE:
    case SPVM_OP_C_ID_LT:
    case SPVM_OP_C_ID_LE:
    case SPVM_OP_C_ID_BOOL:
    case SPVM_OP_C_ID_STRING_EQ:
    case SPVM_OP_C_ID_STRING_NE:
    case SPVM_OP_C_ID_STRING_GT:
    case SPVM_OP_C_ID_STRING_GE:
    case SPVM_OP_C_ID_STRING_LT:
    case SPVM_OP_C_ID_STRING_LE:
    case SPVM_OP_C_ID_ISA: {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, op->file, op->line);
      type = op_type->uv.type;
      break;
    }
    case SPVM_OP_C_ID_CONCAT: {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, op->file, op->line);
      type = op_type->uv.type;
      break;
    }
    case SPVM_OP_C_ID_ARRAY_LENGTH: {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, op->file, op->line);
      type = op_type->uv.type;
      break;
    }
    case SPVM_OP_C_ID_ARRAY_ACCESS: {
      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op->first);
      type = SPVM_TYPE_new(compiler);
      SPVM_BASIC_TYPE* basic_type = SPVM_HASH_fetch(compiler->basic_type_symtable, first_type->basic_type->name, strlen(first_type->basic_type->name));
      type->basic_type = basic_type;
      assert(first_type->dimension > 0);
      type->dimension = first_type->dimension - 1;
      if (first_type->flag & SPVM_TYPE_C_FLAG_CONST) {
        type->flag |= SPVM_TYPE_C_FLAG_CONST;
      }
      break;
    }
    case SPVM_OP_C_ID_ADD:
    case SPVM_OP_C_ID_SUBTRACT:
    case SPVM_OP_C_ID_MULTIPLY:
    case SPVM_OP_C_ID_DIVIDE:
    case SPVM_OP_C_ID_REMAINDER:
    case SPVM_OP_C_ID_INC:
    case SPVM_OP_C_ID_PRE_INC:
    case SPVM_OP_C_ID_POST_INC:
    case SPVM_OP_C_ID_DEC:
    case SPVM_OP_C_ID_PRE_DEC:
    case SPVM_OP_C_ID_POST_DEC:
    case SPVM_OP_C_ID_LEFT_SHIFT:
    case SPVM_OP_C_ID_RIGHT_SHIFT:
    case SPVM_OP_C_ID_RIGHT_SHIFT_UNSIGNED:
    case SPVM_OP_C_ID_BIT_XOR:
    case SPVM_OP_C_ID_BIT_OR:
    case SPVM_OP_C_ID_BIT_AND:
    case SPVM_OP_C_ID_COMPLEMENT:
    case SPVM_OP_C_ID_PLUS:
    case SPVM_OP_C_ID_NEGATE:
    case SPVM_OP_C_ID_NEW:
    case SPVM_OP_C_ID_CHECK_CAST:
    case SPVM_OP_C_ID_ARRAY_INIT:
    {
      type = SPVM_OP_get_type(compiler, op->first);
      break;
    }
    case SPVM_OP_C_ID_LIST:
    case SPVM_OP_C_ID_SEQUENCE:
      type = SPVM_OP_get_type(compiler, op->last);
      break;
    case SPVM_OP_C_ID_ASSIGN: {
      type = SPVM_OP_get_type(compiler, op->last);
      break;
    }
    case SPVM_OP_C_ID_RETURN: {
      if (op->first) {
        type = SPVM_OP_get_type(compiler, op->first);
      }
      break;
    }
    case SPVM_OP_C_ID_CONVERT: {
      SPVM_OP* op_type = op->last;
      type = SPVM_OP_get_type(compiler, op_type);
      break;
    }
    case SPVM_OP_C_ID_TYPE: {
      if (op->uv.type) {
        type = op->uv.type;
      }
      break;
    }
    case SPVM_OP_C_ID_SWITCH_CONDITION : {
      type = SPVM_OP_get_type(compiler, op->first);
      break;
    }
    case SPVM_OP_C_ID_UNDEF : {
      SPVM_OP* op_type = SPVM_OP_new_op_undef_type(compiler, op->file, op->line);
      type = op_type->uv.type;
      break;
    }
    case SPVM_OP_C_ID_CONSTANT: {
      SPVM_CONSTANT* constant = op->uv.constant;
      type = constant->type;
      break;
    }
    case SPVM_OP_C_ID_VAR: {
      SPVM_VAR* var = op->uv.var;
      type = var->my->type;
      break;
    }
    case SPVM_OP_C_ID_PACKAGE_VAR_ACCESS: {
      SPVM_PACKAGE_VAR* package_var = op->uv.package_var_access->package_var;
      if (package_var->type) {
        type = package_var->type;
      }
      break;
    }
    case SPVM_OP_C_ID_PACKAGE_VAR: {
      SPVM_PACKAGE_VAR* package_var = op->uv.package_var;
      if (package_var->type) {
        type = package_var->type;
      }
      break;
    }
    case SPVM_OP_C_ID_EXCEPTION_VAR: {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, op->file, op->line);
      type = op_type->uv.type;
      break;
    }
    case SPVM_OP_C_ID_MY: {
      
      SPVM_MY* my = op->uv.my;
      type = my->type;
      break;
    }
    case SPVM_OP_C_ID_CALL_SUB: {
      SPVM_CALL_SUB* call_sub = op->uv.call_sub;
      const char* abs_name = call_sub->sub->abs_name;
      SPVM_SUB* sub = SPVM_HASH_fetch(compiler->sub_symtable, abs_name, strlen(abs_name));
      type = sub->return_type;
      break;
    }
    case SPVM_OP_C_ID_FIELD_ACCESS: {
      SPVM_FIELD_ACCESS* field_access = op->uv.field_access;
      SPVM_FIELD* field = field_access->field;
      type = field->type;
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
    case SPVM_OP_C_ID_REF: {
      SPVM_TYPE* term_type = SPVM_OP_get_type(compiler, op->first);
      assert(term_type->dimension == 0);
      switch (term_type->basic_type->id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          SPVM_OP* op_type = SPVM_OP_new_op_byte_ref_type(compiler, op->file, op->line);
          type = op_type->uv.type;
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          SPVM_OP* op_type = SPVM_OP_new_op_short_ref_type(compiler, op->file, op->line);
          type = op_type->uv.type;
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          SPVM_OP* op_type = SPVM_OP_new_op_int_ref_type(compiler, op->file, op->line);
          type = op_type->uv.type;
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          SPVM_OP* op_type = SPVM_OP_new_op_long_ref_type(compiler, op->file, op->line);
          type = op_type->uv.type;
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          SPVM_OP* op_type = SPVM_OP_new_op_float_ref_type(compiler, op->file, op->line);
          type = op_type->uv.type;
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          SPVM_OP* op_type = SPVM_OP_new_op_double_ref_type(compiler, op->file, op->line);
          type = op_type->uv.type;
          break;
        }
        default:
          assert(SPVM_TYPE_is_value_type(compiler, term_type->basic_type->id, term_type->dimension, term_type->flag));
          type = SPVM_TYPE_new(compiler);
          type->basic_type = term_type->basic_type;
          type->dimension = term_type->dimension;
          type->flag = term_type->flag | SPVM_TYPE_C_FLAG_REF;
      }
      break;
    }
    case SPVM_OP_C_ID_DEREF: {
      SPVM_TYPE* term_type = SPVM_OP_get_type(compiler, op->first);
      assert(term_type->dimension == 0);
      switch (term_type->basic_type->id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          SPVM_OP* op_type = SPVM_OP_new_op_byte_type(compiler, op->file, op->line);
          type = op_type->uv.type;
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          SPVM_OP* op_type = SPVM_OP_new_op_short_type(compiler, op->file, op->line);
          type = op_type->uv.type;
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, op->file, op->line);
          type = op_type->uv.type;
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          SPVM_OP* op_type = SPVM_OP_new_op_long_type(compiler, op->file, op->line);
          type = op_type->uv.type;
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          SPVM_OP* op_type = SPVM_OP_new_op_float_type(compiler, op->file, op->line);
          type = op_type->uv.type;
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          SPVM_OP* op_type = SPVM_OP_new_op_double_type(compiler, op->file, op->line);
          type = op_type->uv.type;
          break;
        }
        default:
          assert(SPVM_TYPE_is_value_ref_type(compiler, term_type->basic_type->id, term_type->dimension, term_type->flag));
          type = SPVM_TYPE_new(compiler);
          type->basic_type = term_type->basic_type;
          type->dimension = term_type->dimension;
          type->flag = term_type->flag & ~SPVM_TYPE_C_FLAG_REF;
      }
      break;
    }
  }
  
  return type;
}

SPVM_OP* SPVM_OP_build_array_access(SPVM_COMPILER* compiler, SPVM_OP* op_term_array, SPVM_OP* op_term_index) {
  
  SPVM_OP* op_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_ACCESS, op_term_array->file, op_term_array->line);
  SPVM_OP_insert_child(compiler, op_array_access, op_array_access->last, op_term_array);
  SPVM_OP_insert_child(compiler, op_array_access, op_array_access->last, op_term_index);
  
  return op_array_access;
}

SPVM_OP* SPVM_OP_build_field_access(SPVM_COMPILER* compiler, SPVM_OP* op_term, SPVM_OP* op_name_field) {
  SPVM_OP* op_field_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_FIELD_ACCESS, op_term->file, op_term->line);
  SPVM_OP_insert_child(compiler, op_field_access, op_field_access->last, op_term);
  
  SPVM_FIELD_ACCESS* field_access = SPVM_FIELD_ACCESS_new(compiler);
  
  if (strchr(op_name_field->uv.name, ':')) {
    SPVM_yyerror_format(compiler, "field name \"%s\" can't contain :: at %s line %d\n",
      op_name_field, op_name_field->file, op_name_field->line);
  }
  
  field_access->op_term = op_term;
  field_access->op_name = op_name_field;
  op_field_access->uv.field_access = field_access;
  
  return op_field_access;
}

SPVM_OP* SPVM_OP_build_weaken_field(SPVM_COMPILER* compiler, SPVM_OP* op_weaken, SPVM_OP* op_field_access) {
  
  SPVM_OP* op_weaken_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_WEAKEN_FIELD, op_weaken->file, op_weaken->line);
  SPVM_OP_insert_child(compiler, op_weaken_field, op_weaken_field->last, op_field_access);
  
  op_field_access->flag |= SPVM_OP_C_FLAG_FIELD_ACCESS_WEAKEN;
  
  return op_weaken_field;
}

SPVM_OP* SPVM_OP_build_weaken_array_element(SPVM_COMPILER* compiler, SPVM_OP* op_weaken, SPVM_OP* op_array_access) {
  
  SPVM_OP* op_weaken_array_element = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_WEAKEN_ARRAY_ELEMENT, op_weaken->file, op_weaken->line);
  SPVM_OP_insert_child(compiler, op_weaken_array_element, op_weaken_array_element->last, op_array_access);
  
  op_array_access->flag |= SPVM_OP_C_FLAG_ARRAY_ACCESS_WEAKEN;
  
  return op_weaken_array_element;
}

SPVM_OP* SPVM_OP_build_convert(SPVM_COMPILER* compiler, SPVM_OP* op_convert, SPVM_OP* op_type, SPVM_OP* op_term) {
  
  SPVM_OP_insert_child(compiler, op_convert, op_convert->last, op_term);
  SPVM_OP_insert_child(compiler, op_convert, op_convert->last, op_type);
  
  op_convert->file = op_type->file;
  op_convert->line = op_type->line;
  
  return op_convert;
}

SPVM_OP* SPVM_OP_build_grammar(SPVM_COMPILER* compiler, SPVM_OP* op_packages) {
  
  SPVM_OP* op_grammar = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_GRAMMAR, op_packages->file, op_packages->line);
  SPVM_OP_insert_child(compiler, op_grammar, op_grammar->last, op_packages);

  return op_grammar;
}

const char* SPVM_OP_create_abs_name(SPVM_COMPILER* compiler, const char* package_name, const char* name) {
  int32_t length = (int32_t)(strlen(package_name) + 2 + strlen(name));
  
  char* abs_name = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, length + 1);
  
  sprintf(abs_name, "%s::%s", package_name, name);
  
  return abs_name;
}

const char* SPVM_OP_create_package_var_access_abs_name(SPVM_COMPILER* compiler, const char* package_name, const char* name) {
  int32_t length = (int32_t)(strlen(package_name) + 2 + strlen(name));
  
  char* abs_name = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, length + 1);
  
  sprintf(abs_name, "$%s::%s", package_name, &name[1]);
  
  return abs_name;
}

SPVM_OP* SPVM_OP_build_package(SPVM_COMPILER* compiler, SPVM_OP* op_package, SPVM_OP* op_type, SPVM_OP* op_block, SPVM_OP* op_list_descriptors) {

  // Package
  SPVM_PACKAGE* package = SPVM_PACKAGE_new(compiler);
  
  package->load_path = compiler->cur_file;
  
  if (!op_type) {
    // Package is anon
    package->flag |= SPVM_PACKAGE_C_FLAG_IS_ANON;
    
    // Anon package name
    char* name_package = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, strlen("anon2147483647") + 1);
    sprintf(name_package, "anon%d", compiler->anon_package_length);
    compiler->anon_package_length++;
    SPVM_OP* op_name_package = SPVM_OP_new_op_name(compiler, name_package, op_package->file, op_package->line);
    op_type = SPVM_OP_build_basic_type(compiler, op_name_package);
  }
  
  package->op_type = op_type;
  
  const char* package_name = op_type->uv.type->basic_type->name;
  
  if (!(package->flag & SPVM_PACKAGE_C_FLAG_IS_ANON) && islower(package_name[0])) {
    SPVM_yyerror_format(compiler, "Package name must start with upper case \"%s\" at %s line %d\n", package_name, op_package->file, op_package->line);
  }

  SPVM_HASH* package_symtable = compiler->package_symtable;

  // Redeclaration package error
  SPVM_PACKAGE* found_package = SPVM_HASH_fetch(package_symtable, package_name, strlen(package_name));
  if (found_package) {
    SPVM_yyerror_format(compiler, "redeclaration of package \"%s\" at %s line %d\n", package_name, op_package->file, op_package->line);
    return NULL;
  }
  
  SPVM_OP* op_name_package = SPVM_OP_new_op_name(compiler, op_type->uv.type->basic_type->name, op_type->file, op_type->line);
  package->op_name = op_name_package;
  
  package->name = op_name_package->uv.name;

  // Package is interface
  int32_t duplicate_descriptors = 0;
  if (op_list_descriptors) {
    SPVM_OP* op_descriptor = op_list_descriptors->first;
    while ((op_descriptor = SPVM_OP_sibling(compiler, op_descriptor))) {
      SPVM_DESCRIPTOR* descriptor = op_descriptor->uv.descriptor;
      switch (descriptor->id) {
        case SPVM_DESCRIPTOR_C_ID_INTERFACE:
          package->category = SPVM_PACKAGE_C_CATEGORY_INTERFACE;
          duplicate_descriptors++;
          break;
        case SPVM_DESCRIPTOR_C_ID_POINTER:
          package->category = SPVM_PACKAGE_C_CATEGORY_CLASS;
          package->flag |= SPVM_PACKAGE_C_FLAG_IS_POINTER;
          duplicate_descriptors++;
          break;
        case SPVM_DESCRIPTOR_C_ID_VALUE_T:
          package->category = SPVM_PACKAGE_C_CATEGORY_VALUE_T;
          duplicate_descriptors++;
          break;
        case SPVM_DESCRIPTOR_C_ID_PRIVATE:
          package->flag |= SPVM_PACKAGE_C_FLAG_IS_PRIVATE;
          break;
        case SPVM_DESCRIPTOR_C_ID_PUBLIC:
          break;
        default:
          SPVM_yyerror_format(compiler, "Invalid package descriptor %s at %s line %d\n", SPVM_DESCRIPTOR_C_ID_NAMES[descriptor->id], op_package->file, op_package->line);
      }
    }
    if (duplicate_descriptors > 1) {
      SPVM_yyerror_format(compiler, "Invalid descriptor combination at %s line %d\n", op_list_descriptors->file, op_list_descriptors->line);
    }
  }
  
  // Divide declarations to field, sub, enum, package variable, use
  SPVM_OP* op_decls = op_block->first;
  SPVM_OP* op_decl = op_decls->first;
  while ((op_decl = SPVM_OP_sibling(compiler, op_decl))) {
    if (op_decl->id == SPVM_OP_C_ID_FIELD) {
      if (package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE) {
        SPVM_yyerror_format(compiler, "Interface package can't have field at %s line %d\n", op_decl->file, op_decl->line);
      }
      SPVM_LIST_push(package->fields, op_decl->uv.field);
    }
    else if (op_decl->id == SPVM_OP_C_ID_SUB) {
      SPVM_LIST_push(package->subs, op_decl->uv.sub);
    }
    else if (op_decl->id == SPVM_OP_C_ID_ENUM) {
      SPVM_OP* op_enum_block = op_decl->first;
      SPVM_OP* op_enumeration_values = op_enum_block->first;
      SPVM_OP* op_sub = op_enumeration_values->first;
      while ((op_sub = SPVM_OP_sibling(compiler, op_sub))) {
        SPVM_LIST_push(package->subs, op_sub->uv.sub);
      }
    }
    else if (op_decl->id == SPVM_OP_C_ID_PACKAGE_VAR) {
      if (package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE) {
        SPVM_yyerror_format(compiler, "Interface package can't have package variable at %s line %d\n", op_decl->file, op_decl->line);
      }
      SPVM_LIST_push(package->package_vars, op_decl->uv.package_var);
    }
    else if (op_decl->id == SPVM_OP_C_ID_USE) {
      // Static import
    }
    else {
      assert(0);
    }
  }
  
  // Outer variable become field declaration
  for (int32_t i = 0; i < compiler->cur_op_fields_outer->length; i++) {
    SPVM_OP* op_field = SPVM_LIST_fetch(compiler->cur_op_fields_outer, i);
    SPVM_LIST_push(package->fields, op_field->uv.field);
  }
  compiler->cur_op_fields_outer = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  
  // Field declarations
  {
    int32_t i;
    for (i = 0; i < package->fields->length; i++) {
      if (package->flag & SPVM_PACKAGE_C_FLAG_IS_POINTER) {
        SPVM_yyerror_format(compiler, "Pointer package can't have field at %s line %d\n", op_decl->file, op_decl->line);
        continue;
      }

      SPVM_FIELD* field = SPVM_LIST_fetch(package->fields, i);
      field->index = i;
      const char* field_name = field->op_name->uv.name;
      const char* field_abs_name = SPVM_OP_create_abs_name(compiler, package_name, field_name);
      field->abs_name = field_abs_name;
      
      SPVM_FIELD* found_field = SPVM_HASH_fetch(package->field_symtable, field_name, strlen(field_name));
      
      if (found_field) {
        SPVM_yyerror_format(compiler, "Redeclaration of field \"%s::%s\" at %s line %d\n", package_name, field_name, field->op_field->file, field->op_field->line);
      }
      else if (package->fields->length >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
        SPVM_yyerror_format(compiler, "Too many field declarations at %s line %d\n", field->op_field->file, field->op_field->line);
      }
      else {
        field->id = compiler->fields->length + 1;
        field->rel_id = i;
        SPVM_LIST_push(compiler->fields, field);
        SPVM_HASH_insert(compiler->field_symtable, field_abs_name, strlen(field_abs_name), field);
        
        SPVM_HASH_insert(package->field_symtable, field_name, strlen(field_name), field);
        
        // Add op package
        field->package = package;
      }
    }
  }

  // Package variable declarations
  {
    int32_t i;
    for (i = 0; i < package->package_vars->length; i++) {
      SPVM_PACKAGE_VAR* package_var = SPVM_LIST_fetch(package->package_vars, i);
      package_var->rel_id = i;
      const char* package_var_name = package_var->op_var->uv.var->op_name->uv.name;
      const char* package_var_abs_name = SPVM_OP_create_abs_name(compiler, package_name, package_var_name);
      package_var->abs_name = package_var_abs_name;
      
      SPVM_PACKAGE_VAR* found_package_var = SPVM_HASH_fetch(package->package_var_symtable, package_var_name, strlen(package_var_name));
      
      if (found_package_var) {
        SPVM_yyerror_format(compiler, "Redeclaration of package variable \"%s::%s\" at %s line %d\n", package_name, package_var_name, package_var->op_package_var->file, package_var->op_package_var->line);
      }
      else if (package->package_vars->length >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
        SPVM_yyerror_format(compiler, "Too many package variable declarations at %s line %d\n", package_var->op_package_var->file, package_var->op_package_var->line);
        
      }
      else {
        const char* package_var_access_abs_name = SPVM_OP_create_package_var_access_abs_name(compiler, package_name, package_var_name);
        package_var->id = compiler->package_vars->length + 1;
        SPVM_LIST_push(compiler->package_vars, package_var);
        SPVM_HASH_insert(compiler->package_var_symtable, package_var_access_abs_name, strlen(package_var_access_abs_name), package_var);

        SPVM_HASH_insert(package->package_var_symtable, package_var_name, strlen(package_var_name), package_var);
        
        // Add op package
        package_var->package = package;
      }
    }
  }
  
  // Subroutine declarations
  {
    int32_t i;
    for (i = 0; i < package->subs->length; i++) {
      SPVM_SUB* sub = SPVM_LIST_fetch(package->subs, i);
      
      if (sub->flag & SPVM_SUB_C_FLAG_IS_ANON_SUB) {
        package->flag |= SPVM_PACKAGE_C_FLAG_IS_HAS_ONLY_ANON_SUB;
        assert(package->subs->length == 1);
      }

      sub->rel_id = i;
      
      SPVM_OP* op_name_sub = sub->op_name;
      const char* sub_name = op_name_sub->uv.name;
      const char* sub_abs_name = SPVM_OP_create_abs_name(compiler, package_name, sub_name);

      // Method check
      
      // Set first argument type if not set
      if (sub->args->length > 0) {
        SPVM_MY* arg_my_first = SPVM_LIST_fetch(sub->args, 0);
        SPVM_OP* op_arg_first_type = NULL;
        if (arg_my_first->type->is_self) {
          SPVM_TYPE* arg_invocant_type = SPVM_TYPE_clone_type(compiler, op_type->uv.type);
          op_arg_first_type = SPVM_OP_new_op_type(compiler, arg_invocant_type, sub->op_sub->file, sub->op_sub->line);
          arg_my_first->type = op_arg_first_type->uv.type;
          sub->call_type_id = SPVM_SUB_C_CALL_TYPE_ID_METHOD;
          assert(arg_invocant_type->basic_type);
        }
        else {
          op_arg_first_type = arg_my_first->type->op_type;
          assert(op_arg_first_type->uv.type->basic_type);
        }
      }
      
      // Subroutine in interface package must be method
      if (package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE && sub->call_type_id != SPVM_SUB_C_CALL_TYPE_ID_METHOD) {
        SPVM_yyerror_format(compiler, "Subroutine in interface package must be method at %s line %d\n", sub->op_sub->file, sub->op_sub->line);
      }
      
      // If Subroutine is anon, sub must be method
      if (strlen(sub_name) == 0 && sub->call_type_id != SPVM_SUB_C_CALL_TYPE_ID_METHOD) {
        SPVM_yyerror_format(compiler, "Anon subroutine must be method at %s line %d\n", sub->op_sub->file, sub->op_sub->line);
      }
      
      
      SPVM_SUB* found_sub = SPVM_HASH_fetch(compiler->sub_symtable, sub_abs_name, strlen(sub_abs_name));
      
      if (found_sub) {
        SPVM_yyerror_format(compiler, "Redeclaration of sub \"%s\" at %s line %d\n", sub_abs_name, sub->op_sub->file, sub->op_sub->line);
      }
      else if (package->subs->length >= SPVM_LIMIT_C_OPCODE_OPERAND_VALUE_MAX) {
        SPVM_yyerror_format(compiler, "Too many sub declarations at %s line %d\n", sub_name, sub->op_sub->file, sub->op_sub->line);
      }
      // Unknown sub
      else {
        // Bind standard functions
        sub->abs_name = sub_abs_name;
        
        sub->package = package;
        
        if (sub->flag & SPVM_SUB_C_FLAG_IS_DESTRUCTOR) {
          package->sub_destructor = sub;
        }
        
        assert(sub->op_sub->file);
        
        sub->id = compiler->subs->length + 1;
        
        SPVM_LIST_push(compiler->subs, sub);
        SPVM_HASH_insert(compiler->sub_symtable, sub_abs_name, strlen(sub_abs_name), sub);
        
        SPVM_HASH_insert(package->sub_symtable, sub->op_name->uv.name, strlen(sub->op_name->uv.name), sub);
      }
    }
  }
  
  // Interface must have only one method
  if (package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE) {
    if (package->subs->length != 1) {
      SPVM_yyerror_format(compiler, "Interface must have only one method at %s line %d\n", op_package->file, op_package->line);
    }
  }
  
  // Set package
  op_package->uv.package = package;
  
  package->op_package = op_package;
  
  // Add package
  SPVM_LIST_push(compiler->packages, package);
  SPVM_HASH_insert(compiler->package_symtable, package_name, strlen(package_name), package);

  return op_package;
}

SPVM_OP* SPVM_OP_build_use(SPVM_COMPILER* compiler, SPVM_OP* op_use, SPVM_OP* op_type) {
  
  SPVM_OP_insert_child(compiler, op_use, op_use->last, op_type);
  
  SPVM_USE* use = SPVM_USE_new(compiler);
  op_use->uv.use = use;
  use->op_type = op_type;
  
  SPVM_LIST_push(compiler->op_use_stack, op_use);
  
  return op_use;
}

SPVM_OP* SPVM_OP_build_arg(SPVM_COMPILER* compiler, SPVM_OP* op_var, SPVM_OP* op_type) {
  
  SPVM_MY* my = SPVM_MY_new(compiler);
  SPVM_OP* op_my = SPVM_OP_new_op_my(compiler, my, op_var->file, op_var->line);
  
  op_var = SPVM_OP_build_my(compiler, op_my, op_var, op_type, 0);
  
  return op_var;
}

SPVM_OP* SPVM_OP_build_my(SPVM_COMPILER* compiler, SPVM_OP* op_my, SPVM_OP* op_var, SPVM_OP* op_type, int32_t is_outer) {
  
  // Declaration
  op_var->uv.var->is_declaration = 1;
  
  // Create my var information
  SPVM_MY* my = op_my->uv.my;
  if (op_type) {
    my->type = op_type->uv.type;
  }
  
  // Name OP
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NAME, op_var->file, op_var->line);
  op_name->uv.name = op_var->uv.var->op_name->uv.name;
  my->op_name = op_name;
  
  op_var->uv.var->my = my;

  // outer variables
  op_var->uv.var->is_outer = 1;

  // Filed name OP
  SPVM_OP* op_name_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NAME, op_var->file, op_var->line);
  op_name_field->uv.name = op_var->uv.var->op_name->uv.name;
  
  // Field type op
  /*
  SPVM_OP* op_type_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_type->file, op_type->line);
  SPVM_TYPE* type_field = SPVM_TYPE_clone_type(compiler, op_type->uv.type);
  op_type_field->uv.type = type_field;
  SPVM_OP* op_has = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_FIELD, op_my->file, op_my->line);
  SPVM_OP_build_has(compiler, op_has, op_name_field, NULL, op_type_field);
  SPVM_LIST_push(compiler->cur_op_fields_outer, op_has);
  */
  
  
  return op_var;
}

SPVM_OP* SPVM_OP_build_our(SPVM_COMPILER* compiler, SPVM_OP* op_var, SPVM_OP* op_type) {
  
  SPVM_OP* op_package_var = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PACKAGE_VAR, op_var->file, op_var->line);
  SPVM_PACKAGE_VAR* package_var = SPVM_PACKAGE_VAR_new(compiler);
  
  const char* name = op_var->uv.var->op_name->uv.name;;
  
  package_var->name = op_var->uv.var->op_name->uv.name;
  
  int32_t invalid_name = 0;
  if (strchr(name, ':')) {
    invalid_name = 1;
  }
  
  if (invalid_name) {
    SPVM_yyerror_format(compiler, "Invalid package variable name %s at %s line %d\n", name, op_var->file, op_var->line);
    
  }
  
  package_var->op_var = op_var;
  package_var->type = op_type->uv.type;
  package_var->op_package_var = op_package_var;

  op_package_var->uv.package_var = package_var;
  
  return op_package_var;
}

SPVM_OP* SPVM_OP_build_has(SPVM_COMPILER* compiler, SPVM_OP* op_field, SPVM_OP* op_name_field, SPVM_OP* op_descriptors, SPVM_OP* op_type) {

  // Create field information
  SPVM_FIELD* field = SPVM_FIELD_new(compiler);
  
  // Name
  field->op_name = op_name_field;
  
  field->name = op_name_field->uv.name;
  
  // Type
  field->type = op_type->uv.type;
  
  // Set field informaiton
  op_field->uv.field = field;
  
  SPVM_OP* op_descriptor = op_descriptors->first;
  while ((op_descriptor = SPVM_OP_sibling(compiler, op_descriptor))) {
    SPVM_DESCRIPTOR* descriptor = op_descriptor->uv.descriptor;
    
    switch (descriptor->id) {
      case SPVM_DESCRIPTOR_C_ID_PRIVATE:
        field->flag |= SPVM_FIELD_C_FLAG_PRIVATE;
        break;
      case SPVM_DESCRIPTOR_C_ID_PUBLIC:
        break;
      default:
        SPVM_yyerror_format(compiler, "Invalid field descriptor %s", SPVM_DESCRIPTOR_C_ID_NAMES[descriptor->id], op_descriptors->file, op_descriptors->line);
    }
  }
  
  field->op_field = op_field;
  
  return op_field;
}

SPVM_OP* SPVM_OP_build_sub(SPVM_COMPILER* compiler, SPVM_OP* op_sub, SPVM_OP* op_name_sub, SPVM_OP* op_return_type, SPVM_OP* op_args, SPVM_OP* op_descriptors, SPVM_OP* op_block) {
  if (op_args == NULL) {
    op_args = SPVM_OP_new_op_list(compiler, op_sub->file, op_sub->line);
  }
  if (op_descriptors == NULL) {
    op_descriptors = SPVM_OP_new_op_list(compiler, op_sub->file, op_sub->line);
  }

  SPVM_SUB* sub = SPVM_SUB_new(compiler);

  if (!op_name_sub) {
    sub->flag |= SPVM_SUB_C_FLAG_IS_ANON_SUB;
    
    // Anon sub name
    char* name_sub = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, 1);
    op_name_sub = SPVM_OP_new_op_name(compiler, name_sub, op_sub->file, op_sub->line);
  }
  
  // Build OP_SUB
  SPVM_OP_insert_child(compiler, op_sub, op_sub->last, op_args);
  if (op_block) {
    op_block->uv.block->id = SPVM_BLOCK_C_ID_SUB;
    SPVM_OP_insert_child(compiler, op_sub, op_sub->last, op_block);
  }
  
  // Create sub information
  sub->op_name = op_name_sub;
  
  sub->file = op_sub->file;
  sub->line = op_sub->line;
  sub->name = sub->op_name->uv.name;
  
  // Descriptors
  SPVM_OP* op_descriptor = op_descriptors->first;
  while ((op_descriptor = SPVM_OP_sibling(compiler, op_descriptor))) {
    SPVM_DESCRIPTOR* descriptor = op_descriptor->uv.descriptor;
    
    if (descriptor->id == SPVM_DESCRIPTOR_C_ID_NATIVE) {
      sub->flag |= SPVM_SUB_C_FLAG_HAVE_NATIVE_DESC;
    }
    else if (descriptor->id == SPVM_DESCRIPTOR_C_ID_PRECOMPILE) {
      sub->flag |= SPVM_SUB_C_FLAG_HAVE_PRECOMPILE_DESC;
    }
    else {
      SPVM_yyerror_format(compiler, "invalid subroutine descriptor %s", SPVM_DESCRIPTOR_C_ID_NAMES[descriptor->id], op_descriptors->file, op_descriptors->line);
    }
  }

  if ((sub->flag & SPVM_SUB_C_FLAG_HAVE_NATIVE_DESC) && (sub->flag & SPVM_SUB_C_FLAG_HAVE_PRECOMPILE_DESC)) {
    SPVM_yyerror_format(compiler, "native and compile descriptor can't be used together", op_descriptors->file, op_descriptors->line);
  }

  // Native subroutine can't have block
  if ((sub->flag & SPVM_SUB_C_FLAG_HAVE_NATIVE_DESC) && op_block) {
    SPVM_yyerror_format(compiler, "Native subroutine can't have block", op_block->file, op_block->line);
  }
  
  // sub args
  {
    int32_t sub_index = 0;
    SPVM_OP* op_arg = op_args->first;
    while ((op_arg = SPVM_OP_sibling(compiler, op_arg))) {
      if (sub_index == 0) {
        // Call type
        SPVM_TYPE* type = op_arg->uv.var->my->type;
        if (type) {
          if (type->is_self) {
            sub->call_type_id = SPVM_SUB_C_CALL_TYPE_ID_METHOD;
          }
          else {
            sub->call_type_id = SPVM_SUB_C_CALL_TYPE_ID_CLASS_METHOD;
          }
        }
      }
      SPVM_LIST_push(sub->args, op_arg->uv.var->my);
      sub_index++;
    }
  }
  
  // Native my vars is same as arguments
  if (sub->flag & SPVM_SUB_C_FLAG_HAVE_NATIVE_DESC) {
    SPVM_OP* op_arg = op_args->first;
    while ((op_arg = SPVM_OP_sibling(compiler, op_arg))) {
      SPVM_LIST_push(sub->mys, op_arg->uv.var->my);
    }
  }

  // return type
  sub->return_type = op_return_type->uv.type;
  
  if (strcmp(sub->op_name->uv.name, "DESTROY") == 0) {
    sub->flag |= SPVM_SUB_C_FLAG_IS_DESTRUCTOR;
    
    // DESTROY return type must be void
    if (!(sub->return_type->dimension == 0 && sub->return_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_VOID)) {
      SPVM_yyerror_format(compiler, "DESTROY return type must be void\n", op_block->file, op_block->line);
    }
  }
  
  // Add variable declaration to first of block
  if (op_block) {
    SPVM_OP* op_list_statement = op_block->first;
    {
      int32_t i;
      for (i = sub->args->length - 1; i >= 0; i--) {
        SPVM_MY* arg_my = SPVM_LIST_fetch(sub->args, i);
        assert(arg_my);
        SPVM_OP* op_my = SPVM_OP_new_op_my(compiler, arg_my, arg_my->op_my->file, arg_my->op_my->line);
        SPVM_OP* op_var = SPVM_OP_new_op_var(compiler, op_my->uv.my->op_name);
        op_var->uv.var->my = arg_my;
        op_var->uv.var->is_declaration = 1;

        SPVM_OP_insert_child(compiler, op_list_statement, op_list_statement->first, op_var);
      }
    }
    
    // Add return to last of statement if need
    if (!op_list_statement->last || op_list_statement->last->id != SPVM_OP_C_ID_RETURN) {
      SPVM_OP* op_return = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_RETURN, op_list_statement->file, op_list_statement->line);
      SPVM_TYPE* return_type = sub->return_type;
      
      SPVM_OP* op_constant;
      if (return_type->dimension == 0 && return_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_VOID) {
        // Nothing
      }
      else if (return_type->dimension == 0 && return_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE) {
        op_constant = SPVM_OP_new_op_constant_byte(compiler, 0, op_list_statement->file, op_list_statement->line);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
      }
      else if (return_type->dimension == 0 && return_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_SHORT) {
        op_constant = SPVM_OP_new_op_constant_short(compiler, 0, op_list_statement->file, op_list_statement->line);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
      }
      else if (return_type->dimension == 0 && return_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
        op_constant = SPVM_OP_new_op_constant_int(compiler, 0, op_list_statement->file, op_list_statement->line);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
      }
      else if (return_type->dimension == 0 && return_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_LONG) {
        op_constant = SPVM_OP_new_op_constant_long(compiler, 0, op_list_statement->file, op_list_statement->line);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
      }
      else if (return_type->dimension == 0 && return_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_FLOAT) {
        op_constant = SPVM_OP_new_op_constant_float(compiler, 0, op_list_statement->file, op_list_statement->line);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
      }
      else if (return_type->dimension == 0 && return_type->basic_type->id == SPVM_BASIC_TYPE_C_ID_DOUBLE) {
        op_constant = SPVM_OP_new_op_constant_double(compiler, 0, op_list_statement->file, op_list_statement->line);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
      }
      else {
        // Undef
        SPVM_OP* op_undef = SPVM_OP_new_op_undef(compiler, op_list_statement->file, op_list_statement->line);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_undef);
      }
      
      SPVM_OP_insert_child(compiler, op_list_statement, op_list_statement->last, op_return);
    }
  }
  
  // Save block
  sub->op_block = op_block;
  
  sub->op_sub = op_sub;
  
  op_sub->uv.sub = sub;
  
  return op_sub;
}

SPVM_OP* SPVM_OP_build_enumeration_value(SPVM_COMPILER* compiler, SPVM_OP* op_name, SPVM_OP* op_constant) {
  
  if (op_constant) {
    
    SPVM_CONSTANT* constant = op_constant->uv.constant;
    
    if (constant->type->dimension == 0 && constant->type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
      compiler->current_enum_value = constant->value.ival;
    }
    else {
      SPVM_yyerror_format(compiler, "enum value must be int type at %s line %d\n", op_constant->file, op_constant->line);
      return NULL;
    }
    
    compiler->current_enum_value++;
  }
  else {
    op_constant = SPVM_OP_new_op_constant_int(compiler, (int32_t)compiler->current_enum_value, op_name->file, op_name->line);
    
    compiler->current_enum_value++;
  }
  
  // Return
  SPVM_OP* op_return = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_RETURN, op_name->file, op_name->line);
  SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
  
  // Statements
  SPVM_OP* op_list_statements = SPVM_OP_new_op_list(compiler, op_name->file, op_name->line);
  SPVM_OP_insert_child(compiler, op_list_statements, op_list_statements->last, op_return);

  // Block
  SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, op_name->file, op_name->line);
  SPVM_OP_insert_child(compiler, op_block, op_block->last, op_list_statements);
  
  // sub
  SPVM_OP* op_sub = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUB, op_name->file, op_name->line);
  op_sub->file = op_name->file;
  op_sub->line = op_name->line;
  
  // Type
  SPVM_OP* op_return_type = SPVM_OP_new_op_type(compiler, op_constant->uv.constant->type, op_name->file, op_name->line);
  
  // Build subroutine
  op_sub = SPVM_OP_build_sub(compiler, op_sub, op_name, op_return_type, NULL, NULL, op_block);
  
  // Set constant
  op_sub->uv.sub->op_constant = op_constant;
  
  // Subroutine is constant
  op_sub->uv.sub->flag |= SPVM_SUB_C_FLAG_IS_ENUM;
  op_sub->uv.sub->call_type_id = SPVM_SUB_C_CALL_TYPE_ID_CLASS_METHOD;
  
  return op_sub;
}

SPVM_OP* SPVM_OP_build_enumeration(SPVM_COMPILER* compiler, SPVM_OP* op_enumeration, SPVM_OP* op_enumeration_block) {
  
  // Build OP_SUB
  SPVM_OP_insert_child(compiler, op_enumeration, op_enumeration->last, op_enumeration_block);
  
  // Reset enum information
  compiler->current_enum_value = 0;
  
  return op_enumeration;
}

SPVM_OP* SPVM_OP_build_call_sub(SPVM_COMPILER* compiler, SPVM_OP* op_invocant, SPVM_OP* op_name_sub, SPVM_OP* op_list_terms) {
  
  // Build OP_SUB
  SPVM_OP* op_call_sub = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CALL_SUB, op_name_sub->file, op_name_sub->line);
  SPVM_OP_insert_child(compiler, op_call_sub, op_call_sub->last, op_name_sub);
  SPVM_OP_insert_child(compiler, op_call_sub, op_call_sub->last, op_list_terms);
  
  SPVM_CALL_SUB* call_sub = SPVM_CALL_SUB_new(compiler);
  
  const char* sub_name = op_name_sub->uv.name;
  
  if (strstr(sub_name, "::")) {
    SPVM_yyerror_format(compiler, "subroutine name can't conatin :: at %s line %d\n", op_name_sub->file, op_name_sub->line);
  }
  
  // Method call
  if (op_invocant && op_invocant->id != SPVM_OP_C_ID_TYPE) {
    call_sub->call_type_id = SPVM_SUB_C_CALL_TYPE_ID_METHOD;
    call_sub->op_invocant = op_invocant;
    call_sub->op_name = op_name_sub;
    
    SPVM_OP_insert_child(compiler, op_list_terms, op_list_terms->first, op_invocant);
  }
  // Class method call
  else {
    call_sub->call_type_id = SPVM_SUB_C_CALL_TYPE_ID_CLASS_METHOD;
    call_sub->op_invocant = op_invocant;
    call_sub->op_name = op_name_sub;
  }
  
  // term is passed to subroutine
  SPVM_OP* op_term = op_list_terms->first;
  while ((op_term = SPVM_OP_sibling(compiler, op_term))) {
    op_term->is_passed_to_sub = 1;
  }
  
  op_call_sub->uv.call_sub = call_sub;
  
  return op_call_sub;
}

SPVM_OP* SPVM_OP_build_unop(SPVM_COMPILER* compiler, SPVM_OP* op_unary, SPVM_OP* op_first) {
  
  // Build op
  SPVM_OP_insert_child(compiler, op_unary, op_unary->last, op_first);
  
  return op_unary;
}

SPVM_OP* SPVM_OP_build_incdec(SPVM_COMPILER* compiler, SPVM_OP* op_incdec, SPVM_OP* op_first) {
  
  // Build op
  SPVM_OP_insert_child(compiler, op_incdec, op_incdec->last, op_first);

  if (!SPVM_OP_is_mutable(compiler, op_first)) {
    SPVM_yyerror_format(compiler, "inc/dec target value must be mutable at %s line %d\n", op_first->file, op_first->line);
  }
  
  return op_incdec;
}

SPVM_OP* SPVM_OP_build_isa(SPVM_COMPILER* compiler, SPVM_OP* op_isa, SPVM_OP* op_term, SPVM_OP* op_type) {
  
  // Build op
  SPVM_OP_insert_child(compiler, op_isa, op_isa->last, op_term);
  SPVM_OP_insert_child(compiler, op_isa, op_isa->last, op_type);
  
  return op_isa;
}

SPVM_OP* SPVM_OP_build_binop(SPVM_COMPILER* compiler, SPVM_OP* op_bin, SPVM_OP* op_first, SPVM_OP* op_last) {
  
  // Build op
  SPVM_OP_insert_child(compiler, op_bin, op_bin->last, op_first);
  SPVM_OP_insert_child(compiler, op_bin, op_bin->last, op_last);
  
  return op_bin;
}

SPVM_OP* SPVM_OP_build_concat(SPVM_COMPILER* compiler, SPVM_OP* op_cancat_string, SPVM_OP* op_first, SPVM_OP* op_last) {
  
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
        BOOL
          1           true1
        BOOL
          0           false1
      BOOL
        0             false2
  */
  
  SPVM_OP* op_if1 = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, op_and->file, op_and->line);
  
  // Constant true
  SPVM_OP* op_bool_true = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BOOL, op_if1->file, op_if1->line);
  SPVM_OP* op_constant_true = SPVM_OP_new_op_constant_int(compiler, 1, op_if1->file, op_if1->line);
  SPVM_OP_insert_child(compiler, op_bool_true, op_bool_true->last, op_constant_true);
  
  // Constant false 1
  SPVM_OP* op_bool_false1 = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BOOL, op_if1->file, op_if1->line);
  SPVM_OP* op_constant_false1 = SPVM_OP_new_op_constant_int(compiler, 0, op_if1->file, op_if1->line);
  SPVM_OP_insert_child(compiler, op_bool_false1, op_bool_false1->last, op_constant_false1);
  
  // Constant false 2
  SPVM_OP* op_bool_false2 = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BOOL, op_if1->file, op_if1->line);
  SPVM_OP* op_constant_false2 = SPVM_OP_new_op_constant_int(compiler, 0, op_if1->file, op_if1->line);
  SPVM_OP_insert_child(compiler, op_bool_false2, op_bool_false2->last, op_constant_false2);
  
  // if2
  SPVM_OP* op_if2 = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, op_if1->file, op_if1->line);
  
  // Build if tree
  SPVM_OP_build_if_statement(compiler, op_if2, op_last, op_bool_true, op_bool_false1);
  SPVM_OP_build_if_statement(compiler, op_if1, op_first, op_if2, op_bool_false2);
  
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
  //    BOOL
  //      1     true1
  //    IF    if2
  //      last
  //      BOOL
  //        1   true2
  //      BOOL
  //        0   false
  
  SPVM_OP* op_if1 = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, op_or->file, op_or->line);
  
  // Constant true 1
  SPVM_OP* op_bool_true1 = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BOOL, op_if1->file, op_if1->line);
  SPVM_OP* op_constant_true1 = SPVM_OP_new_op_constant_int(compiler, 1, op_if1->file, op_if1->line);
  SPVM_OP_insert_child(compiler, op_bool_true1, op_bool_true1->last, op_constant_true1);
  
  // Constant true 2
  SPVM_OP* op_bool_true2 = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BOOL, op_if1->file, op_if1->line);
  SPVM_OP* op_constant_true2 = SPVM_OP_new_op_constant_int(compiler, 1, op_if1->file, op_if1->line);
  SPVM_OP_insert_child(compiler, op_bool_true2, op_bool_true2->last, op_constant_true2);
  
  // Constant false
  SPVM_OP* op_bool_false = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BOOL, op_if1->file, op_if1->line);
  SPVM_OP* op_constant_false = SPVM_OP_new_op_constant_int(compiler, 0, op_if1->file, op_if1->line);
  SPVM_OP_insert_child(compiler, op_bool_false, op_bool_false->last, op_constant_false);
  
  // if2
  SPVM_OP* op_if2 = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, op_if1->file, op_if1->line);
  
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
  //    BOOL
  //      0
  //    BOOL
  //      1
  
  SPVM_OP* op_if = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, op_not->file, op_not->line);
  
  // Constant false
  SPVM_OP* op_bool_false = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BOOL, op_if->file, op_if->line);
  SPVM_OP* op_constant_false = SPVM_OP_new_op_constant_int(compiler, 0, op_if->file, op_if->line);
  SPVM_OP_insert_child(compiler, op_bool_false, op_bool_false->last, op_constant_false);

  // Constant true
  SPVM_OP* op_bool_true = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BOOL, op_if->file, op_if->line);
  SPVM_OP* op_constant_true = SPVM_OP_new_op_constant_int(compiler, 1, op_if->file, op_if->line);
  SPVM_OP_insert_child(compiler, op_bool_true, op_bool_true->last, op_constant_true);
  
  // Build if tree
  SPVM_OP_build_if_statement(compiler, op_if, op_first, op_bool_false, op_bool_true);
  
  return op_if;
}

SPVM_OP* SPVM_OP_build_special_assign(SPVM_COMPILER* compiler, SPVM_OP* op_special_assign, SPVM_OP* op_term_dist, SPVM_OP* op_term_src) {
  
  SPVM_OP_insert_child(compiler, op_special_assign, op_special_assign->last, op_term_src);
  SPVM_OP_insert_child(compiler, op_special_assign, op_special_assign->last, op_term_dist);
  
  if (!SPVM_OP_is_mutable(compiler, op_term_dist)) {
    SPVM_yyerror_format(compiler, "special assign operator left value must be mutable at %s line %d\n", op_term_dist->file, op_term_dist->line);
  }
  
  return op_special_assign;
}

SPVM_OP* SPVM_OP_build_assign(SPVM_COMPILER* compiler, SPVM_OP* op_assign, SPVM_OP* op_term_dist, SPVM_OP* op_term_src) {
  
  // Build op
  // Exchange left and right for excecution order
  
  SPVM_OP_insert_child(compiler, op_assign, op_assign->last, op_term_src);
  SPVM_OP_insert_child(compiler, op_assign, op_assign->last, op_term_dist);
  
  op_term_dist->is_lvalue = 1;
  
  if (!SPVM_OP_is_mutable(compiler, op_term_dist)) {
    SPVM_yyerror_format(compiler, "assign operator left value must be mutable at %s line %d\n", op_term_dist->file, op_term_dist->line);
  }
  
  return op_assign;
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
    op_term =SPVM_OP_new_op_constant_string(compiler, "Error", strlen("Error"), op_croak->file, op_croak->line);;
  }
  
  // Exception variable
  SPVM_OP* op_exception_var = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_EXCEPTION_VAR, op_term->file, op_term->line);
  
  // Assign
  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_term->file, op_term->line);
  SPVM_OP_build_assign(compiler, op_assign, op_exception_var, op_term);
  
  SPVM_OP_insert_child(compiler, op_croak, op_croak->last, op_assign);
  
  return op_croak;
}

SPVM_OP* SPVM_OP_build_basic_type(SPVM_COMPILER* compiler, SPVM_OP* op_name) {
  
  const char* name = op_name->uv.name;
  
  // Type op
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, op_name->file, op_name->line);
  SPVM_OP_insert_child(compiler, op_type, op_type->last, op_name);
  
  // Add basic type
  SPVM_BASIC_TYPE* found_basic_type = SPVM_HASH_fetch(compiler->basic_type_symtable, name, strlen(name));
  if (found_basic_type) {
    type->basic_type = found_basic_type;
  }
  else {
    SPVM_BASIC_TYPE* new_basic_type = SPVM_BASIC_TYPE_new(compiler);
    new_basic_type->id = compiler->basic_types->length;
    new_basic_type->name = name;
    SPVM_LIST_push(compiler->basic_types, new_basic_type);
    SPVM_HASH_insert(compiler->basic_type_symtable, new_basic_type->name, strlen(new_basic_type->name), new_basic_type);
    type->basic_type = new_basic_type;
  }
  
  type->op_type = op_type;
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_const_array_type(SPVM_COMPILER* compiler, SPVM_OP* op_type) {
  
  SPVM_TYPE* type = op_type->uv.type;
  
  SPVM_BASIC_TYPE* basic_type = type->basic_type;
  int32_t dimension = type->dimension;
  
  if (!(basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE && dimension == 1)) {
    SPVM_yyerror_format(compiler, "const only can specify byte array at %s line %d\n", op_type->file, op_type->line);
  }
  
  type->flag |= SPVM_TYPE_C_FLAG_CONST;

  type->op_type = op_type;
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_ref_type(SPVM_COMPILER* compiler, SPVM_OP* op_type_original) {
  
  // Type
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = op_type_original->uv.type->basic_type;
  type->dimension = op_type_original->uv.type->dimension;
  type->flag |= SPVM_TYPE_C_FLAG_REF;
  
  // Type OP
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, op_type_original->file, op_type_original->line);
  SPVM_OP_insert_child(compiler, op_type, op_type->last, op_type_original);

  type->op_type = op_type;
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_array_type(SPVM_COMPILER* compiler, SPVM_OP* op_type_child, SPVM_OP* op_term_length) {
  
  // Type
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->dimension = op_type_child->uv.type->dimension + 1;
  type->basic_type = op_type_child->uv.type->basic_type;
  if (op_type_child->uv.type->flag & SPVM_TYPE_C_FLAG_CONST) {
    type->flag |= SPVM_TYPE_C_FLAG_CONST;
  }
  
  // Type OP
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, op_type_child->file, op_type_child->line);
  SPVM_OP_insert_child(compiler, op_type, op_type->last, op_type_child);
  
  if (op_term_length) {
    SPVM_OP_insert_child(compiler, op_type, op_type->last, op_term_length);
  }
  else {
    SPVM_OP* op_null = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, op_type_child->file, op_type_child->line);
    SPVM_OP_insert_child(compiler, op_type, op_type->last, op_null);
  }

  return op_type;
}

SPVM_OP* SPVM_OP_new_op_list(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  
  SPVM_OP* op_pushmark = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PUSHMARK, file, line);
  
  SPVM_OP* op_list = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_LIST, file, line);
  SPVM_OP_insert_child(compiler, op_list, op_list->last, op_pushmark);
  
  return op_list;
}


SPVM_OP* SPVM_OP_new_op(SPVM_COMPILER* compiler, int32_t id, const char* file, int32_t line) {

  SPVM_OP *op = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_OP));
  
  memset(op, 0, sizeof(SPVM_OP));
  
  op->id = id;
  
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
