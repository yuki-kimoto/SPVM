#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "spvm_api.h"

void boot_SPVM__std() {}

int32_t SPVM__std__sum_int(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  
  void* array = args[0].oval;
  
  int32_t length = api->get_array_length(api, array);
  
  int32_t* values = api->get_int_array_elements(api, array);
  
  int64_t total = 0;
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      total += values[i];
    }
  }
  
  return total;
}

int32_t SPVM__std__test1(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  
  int32_t num1 = args[0].ival;
  int32_t num2 = args[1].ival;
  
  int32_t sub_id = api->get_sub_id(api, "std::test2");
  
  SPVM_VALUE new_args[2];
  new_args[0].ival = 5;
  new_args[1].ival = 3;
  
  int32_t ret = api->call_int_sub(api, sub_id, new_args);
  
  int32_t num3 = num1 + num2 + ret;
  
  return num3;
}

int32_t SPVM__std__test2(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  
  int32_t num1 = args[0].ival;
  int32_t num2 = args[1].ival;
  
  int32_t num3 = num1 * num2;
  
  return num3;
}

void SPVM__std__print(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  
  void* array = args[0].oval;

  int8_t* string = api->get_byte_array_elements(api, array);
  
  printf("%s\n", (char*)string);
}

void SPVM__std__say(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  
  void* array = args[0].oval;

  int8_t* string = api->get_byte_array_elements(api, array);

  printf("%s\n", (char*)string);
}

void SPVM__std__say_byte(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  
  int8_t value = args[0].bval;
  
  printf("%" PRId8 "\n", value);
}

void SPVM__std__say_short(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  
  int16_t value = args[0].sval;
  
  printf("%" PRId16 "\n", value);
}

void SPVM__std__say_int(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  
  int32_t value = args[0].ival;
  
  printf("%" PRId32 "\n", value);
}

void SPVM__std__say_long(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  
  int64_t value = args[0].lval;
  
  printf("%" PRId64 "\n", value);
}

void SPVM__std__say_float(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  
  float value = args[0].fval;

  printf("%f\n", value);
}

void SPVM__std__say_double(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = args[0].dval;
  
  printf("%f\n", value);
}

void SPVM__std__print_byte(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  
  int8_t value = args[0].bval;
  
  printf("%" PRId8, value);
}

void SPVM__std__print_short(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  
  int16_t value = args[0].sval;
  
  printf("%" PRId16, value);
}

void SPVM__std__print_int(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  
  int32_t value = args[0].ival;
  
  printf("%" PRId32, value);
}

void SPVM__std__print_long(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  
  int64_t value = args[0].lval;
  
  printf("%" PRId64, value);
}

void SPVM__std__print_float(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  
  float value = args[0].fval;
  
  printf("%f", value);
}

void SPVM__std__print_double(SPVM_ENV* api, SPVM_VALUE* args) {
  (void)api;
  
  double value = args[0].dval;
  
  printf("%f", value);
}
