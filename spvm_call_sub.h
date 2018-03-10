#ifndef SPVM_CALL_SUB_H
#define SPVM_CALL_SUB_H

#include "spvm_base.h"

enum {
  SPVM_CALL_SUB_C_ID_METHOD_CALL,
  SPVM_CALL_SUB_C_ID_SUB_CALL,
};

struct SPVM_call_sub {
  SPVM_OP* op_term;
  SPVM_OP* op_name;
  SPVM_SUB* sub;
  int32_t id;
};

SPVM_CALL_SUB* SPVM_CALL_SUB_new(SPVM_COMPILER* compiler);

#endif
