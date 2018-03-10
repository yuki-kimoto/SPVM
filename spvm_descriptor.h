#ifndef SPVM_DESCRIPTOR_H
#define SPVM_DESCRIPTOR_H

#include "spvm_base.h"

enum {
  SPVM_DESCRIPTOR_C_ID_NATIVE,
  SPVM_DESCRIPTOR_C_ID_CONST,
  SPVM_DESCRIPTOR_C_ID_JIT,
};

extern const char* const SPVM_DESCRIPTOR_C_ID_NAMES[];

// Field information
struct SPVM_descriptor {
  int32_t id;
};

SPVM_DESCRIPTOR* SPVM_DESCRIPTOR_new(SPVM_COMPILER* compiler);

#endif
