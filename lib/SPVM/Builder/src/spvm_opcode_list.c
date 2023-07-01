// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "spvm_opcode_list.h"
#include "spvm_allocator.h"
#include "spvm_compiler.h"
#include "spvm_opcode.h"

SPVM_OPCODE_LIST* SPVM_OPCODE_LIST_new(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_OPCODE_LIST* opcodes = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, sizeof(SPVM_OPCODE_LIST));
  opcodes->capacity = 64;
  opcodes->length = 0;
  
  int64_t values_size = (int64_t)opcodes->capacity * (int64_t)sizeof(SPVM_OPCODE);
  SPVM_OPCODE* values = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, values_size);
  opcodes->values = values;
  
  return opcodes;
}

void SPVM_OPCODE_LIST_push_opcode(SPVM_COMPILER* compiler, SPVM_OPCODE_LIST* opcodes, SPVM_OPCODE* opcode) {
  (void)compiler;

  int32_t length = opcodes->length;
  int32_t capacity = opcodes->capacity;
  
  if (length >= capacity) {
    int32_t new_capacity = capacity * 2;
    
    int64_t new_values_size = (int64_t)new_capacity * (int64_t)sizeof(SPVM_OPCODE);
    SPVM_OPCODE* new_values = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, new_values_size);
    memcpy(new_values, opcodes->values, capacity * sizeof(SPVM_OPCODE));
    opcodes->values = new_values;
    
    opcodes->capacity = new_capacity;
  }
  
  assert(opcode);
  memcpy(&opcodes->values[length], opcode, sizeof(SPVM_OPCODE));

  opcodes->length++;
}

void SPVM_OPCODE_LIST_free(SPVM_COMPILER* compiler, SPVM_OPCODE_LIST* opcodes) {
  (void)compiler;
}
