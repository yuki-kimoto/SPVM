#ifndef SPVM_CONSTANT_POOL_SUB_H
#define SPVM_CONSTANT_POOL_SUB_H

#include "spvm_base.h"

struct SPVM_constant_pool_sub {
  void* native_address;
  void* jit_address;
  int32_t opcode_base;
  int32_t opcode_length;
  int32_t file_name_id;
  int32_t abs_name_id;
  int32_t call_sub_arg_stack_max;
  int32_t mys_length;
  int32_t args_length;
  int32_t object_args_length;
  int32_t object_args_base;
  int32_t object_mys_length;
  int32_t object_mys_base;
  int32_t return_type_id;
  int32_t arg_type_ids_base;
  int32_t my_type_ids_base;
  int32_t eval_stack_max_length;
  int32_t auto_dec_ref_count_stack_max_length;
  int32_t call_count;
  int32_t on_stack_replacement_jump_opcode_indexes_base;
  int32_t loop_structure_count;
  _Bool is_native;
  _Bool is_destructor;
  _Bool is_void;
  _Bool is_jit;
  _Bool disable_jit;
};

#endif
