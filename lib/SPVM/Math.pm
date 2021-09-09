package SPVM::Math;

1;

=head1 NAME

SPVM::Math - Math functions

=head1 SYNOPSYS

  use SPVM::Math;
  
  my $sin = SPVM::Math->sin(SPVM::Math->PI / 4);
  
=head1 DESCRIPTION

L<Math|SPVM::Math> defines mathmatical functions. 

=head1 STATIC METHODS

=head2 abs

  sub abs : int ($x : int);

Get the abusolute value of a int value.

=head2 acos

  sub acos : double ($x : double)

acos function defined in C language math.h.

=head2 acosf

  sub acosf : float ($x : float)

acosf function defined in C language math.h.

=head2 acosh

  sub acosh : double ($x : double)

acosh function defined in C language math.h.

=head2 acoshf

  sub acoshf : float ($x : float)

acoshf function defined in C language math.h.

=head2 asin

  sub asin : double ($x : double)

asin function defined in C language math.h.

=head2 asinf

  sub asinf : float ($x : float)

asinf function defined in C language math.h.

=head2 asinh

  sub asinh : double ($x : double)

asinh function defined in C language math.h.

=head2 asinhf

  sub asinhf : float ($x : float)

asinhf function defined in C language math.h.

=head2 atan

  sub atan : double ($x : double)

atan function defined in C language math.h.

=head2 atan2

  sub atan2 : double ($y : double, $x : double)

atan2 function defined in C language math.h.

=head2 atanf

  sub atanf : float ($x : float)

atanf function defined in C language math.h.

=head2 atanh

  sub atanh : double ($x : double)

atanh function defined in C language math.h.

=head2 atanhf

  sub atanhf : float ($x : float)

atanhf function defined in C language math.h.

=head2 cabs

  sub cabs : double ($z : SPVM::Complex_2d)

cabs function defined in C language complex.h.

=head2 cabsf

  sub cabsf : float ($z : SPVM::Complex_2f)

cabsf function defined in C language complex.h.

=head2 cacos

  sub cacos : SPVM::Complex_2d ($z : SPVM::Complex_2d)

cacos function defined in C language complex.h.

=head2 cacosf

  sub cacosf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

cacosf function defined in C language complex.h.

=head2 cacosh

  sub cacosh : SPVM::Complex_2d ($z : SPVM::Complex_2d)

cacosh function defined in C language complex.h.

=head2 cacoshf

  sub cacoshf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

cacoshf function defined in C language complex.h.

=head2 cadd

  sub cadd : SPVM::Complex_2d ($z1 : SPVM::Complex_2d, $z2 : SPVM::Complex_2d)

cadd function defined in C language complex.h.

=head2 caddf

  sub caddf : SPVM::Complex_2f ($z1 : SPVM::Complex_2f, $z2 : SPVM::Complex_2f)

caddf function defined in C language complex.h.

=head2 carg

  sub carg : double ($z : SPVM::Complex_2d)

carg function defined in C language complex.h.

=head2 cargf

  sub cargf : float ($z : SPVM::Complex_2f)

cargf function defined in C language complex.h.

=head2 casin

  sub casin : SPVM::Complex_2d ($z : SPVM::Complex_2d)

casin function defined in C language complex.h.

=head2 casinf

  sub casinf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

casinf function defined in C language complex.h.

=head2 casinh

  sub casinh : SPVM::Complex_2d ($z : SPVM::Complex_2d)

casinh function defined in C language complex.h.

=head2 casinhf

  sub casinhf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

casinhf function defined in C language complex.h.

=head2 catan

  sub catan : SPVM::Complex_2d ($z : SPVM::Complex_2d)

catan function defined in C language complex.h.

=head2 catanf

  sub catanf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

catanf function defined in C language complex.h.

=head2 catanh

  sub catanh : SPVM::Complex_2d ($z : SPVM::Complex_2d)

catanh function defined in C language complex.h.

=head2 catanhf

  sub catanhf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

