#include <string.h>
#include <stdlib.h>
#include <assert.h>


#include "spvm_constant_pool.h"
#include "spvm_constant.h"
#include "spvm_package.h"
#include "spvm_field.h"
#include "spvm_sub.h"
#include "spvm_util_allocator.h"
#include "spvm_list.h"
#include "spvm_op.h"
#include "spvm_constant_pool_field.h"
#include "spvm_constant_pool_type.h"
#include "spvm_type.h"
#include "spvm_hash.h"
#include "spvm_compiler.h"

void SPVM_CONSTANT_POOL_adjust_alignment(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, int32_t byte_size) {
  
  assert(byte_size % sizeof(int32_t) == 0);
  int32_t count = byte_size / sizeof(int32_t);
  
  int32_t rem_count = constant_pool->length % count;
  
  if (rem_count == 0) {
    return;
  }
  
  int32_t rest_count = count - rem_count;
  
  {
    int32_t i;
    for (i = 0; i < rest_count; i++) {
      SPVM_CONSTANT_POOL_push_int(compiler, constant_pool, rest_count);
    }
  }
  
  assert(constant_pool->length % count == 0);
}

SPVM_CONSTANT_POOL* SPVM_CONSTANT_POOL_new(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_CONSTANT_POOL* constant_pool = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_CONSTANT_POOL));
  
  constant_pool->capacity = 64;
  
  // index 0 is not used.
  constant_pool->length = 1;
  
  int64_t values_byte_size = (int64_t)constant_pool->capacity * (int64_t)sizeof(int32_t);
  int32_t* values = SPVM_UTIL_ALLOCATOR_safe_malloc(values_byte_size);
  constant_pool->values = values;
  
  return constant_pool;
}

int32_t SPVM_CONSTANT_POOL_calculate_extend_length(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, int32_t byte_size) {
  (void)compiler;
  (void)constant_pool;
  
  int32_t length = (byte_size + (sizeof(int32_t) - 1)) / sizeof(int32_t);
  
  return length;
}

void SPVM_CONSTANT_POOL_extend(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, int32_t extend) {
  (void)compiler;
  
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

int32_t SPVM_CONSTANT_POOL_push_type(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, SPVM_TYPE* type) {
  (void)compiler;
  
  int32_t id = constant_pool->length;
  
  // Extend
  int32_t extend_length = SPVM_CONSTANT_POOL_calculate_extend_length(compiler, constant_pool, sizeof(SPVM_CONSTANT_POOL_TYPE));
  SPVM_CONSTANT_POOL_extend(compiler, constant_pool, extend_length);
  
  // Constant pool type information
  SPVM_CONSTANT_POOL_TYPE constant_pool_type;
  memset(&constant_pool_type, 0, sizeof(SPVM_CONSTANT_POOL_TYPE));
  
  // Add length
  constant_pool->length += extend_length;
  
  memcpy(&constant_pool->values[id], &constant_pool_type, sizeof(SPVM_CONSTANT_POOL_TYPE));
  
  return id;
}

int32_t SPVM_CONSTANT_POOL_push_package(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, SPVM_PACKAGE* package) {
  (void)compiler;
  
  int32_t id = constant_pool->length;

  // Push object fields constant_pool byte offsets to constant pool
  {
    int32_t field_pos;
    package->object_field_byte_offsets_base = constant_pool->length;
    int32_t object_field_byte_offsets_length = 0;
    for (field_pos = 0; field_pos < package->op_fields->length; field_pos++) {
      SPVM_OP* op_field = SPVM_LIST_fetch(package->op_fields, field_pos);
      SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, op_field);
      
      if (SPVM_TYPE_is_object(compiler, field_type)) {
        SPVM_FIELD* field = op_field->uv.field;
        int32_t byte_offset = field->byte_offset;
        SPVM_CONSTANT_POOL_push_int(compiler, constant_pool, byte_offset);
        object_field_byte_offsets_length++;
      }
    }
    package->object_field_byte_offsets_length = object_field_byte_offsets_length;
  }
  
  return id;
}

int32_t SPVM_CONSTANT_POOL_push_field(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, SPVM_FIELD* field) {
  (void)compiler;

  int32_t id = constant_pool->length;

  // Extend
  int32_t extend_length = SPVM_CONSTANT_POOL_calculate_extend_length(compiler, constant_pool, sizeof(SPVM_CONSTANT_POOL_FIELD));
  SPVM_CONSTANT_POOL_extend(compiler, constant_pool, extend_length);
  
  // Constant pool field information
  // Field id is field index + 1 because 0 mean no id
  SPVM_CONSTANT_POOL_FIELD constant_pool_field;
  memset(&constant_pool_field, 0, sizeof(SPVM_CONSTANT_POOL_FIELD));
  
  // Add length
  constant_pool->length += extend_length;
  
  memcpy(&constant_pool->values[id], &constant_pool_field, sizeof(SPVM_CONSTANT_POOL_FIELD));
  
  return id;
}

