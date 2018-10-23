#ifndef SPVM_CALL_SUB_H
#define SPVM_CALL_SUB_H

#include "spvm_base.h"

struct SPVM_call_sub {
  SPVM_OP* op_invocant;
  SPVM_OP* op_name;
  SPVM_SUB* sub;
  int32_t call_type_id;
  int32_t info_constant_id;
};

SPVM_CALL_SUB* SPVM_CALL_SUB_new(SPVM_COMPILER* compiler);

#endif
