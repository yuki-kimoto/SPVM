#include "spvm_native.h"

#include "spvm_opcode.h"
#include "spvm_runtime.h"
#include "spvm_api_runtime.h"

void SPVM_API_RUNTIME_prepare(SPVM_RUNTIME* runtime) {

  SPVM_RUNTIME_prepare(runtime);
}

SPVM_OPCODE* SPVM_API_RUNTIME_get_opcodes(SPVM_RUNTIME* runtime) {

  return runtime->opcodes;
}

int32_t SPVM_API_RUNTIME_get_opcode_ids_length(SPVM_RUNTIME* runtime) {
  
  return runtime->opcode_ids_length;
}

void SPVM_API_RUNTIME_free(SPVM_RUNTIME* runtime) {

  SPVM_RUNTIME_free(runtime);
}
