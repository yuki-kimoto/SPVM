#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "spvm_api.h"

int64_t SPVM__CORE__time(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;

  int64_t timer_value = (int64_t)time(NULL);
  
  
  return timer_value;
}

void SPVM__CORE__print(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* object = args[0].object_value;
  
  int8_t* bytes = api->get_byte_array_elements(api, object);
  int32_t string_length = api->get_array_length(api, object);
  
  {
    int32_t i;
    for (i = 0; i < string_length; i++) {
      putchar((char)bytes[i]);
    }
  }
}

void SPVM__CORE__warn(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* object = args[0].object_value;
  
  int8_t* bytes = api->get_byte_array_elements(api, object);
  int32_t string_length = api->get_array_length(api, object);
  
  {
    int32_t i;
    for (i = 0; i < string_length; i++) {
      putc((char)bytes[i], stderr);
    }
  }
  
  fprintf(stderr, "\n");
}
