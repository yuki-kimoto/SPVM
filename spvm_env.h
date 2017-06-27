#ifndef SPVM_ENV_H
#define SPVM_ENV_H

#include "spvm_base.h"

SPVM_DATA** SPVM_API_get_array_values_ref(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array);

// SPVM_ENV
struct SPVM_env {
  int32_t* constant_pool;
};

#endif
