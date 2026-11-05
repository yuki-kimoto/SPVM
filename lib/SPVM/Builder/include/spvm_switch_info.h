// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_SWITCH_INFO_H
#define SPVM_SWITCH_INFO_H

#include "spvm_typedecl.h"

// Parser information
struct spvm_switch_info {
  SPVM_LIST* case_infos;
  SPVM_OP* op_default;
  int32_t default_opcode_index;
  int32_t opcode_index;
};

SPVM_SWITCH_INFO* SPVM_SWITCH_INFO_new(SPVM_COMPILER* compiler);

#endif
