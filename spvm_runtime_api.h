#ifndef SPVM_RUNTIME_API_H
#define SPVM_RUNTIME_API_H

#include "spvm_base.h"
#include "spvm_api.h"

int32_t SPVM_RUNTIME_API_get_array_length(SPVM_API* api, SPVM_ARRAY_OBJECT* array_object);
int64_t SPVM_RUNTIME_API_calcurate_base_object_byte_size(SPVM_API* api, SPVM_BASE_OBJECT* base_object);
SPVM_ARRAY_OBJECT* SPVM_RUNTIME_API_create_array_object_byte(SPVM_API* api, int32_t length);
SPVM_ARRAY_OBJECT* SPVM_RUNTIME_API_create_array_object_byte_from_pv(SPVM_API* api, const char* pv);
void SPVM_RUNTIME_API_dec_ref_count(SPVM_API* api, SPVM_BASE_OBJECT* base_object);
void SPVM_RUNTIME_API_inc_ref_count(SPVM_API* api, SPVM_BASE_OBJECT* base_object);
void SPVM_RUNTIME_API_push_stack_byte(SPVM_API* api, int8_t value);
void SPVM_RUNTIME_API_push_stack_short(SPVM_API* api, int16_t value);
void SPVM_RUNTIME_API_push_stack_int(SPVM_API* api, int32_t value);
void SPVM_RUNTIME_API_push_stack_long(SPVM_API* api, int64_t value);
void SPVM_RUNTIME_API_push_stack_float(SPVM_API* api, float value);
void SPVM_RUNTIME_API_push_stack_double(SPVM_API* api, double value);
void SPVM_RUNTIME_API_push_stack_ref(SPVM_API* api, void* value);
int8_t SPVM_RUNTIME_API_pop_stack_byte(SPVM_API* api);
int16_t SPVM_RUNTIME_API_pop_stack_short(SPVM_API* api);
int32_t SPVM_RUNTIME_API_pop_stack_int(SPVM_API* api);
int64_t SPVM_RUNTIME_API_pop_stack_long(SPVM_API* api);
float SPVM_RUNTIME_API_pop_stack_float(SPVM_API* api);
double SPVM_RUNTIME_API_pop_stack_double(SPVM_API* api);
void* SPVM_RUNTIME_API_pop_stack_address(SPVM_API* api);
int8_t SPVM_RUNTIME_API_get_var_byte(SPVM_API* api, int32_t index);
int16_t SPVM_RUNTIME_API_get_var_short(SPVM_API* api, int32_t index);
int32_t SPVM_RUNTIME_API_get_var_int(SPVM_API* api, int32_t index);
int64_t SPVM_RUNTIME_API_get_var_long(SPVM_API* api, int32_t index);
float SPVM_RUNTIME_API_get_var_float(SPVM_API* api, int32_t index);
double SPVM_RUNTIME_API_get_var_double(SPVM_API* api, int32_t index);
void* SPVM_RUNTIME_API_get_var_address(SPVM_API* api, int32_t index);

int32_t SPVM_RUNTIME_API_get_array_value_size(SPVM_API* api, int32_t type);
SPVM_VALUE* SPVM_RUNTIME_API_get_fields(SPVM_API* api, SPVM_OBJECT* object);
int32_t SPVM_RUNTIME_API_get_field_index(SPVM_API* api, SPVM_OBJECT* object, const char* name);
int32_t SPVM_RUNTIME_API_get_fields_length(SPVM_API* api, SPVM_OBJECT* object);
void SPVM_RUNTIME_API_set_byte_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index, int8_t value);
void SPVM_RUNTIME_API_set_short_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index, int16_t value);
void SPVM_RUNTIME_API_set_int_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index, int32_t value);
void SPVM_RUNTIME_API_set_long_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index, int64_t value);
void SPVM_RUNTIME_API_set_float_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index, float value);
void SPVM_RUNTIME_API_set_double_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index, double value);
int8_t SPVM_RUNTIME_API_get_byte_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index);
int16_t SPVM_RUNTIME_API_get_short_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index);
int32_t SPVM_RUNTIME_API_get_int_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index);
int64_t SPVM_RUNTIME_API_get_long_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index);
float SPVM_RUNTIME_API_get_float_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index);
double SPVM_RUNTIME_API_get_double_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index);
SPVM_BASE_OBJECT* SPVM_RUNTIME_API_get_ref_field(SPVM_API* api, SPVM_OBJECT* object, int32_t field_index);
int32_t SPVM_RUNTIME_API_dump_field_names(SPVM_API* api, SPVM_OBJECT* object);
int32_t SPVM_RUNTIME_API_get_ref_count(SPVM_API* api, SPVM_BASE_OBJECT* base_object);
int8_t* SPVM_RUNTIME_API_get_byte_array_elements(SPVM_API* api, SPVM_ARRAY_OBJECT* array_object);
int16_t* SPVM_RUNTIME_API_get_short_array_elements(SPVM_API* api, SPVM_ARRAY_OBJECT* array_object);
int32_t* SPVM_RUNTIME_API_get_int_array_elements(SPVM_API* api, SPVM_ARRAY_OBJECT* array_object);
int64_t* SPVM_RUNTIME_API_get_long_array_elements(SPVM_API* api, SPVM_ARRAY_OBJECT* array_object);
float* SPVM_RUNTIME_API_get_float_array_elements(SPVM_API* api, SPVM_ARRAY_OBJECT* array_object);
double* SPVM_RUNTIME_API_get_double_array_elements(SPVM_API* api, SPVM_ARRAY_OBJECT* array_object);
SPVM_BASE_OBJECT** SPVM_RUNTIME_API_get_ref_array_elements(SPVM_API* api, SPVM_ARRAY_OBJECT* array_object);

#endif
