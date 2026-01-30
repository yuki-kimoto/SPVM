// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_NATIVE_H
#define SPVM_NATIVE_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "spvm_version.h"

#define SPVM_NATIVE_GET_POINTER(object) (*(void**)object)

#define SPVM_NATIVE_SET_POINTER(object, pointer) (*(void**)object = pointer)

#define spvm_warnf(stream, format, ...) fprintf(stream, format "\n  %s at %s line %d\n", ##__VA_ARGS__, __func__, __FILE__, __LINE__)

#define spvm_warn(format, ...) spvm_warnf(stderr, format, ##__VA_ARGS__)

typedef union spvm_value SPVM_VALUE;

struct spvm_env;
typedef struct spvm_env SPVM_ENV;

struct spvm_env_api;
typedef struct spvm_env_api SPVM_ENV_API;

struct spvm_api_allocator;
typedef struct spvm_api_allocator SPVM_API_ALLOCATOR;

struct spvm_api_string_buffer;
typedef struct spvm_api_string_buffer SPVM_API_STRING_BUFFER;

struct spvm_api_compiler;
typedef struct spvm_api_compiler SPVM_API_COMPILER;

struct spvm_api_class_file;
typedef struct spvm_api_class_file SPVM_API_CLASS_FILE;

struct spvm_api_runtime;
typedef struct spvm_api_runtime SPVM_API_RUNTIME;

struct spvm_api_basic_type;
typedef struct spvm_api_basic_type SPVM_API_BASIC_TYPE;

struct spvm_api_class_var;
typedef struct spvm_api_class_var SPVM_API_CLASS_VAR;

struct spvm_api_field;
typedef struct spvm_api_field SPVM_API_FIELD;

struct spvm_api_type;
typedef struct spvm_api_type SPVM_API_TYPE;

struct spvm_api_method;
typedef struct spvm_api_method SPVM_API_METHOD;

struct spvm_api_arg;
typedef struct spvm_api_arg SPVM_API_ARG;

struct spvm_api_internal;
typedef struct spvm_api_internal SPVM_API_INTERNAL;

struct spvm_api_mutex;
typedef struct spvm_api_mutex SPVM_API_MUTEX;

