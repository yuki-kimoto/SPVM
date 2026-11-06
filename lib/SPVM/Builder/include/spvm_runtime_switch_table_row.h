// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_RUNTIME_SWITCH_TABLE_ROW_H
#define SPVM_RUNTIME_SWITCH_TABLE_ROW_H

#include "spvm_typedecl.h"

struct spvm_runtime_switch_table_row {
  int32_t value;
  int32_t index;
};

#endif
