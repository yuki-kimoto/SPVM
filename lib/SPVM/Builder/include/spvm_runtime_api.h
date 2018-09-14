#ifndef SPVM_RUNTIME_API_H
#define SPVM_RUNTIME_API_H

#include "spvm_base.h"
#include "spvm_native.h"

int32_t SPVM_RUNTIME_API_has_interface(SPVM_ENV* env, int32_t package_basic_type_id, int32_t interface_basic_type_id);

int32_t SPVM_RUNTIME_API_call_entry_point_sub(SPVM_ENV* env, const char* package_name, int32_t argc, const char *argv[]);

int32_t SPVM_RUNTIME_API_is_value_type(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_RUNTIME_API_is_object_type(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_RUNTIME_API_is_ref_type(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_RUNTIME_API_is_numeric_ref_type(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_RUNTIME_API_is_array_type(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t flag);
int32_t SPVM_RUNTIME_API_is_value_ref_type(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t flag);

int32_t SPVM_RUNTIME_API_get_width(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t flag);


// Get
int32_t SPVM_RUNTIME_API_get_object_header_byte_size(SPVM_ENV* env);
int32_t SPVM_RUNTIME_API_get_array_length(SPVM_ENV* env, SPVM_OBJECT* array);
int8_t* SPVM_RUNTIME_API_get_byte_array_elements(SPVM_ENV* env, SPVM_OBJECT* array);
int16_t* SPVM_RUNTIME_API_get_short_array_elements(SPVM_ENV* env, SPVM_OBJECT* array);
int32_t* SPVM_RUNTIME_API_get_int_array_elements(SPVM_ENV* env, SPVM_OBJECT* array);
int64_t* SPVM_RUNTIME_API_get_long_array_elements(SPVM_ENV* env, SPVM_OBJECT* array);
float* SPVM_RUNTIME_API_get_float_array_elements(SPVM_ENV* env, SPVM_OBJECT* array);
double* SPVM_RUNTIME_API_get_double_array_elements(SPVM_ENV* env, SPVM_OBJECT* array);
SPVM_OBJECT* SPVM_RUNTIME_API_get_object_array_element(SPVM_ENV* env, SPVM_OBJECT* array, int32_t index);
void* SPVM_RUNTIME_API_get_pointer(SPVM_ENV* env, SPVM_OBJECT* object);
int8_t SPVM_RUNTIME_API_get_byte_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index);
int16_t SPVM_RUNTIME_API_get_short_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index);
int32_t SPVM_RUNTIME_API_get_int_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index);
int64_t SPVM_RUNTIME_API_get_long_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index);
float SPVM_RUNTIME_API_get_float_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index);
double SPVM_RUNTIME_API_get_double_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index);
SPVM_OBJECT* SPVM_RUNTIME_API_get_object_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index);

// Set
void SPVM_RUNTIME_API_set_byte_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, int8_t value);
void SPVM_RUNTIME_API_set_short_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, int16_t value);
void SPVM_RUNTIME_API_set_int_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, int32_t value);
void SPVM_RUNTIME_API_set_long_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, int64_t value);
void SPVM_RUNTIME_API_set_float_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, float value);
void SPVM_RUNTIME_API_set_double_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, double value);
void SPVM_RUNTIME_API_set_object_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, SPVM_OBJECT* value);
void SPVM_RUNTIME_API_set_object_array_element(SPVM_ENV* env, SPVM_OBJECT* array, int32_t index, SPVM_OBJECT* value);

