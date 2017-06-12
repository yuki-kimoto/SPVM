#ifndef SPVM_OP_H
#define SPVM_OP_H

#include "spvm_base.h"











































/* Operation code */
enum {
  SPVM_OP_C_CODE_IF,
  SPVM_OP_C_CODE_ELSIF,
  SPVM_OP_C_CODE_ELSE,
  SPVM_OP_C_CODE_FOR,
  SPVM_OP_C_CODE_WHILE,
  SPVM_OP_C_CODE_NULL,
  SPVM_OP_C_CODE_LIST,
  SPVM_OP_C_CODE_PUSHMARK,
  SPVM_OP_C_CODE_GRAMMAR,
  SPVM_OP_C_CODE_NAME,
  SPVM_OP_C_CODE_PACKAGE,
  SPVM_OP_C_CODE_MY_VAR,
  SPVM_OP_C_CODE_MY_VAR_INIT,
  SPVM_OP_C_CODE_FIELD,
  SPVM_OP_C_CODE_SUB,
  SPVM_OP_C_CODE_ENUM,
  SPVM_OP_C_CODE_DESCRIPTOR,
  SPVM_OP_C_CODE_ENUMERATION_VALUE,
  SPVM_OP_C_CODE_BLOCK,
  SPVM_OP_C_CODE_ENUM_BLOCK,
  SPVM_OP_C_CODE_CLASS_BLOCK,
  SPVM_OP_C_CODE_TYPE,
  SPVM_OP_C_CODE_CONSTANT,
  SPVM_OP_C_CODE_PRE_INC,
  SPVM_OP_C_CODE_POST_INC,
  SPVM_OP_C_CODE_PRE_DEC,
  SPVM_OP_C_CODE_POST_DEC,
  SPVM_OP_C_CODE_COMPLEMENT,
  SPVM_OP_C_CODE_NEGATE,
  SPVM_OP_C_CODE_PLUS,
  SPVM_OP_C_CODE_EQ,
  SPVM_OP_C_CODE_NE,
  SPVM_OP_C_CODE_LT,
  SPVM_OP_C_CODE_LE,
  SPVM_OP_C_CODE_GT,
  SPVM_OP_C_CODE_GE,
  SPVM_OP_C_CODE_ADD,
  SPVM_OP_C_CODE_SUBTRACT,
  SPVM_OP_C_CODE_MULTIPLY,
  SPVM_OP_C_CODE_DIVIDE,
  SPVM_OP_C_CODE_BIT_AND,
  SPVM_OP_C_CODE_BIT_OR,
  SPVM_OP_C_CODE_BIT_XOR,
  SPVM_OP_C_CODE_BIT_NOT,
  SPVM_OP_C_CODE_REMAINDER,
  SPVM_OP_C_CODE_LEFT_SHIFT,
  SPVM_OP_C_CODE_RIGHT_SHIFT,
  SPVM_OP_C_CODE_RIGHT_SHIFT_UNSIGNED,
  SPVM_OP_C_CODE_AND,
  SPVM_OP_C_CODE_OR,
  SPVM_OP_C_CODE_NOT,
  SPVM_OP_C_CODE_ARRAY_ELEM,
  SPVM_OP_C_CODE_ASSIGN,
  SPVM_OP_C_CODE_CALL_SUB,
  SPVM_OP_C_CODE_CALL_FIELD,
  SPVM_OP_C_CODE_USE,
  SPVM_OP_C_CODE_RETURN,
  SPVM_OP_C_CODE_LAST,
  SPVM_OP_C_CODE_NEXT,
  SPVM_OP_C_CODE_LOOP,
  SPVM_OP_C_CODE_VAR,
  SPVM_OP_C_CODE_CONVERT,
  SPVM_OP_C_CODE_POP,
  SPVM_OP_C_CODE_UNDEF,
  SPVM_OP_C_CODE_MALLOC,
  SPVM_OP_C_CODE_ARRAY_LENGTH,
  SPVM_OP_C_CODE_CONDITION,
  SPVM_OP_C_CODE_DIE,
  SPVM_OP_C_CODE_SWITCH,
  SPVM_OP_C_CODE_CASE,
  SPVM_OP_C_CODE_DEFAULT,
  SPVM_OP_C_CODE_SWITCH_CONDITION,
  SPVM_OP_C_CODE_VOID,
  SPVM_OP_C_CODE_TRY,
  SPVM_OP_C_CODE_CATCH,
  SPVM_OP_C_CODE_DEC_REF_COUNT,
  SPVM_OP_C_CODE_INC_REF_COUNT,
  SPVM_OP_C_CODE_FORMAL_ARGS,
  SPVM_OP_C_CODE_BLOCK_END,
  SPVM_OP_C_CODE_RETURN_PROCESS,
  SPVM_OP_C_CODE_LEAVE_SCOPE,
  SPVM_OP_C_CODE_DIE_PROCESS,
  SPVM_OP_C_CODE_STORE,
  SPVM_OP_C_CODE_LAST_PROCESS,
  SPVM_OP_C_CODE_NEXT_PROCESS,
};

