#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "spvm_env.h"

void SPVM_EXTENTION_std__sum_int(SPVM_ENV* env) {
  void* data_array = env->get_var_address(env, 0);
  
  int32_t length = env->get_array_length(env, data_array);
  
  int32_t* values = env->get_array_values_int(env, data_array);
  
  int64_t total = 0;
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      total += values[i];
    }
  }
  
  env->push_return_value_int(env, total);
}

void SPVM_EXTENTION_std__print(SPVM_ENV* env) {
  void* data_array = env->get_var_address(env, 0);

  int32_t length = env->get_array_length(env, data_array);
  int8_t* string = env->get_array_values_byte(env, data_array);
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      putchar((int)string[i]);
    }
  }
}

void SPVM_EXTENTION_std__println(SPVM_ENV* env) {
  void* data_array = env->get_var_address(env, 0);

  int32_t length = env->get_array_length(env, data_array);
  
  int8_t* string = env->get_array_values_byte(env, data_array);
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      putchar((int)string[i]);
    }
  }
  
  printf("\n");
}

void SPVM_EXTENTION_std__println_byte(SPVM_ENV* env) {
  int8_t value = env->get_var_byte(env, 0);
  
  printf("%" PRId8 "\n", value);
}

void SPVM_EXTENTION_std__println_short(SPVM_ENV* env) {
  int16_t value = env->get_var_short(env, 0);
  
  printf("%" PRId16 "\n", value);
}

void SPVM_EXTENTION_std__println_int(SPVM_ENV* env) {
  int32_t value = env->get_var_int(env, 0);
  
  printf("%" PRId32 "\n", value);
}

void SPVM_EXTENTION_std__println_long(SPVM_ENV* env) {
  int64_t value = env->get_var_long(env, 0);
  
  printf("%" PRId64 "\n", value);
}

void SPVM_EXTENTION_std__println_float(SPVM_ENV* env) {
  float value = env->get_var_float(env, 0);

  printf("%f\n", value);
}

void SPVM_EXTENTION_std__println_double(SPVM_ENV* env) {
  double value = env->get_var_double(env, 0);
  
  printf("%f\n", value);
}

void SPVM_EXTENTION_std__print_byte(SPVM_ENV* env) {
  int8_t value = env->get_var_byte(env, 0);
  
  printf("%" PRId8, value);
}

void SPVM_EXTENTION_std__print_short(SPVM_ENV* env) {
  int16_t value = env->get_var_short(env, 0);
  
  printf("%" PRId16, value);
}

void SPVM_EXTENTION_std__print_int(SPVM_ENV* env) {
  int32_t value = env->get_var_int(env, 0);
  
  printf("%" PRId32, value);
}

void SPVM_EXTENTION_std__print_long(SPVM_ENV* env) {
  int64_t value = env->get_var_long(env, 0);
  
  printf("%" PRId64, value);
}

void SPVM_EXTENTION_std__print_float(SPVM_ENV* env) {
  float value = env->get_var_float(env, 0);
  
  printf("%f", value);
}

void SPVM_EXTENTION_std__print_double(SPVM_ENV* env) {
  double value = env->get_var_double(env, 0);
  
  printf("%f", value);
}