catanhf function defined in C language complex.h.

=head2 cbrt

  sub cbrt : double ($x : double)

cbrt function defined in C language math.h.

=head2 cbrtf

  sub cbrtf : float ($x : float)

cbrtf function defined in C language math.h.

=head2 ccos

  sub ccos : SPVM::Complex_2d ($z : SPVM::Complex_2d)

ccos function defined in C language complex.h.

=head2 ccosf

  sub ccosf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

ccosf function defined in C language complex.h.

=head2 ccosh

  sub ccosh : SPVM::Complex_2d ($z : SPVM::Complex_2d)

ccosh function defined in C language complex.h.

=head2 ccoshf

  sub ccoshf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

ccoshf function defined in C language complex.h.

=head2 cdiv

  sub cdiv : SPVM::Complex_2d ($z1 : SPVM::Complex_2d, $z2 : SPVM::Complex_2d)

double complex division.

=head2 cdivf

  sub cdivf : SPVM::Complex_2f ($z1 : SPVM::Complex_2f, $z2 : SPVM::Complex_2f)

float complex division.

=head2 ceil

  sub ceil : double ($x : double)

ceil function defined in C language math.h.

=head2 ceilf

  sub ceilf : float ($x : float)

ceilf function defined in C language math.h.

=head2 cexp

  sub cexp : SPVM::Complex_2d ($z : SPVM::Complex_2d)

cexp function defined in C language complex.h.

=head2 cexpf

  sub cexpf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

cexpf function defined in C language complex.h.

=head2 clog

  sub clog : SPVM::Complex_2d ($z : SPVM::Complex_2d)

clog function defined in C language complex.h.

=head2 clogf

  sub clogf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

clogf function defined in C language complex.h.

=head2 cmul

  sub cmul : SPVM::Complex_2d ($z1 : SPVM::Complex_2d, $z2 : SPVM::Complex_2d)

double complex multiplication.

=head2 cmulf

  sub cmulf : SPVM::Complex_2f ($z1 : SPVM::Complex_2f, $z2 : SPVM::Complex_2f)

float complex multiplication.

=head2 complex

  sub complex : SPVM::Complex_2d ($x : double, $y : double)

Create double complex value. This value is defined in L<Complex_2d|SPVM::Complex_2d>.

=head2 complexf

  sub complexf : SPVM::Complex_2f ($x : float, $y : float)

Create float complex value. This value is defined in L<Complex_2f|SPVM::Complex_2f>.

=head2 conj

  sub conj : SPVM::Complex_2d ($z : SPVM::Complex_2d)

conj function defined in C language complex.h.

=head2 conjf

  sub conjf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

conjf function defined in C language complex.h.

=head2 copysign

  sub copysign : double ($x1 : double, $x2 : double)

copysign function defined in C language math.h.

=head2 copysignf

  sub copysignf : float ($x1 : float, $x2 : float)

copysignf function defined in C language math.h.

=head2 cos

  sub cos : double ($x : double)

cos function defined in C language math.h.

=head2 cosf

  sub cosf : float ($x : float)

cosf function defined in C language math.h.

=head2 cosh

  sub cosh : double ($x : double)

cosh function defined in C language math.h.

=head2 coshf

  sub coshf : float ($x : float)

coshf function defined in C language math.h.

=head2 cpow

  sub cpow : SPVM::Complex_2d ($z1 : SPVM::Complex_2d, $z2 : SPVM::Complex_2d)

cpow function defined in C language complex.h.

=head2 cpowf

  sub cpowf : SPVM::Complex_2f ($z1 : SPVM::Complex_2f, $z2 : SPVM::Complex_2f)

cpowf function defined in C language complex.h.

=head2 cscamul

  sub cscamul : SPVM::Complex_2d ($c : double, $z : SPVM::Complex_2d)

double complex scalar multiplication.

=head2 cscamulf

  sub cscamulf : SPVM::Complex_2f ($c : float, $z : SPVM::Complex_2f)

