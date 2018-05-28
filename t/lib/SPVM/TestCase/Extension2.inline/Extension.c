#include <spvm_api.h>

#include <Extension2_util.h>

int32_t SPVM__TestCase__Extension2__mul(SPVM_API* api, const SPVM_API_VALUE* args) {
  (void)api;
  (void)args;

  int32_t total = args[0].ival * args[1].ival;
  
  return total;
}

int32_t SPVM__TestCase__Extension2__one(SPVM_API* api, const SPVM_API_VALUE* args) {
  (void)api;
  (void)args;
  
  int32_t value = Extension2_util_one();
  
  return value;
}
