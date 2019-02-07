#include <spvm_native.h>

int32_t SPNATIVE__TestCase__Extension2__mul(SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;

  int32_t total = args[0].ival * args[1].ival;
  
  args[0].ival = total;
  
  return 0;
}
