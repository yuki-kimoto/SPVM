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
#include "spvm_name_info.h"
#include "spvm_type.h"
#include "spvm_bytecode_builder.h"
#include "spvm_op_checker.h"
#include "spvm_switch_info.h"
#include "spvm_descriptor.h"
#include "spvm_compiler_allocator.h"
#include "spvm_limit.h"
#include "spvm_extention.h"
#include "spvm_extention_bind.h"
#include "spvm_use.h"







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
  "DIE",
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
};

// Return cloned op and target op become stab
SPVM_OP* SPVM_OP_cut_op(SPVM_COMPILER* compiler, SPVM_OP* op_target) {
  
  // Cut op
  SPVM_OP* op_cut = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, op_target->file, op_target->line);
  op_cut->first = op_target->first;
  op_cut->last = op_target->last;
  if (op_cut->last) {
    op_cut->last->sibparent = op_cut;
  }
  op_cut->uv = op_target->uv;
  op_cut->code = op_target->code;
  op_cut->flag = op_target->flag;
  
  op_target->first = NULL;
  op_target->last = NULL;
  op_target->uv.name = NULL;
  op_target->code = SPVM_OP_C_CODE_STAB;
  op_target->flag = 0;
  
  return op_cut;
}

// Replace target op with replace op
void SPVM_OP_replace_op(SPVM_COMPILER* compiler, SPVM_OP* op_target, SPVM_OP* op_replace) {
  (void)compiler;
  
  op_target->first = op_replace->first;
  op_target->last = op_replace->last;
  if (op_target->last) {
    op_target->last->sibparent = op_target;
  }
  op_target->uv = op_replace->uv;
  op_target->code = op_replace->code;
  op_target->file = op_replace->file;
  op_target->line = op_replace->line;
}

