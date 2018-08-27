#ifndef SPVM_RUNTIME_BUILDER_H
#define SPVM_RUNTIME_BUILDER_H

#include <stdio.h>

#include "spvm_base.h"
#include "spvm_native.h"

SPVM_RUNTIME* SPVM_RUNTIME_BUILDER_build_runtime(SPVM_PORTABLE* portable);

#endif
