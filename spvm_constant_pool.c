#include <string.h>
#include <stdlib.h>
#include <assert.h>


#include "spvm_constant_pool.h"
#include "spvm_constant.h"
#include "spvm_package.h"
#include "spvm_field.h"
#include "spvm_sub.h"
#include "spvm_util_allocator.h"
#include "spvm_dynamic_array.h"
#include "spvm_op.h"
#include "spvm_constant_pool_sub.h"
#include "spvm_constant_pool_field.h"
#include "spvm_constant_pool_package.h"
#include "spvm_type.h"

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

int32_t SPVM_CONSTANT_POOL_push_package(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, SPVM_PACKAGE* package) {
  (void)compiler;
  
  int32_t start_index = constant_pool->length;
  
  // Extend
  int32_t extend_length = SPVM_CONSTANT_POOL_calculate_extend_length(compiler, constant_pool, sizeof(SPVM_CONSTANT_POOL_PACKAGE));
  SPVM_CONSTANT_POOL_extend(compiler, constant_pool, extend_length);

  // Constant pool package information
  SPVM_CONSTANT_POOL_PACKAGE constant_pool_package;
  constant_pool_package.fields_length = package->op_fields->length;
  constant_pool_package.object_fields_length = SPVM_PACKAGE_get_object_fields_length(compiler, package);
  
  // Add length
  constant_pool->length += extend_length;
  
  // Push package name to constant pool
  const char* package_name = package->op_name->uv.name;
  constant_pool_package.name_constant_pool_index = SPVM_CONSTANT_POOL_push_string(compiler, constant_pool, package_name);

  // Push fields constant_pool indexes to constant pool
  {
    int32_t field_pos;
    constant_pool_package.field_indexes_constant_pool_index = constant_pool->length;
    for (field_pos = 0; field_pos < package->op_fields->length; field_pos++) {
      SPVM_OP* op_field = SPVM_DYNAMIC_ARRAY_fetch(package->op_fields, field_pos);
      SPVM_FIELD* field = op_field->uv.field;
      SPVM_CONSTANT_POOL_push_int(compiler, constant_pool, field->constant_pool_index);
    }
  }
  
  memcpy(&constant_pool->values[start_index], &constant_pool_package, sizeof(SPVM_CONSTANT_POOL_PACKAGE));
  
  return start_index;
}

int32_t SPVM_CONSTANT_POOL_push_sub(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, SPVM_SUB* sub) {
  (void)compiler;
  
  int32_t start_index = constant_pool->length;
  
  // Extend
  int32_t extend_length = SPVM_CONSTANT_POOL_calculate_extend_length(compiler, constant_pool, sizeof(SPVM_CONSTANT_POOL_SUB));
  SPVM_CONSTANT_POOL_extend(compiler, constant_pool, extend_length);
  
  // Set subroutine information
  SPVM_CONSTANT_POOL_SUB constant_pool_sub;
  constant_pool_sub.native_address = sub->native_address;
  constant_pool_sub.bytecode_base = sub->bytecode_base;
  constant_pool_sub.my_vars_length = sub->op_my_vars->length;
  constant_pool_sub.operand_stack_max = sub->operand_stack_max;
  constant_pool_sub.args_length = sub->op_args->length;
  constant_pool_sub.is_native = sub->is_native;
  if (sub->op_return_type->code == SPVM_OP_C_CODE_VOID) {
    constant_pool_sub.return_type_id = -1;
  }
  else {
    constant_pool_sub.return_type_id = sub->op_return_type->uv.type->id;
  }

  // Add length
  constant_pool->length += extend_length;
  
  // Object args length
  int32_t object_args_length = 0;
  constant_pool_sub.object_arg_indexes_constant_pool_index = constant_pool->length;
  {
    int32_t i;
    for (i = 0; i < sub->op_args->length; i++) {
      SPVM_OP* op_arg = SPVM_DYNAMIC_ARRAY_fetch(sub->op_args, i);
      SPVM_TYPE* arg_type = SPVM_OP_get_type(compiler, op_arg);
      assert(arg_type);
      if (!SPVM_TYPE_is_numeric(compiler, arg_type)) {
        SPVM_CONSTANT_POOL_push_int(compiler, constant_pool, i);
        object_args_length++;
      }
    }
    constant_pool_sub.object_args_length = object_args_length;
  }
  if (object_args_length == 0) {
    constant_pool_sub.object_arg_indexes_constant_pool_index = -1;
  }

  // Object my_vars length
  int32_t object_my_vars_length = 0;
  constant_pool_sub.object_my_var_indexes_constant_pool_index = constant_pool->length;
  {
    int32_t i;
    for (i = 0; i < sub->op_my_vars->length; i++) {
      SPVM_OP* op_my_var = SPVM_DYNAMIC_ARRAY_fetch(sub->op_my_vars, i);
      SPVM_TYPE* my_var_type = SPVM_OP_get_type(compiler, op_my_var);
      assert(my_var_type);
      if (!SPVM_TYPE_is_numeric(compiler, my_var_type)) {
        SPVM_CONSTANT_POOL_push_int(compiler, constant_pool, i);
        object_my_vars_length++;
      }
    }
    constant_pool_sub.object_my_vars_length = object_my_vars_length;
  }
  
  if (object_my_vars_length == 0) {
    constant_pool_sub.object_my_var_indexes_constant_pool_index = -1;
  }

  // Push sub name to constant pool
  constant_pool_sub.abs_name_constant_pool_index = SPVM_CONSTANT_POOL_push_string(compiler, constant_pool, sub->abs_name);
  
  // Push file name to constant pool
  constant_pool_sub.file_name_constant_pool_index = SPVM_CONSTANT_POOL_push_string(compiler, constant_pool, sub->file_name);
  
  memcpy(&constant_pool->values[start_index], &constant_pool_sub, sizeof(SPVM_CONSTANT_POOL_SUB));
  
  return start_index;
}

