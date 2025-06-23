// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_CALL_STACK_FRAME_INFO_H
#define SPVM_RUNTIME_CALL_STACK_FRAME_INFO_H

#include "spvm_typedecl.h"

struct spvm_runtime_call_stack_frame_info {
  SPVM_RUNTIME_METHOD* method;
  int64_t** long_vars_address;
  double** double_vars_address;
  void*** object_vars_address;
  void*** ref_vars_address;
  int32_t** int_vars_address;
  float** float_vars_address;
  int32_t** mortal_stack_address;
  int32_t** mortal_stack_tops_address;
  int16_t** short_vars_address;
  int8_t** byte_vars_address;
  void* memory_block;
  int32_t memory_block_offset;
};

#endif
