// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_NATIVE_H
#define SPVM_NATIVE_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

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
  void* class_vars_heap;
  void* object_header_size;
  void* object_weaken_backref_head_offset;
  void* object_ref_count_offset;
  void* object_basic_type_id_offset;
  void* object_type_dimension_offset;
  void* object_flag_offset;
  void* object_length_offset;
  SPVM_ENV_API* api;
  void* allocator;
  SPVM_ENV* (*new_env_raw)();
  void (*free_env_raw)(SPVM_ENV* env);
  int32_t (*isa)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t cast_basic_type_id, int32_t cast_type_dimension);
  int32_t (*elem_isa)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, void* element);
  void* runtime;
  int32_t (*get_basic_type_id)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name);
  int32_t (*get_field_id)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name);
  int32_t (*get_field_offset)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t field_id);
  int32_t (*get_class_var_id)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name);
  int32_t (*get_class_method_id)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* method_name);
  int32_t (*get_instance_method_id)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* method_name);
  void* (*new_object_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id);
  void* (*new_object)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id);
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
  void* (*new_object_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length);
  void* (*new_object_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length);
  void* (*new_muldim_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t element_dimension, int32_t length);
  void* (*new_muldim_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t element_dimension, int32_t length);
  void* (*new_mulnum_array_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length);
  void* (*new_mulnum_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length);
  void* (*new_string_nolen_raw)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes);
  void* (*new_string_nolen)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes);
  void* (*new_string_raw)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length);
  void* (*new_string)(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length);
  void* (*concat_raw)(SPVM_ENV* env, SPVM_VALUE* stack, void* string1, void* string2);
  void* (*concat)(SPVM_ENV* env, SPVM_VALUE* stack, void* string1, void* string2);
  void* (*new_stack_trace_raw)(SPVM_ENV* env, SPVM_VALUE* stack, void* exception, int32_t method_id, int32_t line);
  void* (*new_stack_trace)(SPVM_ENV* env, SPVM_VALUE* stack, void* exception, int32_t method_id, int32_t line);
  int32_t (*length)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  int8_t* (*get_elems_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  int16_t* (*get_elems_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  int32_t* (*get_elems_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  int64_t* (*get_elems_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  float* (*get_elems_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  double* (*get_elems_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* array);
  void* (*get_elem_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index);
  void (*set_elem_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, void* object);
  int8_t (*get_field_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id);
  int16_t (*get_field_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id);
  int32_t (*get_field_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id);
  int64_t (*get_field_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id);
  float (*get_field_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id);
  double (*get_field_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id);
  void* (*get_field_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id);
  void (*set_field_byte)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int8_t value);
  void (*set_field_short)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int16_t value);
  void (*set_field_int)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int32_t value);
  void (*set_field_long)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, int64_t value);
  void (*set_field_float)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, float value);
  void (*set_field_double)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, double value);
  void (*set_field_object)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t field_id, void* value);
  int8_t (*get_class_var_byte)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t pkgvar_id);
  int16_t (*get_class_var_short)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t pkgvar_id);
  int32_t (*get_class_var_int)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t pkgvar_id);
  int64_t (*get_class_var_long)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t pkgvar_id);
  float (*get_class_var_float)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t pkgvar_id);
  double (*get_class_var_double)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t pkgvar_id);
  void* (*get_class_var_object)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t pkgvar_id);
  void (*set_class_var_byte)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t pkgvar_id, int8_t value);
  void (*set_class_var_short)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t pkgvar_id, int16_t value);
  void (*set_class_var_int)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t pkgvar_id, int32_t value);
  void (*set_class_var_long)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t pkgvar_id, int64_t value);
  void (*set_class_var_float)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t pkgvar_id, float value);
  void (*set_class_var_double)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t pkgvar_id, double value);
  void (*set_class_var_object)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t pkgvar_id, void* value);
  void* (*get_pointer)(SPVM_ENV* env, SPVM_VALUE* stack, void* pointer_object);
  void (*set_pointer)(SPVM_ENV* env, SPVM_VALUE* stack, void* pointer_object, void* pointer);
  int32_t (*call_method)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t method_id, int32_t args_stack_length);
  void* (*get_exception)(SPVM_ENV* env, SPVM_VALUE* stack);
  int32_t (*set_exception)(SPVM_ENV* env, SPVM_VALUE* stack, void* exception);
  int32_t (*get_ref_count)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void (*inc_ref_count)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void (*dec_ref_count)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*enter_scope)(SPVM_ENV* env, SPVM_VALUE* stack);
  int32_t (*push_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void (*leave_scope)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t scope_id);
  int32_t (*remove_mortal)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t scope_id, void* remove_object);
  int32_t (*is_type)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, int32_t basic_type_id, int32_t type_dimension);
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
  void* (*new_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, int32_t* error, const char* func_name, const char* file, int32_t line);
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
  void (*set_class_var_byte_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int8_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_short_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int16_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_int_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_long_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int64_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_float_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, float value, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_double_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, double value, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*set_class_var_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, void* value, int32_t* error, const char* func_name, const char* file, int32_t line);
  int8_t (*get_class_var_byte_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  int16_t (*get_class_var_short_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  int32_t (*get_class_var_int_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  int64_t (*get_class_var_long_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  float (*get_class_var_float_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  double (*get_class_var_double_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  void* (*get_class_var_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  int32_t (*call_class_method_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* method_name, int32_t args_stack_length, const char* func_name, const char* file, int32_t line);
  int32_t (*call_instance_method_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t args_stack_length, const char* func_name, const char* file, int32_t line);
  const char* (*get_field_string_chars_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  void (*free_env_prepared)(SPVM_ENV* env);
  void* (*dump_raw)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void* (*dump)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*get_instance_method_id_static)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* method_name);
  int32_t (*get_bool_object_value)(SPVM_ENV* env, SPVM_VALUE* stack, void* bool_object);
  void (*cleanup_global_vars)(SPVM_ENV* env);
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
  void (*call_init_blocks)(SPVM_ENV* env);
  int32_t (*get_class_id)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name);
  SPVM_VALUE* (*new_stack)(SPVM_ENV* env);
  void (*free_stack)(SPVM_ENV* env, SPVM_VALUE* stack);
  void* (*new_memory_env)(SPVM_ENV* env, size_t size);
  void (*free_memory_env)(SPVM_ENV* env, void* block);
  int32_t (*get_memory_blocks_count_env)(SPVM_ENV* env);
  void* (*new_memory_stack)(SPVM_ENV* env, SPVM_VALUE* stack, size_t size);
  void (*free_memory_stack)(SPVM_ENV* env, SPVM_VALUE* stack, void* block);
  int32_t (*get_memory_blocks_count_stack)(SPVM_ENV* env, SPVM_VALUE* stack);
  int32_t (*set_command_info_program_name)(SPVM_ENV* env, void* obj_program_name);
  int32_t (*set_command_info_argv)(SPVM_ENV* env, void* obj_argv);
  int32_t (*get_class_id_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  const char* (*strerror)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length);
  void* (*new_string_array)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
  int32_t (*get_args_stack_length)(SPVM_ENV* env, SPVM_VALUE* stack);
  void (*set_args_stack_length)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t args_length);
  const char* (*dumpc)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void* (*new_pointer_object_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, void* pointer);
  void* (*new_pointer_object)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, void* pointer);
  void* (*new_pointer_object_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, void* pointer, int32_t* error, const char* func_name, const char* file, int32_t line);
  void* (*get_elem_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index);
  void (*set_elem_string)(SPVM_ENV* env, SPVM_VALUE* stack, void* array, int32_t index, void* string);
  int32_t (*is_class)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  int32_t (*is_pointer_class)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);
  void* (*strerror_string)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length);
  int32_t (*get_basic_type_id_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error, const char* func_name, const char* file, int32_t line);
  int32_t (*get_field_id_static)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* field_name);
  int32_t (*items)(SPVM_ENV* env, SPVM_VALUE* stack);
  int32_t (*call_instance_method_static_by_name)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* method_name, int32_t args_stack_length, const char* func_name, const char* file, int32_t line);
  int32_t (*get_method_id)(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* method_name);
  const char* (*strerror_nolen)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value);
  void* (*strerror_string_nolen)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value);
  void* (*get_compile_type_name_raw)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t dimension, int32_t flag);
  void* (*get_compile_type_name)(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t dimension, int32_t flag);
  int32_t (*set_command_info_base_time)(SPVM_ENV* env, int64_t base_time);
};