int32_t SPVM_CONSTANT_POOL_push_field(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, SPVM_FIELD* field) {
  (void)compiler;

  int32_t start_index = constant_pool->length;

  // Extend
  int32_t extend_length = SPVM_CONSTANT_POOL_calculate_extend_length(compiler, constant_pool, sizeof(SPVM_CONSTANT_POOL_FIELD));
  SPVM_CONSTANT_POOL_extend(compiler, constant_pool, extend_length);
  
  // Constant pool field information
  SPVM_CONSTANT_POOL_FIELD constant_pool_field;
  constant_pool_field.index = field->index;
  
  // Add length
  constant_pool->length += extend_length;
  
  // Add field abs name to constant pool
  constant_pool_field.abs_name_constant_pool_index = SPVM_CONSTANT_POOL_push_string(compiler, constant_pool, field->abs_name);
  
  // Add field name to constant pool
  constant_pool_field.name_constant_pool_index = SPVM_CONSTANT_POOL_push_string(compiler, constant_pool, field->op_name->uv.name);
  
  memcpy(&constant_pool->values[start_index], &constant_pool_field, sizeof(SPVM_CONSTANT_POOL_FIELD));
  
  return start_index;
}

int32_t SPVM_CONSTANT_POOL_push_int(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, int32_t value) {
  (void)compiler;

  int32_t start_index = constant_pool->length;

  // Add int value
  int32_t extend_length = SPVM_CONSTANT_POOL_calculate_extend_length(compiler, constant_pool, sizeof(int32_t));
  SPVM_CONSTANT_POOL_extend(compiler, constant_pool, extend_length);
  memcpy(&constant_pool->values[constant_pool->length], &value, sizeof(int32_t));
  constant_pool->length += extend_length;
  
  return start_index;
}

int32_t SPVM_CONSTANT_POOL_push_long(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, int64_t value) {
  (void)compiler;

  int32_t start_index = constant_pool->length;

  // Add long value
  int32_t extend_length = SPVM_CONSTANT_POOL_calculate_extend_length(compiler, constant_pool, sizeof(int64_t));
  SPVM_CONSTANT_POOL_extend(compiler, constant_pool, extend_length);
  memcpy(&constant_pool->values[constant_pool->length], &value, sizeof(int64_t));
  
  constant_pool->length += extend_length;
  
  return start_index;
}

int32_t SPVM_CONSTANT_POOL_push_float(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, float value) {
  (void)compiler;
  
  int32_t start_index = constant_pool->length;

  // Add float value
  int32_t extend_length = SPVM_CONSTANT_POOL_calculate_extend_length(compiler, constant_pool, sizeof(float));
  SPVM_CONSTANT_POOL_extend(compiler, constant_pool, extend_length);
  memcpy(&constant_pool->values[constant_pool->length], &value, sizeof(float));
  constant_pool->length += extend_length;
  
  return start_index;
}

int32_t SPVM_CONSTANT_POOL_push_double(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, double value) {
  (void)compiler;

  int32_t start_index = constant_pool->length;

  // Add double value
  int32_t extend_length = SPVM_CONSTANT_POOL_calculate_extend_length(compiler, constant_pool, sizeof(double));
  SPVM_CONSTANT_POOL_extend(compiler, constant_pool, extend_length);
  memcpy(&constant_pool->values[constant_pool->length], &value, sizeof(double));
  constant_pool->length += extend_length;
  
  return start_index;
}

int32_t SPVM_CONSTANT_POOL_push_string(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool, const char* string) {

  int32_t start_index = constant_pool->length;

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
  
  return start_index;
}

void SPVM_CONSTANT_POOL_free(SPVM_COMPILER* compiler, SPVM_CONSTANT_POOL* constant_pool) {
  (void)compiler;
  
  free(constant_pool->values);
  free(constant_pool);
}
