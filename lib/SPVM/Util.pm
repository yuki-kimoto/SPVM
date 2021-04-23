package SPVM::Util;

1;

=head1 NAME

SPVM::Util - Variouse utilities

=head1 SYNOPSYS
  
  use SPVM::Util;
  
  my $int8_max = SPVM::Util->INT8_MAX();
  my $int16_max = SPVM::Util->INT16_MAX();
  my $int32_max = SPVM::Util->INT32_MAX();
  my $int64_max = SPVM::Util->INT64_MAX();
  

=head1 DESCRIPTION

Utilities

=head1 STATIC METHODS

=head2 INT8_MIN

  sub INT8_MIN : byte ()

byte(8bit integer) min value. return -128.

=head2 INT8_MAX

  INT8_MAX : byte ()

byte(8bit integer) max value. return 127.

=head2 INT16_MIN

  sub INT16_MIN : short ()

short(16bit integer) min value. return -32768.

=head2 INT16_MAX

  sub INT16_MAX : short ()

short(16bit integer) max value. return 32767.

=head2 INT32_MIN

  sub INT32_MIN : int ()

int(32bit integer) min value. return -2147483648.

=head2 INT32_MAX

  sub INT32_MAX : int ()

int(32bit integer) max value. return 2147483647.

=head2 INT64_MIN

  sub INT64_MIN : long ()

long(64bit integer) min value. return -9223372036854775808.

=head2 INT64_MAX

  sub INT64_MAX : long ()

long(64bit integer) max value. return 9223372036854775807.

=head2 UINT8_MAX

  sub UINT8_MAX : byte ()

return -1. This is same as bit expression of 0xFF in unsigned 8bit integer in 2's complement.

=head2 UINT16_MAX

  sub UINT16_MAX : short ()

return -1. This is same as bit expression of 0xFFFF in unsigned 8bit integer in 2's complement.

=head2 UINT32_MAX

  sub UINT32_MAX : int ()

return -1. This is same as bit expression of 0xFFFFFFFF in unsigned 8bit integer in 2's complement.

=head2 UINT64_MAX

  sub UINT64_MAX : long ()

return -1. This is same as bit expression of 0xFFFFFFFFFFFFFFFF in unsigned 8bit integer in 2's complement.

=head2 FLT_MIN

  sub FLT_MIN : float ()

return the value of FLT_MIN macro of float.h C library.

=head2 FLT_MAX

  sub FLT_MAX : float ()

return the value of FLT_MAX macro of float.h C library.

=head2 DBL_MIN

  sub DBL_MIN : double ()

return the value of DBL_MIN macro of float.h C library.

=head2 DBL_MAX

  sub DBL_MAX : double ()

return the value of DBL_MAX macro of float.h C library.

=head2 crand

  sub crand : int ();

Get random number(0 to SPVM::Util->RAND_MAX). This is same as rand function of C language.

The first seed is epoch time usually. Second seed is the return value.

  use SPVM::Time;
  my $rand1 = crand(SPVM::Time->time);
  my $rand2 = crand($rand1);

=head2 rand

  sub rand : double ();

Get random number(0 <= random_number < 1). This is same as rand function of Perl language.

The first seed is epoch time usually. Second seed is the return value.

  use SPVM::Time;
  my $rand1 = crand(SPVM::Time->time);
  my $rand2 = crand($rand1);

=head2 srand

  sub srand : void ($seed : long);

Sets random number seed for the "crand" static method.
