#ifndef SPVM_RESOLVED_TYPE_H
#define SPVM_RESOLVED_TYPE_H

#include "spvm_base.h"

extern const char* const SPVM_RESOLVED_TYPE_C_CORE_NAMES[];

struct SPVM_resolved_type {
  const char* name;
  int32_t name_length;
  int32_t id;
};

SPVM_RESOLVED_TYPE* SPVM_RESOLVED_TYPE_new(SPVM_COMPILER* compiler);
_Bool SPVM_RESOLVED_TYPE_is_integral(SPVM_COMPILER* compiler, SPVM_RESOLVED_TYPE* resolved_type);
_Bool SPVM_RESOLVED_TYPE_is_numeric(SPVM_COMPILER* compiler, SPVM_RESOLVED_TYPE* resolved_type);
_Bool SPVM_RESOLVED_TYPE_is_array(SPVM_COMPILER* compiler, SPVM_RESOLVED_TYPE* resolved_type);
_Bool SPVM_RESOLVED_TYPE_is_array_numeric(SPVM_COMPILER* compiler, SPVM_RESOLVED_TYPE* resolved_type);

#endif