float complex scalar multiplication.

=head2 csin

  sub csin : SPVM::Complex_2d ($z : SPVM::Complex_2d)

csin function defined in C language complex.h.

=head2 csinf

  sub csinf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

csinf function defined in C language complex.h.

=head2 csinh

  sub csinh : SPVM::Complex_2d ($z : SPVM::Complex_2d)

csinh function defined in C language complex.h.

=head2 csinhf

  sub csinhf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

csinhf function defined in C language complex.h.

=head2 csqrt

  sub csqrt : SPVM::Complex_2d ($z : SPVM::Complex_2d)

csqrt function defined in C language complex.h.

=head2 csqrtf

  sub csqrtf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

csqrtf function defined in C language complex.h.

=head2 csub

  sub csub : SPVM::Complex_2d ($z1 : SPVM::Complex_2d, $z2 : SPVM::Complex_2d)

csub function defined in C language complex.h.

=head2 csubf

  sub csubf : SPVM::Complex_2f ($z1 : SPVM::Complex_2f, $z2 : SPVM::Complex_2f)

csubf function defined in C language complex.h.

=head2 ctan

  sub ctan : SPVM::Complex_2d ($z : SPVM::Complex_2d)

ctan function defined in C language complex.h.

=head2 ctanf

  sub ctanf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

ctanf function defined in C language complex.h.

=head2 ctanh

  sub ctanh : SPVM::Complex_2d ($z : SPVM::Complex_2d)

ctanh function defined in C language complex.h.

=head2 ctanhf

  sub ctanhf : SPVM::Complex_2f ($z : SPVM::Complex_2f)

ctanhf function defined in C language complex.h.

=head2 E

  sub E : double ()

Euler’s Number e. This value is 0x1.5bf0a8b145769p+1.

=head2 erf

  sub erf : double ($x : double)

erf function defined in C language math.h.

=head2 erfc

  sub erfc : double ($x : double)

erfc function defined in C language math.h.

=head2 erfcf

  sub erfcf : float ($x : float)

erfcf function defined in C language math.h.

=head2 erff

  sub erff : float ($x : float)

erff function defined in C language math.h.

=head2 exp

  sub exp : double ($x : double)

exp function defined in C language math.h.

=head2 exp2

  sub exp2 : double ($x : double)

exp2 function defined in C language math.h.

=head2 exp2f

  sub exp2f : float ($x : float)

exp2f function defined in C language math.h.

=head2 expf

  sub expf : float ($x : float)

expf function defined in C language math.h.

=head2 expm1

  sub expm1 : double ($x : double)

expm1 function defined in C language math.h.

=head2 expm1f

  sub expm1f : float ($x : float)

expm1f function defined in C language math.h.

=head2 fabs

  sub fabs : double ($x : double)

fabs function defined in C language math.h.

=head2 fabsf

  sub fabsf : float ($x : float)

fabsf function defined in C language math.h.

=head2 fdim

  sub fdim : double ($x1 : double, $x2 : double)

fdim function defined in C language math.h.

=head2 fdimf

  sub fdimf : float ($x1 : float, $x2 : float)

fdimf function defined in C language math.h.

=head2 FE_DOWNWARD

  sub FE_DOWNWARD : int ()

FE_DOWNWARD macro defined in C language fenv.h.

=head2 FE_TONEAREST

  sub FE_TONEAREST : int ()

FE_TONEAREST macro defined in C language fenv.h.

=head2 FE_TOWARDZERO

  sub FE_TOWARDZERO : int ()

FE_TOWARDZERO macro defined in C language fenv.h.

=head2 FE_UPWARD

  sub FE_UPWARD : int ()

FE_UPWARD macro defined in C language fenv.h.

=head2 fesetround

  sub fesetround : int ($round : int)

fesetround function defined in C language math.h.

=head2 floor

  sub floor : double ($x : double)

floor function defined in C language math.h.

