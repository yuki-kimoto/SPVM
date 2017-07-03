#ifndef SPVM_PACKAGE_H
#define SPVM_PACKAGE_H

#include "spvm_base.h"

struct SPVM_package {
  SPVM_OP* op_name;
  SPVM_OP* op_type;
  SPVM_ARRAY* op_fields;
  SPVM_ARRAY* op_subs;
  int32_t constant_pool_index;
  int32_t name_constant_pool_index;
};

SPVM_PACKAGE* SPVM_PACKAGE_new(SPVM_COMPILER* compiler);

int32_t SPVM_PACKAGE_get_ref_fields_length(SPVM_COMPILER* compiler, SPVM_PACKAGE* package);

#endif
