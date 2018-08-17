#ifndef SPVM_RUNTIME_SUB_H
#define SPVM_RUNTIME_SUB_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_sub {
  int32_t id;
  int32_t flag;
  const char* name;
  const char* abs_name;
  const char* signature;
  SPVM_PACKAGE* package;
  void* precompile_address;
  void* native_address;
};

SPVM_RUNTIME_SUB* SPVM_RUNTIME_SUB_new();

#endif
