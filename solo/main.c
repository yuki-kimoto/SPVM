#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

#include "spvm_compiler.h"
#include "spvm_hash.h"
#include "spvm_list.h"
#include "spvm_runtime.h"
#include "spvm_op.h"
#include "spvm_sub.h"
#include "spvm_util_allocator.h"
#include "spvm_runtime_sub.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_package.h"
#include "spvm_runtime_sub.h"
#include "spvm_runtime_api.h"
#include "spvm_portable.h"

#include <spvm_native.h>

int32_t SPVM_NATIVE_SPVM__CORE__cadd(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__print(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__acos(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__asin(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__atan(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__atan2(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__acosh(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__asinh(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__atanh(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__abs(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__cos(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__cosh(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__cbrt(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__ceil(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__exp(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__exp2(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__expm1(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__erf(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__erfc(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__fabs(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__floor(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__hypot(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__isinff(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__isfinitef(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__isnanf(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__isinf(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__isfinite(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__isnan(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__log(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__log10(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__log1p(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__labs(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__lgamma(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__nearbyint(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__pow(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__round(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__remainder(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__sin(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__sinh(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__sqrt(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__time(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__tan(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__tanh(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__tgamma(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__warn(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__DBL_MAX(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__DBL_MIN(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__E(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__FLT_MAX(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__FLT_MIN(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__INFINITYF(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__INFINITY(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__INT8_MIN(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__INT8_MAX(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__INT16_MIN(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__INT16_MAX(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__INT32_MIN(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__INT32_MAX(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__INT64_MIN(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__INT64_MAX(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__NANF(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__NAN(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__PI(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__csub(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__csubf(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__cmul(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__cdiv(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__caddf(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__cmulf(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__cdivf(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__new_fcomplex(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPVM_NATIVE_SPVM__CORE__new_dcomplex(SPVM_ENV* env, SPVM_VALUE* stack);

int32_t main(int32_t argc, const char *argv[]) {
  
  // Package name
  const char* package_name = "TestCase";
  
  // Create compiler
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  
  // compiler->debug = 1;
  
  // Create use op for entry point package
  SPVM_OP* op_name_start = SPVM_OP_new_op_name(compiler, package_name, package_name, 0);
  SPVM_OP* op_type_start = SPVM_OP_build_basic_type(compiler, op_name_start);
  SPVM_OP* op_use_start = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, package_name, 0);
  SPVM_OP_build_use(compiler, op_use_start, op_type_start, NULL, 0);
  SPVM_LIST_push(compiler->op_use_stack, op_use_start);
  
  SPVM_LIST_push(compiler->module_include_pathes, "lib");
  SPVM_LIST_push(compiler->module_include_pathes, "solo/lib");
  
  SPVM_COMPILER_compile(compiler);
  
  if (compiler->error_count > 0) {
    exit(1);
  }

  // Build portable info
  SPVM_PORTABLE* portable = SPVM_PORTABLE_build_portable(compiler);
  
  // Create run-time
  SPVM_ENV* env = SPVM_RUNTIME_build_runtime_env(portable);
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Free compiler
  SPVM_COMPILER_free(compiler);

#ifndef SPVM_DONT_USE_CORE_LIB

  // Bind native subroutine
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "cadd";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__cadd;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "csub";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__csub;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "cmul";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__cmul;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "cdiv";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__cdiv;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "caddf";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__caddf;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "csubf";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__csubf;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "cmulf";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__cmulf;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "cdivf";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__cdivf;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "new_fcomplex";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__new_fcomplex;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "new_dcomplex";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__new_dcomplex;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "print";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__print;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "warn";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__warn;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "time";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__time;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "INFINITYF";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__INFINITYF;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "NANF";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__NANF;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "isinff";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__isinff;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "isfinitef";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__isfinitef;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "isnanf";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__isnanf;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "INFINITY";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__INFINITY;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "NAN";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__NAN;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "isinf";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__isinf;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "isfinite";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__isfinite;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "isnan";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__isnan;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "PI";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__PI;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "E";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__E;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "acos";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__acos;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "asin";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__asin;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "atan";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__atan;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "atan2";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__atan2;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "cos";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__cos;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "sin";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__sin;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "tan";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__tan;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "acosh";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__acosh;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "asinh";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__asinh;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "atanh";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__atanh;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "cosh";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__cosh;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "sinh";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__sinh;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "tanh";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__tanh;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "exp";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__exp;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "exp2";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__exp2;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "expm1";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__expm1;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "log";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__log;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "log10";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__log10;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "log1p";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__log1p;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "abs";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__abs;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "labs";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__labs;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "cbrt";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__cbrt;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "fabs";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__fabs;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "hypot";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__hypot;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "pow";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__pow;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "sqrt";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__sqrt;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "erf";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__erf;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "erfc";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__erfc;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "lgamma";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__lgamma;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "tgamma";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__tgamma;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "ceil";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__ceil;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "floor";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__floor;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "nearbyint";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__nearbyint;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "round";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__round;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "remainder";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__remainder;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "INT8_MIN";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__INT8_MIN;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "INT8_MAX";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__INT8_MAX;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "INT16_MIN";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__INT16_MIN;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "INT16_MAX";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__INT16_MAX;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "INT32_MIN";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__INT32_MIN;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "INT32_MAX";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__INT32_MAX;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "INT64_MIN";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__INT64_MIN;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "INT64_MAX";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__INT64_MAX;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "FLT_MAX";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__FLT_MAX;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "FLT_MIN";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__FLT_MIN;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "DBL_MAX";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__DBL_MAX;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "DBL_MIN";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_get_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_get_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPVM_NATIVE_SPVM__CORE__DBL_MIN;
  }
#endif
  
  // Call begin blocks
  SPVM_RUNTIME_API_call_begin_blocks(env);

  // Call entry point sub
  int32_t status_code = SPVM_RUNTIME_API_call_entry_point_sub(env, package_name, argc, argv);
  
  SPVM_RUNTIME_free_runtime(env);
  
  return status_code;
}

