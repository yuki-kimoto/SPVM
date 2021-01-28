#ifndef SPVM_CALL_SUB_H
#define SPVM_CALL_SUB_H

#include "spvm_typedef.h"

struct SPVM_call_sub {
  SPVM_OP* op_invocant;
  SPVM_OP* op_name;
  SPVM_SUB* sub;
  int32_t call_type_id;
  int32_t constant_pool_id;
};

SPVM_CALL_SUB* SPVM_CALL_SUB_new(SPVM_COMPILER* compiler);

#endif
