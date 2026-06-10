// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>

#include "spvm_native.h"

#include "spvm_api_cfunc.h"
#include "spvm_api.h"

SPVM_API_CFUNC* SPVM_API_CFUNC_new_api() {
  
  void* env_cfunc_init[]  = {
    SPVM_API_c_strlen,
    SPVM_API_c_memcpy,
    SPVM_API_c_memset,
    SPVM_API_c_memcmp,
    SPVM_API_c_strtoll,
    SPVM_API_c_strtof,
    SPVM_API_c_strtod,
    SPVM_API_c_fputs,
    SPVM_API_c_fgetc,
    SPVM_API_c_snprintf_len,
    SPVM_API_c_errno,
    SPVM_API_c_set_errno,
    SPVM_API_c_fopen,
    SPVM_API_c_freopen,
    SPVM_API_c_fclose,
    SPVM_API_c_fread,
    SPVM_API_c_fwrite,
    SPVM_API_c_fflush,
    SPVM_API_c_fseek,
    SPVM_API_c_ftell,
    SPVM_API_c_feof,
    SPVM_API_c_ferror,
    SPVM_API_c_fileno,
    SPVM_API_c_stdin,
    SPVM_API_c_stdout,
    SPVM_API_c_stderr,
    SPVM_API_c_getenv,
    SPVM_API_c_setenv,
    SPVM_API_c_unsetenv,
    SPVM_API_c__dupenv_s,
    SPVM_API_c__putenv_s,
    SPVM_API_c_localtime,
    SPVM_API_c_tzset,
    SPVM_API_c_malloc,
    SPVM_API_c_calloc,
    SPVM_API_c_realloc,
    SPVM_API_c_free,
    SPVM_API_c_localtime_r,
    SPVM_API_c_localtime_s,
    SPVM_API_c_gmtime_r,
    SPVM_API_c_gmtime_s,
  };
  SPVM_API_CFUNC* env_cfunc = calloc(1, sizeof(env_cfunc_init));
  memcpy(env_cfunc, env_cfunc_init, sizeof(env_cfunc_init));
  
  return env_cfunc;
}

void SPVM_API_CFUNC_free_api(SPVM_API_CFUNC* api) {
  free(api);
}