union spvm_value {
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















struct spvm_env {
  void* runtime;
  SPVM_ENV_API* api;
  SPVM_ENV* (*new_env)(void);
  void (*free_env)(SPVM_ENV* env);
  int32_t (*call_init_methods)(SPVM_ENV* env, SPVM_VALUE* stack);
  int32_t (*set_command_info_program_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* obj_program_name);
  int32_t (*set_command_info_argv)(SPVM_ENV* env, SPVM_VALUE* stack, void* obj_argv);
  int32_t (*set_command_info_basetime)(SPVM_ENV* env, SPVM_VALUE* stack, int64_t base_time);
  void (*destroy_class_vars)(SPVM_ENV* env, SPVM_VALUE* stack);
  int32_t (*args_width)(SPVM_ENV* env, SPVM_VALUE* stack);
  void* (*get_object_basic_type)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*get_object_basic_type_id)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  const char* (*get_object_basic_type_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*get_object_type_dimension)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void* (*get_basic_type)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name);
  void* (*get_basic_type_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* (*get_basic_type_by_id)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id);
  int32_t (*get_basic_type_id)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name);
  int32_t (*get_basic_type_id_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* (*get_class_var)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name);
  int8_t (*get_class_var_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);
  int16_t (*get_class_var_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);
  int32_t (*get_class_var_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);
  int64_t (*get_class_var_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);
  float (*get_class_var_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);
  double (*get_class_var_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);
  void* (*get_class_var_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);
  void* (*get_class_var_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);
  void (*set_class_var_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, int8_t value);
  void (*set_class_var_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, int16_t value);
  void (*set_class_var_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, int32_t value);
  void (*set_class_var_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, int64_t value);
  void (*set_class_var_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, float value);
  void (*set_class_var_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, double value);
  void (*set_class_var_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, void* value);
  void (*set_class_var_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, void* value);
  void** (*get_class_var_object_ref)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);
  int8_t (*get_class_var_byte_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  int16_t (*get_class_var_short_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  int32_t (*get_class_var_int_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  int64_t (*get_class_var_long_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  float (*get_class_var_float_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  double (*get_class_var_double_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* (*get_class_var_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* (*get_class_var_string_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_byte_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int8_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_short_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int16_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_int_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_long_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int64_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_float_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, float value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_double_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, double value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, void* value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_string_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, void* value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* (*get_field)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name);
  void* (*get_field_static)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* field_name);
  int8_t (*get_field_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);
  int16_t (*get_field_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);
  int32_t (*get_field_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);
  int64_t (*get_field_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);
  float (*get_field_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);
  double (*get_field_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);
  void* (*get_field_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);
  void* (*get_field_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);
  void (*set_field_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, int8_t value);
  void (*set_field_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, int16_t value);
  void (*set_field_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, int32_t value);
  void (*set_field_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, int64_t value);
  void (*set_field_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, float value);
  void (*set_field_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, double value);
  void (*set_field_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, void* value);
  void (*set_field_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, void* value);
  int8_t (*get_field_byte_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  int16_t (*get_field_short_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  int32_t (*get_field_int_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  int64_t (*get_field_long_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  float (*get_field_float_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  double (*get_field_double_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* (*get_field_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* (*get_field_string_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*set_field_byte_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int8_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*set_field_short_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int16_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*set_field_int_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*set_field_long_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int64_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*set_field_float_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, float value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*set_field_double_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, double value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*set_field_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, void* value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*set_field_string_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, void* value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  const char* (*get_field_string_chars_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* (*get_method)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name);
  void* (*get_class_method)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name);
  void* (*get_instance_method_static)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name);
  void* (*get_instance_method)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* method_name);
  int32_t (*call_method_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* method, int32_t args_width, const char* func_name, const char* file, int32_t line);
  int32_t (*call_method)(SPVM_ENV* env, SPVM_VALUE* stack, void* method, int32_t args_width, const char* func_name, const char* file, int32_t line);
  void (*call_class_method_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name, int32_t args_width, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*call_instance_method_static_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name, int32_t args_width, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*call_instance_method_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t args_width, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* (*new_object_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type);
  void* (*new_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type);
  void* (*new_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* (*new_pointer_object_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, void* pointer);
  void* (*new_pointer_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, void* pointer);
  void* (*new_pointer_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, void* pointer, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* (*get_pointer)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void (*set_pointer)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* pointer);
  void* (*new_string_nolen_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes);
  void* (*new_string_nolen)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes);
  void* (*new_string_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length);
  void* (*new_string)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length);
  void* (*new_byte_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_byte_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_short_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_short_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_int_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_int_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_long_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_long_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_float_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_float_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_double_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_double_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_object_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t length);
  void* (*new_object_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t length);
  void* (*new_object_array_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t length, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* (*new_string_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_muldim_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t type_dimension, int32_t length);
  void* (*new_muldim_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t type_dimension, int32_t length);
  void* (*new_muldim_array_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t type_dimension, int32_t length, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* (*new_mulnum_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t length);
  void* (*new_mulnum_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t length);
  void* (*new_mulnum_array_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t length, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* (*new_array_proto_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t length);
  void* (*new_array_proto)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t length);
  int32_t (*length)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int8_t* (*get_elems_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  int16_t* (*get_elems_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  int32_t* (*get_elems_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  int64_t* (*get_elems_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  float* (*get_elems_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  double* (*get_elems_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  void* (*get_elem_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index);
  void* (*get_elem_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index);
  void (*set_elem_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, void* object);
  void (*set_elem_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, void* string);
  const char* (*get_chars)(SPVM_ENV* env, SPVM_VALUE* stack, void* string_object);
  int32_t (*get_bool_object_value)(SPVM_ENV* env, SPVM_VALUE* stack, void* bool_object);
  void* (*concat_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* string1, void* string2);
  void* (*concat)(SPVM_ENV* env, SPVM_VALUE* stack, void* string1, void* string2);
  void (*shorten)(SPVM_ENV* env, SPVM_VALUE* stack, void* string, int32_t new_length);
  void (*make_read_only)(SPVM_ENV* env, SPVM_VALUE* stack, void* string);
  int32_t (*is_read_only)(SPVM_ENV* env, SPVM_VALUE* stack, void* string);
  void (*print)(SPVM_ENV* env, SPVM_VALUE* stack, void* string);
  void (*print_stderr)(SPVM_ENV* env, SPVM_VALUE* stack, void* string);
  void* (*dump_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void* (*dump)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  const char* (*dumpc)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void* (*copy_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void* (*copy)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  const char* (*get_spvm_version_string)(SPVM_ENV* env, SPVM_VALUE* stack);
  double (*get_spvm_version_number)(SPVM_ENV* env, SPVM_VALUE* stack);
  const char* (*get_version_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type);
  double (*get_version_number)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type);
  int32_t (*die)(SPVM_ENV* env, SPVM_VALUE* stack, const char* exception_format, const char* func_name, const char* file, int32_t line, ...);
  void* (*get_exception)(SPVM_ENV* env, SPVM_VALUE* stack);
  int32_t (*set_exception)(SPVM_ENV* env, SPVM_VALUE* stack, void* exception);
  void* (*new_stack_trace_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* exception, void* method, int32_t line);
  void* (*new_stack_trace)(SPVM_ENV* env, SPVM_VALUE* stack, void* exception, void* method, int32_t line);
  int32_t (*is_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*is_class)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*is_pointer_class)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*is_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*is_object_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*is_numeric_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*is_mulnum_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*isa)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* basic_type, int32_t type_dimension);
  int32_t (*isa_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* basic_type_name, int32_t type_dimension);
  int32_t (*is_type)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* basic_type, int32_t type_dimension);
  int32_t (*is_type_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* basic_type_name, int32_t type_dimension);
  int32_t (*elem_isa)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, void* element);
  int32_t (*get_elem_size)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  void* (*get_type_name_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void* (*get_type_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void* (*get_compile_type_name_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t type_dimension, int32_t type_flag);
  void* (*get_compile_type_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t type_dimension, int32_t type_flag);
  int32_t (*enter_scope)(SPVM_ENV* env, SPVM_VALUE* stack);
  void (*leave_scope)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t mortal_stack_top);
  int32_t (*push_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*weaken)(SPVM_ENV* env, SPVM_VALUE* stack, void** object_address);
  int32_t (*isweak)(SPVM_ENV* env, SPVM_VALUE* stack, void** object);
  void (*unweaken)(SPVM_ENV* env, SPVM_VALUE* stack, void** object_address);
  void* (*strerror_string)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length);
  void* (*strerror_string_nolen)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value);
  const char* (*strerror)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length);
  const char* (*strerror_nolen)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value);
  int32_t (*is_binary_compatible_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*is_binary_compatible_stack)(SPVM_ENV* env, SPVM_VALUE* stack);
  SPVM_VALUE* (*new_stack)(SPVM_ENV* env);
  void (*free_stack)(SPVM_ENV* env, SPVM_VALUE* stack);
  void* (*get_field_object_defined_and_has_pointer_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file_name, int32_t line);
  void** (*get_field_object_ref)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);
  void** (*get_field_object_ref_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  int32_t (*check_bootstrap_method)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name);
  void (*assign_object)(SPVM_ENV* env, SPVM_VALUE* stack, void** dist_ref, void* object);
  void* (*new_string_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_memory_block)(SPVM_ENV* env, SPVM_VALUE* stack, size_t size);
  void (*free_memory_block)(SPVM_ENV* env, SPVM_VALUE* stack, void* block);
  int32_t (*get_memory_blocks_count)(SPVM_ENV* env, SPVM_VALUE* stack);
  void (*say)(SPVM_ENV* env, SPVM_VALUE* stack, void* string);
  void (*warn)(SPVM_ENV* env, SPVM_VALUE* stack, void* string, const char* func_name, const char* file, int32_t line);
  FILE* (*spvm_stdin)(SPVM_ENV* env, SPVM_VALUE* stack);
  FILE* (*spvm_stdout)(SPVM_ENV* env, SPVM_VALUE* stack);
  FILE* (*spvm_stderr)(SPVM_ENV* env, SPVM_VALUE* stack);
  void* (*new_array_proto_element_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* element, int32_t length);
  void* (*new_array_proto_element)(SPVM_ENV* env, SPVM_VALUE* stack, void* element, int32_t length);
  int32_t (*get_byte_object_value)(SPVM_ENV* env, SPVM_VALUE* stack, void* byte_object);
  int32_t (*get_short_object_value)(SPVM_ENV* env, SPVM_VALUE* stack, void* short_object);
  int32_t (*get_int_object_value)(SPVM_ENV* env, SPVM_VALUE* stack, void* int_object);
  int64_t (*get_long_object_value)(SPVM_ENV* env, SPVM_VALUE* stack, void* long_object);
  float (*get_float_object_value)(SPVM_ENV* env, SPVM_VALUE* stack, void* float_object);
  double (*get_double_object_value)(SPVM_ENV* env, SPVM_VALUE* stack, void* double_object);
  int32_t (*no_free)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void (*set_no_free)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t no_free);
  char* (*get_stack_tmp_buffer)(SPVM_ENV* env, SPVM_VALUE* stack);
  void (*print_exception_to_stderr)(SPVM_ENV* env, SPVM_VALUE* stack);
  void* (*dump_object_internal)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*get_seed)(SPVM_ENV* env, SPVM_VALUE* stack);
  void (*set_seed)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t seed);
  int32_t (*seed_initialized)(SPVM_ENV* env, SPVM_VALUE* stack);
  const char* (*get_basic_type_name_in_version_from)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type);
  int32_t (*set_command_info_warning)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t warning);
  void (*destroy_cache_class_vars)(SPVM_ENV* env, SPVM_VALUE* stack);
  SPVM_VALUE* (*new_stack_with_all_method_call_permitted)(SPVM_ENV* env);
  int32_t (*call_instance_method_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t args_width);
  int32_t (*call_instance_method)(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t args_width);
  int32_t (*call_method_no_mortal_no_check_args)(SPVM_ENV* env, SPVM_VALUE* stack, void* method, int32_t args_width, const char* func_name, const char* file_name, int32_t line);
  int32_t (*call_instance_method_no_mortal_less_check_args)(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t args_width, const char* decl_args_signature, const char* func_name, const char* file_name, int32_t line);
  void (*enable_options)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void (*disable_options)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*is_options)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*is_any_object_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*exists_field)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);
  int32_t (*exists_field_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*delete_field)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);
  void (*delete_field_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* object_data_offset;
  void* object_length_offset;
  void (*make_fixed_length)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*is_fixed_length)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void* object_capacity_offset;
  int32_t (*set_length)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t length);
  int32_t (*capacity)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*set_capacity)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t capacity);
  int8_t (*numeric_object_to_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t* error_id);
  int16_t (*numeric_object_to_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t* error_id);
  int32_t (*numeric_object_to_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t* error_id);
  int64_t (*numeric_object_to_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t* error_id);
  float (*numeric_object_to_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t* error_id);
  double (*numeric_object_to_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t* error_id);
  void* (*numeric_object_to_string_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t* error_id);
  void* (*numeric_object_to_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t* error_id);
  int32_t (*is_numeric_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void (*say_stderr)(SPVM_ENV* env, SPVM_VALUE* stack, void* string);
  void* stack_index_call_depth;
  void* stack_index_caller_info_stack;
  void* stack_index_caller_info_stack_record_size;
  int32_t (*get_call_depth)(SPVM_ENV* env, SPVM_VALUE* stack);
  void** (*get_caller_info_stack)(SPVM_ENV* env, SPVM_VALUE* stack);
  int32_t (*get_caller_info_stack_record_size)(SPVM_ENV* env, SPVM_VALUE* stack);
  void* (*get_current_method)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t level, int32_t* error_id);
  void* (*caller_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t level, int32_t* error_id);
  void* (*caller)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t level, int32_t* error_id);
  int32_t (*die_with_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* obj_exception, const char* func_name, const char* file, int32_t line);
  void* (*build_exception_message_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t level);
  void* (*build_exception_message)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t level);
  int32_t (*die_v2)(SPVM_ENV* env, SPVM_VALUE* stack, const char* exception_format, const char* func_name, const char* file, int32_t line, ...);
};

