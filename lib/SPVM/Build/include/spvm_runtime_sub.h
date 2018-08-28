#ifndef SPVM_RUNTIME_SUB_H
#define SPVM_RUNTIME_SUB_H

#include "spvm_base.h"

// Field information
struct SPVM_runtime_sub {
  int32_t id;
  int32_t flag;
  int32_t name_id;
  int32_t abs_name_id;
  int32_t signature_id;
  int32_t package_id;
  int32_t file_id;
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
  int32_t info_package_var_ids_base;
  int32_t info_package_var_ids_length;
  int32_t info_field_ids_base;
  int32_t info_field_ids_length;
  int32_t info_sub_ids_base;
  int32_t info_sub_ids_length;
  int32_t info_types_base;
  int32_t info_types_length;
  int32_t info_switch_infos_base;
  int32_t info_switch_infos_length;
};

SPVM_RUNTIME_SUB* SPVM_RUNTIME_SUB_new();

#endif
