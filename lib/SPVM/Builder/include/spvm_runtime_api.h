#ifndef SPVM_RUNTIME_API_H
#define SPVM_RUNTIME_API_H

#include "spvm_base.h"
#include "spvm_native.h"

/*
  "& ~(intptr_t)1" means dropping weaken flag
*/

#define SPVM_RUNTIME_API_GET_OBJECT_NO_WEAKEN_ADDRESS(object) ((void*)((intptr_t)object & ~(intptr_t)1))
#define SPVM_RUNTIME_API_GET_REF_COUNT(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_byte_offset)))
#define SPVM_RUNTIME_API_INC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_byte_offset))++)
#define SPVM_RUNTIME_API_INC_REF_COUNT(object)\
do {\
  if (object != NULL) {\
    SPVM_RUNTIME_API_INC_REF_COUNT_ONLY(object);\
  }\
} while (0)\

#define SPVM_RUNTIME_API_DEC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_byte_offset))--)
#define SPVM_RUNTIME_API_DEC_REF_COUNT(object)\
do {\
  if (object != NULL) {\
    if (SPVM_RUNTIME_API_GET_REF_COUNT(object) > 1) { SPVM_RUNTIME_API_DEC_REF_COUNT_ONLY(object); }\
    else { env->dec_ref_count(env, object); }\
  }\
} while (0)\

#define SPVM_RUNTIME_API_ISWEAK(dist_address) (((intptr_t)*(void**)dist_address) & 1)
#define SPVM_RUNTIME_API_OBJECT_ASSIGN(dist_address, src_object) \
do {\
  void* tmp_object = src_object;\
  if (tmp_object != NULL) {\
    SPVM_RUNTIME_API_INC_REF_COUNT_ONLY(tmp_object);\
  }\
  if (*(void**)(dist_address) != NULL) {\
    if (SPVM_RUNTIME_API_ISWEAK(dist_address)) { env->unweaken(env, (void**)dist_address); }\
    if (SPVM_RUNTIME_API_GET_REF_COUNT(*(void**)(dist_address)) > 1) { SPVM_RUNTIME_API_DEC_REF_COUNT_ONLY(*(void**)(dist_address)); }\
    else { env->dec_ref_count(env, *(void**)(dist_address)); }\
  }\
  *(void**)(dist_address) = tmp_object;\
} while (0)\

SPVM_ENV* SPVM_RUNTIME_API_new_env(SPVM_ENV* env);
SPVM_ENV* SPVM_RUNTIME_API_create_env(SPVM_RUNTIME* runtime);
SPVM_RUNTIME* SPVM_RUNTIME_API_build_runtime(SPVM_PORTABLE* portable);
void SPVM_RUNTIME_API_free_env(SPVM_ENV* env);
void SPVM_RUNTIME_API_free_runtime(SPVM_RUNTIME* runtime);

void SPVM_RUNTIME_API_call_begin_blocks(SPVM_ENV* env);

int32_t SPVM_RUNTIME_API_has_interface(SPVM_ENV* env, SPVM_OBJECT* object, int32_t interface_basic_type_id);

int32_t SPVM_RUNTIME_API_call_entry_point_sub(SPVM_ENV* env, const char* package_name, int32_t argc, const char *argv[]);

SPVM_RUNTIME_SUB* SPVM_RUNTIME_API_get_sub(SPVM_ENV* env, SPVM_RUNTIME_PACKAGE* package, const char* sub_name);

SPVM_RUNTIME_BASIC_TYPE* SPVM_RUNTIME_API_get_basic_type(SPVM_ENV* env,  const char* basic_type_name);

// Get
int32_t SPVM_RUNTIME_API_get_object_header_byte_size(SPVM_ENV* env);
int32_t SPVM_RUNTIME_API_get_array_length(SPVM_ENV* env, SPVM_OBJECT* array);

int8_t* SPVM_RUNTIME_API_get_byte_array_elements_new(SPVM_ENV* env, SPVM_OBJECT* array);
int16_t* SPVM_RUNTIME_API_get_short_array_elements_new(SPVM_ENV* env, SPVM_OBJECT* array);
int32_t* SPVM_RUNTIME_API_get_int_array_elements_new(SPVM_ENV* env, SPVM_OBJECT* array);
int64_t* SPVM_RUNTIME_API_get_long_array_elements_new(SPVM_ENV* env, SPVM_OBJECT* array);
float* SPVM_RUNTIME_API_get_float_array_elements_new(SPVM_ENV* env, SPVM_OBJECT* array);
double* SPVM_RUNTIME_API_get_double_array_elements_new(SPVM_ENV* env, SPVM_OBJECT* array);


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
int32_t SPVM_RUNTIME_API_get_sub_id(SPVM_ENV* env, const char* package_name, const char* sub_name, const char* signature);
int32_t SPVM_RUNTIME_API_get_sub_id_method_call(SPVM_ENV* env, SPVM_OBJECT* object, const char* sub_name, const char* signature);
int32_t SPVM_RUNTIME_API_get_package_var_id(SPVM_ENV* env, const char* package_name, const char* package_var_name, const char* signature);
int32_t SPVM_RUNTIME_API_get_field_id(SPVM_ENV* env, const char* package_name, const char* field_name, const char* signature);
int32_t SPVM_RUNTIME_API_get_field_index(SPVM_ENV* env, int32_t field_id);
int32_t SPVM_RUNTIME_API_get_field_byte_offset(SPVM_ENV* env, int32_t field_id);

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
SPVM_OBJECT* SPVM_RUNTIME_API_new_value_array(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
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
SPVM_OBJECT* SPVM_RUNTIME_API_new_value_array_raw(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
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
void SPVM_RUNTIME_API_weaken(SPVM_ENV* env, SPVM_OBJECT** object_address);
void SPVM_RUNTIME_API_unweaken(SPVM_ENV* env, SPVM_OBJECT** object_address);
int32_t SPVM_RUNTIME_API_isweak(SPVM_ENV* env, SPVM_OBJECT** object_address);

// Global information
SPVM_ENV* SPVM_RUNTIME_API_get_env_runtime();
int32_t SPVM_RUNTIME_API_get_memory_blocks_count(SPVM_ENV* env);

// Scope
int32_t SPVM_RUNTIME_API_enter_scope(SPVM_ENV* env);
void SPVM_RUNTIME_API_push_mortal(SPVM_ENV* env, SPVM_OBJECT* object);
void SPVM_RUNTIME_API_leave_scope(SPVM_ENV* env, int32_t original_mortal_stack_top);

// Call subroutine
int32_t SPVM_RUNTIME_API_call_sub(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* stack);
int32_t SPVM_RUNTIME_API_call_sub_vm(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* stack);

void* SPVM_RUNTIME_API_alloc_memory_block_zero(SPVM_ENV* env, int64_t byte_size);
void SPVM_RUNTIME_API_free_memory_block(SPVM_ENV* env, void* block);
void* SPVM_RUNTIME_API_safe_malloc_zero(int64_t byte_size);

#endif
