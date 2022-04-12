#include "spvm_native.h"

#include "spvm_precompile.h"
#include "spvm_api_precompile.h"

SPVM_API_PRECOMPILE* SPVM_API_PRECOMPILE_new_precompile() {
  SPVM_API_PRECOMPILE* precompile = SPVM_API_PRECOMPILE_new(precompile);
  return precompile;
}

void SPVM_API_PRECOMPILE_free_precompile(SPVM_API_PRECOMPILE* precompile) {
  SPVM_API_PRECOMPILE_free(precompile);
}

void SPVM_API_PRECOMPILE_set_runtime(SPVM_API_PRECOMPILE* precompile, SPVM_RUNTIME* runtime) {
  SPVM_API_PRECOMPILE_set_runtime(precompile, runtime);
}

SPVM_RUNTIME* SPVM_API_PRECOMPILE_get_runtime(SPVM_API_PRECOMPILE* precompile) {
  return SPVM_API_PRECOMPILE_get_runtime(precompile, runtime);
}

void SPVM_API_PRECOMPILE_create_precompile_source(SPVM_API_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* class_name) {
  SPVM_PRECOMPILE_create_precompile_source(precompile, string_buffer, class_name);
}
