#ifndef SPVM_REF_STRING_H
#define SPVM_REF_STRING_H

#include "spvm_value.h"
#include "spvm_base.h"

struct SPVM_ref_string {
  int32_t ref_count;
  int8_t type;
  SPVM_SV* sv;
};

#endif