struct spvm_env_api {
  SPVM_API_ALLOCATOR* allocator;
  SPVM_API_STRING_BUFFER* string_buffer;
  SPVM_API_COMPILER* compiler;
  SPVM_API_CLASS_FILE* class_file;
  SPVM_API_RUNTIME* runtime;
  SPVM_API_BASIC_TYPE* basic_type;
  SPVM_API_CLASS_VAR* class_var;
  SPVM_API_FIELD* field;
  SPVM_API_METHOD* method;
  SPVM_API_ARG* arg;
  SPVM_API_TYPE* type;
  SPVM_API_INTERNAL* internal;
  SPVM_API_MUTEX* mutex;
};

struct spvm_api_allocator {
  void* (*new_instance)(void);
  void (*free_instance)(void* allocator);
};

struct spvm_api_arg {
  const char* (*get_name)(void* runtime, void* arg);
  int32_t (*get_index)(void* runtime, void* arg);
  void* (*get_basic_type)(void* runtime, void* arg);
  int32_t (*get_type_dimension)(void* runtime, void* arg);
  int32_t (*get_type_flag)(void* runtime, void* arg);
  int32_t (*get_stack_index)(void* runtime, void* arg);
  void* (*get_current_method)(void* runtime, void* arg);
  int32_t (*is_optional)(void* runtime, void* arg);
  SPVM_VALUE (*get_default_value)(void* runtime, void* arg);
};

