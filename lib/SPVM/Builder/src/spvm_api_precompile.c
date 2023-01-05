#include <stdlib.h>

#include "spvm_native.h"

#include "spvm_runtime.h"
#include "spvm_precompile.h"
#include "spvm_api_precompile.h"

SPVM_ENV_PRECOMPILE* SPVM_API_PRECOMPILE_new_env() {
  void* env_precompile_init[]  = {
    SPVM_API_PRECOMPILE_new_object,
    SPVM_API_PRECOMPILE_free_object,
    SPVM_API_PRECOMPILE_set_runtime,
    SPVM_API_PRECOMPILE_get_runtime,
    SPVM_API_PRECOMPILE_build_class_source,
    SPVM_API_PRECOMPILE_build_method_source,
  };
  SPVM_ENV_PRECOMPILE* env_precompile = calloc(1, sizeof(env_precompile_init));
  memcpy(env_precompile, env_precompile_init, sizeof(env_precompile_init));
  
  return env_precompile;
}

SPVM_PRECOMPILE* SPVM_API_PRECOMPILE_new_object() {
  SPVM_PRECOMPILE* precompile = SPVM_PRECOMPILE_new(precompile);
  return precompile;
}

void SPVM_API_PRECOMPILE_free_object(SPVM_PRECOMPILE* precompile) {
  SPVM_PRECOMPILE_free(precompile);
}

void SPVM_API_PRECOMPILE_set_runtime(SPVM_PRECOMPILE* precompile, SPVM_RUNTIME* runtime) {
  SPVM_PRECOMPILE_set_runtime(precompile, runtime);
}

SPVM_RUNTIME* SPVM_API_PRECOMPILE_get_runtime(SPVM_PRECOMPILE* precompile) {
  return SPVM_PRECOMPILE_get_runtime(precompile);
}

void SPVM_API_PRECOMPILE_build_class_source(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* class_name) {
  SPVM_PRECOMPILE_build_class_source(precompile, string_buffer, class_name);
}

void SPVM_API_PRECOMPILE_build_method_source(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* class_name, const char* method_name) {
  SPVM_PRECOMPILE_build_method_source(precompile, string_buffer, class_name, method_name);
}
