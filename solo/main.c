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
  
  // Bind native subroutine
  {
    SPVM_OP* op_sub_SPVM__CORE__print = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::print", strlen("SPVM::CORE::print"));
    op_sub_SPVM__CORE__print->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__print;
    SPVM_OP* op_sub_SPVM__CORE__acos = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::acos", strlen("SPVM::CORE::acos"));
    op_sub_SPVM__CORE__acos->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__acos;
    SPVM_OP* op_sub_SPVM__CORE__asin = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::asin", strlen("SPVM::CORE::asin"));
    op_sub_SPVM__CORE__asin->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__asin;
    SPVM_OP* op_sub_SPVM__CORE__atan = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::atan", strlen("SPVM::CORE::atan"));
    op_sub_SPVM__CORE__atan->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__atan;
    SPVM_OP* op_sub_SPVM__CORE__atan2 = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::atan2", strlen("SPVM::CORE::atan2"));
    op_sub_SPVM__CORE__atan2->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__atan2;
    SPVM_OP* op_sub_SPVM__CORE__acosh = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::acosh", strlen("SPVM::CORE::acosh"));
    op_sub_SPVM__CORE__acosh->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__acosh;
    SPVM_OP* op_sub_SPVM__CORE__asinh = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::asinh", strlen("SPVM::CORE::asinh"));
    op_sub_SPVM__CORE__asinh->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__asinh;
    SPVM_OP* op_sub_SPVM__CORE__atanh = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::atanh", strlen("SPVM::CORE::atanh"));
    op_sub_SPVM__CORE__atanh->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__atanh;
    SPVM_OP* op_sub_SPVM__CORE__abs = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::abs", strlen("SPVM::CORE::abs"));
    op_sub_SPVM__CORE__abs->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__abs;
    SPVM_OP* op_sub_SPVM__CORE__cos = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::cos", strlen("SPVM::CORE::cos"));
    op_sub_SPVM__CORE__cos->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__cos;
    SPVM_OP* op_sub_SPVM__CORE__cosh = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::cosh", strlen("SPVM::CORE::cosh"));
    op_sub_SPVM__CORE__cosh->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__cosh;
    SPVM_OP* op_sub_SPVM__CORE__cbrt = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::cbrt", strlen("SPVM::CORE::cbrt"));
    op_sub_SPVM__CORE__cbrt->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__cbrt;
    SPVM_OP* op_sub_SPVM__CORE__ceil = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::ceil", strlen("SPVM::CORE::ceil"));
    op_sub_SPVM__CORE__ceil->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__ceil;
    SPVM_OP* op_sub_SPVM__CORE__exp = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::exp", strlen("SPVM::CORE::exp"));
    op_sub_SPVM__CORE__exp->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__exp;
    SPVM_OP* op_sub_SPVM__CORE__exp2 = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::exp2", strlen("SPVM::CORE::exp2"));
    op_sub_SPVM__CORE__exp2->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__exp2;
    SPVM_OP* op_sub_SPVM__CORE__expm1 = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::expm1", strlen("SPVM::CORE::expm1"));
    op_sub_SPVM__CORE__expm1->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__expm1;
    SPVM_OP* op_sub_SPVM__CORE__erf = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::erf", strlen("SPVM::CORE::erf"));
    op_sub_SPVM__CORE__erf->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__erf;
    SPVM_OP* op_sub_SPVM__CORE__erfc = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::erfc", strlen("SPVM::CORE::erfc"));
    op_sub_SPVM__CORE__erfc->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__erfc;
    SPVM_OP* op_sub_SPVM__CORE__fabs = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::fabs", strlen("SPVM::CORE::fabs"));
    op_sub_SPVM__CORE__fabs->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__fabs;
    SPVM_OP* op_sub_SPVM__CORE__floor = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::floor", strlen("SPVM::CORE::floor"));
    op_sub_SPVM__CORE__floor->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__floor;
    SPVM_OP* op_sub_SPVM__CORE__hypot = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::hypot", strlen("SPVM::CORE::hypot"));
    op_sub_SPVM__CORE__hypot->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__hypot;
    SPVM_OP* op_sub_SPVM__CORE__isinff = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::isinff", strlen("SPVM::CORE::isinff"));
    op_sub_SPVM__CORE__isinff->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__isinff;
    SPVM_OP* op_sub_SPVM__CORE__isfinitef = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::isfinitef", strlen("SPVM::CORE::isfinitef"));
    op_sub_SPVM__CORE__isfinitef->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__isfinitef;
    SPVM_OP* op_sub_SPVM__CORE__isnanf = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::isnanf", strlen("SPVM::CORE::isnanf"));
    op_sub_SPVM__CORE__isnanf->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__isnanf;
    SPVM_OP* op_sub_SPVM__CORE__isinf = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::isinf", strlen("SPVM::CORE::isinf"));
    op_sub_SPVM__CORE__isinf->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__isinf;
    SPVM_OP* op_sub_SPVM__CORE__isfinite = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::isfinite", strlen("SPVM::CORE::isfinite"));
    op_sub_SPVM__CORE__isfinite->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__isfinite;
    SPVM_OP* op_sub_SPVM__CORE__isnan = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::isnan", strlen("SPVM::CORE::isnan"));
    op_sub_SPVM__CORE__isnan->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__isnan;
    SPVM_OP* op_sub_SPVM__CORE__log = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::log", strlen("SPVM::CORE::log"));
    op_sub_SPVM__CORE__log->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__log;
    SPVM_OP* op_sub_SPVM__CORE__log10 = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::log10", strlen("SPVM::CORE::log10"));
    op_sub_SPVM__CORE__log10->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__log10;
    SPVM_OP* op_sub_SPVM__CORE__log1p = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::log1p", strlen("SPVM::CORE::log1p"));
    op_sub_SPVM__CORE__log1p->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__log1p;
    SPVM_OP* op_sub_SPVM__CORE__labs = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::labs", strlen("SPVM::CORE::labs"));
    op_sub_SPVM__CORE__labs->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__labs;
    SPVM_OP* op_sub_SPVM__CORE__lgamma = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::lgamma", strlen("SPVM::CORE::lgamma"));
    op_sub_SPVM__CORE__lgamma->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__lgamma;
    SPVM_OP* op_sub_SPVM__CORE__nearbyint = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::nearbyint", strlen("SPVM::CORE::nearbyint"));
    op_sub_SPVM__CORE__nearbyint->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__nearbyint;
    SPVM_OP* op_sub_SPVM__CORE__pow = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::pow", strlen("SPVM::CORE::pow"));
    op_sub_SPVM__CORE__pow->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__pow;
    SPVM_OP* op_sub_SPVM__CORE__round = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::round", strlen("SPVM::CORE::round"));
    op_sub_SPVM__CORE__round->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__round;
    SPVM_OP* op_sub_SPVM__CORE__remainder = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::remainder", strlen("SPVM::CORE::remainder"));
    op_sub_SPVM__CORE__remainder->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__remainder;
    SPVM_OP* op_sub_SPVM__CORE__sin = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::sin", strlen("SPVM::CORE::sin"));
    op_sub_SPVM__CORE__sin->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__sin;
    SPVM_OP* op_sub_SPVM__CORE__sinh = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::sinh", strlen("SPVM::CORE::sinh"));
    op_sub_SPVM__CORE__sinh->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__sinh;
    SPVM_OP* op_sub_SPVM__CORE__sqrt = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::sqrt", strlen("SPVM::CORE::sqrt"));
    op_sub_SPVM__CORE__sqrt->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__sqrt;
    SPVM_OP* op_sub_SPVM__CORE__time = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::time", strlen("SPVM::CORE::time"));
    op_sub_SPVM__CORE__time->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__time;
    SPVM_OP* op_sub_SPVM__CORE__tan = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::tan", strlen("SPVM::CORE::tan"));
    op_sub_SPVM__CORE__tan->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__tan;
    SPVM_OP* op_sub_SPVM__CORE__tanh = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::tanh", strlen("SPVM::CORE::tanh"));
    op_sub_SPVM__CORE__tanh->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__tanh;
    SPVM_OP* op_sub_SPVM__CORE__tgamma = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::tgamma", strlen("SPVM::CORE::tgamma"));
    op_sub_SPVM__CORE__tgamma->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__tgamma;
    SPVM_OP* op_sub_SPVM__CORE__warn = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::warn", strlen("SPVM::CORE::warn"));
    op_sub_SPVM__CORE__warn->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__warn;
    SPVM_OP* op_sub_SPVM__CORE__DBL_MAX = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::DBL_MAX", strlen("SPVM::CORE::DBL_MAX"));
    op_sub_SPVM__CORE__DBL_MAX->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__DBL_MAX;
    SPVM_OP* op_sub_SPVM__CORE__DBL_MIN = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::DBL_MIN", strlen("SPVM::CORE::DBL_MIN"));
    op_sub_SPVM__CORE__DBL_MIN->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__DBL_MIN;
    SPVM_OP* op_sub_SPVM__CORE__E = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::E", strlen("SPVM::CORE::E"));
    op_sub_SPVM__CORE__E->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__E;
    SPVM_OP* op_sub_SPVM__CORE__FLT_MAX = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::FLT_MAX", strlen("SPVM::CORE::FLT_MAX"));
    op_sub_SPVM__CORE__FLT_MAX->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__FLT_MAX;
    SPVM_OP* op_sub_SPVM__CORE__FLT_MIN = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::FLT_MIN", strlen("SPVM::CORE::FLT_MIN"));
    op_sub_SPVM__CORE__FLT_MIN->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__FLT_MIN;
    SPVM_OP* op_sub_SPVM__CORE__INFINITYF = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::INFINITYF", strlen("SPVM::CORE::INFINITYF"));
    op_sub_SPVM__CORE__INFINITYF->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__INFINITYF;
    SPVM_OP* op_sub_SPVM__CORE__INFINITY = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::INFINITY", strlen("SPVM::CORE::INFINITY"));
    op_sub_SPVM__CORE__INFINITY->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__INFINITY;
    SPVM_OP* op_sub_SPVM__CORE__INT8_MIN = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::INT8_MIN", strlen("SPVM::CORE::INT8_MIN"));
    op_sub_SPVM__CORE__INT8_MIN->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__INT8_MIN;
    SPVM_OP* op_sub_SPVM__CORE__INT8_MAX = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::INT8_MAX", strlen("SPVM::CORE::INT8_MAX"));
    op_sub_SPVM__CORE__INT8_MAX->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__INT8_MAX;
    SPVM_OP* op_sub_SPVM__CORE__INT16_MIN = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::INT16_MIN", strlen("SPVM::CORE::INT16_MIN"));
    op_sub_SPVM__CORE__INT16_MIN->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__INT16_MIN;
    SPVM_OP* op_sub_SPVM__CORE__INT16_MAX = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::INT16_MAX", strlen("SPVM::CORE::INT16_MAX"));
    op_sub_SPVM__CORE__INT16_MAX->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__INT16_MAX;
    SPVM_OP* op_sub_SPVM__CORE__INT32_MIN = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::INT32_MIN", strlen("SPVM::CORE::INT32_MIN"));
    op_sub_SPVM__CORE__INT32_MIN->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__INT32_MIN;
    SPVM_OP* op_sub_SPVM__CORE__INT32_MAX = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::INT32_MAX", strlen("SPVM::CORE::INT32_MAX"));
    op_sub_SPVM__CORE__INT32_MAX->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__INT32_MAX;
    SPVM_OP* op_sub_SPVM__CORE__INT64_MIN = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::INT64_MIN", strlen("SPVM::CORE::INT64_MIN"));
    op_sub_SPVM__CORE__INT64_MIN->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__INT64_MIN;
    SPVM_OP* op_sub_SPVM__CORE__INT64_MAX = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::INT64_MAX", strlen("SPVM::CORE::INT64_MAX"));
    op_sub_SPVM__CORE__INT64_MAX->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__INT64_MAX;
    SPVM_OP* op_sub_SPVM__CORE__NANF = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::NANF", strlen("SPVM::CORE::NANF"));
    op_sub_SPVM__CORE__NANF->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__NANF;
    SPVM_OP* op_sub_SPVM__CORE__NAN = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::NAN", strlen("SPVM::CORE::NAN"));
    op_sub_SPVM__CORE__NAN->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__NAN;
    SPVM_OP* op_sub_SPVM__CORE__PI = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::PI", strlen("SPVM::CORE::PI"));
    op_sub_SPVM__CORE__PI->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__PI;
  }
  
  // Create run-time
  SPVM_RUNTIME* runtime = SPVM_COMPILER_new_runtime(compiler);
  
  SPVM_ENV* env = runtime->env;

  // Entry point subroutine address
  SPVM_OP* op_sub_start;
  int32_t sub_id;
  if (start_sub_name) {
    op_sub_start = SPVM_HASH_fetch(compiler->op_sub_symtable, start_sub_name, strlen(start_sub_name));
    if (op_sub_start) {
      sub_id = op_sub_start->uv.sub->id;
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

