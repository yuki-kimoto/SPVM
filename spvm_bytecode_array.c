#include <string.h>
#include <stdlib.h>


#include "spvm_bytecode_array.h"
#include "spvm_util_allocator.h"
#include "spvm_compiler.h"

SPVM_BYTECODE_ARRAY* SPVM_BYTECODE_ARRAY_new(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_BYTECODE_ARRAY* bytecodes = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_BYTECODE_ARRAY));
  bytecodes->capacity = 64;
  bytecodes->length = 0;
  
  int64_t values_byte_size = (int64_t)bytecodes->capacity * (int64_t)sizeof(int32_t);
  int32_t* values = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(values_byte_size);
  bytecodes->values = values;
  
  // Add 4 byte because 0 mean no bytecode
  SPVM_BYTECODE_ARRAY_push_int(compiler, bytecodes, 0);
  
  return bytecodes;
}

void SPVM_BYTECODE_ARRAY_push_int(SPVM_COMPILER* compiler, SPVM_BYTECODE_ARRAY* bytecodes, int32_t value) {
  (void)compiler;

  int32_t length = bytecodes->length;
  int32_t capacity = bytecodes->capacity;
  
  if (length >= capacity) {
    int32_t new_capacity = capacity * 2;
    
    int64_t new_values_byte_size = (int64_t)new_capacity * (int64_t)sizeof(int32_t);
    int32_t* new_values = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(new_values_byte_size);
    memcpy(new_values, bytecodes->values, capacity * sizeof(int32_t));
    free(bytecodes->values);
    bytecodes->values = new_values;

    bytecodes->capacity = new_capacity;
  }
  *(int32_t*)&bytecodes->values[length] = value;
  bytecodes->length++;
}

void SPVM_BYTECODE_ARRAY_free(SPVM_COMPILER* compiler, SPVM_BYTECODE_ARRAY* bytecodes) {
  (void)compiler;
  
  free(bytecodes->values);
  free(bytecodes);
}
