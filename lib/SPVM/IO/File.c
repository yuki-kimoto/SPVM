#include "spvm_native.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int32_t SPNATIVE__SPVM__IO__FILE__O_RDONLY(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef O_RDONLY
  stack[0].ival = O_RDONLY;
#else
  SPVM_DIE("Errno O_RDONLY is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__O_WRONLY(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef O_WRONLY
  stack[0].ival = O_WRONLY;
#else
  SPVM_DIE("Errno O_WRONLY is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__O_RDWR(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef O_RDWR
  stack[0].ival = O_RDWR;
#else
  SPVM_DIE("Errno O_RDWR is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__O_APPEND(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef O_APPEND
  stack[0].ival = O_APPEND;
#else
  SPVM_DIE("Errno O_APPEND is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__O_CREAT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef O_CREAT
  stack[0].ival = O_CREAT;
#else
  SPVM_DIE("Errno O_CREAT is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__O_TRUNC(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef O_TRUNC
  stack[0].ival = O_TRUNC;
#else
  SPVM_DIE("Errno O_TRUNC is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__SEEK_SET(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef SEEK_SET
  stack[0].ival = SEEK_SET;
#else
  SPVM_DIE("Errno SEEK_SET is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__SEEK_CUR(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef SEEK_CUR
  stack[0].ival = SEEK_CUR;
#else
  SPVM_DIE("Errno SEEK_CUR is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__SEEK_END(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef SEEK_END
  stack[0].ival = SEEK_END;
#else
  SPVM_DIE("Errno SEEK_END is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__EOF(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EOF
  stack[0].ival = EOF;
#else
  SPVM_DIE("Errno EOF is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__STDIN(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef STDIN
  stack[0].ival = STDIN;
#else
  SPVM_DIE("Errno STDIN is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__IO__FILE__STDOUT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef STDOUT
  stack[0].ival = STDOUT;
#else
  SPVM_DIE("Errno STDOUT is not defined", "SPVM/IO/File.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}
