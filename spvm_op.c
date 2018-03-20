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
#include "spvm_call_field.h"
#include "spvm_call_sub.h"
#include "spvm_type.h"
#include "spvm_opcode_builder.h"
#include "spvm_op_checker.h"
#include "spvm_switch_info.h"
#include "spvm_descriptor.h"
#include "spvm_compiler_allocator.h"
#include "spvm_limit.h"
#include "spvm_use.h"
#include "spvm_our.h"
#include "spvm_package_var.h"
#include "spvm_jitcode_builder.h"
#include "spvm_undef.h"
#include "spvm_block.h"


const char* const SPVM_OP_C_ID_NAMES[] = {
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
  "WEAKEN",
  "WEAKEN_FIELD",
  "SPECIAL_ASSIGN",
  "CONCAT_STRING",
  "SET",
  "GET",
  "OUR",
  "PACKAGE_VAR",
  "ARRAY_INIT",
  "BOOL",
  "LOOP_INCREMENT",
  "SELF",
  "CLASS",
};

void SPVM_OP_apply_unary_numeric_promotion(SPVM_COMPILER* compiler, SPVM_OP* op_term) {
  
  SPVM_TYPE* type = SPVM_OP_get_type(compiler, op_term);
  
  SPVM_TYPE* dist_type;
  if (type->id <= SPVM_TYPE_C_ID_INT) {
    dist_type = SPVM_TYPE_get_int_type(compiler);
  }
  else {
    return;
  }
  
  if (type->id != dist_type->id) {
    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_term);
    
    SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, op_term->file, op_term->line);
    SPVM_OP* op_dist_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_term->file, op_term->line);
    op_dist_type->uv.type = dist_type;
    SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_term);
    
    SPVM_OP_replace_op(compiler, op_stab, op_convert);
  }
}

void SPVM_OP_apply_binary_numeric_promotion(SPVM_COMPILER* compiler, SPVM_OP* op_first, SPVM_OP* op_last) {
  
  SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op_first);
  SPVM_TYPE* last_type = SPVM_OP_get_type(compiler, op_last);
  
  SPVM_TYPE* dist_type;
  if (first_type->id == SPVM_TYPE_C_ID_DOUBLE || last_type->id == SPVM_TYPE_C_ID_DOUBLE) {
    dist_type = SPVM_TYPE_get_double_type(compiler);
  }
  else if (first_type->id == SPVM_TYPE_C_ID_FLOAT || last_type->id == SPVM_TYPE_C_ID_FLOAT) {
    dist_type = SPVM_TYPE_get_float_type(compiler);
  }
  else if (first_type->id == SPVM_TYPE_C_ID_LONG || last_type->id == SPVM_TYPE_C_ID_LONG) {
    dist_type = SPVM_TYPE_get_long_type(compiler);
  }
  else {
    dist_type = SPVM_TYPE_get_int_type(compiler);
  }
  
  if (first_type->id != dist_type->id) {
    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_first);
    
    SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, op_first->file, op_first->line);
    SPVM_OP* op_dist_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_first->file, op_first->line);
    op_dist_type->uv.type = dist_type;
    SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_first);
    
    SPVM_OP_replace_op(compiler, op_stab, op_convert);
  }
  
  if (last_type->id != dist_type->id) {
    SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_last);
    
    SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, op_last->file, op_last->line);
    SPVM_OP* op_dist_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_last->file, op_last->line);
    op_dist_type->uv.type = dist_type;
    SPVM_OP_build_convert(compiler, op_convert, op_dist_type, op_last);
    SPVM_OP_replace_op(compiler, op_stab, op_convert);
  }
}

_Bool SPVM_OP_is_rel_op(SPVM_COMPILER* compiler, SPVM_OP* op) {
  (void)compiler;
  
  switch (op->id) {
    case SPVM_OP_C_ID_EQ:
    case SPVM_OP_C_ID_NE:
    case SPVM_OP_C_ID_GT:
    case SPVM_OP_C_ID_GE:
    case SPVM_OP_C_ID_LT:
    case SPVM_OP_C_ID_LE:
      return 1;
  }
  
  return 0;
}

int32_t SPVM_OP_get_my_index(SPVM_COMPILER* compiler, SPVM_OP* op_var) {
  (void)compiler;
  
  return op_var->uv.var->op_my->uv.my->index;
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
  // Package variable
  else if (isupper(var_name[1]) || strchr(var_name, ':')) {
    
    _Bool is_invalid = 0;
    int32_t length = (int32_t)strlen(var_name);
    
    // only allow two colon
    {
      int32_t i = 0;
      while (1) {
        if (i < length) {
          if (var_name[i] == ':') {
            if (var_name[i + 1] != ':') {
              is_invalid = 1;
              break;
            }
            else {
              if (!isalpha(var_name[i + 2])) {
                is_invalid = 1;
                break;
              }
              else {
                i += 2;
                continue;
              }
            }
          }
        }
        else {
          break;
        }
        i++;
      }
    }
    
    if (is_invalid) {
      fprintf(stderr, "Invalid package variable name %s at %s line %" PRId32 "\n", var_name, compiler->cur_file, compiler->cur_line);
      exit(EXIT_FAILURE);
    }
    
    // Var OP
    SPVM_OP* op_package_var = SPVM_OP_new_op_package_var(compiler, op_var_name);
    
    op_var_ret = op_package_var;
  }
  // Lexical variable
  else {
    // Var OP
    SPVM_OP* op_var = SPVM_OP_new_op_var(compiler, op_var_name);
    op_var_ret = op_var;
  }
  
  return op_var_ret;
}

void SPVM_OP_resolve_package_var(SPVM_COMPILER* compiler, SPVM_OP* op_package_var, SPVM_OP* op_package) {
  
  SPVM_OP* op_name = op_package_var->uv.package_var->op_name;
  
  const char* name = op_name->uv.name;
  const char* abs_name;
  if (strchr(name, ':')) {
    abs_name = name;
  }
  else {
    abs_name = SPVM_OP_create_package_var_abs_name(compiler, op_package->uv.package->op_name->uv.name, name);
  }
  
  SPVM_OP* op_our = SPVM_HASH_search(compiler->op_our_symtable, abs_name, strlen(abs_name));
  
  if (op_our) {
    op_package_var->uv.package_var->op_our = op_our;
  }
}

SPVM_OP* SPVM_OP_new_op_undef(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_OP* op_undef = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_UNDEF, file, line);
  
  SPVM_UNDEF* undef = SPVM_UNDEF_new(compiler);
  op_undef->uv.undef = undef;
  
  return op_undef;
}

