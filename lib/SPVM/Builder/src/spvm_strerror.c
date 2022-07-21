// This is for XSI strerror_r
#define _POSIX_C_SOURCE 200112L
#undef _GNU_SOURCE

#include "spvm_native.h"
#include <string.h>

int32_t SPVM_STRERROR_strerror(int errnum, char *buf, size_t buflen) {
  
  int32_t status;
  
#ifdef _WIN32
  status = strerror_s(buf, buflen, errnum);
#else
  status = strerror_r(errnum, buf, buflen);
#endif
  
  return status;
}
