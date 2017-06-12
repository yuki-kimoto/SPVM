#ifndef SPVM_DESCRIPTOR_H
#define SPVM_DESCRIPTOR_H

#include "spvm_base.h"

enum {
  SPVM_DESCRIPTOR_C_CODE_NATIVE,
  SPVM_DESCRIPTOR_C_CODE_CONST,
};

extern const char* const SPVM_DESCRIPTOR_C_CODE_NAMES[];

// Field information
struct SPVM_descriptor {
  int32_t code;
};

SPVM_DESCRIPTOR* SPVM_DESCRIPTOR_new(SPVM_* spvm);

#endif
