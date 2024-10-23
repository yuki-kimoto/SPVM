// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_OP_H
#define SPVM_OP_H

#include "spvm_typedecl.h"


























































































/* Operation IDs */
enum {
  SPVM_OP_C_ID_GRAMMAR,
  SPVM_OP_C_ID_LIST,
  SPVM_OP_C_ID_PUSHMARK,
  SPVM_OP_C_ID_DO_NOTHING,
  SPVM_OP_C_ID_NAME,
  SPVM_OP_C_ID_ATTRIBUTE,
  SPVM_OP_C_ID_OUTMOST_CLASS,
  SPVM_OP_C_ID_CLASS,
  SPVM_OP_C_ID_EXTENDS,
  SPVM_OP_C_ID_CLASS_BLOCK,
  SPVM_OP_C_ID_END_OF_FILE,
  SPVM_OP_C_ID_VERSION_DECL,
  SPVM_OP_C_ID_IF,
  SPVM_OP_C_ID_UNLESS,
  SPVM_OP_C_ID_ELSIF,
  SPVM_OP_C_ID_ELSE,
  SPVM_OP_C_ID_CONDITION,
  SPVM_OP_C_ID_CONDITION_NOT,
  SPVM_OP_C_ID_SWITCH,
  SPVM_OP_C_ID_CASE,
  SPVM_OP_C_ID_DEFAULT,
  SPVM_OP_C_ID_SWITCH_CONDITION,
  SPVM_OP_C_ID_BREAK,
  SPVM_OP_C_ID_FOR,
  SPVM_OP_C_ID_WHILE,
  SPVM_OP_C_ID_LOOP,
  SPVM_OP_C_ID_LOOP_INCREMENT,
  SPVM_OP_C_ID_LAST,
  SPVM_OP_C_ID_NEXT,
  SPVM_OP_C_ID_VAR_DECL,
  SPVM_OP_C_ID_FIELD,
  SPVM_OP_C_ID_METHOD,
  SPVM_OP_C_ID_ENUM,
  SPVM_OP_C_ID_ENUMERATION_ITEM,
  SPVM_OP_C_ID_ENUM_BLOCK,
  SPVM_OP_C_ID_BLOCK,
  SPVM_OP_C_ID_EVAL,
  SPVM_OP_C_ID_TYPE,
  SPVM_OP_C_ID_MUTABLE,
  SPVM_OP_C_ID_VOID,
  SPVM_OP_C_ID_BYTE,
  SPVM_OP_C_ID_SHORT,
  SPVM_OP_C_ID_INT,
  SPVM_OP_C_ID_LONG,
  SPVM_OP_C_ID_FLOAT,
  SPVM_OP_C_ID_DOUBLE,
  SPVM_OP_C_ID_STRING,
  SPVM_OP_C_ID_OBJECT,
  SPVM_OP_C_ID_DOT3,
  SPVM_OP_C_ID_OF,
  SPVM_OP_C_ID_USE,
  SPVM_OP_C_ID_AS,
  SPVM_OP_C_ID_ALIAS,
  SPVM_OP_C_ID_REQUIRE,
  SPVM_OP_C_ID_IF_REQUIRE,
  SPVM_OP_C_ID_INIT,
  SPVM_OP_C_ID_INTERFACE,
  SPVM_OP_C_ID_ALLOW,
  SPVM_OP_C_ID_DIE,
  SPVM_OP_C_ID_RETURN,
  SPVM_OP_C_ID_CONSTANT,
  SPVM_OP_C_ID_MINUS,
  SPVM_OP_C_ID_PLUS,
  SPVM_OP_C_ID_INC,
  SPVM_OP_C_ID_DEC,
  SPVM_OP_C_ID_PRE_INC,
  SPVM_OP_C_ID_POST_INC,
  SPVM_OP_C_ID_PRE_DEC,
  SPVM_OP_C_ID_POST_DEC,
  SPVM_OP_C_ID_ADD,
  SPVM_OP_C_ID_SUBTRACT,
  SPVM_OP_C_ID_MULTIPLY,
  SPVM_OP_C_ID_DIVIDE,
  SPVM_OP_C_ID_DIVIDE_UNSIGNED_INT,
  SPVM_OP_C_ID_DIVIDE_UNSIGNED_LONG,
  SPVM_OP_C_ID_BIT_AND,
  SPVM_OP_C_ID_BIT_OR,
  SPVM_OP_C_ID_BIT_XOR,
  SPVM_OP_C_ID_BIT_NOT,
  SPVM_OP_C_ID_MODULO,
  SPVM_OP_C_ID_MODULO_UNSIGNED_INT,
  SPVM_OP_C_ID_MODULO_UNSIGNED_LONG,
  SPVM_OP_C_ID_LEFT_SHIFT,
  SPVM_OP_C_ID_RIGHT_ARITHMETIC_SHIFT,
  SPVM_OP_C_ID_RIGHT_LOGICAL_SHIFT,
  SPVM_OP_C_ID_LOGICAL_AND,
  SPVM_OP_C_ID_LOGICAL_OR,
  SPVM_OP_C_ID_LOGICAL_NOT,
  SPVM_OP_C_ID_ELEMENT_ACCESS,
  SPVM_OP_C_ID_ASSIGN,
  SPVM_OP_C_ID_FIELD_ACCESS,
  SPVM_OP_C_ID_VAR,
  SPVM_OP_C_ID_UNDEF,
  SPVM_OP_C_ID_ARRAY_LENGTH,
  SPVM_OP_C_ID_SCALAR,
  SPVM_OP_C_ID_EXCEPTION_VAR,
  SPVM_OP_C_ID_SPECIAL_ASSIGN,
  SPVM_OP_C_ID_STRING_LENGTH,
  SPVM_OP_C_ID_STRING_CONCAT,
  SPVM_OP_C_ID_CLASS_VAR,
  SPVM_OP_C_ID_CLASS_VAR_ACCESS,
  SPVM_OP_C_ID_NUMERIC_COMPARISON_EQ,
  SPVM_OP_C_ID_NUMERIC_COMPARISON_NE,
  SPVM_OP_C_ID_NUMERIC_COMPARISON_LT,
  SPVM_OP_C_ID_NUMERIC_COMPARISON_LE,
  SPVM_OP_C_ID_NUMERIC_COMPARISON_GT,
  SPVM_OP_C_ID_NUMERIC_COMPARISON_GE,
  SPVM_OP_C_ID_NUMERIC_COMPARISON_CMP,
  SPVM_OP_C_ID_STRING_COMPARISON_EQ,
  SPVM_OP_C_ID_STRING_COMPARISON_NE,
  SPVM_OP_C_ID_STRING_COMPARISON_GT,
  SPVM_OP_C_ID_STRING_COMPARISON_GE,
  SPVM_OP_C_ID_STRING_COMPARISON_LT,
  SPVM_OP_C_ID_STRING_COMPARISON_LE,
  SPVM_OP_C_ID_STRING_COMPARISON_CMP,
  SPVM_OP_C_ID_ARRAY_FIELD_ACCESS,
  SPVM_OP_C_ID_NEW,
  SPVM_OP_C_ID_ARRAY_INIT,
  SPVM_OP_C_ID_WARN,
  SPVM_OP_C_ID_PRINT,
  SPVM_OP_C_ID_SAY,
  SPVM_OP_C_ID_DUMP,
  SPVM_OP_C_ID_TRUE,
  SPVM_OP_C_ID_FALSE,
  SPVM_OP_C_ID_NEW_STRING_LEN,
  SPVM_OP_C_ID_IS_READ_ONLY,
  SPVM_OP_C_ID_MAKE_READ_ONLY,
  SPVM_OP_C_ID_COPY,
  SPVM_OP_C_ID_TYPE_CAST,
  SPVM_OP_C_ID_BOOL,
  SPVM_OP_C_ID_ISA,
  SPVM_OP_C_ID_ISA_ERROR,
  SPVM_OP_C_ID_IS_TYPE,
  SPVM_OP_C_ID_IS_ERROR,
  SPVM_OP_C_ID_IS_COMPILE_TYPE,
  SPVM_OP_C_ID_CAN,
  SPVM_OP_C_ID_BASIC_TYPE_ID,
  SPVM_OP_C_ID_TYPE_NAME,
  SPVM_OP_C_ID_COMPILE_TYPE_NAME,
  SPVM_OP_C_ID_OUTMOST_CLASS_NAME,
  SPVM_OP_C_ID_ARGS_WIDTH,
  SPVM_OP_C_ID_CALL_METHOD,
  SPVM_OP_C_ID_WEAKEN,
  SPVM_OP_C_ID_WEAKEN_FIELD,
  SPVM_OP_C_ID_UNWEAKEN,
  SPVM_OP_C_ID_UNWEAKEN_FIELD,
  SPVM_OP_C_ID_ISWEAK,
  SPVM_OP_C_ID_ISWEAK_FIELD,
  SPVM_OP_C_ID_REFERENCE,
  SPVM_OP_C_ID_DEREFERENCE,
  SPVM_OP_C_ID_EVAL_ERROR_ID,
  SPVM_OP_C_ID_SEQUENCE,
};