struct spvm_api_basic_type {
  const char* (*get_name)(void* runtime, void* basic_type);
  int32_t (*get_id)(void* runtime, void* basic_type);
  int32_t (*get_category)(void* runtime, void* basic_type);
  void* (*get_parent)(void* runtime, void* basic_type);
  const char* (*get_version_string)(void* runtime, void* basic_type);
  const char* (*get_class_dir)(void* runtime, void* basic_type);
  const char* (*get_class_rel_file)(void* runtime, void* basic_type);
  int32_t (*is_pointer)(void* runtime, void* basic_type);
  int32_t (*is_anon)(void* runtime, void* basic_type);
  void* (*get_class_var_by_index)(void* runtime, void* basic_type, int32_t class_var_index);
  void* (*get_class_var_by_name)(void* runtime, void* basic_type, const char* class_var_name);
  int32_t (*get_class_vars_length)(void* runtime, void* basic_type);
  void* (*get_field_by_index)(void* runtime, void* basic_type, int32_t field_index);
  void* (*get_field_by_name)(void* runtime, void* basic_type, const char* field_name);
  int32_t (*get_fields_length)(void* runtime, void* basic_type);
  void* (*get_method_by_index)(void* runtime, void* basic_type, int32_t method_index);
  void* (*get_method_by_name)(void* runtime, void* basic_type, const char* method_name);
  int32_t (*get_methods_length)(void* runtime, void* basic_type);
  void* (*get_anon_basic_type_by_index)(void* runtime, void* basic_type, int32_t anon_basic_type_index);
  int32_t (*get_anon_basic_types_length)(void* runtime, void* basic_type);
  int32_t (*has_interface)(void* runtime, void* basic_type, void* interface_basic_type);
  int32_t (*is_super_class)(void* runtime, void* dist_basic_type, void* src_basic_type);
  const char* (*get_file)(void* runtime, void* basic_type);
  void* (*get_current_runtime)(void* runtime, void* basic_type);
  void* (*get_basic_type_in_version_from)(void* runtime, void* basic_type);
  int32_t (*get_fields_size)(void* runtime, void* basic_type);
};

