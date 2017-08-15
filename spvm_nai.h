#ifndef SPVM_NAI_H
#define SPVM_NAI_H

// NAI - SPVM Native Interface

#include <stdint.h>

enum {
  SPVM_NAI_ERROR_NO_ID = -1
};

struct SPVM_nai;
typedef struct SPVM_nai SPVM_NAI;
typedef void SPVM_NAI_OBJECT;

union SPVM_NAI_value {
  int8_t byte_value;
  int16_t short_value;
  int32_t int_value;
  int64_t long_value;
  float float_value;
  double double_value;
  SPVM_NAI_OBJECT* object_value;
};

// spvm_nai.h
typedef union SPVM_NAI_value SPVM_NAI_VALUE;

struct SPVM_nai {
  // Array functions
  int32_t (*get_array_length)(SPVM_NAI*, SPVM_NAI_OBJECT*);
  int32_t (*get_array_value_size)(SPVM_NAI*, int32_t);
  int8_t* (*get_byte_array_elements)(SPVM_NAI*, SPVM_NAI_OBJECT*);
  int16_t* (*get_short_array_elements)(SPVM_NAI*, SPVM_NAI_OBJECT*);
  int32_t* (*get_int_array_elements)(SPVM_NAI*, SPVM_NAI_OBJECT*);
  int64_t* (*get_long_array_elements)(SPVM_NAI*, SPVM_NAI_OBJECT*);
  float* (*get_float_array_elements)(SPVM_NAI*, SPVM_NAI_OBJECT*);
  double* (*get_double_array_elements)(SPVM_NAI*, SPVM_NAI_OBJECT*);
  SPVM_NAI_OBJECT** (*get_object_array_elements)(SPVM_NAI*, SPVM_NAI_OBJECT*);
  SPVM_NAI_OBJECT* (*get_object_array_element)(SPVM_NAI*, SPVM_NAI_OBJECT*, int32_t index);
  void (*set_object_array_element)(SPVM_NAI*, SPVM_NAI_OBJECT*, int32_t index, SPVM_NAI_OBJECT* value);
  
  // Object functions
  int32_t (*get_field_id)(SPVM_NAI*, SPVM_NAI_OBJECT*, const char*);
  int8_t (*get_byte_field)(SPVM_NAI*, SPVM_NAI_OBJECT*, int32_t);
  int16_t (*get_short_field)(SPVM_NAI*, SPVM_NAI_OBJECT*, int32_t);
  int32_t (*get_int_field)(SPVM_NAI*, SPVM_NAI_OBJECT*, int32_t);
  int64_t (*get_long_field)(SPVM_NAI*, SPVM_NAI_OBJECT*, int32_t);
  float (*get_float_field)(SPVM_NAI*, SPVM_NAI_OBJECT*, int32_t);
  double (*get_double_field)(SPVM_NAI*, SPVM_NAI_OBJECT*, int32_t);
  SPVM_NAI_OBJECT* (*get_object_field)(SPVM_NAI*, SPVM_NAI_OBJECT*, int32_t);
  void (*set_byte_field)(SPVM_NAI*, SPVM_NAI_OBJECT*, int32_t, int8_t);
  void (*set_short_field)(SPVM_NAI*, SPVM_NAI_OBJECT*, int32_t, int16_t);
  void (*set_int_field)(SPVM_NAI*, SPVM_NAI_OBJECT*, int32_t, int32_t);
  void (*set_long_field)(SPVM_NAI*, SPVM_NAI_OBJECT*, int32_t, int64_t);
  void (*set_float_field)(SPVM_NAI*, SPVM_NAI_OBJECT*, int32_t, float);
  void (*set_double_field)(SPVM_NAI*, SPVM_NAI_OBJECT*, int32_t, double);
  void (*set_object_field)(SPVM_NAI*, SPVM_NAI_OBJECT*, int32_t, SPVM_NAI_OBJECT*);
  
  // Call subroutine fucntions
  int32_t (*get_sub_id)(SPVM_NAI*, const char*);
  void (*call_sub)(SPVM_NAI*, int32_t);
  void (*call_void_sub)(SPVM_NAI* nai, int32_t sub_id, SPVM_NAI_VALUE* args);
  int8_t (*call_byte_sub)(SPVM_NAI* nai, int32_t sub_id, SPVM_NAI_VALUE* args);
  int16_t (*call_short_sub)(SPVM_NAI* nai, int32_t sub_id, SPVM_NAI_VALUE* args);
  int32_t (*call_int_sub)(SPVM_NAI* nai, int32_t sub_id, SPVM_NAI_VALUE* args);
  int64_t (*call_long_sub)(SPVM_NAI* nai, int32_t sub_id, SPVM_NAI_VALUE* args);
  float (*call_float_sub)(SPVM_NAI* nai, int32_t sub_id, SPVM_NAI_VALUE* args);
  double (*call_double_sub)(SPVM_NAI* nai, int32_t sub_id, SPVM_NAI_VALUE* args);
  SPVM_NAI_OBJECT* (*call_object_sub)(SPVM_NAI* nai, int32_t sub_id, SPVM_NAI_VALUE* args);
  
  // Malloc funtctions
  int32_t (*get_package_id)(SPVM_NAI*, const char*);
  SPVM_NAI_OBJECT* (*new_object)(SPVM_NAI*, int32_t);
  SPVM_NAI_OBJECT* (*new_byte_array)(SPVM_NAI*, int32_t);
  SPVM_NAI_OBJECT* (*new_short_array)(SPVM_NAI*, int32_t);
  SPVM_NAI_OBJECT* (*new_int_array)(SPVM_NAI*, int32_t);
  SPVM_NAI_OBJECT* (*new_long_array)(SPVM_NAI*, int32_t);
  SPVM_NAI_OBJECT* (*new_float_array)(SPVM_NAI*, int32_t);
  SPVM_NAI_OBJECT* (*new_double_array)(SPVM_NAI*, int32_t);
  SPVM_NAI_OBJECT* (*new_object_array)(SPVM_NAI*, int32_t);
  
  // Exception
  void (*set_exception)(SPVM_NAI* nai, SPVM_NAI_OBJECT* exception);
  SPVM_NAI_OBJECT* (*get_exception)(SPVM_NAI* nai);
  
  // Reference count
  int32_t (*get_ref_count)(SPVM_NAI* nai, SPVM_NAI_OBJECT* base_object);
  void (*inc_ref_count)(SPVM_NAI* nai, SPVM_NAI_OBJECT* base_object);
  void (*dec_ref_count)(SPVM_NAI* nai, SPVM_NAI_OBJECT* base_object);
  void (*inc_dec_ref_count)(SPVM_NAI* nai, SPVM_NAI_OBJECT* base_object);
};
#endif
