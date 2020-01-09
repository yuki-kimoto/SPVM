#ifndef SPVM_CSOURCE_BUILDER_EXE_H
#define SPVM_CSOURCE_BUILDER_EXE_H

#include <stdio.h>

#include "spvm_base.h"
#include "spvm_native.h"

void SPVM_CSOURCE_BUILDER_EXE_build_exe_csource(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, SPVM_RUNTIME_INFO* runtime_info, const char* package_name);

#endif
