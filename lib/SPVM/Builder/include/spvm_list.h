#ifndef SPVM_LIST_H
#define SPVM_LIST_H

#include <stdint.h>
#include <stddef.h>

struct spvm_list;
typedef struct spvm_list SPVM_LIST;

struct spvm_list {
  void** values;
  int32_t length;
  int32_t capacity;
};

SPVM_LIST* SPVM_LIST_new(int32_t capacity);
void SPVM_LIST_free(SPVM_LIST* array);
void SPVM_LIST_maybe_extend(SPVM_LIST* array);

void SPVM_LIST_push(SPVM_LIST* array, void* value);
void* SPVM_LIST_fetch(SPVM_LIST* array, int32_t index);
void SPVM_LIST_store(SPVM_LIST* array, int32_t index, void* value);
void* SPVM_LIST_pop(SPVM_LIST* array);
void* SPVM_LIST_shift(SPVM_LIST* array);

#endif
