#ifndef SPVM_FIELD_ACCESS_H
#define SPVM_FIELD_ACCESS_H

#include "spvm_typedecl.h"

struct spvm_field_access {
  SPVM_OP* op_invocant;
  SPVM_OP* op_name;
  SPVM_FIELD* field;
  int32_t inline_expansion;
};

SPVM_FIELD_ACCESS* SPVM_FIELD_ACCESS_new(SPVM_COMPILER* compiler);

#endif
