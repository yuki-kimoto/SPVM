// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_SWITCH_INFO_H
#define SPVM_RUNTIME_SWITCH_INFO_H

#include "spvm_typedecl.h"

enum {
  SPVM_RUNTIME_SWITCH_INFO_C_ALGORITHM_UNKNOWN,
  SPVM_RUNTIME_SWITCH_INFO_C_ALGORITHM_LINEAR_SEARCH,
  SPVM_RUNTIME_SWITCH_INFO_C_ALGORITHM_JUMP_TABLE,
  SPVM_RUNTIME_SWITCH_INFO_C_ALGORITHM_BINARY_SEARCH,
};

struct spvm_runtime_switch_info {
  SPVM_RUNTIME_CASE_INFO* case_infos;
  SPVM_RUNTIME_SWITCH_TABLE_ROW* table_rows;
  int32_t case_infos_length;
  int32_t default_opcode_index;
  int32_t opcode_index;
  int32_t table_rows_length;
  int32_t algorithm;
};

#endif
