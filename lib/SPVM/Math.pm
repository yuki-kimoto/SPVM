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

=head2 FE_DOWNWARD

  sub FE_DOWNWARD : int ()

=head2 FE_TONEAREST

  sub FE_TONEAREST : int ()

=head2 FE_TOWARDZERO

  sub FE_TOWARDZERO : int ()

=head2 FE_UPWARD

  sub FE_UPWARD : int ()

=head2 FP_ILOGB0

  sub FP_ILOGB0 : int ()

=head2 FP_ILOGBNAN

  sub FP_ILOGBNAN : int ()

=head2 FP_INFINITE

  sub FP_INFINITE : int ()

=head2 FP_NAN

  sub FP_NAN : int ()

=head2 FP_ZERO

  sub FP_ZERO : int ()

=head2 HUGE_VAL

  sub HUGE_VAL : double ()

=head2 HUGE_VALF

  sub HUGE_VALF : float ()

=head2 INFINITY

  sub INFINITY : double ()

=head2 INFINITYF

  sub INFINITYF : float ()

=head2 NAN

  sub NAN : double ()

=head2 NANF

  sub NANF : float ()

=head2 acos

  sub acos : double ($x : double)

=head2 acosf

  sub acosf : float ($x : float)

=head2 acosh

  sub acosh : double ($x : double)

=head2 acoshf

  sub acoshf : float ($x : float)

=head2 asin

  sub asin : double ($x : double)

=head2 asinf

  sub asinf : float ($x : float)

=head2 asinh

  sub asinh : double ($x : double)

=head2 asinhf

  sub asinhf : float ($x : float)

=head2 atan

  sub atan : double ($x : double)

=head2 atan2

  sub atan2 : double ($y : double, $x : double)

=head2 atanf

  sub atanf : float ($x : float)

=head2 atanh

  sub atanh : double ($x : double)

=head2 atanhf

  sub atanhf : float ($x : float)

=head2 cabs

  sub cabs : double ($z : SPVM::Complex_2d)

=head2 cabsf

  sub cabsf : float ($z : SPVM::Complex_2f)

=head2 cacos

  sub cacos : SPVM::Complex_2d ($z : SPVM::Complex_2d)

=head2 cacosf

  sub cacosf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

=head2 cacosh

  sub cacosh : SPVM::Complex_2d ($z : SPVM::Complex_2d)

=head2 cacoshf

  sub cacoshf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

=head2 cadd

  sub cadd : SPVM::Complex_2d ($z1 : SPVM::Complex_2d, $z2 : SPVM::Complex_2d)

=head2 caddf

  sub caddf : SPVM::Complex_2f ($z1 : SPVM::Complex_2f, $z2 : SPVM::Complex_2f)

=head2 carg

  sub carg : double ($z : SPVM::Complex_2d)

=head2 cargf

  sub cargf : float ($z : SPVM::Complex_2f)

=head2 casin

  sub casin : SPVM::Complex_2d ($z : SPVM::Complex_2d)

=head2 casinf

  sub casinf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

=head2 casinh

  sub casinh : SPVM::Complex_2d ($z : SPVM::Complex_2d)

=head2 casinhf

  sub casinhf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

=head2 catan

  sub catan : SPVM::Complex_2d ($z : SPVM::Complex_2d)

=head2 catanf

  sub catanf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

=head2 catanh

  sub catanh : SPVM::Complex_2d ($z : SPVM::Complex_2d)

=head2 catanhf

  sub catanhf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

=head2 cbrt

  sub cbrt : double ($x : double)

=head2 cbrtf

  sub cbrtf : float ($x : float)

=head2 ccos

  sub ccos : SPVM::Complex_2d ($z : SPVM::Complex_2d)

=head2 ccosf

  sub ccosf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

=head2 ccosh

  sub ccosh : SPVM::Complex_2d ($z : SPVM::Complex_2d)

=head2 ccoshf

  sub ccoshf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

=head2 cdiv

  sub cdiv : SPVM::Complex_2d ($z1 : SPVM::Complex_2d, $z2 : SPVM::Complex_2d)

=head2 cdivf

  sub cdivf : SPVM::Complex_2f ($z1 : SPVM::Complex_2f, $z2 : SPVM::Complex_2f)

=head2 ceil

  sub ceil : double ($x : double)

=head2 ceilf

  sub ceilf : float ($x : float)

=head2 cexp

  sub cexp : SPVM::Complex_2d ($z : SPVM::Complex_2d)

=head2 cexpf

  sub cexpf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

=head2 clog

  sub clog : SPVM::Complex_2d ($z : SPVM::Complex_2d)

=head2 clogf

  sub clogf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

=head2 cmul

  sub cmul : SPVM::Complex_2d ($z1 : SPVM::Complex_2d, $z2 : SPVM::Complex_2d)

=head2 cmulf

  sub cmulf : SPVM::Complex_2f ($z1 : SPVM::Complex_2f, $z2 : SPVM::Complex_2f)

