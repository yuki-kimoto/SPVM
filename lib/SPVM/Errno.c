#ifndef _XOPEN_SOURCE
#  define _XOPEN_SOURCE 600
#endif

#include "spvm_native.h"

#include <errno.h>
#include <stdlib.h>

int32_t SPNATIVE__SPVM__Errno__errno(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  stack[0].ival = errno;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__set_errno(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  errno = stack[0].ival;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__strerror(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t error_number = stack[0].ival;

  char strerr[256] = {0};
// Don't check the return value of strerror_s and strerror_r for portability
#ifdef _WIN32
    strerror_s(strerr, 256, error_number);
#else
    strerror_r(error_number, strerr, 256);
#endif
  strerr[255] = '\0';
  
  // If the first character is '\0', that means can't get an error string.
  if (strerr[0] == '\0') {
    SPVM_DIE("strerror can't get a valid message", "SPVM/Errno.c", __LINE__);
  }
  
  void* obj_strerr = env->new_str(env, strerr);
  
  stack[0].oval = obj_strerr;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__E2BIG(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef E2BIG
  stack[0].ival = E2BIG;
#else
  SPVM_DIE("Errno E2BIG is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EACCES(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EACCES
  stack[0].ival = EACCES;
#else
  SPVM_DIE("Errno EACCES is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EADDRINUSE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EADDRINUSE
  stack[0].ival = EADDRINUSE;
#else
  SPVM_DIE("Errno EADDRINUSE is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EADDRNOTAVAIL(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EADDRNOTAVAIL
  stack[0].ival = EADDRNOTAVAIL;
#else
  SPVM_DIE("Errno EADDRNOTAVAIL is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EAFNOSUPPORT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EAFNOSUPPORT
  stack[0].ival = EAFNOSUPPORT;
#else
  SPVM_DIE("Errno EAFNOSUPPORT is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EAGAIN(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EAGAIN
  stack[0].ival = EAGAIN;
#else
  SPVM_DIE("Errno EAGAIN is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EALREADY(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EALREADY
  stack[0].ival = EALREADY;
#else
  SPVM_DIE("Errno EALREADY is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EBADF(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EBADF
  stack[0].ival = EBADF;
#else
  SPVM_DIE("Errno EBADF is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EBADMSG(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EBADMSG
  stack[0].ival = EBADMSG;
#else
  SPVM_DIE("Errno EBADMSG is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EBUSY(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EBUSY
  stack[0].ival = EBUSY;
#else
  SPVM_DIE("Errno EBUSY is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ECANCELED(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ECANCELED
  stack[0].ival = ECANCELED;
#else
  SPVM_DIE("Errno ECANCELED is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ECHILD(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ECHILD
  stack[0].ival = ECHILD;
#else
  SPVM_DIE("Errno ECHILD is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ECONNABORTED(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ECONNABORTED
  stack[0].ival = ECONNABORTED;
#else
  SPVM_DIE("Errno ECONNABORTED is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ECONNREFUSED(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ECONNREFUSED
  stack[0].ival = ECONNREFUSED;
#else
  SPVM_DIE("Errno ECONNREFUSED is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ECONNRESET(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ECONNRESET
  stack[0].ival = ECONNRESET;
#else
  SPVM_DIE("Errno ECONNRESET is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EDEADLK(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EDEADLK
  stack[0].ival = EDEADLK;
#else
  SPVM_DIE("Errno EDEADLK is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EDESTADDRREQ(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EDESTADDRREQ
  stack[0].ival = EDESTADDRREQ;
#else
  SPVM_DIE("Errno EDESTADDRREQ is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EDOM(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EDOM
  stack[0].ival = EDOM;
#else
  SPVM_DIE("Errno EDOM is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EEXIST(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EEXIST
  stack[0].ival = EEXIST;
#else
  SPVM_DIE("Errno EEXIST is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EFAULT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EFAULT
  stack[0].ival = EFAULT;
#else
  SPVM_DIE("Errno EFAULT is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EFBIG(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EFBIG
  stack[0].ival = EFBIG;
#else
  SPVM_DIE("Errno EFBIG is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EHOSTUNREACH(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EHOSTUNREACH
  stack[0].ival = EHOSTUNREACH;
#else
  SPVM_DIE("Errno EHOSTUNREACH is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EIDRM(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EIDRM
  stack[0].ival = EIDRM;
#else
  SPVM_DIE("Errno EIDRM is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EILSEQ(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EILSEQ
  stack[0].ival = EILSEQ;
#else
  SPVM_DIE("Errno EILSEQ is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EINPROGRESS(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EINPROGRESS
  stack[0].ival = EINPROGRESS;
#else
  SPVM_DIE("Errno EINPROGRESS is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EINTR(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EINTR
  stack[0].ival = EINTR;
#else
  SPVM_DIE("Errno EINTR is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EINVAL(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EINVAL
  stack[0].ival = EINVAL;
#else
  SPVM_DIE("Errno EINVAL is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EIO(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EIO
  stack[0].ival = EIO;
#else
  SPVM_DIE("Errno EIO is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EISCONN(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EISCONN
  stack[0].ival = EISCONN;
#else
  SPVM_DIE("Errno EISCONN is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EISDIR(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EISDIR
  stack[0].ival = EISDIR;
#else
  SPVM_DIE("Errno EISDIR is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ELOOP(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ELOOP
  stack[0].ival = ELOOP;
#else
  SPVM_DIE("Errno ELOOP is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EMFILE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EMFILE
  stack[0].ival = EMFILE;
#else
  SPVM_DIE("Errno EMFILE is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EMLINK(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EMLINK
  stack[0].ival = EMLINK;
#else
  SPVM_DIE("Errno EMLINK is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EMSGSIZE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EMSGSIZE
  stack[0].ival = EMSGSIZE;
#else
  SPVM_DIE("Errno EMSGSIZE is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENAMETOOLONG(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENAMETOOLONG
  stack[0].ival = ENAMETOOLONG;
#else
  SPVM_DIE("Errno ENAMETOOLONG is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENETDOWN(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENETDOWN
  stack[0].ival = ENETDOWN;
#else
  SPVM_DIE("Errno ENETDOWN is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENETRESET(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENETRESET
  stack[0].ival = ENETRESET;
#else
  SPVM_DIE("Errno ENETRESET is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENETUNREACH(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENETUNREACH
  stack[0].ival = ENETUNREACH;
#else
  SPVM_DIE("Errno ENETUNREACH is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENFILE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENFILE
  stack[0].ival = ENFILE;
#else
  SPVM_DIE("Errno ENFILE is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENOBUFS(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENOBUFS
  stack[0].ival = ENOBUFS;
#else
  SPVM_DIE("Errno ENOBUFS is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENODATA(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENODATA
  stack[0].ival = ENODATA;
#else
  SPVM_DIE("Errno ENODATA is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENODEV(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENODEV
  stack[0].ival = ENODEV;
#else
  SPVM_DIE("Errno ENODEV is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENOENT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENOENT
  stack[0].ival = ENOENT;
#else
  SPVM_DIE("Errno ENOENT is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENOEXEC(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENOEXEC
  stack[0].ival = ENOEXEC;
#else
  SPVM_DIE("Errno ENOEXEC is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENOLCK(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENOLCK
  stack[0].ival = ENOLCK;
#else
  SPVM_DIE("Errno ENOLCK is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENOLINK(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENOLINK
  stack[0].ival = ENOLINK;
#else
  SPVM_DIE("Errno ENOLINK is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENOMEM(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENOMEM
  stack[0].ival = ENOMEM;
#else
  SPVM_DIE("Errno ENOMEM is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENOMSG(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENOMSG
  stack[0].ival = ENOMSG;
#else
  SPVM_DIE("Errno ENOMSG is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENOPROTOOPT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENOPROTOOPT
  stack[0].ival = ENOPROTOOPT;
#else
  SPVM_DIE("Errno ENOPROTOOPT is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENOSPC(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENOSPC
  stack[0].ival = ENOSPC;
#else
  SPVM_DIE("Errno ENOSPC is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENOSR(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENOSR
  stack[0].ival = ENOSR;
#else
  SPVM_DIE("Errno ENOSR is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENOSTR(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENOSTR
  stack[0].ival = ENOSTR;
#else
  SPVM_DIE("Errno ENOSTR is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENOSYS(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENOSYS
  stack[0].ival = ENOSYS;
#else
  SPVM_DIE("Errno ENOSYS is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENOTCONN(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENOTCONN
  stack[0].ival = ENOTCONN;
#else
  SPVM_DIE("Errno ENOTCONN is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENOTDIR(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENOTDIR
  stack[0].ival = ENOTDIR;
#else
  SPVM_DIE("Errno ENOTDIR is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENOTEMPTY(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENOTEMPTY
  stack[0].ival = ENOTEMPTY;
#else
  SPVM_DIE("Errno ENOTEMPTY is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENOTRECOVERABLE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENOTRECOVERABLE
  stack[0].ival = ENOTRECOVERABLE;
#else
  SPVM_DIE("Errno ENOTRECOVERABLE is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENOTSOCK(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENOTSOCK
  stack[0].ival = ENOTSOCK;
#else
  SPVM_DIE("Errno ENOTSOCK is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENOTSUP(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENOTSUP
  stack[0].ival = ENOTSUP;
#else
  SPVM_DIE("Errno ENOTSUP is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENOTTY(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENOTTY
  stack[0].ival = ENOTTY;
#else
  SPVM_DIE("Errno ENOTTY is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ENXIO(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ENXIO
  stack[0].ival = ENXIO;
#else
  SPVM_DIE("Errno ENXIO is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EOPNOTSUPP(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EOPNOTSUPP
  stack[0].ival = EOPNOTSUPP;
#else
  SPVM_DIE("Errno EOPNOTSUPP is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EOTHER(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EOTHER
  stack[0].ival = EOTHER;
#else
  SPVM_DIE("Errno EOTHER is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EOVERFLOW(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EOVERFLOW
  stack[0].ival = EOVERFLOW;
#else
  SPVM_DIE("Errno EOVERFLOW is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EOWNERDEAD(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EOWNERDEAD
  stack[0].ival = EOWNERDEAD;
#else
  SPVM_DIE("Errno EOWNERDEAD is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EPERM(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EPERM
  stack[0].ival = EPERM;
#else
  SPVM_DIE("Errno EPERM is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EPIPE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EPIPE
  stack[0].ival = EPIPE;
#else
  SPVM_DIE("Errno EPIPE is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EPROTO(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EPROTO
  stack[0].ival = EPROTO;
#else
  SPVM_DIE("Errno EPROTO is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EPROTONOSUPPORT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EPROTONOSUPPORT
  stack[0].ival = EPROTONOSUPPORT;
#else
  SPVM_DIE("Errno EPROTONOSUPPORT is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EPROTOTYPE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EPROTOTYPE
  stack[0].ival = EPROTOTYPE;
#else
  SPVM_DIE("Errno EPROTOTYPE is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ERANGE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ERANGE
  stack[0].ival = ERANGE;
#else
  SPVM_DIE("Errno ERANGE is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EROFS(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EROFS
  stack[0].ival = EROFS;
#else
  SPVM_DIE("Errno EROFS is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ESPIPE(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ESPIPE
  stack[0].ival = ESPIPE;
#else
  SPVM_DIE("Errno ESPIPE is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ESRCH(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ESRCH
  stack[0].ival = ESRCH;
#else
  SPVM_DIE("Errno ESRCH is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ETIME(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ETIME
  stack[0].ival = ETIME;
#else
  SPVM_DIE("Errno ETIME is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ETIMEDOUT(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ETIMEDOUT
  stack[0].ival = ETIMEDOUT;
#else
  SPVM_DIE("Errno ETIMEDOUT is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__ETXTBSY(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef ETXTBSY
  stack[0].ival = ETXTBSY;
#else
  SPVM_DIE("Errno ETXTBSY is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EWOULDBLOCK(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EWOULDBLOCK
  stack[0].ival = EWOULDBLOCK;
#else
  SPVM_DIE("Errno EWOULDBLOCK is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Errno__EXDEV(SPVM_ENV* env, SPVM_VALUE* stack) {
#ifdef EXDEV
  stack[0].ival = EXDEV;
#else
  SPVM_DIE("Errno EXDEV is not defined", "SPVM/Errno.c", __LINE__);
#endif

  return SPVM_SUCCESS;
}
