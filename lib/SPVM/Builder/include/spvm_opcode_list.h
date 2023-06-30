// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_OPCODE_LIST_H
#define SPVM_OPCODE_LIST_H

#include "spvm_typedecl.h"

// Array
struct spvm_opcode_list {
  SPVM_OPCODE* values;
  int32_t length;
  int32_t capacity;
};

// Array function
SPVM_OPCODE_LIST* SPVM_OPCODE_LIST_new(SPVM_COMPILER* compiler);
void SPVM_OPCODE_LIST_free(SPVM_COMPILER* compiler, SPVM_OPCODE_LIST* opcodes);
void SPVM_OPCODE_LIST_push_opcode(SPVM_COMPILER* compiler, SPVM_OPCODE_LIST* opcodes, SPVM_OPCODE* opcode);

#endif