struct spvm_env_runtime {
  void* (*new_object)();
  void (*free_object)(void* runtime);
  int32_t* (*get_opcodes)(void* runtime);
  int32_t (*get_opcodes_length)(void* runtime);
  int32_t* (*get_runtime_codes)(void* runtime);
  int32_t (*get_runtime_codes_length)(void* runtime);
  int32_t (*get_classes_length)(void* runtime);
  int32_t (*get_constant_string_id)(void* runtime, const char* string);
  const char* (*get_constant_string_value)(void* runtime, int32_t constant_string_id, int32_t* string_length);
  const char* (*get_name)(void* runtime, int32_t constant_string_id);
  int32_t (*get_basic_type_id_by_name)(void* runtime, const char* basic_type_name);
  int32_t (*get_basic_type_name_id)(void* runtime, int32_t basic_type_id);
  int32_t (*get_basic_type_class_id)(void* runtime, int32_t basic_type_id);
  int32_t (*get_basic_type_category)(void* runtime, int32_t basic_type_id);
  int32_t (*get_type_basic_type_id)(void* runtime, int32_t type_id);
  int32_t (*get_type_dimension)(void* runtime, int32_t type_id);
  int32_t (*get_type_stack_length)(void* runtime, int32_t type_id);
  int32_t (*get_type_is_object)(void* runtime, int32_t type_id);
  int32_t (*get_type_is_ref)(void* runtime, int32_t type_id);
  int32_t (*get_class_id_by_name)(void* runtime, const char* class_name);
  int32_t (*get_class_name_id)(void* runtime, int32_t class_id);
  int32_t (*get_class_class_rel_file_id)(void* runtime, int32_t class_id);
  int32_t (*get_class_class_path_id)(void* runtime, int32_t class_id);
  int32_t (*get_class_is_anon)(void* runtime, int32_t class_id);
  int32_t (*get_class_fields_base_id)(void* runtime, int32_t class_id);
  int32_t (*get_class_fields_length)(void* runtime, int32_t class_id);
  int32_t (*get_class_methods_base_id)(void* runtime, int32_t class_id);
  int32_t (*get_class_methods_length)(void* runtime, int32_t class_id);
  int32_t (*get_class_class_vars_base_id)(void* runtime, int32_t class_id);
  int32_t (*get_class_class_vars_length)(void* runtime, int32_t class_id);
  int32_t (*get_class_anon_methods_base_id)(void* runtime, int32_t class_id);
  int32_t (*get_class_anon_methods_length)(void* runtime, int32_t class_id);
  int32_t (*get_class_var_id_by_index)(void* runtime, int32_t class_id, int32_t class_var_index);
  int32_t (*get_class_var_id_by_name)(void* runtime, const char* class_name, const char* class_var_name);
  int32_t (*get_class_var_name_id)(void* runtime, int32_t class_var_id);
  int32_t (*get_class_var_class_id)(void* runtime, int32_t class_var_id);
  int32_t (*get_field_id_by_index)(void* runtime, int32_t class_id, int32_t field_index);
  int32_t (*get_field_id_by_name)(void* runtime, const char* class_name, const char* field_name);
  int32_t (*get_field_name_id)(void* runtime, int32_t field_id);
  int32_t (*get_field_type_id)(void* runtime, int32_t field_id);
  int32_t (*get_field_class_id)(void* runtime, int32_t field_id);
  int32_t (*get_method_id_by_index)(void* runtime, int32_t class_id, int32_t method_index);
  int32_t (*get_method_id_by_name)(void* runtime, const char* class_name, const char* method_name);
  int32_t (*get_method_name_id)(void* runtime, int32_t method_id);
  int32_t (*get_method_return_type_id)(void* runtime, int32_t method_id);
  int32_t (*get_method_class_id)(void* runtime, int32_t method_id);
  int32_t (*get_method_is_class_method)(void* runtime, int32_t method_id);
  int32_t (*get_method_is_anon)(void* runtime, int32_t method_id);
  int32_t (*get_method_is_native)(void* runtime, int32_t method_id);
  int32_t (*get_method_is_precompile)(void* runtime, int32_t method_id);
  int32_t (*get_method_call_stack_byte_vars_length)(void* runtime, int32_t method_id);
  int32_t (*get_method_call_stack_short_vars_length)(void* runtime, int32_t method_id);
  int32_t (*get_method_call_stack_int_vars_length)(void* runtime, int32_t method_id);
  int32_t (*get_method_call_stack_long_vars_length)(void* runtime, int32_t method_id);
  int32_t (*get_method_call_stack_float_vars_length)(void* runtime, int32_t method_id);
  int32_t (*get_method_call_stack_double_vars_length)(void* runtime, int32_t method_id);
  int32_t (*get_method_call_stack_object_vars_length)(void* runtime, int32_t method_id);
  int32_t (*get_method_call_stack_ref_vars_length)(void* runtime, int32_t method_id);
  int32_t (*get_method_mortal_stack_length)(void* runtime, int32_t method_id);
  int32_t (*get_method_opcodes_base_id)(void* runtime, int32_t method_id);
  int32_t (*get_method_opcodes_length)(void* runtime, int32_t method_id);
  int32_t (*get_method_args_base_id)(void* runtime, int32_t method_id);
  int32_t (*get_method_args_length)(void* runtime, int32_t method_id);
  int32_t (*get_arg_type_id)(void* runtime, int32_t arg_id);
  int32_t (*get_anon_method_method_id)(void* runtime, int32_t anon_method_id);
  void* (*get_native_method_address)(void* runtime, int32_t method_id);
  void (*set_native_method_address)(void* runtime, int32_t method_id, void* address);
  void* (*get_precompile_method_address)(SPVM_ENV*, int32_t method_id);
  void (*set_precompile_method_address)(void* runtime, int32_t method_id, void* address);
  void* object_header_size;
  void* object_weaken_backref_head_offset;
  void* object_ref_count_offset;
  void* object_basic_type_id_offset;
  void* object_type_dimension_offset;
  void* object_flag_offset;
  void* object_length_offset;
  void* (*get_allocator)(void* runtime);
  void (*build)(void* runtime, int32_t* runtime_codes);
  int32_t (*get_class_parent_class_id)(void* runtime, int32_t class_id);
  int32_t (*get_method_required_args_length)(void* runtime, int32_t method_id);
  int32_t (*get_class_is_pointer)(void* runtime, int32_t class_id);
  int32_t (*get_method_is_enum)(void* runtime, int32_t method_id);
  int32_t (*get_type_flag)(void* runtime, int32_t type_id);
  int32_t (*is_object_type)(void* runtime, int32_t basic_type_id, int32_t type_dimension, int32_t flag);
};

