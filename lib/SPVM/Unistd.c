#include "spvm_native.h"

#include <unistd.h>

int32_t SPNATIVE__SPVM__Unistd__sleep(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void) env;

  uint32_t seconds = stack[0].lval;
  sleep(seconds);

  return SPVM_SUCCESS;
}