SPVM_OP* SPVM_OP_build_constant(SPVM_COMPILER* compiler, SPVM_OP* op_constant) {
  
  SPVM_DYNAMIC_ARRAY_push(compiler->op_constants, op_constant);
  SPVM_CONSTANT* constant = op_constant->uv.constant;
  
  if (constant->type->id == SPVM_TYPE_C_ID_STRING) {
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
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_short(SPVM_COMPILER* compiler, int16_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.short_value = value;
  constant->type = SPVM_TYPE_get_short_type(compiler);
  
  op_constant->uv.constant = constant;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_int(SPVM_COMPILER* compiler, int32_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.int_value = value;
  constant->type = SPVM_TYPE_get_int_type(compiler);
  
  op_constant->uv.constant = constant;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_long(SPVM_COMPILER* compiler, int64_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.long_value = value;
  constant->type = SPVM_TYPE_get_long_type(compiler);
  
  op_constant->uv.constant = constant;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_float(SPVM_COMPILER* compiler, float value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.float_value = value;
  constant->type = SPVM_TYPE_get_float_type(compiler);
  
  op_constant->uv.constant = constant;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_double(SPVM_COMPILER* compiler, double value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->value.double_value = value;
  constant->type = SPVM_TYPE_get_double_type(compiler);
  
  op_constant->uv.constant = constant;
  
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
  
  // Set exception to undef at first of eval block
  SPVM_OP* op_exception_var = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_EXCEPTION_VAR, op_eval_block->file, op_eval_block->line);
  SPVM_OP* op_undef = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_UNDEF, op_eval_block->file, op_eval_block->line);
  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ASSIGN, op_eval_block->file, op_eval_block->line);
  SPVM_OP_insert_child(compiler, op_assign, op_assign->last, op_exception_var);
  SPVM_OP_insert_child(compiler, op_assign, op_assign->last, op_undef);
  
  op_assign->first->lvalue = 1;
  op_assign->last->rvalue = 1;
  
  SPVM_OP* op_list_statement = op_eval_block->first;
  SPVM_OP_insert_child(compiler, op_list_statement, op_list_statement->first, op_assign);
  
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
    case SPVM_OP_C_CODE_ASSIGN_PROCESS:
      type = SPVM_OP_get_type(compiler, op->first);
      break;
    case SPVM_OP_C_CODE_ARRAY_LENGTH:
      type = SPVM_TYPE_get_int_type(compiler);
      break;
    case SPVM_OP_C_CODE_ARRAY_ELEM: {
      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op->first);
      type = SPVM_HASH_search(compiler->type_symtable, first_type->name, strlen(first_type->name) - 2);
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
      SPVM_NAME_INFO* name_info = op->uv.name_info;
      const char* abs_name = name_info->resolved_name;
      SPVM_OP* op_sub = SPVM_HASH_search(compiler->op_sub_symtable, abs_name, strlen(abs_name));
      SPVM_SUB* sub = op_sub->uv.sub;
      type = sub->op_return_type->uv.type;
      break;
    }
    case SPVM_OP_C_CODE_CALL_FIELD: {
      SPVM_NAME_INFO* name_info = op->uv.name_info;
      const char* abs_name = name_info->resolved_name;
      SPVM_OP* op_field = SPVM_HASH_search(compiler->op_field_symtable, abs_name, strlen(abs_name));
      SPVM_FIELD* field = op_field->uv.field;
      type = field->op_type->uv.type;
      break;
    }
  }
  
  return type;
}

void SPVM_OP_resolve_sub_name(SPVM_COMPILER* compiler, SPVM_OP* op_package, SPVM_OP* op_name) {
  
  SPVM_NAME_INFO* name_info = op_name->uv.name_info;
  
  const char* sub_abs_name = NULL;
  if (name_info->code == SPVM_NAME_INFO_C_CODE_VARBASENAME) {
    const char* package_name = name_info->op_var->uv.var->op_my_var->uv.my_var->op_type->uv.type->name;
    const char* sub_name = name_info->op_name->uv.name;
    sub_abs_name = SPVM_OP_create_abs_name(compiler, package_name, sub_name);
  }
  else if (name_info->code == SPVM_NAME_INFO_C_CODE_ABSNAME) {
    sub_abs_name = name_info->op_name->uv.name;
  }
  else if (name_info->code == SPVM_NAME_INFO_C_CODE_BASENAME) {
    const char* package_name = op_package->uv.package->op_name->uv.name;
    const char* sub_name = name_info->op_name->uv.name;
    sub_abs_name = SPVM_OP_create_abs_name(compiler, package_name, sub_name);
  }
  
  name_info->resolved_name = sub_abs_name;
}

void SPVM_OP_resolve_field_name(SPVM_COMPILER* compiler, SPVM_OP* op_field) {
  
  SPVM_OP* op_term_invoker = op_field->first;
  SPVM_OP* op_name = op_field->last;
  
  SPVM_TYPE* invoker_type = SPVM_OP_get_type(compiler, op_term_invoker);
  const char* package_name = invoker_type->name;
  const char* field_name = op_name->uv.name;
  const char* field_abs_name = SPVM_OP_create_abs_name(compiler, package_name, field_name);
  
  op_field->uv.name_info->resolved_name = field_abs_name;
}

SPVM_OP* SPVM_OP_build_array_elem(SPVM_COMPILER* compiler, SPVM_OP* op_var, SPVM_OP* op_term) {
  
  SPVM_OP* op_array_elem = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ARRAY_ELEM, op_var->file, op_var->line);
  SPVM_OP_insert_child(compiler, op_array_elem, op_array_elem->last, op_var);
  SPVM_OP_insert_child(compiler, op_array_elem, op_array_elem->last, op_term);
  
  return op_array_elem;
}

SPVM_OP* SPVM_OP_build_call_field(SPVM_COMPILER* compiler, SPVM_OP* op_var, SPVM_OP* op_name_field) {
  SPVM_OP* op_field = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CALL_FIELD, op_var->file, op_var->line);
  SPVM_OP_insert_child(compiler, op_field, op_field->last, op_var);
  SPVM_OP_insert_child(compiler, op_field, op_field->last, op_name_field);
  
  SPVM_NAME_INFO* name_info = SPVM_NAME_INFO_new(compiler);
  
  if (strchr(op_name_field->uv.name, ':')) {
    SPVM_yyerror_format(compiler, "field name \"%s\" can't contain :: at %s line %d\n",
      op_name_field, op_name_field->file, op_name_field->line);
  }
  
  name_info->code = SPVM_NAME_INFO_C_CODE_VARBASENAME;
  name_info->op_var = op_var;
  name_info->op_name = op_name_field;
  op_field->uv.name_info = name_info;
  
  return op_field;
}

