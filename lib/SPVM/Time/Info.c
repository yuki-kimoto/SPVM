#include "spvm_native.h"

#include <time.h>

static const char* FILE_NAME = "SPVM/Time/Info.c";

int32_t SPVM__Time__Info__new(SPVM_ENV* env, SPVM_VALUE* stack) {

  int32_t e;
  
  struct tm* st_tm = env->alloc_memory_block_zero(env, sizeof(struct tm));
  
  void* obj_time_info = env->new_pointer_by_name(env, "Time::Info", st_tm, &e, FILE_NAME, __LINE__);
  if (e) { return e; }

  stack[0].oval = obj_time_info;
  
  return 0;
}

int32_t SPVM__Time__Info__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  if (obj_time_info != NULL) {
    struct tm* st_tm = env->get_pointer(env, obj_time_info);
    env->free_memory_block(env, st_tm);
  }
  
  return 0;
}

int32_t SPVM__Time__Info__sec(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  
  struct tm* st_tm = env->get_pointer(env, obj_time_info);
  
  stack[0].ival = st_tm->tm_sec;
  
  return 0;
}

int32_t SPVM__Time__Info__min(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  
  struct tm* st_tm = env->get_pointer(env, obj_time_info);
  
  stack[0].ival = st_tm->tm_min;
  
  return 0;
}
int32_t SPVM__Time__Info__hour(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  
  struct tm* st_tm = env->get_pointer(env, obj_time_info);
  
  stack[0].ival = st_tm->tm_hour;
  
  return 0;
}

int32_t SPVM__Time__Info__mday(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  
  struct tm* st_tm = env->get_pointer(env, obj_time_info);
  
  stack[0].ival = st_tm->tm_mday;
  
  return 0;
}

int32_t SPVM__Time__Info__mon(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  
  struct tm* st_tm = env->get_pointer(env, obj_time_info);
  
  stack[0].ival = st_tm->tm_mon;
  
  return 0;
}

int32_t SPVM__Time__Info__year(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  
  struct tm* st_tm = env->get_pointer(env, obj_time_info);
  
  stack[0].ival = st_tm->tm_year;
  
  return 0;
}

int32_t SPVM__Time__Info__wday(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  
  struct tm* st_tm = env->get_pointer(env, obj_time_info);
  
  stack[0].ival = st_tm->tm_wday;
  
  return 0;
}

int32_t SPVM__Time__Info__yday(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  
  struct tm* st_tm = env->get_pointer(env, obj_time_info);
  
  stack[0].ival = st_tm->tm_yday;
  
  return 0;
}

int32_t SPVM__Time__Info__isdst(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  
  struct tm* st_tm = env->get_pointer(env, obj_time_info);
  
  stack[0].ival = st_tm->tm_isdst;
  
  return 0;
}

int32_t SPVM__Time__Info__set_sec(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  
  int32_t sec = stack[1].ival;
  
  struct tm* st_tm = env->get_pointer(env, obj_time_info);
  
  st_tm->tm_sec = sec;
  
  return 0;
}

int32_t SPVM__Time__Info__set_min(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  
  int32_t min = stack[1].ival;
  
  struct tm* st_tm = env->get_pointer(env, obj_time_info);
  
  st_tm->tm_min = min;
  
  return 0;
}

int32_t SPVM__Time__Info__set_hour(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  
  int32_t hour = stack[1].ival;
  
  struct tm* st_tm = env->get_pointer(env, obj_time_info);
  
  st_tm->tm_hour = hour;
  
  return 0;
}

int32_t SPVM__Time__Info__set_mday(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  
  int32_t mday = stack[1].ival;
  
  struct tm* st_tm = env->get_pointer(env, obj_time_info);
  
  st_tm->tm_mday = mday;
  
  return 0;
}

int32_t SPVM__Time__Info__set_mon(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  
  int32_t mon = stack[1].ival;
  
  struct tm* st_tm = env->get_pointer(env, obj_time_info);
  
  st_tm->tm_mon = mon;
  
  return 0;
}

int32_t SPVM__Time__Info__set_year(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  
  int32_t year = stack[1].ival;
  
  struct tm* st_tm = env->get_pointer(env, obj_time_info);
  
  st_tm->tm_year = year;
  
  return 0;
}

int32_t SPVM__Time__Info__set_wday(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  
  int32_t wday = stack[1].ival;
  
  struct tm* st_tm = env->get_pointer(env, obj_time_info);
  
  st_tm->tm_wday = wday;
  
  return 0;
}

int32_t SPVM__Time__Info__set_yday(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  
  int32_t yday = stack[1].ival;
  
  struct tm* st_tm = env->get_pointer(env, obj_time_info);
  
  st_tm->tm_yday = yday;
  
  return 0;
}

int32_t SPVM__Time__Info__set_isdst(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_time_info = stack[0].oval;
  
  int32_t isdst = stack[1].ival;
  
  struct tm* st_tm = env->get_pointer(env, obj_time_info);
  
  st_tm->tm_isdst = isdst;
  
  return 0;
}
