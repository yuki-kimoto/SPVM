#ifndef SPVM_RUNTIME_API_H
#define SPVM_RUNTIME_API_H

#include "spvm_base.h"
#include "spvm_api.h"

int32_t SPVM_RUNTIME_API_get_array_length(SPVM_API* api, SPVM_DATA_ARRAY* data_array);
int64_t SPVM_RUNTIME_API_calcurate_data_byte_size(SPVM_API* api, SPVM_DATA* data);
SPVM_DATA_ARRAY* SPVM_RUNTIME_API_create_data_array_byte(SPVM_API* api, int32_t length);
SPVM_DATA_ARRAY* SPVM_RUNTIME_API_create_data_array_byte_from_pv(SPVM_API* api, const char* pv);
void SPVM_RUNTIME_API_dec_ref_count(SPVM_API* api, SPVM_DATA* data);
void SPVM_RUNTIME_API_inc_ref_count(SPVM_API* api, SPVM_DATA* data);
void SPVM_RUNTIME_API_push_return_value_byte(SPVM_API* api, int8_t value);
void SPVM_RUNTIME_API_push_return_value_short(SPVM_API* api, int16_t value);
void SPVM_RUNTIME_API_push_return_value_int(SPVM_API* api, int32_t value);
void SPVM_RUNTIME_API_push_return_value_long(SPVM_API* api, int64_t value);
void SPVM_RUNTIME_API_push_return_value_float(SPVM_API* api, float value);
void SPVM_RUNTIME_API_push_return_value_double(SPVM_API* api, double value);
void SPVM_RUNTIME_API_push_ret(SPVM_API* api, void* value);
int8_t SPVM_RUNTIME_API_pop_return_value_byte(SPVM_API* api);
int16_t SPVM_RUNTIME_API_pop_return_value_short(SPVM_API* api);
int32_t SPVM_RUNTIME_API_pop_return_value_int(SPVM_API* api);
int64_t SPVM_RUNTIME_API_pop_return_value_long(SPVM_API* api);
float SPVM_RUNTIME_API_pop_return_value_float(SPVM_API* api);
double SPVM_RUNTIME_API_pop_return_value_double(SPVM_API* api);
void* SPVM_RUNTIME_API_pop_return_value_address(SPVM_API* api);
int8_t SPVM_RUNTIME_API_get_var_byte(SPVM_API* api, int32_t index);
int16_t SPVM_RUNTIME_API_get_var_short(SPVM_API* api, int32_t index);
int32_t SPVM_RUNTIME_API_get_var_int(SPVM_API* api, int32_t index);
int64_t SPVM_RUNTIME_API_get_var_long(SPVM_API* api, int32_t index);
float SPVM_RUNTIME_API_get_var_float(SPVM_API* api, int32_t index);
double SPVM_RUNTIME_API_get_var_double(SPVM_API* api, int32_t index);
void* SPVM_RUNTIME_API_get_var_address(SPVM_API* api, int32_t index);
void SPVM_RUNTIME_API_push_var_byte(SPVM_API* api, int8_t value);
void SPVM_RUNTIME_API_push_var_short(SPVM_API* api, int16_t value);
void SPVM_RUNTIME_API_push_var_int(SPVM_API* api, int32_t value);
void SPVM_RUNTIME_API_push_var_long(SPVM_API* api, int64_t value);
void SPVM_RUNTIME_API_push_var_float(SPVM_API* api, float value);
void SPVM_RUNTIME_API_push_var_double(SPVM_API* api, double value);
void SPVM_RUNTIME_API_push_var_address(SPVM_API* api, void* value);


int32_t SPVM_RUNTIME_API_get_array_value_size(SPVM_API* api, int32_t type);
SPVM_VALUE* SPVM_RUNTIME_API_get_fields(SPVM_API* api, SPVM_DATA_OBJECT* data_object);
int32_t SPVM_RUNTIME_API_get_field_index(SPVM_API* api, SPVM_DATA_OBJECT* data_object, const char* name);
int32_t SPVM_RUNTIME_API_get_fields_length(SPVM_API* api, SPVM_DATA_OBJECT* data_object);
void SPVM_RUNTIME_API_set_byte_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index, int8_t value);
void SPVM_RUNTIME_API_set_short_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index, int16_t value);
void SPVM_RUNTIME_API_set_int_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index, int32_t value);
void SPVM_RUNTIME_API_set_long_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index, int64_t value);
void SPVM_RUNTIME_API_set_float_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index, float value);
void SPVM_RUNTIME_API_set_double_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index, double value);
int8_t SPVM_RUNTIME_API_get_byte_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index);
int16_t SPVM_RUNTIME_API_get_short_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index);
int32_t SPVM_RUNTIME_API_get_int_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index);
int64_t SPVM_RUNTIME_API_get_long_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index);
float SPVM_RUNTIME_API_get_float_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index);
double SPVM_RUNTIME_API_get_double_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index);
SPVM_DATA* SPVM_RUNTIME_API_get_ref_field(SPVM_API* api, SPVM_DATA_OBJECT* data_object, int32_t field_index);
int32_t SPVM_RUNTIME_API_dump_field_names(SPVM_API* api, SPVM_DATA_OBJECT* data_object);
int32_t SPVM_RUNTIME_API_get_ref_count(SPVM_API* api, SPVM_DATA* data);
int8_t* SPVM_RUNTIME_API_get_byte_array_elements(SPVM_API* api, SPVM_DATA_ARRAY* data_array);
int16_t* SPVM_RUNTIME_API_get_short_array_elements(SPVM_API* api, SPVM_DATA_ARRAY* data_array);
int32_t* SPVM_RUNTIME_API_get_int_array_elements(SPVM_API* api, SPVM_DATA_ARRAY* data_array);
int64_t* SPVM_RUNTIME_API_get_long_array_elements(SPVM_API* api, SPVM_DATA_ARRAY* data_array);
float* SPVM_RUNTIME_API_get_float_array_elements(SPVM_API* api, SPVM_DATA_ARRAY* data_array);
double* SPVM_RUNTIME_API_get_double_array_elements(SPVM_API* api, SPVM_DATA_ARRAY* data_array);
SPVM_DATA** SPVM_RUNTIME_API_get_ref_array_elements(SPVM_API* api, SPVM_DATA_ARRAY* data_array);

#endif
