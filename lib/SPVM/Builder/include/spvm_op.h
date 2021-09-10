#ifndef SPVM_OP_H
#define SPVM_OP_H

#include "spvm_typedecl.h"











































/* Operation id */
enum {
  SPVM_OP_C_ID_IF,
  SPVM_OP_C_ID_UNLESS,
  SPVM_OP_C_ID_ELSIF,
  SPVM_OP_C_ID_ELSE,
  SPVM_OP_C_ID_FOR,
  SPVM_OP_C_ID_WHILE,
  SPVM_OP_C_ID_NULL,
  SPVM_OP_C_ID_LIST,
  SPVM_OP_C_ID_PUSHMARK,
  SPVM_OP_C_ID_GRAMMAR,
  SPVM_OP_C_ID_NAME,
  SPVM_OP_C_ID_CLASS,
  SPVM_OP_C_ID_MY,
  SPVM_OP_C_ID_FIELD,
  SPVM_OP_C_ID_METHOD,
  SPVM_OP_C_ID_ENUM,
  SPVM_OP_C_ID_DESCRIPTOR,
  SPVM_OP_C_ID_ENUMERATION_VALUE,
  SPVM_OP_C_ID_BLOCK,
  SPVM_OP_C_ID_ENUM_BLOCK,
  SPVM_OP_C_ID_CLASS_BLOCK,
  SPVM_OP_C_ID_TYPE,
  SPVM_OP_C_ID_CONSTANT,
  SPVM_OP_C_ID_INC,
  SPVM_OP_C_ID_DEC,
  SPVM_OP_C_ID_PRE_INC,
  SPVM_OP_C_ID_POST_INC,
  SPVM_OP_C_ID_PRE_DEC,
  SPVM_OP_C_ID_POST_DEC,
  SPVM_OP_C_ID_MINUS,
  SPVM_OP_C_ID_PLUS,
  SPVM_OP_C_ID_ADD,
  SPVM_OP_C_ID_METHODTRACT,
  SPVM_OP_C_ID_MULTIPLY,
  SPVM_OP_C_ID_DIVIDE,
  SPVM_OP_C_ID_BIT_AND,
  SPVM_OP_C_ID_BIT_OR,
  SPVM_OP_C_ID_BIT_XOR,
  SPVM_OP_C_ID_BIT_NOT,
  SPVM_OP_C_ID_REMAINDER,
  SPVM_OP_C_ID_LEFT_SHIFT,
  SPVM_OP_C_ID_RIGHT_ARITHMETIC_SHIFT,
  SPVM_OP_C_ID_RIGHT_LOGICAL_SHIFT,
  SPVM_OP_C_ID_LOGICAL_AND,
  SPVM_OP_C_ID_LOGICAL_OR,
  SPVM_OP_C_ID_LOGICAL_NOT,
  SPVM_OP_C_ID_ARRAY_ACCESS,
  SPVM_OP_C_ID_ASSIGN,
  SPVM_OP_C_ID_CALL_METHOD,
  SPVM_OP_C_ID_FIELD_ACCESS,
  SPVM_OP_C_ID_USE,
  SPVM_OP_C_ID_RETURN,
  SPVM_OP_C_ID_LAST,
  SPVM_OP_C_ID_NEXT,
  SPVM_OP_C_ID_LOOP,
  SPVM_OP_C_ID_VAR,
  SPVM_OP_C_ID_CONVERT,
  SPVM_OP_C_ID_UNDEF,
  SPVM_OP_C_ID_ARRAY_LENGTH,
  SPVM_OP_C_ID_CONDITION,
  SPVM_OP_C_ID_CONDITION_NOT,
  SPVM_OP_C_ID_DIE,
  SPVM_OP_C_ID_SWITCH,
  SPVM_OP_C_ID_CASE,
  SPVM_OP_C_ID_DEFAULT,
  SPVM_OP_C_ID_SWITCH_CONDITION,
  SPVM_OP_C_ID_VOID,
  SPVM_OP_C_ID_EVAL,
  SPVM_OP_C_ID_BLOCK_END,
  SPVM_OP_C_ID_EXCEPTION_VAR,
  SPVM_OP_C_ID_NEW,
  SPVM_OP_C_ID_STAB,
  SPVM_OP_C_ID_BYTE,
  SPVM_OP_C_ID_SHORT,
  SPVM_OP_C_ID_INT,
  SPVM_OP_C_ID_LONG,
  SPVM_OP_C_ID_FLOAT,
  SPVM_OP_C_ID_DOUBLE,
  SPVM_OP_C_ID_STRING,
  SPVM_OP_C_ID_OBJECT,
  SPVM_OP_C_ID_WEAKEN,
  SPVM_OP_C_ID_WEAKEN_FIELD,
  SPVM_OP_C_ID_UNWEAKEN,
  SPVM_OP_C_ID_UNWEAKEN_FIELD,
  SPVM_OP_C_ID_ISWEAK,
  SPVM_OP_C_ID_ISWEAK_FIELD,
  SPVM_OP_C_ID_SPECIAL_ASSIGN,
  SPVM_OP_C_ID_CONCAT,
  SPVM_OP_C_ID_SET,
  SPVM_OP_C_ID_GET,
  SPVM_OP_C_ID_CLASS_VAR,
  SPVM_OP_C_ID_CLASS_VAR_ACCESS,
  SPVM_OP_C_ID_ARRAY_INIT,
  SPVM_OP_C_ID_BOOL,
  SPVM_OP_C_ID_LOOP_INCREMENT,
  SPVM_OP_C_ID_SELF,
  SPVM_OP_C_ID_CHECK_CONVERT,
  SPVM_OP_C_ID_NUMERIC_EQ,
  SPVM_OP_C_ID_NUMERIC_NE,
  SPVM_OP_C_ID_NUMERIC_LT,
  SPVM_OP_C_ID_NUMERIC_LE,
  SPVM_OP_C_ID_NUMERIC_GT,
  SPVM_OP_C_ID_NUMERIC_GE,
  SPVM_OP_C_ID_NUMERIC_CMP,
  SPVM_OP_C_ID_STRING_EQ,
  SPVM_OP_C_ID_STRING_NE,
  SPVM_OP_C_ID_STRING_GT,
  SPVM_OP_C_ID_STRING_GE,
  SPVM_OP_C_ID_STRING_LT,
  SPVM_OP_C_ID_STRING_LE,
  SPVM_OP_C_ID_STRING_CMP,
  SPVM_OP_C_ID_ISA,
  SPVM_OP_C_ID_SEQUENCE,
  SPVM_OP_C_ID_PRECOMPILE,
  SPVM_OP_C_ID_SCALAR,
  SPVM_OP_C_ID_ARRAY_FIELD_ACCESS,
  SPVM_OP_C_ID_CREATE_REF,
  SPVM_OP_C_ID_DEREF,
  SPVM_OP_C_ID_DOT3,
  SPVM_OP_C_ID_STRING_LENGTH,
  SPVM_OP_C_ID_RW,
  SPVM_OP_C_ID_RO,
  SPVM_OP_C_ID_WO,
  SPVM_OP_C_ID_INIT,
  SPVM_OP_C_ID_REQUIRE,
  SPVM_OP_C_ID_IF_REQUIRE,
  SPVM_OP_C_ID_CURRENT_CLASS,
  SPVM_OP_C_ID_FREE_TMP,
  SPVM_OP_C_ID_REFCNT,
  SPVM_OP_C_ID_ALLOW,
  SPVM_OP_C_ID_BREAK,
  SPVM_OP_C_ID_WARN,
  SPVM_OP_C_ID_PRINT,
  SPVM_OP_C_ID_REFOP,
  SPVM_OP_C_ID_DUMP,
};

