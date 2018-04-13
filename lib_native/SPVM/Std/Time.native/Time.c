#include <time.h>

#include "spvm_api.h"

int64_t SPVM__Std__Time__time(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  (void)args;

  int64_t timer_value = (int64_t)time(NULL);
  
  
  return timer_value;
}
