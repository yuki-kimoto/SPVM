#include "spvm_native.h"

#include <time.h>

int32_t SPNATIVE__SPVM__Time__time(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int64_t timer_value = (int64_t)time(NULL);
  
  stack[0].lval = timer_value;
  
  return SPVM_SUCCESS;
}

/*
int32_t SPNATIVE__SPVM__Time__localtime(SPVM_ENV* env, SPVM_VALUE* stack) {

  time_t time;
  struct tm resultp;

#ifdef __CYGWIN__ || __MINGW32__
  localtime_s(&time, &resultp);
#else
  localtime_r(&time, &resultp);
#endif

  return SPVM_SUCCESS;
}
*/