#ifndef SPVM_API_H
#define SPVM_API_H

#include <stdint.h>

struct SPVM_api;
typedef struct SPVM_api SPVM_API;
typedef void SPVM_API_OBJECT;
typedef void SPVM_API_RUNTIME;

union SPVM_value {
  int8_t byte_value;
  int16_t short_value;
  int32_t int_value;
  int64_t long_value;
  float float_value;
  double double_value;
  SPVM_API_OBJECT* object_value;
  SPVM_API_OBJECT** object_address_value;
  char* string_value;
  void* pointer_value;
};

// spvm_api.h
typedef union SPVM_value SPVM_VALUE;

typedef int8_t SPVM_API_byte;
typedef int16_t SPVM_API_short;
typedef int32_t SPVM_API_int;
typedef int64_t SPVM_API_long;
typedef float SPVM_API_float;
typedef double SPVM_API_double;

struct SPVM_api {
  int32_t (*get_array_length)(SPVM_API*, SPVM_API_OBJECT*);
  int8_t* (*get_byte_array_elements)(SPVM_API*, SPVM_API_OBJECT*);
  int16_t* (*get_short_array_elements)(SPVM_API*, SPVM_API_OBJECT*);
  int32_t* (*get_int_array_elements)(SPVM_API*, SPVM_API_OBJECT*);
  int64_t* (*get_long_array_elements)(SPVM_API*, SPVM_API_OBJECT*);
  float* (*get_float_array_elements)(SPVM_API*, SPVM_API_OBJECT*);
  double* (*get_double_array_elements)(SPVM_API*, SPVM_API_OBJECT*);
  SPVM_API_OBJECT* (*get_object_array_element)(SPVM_API*, SPVM_API_OBJECT*, int32_t index);
  void (*set_object_array_element)(SPVM_API*, SPVM_API_OBJECT*, int32_t index, SPVM_API_OBJECT* value);
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
  int32_t (*get_sub_id)(SPVM_API*, const char*);
  void (*call_void_sub)(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args);
  int8_t (*call_byte_sub)(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args);
  int16_t (*call_short_sub)(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args);
  int32_t (*call_int_sub)(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args);
  int64_t (*call_long_sub)(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args);
  float (*call_float_sub)(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args);
  double (*call_double_sub)(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args);
  SPVM_API_OBJECT* (*call_object_sub)(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args);
  int32_t (*get_type_id)(SPVM_API*, const char*);
  SPVM_API_OBJECT* (*new_object)(SPVM_API*, int32_t);
  SPVM_API_OBJECT* (*new_byte_array)(SPVM_API*, int32_t);
  SPVM_API_OBJECT* (*new_short_array)(SPVM_API*, int32_t);
  SPVM_API_OBJECT* (*new_int_array)(SPVM_API*, int32_t);
  SPVM_API_OBJECT* (*new_long_array)(SPVM_API*, int32_t);
  SPVM_API_OBJECT* (*new_float_array)(SPVM_API*, int32_t);
  SPVM_API_OBJECT* (*new_double_array)(SPVM_API*, int32_t);
  SPVM_API_OBJECT* (*new_object_array)(SPVM_API*, int32_t, int32_t);
  SPVM_API_OBJECT* (*new_string)(SPVM_API* api, const char* string, int32_t length);
  int32_t (*get_string_length)(SPVM_API* api, SPVM_API_OBJECT*);
  char* (*get_string_chars)(SPVM_API* api, SPVM_API_OBJECT*);
  SPVM_API_OBJECT* (*get_exception)(SPVM_API* api);
  void (*set_exception)(SPVM_API* api, SPVM_API_OBJECT* exception);
  int32_t (*get_ref_count)(SPVM_API* api, SPVM_API_OBJECT* base_object);
  void (*inc_ref_count)(SPVM_API* api, SPVM_API_OBJECT* base_object);
  void (*dec_ref_count)(SPVM_API* api, SPVM_API_OBJECT* base_object);
  void (*inc_dec_ref_count)(SPVM_API* api, SPVM_API_OBJECT* base_object);
  int32_t (*get_objects_count)(SPVM_API* api);
  SPVM_API_RUNTIME* (*get_runtime)(SPVM_API* api);
  int32_t (*get_object_header_byte_size)(SPVM_API* api);
  void (*dec_ref_count_only)(SPVM_API* api, SPVM_API_OBJECT* base_object);
  int32_t (*get_object_header_length_offset)(SPVM_API* api);
  int32_t (*get_void_type_code)(SPVM_API* api);
  int32_t (*get_byte_type_code)(SPVM_API* api);
  int32_t (*get_short_type_code)(SPVM_API* api);
  int32_t (*get_int_type_code)(SPVM_API* api);
  int32_t (*get_long_type_code)(SPVM_API* api);
  int32_t (*get_float_type_code)(SPVM_API* api);
  int32_t (*get_double_type_code)(SPVM_API* api);
  void (*weaken)(SPVM_API* api, SPVM_API_OBJECT** object_address);
  int32_t (*isweak)(SPVM_API* api, SPVM_API_OBJECT* object);
  void (*unweaken)(SPVM_API* api, SPVM_API_OBJECT** object_address);
  SPVM_API_OBJECT* (*new_value_array)(SPVM_API* api, int32_t length);
  SPVM_VALUE* (*get_value_array_elements)(SPVM_API* api, SPVM_API_OBJECT* object);
  int32_t* (*get_constant_pool)(SPVM_API* api);
  int32_t* (*get_bytecodes)(SPVM_API* api);
  SPVM_VALUE* (*get_package_vars)(SPVM_API* api);
  int32_t (*is_debug)(SPVM_API* api);
  int32_t (*get_type_code)(SPVM_API* api, int32_t type_id);
  int32_t (*get_sub_name_id)(SPVM_API* api, int32_t sub_id);
  int32_t (*get_sub_file_name_id)(SPVM_API* api, int32_t sub_id);
  int32_t (*get_sub_args_length)(SPVM_API* api, int32_t sub_id);
  int32_t (*get_sub_operand_stack_max)(SPVM_API* api, int32_t sub_id);
  int32_t (*get_sub_my_vars_length)(SPVM_API* api, int32_t sub_id);
  int32_t (*get_sub_object_args_length)(SPVM_API* api, int32_t sub_id);
  int32_t (*get_sub_object_args_base)(SPVM_API* api, int32_t sub_id);
  int32_t (*get_sub_is_native)(SPVM_API* api, int32_t sub_id);
  int32_t (*get_sub_return_type_id)(SPVM_API* api, int32_t sub_id);
  void* (*get_sub_native_address)(SPVM_API* api, int32_t sub_id);
  int32_t (*get_sub_bytecode_base)(SPVM_API* api, int32_t sub_id);
  int32_t (*get_sub_is_void)(SPVM_API* api, int32_t sub_id);
  int32_t (*get_sub_object_my_vars_base)(SPVM_API* api, int32_t sub_id);
  int32_t (*get_sub_object_my_vars_length)(SPVM_API* api, int32_t sub_id);
  SPVM_API_OBJECT* (*concat_string_byte)(SPVM_API* api, SPVM_API_OBJECT* string1, int8_t string2);
  SPVM_API_OBJECT* (*concat_string_short)(SPVM_API* api, SPVM_API_OBJECT* string1, int16_t string2);
  SPVM_API_OBJECT* (*concat_string_int)(SPVM_API* api, SPVM_API_OBJECT* string1, int32_t string2);
  SPVM_API_OBJECT* (*concat_string_long)(SPVM_API* api, SPVM_API_OBJECT* string1, int64_t string2);
  SPVM_API_OBJECT* (*concat_string_float)(SPVM_API* api, SPVM_API_OBJECT* string1, float string2);
  SPVM_API_OBJECT* (*concat_string_double)(SPVM_API* api, SPVM_API_OBJECT* string1, double string2);
  SPVM_API_OBJECT* (*concat_string_string)(SPVM_API* api, SPVM_API_OBJECT* string1, SPVM_API_OBJECT* string2);
  void (*weaken_object_field)(SPVM_API* api, SPVM_API_OBJECT* object, int32_t field_id);
};
#endif
