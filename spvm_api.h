#ifndef SPVM_API_H
#define SPVM_API_H

#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "spvm_value.h"
#include "spvm_data.h"
#include "spvm_data_array.h"
#include "spvm_data_object.h"
#include "spvm_base.h"

struct SPVM_constant_pool_package;
typedef struct SPVM_constant_pool_package SPVM_CONSTANT_POOL_PACKAGE;

struct SPVM_constant_pool_field;
typedef struct SPVM_constant_pool_field SPVM_CONSTANT_POOL_FIELD;

struct SPVM_constant_pool_sub;
typedef struct SPVM_constant_pool_sub SPVM_CONSTANT_POOL_SUB;

struct SPVM_env;
typedef struct SPVM_env SPVM_ENV;

enum {
  SPVM_DATA_C_TYPE_OBJECT = 0,
  SPVM_DATA_C_TYPE_ARRAY = 1,
};

// SPVM_ENV
struct SPVM_env {
  int32_t* constant_pool;
};

// SPVM_CONSTANT_POOL_PACKAGE
struct SPVM_constant_pool_package {
  int32_t name_constant_pool_index;
  int32_t fields_length;
  int32_t ref_fields_length;
  int32_t field_name_indexes_constant_pool_index;
};

// SPVM_CONSTANT_POOL_FIELD
struct SPVM_constant_pool_field {
  int32_t abs_name_constant_pool_index;
  int32_t name_constant_pool_index;
  int32_t index;
};

// SPVM_CONSTANT_POOL_SUB
struct SPVM_constant_pool_sub {
  void* native_address;
  int32_t bytecode_base;
  int32_t file_name_constant_pool_index;
  int32_t abs_name_constant_pool_index;
  int32_t operand_stack_max;
  int32_t my_vars_length;
  int32_t args_length;
  _Bool is_native;
  _Bool has_return_value;
};

static inline int32_t SPVM_API_get_array_value_size(SPVM_ENV* env, int32_t type) {
  (void)env;
  
  static const int32_t array_value_sizes[] = {
    sizeof(int8_t),
    sizeof(int16_t),
    sizeof(int32_t),
    sizeof(int64_t),
    sizeof(float),
    sizeof(double),
    sizeof(void*),
  };
  
  return array_value_sizes[type];
}

static inline SPVM_VALUE* SPVM_API_get_object_fields(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object) {
  (void)env;
  
  return (SPVM_VALUE*)((intptr_t)data_object + SPVM_DATA_C_HEADER_BYTE_SIZE);
}

static inline int32_t SPVM_API_get_object_field_index(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name) {
  (void)env;
  
  int32_t field_name_indexes_constant_pool_index = data_object->field_name_indexes_constant_pool_index;
  int32_t* constant_pool = env->constant_pool;
  int32_t length = constant_pool[field_name_indexes_constant_pool_index];
  
  int32_t field_index = -1;
  _Bool found = 0;
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      int32_t name_index = constant_pool[field_name_indexes_constant_pool_index + i + 1];
      char* match_name = (char*)&constant_pool[name_index + 1];
      if (strcmp(name, match_name) == 0) {
        found = 1;
        field_index = i;
      }
    }
  }
  
  if (!found) {
    fprintf(stderr, "Can't find filed name \"%s\"\n", name);
    abort();
  }
  
  return field_index;
}

static inline int32_t SPVM_API_get_object_fields_length(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object) {
  (void)env;
  
  int32_t field_name_indexes_constant_pool_index = data_object->field_name_indexes_constant_pool_index;
  
  int32_t* constant_pool = env->constant_pool;
  
  int32_t length = constant_pool[field_name_indexes_constant_pool_index];
  
  return length;
}

static inline void SPVM_API_set_object_field_value_byte(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name, int8_t value) {
  (void)env;
  
  SPVM_VALUE* fields = SPVM_API_get_object_fields(env, data_object);
  int32_t field_index = SPVM_API_get_object_field_index(env, data_object, name);
  fields[field_index].byte_value = value;
}

static inline void SPVM_API_set_object_field_value_short(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name, int16_t value) {
  
  SPVM_VALUE* fields = SPVM_API_get_object_fields(env, data_object);
  int32_t field_index = SPVM_API_get_object_field_index(env, data_object, name);
  fields[field_index].short_value = value;
}

static inline void SPVM_API_set_object_field_value_int(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name, int32_t value) {
  (void)env;
  
  SPVM_VALUE* fields = SPVM_API_get_object_fields(env, data_object);
  int32_t field_index = SPVM_API_get_object_field_index(env, data_object, name);
  fields[field_index].int_value = value;
}

static inline void SPVM_API_set_object_field_value_long(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name, int64_t value) {
  
  SPVM_VALUE* fields = SPVM_API_get_object_fields(env, data_object);
  int32_t field_index = SPVM_API_get_object_field_index(env, data_object, name);
  fields[field_index].long_value = value;
}

