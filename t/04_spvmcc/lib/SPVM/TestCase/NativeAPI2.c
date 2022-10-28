#include <assert.h>
#include <fcntl.h>

#include <spvm_native.h>

#include "foo.h"
#include "bar.h"
#include "baz/baz.h"

#include "mylib1_source1.h"
#include "mylib2_source1.h"

int32_t SPVM__TestCase__NativeAPI2__mul(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t total = stack[0].ival * stack[1].ival;
  
  stack[0].ival = total;

// Extra test of stdin, stdout, stderr is binary mode.
#ifdef _WIN32  
  int32_t stdin_old_mode = _setmode(0, _O_BINARY);
  assert(stdin_old_mode == _O_BINARY);
  int32_t stdout_old_mode = _setmode(1, _O_BINARY);
  assert(stdout_old_mode == _O_BINARY);
  int32_t stderr_old_mode = _setmode(2, _O_BINARY);
  assert(stderr_old_mode == _O_BINARY);
#endif
  
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

int32_t SPVM__TestCase__NativeAPI2__mylib2_source1_func1(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  const char* string = mylib2_source1_func1();
  
  stack[0].oval = env->new_string_nolen(env, stack, string);
  
  return 0;
}
