#ifndef SPVM_FIELD_H
#define SPVM_FIELD_H

#include "spvm_base.h"

enum {
  SPVM_FIELD_C_FLAG_PRIVATE = 1,
};

struct SPVM_field {
  SPVM_OP* op_field;
  SPVM_OP* op_name;
  SPVM_PACKAGE* package;
  SPVM_TYPE* type;
  const char* signature;
  const char* name;
  int32_t id;
  int32_t index;
  int32_t flag;
  int32_t runtime_type;
  int8_t is_captured;
};

SPVM_FIELD* SPVM_FIELD_new(SPVM_COMPILER* compiler);

#endif
