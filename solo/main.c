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

#include <spvm_native.h>

#include "SPVM/CORE.native/CORE.c"

int main(int argc, char *argv[]) {
  
  // Package name
  const char* start_package_name = "TestCase";
  
  // Create compiler
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  
  // compiler->debug = 1;
  
  // Create use op for entry point package
  SPVM_OP* op_name_start = SPVM_OP_new_op_name(compiler, start_package_name, start_package_name, 0);
  SPVM_OP* op_type_start = SPVM_OP_build_basic_type(compiler, op_name_start);
  SPVM_OP* op_use_start = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, start_package_name, 0);
  SPVM_OP_build_use(compiler, op_use_start, op_type_start);
  SPVM_LIST_push(compiler->op_use_stack, op_use_start);
  
  // Entry point
  int32_t start_package_name_length = (int32_t)strlen(start_package_name);
  int32_t start_sub_name_length =  (int32_t)(start_package_name_length + 6);
  char* start_sub_name = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(start_sub_name_length + 1);
  strncpy(start_sub_name, start_package_name, start_package_name_length);
  strncpy(start_sub_name + start_package_name_length, "::main", 6);
  start_sub_name[start_sub_name_length] = '\0';

  SPVM_LIST_push(compiler->module_include_pathes, "lib");
  SPVM_LIST_push(compiler->module_include_pathes, "solo/lib");
  
  SPVM_COMPILER_compile(compiler);
  
  if (compiler->error_count > 0) {
    exit(1);
  }
  
  // Create run-time
  SPVM_RUNTIME* runtime = SPVM_COMPILER_new_runtime(compiler);
  
  // Bind native subroutine
  {
    SPVM_SUB* sub_SPVM__CORE__print = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::print", strlen("SPVM::CORE::print"));
    sub_SPVM__CORE__print->native_address = SPVM_NATIVE_SPVM__CORE__print;
    SPVM_SUB* sub_SPVM__CORE__acos = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::acos", strlen("SPVM::CORE::acos"));
    sub_SPVM__CORE__acos->native_address = SPVM_NATIVE_SPVM__CORE__acos;
    SPVM_SUB* sub_SPVM__CORE__asin = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::asin", strlen("SPVM::CORE::asin"));
    sub_SPVM__CORE__asin->native_address = SPVM_NATIVE_SPVM__CORE__asin;
    SPVM_SUB* sub_SPVM__CORE__atan = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::atan", strlen("SPVM::CORE::atan"));
    sub_SPVM__CORE__atan->native_address = SPVM_NATIVE_SPVM__CORE__atan;
    SPVM_SUB* sub_SPVM__CORE__atan2 = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::atan2", strlen("SPVM::CORE::atan2"));
    sub_SPVM__CORE__atan2->native_address = SPVM_NATIVE_SPVM__CORE__atan2;
    SPVM_SUB* sub_SPVM__CORE__acosh = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::acosh", strlen("SPVM::CORE::acosh"));
    sub_SPVM__CORE__acosh->native_address = SPVM_NATIVE_SPVM__CORE__acosh;
    SPVM_SUB* sub_SPVM__CORE__asinh = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::asinh", strlen("SPVM::CORE::asinh"));
    sub_SPVM__CORE__asinh->native_address = SPVM_NATIVE_SPVM__CORE__asinh;
    SPVM_SUB* sub_SPVM__CORE__atanh = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::atanh", strlen("SPVM::CORE::atanh"));
    sub_SPVM__CORE__atanh->native_address = SPVM_NATIVE_SPVM__CORE__atanh;
    SPVM_SUB* sub_SPVM__CORE__abs = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::abs", strlen("SPVM::CORE::abs"));
    sub_SPVM__CORE__abs->native_address = SPVM_NATIVE_SPVM__CORE__abs;
    SPVM_SUB* sub_SPVM__CORE__cos = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::cos", strlen("SPVM::CORE::cos"));
    sub_SPVM__CORE__cos->native_address = SPVM_NATIVE_SPVM__CORE__cos;
    SPVM_SUB* sub_SPVM__CORE__cosh = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::cosh", strlen("SPVM::CORE::cosh"));
    sub_SPVM__CORE__cosh->native_address = SPVM_NATIVE_SPVM__CORE__cosh;
    SPVM_SUB* sub_SPVM__CORE__cbrt = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::cbrt", strlen("SPVM::CORE::cbrt"));
    sub_SPVM__CORE__cbrt->native_address = SPVM_NATIVE_SPVM__CORE__cbrt;
    SPVM_SUB* sub_SPVM__CORE__ceil = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::ceil", strlen("SPVM::CORE::ceil"));
    sub_SPVM__CORE__ceil->native_address = SPVM_NATIVE_SPVM__CORE__ceil;
    SPVM_SUB* sub_SPVM__CORE__exp = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::exp", strlen("SPVM::CORE::exp"));
    sub_SPVM__CORE__exp->native_address = SPVM_NATIVE_SPVM__CORE__exp;
    SPVM_SUB* sub_SPVM__CORE__exp2 = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::exp2", strlen("SPVM::CORE::exp2"));
    sub_SPVM__CORE__exp2->native_address = SPVM_NATIVE_SPVM__CORE__exp2;
    SPVM_SUB* sub_SPVM__CORE__expm1 = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::expm1", strlen("SPVM::CORE::expm1"));
    sub_SPVM__CORE__expm1->native_address = SPVM_NATIVE_SPVM__CORE__expm1;
    SPVM_SUB* sub_SPVM__CORE__erf = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::erf", strlen("SPVM::CORE::erf"));
    sub_SPVM__CORE__erf->native_address = SPVM_NATIVE_SPVM__CORE__erf;
    SPVM_SUB* sub_SPVM__CORE__erfc = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::erfc", strlen("SPVM::CORE::erfc"));
    sub_SPVM__CORE__erfc->native_address = SPVM_NATIVE_SPVM__CORE__erfc;
    SPVM_SUB* sub_SPVM__CORE__fabs = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::fabs", strlen("SPVM::CORE::fabs"));
    sub_SPVM__CORE__fabs->native_address = SPVM_NATIVE_SPVM__CORE__fabs;
    SPVM_SUB* sub_SPVM__CORE__floor = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::floor", strlen("SPVM::CORE::floor"));
    sub_SPVM__CORE__floor->native_address = SPVM_NATIVE_SPVM__CORE__floor;
    SPVM_SUB* sub_SPVM__CORE__hypot = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::hypot", strlen("SPVM::CORE::hypot"));
    sub_SPVM__CORE__hypot->native_address = SPVM_NATIVE_SPVM__CORE__hypot;
    SPVM_SUB* sub_SPVM__CORE__isinff = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::isinff", strlen("SPVM::CORE::isinff"));
    sub_SPVM__CORE__isinff->native_address = SPVM_NATIVE_SPVM__CORE__isinff;
    SPVM_SUB* sub_SPVM__CORE__isfinitef = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::isfinitef", strlen("SPVM::CORE::isfinitef"));
    sub_SPVM__CORE__isfinitef->native_address = SPVM_NATIVE_SPVM__CORE__isfinitef;
    SPVM_SUB* sub_SPVM__CORE__isnanf = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::isnanf", strlen("SPVM::CORE::isnanf"));
    sub_SPVM__CORE__isnanf->native_address = SPVM_NATIVE_SPVM__CORE__isnanf;
    SPVM_SUB* sub_SPVM__CORE__isinf = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::isinf", strlen("SPVM::CORE::isinf"));
    sub_SPVM__CORE__isinf->native_address = SPVM_NATIVE_SPVM__CORE__isinf;
    SPVM_SUB* sub_SPVM__CORE__isfinite = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::isfinite", strlen("SPVM::CORE::isfinite"));
    sub_SPVM__CORE__isfinite->native_address = SPVM_NATIVE_SPVM__CORE__isfinite;
    SPVM_SUB* sub_SPVM__CORE__isnan = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::isnan", strlen("SPVM::CORE::isnan"));
    sub_SPVM__CORE__isnan->native_address = SPVM_NATIVE_SPVM__CORE__isnan;
    SPVM_SUB* sub_SPVM__CORE__log = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::log", strlen("SPVM::CORE::log"));
    sub_SPVM__CORE__log->native_address = SPVM_NATIVE_SPVM__CORE__log;
    SPVM_SUB* sub_SPVM__CORE__log10 = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::log10", strlen("SPVM::CORE::log10"));
    sub_SPVM__CORE__log10->native_address = SPVM_NATIVE_SPVM__CORE__log10;
    SPVM_SUB* sub_SPVM__CORE__log1p = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::log1p", strlen("SPVM::CORE::log1p"));
    sub_SPVM__CORE__log1p->native_address = SPVM_NATIVE_SPVM__CORE__log1p;
    SPVM_SUB* sub_SPVM__CORE__labs = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::labs", strlen("SPVM::CORE::labs"));
    sub_SPVM__CORE__labs->native_address = SPVM_NATIVE_SPVM__CORE__labs;
    SPVM_SUB* sub_SPVM__CORE__lgamma = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::lgamma", strlen("SPVM::CORE::lgamma"));
    sub_SPVM__CORE__lgamma->native_address = SPVM_NATIVE_SPVM__CORE__lgamma;
    SPVM_SUB* sub_SPVM__CORE__nearbyint = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::nearbyint", strlen("SPVM::CORE::nearbyint"));
    sub_SPVM__CORE__nearbyint->native_address = SPVM_NATIVE_SPVM__CORE__nearbyint;
    SPVM_SUB* sub_SPVM__CORE__pow = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::pow", strlen("SPVM::CORE::pow"));
    sub_SPVM__CORE__pow->native_address = SPVM_NATIVE_SPVM__CORE__pow;
    SPVM_SUB* sub_SPVM__CORE__round = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::round", strlen("SPVM::CORE::round"));
    sub_SPVM__CORE__round->native_address = SPVM_NATIVE_SPVM__CORE__round;
    SPVM_SUB* sub_SPVM__CORE__remainder = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::remainder", strlen("SPVM::CORE::remainder"));
    sub_SPVM__CORE__remainder->native_address = SPVM_NATIVE_SPVM__CORE__remainder;
    SPVM_SUB* sub_SPVM__CORE__sin = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::sin", strlen("SPVM::CORE::sin"));
    sub_SPVM__CORE__sin->native_address = SPVM_NATIVE_SPVM__CORE__sin;
    SPVM_SUB* sub_SPVM__CORE__sinh = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::sinh", strlen("SPVM::CORE::sinh"));
    sub_SPVM__CORE__sinh->native_address = SPVM_NATIVE_SPVM__CORE__sinh;
    SPVM_SUB* sub_SPVM__CORE__sqrt = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::sqrt", strlen("SPVM::CORE::sqrt"));
    sub_SPVM__CORE__sqrt->native_address = SPVM_NATIVE_SPVM__CORE__sqrt;
    SPVM_SUB* sub_SPVM__CORE__time = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::time", strlen("SPVM::CORE::time"));
    sub_SPVM__CORE__time->native_address = SPVM_NATIVE_SPVM__CORE__time;
    SPVM_SUB* sub_SPVM__CORE__tan = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::tan", strlen("SPVM::CORE::tan"));
    sub_SPVM__CORE__tan->native_address = SPVM_NATIVE_SPVM__CORE__tan;
    SPVM_SUB* sub_SPVM__CORE__tanh = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::tanh", strlen("SPVM::CORE::tanh"));
    sub_SPVM__CORE__tanh->native_address = SPVM_NATIVE_SPVM__CORE__tanh;
    SPVM_SUB* sub_SPVM__CORE__tgamma = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::tgamma", strlen("SPVM::CORE::tgamma"));
    sub_SPVM__CORE__tgamma->native_address = SPVM_NATIVE_SPVM__CORE__tgamma;
    SPVM_SUB* sub_SPVM__CORE__warn = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::warn", strlen("SPVM::CORE::warn"));
    sub_SPVM__CORE__warn->native_address = SPVM_NATIVE_SPVM__CORE__warn;
    SPVM_SUB* sub_SPVM__CORE__DBL_MAX = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::DBL_MAX", strlen("SPVM::CORE::DBL_MAX"));
    sub_SPVM__CORE__DBL_MAX->native_address = SPVM_NATIVE_SPVM__CORE__DBL_MAX;
    SPVM_SUB* sub_SPVM__CORE__DBL_MIN = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::DBL_MIN", strlen("SPVM::CORE::DBL_MIN"));
    sub_SPVM__CORE__DBL_MIN->native_address = SPVM_NATIVE_SPVM__CORE__DBL_MIN;
    SPVM_SUB* sub_SPVM__CORE__E = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::E", strlen("SPVM::CORE::E"));
    sub_SPVM__CORE__E->native_address = SPVM_NATIVE_SPVM__CORE__E;
    SPVM_SUB* sub_SPVM__CORE__FLT_MAX = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::FLT_MAX", strlen("SPVM::CORE::FLT_MAX"));
    sub_SPVM__CORE__FLT_MAX->native_address = SPVM_NATIVE_SPVM__CORE__FLT_MAX;
    SPVM_SUB* sub_SPVM__CORE__FLT_MIN = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::FLT_MIN", strlen("SPVM::CORE::FLT_MIN"));
    sub_SPVM__CORE__FLT_MIN->native_address = SPVM_NATIVE_SPVM__CORE__FLT_MIN;
    SPVM_SUB* sub_SPVM__CORE__INFINITYF = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::INFINITYF", strlen("SPVM::CORE::INFINITYF"));
    sub_SPVM__CORE__INFINITYF->native_address = SPVM_NATIVE_SPVM__CORE__INFINITYF;
    SPVM_SUB* sub_SPVM__CORE__INFINITY = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::INFINITY", strlen("SPVM::CORE::INFINITY"));
    sub_SPVM__CORE__INFINITY->native_address = SPVM_NATIVE_SPVM__CORE__INFINITY;
    SPVM_SUB* sub_SPVM__CORE__INT8_MIN = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::INT8_MIN", strlen("SPVM::CORE::INT8_MIN"));
    sub_SPVM__CORE__INT8_MIN->native_address = SPVM_NATIVE_SPVM__CORE__INT8_MIN;
    SPVM_SUB* sub_SPVM__CORE__INT8_MAX = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::INT8_MAX", strlen("SPVM::CORE::INT8_MAX"));
    sub_SPVM__CORE__INT8_MAX->native_address = SPVM_NATIVE_SPVM__CORE__INT8_MAX;
    SPVM_SUB* sub_SPVM__CORE__INT16_MIN = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::INT16_MIN", strlen("SPVM::CORE::INT16_MIN"));
    sub_SPVM__CORE__INT16_MIN->native_address = SPVM_NATIVE_SPVM__CORE__INT16_MIN;
    SPVM_SUB* sub_SPVM__CORE__INT16_MAX = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::INT16_MAX", strlen("SPVM::CORE::INT16_MAX"));
    sub_SPVM__CORE__INT16_MAX->native_address = SPVM_NATIVE_SPVM__CORE__INT16_MAX;
    SPVM_SUB* sub_SPVM__CORE__INT32_MIN = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::INT32_MIN", strlen("SPVM::CORE::INT32_MIN"));
    sub_SPVM__CORE__INT32_MIN->native_address = SPVM_NATIVE_SPVM__CORE__INT32_MIN;
    SPVM_SUB* sub_SPVM__CORE__INT32_MAX = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::INT32_MAX", strlen("SPVM::CORE::INT32_MAX"));
    sub_SPVM__CORE__INT32_MAX->native_address = SPVM_NATIVE_SPVM__CORE__INT32_MAX;
    SPVM_SUB* sub_SPVM__CORE__INT64_MIN = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::INT64_MIN", strlen("SPVM::CORE::INT64_MIN"));
    sub_SPVM__CORE__INT64_MIN->native_address = SPVM_NATIVE_SPVM__CORE__INT64_MIN;
    SPVM_SUB* sub_SPVM__CORE__INT64_MAX = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::INT64_MAX", strlen("SPVM::CORE::INT64_MAX"));
    sub_SPVM__CORE__INT64_MAX->native_address = SPVM_NATIVE_SPVM__CORE__INT64_MAX;
    SPVM_SUB* sub_SPVM__CORE__NANF = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::NANF", strlen("SPVM::CORE::NANF"));
    sub_SPVM__CORE__NANF->native_address = SPVM_NATIVE_SPVM__CORE__NANF;
    SPVM_SUB* sub_SPVM__CORE__NAN = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::NAN", strlen("SPVM::CORE::NAN"));
    sub_SPVM__CORE__NAN->native_address = SPVM_NATIVE_SPVM__CORE__NAN;
    SPVM_SUB* sub_SPVM__CORE__PI = SPVM_HASH_fetch(compiler->sub_symtable, "SPVM::CORE::PI", strlen("SPVM::CORE::PI"));
    sub_SPVM__CORE__PI->native_address = SPVM_NATIVE_SPVM__CORE__PI;
  }

  // Bind native subroutine
  {
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__print = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::print", strlen("SPVM::CORE::print"));
    sub_SPVM__CORE__print->native_address = SPVM_NATIVE_SPVM__CORE__print;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__acos = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::acos", strlen("SPVM::CORE::acos"));
    sub_SPVM__CORE__acos->native_address = SPVM_NATIVE_SPVM__CORE__acos;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__asin = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::asin", strlen("SPVM::CORE::asin"));
    sub_SPVM__CORE__asin->native_address = SPVM_NATIVE_SPVM__CORE__asin;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__atan = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::atan", strlen("SPVM::CORE::atan"));
    sub_SPVM__CORE__atan->native_address = SPVM_NATIVE_SPVM__CORE__atan;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__atan2 = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::atan2", strlen("SPVM::CORE::atan2"));
    sub_SPVM__CORE__atan2->native_address = SPVM_NATIVE_SPVM__CORE__atan2;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__acosh = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::acosh", strlen("SPVM::CORE::acosh"));
    sub_SPVM__CORE__acosh->native_address = SPVM_NATIVE_SPVM__CORE__acosh;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__asinh = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::asinh", strlen("SPVM::CORE::asinh"));
    sub_SPVM__CORE__asinh->native_address = SPVM_NATIVE_SPVM__CORE__asinh;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__atanh = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::atanh", strlen("SPVM::CORE::atanh"));
    sub_SPVM__CORE__atanh->native_address = SPVM_NATIVE_SPVM__CORE__atanh;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__abs = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::abs", strlen("SPVM::CORE::abs"));
    sub_SPVM__CORE__abs->native_address = SPVM_NATIVE_SPVM__CORE__abs;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__cos = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::cos", strlen("SPVM::CORE::cos"));
    sub_SPVM__CORE__cos->native_address = SPVM_NATIVE_SPVM__CORE__cos;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__cosh = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::cosh", strlen("SPVM::CORE::cosh"));
    sub_SPVM__CORE__cosh->native_address = SPVM_NATIVE_SPVM__CORE__cosh;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__cbrt = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::cbrt", strlen("SPVM::CORE::cbrt"));
    sub_SPVM__CORE__cbrt->native_address = SPVM_NATIVE_SPVM__CORE__cbrt;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__ceil = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::ceil", strlen("SPVM::CORE::ceil"));
    sub_SPVM__CORE__ceil->native_address = SPVM_NATIVE_SPVM__CORE__ceil;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__exp = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::exp", strlen("SPVM::CORE::exp"));
    sub_SPVM__CORE__exp->native_address = SPVM_NATIVE_SPVM__CORE__exp;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__exp2 = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::exp2", strlen("SPVM::CORE::exp2"));
    sub_SPVM__CORE__exp2->native_address = SPVM_NATIVE_SPVM__CORE__exp2;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__expm1 = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::expm1", strlen("SPVM::CORE::expm1"));
    sub_SPVM__CORE__expm1->native_address = SPVM_NATIVE_SPVM__CORE__expm1;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__erf = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::erf", strlen("SPVM::CORE::erf"));
    sub_SPVM__CORE__erf->native_address = SPVM_NATIVE_SPVM__CORE__erf;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__erfc = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::erfc", strlen("SPVM::CORE::erfc"));
    sub_SPVM__CORE__erfc->native_address = SPVM_NATIVE_SPVM__CORE__erfc;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__fabs = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::fabs", strlen("SPVM::CORE::fabs"));
    sub_SPVM__CORE__fabs->native_address = SPVM_NATIVE_SPVM__CORE__fabs;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__floor = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::floor", strlen("SPVM::CORE::floor"));
    sub_SPVM__CORE__floor->native_address = SPVM_NATIVE_SPVM__CORE__floor;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__hypot = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::hypot", strlen("SPVM::CORE::hypot"));
    sub_SPVM__CORE__hypot->native_address = SPVM_NATIVE_SPVM__CORE__hypot;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__isinff = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::isinff", strlen("SPVM::CORE::isinff"));
    sub_SPVM__CORE__isinff->native_address = SPVM_NATIVE_SPVM__CORE__isinff;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__isfinitef = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::isfinitef", strlen("SPVM::CORE::isfinitef"));
    sub_SPVM__CORE__isfinitef->native_address = SPVM_NATIVE_SPVM__CORE__isfinitef;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__isnanf = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::isnanf", strlen("SPVM::CORE::isnanf"));
    sub_SPVM__CORE__isnanf->native_address = SPVM_NATIVE_SPVM__CORE__isnanf;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__isinf = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::isinf", strlen("SPVM::CORE::isinf"));
    sub_SPVM__CORE__isinf->native_address = SPVM_NATIVE_SPVM__CORE__isinf;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__isfinite = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::isfinite", strlen("SPVM::CORE::isfinite"));
    sub_SPVM__CORE__isfinite->native_address = SPVM_NATIVE_SPVM__CORE__isfinite;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__isnan = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::isnan", strlen("SPVM::CORE::isnan"));
    sub_SPVM__CORE__isnan->native_address = SPVM_NATIVE_SPVM__CORE__isnan;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__log = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::log", strlen("SPVM::CORE::log"));
    sub_SPVM__CORE__log->native_address = SPVM_NATIVE_SPVM__CORE__log;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__log10 = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::log10", strlen("SPVM::CORE::log10"));
    sub_SPVM__CORE__log10->native_address = SPVM_NATIVE_SPVM__CORE__log10;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__log1p = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::log1p", strlen("SPVM::CORE::log1p"));
    sub_SPVM__CORE__log1p->native_address = SPVM_NATIVE_SPVM__CORE__log1p;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__labs = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::labs", strlen("SPVM::CORE::labs"));
    sub_SPVM__CORE__labs->native_address = SPVM_NATIVE_SPVM__CORE__labs;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__lgamma = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::lgamma", strlen("SPVM::CORE::lgamma"));
    sub_SPVM__CORE__lgamma->native_address = SPVM_NATIVE_SPVM__CORE__lgamma;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__nearbyint = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::nearbyint", strlen("SPVM::CORE::nearbyint"));
    sub_SPVM__CORE__nearbyint->native_address = SPVM_NATIVE_SPVM__CORE__nearbyint;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__pow = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::pow", strlen("SPVM::CORE::pow"));
    sub_SPVM__CORE__pow->native_address = SPVM_NATIVE_SPVM__CORE__pow;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__round = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::round", strlen("SPVM::CORE::round"));
    sub_SPVM__CORE__round->native_address = SPVM_NATIVE_SPVM__CORE__round;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__remainder = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::remainder", strlen("SPVM::CORE::remainder"));
    sub_SPVM__CORE__remainder->native_address = SPVM_NATIVE_SPVM__CORE__remainder;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__sin = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::sin", strlen("SPVM::CORE::sin"));
    sub_SPVM__CORE__sin->native_address = SPVM_NATIVE_SPVM__CORE__sin;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__sinh = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::sinh", strlen("SPVM::CORE::sinh"));
    sub_SPVM__CORE__sinh->native_address = SPVM_NATIVE_SPVM__CORE__sinh;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__sqrt = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::sqrt", strlen("SPVM::CORE::sqrt"));
    sub_SPVM__CORE__sqrt->native_address = SPVM_NATIVE_SPVM__CORE__sqrt;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__time = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::time", strlen("SPVM::CORE::time"));
    sub_SPVM__CORE__time->native_address = SPVM_NATIVE_SPVM__CORE__time;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__tan = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::tan", strlen("SPVM::CORE::tan"));
    sub_SPVM__CORE__tan->native_address = SPVM_NATIVE_SPVM__CORE__tan;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__tanh = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::tanh", strlen("SPVM::CORE::tanh"));
    sub_SPVM__CORE__tanh->native_address = SPVM_NATIVE_SPVM__CORE__tanh;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__tgamma = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::tgamma", strlen("SPVM::CORE::tgamma"));
    sub_SPVM__CORE__tgamma->native_address = SPVM_NATIVE_SPVM__CORE__tgamma;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__warn = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::warn", strlen("SPVM::CORE::warn"));
    sub_SPVM__CORE__warn->native_address = SPVM_NATIVE_SPVM__CORE__warn;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__DBL_MAX = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::DBL_MAX", strlen("SPVM::CORE::DBL_MAX"));
    sub_SPVM__CORE__DBL_MAX->native_address = SPVM_NATIVE_SPVM__CORE__DBL_MAX;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__DBL_MIN = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::DBL_MIN", strlen("SPVM::CORE::DBL_MIN"));
    sub_SPVM__CORE__DBL_MIN->native_address = SPVM_NATIVE_SPVM__CORE__DBL_MIN;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__E = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::E", strlen("SPVM::CORE::E"));
    sub_SPVM__CORE__E->native_address = SPVM_NATIVE_SPVM__CORE__E;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__FLT_MAX = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::FLT_MAX", strlen("SPVM::CORE::FLT_MAX"));
    sub_SPVM__CORE__FLT_MAX->native_address = SPVM_NATIVE_SPVM__CORE__FLT_MAX;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__FLT_MIN = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::FLT_MIN", strlen("SPVM::CORE::FLT_MIN"));
    sub_SPVM__CORE__FLT_MIN->native_address = SPVM_NATIVE_SPVM__CORE__FLT_MIN;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INFINITYF = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::INFINITYF", strlen("SPVM::CORE::INFINITYF"));
    sub_SPVM__CORE__INFINITYF->native_address = SPVM_NATIVE_SPVM__CORE__INFINITYF;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INFINITY = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::INFINITY", strlen("SPVM::CORE::INFINITY"));
    sub_SPVM__CORE__INFINITY->native_address = SPVM_NATIVE_SPVM__CORE__INFINITY;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INT8_MIN = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::INT8_MIN", strlen("SPVM::CORE::INT8_MIN"));
    sub_SPVM__CORE__INT8_MIN->native_address = SPVM_NATIVE_SPVM__CORE__INT8_MIN;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INT8_MAX = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::INT8_MAX", strlen("SPVM::CORE::INT8_MAX"));
    sub_SPVM__CORE__INT8_MAX->native_address = SPVM_NATIVE_SPVM__CORE__INT8_MAX;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INT16_MIN = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::INT16_MIN", strlen("SPVM::CORE::INT16_MIN"));
    sub_SPVM__CORE__INT16_MIN->native_address = SPVM_NATIVE_SPVM__CORE__INT16_MIN;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INT16_MAX = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::INT16_MAX", strlen("SPVM::CORE::INT16_MAX"));
    sub_SPVM__CORE__INT16_MAX->native_address = SPVM_NATIVE_SPVM__CORE__INT16_MAX;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INT32_MIN = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::INT32_MIN", strlen("SPVM::CORE::INT32_MIN"));
    sub_SPVM__CORE__INT32_MIN->native_address = SPVM_NATIVE_SPVM__CORE__INT32_MIN;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INT32_MAX = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::INT32_MAX", strlen("SPVM::CORE::INT32_MAX"));
    sub_SPVM__CORE__INT32_MAX->native_address = SPVM_NATIVE_SPVM__CORE__INT32_MAX;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INT64_MIN = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::INT64_MIN", strlen("SPVM::CORE::INT64_MIN"));
    sub_SPVM__CORE__INT64_MIN->native_address = SPVM_NATIVE_SPVM__CORE__INT64_MIN;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__INT64_MAX = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::INT64_MAX", strlen("SPVM::CORE::INT64_MAX"));
    sub_SPVM__CORE__INT64_MAX->native_address = SPVM_NATIVE_SPVM__CORE__INT64_MAX;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__NANF = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::NANF", strlen("SPVM::CORE::NANF"));
    sub_SPVM__CORE__NANF->native_address = SPVM_NATIVE_SPVM__CORE__NANF;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__NAN = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::NAN", strlen("SPVM::CORE::NAN"));
    sub_SPVM__CORE__NAN->native_address = SPVM_NATIVE_SPVM__CORE__NAN;
    SPVM_RUNTIME_SUB* sub_SPVM__CORE__PI = SPVM_HASH_fetch(runtime->runtime_sub_symtable, "SPVM::CORE::PI", strlen("SPVM::CORE::PI"));
    sub_SPVM__CORE__PI->native_address = SPVM_NATIVE_SPVM__CORE__PI;
  }

  SPVM_ENV* env = runtime->env;

  // Entry point subroutine address
  SPVM_SUB* sub_start;
  int32_t sub_id;
  if (start_sub_name) {
    sub_start = SPVM_HASH_fetch(compiler->sub_symtable, start_sub_name, strlen(start_sub_name));
    if (sub_start) {
      sub_id = sub_start->id;
    }
    else {
      fprintf(stderr, "Can't find entry point subroutine %s", start_sub_name);
      exit(EXIT_FAILURE);
    }
  }
  else {
    fprintf(stderr, "Can't find entry point subroutine\n");
    exit(EXIT_FAILURE);
  }
  
  // Enter scope
  int32_t scope_id = env->enter_scope(env);
  
  // new byte[][args_length] object
  int32_t arg_type_basic_id = env->get_basic_type_id(env, "byte");
  void* cmd_args_obj = env->new_multi_array(env, arg_type_basic_id, 1, argc);
  
  // Set command line arguments
  for (int32_t arg_index = 0; arg_index < argc; arg_index++) {
    void* cmd_arg_obj = env->new_string(env, argv[arg_index], strlen(argv[arg_index]));
    env->set_object_array_element(env, cmd_args_obj, arg_index, cmd_arg_obj);
  }
  
  SPVM_VALUE stack[255];
  stack[0].oval = cmd_args_obj;
  
  // Run
  int32_t exception_flag = env->call_sub(env, sub_id, stack);
  
  int32_t status_code;
  if (exception_flag) {
    SPVM_RUNTIME_API_print(env, runtime->exception);
    printf("\n");
    status_code = 255;
  }
  else {
    status_code = stack[0].ival;
  }
  
  // Leave scope
  env->leave_scope(env, scope_id);
  
  SPVM_RUNTIME_free(runtime);
  
  return status_code;
}

