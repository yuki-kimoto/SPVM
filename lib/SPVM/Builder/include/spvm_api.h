// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_H
#define SPVM_API_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

enum {
  SPVM_API_C_STACK_LENGTH = 512,
};

enum {
  SPVM_API_C_CALL_STACK_MEMORY_BLOCK_SIZE = 2048,
};

enum {
  SPVM_API_C_STACK_INDEX_TMP_BUFFER = 384, // 384 to 511
  SPVM_API_C_STACK_INDEX_EXCEPTION = 383,
  SPVM_API_C_STACK_INDEX_MORTAL_STACK = 382,
  SPVM_API_C_STACK_INDEX_MORTAL_STACK_LENGTH = 381,
  SPVM_API_C_STACK_INDEX_MORTAL_STACK_CAPACITY = 380,
  SPVM_API_C_STACK_INDEX_ARGS_WIDTH = 379,
  SPVM_API_C_STACK_INDEX_CALL_DEPTH = 378,
  SPVM_API_C_STACK_INDEX_ENV = 377,
  SPVM_API_C_STACK_INDEX_SEED = 376,
  SPVM_API_C_STACK_INDEX_SEED_INITIALIZED = 375,
  SPVM_API_C_STACK_INDEX_ALL_METHOD_CALL_PERMITTED = 374,
  SPVM_API_C_STACK_INDEX_CALL_STACK_FRAME_INFOS = 373,
  SPVM_API_C_STACK_INDEX_CALL_STACK_FRAME_INFOS_LENGTH = 372,
  SPVM_API_C_STACK_INDEX_CALL_STACK_FRAME_INFOS_CAPACITY = 371,
  SPVM_API_C_STACK_INDEX_CALL_STACK_OFFSET = 370,
  SPVM_API_C_STACK_INDEX_CALL_STACK_MEMORY_BLOCKS = 369,
  SPVM_API_C_STACK_INDEX_CALL_STACK_MEMORY_BLOCKS_CAPACITY = 368,
  SPVM_API_C_STACK_INDEX_MEMORY_BLOCKS_FOR_CALL_STACK = 367,
  SPVM_API_C_STACK_INDEX_CALLER_INFO_STACK = 366,
  SPVM_API_C_STACK_INDEX_CALLER_INFO_STACK_RECORD_SIZE = 365,
  SPVM_API_C_STACK_INDEX_CALLER_INFO_STACK_CAPACITY = 364
  SPVM_API_C_STACK_INDEX_CURRENT_METHOD = 363,
};

enum {
  SPVM_API_C_CALL_METHOD_CHECK_ARGS_LEVEL_NO_CHECK,
  SPVM_API_C_CALL_METHOD_CHECK_ARGS_LEVEL_AUTO_CHECK,
  SPVM_API_C_CALL_METHOD_CHECK_ARGS_LEVEL_FULL_CHECK,
};

/*
  Environment APIs
*/

