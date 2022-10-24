#include "spvm_native.h"

#include "mylib1_source1.h"
#include "mylib1_source2.h"

int32_t SPVM__TestCase__UseResource__Basic__mylib1_source1_func1 (SPVM_ENV* env, SPVM_VALUE* stack) {
  
  const char* string = mylib1_source1_func1();
  
  stack[0].oval = env->new_string_nolen(env, stack, string);
  
  return 0;
}

int32_t SPVM__TestCase__UseResource__Basic__mylib1_source1_func2 (SPVM_ENV* env, SPVM_VALUE* stack) {
  
  const char* string = mylib1_source1_func2();
  
  stack[0].oval = env->new_string_nolen(env, stack, string);

  return 0;
}

int32_t SPVM__TestCase__UseResource__Basic__mylib1_source2_func1 (SPVM_ENV* env, SPVM_VALUE* stack) {

  const char* string = mylib1_source2_func1();
  
  stack[0].oval = env->new_string_nolen(env, stack, string);
  
  return 0;
}

int32_t SPVM__TestCase__UseResource__Basic__mylib1_source2_func2 (SPVM_ENV* env, SPVM_VALUE* stack) {

  const char* string = mylib1_source2_func2();
  
  stack[0].oval = env->new_string_nolen(env, stack, string);
  
  return 0;
}
