#ifndef _XOPEN_SOURCE
#  define _XOPEN_SOURCE
#endif

#include "spvm_native.h"

#include <stdlib.h>
#include <time.h>

// FIXME: Remove duplication between Moment.c and Format.c
int32_t SPNATIVE__SPVM__Time__Moment__strptime(SPVM_ENV* env, SPVM_VALUE* stack) {
  const char* buf = (const char*)env->belems(env, stack[0].oval);
  const char* format = (const char*)env->belems(env, stack[1].oval);

  struct tm dt;
  if (!strptime(buf, format, &dt)) {
    return SPVM_EXCEPTION;
  }

  stack[0].ival = dt.tm_sec;
  stack[1].ival = dt.tm_min;
  stack[2].ival = dt.tm_hour;
  stack[3].ival = dt.tm_mday;
  stack[4].ival = dt.tm_mon;
  stack[5].ival = dt.tm_year;
  stack[6].ival = dt.tm_wday;
  stack[7].ival = dt.tm_yday;
  stack[8].ival = dt.tm_isdst;

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Time__Moment__gmtime(SPVM_ENV* env, SPVM_VALUE* stack) {
  time_t epoch = stack[0].lval;

  struct tm dt;
  gmtime_r(&epoch, &dt);

  stack[0].ival = dt.tm_sec;
  stack[1].ival = dt.tm_min;
  stack[2].ival = dt.tm_hour;
  stack[3].ival = dt.tm_mday;
  stack[4].ival = dt.tm_mon;
  stack[5].ival = dt.tm_year;
  stack[6].ival = dt.tm_wday;
  stack[7].ival = dt.tm_yday;
  stack[8].ival = dt.tm_isdst;

  return SPVM_SUCCESS;
}