const char* const* SPVM_OP_C_ID_NAMES(void);

enum {
  // Condition flag
  SPVM_OP_C_FLAG_CONDITION_IF = 1,
  SPVM_OP_C_FLAG_CONDITION_LOOP = 2,
};

enum {
  // Special assign flag
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_ADD,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_SUBTRACT,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_MULTIPLY,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_DIVIDE,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_MODULO,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_LEFT_SHIFT,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_ARITHMETIC_SHIFT,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_RIGHT_LOGICAL_SHIFT,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_XOR,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_OR,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_BIT_AND,
  SPVM_OP_C_FLAG_SPECIAL_ASSIGN_STRING_CONCAT,
};

enum {
  // FIELD_ACCESS flag
  SPVM_OP_C_FLAG_FIELD_ACCESS_WEAKEN = 1,
  SPVM_OP_C_FLAG_FIELD_ACCESS_UNWEAKEN = 2,
  SPVM_OP_C_FLAG_FIELD_ACCESS_ISWEAK = 4,
};
enum {
  // ELEMENT_ACCESS flag
  SPVM_OP_C_FLAG_ELEMENT_ACCESS_WEAKEN = 1,
  SPVM_OP_C_FLAG_ELEMENT_ACCESS_STRING = 2,
  SPVM_OP_C_FLAG_ELEMENT_ACCESS_UNWEAKEN = 4,
  SPVM_OP_C_FLAG_ELEMENT_ACCESS_ISWEAK = 8,
};

