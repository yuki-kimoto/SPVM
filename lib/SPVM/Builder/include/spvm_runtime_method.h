#ifndef SPVM_RUNTIME_METHOD_H
#define SPVM_RUNTIME_METHOD_H

#include "spvm_typedecl.h"

// Method information
struct spvm_runtime_method {
  void* precompile_address;
  void* native_address;
  int32_t return_type_id;
  SPVM_LIST* arg_type_ids;
  SPVM_LIST* arg_mem_ids;
  const char* name;
  const char* signature;
  int32_t opcodes_base;
  int32_t opcodes_length;
  int32_t id;
  int32_t class_id;
  int32_t flag;
  int8_t is_class_method;
};

#endif
