#ifndef SPVM_ENV_H
#define SPVM_ENV_H

#include <stdint.h>

// spvm_env.h
struct SPVM_env;
typedef struct SPVM_env SPVM_ENV;

struct SPVM_env {
  void* runtime;
  int32_t (*get_array_length)(void*, void*);
  int64_t (*calcurate_data_byte_size)(void*, void*);
  void* (*create_data_array_byte)(void*, int32_t);
  void* (*create_data_array_byte_from_pv)(void*, const char*);
  void (*dec_ref_count)(void*, void*);
  void (*inc_ref_count)(void*, void*);
  void (*push_return_value_byte)(void*, int8_t);
  void (*push_return_value_short)(void*, int16_t);
  void (*push_return_value_int)(void*, int32_t);
  void (*push_return_value_long)(void*, int64_t);
  void (*push_return_value_float)(void*, float);
  void (*push_return_value_double)(void*, double);
  void (*push_ret)(void*, void*);
  int8_t (*pop_return_value_byte)(void*);
  int16_t (*pop_return_value_short)(void*);
  int32_t (*pop_return_value_int)(void*);
  int64_t (*pop_return_value_long)(void*);
  float (*pop_return_value_float)(void*);
  double (*pop_return_value_double)(void*);
  void* (*pop_return_value_address)(void*);
  int8_t (*get_var_byte)(void*, int32_t);
  int16_t (*get_var_short)(void*, int32_t);
  int32_t (*get_var_int)(void*, int32_t);
  int64_t (*get_var_long)(void*, int32_t);
  float (*get_var_float)(void*, int32_t);
  double (*get_var_double)(void*, int32_t);
  void* (*get_var_address)(void*, int32_t);
  void (*push_var_byte)(void*, int8_t);
  void (*push_var_short)(void*, int16_t);
  void (*push_var_int)(void*, int32_t);
  void (*push_var_long)(void*, int64_t);
  void (*push_var_float)(void*, float);
  void (*push_var_double)(void*, double);
  void (*push_var_address)(void*, void*);
  int32_t (*get_array_value_size)(void*, int32_t);
  void* (*get_object_fields)(void*, void*);
  int32_t (*get_object_field_index)(void*, void*, const char*);
  int32_t (*get_object_fields_length)(void*, void*);
  void (*set_object_field_value_byte)(void*, void*, const char*, int8_t);
  void (*set_object_field_value_short)(void*, void*, const char*, int16_t);
  void (*set_object_field_value_int)(void*, void*, const char*, int32_t);
  void (*set_object_field_value_long)(void*, void*, const char*, int64_t);
  void (*set_object_field_value_float)(void*, void*, const char*, float);
  void (*set_object_field_value_double)(void*, void*, const char*, double);
  int8_t (*get_object_field_value_byte)(void*, void*, const char*);
  int16_t (*get_object_field_value_short)(void*, void*, const char*);
  int32_t (*get_object_field_value_int)(void*, void*, const char*);
  int64_t (*get_object_field_value_long)(void*, void*, const char*);
  float (*get_object_field_value_float)(void*, void*, const char*);
  double (*get_object_field_value_double)(void*, void*, const char*);
  void* (*get_object_field_value_ref)(void*, void*, const char*);
  int32_t (*dump_object_field_names)(void*, void*);
  int32_t (*get_ref_count)(void*, void*);
  int8_t* (*get_array_values_byte)(void*, void*);
  int16_t* (*get_array_values_short)(void*, void*);
  int32_t* (*get_array_values_int)(void*, void*);
  int64_t* (*get_array_values_long)(void*, void*);
  float* (*get_array_values_float)(void*, void*);
  double* (*get_array_values_double)(void*, void*);
  void** (*get_array_values_ref)(void*, void*);
  void** (*call_sub)(void*, void*);
};

#endif
