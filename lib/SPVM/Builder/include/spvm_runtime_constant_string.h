#ifndef SPVM_RUNTIME_CONSTANT_STRING_H
#define SPVM_RUNTIME_CONSTANT_STRING_H

#include "spvm_typedecl.h"

struct spvm_runtime_constant_string {
  const char* value;
  int32_t length;
  int32_t id;
  int32_t string_buffer_id;
};

#endif
