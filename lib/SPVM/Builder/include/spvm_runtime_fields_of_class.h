#ifndef SPVM_RUNTIME_FIELDS_OF_CLASS_H
#define SPVM_RUNTIME_FIELDS_OF_CLASS_H

#include "spvm_typedecl.h"

struct spvm_runtime_fields_of_class {
  const char* name;
  int32_t name_id;
  int32_t class_id;
  int32_t field_id;
};

#endif
