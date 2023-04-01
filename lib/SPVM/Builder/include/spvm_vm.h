// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_VM_H
#define SPVM_VM_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

int32_t SPVM_VM_call_method(SPVM_ENV* env, SPVM_VALUE* stack, int32_t method_id, int32_t args_stack_length);

#endif
