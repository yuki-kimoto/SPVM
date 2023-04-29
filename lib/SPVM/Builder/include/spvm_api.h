// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_H
#define SPVM_API_H

#define SPVM_VERSION "0.971009"

#include "spvm_typedecl.h"
#include "spvm_native.h"

enum {
  STACK_INDEX_EXCEPTION = 511,
  STACK_INDEX_MORTAL_STACK = 510,
  STACK_INDEX_MORTAL_STACK_TOP = 509,
  STACK_INDEX_MORTAL_STACK_CAPACITY = 508,
  STACK_INDEX_MEMORY_BLOCKS_COUNT = 507,
  STACK_INDEX_ARGS_STACK_LENGTH = 506,
  STACK_INDEX_CALL_DEPTH = 505,
};

/*
  Version
*/

const char* SPVM_API_get_spvm_version_string(SPVM_ENV* env, SPVM_VALUE* stack);
double SPVM_API_get_spvm_version_number(SPVM_ENV* env, SPVM_VALUE* stack);
const char* SPVM_API_get_version_string(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_id);
double SPVM_API_get_version_number(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_id);

/*
  Environment APIs
*/

SPVM_ENV* SPVM_API_new_env_raw(void);
void SPVM_API_free_env_raw(SPVM_ENV* env);
SPVM_ENV* SPVM_API_new_env(SPVM_ENV* env);
int32_t SPVM_API_init_env(SPVM_ENV* env);
void SPVM_API_free_env(SPVM_ENV* env);
void SPVM_API_free_env_prepared(SPVM_ENV* env);
void* SPVM_API_new_memory_env(SPVM_ENV* env, size_t size);
void SPVM_API_free_memory_env(SPVM_ENV* env, void* block);
int32_t SPVM_API_get_memory_blocks_count_env(SPVM_ENV* env);
SPVM_VALUE* SPVM_API_new_stack(SPVM_ENV* env);
void SPVM_API_free_stack(SPVM_ENV* env, SPVM_VALUE* stack);
void SPVM_API_call_init_blocks(SPVM_ENV* env);
void SPVM_API_cleanup_global_vars(SPVM_ENV* env);
int32_t SPVM_API_set_command_info_program_name(SPVM_ENV* env, SPVM_OBJECT* obj_program_name);
int32_t SPVM_API_set_command_info_argv(SPVM_ENV* env, SPVM_OBJECT* obj_argv);
int32_t SPVM_API_set_command_info_base_time(SPVM_ENV* env, int64_t base_time);

/*
  Object manipulating APIs
  These APIs need stack argument
*/

// Runtime information

int32_t SPVM_API_get_class_id(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name);
int32_t SPVM_API_get_basic_type_id(SPVM_ENV* env, SPVM_VALUE* stack, const char* name);
int32_t SPVM_API_get_method_id(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* method_name);
int32_t SPVM_API_get_class_method_id(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* method_name);
int32_t SPVM_API_get_instance_method_id(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* method_name);
int32_t SPVM_API_get_class_var_id(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name);
int32_t SPVM_API_get_field_id(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name);
int32_t SPVM_API_get_field_id_static(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* field_name);
int32_t SPVM_API_get_field_offset(SPVM_ENV* env, SPVM_VALUE* stack, int32_t field_id);
int32_t SPVM_API_get_instance_method_id_static(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* method_name);

// Manipulate memory
void* SPVM_API_new_memory_stack(SPVM_ENV* env, SPVM_VALUE* stack, size_t size);
void SPVM_API_free_memory_stack(SPVM_ENV* env, SPVM_VALUE* stack, void* block);
int32_t SPVM_API_get_memory_blocks_count_stack(SPVM_ENV* env, SPVM_VALUE* stack);

// Class id
int32_t SPVM_API_get_class_id_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, int32_t* error, const char* func_name, const char* file, int32_t line);

// Basic type id
int32_t SPVM_API_get_basic_type_id_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error, const char* func_name, const char* file, int32_t line);

// Call Method
int32_t SPVM_API_call_method(SPVM_ENV* env, SPVM_VALUE* stack, int32_t method_id, int32_t args_stack_length);
int32_t SPVM_API_get_args_stack_length(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_API_items(SPVM_ENV* env, SPVM_VALUE* stack);
void SPVM_API_set_args_stack_length(SPVM_ENV* env, SPVM_VALUE* stack, int32_t args_length);

// Call Method by name
int32_t SPVM_API_call_class_method_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* method_name, int32_t args_stack_length, const char* func_name, const char* file, int32_t line);
int32_t SPVM_API_call_instance_method_static_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* method_name, int32_t args_stack_length, const char* func_name, const char* file, int32_t line);
int32_t SPVM_API_call_instance_method_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t args_stack_length, const char* func_name, const char* file, int32_t line);

