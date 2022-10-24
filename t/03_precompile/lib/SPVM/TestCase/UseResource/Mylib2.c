#include "spvm_native.h"

#include "mylib2_source1.h"

int32_t SPVM__TestCase__UseResource__Mylib2__mylib2_source1_func1 (SPVM_ENV* env, SPVM_VALUE* stack) {
  
  const char* string = mylib2_source1_func1();
  
  stack[0].oval = env->new_string_nolen(env, stack, string);
  
  return 0;
}

int32_t SPVM__TestCase__UseResource__Mylib2__mylib2_source1_func2 (SPVM_ENV* env, SPVM_VALUE* stack) {
  
  const char* string = mylib2_source1_func2();
  
  stack[0].oval = env->new_string_nolen(env, stack, string);

  return 0;
}