SPVM_OP* SPVM_OP_new_op_block(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_OP* op_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BLOCK, file, line);
  
  SPVM_BLOCK* block = SPVM_BLOCK_new(compiler);
  op_block->uv.block = block;
  
  return op_block;
}

SPVM_OP* SPVM_OP_new_op_package_var(SPVM_COMPILER* compiler, SPVM_OP* op_name) {
  SPVM_OP* op_package_var = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PACKAGE_VAR, op_name->file, op_name->line);

  SPVM_PACKAGE_VAR* package_var = SPVM_PACKAGE_VAR_new(compiler);
  package_var->op_name = op_name;
  op_package_var->uv.package_var = package_var;
  
  return op_package_var;
}

SPVM_OP* SPVM_OP_clone_op_type(SPVM_COMPILER* compiler, SPVM_OP* op_type) {
  
  SPVM_OP* op_type_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_type->file, op_type->line);
  
  op_type_new->uv.type = op_type->uv.type;
  
  // Add types
  SPVM_LIST_push(compiler->op_types, op_type_new);
  
  return op_type_new;
}

SPVM_OP* SPVM_OP_new_op_var_tmp(SPVM_COMPILER* compiler, const char* file, int32_t line) {

  // Temparary variable name
  char* name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, strlen("@@tmp2147483647"));
  sprintf(name, "@@tmp%d", compiler->tmp_var_index++);
  SPVM_OP* op_name = SPVM_OP_new_op_name(compiler, name, file, line);
  
  SPVM_OP* op_var_tmp = SPVM_OP_new_op_var(compiler, op_name);
  
  return op_var_tmp;
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
  
  // Get parent op
  SPVM_OP* op_parent = SPVM_OP_get_parent(compiler, op_target);
  
  _Bool op_target_is_last_child = op_parent->last == op_target;

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

  if (op_target_is_last_child) {
    op_parent->last = op_replace;
  }
}

// Cut op and insert stab into original position and return stab
SPVM_OP* SPVM_OP_cut_op(SPVM_COMPILER* compiler, SPVM_OP* op_target) {
  // Get parent op
  SPVM_OP* op_parent = SPVM_OP_get_parent(compiler, op_target);
  
  _Bool op_target_is_last_child = op_parent->last == op_target;

  // Get before op
  _Bool next_is_child;
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
  
  if (constant->type->id == SPVM_TYPE_C_ID_STRING) {
    SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, op_constant->file, op_constant->line);
    SPVM_OP_insert_child(compiler, op_new, op_new->last, op_constant);
    return op_new;
  }
  else {
    return op_constant;
  }
}

SPVM_OP* SPVM_OP_new_op_use_from_package_name(SPVM_COMPILER* compiler, const char* package_name, const char* file, int32_t line) {

  SPVM_OP* op_name_package = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NAME, file, line);
  op_name_package->uv.name = package_name;
  SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, file, line);
  SPVM_USE* use = SPVM_USE_new(compiler);
  use->package_name = package_name;
  use->package_name_with_template_args = package_name;
  op_use->uv.use = use;
  SPVM_OP_insert_child(compiler, op_use, op_use->last, op_name_package);
  
  return op_use;
}

