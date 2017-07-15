#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>

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
  "MALLOC",
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
};

SPVM_OP* SPVM_OP_build_constant(SPVM_COMPILER* compiler, SPVM_OP* op_constant) {
  
  SPVM_DYNAMIC_ARRAY_push(compiler->op_constants, op_constant);
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_use_from_package_name(SPVM_COMPILER* compiler, const char* package_name, const char* file, int32_t line) {

  SPVM_OP* op_name_package = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NAME, file, line);
  op_name_package->uv.name = package_name;
  SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_USE, file, line);
  SPVM_OP_insert_child(compiler, op_use, op_use->last, op_name_package);
  
  return op_use;
}

SPVM_OP* SPVM_OP_new_op_constant_int(SPVM_COMPILER* compiler, int32_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->code = SPVM_CONSTANT_C_CODE_INT;
  constant->uv.long_value = value;
  constant->type = SPVM_HASH_search(compiler->type_symtable, "int", strlen("int"));
  
  op_constant->uv.constant = constant;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_long(SPVM_COMPILER* compiler, int64_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->code = SPVM_CONSTANT_C_CODE_LONG;
  constant->uv.long_value = value;
  constant->type = SPVM_HASH_search(compiler->type_symtable, "long", strlen("long"));
  
  op_constant->uv.constant = constant;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_float(SPVM_COMPILER* compiler, float value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->code = SPVM_CONSTANT_C_CODE_FLOAT;
  constant->uv.float_value = value;
  constant->type = SPVM_HASH_search(compiler->type_symtable, "float", strlen("float"));
  
  op_constant->uv.constant = constant;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_double(SPVM_COMPILER* compiler, double value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  
  constant->code = SPVM_CONSTANT_C_CODE_DOUBLE;
  constant->uv.double_value = value;
  constant->type = SPVM_HASH_search(compiler->type_symtable, "double", strlen("double"));
  
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
  op_switch->uv.switch_info->op_cases = compiler->cur_op_cases;
  
  op_switch_condition->uv.switch_info = switch_info;
  switch_info->op_term_condition = op_term_condition;
  
  compiler->cur_op_cases = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
  
  return op_switch;
}

SPVM_OP* SPVM_OP_build_case_statement(SPVM_COMPILER* compiler, SPVM_OP* op_case, SPVM_OP* op_term) {
  
  SPVM_OP_insert_child(compiler, op_case, op_case->last, op_term);
  
  op_term->flag = SPVM_OP_C_FLAG_CONSTANT_CASE;
  
  assert(compiler->cur_op_cases->length <= SPVM_LIMIT_C_CASES);
  if (compiler->cur_op_cases->length == SPVM_LIMIT_C_CASES) {
    SPVM_yyerror_format(compiler, "Too many case statements at %s line %d\n", op_case->file, op_case->line);
    return NULL;
  }

  SPVM_DYNAMIC_ARRAY_push(compiler->cur_op_cases, op_case);
  
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

SPVM_OP* SPVM_OP_build_if_statement(SPVM_COMPILER* compiler, SPVM_OP* op_if, SPVM_OP* op_term, SPVM_OP* op_block_false, SPVM_OP* op_block_true) {
  
  // ELSIF is same as IF
  if (op_if->code == SPVM_OP_C_CODE_ELSIF) {
    op_if->code = SPVM_OP_C_CODE_IF;
  }
  
  // Condition
  SPVM_OP* op_condition = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONDITION, op_term->file, op_term->line);
  op_condition->flag |= SPVM_OP_C_FLAG_CONDITION_IF;
  SPVM_OP_insert_child(compiler, op_condition, op_condition->last, op_term);

  // Create false block if needed
  if (op_block_false->code != SPVM_OP_C_CODE_BLOCK) {
    SPVM_OP* op_not_block = op_block_false;
    
    op_block_false = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, op_not_block->file, op_not_block->line);
    SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, op_not_block->file, op_not_block->line);
    SPVM_OP_insert_child(compiler, op_list, op_list->last, op_not_block);
    SPVM_OP_insert_child(compiler, op_block_false, op_block_false->last, op_list);
  }
  
  // Create true block if needed
  if (op_block_true->code != SPVM_OP_C_CODE_BLOCK) {
    SPVM_OP* op_not_block = op_block_true;
    
    // Create block
    op_block_true = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, op_not_block->file, op_not_block->line);
    SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, op_not_block->file, op_not_block->line);
    SPVM_OP_insert_child(compiler, op_list, op_list->last, op_not_block);
    SPVM_OP_insert_child(compiler, op_block_true, op_block_true->last, op_list);
  }
  
  op_block_true->flag |= SPVM_OP_C_FLAG_BLOCK_IF_TURE;
  op_block_false->flag |= SPVM_OP_C_FLAG_BLOCK_IF_FALSE;
  
  SPVM_OP_insert_child(compiler, op_if, op_if->last, op_condition);
  SPVM_OP_insert_child(compiler, op_if, op_if->last, op_block_true);
  SPVM_OP_insert_child(compiler, op_if, op_if->last, op_block_false);
  
  if (op_block_false->code == SPVM_OP_C_CODE_BLOCK) {
    op_block_true->flag |= SPVM_OP_C_FLAG_BLOCK_HAS_ELSE;
  }
  
  return op_if;
}

