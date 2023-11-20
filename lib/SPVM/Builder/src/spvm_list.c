// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "spvm_list.h"
#include "spvm_allocator.h"

SPVM_LIST* SPVM_LIST_new(SPVM_ALLOCATOR* allocator, int32_t capacity, int32_t memory_block_type) {
  
  assert(capacity >= 0);
  
  SPVM_LIST* list;
  if (memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
    list = SPVM_ALLOCATOR_alloc_memory_block_tmp(allocator, sizeof(SPVM_LIST));
  }
  else if (memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
    list = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(SPVM_LIST));
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
  if (memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
    values = SPVM_ALLOCATOR_alloc_memory_block_tmp(allocator, list->capacity * sizeof(void*));
  }
  else if (memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
    values = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, list->capacity * sizeof(void*));
  }
  else {
    assert(0);
  }

  list->values = values;
  
  list->allocator = allocator;
  
  list->memory_block_type = memory_block_type;
  
  return list;
}

SPVM_LIST* SPVM_LIST_new_list_permanent(SPVM_ALLOCATOR* allocator, int32_t capacity) {
  (void)allocator;

  int32_t memory_block_type = SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT;
  SPVM_LIST* list = SPVM_LIST_new(allocator, capacity, memory_block_type);
  
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
    if (list->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
      new_values = SPVM_ALLOCATOR_alloc_memory_block_tmp(allocator, new_capacity * sizeof(void*));
    }
    else if (list->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
      new_values = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, new_capacity * sizeof(void*));
    }
    else {
      assert(0);
    }
    memcpy(new_values, list->values, capacity * sizeof(void*));
    if (list->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
      SPVM_ALLOCATOR_free_memory_block_tmp(allocator, list->values);
    }
    else if (list->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
      // Nothing
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

  if (list->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
    SPVM_ALLOCATOR_free_memory_block_tmp(allocator, list->values);
    SPVM_ALLOCATOR_free_memory_block_tmp(allocator, list);
  }
  else if (list->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
    // Nothing
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

void SPVM_LIST_unshift(SPVM_LIST* list, void* value) {
  
  SPVM_LIST_maybe_extend(list);
  
  int32_t length = list->length;
  
  memmove(list->values + 1, list->values, sizeof(void*) * length);
  
  *(void**)&list->values[0] = value;
  list->length++;
}

void* SPVM_LIST_get(SPVM_LIST* list, int32_t index) {
  assert(list);
  assert(index >= 0);
  assert(index < list->length);
  
  
  return *(void**)&list->values[index];
}

void SPVM_LIST_set(SPVM_LIST* list, int32_t index, void* value) {
  
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

void SPVM_LIST_clear(SPVM_LIST* list) {
  
  while (list->length > 0) {
    list->length--;
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