extern const char* const SPVM_OP_C_CODE_NAMES[];

enum {
  // Block flag
  SPVM_OP_C_FLAG_BLOCK_IF = 1,
  SPVM_OP_C_FLAG_BLOCK_ELSE = 2,
  SPVM_OP_C_FLAG_BLOCK_LOOP = 4,
  SPVM_OP_C_FLAG_BLOCK_SWITCH = 8,
  SPVM_OP_C_FLAG_BLOCK_HAS_ELSE = 16,
  SPVM_OP_C_FLAG_BLOCK_SUB = 32,
  SPVM_OP_C_FLAG_BLOCK_TRY = 64,
};

enum {
  // Condition flag
  SPVM_OP_C_FLAG_CONDITION_IF = 1,
  SPVM_OP_C_FLAG_CONDITION_LOOP = 2,
};

enum {
  // Case flag
  SPVM_OP_C_FLAG_CONSTANT_CASE = 1,
};

/* Binary operation */
struct SPVM_op {
  SPVM_OP* first;
  SPVM_OP* last;
  SPVM_OP* sibparent;
  const char* file;
  union {
    const char* name;
    SPVM_MY_VAR* my_var;
    SPVM_SUB* sub;
    SPVM_CONSTANT* constant;
    SPVM_NAME_INFO* name_info;
    SPVM_TYPE* type;
    SPVM_VAR* var;
    SPVM_FIELD* field;
    SPVM_PACKAGE* package;
    SPVM_ENUMERATION* enumeration;
    SPVM_SWITCH_INFO* switch_info;
  } uv;
  int32_t code;
  int32_t flag;
  int32_t line;
  _Bool moresib;
  _Bool lvalue;
};


SPVM_OP* SPVM_OP_get_op_block_from_op_sub(SPVM_* spvm, SPVM_OP* op_sub);
SPVM_RESOLVED_TYPE* SPVM_OP_get_resolved_type(SPVM_* spvm, SPVM_OP* op);

void SPVM_OP_convert_to_op_constant_true(SPVM_* spvm, SPVM_OP* op);
void SPVM_OP_convert_to_op_constant_false(SPVM_* spvm, SPVM_OP* op);
void SPVM_OP_convert_not_to_if(SPVM_* spvm, SPVM_OP* op);
void SPVM_OP_convert_and_to_if(SPVM_* spvm, SPVM_OP* op);
void SPVM_OP_convert_or_to_if(SPVM_* spvm, SPVM_OP* op);

void SPVM_OP_resolve_type(SPVM_* spvm, SPVM_TYPE* type, int32_t name_length);

void SPVM_OP_resolve_sub_name(SPVM_* spvm, SPVM_OP* op_package, SPVM_OP* op_name);
void SPVM_OP_resolve_field_name(SPVM_* spvm, SPVM_OP* op_name);

