#include "spvm_native.h"
#include <stdio.h>

static const char* MFILE = "SPVM/IO/Stdout.c";

int32_t SPNATIVE__SPVM__IO__Stdout__print(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  void* string = stack[0].oval;
  
  const char* bytes = (const char*)env->get_elems_byte(env, string);
  int32_t string_length = env->length(env, string);
  
  // Print
  int32_t error = 0;
  for (int32_t i = 0; i < string_length; i++) {
    int32_t ret = fputc(bytes[i], stdout);
    if (ret == EOF) {
      error = 1;
      break;
    }
  }
  
  // Auto flush
  int8_t auto_flush;
  SPVM_GET_PACKAGE_VAR_BYTE(env, auto_flush, "SPVM::IO::Stdout", "$AUTO_FLUSH", MFILE, __LINE__);
  
  if (auto_flush) {
    fflush(stdout);//SPVM::IO::Stdout::print (Don't remove this comment for tests)
  }
  
  if (error) {
    stack[0].ival = -1;
  }
  else {
    stack[0].ival = string_length;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__Stdout__flush(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  stack[0].ival = fflush(stdout);
  
  return SPVM_SUCCESS;
}
