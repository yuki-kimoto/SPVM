#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "spvm_list.h"
#include "spvm_compiler.h"
#include "spvm_allocator.h"

SPVM_LIST* SPVM_LIST_new(SPVM_COMPILER* compiler, int32_t capacity, int32_t memory_block_type) {
  
  assert(capacity >= 0);
  
  SPVM_LIST* list;
  if (memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_COMPILE_TIME_ETERNAL) {
    list = SPVM_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_LIST));
  }
  else {
    list = SPVM_ALLOCATOR_new_block_tmp(compiler, sizeof(SPVM_LIST));
  }
  
  list->length = 0;
  
  if (capacity == 0) {
    list->capacity = 1;
  }
  else {
    list->capacity = capacity;
  }
  
  void** values;
  if (memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_COMPILE_TIME_ETERNAL) {
    values = SPVM_ALLOCATOR_safe_malloc_zero(compiler, list->capacity * sizeof(void*));
  }
  else {
    values = SPVM_ALLOCATOR_new_block_tmp(compiler, list->capacity * sizeof(void*));
  }
  list->values = values;
  
  list->compiler = compiler;
  
  list->memory_block_type = memory_block_type;
  
  return list;
}

void SPVM_LIST_maybe_extend(SPVM_LIST* list) {
  
  assert(list);
  
  SPVM_COMPILER* compiler = list->compiler;
  
  int32_t length = list->length;
  int32_t capacity = list->capacity;
  
  if (length >= capacity) {
    int32_t new_capacity = capacity * 2;
    
    void** new_values;
    if (list->memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_COMPILE_TIME_ETERNAL) {
      new_values = SPVM_ALLOCATOR_safe_malloc_zero(compiler, new_capacity * sizeof(void*));
    }
    else {
      new_values = SPVM_ALLOCATOR_new_block_tmp(compiler, new_capacity * sizeof(void*));
    }
    memcpy(new_values, list->values, capacity * sizeof(void*));
    if (list->memory_block_type != SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_COMPILE_TIME_ETERNAL) {
      SPVM_ALLOCATOR_free_tmp(compiler, list->values);
    }
    list->values = new_values;
    
    list->capacity = new_capacity;
  }
}

void SPVM_LIST_free(SPVM_LIST* list) {

  SPVM_COMPILER* compiler = list->compiler;
  
  if (list->memory_block_type != SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_COMPILE_TIME_ETERNAL) {
    SPVM_ALLOCATOR_free_tmp(compiler, list->values);
    SPVM_ALLOCATOR_free_tmp(compiler, list);
  }
}

void SPVM_LIST_push(SPVM_LIST* list, void* value) {
  
  SPVM_LIST_maybe_extend(list);
  
  int32_t length = list->length;
  
  *(void**)&list->values[length] = value;
  list->length++;
}

void* SPVM_LIST_fetch(SPVM_LIST* list, int32_t index) {
  assert(list);
  assert(index >= 0);
  assert(index < list->length);
  
  
  return *(void**)&list->values[index];
}

void SPVM_LIST_store(SPVM_LIST* list, int32_t index, void* value) {
  
  assert(list);
  assert(index >= 0);
  assert(index < list->length);
  
  *(void**)&list->values[index] = value;
}

void* SPVM_LIST_pop(SPVM_LIST* list) {
  
  assert(list->length >= 0);
  
  if (list->length == 0) {
    return NULL;
  }
  else {
    list->length--;
    return *(void**)&list->values[list->length];
  }
}

void* SPVM_LIST_shift(SPVM_LIST* list) {
  
  assert(list->length >= 0);
  
  if (list->length == 0) {
    return NULL;
  }
  else {
    void* return_value = list->values[0];
    for (int32_t i = 0; i < list->length - 1; i++) {
      list->values[i] = list->values[i + 1];
    }

    list->length--;
    return return_value;
  }
}
