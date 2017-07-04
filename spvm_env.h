#ifndef SPVM_ENV_H
#define SPVM_ENV_H

#include <stdint.h>

// spvm_env.h
struct SPVM_env;
typedef struct SPVM_env SPVM_ENV;

struct SPVM_env {
  void* runtime;
  int32_t (*get_array_length)(SPVM_ENV*, void*);
  int64_t (*calcurate_data_byte_size)(SPVM_ENV*, void*);
  void* (*create_data_array_byte)(SPVM_ENV*, int32_t);
  void* (*create_data_array_byte_from_pv)(SPVM_ENV*, const char*);
  void (*dec_ref_count)(SPVM_ENV*, void*);
  void (*inc_ref_count)(SPVM_ENV*, void*);
  void (*push_return_value_byte)(SPVM_ENV*, int8_t);
  void (*push_return_value_short)(SPVM_ENV*, int16_t);
  void (*push_return_value_int)(SPVM_ENV*, int32_t);
  void (*push_return_value_long)(SPVM_ENV*, int64_t);
  void (*push_return_value_float)(SPVM_ENV*, float);
  void (*push_return_value_double)(SPVM_ENV*, double);
  void (*push_ret)(SPVM_ENV*, void*);
  int8_t (*pop_return_value_byte)(SPVM_ENV*);
  int16_t (*pop_return_value_short)(SPVM_ENV*);
  int32_t (*pop_return_value_int)(SPVM_ENV*);
  int64_t (*pop_return_value_long)(SPVM_ENV*);
  float (*pop_return_value_float)(SPVM_ENV*);
  double (*pop_return_value_double)(SPVM_ENV*);
  void* (*pop_return_value_address)(SPVM_ENV*);
  int8_t (*get_var_byte)(SPVM_ENV*, int32_t);
  int16_t (*get_var_short)(SPVM_ENV*, int32_t);
  int32_t (*get_var_int)(SPVM_ENV*, int32_t);
  int64_t (*get_var_long)(SPVM_ENV*, int32_t);
  float (*get_var_float)(SPVM_ENV*, int32_t);
  double (*get_var_double)(SPVM_ENV*, int32_t);
  void* (*get_var_address)(SPVM_ENV*, int32_t);
  void (*push_var_byte)(SPVM_ENV*, int8_t);
  void (*push_var_short)(SPVM_ENV*, int16_t);
  void (*push_var_int)(SPVM_ENV*, int32_t);
  void (*push_var_long)(SPVM_ENV*, int64_t);
  void (*push_var_float)(SPVM_ENV*, float);
  void (*push_var_double)(SPVM_ENV*, double);
  void (*push_var_address)(SPVM_ENV*, void*);
  int32_t (*get_array_value_size)(SPVM_ENV*, int32_t);
  void* (*get_object_fields)(SPVM_ENV*, void*);
  int32_t (*get_object_field_index)(SPVM_ENV*, void*, const char*);
  int32_t (*get_object_fields_length)(SPVM_ENV*, void*);
  void (*set_object_field_value_byte)(SPVM_ENV*, void*, int32_t, int8_t);
  void (*set_object_field_value_short)(SPVM_ENV*, void*, int32_t, int16_t);
  void (*set_object_field_value_int)(SPVM_ENV*, void*, int32_t, int32_t);
  void (*set_object_field_value_long)(SPVM_ENV*, void*, int32_t, int64_t);
  void (*set_object_field_value_float)(SPVM_ENV*, void*, int32_t, float);
  void (*set_object_field_value_double)(SPVM_ENV*, void*, int32_t, double);
  int8_t (*get_object_field_value_byte)(SPVM_ENV*, void*, int32_t);
  int16_t (*get_object_field_value_short)(SPVM_ENV*, void*, int32_t);
  int32_t (*get_object_field_value_int)(SPVM_ENV*, void*, int32_t);
  int64_t (*get_object_field_value_long)(SPVM_ENV*, void*, int32_t);
  float (*get_object_field_value_float)(SPVM_ENV*, void*, int32_t);
  double (*get_object_field_value_double)(SPVM_ENV*, void*, int32_t);
  void* (*get_object_field_value_ref)(SPVM_ENV*, void*, int32_t);
  int32_t (*dump_object_field_names)(SPVM_ENV*, void*);
  int32_t (*get_ref_count)(SPVM_ENV*, void*);
  int8_t* (*get_array_values_byte)(SPVM_ENV*, void*);
  int16_t* (*get_array_values_short)(SPVM_ENV*, void*);
  int32_t* (*get_array_values_int)(SPVM_ENV*, void*);
  int64_t* (*get_array_values_long)(SPVM_ENV*, void*);
  float* (*get_array_values_float)(SPVM_ENV*, void*);
  double* (*get_array_values_double)(SPVM_ENV*, void*);
  void** (*get_array_values_ref)(SPVM_ENV*, void*);
  void** (*call_sub)(SPVM_ENV*, int32_t);
};

#endif
