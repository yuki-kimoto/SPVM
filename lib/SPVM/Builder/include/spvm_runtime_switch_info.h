// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_SWITCH_INFO_H
#define SPVM_RUNTIME_SWITCH_INFO_H

#include "spvm_typedecl.h"

#include "spvm_runtime_case_info.h"

struct spvm_runtime_switch_info {
  SPVM_RUNTIME_CASE_INFO* case_infos;
  int32_t case_infos_length;
  int32_t default_opcode_index;
  int32_t opcode_index;
};

#endif
