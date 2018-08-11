#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <assert.h>

#include "spvm_compiler.h"
#include "spvm_hash.h"
#include "spvm_list.h"
#include "spvm_util_allocator.h"
#include "spvm_opcode_array.h"
#include "spvm_runtime.h"
#include "spvm_op.h"
#include "spvm_sub.h"
#include "spvm_dumper.h"
#include "spvm_yacc_util.h"
#include "spvm_runtime_api.h"
#include "spvm_opcode_builder.h"
#include "spvm_csource_builder.h"
#include "spvm_package.h"

#include <spvm_native.h>

#include "spvm_core_func.h"

void SPVM_MAIN_bind_core_func(SPVM_COMPILER* compiler, SPVM_LIST* op_subs) {
  (void)compiler;
  
  // Bind native subroutine
  {
    int32_t i;
    for (i = 0; i < op_subs->length; i++) {
      SPVM_OP* op_sub = SPVM_LIST_fetch(op_subs, i);
      SPVM_SUB* sub = op_sub->uv.sub;
      
      if (sub->have_native_desc) {
        // Sub abs name
        const char* sub_name = sub->op_name->uv.name;
        switch (sub_name[0]) {
          case 'a':
            if (strcmp(sub_name, "acos") == 0) {
              sub->native_address = SPVM_CORE_FUNC_acos;
            }
            else if (strcmp(sub_name, "asin") == 0) {
              sub->native_address = SPVM_CORE_FUNC_asin;
            }
            else if (strcmp(sub_name, "atan") == 0) {
              sub->native_address = SPVM_CORE_FUNC_atan;
            }
            else if (strcmp(sub_name, "atan2") == 0) {
              sub->native_address = SPVM_CORE_FUNC_atan2;
            }
            else if (strcmp(sub_name, "acosh") == 0) {
              sub->native_address = SPVM_CORE_FUNC_acosh;
            }
            else if (strcmp(sub_name, "asinh") == 0) {
              sub->native_address = SPVM_CORE_FUNC_asinh;
            }
            else if (strcmp(sub_name, "atanh") == 0) {
              sub->native_address = SPVM_CORE_FUNC_atanh;
            }
            else if (strcmp(sub_name, "abs") == 0) {
              sub->native_address = SPVM_CORE_FUNC_abs;
            }
            break;
          case 'c':
            if (strcmp(sub_name, "cos") == 0) {
              sub->native_address = SPVM_CORE_FUNC_cos;
            }
            else if (strcmp(sub_name, "cosh") == 0) {
              sub->native_address = SPVM_CORE_FUNC_cosh;
            }
            else if (strcmp(sub_name, "cbrt") == 0) {
              sub->native_address = SPVM_CORE_FUNC_cbrt;
            }
            else if (strcmp(sub_name, "ceil") == 0) {
              sub->native_address = SPVM_CORE_FUNC_ceil;
            }
            break;
          case 'e':
              if (strcmp(sub_name, "exp") == 0) {
                sub->native_address = SPVM_CORE_FUNC_exp;
              }
              else if (strcmp(sub_name, "exp2") == 0) {
                sub->native_address = SPVM_CORE_FUNC_exp2;
              }
              else if (strcmp(sub_name, "expm1") == 0) {
                sub->native_address = SPVM_CORE_FUNC_expm1;
              }
              else if (strcmp(sub_name, "erf") == 0) {
                sub->native_address = SPVM_CORE_FUNC_erf;
              }
              else if (strcmp(sub_name, "erfc") == 0) {
                sub->native_address = SPVM_CORE_FUNC_erfc;
              }
            break;
          case 'f':
            if (strcmp(sub_name, "fabs") == 0) {
              sub->native_address = SPVM_CORE_FUNC_fabs;
            }
            else if (strcmp(sub_name, "floor") == 0) {
              sub->native_address = SPVM_CORE_FUNC_floor;
            }
            break;
          case 'h':
            if (strcmp(sub_name, "hypot") == 0) {
              sub->native_address = SPVM_CORE_FUNC_hypot;
            }
            break;
          case 'i':
            if (strcmp(sub_name, "isinff") == 0) {
              sub->native_address = SPVM_CORE_FUNC_isinff;
            }
            else if (strcmp(sub_name, "isfinitef") == 0) {
              sub->native_address = SPVM_CORE_FUNC_isfinitef;
            }
            else if (strcmp(sub_name, "isnanf") == 0) {
              sub->native_address = SPVM_CORE_FUNC_isnanf;
            }
            else if (strcmp(sub_name, "isinf") == 0) {
              sub->native_address = SPVM_CORE_FUNC_isinf;
            }
            else if (strcmp(sub_name, "isfinite") == 0) {
              sub->native_address = SPVM_CORE_FUNC_isfinite;
            }
            else if (strcmp(sub_name, "isnan") == 0) {
              sub->native_address = SPVM_CORE_FUNC_isnan;
            }
            break;
          case 'l':
            if (strcmp(sub_name, "log") == 0) {
              sub->native_address = SPVM_CORE_FUNC_log;
            }
            else if (strcmp(sub_name, "log10") == 0) {
              sub->native_address = SPVM_CORE_FUNC_log10;
            }
            else if (strcmp(sub_name, "log1p") == 0) {
              sub->native_address = SPVM_CORE_FUNC_log1p;
            }
            else if (strcmp(sub_name, "labs") == 0) {
              sub->native_address = SPVM_CORE_FUNC_labs;
            }
            else if (strcmp(sub_name, "lgamma") == 0) {
              sub->native_address = SPVM_CORE_FUNC_lgamma;
            }
            break;
          case 'n':
            if (strcmp(sub_name, "nearbyint") == 0) {
              sub->native_address = SPVM_CORE_FUNC_nearbyint;
            }
            break;
          case 'p':
            if (strcmp(sub_name, "print") == 0) {
              sub->native_address = SPVM_CORE_FUNC_print;
            }
            else if (strcmp(sub_name, "pow") == 0) {
              sub->native_address = SPVM_CORE_FUNC_pow;
            }
            break;
          case 'r':
            if (strcmp(sub_name, "round") == 0) {
              sub->native_address = SPVM_CORE_FUNC_round;
            }
            else if (strcmp(sub_name, "remainder") == 0) {
              sub->native_address = SPVM_CORE_FUNC_remainder;
            }
            break;
          case 's':
            if (strcmp(sub_name, "sin") == 0) {
              sub->native_address = SPVM_CORE_FUNC_sin;
            }
            else if (strcmp(sub_name, "sinh") == 0) {
              sub->native_address = SPVM_CORE_FUNC_sinh;
            }
            else if (strcmp(sub_name, "sqrt") == 0) {
              sub->native_address = SPVM_CORE_FUNC_sqrt;
            }
            break;
          case 't':
            if (strcmp(sub_name, "time") == 0) {
              sub->native_address = SPVM_CORE_FUNC_time;
            }
            else if (strcmp(sub_name, "tan") == 0) {
              sub->native_address = SPVM_CORE_FUNC_tan;
            }
            else if (strcmp(sub_name, "tanh") == 0) {
              sub->native_address = SPVM_CORE_FUNC_tanh;
            }
            else if (strcmp(sub_name, "tgamma") == 0) {
              sub->native_address = SPVM_CORE_FUNC_tgamma;
            }
            break;
          case 'w':
            if (strcmp(sub_name, "warn") == 0) {
              sub->native_address = SPVM_CORE_FUNC_warn;
            }
            break;
          case 'D':
            if (strcmp(sub_name, "DBL_MAX") == 0) {
              sub->native_address = SPVM_CORE_FUNC_DBL_MAX;
            }
            else if (strcmp(sub_name, "DBL_MIN") == 0) {
              sub->native_address = SPVM_CORE_FUNC_DBL_MIN;
            }
            break;
          case 'E':
            if (strcmp(sub_name, "E") == 0) {
              sub->native_address = SPVM_CORE_FUNC_E;
            }
            break;
          case 'F':
            if (strcmp(sub_name, "FLT_MAX") == 0) {
              sub->native_address = SPVM_CORE_FUNC_FLT_MAX;
            }
            else if (strcmp(sub_name, "FLT_MIN") == 0) {
              sub->native_address = SPVM_CORE_FUNC_FLT_MIN;
            }
            break;
          case 'I':
            if (strcmp(sub_name, "INFINITYF") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INFINITYF;
            }
            else if (strcmp(sub_name, "INFINITY") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INFINITY;
            }
            else if (strcmp(sub_name, "INT8_MIN") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INT8_MIN;
            }
            else if (strcmp(sub_name, "INT8_MAX") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INT8_MAX;
            }
            else if (strcmp(sub_name, "INT16_MIN") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INT16_MIN;
            }
            else if (strcmp(sub_name, "INT16_MAX") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INT16_MAX;
            }
            else if (strcmp(sub_name, "INT32_MIN") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INT32_MIN;
            }
            else if (strcmp(sub_name, "INT32_MAX") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INT32_MAX;
            }
            else if (strcmp(sub_name, "INT64_MIN") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INT64_MIN;
            }
            else if (strcmp(sub_name, "INT64_MAX") == 0) {
              sub->native_address = SPVM_CORE_FUNC_INT64_MAX;
            }
            break;
          case 'N':
            if (strcmp(sub_name, "NANF") == 0) {
              sub->native_address = SPVM_CORE_FUNC_NANF;
            }
            else if (strcmp(sub_name, "NAN") == 0) {
              sub->native_address = SPVM_CORE_FUNC_NAN;
            }
            break;
          case 'P':
            if (strcmp(sub_name, "PI") == 0) {
              sub->native_address = SPVM_CORE_FUNC_PI;
            }
            break;
          default:
            assert(0);
        }
      }
    }
  }
}

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
  
  for (int32_t package_index = 0; package_index < compiler->op_packages->length; package_index++) {
    SPVM_OP* op_package = SPVM_LIST_fetch(compiler->op_packages, package_index);
    SPVM_PACKAGE* package = op_package->uv.package;
    const char* package_name = package->op_name->uv.name;
    
    if (strcmp(package_name, "SPVM::CORE") == 0) {
      SPVM_MAIN_bind_core_func(compiler, package->op_subs);
    }
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