struct spvm_api_class_file {
  const char* (*get_class_name)(void* compiler, void* class_file);
  const char* (*get_file)(void* compiler, void* class_file);
  void (*set_file)(void* compiler, void* class_file, const char* file);
  const char* (*get_dir)(void* compiler, void* class_file);
  void (*set_dir)(void* compiler, void* class_file, const char* dir);
  const char* (*get_rel_file)(void* compiler, void* class_file);
  void (*set_rel_file)(void* compiler, void* class_file, const char* rel_file);
  const char* (*get_content)(void* compiler, void* class_file);
  void (*set_content)(void* compiler, void* class_file, const char* content);
  int32_t (*get_content_length)(void* compiler, void* class_file);
  void (*set_content_length)(void* compiler, void* class_file, int32_t content_length);
};

struct spvm_api_class_var {
  const char* (*get_name)(void* runtime, void* class_var);
  int32_t (*get_index)(void* runtime, void* class_var);
  void* (*get_basic_type)(void* runtime, void* class_var);
  int32_t (*get_type_dimension)(void* runtime, void* class_var);
  int32_t (*get_type_flag)(void* runtime, void* class_var);
  void* (*get_current_basic_type)(void* runtime, void* class_var);
  int32_t (*is_cache)(void* runtime, void* class_var);
};