SPVM_OP* SPVM_OP_new_op_constant_byte(SPVM_COMPILER* compiler, int8_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.byte_value = value;
  constant->type = SPVM_TYPE_get_byte_type(compiler);
  
  op_constant->uv.constant = constant;

  SPVM_LIST_push(compiler->op_constants, op_constant);
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_short(SPVM_COMPILER* compiler, int16_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.short_value = value;
  constant->type = SPVM_TYPE_get_short_type(compiler);
  
  op_constant->uv.constant = constant;

  SPVM_LIST_push(compiler->op_constants, op_constant);

  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_int(SPVM_COMPILER* compiler, int32_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.int_value = value;
  constant->type = SPVM_TYPE_get_int_type(compiler);
  
  op_constant->uv.constant = constant;

  SPVM_LIST_push(compiler->op_constants, op_constant);

  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_long(SPVM_COMPILER* compiler, int64_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.long_value = value;
  constant->type = SPVM_TYPE_get_long_type(compiler);
  
  op_constant->uv.constant = constant;

  SPVM_LIST_push(compiler->op_constants, op_constant);

  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_float(SPVM_COMPILER* compiler, float value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.float_value = value;
  constant->type = SPVM_TYPE_get_float_type(compiler);
  
  op_constant->uv.constant = constant;

  SPVM_LIST_push(compiler->op_constants, op_constant);

  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_double(SPVM_COMPILER* compiler, double value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.double_value = value;
  constant->type = SPVM_TYPE_get_double_type(compiler);
  
  op_constant->uv.constant = constant;
  
  SPVM_LIST_push(compiler->op_constants, op_constant);
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_string(SPVM_COMPILER* compiler, char* string, int32_t length, const char* file, int32_t line) {

  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  constant->value.string_value = string;
  constant->type = SPVM_TYPE_get_string_type(compiler);
  constant->string_length = length;
  op_constant->uv.constant = constant;
  
  SPVM_LIST_push(compiler->op_constants, op_constant);
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_var_from_op_my(SPVM_COMPILER* compiler, SPVM_OP* op_my) {
  (void)compiler;
  
  SPVM_VAR* var = SPVM_VAR_new(compiler);
  SPVM_OP* op_var = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_VAR, op_my->file, op_my->line);
  
  SPVM_MY* my = op_my->uv.my;
  
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NAME, op_my->file, op_my->line);
  op_name->uv.name = my->op_name->uv.name;
  var->op_name = op_name;
  var->op_my = op_my;
  op_var->uv.var = var;
  
  SPVM_OP_insert_child(compiler, op_var, op_var->last, op_my);
  
  return op_var;
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

SPVM_OP* SPVM_OP_build_case_statement(SPVM_COMPILER* compiler, SPVM_OP* op_case, SPVM_OP* op_term) {
  
  SPVM_OP_insert_child(compiler, op_case, op_case->last, op_term);
  
  op_term->flag = SPVM_OP_C_FLAG_CONSTANT_CASE;
  
  return op_case;
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

SPVM_OP* SPVM_OP_build_for_statement(SPVM_COMPILER* compiler, SPVM_OP* op_for, SPVM_OP* op_statement_init, SPVM_OP* op_term_condition, SPVM_OP* op_term_increment, SPVM_OP* op_block_statements) {
  
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
  
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_statement_init);
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
  SPVM_OP* op_statement_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, op_while->file, op_while->line);
  
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
  
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_statement_init);
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_block_statements);
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_loop_increment);
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_condition);
  
  SPVM_OP_insert_child(compiler, op_loop, op_loop->last, op_block_init);
  
  return op_loop;
}

SPVM_OP* SPVM_OP_build_if_statement(SPVM_COMPILER* compiler, SPVM_OP* op_if, SPVM_OP* op_term_condition, SPVM_OP* op_block_true, SPVM_OP* op_block_false) {
  
  // ELSIF is same as IF
  if (op_if->id == SPVM_OP_C_ID_ELSIF) {
    op_if->id = SPVM_OP_C_ID_IF;
  }
  
  // Condition
  SPVM_OP* op_condition = SPVM_OP_build_condition(compiler, op_term_condition, 0);
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

SPVM_OP* SPVM_OP_build_new_object(SPVM_COMPILER* compiler, SPVM_OP* op_new, SPVM_OP* op_type, SPVM_OP* op_list_elements) {
  
  SPVM_OP_insert_child(compiler, op_new, op_new->last, op_type);
  
  // Array initialization
  if (op_list_elements) {
    // NEW
    //   TYPE
    //   ARRAY_INIT
    //     LIST_INDEXES
    //     LIST_ELEMENTS
    
    // Add elmenets length to op_type
    int32_t length = 0;
    {
      SPVM_OP* op_term_element = op_list_elements->first;
      while ((op_term_element = SPVM_OP_sibling(compiler, op_term_element))) {
        length++;
      }
    }
    SPVM_OP* op_constant_length = SPVM_OP_new_op_constant_int(compiler, length, op_list_elements->file, op_list_elements->line);
    SPVM_OP_insert_child(compiler, op_type, op_type->last, op_constant_length);
    
    // ARRAY_INIT
    SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, op_list_elements->file, op_list_elements->line);
    
    // Indexes
    SPVM_OP* op_list_indexes = SPVM_OP_new_op_list(compiler, op_list_elements->file, op_list_elements->line);
    {
      int32_t index = 0;
      SPVM_OP* op_term_element = op_list_elements->first;
      while ((op_term_element = SPVM_OP_sibling(compiler, op_term_element))) {
        SPVM_OP* op_constant_index = SPVM_OP_new_op_constant_int(compiler, index, op_list_elements->file, op_list_elements->line);
        SPVM_OP_insert_child(compiler, op_list_indexes, op_list_indexes->last, op_constant_index);
        index++;
      }
    }
    
    SPVM_OP_insert_child(compiler, op_array_init, op_array_init->last, op_list_indexes);
    SPVM_OP_insert_child(compiler, op_array_init, op_array_init->last, op_list_elements);
    
    SPVM_OP_insert_child(compiler, op_new, op_new->last, op_array_init);
  }
  
  return op_new;
}

SPVM_TYPE* SPVM_OP_get_type(SPVM_COMPILER* compiler, SPVM_OP* op) {
  
  SPVM_TYPE*  type = NULL;
  
  switch (op->id) {
    case SPVM_OP_C_ID_EQ:
    case SPVM_OP_C_ID_NE:
    case SPVM_OP_C_ID_GT:
    case SPVM_OP_C_ID_GE:
    case SPVM_OP_C_ID_LT:
    case SPVM_OP_C_ID_LE:
    case SPVM_OP_C_ID_BOOL:
      type = SPVM_TYPE_get_int_type(compiler);
      break;
    case SPVM_OP_C_ID_CONCAT_STRING:
      type = SPVM_TYPE_get_string_type(compiler);
      break;
    case SPVM_OP_C_ID_ARRAY_LENGTH:
      type = SPVM_TYPE_get_int_type(compiler);
      break;
    case SPVM_OP_C_ID_ARRAY_ELEM: {
      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op->first);
      if (strcmp(first_type->name, "string") == 0) {
        type = SPVM_HASH_search(compiler->type_symtable, "byte", strlen("byte"));
      }
      else {
        type = SPVM_HASH_search(compiler->type_symtable, first_type->name, strlen(first_type->name) - 2);
      }
      break;
    }
    case SPVM_OP_C_ID_ADD:
    case SPVM_OP_C_ID_SUBTRACT:
    case SPVM_OP_C_ID_MULTIPLY:
    case SPVM_OP_C_ID_DIVIDE:
    case SPVM_OP_C_ID_REMAINDER:
    case SPVM_OP_C_ID_PRE_INC:
    case SPVM_OP_C_ID_POST_INC:
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
    {
      type = SPVM_OP_get_type(compiler, op->first);
      break;
    }
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
      if (op->uv.undef->type) {
        type = op->uv.undef->type;
      }
      else {
        type = NULL;
      }
      break;
    }
    case SPVM_OP_C_ID_CONSTANT: {
      SPVM_CONSTANT* constant = op->uv.constant;
      type = constant->type;
      break;
    }
    case SPVM_OP_C_ID_VAR: {
      SPVM_VAR* var = op->uv.var;
      if (var->op_my->uv.my->op_type) {
        type = var->op_my->uv.my->op_type->uv.type;
      }
      break;
    }
    case SPVM_OP_C_ID_PACKAGE_VAR: {
      SPVM_OUR* our = op->uv.package_var->op_our->uv.our;
      if (our->op_type) {
        type = our->op_type->uv.type;
      }
      break;
    }
    case SPVM_OP_C_ID_EXCEPTION_VAR: {
      type = SPVM_TYPE_get_string_type(compiler);
      break;
    }
    case SPVM_OP_C_ID_MY: {
      
      SPVM_MY* my = op->uv.my;
      if ( my->op_type) {
        type = my->op_type->uv.type;
      }
      break;
    }
    case SPVM_OP_C_ID_CALL_SUB: {
      SPVM_CALL_SUB* call_sub = op->uv.call_sub;
      const char* abs_name = call_sub->sub->abs_name;
      SPVM_OP* op_sub = SPVM_HASH_search(compiler->op_sub_symtable, abs_name, strlen(abs_name));
      SPVM_SUB* sub = op_sub->uv.sub;
      type = sub->op_return_type->uv.type;
      break;
    }
    case SPVM_OP_C_ID_CALL_FIELD: {
      SPVM_CALL_FIELD* call_field = op->uv.call_field;
      SPVM_FIELD* field = call_field->field;
      type = field->op_type->uv.type;
      break;
    }
    case SPVM_OP_C_ID_FIELD: {
      SPVM_FIELD* field = op->uv.field;
      type = field->op_type->uv.type;
      break;
    }
  }
  
  return type;
}