SPVM_ENV* SPVM_API_new_env(void);
void SPVM_API_free_env(SPVM_ENV* env);
SPVM_VALUE* SPVM_API_new_stack(SPVM_ENV* env);
SPVM_VALUE* SPVM_API_new_stack_with_all_method_call_permitted(SPVM_ENV* env);
void SPVM_API_free_stack(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_API_args_width(SPVM_ENV* env, SPVM_VALUE* stack);

// Initialize/Cleanup
int32_t SPVM_API_call_init_methods(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_API_set_command_info_program_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* obj_program_name);
int32_t SPVM_API_set_command_info_argv(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* obj_argv);
int32_t SPVM_API_set_command_info_basetime(SPVM_ENV* env, SPVM_VALUE* stack, int64_t base_time);
void SPVM_API_destroy_class_vars(SPVM_ENV* env, SPVM_VALUE* stack);
void SPVM_API_destroy_cache_class_vars(SPVM_ENV* env, SPVM_VALUE* stack);

// Manipulate memory
void* SPVM_API_new_memory_block(SPVM_ENV* env, SPVM_VALUE* stack, size_t size);
void SPVM_API_free_memory_block(SPVM_ENV* env, SPVM_VALUE* stack, void* block);
int32_t SPVM_API_get_memory_blocks_count(SPVM_ENV* env, SPVM_VALUE* stack);

// Basic type
int32_t SPVM_API_get_basic_type_id(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name);
int32_t SPVM_API_get_basic_type_id_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_get_basic_type(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_get_basic_type_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_get_basic_type_by_id(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id);

// Class variable
SPVM_RUNTIME_CLASS_VAR* SPVM_API_get_class_var(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name);

// Get Class variable
int8_t SPVM_API_get_class_var_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var);
int16_t SPVM_API_get_class_var_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var);
int32_t SPVM_API_get_class_var_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var);
int64_t SPVM_API_get_class_var_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var);
float SPVM_API_get_class_var_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var);
double SPVM_API_get_class_var_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var);
SPVM_OBJECT* SPVM_API_get_class_var_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var);
SPVM_OBJECT* SPVM_API_get_class_var_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var);
SPVM_OBJECT** SPVM_API_get_class_var_object_ref(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var);

// Set class variable
void SPVM_API_set_class_var_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, int8_t value);
void SPVM_API_set_class_var_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, int16_t value);
void SPVM_API_set_class_var_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, int32_t value);
void SPVM_API_set_class_var_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, int64_t value);
void SPVM_API_set_class_var_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, float value);
void SPVM_API_set_class_var_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, double value);
void SPVM_API_set_class_var_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, SPVM_OBJECT* value);
void SPVM_API_set_class_var_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CLASS_VAR* class_var, SPVM_OBJECT* value);

// Get Class variable by name
int8_t SPVM_API_get_class_var_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
int16_t SPVM_API_get_class_var_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
int32_t SPVM_API_get_class_var_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
int64_t SPVM_API_get_class_var_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
float SPVM_API_get_class_var_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
double SPVM_API_get_class_var_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
SPVM_OBJECT* SPVM_API_get_class_var_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
SPVM_OBJECT* SPVM_API_get_class_var_string_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);

// Set class variable by name
void SPVM_API_set_class_var_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int8_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_class_var_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int16_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_class_var_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int32_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_class_var_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, int64_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_class_var_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, float value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_class_var_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, double value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_class_var_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, SPVM_OBJECT* value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_class_var_string_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* class_var_name, SPVM_OBJECT* value, int32_t* error_id, const char* func_name, const char* file, int32_t line);

// Field
SPVM_RUNTIME_FIELD* SPVM_API_get_field(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name);
SPVM_RUNTIME_FIELD* SPVM_API_get_field_static(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* field_name);

// Get field
int8_t SPVM_API_get_field_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field);
int16_t SPVM_API_get_field_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field);
int32_t SPVM_API_get_field_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field);
int64_t SPVM_API_get_field_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field);
float SPVM_API_get_field_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field);
double SPVM_API_get_field_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field);
SPVM_OBJECT* SPVM_API_get_field_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field);
SPVM_OBJECT** SPVM_API_get_field_object_ref(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field);
SPVM_OBJECT* SPVM_API_get_field_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field);

// Set field
void SPVM_API_set_field_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, int8_t value);
void SPVM_API_set_field_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, int16_t value);
void SPVM_API_set_field_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, int32_t value);
void SPVM_API_set_field_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, int64_t value);
void SPVM_API_set_field_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, float value);
void SPVM_API_set_field_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, double value);
void SPVM_API_set_field_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, SPVM_OBJECT* value);
void SPVM_API_set_field_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field, SPVM_OBJECT* value);

