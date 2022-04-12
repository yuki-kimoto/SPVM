#include "spvm_native.h"

#include "spvm_precompile.h"
#include "spvm_api_precompile.h"

SPVM_PRECOMPILE* SPVM_API_PRECOMPILE_new_precompile() {
  SPVM_PRECOMPILE* precompile = SPVM_PRECOMPILE_new(precompile);

  return precompile;
}

void SPVM_API_PRECOMPILE_free_precompile(SPVM_PRECOMPILE* precompile) {
  SPVM_PRECOMPILE_free(precompile);
}

void SPVM_PRECOMPILE_set_runtime(SPVM_PRECOMPILE* precompile, SPVM_RUNTIME* runtime) {
  SPVM_PRECOMPILE_set_runtime(precompile, runtime);
}

SPVM_RUNTIME* SPVM_PRECOMPILE_get_runtime(SPVM_PRECOMPILE* precompile) {
  return SPVM_PRECOMPILE_get_runtime(precompile, runtime);
}
