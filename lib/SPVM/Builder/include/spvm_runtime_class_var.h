#ifndef SPVM_RUNTIME_CLASS_VAR_H
#define SPVM_RUNTIME_CLASS_VAR_H

#include "spvm_typedecl.h"

struct spvm_runtime_class_var {
  const char* name;
  const char* signature;
  int32_t id;
  int32_t name_id;
  int32_t signature_id;
  int32_t class_id;
  int32_t type_id;
};

#endif
