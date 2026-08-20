#include <spvm_native.h>

static const char* FILE_NAME = "TestCase/NativeAPILinkTo.c";

int32_t SPVM__TestCase__NativeAPILinkTo__basic(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].ival = 1;
  
  return 0;
}
