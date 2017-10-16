#ifndef SPVM_PACKAGE_H
#define SPVM_PACKAGE_H

#include "spvm_base.h"

struct SPVM_package {
  SPVM_OP* op_name;
  SPVM_OP* op_type;
  SPVM_DYNAMIC_ARRAY* op_fields;
  SPVM_HASH* op_field_symtable;
  int32_t id;
  SPVM_OP* op_sub_destructor;
  SPVM_DYNAMIC_ARRAY* native_subs;
};

SPVM_PACKAGE* SPVM_PACKAGE_new(SPVM_COMPILER* compiler);

int32_t SPVM_PACKAGE_get_object_fields_length(SPVM_COMPILER* compiler, SPVM_PACKAGE* package);

#endif
