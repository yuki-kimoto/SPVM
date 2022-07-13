#ifndef SPVM_API_H
#define SPVM_API_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

/*
  Runtime information APIs
*/

int32_t SPVM_API_get_method_id_cache(SPVM_ENV* env, const char* method_cache_name, int32_t method_cache_name_length);
int32_t SPVM_API_get_field_id_cache(SPVM_ENV* env, const char* field_cache_name, int32_t field_cache_name_length);
int32_t SPVM_API_get_class_var_id_cache(SPVM_ENV* env, const char* class_var_cache_name, int32_t class_var_cache_name_length);
int32_t SPVM_API_get_class_id(SPVM_ENV* env, const char* class_name);

// ID
int32_t SPVM_API_get_basic_type_id(SPVM_ENV* env, const char* name);
int32_t SPVM_API_get_class_method_id(SPVM_ENV* env, const char* class_name, const char* method_name, const char* signature);
int32_t SPVM_API_get_instance_method_id(SPVM_ENV* env, SPVM_OBJECT* object, const char* method_name, const char* signature);
int32_t SPVM_API_get_instance_method_id_super(SPVM_ENV* env, SPVM_OBJECT* object, const char* method_name, const char* signature);
int32_t SPVM_API_get_instance_method_id_common(SPVM_ENV* env, SPVM_OBJECT* object, const char* method_name, const char* signature, int32_t is_parent);
int32_t SPVM_API_get_class_var_id(SPVM_ENV* env, const char* class_name, const char* class_var_name, const char* type_signature);
int32_t SPVM_API_get_field_id(SPVM_ENV* env, const char* class_name, const char* field_name, const char* signature);
int32_t SPVM_API_get_field_index(SPVM_ENV* env, int32_t field_id);
int32_t SPVM_API_get_field_offset(SPVM_ENV* env, int32_t field_id);
int32_t SPVM_API_get_instance_method_id_static(SPVM_ENV* env, const char* class_name, const char* method_name, const char* signature);
int32_t SPVM_API_object_header_byte_size(SPVM_ENV* env);

/*
  Environment APIs
*/

SPVM_ENV* SPVM_API_new_env_raw();
void SPVM_API_free_env_raw(SPVM_ENV* env);
SPVM_ENV* SPVM_API_new_env(SPVM_ENV* env);
int32_t SPVM_API_init_env(SPVM_ENV* env);
void SPVM_API_free_env(SPVM_ENV* env);
void SPVM_API_free_env_prepared(SPVM_ENV* env);
void* SPVM_API_new_memory_env(SPVM_ENV* env, size_t byte_size);
void SPVM_API_free_memory_env(SPVM_ENV* env, void* block);
int32_t SPVM_API_get_memory_blocks_count_env(SPVM_ENV* env);

/*
  Stack manipulation APIs
*/

SPVM_VALUE* SPVM_API_new_stack(SPVM_ENV* env);
void SPVM_API_free_stack(SPVM_ENV* env, SPVM_VALUE* stack);

/*
  Object manipulating APIs
  These APIs need stack argument
*/

// Call INIT blocks
void SPVM_API_call_init_blocks(SPVM_ENV* env, SPVM_VALUE* stack);

// Call Method
int32_t SPVM_API_call_spvm_method(SPVM_ENV* env, SPVM_VALUE* stack, int32_t method_id);
int32_t SPVM_API_call_spvm_method_vm(SPVM_ENV* env, SPVM_VALUE* stack, int32_t method_id);
int32_t SPVM_API_call_class_method(SPVM_ENV* env, SPVM_VALUE* stack, int32_t method_id);
int32_t SPVM_API_call_instance_method(SPVM_ENV* env, SPVM_VALUE* stack, int32_t method_id);

// Call Method by name
int32_t SPVM_API_call_class_method_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* method_name, const char* signature, const char* file, int32_t line);
int32_t SPVM_API_call_instance_method_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* method_name, const char* signature, const char* file, int32_t line);

// Cleanup global variables
void SPVM_API_cleanup_global_vars(SPVM_ENV* env, SPVM_VALUE* stack);

