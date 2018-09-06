#ifndef SPVM_RUNTIME_BUILDER_H
#define SPVM_RUNTIME_BUILDER_H

#include <stdio.h>

#include "spvm_base.h"
#include "spvm_native.h"

SPVM_ENV* SPVM_RUNTIME_BUILDER_build_runtime_env(SPVM_PORTABLE* portable);
SPVM_ENV* SPVM_RUNTIME_BUILDER_create_env(SPVM_RUNTIME* runtime);

#endif
