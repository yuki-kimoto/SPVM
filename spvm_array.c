#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "spvm_array.h"
#include "spvm_util_allocator.h"
#include "spvm_compiler.h"

SPVM_ARRAY* SPVM_ARRAY_new(int32_t capacity) {
  
  assert(capacity >= 0);
  
  SPVM_ARRAY* array = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(1, sizeof(SPVM_ARRAY));
  array->length = 0;
  
  if (capacity == 0) {
    array->capacity = 128;
  }
  else {
    array->capacity = capacity;
  }
  
  void** values = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(array->capacity, sizeof(void*));
  
  array->values = values;
  
  return array;
}

void SPVM_ARRAY_maybe_extend(SPVM_ARRAY* array) {
  
  assert(array);
  
  int32_t length = array->length;
  int32_t capacity = array->capacity;
  
  if (length >= capacity) {
    int32_t new_capacity = capacity * 2;
    array->values = SPVM_UTIL_ALLOCATOR_safe_realloc_i32(array->values, new_capacity, sizeof(void*));
    array->capacity = new_capacity;
  }
}

void SPVM_ARRAY_free(SPVM_ARRAY* array) {
  
  free(array->values);
  free(array);
}

void SPVM_ARRAY_push(SPVM_ARRAY* array, void* value) {
  
  SPVM_ARRAY_maybe_extend(array);
  
  int32_t length = array->length;
  
  *(void**)&array->values[length] = value;
  array->length++;
}

void* SPVM_ARRAY_fetch(SPVM_ARRAY* array, int32_t index) {
  
  assert(array);
  assert(index >= 0);
  assert(index < array->length);
  
  return *(void**)&array->values[index];
}

void SPVM_ARRAY_store(SPVM_ARRAY* array, int32_t index, void* value) {
  
  assert(array);
  assert(index >= 0);
  assert(index < array->length);
  
  *(void**)&array->values[index] = value;
}

void* SPVM_ARRAY_pop(SPVM_ARRAY* array) {
  
  assert(array->length >= 0);
  
  if (array->length == 0) {
    return NULL;
  }
  else {
    array->length--;
    return *(void**)&array->values[array->length];
  }
}
