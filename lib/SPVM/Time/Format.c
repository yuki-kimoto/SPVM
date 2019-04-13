#include "spvm_native.h"

#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <locale.h>

int32_t SPNATIVE__SPVM__Time__Format__epoch_by_strptime(SPVM_ENV* env, SPVM_VALUE* stack) {
  if (!stack[0].oval) {
    SPVM_DIE("buffer must not be undef", "SPVM/Time/Format.c", __LINE__);
  }
  if (!stack[1].oval) {
    SPVM_DIE("format must not be undef", "SPVM/Time/Format.c", __LINE__);
  }
  if (!stack[2].oval) {
    SPVM_DIE("locale must not be undef", "SPVM/Time/Format.c", __LINE__);
  }
  const char* buf = (const char*)env->belems(env, stack[0].oval);
  const char* format = (const char*)env->belems(env, stack[1].oval);
  const char* locale = (const char*)env->belems(env, stack[2].oval);

  struct tm tm;
  char *prev_locale = setlocale(LC_TIME, NULL);
  setlocale(LC_TIME, locale);
  if (strptime(buf, format, &tm) == NULL) {
    setlocale(LC_TIME, prev_locale);
    SPVM_DIE("Can't parse buffer like format", "SPVM/Time/Format.c", __LINE__);
  }
  setlocale(LC_TIME, prev_locale);

  stack[0].lval = mktime(&tm);

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Time__Format__strftime(SPVM_ENV* env, SPVM_VALUE* stack) {
  if (!stack[0].oval) {
    SPVM_DIE("format must not be undef", "SPVM/Time/Format.c", __LINE__);
  }
  if (!stack[2].oval) {
    SPVM_DIE("locale must not be undef", "SPVM/Time/Format.c", __LINE__);
  }
  const char* format = (const char*)env->belems(env, stack[0].oval);
  time_t epoch = stack[1].lval;
  const char* locale = (const char*)env->belems(env, stack[2].oval);

  struct tm dt;
  gmtime_r(&epoch, &dt); // FIXME: only support UTC for now

  int32_t capacity = 100;
  void* obuffer = env->new_barray_raw(env, capacity);
  env->inc_ref_count(env, obuffer);
  char* buffer = (char *)(env->belems(env, obuffer));

  char *prev_locale = setlocale(LC_TIME, NULL);
  setlocale(LC_TIME, locale);
  if (!strftime(buffer, capacity, format, &dt)) {
    setlocale(LC_TIME, prev_locale);
    env->dec_ref_count(env, obuffer);
    SPVM_DIE("Can't write like format", "SPVM/Time/Format.c", __LINE__);
  }
  setlocale(LC_TIME, prev_locale);

  int32_t length = sprintf(buffer, "%s", buffer);
  void* oline = env->new_barray_raw(env, length);
  int8_t* line = env->belems(env, oline);
  memcpy(line, buffer, length);

  env->dec_ref_count(env, obuffer);
  stack[0].oval = oline;

  return SPVM_SUCCESS;
}