void SPVM_OP_resolve_call_sub(SPVM_COMPILER* compiler, SPVM_OP* op_call_sub, SPVM_OP* op_package_current) {
  
  SPVM_CALL_SUB* call_sub = op_call_sub->uv.call_sub;
  
  if (call_sub->sub) {
    return;
  }
  
  SPVM_OP* found_op_sub;
  
  if (call_sub->call_type_id == SPVM_SUB_C_CALL_TYPE_ID_CLASS_METHOD) {
    const char* package_name = call_sub->op_name_package->uv.name;
    const char* sub_name = call_sub->op_name->uv.name;
    
    const char* sub_abs_name = SPVM_OP_create_abs_name(compiler, package_name, sub_name);
    
    found_op_sub= SPVM_HASH_search(
      compiler->op_sub_symtable,
      sub_abs_name,
      strlen(sub_abs_name)
    );
  }
  else if (call_sub->call_type_id == SPVM_SUB_C_CALL_TYPE_ID_METHOD) {
    SPVM_TYPE* type = SPVM_OP_get_type(compiler, call_sub->op_term);
    const char* type_name = type->name;
    const char* sub_name = call_sub->op_name->uv.name;
    const char* sub_abs_name = SPVM_OP_create_abs_name(compiler, type_name, sub_name);
    
    found_op_sub= SPVM_HASH_search(
      compiler->op_sub_symtable,
      sub_abs_name,
      strlen(sub_abs_name)
    );
  }
  else if (call_sub->call_type_id == SPVM_SUB_C_CALL_TYPE_ID_SUB) {
    const char* sub_name = call_sub->op_name->uv.name;
    
    if (strstr(sub_name, "::")) {
      const char* sub_abs_name = call_sub->op_name->uv.name;
      
      found_op_sub= SPVM_HASH_search(
        compiler->op_sub_symtable,
        sub_abs_name,
        strlen(sub_abs_name)
      );
    }
    else {
      // Search current pacakge
      SPVM_PACKAGE* package = op_package_current->uv.package;
      const char* package_name = package->op_name->uv.name;
      const char* sub_abs_name = SPVM_OP_create_abs_name(compiler, package_name, sub_name);
      found_op_sub= SPVM_HASH_search(
        compiler->op_sub_symtable,
        sub_abs_name,
        strlen(sub_abs_name)
      );
      
      // Search CORE
      if (!found_op_sub) {
        sub_abs_name = SPVM_OP_create_abs_name(compiler, "CORE", sub_name);
        
        found_op_sub= SPVM_HASH_search(
          compiler->op_sub_symtable,
          sub_abs_name,
          strlen(sub_abs_name)
        );
      }
    }
  }
  else {
    assert(0);
  }
  
  if (found_op_sub) {
    call_sub->sub = found_op_sub->uv.sub;
  }
}

void SPVM_OP_resolve_call_field(SPVM_COMPILER* compiler, SPVM_OP* op_call_field) {

  SPVM_CALL_FIELD* call_field = op_call_field->uv.call_field;

  if (call_field->field) {
    return;
  }

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
  
  SPVM_OP* op_array_elem = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_ELEM, op_var->file, op_var->line);
  SPVM_OP_insert_child(compiler, op_array_elem, op_array_elem->last, op_var);
  SPVM_OP_insert_child(compiler, op_array_elem, op_array_elem->last, op_term);
  
  return op_array_elem;
}

SPVM_OP* SPVM_OP_build_call_field(SPVM_COMPILER* compiler, SPVM_OP* op_term, SPVM_OP* op_name_field) {
  SPVM_OP* op_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CALL_FIELD, op_term->file, op_term->line);
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
  
  SPVM_OP* op_weaken_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_WEAKEN_FIELD, op_weaken->file, op_weaken->line);
  SPVM_OP_insert_child(compiler, op_weaken_field, op_weaken_field->last, op_call_field);
  
  op_call_field->flag |= SPVM_OP_C_FLAG_CALL_FIELD_WEAKEN;
  
  return op_weaken_field;
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
  
  compiler->op_grammar = op_grammar;
  
  // Check syntax and data validity
  SPVM_OP_CHECKER_check(compiler);
  
  if (compiler->fatal_error) {
    return NULL;
  }
  
  if (compiler->fatal_error) {
    return NULL;
  }
  
  // Create bytecodes
  if (compiler->error_count > 0) {
    return NULL;
  }
  
  return op_grammar;
}

const char* SPVM_OP_create_abs_name(SPVM_COMPILER* compiler, const char* package_name, const char* name) {
  int32_t length = (int32_t)(strlen(package_name) + 2 + strlen(name));
  
  char* abs_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, length);
  
  sprintf(abs_name, "%s::%s", package_name, name);
  
  return abs_name;
}