// Get field by name
int8_t SPVM_API_get_field_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
int16_t SPVM_API_get_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
int32_t SPVM_API_get_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
int64_t SPVM_API_get_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
float SPVM_API_get_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
double SPVM_API_get_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
SPVM_OBJECT* SPVM_API_get_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
SPVM_OBJECT** SPVM_API_get_field_object_ref_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
SPVM_OBJECT* SPVM_API_get_field_object_defined_and_has_pointer_by_name(SPVM_ENV* env, SPVM_VALUE* stack, void* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file_name, int32_t line);
const char* SPVM_API_get_field_string_chars_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
SPVM_OBJECT* SPVM_API_get_field_string_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);

// Set field by name
void SPVM_API_set_field_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int8_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int16_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int64_t value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, float value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, double value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, SPVM_OBJECT* value, int32_t* error_id, const char* func_name, const char* file, int32_t line);
void SPVM_API_set_field_string_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, SPVM_OBJECT* value, int32_t* error_id, const char* func_name, const char* file, int32_t line);

// Method
SPVM_RUNTIME_METHOD* SPVM_API_get_method(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name);
SPVM_RUNTIME_METHOD* SPVM_API_get_class_method(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name);
SPVM_RUNTIME_METHOD* SPVM_API_get_instance_method_static(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name);
SPVM_RUNTIME_METHOD* SPVM_API_get_instance_method(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* method_name);

// Call Method
int32_t SPVM_API_call_method_native(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* method, int32_t args_width);
int32_t SPVM_API_call_method_common(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* method, int32_t args_width, int32_t mortal, int32_t check_args_level, const char* func_name, const char* file, int32_t line);
int32_t SPVM_API_call_method_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* method, int32_t args_width, const char* func_name, const char* file, int32_t line);
int32_t SPVM_API_call_method_no_mortal_no_check_args(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* method, int32_t args_width, const char* func_name, const char* file, int32_t line);
int32_t SPVM_API_call_method(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_METHOD* method, int32_t args_width, const char* func_name, const char* file, int32_t line);
int32_t SPVM_API_call_instance_method_common(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t args_width, int32_t mortal, int32_t less_check_args, const char* decl_basic_type_name, const char* func_name, const char* file, int32_t line);
int32_t SPVM_API_call_instance_method_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t args_width, const char* func_name, const char* file, int32_t line);
int32_t SPVM_API_call_instance_method_no_mortal_less_check_args(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t args_width, const char* decl_basic_type_name, const char* func_name, const char* file, int32_t line);
int32_t SPVM_API_call_instance_method(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t args_width, const char* func_name, const char* file, int32_t line);

// Call Method by name
void SPVM_API_call_class_method_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name, int32_t args_width, int32_t* error_id, const char* func_name, const char* file, int32_t line);
void SPVM_API_call_instance_method_static_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, const char* method_name, int32_t args_width, int32_t* error_id, const char* func_name, const char* file, int32_t line);
void SPVM_API_call_instance_method_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* method_name, int32_t args_width, int32_t* error_id, const char* func_name, const char* file, int32_t line);

