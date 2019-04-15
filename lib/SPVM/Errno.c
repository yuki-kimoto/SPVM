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

int32_t SPNATIVE__SPVM__Errno__init_native_constants(SPVM_ENV* env, SPVM_VALUE* stack) {

  // E2BIG
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$E2BIG", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, E2BIG);
  }

  // EACCES
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EACCES", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EACCES);
  }

  // EADDRINUSE
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EADDRINUSE", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EADDRINUSE);
  }

  // EADDRNOTAVAIL
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EADDRNOTAVAIL", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EADDRNOTAVAIL);
  }

  // EAFNOSUPPORT
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EAFNOSUPPORT", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EAFNOSUPPORT);
  }

  // EAGAIN
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EAGAIN", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EAGAIN);
  }

  // EALREADY
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EALREADY", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EALREADY);
  }

  // EBADF
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EBADF", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EBADF);
  }

  // EBADMSG
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EBADMSG", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EBADMSG);
  }

  // EBUSY
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EBUSY", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EBUSY);
  }

  // ECANCELED
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ECANCELED", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ECANCELED);
  }

  // ECHILD
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ECHILD", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ECHILD);
  }

  // ECONNABORTED
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ECONNABORTED", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ECONNABORTED);
  }

  // ECONNREFUSED
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ECONNREFUSED", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ECONNREFUSED);
  }

  // ECONNRESET
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ECONNRESET", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ECONNRESET);
  }

  // EDEADLK
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EDEADLK", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EDEADLK);
  }

  // EDESTADDRREQ
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EDESTADDRREQ", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EDESTADDRREQ);
  }

  // EDOM
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EDOM", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EDOM);
  }

  // EEXIST
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EEXIST", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EEXIST);
  }

  // EFAULT
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EFAULT", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EFAULT);
  }

  // EFBIG
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EFBIG", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EFBIG);
  }

  // EHOSTUNREACH
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EHOSTUNREACH", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EHOSTUNREACH);
  }

  // EIDRM
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EIDRM", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EIDRM);
  }

  // EILSEQ
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EILSEQ", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EILSEQ);
  }

  // EINPROGRESS
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EINPROGRESS", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EINPROGRESS);
  }

  // EINTR
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EINTR", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EINTR);
  }

  // EINVAL
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EINVAL", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EINVAL);
  }

  // EIO
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EIO", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EIO);
  }

  // EISCONN
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EISCONN", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EISCONN);
  }

  // EISDIR
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EISDIR", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EISDIR);
  }

  // ELOOP
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ELOOP", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ELOOP);
  }

  // EMFILE
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EMFILE", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EMFILE);
  }

  // EMLINK
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EMLINK", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EMLINK);
  }

  // EMSGSIZE
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EMSGSIZE", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EMSGSIZE);
  }

  // ENAMETOOLONG
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENAMETOOLONG", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENAMETOOLONG);
  }

  // ENETDOWN
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENETDOWN", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENETDOWN);
  }

  // ENETRESET
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENETRESET", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENETRESET);
  }

  // ENETUNREACH
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENETUNREACH", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENETUNREACH);
  }

  // ENFILE
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENFILE", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENFILE);
  }

  // ENOBUFS
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENOBUFS", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENOBUFS);
  }

  // ENODATA
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENODATA", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENODATA);
  }

  // ENODEV
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENODEV", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENODEV);
  }

  // ENOENT
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENOENT", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENOENT);
  }

  // ENOEXEC
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENOEXEC", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENOEXEC);
  }

  // ENOLCK
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENOLCK", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENOLCK);
  }

  // ENOLINK
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENOLINK", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENOLINK);
  }

  // ENOMEM
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENOMEM", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENOMEM);
  }

  // ENOMSG
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENOMSG", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENOMSG);
  }

  // ENOPROTOOPT
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENOPROTOOPT", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENOPROTOOPT);
  }

  // ENOSPC
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENOSPC", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENOSPC);
  }

  // ENOSR
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENOSR", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENOSR);
  }

  // ENOSTR
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENOSTR", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENOSTR);
  }

  // ENOSYS
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENOSYS", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENOSYS);
  }

  // ENOTCONN
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENOTCONN", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENOTCONN);
  }

  // ENOTDIR
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENOTDIR", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENOTDIR);
  }

  // ENOTEMPTY
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENOTEMPTY", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENOTEMPTY);
  }

  // ENOTRECOVERABLE
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENOTRECOVERABLE", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENOTRECOVERABLE);
  }

  // ENOTSOCK
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENOTSOCK", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENOTSOCK);
  }

  // ENOTSUP
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENOTSUP", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENOTSUP);
  }

  // ENOTTY
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENOTTY", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENOTTY);
  }

  // ENXIO
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ENXIO", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ENXIO);
  }

  // EOPNOTSUPP
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EOPNOTSUPP", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EOPNOTSUPP);
  }

  // EOVERFLOW
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EOVERFLOW", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EOVERFLOW);
  }

  // EOWNERDEAD
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EOWNERDEAD", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EOWNERDEAD);
  }

  // EPERM
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EPERM", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EPERM);
  }

  // EPIPE
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EPIPE", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EPIPE);
  }

  // EPROTO
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EPROTO", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EPROTO);
  }

  // EPROTONOSUPPORT
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EPROTONOSUPPORT", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EPROTONOSUPPORT);
  }

  // EPROTOTYPE
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EPROTOTYPE", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EPROTOTYPE);
  }

  // ERANGE
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ERANGE", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ERANGE);
  }

  // EROFS
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EROFS", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EROFS);
  }

  // ESPIPE
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ESPIPE", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ESPIPE);
  }

  // ESRCH
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ESRCH", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ESRCH);
  }

  // ETIME
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ETIME", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ETIME);
  }

  // ETIMEDOUT
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ETIMEDOUT", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ETIMEDOUT);
  }

  // ETXTBSY
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$ETXTBSY", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, ETXTBSY);
  }

  // EWOULDBLOCK
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EWOULDBLOCK", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EWOULDBLOCK);
  }

  // EXDEV
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Errno", "$EXDEV", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, EXDEV);
  }
}
