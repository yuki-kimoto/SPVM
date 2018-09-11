#ifndef SPVM_OP_CHECKER_H
#define SPVM_OP_CHECKER_H

#include "spvm_base.h"

void SPVM_OP_CHECKER_check(SPVM_COMPILER* compiler);
_Bool SPVM_OP_CHECKER_check_cast(SPVM_COMPILER* compiler, int32_t dist_basic_type_id, int32_t dist_type_dimension, int32_t dist_type_flag, int32_t src_basic_type_id, int32_t src_type_dimension, int32_t src_type_flag);
SPVM_OP* SPVM_OP_CHECKER_check_and_convert_type(SPVM_COMPILER* compiler, SPVM_OP* op_assign_to, SPVM_OP* op_assign_from);

void SPVM_OP_CHECKER_resolve_types(SPVM_COMPILER* compiler);
void SPVM_OP_CHECKER_resolve_call_sub(SPVM_COMPILER* compiler, SPVM_OP* op_call_sub, SPVM_OP* op_package_current);
void SPVM_OP_CHECKER_resolve_field_access(SPVM_COMPILER* compiler, SPVM_OP* op_field_access);
void SPVM_OP_CHECKER_resolve_package_var_access(SPVM_COMPILER* compiler, SPVM_OP* op_package_var_access, SPVM_OP* op_package);
void SPVM_OP_CHECKER_resolve_basic_types(SPVM_COMPILER* compiler);
void SPVM_OP_CHECKER_resolve_packages(SPVM_COMPILER* compiler);

void SPVM_OP_CHECKER_apply_unary_numeric_promotion(SPVM_COMPILER* compiler, SPVM_OP* op_unary);
void SPVM_OP_CHECKER_apply_binary_numeric_promotion(SPVM_COMPILER* compiler, SPVM_OP* op_first, SPVM_OP* op_last);

const char* SPVM_OP_CHECKER_create_sub_signature(SPVM_COMPILER* compiler, SPVM_SUB* sub);
const char* SPVM_OP_CHECKER_create_field_signature(SPVM_COMPILER* compiler, SPVM_FIELD* field);
const char* SPVM_OP_CHECKER_create_package_var_signature(SPVM_COMPILER* compiler, SPVM_PACKAGE_VAR* package_var);


#endif