// Get spvm_object.h information
int32_t SPVM_API_string_length(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int8_t* SPVM_API_string_bytes(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_length(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array);
int32_t SPVM_API_get_object_type_dimension(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
int32_t SPVM_API_get_object_basic_type_id(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);

// Check type
int32_t SPVM_API_is_type(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t basic_type_id, int32_t type_dimension);
int32_t SPVM_API_is_array(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
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
int8_t SPVM_API_get_class_var_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* file, int32_t line);
int16_t SPVM_API_get_class_var_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* file, int32_t line);
int32_t SPVM_API_get_class_var_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* file, int32_t line);
int64_t SPVM_API_get_class_var_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* file, int32_t line);
float SPVM_API_get_class_var_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* file, int32_t line);
double SPVM_API_get_class_var_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t* error, const char* file, int32_t line);
SPVM_OBJECT* SPVM_API_get_class_var_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, const char* type_signature, int32_t* error, const char* file, int32_t line);

// Set class variable by name
void SPVM_API_set_class_var_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int8_t value, int32_t* error, const char* file, int32_t line);
void SPVM_API_set_class_var_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int16_t value, int32_t* error, const char* file, int32_t line);
void SPVM_API_set_class_var_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int32_t value, int32_t* error, const char* file, int32_t line);
void SPVM_API_set_class_var_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, int64_t value, int32_t* error, const char* file, int32_t line);
void SPVM_API_set_class_var_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, float value, int32_t* error, const char* file, int32_t line);
void SPVM_API_set_class_var_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, double value, int32_t* error, const char* file, int32_t line);
void SPVM_API_set_class_var_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, const char* class_var_name, const char* type_signature, SPVM_OBJECT* value, int32_t* error, const char* file, int32_t line);

// Get field
int8_t SPVM_API_get_field_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index);
int16_t SPVM_API_get_field_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index);
int32_t SPVM_API_get_field_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index);
int64_t SPVM_API_get_field_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index);
float SPVM_API_get_field_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index);
double SPVM_API_get_field_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index);
SPVM_OBJECT* SPVM_API_get_field_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index);

// Get field by name
int8_t SPVM_API_get_field_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* error, const char* file, int32_t line);
int16_t SPVM_API_get_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* error, const char* file, int32_t line);
int32_t SPVM_API_get_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* error, const char* file, int32_t line);
int64_t SPVM_API_get_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* error, const char* file, int32_t line);
float SPVM_API_get_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* error, const char* file, int32_t line);
double SPVM_API_get_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* error, const char* file, int32_t line);
SPVM_OBJECT* SPVM_API_get_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, const char* signature, int32_t* error, const char* file, int32_t line);
const char* SPVM_API_get_field_string_chars_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* obj, const char* class_name, const char* field_name, int32_t* error, const char* file, int32_t line);

// Set field
void SPVM_API_set_field_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, int8_t value);
void SPVM_API_set_field_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, int16_t value);
void SPVM_API_set_field_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, int32_t value);
void SPVM_API_set_field_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, int64_t value);
void SPVM_API_set_field_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, float value);
void SPVM_API_set_field_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, double value);
void SPVM_API_set_field_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t field_index, SPVM_OBJECT* value);

// Set field by name
void SPVM_API_set_field_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int8_t value, int32_t* error, const char* file, int32_t line);
void SPVM_API_set_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int16_t value, int32_t* error, const char* file, int32_t line);
void SPVM_API_set_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t value, int32_t* error, const char* file, int32_t line);
void SPVM_API_set_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, int64_t value, int32_t* error, const char* file, int32_t line);
void SPVM_API_set_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, float value, int32_t* error, const char* file, int32_t line);
void SPVM_API_set_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, double value, int32_t* error, const char* file, int32_t line);
void SPVM_API_set_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, const char* class_name, const char* field_name, const char* signature, SPVM_OBJECT* value, int32_t* error, const char* file, int32_t line);

// Get array information
int32_t SPVM_API_get_elem_byte_size(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array);

// Get array elements
int8_t* SPVM_API_get_elems_byte(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array);
int16_t* SPVM_API_get_elems_short(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array);
int32_t* SPVM_API_get_elems_int(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array);
int64_t* SPVM_API_get_elems_long(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array);
float* SPVM_API_get_elems_float(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array);
double* SPVM_API_get_elems_double(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array);
SPVM_OBJECT* SPVM_API_get_elem_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t index);

