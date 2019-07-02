#ifndef SPVM_RUNTIME_FIELD_H
#define SPVM_RUNTIME_FIELD_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_field {
  int32_t id;
  int32_t name_id;
  int32_t signature_id;
  int32_t basic_type_id;
  int32_t package_id;
  int32_t offset;
  uint16_t index;
  uint16_t flag;
  uint8_t type_dimension;
  uint8_t runtime_type_category;
};

SPVM_RUNTIME_FIELD* SPVM_RUNTIME_FIELD_new();

#endif
