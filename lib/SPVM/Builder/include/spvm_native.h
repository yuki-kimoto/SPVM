// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_NATIVE_H
#define SPVM_NATIVE_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define SPVM_NATIVE_VERSION_NUMBER 0.989016

#define SPVM_NATIVE_CREATE_VERSION_STRING_STRINGIFY(x) #x

#define SPVM_NATIVE_CREATE_VERSION_STRING(x) SPVM_NATIVE_CREATE_VERSION_STRING_STRINGIFY(x)

#define SPVM_NATIVE_VERSION_STRING SPVM_NATIVE_CREATE_VERSION_STRING(SPVM_NATIVE_VERSION_NUMBER);

struct spvm_env;
typedef struct spvm_env SPVM_ENV;

struct spvm_env_api;
typedef struct spvm_env_api SPVM_ENV_API;

struct spvm_env_compiler;
typedef struct spvm_env_compiler SPVM_ENV_COMPILER;

struct spvm_env_runtime;
typedef struct spvm_env_runtime SPVM_ENV_RUNTIME;

struct spvm_env_precompile;
typedef struct spvm_env_precompile SPVM_ENV_PRECOMPILE;

struct spvm_env_string_buffer;
typedef struct spvm_env_string_buffer SPVM_ENV_STRING_BUFFER;

struct spvm_env_allocator;
typedef struct spvm_env_allocator SPVM_ENV_ALLOCATOR;

