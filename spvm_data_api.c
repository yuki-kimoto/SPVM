#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "spvm_data_api.h"

const int32_t SPVM_DATA_ARRAY_C_VALUE_SIZES[] = {
  sizeof(int8_t),
  sizeof(int16_t),
  sizeof(int32_t),
  sizeof(int64_t),
  sizeof(float),
  sizeof(double),
  sizeof(void*),
};

inline void SPVM_DATA_API_set_object_field_value_byte(SPVM_DATA_OBJECT* data_object, const char* name, int8_t value) {
  
  SPVM_VALUE* fields = SPVM_DATA_API_get_object_fields(data_object);
  int32_t field_index = SPVM_DATA_API_get_object_field_index(data_object, name);
  fields[field_index].byte_value = value;
}

inline void SPVM_DATA_API_set_object_field_value_short(SPVM_DATA_OBJECT* data_object, const char* name, int16_t value) {
  
  SPVM_VALUE* fields = SPVM_DATA_API_get_object_fields(data_object);
  int32_t field_index = SPVM_DATA_API_get_object_field_index(data_object, name);
  fields[field_index].short_value = value;
}

inline void SPVM_DATA_API_set_object_field_value_int(SPVM_DATA_OBJECT* data_object, const char* name, int32_t value) {
  
  SPVM_VALUE* fields = SPVM_DATA_API_get_object_fields(data_object);
  int32_t field_index = SPVM_DATA_API_get_object_field_index(data_object, name);
  fields[field_index].int_value = value;
}

inline void SPVM_DATA_API_set_object_field_value_long(SPVM_DATA_OBJECT* data_object, const char* name, int64_t value) {
  
  SPVM_VALUE* fields = SPVM_DATA_API_get_object_fields(data_object);
  int32_t field_index = SPVM_DATA_API_get_object_field_index(data_object, name);
  fields[field_index].long_value = value;
}

inline void SPVM_DATA_API_set_object_field_value_float(SPVM_DATA_OBJECT* data_object, const char* name, float value) {
  
  SPVM_VALUE* fields = SPVM_DATA_API_get_object_fields(data_object);
  int32_t field_index = SPVM_DATA_API_get_object_field_index(data_object, name);
  fields[field_index].float_value = value;
}

inline void SPVM_DATA_API_set_object_field_value_double(SPVM_DATA_OBJECT* data_object, const char* name, double value) {
  
  SPVM_VALUE* fields = SPVM_DATA_API_get_object_fields(data_object);
  int32_t field_index = SPVM_DATA_API_get_object_field_index(data_object, name);
  fields[field_index].double_value = value;
}

inline int8_t SPVM_DATA_API_get_object_field_value_byte(SPVM_DATA_OBJECT* data_object, const char* name) {
  
  SPVM_VALUE* fields = SPVM_DATA_API_get_object_fields(data_object);
  int32_t field_index = SPVM_DATA_API_get_object_field_index(data_object, name);
  int8_t byte_value = fields[field_index].byte_value;
  
  return byte_value;
}

inline int16_t SPVM_DATA_API_get_object_field_value_short(SPVM_DATA_OBJECT* data_object, const char* name) {
  
  SPVM_VALUE* fields = SPVM_DATA_API_get_object_fields(data_object);
  int32_t field_index = SPVM_DATA_API_get_object_field_index(data_object, name);
  int16_t short_value = fields[field_index].short_value;
  
  return short_value;
}

inline int32_t SPVM_DATA_API_get_object_field_value_int(SPVM_DATA_OBJECT* data_object, const char* name) {
  
  SPVM_VALUE* fields = SPVM_DATA_API_get_object_fields(data_object);
  int32_t field_index = SPVM_DATA_API_get_object_field_index(data_object, name);
  int32_t int_value = fields[field_index].int_value;
  
  return int_value;
}

inline int64_t SPVM_DATA_API_get_object_field_value_long(SPVM_DATA_OBJECT* data_object, const char* name) {
  
  SPVM_VALUE* fields = SPVM_DATA_API_get_object_fields(data_object);
  int32_t field_index = SPVM_DATA_API_get_object_field_index(data_object, name);
  int64_t long_value = fields[field_index].long_value;
  
  return long_value;
}

inline float SPVM_DATA_API_get_object_field_value_float(SPVM_DATA_OBJECT* data_object, const char* name) {
  
  SPVM_VALUE* fields = SPVM_DATA_API_get_object_fields(data_object);
  int32_t field_index = SPVM_DATA_API_get_object_field_index(data_object, name);
  float float_value = fields[field_index].float_value;
  
  return float_value;
}

