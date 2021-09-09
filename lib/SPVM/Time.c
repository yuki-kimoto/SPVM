#include "spvm_native.h"

#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>

static const char* MFILE = "SPVM/Time.c";

int32_t SPVM__Time__time(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int64_t timer_value = (int64_t)time(NULL);
  
  stack[0].lval = timer_value;
  
  return 0;
}

int32_t SPVM__Time__localtime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e;
  
  time_t time = (time_t)stack[0].lval;
  struct tm* resultp = localtime(&time);

  void* obj_time_info = env->new_object_by_name(env, "Time::Info", &e, MFILE, __LINE__);
  if (e) { return e; }

  env->set_field_int_by_name(env, obj_time_info, "Time::Info", "sec", resultp->tm_sec, &e, MFILE, __LINE__);
  env->set_field_int_by_name(env, obj_time_info, "Time::Info", "min", resultp->tm_min, &e, MFILE, __LINE__);
  env->set_field_int_by_name(env, obj_time_info, "Time::Info", "hour", resultp->tm_hour, &e, MFILE, __LINE__);
  env->set_field_int_by_name(env, obj_time_info, "Time::Info", "mday", resultp->tm_mday, &e, MFILE, __LINE__);
  env->set_field_int_by_name(env, obj_time_info, "Time::Info", "mon", resultp->tm_mon, &e, MFILE, __LINE__);
  env->set_field_int_by_name(env, obj_time_info, "Time::Info", "year", resultp->tm_year, &e, MFILE, __LINE__);
  env->set_field_int_by_name(env, obj_time_info, "Time::Info", "wday", resultp->tm_wday, &e, MFILE, __LINE__);
  env->set_field_int_by_name(env, obj_time_info, "Time::Info", "yday", resultp->tm_yday, &e, MFILE, __LINE__);
  env->set_field_int_by_name(env, obj_time_info, "Time::Info", "isdst", resultp->tm_isdst, &e, MFILE, __LINE__);
  
  stack[0].oval = obj_time_info;
  
  return 0;
}

int32_t SPVM__Time__gmtime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e;

  time_t time = (time_t)stack[0].lval;
  struct tm* resultp = gmtime(&time);

  void* obj_time_info = env->new_object_by_name(env, "Time::Info", &e, MFILE, __LINE__);
  if (e) { return e; }

  env->set_field_int_by_name(env, obj_time_info, "Time::Info", "sec", resultp->tm_sec, &e, MFILE, __LINE__);
  env->set_field_int_by_name(env, obj_time_info, "Time::Info", "min", resultp->tm_min, &e, MFILE, __LINE__);
  env->set_field_int_by_name(env, obj_time_info, "Time::Info", "hour", resultp->tm_hour, &e, MFILE, __LINE__);
  env->set_field_int_by_name(env, obj_time_info, "Time::Info", "mday", resultp->tm_mday, &e, MFILE, __LINE__);
  env->set_field_int_by_name(env, obj_time_info, "Time::Info", "mon", resultp->tm_mon, &e, MFILE, __LINE__);
  env->set_field_int_by_name(env, obj_time_info, "Time::Info", "year", resultp->tm_year, &e, MFILE, __LINE__);
  env->set_field_int_by_name(env, obj_time_info, "Time::Info", "wday", resultp->tm_wday, &e, MFILE, __LINE__);
  env->set_field_int_by_name(env, obj_time_info, "Time::Info", "yday", resultp->tm_yday, &e, MFILE, __LINE__);
  env->set_field_int_by_name(env, obj_time_info, "Time::Info", "isdst", resultp->tm_isdst, &e, MFILE, __LINE__);
  
  stack[0].oval = obj_time_info;
  
  return 0;
}

int32_t SPVM__Time__timelocal(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t e;
  
  void* obj_time_info = stack[0].oval;
  if (!obj_time_info) { return env->die(env, "Time::Info object must be defined", MFILE, __LINE__); }

  struct tm resultp;

  resultp.tm_sec = env->get_field_int_by_name(env, obj_time_info, "Time::Info", "sec", &e, MFILE, __LINE__);
  resultp.tm_min = env->get_field_int_by_name(env, obj_time_info, "Time::Info", "min", &e, MFILE, __LINE__);
  resultp.tm_hour = env->get_field_int_by_name(env, obj_time_info, "Time::Info", "hour", &e, MFILE, __LINE__);
  resultp.tm_mday = env->get_field_int_by_name(env, obj_time_info, "Time::Info", "mday", &e, MFILE, __LINE__);
  resultp.tm_mon = env->get_field_int_by_name(env, obj_time_info, "Time::Info", "mon", &e, MFILE, __LINE__);
  resultp.tm_year = env->get_field_int_by_name(env, obj_time_info, "Time::Info", "year", &e, MFILE, __LINE__);
  resultp.tm_wday = env->get_field_int_by_name(env, obj_time_info, "Time::Info", "wday", &e, MFILE, __LINE__);
  resultp.tm_yday = env->get_field_int_by_name(env, obj_time_info, "Time::Info", "yday", &e, MFILE, __LINE__);
  resultp.tm_isdst = env->get_field_int_by_name(env, obj_time_info, "Time::Info", "isdst", &e, MFILE, __LINE__);
  
  int64_t ltime = (int64_t)mktime(&resultp);
  
  stack[0].lval = ltime;
  
  return 0;
}