=head2 floorf

  sub floorf : float ($x : float)

floorf function defined in C language math.h.

=head2 fma

  sub fma : double ($x1 : double, $x2 : double, $x3 : double)

fma function defined in C language math.h.

=head2 fmaf

  sub fmaf : float ($x1 : float, $x2 : float, $x3 : float)

fmaf function defined in C language math.h.

=head2 fmax

  sub fmax : double ($x1 : double, $x2 : double)

fmax function defined in C language math.h.

=head2 fmaxf

  sub fmaxf : float ($x1 : float, $x2 : float)

fmaxf function defined in C language math.h.

=head2 fmin

  sub fmin : double ($x1 : double, $x2 : double)

fmin function defined in C language math.h.

=head2 fminf

  sub fminf : float ($x1 : float, $x2 : float)

fminf function defined in C language math.h.

=head2 fmod

  sub fmod : double ($x1 : double, $x2 : double)

fmod function defined in C language math.h.

=head2 fmodf

  sub fmodf : float ($x1 : float, $x2 : float)

fmodf function defined in C language math.h.

=head2 FP_ILOGB0

  sub FP_ILOGB0 : int ()

FP_ILOGB0 macro defined in C language fenv.h.

=head2 FP_ILOGBNAN

  sub FP_ILOGBNAN : int ()

FP_ILOGBNAN macro defined in C language fenv.h.

=head2 FP_INFINITE

  sub FP_INFINITE : int ()

FP_INFINITE macro defined in C language fenv.h.

=head2 FP_NAN

  sub FP_NAN : int ()

FP_NAN macro defined in C language fenv.h.

=head2 FP_ZERO

  sub FP_ZERO : int ()

FP_ZERO macro defined in C language fenv.h.

=head2 fpclassify

  sub fpclassify : int ($x : double)

fpclassify macro defined in C language math.h. This method receives a double value.

=head2 fpclassifyf

  sub fpclassifyf : int ($x : float)

fpclassify macro defined in C language math.h for float type. This method receives a float value.

=head2 frexp

  sub frexp : double ($x : double, $exp : int&)

frexp function defined in C language math.h.

=head2 frexpf

  sub frexpf : float ($x : float, $exp : int&)

frexpf function defined in C language math.h.

=head2 HUGE_VAL

  sub HUGE_VAL : double ()

HUGE_VAL macro defined in C language math.h.

=head2 HUGE_VALF

  sub HUGE_VALF : float ()

HUGE_VALF macro defined in C language math.h.

=head2 hypot

  sub hypot : double ($x : double, $y : double)

hypot function defined in C language math.h.

=head2 hypotf

  sub hypotf : float ($x : float, $y : float)

hypotf function defined in C language math.h.

=head2 ilogb

  sub ilogb : int ($x : double)

ilogb function defined in C language math.h.

=head2 ilogbf

  sub ilogbf : int ($x : float)

ilogbf function defined in C language math.h.

=head2 INFINITY

  sub INFINITY : double ()

INFINITY macro defined in C language math.h. This method returns a double value.

=head2 INFINITYF

  sub INFINITYF : float ()

INFINITY macro for float type defined in C language math.h. This method returns a float value.

=head2 isfinite

  sub isfinite : int ($x : double)

isfinite macro defined in C language math.h. This method receives a double value.

=head2 isfinitef

  sub isfinitef : int($x : float)

isfinite macro defined in C language math.h for float type. This method receives a float value.

=head2 isgreater

  sub isgreater : int ($x1 : double, $x2 : double)

isgreater macro defined in C language math.h. This method receives two double values.

=head2 isgreaterequal

  sub isgreaterequal : int ($x1 : double, $x2 : double)

isgreaterequal macro defined in C language math.h. This method receives two double values.

=head2 isgreaterequalf

  sub isgreaterequalf : int ($x1 : float, $x2 : float)

isgreaterequal macro defined in C language math.h. This method receives two float values.

