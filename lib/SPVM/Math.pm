package SPVM::Math;

1;

=head1 NAME

SPVM::Math - Math in SPVM | Math functions

=head1 SYNOPSYS

  use Math;
  
  my $sin = Math->sin(Math->PI / 4);
  
=head1 DESCRIPTION

L<Math|Math> defines mathmatical functions. 

=head1 CLASS METHODS

=head2 abs

  static method abs : int ($x : int);

Get the abusolute value of a int value.

=head2 acos

  static method acos : double ($x : double)

acos function defined in C language math.h.

=head2 acosf

  static method acosf : float ($x : float)

acosf function defined in C language math.h.

=head2 acosh

  static method acosh : double ($x : double)

acosh function defined in C language math.h.

=head2 acoshf

  static method acoshf : float ($x : float)

acoshf function defined in C language math.h.

=head2 asin

  static method asin : double ($x : double)

asin function defined in C language math.h.

=head2 asinf

  static method asinf : float ($x : float)

asinf function defined in C language math.h.

=head2 asinh

  static method asinh : double ($x : double)

asinh function defined in C language math.h.

=head2 asinhf

  static method asinhf : float ($x : float)

asinhf function defined in C language math.h.

=head2 atan

  static method atan : double ($x : double)

atan function defined in C language math.h.

=head2 atan2

  static method atan2 : double ($y : double, $x : double)

atan2 function defined in C language math.h.

=head2 atanf

  static method atanf : float ($x : float)

atanf function defined in C language math.h.

=head2 atanh

  static method atanh : double ($x : double)

atanh function defined in C language math.h.

=head2 atanhf

  static method atanhf : float ($x : float)

atanhf function defined in C language math.h.

=head2 cabs

  static method cabs : double ($z : Complex_2d)

cabs function defined in C language complex.h.

=head2 cabsf

  static method cabsf : float ($z : Complex_2f)

cabsf function defined in C language complex.h.

=head2 cacos

  static method cacos : Complex_2d ($z : Complex_2d)

cacos function defined in C language complex.h.

=head2 cacosf

  static method cacosf : Complex_2f ($z : Complex_2f)

cacosf function defined in C language complex.h.

=head2 cacosh

  static method cacosh : Complex_2d ($z : Complex_2d)

cacosh function defined in C language complex.h.

=head2 cacoshf

  static method cacoshf : Complex_2f ($z : Complex_2f)

cacoshf function defined in C language complex.h.

=head2 cadd

  static method cadd : Complex_2d ($z1 : Complex_2d, $z2 : Complex_2d)

cadd function defined in C language complex.h.

=head2 caddf

  static method caddf : Complex_2f ($z1 : Complex_2f, $z2 : Complex_2f)

caddf function defined in C language complex.h.

=head2 carg

  static method carg : double ($z : Complex_2d)

carg function defined in C language complex.h.

=head2 cargf

  static method cargf : float ($z : Complex_2f)

cargf function defined in C language complex.h.

=head2 casin

  static method casin : Complex_2d ($z : Complex_2d)

casin function defined in C language complex.h.

=head2 casinf

  static method casinf : Complex_2f ($z : Complex_2f)

casinf function defined in C language complex.h.

=head2 casinh

  static method casinh : Complex_2d ($z : Complex_2d)

casinh function defined in C language complex.h.

=head2 casinhf

  static method casinhf : Complex_2f ($z : Complex_2f)

casinhf function defined in C language complex.h.

=head2 catan

  static method catan : Complex_2d ($z : Complex_2d)

catan function defined in C language complex.h.

=head2 catanf

  static method catanf : Complex_2f ($z : Complex_2f)

catanf function defined in C language complex.h.

=head2 catanh

  static method catanh : Complex_2d ($z : Complex_2d)

catanh function defined in C language complex.h.

=head2 catanhf

  static method catanhf : Complex_2f ($z : Complex_2f)

