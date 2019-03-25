#include "spvm_native.h"

#include <stdlib.h>
#include <time.h>

int32_t SPNATIVE__SPVM__Time__Format__epoch_by_strptime(SPVM_ENV* env, SPVM_VALUE* stack) {
  const char* buf = (const char*)env->belems(env, stack[0].oval);
  const char* format = (const char*)env->belems(env, stack[1].oval);

  struct tm tm;
  if (!strptime(buf, format, &tm)) {
    SPVM_CROAK("Can't parse format", "SPVM/Time/Format.c", __LINE__);
  }

  stack[0].lval = mktime(&tm);

  return SPVM_SUCCESS;
}
