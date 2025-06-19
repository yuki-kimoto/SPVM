// Copyright (c) 2023 Yuki Kimoto
// MIT License

#IFNDEF SPVM_RUNTIME_LOCAL_VARS_BASE_H
#DEFINE SPVM_RUNTIME_LOCAL_VARS_BASE_H

#include "spvm_typedecl.h"

struct spvm_runtime_local_vars_base {
  int8_t** byte_vars_base;
  int16_t** short_vars_base;
  int32_t** int_vars_base;
  int64_t** long_vars_base;
  float** float_vars_base;
  double** double_vars_base;
  void*** object_vars_base;
  void*** ref_vars_base;
  int32_t** mortal_stack_length;
  int32_t** mortal_stack_tops_length;
};

#endif
