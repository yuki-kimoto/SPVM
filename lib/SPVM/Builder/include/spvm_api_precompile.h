// Copyright (c) 2023 Yuki Kimoto
// MIT License

#ifndef SPVM_API_PRECOMPILE_H
#define SPVM_API_PRECOMPILE_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_ENV_PRECOMPILE* SPVM_API_PRECOMPILE_new_env();
SPVM_PRECOMPILE* SPVM_API_PRECOMPILE_new_object();
void SPVM_API_PRECOMPILE_free_object(SPVM_PRECOMPILE* precompile);
void SPVM_API_PRECOMPILE_set_runtime(SPVM_PRECOMPILE* precompile, SPVM_RUNTIME* runtime);
SPVM_RUNTIME* SPVM_API_PRECOMPILE_get_runtime(SPVM_PRECOMPILE* precompile);
void SPVM_API_PRECOMPILE_build_class_source(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* class_name);
void SPVM_API_PRECOMPILE_build_method_source(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* class_name, const char* method_name);

#endif