// Get spvm_object.h information
int32_t SPVM_API_string_length(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int8_t* SPVM_API_string_bytes(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_length(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array);
int32_t SPVM_API_get_object_type_dimension(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_get_object_basic_type_id(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

// Check type
int32_t SPVM_API_is_type(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t basic_type_id, int32_t type_dimension);
int32_t SPVM_API_is_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_is_class(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_is_pointer_class(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_is_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_is_numeric_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_is_mulnum_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_is_object_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_has_interface(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t callback_basic_type_id);
int32_t SPVM_API_is_child_class(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t super_class_basic_type_id);

// Get Class variable
int8_t SPVM_API_get_class_var_byte(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id);
int16_t SPVM_API_get_class_var_short(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id);
int32_t SPVM_API_get_class_var_int(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id);
int64_t SPVM_API_get_class_var_long(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id);
float SPVM_API_get_class_var_float(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id);
double SPVM_API_get_class_var_double(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id);
SPVM_OBJECT* SPVM_API_get_class_var_object(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id);

// Set class variable
void SPVM_API_set_class_var_byte(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id, int8_t value);
void SPVM_API_set_class_var_short(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id, int16_t value);
void SPVM_API_set_class_var_int(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id, int32_t value);
void SPVM_API_set_class_var_long(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id, int64_t value);
void SPVM_API_set_class_var_float(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id, float value);
void SPVM_API_set_class_var_double(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id, double value);
void SPVM_API_set_class_var_object(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_var_id, SPVM_OBJECT* value);

// Get Class variable by name
int8_t SPVM_API_get_class_var_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
int16_t SPVM_API_get_class_var_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
int32_t SPVM_API_get_class_var_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
int64_t SPVM_API_get_class_var_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
float SPVM_API_get_class_var_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
double SPVM_API_get_class_var_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);
SPVM_OBJECT* SPVM_API_get_class_var_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* func_name, const char* file, int32_t line);

// Set class variable by name
void SPVM_API_set_class_var_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int8_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_class_var_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int16_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_class_var_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_class_var_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int64_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_class_var_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, float value, int32_t* error, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_class_var_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, double value, int32_t* error, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_class_var_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, SPVM_OBJECT* value, int32_t* error, const char* func_name, const char* file, int32_t line);

// Get field
int8_t SPVM_API_get_field_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index);
int16_t SPVM_API_get_field_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index);
int32_t SPVM_API_get_field_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index);
int64_t SPVM_API_get_field_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index);
float SPVM_API_get_field_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index);
double SPVM_API_get_field_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index);
SPVM_OBJECT* SPVM_API_get_field_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index);

// Get field by name
int8_t SPVM_API_get_field_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line);
int16_t SPVM_API_get_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line);
int32_t SPVM_API_get_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line);
int64_t SPVM_API_get_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line);
float SPVM_API_get_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line);
double SPVM_API_get_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line);
SPVM_OBJECT* SPVM_API_get_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line);
const char* SPVM_API_get_field_string_chars_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error, const char* func_name, const char* file, int32_t line);

// Set field
void SPVM_API_set_field_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, int8_t value);
void SPVM_API_set_field_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, int16_t value);
void SPVM_API_set_field_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, int32_t value);
void SPVM_API_set_field_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, int64_t value);
void SPVM_API_set_field_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, float value);
void SPVM_API_set_field_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, double value);
void SPVM_API_set_field_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, SPVM_OBJECT* value);

// Set field by name
void SPVM_API_set_field_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int8_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int16_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int64_t value, int32_t* error, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, float value, int32_t* error, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, double value, int32_t* error, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, SPVM_OBJECT* value, int32_t* error, const char* func_name, const char* file, int32_t line);

// Get array information
int32_t SPVM_API_get_elem_size(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array);

// Get and set array element
int8_t* SPVM_API_get_elems_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array);
int16_t* SPVM_API_get_elems_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array);
int32_t* SPVM_API_get_elems_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array);
int64_t* SPVM_API_get_elems_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array);
float* SPVM_API_get_elems_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array);
double* SPVM_API_get_elems_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array);
SPVM_OBJECT* SPVM_API_get_elem_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t index);
void SPVM_API_set_elem_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t index, SPVM_OBJECT* object);
SPVM_OBJECT* SPVM_API_get_elem_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t index);
void SPVM_API_set_elem_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t index, SPVM_OBJECT* string);

