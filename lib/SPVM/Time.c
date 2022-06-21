#include "spvm_native.h"

#include <time.h>

static const char* FILE_NAME = "SPVM/Time.c";

int32_t SPVM__Time__time(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int64_t epoch = (int64_t)time(NULL);
  
  stack[0].lval = epoch;
  
  return 0;
}

int32_t SPVM__Time__localtime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e;
  
  time_t time = (time_t)stack[0].lval;
  struct tm* st_tm = env->alloc_memory_block_zero(env, sizeof(struct tm));
  
#ifdef _WIN32
  localtime_s(st_tm, &time);
#else
  localtime_r(&time, st_tm);
#endif
  
  void* obj_time_info = env->new_pointer_by_name(env, stack, "Time::Info", st_tm, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_time_info;
  
  return 0;
}

int32_t SPVM__Time__gmtime(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t e;
  
  time_t time = (time_t)stack[0].lval;
  struct tm* st_tm = env->alloc_memory_block_zero(env, sizeof(struct tm));
  
#ifdef _WIN32
  gmtime_s(st_tm, &time);
#else
  gmtime_r(&time, st_tm);
#endif
  
  void* obj_time_info = env->new_pointer_by_name(env, stack, "Time::Info", st_tm, &e, FILE_NAME, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = obj_time_info;
  
  return 0;
}

int32_t SPVM__Time__timelocal(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t e;
  
  void* obj_time_info = stack[0].oval;
  if (!obj_time_info) { return env->die(env, stack, "Time::Info object must be defined", FILE_NAME, __LINE__); }
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_time_info);

  int64_t ltime = (int64_t)mktime(st_tm);
  
  stack[0].lval = ltime;
  
  return 0;
}

int32_t SPVM__Time__timegm(SPVM_ENV* env, SPVM_VALUE* stack) {
  int32_t e;
  
  void* obj_time_info = stack[0].oval;
  if (!obj_time_info) { return env->die(env, stack, "Time::Info object must be defined", FILE_NAME, __LINE__); }
  
  struct tm* st_tm = env->get_pointer(env, stack, obj_time_info);
  
#ifdef _WIN32
  int64_t time = (int64_t)_mkgmtime(st_tm);
#else
  int64_t time = (int64_t)timegm(st_tm);
#endif
  
  stack[0].lval = time;
  
  return 0;
}