SPVM_OP* SPVM_OP_build_convert_type(SPVM_COMPILER* compiler, SPVM_OP* op_type, SPVM_OP* op_term) {
  
  SPVM_OP* op_convert_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONVERT, op_type->file, op_type->line);
  SPVM_OP_insert_child(compiler, op_convert_type, op_convert_type->last, op_term);
  SPVM_OP_insert_child(compiler, op_convert_type, op_convert_type->last, op_type);
  
  op_convert_type->file = op_type->file;
  op_convert_type->line = op_type->line;
  
  return op_convert_type;
}

SPVM_OP* SPVM_OP_build_grammar(SPVM_COMPILER* compiler, SPVM_OP* op_packages) {
  
  SPVM_OP* op_grammar = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_GRAMMAR, op_packages->file, op_packages->line);
  SPVM_OP_insert_child(compiler, op_grammar, op_grammar->last, op_packages);
  
  compiler->op_grammar = op_grammar;
  
  // Check types
  SPVM_OP_CHECKER_check(compiler);

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
    type->code = SPVM_TYPE_C_CODE_NAME;
    type->uv.op_name = op_name_package;
    type->base_name = package_name;
    
    // Type OP
    SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_name_package->file, op_name_package->line);
    op_type->uv.type = type;
    
    // Add type
    package->op_type = op_type;
    SPVM_DYNAMIC_ARRAY_push(compiler->op_types, op_type);
    
    SPVM_DYNAMIC_ARRAY* op_fields = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
    SPVM_DYNAMIC_ARRAY* op_subs = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
    
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
        
        const char* field_abs_name = SPVM_OP_create_abs_name(compiler, package_name, field_name);
        SPVM_OP* found_op_field = SPVM_HASH_search(compiler->op_field_symtable, field_abs_name, strlen(field_abs_name));
        
        assert(op_fields->length <= SPVM_LIMIT_C_FIELDS);
        
        if (found_op_field) {
          SPVM_yyerror_format(compiler, "Redeclaration of field \"%s::%s\" at %s line %d\n", package_name, field_name, op_field->file, op_field->line);
        }
        else if (op_fields->length == SPVM_LIMIT_C_FIELDS) {
          SPVM_yyerror_format(compiler, "Too many fields, field \"%s\" ignored at %s line %d\n", field_name, op_field->file, op_field->line);
          compiler->fatal_error = 1;
        }
        else {
          const char* field_abs_name = SPVM_OP_create_abs_name(compiler, package_name, field_name);
          field->abs_name = field_abs_name;
          
          // Add op field symtable
          SPVM_HASH_insert(compiler->op_field_symtable, field_abs_name, strlen(field_abs_name), op_field);
        }
      }
    }
    
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
        
        assert(op_subs->length <= SPVM_LIMIT_C_SUBS);
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
          if (sub->is_native) {
            SPVM_EXTENTION_BIND_bind_core_extentions(compiler, sub, sub_abs_name);
          }
          
          sub->abs_name = sub_abs_name;
          
          assert(op_sub->file);
          
          sub->file_name = op_sub->file;
          
          SPVM_HASH_insert(compiler->op_sub_symtable, sub_abs_name, strlen(sub_abs_name), op_sub);
        }
      }
    }
    
    package->op_fields = op_fields;
    package->op_subs = op_subs;
    
    // Add package
    op_package->uv.package = package;
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

