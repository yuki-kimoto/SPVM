#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

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
