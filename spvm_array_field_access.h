#ifndef SPVM_ARRAY_FIELD_ACCESS_H
#define SPVM_ARRAY_FIELD_ACCESS_H

#include "spvm_base.h"

struct SPVM_array_field_access {
  SPVM_OP* op_term;
  SPVM_OP* op_name;
  SPVM_FIELD* field;
  int32_t sub_rel_id;
  _Bool is_value_t_array_access;
  SPVM_OP* op_term_array_access;
};

SPVM_ARRAY_FIELD_ACCESS* SPVM_ARRAY_FIELD_ACCESS_new(SPVM_COMPILER* compiler);

#endif