const char* SPVM_OP_create_package_var_abs_name(SPVM_COMPILER* compiler, const char* package_name, const char* name) {
  int32_t length = (int32_t)(strlen(package_name) + 2 + strlen(name));
  
  char* abs_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, length);
  
  sprintf(abs_name, "$%s::%s", package_name, &name[1]);
  
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
    SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_name_package->file, op_name_package->line);
    op_type->uv.type = type;
    
    // Add type
    package->op_type = op_type;
    SPVM_LIST_push(compiler->op_types, op_type);
    
    SPVM_LIST* op_fields = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
    SPVM_LIST* op_subs = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
    SPVM_LIST* op_ours = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
    
    SPVM_LIST* op_names_set_field = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
    SPVM_LIST* op_names_get_field = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
    
    SPVM_OP* op_decls = op_block->first;
    SPVM_OP* op_decl = op_decls->first;
    while ((op_decl = SPVM_OP_sibling(compiler, op_decl))) {
      if (op_decl->id == SPVM_OP_C_ID_FIELD) {
        SPVM_LIST_push(op_fields, op_decl);
      }
      else if (op_decl->id == SPVM_OP_C_ID_SUB) {
        SPVM_LIST_push(op_subs, op_decl);
      }
      else if (op_decl->id == SPVM_OP_C_ID_ENUM) {
        SPVM_OP* op_enum_block = op_decl->first;
        SPVM_OP* op_enumeration_values = op_enum_block->first;
        SPVM_OP* op_sub = op_enumeration_values->first;
        while ((op_sub = SPVM_OP_sibling(compiler, op_sub))) {
          SPVM_LIST_push(op_subs, op_sub);
        }
      }
      else if (op_decl->id == SPVM_OP_C_ID_SET) {
        SPVM_OP* op_list = op_decl->first;
        SPVM_OP* op_name = op_list->first;
        while ((op_name = SPVM_OP_sibling(compiler, op_name))) {
          SPVM_LIST_push(op_names_set_field, op_name);
        }
      }
      else if (op_decl->id == SPVM_OP_C_ID_GET) {
        SPVM_OP* op_list = op_decl->first;
        SPVM_OP* op_name = op_list->first;
        while ((op_name = SPVM_OP_sibling(compiler, op_name))) {
          SPVM_LIST_push(op_names_get_field, op_name);
        }
      }
      else if (op_decl->id == SPVM_OP_C_ID_OUR) {
        SPVM_LIST_push(op_ours, op_decl);
      }
      else {
        assert(0);
      }
    }
    
    // Register field
    {
      int32_t i;
      for (i = 0; i < op_fields->length; i++) {
        SPVM_OP* op_field = SPVM_LIST_fetch(op_fields, i);
        
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

    // Register package variable
    {
      int32_t i;
      for (i = 0; i < op_ours->length; i++) {

        SPVM_OP* op_our = SPVM_LIST_fetch(op_ours, i);
        
        SPVM_OUR* our = op_our->uv.our;
        const char* package_var_name = our->op_package_var->uv.package_var->op_name->uv.name;
        
        SPVM_OP* found_op_our = SPVM_HASH_search(package->op_our_symtable, package_var_name, strlen(package_var_name));
        
        assert(op_ours->length <= SPVM_LIMIT_C_OURS);
        
        if (found_op_our) {
          SPVM_yyerror_format(compiler, "Redeclaration of our \"%s::%s\" at %s line %d\n", package_name, package_var_name, op_our->file, op_our->line);
        }
        else if (op_ours->length == SPVM_LIMIT_C_OURS) {
          SPVM_yyerror_format(compiler, "Too many ours, our \"%s\" ignored at %s line %d\n", package_var_name, op_our->file, op_our->line);
          compiler->fatal_error = 1;
        }
        else {
          SPVM_HASH_insert(package->op_our_symtable, package_var_name, strlen(package_var_name), op_our);
          
          const char* package_var_name_abs = SPVM_OP_create_package_var_abs_name(compiler, package_name, package_var_name);
          SPVM_HASH_insert(compiler->op_our_symtable, package_var_name_abs, strlen(package_var_name_abs), op_our);
          
          compiler->package_var_length++;
          our->id = compiler->package_var_length;
          
          // Add op package
          our->op_package = op_package;
        }
      }
    }
    
    // Add package load path
    const char* package_load_path = SPVM_HASH_search(compiler->package_load_path_symtable, package_name, strlen(package_name));
    package->load_path = (char*)package_load_path;
    
    // Add package
    op_package->uv.package = package;
    
    // Register subrotuine
    {
      int32_t i;
      for (i = 0; i < op_subs->length; i++) {
        SPVM_OP* op_sub = SPVM_LIST_fetch(op_subs, i);

        SPVM_SUB* sub = op_sub->uv.sub;

        SPVM_OP* op_name_sub = sub->op_name;
        const char* sub_name = op_name_sub->uv.name;
        const char* sub_abs_name = SPVM_OP_create_abs_name(compiler, package_name, sub_name);
        
        // Method check
        // Set first argument type if not set
        if (sub->op_args->length > 0) {
          SPVM_OP* op_arg_first = SPVM_LIST_fetch(sub->op_args, 0);
          SPVM_OP* op_arg_first_type = NULL;
          if (op_arg_first->uv.my->op_type) {
            if (op_arg_first->uv.my->op_type->id == SPVM_OP_C_ID_SELF) {
              op_arg_first_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_sub->file, op_sub->line);
              op_arg_first_type->uv.type = package->op_type->uv.type;
              op_arg_first->uv.my->op_type = op_arg_first_type;
              sub->call_type_id = SPVM_SUB_C_CALL_TYPE_ID_METHOD;
            }
            else {
              op_arg_first_type = op_arg_first->uv.my->op_type;
            }
          }
          else {
            op_arg_first_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_sub->file, op_sub->line);
            op_arg_first_type->uv.type = package->op_type->uv.type;
            op_arg_first->uv.my->op_type = op_arg_first_type;
          }
          if (op_arg_first->uv.my->op_type) {
            SPVM_LIST_push(compiler->op_types, op_arg_first->uv.my->op_type);
          }
        }
        
        SPVM_OP* found_op_sub = SPVM_HASH_search(compiler->op_sub_symtable, sub_abs_name, strlen(sub_abs_name));
        
        if (found_op_sub) {
          SPVM_yyerror_format(compiler, "Redeclaration of sub \"%s\" at %s line %d\n", sub_abs_name, op_sub->file, op_sub->line);
        }
        else if (op_subs->length == SPVM_LIMIT_C_SUBS) {
          SPVM_yyerror_format(compiler, "Too many subroutines at %s line %d\n", sub_name, op_sub->file, op_sub->line);
          compiler->fatal_error = 1;
        }
        // Unknown sub
        else {
          // Bind standard functions
          sub->abs_name = sub_abs_name;
          
          sub->op_package = op_package;
          
          if (sub->is_destructor) {
            package->op_sub_destructor = op_sub;
          }
          
          assert(op_sub->file);
          
          sub->file_name = op_sub->file;
          
          SPVM_LIST_push(compiler->op_subs, op_sub);
          SPVM_HASH_insert(compiler->op_sub_symtable, sub_abs_name, strlen(sub_abs_name), op_sub);
        }
      }
    }
    
    // Add op fields
    package->op_fields = op_fields;
    package->op_subs = op_subs;
    
    package->id = compiler->op_packages->length;
    SPVM_LIST_push(compiler->op_packages, op_package);
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
  
  SPVM_LIST* part_names = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  
  const char* found_ptr = package_name_with_template_args;
  const char* base_ptr = package_name_with_template_args;
  
  while (1) {
    found_ptr = strchr(base_ptr, '_');
    if (found_ptr) {
      int32_t length = (int32_t)(found_ptr - base_ptr);
      char* part_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, length);
      memcpy(part_name, base_ptr, length);
      part_name[length] = '\0';
      SPVM_LIST_push(part_names, part_name);
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
    SPVM_LIST_push(part_names, part_name);
  }
  
  const char* package_name = SPVM_LIST_fetch(part_names, 0);
  use->package_name = package_name;
  if (part_names->length > 1) {
    int32_t i;
    for (i = 1; i < part_names->length; i++) {
      char* part_name = SPVM_LIST_fetch(part_names, i);
      SPVM_LIST_push(use->template_args, part_name);
    }
  }
  
  SPVM_OP* found_op_use = SPVM_HASH_search(compiler->op_use_symtable, package_name_with_template_args, strlen(package_name));
  
  if (!found_op_use) {
    SPVM_LIST_push(compiler->op_use_stack, op_use);
    SPVM_HASH_insert(compiler->op_use_symtable, package_name_with_template_args, strlen(package_name), op_use);
  }
  
  return op_use;
}