// Get spvm_object.h information
int32_t SPVM_API_string_length(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int8_t* SPVM_API_string_bytes(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_length(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_capacity(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_set_length(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t length);
int32_t SPVM_API_set_capacity(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t capacity);

int32_t SPVM_API_get_object_type_dimension(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_get_object_basic_type_id(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
const char* SPVM_API_get_object_basic_type_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_get_object_basic_type(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

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
int32_t SPVM_API_get_byte_object_value(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* byte_object);
int32_t SPVM_API_get_short_object_value(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* short_object);
int32_t SPVM_API_get_int_object_value(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* int_object);
int64_t SPVM_API_get_long_object_value(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* long_object);
float SPVM_API_get_float_object_value(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* float_object);
double SPVM_API_get_double_object_value(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* double_object);

// String manipulation
SPVM_OBJECT* SPVM_API_concat_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string1, SPVM_OBJECT* string2);
SPVM_OBJECT* SPVM_API_concat(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string1, SPVM_OBJECT* string2);
void SPVM_API_make_read_only(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string);
void SPVM_API_make_fixed_length(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_is_read_only(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string);
int32_t SPVM_API_is_fixed_length(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
SPVM_OBJECT* SPVM_API_copy_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
SPVM_OBJECT* SPVM_API_copy(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
void SPVM_API_shorten(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string, int32_t new_length);
const char* SPVM_API_get_chars(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string);

// Print
void SPVM_API_print(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string);
void SPVM_API_say(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string);
void SPVM_API_fprint(SPVM_ENV* env, SPVM_VALUE* stack, FILE* fh, SPVM_OBJECT* string);
void SPVM_API_print_stderr(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string);
void SPVM_API_say_stderr(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string);
void SPVM_API_warn(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* string, const char* basic_type_name, const char* method_name, const char* file, int32_t line);

// New object
SPVM_OBJECT* SPVM_API_new_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type);
SPVM_OBJECT* SPVM_API_new_pointer_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type, void* pointer);
SPVM_OBJECT* SPVM_API_new_byte_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_short_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_int_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_long_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_float_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_double_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_object_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t length);
SPVM_OBJECT* SPVM_API_new_string_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_muldim_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t length);
SPVM_OBJECT* SPVM_API_new_mulnum_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t length);
SPVM_OBJECT* SPVM_API_new_string_nolen(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes);
SPVM_OBJECT* SPVM_API_new_string(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length);
SPVM_OBJECT* SPVM_API_new_array_proto(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t length);
SPVM_OBJECT* SPVM_API_new_object_common(SPVM_ENV* env, SPVM_VALUE* stack, size_t alloc_size, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t length, int32_t flag);

// New object no mortal
SPVM_OBJECT* SPVM_API_new_object_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type);
SPVM_OBJECT* SPVM_API_new_pointer_object_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type, void* pointer);
SPVM_OBJECT* SPVM_API_new_byte_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_short_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_int_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_long_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_float_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_double_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_object_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t length);
SPVM_OBJECT* SPVM_API_new_string_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_muldim_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t length);
SPVM_OBJECT* SPVM_API_new_mulnum_array_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t length);
SPVM_OBJECT* SPVM_API_new_string_nolen_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes);
SPVM_OBJECT* SPVM_API_new_string_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length);
SPVM_OBJECT* SPVM_API_new_array_proto_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t length);

// New object by name
void* SPVM_API_new_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);
SPVM_OBJECT* SPVM_API_new_pointer_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, void* pointer, int32_t* error_id, const char* func_name, const char* file, int32_t line);
SPVM_OBJECT* SPVM_API_new_object_array_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t length, int32_t* error_id, const char* func_name, const char* file, int32_t line);
SPVM_OBJECT* SPVM_API_new_muldim_array_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t type_dimension, int32_t length, int32_t* error_id, const char* func_name, const char* file, int32_t line);
SPVM_OBJECT* SPVM_API_new_mulnum_array_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t length, int32_t* error_id, const char* func_name, const char* file, int32_t line);

// Exception
int32_t SPVM_API_set_exception(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* exception);
SPVM_OBJECT* SPVM_API_get_exception(SPVM_ENV* env, SPVM_VALUE* stack);
SPVM_OBJECT* SPVM_API_new_stack_trace_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* exception, SPVM_RUNTIME_METHOD* method, int32_t line);
SPVM_OBJECT* SPVM_API_new_stack_trace(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* exception, SPVM_RUNTIME_METHOD* method, int32_t line);
int32_t SPVM_API_die(SPVM_ENV* env, SPVM_VALUE* stack, const char* message, ...);

// Reference count
void SPVM_API_inc_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
void SPVM_API_dec_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_get_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

