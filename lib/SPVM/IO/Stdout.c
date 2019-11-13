#include "spvm_native.h"
#include <stdio.h>

// import _setmode and _O_BINARY
#ifdef _WIN32
#include <io.h>
#endif

static const char* MFILE = "SPVM/IO/Stdout.c";

int32_t SPNATIVE__SPVM__IO__Stdout__print(SPVM_ENV* env, SPVM_VALUE* stack) {

  (void)env;
  
  void* string = stack[0].oval;
  
  const char* bytes = (const char*)env->get_elems_byte(env, string);
  int32_t string_length = env->length(env, string);
  
  for (int32_t i = 0; i < string_length; i++) {
    putchar(bytes[i]);
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__Stdout__set_binmode(SPVM_ENV* env, SPVM_VALUE* stack) {

#ifdef _WIN32
  int32_t binmode = stack[0].ival;
  if (binmode) {
    _setmode(_fileno(stdout), _O_BINARY);
  }
  else {
    _setmode(_fileno(stdout), _O_TEXT);
  }
#endif
  
  return SPVM_SUCCESS;
}