SPVM_OP* SPVM_OP_build_arg(SPVM_COMPILER* compiler, SPVM_OP* op_var, SPVM_OP* op_type) {
  
  op_var = SPVM_OP_build_my(compiler, op_var, op_type);
  
  // Variable declaration is argument
  if (op_var->first) {
    op_var->first->uv.my->is_arg = 1;
  }
  
  return op_var;
}

SPVM_OP* SPVM_OP_build_my(SPVM_COMPILER* compiler, SPVM_OP* op_var, SPVM_OP* op_type) {
  
  if (op_var->id == SPVM_OP_C_ID_VAR) {
    SPVM_OP* op_my = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MY, op_var->file, op_var->line);
    
    // Create my var information
    SPVM_MY* my = SPVM_MY_new(compiler);
    if (op_type) {
      my->op_type = op_type;
    }
    
    // Name OP
    SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NAME, op_var->file, op_var->line);
    op_name->uv.name = op_var->uv.var->op_name->uv.name;
    my->op_name = op_name;

    // Add my information to op
    op_my->uv.my = my;
    
    op_var->uv.var->op_my = op_my;
    
    SPVM_OP_insert_child(compiler, op_var, op_var->last, op_my);
    
    assert(op_var->first);
  }
  else {
    const char* name = SPVM_OP_get_var_name(compiler, op_var);
    SPVM_yyerror_format(compiler, "Invalid lexical variable name %s at %s line %d\n", name, op_var->file, op_var->line);
    compiler->fatal_error = 1;
  }
  
  return op_var;
}

SPVM_OP* SPVM_OP_build_our(SPVM_COMPILER* compiler, SPVM_OP* op_package_var, SPVM_OP* op_type) {
  
  SPVM_OP* op_our = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_OUR, op_package_var->file, op_package_var->line);
  SPVM_OUR* our = SPVM_OUR_new(compiler);
  
  const char* name = SPVM_OP_get_var_name(compiler, op_package_var);
  
  _Bool invalid_name = 0;
  if (op_package_var->id != SPVM_OP_C_ID_PACKAGE_VAR) {
    invalid_name = 1;
  }
  else {
    if (strchr(name, ':')) {
      invalid_name = 1;
    }
  }
  
  if (invalid_name) {
    SPVM_yyerror_format(compiler, "Invalid package variable name %s at %s line %d\n", name, op_package_var->file, op_package_var->line);
    compiler->fatal_error = 1;
  }
  
  our->op_package_var = op_package_var;
  our->op_type = op_type;
  op_our->uv.our = our;
  
  return op_our;
}

const char* SPVM_OP_get_var_name(SPVM_COMPILER* compiler, SPVM_OP* op_var) {
  (void)compiler;
  
  const char* name;
  if (op_var->id == SPVM_OP_C_ID_VAR) {
    name = op_var->uv.var->op_name->uv.name;
  }
  else if (op_var->id == SPVM_OP_C_ID_PACKAGE_VAR) {
    name = op_var->uv.package_var->op_name->uv.name;
  }
  else if (op_var->id == SPVM_OP_C_ID_EXCEPTION_VAR) {
    name = "$@";
  }
  else {
    assert(0);
  }
  
  return name;
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
  
  // Set field informaiton
  op_field->uv.field = field;
  
  return op_field;
}

SPVM_OP* SPVM_OP_build_sub(SPVM_COMPILER* compiler, SPVM_OP* op_sub, SPVM_OP* op_name_sub, SPVM_OP* op_return_type, SPVM_OP* op_args, SPVM_OP* op_descriptors, SPVM_OP* op_block) {
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
    op_block->uv.block->id = SPVM_BLOCK_C_ID_SUB;
    SPVM_OP_insert_child(compiler, op_sub, op_sub->last, op_block);
  }
  
  // Create sub information
  SPVM_SUB* sub = SPVM_SUB_new(compiler);
  sub->op_name = op_name_sub;
  
  // Descriptors
  SPVM_OP* op_descriptor = op_descriptors->first;
  while ((op_descriptor = SPVM_OP_sibling(compiler, op_descriptor))) {
    if (op_descriptor->id == SPVM_DESCRIPTOR_C_ID_NATIVE) {
      sub->is_native = 1;
      sub->disable_jit = 1;
    }
    else if (op_descriptor->id == SPVM_DESCRIPTOR_C_ID_JIT){
      sub->have_jit_desc = 1;
    }
    else {
      SPVM_yyerror_format(compiler, "invalid subroutine descriptor %s", SPVM_DESCRIPTOR_C_ID_NAMES[op_descriptor->id], op_descriptors->file, op_descriptors->line);
    }
  }
  if (sub->is_native && sub->have_jit_desc) {
    SPVM_yyerror_format(compiler, "native and jit descriptor can't be used together %s", SPVM_DESCRIPTOR_C_ID_NAMES[op_descriptor->id], op_descriptors->file, op_descriptors->line);
  }
  
  // Native subroutine can't have block
  if (sub->is_native && op_block) {
    SPVM_yyerror_format(compiler, "Native subroutine can't have block", op_block->file, op_block->line);
  }
  
  // sub args
  {
    int32_t sub_index = 0;
    SPVM_OP* op_arg = op_args->first;
    while ((op_arg = SPVM_OP_sibling(compiler, op_arg))) {
      if (sub_index == 0) {
        // Call type
        SPVM_OP* op_type = op_arg->first->uv.my->op_type;
        if (op_type) {
          if (op_type->id == SPVM_OP_C_ID_CLASS) {
            sub->call_type_id = SPVM_SUB_C_CALL_TYPE_ID_CLASS_METHOD;
          }
          else if (op_type->id == SPVM_OP_C_ID_SELF) {
            sub->call_type_id = SPVM_SUB_C_CALL_TYPE_ID_METHOD;
            SPVM_LIST_push(sub->op_args, op_arg->first);
          }
          else {
            sub->call_type_id = SPVM_SUB_C_CALL_TYPE_ID_SUB;
            SPVM_LIST_push(sub->op_args, op_arg->first);
          }
        }
      }
      else {
        SPVM_LIST_push(sub->op_args, op_arg->first);
      }
      sub_index++;
    }
  }

  // Native my vars is same as arguments
  if (sub->is_native) {
    SPVM_OP* op_arg = op_args->first;
    while ((op_arg = SPVM_OP_sibling(compiler, op_arg))) {
      SPVM_LIST_push(sub->op_mys, op_arg->first);
    }
  }

  // return type
  sub->op_return_type = op_return_type;
  
  if (strcmp(sub->op_name->uv.name, "DESTROY") == 0) {
    sub->is_destructor = 1;
    // DESTROY return type must be void
    if (sub->op_return_type->uv.type->id != SPVM_TYPE_C_ID_VOID) {
      SPVM_yyerror_format(compiler, "DESTROY return type must be void\n", op_block->file, op_block->line);
    }
  }
  
  // Add my declaration to first of block
  if (op_block) {
    SPVM_OP* op_list_statement = op_block->first;
    {
      int32_t i;
      for (i = sub->op_args->length - 1; i >= 0; i--) {
        SPVM_OP* op_arg = SPVM_LIST_fetch(sub->op_args, i);
        SPVM_OP* op_my = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MY, op_arg->file, op_arg->line);
        op_my->uv.my = op_arg->uv.my;
        SPVM_OP_insert_child(compiler, op_list_statement, op_list_statement->first, op_my);
      }
    }
    
    // Add return to last of statement if need
    if (!op_list_statement->last || op_list_statement->last->id != SPVM_OP_C_ID_RETURN) {
      SPVM_OP* op_return = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_RETURN, op_list_statement->file, op_list_statement->line);
      SPVM_TYPE* return_type = sub->op_return_type->uv.type;
      
      SPVM_OP* op_constant;
      if (return_type->id == SPVM_TYPE_C_ID_VOID) {
        // Nothing
      }
      else if (return_type->id == SPVM_TYPE_C_ID_BYTE) {
        op_constant = SPVM_OP_new_op_constant_byte(compiler, 0, op_list_statement->file, op_list_statement->line);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
      }
      else if (return_type->id == SPVM_TYPE_C_ID_SHORT) {
        op_constant = SPVM_OP_new_op_constant_short(compiler, 0, op_list_statement->file, op_list_statement->line);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
      }
      else if (return_type->id == SPVM_TYPE_C_ID_INT) {
        op_constant = SPVM_OP_new_op_constant_int(compiler, 0, op_list_statement->file, op_list_statement->line);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
      }
      else if (return_type->id == SPVM_TYPE_C_ID_LONG) {
        op_constant = SPVM_OP_new_op_constant_long(compiler, 0, op_list_statement->file, op_list_statement->line);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
      }
      else if (return_type->id == SPVM_TYPE_C_ID_FLOAT) {
        op_constant = SPVM_OP_new_op_constant_float(compiler, 0, op_list_statement->file, op_list_statement->line);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
      }
      else if (return_type->id == SPVM_TYPE_C_ID_DOUBLE) {
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

  op_sub->uv.sub = sub;
  
  // Register subroutine name
  {
    // Add sub names
    const char* sub_name = sub->op_name->uv.name;
    
    int32_t* found_index_ptr = SPVM_HASH_search(compiler->sub_name_symtable, sub_name, strlen(sub_name));
    if (!found_index_ptr) {
      SPVM_LIST_push(compiler->sub_names, sub->op_name->uv.name);
      int32_t* new_found_index_ptr = SPVM_COMPILER_ALLOCATOR_alloc_int(compiler, compiler->allocator);
      *new_found_index_ptr = compiler->sub_names->length - 1;
      SPVM_HASH_insert(compiler->sub_name_symtable, sub_name, strlen(sub_name), new_found_index_ptr);
    }
  }
  
  return op_sub;
}

