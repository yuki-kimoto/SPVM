#ifndef SPVM_CORE_FUNC_H
#define SPVM_CORE_FUNC_H

#include "spvm_base.h"
#include "spvm_native.h"

double SPVM_CORE_FUNC_PI(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_E(SPVM_ENV* env, SPVM_VALUE* args);

int64_t SPVM_CORE_FUNC_time(SPVM_ENV* env, SPVM_VALUE* args);
void SPVM_CORE_FUNC_print(SPVM_ENV* env, SPVM_VALUE* args);
void SPVM_CORE_FUNC_warn(SPVM_ENV* env, SPVM_VALUE* args);

int32_t SPVM_CORE_FUNC_isinff(SPVM_ENV* env, SPVM_VALUE* args);
int32_t SPVM_CORE_FUNC_isfinitef(SPVM_ENV* env, SPVM_VALUE* args);
int32_t SPVM_CORE_FUNC_isnanf(SPVM_ENV* env, SPVM_VALUE* args);
float SPVM_CORE_FUNC_INFINITYF(SPVM_ENV* env, SPVM_VALUE* args);
float SPVM_CORE_FUNC_NANF(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_INFINITY(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_NAN(SPVM_ENV* env, SPVM_VALUE* args);
int32_t SPVM_CORE_FUNC_isinf(SPVM_ENV* env, SPVM_VALUE* args);
int32_t SPVM_CORE_FUNC_isnan(SPVM_ENV* env, SPVM_VALUE* args);
int32_t SPVM_CORE_FUNC_isfinite(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_sin(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_cos(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_tan(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_asin(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_acosh(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_atanh(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_asinh(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_acos(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_atan(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_exp(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_exp2(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_log(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_log10(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_sqrt(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_cbrt(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_ceil(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_remainder(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_floor(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_nearbyint(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_atan2(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_pow(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_round(SPVM_ENV* env, SPVM_VALUE* args);
int32_t SPVM_CORE_FUNC_abs(SPVM_ENV* env, SPVM_VALUE* args);
int64_t SPVM_CORE_FUNC_labs(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_fabs(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_erf(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_erfc(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_lgamma(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_tgamma(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_sinh(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_cosh(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_tanh(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_hypot(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_expm1(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_log1p(SPVM_ENV* env, SPVM_VALUE* args);
float SPVM_CORE_FUNC_FLT_MAX(SPVM_ENV* env, SPVM_VALUE* args);
float SPVM_CORE_FUNC_FLT_MIN(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_DBL_MAX(SPVM_ENV* env, SPVM_VALUE* args);
double SPVM_CORE_FUNC_DBL_MIN(SPVM_ENV* env, SPVM_VALUE* args);

int8_t SPVM_CORE_FUNC_INT8_MIN(SPVM_ENV* env, SPVM_VALUE* args);
int8_t SPVM_CORE_FUNC_INT8_MAX(SPVM_ENV* env, SPVM_VALUE* args);
int16_t SPVM_CORE_FUNC_INT16_MIN(SPVM_ENV* env, SPVM_VALUE* args);
int16_t SPVM_CORE_FUNC_INT16_MAX(SPVM_ENV* env, SPVM_VALUE* args);
int32_t SPVM_CORE_FUNC_INT32_MIN(SPVM_ENV* env, SPVM_VALUE* args);
int32_t SPVM_CORE_FUNC_INT32_MAX(SPVM_ENV* env, SPVM_VALUE* args);
int64_t SPVM_CORE_FUNC_INT64_MIN(SPVM_ENV* env, SPVM_VALUE* args);
int64_t SPVM_CORE_FUNC_INT64_MAX(SPVM_ENV* env, SPVM_VALUE* args);

#endif
