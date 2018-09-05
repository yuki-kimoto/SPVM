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
#include "spvm_runtime_builder.h"
#include "spvm_runtime_package.h"
#include "spvm_runtime_sub.h"
#include "spvm_runtime_api.h"

#include <spvm_native.h>

#include "SPVM/CORE.native/CORE.c"

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
  SPVM_OP_build_use(compiler, op_use_start, op_type_start);
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
  SPVM_ENV* env = SPVM_RUNTIME_BUILDER_build_runtime_env(portable);
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Free compiler
  SPVM_COMPILER_free(compiler);

  // Bind native subroutine
  {
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__print = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::print", strlen("SPVM::CORE::print"));
    runtime->sub_native_addresses[sub_SPVM__CORE__print->id] = SPVM_NATIVE_SPVM__CORE__print;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__acos = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::acos", strlen("SPVM::CORE::acos"));
    runtime->sub_native_addresses[sub_SPVM__CORE__acos->id] = SPVM_NATIVE_SPVM__CORE__acos;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__asin = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::asin", strlen("SPVM::CORE::asin"));
    runtime->sub_native_addresses[sub_SPVM__CORE__asin->id] = SPVM_NATIVE_SPVM__CORE__asin;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__atan = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::atan", strlen("SPVM::CORE::atan"));
    runtime->sub_native_addresses[sub_SPVM__CORE__atan->id] = SPVM_NATIVE_SPVM__CORE__atan;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__atan2 = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::atan2", strlen("SPVM::CORE::atan2"));
    runtime->sub_native_addresses[sub_SPVM__CORE__atan2->id] = SPVM_NATIVE_SPVM__CORE__atan2;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__acosh = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::acosh", strlen("SPVM::CORE::acosh"));
    runtime->sub_native_addresses[sub_SPVM__CORE__acosh->id] = SPVM_NATIVE_SPVM__CORE__acosh;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__asinh = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::asinh", strlen("SPVM::CORE::asinh"));
    runtime->sub_native_addresses[sub_SPVM__CORE__asinh->id] = SPVM_NATIVE_SPVM__CORE__asinh;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__atanh = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::atanh", strlen("SPVM::CORE::atanh"));
    runtime->sub_native_addresses[sub_SPVM__CORE__atanh->id] = SPVM_NATIVE_SPVM__CORE__atanh;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__abs = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::abs", strlen("SPVM::CORE::abs"));
    runtime->sub_native_addresses[sub_SPVM__CORE__abs->id] = SPVM_NATIVE_SPVM__CORE__abs;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__cos = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::cos", strlen("SPVM::CORE::cos"));
    runtime->sub_native_addresses[sub_SPVM__CORE__cos->id] = SPVM_NATIVE_SPVM__CORE__cos;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__cosh = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::cosh", strlen("SPVM::CORE::cosh"));
    runtime->sub_native_addresses[sub_SPVM__CORE__cosh->id] = SPVM_NATIVE_SPVM__CORE__cosh;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__cbrt = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::cbrt", strlen("SPVM::CORE::cbrt"));
    runtime->sub_native_addresses[sub_SPVM__CORE__cbrt->id] = SPVM_NATIVE_SPVM__CORE__cbrt;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__ceil = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::ceil", strlen("SPVM::CORE::ceil"));
    runtime->sub_native_addresses[sub_SPVM__CORE__ceil->id] = SPVM_NATIVE_SPVM__CORE__ceil;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__exp = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::exp", strlen("SPVM::CORE::exp"));
    runtime->sub_native_addresses[sub_SPVM__CORE__exp->id] = SPVM_NATIVE_SPVM__CORE__exp;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__exp2 = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::exp2", strlen("SPVM::CORE::exp2"));
    runtime->sub_native_addresses[sub_SPVM__CORE__exp2->id] = SPVM_NATIVE_SPVM__CORE__exp2;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__expm1 = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::expm1", strlen("SPVM::CORE::expm1"));
    runtime->sub_native_addresses[sub_SPVM__CORE__expm1->id] = SPVM_NATIVE_SPVM__CORE__expm1;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__erf = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::erf", strlen("SPVM::CORE::erf"));
    runtime->sub_native_addresses[sub_SPVM__CORE__erf->id] = SPVM_NATIVE_SPVM__CORE__erf;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__erfc = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::erfc", strlen("SPVM::CORE::erfc"));
    runtime->sub_native_addresses[sub_SPVM__CORE__erfc->id] = SPVM_NATIVE_SPVM__CORE__erfc;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__fabs = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::fabs", strlen("SPVM::CORE::fabs"));
    runtime->sub_native_addresses[sub_SPVM__CORE__fabs->id] = SPVM_NATIVE_SPVM__CORE__fabs;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__floor = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::floor", strlen("SPVM::CORE::floor"));
    runtime->sub_native_addresses[sub_SPVM__CORE__floor->id] = SPVM_NATIVE_SPVM__CORE__floor;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__hypot = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::hypot", strlen("SPVM::CORE::hypot"));
    runtime->sub_native_addresses[sub_SPVM__CORE__hypot->id] = SPVM_NATIVE_SPVM__CORE__hypot;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__isinff = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::isinff", strlen("SPVM::CORE::isinff"));
    runtime->sub_native_addresses[sub_SPVM__CORE__isinff->id] = SPVM_NATIVE_SPVM__CORE__isinff;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__isfinitef = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::isfinitef", strlen("SPVM::CORE::isfinitef"));
    runtime->sub_native_addresses[sub_SPVM__CORE__isfinitef->id] = SPVM_NATIVE_SPVM__CORE__isfinitef;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__isnanf = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::isnanf", strlen("SPVM::CORE::isnanf"));
    runtime->sub_native_addresses[sub_SPVM__CORE__isnanf->id] = SPVM_NATIVE_SPVM__CORE__isnanf;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__isinf = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::isinf", strlen("SPVM::CORE::isinf"));
    runtime->sub_native_addresses[sub_SPVM__CORE__isinf->id] = SPVM_NATIVE_SPVM__CORE__isinf;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__isfinite = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::isfinite", strlen("SPVM::CORE::isfinite"));
    runtime->sub_native_addresses[sub_SPVM__CORE__isfinite->id] = SPVM_NATIVE_SPVM__CORE__isfinite;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__isnan = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::isnan", strlen("SPVM::CORE::isnan"));
    runtime->sub_native_addresses[sub_SPVM__CORE__isnan->id] = SPVM_NATIVE_SPVM__CORE__isnan;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__log = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::log", strlen("SPVM::CORE::log"));
    runtime->sub_native_addresses[sub_SPVM__CORE__log->id] = SPVM_NATIVE_SPVM__CORE__log;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__log10 = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::log10", strlen("SPVM::CORE::log10"));
    runtime->sub_native_addresses[sub_SPVM__CORE__log10->id] = SPVM_NATIVE_SPVM__CORE__log10;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__log1p = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::log1p", strlen("SPVM::CORE::log1p"));
    runtime->sub_native_addresses[sub_SPVM__CORE__log1p->id] = SPVM_NATIVE_SPVM__CORE__log1p;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__labs = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::labs", strlen("SPVM::CORE::labs"));
    runtime->sub_native_addresses[sub_SPVM__CORE__labs->id] = SPVM_NATIVE_SPVM__CORE__labs;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__lgamma = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::lgamma", strlen("SPVM::CORE::lgamma"));
    runtime->sub_native_addresses[sub_SPVM__CORE__lgamma->id] = SPVM_NATIVE_SPVM__CORE__lgamma;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__nearbyint = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::nearbyint", strlen("SPVM::CORE::nearbyint"));
    runtime->sub_native_addresses[sub_SPVM__CORE__nearbyint->id] = SPVM_NATIVE_SPVM__CORE__nearbyint;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__pow = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::pow", strlen("SPVM::CORE::pow"));
    runtime->sub_native_addresses[sub_SPVM__CORE__pow->id] = SPVM_NATIVE_SPVM__CORE__pow;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__round = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::round", strlen("SPVM::CORE::round"));
    runtime->sub_native_addresses[sub_SPVM__CORE__round->id] = SPVM_NATIVE_SPVM__CORE__round;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__remainder = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::remainder", strlen("SPVM::CORE::remainder"));
    runtime->sub_native_addresses[sub_SPVM__CORE__remainder->id] = SPVM_NATIVE_SPVM__CORE__remainder;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__sin = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::sin", strlen("SPVM::CORE::sin"));
    runtime->sub_native_addresses[sub_SPVM__CORE__sin->id] = SPVM_NATIVE_SPVM__CORE__sin;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__sinh = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::sinh", strlen("SPVM::CORE::sinh"));
    runtime->sub_native_addresses[sub_SPVM__CORE__sinh->id] = SPVM_NATIVE_SPVM__CORE__sinh;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__sqrt = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::sqrt", strlen("SPVM::CORE::sqrt"));
    runtime->sub_native_addresses[sub_SPVM__CORE__sqrt->id] = SPVM_NATIVE_SPVM__CORE__sqrt;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__time = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::time", strlen("SPVM::CORE::time"));
    runtime->sub_native_addresses[sub_SPVM__CORE__time->id] = SPVM_NATIVE_SPVM__CORE__time;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__tan = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::tan", strlen("SPVM::CORE::tan"));
    runtime->sub_native_addresses[sub_SPVM__CORE__tan->id] = SPVM_NATIVE_SPVM__CORE__tan;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__tanh = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::tanh", strlen("SPVM::CORE::tanh"));
    runtime->sub_native_addresses[sub_SPVM__CORE__tanh->id] = SPVM_NATIVE_SPVM__CORE__tanh;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__tgamma = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::tgamma", strlen("SPVM::CORE::tgamma"));
    runtime->sub_native_addresses[sub_SPVM__CORE__tgamma->id] = SPVM_NATIVE_SPVM__CORE__tgamma;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__warn = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::warn", strlen("SPVM::CORE::warn"));
    runtime->sub_native_addresses[sub_SPVM__CORE__warn->id] = SPVM_NATIVE_SPVM__CORE__warn;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__DBL_MAX = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::DBL_MAX", strlen("SPVM::CORE::DBL_MAX"));
    runtime->sub_native_addresses[sub_SPVM__CORE__DBL_MAX->id] = SPVM_NATIVE_SPVM__CORE__DBL_MAX;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__DBL_MIN = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::DBL_MIN", strlen("SPVM::CORE::DBL_MIN"));
    runtime->sub_native_addresses[sub_SPVM__CORE__DBL_MIN->id] = SPVM_NATIVE_SPVM__CORE__DBL_MIN;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__E = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::E", strlen("SPVM::CORE::E"));
    runtime->sub_native_addresses[sub_SPVM__CORE__E->id] = SPVM_NATIVE_SPVM__CORE__E;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__FLT_MAX = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::FLT_MAX", strlen("SPVM::CORE::FLT_MAX"));
    runtime->sub_native_addresses[sub_SPVM__CORE__FLT_MAX->id] = SPVM_NATIVE_SPVM__CORE__FLT_MAX;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__FLT_MIN = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::FLT_MIN", strlen("SPVM::CORE::FLT_MIN"));
    runtime->sub_native_addresses[sub_SPVM__CORE__FLT_MIN->id] = SPVM_NATIVE_SPVM__CORE__FLT_MIN;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INFINITYF = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::INFINITYF", strlen("SPVM::CORE::INFINITYF"));
    runtime->sub_native_addresses[sub_SPVM__CORE__INFINITYF->id] = SPVM_NATIVE_SPVM__CORE__INFINITYF;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INFINITY = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::INFINITY", strlen("SPVM::CORE::INFINITY"));
    runtime->sub_native_addresses[sub_SPVM__CORE__INFINITY->id] = SPVM_NATIVE_SPVM__CORE__INFINITY;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INT8_MIN = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::INT8_MIN", strlen("SPVM::CORE::INT8_MIN"));
    runtime->sub_native_addresses[sub_SPVM__CORE__INT8_MIN->id] = SPVM_NATIVE_SPVM__CORE__INT8_MIN;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INT8_MAX = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::INT8_MAX", strlen("SPVM::CORE::INT8_MAX"));
    runtime->sub_native_addresses[sub_SPVM__CORE__INT8_MAX->id] = SPVM_NATIVE_SPVM__CORE__INT8_MAX;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INT16_MIN = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::INT16_MIN", strlen("SPVM::CORE::INT16_MIN"));
    runtime->sub_native_addresses[sub_SPVM__CORE__INT16_MIN->id] = SPVM_NATIVE_SPVM__CORE__INT16_MIN;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INT16_MAX = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::INT16_MAX", strlen("SPVM::CORE::INT16_MAX"));
    runtime->sub_native_addresses[sub_SPVM__CORE__INT16_MAX->id] = SPVM_NATIVE_SPVM__CORE__INT16_MAX;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INT32_MIN = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::INT32_MIN", strlen("SPVM::CORE::INT32_MIN"));
    runtime->sub_native_addresses[sub_SPVM__CORE__INT32_MIN->id] = SPVM_NATIVE_SPVM__CORE__INT32_MIN;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INT32_MAX = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::INT32_MAX", strlen("SPVM::CORE::INT32_MAX"));
    runtime->sub_native_addresses[sub_SPVM__CORE__INT32_MAX->id] = SPVM_NATIVE_SPVM__CORE__INT32_MAX;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INT64_MIN = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::INT64_MIN", strlen("SPVM::CORE::INT64_MIN"));
    runtime->sub_native_addresses[sub_SPVM__CORE__INT64_MIN->id] = SPVM_NATIVE_SPVM__CORE__INT64_MIN;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INT64_MAX = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::INT64_MAX", strlen("SPVM::CORE::INT64_MAX"));
    runtime->sub_native_addresses[sub_SPVM__CORE__INT64_MAX->id] = SPVM_NATIVE_SPVM__CORE__INT64_MAX;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__NANF = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::NANF", strlen("SPVM::CORE::NANF"));
    runtime->sub_native_addresses[sub_SPVM__CORE__NANF->id] = SPVM_NATIVE_SPVM__CORE__NANF;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__NAN = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::NAN", strlen("SPVM::CORE::NAN"));
    runtime->sub_native_addresses[sub_SPVM__CORE__NAN->id] = SPVM_NATIVE_SPVM__CORE__NAN;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__PI = SPVM_HASH_fetch(runtime->sub_symtable, "SPVM::CORE::PI", strlen("SPVM::CORE::PI"));
    runtime->sub_native_addresses[sub_SPVM__CORE__PI->id] = SPVM_NATIVE_SPVM__CORE__PI;
  }
  
  // Call entry point sub
  int32_t status_code = SPVM_RUNTIME_API_call_entry_point_sub(env, package_name, argc, argv);
  
  SPVM_RUNTIME_free(env);
  
  return status_code;
}

