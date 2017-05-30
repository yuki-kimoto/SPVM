#ifndef SPVM_API_H
#define SPVM_API_H

void SPVM_API_dec_ref_count(SPVM* spvm, SPVM_ENV* env, SPVM_REF* ref);
void SPVM_API_inc_ref_count(SPVM* spvm, SPVM_ENV* env, SPVM_REF* ref);

void SPVM_API_call_sub(SPVM* spvm, SPVM_ENV* env, const char* sub_base_name);

int32_t SPVM_API_get_ref_count(SPVM* spvm, SPVM_ENV* env, SPVM_REF* ref);
int32_t SPVM_API_get_array_length(SPVM* spvm, SPVM_ENV* env, SPVM_REF_ARRAY* array);

int8_t* SPVM_API_get_array_byte_values(SPVM* spvm, SPVM_ENV* env, void* address);
int16_t* SPVM_API_get_array_short_values(SPVM* spvm, SPVM_ENV* env, void* address);
int32_t* SPVM_API_get_array_int_values(SPVM* spvm, SPVM_ENV* env, void* address);
int64_t* SPVM_API_get_array_long_values(SPVM* spvm, SPVM_ENV* env, void* address);
float* SPVM_API_get_array_float_values(SPVM* spvm, SPVM_ENV* env, void* address);
double* SPVM_API_get_array_double_values(SPVM* spvm, SPVM_ENV* env, void* address);

SPVM_SV* SPVM_API_get_string_sv(SPVM* spvm, SPVM_ENV* env, SPVM_REF_STRING* string);

int8_t SPVM_API_get_var_byte(SPVM* spvm, SPVM_ENV* env, int32_t index);
int16_t SPVM_API_get_var_short(SPVM* spvm, SPVM_ENV* env, int32_t index);
int32_t SPVM_API_get_var_int(SPVM* spvm, SPVM_ENV* env, int32_t index);
int64_t SPVM_API_get_var_long(SPVM* spvm, SPVM_ENV* env, int32_t index);
float SPVM_API_get_var_float(SPVM* spvm, SPVM_ENV* env, int32_t index);
double SPVM_API_get_var_double(SPVM* spvm, SPVM_ENV* env, int32_t index);
void* SPVM_API_get_var_address(SPVM* spvm, SPVM_ENV* env, int32_t index);

void SPVM_API_push_var_byte(SPVM* spvm, SPVM_ENV* env, int8_t value);
void SPVM_API_push_var_short(SPVM* spvm, SPVM_ENV* env, int16_t value);
void SPVM_API_push_var_int(SPVM* spvm, SPVM_ENV* env, int32_t value);
void SPVM_API_push_var_long(SPVM* spvm, SPVM_ENV* env, int64_t value);
void SPVM_API_push_var_float(SPVM* spvm, SPVM_ENV* env, float value);
void SPVM_API_push_var_double(SPVM* spvm, SPVM_ENV* env, double value);
void SPVM_API_push_var_address(SPVM* spvm, SPVM_ENV* env, void* value);

void SPVM_API_push_return_value_byte(SPVM* spvm, SPVM_ENV* env, int8_t value);
void SPVM_API_push_return_value_short(SPVM* spvm, SPVM_ENV* env, int16_t value);
void SPVM_API_push_return_value_int(SPVM* spvm, SPVM_ENV* env, int32_t value);
void SPVM_API_push_return_value_long(SPVM* spvm, SPVM_ENV* env, int64_t value);
void SPVM_API_push_return_value_float(SPVM* spvm, SPVM_ENV* env, float value);
void SPVM_API_push_return_value_double(SPVM* spvm, SPVM_ENV* env, double value);
void SPVM_API_push_return_value_address(SPVM* spvm, SPVM_ENV* env, void* value);

int8_t SPVM_API_pop_return_value_byte(SPVM* spvm, SPVM_ENV* env);
int16_t SPVM_API_pop_return_value_short(SPVM* spvm, SPVM_ENV* env);
int32_t SPVM_API_pop_return_value_int(SPVM* spvm, SPVM_ENV* env);
int64_t SPVM_API_pop_return_value_long(SPVM* spvm, SPVM_ENV* env);
float SPVM_API_pop_return_value_float(SPVM* spvm, SPVM_ENV* env);
double SPVM_API_pop_return_value_double(SPVM* spvm, SPVM_ENV* env);
void* SPVM_API_pop_return_value_address(SPVM* spvm, SPVM_ENV* env);

char* SPVM_API_get_string_value(SPVM* spvm, SPVM_ENV* env, SPVM_REF_STRING* ref_string);

void* SPVM_API_create_string_sv(SPVM* spvm, SPVM_ENV* env, SPVM_SV* sv);
SPVM_REF_STRING* SPVM_API_create_ref_string_from_pv(SPVM* spvm, SPVM_ENV* env, const char* pv);

#endif
