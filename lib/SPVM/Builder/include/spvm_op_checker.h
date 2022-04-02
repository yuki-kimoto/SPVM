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
void SPVM_OP_CHECKER_apply_numeric_to_string_conversion(SPVM_COMPILER* compiler, SPVM_OP* op_term);
void SPVM_OP_CHECKER_apply_unary_numeric_widening_conversion(SPVM_COMPILER* compiler, SPVM_OP* op_unary);
void SPVM_OP_CHECKER_apply_binary_numeric_conversion(SPVM_COMPILER* compiler, SPVM_OP* op_first, SPVM_OP* op_last);

void SPVM_OP_CHECKER_resolve_my_mem_ids(SPVM_COMPILER* compiler, SPVM_METHOD* method);

SPVM_OP* SPVM_OP_CHECKER_new_op_var_tmp(SPVM_COMPILER* compiler, SPVM_METHOD* method, SPVM_TYPE* type, const char* file, int32_t line);


#endif
