#ifndef SPVM_EXE_CSOURCE_BUILDER_H
#define SPVM_EXE_CSOURCE_BUILDER_H

#include <stdio.h>

#include "spvm_base.h"
#include "spvm_native.h"

void SPVM_EXE_CSOURCE_BUILDER_build_exe_csource(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, SPVM_PORTABLE* portable, const char* package_name);

#endif
