#ifndef SPVM_API_H
#define SPVM_API_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

/*
  "& ~(intptr_t)1" means dropping weaken flag
*/

#define SPVM_API_GET_OBJECT_NO_WEAKEN_ADDRESS(object) ((void*)((intptr_t)object & ~(intptr_t)1))
#define SPVM_API_GET_REF_COUNT(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset)))
#define SPVM_API_INC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset))++)
#define SPVM_API_INC_REF_COUNT(object)\
do {\
  if (object != NULL) {\
    SPVM_API_INC_REF_COUNT_ONLY(object);\
  }\
} while (0)\

#define SPVM_API_DEC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset))--)
#define SPVM_API_DEC_REF_COUNT(object)\
do {\
  if (object != NULL) {\
    if (SPVM_API_GET_REF_COUNT(object) > 1) { SPVM_API_DEC_REF_COUNT_ONLY(object); }\
    else { env->dec_ref_count(env, object); }\
  }\
} while (0)\

#define SPVM_API_ISWEAK(dist_address) (((intptr_t)*(void**)dist_address) & 1)
#define SPVM_API_OBJECT_ASSIGN(dist_address, src_object) \
do {\
  void* tmp_object = SPVM_API_GET_OBJECT_NO_WEAKEN_ADDRESS(src_object);\
  if (tmp_object != NULL) {\
    SPVM_API_INC_REF_COUNT_ONLY(tmp_object);\
  }\
  if (*(void**)(dist_address) != NULL) {\
    if (__builtin_expect(SPVM_API_ISWEAK(dist_address), 0)) { env->unweaken(env, (void**)dist_address); }\
    if (SPVM_API_GET_REF_COUNT(*(void**)(dist_address)) > 1) { SPVM_API_DEC_REF_COUNT_ONLY(*(void**)(dist_address)); }\
    else { env->dec_ref_count(env, *(void**)(dist_address)); }\
  }\
  *(void**)(dist_address) = tmp_object;\
} while (0)\

void* SPVM_API_new_object_by_name(SPVM_ENV* env, const char* class_name, int32_t* exception_flag, const char* file, int32_t line);

int32_t SPVM_API_die(SPVM_ENV* env, const char* message, ...);

int32_t SPVM_API_remove_mortal(SPVM_ENV* env, int32_t original_mortal_stack_top, SPVM_OBJECT* remove_object);

int32_t SPVM_API_is_utf8(SPVM_ENV* env, SPVM_OBJECT* object);

SPVM_ENV* SPVM_API_new_env(SPVM_ENV* env);
SPVM_ENV* SPVM_API_create_env(SPVM_COMPILER* compiler);
SPVM_RUNTIME* SPVM_API_build_runtime(SPVM_COMPILER* compiler);
void SPVM_API_free_env(SPVM_ENV* env);
void SPVM_API_free_runtime(SPVM_RUNTIME* runtime);

void SPVM_API_call_init_blocks(SPVM_ENV* env);

int32_t SPVM_API_is_type(SPVM_ENV* env, SPVM_OBJECT* object, int32_t basic_type_id, int32_t type_dimension);
int32_t SPVM_API_is_array(SPVM_ENV* env, SPVM_OBJECT* object);
int32_t SPVM_API_is_string(SPVM_ENV* env, SPVM_OBJECT* object);
int32_t SPVM_API_is_numeric_array(SPVM_ENV* env, SPVM_OBJECT* object);
int32_t SPVM_API_is_mulnum_array(SPVM_ENV* env, SPVM_OBJECT* object);
int32_t SPVM_API_get_elem_byte_size(SPVM_ENV* env, SPVM_OBJECT* array);
int32_t SPVM_API_has_callback(SPVM_ENV* env, SPVM_OBJECT* object, int32_t callback_basic_type_id);

SPVM_METHOD* SPVM_API_method(SPVM_ENV* env, SPVM_CLASS* class, const char* method_name);

