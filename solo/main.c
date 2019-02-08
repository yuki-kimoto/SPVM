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

int32_t SPNATIVE__SPVM__CORE__print(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPNATIVE__SPVM__CORE__warn(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPNATIVE__SPVM__CORE__DBL_MAX(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPNATIVE__SPVM__CORE__DBL_MIN(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPNATIVE__SPVM__CORE__FLT_MAX(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPNATIVE__SPVM__CORE__FLT_MIN(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPNATIVE__SPVM__CORE__INT8_MIN(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPNATIVE__SPVM__CORE__INT8_MAX(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPNATIVE__SPVM__CORE__INT16_MIN(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPNATIVE__SPVM__CORE__INT16_MAX(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPNATIVE__SPVM__CORE__INT32_MIN(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPNATIVE__SPVM__CORE__INT32_MAX(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPNATIVE__SPVM__CORE__INT64_MIN(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPNATIVE__SPVM__CORE__INT64_MAX(SPVM_ENV* env, SPVM_VALUE* stack);
int32_t SPNATIVE__SPVM__CORE__init_native_constants(SPVM_ENV* env, SPVM_VALUE* stack);

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
  
  // Build runtime
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_build_runtime(portable);
  
  // Create env
  SPVM_ENV* env = SPVM_RUNTIME_API_create_env(runtime);
  
  // Free compiler
  SPVM_COMPILER_free(compiler);

#ifndef SPVM_DONT_USE_CORE_LIB

  // Bind native subroutine
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "init_native_constants";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);
    
    runtime->sub_cfunc_addresses[sub->id] = SPNATIVE__SPVM__CORE__init_native_constants;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "print";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPNATIVE__SPVM__CORE__print;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "warn";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPNATIVE__SPVM__CORE__warn;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "INT8_MIN";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPNATIVE__SPVM__CORE__INT8_MIN;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "INT8_MAX";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPNATIVE__SPVM__CORE__INT8_MAX;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "INT16_MIN";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPNATIVE__SPVM__CORE__INT16_MIN;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "INT16_MAX";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPNATIVE__SPVM__CORE__INT16_MAX;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "INT32_MIN";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPNATIVE__SPVM__CORE__INT32_MIN;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "INT32_MAX";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPNATIVE__SPVM__CORE__INT32_MAX;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "INT64_MIN";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPNATIVE__SPVM__CORE__INT64_MIN;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "INT64_MAX";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPNATIVE__SPVM__CORE__INT64_MAX;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "FLT_MAX";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPNATIVE__SPVM__CORE__FLT_MAX;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "FLT_MIN";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPNATIVE__SPVM__CORE__FLT_MIN;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "DBL_MAX";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPNATIVE__SPVM__CORE__DBL_MAX;
  }
  {
    const char* package_name = "SPVM::CORE";
    const char* sub_name = "DBL_MIN";
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_RUNTIME_API_basic_type(env, package_name); SPVM_RUNTIME_PACKAGE* package = &runtime->packages[basic_type->package_id];
    SPVM_RUNTIME_SUB* sub = SPVM_RUNTIME_API_sub(env, package, sub_name);
    runtime->sub_cfunc_addresses[sub->id] = SPNATIVE__SPVM__CORE__DBL_MIN;
  }
#endif
  
  // Call begin blocks
  SPVM_RUNTIME_API_call_begin_blocks(env);

  // Call entry point sub
  int32_t status_code = SPVM_RUNTIME_API_call_entry_point_sub(env, package_name, argc, argv);
  
  SPVM_RUNTIME_API_free_env(env);
  SPVM_RUNTIME_API_free_runtime(runtime);
  
  return status_code;
}

