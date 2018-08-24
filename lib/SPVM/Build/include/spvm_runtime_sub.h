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
  int32_t package_id;
  void* precompile_address;
  void* native_address;
  const char* file;
  int32_t line;
  int32_t args_alloc_length;
  int32_t vars_alloc_length;
  int32_t return_basic_type_id;
  int32_t return_type_dimension;
  int32_t return_type_flag;
  int32_t opcode_base;
  int32_t mortal_stack_length;
  int32_t arg_ids_base;
  int32_t arg_ids_length;
};

SPVM_RUNTIME_SUB* SPVM_RUNTIME_SUB_new();

#endif