SPVM_OP* SPVM_OP_build_enumeration_value(SPVM_COMPILER* compiler, SPVM_OP* op_name, SPVM_OP* op_constant) {
  
  if (op_constant) {
    
    SPVM_CONSTANT* constant = op_constant->uv.constant;
    
    if (constant->type->id == SPVM_TYPE_C_ID_INT) {
      compiler->enum_default_value = constant->value.int_value;
    }
    else {
      SPVM_yyerror_format(compiler, "enum value must be int type at %s line %d\n", op_constant->file, op_constant->line);
      return NULL;
    }
    
    compiler->enum_default_value++;
  }
  else {
    op_constant = SPVM_OP_new_op_constant_int(compiler, (int32_t)compiler->enum_default_value, op_name->file, op_name->line);
    
    compiler->enum_default_value++;
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
  SPVM_OP* op_return_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_name->file, op_name->line);
  op_return_type->uv.type = op_constant->uv.constant->type;
  
  // Build subroutine
  op_sub = SPVM_OP_build_sub(compiler, op_sub, op_name, op_return_type, NULL, NULL, op_block);
  
  // Set constant
  op_sub->uv.sub->op_constant = op_constant;
  
  // Subroutine is constant
  op_sub->uv.sub->is_enum = 1;
  op_sub->uv.sub->disable_jit = 1;
  op_sub->uv.sub->call_type_id = SPVM_SUB_C_CALL_TYPE_ID_CLASS_METHOD;
  
  return op_sub;
}

SPVM_OP* SPVM_OP_build_enumeration(SPVM_COMPILER* compiler, SPVM_OP* op_enumeration, SPVM_OP* op_enumeration_block) {
  
  // Build OP_SUB
  SPVM_OP_insert_child(compiler, op_enumeration, op_enumeration->last, op_enumeration_block);
  
  // Reset enum information
  compiler->enum_default_value = 0;
  compiler->enum_default_type_id = SPVM_TYPE_C_ID_INT;
  
  return op_enumeration;
}

