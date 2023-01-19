#include <spvm_native.h>

#include "foo.h"
#include "bar.h"
#include "baz/baz.h"

int32_t SPVM__TestCase__NativeAPI2__mul(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t total = stack[0].ival * stack[1].ival;
  
  stack[0].ival = total;
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI2__src_foo(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  if (foo() == 3) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI2__src_bar(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  if (bar() == 4) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPI2__src_baz(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  if (baz() == 5) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

