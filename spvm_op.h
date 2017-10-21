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
  SPVM_OP_C_CODE_MY,
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
  SPVM_OP_C_CODE_ARRAY_LENGTH,
  SPVM_OP_C_CODE_CONDITION,
  SPVM_OP_C_CODE_CROAK,
  SPVM_OP_C_CODE_SWITCH,
  SPVM_OP_C_CODE_CASE,
  SPVM_OP_C_CODE_DEFAULT,
  SPVM_OP_C_CODE_SWITCH_CONDITION,
  SPVM_OP_C_CODE_VOID,
  SPVM_OP_C_CODE_EVAL,
  SPVM_OP_C_CODE_BLOCK_END,
  SPVM_OP_C_CODE_EXCEPTION_VAR,
  SPVM_OP_C_CODE_ASSIGN_PROCESS,
  SPVM_OP_C_CODE_NEW,
  SPVM_OP_C_CODE_STAB,
  SPVM_OP_C_CODE_BYTE,
  SPVM_OP_C_CODE_SHORT,
  SPVM_OP_C_CODE_INT,
  SPVM_OP_C_CODE_LONG,
  SPVM_OP_C_CODE_FLOAT,
  SPVM_OP_C_CODE_DOUBLE,
  SPVM_OP_C_CODE_STRING,
  SPVM_OP_C_CODE_WEAKEN,
  SPVM_OP_C_CODE_WEAKEN_FIELD,
  SPVM_OP_C_CODE_SPECIAL_ASSIGN,
  SPVM_OP_C_CODE_CONCAT_STRING,
  SPVM_OP_C_CODE_SET,
  SPVM_OP_C_CODE_GET,
  SPVM_OP_C_CODE_OUR,
  SPVM_OP_C_CODE_PACKAGE_VAR,
};

extern const char* const SPVM_OP_C_CODE_NAMES[];

enum {
  // Block flag
  SPVM_OP_C_FLAG_BLOCK_IF_TRUE = 1,
  SPVM_OP_C_FLAG_BLOCK_IF_FALSE = 2,
  SPVM_OP_C_FLAG_BLOCK_LOOP = 4,
  SPVM_OP_C_FLAG_BLOCK_SWITCH = 8,
  SPVM_OP_C_FLAG_BLOCK_SUB = 32,
  SPVM_OP_C_FLAG_BLOCK_EVAL = 64,
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

enum {
  // Assign flag
  SPVM_OP_C_FLAG_ASSIGN_TMP_VAR = 1
};

enum {
  // Special assign flag
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_ADD,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_SUBTRACT,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_MULTIPLY,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_DIVIDE,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_REMAINDER,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_LEFT_SHIFT,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_SHIFT,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_SHIFT_UNSIGNED,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_XOR,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_OR,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_AND,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_CONCAT_STRING,
};

enum {
  // CALL_FIELD flag
  SPVM_OP_C_FLAG_CALL_FIELD_WEAKEN = 1
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
    SPVM_TYPE* type;
    SPVM_VAR* var;
    SPVM_FIELD* field;
    SPVM_PACKAGE* package;
    SPVM_ENUMERATION* enumeration;
    SPVM_SWITCH_INFO* switch_info;
    SPVM_USE* use;
    SPVM_CALL_SUB* call_sub;
    SPVM_CALL_FIELD* call_field;
    SPVM_OUR* our;
    SPVM_PACKAGE_VAR* package_var;
  } uv;
  int32_t code;
  int32_t flag;
  int32_t line;
  _Bool moresib;
  _Bool lvalue;
  _Bool rvalue;
};

void SPVM_OP_resolve_package_var(SPVM_COMPILER* compiler, SPVM_OP* op_package_var);

SPVM_OP* SPVM_OP_build_setters(SPVM_COMPILER* compiler, SPVM_OP* op_set, SPVM_OP* op_names);
SPVM_OP* SPVM_OP_build_getters(SPVM_COMPILER* compiler, SPVM_OP* op_get, SPVM_OP* op_names);


