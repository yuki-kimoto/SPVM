#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>

#include "spvm_native.h"

int64_t SPVM_CORE_FUNC_time(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;

  int64_t timer_value = (int64_t)time(NULL);
  
  
  return timer_value;
}

void SPVM_CORE_FUNC_print(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  void* object = args[0].oval;
  
  int8_t* bytes = env->get_byte_array_elements(env, object);
  int32_t string_length = env->get_array_length(env, object);
  
  {
    int32_t i;
    for (i = 0; i < string_length; i++) {
      putchar((char)bytes[i]);
    }
  }
}

void SPVM_CORE_FUNC_warn(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  
  void* object = args[0].oval;
  
  int8_t* bytes = env->get_byte_array_elements(env, object);
  int32_t string_length = env->get_array_length(env, object);
  
  {
    int32_t i;
    for (i = 0; i < string_length; i++) {
      putc((char)bytes[i], stderr);
    }
  }
  
  fprintf(stderr, "\n");
}
