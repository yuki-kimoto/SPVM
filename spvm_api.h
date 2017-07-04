#ifndef SPVM_API_H
#define SPVM_API_H

#include <stdint.h>

// spvm_api.h
struct SPVM_api;
typedef struct SPVM_api SPVM_API;

struct SPVM_api {
  void* runtime;
  int32_t (*get_array_length)(SPVM_API*, void*);
  int64_t (*calcurate_data_byte_size)(SPVM_API*, void*);
  void* (*create_data_array_byte)(SPVM_API*, int32_t);
  void* (*create_data_array_byte_from_pv)(SPVM_API*, const char*);
  void (*dec_ref_count)(SPVM_API*, void*);
  void (*inc_ref_count)(SPVM_API*, void*);
  void (*push_return_value_byte)(SPVM_API*, int8_t);
  void (*push_return_value_short)(SPVM_API*, int16_t);
  void (*push_return_value_int)(SPVM_API*, int32_t);
  void (*push_return_value_long)(SPVM_API*, int64_t);
  void (*push_return_value_float)(SPVM_API*, float);
  void (*push_return_value_double)(SPVM_API*, double);
  void (*push_ret)(SPVM_API*, void*);
  int8_t (*pop_return_value_byte)(SPVM_API*);
  int16_t (*pop_return_value_short)(SPVM_API*);
  int32_t (*pop_return_value_int)(SPVM_API*);
  int64_t (*pop_return_value_long)(SPVM_API*);
  float (*pop_return_value_float)(SPVM_API*);
  double (*pop_return_value_double)(SPVM_API*);
  void* (*pop_return_value_address)(SPVM_API*);
  int8_t (*get_var_byte)(SPVM_API*, int32_t);
  int16_t (*get_var_short)(SPVM_API*, int32_t);
  int32_t (*get_var_int)(SPVM_API*, int32_t);
  int64_t (*get_var_long)(SPVM_API*, int32_t);
  float (*get_var_float)(SPVM_API*, int32_t);
  double (*get_var_double)(SPVM_API*, int32_t);
  void* (*get_var_address)(SPVM_API*, int32_t);
  void (*push_var_byte)(SPVM_API*, int8_t);
  void (*push_var_short)(SPVM_API*, int16_t);
  void (*push_var_int)(SPVM_API*, int32_t);
  void (*push_var_long)(SPVM_API*, int64_t);
  void (*push_var_float)(SPVM_API*, float);
  void (*push_var_double)(SPVM_API*, double);
  void (*push_var_address)(SPVM_API*, void*);
  int32_t (*get_array_value_size)(SPVM_API*, int32_t);
  void* (*get_object_fields)(SPVM_API*, void*);
  int32_t (*get_object_field_index)(SPVM_API*, void*, const char*);
  int32_t (*get_object_fields_length)(SPVM_API*, void*);
  void (*set_object_field_value_byte)(SPVM_API*, void*, int32_t, int8_t);
  void (*set_object_field_value_short)(SPVM_API*, void*, int32_t, int16_t);
  void (*set_object_field_value_int)(SPVM_API*, void*, int32_t, int32_t);
  void (*set_object_field_value_long)(SPVM_API*, void*, int32_t, int64_t);
  void (*set_object_field_value_float)(SPVM_API*, void*, int32_t, float);
  void (*set_object_field_value_double)(SPVM_API*, void*, int32_t, double);
  int8_t (*get_object_field_value_byte)(SPVM_API*, void*, int32_t);
  int16_t (*get_object_field_value_short)(SPVM_API*, void*, int32_t);
  int32_t (*get_object_field_value_int)(SPVM_API*, void*, int32_t);
  int64_t (*get_object_field_value_long)(SPVM_API*, void*, int32_t);
  float (*get_object_field_value_float)(SPVM_API*, void*, int32_t);
  double (*get_object_field_value_double)(SPVM_API*, void*, int32_t);
  void* (*get_object_field_value_ref)(SPVM_API*, void*, int32_t);
  int32_t (*dump_object_field_names)(SPVM_API*, void*);
  int32_t (*get_ref_count)(SPVM_API*, void*);
  int8_t* (*get_array_values_byte)(SPVM_API*, void*);
  int16_t* (*get_array_values_short)(SPVM_API*, void*);
  int32_t* (*get_array_values_int)(SPVM_API*, void*);
  int64_t* (*get_array_values_long)(SPVM_API*, void*);
  float* (*get_array_values_float)(SPVM_API*, void*);
  double* (*get_array_values_double)(SPVM_API*, void*);
  void** (*get_array_values_ref)(SPVM_API*, void*);
  void** (*call_sub)(SPVM_API*, int32_t);
};

#endif