typedef union spvm_value SPVM_VALUE;

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
  void* reserved0;
  void* reserved1;
  void* reserved2;
  void* reserved3;
  void* reserved4;
  void* reserved5;
  void* reserved6;
  void* reserved7;
  SPVM_ENV_API* api;
  void* allocator;
  SPVM_ENV* (*new_env_raw)();
  void (*free_env_raw)(SPVM_ENV* env);
  int32_t (*isa)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* basic_type, int32_t type_dimension);
  int32_t (*elem_isa)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, void* element);
  void* runtime;
  int32_t (*get_basic_type_id)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name);
  void* (*get_field)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name);
  void* reserved17;
  void* (*get_class_var)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name);
  void* (*get_class_method)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name);
  void* (*get_instance_method)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* method_name);
  void* (*new_object_raw)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type);
  void* (*new_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type);
  void* (*new_byte_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_byte_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_short_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_short_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_int_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_int_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_long_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_long_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_float_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_float_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_double_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_double_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* (*new_object_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t length);
  void* (*new_object_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t length);
  void* (*new_muldim_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t element_dimension, int32_t length);
  void* (*new_muldim_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t element_dimension, int32_t length);
  void* (*new_mulnum_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t length);
  void* (*new_mulnum_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, int32_t length);
  void* (*new_string_nolen_raw)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes);
  void* (*new_string_nolen)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes);
  void* (*new_string_raw)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length);
  void* (*new_string)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length);
  void* (*concat_raw)(SPVM_ENV* env, SPVM_VALUE* stack, void* string1, void* string2);
  void* (*concat)(SPVM_ENV* env, SPVM_VALUE* stack, void* string1, void* string2);
  void* (*new_stack_trace_raw)(SPVM_ENV* env, SPVM_VALUE* stack, void* exception, void* method, int32_t line);
  void* (*new_stack_trace)(SPVM_ENV* env, SPVM_VALUE* stack, void* exception, void* method, int32_t line);
  int32_t (*length)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  int8_t* (*get_elems_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  int16_t* (*get_elems_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  int32_t* (*get_elems_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  int64_t* (*get_elems_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  float* (*get_elems_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  double* (*get_elems_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  void* (*get_elem_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index);
  void (*set_elem_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, void* object);
  int8_t (*get_field_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);
  int16_t (*get_field_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);
  int32_t (*get_field_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);
  int64_t (*get_field_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);
  float (*get_field_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);
  double (*get_field_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);
  void* (*get_field_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field);
  void (*set_field_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, int8_t value);
  void (*set_field_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, int16_t value);
  void (*set_field_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, int32_t value);
  void (*set_field_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, int64_t value);
  void (*set_field_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, float value);
  void (*set_field_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, double value);
  void (*set_field_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* field, void* value);
  int8_t (*get_class_var_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);
  int16_t (*get_class_var_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);
  int32_t (*get_class_var_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);
  int64_t (*get_class_var_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);
  float (*get_class_var_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);
  double (*get_class_var_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);
  void* (*get_class_var_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);
  void (*set_class_var_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, int8_t value);
  void (*set_class_var_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, int16_t value);
  void (*set_class_var_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, int32_t value);
  void (*set_class_var_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, int64_t value);
  void (*set_class_var_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, float value);
  void (*set_class_var_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, double value);
  void (*set_class_var_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var, void* value);
  void* (*get_pointer)(SPVM_ENV* env, SPVM_VALUE* stack, void* pointer_object);
  void (*set_pointer)(SPVM_ENV* env, SPVM_VALUE* stack, void* pointer_object, void* pointer);
  int32_t (*call_method_raw)(SPVM_ENV* env, SPVM_VALUE* stack, void* method, int32_t items);
  void* (*get_exception)(SPVM_ENV* env, SPVM_VALUE* stack);
  int32_t (*set_exception)(SPVM_ENV* env, SPVM_VALUE* stack, void* exception);
  int32_t (*get_ref_count)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void (*inc_ref_count)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void (*dec_ref_count)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*enter_scope)(SPVM_ENV* env, SPVM_VALUE* stack);
  int32_t (*push_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void (*leave_scope)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t scope_id);
  int32_t (*remove_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t scope_id, void* remove_object);
  int32_t (*is_type)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, void* basic_type, int32_t type_dimension);
  int32_t (*is_object_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*get_object_basic_type_id)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*get_object_type_dimension)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*weaken)(SPVM_ENV* env, SPVM_VALUE* stack, void** object_address);
  int32_t (*isweak)(SPVM_ENV* env, SPVM_VALUE* stack, void** object);
  void (*unweaken)(SPVM_ENV* env, SPVM_VALUE* stack, void** object_address);
  void* (*alloc_memory_block_zero)(SPVM_ENV* env, size_t size);
  void (*free_memory_block)(SPVM_ENV* env, void* block);
  int32_t (*get_memory_blocks_count)(SPVM_ENV* env);
  void* (*get_type_name_raw)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void* (*get_type_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  SPVM_ENV* (*new_env)(SPVM_ENV* env);
  void (*free_env)(SPVM_ENV* env);
  void* memory_blocks_count;
  const char* (*get_chars)(SPVM_ENV* env, SPVM_VALUE* stack, void* string_object);
  int32_t (*die)(SPVM_ENV* env, SPVM_VALUE* stack, const char* message, ...);
  void* (*new_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_field_byte_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int8_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_field_short_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int16_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_field_int_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_field_long_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int64_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_field_float_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, float value, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_field_double_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, double value, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_field_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, void* value, int32_t* error, const char* func_name, const char* file, int32_t line);
  int8_t (*get_field_byte_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  int16_t (*get_field_short_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  int32_t (*get_field_int_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  int64_t (*get_field_long_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  float (*get_field_float_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  double (*get_field_double_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  void* (*get_field_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_byte_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int8_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_short_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int16_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_int_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_long_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int64_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_float_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, float value, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_double_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, double value, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, void* value, int32_t* error, const char* func_name, const char* file, int32_t line);
  int8_t (*get_class_var_byte_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  int16_t (*get_class_var_short_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  int32_t (*get_class_var_int_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  int64_t (*get_class_var_long_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  float (*get_class_var_float_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  double (*get_class_var_double_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  void* (*get_class_var_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*call_class_method_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name, int32_t items, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*call_instance_method_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t items, int32_t* error, const char* func_name, const char* file, int32_t line);
  const char* (*get_field_string_chars_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*free_env_prepared)(SPVM_ENV* env);
  void* (*dump_raw)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void* (*dump)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void* (*get_instance_method_static)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name);
  int32_t (*get_bool_object_value)(SPVM_ENV* env, SPVM_VALUE* stack, void* bool_object);
  void (*cleanup_global_vars)(SPVM_ENV* env, SPVM_VALUE* stack);
  void (*make_read_only)(SPVM_ENV* env, SPVM_VALUE* stack, void* string);
  int32_t (*is_read_only)(SPVM_ENV* env, SPVM_VALUE* stack, void* string);
  int32_t (*is_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*is_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*is_numeric_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*is_mulnum_array)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*get_elem_size)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  void* (*new_array_proto_raw)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t length);
  void* (*new_array_proto)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t length);
  void* (*copy_raw)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void* (*copy)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void (*shorten)(SPVM_ENV* env, SPVM_VALUE* stack, void* string, int32_t new_length);
  int32_t (*has_interface)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t interface_basic_type_id);
  void (*print)(SPVM_ENV* env, SPVM_VALUE* stack, void* string);
  void (*print_stderr)(SPVM_ENV* env, SPVM_VALUE* stack, void* string);
  int32_t (*init_env)(SPVM_ENV* env);
  int32_t (*call_init_blocks)(SPVM_ENV* env, SPVM_VALUE* stack);
  void* reserved170;
  SPVM_VALUE* (*new_stack)(SPVM_ENV* env);
  void (*free_stack)(SPVM_ENV* env, SPVM_VALUE* stack);
  void* (*new_memory_env)(SPVM_ENV* env, size_t size);
  void (*free_memory_env)(SPVM_ENV* env, void* block);
  int32_t (*get_memory_blocks_count_env)(SPVM_ENV* env);
  void* (*new_memory_stack)(SPVM_ENV* env, SPVM_VALUE* stack, size_t size);
  void (*free_memory_stack)(SPVM_ENV* env, SPVM_VALUE* stack, void* block);
  int32_t (*get_memory_blocks_count_stack)(SPVM_ENV* env, SPVM_VALUE* stack);
  int32_t (*set_command_info_program_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* obj_program_name);
  int32_t (*set_command_info_argv)(SPVM_ENV* env, SPVM_VALUE* stack, void* obj_argv);
  void* reserved181;
  const char* (*strerror)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length);
  void* (*new_string_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  void* reserved184;
  void* reserved185;
  const char* (*dumpc)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void* (*new_pointer_object_raw)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, void* pointer);
  void* (*new_pointer_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* basic_type, void* pointer);
  void* (*new_pointer_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, void* pointer, int32_t* error, const char* func_name, const char* file, int32_t line);
  void* (*get_elem_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index);
  void (*set_elem_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, void* string);
  int32_t (*is_class)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*is_pointer_class)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void* (*strerror_string)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length);
  int32_t (*get_basic_type_id_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  void* (*get_field_static)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* field_name);
  int32_t (*items)(SPVM_ENV* env, SPVM_VALUE* stack);
  void (*call_instance_method_static_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name, int32_t items, int32_t* error, const char* func_name, const char* file, int32_t line);
  void* (*get_method)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name);
  const char* (*strerror_nolen)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value);
  void* (*strerror_string_nolen)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value);
  void* (*get_compile_type_name_raw)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t dimension, int32_t flag);
  void* (*get_compile_type_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t dimension, int32_t flag);
  int32_t (*set_command_info_base_time)(SPVM_ENV* env, SPVM_VALUE* stack, int64_t base_time);
  const char* (*get_spvm_version_string)(SPVM_ENV* env, SPVM_VALUE* stack);
  double (*get_spvm_version_number)(SPVM_ENV* env, SPVM_VALUE* stack);
  const char* (*get_version_string)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id);
  double (*get_version_number)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id);
  int32_t (*call_method)(SPVM_ENV* env, SPVM_VALUE* stack, void* method, int32_t items);
  void* reserved210;
  const char* (*get_object_basic_type_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*isa_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* basic_type_name, int32_t type_dimension);
  int32_t (*is_type_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* basic_type_name, int32_t type_dimension);
  void* (*new_object_array_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t length, int32_t* error, const char* func_name, const char* file, int32_t line);
  void* (*new_muldim_array_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t element_dimension, int32_t length, int32_t* error, const char* func_name, const char* file, int32_t line);
  void* (*new_mulnum_array_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t length, int32_t* error, const char* func_name, const char* file, int32_t line);
  int32_t (*has_interface_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* basic_type_name);
  void** (*get_class_var_object_address)(SPVM_ENV* env, SPVM_VALUE* stack, void* class_var);
  void* (*get_basic_type)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name);
  void* (*get_basic_type_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error, const char* func_name, const char* file, int32_t line);
};