inline double SPVM_DATA_API_get_object_field_value_double(SPVM_DATA_OBJECT* data_object, const char* name) {
  
  SPVM_VALUE* fields = SPVM_DATA_API_get_object_fields(data_object);
  int32_t field_index = SPVM_DATA_API_get_object_field_index(data_object, name);
  double double_value = fields[field_index].double_value;
  
  return double_value;
}

inline SPVM_DATA* SPVM_DATA_API_get_object_field_value_ref(SPVM_DATA_OBJECT* data_object, const char* name) {
  
  SPVM_VALUE* fields = SPVM_DATA_API_get_object_fields(data_object);
  int32_t field_index = SPVM_DATA_API_get_object_field_index(data_object, name);
  SPVM_DATA* address_value = fields[field_index].address_value;
  
  return address_value;
}

inline SPVM_VALUE* SPVM_DATA_API_get_object_fields(SPVM_DATA_OBJECT* data_object) {
  return (SPVM_VALUE*)((intptr_t)data_object + SPVM_DATA_C_HEADER_BYTE_SIZE);
}

inline int32_t SPVM_DATA_API_get_object_field_index(SPVM_DATA_OBJECT* data_object, const char* name) {
  
  int32_t field_name_indexes_constant_pool_address = data_object->field_name_indexes_constant_pool_address;
  int32_t* constant_pool = data_object->constant_pool;
  int32_t length = constant_pool[field_name_indexes_constant_pool_address];
  
  int32_t field_index;
  _Bool found = 0;
  for (int32_t i = 0; i < length; i++) {
    int32_t name_index = constant_pool[field_name_indexes_constant_pool_address + i + 1];
    char* match_name = (char*)&constant_pool[name_index + 1];
    if (strcmp(name, match_name) == 0) {
      found = 1;
      field_index = i;
    }
  }
  
  if (!found) {
    fprintf(stderr, "Can't find filed name \"%s\"\n", name);
    abort();
  }
  
  return field_index;
}

inline int32_t SPVM_DATA_API_dump_object_field_names(SPVM_DATA_OBJECT* data_object) {
  
  int32_t field_name_indexes_constant_pool_address = data_object->field_name_indexes_constant_pool_address;
  
  int32_t* constant_pool = data_object->constant_pool;
  
  int32_t length = constant_pool[field_name_indexes_constant_pool_address];
  
  for (int32_t i = 0; i < length; i++) {
    int32_t name_index = constant_pool[field_name_indexes_constant_pool_address + i + 1];
    char* name = (char*)&constant_pool[name_index + 1];
    fprintf(stderr, "%s\n", name);
  }
  
  return length;
}

inline int32_t SPVM_DATA_API_get_object_fields_length(SPVM_DATA_OBJECT* data_object) {
  
  int32_t field_name_indexes_constant_pool_address = data_object->field_name_indexes_constant_pool_address;
  
  int32_t* constant_pool = data_object->constant_pool;
  
  int32_t length = constant_pool[field_name_indexes_constant_pool_address];
  
  return length;
}

inline int32_t* SPVM_DATA_API_get_constant_pool(SPVM_DATA* data) {
  
  return data->constant_pool;
}

inline int32_t SPVM_DATA_API_get_ref_count(SPVM_DATA* data) {
  
  return data->ref_count;
}

inline int32_t SPVM_DATA_API_get_array_length(SPVM_DATA_ARRAY* data_array) {
  
  return data_array->length;
}

inline int8_t* SPVM_DATA_API_get_array_values_byte(SPVM_DATA_ARRAY* data_array) {

  return (int8_t*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE);
}

inline int16_t* SPVM_DATA_API_get_array_values_short(SPVM_DATA_ARRAY* data_array) {
  
  return (int16_t*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE);
}

inline int32_t* SPVM_DATA_API_get_array_values_int(SPVM_DATA_ARRAY* data_array) {
  
  return (int32_t*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE);
}

inline int64_t* SPVM_DATA_API_get_array_values_long(SPVM_DATA_ARRAY* data_array) {
  
  return (int64_t*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE);
}

inline float* SPVM_DATA_API_get_array_values_float(SPVM_DATA_ARRAY* data_array) {
  
  return (float*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE);
}

inline double* SPVM_DATA_API_get_array_values_double(SPVM_DATA_ARRAY* data_array) {
  
  return (double*)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE);
}

inline SPVM_DATA** SPVM_DATA_API_get_array_values_ref(SPVM_DATA_ARRAY* data_array) {
  
  return (SPVM_DATA**)((intptr_t)data_array + SPVM_DATA_C_HEADER_BYTE_SIZE);
}