=head2 complex

  sub complex : SPVM::Complex_2d ($x : double, $y : double)

=head2 complexf

  sub complexf : SPVM::Complex_2f ($x : float, $y : float)

=head2 conj

  sub conj : SPVM::Complex_2d ($z : SPVM::Complex_2d)

=head2 conjf

  sub conjf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

=head2 copysign

  sub copysign : double ($x1 : double, $x2 : double)

=head2 copysignf

  sub copysignf : float ($x1 : float, $x2 : float)

=head2 cos

  sub cos : double ($x : double)

=head2 cosf

  sub cosf : float ($x : float)

=head2 cosh

  sub cosh : double ($x : double)

=head2 coshf

  sub coshf : float ($x : float)

=head2 cpow

  sub cpow : SPVM::Complex_2d ($z1 : SPVM::Complex_2d, $z2 : SPVM::Complex_2d)

=head2 cpowf

  sub cpowf : SPVM::Complex_2f ($z1 : SPVM::Complex_2f, $z2 : SPVM::Complex_2f)

=head2 cproj

  sub cproj : SPVM::Complex_2d ($z : SPVM::Complex_2d)

=head2 cprojf

  sub cprojf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

=head2 cscamul

  sub cscamul : SPVM::Complex_2d ($c : double, $z : SPVM::Complex_2d)

=head2 cscamulf

  sub cscamulf : SPVM::Complex_2f ($c : float, $z : SPVM::Complex_2f)

=head2 csin

  sub csin : SPVM::Complex_2d ($z : SPVM::Complex_2d)

=head2 csinf

  sub csinf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

=head2 csinh

  sub csinh : SPVM::Complex_2d ($z : SPVM::Complex_2d)

=head2 csinhf

  sub csinhf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

=head2 csqrt

  sub csqrt : SPVM::Complex_2d ($z : SPVM::Complex_2d)

=head2 csqrtf

  sub csqrtf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

=head2 csub

  sub csub : SPVM::Complex_2d ($z1 : SPVM::Complex_2d, $z2 : SPVM::Complex_2d)

=head2 csubf

  sub csubf : SPVM::Complex_2f ($z1 : SPVM::Complex_2f, $z2 : SPVM::Complex_2f)

=head2 ctan

  sub ctan : SPVM::Complex_2d ($z : SPVM::Complex_2d)

=head2 ctanf

  sub ctanf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

=head2 ctanh

  sub ctanh : SPVM::Complex_2d ($z : SPVM::Complex_2d)

=head2 ctanhf

  sub ctanhf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

=head2 erf

  sub erf : double ($x : double)

=head2 erfc

  sub erfc : double ($x : double)

=head2 erfcf

  sub erfcf : float ($x : float)

=head2 erff

  sub erff : float ($x : float)

=head2 exp

  sub exp : double ($x : double)

=head2 exp2

  sub exp2 : double ($x : double)

=head2 exp2f

  sub exp2f : float ($x : float)

=head2 expf

  sub expf : float ($x : float)

=head2 expm1

  sub expm1 : double ($x : double)

=head2 expm1f

  sub expm1f : float ($x : float)

=head2 fabs

  sub fabs : double ($x : double)

=head2 fabsf

  sub fabsf : float ($x : float)

=head2 fdim

  sub fdim : double ($x1 : double, $x2 : double)

=head2 fdimf

  sub fdimf : float ($x1 : float, $x2 : float)

=head2 fesetround

  sub fesetround : int ($round : int)

=head2 floor

  sub floor : double ($x : double)

=head2 floorf

  sub floorf : float ($x : float)

=head2 fma

  sub fma : double ($x1 : double, $x2 : double, $x3 : double)

=head2 fmaf

  sub fmaf : float ($x1 : float, $x2 : float, $x3 : float)

=head2 fmax

  sub fmax : double ($x1 : double, $x2 : double)

=head2 fmaxf

  sub fmaxf : float ($x1 : float, $x2 : float)

=head2 fmin

  sub fmin : double ($x1 : double, $x2 : double)

=head2 fminf

  sub fminf : float ($x1 : float, $x2 : float)

=head2 fmod

  sub fmod : double ($x1 : double, $x2 : double)

=head2 fmodf

  sub fmodf : float ($x1 : float, $x2 : float)

=head2 fpclassify

  sub fpclassify : int ($x : double)

=head2 fpclassifyf

  sub fpclassifyf : int ($x : float)

=head2 frexp

  sub frexp : double ($x : double, $exp : int&)

=head2 frexpf

  sub frexpf : float ($x : float, $exp : int&)

=head2 hypot

  sub hypot : double ($x : double, $y : double)

=head2 hypotf

  sub hypotf : float ($x : float, $y : float)

=head2 ilogb

  sub ilogb : int ($x : double)

=head2 ilogbf

  sub ilogbf : int ($x : float)

=head2 isfinite

  sub isfinite : int ($x : double)

=head2 isfinitef

  sub isfinitef : int($x : float)

