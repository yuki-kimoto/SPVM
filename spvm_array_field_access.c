#ifndef SPVM_ARRAY_FIELD_ACCESS_H
#define SPVM_ARRAY_FIELD_ACCESS_H

#include "spvm_base.h"

struct SPVM_array_field_access {
  SPVM_FIELD* field;
  int32_t sub_rel_id;
};

SPVM_ARRAY_FIELD_ACCESS* SPVM_ARRAY_FIELD_ACCESS_new(SPVM_COMPILER* compiler);

#endif
