use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use Errno;

use Test::More 'no_plan';

use SPVM 'SPVM::Errno';
use SPVM 'TestCase::Lib::SPVM::Errno';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::Float
{
  # errno
  {
    $! = 1;
    my $errno = SPVM::Errno->errno;
    is($errno, 1);
  }
  
  # set_errno
  {
    SPVM::Errno->set_errno(5);
    ok($! == 5);
  }
  
  # errno constants
  {
    if (exists &Errno::E2BIG) { ok(Errno::E2BIG() == SPVM::Errno->E2BIG) };
    if (exists &Errno::EACCES) { ok(Errno::EACCES() == SPVM::Errno->EACCES) };
    if (exists &Errno::EADDRINUSE) { ok(Errno::EADDRINUSE() == SPVM::Errno->EADDRINUSE) };
    if (exists &Errno::EADDRNOTAVAIL) { ok(Errno::EADDRNOTAVAIL() == SPVM::Errno->EADDRNOTAVAIL) };
    if (exists &Errno::EAFNOSUPPORT) { ok(Errno::EAFNOSUPPORT() == SPVM::Errno->EAFNOSUPPORT) };
    if (exists &Errno::EAGAIN) { ok(Errno::EAGAIN() == SPVM::Errno->EAGAIN) };
    if (exists &Errno::EALREADY) { ok(Errno::EALREADY() == SPVM::Errno->EALREADY) };
    if (exists &Errno::EBADF) { ok(Errno::EBADF() == SPVM::Errno->EBADF) };
    if (exists &Errno::EBADMSG) { ok(Errno::EBADMSG() == SPVM::Errno->EBADMSG) };
    if (exists &Errno::EBUSY) { ok(Errno::EBUSY() == SPVM::Errno->EBUSY) };
    if (exists &Errno::ECANCELED) { ok(Errno::ECANCELED() == SPVM::Errno->ECANCELED) };
    if (exists &Errno::ECHILD) { ok(Errno::ECHILD() == SPVM::Errno->ECHILD) };
    if (exists &Errno::ECONNABORTED) { ok(Errno::ECONNABORTED() == SPVM::Errno->ECONNABORTED) };
    if (exists &Errno::ECONNREFUSED) { ok(Errno::ECONNREFUSED() == SPVM::Errno->ECONNREFUSED) };
    if (exists &Errno::ECONNRESET) { ok(Errno::ECONNRESET() == SPVM::Errno->ECONNRESET) };
    if (exists &Errno::EDEADLK) { ok(Errno::EDEADLK() == SPVM::Errno->EDEADLK) };
    if (exists &Errno::EDESTADDRREQ) { ok(Errno::EDESTADDRREQ() == SPVM::Errno->EDESTADDRREQ) };
    if (exists &Errno::EDOM) { ok(Errno::EDOM() == SPVM::Errno->EDOM) };
    if (exists &Errno::EEXIST) { ok(Errno::EEXIST() == SPVM::Errno->EEXIST) };
    if (exists &Errno::EFAULT) { ok(Errno::EFAULT() == SPVM::Errno->EFAULT) };
    if (exists &Errno::EFBIG) { ok(Errno::EFBIG() == SPVM::Errno->EFBIG) };
    if (exists &Errno::EHOSTUNREACH) { ok(Errno::EHOSTUNREACH() == SPVM::Errno->EHOSTUNREACH) };
    if (exists &Errno::EIDRM) { ok(Errno::EIDRM() == SPVM::Errno->EIDRM) };
    if (exists &Errno::EILSEQ) { ok(Errno::EILSEQ() == SPVM::Errno->EILSEQ) };
    if (exists &Errno::EINPROGRESS) { ok(Errno::EINPROGRESS() == SPVM::Errno->EINPROGRESS) };
    if (exists &Errno::EINTR) { ok(Errno::EINTR() == SPVM::Errno->EINTR) };
    if (exists &Errno::EINVAL) { ok(Errno::EINVAL() == SPVM::Errno->EINVAL) };
    if (exists &Errno::EIO) { ok(Errno::EIO() == SPVM::Errno->EIO) };
    if (exists &Errno::EISCONN) { ok(Errno::EISCONN() == SPVM::Errno->EISCONN) };
    if (exists &Errno::EISDIR) { ok(Errno::EISDIR() == SPVM::Errno->EISDIR) };
    if (exists &Errno::ELOOP) { ok(Errno::ELOOP() == SPVM::Errno->ELOOP) };
    if (exists &Errno::EMFILE) { ok(Errno::EMFILE() == SPVM::Errno->EMFILE) };
    if (exists &Errno::EMLINK) { ok(Errno::EMLINK() == SPVM::Errno->EMLINK) };
    if (exists &Errno::EMSGSIZE) { ok(Errno::EMSGSIZE() == SPVM::Errno->EMSGSIZE) };
    if (exists &Errno::ENAMETOOLONG) { ok(Errno::ENAMETOOLONG() == SPVM::Errno->ENAMETOOLONG) };
    if (exists &Errno::ENETDOWN) { ok(Errno::ENETDOWN() == SPVM::Errno->ENETDOWN) };
    if (exists &Errno::ENETRESET) { ok(Errno::ENETRESET() == SPVM::Errno->ENETRESET) };
    if (exists &Errno::ENETUNREACH) { ok(Errno::ENETUNREACH() == SPVM::Errno->ENETUNREACH) };
    if (exists &Errno::ENFILE) { ok(Errno::ENFILE() == SPVM::Errno->ENFILE) };
    if (exists &Errno::ENOBUFS) { ok(Errno::ENOBUFS() == SPVM::Errno->ENOBUFS) };
    if (exists &Errno::ENODATA) { ok(Errno::ENODATA() == SPVM::Errno->ENODATA) };
    if (exists &Errno::ENODEV) { ok(Errno::ENODEV() == SPVM::Errno->ENODEV) };
    if (exists &Errno::ENOENT) { ok(Errno::ENOENT() == SPVM::Errno->ENOENT) };
    if (exists &Errno::ENOEXEC) { ok(Errno::ENOEXEC() == SPVM::Errno->ENOEXEC) };
    if (exists &Errno::ENOLCK) { ok(Errno::ENOLCK() == SPVM::Errno->ENOLCK) };
    if (exists &Errno::ENOLINK) { ok(Errno::ENOLINK() == SPVM::Errno->ENOLINK) };
    if (exists &Errno::ENOMEM) { ok(Errno::ENOMEM() == SPVM::Errno->ENOMEM) };
    if (exists &Errno::ENOMSG) { ok(Errno::ENOMSG() == SPVM::Errno->ENOMSG) };
    if (exists &Errno::ENOPROTOOPT) { ok(Errno::ENOPROTOOPT() == SPVM::Errno->ENOPROTOOPT) };
    if (exists &Errno::ENOSPC) { ok(Errno::ENOSPC() == SPVM::Errno->ENOSPC) };
    if (exists &Errno::ENOSR) { ok(Errno::ENOSR() == SPVM::Errno->ENOSR) };
    if (exists &Errno::ENOSTR) { ok(Errno::ENOSTR() == SPVM::Errno->ENOSTR) };
    if (exists &Errno::ENOSYS) { ok(Errno::ENOSYS() == SPVM::Errno->ENOSYS) };
    if (exists &Errno::ENOTCONN) { ok(Errno::ENOTCONN() == SPVM::Errno->ENOTCONN) };
    if (exists &Errno::ENOTDIR) { ok(Errno::ENOTDIR() == SPVM::Errno->ENOTDIR) };
    if (exists &Errno::ENOTEMPTY) { ok(Errno::ENOTEMPTY() == SPVM::Errno->ENOTEMPTY) };
    if (exists &Errno::ENOTRECOVERABLE) { ok(Errno::ENOTRECOVERABLE() == SPVM::Errno->ENOTRECOVERABLE) };
    if (exists &Errno::ENOTSOCK) { ok(Errno::ENOTSOCK() == SPVM::Errno->ENOTSOCK) };
    if (exists &Errno::ENOTSUP) { ok(Errno::ENOTSUP() == SPVM::Errno->ENOTSUP) };
    if (exists &Errno::ENOTTY) { ok(Errno::ENOTTY() == SPVM::Errno->ENOTTY) };
    if (exists &Errno::ENXIO) { ok(Errno::ENXIO() == SPVM::Errno->ENXIO) };
    if (exists &Errno::EOPNOTSUPP) { ok(Errno::EOPNOTSUPP() == SPVM::Errno->EOPNOTSUPP) };
    if (exists &Errno::EOVERFLOW) { ok(Errno::EOVERFLOW() == SPVM::Errno->EOVERFLOW) };
    if (exists &Errno::EOWNERDEAD) { ok(Errno::EOWNERDEAD() == SPVM::Errno->EOWNERDEAD) };
    if (exists &Errno::EPERM) { ok(Errno::EPERM() == SPVM::Errno->EPERM) };
    if (exists &Errno::EPIPE) { ok(Errno::EPIPE() == SPVM::Errno->EPIPE) };
    if (exists &Errno::EPROTO) { ok(Errno::EPROTO() == SPVM::Errno->EPROTO) };
    if (exists &Errno::EPROTONOSUPPORT) { ok(Errno::EPROTONOSUPPORT() == SPVM::Errno->EPROTONOSUPPORT) };
    if (exists &Errno::EPROTOTYPE) { ok(Errno::EPROTOTYPE() == SPVM::Errno->EPROTOTYPE) };
    if (exists &Errno::ERANGE) { ok(Errno::ERANGE() == SPVM::Errno->ERANGE) };
    if (exists &Errno::EROFS) { ok(Errno::EROFS() == SPVM::Errno->EROFS) };
    if (exists &Errno::ESPIPE) { ok(Errno::ESPIPE() == SPVM::Errno->ESPIPE) };
    if (exists &Errno::ESRCH) { ok(Errno::ESRCH() == SPVM::Errno->ESRCH) };
    if (exists &Errno::ETIME) { ok(Errno::ETIME() == SPVM::Errno->ETIME) };
    if (exists &Errno::ETIMEDOUT) { ok(Errno::ETIMEDOUT() == SPVM::Errno->ETIMEDOUT) };
    if (exists &Errno::ETXTBSY) { ok(Errno::ETXTBSY() == SPVM::Errno->ETXTBSY) };
    if (exists &Errno::EWOULDBLOCK) { ok(Errno::EWOULDBLOCK() == SPVM::Errno->EWOULDBLOCK) };
    if (exists &Errno::EXDEV) { ok(Errno::EXDEV() == SPVM::Errno->EXDEV) };
    if (exists &Errno::EOTHER) { ok(Errno::EOTHER() == SPVM::Errno->EOTHER) };
  }
}

# strerror
{
  ok(TestCase::Lib::SPVM::Errno->test_strerror);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

