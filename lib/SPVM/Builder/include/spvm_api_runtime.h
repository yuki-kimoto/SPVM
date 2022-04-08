#ifndef SPVM_API_RUNTIME_H
#define SPVM_API_RUNTIME_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_RUNTIME* SPVM_API_RUNTIME_new_runtime();
void SPVM_API_RUNTIME_prepare(SPVM_RUNTIME* runtime);
SPVM_OPCODE* SPVM_API_RUNTIME_get_opcodes(SPVM_RUNTIME* runtime);
int32_t SPVM_API_RUNTIME_get_opcode_ids_length(SPVM_RUNTIME* runtime);
void SPVM_API_RUNTIME_free_runtime(SPVM_RUNTIME* runtime);

#endif
