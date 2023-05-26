// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_BLOCK_H
#define SPVM_BLOCK_H

#include "spvm_typedecl.h"

enum {
  // Block flag
  SPVM_BLOCK_C_ID_NORMAL,
  SPVM_BLOCK_C_ID_IF,
  SPVM_BLOCK_C_ID_ELSE,
  SPVM_BLOCK_C_ID_LOOP_STATEMENTS,
  SPVM_BLOCK_C_ID_SWITCH,
  SPVM_BLOCK_C_ID_METHOD,
  SPVM_BLOCK_C_ID_EVAL,
  SPVM_BLOCK_C_ID_LOOP_INIT,
};

struct spvm_block {
  int32_t id;
  int32_t no_scope;
  int32_t has_object_var_decls;
  int32_t need_leave_scope;
};

SPVM_BLOCK* SPVM_BLOCK_new(SPVM_COMPILER* compiler);

#endif