struct spvm_op {
  SPVM_OP* first;
  SPVM_OP* last;
  SPVM_OP* sibparent;
  const char* file;
  union {
    SPVM_BLOCK* block;
    SPVM_ATTRIBUTE* attribute;
    SPVM_USE* use;
    SPVM_ALLOW* allow;
    SPVM_INTERFACE* interface;
    SPVM_CLASS_VAR_ACCESS* class_var_access;
    SPVM_ARRAY_FIELD_ACCESS* array_field_access;
    SPVM_FIELD_ACCESS* field_access;
    SPVM_CALL_METHOD* call_method;
    SPVM_CONSTANT* constant;
    SPVM_VAR* var;
    SPVM_VAR_DECL* var_decl;
    SPVM_TYPE* type;
    const char* name;
    SPVM_CLASS_VAR* class_var;
    SPVM_FIELD* field;
    SPVM_METHOD* method;
    SPVM_SWITCH_INFO* switch_info;
    SPVM_CASE_INFO* case_info;
  } uv;
  int32_t id;
  int32_t original_id;
  int32_t flag;
  int32_t line;
  int32_t column;
  int8_t moresib;
  int8_t is_dist;
  int8_t is_assigned_to_var;
  int8_t allow_narrowing_conversion;
};

SPVM_OP* SPVM_OP_build_operator_statement(SPVM_COMPILER* compiler, SPVM_OP* op_value_op);

SPVM_OP* SPVM_OP_build_if_require_statement(SPVM_COMPILER* compiler, SPVM_OP* op_if_require, SPVM_OP* op_use, SPVM_OP* op_block_true, SPVM_OP* op_block_false);

SPVM_OP* SPVM_OP_build_var(SPVM_COMPILER* compiler, SPVM_OP* op_var_name);

