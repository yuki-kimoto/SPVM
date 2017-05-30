#ifndef SPVM_ARRAY_H
#define SPVM_ARRAY_H

#include "spvm_base.h"

struct SPVM_array {
  void** values;
  int32_t length;
  int32_t capacity;
};

SPVM_ARRAY* SPVM_ARRAY_new(SPVM* spvm, int32_t capacity);
void SPVM_ARRAY_free(SPVM* spvm, SPVM_ARRAY* array);
void SPVM_ARRAY_maybe_extend(SPVM* spvm, SPVM_ARRAY* array);

void SPVM_ARRAY_push(SPVM* spvm, SPVM_ARRAY* array, void* value);
void* SPVM_ARRAY_fetch(SPVM* spvm, SPVM_ARRAY* array, int32_t index);
void SPVM_ARRAY_store(SPVM* spvm, SPVM_ARRAY* array, int32_t index, void* value);
void* SPVM_ARRAY_pop(SPVM* spvm, SPVM_ARRAY* array);

#endif
