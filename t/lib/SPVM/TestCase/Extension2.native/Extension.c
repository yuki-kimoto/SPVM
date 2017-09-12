#include <spvm_api.h>

#include <Extension2_util.h>

int32_t SPVM__TestCase__Extension2__mul(SPVM_API* api, SPVM_API_VALUE* args) {

  int32_t total = args[0].int_value * args[1].int_value;
  
  return total;
}

int32_t SPVM__TestCase__Extension2__one(SPVM_API* api, SPVM_API_VALUE* args) {
  
  int32_t value = Extension2_util_one();
  
  return value;
}
