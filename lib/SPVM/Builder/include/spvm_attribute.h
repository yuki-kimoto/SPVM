#ifndef SPVM_ATTRIBUTE_H
#define SPVM_ATTRIBUTE_H

#include "spvm_typedecl.h"




enum {
  SPVM_ATTRIBUTE_C_ID_MULNUM_T,
  SPVM_ATTRIBUTE_C_ID_POINTER_T,
  SPVM_ATTRIBUTE_C_ID_NATIVE,
  SPVM_ATTRIBUTE_C_ID_PRECOMPILE,
  SPVM_ATTRIBUTE_C_ID_PUBLIC,
  SPVM_ATTRIBUTE_C_ID_PRIVATE,
  SPVM_ATTRIBUTE_C_ID_RW,
  SPVM_ATTRIBUTE_C_ID_RO,
  SPVM_ATTRIBUTE_C_ID_WO,
  SPVM_ATTRIBUTE_C_ID_STATIC,
  SPVM_ATTRIBUTE_C_ID_INTERFACE_T,
  SPVM_ATTRIBUTE_C_ID_REQUIRED,
};

// Field information
struct spvm_attribute {
  int32_t id;
};

const char* SPVM_ATTRIBUTE_get_name(SPVM_COMPILER* compiler, int32_t id);
SPVM_ATTRIBUTE* SPVM_ATTRIBUTE_new(SPVM_COMPILER* compiler);
const char* const* SPVM_ATTRIBUTE_C_ID_NAMES(void);

#endif