SPVM_OP* SPVM_OP_build_my_var(SPVM_COMPILER* compiler, SPVM_OP* op_my_var, SPVM_OP* op_var, SPVM_OP* op_type) {
  
  // Create my var information
  SPVM_MY_VAR* my_var = SPVM_MY_VAR_new(compiler);
  if (op_type) {
    my_var->op_type = op_type;
  }
  else {
    SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_my_var->file, op_my_var->line);
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

SPVM_OP* SPVM_OP_build_field(SPVM_COMPILER* compiler, SPVM_OP* op_field, SPVM_OP* op_name_field, SPVM_OP* op_type) {
  
  // Build OP
  SPVM_OP_insert_child(compiler, op_field, op_field->last, op_name_field);
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

SPVM_OP* SPVM_OP_build_sub(SPVM_COMPILER* compiler, SPVM_OP* op_sub, SPVM_OP* op_name_sub, SPVM_OP* op_args, SPVM_OP* op_descriptors, SPVM_OP* op_type_or_void, SPVM_OP* op_block) {
  
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
  SPVM_OP_insert_child(compiler, op_sub, op_sub->last, op_type_or_void);
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
      SPVM_yyerror_format(compiler, "invalid descriptor %s", SPVM_DESCRIPTOR_C_CODE_NAMES[op_descriptor->code], op_descriptors->file, op_descriptors->line);
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
  sub->op_return_type = op_type_or_void;
  
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
    
    compiler->enum_default_type_id = constant->type->id;
    
    // TODO add type
    if (compiler->enum_default_type_id == SPVM_TYPE_C_ID_BYTE) {
      compiler->enum_default_value = constant->value.byte_value;
    }
    else if (compiler->enum_default_type_id == SPVM_TYPE_C_ID_SHORT) {
      compiler->enum_default_value = constant->value.short_value;
    }
    else if (compiler->enum_default_type_id == SPVM_TYPE_C_ID_INT) {
      compiler->enum_default_value = constant->value.int_value;
    }
    else if (compiler->enum_default_type_id == SPVM_TYPE_C_ID_LONG) {
      compiler->enum_default_value = constant->value.long_value;
    }
    else if (compiler->enum_default_type_id == SPVM_TYPE_C_ID_FLOAT) {
      compiler->enum_default_value = (int64_t)constant->value.float_value;
    }
    else if (compiler->enum_default_type_id == SPVM_TYPE_C_ID_DOUBLE) {
      compiler->enum_default_value = (int64_t)constant->value.double_value;
    }
    
    compiler->enum_default_value++;
  }
  else {
    SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
    
    // TODO add type
    if (compiler->enum_default_type_id == SPVM_TYPE_C_ID_BYTE) {
      constant->type = SPVM_TYPE_get_byte_type(compiler);
      constant->value.byte_value = (int8_t)compiler->enum_default_value;
    }
    else if (compiler->enum_default_type_id == SPVM_TYPE_C_ID_SHORT) {
      constant->type = SPVM_TYPE_get_short_type(compiler);
      constant->value.short_value = (int16_t)compiler->enum_default_value;
    }
    else if (compiler->enum_default_type_id == SPVM_TYPE_C_ID_INT) {
      constant->type = SPVM_TYPE_get_int_type(compiler);
      constant->value.int_value = (int32_t)compiler->enum_default_value;
    }
    else if (compiler->enum_default_type_id == SPVM_TYPE_C_ID_LONG) {
      constant->type = SPVM_TYPE_get_long_type(compiler);
      constant->value.long_value = (int64_t)compiler->enum_default_value;
    }
    else if (compiler->enum_default_type_id == SPVM_TYPE_C_ID_FLOAT) {
      constant->type = SPVM_TYPE_get_float_type(compiler);
      constant->value.float_value = (float)compiler->enum_default_value;
    }
    else if (compiler->enum_default_type_id == SPVM_TYPE_C_ID_DOUBLE) {
      constant->type = SPVM_TYPE_get_double_type(compiler);
      constant->value.double_value = (double)compiler->enum_default_value;
    }
    else {
      assert(0);
    }
    
    op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, op_name->file, op_name->line);
    op_constant->uv.constant = constant;
    
    SPVM_DYNAMIC_ARRAY_push(compiler->op_constants, op_constant);
    
    compiler->enum_default_value++;
  }
  SPVM_DYNAMIC_ARRAY_push(compiler->op_constants, op_constant);
  
  // Return
  SPVM_OP* op_return = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_RETURN, op_name->file, op_name->line);
  SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
  
  // Block
  SPVM_OP* op_block = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, op_name->file, op_name->line);
  SPVM_OP_insert_child(compiler, op_block, op_block->last, op_return);
  
  // sub
  SPVM_OP* op_sub = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_SUB, op_name->file, op_name->line);
  op_sub->file = op_name->file;
  op_sub->line = op_name->line;
  
  // Type
  SPVM_OP* op_return_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_name->file, op_name->line);
  op_return_type->uv.type = op_constant->uv.constant->type;
  
  // Build subroutine
  op_sub = SPVM_OP_build_sub(compiler, op_sub, op_name, NULL, NULL, op_return_type, op_block);
  
  // Subroutine is constant
  op_sub->uv.sub->is_constant = 1;
  
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
  
  if (op_name_sub->code == SPVM_OP_C_CODE_NEW) {
    op_name_sub->code = SPVM_OP_C_CODE_NAME;
    op_name_sub->uv.name = "new";
  }
  
  // Build OP_SUB
  SPVM_OP* op_call_sub = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CALL_SUB, op_name_sub->file, op_name_sub->line);
  SPVM_OP_insert_child(compiler, op_call_sub, op_call_sub->last, op_name_sub);
  SPVM_OP_insert_child(compiler, op_call_sub, op_call_sub->last, op_terms);
  
  SPVM_NAME_INFO* name_info = SPVM_NAME_INFO_new(compiler);
  
  const char* sub_name = op_name_sub->uv.name;
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NAME, op_invocant->file, op_invocant->line);
  
  // Normal call
  if (op_invocant->code == SPVM_OP_C_CODE_NULL) {
    // Absolute
    // P::m();
    if (strstr(sub_name, ":")) {
      name_info->code = SPVM_NAME_INFO_C_CODE_ABSNAME;
      op_name->uv.name = sub_name;
      name_info->op_name = op_name;
    }
    // Base name
    // m();
    else {
      name_info->code = SPVM_NAME_INFO_C_CODE_BASENAME;
      op_name->uv.name = sub_name;
      name_info->op_name = op_name;
    }
  }
  // Method call
  else if (op_invocant->code == SPVM_OP_C_CODE_VAR) {
    // Absolute
    // $var->P::m();
    if (strstr(sub_name, ":")) {
      name_info->code = SPVM_NAME_INFO_C_CODE_ABSNAME;
      op_name->uv.name = sub_name;
      name_info->op_name = op_name;
    }
    // Base name
    // $var->m();
    else {
      name_info->code = SPVM_NAME_INFO_C_CODE_VARBASENAME;
      name_info->op_var = op_invocant;
      name_info->op_name = op_name_sub;
    }
    SPVM_OP_insert_child(compiler, op_terms, op_terms->last, op_invocant);
  }
  // Method call
  else if (op_invocant->code == SPVM_OP_C_CODE_NAME) {
    // Absolute
    // P->Q::m;
    if (strstr(sub_name, ":")) {
      SPVM_yyerror_format(compiler, "package name is ambiguas %s line %d\n", op_invocant->file, op_invocant->line);
    }
    // Base name
    else {
      const char* package_name = op_invocant->uv.name;
      const char* name = op_name_sub->uv.name;
      
      // Create abs name
      const char* abs_name = SPVM_OP_create_abs_name(compiler, package_name, name);
      
      // Create op abs name
      SPVM_OP* op_abs_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NAME, op_invocant->file, op_invocant->line);
      op_abs_name->uv.name = abs_name;
      
      // Set abs name
      name_info->code = SPVM_NAME_INFO_C_CODE_ABSNAME;
      name_info->op_name = op_abs_name;
    }
  }
  
  op_call_sub->uv.name_info = name_info;
  
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
      
      // Length constant
      int32_t length = 0;
      SPVM_TYPE* first_type = NULL;
      SPVM_OP* op_constant = op_list->first;
      while ((op_constant = SPVM_OP_sibling(compiler, op_constant))) {
        if (first_type == NULL) {
          first_type = SPVM_OP_get_type(compiler, op_constant);
        }
        
        // Type must be same as first type
        SPVM_TYPE* constant_type = SPVM_OP_get_type(compiler, op_constant);
        if (constant_type->id != first_type->id) {
          SPVM_yyerror_format(compiler, "All of array init elements must be same types at %s line %d\n", op_list->file, op_list->line);
          compiler->fatal_error = 1;
          return NULL;
        }
        
        length++;
      }
      SPVM_OP* op_constant_length = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, op_list->file, op_list->line);
      SPVM_CONSTANT* constant_length = SPVM_CONSTANT_new(compiler);
      constant_length->type = SPVM_TYPE_get_int_type(compiler);
      constant_length->value.int_value = length;
      op_constant_length->uv.constant = constant_length;
      
      // New
      SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NEW, op_list->file, op_list->line);
      SPVM_OP* op_type_new = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_list->file, op_list->line);
      
      if (first_type->id == SPVM_TYPE_C_ID_BYTE) {
        op_type_new->uv.type = SPVM_HASH_search(compiler->type_symtable, "byte[]", strlen("byte[]"));
      }
      else if (first_type->id == SPVM_TYPE_C_ID_SHORT) {
        op_type_new->uv.type = SPVM_HASH_search(compiler->type_symtable, "short[]", strlen("short[]"));
      }
      else if (first_type->id == SPVM_TYPE_C_ID_INT) {
        op_type_new->uv.type = SPVM_HASH_search(compiler->type_symtable, "int[]", strlen("int[]"));
      }
      else if (first_type->id == SPVM_TYPE_C_ID_LONG) {
        op_type_new->uv.type = SPVM_HASH_search(compiler->type_symtable, "long[]", strlen("long[]"));
      }
      else if (first_type->id == SPVM_TYPE_C_ID_FLOAT) {
        op_type_new->uv.type = SPVM_HASH_search(compiler->type_symtable, "float[]", strlen("float[]"));
      }
      else if (first_type->id == SPVM_TYPE_C_ID_DOUBLE) {
        op_type_new->uv.type = SPVM_HASH_search(compiler->type_symtable, "double[]", strlen("double[]"));
      }
      else if (first_type->id == SPVM_TYPE_C_ID_STRING) {
        op_type_new->uv.type = SPVM_HASH_search(compiler->type_symtable, "string[]", strlen("string[]"));
      }
      else {
        assert(0);
      }
      SPVM_OP_insert_child(compiler, op_new, op_new->last, op_type_new);
      
      op_assign->last = op_new;
      op_new->moresib = 0;
      op_new->sibparent = op_assign;
      op_first->sibparent = op_new;
      
      // Add length constant
      SPVM_OP_insert_child(compiler, op_type_new, op_type_new->last, op_constant_length);
      
      // Assign array element
      SPVM_OP* op_list_new = SPVM_OP_new_op_list(compiler, op_list->file, op_list->line);
      SPVM_DYNAMIC_ARRAY* op_constants = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
      op_constant = op_list->first;
      while ((op_constant = SPVM_OP_sibling(compiler, op_constant))) {
        SPVM_DYNAMIC_ARRAY_push(op_constants, op_constant);
      }
      {
        int32_t i;
        for (i = 0; i < op_constants->length; i++) {
          SPVM_OP* op_constant = SPVM_DYNAMIC_ARRAY_fetch(op_constants, i);
          
          SPVM_OP* op_assign_array = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ASSIGN, op_list->file, op_list->line);
          SPVM_OP* op_array_elem = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ARRAY_ELEM, op_list->file, op_list->line);
          SPVM_OP* op_var_array_elem = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_VAR, op_list->file, op_list->line);
          op_var_array_elem->uv.var = op_first->uv.var;
          SPVM_OP_insert_child(compiler, op_array_elem, op_array_elem->last, op_var_array_elem);
          
          SPVM_OP* op_constant_index = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, op_list->file, op_list->line);
          SPVM_CONSTANT* constant_index = SPVM_CONSTANT_new(compiler);
          constant_index->type = SPVM_TYPE_get_int_type(compiler);
          constant_index->value.int_value = i;
          op_constant_index->uv.constant = constant_index;
          SPVM_OP_insert_child(compiler, op_array_elem, op_array_elem->last, op_constant_index);
          
          SPVM_OP_insert_child(compiler, op_assign_array, op_assign_array->last, op_array_elem);
          op_constant->moresib = 0;
          op_constant->sibparent = NULL;
          SPVM_OP_insert_child(compiler, op_assign_array, op_assign_array->last, op_constant);
          
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