=head2 isgreaterf

  sub isgreaterf : int ($x1 : float, $x2 : float)

isgreater macro defined in C language math.h. This method receives two float values.

=head2 isinf

  sub isinf : int ($x : double)

isinf macro defined in C language math.h. This method receives a double value.

=head2 isinff

  sub isinff : int($x : float)

isinf macro defined in C language math.h. This method receives a float value.

=head2 isless

  sub isless : int ($x1 : double, $x2 : double)

isless macro defined in C language math.h. This method receives two double values.

=head2 islessequal

  sub islessequal : int ($x1 : double, $x2 : double)

islessequal macro defined in C language math.h. This method receives two double values.

=head2 islessequalf

  sub islessequalf : int ($x1 : float, $x2 : float)

islessequalf macro defined in C language math.h. This method receives two float values.

=head2 islessf

  sub islessf : int ($x1 : float, $x2 : float)

islessf macro defined in C language math.h. This method receives two float values.

=head2 islessgreater

  sub islessgreater : int ($x1 : double, $x2 : double)

islessgreater macro defined in C language math.h. This method receives two double values.

=head2 islessgreaterf

  sub islessgreaterf : int ($x1 : float, $x2 : float)

islessgreater macro defined in C language math.h. This method receives two float values.

=head2 isnan

  sub isnan : int ($x : double)

isnan macro defined in C language math.h. This method receives a double value.

=head2 isnanf

  sub isnanf : int ($x : float)

isnanf macro defined in C language math.h. This method receives a float value.

=head2 isunordered

  sub isunordered : int ($x1 : double, $x2 : double)

isunordered macro defined in C language math.h. This method receives two double values.

=head2 isunorderedf

  sub isunorderedf : int ($x1 : float, $x2 : float)

isunorderedf macro defined in C language math.h. This method receives two float values.

=head2 labs

  sub labs : long ($x : long);

Get the abusolute value of a long value.

=head2 ldexp

  sub ldexp : double ($x : double, $exp : int)

ldexp function defined in C language math.h.

=head2 ldexpf

  sub ldexpf : float ($x : float, $exp : int)

ldexpf function defined in C language math.h.

=head2 lgamma

  sub lgamma : double ($x : double)

lgamma function defined in C language math.h.

=head2 lgammaf

  sub lgammaf : float ($x : float)

lgammaf function defined in C language math.h.

=head2 log

  sub log : double ($x : double)

log function defined in C language math.h.

=head2 log10

  sub log10 : double ($x : double)

log10 function defined in C language math.h.

=head2 log10f

  sub log10f : float ($x : float)

log10f function defined in C language math.h.

=head2 log1p

  sub log1p : double ($x : double)

log1p function defined in C language math.h.

=head2 log1pf

  sub log1pf : float ($x : float)

log1pf function defined in C language math.h.

=head2 log2

  sub log2 : double ($x : double)

log2 function defined in C language math.h.

=head2 log2f

  sub log2f : float ($x : float)

log2f function defined in C language math.h.

=head2 logb

  sub logb : double ($x : double)

logb function defined in C language math.h.

=head2 logbf

  sub logbf : float ($x : float)

logbf function defined in C language math.h.

=head2 logf

  sub logf : float ($x : float)

logf function defined in C language math.h.

=head2 lround

  sub lround : long ($x : double)

llround function defined in C language math.h. Note that call llround instead of lround in C level.

=head2 lroundf

  sub lroundf : long ($x : float)

llroundf function defined in C language math.h. Note that call llroundf instead of lroundf in C level.

=head2 modf

  sub modf : double ($x : double, $intpart : double&)

modf function defined in C language math.h.

=head2 modff

  sub modff : float ($x : float, $intpart : float&)

modff function defined in C language math.h.

=head2 NAN

  sub NAN : double ()

NAN macro defined in C language math.h. This method return a double value.

=head2 nan

  sub nan : double ($str : string)

nan function defined in C language math.h.

String must be defined, otherwise a exception occurs.

