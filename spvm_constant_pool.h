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
SPVM_CONSTANT_POOL* SPVM_CONSTANT_POOL_new(SPVM* spvm);
void SPVM_CONSTANT_POOL_extend(SPVM* spvm, SPVM_CONSTANT_POOL* constant_pool, int32_t extend);

void SPVM_CONSTANT_POOL_push_int(SPVM* spvm, SPVM_CONSTANT_POOL* constant_pool, int32_t value);
void SPVM_CONSTANT_POOL_push_long(SPVM* spvm, SPVM_CONSTANT_POOL* constant_pool, int64_t value);
void SPVM_CONSTANT_POOL_push_float(SPVM* spvm, SPVM_CONSTANT_POOL* constant_pool, float value);
void SPVM_CONSTANT_POOL_push_double(SPVM* spvm, SPVM_CONSTANT_POOL* constant_pool, double value);

void SPVM_CONSTANT_POOL_push_string(SPVM* spvm, SPVM_CONSTANT_POOL* constant_pool, const char* string);

void SPVM_CONSTANT_POOL_push_sub(SPVM* spvm, SPVM_CONSTANT_POOL* constant_pool, SPVM_SUB* sub);
void SPVM_CONSTANT_POOL_push_package(SPVM* spvm, SPVM_CONSTANT_POOL* constant_pool, SPVM_PACKAGE* package);
void SPVM_CONSTANT_POOL_push_field(SPVM* spvm, SPVM_CONSTANT_POOL* constant_pool, SPVM_FIELD* field);
void SPVM_CONSTANT_POOL_free(SPVM* spvm, SPVM_CONSTANT_POOL* constant_pool);

#endif
