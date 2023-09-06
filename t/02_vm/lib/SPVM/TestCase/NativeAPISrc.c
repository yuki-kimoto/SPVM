#include <spvm_native.h>

#include "foo.h"
#include "bar.h"
#include "baz/baz.h"

int32_t SPVM__TestCase__NativeAPISrc__src_foo(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t value = foo();
  
  if (value == 3) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPISrc__src_bar(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t value = bar();
  
  if (value == 4) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPVM__TestCase__NativeAPISrc__src_baz(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t value = baz();
  
  if (value == 6) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

