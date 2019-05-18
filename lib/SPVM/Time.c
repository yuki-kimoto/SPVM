#ifndef _XOPEN_SOURCE
#  define _XOPEN_SOURCE
#endif

#include "spvm_native.h"

#include <time.h>
#include <string.h>
#include <locale.h>

static const char* MFILE = "SPVM/Time.c";

int32_t SPNATIVE__SPVM__Time__setlocale(SPVM_ENV* env, SPVM_VALUE* stack) {

  void* obj_str = stack[0].oval;
  if (!obj_str) { SPVM_DIE("String must be defined", MFILE, __LINE__); }
  const char* locale = (const char*)env->belems(env, obj_str);
  setlocale(LC_TIME, locale);

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Time__time(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int64_t timer_value = (int64_t)time(NULL);
  
  stack[0].lval = timer_value;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Time__localtime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  time_t time = (time_t)stack[0].lval;
  struct tm resultp;

  localtime_r(&time, &resultp);

  void* obj_time_info;
  SPVM_NEW_OBJ(env, obj_time_info, "SPVM::Time::Info", MFILE, __LINE__);

  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "sec", resultp.tm_sec, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "min", resultp.tm_min, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "hour", resultp.tm_hour, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "mday", resultp.tm_mday, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "mon", resultp.tm_mon, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "year", resultp.tm_year, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "wday", resultp.tm_wday, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "yday", resultp.tm_yday, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "isdst", resultp.tm_isdst, MFILE, __LINE__);
  
  stack[0].oval = obj_time_info;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Time__gmtime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  time_t time = (time_t)stack[0].lval;
  struct tm resultp;

  gmtime_r(&time, &resultp);

  void* obj_time_info;
  SPVM_NEW_OBJ(env, obj_time_info, "SPVM::Time::Info", MFILE, __LINE__);

  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "sec", resultp.tm_sec, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "min", resultp.tm_min, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "hour", resultp.tm_hour, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "mday", resultp.tm_mday, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "mon", resultp.tm_mon, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "year", resultp.tm_year, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "wday", resultp.tm_wday, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "yday", resultp.tm_yday, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "isdst", resultp.tm_isdst, MFILE, __LINE__);
  
  stack[0].oval = obj_time_info;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Time__strptime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_str = stack[0].oval;
  if (!obj_str) { SPVM_DIE("String must be defined", MFILE, __LINE__); }
  const char* str = (const char*)env->belems(env, obj_str);
  
  void* obj_format = stack[1].oval;
  if (!obj_format) { SPVM_DIE("Format must be defined", MFILE, __LINE__); }
  const char* format = (const char*)env->belems(env, obj_format);

  struct tm resultp;
  
  const char* end_ptr = strptime(str, format, &resultp);
  
  if (end_ptr && *end_ptr != '\0') {
    SPVM_DIE("Format parsing failed \"%s\"", end_ptr, MFILE, __LINE__);
  }
  else if (!end_ptr) {
    SPVM_DIE("Format parsing failed", MFILE, __LINE__);
  }

  void* obj_time_info;
  SPVM_NEW_OBJ(env, obj_time_info, "SPVM::Time::Info", MFILE, __LINE__);

  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "sec", resultp.tm_sec, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "min", resultp.tm_min, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "hour", resultp.tm_hour, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "mday", resultp.tm_mday, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "mon", resultp.tm_mon, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "year", resultp.tm_year, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "wday", resultp.tm_wday, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "yday", resultp.tm_yday, MFILE, __LINE__);
  SPVM_SET_IFIELD(env, obj_time_info, "SPVM::Time::Info", "isdst", resultp.tm_isdst, MFILE, __LINE__);
  
  stack[0].oval = obj_time_info;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Time__strftime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_format = stack[0].oval;
  if (!obj_format) { SPVM_DIE("Format must be defined", MFILE, __LINE__); }
  const char* format = (const char*)env->belems(env, obj_format);
  
  void* obj_time_info = stack[1].oval;
  if (!obj_time_info) { SPVM_DIE("SPVM::Time::Info object must be defined", MFILE, __LINE__); }

  struct tm resultp;

  SPVM_IFIELD(env, resultp.tm_sec, obj_time_info, "SPVM::Time::Info", "sec", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_min, obj_time_info, "SPVM::Time::Info", "min", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_hour, obj_time_info, "SPVM::Time::Info", "hour", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_mday, obj_time_info, "SPVM::Time::Info", "mday", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_mon, obj_time_info, "SPVM::Time::Info", "mon", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_year, obj_time_info, "SPVM::Time::Info", "year", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_wday, obj_time_info, "SPVM::Time::Info", "wday", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_yday, obj_time_info, "SPVM::Time::Info", "yday", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_isdst, obj_time_info, "SPVM::Time::Info", "isdst", MFILE, __LINE__);
  
  char str[256] = {0};
  int32_t count = strftime(str, 256, format, &resultp);
  
  if (count == 0) {
    SPVM_DIE("strftime fail", MFILE, __LINE__);
  }

  void* obj_str = env->new_str_len(env, str, strlen(str));
  
  stack[0].oval = obj_str;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Time__mktime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  if (!obj_time_info) { SPVM_DIE("SPVM::Time::Info object must be defined", MFILE, __LINE__); }

  struct tm resultp;

  SPVM_IFIELD(env, resultp.tm_sec, obj_time_info, "SPVM::Time::Info", "sec", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_min, obj_time_info, "SPVM::Time::Info", "min", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_hour, obj_time_info, "SPVM::Time::Info", "hour", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_mday, obj_time_info, "SPVM::Time::Info", "mday", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_mon, obj_time_info, "SPVM::Time::Info", "mon", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_year, obj_time_info, "SPVM::Time::Info", "year", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_wday, obj_time_info, "SPVM::Time::Info", "wday", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_yday, obj_time_info, "SPVM::Time::Info", "yday", MFILE, __LINE__);
  SPVM_IFIELD(env, resultp.tm_isdst, obj_time_info, "SPVM::Time::Info", "isdst", MFILE, __LINE__);
  
  int64_t ltime = (int64_t)mktime(&resultp);
  
  stack[0].lval = ltime;
  
  return SPVM_SUCCESS;
}
