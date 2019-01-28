#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <assert.h>
#include <stdio.h>
#include <fcntl.h>

#include <spvm_native.h>

int32_t SPVM_NATIVE_TestCase__Lib__SPVM__CORE__test_init_native_constants_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t* int_constants = env->ielems(env, stack[0].oval);
  
  if (int_constants[0] != O_RDONLY) {
    stack[0].ival = 0;
    return SPVM_SUCCESS;
  }

  if (int_constants[1] != O_WRONLY) {
    stack[0].ival = 0;
    return SPVM_SUCCESS;
  }

  if (int_constants[2] != O_RDWR) {
    stack[0].ival = 0;
    return SPVM_SUCCESS;
  }

  if (int_constants[3] != O_APPEND) {
    stack[0].ival = 0;
    return SPVM_SUCCESS;
  }

  if (int_constants[4] != O_CREAT) {
    stack[0].ival = 0;
    return SPVM_SUCCESS;
  }

  if (int_constants[5] != O_TRUNC) {
    stack[0].ival = 0;
    return SPVM_SUCCESS;
  }

  if (int_constants[6] != SEEK_SET) {
    stack[0].ival = 0;
    return SPVM_SUCCESS;
  }

  if (int_constants[7] != SEEK_CUR) {
    stack[0].ival = 0;
    return SPVM_SUCCESS;
  }

  if (int_constants[8] != SEEK_END) {
    stack[0].ival = 0;
    return SPVM_SUCCESS;
  }

  if (int_constants[9] != EOF) {
    stack[0].ival = 0;
    return SPVM_SUCCESS;
  }
  
  stack[0].ival = 1;
  return SPVM_SUCCESS;
}
