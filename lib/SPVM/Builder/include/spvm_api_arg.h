// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_ARG_H
#define SPVM_API_ARG_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_ARG* SPVM_API_ARG_new_api();

void SPVM_API_ARG_free_api(SPVM_API_ARG* api);

#endif