SPVM_OP* SPVM_OP_build_last(SPVM_* spvm, SPVM_OP* op_last);
SPVM_OP* SPVM_OP_build_next(SPVM_* spvm, SPVM_OP* op_next);
SPVM_OP* SPVM_OP_build_return(SPVM_* spvm, SPVM_OP* op_return, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_die(SPVM_* spvm, SPVM_OP* op_die, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_try_catch(SPVM_* spvm, SPVM_OP* op_try, SPVM_OP* op_try_block, SPVM_OP* op_catch, SPVM_OP* op_my_var, SPVM_OP* op_catch_block);
SPVM_OP* SPVM_OP_build_switch_statement(SPVM_* spvm, SPVM_OP* op_switch, SPVM_OP* op_term, SPVM_OP* op_block);
SPVM_OP* SPVM_OP_build_case_statement(SPVM_* spvm, SPVM_OP* op_case, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_logical_op(SPVM_* spvm, SPVM_OP* op_logical_op, SPVM_OP* op_first, SPVM_OP* op_last);
SPVM_OP* SPVM_OP_build_for_statement(SPVM_* spvm, SPVM_OP* op_for, SPVM_OP* op_term_loop_var, SPVM_OP* op_term_condition, SPVM_OP* op_term_next_value, SPVM_OP* op_block);
SPVM_OP* SPVM_OP_build_while_statement(SPVM_* spvm, SPVM_OP* op_while, SPVM_OP* op_term_condition, SPVM_OP* op_block);
SPVM_OP* SPVM_OP_build_if_statement(SPVM_* spvm, SPVM_OP* op_if, SPVM_OP* op_term, SPVM_OP* op_block, SPVM_OP* op_else_statement);
SPVM_OP* SPVM_OP_build_array_length(SPVM_* spvm, SPVM_OP* op_array_length, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_malloc_object(SPVM_* spvm, SPVM_OP* op_malloc, SPVM_OP* op_type);
SPVM_OP* SPVM_OP_build_array_init(SPVM_* spvm, SPVM_OP* op_opt_terms);
SPVM_OP* SPVM_OP_build_binop(SPVM_* spvm, SPVM_OP* op_call_op, SPVM_OP* op_first, SPVM_OP* op_last);
SPVM_OP* SPVM_OP_build_type_name(SPVM_* spvm, SPVM_OP* op_type_name);
SPVM_OP* SPVM_OP_build_type_array(SPVM_* spvm, SPVM_OP* op_type, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_call_field(SPVM_* spvm, SPVM_OP* op_name_package, SPVM_OP* op_name_field);
SPVM_OP* SPVM_OP_build_package(SPVM_* spvm, SPVM_OP* op_package, SPVM_OP* op_name_package, SPVM_OP* op_block);
SPVM_OP* SPVM_OP_build_sub(SPVM_* spvm, SPVM_OP* op_sub, SPVM_OP* op_subname, SPVM_OP* op_subargs, SPVM_OP* op_descriptors, SPVM_OP* type, SPVM_OP* op_block);
SPVM_OP* SPVM_OP_build_CONSTVALUE(SPVM_* spvm, SPVM_OP* op_const);
SPVM_OP* SPVM_OP_build_field(SPVM_* spvm, SPVM_OP* op_field, SPVM_OP* op_field_base_name, SPVM_OP* type);
SPVM_OP* SPVM_OP_build_my_var(SPVM_* spvm, SPVM_OP* op_my, SPVM_OP* op_var, SPVM_OP* op_type, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_grammar(SPVM_* spvm, SPVM_OP* op_packages);
SPVM_OP* SPVM_OP_build_use(SPVM_* spvm, SPVM_OP* op_use, SPVM_OP* op_name_package);
SPVM_OP* SPVM_OP_build_call_sub(SPVM_* spvm, SPVM_OP* op_invocant, SPVM_OP* op_subname, SPVM_OP* op_terms);
SPVM_OP* SPVM_OP_build_convert_type(SPVM_* spvm, SPVM_OP* op_type, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_enumeration(SPVM_* spvm, SPVM_OP* op_enumeration, SPVM_OP* op_enumeration_block);
SPVM_OP* SPVM_OP_build_unop(SPVM_* spvm, SPVM_OP* op_unary, SPVM_OP* op_first);
SPVM_OP* SPVM_OP_build_array_elem(SPVM_* spvm, SPVM_OP* op_var, SPVM_OP* op_term);

void SPVM_OP_resolve_op_convert_type(SPVM_* spvm, SPVM_OP* op_convert_type);

const char* SPVM_OP_create_abs_name(SPVM_* spvm, const char* package_name, const char* base_name);

SPVM_OP* SPVM_OP_new_op_constant_int(SPVM_* spvm, int32_t value, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_constant_long(SPVM_* spvm, int64_t value, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_constant_float(SPVM_* spvm, float value, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_constant_double(SPVM_* spvm, double value, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_var_from_op_my_var(SPVM_* spvm, SPVM_OP* op_my_var);
SPVM_OP* SPVM_OP_new_op_list(SPVM_* spvm, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op(SPVM_* spvm, int32_t code, const char* file, int32_t line);

SPVM_OP* SPVM_OP_sibling_splice(SPVM_* spvm, SPVM_OP* parent, SPVM_OP* start, int32_t del_count, SPVM_OP *insert);
SPVM_OP* SPVM_OP_sibling(SPVM_* spvm, SPVM_OP* o);
void SPVM_OP_moresib_set(SPVM_* spvm, SPVM_OP* o, SPVM_OP* sib);
void SPVM_OP_lastsib_set(SPVM_* spvm, SPVM_OP* o, SPVM_OP* parent);
void SPVM_OP_maybesib_set(SPVM_* spvm, SPVM_OP* o, SPVM_OP* sib, SPVM_OP* parent);
SPVM_OP* SPVM_OP_append_elem(SPVM_* spvm, SPVM_OP *first, SPVM_OP *last, const char* file, int32_t line);


#endif