struct spvm_env_compiler {
  void* (*new_object)();
  void (*free_object)(void* compiler);
  void (*set_start_line)(void* compiler, int32_t start_line);
  int32_t (*get_start_line)(void* compiler);
  void (*set_start_file)(void* compiler, const char* start_file);
  const char* (*get_start_file)(void* compiler);
  void (*add_class_path)(void* compiler, const char* class_path);
  int32_t (*get_class_paths_length )(void* compiler);
  const char* (*get_class_path )(void* compiler, int32_t index);
  int32_t (*compile)(void* compiler, const char* class_name);
  int32_t (*get_error_messages_length)(void* compiler);
  const char* (*get_error_message)(void* compiler, int32_t index);
  int32_t* (*create_runtime_codes)(void* compiler, void* allocator);
  void (*clear_class_paths)(void* compiler);
};

struct spvm_env_precompile {
  void* (*new_object)();
  void (*free_object)(void* precompile);
  void (*set_runtime)(void* precompile, void* runtime);
  void* (*get_runtime)(void* precompile);
  void (*build_class_source)(void* precompile, void* string_buffer, const char* class_name);
  void (*build_method_source)(void* precompile, void* string_buffer, const char* class_name, const char* method_name);
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
  SPVM_NATIVE_C_BASIC_TYPE_ID_COMMAND_INFO_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS,
  SPVM_NATIVE_C_BASIC_TYPE_ID_ADDRESS_CLASS,
};

enum {
  SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_UNKNOWN,
  SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NOT_FOUND_CLASS,
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
  SPVM_NATIVE_C_CLASS_ID_ERROR = 1,
  SPVM_NATIVE_C_CLASS_ID_ERROR_SYSTEM = 2,
  SPVM_NATIVE_C_CLASS_ID_ERROR_NOT_SUPPORTED = 3,
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
