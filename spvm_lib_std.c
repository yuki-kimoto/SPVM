#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "spvm_native.h"

void boot_SPVM__std() {}

int32_t SPVM__std__sum_int(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  void* array = args[0].oval;
  
  int32_t length = env->get_array_length(env, array);
  
  int32_t* values = env->get_int_array_elements(env, array);
  
  int64_t total = 0;
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      total += values[i];
    }
  }
  
  return total;
}

int32_t SPVM__std__test1(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  int32_t num1 = args[0].ival;
  int32_t num2 = args[1].ival;
  
  int32_t sub_id = env->get_sub_id(env, "std::test2");
  
  SPVM_VALUE new_args[2];
  new_args[0].ival = 5;
  new_args[1].ival = 3;
  
  int32_t ret = env->call_int_sub(env, sub_id, new_args);
  
  int32_t num3 = num1 + num2 + ret;
  
  return num3;
}

int32_t SPVM__std__test2(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  int32_t num1 = args[0].ival;
  int32_t num2 = args[1].ival;
  
  int32_t num3 = num1 * num2;
  
  return num3;
}

void SPVM__std__print(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  void* array = args[0].oval;

  int8_t* string = env->get_byte_array_elements(env, array);
  
  printf("%s\n", (char*)string);
}

void SPVM__std__say(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  void* array = args[0].oval;

  int8_t* string = env->get_byte_array_elements(env, array);

  printf("%s\n", (char*)string);
}

void SPVM__std__say_byte(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  int8_t value = args[0].bval;
  
  printf("%" PRId8 "\n", value);
}

void SPVM__std__say_short(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  int16_t value = args[0].sval;
  
  printf("%" PRId16 "\n", value);
}

void SPVM__std__say_int(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  int32_t value = args[0].ival;
  
  printf("%" PRId32 "\n", value);
}

void SPVM__std__say_long(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  int64_t value = args[0].lval;
  
  printf("%" PRId64 "\n", value);
}

void SPVM__std__say_float(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  float value = args[0].fval;

  printf("%f\n", value);
}

void SPVM__std__say_double(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = args[0].dval;
  
  printf("%f\n", value);
}

void SPVM__std__print_byte(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  int8_t value = args[0].bval;
  
  printf("%" PRId8, value);
}

void SPVM__std__print_short(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  int16_t value = args[0].sval;
  
  printf("%" PRId16, value);
}

void SPVM__std__print_int(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  int32_t value = args[0].ival;
  
  printf("%" PRId32, value);
}

void SPVM__std__print_long(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  int64_t value = args[0].lval;
  
  printf("%" PRId64, value);
}

void SPVM__std__print_float(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  float value = args[0].fval;
  
  printf("%f", value);
}

void SPVM__std__print_double(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  double value = args[0].dval;
  
  printf("%f", value);
}
