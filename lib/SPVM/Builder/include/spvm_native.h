#ifndef SPVM_NATIVE_H
#define SPVM_NATIVE_H

#include <stdint.h>

struct SPVM_env;
typedef struct SPVM_env SPVM_ENV;

typedef union SPVM_value SPVM_VALUE;

union SPVM_value {
  int8_t bval;
  int16_t sval;
  int32_t ival;
  int64_t lval;
  float fval;
  double dval;
  void* oval;
  int8_t* bref;
  int16_t* sref;
  int32_t* iref;
  int64_t* lref;
  float* fref;
  double* dref;
};

typedef int8_t SPVM_VALUE_byte;
typedef int16_t SPVM_VALUE_short;
typedef int32_t SPVM_VALUE_int;
typedef int64_t SPVM_VALUE_long;
typedef float SPVM_VALUE_float;
typedef double SPVM_VALUE_double;
typedef void* SPVM_VALUE_object;

#define SPVM_SUCCESS 0
#define SPVM_EXCEPTION 1











struct SPVM_env {
  void* exception;
  void* native_mortal_stack;
  void* native_mortal_stack_top;
  void* native_mortal_stack_capacity;
  void* runtime;
  void* runtime_package_vars_heap_byte_offset;
  void* object_header_byte_size;
  void* object_ref_count_byte_offset;
  void* object_basic_type_id_byte_offset;
  void* object_type_dimension_byte_offset;
  void* object_array_length_byte_offset;
  void* byte_object_basic_type_id;
  void* short_object_basic_type_id;
  void* int_object_basic_type_id;
  void* long_object_basic_type_id;
  void* float_object_basic_type_id;
  void* double_object_basic_type_id;
  int32_t (*get_array_length)(SPVM_ENV*, void*);
  int8_t* (*get_byte_array_elements)(SPVM_ENV*, void*);
  int16_t* (*get_short_array_elements)(SPVM_ENV*, void*);
  int32_t* (*get_int_array_elements)(SPVM_ENV*, void*);
  int64_t* (*get_long_array_elements)(SPVM_ENV*, void*);
  float* (*get_float_array_elements)(SPVM_ENV*, void*);
  double* (*get_double_array_elements)(SPVM_ENV*, void*);
  void* (*get_object_array_element)(SPVM_ENV*, void*, int32_t index);
  void (*set_object_array_element)(SPVM_ENV*, void*, int32_t index, void* value);
  int32_t (*get_field_id)(SPVM_ENV*, const char*, const char*, const char*);
  int8_t (*get_byte_field)(SPVM_ENV*, void*, int32_t);
  int16_t (*get_short_field)(SPVM_ENV*, void*, int32_t);
  int32_t (*get_int_field)(SPVM_ENV*, void*, int32_t);
  int64_t (*get_long_field)(SPVM_ENV*, void*, int32_t);
  float (*get_float_field)(SPVM_ENV*, void*, int32_t);
  double (*get_double_field)(SPVM_ENV*, void*, int32_t);
  void* (*get_object_field)(SPVM_ENV*, void*, int32_t);
  void* (*get_pointer)(SPVM_ENV*, void*);
  void (*set_byte_field)(SPVM_ENV*, void*, int32_t, int8_t);
  void (*set_short_field)(SPVM_ENV*, void*, int32_t, int16_t);
  void (*set_int_field)(SPVM_ENV*, void*, int32_t, int32_t);
  void (*set_long_field)(SPVM_ENV*, void*, int32_t, int64_t);
  void (*set_float_field)(SPVM_ENV*, void*, int32_t, float);
  void (*set_double_field)(SPVM_ENV*, void*, int32_t, double);
  void (*set_object_field)(SPVM_ENV*, void*, int32_t, void*);
  int32_t (*get_sub_id)(SPVM_ENV*, const char*, const char*, const char*);
  int32_t (*get_sub_id_method_call)(SPVM_ENV*, void* object, const char*, const char*);
  int32_t (*get_basic_type_id)(SPVM_ENV*, const char*);
  void* (*new_object_raw)(SPVM_ENV*, int32_t);
  void* (*new_byte_array_raw)(SPVM_ENV*, int32_t);
  void* (*new_short_array_raw)(SPVM_ENV*, int32_t);
  void* (*new_int_array_raw)(SPVM_ENV*, int32_t);
  void* (*new_long_array_raw)(SPVM_ENV*, int32_t);
  void* (*new_float_array_raw)(SPVM_ENV*, int32_t);
  void* (*new_double_array_raw)(SPVM_ENV*, int32_t);
  void* (*new_object_array_raw)(SPVM_ENV*, int32_t, int32_t);
  void* (*new_multi_array_raw)(SPVM_ENV*, int32_t, int32_t, int32_t);
  void* (*new_value_array_raw)(SPVM_ENV*, int32_t, int32_t);
  void* (*new_string_raw)(SPVM_ENV* env, const char* bytes, int32_t length);
  void* (*new_pointer_raw)(SPVM_ENV*, int32_t basic_type_id, void* ptr);
  void* (*get_exception)(SPVM_ENV* env);
  void (*set_exception)(SPVM_ENV* env, void* exception);
  int32_t (*get_ref_count)(SPVM_ENV* env, void* object);
  void (*inc_ref_count)(SPVM_ENV* env, void* object);
  void (*dec_ref_count)(SPVM_ENV* env, void* object);
  void (*inc_dec_ref_count)(SPVM_ENV* env, void* object);
  int32_t (*get_memory_blocks_count)(SPVM_ENV* env);
  void (*dec_ref_count_only)(SPVM_ENV* env, void* object);
  void (*weaken)(SPVM_ENV* env, void** object_address);
  int32_t (*isweak)(SPVM_ENV* env, void** object);
  void (*unweaken)(SPVM_ENV* env, void** object_address);
  void* (*concat)(SPVM_ENV* env, void* string1, void* string2);
  void* (*create_exception_stack_trace)(SPVM_ENV* env, void* excetpion, const char* package_name, const char* sub_name, const char* file, int32_t line);
  int32_t (*call_sub)(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
  int32_t (*enter_scope)(SPVM_ENV* env);
  void (*push_mortal)(SPVM_ENV* env, void* object);
  void (*leave_scope)(SPVM_ENV* env, int32_t original_mortal_stack_top);
  void* (*new_object)(SPVM_ENV*, int32_t);
  void* (*new_byte_array)(SPVM_ENV*, int32_t);
  void* (*new_short_array)(SPVM_ENV*, int32_t);
  void* (*new_int_array)(SPVM_ENV*, int32_t);
  void* (*new_long_array)(SPVM_ENV*, int32_t);
  void* (*new_float_array)(SPVM_ENV*, int32_t);
  void* (*new_double_array)(SPVM_ENV*, int32_t);
  void* (*new_object_array)(SPVM_ENV*, int32_t, int32_t);
  void* (*new_multi_array)(SPVM_ENV*, int32_t, int32_t, int32_t);
  void* (*new_value_array)(SPVM_ENV*, int32_t, int32_t);
  void* (*new_string)(SPVM_ENV* env, const char* bytes, int32_t length);
  void* (*new_pointer)(SPVM_ENV* env, int32_t basic_type_id, void* ptr);
  int32_t (*get_package_var_id)(SPVM_ENV* env, const char* package_name, const char* package_var_name, const char* signature);
  int32_t (*has_interface)(SPVM_ENV*, void* object, int32_t interface_basic_type_id);
  int32_t (*get_field_byte_offset)(SPVM_ENV*, int32_t);
  void* (*new_env)(SPVM_ENV*);
  void (*free_env)(SPVM_ENV*);
};
#endif
