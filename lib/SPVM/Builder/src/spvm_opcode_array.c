#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "spvm_opcode_array.h"
#include "spvm_allocator.h"
#include "spvm_compiler.h"
#include "spvm_opcode.h"

SPVM_OPCODE_ARRAY* SPVM_OPCODE_ARRAY_new(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_OPCODE_ARRAY* opcodes = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, sizeof(SPVM_OPCODE_ARRAY));
  opcodes->capacity = 64;
  opcodes->length = 0;
  
  int64_t values_byte_size = (int64_t)opcodes->capacity * (int64_t)sizeof(SPVM_OPCODE);
  SPVM_OPCODE* values = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, values_byte_size);
  opcodes->values = values;
  
  // Add 1 opcode because 0 mean no opcode
  SPVM_OPCODE opcode;
  memset(&opcode, 0, sizeof(SPVM_OPCODE));
  SPVM_OPCODE_ARRAY_push_opcode(compiler, opcodes, &opcode);
  
  return opcodes;
}

void SPVM_OPCODE_ARRAY_push_opcode(SPVM_COMPILER* compiler, SPVM_OPCODE_ARRAY* opcodes, SPVM_OPCODE* opcode) {
  (void)compiler;

  int32_t length = opcodes->length;
  int32_t capacity = opcodes->capacity;
  
  if (length >= capacity) {
    int32_t new_capacity = capacity * 2;
    
    int64_t new_values_byte_size = (int64_t)new_capacity * (int64_t)sizeof(SPVM_OPCODE);
    SPVM_OPCODE* new_values = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, new_values_byte_size);
    memcpy(new_values, opcodes->values, capacity * sizeof(SPVM_OPCODE));
    opcodes->values = new_values;
    
    opcodes->capacity = new_capacity;
  }
  
  assert(opcode);
  memcpy(&opcodes->values[length], opcode, sizeof(SPVM_OPCODE));

  opcodes->length++;
}

void SPVM_OPCODE_ARRAY_free(SPVM_COMPILER* compiler, SPVM_OPCODE_ARRAY* opcodes) {
  (void)compiler;
}
