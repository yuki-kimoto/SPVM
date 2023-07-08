// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"
#include "spvm_api.h"

SPVM_ENV* SPVM_NATIVE_new_env() {
  return SPVM_API_new_env();
}

void SPVM_NATIVE_free_env(SPVM_ENV* env) {
  return SPVM_API_free_env(env);
}
