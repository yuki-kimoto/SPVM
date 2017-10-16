#ifndef SPVM_CALL_FIELD_H
#define SPVM_CALL_FIELD_H

#include "spvm_base.h"

struct SPVM_call_field {
  SPVM_OP* op_term_invocant;
  SPVM_OP* op_name;
  const char* resolved_name;
  int32_t id;
};

SPVM_CALL_FIELD* SPVM_CALL_FIELD_new(SPVM_COMPILER* compiler);

#endif