SPVM_BASIC_TYPE* SPVM_API_get_basic_type(SPVM_ENV* env,  const char* basic_type_name);
SPVM_CLASS_VAR* SPVM_API_class_var(SPVM_ENV* env, SPVM_CLASS* class, const char* class_var_name);

// Get
int32_t SPVM_API_object_header_byte_size(SPVM_ENV* env);
int32_t SPVM_API_length(SPVM_ENV* env, SPVM_OBJECT* array);

int8_t* SPVM_API_get_elems_byte(SPVM_ENV* env, SPVM_OBJECT* array);
int16_t* SPVM_API_get_elems_short(SPVM_ENV* env, SPVM_OBJECT* array);
int32_t* SPVM_API_get_elems_int(SPVM_ENV* env, SPVM_OBJECT* array);
int64_t* SPVM_API_get_elems_long(SPVM_ENV* env, SPVM_OBJECT* array);
float* SPVM_API_get_elems_float(SPVM_ENV* env, SPVM_OBJECT* array);
double* SPVM_API_get_elems_double(SPVM_ENV* env, SPVM_OBJECT* array);


SPVM_OBJECT* SPVM_API_get_elem_object(SPVM_ENV* env, SPVM_OBJECT* array, int32_t index);
void* SPVM_API_pointer(SPVM_ENV* env, SPVM_OBJECT* object);
int8_t SPVM_API_get_field_byte(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index);
int16_t SPVM_API_get_field_short(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index);
int32_t SPVM_API_get_field_int(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index);
int64_t SPVM_API_get_field_long(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index);
float SPVM_API_get_field_float(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index);
double SPVM_API_get_field_double(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index);
SPVM_OBJECT* SPVM_API_get_field_object(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index);

// Set
void SPVM_API_set_field_byte(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, int8_t value);
void SPVM_API_set_field_short(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, int16_t value);
void SPVM_API_set_field_int(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, int32_t value);
void SPVM_API_set_field_long(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, int64_t value);
void SPVM_API_set_field_float(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, float value);
void SPVM_API_set_field_double(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, double value);
void SPVM_API_set_field_object(SPVM_ENV* env, SPVM_OBJECT* object, int32_t field_index, SPVM_OBJECT* value);
void SPVM_API_set_elem_object(SPVM_ENV* env, SPVM_OBJECT* array, int32_t index, SPVM_OBJECT* value);
void SPVM_API_set_pointer(SPVM_ENV* env, SPVM_OBJECT* object, void* ptr);

// Call Method
void SPVM_API_call_void_method(SPVM_ENV* env, int32_t method_id, SPVM_VALUE* args);
int8_t SPVM_API_call_byte_method(SPVM_ENV* env, int32_t method_id, SPVM_VALUE* args);
int16_t SPVM_API_call_short_method(SPVM_ENV* env, int32_t method_id, SPVM_VALUE* args);
int32_t SPVM_API_call_int_method(SPVM_ENV* env, int32_t method_id, SPVM_VALUE* args);
int64_t SPVM_API_call_long_method(SPVM_ENV* env, int32_t method_id, SPVM_VALUE* args);
float SPVM_API_call_float_method(SPVM_ENV* env, int32_t method_id, SPVM_VALUE* args);
double SPVM_API_call_double_method(SPVM_ENV* env, int32_t method_id, SPVM_VALUE* args);
SPVM_OBJECT* SPVM_API_call_object_method(SPVM_ENV* env, int32_t method_id, SPVM_VALUE* args);

// String
int32_t SPVM_API_string_length(SPVM_ENV* env, SPVM_OBJECT* object);
int8_t* SPVM_API_string_bytes(SPVM_ENV* env, SPVM_OBJECT* object);
void SPVM_API_print(SPVM_ENV* env, SPVM_OBJECT* string);
SPVM_OBJECT* SPVM_API_concat_raw(SPVM_ENV* env, SPVM_OBJECT* string1, SPVM_OBJECT* string2);
SPVM_OBJECT* SPVM_API_concat(SPVM_ENV* env, SPVM_OBJECT* string1, SPVM_OBJECT* string2);

