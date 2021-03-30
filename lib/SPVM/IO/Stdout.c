#include "spvm_native.h"
#include <stdio.h>

static const char* MFILE = "SPVM/IO/Stdout.c";

int32_t SPNATIVE__SPVM__IO__Stdout__print(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  void* string = stack[0].oval;
  
  if (!string) {
    return env->die(env, "String must be defined", MFILE, __LINE__);
  }
  
  const char* bytes = env->get_chars(env, string);
  int32_t string_length = env->length(env, string);
  
  // Print
  if (string_length > 0) {
    int32_t write_length = fwrite(bytes, 1, string_length, stdout);
    if (write_length != string_length) {
      return env->die(env, "Can't print string to stdout", MFILE, __LINE__);
    }
  }
  
  // Flush buffer to stdout if auto flush is true
  int8_t auto_flush;
  SPVM_GET_PACKAGE_VAR_BYTE(env, "SPVM::IO::Stdout", "$AUTO_FLUSH", &auto_flush, MFILE, __LINE__);
  if (auto_flush) {
    int32_t ret = fflush(stdout);//SPVM::IO::Stdout::print (Don't remove this comment for tests)
    if (ret != 0) {
      return env->die(env, "Can't flush buffer to stdout", MFILE, __LINE__);
    }
  }
  
  return 0;
}

int32_t SPNATIVE__SPVM__IO__Stdout__flush(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  int32_t ret  = (int32_t)fflush(stdout);
  
  if (ret != 0) {
    return env->die(env, "Can't flush buffer to stdout", MFILE, __LINE__);
  }
  
  return 0;
}
