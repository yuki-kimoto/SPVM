#include "spvm_native.h"

#include "spvm_opcode.h"
#include "spvm_runtime.h"
#include "spvm_api_runtime.h"

SPVM_ENV_RUNTIME* SPVM_API_RUNTIME_new_env_raw() {
  
  return NULL;
}

void SPVM_API_RUNTIME_prepare(SPVM_ENV_RUNTIME* env_runtime) {

  SPVM_RUNTIME* runtime = env_runtime->runtime;

  SPVM_RUNTIME_prepare(runtime);
}

SPVM_OPCODE* SPVM_API_RUNTIME_get_opcodes(SPVM_ENV_RUNTIME* env_runtime) {

  SPVM_RUNTIME* runtime = env_runtime->runtime;
  
  return runtime->opcodes;
}

int32_t SPVM_API_RUNTIME_get_opcode_ids_length(SPVM_ENV_RUNTIME* env_runtime) {
  
  SPVM_RUNTIME* runtime = env_runtime->runtime;
  
  return runtime->opcode_ids_length;
}

void SPVM_API_RUNTIME_free(SPVM_ENV_RUNTIME* env_runtime) {

  SPVM_RUNTIME* runtime = env_runtime->runtime;
  
  SPVM_RUNTIME_free(runtime);
}