SPVM_OP* SPVM_OP_build_enumeration_item(SPVM_COMPILER* compiler, SPVM_OP* op_name, SPVM_OP* op_operand);

SPVM_OP* SPVM_OP_build_new(SPVM_COMPILER* compiler, SPVM_OP* op_new, SPVM_OP* op_type, SPVM_OP* op_length);

SPVM_OP* SPVM_OP_build_logical_and(SPVM_COMPILER* compiler, SPVM_OP* op_and, SPVM_OP* op_left_operand, SPVM_OP* op_right_operand);

SPVM_OP* SPVM_OP_build_logical_or(SPVM_COMPILER* compiler, SPVM_OP* op_or, SPVM_OP* op_left_operand, SPVM_OP* op_right_operand);

SPVM_OP* SPVM_OP_build_logical_not(SPVM_COMPILER* compiler, SPVM_OP* op_not, SPVM_OP* op_operand);

SPVM_OP* SPVM_OP_build_type_check(SPVM_COMPILER* compiler, SPVM_OP* op_is, SPVM_OP* op_left_operand, SPVM_OP* op_right_operand);

SPVM_OP* SPVM_OP_build_return(SPVM_COMPILER* compiler, SPVM_OP* op_return, SPVM_OP* op_operand);

SPVM_OP* SPVM_OP_build_die(SPVM_COMPILER* compiler, SPVM_OP* op_die, SPVM_OP* op_operand, SPVM_OP* op_type);

SPVM_OP* SPVM_OP_build_warn(SPVM_COMPILER* compiler, SPVM_OP* op_warn, SPVM_OP* op_operand);

SPVM_OP* SPVM_OP_build_print(SPVM_COMPILER* compiler, SPVM_OP* op_print, SPVM_OP* op_operand);

SPVM_OP* SPVM_OP_build_eval(SPVM_COMPILER* compiler, SPVM_OP* op_eval, SPVM_OP* op_block);

SPVM_OP* SPVM_OP_build_switch_statement(SPVM_COMPILER* compiler, SPVM_OP* op_switch, SPVM_OP* op_operand, SPVM_OP* op_block);

SPVM_OP* SPVM_OP_build_switch_block(SPVM_COMPILER* compiler, SPVM_OP* op_switch_block, SPVM_OP* op_case_statements, SPVM_OP* op_default_statement);

SPVM_OP* SPVM_OP_build_default_statement(SPVM_COMPILER* compiler, SPVM_OP* op_default, SPVM_OP* op_block);

SPVM_OP* SPVM_OP_build_case_statement(SPVM_COMPILER* compiler, SPVM_OP* op_case, SPVM_OP* op_operand, SPVM_OP* op_block);

SPVM_OP* SPVM_OP_build_logical_op(SPVM_COMPILER* compiler, SPVM_OP* op_logical_op, SPVM_OP* op_left_operand, SPVM_OP* op_right_operand);

SPVM_OP* SPVM_OP_build_for_statement(SPVM_COMPILER* compiler, SPVM_OP* op_for, SPVM_OP* op_loop_var, SPVM_OP* op_condition, SPVM_OP* op_next_value, SPVM_OP* op_block);

SPVM_OP* SPVM_OP_build_foreach_statement(SPVM_COMPILER* compiler, SPVM_OP* op_for, SPVM_OP* op_var_decl, SPVM_OP* op_array_length, SPVM_OP* op_block_statements);

SPVM_OP* SPVM_OP_build_while_statement(SPVM_COMPILER* compiler, SPVM_OP* op_while, SPVM_OP* op_condition, SPVM_OP* op_block);

SPVM_OP* SPVM_OP_build_if_statement(SPVM_COMPILER* compiler, SPVM_OP* op_if, SPVM_OP* op_operand, SPVM_OP* op_block, SPVM_OP* op_else_statement, int32_t no_scope);

SPVM_OP* SPVM_OP_build_array_length(SPVM_COMPILER* compiler, SPVM_OP* op_array_length, SPVM_OP* op_operand);

SPVM_OP* SPVM_OP_build_malloc_object(SPVM_COMPILER* compiler, SPVM_OP* op_malloc, SPVM_OP* op_type);

