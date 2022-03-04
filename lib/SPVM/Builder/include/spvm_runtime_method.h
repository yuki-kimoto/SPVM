#ifndef SPVM_RUNTIME_METHOD_H
#define SPVM_RUNTIME_METHOD_H

#include "spvm_typedecl.h"

// Method information
struct spvm_runtime_method {
  void* precompile_address;
  void* native_address;
  SPVM_TYPE* return_type;
  SPVM_LIST* arg_types;
  SPVM_LIST* arg_mem_ids;
  const char* name;
  const char* signature;
  int32_t opcodes_base;
  int32_t opcodes_length;
  int32_t id;
};

#endif
