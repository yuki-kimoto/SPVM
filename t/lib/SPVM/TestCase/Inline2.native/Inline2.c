#include <spvm_api.h>

#include <Inline2_util.h>

int32_t SPVM__TestCase__Inline2__sum(SPVM_API* api, SPVM_API_VALUE* args) {

  int32_t total = args[0].int_value + args[1].int_value;
  
  return total;
}