catanhf function defined in C language complex.h.

=head2 cbrt

  static method cbrt : double ($x : double)

cbrt function defined in C language math.h.

=head2 cbrtf

  static method cbrtf : float ($x : float)

cbrtf function defined in C language math.h.

=head2 ccos

  static method ccos : Complex_2d ($z : Complex_2d)

ccos function defined in C language complex.h.

=head2 ccosf

  static method ccosf : Complex_2f ($z : Complex_2f)

ccosf function defined in C language complex.h.

=head2 ccosh

  static method ccosh : Complex_2d ($z : Complex_2d)

ccosh function defined in C language complex.h.

=head2 ccoshf

  static method ccoshf : Complex_2f ($z : Complex_2f)

ccoshf function defined in C language complex.h.

=head2 cdiv

  static method cdiv : Complex_2d ($z1 : Complex_2d, $z2 : Complex_2d)

double complex division.

=head2 cdivf

  static method cdivf : Complex_2f ($z1 : Complex_2f, $z2 : Complex_2f)

float complex division.

=head2 ceil

  static method ceil : double ($x : double)

ceil function defined in C language math.h.

=head2 ceilf

  static method ceilf : float ($x : float)

ceilf function defined in C language math.h.

=head2 cexp

  static method cexp : Complex_2d ($z : Complex_2d)

cexp function defined in C language complex.h.

=head2 cexpf

  static method cexpf : Complex_2f ($z : Complex_2f)

cexpf function defined in C language complex.h.

=head2 clog

  static method clog : Complex_2d ($z : Complex_2d)

clog function defined in C language complex.h.

=head2 clogf

  static method clogf : Complex_2f ($z : Complex_2f)

clogf function defined in C language complex.h.

=head2 cmul

  static method cmul : Complex_2d ($z1 : Complex_2d, $z2 : Complex_2d)

double complex multiplication.

=head2 cmulf

  static method cmulf : Complex_2f ($z1 : Complex_2f, $z2 : Complex_2f)

float complex multiplication.

=head2 complex

  static method complex : Complex_2d ($x : double, $y : double)

Create double complex value. This value is defined in L<Complex_2d|SPVM::Complex_2d>.

=head2 complexf

  static method complexf : Complex_2f ($x : float, $y : float)

Create float complex value. This value is defined in L<Complex_2f|SPVM::Complex_2f>.

=head2 conj

  static method conj : Complex_2d ($z : Complex_2d)

conj function defined in C language complex.h.

=head2 conjf

  static method conjf : Complex_2f ($z : Complex_2f)

conjf function defined in C language complex.h.

=head2 copysign

  static method copysign : double ($x1 : double, $x2 : double)

copysign function defined in C language math.h.

=head2 copysignf

  static method copysignf : float ($x1 : float, $x2 : float)

copysignf function defined in C language math.h.

=head2 cos

  static method cos : double ($x : double)

cos function defined in C language math.h.

=head2 cosf

  static method cosf : float ($x : float)

cosf function defined in C language math.h.

=head2 cosh

  static method cosh : double ($x : double)

cosh function defined in C language math.h.

=head2 coshf

  static method coshf : float ($x : float)

coshf function defined in C language math.h.

=head2 cpow

  static method cpow : Complex_2d ($z1 : Complex_2d, $z2 : Complex_2d)

cpow function defined in C language complex.h.

=head2 cpowf

  static method cpowf : Complex_2f ($z1 : Complex_2f, $z2 : Complex_2f)

cpowf function defined in C language complex.h.

=head2 cscamul

  static method cscamul : Complex_2d ($c : double, $z : Complex_2d)

double complex scalar multiplication.

=head2 cscamulf

  static method cscamulf : Complex_2f ($c : float, $z : Complex_2f)

float complex scalar multiplication.

=head2 csin

  static method csin : Complex_2d ($z : Complex_2d)

csin function defined in C language complex.h.

