#ifndef SPVM_API_RUNTIME_H
#define SPVM_API_RUNTIME_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_ENV_RUNTIME* SPVM_API_RUNTIME_new_env_raw();
void SPVM_API_RUNTIME_prepare(SPVM_ENV_RUNTIME* env_runtime);
SPVM_OPCODE* SPVM_API_RUNTIME_get_opcodes(SPVM_ENV_RUNTIME* env_runtime);
int32_t SPVM_API_RUNTIME_get_opcode_ids_length(SPVM_ENV_RUNTIME* env_runtime);
void SPVM_API_RUNTIME_free(SPVM_ENV_RUNTIME* env_runtime);

#endif
