package SPVM::Errno;

use SPVM 'SPVM::Errno';

1;

=head1 NAME

SPVM::Errno - Error number

=head1 SYNOPSYS

  use SPVM::Errno;
  
  # Get a current error number;
  my $errno = SPVM::Errno->errno;
  
  # Set a current error number;
  SPVM::Errno->set_errno(SPVM::Errno->EACCES);
  
  # Get a error number constant
  my $eaccess = SPVM::Errno->EACCES;
  
=head1 DESCRIPTION

L<SPVM::Errno> gets and sets a error number, and L<SPVM::Errno> defines various error numbers.

=head1 CLASS METHODS

=head2 errno

  sub errno : int()

Get a current error number;

=head2 set_errno

  sub set_errno : void ($errno : int)

Set a current error number;

=head strerror

  sub strerror : string ($errno : int)

Get a error string corresponding to the error number.

This method is thread safe unlike strerror function of C language.

=head2 E2BIG

  sub E2BIG : int ()

=head2 EACCES

  sub EACCES : int ()

=head2 EADDRINUSE

  sub EADDRINUSE : int ()

=head2 EADDRNOTAVAIL

  sub EADDRNOTAVAIL : int ()

=head2 EAFNOSUPPORT

  sub EAFNOSUPPORT : int ()

=head2 EAGAIN

  sub EAGAIN : int ()

=head2 EALREADY

  sub EALREADY : int ()

=head2 EBADF

  sub EBADF : int ()

=head2 EBADMSG

  sub EBADMSG : int ()

=head2 EBUSY

  sub EBUSY : int ()

=head2 ECANCELED

  sub ECANCELED : int ()

=head2 ECHILD

  sub ECHILD : int ()

=head2 ECONNABORTED

  sub ECONNABORTED : int ()

=head2 ECONNREFUSED

  sub ECONNREFUSED : int ()

=head2 ECONNRESET

  sub ECONNRESET : int ()

=head2 EDEADLK

  sub EDEADLK : int ()

=head2 EDESTADDRREQ

  sub EDESTADDRREQ : int ()

=head2 EDOM

  sub EDOM : int ()

=head2 EEXIST

  sub EEXIST : int ()

=head2 EFAULT

  sub EFAULT : int ()

=head2 EFBIG

  sub EFBIG : int ()

=head2 EHOSTUNREACH

  sub EHOSTUNREACH : int ()

=head2 EIDRM

  sub EIDRM : int ()

=head2 EILSEQ

  sub EILSEQ : int ()

=head2 EINPROGRESS

  sub EINPROGRESS : int ()

=head2 EINTR

  sub EINTR : int ()

=head2 EINVAL

  sub EINVAL : int ()

=head2 EIO

  sub EIO : int ()

=head2 EISCONN

  sub EISCONN : int ()

=head2 EISDIR

  sub EISDIR : int ()

=head2 ELOOP

  sub ELOOP : int ()

=head2 EMFILE

  sub EMFILE : int ()

=head2 EMLINK

  sub EMLINK : int ()

=head2 EMSGSIZE

  sub EMSGSIZE : int ()

=head2 ENAMETOOLONG

  sub ENAMETOOLONG : int ()

=head2 ENETDOWN

  sub ENETDOWN : int ()

=head2 ENETRESET

  sub ENETRESET : int ()

=head2 ENETUNREACH

  sub ENETUNREACH : int ()

=head2 ENFILE

  sub ENFILE : int ()

=head2 ENOBUFS

  sub ENOBUFS : int ()

=head2 ENODATA

  sub ENODATA : int ()

=head2 ENODEV

  sub ENODEV : int ()

=head2 ENOENT

  sub ENOENT : int ()

=head2 ENOEXEC

  sub ENOEXEC : int ()

=head2 ENOLCK

  sub ENOLCK : int ()

=head2 ENOLINK

  sub ENOLINK : int ()

=head2 ENOMEM

  sub ENOMEM : int ()

=head2 ENOMSG

  sub ENOMSG : int ()

=head2 ENOPROTOOPT

  sub ENOPROTOOPT : int ()

=head2 ENOSPC

  sub ENOSPC : int ()

=head2 ENOSR

  sub ENOSR : int ()

=head2 ENOSTR

  sub ENOSTR : int ()

=head2 ENOSYS

  sub ENOSYS : int ()

=head2 ENOTCONN

  sub ENOTCONN : int ()

=head2 ENOTDIR

  sub ENOTDIR : int ()

=head2 ENOTEMPTY

  sub ENOTEMPTY : int ()

=head2 ENOTRECOVERABLE

  sub ENOTRECOVERABLE : int ()

=head2 ENOTSOCK

  sub ENOTSOCK : int ()

=head2 ENOTSUP

  sub ENOTSUP : int ()

=head2 ENOTTY

  sub ENOTTY : int ()

=head2 ENXIO

  sub ENXIO : int ()

=head2 EOPNOTSUPP

  sub EOPNOTSUPP : int ()

=head2 EOVERFLOW

  sub EOVERFLOW : int ()

=head2 EOWNERDEAD

  sub EOWNERDEAD : int ()

=head2 EPERM

  sub EPERM : int ()

=head2 EPIPE

  sub EPIPE : int ()

=head2 EPROTO

  sub EPROTO : int ()

=head2 EPROTONOSUPPORT

  sub EPROTONOSUPPORT : int ()

=head2 EPROTOTYPE

  sub EPROTOTYPE : int ()

=head2 ERANGE

  sub ERANGE : int ()

=head2 EROFS

  sub EROFS : int ()

=head2 ESPIPE

  sub ESPIPE : int ()

=head2 ESRCH

  sub ESRCH : int ()

=head2 ETIME

  sub ETIME : int ()

=head2 ETIMEDOUT

  sub ETIMEDOUT : int ()

=head2 ETXTBSY

  sub ETXTBSY : int ()

=head2 EWOULDBLOCK

  sub EWOULDBLOCK : int ()

=head2 EXDEV

  sub EXDEV : int ()

=head2 EOTHER

  sub EOTHER : int ()