SPVM_OP* SPVM_OP_build_void(SPVM_COMPILER* compiler, SPVM_OP* op_void) {
  
  // Name op
  const char* name = "void";
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NAME, op_void->file, op_void->line);
  op_name->uv.name = name;
  
  // Type
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->code = SPVM_TYPE_C_CODE_NAME;
  type->uv.op_name = op_name;
  type->base_name = name;
  
  // Type op
  SPVM_OP* op_type_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_void->file, op_void->line);
  SPVM_OP_insert_child(compiler, op_type_name, op_type_name->last, op_name);
  op_type_name->uv.type = type;
  op_type_name->file = op_name->file;
  op_type_name->line = op_name->line;
  
  // Resolve name and id
  type->name = name;
  type->id = SPVM_TYPE_C_ID_VOID;
  
  // Add types
  SPVM_DYNAMIC_ARRAY_push(compiler->op_types, op_type_name);
  
  return op_type_name;
}

SPVM_OP* SPVM_OP_build_return(SPVM_COMPILER* compiler, SPVM_OP* op_return, SPVM_OP* op_term) {
  
  if (op_term) {
    SPVM_OP_insert_child(compiler, op_return, op_return->last, op_term);
  }
  
  return op_return;
}

SPVM_OP* SPVM_OP_build_die(SPVM_COMPILER* compiler, SPVM_OP* op_die, SPVM_OP* op_term) {
  
  if (!op_term) {
    // Default error message
    SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, op_die->file, op_die->line);
    SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
    constant->value.string_value = "Error";
    constant->type = SPVM_TYPE_get_string_type(compiler);
    op_constant->uv.constant = constant;
    
    op_term = op_constant;
  }
  
  // Exception variable
  SPVM_OP* op_exception_var = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_EXCEPTION_VAR, op_term->file, op_term->line);
  
  // Assign
  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ASSIGN, op_term->file, op_term->line);
  SPVM_OP_insert_child(compiler, op_assign, op_assign->last, op_exception_var);
  SPVM_OP_insert_child(compiler, op_assign, op_assign->last, op_term);
  
  op_assign->first->lvalue = 1;
  op_assign->last->rvalue = 1;
  
  SPVM_OP_insert_child(compiler, op_die, op_die->last, op_assign);
  
  return op_die;
}