=head2 NANF

  sub NANF : float ()

NAN macro defined in C language math.h. This method return a float value.

=head2 nanf

  sub nanf : float ($str : string)

nanf function defined in C language math.h.

String must be defined, otherwise a exception occurs.

=head2 nearbyint

  sub nearbyint : double ($x : double)

nearbyint function defined in C language math.h.

=head2 nearbyintf

  sub nearbyintf : float ($x : float)

nearbyintf function defined in C language math.h.

=head2 nextafter

  sub nextafter : double ($x1 : double, $x2 : double)

nextafter function defined in C language math.h.

=head2 nextafterf

  sub nextafterf : float ($x1 : float, $x2 : float)

nextafterf function defined in C language math.h.

=head2 nexttoward

  sub nexttoward : double ($x1 : double, $x2 : double)

nexttoward function defined in C language math.h.

=head2 nexttowardf

  sub nexttowardf : float ($x1 : float, $x2 : double)

nexttowardf function defined in C language math.h.

=head2 PI

  sub PI : double ()

pi. This value is 0x1.921fb54442d18p+1.

=head2 pow

  sub pow : double ($x : double, $y : double)

pow function defined in C language math.h.

=head2 powf

  sub powf : float ($x : float, $y : float)

powf function defined in C language math.h.

=head2 remainder

  sub remainder : double ($x1 : double, $x2 : double)

remainder function defined in C language math.h.

=head2 remainderf

  sub remainderf : float ($x1 : float, $x2 : float)

remainderf function defined in C language math.h.

=head2 remquo

  sub remquo : double ($x1 : double, $x2 : double, $quo : int&)

remquo function defined in C language math.h.

=head2 remquof

  sub remquof : float ($x1 : float, $x2 : float, $quo : int&)

remquof function defined in C language math.h.

=head2 round

  sub round : double ($x : double)

round function defined in C language math.h.

=head2 roundf

  sub roundf : float ($x : float)

roundf function defined in C language math.h.

=head2 scalbln

  sub scalbln : double ($x : double, $exp : long)

scalbln function defined in C language math.h.

=head2 scalblnf

  sub scalblnf : float ($x : float, $exp : long)

scalblnf function defined in C language math.h.

=head2 scalbn

  sub scalbn : double ($x : double, $exp : int)

scalbn function defined in C language math.h.

=head2 scalbnf

  sub scalbnf : float ($x : float, $exp : int)

scalbnf function defined in C language math.h.

=head2 signbit

  sub signbit : int ($x : double)

signbit function defined in C language math.h.

=head2 signbitf

  sub signbitf : int ($x : float)

signbitf function defined in C language math.h.

=head2 sin

  sub sin : double ($x : double)

sin function defined in C language math.h.

=head2 sinf

  sub sinf : float ($x : float)

sinf function defined in C language math.h.

=head2 sinh

  sub sinh : double ($x : double)

sinh function defined in C language math.h.

=head2 sinhf

  sub sinhf : float ($x : float)

sinhf function defined in C language math.h.

=head2 sqrt

  sub sqrt : double ($x : double)

sqrt function defined in C language math.h.

=head2 sqrtf

sqrtf function defined in C language math.h.

=head2 tan

  sub tan : double ($x : double)

tan function defined in C language math.h.

=head2 tanf

  sub tanf : float ($x : float)

tanf function defined in C language math.h.

=head2 tanh

  sub tanh : double ($x : double)

tanh function defined in C language math.h.

=head2 tanhf

  sub tanhf : float ($x : float)

tanhf function defined in C language math.h.

=head2 tgamma

  sub tgamma : double ($x : double)

tgamma function defined in C language math.h.

=head2 tgammaf

  sub tgammaf : float ($x : float)

tgammaf function defined in C language math.h.

=head2 trunc

  sub trunc : double ($x : double)

trunc function defined in C language math.h.

=head2 truncf

  sub truncf : float ($x : float)

truncf function defined in C language math.h.
