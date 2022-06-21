#ifndef SPVM_LIST_H
#define SPVM_LIST_H

#include "spvm_typedecl.h"

struct spvm_list {
  SPVM_ALLOCATOR* allocator;
  void** values;
  int32_t length;
  int32_t capacity;
  int8_t memory_block_type;
};

SPVM_LIST* SPVM_LIST_new(SPVM_ALLOCATOR* allocator, int32_t capacity, int32_t memory_block_type);
SPVM_LIST* SPVM_LIST_new_list_permanent(SPVM_ALLOCATOR* allocator, int32_t capacity);
void SPVM_LIST_free(SPVM_LIST* array);
void SPVM_LIST_maybe_extend(SPVM_LIST* array);
void SPVM_LIST_push(SPVM_LIST* array, void* value);
void* SPVM_LIST_get(SPVM_LIST* array, int32_t index);
void SPVM_LIST_set(SPVM_LIST* array, int32_t index, void* value);
void* SPVM_LIST_pop(SPVM_LIST* array);
void* SPVM_LIST_shift(SPVM_LIST* array);
void SPVM_LIST_unshift(SPVM_LIST* list, void* value);

#endif