=head2 csinf

  static method csinf : Complex_2f ($z : Complex_2f)

csinf function defined in C language complex.h.

=head2 csinh

  static method csinh : Complex_2d ($z : Complex_2d)

csinh function defined in C language complex.h.

=head2 csinhf

  static method csinhf : Complex_2f ($z : Complex_2f)

csinhf function defined in C language complex.h.

=head2 csqrt

  static method csqrt : Complex_2d ($z : Complex_2d)

csqrt function defined in C language complex.h.

=head2 csqrtf

  static method csqrtf : Complex_2f ($z : Complex_2f)

csqrtf function defined in C language complex.h.

=head2 csub

  static method csub : Complex_2d ($z1 : Complex_2d, $z2 : Complex_2d)

csub function defined in C language complex.h.

=head2 csubf

  static method csubf : Complex_2f ($z1 : Complex_2f, $z2 : Complex_2f)

csubf function defined in C language complex.h.

=head2 ctan

  static method ctan : Complex_2d ($z : Complex_2d)

ctan function defined in C language complex.h.

=head2 ctanf

  static method ctanf : Complex_2f ($z : Complex_2f)

ctanf function defined in C language complex.h.

=head2 ctanh

  static method ctanh : Complex_2d ($z : Complex_2d)

ctanh function defined in C language complex.h.

=head2 ctanhf

  static method ctanhf : Complex_2f ($z : Complex_2f)

ctanhf function defined in C language complex.h.

=head2 E

  static method E : double ()

Euler’s Number e. This value is 0x1.5bf0a8b145769p+1.

=head2 erf

  static method erf : double ($x : double)

erf function defined in C language math.h.

=head2 erfc

  static method erfc : double ($x : double)

erfc function defined in C language math.h.

=head2 erfcf

  static method erfcf : float ($x : float)

erfcf function defined in C language math.h.

=head2 erff

  static method erff : float ($x : float)

erff function defined in C language math.h.

=head2 exp

  static method exp : double ($x : double)

exp function defined in C language math.h.

=head2 exp2

  static method exp2 : double ($x : double)

exp2 function defined in C language math.h.

=head2 exp2f

  static method exp2f : float ($x : float)

exp2f function defined in C language math.h.

=head2 expf

  static method expf : float ($x : float)

expf function defined in C language math.h.

=head2 expm1

  static method expm1 : double ($x : double)

expm1 function defined in C language math.h.

=head2 expm1f

  static method expm1f : float ($x : float)

expm1f function defined in C language math.h.

=head2 fabs

  static method fabs : double ($x : double)

fabs function defined in C language math.h.

=head2 fabsf

  static method fabsf : float ($x : float)

fabsf function defined in C language math.h.

=head2 fdim

  static method fdim : double ($x1 : double, $x2 : double)

fdim function defined in C language math.h.

=head2 fdimf

  static method fdimf : float ($x1 : float, $x2 : float)

fdimf function defined in C language math.h.

=head2 FE_DOWNWARD

  static method FE_DOWNWARD : int ()

FE_DOWNWARD macro defined in C language fenv.h.

=head2 FE_TONEAREST

  static method FE_TONEAREST : int ()

FE_TONEAREST macro defined in C language fenv.h.

=head2 FE_TOWARDZERO

  static method FE_TOWARDZERO : int ()

FE_TOWARDZERO macro defined in C language fenv.h.

=head2 FE_UPWARD

  static method FE_UPWARD : int ()

FE_UPWARD macro defined in C language fenv.h.

=head2 fesetround

  static method fesetround : int ($round : int)

fesetround function defined in C language math.h.

=head2 floor

  static method floor : double ($x : double)

floor function defined in C language math.h.

=head2 floorf

  static method floorf : float ($x : float)

floorf function defined in C language math.h.

=head2 fma

  static method fma : double ($x1 : double, $x2 : double, $x3 : double)

