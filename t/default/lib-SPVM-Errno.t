use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use Errno;

use Test::More 'no_plan';

use SPVM 'SPVM::Errno';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

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
    ok(Errno::E2BIG == SPVM::Errno->E2BIG);
    ok(Errno::EACCES == SPVM::Errno->EACCES);
    ok(Errno::EADDRINUSE == SPVM::Errno->EADDRINUSE);
    ok(Errno::EADDRNOTAVAIL == SPVM::Errno->EADDRNOTAVAIL);
    ok(Errno::EAFNOSUPPORT == SPVM::Errno->EAFNOSUPPORT);
    ok(Errno::EAGAIN == SPVM::Errno->EAGAIN);
    ok(Errno::EALREADY == SPVM::Errno->EALREADY);
    ok(Errno::EBADF == SPVM::Errno->EBADF);
    ok(Errno::EBADMSG == SPVM::Errno->EBADMSG);
    ok(Errno::EBUSY == SPVM::Errno->EBUSY);
    ok(Errno::ECANCELED == SPVM::Errno->ECANCELED);
    ok(Errno::ECHILD == SPVM::Errno->ECHILD);
    ok(Errno::ECONNABORTED == SPVM::Errno->ECONNABORTED);
    ok(Errno::ECONNREFUSED == SPVM::Errno->ECONNREFUSED);
    ok(Errno::ECONNRESET == SPVM::Errno->ECONNRESET);
    ok(Errno::EDEADLK == SPVM::Errno->EDEADLK);
    ok(Errno::EDESTADDRREQ == SPVM::Errno->EDESTADDRREQ);
    ok(Errno::EDOM == SPVM::Errno->EDOM);
    ok(Errno::EEXIST == SPVM::Errno->EEXIST);
    ok(Errno::EFAULT == SPVM::Errno->EFAULT);
    ok(Errno::EFBIG == SPVM::Errno->EFBIG);
    ok(Errno::EHOSTUNREACH == SPVM::Errno->EHOSTUNREACH);
    ok(Errno::EIDRM == SPVM::Errno->EIDRM);
    ok(Errno::EILSEQ == SPVM::Errno->EILSEQ);
    ok(Errno::EINPROGRESS == SPVM::Errno->EINPROGRESS);
    ok(Errno::EINTR == SPVM::Errno->EINTR);
    ok(Errno::EINVAL == SPVM::Errno->EINVAL);
    ok(Errno::EIO == SPVM::Errno->EIO);
    ok(Errno::EISCONN == SPVM::Errno->EISCONN);
    ok(Errno::EISDIR == SPVM::Errno->EISDIR);
    ok(Errno::ELOOP == SPVM::Errno->ELOOP);
    ok(Errno::EMFILE == SPVM::Errno->EMFILE);
    ok(Errno::EMLINK == SPVM::Errno->EMLINK);
    ok(Errno::EMSGSIZE == SPVM::Errno->EMSGSIZE);
    ok(Errno::ENAMETOOLONG == SPVM::Errno->ENAMETOOLONG);
    ok(Errno::ENETDOWN == SPVM::Errno->ENETDOWN);
    ok(Errno::ENETRESET == SPVM::Errno->ENETRESET);
    ok(Errno::ENETUNREACH == SPVM::Errno->ENETUNREACH);
    ok(Errno::ENFILE == SPVM::Errno->ENFILE);
    ok(Errno::ENOBUFS == SPVM::Errno->ENOBUFS);
    ok(Errno::ENODATA == SPVM::Errno->ENODATA);
    ok(Errno::ENODEV == SPVM::Errno->ENODEV);
    ok(Errno::ENOENT == SPVM::Errno->ENOENT);
    ok(Errno::ENOEXEC == SPVM::Errno->ENOEXEC);
    ok(Errno::ENOLCK == SPVM::Errno->ENOLCK);
    ok(Errno::ENOLINK == SPVM::Errno->ENOLINK);
    ok(Errno::ENOMEM == SPVM::Errno->ENOMEM);
    ok(Errno::ENOMSG == SPVM::Errno->ENOMSG);
    ok(Errno::ENOPROTOOPT == SPVM::Errno->ENOPROTOOPT);
    ok(Errno::ENOSPC == SPVM::Errno->ENOSPC);
    ok(Errno::ENOSR == SPVM::Errno->ENOSR);
    ok(Errno::ENOSTR == SPVM::Errno->ENOSTR);
    ok(Errno::ENOSYS == SPVM::Errno->ENOSYS);
    ok(Errno::ENOTCONN == SPVM::Errno->ENOTCONN);
    ok(Errno::ENOTDIR == SPVM::Errno->ENOTDIR);
    ok(Errno::ENOTEMPTY == SPVM::Errno->ENOTEMPTY);
    ok(Errno::ENOTRECOVERABLE == SPVM::Errno->ENOTRECOVERABLE);
    ok(Errno::ENOTSOCK == SPVM::Errno->ENOTSOCK);
    ok(Errno::ENOTSUP == SPVM::Errno->ENOTSUP);
    ok(Errno::ENOTTY == SPVM::Errno->ENOTTY);
    ok(Errno::ENXIO == SPVM::Errno->ENXIO);
    ok(Errno::EOPNOTSUPP == SPVM::Errno->EOPNOTSUPP);
    ok(Errno::EOVERFLOW == SPVM::Errno->EOVERFLOW);
    ok(Errno::EOWNERDEAD == SPVM::Errno->EOWNERDEAD);
    ok(Errno::EPERM == SPVM::Errno->EPERM);
    ok(Errno::EPIPE == SPVM::Errno->EPIPE);
    ok(Errno::EPROTO == SPVM::Errno->EPROTO);
    ok(Errno::EPROTONOSUPPORT == SPVM::Errno->EPROTONOSUPPORT);
    ok(Errno::EPROTOTYPE == SPVM::Errno->EPROTOTYPE);
    ok(Errno::ERANGE == SPVM::Errno->ERANGE);
    ok(Errno::EROFS == SPVM::Errno->EROFS);
    ok(Errno::ESPIPE == SPVM::Errno->ESPIPE);
    ok(Errno::ESRCH == SPVM::Errno->ESRCH);
    ok(Errno::ETIME == SPVM::Errno->ETIME);
    ok(Errno::ETIMEDOUT == SPVM::Errno->ETIMEDOUT);
    ok(Errno::ETXTBSY == SPVM::Errno->ETXTBSY);
    ok(Errno::EWOULDBLOCK == SPVM::Errno->EWOULDBLOCK);
    ok(Errno::EXDEV == SPVM::Errno->EXDEV);
  }
  
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

