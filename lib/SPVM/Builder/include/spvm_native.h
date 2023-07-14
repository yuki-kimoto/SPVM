// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_NATIVE_H
#define SPVM_NATIVE_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define SPVM_NATIVE_VERSION_NUMBER 0.989023

#define SPVM_NATIVE_CREATE_VERSION_STRING_STRINGIFY(x) #x

#define SPVM_NATIVE_CREATE_VERSION_STRING(x) SPVM_NATIVE_CREATE_VERSION_STRING_STRINGIFY(x)

#define SPVM_NATIVE_VERSION_STRING SPVM_NATIVE_CREATE_VERSION_STRING(SPVM_NATIVE_VERSION_NUMBER);

#define spvm_warn(format, ...) fprintf(stderr, format "\n", ##__VA_ARGS__)

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

struct spvm_api_module_file;
typedef struct spvm_api_module_file SPVM_API_MODULE_FILE;

struct spvm_api_runtime;
typedef struct spvm_api_runtime SPVM_API_RUNTIME;

struct spvm_api_basic_type;
typedef struct spvm_api_basic_type SPVM_API_BASIC_TYPE;

struct spvm_api_class_var;
typedef struct spvm_api_class_var SPVM_API_CLASS_VAR;

struct spvm_api_field;
typedef struct spvm_api_field SPVM_API_FIELD;

struct spvm_api_method;
typedef struct spvm_api_method SPVM_API_METHOD;

struct spvm_api_arg;
typedef struct spvm_api_arg SPVM_API_ARG;

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
  int32_t (*set_command_info_base_time)(SPVM_ENV* env, SPVM_VALUE* stack, int64_t base_time);
  void (*destroy_class_vars)(SPVM_ENV* env, SPVM_VALUE* stack);
  int32_t (*items)(SPVM_ENV* env, SPVM_VALUE* stack);
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
  void** (*get_class_var_object_address)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);
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
  int32_t (*call_method_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* method, int32_t items);
  int32_t (*call_method)(SPVM_ENV* env, SPVM_VALUE* stack, void* method, int32_t items);
  void (*call_class_method_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name, int32_t items, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*call_instance_method_static_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name, int32_t items, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void (*call_instance_method_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t items, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* (*new_object_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type);
  void* (*new_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type);
  void* (*new_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* (*new_pointer_object_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, void* pointer);
  void* (*new_pointer_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, void* pointer);
  void* (*new_pointer_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, void* pointer, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* (*get_pointer)(SPVM_ENV* env, SPVM_VALUE* stack, void* pointer_object);
  void (*set_pointer)(SPVM_ENV* env, SPVM_VALUE* stack, void* pointer_object, void* pointer);
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
  void* (*new_muldim_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t element_dimension, int32_t length);
  void* (*new_muldim_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t element_dimension, int32_t length);
  void* (*new_muldim_array_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t element_dimension, int32_t length, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* (*new_mulnum_array_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t length);
  void* (*new_mulnum_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t length);
  void* (*new_mulnum_array_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t length, int32_t* error_id, const char* func_name, const char* file, int32_t line);
  void* (*new_array_proto_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t length);
  void* (*new_array_proto)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t length);
  int32_t (*length)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
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
  int32_t (*die)(SPVM_ENV* env, SPVM_VALUE* stack, const char* message, ...);
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
  void* (*get_compile_type_name_no_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t dimension, int32_t flag);
  void* (*get_compile_type_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t dimension, int32_t flag);
  int32_t (*enter_scope)(SPVM_ENV* env, SPVM_VALUE* stack);
  void (*leave_scope)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t scope_id);
  int32_t (*push_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*remove_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t scope_id, void* remove_object);
  int32_t (*weaken)(SPVM_ENV* env, SPVM_VALUE* stack, void** object_address);
  int32_t (*isweak)(SPVM_ENV* env, SPVM_VALUE* stack, void** object);
  void (*unweaken)(SPVM_ENV* env, SPVM_VALUE* stack, void** object_address);
  void* (*strerror_string)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length);
  void* (*strerror_string_nolen)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value);
  const char* (*strerror)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length);
  const char* (*strerror_nolen)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value);
  void* allocator;
  void* (*new_memory_env)(SPVM_ENV* env, size_t size);
  void (*free_memory_env)(SPVM_ENV* env, void* block);
  int32_t (*get_memory_blocks_count_env)(SPVM_ENV* env);
  void* (*new_memory_stack)(SPVM_ENV* env, SPVM_VALUE* stack, size_t size);
  void (*free_memory_stack)(SPVM_ENV* env, SPVM_VALUE* stack, void* block);
  int32_t (*get_memory_blocks_count_stack)(SPVM_ENV* env, SPVM_VALUE* stack);
  SPVM_VALUE* (*new_stack)(SPVM_ENV* env);
  void (*free_stack)(SPVM_ENV* env, SPVM_VALUE* stack);
  int32_t (*get_ref_count)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void (*inc_ref_count)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void (*dec_ref_count)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
};