SPVM_OP* SPVM_OP_build_binary_op(SPVM_COMPILER* compiler, SPVM_OP* op_call_op, SPVM_OP* op_left_operand, SPVM_OP* op_right_operand);

SPVM_OP* SPVM_OP_build_basic_type(SPVM_COMPILER* compiler, SPVM_OP* op_type_name);

SPVM_OP* SPVM_OP_build_array_type(SPVM_COMPILER* compiler, SPVM_OP* op_type, SPVM_OP* op_operand);

SPVM_OP* SPVM_OP_build_ref_type(SPVM_COMPILER* compiler, SPVM_OP* op_type_original);

SPVM_OP* SPVM_OP_build_field_access(SPVM_COMPILER* compiler, SPVM_OP* op_field_access, SPVM_OP* op_invocant, SPVM_OP* op_name_field);

SPVM_OP* SPVM_OP_build_class(SPVM_COMPILER* compiler, SPVM_OP* op_class, SPVM_OP* op_name_basic_type, SPVM_OP* op_block, SPVM_OP* op_list_attributes, SPVM_OP* op_extends);

SPVM_OP* SPVM_OP_build_version_decl(SPVM_COMPILER* compiler, SPVM_OP* op_version, SPVM_OP* op_version_string);

SPVM_OP* SPVM_OP_build_method(SPVM_COMPILER* compiler, SPVM_OP* op_method, SPVM_OP* op_methodname, SPVM_OP* op_return_type, SPVM_OP* op_args, SPVM_OP* op_attributes, SPVM_OP* op_block);

SPVM_OP* SPVM_OP_attach_anon_method_fields(SPVM_COMPILER* compiler, SPVM_OP* op_method, SPVM_OP* op_anon_method_fields);

SPVM_OP* SPVM_OP_build_init_block(SPVM_COMPILER* compiler, SPVM_OP* op_init, SPVM_OP* op_block);

SPVM_OP* SPVM_OP_build_init_statement(SPVM_COMPILER* compiler, SPVM_OP* op_init, SPVM_OP* op_block);

SPVM_OP* SPVM_OP_build_CONSTVALUE(SPVM_COMPILER* compiler, SPVM_OP* op_const);

SPVM_OP* SPVM_OP_build_field(SPVM_COMPILER* compiler, SPVM_OP* op_field, SPVM_OP* op_field_base_name, SPVM_OP* op_descripters, SPVM_OP* type);

SPVM_OP* SPVM_OP_build_class_var(SPVM_COMPILER* compiler, SPVM_OP* class_var, SPVM_OP* op_class_var_name, SPVM_OP* op_attributes, SPVM_OP* op_type);

SPVM_OP* SPVM_OP_build_var_decl(SPVM_COMPILER* compiler, SPVM_OP* op_var_decl, SPVM_OP* op_var, SPVM_OP* op_type, SPVM_OP* op_attributes);

SPVM_OP* SPVM_OP_build_arg(SPVM_COMPILER* compiler, SPVM_OP* op_var, SPVM_OP* op_type, SPVM_OP* op_attributes, SPVM_OP* op_default);

SPVM_OP* SPVM_OP_build_anon_method(SPVM_COMPILER* compiler, SPVM_OP* op_method);

SPVM_OP* SPVM_OP_build_anon_method_field(SPVM_COMPILER* compiler, SPVM_OP* op_field, SPVM_OP* op_name_field, SPVM_OP* op_attributes, SPVM_OP* op_type, SPVM_OP* op_default);

SPVM_OP* SPVM_OP_build_use(SPVM_COMPILER* compiler, SPVM_OP* op_use, SPVM_OP* op_name_basic_type, SPVM_OP* op_name_alias, int32_t is_require);

SPVM_OP* SPVM_OP_build_allow(SPVM_COMPILER* compiler, SPVM_OP* op_use, SPVM_OP* op_name_basic_type);

SPVM_OP* SPVM_OP_build_interface_statement(SPVM_COMPILER* compiler, SPVM_OP* op_use, SPVM_OP* op_name_basic_type);