const char* const* SPVM_OP_C_ID_NAMES(void);

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
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_METHODTRACT,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_MULTIPLY,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_DIVIDE,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_REMAINDER,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_LEFT_SHIFT,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_ARITHMETIC_SHIFT,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_LOGICAL_SHIFT,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_XOR,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_OR,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_AND,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_CONCAT,
};

enum {
  // FIELD_ACCESS flag
  SPVM_OP_C_FLAG_FIELD_ACCESS_WEAKEN = 1,
  SPVM_OP_C_FLAG_FIELD_ACCESS_UNWEAKEN = 2,
  SPVM_OP_C_FLAG_FIELD_ACCESS_ISWEAK = 4,
};
enum {
  // ARRAY_ACCESS flag
  SPVM_OP_C_FLAG_ARRAY_ACCESS_WEAKEN = 1,
  SPVM_OP_C_FLAG_ARRAY_ACCESS_CONST = 2,
  SPVM_OP_C_FLAG_ARRAY_ACCESS_UNWEAKEN = 4,
  SPVM_OP_C_FLAG_ARRAY_ACCESS_ISWEAK = 8,
};

enum {
  // NEW flag
  SPVM_OP_C_FLAG_NEW_INLINE = 1,
};

enum {
  // ARRAY_INIT flag
  SPVM_OP_C_FLAG_ARRAY_INIT_IS_KEY_VALUES = 1,
};