=head2 isgreater

  sub isgreater : int ($x1 : double, $x2 : double)

=head2 isgreaterequal

  sub isgreaterequal : int ($x1 : double, $x2 : double)

=head2 isgreaterequalf

  sub isgreaterequalf : int ($x1 : float, $x2 : float)

=head2 isgreaterf

  sub isgreaterf : int ($x1 : float, $x2 : float)

=head2 isinf

  sub isinf : int ($x : double)

=head2 isinff

  sub isinff : int($x : float)

=head2 isless

  sub isless : int ($x1 : double, $x2 : double)

=head2 islessequal

  sub islessequal : int ($x1 : double, $x2 : double)

=head2 islessequalf

  sub islessequalf : int ($x1 : float, $x2 : float)

=head2 islessf

  sub islessf : int ($x1 : float, $x2 : float)

=head2 islessgreater

  sub islessgreater : int ($x1 : double, $x2 : double)

=head2 islessgreaterf

  sub islessgreaterf : int ($x1 : float, $x2 : float)

=head2 isnan

  sub isnan : int ($x : double)

=head2 isnanf

  sub isnanf : int ($x : float)

=head2 isunordered

  sub isunordered : int ($x1 : double, $x2 : double)

=head2 isunorderedf

  sub isunorderedf : int ($x1 : float, $x2 : float)

=head2 ldexp

  sub ldexp : double ($x : double, $exp : int)

=head2 ldexpf

  sub ldexpf : float ($x : float, $exp : int)

=head2 lgamma

  sub lgamma : double ($x : double)

=head2 lgammaf

  sub lgammaf : float ($x : float)

=head2 log

  sub log : double ($x : double)

=head2 log10

  sub log10 : double ($x : double)

=head2 log10f

  sub log10f : float ($x : float)

=head2 log1p

  sub log1p : double ($x : double)

=head2 log1pf

  sub log1pf : float ($x : float)

=head2 log2

  sub log2 : double ($x : double)

=head2 log2f

  sub log2f : float ($x : float)

=head2 logb

  sub logb : double ($x : double)

=head2 logbf

  sub logbf : float ($x : float)

=head2 logf

  sub logf : float ($x : float)

=head2 lround

  sub lround : long ($x : double)

=head2 lroundf

  sub lroundf : long ($x : float)

=head2 modf

  sub modf : double ($x : double, $intpart : double&)

=head2 modff

  sub modff : float ($x : float, $intpart : float&)

=head2 nan

  sub nan : double ($str : string)

=head2 nanf

  sub nanf : float ($str : string)

=head2 nearbyint

  sub nearbyint : double ($x : double)

=head2 nearbyintf

  sub nearbyintf : float ($x : float)

=head2 nextafter

  sub nextafter : double ($x1 : double, $x2 : double)

=head2 nextafterf

  sub nextafterf : float ($x1 : float, $x2 : float)

=head2 nexttoward

  sub nexttoward : double ($x1 : double, $x2 : double)

=head2 nexttowardf

  sub nexttowardf : float ($x1 : float, $x2 : double)

=head2 pi

  sub pi : double ()

=head2 pow

  sub pow : double ($x : double, $y : double)

=head2 powf

  sub powf : float ($x : float, $y : float)

=head2 remainder

  sub remainder : double ($x1 : double, $x2 : double)

=head2 remainderf

  sub remainderf : float ($x1 : float, $x2 : float)

=head2 remquo

  sub remquo : double ($x1 : double, $x2 : double, $quo : int&)

=head2 remquof

  sub remquof : float ($x1 : float, $x2 : float, $quo : int&)

=head2 round

  sub round : double ($x : double)

=head2 roundf

  sub roundf : float ($x : float)

=head2 scalbln

  sub scalbln : double ($x : double, $exp : long)

=head2 scalblnf

  sub scalblnf : float ($x : float, $exp : long)

=head2 scalbn

  sub scalbn : double ($x : double, $exp : int)

=head2 scalbnf

  sub scalbnf : float ($x : float, $exp : int)

=head2 signbit

  sub signbit : int ($x : double)

=head2 signbitf

  sub signbitf : int ($x : float)

=head2 sin

  sub sin : double ($x : double)

=head2 sinf

  sub sinf : float ($x : float)

=head2 sinh

  sub sinh : double ($x : double)

=head2 sinhf

  sub sinhf : float ($x : float)

=head2 sqrt

  sub sqrt : double ($x : double)

=head2 sqrtf

  sub sqrtf : float ($x : float)

=head2 tan

  sub tan : double ($x : double)

=head2 tanf

  sub tanf : float ($x : float)

=head2 tanh

  sub tanh : double ($x : double)

=head2 tanhf

  sub tanhf : float ($x : float)

=head2 tgamma

  sub tgamma : double ($x : double)

=head2 tgammaf

  sub tgammaf : float ($x : float)

=head2 trunc

  sub trunc : double ($x : double)

=head2 truncf

  sub truncf : float ($x : float)

