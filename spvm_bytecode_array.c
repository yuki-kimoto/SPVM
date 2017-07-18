#include <string.h>
#include <stdlib.h>


#include "spvm_bytecode_array.h"
#include "spvm_util_allocator.h"
#include "spvm_compiler.h"

SPVM_BYTECODE_ARRAY* SPVM_BYTECODE_ARRAY_new(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BYTECODE_ARRAY* bytecodes = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(1, sizeof(SPVM_BYTECODE_ARRAY));
  bytecodes->capacity = 64;
  bytecodes->length = 0;
  
  uint8_t* values = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(bytecodes->capacity, sizeof(uint8_t));
  bytecodes->values = values;
  
  return bytecodes;
}

void SPVM_BYTECODE_ARRAY_push(SPVM_COMPILER* compiler, SPVM_BYTECODE_ARRAY* bytecodes, uint8_t value) {
  (void)compiler;

  int32_t length = bytecodes->length;
  int32_t capacity = bytecodes->capacity;
  
  if (length >= capacity) {
    int32_t new_capacity = capacity * 2;

    uint8_t* new_values = SPVM_UTIL_ALLOCATOR_safe_malloc_i32_zero(new_capacity, sizeof(uint8_t));
    memcpy(new_values, bytecodes->values, capacity * sizeof(uint8_t));
    free(bytecodes->values);
    bytecodes->values = new_values;

    bytecodes->capacity = new_capacity;
  }
  bytecodes->values[length] = value;
  bytecodes->length++;
}

void SPVM_BYTECODE_ARRAY_free(SPVM_COMPILER* compiler, SPVM_BYTECODE_ARRAY* bytecodes) {
  (void)compiler;
  
  free(bytecodes->values);
  free(bytecodes);
}
