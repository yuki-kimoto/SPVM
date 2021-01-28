#ifndef SPVM_OPCODE_ARRAY_H
#define SPVM_OPCODE_ARRAY_H

#include "spvm_typedef.h"

// Array
struct SPVM_opcode_array {
  SPVM_OPCODE* values;
  int32_t length;
  int32_t capacity;
};

// Array function
SPVM_OPCODE_ARRAY* SPVM_OPCODE_ARRAY_new(SPVM_COMPILER* compiler);
void SPVM_OPCODE_ARRAY_free(SPVM_COMPILER* compiler, SPVM_OPCODE_ARRAY* opcodes);
void SPVM_OPCODE_ARRAY_push_opcode(SPVM_COMPILER* compiler, SPVM_OPCODE_ARRAY* opcodes, SPVM_OPCODE* opcode);

#endif
