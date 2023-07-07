// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_CLASS_VAR_H
#define SPVM_API_CLASS_VAR_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_CLASS_VAR* SPVM_API_CLASS_VAR_new_api();

void SPVM_API_CLASS_VAR_free_api(SPVM_API_CLASS_VAR* api);

#endif
