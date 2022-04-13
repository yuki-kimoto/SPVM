#include "spvm_native.h"

#include "spvm_runtime.h"
#include "spvm_precompile.h"
#include "spvm_api_precompile.h"

SPVM_PRECOMPILE* SPVM_API_PRECOMPILE_new_precompile() {
  SPVM_PRECOMPILE* precompile = SPVM_PRECOMPILE_new(precompile);
  return precompile;
}

void SPVM_API_PRECOMPILE_free_precompile(SPVM_PRECOMPILE* precompile) {
  SPVM_PRECOMPILE_free(precompile);
}

void SPVM_API_PRECOMPILE_set_runtime(SPVM_PRECOMPILE* precompile, SPVM_RUNTIME* runtime) {
  SPVM_PRECOMPILE_set_runtime(precompile, runtime);
}

SPVM_RUNTIME* SPVM_API_PRECOMPILE_get_runtime(SPVM_PRECOMPILE* precompile) {
  return SPVM_PRECOMPILE_get_runtime(precompile);
}

void SPVM_API_PRECOMPILE_create_precompile_source(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* class_name) {
  SPVM_PRECOMPILE_create_precompile_source(precompile, string_buffer, class_name);
}
