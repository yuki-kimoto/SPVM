#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "spvm.h"
#include "spvm_extention.h"
#include "spvm_api.h"
#include "spvm_env.h"
#include "spvm_sv.h"

void SPVM_EXTENTION_std__test_call1(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  int32_t value =  SPVM_API_get_var_int(spvm, env, 0);
  
  int32_t value2 = value * 2;
  
  // Call subroutine
  SPVM_ENV* new_env = SPVM_ENV_new(spvm);
  SPVM_API_push_var_int(spvm, new_env, value2);
  SPVM_API_call_sub(spvm, new_env, "std::test_call2");
  int32_t value3 = SPVM_API_pop_return_value_int(spvm, new_env);
  SPVM_ENV_free(spvm, new_env);
  
  SPVM_API_push_return_value_int(spvm, env, value3);
}

void SPVM_EXTENTION_std__test_call2(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  int32_t value =  SPVM_API_get_var_int(spvm, env, 0);
  
  int32_t value2 = value * 3;
  
  SPVM_API_push_return_value_int(spvm, env, value2);
}

void SPVM_EXTENTION_std__sum_int(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  void* int_array = SPVM_API_get_var_address(spvm, env, 0);
  
  int64_t length = SPVM_API_get_array_length(spvm, env, int_array);
  
  int64_t* int_array_data = SPVM_API_get_array_int_values(spvm, env, int_array);
  
  int64_t total = 0;
  for (int64_t i = 0; i < length; i++) {
    total += int_array_data[i];
  }
  
  SPVM_API_push_return_value_int(spvm, env, total);
}

void SPVM_EXTENTION_std__println(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  void* string = SPVM_API_get_var_address(spvm, env, 0);
  
  SPVM_SV* sv = SPVM_API_get_string_sv(spvm, env, string);
  
  char* buffer = sv->buffer;
  int64_t length = sv->length;
  
  for (int64_t i = 0; i < length; i++) {
    putchar((int)buffer[i]);
  }
  
  printf("\n");
}

void SPVM_EXTENTION_std__println_byte(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  int8_t value = SPVM_API_get_var_byte(spvm, env, 0);
  
  printf("%" PRId8 "\n", value);
}

void SPVM_EXTENTION_std__println_short(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  int16_t value = SPVM_API_get_var_short(spvm, env, 0);
  
  printf("%" PRId16 "\n", value);
}

void SPVM_EXTENTION_std__println_int(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  int32_t value = SPVM_API_get_var_int(spvm, env, 0);
  
  printf("%" PRId32 "\n", value);
}

void SPVM_EXTENTION_std__println_long(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  int64_t value = SPVM_API_get_var_long(spvm, env, 0);
  
  printf("%" PRId64 "\n", value);
}

void SPVM_EXTENTION_std__println_float(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  float value = SPVM_API_get_var_float(spvm, env, 0);
  
  printf("%f\n", value);
}

void SPVM_EXTENTION_std__println_double(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  double value = SPVM_API_get_var_double(spvm, env, 0);
  
  printf("%f\n", value);
}

void SPVM_EXTENTION_std__print(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  void* string = SPVM_API_get_var_address(spvm, env, 0);
  
  SPVM_SV* sv = SPVM_API_get_string_sv(spvm, env, string);
  
  char* buffer = sv->buffer;
  int64_t length = sv->length;
  
  for (int64_t i = 0; i < length; i++) {
    putchar((int)buffer[i]);
  }
  
  printf("\n");
}

void SPVM_EXTENTION_std__print_byte(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  int8_t value = SPVM_API_get_var_byte(spvm, env, 0);
  
  printf("%" PRId8, value);
}

void SPVM_EXTENTION_std__print_short(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  int16_t value = SPVM_API_get_var_short(spvm, env, 0);
  
  printf("%" PRId16, value);
}

void SPVM_EXTENTION_std__print_int(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  int32_t value = SPVM_API_get_var_int(spvm, env, 0);
  
  printf("%" PRId32, value);
}

void SPVM_EXTENTION_std__print_long(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  int64_t value = SPVM_API_get_var_long(spvm, env, 0);
  
  printf("%" PRId64, value);
}

void SPVM_EXTENTION_std__print_float(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  float value = SPVM_API_get_var_float(spvm, env, 0);
  
  printf("%f", value);
}

void SPVM_EXTENTION_std__print_double(SPVM* spvm, SPVM_ENV* env) {
  (void)spvm;
  (void)env;
  
  double value = SPVM_API_get_var_double(spvm, env, 0);
  
  printf("%f", value);
}
