#ifndef SPVM_CONSTANT_POOL_H
#define SPVM_CONSTANT_POOL_H

#include "spvm_base.h"

// Array
struct SPVM_constant_pool {
  int32_t* values;
  int32_t length;
  int32_t capacity;
};

// Array function
SPVM_CONSTANT_POOL* SPVM_CONSTANT_POOL_new(int32_t capacity);
void SPVM_CONSTANT_POOL_extend(SPVM_CONSTANT_POOL* constant_pool, int32_t extend);

int32_t SPVM_CONSTANT_POOL_push_int(SPVM_CONSTANT_POOL* constant_pool, int32_t value);
int32_t SPVM_CONSTANT_POOL_push_long(SPVM_CONSTANT_POOL* constant_pool, int64_t value);
int32_t SPVM_CONSTANT_POOL_push_double(SPVM_CONSTANT_POOL* constant_pool, double value);

void SPVM_CONSTANT_POOL_free(SPVM_CONSTANT_POOL* constant_pool);

#endif