struct spvm_api_compiler {
  void* (*new_instance)(void);
  void (*free_instance)(void* compiler);
  int32_t (*get_start_line)(void* compiler);
  void (*set_start_line)(void* compiler, int32_t start_line);
  const char* (*get_start_file)(void* compiler);
  void (*set_start_file)(void* compiler, const char* start_file);
  int32_t (*get_include_dirs_length )(void* compiler);
  const char* (*get_include_dir )(void* compiler, int32_t index);
  void (*add_include_dir)(void* compiler, const char* include_dir);
  void (*clear_include_dirs)(void* compiler);
  void (*add_class_file)(void* compiler, const char* class_name);
  void (*delete_class_file)(void* compiler, const char* class_name);
  void* (*get_class_file)(void* compiler, const char* class_name);
  int32_t (*compile)(void* compiler, const char* basic_type_name);
  const char* (*get_error_message)(void* compiler, int32_t index);
  int32_t (*get_error_messages_length)(void* compiler);
  void* (*get_runtime)(void* compiler);
  void (*prepend_include_dir)(void* compiler, const char* include_dir);
  int32_t (*compile_anon_class)(void* compiler, const char* source, const char** anon_basic_type_name_ptr);
  int32_t (*compile_script)(void* compiler, const char* source, const char** anon_basic_type_name_ptr);
};

struct spvm_api_field {
  const char* (*get_name)(void* runtime, void* field);
  int32_t (*get_index)(void* runtime, void* field);
  int32_t (*get_offset)(void* runtime, void* field);
  void* (*get_basic_type)(void* runtime, void* field);
  int32_t (*get_type_dimension)(void* runtime, void* field);
  int32_t (*get_type_flag)(void* runtime, void* field);
  void* (*get_current_basic_type)(void* runtime, void* field);
  int32_t (*get_exists_offset)(void* runtime, void* field);
  int32_t (*get_exists_bit)(void* runtime, void* field);
};

