#include "spvm_native.h"
#include "spvm_api.h"

SPVM_ENV* SPVM_PUBLIC_API_new_env_raw(SPVM_ENV* unused_env) {
  return SPVM_API_new_env_raw(unused_env);
}