SPVM_OP* SPVM_OP_build_array_length(SPVM_COMPILER* compiler, SPVM_OP* op_array_length, SPVM_OP* op_term) {
  
  SPVM_OP_insert_child(compiler, op_array_length, op_array_length->last, op_term);
  
  return op_array_length;
}

SPVM_OP* SPVM_OP_build_malloc_object(SPVM_COMPILER* compiler, SPVM_OP* op_malloc, SPVM_OP* op_type) {
  
  SPVM_OP_insert_child(compiler, op_malloc, op_malloc->last, op_type);
  
  return op_malloc;
}

SPVM_TYPE* SPVM_OP_get_type(SPVM_COMPILER* compiler, SPVM_OP* op) {
  
  SPVM_TYPE*  type = NULL;
  
  switch (op->code) {
    case SPVM_OP_C_CODE_ARRAY_LENGTH:
      type = SPVM_HASH_search(compiler->type_symtable, "int", strlen("int"));
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
    case SPVM_OP_C_CODE_MALLOC:
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
      type = SPVM_HASH_search(compiler->type_symtable, "string", strlen("string"));
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
      if (sub->op_return_type->code != SPVM_OP_C_CODE_VOID) {
        type = sub->op_return_type->uv.type;
      }
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

void SPVM_OP_convert_and_to_if(SPVM_COMPILER* compiler, SPVM_OP* op_if1) {
  
  /* before
    AND
      x
      y
  */
  
  /* after 
    IF              if1
      CONDITION
        x
      IF            if2
        CONDITION
          y
        1           true1
        0           false1
      0             false2
  */
  
  SPVM_OP* op_x = op_if1->first;
  SPVM_OP* op_y = op_if1->last;
  
  // Convert to ADN to IF
  op_if1->code = SPVM_OP_C_CODE_IF;
  
  // Cut op
  op_x->moresib = 0;
  op_x->sibparent = NULL;
  op_y->moresib = 0;
  op_y->sibparent = NULL;
  op_if1->first = NULL;
  op_if1->last = NULL;
  
  // Constant true
  SPVM_OP* op_constant_true = SPVM_OP_new_op_constant_int(compiler, 1, op_if1->file, op_if1->line);

  // Constant false 1
  SPVM_OP* op_constant_false1 = SPVM_OP_new_op_constant_int(compiler, 0, op_if1->file, op_if1->line);
  
  // Constant false 2
  SPVM_OP* op_constant_false2 = SPVM_OP_new_op_constant_int(compiler, 0, op_if1->file, op_if1->line);
  
  // if2
  SPVM_OP* op_if2 = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_IF, op_if1->file, op_if1->line);
  
  // Build if tree
  SPVM_OP_build_if_statement(compiler, op_if2, op_y, op_constant_true, op_constant_false1);
  SPVM_OP_build_if_statement(compiler, op_if1, op_x, op_if2, op_constant_false2);
}

void SPVM_OP_convert_or_to_if(SPVM_COMPILER* compiler, SPVM_OP* op_if1) {
  
  // before
  //  OR
  //    x
  //    y
  
  // after 
  //  IF      if1
  //    x
  //    1     true1
  //    IF    if2
  //      y
  //      1   true2
  //      0   false
  
  SPVM_OP* op_x = op_if1->first;
  SPVM_OP* op_y = op_if1->last;
  
  // Convert to ADN to IF
  op_if1->code = SPVM_OP_C_CODE_IF;
  
  // Cut op
  op_x->moresib = 0;
  op_x->sibparent = NULL;
  op_y->moresib = 0;
  op_y->sibparent = NULL;
  op_if1->first = NULL;
  op_if1->last = NULL;
  
  // Constant true 1
  SPVM_OP* op_constant_true1 = SPVM_OP_new_op_constant_int(compiler, 1, op_if1->file, op_if1->line);
  
  // Constant true 2
  SPVM_OP* op_constant_true2 = SPVM_OP_new_op_constant_int(compiler, 1, op_if1->file, op_if1->line);
  
  // Constant false
  SPVM_OP* op_constant_false = SPVM_OP_new_op_constant_int(compiler, 0, op_if1->file, op_if1->line);
  
  // if2
  SPVM_OP* op_if2 = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_IF, op_if1->file, op_if1->line);
  
  // Build if tree
  SPVM_OP_build_if_statement(compiler, op_if2, op_y, op_constant_true2, op_constant_false);
  SPVM_OP_build_if_statement(compiler, op_if1, op_x, op_constant_true1, op_if2);
}