fma function defined in C language math.h.

=head2 fmaf

  static method fmaf : float ($x1 : float, $x2 : float, $x3 : float)

fmaf function defined in C language math.h.

=head2 fmax

  static method fmax : double ($x1 : double, $x2 : double)

fmax function defined in C language math.h.

=head2 fmaxf

  static method fmaxf : float ($x1 : float, $x2 : float)

fmaxf function defined in C language math.h.

=head2 fmin

  static method fmin : double ($x1 : double, $x2 : double)

fmin function defined in C language math.h.

=head2 fminf

  static method fminf : float ($x1 : float, $x2 : float)

fminf function defined in C language math.h.

=head2 fmod

  static method fmod : double ($x1 : double, $x2 : double)

fmod function defined in C language math.h.

=head2 fmodf

  static method fmodf : float ($x1 : float, $x2 : float)

fmodf function defined in C language math.h.

=head2 FP_ILOGB0

  static method FP_ILOGB0 : int ()

FP_ILOGB0 macro defined in C language fenv.h.

=head2 FP_ILOGBNAN

  static method FP_ILOGBNAN : int ()

FP_ILOGBNAN macro defined in C language fenv.h.

=head2 FP_INFINITE

  static method FP_INFINITE : int ()

FP_INFINITE macro defined in C language fenv.h.

=head2 FP_NAN

  static method FP_NAN : int ()

FP_NAN macro defined in C language fenv.h.

=head2 FP_ZERO

  static method FP_ZERO : int ()

FP_ZERO macro defined in C language fenv.h.

=head2 fpclassify

  static method fpclassify : int ($x : double)

fpclassify macro defined in C language math.h. This method receives a double value.

=head2 fpclassifyf

  static method fpclassifyf : int ($x : float)

fpclassify macro defined in C language math.h for float type. This method receives a float value.

=head2 frexp

  static method frexp : double ($x : double, $exp : int&)

frexp function defined in C language math.h.

=head2 frexpf

  static method frexpf : float ($x : float, $exp : int&)

frexpf function defined in C language math.h.

=head2 HUGE_VAL

  static method HUGE_VAL : double ()

HUGE_VAL macro defined in C language math.h.

=head2 HUGE_VALF

  static method HUGE_VALF : float ()

HUGE_VALF macro defined in C language math.h.

=head2 hypot

  static method hypot : double ($x : double, $y : double)

hypot function defined in C language math.h.

=head2 hypotf

  static method hypotf : float ($x : float, $y : float)

hypotf function defined in C language math.h.

=head2 ilogb

  static method ilogb : int ($x : double)

ilogb function defined in C language math.h.

=head2 ilogbf

  static method ilogbf : int ($x : float)

ilogbf function defined in C language math.h.

=head2 INFINITY

  static method INFINITY : double ()

INFINITY macro defined in C language math.h. This method returns a double value.

=head2 INFINITYF

  static method INFINITYF : float ()

INFINITY macro for float type defined in C language math.h. This method returns a float value.

=head2 isfinite

  static method isfinite : int ($x : double)

isfinite macro defined in C language math.h. This method receives a double value.

=head2 isfinitef

  static method isfinitef : int($x : float)

isfinite macro defined in C language math.h for float type. This method receives a float value.

=head2 isgreater

  static method isgreater : int ($x1 : double, $x2 : double)

isgreater macro defined in C language math.h. This method receives two double values.

=head2 isgreaterequal

  static method isgreaterequal : int ($x1 : double, $x2 : double)

isgreaterequal macro defined in C language math.h. This method receives two double values.

=head2 isgreaterequalf

  static method isgreaterequalf : int ($x1 : float, $x2 : float)

isgreaterequal macro defined in C language math.h. This method receives two float values.

=head2 isgreaterf

  static method isgreaterf : int ($x1 : float, $x2 : float)

isgreater macro defined in C language math.h. This method receives two float values.

