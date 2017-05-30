#ifndef SPVM_PACKAGE_H
#define SPVM_PACKAGE_H

#include "spvm_base.h"

struct SPVM_package {
  SPVM_OP* op_name;
  SPVM_OP* op_type;
  SPVM_ARRAY* op_fields;
  SPVM_ARRAY* op_subs;
  int32_t byte_size;
  int32_t constant_pool_address;
  int32_t name_constant_pool_address;
  int32_t ref_fields_count;
};

SPVM_PACKAGE* SPVM_PACKAGE_new(SPVM* spvm);

#endif
