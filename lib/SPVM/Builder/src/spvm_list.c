#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "spvm_list.h"

SPVM_LIST* SPVM_LIST_new(int32_t capacity) {
  
  assert(capacity >= 0);
  
  SPVM_LIST* array = calloc(1, sizeof(SPVM_LIST));
  
  array->length = 0;
  
  if (capacity == 0) {
    array->capacity = 1;
  }
  else {
    array->capacity = capacity;
  }
  
  void** values = calloc(array->capacity, sizeof(void*));
  
  array->values = values;
  
  return array;
}

void SPVM_LIST_maybe_extend(SPVM_LIST* array) {
  
  assert(array);
  
  int32_t length = array->length;
  int32_t capacity = array->capacity;
  
  if (length >= capacity) {
    int32_t new_capacity = capacity * 2;
    
    void** new_values = calloc(new_capacity, sizeof(void*));
    memcpy(new_values, array->values, capacity * sizeof(void*));
    free(array->values);
    array->values = new_values;
    
    array->capacity = new_capacity;
  }
}

void SPVM_LIST_free(SPVM_LIST* array) {
  
  free(array->values);
  free(array);
}

void SPVM_LIST_push(SPVM_LIST* array, void* value) {
  
  SPVM_LIST_maybe_extend(array);
  
  int32_t length = array->length;
  
  *(void**)&array->values[length] = value;
  array->length++;
}

void* SPVM_LIST_fetch(SPVM_LIST* array, int32_t index) {
  assert(array);
  assert(index >= 0);
  assert(index < array->length);
  
  
  return *(void**)&array->values[index];
}

void SPVM_LIST_store(SPVM_LIST* array, int32_t index, void* value) {
  
  assert(array);
  assert(index >= 0);
  assert(index < array->length);
  
  *(void**)&array->values[index] = value;
}

void* SPVM_LIST_pop(SPVM_LIST* array) {
  
  assert(array->length >= 0);
  
  if (array->length == 0) {
    return NULL;
  }
  else {
    array->length--;
    return *(void**)&array->values[array->length];
  }
}

void* SPVM_LIST_shift(SPVM_LIST* array) {
  
  assert(array->length >= 0);
  
  if (array->length == 0) {
    return NULL;
  }
  else {
    void* return_value = array->values[0];
    for (int32_t i = 0; i < array->length - 1; i++) {
      array->values[i] = array->values[i + 1];
    }

    array->length--;
    return return_value;
  }
}
