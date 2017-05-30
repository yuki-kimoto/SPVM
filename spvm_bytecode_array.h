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
SPVM_BYTECODE_ARRAY* SPVM_BYTECODE_ARRAY_new(SPVM* spvm);
void SPVM_BYTECODE_ARRAY_push(SPVM* spvm, SPVM_BYTECODE_ARRAY* bytecodes, uint8_t value);
void SPVM_BYTECODE_ARRAY_free(SPVM* spvm, SPVM_BYTECODE_ARRAY* bytecodes);

#endif
