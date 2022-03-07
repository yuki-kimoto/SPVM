#ifndef SPVM_RUNTIME_METHODS_OF_CLASS_H
#define SPVM_RUNTIME_METHODS_OF_CLASS_H

#include "spvm_typedecl.h"

struct spvm_runtime_methods_of_class {
  const char* name;
  int32_t name_id;
  int32_t class_id;
  int32_t method_id;
};

#endif
 