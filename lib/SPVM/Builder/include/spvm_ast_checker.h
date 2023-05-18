// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_OP_CHECKER_H
#define SPVM_OP_CHECKER_H

#include "spvm_typedecl.h"

void SPVM_OP_CHECKER_check(SPVM_COMPILER* compiler);

void SPVM_OP_CHECKER_resolve_op_types(SPVM_COMPILER* compiler);
void SPVM_OP_CHECKER_resolve_types(SPVM_COMPILER* compiler);
void SPVM_OP_CHECKER_resolve_call_method(SPVM_COMPILER* compiler, SPVM_OP* op_call_method, SPVM_OP* op_class_current);
void SPVM_OP_CHECKER_resolve_field_access(SPVM_COMPILER* compiler, SPVM_OP* op_field_access);
void SPVM_OP_CHECKER_resolve_class_var_access(SPVM_COMPILER* compiler, SPVM_OP* op_class_var_access, SPVM_OP* op_class);
void SPVM_OP_CHECKER_resolve_basic_types(SPVM_COMPILER* compiler);
void SPVM_OP_CHECKER_resolve_classes(SPVM_COMPILER* compiler);

SPVM_OP* SPVM_OP_CHECKER_check_assign(SPVM_COMPILER* compiler, SPVM_TYPE* dist_type, SPVM_OP* op_src, const char* place, const char* file, int32_t line);
void SPVM_OP_CHECKER_perform_numeric_to_string_conversion(SPVM_COMPILER* compiler, SPVM_OP* op_term);
void SPVM_OP_CHECKER_perform_integer_promotional_conversion(SPVM_COMPILER* compiler, SPVM_OP* op_unary);
void SPVM_OP_CHECKER_perform_binary_numeric_conversion(SPVM_COMPILER* compiler, SPVM_OP* op_first, SPVM_OP* op_last);

void SPVM_OP_CHECKER_resolve_var_decl_mem_ids(SPVM_COMPILER* compiler, SPVM_METHOD* method);

SPVM_OP* SPVM_OP_CHECKER_new_op_var_tmp(SPVM_COMPILER* compiler, SPVM_TYPE* type, const char* file, int32_t line);

void SPVM_OP_CHECKER_traversal_ast_check_syntax(SPVM_COMPILER* compiler, SPVM_OP* op_root, SPVM_CHECK_AST_INFO* check_ast_info);
int32_t SPVM_OP_CHECKER_get_mem_id(SPVM_COMPILER* compiler, SPVM_LIST* mem_stack, SPVM_VAR_DECL* var_decl);
int32_t SPVM_OP_CHECKER_can_access(SPVM_COMPILER* compiler, SPVM_CLASS* class_from, SPVM_CLASS* class_to, int32_t access_controll_flag_to);
#endif
