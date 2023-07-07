// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_FIELD_H
#define SPVM_API_FIELD_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_API_FIELD* SPVM_API_FIELD_new_api();

void SPVM_API_FIELD_free_api(SPVM_API_FIELD* api);

#endif