static inline void SPVM_API_set_object_field_value_float(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name, float value) {
  (void)env;
  
  SPVM_VALUE* fields = SPVM_API_get_object_fields(env, data_object);
  int32_t field_index = SPVM_API_get_object_field_index(env, data_object, name);
  fields[field_index].float_value = value;
}

static inline void SPVM_API_set_object_field_value_double(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name, double value) {
  (void)env;
  
  SPVM_VALUE* fields = SPVM_API_get_object_fields(env, data_object);
  int32_t field_index = SPVM_API_get_object_field_index(env, data_object, name);
  fields[field_index].double_value = value;
}

static inline int8_t SPVM_API_get_object_field_value_byte(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name) {
  (void)env;
  
  SPVM_VALUE* fields = SPVM_API_get_object_fields(env, data_object);
  int32_t field_index = SPVM_API_get_object_field_index(env, data_object, name);
  int8_t byte_value = fields[field_index].byte_value;
  
  return byte_value;
}

static inline int16_t SPVM_API_get_object_field_value_short(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name) {
  (void)env;
  
  SPVM_VALUE* fields = SPVM_API_get_object_fields(env, data_object);
  int32_t field_index = SPVM_API_get_object_field_index(env, data_object, name);
  int16_t short_value = fields[field_index].short_value;
  
  return short_value;
}

static inline int32_t SPVM_API_get_object_field_value_int(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name) {
  (void)env;
  
  SPVM_VALUE* fields = SPVM_API_get_object_fields(env, data_object);
  int32_t field_index = SPVM_API_get_object_field_index(env, data_object, name);
  int32_t int_value = fields[field_index].int_value;
  
  return int_value;
}

static inline int64_t SPVM_API_get_object_field_value_long(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name) {
  (void)env;
  
  SPVM_VALUE* fields = SPVM_API_get_object_fields(env, data_object);
  int32_t field_index = SPVM_API_get_object_field_index(env, data_object, name);
  int64_t long_value = fields[field_index].long_value;
  
  return long_value;
}

static inline float SPVM_API_get_object_field_value_float(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name) {
  
  SPVM_VALUE* fields = SPVM_API_get_object_fields(env, data_object);
  int32_t field_index = SPVM_API_get_object_field_index(env, data_object, name);
  float float_value = fields[field_index].float_value;
  
  return float_value;
}

static inline double SPVM_API_get_object_field_value_double(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name) {
  (void)env;
  
  SPVM_VALUE* fields = SPVM_API_get_object_fields(env, data_object);
  int32_t field_index = SPVM_API_get_object_field_index(env, data_object, name);
  double double_value = fields[field_index].double_value;
  
  return double_value;
}

static inline SPVM_DATA* SPVM_API_get_object_field_value_ref(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name) {
  (void)env;
  
  SPVM_VALUE* fields = SPVM_API_get_object_fields(env, data_object);
  int32_t field_index = SPVM_API_get_object_field_index(env, data_object, name);
  SPVM_DATA* address_value = fields[field_index].address_value;
  
  return address_value;
}

static inline int32_t SPVM_API_dump_object_field_names(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object) {
  (void)env;
  
  int32_t field_name_indexes_constant_pool_index = data_object->field_name_indexes_constant_pool_index;
  
  int32_t* constant_pool = env->constant_pool;
  
  int32_t length = constant_pool[field_name_indexes_constant_pool_index];
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      int32_t name_index = constant_pool[field_name_indexes_constant_pool_index + i + 1];
      char* name = (char*)&constant_pool[name_index + 1];
      fprintf(stderr, "%s\n", name);
    }
  }
  
  return length;
}

static inline int32_t* SPVM_API_get_constant_pool(SPVM_ENV* env) {
  (void)env;
  
  return env->constant_pool;
}

static inline int32_t SPVM_API_get_ref_count(SPVM_ENV* env, SPVM_DATA* data) {
  (void)env;
  
  return data->ref_count;
}

static inline int32_t SPVM_API_get_array_length(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array) {
  (void)env;
  
  return data_array->length;
}

static inline int8_t* SPVM_API_get_array_values_byte(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array) {
  (void)env;

  return (int8_t*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE);
}

static inline int16_t* SPVM_API_get_array_values_short(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array) {
  (void)env;
  
  return (int16_t*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE);
}

static inline int32_t* SPVM_API_get_array_values_int(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array) {
  (void)env;
  
  return (int32_t*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE);
}

static inline int64_t* SPVM_API_get_array_values_long(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array) {
  (void)env;
  
  return (int64_t*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE);
}

static inline float* SPVM_API_get_array_values_float(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array) {
  (void)env;
  
  return (float*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE);
}

static inline double* SPVM_API_get_array_values_double(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array) {
  (void)env;
  
  return (double*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE);
}

static inline SPVM_DATA** SPVM_API_get_array_values_ref(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array) {
  (void)env;
  
  return (SPVM_DATA**)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE);
}

#endif