SPVM_OP* SPVM_OP_new_op_name(SPVM_COMPILER* compiler, const char* name, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_var(SPVM_COMPILER* compiler, SPVM_OP* op_name);
SPVM_OP* SPVM_OP_new_op_package_var(SPVM_COMPILER* compiler, SPVM_OP* op_name);

SPVM_OP* SPVM_OP_get_parent(SPVM_COMPILER* compiler, SPVM_OP* op_target);
void SPVM_OP_get_before(SPVM_COMPILER* compiler, SPVM_OP* op_target, SPVM_OP** op_before_ptr, _Bool* next_is_child_ptr);

void SPVM_OP_build_constant_pool(SPVM_COMPILER* compiler);
SPVM_OP* SPVM_OP_cut_op(SPVM_COMPILER* compiler, SPVM_OP* op_target);
void SPVM_OP_replace_op(SPVM_COMPILER* compiler, SPVM_OP* op_target, SPVM_OP* op_replace);
SPVM_OP* SPVM_OP_build_void(SPVM_COMPILER* compiler, SPVM_OP* op_void);

SPVM_OP* SPVM_OP_build_enumeration_value(SPVM_COMPILER* compiler, SPVM_OP* op_name, SPVM_OP* op_term);

SPVM_OP* SPVM_OP_build_new_object(SPVM_COMPILER* compiler, SPVM_OP* op_new, SPVM_OP* op_type);

SPVM_OP* SPVM_OP_build_and(SPVM_COMPILER* compiler, SPVM_OP* op_and, SPVM_OP* op_first, SPVM_OP* op_last);
SPVM_OP* SPVM_OP_build_or(SPVM_COMPILER* compiler, SPVM_OP* op_or, SPVM_OP* op_first, SPVM_OP* op_last);
SPVM_OP* SPVM_OP_build_not(SPVM_COMPILER* compiler, SPVM_OP* op_not, SPVM_OP* op_first);

void SPVM_OP_resolve_constant(SPVM_COMPILER* compiler, SPVM_OP* op_constant);
SPVM_OP* SPVM_OP_fold_constant(SPVM_COMPILER* compiler, SPVM_OP* op_cur);

SPVM_OP* SPVM_OP_new_op_use_from_package_name(SPVM_COMPILER* compiler, const char* package_name, const char* file, int32_t line);

SPVM_OP* SPVM_OP_get_op_block_from_op_sub(SPVM_COMPILER* compiler, SPVM_OP* op_sub);
SPVM_TYPE* SPVM_OP_get_type(SPVM_COMPILER* compiler, SPVM_OP* op);

void SPVM_OP_convert_to_op_constant_true(SPVM_COMPILER* compiler, SPVM_OP* op);
void SPVM_OP_convert_to_op_constant_false(SPVM_COMPILER* compiler, SPVM_OP* op);

void SPVM_OP_resolve_call_sub(SPVM_COMPILER* compiler, SPVM_OP* op_call_sub);
void SPVM_OP_resolve_call_field(SPVM_COMPILER* compiler, SPVM_OP* op_call_field);

SPVM_OP* SPVM_OP_build_concat_string(SPVM_COMPILER* compiler, SPVM_OP* op_cancat_string, SPVM_OP* op_first, SPVM_OP* op_last);
SPVM_OP* SPVM_OP_build_return(SPVM_COMPILER* compiler, SPVM_OP* op_return, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_croak(SPVM_COMPILER* compiler, SPVM_OP* op_croak, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_eval(SPVM_COMPILER* compiler, SPVM_OP* op_eval, SPVM_OP* op_block);
SPVM_OP* SPVM_OP_build_switch_statement(SPVM_COMPILER* compiler, SPVM_OP* op_switch, SPVM_OP* op_term, SPVM_OP* op_block);
SPVM_OP* SPVM_OP_build_case_statement(SPVM_COMPILER* compiler, SPVM_OP* op_case, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_logical_op(SPVM_COMPILER* compiler, SPVM_OP* op_logical_op, SPVM_OP* op_first, SPVM_OP* op_last);
SPVM_OP* SPVM_OP_build_for_statement(SPVM_COMPILER* compiler, SPVM_OP* op_for, SPVM_OP* op_term_loop_var, SPVM_OP* op_term_condition, SPVM_OP* op_term_next_value, SPVM_OP* op_block);
SPVM_OP* SPVM_OP_build_while_statement(SPVM_COMPILER* compiler, SPVM_OP* op_while, SPVM_OP* op_term_condition, SPVM_OP* op_block);
SPVM_OP* SPVM_OP_build_if_statement(SPVM_COMPILER* compiler, SPVM_OP* op_if, SPVM_OP* op_term, SPVM_OP* op_block, SPVM_OP* op_else_statement);
SPVM_OP* SPVM_OP_build_array_length(SPVM_COMPILER* compiler, SPVM_OP* op_array_length, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_malloc_object(SPVM_COMPILER* compiler, SPVM_OP* op_malloc, SPVM_OP* op_type);
SPVM_OP* SPVM_OP_build_array_init(SPVM_COMPILER* compiler, SPVM_OP* op_opt_terms);
SPVM_OP* SPVM_OP_build_binop(SPVM_COMPILER* compiler, SPVM_OP* op_call_op, SPVM_OP* op_first, SPVM_OP* op_last);
SPVM_OP* SPVM_OP_build_type_byte(SPVM_COMPILER* compiler, SPVM_OP* op_byte);
SPVM_OP* SPVM_OP_build_type_short(SPVM_COMPILER* compiler, SPVM_OP* op_short);
SPVM_OP* SPVM_OP_build_type_int(SPVM_COMPILER* compiler, SPVM_OP* op_int);
SPVM_OP* SPVM_OP_build_type_long(SPVM_COMPILER* compiler, SPVM_OP* op_long);
SPVM_OP* SPVM_OP_build_type_float(SPVM_COMPILER* compiler, SPVM_OP* op_float);
SPVM_OP* SPVM_OP_build_type_double(SPVM_COMPILER* compiler, SPVM_OP* op_double);
SPVM_OP* SPVM_OP_build_type_string(SPVM_COMPILER* compiler, SPVM_OP* op_string);
SPVM_OP* SPVM_OP_build_type_name(SPVM_COMPILER* compiler, SPVM_OP* op_type_name);
SPVM_OP* SPVM_OP_build_type_array(SPVM_COMPILER* compiler, SPVM_OP* op_type, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_call_field(SPVM_COMPILER* compiler, SPVM_OP* op_name_package, SPVM_OP* op_name_field);
SPVM_OP* SPVM_OP_build_package(SPVM_COMPILER* compiler, SPVM_OP* op_package, SPVM_OP* op_name_package, SPVM_OP* op_block);
SPVM_OP* SPVM_OP_build_sub(SPVM_COMPILER* compiler, SPVM_OP* op_sub, SPVM_OP* op_subname, SPVM_OP* op_subargs, SPVM_OP* op_descriptors, SPVM_OP* type, SPVM_OP* op_block);
SPVM_OP* SPVM_OP_build_CONSTVALUE(SPVM_COMPILER* compiler, SPVM_OP* op_const);
SPVM_OP* SPVM_OP_build_field(SPVM_COMPILER* compiler, SPVM_OP* op_field, SPVM_OP* op_field_base_name, SPVM_OP* op_descripters, SPVM_OP* type);
SPVM_OP* SPVM_OP_build_our(SPVM_COMPILER* compiler, SPVM_OP* op_var, SPVM_OP* op_type);
SPVM_OP* SPVM_OP_build_my_var(SPVM_COMPILER* compiler, SPVM_OP* op_var, SPVM_OP* op_type);
SPVM_OP* SPVM_OP_build_grammar(SPVM_COMPILER* compiler, SPVM_OP* op_packages);
SPVM_OP* SPVM_OP_build_use(SPVM_COMPILER* compiler, SPVM_OP* op_use, SPVM_OP* op_name_package);
SPVM_OP* SPVM_OP_build_call_sub(SPVM_COMPILER* compiler, SPVM_OP* op_invocant, SPVM_OP* op_subname, SPVM_OP* op_terms);
SPVM_OP* SPVM_OP_build_convert_type(SPVM_COMPILER* compiler, SPVM_OP* op_type, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_enumeration(SPVM_COMPILER* compiler, SPVM_OP* op_enumeration, SPVM_OP* op_enumeration_block);
SPVM_OP* SPVM_OP_build_unop(SPVM_COMPILER* compiler, SPVM_OP* op_unary, SPVM_OP* op_first);
SPVM_OP* SPVM_OP_build_array_elem(SPVM_COMPILER* compiler, SPVM_OP* op_var, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_assign(SPVM_COMPILER* compiler, SPVM_OP* op_assign, SPVM_OP* op_first, SPVM_OP* op_last);
SPVM_OP* SPVM_OP_build_constant(SPVM_COMPILER* compiler, SPVM_OP* op_constant);
SPVM_OP* SPVM_OP_build_weaken_field(SPVM_COMPILER* compiler, SPVM_OP* op_weaken, SPVM_OP* op_call_field);

void SPVM_OP_resolve_op_convert_type(SPVM_COMPILER* compiler, SPVM_OP* op_convert_type);

const char* SPVM_OP_create_abs_name(SPVM_COMPILER* compiler, const char* package_name, const char* base_name);
const char* SPVM_OP_create_package_var_abs_name(SPVM_COMPILER* compiler, const char* package_name, const char* name);

SPVM_OP* SPVM_OP_new_op_constant_byte(SPVM_COMPILER* compiler, int8_t value, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_constant_short(SPVM_COMPILER* compiler, int16_t value, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_constant_int(SPVM_COMPILER* compiler, int32_t value, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_constant_long(SPVM_COMPILER* compiler, int64_t value, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_constant_float(SPVM_COMPILER* compiler, float value, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_constant_double(SPVM_COMPILER* compiler, double value, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_constant_string(SPVM_COMPILER* compiler, char* string, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_constant_byte_array_string(SPVM_COMPILER* compiler, char* string, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_var_from_op_my_var(SPVM_COMPILER* compiler, SPVM_OP* op_my_var);
SPVM_OP* SPVM_OP_new_op_list(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op(SPVM_COMPILER* compiler, int32_t code, const char* file, int32_t line);
void SPVM_OP_insert_child(SPVM_COMPILER* compiler, SPVM_OP* parent, SPVM_OP* start, SPVM_OP* insert);

SPVM_OP* SPVM_OP_sibling(SPVM_COMPILER* compiler, SPVM_OP* o);

#endif