struct spvm_api_method {
  const char* (*get_name)(void* runtime, void* method);
  int32_t (*get_index)(void* runtime, void* method);
  void* (*get_return_basic_type)(void* runtime, void* method);
  int32_t (*get_return_type_dimension)(void* runtime, void* method);
  int32_t (*get_return_type_flag)(void* runtime, void* method);
  void* (*get_arg_by_index)(void* runtime, void* method, int32_t arg_index);
  int32_t (*get_args_length)(void* runtime, void* method);
  int32_t (*get_required_args_length)(void* runtime, void* method);
  void* (*get_current_basic_type)(void* runtime, void* method);
  void* (*get_opcode_by_index)(void* runtime, void* method, int32_t opcode_index);
  int32_t (*get_opcodes_length)(void* runtime, void* method);
  int32_t (*is_class_method)(void* runtime, void* method);
  int32_t (*is_anon)(void* runtime, void* method);
  int32_t (*is_native)(void* runtime, void* method);
  int32_t (*is_precompile)(void* runtime, void* method);
  int32_t (*is_enum)(void* runtime, void* method);
  int32_t (*get_byte_vars_width)(void* runtime, void* method);
  int32_t (*get_short_vars_width)(void* runtime, void* method);
  int32_t (*get_int_vars_width)(void* runtime, void* method);
  int32_t (*get_long_vars_width)(void* runtime, void* method);
  int32_t (*get_float_vars_width)(void* runtime, void* method);
  int32_t (*get_double_vars_width)(void* runtime, void* method);
  int32_t (*get_object_vars_width)(void* runtime, void* method);
  int32_t (*get_ref_vars_width)(void* runtime, void* method);
  int32_t (*get_mortal_stack_length)(void* runtime, void* method);
  void* (*get_native_address)(void* runtime, void* method);
  void (*set_native_address)(void* runtime, void* method, void* address);
  void* (*get_precompile_address)(void* runtime, void* method);
  void (*set_precompile_address)(void* runtime, void* method, void* address);
  int32_t (*is_precompile_fallback)(void* runtime, void* method);
  void (*set_is_precompile_fallback)(void* runtime, void* method, int32_t is_precompile_fallback);
  int32_t (*is_not_permitted)(void* runtime, void* method);
  void (*set_is_not_permitted)(void* runtime, void* method, int32_t is_not_permitted);
  const char* (*get_args_signature)(void* runtime, void* method);
  const char* (*get_abs_name)(void* runtime, void* method);
};

struct spvm_api_runtime {
  int32_t (*get_object_data_offset)(void* runtime);
  int32_t (*get_object_ref_count_offset)(void* runtime);
  int32_t (*get_object_length_offset)(void* runtime);
  void* (*get_basic_type_by_id)(void* runtime, int32_t basic_type_id);
  void* (*get_basic_type_by_name)(void* runtime, const char* basic_type_name);
  int32_t (*get_basic_types_length)(void* runtime);
  void (*build_precompile_class_source)(void* runtime, void* string_buffer, void* module_basic_type);
  void (*build_precompile_method_source)(void* runtime, void* string_buffer, void* method);
  void* (*get_compiler)(void* runtime);
  void (*set_compiler)(void* runtime, void* compiler);
  FILE* (*get_spvm_stdin)(void* runtime);
  FILE* (*get_spvm_stdout)(void* runtime);
  FILE* (*get_spvm_stderr)(void* runtime);
  SPVM_ENV* (*get_env)(void* runtime);
  int32_t (*get_object_capacity_offset)(void* runtime);
};