void SPVM_OP_convert_not_to_if(SPVM_COMPILER* compiler, SPVM_OP* op_if) {
  
  // before
  //  NOT
  //    x
  
  // after 
  //  IF
  //    x
  //    0
  //    1
  
  SPVM_OP* op_x = op_if->first;
  
  // Convert to ADN to IF
  op_if->code = SPVM_OP_C_CODE_IF;
  
  // Cut op
  op_x->moresib = 0;
  op_x->sibparent = NULL;
  op_if->first = NULL;
  op_if->last = NULL;
  
  // Constant false
  SPVM_OP* op_constant_false = SPVM_OP_new_op_constant_int(compiler, 0, op_if->file, op_if->line);

  // Constant true
  SPVM_OP* op_constant_true = SPVM_OP_new_op_constant_int(compiler, 1, op_if->file, op_if->line);
  
  // Build if tree
  SPVM_OP_build_if_statement(compiler, op_if, op_x, op_constant_false, op_constant_true);
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
    
    // Type OP
    SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_name_package->file, op_name_package->line);
    op_type->uv.type = type;
    
    // Add type
    package->op_type = op_type;
    SPVM_DYNAMIC_ARRAY_push(compiler->op_types, op_type);
    
    SPVM_DYNAMIC_ARRAY* op_fields = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
    SPVM_DYNAMIC_ARRAY* op_subs = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
    
    // Fields
    SPVM_OP* op_decls = op_block->first;
    SPVM_OP* op_decl = op_decls->first;
    while ((op_decl = SPVM_OP_sibling(compiler, op_decl))) {
      if (op_decl->code == SPVM_OP_C_CODE_FIELD) {
        SPVM_OP* op_field = op_decl;
        SPVM_FIELD* field = op_field->uv.field;
        const char* field_name = field->op_name->uv.name;
        
        const char* field_abs_name = SPVM_OP_create_abs_name(compiler, package_name, field_name);
        SPVM_OP* found_op_field = SPVM_HASH_search(compiler->op_field_symtable, field_abs_name, strlen(field_abs_name));
        
        assert(op_fields->length <= SPVM_LIMIT_C_FIELDS);
        
        if (found_op_field) {
          SPVM_yyerror_format(compiler, "redeclaration of field \"%s::%s\" at %s line %d\n", package_name, field_name, op_field->file, op_field->line);
        }
        else if (op_fields->length == SPVM_LIMIT_C_FIELDS) {
          SPVM_yyerror_format(compiler, "too many fields, field \"%s\" ignored at %s line %d\n", field_name, op_field->file, op_field->line);
          compiler->fatal_error = 1;
        }
        else {
          SPVM_DYNAMIC_ARRAY_push(op_fields, op_field);
          
          const char* field_abs_name = SPVM_OP_create_abs_name(compiler, package_name, field_name);
          field->abs_name = field_abs_name;
          
          // Add op field symtable
          SPVM_HASH_insert(compiler->op_field_symtable, field_abs_name, strlen(field_abs_name), op_field);
        }
      }
      else if (op_decl->code == SPVM_OP_C_CODE_SUB) {
        SPVM_OP* op_sub = op_decl;
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
          SPVM_yyerror_format(compiler, "too many subroutines at %s line %d\n", sub_name, op_sub->file, op_sub->line);
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
          SPVM_DYNAMIC_ARRAY_push(op_subs, op_sub);
        }
      }
      else if (op_decl->code == SPVM_OP_C_CODE_ENUM) {
        SPVM_OP* op_enumeration = op_decl;
        SPVM_OP* op_enumeration_block = op_enumeration->first;
        
        // Starting value
        int64_t start_value = 0;
        SPVM_OP* op_enumeration_values = op_enumeration_block->first;
        SPVM_OP* op_enumeration_value = op_enumeration_values->first;
        
        int32_t constant_code = SPVM_CONSTANT_C_CODE_LONG;
        while ((op_enumeration_value = SPVM_OP_sibling(compiler, op_enumeration_value))) {
          SPVM_ENUMERATION_VALUE* enumeration_value = SPVM_ENUMERATION_VALUE_new(compiler);
          enumeration_value->op_name = op_enumeration_value->first;
          if (op_enumeration_value->first != op_enumeration_value->last) {
            enumeration_value->op_constant = op_enumeration_value->last;
          }
          
          SPVM_OP* op_constant;
          if (enumeration_value->op_constant) {
            op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CONSTANT, op_enumeration_value->file, op_enumeration_value->line);
            op_constant->uv.constant = enumeration_value->op_constant->uv.constant;
            
            if (op_constant->uv.constant->code == SPVM_CONSTANT_C_CODE_INT) {
              constant_code = SPVM_CONSTANT_C_CODE_INT;
            }
            else if (op_constant->uv.constant->code == SPVM_CONSTANT_C_CODE_LONG) {
              constant_code = SPVM_CONSTANT_C_CODE_LONG;
            }
            else {
              assert(0);
            }
            start_value = op_constant->uv.constant->uv.long_value + 1;
          }
          else {
            if (constant_code == SPVM_CONSTANT_C_CODE_INT) {
              op_constant = SPVM_OP_new_op_constant_int(compiler, (int32_t)start_value, op_enumeration_value->file, op_enumeration_value->line);
            }
            else if (constant_code == SPVM_CONSTANT_C_CODE_LONG) {
              op_constant = SPVM_OP_new_op_constant_long(compiler, start_value, op_enumeration_value->file, op_enumeration_value->line);
            }
            else {
              assert(0);
            }
            enumeration_value->op_constant = op_constant;
            
            start_value++;
          }
          
          // sub
          SPVM_OP* op_sub = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_SUB, op_enumeration_value->file, op_enumeration_value->line);
          op_sub->file = op_enumeration_value->file;
          op_sub->line = op_enumeration_value->line;
          
          // Type
          SPVM_OP* op_return_type = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_enumeration_value->file, op_enumeration_value->line);
          op_return_type->uv.type = op_constant->uv.constant->type;

          // Name
          SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NAME, op_enumeration_value->file, op_enumeration_value->line);
          op_name->uv.name = enumeration_value->op_name->uv.name;
          
          // Return
          SPVM_OP* op_return = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_RETURN, op_enumeration_value->file, op_enumeration_value->line);
          SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
          
          // Create sub information
          SPVM_SUB* sub = SPVM_SUB_new(compiler);
          sub->op_name = op_name;
          sub->op_return_type = op_return_type;
          sub->op_block = op_constant;
          sub->is_constant = 1;

          // Create absolute name
          const char* sub_abs_name = SPVM_OP_create_abs_name(compiler, package_name, op_name->uv.name);
          sub->abs_name = sub_abs_name;
          sub->file_name = op_enumeration_value->file;
          
          // Set sub
          op_sub->uv.sub = sub;
         
          SPVM_OP* found_op_sub = SPVM_HASH_search(compiler->op_sub_symtable, sub_abs_name, strlen(sub_abs_name));
          
          if (found_op_sub) {
            SPVM_yyerror_format(compiler, "redeclaration of sub \"%s\" at %s line %d\n", sub_abs_name, op_sub->file, op_sub->line);
          }
          // Unknown sub
          else {
            SPVM_HASH_insert(compiler->op_sub_symtable, sub_abs_name, strlen(sub_abs_name), op_sub);
            SPVM_DYNAMIC_ARRAY_push(op_subs, op_sub);
          }
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