struct spvm_env_runtime {
  void* (*new_object)();
  void (*free_object)(void* runtime);
  int32_t* (*get_opcodes)(void* runtime);
  void* reserved3;
  int32_t* (*get_runtime_codes)(void* runtime);
  int32_t (*get_runtime_codes_length)(void* runtime);
  void* reserved6;
  void* reserved7;
  void* reserved8;
  void* reserved9;
  int32_t (*get_basic_type_id_by_name)(void* runtime, const char* basic_type_name);
  const char* (*get_basic_type_name)(void* runtime, int32_t basic_type_id);
  void* reserved12;
  int32_t (*get_basic_type_category)(void* runtime, int32_t basic_type_id);
  void* reserved14;
  void* reserved15;
  void* reserved16;
  void* reserved17;
  void* reserved18;
  void* reserved19;
  void* reserved20;
  void* reserved21;
  void* reserved22;
  void* reserved23;
  void* reserved24;
  void* reserved25;
  void* reserved26;
  void* reserved27;
  void* reserved28;
  void* reserved29;
  void* reserved30;
  void* reserved31;
  void* (*get_class_var)(void* runtime, int32_t basic_type_id, int32_t class_var_index);
  void* reserved33;
  const char* (*get_class_var_name)(void* runtime, void* class_var);
  void* reserved35;
  void* reserved36;
  void* reserved37;
  const char* (*get_field_name)(void* runtime, void* field);
  void* reserved39;
  void* reserved40;
  void* reserved41;
  void* reserved42;
  const char* (*get_method_name)(void* runtime, void* method);
  void* reserved44;
  void* reserved45;
  int32_t (*get_method_is_class_method)(void* runtime, void* method);
  int32_t (*get_method_is_anon)(void* runtime, void* method);
  int32_t (*get_method_is_native)(void* runtime, void* method);
  int32_t (*get_method_is_precompile)(void* runtime, void* method);
  int32_t (*get_method_call_stack_byte_vars_length)(void* runtime, void* method);
  int32_t (*get_method_call_stack_short_vars_length)(void* runtime, void* method);
  int32_t (*get_method_call_stack_int_vars_length)(void* runtime, void* method);
  int32_t (*get_method_call_stack_long_vars_length)(void* runtime, void* method);
  int32_t (*get_method_call_stack_float_vars_length)(void* runtime, void* method);
  int32_t (*get_method_call_stack_double_vars_length)(void* runtime, void* method);
  int32_t (*get_method_call_stack_object_vars_length)(void* runtime, void* method);
  int32_t (*get_method_call_stack_ref_vars_length)(void* runtime, void* method);
  int32_t (*get_method_mortal_stack_length)(void* runtime, void* method);
  int32_t (*get_method_opcodes_base)(void* runtime, void* method);
  int32_t (*get_method_opcodes_length)(void* runtime, void* method);
  int32_t (*get_method_args_base)(void* runtime, void* method);
  int32_t (*get_method_args_length)(void* runtime, void* method);
  void* reserved63;
  void* reserved64;
  void* (*get_native_method_address)(void* runtime, void* method);
  void (*set_native_method_address)(void* runtime, void* method, void* address);
  void* (*get_precompile_method_address)(SPVM_ENV*, void* method);
  void (*set_precompile_method_address)(void* runtime, void* method, void* address);
  void* object_header_size;
  void* reserved70;
  void* object_ref_count_offset;
  void* reserved72;
  void* reserved73;
  void* reserved74;
  void* object_length_offset;
  void* (*get_allocator)(void* runtime);
  void (*build)(void* runtime, int32_t* runtime_codes);
  void* reserved78;
  int32_t (*get_method_required_args_length)(void* runtime, void* method);
  void* reserved80;
  int32_t (*get_method_is_enum)(void* runtime, void* method);
  void* reserved82;
  int32_t (*is_object_type)(void* runtime, void* basic_type, int32_t type_dimension, int32_t flag);
  void* reserved84;
  void* reserved85;
  int32_t (*can_assign)(void* runtime, void* dist_basic_type, int32_t dist_type_dimension, int32_t dist_type_flag, void* src_basic_type, int32_t src_type_dimension, int32_t src_type_flag);
  const char* (*get_basic_type_module_rel_file)(void* runtime, int32_t basic_type_id);
  const char* (*get_basic_type_module_dir)(void* runtime, int32_t basic_type_id);
  int32_t (*get_basic_type_is_anon)(void* runtime, int32_t basic_type_id);
  int32_t (*get_basic_type_fields_base)(void* runtime, int32_t basic_type_id);
  int32_t (*get_basic_type_fields_length)(void* runtime, int32_t basic_type_id);
  int32_t (*get_basic_type_methods_base)(void* runtime, int32_t basic_type_id);
  int32_t (*get_basic_type_methods_length)(void* runtime, int32_t basic_type_id);
  int32_t (*get_basic_type_class_vars_base)(void* runtime, int32_t basic_type_id);
  int32_t (*get_basic_type_class_vars_length)(void* runtime, int32_t basic_type_id);
  void* reserved96;
  void* reserved97;
  void* reserved98;
  int32_t (*get_basic_types_length)(void* runtime);
  void* (*get_field_basic_type)(void* runtime, void* field);
  int32_t (*get_field_type_dimension)(void* runtime, void* field);
  int32_t (*get_field_type_flag)(void* runtime, void* field);
  void* (*get_class_var_basic_type)(void* runtime, void* class_var);
  int32_t (*get_class_var_type_dimension)(void* runtime, void* class_var);
  int32_t (*get_class_var_type_flag)(void* runtime, void* class_var);
  void* (*get_method_return_basic_type)(void* runtime, void* method);
  int32_t (*get_method_return_type_dimension)(void* runtime, void* method);
  int32_t (*get_method_return_type_flag)(void* runtime, void* method);
  void* (*get_arg_basic_type)(void* runtime, void* arg);
  int32_t (*get_arg_type_dimension)(void* runtime, void* arg);
  int32_t (*get_arg_type_flag)(void* runtime, void* arg);
  void* (*get_method_current_basic_type)(void* runtime, void* method);
  void* (*get_field_current_basic_type)(void* runtime, void* field);
  void* (*get_class_var_current_basic_type)(void* runtime, void* class_var);
  int32_t (*get_basic_type_parent_id)(void* runtime, int32_t basic_type_id);
  const char* (*get_basic_type_version_string)(void* runtime, int32_t basic_type_id);
  void* (*get_basic_type)(void* runtime, int32_t basic_type_id);
  void* (*get_field)(void* runtime, void* basic_type, int32_t field_index);
  void* (*get_method)(void* runtime, void* basic_type, int32_t method_index);
  void* reserved120;
  void* reserved121;
  void* (*get_class_var_by_name)(void* runtime, void* basic_type, const char* class_var_name);
  void* (*get_field_by_name)(void* runtime, void* basic_type, const char* field_name);
  void* (*get_method_by_name)(void* runtime, void* basic_type, const char* method_name);
  int32_t (*get_basic_type_id)(void* runtime, void* basic_type);
  void* reserved126;
  int32_t (*get_method_index)(void* runtime, void* method);
  void* reserved128;
  int32_t (*get_class_var_index)(void* runtime, void* class_var);
  int32_t (*get_field_index)(void* runtime, void* field);
  int32_t (*get_field_offset)(void* runtime, void* field);
  void* (*get_arg)(void* runtime, void* method, int32_t arg_index);
  void* (*get_basic_type_by_name)(void* runtime, const char* basic_type_name);
  const char* (*get_basic_type_name_v2)(void* runtime, void* basic_type);
  int32_t (*get_basic_type_category_v2)(void* runtime, void* basic_type);
  const char* (*get_basic_type_module_rel_file_v2)(void* runtime, void* basic_type);
  const char* (*get_basic_type_module_dir_v2)(void* runtime, void* basic_type);
  int32_t (*get_basic_type_is_anon_v2)(void* runtime, void* basic_type);
  int32_t (*get_basic_type_fields_base_v2)(void* runtime, void* basic_type);
  int32_t (*get_basic_type_fields_length_v2)(void* runtime, void* basic_type);
  int32_t (*get_basic_type_methods_base_v2)(void* runtime, void* basic_type);
  int32_t (*get_basic_type_methods_length_v2)(void* runtime, void* basic_type);
  int32_t (*get_basic_type_class_vars_base_v2)(void* runtime, void* basic_type);
  int32_t (*get_basic_type_class_vars_length_v2)(void* runtime, void* basic_type);
  void* (*get_basic_type_parent)(void* runtime, void* basic_type);
  const char* (*get_basic_type_version_string_v2)(void* runtime, void* basic_type);
  void* (*get_basic_type_anon_basic_type)(void* runtime, void* basic_type, int32_t anon_basic_type_index);
  void* (*get_class_var_v2)(void* runtime, void* basic_type, int32_t class_var_index);
};

