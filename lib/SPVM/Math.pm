package SPVM::Math;

1;

=head1 NAME

SPVM::Math - Mathmatical functions

=head1 SYNOPSYS

  use SPVM::Math;
  
  my $pi = SPVM::Math->pi;
  my $sin = SPVM::Math->sin($pi / 4);
  
=head1 DESCRIPTION

L<SPVM::Math> defines mathmatical functions. 

=head1 CLASS METHODS

=head2 pi

  sub pi : double()

=head2 INFINITYF

  sub INFINITYF : float ()

=head2 NANF

  sub NANF : float ()

=head2 isinff

  sub isinff : int($x : float)

=head2 isfinitef

  sub isfinitef : int($x : float)

=head2 isnanf

  sub isnanf : int ($x : float)

=head2 INFINITY

  sub INFINITY : double ()

=head2 NAN

  sub NAN : double ()

=head2 isinf

  sub isinf : int ($x : double)

=head2 isfinite

  sub isfinite : int ($x : double)

=head2 isnan

  sub isnan : int ($x : double)

=head2 acos

  sub acos : double ($x : double)

=head2 asin

  sub asin : double($x : double)

=head2 atan

  sub atan : double ($x : double)

=head2 atan2

  sub atan2 : double ($y : double, $x : double)

=head2 cos

  sub cos : double ($x : double)

=head2 sin

  sub sin : double ($x : double)

=head2 tan

  sub tan : double ($x : double)

=head2 acosh

  sub acosh : double ($x : double)

=head2 asinh

  sub asinh : double ($x : double)

=head2 atanh

  sub atanh : double ($x : double)

=head2 cosh

  sub cosh : double ($x : double)

=head2 sinh

  sub sinh : double ($x : double)

=head2 tanh

  sub tanh : double ($x : double)

=head2 exp

  sub exp : double ($x : double)

=head2 exp2

  sub exp2 : double ($x : double)

=head2 expm1

  sub expm1 : double ($x : double)

=head2 log

  sub log : double ($x : double)

=head2 log10

  sub log10 : double ($x : double)

=head2 log1p

  sub log1p : double ($x : double)

=head2 cbrt

  sub cbrt : double ($x : double)

=head2 fabs

  sub fabs : double ($x : double)

=head2 hypot

  sub hypot : double ($x : double, $y : double)

=head2 pow

  sub pow : double ($x : double, $y : double)

=head2 sqrt

  sub sqrt : double ($x : double)

=head2 erf

  sub erf : double ($x : double)

=head2 erfc

  sub erfc : double ($x : double)

=head2 lgamma

  sub lgamma : double ($x : double)

=head2 tgamma

  sub tgamma : double ($x : double)

=head2 ceil

  sub ceil : double ($x : double)

=head2 floor

  sub floor : double ($x : double)

=head2 nearbyint

  sub nearbyint : double ($x : double)

=head2 round

  sub round : double ($x : double)

=head2 remainder

  sub remainder : double ($x1 : double, $x2 : double)

=head2 signbitf

  sub signbitf : int ($num : float)

=head2 signbit

  sub signbit : int ($num : double)
