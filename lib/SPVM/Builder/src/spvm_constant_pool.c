#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "spvm_constant_pool.h"
#include "spvm_util_allocator.h"
#include "spvm_list.h"
#include "spvm_op.h"
#include "spvm_hash.h"
#include "spvm_native.h"

SPVM_CONSTANT_POOL* SPVM_CONSTANT_POOL_new(int32_t capacity) {
  
  SPVM_CONSTANT_POOL* constant_pool = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_CONSTANT_POOL));
  
  if (capacity == 0) {
    constant_pool->capacity = 64;
  }
  
  // index 0 is not used.
  constant_pool->length = 1;
  
  int64_t values_byte_size = (int64_t)constant_pool->capacity * (int64_t)sizeof(int32_t);
  int32_t* values = SPVM_UTIL_ALLOCATOR_safe_malloc(values_byte_size);
  constant_pool->values = values;
  
  return constant_pool;
}

void SPVM_CONSTANT_POOL_extend(SPVM_CONSTANT_POOL* constant_pool, int32_t extend) {
  
  int32_t capacity = constant_pool->capacity;
  
  if (constant_pool->length + extend >= capacity) {
    int32_t new_capacity = capacity * 2;
    
    int64_t new_values_byte_size = (int64_t)new_capacity * (int64_t)sizeof(int32_t);
    int32_t* new_values = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(new_values_byte_size);
    memcpy(new_values, constant_pool->values, capacity * sizeof(int32_t));
    free(constant_pool->values);
    constant_pool->values = new_values;
    
    constant_pool->capacity = new_capacity;
  }
}

int32_t SPVM_CONSTANT_POOL_push_int(SPVM_CONSTANT_POOL* constant_pool, int32_t value) {
  
  int32_t id = constant_pool->length;

  // Add int value
  SPVM_CONSTANT_POOL_extend(constant_pool, 1);
  constant_pool->values[constant_pool->length] = value;
  constant_pool->length += 1;
  
  return id;
}

int32_t SPVM_CONSTANT_POOL_push_long(SPVM_CONSTANT_POOL* constant_pool, int64_t value) {
  
  int32_t id = constant_pool->length;

  SPVM_CONSTANT_POOL_push_int(constant_pool, (int32_t)(uint32_t)(((uint64_t)value >> 32) & 0xFFFFFFFF));
  SPVM_CONSTANT_POOL_push_int(constant_pool, (int32_t)(uint32_t)((uint64_t)value & 0xFFFFFFFF));
  
  return id;
}

int32_t SPVM_CONSTANT_POOL_push_double(SPVM_CONSTANT_POOL* constant_pool, double value) {

  int32_t id = constant_pool->length;
  
  SPVM_VALUE union_value;
  union_value.dval = value;
  int64_t long_value = union_value.lval;

  SPVM_CONSTANT_POOL_push_int(constant_pool, (int32_t)(uint32_t)(((uint64_t)long_value >> 32) & 0xFFFFFFFF));
  SPVM_CONSTANT_POOL_push_int(constant_pool, (int32_t)(uint32_t)((uint64_t)long_value & 0xFFFFFFFF));

  return id;
}

void SPVM_CONSTANT_POOL_free(SPVM_CONSTANT_POOL* constant_pool) {
  
  free(constant_pool->values);
  free(constant_pool);
}
