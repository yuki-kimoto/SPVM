// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_CHECK_H
#define SPVM_CHECK_H

#include "spvm_typedecl.h"

void SPVM_CHECK_check(SPVM_COMPILER* compiler);

void SPVM_CHECK_check_op_type(SPVM_COMPILER* compiler, SPVM_OP* op_type);

void SPVM_CHECK_check_op_types(SPVM_COMPILER* compiler);

void SPVM_CHECK_build_string_class(SPVM_COMPILER* compiler);

void SPVM_CHECK_check_call_method_call(SPVM_COMPILER* compiler, SPVM_OP* op_call_method, SPVM_METHOD* current_method);

SPVM_OP* SPVM_CHECK_check_call_method_varargs(SPVM_COMPILER* compiler, SPVM_OP* op_call_method, SPVM_METHOD* current_method);

void SPVM_CHECK_check_call_method_args(SPVM_COMPILER* compiler, SPVM_OP* op_call_method, SPVM_METHOD* current_method);

void SPVM_CHECK_check_field_access(SPVM_COMPILER* compiler, SPVM_OP* op_field_access);

void SPVM_CHECK_check_field_offset(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type, SPVM_LIST* merged_fields);

void SPVM_CHECK_check_class_var_access(SPVM_COMPILER* compiler, SPVM_OP* op_class_var_access, SPVM_METHOD* current_method);

void SPVM_CHECK_check_basic_types(SPVM_COMPILER* compiler);

void SPVM_CHECK_check_basic_types(SPVM_COMPILER* compiler);

void SPVM_CHECK_check_basic_types_relation(SPVM_COMPILER* compiler);

void SPVM_CHECK_check_class_vars(SPVM_COMPILER* compiler);

void SPVM_CHECK_check_fields(SPVM_COMPILER* compiler);

void SPVM_CHECK_check_methods(SPVM_COMPILER* compiler);

void SPVM_CHECK_check_asts(SPVM_COMPILER* compiler);

void SPVM_CHECK_check_ast_types(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type, SPVM_METHOD* method);

void SPVM_CHECK_check_ast_syntax(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type, SPVM_METHOD* method);

void SPVM_CHECK_check_ast_assign_form(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type, SPVM_METHOD* method);

void SPVM_CHECK_check_ast_fix_leave_scope(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type, SPVM_METHOD* method);

void SPVM_CHECK_check_ast_resolve_typed_var_indexes(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type, SPVM_METHOD* method);

int SPVM_CHECK_method_name_compare_cb(const void* method1_ptr, const void* method2_ptr);

int SPVM_CHECK_field_order_compare_cb(const void* field1_ptr, const void* field2_ptr);

SPVM_METHOD* SPVM_CHECK_search_method(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type, const char* method_name);

SPVM_FIELD* SPVM_CHECK_search_original_field(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type, const char* field_name);

int32_t SPVM_CHECK_check_allow_narrowing_conversion(SPVM_COMPILER* compiler, SPVM_TYPE* dist_type, SPVM_OP* op_src);

SPVM_OP* SPVM_CHECK_check_assign(SPVM_COMPILER* compiler, SPVM_TYPE* dist_type, SPVM_OP* op_src, const char* place, const char* file, int32_t line);

void SPVM_CHECK_perform_numeric_to_string_conversion(SPVM_COMPILER* compiler, SPVM_OP* op_term);

void SPVM_CHECK_perform_integer_promotional_conversion(SPVM_COMPILER* compiler, SPVM_OP* op_unary);

void SPVM_CHECK_perform_binary_numeric_conversion(SPVM_COMPILER* compiler, SPVM_OP* op_left_operand, SPVM_OP* op_right_operand);

int32_t SPVM_CHECK_can_access(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type_from, SPVM_BASIC_TYPE* basic_type_to, int32_t access_controll_flag_to, int32_t is_parent_field);

int32_t SPVM_CHECK_get_typed_var_index(SPVM_COMPILER* compiler, SPVM_LIST* mem_stack, SPVM_VAR_DECL* var_decl);

SPVM_OP* SPVM_CHECK_new_op_var_tmp(SPVM_COMPILER* compiler, SPVM_TYPE* type, SPVM_METHOD* method, const char* file, int32_t line);

SPVM_OP* SPVM_CHECK_new_op_type_shared(SPVM_COMPILER* compiler, SPVM_TYPE* type, const char* file, int32_t line);

SPVM_TYPE* SPVM_CHECK_get_type(SPVM_COMPILER* compiler, SPVM_OP* op);

SPVM_OP* SPVM_CHECK_apply_union_type_mapping(SPVM_COMPILER* compiler, SPVM_OP* op_call_method);

#endif
