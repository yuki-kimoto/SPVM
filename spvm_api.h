#ifndef SPVM_API_H
#define SPVM_API_H

#include <stdint.h>

enum {
  SPVM_API_ERROR_NO_ID = -1
};

struct SPVM_api;
typedef struct SPVM_api SPVM_API;
typedef void SPVM_API_OBJECT;

union SPVM_API_value {
  int8_t byte_value;
  int16_t short_value;
  int32_t int_value;
  int64_t long_value;
  float float_value;
  double double_value;
  SPVM_API_OBJECT* object_value;
};

// spvm_api.h
typedef union SPVM_API_value SPVM_API_VALUE;

struct SPVM_api {
  // Array functions
  int32_t (*get_array_length)(SPVM_API*, SPVM_API_OBJECT*);
  int32_t (*get_array_value_size)(SPVM_API*, int32_t);
  int8_t* (*get_byte_array_elements)(SPVM_API*, SPVM_API_OBJECT*);
  int16_t* (*get_short_array_elements)(SPVM_API*, SPVM_API_OBJECT*);
  int32_t* (*get_int_array_elements)(SPVM_API*, SPVM_API_OBJECT*);
  int64_t* (*get_long_array_elements)(SPVM_API*, SPVM_API_OBJECT*);
  float* (*get_float_array_elements)(SPVM_API*, SPVM_API_OBJECT*);
  double* (*get_double_array_elements)(SPVM_API*, SPVM_API_OBJECT*);
  SPVM_API_OBJECT** (*get_object_array_elements)(SPVM_API*, SPVM_API_OBJECT*);
  SPVM_API_OBJECT* (*get_object_array_element)(SPVM_API*, SPVM_API_OBJECT*, int32_t index);
  void (*set_object_array_element)(SPVM_API*, SPVM_API_OBJECT*, int32_t index, SPVM_API_OBJECT* value);
  
  // Object functions
  int32_t (*get_field_id)(SPVM_API*, SPVM_API_OBJECT*, const char*);
  int8_t (*get_byte_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t);
  int16_t (*get_short_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t);
  int32_t (*get_int_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t);
  int64_t (*get_long_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t);
  float (*get_float_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t);
  double (*get_double_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t);
  SPVM_API_OBJECT* (*get_object_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t);
  void (*set_byte_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t, int8_t);
  void (*set_short_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t, int16_t);
  void (*set_int_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t, int32_t);
  void (*set_long_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t, int64_t);
  void (*set_float_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t, float);
  void (*set_double_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t, double);
  void (*set_object_field)(SPVM_API*, SPVM_API_OBJECT*, int32_t, SPVM_API_OBJECT*);
  
  // Call subroutine fucntions
  int32_t (*get_sub_id)(SPVM_API*, const char*);
  void (*call_sub)(SPVM_API*, int32_t);
  void (*call_void_sub)(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args);
  int8_t (*call_byte_sub)(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args);
  int16_t (*call_short_sub)(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args);
  int32_t (*call_int_sub)(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args);
  int64_t (*call_long_sub)(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args);
  float (*call_float_sub)(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args);
  double (*call_double_sub)(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args);
  SPVM_API_OBJECT* (*call_object_sub)(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args);
  
  // Malloc funtctions
  int32_t (*get_package_id)(SPVM_API*, const char*);
  SPVM_API_OBJECT* (*new_object)(SPVM_API*, int32_t);
  SPVM_API_OBJECT* (*new_byte_array)(SPVM_API*, int32_t);
  SPVM_API_OBJECT* (*new_short_array)(SPVM_API*, int32_t);
  SPVM_API_OBJECT* (*new_int_array)(SPVM_API*, int32_t);
  SPVM_API_OBJECT* (*new_long_array)(SPVM_API*, int32_t);
  SPVM_API_OBJECT* (*new_float_array)(SPVM_API*, int32_t);
  SPVM_API_OBJECT* (*new_double_array)(SPVM_API*, int32_t);
  SPVM_API_OBJECT* (*new_object_array)(SPVM_API*, int32_t);
  
  // Exception
  void (*set_exception)(SPVM_API* api, SPVM_API_OBJECT* exception);
  SPVM_API_OBJECT* (*get_exception)(SPVM_API* api);
  
  // Reference count
  int32_t (*get_ref_count)(SPVM_API* api, SPVM_API_OBJECT* base_object);
  void (*inc_ref_count)(SPVM_API* api, SPVM_API_OBJECT* base_object);
  void (*dec_ref_count)(SPVM_API* api, SPVM_API_OBJECT* base_object);
  void (*inc_dec_ref_count)(SPVM_API* api, SPVM_API_OBJECT* base_object);
};
#endif