// Weak refernece
void SPVM_API_free_weaken_backrefs(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_WEAKEN_BACKREF* weaken_backref_head);
int32_t SPVM_API_weaken(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** ref);
void SPVM_API_unweaken(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** ref);
int32_t SPVM_API_isweak(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** ref);
SPVM_OBJECT* SPVM_API_drop_tag_pointers(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

// Scope
int32_t SPVM_API_enter_scope(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_API_push_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
void SPVM_API_leave_scope(SPVM_ENV* env, SPVM_VALUE* stack, int32_t original_mortal_stack_top);
void SPVM_API_leave_scope_local_removed3(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** object_vars, int32_t* mortal_stack, int32_t* mortal_stack_top_ptr, int32_t original_mortal_stack_top);
void SPVM_API_leave_scope_local(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** object_vars, int32_t* mortal_stack_typed_var_index, int32_t* mortal_stack_top_ptr, int32_t* mortal_stack_tops, int32_t mortal_stack_tops_index);

// Get type name
SPVM_OBJECT* SPVM_API_get_type_name_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
SPVM_OBJECT* SPVM_API_get_type_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_get_compile_type_name_length(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t type_dimension, int32_t type_flag);
SPVM_OBJECT* SPVM_API_get_compile_type_name_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t type_dimension, int32_t type_flag);
SPVM_OBJECT* SPVM_API_get_compile_type_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name, int32_t type_dimension, int32_t type_flag);

// Dump
SPVM_OBJECT* SPVM_API_dump_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
SPVM_OBJECT* SPVM_API_dump(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
void SPVM_API_dump_recursive(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t* depth, SPVM_STRING_BUFFER* string_buffer, SPVM_HASH* address_symtable);
const char* SPVM_API_dumpc(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

/*
  Version
*/

const char* SPVM_API_get_spvm_version_string(SPVM_ENV* env, SPVM_VALUE* stack);
double SPVM_API_get_spvm_version_number(SPVM_ENV* env, SPVM_VALUE* stack);
const char* SPVM_API_get_version_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type);
double SPVM_API_get_version_number(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type);

// Type utilities
int32_t SPVM_API_isa(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension);
int32_t SPVM_API_isa_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* basic_type_name, int32_t type_dimension);
int32_t SPVM_API_is_type(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension);
int32_t SPVM_API_is_type_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* basic_type_name, int32_t type_dimension);
int32_t SPVM_API_elem_isa(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, SPVM_OBJECT* element);
int32_t SPVM_API_is_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_is_class(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_is_pointer_class(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_is_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_is_numeric_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_is_numeric_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_is_mulnum_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_is_object_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_is_any_object_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

// strerror
const char* SPVM_API_strerror(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length);
const char* SPVM_API_strerror_nolen(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value);
void* SPVM_API_strerror_string(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value, int32_t length);
void* SPVM_API_strerror_string_nolen(SPVM_ENV* env, SPVM_VALUE* stack, int32_t errno_value);

int32_t SPVM_API_is_binary_compatible_stack(SPVM_ENV* env, SPVM_VALUE* stack);

// Assign

void SPVM_API_assign_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** dist_ref, SPVM_OBJECT* object);

SPVM_MUTEX* SPVM_API_get_object_mutex(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

void SPVM_API_lock_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

void SPVM_API_unlock_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

// Internal native APIs

void SPVM_API_INTERNAL_lock_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

void SPVM_API_INTERNAL_unlock_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

void SPVM_API_INTERNAL_inc_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

void SPVM_API_INTERNAL_dec_ref_count(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

void SPVM_API_INTERNAL_leave_scope_local_removed3(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT** object_vars, int32_t* mortal_stack, int32_t* mortal_stack_top_ptr, int32_t original_mortal_stack_top);

FILE* SPVM_API_spvm_stdin(SPVM_ENV* env, SPVM_VALUE* stack);

FILE* SPVM_API_spvm_stdout(SPVM_ENV* env, SPVM_VALUE* stack);

FILE* SPVM_API_spvm_stderr(SPVM_ENV* env, SPVM_VALUE* stack);

int32_t SPVM_API_check_bootstrap_method(SPVM_ENV* env, SPVM_VALUE* stack, const char* basic_type_name);

SPVM_OBJECT* SPVM_API_new_array_proto_element_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* element, int32_t length);

SPVM_OBJECT* SPVM_API_new_array_proto_element(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* element, int32_t length);

int32_t SPVM_API_is_binary_compatible_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

char* SPVM_API_get_stack_tmp_buffer(SPVM_ENV* env, SPVM_VALUE* stack);

int32_t SPVM_API_no_free(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

void SPVM_API_set_no_free(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t no_free);

void SPVM_API_print_exception_to_stderr(SPVM_ENV* env, SPVM_VALUE* stack);

SPVM_OBJECT* SPVM_API_dump_object_internal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

int32_t SPVM_API_get_seed(SPVM_ENV* env, SPVM_VALUE* stack);

void SPVM_API_set_seed(SPVM_ENV* env, SPVM_VALUE* stack, int32_t seed);

int32_t SPVM_API_seed_initialized(SPVM_ENV* env, SPVM_VALUE* stack);

const char* SPVM_API_get_basic_type_name_in_version_from(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type);

int32_t SPVM_API_set_command_info_warning(SPVM_ENV* env, SPVM_VALUE* stack, int32_t warning);

int32_t SPVM_API_can_assign(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* dist_basic_type, int32_t dist_type_dimension, int32_t dist_type_flag, SPVM_RUNTIME_BASIC_TYPE* src_basic_type, int32_t src_type_dimension, int32_t src_type_flag);

/*
  Type native APIs
*/

int32_t SPVM_API_get_type_width(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag);

int32_t SPVM_API_is_object_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag);

int32_t SPVM_API_is_any_object_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag);

int32_t SPVM_API_is_object_array_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag);

