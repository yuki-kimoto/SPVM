#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>
#include <stdlib.h>

#include "spvm_api.h"

double SPVM__Math__sin(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = sin(args[0].double_value);
  
  return value;
}

double SPVM__Math__cos(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = cos(args[0].double_value);
  
  return value;
}

double SPVM__Math__tan(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = tan(args[0].double_value);
  
  return value;
}

double SPVM__Math__asin(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = asin(args[0].double_value);
  
  return value;
}

double SPVM__Math__acos(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = acos(args[0].double_value);
  
  return value;
}

double SPVM__Math__atan(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = atan(args[0].double_value);
  
  return value;
}

double SPVM__Math__to_radians(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = args[0].double_value * M_PI / 180.0;
  
  return value;
}

double SPVM__Math__to_degrees(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = args[0].double_value * 180.0 / M_PI;
  
  return value;
}

double SPVM__Math__exp(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = exp(args[0].double_value);
  
  return value;
}

double SPVM__Math__log(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = log(args[0].double_value);
  
  return value;
}

double SPVM__Math__log10(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = log10(args[0].double_value);
  
  return value;
}

double SPVM__Math__sqrt(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = sqrt(args[0].double_value);
  
  return value;
}

double SPVM__Math__cbrt(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = cbrt(args[0].double_value);
  
  return value;
}

double SPVM__Math__ceil(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = ceil(args[0].double_value);
  
  return value;
}

double SPVM__Math__IEEE_remainder(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  // x - Math.Round(x / y) * y
  double value = args[0].double_value - round(args[0].double_value / args[1].double_value) * args[1].double_value;

  return value;
}

double SPVM__Math__floor(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = floor(args[0].double_value);
  
  return value;
}

double SPVM__Math__rint(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = rint(args[0].double_value);
  
  return value;
}

double SPVM__Math__atan2(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = atan2(args[0].double_value, args[1].double_value);
  
  return value;
}

double SPVM__Math__pow(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = pow(args[0].double_value, args[1].double_value);
  
  return value;
}

double SPVM__Math__round(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = round(args[0].double_value);
  
  return value;
}

int32_t SPVM__Math__abs(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int32_t value = (int32_t)labs((long)args[0].int_value);
  
  return value;
}

int64_t SPVM__Math__abs_long(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int64_t value = (int64_t)labs((long long)args[0].long_value);
  
  return value;
}

float SPVM__Math__abs_float(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  float value = fabsf(args[0].float_value);
  
  return value;
}
