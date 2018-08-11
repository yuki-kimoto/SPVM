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

#include "SPVM/CORE.native/CORE.c"

void SPVM_MAIN_bind_core_func(SPVM_COMPILER* compiler, SPVM_LIST* op_subs) {
  (void)compiler;
  
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
              sub->native_address = SPVM_NATIVE_SPVM__CORE__acos;
            }
            else if (strcmp(sub_name, "asin") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__asin;
            }
            else if (strcmp(sub_name, "atan") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__atan;
            }
            else if (strcmp(sub_name, "atan2") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__atan2;
            }
            else if (strcmp(sub_name, "acosh") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__acosh;
            }
            else if (strcmp(sub_name, "asinh") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__asinh;
            }
            else if (strcmp(sub_name, "atanh") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__atanh;
            }
            else if (strcmp(sub_name, "abs") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__abs;
            }
            break;
          case 'c':
            if (strcmp(sub_name, "cos") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__cos;
            }
            else if (strcmp(sub_name, "cosh") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__cosh;
            }
            else if (strcmp(sub_name, "cbrt") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__cbrt;
            }
            else if (strcmp(sub_name, "ceil") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__ceil;
            }
            break;
          case 'e':
              if (strcmp(sub_name, "exp") == 0) {
                sub->native_address = SPVM_NATIVE_SPVM__CORE__exp;
              }
              else if (strcmp(sub_name, "exp2") == 0) {
                sub->native_address = SPVM_NATIVE_SPVM__CORE__exp2;
              }
              else if (strcmp(sub_name, "expm1") == 0) {
                sub->native_address = SPVM_NATIVE_SPVM__CORE__expm1;
              }
              else if (strcmp(sub_name, "erf") == 0) {
                sub->native_address = SPVM_NATIVE_SPVM__CORE__erf;
              }
              else if (strcmp(sub_name, "erfc") == 0) {
                sub->native_address = SPVM_NATIVE_SPVM__CORE__erfc;
              }
            break;
          case 'f':
            if (strcmp(sub_name, "fabs") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__fabs;
            }
            else if (strcmp(sub_name, "floor") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__floor;
            }
            break;
          case 'h':
            if (strcmp(sub_name, "hypot") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__hypot;
            }
            break;
          case 'i':
            if (strcmp(sub_name, "isinff") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__isinff;
            }
            else if (strcmp(sub_name, "isfinitef") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__isfinitef;
            }
            else if (strcmp(sub_name, "isnanf") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__isnanf;
            }
            else if (strcmp(sub_name, "isinf") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__isinf;
            }
            else if (strcmp(sub_name, "isfinite") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__isfinite;
            }
            else if (strcmp(sub_name, "isnan") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__isnan;
            }
            break;
          case 'l':
            if (strcmp(sub_name, "log") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__log;
            }
            else if (strcmp(sub_name, "log10") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__log10;
            }
            else if (strcmp(sub_name, "log1p") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__log1p;
            }
            else if (strcmp(sub_name, "labs") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__labs;
            }
            else if (strcmp(sub_name, "lgamma") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__lgamma;
            }
            break;
          case 'n':
            if (strcmp(sub_name, "nearbyint") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__nearbyint;
            }
            break;
          case 'p':
            if (strcmp(sub_name, "pow") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__pow;
            }
            break;
          case 'r':
            if (strcmp(sub_name, "round") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__round;
            }
            else if (strcmp(sub_name, "remainder") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__remainder;
            }
            break;
          case 's':
            if (strcmp(sub_name, "sin") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__sin;
            }
            else if (strcmp(sub_name, "sinh") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__sinh;
            }
            else if (strcmp(sub_name, "sqrt") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__sqrt;
            }
            break;
          case 't':
            if (strcmp(sub_name, "time") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__time;
            }
            else if (strcmp(sub_name, "tan") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__tan;
            }
            else if (strcmp(sub_name, "tanh") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__tanh;
            }
            else if (strcmp(sub_name, "tgamma") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__tgamma;
            }
            break;
          case 'w':
            if (strcmp(sub_name, "warn") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__warn;
            }
            break;
          case 'D':
            if (strcmp(sub_name, "DBL_MAX") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__DBL_MAX;
            }
            else if (strcmp(sub_name, "DBL_MIN") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__DBL_MIN;
            }
            break;
          case 'E':
            if (strcmp(sub_name, "E") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__E;
            }
            break;
          case 'F':
            if (strcmp(sub_name, "FLT_MAX") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__FLT_MAX;
            }
            else if (strcmp(sub_name, "FLT_MIN") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__FLT_MIN;
            }
            break;
          case 'I':
            if (strcmp(sub_name, "INFINITYF") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__INFINITYF;
            }
            else if (strcmp(sub_name, "INFINITY") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__INFINITY;
            }
            else if (strcmp(sub_name, "INT8_MIN") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__INT8_MIN;
            }
            else if (strcmp(sub_name, "INT8_MAX") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__INT8_MAX;
            }
            else if (strcmp(sub_name, "INT16_MIN") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__INT16_MIN;
            }
            else if (strcmp(sub_name, "INT16_MAX") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__INT16_MAX;
            }
            else if (strcmp(sub_name, "INT32_MIN") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__INT32_MIN;
            }
            else if (strcmp(sub_name, "INT32_MAX") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__INT32_MAX;
            }
            else if (strcmp(sub_name, "INT64_MIN") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__INT64_MIN;
            }
            else if (strcmp(sub_name, "INT64_MAX") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__INT64_MAX;
            }
            break;
          case 'N':
            if (strcmp(sub_name, "NANF") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__NANF;
            }
            else if (strcmp(sub_name, "NAN") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__NAN;
            }
            break;
          case 'P':
            if (strcmp(sub_name, "PI") == 0) {
              sub->native_address = SPVM_NATIVE_SPVM__CORE__PI;
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
  
  // Bind native subroutine
  {
    SPVM_OP* op_sub_SPVM__CORE__print = SPVM_HASH_fetch(compiler->op_sub_symtable, "SPVM::CORE::print", strlen("SPVM::CORE::print"));
    op_sub_SPVM__CORE__print->uv.sub->native_address = SPVM_NATIVE_SPVM__CORE__print;
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

