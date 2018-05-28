#ifndef SPVM_NATIVE_H
#define SPVM_NATIVE_H

#include <stdint.h>

struct SPVM_env;
typedef struct SPVM_env SPVM_ENV;

union SPVM_value {
  int8_t bval;
  int16_t sval;
  int32_t ival;
  int64_t lval;
  float fval;
  double dval;
  void* oval;
};

// spvm_native.h
typedef union SPVM_value SPVM_VALUE;

typedef int8_t SPVM_VALUE_byte;
typedef int16_t SPVM_VALUE_short;
typedef int32_t SPVM_VALUE_int;
typedef int64_t SPVM_VALUE_long;
typedef float SPVM_VALUE_float;
typedef double SPVM_VALUE_double;
typedef void* SPVM_VALUE_object;






struct SPVM_env {
  int32_t (*get_array_length)(SPVM_ENV*, void*);
  int8_t* (*get_byte_array_elements)(SPVM_ENV*, void*);
  int16_t* (*get_short_array_elements)(SPVM_ENV*, void*);
  int32_t* (*get_int_array_elements)(SPVM_ENV*, void*);
  int64_t* (*get_long_array_elements)(SPVM_ENV*, void*);
  float* (*get_float_array_elements)(SPVM_ENV*, void*);
  double* (*get_double_array_elements)(SPVM_ENV*, void*);
  void* (*get_object_array_element)(SPVM_ENV*, void*, int32_t index);
  void (*set_object_array_element)(SPVM_ENV*, void*, int32_t index, void* value);
  int32_t (*get_field_id)(SPVM_ENV*, void*, const char*);
  int8_t (*get_byte_field)(SPVM_ENV*, void*, int32_t);
  int16_t (*get_short_field)(SPVM_ENV*, void*, int32_t);
  int32_t (*get_int_field)(SPVM_ENV*, void*, int32_t);
  int64_t (*get_long_field)(SPVM_ENV*, void*, int32_t);
  float (*get_float_field)(SPVM_ENV*, void*, int32_t);
  double (*get_double_field)(SPVM_ENV*, void*, int32_t);
  void* (*get_object_field)(SPVM_ENV*, void*, int32_t);
  void (*set_byte_field)(SPVM_ENV*, void*, int32_t, int8_t);
  void (*set_short_field)(SPVM_ENV*, void*, int32_t, int16_t);
  void (*set_int_field)(SPVM_ENV*, void*, int32_t, int32_t);
  void (*set_long_field)(SPVM_ENV*, void*, int32_t, int64_t);
  void (*set_float_field)(SPVM_ENV*, void*, int32_t, float);
  void (*set_double_field)(SPVM_ENV*, void*, int32_t, double);
  void (*set_object_field)(SPVM_ENV*, void*, int32_t, void*);
  int32_t (*get_sub_id)(SPVM_ENV*, const char*);
  int32_t (*get_sub_id_interface_method)(SPVM_ENV*, void* object, int32_t);
  int32_t (*get_class_method_sub_id)(SPVM_ENV*, const char*, const char*);
  int32_t (*get_basic_type_id)(SPVM_ENV*, const char*);
  void (*call_void_sub)(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
  int8_t (*call_byte_sub)(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
  int16_t (*call_short_sub)(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
  int32_t (*call_int_sub)(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
  int64_t (*call_long_sub)(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
  float (*call_float_sub)(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
  double (*call_double_sub)(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
  void* (*call_object_sub)(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
  void* (*new_object)(SPVM_ENV*, int32_t);
  void* (*new_byte_array)(SPVM_ENV*, int32_t);
  void* (*new_short_array)(SPVM_ENV*, int32_t);
  void* (*new_int_array)(SPVM_ENV*, int32_t);
  void* (*new_long_array)(SPVM_ENV*, int32_t);
  void* (*new_float_array)(SPVM_ENV*, int32_t);
  void* (*new_double_array)(SPVM_ENV*, int32_t);
  void* (*new_object_array)(SPVM_ENV*, int32_t, int32_t);
  void* (*new_multi_array)(SPVM_ENV*, int32_t, int32_t, int32_t);
  void* (*new_string)(SPVM_ENV* env, char* bytes, int32_t length);
  void* (*get_exception)(SPVM_ENV* env);
  void (*set_exception)(SPVM_ENV* env, void* exception);
  int32_t (*get_ref_count)(SPVM_ENV* env, void* object);
  void (*inc_ref_count)(SPVM_ENV* env, void* object);
  void (*dec_ref_count)(SPVM_ENV* env, void* object);
  void (*inc_dec_ref_count)(SPVM_ENV* env, void* object);
  int32_t (*get_objects_count)(SPVM_ENV* env);
  void* (*get_runtime)(SPVM_ENV* env);
  void (*dec_ref_count_only)(SPVM_ENV* env, void* object);
  void (*weaken)(SPVM_ENV* env, void** object_address);
  int32_t (*isweak)(SPVM_ENV* env, void* object);
  void (*unweaken)(SPVM_ENV* env, void** object_address);
  void* (*concat)(SPVM_ENV* env, void* string1, void* string2);
  void (*weaken_object_field)(SPVM_ENV* env, void* object, int32_t field_id);
  void* (*create_exception_stack_trace)(SPVM_ENV* env, void* excetpion, int32_t sub_id, int32_t current_line);
  int32_t (*check_cast)(SPVM_ENV* env, int32_t cast_basic_type_id, int32_t cast_type_dimension, void* object);
  void* object_header_byte_size;
  void* object_ref_count_byte_offset;
  void* object_basic_type_id_byte_offset;
  void* object_dimension_byte_offset;
  void* object_units_length_byte_offset;
};
#endif
