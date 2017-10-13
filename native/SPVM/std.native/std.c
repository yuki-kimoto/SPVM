#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>

#include "spvm_api.h"

int64_t SPVM__std__time(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;

  int64_t timer_value = (int64_t)time(NULL);
  
  
  return timer_value;
}

int32_t SPVM__std__sum_int(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* array = args[0].object_value;
  
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

int32_t SPVM__std__test1(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int32_t num1 = args[0].int_value;
  int32_t num2 = args[1].int_value;
  
  int32_t sub_id = api->get_sub_id(api, "std::test2");
  
  SPVM_API_VALUE new_args[2];
  new_args[0].int_value = 5;
  new_args[1].int_value = 3;
  
  int32_t ret = api->call_int_sub(api, sub_id, new_args);
  
  int32_t num3 = num1 + num2 + ret;
  
  return num3;
}

int32_t SPVM__std__test2(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int32_t num1 = args[0].int_value;
  int32_t num2 = args[1].int_value;
  
  int32_t num3 = num1 * num2;
  
  return num3;
}

void SPVM__std__say(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* object = args[0].object_value;
  
  char* chars = api->get_string_chars(api, object);

  printf("%s\n", (char*)chars);
}

void SPVM__std__say_byte(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int8_t value = args[0].byte_value;
  
  printf("%" PRId8 "\n", value);
}

void SPVM__std__say_short(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int16_t value = args[0].short_value;
  
  printf("%" PRId16 "\n", value);
}

void SPVM__std__say_int(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int32_t value = args[0].int_value;
  
  printf("%" PRId32 "\n", value);
}

void SPVM__std__say_long(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int64_t value = args[0].long_value;
  
  printf("%" PRId64 "\n", value);
}

void SPVM__std__say_float(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  float value = args[0].float_value;

  printf("%f\n", value);
}

void SPVM__std__say_double(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = args[0].double_value;
  
  printf("%f\n", value);
}

void SPVM__std__print(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* object = args[0].object_value;
  
  char* chars = api->get_string_chars(api, object);
  
  printf("%s\n", (char*)chars);
}

void SPVM__std__print_byte(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int8_t value = args[0].byte_value;
  
  printf("%" PRId8, value);
}

void SPVM__std__print_short(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int16_t value = args[0].short_value;
  
  printf("%" PRId16, value);
}

void SPVM__std__print_int(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int32_t value = args[0].int_value;
  
  printf("%" PRId32, value);
}

void SPVM__std__print_long(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int64_t value = args[0].long_value;
  
  printf("%" PRId64, value);
}

void SPVM__std__print_float(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  float value = args[0].float_value;
  
  printf("%f", value);
}

void SPVM__std__print_double(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = args[0].double_value;
  
  printf("%f", value);
}

void SPVM__std__print_err(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* object = args[0].object_value;
  
  char* chars = api->get_string_chars(api, object);
  
  fprintf(stderr, "%s\n", chars);
}

void SPVM__std__say_err(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* object = args[0].object_value;
  
  char* chars = api->get_string_chars(api, object);

  fprintf(stderr, "%s\n", chars);
}

void SPVM__std__say_err_byte(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int8_t value = args[0].byte_value;
  
  fprintf(stderr, "%" PRId8 "\n", value);
}

void SPVM__std__say_err_short(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int16_t value = args[0].short_value;
  
  fprintf(stderr, "%" PRId16 "\n", value);
}

void SPVM__std__say_err_int(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int32_t value = args[0].int_value;
  
  fprintf(stderr, "%" PRId32 "\n", value);
}

void SPVM__std__say_err_long(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int64_t value = args[0].long_value;
  
  fprintf(stderr, "%" PRId64 "\n", value);
}

void SPVM__std__say_err_float(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  float value = args[0].float_value;

  fprintf(stderr, "%f\n", value);
}

void SPVM__std__say_err_double(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = args[0].double_value;
  
  fprintf(stderr, "%f\n", value);
}

void SPVM__std__print_err_byte(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int8_t value = args[0].byte_value;
  
  fprintf(stderr, "%" PRId8, value);
}

void SPVM__std__print_err_short(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int16_t value = args[0].short_value;
  
  fprintf(stderr, "%" PRId16, value);
}

void SPVM__std__print_err_int(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int32_t value = args[0].int_value;
  
  fprintf(stderr, "%" PRId32, value);
}

void SPVM__std__print_err_long(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int64_t value = args[0].long_value;
  
  fprintf(stderr, "%" PRId64, value);
}

void SPVM__std__print_err_float(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  float value = args[0].float_value;
  
  fprintf(stderr, "%f", value);
}

void SPVM__std__print_err_double(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = args[0].double_value;
  
  fprintf(stderr, "%f", value);
}
