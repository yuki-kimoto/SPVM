#include "spvm_native.h"

#include <time.h>

static const char* MFILE = "SPVM/Time.c";

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
