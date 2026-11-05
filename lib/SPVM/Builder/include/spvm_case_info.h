// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_CASE_INFO_H
#define SPVM_CASE_INFO_H

#include "spvm_typedecl.h"

struct spvm_case_info {
  SPVM_OP* op_case_info;
  const char* method_abs_name;
  int32_t value;
  int32_t goto_opcode_index;
};

SPVM_CASE_INFO* SPVM_CASE_INFO_new(SPVM_COMPILER* compiler);

#endif