struct spvm_env_compiler {
  void* (*new_object)();
  void (*free_object)(void* compiler);
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
  int32_t* (*create_runtime_codes)(void* compiler, void* allocator);
  void (*clear_include_dirs)(void* compiler);
};

struct spvm_env_precompile {
  void* (*new_object)();
  void (*free_object)(void* precompile);
  void (*set_runtime)(void* precompile, void* runtime);
  void* (*get_runtime)(void* precompile);
  void (*build_source)(void* precompile, void* string_buffer, const char* basic_type_name);
  void (*build_method_source)(void* precompile, void* string_buffer, const char* basic_type_name, const char* method_name);
};

SPVM_ENV* SPVM_NATIVE_new_env_raw();
SPVM_ENV* SPVM_NATIVE_new_env_prepared();

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

struct spvm_env_allocator {
  void* (*new_object)();
  void (*free_object)(void* allocator);
};

struct spvm_env_string_buffer {
  void* (*new_object)();
  void (*free_object)(void* string_buffer);
  const char* (*get_value)(void* string_buffer);
  int32_t (*get_length)(void* string_buffer);
};

struct spvm_env_api {
  SPVM_ENV_ALLOCATOR* allocator;
  SPVM_ENV_STRING_BUFFER* string_buffer;
  SPVM_ENV_COMPILER* compiler;
  SPVM_ENV_PRECOMPILE* precompile;
  SPVM_ENV_RUNTIME* runtime;
};

#define spvm_warn(format, ...) fprintf(stderr, format "\n", ##__VA_ARGS__)

#endif