// ID
int32_t SPVM_API_get_basic_type_id(SPVM_ENV* env, const char* name);
int32_t SPVM_API_get_class_method_id(SPVM_ENV* env, const char* class_name, const char* method_name, const char* signature);
int32_t SPVM_API_get_instance_method_id(SPVM_ENV* env, SPVM_OBJECT* object, const char* method_name, const char* signature);
int32_t SPVM_API_get_class_var_id(SPVM_ENV* env, const char* class_name, const char* class_var_name, const char* type_signature);
int32_t SPVM_API_get_field_id(SPVM_ENV* env, const char* class_name, const char* field_name, const char* signature);
int32_t SPVM_API_get_field_index(SPVM_ENV* env, int32_t field_id);
int32_t SPVM_API_get_field_offset(SPVM_ENV* env, int32_t field_id);

// New
SPVM_OBJECT* SPVM_API_new_object(SPVM_ENV* env, int32_t class_id);
SPVM_OBJECT* SPVM_API_new_pointer(SPVM_ENV* env, int32_t basic_type_id, void* ptr);
SPVM_OBJECT* SPVM_API_new_byte_array(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_API_new_short_array(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_API_new_int_array(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_API_new_long_array(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_API_new_float_array(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_API_new_double_array(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_API_new_object_array(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
SPVM_OBJECT* SPVM_API_new_muldim_array(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t length);
SPVM_OBJECT* SPVM_API_new_mulnum_array(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
SPVM_OBJECT* SPVM_API_new_string_nolen(SPVM_ENV* env, const char* bytes);
SPVM_OBJECT* SPVM_API_new_string(SPVM_ENV* env, const char* bytes, int32_t length);

int32_t SPVM_API_get_bool_object_value(SPVM_ENV* env, SPVM_OBJECT* bool_object);

// New raw
SPVM_OBJECT* SPVM_API_new_object_raw(SPVM_ENV* env, int32_t class_id);
SPVM_OBJECT* SPVM_API_new_pointer_raw(SPVM_ENV* env, int32_t basic_type_id, void* ptr);
SPVM_OBJECT* SPVM_API_new_byte_array_raw(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_API_new_short_array_raw(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_API_new_int_array_raw(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_API_new_long_array_raw(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_API_new_float_array_raw(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_API_new_double_array_raw(SPVM_ENV* env, int32_t length);
SPVM_OBJECT* SPVM_API_new_object_array_raw(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
SPVM_OBJECT* SPVM_API_new_muldim_array_raw(SPVM_ENV* env, int32_t basic_type_id, int32_t dimension, int32_t length);
SPVM_OBJECT* SPVM_API_new_mulnum_array_raw(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
SPVM_OBJECT* SPVM_API_new_string_nolen_raw(SPVM_ENV* env, const char* bytes);
SPVM_OBJECT* SPVM_API_new_string_raw(SPVM_ENV* env, const char* bytes, int32_t length);

// Exception
int32_t SPVM_API_set_exception(SPVM_ENV* env, SPVM_OBJECT* exception);
SPVM_OBJECT* SPVM_API_exception(SPVM_ENV* env);
SPVM_OBJECT* SPVM_API_new_stack_trace_raw(SPVM_ENV* env, SPVM_OBJECT* exception, const char* class_name, const char* method_name, const char* file, int32_t line);
SPVM_OBJECT* SPVM_API_new_stack_trace(SPVM_ENV* env, SPVM_OBJECT* exception, const char* class_name, const char* method_name, const char* file, int32_t line);

// Reference count
void SPVM_API_inc_ref_count(SPVM_ENV* env, SPVM_OBJECT* object);
void SPVM_API_dec_ref_count(SPVM_ENV* env, SPVM_OBJECT* object);
int32_t SPVM_API_ref_count(SPVM_ENV* env, SPVM_OBJECT* object);

// Weak refernece
int32_t SPVM_API_weaken(SPVM_ENV* env, SPVM_OBJECT** object_address);
void SPVM_API_unweaken(SPVM_ENV* env, SPVM_OBJECT** object_address);
int32_t SPVM_API_isweak(SPVM_ENV* env, SPVM_OBJECT** object_address);

// Global information
SPVM_ENV* SPVM_API_env_runtime();
int32_t SPVM_API_get_memory_blocks_count(SPVM_ENV* env);

// Scope
int32_t SPVM_API_enter_scope(SPVM_ENV* env);
int32_t SPVM_API_push_mortal(SPVM_ENV* env, SPVM_OBJECT* object);
void SPVM_API_leave_scope(SPVM_ENV* env, int32_t original_mortal_stack_top);

// Call method
int32_t SPVM_API_call_spvm_method(SPVM_ENV* env, int32_t method_id, SPVM_VALUE* stack);
int32_t SPVM_API_call_spvm_method_vm(SPVM_ENV* env, int32_t method_id, SPVM_VALUE* stack);

void* SPVM_API_alloc_memory_block_zero(SPVM_ENV* env, size_t byte_size);
void SPVM_API_free_memory_block(SPVM_ENV* env, void* block);
void* SPVM_API_safe_malloc_zero(int64_t byte_size);

SPVM_OBJECT* SPVM_API_i_to_string_raw(SPVM_ENV* env, int32_t value);
SPVM_OBJECT* SPVM_API_i_to_string(SPVM_ENV* env, int32_t value);
SPVM_OBJECT* SPVM_API_l_to_string_raw(SPVM_ENV* env, int64_t value);
SPVM_OBJECT* SPVM_API_l_to_string(SPVM_ENV* env, int64_t value);
SPVM_OBJECT* SPVM_API_f_to_string_raw(SPVM_ENV* env, float value);
SPVM_OBJECT* SPVM_API_f_to_string(SPVM_ENV* env, float value);
SPVM_OBJECT* SPVM_API_d_to_string_raw(SPVM_ENV* env, double value);
SPVM_OBJECT* SPVM_API_d_to_string(SPVM_ENV* env, double value);

// Class variable access
int8_t SPVM_API_get_class_var_byte(SPVM_ENV* env, int32_t class_var_id);
int16_t SPVM_API_get_class_var_short(SPVM_ENV* env, int32_t class_var_id);
int32_t SPVM_API_get_class_var_int(SPVM_ENV* env, int32_t class_var_id);
int64_t SPVM_API_get_class_var_long(SPVM_ENV* env, int32_t class_var_id);
float SPVM_API_get_class_var_float(SPVM_ENV* env, int32_t class_var_id);
double SPVM_API_get_class_var_double(SPVM_ENV* env, int32_t class_var_id);
SPVM_OBJECT* SPVM_API_get_class_var_object(SPVM_ENV* env, int32_t class_var_id);
void SPVM_API_set_class_var_byte(SPVM_ENV* env, int32_t class_var_id, int8_t value);
void SPVM_API_set_class_var_short(SPVM_ENV* env, int32_t class_var_id, int16_t value);
void SPVM_API_set_class_var_int(SPVM_ENV* env, int32_t class_var_id, int32_t value);
void SPVM_API_set_class_var_long(SPVM_ENV* env, int32_t class_var_id, int64_t value);
void SPVM_API_set_class_var_float(SPVM_ENV* env, int32_t class_var_id, float value);
void SPVM_API_set_class_var_double(SPVM_ENV* env, int32_t class_var_id, double value);
void SPVM_API_set_class_var_object(SPVM_ENV* env, int32_t class_var_id, SPVM_OBJECT* value);

SPVM_OBJECT* SPVM_API_get_type_name_raw(SPVM_ENV* env, SPVM_OBJECT* object);
SPVM_OBJECT* SPVM_API_get_type_name(SPVM_ENV* env, SPVM_OBJECT* object);

int32_t SPVM_API_object_type_dimension(SPVM_ENV* env, SPVM_OBJECT* object);
int32_t SPVM_API_object_basic_type_id(SPVM_ENV* env, SPVM_OBJECT* object);

const char* SPVM_API_get_chars(SPVM_ENV* env, SPVM_OBJECT* string);

void SPVM_API_make_read_only(SPVM_ENV* env, SPVM_OBJECT* string);
int32_t SPVM_API_is_read_only(SPVM_ENV* env, SPVM_OBJECT* string);

SPVM_OBJECT* SPVM_API_new_pointer_by_name(SPVM_ENV* env, const char* class_name, void* pointer, int32_t* exception_flag, const char* file, int32_t line);
void SPVM_API_set_field_byte_by_name(SPVM_ENV* env, SPVM_OBJECT* object, const char* class_name, const char* field_name, int8_t value, int32_t* exception_flag, const char* file, int32_t line);
void SPVM_API_set_field_short_by_name(SPVM_ENV* env, SPVM_OBJECT* object, const char* class_name, const char* field_name, int16_t value, int32_t* exception_flag, const char* file, int32_t line);
void SPVM_API_set_field_int_by_name(SPVM_ENV* env, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t value, int32_t* exception_flag, const char* file, int32_t line);
void SPVM_API_set_field_long_by_name(SPVM_ENV* env, SPVM_OBJECT* object, const char* class_name, const char* field_name, int64_t value, int32_t* exception_flag, const char* file, int32_t line);
void SPVM_API_set_field_float_by_name(SPVM_ENV* env, SPVM_OBJECT* object, const char* class_name, const char* field_name, float value, int32_t* exception_flag, const char* file, int32_t line);
void SPVM_API_set_field_double_by_name(SPVM_ENV* env, SPVM_OBJECT* object, const char* class_name, const char* field_name, double value, int32_t* exception_flag, const char* file, int32_t line);
void SPVM_API_set_field_object_by_name(SPVM_ENV* env, SPVM_OBJECT* object, const char* class_name, const char* field_name, const char* signature, SPVM_OBJECT* value, int32_t* exception_flag, const char* file, int32_t line);
int8_t SPVM_API_get_field_byte_by_name(SPVM_ENV* env, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* exception_flag, const char* file, int32_t line);
int16_t SPVM_API_get_field_short_by_name(SPVM_ENV* env, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* exception_flag, const char* file, int32_t line);
int32_t SPVM_API_get_field_int_by_name(SPVM_ENV* env, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* exception_flag, const char* file, int32_t line);
int64_t SPVM_API_get_field_long_by_name(SPVM_ENV* env, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* exception_flag, const char* file, int32_t line);
float SPVM_API_get_field_float_by_name(SPVM_ENV* env, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* exception_flag, const char* file, int32_t line);
double SPVM_API_get_field_double_by_name(SPVM_ENV* env, SPVM_OBJECT* object, const char* class_name, const char* field_name, int32_t* exception_flag, const char* file, int32_t line);
SPVM_OBJECT* SPVM_API_get_field_object_by_name(SPVM_ENV* env, SPVM_OBJECT* object, const char* class_name, const char* field_name, const char* signature, int32_t* exception_flag, const char* file, int32_t line);

// Class Variable access by name
void SPVM_API_set_class_var_byte_by_name(SPVM_ENV* env, const char* class_name, const char* class_var_name, int8_t value, int32_t* exception_flag, const char* file, int32_t line);
void SPVM_API_set_class_var_short_by_name(SPVM_ENV* env, const char* class_name, const char* class_var_name, int16_t value, int32_t* exception_flag, const char* file, int32_t line);
void SPVM_API_set_class_var_int_by_name(SPVM_ENV* env, const char* class_name, const char* class_var_name, int32_t value, int32_t* exception_flag, const char* file, int32_t line);
void SPVM_API_set_class_var_long_by_name(SPVM_ENV* env, const char* class_name, const char* class_var_name, int64_t value, int32_t* exception_flag, const char* file, int32_t line);
void SPVM_API_set_class_var_float_by_name(SPVM_ENV* env, const char* class_name, const char* class_var_name, float value, int32_t* exception_flag, const char* file, int32_t line);
void SPVM_API_set_class_var_double_by_name(SPVM_ENV* env, const char* class_name, const char* class_var_name, double value, int32_t* exception_flag, const char* file, int32_t line);
void SPVM_API_set_class_var_object_by_name(SPVM_ENV* env, const char* class_name, const char* class_var_name, const char* type_signature, SPVM_OBJECT* value, int32_t* exception_flag, const char* file, int32_t line);
int8_t SPVM_API_get_class_var_byte_by_name(SPVM_ENV* env, const char* class_name, const char* class_var_name, int32_t* exception_flag, const char* file, int32_t line);
int16_t SPVM_API_get_class_var_short_by_name(SPVM_ENV* env, const char* class_name, const char* class_var_name, int32_t* exception_flag, const char* file, int32_t line);
int32_t SPVM_API_get_class_var_int_by_name(SPVM_ENV* env, const char* class_name, const char* class_var_name, int32_t* exception_flag, const char* file, int32_t line);
int64_t SPVM_API_get_class_var_long_by_name(SPVM_ENV* env, const char* class_name, const char* class_var_name, int32_t* exception_flag, const char* file, int32_t line);
float SPVM_API_get_class_var_float_by_name(SPVM_ENV* env, const char* class_name, const char* class_var_name, int32_t* exception_flag, const char* file, int32_t line);
double SPVM_API_get_class_var_double_by_name(SPVM_ENV* env, const char* class_name, const char* class_var_name, int32_t* exception_flag, const char* file, int32_t line);
SPVM_OBJECT* SPVM_API_get_class_var_object_by_name(SPVM_ENV* env, const char* class_name, const char* class_var_name, const char* type_signature, int32_t* exception_flag, const char* file, int32_t line);

int32_t SPVM_API_call_class_method_by_name(SPVM_ENV* env, const char* class_name, const char* method_name, const char* signature, SPVM_VALUE* stack, const char* file, int32_t line);
int32_t SPVM_API_call_instance_method_by_name(SPVM_ENV* env, SPVM_OBJECT* object, const char* method_name, const char* signature, SPVM_VALUE* stack, const char* file, int32_t line);
const char* SPVM_API_get_field_string_chars_by_name(SPVM_ENV* env, SPVM_OBJECT* obj, const char* class_name, const char* field_name, int32_t* exception_flag, const char* file, int32_t line);

SPVM_OBJECT* SPVM_API_dump_raw(SPVM_ENV* env, SPVM_OBJECT* object);
SPVM_OBJECT* SPVM_API_dump(SPVM_ENV* env, SPVM_OBJECT* object);
void SPVM_API_dump_recursive(SPVM_ENV* env, SPVM_OBJECT* object, int32_t* depth, SPVM_STRING_BUFFER* string_buffer, SPVM_HASH* address_symtable);

SPVM_CLASS_VAR* SPVM_API_get_class_var(SPVM_ENV* env, SPVM_CLASS* class, const char* class_var_name);
SPVM_METHOD* SPVM_API_get_method(SPVM_ENV* env, SPVM_CLASS* class, const char* method_name);

int32_t SPVM_API_get_instance_method_id_static(SPVM_ENV* env, const char* class_name, const char* method_name, const char* signature);

#endif
