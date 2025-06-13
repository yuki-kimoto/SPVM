// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_INTERNAL_H
#define SPVM_API_INTERNAL_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_INTERNAL* SPVM_API_INTERNAL_new_api();

void SPVM_API_INTERNAL_free_api(SPVM_API_INTERNAL* internal);

#endif
