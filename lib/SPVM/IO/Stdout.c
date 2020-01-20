#include "spvm_native.h"
#include <stdio.h>

static const char* MFILE = "SPVM/IO/Stdout.c";

int32_t SPNATIVE__SPVM__IO__Stdout__print(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  void* string = stack[0].oval;
  
  if (!string) {
    SPVM_DIE("String must be defined", MFILE, __LINE__);
  }
  
  const char* bytes = (const char*)env->get_elems_byte(env, string);
  int32_t string_length = env->length(env, string);
  
  // Print
  int32_t error = 0;
  int32_t write_length = fwrite(bytes, 1, string_length, stdout);
  if (write_length =! string_length) {
    SPVM_DIE("Can't print string to stdout", MFILE, __LINE__);
  }
  
  // Flush buffer to stdout if auto flush is true
  int8_t auto_flush;
  SPVM_GET_PACKAGE_VAR_BYTE(env, auto_flush, "SPVM::IO::Stdout", "$AUTO_FLUSH", MFILE, __LINE__);
  if (auto_flush) {
    int32_t ret = fflush(stdout);//SPVM::IO::Stdout::print (Don't remove this comment for tests)
    if (ret != 0) {
      SPVM_DIE("Can't flush buffer to stdout", MFILE, __LINE__);
    }
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__Stdout__flush(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  int32_t ret  = (int32_t)fflush(stdout);
  
  if (ret != 0) {
    SPVM_DIE("Can't flush buffer to stdout", MFILE, __LINE__);
  }
  
  return SPVM_SUCCESS;
}
