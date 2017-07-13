#ifndef SPVM_DYNAMIC_ARRAY_H
#define SPVM_DYNAMIC_ARRAY_H

#include "spvm_base.h"

struct SPVM_dynamic_array {
  void** values;
  int32_t length;
  int32_t capacity;
};

SPVM_DYNAMIC_ARRAY* SPVM_DYNAMIC_ARRAY_new(int32_t capacity);
void SPVM_DYNAMIC_ARRAY_free(SPVM_DYNAMIC_ARRAY* array);
void SPVM_DYNAMIC_ARRAY_maybe_extend(SPVM_DYNAMIC_ARRAY* array);

void SPVM_DYNAMIC_ARRAY_push(SPVM_DYNAMIC_ARRAY* array, void* value);
void* SPVM_DYNAMIC_ARRAY_fetch(SPVM_DYNAMIC_ARRAY* array, int32_t index);
void SPVM_DYNAMIC_ARRAY_store(SPVM_DYNAMIC_ARRAY* array, int32_t index, void* value);
void* SPVM_DYNAMIC_ARRAY_pop(SPVM_DYNAMIC_ARRAY* array);

#endif
