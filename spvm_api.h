#ifndef SPVM_API_H
#define SPVM_API_H

#include <stdint.h>

// spvm_api.h
struct SPVM_api;
typedef struct SPVM_api SPVM_API;
typedef void SPVM_API_OBJECT;
typedef void SPVM_API_ARRAY_OBJECT;
typedef void SPVM_API_BASE_OBJECT;

struct SPVM_api {
  void* runtime;
  int32_t (*get_array_length)(SPVM_API*, SPVM_API_ARRAY_OBJECT*);
  int64_t (*calcurate_base_object_byte_size)(SPVM_API*, SPVM_API_BASE_OBJECT*);
  void* (*create_array_object_byte)(SPVM_API*, int32_t);
  void* (*create_array_object_byte_from_pv)(SPVM_API*, const char*);
  void (*dec_ref_count)(SPVM_API*, SPVM_API_BASE_OBJECT*);
  void (*inc_ref_count)(SPVM_API*, SPVM_API_BASE_OBJECT*);
  void (*push_stack_byte)(SPVM_API*, int8_t);
  void (*push_stack_short)(SPVM_API*, int16_t);
  void (*push_stack_int)(SPVM_API*, int32_t);
  void (*push_stack_long)(SPVM_API*, int64_t);
  void (*push_stack_float)(SPVM_API*, float);
  void (*push_stack_double)(SPVM_API*, double);
  void (*push_stack_ref)(SPVM_API*, void*);
  int8_t (*pop_stack_byte)(SPVM_API*);
  int16_t (*pop_stack_short)(SPVM_API*);
  int32_t (*pop_stack_int)(SPVM_API*);
  int64_t (*pop_stack_long)(SPVM_API*);
  float (*pop_stack_float)(SPVM_API*);
  double (*pop_stack_double)(SPVM_API*);
  void* (*pop_stack_address)(SPVM_API*);
  int8_t (*get_var_byte)(SPVM_API*, int32_t);
  int16_t (*get_var_short)(SPVM_API*, int32_t);
  int32_t (*get_var_int)(SPVM_API*, int32_t);
  int64_t (*get_var_long)(SPVM_API*, int32_t);
  float (*get_var_float)(SPVM_API*, int32_t);
  double (*get_var_double)(SPVM_API*, int32_t);
  void* (*get_var_address)(SPVM_API*, int32_t);
  int32_t (*get_array_value_size)(SPVM_API*, int32_t);
  void* (*get_fields)(SPVM_API*, SPVM_API_OBJECT*);
  int32_t (*get_field_index)(SPVM_API*, SPVM_API_OBJECT*, const char*);
  int32_t (*get_fields_length)(SPVM_API*, SPVM_API_OBJECT*);
  void (*set_byte_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t, int8_t);
  void (*set_short_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t, int16_t);
  void (*set_int_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t, int32_t);
  void (*set_long_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t, int64_t);
  void (*set_float_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t, float);
  void (*set_double_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t, double);
  int8_t (*get_byte_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t);
  int16_t (*get_short_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t);
  int32_t (*get_int_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t);
  int64_t (*get_long_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t);
  float (*get_float_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t);
  double (*get_double_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t);
  void* (*get_ref_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t);
  int32_t (*dump_field_names)(SPVM_API*, SPVM_API_OBJECT*);
  int32_t (*get_ref_count)(SPVM_API*, SPVM_API_BASE_OBJECT*);
  int8_t* (*get_byte_array_elements)(SPVM_API*, SPVM_API_ARRAY_OBJECT*);
  int16_t* (*get_short_array_elements)(SPVM_API*, SPVM_API_ARRAY_OBJECT*);
  int32_t* (*get_int_array_elements)(SPVM_API*, SPVM_API_ARRAY_OBJECT*);
  int64_t* (*get_long_array_elements)(SPVM_API*, SPVM_API_ARRAY_OBJECT*);
  float* (*get_float_array_elements)(SPVM_API*, SPVM_API_ARRAY_OBJECT*);
  double* (*get_double_array_elements)(SPVM_API*, SPVM_API_ARRAY_OBJECT*);
  void** (*get_ref_array_elements)(SPVM_API*, SPVM_API_ARRAY_OBJECT*);
  void** (*call_sub)(SPVM_API*, int32_t);
};

#endif