struct spvm_env_api {
  SPVM_API_ALLOCATOR* allocator;
  SPVM_API_STRING_BUFFER* string_buffer;
  SPVM_API_COMPILER* compiler;
  SPVM_API_MODULE_FILE* module_file;
  SPVM_API_RUNTIME* runtime;
  SPVM_API_BASIC_TYPE* basic_type;
  SPVM_API_CLASS_VAR* class_var;
  SPVM_API_FIELD* field;
  SPVM_API_METHOD* method;
  SPVM_API_ARG* arg;
};

struct spvm_api_allocator {
  void* (*new_instance)(void);
  void (*free_instance)(void* allocator);
};

struct spvm_api_string_buffer {
  void* (*new_instance)(void* allocator, int32_t capacity);
  void (*free_instance)(void* string_buffer);
  const char* (*get_string)(void* string_buffer);
  int32_t (*get_length)(void* string_buffer);
};

struct spvm_api_compiler {
  void* (*new_instance)(void);
  void (*free_instance)(void* compiler);
  void (*set_start_line)(void* compiler, int32_t start_line);
  int32_t (*get_start_line)(void* compiler);
  void (*set_start_file)(void* compiler, const char* start_file);
  const char* (*get_start_file)(void* compiler);
  void (*add_include_dir)(void* compiler, const char* include_dir);
  int32_t (*get_include_dirs_length )(void* compiler);
  const char* (*get_include_dir )(void* compiler, int32_t index);
  int32_t (*compile)(void* compiler, const char* basic_type_name);
  int32_t (*get_error_messages_length)(void* compiler);
  const char* (*get_error_message)(void* compiler, int32_t index);
  void* reserved12;
  void (*clear_include_dirs)(void* compiler);
  void* (*get_module_file)(void* compiler, const char* module_name);
  void (*add_module_file)(void* compiler, const char* module_name, void* module_file);
  void* (*build_runtime)(void* compiler);
};

struct spvm_api_module_file {
  void* (*new_instance)(void* compiler);
  const char* (*get_module_name)(void* compiler, void* module_file);
  void (*set_module_name)(void* compiler, void* module_file, void* module_name);
  const char* (*get_file)(void* compiler, void* module_file);
  void (*set_file)(void* compiler, void* module_file, void* file);
  const char* (*get_dir)(void* compiler, void* module_file);
  void (*set_dir)(void* compiler, void* module_file, void* dir);
  const char* (*get_rel_file)(void* compiler, void* module_file);
  void (*set_rel_file)(void* compiler, void* module_file, void* rel_file);
  const char* (*get_content)(void* compiler, void* module_file);
  void (*set_content)(void* compiler, void* module_file, void* content);
  int32_t (*get_content_length)(void* compiler, void* module_file);
  void (*set_content_length)(void* compiler, void* module_file, int32_t content_length);
};

