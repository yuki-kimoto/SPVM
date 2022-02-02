#ifndef SPVM_BASIC_TYPE_H
#define SPVM_BASIC_TYPE_H

#include "spvm_typedecl.h"




enum {
  SPVM_BASIC_TYPE_C_ID_UNKNOWN,
  SPVM_BASIC_TYPE_C_ID_UNDEF,
  SPVM_BASIC_TYPE_C_ID_VOID,
  SPVM_BASIC_TYPE_C_ID_BYTE,
  SPVM_BASIC_TYPE_C_ID_SHORT,
  SPVM_BASIC_TYPE_C_ID_INT,
  SPVM_BASIC_TYPE_C_ID_LONG,
  SPVM_BASIC_TYPE_C_ID_FLOAT,
  SPVM_BASIC_TYPE_C_ID_DOUBLE,
  SPVM_BASIC_TYPE_C_ID_STRING,
  SPVM_BASIC_TYPE_C_ID_ANY_OBJECT,
  SPVM_BASIC_TYPE_C_ID_OARRAY,
  SPVM_BASIC_TYPE_C_ID_BYTE_OBJECT,
  SPVM_BASIC_TYPE_C_ID_SHORT_OBJECT,
  SPVM_BASIC_TYPE_C_ID_INT_OBJECT,
  SPVM_BASIC_TYPE_C_ID_LONG_OBJECT,
  SPVM_BASIC_TYPE_C_ID_FLOAT_OBJECT,
  SPVM_BASIC_TYPE_C_ID_DOUBLE_OBJECT,
  SPVM_BASIC_TYPE_C_ID_BOOL_OBJECT,
  SPVM_BASIC_TYPE_C_ID_STRING_OBJECT,
};

enum {
  SPVM_BASIC_TYPE_C_NUMERIC_OBJECT_UPGRADE_SHIFT = 9,
};

struct spvm_basic_type {
  const char* name;
  SPVM_CLASS* class;
  int32_t id;
  int32_t fail_load;
};

SPVM_BASIC_TYPE* SPVM_BASIC_TYPE_new(SPVM_COMPILER* compiler);
const char* const* SPVM_BASIC_TYPE_C_ID_NAMES(void);

#endif
