#include "spvm_native.h"

#include "bar1.h"
#include "bar2.h"

int32_t SPVM__TestCase__UseResource__Basic__bar1_baz1 (SPVM_ENV* env, SPVM_VALUE* stack) {
  
  const char* string = bar1_baz1();
  
  stack[0].oval = env->new_string_nolen(env, string);
  
  return 0;
}

int32_t SPVM__TestCase__UseResource__Basic__bar1_baz2 (SPVM_ENV* env, SPVM_VALUE* stack) {
  
  const char* string = bar1_baz2();
  
  stack[0].oval = env->new_string_nolen(env, string);

  return 0;
}

int32_t SPVM__TestCase__UseResource__Basic__bar2_baz1 (SPVM_ENV* env, SPVM_VALUE* stack) {

  const char* string = bar2_baz1();
  
  stack[0].oval = env->new_string_nolen(env, string);
  
  return 0;
}

int32_t SPVM__TestCase__UseResource__Basic__bar2_baz2 (SPVM_ENV* env, SPVM_VALUE* stack) {

  const char* string = bar2_baz2();
  
  stack[0].oval = env->new_string_nolen(env, string);
  
  return 0;
}