// Set array element
void SPVM_API_set_elem_object(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t index, SPVM_OBJECT* value);

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
SPVM_OBJECT* SPVM_API_new_pointer(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, void* ptr);
SPVM_OBJECT* SPVM_API_new_byte_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_short_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_int_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_long_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_float_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_double_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_object_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length);
SPVM_OBJECT* SPVM_API_new_muldim_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t dimension, int32_t length);
SPVM_OBJECT* SPVM_API_new_mulnum_array(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length);
SPVM_OBJECT* SPVM_API_new_string_nolen(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes);
SPVM_OBJECT* SPVM_API_new_string(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length);
SPVM_OBJECT* SPVM_API_new_array_proto(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t length);

// New object raw
SPVM_OBJECT* SPVM_API_new_object_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t class_id);
SPVM_OBJECT* SPVM_API_new_pointer_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, void* ptr);
SPVM_OBJECT* SPVM_API_new_byte_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_short_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_int_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_long_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_float_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_double_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t length);
SPVM_OBJECT* SPVM_API_new_object_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length);
SPVM_OBJECT* SPVM_API_new_muldim_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t dimension, int32_t length);
SPVM_OBJECT* SPVM_API_new_mulnum_array_raw(SPVM_ENV* env, SPVM_VALUE* stack, int32_t basic_type_id, int32_t length);
SPVM_OBJECT* SPVM_API_new_string_nolen_raw(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes);
SPVM_OBJECT* SPVM_API_new_string_raw(SPVM_ENV* env, SPVM_VALUE* stack, const char* bytes, int32_t length);
SPVM_OBJECT* SPVM_API_new_array_proto_raw(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, int32_t length);

// New object by name
void* SPVM_API_new_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, int32_t* error, const char* file, int32_t line);
SPVM_OBJECT* SPVM_API_new_pointer_by_name(SPVM_ENV* env, SPVM_VALUE* stack, const char* class_name, void* pointer, int32_t* error, const char* file, int32_t line);

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

// Dump
SPVM_OBJECT* SPVM_API_dump_raw(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
SPVM_OBJECT* SPVM_API_dump(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object);
void SPVM_API_dump_recursive(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t* depth, SPVM_STRING_BUFFER* string_buffer, SPVM_HASH* address_symtable);

// Runtime type checking
int32_t SPVM_API_isa(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* object, int32_t cast_basic_type_id, int32_t cast_type_dimension);
int32_t SPVM_API_elem_isa(SPVM_ENV* env, SPVM_VALUE* stack, SPVM_OBJECT* array, SPVM_OBJECT* element);

//  "& ~(intptr_t)1" means dropping weaken flag
#define SPVM_API_GET_OBJECT_NO_WEAKEN_ADDRESS(env, stack, object) ((void*)((intptr_t)object & ~(intptr_t)1))
#define SPVM_API_GET_REF_COUNT(env, stack, object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset)))
#define SPVM_API_INC_REF_COUNT_ONLY(env, stack, object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset))++)
#define SPVM_API_INC_REF_COUNT(env, stack, object)\
do {\
  if (object != NULL) {\
    SPVM_API_INC_REF_COUNT_ONLY(env, stack, object);\
  }\
} while (0)\

#define SPVM_API_DEC_REF_COUNT_ONLY(env, stack, object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset))--)
#define SPVM_API_DEC_REF_COUNT(env, stack, object)\
do {\
  if (object != NULL) {\
    if (SPVM_API_GET_REF_COUNT(env, stack, object) > 1) { SPVM_API_DEC_REF_COUNT_ONLY(env, stack, object); }\
    else { env->dec_ref_count(env, stack, object); }\
  }\
} while (0)\

#define SPVM_API_ISWEAK(dist_address) (((intptr_t)*(void**)dist_address) & 1)
#define SPVM_API_OBJECT_ASSIGN(env, stack, dist_address, src_object) \
do {\
  void* tmp_object = SPVM_API_GET_OBJECT_NO_WEAKEN_ADDRESS(env, stack, src_object);\
  if (tmp_object != NULL) {\
    SPVM_API_INC_REF_COUNT_ONLY(env, stack, tmp_object);\
  }\
  if (*(void**)(dist_address) != NULL) {\
    if (__builtin_expect(SPVM_API_ISWEAK(dist_address), 0)) { env->unweaken(env, stack, (void**)dist_address); }\
    if (SPVM_API_GET_REF_COUNT(env, stack, *(void**)(dist_address)) > 1) { SPVM_API_DEC_REF_COUNT_ONLY(env, stack, *(void**)(dist_address)); }\
    else { env->dec_ref_count(env, stack, *(void**)(dist_address)); }\
  }\
  *(void**)(dist_address) = tmp_object;\
} while (0)\

#endif
