// Enable strerror_r, fileno
#ifndef _XOPEN_SOURCE
#  define _XOPEN_SOURCE 600
#endif

#include "spvm_native.h"
#include <stdio.h>

static const char* MFILE = "SPVM/IO/Stderr.c";

int32_t SPNATIVE__SPVM__IO__Stderr__print(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  void* string = stack[0].oval;
  
  const char* bytes = (const char*)env->get_elems_byte(env, string);
  int32_t string_length = env->length(env, string);
  
  for (int32_t i = 0; i < string_length; i++) {
    fputc(bytes[i], stderr);
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__Stderr__fileno(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t fno = fileno(stderr);
  
  stack[0].ival = fno;

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__Stderr__write(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t length = stack[1].ival;

  // Buffer
  void* obj_buffer = stack[0].oval;
  if (obj_buffer == NULL) {
    stack[0].oval = NULL;
    return SPVM_SUCCESS;
  }
  char* buffer = (char*)env->get_elems_byte(env, obj_buffer);
  
  int32_t write_length = fwrite(buffer, 1, length, stderr);
  
  stack[0].ival = write_length;

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__Stderr__putc(SPVM_ENV* env, SPVM_VALUE* stack) {

  // Char
  char ch = (char)stack[0].bval;
  
  int32_t ret = fputc(ch, stderr);
  
  stack[0].ival = ret;

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__Stderr__flush(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  int32_t ret = fflush(stdout);
  
  if (ret != 0) {
    SPVM_DIE("Can't flash to stderr", MFILE, __LINE__);
  }
  
  return SPVM_SUCCESS;
}