// Get pointer
void* SPVM_API_get_pointer(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

// Set pointer
void SPVM_API_set_pointer(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, void* ptr);

// Get Bool object
int32_t SPVM_API_get_bool_object_value(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* bool_object);

// String manipulation
SPVM_OBJECT* SPVM_API_concat_raw(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string1, SPVM_OBJECT* string2);
SPVM_OBJECT* SPVM_API_concat(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string1, SPVM_OBJECT* string2);
void SPVM_API_make_read_only(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string);
int32_t SPVM_API_is_read_only(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string);
SPVM_OBJECT* SPVM_API_copy_raw(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
SPVM_OBJECT* SPVM_API_copy(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
void SPVM_API_shorten(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string, int32_t new_length);
const char* SPVM_API_get_chars(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string);

// Print
void SPVM_API_print(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string);
void SPVM_API_fprint(SPVM_ENV* env, SPVM_VALUE* stack, FILE* fh, SPVM_OBJECT* string);
void SPVM_API_print_stderr(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string);

// New object
SPVM_OBJECT* SPVM_API_new_object(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_id);
SPVM_OBJECT* SPVM_API_new_pointer_object(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, void* ptr);
SPVM_OBJECT* SPVM_API_new_byte_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_short_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_int_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_long_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_float_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_double_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_object_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length);
SPVM_OBJECT* SPVM_API_new_string_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_muldim_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t type_dimension, int32_t length);
SPVM_OBJECT* SPVM_API_new_mulnum_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length);
SPVM_OBJECT* SPVM_API_new_string_nolen(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes);
SPVM_OBJECT* SPVM_API_new_string(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length);
SPVM_OBJECT* SPVM_API_new_array_proto(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t length);

// New object raw
SPVM_OBJECT* SPVM_API_new_object_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_id);
SPVM_OBJECT* SPVM_API_new_pointer_object_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, void* ptr);
SPVM_OBJECT* SPVM_API_new_byte_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_short_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_int_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_long_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_float_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_double_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_object_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length);
SPVM_OBJECT* SPVM_API_new_muldim_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t type_dimension, int32_t length);
SPVM_OBJECT* SPVM_API_new_mulnum_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length);
SPVM_OBJECT* SPVM_API_new_string_nolen_raw(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes);
SPVM_OBJECT* SPVM_API_new_string_raw(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length);
SPVM_OBJECT* SPVM_API_new_array_proto_raw(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t length);

// New object by name
void* SPVM_API_new_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, int32_t* error, const char* func_name, const char* file, int32_t line);
SPVM_OBJECT* SPVM_API_new_pointer_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, void* pointer, int32_t* error, const char* func_name, const char* file, int32_t line);

// Exception
int32_t SPVM_API_set_exception(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* exception);
SPVM_OBJECT* SPVM_API_exception(SPVM_ENV* env, SPVM_VALUE* stack);
SPVM_OBJECT* SPVM_API_new_stack_trace_raw(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* exception, int32_t method_id, int32_t line);
SPVM_OBJECT* SPVM_API_new_stack_trace(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* exception, int32_t method_id, int32_t line);
int32_t SPVM_API_die(SPVM_ENV* env, SPVM_VALUE* stack, const char* message, ...);

// Reference count
void SPVM_API_inc_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
void SPVM_API_dec_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

// Weak refernece
void SPVM_API_free_weaken_back_refs(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_WEAKEN_BACKREF* weaken_backref_head);
int32_t SPVM_API_weaken(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** object_address);
void SPVM_API_unweaken(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** object_address);
int32_t SPVM_API_isweak(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** object_address);

// Scope
int32_t SPVM_API_enter_scope(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_API_push_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
void SPVM_API_leave_scope(SPVM_ENV* env, SPVM_VALUE* stack, int32_t original_mortal_stack_top);
int32_t SPVM_API_remove_mortal(SPVM_ENV* env, SPVM_VALUE* stack, int32_t original_mortal_stack_top, SPVM_OBJECT* remove_object);

// Get type name
SPVM_OBJECT* SPVM_API_get_type_name_raw(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
SPVM_OBJECT* SPVM_API_get_type_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_get_compile_type_name_length(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t type_dimension, int32_t type_flag);
SPVM_OBJECT* SPVM_API_get_compile_type_name_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t type_dimension, int32_t type_flag);
SPVM_OBJECT* SPVM_API_get_compile_type_name(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t type_dimension, int32_t type_flag);

// Dump
SPVM_OBJECT* SPVM_API_dump_raw(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
SPVM_OBJECT* SPVM_API_dump(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
void SPVM_API_dump_recursive(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t* depth, SPVM_STRING_BUFFER* string_buffer, SPVM_HASH* address_symtable);
const char* SPVM_API_dumpc(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

// Runtime type checking
int32_t SPVM_API_isa(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t cast_basic_type_id, int32_t cast_type_dimension);
int32_t SPVM_API_elem_isa(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, SPVM_OBJECT* element);

// Error
const char* SPVM_API_strerror(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length);
const char* SPVM_API_strerror_nolen(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value);
void* SPVM_API_strerror_string(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length);
void* SPVM_API_strerror_string_nolen(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value);

int32_t SPVM_API_call_method_vm(SPVM_ENV* env, SPVM_VALUE* stack, int32_t method_id, int32_t args_stack_length);

#endif
