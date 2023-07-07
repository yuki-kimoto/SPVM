// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_METHOD_H
#define SPVM_API_METHOD_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_METHOD* SPVM_API_METHOD_new_api();

void SPVM_API_METHOD_free_api(SPVM_API_METHOD* api);

#endif
