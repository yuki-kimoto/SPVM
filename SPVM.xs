#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"

#include <stdint.h>
#include "spvm_compiler.h"
#include "spvm_hash.h"
#include "spvm_array.h"
#include "spvm_util_allocator.h"
#include "spvm_constant_pool.h"
#include "spvm_bytecode_array.h"
#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_runtime_allocator.h"
#include "spvm_op.h"
#include "spvm_sub.h"
#include "spvm_data_api.h"

MODULE = SPVM::Compiler		PACKAGE = SPVM::Compiler

SV*
compile(...)
  PPCODE:
{
  // Create compiler
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  
  SPVM_ARRAY_push(compiler->include_pathes, "lib");
  
  SPVM_COMPILER_compile(compiler);
  
  if (compiler->error_count > 0) {
    croak("Compile error");
  }

  // Create run-time
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_new();
  
  // Copy constant pool to runtime
  runtime->constant_pool = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(compiler->constant_pool->length, sizeof(int32_t));
  memcpy(runtime->constant_pool, compiler->constant_pool->values, compiler->constant_pool->length * sizeof(int32_t));

  // Copy bytecodes to runtime
  runtime->bytecodes = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(compiler->bytecode_array->length, sizeof(uint8_t));
  memcpy(runtime->bytecodes, compiler->bytecode_array->values, compiler->bytecode_array->length * sizeof(uint8_t));
  
  // Free compiler
  SPVM_COMPILER_free(compiler);
  
  // Initialize runtime before push arguments and call subroutine
  SPVM_RUNTIME_init(runtime);

  XSRETURN(0);
}

SV*
bar(...)
  PPCODE:
{
  PerlIO_printf(PerlIO_stdout(), "bar\n");
  XSRETURN(0);
}

MODULE = SPVM		PACKAGE = SPVM
