// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_BASIC_TYPE_H
#define SPVM_API_BASIC_TYPE_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_BASIC_TYPE* SPVM_API_BASIC_TYPE_new_api();

void SPVM_API_BASIC_TYPE_free_api(SPVM_API_BASIC_TYPE* api);

#endif