SPVM_OP* SPVM_OP_build_use(SPVM_COMPILER* compiler, SPVM_OP* op_use, SPVM_OP* op_name_package) {
  
  SPVM_OP_insert_child(compiler, op_use, op_use->last, op_name_package);
  
  const char* package_name = op_name_package->uv.name;
  SPVM_OP* found_op_use = SPVM_HASH_search(compiler->op_use_symtable, package_name, strlen(package_name));
  
  if (!found_op_use) {
    SPVM_DYNAMIC_ARRAY_push(compiler->op_use_stack, op_use);
    SPVM_HASH_insert(compiler->op_use_symtable, package_name, strlen(package_name), op_use);
  }
  
  return op_use;
}

SPVM_OP* SPVM_OP_build_my_var(SPVM_COMPILER* compiler, SPVM_OP* op_my_var, SPVM_OP* op_var, SPVM_OP* op_type) {
  
  // Create my var information
  SPVM_MY_VAR* my_var = SPVM_MY_VAR_new(compiler);
  my_var->op_type = op_type;
  
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
  }
  
  // return type
  sub->op_return_type = op_type_or_void;
  
  // Save block
  sub->op_block = op_block;

  op_sub->uv.sub = sub;
  
  return op_sub;
}

SPVM_OP* SPVM_OP_build_enumeration(SPVM_COMPILER* compiler, SPVM_OP* op_enumeration, SPVM_OP* op_enumeration_block) {
  
  // Build OP_SUB
  SPVM_OP_insert_child(compiler, op_enumeration, op_enumeration->last, op_enumeration_block);
  
  return op_enumeration;
}

