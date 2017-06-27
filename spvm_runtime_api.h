#ifndef SPVM_RUNTIME_API_H
#define SPVM_RUNTIME_API_H

#include "spvm_base.h"

int64_t SPVM_RUNTIME_API_calcurate_data_byte_size(SPVM_RUNTIME* runtime, SPVM_DATA* data);
SPVM_DATA_ARRAY* SPVM_RUNTIME_API_create_data_array_byte(SPVM_RUNTIME* runtime, int32_t length);
SPVM_DATA_ARRAY* SPVM_RUNTIME_API_create_data_array_byte_from_pv(SPVM_RUNTIME* runtime, const char* pv);
void SPVM_RUNTIME_API_dec_ref_count(SPVM_RUNTIME* runtime, SPVM_DATA* data);
void SPVM_RUNTIME_API_inc_ref_count(SPVM_RUNTIME* runtime, SPVM_DATA* data);
void SPVM_RUNTIME_API_push_return_value_byte(SPVM_RUNTIME* runtime, int8_t value);
void SPVM_RUNTIME_API_push_return_value_short(SPVM_RUNTIME* runtime, int16_t value);
void SPVM_RUNTIME_API_push_return_value_int(SPVM_RUNTIME* runtime, int32_t value);
void SPVM_RUNTIME_API_push_return_value_long(SPVM_RUNTIME* runtime, int64_t value);
void SPVM_RUNTIME_API_push_return_value_float(SPVM_RUNTIME* runtime, float value);
void SPVM_RUNTIME_API_push_return_value_double(SPVM_RUNTIME* runtime, double value);
void SPVM_RUNTIME_API_push_ret(SPVM_RUNTIME* runtime, void* value);
int8_t SPVM_RUNTIME_API_pop_return_value_byte(SPVM_RUNTIME* runtime);
int16_t SPVM_RUNTIME_API_pop_return_value_short(SPVM_RUNTIME* runtime);
int32_t SPVM_RUNTIME_API_pop_return_value_int(SPVM_RUNTIME* runtime);
int64_t SPVM_RUNTIME_API_pop_return_value_long(SPVM_RUNTIME* runtime);
float SPVM_RUNTIME_API_pop_return_value_float(SPVM_RUNTIME* runtime);
double SPVM_RUNTIME_API_pop_return_value_double(SPVM_RUNTIME* runtime);
void* SPVM_RUNTIME_API_pop_return_value_address(SPVM_RUNTIME* runtime);
int8_t SPVM_RUNTIME_API_get_var_byte(SPVM_RUNTIME* runtime, int32_t index);
int16_t SPVM_RUNTIME_API_get_var_short(SPVM_RUNTIME* runtime, int32_t index);
int32_t SPVM_RUNTIME_API_get_var_int(SPVM_RUNTIME* runtime, int32_t index);
int64_t SPVM_RUNTIME_API_get_var_long(SPVM_RUNTIME* runtime, int32_t index);
float SPVM_RUNTIME_API_get_var_float(SPVM_RUNTIME* runtime, int32_t index);
double SPVM_RUNTIME_API_get_var_double(SPVM_RUNTIME* runtime, int32_t index);
void* SPVM_RUNTIME_API_get_var_address(SPVM_RUNTIME* runtime, int32_t index);
void SPVM_RUNTIME_API_push_var_byte(SPVM_RUNTIME* runtime, int8_t value);
void SPVM_RUNTIME_API_push_var_short(SPVM_RUNTIME* runtime, int16_t value);
void SPVM_RUNTIME_API_push_var_int(SPVM_RUNTIME* runtime, int32_t value);
void SPVM_RUNTIME_API_push_var_long(SPVM_RUNTIME* runtime, int64_t value);
void SPVM_RUNTIME_API_push_var_float(SPVM_RUNTIME* runtime, float value);
void SPVM_RUNTIME_API_push_var_double(SPVM_RUNTIME* runtime, double value);
void SPVM_RUNTIME_API_push_var_address(SPVM_RUNTIME* runtime, void* value);


int32_t SPVM_API_get_array_value_size(SPVM_ENV* env, int32_t type);
SPVM_VALUE* SPVM_API_get_object_fields(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object);
int32_t SPVM_API_get_object_field_index(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name);
int32_t SPVM_API_get_object_fields_length(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object);
void SPVM_API_set_object_field_value_byte(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name, int8_t value);
void SPVM_API_set_object_field_value_short(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name, int16_t value);
void SPVM_API_set_object_field_value_int(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name, int32_t value);
void SPVM_API_set_object_field_value_long(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name, int64_t value);
void SPVM_API_set_object_field_value_float(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name, float value);
void SPVM_API_set_object_field_value_double(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name, double value);
int8_t SPVM_API_get_object_field_value_byte(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name);
int16_t SPVM_API_get_object_field_value_short(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name);
int32_t SPVM_API_get_object_field_value_int(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name);
int64_t SPVM_API_get_object_field_value_long(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name);
float SPVM_API_get_object_field_value_float(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name);
double SPVM_API_get_object_field_value_double(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name);
SPVM_DATA* SPVM_API_get_object_field_value_ref(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name);
int32_t SPVM_API_dump_object_field_names(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object);
int32_t* SPVM_API_get_constant_pool(SPVM_ENV* env);
int32_t SPVM_API_get_ref_count(SPVM_ENV* env, SPVM_DATA* data);
int32_t SPVM_API_get_array_length(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array);
int8_t* SPVM_API_get_array_values_byte(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array);
int16_t* SPVM_API_get_array_values_short(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array);
int32_t* SPVM_API_get_array_values_int(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array);
int64_t* SPVM_API_get_array_values_long(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array);
float* SPVM_API_get_array_values_float(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array);
double* SPVM_API_get_array_values_double(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array);
SPVM_DATA** SPVM_API_get_array_values_ref(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array);

#endif
