#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "spvm_api.h"

void SPVM_EXTENTION_std__sum_int(SPVM_API* api, SPVM_API_VALUE* args) {
  SPVM_API_BASE_OBJECT* array = args[0].object_value;
  
  int32_t length = api->get_array_length(api, array);
  
  int32_t* values = api->get_int_array_elements(api, array);
  
  int64_t total = 0;
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      total += values[i];
    }
  }
  
  api->push_retval_int(api, total);
}

void SPVM_EXTENTION_std__test1(SPVM_API* api, SPVM_API_VALUE* args) {
  int32_t num1 = args[0].int_value;
  int32_t num2 = args[1].int_value;
  
  int32_t sub_id = api->get_sub_id(api, "stdout::test2");
  
  SPVM_API_VALUE new_args[2];
  new_args[0].int_value = 5;
  new_args[1].int_value = 3;
  
  int32_t ret = api->call_int_sub(api, sub_id, &args);
  
  int32_t num3 = num1 + num2 + ret;
  
  api->push_retval_int(api, num3);
}

void SPVM_EXTENTION_std__test2(SPVM_API* api, SPVM_API_VALUE* args) {
  int32_t num1 = args[0].int_value;
  int32_t num2 = args[1].int_value;
  
  int32_t num3 = num1 * num2;
  
  api->push_retval_int(api, num3);
}

void SPVM_EXTENTION_std__print(SPVM_API* api, SPVM_API_VALUE* args) {
  SPVM_API_BASE_OBJECT* array = args[0].object_value;

  int32_t length = api->get_array_length(api, array);
  int8_t* string = api->get_byte_array_elements(api, array);
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      putchar((int)string[i]);
    }
  }
}

void SPVM_EXTENTION_std__println(SPVM_API* api, SPVM_API_VALUE* args) {
  SPVM_API_BASE_OBJECT* array = args[0].object_value;

  int32_t length = api->get_array_length(api, array);
  
  int8_t* string = api->get_byte_array_elements(api, array);
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      putchar((int)string[i]);
    }
  }
  
  printf("\n");
}

void SPVM_EXTENTION_std__println_byte(SPVM_API* api, SPVM_API_VALUE* args) {
  int8_t value = args[0].byte_value;
  
  printf("%" PRId8 "\n", value);
}

void SPVM_EXTENTION_std__println_short(SPVM_API* api, SPVM_API_VALUE* args) {
  int16_t value = args[0].short_value;
  
  printf("%" PRId16 "\n", value);
}

void SPVM_EXTENTION_std__println_int(SPVM_API* api, SPVM_API_VALUE* args) {
  int32_t value = args[0].int_value;
  
  printf("%" PRId32 "\n", value);
}

void SPVM_EXTENTION_std__println_long(SPVM_API* api, SPVM_API_VALUE* args) {
  int64_t value = args[0].long_value;
  
  printf("%" PRId64 "\n", value);
}

void SPVM_EXTENTION_std__println_float(SPVM_API* api, SPVM_API_VALUE* args) {
  float value = args[0].float_value;

  printf("%f\n", value);
}

void SPVM_EXTENTION_std__println_double(SPVM_API* api, SPVM_API_VALUE* args) {
  double value = args[0].double_value;
  
  printf("%f\n", value);
}

void SPVM_EXTENTION_std__print_byte(SPVM_API* api, SPVM_API_VALUE* args) {
  int8_t value = args[0].byte_value;
  
  printf("%" PRId8, value);
}

void SPVM_EXTENTION_std__print_short(SPVM_API* api, SPVM_API_VALUE* args) {
  int16_t value = args[0].short_value;
  
  printf("%" PRId16, value);
}

void SPVM_EXTENTION_std__print_int(SPVM_API* api, SPVM_API_VALUE* args) {
  int32_t value = args[0].int_value;
  
  printf("%" PRId32, value);
}

void SPVM_EXTENTION_std__print_long(SPVM_API* api, SPVM_API_VALUE* args) {
  int64_t value = args[0].long_value;
  
  printf("%" PRId64, value);
}

void SPVM_EXTENTION_std__print_float(SPVM_API* api, SPVM_API_VALUE* args) {
  float value = args[0].float_value;
  
  printf("%f", value);
}

void SPVM_EXTENTION_std__print_double(SPVM_API* api, SPVM_API_VALUE* args) {
  double value = args[0].double_value;
  
  printf("%f", value);
}
