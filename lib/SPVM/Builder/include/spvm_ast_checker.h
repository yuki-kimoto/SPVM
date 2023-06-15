// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_AST_CHECKER_H
#define SPVM_AST_CHECKER_H

#include "spvm_typedecl.h"

void SPVM_AST_CHECKER_check(SPVM_COMPILER* compiler);

void SPVM_AST_CHECKER_resolve_op_type(SPVM_COMPILER* compiler, SPVM_OP* op_type);

void SPVM_AST_CHECKER_resolve_op_types(SPVM_COMPILER* compiler);

void SPVM_AST_CHECKER_resolve_call_method(SPVM_COMPILER* compiler, SPVM_OP* op_call_method, SPVM_OP* op_class_current);

void SPVM_AST_CHECKER_resolve_field_access(SPVM_COMPILER* compiler, SPVM_OP* op_field_access);

void SPVM_AST_CHECKER_resolve_class_var_access(SPVM_COMPILER* compiler, SPVM_OP* op_class_var_access, SPVM_OP* op_class);

void SPVM_AST_CHECKER_resolve_classes(SPVM_COMPILER* compiler);

void SPVM_AST_CHECKER_traverse_ast_resolve_op_types(SPVM_COMPILER* compiler, SPVM_CLASS* class, SPVM_METHOD* method);

void SPVM_AST_CHECKER_traverse_ast_check_syntax(SPVM_COMPILER* compiler, SPVM_CLASS* class, SPVM_METHOD* method);

void SPVM_AST_CHECKER_traverse_ast_assign_unassigned_op_to_var(SPVM_COMPILER* compiler, SPVM_CLASS* class, SPVM_METHOD* method);

void SPVM_AST_CHECKER_traverse_ast_check_if_block_need_leave_scope(SPVM_COMPILER* compiler, SPVM_CLASS* class, SPVM_METHOD* method);

void SPVM_AST_CHECKER_traverse_ast_resolve_call_stack_ids(SPVM_COMPILER* compiler, SPVM_CLASS* class, SPVM_METHOD* method);

int SPVM_AST_CHECKER_method_name_compare_cb(const void* method1_ptr, const void* method2_ptr);

SPVM_METHOD* SPVM_AST_CHECKER_search_method(SPVM_COMPILER* compiler, SPVM_CLASS* class, const char* method_name);

SPVM_FIELD* SPVM_AST_CHECKER_search_field(SPVM_COMPILER* compiler, SPVM_CLASS* class, const char* field_name);

int32_t SPVM_AST_CHECKER_check_allow_narrowing_conversion(SPVM_COMPILER* compiler, SPVM_TYPE* dist_type, SPVM_OP* op_src);

SPVM_OP* SPVM_AST_CHECKER_check_assign(SPVM_COMPILER* compiler, SPVM_TYPE* dist_type, SPVM_OP* op_src, const char* place, const char* file, int32_t line);

void SPVM_AST_CHECKER_perform_numeric_to_string_conversion(SPVM_COMPILER* compiler, SPVM_OP* op_term);

void SPVM_AST_CHECKER_perform_integer_promotional_conversion(SPVM_COMPILER* compiler, SPVM_OP* op_unary);

void SPVM_AST_CHECKER_perform_binary_numeric_conversion(SPVM_COMPILER* compiler, SPVM_OP* op_first, SPVM_OP* op_last);

int32_t SPVM_AST_CHECKER_can_access(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* class_basic_type_from, SPVM_BASIC_TYPE* class_basic_type_to, int32_t access_controll_flag_to);

int32_t SPVM_AST_CHECKER_get_call_stack_id(SPVM_COMPILER* compiler, SPVM_LIST* mem_stack, SPVM_VAR_DECL* var_decl);

SPVM_OP* SPVM_AST_CHECKER_new_op_var_tmp(SPVM_COMPILER* compiler, SPVM_TYPE* type, SPVM_METHOD* method, const char* file, int32_t line);

#endif
