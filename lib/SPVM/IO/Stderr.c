#include "spvm_native.h"
#include <stdio.h>

static const char* MFILE = "SPVM/IO/Stderr.c";

int32_t SPNATIVE__SPVM__IO__Stderr__print(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  void* string = stack[0].oval;
  
  const char* bytes = (const char*)env->get_elems_byte(env, string);
  int32_t string_length = env->length(env, string);
  
  int32_t error = 0;
  for (int32_t i = 0; i < string_length; i++) {
    int32_t ret = fputc(bytes[i], stderr);
    if (ret == EOF) {
      error = 1;
      break;
    }
  }
  
  if (error) {
    stack[0].ival = -1;
  }
  else {
    stack[0].ival = string_length;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__Stderr__flush(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  int32_t ret  = (int32_t)fflush(stderr);
  
  if (ret != 0) {
    SPVM_DIE("Can't flush to stderr", MFILE, __LINE__);
  }
  
  return SPVM_SUCCESS;
}
