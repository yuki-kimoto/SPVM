#ifndef SPVM_FIELD_H
#define SPVM_FIELD_H

#include "spvm_base.h"

// Field information
struct SPVM_field {
  SPVM_OP* op_type;
  SPVM_OP* op_name;
  const char* abs_name;
  int32_t constant_pool_address;
  int32_t abs_name_constant_pool_address;
  int32_t package_byte_offset;
};

SPVM_FIELD* SPVM_FIELD_new(SPVM* spvm);
int32_t SPVM_FIELD_get_byte_size(SPVM* spvm, SPVM_FIELD* field);

#endif
