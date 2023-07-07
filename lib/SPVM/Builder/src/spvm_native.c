// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_native.h"
#include "spvm_api.h"

SPVM_ENV* SPVM_NATIVE_new_env() {
  return SPVM_API_new_env();
}
