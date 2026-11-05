// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_CASE_INFO_H
#define SPVM_RUNTIME_CASE_INFO_H

#include "spvm_typedecl.h"

struct spvm_runtime_case_info {
  const char* method_abs_name;
  int32_t case_value;
  int32_t goto_opcode_index;
};

#endif