int32_t SPVM_CONSTANT_POOL_push_byte(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, int8_t value) {
  (void)compiler;
  
  int32_t id = constant_pool->length;
  
  // Add int value
  int32_t extend_length = SPVM_CONSTANT_POOL_calculate_extend_length(compiler, constant_pool, sizeof(int32_t));
  SPVM_CONSTANT_POOL_extend(compiler, constant_pool, extend_length);
  memcpy(&constant_pool->values[constant_pool->length], &value, sizeof(int8_t));
  constant_pool->length += extend_length;
  
  return id;
}

int32_t SPVM_CONSTANT_POOL_push_short(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, int16_t value) {
  (void)compiler;
  
  int32_t id = constant_pool->length;
  
  // Add int value
  int32_t extend_length = SPVM_CONSTANT_POOL_calculate_extend_length(compiler, constant_pool, sizeof(int32_t));
  SPVM_CONSTANT_POOL_extend(compiler, constant_pool, extend_length);
  memcpy(&constant_pool->values[constant_pool->length], &value, sizeof(int16_t));
  constant_pool->length += extend_length;
  
  return id;
}

int32_t SPVM_CONSTANT_POOL_push_int(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, int32_t value) {
  (void)compiler;

  int32_t id = constant_pool->length;

  // Add int value
  int32_t extend_length = SPVM_CONSTANT_POOL_calculate_extend_length(compiler, constant_pool, sizeof(int32_t));
  SPVM_CONSTANT_POOL_extend(compiler, constant_pool, extend_length);
  memcpy(&constant_pool->values[constant_pool->length], &value, sizeof(int32_t));
  constant_pool->length += extend_length;
  
  return id;
}

int32_t SPVM_CONSTANT_POOL_push_long(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, int64_t value) {
  (void)compiler;
  
  SPVM_CONSTANT_POOL_adjust_alignment(compiler, constant_pool, sizeof(int64_t));
  
  int32_t id = constant_pool->length;

  // Add long value
  int32_t extend_length = SPVM_CONSTANT_POOL_calculate_extend_length(compiler, constant_pool, sizeof(int64_t));
  SPVM_CONSTANT_POOL_extend(compiler, constant_pool, extend_length);
  memcpy(&constant_pool->values[constant_pool->length], &value, sizeof(int64_t));
  
  constant_pool->length += extend_length;
  
  return id;
}

int32_t SPVM_CONSTANT_POOL_push_float(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, float value) {
  (void)compiler;
  
  int32_t id = constant_pool->length;

  // Add float value
  int32_t extend_length = SPVM_CONSTANT_POOL_calculate_extend_length(compiler, constant_pool, sizeof(float));
  SPVM_CONSTANT_POOL_extend(compiler, constant_pool, extend_length);
  memcpy(&constant_pool->values[constant_pool->length], &value, sizeof(float));
  constant_pool->length += extend_length;
  
  return id;
}

int32_t SPVM_CONSTANT_POOL_push_double(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, double value) {
  (void)compiler;

  SPVM_CONSTANT_POOL_adjust_alignment(compiler, constant_pool, sizeof(double));

  int32_t id = constant_pool->length;

  // Add double value
  int32_t extend_length = SPVM_CONSTANT_POOL_calculate_extend_length(compiler, constant_pool, sizeof(double));
  SPVM_CONSTANT_POOL_extend(compiler, constant_pool, extend_length);
  memcpy(&constant_pool->values[constant_pool->length], &value, sizeof(double));
  constant_pool->length += extend_length;
  
  return id;
}

int32_t SPVM_CONSTANT_POOL_push_string(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, const char* string) {
  
  int32_t id = (int32_t)(intptr_t)SPVM_HASH_search(compiler->string_symtable, string, strlen(string));
  
  if (id > 0) {
    return id;
  }
  else {
    int32_t id = constant_pool->length;
    
    // Add string length
    int32_t string_length = (int32_t)strlen(string);
    SPVM_CONSTANT_POOL_extend(compiler, constant_pool, 1);
    memcpy(&constant_pool->values[constant_pool->length], &string_length, sizeof(int32_t));
    constant_pool->length++;
    
    // Add string base_object
    int32_t extend_length = SPVM_CONSTANT_POOL_calculate_extend_length(compiler, constant_pool, string_length + 1);
    SPVM_CONSTANT_POOL_extend(compiler, constant_pool, extend_length);
    memcpy(&constant_pool->values[constant_pool->length], string, string_length + 1);
    
    constant_pool->length += extend_length;
    
    SPVM_HASH_insert(compiler->string_symtable, string, strlen(string), (void*)(intptr_t)id);
    
    return id;
  }
}

void SPVM_CONSTANT_POOL_free(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool) {
  (void)compiler;
  
  free(constant_pool->values);
  free(constant_pool);
}
