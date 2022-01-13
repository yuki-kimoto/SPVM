#include <spvm_native.h>

#include "foo.h"
#include "bar.h"
#include "baz/baz.h"

#include "utf8proc.h"

int32_t SPVM__TestCase__NativeAPI2__use_resource(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t value = UTF8PROC_VERSION_MAJOR;
  
  if (value) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

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

int32_t SPVM__TestCase__NativeAPI2__get_string_field_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* sv_self = stack[0].oval;
  
  int32_t e = 0;
  
  void* sv_text = env->get_field_object_by_name(env, sv_self, "TestCase::NativeAPI2", "text", "string", &e, __FILE__, __LINE__);
  if (e) {
    stack[0].ival = 0;
    return 0;
  }
  
  int32_t length = env->length(env, sv_text);
  
  if (length != 5) {
    stack[0].ival = 0;
    return 0;
  }

  const char* text_chars = env->get_chars(env, sv_text);

  if (strcmp(text_chars, "Hello") != 0) {
    stack[0].ival = 0;
    return 0;
  }
  
  stack[0].ival = 1;
  
  return 0;
}