SPVM_OP* SPVM_OP_build_call_method(SPVM_COMPILER* compiler, SPVM_OP* op_call_method, SPVM_OP* op_invocant, SPVM_OP* op_name_method, SPVM_OP* op_list_operands);

SPVM_OP* SPVM_OP_build_type_cast(SPVM_COMPILER* compiler, SPVM_OP* op_convert, SPVM_OP* op_type, SPVM_OP* op_operand, SPVM_OP* op_attributes);

SPVM_OP* SPVM_OP_build_enumeration(SPVM_COMPILER* compiler, SPVM_OP* op_enumeration, SPVM_OP* op_enumeration_block, SPVM_OP* op_descripters);

SPVM_OP* SPVM_OP_build_unary_op(SPVM_COMPILER* compiler, SPVM_OP* op_unary, SPVM_OP* op_operand);

SPVM_OP* SPVM_OP_build_unary_op_var(SPVM_COMPILER* compiler, SPVM_OP* op_unary, SPVM_OP* op_operand);

SPVM_OP* SPVM_OP_build_element_access(SPVM_COMPILER* compiler, SPVM_OP* op_element_access, SPVM_OP* op_var, SPVM_OP* op_operand);

SPVM_OP* SPVM_OP_build_assign(SPVM_COMPILER* compiler, SPVM_OP* op_assign, SPVM_OP* op_left_operand, SPVM_OP* op_right_operand);

SPVM_OP* SPVM_OP_build_weaken_field(SPVM_COMPILER* compiler, SPVM_OP* op_weaken, SPVM_OP* op_field_access);

SPVM_OP* SPVM_OP_build_unweaken_field(SPVM_COMPILER* compiler, SPVM_OP* op_unweaken, SPVM_OP* op_field_access);

SPVM_OP* SPVM_OP_build_isweak_field(SPVM_COMPILER* compiler, SPVM_OP* op_isweak, SPVM_OP* op_field_access);

SPVM_OP* SPVM_OP_build_array_init(SPVM_COMPILER* compiler, SPVM_OP* op_array_init, SPVM_OP* op_list_elements, int32_t is_key_values);

SPVM_OP* SPVM_OP_build_inc(SPVM_COMPILER* compiler, SPVM_OP* op_inc, SPVM_OP* op_operand);

SPVM_OP* SPVM_OP_build_dec(SPVM_COMPILER* compiler, SPVM_OP* op_dec, SPVM_OP* op_operand);

SPVM_OP* SPVM_OP_build_special_assign(SPVM_COMPILER* compiler, SPVM_OP* op_special_assign, SPVM_OP* op_dist, SPVM_OP* op_src);

SPVM_OP* SPVM_OP_build_make_read_only(SPVM_COMPILER* compiler, SPVM_OP* op_make_read_only, SPVM_OP* op_operand);

SPVM_OP* SPVM_OP_build_can(SPVM_COMPILER* compiler, SPVM_OP* op_has_interface, SPVM_OP* op_var, SPVM_OP* op_name);

SPVM_OP* SPVM_OP_build_mutable_type(SPVM_COMPILER* compiler, SPVM_OP* op_type_child);

SPVM_OP* SPVM_OP_build_alias(SPVM_COMPILER* compiler, SPVM_OP* op_use, SPVM_OP* op_name_basic_type, SPVM_OP* op_name_alias);

SPVM_OP* SPVM_OP_build_basic_type_id(SPVM_COMPILER* compiler, SPVM_OP* op_basic_type_id, SPVM_OP* op_type);

SPVM_OP* SPVM_OP_build_extends(SPVM_COMPILER* compiler, SPVM_OP* op_extends, SPVM_OP* op_name_parent_class);

