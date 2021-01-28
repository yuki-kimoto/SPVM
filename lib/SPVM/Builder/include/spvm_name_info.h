#ifndef SPVM_FIELD_ACCESS_H
#define SPVM_FIELD_ACCESS_H

#include "spvm_typedef.h"

struct spvm_field_access {
  SPVM_OP* op_term_invocant;
  SPVM_OP* op_name;
  const char* resolved_name;
  int32_t id;
};

SPVM_FIELD_ACCESS* SPVM_FIELD_ACCESS_new(SPVM_COMPILER* compiler);

#endif
