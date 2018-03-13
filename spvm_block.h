#ifndef SPVM_BLOCK_H
#define SPVM_BLOCK_H

#include "spvm_base.h"

struct SPVM_block {
  int32_t id;
  int32_t need_leave_scope;
};

SPVM_BLOCK* SPVM_BLOCK_new(SPVM_COMPILER* compiler);

enum {
  // Block flag
  SPVM_BLOCK_C_FLAG_NORMAL,
  SPVM_BLOCK_C_FLAG_IF,
  SPVM_BLOCK_C_FLAG_ELSE,
  SPVM_BLOCK_C_FLAG_LOOP_STATEMENTS,
  SPVM_BLOCK_C_FLAG_SWITCH,
  SPVM_BLOCK_C_FLAG_SUB,
  SPVM_BLOCK_C_FLAG_EVAL,
  SPVM_BLOCK_C_FLAG_LOOP_INIT,
};

#endif
