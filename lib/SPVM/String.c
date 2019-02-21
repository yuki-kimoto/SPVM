#include "spvm_native.h"
#include <stdio.h>

int32_t SPNATIVE__SPVM__String__is_utf8(SPVM_ENV* env, SPVM_VALUE* stack) {

  // File handle
  void* ostring = stack[0].oval;
  
  if (ostring == NULL) {
    SPVM_CROAK("Can't close file handle", "SPVM/String", __LINE__);
  }
  
  int32_t is_utf8 = env->is_utf8(env, ostring);
  
  stack[0].ival = is_utf8;
  
  return SPVM_SUCCESS;
}
