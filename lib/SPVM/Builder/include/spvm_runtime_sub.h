#ifndef SPVM_RUNTIME_SUB_H
#define SPVM_RUNTIME_SUB_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_sub {
  int32_t id;
  int32_t name_id;
  int32_t signature_id;
  int32_t package_id;
  int32_t file_id;
  int32_t line;
  int32_t return_basic_type_id;
  int32_t opcodes_base;
  int32_t arg_ids_base;
  uint16_t opcodes_length;
  uint16_t return_type_flag;
  uint16_t flag;
  uint16_t mortal_stack_length;
  uint16_t arg_ids_length;
  uint16_t byte_vars_alloc_length;
  uint16_t short_vars_alloc_length;
  uint16_t int_vars_alloc_length;
  uint16_t long_vars_alloc_length;
  uint16_t float_vars_alloc_length;
  uint16_t double_vars_alloc_length;
  uint16_t object_vars_alloc_length;
  uint16_t ref_vars_alloc_length;
  uint8_t return_type_dimension;
  uint8_t call_type_id;
  uint8_t args_alloc_length;
  uint8_t return_runtime_type_category;
};

SPVM_RUNTIME_SUB* SPVM_RUNTIME_SUB_new();

#endif
