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
SPVM_CONSTANT_POOL* SPVM_CONSTANT_POOL_new(SPVM_* spvm);
void SPVM_CONSTANT_POOL_extend(SPVM_* spvm, SPVM_CONSTANT_POOL* constant_pool, int32_t extend);

void SPVM_CONSTANT_POOL_push_int(SPVM_* spvm, SPVM_CONSTANT_POOL* constant_pool, int32_t value);
void SPVM_CONSTANT_POOL_push_long(SPVM_* spvm, SPVM_CONSTANT_POOL* constant_pool, int64_t value);
void SPVM_CONSTANT_POOL_push_float(SPVM_* spvm, SPVM_CONSTANT_POOL* constant_pool, float value);
void SPVM_CONSTANT_POOL_push_double(SPVM_* spvm, SPVM_CONSTANT_POOL* constant_pool, double value);

void SPVM_CONSTANT_POOL_push_string(SPVM_* spvm, SPVM_CONSTANT_POOL* constant_pool, const char* string);

void SPVM_CONSTANT_POOL_push_sub(SPVM_* spvm, SPVM_CONSTANT_POOL* constant_pool, SPVM_SUB* sub);
void SPVM_CONSTANT_POOL_push_package(SPVM_* spvm, SPVM_CONSTANT_POOL* constant_pool, SPVM_PACKAGE* package);
void SPVM_CONSTANT_POOL_push_field(SPVM_* spvm, SPVM_CONSTANT_POOL* constant_pool, SPVM_FIELD* field);
void SPVM_CONSTANT_POOL_free(SPVM_* spvm, SPVM_CONSTANT_POOL* constant_pool);

#endif
