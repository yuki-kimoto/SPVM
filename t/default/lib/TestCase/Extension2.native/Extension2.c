#include <spvm_native.h>

#include <Extension2_util.h>

int32_t SPVM__TestCase__Extension2__mul(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;

  int32_t total = args[0].ival * args[1].ival;
  
  args[0].ival = total;
  
  return 0;
}

int32_t SPVM__TestCase__Extension2__one(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  int32_t value = Extension2_util_one();
  
  args[0].ival = value;
  
  return 0;
}
