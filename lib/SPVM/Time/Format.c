#include "spvm_native.h"

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int32_t SPNATIVE__SPVM__Time__Format__epoch_by_strptime(SPVM_ENV* env, SPVM_VALUE* stack) {
  const char* buf = (const char*)env->belems(env, stack[0].oval);
  const char* format = (const char*)env->belems(env, stack[1].oval);

  struct tm tm;
  if (!strptime(buf, format, &tm)) {
    SPVM_CROAK("Can't parse buffer like format", "SPVM/Time/Format.c", __LINE__);
  }

  stack[0].lval = mktime(&tm);

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Time__Format__strftime(SPVM_ENV* env, SPVM_VALUE* stack) {
  const char* format = (const char*)env->belems(env, stack[0].oval);
  time_t epoch = stack[1].lval;

  struct tm dt;
  gmtime_r(&epoch, &dt); // FIXME: only support UTC for now

  int32_t capacity = 100;
  void* obuffer = env->new_barray_raw(env, capacity);
  env->inc_ref_count(env, obuffer);
  char* buffer = (char *)(env->belems(env, obuffer));

  if (!strftime(buffer, capacity, format, &dt)) {
    env->dec_ref_count(env, obuffer);
    SPVM_CROAK("Can't write like format", "SPVM/Time/Format.c", __LINE__);
  }

  int32_t length = sprintf(buffer, "%s", buffer);
  void* oline = env->new_barray_raw(env, length);
  int8_t* line = env->belems(env, oline);
  memcpy(line, buffer, length);

  env->dec_ref_count(env, obuffer);
  stack[0].oval = oline;

  return SPVM_SUCCESS;
}
