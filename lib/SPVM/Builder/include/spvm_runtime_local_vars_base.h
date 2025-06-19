// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_LOCAL_VARS_BASE_H
#define SPVM_RUNTIME_LOCAL_VARS_BASE_H

#include "spvm_typedecl.h"

struct spvm_runtime_local_vars_base {
  void** head;
  void** byte_vars_base;
  void** short_vars_base;
  void** int_vars_base;
  void** long_vars_base;
  void** float_vars_base;
  void** double_vars_base;
  void** object_vars_base;
  void** ref_vars_base;
  void** mortal_stack_base;
  void** mortal_stack_tops_base;
};

#endif
