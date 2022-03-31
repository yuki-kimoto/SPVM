#ifndef SPVM_API_COMPILER_H
#define SPVM_API_COMPILER_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_ENV_COMPILER* SPVM_API_COMPILER_new_env_raw();
int32_t SPVM_API_COMPILER_get_next_method_id_flag(SPVM_ENV_COMPILER* env_compiler, const char* method_abs_name, int32_t start_index, int32_t flag);
int32_t SPVM_API_COMPILER_get_class_id(SPVM_ENV_COMPILER* env_compiler, const char* class_name);
int32_t SPVM_API_COMPILER_get_classes_length(SPVM_ENV_COMPILER* env_compiler);
const char* SPVM_API_COMPILER_get_class_name(SPVM_ENV_COMPILER* env_compiler, int32_t class_id);
const char* SPVM_API_COMPILER_get_class_module_file(SPVM_ENV_COMPILER* env_compiler, int32_t class_id);
int32_t SPVM_API_COMPILER_get_method_class_id(SPVM_ENV_COMPILER* env_compiler, int32_t method_id);
int32_t SPVM_API_COMPILER_is_anon_class(SPVM_ENV_COMPILER* env_compiler, int32_t class_id);
int32_t SPVM_API_COMPILER_get_methods_length(SPVM_ENV_COMPILER* env_compiler, int32_t class_id);
int32_t SPVM_API_COMPILER_get_method_id(SPVM_ENV_COMPILER* env_compiler, int32_t class_id, int32_t method_index_of_class);
int32_t SPVM_API_COMPILER_get_method_id_by_name(SPVM_ENV_COMPILER* env_compiler, const char* class_name, const char* method_name);
const char* SPVM_API_COMPILER_get_method_name(SPVM_ENV_COMPILER* env_compiler, int32_t method_id);
int32_t SPVM_API_COMPILER_is_anon_method(SPVM_ENV_COMPILER* env_compiler, int32_t method_id);
int32_t SPVM_API_COMPILER_is_init_block_method(SPVM_ENV_COMPILER* env_compiler, int32_t method_id);
int32_t SPVM_API_COMPILER_is_native_method(SPVM_ENV_COMPILER* env_compiler, int32_t method_id);
int32_t SPVM_API_COMPILER_is_precompile_method(SPVM_ENV_COMPILER* env_compiler, int32_t method_id);
const char* SPVM_API_COMPILER_get_method_signature(SPVM_ENV_COMPILER* env_compiler, int32_t method_id);
void* SPVM_API_COMPILER_get_native_method_address(SPVM_ENV_COMPILER* env_compiler, int32_t method_id);
void* SPVM_API_COMPILER_get_precompile_method_address(SPVM_ENV_COMPILER* env_compiler, int32_t method_id);
void SPVM_API_COMPILER_set_native_method_address(SPVM_ENV_COMPILER* env_compiler, int32_t method_id, void* address);
void SPVM_API_COMPILER_set_precompile_method_address(SPVM_ENV_COMPILER* env_compiler, int32_t method_id, void* address);
const char* SPVM_API_COMPILER_get_method_abs_name(SPVM_ENV_COMPILER* env_compiler, int32_t method_id);
SPVM_COMPILER* SPVM_API_COMPILER_new();
void SPVM_API_COMPILER_set_start_line(SPVM_ENV_COMPILER* env_compiler, int32_t start_line);
int32_t SPVM_API_COMPILER_get_start_line(SPVM_ENV_COMPILER* env_compiler);
void SPVM_API_COMPILER_set_start_file(SPVM_ENV_COMPILER* env_compiler, const char* start_file);
const char* SPVM_API_COMPILER_get_start_file(SPVM_ENV_COMPILER* env_compiler);
void SPVM_API_COMPILER_add_module_dir(SPVM_ENV_COMPILER* env_compiler, const char* module_dir);
int32_t SPVM_API_COMPILER_get_module_dirs_length (SPVM_ENV* env, SPVM_ENV_COMPILER* env_compiler);
const char* SPVM_API_COMPILER_get_module_dir (SPVM_ENV* env, SPVM_ENV_COMPILER* env_compiler, int32_t module_dir_id);
int32_t SPVM_API_COMPILER_compile_spvm(SPVM_ENV_COMPILER* env_compiler, const char* class_name);
void SPVM_API_COMPILER_build_runtime(SPVM_ENV_COMPILER* env_compiler, SPVM_RUNTIME* runtime);
void SPVM_API_COMPILER_free(SPVM_ENV_COMPILER* env_compiler);
const char* SPVM_API_COMPILER_get_module_source(SPVM_ENV_COMPILER* env_compiler, const char* class_name);
int32_t SPVM_API_COMPILER_get_error_messages_length(SPVM_ENV_COMPILER* env_compiler);
const char* SPVM_API_COMPILER_get_error_message(SPVM_ENV_COMPILER* env_compiler, int32_t index);

#endif