SPVM_OP* SPVM_OP_new_op_bool(SPVM_COMPILER* compiler, SPVM_OP* op_operand, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_var_decl(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_block(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_name(SPVM_COMPILER* compiler, const char* name, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_var(SPVM_COMPILER* compiler, SPVM_OP* op_name);

SPVM_OP* SPVM_OP_new_op_var_condition_flag(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_class_var_access(SPVM_COMPILER* compiler, SPVM_OP* op_name);

SPVM_OP* SPVM_OP_new_op_undef(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_attribute(SPVM_COMPILER* compiler, int32_t id, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_void(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_constant_byte(SPVM_COMPILER* compiler, int8_t value, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_constant_short(SPVM_COMPILER* compiler, int16_t value, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_constant_int(SPVM_COMPILER* compiler, int32_t value, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_constant_long(SPVM_COMPILER* compiler, int64_t value, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_constant_float(SPVM_COMPILER* compiler, float value, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_constant_double(SPVM_COMPILER* compiler, double value, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_constant_string(SPVM_COMPILER* compiler, const char* string, int32_t length, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_constant_byte_array_string(SPVM_COMPILER* compiler, char* string, int32_t length, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_var_from_op_var_decl(SPVM_COMPILER* compiler, SPVM_OP* op_var_decl, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_list(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op(SPVM_COMPILER* compiler, int32_t id, const char* file, int32_t line);

SPVM_OP* SPVM_OP_clone_op_var(SPVM_COMPILER* compiler, SPVM_OP* original_op_var);

SPVM_OP* SPVM_OP_new_op_byte_type(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_short_type(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_int_type(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_long_type(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_float_type(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_double_type(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_string_type(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_undef_type(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_bool_type(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_byte_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_short_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_int_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_long_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_float_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_double_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_string_type(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_any_object_type(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_void_type(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_unresolved_type(SPVM_COMPILER* compiler, const char* name, int32_t type_dimension, int32_t type_flag, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_any_object_array_type(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_type(SPVM_COMPILER* compiler, const char* unresolved_basic_type_name, SPVM_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag, const char* file, int32_t line);

SPVM_OP* SPVM_OP_clone_op_field_access(SPVM_COMPILER* compiler, SPVM_OP* op_field_access, SPVM_OP* op_var_invocant, SPVM_OP* op_name_field);

SPVM_OP* SPVM_OP_clone_op_element_access(SPVM_COMPILER* compiler, SPVM_OP* op_element_access, SPVM_OP* op_var_array, SPVM_OP* op_var_index);

SPVM_OP* SPVM_OP_clone_op_array_field_access(SPVM_COMPILER* compiler, SPVM_OP* op_field_access, SPVM_OP* op_name_field, SPVM_OP* op_element_access, SPVM_OP* op_var_array, SPVM_OP* op_var_index);

SPVM_OP* SPVM_OP_clone_op_deref(SPVM_COMPILER* compiler, SPVM_OP* op_deref, SPVM_OP* op_var);

SPVM_OP* SPVM_OP_new_op_true(SPVM_COMPILER* compiler, SPVM_OP* op);

SPVM_OP* SPVM_OP_new_op_false(SPVM_COMPILER* compiler, SPVM_OP* op);

SPVM_OP* SPVM_OP_new_op_use(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_constant(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_array_field_access(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_field_access(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_call_method(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_var_decl_arg(SPVM_COMPILER* compiler, const char* file, int32_t line);

SPVM_OP* SPVM_OP_new_op_name_tmp_var(SPVM_COMPILER* compiler, const char* file, int32_t line);

int32_t SPVM_OP_is_allowed(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type_current, SPVM_BASIC_TYPE* basic_type_dist, int32_t is_parent_field);

int32_t SPVM_OP_is_mutable(SPVM_COMPILER* compiler, SPVM_OP* op);

SPVM_OP* SPVM_OP_get_parent(SPVM_COMPILER* compiler, SPVM_OP* op_target);

void SPVM_OP_get_before(SPVM_COMPILER* compiler, SPVM_OP* op_target, SPVM_OP** op_before_ptr, int32_t* next_is_child_ptr);

SPVM_OP* SPVM_OP_cut_op(SPVM_COMPILER* compiler, SPVM_OP* op_target);

void SPVM_OP_replace_op(SPVM_COMPILER* compiler, SPVM_OP* op_target, SPVM_OP* op_replace);

void SPVM_OP_insert_child(SPVM_COMPILER* compiler, SPVM_OP* parent, SPVM_OP* start, SPVM_OP* insert);

SPVM_OP* SPVM_OP_sibling(SPVM_COMPILER* compiler, SPVM_OP* op);

const char* SPVM_OP_get_op_name(SPVM_COMPILER* compiler, int32_t op_id);

#endif
