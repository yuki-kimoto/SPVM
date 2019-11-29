#include "spvm_native.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <float.h>
#include <complex.h>
#include <memory.h>
#include <ctype.h>
#include <errno.h>

static const char* MFILE = "SPVM/CORE.c";

int32_t SPNATIVE__SPVM__CORE__DBL_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = DBL_MAX;
  
  return SPVM_SUCCESS;
}