=head2 isinf

  static method isinf : int ($x : double)

isinf macro defined in C language math.h. This method receives a double value.

=head2 isinff

  static method isinff : int($x : float)

isinf macro defined in C language math.h. This method receives a float value.

=head2 isless

  static method isless : int ($x1 : double, $x2 : double)

isless macro defined in C language math.h. This method receives two double values.

=head2 islessequal

  static method islessequal : int ($x1 : double, $x2 : double)

islessequal macro defined in C language math.h. This method receives two double values.

=head2 islessequalf

  static method islessequalf : int ($x1 : float, $x2 : float)

islessequalf macro defined in C language math.h. This method receives two float values.

=head2 islessf

  static method islessf : int ($x1 : float, $x2 : float)

islessf macro defined in C language math.h. This method receives two float values.

=head2 islessgreater

  static method islessgreater : int ($x1 : double, $x2 : double)

islessgreater macro defined in C language math.h. This method receives two double values.

=head2 islessgreaterf

  static method islessgreaterf : int ($x1 : float, $x2 : float)

islessgreater macro defined in C language math.h. This method receives two float values.

=head2 isnan

  static method isnan : int ($x : double)

isnan macro defined in C language math.h. This method receives a double value.

=head2 isnanf

  static method isnanf : int ($x : float)

isnanf macro defined in C language math.h. This method receives a float value.

=head2 isunordered

  static method isunordered : int ($x1 : double, $x2 : double)

isunordered macro defined in C language math.h. This method receives two double values.

=head2 isunorderedf

  static method isunorderedf : int ($x1 : float, $x2 : float)

isunorderedf macro defined in C language math.h. This method receives two float values.

=head2 labs

  static method labs : long ($x : long);

Get the abusolute value of a long value.

=head2 ldexp

  static method ldexp : double ($x : double, $exp : int)

ldexp function defined in C language math.h.

=head2 ldexpf

  static method ldexpf : float ($x : float, $exp : int)

ldexpf function defined in C language math.h.

=head2 lgamma

  static method lgamma : double ($x : double)

lgamma function defined in C language math.h.

=head2 lgammaf

  static method lgammaf : float ($x : float)

lgammaf function defined in C language math.h.

=head2 log

  static method log : double ($x : double)

log function defined in C language math.h.

=head2 log10

  static method log10 : double ($x : double)

log10 function defined in C language math.h.

=head2 log10f

  static method log10f : float ($x : float)

log10f function defined in C language math.h.

=head2 log1p

  static method log1p : double ($x : double)

log1p function defined in C language math.h.

=head2 log1pf

  static method log1pf : float ($x : float)

log1pf function defined in C language math.h.

=head2 log2

  static method log2 : double ($x : double)

log2 function defined in C language math.h.

=head2 log2f

  static method log2f : float ($x : float)

log2f function defined in C language math.h.

=head2 logb

  static method logb : double ($x : double)

logb function defined in C language math.h.

=head2 logbf

  static method logbf : float ($x : float)

logbf function defined in C language math.h.

=head2 logf

  static method logf : float ($x : float)

logf function defined in C language math.h.

=head2 lround

  static method lround : long ($x : double)

llround function defined in C language math.h. Note that call llround instead of lround in C level.

=head2 lroundf

  static method lroundf : long ($x : float)

llroundf function defined in C language math.h. Note that call llroundf instead of lroundf in C level.

=head2 modf

  static method modf : double ($x : double, $intpart : double&)

modf function defined in C language math.h.

=head2 modff

  static method modff : float ($x : float, $intpart : float&)

modff function defined in C language math.h.

=head2 NAN

  static method NAN : double ()

NAN macro defined in C language math.h. This method return a double value.

=head2 nan

  static method nan : double ($str : string)

nan function defined in C language math.h.

String must be defined, otherwise a exception occurs.

=head2 NANF

  static method NANF : float ()

