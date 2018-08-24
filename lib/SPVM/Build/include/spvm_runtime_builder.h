#ifndef SPVM_RUNTIME_BUILDER_H
#define SPVM_RUNTIME_BUILDER_H

#include <stdio.h>

#include "spvm_base.h"
#include "spvm_native.h"

int32_t SPVM_RUNTIME_BUILDER_push_runtime_string(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, const char* string);
void SPVM_RUNTIME_BUILDER_push_portable_basic_type(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_BASIC_TYPE* basic_type);
void SPVM_RUNTIME_BUILDER_push_portable_field(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_FIELD* field);
void SPVM_RUNTIME_BUILDER_push_portable_package_var(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_PACKAGE_VAR* package_var);
void SPVM_RUNTIME_BUILDER_push_portable_sub(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_SUB* sub);
void SPVM_RUNTIME_BUILDER_push_portable_package(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_PACKAGE* package);
void SPVM_RUNTIME_BUILDER_push_portable_arg(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_MY* my);
SPVM_RUNTIME* SPVM_RUNTIME_BUILDER_build_runtime(SPVM_COMPILER* compiler);

#endif
