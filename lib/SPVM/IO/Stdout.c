#include "spvm_native.h"
#include <stdio.h>

static const char* MFILE = "SPVM/IO/Stdout.c";

int32_t SPNATIVE__SPVM__IO__Stdout__print(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  void* string = stack[0].oval;
  
  const char* bytes = (const char*)env->get_elems_byte(env, string);
  int32_t string_length = env->length(env, string);
  
  int32_t error = 0;
  for (int32_t i = 0; i < string_length; i++) {
    int32_t ret = fputc(bytes[i], stdout);
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

int32_t SPNATIVE__SPVM__IO__Stdout__write(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t offset = stack[1].ival;
  int32_t length = stack[2].ival;
  
  // Buffer
  void* obj_bytes = stack[0].oval;
  if (obj_bytes == NULL) {
    stack[0].oval = NULL;
    return SPVM_SUCCESS;
  }
  char* bytes = (char*)env->get_elems_byte(env, obj_bytes);
  int32_t bytes_length = (char*)env->length(env, obj_bytes);
  if (offset < 0) {
    stack[0].ival = 0;
    return SPVM_SUCCESS;
  }
  if (offset + length > bytes_length) {
    stack[0].ival = 0;
    return SPVM_SUCCESS;
  }
  
  int32_t write_length = fwrite(bytes + offset, 1, length, stdout);
  
  stack[0].ival = write_length;

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__Stdout__flush(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  stack[0].ival = fflush(stdout);
  
  return SPVM_SUCCESS;
}
