#ifndef SPVM_FIELD_INFO_H
#define SPVM_FIELD_INFO_H

#include "spvm_base.h"

// Field information
struct SPVM_field_info {
  SPVM_OP* op_type;
  SPVM_OP* op_name;
  const char* abs_name;
  int32_t id;
  int32_t index;
  _Bool is_private;
};

SPVM_FIELD_INFO* SPVM_FIELD_INFO_new(SPVM_COMPILER* compiler);
int32_t SPVM_FIELD_INFO_get_byte_size(SPVM_COMPILER* compiler, SPVM_FIELD_INFO* field);

#endif
