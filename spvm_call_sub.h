#ifndef SPVM_CALL_SUB_H
#define SPVM_CALL_SUB_H

#include "spvm_base.h"

enum {
  SPVM_CALL_SUB_C_CODE_VARBASENAME,
  SPVM_CALL_SUB_C_CODE_BASENAME,
  SPVM_CALL_SUB_C_CODE_ABSNAME,
};

struct SPVM_call_sub {
  SPVM_OP* op_term;
  SPVM_OP* op_name;
  SPVM_SUB* sub;
  const char* resolved_name;
  int32_t code;
};

SPVM_CALL_SUB* SPVM_CALL_SUB_new(SPVM_COMPILER* compiler);

#endif
