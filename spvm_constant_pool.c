#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "spvm_constant_pool.h"
#include "spvm_util_allocator.h"
#include "spvm_list.h"
#include "spvm_op.h"
#include "spvm_hash.h"
#include "spvm_compiler.h"
#include "spvm_limit.h"

SPVM_CONSTANT_POOL* SPVM_CONSTANT_POOL_new(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_CONSTANT_POOL* constant_pool = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_CONSTANT_POOL));
  
  constant_pool->capacity = 1024;
  
  // index 0 is not used.
  constant_pool->length = 1;
  
  char* values = SPVM_UTIL_ALLOCATOR_safe_malloc(constant_pool->capacity);
  constant_pool->values = values;
  
  return constant_pool;
}

void SPVM_CONSTANT_POOL_extend(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, int32_t extend) {
  (void)compiler;
  
  int32_t capacity = constant_pool->capacity;
  
  if (constant_pool->length + extend >= capacity) {
    int32_t new_capacity = capacity * 2;
    
    char* new_values = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(new_capacity);
    memcpy(new_values, constant_pool->values, capacity);
    free(constant_pool->values);
    constant_pool->values = new_values;
    
    constant_pool->capacity = new_capacity;
  }
}

int32_t SPVM_CONSTANT_POOL_push_basic_type_name(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, const char* basic_type_name) {
  
  int32_t id = (int32_t)(intptr_t)SPVM_HASH_search(compiler->basic_type_name_symtable, basic_type_name, strlen(basic_type_name));
  
  if (id > 0) {
    return id;
  }
  else {
    // Add @@@...@@@int, @ count is 255
    int32_t dimension_max = SPVM_LIMIT_DIMENSION;
    
    int32_t id = constant_pool->length + dimension_max;
    
    // Add basic_type_name base_object
    int32_t basic_type_name_length = strlen(basic_type_name);
    int32_t extend_length = dimension_max + (int32_t)basic_type_name_length + 1;
    SPVM_CONSTANT_POOL_extend(compiler, constant_pool, extend_length);
    memset(&constant_pool->values[constant_pool->length], '@', dimension_max);;
    memcpy(&constant_pool->values[constant_pool->length + dimension_max], basic_type_name, basic_type_name_length);
    constant_pool->values[constant_pool->length + dimension_max + basic_type_name_length] = '\0';
    
    constant_pool->length += extend_length;
    
    SPVM_HASH_insert(compiler->basic_type_name_symtable, basic_type_name, strlen(basic_type_name), (void*)(intptr_t)id);
    
    return id;
  }
}

void SPVM_CONSTANT_POOL_free(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool) {
  (void)compiler;
  
  free(constant_pool->values);
  free(constant_pool);
}