// Call Subroutine
void SPVM_RUNTIME_API_call_void_sub(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
int8_t SPVM_RUNTIME_API_call_byte_sub(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
int16_t SPVM_RUNTIME_API_call_short_sub(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
int32_t SPVM_RUNTIME_API_call_int_sub(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
int64_t SPVM_RUNTIME_API_call_long_sub(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
float SPVM_RUNTIME_API_call_float_sub(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
double SPVM_RUNTIME_API_call_double_sub(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
SPVM_OBJECT* SPVM_RUNTIME_API_call_object_sub(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);

// String
int32_t SPVM_RUNTIME_API_get_string_length(SPVM_ENV* env, SPVM_OBJECT* object);
int8_t* SPVM_RUNTIME_API_get_string_bytes(SPVM_ENV* env, SPVM_OBJECT* object);
void SPVM_RUNTIME_API_print(SPVM_ENV* env, SPVM_OBJECT* string);
SPVM_OBJECT* SPVM_RUNTIME_API_concat(SPVM_ENV* env, SPVM_OBJECT* string1, SPVM_OBJECT* string2);

// ID
int32_t SPVM_RUNTIME_API_get_basic_type_id(SPVM_ENV* env, const char* name);
int32_t SPVM_RUNTIME_API_get_sub_id(SPVM_ENV* env, const char* package_name, const char* signature);
int32_t SPVM_RUNTIME_API_get_sub_id_method_call(SPVM_ENV* env, SPVM_OBJECT* object, const char* signature);
int32_t SPVM_RUNTIME_API_get_package_var_id(SPVM_ENV* env, const char* package_name, const char* signature);
int32_t SPVM_RUNTIME_API_get_field_index(SPVM_ENV* env, const char* package_name, const char* signature);
int32_t SPVM_RUNTIME_API_get_package_var_id(SPVM_ENV* env, const char* package_name, const char* signature);

// New raw
SPVM_OBJECT* SPVM_RUNTIME_API_new_object(SPVM_ENV* env, int32_t package_id);
SPVM_OBJECT* SPVM_RUNTIME_API_new_pointer(SPVM_ENV* env, int32_t basic_type_id, void* ptr);
SPVM_OBJECT* SPVM_RUNTIME_API_new_byte_array(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_RUNTIME_API_new_short_array(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_RUNTIME_API_new_int_array(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_RUNTIME_API_new_long_array(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_RUNTIME_API_new_float_array(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_RUNTIME_API_new_double_array(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_RUNTIME_API_new_object_array(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
SPVM_OBJECT* SPVM_RUNTIME_API_new_multi_array(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t length);
SPVM_OBJECT* SPVM_RUNTIME_API_new_value_t_array(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
SPVM_OBJECT* SPVM_RUNTIME_API_new_string(SPVM_ENV* env, const char* bytes, int32_t length);

// New
SPVM_OBJECT* SPVM_RUNTIME_API_new_object_raw(SPVM_ENV* env, int32_t package_id);
SPVM_OBJECT* SPVM_RUNTIME_API_new_pointer_raw(SPVM_ENV* env, int32_t basic_type_id, void* ptr);
SPVM_OBJECT* SPVM_RUNTIME_API_new_byte_array_raw(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_RUNTIME_API_new_short_array_raw(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_RUNTIME_API_new_int_array_raw(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_RUNTIME_API_new_long_array_raw(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_RUNTIME_API_new_float_array_raw(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_RUNTIME_API_new_double_array_raw(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_RUNTIME_API_new_object_array_raw(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
SPVM_OBJECT* SPVM_RUNTIME_API_new_multi_array_raw(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t length);
SPVM_OBJECT* SPVM_RUNTIME_API_new_value_t_array_raw(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
SPVM_OBJECT* SPVM_RUNTIME_API_new_string_raw(SPVM_ENV* env, const char* bytes, int32_t length);

// Exception
void SPVM_RUNTIME_API_set_exception(SPVM_ENV* env, SPVM_OBJECT* exception);
SPVM_OBJECT* SPVM_RUNTIME_API_get_exception(SPVM_ENV* env);
SPVM_OBJECT* SPVM_RUNTIME_API_create_exception_stack_trace(SPVM_ENV* env, SPVM_OBJECT* exception, const char* package_name, const char* sub_name, const char* file, int32_t line);

// Reference count
void SPVM_RUNTIME_API_inc_ref_count(SPVM_ENV* env, SPVM_OBJECT* object);
void SPVM_RUNTIME_API_inc_dec_ref_count(SPVM_ENV* env, SPVM_OBJECT* object);
void SPVM_RUNTIME_API_dec_ref_count(SPVM_ENV* env, SPVM_OBJECT* object);
void SPVM_RUNTIME_API_dec_ref_count_only(SPVM_ENV* env, SPVM_OBJECT* object);
int32_t SPVM_RUNTIME_API_get_ref_count(SPVM_ENV* env, SPVM_OBJECT* object);

// Weak refernece
int32_t SPVM_RUNTIME_API_isweak(SPVM_ENV* env, SPVM_OBJECT* object);
void SPVM_RUNTIME_API_weaken(SPVM_ENV* env, SPVM_OBJECT** object_address);
void SPVM_RUNTIME_API_unweaken(SPVM_ENV* env, SPVM_OBJECT** object_address);
int32_t SPVM_RUNTIME_API_weaken_object_field(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index);

// Global information
SPVM_ENV* SPVM_RUNTIME_API_get_env_runtime();
int32_t SPVM_RUNTIME_API_get_memory_blocks_count(SPVM_ENV* env);

// Scope
int32_t SPVM_RUNTIME_API_enter_scope(SPVM_ENV* env);
void SPVM_RUNTIME_API_push_mortal(SPVM_ENV* env, SPVM_OBJECT* object);
void SPVM_RUNTIME_API_leave_scope(SPVM_ENV* env, int32_t original_mortal_stack_top);

#endif
