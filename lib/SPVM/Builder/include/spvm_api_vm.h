#ifndef SPVM_VM_H
#define SPVM_VM_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

int32_t SPVM_API_VM_call_spvm_method_vm(SPVM_ENV* env, SPVM_VALUE* stack, int32_t method_id, int32_t args_stack_length);

#endif
