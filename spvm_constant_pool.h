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
SPVM_CONSTANT_POOL* SPVM_CONSTANT_POOL_new(SPVM_COMPILER* compiler);
void SPVM_CONSTANT_POOL_extend(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, int32_t extend);

int32_t SPVM_CONSTANT_POOL_push_int(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, int32_t value);
int32_t SPVM_CONSTANT_POOL_push_long(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, int64_t value);
int32_t SPVM_CONSTANT_POOL_push_float(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, float value);
int32_t SPVM_CONSTANT_POOL_push_double(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, double value);

int32_t SPVM_CONSTANT_POOL_push_string(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, const char* string);
int32_t SPVM_CONSTANT_POOL_push_sub(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, SPVM_SUB* sub);
int32_t SPVM_CONSTANT_POOL_push_package(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, SPVM_PACKAGE* package);
int32_t SPVM_CONSTANT_POOL_push_field(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, SPVM_FIELD* field);
int32_t SPVM_CONSTANT_POOL_push_type(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, SPVM_TYPE* type);
void SPVM_CONSTANT_POOL_adjust_alignment(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, int32_t byte_size);

void SPVM_CONSTANT_POOL_free(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool);

#endif
