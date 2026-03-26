#include "spvm_native.h"

int32_t external_sum(int32_t x, int32_t y);

static const char* FILE_NAME = "TestCase/ExternalFunction.c";

int32_t SPVM__TestCase__ExternalFunction__external_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t x = stack[0].ival;
  
  int32_t y = stack[1].ival;
  
  int32_t ret = external_sum(x, y);
  
  stack[0].ival = ret;
  
  return 0;
}
