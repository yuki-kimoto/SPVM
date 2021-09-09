package SPVM::NumberUtil;

1;

=head1 NAME

SPVM::NumberUtil - NumberUtil in SPVM | Number Utilities

=head1 SYNOPSYS
  
  use NumberUtil;
  
  my $int8_max = NumberUtil->INT8_MAX();
  my $int16_max = NumberUtil->INT16_MAX();
  my $int32_max = NumberUtil->INT32_MAX();
  my $int64_max = NumberUtil->INT64_MAX();
  
  my $rand = NumberUtil->rand();

=head1 DESCRIPTION

Number utilities.

=head1 STATIC METHODS

=head2 INT8_MIN

  sub INT8_MIN : byte ()

Return -128. The minimal value of the signed 8bit integer.

=head2 INT8_MAX

  INT8_MAX : byte ()

Return 127. The maximum value of the signed 8bit integer.

=head2 INT16_MIN

  sub INT16_MIN : short ()

Return -32768. The minimal value of the signed 16bit integer. 

=head2 INT16_MAX

  sub INT16_MAX : short ()

Return 32767. The maximum value of the signed 16bit integer .

=head2 INT32_MIN

  sub INT32_MIN : int ()

Return -2147483648. The minimal value of the signed 32bit integer.

=head2 INT32_MAX

  sub INT32_MAX : int ()

Return 2147483647. The maximum value of the signed 32bit integer.

=head2 INT64_MIN

  sub INT64_MIN : long ()

Return -9223372036854775808. The minimal value of signed 64bit integer.

=head2 INT64_MAX

  sub INT64_MAX : long ()

Return 9223372036854775807. The maximum value of the signed 64bit integer. 

=head2 UINT8_MAX

  sub UINT8_MAX : byte ()

Return -1. The same bit expression of 0xFF in the unsigned 8bit integer in 2's complement.

=head2 UINT16_MAX

  sub UINT16_MAX : short ()

Return -1. The same bit expression of 0xFFFF in the unsigned 16bit integer in 2's complement.

=head2 UINT32_MAX

  sub UINT32_MAX : int ()

Return -1. The same bit expression of 0xFFFFFFFF in the unsigned 32bit integer in 2's complement.

=head2 UINT64_MAX

  sub UINT64_MAX : long ()

Return -1. The same bit expression of 0xFFFFFFFFFFFFFFFF in the unsigned 64bit integer in 2's complement.

=head2 FLT_MIN

  sub FLT_MIN : float ()

Return the value of FLT_MIN macro defined in float.h C header.

=head2 FLT_MAX

  sub FLT_MAX : float ()

Return the value of FLT_MAX macro defined in float.h C header.

=head2 DBL_MIN

  sub DBL_MIN : double ()

Return the value of DBL_MIN macro defined in float.h C header.

=head2 DBL_MAX

  sub DBL_MAX : double ()

Return the value of DBL_MAX macro defined in float.h C header.

=head2 crand

  sub crand : int ();

Get random number(0 <= rundom_number <= NumberUtil->RAND_MAX). This is same as rand function of C language.

The first seed is initialized by epoch time automatically. If you set a seed manually, you can use <srand> static method.

This method is not thread safe because internaly this method use rand function of C language.

=head2 rand

  sub rand : double ();

Get random number(0 <= random_number < 1). This is same as rand function of Perl language.

The first seed is initialized by epoch time automatically. If you set a seed manually, you can use <srand> static method.

This method is not thread safe because internaly this method use rand function of C language.

=head2 srand

  sub srand : void ($seed : long);

Sets random number seed for the C<crand> or C<rand> static method.