SPVM_OP* SPVM_OP_build_call_sub(SPVM_COMPILER* compiler, SPVM_OP* op_invocant, SPVM_OP* op_name_sub, SPVM_OP* op_terms) {
  
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

SPVM_OP* SPVM_OP_build_assignop(SPVM_COMPILER* compiler, SPVM_OP* op_assign, SPVM_OP* op_first, SPVM_OP* op_last) {
  
  // Build op
  SPVM_OP_insert_child(compiler, op_assign, op_assign->last, op_first);
  SPVM_OP_insert_child(compiler, op_assign, op_assign->last, op_last);
  
  // Return variable if first children is var
  if (op_first->code == SPVM_OP_C_CODE_VAR) {
    SPVM_OP* op_var = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_VAR, op_assign->file, op_assign->line);
    op_var->uv.var = op_first->uv.var;
    SPVM_OP_insert_child(compiler, op_var, op_var->last, op_assign);
    
    return op_var;
  }
  else {
    return op_assign;
  }
}


SPVM_OP* SPVM_OP_build_type_name(SPVM_COMPILER* compiler, SPVM_OP* op_name) {
  
  // 
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->code = SPVM_TYPE_C_CODE_NAME;
  type->uv.op_name = op_name;

  SPVM_OP* op_type_name = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_TYPE, op_name->file, op_name->line);
  SPVM_OP_insert_child(compiler, op_type_name, op_type_name->last, op_name);
  
  op_type_name->uv.type = type;
  op_type_name->file = op_name->file;
  op_type_name->line = op_name->line;

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
    constant->code = SPVM_CONSTANT_C_CODE_STRING;
    constant->uv.string_value = "Error";
    constant->type = SPVM_HASH_search(compiler->type_symtable, "byte[]", strlen("byte[]"));
    op_constant->uv.constant = constant;
    
    op_term = op_constant;
  }
  
  // Exception variable
  SPVM_OP* op_exception_var = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_EXCEPTION_VAR, op_term->file, op_term->line);
  
  // Assign
  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ASSIGN, op_term->file, op_term->line);
  SPVM_OP_insert_child(compiler, op_assign, op_assign->last, op_exception_var);
  SPVM_OP_insert_child(compiler, op_assign, op_assign->last, op_term);
  
  SPVM_OP_insert_child(compiler, op_die, op_die->last, op_assign);
  
  return op_die;
}

SPVM_OP* SPVM_OP_build_type_array(SPVM_COMPILER* compiler, SPVM_OP* op_type, SPVM_OP* op_term_length) {
  
  // Type
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->code = SPVM_TYPE_C_CODE_ARRAY;
  type->uv.op_type = op_type;
  
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
