#ifndef SPVM_BYTECODE_ARRAY_H
#define SPVM_BYTECODE_ARRAY_H

#include "spvm_base.h"

// Array
struct SPVM_bytecode_array {
  uint8_t* values;
  int32_t length;
  int32_t capacity;
};

// Array function
SPVM_BYTECODE_ARRAY* SPVM_BYTECODE_ARRAY_new(SPVM_* spvm);
void SPVM_BYTECODE_ARRAY_push(SPVM_* spvm, SPVM_BYTECODE_ARRAY* bytecodes, uint8_t value);
void SPVM_BYTECODE_ARRAY_free(SPVM_* spvm, SPVM_BYTECODE_ARRAY* bytecodes);

#endif
