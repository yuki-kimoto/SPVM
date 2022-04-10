#ifndef SPVM_STRING_H
#define SPVM_STRING_H

#include "spvm_typedecl.h"

struct spvm_constant_string {
  const char* value;
  int32_t length;
  int32_t id;
  int32_t string_buffer_id;
};

SPVM_CONSTANT_STRING* SPVM_CONSTANT_STRING_new(SPVM_COMPILER* compiler, const char* value, int32_t length);

#endif
