// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_CFUNC_H
#define SPVM_API_CFUNC_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_CFUNC* SPVM_API_CFUNC_new_api();

void SPVM_API_CFUNC_free_api(SPVM_API_CFUNC* cfunc);

#endif