NAN macro defined in C language math.h. This method return a float value.

=head2 nanf

  static method nanf : float ($str : string)

nanf function defined in C language math.h.

String must be defined, otherwise a exception occurs.

=head2 nearbyint

  static method nearbyint : double ($x : double)

nearbyint function defined in C language math.h.

=head2 nearbyintf

  static method nearbyintf : float ($x : float)

nearbyintf function defined in C language math.h.

=head2 nextafter

  static method nextafter : double ($x1 : double, $x2 : double)

nextafter function defined in C language math.h.

=head2 nextafterf

  static method nextafterf : float ($x1 : float, $x2 : float)

nextafterf function defined in C language math.h.

=head2 nexttoward

  static method nexttoward : double ($x1 : double, $x2 : double)

nexttoward function defined in C language math.h.

=head2 nexttowardf

  static method nexttowardf : float ($x1 : float, $x2 : double)

nexttowardf function defined in C language math.h.

=head2 PI

  static method PI : double ()

pi. This value is 0x1.921fb54442d18p+1.

=head2 pow

  static method pow : double ($x : double, $y : double)

pow function defined in C language math.h.

=head2 powf

  static method powf : float ($x : float, $y : float)

powf function defined in C language math.h.

=head2 remainder

  static method remainder : double ($x1 : double, $x2 : double)

remainder function defined in C language math.h.

=head2 remainderf

  static method remainderf : float ($x1 : float, $x2 : float)

remainderf function defined in C language math.h.

=head2 remquo

  static method remquo : double ($x1 : double, $x2 : double, $quo : int&)

remquo function defined in C language math.h.

=head2 remquof

  static method remquof : float ($x1 : float, $x2 : float, $quo : int&)

remquof function defined in C language math.h.

=head2 round

  static method round : double ($x : double)

round function defined in C language math.h.

=head2 roundf

  static method roundf : float ($x : float)

roundf function defined in C language math.h.

=head2 scalbln

  static method scalbln : double ($x : double, $exp : long)

scalbln function defined in C language math.h.

=head2 scalblnf

  static method scalblnf : float ($x : float, $exp : long)

scalblnf function defined in C language math.h.

=head2 scalbn

  static method scalbn : double ($x : double, $exp : int)

scalbn function defined in C language math.h.

=head2 scalbnf

  static method scalbnf : float ($x : float, $exp : int)

scalbnf function defined in C language math.h.

=head2 signbit

  static method signbit : int ($x : double)

signbit function defined in C language math.h.

=head2 signbitf

  static method signbitf : int ($x : float)

signbitf function defined in C language math.h.

=head2 sin

  static method sin : double ($x : double)

sin function defined in C language math.h.

=head2 sinf

  static method sinf : float ($x : float)

sinf function defined in C language math.h.

=head2 sinh

  static method sinh : double ($x : double)

sinh function defined in C language math.h.

=head2 sinhf

  static method sinhf : float ($x : float)

sinhf function defined in C language math.h.

=head2 sqrt

  static method sqrt : double ($x : double)

sqrt function defined in C language math.h.

=head2 sqrtf

sqrtf function defined in C language math.h.

=head2 tan

  static method tan : double ($x : double)

tan function defined in C language math.h.

=head2 tanf

  static method tanf : float ($x : float)

tanf function defined in C language math.h.

=head2 tanh

  static method tanh : double ($x : double)

tanh function defined in C language math.h.

=head2 tanhf

  static method tanhf : float ($x : float)

tanhf function defined in C language math.h.

=head2 tgamma

  static method tgamma : double ($x : double)

tgamma function defined in C language math.h.

=head2 tgammaf

  static method tgammaf : float ($x : float)

tgammaf function defined in C language math.h.

=head2 trunc

  static method trunc : double ($x : double)

trunc function defined in C language math.h.

=head2 truncf

  static method truncf : float ($x : float)

truncf function defined in C language math.h.