SPVM_OP* SPVM_OP_build_call_sub(SPVM_COMPILER* compiler, SPVM_OP* op_invocant, SPVM_OP* op_name_sub, SPVM_OP* op_terms) {
  
  // Build OP_SUB
  SPVM_OP* op_call_sub = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CALL_SUB, op_name_sub->file, op_name_sub->line);
  SPVM_OP_insert_child(compiler, op_call_sub, op_call_sub->last, op_name_sub);
  SPVM_OP_insert_child(compiler, op_call_sub, op_call_sub->last, op_terms);
  
  SPVM_CALL_SUB* call_sub = SPVM_CALL_SUB_new(compiler);
  
  const char* sub_name = op_name_sub->uv.name;
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NAME, op_invocant->file, op_invocant->line);
  
  // Normal call
  if (op_invocant->id == SPVM_OP_C_ID_NULL) {
    call_sub->call_type_id = SPVM_SUB_C_CALL_TYPE_ID_SUB;
    op_name->uv.name = sub_name;
    call_sub->op_name = op_name;
  }
  // Class method call
  else if (op_invocant->id == SPVM_OP_C_ID_NAME) {
    call_sub->call_type_id = SPVM_SUB_C_CALL_TYPE_ID_CLASS_METHOD;
    op_name->uv.name = sub_name;
    call_sub->op_name_package = op_invocant;
    call_sub->op_name = op_name;
  }
  // Method call
  else {
    call_sub->call_type_id = SPVM_SUB_C_CALL_TYPE_ID_METHOD;
    call_sub->op_term = op_invocant;
    call_sub->op_name = op_name_sub;
    
    SPVM_OP_insert_child(compiler, op_terms, op_terms->first, op_invocant);
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

SPVM_OP* SPVM_OP_build_assign(SPVM_COMPILER* compiler, SPVM_OP* op_assign, SPVM_OP* op_assign_to, SPVM_OP* op_assign_from) {
  
  if (op_assign->id == SPVM_OP_C_ID_SPECIAL_ASSIGN) {
    int32_t flag = op_assign->flag;
    
    SPVM_OP* op_operation;
    if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_ADD) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_SUBTRACT) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_MULTIPLY) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MULTIPLY, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_DIVIDE) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DIVIDE, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_REMAINDER) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REMAINDER, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_LEFT_SHIFT) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_LEFT_SHIFT, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_SHIFT) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_RIGHT_SHIFT, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_SHIFT_UNSIGNED) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_RIGHT_SHIFT_UNSIGNED, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_XOR) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BIT_XOR, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_OR) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BIT_OR, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_AND) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BIT_AND, op_assign->file, op_assign->line);
    }
    else if (flag == SPVM_OP_C_FLAG_SPECIAL_ASSIGN_CONCAT_STRING) {
      op_operation = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONCAT_STRING, op_assign->file, op_assign->line);
    }
    else {
      assert(0);
    }
    
    SPVM_OP* op_var_right = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_VAR, op_assign->file, op_assign->line);
    op_var_right->uv.var = op_assign_to->uv.var;
    
    SPVM_OP_insert_child(compiler, op_operation, op_operation->last, op_var_right);
    SPVM_OP_insert_child(compiler, op_operation, op_operation->last, op_assign_from);
    
    op_assign_from = op_operation;
    
    op_assign->id = SPVM_OP_C_ID_ASSIGN;
  }
  
  // Build op
  // Exchange left and right for excecution order
  SPVM_OP_insert_child(compiler, op_assign, op_assign->last, op_assign_from);
  SPVM_OP_insert_child(compiler, op_assign, op_assign->last, op_assign_to);
  
  op_assign_to->is_assign_to = 1;
  
  SPVM_OP* op_parent;
  
  op_assign_from->is_assign_from = 1;
  
  // Return variable if first children is var
  if (op_assign_to->id == SPVM_OP_C_ID_VAR) {
    op_assign_from->is_var_assign_from = 1;
    
    SPVM_OP* op_var = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_VAR, op_assign->file, op_assign->line);
    op_var->uv.var = op_assign_to->uv.var;
    SPVM_OP_insert_child(compiler, op_var, op_var->last, op_assign);
    
    op_parent = op_var;
  }
  else {
    op_parent = op_assign;
  }
  
  // Assign left child is var and it has variable declaration, try type inference
  if (op_assign_to->id == SPVM_OP_C_ID_VAR) {
    SPVM_OP* op_var = op_assign_to;
    if (op_var->first && op_var->first->id == SPVM_OP_C_ID_MY) {
      SPVM_OP* op_my = op_var->first;
      SPVM_MY* my = op_my->uv.my;
      my->try_type_inference = 1;
      my->op_term_type_inference = op_assign_from;
    }
  }
  
  return op_parent;
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

SPVM_OP* SPVM_OP_new_op_void(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  
  // Type op
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, file, line);
  
  op_type->uv.type = SPVM_TYPE_get_void_type(compiler);
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_type_byte(SPVM_COMPILER* compiler, SPVM_OP* op_byte) {
  
  // Type op
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_byte->file, op_byte->line);
  op_type->uv.type = SPVM_LIST_fetch(compiler->types, SPVM_TYPE_C_ID_BYTE);
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_type_short(SPVM_COMPILER* compiler, SPVM_OP* op_short) {

  // Type op
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_short->file, op_short->line);
  op_type->uv.type = SPVM_LIST_fetch(compiler->types, SPVM_TYPE_C_ID_SHORT);
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_type_int(SPVM_COMPILER* compiler, SPVM_OP* op_int) {
  // Type op
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_int->file, op_int->line);
  op_type->uv.type = SPVM_LIST_fetch(compiler->types, SPVM_TYPE_C_ID_INT);
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_type_long(SPVM_COMPILER* compiler, SPVM_OP* op_long) {
  // Type op
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_long->file, op_long->line);
  op_type->uv.type = SPVM_LIST_fetch(compiler->types, SPVM_TYPE_C_ID_LONG);
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_type_float(SPVM_COMPILER* compiler, SPVM_OP* op_float) {
  // Type op
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_float->file, op_float->line);
  op_type->uv.type = SPVM_LIST_fetch(compiler->types, SPVM_TYPE_C_ID_FLOAT);
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_type_double(SPVM_COMPILER* compiler, SPVM_OP* op_double) {
  // Type op
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_double->file, op_double->line);
  op_type->uv.type = SPVM_LIST_fetch(compiler->types, SPVM_TYPE_C_ID_DOUBLE);
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_type_name(SPVM_COMPILER* compiler, SPVM_OP* op_name) {
  
  // Type
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->name = op_name->uv.name;
  
  // Type op
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_name->file, op_name->line);
  SPVM_OP_insert_child(compiler, op_type, op_type->last, op_name);
  op_type->uv.type = type;
  
  // Add types
  SPVM_LIST_push(compiler->op_types, op_type);
  
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
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, op_type_child->file, op_type_child->line);
  SPVM_OP_insert_child(compiler, op_type, op_type->last, op_type_child);
  
  if (op_term_length) {
    SPVM_OP_insert_child(compiler, op_type, op_type->last, op_term_length);
  }
  else {
    SPVM_OP* op_null = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, op_type_child->file, op_type_child->line);
    SPVM_OP_insert_child(compiler, op_type, op_type->last, op_null);
  }
  
  op_type->uv.type = type;
  op_type->file = op_type_child->file;
  op_type->line = op_type_child->line;
  
  SPVM_LIST_push(compiler->op_types, op_type);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_list(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  
  SPVM_OP* op_pushmark = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PUSHMARK, file, line);
  
  SPVM_OP* op_list = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_LIST, file, line);
  SPVM_OP_insert_child(compiler, op_list, op_list->last, op_pushmark);
  
  return op_list;
}


SPVM_OP* SPVM_OP_new_op(SPVM_COMPILER* compiler, int32_t id, const char* file, int32_t line) {

  SPVM_OP *op = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_OP));
  
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