/* Binary operation */
struct spvm_op {
  SPVM_OP* first;
  SPVM_OP* last;
  SPVM_OP* sibparent;
  const char* file;
  union {
    const char* name;
    SPVM_MY* my;
    SPVM_METHOD* method;
    SPVM_CONSTANT* constant;
    SPVM_TYPE* type;
    SPVM_VAR* var;
    SPVM_FIELD* field;
    SPVM_CLASS* class;
    SPVM_ENUMERATION* enumeration;
    SPVM_SWITCH_INFO* switch_info;
    SPVM_CASE_INFO* case_info;
    SPVM_USE* use;
    SPVM_ALLOW* allow;
    SPVM_CALL_METHOD* call_spvm_method;
    SPVM_FIELD_ACCESS* field_access;
    SPVM_ARRAY_FIELD_ACCESS* array_field_access;
    SPVM_CLASS_VAR* class_var;
    SPVM_CLASS_VAR_ACCESS* class_var_access;
    SPVM_BLOCK* block;
    SPVM_DESCRIPTOR* descriptor;
  } uv;
  int32_t id;
  int32_t flag;
  int32_t line;
  int32_t keyword_start_pos;
  int8_t moresib;
  int8_t is_lvalue;
  int8_t is_assigned_to_var;
  int8_t is_passed_to_method;
  int8_t no_need_check;
  int8_t free_tmp_vars;
};