struct spvm_api_runtime {
  int32_t (*get_object_data_offset)(void* runtime);
  int32_t (*get_object_ref_count_offset)(void* runtime);
  int32_t (*get_object_length_offset)(void* runtime);
  void* (*get_basic_type_by_id)(void* runtime, int32_t basic_type_id);
  void* (*get_basic_type_by_name)(void* runtime, const char* basic_type_name);
  int32_t (*get_basic_types_length)(void* runtime);
  int32_t (*is_object_type)(void* runtime, void* basic_type, int32_t type_dimension, int32_t flag);
  int32_t (*can_assign)(void* runtime, void* dist_basic_type, int32_t dist_type_dimension, int32_t dist_type_flag, void* src_basic_type, int32_t src_type_dimension, int32_t src_type_flag);
  void (*build_precompile_module_source)(void* runtime, void* string_buffer, void* module_basic_type);
  void (*build_precompile_method_source)(void* runtime, void* string_buffer, void* method);
};

struct spvm_api_basic_type {
  const void* (*get_name)(void* runtime, void* basic_type);
  int32_t (*get_id)(void* runtime, void* basic_type);
  int32_t (*get_category)(void* runtime, void* basic_type);
  void* (*get_parent)(void* runtime, void* basic_type);
  const void* (*get_version_string)(void* runtime, void* basic_type);
  const void* (*get_module_dir)(void* runtime, void* basic_type);
  const void* (*get_module_rel_file)(void* runtime, void* basic_type);
  int32_t (*is_pointer)(void* runtime, void* basic_type);
  int32_t (*is_anon)(void* runtime, void* basic_type);
  void* (*get_class_var_by_index)(void* runtime, void* basic_type, int32_t class_var_index);
  void* (*get_class_var_by_name)(void* runtime, void* basic_type, const void* class_var_name);
  int32_t (*get_class_vars_length)(void* runtime, void* basic_type);
  void* (*get_field_by_index)(void* runtime, void* basic_type, int32_t field_index);
  void* (*get_field_by_name)(void* runtime, void* basic_type, const void* field_name);
  int32_t (*get_fields_length)(void* runtime, void* basic_type);
  void* (*get_method_by_index)(void* runtime, void* basic_type, int32_t method_index);
  void* (*get_method_by_name)(void* runtime, void* basic_type, const void* method_name);
  int32_t (*get_methods_length)(void* runtime, void* basic_type);
  void* (*get_anon_basic_type_by_index)(void* runtime, void* basic_type, int32_t anon_basic_type_index);
  int32_t (*get_anon_basic_types_length)(void* runtime, void* basic_type);
  int32_t (*has_interface)(void* runtime, void* basic_type, void* interface_basic_type);
  int32_t (*is_super_class)(void* runtime, void* super_basic_type, void* child_basic_type);
};

struct spvm_api_class_var {
  const char* (*get_name)(void* runtime, void* class_var);
  void* (*get_basic_type)(void* runtime, void* class_var);
  int32_t (*get_type_dimension)(void* runtime, void* class_var);
  int32_t (*get_type_flag)(void* runtime, void* class_var);
  void* (*get_current_basic_type)(void* runtime, void* class_var);
};

struct spvm_api_field {
  const char* (*get_name)(void* runtime, void* field);
  int32_t (*get_index)(void* runtime, void* field);
  int32_t (*get_offset)(void* runtime, void* field);
  void* (*get_basic_type)(void* runtime, void* field);
  int32_t (*get_type_dimension)(void* runtime, void* field);
  int32_t (*get_type_flag)(void* runtime, void* field);
  void* (*get_current_basic_type)(void* runtime, void* field);
};

struct spvm_api_method {
  const void* (*get_name)(void* runtime, void* method);
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
};

struct spvm_api_arg {
  void* (*get_basic_type)(void* runtime, void* arg);
  int32_t (*get_type_dimension)(void* runtime, void* arg);
  int32_t (*get_type_flag)(void* runtime, void* arg);
};

SPVM_ENV* SPVM_API_new_env(void);

void SPVM_API_free_env(SPVM_ENV* env);

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
};

#endif
