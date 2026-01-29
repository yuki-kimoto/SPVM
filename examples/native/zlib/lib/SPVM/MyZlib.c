#include "spvm_native.h"
#include<stdio.h>

#include "zlib.h"

static const char* FILE_NAME = "MyZlib.c";

int32_t SPVM__MyZlib__test(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_out_file = stack[0].oval;
  
  if (!obj_out_file){
    return env->die_v2(env, stack, "$ouf_file must be defined.", __func__, FILE_NAME, __LINE__);
  }
  
  const char* out_file = env->get_chars(env, stack, obj_out_file);
  
  char buf[]="0123456789abcdefghijklmnopqrstuvwxyz\n";
  int cnt = 0;
  gzFile zp;
  
  zp = gzopen(out_file, "w9");
  if(zp == NULL){
    return env->die_v2(env, stack, "gzopen failed.", __func__, FILE_NAME, __LINE__);
  }
  
  for(cnt = 0; cnt < 100; cnt++){
    gzputs(zp, buf);
  }
  
  gzclose(zp);
  
  return 0;
}
