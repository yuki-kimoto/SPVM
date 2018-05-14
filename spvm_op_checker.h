#ifndef SPVM_OP_CHECKER_H
#define SPVM_OP_CHECKER_H

#include "spvm_base.h"

void SPVM_OP_CHECKER_check(SPVM_COMPILER* compiler);
_Bool SPVM_OP_CHECKER_can_assign(SPVM_COMPILER* compiler, SPVM_TYPE* assign_to_type, SPVM_TYPE* assign_from_type);
SPVM_OP* SPVM_OP_CHECKER_check_and_convert_type(SPVM_COMPILER* compiler, SPVM_OP* op_assign_to, SPVM_OP* op_assign_from);

#endif