SPVM_OP* SPVM_OP_build_type_name(SPVM_COMPILER* compiler, SPVM_OP* op_name) {
  
  // Type
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->code = SPVM_TYPE_C_CODE_NAME;
  type->uv.op_name = op_name;
  type->base_name = op_name->uv.name;
  
  // Type op
  SPVM_OP* op_type_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_name->file, op_name->line);
  SPVM_OP_insert_child(compiler, op_type_name, op_type_name->last, op_name);
  op_type_name->uv.type = type;
  op_type_name->file = op_name->file;
  op_type_name->line = op_name->line;
  
  SPVM_TYPE_resolve_name(compiler, op_type_name);

  // Resolve only numeric type
  const char* type_name = op_name->uv.name;
  if (strcmp(type_name, "byte") == 0 || strcmp(type_name, "short") == 0 || strcmp(type_name, "int") == 0
    || strcmp(type_name, "long") == 0 || strcmp(type_name, "float") == 0 || strcmp(type_name, "double") == 0
  )
  {
    SPVM_TYPE_resolve_id(compiler, op_type_name);
  }
  
  // Add types
  SPVM_DYNAMIC_ARRAY_push(compiler->op_types, op_type_name);
  
  return op_type_name;
}

SPVM_OP* SPVM_OP_build_type_array(SPVM_COMPILER* compiler, SPVM_OP* op_type, SPVM_OP* op_term_length) {
  
  // Type
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->code = SPVM_TYPE_C_CODE_ARRAY;
  type->uv.op_type = op_type;
  assert(op_type->uv.type->base_name);
  type->base_name = op_type->uv.type->base_name;
  type->dimension = op_type->uv.type->dimension + 1;
  
  // Type OP
  SPVM_OP* op_type_array = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_type->file, op_type->line);
  SPVM_OP_insert_child(compiler, op_type_array, op_type_array->last, op_type);
  
  if (op_term_length) {
    SPVM_OP_insert_child(compiler, op_type_array, op_type_array->last, op_term_length);
  }
  else {
    SPVM_OP* op_null = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, op_type->file, op_type->line);
    SPVM_OP_insert_child(compiler, op_type_array, op_type_array->last, op_null);
  }
  
  op_type_array->uv.type = type;
  op_type_array->file = op_type->file;
  op_type_array->line = op_type->line;
  
  SPVM_DYNAMIC_ARRAY_push(compiler->op_types, op_type_array);
  
  SPVM_TYPE_resolve_name(compiler, op_type_array);
  
  return op_type_array;
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
