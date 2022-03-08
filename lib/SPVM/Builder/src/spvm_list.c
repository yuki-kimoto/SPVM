#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "spvm_list.h"
#include "spvm_allocator.h"
#include "spvm_native.h"

SPVM_LIST* SPVM_LIST_new(SPVM_ALLOCATOR* allocator, int32_t capacity, int32_t memory_block_type, SPVM_ENV* env) {
  
  assert(capacity >= 0);
  
  SPVM_LIST* list;
  if (memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_COMPILE_TIME_TEMPORARY) {
    list = SPVM_ALLOCATOR_new_block_compile_tmp(allocator, sizeof(SPVM_LIST));
  }
  else if (memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_COMPILE_TIME_ETERNAL) {
    list = SPVM_ALLOCATOR_new_block_compile_eternal(allocator, sizeof(SPVM_LIST));
  }
  else if (memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_RUN_TIME) {
    list = SPVM_ALLOCATOR_new_block_runtime(allocator, sizeof(SPVM_LIST), env);
  }
  else {
    assert(0);
  }
  
  list->length = 0;
  
  if (capacity == 0) {
    list->capacity = 1;
  }
  else {
    list->capacity = capacity;
  }
  
  void** values;
  if (memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_COMPILE_TIME_TEMPORARY) {
    values = SPVM_ALLOCATOR_new_block_compile_tmp(allocator, list->capacity * sizeof(void*));
  }
  else if (memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_COMPILE_TIME_ETERNAL) {
    values = SPVM_ALLOCATOR_new_block_compile_eternal(allocator, list->capacity * sizeof(void*));
  }
  else if (memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_RUN_TIME) {
    values = SPVM_ALLOCATOR_new_block_runtime(allocator, list->capacity * sizeof(void*), env);
  }
  else {
    assert(0);
  }

  list->values = values;
  
  list->allocator = allocator;
  
  list->memory_block_type = memory_block_type;
  
  list->env = env;
  
  return list;
}

void SPVM_LIST_maybe_extend(SPVM_LIST* list) {
  
  assert(list);
  
  SPVM_ALLOCATOR* allocator = list->allocator;
  
  int32_t length = list->length;
  int32_t capacity = list->capacity;
  
  if (length >= capacity) {
    int32_t new_capacity = capacity * 2;
    
    void** new_values;
    if (list->memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_COMPILE_TIME_TEMPORARY) {
      new_values = SPVM_ALLOCATOR_new_block_compile_tmp(allocator, new_capacity * sizeof(void*));
    }
    else if (list->memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_COMPILE_TIME_ETERNAL) {
      new_values = SPVM_ALLOCATOR_new_block_compile_eternal(allocator, new_capacity * sizeof(void*));
    }
    else if (list->memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_RUN_TIME) {
      new_values = SPVM_ALLOCATOR_new_block_runtime(allocator, new_capacity * sizeof(void*), list->env);
    }
    else {
      assert(0);
    }
    memcpy(new_values, list->values, capacity * sizeof(void*));
    if (list->memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_COMPILE_TIME_TEMPORARY) {
      SPVM_ALLOCATOR_free_block_compile_tmp(allocator, list->values);
    }
    else if (list->memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_COMPILE_TIME_ETERNAL) {
      // Nothing
    }
    else if (list->memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_RUN_TIME) {
      SPVM_ALLOCATOR_free_block_runtime(allocator, list->values, list->env);
    }
    else {
      assert(0);
    }

    list->values = new_values;
    
    list->capacity = new_capacity;
  }
}

void SPVM_LIST_free(SPVM_LIST* list) {

  SPVM_ALLOCATOR* allocator = list->allocator;

  if (list->memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_COMPILE_TIME_TEMPORARY) {
    SPVM_ALLOCATOR_free_block_compile_tmp(allocator, list->values);
    SPVM_ALLOCATOR_free_block_compile_tmp(allocator, list);
  }
  else if (list->memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_COMPILE_TIME_ETERNAL) {
    // Nothing
  }
  else if (list->memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_RUN_TIME) {
    SPVM_ALLOCATOR_free_block_runtime(allocator, list->values, list->env);
    SPVM_ALLOCATOR_free_block_runtime(allocator, list, list->env);
  }
  else {
    assert(0);
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
