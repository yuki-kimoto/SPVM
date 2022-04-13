#ifndef SPVM_API_PRECOMPILE_H
#define SPVM_API_PRECOMPILE_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_ENV_PRECOMPILE* SPVM_API_PRECOMPILE_new_env();
SPVM_PRECOMPILE* SPVM_API_PRECOMPILE_new_precompile();
void SPVM_API_PRECOMPILE_free_precompile(SPVM_PRECOMPILE* precompile);
void SPVM_API_PRECOMPILE_set_runtime(SPVM_PRECOMPILE* precompile, SPVM_RUNTIME* runtime);
SPVM_RUNTIME* SPVM_API_PRECOMPILE_get_runtime(SPVM_PRECOMPILE* precompile);
void SPVM_API_PRECOMPILE_create_precompile_source(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* class_name);

#endif