struct spvm_api_internal {
  int32_t (*get_ref_count)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void (*inc_ref_count)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void (*dec_ref_count)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void (*removed3)(SPVM_ENV* env, SPVM_VALUE* stack, void** object_vars, int32_t* mortal_stack, int32_t* mortal_stack_top_ptr, int32_t original_mortal_stack_top);
  char* (*get_stack_tmp_buffer)(SPVM_ENV* env, SPVM_VALUE* stack);
  void (*leave_scope_local)(SPVM_ENV* env, SPVM_VALUE* stack, void** object_vars, int32_t* mortal_stack_typed_var_index, int32_t* mortal_stack_top_ptr, int32_t* mortal_stack_tops, int32_t mortal_stack_tops_index);
};

struct spvm_api_mutex {
  void* (*new_instance)(SPVM_ENV* env, SPVM_VALUE* stack);
  void (*free_instance)(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex);
  void (*lock)(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex);
  void (*unlock)(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex);
  void (*reader_lock)(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex);
  void (*reader_unlock)(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex);
};

struct spvm_api_string_buffer {
  void* (*new_instance)(void* allocator, int32_t capacity);
  void (*free_instance)(void* string_buffer);
  const char* (*get_string)(void* string_buffer);
  int32_t (*get_length)(void* string_buffer);
};

struct spvm_api_type {
  int32_t (*can_assign)(void* runtime, void* dist_basic_type, int32_t dist_type_dimension, int32_t dist_type_flag, void* src_basic_type, int32_t src_type_dimension, int32_t src_type_flag);
  int32_t (*get_type_width)(void* runtime, void* basic_type, int32_t type_dimension, int32_t type_flag);
  int32_t (*is_object_type)(void* runtime, void* basic_type, int32_t type_dimension, int32_t type_flag);
  int32_t (*is_any_object_type)(void* runtime, void* basic_type, int32_t type_dimension, int32_t type_flag);
  int32_t (*is_object_array_type)(void* runtime, void* basic_type, int32_t type_dimension, int32_t type_flag);
  int32_t (*is_any_object_array_type)(void* runtime, void* basic_type, int32_t type_dimension, int32_t type_flag);
  int32_t (*is_numeric_type)(void* runtime, void* basic_type, int32_t type_dimension, int32_t type_flag);
  int32_t (*is_class_type)(void* runtime, void* basic_type, int32_t type_dimension, int32_t type_flag);
};

enum {
  SPVM_NATIVE_C_BASIC_TYPE_ID_UNKNOWN,
  SPVM_NATIVE_C_BASIC_TYPE_ID_UNDEF,
  SPVM_NATIVE_C_BASIC_TYPE_ID_VOID,
  SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE,
  SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT,
  SPVM_NATIVE_C_BASIC_TYPE_ID_INT,
  SPVM_NATIVE_C_BASIC_TYPE_ID_LONG,
  SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT,
  SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE,
  SPVM_NATIVE_C_BASIC_TYPE_ID_STRING,
  SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT,
  SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_INT_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_BOOL_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_COMMAND_INFO_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_ADDRESS_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_COMPILE_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_SPVM_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_METHOD_CALL_NOT_PERMITTED_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_STRINGABLE_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_COUNTABLE_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_CALLER_INFO_CLASS,
};

enum {
  SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_UNKNOWN,
  SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_UNDEF,
  SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_VOID,
  SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC,
  SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM,
  SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING,
  SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE,
  SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT,
};

enum {
  SPVM_NATIVE_C_TYPE_FLAG_REF = 1,
  SPVM_NATIVE_C_TYPE_FLAG_MUTABLE = 2,
  SPVM_NATIVE_C_TYPE_FLAG_VARARGS = 4,
};

enum {
  SPVM_NATIVE_C_STACK_TMP_BUFFER_SIZE = 512,
};

// These functions are linked only by SPVM itself,
// so native classes cannot use these functions.
SPVM_ENV* SPVM_NATIVE_new_env(void);

#endif
