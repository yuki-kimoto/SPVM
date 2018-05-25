#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#include "spvm_api.h"

void SPVM__Std__IO__print(SPVM_API* api, SPVM_API_VALUE* args) {
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

void SPVM__Std__IO__warn(SPVM_API* api, SPVM_API_VALUE* args) {
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
