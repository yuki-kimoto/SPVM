#include <spvm_native.h>

#include "foo.h"
#include "bar.h"
#include "baz/baz.h"

int32_t SPNATIVE__TestCase__NativeAPI2__mul(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;

  int32_t total = args[0].ival * args[1].ival;
  
  args[0].ival = total;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__NativeAPI2__src_foo(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  if (foo() == 3) {
    args[0].ival = 1;
  }
  else {
    args[0].ival = 0;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__NativeAPI2__src_bar(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;

  if (bar() == 4) {
    args[0].ival = 1;
  }
  else {
    args[0].ival = 0;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__TestCase__NativeAPI2__src_baz(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;

  if (baz() == 5) {
    args[0].ival = 1;
  }
  else {
    args[0].ival = 0;
  }
  
  return SPVM_SUCCESS;
}