SPVM_OP* SPVM_OP_build_expression_statement(SPVM_COMPILER* compiler, SPVM_OP* op_expression);
SPVM_OP* SPVM_OP_build_if_require_statement(SPVM_COMPILER* compiler, SPVM_OP* op_if_require, SPVM_OP* op_use, SPVM_OP* op_block_true, SPVM_OP* op_block_false);
SPVM_OP* SPVM_OP_build_var(SPVM_COMPILER* compiler, SPVM_OP* op_var_name);
SPVM_OP* SPVM_OP_build_enumeration_value(SPVM_COMPILER* compiler, SPVM_OP* op_name, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_new(SPVM_COMPILER* compiler, SPVM_OP* op_new, SPVM_OP* op_type, SPVM_OP* op_list_elements);
SPVM_OP* SPVM_OP_build_and(SPVM_COMPILER* compiler, SPVM_OP* op_and, SPVM_OP* op_first, SPVM_OP* op_last);
SPVM_OP* SPVM_OP_build_or(SPVM_COMPILER* compiler, SPVM_OP* op_or, SPVM_OP* op_first, SPVM_OP* op_last);
SPVM_OP* SPVM_OP_build_not(SPVM_COMPILER* compiler, SPVM_OP* op_not, SPVM_OP* op_first);
SPVM_OP* SPVM_OP_build_isa(SPVM_COMPILER* compiler, SPVM_OP* op_isa, SPVM_OP* op_term, SPVM_OP* op_type);
SPVM_OP* SPVM_OP_build_return(SPVM_COMPILER* compiler, SPVM_OP* op_return, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_die(SPVM_COMPILER* compiler, SPVM_OP* op_die, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_warn(SPVM_COMPILER* compiler, SPVM_OP* op_warn, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_print(SPVM_COMPILER* compiler, SPVM_OP* op_print, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_eval(SPVM_COMPILER* compiler, SPVM_OP* op_eval, SPVM_OP* op_block);
SPVM_OP* SPVM_OP_build_switch_statement(SPVM_COMPILER* compiler, SPVM_OP* op_switch, SPVM_OP* op_term, SPVM_OP* op_block);
SPVM_OP* SPVM_OP_build_switch_block(SPVM_COMPILER* compiler, SPVM_OP* op_switch_block, SPVM_OP* op_case_statements, SPVM_OP* op_default_statement);
SPVM_OP* SPVM_OP_build_default_statement(SPVM_COMPILER* compiler, SPVM_OP* op_default, SPVM_OP* op_block);
SPVM_OP* SPVM_OP_build_case_statement(SPVM_COMPILER* compiler, SPVM_OP* op_case, SPVM_OP* op_term, SPVM_OP* op_block);
SPVM_OP* SPVM_OP_build_logical_op(SPVM_COMPILER* compiler, SPVM_OP* op_logical_op, SPVM_OP* op_first, SPVM_OP* op_last);
SPVM_OP* SPVM_OP_build_for_statement(SPVM_COMPILER* compiler, SPVM_OP* op_for, SPVM_OP* op_term_loop_var, SPVM_OP* op_term_condition, SPVM_OP* op_term_next_value, SPVM_OP* op_block);
SPVM_OP* SPVM_OP_build_while_statement(SPVM_COMPILER* compiler, SPVM_OP* op_while, SPVM_OP* op_term_condition, SPVM_OP* op_block);
SPVM_OP* SPVM_OP_build_if_statement(SPVM_COMPILER* compiler, SPVM_OP* op_if, SPVM_OP* op_term, SPVM_OP* op_block, SPVM_OP* op_else_statement);
SPVM_OP* SPVM_OP_build_array_length(SPVM_COMPILER* compiler, SPVM_OP* op_array_length, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_malloc_object(SPVM_COMPILER* compiler, SPVM_OP* op_malloc, SPVM_OP* op_type);
SPVM_OP* SPVM_OP_build_comparison_op(SPVM_COMPILER* compiler, SPVM_OP* op_comparison, SPVM_OP* op_first, SPVM_OP* op_last);
SPVM_OP* SPVM_OP_build_binary_op(SPVM_COMPILER* compiler, SPVM_OP* op_call_op, SPVM_OP* op_first, SPVM_OP* op_last);
SPVM_OP* SPVM_OP_build_basic_type(SPVM_COMPILER* compiler, SPVM_OP* op_type_name);
SPVM_OP* SPVM_OP_build_array_type(SPVM_COMPILER* compiler, SPVM_OP* op_type, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_ref_type(SPVM_COMPILER* compiler, SPVM_OP* op_type_original);
SPVM_OP* SPVM_OP_build_field_access(SPVM_COMPILER* compiler, SPVM_OP* op_name_class, SPVM_OP* op_name_field);
SPVM_OP* SPVM_OP_build_class(SPVM_COMPILER* compiler, SPVM_OP* op_class, SPVM_OP* op_name_class, SPVM_OP* op_block, SPVM_OP* op_list_descriptors);
SPVM_OP* SPVM_OP_build_method(SPVM_COMPILER* compiler, SPVM_OP* op_method, SPVM_OP* op_methodname, SPVM_OP* op_return_type, SPVM_OP* op_args, SPVM_OP* op_descriptors, SPVM_OP* op_block, SPVM_OP* op_list_captures, SPVM_OP* op_dot3, int32_t is_begin, int32_t is_new_callback_object, int32_t can_precompile);
SPVM_OP* SPVM_OP_build_CONSTVALUE(SPVM_COMPILER* compiler, SPVM_OP* op_const);
SPVM_OP* SPVM_OP_build_has(SPVM_COMPILER* compiler, SPVM_OP* op_field, SPVM_OP* op_field_base_name, SPVM_OP* op_descripters, SPVM_OP* type);
SPVM_OP* SPVM_OP_build_our(SPVM_COMPILER* compiler, SPVM_OP* class_var, SPVM_OP* op_class_var_name, SPVM_OP* op_descriptors, SPVM_OP* op_type);
SPVM_OP* SPVM_OP_build_my(SPVM_COMPILER* compiler, SPVM_OP* op_my, SPVM_OP* op_var, SPVM_OP* op_type);
SPVM_OP* SPVM_OP_build_arg(SPVM_COMPILER* compiler, SPVM_OP* op_var, SPVM_OP* op_type);
SPVM_OP* SPVM_OP_build_grammar(SPVM_COMPILER* compiler, SPVM_OP* op_classes);
SPVM_OP* SPVM_OP_build_use(SPVM_COMPILER* compiler, SPVM_OP* op_use, SPVM_OP* op_type, SPVM_OP* method_names, int32_t is_require);
SPVM_OP* SPVM_OP_build_allow(SPVM_COMPILER* compiler, SPVM_OP* op_use, SPVM_OP* op_type);
SPVM_OP* SPVM_OP_build_call_spvm_method(SPVM_COMPILER* compiler, SPVM_OP* op_invocant, SPVM_OP* op_methodname, SPVM_OP* op_terms);
SPVM_OP* SPVM_OP_build_convert(SPVM_COMPILER* compiler, SPVM_OP* op_convert, SPVM_OP* op_type, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_enumeration(SPVM_COMPILER* compiler, SPVM_OP* op_enumeration, SPVM_OP* op_enumeration_block, SPVM_OP* op_descripters);
SPVM_OP* SPVM_OP_build_unary_op(SPVM_COMPILER* compiler, SPVM_OP* op_unary, SPVM_OP* op_first);
SPVM_OP* SPVM_OP_build_array_access(SPVM_COMPILER* compiler, SPVM_OP* op_var, SPVM_OP* op_term);
SPVM_OP* SPVM_OP_build_assign(SPVM_COMPILER* compiler, SPVM_OP* op_assign, SPVM_OP* op_first, SPVM_OP* op_last);
SPVM_OP* SPVM_OP_build_weaken_field(SPVM_COMPILER* compiler, SPVM_OP* op_weaken, SPVM_OP* op_field_access);
SPVM_OP* SPVM_OP_build_unweaken_field(SPVM_COMPILER* compiler, SPVM_OP* op_unweaken, SPVM_OP* op_field_access);
SPVM_OP* SPVM_OP_build_isweak_field(SPVM_COMPILER* compiler, SPVM_OP* op_isweak, SPVM_OP* op_field_access);
SPVM_OP* SPVM_OP_build_array_init(SPVM_COMPILER* compiler, SPVM_OP* op_array_init, SPVM_OP* op_list_elements, int32_t is_key_values);
SPVM_OP* SPVM_OP_build_inc(SPVM_COMPILER* compiler, SPVM_OP* op_inc, SPVM_OP* op_first);
SPVM_OP* SPVM_OP_build_dec(SPVM_COMPILER* compiler, SPVM_OP* op_dec, SPVM_OP* op_first);
SPVM_OP* SPVM_OP_build_special_assign(SPVM_COMPILER* compiler, SPVM_OP* op_special_assign, SPVM_OP* op_term_dist, SPVM_OP* op_term_src);
SPVM_OP* SPVM_OP_build_class_var_access(SPVM_COMPILER* compiler, SPVM_OP* op_class_var_name);

SPVM_OP* SPVM_OP_new_op_assign_bool(SPVM_COMPILER* compiler, SPVM_OP* op_operand, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_my(SPVM_COMPILER* compiler, SPVM_MY* my, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_type(SPVM_COMPILER* compiler, SPVM_TYPE* type, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_block(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_name(SPVM_COMPILER* compiler, const char* name, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_var(SPVM_COMPILER* compiler, SPVM_OP* op_name);
SPVM_OP* SPVM_OP_new_op_class_var_access(SPVM_COMPILER* compiler, SPVM_OP* op_name);
SPVM_OP* SPVM_OP_new_op_undef(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_descriptor(SPVM_COMPILER* compiler, int32_t id, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_void(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_constant_byte(SPVM_COMPILER* compiler, int8_t value, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_constant_short(SPVM_COMPILER* compiler, int16_t value, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_constant_int(SPVM_COMPILER* compiler, int32_t value, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_constant_long(SPVM_COMPILER* compiler, int64_t value, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_constant_float(SPVM_COMPILER* compiler, float value, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_constant_double(SPVM_COMPILER* compiler, double value, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_constant_string(SPVM_COMPILER* compiler, const char* string, int32_t length, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_constant_byte_array_string(SPVM_COMPILER* compiler, char* string, int32_t length, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_var_from_op_my(SPVM_COMPILER* compiler, SPVM_OP* op_my, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_list(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op(SPVM_COMPILER* compiler, int32_t id, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_var_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_var, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_byte_type(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_short_type(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_int_type(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_long_type(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_float_type(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_double_type(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_string_type(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_undef_type(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_byte_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_short_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_int_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_long_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_float_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_double_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_string_type(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_any_object_type(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_void_type(SPVM_COMPILER* compiler, const char* file, int32_t line);
SPVM_OP* SPVM_OP_new_op_var_clone_var_or_assign(SPVM_COMPILER* compiler, SPVM_OP* original_op_var_or_assign);
SPVM_OP* SPVM_OP_new_op_field_access_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_field_access);
SPVM_OP* SPVM_OP_new_op_array_access_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_array_access);
SPVM_OP* SPVM_OP_new_op_array_field_access_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_array_field_access);
SPVM_OP* SPVM_OP_new_op_class_var_access_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_class_var_access);
SPVM_OP* SPVM_OP_new_op_deref_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_deref);
SPVM_OP* SPVM_OP_new_op_term_mutable_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_term_mutable);

int32_t SPVM_OP_is_allowed(SPVM_COMPILER* compiler, SPVM_OP* op_class_current, SPVM_OP* op_class_dist);
const char* SPVM_OP_get_var_name(SPVM_COMPILER* compiler, SPVM_OP* op_var);
int32_t SPVM_OP_get_mem_id(SPVM_COMPILER* compiler, SPVM_OP* op);
void SPVM_OP_insert_to_most_left_deep_child(SPVM_COMPILER* compiler, SPVM_OP* op_parent, SPVM_OP* op_child);

SPVM_OP* SPVM_OP_get_parent(SPVM_COMPILER* compiler, SPVM_OP* op_target);
void SPVM_OP_get_before(SPVM_COMPILER* compiler, SPVM_OP* op_target, SPVM_OP** op_before_ptr, int32_t* next_is_child_ptr);

SPVM_OP* SPVM_OP_cut_op(SPVM_COMPILER* compiler, SPVM_OP* op_target);
void SPVM_OP_replace_op(SPVM_COMPILER* compiler, SPVM_OP* op_target, SPVM_OP* op_replace);

SPVM_OP* SPVM_OP_fold_constant(SPVM_COMPILER* compiler, SPVM_OP* op_cur);

SPVM_OP* SPVM_OP_get_op_block_from_op_method(SPVM_COMPILER* compiler, SPVM_OP* op_method);
SPVM_TYPE* SPVM_OP_get_type(SPVM_COMPILER* compiler, SPVM_OP* op);

void SPVM_OP_convert_to_op_constant_true(SPVM_COMPILER* compiler, SPVM_OP* op);
void SPVM_OP_convert_to_op_constant_false(SPVM_COMPILER* compiler, SPVM_OP* op);

void SPVM_OP_resolve_op_convert_type(SPVM_COMPILER* compiler, SPVM_OP* op_convert_type);

void SPVM_OP_insert_child(SPVM_COMPILER* compiler, SPVM_OP* parent, SPVM_OP* start, SPVM_OP* insert);

int32_t SPVM_OP_is_op_term_mutable(SPVM_COMPILER* compiler, SPVM_OP* op);

SPVM_OP* SPVM_OP_sibling(SPVM_COMPILER* compiler, SPVM_OP* op);

int32_t SPVM_OP_get_list_elements_count(SPVM_COMPILER* compiler, SPVM_OP* op_list);

#endif
