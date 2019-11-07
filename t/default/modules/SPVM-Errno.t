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
    if (defined &Errno::E2BIG) { ok(Errno::E2BIG() == SPVM::Errno->E2BIG) };
    if (defined &Errno::EACCES) { ok(Errno::EACCES() == SPVM::Errno->EACCES) };
    if (defined &Errno::EADDRINUSE) { ok(Errno::EADDRINUSE() == SPVM::Errno->EADDRINUSE) };
    if (defined &Errno::EADDRNOTAVAIL) { ok(Errno::EADDRNOTAVAIL() == SPVM::Errno->EADDRNOTAVAIL) };
    if (defined &Errno::EAFNOSUPPORT) { ok(Errno::EAFNOSUPPORT() == SPVM::Errno->EAFNOSUPPORT) };
    if (defined &Errno::EAGAIN) { ok(Errno::EAGAIN() == SPVM::Errno->EAGAIN) };
    if (defined &Errno::EALREADY) { ok(Errno::EALREADY() == SPVM::Errno->EALREADY) };
    if (defined &Errno::EBADF) { ok(Errno::EBADF() == SPVM::Errno->EBADF) };
    if (defined &Errno::EBADMSG) { ok(Errno::EBADMSG() == SPVM::Errno->EBADMSG) };
    if (defined &Errno::EBUSY) { ok(Errno::EBUSY() == SPVM::Errno->EBUSY) };
    if (defined &Errno::ECANCELED) { ok(Errno::ECANCELED() == SPVM::Errno->ECANCELED) };
    if (defined &Errno::ECHILD) { ok(Errno::ECHILD() == SPVM::Errno->ECHILD) };
    if (defined &Errno::ECONNABORTED) { ok(Errno::ECONNABORTED() == SPVM::Errno->ECONNABORTED) };
    if (defined &Errno::ECONNREFUSED) { ok(Errno::ECONNREFUSED() == SPVM::Errno->ECONNREFUSED) };
    if (defined &Errno::ECONNRESET) { ok(Errno::ECONNRESET() == SPVM::Errno->ECONNRESET) };
    if (defined &Errno::EDEADLK) { ok(Errno::EDEADLK() == SPVM::Errno->EDEADLK) };
    if (defined &Errno::EDESTADDRREQ) { ok(Errno::EDESTADDRREQ() == SPVM::Errno->EDESTADDRREQ) };
    if (defined &Errno::EDOM) { ok(Errno::EDOM() == SPVM::Errno->EDOM) };
    if (defined &Errno::EEXIST) { ok(Errno::EEXIST() == SPVM::Errno->EEXIST) };
    if (defined &Errno::EFAULT) { ok(Errno::EFAULT() == SPVM::Errno->EFAULT) };
    if (defined &Errno::EFBIG) { ok(Errno::EFBIG() == SPVM::Errno->EFBIG) };
    if (defined &Errno::EHOSTUNREACH) { ok(Errno::EHOSTUNREACH() == SPVM::Errno->EHOSTUNREACH) };
    if (defined &Errno::EIDRM) { ok(Errno::EIDRM() == SPVM::Errno->EIDRM) };
    if (defined &Errno::EILSEQ) { ok(Errno::EILSEQ() == SPVM::Errno->EILSEQ) };
    if (defined &Errno::EINPROGRESS) { ok(Errno::EINPROGRESS() == SPVM::Errno->EINPROGRESS) };
    if (defined &Errno::EINTR) { ok(Errno::EINTR() == SPVM::Errno->EINTR) };
    if (defined &Errno::EINVAL) { ok(Errno::EINVAL() == SPVM::Errno->EINVAL) };
    if (defined &Errno::EIO) { ok(Errno::EIO() == SPVM::Errno->EIO) };
    if (defined &Errno::EISCONN) { ok(Errno::EISCONN() == SPVM::Errno->EISCONN) };
    if (defined &Errno::EISDIR) { ok(Errno::EISDIR() == SPVM::Errno->EISDIR) };
    if (defined &Errno::ELOOP) { ok(Errno::ELOOP() == SPVM::Errno->ELOOP) };
    if (defined &Errno::EMFILE) { ok(Errno::EMFILE() == SPVM::Errno->EMFILE) };
    if (defined &Errno::EMLINK) { ok(Errno::EMLINK() == SPVM::Errno->EMLINK) };
    if (defined &Errno::EMSGSIZE) { ok(Errno::EMSGSIZE() == SPVM::Errno->EMSGSIZE) };
    if (defined &Errno::ENAMETOOLONG) { ok(Errno::ENAMETOOLONG() == SPVM::Errno->ENAMETOOLONG) };
    if (defined &Errno::ENETDOWN) { ok(Errno::ENETDOWN() == SPVM::Errno->ENETDOWN) };
    if (defined &Errno::ENETRESET) { ok(Errno::ENETRESET() == SPVM::Errno->ENETRESET) };
    if (defined &Errno::ENETUNREACH) { ok(Errno::ENETUNREACH() == SPVM::Errno->ENETUNREACH) };
    if (defined &Errno::ENFILE) { ok(Errno::ENFILE() == SPVM::Errno->ENFILE) };
    if (defined &Errno::ENOBUFS) { ok(Errno::ENOBUFS() == SPVM::Errno->ENOBUFS) };
    if (defined &Errno::ENODATA) { ok(Errno::ENODATA() == SPVM::Errno->ENODATA) };
    if (defined &Errno::ENODEV) { ok(Errno::ENODEV() == SPVM::Errno->ENODEV) };
    if (defined &Errno::ENOENT) { ok(Errno::ENOENT() == SPVM::Errno->ENOENT) };
    if (defined &Errno::ENOEXEC) { ok(Errno::ENOEXEC() == SPVM::Errno->ENOEXEC) };
    if (defined &Errno::ENOLCK) { ok(Errno::ENOLCK() == SPVM::Errno->ENOLCK) };
    if (defined &Errno::ENOLINK) { ok(Errno::ENOLINK() == SPVM::Errno->ENOLINK) };
    if (defined &Errno::ENOMEM) { ok(Errno::ENOMEM() == SPVM::Errno->ENOMEM) };
    if (defined &Errno::ENOMSG) { ok(Errno::ENOMSG() == SPVM::Errno->ENOMSG) };
    if (defined &Errno::ENOPROTOOPT) { ok(Errno::ENOPROTOOPT() == SPVM::Errno->ENOPROTOOPT) };
    if (defined &Errno::ENOSPC) { ok(Errno::ENOSPC() == SPVM::Errno->ENOSPC) };
    if (defined &Errno::ENOSR) { ok(Errno::ENOSR() == SPVM::Errno->ENOSR) };
    if (defined &Errno::ENOSTR) { ok(Errno::ENOSTR() == SPVM::Errno->ENOSTR) };
    if (defined &Errno::ENOSYS) { ok(Errno::ENOSYS() == SPVM::Errno->ENOSYS) };
    if (defined &Errno::ENOTCONN) { ok(Errno::ENOTCONN() == SPVM::Errno->ENOTCONN) };
    if (defined &Errno::ENOTDIR) { ok(Errno::ENOTDIR() == SPVM::Errno->ENOTDIR) };
    if (defined &Errno::ENOTEMPTY) { ok(Errno::ENOTEMPTY() == SPVM::Errno->ENOTEMPTY) };
    if (defined &Errno::ENOTRECOVERABLE) { ok(Errno::ENOTRECOVERABLE() == SPVM::Errno->ENOTRECOVERABLE) };
    if (defined &Errno::ENOTSOCK) { ok(Errno::ENOTSOCK() == SPVM::Errno->ENOTSOCK) };
    if (defined &Errno::ENOTSUP) { ok(Errno::ENOTSUP() == SPVM::Errno->ENOTSUP) };
    if (defined &Errno::ENOTTY) { ok(Errno::ENOTTY() == SPVM::Errno->ENOTTY) };
    if (defined &Errno::ENXIO) { ok(Errno::ENXIO() == SPVM::Errno->ENXIO) };
    if (defined &Errno::EOPNOTSUPP) { ok(Errno::EOPNOTSUPP() == SPVM::Errno->EOPNOTSUPP) };
    if (defined &Errno::EOVERFLOW) { ok(Errno::EOVERFLOW() == SPVM::Errno->EOVERFLOW) };
    if (defined &Errno::EOWNERDEAD) { ok(Errno::EOWNERDEAD() == SPVM::Errno->EOWNERDEAD) };
    if (defined &Errno::EPERM) { ok(Errno::EPERM() == SPVM::Errno->EPERM) };
    if (defined &Errno::EPIPE) { ok(Errno::EPIPE() == SPVM::Errno->EPIPE) };
    if (defined &Errno::EPROTO) { ok(Errno::EPROTO() == SPVM::Errno->EPROTO) };
    if (defined &Errno::EPROTONOSUPPORT) { ok(Errno::EPROTONOSUPPORT() == SPVM::Errno->EPROTONOSUPPORT) };
    if (defined &Errno::EPROTOTYPE) { ok(Errno::EPROTOTYPE() == SPVM::Errno->EPROTOTYPE) };
    if (defined &Errno::ERANGE) { ok(Errno::ERANGE() == SPVM::Errno->ERANGE) };
    if (defined &Errno::EROFS) { ok(Errno::EROFS() == SPVM::Errno->EROFS) };
    if (defined &Errno::ESPIPE) { ok(Errno::ESPIPE() == SPVM::Errno->ESPIPE) };
    if (defined &Errno::ESRCH) { ok(Errno::ESRCH() == SPVM::Errno->ESRCH) };
    if (defined &Errno::ETIME) { ok(Errno::ETIME() == SPVM::Errno->ETIME) };
    if (defined &Errno::ETIMEDOUT) { ok(Errno::ETIMEDOUT() == SPVM::Errno->ETIMEDOUT) };
    if (defined &Errno::ETXTBSY) { ok(Errno::ETXTBSY() == SPVM::Errno->ETXTBSY) };
    if (defined &Errno::EWOULDBLOCK) { ok(Errno::EWOULDBLOCK() == SPVM::Errno->EWOULDBLOCK) };
    if (defined &Errno::EXDEV) { ok(Errno::EXDEV() == SPVM::Errno->EXDEV) };
    if (defined &Errno::EOTHER) { ok(Errno::EOTHER() == SPVM::Errno->EOTHER) };
  }
}

# strerror
{
  ok(TestCase::Lib::SPVM::Errno->test_strerror);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