int32_t SPVM_API_is_any_object_array_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag);

int32_t SPVM_API_is_numeric_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag);

int32_t SPVM_API_is_class_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag);

int32_t SPVM_API_is_mulnum_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag);

int32_t SPVM_API_is_dynamic_data_type(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag);

/*
  The end of type native APIs
*/

int32_t SPVM_API_get_call_stack_frame_size(SPVM_RUNTIME_METHOD* method);
int32_t SPVM_API_push_call_stack_frame(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CALL_STACK_FRAME_INFO* call_stack_frame_info);
void SPVM_API_pop_call_stack_frame(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CALL_STACK_FRAME_INFO* call_stack_frame_info);
void SPVM_API_set_call_stack_frame_info(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_RUNTIME_CALL_STACK_FRAME_INFO* call_stack_frame_info, char* call_stack_frame);
void* SPVM_API_new_memory_block_for_call_stack(SPVM_ENV* env, SPVM_VALUE* stack, int32_t size);

void SPVM_API_free_memory_block_for_call_stack(SPVM_ENV* env, SPVM_VALUE* stack, void* block);

void SPVM_API_enable_options(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
void SPVM_API_disable_options(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_is_options(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

int32_t SPVM_API_exists_field(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field);

int32_t SPVM_API_exists_field_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);

void SPVM_API_delete_field(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, SPVM_RUNTIME_FIELD* field);

void SPVM_API_delete_field_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* field_name, int32_t* error_id, const char* func_name, const char* file, int32_t line);

int32_t SPVM_API_is_numeric_object_type(SPVM_RUNTIME* runtime, SPVM_RUNTIME_BASIC_TYPE* basic_type, int32_t type_dimension, int32_t type_flag);

int8_t SPVM_API_numeric_object_to_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t* error_id);
int16_t SPVM_API_numeric_object_to_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t* error_id);
int32_t SPVM_API_numeric_object_to_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t* error_id);
int64_t SPVM_API_numeric_object_to_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t* error_id);
float SPVM_API_numeric_object_to_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t* error_id);
double SPVM_API_numeric_object_to_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t* error_id);
void* SPVM_API_numeric_object_to_string_no_mortal(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t* error_id);
void* SPVM_API_numeric_object_to_string(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t* error_id);

#endif
